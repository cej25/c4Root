#ifndef C4_VME_DIGITISER_DECODE_H
#define C4_VME_DIGITISER_DECODE_H

#include "FatimaVmePackedSafety.h"
#include "FatimaVmeQdcSafety.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

// Decode UCESB banks without FATIMA mappings. Header-only helpers are
// shared between the FairRoot readers and standalone decoder tests.
namespace c4 { namespace vme {

template<typename Words>
std::uint64_t Timestamp(const Words& words) {
    return (std::uint64_t(words[3]) << 48) |
           (std::uint64_t(words[2]) << 32) |
           (std::uint64_t(words[1]) << 16) |
           std::uint64_t(words[0]);
}

template<typename Bank, typename Emit>
void DecodeV1751(const Bank& bank, std::size_t slot, Emit emit) {
    const auto mask = static_cast<std::uint32_t>(bank._channels);
    // s100 FATIMA QDC uses channels 0..7, matching its legacy reader.
    for (std::uint32_t channel = 0; channel < 8; ++channel) {
        if ((mask & (1u << channel)) == 0) continue;
        // Packed fields have independent counters; index by packed entry,
        // not the physical channel number.
        std::uint32_t packed = 0;
        for (std::uint32_t c = 0; c < channel; ++c)
            if (mask & (1u << c)) ++packed;
        if (!fatima_vme_qdc_safety::CompleteEntry(
                packed, bank._channel_time, bank._chan_ext_time,
                bank._chan_fine_time, bank._qlong, bank._qshort))
            continue;
        emit(slot, static_cast<int>(bank._board_id), channel, packed, bank);
    }
}

template <std::size_t Blocks, typename Emit>
void DecodeV1290Blocks(std::uint32_t count, const std::uint32_t (&channels)[Blocks],
                       const std::uint32_t (&ends)[Blocks], std::uint32_t dataCount,
                       std::uint32_t edgeCount, Emit emit)
{
    std::uint32_t start = 0;
    const auto bounded = std::min<std::size_t>(Blocks, fatima_vme_packed_safety::BoundedBlockCount(count));
    for (std::size_t block = 0; block < bounded; ++block) {
        const auto end = ends[block];
        if (!fatima_vme_packed_safety::ValidTdcBlock(start, end, dataCount, edgeCount)) {
            if (end > start) start = end;
            continue;
        }
        for (auto index = start; index < end; ++index)
            emit(channels[block], index);
        start = end;
    }
}

template<typename Bank, typename Emit>
void DecodeV1290(const Bank& bank, std::size_t slot, Emit emit) {
    DecodeV1290Blocks(bank._measurement_nM, bank._measurement_nMI, bank._measurement_nME,
                       bank._measurement_n, bank._measurement_leadOrTrail,
                       [&](auto channel, auto index) {
                           emit(slot, static_cast<int>(bank._geo), channel, index, bank);
                       });
}

template<typename Bank>
std::vector<std::uint32_t> Waveform(const Bank& bank, std::uint32_t packed) {
    const auto& a = bank._sample_one[packed];
    const auto& b = bank._sample_two[packed];
    const auto& c = bank._sample_three[packed];
    const auto n = fatima_vme_qdc_safety::CompleteWaveformTriplets(a._, b._, c._);
    std::vector<std::uint32_t> result;
    result.reserve(3 * n);
    for (std::uint32_t i = 0; i < n; ++i) {
        result.push_back(a.v[i]);
        result.push_back(b.v[i]);
        result.push_back(c.v[i]);
    }
    return result;
}

}} // namespace c4::vme
#endif
