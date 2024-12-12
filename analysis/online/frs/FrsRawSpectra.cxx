// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsRawSpectra.h"
#include "FrsMainData.h"
#include "FrsTPCData.h"
#include "FrsUserData.h"
#include "EventHeader.h"
#include "c4Logger.h"

// ROOT
#include "TCanvas.h"
#include "TClonesArray.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <vector>

FrsRawSpectra::FrsRawSpectra()
    :   FrsRawSpectra("FrsRawSpectra", 1)
{
}

FrsRawSpectra::FrsRawSpectra(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   fNEvents(0)
    ,   header(nullptr) 
    ,   v792arrayMain(nullptr)
    ,   v1290arrayMain(nullptr)
    ,   v7x5arrayTPC(nullptr)
    ,   v1190arrayTPC(nullptr)
    ,   v7x5arrayUser(nullptr)
{
}

FrsRawSpectra::~FrsRawSpectra()
{
    c4LOG(info, "");
}

InitStatus FrsRawSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    v792arrayMain = mgr->InitObjectAs<decltype(v792arrayMain)>("FrsMainV792Data");
    c4LOG_IF(fatal, !v792arrayMain, "Branch FrsMainV792Data not found!");
    v1290arrayMain = mgr->InitObjectAs<decltype(v1290arrayMain)>("FrsMainV1290Data");
    c4LOG_IF(fatal, !v1290arrayMain, "Branch FrsMainV1290Data not found!");
    v7x5arrayTPC = mgr->InitObjectAs<decltype(v7x5arrayTPC)>("FrsTPCV7X5Data");
    c4LOG_IF(fatal, !v7x5arrayTPC, "Branch v7x5array not found!");
    v1190arrayTPC = mgr->InitObjectAs<decltype(v1190arrayTPC)>("FrsTPCV1190Data");
    c4LOG_IF(fatal, !v1190arrayTPC, "Branch v1190array not found!");
    v7x5arrayUser = mgr->InitObjectAs<decltype(v7x5arrayUser)>("FrsUserV7X5Data");
    c4LOG_IF(fatal, !v7x5arrayUser, "Branch FrsUserV7X5Data not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");
    
    TDirectory::TContext ctx(nullptr);

    // look for FRS directory, create it if not found
    dir_frs = (TDirectory*)mgr->GetObject("FRS");
    if (dir_frs == nullptr) 
    {
        LOG(info) << "Creating FRS Online Directory";
        dir_frs = new TDirectory("FRS Online", "FRS Online", "", 0);
        mgr->Register("FRS", "FRS Online Directory", dir_frs, false); // allow other tasks to find this
        histograms->Add(dir_frs);
    }
    
    dir_frs_raw = dir_frs->mkdir("FRS Raw Spectra");
    dir_frs_raw_main = dir_frs_raw->mkdir("Main Crate");
    dir_frs_raw_tpc = dir_frs_raw->mkdir("TPC Crate");
    dir_frs_raw_user = dir_frs_raw->mkdir("User Crate");

    dir_raw_v792_main = dir_frs_raw_main->mkdir("V792 (Main)");
    dir_raw_v1290_main = dir_frs_raw_main->mkdir("V1290 (Main)");
    dir_raw_v7x5_tpc = dir_frs_raw_tpc->mkdir("V7X5 (TPC)");
    dir_raw_v1190_tpc = dir_frs_raw_tpc->mkdir("V1190 (TPC)");
    dir_raw_v7x5_user = dir_frs_raw_user->mkdir("V7X5 (User)"); 

    // ---- * Main Crate * ---- //

    // Geo = 14
    dir_raw_v792_main->cd();
    c_v792_main = new TCanvas("c_v792_main", "Raw V792 (Main Crate) spectra", 650, 350); //?
    c_v792_main->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v792_main->cd(ihist+1);
        h1_v792_main_data[ihist] = new TH1F(Form("h1_v792_main_data_%i", ihist), Form("V792 Data - Channel %i", ihist), 1000, 0, 1000.);
        h1_v792_main_data[ihist]->Draw();
    }
    c_v792_main->cd(0);
    dir_raw_v792_main->Append(c_v792_main);

    h2_v792_main_data_vs_chan = new TH2F("h2_v792_main_data_vs_chan", "V792 Data vs Channel", 32, 0, 32, 1000, 0, 1000.);

    // Geo = ?? V1290
    dir_raw_v1290_main->cd();
    c_v1290_main_mult = new TCanvas("c_v1290_main_mult", "V1290 (Main Crate) Multiplicity", 650, 350);
    c_v1290_main_mult->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v1290_main_mult->cd(ihist+1);
        h1_v1290_main_mult[ihist] = new TH1F(Form("h1_v1290_main_mult_%i", ihist), Form("V1290 Multiplicity - Channel %i", ihist), 10, 0, 10);
        h1_v1290_main_mult[ihist]->Draw();
    }
    c_v1290_main_mult->cd(0);
    dir_raw_v1290_main->Append(c_v1290_main_mult);

    c_v1290_main_leads = new TCanvas("c_v1290_main_leads", "V1290 (Main Crate) Leads", 650, 350);
    c_v1290_main_leads->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v1290_main_leads->cd(ihist+1);
        h1_v1290_main_leads[ihist] = new TH1F(Form("h1_v1290_main_leads_%i", ihist), Form("V1290 Data (Leads) - Channel %i", ihist), 4000, 0, 200000);
        h1_v1290_main_leads[ihist]->Draw();
    }
    c_v1290_main_leads->cd(0);
    dir_raw_v1290_main->Append(c_v1290_main_leads);

    h2_v1290_main_data_vs_chan = new TH2F("h2_v1290_main_data_vs_chan", "V1290 Data vs Channel", 32, 0, 32, 4000, 0, 200000);
    // ----------------------- //

    // ---- * TPC Crate * ---- //

    // Geo = 12
    dir_raw_v7x5_tpc->cd();
    c_v7x5_tpc_geo12 = new TCanvas("c_v7x5_tpc_geo12", "Raw V7X5 - Geo 12 (TPC Crate) spectra", 650, 350);
    c_v7x5_tpc_geo12->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v7x5_tpc_geo12->cd(ihist+1);
        h1_v7x5_tpc_data12[ihist] = new TH1F(Form("h1_v7x5_tpc_data12_%i", ihist), Form("V7X5 Data (Geo 12, Channel %i)", ihist), 2000, 0., 2000.);
        h1_v7x5_tpc_data12[ihist]->Draw();
    }
    c_v7x5_tpc_geo12->cd(0);
    dir_raw_v7x5_tpc->Append(c_v7x5_tpc_geo12);

    h2_v7x5_tpc_data12_vs_chan = new TH2F("h2_v7x5_tpc_data12_vs_chan", "V7X5 Data (Geo 12) vs Channel", 32, 0, 32, 2000, 0., 2000.);

    // Geo = 8
    c_v7x5_tpc_geo8 = new TCanvas("c_v7x5_tpc_geo8", "Raw V7X5 - Geo 8 (TPC Crate) spectra", 650, 350);
    c_v7x5_tpc_geo8->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v7x5_tpc_geo8->cd(ihist+1);
        h1_v7x5_tpc_data8[ihist] = new TH1F(Form("h1_v7x5_tpc_data8_%i", ihist), Form("V7X5 Data (Geo 8, Channel %i)", ihist), 2000, 0., 2000.);
        h1_v7x5_tpc_data8[ihist]->Draw();
    }
    c_v7x5_tpc_geo8->cd(0);
    dir_raw_v7x5_tpc->Append(c_v7x5_tpc_geo8);

    h2_v7x5_tpc_data8_vs_chan = new TH2F("h2_v7x5_tpc_data8_vs_chan", "V7X5 Data (Geo 8) vs Channel", 32, 0, 32, 2000, 0, 2000.);

    // Geo = ?? V1190
    dir_raw_v1190_tpc->cd();
    c_v1190_tpc = new TCanvas("c_v1190_tpc", "Raw V1190 (TPC Crate) spectra", 650, 350);
    c_v1190_tpc->Divide(8, 16); // is this sensible lol
    for (int ihist = 0; ihist < 128; ihist++)
    {
        c_v1190_tpc->cd(ihist+1);
        h1_v1190_tpc_data[ihist] = new TH1F(Form("h1_v1190_tpc_data_%i", ihist), Form("V1190 Data - Channel %i", ihist), 4000, 0., 200000.);
        h1_v1190_tpc_data[ihist]->Draw();
    }
    c_v1190_tpc->cd(0);
    dir_raw_v1190_tpc->Append(c_v1190_tpc);

    h2_v1190_tpc_data_vs_chan = new TH2F("h2_v1190_tpc_data_vs_chan", "V1190 Data vs Chan", 128, 0, 128, 4000, 0, 200000.);
    h2_v1190_tpc_data_vs_chan_1st_hit = new TH2F("h2_v1190_tpc_data_vs_chan_1st_hit", "V1190 Data vs Chan (1st Hit)", 128, 0, 128, 4000, 0., 200000.);
    // ------------------------ //

    // ---- * User Crate * ---- //

    // Geo = 10
    dir_raw_v7x5_user->cd();
    c_v7x5_user_geo10 = new TCanvas("c_v7x5_user_geo10", "Raw V7X5 Geo 10 (User Crate) spectra", 650, 350);
    c_v7x5_user_geo10->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v7x5_user_geo10->cd(ihist+1);
        h1_v7x5_user_data10[ihist] = new TH1F(Form("h1_v7x5_user_data10_%i", ihist), Form("V7X5 Data (Geo 10, Channel %i)", ihist), 4000, 0, 200000);
        h1_v7x5_user_data10[ihist]->Draw();
    }
    c_v7x5_user_geo10->cd(0);
    dir_raw_v7x5_user->Append(c_v7x5_user_geo10);

    h2_v7x5_user_data10_vs_chan = new TH2F("h2_v7x5_user_data10_vs_chan", "V7X5 Data (Geo 10) vs Channel", 32, 0, 32, 4000, 0, 200000);

    // Geo = 12
    c_v7x5_user_geo12 = new TCanvas("c_v7x5_user_geo12", "Raw V7X5 Geo 12 (User Crate) spectra", 650, 350);
    c_v7x5_user_geo12->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v7x5_user_geo12->cd(ihist+1);
        h1_v7x5_user_data12[ihist] = new TH1F(Form("h1_v7x5_user_data12_%i", ihist), Form("V7X5 Data (Geo 12, Channel %i)", ihist), 4000, 0, 200000);
        h1_v7x5_user_data12[ihist]->Draw();
    }
    c_v7x5_user_geo12->cd(0);
    dir_raw_v7x5_user->Append(c_v7x5_user_geo12);

    h2_v7x5_user_data12_vs_chan = new TH2F("h2_v7x5_user_data12_vs_chan", "V7X5 Data (Geo 12) vs Channel", 32, 0, 32, 4000, 0, 200000);
    // ----------------------- //

    dir_frs->cd();

    return kSUCCESS;

}


// reset histos
// snapshot histos


void FrsRawSpectra::Exec(Option_t* option)
{
    // Main
        
    for (auto const & v792item : *v792arrayMain)
    {
        uint32_t data = v792item.Get_v792_data();
        uint32_t channel = v792item.Get_channel();

        h1_v792_main_data[channel]->Fill(data);
        h2_v792_main_data_vs_chan->Fill(channel, data);
    }

    int v1290_mult[32] = {0};
    for (auto const & v1290item : *v1290arrayMain)
    {
        uint32_t channel = v1290item.Get_channel();
        uint32_t data = v1290item.Get_v1290_data();
        uint32_t lot = v1290item.Get_leadOrTrail();

        if (lot == 0) h1_v1290_main_leads[channel]->Fill(data);
        h2_v1290_main_data_vs_chan->Fill(channel, data);
        v1290_mult[channel]++;
    }
    for (int i = 0; i < 32; i++) h1_v1290_main_mult[i]->Fill(v1290_mult[i]);

    // TPC
    for (auto const & v7x5item : *v7x5arrayTPC)
    {
        uint32_t geo = v7x5item.Get_geo();
        uint32_t data = v7x5item.Get_v7x5_data();
        uint32_t channel = v7x5item.Get_channel();
        if (geo == 12)
        {
            h1_v7x5_tpc_data12[channel]->Fill(data);
            h2_v7x5_tpc_data12_vs_chan->Fill(channel, data);
        }
        else if (geo == 8)
        {
            h1_v7x5_tpc_data8[channel]->Fill(data);
            h2_v7x5_tpc_data8_vs_chan->Fill(channel, data);
        }
    }
    
    int v1190count = 0;
    for (auto const & v1190item : *v1190arrayTPC)
    {
        uint32_t channel = v1190item.Get_channel();
        uint32_t data = v1190item.Get_v1190_data();
        uint32_t lot = v1190item.Get_leadOrTrail();

        h1_v1190_tpc_data[channel]->Fill(data);
        h2_v1190_tpc_data_vs_chan->Fill(channel, data);
        if (v1190count == 0) h2_v1190_tpc_data_vs_chan_1st_hit->Fill(channel, data);
        v1190count++;
    }

    // User
    for (auto const & v7x5item : *v7x5arrayUser)
    {
        uint32_t geo = v7x5item.Get_geo();
        uint32_t data = v7x5item.Get_v7x5_data();
        uint32_t channel = v7x5item.Get_channel();

        if (geo == 12)
        {
            h1_v7x5_user_data12[channel]->Fill(data);
            h2_v7x5_user_data12_vs_chan->Fill(channel, data);
        }
        else if (geo == 10)
        {
            h1_v7x5_user_data10[channel]->Fill(data);
            h2_v7x5_user_data10_vs_chan->Fill(channel, data);
        }
    }

}

void FrsRawSpectra::FinishEvent()
{

}


void FrsRawSpectra::FinishTask()
{

}

ClassImp(FrsRawSpectra)
