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

    fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksAnaData");
    c4LOG_IF(fatal, !fHitsMCP, "Branch H10MCPTwinpeaksAnaData not found!");
    
    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_mcp = new TDirectory("MCPs", "MCPs", "", 0);
    histograms->Add(dir_mcp);

 	
    h1_dT = MakeTH1(dir_mcp, "F", "h1_dT", "Time Difference T2-T1", 10000, -100, 100,"dt [ns]", kPink, kBlack);  
    h2_dX1_dT = MakeTH2(dir_mcp, "F", "h2_dX1_dT", "X12-X11 position vs Time Difference T2-T1", 100, -250, 250, 100, -100, 100);
    h2_dY1_dT = MakeTH2(dir_mcp, "F", "h2_dY1_dT", "Y12-Y11 position vs Time Difference T2-T1", 100, -250, 250, 100, -100, 100); 
    h2_dX2_dT = MakeTH2(dir_mcp, "F", "h2_dX2_dT", "X22-X21 position vs Time Difference T2-T1", 100, -250, 250, 100, -100, 100); 
    h2_dY2_dT = MakeTH2(dir_mcp, "F", "h2_dY2_dT", "Y22-Y21 position vs Time Difference T2-T1", 100, -250, 250, 100, -100, 100); 
    	
    	
	MCP1Heatmap1 = MakeTH2(dir_mcp,"b", "MCP1Heatmap1", "MCP1 Heatmap 1" , 100, -250, 250, 100, -250, 250); 
	MCP2Heatmap1 = MakeTH2(dir_mcp,"b", "MCP2Heatmap1", "MCP2 Heatmap 1" , 100, -250, 250, 100, -250, 250); 

    h1_sc41_mcp1 = MakeTH1(dir_mcp, "I", "h1_sc41_mcp1", "SC41-MCP1 Time", 4000, 0, 1000,"dt [ns]", kSpring, kBlack);
    h1_sc41_mcp2 = MakeTH1(dir_mcp, "I", "h1_sc41_mcp2", "SC41-MCP2 Time", 4000, 0, 1000,"dt [ns]", kSpring, kBlack);
    h1_sc42_mcp1 = MakeTH1(dir_mcp, "I", "h1_sc42_mcp1", "SC42-MCP1 Time", 4000, 0, 1000,"dt [ns]", kSpring, kBlack);
    h1_sc42_mcp2 = MakeTH1(dir_mcp, "I", "h1_sc42_mcp2", "SC42-MCP2 Time", 4000, 0, 1000,"dt [ns]", kSpring, kBlack);
    h1_sc41_sc42 = MakeTH1(dir_mcp, "I", "h1_sc41_sc42", "SC41-SC42 Time", 1000, -10, 10,"dt [ns]", kCyan, kBlack);
    h1_stefan_mcp1 = MakeTH1(dir_mcp, "I", "h1_stefan_mcp1", "STEFAN-MCP1 Time", 4000,0, 1000,"dt [ns]", kOrange, kBlack);
    h1_stefan_mcp2 = MakeTH1(dir_mcp, "I", "h1_stefan_mcp2", "STEFAN-MCP2 Time", 4000, 0, 1000,"dt [ns]", kOrange, kBlack);
    h1_stefan_sc41 = MakeTH1(dir_mcp, "I", "h1_stefan_sc41", "STEFAN-SC41 Time", 4000,0, 1000,"dt [ns]", kOrange, kBlack);
    h1_stefan_sc42 = MakeTH1(dir_mcp, "I", "h1_stefan_sc42", "STEFAN-SC42 Time", 4000, 0, 1000,"dt [ns]", kOrange, kBlack);
	//gStyle->SetPalette(kBlueRedYellow);
    run->GetHttpServer()->RegisterCommand("Reset_MCP_Histos", Form("/Objects/%s/->Reset_Histo()", GetName()));
	
	mcp_hists = new TCanvas("mcp_hists","MCP histos",650,350);
    mcp_hists->Divide(2,2);
    mcp_hists->cd(1);
    MCP1Heatmap1->Draw();
    mcp_hists->cd(2);
    MCP2Heatmap1->Draw();
    mcp_hists->cd(3);
    h1_dT->Draw();
    mcp_hists->cd(4);
    h1_stefan_mcp1->Draw();
    mcp_hists->SetLogy();
	

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
    double E1=0;
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


    if (fHitsMCP && fHitsMCP->GetEntriesFast() > 0)
    {   
    
        for(int ihit=0; ihit < fHitsMCP->GetEntriesFast(); ++ihit) 
        {
            Long64_t mpc_wr = 0;
            H10MCPTwinpeaksAnaData* hit = (H10MCPTwinpeaksAnaData*)fHitsMCP->At(ihit);
            if (!hit) return;
            mcp_wr = hit->wr_t;

            // if (!hit->full_event) return;        
        
            T1 = hit->T1;
            X11 = hit->X11;
            X12 = hit->X12;
            Y11 = hit->Y11;
            Y12 = hit->Y12;
            T2 = hit->T2;
            X21 = hit->X21;
            X22 = hit->X22;
            Y21 = hit->Y21;
            Y22 = hit->Y22;
            SC41 = hit->SC41;
            SC42 = hit->SC42;
            DSSDAccept = hit->DSSDAccept;

            //if (SC41 > 0)
        // {
            if(SC41!=0 && T1!=0) h1_sc41_mcp1->Fill(SC41-T1);
            if(SC41!=0 && T2!=0) h1_sc41_mcp2->Fill(SC41-T2); 
            //}
            //if (SC42 > 0)
        // {
            if(SC42!=0 && T1!=0) h1_sc42_mcp1->Fill(SC42-T1);
            if(SC42!=0 && T2!=0) h1_sc42_mcp2->Fill(SC42-T2);  
        // }
            if(SC42!=0 && SC41!=0) h1_sc41_sc42->Fill(SC41-SC42);
            h1_dT->Fill(T2 - T1);
        
            if(X12!=0 && X11!=0) h2_dX1_dT->Fill(X12-X11, T2-T1);
            if(Y12!=0 && Y11!=0) h2_dY1_dT->Fill(Y12-Y11, T2-T1);
            if(X22!=0 && X21!=0) h2_dX2_dT->Fill(X22-X21, T2-T1);
            if(Y22!=0 && Y21!=0) h2_dY2_dT->Fill(Y22-Y21, T2-T1);
            
            if(T1!=0 && DSSDAccept!=0) h1_stefan_mcp1->Fill(DSSDAccept-T1);
            if(T2!=0 && DSSDAccept!=0) h1_stefan_mcp2->Fill(DSSDAccept-T2);
            
            if(SC41!=0 && DSSDAccept!=0) h1_stefan_sc41->Fill(DSSDAccept-T1);
            if(SC42!=0 && DSSDAccept!=0) h1_stefan_sc42->Fill(DSSDAccept-T2);
            
            if(X12!=0 && X11!=0 && Y12!=0 && Y11!=0) MCP1Heatmap1->Fill(X12-X11, Y12-Y11);
            if(X22!=0 && X21!=0 && Y22!=0 && Y21!=0) MCP2Heatmap1->Fill(X22-X21, Y22-Y21);
        }
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
