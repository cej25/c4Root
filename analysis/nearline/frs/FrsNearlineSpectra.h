#ifndef FrsNearlineSpectra_H
#define FrsNearlineSpectra_H

#include "TFrsConfiguration.h"
#include "TExperimentConfiguration.h"
#include "FrsCalData.h"
#include "FrsHitData.h"
#include "FairTask.h"
#include "TFRSParameter.h"
#include "EventHeader.h"
#include "TH2.h"
#include "TH1.h"
#include "TCutG.h"
#include "TDirectory.h"
#include "TFile.h"
#include "FrsGate.h"
#include "TLine.h"
#include "TText.h"
#include "TCanvas.h"

class TFrsConfiguration;
class TExperimentConfiguration;
class EventHeader;
class FrsHitData;
class FrsGate;
class TFile;
class TDirectory;
class TH1;
class TH2;

class FrsNearlineSpectra : public FairTask
{
    public:
        FrsNearlineSpectra();
        FrsNearlineSpectra(std::vector<FrsGate*> fFrsGates);
        FrsNearlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsNearlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        void Process_TAC();
        void Process_MHTDC();
        void Process_Monitors();

        virtual void FinishEvent();

        virtual void FinishTask();

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

        std::vector<FrsGate*> FrsGates;
        int num_frs_gates = 0;

        Int_t fNEvents;
        EventHeader const* header;
        
        std::vector<FrsHitItem> const* hitArray;
        std::vector<FrsMultiHitItem> const* multihitArray;
        FrsHitItem hitItem;
        FrsMultiHitItem multiHitItem;
        Long64_t wr_frs = 0;
        Long64_t trav_mus_wr = 0;
        Long64_t FRS_time_mins = 0;

        // folders
        bool found_dir_frs = true;
        TDirectory* dir_frs;
        TDirectory* dir_id;
        TDirectory* dir_id_s1s2;
        TDirectory* dir_id_s1s2_1d;
        TDirectory* dir_lisa_pos_1d;
        TDirectory* dir_id_s1s2_2d;
        TDirectory* dir_lisa_pos_2d;
        TDirectory* dir_id_s1s2_gated;
        TDirectory** dir_id_s1s2_gates;
        TDirectory* dir_id_s2s4;
        TDirectory* dir_id_s2s4_1d;
        TDirectory* dir_id_s2s4_2d;
        TDirectory* dir_id_s2s4_gated;
        TDirectory** dir_id_s2s4_gates;
        TDirectory* dir_id_sequential;
        TDirectory** dir_id_sequential_gates;
        TDirectory* dir_mhtdc;
        TDirectory* dir_mhtdc_s1s2;
        TDirectory* dir_mhtdc_s1s2_1d;
        TDirectory* dir_mhtdc_s1s2_2d;
        TDirectory* dir_mhtdc_s1s2_gated;
        TDirectory** dir_mhtdc_s1s2_gates;
        TDirectory* dir_mhtdc_s2s4;
        TDirectory* dir_mhtdc_s2s4_1d;
        TDirectory* dir_mhtdc_s2s4_2d;
        TDirectory* dir_mhtdc_s2s4_gated;
        TDirectory** dir_mhtdc_s2s4_gates;
        TDirectory* dir_mhtdc_sequential;
        TDirectory** dir_mhtdc_sequential_gates;
        TDirectory** dir_mhtdc_sequential_rates;
        TDirectory* dir_sci;
        TDirectory* dir_sci_e;
        TDirectory* dir_sci_x;
        TDirectory* dir_sci_tof;
        TDirectory* dir_music;
        TDirectory* dir_music_e;
        TDirectory* dir_monitors;
        TDirectory* dir_scalers;
        TDirectory* dir_rates;
        TDirectory* dir_drifts;
     

        // ::::: TAC :::::::::
        // ------ 2D -------
        TH2* h2_Z41_vs_AoQs2s4;
        TH2* h2_Z41_vs_AoQs2s4_driftcorr;
        TH2* h2_Z41_vs_AoQs2s4_corr;
        TH2* h2_Z41_vs_Z42;
        TH2* h2_Z41_vs_AoQs2s4_Zsame;
        TH2* h2_x2_vs_AoQs2s4_Zsame;
        TH2* h2_x4_vs_AoQs2s4_Zsame;
        TH2* h2_x2_vs_AoQs2s4;
        TH2* h2_x4_vs_AoQs2s4;
        TH2* h2_dEdegoQ_vs_Z41;
        TH2* h2_dEdegZ41_vs_Z41;
        TH2* h2_a2_vs_AoQs2s4;
        TH2* h2_a4_vs_AoQs2s4;
        TH2* h2_Z41_vs_dE42;
        TH2* h2_x2_vs_x4;
        TH2* h2_SC41dE_vs_AoQs2s4;
        TH2* h2_SC42dE_vs_AoQs2s4;
        TH2* h2_SC41dE_vs_Z41;
        TH2* h2_SC42dE_vs_Z41;
        TH2* h2_dE41_vs_ToF_21_41;
        TH2* h2_x2_vs_Z41;
        TH2* h2_x4_vs_Z41;
        TH2* h2_dE41_vs_x2;
        TH2* h2_dE41_vs_x4;
        TH2* h2_x2_vs_a2;
        TH2* h2_y2_vs_b2;
        TH2* h2_x4_vs_a4;
        TH2* h2_y4_vs_b4;
        TH2* h2_Z41_vs_Sc21E;
        
        // ---- 1D --------- 
        TH1* h1_Z21;
        TH1* h1_Z22;
        TH1* h1_Z41;
        TH1* h1_Z41_driftcorr;
        TH1* h1_Z42;
        TH1* h1_Z43;
        TH1* h1_AoQs1s2;
        TH1* h1_AoQs2s4;
        TH1* h1_AoQs2s4_driftcorr;
        TH1* h1_AoQs1s2_corr;
        TH1* h1_AoQs2s4_corr;

        // :::: TAC GATED :::: 
        // ------ 2D --------
        // S2S4
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_S2S4Gated;
        std::vector<TH2*> h2_Z41_vs_Z42_S2S4Gated;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_S2S4Gated;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_S2S4Gated;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_S2S4Gated;
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_S2S4Gated;

        // Sequential

        // ------ 1D --------
        // S2S4
        std::vector<TH1*> h1_beta_s2s4_S2S4Gated;
        std::vector<TH1*> h1_AoQs2s4_S2S4Gated;
        std::vector<TH1*> h1_Z41_S2S4Gated;
        std::vector<TH1*> h1_Z42_S2S4Gated;
   
        TH1* h1_tpat;
        TH1* h1_x1;
        TH1* h1_x2;
        TH1* h1_x4;
        TH1* h1_a1;
        TH1* h1_a2;
        TH1* h1_a4;
        TH1* h1_y1;
        TH1* h1_y2;
        TH1* h1_y4;
        TH1* h1_b1;
        TH1* h1_b2;
        TH1* h1_b4;
        TH1* h1_beta_s1s2;
        TH1* h1_beta_s2s4; 
        TH1* h1_dEdegoQ;
        TH1* h1_dEdegZ41;
        TH1* h1_rho[2];
        TH1* h1_brho[2];
        TH1* h1_music21_dE;
        TH1* h1_music22_dE;
        TH1* h1_music21_dE_cor;
        TH1* h1_music22_dE_cor;
        TH1* h1_music41_dE;
        TH1* h1_music42_dE;
        TH1* h1_music41_dE_cor;
        TH1* h1_music42_dE_cor;
        TH1* h1_sci_11l;
        TH1* h1_sci_11r;
        TH1* h1_sci_21l;
        TH1* h1_sci_21r;
        TH1* h1_sci_22l;
        TH1* h1_sci_22r;
        TH1* h1_sci_31l;
        TH1* h1_sci_31r;
        TH1* h1_sci_41l;
        TH1* h1_sci_41r;
        TH1* h1_sci_42l;
        TH1* h1_sci_42r;
        TH1* h1_sci_43l;
        TH1* h1_sci_43r;
        TH1* h1_sci_81l;
        TH1* h1_sci_81r;
        TH1* h1_sci_e_11;
        TH1* h1_sci_e_21;
        TH1* h1_sci_e_22;
        TH1* h1_sci_e_31;
        TH1* h1_sci_e_41;
        TH1* h1_sci_e_42;
        TH1* h1_sci_e_43;
        TH1* h1_sci_e_81;
        TH1* h1_sci_x_11;
        TH1* h1_sci_x_21;
        TH1* h1_sci_x_22;
        TH1* h1_sci_x_31;
        TH1* h1_sci_x_41;
        TH1* h1_sci_x_42;
        TH1* h1_sci_x_43;
        TH1* h1_sci_x_81;
        TH1* h1_sci_tof_11_21;
        TH1* h1_sci_tof_11_21_calib;
        TH1* h1_sci_tof_21_41;
        TH1* h1_sci_tof_21_41_calib;
        TH1* h1_sci_tof_21_42;
        TH1* h1_sci_tof_21_42_calib;
        TH1* h1_sci_tof_21_81;
        TH1* h1_sci_tof_21_81_calib;
        TH1* h1_sci_tof_22_41;
        TH1* h1_sci_tof_22_41_calib;
        TH1* h1_sci_tof_22_81;
        TH1* h1_sci_tof_22_81_calib;
        
        // For LISA
        TH1** h1_tpc_x_at_LISA;
        TH1** h1_tpc_y_at_LISA;
        TH2** h2_tpc_xy_at_LISA;
    
        // MHTDC 2D
        TH2* h2_Z41_vs_AoQs2s4_mhtdc;
        TH2* h2_Z41_vs_AoQs2s4_corr_mhtdc;
        TH2* h2_Z41_vs_Z42_mhtdc;
        TH2* h2_Z21_vs_AoQs1s2_mhtdc;
        TH2* h2_Z21_vs_AoQs1s2_corr_mhtdc;
        TH2* h2_Z21_vs_Z22_mhtdc;
        TH2* h2_Z21_vs_Z41_mhtdc;
        TH2* h2_Z41_vs_AoQs2s4_Zsame_mhtdc;
        TH2* h2_x4_vs_AoQs2s4_Zsame_mhtdc;
        TH2* h2_x2_vs_AoQs2s4_Zsame_mhtdc;
        TH2* h2_x2_vs_AoQs2s4_mhtdc;
        TH2* h2_x2_vs_AoQs1s2_mhtdc;
        TH2* h2_x4_vs_AoQs2s4_mhtdc;
        TH2* h2_dEdegoQ_vs_Z41_mhtdc;
        TH2* h2_dEdegZ41_vs_Z41_mhtdc;
        TH2* h2_a2_vs_AoQs1s2_mhtdc;
        TH2* h2_a2_vs_AoQs2s4_mhtdc;
        TH2* h2_a4_vs_AoQs2s4_mhtdc;
        TH2* h2_Z41_vs_dE42_mhtdc;
        TH2* h2_Z21_vs_dE21_mhtdc;
        TH2* h2_x2_vs_x4_mhtdc;
        TH2* h2_SC41dE_vs_AoQs2s4_mhtdc;
        TH2* h2_SC42dE_vs_AoQs2s4_mhtdc; // !! not added yet !!
        TH2* h2_SC41dE_vs_Z41_mhtdc; // !! not added yet !! 
        TH2* h2_SC42dE_vs_Z41_mhtdc; // !! not added yet !!
        TH2* h2_dE41_vs_ToF_mhtdc;
        TH2* h2_x2_vs_Z21_mhtdc;
        TH2* h2_x2_vs_Z41_mhtdc;
        TH2* h2_x4_vs_Z41_mhtdc;
        TH2* h2_Z41_vs_Sc21E_mhtdc;
        TH2* h2_Z21_vs_Sc21E_mhtdc;

        // 1D
        TH1* h1_beta_s1s2_mhtdc;
        TH1* h1_beta_s2s4_mhtdc;
        TH1* h1_AoQs1s2_mhtdc;
        TH1* h1_AoQs2s4_mhtdc;
        TH1* h1_AoQs1s2_corr_mhtdc;
        TH1* h1_AoQs2s4_corr_mhtdc;
        TH1* h1_Z21_mhtdc;
        TH1* h1_Z22_mhtdc;
        TH1* h1_Z41_mhtdc;
        TH1* h1_Z42_mhtdc;
        TH1* h1_Z43_mhtdc;
        TH1* h1_dEdegoQ_mhtdc;
        TH1* h1_dEdegZ41_mhtdc;

        // :::: MHTDC Gated :::: 
        // ---------2D ---------
        // S1S2
        std::vector<TH2*> h2_Z21_vs_AoQs1s2_S1S2Gated_mhtdc;
        std::vector<TH2*> h2_x1_vs_AoQs1s2_S1S2Gated_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs1s2_S1S2Gated_mhtdc;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_S1S2Gated_mhtdc;
        std::vector<TH2*> h2_Z41_vs_Z42_S1S2Gated_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_S1S2Gated_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_S1S2Gated_mhtdc;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_S1S2Gated_mhtdc;
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_S1S2Gated_mhtdc;

        // S2S4
        std::vector<TH2*> h2_Z21_vs_AoQs1s2_S2S4Gated_mhtdc;
        std::vector<TH2*> h2_x1_vs_AoQs1s2_S2S4Gated_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs1s2_S2S4Gated_mhtdc;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_S2S4Gated_mhtdc;
        std::vector<TH2*> h2_Z41_vs_Z42_S2S4Gated_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_S2S4Gated_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_S2S4Gated_mhtdc;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_S2S4Gated_mhtdc;
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_S2S4Gated_mhtdc;

        // Sequential
        std::vector<TH2*> h2_Z21_Z41_S1S2S4Gated_mhtdc;
        std::vector<TH2*> h2_Z21_vs_AoQs1s2_S1S2S4Gated_mhtdc;
        std::vector<TH2*> h2_x1_vs_AoQs1s2_S1S2S4Gated_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs1s2_S1S2S4Gated_mhtdc;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_S1S2S4Gated_mhtdc;
        std::vector<TH2*> h2_Z41_vs_Z42_S1S2S4Gated_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_S1S2S4Gated_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_S1S2S4Gated_mhtdc;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_S1S2S4Gated_mhtdc;
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_S1S2S4Gated_mhtdc;

        // --- 1D ---- 
        // S1S2
        std::vector<TH1*> h1_beta_s1s2_S1S2Gated_mhtdc;
        std::vector<TH1*> h1_AoQs1s2_S1S2Gated_mhtdc;
        std::vector<TH1*> h1_Z21_S1S2Gated_mhtdc;
        std::vector<TH1*> h1_beta_s2s4_S1S2Gated_mhtdc;
        std::vector<TH1*> h1_AoQs2s4_S1S2Gated_mhtdc;
        std::vector<TH1*> h1_Z41_S1S2Gated_mhtdc;
        std::vector<TH1*> h1_Z42_S1S2Gated_mhtdc;
        
        // S2S4
        std::vector<TH1*> h1_beta_s1s2_S2S4Gated_mhtdc;
        std::vector<TH1*> h1_AoQs1s2_S2S4Gated_mhtdc;
        std::vector<TH1*> h1_Z21_S2S4Gated_mhtdc;
        std::vector<TH1*> h1_beta_s2s4_S2S4Gated_mhtdc;
        std::vector<TH1*> h1_AoQs2s4_S2S4Gated_mhtdc;
        std::vector<TH1*> h1_Z41_S2S4Gated_mhtdc;
        std::vector<TH1*> h1_Z42_S2S4Gated_mhtdc;

        // Sequential
        std::vector<TH1*> h1_beta_s1s2_S1S2S4Gated_mhtdc;
        std::vector<TH1*> h1_AoQs1s2_S1S2S4Gated_mhtdc;
        std::vector<TH1*> h1_Z21_S1S2S4Gated_mhtdc;
        std::vector<TH1*> h1_beta_s2s4_S1S2S4Gated_mhtdc;
        std::vector<TH1*> h1_AoQs2s4_S1S2S4Gated_mhtdc;
        std::vector<TH1*> h1_Z41_S1S2S4Gated_mhtdc;
        std::vector<TH1*> h1_Z42_S1S2S4Gated_mhtdc;

        // --- Rates/Ratio ---- 
        std::vector<TH1*> h1_ratio_S2_S4_Gates_mhtdc;
        std::vector<TH1*> h1_integral_S2_Gates_mhtdc;
        std::vector<TH1*> h1_integral_S4_Gates_mhtdc;



        // ::::: Drifts ::::: 
        TH2* h2_Z41_vs_T;
        TH2* h2_Z41_driftcorr_vs_T;
        TH2* h2_AoQs2s4_vs_T;
        TH2* h2_AoQs2s4_driftcorr_vs_T;
        TH2* h2_Z41_vs_T_mhtdc;
        TH2* h2_AoQs2s4_vs_T_mhtdc;
        TH2* h2_sci_tof_11_21_vs_T;
        TH2* h2_sci_tof_21_41_vs_T;
        TH2* h2_sci_tof_21_42_vs_T;
        TH2* h2_sci_tof_21_81_vs_T;
        TH2* h2_sci_tof_22_41_vs_T;
        TH2* h2_sci_tof_22_81_vs_T;
        TH2* h2_tpc_vs_T[6];


        // Lines and Text
        TLine* hline;
        TLine* left_bar;
        TLine* right_bar;
        TText* run_number_text;

        double frs_time_min;
        double frs_time_max;
        

        // Scalers
        char scaler_name[66][256]; // don't need perhaps
        TH1* hScaler_per_s[66];
        TH1* hScaler_per_100ms[66];
        TH1* hScaler_per_spill[66];
        int ratio_previous = 100;
        int ratio_previous2 = 100;


        // TPC rates
        TH1* h1_tpc21_rate;
        TH1* h1_tpc22_rate;
        TH1* h1_tpc23_rate;
        TH1* h1_tpc24_rate;
        TH1* h1_tpc41_rate;
        TH1* h1_tpc42_rate;
        Float_t* tpc_x;
        Float_t tpc_counters[7] = {0};
        Float_t tpc_rates[7] = {0};
        Float_t tpc_21_counter = 0;
        Float_t tpc_21_rate = 0;
        int tpc_running_count = 0;
        int ratio_running_count = 0;
        Long64_t saved_wr_frs = 0;

        // Trackers
        int multihit_counter = 0;
        std::vector<bool> passed_s1s2;
        std::vector<bool> passed_s2s4;
        std::vector<bool> passed_s1s2s4;
        std::vector<int> count_passed_s1s2;
        int* count_passed_s2s4;
        int* count_passed_s1s2s4;

        std::vector<std::vector<Float_t>> z21_passed;
        std::vector<std::vector<Float_t>> AoQ_s1s2_passed;
        std::vector<std::vector<Float_t>> z41_passed;
        std::vector<std::vector<Float_t>> z42_passed;
        std::vector<std::vector<Float_t>> AoQ_s2s4_passed;
        std::vector<std::vector<Float_t>> dEdeg_z41_passed;

    public:
        ClassDef(FrsNearlineSpectra, 1);
};

#endif