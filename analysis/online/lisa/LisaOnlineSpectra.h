#ifndef LisaOnlineSpectra_H
#define LisaOnlineSpectra_H

#include "FairTask.h"
#include "TLisaConfiguration.h"
#include "LisaData.h" // do we need raw?
#include "LisaCalData.h"
#include <vector>
#include <memory>
#include "TDirectory.h"
#include "TFolder.h"
#include "TPad.h"
#include "TH2I.h"
#include "TGraph.h"
#include "TString.h"

//Debugging. Replaced std::string with TString nov24

class LisaCalItem;
class TLisaConfiguration;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TH1I;
class TH2I;
class TFolder;
class TDirectory;


class LisaOnlineSpectra : public FairTask
{
    public:
        LisaOnlineSpectra();
        LisaOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~LisaOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        // range setters

    
    private:
        TLisaConfiguration const* lisa_config;
        // TClonesArray* fHitLisa;

        std::vector<LisaCalItem> const* lisaCalArray;

        // common variables
        int layer_number;
        int det_number;
        int xmax;
        int ymax;
        int num_layers;
        TString city = "";

        Int_t layer;
        Int_t lay;
        Int_t xp;
        Int_t yp;
        float en;
        std::vector<float> trace;
        std::vector<float> trace_MWD;
        
        EventHeader* header;
        Int_t fNEvents;

        // ::: Counter
        std::vector<std::vector<std::vector<int>>> detector_counter; 
        std::vector<std::vector<std::vector<int>>> detector_rate;    
        int rate_running_count = 0;

        // Rate
        Long64_t prev_wr = 0;
        Long64_t wr_diff; 
        Long64_t wr_rate; 
        Long64_t saved_wr =  0; 
        uint64_t wr_time;

        TFolder* histograms;
        TDirectory* dir_lisa;
        TDirectory* dir_stats;
        TDirectory* dir_rates;
        TDirectory* dir_energy;
        TDirectory* dir_febex;
        TDirectory* dir_energy_MWD;
        TDirectory* dir_febex_channel;
        TDirectory* dir_MWD_channel;

        TDirectory* dir_traces;    

        // ::: Canvas
        //     Stats
        std::vector<TCanvas*> c_layer_rates;
        TCanvas* c_hitpattern_layer;
        TCanvas* c_hitpattern_grid;
        TCanvas* c_pileup_grid;
        TCanvas* c_overflow_grid;
        TCanvas* c_multiplicity_per_layer;
        //      Energy
        std::vector<TCanvas*> c_energy_ch;
        TCanvas* c_energy_layer;
        TCanvas* c_energy_vs_ID;
        TCanvas* c_energy_vs_ID_total;
        TCanvas* c_energy_vs_layer;
        TCanvas* c_energy_layer_vs_layer;
        TCanvas* c_energy_first_vs_last;

        std::vector<TCanvas*> c_energy_MWD_ch;
        TCanvas* c_energy_MWD_layer;
        TCanvas* c_energy_MWD_vs_ID;
        TCanvas* c_energy_MWD_vs_layer;
        std::vector<TCanvas*> c_traces_ch;
        TCanvas* c_energy_MWD_layer_vs_layer;
        TCanvas* c_energy_MWD_first_vs_last;
    
        // ::: Histograms
        //     Stats
        TH1I* h1_hitpattern_total;
        TH1I* h1_wr_diff;
        std::vector<std::vector<std::vector<TH1I*>>> h1_rate;
        std::vector<TH1I*> h1_hitpattern_layer;
        std::vector<TH2F*> h2_hitpattern_grid;
        std::vector<TH2F*> h2_pileup_grid;
        std::vector<TH2F*> h2_overflow_grid;
        TH1I* h1_multiplicity;
        std::vector<TH1I*> h1_multiplicity_per_layer; ;
        TH1I* h1_layer_multiplicity;
        // ::: Energy
        //      Febex 
        std::vector<std::vector<std::vector<TH1F*>>> h1_energy_ch;
        std::vector<TH1F*> h1_energy_layer;
        std::vector<TH2F*> h2_energy_vs_ID;
        //TH2F* h2_energy_vs_ID_total;
        TH2F* h2_energy_vs_layer;
        std::vector<TH2F*> h2_energy_layer_vs_layer;
        TH2F* h2_energy_first_vs_last;
        //      MWD  
        std::vector<std::vector<std::vector<TH1F*>>> h1_energy_MWD_ch;
        std::vector<TH1F*> h1_energy_MWD_layer;
        std::vector<TH2F*> h2_energy_MWD_vs_ID;
        TH2F* h2_energy_MWD_vs_layer;
        std::vector<TH2F*> h2_energy_MWD_layer_vs_layer;
        TH2F* h2_energy_MWD_first_vs_last;

        // ::: Traces
        std::vector<std::vector<std::vector<TH1F*>>> h1_traces_ch;        

    public:
        ClassDef(LisaOnlineSpectra, 1)
};

#endif
