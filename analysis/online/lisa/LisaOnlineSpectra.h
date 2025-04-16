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
        // Int_t en_count1 = 0;
        // Int_t en_count2 = 0;
        // Int_t en_count3 = 0;
        // Int_t en_count4 = 0;
        // Int_t counter = 0;

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
        // TDirectory* dir_energy;
        // TDirectory* dir_energy_MWD;
        // TDirectory* dir_traces;
        // TDirectory* dir_traces_MWD;
    

        // Canvas
        std::vector<TCanvas*> c_layer_rates;
        // TCanvas* c_hitpattern_layer;
        // TCanvas* c_multiplicity_layer;
        // TCanvas* c_hitpattern_grid;
        // TCanvas* c_pileup_grid;
        // TCanvas* c_overflow_grid;
        // TCanvas* c_energy_layer1_vs_layer2;
        // TCanvas* c_energy_layer_vs_time;
        // std::vector<TCanvas*> c_energy_layer_ch;
        // std::vector<TCanvas*> c_energy_layer_ch_vs_time;
        // std::vector<TCanvas*> c_traces_layer_ch;
        // std::vector<TCanvas*> c_traces_layer_ch_stat;

    
        // Histograms
        // TH1I* h1_hitpattern_total;
        TH1I* h1_wr_diff;
        std::vector<std::vector<std::vector<TH1I*>>> h1_rate;
        // std::vector<TH1I*> h1_hitpattern_layer;
        // std::vector<TH2F*> h2_hitpattern_grid;
        // std::vector<TH2F*> h2_pileup_grid;
        // std::vector<TH2F*> h2_overflow_grid;
        // TH1I* h1_multiplicity;
        // std::vector<TH1I*> h1_multiplicity_layer; ;
        // TH1I* h1_layer_multiplicity;
        // //TH2F* h2_hitpattern_grid;
        // //TH1F* h1_energy_layer0;
        // std::vector<std::vector<std::vector<TH1F*>>> h1_energy_layer_ch;
        // TH2F* h2_energy_layer1_vs_layer2;
        // std::vector<std::vector<std::vector<TH1F*>>> h1_traces_layer_ch;
        // std::vector<std::vector<std::vector<TH2F*>>> h2_traces_layer_ch_stat;


        //TGraph
        // std::vector<TGraph*> hG_energy_layer_vs_time;
        // std::vector<std::vector<std::vector<TGraph*>>> hG_energy_layer_ch_vs_time;

        

    public:
        ClassDef(LisaOnlineSpectra, 1)
};

#endif
