#ifndef FIMP_MULTIHIT_SAFETY_H
#define FIMP_MULTIHIT_SAFETY_H

#include <algorithm>
#include <cstddef>

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
} // namespace fimp_multihit_safety

#endif
