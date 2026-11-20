#ifndef FEBEX_TIMING_H
#define FEBEX_TIMING_H

#include <cstdint>

namespace febex
{
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
