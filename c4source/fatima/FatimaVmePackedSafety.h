#ifndef FATIMA_VME_PACKED_SAFETY_H
#define FATIMA_VME_PACKED_SAFETY_H

#include <cstdint>

namespace fatima_vme_packed_safety
{
// The TDC's unpacked data and lead/trail arrays are independently counted.
// Validate each packed block before indexing the two arrays in lockstep.
inline bool ValidTdcBlock(std::uint32_t start, std::uint32_t end,
                          std::uint32_t data_count, std::uint32_t edge_count)
{
    return end >= start &&
           end <= data_count && end <= edge_count &&
           end <= 16384;
}

inline std::uint32_t BoundedBlockCount(std::uint32_t count)
{
    return count < 128 ? count : 128;
}
} // namespace fatima_vme_packed_safety

#endif
