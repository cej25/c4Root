#ifndef C4_CLUSTER_TIME_OVERLAP_H
#define C4_CLUSTER_TIME_OVERLAP_H

#include <cstdint>

// True if two closed time intervals overlap, allowing a nonnegative tolerance.
// Unsigned subtraction after signed ordering avoids overflow at int64 limits.
namespace c4_cluster_time
{
inline bool IntervalsOverlap(std::int64_t a_min, std::int64_t a_max,
                             std::int64_t b_min, std::int64_t b_max,
                             std::int64_t tolerance)
{
    if (tolerance < 0 || a_min > a_max || b_min > b_max) return false;
    const auto allowed = static_cast<std::uint64_t>(tolerance);
    if (a_min > b_max)
    {
        return static_cast<std::uint64_t>(a_min) -
               static_cast<std::uint64_t>(b_max) <= allowed;
    }
    if (b_min > a_max)
    {
        return static_cast<std::uint64_t>(b_min) -
               static_cast<std::uint64_t>(a_max) <= allowed;
    }
    return true;
}
} // namespace c4_cluster_time

#endif
