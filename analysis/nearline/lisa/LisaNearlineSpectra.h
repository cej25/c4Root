
#ifndef LisaNearlineSpectra_H
#define LisaNearlineSpectra_H

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

        // common variables
        int layer_number;
        int det_number;
        int xmax;
        int ymax;
        int num_layers;
        TString city = "";
        
        std::vector<std::vector<std::vector<int>>> detector_counter;  //ok
        std::vector<std::vector<std::vector<int>>> detector_rate;     //ok
        int rate_running_count = 0; //ok

        EventHeader* header;
        Int_t fNEvents;

        Int_t en_count1 = 0;
        Int_t en_count2 = 0;
        Int_t counter = 0;
        uint64_t wr_time;
        Int_t layer;
        Int_t lay;
        Int_t xp;
        Int_t yp;
        uint32_t en;

        TDirectory* dir_lisa;

        TDirectory* dir_stats;
        TDirectory* dir_rates;

        TDirectory* dir_energy_febex;
        TDirectory* dir_energy_febex_ch;
        TDirectory* dir_energy_MWD;
        TDirectory* dir_energy_MWD_ch;

        TDirectory* dir_traces;
        TDirectory* dir_traces_tokyo;
        
        TDirectory* dir_drift;
        TDirectory* dir_drift_ch;
        TDirectory* dir_drift_tokyo;

        TDirectory* dir_music;
        TDirectory* dir_correlations;

        TDirectory* dir_tokyo;
        

        int64_t prev_wr = 0;
        int64_t wr_diff;
        int64_t wr_rate;
    
        // ::: Histograms

        // ::: Stats
        TH1I* h1_hitpattern_total;
        TH1I* h1_wr_diff; //ok
        std::vector<std::vector<std::vector<TH1I*>>> h1_lisa_rate; //ok

 
        std::vector<TH1I*> h1_hitpattern_layer;
        std::vector<TH2F*> h2_hitpattern_grid;
        std::vector<TH2F*> h2_pileup_grid;
        std::vector<TH2F*> h2_overflow_grid;
        TH1I* h1_evt_multiplicity;
        std::vector<TH1I*> h1_multiplicity_layer; ;
        TH1I* h1_layers_multiplicity;
        //TH2F* h2_hitpattern_grid;
        //TH1F* h1_energy_layer0;

        // Energy for febex and MWD
        std::vector<std::vector<std::vector<TH1F*>>> h1_energy_febex;
        std::vector<std::vector<std::vector<TH1F*>>> h1_energy_MWD;
        std::vector<TH1F*> h1_energy_febex_layer;
        std::vector<TH1F*> h1_energy_MWD_layer;

        // Energy of layers summed or vs
        TH1F* h1_energy_all_layers_GM;
        TH2F* h2_sum_energy_layer1_vs_layer2;
        TH2F* h2_sum_energy_layer1_vs_layer2_GM;
        TH2F* h2_energy_layer1_vs_layer2;
        TH2F* h2_energy_MWD_layer1_vs_layer2_GM;

        // ::: Traces
        std::vector<std::vector<std::vector<TH2F*>>> h2_traces_ch_stat;

        // ::: Drifts
        std::vector<TH2*> h2_energy_layer_vs_time;
        std::vector<TH2*> h2_energy_MWD_layer_vs_time;
        std::vector<std::vector<std::vector<TH2*>>> h2_energy_ch_vs_time;
        std::vector<std::vector<std::vector<TH2*>>> h2_energy_MWD_ch_vs_time;

        

    public:
        ClassDef(LisaNearlineSpectra, 1)
};

#endif
