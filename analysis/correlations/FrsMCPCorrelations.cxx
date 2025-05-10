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
 *                              C.E. Jones                                    *
 *                               25.11.24                                     *
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
    ,   lisaCalArray(nullptr)
    ,   frsHitArray(nullptr)
    ,   fNEvents(0)
    ,   multihitArray(nullptr)

{
    frs_config = TFrsConfiguration::GetInstance();
    frs = frs_config->FRS();
    mcp_config = TH10MCPConfiguration::GetInstance();
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
    fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitsMCP, "Branch H10MCPTwinpeaksCalData not found!");

  

    FairRootManager::Instance()->GetOutFile()->cd();


    dir_corr = gDirectory->mkdir("Correlations");

    return kSUCCESS;

}



void FrsMCPCorrelations::Exec(Option_t* option)
{   
    // -> Reject events without both subsystems <-
    if (frsHitArray->size() <= 0 || fHitsMCP->GetEntriesFast() <= 0) return;

    const auto & frsHitItem = frsHitArray->at(0);
    const auto & multihitItem = multihitArray->at(0);

    wr_FRS = frsHitItem.Get_wr_t();

    std::vector<Float_t> z41_mhtdc = multihitItem.Get_ID_z41_mhtdc();
    std::vector<Float_t> z42_mhtdc = multihitItem.Get_ID_z42_mhtdc();
    std::vector<Float_t> AoQ_s2s4_mhtdc = multihitItem.Get_ID_AoQ_corr_s2s4_mhtdc();
    std::vector<Float_t> dEdeg_z41_mhtdc = multihitItem.Get_ID_dEdeg_z41_mhtdc();
    Float_t x2_position = frsHitItem.Get_ID_x2();
    Float_t x4_position = frsHitItem.Get_ID_x4();
    Float_t sci42e = frsHitItem.Get_sci_e_42();

    int mh_counter_passed_s2s4[FrsGates.size()] = {0};
    if (!FrsGates.empty())
    {
        for (int gate = 0; gate < FrsGates.size(); gate++)
        {    
            // Loop for S1S2
            for (int i = 0; i < AoQ_s2s4_mhtdc.size(); i++)
            {
                if (mh_counter_passed_s2s4[gate] > 0) break;
                if (FrsGates[gate]->PassedS2S4(z41_mhtdc.at(i), z42_mhtdc.at(i), x2_position, x4_position, AoQ_s2s4_mhtdc.at(i), dEdeg_z41_mhtdc.at(i), sci42e))
                {
                    // MCP stuff

                    // zwischenspeicher fuereventbuilding
                    ULong64_t ttrigger0; // T1 hat leider der CAEN stempel geklaut
                    ULong64_t T1;
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
                    double T01Epoch=0;
                    double T02Epoch=0;
                    double X01Epoch=0;
                    double X02Epoch=0;
                    double Y01Epoch=0;
                    double Y02Epoch=0;
                    double X11Epoch=0;
                    double X12Epoch=0;
                    double Y11Epoch=0;
                    double Y12Epoch=0;

                    ULong64_t entry2 = 0;
                    ULong64_t lastProcessedEntry = 0;
                    ULong64_t t2search;
                    int ttrigger = 0;
                    int maxFileCount = 0;
                    int ch0counter = 0;
                    int ch1counter = 0;
                    int ch2counter = 0;
                    int ch3counter = 0;
                    int ch4counter = 0;
                    int ch5counter = 0;
                    int eventcounter = 0;
                    int dataPointsCounter = 0;
                    int fileCount = 0;
                    bool foundMatchingFile = false;
                    int reruns = 0;
            
                    if (fHitsMCP && fHitsMCP->GetEntriesFast() > 0)
                    {   
                        ch0counter = 0;
                        ch1counter = 0;
                        ch2counter = 0;
                        ch3counter = 0;
                        ch4counter = 0;
                        ch5counter = 0;
                        eventcounter = 0;
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
        

                            if (mcp_id==0 && type==0 && number== 0 ){
                            T01 = hit->Get_fast_lead_time();
                            T01Epoch=hit->Get_fast_lead_epoch();}
                            if (mcp_id==1 && type==0 && number== 0 ){
                            T02 = hit->Get_fast_lead_time();
                            T02Epoch=hit->Get_fast_lead_epoch();}
                            if (mcp_id==0 && type==1 && number== 0 ){
                            X01 = hit->Get_fast_lead_time();
                            X01Epoch=hit->Get_fast_lead_epoch();}
                            if (mcp_id==0 && type==1 && number== 1 ){
                            X02 = hit->Get_fast_lead_time();
                            X02Epoch=hit->Get_fast_lead_epoch();}
                            if (mcp_id==0 && type==2 && number== 0 ){
                            Y01 = hit->Get_fast_lead_time(); 
                            Y01Epoch=hit->Get_fast_lead_epoch();}
                            if (mcp_id==0 && type==2 && number== 1 ){
                            Y02 = hit->Get_fast_lead_time();
                            Y02Epoch=hit->Get_fast_lead_epoch();}
                            if (mcp_id==1 && type==1 && number== 0 ){
                            X11 = hit->Get_fast_lead_time(); 
                            X11Epoch=hit->Get_fast_lead_epoch();}
                            if (mcp_id==1 && type==1 && number== 1 ){
                            X12 = hit->Get_fast_lead_time(); 
                            X12Epoch=hit->Get_fast_lead_epoch();}
                            if (mcp_id==1 && type==2 && number== 0 ){
                            Y11 = hit->Get_fast_lead_time();
                            Y11Epoch=hit->Get_fast_lead_epoch();}
                            if (mcp_id==1 && type==2 && number== 1 ){
                            Y12 = hit->Get_fast_lead_time();
                            Y12Epoch=hit->Get_fast_lead_epoch();}

                            if (eventcounter == 6 )
                            {
                                ch0counter = 0;
                                ch1counter = 0;
                                ch2counter = 0;
                                ch3counter = 0;
                                ch4counter = 0;
                                ch5counter = 0;
                                eventcounter = 0;
                                dataPointsCounter++; // Increment the counter for each data point collected
                            }    
                        }
                        h1_test_histogram_FRSGated[gate]->Fill(T02 - T01+(T01Epoch-T01Epoch));
                        histogram2_FRSGated[gate]->Fill(X02-X01, T02-T01);
                        MCP1Heatmap_FRSGated[gate]->Fill(X02-X01+(X02Epoch-X01Epoch), Y02-Y01+(Y01Epoch-Y02Epoch));
                        MCP2Heatmap_FRSGated[gate]->Fill(X12-X11+(X12Epoch-X11Epoch), Y12-Y11+(Y12Epoch-Y11Epoch));

                        mh_counter_passed_s2s4[gate]++;
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