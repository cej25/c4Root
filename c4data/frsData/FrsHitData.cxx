#include "FrsHitData.h"


FrsHitData::FrsHitData()
    :   fWR_TS(0)
{

}

FrsHitData::FrsHitData(uint64_t WR_TS)
    :   fWR_TS(WR_TS)
{
}

FrsHitData::~FrsHitData()
{
    /*delete fIncreaseScalerTemp;
    delete fDe_array;
    delete fMusicT1;
    delete fMusicT2;*/
}

ClassImp(FrsHitData)