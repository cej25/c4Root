/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                        C.E. Jones, D. Bittner                              *
 *                               06.05.25                                     *
 ******************************************************************************/

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

    // fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksCalData");
    // c4LOG_IF(fatal, !fHitsMCP, "Branch H10MCPTwinpeaksCalData not found!");

    fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksAnaData");
    c4LOG_IF(fatal, !fHitsMCP, "Branch H10MCPTwinpeaksAnaData not found!");
    
    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_mcp = new TDirectory("MCPs", "MCPs", "", 0);
    histograms->Add(dir_mcp);

 
    h1_test_histogram = MakeTH1(dir_mcp, "F", "h1_test_histogram", "TEST HIST", 10000, -100, 100);  
	histogram2 = MakeTH2(dir_mcp,"b", "aaa", "test hist" , 100, -250, 250, 100, -100, 100);
	MCP1Heatmap1 = MakeTH2(dir_mcp,"b", "MCP1Heatmap1", "MCP1 Heatmap 1" , 100, -250, 250, 100, -250, 250);
	MCP2Heatmap1 = MakeTH2(dir_mcp,"b", "MCP2Heatmap1", "MCP2 Heatmap 1" , 100, -250, 250, 100, -250, 250);

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
    // double T01=0;
    // double T02=0;
    double E1=0;
    // double X01=0;
    // double X02=0;
    // double Y01=0;
    // double Y02=0;
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
	  
    if (fHitsMCP && fHitsMCP->GetEntriesFast() > 0)
    {   
        Long64_t mpc_wr = 0;
        H10MCPTwinpeaksAnaData* hit = (H10MCPTwinpeaksAnaData*)fHitsMCP->At(0);
        if (!hit) return;
        mcp_wr = hit->wr_t;


        // for (Int_t ihit = 0; ihit < nHits; ihit++)
        // {   
            // H10MCPTwinpeaksCalData* hit = (H10MCPTwinpeaksCalData*)fHitsMCP->At(ihit);
            

            // Int_t mcp_id = hit->Get_mcp_id();
            // Int_t type = hit->Get_type();
            // Int_t number = hit->Get_number();

			// if (mcp_id==0 && type==0 && number== 0 ) T01 = hit->Get_fast_lead_time();
			// if (mcp_id==1 && type==0 && number== 0 ) T02 = hit->Get_fast_lead_time();
			// if (mcp_id==0 && type==1 && number== 0 ) X01 = hit->Get_fast_lead_time();
			// if (mcp_id==0 && type==1 && number== 1 ) X02 = hit->Get_fast_lead_time();
			// if (mcp_id==0 && type==2 && number== 0 ) Y01 = hit->Get_fast_lead_time();
			// if (mcp_id==0 && type==2 && number== 1 ) Y02 = hit->Get_fast_lead_time();
			// if (mcp_id==1 && type==1 && number== 0 ) X11 = hit->Get_fast_lead_time();
			// if (mcp_id==1 && type==1 && number== 1 ) X12 = hit->Get_fast_lead_time();
			// if (mcp_id==1 && type==2 && number== 0 ) Y11 = hit->Get_fast_lead_time();
			// if (mcp_id==1 && type==2 && number== 1 ) Y12 = hit->Get_fast_lead_time();

        // }
        
        // h1_test_histogram->Fill(T02 - T01);
        // histogram2->Fill(X02-X01, T02-T01);
        // MCP1Heatmap1->Fill(X02-X01, Y02-Y01);
        // MCP2Heatmap1->Fill(X12-X11, Y12-Y11);

        if (!hit->full_event) return;

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

        h1_test_histogram->Fill(T2 - T1);
        histogram2->Fill(X12-X11, T2-T1);
        MCP1Heatmap1->Fill(X12-X11, Y12-Y11);
        MCP2Heatmap1->Fill(X22-X21, Y22-Y21);

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
