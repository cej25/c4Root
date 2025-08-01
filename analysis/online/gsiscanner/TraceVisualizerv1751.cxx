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
#include "TraceVisualizerv1751.h"
#include "EventHeader.h"
#include "v1751TraceData.h"

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


TraceVisualizerv1751::TraceVisualizerv1751() : TraceVisualizerv1751("TraceVisualizerv1751")
{
}

TraceVisualizerv1751::TraceVisualizerv1751(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitUncal(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
}

TraceVisualizerv1751::~TraceVisualizerv1751()
{
    c4LOG(info, "");
    if (fHitUncal)
        delete fHitUncal;
}

void TraceVisualizerv1751::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus TraceVisualizerv1751::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);
    
    
    run->GetHttpServer()->RegisterCommand("ResetAllHistos", Form("/Objects/%s/->ResetAllHistos()", GetName()));


    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");
 
    fHitUncal = (TClonesArray*)mgr->GetObject("v1751TraceData");
    c4LOG_IF(fatal, !fHitUncal, "Branch v1751TraceData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");
    
    TDirectory::TContext ctx(nullptr);

    dir_v1751 = new TDirectory("v1751", "v1751", "", 0);
    mgr->Register("v1751", "v1751 Directory", dir_v1751, false);
    dir_v1751_board = new TDirectory*[number_of_boards];
    for (int i = 0; i<number_of_boards;i++) {
        dir_v1751_board[i] = new TDirectory(Form("v1751 board %i",i), Form("v1751 board %i",i), "", 0);
        dir_v1751->Append(dir_v1751_board[i]);
    }

    histograms->Add(dir_v1751);
    dir_v1751->cd();

    c_trace_board  = new TCanvas*[number_of_boards];
    c_trace  = new TCanvas**[number_of_boards];
    h1_trace = new TH1F**[number_of_boards];

    for (int iboard = 0; iboard < number_of_boards; iboard++){
        dir_v1751_board[iboard]->cd();
        c_trace[iboard]  = new TCanvas*[number_of_channels_per_board];
        h1_trace[iboard] = new TH1F*[number_of_channels_per_board];
        
        c_trace_board[iboard] = new TCanvas(Form("c_trace_board_%i",iboard),Form("Energy spectrum board %i",iboard),650,350);
        c_trace_board[iboard]->Divide(4,4);
        dir_v1751_board[iboard]->Append(c_trace_board[iboard]);

        for (int ihist = 0; ihist < number_of_channels_per_board; ihist++){
            c_trace[iboard][ihist] = new TCanvas(Form("c_trace_%i_%i",iboard,ihist),Form("Trace board %i channel %i",iboard,ihist),650,350);
            c_trace[iboard][ihist]->cd();
            h1_trace[iboard][ihist] = new TH1F(Form("h1_trace_%i_%i",iboard,ihist),Form("Trace board %i channel %i",iboard,ihist),trace_length_plot,0,trace_length_plot);
            h1_trace[iboard][ihist]->GetXaxis()->SetTitle("time 10 ns");
            h1_trace[iboard][ihist]->Draw();
            
            c_trace_board[iboard]->cd(ihist+1);
            h1_trace[iboard][ihist]->Draw();
            
            
            dir_v1751_board[iboard]->Append(c_trace[iboard][ihist]);
            dir_v1751_board[iboard]->Append(h1_trace[iboard][ihist]);
        }
    }
    

    return kSUCCESS;
}

void TraceVisualizerv1751::ResetAllHistos()
{
    for (int iboard = 0; iboard < number_of_boards; iboard++){
        for (int ihist = 0; ihist < number_of_boards; ihist++){
            h1_energy[iboard][ihist]->Reset();
        }
    }
    c4LOG(info, "Histograms reset.");
}

void TraceVisualizerv1751::Exec(Option_t* option){
    if (fHitUncal && fHitUncal->GetEntriesFast() > 0){
        
        skip_counter ++;
        Int_t nHits = fHitUncal->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++){
            
            v1751TraceData* hit1 = (v1751TraceData*)fHitUncal->At(ihit);
            if (!hit1) continue;
            
            uint32_t num_channels_fired1 = hit1->Get_num_channels_fired();
            uint8_t board_id1 = 0;
            uint8_t channel_id1 = hit1->Get_channel_id();


            if (skip_counter >= plot_every_ntrace){
                for (int trace_index = 0; trace_index < hit1->Get_trace_length(); trace_index ++){
                    h1_trace[board_id1][channel_id1]->SetBinContent(trace_index+1, hit1->Get_trace(trace_index));
                }
                
            }        
            
        }
        if (skip_counter >= plot_every_ntrace) skip_counter = 0;
    }

    fNEvents += 1;
}



void TraceVisualizerv1751::FinishEvent()
{

    if (fHitUncal){
        fHitUncal->Clear();
    }
}

void TraceVisualizerv1751::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }
    if (fHitUncal)
    {
        c4LOG(info, "DEGAS histograms written to file.");
    }
}

ClassImp(TraceVisualizerv1751)
