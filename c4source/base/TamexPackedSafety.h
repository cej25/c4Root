#ifndef C4_TAMEX_PACKED_SAFETY_H
#define C4_TAMEX_PACKED_SAFETY_H

#include <algorithm>
#include <cstdint>

namespace c4_tamex_packed_safety
{
// Event size is encoded in bytes; the first three 32-bit words are headers.
// Avoid unsigned underflow on short/empty payloads and cap the generated
// unpacked TAMEX arrays at 1024 entries.
inline std::uint32_t EventHitBudget(std::uint32_t bytes)
{
    const auto words = bytes / 4;
    return words > 3 ? std::min(words - 3, std::uint32_t{1024}) : 0;
}

inline bool ValidChannel(std::uint32_t channel, std::uint32_t count)
{
    return channel < count;
}

inline bool ValidFineBin(std::uint32_t fine, std::uint32_t bins)
{
    return fine < bins;
}

inline bool HasCompleteHit(std::uint32_t index,
                           std::uint32_t epoch,
                           std::uint32_t coarse,
                           std::uint32_t fine,
                           std::uint32_t channel,
                           std::uint32_t edge)
{
    return index < epoch && index < coarse && index < fine &&
           index < channel && index < edge;
}
} // namespace c4_tamex_packed_safety

#endif
