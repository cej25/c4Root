#ifndef ImplantationStackCorrelationsOnline_H
#define ImplantationStackCorrelationsOnline_H

// FairRoot
#include "FairTask.h"
#include "TDirectory.h"
#include "TFolder.h"
#include "TFile.h"
#include <vector>
#include "TH1.h"
#include "TClonesArray.h"

// c4
#include "bPlastTwinpeaksCalData.h"
#include "TbPlastConfiguration.h"
#include "TBGOTwinpeaksConfiguration.h"
#include "TGermaniumConfiguration.h"
#include "AidaCalData.h"
#include "AidaData.h"
#include "AidaHitData.h"
#include "TAidaConfiguration.h"

// ROOT
#include "TDirectory.h"
#include "TFolder.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TClonesArray.h"
#include <array>
#include <deque>
#include <map>
#include <vector>

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class TDirectory;

class ImplantationStackCorrelationsOnline : public FairTask
{
    public:
        ImplantationStackCorrelationsOnline();
        ImplantationStackCorrelationsOnline(const TString& name, Int_t verbose = 1);
        
        virtual ~ImplantationStackCorrelationsOnline();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        // HTTP Commands
        virtual void Reset_Histo();


    private:
        // Configs
        TbPlastConfiguration const* bplast_config;
        TAidaConfiguration const* aida_config;
        TBGOTwinpeaksConfiguration const* bgo_conf;
        std::map<std::pair<int, int>, std::pair<int, std::pair<char, char>>> bplast_map;

        // Data
        TClonesArray* fHitbPlastTwinpeaks;
        TClonesArray* fHitBGO;
        std::vector<AidaUnpackAdcItem> const* adcArray;
        std::vector<AidaUnpackFlowItem> const* flowArray;
        std::vector<AidaUnpackScalerItem> const* scalerArray;
        std::vector<AidaCalAdcItem> const* implantCalArray;
        std::vector<AidaCalAdcItem> const* decayCalArray;
        std::vector<AidaHit> const* implantHitArray;
        std::vector<AidaHit> const* decayHitArray;

        EventHeader* header;
        Int_t fNEvents;

        TDirectory* dir_implantationstack_corrs;
        TFolder* histograms;

        std::vector<TH1F*> h1_germanium_energy_bplast_corr;
        TH1F* h1_germanium_energy_bplast_corr_sum;
        
        std::vector<std::pair<int,int>> crystals_to_plot;

        int number_of_detectors_to_plot;


    public:
        ClassDef(ImplantationStackCorrelationsOnline, 1)
};


#endif
