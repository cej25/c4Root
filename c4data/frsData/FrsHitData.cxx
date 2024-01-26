#include "FrsHitData.h"


FrsHitData::FrsHitData()
    :   fWR_TS(0)
    ,   fID_x2(0)
    ,   fID_x4(0)
{

}

FrsHitData::FrsHitData(uint64_t WR_TS, Float_t id_x2, Float_t id_x4)
    :   fWR_TS(WR_TS)
    ,   fID_x2(id_x2)
    ,   fID_x4(id_x4)
{
}

FrsHitData::~FrsHitData()
{
}

ClassImp(FrsHitData)