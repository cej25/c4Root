#ifndef FATIMA_LEGACY_PULSE_BUILDER_H
#define FATIMA_LEGACY_PULSE_BUILDER_H

#include <cstdint>

namespace fatima
{
// Compatibility model for FatimaReader's existing pulse-building behaviour.
// This is deliberately kept in FATIMA processing, not the electronics decoder.
// It will be used by the new FATIMA Raw2Cal once parity is established.
struct TimedEdge
{
    std::uint32_t epoch = 0;
    std::uint16_t coarse = 0;
    double fine_ns = 0.0;
};

struct PairedPulse
{
    std::uint16_t channel = 0;
    TimedEdge lead;
    TimedEdge trail;
    TimedEdge accepted_trigger;
    double accepted_trigger_ns = 0.0;
};

class LegacyPulseBuilder
{
public:
    // One instance per board/event: the legacy reader tracks a single
    // pending leading edge, irrespective of channel.
    void Reset()
    {
        last_lead_ = {};
        has_lead_ = false;
        accepted_trigger_ = {};
        accepted_trigger_ns_ = 0.0;
    }

    template <typename RawWord, typename FineTime, typename Emit>
    void Process(const RawWord& word, bool calibration_ready,
                 FineTime&& fine_time, Emit&& emit)
    {
        if (word.kind == RawWord::Epoch) return;
        if ((word.flags & RawWord::InvalidFine) != 0) return;
        // The decoder has already enforced the TAMEX4 valid-channel range.
        const TimedEdge edge{word.epoch, word.coarse, fine_time(word.channel, word.fine)};

        // While building calibration histograms, the legacy reader skips
        // leading edges entirely; trailing edges cannot form pairs.
        if (!calibration_ready && word.leading) return;

        if (word.channel == 0)
        {
            accepted_trigger_ = edge;
            accepted_trigger_ns_ =
                static_cast<double>(edge.epoch) * 10240.0 +
                static_cast<double>(edge.coarse) * 5.0 - edge.fine_ns;
            return;
        }

        if (word.leading)
        {
            last_lead_ = edge;
            has_lead_ = true;
        }
        else if (has_lead_)
        {
            emit(PairedPulse{word.channel, last_lead_, edge,
                             accepted_trigger_, accepted_trigger_ns_});
            has_lead_ = false;
            last_lead_ = {};
        }
    }

private:
    TimedEdge last_lead_{};
    bool has_lead_ = false;
    TimedEdge accepted_trigger_{};
    double accepted_trigger_ns_ = 0.0;
};
} // namespace fatima

#endif
