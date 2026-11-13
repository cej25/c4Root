#ifndef FIMP_MULTIHIT_SAFETY_H
#define FIMP_MULTIHIT_SAFETY_H

#include <algorithm>
#include <cstddef>
#include <cstdint>

// Four aligned vectors are required to reconstruct each FIMP lead/trail pair.
// This helper is used by FimpRaw2Cal and its dependency-free regression tests.
namespace fimp_multihit_safety
{
inline std::size_t MatchedHitCount(std::size_t lead_coarse,
                                   std::size_t lead_fine,
                                   std::size_t trail_coarse,
                                   std::size_t trail_fine)
{
    return std::min({lead_coarse, lead_fine, trail_coarse, trail_fine});
}
// Packed hit blocks index coarse, fine, and lead/trail arrays in lockstep.
inline bool ValidPackedHitBlock(int start, int end,
                                std::size_t coarse_count,
                                std::size_t fine_count,
                                std::size_t lead_trail_count,
                                std::size_t capacity)
{
    return start >= 0 && end >= start &&
           static_cast<std::size_t>(end) <= coarse_count &&
           static_cast<std::size_t>(end) <= fine_count &&
           static_cast<std::size_t>(end) <= lead_trail_count &&
           static_cast<std::size_t>(end) <= capacity;
}

inline bool ValidFineTimeIndex(int channel, std::size_t channels,
                               std::uint32_t fine_bin, std::size_t bins)
{
    return channel >= 0 &&
           static_cast<std::size_t>(channel) < channels &&
           fine_bin < bins;
}

} // namespace fimp_multihit_safety

#endif
