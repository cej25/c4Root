#ifndef STEFAN_PACKED_SAFETY_H
#define STEFAN_PACKED_SAFETY_H

#include <algorithm>
#include <cstdint>

namespace stefan_packed_safety
{
// StefanReader accesses these five UCESB arrays at the same packed hit index.
// Never read beyond a short array or the generated fixed capacity (16).
inline std::uint32_t CompleteChannelCount(std::uint32_t energy,
                                           std::uint32_t cfd,
                                           std::uint32_t trigger_time_lo,
                                           std::uint32_t pileup,
                                           std::uint32_t overflow)
{
    return std::min({energy, cfd, trigger_time_lo, pileup, overflow,
                     std::uint32_t{16}});
}
} // namespace stefan_packed_safety

#endif
