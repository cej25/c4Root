#ifndef FrsCal2Hit_H
#define FrsCal2Hit_H

#include "TFrsConfiguration.h"
#include "TExperimentConfiguration.h"
#include "TFRSParameter.h"
#include "FrsData.h"
#include "FrsCalData.h"
#include "FrsHitData.h"
#include "EventHeader.h"
#include "GainShift.h"

#include "FairTask.h"
#include <TRandom3.h>
#include "TClonesArray.h"

class TClonesArray;
class FrsHitItem;
class EventHeader;
class TFrsConfiguration;
class TExperimentConfiguration;

class FrsCal2Hit : public FairTask
{
    public:
        FrsCal2Hit();

        FrsCal2Hit(const TString& name, Int_t verbose);

        virtual ~FrsCal2Hit();
        
        virtual InitStatus Init();

        virtual void Exec(Option_t* option); // virtual?

        void ProcessScalers();
        void ProcessSci_TAC();
        void ProcessSci_MHTDC();
        void ProcessMusic();
    
        void ProcessIDs();
        void ProcessIDs_MHTDC();
        void ProcessDriftCorrections();

        Float_t rand3();

        void FinishEvent();
        void FinishTask();


        void SetMusic41TACGainShift(GainShift * p) {music41_tac_z_gain_shifts = p;}
        void SetMusic42TACGainShift(GainShift * p) {music42_tac_z_gain_shifts = p;}
        
        void SetMusic41MHTDCGainShift(GainShift * p) {music41_mhtdc_z_gain_shifts = p;}
        void SetMusic42MHTDCGainShift(GainShift * p) {music42_mhtdc_z_gain_shifts = p;}
        
        
        void SetOnline(Bool_t option) { fOnline = option; }
    
    private:

        TFrsConfiguration const* frs_config;
        TExperimentConfiguration const* exp_config;
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
        std::string pathToConfigFiles;


        GainShift * music41_tac_z_gain_shifts = nullptr;
        GainShift * music42_tac_z_gain_shifts = nullptr;

        GainShift * music41_mhtdc_z_gain_shifts = nullptr;
        GainShift * music42_mhtdc_z_gain_shifts = nullptr;

        Bool_t fOnline;
        Int_t fNEvents;
        EventHeader* header;
        int total_time_microsecs = 0;

        bool conditions_files_read = false;

        std::vector<FrsTpatItem> const* tpatArray;
        std::vector<FrsScalerItem> const* scalerArray;
        std::vector<FrsCalSciItem> const* calSciArray;
        std::vector<FrsCalMusicItem> const* calMusicArray;
        std::vector<FrsCalTpcItem> const* calTpcArray;
        std::vector<FrsHitItem>* hitArray;
        std::vector<FrsMultiHitItem>* multihitArray;

        Float_t FRS_time_mins = 0;
        Long64_t wr_t = 0;
        Short_t tpat = 0;

        // Dummy variables and arrays
        // ::: Scalers ::::: //
        UInt_t scaler_current[67];
        UInt_t scaler_previous[67];
        UInt_t scaler_increment[67];
        UInt_t scaler_cumulative[67];
        Bool_t scaler_increment_calculated[67];
        Int_t scaler_check_first_event = 1;
        Int_t increase_scaler_temp[67];
        Int_t scaler_temp_free_for_100s = 0;
        Int_t scaler_temp_accept_for_100s = 0;
        Int_t scaler_temp_SCI41L_for_100s = 0;
        Int_t scaler_temp_SCI42L_for_100s = 0;
        Int_t scaler_temp_SCI43L_for_100s = 0;
        Int_t scaler_temp_free_for_s = 0;
        Int_t scaler_temp_accept_for_s = 0;
        Int_t scaler_temp_SCI41L_for_s = 0;
        Int_t scaler_temp_SCI42L_for_s = 0;
        Int_t scaler_temp_SCI43L_for_s = 0;
        Int_t scaler_temp_free_for_100ms = 0;
        Int_t scaler_temp_accept_for_100ms = 0;
        Int_t scaler_temp_SCI41L_for_100ms = 0;
        Int_t scaler_temp_SCI42L_for_100ms = 0;
        Int_t scaler_temp_SCI43L_for_100ms = 0;
        Int_t scaler_temp_free_for_spill = 0;
        Int_t scaler_temp_accept_for_spill = 0;
        Int_t scaler_temp_SCI41L_for_spill = 0;
        Int_t scaler_temp_SCI42L_for_spill = 0;
        Int_t scaler_temp_SCI43L_for_spill = 0;
        Double_t time_in_ms = 0.;
        Double_t time_in_us = 0.;
        Int_t scaler_ch_spillstart = 8; // these channels should be mapped imo
        Int_t scaler_ch_1kHz = 39;
        Int_t scaler_ch_100kHz = 38;
        Int_t scaler_ch_1000kHz = 62;
        Int_t extraction_time_ms = 0;
        Int_t ibin_for_100s = 0;
        Int_t ibin_for_s = 0;
        Int_t ibin_for_100ms = 0;
        Int_t ibin_for_spill = 0;
        Int_t ibin_clean_for_100s = 0;
        Int_t ibin_clean_for_s = 0;
        Int_t ibin_clean_for_100ms = 0;
        Int_t ibin_clean_for_spill = 0;
        Int_t ibin_for_100s_previous = 0;
        Int_t ibin_for_s_previous = 0;
        Int_t ibin_for_100ms_previous = 0;
        Int_t ibin_for_spill_previous = 0;
        Int_t tpat2_counter = 0;
        Int_t ratio_product_for_100s = 0;
        Int_t ratio_product2_for_100s = 0;
        Int_t ratio_product3_for_100s = 0;
        Int_t ratio_product_for_s = 0;
        Int_t ratio_product2_for_s = 0;
        Int_t ratio_product3_for_s = 0;
        Int_t ratio_product_for_100ms = 0;
        Int_t ratio_product2_for_100ms = 0;
        Int_t ratio_product3_for_100ms = 0;

        // ::: SCI TAC :::::: //
        UInt_t de_11l = 0;
        UInt_t de_11r = 0;
        UInt_t de_21l = 0;
        UInt_t de_21r = 0;
        UInt_t de_22l = 0;
        UInt_t de_22r = 0;
        UInt_t de_31l = 0;
        UInt_t de_31r = 0;
        UInt_t de_41l = 0;
        UInt_t de_41r = 0;
        UInt_t de_42l = 0;
        UInt_t de_42r = 0;
        UInt_t de_43l = 0;
        UInt_t de_43r = 0;
        UInt_t de_81l = 0;
        UInt_t de_81r = 0;

        Float_t sci_e_11 = 0.;
        Float_t sci_tx_11lr = 0.;
        Float_t sci_x_11 = -999.;
        Bool_t sci_b_x_11 = false;
        Float_t sci_e_21 = 0.;
        Float_t sci_tx_21lr = 0.;
        Float_t sci_x_21 = -999.;
        Bool_t sci_b_x_21 = false;
        Float_t sci_e_22 = 0.;
        Float_t sci_tx_22lr = 0.;
        Float_t sci_x_22 = -999.;
        Bool_t sci_b_x_22 = false;
        Float_t sci_e_31 = 0.;
        Float_t sci_e_41 = 0.;
        Float_t sci_tx_41lr = -999.;
        Float_t sci_x_41 = -999.;
        Bool_t sci_b_x_41 = false;
        Float_t sci_e_42 = 0.;
        Float_t sci_tx_42lr = 0.;
        Float_t sci_x_42 = -999.;
        Bool_t sci_b_x_42 = false;
        Float_t sci_e_43 = 0.;
        Float_t sci_tx_43lr = 0.;
        Float_t sci_x_43 = -999.;
        Bool_t sci_b_x_43 = false;
        Float_t sci_e_81 = 0.;
        Float_t sci_tx_81lr = 9.;
        Float_t sci_x_81 = -999.;
        Bool_t sci_b_x_81 = false;

        Float_t sci_tofll_11_21 = 0.;
        Float_t sci_tofrr_11_21 = 0.;
        Bool_t sci_b_tofll_11_21 = false;
        Bool_t sci_b_tofrr_11_21 = false;
        Float_t sci_tof_11_21 = 0.;
        Float_t sci_tof_11_21_calib = 0.;
        Float_t sci_tofll_21_41 = 0.;
        Float_t sci_tofrr_21_41 = 0.;
        Bool_t sci_b_tofll_21_41 = false;
        Bool_t sci_b_tofrr_21_41 = false;
        Float_t sci_tof_21_41 = 0.;
        Float_t sci_tof_21_41_calib = 0.;
        Float_t sci_tofll_21_42 = 0.;
        Float_t sci_tofrr_21_42 = 0.;
        Bool_t sci_b_tofll_21_42 = false;
        Bool_t sci_b_tofrr_21_42 = false;
        Float_t sci_tof_21_42 = 0.;
        Float_t sci_tof_21_42_calib = 0.;
        Float_t sci_tofll_21_81 = 0.;
        Float_t sci_tofrr_21_81 = 0.;
        Float_t sci_tof_21_81 = 0.;
        Float_t sci_tof_21_81_calib = 0.;
        Float_t sci_tofll_22_41 = 0.;
        Float_t sci_tofrr_22_41 = 0.;
        Bool_t sci_b_tofll_22_41 = false;
        Bool_t sci_b_tofrr_22_41 = false;
        Float_t sci_tof_22_41 = 0.;
        Float_t sci_tof_22_41_calib = 0.;
        Float_t sci_tofll_22_81 = 0.;
        Float_t sci_tofrr_22_81 = 0.;
        Float_t sci_tof_22_81 = 0.;
        Float_t sci_tof_22_81_calib = 0.;

        // ::: SCI MHTDC ::: //
        Int_t hits_in_11lr = 0;
        Int_t hits_in_21lr = 0;
        Int_t hits_in_22lr = 0;
        Int_t hits_in_41lr = 0;
        Int_t hits_in_42lr = 0;
        Int_t hits_in_tof2111 = 0;
        Int_t hits_in_tof4121 = 0;
        Int_t hits_in_tof4122 = 0;
        Int_t hits_in_tof4221 = 0;

        Int_t hits_in_s1x = 0;
        Int_t hits_in_s2x = 0;
        Int_t hits_in_s4x = 0;
        Int_t hits_in_s1s2 = 0;
        Int_t hits_in_s2s4 = 0;

        Float_t temp_a1;
        Float_t temp_a2;
        Float_t temp_a4;

        //std::vector<Int_t> 
        std::vector<Int_t> sci11l_hits;
        std::vector<Int_t> sci11r_hits;
        std::vector<Int_t> sci21l_hits;
        std::vector<Int_t> sci21r_hits;
        std::vector<Int_t> sci22l_hits;
        std::vector<Int_t> sci22r_hits;
        std::vector<Int_t> sci31l_hits;
        std::vector<Int_t> sci31r_hits;
        std::vector<Int_t> sci41l_hits;
        std::vector<Int_t> sci41r_hits;
        std::vector<Int_t> sci42l_hits;
        std::vector<Int_t> sci42r_hits;
        std::vector<Int_t> sci43l_hits;
        std::vector<Int_t> sci43r_hits;
        std::vector<Int_t> sci81l_hits;
        std::vector<Int_t> sci81r_hits;

        // it is encouraged that these become vectors, 
        // so perhaps in the future.
        Float_t* mhtdc_sc11lr_dt = nullptr;
        Float_t* mhtdc_sc21lr_dt = nullptr;
        Float_t* mhtdc_sc22lr_dt = nullptr;
        Float_t* mhtdc_sc41lr_dt = nullptr;
        Float_t* mhtdc_sc31lr_dt = nullptr;
        Float_t* mhtdc_sc42lr_dt = nullptr;
        Float_t* mhtdc_sc43lr_dt = nullptr;
        Float_t* mhtdc_sc81lr_dt = nullptr;

        Float_t* mhtdc_sc11lr_x = nullptr;
        Float_t* mhtdc_sc21lr_x = nullptr;
        Float_t* mhtdc_sc22lr_x = nullptr;
        Float_t* mhtdc_sc41lr_x = nullptr;
        Float_t* mhtdc_sc31lr_x = nullptr;
        Float_t* mhtdc_sc81lr_x = nullptr;
        Float_t* mhtdc_sc42lr_x = nullptr;
        Float_t* mhtdc_sc43lr_x = nullptr;
        Float_t* mhtdc_tof2111 = nullptr;
        Float_t* mhtdc_tof2211 = nullptr;
        Float_t* mhtdc_tof4121 = nullptr;
        Float_t* mhtdc_tof4122 = nullptr;
        Float_t* mhtdc_tof4221 = nullptr;
        Float_t* mhtdc_tof4321 = nullptr;
        Float_t* mhtdc_tof8121 = nullptr;
        Float_t* mhtdc_tof3121 = nullptr;

        Float_t temp_s4x = -999.;
        Float_t* temp_s1x_mhtdc = nullptr;
        Float_t* temp_s2x_mhtdc = nullptr;
        Float_t* temp_s4x_mhtdc = nullptr;
        Float_t temp_s8x_mhtdc = 0;


        // ::: MUSIC ::: //
        Int_t music21_anodes_cnt = 0;
        Int_t music22_anodes_cnt = 0;
        Int_t music41_anodes_cnt = 0;
        Int_t music42_anodes_cnt = 0;
        Int_t music43_anodes_cnt = 0;
        const UInt_t* music21_e;
        const UInt_t* music22_e;
        const UInt_t* music41_e;
        const UInt_t* music42_e;
        const UInt_t* music43_e;
        Bool_t music21_b_e[8];
        Bool_t music22_b_e[8];
        Bool_t music41_b_e[8];
        Bool_t music42_b_e[8];
        Bool_t music43_b_e[8];
        Bool_t music21_b_t[8];
        Bool_t music22_b_t[8];
        Bool_t music41_b_t[8];
        Bool_t music42_b_t[8];
        Bool_t music43_b_t[8];
        Float_t music21_de = 0;
        Float_t music22_de = 0;
        Float_t music41_de = 0;
        Float_t music42_de = 0;
        Float_t music43_de = 0;
        Float_t music21_de_cor = 0;
        Float_t music22_de_cor = 0;
        Float_t music41_de_cor = 0;
        Float_t music42_de_cor = 0;
        Float_t music43_de_cor = 0;
        Bool_t b_music21de = false;
        Bool_t b_music22de = false;
        Bool_t b_music41de = false;
        Bool_t b_music42de = false;
        Bool_t b_music43de = false;

        Float_t music21_x_mean = 0;
        Float_t music22_x_mean = 0;
        Float_t music41_x_mean = 0;
        Float_t music42_x_mean = 0;
        Float_t music43_x_mean = 0;


        // ::: TPCs ::: //
        const Bool_t* b_tpc_xy; // 7
        Bool_t sci_b_x[12] = {false};

        // ::: IDs ::: //
        Float_t id_x1;
        Float_t id_y1;
        Float_t id_a1;
        Float_t id_b1;
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
        Float_t id_beta_s1s2;
        Float_t id_gamma_s1s2;
        Float_t id_AoQ_s1s2;
        Float_t id_AoQ_corr_s1s2;
        Float_t id_music21_v_cor;
        Float_t id_music22_v_cor;
        Float_t id_z21;
        Float_t id_z22;
        Float_t id_rho[4];
        Float_t id_brho[4];
        Float_t id_beta_s2s4;
        Float_t id_gamma_s2s4;
        Float_t id_AoQ_s2s4;
        Float_t id_AoQ_corr_s2s4;
        Float_t id_music41_v_cor;
        Float_t id_music42_v_cor;
        Float_t id_music43_v_cor;
        Float_t id_z41;
        Float_t id_z42;
        Float_t id_z43;
        Float_t id_gamma_ta_s2s4;
        Float_t id_dEdegoQ;
        Float_t id_dEdeg_z41;
        Bool_t id_b_x1;
        Bool_t id_b_x2;
        Bool_t id_b_x4;
        Bool_t id_b_AoQ_s1s2;
        Bool_t id_b_z21;
        Bool_t id_b_z22;
        Bool_t id_b_AoQ_s2s4;
        Bool_t id_b_z41;
        Bool_t id_b_z42;
        Bool_t id_b_z43;

        Float_t* id_mhtdc_tof_s1s2 = nullptr;
        Float_t* id_mhtdc_beta_s1s2 = nullptr;
        Float_t* id_mhtdc_gamma_s1s2 = nullptr;
        Float_t* id_mhtdc_delta_s1s2 = nullptr;
        Float_t* id_mhtdc_aoq_s1s2 = nullptr;
        Float_t* id_mhtdc_aoq_corr_s1s2 = nullptr;
        Float_t* id_mhtdc_v_cor_music21 = nullptr;
        Float_t* id_mhtdc_z_music21 = nullptr;
        Float_t* id_mhtdc_z_shifted_music21 = nullptr;
        Float_t* id_mhtdc_v_cor_music22 = nullptr;
        Float_t* id_mhtdc_z_music22 = nullptr;
        Float_t* id_mhtdc_z_shifted_music22 = nullptr;

        Float_t* id_mhtdc_tof_s2s4 = nullptr;
        Float_t* id_mhtdc_beta_s2s4 = nullptr;
        Float_t* id_mhtdc_gamma_s2s4 = nullptr;
        Float_t* id_mhtdc_delta_s2s4 = nullptr;
        Float_t* id_mhtdc_aoq_s2s4 = nullptr;
        Float_t* id_mhtdc_aoq_corr_s2s4 = nullptr;
        Float_t* id_mhtdc_v_cor_music41 = nullptr;
        Float_t* id_mhtdc_z_music41 = nullptr;
        Float_t* id_mhtdc_z_shifted_music41 = nullptr;
        Float_t* id_mhtdc_v_cor_music42 = nullptr;
        Float_t* id_mhtdc_z_music42 = nullptr;
        Float_t* id_mhtdc_z_shifted_music42 = nullptr;
        Float_t* id_mhtdc_v_cor_music43 = nullptr;
        Float_t* id_mhtdc_z_music43 = nullptr;
        Float_t* id_mhtdc_z_shifted_music43 = nullptr;

        Float_t* mhtdc_gamma1square_s2s4 = nullptr;
        Float_t* id_mhtdc_gamma_ta_s2s4 = nullptr;
        Float_t* id_mhtdc_dEdegoQ_s2s4 = nullptr;
        Float_t* id_mhtdc_dEdeg_z41 = nullptr;

        std::vector<Float_t> s1x_mhtdc;
        std::vector<Float_t> s1a_mhtdc;
        std::vector<Float_t> s2x_s1s2_mhtdc;
        std::vector<Float_t> s2a_s1s2_mhtdc;
        std::vector<Float_t> tof_s1s2_mhtdc;
        std::vector<Float_t> beta_s1s2_mhtdc;
        std::vector<Float_t> aoq_s1s2_mhtdc;
        std::vector<Float_t> aoq_corr_s1s2_mhtdc;
        std::vector<Float_t> z_music21_mhtdc;
        std::vector<Float_t> z_music22_mhtdc;

        std::vector<Float_t> s2x_s2s4_mhtdc;
        std::vector<Float_t> s2a_s2s4_mhtdc;
        std::vector<Float_t> s4x_mhtdc;
        std::vector<Float_t> s4a_mhtdc;
        std::vector<Float_t> tof_s2s4_mhtdc;
        std::vector<Float_t> beta_s2s4_mhtdc;
        std::vector<Float_t> aoq_s2s4_mhtdc;
        std::vector<Float_t> aoq_corr_s2s4_mhtdc;
        std::vector<Float_t> z_music41_mhtdc;
        std::vector<Float_t> z_music42_mhtdc;
        std::vector<Float_t> z_music43_mhtdc;
        std::vector<Float_t> dEdegoQ_s2s4_mhtdc;
        std::vector<Float_t> dEdeg_z41_mhtdc;

        // :: DriftCorr :: //
        Float_t id_AoQ_driftcorr;
        Float_t id_z_driftcorr;


        // Misc
        TRandom3 random3;
        Float_t aoq_factor = 931.4940 / 299.792458;
        Float_t speed_light = 0.299792458; //m/ns
        Float_t temp_tm_to_MeV = 299.792458;
        Float_t temp_mu = 931.4940954; //MeV

       
    public:
        ClassDef(FrsCal2Hit, 1);

};

#endif
