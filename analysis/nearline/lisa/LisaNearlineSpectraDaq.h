#ifndef LisaNearlineSpectraDaq_H
#define LisaNearlineSpectraDaq_H

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

//Debugging. Replaced std::string with TString 8nov24



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


class LisaNearlineSpectraDaq : public FairTask
{
    public:
        LisaNearlineSpectraDaq();
        LisaNearlineSpectraDaq(const TString& name, Int_t verbose = 1);

        virtual ~LisaNearlineSpectraDaq();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

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
        

        EventHeader const* header;
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
        TDirectory* dir_energy;
        TDirectory* dir_febex;
        TDirectory* dir_febex_channel;
        TDirectory* dir_energy_MWD;
        TDirectory* dir_MWD_channel;
        TDirectory* dir_traces;
        TDirectory* dir_stats;
        TDirectory* dir_music;
        TDirectory* dir_correlations;
        TDirectory* dir_drift;
        

        int64_t prev_wr = 0;
        int64_t wr_diff;

    
        // Histograms
        TH1I* h1_hitpattern_total;
        TH1I* h1_wr_diff;
        std::vector<TH1I*> h1_hitpattern_layer;
        std::vector<TH2F*> h2_hitpattern_grid;
        std::vector<TH2F*> h2_pileup_grid;
        std::vector<TH2F*> h2_overflow_grid;
        TH1I* h1_multiplicity;
        std::vector<TH1I*> h1_multiplicity_layer; ;
        TH1I* h1_layer_multiplicity;
        std::vector<std::vector<std::vector<TH1F*>>> h1_energy_ch;
        std::vector<TH1*> h1_energy_layer;
        std::vector<std::vector<std::vector<TH1F*>>> h1_energy_MWD_ch;
        std::vector<TH1*> h1_energy_MWD_layer;
        //std::vector<std::vector<std::vector<TH1F*>>> h1_traces_layer_ch;
        std::vector<std::vector<std::vector<TH2F*>>> h2_traces_layer_ch;
        
        std::vector<std::vector<std::vector<TH2*>>> h2_energy_ch_vs_evtno;
        std::vector<std::vector<std::vector<TH2*>>> h2_energy_MWD_ch_vs_evtno;
        std::vector<TH2F*> h2_energy_layer_vs_evtno;
        
        

    public:
        ClassDef(LisaNearlineSpectraDaq, 1)
};

#endif
