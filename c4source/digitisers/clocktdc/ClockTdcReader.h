#ifndef CLOCK_TDC_READER_H
#define CLOCK_TDC_READER_H

#include <algorithm>
#include <cstddef>
#include <cstdint>

namespace clocktdc
{
struct RawEdge
{
    std::uint32_t sparseIndex; // One-based UCESB index, useful for per-edge fine-time calibration.
    std::uint32_t channel; // Decoded hardware channel. The final sparse index is reserved for dummy words.
    std::uint32_t coarse;
    std::uint32_t fine;
    bool trailing;
};

template <std::size_t N>
struct PackedColumn
{
    std::size_t count;
    const std::uint32_t (&values)[N];
};

template <std::size_t N>
PackedColumn(std::size_t, const std::uint32_t (&)[N]) -> PackedColumn<N>;

constexpr std::uint64_t TriggerCoarseTime(std::uint32_t high, std::uint32_t low)
{
    return (std::uint64_t{high} << 22) + low;
}

// ClockTDC supplies coarse time, fine time, and edge flags for each packed hit.
template <std::size_t Blocks, std::size_t Coarse, std::size_t Fine, std::size_t Flags, typename Emit>
void ReadEdges(std::size_t blocks, const std::uint32_t (&indices)[Blocks],
               const std::uint32_t (&ends)[Blocks], PackedColumn<Coarse> coarse,
               PackedColumn<Fine> fine, PackedColumn<Flags> flags, Emit emit)
{
    const auto capacity = std::min({coarse.count, fine.count, flags.count, Coarse, Fine, Flags});
    const auto blockCount = std::min(blocks, Blocks);
    std::size_t start = 0;
    for (std::size_t block = 0; block < blockCount; ++block)
    {
        const std::size_t end = ends[block];
        if (end < start) continue;

        const auto channelIndex = indices[block];
        if (end <= capacity && channelIndex > 0 && channelIndex <= Blocks)
        {
            for (auto hit = start; hit < end; ++hit)
            {
                const bool trailing = (flags.values[hit] & 1u) != 0;
                // The unpacker packs channel * 2 + edge under a one-based sparse index.
                const auto channel = (channelIndex - static_cast<unsigned>(trailing)) / 2;
                emit(RawEdge{channelIndex, channel, coarse.values[hit], fine.values[hit], trailing});
            }
        }
        start = end;
    }
}
}
#endif
