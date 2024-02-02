#include "FrsHitData.h"


FrsHitData::FrsHitData()
    :   fWR_TS(0)
    ,   fID_x2(0)
    ,   fID_x4(0)
    ,   fID_AoQ(0)
    ,   fID_AoQ_corr(0)
    ,   fID_z(0)
    ,   fID_z2(0)
{

}

FrsHitData::FrsHitData(uint64_t WR_TS, Float_t id_x2, Float_t id_x4, Float_t id_AoQ, Float_t id_AoQ_corr, Float_t id_z, Float_t id_z2)
    :   fWR_TS(WR_TS)
    ,   fID_x2(id_x2)
    ,   fID_x4(id_x4)
    ,   fID_AoQ(id_AoQ)
    ,   fID_AoQ_corr(id_AoQ_corr)
    ,   fID_z(id_z)
    ,   fID_z2(id_z2)
{
}

FrsHitData::~FrsHitData()
{
}

ClassImp(FrsHitData)