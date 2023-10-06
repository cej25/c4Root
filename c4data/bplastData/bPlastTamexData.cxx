#include "bPlastTamexData.h"

bPlastTamexData::bPlastTamexData()
    : fDet(0)
    , fChan(0)
    , fPMT_Lead(0)
{
}

bPlastTamexData::bPlastTamexData(UInt_t detNum, UInt_t chanNum, UInt_t PMT_Lead)
    : fDet(detNum)
    , fChan(chanNum)
    , fPMT_Lead(PMT_Lead)
{
}

ClassImp(bPlastTamexData)