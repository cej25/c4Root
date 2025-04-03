// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"

// c4
#include "H10MCPNearlineSpectra.h"
#include "EventHeader.h"

#include "c4Logger.h"
#include "AnalysisTools.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TFile.h"
#include "TRandom.h"
#include <chrono>
#include <sstream>

H10MCPNearlineSpectra::H10MCPNearlineSpectra() : H10MCPNearlineSpectra("H10MCPNearlineSpectra")
{
    mcp_config = TH10MCPConfiguration::GetInstance();
}

H10MCPNearlineSpectra::H10MCPNearlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fNEvents(0)
    , header(nullptr)
    , fHitsMCP(NULL)
{    
    mcp_config = TH10MCPConfiguration::GetInstance();
}

H10MCPNearlineSpectra::~H10MCPNearlineSpectra()
{
    // delete
}


InitStatus H10MCPNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    // FairRunAna * run = FairRunAna::Instance();
    // run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitsMCP, "Branch H10MCPTwinpeaksCalData not found!");
    
    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_mcp = new TDirectory("MCPs", "MCPs", "", 0);
    histograms->Add(dir_mcp);



    return kSUCCESS;
    
}

void H10MCPNearlineSpectra::Reset_Histo() 
{
    c4LOG(info, "Resetting MCP histograms.");

    // Assuming dir is a TDirectory pointer containing histograms
    if (dir_mcp) {
        AnalysisTools_H::ResetHistogramsInDirectory(dir_mcp);
        c4LOG(info, "MCP histograms reset.");
    } else {
        c4LOG(error, "Failed to get list of histograms from directory.");
    }
}


void H10MCPNearlineSpectra::Exec(Option_t* option)
{   
    
    auto start = std::chrono::high_resolution_clock::now();
    
    if (fHitsMCP && fHitsMCP->GetEntriesFast() > 0)
    {   
        Long64_t mpc_wr = 0;
        Int_t nHits = fHitsMCP->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            H10MCPTwinpeaksCalData* hit = (H10MCPTwinpeaksCalData*)fHitsMCP->At(ihit);
            if (!hit) continue;
            mcp_wr = hit->Get_wr_t();

            Int_t mcp_id = hit->Get_mcp_id();
            Int_t type = hit->Get_type();
            Int_t number = hit->Get_number();

            std::cout << "NEW HIT :: " << std::endl;
            std::cout << "MPC :: " << mcp_id << std::endl;
            std::cout << "Type :: " << type << std::endl;
            std::cout << "Number :: " << number << std::endl;

        }

    }
    


    fNEvents++;
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
    
}



void H10MCPNearlineSpectra::FinishEvent()
{
    // resets and whatever
}

void H10MCPNearlineSpectra::FinishTask()
{
   
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    
}

ClassImp(H10MCPNearlineSpectra)
