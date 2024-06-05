#include "FrsHitData.h"

FrsHitData::FrsHitData()
{
}

FrsHitData::~FrsHitData()
{
}

FrsHitItem::FrsHitItem()
{

}

void FrsHitItem::SetAll(uint64_t wr_t,
                    uint16_t tpat,
                    uint64_t wr_travmus,
                    Float_t x2,
                    Float_t y2,
                    Float_t x4,
                    Float_t y4,
                    Float_t a2,
                    Float_t b2,
                    Float_t a4,
                    Float_t b4,
                    Float_t AoQ,
                    Float_t AoQ_corr,
                    Float_t z,
                    Float_t z2,
                    Float_t z_travmus,
                    Float_t beta,
                    Float_t dEdeg,
                    Float_t dEdegoQ,
                    Float_t* rho,
                    Float_t* brho,
                    Float_t* music_dE,
                    Float_t* music_dE_cor,
                    Float_t travmusic_dE,
                    Float_t travmusic_dE_cor,
                    Float_t* sci_e,
                    Float_t* sci_l,
                    Float_t* sci_r,
                    Float_t* sci_x,
                    Float_t* sci_tof,
                    Float_t* sci_tof_calib,
                    Float_t sci_tof2,
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
                    uint32_t ibin_clean_for_spill)
{
    fwr_t = wr_t;
    ftpat = tpat;
    fwr_travmus = wr_travmus;
    fID_x2 = x2;
    fID_y2 = y2;
    fID_x4 = x4;
    fID_y4 = y4;
    fID_a2 = a2;
    fID_b2 = b2;
    fID_a4 = a4;
    fID_b4 = b4;
    fID_AoQ = AoQ;
    fID_AoQ_corr = AoQ_corr;
    fID_z = z;
    fID_z2 = z2;
    fID_z_travmus = z_travmus;
    fID_beta = beta;
    fID_dEdeg = dEdeg;
    fID_dEdegoQ = dEdegoQ;
    for (int i = 0; i < 2; i++) fID_rho[i] = rho[i];
    for (int i = 0; i < 2; i++) fID_brho[i] = brho[i];
    for (int i = 0; i < 2; i++) fmusic_dE[i] = music_dE[i];
    for (int i = 0; i < 2; i++) fmusic_dE_cor[i] = music_dE_cor[i];
    ftravmusic_dE = travmusic_dE;
    ftravmusic_dE_cor = travmusic_dE_cor;
    for (int i = 0; i < 6; i++) fsci_e[i] = sci_e[i];
    for (int i = 0; i < 6; i++) fsci_l[i] = sci_l[i];
    for (int i = 0; i < 6; i++) fsci_r[i] = sci_r[i];
    for (int i = 0; i < 6; i++) fsci_x[i] = sci_x[i];
    for (int i = 0; i < 6; i++) fsci_tof[i] = sci_tof[i];
    for (int i = 0; i < 6; i++) fsci_tof_calib[i] = sci_tof_calib[i];
    fsci_tof2 = sci_tof2;
    ftime_in_ms = time_in_ms;
    fibin_for_s = ibin_for_s;
    fibin_for_100ms = ibin_for_100ms;
    fibin_for_spill = ibin_for_spill;
    for (int i = 0; i < 32; i++) fincrease_sc_temp_main[i] = increase_sc_temp_main[i];
    for (int i = 0; i < 32; i++) fincrease_sc_temp_user[i] = increase_sc_temp_user[i];
    fincrease_sc_temp2 = increase_sc_temp2;
    fincrease_sc_temp3 = increase_sc_temp3;
    fextraction_time_ms = extraction_time_ms;
    fibin_clean_for_s = ibin_clean_for_s;
    fibin_clean_for_100ms = ibin_clean_for_100ms;
    fibin_clean_for_spill = ibin_clean_for_spill;
}

void FrsHitItem::Reset()
{
    fwr_t = 0;
    ftpat = 0;
    fwr_travmus = 0;
    fID_x2 = 0;
    fID_y2 = 0;
    fID_x4 = 0;
    fID_y4 = 0;
    fID_a2 = 0;
    fID_b2 = 0;
    fID_a4 = 0;
    fID_b4 = 0;
    fID_AoQ = 0;
    fID_AoQ_corr = 0;
    fID_z = 0;
    fID_z2 = 0;
    fID_z_travmus = 0;
    fID_beta = 0;
    fID_dEdeg = 0;
    fID_dEdegoQ = 0;
    memset(fID_rho, 0, sizeof(fID_rho));
    memset(fID_brho, 0, sizeof(fID_brho));
    memset(fmusic_dE, 0, sizeof(fmusic_dE));
    memset(fmusic_dE_cor, 0, sizeof(fmusic_dE_cor));
    ftravmusic_dE = 0;
    ftravmusic_dE_cor = 0;
    memset(fsci_e, 0, sizeof(fsci_e));
    memset(fsci_l, 0, sizeof(fsci_l));
    memset(fsci_r, 0, sizeof(fsci_r));
    memset(fsci_x, 0, sizeof(fsci_x));
    memset(fsci_tof, 0, sizeof(fsci_tof));
    memset(fsci_tof_calib, 0, sizeof(fsci_tof_calib));
    fsci_tof2 = 0;
    ftime_in_ms = 0;
    fibin_for_s = 0;
    fibin_for_100ms = 0;
    fibin_for_spill = 0;
    memset(fincrease_sc_temp_main, 0, sizeof(fincrease_sc_temp_main));
    memset(fincrease_sc_temp_user, 0, sizeof(fincrease_sc_temp_user));
    fincrease_sc_temp2 = 0;
    fincrease_sc_temp3 = 0;
    fextraction_time_ms = 0;
    fibin_clean_for_s = 0;
    fibin_clean_for_100ms = 0;
    fibin_clean_for_spill = 0;
}

FrsMultiHitItem::FrsMultiHitItem()
{

}

void FrsMultiHitItem::SetAll(
                            Float_t s2x,
                            Float_t s2a,
                            Float_t s4x,
                            Float_t s4a,
                            Float_t tof,
                            Float_t beta, 
                            Float_t AoQ, 
                            Float_t AoQ_corr, 
                            Float_t z,
                            Float_t z2,
                            Float_t dEdeg,
                            Float_t dEdegoQ)
{
    fID_s2x_mhtdc = s2x;
    fID_s2a_mhtdc = s2a;
    fID_s4x_mhtdc = s4x;
    fID_s4a_mhtdc = s4a;
    fID_tof_mhtdc = tof;
    fID_beta_mhtdc = beta;
    fID_AoQ_mhtdc = AoQ;
    fID_AoQ_corr_mhtdc = AoQ_corr;
    fID_z_mhtdc = z;
    fID_z2_mhtdc = z2;
    fID_dEdeg_mhtdc = dEdeg;
    fID_dEdegoQ_mhtdc = dEdegoQ;
}

void FrsMultiHitItem::Reset()
{

}

ClassImp(FrsHitData)