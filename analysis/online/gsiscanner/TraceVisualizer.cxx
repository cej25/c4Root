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
#include "TraceVisualizer.h"
#include "EventHeader.h"
#include "GermaniumFebexData.h"

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


TraceVisualizer::TraceVisualizer() : TraceVisualizer("TraceVisualizer")
{
}

TraceVisualizer::TraceVisualizer(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitUncal(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
}

TraceVisualizer::~TraceVisualizer()
{
    c4LOG(info, "");
    if (fHitUncal)
        delete fHitUncal;
}

void TraceVisualizer::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus TraceVisualizer::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);
    
    
    run->GetHttpServer()->RegisterCommand("ResetAllHistos", Form("/Objects/%s/->ResetAllHistos()", GetName()));


    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");
 
    fHitUncal = (TClonesArray*)mgr->GetObject("GermaniumFebexTraceData");
    c4LOG_IF(fatal, !fHitUncal, "Branch GermaniumFebexTraceData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");
    
    TDirectory::TContext ctx(nullptr);

    dir_febex = new TDirectory("FEBEX", "FEBEX", "", 0);
    mgr->Register("FEBEX", "FEBEX Directory", dir_febex, false);
    dir_febex_board = new TDirectory*[number_of_boards];
    for (int i = 0; i<number_of_boards;i++) {
        dir_febex_board[i] = new TDirectory(Form("FEBEX board %i",i), Form("FEBEX board %i",i), "", 0);
        dir_febex->Append(dir_febex_board[i]);
    }
    histograms->Add(dir_febex);
    dir_febex->cd();

    
    c_energy  = new TCanvas**[number_of_boards];
    c_energy_board  = new TCanvas*[number_of_boards];
    h1_energy = new TH1F**[number_of_boards];

    for (int iboard = 0; iboard < number_of_boards; iboard++){
        dir_febex_board[iboard]->cd();
        c_energy[iboard]  = new TCanvas*[number_of_channels_per_board];
        h1_energy[iboard] = new TH1F*[number_of_channels_per_board];
        c_energy_board[iboard] = new TCanvas(Form("c_energy_board_%i",iboard),Form("Energy spectrum board %i",iboard),650,350);
        c_energy_board[iboard]->Divide(4,4);
        dir_febex_board[iboard]->Append(c_energy_board[iboard]);
        
        for (int ihist = 0; ihist < number_of_channels_per_board; ihist++){
            c_energy[iboard][ihist] = new TCanvas(Form("c_energy_%i_%i",iboard,ihist),Form("Energy spectrum board %i channel %i",iboard,ihist),650,350);
            c_energy[iboard][ihist]->cd();
            h1_energy[iboard][ihist] = new TH1F(Form("h1_energy_%i_%i",iboard,ihist),Form("Energy spectrum board %i channel %i",iboard,ihist),funcal_nbins,funcal_bin_low,funcal_bin_high);
            h1_energy[iboard][ihist]->GetXaxis()->SetTitle("uncal (keV)");
            h1_energy[iboard][ihist]->Draw();
            c_energy_board[iboard]->cd(ihist+1);
            h1_energy[iboard][ihist]->Draw();
            
            dir_febex_board[iboard]->Append(c_energy[iboard][ihist]);
            dir_febex_board[iboard]->Append(h1_energy[iboard][ihist]);
        }
    }




    c_trace_board  = new TCanvas*[number_of_boards];
    c_trace  = new TCanvas**[number_of_boards];
    h1_trace = new TH1F**[number_of_boards];

    for (int iboard = 0; iboard < number_of_boards; iboard++){
        dir_febex_board[iboard]->cd();
        c_trace[iboard]  = new TCanvas*[number_of_channels_per_board];
        h1_trace[iboard] = new TH1F*[number_of_channels_per_board];
        
        c_trace_board[iboard] = new TCanvas(Form("c_trace_board_%i",iboard),Form("Energy spectrum board %i",iboard),650,350);
        c_trace_board[iboard]->Divide(4,4);
        dir_febex_board[iboard]->Append(c_trace_board[iboard]);

        for (int ihist = 0; ihist < number_of_channels_per_board; ihist++){
            c_trace[iboard][ihist] = new TCanvas(Form("c_trace_%i_%i",iboard,ihist),Form("Trace board %i channel %i",iboard,ihist),650,350);
            c_trace[iboard][ihist]->cd();
            h1_trace[iboard][ihist] = new TH1F(Form("h1_trace_%i_%i",iboard,ihist),Form("Trace board %i channel %i",iboard,ihist),trace_length_plot,0,trace_length_plot);
            h1_trace[iboard][ihist]->GetXaxis()->SetTitle("time 10 ns");
            h1_trace[iboard][ihist]->Draw();
            
            c_trace_board[iboard]->cd(ihist+1);
            h1_trace[iboard][ihist]->Draw();
            
            
            dir_febex_board[iboard]->Append(c_trace[iboard][ihist]);
            dir_febex_board[iboard]->Append(h1_trace[iboard][ihist]);
        }
    }
    

    return kSUCCESS;
}

void TraceVisualizer::ResetAllHistos()
{
    for (int iboard = 0; iboard < number_of_boards; iboard++){
        for (int ihist = 0; ihist < number_of_boards; ihist++){
            h1_energy[iboard][ihist]->Reset();
        }
    }
    c4LOG(info, "Histograms reset.");
}

void TraceVisualizer::Exec(Option_t* option){
    if (fHitUncal && fHitUncal->GetEntriesFast() > 0){
        
        skip_counter ++;
        Int_t nHits = fHitUncal->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++){
            
            GermaniumFebexTraceData* hit1 = (GermaniumFebexTraceData*)fHitUncal->At(ihit);
            if (!hit1) continue;
            
            uint32_t num_channels_fired1 = hit1->Get_num_channels_fired();
            uint64_t event_trigger_time1 = hit1->Get_event_trigger_time();
            uint16_t hit_pattern1 = hit1->Get_hit_pattern();
            uint8_t board_id1 = hit1->Get_board_id();
            uint8_t pileup1 = hit1->Get_pileup();
            uint8_t overflow1 = hit1->Get_overflow();
            uint8_t channel_id1 = hit1->Get_channel_id();
            double channel_trigger_time1 = hit1->Get_channel_trigger_time();
            int32_t channel_energy1 = hit1->Get_channel_energy();
            uint16_t wr_subsystem_id1 = hit1->Get_wr_subsystem_id();
            uint64_t wr_t1 = hit1->Get_wr_t();
            
            if (overflow1 != 0) continue; 
            if (pileup1 != 0) continue; 
            
            if (skip_counter >= plot_every_ntrace){
                for (int trace_index = 0; trace_index < trace_length_plot; trace_index ++){
                    h1_trace[board_id1][channel_id1-1]->SetBinContent(trace_index+1, hit1->Get_trace_value(trace_index));
                    h1_trace[board_id1][channel_id1-1]->SetTitle(Form("Trace energy = %3f (*1000)",channel_energy1/1e3));
                }
                
            }
            if (channel_trigger_time1 != 0) h1_energy[board_id1][channel_id1-1]->Fill(channel_energy1);
            
            
        }
        if (skip_counter >= plot_every_ntrace) skip_counter = 0;
    }

    fNEvents += 1;
}



void TraceVisualizer::FinishEvent()
{

    if (fHitUncal){
        fHitUncal->Clear();
    }
}

void TraceVisualizer::FinishTask()
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

ClassImp(TraceVisualizer)
