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
#include "TDirectory.h"

FrsRawSpectra::FrsRawSpectra()
    :   FrsRawSpectra("FrsRawSpectra", 1)
{
}

FrsRawSpectra::FrsRawSpectra(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   fFrsMainArray(NULL)
    ,   fFrsUserArray(NULL)
    ,   fFrsTPCArray(NULL)
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
}

void FrsRawSpectra::SetParContainers()
{
    // Parameter Containers
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus FrsRawSpectra::Init()
{
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
    
    TDirectory::TContext ctx(nullptr);

    
    folder_frs_hists = (TFolder*)mgr->GetObject("FRS");
    //if (!folder_frs_hists) folder_frs_hists = new TFolder("FRS", "FRS");
    
 
    folder_frs_raw_hists = new TFolder("Raw Histograms", "Raw Histograms");
    folder_frs_hists->Add(folder_frs_raw_hists);
    
    //run->AddObject(folder_frs_raw_hists);

    folder_frs_raw_main_hists = new TFolder("Main Raw_Histograms", "Main Raw Histograms");
    folder_frs_raw_tpc_hists = new TFolder("TPC Raw Histograms", "TPC Raw Histograms");
    folder_frs_raw_user_hists = new TFolder("User Raw Histograms", "User Raw Histograms");
    //folder_frs_raw_vftx_hists = new TFolder("VFTX Raw Histograms", "VFTX_Raw Histograms");
    folder_frs_raw_hists->Add(folder_frs_raw_main_hists);
    folder_frs_raw_hists->Add(folder_frs_raw_tpc_hists);
    folder_frs_raw_hists->Add(folder_frs_raw_user_hists);
    //folder_frs_raw_hists->Add(folder_frs_raw_vftx_hists);


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

}

void FrsRawSpectra::FinishEvent()
{
    if (fFrsMainArray) fFrsMainArray->Clear();
    if (fFrsTPCArray) fFrsTPCArray->Clear();
    if (fFrsUserArray) fFrsUserArray->Clear();
}


void FrsRawSpectra::FinishTask()
{
    // Can add a "WRITE" task if necessary
    //folder_frs_raw_hists->Write();
}

ClassImp(FrsRawSpectra)
