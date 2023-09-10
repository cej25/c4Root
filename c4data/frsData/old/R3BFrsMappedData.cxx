#include "R3BFrsMappedData.h"

R3BFrsMappedData::R3BFrsMappedData()
    : fZ(0)
    , fAoQ_corr(0)
    , fTrigger(0)
{
}

// Float_t Float_t
R3BFrsMappedData::R3BFrsMappedData(Float_t Z, Float_t AoQ_corr, unsigned int Trigger)
    : fZ(Z)
    , fAoQ_corr(AoQ_corr)
    , fTrigger(Trigger)
{
}

ClassImp(R3BFrsMappedData);