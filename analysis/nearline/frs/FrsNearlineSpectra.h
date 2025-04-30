#ifndef FrsNearlineSpectra_H
#define FrsNearlineSpectra_H

#include "TFrsConfiguration.h"
#include "TExperimentConfiguration.h"
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

        Int_t fNEvents;
        EventHeader const* header;
        
        std::vector<FrsHitItem> const* hitArray;
        std::vector<FrsMultiHitItem> const* multihitArray;

        // folders
        bool found_dir_frs = true;
        TDirectory* dir_frs; // for now fine, maybe needs to be...overarching branch? dunno
        TDirectory* dir_tac;
        TDirectory* dir_mhtdc;
        TDirectory* dir_scalers;
        TDirectory* dir_rates;
        TDirectory* dir_drifts;
        TDirectory* dir_tac_1d;
        TDirectory* dir_tac_S1S2;
        TDirectory* dir_tac_1d_S1S2;
        TDirectory* dir_tac_2d_S1S2;
        TDirectory* dir_tac_S2S4;
        TDirectory* dir_tac_1d_S2S4;
        TDirectory* dir_tac_2d_S2S4;
        TDirectory* dir_tac_2d;
        TDirectory* dir_gated_tac;
        TDirectory* dir_Z41vsAoQs2s4_tac;
        TDirectory* dir_Z41vsZ42_tac;
        TDirectory* dir_x2vsAoQs2s4_tac;
        TDirectory* dir_x4vsAoQs2s4_tac;
        TDirectory* dir_dEdegZ41vsZ41_tac;
        TDirectory* dir_mhtdc_1d;
        TDirectory* dir_mhtdc_2d;
        TDirectory* dir_mhtdc_S1S2; 
        TDirectory* dir_mhtdc_1d_S1S2;
        TDirectory* dir_mhtdc_2d_S1S2;
        TDirectory* dir_mhtdc_S2S4;
        TDirectory* dir_mhtdc_1d_S2S4;
        TDirectory* dir_mhtdc_2d_S2S4;
        TDirectory* dir_gated_mhtdc_2d_S1S2;
        TDirectory* dir_gated_mhtdc_2d_S2S4;
        TDirectory* dir_Z21vsAoQs1s2_mhtdc;
        TDirectory* dir_Z21vsAoQs1s2_mhtdc_1d;
        TDirectory* dir_Z41vsAoQs2s4_mhtdc;
        TDirectory* dir_Z41vsZ42_mhtdc;
        TDirectory* dir_x2vsAoQs2s4_mhtdc; 
        TDirectory* dir_x4vsAoQs2s4_mhtdc;
        TDirectory* dir_dEdegZ41vsZ41_mhtdc;

        //canvases
        TCanvas* c_TravMus_drift;
    
        // Histograms
        // TAC 2D + Gated
        TH2* h2_Z41_vs_AoQs2s4;
        TH2* h2_Z41_vs_AoQs2s4_driftcorr;
        TH2* h2_Z41_vs_AoQs2s4_corr;
        TH2* h2_Z41_vs_Z42;
        TH2* h2_travmus_vs_Z41;
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
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Z41AoQs2s4_gate;
        std::vector<TH2*> h2_Z41_vs_Z42_Z41AoQs2s4_gate;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Z41AoQs2s4_gate;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Z41AoQs2s4_gate;
        std::vector<TH2*> h2_dedegoQ_vs_Z41_Z41AoQs2s4_gate; // 
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Z41AoQs2s4_gate;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_Zsame_gate;
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Zsame_gate;
        std::vector<TH2*> h2_Z41_vs_Z42_Zsame_gate;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Zsame_gate;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Zsame_gate;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_gate; //
        std::vector<TH2*> h2_x2_vs_AoQs2s4_x2AoQs2s4_gate;
        std::vector<TH2*> h2_Z41_vs_Z42_x2AoQs2s4_gate;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Zsame_x2AoQs2s4_gate;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Zsame_x2AoQs2s4_gate;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_x2AoQs2s4_gate;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_Zsame_x2AoQs2s4_gate; // 
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Zsame_x2AoQs2s4_gate;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_x4AoQs2s4_gate;
        std::vector<TH2*> h2_Z41_vs_Z42_x4AoQs2s4_gate;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Zsame_x4AoQs2s4_gate;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Zsame_x4AoQs2s4_gate;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_x4AoQs2s4_gate;
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Zsame_x4AoQs2s4_gate;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_Zsame_x4AoQs2s4_gate; // 
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_dEdegZ41_Z41_gate;
        std::vector<TH2*> h2_Z41_vs_Z42_dEdegZ41_Z41_gate;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_dEdegZ41_Z41_gate;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_dEdegZ41_Z41_gate;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_dEdegZ41_Z41_gate; // 
        

        // TAC 1D // :: Should add gated a2/a4 here if they're really desired
        TH1* h1_tpat;
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
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Z41AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_Z42_Z41AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Z41AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Z41AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_dedegoQ_vs_Z41_Z41AoQs2s4_gate_mhtdc; //
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Z41AoQs2s4_gate_mhtdc; 
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Zsame_gate_mhtdc;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_Zsame_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_Z42_Zsame_gate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Zsame_gate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Zsame_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_gate_mhtdc; // 
        std::vector<TH2*> h2_x2_vs_AoQs2s4_x2AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_Z42_x2AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Zsame_x2AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Zsame_x2AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_Z42_Zsame_x2AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_x2AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_Zsame_x2AoQs2s4_gate_mhtdc; // 
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Zsame_x2AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_x4AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_Z42_x4AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_Z42_Zsame_x4AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Zsame_x4AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Zsame_x4AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_x4AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_Zsame_x4AoQs2s4_gate_mhtdc; //
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Zsame_x4AoQs2s4_gate_mhtdc; 
        std::vector<TH2*> h2_Z41_vs_dEdegZ41_dEdegZ41_Z41_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_dEdegZ41_Z41_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_Z42_dEdegZ41_Z41_gate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_dEdegZ41_Z41_gate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_dEdegZ41_Z41_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_dEdegZ41_Z41_gate_mhtdc; // 
        // not a PID gate but an energy gate on trav Z
        TH2* h2_Z41_vs_AoQs2s4_mhtdc_trav_gate;
        TH2* h2_Z41_vs_AoQs2s4_tac_trav_gate_driftcorr;
        TH2* h2_Z41_vs_AoQs2s4_driftcorr_trav_gate;

        // -- Gated on S1S2
        std::vector<TH2*> h2_x2_vs_AoQs1s2_Z21vsAoQs1s2_gate;
        std::vector<TH2*> h2_x1_vs_AoQs1s2_Z21vsAoQs1s2_gate;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Z21vsAoQs1s2_gate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Z21vsAoQs1s2_gate_mhtdc;
        std::vector<TH2*> h2_Z21_vs_Z41_mhtdc_Z21vsAoQs1s2_gate_mhtdc;


        // MHTDC 1D
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

        // --  Gated on S1S2
        std::vector<TH1*> h1_beta_s2s4_mhtdc_Z21vsAoQs1s2_gate;
        std::vector<TH1*> h1_AoQs2s4_mhtdc_Z21vsAoQs1s2_gate;
        std::vector<TH1*> h1_Z41_mhtdc_Z21vsAoQs1s2_gate;
        std::vector<TH1*> h1_Z42_mhtdc_Z21vsAoQs1s2_gate;


        // Drifts
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
        TH2D* h2_TravMus_vs_T;
        TH2D* h2_TravMus_driftcorr_vs_T;

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
        int64_t saved_frs_wr = 0;

        // Trackers
        int multihit_counter = 0;
        std::vector<bool> passed_Z21vsAoQs1s2;
        std::vector<int> count_passed_Z41vsAoQs2s4;
        std::vector<int> count_passed_Z41vsZ42;


    public:
        ClassDef(FrsNearlineSpectra, 1);
};

#endif