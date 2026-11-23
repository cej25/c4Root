#ifndef VME_DIGITISER_RAW_DATA_H
#define VME_DIGITISER_RAW_DATA_H
#include "TObject.h"
#include <cstdint>
#include <vector>

// One electronics-level record per digitiser hit or measurement.
// Current readers store zero-based hardware channels.
class V1751RawData : public TObject {
public:
    std::uint16_t procid = 0;
    std::uint16_t board_slot = 0; // Zero-based index within the readout bank.
    std::int32_t board_id = 0;
    std::uint16_t channel = 0;
    std::uint32_t wr_subsystem = 0;
    std::uint64_t wr_timestamp = 0;
    std::uint32_t coarse = 0;
    std::uint32_t extended = 0;
    std::uint32_t fine = 0;
    std::uint32_t qlong = 0;
    std::uint32_t qshort = 0;
    std::uint32_t sazc = 0;
    std::uint32_t sbzc = 0;
    std::uint32_t midscale = 0;
    std::vector<std::uint32_t> waveform;
    ClassDef(V1751RawData, 1);
};

class V1290RawData : public TObject {
public:
    std::uint16_t procid = 0;
    std::uint16_t board_slot = 0; // Zero-based index within the readout bank.
    std::int32_t geo = 0;
    std::uint16_t channel = 0;
    std::uint32_t wr_subsystem = 0;
    std::uint64_t wr_timestamp = 0;
    std::uint32_t measurement = 0;
    std::uint8_t leading_or_trailing = 0;
    ClassDef(V1290RawData, 1);
};
#endif
