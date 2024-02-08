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
#include "../../../config/frs_config.h"

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
    if (!folder_frs_hists)
    {
        folder_frs_hists = new TFolder("FRS", "FRS Histograms");
    }
 
    folder_frs_raw_hists = new TFolder("Raw_Histograms", "Raw_Histograms");
    folder_frs_hists->Add(folder_frs_raw_hists);

    folder_frs_raw_main_hists = new TFolder("Main_Raw_Histograms", "Main_Raw_Histograms");
    folder_frs_raw_tpc_hists = new TFolder("TPC_Raw_Histograms", "TPC_Raw_Histograms");
    folder_frs_raw_user_hists = new TFolder("User_Raw_Histograms", "User_Raw_Histograms");
    folder_frs_raw_vftx_hists = new TFolder("VFTX_Raw_Histograms", "VFTX_Raw_Histograms");
    folder_frs_raw_hists->Add(folder_frs_raw_main_hists);
    folder_frs_raw_hists->Add(folder_frs_raw_tpc_hists);
    folder_frs_raw_hists->Add(folder_frs_raw_user_hists);
    folder_frs_raw_hists->Add(folder_frs_raw_vftx_hists);


    // ---- * Main Crate * ---- //
    folder_raw_v792_main_hists = new TFolder("V792_Histograms", "V792_Histograms");
    folder_raw_v1290_main_hists = new TFolder("V1290_Histograms", "V1290_Histograms");
    folder_frs_raw_main_hists->Add(folder_raw_v792_main_hists);
    folder_frs_raw_main_hists->Add(folder_raw_v1290_main_hists);

    // Scalers? Do we do the "hit" scalers here??

    // Geo = 14
    for (int i = 0; i < 32; i++) h1_v792_main_data[i] = new TH1F(Form("h1_v792_main_data_%i", i), Form("V792 Data - Channel %i", i), 1000, 0, 1000.);
    h2_v792_main_data_vs_chan = new TH2F("h2_v792_main_data_vs_chan", "V792 Data vs Channel", 32, 0, 32, 1000, 0, 1000.);
    for (int i = 0; i < 32; i++) folder_raw_v792_main_hists->Add(h1_v792_main_data[i]);
    folder_raw_v792_main_hists->Add(h2_v792_main_data_vs_chan);

    // Geo = ?? V1290
    for (int i = 0; i < 32; i++) h1_v1290_main_mult[i] = new TH1F(Form("h1_v1290_main_mult_%i", i), Form("V1290 Multiplicity - Channel %i", i), 10, 0, 10);
    for (int i = 0; i < 32; i++) h1_v1290_main_leads[i] = new TH1F(Form("h1_v1290_main_leads_%i", i), Form("V1290 Data (Leads) - Channel %i", i), 4000, 0, 200000);
    h2_v1290_main_data_vs_chan = new TH2F("h2_v1290_main_data_vs_chan", "V1290 Data vs Channel", 32, 0, 32, 4000, 0, 200000);
    for (int i = 0; i < 32; i++) folder_raw_v1290_main_hists->Add(h1_v1290_main_mult[i]);
    for (int i = 0; i < 32; i++) folder_raw_v1290_main_hists->Add(h1_v1290_main_leads[i]);
    folder_raw_v1290_main_hists->Add(h2_v1290_main_data_vs_chan);
    // ----------------------- //

    // ---- * TPC Crate * ---- //
    folder_raw_v7x5_tpc_hists = new TFolder("V7X5_Histograms", "V7X5_Histograms");
    folder_raw_v1190_tpc_hists = new TFolder("V1190_Histograms", "V1190_Histograms");
    folder_frs_raw_tpc_hists->Add(folder_raw_v7x5_tpc_hists);
    folder_frs_raw_tpc_hists->Add(folder_raw_v1190_tpc_hists);

    // Geo = 12
    for (int i = 0; i < 32; i++) h1_v7x5_tpc_data12[i] = new TH1F(Form("h1_v7x5_tpc_data12_%i", i), Form("V7X5 Data (Geo 12, Channel %i", i), 2000, 0., 2000.);
    h2_v7x5_tpc_data12_vs_chan = new TH2F("h2_v7x5_tpc_data12_vs_chan", "V7X5 Data (Geo 12) vs Channel", 32, 0, 32, 2000, 0., 2000.);
    for (int i = 0; i < 32; i++) folder_raw_v7x5_tpc_hists->Add(h1_v7x5_tpc_data12[i]);
    folder_raw_v7x5_tpc_hists->Add(h2_v7x5_tpc_data12_vs_chan);

    // Geo = 13
    for (int i = 0; i < 32; i++) h1_v7x5_tpc_data8[i] = new TH1F(Form("h1_v7x5_tpc_data8_%i", i), Form("V7X5 Data (Geo 8, Channel %i", i), 2000, 0., 2000.);
    h2_v7x5_tpc_data8_vs_chan = new TH2F("h2_v7x5_tpc_data8_vs_chan", "V7X5 Data (Geo 8) vs Channel", 32, 0, 32, 2000, 0, 2000.);
    for (int i = 0; i < 32; i++) folder_raw_v7x5_tpc_hists->Add(h1_v7x5_tpc_data8[i]);
    folder_raw_v7x5_tpc_hists->Add(h2_v7x5_tpc_data8_vs_chan);

    // Geo = ?? V1190 
    for (int i = 0; i < 128; i++) h1_v1190_tpc_data[i] = new TH1F(Form("h1_v1190_tpc_data_%i", i), Form("V1190 Data - Channel %i", i), 4000, 0., 200000.);
    h2_v1190_tpc_data_vs_chan = new TH2F("h2_v1190_tpc_data_vs_chan", "V1190 Data vs Chan", 128, 0, 128, 4000, 0, 200000.);
    h2_v1190_tpc_data_vs_chan_1st_hit = new TH2F("h2_v1190_tpc_data_vs_chan_1st_hit", "V1190 Data vs Chan (1st Hit)", 128, 0, 128, 4000, 0., 200000.);
    for (int i = 0; i < 128; i++) folder_raw_v1190_tpc_hists->Add(h1_v1190_tpc_data[i]);
    folder_raw_v1190_tpc_hists->Add(h2_v1190_tpc_data_vs_chan);
    folder_raw_v1190_tpc_hists->Add(h2_v1190_tpc_data_vs_chan_1st_hit);
    // ----------------------- //

    // ---- * User Crate * ---- //
    folder_raw_v7x5_user_hists = new TFolder("V7X5_Histograms", "V7X5_Histograms");
    folder_frs_raw_user_hists->Add(folder_raw_v7x5_user_hists);
    
    // Do we need to do Scalers here?

    // Geo = 10
    for (int i = 0; i < 32; i++) h1_v7x5_user_data10[i] = new TH1F(Form("h1_v7x5_user_data10_%i", i), Form("V7X5 Data (Geo 10, Channel %i", i), 4000, 0, 200000);
    h2_v7x5_user_data10_vs_chan = new TH2F("h2_v7x5_user_data10_vs_chan", "V7X5 Data (Geo 10) vs Channel", 32, 0, 32, 4000, 0, 200000);
    for (int i = 0; i < 32; i++) folder_raw_v7x5_user_hists->Add(h1_v7x5_user_data10[i]);
    folder_raw_v7x5_user_hists->Add(h2_v7x5_user_data10_vs_chan);

    // Geo = 12
    for (int i = 0; i < 32; i++) h1_v7x5_user_data12[i] = new TH1F(Form("h1_v7x5_user_data12_%i", i), Form("V7X5 Data (Geo 12, Channel %i", i), 4000, 0, 200000);
    h2_v7x5_user_data12_vs_chan = new TH2F("h2_v7x5_user_data12_vs_chan", "V7X5 Data (Geo 12) vs Channel", 32, 0, 32, 4000, 0, 200000);
    for (int i = 0; i < 32; i++) folder_raw_v7x5_user_hists->Add(h1_v7x5_user_data12[i]);
    folder_raw_v7x5_user_hists->Add(h2_v7x5_user_data12_vs_chan);
    // ----------------------- //

    // ---- * VFTX Crate * ---- //
    folder_raw_vftx_vftx_hists = new TFolder("VFTX_Histograms", "VFTX_Histograms");
    folder_frs_raw_vftx_hists->Add(folder_raw_vftx_vftx_hists);

    // Geo = ?? VFTX TDC. Should we used VFTX_N? Only one module..
    for (int i = 0; i < VFTX_MAX_CHN; i++) h1_vftx_vftx_lead_mult[i] = new TH1I(Form("h1_vftx_vftx_lead_%i_mult", i), Form("VFTX Lead Multiplicity - Channel %i", i), VFTX_MAX_HITS, 0, VFTX_MAX_HITS);
    for (int i = 0; i < VFTX_MAX_CHN; i++) h1_vftx_vftx_trail_mult[i] = new TH1I(Form("h1_vftx_vftx_trail_%i_mult", i), Form("VFTX Trail Multiplicity - Channel %i", i), VFTX_MAX_HITS, 0, VFTX_MAX_HITS);
    for (int i = 0; i < VFTX_MAX_CHN; i++) h1_vftx_vftx_lead_cc[i] = new TH1I(Form("h1_vftx_vftx_lead_%i_cc", i), Form("VFTX Clock (Leading) - Channel %i", i), 9000, 0., 9000.);
    for (int i = 0; i < VFTX_MAX_CHN; i++) h1_vftx_vftx_lead_ft[i] = new TH1I(Form("h1_vftx_vftx_lead_%i_ft", i), Form("VFTX FineTime (Leading) - Channel %i", i), 1000, 0., 1000.);
    for (int i = 0; i < VFTX_MAX_CHN; i++) h1_vftx_vftx_lead_time[i] = new TH1I(Form("h1_vftx_vftx_lead_%i_time", i), Form("VFTX Leading Time (ps) - Channel %i", i), 1000, 0., 1000.);
    for (int i = 0; i < VFTX_MAX_CHN; i++) h1_vftx_vftx_trail_cc[i] = new TH1I(Form("h1_vftx_vftx_trail_%i_cc", i), Form("VFTX Clock (Trailing) - Channel %i", i), 9000, 0., 9000.);
    for (int i = 0; i < VFTX_MAX_CHN; i++) h1_vftx_vftx_trail_ft[i] = new TH1I(Form("h1_vftx_vftx_trail_%i_ft", i), Form("VFTX FineTime (Trailing) - Channel %i", i), 1000, 0., 1000.);
    for (int i = 0; i < VFTX_MAX_CHN; i++) h1_vftx_vftx_lead_time_ref_ch0[i] = new TH1I(Form("h1_vftx_vftx_lead_time_%i_ref_ch0", i), Form("VFTX Time Difference (Ref Channel 0) - Channel %i", i), 20000, -10000., 10000.);
    for (int i = 0; i < VFTX_MAX_CHN; i++) h2_vftx_vftx_lead_time_ref_ch0_vs_event[i] = new TH2I(Form("h2_vftx_vftx_lead_time_%i_ref_ch0_vs_event", i), Form("VFTX Time Difference (Ref Channel 0) vs Event - Channel %i", i), 400, 0, 4000000, 2000, -10000., 10000.);
    for (int i = 0; i < VFTX_MAX_CHN; i++) h2_vftx_vftx_lead_time_ref_ch8_vs_event[i] = new TH2I(Form("h2_vftx_vftx_lead_time_%i_ref_ch8_vs_event", i), Form("VFTX Time Difference (Ref Channel 8) vs Event - Channel %i", i), 400, 0, 4000000, 2000, -10000., 10000.);
    h2_vftx_vftx_lead_time_ch0vs4 = new TH2I("h2_vftx_vftx_lead_time_ch0vs4", "VFTX Lead Time Channel 0 vs Channel 4", 1000, 0., 100000., 1000, 0., 100000.);
    for (int i = 0; i < VFTX_MAX_CHN; i++) folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_lead_mult[i]);
    for (int i = 0; i < VFTX_MAX_CHN; i++) folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_trail_mult[i]);
    for (int i = 0; i < VFTX_MAX_CHN; i++) folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_lead_cc[i]);
    for (int i = 0; i < VFTX_MAX_CHN; i++) folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_lead_ft[i]);
    for (int i = 0; i < VFTX_MAX_CHN; i++) folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_lead_time[i]);
    for (int i = 0; i < VFTX_MAX_CHN; i++) folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_trail_cc[i]);
    for (int i = 0; i < VFTX_MAX_CHN; i++) folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_trail_ft[i]);
    for (int i = 0; i < VFTX_MAX_CHN; i++) folder_raw_vftx_vftx_hists->Add(h1_vftx_vftx_lead_time_ref_ch0[i]);
    for (int i = 0; i < VFTX_MAX_CHN; i++) folder_raw_vftx_vftx_hists->Add(h2_vftx_vftx_lead_time_ref_ch0_vs_event[i]);
    for (int i = 0; i < VFTX_MAX_CHN; i++) folder_raw_vftx_vftx_hists->Add(h2_vftx_vftx_lead_time_ref_ch8_vs_event[i]);
    folder_raw_vftx_vftx_hists->Add(h2_vftx_vftx_lead_time_ch0vs4);
    // ----------------------- //

    // unsure where this goes
    /*h1_Trigger = new TH1I();
    h1_pTrigger = new TH1I();
    h1_NbTrig = new TH1I();
    h2_CombiTrig2 = new TH2I();
    h1_Tpat = new TH1F(); // tpat crate? functional?*/

    // do we need more from DESPEC Go4?

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
            //for (int m = 0; m < 2; m++) v7x5_geo[m] = fHitFrsTPCRaw->Get_v7x5_geo()[m];
            std::vector<uint32_t>* v7x5_channels = fHitFrsTPCRaw->Get_v7x5_channel();
            //for (int m = 0; m < 2; m++) v7x5_channels[2] = fHitFrsTPCRaw->Get_v7x5_channel()[m];
            std::vector<uint32_t>* v7x5_data = fHitFrsTPCRaw->Get_v7x5_data();
            //for (int m = 0; m < 2; m++) v7x5_data[2] = fHitFrsTPCRaw->Get_v7x5_data()[m]; 

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


}

void FrsRawSpectra::FinishEvent()
{
    if (fHitFrsMainRaw)
    {
        fHitFrsMainRaw->Clear();
    }
}


void FrsRawSpectra::FinishTask()
{
    if (fHitFrsMainRaw)
    {
        folder_frs_raw_hists->Write();
    }
}

ClassImp(FrsRawSpectra)