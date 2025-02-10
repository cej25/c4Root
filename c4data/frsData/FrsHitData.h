#ifndef FrsHitData_H
#define FrsHitData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

typedef Int_t Int_t;
typedef Float_t Float_t;

// to be renamed as FrsHitItem
class FrsHitItem : public TObject
{
    public:
        FrsHitItem();

        void SetMetaData(Long64_t wr_t, Short_t tpat);

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

        void SetSciData(Float_t sci_e_21,
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
                        Float_t sci_tof_22_81_calib);

        void SetMusicData(Float_t music_dE[2], Float_t music_dE_cor[2]);
        
        void SetIDs(Float_t x2,
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
                    Float_t brho[2]);

        void SetDriftCorrections(Float_t FRS_time, 
                                Float_t AoQ_driftcorr, 
                                Float_t z_driftcorr);


        Long64_t Get_wr_t() const { return fwr_t; }
        Short_t Get_tpat() const { return ftpat; }
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
        const Float_t (&Get_music_dE() const) [2] { return fmusic_dE; }
        const Float_t (&Get_music_dE_cor() const) [2] { return fmusic_dE_cor; }
        Float_t Get_ID_x2() const { return fID_x2; }
        Float_t Get_ID_y2() const { return fID_y2; }
        Float_t Get_ID_x4() const { return fID_x4; }
        Float_t Get_ID_y4() const { return fID_y4; }
        Float_t Get_ID_a2() const { return fID_a2; }
        Float_t Get_ID_b2() const { return fID_b2; }
        Float_t Get_ID_a4() const { return fID_a4; }
        Float_t Get_ID_b4() const { return fID_b4; }
        Float_t Get_ID_AoQ() const { return fID_AoQ; }
        Float_t Get_ID_AoQ_corr() const { return fID_AoQ_corr; }
        Float_t Get_ID_z() const { return fID_z; }
        Float_t Get_ID_z2() const { return fID_z2; }
        Float_t Get_ID_beta() const { return fID_beta; }
        Float_t Get_ID_dEdeg() const { return fID_dEdeg; }
        Float_t Get_ID_dEdegoQ() const { return fID_dEdegoQ; }
        const Float_t (&Get_ID_rho() const) [2] { return fID_rho; }
        const Float_t (&Get_ID_brho() const) [2] { return fID_brho; }
        Float_t Get_FRS_time_mins() const { return FRS_time_mins; }
        Float_t Get_ID_AoQ_driftcorr() const { return fID_AoQ_driftcorr; }
        Float_t Get_ID_z_driftcorr() const { return fID_z_driftcorr; }


        ClassDef(FrsHitItem, 1);

    private:

        // Meta
        Long64_t fwr_t;
        Short_t ftpat;

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
        Float_t fmusic_dE[2];
        Float_t fmusic_dE_cor[2];

        // IDs
        Float_t fID_x2;
        Float_t fID_y2;
        Float_t fID_x4;
        Float_t fID_y4;
        Float_t fID_a2;
        Float_t fID_b2;
        Float_t fID_a4;
        Float_t fID_b4;
        Float_t fID_AoQ;
        Float_t fID_AoQ_corr;
        Float_t fID_z;
        Float_t fID_z2;
        Float_t fID_beta;
        Float_t fID_dEdeg;
        Float_t fID_dEdegoQ;
        Float_t fID_rho[2];
        Float_t fID_brho[2];

        // DriftCorrs
        Float_t FRS_time_mins;
        Float_t fID_AoQ_driftcorr;
        Float_t fID_z_driftcorr;

};

class FrsMultiHitItem : public TObject
{
    public:
        FrsMultiHitItem();

        void SetAll(
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
                    Float_t dEdegoQ);
        
        void SetMetaData(Long64_t wr_t, Short_t tpat);

        Float_t Get_wr_t() const { return fwr_t; }
        Float_t Get_ID_s2x_mhtdc() const { return fID_s2x_mhtdc; }
        Float_t Get_ID_s4x_mhtdc() const { return fID_s4x_mhtdc; }
        Float_t Get_ID_s2a_mhtdc() const { return fID_s2a_mhtdc; }
        Float_t Get_ID_s4a_mhtdc() const { return fID_s4a_mhtdc; }
        Float_t Get_ID_tof_mhtdc() const { return fID_tof_mhtdc; }
        Float_t Get_ID_beta_mhtdc() const { return fID_beta_mhtdc; }
        Float_t Get_ID_AoQ_mhtdc() const { return fID_AoQ_mhtdc; }
        Float_t Get_ID_AoQ_corr_mhtdc() const { return fID_AoQ_corr_mhtdc; }
        Float_t Get_ID_z_mhtdc() const { return fID_z_mhtdc; }
        Float_t Get_ID_z2_mhtdc() const { return fID_z2_mhtdc; }
        Float_t Get_ID_dEdeg_mhtdc() const { return fID_dEdeg_mhtdc; }
        Float_t Get_ID_dEdegoQ_mhtdc() const { return fID_dEdegoQ_mhtdc; }
      

        ClassDef(FrsMultiHitItem, 1);

    private:
        
        Long64_t fwr_t; 
        Short_t ftpat;
        Float_t fID_s2x_mhtdc;
        Float_t fID_s4x_mhtdc;
        Float_t fID_s2a_mhtdc;
        Float_t fID_s4a_mhtdc;
        Float_t fID_tof_mhtdc;
        Float_t fID_beta_mhtdc;
        Float_t fID_AoQ_mhtdc;
        Float_t fID_AoQ_corr_mhtdc;
        Float_t fID_z_mhtdc;
        Float_t fID_z2_mhtdc;
        Float_t fID_dEdeg_mhtdc;
        Float_t fID_dEdegoQ_mhtdc;

};

#endif 
