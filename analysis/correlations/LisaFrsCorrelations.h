#ifndef LisaFrsCorrelations_H
#define LisaFrsCorrelations_H

#include "TLisaConfiguration.h"
#include "TFrsConfiguration.h"
#include "TCorrelationsConfiguration.h"
#include "LisaCalData.h"
#include "LisaGate.h"
#include "FrsGate.h"
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

        int gate_number = 0;
        int mwd_gate_number = 0;

        std::vector<LisaCalItem> const* lisaCalArray;
        std::vector<FrsHitItem> const* frsHitArray;
        std::vector<FrsMultiHitItem> const* multihitArray;


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
        TDirectory* dir_febex_gates;
        TDirectory* dir_febex_LISA;
        TDirectory* dir_febex_FRS;
        TDirectory* dir_febex_FRS_xy;
        TDirectory* dir_febex_LISA_FRS;
        TDirectory* dir_febex_LISA_FRS_xy;

        TDirectory* dir_mwd_gates;
        TDirectory* dir_mwd_LISA;
        TDirectory* dir_mwd_FRS;
        TDirectory* dir_mwd_FRS_xy;
        TDirectory* dir_mwd_LISA_FRS;
        TDirectory* dir_mwd_LISA_FRS_xy;

        // TDirectory* dir_energy;
        // TDirectory* dir_energy_MWD;
        // TDirectory* dir_energy_ch;
        // TDirectory* dir_energy_MWD_ch;

        // TDirectory* dir_corr_driftcorr;
        // TDirectory* dir_energy_ch_driftcorr;
        // TDirectory* dir_energy_MWD_ch_driftcorr;
        
        // ::: common var
        int layer_number;
        int xmax;
        int ymax;
        //int multi_evt = 0;

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
        // Float_t energy_travMUSIC;
        // Float_t energy_travMUSIC_driftcorr;

        TString city = "";

        Int_t layer;

        // ::: Histograms
        // Time
        std::vector<TH1I*> h1_wr_diff;

        // Position

        // Energy - LISA-MUSICs
        std::vector<TH2F*> h2_MUSIC21_vs_LISA_febex;
        std::vector<TH2F*> h2_MUSIC41_vs_LISA_febex;

        std::vector<TH2F*> h2_MUSIC21_vs_LISA_MWD;
        std::vector<TH2F*> h2_MUSIC41_vs_LISA_MWD;

        // std::vector<TH2F*> h2_MUSIC_1_layer_GM;
        // std::vector<TH2F*> h2_MUSIC_2_layer_GM;
        // std::vector<TH2F*> h2_travMUSIC_layer_GM;
        // std::vector<TH2F*> h2_travMUSIC_driftcorr_layer_GM;
        // std::vector<TH2F*> h2_xy_pos_layer1;
        // std::vector<TH2F*> h2_xy_pos_layer2;
        // std::vector<std::vector<std::vector<TH1F*>>> h1_energy_layer_ch_GM;
        // std::vector<std::vector<std::vector<std::vector<TH1F*>>>> h1_energy_ch_GM_PIDgated;
        // std::vector<std::vector<std::vector<std::vector<TH1F*>>>> h1_energy_ch_GM_PIDgated_Trav;
        
        // std::vector<std::vector<TH1F*>> h1_energy_layer_GM_PID_TM;
        // std::vector<std::vector<TH1F*>> h1_energy_layer2_GM_PID_TM_LISA1;


        // ::: Histo for drift corrected FRS
        // std::vector<std::vector<std::vector<std::vector<TH1F*>>>> h1_energy_ch_GM_PID_driftcorr;
        // std::vector<std::vector<std::vector<std::vector<TH1F*>>>> h1_energy_ch_GM_PID_TM_driftcorr;
        // std::vector<std::vector<std::vector<std::vector<TH1F*>>>> h1_energy_ch201_GM_PID_TM_driftcorr_ch101;

        // std::vector<std::vector<TH1F*>> h1_energy_layer_GM_PID_driftcorr;
        // std::vector<std::vector<TH1F*>> h1_energy_layer_GM_PID_TM_driftcorr;
        // std::vector<std::vector<TH1F*>> h1_energy_layer2_GM_PID_TM_driftcorr_LISA1;

        std::set<std::tuple<int, int, int>> excluded;

    public:
        ClassDef(LisaFrsCorrelations, 1)
};

#endif
