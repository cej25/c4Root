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
 *                         C.E. Jones, E.G. Gandolfo                          *
 *                               24.11.25                                     *
 ******************************************************************************/

// ::: Note::: No canvases in Nearline Tasks please :::

#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairTask.h"

#include "FrsMCPCorrelations.h"
#include "c4Logger.h"
#include "TFile.h"
#include "THttpServer.h"
#include "TCanvas.h"

// c4
#include "EventHeader.h"
#include "c4Logger.h"
#include "AnalysisTools.h"

#include "TCanvas.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <string>
#include "TColor.h"
#include "TStyle.h"

FrsMCPCorrelations::FrsMCPCorrelations() 
    : FrsMCPCorrelations("FrsMCPCorrelations")
{
    mcp_config = TH10MCPConfiguration::GetInstance();
}

FrsMCPCorrelations::FrsMCPCorrelations(std::vector<FrsGate*> fg)
    : FrsMCPCorrelations("FrsMCPCorrelations")
{
    FrsGates = fg;
    mcp_config = TH10MCPConfiguration::GetInstance();
}

FrsMCPCorrelations::FrsMCPCorrelations(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   header(nullptr)
    ,   frsHitArray(nullptr)
    ,   fNEvents(0)
    ,   multihitArray(nullptr)
    ,   fHitsMCP(NULL)
    ,   StefanHit(nullptr)

{
    frs_config = TFrsConfiguration::GetInstance();
    frs = frs_config->FRS();
    mcp_config = TH10MCPConfiguration::GetInstance();
    stefan_config = TStefanConfiguration::GetInstance();

}

FrsMCPCorrelations::~FrsMCPCorrelations()
{
    c4LOG(info, "Destroyed FrsMCPCorrelationsProperly.");
}

InitStatus FrsMCPCorrelations::Init()
{

    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = mgr->InitObjectAs<decltype(header)>("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found!");

    frsHitArray = mgr->InitObjectAs<decltype(frsHitArray)>("FrsHitData");
    c4LOG_IF(fatal, !frsHitArray, "Branch FrsHitData not found!");
    multihitArray = mgr->InitObjectAs<decltype(multihitArray)>("FrsMultiHitData");
    c4LOG_IF(fatal, !multihitArray, "Branch FrsMultiHitData not found!");

    fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksAnaData");
    c4LOG_IF(fatal, !fHitsMCP, "Branch H10MCPTwinpeaksAnaData not found!");
    // fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksCalData");
    // c4LOG_IF(fatal, !fHitsMCP, "Branch H10MCPTwinpeaksCalData not found!");

    StefanHit = mgr->InitObjectAs<decltype(StefanHit)>("StefanHitData");
    c4LOG_IF(fatal, !StefanHit, "Branch StefanHitData not found - no correlations with Stefan possible!");


    FairRootManager::Instance()->GetOutFile()->cd();

    int num_dssds = stefan_config->DSSDs();

    dir_corr = gDirectory->mkdir("Correlations");
    gDirectory->cd("MCPs");
    dir_mcp_stefan = dir_corr->mkdir("MCP-Stefan");

    dir_frs_gates = new TDirectory*[FrsGates.size()];

    // MCP + STEFAN
    h2_e_dssd_vs_mcp_dt.resize(num_dssds);
    for (int i = 0; i < num_dssds; i++) 
    {
        h2_e_dssd_vs_mcp_dt[i] = MakeTH2(dir_mcp_stefan, "D", Form("h2_e_dssd_%i_vs_mcp_dt", i), Form("DSSD %i E vs MCP dT", i), 1000, -100, 100, 750, 0, 5000000);
    }

    // MCP + FRS
    if (!FrsGates.empty())
    {
        // dT Gated on FRS
        h1_dT_gated_on_frs.resize(FrsGates.size());

        // HeatMaps Gated on FRS
        h2_MCP1_HeatMap_gated_on_frs.resize(FrsGates.size());
        h2_MCP2_HeatMap_gated_on_frs.resize(FrsGates.size());
        h2_e_dssd_vs_mcp_dt_gated_on_frs.resize(FrsGates.size());

        for (int gate_frs = 0; gate_frs < FrsGates.size(); gate_frs++)
        {
            dir_frs_gates[gate_frs] = dir_corr->mkdir(TString(FrsGates.at(gate_frs)->GetName())); 
            
            h1_dT_gated_on_frs[gate_frs] = MakeTH1(dir_frs_gates[gate_frs], "F", Form("h1_dT_%i", gate_frs), Form(" MCPs dT Gated %i", gate_frs), 10000, -100, 100,"dt [ns]", kPink, kBlack);  

            h2_MCP1_HeatMap_gated_on_frs[gate_frs] = MakeTH2(dir_frs_gates[gate_frs],"b",  Form("h2_MCP1_Heatmap_gated_on_frs_%i", gate_frs), Form(" MCP1 HeatMap Gated %i", gate_frs), 500, -250, 250, 500, -250, 250); 
            h2_MCP1_HeatMap_gated_on_frs[gate_frs]->GetXaxis()->SetTitle("DeltaX");
            h2_MCP1_HeatMap_gated_on_frs[gate_frs]->GetYaxis()->SetTitle("DeltaY");

            h2_MCP2_HeatMap_gated_on_frs[gate_frs] = MakeTH2(dir_frs_gates[gate_frs],"b",  Form("h2_MCP2_Heatmap_gated_on_frs_%i", gate_frs), Form(" MCP2 HeatMap Gated %i", gate_frs), 500, -250, 250, 500, -250, 250); 
            h2_MCP1_HeatMap_gated_on_frs[gate_frs]->GetXaxis()->SetTitle("DeltaX");
            h2_MCP1_HeatMap_gated_on_frs[gate_frs]->GetYaxis()->SetTitle("DeltaY");

            // MCP + FRS + STEFAN
            h2_e_dssd_vs_mcp_dt_gated_on_frs[gate_frs].resize(num_dssds);
            for (int i = 0; i < num_dssds; i++) 
            {
                h2_e_dssd_vs_mcp_dt_gated_on_frs[gate_frs][i] = MakeTH2(dir_frs_gates[gate_frs], "D", Form("h2_e_dssd_%i_vs_mcp_dt_gated_on_frs_%i", i, gate_frs), Form("DSSD %i E vs MCP dT", i), 1000, -100, 100, 750, 0, 5000000);
            }
        
        }

    }

    return kSUCCESS;

}



void FrsMCPCorrelations::Exec(Option_t* option)
{   
    
    // -> Reject events without both subsystems <-
    //if (frsHitArray->size() <= 0 || fHitsMCP->GetEntriesFast() <= 0) return;
    if (multihitArray->size() <= 0 || fHitsMCP->GetEntriesFast() <= 0) return;


    const auto & frsHitItem = frsHitArray->at(0);
    const auto & multihitItem = multihitArray->at(0);

    wr_FRS = 0;
    wr_FRS = frsHitItem.Get_wr_t();

    H10MCPTwinpeaksAnaData* hit = (H10MCPTwinpeaksAnaData*)fHitsMCP->At(0);
    if (!hit) return;

    // EG Uncomment this is if you want to look at data only when both mcp are firing
    // if (!hit->full_event) return;   

    std::vector<Float_t> z41_mhtdc = multihitItem.Get_ID_z41_mhtdc();
    std::vector<Float_t> z21_mhtdc = multihitItem.Get_ID_z21_mhtdc();
    std::vector<Float_t> z42_mhtdc = multihitItem.Get_ID_z42_mhtdc();
    std::vector<Float_t> AoQ_s1s2_mhtdc = multihitItem.Get_ID_AoQ_corr_s1s2_mhtdc();
    std::vector<Float_t> AoQ_s2s4_mhtdc = multihitItem.Get_ID_AoQ_corr_s2s4_mhtdc();
    std::vector<Float_t> dEdeg_z41_mhtdc = multihitItem.Get_ID_dEdeg_z41_mhtdc();
    Float_t x2_position = frsHitItem.Get_ID_x2();
    Float_t x4_position = frsHitItem.Get_ID_x4();
    Float_t sci42e = frsHitItem.Get_sci_e_42();

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
    mcp_wr = hit->wr_t;

    // MCP + STEFAN
    for (auto const & s_hit : *StefanHit)
    {
        h2_e_dssd_vs_mcp_dt[s_hit.DSSD]->Fill(T2-T1, s_hit.Energy);
    }

    // MCP + FRS
    if (!FrsGates.empty())
    {

        for (int gate = 0; gate < FrsGates.size(); gate++)
        {    
            
            for (int i = 0; i < AoQ_s2s4_mhtdc.size(); i++)
            {

                if (FrsGates[gate]->PassedS2S4(z41_mhtdc.at(i), z42_mhtdc.at(i), x2_position, x4_position, AoQ_s2s4_mhtdc.at(i), dEdeg_z41_mhtdc.at(i), sci42e))
                {
            
                    // MCP + FRS
                    if(T1!=0 && T2!=0)h1_dT_gated_on_frs[gate]->Fill(T2-T1);
                    if( X12!=0 && X11!=0 && Y12!=0 && Y11!=0 ) h2_MCP1_HeatMap_gated_on_frs[gate]->Fill(X11-X12, Y11-Y12);
                    if( X22!=0 && X21!=0 && Y22!=0 && Y21!=0 ) h2_MCP2_HeatMap_gated_on_frs[gate]->Fill(X21-X22, Y21-Y22);

                    // MCP + STEFAN + FRS
                    for (auto const & s_hit : *StefanHit)
                    {
                        if(T1!=0 && T2!=0)h2_e_dssd_vs_mcp_dt_gated_on_frs[gate][s_hit.DSSD]->Fill(T2-T1, s_hit.Energy);
                    }

                }
            }
        }
    }

    fNEvents++;
}
void FrsMCPCorrelations::FinishEvent()
{
    
}

void FrsMCPCorrelations::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_corr->Write();
    c4LOG(info, "Written FRS-MCP analysis histograms to file.");

}


ClassImp(FrsMCPCorrelations)