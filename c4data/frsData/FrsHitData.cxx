#include "FrsHitData.h"


FrsHitItem::FrsHitItem() {}

void FrsHitItem::SetMetaData(Long64_t wr_t, Short_t tpat, TString setup, Long64_t travmus_wr_t)
{
    fwr_t = wr_t;
    ftpat = tpat;
    setup_file = setup;
    ftravmus_wr_t = travmus_wr_t;
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

void FrsHitItem::SetSciData(Float_t sci_e_11,
                            Float_t sci_x_11,
                            Float_t sci_e_21,
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
                            Float_t sci_tof_11_21,
                            Float_t sci_tof_11_21_calib,
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
    fsci_e_11 = sci_e_11;
    fsci_x_11 = sci_x_11;
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
    fsci_tof_11_21 = sci_tof_11_21;
    fsci_tof_11_21_calib = sci_tof_11_21_calib;
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

void FrsHitItem::SetMusicData(Float_t music21_dE,
                            Float_t music22_dE,
                            Float_t music41_dE,
                            Float_t music42_dE,
                            Float_t music43_dE,
                            Float_t music21_dE_cor,
                            Float_t music22_dE_cor,
                            Float_t music41_dE_cor,
                            Float_t music42_dE_cor,
                            Float_t music43_dE_cor)
{
    fmusic21_dE = music21_dE;
    fmusic22_dE = music22_dE;
    fmusic41_dE = music41_dE;
    fmusic42_dE = music42_dE;
    fmusic43_dE = music43_dE;
    fmusic21_dE_cor =  music21_dE_cor;
    fmusic22_dE_cor =  music22_dE_cor;
    fmusic41_dE_cor =  music41_dE_cor;
    fmusic42_dE_cor =  music42_dE_cor;
    fmusic43_dE_cor =  music43_dE_cor;
}

        
void FrsHitItem::SetIDs(Float_t x1,
                        Float_t y1,
                        Float_t a1,
                        Float_t b1,
                        Float_t x2,
                        Float_t y2,
                        Float_t x4,
                        Float_t y4,
                        Float_t a2,
                        Float_t b2,
                        Float_t a4,
                        Float_t b4,
                        Float_t beta_s1s2,
                        Float_t AoQ_s1s2,
                        Float_t AoQ_corr_s1s2,
                        Float_t z21,
                        Float_t z22,
                        Float_t beta_s2s4,
                        Float_t AoQ_s2s4,
                        Float_t AoQ_corr_s2s4,
                        Float_t z41,
                        Float_t z42,
                        Float_t z43,
                        Float_t dEdegoQ,
                        Float_t dEdeg_z41,
                        Float_t rho[4],
                        Float_t brho[4])
{
    fID_x1 = x1;
    fID_y1 = y1;
    fID_a1 = a1;
    fID_b1 = b1;
    fID_x2 = x2;
    fID_y2 = y2;
    fID_x4 = x4;
    fID_y4 = y4;
    fID_a2 = a2;
    fID_b2 = b2;
    fID_a4 = a4;
    fID_b4 = b4;
    fID_beta_s1s2 = beta_s1s2;
    fID_AoQ_s1s2 = AoQ_s1s2;
    fID_AoQ_corr_s1s2 = AoQ_corr_s1s2;
    fID_z21 = z21;
    fID_z22 = z22;
    fID_beta_s2s4 = beta_s2s4;
    fID_AoQ_s2s4 = AoQ_s2s4;
    fID_AoQ_corr_s2s4 = AoQ_corr_s2s4;
    fID_z41 = z41;
    fID_z42 = z42;
    fID_z43 = z43;
    fID_dEdegoQ = dEdegoQ;
    fID_dEdeg_z41 = dEdeg_z41;
    for (int i = 0; i < 4; i++)
    {
        fID_rho[i] =  rho[i];
        fID_brho[i] =  brho[i];
    }    
}

void FrsHitItem::SetDriftCorrections(Float_t FRS_time,
                        Float_t AoQs1s2_driftcorr,
                        Float_t AoQs2s4_driftcorr,
                        Float_t z21_driftcorr,
                        Float_t z22_driftcorr,
                        Float_t z41_driftcorr,
                        Float_t z42_driftcorr,
                        Float_t z43_driftcorr)
{
    FRS_time_mins = FRS_time;
    fID_AoQs1s2_driftcorr = AoQs1s2_driftcorr;
    fID_AoQs2s4_driftcorr = AoQs2s4_driftcorr;
    fID_z21_driftcorr = z21_driftcorr;
    fID_z22_driftcorr = z22_driftcorr;
    fID_z41_driftcorr = z41_driftcorr;
    fID_z42_driftcorr = z42_driftcorr;
    fID_z43_driftcorr = z43_driftcorr;
}

ClassImp(FrsHitItem)


FrsMultiHitItem::FrsMultiHitItem() {}


void FrsMultiHitItem::SetS1S2(std::vector<Float_t> s1x,
                    std::vector<Float_t> s1a,
                    std::vector<Float_t> s2x_s1s2,
                    std::vector<Float_t> s2a_s1s2,
                    std::vector<Float_t> tof_s1s2,
                    std::vector<Float_t> beta_s1s2,
                    std::vector<Float_t> AoQ_s1s2,
                    std::vector<Float_t> AoQ_corr_s1s2,
                    std::vector<Float_t> z21,
                    std::vector<Float_t> z22)
{
    fID_s1x_mhtdc = s1x;
    fID_s1a_mhtdc = s1a;
    fID_s2x_s1s2_mhtdc = s2x_s1s2;
    fID_s2a_s1s2_mhtdc = s2a_s1s2;
    fID_tof_s1s2_mhtdc = tof_s1s2;
    fID_beta_s1s2_mhtdc = beta_s1s2;
    fID_AoQ_s1s2_mhtdc = AoQ_s1s2;
    fID_AoQ_corr_s1s2_mhtdc = AoQ_corr_s1s2;
    fID_z21_mhtdc = z21;
    fID_z22_mhtdc = z22;
}



void FrsMultiHitItem::SetS2S4(std::vector<Float_t> s2x_s2s4,
            std::vector<Float_t> s2a_s2s4,
            std::vector<Float_t> s4x,
            std::vector<Float_t> s4a,
            std::vector<Float_t> tof_s2s4,
            std::vector<Float_t> beta_s2s4,
            std::vector<Float_t> AoQ_s2s4,
            std::vector<Float_t> AoQ_corr_s2s4,
            std::vector<Float_t> z41,
            std::vector<Float_t> z42,
            std::vector<Float_t> z43,
            std::vector<Float_t> dEdegoQ,
            std::vector<Float_t> dEdeg_z41)
{
    fID_s2x_s2s4_mhtdc = s2x_s2s4;
    fID_s2a_s2s4_mhtdc = s2a_s2s4;
    fID_s4x_mhtdc = s4x;
    fID_s4a_mhtdc = s4a;
    fID_tof_s2s4_mhtdc = tof_s2s4;
    fID_beta_s2s4_mhtdc = beta_s2s4;
    fID_AoQ_s2s4_mhtdc = AoQ_s2s4;
    fID_AoQ_corr_s2s4_mhtdc = AoQ_corr_s2s4;
    fID_z41_mhtdc = z41;
    fID_z42_mhtdc = z42;
    fID_z43_mhtdc = z43;
    fID_dEdegoQ_mhtdc = dEdegoQ;
    fID_dEdeg_z41_mhtdc = dEdeg_z41;
}



// void FrsMultiHitItem::SetAll(Float_t s2x,
//                             Float_t s2a,
//                             Float_t s4x,
//                             Float_t s4a,
//                             Float_t tof,
//                             Float_t beta, 
//                             Float_t AoQ, 
//                             Float_t AoQ_corr, 
//                             Float_t z,
//                             Float_t z2,
//                             Float_t dEdeg,
//                             Float_t dEdegoQ)
// {
//     fID_s2x_mhtdc = s2x;
//     fID_s2a_mhtdc = s2a;
//     fID_s4x_mhtdc = s4x;
//     fID_s4a_mhtdc = s4a;
//     fID_tof_mhtdc = tof;
//     fID_beta_mhtdc = beta;
//     fID_AoQ_mhtdc = AoQ;
//     fID_AoQ_corr_mhtdc = AoQ_corr;
//     fID_z_mhtdc = z;
//     fID_z2_mhtdc = z2;
//     fID_dEdeg_mhtdc = dEdeg;
//     fID_dEdegoQ_mhtdc = dEdegoQ;
// }

ClassImp(FrsMultiHitItem)