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
class TH2;
//class TH3;
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
            dt_reference_detectors_energy_gates.emplace_back(
                energy_in_other,
                energy_in_ref_det
            );
        }

        void AddDeltaTReferenceEnergyGate(double energy_in_ref_det)
        {
            dt_reference_detectors_energy_gates.emplace_back(
                0.0,
                energy_in_ref_det
            );
        }

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
        TCanvas* c_lisafast_time_spectra_divided_LaBr;
        TCanvas* c_lisafast_energy_LaBr;
        TCanvas* c_lisafast_energy_uncal_LaBr;
        TCanvas* c_lisafast_energy_vs_detid_LaBr;
        TCanvas* c_lisafast_hitpatterns_LaBr;
        TCanvas* c_lisafast_deltaT_LaBr;
        TCanvas* c_lisafast_dTw_coin_LaBr;
        TCanvas* c_lisafast_deltaT_vs_energy_LaBr;
        TCanvas* c_lisafast_dTw_vs_energy_coin_LaBr;

        //TCanvas* c_lisafast_deltaT_LaBr_gated;
        //TCanvas* c_lisafast_deltaT_vs_energy_LaBr_gated;
        std::vector<TCanvas*> c_lisafast_deltaT_LaBr_gated;
        std::vector<TCanvas*> c_lisafast_deltaT_vs_energy_LaBr_gated;

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

        TDirectory* dir_lisafast_dT_event_coin_LaBr;
        TDirectory* dir_lisafast_dT_event_Gates_LaBr;
        TDirectory* dir_lisafast_dTw_coin_LaBr;
        TDirectory* dir_lisafast_dT_window_Gates_LaBr;

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

        
        int number_labr_detectors = 0;
        int number_diamond_detectors = 0;

        std::vector<std::pair<double, double>> dt_reference_detectors_energy_gates;
        
        // Histograms 
        // LaBr
        std::vector<TH1*> h1_lisafast_slowToT_LaBr;
        std::vector<TH1*> h1_lisafast_fastToT_LaBr;
        std::vector<TH1*> h1_lisafast_energy_LaBr;
        std::vector<TH2*> h2_lisafast_fast_v_slow_LaBr;
        std::vector<TH1*> h1_lisafast_abs_time_LaBr;

        TH1* h1_lisafast_hitpattern_slow_LaBr;
        TH1* h1_lisafast_hitpattern_fast_LaBr;

        TH2* h2_lisafast_energy_vs_detid_LaBr;
        TH2* h2_lisafast_energy_uncal_vs_detid_LaBr; 

        // Event based coincidence - no gated
        std::vector<TH1*> h1_lisafast_deltaT_LaBr;
        std::vector<TH2*> h2_lisafast_deltaT_vs_energy_LaBr;
        // Event based coincidence - gate
        std::vector<std::vector<TH1*>> h1_lisafast_deltaT_LaBr_gated;
        std::vector<std::vector<TH2*>> h2_lisafast_deltaT_vs_energy_LaBr_gated;

        // dT window based coincidence
        std::vector<std::vector<TH1*>> h1_lisafast_dTw_LaBr_gated;
        std::vector<std::vector<TH2*>> h2_lisafast_dTw_vs_energy_LaBr_gated;

        std::vector<TCanvas*> c_lisafast_dTw_LaBr_gated;
        std::vector<TCanvas*> c_lisafast_dTw_vs_energy_LaBr_gated;

        TH1* h1_lisafast_dTw_coin_LaBr;
        TH2* h2_lisafast_dTw_vs_energy_coin_LaBr;
        TH2* h2_E1_vs_E2_dTw_coin_all_LaBr;

        TH2* h2_E1_vs_E2_all_LaBr;

        
        // Diamonds
        std::vector<std::vector<std::vector<TH1*>>> h1_lisafast_slowToT_Diamond;
        std::vector<std::vector<std::vector<TH1*>>> h1_lisafast_fastToT_Diamond;
        std::vector<std::vector<std::vector<TH1*>>> h1_lisafast_energy_Diamond;
        std::vector<std::vector<std::vector<TH2*>>> h2_lisafast_fast_v_slow_Diamond;
        std::vector<std::vector<std::vector<TH1*>>> h1_lisafast_abs_time_Diamond;

        TH1* h1_lisafast_hitpattern_slow_Diamond;
        TH1* h1_lisafast_hitpattern_fast_Diamond;        

        TH1* h1_lisafast_multiplicity; 
        
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

        double energygate_width = 20;
            
        int event_multiplicity;

        // rates
        int* detector_counters;
        int* detector_rates;
        int rate_running_count = 0;
         
        float coin_window_ns = 1500.; // move to config
        std::vector<LisaFastCalData> coin_hits;

    public:
        ClassDef(LisaFastOnlineSpectra, 1)
};

#endif
