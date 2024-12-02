#ifndef FrsOnlineSpectra_H
#define FrsOnlineSpectra_H 1

#include "TFrsConfiguration.h"
#include "TExperimentConfiguration.h"
#include "FrsGate.h"
#include "FrsHitData.h"
#include "FrsTPCCalData.h"
#include "AnalysisTools.h"

#include "FairTask.h"
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

        virtual void Snapshot_Histo();


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

        std::vector<FrsTPCCalItem> const* tpcCalArray;
        std::vector<FrsHitItem> const* hitArray;
        std::vector<FrsMultiHitItem> const* multihitArray; //EG

        EventHeader* header;
        Int_t fNEvents;

        TString screenshot_path = "/u/despec/screenshots/";

        // Canvas
        TCanvas* c_frs_z1_vs_AoQ;
        TCanvas* c_frs_x4_vs_AoQ;
        TCanvas* c_frs_snapshot;
        TCanvas* c_z_compare;
        TCanvas* c_z_compare_mhtdc;
        TCanvas* c_dE_compare;

        // TDirectory structure
        TFolder* histograms;
        TDirectory* dir_frs;
        TDirectory* dir_tac;
        TDirectory* dir_mhtdc;
        TDirectory* dir_scalers;
        TDirectory* dir_rates;
        TDirectory* dir_tac_1d;
        TDirectory* dir_tac_2d;
        TDirectory* dir_gated_tac;
        TDirectory* dir_ZvsZ2;
        TDirectory* dir_ZvsZ2_x2vsAoQ;
        TDirectory* dir_ZvsZ2_x4vsAoQ;
        TDirectory* dir_mhtdc_1d;
        TDirectory* dir_mhtdc_2d;
        TDirectory* dir_gated_mhtdc;
        TDirectory* dir_ZvsZ2_mhtdc;
        TDirectory* dir_ZvsZ2_x2vsAoQ_mhtdc;
        TDirectory* dir_ZvsZ2_x4vsAoQ_mhtdc;
        TDirectory* dir_travmus;
        TDirectory* dir_travmus_tac;
        TDirectory* dir_travmus_mhtdc;

        // Histograms for PID:
        // TAC 2D
        TH2* h2_Z_vs_AoQ;
        TH2* h2_Z_vs_AoQ_corr;
        TH2* h2_Z_vs_Z2;
        TH2* h2_travmus_vs_Z;
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
        std::vector<TH2*> h2_Z_vs_AoQ_Z1Z2gate;
        std::vector<TH2*> h2_Z1_vs_Z2_Z1Z2gate;
        std::vector<TH2*> h2_x2_vs_AoQ_Z1Z2gate;
        std::vector<TH2*> h2_x4_vs_AoQ_Z1Z2gate;
        std::vector<TH2*> h2_dEdeg_vs_Z_Z1Z2gate;
        std::vector<TH2*> h2_dedegoQ_vs_Z_Z1Z2gate;
        std::vector<TH2*> h2_x2_vs_AoQ_Z1Z2x2AoQgate;
        std::vector<TH2*> h2_x4_vs_AoQ_Z1Z2x2AoQgate;
        std::vector<TH2*> h2_Z_vs_AoQ_Z1Z2x2AoQgate;
        std::vector<TH2*> h2_dEdeg_vs_Z_Z1Z2x2AoQgate;
        std::vector<TH2*> h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate;
        std::vector<TH2*> h2_x2_vs_AoQ_Z1Z2x4AoQgate;
        std::vector<TH2*> h2_x4_vs_AoQ_Z1Z2x4AoQgate;
        std::vector<TH2*> h2_Z_vs_AoQ_Z1Z2x4AoQgate;
        std::vector<TH2*> h2_dEdeg_vs_Z_Z1Z2x4AoQgate;
        std::vector<TH2*> h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate;
     
        // TAC 1D
        TH1* h1_tpat;
        TH1* h1_Z;
        TH1* h1_Z2;
        TH1* h1_Z_travmus;
        TH1* h1_AoQ;
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
        TH1* h1_travmus_dE;
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
        // 1D Gated?

        // MHTDC 2D
        TH2* h2_Z_vs_AoQ_mhtdc;
        TH2* h2_Z_vs_AoQ_corr_mhtdc;
        TH2* h2_Z_vs_Z2_mhtdc;
        TH2* h2_travmus_vs_Z_mhtdc;
        TH2* h2_Z_vs_AoQ_Zsame_mhtdc;
        TH2* h2_x2_vs_AoQ_Zsame_mhtdc;
        TH2* h2_x4_vs_AoQ_Zsame_mhtdc;
        TH2* h2_x2_vs_AoQ_mhtdc;
        TH2* h2_x4_vs_AoQ_mhtdc;
        TH2* h2_dEdegoQ_vs_Z_mhtdc;
        TH2* h2_dEdeg_vs_Z_mhtdc;
        TH2* h2_a2_vs_AoQ_mhtdc;
        TH2* h2_a4_vs_AoQ_mhtdc;
        TH2* h2_Z_vs_dE2_mhtdc;
        TH2* h2_SC41dE_vs_AoQ_mhtdc;
        TH2* h2_SC42dE_vs_AoQ_mhtdc; // !! not added yet !!
        TH2* h2_SC41dE_vs_Z_mhtdc; // !! not added yet !! 
        TH2* h2_SC42dE_vs_Z_mhtdc; // !! not added yet !!
        TH2* h2_x2_vs_Z_mhtdc;
        TH2* h2_x4_vs_Z_mhtdc;
        TH2* h2_dE1_vs_x2_mhtdc; // !! not added yet !!
        TH2* h2_dE1_vs_x4_mhtdc; // !! not added yet !!
        TH2* h2_Z_vs_Sc21E_mhtdc;
        std::vector<TH2*> h2_Z_vs_AoQ_Z1Z2gate_mhtdc;
        std::vector<TH2*> h2_Z1_vs_Z2_Z1Z2gate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQ_Z1Z2gate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQ_Z1Z2gate_mhtdc;
        std::vector<TH2*> h2_dEdeg_vs_Z_Z1Z2gate_mhtdc;
        std::vector<TH2*> h2_dedegoQ_vs_Z_Z1Z2gate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2*> h2_Z_vs_AoQ_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2*> h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2*> h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2*> h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2*> h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2*> h2_Z_vs_AoQ_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2*> h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2*> h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc;

        // MHTDC 1D
        TH1* h1_beta_mhtdc;
        TH1* h1_AoQ_mhtdc;
        TH1* h1_AoQ_corr_mhtdc;
        TH1* h1_z_mhtdc;
        TH1* h1_z2_mhtdc;
        TH1* h1_z_travmus_mhtdc;
        TH1* h1_dEdeg_mhtdc;
        TH1* h1_dEdegoQ_mhtdc;

        // travel music specific
        TH1* h1_wr_frs_travmus;

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