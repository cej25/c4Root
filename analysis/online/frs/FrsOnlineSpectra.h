#ifndef FrsOnlineSpectra_H
#define FrsOnlineSpectra_H 1

#include "FairTask.h"

class TClonesArray;
class EventHeader;
class FrsHitData;
class TFolder;
class TCanvas;
class TH1F;
class TH2F;
class TH1D;

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

        void SetRangeZ(Double_t min, Double_t max)
        {
            fMin_Z = min;
            fMax_Z = max;
        }

        void SetRangeAq(Double_t min, Double_t max)
        {
            fMin_AoQ = min;
            fMax_AoQ = max;
        }

        void SetRangeX4(Double_t min, Double_t max)
        {
            fMin_x4 = min;
            fMax_x4 = max;
        }

        void SetIsoGate(Double_t minz, Double_t maxz, Double_t minaq, Double_t maxaq)
        {
            fMin_Z_gate = minz;
            fMax_Z_gate = maxz;
            fMin_AoQ_gate = minaq;
            fMax_AoQ_gate = maxaq;
        }

    private:
        TClonesArray* fHitFrsArray; // array with hit items
        FrsHitData* fHitFrs; // array with hit items

        // Ranges for histograms
        Double_t fMin_Z, fMax_Z, fMin_AoQ, fMax_AoQ, fMin_x4, fMax_x4;
        Double_t fMin_Z_gate, fMax_Z_gate, fMin_AoQ_gate, fMax_AoQ_gate;

        EventHeader* header;
        Int_t fNEvents;

        TFolder* frs_spectra_folder;

        // Canvas
        TCanvas* c_frs_z1_vs_AoQ;
        TCanvas* c_frs_x4_vs_AoQ;

        // Histograms for PID:
        TH2F* h_frs_z1_vs_AoQ;
        TH2F* h_frs_x4_vs_AoQ;
        TH1D* h_frs_beta_sci;

        // Histograms for Scalers
        char scaler_name[66][256];
        TH1D* hScaler_per_s[66];
        TH1D* hScaler_per_100ms[66];
        TH1D* hScaler_per_spill[66];
        int ratio_previous = 100;
        int ratio_previous2 = 100;



    public:
        ClassDef(FrsOnlineSpectra, 1)

};

#endif