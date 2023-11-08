#ifndef FatimaOnlineSpectra_H
#define FatimaOnlineSpectra_H

#include "FairTask.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;

class FatimaOnlineSpectra : public FairTask
{
    public:
        FatimaOnlineSpectra();
        FatimaOnlineSpectra(const TString& name, Int_t verbose = 1);


        void CreateHistograms();

        virtual ~FatimaOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        // range setters

    
    private:
        TClonesArray* fHitFatimaTwinpeaks;


        // ranges
        //Double_t

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TCanvas* cslowToT;
        TCanvas* cfastToT;
        TCanvas* cfast_v_slow;
        TCanvas* time_spectra_divided;

        static const int NDetectors =9*17;
        // Histograms energy
        TH1F * h1_slowToT[NDetectors];
        TH1F * h1_fastToT[NDetectors];
        TH2F * h2_fast_v_slow[NDetectors];

        //Absolute time spectra
        TH1F * h1_abs_time[NDetectors];

        



    public:
        ClassDef(FatimaOnlineSpectra, 1)
};

#endif