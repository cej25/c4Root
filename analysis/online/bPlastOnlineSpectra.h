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
        TCanvas* c_bplast_slowToT;
        TCanvas* c_bplast_fastToT;
        TCanvas* c_bplast_hitpatterns;
        TCanvas* c_bplast_hitpatterns_gated;
        TCanvas* c_bplast_fast_v_slow;

        TCanvas* c_bplast_time_spectra;

        static const int NDetectors = 80;

        // Histograms energy
        TH1F * h1_bplast_slowToT[NDetectors];
        TH1F * h1_bplast_fastToT[NDetectors];
        TH1F * h1_bplast_fast_hitpatterns;
        TH1F * h1_bplast_slow_hitpatterns;
        
        TH1F * h1_bplast_fast_hitpatterns_gated;
        TH1F * h1_bplast_slow_hitpatterns_gated;

        TH2F * h2_bplast_slowToT_vs_fastToT[NDetectors];

        //Absolute time spectra
        TH1F * h1_bplast_abs_time[NDetectors];



    public:
        ClassDef(bPlastOnlineSpectra, 1)
};

#endif
