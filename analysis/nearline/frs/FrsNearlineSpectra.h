#ifndef FrsNearlineSpectra_H
#define FrsNearlineSpectra_H

#include "TFrsConfiguration.h"
#include "TExperimentConfiguration.h"
#include "FrsHitData.h"
#include "FrsTPCCalData.h"
#include "FairTask.h"
#include "TFRSParameter.h"
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
        EventHeader* header;
        int multihit_counter = 0;
        
        std::vector<FrsTPCCalItem> const* tpcCalArray;
        std::vector<FrsHitItem> const* hitArray;
        std::vector<FrsMultiHitItem> const* multihitArray;

        // folders
        bool found_dir_frs = true;
        TDirectory* dir_frs; // for now fine, maybe needs to be...overarching branch? dunno
        TDirectory* dir_scalers;
        TDirectory* dir_rates;
        TDirectory* dir_drifts;
        TDirectory* dir_tac;
        TDirectory* dir_mhtdc;
        TDirectory* dir_tac_1d;
        TDirectory* dir_tac_2d;
        TDirectory* dir_gated_tac;
        TDirectory* dir_ZvsAoQ_tac;
        TDirectory* dir_Z1vsZ2_tac;
        TDirectory* dir_x2vsAoQ_tac;
        TDirectory* dir_x4vsAoQ_tac;
        TDirectory* dir_dEdegvsZ_tac;
        TDirectory* dir_mhtdc_1d;
        TDirectory* dir_mhtdc_2d;
        TDirectory* dir_gated_mhtdc;
        TDirectory* dir_ZvsAoQ_mhtdc;
        TDirectory* dir_Z1vsZ2_mhtdc;
        TDirectory* dir_x2vsAoQ_mhtdc; 
        TDirectory* dir_x4vsAoQ_mhtdc;
        TDirectory* dir_dEdegvsZ_mhtdc;

        //canvases
        TCanvas* c_TravMus_drift;
    
        // Histograms
        // TAC 2D + Gated
        TH2* h2_Z_vs_AoQ;
        TH2* h2_Z_vs_AoQ_driftcorr;
        TH2* h2_Z_vs_AoQ_corr;
        TH2* h2_Z_vs_Z2;
        TH2* h2_Z_vs_AoQ_Zsame;
        TH2* h2_x4_vs_AoQ_Zsame;
        TH2* h2_x2_vs_AoQ_Zsame;
        TH2* h2_x2_vs_AoQ;
        TH2* h2_x4_vs_AoQ;
        TH2* h2_dEdegoQ_vs_Z;
        TH2* h2_dEdeg_vs_Z;
        TH2* h2_a2_vs_AoQ;
        TH2* h2_a4_vs_AoQ;
        TH2* h2_Z_vs_dE2;
        TH2* h2_x2_vs_x4;
        TH2* h2_SC41dE_vs_AoQ;
        TH2* h2_SC42dE_vs_AoQ;
        TH2* h2_SC41dE_vs_Z;
        TH2* h2_SC42dE_vs_Z;
        TH2* h2_dE_vs_ToF_21_41;
        TH2* h2_x2_vs_Z;
        TH2* h2_x4_vs_Z;
        TH2* h2_dE1_vs_x2;
        TH2* h2_dE1_vs_x4;
        TH2* h2_x2_vs_a2;
        TH2* h2_y2_vs_b2;
        TH2* h2_x4_vs_a4;
        TH2* h2_y4_vs_b4;
        TH2* h2_Z_vs_Sc21E;
        std::vector<TH2*> h2_Z_vs_AoQ_ZAoQgate;
        std::vector<TH2*> h2_Z1_vs_Z2_ZAoQgate;
        std::vector<TH2*> h2_x2_vs_AoQ_ZAoQgate;
        std::vector<TH2*> h2_x4_vs_AoQ_ZAoQgate;
        std::vector<TH2*> h2_dEdeg_vs_Z_ZAoQgate;
        std::vector<TH2*> h2_dedegoQ_vs_Z_ZAoQgate; // 
        std::vector<TH2*> h2_dEdeg_vs_Z_Z1Z2gate;
        std::vector<TH2*> h2_dEdegoQ_vs_Z_Z1Z2gate;
        std::vector<TH2*> h2_Z1_vs_Z2_Z1Z2gate;
        std::vector<TH2*> h2_x2_vs_AoQ_Z1Z2gate;
        std::vector<TH2*> h2_x4_vs_AoQ_Z1Z2gate;
        std::vector<TH2*> h2_Z_vs_AoQ_Z1Z2gate; //
        std::vector<TH2*> h2_x2_vs_AoQ_x2AoQgate;
        std::vector<TH2*> h2_Z1_vs_Z2_x2AoQgate;
        std::vector<TH2*> h2_x2_vs_AoQ_Z1Z2x2AoQgate;
        std::vector<TH2*> h2_x4_vs_AoQ_Z1Z2x2AoQgate;
        std::vector<TH2*> h2_Z_vs_AoQ_Z1Z2x2AoQgate;
        std::vector<TH2*> h2_dEdeg_vs_Z_Z1Z2x2AoQgate;
        std::vector<TH2*> h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate; // 
        std::vector<TH2*> h2_x4_vs_AoQ_x4AoQgate;
        std::vector<TH2*> h2_Z1_vs_Z2_x4AoQgate;
        std::vector<TH2*> h2_x2_vs_AoQ_Z1Z2x4AoQgate;
        std::vector<TH2*> h2_x4_vs_AoQ_Z1Z2x4AoQgate;
        std::vector<TH2*> h2_Z_vs_AoQ_Z1Z2x4AoQgate;
        std::vector<TH2*> h2_dEdeg_vs_Z_Z1Z2x4AoQgate;
        std::vector<TH2*> h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate; // 
        std::vector<TH2*> h2_Z_vs_AoQ_dEdegZgate;
        std::vector<TH2*> h2_Z1_vs_Z2_dEdegZgate;
        std::vector<TH2*> h2_x2_vs_AoQ_dEdegZgate;
        std::vector<TH2*> h2_x4_vs_AoQ_dEdegZgate;
        std::vector<TH2*> h2_Z_vs_AoQ_Zsame_dEdegZgate; // 
        

        // TAC 1D // :: Should add gated a2/a4 here if they're really desired
        TH1* h1_tpat;
        TH1* h1_Z;
        TH1* h1_Z_driftcorr;
        TH1* h1_Z2;
        TH1* h1_AoQ;
        TH1* h1_AoQ_driftcorr;
        TH1* h1_AoQ_corr;
        TH1* h1_x2;
        TH1* h1_x4;
        TH1* h1_a2;
        TH1* h1_a4;
        TH1* h1_y2;
        TH1* h1_y4;
        TH1* h1_b2;
        TH1* h1_b4;
        TH1* h1_beta; 
        TH1* h1_dEdeg;
        TH1* h1_dEdegoQ;
        TH1* h1_rho[2];
        TH1* h1_brho[2];
        TH1* h1_music_dE[2];
        TH1* h1_music_dEcorr[2];
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
        TH1* h1_sci_e_21;
        TH1* h1_sci_e_22;
        TH1* h1_sci_e_31;
        TH1* h1_sci_e_41;
        TH1* h1_sci_e_42;
        TH1* h1_sci_e_43;
        TH1* h1_sci_e_81;
        TH1* h1_sci_x_21;
        TH1* h1_sci_x_22;
        TH1* h1_sci_x_31;
        TH1* h1_sci_x_41;
        TH1* h1_sci_x_42;
        TH1* h1_sci_x_43;
        TH1* h1_sci_x_81;
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
        TH2* h2_Z_vs_AoQ_mhtdc;
        TH2* h2_Z_vs_AoQ_corr_mhtdc;
        TH2* h2_Z_vs_Z2_mhtdc;
        TH2* h2_Z_vs_AoQ_Zsame_mhtdc;
        TH2* h2_x4_vs_AoQ_Zsame_mhtdc;
        TH2* h2_x2_vs_AoQ_Zsame_mhtdc;
        TH2* h2_x2_vs_AoQ_mhtdc;
        TH2* h2_x4_vs_AoQ_mhtdc;
        TH2* h2_dEdegoQ_vs_Z_mhtdc;
        TH2* h2_dEdeg_vs_Z_mhtdc;
        TH2* h2_a2_vs_AoQ_mhtdc;
        TH2* h2_a4_vs_AoQ_mhtdc;
        TH2* h2_Z_vs_dE2_mhtdc;
        TH2* h2_x2_vs_x4_mhtdc;
        TH2* h2_SC41dE_vs_AoQ_mhtdc;
        TH2* h2_SC42dE_vs_AoQ_mhtdc; // !! not added yet !!
        TH2* h2_SC41dE_vs_Z_mhtdc; // !! not added yet !! 
        TH2* h2_SC42dE_vs_Z_mhtdc; // !! not added yet !!
        TH2* h2_dE_vs_ToF_mhtdc;
        TH2* h2_x2_vs_Z_mhtdc;
        TH2* h2_x4_vs_Z_mhtdc;
        TH2* h2_Z_vs_Sc21E_mhtdc;
        std::vector<TH2*> h2_Z_vs_AoQ_ZAoQgate_mhtdc;
        std::vector<TH2*> h2_Z1_vs_Z2_ZAoQgate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQ_ZAoQgate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQ_ZAoQgate_mhtdc;
        std::vector<TH2*> h2_dEdeg_vs_Z_ZAoQgate_mhtdc;
        std::vector<TH2*> h2_dedegoQ_vs_Z_ZAoQgate_mhtdc; // 
        std::vector<TH2*> h2_dEdeg_vs_Z_Z1Z2gate_mhtdc;
        std::vector<TH2*> h2_dEdegoQ_vs_Z_Z1Z2gate_mhtdc;
        std::vector<TH2*> h2_Z1_vs_Z2_Z1Z2gate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQ_Z1Z2gate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQ_Z1Z2gate_mhtdc;
        std::vector<TH2*> h2_Z_vs_AoQ_Z1Z2gate_mhtdc; // 
        std::vector<TH2*> h2_x2_vs_AoQ_x2AoQgate_mhtdc;
        std::vector<TH2*> h2_Z1_vs_Z2_x2AoQgate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2*> h2_Z1_vs_Z2_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2*> h2_Z_vs_AoQ_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2*> h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2*> h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc; // 
        std::vector<TH2*> h2_x4_vs_AoQ_x4AoQgate_mhtdc;
        std::vector<TH2*> h2_Z1_vs_Z2_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2*> h2_Z1_vs_Z2_x4AoQgate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2*> h2_Z_vs_AoQ_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2*> h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2*> h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc; // 
        std::vector<TH2*> h2_Z_vs_dEdeg_dEdegZgate_mhtdc;
        std::vector<TH2*> h2_Z_vs_AoQ_dEdegZgate_mhtdc;
        std::vector<TH2*> h2_Z1_vs_Z2_dEdegZgate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQ_dEdegZgate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQ_dEdegZgate_mhtdc;
        std::vector<TH2*> h2_Z_vs_AoQ_Zsame_dEdegZgate_mhtdc; // 
        // not a PID gate but an energy gate on trav Z
        TH2* h2_Z_vs_AoQ_mhtdc_trav_gate;
        TH2* h2_Z_vs_AoQ_tac_trav_gate_driftcorr;
        TH2* h2_Z_vs_AoQ_driftcorr_trav_gate;


        // MHTDC 1D
        TH1* h1_beta_mhtdc;
        TH1* h1_AoQ_mhtdc;
        TH1* h1_AoQ_corr_mhtdc;
        TH1* h1_z_mhtdc;
        TH1* h1_z2_mhtdc;
        TH1* h1_dEdeg_mhtdc;
        TH1* h1_dEdegoQ_mhtdc;

        // Drifts
        TH2* h2_Z1_vs_T;
        TH2* h2_Z1_driftcorr_vs_T;
        TH2* h2_AoQ_vs_T;
        TH2* h2_AoQ_driftcorr_vs_T;
        TH2* h2_Z1_vs_T_mhtdc;
        TH2* h2_AoQ_vs_T_mhtdc;
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



    public:
        ClassDef(FrsNearlineSpectra, 1);
};

#endif