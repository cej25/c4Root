#ifndef VME_READER_H
#define VME_READER_H

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

template <std::size_t Channels, typename Emit>
void DecodeV775(std::uint32_t count, const std::uint32_t (&indices)[Channels],
                const std::uint32_t (&samples)[Channels], Emit emit)
{
    const auto bounded = std::min<std::size_t>(count, Channels);
    for (std::size_t i = 0; i < bounded; ++i)
    {
        const auto index = indices[i];
        if (index == 0 || index > Channels) continue;

        const auto sample = samples[i];
        emit(index - 1, sample & 0x0fff, static_cast<std::int32_t>((sample >> 12) & 0x7));
    }
}

template<typename Bank, typename Emit>
void DecodeV1751(const Bank& bank, std::size_t slot, Emit emit) {
    const auto mask = static_cast<std::uint32_t>(bank.channels);
    // The V1751 channel mask has one bit for each of its eight hardware channels.
    for (std::uint32_t channel = 0; channel < 8; ++channel) {
        if ((mask & (1u << channel)) == 0) continue;
        // Packed fields have independent counters; index by packed entry,
        // not the physical channel number.
        std::uint32_t packed = 0;
        for (std::uint32_t c = 0; c < channel; ++c)
            if (mask & (1u << c)) ++packed;
        if (!fatima_vme_qdc_safety::CompleteEntry(
                packed, bank.channel_time, bank.chan_ext_time,
                bank.chan_fine_time, bank.qlong, bank.qshort))
            continue;
        emit(slot, static_cast<int>(bank.board_id), channel, packed, bank);
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
        const auto channel = channels[block];
        if (channel >= 1 && channel <= 32) {
            // UCESB sparse indices start at one. The raw records use hardware channels.
            for (auto index = start; index < end; ++index)
                emit(channel - 1, index);
        }
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
    const auto& a = bank.sample_one[packed];
    const auto& b = bank.sample_two[packed];
    const auto& c = bank.sample_three[packed];
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

template <typename Hit, typename Bank>
void FillV1751(Hit& hit, std::uint16_t procid, std::uint32_t subsystem,
                 std::uint64_t wr, std::size_t slot, int board,
                 std::uint32_t channel, std::uint32_t packed, const Bank& bank)
{
    hit.procid = procid;
    hit.board_slot = static_cast<std::uint16_t>(slot);
    hit.board_id = board;
    hit.channel = static_cast<std::uint16_t>(channel);
    hit.wr_timestamp = wr;
    hit.wr_subsystem = subsystem;
    hit.coarse = bank.channel_timev[packed];
    hit.extended = bank.chan_ext_timev[packed];
    hit.fine = bank.chan_fine_timev[packed];
    hit.qlong = bank.qlongv[packed];
    hit.qshort = bank.qshortv[packed];
    hit.sazc = packed < bank.chan_sazc ? bank.chan_sazcv[packed] : 0;
    hit.sbzc = packed < bank.chan_sbzc ? bank.chan_sbzcv[packed] : 0;
    hit.midscale = packed < bank.chan_midscale ?
        bank.chan_midscalev[packed] : 0;
    hit.waveform = c4::vme::Waveform(bank, packed);
}

template <typename Hit, typename Bank>
void FillV1290(Hit& hit, std::uint16_t procid, std::uint32_t subsystem,
                 std::uint64_t wr, std::size_t slot, int geo,
                 std::uint32_t channel, std::uint32_t index, const Bank& bank)
{
    hit.procid = procid;
    hit.board_slot = static_cast<std::uint16_t>(slot);
    hit.geo = geo;
    hit.channel = static_cast<std::uint16_t>(channel);
    hit.wr_timestamp = wr;
    hit.wr_subsystem = subsystem;
    hit.measurement = bank._measurement_data[index];
    hit.leading_or_trailing = bank._measurement_leadOrTrailv[index];
}

}} // namespace c4::vme
#endif
