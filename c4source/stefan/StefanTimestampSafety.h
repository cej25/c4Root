#ifndef STEFAN_TIMESTAMP_SAFETY_H
#define STEFAN_TIMESTAMP_SAFETY_H

#include <cstdint>

namespace stefan_timestamp_safety
{
// Assemble the four White Rabbit 16-bit words without shifting signed values.
inline std::uint64_t AssembleWhiteRabbitTimestamp(std::uint32_t word0,
                                                  std::uint32_t word1,
                                                  std::uint32_t word2,
                                                  std::uint32_t word3)
{
    return (std::uint64_t{word3} << 48) |
           (std::uint64_t{word2} << 32) |
           (std::uint64_t{word1} << 16) |
           std::uint64_t{word0};
}
} // namespace stefan_timestamp_safety

#endif
