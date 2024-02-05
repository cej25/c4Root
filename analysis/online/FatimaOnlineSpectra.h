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

        virtual void Snapshot_Histo();

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
        TCanvas* c_fatima_energy;
        TCanvas* c_fatima_energies;
        TCanvas* c_fatima_energy_uncal;
        TCanvas* c_fatima_time_differences;
        TCanvas* c_fatima_energy_energy;
        TCanvas* c_fatima_time_differences_SCI41;
        TCanvas* c_fatima_time_differences_energy_SCI41;
        TCanvas* c_fatima_time_differences_energy_SCI41_sum;
        TCanvas* c_fatima_time_differences_energy_SCI41_gated;
        TCanvas* c_fatima_snapshot;

        //Folders and directories
        TDirectory* fatimaFolderObj;
        TFolder* folder_fatima;
        TFolder* folder_fatima_slowToT;
        TFolder* folder_fatima_fastToT;
        TFolder* folder_fatima_fast_v_slow;
        TFolder* folder_fatima_time_spectra_divided;
        TFolder* folder_fatima_hitpatterns;
        TFolder* folder_fatima_energy_spectra;
        TFolder* folder_fatima_time_differences;
        TFile* file_fatima_snapshot;


        static const int NDetectors = 24; //change this
        
        // Histograms energy
        TH1F * h1_fatima_slowToT[NDetectors];
        TH1F * h1_fatima_fastToT[NDetectors];
        TH1F * h1_fatima_energies[NDetectors];
        TH1F * h1_fatima_time_differences[NDetectors];
        TH2F * h2_fatima_fast_v_slow[NDetectors];
        TH2F * h1_fatima_time_differences_energy_SCI41[NDetectors];
        TH2F * h1_fatima_time_differences_energy_SCI41_sum;
        TH1F * h1_fatima_time_differences_energy_SCI41_gated;
        TH1F * h1_fatima_time_differences_SCI41[NDetectors];

        TH2F * h2_fatima_energy;
        TH2F * h2_fatima_energy_energy;
        TH2F * h2_fatima_energy_uncal;

        TH1F * h1_fatima_hitpattern_slow;
        TH1F * h1_fatima_hitpattern_fast;

        //Absolute time spectra
        TH1F * h1_fatima_abs_time[NDetectors];

        



    public:
        ClassDef(FatimaOnlineSpectra, 1)
};

#endif
