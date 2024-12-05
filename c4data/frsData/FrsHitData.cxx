#include "FrsHitData.h"

FrsHitItem::FrsHitItem()
{

}

void FrsHitItem::SetAll(uint64_t wr_t,
                    uint16_t tpat,
                    Float_t x2,
                    Float_t y2,
                    Float_t x4,
                    Float_t y4,
                    Float_t a2,
                    Float_t b2,
                    Float_t a4,
                    Float_t b4,
                    Float_t AoQ,
                    Float_t AoQ_driftcorr,
                    Float_t AoQ_corr,
                    Float_t z,
                    Float_t z_driftcorr,
                    Float_t z2,
                    Float_t beta,
                    Float_t dEdeg,
                    Float_t dEdegoQ,
                    Float_t* rho,
                    Float_t* brho,
                    Float_t* music_dE,
                    Float_t* music_dE_cor,
                    Float_t sci_21l,
                    Float_t sci_21r,
                    Float_t sci_22l,
                    Float_t sci_22r,
                    Float_t sci_31l,
                    Float_t sci_31r,
                    Float_t sci_41l,
                    Float_t sci_41r,
                    Float_t sci_42l,
                    Float_t sci_42r,
                    Float_t sci_43l,
                    Float_t sci_43r,
                    Float_t sci_81l,
                    Float_t sci_81r,
                    Float_t sci_e_21,
                    Float_t sci_e_22,
                    Float_t sci_e_31,
                    Float_t sci_e_41,
                    Float_t sci_e_42,
                    Float_t sci_e_43,
                    Float_t sci_e_81,
                    Float_t sci_x_21,
                    Float_t sci_x_22,
                    Float_t sci_x_41,
                    Float_t sci_x_42,
                    Float_t sci_x_43,
                    Float_t sci_x_81,
                    Float_t sci_tof_21_41,
                    Float_t sci_tof_21_41_calib,
                    Float_t sci_tof_21_42,
                    Float_t sci_tof_21_42_calib,
                    Float_t sci_tof_21_81,
                    Float_t sci_tof_21_81_calib,
                    Float_t sci_tof_22_41,
                    Float_t sci_tof_22_41_calib,
                    Float_t sci_tof_22_81,
                    Float_t sci_tof_22_81_calib,
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
    fID_x2 = x2;
    fID_y2 = y2;
    fID_x4 = x4;
    fID_y4 = y4;
    fID_a2 = a2;
    fID_b2 = b2;
    fID_a4 = a4;
    fID_b4 = b4;
    fID_AoQ = AoQ;
    fID_AoQ_driftcorr = AoQ_driftcorr;
    fID_AoQ_corr = AoQ_corr;
    fID_z = z;
    fID_z_driftcorr = z_driftcorr;
    fID_z2 = z2;
    fID_beta = beta;
    fID_dEdeg = dEdeg;
    fID_dEdegoQ = dEdegoQ;
    for (int i = 0; i < 2; i++) fID_rho[i] = rho[i];
    for (int i = 0; i < 2; i++) fID_brho[i] = brho[i];
    for (int i = 0; i < 2; i++) fmusic_dE[i] = music_dE[i];
    for (int i = 0; i < 2; i++) fmusic_dE_cor[i] = music_dE_cor[i];
    fsci_21l = sci_21l;
    fsci_21r = sci_21r;
    fsci_22l = sci_22l;
    fsci_22r = sci_22r;
    fsci_31l = sci_31l;
    fsci_31r = sci_31r;
    fsci_41l = sci_41l;
    fsci_41r = sci_41r;
    fsci_42l = sci_42l;
    fsci_42r = sci_42r;
    fsci_43l = sci_43l;
    fsci_43r = sci_43r;
    fsci_81l = sci_81l;
    fsci_81r = sci_81r;
    fsci_e_21 = sci_e_21;
    fsci_e_22 = sci_e_22;
    fsci_e_31 = sci_e_31;
    fsci_e_41 = sci_e_41;
    fsci_e_42 = sci_e_42;
    fsci_e_43 = sci_e_43;
    fsci_e_81 = sci_e_81;
    fsci_x_21 = sci_x_21;
    fsci_x_22 = sci_x_22;
    fsci_x_41 = sci_x_41;
    fsci_x_42 = sci_x_42;
    fsci_x_43 = sci_x_43;
    fsci_x_81 = sci_x_81;
    fsci_tof_21_41 = sci_tof_21_41;
    fsci_tof_21_41_calib = sci_tof_21_41_calib;
    fsci_tof_21_42 = sci_tof_21_42;
    fsci_tof_21_42_calib = sci_tof_21_42_calib;
    fsci_tof_21_81 = sci_tof_21_81;
    fsci_tof_21_81_calib = sci_tof_21_81_calib;
    fsci_tof_22_41 = sci_tof_22_41;
    fsci_tof_22_41_calib = sci_tof_22_41_calib;
    fsci_tof_22_81 = sci_tof_22_81;
    fsci_tof_22_81_calib = sci_tof_22_81_calib;
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
    fID_x2 = 0;
    fID_y2 = 0;
    fID_x4 = 0;
    fID_y4 = 0;
    fID_a2 = 0;
    fID_b2 = 0;
    fID_a4 = 0;
    fID_b4 = 0;
    fID_AoQ = 0;
    fID_AoQ_driftcorr = 0;
    fID_AoQ_corr = 0;
    fID_z = 0;
    fID_z_driftcorr = 0;
    fID_z2 = 0;
    fID_beta = 0;
    fID_dEdeg = 0;
    fID_dEdegoQ = 0;
    memset(fID_rho, 0, sizeof(fID_rho));
    memset(fID_brho, 0, sizeof(fID_brho));
    memset(fmusic_dE, 0, sizeof(fmusic_dE));
    memset(fmusic_dE_cor, 0, sizeof(fmusic_dE_cor));
    fsci_21l = 0;
    fsci_21r = 0;
    fsci_22l = 0;
    fsci_22r = 0;
    fsci_31l = 0;
    fsci_31r = 0;
    fsci_41l = 0;
    fsci_41r = 0;
    fsci_42l = 0;
    fsci_42r = 0;
    fsci_43l = 0;
    fsci_43r = 0;
    fsci_81l = 0;
    fsci_81r = 0;
    fsci_e_21 = 0;
    fsci_e_22 = 0;
    fsci_e_31 = 0;
    fsci_e_41 = 0;
    fsci_e_42 = 0;
    fsci_e_43 = 0;
    fsci_e_81 = 0;
    fsci_x_21 = 0;
    fsci_x_22 = 0;
    fsci_x_41 = 0;
    fsci_x_42 = 0;
    fsci_x_43 = 0;
    fsci_x_81 = 0;
    fsci_tof_21_41 = 0;
    fsci_tof_21_41_calib = 0;
    fsci_tof_21_42 = 0;
    fsci_tof_21_42_calib = 0;
    fsci_tof_21_81 = 0;
    fsci_tof_21_81_calib = 0;
    fsci_tof_22_41 = 0;
    fsci_tof_22_41_calib = 0;
    fsci_tof_22_81 = 0;
    fsci_tof_22_81_calib = 0;
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

ClassImp(FrsHitItem)


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
    fID_beta_mhtdc = 0;
    fID_AoQ_mhtdc = 0;
    fID_AoQ_corr_mhtdc = 0;
    fID_z_mhtdc = 0;
    fID_z2_mhtdc = 0;
    fID_dEdeg_mhtdc = 0;
    fID_dEdegoQ_mhtdc = 0;
}

ClassImp(FrsMultiHitItem)