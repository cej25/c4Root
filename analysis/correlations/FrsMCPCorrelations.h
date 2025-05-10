#ifndef FrsMCPCorrelations_H
#define FrsMCPCorrelations_H

#include "TH10MCPConfiguration.h"
#include "TFrsConfiguration.h"
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
class TH1;
class TH2;
class FrsCalTpcItem;
class FrsHitData;
class TFrsConfiguration;
class TFolder;
class TDirectory;
class FrsGate;
class TGraph;
class TCanvas;

class FrsMCPCorrelations : public FairTask
{
    public:
        FrsMCPCorrelations();
        FrsMCPCorrelations(std::vector<FrsGate*> fg);
        // MCP gate
        FrsMCPCorrelations(const TString& name, Int_t verbose = 1);

        virtual ~FrsMCPCorrelations();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        virtual void FinishTask();

    private:

        const TH10MCPConfiguration* mcp_config;
        TFrsConfiguration const* frs_config;
        TFRSParameter* frs;
        TClonesArray* fHitsMCP;

        std::vector<FrsHitItem> const* frsHitArray;
        std::vector<FrsMultiHitItem> const* multihitArray;


        Int_t fNEvents;
        EventHeader const* header;

        // ::: Directories
        TDirectory* dir_corr;
    

    public:
        ClassDef(FrsMCPCorrelations, 1)
};

#endif
