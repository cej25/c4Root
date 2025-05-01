
#ifndef LisaNearlineSpectra_H
#define LisaNearlineSpectra_H

#include "FairTask.h"
#include "TLisaConfiguration.h"
#include "LisaData.h" // do we need raw?
#include "LisaCalData.h"
#include <vector>
#include <memory>
#include <sstream>
#include <string>
#include "TDirectory.h"
#include "TFolder.h"
#include "TPad.h"
#include "TH2I.h"
#include "TGraph.h"
#include "TString.h"
#include "TExperimentConfiguration.h"


//Debugging. Replaced std::string with TString 8nov24



class LisaCalItem;
class TLisaConfiguration;
class TExperimentConfiguration;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TH1I;
class TH2I;
class TFolder;
class TDirectory;
class TH2;
class TH1;


class LisaNearlineSpectra : public FairTask
{
    public:
        LisaNearlineSpectra();
        LisaNearlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~LisaNearlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        // range setters

    
    private:
        TLisaConfiguration const* lisa_config;
        TExperimentConfiguration const* exp_config;

        // TClonesArray* fHitLisa;

        std::vector<LisaCalItem> const* lisaCalArray;

        // Variables for Gates
        std::map<int, std::vector<std::tuple<std::string, double, double>>> gates_LISA_febex;
        std::map<int, std::vector<std::tuple<std::string, double, double>>> gates_LISA_MWD;

        // common variables
        int layer_number;
        int det_number;
        int xmax;
        int ymax;
        int num_layers;
        uint64_t wr_time;
        Int_t layer;
        TString city = "";
        EventHeader* header;
        Int_t fNEvents;
        
        // counters
        std::vector<std::vector<std::vector<int>>> detector_counter; 
        std::vector<std::vector<std::vector<int>>> detector_rate;    
        int rate_running_count = 0; 

        // Rates
        Long64_t prev_wr = 0;
        Long64_t wr_diff; 
        Long64_t wr_rate; 
        Long64_t saved_wr =  0; 

        // ::: Directories
        TDirectory* dir_lisa;

        //  Stats
        TDirectory* dir_stats;
        TDirectory* dir_rates;
        //  Energy
        TDirectory* dir_energy;
        TDirectory* dir_febex;
        TDirectory* dir_energy_MWD;
        TDirectory* dir_febex_channel;
        TDirectory* dir_MWD_channel;
        //  Traces
        TDirectory* dir_traces;
        //  Drift
        TDirectory* dir_drift;
        TDirectory* dir_febex_drift;
        TDirectory* dir_febex_ch_drift;
        TDirectory* dir_MWD_drift;
        TDirectory* dir_MWD_ch_drift;
        //  Gates LISA only
        TDirectory* dir_gates;

        std::map<std::string, TDirectory*> dirs_gate_file;
        std::map<std::string, TDirectory*> dirs_gate_febex;
        std::map<std::string, TDirectory*> dirs_gate_mwd;
        std::map<std::string, TDirectory*> dirs_gate_febex_channel;
        std::map<std::string, TDirectory*> dirs_gate_mwd_channel;
        TDirectory* dir_febex_gates;
        TDirectory* dir_MWD_gates;
        TDirectory* dir_febex_gates_channel;
        TDirectory* dir_MWD_gates_channel;

        // ::: Histograms :::
        // ::: Stats
        TH1I* h1_wr_diff; 
        std::vector<std::vector<std::vector<TH1I*>>> h1_lisa_rate; 
        TH1I* h1_hitpattern_total;
        std::vector<TH1I*> h1_hitpattern_layer;
        std::vector<TH2F*> h2_hitpattern_grid;
        std::vector<TH2F*> h2_pileup_grid;
        std::vector<TH2F*> h2_overflow_grid;
        TH1I* h1_multiplicity;
        std::vector<TH1I*> h1_multiplicity_per_layer; ;
        TH1I* h1_layer_multiplicity;

        //  ::: Energy
        //      Febex
        std::vector<std::vector<std::vector<TH1F*>>> h1_energy_ch;
        std::vector<TH1F*> h1_energy_layer;
        std::vector<TH2F*> h2_energy_vs_ID;
        TH2F* h2_energy_vs_ID_total;
        TH2F* h2_energy_vs_layer;
        std::vector<TH2F*> h2_energy_layer_vs_layer;
        TH2F* h2_energy_first_vs_last;
        //      - Gated
        std::vector<std::vector<TH1F*>> h1_energy_layer_gated; 
        std::vector<std::vector<TH1F*>> h1_energy_xy_gated;
        //std::vector<TH1F*> h1_energy_layer_gated;
        //std::vector<TH1F*> h1_energy_xy_gated;
        
        //      MWD
        std::vector<std::vector<std::vector<TH1F*>>> h1_energy_MWD_ch;
        std::vector<TH1F*> h1_energy_MWD_layer;
        std::vector<TH2F*> h2_energy_MWD_vs_ID_layer;
        TH2F* h2_energy_MWD_vs_layer;
        std::vector<TH2F*> h2_energy_MWD_layer_vs_layer;
        TH2F* h2_energy_MWD_first_vs_last;
        //      - Gated
        std::vector<std::vector<TH1F*>> h1_energy_MWD_layer_gated;
        std::vector<std::vector<TH1F*>> h1_energy_MWD_xy_gated;
        //std::vector<TH1F*> h1_energy_MWD_layer_gated;
        //std::vector<TH1F*> h1_energy_MWD_xy_gated;

        // ::: Traces
        std::vector<std::vector<std::vector<TH2F*>>> h2_traces_ch;

        // ::: Drifts
        std::vector<TH2*> h2_energy_layer_vs_time;
        std::vector<TH2*> h2_energy_MWD_layer_vs_time;
        std::vector<std::vector<std::vector<TH2*>>> h2_energy_ch_vs_time;
        std::vector<std::vector<std::vector<TH2*>>> h2_energy_MWD_ch_vs_time;

        

    public:
        ClassDef(LisaNearlineSpectra, 1)
};

#endif
