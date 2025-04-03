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
    , fHitsMCP(new TC)
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

    // FairRunAna* run = FairRunAna::Instance();
    // run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitsMCP, "Branch H10MCPTwinpeaksCalData not found!");
    
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_mcp = gDirectory->mkdir("MCPs");
    gDirectory->cd("MCPs");

    h1_test_histogram = MakeTH1(dir_mcp, "F", "h1_test_histogram", "TEST HIST", 100, 0, 100);

    return kSUCCESS;
    
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
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_mcp->Write();
    gDirectory = tmp;
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    
}

ClassImp(H10MCPNearlineSpectra)
