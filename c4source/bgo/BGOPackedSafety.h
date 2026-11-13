#ifndef BGO_PACKED_SAFETY_H
#define BGO_PACKED_SAFETY_H

#include <algorithm>
#include <cstdint>

namespace bgo_packed_safety
{
// TAMEX event_size is in bytes; the decoder skips its three header words.
// Avoid unsigned subtraction underflow on absent/short event payloads.
inline std::uint32_t EventHitBudget(std::uint32_t event_size)
{
    const auto words = event_size / 4;
    return words > 3 ? std::min(words - 3, std::uint32_t{1024}) : 0;
}

inline bool ValidChannel(std::uint32_t channel, std::uint32_t capacity = 33)
{
    return channel < capacity;
}

inline bool ValidFineBin(std::uint32_t fine, std::uint32_t capacity = 1024)
{
    return fine < capacity;
}
} // namespace bgo_packed_safety

#endif
