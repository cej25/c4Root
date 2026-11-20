#ifndef FEBEX_TIMING_H
#define FEBEX_TIMING_H

#include <cstdint>

namespace febex
{
constexpr double LegacyChannelTimeNs(std::uint64_t channelTicks, std::uint8_t cfd)
{
    return (static_cast<double>(channelTicks & 0xffffffu) + (cfd & 0x3fu) / 64.0) * 10.0;
}

constexpr std::int32_t GammaSignedEnergy(std::uint32_t word)
{
    const auto magnitude = static_cast<std::int32_t>(word & 0x7fffffu);
    return word & 0x800000u ? -magnitude : magnitude;
}

// Take the difference before converting to nanoseconds, including at rollover.
// Quantise as in the legacy path, with the positive CFD fraction rounded down.
constexpr std::int64_t HitOffsetNs(std::uint64_t eventTicks, std::uint64_t channelTicks, std::uint8_t cfd)
{
    constexpr std::uint64_t halfPeriod = std::uint64_t{1} << 47;
    constexpr std::uint64_t mask = halfPeriod * 2 - 1;
    const auto offset = static_cast<std::int64_t>((channelTicks - eventTicks + halfPeriod) & mask)
                      - static_cast<std::int64_t>(halfPeriod);
    return offset * 10 + (cfd & 0x3fu) * 10 / 64;
}

// GermaniumFebexData stores only the low 24 channel ticks, at 10 ns per tick.
// Compare them with the matching part of the event clock. The signed
// difference is unique within half a counter period of the trigger.
constexpr std::int64_t LegacyHitOffsetNs(std::uint64_t eventTimeNs, double channelTimeNs)
{
    constexpr std::int64_t periodNs = (std::int64_t{1} << 24) * 10;
    constexpr auto halfPeriodNs = periodNs / 2;
    // Preserve the existing whole-nanosecond quantisation of the channel time.
    const auto offset = static_cast<std::int64_t>(channelTimeNs)
                      - static_cast<std::int64_t>(eventTimeNs % periodNs);
    if (offset < -halfPeriodNs) return offset + periodNs;
    if (offset >= halfPeriodNs) return offset - periodNs;
    return offset;
}
}

#endif
