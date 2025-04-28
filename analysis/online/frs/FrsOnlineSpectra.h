#ifndef FrsOnlineSpectra_H
#define FrsOnlineSpectra_H 1

#include "TFrsConfiguration.h"
#include "TExperimentConfiguration.h"
#include "FrsGate.h"
#include "FrsHitData.h"
#include "AnalysisTools.h"
#include "EventHeader.h"

#include "FairTask.h"
#include "TGraph.h"
#include "TH2.h"
#include "TCutG.h"
#include "TDirectory.h"
#include <vector>

class TFrsConfiguration;
class TExperimentConfiguration;
class EventHeader;
class FrsHitData;
class FrsGate;
class TFolder;
class TDirectory;
class TCanvas;
class TH1;
class TH2;

class FrsOnlineSpectra : public FairTask
{
    public:
        FrsOnlineSpectra();
        FrsOnlineSpectra(std::vector<FrsGate*> fg);

        FrsOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsOnlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

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

        std::vector<FrsHitItem> const* hitArray;
        std::vector<FrsMultiHitItem> const* multihitArray; //EG

        EventHeader* header;
        Int_t fNEvents;


        // Canvas
        TCanvas* c_frs_z1_vs_AoQ;
        TCanvas* c_frs_x4_vs_AoQ;
        TCanvas* c_z_compare;
        TCanvas* c_z_compare_mhtdc;
        TCanvas* c_dE_compare;
        TCanvas* c_beta_compare_mhtdc;
        TCanvas* c_AoQ_compare_mhtdc;
        TCanvas* c_PID_compare_mhtdc;

        // TDirectory structure
        TFolder* histograms;
        TDirectory* dir_frs;
        TDirectory* dir_tac;
        TDirectory* dir_mhtdc;
        TDirectory* dir_scalers;
        TDirectory* dir_rates;
        TDirectory* dir_tac_S1S2; 
        TDirectory* dir_tac_1d_S1S2;
        TDirectory* dir_tac_2d_S1S2;
        TDirectory* dir_tac_S2S4;
        TDirectory* dir_tac_1d_S2S4;
        TDirectory* dir_tac_2d_S2S4;
        //TDirectory* dir_tac_1d;
        //TDirectory* dir_tac_2d;
        TDirectory* dir_gated_tac;
        TDirectory* dir_Z41vsZ42;
        TDirectory* dir_Z41vsZ42_x2vsAoQs2s4;
        TDirectory* dir_Z41vsZ42_x4vsAoQs2s4;

        TDirectory* dir_mhtdc_S1S2; 
        TDirectory* dir_mhtdc_1d_S1S2;
        TDirectory* dir_mhtdc_2d_S1S2;
        TDirectory* dir_mhtdc_S2S4;
        TDirectory* dir_mhtdc_1d_S2S4;
        TDirectory* dir_mhtdc_2d_S2S4;
        //TDirectory* dir_mhtdc_1d;
        //TDirectory* dir_mhtdc_2d;
        TDirectory* dir_gated_mhtdc;
        TDirectory* dir_Z41vsZ42_mhtdc;
        TDirectory* dir_Z41vsZ42_x2vsAoQs2s4_mhtdc;
        TDirectory* dir_Z41vsZ42_x4vsAoQs2s4_mhtdc;
        TDirectory* dir_travmus;
        TDirectory* dir_travmus_tac;
        TDirectory* dir_travmus_mhtdc;

        // Histograms for PID:
        // TAC 2D
        TH2* h2_Z41_vs_AoQs2s4;
        TH2* h2_Z41_vs_AoQs2s4_corr;
        TH2* h2_Z41_vs_Z42;
        TH2* h2_Z21_vs_Z41;
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
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_gate;
        std::vector<TH2*> h2_Z41_vs_Z42_Zsame_gate;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Zsame_gate;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Zsame_gate;
        std::vector<TH2*> h2_dedegoQ_vs_Z41_Zsame_gate;
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Zsame_gate;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Zsame_x2AoQs2s4_gate;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Zsame_x2AoQs2s4_gate;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_x2AoQs2s4_gate;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_Zsame_x2AoQs2s4_gate;
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Zsame_x2AoQs2s4_gate;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Zsame_x4AoQs2s4_gate;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Zsame_x4AoQs2s4_gate;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_x4AoQs2s4_gate;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_Zsame_x4AoQs2s4_gate;
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Zsame_x4AoQs2s4_gate;
     
        // TAC 1D
        TH1* h1_tpat;
        TH1* h1_Z21;
        TH1* h1_Z22;
        TH1* h1_Z41;
        TH1* h1_Z42;
        TH1* h1_Z43;
        TH1* h1_Z_travmus;
        TH1* h1_AoQs1s2;
        TH1* h1_AoQs2s4;
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
        TH1* h1_beta_s1s2;; 
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
        // 1D Gated?

        // MHTDC 2D
        TH2* h2_Z41_vs_AoQs2s4_mhtdc;
        TH2* h2_Z41_vs_AoQs2s4_corr_mhtdc;
        TH2* h2_Z41_vs_Z42_mhtdc;
        TH2* h2_Z21_vs_AoQs1s2_mhtdc;
        TH2* h2_Z21_vs_AoQs1s2_corr_mhtdc;
        TH2* h2_Z21_vs_Z22_mhtdc;
        TH2* h2_Z21_vs_Z41_mhtdc;
        TH2* h2_Z21_vs_dE21_mhtdc;
        TH2* h2_Z41_vs_AoQs2s4_Zsame_mhtdc;
        TH2* h2_x2_vs_AoQs2s4_Zsame_mhtdc;
        TH2* h2_x4_vs_AoQs2s4_Zsame_mhtdc;
        TH2* h2_x2_vs_AoQs1s2_mhtdc;
        TH2* h2_x2_vs_AoQs2s4_mhtdc;
        TH2* h2_x4_vs_AoQs2s4_mhtdc;
        TH2* h2_dEdegoQ_vs_Z41_mhtdc;
        TH2* h2_dEdegZ41_vs_Z41_mhtdc;
        TH2* h2_a2_vs_AoQs1s2_mhtdc;
        TH2* h2_a2_vs_AoQs2s4_mhtdc;
        TH2* h2_a4_vs_AoQs2s4_mhtdc;
        TH2* h2_Z41_vs_dE42_mhtdc;
        TH2* h2_SC41dE_vs_AoQs2s4_mhtdc;
        TH2* h2_SC42dE_vs_AoQs2s4_mhtdc; // !! not added yet !!
        TH2* h2_SC41dE_vs_Z41_mhtdc; // !! not added yet !! 
        TH2* h2_SC42dE_vs_Z41_mhtdc; // !! not added yet !!
        TH2* h2_x2_vs_Z21_mhtdc;
        TH2* h2_x2_vs_Z41_mhtdc;
        TH2* h2_x4_vs_Z41_mhtdc;
        TH2* h2_dE41_vs_x2_mhtdc; // !! not added yet !!
        TH2* h2_dE41_vs_x4_mhtdc; // !! not added yet !!
        TH2* h2_Z21_vs_Sc21E_mhtdc;
        TH2* h2_Z41_vs_Sc21E_mhtdc;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_Z42_Zsame_gate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Zsame_gate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Zsame_gate_mhtdc;
        std::vector<TH2*> h2_dedegoQ_vs_Z41_Zsame_gate_mhtdc;
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Zsame_gate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Zsame_x2AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Zsame_x2AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_x2AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_Zsame_x2AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Zsame_x2AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQs2s4_Zsame_x4AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQs2s4_Zsame_x4AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_Z41_vs_AoQs2s4_Zsame_x4AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_dEdegoQ_vs_Z41_Zsame_x4AoQs2s4_gate_mhtdc;
        std::vector<TH2*> h2_dEdegZ41_vs_Z41_Zsame_x4AoQs2s4_gate_mhtdc;

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

        // travel music specific
        TH1* h1_wr_frs_travmus;

        TGraph* hG_spill_tracker;
        bool previous_spill_flag = false;
        bool current_spill_flag = false;
        int spill_flag_counter = 0;
        int spill_counter = 0;
        int dummy_time_counter = 1;

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

    public:
        ClassDef(FrsOnlineSpectra, 1)

};

#endif
