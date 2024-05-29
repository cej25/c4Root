#ifndef FatimaOnlineSpectra_H
#define FatimaOnlineSpectra_H

#include "FairTask.h"
#include "TDirectory.h"
#include "TFatimaTwinpeaksConfiguration.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include <vector>

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1;
class TH1F;
class TH2F;
class TDirectory;
class TFolder;

class FatimaOnlineSpectra : public FairTask
{
    public:
        FatimaOnlineSpectra();
        FatimaOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FatimaOnlineSpectra();

        virtual void SetParContainers();

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
        void SetBinningCoincidences(int nbins, float binlow, float binhigh){
            ftime_coincidence_nbins = nbins;
            ftime_coincidence_low = binlow;
            ftime_coincidence_high = binhigh;
        }

        void SetDetectorsToPlot(std::vector<int> detectors_to_analyze){
            detectors = detectors_to_analyze;
            number_detectors = detectors.size();
        }

        int GetDetectorIndex(int detector_id){
            //return the index of the detector id in the vector, to index the TH arrays / histograms
            return std::distance(detectors.begin(), std::find(detectors.begin(), detectors.end(), detector_id));
        }

        void AddReferenceDetectorForTimeDifferences(int det){
            dt_reference_detectors.emplace_back(det);
            number_reference_detectors = dt_reference_detectors.size();
            dt_reference_detectors_energy_gates.emplace_back(std::pair<double,double>(0.0, 0.0));
        }
        
        void AddReferenceDetectorForTimeDifferencesWithEnergyGates(int detector_id, double energy_in_other, double energy_in_ref_det){
            dt_reference_detectors.emplace_back(detector_id);
            number_reference_detectors = dt_reference_detectors.size();
            dt_reference_detectors_energy_gates.emplace_back(std::pair<double,double>(energy_in_other,energy_in_ref_det));
        }

        void AddReferenceDetectorForTimeDifferencesWithEnergyGates(int detector_id, double energy_in_ref_det){
            dt_reference_detectors.emplace_back(detector_id);
            number_reference_detectors = dt_reference_detectors.size();
            dt_reference_detectors_energy_gates.emplace_back(std::pair<double,double>(0.0, energy_in_ref_det));
        }


        
        void SetEnergyGateWidth(double width){
            energygate_width = width;
        }
        

        virtual void Reset_Histo();

        virtual void Snapshot_Histo();

        // range setters

    
    private:
        const TFatimaTwinpeaksConfiguration * fatima_configuration;

        TClonesArray* fHitFatimaTwinpeaks;

        // ranges
        EventHeader* header;
        Int_t fNEvents;
        int total_time_microsecs = 0;

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
        TFolder* histograms;
        TDirectory* dir_fatima;
        TDirectory* dir_fatima_slowToT;
        TDirectory* dir_fatima_fastToT;
        TDirectory* dir_fatima_fast_v_slow;
        TDirectory* dir_fatima_hitpattern;
        TDirectory* dir_fatima_energy_spectra;
        TDirectory* dir_fatima_time_spectra;
        TDirectory* dir_fatima_sci41;
        std::vector<TDirectory*> dir_fatima_time_differences = {};
        

        TFile* file_fatima_snapshot;

        TString screenshot_path = "/u/despec/screenshots/";

        std::vector<int> detectors = {0,1,2};
        int number_detectors = 3;


        std::vector<int> dt_reference_detectors = {};
        std::vector<std::pair<double,double>> dt_reference_detectors_energy_gates = {};
        int number_reference_detectors = 0;
        
        // Histograms 
        std::vector<TH1*> h1_fatima_slowToT;
        //std::vector<TH1F*> h1_fatima_slowToT;
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

        //sci41 spectra:
        TCanvas * c_fatima_energy_summed_vs_tsci41;
        TH2F * h2_fatima_energy_summed_vs_tsci41;
        TCanvas * c_fatima_energy_summed_vs_tsci41_cut;
        TH1F * h1_fatima_energy_summed_vs_tsci41_cut;
        TCanvas * c_fatima_energy_energy_sci41_cut;
        TH2F * h2_fatima_energy_energy_sci41_cut;
        
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
        int ftime_coincidence_nbins = 1000;
        float ftime_coincidence_low = -100;
        float ftime_coincidence_high = 100;

        double energygate_width = 10;
            
        int event_multiplicity;

    public:
        ClassDef(FatimaOnlineSpectra, 1)
};

#endif
