#ifndef FRS_READER_SAFETY_H
#define FRS_READER_SAFETY_H

#include <cstddef>
#include <cstdint>

// Dependency-free helpers shared by the FRS reader and its regression tests.
namespace frs_reader_safety
{
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

// Hardware channels are one-based; zero and values past capacity are invalid.
inline bool ValidOneBasedChannel(std::int64_t channel, std::size_t capacity)
{
    return channel > 0 &&
           static_cast<std::uint64_t>(channel) <= capacity;
}

inline bool ValidPackedBlock(int start,
                             int end,
                             std::uint32_t time_count,
                             std::uint32_t flag_count,
                             std::size_t capacity)
{
    return start >= 0 &&
           end >= start &&
           static_cast<std::uint64_t>(end) <= time_count &&
           static_cast<std::uint64_t>(end) <= flag_count &&
           static_cast<std::uint64_t>(end) <= capacity;
}
} // namespace frs_reader_safety

#endif
