// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsOnlineSpectra.h"
#include "FrsHitData.h"
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
#include "TDirectory.h"

FrsOnlineSpectra::FrsOnlineSpectra()
    : FrsOnlineSpectra("FrsOnlineSpectra", 1)
{
}

FrsOnlineSpectra::FrsOnlineSpectra(const TString& name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fHitFrsArray(NULL)
    , fNEvents(0)
    , fMin_Z(30.)
    , fMax_Z(100.)
    , fMin_AoQ(1.6)
    , fMax_AoQ(4.0)
    , fMin_x4(-100.)
    , fMax_x4(100.0)
    , fMin_Z_gate(30.)
    , fMax_Z_gate(100.)
    , fMin_AoQ_gate(1.6)
    , fMax_AoQ_gate(4.0)
    , header(nullptr)
{
}

FrsOnlineSpectra::~FrsOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitFrsArray) delete fHitFrsArray;
}

// Public Method SetParContainers
void FrsOnlineSpectra::SetParContainers()
{
    // Parameter Containers
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus FrsOnlineSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFrsArray = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fHitFrsArray, "Branch FrsHitData not found");
    
    TDirectory::TContext ctx(nullptr);

    //folder_frs_hists = (TFolder*)mgr->GetObject("FRS");
    folder_frs_hists = new TFolder("FRS", "FRS");
    mgr->Register("FRS", "FRS Folder", folder_frs_hists, false);

    run->AddObject(folder_frs_hists);


    // CEJ: name should be more specfic? we want to break down histograms by type
    // will come back to and re-adjust names later.
    TFolder* frs_spectra_folder_histograms = new TFolder("Basic Histograms", "Basic Histograms");
    TFolder* frs_spectra_folder_scalers = new TFolder("Scalers", "Scalers");

    folder_frs_hists->Add(frs_spectra_folder_histograms);
    folder_frs_hists->Add(frs_spectra_folder_scalers);

    c_frs_z1_vs_AoQ = new TCanvas("h_frs_z1_vs_AoQ","Z1 vs A/Q",600,600);
    h_frs_z1_vs_AoQ = new TH2F("h_frs_z1_vs_AoQ","Z1 vs A/Q",5000,fMin_AoQ,fMax_AoQ,5000,fMin_Z,fMax_Z);
    c_frs_x4_vs_AoQ = new TCanvas("h_frs_x4_vs_AoQ","x4 pos vs A/Q",600,600);
    h_frs_x4_vs_AoQ = new TH2F("h_frs_x4_vs_AoQ","x4 pos vs A/Q",1000,fMin_AoQ,fMax_AoQ,1000,fMin_x4,fMax_x4);
    folder_frs_hists->Add(c_frs_z1_vs_AoQ);
    frs_spectra_folder_histograms->Add(h_frs_z1_vs_AoQ);
    folder_frs_hists->Add(c_frs_x4_vs_AoQ);
    frs_spectra_folder_histograms->Add(h_frs_x4_vs_AoQ);

    h_frs_beta_sci = new TH1D("h_frs_beta_sci", "beta from SCI TOF", 1000,0,1);
    frs_spectra_folder_histograms->Add(h_frs_beta_sci);


    /* ------------------ */
    // Scalers
    // CEJ: (most?) of these scalers have actual names, come back to.
    /* ------------------ */
    for (int i = 0; i < 66; i++) sprintf(scaler_name[i], "scaler_ch%d", i); // default name
    sprintf(scaler_name[0], "IC01curr-new");
    sprintf(scaler_name[1], "SEETRAM-old");
    sprintf(scaler_name[2], "SEETRAM-new");
    sprintf(scaler_name[3], "IC01curr-old");
    sprintf(scaler_name[4], "IC01 count");
    sprintf(scaler_name[5], "SCI00");
    sprintf(scaler_name[6], "SCI01");
    sprintf(scaler_name[7], "SCI02");
    sprintf(scaler_name[8], "Start Extr");
    sprintf(scaler_name[9], "Stop Extr");
    sprintf(scaler_name[10], "Beam Transformer");

    sprintf(scaler_name[32], "Free Trigger");
    sprintf(scaler_name[33], "Accept Trigger");
    sprintf(scaler_name[34], "Spill Counter");
    sprintf(scaler_name[35], "1 Hz Clock");
    sprintf(scaler_name[36], "10 Hz Clock");
    sprintf(scaler_name[37], "100 kHz veto dead-time");
    sprintf(scaler_name[38], "100 kHz Clock");
    sprintf(scaler_name[39], "1 kHz Clock");

    sprintf(scaler_name[48], "SCI21L");
    sprintf(scaler_name[49], "SCI41L");
    sprintf(scaler_name[50], "SCI42L");
    sprintf(scaler_name[51], "SCI43L");
    sprintf(scaler_name[52], "SCI42R");
    sprintf(scaler_name[53], "SCI21R");
    sprintf(scaler_name[54], "SCI41R");
    sprintf(scaler_name[55], "SCI81L");
    sprintf(scaler_name[56], "SCI43R");
    sprintf(scaler_name[57], "SCI81R");
    sprintf(scaler_name[58], "SCI31L");
    sprintf(scaler_name[59], "SCI31R");
    sprintf(scaler_name[60], "SCI11");
    sprintf(scaler_name[61], "SCI22L");
    sprintf(scaler_name[62], "SCI22R");
    sprintf(scaler_name[63], "SCI51");
    sprintf(scaler_name[64], "Accept-ov-Free Trigger");
    sprintf(scaler_name[65], "veto-dead-time-ov-100kHz");

    for (int i = 0; i < 66; i++) hScaler_per_s[i] = new TH1D(Form("hScaler_per_s_%s", scaler_name[i]), Form("Scaler %s per 1s ", scaler_name[i]), 1000, 0, 1000);
    for (int i = 0; i < 66; i++) hScaler_per_100ms[i] = new TH1D(Form("hScaler_per_100ms_%s", scaler_name[i]), Form("Scaler %s per 0.1s", scaler_name[i]), 4000, 0, 400);
    for (int i = 0; i < 66; i++) hScaler_per_spill[i] = new TH1D(Form("hScaler_per_spill_%s", scaler_name[i]), Form("Scaler %s per spill ", scaler_name[i]), 1000, 0, 1000);

    for (int i = 0; i < 66; i++) frs_spectra_folder_scalers->Add(hScaler_per_s[i]);
    for (int i = 0; i < 66; i++) frs_spectra_folder_scalers->Add(hScaler_per_100ms[i]);
    for (int i = 0; i < 66; i++) frs_spectra_folder_scalers->Add(hScaler_per_spill[i]);
 
    //h1_raw_tpat = new TH1I("h1_raw_tpat", "TPAT", 20, 0, 20);

    // Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_IncomingID_HIST", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;

}

void FrsOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
   // fh1_TdcRaw->Clear();
   // fh1_TdcChan->Clear();
}

void FrsOnlineSpectra::Exec(Option_t* option)
{
    // Fill hit data
    if (fHitFrsArray && fHitFrsArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitFrsArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            fHitFrs = (FrsHitData*)fHitFrsArray->At(ihit);
            if (!fHitFrs)
                continue;

            /* ---------------------------------------------------------------------------- */
            // PIDs //
            /* ---------------------------------------------------------------------------- */
            h_frs_z1_vs_AoQ->Fill(fHitFrs->Get_ID_AoQ_corr(), fHitFrs->Get_ID_z());
            h_frs_x4_vs_AoQ->Fill(fHitFrs->Get_ID_AoQ_corr(),fHitFrs->Get_ID_x4());
            h_frs_beta_sci->Fill(fHitFrs->Get_ID_beta());

            /* ---------------------------------------------------------------------------- */


            /* ---------------------------------------------------------------------------- */
            // Scalers - CEJ: ok yeah sc_long is way easier, ok change]
            // seriously calum go back to this
            /* ---------------------------------------------------------------------------- */
            for (int i = 0; i < 32; i++)
            {   
                // are we significantly slower if we have to "get" every time?
                hScaler_per_s[i]->AddBinContent(fHitFrs->Get_ibin_for_s(), fHitFrs->Get_increase_sc_temp_main()[i]);
                hScaler_per_s[i+32]->AddBinContent(fHitFrs->Get_ibin_for_s(),fHitFrs->Get_increase_sc_temp_user()[i]);
                hScaler_per_100ms[i]->AddBinContent(fHitFrs->Get_ibin_for_100ms(), fHitFrs->Get_increase_sc_temp_main()[i]);
                hScaler_per_100ms[i+32]->AddBinContent(fHitFrs->Get_ibin_for_100ms(),fHitFrs->Get_increase_sc_temp_user()[i]);
                hScaler_per_spill[i]->AddBinContent(fHitFrs->Get_ibin_for_spill(), fHitFrs->Get_increase_sc_temp_main()[i]);
                hScaler_per_spill[i+32]->AddBinContent(fHitFrs->Get_ibin_for_spill(),fHitFrs->Get_increase_sc_temp_user()[i]);

            }

            Int_t ratio_product = int(0.95 * fHitFrs->Get_increase_sc_temp2() + 0.05 * ratio_previous);
            hScaler_per_s[64]->SetBinContent(fHitFrs->Get_ibin_for_s(), ratio_product);
            hScaler_per_100ms[64]->SetBinContent(fHitFrs->Get_ibin_for_100ms(), ratio_product);
            hScaler_per_spill[64]->SetBinContent(fHitFrs->Get_ibin_for_spill(), ratio_product);
            Int_t ratio_product2 = int(0.95 * fHitFrs->Get_increase_sc_temp3() + 0.05 * ratio_previous2);
            hScaler_per_s[65]->SetBinContent(fHitFrs->Get_ibin_for_s(), ratio_product2);
            hScaler_per_100ms[65]->SetBinContent(fHitFrs->Get_ibin_for_100ms(), ratio_product2);
            hScaler_per_spill[65]->SetBinContent(fHitFrs->Get_ibin_for_spill(), ratio_product2);

            for (int i = 0; i < 32; i++)
            {
                hScaler_per_s[i]->SetBinContent(fHitFrs->Get_ibin_clean_for_s(), 0);
                hScaler_per_s[i+32]->SetBinContent(fHitFrs->Get_ibin_clean_for_s(),0);
                hScaler_per_100ms[i]->SetBinContent(fHitFrs->Get_ibin_clean_for_100ms(), 0);
                hScaler_per_100ms[i+32]->SetBinContent(fHitFrs->Get_ibin_clean_for_100ms(), 0);
                hScaler_per_spill[i]->SetBinContent(fHitFrs->Get_ibin_clean_for_spill(), 0);
                hScaler_per_spill[i+32]->SetBinContent(fHitFrs->Get_ibin_clean_for_spill(), 0);
            }

        }
    }

    fNEvents += 1;
}

void FrsOnlineSpectra::FinishEvent()
{
    if (fHitFrsArray)
    {
        fHitFrsArray->Clear();
    }
}

void FrsOnlineSpectra::FinishTask()
{   
    //folder_frs_hists->Write();
}

ClassImp(FrsOnlineSpectra)
