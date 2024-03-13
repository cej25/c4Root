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
#include "FrsVFTXData.h"
#include "EventHeader.h"
#include "c4Logger.h"

// ROOT
#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
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
    ,   fFrsMainArray(NULL)
    ,   fFrsUserArray(NULL)
    ,   fFrsTPCArray(NULL)
    ,   fFrsVFTXArray(NULL)  
    ,   fNEvents(0)
    ,   header(nullptr)  
{
}

FrsRawSpectra::~FrsRawSpectra()
{
    c4LOG(info, "");
    if (fFrsMainArray) delete fFrsMainArray;
    if (fFrsTPCArray) delete fFrsTPCArray;
    if (fFrsUserArray) delete fFrsUserArray;
    if (fFrsVFTXArray) delete fFrsVFTXArray;
}

void FrsRawSpectra::SetParContainers()
{
    // Parameter Containers
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus FrsRawSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fFrsMainArray = (TClonesArray*)mgr->GetObject("FrsMainData");
    c4LOG_IF(fatal, !fFrsMainArray, "Branch FrsMainData not found");
    fFrsUserArray = (TClonesArray*)mgr->GetObject("FrsUserData");
    c4LOG_IF(fatal, !fFrsUserArray, "Branch FrsUserData not found");
    fFrsTPCArray = (TClonesArray*)mgr->GetObject("FrsTPCData");
    c4LOG_IF(fatal, !fFrsTPCArray, "Branch FrsTPCData not found");
    fFrsVFTXArray = (TClonesArray*)mgr->GetObject("FrsVFTXData");
    c4LOG_IF(fatal, !fFrsVFTXArray, "Branch FrsVFTXData not found");

    folder_frs_hists = (TFolder*)mgr->GetObject("FRS");
    if (!folder_frs_hists) folder_frs_hists = new TFolder("FRS", "FRS");
 
    folder_frs_raw_hists = new TFolder("Raw Histograms", "Raw Histograms");
    folder_frs_hists->Add(folder_frs_raw_hists);

    folder_frs_raw_main_hists = new TFolder("Main Raw_Histograms", "Main Raw Histograms");
    folder_frs_raw_tpc_hists = new TFolder("TPC Raw Histograms", "TPC Raw Histograms");
    folder_frs_raw_user_hists = new TFolder("User Raw Histograms", "User Raw Histograms");
    folder_frs_raw_vftx_hists = new TFolder("VFTX Raw Histograms", "VFTX_Raw Histograms");
    folder_frs_raw_hists->Add(folder_frs_raw_main_hists);
    folder_frs_raw_hists->Add(folder_frs_raw_tpc_hists);
    folder_frs_raw_hists->Add(folder_frs_raw_user_hists);
    folder_frs_raw_hists->Add(folder_frs_raw_vftx_hists);


    // ---- * Main Crate * ---- //

    // Scalers in "OnlineSpectra" at the moment

    folder_raw_v792_main_hists = new TFolder("V792 Histograms", "V792 Histograms");
    folder_raw_v1290_main_hists = new TFolder("V1290 Histograms", "V1290 Histograms");
    folder_frs_raw_main_hists->Add(folder_raw_v792_main_hists);
    folder_frs_raw_main_hists->Add(folder_raw_v1290_main_hists);

    // Geo = 14
    c_v792_main = new TCanvas("c_v792_main", "Raw V792 (Main Crate) spectra", 650, 350); //?
    c_v792_main->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v792_main->cd(ihist+1);
        h1_v792_main_data[ihist] = new TH1F(Form("h1_v792_main_data_%i", ihist), Form("V792 Data - Channel %i", ihist), 1000, 0, 1000.);
        h1_v792_main_data[ihist]->Draw();
        folder_raw_v792_main_hists->Add(h1_v792_main_data[ihist]);
    }
    c_v792_main->cd(0);
    folder_raw_v792_main_hists->Add(c_v792_main);

    h2_v792_main_data_vs_chan = new TH2F("h2_v792_main_data_vs_chan", "V792 Data vs Channel", 32, 0, 32, 1000, 0, 1000.);
    folder_raw_v792_main_hists->Add(h2_v792_main_data_vs_chan);


    // Geo = ?? V1290
    c_v1290_main_mult = new TCanvas("c_v1290_main_mult", "V1290 (Main Crate) Multiplicity", 650, 350);
    c_v1290_main_mult->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v1290_main_mult->cd(ihist+1);
        h1_v1290_main_mult[ihist] = new TH1F(Form("h1_v1290_main_mult_%i", ihist), Form("V1290 Multiplicity - Channel %i", ihist), 10, 0, 10);
        h1_v1290_main_mult[ihist]->Draw();
        folder_raw_v1290_main_hists->Add(h1_v1290_main_mult[ihist]);
    }
    c_v1290_main_mult->cd(0);
    folder_raw_v1290_main_hists->Add(c_v1290_main_mult);

    c_v1290_main_leads = new TCanvas("c_v1290_main_leads", "V1290 (Main Crate) Leads", 650, 350);
    c_v1290_main_leads->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v1290_main_leads->cd(ihist+1);
        h1_v1290_main_leads[ihist] = new TH1F(Form("h1_v1290_main_leads_%i", ihist), Form("V1290 Data (Leads) - Channel %i", ihist), 4000, 0, 200000);
        h1_v1290_main_leads[ihist]->Draw();
        folder_raw_v1290_main_hists->Add(h1_v1290_main_leads[ihist]);
    }
    c_v1290_main_leads->cd(0);
    folder_raw_v1290_main_hists->Add(c_v1290_main_leads);

    h2_v1290_main_data_vs_chan = new TH2F("h2_v1290_main_data_vs_chan", "V1290 Data vs Channel", 32, 0, 32, 4000, 0, 200000);
    folder_raw_v1290_main_hists->Add(h2_v1290_main_data_vs_chan);
    // ----------------------- //

    // ---- * TPC Crate * ---- //
    folder_raw_v7x5_tpc_hists = new TFolder("V7X5 Histograms", "V7X5 Histograms");
    folder_raw_v1190_tpc_hists = new TFolder("V1190 Histograms", "V1190 Histograms");
    folder_frs_raw_tpc_hists->Add(folder_raw_v7x5_tpc_hists);
    folder_frs_raw_tpc_hists->Add(folder_raw_v1190_tpc_hists);

    // Geo = 12
    c_v7x5_tpc_geo12 = new TCanvas("c_v7x5_tpc_geo12", "Raw V7X5 - Geo 12 (TPC Crate) spectra", 650, 350);
    c_v7x5_tpc_geo12->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v7x5_tpc_geo12->cd(ihist+1);
        h1_v7x5_tpc_data12[ihist] = new TH1F(Form("h1_v7x5_tpc_data12_%i", ihist), Form("V7X5 Data (Geo 12, Channel %i)", ihist), 2000, 0., 2000.);
        h1_v7x5_tpc_data12[ihist]->Draw();
        folder_raw_v7x5_tpc_hists->Add(h1_v7x5_tpc_data12[ihist]);
    }
    c_v7x5_tpc_geo12->cd(0);
    folder_raw_v7x5_tpc_hists->Add(c_v7x5_tpc_geo12);

    h2_v7x5_tpc_data12_vs_chan = new TH2F("h2_v7x5_tpc_data12_vs_chan", "V7X5 Data (Geo 12) vs Channel", 32, 0, 32, 2000, 0., 2000.);
    folder_raw_v7x5_tpc_hists->Add(h2_v7x5_tpc_data12_vs_chan);

    // Geo = 8
    c_v7x5_tpc_geo8 = new TCanvas("c_v7x5_tpc_geo8", "Raw V7X5 - Geo 8 (TPC Crate) spectra", 650, 350);
    c_v7x5_tpc_geo8->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v7x5_tpc_geo8->cd(ihist+1);
        h1_v7x5_tpc_data8[ihist] = new TH1F(Form("h1_v7x5_tpc_data8_%i", ihist), Form("V7X5 Data (Geo 8, Channel %i)", ihist), 2000, 0., 2000.);
        h1_v7x5_tpc_data8[ihist]->Draw();
        folder_raw_v7x5_tpc_hists->Add(h1_v7x5_tpc_data8[ihist]);
    }
    c_v7x5_tpc_geo8->cd(0);
    folder_raw_v7x5_tpc_hists->Add(c_v7x5_tpc_geo8);

    h2_v7x5_tpc_data8_vs_chan = new TH2F("h2_v7x5_tpc_data8_vs_chan", "V7X5 Data (Geo 8) vs Channel", 32, 0, 32, 2000, 0, 2000.);
    folder_raw_v7x5_tpc_hists->Add(h2_v7x5_tpc_data8_vs_chan);

    // Geo = ?? V1190
    c_v1190_tpc = new TCanvas("c_v1190_tpc", "Raw V1190 (TPC Crate) spectra", 650, 350);
    c_v1190_tpc->Divide(8, 16); // is this sensible lol
    for (int ihist = 0; ihist < 128; ihist++)
    {
        c_v1190_tpc->cd(ihist+1);
        h1_v1190_tpc_data[ihist] = new TH1F(Form("h1_v1190_tpc_data_%i", ihist), Form("V1190 Data - Channel %i", ihist), 4000, 0., 200000.);
        h1_v1190_tpc_data[ihist]->Draw();
        folder_raw_v1190_tpc_hists->Add(h1_v1190_tpc_data[ihist]);
    }
    c_v1190_tpc->cd(0);
    folder_raw_v1190_tpc_hists->Add(c_v1190_tpc);

    h2_v1190_tpc_data_vs_chan = new TH2F("h2_v1190_tpc_data_vs_chan", "V1190 Data vs Chan", 128, 0, 128, 4000, 0, 200000.);
    h2_v1190_tpc_data_vs_chan_1st_hit = new TH2F("h2_v1190_tpc_data_vs_chan_1st_hit", "V1190 Data vs Chan (1st Hit)", 128, 0, 128, 4000, 0., 200000.);
    folder_raw_v1190_tpc_hists->Add(h2_v1190_tpc_data_vs_chan);
    folder_raw_v1190_tpc_hists->Add(h2_v1190_tpc_data_vs_chan_1st_hit);
    // ------------------------ //

    // ---- * User Crate * ---- //
    folder_raw_v7x5_user_hists = new TFolder("V7X5 Histograms", "V7X5 Histograms");
    folder_frs_raw_user_hists->Add(folder_raw_v7x5_user_hists);
    
    // Scalers in "OnlineSpectra" at the moment

    // Geo = 10
    c_v7x5_user_geo10 = new TCanvas("c_v7x5_user_geo10", "Raw V7X5 Geo 10 (User Crate) spectra", 650, 350);
    c_v7x5_user_geo10->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v7x5_user_geo10->cd(ihist+1);
        h1_v7x5_user_data10[ihist] = new TH1F(Form("h1_v7x5_user_data10_%i", ihist), Form("V7X5 Data (Geo 10, Channel %i)", ihist), 4000, 0, 200000);
        h1_v7x5_user_data10[ihist]->Draw();
        folder_raw_v7x5_user_hists->Add(h1_v7x5_user_data10[ihist]);
    }
    c_v7x5_user_geo10->cd(0);
    folder_raw_v7x5_user_hists->Add(c_v7x5_user_geo10);

    h2_v7x5_user_data10_vs_chan = new TH2F("h2_v7x5_user_data10_vs_chan", "V7X5 Data (Geo 10) vs Channel", 32, 0, 32, 4000, 0, 200000);
    folder_raw_v7x5_user_hists->Add(h2_v7x5_user_data10_vs_chan);

    // Geo = 12
    c_v7x5_user_geo12 = new TCanvas("c_v7x5_user_geo12", "Raw V7X5 Geo 12 (User Crate) spectra", 650, 350);
    c_v7x5_user_geo12->Divide(4, 8);
    for (int ihist = 0; ihist < 32; ihist++)
    {
        c_v7x5_user_geo12->cd(ihist+1);
        h1_v7x5_user_data12[ihist] = new TH1F(Form("h1_v7x5_user_data12_%i", ihist), Form("V7X5 Data (Geo 12, Channel %i)", ihist), 4000, 0, 200000);
        h1_v7x5_user_data12[ihist]->Draw();
        folder_raw_v7x5_user_hists->Add(h1_v7x5_user_data12[ihist]);
    }
    c_v7x5_user_geo12->cd(0);
    folder_raw_v7x5_user_hists->Add(c_v7x5_user_geo12);

    h2_v7x5_user_data12_vs_chan = new TH2F("h2_v7x5_user_data12_vs_chan", "V7X5 Data (Geo 12) vs Channel", 32, 0, 32, 4000, 0, 200000);
    folder_raw_v7x5_user_hists->Add(h2_v7x5_user_data12_vs_chan);
    // ----------------------- //

    // ---- * VFTX Crate * ---- //
    folder_raw_vftx_vftx_hists = new TFolder("VFTX Histograms", "VFTX Histograms");
    folder_frs_raw_vftx_hists->Add(folder_raw_vftx_vftx_hists);

    // Geo = ?? VFTX TDC. Should we used VFTX_N? Only one module..
    c_vftx_lead_mult = new TCanvas("c_vftx_lead_mult", "VFTX Lead Multiplciity", 650, 350);
    c_vftx_lead_mult->Divide(4, 4);
    for (int ihist = 0; ihist < VFTX_MAX_CHN; ihist++)
    {
        c_vftx_lead_mult->cd(ihist+1);
        h1_vftx_vftx_lead_mult[ihist] = new TH1I(Form("h1_vftx_vftx_lead_%i_mult", ihist), Form("VFTX Lead Multiplicity - Channel %i", ihist), VFTX_MAX_HITS, 0, VFTX_MAX_HITS);
        h1_vftx_vftx_lead_mult[ihist]->Draw();
        folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_lead_mult[ihist]);
    }
    c_vftx_lead_mult->cd(0);
    folder_raw_vftx_vftx_hists->Add(c_vftx_lead_mult);

    c_vftx_trail_mult = new TCanvas("c_vftx_trail_mult", "VFTX Trail Multiplcity", 650, 350);
    c_vftx_trail_mult->Divide(4, 4);
    for (int ihist = 0; ihist < VFTX_MAX_CHN; ihist++)
    {
        c_vftx_trail_mult->cd(ihist+1);
        h1_vftx_vftx_trail_mult[ihist] = new TH1I(Form("h1_vftx_vftx_trail_%i_mult", ihist), Form("VFTX Trail Multiplicity - Channel %i", ihist), VFTX_MAX_HITS, 0, VFTX_MAX_HITS);
        h1_vftx_vftx_trail_mult[ihist]->Draw();
        folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_trail_mult[ihist]);
    }
    c_vftx_trail_mult->cd(0);
    folder_raw_vftx_vftx_hists->Add(c_vftx_trail_mult);

    c_vftx_lead_cc = new TCanvas("c_vftx_lead_cc", "VFTX Lead Coarse Times", 650, 350);
    c_vftx_lead_cc->Divide(4, 4);
    for (int ihist = 0; ihist < VFTX_MAX_CHN; ihist++)
    {
        c_vftx_lead_cc->cd(ihist+1);
        h1_vftx_vftx_lead_cc[ihist] = new TH1I(Form("h1_vftx_vftx_lead_%i_cc", ihist), Form("VFTX Clock (Leading) - Channel %i", ihist), 9000, 0., 9000.);
        h1_vftx_vftx_lead_cc[ihist]->Draw();
        folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_lead_cc[ihist]);
    }
    c_vftx_lead_cc->cd(0);
    folder_raw_vftx_vftx_hists->Add(c_vftx_lead_cc);

    c_vftx_lead_ft = new TCanvas("c_vftx_lead_ft", "VFTX Lead Fine Times", 650, 350);
    c_vftx_lead_ft->Divide(4, 4);
    for (int ihist = 0; ihist < VFTX_MAX_CHN; ihist++)
    {
        c_vftx_lead_ft->cd(ihist+1);
        h1_vftx_vftx_lead_ft[ihist] = new TH1I(Form("h1_vftx_vftx_lead_%i_ft", ihist), Form("VFTX FineTime (Leading) - Channel %i", ihist), 1000, 0., 1000.);
        h1_vftx_vftx_lead_ft[ihist]->Draw();
        folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_lead_ft[ihist]);
    }
    c_vftx_lead_ft->cd(0);
    folder_raw_vftx_vftx_hists->Add(c_vftx_lead_ft);

    c_vftx_lead_time = new TCanvas("c_vftx_lead_time", "VFTX Lead Times", 650, 350);
    c_vftx_lead_time->Divide(4, 4);
    for (int ihist = 0; ihist < VFTX_MAX_CHN; ihist++)
    {
        c_vftx_lead_time->cd(ihist+1);
        h1_vftx_vftx_lead_time[ihist] = new TH1I(Form("h1_vftx_vftx_lead_%i_time", ihist), Form("VFTX Leading Time (ps) - Channel %i", ihist), 1000, 0., 1000.);
        h1_vftx_vftx_lead_time[ihist]->Draw();
        folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_lead_time[ihist]);
    }
    c_vftx_lead_time->cd(0);
    folder_raw_vftx_vftx_hists->Add(c_vftx_lead_time);

    c_vftx_trail_cc = new TCanvas("c_vftx_trail_cc", "VFTX Trail Coarse Times", 650, 350);
    c_vftx_trail_cc->Divide(4, 4);
    for (int ihist = 0; ihist < VFTX_MAX_CHN; ihist++)
    {
        c_vftx_trail_cc->cd(ihist+1);
        h1_vftx_vftx_trail_cc[ihist] = new TH1I(Form("h1_vftx_vftx_trail_%i_cc", ihist), Form("VFTX Clock (Trailing) - Channel %i", ihist), 9000, 0., 9000.);
        h1_vftx_vftx_trail_cc[ihist]->Draw();
        folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_trail_cc[ihist]);
    }
    c_vftx_trail_cc->cd(0);
    folder_raw_vftx_vftx_hists->Add(c_vftx_trail_cc);

    c_vftx_trail_ft = new TCanvas("c_vftx_trail_ft", "VFTX Trail Fine Times", 650, 350);
    c_vftx_trail_ft->Divide(4, 4);
    for (int ihist = 0; ihist < VFTX_MAX_CHN; ihist++)
    {
        c_vftx_trail_ft->cd(ihist+1);
        h1_vftx_vftx_trail_ft[ihist] = new TH1I(Form("h1_vftx_vftx_trail_%i_ft", ihist), Form("VFTX FineTime (Trailing) - Channel %i", ihist), 1000, 0., 1000.);
        h1_vftx_vftx_trail_ft[ihist]->Draw();
        folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_trail_ft[ihist]);
    }
    c_vftx_trail_ft->cd(0);
    folder_raw_vftx_vftx_hists->Add(c_vftx_trail_ft);

    c_vftx_trail_time = new TCanvas("c_vftx_trail_time", "VFTX Trail Times", 650, 350);
    c_vftx_trail_time->Divide(4, 4);
    for (int ihist = 0; ihist < VFTX_MAX_CHN; ihist++)
    {
        c_vftx_trail_time->cd(ihist+1);
        h1_vftx_vftx_trail_time[ihist] = new TH1I(Form("h1_vftx_vftx_trail_%i_time", ihist), Form("VFTX Trailing Time (ps) - Channel %i", ihist), 1000, 0., 1000.);
        h1_vftx_vftx_trail_time[ihist]->Draw();
        folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_trail_time[ihist]);
    }
    c_vftx_trail_time->cd(0);
    folder_raw_vftx_vftx_hists->Add(c_vftx_trail_time);

    c_vftx_lead_refch0 = new TCanvas("c_vftx_lead_refch0", "VFTX Lead Time - Ref Channel 0", 650, 350);
    c_vftx_lead_refch0->Divide(4, 4);
    for (int ihist = 0; ihist < VFTX_MAX_CHN; ihist++)
    {
        c_vftx_lead_refch0->cd(ihist+1);
        h1_vftx_vftx_lead_time_ref_ch0[ihist] = new TH1I(Form("h1_vftx_vftx_lead_time_%i_ref_ch0", ihist), Form("VFTX Time Difference (Ref Channel 0) - Channel %i", ihist), 20000, -10000., 10000.);
        h1_vftx_vftx_lead_time_ref_ch0[ihist]->Draw();
        folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_lead_time_ref_ch0[ihist]);
    }
    c_vftx_lead_refch0->cd(0);
    folder_raw_vftx_vftx_hists->Add(c_vftx_lead_refch0);

    c_vftx_lead_refch0_vs_event = new TCanvas("c_vftx_lead_refch0_vs_event", "VFTX Lead Time - Reference Channel 0 vs Event", 650, 350);
    c_vftx_lead_refch0_vs_event->Divide(4, 4);
    for (int ihist = 0; ihist < VFTX_MAX_CHN; ihist++)
    {
        c_vftx_lead_refch0_vs_event->cd(ihist+1);
        h2_vftx_vftx_lead_time_ref_ch0_vs_event[ihist] = new TH2I(Form("h2_vftx_vftx_lead_time_%i_ref_ch0_vs_event", ihist), Form("VFTX Time Difference (Ref Channel 0) vs Event - Channel %i", ihist), 400, 0, 4000000, 2000, -10000., 10000.);
        h2_vftx_vftx_lead_time_ref_ch0_vs_event[ihist]->Draw();
        folder_raw_vftx_vftx_hists->Add(h2_vftx_vftx_lead_time_ref_ch0_vs_event[ihist]);
    }
    c_vftx_lead_refch0_vs_event->cd(0);
    folder_raw_vftx_vftx_hists->Add(c_vftx_lead_refch0_vs_event);

    c_vftx_lead_refch8_vs_event = new TCanvas("c_vftx_lead_refch8_vs_event", "VFTX Lead Time - Reference Channel 8 vs Event", 650, 350);
    c_vftx_lead_refch8_vs_event->Divide(4, 4);
    for (int ihist = 0; ihist < VFTX_MAX_CHN; ihist++)
    {
        c_vftx_lead_refch8_vs_event->cd(ihist+1);
        h2_vftx_vftx_lead_time_ref_ch8_vs_event[ihist] = new TH2I(Form("h2_vftx_vftx_lead_time_%i_ref_ch8_vs_event", ihist), Form("VFTX Time Difference (Ref Channel 8) vs Event - Channel %i", ihist), 400, 0, 4000000, 2000, -10000., 10000.);
        h2_vftx_vftx_lead_time_ref_ch8_vs_event[ihist]->Draw();
        folder_raw_vftx_vftx_hists->Add(h2_vftx_vftx_lead_time_ref_ch8_vs_event[ihist]);
    }
    c_vftx_lead_refch8_vs_event->cd(0);
    folder_raw_vftx_vftx_hists->Add(c_vftx_lead_refch8_vs_event);

    h2_vftx_vftx_lead_time_ch0vs4 = new TH2I("h2_vftx_vftx_lead_time_ch0vs4", "VFTX Lead Time Channel 0 vs Channel 4", 1000, 0., 100000., 1000, 0., 100000.);
    folder_raw_vftx_vftx_hists->Add(h2_vftx_vftx_lead_time_ch0vs4);
    // ----------------------- //

    return kSUCCESS;

}



// reset histos


void FrsRawSpectra::Exec(Option_t* option)
{
    /* ---- Main Crate ---- */
    if (fFrsMainArray && fFrsMainArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fFrsMainArray->GetEntriesFast();
        for (int ihit = 0; ihit < nHits; ihit++)
        {
            fHitFrsMainRaw = (FrsMainData*)fFrsMainArray->At(ihit);
            if (!fHitFrsMainRaw) continue;

            // v792
            std::vector<uint32_t> v792_main_channels = fHitFrsMainRaw->Get_V792_Channel();
            std::vector<uint32_t> v792_main_data = fHitFrsMainRaw->Get_V792_Data();
            for (int i = 0; i < v792_main_data.size(); i++)
            {
                h1_v792_main_data[v792_main_channels.at(i)-1]->Fill(v792_main_data.at(i));
                h2_v792_main_data_vs_chan->Fill(v792_main_channels.at(i)-1, v792_main_data.at(i));
            }

            // v1290
            std::vector<uint32_t> v1290_main_channels = fHitFrsMainRaw->Get_V1290_Channel();
            std::vector<uint32_t> v1290_main_data = fHitFrsMainRaw->Get_V1290_Data();
            std::vector<uint32_t> v1290_main_lot = fHitFrsMainRaw->Get_V1290_LoT();

            for (int i = 0; i < v1290_main_data.size(); i++)
            {
                if (v1290_main_lot.at(i) == 0)
                {
                    h1_v1290_main_leads[v1290_main_channels.at(i)-1]->Fill(v1290_main_data.at(i));
                }
                // both leads and trails? or just trails?
                h2_v1290_main_data_vs_chan->Fill(v1290_main_channels.at(i)-1, v1290_main_data.at(i));
                v1290_mult[v1290_main_channels.at(i)-1]++;
            }
            for (int i = 0; i < 32; i++) h1_v1290_main_mult[i]->Fill(v1290_mult[i]);

        } // nhits
    } // main crate

    /* ---- TPC Crate ---- */
    if (fFrsTPCArray && fFrsTPCArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fFrsTPCArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            fHitFrsTPCRaw = (FrsTPCData*)fFrsTPCArray->At(ihit);
            if (!fHitFrsTPCRaw) continue;

            // v7x5
            std::vector<uint32_t>* v7x5_geo = fHitFrsTPCRaw->Get_v7x5_geo();
            std::vector<uint32_t>* v7x5_channels = fHitFrsTPCRaw->Get_v7x5_channel();
            std::vector<uint32_t>* v7x5_data = fHitFrsTPCRaw->Get_v7x5_data();

            for (int m = 0; m < 2; m++)
            {
                for (int i = 0; i < v7x5_data[m].size(); i++)
                {
                    if (v7x5_geo[m].at(i) == 12)
                    {
                        h1_v7x5_tpc_data12[v7x5_channels[m].at(i)]->Fill(v7x5_data[m].at(i));
                        h2_v7x5_tpc_data12_vs_chan->Fill(v7x5_channels[m].at(i), v7x5_data[m].at(i));
                    }
                    else if (v7x5_geo[m].at(i) == 8)
                    {
                        h1_v7x5_tpc_data8[v7x5_channels[m].at(i)]->Fill(v7x5_data[m].at(i));
                        h2_v7x5_tpc_data8_vs_chan->Fill(v7x5_channels[m].at(i), v7x5_data[m].at(i));
                    }

                }
            }

            // v1190
            std::vector<uint32_t> v1190_tpc_channels = fHitFrsTPCRaw->Get_V1190_Channel();
            std::vector<uint32_t> v1190_tpc_data = fHitFrsTPCRaw->Get_V1190_Data();
            std::vector<uint32_t> v1190_tpc_lot = fHitFrsTPCRaw->Get_V1190_LoT();

            for (int i = 0; i < v1190_tpc_data.size(); i++)
            {   
                // check lead vs trail?
                h1_v1190_tpc_data[v1190_tpc_channels.at(i)-1]->Fill(v1190_tpc_data.at(i));
                h2_v1190_tpc_data_vs_chan->Fill(v1190_tpc_channels.at(i)-1, v1190_tpc_data.at(i));
                if (i == 0) h2_v1190_tpc_data_vs_chan_1st_hit->Fill(v1190_tpc_channels.at(i)-1, v1190_tpc_data.at(i));
            }

        } // nhits
    } // tpc crate


    /* ---- User Crate ---- */
    if (fFrsUserArray && fFrsUserArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fFrsUserArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            fHitFrsUserRaw = (FrsUserData*)fFrsUserArray->At(ihit);
            if (!fHitFrsUserRaw) continue;

            // v7x5
            std::vector<uint32_t>* v7x5_geo = fHitFrsUserRaw->Get_v7x5_geo_user();
            std::vector<uint32_t>* v7x5_channels = fHitFrsUserRaw->Get_v7x5_channel_user();
            std::vector<uint32_t>* v7x5_data = fHitFrsUserRaw->Get_v7x5_data_user();

            for (int m = 0; m < 4; m++)
            {
                for (int i = 0; i < v7x5_data[m].size(); i++)
                {
                    if (v7x5_geo[m].at(i) == 12)
                    {
                        h1_v7x5_user_data12[v7x5_channels[m].at(i)]->Fill(v7x5_data[m].at(i));
                        h2_v7x5_user_data12_vs_chan->Fill(v7x5_channels[m].at(i), v7x5_data[m].at(i));
                    }
                    else if (v7x5_geo[m].at(i) == 10)
                    {
                        h1_v7x5_user_data10[v7x5_channels[m].at(i)]->Fill(v7x5_data[m].at(i));
                        h2_v7x5_user_data10_vs_chan->Fill(v7x5_channels[m].at(i), v7x5_data[m].at(i));
                    }

                }
            } // v7x5 modules
        } // nhits
    } // user crate


    /* ---- VFTX Crate ---- */
    if (fFrsVFTXArray && fFrsVFTXArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fFrsVFTXArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            fHitFrsVFTXRaw = (FrsVFTXData*)fFrsVFTXArray->At(ihit);
            if (!fHitFrsVFTXRaw) continue;

            std::vector<uint32_t>* vftx_leading_cc = fHitFrsVFTXRaw->Get_vftx_leading_cc();
            std::vector<uint32_t>* vftx_leading_ft = fHitFrsVFTXRaw->Get_vftx_leading_ft();
            std::vector<uint32_t>* vftx_leading_time = fHitFrsVFTXRaw->Get_vftx_leading_time();
            std::vector<uint32_t>* vftx_trailing_cc = fHitFrsVFTXRaw->Get_vftx_trailing_cc();
            std::vector<uint32_t>* vftx_trailing_ft = fHitFrsVFTXRaw->Get_vftx_trailing_ft();
            std::vector<uint32_t>* vftx_trailing_time = fHitFrsVFTXRaw->Get_vftx_trailing_time();

            for (int i = 0; i < VFTX_MAX_CHN; i++)
            {   
                h1_vftx_vftx_lead_mult[i]->Fill(vftx_leading_time[i].size());
                for (int j = 0; j < vftx_leading_time[i].size(); j++)
                {   
                    h1_vftx_vftx_lead_cc[i]->Fill(vftx_leading_cc[i].at(j));
                    h1_vftx_vftx_lead_ft[i]->Fill(vftx_leading_ft[i].at(j));
                    h1_vftx_vftx_lead_time[i]->Fill(vftx_leading_time[i].at(j));
                    // h1_vftx_vftx_lead_time_ref_ch0[i]->Fill(vftx_leading_time[i].at(j) - vftx_leading_time[0].at(j));
                    // h1_vftx_vftx_lead_time_ref_ch0[i]->Fill(vftx_leading_time[i].at(j) - vftx_leading_time[0].at(j));
                    // h2_vftx_vftx_lead_time_ref_ch0_vs_event[i]->Fill(fNEvents, vftx_leading_time[i].at(j) - vftx_leading_time[0].at(j));
                    // h2_vftx_vftx_lead_time_ref_ch8_vs_event[i]->Fill(fNEvents, vftx_leading_time[i].at(j) - vftx_leading_time[8].at(j));
                }
                h1_vftx_vftx_trail_mult[i]->Fill(vftx_trailing_time[i].size());
                for (int j = 0; j < vftx_trailing_time[i].size(); j++)
                {   
                    h1_vftx_vftx_trail_cc[i]->Fill(vftx_trailing_cc[i].at(j));
                    h1_vftx_vftx_trail_ft[i]->Fill(vftx_trailing_ft[i].at(j));
                    h1_vftx_vftx_trail_time[i]->Fill(vftx_trailing_time[i].at(j));
                }
            }
            // h2_vftx_vftx_lead_time_ch0vs4->Fill();

        } // nHits
    } // VFTX crate


}

void FrsRawSpectra::FinishEvent()
{
    if (fFrsMainArray) fFrsMainArray->Clear();
    if (fFrsTPCArray) fFrsTPCArray->Clear();
    if (fFrsUserArray) fFrsUserArray->Clear();
    if (fFrsVFTXArray) fFrsVFTXArray->Clear();
}


void FrsRawSpectra::FinishTask()
{
    // Can add a "WRITE" task if necessary
    folder_frs_hists->Write();
}

ClassImp(FrsRawSpectra)
