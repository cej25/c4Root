#ifndef C4_FATIMA_VME_ELECTRONICS_CAL_DATA_H
#define C4_FATIMA_VME_ELECTRONICS_CAL_DATA_H

#include "TObject.h"
#include <cstdint>

// Detector-specific calibrated hits built from the generic VME electronics.
// Unlike the legacy vector interfaces, each TClonesArray entry is one hit.
class FatimaVmeQdcCalHit : public TObject {
public:
    std::uint64_t wr_timestamp = 0;
    std::int32_t detector_id = -1;
    std::int32_t board_id = -1;
    std::uint16_t channel = 0;
    std::uint32_t coarse_raw = 0;
    std::uint32_t fine_raw = 0;
    std::uint32_t qlong_raw = 0;
    std::uint32_t qshort_raw = 0;
    double coarse_time = 0;
    double fine_time = 0;
    double energy = 0;
    ClassDef(FatimaVmeQdcCalHit, 1);
};

class FatimaVmeTdcCalHit : public TObject {
public:
    std::uint64_t wr_timestamp = 0;
    std::uint32_t wr_subsystem = 0;
    std::int32_t detector_id = -1;
    std::int32_t geo = -1;
    std::uint16_t channel = 0;
    std::uint32_t measurement_raw = 0;
    std::uint8_t leading_or_trailing = 0;
    double time = 0;
    ClassDef(FatimaVmeTdcCalHit, 1);
};

#endif
