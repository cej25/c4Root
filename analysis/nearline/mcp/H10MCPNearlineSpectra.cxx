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

H10MCPNearlineSpectra::H10MCPNearlineSpectra(std::vector<McpGate*>& fMcpGates)
    : FairTask()
    , fNEvents()
    , header(nullptr)
    , fHitsMCP(NULL)
{    
    mcp_config = TH10MCPConfiguration::GetInstance();
    mcpGates = fMcpGates;
    numberMcpGates = mcpGates.size();
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
    gDirectory->cd("Gated");

    for (const auto gate : mcpGates){
        dir_mcpGates.emplace_back(dir_Gated->mkdir(gate->GetName().Data()));
    }

    // Time difference
    h1_dT = MakeTH1(dir_mcp, "F", "h1_dT", "dT MCP2 - MCP1", 4000, -100, 100);  
    h1_dT->GetXaxis()->SetTitle("#DeltaT of MCPs (ns)");

    // Time vs position
    h2_dX1_dT = MakeTH2(dir_mcp,"F", "h2_dX1_dT", " dT vs X12- X11" , 1000, -250, 250, 100, -100, 100);
    h2_dX1_dT->GetXaxis()->SetTitle("#DeltaX of MCP1");
    h2_dX1_dT->GetYaxis()->SetTitle("#DeltaT of MCPs (ns)");

    h2_dY1_dT = MakeTH2(dir_mcp,"F", "h2_dY1_dT", " dT vs Y12- Y11" , 1000, -250, 250, 100, -100, 100);
    h2_dY1_dT->GetXaxis()->SetTitle("#DeltaY of MCP1");
    h2_dY1_dT->GetYaxis()->SetTitle("#DeltaT of MCPs (ns)");

    h2_dX2_dT = MakeTH2(dir_mcp,"F", "h2_dX2_dT", " dT vs X22- X21" , 1000, -250, 250, 100, -100, 100);
    h2_dX2_dT->GetXaxis()->SetTitle("#DeltaX of MCP2");
    h2_dX2_dT->GetYaxis()->SetTitle("#DeltaT of MCPs (ns)");

    h2_dY2_dT = MakeTH2(dir_mcp,"F", "h2_dY2_dT", " dT vs Y22- Y21" , 1000, -250, 250, 100, -100, 100);
    h2_dY2_dT->GetXaxis()->SetTitle("#DeltaY of MCP2");
    h2_dY2_dT->GetYaxis()->SetTitle("#DeltaT of MCPs (ns)");
    
    // HeatMap
    h2_MCP1_HeatMap = MakeTH2(dir_Position,"F", "h2_MCP1_HeatMap", "MCP1 HeatMap" , 1000, -250, 250, 1000, -250, 250);
    h2_MCP1_HeatMap->GetXaxis()->SetTitle("#DeltaX of MCP1");
    h2_MCP1_HeatMap->GetYaxis()->SetTitle("#DeltaY of MCP1");

    h2_MCP2_HeatMap = MakeTH2(dir_Position,"F", "h2_MCP2_HeatMap", "MCP2 HeatMap" , 1000, -250, 250, 1000, -250, 250);
    h2_MCP2_HeatMap->GetXaxis()->SetTitle("#DeltaX of MCP2");
    h2_MCP2_HeatMap->GetYaxis()->SetTitle("#DeltaY of MCP2");

    // Position 1D
    h1_dX1 = MakeTH1(dir_Position, "F", "h1_dX1", " X12 - X11", 1000, -250, 250);
    h1_dX1->GetXaxis()->SetTitle("#DeltaX1 of MCP1");

    h1_dY1 = MakeTH1(dir_Position, "F", "h1_dY1", " Y12 - Y11", 1000, -250, 250); 
    h1_dY1->GetXaxis()->SetTitle("#DeltaY1 of MCP1");

    h1_dX2 = MakeTH1(dir_Position, "F", "h1_dX2", " X22 - X21", 1000, -250, 250); 
    h1_dX2->GetXaxis()->SetTitle("#DeltaX2 of MCP2");

    h1_dY2 = MakeTH1(dir_Position, "F", "h1_dY2", " Y22 - Y21", 1000, -250, 250); 
    h1_dY2->GetXaxis()->SetTitle("#DeltaY2 of MCP2");

    // Energy 1D - Time channel
    h1_E1 = MakeTH1(dir_Energy, "F", "h1_E1", " E1 MCP1", 1000, 0, 40000);
    h1_E1->GetXaxis()->SetTitle("E of MCP1");
    
    h1_E2 = MakeTH1(dir_Energy, "F", "h1_E2", " E2 MCP2", 1000, 0, 40000); 
    h1_E2->GetXaxis()->SetTitle("E of MCP2");

    // Energy 1D - Position channels
    h1_E_X11 = MakeTH1(dir_Energy, "F", "h1_E_X11", " E_X11 MCP1", 1000, 0, 40000); 
    h1_E_X11->GetXaxis()->SetTitle("E of X11 of MCP1");

    h1_E_X12 = MakeTH1(dir_Energy, "F", "h1_E_X12", " E_X12 MCP1", 1000, 0, 40000); 
    h1_E_X12->GetXaxis()->SetTitle("E of X12 of MCP1");

    h1_E_Y11 = MakeTH1(dir_Energy, "F", "h1_E_Y11", " E_Y12 MCP1", 1000, 0, 40000);
    h1_E_Y11->GetXaxis()->SetTitle("E of Y11 of MCP1");
 
    h1_E_Y12 = MakeTH1(dir_Energy, "F", "h1_E_Y12", " E_Y12 MCP1", 1000, 0, 40000); 
    h1_E_Y12->GetXaxis()->SetTitle("E of Y12 of MCP1");

    h1_E_X21 = MakeTH1(dir_Energy, "F", "h1_E_X21", " E_X11 MCP2", 1000, 0, 40000); 
    h1_E_X21->GetXaxis()->SetTitle("E of X21 of MCP2");

    h1_E_X22 = MakeTH1(dir_Energy, "F", "h1_E_X22", " E_X12 MCP2", 1000, 0, 40000); 
    h1_E_X22->GetXaxis()->SetTitle("E of X22 of MCP2");

    h1_E_Y21 = MakeTH1(dir_Energy, "F", "h1_E_Y21", " E_Y12 MCP2", 1000, 0, 40000); 
    h1_E_Y21->GetXaxis()->SetTitle("E of Y21 of MCP2");

    h1_E_Y22 = MakeTH1(dir_Energy, "F", "h1_E_Y22", " E_Y12 MCP2", 1000, 0, 40000); 
    h1_E_Y22->GetXaxis()->SetTitle("E of Y22 of MCP2");

    // Time vs Energy
    h2_E1_dT = MakeTH2(dir_mcp,"F", "h2_E1_dT", " dT vs E1" , 1000, 0, 4000, 4000,-100, 100);
    h2_E1_dT->GetXaxis()->SetTitle("E of MCP1");
    h2_E1_dT->GetYaxis()->SetTitle("dT of MCPs (ns)");

    h2_E2_dT = MakeTH2(dir_mcp,"F", "h2_E2_dT", " dT vs E2" , 1000, 0, 4000, 4000,-100, 100);
    h2_E2_dT->GetXaxis()->SetTitle("E of MCP2");
    h2_E2_dT->GetYaxis()->SetTitle("#DeltaT of MCPs (ns)");

    // :::Gated Histograms
    //    Legend: Pos1Gate = Gate on the position of MCP1, as a TCut drawn on the heatmap of the MCP1
    //            Pos1Gate = Gate on the position of MCP2, as a TCut drawn on the heatmap of the MCP2
    //            dTGate = Gate on the dT spectrum

    // All of these will prob need to be vectors to get multiple gates
    // Time gated on position
    for (int idx{}; idx < numberMcpGates; ++idx){
        const auto gate = mcpGates[idx];

        h1_dT_Pos1Gate.emplace_back(MakeTH1(dir_mcpGates[idx], "F", "h1_dT_Pos1Gate_"+gate->GetName(), " dT Gated on MCP1 Position ("+gate->GetName()+")", 4000, -100, 100));
        h1_dT_Pos1Gate.back()->GetXaxis()->SetTitle("#DeltaT of MCPs (ns)");

        h1_dT_Pos2Gate.emplace_back(MakeTH1(dir_mcpGates[idx], "F", "h1_dT_Pos2Gate_"+gate->GetName(), " dT Gated on MCP2 Position ("+gate->GetName()+")", 4000, -100, 100));
        h1_dT_Pos2Gate.back()->GetXaxis()->SetTitle("#DeltaT of MCPs (ns)");

        // Energy gated on position
        h1_E1_Pos1Gate.emplace_back(MakeTH1(dir_mcpGates[idx], "F", "h1_E1_Pos1Gate_"+gate->GetName(), " E1 MCP1 Gated on MCP1 Position ("+gate->GetName()+")", 1000, 0, 40000)); 
        h1_E1_Pos1Gate.back()->GetXaxis()->SetTitle("E of MCP1");

        h1_E2_Pos1Gate.emplace_back(MakeTH1(dir_mcpGates[idx], "F", "h1_E2_Pos1Gate_"+gate->GetName(), " E2 MCP2 Gated on MCP1 Position ("+gate->GetName()+")", 1000, 0, 40000)); 
        h1_E2_Pos1Gate.back()->GetXaxis()->SetTitle("E of MCP2");

        h1_E2_Pos2Gate.emplace_back(MakeTH1(dir_mcpGates[idx], "F", "h1_E2_Pos2Gate_"+gate->GetName(), " E2 MCP2 Gated on MCP2 Position ("+gate->GetName()+")", 1000, 0, 40000));
        h1_E2_Pos1Gate.back()->GetXaxis()->SetTitle("E of MCP2");

        h1_E_X11_Pos1Gate.emplace_back(MakeTH1(dir_mcpGates[idx], "F", "h1_E_X11_Pos1Gate_"+gate->GetName(), " E of X11 ch Gated on MCP1 Position ("+gate->GetName()+")", 1000, 0, 40000)); 
        h1_E_X11_Pos1Gate.back()->GetXaxis()->SetTitle("E of X11 of MCP1");

        h1_E_X12_Pos1Gate.emplace_back(MakeTH1(dir_mcpGates[idx], "F", "h1_E_X12_Pos1Gate_"+gate->GetName(), " E of X12 ch Gated on MCP1 Position ("+gate->GetName()+")", 1000, 0, 40000)); 
        h1_E_X12_Pos1Gate.back()->GetXaxis()->SetTitle("E of X12 of MCP1");

        h1_E_Y11_Pos1Gate.emplace_back(MakeTH1(dir_mcpGates[idx], "F", "h1_E_Y11_Pos1Gate_"+gate->GetName(), " E of Y11 ch Gated on MCP1 Position ("+gate->GetName()+")", 1000, 0, 40000)); 
        h1_E_Y11_Pos1Gate.back()->GetXaxis()->SetTitle("E of Y11 of MCP1");

        h1_E_Y12_Pos1Gate.emplace_back(MakeTH1(dir_mcpGates[idx], "F", "h1_E_Y12_Pos1Gate_"+gate->GetName(), " E of Y12 ch Gated on MCP1 Position ("+gate->GetName()+")", 1000, 0, 40000)); 
        h1_E_Y12_Pos1Gate.back()->GetXaxis()->SetTitle("E of Y12 of MCP1");

        h1_E_X21_Pos2Gate.emplace_back(MakeTH1(dir_mcpGates[idx], "F", "h1_E_X21_Pos2Gate_"+gate->GetName(), " E of X21 ch Gated on MCP2 Position ("+gate->GetName()+")", 1000, 0, 40000)); 
        h1_E_X21_Pos2Gate.back()->GetXaxis()->SetTitle("E of X21 of MCP2");

        h1_E_X22_Pos2Gate.emplace_back(MakeTH1(dir_mcpGates[idx], "F", "h1_E_X22_Pos2Gate_"+gate->GetName(), " E of X22 ch Gated on MCP2 Position ("+gate->GetName()+")", 1000, 0, 40000)); 
        h1_E_X22_Pos2Gate.back()->GetXaxis()->SetTitle("E of X22 of MCP2");

        h1_E_Y21_Pos2Gate.emplace_back(MakeTH1(dir_mcpGates[idx], "F", "h1_E_Y21_Pos2Gate_"+gate->GetName(), " E of Y21 ch Gated on MCP2 Position ("+gate->GetName()+")", 1000, 0, 40000)); 
        h1_E_Y21_Pos2Gate.back()->GetXaxis()->SetTitle("E of Y21 of MCP2");

        h1_E_Y22_Pos2Gate.emplace_back(MakeTH1(dir_mcpGates[idx], "F", "h1_E_Y22_Pos2Gate_"+gate->GetName(), " E of Y22 ch Gated on MCP2 Position ("+gate->GetName()+")", 1000, 0, 40000)); 
        h1_E_Y22_Pos2Gate.back()->GetXaxis()->SetTitle("E of Y22 of MCP2");

        // HeatMap gated on positions
        h2_MCP1_HeatMap_Pos2Gate.emplace_back(MakeTH2(dir_mcpGates[idx],"F", "h2_MCP1_HeatMap_Pos2Gate_"+gate->GetName(), "MCP1 HeatMap Gated on MCP2 Position ("+gate->GetName()+")" , 1000, -250, 250, 1000, -250, 250));
        h2_MCP1_HeatMap_Pos2Gate.back()->GetXaxis()->SetTitle("#DeltaX of MCP1");
        h2_MCP1_HeatMap_Pos2Gate.back()->GetYaxis()->SetTitle("#DeltaY of MCP1");

        h2_MCP1_HeatMap_Pos1Gate.emplace_back(MakeTH2(dir_mcpGates[idx],"F", "h2_MCP1_HeatMap_Pos1Gate_"+gate->GetName(), "MCP1 HeatMap Gated on MCP1 Position ("+gate->GetName()+")" , 1000, -250, 250, 1000, -250, 250));
        h2_MCP1_HeatMap_Pos1Gate.back()->GetXaxis()->SetTitle("#DeltaX of MCP1");
        h2_MCP1_HeatMap_Pos1Gate.back()->GetYaxis()->SetTitle("#DeltaY of MCP1");

        h2_MCP2_HeatMap_Pos1Gate.emplace_back(MakeTH2(dir_mcpGates[idx],"F", "h2_MCP2_HeatMap_Pos1Gate_"+gate->GetName(), "MCP2 HeatMap Gated on MCP1 Position ("+gate->GetName()+")" , 1000, -250, 250, 1000, -250, 250));
        h2_MCP2_HeatMap_Pos1Gate.back()->GetXaxis()->SetTitle("#DeltaX of MCP2");
        h2_MCP2_HeatMap_Pos1Gate.back()->GetYaxis()->SetTitle("#DeltaY of MCP2");

        // Time vs Energy gated on positions
        h2_E1_dT_Pos1Gate.emplace_back(MakeTH2(dir_mcpGates[idx],"F", "h2_E1_dT_Pos1Gate_"+gate->GetName(), " dT vs E1 gated on MCP1 Position ("+gate->GetName()+")" , 4000, -100, 100, 1000, 0, 40000));
        h2_E1_dT_Pos1Gate.back()->GetXaxis()->SetTitle("E of MCP1");
        h2_E1_dT_Pos1Gate.back()->GetYaxis()->SetTitle("#DeltaT of MCPs (ns)");

        h2_E1_dT_Pos2Gate.emplace_back(MakeTH2(dir_mcpGates[idx],"F", "h2_E1_dT_Pos2Gate_"+gate->GetName(), " dT vs E1 gated on MCP2 Position ("+gate->GetName()+")" , 4000, -100, 100, 1000, 0, 40000));
        h2_E1_dT_Pos2Gate.back()->GetXaxis()->SetTitle("E of MCP1");
        h2_E1_dT_Pos2Gate.back()->GetYaxis()->SetTitle("#DeltaT of MCPs (ns)");

        h2_E1_dT_Pos1Gate_Pos2Gate.emplace_back(MakeTH2(dir_mcpGates[idx],"F", "h2_E1_dT_Pos1Gate_Pos2Gate", " dT vs E1 gated on MCP1 and MCP2 Positions ("+gate->GetName()+")" , 100, -250, 250, 1000, 0, 40000));
        h2_E1_dT_Pos1Gate_Pos2Gate.back()->GetXaxis()->SetTitle("E of MCP1");
        h2_E1_dT_Pos1Gate_Pos2Gate.back()->GetYaxis()->SetTitle("#DeltaT of MCPs (ns)");

        h2_E2_dT_Pos2Gate.emplace_back(MakeTH2(dir_mcpGates[idx],"F", "h2_E2_dT_Pos2Gate_"+gate->GetName(), " dT vs E2 gated on MCP2 Position ("+gate->GetName()+")" , 4000, -100, 100, 1000, 0, 40000));
        h2_E2_dT_Pos2Gate.back()->GetXaxis()->SetTitle("E of MCP2");
        h2_E2_dT_Pos2Gate.back()->GetYaxis()->SetTitle("#DeltaT of MCPs (ns)");

        h2_E2_dT_Pos1Gate.emplace_back(MakeTH2(dir_mcpGates[idx],"F", "h2_E2_dT_Pos1Gate_"+gate->GetName(), " dT vs E2 gated on MCP1 Position ("+gate->GetName()+")" , 4000, -100, 100, 1000, 0, 40000));
        h2_E2_dT_Pos1Gate.back()->GetXaxis()->SetTitle("E of MCP2");
        h2_E2_dT_Pos1Gate.back()->GetYaxis()->SetTitle("#DeltaT of MCPs (ns)");

        h2_E2_dT_Pos1Gate_Pos2Gate.emplace_back(MakeTH2(dir_mcpGates[idx],"F", "h2_E2_dT_Pos1Gate_Pos2Gate_"+gate->GetName(), " dT vs E2 gated on MCP1 and MCP2 Positions ("+gate->GetName()+")" , 100, -250, 250, 1000, 0, 40000));
        h2_E2_dT_Pos1Gate_Pos2Gate.back()->GetXaxis()->SetTitle("E of MCP2");
        h2_E2_dT_Pos1Gate_Pos2Gate.back()->GetYaxis()->SetTitle("#DeltaT of MCPs (ns)");

        // MCP2 Position gated on MCP1 position and dT gate
        h2_MCP2_HeatMap_Pos1Gate_dTGate.emplace_back(MakeTH2(dir_mcpGates[idx],"F", "h2_MCP2_HeatMap_Pos1Gate_dTGate", "MCP2 HeatMap Gated on MCP1 Position and dT ("+gate->GetName()+")" , 1000, -250, 250, 1000, -250, 250));
        h2_MCP2_HeatMap_Pos1Gate_dTGate.back()->GetXaxis()->SetTitle("#DeltaX of MCP2");
        h2_MCP2_HeatMap_Pos1Gate_dTGate.back()->GetYaxis()->SetTitle("#DeltaY of MCP2");
    
    }

    return kSUCCESS;
    
}

    

void H10MCPNearlineSpectra::Exec(Option_t* option)
{ 
  	  
    auto start = std::chrono::high_resolution_clock::now();
    if (fHitsMCP && fHitsMCP->GetEntriesFast() > 0)
    {   

        Long64_t mpc_wr = 0;
        H10MCPTwinpeaksAnaData* hit = (H10MCPTwinpeaksAnaData*)fHitsMCP->At(0);
        if (!hit) return;
        mcp_wr = hit->wr_t;
        //if (!hit->full_event) return; // EG if both MCPs are not there, then it does not fill histos (for Dennis)
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
        if(X12!=0 && X11!=0)h2_dX1_dT->Fill(X11-X12, T2-T1);
        if(Y12!=0 && Y11!=0)h2_dY1_dT->Fill(Y11-Y12, T2-T1);
        if(X22!=0 && X21!=0)h2_dX2_dT->Fill(X21-X22, T2-T1);
        if(Y22!=0 && Y21!=0)h2_dY2_dT->Fill(Y22-Y21, T2-T1);
        // :::Heat Map
        if(X12!=0 && X11!=0 && Y12!=0 && Y11!=0)h2_MCP1_HeatMap->Fill(X11-X12, Y11-Y12);
        if(X22!=0 && X21!=0 && Y22!=0 && Y21!=0)h2_MCP2_HeatMap->Fill(X21-X22, Y22-Y21);
        // :::Position 1D
        h1_dX1->Fill(X11-X12);
        h1_dY1->Fill(Y11-Y12);
        h1_dX2->Fill(X21-X22);
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
        for (int idx{}; idx < numberMcpGates; ++idx){
            const auto gate = mcpGates[idx];

            //std::cout << gate->GetName().Data() << std::endl;
            // std::cout << "Does MCP1 Exist? (" << gate->Does_mcp1PosDxVsPosDy_Exist() << ") || Does MCP2 Exist? (" << gate->Does_mcp2PosDxVsPosDy_Exist() << ") || Does dt Exist? (" <<gate->Does_deltaTime_Exist() << ")" << std::endl;
            // std::cout << "\n dx1 = " << X11-X12 << " || dx2 = " << Y11-Y12 << " || dx2 = " << X21-X22 << " || dy2 = " << Y22-Y21 << " || dt = " << T2-T1 
            //     << "\nPassed MCP1 (" << gate->Passed_mcp1PosDxVsPosDy(X11-X12, Y11-Y12) << ") || Passed MCP2 (" <<  gate->Passed_mcp2PosDxVsPosDy(X21-X22, Y22-Y21) << ") || Passed dt (" << gate->Passed_deltaTime(T2-T1) << ")" << std::endl;

            // Time gated on MCPx positions
            if (gate->Passed_mcp1PosDxVsPosDy(X11-X12, Y11-Y12)) h1_dT_Pos1Gate[idx]->Fill(T2 - T1);
            if (gate->Passed_mcp2PosDxVsPosDy(X21-X22, Y22-Y21)) h1_dT_Pos2Gate[idx]->Fill(T2 - T1);

            // Energy gated on MCPx positions
            if (gate->Passed_mcp1PosDxVsPosDy(X11-X12, Y11-Y12)) h1_E1_Pos1Gate[idx]->Fill(E1);
            if (gate->Passed_mcp1PosDxVsPosDy(X11-X12, Y11-Y12)) h1_E2_Pos1Gate[idx]->Fill(E2);
            if (gate->Passed_mcp2PosDxVsPosDy(X21-X22, Y22-Y21)) h1_E2_Pos2Gate[idx]->Fill(E2);

            if (gate->Passed_mcp1PosDxVsPosDy(X11-X12, Y11-Y12)) h1_E_X11_Pos1Gate[idx]->Fill(E_X11);
            if (gate->Passed_mcp1PosDxVsPosDy(X11-X12, Y11-Y12)) h1_E_X12_Pos1Gate[idx]->Fill(E_X12);
            if (gate->Passed_mcp1PosDxVsPosDy(X11-X12, Y11-Y12)) h1_E_Y11_Pos1Gate[idx]->Fill(E_Y11);
            if (gate->Passed_mcp1PosDxVsPosDy(X11-X12, Y11-Y12)) h1_E_Y12_Pos1Gate[idx]->Fill(E_Y12);
            if (gate->Passed_mcp2PosDxVsPosDy(X21-X22, Y22-Y21)) h1_E_X21_Pos2Gate[idx]->Fill(E_X21);
            if (gate->Passed_mcp2PosDxVsPosDy(X21-X22, Y22-Y21)) h1_E_X22_Pos2Gate[idx]->Fill(E_X22);
            if (gate->Passed_mcp2PosDxVsPosDy(X21-X22, Y22-Y21)) h1_E_Y21_Pos2Gate[idx]->Fill(E_Y21);
            if (gate->Passed_mcp2PosDxVsPosDy(X21-X22, Y22-Y21)) h1_E_Y22_Pos2Gate[idx]->Fill(E_Y22);

            // HeatMaps Gated on positions
            if(X12!=0 && X11!=0 && Y12!=0 && Y11!=0 && gate->Passed_mcp2PosDxVsPosDy(X21-X22, Y22-Y21)) h2_MCP1_HeatMap_Pos2Gate[idx]->Fill(X11-X12, Y11-Y12);
            if(X12!=0 && X11!=0 && Y12!=0 && Y11!=0 && gate->Passed_mcp1PosDxVsPosDy(X11-X12, Y11-Y12)) h2_MCP1_HeatMap_Pos1Gate[idx]->Fill(X11-X12, Y11-Y12);
            if(X22!=0 && X21!=0 && Y22!=0 && Y21!=0 && gate->Passed_mcp1PosDxVsPosDy(X11-X12, Y11-Y12)) h2_MCP2_HeatMap_Pos1Gate[idx]->Fill(X21-X22, Y22-Y21);

            // Time vs Energy gated on position
            if(E1!=0 && gate->Passed_mcp1PosDxVsPosDy(X11-X12, Y11-Y12)) h2_E1_dT_Pos1Gate[idx]->Fill(E1, T2-T1);
            if(E1!=0 && gate->Passed_mcp2PosDxVsPosDy(X21-X22, Y22-Y21)) h2_E1_dT_Pos2Gate[idx]->Fill(E1, T2-T1);

            if(E2!=0 && gate->Passed_mcp2PosDxVsPosDy(X21-X22, Y22-Y21)) h2_E2_dT_Pos2Gate[idx]->Fill(E2, T2-T1);
            if(E2!=0 && gate->Passed_mcp1PosDxVsPosDy(X11-X12, Y11-Y12)) h2_E2_dT_Pos1Gate[idx]->Fill(E2, T2-T1);

            if(E1!=0 && gate->PassedAllPositions(X11-X12, Y11-Y12, X21-X22, Y22-Y21)) h2_E1_dT_Pos1Gate_Pos2Gate[idx]->Fill(E1, T2-T1);
            if(E2!=0 && gate->PassedAllPositions(X11-X12, Y11-Y12, X21-X22, Y22-Y21)) h2_E2_dT_Pos1Gate_Pos2Gate[idx]->Fill(E2, T2-T1);

            // MCP2 heatmap gated on MCP1 position and dT
            if(X22!=0 && X21!=0 && Y22!=0 && Y21!=0 && gate->Passed_deltaTime(T2-T1))h2_MCP2_HeatMap_Pos1Gate_dTGate[idx]->Fill(X21-X22, Y22-Y21);
        }
	                                  
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
