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


        void SetDetectorsToPlot(std::vector<int> detectors_to_analyze){
            detectors = detectors_to_analyze;
            number_detectors = detectors.size();
        }
        int GetDetectorIndex(int detector_id){
            //return the index of the detector id in the vector, to index the TH arrays / histograms
            return std::distance(detectors.begin(), std::find(detectors.begin(), detectors.end(), detector_id));
        }



        void SetReferenceDetectorsForTimeDifferences(std::vector<int> ref_dets){
            dt_reference_detectors = ref_dets;
            number_reference_detectors = dt_reference_detectors.size();
        }
        int GetReferenceDetectorIndex(int detector_id){
            //return the index of the detector id in the vector, to index the TH arrays / histograms
            return std::distance(detectors.begin(), std::find(detectors.begin(), detectors.end(), detector_id));
        }

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
        TCanvas* c_fatima_energy_vs_detid;
        TCanvas* c_fatima_energies;
        TCanvas* c_fatima_energy_uncal;
        TCanvas* c_fatima_time_differences;
        TCanvas* c_fatima_time_differences_vs_energy;
        TCanvas* c_fatima_snapshot;
        TCanvas* c_fatima_event_multiplicity;
    

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

        std::vector<int> detectors = {0,1,2};
        int number_detectors = 3;


        std::vector<int> dt_reference_detectors = {0};
        int number_reference_detectors = 1;
        
        // Histograms 
        TH1F ** h1_fatima_slowToT;
        TH1F ** h1_fatima_fastToT;
        TH1F ** h1_fatima_energy;
        TH1F ** h1_fatima_abs_time;
        TH2F ** h2_fatima_fast_v_slow;
        TH1F * h1_fatima_multiplicity;
        TH2F * h2_fatima_energy_vs_detid;
        TH2F * h2_fatima_energy_uncal_vs_detid;
        TH1F * h1_fatima_hitpattern_slow;
        TH1F * h1_fatima_hitpattern_fast;
        TH1F *** h1_fatima_time_differences;
        TH2F *** h2_fatima_time_differences_vs_energy;


        //Binnings:
        int ffast_tot_nbins = 500;
        float ffast_tot_bin_low = 0;
        float ffast_tot_bin_high = 100; 
        int fslow_tot_nbins = 500;
        float fslow_tot_bin_low = 550;
        float fslow_tot_bin_high = 750;
        int fenergy_nbins = 500;
        float fenergy_bin_low = 0;
        float fenergy_bin_high = 1500;
            
        int event_multiplicity;

        



    public:
        ClassDef(FatimaOnlineSpectra, 1)
};

#endif
