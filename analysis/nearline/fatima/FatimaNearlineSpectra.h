#ifndef FatimaNearlineSpectra_H
#define FatimaNearlineSpectra_H

#include "FairTask.h"
#include "TDirectory.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include <vector>

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TDirectory;
class TFolder;

class FatimaNearlineSpectra : public FairTask
{
    public:
        FatimaNearlineSpectra();
        FatimaNearlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FatimaNearlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

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

        // range setters

    
    private:
        TClonesArray* fHitFatimaTwinpeaks;

        // ranges
        EventHeader* header;
        Int_t fNEvents;
        int total_time_microsecs = 0;

        //Folders and files
        TDirectory* dir_fatima;
        TDirectory* dir_fatima_slowToT;
        TDirectory* dir_fatima_fastToT;
        TDirectory* dir_fatima_fast_v_slow;
        TDirectory* dir_fatima_hitpattern;
        TDirectory* dir_fatima_energy_spectra;
        TDirectory* dir_fatima_time_spectra;
        std::vector<TDirectory*> dir_fatima_time_differences;
        
        std::vector<int> detectors = {0,1,2};
        int number_detectors = 3;


        std::vector<int> dt_reference_detectors = {0};
        int number_reference_detectors = 1;
        
        // Histograms 
        std::vector<TH1F*> h1_fatima_slowToT;
        std::vector<TH1F*> h1_fatima_fastToT;
        std::vector<TH1F*> h1_fatima_energy;
        std::vector<TH1F*> h1_fatima_abs_time;
        std::vector<TH2F*> h2_fatima_fast_v_slow;

        TH1F * h1_fatima_multiplicity;
        TH2F * h2_fatima_energy_vs_detid;
        TH2F * h2_fatima_energy_uncal_vs_detid;
        TH1F * h1_fatima_hitpattern_slow;
        TH1F * h1_fatima_hitpattern_fast;
        std::vector<std::vector<TH1F*>> h1_fatima_time_differences;
        std::vector<std::vector<TH2F*>> h2_fatima_time_differences_vs_energy;

        // Binnings:
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
        ClassDef(FatimaNearlineSpectra, 1)
};

#endif
