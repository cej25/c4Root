#ifndef FEBEX_READER_H
#define FEBEX_READER_H

#include "FebexConversions.h"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <optional>

namespace febex
{
// Older summary banks indicate board presence with a nonzero trigger timestamp.
enum class SummaryLayout { WithBoardMetadata, WithTriggerTimestamp };

// Transfer the native UCESB FEBEX summary. For layouts with board metadata,
// a malformed hit list returns its slot. Older layouts retain complete hits
// from independently sized columns.
template <SummaryLayout Layout = SummaryLayout::WithBoardMetadata,
          typename Board, std::size_t N, typename OutputBoards>
std::optional<std::size_t> ReadBoards(const Board (&boards)[N], const std::uint32_t (&wrWords)[4],
                                      std::uint16_t wrId, std::uint16_t procid,
                                      const char* detectorName, OutputBoards& outputBoards)
{
    std::uint64_t timestamp = 0;
    for (std::size_t word = 0; word < std::size(wrWords); ++word)
        timestamp |= std::uint64_t{wrWords[word]} << (16 * word);

    for (std::size_t slot = 0; slot < std::size(boards); ++slot)
    {
        const auto& board = boards[slot];
        const auto eventTicks = febex::JoinTicks(board.event_trigger_time_hi, board.event_trigger_time_lo);
        if constexpr (Layout == SummaryLayout::WithBoardMetadata)
        {
            if (!board.present) continue;
        }
        else
        {
            if (!eventTicks) continue;
        }

        auto& output = outputBoards.emplace_back();
        output.detectorName = detectorName;
        output.procid = procid;
        output.wrId = wrId;
        output.wrTimestamp = timestamp;
        output.slot = slot;
        if constexpr (Layout == SummaryLayout::WithBoardMetadata)
        {
            output.sfp = board.sfp;
            output.card = board.board_id;
        }
        else
        {
            output.card = slot;
        }
        output.trigger = board.trig;
        output.hitPattern = board.hit_pattern;
        output.eventTicks = eventTicks;

        const auto completeCount = std::min<std::size_t>({
            board.channel_energy, board.channel_trigger_time_lo, board.channel_cfd,
            board.pileup, board.overflow, std::size(board.channel_energyv)});
        if constexpr (Layout == SummaryLayout::WithBoardMetadata)
        {
            if (completeCount != board.channel_energy || completeCount != board.channel_trigger_time_hi ||
                completeCount != board.channel_trigger_time_lo || completeCount != board.channel_cfd ||
                completeCount != board.pileup || completeCount != board.overflow)
                return slot;
        }

        std::uint32_t previousChannel = 0;
        output.hits.reserve(completeCount);
        for (std::size_t i = 0; i < completeCount; ++i)
        {
            const auto channel = board.channel_energyI[i];
            std::uint32_t channelTimeHigh = 0;
            if constexpr (Layout == SummaryLayout::WithBoardMetadata)
            {
                if (channel <= previousChannel || channel > std::size(board.channel_energyv) ||
                    channel != board.channel_trigger_time_hiI[i] || channel != board.channel_trigger_time_loI[i] ||
                    channel != board.channel_cfdI[i] || channel != board.pileupI[i] || channel != board.overflowI[i])
                    return slot;

                previousChannel = channel;
                channelTimeHigh = board.channel_trigger_time_hiv[i];
            }
            else
            {
                if (channel == 0 || channel > std::size(board.channel_energyv)) continue;
            }

            auto& hit = output.hits.emplace_back();
            hit.channel = channel - 1; // UCESB sparse indices are one-based.
            hit.channelTicks = febex::JoinTicks(channelTimeHigh, board.channel_trigger_time_lov[i]);
            hit.energyWord = board.channel_energyv[i];
            hit.cfd = board.channel_cfdv[i];
            hit.pileup = board.pileupv[i] != 0;
            hit.overflow = board.overflowv[i] != 0;
            hit.signedEnergy = febex::GammaSignedEnergy(hit.energyWord);
            hit.legacyChannelTimeNs = febex::LegacyChannelTimeNs(hit.channelTicks, hit.cfd);
            if constexpr (Layout == SummaryLayout::WithBoardMetadata)
            {
                hit.hitOffsetNs = febex::HitOffsetNs(output.eventTicks, hit.channelTicks, hit.cfd);
                hit.hasConvertedValues = true;
            }
        }
    }
    return std::nullopt;
}

// Transfer the native FEBEX trace layout, preserving its reported multiplicity.
template <typename Board, std::size_t N, typename Crate>
void ReadTraceBoards(const Board (&boards)[N], Crate& crate, const char* detectorName)
{
    if (!crate.wrTimestamp) return;
    for (std::size_t slot = 0; slot < N; ++slot)
    {
        const auto& input = boards[slot];
        const auto ticks = febex::JoinTicks(input.event_trigger_time_hi, input.event_trigger_time_lo);
        if (!ticks) continue;

        auto& board = crate.boards.emplace_back();
        board.reportedHits = input.num_channels_fired;
        auto& summary = board.summary;
        summary.detectorName = detectorName;
        summary.eventTicks = ticks;
        summary.wrTimestamp = crate.wrTimestamp;
        summary.wrId = crate.wrId;
        summary.procid = crate.procid;
        summary.hitPattern = input.hit_pattern;
        summary.slot = slot;
        summary.card = input.board_num;
        summary.trigger = input.trig;

        const auto count = std::min<std::size_t>({input.num_channels_fired, input.channel_id,
            input.channel_trigger_time_hi, input.channel_trigger_time_lo, input.channel_energy,
            input.pileup, input.overflow, std::size(input.channel_idv)});
        for (std::size_t i = 0; i < count; ++i)
        {
            const auto channel = input.channel_idv[i];
            if (channel >= std::size(input.trace_traces)) continue;

            const auto& trace = input.trace_traces[channel];
            const auto traceSize = std::min<std::size_t>(trace._, std::size(trace.v));
            board.traces.emplace_back(trace.v, trace.v + traceSize);
            auto& hit = summary.hits.emplace_back();
            hit.channel = channel;
            hit.channelTicks = febex::JoinTicks(input.channel_trigger_time_hiv[i], input.channel_trigger_time_lov[i]);
            hit.energyWord = input.channel_energyv[i];
            hit.cfd = i < input.channel_cfd ? input.channel_cfdv[i] : 0;
            hit.pileup = (input.pileupv[i] & 1u) != 0;
            hit.overflow = (input.overflowv[i] & 1u) != 0;
        }
    }
}
}
#endif
