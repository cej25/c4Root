#ifndef LisaFrsCorrelations_H
#define LisaFrsCorrelations_H

#include "TLisaConfiguration.h"
#include "TFrsConfiguration.h"
#include "TCorrelationsConfiguration.h"
#include "LisaCalData.h"
#include "LisaGate.h"
#include "FrsGate.h"
#include "FrsCalData.h"
#include "FrsHitData.h"

#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TCutG.h"
#include "TFolder.h"
#include "TDirectory.h"
#include <vector>
#include <map>
#include "TString.h"
#include "EventHeader.h"

class EventHeader;
class TH1I;
class TH2I;
class TH2F;
class TH2D;
class LisaCalItem;
class FrsCalTpcItem;
class FrsHitData;
class TLisaConfiguration;
class TFrsConfiguration;
class TCorrelationsConfiguration;
class TFolder;
class TDirectory;
class FrsGate;
class LisaGate;
class TGraph;
class TCanvas;

class LisaFrsCorrelations : public FairTask
{
    public:
        LisaFrsCorrelations();
        LisaFrsCorrelations(std::vector<FrsGate*> fg);
        LisaFrsCorrelations(std::vector<LisaGate*> lg);
        LisaFrsCorrelations(std::vector<FrsGate*> fg, std::vector<LisaGate*> lg);
        LisaFrsCorrelations(const TString& name, Int_t verbose = 1);

        virtual ~LisaFrsCorrelations();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        virtual void FinishTask();

    private:

        TLisaConfiguration const* lisa_config;
        TFrsConfiguration const* frs_config;
        TFRSParameter* frs;
        TCorrelationsConfiguration const* correl_config;
        std::map<std::string, std::vector<int>> Correl;

        std::vector<FrsGate*> FrsGates;
        std::vector<LisaGate*> febex_gates;
        std::vector<LisaGate*> mwd_gates;

        int ncorr = 0;
        int tot_pass_s2s4 = 0;
        int nbreak = 0;
        int nmultihit = 0;
        int nnobreak = 0;
        int aoq = 0;
        int layer1count = 0;
        int layer2count = 0;
        int bothlayerseen = 0;
        bool layer1seen = false;
        bool layer2seen = false;
        int gate1 = 0;
        int gate2 = 0;
        int bothgate = 0;

        int gate_number = 0;
        int mwd_gate_number = 0;

        int pair_count = 0;
        int pair_count_MWD = 0;

        std::vector<LisaCalItem> const* lisaCalArray;
        std::vector<FrsHitItem> const* frsHitArray;
        std::vector<FrsMultiHitItem> const* multihitArray;
        std::vector<FrsCalTpcItem> const* calTpcArray;


        Int_t fNEvents;
        EventHeader const* header;

        // ::: Directories
        TDirectory* dir_corr;
        TDirectory* dir_lisa_frs;

        TDirectory* dir_time;
        
        TDirectory* dir_position;

        TDirectory* dir_energy;
        TDirectory* dir_febex;
        TDirectory* dir_mwd;

        TDirectory* dir_gates;

        TDirectory* dir_gate_LISA;
        TDirectory* dir_gate_LISA_febex;
        TDirectory** dir_LISA_febex_gates;
        TDirectory** dir_LISA_febex_gates_channel;
        TDirectory* dir_gate_LISA_mwd;
        TDirectory** dir_LISA_mwd_gates;
        TDirectory** dir_LISA_mwd_gates_channel;

        TDirectory* dir_gate_FRS;
        TDirectory* dir_gate_FRS_febex;
        TDirectory** dir_FRS_febex_gates;
        TDirectory** dir_FRS_febex_gates_channel;
        TDirectory* dir_gate_FRS_mwd;
        TDirectory** dir_FRS_mwd_gates;
        TDirectory** dir_FRS_mwd_gates_channel;

        TDirectory* dir_gate_LISA_FRS;
        TDirectory* dir_gate_LISA_FRS_febex;
        TDirectory** dir_LISA_FRS_febex_gates;
        TDirectory** dir_LISA_FRS_febex_gates_channel;
        TDirectory* dir_gate_LISA_FRS_mwd;
        TDirectory** dir_LISA_FRS_mwd_gates;
        TDirectory** dir_LISA_FRS_mwd_gates_channel;
        
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
        // Float_t s2_x;
        // Float_t s2_y;
        Float_t energy_MUSIC_21;
        Float_t energy_MUSIC_41;
        Float_t energy_MUSIC_42;

        TString city = "";

        Int_t layer;

        // ::: Histograms
        // ::: Time
        std::vector<TH1I*> h1_wr_diff;

        // ::: Position
        std::vector<TH2F*> h2_TPC_vs_LISA_x;
        std::vector<TH2F*> h2_TPC_vs_LISA_y;

        // ::: Energy - LISA-MUSICs
        std::vector<TH2F*> h2_MUSIC21_vs_LISA_febex;
        std::vector<TH2F*> h2_MUSIC41_vs_LISA_febex;

        std::vector<TH2F*> h2_MUSIC21_vs_LISA_MWD;
        std::vector<TH2F*> h2_MUSIC41_vs_LISA_MWD;

        // ::: Gates
        // ::: Gated - FRS applied on LISA
        // Full sequential gate
        std::vector<TH2F*> h2_LISA_energy_vs_layer_s1s2s4_gated;
        std::vector<TH2F*> h2_LISA_energy_xy_vs_layer_s1s2s4_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_s1s2s4_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_xy_s1s2s4_gated;

        std::vector<TH2F*> h2_LISA_energy_MWD_vs_layer_s1s2s4_gated;
        std::vector<TH2F*> h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_MWD_s1s2s4_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_MWD_xy_s1s2s4_gated;
        
        // only s1s2 gate
        std::vector<TH2F*> h2_LISA_energy_vs_layer_s1s2_gated;
        std::vector<TH2F*> h2_LISA_energy_xy_vs_layer_s1s2_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_s1s2_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_xy_s1s2_gated;

        std::vector<TH2F*> h2_LISA_energy_MWD_vs_layer_s1s2_gated;
        std::vector<TH2F*> h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_MWD_s1s2_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_MWD_xy_s1s2_gated;
        //..............................
        // ::: Gated - LISA applied on FRS
        std::vector<std::vector<TH2F*>> h2_Z21_vs_AoQs1s2_LISA_gated;
        std::vector<std::vector<TH2F*>> h2_Z41_vs_AoQs2s4_LISA_gated;

        std::vector<std::vector<TH2F*>> h2_Z21_vs_AoQs1s2_LISA_MWD_gated;
        std::vector<std::vector<TH2F*>> h2_Z41_vs_AoQs2s4_LISA_MWD_gated;
        //..............................
        // ::: Gated - LISA and FRS applied on LISA
        // Full sequential gate
        std::vector<TH2F*> h2_LISA_energy_vs_layer_LISA_s1s2s4_gated;
        std::vector<TH2F*> h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_LISA_s1s2s4_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_xy_LISA_s1s2s4_gated;

        std::vector<TH2F*> h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated;
        std::vector<TH2F*> h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_MWD_LISA_s1s2s4_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_MWD_xy_LISA_s1s2s4_gated;

        //only s1s2
        std::vector<TH2F*> h2_LISA_energy_vs_layer_LISA_s1s2_gated;
        std::vector<TH2F*> h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_LISA_s1s2_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_xy_LISA_s1s2_gated;

        std::vector<TH2F*> h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated;
        std::vector<TH2F*> h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_MWD_LISA_s1s2_gated;
        std::vector<std::vector<TH1*>> h1_LISA_energy_MWD_xy_LISA_s1s2_gated;

        TH1** h1_tpc_lisa_x;
        TH1** h1_tpc_lisa_y;
        TH2** h2_tpc_x_lisa_x;
        TH2** h2_tpc_y_lisa_y;
        TH2** h2_tpc_xy_LISA;
        TH2* h2_tpc_xy_LISA_001;
        TH2* h2_tpc_xy_LISA_011;
        TH2* h2_tpc_xy_LISA_000;
        TH2* h2_tpc_xy_LISA_010;

        //..............................
        std::set<std::tuple<int, int, int>> excluded;

    public:
        ClassDef(LisaFrsCorrelations, 1)
};

#endif
