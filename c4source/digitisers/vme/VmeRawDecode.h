#ifndef VME_RAW_DECODE_H
#define VME_RAW_DECODE_H

#include "VmeDigitiserDecode.h"
#include "VmeDigitiserRawData.h"

namespace c4::vme
{
template <typename Bank>
void FillV1751(V1751RawData& hit, std::uint16_t procid, std::uint32_t subsystem,
                 std::uint64_t wr, std::size_t slot, int board,
                 std::uint32_t channel, std::uint32_t packed, const Bank& bank)
{
    hit.procid = procid;
    hit.board_slot = static_cast<std::uint16_t>(slot);
    hit.board_id = board;
    hit.channel = static_cast<std::uint16_t>(channel);
    hit.wr_timestamp = wr;
    hit.wr_subsystem = subsystem;
    hit.coarse = bank._channel_timev[packed];
    hit.extended = bank._chan_ext_timev[packed];
    hit.fine = bank._chan_fine_timev[packed];
    hit.qlong = bank._qlongv[packed];
    hit.qshort = bank._qshortv[packed];
    hit.sazc = packed < bank._chan_sazc ? bank._chan_sazcv[packed] : 0;
    hit.sbzc = packed < bank._chan_sbzc ? bank._chan_sbzcv[packed] : 0;
    hit.midscale = packed < bank._chan_midscale ?
        bank._chan_midscalev[packed] : 0;
    hit.waveform = c4::vme::Waveform(bank, packed);
}

template <typename Bank>
void FillV1290(V1290RawData& hit, std::uint16_t procid, std::uint32_t subsystem,
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
}
#endif
