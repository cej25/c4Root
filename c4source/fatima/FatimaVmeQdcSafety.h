#ifndef FATIMA_VME_QDC_SAFETY_H
#define FATIMA_VME_QDC_SAFETY_H

#include <algorithm>
#include <cstdint>

namespace fatima_vme_qdc_safety
{
// Each QDC field is unpacked independently; only complete packed entries
// may be combined into a reconstructed QDC hit.
inline bool CompleteEntry(std::uint32_t index,
                          std::uint32_t coarse,
                          std::uint32_t extended,
                          std::uint32_t fine,
                          std::uint32_t qlong,
                          std::uint32_t qshort)
{
    return index < 64 && index < coarse && index < extended &&
           index < fine && index < qlong && index < qshort;
}

// Waveforms are stored in three independently counted sample arrays of 224
// elements each. The existing decoder uses up to 120 interleaved triplets.
inline std::uint32_t CompleteWaveformTriplets(std::uint32_t first,
                                              std::uint32_t second,
                                              std::uint32_t third)
{
    return std::min({first, second, third, std::uint32_t{120}});
}
} // namespace fatima_vme_qdc_safety

#endif
