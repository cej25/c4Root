#include "../c4source/digitisers/tamex/TamexPulseBuilder.h"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <vector>

// Mirrored field interface of persisted TamexRawWord, no ROOT dependency.
struct RawWord
{
    enum : std::uint8_t { Epoch = 0, Edge = 1 };
    enum : std::uint8_t { InvalidFine = 1u << 3 };
    std::uint8_t kind = Edge;
    std::uint32_t epoch = 0;
    std::uint16_t channel = 0;
    std::uint16_t coarse = 0;
    std::uint32_t fine = 0;
    bool leading = false;
    std::uint8_t flags = 0;
};

int main()
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
    return 0;
}
