#ifndef FrsTravMusCorrelations_H
#define FrsTravMusCorrelations_H

#include "TFrsConfiguration.h"
#include "TCorrelationsConfiguration.h"
#include "TravMusCalData.h"
#include "TravMusAnaData.h"
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

class EventHeader;
class TH1I;
class TH2I;
class TH2F;
class TH2D;
class FrsHitData;
class TFrsConfiguration;
class TCorrelationsConfiguration;
class TFolder;
class TDirectory;
class FrsGate;
class TGraph;
class TCanvas;

class FrsTravMusCorrelations : public FairTask
{
    public:
        FrsTravMusCorrelations();
        FrsTravMusCorrelations(std::vector<FrsGate*> fg);
        FrsTravMusCorrelations(const TString& name, Int_t verbose = 1);

        virtual ~FrsTravMusCorrelations();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        virtual void FinishTask();

    private:

        
        TFrsConfiguration const* frs_config;
        TCorrelationsConfiguration const* correl_config;
        std::map<std::string, std::vector<int>> Correl;

        std::vector<FrsGate*> FrsGates;

        std::vector<FrsHitItem> const* frsHitArray;
        std::vector<FrsMultiHitItem> const* frsMultihitArray;
        std::vector<TravMusCalItem> const* travMusCalArray;
        std::vector<TravMusAnaItem> const* travMusAnaArray;


        Int_t fNEvents;
        EventHeader* header;

        // Directories
        TDirectory* dir_corr;

        // common var
       

        // Canvases


        // Histograms
        TH2* h2_Z_vs_AoQ_driftcorr_trav_gate;
        TH2* h2_Z_vs_AoQ_tac_trav_gate_driftcorr; // ? ok what the f are these names Elisa
        TH2* h2_Z_vs_AoQ_mhtdc_trav_gate;

    public:
        ClassDef(FrsTravMusCorrelations, 1)
};

#endif
