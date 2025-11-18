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
#include "TBox.h"


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

}


InitStatus H10MCPNearlineSpectra::Init()
{

    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksAnaData");
    c4LOG_IF(fatal, !fHitsMCP, "Branch H10MCPTwinpeaksAnaData not found!");

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_mcp = gDirectory->mkdir("MCPs");
    gDirectory->cd("MCPs");

    dir_Position = dir_mcp->mkdir("Position");
    dir_Energy = dir_mcp->mkdir("Energy");
    dir_Gated = dir_mcp->mkdir("Gated");


    // Time difference
    h1_dT = MakeTH1(dir_mcp, "F", "h1_dT", "dT MCP2 - MCP1", 4000, -100, 100);  
    // Time vs position
    h2_dX1_dT = MakeTH2(dir_mcp,"F", "h2_dX1_dT", " dT vs X12- X11" , 100, -250, 250, 100, -100, 100);
    h2_dY1_dT = MakeTH2(dir_mcp,"F", "h2_dY1_dT", " dT vs Y12- Y11" , 100, -250, 250, 100, -100, 100);
    h2_dX2_dT = MakeTH2(dir_mcp,"F", "h2_dX2_dT", " dT vs X22- X21" , 100, -250, 250, 100, -100, 100);
    h2_dY2_dT = MakeTH2(dir_mcp,"F", "h2_dY2_dT", " dT vs Y22- Y21" , 100, -250, 250, 100, -100, 100);
    
    // HeatMap
    h2_MCP1_HeatMap = MakeTH2(dir_Position,"F", "h2_MCP1_HeatMap", "MCP1 HeatMap" , 500, -250, 250, 500, -250, 250);
    h2_MCP2_HeatMap = MakeTH2(dir_Position,"F", "h2_MCP2_HeatMap", "MCP2 HeatMap" , 500, -250, 250, 500, -250, 250);

    // Position 1D
    h1_dX1 = MakeTH1(dir_Position, "F", "h1_dX1", " X12 - X11", 100, -250, 250); 
    h1_dY1 = MakeTH1(dir_Position, "F", "h1_dY1", " Y12 - Y11", 100, -250, 250); 
    h1_dX2 = MakeTH1(dir_Position, "F", "h1_dX2", " X22 - X21", 100, -250, 250); 
    h1_dY2 = MakeTH1(dir_Position, "F", "h1_dY2", " Y22 - Y21", 100, -250, 250); 

    // Energy 1D - Time channel
    h1_E1 = MakeTH1(dir_Energy, "F", "h1_E1", " E1 MCP1", 1000, 0, 40000); 
    h1_E2 = MakeTH1(dir_Energy, "F", "h1_E2", " E2 MCP2", 1000, 0, 40000); 
    // Energy 1D - Position channels
    h1_E_X11 = MakeTH1(dir_Energy, "F", "h1_E_X11", " E_X11 MCP1", 1000, 0, 40000); 
    h1_E_X12 = MakeTH1(dir_Energy, "F", "h1_E_X12", " E_X12 MCP1", 1000, 0, 40000); 
    h1_E_Y11 = MakeTH1(dir_Energy, "F", "h1_E_Y11", " E_Y12 MCP1", 1000, 0, 40000); 
    h1_E_Y12 = MakeTH1(dir_Energy, "F", "h1_E_Y12", " E_Y12 MCP1", 1000, 0, 40000); 

    h1_E_X21 = MakeTH1(dir_Energy, "F", "h1_E_X21", " E_X11 MCP2", 1000, 0, 40000); 
    h1_E_X22 = MakeTH1(dir_Energy, "F", "h1_E_X22", " E_X12 MCP2", 1000, 0, 40000); 
    h1_E_Y21 = MakeTH1(dir_Energy, "F", "h1_E_Y21", " E_Y12 MCP2", 1000, 0, 40000); 
    h1_E_Y22 = MakeTH1(dir_Energy, "F", "h1_E_Y22", " E_Y12 MCP2", 1000, 0, 40000); 

    // Time vs Energy
    h2_E1_dT = MakeTH2(dir_mcp,"F", "h2_E1_dT", " dT vs E1" , 100, -250, 250, 1000, 0, 40000);
    h2_E2_dT = MakeTH2(dir_mcp,"F", "h2_E2_dT", " dT vs E2" , 100, -250, 250, 1000, 0, 40000);

    // :::Gated Histograms
    //    Legend: Pos1Gate = Gate on the position of MCP1, as a TCut drawn on the heatmap of the MCP1
    //            Pos1Gate = Gate on the position of MCP2, as a TCut drawn on the heatmap of the MCP2
    //            dTGate = Gate on the dT spectrum

    // All of these will prob need to be vectors to get multiple gates
    // Time gated on position
    h1_dT_Pos1Gate = MakeTH1(dir_Gated, "F", "h1_dT_Pos1Gate", " dT Gated on MCP1 Position", 4000, -100, 100);
    h1_dT_Pos2Gate = MakeTH1(dir_Gated, "F", "h1_dT_Pos2Gate", " dT Gated on MCP2 Position", 4000, -100, 100);

    // Energy gated on position
    h1_E1_Pos1Gate = MakeTH1(dir_Gated, "F", "h1_E1_Pos1Gate", " E1 MCP1 Gated on MCP1 Position", 1000, 0, 40000); 
    h1_E2_Pos1Gate = MakeTH1(dir_Gated, "F", "h1_E2_Pos1Gate", " E2 MCP2 Gated on MCP1 Position", 1000, 0, 40000); 
    h1_E2_Pos2Gate = MakeTH1(dir_Gated, "F", "h1_E2_Pos2Gate", " E2 MCP2 Gated on MCP2 Position", 1000, 0, 40000);
    
    h1_E_X11_Pos1Gate = MakeTH1(dir_Gated, "F", "h1_E_X11_Pos1Gate", " E of X11 ch Gated on MCP1 Position", 1000, 0, 40000); 
    h1_E_X12_Pos1Gate = MakeTH1(dir_Gated, "F", "h1_E_X12_Pos1Gate", " E of X12 ch Gated on MCP1 Position", 1000, 0, 40000); 
    h1_E_Y11_Pos1Gate = MakeTH1(dir_Gated, "F", "h1_E_Y11_Pos1Gate", " E of Y11 ch Gated on MCP1 Position", 1000, 0, 40000); 
    h1_E_Y12_Pos1Gate = MakeTH1(dir_Gated, "F", "h1_E_Y12_Pos1Gate", " E of Y12 ch Gated on MCP1 Position", 1000, 0, 40000); 

    h1_E_X21_Pos2Gate = MakeTH1(dir_Gated, "F", "h1_E_X21_Pos2Gate", " E of X21 ch Gated on MCP2 Position", 1000, 0, 40000); 
    h1_E_X22_Pos2Gate = MakeTH1(dir_Gated, "F", "h1_E_X22_Pos2Gate", " E of X22 ch Gated on MCP2 Position", 1000, 0, 40000); 
    h1_E_Y21_Pos2Gate = MakeTH1(dir_Gated, "F", "h1_E_Y21_Pos2Gate", " E of Y21 ch Gated on MCP2 Position", 1000, 0, 40000); 
    h1_E_Y22_Pos2Gate = MakeTH1(dir_Gated, "F", "h1_E_Y22_Pos2Gate", " E of Y22 ch Gated on MCP2 Position", 1000, 0, 40000); 

    // HeatMap gated on positions
    h2_MCP1_HeatMap_Pos2Gate = MakeTH2(dir_Gated,"F", "h2_MCP1_HeatMap_Pos2Gate", "MCP1 HeatMap Gated on MCP2 Position" , 500, -250, 250, 500, -250, 250);
    h2_MCP2_HeatMap_Pos1Gate = MakeTH2(dir_Gated,"F", "h2_MCP2_HeatMap_Pos1Gate", "MCP2 HeatMap Gated on MCP1 Position" , 500, -250, 250, 500, -250, 250);

    // Time vs Energy gated on positions
    h2_E1_dT_Pos1Gate = MakeTH2(dir_Gated,"F", "h2_E1_dT_Pos1Gate", " dT vs E1 gated on MCP1 Position" , 100, -250, 250, 1000, 0, 40000);
    h2_E1_dT_Pos2Gate = MakeTH2(dir_Gated,"F", "h2_E1_dT_Pos2Gate", " dT vs E1 gated on MCP2 Position" , 100, -250, 250, 1000, 0, 40000);
    h2_E1_dT_Pos1Gate_Pos2Gate = MakeTH2(dir_Gated,"F", "h2_E1_dT_Pos1Gate_Pos2Gate", " dT vs E1 gated on MCP1 and MCP2 Positions" , 100, -250, 250, 1000, 0, 40000);

    h2_E2_dT_Pos2Gate = MakeTH2(dir_Gated,"F", "h2_E2_dT_Pos2Gate", " dT vs E2 gated on MCP2 Position" , 100, -250, 250, 1000, 0, 40000);
    h2_E2_dT_Pos1Gate = MakeTH2(dir_Gated,"F", "h2_E2_dT_Pos1Gate", " dT vs E2 gated on MCP1 Position" , 100, -250, 250, 1000, 0, 40000);
    h2_E2_dT_Pos1Gate_Pos2Gate = MakeTH2(dir_Gated,"F", "h2_E2_dT_Pos1Gate_Pos2Gate", " dT vs E2 gated on MCP1 and MCP2 Positions" , 100, -250, 250, 1000, 0, 40000);

    // MCP2 Position gated on MCP1 position and dT gate
    h2_MCP2_HeatMap_Pos1Gate_dTGate = MakeTH2(dir_Gated,"F", "h2_MCP2_HeatMap_Pos1Gate_dTGate", "MCP2 HeatMap Gated on MCP1 Position and dT" , 500, -250, 250, 500, -250, 250);


    // Dennis stuff, unclear
		// MCP2HeatMapgatedMCP1Omiddle = MakeTH2(dir_mcp,"b", "MCP2HeatmapT1", "MCP2HeatmapT2" , 500, -250, 250, 500, -250, 250);
		// MCP2HeatmapgatedMCP1Oup = MakeTH2(dir_mcp,"b", "MCP2HeatmapT1up", "MCP2HeatmapT2" , 500, -250, 250, 500, -250, 250);
		// MCP2HeatmapgatedMCP1Odown = MakeTH2(dir_mcp,"b", "MCP2HeatmapT1down", "MCP2HeatmapT2" , 500, -250, 250, 500, -250, 250);

		// MCP2HeatmapgatedMCP1centermiddle = MakeTH2(dir_mcp,"b", "MCP2HeatmapT1centermiddle", "MCP2HeatmapT2" , 500, -250, 250, 500, -250, 250);
		// MCP2HeatmapgatedMCP1centerup = MakeTH2(dir_mcp,"b", "MCP2HeatmapTcenter1up", "MCP2HeatmapT2" , 500, -250, 250, 500, -250, 250);
		// MCP2HeatmapgatedMCP1centerdown = MakeTH2(dir_mcp,"b", "MCP2HeatmapT1centerdown", "MCP2HeatmapT2" , 500, -250, 250, 500, -250, 250);		

    return kSUCCESS;
    
}

    

void H10MCPNearlineSpectra::Exec(Option_t* option)
{ 
	
    // Dennis stuff -- to be deleted once the gate class is completed
    // T01=1000;
    // T02=-5000;
    // E1=0;
    // X01=1000;
    // X02=-5000;
    // Y01=1000;
    // Y02=-5000;
    // X11=1000;
    // X12=-5000;
    // Y11=1000;
    // Y12=-5000;  
	  
    auto start = std::chrono::high_resolution_clock::now();

    if (fHitsMCP && fHitsMCP->GetEntriesFast() > 0)
    {   

        Long64_t mpc_wr = 0;
        H10MCPTwinpeaksAnaData* hit = (H10MCPTwinpeaksAnaData*)fHitsMCP->At(0);
        if (!hit) return;
        mcp_wr = hit->wr_t;

        if (!hit->full_event) return;

        T1 = hit->T1;
        E1 = hit->E1;
        E_X11 = hit->E_X11;
        E_X12 = hit->E_X12;
        E_Y11 = hit->E_Y11;
        E_Y12 = hit->E_Y12;
        X11 = hit->X11;
        X12 = hit->X12;
        Y11 = hit->Y11;
        Y12 = hit->Y12;
        T2 = hit->T2;
        E2 = hit->E2;
        E_X21 = hit->E_X21;
        E_X22 = hit->E_X22;
        E_Y21 = hit->E_Y21;
        E_Y22 = hit->E_Y22;
        X21 = hit->X21;
        X22 = hit->X22;
        Y21 = hit->Y21;
        Y22 = hit->Y22;


        // :::Time difference
        h1_dT->Fill(T2 - T1);
        // :::Time vs position
        if(X12!=0 && X11!=0)h2_dX1_dT->Fill(X12-X11, T2-T1);
        if(Y12!=0 && Y11!=0)h2_dY1_dT->Fill(Y12-Y11, T2-T1);
        if(X22!=0 && X21!=0)h2_dX2_dT->Fill(X22-X21, T2-T1);
        if(Y22!=0 && Y21!=0)h2_dY2_dT->Fill(Y22-Y21, T2-T1);
        // :::Heat Map
        if(X12!=0 && X11!=0 && Y12!=0 && Y11!=0)h2_MCP1_HeatMap->Fill(X12-X11, Y12-Y11);
        if(X22!=0 && X21!=0 && Y22!=0 && Y21!=0)h2_MCP2_HeatMap->Fill(X22-X21, Y22-Y21);
        // :::Position 1D
        h1_dX1->Fill(X12-X11);
        h1_dY1->Fill(Y12-Y11);
        h1_dX2->Fill(X22-X21);
        h1_dY2->Fill(Y22-Y21);
        // :::Energy 1D
        h1_E1->Fill(E1);
        h1_E2->Fill(E2);

        h1_E_X11->Fill(E_X11);
        h1_E_X12->Fill(E_X12);
        h1_E_Y11->Fill(E_Y11);
        h1_E_Y12->Fill(E_Y12);

        h1_E_X21->Fill(E_X21);
        h1_E_X22->Fill(E_X22);
        h1_E_Y21->Fill(E_Y21);
        h1_E_Y22->Fill(E_Y22);

        // :::Time vs Energy
        if(E1!=0)h2_E1_dT->Fill(E1, T2-T1);
        if(E2!=0)h2_E2_dT->Fill(E2, T2-T1);

        // :::Gated histograms
        // In the gate loop

            // Time gated on MCPx positions
            /*
            h1_dT_Pos1Gate->Fill(T2 - T1);
            h1_dT_Pos2Gate->Fill(T2 - T1);
            */

            // Energy gated on MCPx positions
            /*
            h1_E1_Pos1Gate->Fill(E1);
            h1_E2_Pos1Gate->Fill(E2);
            h1_E2_Pos2Gate->Fill(E2);

            h1_E_X11_Pos1Gate->Fill(E_X11);
            h1_E_X12_Pos1Gate->Fill(E_X12);
            h1_E_Y11_Pos1Gate->Fill(E_Y11);
            h1_E_Y12_Pos1Gate->Fill(E_Y12);
            h1_E_X21_Pos1Gate->Fill(E_X21);
            h1_E_X22_Pos1Gate->Fill(E_X22);
            h1_E_Y21_Pos1Gate->Fill(E_Y21);
            h1_E_Y22_Pos1Gate->Fill(E_Y22);
            */

            // HeatMaps Gated on positions
            /*
            if(X12!=0 && X11!=0 && Y12!=0 && Y11!=0)h2_MCP1_HeatMap_Pos2Gate->Fill(X12-X11, Y12-Y11);
            if(X22!=0 && X21!=0 && Y22!=0 && Y21!=0)h2_MCP2_HeatMap_Pos1Gate->Fill(X22-X21, Y22-Y21);
            */

            // Time vs Energy gated on position
            /*
            if(E1!=0)h2_E1_dT_Pos1Gate->Fill(E1, T2-T1);
            if(E1!=0)h2_E1_dT_Pos2Gate->Fill(E1, T2-T1);

            if(E2!=0)h2_E2_dT_Pos2Gate->Fill(E2, T2-T1);
            if(E2!=0)h2_E2_dT_Pos1Gate->Fill(E2, T2-T1);

            if(E1!=0)h2_E1_dT_Pos1Gate_Pos2Gate->Fill(E1, T2-T1);
            if(E2!=0)h2_E2_dT_Pos1Gate_Pos2Gate->Fill(E2, T2-T1);
            */

            // MCP2 heatmap gated on MCP1 position and dT
            /*
            if(X22!=0 && X21!=0 && Y22!=0 && Y21!=0)h2_MCP2_HeatMap_Pos1Gate_dTGate->Fill(X22-X21, Y22-Y21);
            */


        // 


  
        //GATED - Dennis stuff
        // if (gateBoxT->IsInside(X02-X01, Y02-Y01)) {
        // MCP2HeatMapgatedMCP1Omiddle->Fill(X12-X11,Y12-Y11   );}                                         
        // if (gateBoxT->IsInside(X02-X01+10, Y02-Y01+10)) {

        //   MCP2HeatMapgatedMCP1Oup->Fill(X12-X11,Y12-Y11   );}  
        // if (gateBoxT->IsInside(X02-X01-10, Y02-Y01-10)) {
        // MCP2HeatMapgatedMCP1Odown->Fill(X12-X11,Y12-Y11   );}    
        
        // if (gateBoxcenter->IsInside(X02-X01, Y02-Y01)) {
        // MCP2HeatMapgatedMCP1centermiddle->Fill(X12-X11,Y12-Y11   );}       
	                                  
  	}

    fNEvents++;
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
    
}



void H10MCPNearlineSpectra::FinishEvent()
{
    T1 = 0;
    E1 = 0;
    X11 = 0;
    X12 = 0;
    Y11 = 0;
    Y12 = 0;
    T2 = 0;
    E2 = 0;
    X21 = 0;
    X22 = 0;
    Y21 = 0;
    Y22 = 0;

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
