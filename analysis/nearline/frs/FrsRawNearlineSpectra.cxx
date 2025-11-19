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
    frs_config = TFrsConfiguration::GetInstance();
    frs = frs_config->FRS();
    mw = frs_config->MW();
    tpc = frs_config->TPC();
    music = frs_config->MUSIC();
    labr = frs_config->LABR();
    sci = frs_config->SCI();
    id = frs_config->ID();
    si = frs_config->SI();
    mrtof = frs_config->MRTOF();
    range = frs_config->Range();
}

FrsRawNearlineSpectra::FrsRawNearlineSpectra(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   fNEvents(0)
    ,   header(nullptr) 
    ,   sciArray(nullptr)
    ,   musicArray(nullptr)
    ,   tpcArray(nullptr)
{
    exp_config = TExperimentConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    frs = frs_config->FRS();
    mw = frs_config->MW();
    tpc = frs_config->TPC();
    music = frs_config->MUSIC();
    labr = frs_config->LABR();
    sci = frs_config->SCI();
    id = frs_config->ID();
    si = frs_config->SI();
    mrtof = frs_config->MRTOF();
    range = frs_config->Range();
}

FrsRawNearlineSpectra::~FrsRawNearlineSpectra()
{
    c4LOG(info, "");
}

InitStatus FrsRawNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

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
    for (int ihist = 0; ihist < 32; ihist++)
    {
        h1_sci_de[ihist] = MakeTH1(dir_sci_de, "F", Form("h1_sci_de_%i", ihist), Form("Scintillator dE Channel %i", ihist), 4096, 0, 4096);
    }

    // TAC dT
    for (int ihist = 0; ihist < 32; ihist++)
    {
        h1_sci_dt[ihist] = MakeTH1(dir_sci_dt, "F", Form("h1_sci_dt_%i", ihist), Form("Scintillator dT Channel %i", ihist), 4096, 0, 4096); // need to figure out ranges
    }

    // MHTDC SCI
    h1_sci_mhtdc_11la = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_11la","MHTDC 11LA", 4000, 0, 100000);
    h1_sci_mhtdc_11lb = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_11lb","MHTDC 11LB", 4000, 0, 100000);
    h1_sci_mhtdc_11lc = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_11lc","MHTDC 11LC", 4000, 0, 100000);
    h1_sci_mhtdc_11ld = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_11ld","MHTDC 11LD", 4000, 0, 100000);
    h1_sci_mhtdc_21l = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_21l","MHTDC 21L", 4000, 0, 100000);
    h1_sci_mhtdc_22l = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_22l","MHTDC 22L", 4000, 0, 100000);
    h1_sci_mhtdc_31l = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_31l","MHTDC 31L", 4000, 0, 100000);
    h1_sci_mhtdc_41l = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_41l","MHTDC 41L", 4000, 0, 100000);
    h1_sci_mhtdc_42l = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_42l","MHTDC 42L", 4000, 0, 100000);
    h1_sci_mhtdc_43l = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_43l","MHTDC 43L", 4000, 0, 100000);
    h1_sci_mhtdc_81l = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_81l","MHTDC 81L", 4000, 0, 100000);

    h1_sci_mhtdc_11ra = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_11ra","MHTDC 11RA", 4000, 0, 100000);
    h1_sci_mhtdc_11rb = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_11rb","MHTDC 11RB", 4000, 0, 100000);
    h1_sci_mhtdc_11rc = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_11rc","MHTDC 11RC", 4000, 0, 100000);
    h1_sci_mhtdc_11rd = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_11rd","MHTDC 11RD", 4000, 0, 100000);
    h1_sci_mhtdc_21r = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_21r","MHTDC 21R", 4000, 0, 100000);
    h1_sci_mhtdc_22r = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_22r","MHTDC 22R", 4000, 0, 100000);
    h1_sci_mhtdc_31r = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_31r","MHTDC 31R", 4000, 0, 100000);
    h1_sci_mhtdc_41r = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_41r","MHTDC 41R", 4000, 0, 100000);
    h1_sci_mhtdc_42r = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_42r","MHTDC 42R", 4000, 0, 100000);
    h1_sci_mhtdc_43r = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_43r","MHTDC 43R", 4000, 0, 100000);
    h1_sci_mhtdc_81r = MakeTH1(dir_sci_mhtdc,"F","h1_sci_mhtdc_81r","MHTDC 81R", 4000, 0, 100000);


    // To replace with crate mapping maybe
    std::map<int, std::string> mhtdcNames = {
        {16, "mhtdc_11LA"},
        {17, "mhtdc_11LB"},
        {18, "mhtdc_11LC"},
        {19, "mhtdc_11LD"},
        {20, "mhtdc_11RA"},
        {21, "mhtdc_11RB"},
        {22, "mhtdc_11RC"},
        {23, "mhtdc_11RD"},
        {2,  "mhtdc_21L"},
        {3,  "mhtdc_21R"},
        {13, "mhtdc_22L"},
        {14, "mhtdc_22R"},
        {10, "mhtdc_31L"},
        {11, "mhtdc_31R"},
        {0,  "mhtdc_41L"},
        {1,  "mhtdc_41R"},
        {4,  "mhtdc_42L"},
        {15, "mhtdc_42R"},
        {6,  "mhtdc_43L"},
        {7,  "mhtdc_43R"},
        {8,  "mhtdc_81L"},
        {9,  "mhtdc_81R"}
    };

    for (int ihist = 0; ihist < 32; ihist++)
    {
        std::string hname;
        if (mhtdcNames.count(ihist))
            hname = mhtdcNames[ihist];
        else
            hname = "empty";

        h1_sci_mhtdc[ihist] = MakeTH1(dir_sci_mhtdc,"F",Form("h1_%s_%i", hname.c_str(), ihist),Form("%s", hname.c_str()),4000, 0, 100000);
    }


    // // MHTDC T
    // for (int ihist = 0; ihist < 32; ihist++)
    // {
    //     h1_sci_mhtdc[ihist] = MakeTH1(dir_sci_mhtdc, "F", Form("h1_sci_mhtdc_%i", ihist), Form("Scintillator MHTDC T Channel %i", ihist), 4000, 0, 100000); // need to figure out ranges
    // }


    
    // ::: MUSIC :::::: 
    // dir_music_e = dir_music->mkdir("E");
    // dir_music_t = dir_music->mkdir("T");
    // c4LOG(info,"4");
    // for (int j = 0; j < 5; j++)
    // {
    //     dir_music_n_e[j] = dir_music_e->mkdir(Form("MUSIC %i", j));

    //     c4LOG(info,"5");
    //     for (int ihist = 0; ihist < 8; ihist++)
    //     {
    //         h1_music_anode_e[j][ihist] = MakeTH1(dir_music_n_e[j], "F", Form("h1_music_%i_e_anode_%i", j, ihist), Form("MUSIC %i Anode %i", j, ihist), 4096, 0, 4096); // need to figure out ranges
    //     }
    //     dir_music_n_t[j] = dir_music_t->mkdir(Form("MUSIC %i", j));

    //     c4LOG(info,"6");
    //     for (int ihist = 0; ihist < 8; ihist++)
    //     {
    //         c4LOG(info,"7");
    //         h1_music_anode_t[j][ihist] = MakeTH1(dir_music_n_t[j], "F", Form("h1_music_%i_t_anode_%i", j, ihist), Form("MUSIC %i Anode %i", j, ihist), 4000, 0, 100000); // need to figure out ranges
    //     }
    // }

    // ::: TPCs :::::
    dir_tpc_adc = dir_tpc->mkdir("ADC");
    dir_tpc_tdc = dir_tpc->mkdir("TPC");

    for (int j = 0; j < 7; j++)
    {
        dir_tpc_n_adc[j] = dir_tpc_adc->mkdir(Form("TPC %i ADCs", j));

        // c_tpc_n_adc[j] = new TCanvas(Form("c_tpc_%i_adc", j), Form("TPC %i ADC Spectra", j) , 650, 350);
        // c_tpc_n_adc[j]->Divide(2, 4);
        for (int ihist = 0; ihist < 8; ihist++)
        {
            // c_tpc_n_adc[j]->cd(ihist+1);
            h1_tpc_adc[j][ihist] = MakeTH1(dir_tpc_n_adc[j], "F", Form("dir_tpc_%i_adc_%i", j, ihist), Form("TPC %i ADC Channel %i", j, ihist), 2000, 0, 2000);
            h1_tpc_adc[j][ihist]->Draw();
        }
        // c_tpc_n_adc[j]->cd(0);
        // dir_tpc_n_adc[j]->Append(c_tpc_n_adc[j]);
    }

    // c_tpc_tdc = new TCanvas("c_tpc_tdc", "TPC TDC Spectra", 650, 350);
    // c_tpc_tdc->Divide(8, 16); // this will obviously look insane
    for (int ihist = 0; ihist < 128; ihist++)
    {
        // c_tpc_tdc->cd(ihist+1);
        h1_tpc_tdc[ihist] = MakeTH1(dir_tpc_tdc, "F", Form("h1_tpc_tdc_%i", ihist), Form("TPC TDC Channel %i", ihist), 2000, 0, 2000);
        h1_tpc_tdc[ihist]->Draw();
    }
    // c_tpc_tdc->cd(0);
    // dir_tpc_tdc->Append(c_tpc_tdc);




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

    sci_11LA_chan.emplace_back(frs_config->Get_mhtdc_11LA_chan());
    sci_11LB_chan.emplace_back(frs_config->Get_mhtdc_11LB_chan());
    sci_11LC_chan.emplace_back(frs_config->Get_mhtdc_11LC_chan());
    sci_11LD_chan.emplace_back(frs_config->Get_mhtdc_11LD_chan());
    sci_21L_chan.emplace_back(frs_config->Get_mhtdc_21L_chan());
    sci_22L_chan.emplace_back(frs_config->Get_mhtdc_22L_chan());
    sci_31L_chan.emplace_back(frs_config->Get_mhtdc_31L_chan());
    sci_41L_chan.emplace_back(frs_config->Get_mhtdc_41L_chan());
    sci_42L_chan.emplace_back(frs_config->Get_mhtdc_42L_chan());
    sci_43L_chan.emplace_back(frs_config->Get_mhtdc_43L_chan());
    sci_81L_chan.emplace_back(frs_config->Get_mhtdc_81L_chan());
    sci_11RA_chan.emplace_back(frs_config->Get_mhtdc_11RA_chan());
    sci_11RB_chan.emplace_back(frs_config->Get_mhtdc_11RB_chan());
    sci_11RC_chan.emplace_back(frs_config->Get_mhtdc_11RC_chan());
    sci_11RD_chan.emplace_back(frs_config->Get_mhtdc_11RD_chan());
    sci_21R_chan.emplace_back(frs_config->Get_mhtdc_21R_chan());
    sci_22R_chan.emplace_back(frs_config->Get_mhtdc_22R_chan());
    sci_31R_chan.emplace_back(frs_config->Get_mhtdc_31R_chan());
    sci_41R_chan.emplace_back(frs_config->Get_mhtdc_41R_chan());
    sci_42R_chan.emplace_back(frs_config->Get_mhtdc_42R_chan());
    sci_43R_chan.emplace_back(frs_config->Get_mhtdc_43R_chan());
    sci_81R_chan.emplace_back(frs_config->Get_mhtdc_81R_chan());

    for (int j = 0; j < sci_11LA_chan.size(); j++)h1_sci_mhtdc_11la->Fill(sci_11LA_chan[j]);
    for (int j = 0; j < sci_11LB_chan.size(); j++)h1_sci_mhtdc_11lb->Fill(sci_11LB_chan[j]);
    for (int j = 0; j < sci_11LC_chan.size(); j++)h1_sci_mhtdc_11lc->Fill(sci_11LC_chan[j]);
    for (int j = 0; j < sci_11LD_chan.size(); j++)h1_sci_mhtdc_11ld->Fill(sci_11LD_chan[j]);
    for (int j = 0; j < sci_21L_chan.size(); j++)h1_sci_mhtdc_21l->Fill(sci_21L_chan[j]);
    for (int j = 0; j < sci_22L_chan.size(); j++)h1_sci_mhtdc_22l->Fill(sci_22L_chan[j]);
    for (int j = 0; j < sci_31L_chan.size(); j++)h1_sci_mhtdc_31l->Fill(sci_31L_chan[j]);
    for (int j = 0; j < sci_41L_chan.size(); j++)h1_sci_mhtdc_41l->Fill(sci_41L_chan[j]);
    for (int j = 0; j < sci_42L_chan.size(); j++)h1_sci_mhtdc_42l->Fill(sci_42L_chan[j]);
    for (int j = 0; j < sci_43L_chan.size(); j++)h1_sci_mhtdc_43l->Fill(sci_43L_chan[j]);
    for (int j = 0; j < sci_81L_chan.size(); j++)h1_sci_mhtdc_81l->Fill(sci_81L_chan[j]);

    for (int j = 0; j < sci_11RA_chan.size(); j++)h1_sci_mhtdc_11ra->Fill(sci_11RA_chan[j]);
    for (int j = 0; j < sci_11RB_chan.size(); j++)h1_sci_mhtdc_11rb->Fill(sci_11RB_chan[j]);
    for (int j = 0; j < sci_11RC_chan.size(); j++)h1_sci_mhtdc_11rc->Fill(sci_11RC_chan[j]);
    for (int j = 0; j < sci_11RD_chan.size(); j++)h1_sci_mhtdc_11rd->Fill(sci_11RD_chan[j]);
    for (int j = 0; j < sci_21R_chan.size(); j++)h1_sci_mhtdc_21r->Fill(sci_21R_chan[j]);
    for (int j = 0; j < sci_22R_chan.size(); j++)h1_sci_mhtdc_22r->Fill(sci_22R_chan[j]);
    for (int j = 0; j < sci_31R_chan.size(); j++)h1_sci_mhtdc_31r->Fill(sci_31R_chan[j]);
    for (int j = 0; j < sci_41R_chan.size(); j++)h1_sci_mhtdc_41r->Fill(sci_41R_chan[j]);
    for (int j = 0; j < sci_42R_chan.size(); j++)h1_sci_mhtdc_42r->Fill(sci_42R_chan[j]);
    for (int j = 0; j < sci_43R_chan.size(); j++)h1_sci_mhtdc_43r->Fill(sci_43R_chan[j]);
    for (int j = 0; j < sci_81R_chan.size(); j++)h1_sci_mhtdc_81r->Fill(sci_81R_chan[j]);


    // auto const & musicItem = musicArray->at(0);
    // musicE = musicItem.Get_music_e();
    // musicT = musicItem.Get_music_t();

    // for (int i = 0; i < 5; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         h1_music_anode_e[i][j]->Fill(musicE[i][j]);
    //         h1_music_anode_t[i][j]->Fill(musicT[i][j]);
    //     }
    // }


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

    sci_11LA_chan.clear();
    sci_11LB_chan.clear();
    sci_11LC_chan.clear();
    sci_11LD_chan.clear();
    sci_21L_chan.clear();
    sci_22L_chan.clear();
    sci_31L_chan.clear();
    sci_41L_chan.clear();
    sci_42L_chan.clear();
    sci_43L_chan.clear();
    sci_81L_chan.clear();
    sci_11RA_chan.clear();
    sci_11RB_chan.clear();
    sci_11RC_chan.clear();
    sci_11RD_chan.clear();
    sci_21R_chan.clear();
    sci_22R_chan.clear();
    sci_31R_chan.clear();
    sci_41R_chan.clear();
    sci_42R_chan.clear();
    sci_43R_chan.clear();
    sci_81R_chan.clear();

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
