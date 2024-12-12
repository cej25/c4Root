#ifndef FrsAnaData_H
#define FrsAnaData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>
//#include <Rtypes.h>


class FrsAnaItem : public TObject
{
    public:
        FrsAnaItem();

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



        ClassDef(FrsAnaItem, 1);

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

class FrsAnaMultiItem : public TObject
{
    public:
        FrsAnaMultiItem();

        void SetAll(Float_t s2x,
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

        Float_t Get_ID_s2x_mhtdc() const;
        Float_t Get_ID_s4x_mhtdc() const;
        Float_t Get_ID_s2a_mhtdc() const;
        Float_t Get_ID_s4a_mhtdc() const;
        Float_t Get_ID_tof_mhtdc() const;
        Float_t Get_ID_beta_mhtdc() const;
        Float_t Get_ID_AoQ_mhtdc() const;
        Float_t Get_ID_AoQ_corr_mhtdc() const;
        Float_t Get_ID_z_mhtdc() const;
        Float_t Get_ID_z2_mhtdc() const;
        Float_t Get_ID_dEdeg_mhtdc() const;
        Float_t Get_ID_dEdegoQ_mhtdc() const;
      

        ClassDef(FrsAnaMultiItem, 1);

    private:

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