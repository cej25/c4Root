#ifndef FrsOnlineSpectra_H
#define FrsOnlineSpectra_H 1

#include "TFrsConfiguration.h"

#include "FairTask.h"
#include "TH2.h"
#include "TCutG.h"

class TClonesArray;
class EventHeader;
class FrsHitData;
class TFolder;
class TCanvas;
class TH1F;
class TH2F;
class TH1D;
class TH1I;
class TH2D;
class TH2I;

class FrsOnlineSpectra : public FairTask
{
    public:
        FrsOnlineSpectra();

        FrsOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();


    private:
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

        TClonesArray* fHitFrsArray; // array with hit items
        FrsHitData* FrsHit; // array with hit items

        EventHeader* header;
        Int_t fNEvents;

        TFolder* folder_frs_hists;
        TFolder* folder_scalers;
        TFolder* folder_pids;
        TFolder* folder_ZvsAoQ_hists;

        // Canvas
        TCanvas* c_frs_z1_vs_AoQ;
        TCanvas* c_frs_x4_vs_AoQ;

        // Histograms for PID:
        TH2D* h2_Z_vs_AoQ;
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
        TH2I* h2_Z_vs_AoQ_ZAoQgate;
        TH2I* h2_Z1_vs_Z2_ZAoQgate;
        TH2I* h2_x2_vs_AoQ_ZAoQgate;
        TH2I* h2_x4_vs_AoQ_ZAoQgate;
        TH2I* h2_dEdeg_vs_Z_ZAoQgate;
        TH2I* h2_dedegoQ_vs_Z_ZAoQgate;
        TH1I* h1_a2_ZAoQ_gate;
        TH1I* h1_a4_ZAoQ_gate;
        TH1I* h1_tpat;

        // Histograms for Scalers
        char scaler_name[66][256];
        TH1D* hScaler_per_s[66];
        TH1D* hScaler_per_100ms[66];
        TH1D* hScaler_per_spill[66];
        int ratio_previous = 100;
        int ratio_previous2 = 100;

        TCutG* cutID_Z_AoQ = nullptr;



    public:
        ClassDef(FrsOnlineSpectra, 1)

};

#endif