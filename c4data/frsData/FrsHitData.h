#ifndef FrsHitData_H
#define FrsHitData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

typedef Int_t Int_t;
typedef Float_t Float_t;

class FrsHitItem : public TObject
{
    public:
        FrsHitItem();

        void SetMetaData(Long64_t wr_t, Short_t tpat, TString setup, Long64_t travmus_wr_t);

        void SetScalerData(Double_t time_in_ms,
                        Double_t time_in_us,
                        Int_t ibin_for_s,
                        Int_t ibin_for_100ms,
                        Int_t ibin_for_spill,
                        Int_t ibin_clean_for_s,
                        Int_t ibin_clean_for_100ms,
                        Int_t ibin_clean_for_spill,
                        Int_t extraction_time_ms,
                        Int_t increase_scaler_temp[67]);

        void SetSciData(Float_t sci_e_11,
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
                        Float_t sci_tof_22_81_calib);

        void SetMusicData(Float_t music21_dE,
                        Float_t music22_dE,
                        Float_t music41_dE,
                        Float_t music42_dE,
                        Float_t music43_dE,
                        Float_t music21_dE_cor,
                        Float_t music22_dE_cor,
                        Float_t music41_dE_cor,
                        Float_t music42_dE_cor,
                        Float_t music43_dE_cor);
        
        void SetIDs(Float_t x1,
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
                    Float_t brho[4]);

        void SetDriftCorrections(Float_t FRS_time,
                                Float_t AoQs1s2_driftcorr,
                                Float_t AoQs2s4_driftcorr,
                                Float_t z21_driftcorr,
                                Float_t z22_driftcorr,
                                Float_t z41_driftcorr,
                                Float_t z42_driftcorr,
                                Float_t z43_driftcorr);


        Long64_t Get_wr_t() const { return fwr_t; }
        Short_t Get_tpat() const { return ftpat; }
        TString Get_setup_file() const { return setup_file; }
        Long64_t Get_travmus_wr_t() const { return ftravmus_wr_t; }
        Double_t Get_time_in_ms() const { return ftime_in_ms; }
        Double_t Get_time_in_us() const { return ftime_in_us; }
        Int_t Get_ibin_for_s() const { return fibin_for_s; }
        Int_t Get_ibin_for_100ms() const { return fibin_for_100ms; }
        Int_t Get_ibin_for_spill() const { return fibin_for_spill; }
        Int_t Get_ibin_clean_for_s() const { return fibin_clean_for_s; }
        Int_t Get_ibin_clean_for_100ms() const { return fibin_clean_for_100ms; }
        Int_t Get_ibin_clean_for_spill() const { return fibin_clean_for_spill; }
        Int_t Get_extraction_time_ms() const { return fextraction_time_ms; }
        const Int_t (&Get_increase_scaler_temp() const) [67] { return fincrease_scaler_temp; }
        Float_t Get_sci_e_11() const { return fsci_e_11; }
        Float_t Get_sci_x_11() const { return fsci_x_11; }
        Float_t Get_sci_e_21() const { return fsci_e_21; }
        Float_t Get_sci_x_21() const { return fsci_x_21; }
        Float_t Get_sci_e_22() const { return fsci_e_22; }
        Float_t Get_sci_x_22() const { return fsci_x_22; }
        Float_t Get_sci_e_31() const { return fsci_e_31; }
        Float_t Get_sci_e_41() const { return fsci_e_41; }
        Float_t Get_sci_x_41() const { return fsci_x_41; }
        Float_t Get_sci_e_42() const { return fsci_e_42; }
        Float_t Get_sci_x_42() const { return fsci_x_42; }
        Float_t Get_sci_e_43() const { return fsci_e_43; }
        Float_t Get_sci_x_43() const { return fsci_x_43; }
        Float_t Get_sci_e_81() const { return fsci_e_81; }
        Float_t Get_sci_x_81() const { return fsci_x_81; }
        Float_t Get_sci_tof_11_21() const { return fsci_tof_11_21; }
        Float_t Get_sci_tof_11_21_calib() const { return fsci_tof_11_21_calib; }
        Float_t Get_sci_tof_21_41() const { return fsci_tof_21_41; }
        Float_t Get_sci_tof_21_41_calib() const { return fsci_tof_21_41_calib; }
        Float_t Get_sci_tof_21_42() const { return fsci_tof_21_42; }
        Float_t Get_sci_tof_21_42_calib() const { return fsci_tof_21_42_calib; }
        Float_t Get_sci_tof_21_81() const { return fsci_tof_21_81; }
        Float_t Get_sci_tof_21_81_calib() const { return fsci_tof_21_81_calib; }
        Float_t Get_sci_tof_22_41() const { return fsci_tof_22_41; }
        Float_t Get_sci_tof_22_41_calib() const { return fsci_tof_22_41_calib; }
        Float_t Get_sci_tof_22_81() const { return fsci_tof_22_81; }
        Float_t Get_sci_tof_22_81_calib() const { return fsci_tof_22_81_calib; }
        Float_t Get_music21_dE() const { return fmusic21_dE; }
        Float_t Get_music22_dE() const { return fmusic22_dE; }
        Float_t Get_music41_dE() const { return fmusic41_dE; }
        Float_t Get_music42_dE() const { return fmusic42_dE; }
        Float_t Get_music43_dE() const { return fmusic43_dE; }
        Float_t Get_music21_dE_cor() const { return fmusic21_dE_cor; }
        Float_t Get_music22_dE_cor() const { return fmusic22_dE_cor; }
        Float_t Get_music41_dE_cor() const { return fmusic41_dE_cor; }
        Float_t Get_music42_dE_cor() const { return fmusic42_dE_cor; }
        Float_t Get_music43_dE_cor() const { return fmusic43_dE_cor; }
        Float_t Get_ID_x1() const { return fID_x1; }
        Float_t Get_ID_x2() const { return fID_x2; }
        Float_t Get_ID_x4() const { return fID_x4; }
        Float_t Get_ID_y1() const { return fID_y1; }
        Float_t Get_ID_y2() const { return fID_y2; }
        Float_t Get_ID_y4() const { return fID_y4; }
        Float_t Get_ID_a1() const { return fID_a1; }
        Float_t Get_ID_a2() const { return fID_a2; }
        Float_t Get_ID_a4() const { return fID_a4; }
        Float_t Get_ID_b1() const { return fID_b1; }
        Float_t Get_ID_b2() const { return fID_b2; }
        Float_t Get_ID_b4() const { return fID_b4; }
        Float_t Get_ID_beta_s1s2() const { return fID_beta_s1s2; }
        Float_t Get_ID_AoQ_s1s2() const { return fID_AoQ_s1s2; }
        Float_t Get_ID_AoQ_corr_s1s2() const { return fID_AoQ_corr_s1s2; }
        Float_t Get_ID_z21() const { return fID_z21; }
        Float_t Get_ID_z22() const { return fID_z22; }
        Float_t Get_ID_beta_s2s4() const { return fID_beta_s2s4; }
        Float_t Get_ID_AoQ_s2s4() const { return fID_AoQ_s2s4; }
        Float_t Get_ID_AoQ_corr_s2s4() const { return fID_AoQ_corr_s2s4; }
        Float_t Get_ID_z41() const { return fID_z41; }
        Float_t Get_ID_z42() const { return fID_z42; }
        Float_t Get_ID_z43() const { return fID_z43; }
        Float_t Get_ID_dEdegoQ() const { return fID_dEdegoQ; }
        Float_t Get_ID_dEdeg_z41() const { return fID_dEdeg_z41; }
        const Float_t (&Get_ID_rho() const) [4] { return fID_rho; }
        const Float_t (&Get_ID_brho() const) [4] { return fID_brho; }
        Float_t Get_FRS_time_mins() const { return FRS_time_mins; }
        Float_t Get_ID_AoQs1s2_driftcorr() const { return fID_AoQs1s2_driftcorr; } // should change
        Float_t Get_ID_AoQs2s4_driftcorr() const { return fID_AoQs2s4_driftcorr; } // should change
        Float_t Get_ID_z21_driftcorr() const { return fID_z21_driftcorr; }
        Float_t Get_ID_z22_driftcorr() const { return fID_z22_driftcorr; }
        Float_t Get_ID_z41_driftcorr() const { return fID_z41_driftcorr; }
        Float_t Get_ID_z42_driftcorr() const { return fID_z42_driftcorr; }
        Float_t Get_ID_z43_driftcorr() const { return fID_z43_driftcorr; }


        ClassDef(FrsHitItem, 1);

    private:

        // Meta
        Long64_t fwr_t;
        Short_t ftpat;
        TString setup_file;
        Long64_t ftravmus_wr_t;

        // Scaler
        Double_t ftime_in_ms;
        Double_t ftime_in_us;
        Int_t fibin_for_s;
        Int_t fibin_for_100ms;
        Int_t fibin_for_spill;
        Int_t fibin_clean_for_s;
        Int_t fibin_clean_for_100ms;
        Int_t fibin_clean_for_spill;
        Int_t fextraction_time_ms;
        Int_t fincrease_scaler_temp[67];

        // SCI
        Float_t fsci_e_11;
        Float_t fsci_x_11;
        Float_t fsci_e_21;
        Float_t fsci_x_21;
        Float_t fsci_e_22;
        Float_t fsci_x_22;
        Float_t fsci_e_31;
        Float_t fsci_e_41;
        Float_t fsci_x_41;
        Float_t fsci_e_42;
        Float_t fsci_x_42;
        Float_t fsci_e_43;
        Float_t fsci_x_43;
        Float_t fsci_e_81;
        Float_t fsci_x_81;
        Float_t fsci_tof_11_21;
        Float_t fsci_tof_11_21_calib;
        Float_t fsci_tof_21_41;
        Float_t fsci_tof_21_41_calib;
        Float_t fsci_tof_21_42;
        Float_t fsci_tof_21_42_calib;
        Float_t fsci_tof_21_81;
        Float_t fsci_tof_21_81_calib;
        Float_t fsci_tof_22_41;
        Float_t fsci_tof_22_41_calib;
        Float_t fsci_tof_22_81;
        Float_t fsci_tof_22_81_calib;

        // MUSIC
        Float_t fmusic21_dE;
        Float_t fmusic22_dE;
        Float_t fmusic41_dE;
        Float_t fmusic42_dE;
        Float_t fmusic43_dE;
        Float_t fmusic21_dE_cor;
        Float_t fmusic22_dE_cor;
        Float_t fmusic41_dE_cor;
        Float_t fmusic42_dE_cor;
        Float_t fmusic43_dE_cor;

        // IDs
        Float_t fID_x1;
        Float_t fID_y1;
        Float_t fID_a1;
        Float_t fID_b1;
        Float_t fID_x2;
        Float_t fID_y2;
        Float_t fID_x4;
        Float_t fID_y4;
        Float_t fID_a2;
        Float_t fID_b2;
        Float_t fID_a4;
        Float_t fID_b4;
        Float_t fID_beta_s1s2;
        Float_t fID_AoQ_s1s2;
        Float_t fID_AoQ_corr_s1s2;
        Float_t fID_z21;
        Float_t fID_z22;
        Float_t fID_beta_s2s4;
        Float_t fID_AoQ_s2s4;
        Float_t fID_AoQ_corr_s2s4;
        Float_t fID_z41;
        Float_t fID_z42;
        Float_t fID_z43;
        Float_t fID_dEdegoQ;
        Float_t fID_dEdeg_z41;
        Float_t fID_rho[4];
        Float_t fID_brho[4];

        // DriftCorrs
        Float_t FRS_time_mins;
        Float_t fID_AoQs1s2_driftcorr;
        Float_t fID_AoQs2s4_driftcorr;
        Float_t fID_z21_driftcorr;
        Float_t fID_z22_driftcorr;
        Float_t fID_z41_driftcorr;
        Float_t fID_z42_driftcorr;
        Float_t fID_z43_driftcorr;

};

class FrsMultiHitItem : public TObject
{
    public:
        FrsMultiHitItem();

        // vectors?
        void SetS1S2(std::vector<Float_t> s1x,
                    std::vector<Float_t> s1a,
                    std::vector<Float_t> s2x_s1s2,
                    std::vector<Float_t> s2a_s1s2,
                    std::vector<Float_t> tof_s1s2,
                    std::vector<Float_t> beta_s1s2,
                    std::vector<Float_t> AoQ_s1s2,
                    std::vector<Float_t> AoQ_corr_s1s2,
                    std::vector<Float_t> z21,
                    std::vector<Float_t> z22); // is there dEdeg ? 


        // vectors?
        void SetS2S4(std::vector<Float_t> s2x_s2s4,
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
                    std::vector<Float_t> dEdeg_z41);

        // void SetAll(Float_t s2x,
        //             Float_t s2a,
        //             Float_t s4x,
        //             Float_t s4a,
        //             Float_t tof,
        //             Float_t beta, 
        //             Float_t AoQ, 
        //             Float_t AoQ_corr, 
        //             Float_t z,
        //             Float_t z2,
        //             Float_t dEdeg,
        //             Float_t dEdegoQ);

        // Float_t Get_ID_s2x_mhtdc() const { return fID_s2x_mhtdc; }
        // Float_t Get_ID_s4x_mhtdc() const { return fID_s4x_mhtdc; }
        // Float_t Get_ID_s2a_mhtdc() const { return fID_s2a_mhtdc; }
        // Float_t Get_ID_s4a_mhtdc() const { return fID_s4a_mhtdc; }
        // Float_t Get_ID_tof_mhtdc() const { return fID_tof_mhtdc; }
        // Float_t Get_ID_beta_mhtdc() const { return fID_beta_mhtdc; }
        // Float_t Get_ID_AoQ_mhtdc() const { return fID_AoQ_mhtdc; }
        // Float_t Get_ID_AoQ_corr_mhtdc() const { return fID_AoQ_corr_mhtdc; }
        // Float_t Get_ID_z_mhtdc() const { return fID_z_mhtdc; }
        // Float_t Get_ID_z2_mhtdc() const { return fID_z2_mhtdc; }
        // Float_t Get_ID_dEdeg_mhtdc() const { return fID_dEdeg_mhtdc; }
        // Float_t Get_ID_dEdegoQ_mhtdc() const { return fID_dEdegoQ_mhtdc; }

        std::vector<Float_t> Get_ID_s1x_mhtdc() const { return fID_s1x_mhtdc; }
        std::vector<Float_t> Get_ID_s1a_mhtdc() const { return fID_s1a_mhtdc; }
        std::vector<Float_t> Get_ID_s2x_s1s2_mhtdc() const { return fID_s2x_s1s2_mhtdc; }
        std::vector<Float_t> Get_ID_s2a_s1s2_mhtdc() const { return fID_s2a_s1s2_mhtdc; }
        std::vector<Float_t> Get_ID_tof_s1s2_mhtdc() const { return fID_tof_s1s2_mhtdc; }
        std::vector<Float_t> Get_ID_beta_s1s2_mhtdc() const { return fID_beta_s1s2_mhtdc; }
        std::vector<Float_t> Get_ID_AoQ_s1s2_mhtdc() const { return fID_AoQ_s1s2_mhtdc; }
        std::vector<Float_t> Get_ID_AoQ_corr_s1s2_mhtdc() const { return fID_AoQ_corr_s1s2_mhtdc; }
        std::vector<Float_t> Get_ID_z21_mhtdc() const { return fID_z21_mhtdc; }
        std::vector<Float_t> Get_ID_z22_mhtdc() const { return fID_z22_mhtdc; }

        // S2S4
        std::vector<Float_t> Get_ID_s2x_s2s4_mhtdc() const { return fID_s2x_s2s4_mhtdc; }
        std::vector<Float_t> Get_ID_s2a_s2s4_mhtdc() const { return fID_s2a_s2s4_mhtdc; }
        std::vector<Float_t> Get_ID_s4x_mhtdc() const { return fID_s4x_mhtdc; }
        std::vector<Float_t> Get_ID_s4a_mhtdc() const { return fID_s4a_mhtdc; }
        std::vector<Float_t> Get_ID_tof_s2s4_mhtdc() const { return fID_tof_s2s4_mhtdc; }
        std::vector<Float_t> Get_ID_beta_s2s4_mhtdc() const { return fID_beta_s2s4_mhtdc; }
        std::vector<Float_t> Get_ID_AoQ_s2s4_mhtdc() const { return fID_AoQ_s2s4_mhtdc; }
        std::vector<Float_t> Get_ID_AoQ_corr_s2s4_mhtdc() const { return fID_AoQ_corr_s2s4_mhtdc; }
        std::vector<Float_t> Get_ID_z41_mhtdc() const { return fID_z41_mhtdc; }
        std::vector<Float_t> Get_ID_z42_mhtdc() const { return fID_z42_mhtdc; }
        std::vector<Float_t> Get_ID_z43_mhtdc() const { return fID_z43_mhtdc; }
        std::vector<Float_t> Get_ID_dEdegoQ_mhtdc() const { return fID_dEdegoQ_mhtdc; }
        std::vector<Float_t> Get_ID_dEdeg_z41_mhtdc() const { return fID_dEdeg_z41_mhtdc; }
      

        ClassDef(FrsMultiHitItem, 1);

    private:


        // S1S2
        std::vector<Float_t> fID_s1x_mhtdc;
        std::vector<Float_t> fID_s1a_mhtdc;
        std::vector<Float_t> fID_s2x_s1s2_mhtdc;
        std::vector<Float_t> fID_s2a_s1s2_mhtdc;
        std::vector<Float_t> fID_tof_s1s2_mhtdc;
        std::vector<Float_t> fID_beta_s1s2_mhtdc;
        std::vector<Float_t> fID_AoQ_s1s2_mhtdc;
        std::vector<Float_t> fID_AoQ_corr_s1s2_mhtdc;
        std::vector<Float_t> fID_z21_mhtdc;
        std::vector<Float_t> fID_z22_mhtdc;

        // S2S4
        std::vector<Float_t> fID_s2x_s2s4_mhtdc;
        std::vector<Float_t> fID_s2a_s2s4_mhtdc;
        std::vector<Float_t> fID_s4x_mhtdc;
        std::vector<Float_t> fID_s4a_mhtdc;
        std::vector<Float_t> fID_tof_s2s4_mhtdc;
        std::vector<Float_t> fID_beta_s2s4_mhtdc;
        std::vector<Float_t> fID_AoQ_s2s4_mhtdc;
        std::vector<Float_t> fID_AoQ_corr_s2s4_mhtdc;
        std::vector<Float_t> fID_z41_mhtdc;
        std::vector<Float_t> fID_z42_mhtdc;
        std::vector<Float_t> fID_z43_mhtdc;
        std::vector<Float_t> fID_dEdegoQ_mhtdc;
        std::vector<Float_t> fID_dEdeg_z41_mhtdc;

        // Float_t fID_s2x_mhtdc;
        // Float_t fID_s4x_mhtdc;
        // Float_t fID_s2a_mhtdc;
        // Float_t fID_s4a_mhtdc;
        // Float_t fID_tof_mhtdc;
        // Float_t fID_beta_mhtdc;
        // Float_t fID_AoQ_mhtdc;
        // Float_t fID_AoQ_corr_mhtdc;
        // Float_t fID_z_mhtdc;
        // Float_t fID_z2_mhtdc;
        // Float_t fID_dEdeg_mhtdc;
        // Float_t fID_dEdegoQ_mhtdc;

};

#endif 
