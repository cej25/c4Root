#ifndef FrsOnlineSpectra_H
#define FrsOnlineSpectra_H 1

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

        // actually these are unnecessary/useless -> set with TFrsConfiguration when it's set up
        void SetRangeZ(Double_t min, Double_t max)
        {
            fMin_Z = min;
            fMax_Z = max;
        }

        void SetRangeAoQ(Double_t min, Double_t max)
        {
            fMin_AoQ = min;
            fMax_AoQ = max;
        }


    private:
        TClonesArray* fHitFrsArray; // array with hit items
        FrsHitData* FrsHit; // array with hit items

        // Ranges for histograms - set defaults.
        Double_t fMin_Z = 0., fMax_Z = 100.;
        Double_t fMin_AoQ = 2., fMax_AoQ = 3.;
        Double_t fMin_x2 = -100., fMax_x2 = 100.;
        Double_t fMin_x4 = -100., fMax_x4 = 100.;
        Double_t fMin_a2 = -100., fMax_a2 = 100.;
        Double_t fMin_a4 = -100., fMax_a4 = 100.;
        Double_t fMin_y2 = -100., fMax_y2 = 100.;
        Double_t fMin_y4 = -100., fMax_y4 = 100.;
        Double_t fMin_b2 = -100., fMax_b2 = 100.;
        Double_t fMin_b4 = -100., fMax_b4 = 100.;
        Double_t fMin_dE = 10., fMax_dE = 100.;
        Double_t fMin_dEoQ = 0.1, fMax_dEoQ = 0.8;
        Double_t fMin_dE_Music1 = 0., fMax_dE_Music1 = 4000.;
        Double_t fMin_dE_Music2 = 0., fMax_dE_Music2 = 4000.;
        // a2? b2? y2? a4? b4? y4?

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