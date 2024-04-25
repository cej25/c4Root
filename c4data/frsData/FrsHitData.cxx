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
                    Float_t beta,
                    Float_t dEdeg,
                    Float_t dEdegoQ,
                    Float_t* rho,
                    Float_t* brho,
                    Float_t* music_dE,
                    Float_t* music_dE_cor,
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
    fID_beta = beta;
    fID_dEdeg = dEdeg;
    fID_dEdegoQ = dEdegoQ;
    fID_rho = rho;
    fID_brho = brho;
    fmusic_dE = music_dE;
    fmusic_dE_cor = music_dE_cor;
    fsci_e = sci_e;
    fsci_l = sci_l;
    fsci_r = sci_r;
    fsci_x = sci_x;
    fsci_tof = sci_tof;
    fsci_tof_calib = sci_tof_calib;
    fsci_tof2 = sci_tof2;
    ftime_in_ms = time_in_ms;
    fibin_for_s = ibin_for_s;
    fibin_for_100ms = ibin_for_100ms;
    fibin_for_spill = ibin_for_spill;
    fincrease_sc_temp_main = increase_sc_temp_main;
    fincrease_sc_temp_user = increase_sc_temp_user;
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
    fID_AoQ_corr = 0;
    fID_z = 0;
    fID_z2 = 0;
    fID_beta = 0;
    fID_dEdeg = 0;
    fID_dEdegoQ = 0;
    fID_rho = 0;
    fID_brho = 0;
    fmusic_dE = 0;
    fmusic_dE_cor = 0;
    fsci_e = 0;
    fsci_l = 0;
    fsci_r = 0;
    fsci_x = 0;
    fsci_tof = 0;
    fsci_tof_calib = 0;
    fsci_tof2 = 0;
    ftime_in_ms = 0;
    fibin_for_s = 0;
    fibin_for_100ms = 0;
    fibin_for_spill = 0;
    fincrease_sc_temp_main = 0;
    fincrease_sc_temp_user = 0;
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

void FrsMultiHitItem::SetAll(Float_t beta, 
                            Float_t AoQ, 
                            Float_t AoQ_corr, 
                            Float_t z,
                            Float_t z2,
                            Float_t dEdeg,
                            Float_t dEdegoQ)
{
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