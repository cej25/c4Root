#ifndef FrsCal2Hit_H
#define FrsCal2Hit_H

#include "../../config/setup.h"
#include "FairTask.h"
#include "TFRSParameter.h"
#include "TClonesArray.h"
#include "FrsMainCalData.h"
#include "FrsTPCCalData.h"
#include "FrsUserCalData.h"
#include "FrsVFTXCalData.h"
#include "FrsTpatData.h"
#include "FrsHitData.h"
#include <TRandom3.h>

class TClonesArray;
class FrsMainCalData;
class FrsTPCCalData;
class FrsUserCalData;
class FrsVFTXCalData;
class FrsHitData;
class EventHeader;
class EventData;

class FrsCal2Hit : public FairTask
{
    public:
        FrsCal2Hit(TFRSParameter* ffrs,
                TMWParameter* fmw,
                TTPCParameter* ftpc,
                TMUSICParameter* fmusic,
                TLABRParameter* flabr,
                TSCIParameter* fsci,
                TIDParameter* fid,
                TSIParameter* fsi,
                TMRTOFMSParameter* fmrtof,
                TRangeParameter* frange,
                TString& fExpName);

        FrsCal2Hit(const TString& name, Int_t verbose);

        virtual ~FrsCal2Hit();
        
        virtual InitStatus Init();
        virtual InitStatus ReInit();

        virtual void Exec(Option_t* option); // virtual?
        
        virtual void SetParContainers();
        void Setup_Conditions(TString path_to_folder_with_frs_config_files);
        void FRS_GainMatching();

        Bool_t Check_WinCond(Float_t P, Float_t* V);
        Bool_t Check_WinCond_Multi(Float_t P, Float_t V[8][2], int cond_num);

        Float_t rand3();

        void ZeroArrays();
        void ZeroVariables();
        void ClearVectors();

        void FinishEvent();
        void FinishTask();
        
        
        void SetOnline(Bool_t option) { fOnline = option; }
    
    private:

        Bool_t fOnline;
        TString expName;

        TClonesArray* fCalArrayMain;
        TClonesArray* fCalArrayTPC;
        TClonesArray* fCalArrayUser;
        TClonesArray* fCalArrayVFTX;
        TClonesArray* fRawArrayTpat;
        TClonesArray* fHitArray;
        TClonesArray* fEventItems;

        FrsTpatData* fRawHitTpat;
        FrsMainCalData* fCalHitMain;
        FrsTPCCalData* fCalHitTPC;
        FrsUserCalData* fCalHitUser;
        FrsVFTXCalData* fCalHitVFTX;
        FrsHitData* fFrsHit;
        //EventData* EventItem;

        Bool_t prevSpillOn = false;

        /* ----------------------------------------------- */
        // Intermediate variables
        /* ----------------------------------------------- */
        
        /* Setup variables */
        Float_t lim_csum[4][7][2];
        Float_t lim_xsum[13][2];
        Float_t lim_ysum[13][2];
        Float_t cMusic1_E[8][2];
        Float_t cMusic2_E[8][2];
        Float_t cMusic3_E[4][2];
        Float_t cMusic1_T[8][2];
        Float_t cMusic2_T[8][2];
        Float_t cMusic3_T[4][2];
        Float_t cMusic3_dec[2];
        Float_t cSCI_L[2];
        Float_t cSCI_R[2];
        Float_t cSCI_E[2];
        Float_t cSCI_Tx[2];
        Float_t cSCI_X[2];
        Float_t cSCI_LL2[2];
        Float_t cSCI_RR2[2];
        Float_t cSCI_LL3[2];
        Float_t cSCI_RR3[2];
        Float_t cSCI_LL4[2];
        Float_t cSCI_RR4[2];
        Float_t cSCI_LL5[2];
        Float_t cSCI_RR5[2];
        Float_t cID_x2[2];
        Float_t cID_x4[2];
        Float_t cID_Z_Z[2];

        uint32_t v830_n_main; // needed?
        uint32_t v830_n_user; // needed?
        std::vector<uint32_t> v830_index_main; // needed?
        std::vector<uint32_t> v830_index_user; // needed?
        std::vector<uint32_t> v830_scalers_main;
        std::vector<uint32_t> v830_scalers_user;
        
        uint32_t scaler_check_first_event = 1;
        uint32_t scaler_ch_1kHz = 7; // main
        uint32_t scaler_ch_spillstart = 8; // user (goes into sc_long first in go4)
        uint32_t sc_main_initial[32] = {0};
        uint32_t sc_main_previous[32] = {0};
        uint32_t sc_user_initial[32] = {0};
        uint32_t sc_user_previous[32] = {0};
        uint32_t increase_sc_temp_main[32] = {0}; // main?
        uint32_t increase_sc_temp_user[32] = {0};

        uint32_t time_in_ms;
        uint32_t ibin_for_s;
        uint32_t ibin_for_100ms;
        uint32_t increase_sc_temp2 = 0;
        uint32_t increase_sc_temp3 = 0;
        uint32_t extraction_time_ms;
        uint32_t ibin_clean_for_s;
        uint32_t ibin_clean_for_100ms;
        uint32_t ibin_for_spill;
        uint32_t ibin_clean_for_spill;
        uint32_t spill_count;

        const uint32_t* music_e1;
        const uint32_t* music_e2;
        const uint32_t* music_t1;
        const uint32_t* music_t2;

        Int_t music1_anodes_cnt;
	    Int_t music2_anodes_cnt;

        Bool_t music_b_e1[8];
        Bool_t music_b_e2[8];
        Bool_t music_b_t1[8];
        Bool_t music_b_t2[8];
        Bool_t b_de1;
	    Bool_t b_de2;
        Float_t music1_x_mean;
        Float_t music2_x_mean;

        std::vector<uint32_t> tdc_array[15];
        uint32_t de_array[14];
        const uint32_t* dt_array; // not coded in raw->cal yet
        Float_t de[3];
        Float_t de_cor[3];
        uint32_t sci_l[6]; // may change when i know the actual dimensions necessary
        uint32_t sci_r[6];
        uint32_t sci_tx[6];
        uint32_t sci_e[6];
        uint32_t sci_x[6];
        Bool_t sci_b_l[12]; // size may be reduced
        Bool_t sci_b_r[12]; // size may be reduced
        Bool_t sci_b_e[12]; // size may be reduced
        Bool_t sci_b_tx[12]; // size may be reduced
        Bool_t sci_b_x[12]; // size may be reduced
        const Bool_t* b_tpc_xy; //Bool_t b_tpc_xy[7];
        Bool_t b_tpc_de[7];
        Bool_t b_tpc_timeref[8];
        Bool_t b_tpc_csum[7][4];
        Float_t tpc_x_s4;
        Float_t tpc_y_s4;
        Float_t tpc_angle_x_s4;
        Float_t tpc_angle_y_s4;
        Bool_t id_b_x2;
        Bool_t id_b_x4;
        Bool_t id_b_AoQ;
        Bool_t id_b_z;
        Bool_t id_b_z2;
        Bool_t id_b_z3;
        int Z_Shift_array;
        Float_t FRS_WR_a[200];
        Float_t FRS_WR_b[200];
        Float_t Z1_shift_value[200];
        Float_t Z2_shift_value[200];
        int AoQ_Shift_array;
        Float_t FRS_WR_i[200];
        Float_t FRS_WR_j[200];
        Float_t AoQ_shift_value[200];
        Float_t AoQ_shift_TPC_value[200];
        Float_t AoQ_shift_Sci21_value[200];
        Float_t AoQ_shift_Sci22_value[200];
        Int_t ts_mins;

        std::vector<Float_t> mhtdc_sc21lr_dt;
        std::vector<Float_t> mhtdc_sc22lr_dt;
        Float_t mhtdc_sc31lr_dt;
        Float_t mhtdc_sc41lr_dt;
        Float_t mhtdc_sc42lr_dt;
        Float_t mhtdc_sc43lr_dt;
        Float_t mhtdc_sc81lr_dt;
        
        std::vector<Float_t> mhtdc_sc21lr_x;
        std::vector<Float_t> mhtdc_sc22lr_x;
        Float_t mhtdc_sc31lr_x;
        Float_t mhtdc_sc41lr_x;
        Float_t mhtdc_sc42lr_x;
        Float_t mhtdc_sc43lr_x;
        Float_t mhtdc_sc81lr_x;

        std::vector<Float_t> mhtdc_tof4121;
        std::vector<Float_t> mhtdc_tof4122;
        Float_t mhtdc_tof4221;
        Float_t mhtdc_tof4321;
        Float_t mhtdc_tof3121;
        Float_t mhtdc_tof8121;

        Int_t dt_21l_21r;
        Int_t dt_41l_41r;
        Int_t dt_42l_42r;
        Int_t dt_43l_43r;
        Int_t dt_81l_81r;
        Int_t dt_21l_41l;
        Int_t dt_21r_41r;
        Int_t dt_42r_21r;
        Int_t dt_42l_21l;
        Int_t dt_21l_81l;
        Int_t dt_21r_81r;
        Int_t dt_22l_22r;
        Int_t dt_22l_41l;
        Int_t dt_22r_41r;
        Int_t dt_22l_81l;
        Int_t dt_22r_81r;

        Float_t sci_tofll2;
        Float_t sci_tofrr2;
        Float_t sci_tof2;
        Float_t sci_tof2_calib;
        Float_t sci_tofll3;
        Float_t sci_tofrr3;
        Float_t sci_tof3;
        Float_t sci_tof3_calib;
        Float_t sci_tofll4;
        Float_t sci_tofrr4;
        Float_t sci_tof4;
        Float_t sci_tof4_calib;
        Float_t sci_tofll5;
        Float_t sci_tofrr5;
        Float_t sci_tof5;
        Float_t sci_tof5_calib;
        Bool_t sci_b_tofll2;
        Bool_t sci_b_tofrr2;
        Bool_t sci_b_tofll3;
        Bool_t sci_b_tofrr3;
        Bool_t sci_b_tofll4;
        Bool_t sci_b_tofrr4;
        Bool_t sci_b_tofll5;
        Bool_t sci_b_tofrr5;

        float temp_s4x; // i think this gets redeclared a bunch.

        std::vector<Float_t> id_mhtdc_beta_s2s4;
        std::vector<Float_t> id_mhtdc_gamma_s2s4;
        std::vector<Float_t> id_mhtdc_delta_s2s4; // not sure this needs to be a vector
        std::vector<Float_t> id_mhtdc_aoq_s2s4;
        std::vector<Float_t> id_mhtdc_aoq_corr_s2s4;
        std::vector<Float_t> id_mhtdc_z_music41;
        std::vector<Float_t> id_mhtdc_zcor_music41;
        std::vector<Float_t> id_mhtdc_v_cor_music41;
        std::vector<Float_t> id_mhtdc_z_music42;
        std::vector<Float_t> id_mhtdc_zcor_music42;
        std::vector<Float_t> id_mhtdc_v_cor_music42;

        std::vector<Float_t> id_mhtdc_dEdegoQ;
        std::vector<Float_t> id_mhtdc_gamma_ta_s2;
        std::vector<Float_t> mhtdc_gamma1square;
        std::vector<Float_t> id_mhtdc_dEdeg;
        
        float speed_light = 0.299792458; //m/ns
        float temp_tm_to_MeV = 299.792458;
        float temp_mu = 931.4940954; //MeV

        const std::vector<uint32_t>* TRaw_vftx;

        std::vector<Float_t> vftx_tof2141;
        std::vector<Float_t> vftx_tof2141_calib;
        std::vector<Float_t> vftx_tof2241;
        std::vector<Float_t> vftx_tof2241_calib;
        std::vector<Float_t> vftx_tof2142;
        std::vector<Float_t> vftx_tof2142_calib;
        std::vector<Float_t> vftx_tof2242;
        std::vector<Float_t> vftx_tof2242_calib;

        std::vector<Float_t> id_vftx_beta_2141;
        std::vector<Float_t> id_vftx_gamma_2141;
        std::vector<Float_t> id_vftx_aoq_2141;
        std::vector<Float_t> id_vftx_aoq_corr_2141;
        std::vector<Float_t> id_vftx_z_2141;
        std::vector<Float_t> id_vftx_z2_2141;
        std::vector<Float_t> id_vftx_vcor_2141;
        std::vector<Float_t> id_vftx_beta_2241;
        std::vector<Float_t> id_vftx_gamma_2241;
        std::vector<Float_t> id_vftx_aoq_2241;
        std::vector<Float_t> id_vftx_aoq_corr_2241;
        std::vector<Float_t> id_vftx_z_2241;
        std::vector<Float_t> id_vftx_z2_2241;
        std::vector<Float_t> id_vftx_vcor_2241;
        std::vector<Float_t> id_vftx_beta_2142;
        std::vector<Float_t> id_vftx_gamma_2142;
        std::vector<Float_t> id_vftx_aoq_2142;
        std::vector<Float_t> id_vftx_aoq_corr_2142;
        std::vector<Float_t> id_vftx_z_2142;
        std::vector<Float_t> id_vftx_z2_2142;
        std::vector<Float_t> id_vftx_vcor_2142;
        std::vector<Float_t> id_vftx_beta_2242;
        std::vector<Float_t> id_vftx_gamma_2242;
        std::vector<Float_t> id_vftx_aoq_2242;
        std::vector<Float_t> id_vftx_aoq_corr_2242;
        std::vector<Float_t> id_vftx_z_2242;
        std::vector<Float_t> id_vftx_z2_2242;
        std::vector<Float_t> id_vftx_vcor_2242;
        Float_t id_vftx_delta_24;

        Double_t power;
        Double_t sum;
        Double_t Corr;

        TRandom3 random3;

        /* ----------------------------------------------- */
        //Hit variables
        /* ----------------------------------------------- */
        uint64_t WR_TS;

        Float_t id_x2;
        Float_t id_y2;
        Float_t id_a2;
        Float_t id_b2;
        Float_t id_x4;
        Float_t id_y4;
        Float_t id_a4;
        Float_t id_b4;
        Float_t id_x8;
        Float_t id_y8;
        Float_t id_a8;
        Float_t id_b8;
        Float_t id_rho[2];
        Float_t id_brho[2];
        Float_t id_beta;
        Float_t id_gamma;
        Float_t id_AoQ;
        Float_t id_AoQ_corr;
        Float_t id_v_cor;
        Float_t id_v_cor2;
        Float_t id_v_cor3;
        Float_t id_z;
        Float_t id_z2;
        Float_t id_z3;
        Float_t id_gamma_ta_s2;
        Float_t id_dEdegoQ;
        Float_t id_dEdeg;

        Float_t aoq_factor = 931.4940 / 299.792458; // 'f' in go4 code

        // parameters from FRS setup
        TFRSParameter* frs;
        TMWParameter* mw;
        TTPCParameter* tpc;
        TMUSICParameter* music;
        TLABRParameter* labr;
        TSCIParameter* sci;
        TIDParameter* id;
        TSIParameter* si;
        TMRTOFMSParameter* mrtof;
        TRangeParameter* range;

        EventHeader* header;
        Int_t fNEvents = 0;

        bool conditions_files_read = false;

        // analysis stuff..

    public:
        ClassDef(FrsCal2Hit, 1);

};

#endif