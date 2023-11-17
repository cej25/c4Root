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
        TCanvas* c_fatima_slowToT;
        TCanvas* c_fatima_fastToT;
        TCanvas* c_fatima_fast_v_slow;
        TCanvas* c_fatima_time_spectra_divided;
        TCanvas* c_fatima_hitpatterns;

        static const int NDetectors = 14; //change this
        // Histograms energy
        TH1F * h1_fatima_slowToT[NDetectors];
        TH1F * h1_fatima_fastToT[NDetectors];
        TH2F * h2_fatima_fast_v_slow[NDetectors];

        TH1F * h1_fatima_hitpattern_slow;
        TH1F * h1_fatima_hitpattern_fast;

        //Absolute time spectra
        TH1F * h1_fatima_abs_time[NDetectors];

        



    public:
        ClassDef(FatimaOnlineSpectra, 1)
};

#endif
