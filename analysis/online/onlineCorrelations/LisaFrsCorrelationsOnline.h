#ifndef LisaFrsCorrelationsOnline_H
#define LisaFrsCorrelationsOnline_H

#include "TLisaConfiguration.h"
#include "TFrsConfiguration.h"
#include "TCorrelationsConfiguration.h"
#include "LisaCalData.h"
#include "FrsGate.h"
#include "FrsHitData.h"
#include "EventHeader.h"

#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TCutG.h"
#include "TFolder.h"
#include "TDirectory.h"
#include <vector>
#include <map>

class EventHeader;
class TH1I;
class TH2I;
class TH2F;
class TH2D;
class LisaCalItem;
class FrsHitData;
class TLisaConfiguration;
class TFrsConfiguration;
class TCorrelationsConfiguration;
class TFolder;
class TDirectory;
class FrsGate;
class TGraph;
class TCanvas;

class LisaFrsCorrelationsOnline : public FairTask
{
    public:
        LisaFrsCorrelationsOnline();
        LisaFrsCorrelationsOnline(std::vector<FrsGate*> fg);
        LisaFrsCorrelationsOnline(const TString& name, Int_t verbose = 1);

        virtual ~LisaFrsCorrelationsOnline();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        virtual void FinishTask();
        virtual void Reset_Histo();

    private:

        

        TLisaConfiguration const* lisa_config;
        TFrsConfiguration const* frs_config;
        TFRSParameter* frs;
        TCorrelationsConfiguration const* correl_config;
        std::map<std::string, std::vector<int>> Correl;

        std::vector<FrsGate*> FrsGates;

        std::vector<LisaCalItem> const* lisaCalArray;
        std::vector<FrsHitItem> const* frsHitArray;

        Int_t fNEvents;
        EventHeader* header;

        TFolder* histograms;

        // ::: Directories
        TDirectory* dir_corr;
        TDirectory* dir_lisa_frs;

        TDirectory* dir_time;
        
        TDirectory* dir_position;

        TDirectory* dir_energy;
        TDirectory* dir_febex;
        TDirectory* dir_mwd;
        TDirectory* dir_energy_correlated;
        TDirectory* dir_energy_MWD_correlated;


        // ::: common var
        int layer_number;
        int xmax;
        int ymax;
        int multi_evt = 0;

        int64_t wr_LISA;
        int64_t wr_FRS;
        int64_t wr_travMUSIC;
        int64_t wr_LISA_FRS;
        int64_t wr_LISA_travMUSIC;
        int64_t wr_travMUSIC_FRS;
        Float_t s2_x;
        Float_t s2_y;
        Float_t energy_MUSIC_21;
        Float_t energy_MUSIC_41;
        Float_t energy_MUSIC_42;

        TString city = "";


        Int_t layer;

        //Canvases
        TCanvas* c_wr_diff;
        TCanvas* c_energy_correlated_sci41;
        TCanvas* c_energy_MWD_correlated_sci41;
        TCanvas* c_MUSIC_21_layer;
        TCanvas* c_MUSIC_41_layer;
        TCanvas* c_MUSIC_21_layer_MWD;
        TCanvas* c_MUSIC_41_layer_MWD;
        TCanvas* c_xy_pos_layer1;
        TCanvas* c_xy_pos_layer2;

        TCanvas* c_tpc_x_lisa_x;
        TCanvas* c_tpc_y_lisa_y;
        TCanvas* c_tpc_xy_at_LISA;

        //Histograms
        TH1I* h1_wr_diff;
        TH1I* h1_wr_diff_tpat2;
        TH1I* h1_wr_diff_tpat6;

        std::vector<TH1*> h1_energy_layer_corr_sci41;
        std::vector<TH1*> h1_energy_MWD_layer_corr_sci41;

        std::vector<TH2F*> h2_MUSIC21_vs_LISA_febex;
        std::vector<TH2F*> h2_MUSIC41_vs_LISA_febex;
        std::vector<TH2F*> h2_MUSIC21_vs_LISA_MWD;
        std::vector<TH2F*> h2_MUSIC41_vs_LISA_MWD;

        std::vector<TH2F*> h2_MUSIC_2_layer;
        std::vector<TH2F*> h2_travMUSIC_layer;
        std::vector<TH2F*> h2_xy_pos_layer1;
        std::vector<TH2F*> h2_xy_pos_layer2;

        TH1** h1_tpc_lisa_x;
        TH1** h1_tpc_lisa_y;
        TH2** h2_tpc_x_lisa_x;
        TH2** h2_tpc_y_lisa_y;
        TH2** h2_tpc_xy_LISA;
        TH2* h2_tpc_xy_LISA_001;
        TH2* h2_tpc_xy_LISA_011;
        TH2* h2_tpc_xy_LISA_000;
        TH2* h2_tpc_xy_LISA_010;

        std::set<std::tuple<int, int, int>> excluded;


    public:
        ClassDef(LisaFrsCorrelationsOnline, 1)
};

#endif
