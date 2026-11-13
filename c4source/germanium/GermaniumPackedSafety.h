#ifndef GERMANIUM_PACKED_SAFETY_H
#define GERMANIUM_PACKED_SAFETY_H

#include <algorithm>
#include <cstddef>
#include <cstdint>

namespace germanium_packed_safety
{
// Both Germanium FEBEX readers access these six unpacked arrays by a common
// packed index. All must contain the entry; generated arrays hold at most 16.
inline std::uint32_t CompleteChannelCount(std::uint32_t energy,
                                           std::uint32_t cfd,
                                           std::uint32_t trigger_hi,
                                           std::uint32_t trigger_lo,
                                           std::uint32_t pileup,
                                           std::uint32_t overflow)
{
    return std::min({energy, cfd, trigger_hi, trigger_lo, pileup,
                     overflow, std::uint32_t{16}});
}

// The generated trace bank has 16 entries, indexed by a one-based FEBEX ID.
inline bool ValidTraceChannel(std::uint32_t one_based_channel)
{
    return one_based_channel >= 1 && one_based_channel <= 16;
}
// UCESB's recorded waveform length can be less than the 4000-sample bank.
inline std::uint32_t PopulatedTraceSamples(std::uint32_t recorded)
{
    return std::min(recorded, std::uint32_t{4000});
}
} // namespace germanium_packed_safety

#endif
