#include "BeamMonitorData.h"

BeamMonitorData::BeamMonitorData()
    : dtS2(0)
    , dtS4(0)
{
}

BeamMonitorData::BeamMonitorData(UInt_t S2, UInt_t S4)
    : dtS2(S2)
    , dtS4(S4)
{
}

ClassImp(BeamMonitorData)