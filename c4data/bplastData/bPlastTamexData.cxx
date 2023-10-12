#include "bPlastTamexData.h"

bPlastTamexData::bPlastTamexData()
    : fDet(0)
    , fChan(0)
    , fbPlastLeadT(0)
    , fbPlastTrailT(0)
    , fbPlastToT(0)
    , fbPlastEpoch(0)
{
}

/* there are some pre-trigger times, but I will probably not save these as they are only used to calculate the time difference between events */
bPlastTamexData::bPlastTamexData(UInt_t detNum, 
                                    UInt_t chanNum, 
                                    UInt_t bPlastLeadT, 
                                    UInt_t bPlastTrailT, 
                                    UInt_t bPlastToT,
                                    UInt_t bPlastEpoch)
    : fDet(detNum)
    , fChan(chanNum)
    , fbPlastLeadT(bPlastLeadT)
    , fbPlastTrailT(bPlastTrailT)
    , fbPlastToT(bPlastToT)
    , fbPlastEpoch(bPlastEpoch)
{
}

ClassImp(bPlastTamexData)