#ifndef LisaFastOnlineSpectra_H
#define LisaFastOnlineSpectra_H

#include "FairTask.h"
#include "TDirectory.h"
#include "TLisaFastConfiguration.h"
#include "LisaFastCalData.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include <vector>
#include <tuple>
#include <map>

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1;
class TH1F;
class TH2F;
class TDirectory;
class TFolder;

class LisaFastOnlineSpectra : public FairTask
{
    public:
        LisaFastOnlineSpectra();
        LisaFastOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~LisaFastOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();


        // void SetDetectorsToPlot(std::vector<int> detectors_to_analyze){
        //     detectors = detectors_to_analyze;
        //     number_detectors = detectors.size();
        // }

        // int GetDetectorIndex(int detector_id){
        //     //return the index of the detector id in the vector, to index the TH arrays / histograms
        //     return std::distance(detectors.begin(), std::find(detectors.begin(), detectors.end(), detector_id));
        // }

        //std::vector<int> dt_reference_labr = {};
        //std::vector<std::tuple<int,int,int>> dt_reference_diamond = {};


        void AddRefLaBrForDeltaT(int det)
        {
            dt_reference_labr = det;
        }

        void AddRefDiamondForDeltaT(int layer, int x, int y)
        {
            dt_reference_diamond = std::make_tuple(layer, x, y);
        }

        void AddDeltaTEnergyGate(double energy_in_other, double energy_in_ref_det)
        {
            dt_reference_detectors_energy_gates =
                std::make_pair(energy_in_other, energy_in_ref_det);
        }

        void AddDeltaTReferenceEnergyGate(double energy_in_ref_det)
        {
            dt_reference_detectors_energy_gates =
                std::make_pair(0.0, energy_in_ref_det);
        }
        
        // void AddRefLaBrForDeltaT(int det){
            
        //     dt_reference_detectors.emplace_back(det);
        //     number_reference_detectors = dt_reference_detectors.size();
        //     dt_reference_detectors_energy_gates.emplace_back(std::pair<double,double>(0.0, 0.0));
        // }
        
        // void AddReferenceDetectorForTimeDifferencesWithEnergyGates(int detector_id, double energy_in_other, double energy_in_ref_det){
        //     dt_reference_detectors.emplace_back(detector_id);
        //     number_reference_detectors = dt_reference_detectors.size();
        //     dt_reference_detectors_energy_gates.emplace_back(std::pair<double,double>(energy_in_other,energy_in_ref_det));
        // }

        // void AddReferenceDetectorForTimeDifferencesWithEnergyGates(int detector_id, double energy_in_ref_det){
        //     dt_reference_detectors.emplace_back(detector_id);
        //     number_reference_detectors = dt_reference_detectors.size();
        //     dt_reference_detectors_energy_gates.emplace_back(std::pair<double,double>(0.0, energy_in_ref_det));
        // }


        

        virtual void Reset_Histo();

        // range setters

    
    private:

        TLisaFastConfiguration const* lisafast_configuration;

        TClonesArray* fHitLisaFast;

        // ranges
        EventHeader* header;
        Int_t fNEvents;
        int total_time_microsecs = 0;

        int dt_reference_labr = -1;
        std::tuple<int,int,int> dt_reference_diamond = std::make_tuple(-1, -1, -1);

        // Canvas
        // LaBr
        TCanvas* c_lisafast_slowToT_LaBr;
        TCanvas* c_lisafast_fastToT_LaBr;
        TCanvas* c_lisafast_fast_v_slow_LaBr;
        // TCanvas* c_lisafast_LaBr_time_spectra;
        TCanvas* c_lisafast_time_spectra_divided_LaBr;
        TCanvas* c_lisafast_energy_LaBr;
        TCanvas* c_lisafast_energy_uncal_LaBr;
        TCanvas* c_lisafast_energy_vs_detid_LaBr;
        TCanvas* c_lisafast_hitpatterns_LaBr;
        TCanvas* c_lisafast_deltaT_LaBr;
        TCanvas* c_lisafast_deltaT_vs_energy_LaBr;

        // Diamond
        TCanvas* c_lisafast_slowToT_Diamond;
        TCanvas* c_lisafast_fastToT_Diamond;
        TCanvas* c_lisafast_fast_v_slow_Diamond;
        TCanvas* c_lisafast_time_spectra_Diamond;
        TCanvas* c_lisafast_energy_Diamond;
        TCanvas* c_lisafast_hitpatterns_Diamond;

        // dt LaBr-Diamond
        TCanvas* c_dt_LaBr_vs_Diamond;
        TCanvas* c_dt_Diamond_vs_LaBr;
        TCanvas* c_dt_reference_LaBr_vs_Diamond;

        TCanvas* c_dt_LaBr_vs_Diamond_vs_energy;
        TCanvas* c_dt_Diamond_vs_LaBr_vs_energy;
        TCanvas* c_dt_reference_LaBr_vs_Diamond_vs_energy;

        // General
        TCanvas* c_lisafast_event_multiplicity;
    

        //Folders and files
        // Folders

        TFolder* histograms;

        TDirectory* dir_lisafast;

        // LaBr
        TDirectory* dir_lisafast_LaBr;
        TDirectory* dir_lisafast_slowToT_LaBr;
        TDirectory* dir_lisafast_fastToT_LaBr;
        TDirectory* dir_lisafast_fast_v_slow_LaBr;
        TDirectory* dir_lisafast_hitpattern_LaBr;
        TDirectory* dir_lisafast_energy_spectra_LaBr;
        TDirectory* dir_lisafast_time_spectra_LaBr;
        TDirectory* dir_lisafast_deltaT_LaBr;

        // Diamond
        TDirectory* dir_lisafast_Diamond;
        TDirectory* dir_lisafast_slowToT_Diamond;
        TDirectory* dir_lisafast_fastToT_Diamond;
        TDirectory* dir_lisafast_fast_v_slow_Diamond;
        TDirectory* dir_lisafast_hitpattern_Diamond;
        TDirectory* dir_lisafast_energy_spectra_Diamond;
        TDirectory* dir_lisafast_time_spectra_Diamond;
        TDirectory* dir_lisafast_deltaT_Diamond;

        // LaBr-Diamond time differences
        TDirectory* dir_lisafast_dt_LaBr_Diamond;
        TDirectory* dir_dt_LaBr_vs_Diamond;
        TDirectory* dir_dt_Diamond_vs_LaBr;
        TDirectory* dir_dt_reference_LaBr_vs_Diamond;

        //std::vector<TDirectory*> dir_lisafast_time_differences = {};
        
        int number_labr_detectors = 0;
        int number_diamond_detectors = 0;

        //int layer_number;
        //int det_LaBr_number;

        //std::vector<int> dt_reference_detectors = {};
        std::pair<double, double> dt_reference_detectors_energy_gates = {0.0, 0.0};
        //int number_reference_detectors = 0;
        
        // Histograms 
        std::vector<TH1*> h1_lisafast_slowToT_LaBr;
        std::vector<TH1*> h1_lisafast_fastToT_LaBr;
        std::vector<TH1*> h1_lisafast_energy_LaBr;
        std::vector<TH2*> h2_lisafast_fast_v_slow_LaBr;
        std::vector<TH1*> h1_lisafast_abs_time_LaBr;
        std::vector<TH1*> h1_lisafast_deltaT_LaBr;
        std::vector<TH2*> h2_lisafast_deltaT_vs_energy_LaBr;


        std::vector<std::vector<std::vector<TH1*>>> h1_lisafast_slowToT_Diamond;
        std::vector<std::vector<std::vector<TH1*>>> h1_lisafast_fastToT_Diamond;
        std::vector<std::vector<std::vector<TH1*>>> h1_lisafast_energy_Diamond;
        std::vector<std::vector<std::vector<TH2*>>> h2_lisafast_fast_v_slow_Diamond;
        std::vector<std::vector<std::vector<TH1*>>> h1_lisafast_abs_time_Diamond;


        TH1* h1_lisafast_hitpattern_slow_LaBr;
        TH1* h1_lisafast_hitpattern_fast_LaBr;

        TH1* h1_lisafast_hitpattern_slow_Diamond;
        TH1* h1_lisafast_hitpattern_fast_Diamond;        

        TH1* h1_lisafast_multiplicity;

        TH2* h2_lisafast_energy_vs_detid_LaBr;
        TH2* h2_lisafast_energy_uncal_vs_detid_LaBr;  
        
        TH2* h2_lisafast_energy_vs_detid_Diamond;
        TH2* h2_lisafast_energy_uncal_vs_detid_Diamond;

        // LaBr detector vs Diamond reference
        std::map<int, TH1*> h1_dt_LaBr_vs_Diamond;
        std::map<int, TH2*> h2_dt_LaBr_vs_Diamond_vs_energy;


        // Diamond detector vs LaBr reference
        std::map<std::tuple<int,int,int>, TH1*> h1_dt_Diamond_vs_LaBr;
        std::map<std::tuple<int,int,int>, TH2*> h2_dt_Diamond_vs_LaBr_vs_energy;


        // LaBr reference vs Diamond reference
        TH1* h1_dt_reference_LaBr_vs_Diamond;
        TH2* h2_dt_reference_LaBr_vs_Diamond_vs_energy;

        //std::vector<std::vector<TH1*>> h1_lisafast_time_differences;
        //std::vector<std::vector<TH2*>> h2_lisafast_time_differences_vs_energy;

        //TH1** h1_lisafast_rates;
        
        // Binnings:  -- we can also add a way to change them!!
        // int ffast_tot_nbins = 500;
        // float ffast_tot_bin_low = 0;
        // float ffast_tot_bin_high = 100; 

        // // int fslow_tot_nbins = 500;
        // // float fslow_tot_bin_low = 550;
        // // float fslow_tot_bin_high = 750;

        // // int fenergy_nbins = 500;
        // // float fenergy_bin_low = 0;
        // // float fenergy_bin_high = 1500;

        // // int ftime_coincidence_nbins = 1000;
        // // float ftime_coincidence_low = -10;
        // // float ftime_coincidence_high = 10;

        double energygate_width = 10;
            
        int event_multiplicity;

        // rates
        int* detector_counters;
        int* detector_rates;
        int rate_running_count = 0;
         
        float coin_window_ns = 2000.; // move to config
        std::vector<LisaFastCalData> coin_hits;

    public:
        ClassDef(LisaFastOnlineSpectra, 1)
};

#endif
