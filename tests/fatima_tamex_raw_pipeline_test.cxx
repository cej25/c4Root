#include "../c4source/digitisers/tamex/TamexReader.h"
#include "../c4source/digitisers/tamex/TamexFineTimeCalibration.h"
#include "../c4source/digitisers/tamex/TamexPulseBuilder.h"

#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <vector>

// Standalone surrogate of the persisted TamexRawWord layout.
struct RawWord
{
    enum : std::uint8_t { Epoch = 0, Edge = 1 };
    enum : std::uint8_t { InvalidFine = 1u << 3 };
    std::uint8_t kind = Epoch;
    std::uint32_t epoch = 0;
    std::uint16_t channel = 0;
    std::uint16_t coarse = 0;
    std::uint32_t fine = 0;
    bool leading = false;
    std::uint8_t flags = 0;
};

static void TestRawPipeline()
{
    // Epoch, accepted trigger, fast lead/trail, slow lead/trail,
    // invalid fine code. A single shared format decoder emits raw words.
    const std::uint32_t epoch[] = {0x10000005u, 0, 0, 0, 0, 0, 0};
    const std::uint32_t coarse[] = {0, 50, 60, 65, 70, 76, 80};
    const std::uint32_t fine[] = {0, 64, 128, 256, 128, 384, 1023};
    const std::uint32_t channels[] = {0, 0, 1, 1, 2, 2, 3};
    const std::uint32_t edges[] = {0, 1, 1, 0, 1, 0, 1};
    const tamex::PackedBoardView input{
        40, epoch, coarse, fine, channels, edges, 7, 7, 7, 7, 7};

    // Existing fine-time calibration: independent of detector mapping.
    tamex::FineTimeCalibration<> lut;
    lut.ObserveLeadingEdge(128);
    lut.ObserveLeadingEdge(256);
    lut.ObserveLeadingEdge(384);
    lut.Calculate();

    std::vector<RawWord> raw;
    const auto stats = tamex::Tamex4Decoder::Decode(input, 2,
        [&raw](const tamex::RawWord& word) {
            RawWord entry{};
            entry.kind = word.kind == tamex::WordKind::Epoch ?
                         RawWord::Epoch : RawWord::Edge;
            entry.epoch = word.epoch;
            entry.channel = word.channel;
            entry.coarse = word.coarse;
            entry.fine = word.fine;
            entry.leading = word.leading;
            if (word.invalid_fine) entry.flags |= RawWord::InvalidFine;
            raw.push_back(entry);
        });
    assert(stats.epoch_words == 1 && stats.edge_words == 6);
    assert(stats.invalid_fine_words == 1 && raw.size() == 7);

    tamex::LegacyPulseBuilder builder;
    std::vector<tamex::PairedPulse> pairs;
    for (const auto& word : raw)
        builder.Process(word, true,
            [&lut](std::uint16_t, std::uint32_t fine_bin) {
                return lut.Time(fine_bin);
            },
            [&pairs](const tamex::PairedPulse& pair) { pairs.push_back(pair); });

    assert(pairs.size() == 2);
    assert(pairs[0].channel == 1 && pairs[1].channel == 2);
    assert(pairs[0].lead.epoch == 5 && pairs[1].trail.epoch == 5);
    assert(pairs[0].accepted_trigger.coarse == 50);
    assert(pairs[1].accepted_trigger.coarse == 50);
    assert(std::abs(pairs[0].lead.fine_ns - lut.Time(128)) < 1e-12);
    assert(std::abs(pairs[1].trail.fine_ns - lut.Time(384)) < 1e-12);
    assert(std::abs(pairs[0].accepted_trigger_ns -
                    (5.0 * 10240.0 + 50.0 * 5.0 - lut.Time(64))) < 1e-10);
}

static void TestPulsePairing()
{
    tamex::LegacyPulseBuilder builder;
    std::vector<tamex::PairedPulse> pulses;
    auto calibrated = [](std::uint16_t channel, std::uint32_t fine) {
        return static_cast<double>(fine) / 1024.0 * 5.0 +
               static_cast<double>(channel) / 100.0;
    };
    const auto collect = [&](const tamex::PairedPulse& pulse) { pulses.push_back(pulse); };
    const auto process = [&](RawWord word, bool ready = true) {
        builder.Process(word, ready, calibrated, collect);
    };

    // Epoch markers are in the raw stream but must not disturb pending hits.
    process(RawWord{RawWord::Epoch, 42});
    // Trigger channel stores the latest trigger time (either edge polarity).
    process(RawWord{RawWord::Edge, 42, 0, 10, 512, true});
    process(RawWord{RawWord::Edge, 42, 1, 20, 100, true});
    process(RawWord{RawWord::Epoch, 43});
    process(RawWord{RawWord::Edge, 43, 1, 21, 110, false});
    assert(pulses.size() == 1);
    assert(pulses[0].channel == 1);
    assert(pulses[0].lead.epoch == 42 && pulses[0].trail.epoch == 43);
    assert(pulses[0].accepted_trigger.epoch == 42);
    assert(std::abs(pulses[0].accepted_trigger_ns - (42.0 * 10240.0 + 50.0 - 2.5)) < 1e-8);

    // A second leading edge replaces the first even across channels,
    // reproducing the legacy reader's single pending lead per board.
    process(RawWord{RawWord::Edge, 44, 3, 30, 200, true});
    process(RawWord{RawWord::Edge, 44, 4, 31, 201, true});
    process(RawWord{RawWord::Edge, 44, 4, 32, 202, false});
    assert(pulses.size() == 2);
    assert(pulses[1].channel == 4);
    assert(pulses[1].lead.coarse == 31);

    // Trailing edge without a leading edge emits nothing.
    process(RawWord{RawWord::Edge, 44, 4, 33, 203, false});
    assert(pulses.size() == 2);

    // Invalid fine words must not replace a pending leading edge.
    process(RawWord{RawWord::Edge, 45, 5, 40, 250, true});
    process(RawWord{RawWord::Edge, 45, 5, 41, 1023, true, RawWord::InvalidFine});
    process(RawWord{RawWord::Edge, 45, 5, 42, 255, false});
    assert(pulses.size() == 3);
    assert(pulses.back().lead.coarse == 40);
    assert(pulses.back().trail.coarse == 42);

    // Reset at every board/event, including accepted trigger metadata.
    builder.Reset();
    process(RawWord{RawWord::Edge, 46, 6, 50, 1, false});
    assert(pulses.size() == 3);
    process(RawWord{RawWord::Edge, 46, 6, 51, 2, true});
    process(RawWord{RawWord::Edge, 46, 6, 52, 3, false});
    assert(pulses.size() == 4);
    assert(pulses.back().accepted_trigger.epoch == 0);
    assert(pulses.back().accepted_trigger_ns == 0.0);

    // During the histogram-collection period, leading edges are ignored,
    // so no pulses are emitted.
    builder.Reset();
    process(RawWord{RawWord::Edge, 47, 1, 60, 10, true}, false);
    process(RawWord{RawWord::Edge, 47, 1, 61, 11, false}, false);
    assert(pulses.size() == 4);
}

static void TestFineTimeCalibration()
{
    tamex::FineTimeCalibration<> fine;
    // Same zero-occupancy linear fallback as the legacy reader.
    fine.Calculate();
    assert(fine.Entries() == 0);
    assert(fine.Time(0) == 0.0);
    assert(fine.Time(512) == 2.5);
    assert(fine.Time(1023) == 5.0 * 1023.0 / 1024.0);

    // Only valid raw leading edges are counted by the caller.
    fine.ObserveLeadingEdge(0);
    fine.ObserveLeadingEdge(0);
    fine.ObserveLeadingEdge(512);
    fine.ObserveLeadingEdge(1023); // TAMEX4 fast-filter failure
    fine.ObserveLeadingEdge(65536); // malformed word, not truncated
    fine.Calculate();
    assert(fine.Entries() == 3);
    assert(fine.Count(0) == 2);
    assert(fine.Count(512) == 1);
    assert(fine.Count(1023) == 0);
    assert(std::abs(fine.Time(0) - 5.0 / 3.0) < 1e-12);
    assert(std::abs(fine.Time(1) - 10.0 / 3.0) < 1e-12);
    assert(std::abs(fine.Time(512) - 25.0 / 6.0) < 1e-12);
    assert(std::abs(fine.Time(513) - 5.0) < 1e-12);

    // Loading an existing histogram must reproduce the same lookup table.
    std::array<std::uint64_t, 1024> histogram{};
    histogram[0] = 2;
    histogram[512] = 1;
    tamex::FineTimeCalibration<> from_file;
    from_file.SetCounts(histogram);
    from_file.Calculate();
    assert(from_file.Entries() == fine.Entries());
    for (std::size_t bin = 0; bin < 1024; ++bin)
        assert(from_file.Time(bin) == fine.Time(bin));

    bool rejected = false;
    try { (void)fine.Time(1024); }
    catch (const std::out_of_range&) { rejected = true; }
    assert(rejected);
}

int main()
{
    TestFineTimeCalibration();
    TestRawPipeline();
    TestPulsePairing();
}
