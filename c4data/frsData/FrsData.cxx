#include "FrsData.h"

FrsData::FrsData()
    : tdcData(0)
    , channel(0)
    , leadOrTrail(0)
{
}

FrsData::FrsData(UInt_t tdc, int chan, int lot)
    : tdcData(tdc) // v1290
    , channel(chan)
    , leadOrTrail(lot)
{
}

ClassImp(FrsData)