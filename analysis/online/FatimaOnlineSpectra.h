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

        void SetBinningFastToT(int nbins, float binlow, float binhigh){
            ffast_tot_nbins = nbins;
            ffast_tot_bin_low = binlow;
            ffast_tot_bin_high = binhigh;
            
            
        };
        void SetBinningSlowToT(int nbins, float binlow, float binhigh){
            fslow_tot_nbins = nbins;
            fslow_tot_bin_low = binlow;
            fslow_tot_bin_high = binhigh;
            
            
        };
        void SetBinningEnergy(int nbins, float binlow, float binhigh){
            fenergy_nbins = nbins;
            fenergy_bin_low = binlow;
            fenergy_bin_high = binhigh; 
        };


        virtual void Snapshot_Histo();

        // range setters

    
    private:
        TClonesArray* fHitFatimaTwinpeaks;

        // ranges
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

        //Folders and files
        TDirectory* fatimaFolderObj;
        TFolder* folder_fatima;
        TFolder* folder_fatima_slowToT;
        TFolder* folder_fatima_fastToT;
        TFolder* folder_fatima_fast_v_slow;
        TFolder* folder_fatima_time_spectra;
        TFolder* folder_fatima_hitpattern;
        TFolder* folder_fatima_energy_spectra;
        TFolder* folder_fatima_time_differences;
        TFile* file_fatima_snapshot;

        static const int NDetectors = 24; //change this
        
        // Histograms 
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

        int ffast_tot_nbins = 500;
        float ffast_tot_bin_low = 0;
        float ffast_tot_bin_high = 2500; 
        int fslow_tot_nbins = 500;
        float fslow_tot_bin_low = 0;
        float fslow_tot_bin_high = 2500;
        int fenergy_nbins = 500;
        float fenergy_bin_low = 0;
        float fenergy_bin_high = 1500;
            


        



    public:
        ClassDef(FatimaOnlineSpectra, 1)
};

#endif
