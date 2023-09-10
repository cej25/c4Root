#include "FrsData.h"

FrsData::FrsData()
    : fZ(0.)
    , fAoQ(0.)
    , fA2(0.)
    , fA4(0.)
    , fX2(0.)
    , fX4(0.)
    , fBeta(0.)
    //, fBrho0(0.)
    //, fBrho1(0.)
{
}

FrsData::FrsData(Float_t Z,
                     Float_t AoQ,
                     Float_t a2,
                     Float_t a4,
                     Float_t x2,
                     Float_t x4,
                     Float_t beta)
    : fZ(Z)
    , fAoQ(AoQ)
    , fA2(a2)
    , fA4(a4)
    , fX2(x2)
    , fX4(x4)
    , fBeta(beta)
{
}

ClassImp(FrsData)
