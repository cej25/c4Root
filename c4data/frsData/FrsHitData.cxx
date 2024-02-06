#include "FrsHitData.h"


FrsHitData::FrsHitData()
    :   fWR_TS(0)
    ,   ftime_in_ms(0)
    ,   fibin_for_s(0)
    ,   fibin_for_100ms(0)
    ,   fibin_for_spill(0)
    ,   fincrease_sc_temp2(0)
    ,   fincrease_sc_temp3(0)
    ,   fextraction_time_ms(0)
    ,   fibin_clean_for_s(0)
    ,   fibin_clean_for_100ms(0)
    ,   fibin_clean_for_spill(0)
    ,   fID_x2(0)
    ,   fID_x4(0)
    ,   fID_AoQ(0)
    ,   fID_AoQ_corr(0)
    ,   fID_z(0)
    ,   fID_z2(0)
    ,   fID_beta(0)
{

}


FrsHitData::FrsHitData(uint64_t WR_TS,
                    uint32_t time_in_ms, 
                    uint32_t ibin_for_s, 
                    uint32_t ibin_for_100ms,
                    uint32_t ibin_for_spill,
                    uint32_t* increase_sc_temp_main,
                    uint32_t* increase_sc_temp_user,
                    uint32_t increase_sc_temp2,
                    uint32_t increase_sc_temp3,
                    uint32_t extraction_time_ms, 
                    uint32_t ibin_clean_for_s, 
                    uint32_t ibin_clean_for_100ms,
                    uint32_t ibin_clean_for_spill,
                    Float_t id_x2,
                    Float_t id_x4,
                    Float_t id_AoQ,
                    Float_t id_AoQ_corr,
                    Float_t id_z,
                    Float_t id_z2,
                    Float_t id_beta)
    :   fWR_TS(WR_TS)
    ,   ftime_in_ms(time_in_ms)
    ,   fibin_for_s(ibin_for_s)
    ,   fibin_for_100ms(ibin_for_100ms)
    ,   fibin_for_spill(ibin_for_spill)
    ,   fincrease_sc_temp2(increase_sc_temp2)
    ,   fincrease_sc_temp3(increase_sc_temp3)
    ,   fextraction_time_ms(extraction_time_ms)
    ,   fibin_clean_for_s(ibin_clean_for_s)
    ,   fibin_clean_for_100ms(ibin_clean_for_100ms)
    ,   fibin_clean_for_spill(ibin_clean_for_spill)
    ,   fID_x2(id_x2)
    ,   fID_x4(id_x4)
    ,   fID_AoQ(id_AoQ)
    ,   fID_AoQ_corr(id_AoQ_corr)
    ,   fID_z(id_z)
    ,   fID_z2(id_z2)
    ,   fID_beta(id_beta)
{
    for (int i = 0; i < 32; i++)
    {
        fincrease_sc_temp_main[i] = increase_sc_temp_main[i];
        fincrease_sc_temp_user[i] = increase_sc_temp_user[i];
    }
}

FrsHitData::~FrsHitData()
{
}

ClassImp(FrsHitData)