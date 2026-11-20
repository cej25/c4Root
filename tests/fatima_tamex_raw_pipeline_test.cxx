#include "../c4source/digitisers/tamex/TamexDecoder.h"
#include "../c4source/digitisers/tamex/TamexFineTimeCalibration.h"
#include "../c4source/digitisers/tamex/TamexPulseBuilder.h"

#include <cassert>
#include <cmath>
#include <cstdint>
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

int main()
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
    return 0;
}
