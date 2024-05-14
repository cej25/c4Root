#ifndef LisaFrsCorrelations_H
#define LisaFrsCorrelations_H

#include "TLisaConfiguration.h"
#include "TFrsConfiguration.h"
#include "TCorrelationsConfiguration.h"
#include "FrsTravMusCalData.h"
#include "LisaCalData.h"
#include "../../config/setup.h"
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

class LisaFrsCorrelations : public FairTask
{
    public:
        LisaFrsCorrelations();
        LisaFrsCorrelations(std::vector<FrsGate*> fg);
        LisaFrsCorrelations(const TString& name, Int_t verbose = 1);

        virtual ~LisaFrsCorrelations();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        virtual void FinishTask();
        virtual void Reset_Histo();

    private:

        

        TLisaConfiguration const* lisa_config;
        TFrsConfiguration const* frs_config;
        TCorrelationsConfiguration const* correl_config;
        std::map<std::string, std::vector<int>> Correl;

        std::vector<FrsGate*> FrsGates;

        std::vector<LisaCalItem> const* lisaCalArray;
        std::vector<FrsHitItem> const* frsHitArray;
        std::vector<FrsTravMusCalItem> const* travMusicArray;

        Int_t fNEvents;
        EventHeader* header;

        TFolder* histograms;
        TDirectory* dir_corr;
        TDirectory* dir_lisa_frs;

        //common var
        int layer_number;

        int64_t wr_LISA;
        int64_t wr_FRS;
        int64_t wr_travMUSIC;
        int64_t wr_LISA_FRS;
        int64_t wr_LISA_travMUSIC;
        int64_t wr_travMUSIC_FRS;
        Float_t s2_x;
        Float_t s2_y;
        Float_t energy_MUSIC_1;
        Float_t energy_MUSIC_2;
        Float_t energy_travMUSIC;

        Int_t layer;

        //Canvases
        TCanvas* c_wr_diff;
        TCanvas* c_MUSIC_1_layer;
        TCanvas* c_MUSIC_2_layer;
        TCanvas* c_travMUSIC_layer;
        TCanvas* c_xy_pos_layer1;
        TCanvas* c_xy_pos_layer2;

        //Histograms
        std::vector<TH1I*> h1_wr_diff;
        std::vector<TH2F*> h2_MUSIC_1_layer;
        std::vector<TH2F*> h2_MUSIC_2_layer;
        std::vector<TH2F*> h2_travMUSIC_layer;
        std::vector<TH2F*> h2_xy_pos_layer1;
        std::vector<TH2F*> h2_xy_pos_layer2;

    public:
        ClassDef(LisaFrsCorrelations, 1)
};

#endif
