#ifndef FrsOnlineSpectra_H
#define FrsOnlineSpectra_H 1

#include "TFrsConfiguration.h"
#include "FrsGate.h"
#include "FrsHitData.h"
#include "AnalysisTools.h"

#include "FairTask.h"
#include "TH2.h"
#include "TCutG.h"
#include "TDirectory.h"
#include <vector>

class TClonesArray;
class EventHeader;
class FrsHitData;
class FrsGate;
class TFolder;
class TDirectory;
class TCanvas;
class TH1;
class TH2;
class TH1I;
class TH1F;
class TH1D;
class TH2I;
class TH2F;
class TH2D;

class FrsOnlineSpectra : public FairTask
{
    public:
        FrsOnlineSpectra();
        FrsOnlineSpectra(std::vector<FrsGate*> fg);

        FrsOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        virtual void Snapshot_Histo();


    private:
        //AnalysisTools const* Ana;

        TFrsConfiguration const* frs_config;

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

        //TClonesArray* fHitFrsArray; // array with hit items
        std::vector<FrsHitItem> const* hitArray;
        std::vector<FrsMultiHitItem> const* multihitArray; //EG

        EventHeader* header;
        Int_t fNEvents;

        TString screenshot_path = "/u/despec/screenshots/";

        // Canvas
        TCanvas* c_frs_z1_vs_AoQ;
        TCanvas* c_frs_x4_vs_AoQ;
        TCanvas* c_frs_snapshot;

        // testing...
        TH1* h1_test_scaler;
        TH2* h2_test_again;

        // Histograms for PID:
        // TAC
        TH2* h2_Z_vs_AoQ;
        //TH2D* h2_Z_vs_AoQ;
        TH2D* h2_Z_vs_AoQ_corr;
        TH2D* h2_Z_vs_Z2;
        TH2D* h2_Z_vs_AoQ_Zsame;
        TH2D* h2_x4_vs_AoQ_Zsame;
        TH2D* h2_x2_vs_AoQ_Zsame;
        TH2D* h2_x2_vs_AoQ;
        TH2D* h2_x4_vs_AoQ;
        TH2D* h2_dEdegoQ_vs_Z;
        TH2D* h2_dEdeg_vs_Z;
        TH2D* h2_a2_vs_AoQ;
        TH2D* h2_a4_vs_AoQ;
        TH2D* h2_Z_vs_dE2;
        TH2D* h2_x2_vs_x4;
        TH2D* h2_SC41dE_vs_AoQ;
        TH2D* h2_dE_vs_ToF;
        TH2D* h2_x2_vs_Z;
        TH2D* h2_x4_vs_Z;
        TH2D* h2_dE1_vs_x2;
        TH2D* h2_dE1_vs_x4;
        TH2D* h2_x2_vs_a2;
        TH2D* h2_y2_vs_b2;
        TH2D* h2_x4_vs_a4;
        TH2D* h2_y4_vs_b4;
        TH2D* h2_Z_vs_Sc21E;
        // MHTDC
        TH2D* h2_Z_vs_AoQ_mhtdc; //EG  


        // Prioritising Z1Z2
        /*TH2I* h2_Z_vs_AoQ_ZAoQgate;
        TH2I* h2_Z1_vs_Z2_ZAoQgate;
        TH2I* h2_x2_vs_AoQ_ZAoQgate;
        TH2I* h2_x4_vs_AoQ_ZAoQgate;
        TH2I* h2_dEdeg_vs_Z_ZAoQgate;
        TH2I* h2_dedegoQ_vs_Z_ZAoQgate;
        TH1I* h1_a2_ZAoQ_gate;
        TH1I* h1_a4_ZAoQ_gate;*/

        std::vector<TH2I*> h2_Z_vs_AoQ_Z1Z2gate;
        std::vector<TH2I*> h2_Z1_vs_Z2_Z1Z2gate;
        std::vector<TH2I*> h2_x2_vs_AoQ_Z1Z2gate;
        std::vector<TH2I*> h2_x4_vs_AoQ_Z1Z2gate;
        std::vector<TH2I*> h2_dEdeg_vs_Z_Z1Z2gate;
        std::vector<TH2I*> h2_dedegoQ_vs_Z_Z1Z2gate;
        std::vector<TH1I*> h1_a2_Z1Z2_gate;
        std::vector<TH1I*> h1_a4_Z1Z2_gate;

        std::vector<TH2I*> h2_x2_vs_AoQ_Z1Z2x2AoQgate;
        std::vector<TH2I*> h2_x4_vs_AoQ_Z1Z2x2AoQgate;
        std::vector<TH2I*> h2_Z_vs_AoQ_Z1Z2x2AoQgate;
        std::vector<TH2I*> h2_dEdeg_vs_Z_Z1Z2x2AoQgate;
        std::vector<TH2I*> h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate;
        std::vector<TH1I*> h1_a2_Z1Z2x2AoQgate;
        std::vector<TH1I*> h1_a4_Z1Z2x2AoQgate;

        std::vector<TH2I*> h2_x2_vs_AoQ_Z1Z2x4AoQgate;
        std::vector<TH2I*> h2_x4_vs_AoQ_Z1Z2x4AoQgate;
        std::vector<TH2I*> h2_Z_vs_AoQ_Z1Z2x4AoQgate;
        std::vector<TH2I*> h2_dEdeg_vs_Z_Z1Z2x4AoQgate;
        std::vector<TH2I*> h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate;
        std::vector<TH1I*> h1_a2_Z1Z2x4AoQgate;
        std::vector<TH1I*> h1_a4_Z1Z2x4AoQgate;

        // 1D plots
        TH1I* h1_tpat;
        // :: switched on and off by config :: //
        TH1D* h1_frs_Z;
        TH1D* h1_frs_Z2;
        TH1D* h1_frs_AoQ;
        TH1D* h1_frs_AoQ_corr;
        TH1D* h1_frs_x2;
        TH1D* h1_frs_x4;
        // more to come .. 
        


        // travel music specific
        TH1I* h1_wr_frs_travmus;
        TH1D* h1_travmus_z;
        TH1D* h1_travmus_z_MHTDC;
        TH1D* h1_travmus_dE;
        TH1D* h1_z1;
        TH1D* h1_z1_MHTDC;
        TH1D* h1_z1_dE;
        TH1D* h1_z2;
        TH1D* h1_z2_MHTDC;
        TH1D* h1_z2_dE;
        TH2D* h2_travmus_z1;
        TCanvas* c_z_compare;
        TCanvas* c_z_compare_MHTDC;
        TCanvas* c_dE_compare;

        // TDirectory structure
        TFolder* histograms;
        TDirectory* dir_frs;
        TDirectory* dir_tac;
        TDirectory* dir_mhtdc;
        TDirectory* dir_scalers;

        TDirectory* dir_tac_1d;
        TDirectory* dir_tac_2d;
        TDirectory* dir_gated_tac;
        TDirectory* dir_ZvsZ2;
        TDirectory* dir_ZvsZ2_x2vsAoQ;
        TDirectory* dir_ZvsZ2_x4vsAoQ;

        TDirectory* dir_mhtdc_1d;
        TDirectory* dir_mhtdc_2d;
        TDirectory* dir_gated_mhtdc;

        TDirectory* dir_travmus;
        TDirectory* dir_travmus_tac;
        TDirectory* dir_travmus_mhtdc;

        // Histograms for Scalers
        char scaler_name[66][256];
        TH1D* hScaler_per_s[66];
        TH1D* hScaler_per_100ms[66];
        TH1D* hScaler_per_spill[66];
        int ratio_previous = 100;
        int ratio_previous2 = 100;

        // I don't think we need this anymore.
        TCutG* cutID_Z_AoQ = nullptr;



    public:
        ClassDef(FrsOnlineSpectra, 1)

};

#endif