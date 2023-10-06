#include "bPlastTamexData.h"

bPlastTamexData::bPlastTamexData()
    : fDet(0)
    , fChan(0)
    , fbPlastLeadT(0)
    , fbPlastTrailT(0)
    , fbPlastToT(0)
{
}

bPlastTamexData::bPlastTamexData(UInt_t detNum, 
                                    UInt_t chanNum, 
                                    UInt_t fbPlastLeadT, 
                                    UInt_t fbPlastTrailT, 
                                    UInt_t fbPlastToT)
    : fDet(detNum)
    , fChan(chanNum)
    , fbPlastLeadT(fbPlastLeadT)
    , fbPlastTrailT(fbPlastTrailT)
    , fbPlastToT(fbPlastToT)
{
}

ClassImp(bPlastTamexData)