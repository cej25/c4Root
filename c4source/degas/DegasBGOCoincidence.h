#ifndef DEGAS_BGO_COINCIDENCE_H
#define DEGAS_BGO_COINCIDENCE_H

#include "BGOTwinpeaksCalData.h"
#include "DegasCalData.h"
#include "TBGOTwinpeaksConfiguration.h"

#include <cmath>

namespace degas
{
inline Long64_t BGOTimeDifference(const DegasCalData& hit, const BGOTwinpeaksCalData& shield)
{
    return static_cast<Long64_t>(shield.Get_wr_t()) - hit.Get_absolute_event_time();
}

inline bool IsBGOCoincidence(const DegasCalData& hit, const BGOTwinpeaksCalData& shield,
                             const TBGOTwinpeaksConfiguration& config)
{
    return static_cast<Long64_t>(hit.Get_detector_id()) == shield.Get_detector_id() && hit.Get_wr_t() && shield.Get_wr_t()
        && std::abs(BGOTimeDifference(hit, shield) + config.Offset()) < config.Window();
}
}

#endif
