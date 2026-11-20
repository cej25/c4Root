#ifndef TAMEX_TWINPEAKS_HITS_H
#define TAMEX_TWINPEAKS_HITS_H

#include "TamexDecoder.h"
#include "TamexPulseBuilder.h"
#include "TamexRawData.h"
#include "TClonesArray.h"

#include <new>

namespace tamex
{
template <typename Hit, typename FineTimes>
void AppendTwinpeaksHits(const TamexRawData& board, const FineTimes& times, TClonesArray& output)
{
    constexpr auto channels = Tamex4Format::channel_count;
    const auto fine_time = [&](std::uint16_t channel, std::uint32_t fine) {
        return times[board.Board() * channels + channel][fine];
    };
    LegacyPulseBuilder builder;
    for (const auto& word : board.Words())
    {
        if (word.kind != TamexRawWord::Edge || word.channel >= channels || word.fine >= Tamex4Format::fine_bins)
            continue;
        builder.Process(word, true, fine_time, [&](const PairedPulse& pulse) {
            new (output[output.GetEntriesFast()]) Hit(
                board.Trigger(), board.Board(), pulse.channel,
                static_cast<std::int64_t>(pulse.accepted_trigger_ns),
                pulse.accepted_trigger.epoch, pulse.accepted_trigger.coarse, pulse.accepted_trigger.fine_ns,
                pulse.lead.epoch, pulse.lead.coarse, pulse.lead.fine_ns,
                pulse.trail.epoch, pulse.trail.coarse, pulse.trail.fine_ns,
                board.WrSubsystem(), board.WrTimestamp());
        });
    }
}
}

#endif
