#ifndef MCP_TIMESTAMP_SAFETY_H
#define MCP_TIMESTAMP_SAFETY_H

#include <cstdint>

namespace mcp_timestamp_safety
{
// Four 16-bit White Rabbit clock words form a 64-bit unsigned timestamp.
// Mask individual words to prevent malformed higher bits from overlapping.
inline std::uint64_t AssembleWhiteRabbitTimestamp(std::uint32_t word0,
                                                  std::uint32_t word1,
                                                  std::uint32_t word2,
                                                  std::uint32_t word3)
{
    return (std::uint64_t{word3 & 0xffffu} << 48) |
           (std::uint64_t{word2 & 0xffffu} << 32) |
           (std::uint64_t{word1 & 0xffffu} << 16) |
           std::uint64_t{word0 & 0xffffu};
}
} // namespace mcp_timestamp_safety

#endif
