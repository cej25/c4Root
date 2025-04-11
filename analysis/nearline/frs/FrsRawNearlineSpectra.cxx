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
 *                             C.E. Jones                                     *
 *                              17.12.24                                      *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsRawNearlineSpectra.h"
#include "EventHeader.h"
#include "c4Logger.h"
#include "AnalysisTools.h"

// ROOT
#include "TCanvas.h"
#include "TClonesArray.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <vector>
#include "TFile.h"

FrsRawNearlineSpectra::FrsRawNearlineSpectra()
    :   FrsRawNearlineSpectra("FrsRawNearlineSpectra", 1)
{
}

FrsRawNearlineSpectra::FrsRawNearlineSpectra(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   fNEvents(0)
    ,   header(nullptr) 
    ,   sciArray(nullptr)
    ,   musicArray(nullptr)
    ,   tpcArray(nullptr)
{
}

FrsRawNearlineSpectra::~FrsRawNearlineSpectra()
{
    c4LOG(info, "");
}

InitStatus FrsRawNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = mgr->InitObjectAs<decltype(header)>("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found!");

    sciArray = mgr->InitObjectAs<decltype(sciArray)>("FrsSciData");
    c4LOG_IF(fatal, !sciArray, "Branch FrsSciData not found!");
    musicArray = mgr->InitObjectAs<decltype(musicArray)>("FrsMusicData");
    c4LOG_IF(fatal, !musicArray, "Branch FrsMusicData not found!");
    tpcArray = mgr->InitObjectAs<decltype(tpcArray)>("FrsTpcData");
    c4LOG_IF(fatal, !tpcArray, "Branch FrsTpcData not found!");

    TDirectory::TContext ctx(nullptr);

   
    dir_frs = (TDirectory*)mgr->GetObject("FRS");
    if (dir_frs == nullptr) 
    {
        LOG(info) << "Creating FRS Directory";
        FairRootManager::Instance()->GetOutFile()->cd();
        dir_frs = gDirectory->mkdir("FRS");
        mgr->Register("FRS", "FRS Directory", dir_frs, false); // allow other tasks to find this
        found_dir_frs = false;
    }

    dir_frs_raw = dir_frs->mkdir("FRS Raw Spectra");
    dir_sci = dir_frs_raw->mkdir("Scintillators");
    dir_music = dir_frs_raw->mkdir("MUSICs");
    dir_tpc = dir_frs_raw->mkdir("TPCs");

    // ::: SCI ::::: 
    dir_sci_de = dir_sci->mkdir("dE");
    dir_sci_dt = dir_sci->mkdir("dT");
    dir_sci_mhtdc = dir_sci->mkdir("MHTDC T");
    
    // TAC dE
    c_sci_de = new TCanvas("c_sci_de", "Scintillator dE spectra", 650, 350);
    c_sci_de->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_sci_de->cd(ihist+1);
        h1_sci_de[ihist] = MakeTH1(dir_sci_de, "F", Form("h1_sci_de_%i", ihist), Form("Scintillator dE Channel %i", ihist), 4096, 0, 4096);
        h1_sci_de[ihist]->Draw();
    }
    c_sci_de->cd(0);
    dir_sci_de->Append(c_sci_de);

    // TAC dT
    c_sci_dt = new TCanvas("c_sci_dt", "Scintillator dT spectra", 650, 350);
    c_sci_dt->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_sci_dt->cd(ihist+1);
        h1_sci_dt[ihist] = MakeTH1(dir_sci_dt, "F", Form("h1_sci_dt_%i", ihist), Form("Scintillator dT Channel %i", ihist), 4096, 0, 4096); // need to figure out ranges
        h1_sci_dt[ihist]->Draw();
    }
    c_sci_dt->cd(0);
    dir_sci_dt->Append(c_sci_dt);

    // MHTDC T
    c_sci_mhtdc = new TCanvas("c_sci_mhtdc", "Scintillator MHTDC T spectra", 650, 350);
    c_sci_mhtdc->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_sci_mhtdc->cd(ihist+1);
        h1_sci_mhtdc[ihist] = MakeTH1(dir_sci_mhtdc, "F", Form("h1_sci_mhtdc_%i", ihist), Form("Scintillator MHTDC T Channel %i", ihist), 4000, 0, 100000); // need to figure out ranges
        h1_sci_mhtdc[ihist]->Draw();
    }
    c_sci_mhtdc->cd(0);
    dir_sci_mhtdc->Append(c_sci_mhtdc);

    
    // ::: MUSIC :::::: 
    dir_music_e = dir_music->mkdir("E");
    dir_music_t = dir_music->mkdir("T");

    for (int j = 0; j < 5; j++)
    {
        dir_music_n_e[j] = dir_music_e->mkdir(Form("MUSIC %i", j));

        c_music_n_e[j] = new TCanvas(Form("c_music_%i_e", j), Form("MUSIC %i Anode E spectra", j), 650, 350);
        c_music_n_e[j]->Divide(5, 4);
        for (int ihist = 0; ihist < 8; ihist++)
        {
            c_music_n_e[j]->cd(ihist+1);
            h1_music_anode_e[j][ihist] = MakeTH1(dir_music_n_e[j], "F", Form("h1_music_%i_e_anode_%i", j, ihist), Form("MUSIC %i Anode %i", j, ihist), 4096, 0, 4096); // need to figure out ranges
            h1_music_anode_e[j][ihist]->Draw();
        }
        c_music_n_e[j]->cd(0);
        dir_music_n_e[j]->Append(c_music_n_e[j]);

        dir_music_n_t[j] = dir_music_t->mkdir(Form("MUSIC %i", j));

        c_music_n_t[j] = new TCanvas(Form("c_music_%i_t", j), Form("MUSIC %i Anode T spectra", j), 650, 350);
        c_music_n_t[j]->Divide(5, 4);
        for (int ihist = 0; ihist < 8; ihist++)
        {
            c_music_n_t[j]->cd(ihist+1);
            h1_music_anode_t[j][ihist] = MakeTH1(dir_music_n_t[j], "F", Form("h1_music_%i_t_anode_%i", j, ihist), Form("MUSIC %i Anode %i", j, ihist), 4000, 0, 100000); // need to figure out ranges
            h1_music_anode_t[j][ihist]->Draw();
        }
        c_music_n_t[j]->cd(0);
        dir_music_n_t[j]->Append(c_music_n_t[j]);
    }

    
    // ::: TPCs :::::
    dir_tpc_adc = dir_tpc->mkdir("ADC");
    dir_tpc_tdc = dir_tpc->mkdir("TPC");

    for (int j = 0; j < 7; j++)
    {
        dir_tpc_n_adc[j] = dir_tpc_adc->mkdir(Form("TPC %i ADCs", j));

        c_tpc_n_adc[j] = new TCanvas(Form("c_tpc_%i_adc", j), Form("TPC %i ADC Spectra", j) , 650, 350);
        c_tpc_n_adc[j]->Divide(2, 4);
        for (int ihist = 0; ihist < 8; ihist++)
        {
            c_tpc_n_adc[j]->cd(ihist+1);
            h1_tpc_adc[j][ihist] = MakeTH1(dir_tpc_n_adc[j], "F", Form("dir_tpc_%i_adc_%i", j, ihist), Form("TPC %i ADC Channel %i", j, ihist), 2000, 0, 2000);
            h1_tpc_adc[j][ihist]->Draw();
        }
        c_tpc_n_adc[j]->cd(0);
        dir_tpc_n_adc[j]->Append(c_tpc_n_adc[j]);
    }

    c_tpc_tdc = new TCanvas("c_tpc_tdc", "TPC TDC Spectra", 650, 350);
    c_tpc_tdc->Divide(8, 16); // this will obviously look insane
    for (int ihist = 0; ihist < 128; ihist++)
    {
        c_tpc_tdc->cd(ihist+1);
        h1_tpc_tdc[ihist] = MakeTH1(dir_tpc_tdc, "F", Form("h1_tpc_tdc_%i", ihist), Form("TPC TDC Channel %i", ihist), 2000, 0, 2000);
        h1_tpc_tdc[ihist]->Draw();
    }
    c_tpc_tdc->cd(0);
    dir_tpc_tdc->Append(c_tpc_tdc);




    return kSUCCESS;

}


void FrsRawNearlineSpectra::Exec(Option_t* option)
{
    if (sciArray->size() == 0) return;


    auto const & sciItem = sciArray->at(0);
    sciDE = sciItem.Get_de_array();
    sciDT = sciItem.Get_dt_array();
    sciMHTDC = sciItem.Get_mhtdc_array();

    for (int i = 0; i < 32; i++)
    {
        h1_sci_de[i]->Fill(sciDE[i]);
        h1_sci_dt[i]->Fill(sciDT[i]);
        for (int j = 0; j < sciMHTDC[i].size(); j++) h1_sci_mhtdc[i]->Fill(sciMHTDC[i][j]);
    }
    
    auto const & musicItem = musicArray->at(0);
    musicE = musicItem.Get_music_e();
    musicT = musicItem.Get_music_t();

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            h1_music_anode_e[i][j]->Fill(musicE[i][j]);
            h1_music_anode_t[i][j]->Fill(musicT[i][j]);
        }
    }



    auto const & tpcItem = tpcArray->at(0);
    adcData = tpcItem.Get_adc_data();
    tdcData = tpcItem.Get_tdc_data();

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            h1_tpc_adc[i][j]->Fill(adcData[i][j]);
        }
    }

    for (int i = 0; i < 128; i++) for (int j = 0; j < tdcData[i].size(); j++) h1_tpc_tdc[i]->Fill(tdcData[i].at(j));

    
    

}

void FrsRawNearlineSpectra::FinishEvent()
{

}


void FrsRawNearlineSpectra::FinishTask()
{
    if (found_dir_frs == false)
    {
        TDirectory* tmp = gDirectory;
        FairRootManager::Instance()->GetOutFile()->cd();
        dir_frs->Write();
        gDirectory = tmp;
        c4LOG(info, "Written FRS Raw histograms to file.");
    }
}

ClassImp(FrsRawNearlineSpectra)
