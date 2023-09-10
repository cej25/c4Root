#include "GermaniumFebexData.h"

GermaniumFebexData::GermaniumFebexData()
    : fGeFired(0)
    , fSumTimeLo(0)
    , fSumTimeHi(0)
    , fHitPattern(0)
    , fChanTimeLo(0)
    , fChanTimeHi(0)
    , fChanCFLo(0)
    , fChanCFHi(0)
    , fPileup(0)
    , fOverflow(0)
    , fDetIds(0)
    , fCrystalIds(0)
{
}

GermaniumFebexData::GermaniumFebexData(Int_t GeFired,
                                           uint32_t sumTimeLo,
                                           uint32_t sumTimeHi,
                                           uint32_t hitPattern,
                                           uint32_t chanTimeLo,
                                           uint32_t chanTimeHi,
                                           uint32_t chanCFLo,
                                           uint32_t chanCFHi,
                                           uint32_t pileup,
                                           uint32_t overflow,
                                           uint32_t detIds,
                                           uint32_t crystalIds)
    : fGeFired(GeFired)
    , fSumTimeLo(sumTimeLo)
    , fSumTimeHi(sumTimeHi)
    , fHitPattern(hitPattern)
    , fChanTimeLo(chanTimeLo)
    , fChanTimeHi(chanTimeHi)
    , fChanCFLo(chanCFLo)
    , fChanCFHi(chanCFHi)
    , fPileup(pileup)
    , fOverflow(overflow)
    , fDetIds(detIds)
    , fCrystalIds(crystalIds)
{
}

ClassImp(GermaniumFebexData)