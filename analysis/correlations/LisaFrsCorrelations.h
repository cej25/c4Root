#ifndef LisaFrsCorrelations_H
#define LisaFrsCorrelations_H

#include "TLisaConfiguration.h"
#include "TFrsConfiguration.h"
#include "TCorrelationsConfiguration.h"
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

    private:

        TLisaConfiguration const* lisa_config;
        TFrsConfiguration const* frs_config;
        TCorrelationsConfiguration const* correl_config;
        std::map<std::string, std::vector<int>> Correl;

        std::vector<FrsGate*> FrsGates;

        std::vector<LisaCalItem> const* lisaCalArray;
        std::vector<FrsHitItem> const* frsHitArray;

        Int_t fNEvents;
        EventHeader* header;

        TFolder* histograms;
        TDirectory* dir_corr;
        TDirectory* dir_lisa_frs;

    public:
        ClassDef(LisaFrsCorrelations, 1)
};

#endif
