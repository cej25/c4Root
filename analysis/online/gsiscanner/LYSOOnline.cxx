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
 *                             J.E.L. Larsson                                 *
 *                                06.05.25                                    *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "LYSOOnline.h"
#include "EventHeader.h"
#include "LYSOCalData.h"
#include "QDCData.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TF1.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include <sstream>
#include <chrono>
#include <iomanip>

#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem> // For creating directories
#include <string>


LYSOOnline::LYSOOnline() : LYSOOnline("LYSOOnline")
{
}

LYSOOnline::LYSOOnline(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitsQDC(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
}

LYSOOnline::~LYSOOnline()
{
    c4LOG(info, "");
    if (fHitsQDC)
        delete fHitsQDC;
}

void LYSOOnline::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus LYSOOnline::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);
    
    
    run->GetHttpServer()->RegisterCommand("ResetAllHistos", Form("/Objects/%s/->ResetAllHistos()", GetName()));


    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");
 
    fHitsQDC = (TClonesArray*)mgr->GetObject("QDCData");
    c4LOG_IF(fatal, !fHitsQDC, "Branch QDCData not found!");
    
    fHitsLYSO = (TClonesArray*)mgr->GetObject("LYSOCalData");
    c4LOG_IF(fatal, !fHitsLYSO, "Branch QDCData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");
    
    TDirectory::TContext ctx(nullptr);

    dir_qdc = new TDirectory("QDC", "QDC", "", 0);
    mgr->Register("QDC", "QDC Directory", dir_qdc, false);

    histograms->Add(dir_qdc);
    dir_qdc->cd();

    
    c_charge  = new TCanvas("c_charge","Charge in QDC");
    c_charge->Divide(number_of_channels_per_board,number_of_boards);
    dir_qdc->Append(c_charge);
    h1_charge = new TH1F*[number_of_channels];

    for (int i = 0; i<number_of_channels; i++){
        c_charge->cd(i+1);
        h1_charge[i] = new TH1F(Form("h1_charge_%i_%i",i/number_of_channels_per_board,i%number_of_channels_per_board), Form("QDC charge bd %i ch %i",i/number_of_channels_per_board,i%number_of_channels_per_board),funcal_nbins,funcal_bin_low,funcal_bin_high);
        h1_charge[i]->Draw();

        //dir_qdc->Append(h1_charge[i]);
    }



    dir_lyso = new TDirectory("LYSO", "LYSO", "", 0);
    mgr->Register("LYSO", "LYSO Directory", dir_lyso, false);

    histograms->Add(dir_lyso);
    dir_lyso->cd();
    c_pos = new TCanvas("c_pos","LYSO position");
    c_pos->cd();
    h2_pos = new TH2F("h2_pos","LYSO position",500,-2,2,500,-2,2);
    h2_pos->Draw("COLZ");
    dir_lyso->Append(c_pos);
    dir_lyso->Append(h2_pos);
    
    c_energy = new TCanvas("c_energy","LYSO energies");
    c_energy->Divide(16,2);
    dir_lyso->Append(c_energy);
    h1_energy = new TH1F*[32];

    for (int i = 0; i<32;i++){
        const char* xy = "x";
        if (i >= 16) xy = "y";
        h1_energy[i] = new TH1F(Form("h1_energy_%s_%i",xy,i%16+1),Form("LYSO energy %s %i",xy,i%16+1),1000,0,1000);
        c_energy->cd(i+1);
        h1_energy[i]->Draw();
        
        //dir_lyso->Append(h1_energy[i]);
    }

    return kSUCCESS;
}

void LYSOOnline::ResetAllHisto()
{
    h2_pos->Reset();
    for (int i = 0; i<number_of_channels; i++) h1_charge[i]->Reset();
    for (int i = 0; i<32; i++) h1_energy[i]->Reset();
    c4LOG(info, "Histograms reset.");
}

void LYSOOnline::Exec(Option_t* option){
    if (fHitsQDC && fHitsQDC->GetEntriesFast() > 0)
    {
        Int_t event_multiplicity = fHitsQDC->GetEntriesFast();
        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++)
        {
            QDCData* fqdc_hit = (QDCData*)fHitsQDC->At(ihit);
            int ch_id = fqdc_hit->Get_ch_ID();
            int board_id = fqdc_hit->Get_board_id();
            int16_t charge = fqdc_hit->Get_charge();

            h1_charge[board_id*number_of_channels_per_board + ch_id - 1]->Fill(charge);
        }
    }
    
    if (fHitsLYSO && fHitsLYSO->GetEntriesFast() > 0)
    {
        Int_t event_multiplicity = fHitsLYSO->GetEntriesFast();
        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++)
        {
            LYSOCalData* flyso_hit = (LYSOCalData*)fHitsLYSO->At(ihit);

            int  fired_anodes = flyso_hit->Get_fired_anodes();
            double  posx = flyso_hit->Get_posx();
            double  posy = flyso_hit->Get_posy();
            

            if (fired_anodes < 32) continue;

            for (int ix = 1; ix<=16;ix++){
                h1_energy[ix-1]->Fill(flyso_hit->Get_energy_x(ix));
                h1_energy[16+ix-1]->Fill(flyso_hit->Get_energy_y(ix));
            }

            h2_pos->Fill(posx,posy);
        }
    }


    fNEvents += 1;
}



void LYSOOnline::FinishEvent()
{

    if (fHitsQDC){
        fHitsQDC->Clear();
    }
    if (fHitsLYSO){
        fHitsLYSO->Clear();
    }
}

void LYSOOnline::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }
    if (fHitsQDC)
    {
        c4LOG(info, "QDC histograms written to file.");
    }
    if (fHitsLYSO)
    {
        c4LOG(info, "LYSO histograms written to file.");
    }
}

ClassImp(LYSOOnline)
