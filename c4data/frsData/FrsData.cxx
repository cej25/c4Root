#include "FrsData.h"

FrsData::FrsData()
    : iScFrs(0)
    , fScFrs(0)
    , iScMain(0)
    , fScMain(0)
{
}

FrsData::FrsData(int sc1, UInt_t ScFrs, int sc2, UInt_t ScMain)
    : iScFrs(sc1)
    , fScFrs(ScFrs)
    , iScMain(sc2)
    , fScMain(ScMain)
{
}

ClassImp(FrsData)