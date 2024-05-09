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
        std::string city = "";
        

        EventHeader* header;
        Int_t fNEvents;

        Int_t en_count = 0;
        Int_t counter = 0;
        uint64_t wr_time;

        TFolder* histograms;
        TDirectory* dir_lisa;
        TDirectory* dir_energy;
        TDirectory* dir_traces;
        TDirectory* dir_stats;
        TDirectory* dir_music;
        TDirectory* dir_correlations;
        

        // Canvas
        TCanvas* c_hitpattern_layer;
        TCanvas* c_multiplicity_layer;
        TCanvas* c_hitpattern_grid;
        TCanvas* c_pileup_grid;
        TCanvas* c_overflow_grid;
        TCanvas* c_energy_layer1_vs_layer2;
        TCanvas* c_energy_layer_vs_time;
        std::vector<TCanvas*> c_energy_layer_ch;
        std::vector<TCanvas*> c_traces_layer_ch;
    
        // Histograms
        TH1I* h1_hitpattern_total;
        std::vector<TH1I*> h1_hitpattern_layer;
        std::vector<TH2F*> h2_hitpattern_grid;
        std::vector<TH2F*> h2_pileup_grid;
        std::vector<TH2F*> h2_overflow_grid;
        TH1I* h1_multiplicity;
        std::vector<TH1I*> h1_multiplicity_layer; 
        //TH2F* h2_hitpattern_grid;
        //TH1F* h1_energy_layer0;
        std::vector<std::vector<std::vector<TH1F*>>> h1_energy_layer_ch;
        TH2F* h2_energy_layer1_vs_layer2;
        std::vector<std::vector<std::vector<TH1F*>>> h1_traces_layer_ch;

        //TGraph
        std::vector<TGraph*> hG_energy_layer_vs_time;

        

    public:
        ClassDef(LisaOnlineSpectra, 1)
};

#endif
