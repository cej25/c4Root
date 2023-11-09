#ifndef bPlastOnlineSpectra_H
#define bPlastOnlineSpectra_H

#include "FairTask.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;

class bPlastOnlineSpectra : public FairTask
{
    public:
        bPlastOnlineSpectra();
        bPlastOnlineSpectra(const TString& name, Int_t verbose = 1);


        void CreateHistograms();

        virtual ~bPlastOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        // range setters

    
    private:
        TClonesArray* fHitbPlastTwinpeaks;


        // ranges
        //Double_t

        EventHeader* header;
        Int_t fNEvents;

        // Canvas -- we can think about adding lead and trail spectra for each channel/detector
        TCanvas* cSlowToT;
        TCanvas* cFastToT;
        TCanvas* cFastHitPatt;
        TCanvas* cSlowHitPatt;
        TCanvas* cSlowToT_vs_FastToT;

        TCanvas* time_spectra_divided;

        static const int NDetectors = 128;

        // Histograms energy
        TH1F * h1_SlowToT[NDetectors];
        TH1F * h1_FastToT[NDetectors];
        TH1F * h1_FastHitPatt;
        TH1F * h1_SlowHitPatt;

         TH2F * h1_SlowToT_vs_FastToT[NDetectors];

        //Absolute time spectra
        TH1F * h1_abs_time[NDetectors];



    public:
        ClassDef(bPlastOnlineSpectra, 1)
};

#endif