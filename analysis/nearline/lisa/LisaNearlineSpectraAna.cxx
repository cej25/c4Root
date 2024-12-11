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
 *                               25..11.24                                    *
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
#include "LisaNearlineSpectraAna.h"
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

LisaNearlineSpectraAna::LisaNearlineSpectraAna()  :   LisaNearlineSpectraAna("LisaNearlineSpectraAna")
{
    lisa_config = TLisaConfiguration::GetInstance();
}

LisaNearlineSpectraAna::LisaNearlineSpectraAna(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    // , fHitLisa(NULL)
    , fNEvents(0)
    , header(nullptr)
    // ranges
{
    lisa_config = TLisaConfiguration::GetInstance();
    exp_config = TExperimentConfiguration::GetInstance();

}

LisaNearlineSpectraAna::~LisaNearlineSpectraAna()
{
    c4LOG(info, "");
}

void LisaNearlineSpectraAna::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus LisaNearlineSpectraAna::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaAnaArray = mgr->InitObjectAs<decltype(lisaAnaArray)>("LisaAnaData");
    c4LOG_IF(fatal, !lisaAnaArray, "Branch LisaAnaData not found!");

    FairRootManager::Instance()->GetOutFile()->cd();
    dir_lisa = gDirectory->mkdir("LISA");
    mgr->Register("LISA", "LISA Directory", dir_lisa, false); // allow other tasks to find this
   
    dir_lisa->cd();
    dir_energy = dir_lisa->mkdir("Energy");
    dir_traces = dir_lisa->mkdir("Traces");
    dir_energy_MWD = dir_energy->mkdir("MWD");
    dir_traces_MWD = dir_traces->mkdir("MWD");
      
  
    dir_energy->cd();
    // :::::  E N E R G Y :::::

    // ::: Energy for all channels
    h1_energy.resize(8);
    for (int i = 0; i < 8; i++) 
    {  
        h1_energy[i] = new TH1F(Form("energy_%i", i), Form("Energy_%i",i), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
        h1_energy[i]->GetXaxis()->SetTitle("E(febex) [a.u.]");
        h1_energy[i]->SetLineColor(kBlack+1);
        h1_energy[i]->Draw();      
    }
    
    dir_energy_MWD->cd();
    // ::: Energy MWD
    h1_energy_MWD.resize(8);
    for (int i = 0; i < 8; i++) 
    {  
        h1_energy_MWD[i] = new TH1F(Form("energy_MWD_%i", i), Form("Energy_%i",i), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
        h1_energy_MWD[i]->GetXaxis()->SetTitle("E(MWD) [a.u.]");
        h1_energy_MWD[i]->SetLineColor(kRed+1);
        h1_energy_MWD[i]->Draw();      
    }
    
    dir_traces->cd();
    // ::::: T R A C E S ::::
    
    //::::::::::::Traces for all channels
    h2_traces.resize(8);
    for (int i = 0; i < 8; i++) 
    {
        h2_traces[i] = new TH2F(Form("h2_traces_%i", i), Form("Traces_%i",i), 250, 0, 2000,300,3000,15000);
        h2_traces[i]->GetXaxis()->SetTitle("Time [us/0.01]");
        h2_traces[i]->SetMinimum(lisa_config->AmplitudeMin);
        h2_traces[i]->SetMaximum(lisa_config->AmplitudeMax);
        h2_traces[i]->SetOption("colz");

    }


    // ::: mapping for histo filling
    mapping[1] = 0;
    mapping[2] = 1;
    mapping[5] = 2;
    mapping[6] = 3;
    mapping[9] = 4;
    mapping[10] = 5;
    mapping[13] = 6;
    mapping[14] = 7;

    return kSUCCESS;
}


void LisaNearlineSpectraAna::Exec(Option_t* option)
{   
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
        h1_energy[mapping[ch_ID]]->Fill(energy_febex);
        h1_energy_MWD[mapping[ch_ID]]->Fill(energy_MWD);			     
                           
        // :::: Fill traces stats :::
        for (int i = 0; i < trace_febex.size(); i++)
        {            
	        h2_traces[mapping[ch_ID]]->Fill(i,trace_febex[i]);
        }
    
    }
    //c4LOG(info, "::::::::::END LOOP::::::::::::" << " Layer number :" << layer_number);        

    fNEvents += 1;
}

void LisaNearlineSpectraAna::FinishEvent()
{

}

void LisaNearlineSpectraAna::FinishTask()
{

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_lisa->Write();
    c4LOG(info, "Written LISA analysis histograms to file.");
    c4LOG(info, "LISA events : " << fNEvents);


}

ClassImp(LisaNearlineSpectraAna)
