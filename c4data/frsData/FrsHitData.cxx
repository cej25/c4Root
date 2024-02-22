#include "FrsHitData.h"


FrsHitData::FrsHitData()
    // :   fWR_TS(0)
    // ,   ftime_in_ms(0)
    // ,   fibin_for_s(0)
    // ,   fibin_for_100ms(0)
    // ,   fibin_for_spill(0)
    // ,   fincrease_sc_temp2(0)
    // ,   fincrease_sc_temp3(0)
    // ,   fextraction_time_ms(0)
    // ,   fibin_clean_for_s(0)
    // ,   fibin_clean_for_100ms(0)
    // ,   fibin_clean_for_spill(0)
    // ,   fsci_tof2(0)
    // ,   fID_x2(0)
    // ,   fID_y2(0)
    // ,   fID_a2(0)
    // ,   fID_b2(0)
    // ,   fID_x4(0)
    // ,   fID_y4(0)
    // ,   fID_a4(0)
    // ,   fID_b4(0)
    // ,   fID_AoQ(0)
    // ,   fID_AoQ_corr(0)
    // ,   fID_z(0)
    // ,   fID_z2(0)
    // ,   fID_beta(0)
    // ,   fID_dEdegoQ(0)
    // ,   fID_dEdeg(0)
{

}

/*
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
                    Float_t* music_dE,
                    uint32_t* sci_e,
                    uint32_t* sci_l,
                    uint32_t* sci_r,
                    uint32_t sci_tof2,
                    Float_t id_x2,
                    Float_t id_y2,
                    Float_t id_a2,
                    Float_t id_b2,
                    Float_t id_x4,
                    Float_t id_y4,
                    Float_t id_a4,
                    Float_t id_b4,
                    Float_t id_AoQ,
                    Float_t id_AoQ_corr,
                    Float_t id_z,
                    Float_t id_z2,
                    Float_t id_beta,
                    Float_t id_dEdegoQ,
                    Float_t id_dEdeg,
                    std::vector<Float_t> id_AoQ_mhtdc,
                    std::vector<Float_t> id_AoQ_corr_mhtdc,
                    std::vector<Float_t> id_z_mhtdc,
                    std::vector<Float_t> id_z2_mhtdc,
                    std::vector<Float_t> id_dEdegoQ_mhtdc,
                    std::vector<Float_t> id_dEdeg_mhtdc)
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
    ,   fsci_tof2(sci_tof2)
    ,   fID_x2(id_x2)
    ,   fID_y2(id_y2)
    ,   fID_a2(id_a2)
    ,   fID_b2(id_b2)
    ,   fID_x4(id_x4)
    ,   fID_y4(id_y4)
    ,   fID_a4(id_a4)
    ,   fID_b4(id_b4)
    ,   fID_AoQ(id_AoQ)
    ,   fID_AoQ_corr(id_AoQ_corr)
    ,   fID_z(id_z)
    ,   fID_z2(id_z2)
    ,   fID_beta(id_beta)
    ,   fID_dEdegoQ(id_dEdegoQ)
    ,   fID_dEdeg(id_dEdeg)
{
    for (int i = 0; i < 32; i++)
    {
        fincrease_sc_temp_main[i] = increase_sc_temp_main[i];
        fincrease_sc_temp_user[i] = increase_sc_temp_user[i];
    }
    
    for (int i = 0; i < 6; i++)
    {
        fsci_e[i] = sci_e[i];
        fsci_l[i] = sci_l[i];
        fsci_r[i] = sci_r[i];
    }

    // >2 for more musics
    for (int i = 0; i < 2; i++)
    {
        fmusic_dE[i] = music_dE[i];
    }

    for (int i = 0; i < MAX_MHTDC_MULT; i++)
    {
        if (i < id_AoQ_mhtdc.size()) fID_AoQ_mhtdc.emplace_back(id_AoQ_mhtdc[i]);
        if (i < id_AoQ_corr_mhtdc.size()) fID_AoQ_corr_mhtdc.emplace_back(id_AoQ_corr_mhtdc[i]);
        if (i < id_z_mhtdc.size()) fID_z_mhtdc.emplace_back(id_z_mhtdc[i]);
        if (i < id_z2_mhtdc.size()) fID_z2_mhtdc.emplace_back(id_z2_mhtdc[i]);
        if (i < id_dEdeg_mhtdc.size()) fID_dEdeg_mhtdc.emplace_back(id_dEdeg_mhtdc[i]);
        if (i < id_dEdegoQ_mhtdc.size()) fID_dEdegoQ_mhtdc.emplace_back(id_dEdegoQ_mhtdc[i]);
    }
}
*/

FrsHitData::~FrsHitData()
{
}

ClassImp(FrsHitData)