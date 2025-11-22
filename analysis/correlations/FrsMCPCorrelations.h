#ifndef FrsMCPCorrelations_H
#define FrsMCPCorrelations_H

#include "TH10MCPConfiguration.h"
#include "TFrsConfiguration.h"
#include "FrsGate.h"
#include "FrsCalData.h"
#include "FrsHitData.h"

#include "H10MCPTwinpeaksAnaData.h"


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
        std::vector<FrsGate*> FrsGates;


        std::vector<FrsHitItem> const* frsHitArray;
        std::vector<FrsMultiHitItem> const* multihitArray;

        double E1 = 0;
        double T1 = 0;
        double X11 = 0;
        double X12 = 0;
        double Y11 = 0;
        double Y12 = 0;
        double T2 = 0;
        double X21 = 0;
        double X22 = 0;
        double Y21 = 0;
        double Y22 = 0;
        double SC41 = 0;
        double SC42 = 0;
        double DSSDAccept = 0;

        Int_t fNEvents;
        EventHeader const* header;

        // ::: Directories
        TDirectory* dir_corr;
        TDirectory** dir_frs_gates;

        // ::: Histograms
        std::vector<TH1*> h1_dT_gated_on_frs;
        std::vector<TH2*> h2_MCP1_HeatMap_gated_on_frs;
        std::vector<TH2*> h2_MCP2_HeatMap_gated_on_frs;



    

    public:
        ClassDef(FrsMCPCorrelations, 1)
};

#endif
