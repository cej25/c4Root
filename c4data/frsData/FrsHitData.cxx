#include "FrsHitData.h"


FrsHitItem::FrsHitItem() {}

void FrsHitItem::SetMetaData(Long64_t wr_t, Short_t tpat)
{
    fwr_t = wr_t;
    ftpat = tpat;
}

void FrsHitItem::SetScalerData(Double_t time_in_ms,
                Double_t time_in_us,
                Int_t ibin_for_s,
                Int_t ibin_for_100ms,
                Int_t ibin_for_spill,
                Int_t ibin_clean_for_s,
                Int_t ibin_clean_for_100ms,
                Int_t ibin_clean_for_spill,
                Int_t extraction_time_ms,
                Int_t increase_scaler_temp[67])
{
    ftime_in_ms = time_in_ms;
    ftime_in_us = time_in_us;
    fibin_for_s = ibin_for_s;
    fibin_for_100ms = ibin_for_100ms;
    fibin_for_spill = ibin_for_spill;
    fibin_clean_for_s = ibin_clean_for_s;
    fibin_clean_for_100ms = ibin_clean_for_100ms;
    fibin_clean_for_spill = ibin_clean_for_spill;
    fextraction_time_ms = extraction_time_ms;
    for (int i = 0; i < 67; i++) fincrease_scaler_temp[i] = fincrease_scaler_temp[i];
}

void FrsHitItem::SetSciData(Float_t sci_e_21,
                Float_t sci_x_21,
                Float_t sci_e_22,
                Float_t sci_x_22,
                Float_t sci_e_31,
                Float_t sci_e_41,
                Float_t sci_x_41,
                Float_t sci_e_42,
                Float_t sci_x_42,
                Float_t sci_e_43,
                Float_t sci_x_43,
                Float_t sci_e_81,
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
                Float_t sci_tof_22_81_calib)
{
   fsci_e_21 = sci_e_21;
   fsci_x_21 = sci_x_21;
   fsci_e_22 = sci_e_22;
   fsci_x_22 = sci_x_22;
   fsci_e_31 = sci_e_31;
   fsci_e_41 = sci_e_41;
   fsci_x_41 = sci_x_41;
   fsci_e_42 = sci_e_42;
   fsci_x_42 = sci_x_42;
   fsci_e_43 = sci_e_43;
   fsci_x_43 = sci_x_43;
   fsci_e_81 = sci_e_81;
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
}

void FrsHitItem::SetMusicData(Float_t music_dE[2], Float_t music_dE_cor[2])
{
    for (int i = 0; i < 2; i++)
    {
        fmusic_dE[i] = music_dE[i];
        fmusic_dE_cor[i] = music_dE[i];
    }
}
        
void FrsHitItem::SetIDs(Float_t x2,
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
            Float_t rho[2],
            Float_t brho[2])
{
    fID_x2 =  x2;
    fID_y2 =  y2;
    fID_x4 =  x4;
    fID_y4 =  y4;
    fID_a2 =  a2;
    fID_b2 =  b2;
    fID_a4 =  a4;
    fID_b4 =  b4;
    fID_AoQ = AoQ;
    fID_AoQ_corr = AoQ_corr;
    fID_z = z;
    fID_z2 = z2;
    fID_beta = beta;
    fID_dEdeg = dEdeg;
    fID_dEdegoQ = dEdegoQ;
    for (int i = 0; i < 2; i++)
    {
        fID_rho[i] =  rho[i];
        fID_brho[i] =  brho[i];
    }    
}

void FrsHitItem::SetDriftCorrections(Float_t FRS_time, 
                        Float_t AoQ_driftcorr, 
                        Float_t z_driftcorr)
{
    FRS_time_mins = FRS_time;
    fID_AoQ_driftcorr = AoQ_driftcorr;
    fID_z_driftcorr = z_driftcorr;
}

ClassImp(FrsHitItem)


FrsMultiHitItem::FrsMultiHitItem() {}

void FrsMultiHitItem::SetAll(Float_t s2x,
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

ClassImp(FrsMultiHitItem)