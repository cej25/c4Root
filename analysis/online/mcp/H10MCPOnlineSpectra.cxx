// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "H10MCPOnlineSpectra.h"
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

H10MCPOnlineSpectra::H10MCPOnlineSpectra() : H10MCPOnlineSpectra("H10MCPOnlineSpectra")
{
    mcp_config = TH10MCPConfiguration::GetInstance();
}

H10MCPOnlineSpectra::H10MCPOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fNEvents(0)
    , header(nullptr)
    , fHitsMCP(NULL)
{    
    mcp_config = TH10MCPConfiguration::GetInstance();
}

H10MCPOnlineSpectra::~H10MCPOnlineSpectra()
{
    // delete
}


InitStatus H10MCPOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitsMCP, "Branch H10MCPTwinpeaksCalData not found!");
    
    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_mcp = new TDirectory("MCPs", "MCPs", "", 0);
    histograms->Add(dir_mcp);

 
    // copy back anything from fatima

    run->GetHttpServer()->RegisterCommand("Reset_MCP_Histos", Form("/Objects/%s/->Reset_Histo()", GetName()));



    return kSUCCESS;
    
}

void H10MCPOnlineSpectra::Reset_Histo() 
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


void H10MCPOnlineSpectra::Exec(Option_t* option)
{   
    
    auto start = std::chrono::high_resolution_clock::now();
    double T01=0;
  double T02=0;
  double E1=0;
  double X01=0;
  double X02=0;
  double Y01=0;
  double Y02=0;
  double X11=0;
  double X12=0;
  double Y11=0;
  double Y12=0;
	  
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

           // std::cout << "NEW HIT :: " << std::endl;
          //  std::cout << "MPC :: " << mcp_id << std::endl;
          //  std::cout << "Type :: " << type << std::endl;
           // std::cout << "Number :: " << number << std::endl;
			if (mcp_id==0 && type==0 && number== 0 ) T01 = hit->Get_fast_lead_time();
			if (mcp_id==1 && type==0 && number== 0 ) T02 = hit->Get_fast_lead_time();
			if (mcp_id==0 && type==1 && number== 0 ) X01 = hit->Get_fast_lead_time();
			if (mcp_id==0 && type==1 && number== 1 ) X02 = hit->Get_fast_lead_time();
			if (mcp_id==0 && type==2 && number== 0 ) Y01 = hit->Get_fast_lead_time();
			if (mcp_id==0 && type==2 && number== 1 ) Y02 = hit->Get_fast_lead_time();
			if (mcp_id==1 && type==1 && number== 0 ) X11 = hit->Get_fast_lead_time();
			if (mcp_id==1 && type==1 && number== 1 ) X12 = hit->Get_fast_lead_time();
			if (mcp_id==1 && type==2 && number== 0 ) Y11 = hit->Get_fast_lead_time();
			if (mcp_id==1 && type==2 && number== 1 ) Y12 = hit->Get_fast_lead_time();
        }
	h1_test_histogram1->Fill(T02 - T01);
	histogram3->Fill(X02-X01, T02-T01);
	MCP1Heatmap1->Fill(X02-X01, Y02-Y01);
	MCP2Heatmap1->Fill(X12-X11, Y12-Y11);
        
        

    }
     



    fNEvents++;
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
    
}



void H10MCPOnlineSpectra::FinishEvent()
{
    // resets and whatever
}

void H10MCPOnlineSpectra::FinishTask()
{
   
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    
}

ClassImp(H10MCPOnlineSpectra)
