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
    frs_config = TFrsConfiguration::GetInstance();
}

FrsOnlineSpectra::FrsOnlineSpectra(const TString& name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fHitFrsArray(NULL)
    , fNEvents(0)
    , header(nullptr)
{
    frs_config = TFrsConfiguration::GetInstance();
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
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFrsArray = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fHitFrsArray, "Branch FrsHitData not found");
    
    TDirectory::TContext ctx(nullptr);

    // TODO: check if exists, i.e. if task is done out of order (?)
    folder_frs_hists = new TFolder("FRS", "FRS");
    mgr->Register("FRS", "FRS Folder", folder_frs_hists, false); // add it to tree
    run->AddObject(folder_frs_hists); // add it to online server

    folder_pids = new TFolder("PIDs", "PIDs");
    folder_scalers = new TFolder("Scalers", "Scalers");

    folder_frs_hists->Add(folder_pids);
    folder_frs_hists->Add(folder_scalers);

  
    // Scalers // -- TODO: Add this name mapping to TFrsConfig or something of the like.
    for (int i = 0; i < 66; i++) sprintf(scaler_name[i], "scaler_ch%d", i);
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

    for (int i = 0; i < 66; i++) folder_scalers->Add(hScaler_per_s[i]);
    for (int i = 0; i < 66; i++) folder_scalers->Add(hScaler_per_100ms[i]);
    for (int i = 0; i < 66; i++) folder_scalers->Add(hScaler_per_spill[i]);
 
    // PIDs and other nearline-ish stuff for online -- TODO: add method for setting Z, AoQ ranges. x4/etc should always remain the same.
    folder_ZvsAoQ_hists = new TFolder("ZvsAoQ Gated", "ZvsAoQ Gated");
    folder_pids->Add(folder_ZvsAoQ_hists);

    h2_Z_vs_AoQ = new TH2D("h2_Z_vs_AoQ", "Z1 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_AoQ->GetXaxis()->SetTitle("A/Q");
    h2_Z_vs_AoQ->GetYaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_AoQ->SetOption("COLZ");
    folder_pids->Add(h2_Z_vs_AoQ);
    
    h2_Z_vs_AoQ_corr = new TH2D("h2_Z_vs_AoQ_corr", "Z1 vs. A/Q (corr)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_AoQ_corr->GetXaxis()->SetTitle("A/Q");
    h2_Z_vs_AoQ_corr->GetYaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_AoQ_corr->SetOption("COLZ");
    folder_pids->Add(h2_Z_vs_AoQ_corr);
    
    h2_Z_vs_Z2 = new TH2D("h2_Z_vs_Z2", "Z1 vs. Z2", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_Z2->GetXaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_Z2->GetYaxis()->SetTitle("Z (MUSIC 2)");
    h2_Z_vs_Z2->SetOption("COLZ");
    folder_pids->Add(h2_Z_vs_Z2);

    h2_Z_vs_AoQ_Zsame = new TH2D("h2_Z_vs_AoQ_Zsame", "Z1 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_AoQ_Zsame->GetXaxis()->SetTitle("A/Q");
    h2_Z_vs_AoQ_Zsame->GetYaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_AoQ_Zsame->SetOption("COLZ");
    folder_pids->Add(h2_Z_vs_AoQ_Zsame);

    h2_x4_vs_AoQ_Zsame = new TH2D("h2_x4_vs_AoQ_Zsame", "x4 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 300, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_x4_vs_AoQ_Zsame->GetXaxis()->SetTitle("A/Q");
    h2_x4_vs_AoQ_Zsame->GetYaxis()->SetTitle("S4 x-position");
    h2_x4_vs_AoQ_Zsame->SetOption("COLZ");
    folder_pids->Add(h2_x4_vs_AoQ_Zsame);

    h2_x2_vs_AoQ_Zsame = new TH2D("h2_x2_vs_AoQ_Zsame", "x4 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 300, frs_config->fMin_x2, frs_config->fMax_x2);
    h2_x2_vs_AoQ_Zsame->GetXaxis()->SetTitle("A/Q");
    h2_x2_vs_AoQ_Zsame->GetYaxis()->SetTitle("S2 x-position");
    h2_x2_vs_AoQ_Zsame->SetOption("COLZ");
    folder_pids->Add(h2_x2_vs_AoQ_Zsame);
   
    h2_x2_vs_AoQ = new TH2D("h2_x2_vs_AoQ", "x2 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2);
    h2_x2_vs_AoQ->GetXaxis()->SetTitle("A/Q");
    h2_x2_vs_AoQ->GetYaxis()->SetTitle("S2 x-position");
    h2_x2_vs_AoQ->SetOption("COLZ");
    folder_pids->Add(h2_x2_vs_AoQ);

    h2_x4_vs_AoQ = new TH2D("h2_x4_vs_AoQ", "x4 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_x4_vs_AoQ->GetXaxis()->SetTitle("A/Q");
    h2_x4_vs_AoQ->GetYaxis()->SetTitle("S4 x-position");
    h2_x4_vs_AoQ->SetOption("COLZ");
    folder_pids->Add(h2_x4_vs_AoQ);

    h2_dEdegoQ_vs_Z = new TH2D("h2_dEdegoQ_vs_Z", "dE in S2 degrader / Q vs. Z1", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ);
    h2_dEdegoQ_vs_Z->GetXaxis()->SetTitle("dE in S2 degrader / Q");
    h2_dEdegoQ_vs_Z->GetYaxis()->SetTitle("Z (MUSIC 1)");
    h2_dEdegoQ_vs_Z->SetOption("COLZ");
    folder_pids->Add(h2_dEdegoQ_vs_Z);

    h2_dEdeg_vs_Z = new TH2D("h2_dEdeg_vs_Z", "dE in S2 degrader vs. Z1", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dE, frs_config->fMax_dE);
    h2_dEdeg_vs_Z->GetXaxis()->SetTitle("dE in S2 degrader");
    h2_dEdeg_vs_Z->GetYaxis()->SetTitle("Z (MUSIC 1)");
    h2_dEdeg_vs_Z->SetOption("COLZ");
    folder_pids->Add(h2_dEdeg_vs_Z);

    h2_a2_vs_AoQ = new TH2D("h2_a2_vs_AoQ", "A/Q vs. AngleX (S2)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a2, frs_config->fMax_a2);
    h2_a2_vs_AoQ->GetXaxis()->SetTitle("A/Q");
    h2_a2_vs_AoQ->GetYaxis()->SetTitle("Angle (S2)");
    h2_a2_vs_AoQ->SetOption("COLZ");
    folder_pids->Add(h2_a2_vs_AoQ);

    h2_a4_vs_AoQ = new TH2D("h2_a4_vs_AoQ", "A/Q vs. AngleX (S4)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a4, frs_config->fMax_a4);
    h2_a4_vs_AoQ->GetXaxis()->SetTitle("A/Q");
    h2_a4_vs_AoQ->GetYaxis()->SetTitle("AngleX (S4)");
    h2_a4_vs_AoQ->SetOption("COLZ");
    folder_pids->Add(h2_a4_vs_AoQ);

    h2_Z_vs_dE2 = new TH2D("h2_Z_vs_dE2", "Z1 vs. dE in MUSIC2", 400, frs_config->fMin_Z, frs_config->fMax_Z, 250, frs_config->fMin_dE_Music2, frs_config->fMax_dE_Music2);
    h2_Z_vs_dE2->GetXaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_dE2->GetYaxis()->SetTitle("dE in MUSIC 2");
    h2_Z_vs_dE2->SetOption("COLZ");
    folder_pids->Add(h2_Z_vs_dE2);

    h2_x2_vs_x4 = new TH2D("h2_x2_vs_x4", "x2 vs. x4", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_x2_vs_x4->GetXaxis()->SetTitle("S2 x-position");
    h2_x2_vs_x4->GetYaxis()->SetTitle("S4 x-position");
    h2_x2_vs_x4->SetOption("COLZ");
    folder_pids->Add(h2_x2_vs_x4);
  
    h2_SC41dE_vs_AoQ = new TH2D("h2_SC41dE_vs_AoQ", "A/Q vs. dE in SC41", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000.);
    h2_SC41dE_vs_AoQ->GetXaxis()->SetTitle("A/Q");
    h2_SC41dE_vs_AoQ->GetYaxis()->SetTitle("dE in SC41");
    h2_SC41dE_vs_AoQ->SetOption("COLZ");
    folder_pids->Add(h2_SC41dE_vs_AoQ);

    h2_dE_vs_ToF = new TH2D("h2_dE_vs_ToF", "ToF S2-S4 vs. dE in MUSIC1", 2000, 0., 70000., 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);
    h2_dE_vs_ToF->GetXaxis()->SetTitle("Time of Flight (S2 - S4)");
    h2_dE_vs_ToF->GetYaxis()->SetTitle("dE in MUSIC 1");
    h2_dE_vs_ToF->SetOption("COLZ");
    folder_pids->Add(h2_dE_vs_ToF);

    h2_x2_vs_Z = new TH2D("h2_x2_vs_Z", "x2 vs. Z1", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x2, frs_config->fMax_x2);
    h2_x2_vs_Z->GetXaxis()->SetTitle("Z (MUSIC 1)");
    h2_x2_vs_Z->GetYaxis()->SetTitle("S2 x-position");
    h2_x2_vs_Z->SetOption("COLZ");
    folder_pids->Add(h2_x2_vs_Z);

    h2_x4_vs_Z = new TH2D("h2_x4_vs_Z", "x4 vs. Z1", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_x4_vs_Z->GetXaxis()->SetTitle("Z (MUSIC 1)");
    h2_x4_vs_Z->GetYaxis()->SetTitle("S4 x-position");
    h2_x4_vs_Z->SetOption("COLZ");
    folder_pids->Add(h2_x4_vs_Z);

    h2_dE1_vs_x2 = new TH2D("h2_dE1_vs_x2", "x2 vs. dE in MUSIC1", 200, frs_config->fMin_x2, frs_config->fMax_x2, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);
    h2_dE1_vs_x2->GetXaxis()->SetTitle("S2 x-position");
    h2_dE1_vs_x2->GetYaxis()->SetTitle("dE in MUSIC 1");
    h2_dE1_vs_x2->SetOption("COLZ");
    folder_pids->Add(h2_dE1_vs_x2);

    h2_dE1_vs_x4 = new TH2D("h2_dE1_vs_x4", "x4 vs. dE in MUSIC1", 200, frs_config->fMin_x4, frs_config->fMax_x4, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);
    h2_dE1_vs_x4->GetXaxis()->SetTitle("S4 x-position");
    h2_dE1_vs_x4->GetYaxis()->SetTitle("dE in MUSIC 1");
    h2_dE1_vs_x4->SetOption("COLZ");
    folder_pids->Add(h2_dE1_vs_x4);

    h2_x2_vs_a2 = new TH2D("h2_x2_vs_a2", "x2 vs. AngleX (S2)", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_a2, frs_config->fMax_a2);
    h2_x2_vs_a2->GetXaxis()->SetTitle("S2 x-position");
    h2_x2_vs_a2->GetYaxis()->SetTitle("AngleX (S2)");
    h2_x2_vs_a2->SetOption("COLZ");
    folder_pids->Add(h2_x2_vs_a2);

    h2_y2_vs_b2 = new TH2D("h2_y2_vs_b2", "y2 vs. AngleY (S2)", 200, frs_config->fMin_y2, frs_config->fMax_y2, 200, frs_config->fMin_b2, frs_config->fMax_b2);
    h2_y2_vs_b2->GetXaxis()->SetTitle("S2 y-position");
    h2_y2_vs_b2->GetYaxis()->SetTitle("AngleY (S2)");
    h2_y2_vs_b2->SetOption("COLZ");
    folder_pids->Add(h2_y2_vs_b2);

    h2_x4_vs_a4 = new TH2D("h2_x4_vs_a4", "x4 vs. AngleX (S4)", 200, frs_config->fMin_x4, frs_config->fMax_x4, 200, frs_config->fMin_a4, frs_config->fMax_a4);
    h2_x4_vs_a4->GetXaxis()->SetTitle("S4 x-position");
    h2_x4_vs_a4->GetYaxis()->SetTitle("AngleX (S4)");
    h2_x4_vs_a4->SetOption("COLZ");
    folder_pids->Add(h2_x4_vs_a4);

    h2_y4_vs_b4 = new TH2D("h2_y4_vs_b4", "y4 vs. AngleY (S4)", 200, frs_config->fMin_y4, frs_config->fMax_y4, 200, frs_config->fMin_b4, frs_config->fMax_b4);
    h2_y4_vs_b4->GetXaxis()->SetTitle("S4 y-position");
    h2_y4_vs_b4->GetYaxis()->SetTitle("AngleY (S4)");
    h2_y4_vs_b4->SetOption("COLZ");
    folder_pids->Add(h2_y4_vs_b4);

    h2_Z_vs_Sc21E = new TH2D("h2_Z_vs_Sc21E", "Z1 vs. SQRT(Sc21_L * Sc21_R)", 300, frs_config->fMin_Z, frs_config->fMax_Z, 400, 0., 4000.);
    h2_Z_vs_Sc21E->GetXaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_Sc21E->GetYaxis()->SetTitle("Sc21 E");
    h2_Z_vs_Sc21E->SetOption("COLZ");
    folder_pids->Add(h2_Z_vs_Sc21E);
    
    // ZvsAoQ gates
    h2_Z_vs_AoQ_ZAoQgate = new TH2I("h2_Z_vs_AoQ_ZAoQgate", "Z vs. A/Q - ZAoQ Gate", 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 750, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_AoQ_ZAoQgate->GetXaxis()->SetTitle("A/Q");
    h2_Z_vs_AoQ_ZAoQgate->GetYaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_AoQ_ZAoQgate->SetOption("COLZ");
    folder_ZvsAoQ_hists->Add(h2_Z_vs_AoQ_ZAoQgate);

    h2_Z1_vs_Z2_ZAoQgate = new TH2I("h2_Z1_vs_Z2_ZAoQgate", "Z1 vs. Z2 - ZAoQ Gate", 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z1_vs_Z2_ZAoQgate->GetXaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z1_vs_Z2_ZAoQgate->GetYaxis()->SetTitle("Z (MUSIC 2)");
    h2_Z1_vs_Z2_ZAoQgate->SetOption("COLZ");
    folder_ZvsAoQ_hists->Add(h2_Z1_vs_Z2_ZAoQgate);

    h2_x2_vs_AoQ_ZAoQgate = new TH2I("h2_x2_vs_AoQ_ZAoQgate", "x2 vs. A/Q - ZAoQ Gate", 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2);
    h2_x2_vs_AoQ_ZAoQgate->GetXaxis()->SetTitle("A/Q");
    h2_x2_vs_AoQ_ZAoQgate->GetYaxis()->SetTitle("S2 x-position)");
    h2_x2_vs_AoQ_ZAoQgate->SetOption("COLZ");
    folder_ZvsAoQ_hists->Add(h2_x2_vs_AoQ_ZAoQgate);

    h2_x4_vs_AoQ_ZAoQgate = new TH2I("h2_x4_vs_AoQ_ZAoQgate", "x4 vs. A/Q - ZAoQ Gate", 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_x4_vs_AoQ_ZAoQgate->GetXaxis()->SetTitle("A/Q");
    h2_x4_vs_AoQ_ZAoQgate->GetYaxis()->SetTitle("S4 x-position)");
    h2_x4_vs_AoQ_ZAoQgate->SetOption("COLZ");
    folder_ZvsAoQ_hists->Add(h2_x4_vs_AoQ_ZAoQgate);

    h2_dEdeg_vs_Z_ZAoQgate = new TH2I("h2_dEdeg_vs_Z_ZAoQgate", "Z1 vs. dE in S2 degrader - ZAoQ Gate", 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dE, frs_config->fMax_dE);
    h2_dEdeg_vs_Z_ZAoQgate->GetXaxis()->SetTitle("Z (MUSIC 1)");
    h2_dEdeg_vs_Z_ZAoQgate->GetYaxis()->SetTitle("dE in S2 degrader");
    h2_dEdeg_vs_Z_ZAoQgate->SetOption("COLZ");
    folder_ZvsAoQ_hists->Add(h2_dEdeg_vs_Z_ZAoQgate);

    h2_dedegoQ_vs_Z_ZAoQgate = new TH2I("h2_dedegoQ_vs_Z_ZAoQgate", "Z1 vs. dE in S2 degrader / Q - ZAoQ Gate", 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ);
    h2_dedegoQ_vs_Z_ZAoQgate->GetXaxis()->SetTitle("Z (MUSIC 1)");
    h2_dedegoQ_vs_Z_ZAoQgate->GetYaxis()->SetTitle("dE in S2 degrader / Q");
    h2_dedegoQ_vs_Z_ZAoQgate->SetOption("COLZ");
    folder_ZvsAoQ_hists->Add(h2_dedegoQ_vs_Z_ZAoQgate);

    h1_a2_ZAoQ_gate = new TH1I("h1_a2_ZAoQ_gate", "Angle S2 [mrad] - ZAoQ Gate", 100, -1000, 1000);
    h1_a2_ZAoQ_gate->GetXaxis()->SetTitle("AngleX (S2)");
    folder_ZvsAoQ_hists->Add(h1_a2_ZAoQ_gate);

    h1_a4_ZAoQ_gate = new TH1I("h1_a4_ZAoQ_gate", "Angle S4 [mrad] - ZAoQ Gate", 100, -1000, 1000);
    h1_a4_ZAoQ_gate->GetXaxis()->SetTitle("AngleX (S4)");
    folder_ZvsAoQ_hists->Add(h1_a4_ZAoQ_gate);

    h1_tpat = new TH1I("h1_tpat", "Trigger Pattern", 20, 0, 20); // may need to decode tpat?
    folder_scalers->Add(h1_tpat);
    // this we'll comment out because it wasn't in go4, looks useful, but will redefine how it fits in
    //h_frs_beta_sci = new TH1D("h_frs_beta_sci", "beta from SCI TOF", 1000,0,1);
    //frs_spectra_folder_histograms->Add(h_frs_beta_sci);

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
            FrsHit = (FrsHitData*)fHitFrsArray->At(ihit);
            if (!FrsHit) continue;

            /* ---------------------------------------------------------------------------- */
            // PIDs //
            /* ---------------------------------------------------------------------------- */
            if (FrsHit->Get_ID_AoQ() > 0 && FrsHit->Get_ID_z() > 0) h2_Z_vs_AoQ->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
            if (FrsHit->Get_ID_AoQ_corr() > 0 && FrsHit->Get_ID_z() > 0) h2_Z_vs_AoQ_corr->Fill(FrsHit->Get_ID_AoQ_corr(), FrsHit->Get_ID_z());

            if (FrsHit->Get_ID_z() > 0 && FrsHit->Get_ID_z2() > 0) h2_Z_vs_Z2->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
            if (TMath::Abs(FrsHit->Get_ID_z() - FrsHit->Get_ID_z2()) < 0.4)
            {
                h2_Z_vs_AoQ_Zsame->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                h2_x4_vs_AoQ_Zsame->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                h2_x2_vs_AoQ_Zsame->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
            }

            if (FrsHit->Get_ID_AoQ() > 0 && FrsHit->Get_ID_x2() > -100 && FrsHit->Get_ID_x2() < 100) h2_x2_vs_AoQ->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
            if (FrsHit->Get_ID_AoQ() > 0 && FrsHit->Get_ID_x4() > -100 && FrsHit->Get_ID_x4() < 100) h2_x4_vs_AoQ->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());

            // Charge states
            if (FrsHit->Get_ID_z() > 0 && FrsHit->Get_ID_dEdegoQ() != 0) h2_dEdegoQ_vs_Z->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdegoQ());
            if (FrsHit->Get_ID_z() > 0 && FrsHit->Get_ID_dEdeg() != 0) h2_dEdeg_vs_Z->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdeg());

            // Angles vs AoQ
            if (FrsHit->Get_ID_AoQ() != 0 && FrsHit->Get_ID_a2() != 0) h2_a2_vs_AoQ->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_a2());
            if (FrsHit->Get_ID_AoQ() != 0 && FrsHit->Get_ID_a4() != 0) h2_a4_vs_AoQ->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_a4());

            // Z vs Energy loss MUSIC 2
            if (FrsHit->Get_ID_z() != 0 && FrsHit->Get_music_dE(1) != 0) h2_Z_vs_dE2->Fill(FrsHit->Get_ID_z(), FrsHit->Get_music_dE(1));

            // x2 vs x4
            if (FrsHit->Get_ID_x2() != 0 && FrsHit->Get_ID_x4() != 0) h2_x2_vs_x4->Fill(FrsHit->Get_ID_x2(), FrsHit->Get_ID_x4());

            // CEJ: changed from Go4, [5] -> [2]
            if (FrsHit->Get_ID_AoQ() != 0 && FrsHit->Get_sci_e(2) != 0) h2_SC41dE_vs_AoQ->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_sci_e(2));

            if (FrsHit->Get_sci_tof2() != 0 && FrsHit->Get_music_dE(0) != 0) h2_dE_vs_ToF->Fill(FrsHit->Get_sci_tof2(), FrsHit->Get_music_dE(0));

            if (FrsHit->Get_ID_z() != 0 && FrsHit->Get_ID_x2() != 0) h2_x2_vs_Z->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_x2());
            if (FrsHit->Get_ID_z() != 0 && FrsHit->Get_ID_x4() != 0) h2_x4_vs_Z->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_x4());

            if (FrsHit->Get_ID_x2() != 0 && FrsHit->Get_music_dE(0) != 0) h2_dE1_vs_x2->Fill(FrsHit->Get_ID_x2(), FrsHit->Get_music_dE(0));
            if (FrsHit->Get_ID_x4() != 0 && FrsHit->Get_music_dE(0) != 0) h2_dE1_vs_x4->Fill(FrsHit->Get_ID_x4(), FrsHit->Get_music_dE(0));

            if (FrsHit->Get_ID_x2() != 0 && FrsHit->Get_ID_a2() != 0) h2_x2_vs_a2->Fill(FrsHit->Get_ID_x2(), FrsHit->Get_ID_a2());
            if (FrsHit->Get_ID_y2() != 0 && FrsHit->Get_ID_b2() != 0) h2_y2_vs_b2->Fill(FrsHit->Get_ID_y2(), FrsHit->Get_ID_b2());
            if (FrsHit->Get_ID_x4() != 0 && FrsHit->Get_ID_a4() != 0) h2_x4_vs_a4->Fill(FrsHit->Get_ID_x4(), FrsHit->Get_ID_a4());
            if (FrsHit->Get_ID_y4() != 0 && FrsHit->Get_ID_b4() != 0) h2_y4_vs_b4->Fill(FrsHit->Get_ID_y4(), FrsHit->Get_ID_b4());

            // CEJ: changed [2] -> [0]
            if (FrsHit->Get_ID_z() != 0 && FrsHit->Get_sci_l(0) != 0 && FrsHit->Get_sci_r(0) != 0) h2_Z_vs_Sc21E->Fill(FrsHit->Get_ID_z(), sqrt(FrsHit->Get_sci_l(0) * FrsHit->Get_sci_r(0)));

            if (cutID_Z_AoQ != nullptr)
            {   
                if (cutID_Z_AoQ->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z()))
                {
                    h2_Z_vs_AoQ_ZAoQgate->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                    h2_Z1_vs_Z2_ZAoQgate->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
                    h2_x2_vs_AoQ_ZAoQgate->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                    h2_x4_vs_AoQ_ZAoQgate->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                    h2_dEdeg_vs_Z_ZAoQgate->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdeg());
                    h2_dedegoQ_vs_Z_ZAoQgate->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdegoQ());
                    h1_a2_ZAoQ_gate->Fill(FrsHit->Get_ID_a2());
                    h1_a4_ZAoQ_gate->Fill(FrsHit->Get_ID_a4());
                }
            }
            /* ---------------------------------------------------------------------------- */


            /* ---------------------------------------------------------------------------- */
            // Scalers - CEJ: ok yeah sc_long is way easier, ok change
            /* ---------------------------------------------------------------------------- */
            for (int i = 0; i < 32; i++)
            {   
                // are we significantly slower if we have to "get" every time?
                hScaler_per_s[i]->AddBinContent(FrsHit->Get_ibin_for_s(), FrsHit->Get_increase_sc_temp_main()[i]);
                hScaler_per_s[i+32]->AddBinContent(FrsHit->Get_ibin_for_s(), FrsHit->Get_increase_sc_temp_user()[i]);
                hScaler_per_100ms[i]->AddBinContent(FrsHit->Get_ibin_for_100ms(), FrsHit->Get_increase_sc_temp_main()[i]);
                hScaler_per_100ms[i+32]->AddBinContent(FrsHit->Get_ibin_for_100ms(), FrsHit->Get_increase_sc_temp_user()[i]);
                hScaler_per_spill[i]->AddBinContent(FrsHit->Get_ibin_for_spill(), FrsHit->Get_increase_sc_temp_main()[i]);
                hScaler_per_spill[i+32]->AddBinContent(FrsHit->Get_ibin_for_spill(), FrsHit->Get_increase_sc_temp_user()[i]);

            }

            Int_t ratio_product = int(0.95 * FrsHit->Get_increase_sc_temp2() + 0.05 * ratio_previous);
            hScaler_per_s[64]->SetBinContent(FrsHit->Get_ibin_for_s(), ratio_product);
            hScaler_per_100ms[64]->SetBinContent(FrsHit->Get_ibin_for_100ms(), ratio_product);
            hScaler_per_spill[64]->SetBinContent(FrsHit->Get_ibin_for_spill(), ratio_product);
            Int_t ratio_product2 = int(0.95 * FrsHit->Get_increase_sc_temp3() + 0.05 * ratio_previous2);
            hScaler_per_s[65]->SetBinContent(FrsHit->Get_ibin_for_s(), ratio_product2);
            hScaler_per_100ms[65]->SetBinContent(FrsHit->Get_ibin_for_100ms(), ratio_product2);
            hScaler_per_spill[65]->SetBinContent(FrsHit->Get_ibin_for_spill(), ratio_product2);

            for (int i = 0; i < 32; i++)
            {
                hScaler_per_s[i]->SetBinContent(FrsHit->Get_ibin_clean_for_s(), 0);
                hScaler_per_s[i+32]->SetBinContent(FrsHit->Get_ibin_clean_for_s(),0);
                hScaler_per_100ms[i]->SetBinContent(FrsHit->Get_ibin_clean_for_100ms(), 0);
                hScaler_per_100ms[i+32]->SetBinContent(FrsHit->Get_ibin_clean_for_100ms(), 0);
                hScaler_per_spill[i]->SetBinContent(FrsHit->Get_ibin_clean_for_spill(), 0);
                hScaler_per_spill[i+32]->SetBinContent(FrsHit->Get_ibin_clean_for_spill(), 0);
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
