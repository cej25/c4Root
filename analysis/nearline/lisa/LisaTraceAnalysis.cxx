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
 *                       E.M. Gandolfo, C.E. Jones                            *
 *                               25.11.24                                    *
 ******************************************************************************/
// ::: Note::: No canvases in Nearline Tasks please :::

#include <sstream>
#include <iomanip>
// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "EventHeader.h"
#include "LisaTraceAnalysis.h"
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

LisaTraceAnalysis::LisaTraceAnalysis()  :   LisaTraceAnalysis("LisaTraceAnalysis")
{
    lisa_config = TLisaConfiguration::GetInstance();
}

LisaTraceAnalysis::LisaTraceAnalysis(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    // , fHitLisa(NULL)
    , fNEvents(0)
    , header(nullptr)
    // ranges
{
    lisa_config = TLisaConfiguration::GetInstance();
    exp_config = TExperimentConfiguration::GetInstance();

}

LisaTraceAnalysis::~LisaTraceAnalysis()
{
    c4LOG(info, "");
}

void LisaTraceAnalysis::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus LisaTraceAnalysis::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    //header = (EventHeader*)mgr->GetObject("EventHeader.");
    header = mgr->InitObjectAs<decltype(header)>("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaAnaArray = mgr->InitObjectAs<decltype(lisaAnaArray)>("LisaAnaData");
    c4LOG_IF(fatal, !lisaAnaArray, "Branch LisaAnaData not found!");

    FairRootManager::Instance()->GetOutFile()->cd();
    dir_lisa = gDirectory->mkdir("LISA");
    mgr->Register("LISA", "LISA Directory", dir_lisa, false); // allow other tasks to find this
   
    dir_lisa->cd();
    dir_energy = dir_lisa->mkdir("Energy");
    dir_traces = dir_lisa->mkdir("Traces");
    dir_energy_MWD = dir_energy->mkdir("E_MWD");
    dir_traces_MWD = dir_traces->mkdir("T_MWD");
      
    // ::: Board number read from macro. 
    //     Since in this stage we don't have a mapping this has to be hardcoded
    int board_number = lisa_config->board_num;
    int histo_number = 16*board_number;         // For each board, 16 histos from 0 to 15

    dir_energy->cd();
    // :::::  E N E R G Y :::::

    // ::: Energy for all channels
    h1_energy.resize(histo_number);
    for (int i = 0; i < histo_number; i++) 
    {  
        
        h1_energy[i] = new TH1F(Form("energy_%i", i), Form("Energy_%i",i), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
        h1_energy[i]->GetXaxis()->SetTitle("E(febex) [a.u.]");
        h1_energy[i]->SetLineColor(kBlack);
    }
    
    dir_energy_MWD->cd();
    // ::: Energy MWD
    h1_energy_MWD.resize(histo_number);
    for (int i = 0; i < histo_number; i++) 
    {  
        h1_energy_MWD[i] = new TH1F(Form("energy_MWD_%i", i), Form("Energy_MWD_%i",i), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
        h1_energy_MWD[i]->GetXaxis()->SetTitle("E(MWD) [a.u.]");
        h1_energy_MWD[i]->SetLineColor(kRed+1);
    }
    

    // ::::: T R A C E S ::::
    //::::::::::::Traces from Febex
    h2_traces.resize(histo_number);
    h2_traces_MWD.resize(histo_number);
    c_trace = new TCanvas("c_trace_ch_compare","c_trace_ch_compare", 800, 600);
    c_trace->Divide(4,4);
    for (int i = 0; i < histo_number; i++) 
    {
        c_trace->cd(i+1);
        h2_traces[i] = MakeTH2(dir_traces,"F",Form("h2_traces_%i", i), Form("Traces_%i",i), 200, 0, 20,300,-5000,5000);
        h2_traces[i]->GetXaxis()->SetTitle("Time [us/0.01]");
        h2_traces[i]->SetMarkerColor(kBlack);
        h2_traces[i]->SetMarkerStyle(5);
        h2_traces[i]->SetOption("SCAT");
        h2_traces[i]->Draw("SCAT");

        h2_traces_MWD[i] = MakeTH2(dir_traces_MWD,"F",Form("h2_traces_MWD_%i", i), Form("Traces_MWD_%i",i), 200, 0, 20,300,-5000,5000);
        h2_traces_MWD[i]->GetXaxis()->SetTitle("Time [us/0.01]");
        h2_traces_MWD[i]->SetMarkerColor(kRed+1);
        h2_traces_MWD[i]->SetMarkerStyle(5);
        h2_traces_MWD[i]->SetOption("SCAT");
        h2_traces_MWD[i]->Draw("SCAT,SAME");
    }
    dir_traces->Append(c_trace);

    // ::: mapping for histo filling
    // mapping[1] = 0;
    // mapping[2] = 1;
    // mapping[5] = 2;
    // mapping[6] = 3;
    // mapping[9] = 4;
    // mapping[10] = 5;
    // mapping[13] = 6;
    // mapping[14] = 7;

    return kSUCCESS;
}


void LisaTraceAnalysis::Exec(Option_t* option)
{   
    int board_number = lisa_config->board_num;
    int histo_number = 16*board_number; 
    int event_to_analyze = lisa_config->event_ana;
    uint64_t Eventno = header->GetEventno();

    for (auto const & lisaAnaItem : *lisaAnaArray)
    {

        // ::::: Retrieve Data :::::
        int ch_ID = lisaAnaItem.Get_channel_id_traces();
        double energy_febex = lisaAnaItem.Get_channel_energy();
        double energy_MWD = lisaAnaItem.Get_channel_energy_MWD();
        std::vector<int16_t> trace_febex = lisaAnaItem.Get_trace();
        std::vector<int16_t> trace_MWD = lisaAnaItem.Get_trace_MWD();

        
        // ::::: F I L L   H I S T O S :::::

        // ::::: E N E R G Y :::::
        //std::cout << " energy from plotting task : " << energy_MWD << "\n";

        h1_energy[ch_ID]->Fill(energy_febex);
        h1_energy_MWD[ch_ID]->Fill(energy_MWD);

        //h1_energy[mapping[ch_ID]]->Fill(energy_febex);
        //h1_energy_MWD[mapping[ch_ID]]->Fill(energy_MWD);			     
                           
        // :::: Fill traces all events :::
        // for (int i = 0; i < trace_febex.size(); i++)
        // {            
	    //     h2_traces[mapping[ch_ID]]->Fill(i,trace_febex[i]);
        // }

        // ::::::  T R A C E S  :::::::
        // ::: Fill traces for event number defined in macro
        int start_MWD_plot = lisa_config->Get_MWD_Trace_Start()/lisa_config->Get_Sampling();
        int stop_MWD_plot = lisa_config->Get_MWD_Trace_Stop()/lisa_config->Get_Sampling();
        //std::cout << " Event no : " << Eventno << "\n";
        if (Eventno == event_to_analyze)
        {
            std::cout<<" Size of MWD trace = " << trace_MWD.size() << "\n";
            //std::cout<< " Event Number : " << Eventno << ", event to analyze : " << event_to_analyze << "\n";
            for (int i = 0; i < trace_febex.size(); i++)
            {            
                h2_traces[ch_ID]->Fill(i*0.01,trace_febex[i]);
            }

            for (int i = 0; i < trace_MWD.size(); i++)
            {            
                h2_traces_MWD[ch_ID]->Fill((i + start_MWD_plot)*0.01,trace_MWD[i]);
            }
        }
    
    }
    //c4LOG(info, "::::::::::END LOOP::::::::::::" << " Layer number :" << layer_number);        

    fNEvents += 1;
}

void LisaTraceAnalysis::FinishEvent()
{

}

void LisaTraceAnalysis::FinishTask()
{

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_lisa->Write();
    c4LOG(info, "Written LISA analysis histograms to file.");
    c4LOG(info, "LISA events : " << fNEvents);


}

ClassImp(LisaTraceAnalysis)
