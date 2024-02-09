#ifndef bPlastOnlineSpectra_H
#define bPlastOnlineSpectra_H

#include "FairTask.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;

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

        virtual void Snapshot_Histo();

        // range setters

    
    private:
        TClonesArray* fHitbPlastTwinpeaks;


        EventHeader* header;
        Int_t fNEvents;

        // Canvases
        TCanvas* c_bplast_slowToT;
        TCanvas* c_bplast_fastToT;
        TCanvas* c_bplast_hitpatterns;
        TCanvas* c_bplast_fast_v_slow;
        TCanvas* c_bplast_time_spectra;
        TCanvas* c_bplast_snapshot;

        //Folders and files
        TDirectory* dir_bplast;
        TFolder* folder_bplast;
        TFolder* folder_bplast_slowToT;
        TFolder* folder_bplast_fastToT;
        TFolder* folder_bplast_hitpattern;
        TFolder* folder_bplast_fast_v_slow;
        TFolder* folder_bplast_time_spectra;
        TFile * file_bplast_snapshot;


        // number of detectors
        static const int NDetectors = 150;

        // Histograms
        TH1F * h1_bplast_slowToT[NDetectors];
        TH1F * h1_bplast_fastToT[NDetectors];

        TH1F * h1_bplast_fast_hitpatterns;
        TH1F * h1_bplast_slow_hitpatterns;

        TH2F * h2_bplast_slowToT_vs_fastToT[NDetectors];

        // Absolute time spectra
        TH1F * h1_bplast_abs_time[NDetectors];


    public:
        ClassDef(bPlastOnlineSpectra, 1)
};

#endif
