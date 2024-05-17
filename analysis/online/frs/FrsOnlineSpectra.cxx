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
#include "TFile.h"
#include "TColor.h"
#include "TStyle.h"

FrsOnlineSpectra::FrsOnlineSpectra(): FrsOnlineSpectra("FrsOnlineSpectra")
{
    
}

FrsOnlineSpectra::FrsOnlineSpectra(std::vector<FrsGate*> fg)
    : FairTask()
    , hitArray(nullptr)
    , fNEvents(0)
    , header(nullptr)
    , multihitArray(nullptr) //EG
{   
    //Ana = AnalysisTools::GetInstance();
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
    FrsGates = fg;
}

FrsOnlineSpectra::FrsOnlineSpectra(const TString& name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , hitArray(nullptr)
    , fNEvents(0)
    , header(nullptr)
    , multihitArray(nullptr) //EG
{
    frs_config = TFrsConfiguration::GetInstance();
}

FrsOnlineSpectra::~FrsOnlineSpectra()
{
    c4LOG(info, "");
    if (hitArray) delete hitArray;
    if (multihitArray) delete multihitArray; //EG
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

    hitArray = mgr->InitObjectAs<decltype(hitArray)>("FrsHitData");
    c4LOG_IF(fatal, !hitArray, "Branch FrsHitData not found!");

    multihitArray = mgr->InitObjectAs<decltype(multihitArray)>("FrsMultiHitData");
    c4LOG_IF(fatal, !multihitArray, "Branch FrsHitData not found!");  

    histograms = (TFolder*)mgr->GetObject("Histograms");
    
    TDirectory::TContext ctx(nullptr);

    dir_frs = (TDirectory*)mgr->GetObject("FRS");
    if (dir_frs == nullptr) 
    {
        LOG(info) << "Creating FRS Online Directory";
        dir_frs = new TDirectory("FRS Online", "FRS Online", "", 0);
        dir_travmus = dir_frs->mkdir("Travel MUSIC");
        mgr->Register("FRS", "FRS Online Directory", dir_frs, false); // allow other tasks to find this
        mgr->Register("Travel MUSIC", "Travel MUSIC Directory", dir_travmus, false);
        histograms->Add(dir_frs);
    } else dir_travmus = dir_frs->mkdir("Travel MUSIC");

    dir_tac = dir_frs->mkdir("TAC");
    dir_mhtdc = dir_frs->mkdir("MHTDC");
    dir_travmus_tac = dir_travmus->mkdir("TAC");
    dir_travmus_mhtdc = dir_travmus->mkdir("MHTDC");

    dir_tac_1d = dir_tac->mkdir("1D Spectra");
    dir_tac_2d = dir_tac->mkdir("2D PIDs");
    dir_gated_tac = dir_tac->mkdir("Gated 2D PIDs");
    dir_ZvsZ2 = dir_gated_tac->mkdir("ZvsZ2 Gated");
    dir_ZvsZ2_x2vsAoQ = dir_ZvsZ2->mkdir("x2vsAoQ Gated");
    dir_ZvsZ2_x4vsAoQ = dir_ZvsZ2->mkdir("x4vsAoQ Gated");

    dir_mhtdc_1d = dir_mhtdc->mkdir("1D Spectra");
    dir_mhtdc_2d = dir_mhtdc->mkdir("2D PIDs");
    dir_gated_mhtdc = dir_mhtdc->mkdir("Gated 2D");
    
    dir_scalers = dir_frs->mkdir("Scalers");

    //dir_mhtdc = dir_frs->mkdir("MHTDC");
    
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

    dir_scalers->cd();

    for (int i = 0; i < 66; i++) hScaler_per_s[i] = new TH1D(Form("hScaler_per_s_%s", scaler_name[i]), Form("Scaler %s per 1s ", scaler_name[i]), 1000, 0, 1000);
    for (int i = 0; i < 66; i++) hScaler_per_100ms[i] = new TH1D(Form("hScaler_per_100ms_%s", scaler_name[i]), Form("Scaler %s per 0.1s", scaler_name[i]), 4000, 0, 400);
    for (int i = 0; i < 66; i++) hScaler_per_spill[i] = new TH1D(Form("hScaler_per_spill_%s", scaler_name[i]), Form("Scaler %s per spill ", scaler_name[i]), 1000, 0, 1000);

    dir_tac_2d->cd();
    
    h2_Z_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_AoQ", "Z1 vs. A/Q", 
                    1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                    1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");

    /*
    h2_Z_vs_AoQ = new TH2D("h2_Z_vs_AoQ", "Z1 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_AoQ->GetXaxis()->SetTitle("A/Q");
    h2_Z_vs_AoQ->GetYaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_AoQ->SetOption("COLZ");
    */
    
    h2_Z_vs_AoQ_corr = new TH2D("h2_Z_vs_AoQ_corr", "Z1 vs. A/Q (corr)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_AoQ_corr->GetXaxis()->SetTitle("A/Q");
    h2_Z_vs_AoQ_corr->GetYaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_AoQ_corr->SetOption("COLZ");
    
    h2_Z_vs_Z2 = new TH2D("h2_Z_vs_Z2", "Z1 vs. Z2", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_Z2->GetXaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_Z2->GetYaxis()->SetTitle("Z (MUSIC 2)");
    h2_Z_vs_Z2->SetOption("COLZ");

    h2_Z_vs_AoQ_Zsame = new TH2D("h2_Z_vs_AoQ_Zsame", "Z1 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_AoQ_Zsame->GetXaxis()->SetTitle("A/Q");
    h2_Z_vs_AoQ_Zsame->GetYaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_AoQ_Zsame->SetOption("COLZ");

    h2_x4_vs_AoQ_Zsame = new TH2D("h2_x4_vs_AoQ_Zsame", "x4 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 300, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_x4_vs_AoQ_Zsame->GetXaxis()->SetTitle("A/Q");
    h2_x4_vs_AoQ_Zsame->GetYaxis()->SetTitle("S4 x-position");
    h2_x4_vs_AoQ_Zsame->SetOption("COLZ");

    h2_x2_vs_AoQ_Zsame = new TH2D("h2_x2_vs_AoQ_Zsame", "x2 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 300, frs_config->fMin_x2, frs_config->fMax_x2);
    h2_x2_vs_AoQ_Zsame->GetXaxis()->SetTitle("A/Q");
    h2_x2_vs_AoQ_Zsame->GetYaxis()->SetTitle("S2 x-position");
    h2_x2_vs_AoQ_Zsame->SetOption("COLZ");
   
    h2_x2_vs_AoQ = new TH2D("h2_x2_vs_AoQ", "x2 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2);
    h2_x2_vs_AoQ->GetXaxis()->SetTitle("A/Q");
    h2_x2_vs_AoQ->GetYaxis()->SetTitle("S2 x-position");
    h2_x2_vs_AoQ->SetOption("COLZ");

    h2_x4_vs_AoQ = new TH2D("h2_x4_vs_AoQ", "x4 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_x4_vs_AoQ->GetXaxis()->SetTitle("A/Q");
    h2_x4_vs_AoQ->GetYaxis()->SetTitle("S4 x-position");
    h2_x4_vs_AoQ->SetOption("COLZ");

    h2_dEdegoQ_vs_Z = new TH2D("h2_dEdegoQ_vs_Z", "dE in S2 degrader / Q vs. Z1", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ);
    h2_dEdegoQ_vs_Z->GetXaxis()->SetTitle("dE in S2 degrader / Q");
    h2_dEdegoQ_vs_Z->GetYaxis()->SetTitle("Z (MUSIC 1)");
    h2_dEdegoQ_vs_Z->SetOption("COLZ");

    h2_dEdeg_vs_Z = new TH2D("h2_dEdeg_vs_Z", "dE in S2 degrader vs. Z1", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dE, frs_config->fMax_dE);
    h2_dEdeg_vs_Z->GetXaxis()->SetTitle("dE in S2 degrader");
    h2_dEdeg_vs_Z->GetYaxis()->SetTitle("Z (MUSIC 1)");
    h2_dEdeg_vs_Z->SetOption("COLZ");

    h2_a2_vs_AoQ = new TH2D("h2_a2_vs_AoQ", "A/Q vs. AngleX (S2)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a2, frs_config->fMax_a2);
    h2_a2_vs_AoQ->GetXaxis()->SetTitle("A/Q");
    h2_a2_vs_AoQ->GetYaxis()->SetTitle("Angle (S2)");
    h2_a2_vs_AoQ->SetOption("COLZ");

    h2_a4_vs_AoQ = new TH2D("h2_a4_vs_AoQ", "A/Q vs. AngleX (S4)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a4, frs_config->fMax_a4);
    h2_a4_vs_AoQ->GetXaxis()->SetTitle("A/Q");
    h2_a4_vs_AoQ->GetYaxis()->SetTitle("AngleX (S4)");
    h2_a4_vs_AoQ->SetOption("COLZ");

    h2_Z_vs_dE2 = new TH2D("h2_Z_vs_dE2", "Z1 vs. dE in MUSIC2", 400, frs_config->fMin_Z, frs_config->fMax_Z, 250, frs_config->fMin_dE_Music2, frs_config->fMax_dE_Music2);
    h2_Z_vs_dE2->GetXaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_dE2->GetYaxis()->SetTitle("dE in MUSIC 2");
    h2_Z_vs_dE2->SetOption("COLZ");

    h2_x2_vs_x4 = new TH2D("h2_x2_vs_x4", "x2 vs. x4", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_x2_vs_x4->GetXaxis()->SetTitle("S2 x-position");
    h2_x2_vs_x4->GetYaxis()->SetTitle("S4 x-position");
    h2_x2_vs_x4->SetOption("COLZ");
  
    h2_SC41dE_vs_AoQ = new TH2D("h2_SC41dE_vs_AoQ", "A/Q vs. dE in SC41", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000.);
    h2_SC41dE_vs_AoQ->GetXaxis()->SetTitle("A/Q");
    h2_SC41dE_vs_AoQ->GetYaxis()->SetTitle("dE in SC41");
    h2_SC41dE_vs_AoQ->SetOption("COLZ");

    h2_dE_vs_ToF = new TH2D("h2_dE_vs_ToF", "ToF S2-S4 vs. dE in MUSIC1", 2000, 0., 70000., 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);
    h2_dE_vs_ToF->GetXaxis()->SetTitle("Time of Flight (S2 - S4)");
    h2_dE_vs_ToF->GetYaxis()->SetTitle("dE in MUSIC 1");
    h2_dE_vs_ToF->SetOption("COLZ");

    h2_x2_vs_Z = new TH2D("h2_x2_vs_Z", "x2 vs. Z1", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x2, frs_config->fMax_x2);
    h2_x2_vs_Z->GetXaxis()->SetTitle("Z (MUSIC 1)");
    h2_x2_vs_Z->GetYaxis()->SetTitle("S2 x-position");
    h2_x2_vs_Z->SetOption("COLZ");

    h2_x4_vs_Z = new TH2D("h2_x4_vs_Z", "x4 vs. Z1", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_x4_vs_Z->GetXaxis()->SetTitle("Z (MUSIC 1)");
    h2_x4_vs_Z->GetYaxis()->SetTitle("S4 x-position");
    h2_x4_vs_Z->SetOption("COLZ");

    h2_dE1_vs_x2 = new TH2D("h2_dE1_vs_x2", "x2 vs. dE in MUSIC1", 200, frs_config->fMin_x2, frs_config->fMax_x2, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);
    h2_dE1_vs_x2->GetXaxis()->SetTitle("S2 x-position");
    h2_dE1_vs_x2->GetYaxis()->SetTitle("dE in MUSIC 1");
    h2_dE1_vs_x2->SetOption("COLZ");

    h2_dE1_vs_x4 = new TH2D("h2_dE1_vs_x4", "x4 vs. dE in MUSIC1", 200, frs_config->fMin_x4, frs_config->fMax_x4, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);
    h2_dE1_vs_x4->GetXaxis()->SetTitle("S4 x-position");
    h2_dE1_vs_x4->GetYaxis()->SetTitle("dE in MUSIC 1");
    h2_dE1_vs_x4->SetOption("COLZ");

    h2_x2_vs_a2 = new TH2D("h2_x2_vs_a2", "x2 vs. AngleX (S2)", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_a2, frs_config->fMax_a2);
    h2_x2_vs_a2->GetXaxis()->SetTitle("S2 x-position");
    h2_x2_vs_a2->GetYaxis()->SetTitle("AngleX (S2)");
    h2_x2_vs_a2->SetOption("COLZ");

    h2_y2_vs_b2 = new TH2D("h2_y2_vs_b2", "y2 vs. AngleY (S2)", 200, frs_config->fMin_y2, frs_config->fMax_y2, 200, frs_config->fMin_b2, frs_config->fMax_b2);
    h2_y2_vs_b2->GetXaxis()->SetTitle("S2 y-position");
    h2_y2_vs_b2->GetYaxis()->SetTitle("AngleY (S2)");
    h2_y2_vs_b2->SetOption("COLZ");

    h2_x4_vs_a4 = new TH2D("h2_x4_vs_a4", "x4 vs. AngleX (S4)", 200, frs_config->fMin_x4, frs_config->fMax_x4, 200, frs_config->fMin_a4, frs_config->fMax_a4);
    h2_x4_vs_a4->GetXaxis()->SetTitle("S4 x-position");
    h2_x4_vs_a4->GetYaxis()->SetTitle("AngleX (S4)");
    h2_x4_vs_a4->SetOption("COLZ");

    h2_y4_vs_b4 = new TH2D("h2_y4_vs_b4", "y4 vs. AngleY (S4)", 200, frs_config->fMin_y4, frs_config->fMax_y4, 200, frs_config->fMin_b4, frs_config->fMax_b4);
    h2_y4_vs_b4->GetXaxis()->SetTitle("S4 y-position");
    h2_y4_vs_b4->GetYaxis()->SetTitle("AngleY (S4)");
    h2_y4_vs_b4->SetOption("COLZ");

    h2_Z_vs_Sc21E = new TH2D("h2_Z_vs_Sc21E", "Z1 vs. SQRT(Sc21_L * Sc21_R)", 300, frs_config->fMin_Z, frs_config->fMax_Z, 400, 0., 4000.);
    //h2_Z_vs_Sc21E = new TH2D("h2_Z_vs_Sc21E", "Z1 vs. SQRT(Sc21_L * Sc21_R)", 300, 30, frs_config->fMax_Z, 400, 0., 4000.);
    h2_Z_vs_Sc21E->GetXaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_Sc21E->GetYaxis()->SetTitle("Sc21 E");
    h2_Z_vs_Sc21E->SetOption("COLZ");

    // 1D plots to turn on and off
    if (frs_config->plot_1d)
    {   
        // preset wide ranges to "always" see peak, in case it's wrong
        dir_tac_1d->cd();

        h1_frs_Z = new TH1D("h1_frs_Z", "Z (MUSIC 1)", 500, 10, 100);
        h1_frs_Z->SetFillColor(kPink-3);
        h1_frs_Z2 = new TH1D("h1_frs_Z2", "Z (MUSIC 1)", 500, 10, 100);
        h1_frs_Z2->SetFillColor(kPink-3);
        h1_frs_AoQ = new TH1D("h1_frs_AoQ", "A/Q", 500, 1.0, 4.0);
        h1_frs_AoQ->SetFillColor(kPink-3);
        h1_frs_AoQ_corr = new TH1D("h1_frs_AoQ_corr", "A/Q corr", 500, 1.0, 4.0);
        h1_frs_AoQ_corr->SetFillColor(kPink-3);
        h1_frs_x2 = new TH1D("h1_frs_x2", "X Position at S2", 200, -100, 100);
        h1_frs_x2->SetFillColor(kYellow-7); // experimental
        h1_frs_x2->SetLineColor(kBlack);
        h1_frs_x2->SetLineWidth(1.5);
        h1_frs_x4 = new TH1D("h1_frs_x4", "X Position at S4", 200, -100, 100);
        h1_frs_x4->SetFillColor(kYellow-7); // experimental
        h1_frs_x4->SetLineColor(kBlack);
        h1_frs_x4->SetLineWidth(1.5);
        
    }

    // :::: MHTDC ::: //
    dir_mhtdc_2d->cd();

    h2_Z_vs_AoQ_mhtdc = new TH2D("h2_Z_vs_AoQ_mhtdc", "Z1 vs. A/Q - MHTDC", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_AoQ_mhtdc->GetXaxis()->SetTitle("A/Q");
    h2_Z_vs_AoQ_mhtdc->GetYaxis()->SetTitle("Z (MUSIC 1)");
    h2_Z_vs_AoQ_mhtdc->SetOption("COLZ");


    // ZvsZ2 gates
    if (!FrsGates.empty())
    {
        h2_Z_vs_AoQ_Z1Z2gate.resize(FrsGates.size());
        h2_Z1_vs_Z2_Z1Z2gate.resize(FrsGates.size());
        h2_x2_vs_AoQ_Z1Z2gate.resize(FrsGates.size());
        h2_x4_vs_AoQ_Z1Z2gate.resize(FrsGates.size());
        h2_dEdeg_vs_Z_Z1Z2gate.resize(FrsGates.size());
        h2_dedegoQ_vs_Z_Z1Z2gate.resize(FrsGates.size());
        h1_a2_Z1Z2_gate.resize(FrsGates.size());
        h1_a4_Z1Z2_gate.resize(FrsGates.size());
        h2_x2_vs_AoQ_Z1Z2x2AoQgate.resize(FrsGates.size());
        h2_x4_vs_AoQ_Z1Z2x2AoQgate.resize(FrsGates.size());
        h2_Z_vs_AoQ_Z1Z2x2AoQgate.resize(FrsGates.size());
        h2_dEdeg_vs_Z_Z1Z2x2AoQgate.resize(FrsGates.size());
        h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate.resize(FrsGates.size());
        h1_a2_Z1Z2x2AoQgate.resize(FrsGates.size());
        h1_a4_Z1Z2x2AoQgate.resize(FrsGates.size());
        h2_x2_vs_AoQ_Z1Z2x4AoQgate.resize(FrsGates.size());
        h2_x4_vs_AoQ_Z1Z2x4AoQgate.resize(FrsGates.size());
        h2_Z_vs_AoQ_Z1Z2x4AoQgate.resize(FrsGates.size());
        h2_dEdeg_vs_Z_Z1Z2x4AoQgate.resize(FrsGates.size());
        h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate.resize(FrsGates.size());
        h1_a2_Z1Z2x4AoQgate.resize(FrsGates.size());
        h1_a4_Z1Z2x4AoQgate.resize(FrsGates.size());

        for (int gate = 0; gate < FrsGates.size(); gate++)
        {   
            // CEJ: Prioritising Z1Z2 for now.
            /*
            dir_ZvsAoQ->cd();
            h2_Z_vs_AoQ_ZAoQgate[gate] = new TH2I(Form("h2_Z_vs_AoQ_ZAoQgate%i", gate), Form("Z vs. A/Q - ZAoQ Gate %i", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 750, frs_config->fMin_Z, frs_config->fMax_Z);
            h2_Z_vs_AoQ_ZAoQgate[gate]->GetXaxis()->SetTitle("A/Q");
            h2_Z_vs_AoQ_ZAoQgate[gate]->GetYaxis()->SetTitle("Z (MUSIC 1)");
            h2_Z_vs_AoQ_ZAoQgate[gate]->SetOption("COLZ");

            h2_Z1_vs_Z2_ZAoQgate[gate] = new TH2I(Form("h2_Z1_vs_Z2_ZAoQgate%i", gate), Form("Z1 vs. Z2 - ZAoQ Gate %i", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_Z, frs_config->fMax_Z);
            h2_Z1_vs_Z2_ZAoQgate[gate]->GetXaxis()->SetTitle("Z (MUSIC 1)");
            h2_Z1_vs_Z2_ZAoQgate[gate]->GetYaxis()->SetTitle("Z (MUSIC 2)");
            h2_Z1_vs_Z2_ZAoQgate[gate]->SetOption("COLZ");

            h2_x2_vs_AoQ_ZAoQgate[gate] = new TH2I(Form("h2_x2_vs_AoQ_ZAoQgate%i", gate), Form("x2 vs. A/Q - ZAoQ Gate %i", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2);
            h2_x2_vs_AoQ_ZAoQgate[gate]->GetXaxis()->SetTitle("A/Q");
            h2_x2_vs_AoQ_ZAoQgate[gate]->GetYaxis()->SetTitle("S2 x-position)");
            h2_x2_vs_AoQ_ZAoQgate[gate]->SetOption("COLZ");

            h2_x4_vs_AoQ_ZAoQgate[gate] = new TH2I(Form("h2_x4_vs_AoQ_ZAoQgate%i", gate), Form("x4 vs. A/Q - ZAoQ Gate %i", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4);
            h2_x4_vs_AoQ_ZAoQgate[gate]->GetXaxis()->SetTitle("A/Q");
            h2_x4_vs_AoQ_ZAoQgate[gate]->GetYaxis()->SetTitle("S4 x-position)");
            h2_x4_vs_AoQ_ZAoQgate[gate]->SetOption("COLZ");

            h2_dEdeg_vs_Z_ZAoQgate[gate] = new TH2I(Form("h2_dEdeg_vs_Z_ZAoQgate%i", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate %i", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dE, frs_config->fMax_dE);
            h2_dEdeg_vs_Z_ZAoQgate[gate]->GetXaxis()->SetTitle("Z (MUSIC 1)");
            h2_dEdeg_vs_Z_ZAoQgate[gate]->GetYaxis()->SetTitle("dE in S2 degrader");
            h2_dEdeg_vs_Z_ZAoQgate[gate]->SetOption("COLZ");

            h2_dedegoQ_vs_Z_ZAoQgate[gate] = new TH2I(Form("h2_dedegoQ_vs_Z_ZAoQgate%i", gate), Form("Z1 vs. dE in S2 degrader / Q - ZAoQ Gate %i", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ);
            h2_dedegoQ_vs_Z_ZAoQgate[gate]->GetXaxis()->SetTitle("Z (MUSIC 1)");
            h2_dedegoQ_vs_Z_ZAoQgate[gate]->GetYaxis()->SetTitle("dE in S2 degrader / Q");
            h2_dedegoQ_vs_Z_ZAoQgate[gate]->SetOption("COLZ");

            h1_a2_ZAoQ_gate[gate] = new TH1I(Form("h1_a2_ZAoQ_gate%i", gate), Form("Angle S2 [mrad] - ZAoQ Gate %i", gate), 100, -1000, 1000);
            h1_a2_ZAoQ_gate[gate]->GetXaxis()->SetTitle("AngleX (S2)");

            h1_a4_ZAoQ_gate[gate] = new TH1I(Form("h1_a4_ZAoQ_gate%i", gate), Form("Angle S4 [mrad] - ZAoQ Gate %i", gate), 100, -1000, 1000);
            h1_a4_ZAoQ_gate[gate]->GetXaxis()->SetTitle("AngleX (S4)");
            */

            dir_ZvsZ2->cd();
            h2_Z_vs_AoQ_Z1Z2gate[gate] = new TH2I(Form("h2_Z_vs_AoQ_ZAoQgate%s", FrsGates[gate]->GetName().c_str()), Form("Z vs. A/Q - ZAoQ Gate %i", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 750, frs_config->fMin_Z, frs_config->fMax_Z);
            h2_Z_vs_AoQ_Z1Z2gate[gate]->GetXaxis()->SetTitle("A/Q");
            h2_Z_vs_AoQ_Z1Z2gate[gate]->GetYaxis()->SetTitle("Z (MUSIC 1)");
            h2_Z_vs_AoQ_Z1Z2gate[gate]->SetOption("COLZ");

            h2_Z1_vs_Z2_Z1Z2gate[gate] = new TH2I(Form("h2_Z1_vs_Z2_ZAoQgate%i", gate), Form("Z1 vs. Z2 - ZAoQ Gate %i", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_Z, frs_config->fMax_Z);
            h2_Z1_vs_Z2_Z1Z2gate[gate]->GetXaxis()->SetTitle("Z (MUSIC 1)");
            h2_Z1_vs_Z2_Z1Z2gate[gate]->GetYaxis()->SetTitle("Z (MUSIC 2)");
            h2_Z1_vs_Z2_Z1Z2gate[gate]->SetOption("COLZ");

            h2_x2_vs_AoQ_Z1Z2gate[gate] = new TH2I(Form("h2_x2_vs_AoQ_ZAoQgate%i", gate), Form("x2 vs. A/Q - ZAoQ Gate %i", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2);
            h2_x2_vs_AoQ_Z1Z2gate[gate]->GetXaxis()->SetTitle("A/Q");
            h2_x2_vs_AoQ_Z1Z2gate[gate]->GetYaxis()->SetTitle("S2 x-position)");
            h2_x2_vs_AoQ_Z1Z2gate[gate]->SetOption("COLZ");

            h2_x4_vs_AoQ_Z1Z2gate[gate] = new TH2I(Form("h2_x4_vs_AoQ_ZAoQgate%i", gate), Form("x4 vs. A/Q - ZAoQ Gate %i", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4);
            h2_x4_vs_AoQ_Z1Z2gate[gate]->GetXaxis()->SetTitle("A/Q");
            h2_x4_vs_AoQ_Z1Z2gate[gate]->GetYaxis()->SetTitle("S4 x-position)");
            h2_x4_vs_AoQ_Z1Z2gate[gate]->SetOption("COLZ");

            h2_dEdeg_vs_Z_Z1Z2gate[gate] = new TH2I(Form("h2_dEdeg_vs_Z_ZAoQgate%i", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate %i", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dE, frs_config->fMax_dE);
            h2_dEdeg_vs_Z_Z1Z2gate[gate]->GetXaxis()->SetTitle("Z (MUSIC 1)");
            h2_dEdeg_vs_Z_Z1Z2gate[gate]->GetYaxis()->SetTitle("dE in S2 degrader");
            h2_dEdeg_vs_Z_Z1Z2gate[gate]->SetOption("COLZ");

            h2_dedegoQ_vs_Z_Z1Z2gate[gate] = new TH2I(Form("h2_dedegoQ_vs_Z_ZAoQgate%i", gate), Form("Z1 vs. dE in S2 degrader / Q - ZAoQ Gate %i", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ);
            h2_dedegoQ_vs_Z_Z1Z2gate[gate]->GetXaxis()->SetTitle("Z (MUSIC 1)");
            h2_dedegoQ_vs_Z_Z1Z2gate[gate]->GetYaxis()->SetTitle("dE in S2 degrader / Q");
            h2_dedegoQ_vs_Z_Z1Z2gate[gate]->SetOption("COLZ");

            h1_a2_Z1Z2_gate[gate] = new TH1I(Form("h1_a2_ZAoQ_gate%i", gate), Form("Angle S2 [mrad] - ZAoQ Gate %i", gate), 100, -1000, 1000);
            h1_a2_Z1Z2_gate[gate]->GetXaxis()->SetTitle("AngleX (S2)");

            h1_a4_Z1Z2_gate[gate] = new TH1I(Form("h1_a4_ZAoQ_gate%i", gate), Form("Angle S4 [mrad] - ZAoQ Gate %i", gate), 100, -1000, 1000);
            h1_a4_Z1Z2_gate[gate]->GetXaxis()->SetTitle("AngleX (S4)");

            // Second gate - x2 vs AoQ
            dir_ZvsZ2_x2vsAoQ->cd();
            h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate] = new TH2I(Form("h2_x2_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2);                
            h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate] = new TH2I(Form("h2_x4_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4);                
            h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate] = new TH2I(Form("h2_Z_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("Z1 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 750, frs_config->fMin_Z, frs_config->fMax_Z);                
            h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate] = new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2x2AoQgate%d", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dE, frs_config->fMax_dE);                
            h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate] = new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate%d", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ);               
            h1_a2_Z1Z2x2AoQgate[gate] = new TH1I(Form("h1_a2_Z1Z2x2AoQgate%d", gate), Form("Angle S2 [mrad] - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 100, -1000, 1000);           
            h1_a4_Z1Z2x2AoQgate[gate] = new TH1I(Form("h1_a4_Z1Z2x2AoQgate%d", gate), Form("Angle S4 [mrad] - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 100, -1000, 1000);

            // Second gate - x4 vs AoQ
            dir_ZvsZ2_x4vsAoQ->cd();
            h2_x2_vs_AoQ_Z1Z2x4AoQgate[gate] = new TH2I(Form("h2_x2_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("x2 vs. A/Q - Z1Z2, x4AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2);               
            h2_x4_vs_AoQ_Z1Z2x4AoQgate[gate] = new TH2I(Form("h2_x4_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("x4 vs. A/Q - Z1Z2, x4AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4);                
            h2_Z_vs_AoQ_Z1Z2x4AoQgate[gate] = new TH2I(Form("h2_Z_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("Z1 vs. A/Q - Z1Z2, x4AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 750, frs_config->fMin_Z, frs_config->fMax_Z);                
            h2_dEdeg_vs_Z_Z1Z2x4AoQgate[gate] = new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2x4AoQgate%d", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2, x4AoQ Gate: %d", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dE, frs_config->fMax_dE);                
            h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[gate] = new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate%d", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2, x4AoQ Gate: %d", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ);                
            h1_a2_Z1Z2x4AoQgate[gate] = new TH1I(Form("h1_a2_Z1Z2x4AoQgate%d", gate), Form("Angle S2 [mrad] - Z1Z2, x4AoQ Gate: %d", gate), 100, -1000, 1000);                
            h1_a4_Z1Z2x4AoQgate[gate] = new TH1I(Form("h1_a4_Z1Z2x4AoQgate%d", gate), Form("Angle S4 [mrad] - Z1Z2, x4AoQ Gate: %d", gate), 100, -1000, 1000);
            

            // :::: MHTDC :::::
            //...


        }
    }

    dir_scalers->cd();
    h1_tpat = new TH1I("h1_tpat", "Trigger Pattern", 20, 0, 20);



    // ::::: Travel MUSIC - treated separately until FRS sorts themselves out ::::: 
    dir_travmus->cd();
    h1_wr_frs_travmus = new TH1I("h1_wr_frs_travmus", "White Rabbit dT FRS - Travel MUSIC", 500, -3000, -1000);

    // ::::::: TAC :::::::: //
    dir_travmus_tac->cd();

    c_z_compare = new TCanvas("c_z_compare", "Z from 3 x MUSIC", 650, 350);
    c_z_compare->Divide(1, 3);
    c_z_compare->cd(1);
    h1_travmus_z = new TH1D("h1_travmus_z", "Z (Travel MUSIC)", 750, frs_config->fMin_Z, frs_config->fMax_Z);
    h1_travmus_z->SetFillColor(kPink-3);
    h1_travmus_z->Draw();
    c_z_compare->cd(2);
    h1_z1 = new TH1D("h1_z1", "Z (MUSIC 1)", 750, frs_config->fMin_Z, frs_config->fMax_Z);
    h1_z1->SetFillColor(kAzure+7);
    h1_z1->SetLineColor(kBlack);
    h1_z1->Draw();
    c_z_compare->cd(3);
    h1_z2 = new TH1D("h1_z2", "Z (MUSIC 2)", 750, frs_config->fMin_Z, frs_config->fMax_Z);
    h1_z2->SetFillColor(kAzure+7);
    h1_z2->SetLineColor(kBlack);
    h1_z2->Draw();
    c_z_compare->cd(0);
    dir_travmus_tac->Append(c_z_compare);

    c_dE_compare = new TCanvas("c_dE_compare", "dE from 3 x MUSIC", 650, 350);
    c_dE_compare->Divide(1, 3);
    c_dE_compare->cd(1);
    h1_travmus_dE = new TH1D("h1_travmus_dE", "dE (Travel MUSIC)", 750, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);
    h1_travmus_dE->SetFillColor(kPink-3);
    h1_travmus_dE->Draw();
    c_dE_compare->cd(2);
    h1_z1_dE = new TH1D("h1_z1_dE", "dE (MUSIC 1)", 750, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);
    h1_z1_dE->SetFillColor(kAzure+7);
    h1_z1_dE->SetLineColor(kBlack);
    h1_z1_dE->Draw();
    c_dE_compare->cd(3);
    h1_z2_dE = new TH1D("h1_z2_dE", "dE (MUSIC 2)", 750, frs_config->fMin_dE_Music2, frs_config->fMax_dE_Music2);
    h1_z2_dE->SetFillColor(kAzure+7);
    h1_z2_dE->SetLineColor(kBlack);
    h1_z2_dE->Draw();
    c_dE_compare->cd(0);
    dir_travmus_tac->Append(c_dE_compare);

    // :::: 2D plots ::::::: 
    h2_travmus_z1 = new TH2D("h2_travmus_z1", "Z (Travel MUSIC) vs Z (MUSIC 1)", 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_travmus_z1->GetXaxis()->SetTitle("Z (Travel MUSIC)");
    h2_travmus_z1->GetYaxis()->SetTitle("Z (MUSIC 1)");
    h2_travmus_z1->SetOption("COLZ");

    // ::::: Travel Music MHTDC ::::::: //
    dir_travmus_mhtdc->cd();

    c_z_compare_MHTDC = new TCanvas("c_z_compare_MHTDC", "Z from 3 x MUSIC MHTDC", 650, 350);
    c_z_compare_MHTDC->Divide(1, 3);
    c_z_compare_MHTDC->cd(1);
    h1_travmus_z_MHTDC = new TH1D("h1_travmus_z_MHTDC", "Z (Travel MUSIC) MHTDC ", 750, frs_config->fMin_Z, frs_config->fMax_Z);
    h1_travmus_z_MHTDC->SetFillColor(kPink-3);
    h1_travmus_z_MHTDC->Draw();
    c_z_compare_MHTDC->cd(2);
    h1_z1_MHTDC = new TH1D("h1_z1_MHTDC", "Z (MUSIC 1) MHTDC", 750, frs_config->fMin_Z, frs_config->fMax_Z);
    h1_z1_MHTDC->SetFillColor(kAzure+7);
    h1_z1_MHTDC->SetLineColor(kBlack);
    h1_z1_MHTDC->Draw();
    c_z_compare_MHTDC->cd(3);
    h1_z2_MHTDC = new TH1D("h1_z2_MHTDC", "Z (MUSIC 2) MHTDC", 750, frs_config->fMin_Z, frs_config->fMax_Z);
    h1_z2_MHTDC->SetFillColor(kAzure+7);
    h1_z2_MHTDC->SetLineColor(kBlack);
    h1_z2_MHTDC->Draw();
    c_z_compare_MHTDC->cd(0);
    dir_travmus_mhtdc->Append(c_z_compare_MHTDC);
    // :::::::::::::::::::: //

    // Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_FRS_Histo", Form("/Objects/%s/->Reset_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_FRS_Histo", Form("/Objects/%s/->Snapshot_Histo()", GetName()));


    dir_frs->cd();

    return kSUCCESS;

}

void FrsOnlineSpectra::Reset_Histo()
{
    c4LOG(info,"Resetting FRS Spectra");
    h2_Z_vs_AoQ->Reset();
    h2_Z_vs_AoQ_corr->Reset();
    h2_Z_vs_Z2->Reset();
    h2_Z_vs_AoQ_Zsame->Reset();
    h2_x2_vs_AoQ_Zsame->Reset();
    h2_x4_vs_AoQ_Zsame->Reset();
    h2_x2_vs_AoQ->Reset();
    h2_x4_vs_AoQ->Reset();
    h2_dEdegoQ_vs_Z->Reset();
    h2_dEdeg_vs_Z->Reset();
    h2_a2_vs_AoQ->Reset();
    h2_a4_vs_AoQ->Reset();
    h2_Z_vs_dE2->Reset();
    h2_x2_vs_x4->Reset();
    h2_SC41dE_vs_AoQ->Reset();
    h2_dE_vs_ToF->Reset();
    h2_x2_vs_Z->Reset();
    h2_x4_vs_Z->Reset();
    h2_dE1_vs_x2->Reset();
    h2_dE1_vs_x4->Reset();
    h2_x2_vs_a2->Reset();
    h2_y2_vs_b2->Reset();
    h2_x4_vs_a4->Reset();
    h2_y4_vs_b4->Reset();
    h2_Z_vs_Sc21E->Reset();
    h1_tpat->Reset();
   //h1_frs_wr->Reset();

    if (!FrsGates.empty())
    {
        for (int gate = 0; gate < FrsGates.size(); gate++)
        {
            h2_Z_vs_AoQ_Z1Z2gate[gate]->Reset();
            h2_Z1_vs_Z2_Z1Z2gate[gate]->Reset();
            h2_x2_vs_AoQ_Z1Z2gate[gate]->Reset();
            h2_x4_vs_AoQ_Z1Z2gate[gate]->Reset();
            h2_dEdeg_vs_Z_Z1Z2gate[gate]->Reset();
            h2_dedegoQ_vs_Z_Z1Z2gate[gate]->Reset();
            h1_a2_Z1Z2_gate[gate]->Reset();
            h1_a4_Z1Z2_gate[gate]->Reset();
            h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate]->Reset();
            h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate]->Reset();
            h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate]->Reset();
            h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate]->Reset();
            h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate]->Reset();
            h1_a2_Z1Z2x2AoQgate[gate]->Reset();
            h1_a4_Z1Z2x2AoQgate[gate]->Reset();
            h2_x2_vs_AoQ_Z1Z2x4AoQgate[gate]->Reset();
            h2_x4_vs_AoQ_Z1Z2x4AoQgate[gate]->Reset();
            h2_Z_vs_AoQ_Z1Z2x4AoQgate[gate]->Reset();
            h2_dEdeg_vs_Z_Z1Z2x4AoQgate[gate]->Reset();
            h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[gate]->Reset();
            h1_a2_Z1Z2x4AoQgate[gate]->Reset();
            h1_a4_Z1Z2x4AoQgate[gate]->Reset();
        }
    }
    c4LOG(info,"FRS Spectra Reset");
}

void FrsOnlineSpectra::Snapshot_Histo()
{
    // create folder with data and time
    c4LOG(info,"Taking FRS Spectra Snapshot");
    time_t now = time(0);
    tm *ltm = localtime(&now);
    TString snapshot_dir = Form("FRS_Spectra_%i_%i_%i_%i_%i_%i", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    gSystem->cd(screenshot_path);
    gSystem->mkdir(snapshot_dir);
    gSystem->cd(snapshot_dir);

    // save all histograms
    c_frs_snapshot = new TCanvas("c_frs_snapshot", "FRS Spectra Snapshot", 800, 600);
    h2_Z_vs_AoQ->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_Z_vs_AoQ.png");
    c_frs_snapshot->Clear();
    h2_Z_vs_AoQ_corr->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_Z_vs_AoQ_corr.png");
    c_frs_snapshot->Clear();
    h2_Z_vs_Z2->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_Z_vs_Z2.png");
    c_frs_snapshot->Clear();
    h2_Z_vs_AoQ_Zsame->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_Z_vs_AoQ_Zsame.png");
    c_frs_snapshot->Clear();
    h2_x2_vs_AoQ_Zsame->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_x2_vs_AoQ_Zsame.png");
    c_frs_snapshot->Clear();
    h2_x4_vs_AoQ_Zsame->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_x4_vs_AoQ_Zsame.png");
    c_frs_snapshot->Clear();
    h2_x2_vs_AoQ->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_x2_vs_AoQ.png");
    c_frs_snapshot->Clear();
    h2_x4_vs_AoQ->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_x4_vs_AoQ.png");
    c_frs_snapshot->Clear();
    h2_dEdegoQ_vs_Z->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_dEdegoQ_vs_Z.png");
    c_frs_snapshot->Clear();
    h2_dEdeg_vs_Z->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_dEdeg_vs_Z.png");
    c_frs_snapshot->Clear();
    h2_a2_vs_AoQ->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_a2_vs_AoQ.png");
    c_frs_snapshot->Clear();
    h2_a4_vs_AoQ->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_a4_vs_AoQ.png");
    c_frs_snapshot->Clear();
    h2_Z_vs_dE2->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_Z_vs_dE2.png");
    c_frs_snapshot->Clear();
    h2_x2_vs_x4->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_x2_vs_x4.png");
    c_frs_snapshot->Clear();
    h2_SC41dE_vs_AoQ->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_SC41dE_vs_AoQ.png");
    c_frs_snapshot->Clear();
    h2_dE_vs_ToF->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_dE_vs_ToF.png");
    c_frs_snapshot->Clear();
    h2_x2_vs_Z->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_x2_vs_Z.png");
    c_frs_snapshot->Clear();
    h2_x4_vs_Z->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_x4_vs_Z.png");
    c_frs_snapshot->Clear();
    h2_dE1_vs_x2->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_dE1_vs_x2.png");
    c_frs_snapshot->Clear();
    h2_dE1_vs_x4->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_dE1_vs_x4.png");
    c_frs_snapshot->Clear();
    h2_x2_vs_a2->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_x2_vs_a2.png");
    c_frs_snapshot->Clear();
    h2_y2_vs_b2->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_y2_vs_b2.png");
    c_frs_snapshot->Clear();
    h2_x4_vs_a4->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_x4_vs_a4.png");
    c_frs_snapshot->Clear();
    h2_y4_vs_b4->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_y4_vs_b4.png");
    c_frs_snapshot->Clear();
    h2_Z_vs_Sc21E->Draw("COLZ");
    c_frs_snapshot->SaveAs("h2_Z_vs_Sc21E.png");
    c_frs_snapshot->Clear();

    if(!FrsGates.empty())
    {
        for (int gate = 0; gate < FrsGates.size(); gate++)
        {
            h2_Z_vs_AoQ_Z1Z2gate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_Z_vs_AoQ_Z1Z2gate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_Z1_vs_Z2_Z1Z2gate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_Z1_vs_Z2_Z1Z2gate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_x2_vs_AoQ_Z1Z2gate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_x2_vs_AoQ_Z1Z2gate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_x4_vs_AoQ_Z1Z2gate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_x4_vs_AoQ_Z1Z2gate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_dEdeg_vs_Z_Z1Z2gate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_dEdeg_vs_Z_Z1Z2gate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_dedegoQ_vs_Z_Z1Z2gate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_dedegoQ_vs_Z_Z1Z2gate%i.png", gate));
            c_frs_snapshot->Clear();
            h1_a2_Z1Z2_gate[gate]->Draw();
            c_frs_snapshot->SaveAs(Form("h1_a2_Z1Z2_gate%i.png", gate));
            c_frs_snapshot->Clear();
            h1_a4_Z1Z2_gate[gate]->Draw();
            c_frs_snapshot->SaveAs(Form("h1_a4_Z1Z2_gate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_x2_vs_AoQ_Z1Z2x2AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_x4_vs_AoQ_Z1Z2x2AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_Z_vs_AoQ_Z1Z2x2AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_dEdeg_vs_Z_Z1Z2x2AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h1_a2_Z1Z2x2AoQgate[gate]->Draw();
            c_frs_snapshot->SaveAs(Form("h1_a2_Z1Z2x2AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h1_a4_Z1Z2x2AoQgate[gate]->Draw();
            c_frs_snapshot->SaveAs(Form("h1_a4_Z1Z2x2AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_x2_vs_AoQ_Z1Z2x4AoQgate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_x2_vs_AoQ_Z1Z2x4AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_x4_vs_AoQ_Z1Z2x4AoQgate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_x4_vs_AoQ_Z1Z2x4AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_Z_vs_AoQ_Z1Z2x4AoQgate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_Z_vs_AoQ_Z1Z2x4AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_dEdeg_vs_Z_Z1Z2x4AoQgate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_dEdeg_vs_Z_Z1Z2x4AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[gate]->Draw("COLZ");
            c_frs_snapshot->SaveAs(Form("h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h1_a2_Z1Z2x4AoQgate[gate]->Draw();
            c_frs_snapshot->SaveAs(Form("h1_a2_Z1Z2x4AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h1_a4_Z1Z2x4AoQgate[gate]->Draw();
            c_frs_snapshot->SaveAs(Form("h1_a4_Z1Z2x4AoQgate%i.png", gate));
            c_frs_snapshot->Clear();
            h1_tpat->Draw();
            c_frs_snapshot->SaveAs("h1_tpat.png");
            c_frs_snapshot->Clear();         
        }
    }
    c4LOG(info,"FRS Spectra Snapshot saved in: " << screenshot_path + snapshot_dir);

}

void FrsOnlineSpectra::Exec(Option_t* option)
{

    int64_t trav_mus_wr = 0;
    for (auto const & hitItem : *hitArray)
    {
        h1_tpat->Fill(hitItem.Get_tpat());
        //h1_frs_wr->Fill(hitItem.Get_wr_t());

        /* ---------------------------------------------------------------------------- */
        // PIDs //
        /* ---------------------------------------------------------------------------- */
        if (hitItem.Get_ID_AoQ() > 0 && hitItem.Get_ID_z() > 0) h2_Z_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
        if (hitItem.Get_ID_AoQ_corr() > 0 && hitItem.Get_ID_z() > 0) h2_Z_vs_AoQ_corr->Fill(hitItem.Get_ID_AoQ_corr(), hitItem.Get_ID_z());

        if (hitItem.Get_ID_z() > 0 && hitItem.Get_ID_z2() > 0) h2_Z_vs_Z2->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_z2());
        if (TMath::Abs(hitItem.Get_ID_z() - hitItem.Get_ID_z2()) < 0.4)
        {
            h2_Z_vs_AoQ_Zsame->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
            h2_x4_vs_AoQ_Zsame->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
            h2_x2_vs_AoQ_Zsame->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
        }

        if (hitItem.Get_ID_AoQ() > 0 && hitItem.Get_ID_x2() > -100 && hitItem.Get_ID_x2() < 100) h2_x2_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
        if (hitItem.Get_ID_AoQ() > 0 && hitItem.Get_ID_x4() > -100 && hitItem.Get_ID_x4() < 100) h2_x4_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());

        // Charge states
        if (hitItem.Get_ID_z() > 0 && hitItem.Get_ID_dEdegoQ() != 0) h2_dEdegoQ_vs_Z->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdegoQ());
        if (hitItem.Get_ID_z() > 0 && hitItem.Get_ID_dEdeg() != 0) h2_dEdeg_vs_Z->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdeg());

        // Angles vs AoQ
        if (hitItem.Get_ID_AoQ() != 0 && hitItem.Get_ID_a2() != 0) h2_a2_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_a2());
        if (hitItem.Get_ID_AoQ() != 0 && hitItem.Get_ID_a4() != 0) h2_a4_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_a4());

        // Z vs Energy loss MUSIC 2
        if (hitItem.Get_ID_z() != 0 && hitItem.Get_music_dE(1) != 0) h2_Z_vs_dE2->Fill(hitItem.Get_ID_z(), hitItem.Get_music_dE(1));

        // x2 vs x4
        if (hitItem.Get_ID_x2() != 0 && hitItem.Get_ID_x4() != 0) h2_x2_vs_x4->Fill(hitItem.Get_ID_x2(), hitItem.Get_ID_x4());

        // CEJ: changed from Go4, [5] -> [2]
        if (hitItem.Get_ID_AoQ() != 0 && hitItem.Get_sci_e(2) != 0) h2_SC41dE_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_sci_e(2));

        if (hitItem.Get_sci_tof2() != 0 && hitItem.Get_music_dE(0) != 0) h2_dE_vs_ToF->Fill(hitItem.Get_sci_tof2(), hitItem.Get_music_dE(0));

        if (hitItem.Get_ID_z() != 0 && hitItem.Get_ID_x2() != 0) h2_x2_vs_Z->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_x2());
        if (hitItem.Get_ID_z() != 0 && hitItem.Get_ID_x4() != 0) h2_x4_vs_Z->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_x4());

        if (hitItem.Get_ID_x2() != 0 && hitItem.Get_music_dE(0) != 0) h2_dE1_vs_x2->Fill(hitItem.Get_ID_x2(), hitItem.Get_music_dE(0));
        if (hitItem.Get_ID_x4() != 0 && hitItem.Get_music_dE(0) != 0) h2_dE1_vs_x4->Fill(hitItem.Get_ID_x4(), hitItem.Get_music_dE(0));

        if (hitItem.Get_ID_x2() != 0 && hitItem.Get_ID_a2() != 0) h2_x2_vs_a2->Fill(hitItem.Get_ID_x2(), hitItem.Get_ID_a2());
        if (hitItem.Get_ID_y2() != 0 && hitItem.Get_ID_b2() != 0) h2_y2_vs_b2->Fill(hitItem.Get_ID_y2(), hitItem.Get_ID_b2());
        if (hitItem.Get_ID_x4() != 0 && hitItem.Get_ID_a4() != 0) h2_x4_vs_a4->Fill(hitItem.Get_ID_x4(), hitItem.Get_ID_a4());
        if (hitItem.Get_ID_y4() != 0 && hitItem.Get_ID_b4() != 0) h2_y4_vs_b4->Fill(hitItem.Get_ID_y4(), hitItem.Get_ID_b4());

        // CEJ: changed [2] -> [0]
        if (hitItem.Get_ID_z() != 0 && hitItem.Get_sci_l(0) != 0 && hitItem.Get_sci_r(0) != 0) h2_Z_vs_Sc21E->Fill(hitItem.Get_ID_z(), sqrt(hitItem.Get_sci_l(0) * hitItem.Get_sci_r(0)));

        // 1d plots to switch on and off
        // 1D plots to turn on and off
        if (frs_config->plot_1d)
        {
            h1_frs_Z->Fill(hitItem.Get_ID_z());
            h1_frs_Z2->Fill(hitItem.Get_ID_z2());
            h1_frs_AoQ->Fill(hitItem.Get_ID_AoQ());
            h1_frs_AoQ_corr->Fill(hitItem.Get_ID_AoQ_corr());
            h1_frs_x2->Fill(hitItem.Get_ID_x2());
            h1_frs_x4->Fill(hitItem.Get_ID_x4());
            // more..
        }


        if (!FrsGates.empty())
        {   
            for (int gate = 0; gate < FrsGates.size(); gate++)
            {
                if (FrsGates[gate]->Passed_ZvsZ2(hitItem.Get_ID_z(), hitItem.Get_ID_z2()))
                {
                    h2_Z_vs_AoQ_Z1Z2gate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
                    h2_Z1_vs_Z2_Z1Z2gate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_z2());
                    h2_x2_vs_AoQ_Z1Z2gate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
                    h2_x4_vs_AoQ_Z1Z2gate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
                    h2_dEdeg_vs_Z_Z1Z2gate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdeg());
                    h2_dedegoQ_vs_Z_Z1Z2gate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdegoQ());
                    h1_a2_Z1Z2_gate[gate]->Fill(hitItem.Get_ID_a2());
                    h1_a4_Z1Z2_gate[gate]->Fill(hitItem.Get_ID_a4());

                    if (FrsGates[gate]->Passed_x2vsAoQ(hitItem.Get_ID_x2(), hitItem.Get_ID_AoQ()))
                    {
                        h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
                        h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
                        h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
                        h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdeg());
                        h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdegoQ());
                        h1_a2_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_a2());
                        h1_a4_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_a4());
                    }

                    if (FrsGates[gate]->Passed_x4vsAoQ(hitItem.Get_ID_x4(), hitItem.Get_ID_AoQ()))
                    {
                        h2_x2_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
                        h2_x4_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
                        h2_Z_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
                        h2_dEdeg_vs_Z_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdeg());
                        h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdegoQ());
                        h1_a2_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_a2());
                        h1_a4_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_a4());
                    }
                }
            }
        }

        /* ---------------------------------------------------------------------------- */

        // ::::: TRAVEL MUSIC ::::::

        trav_mus_wr = hitItem.Get_wr_travmus();
        if (trav_mus_wr > 0)
        {
            h1_wr_frs_travmus->Fill((int64_t)hitItem.Get_wr_t() - (int64_t)hitItem.Get_wr_travmus());

            if (hitItem.Get_ID_z_travmus() > 0) h1_travmus_z->Fill(hitItem.Get_ID_z_travmus());
            if (hitItem.Get_ID_z() > 0) h1_z1->Fill(hitItem.Get_ID_z()); // same as elsewhere, purely for comparison
            if (hitItem.Get_ID_z2() > 0) h1_z2->Fill(hitItem.Get_ID_z2()); // same as elsewhere, purely for comparison

            if (hitItem.Get_travmusic_dE() > 0) h1_travmus_dE->Fill(hitItem.Get_travmusic_dE());
            if (hitItem.Get_music_dE(0) > 0) h1_z1_dE->Fill(hitItem.Get_music_dE(0));
            if (hitItem.Get_music_dE(1) > 0) h1_z2_dE->Fill(hitItem.Get_music_dE(1));

            h2_travmus_z1->Fill(hitItem.Get_ID_z_travmus(), hitItem.Get_ID_z());

            //c4LOG(info, "trav_mus_de : " << hitItem.Get_travmusic_dE() << " music 1 en : " << hitItem.Get_music_dE(0) << "music 2 en : " << hitItem.Get_music_dE(1) );
        }
   

        // :::::::::::::::::::::::::


        /* ---------------------------------------------------------------------------- */
        // Scalers
        /* ---------------------------------------------------------------------------- */
        for (int i = 0; i < 32; i++)
        {   
            // are we significantly slower if we have to "get" every time?
            hScaler_per_s[i]->AddBinContent(hitItem.Get_ibin_for_s(), hitItem.Get_increase_sc_temp_main(i));
            hScaler_per_s[i+32]->AddBinContent(hitItem.Get_ibin_for_s(), hitItem.Get_increase_sc_temp_user(i));
            hScaler_per_100ms[i]->AddBinContent(hitItem.Get_ibin_for_100ms(), hitItem.Get_increase_sc_temp_main(i));
            hScaler_per_100ms[i+32]->AddBinContent(hitItem.Get_ibin_for_100ms(), hitItem.Get_increase_sc_temp_user(i));
            hScaler_per_spill[i]->AddBinContent(hitItem.Get_ibin_for_spill(), hitItem.Get_increase_sc_temp_main(i));
            hScaler_per_spill[i+32]->AddBinContent(hitItem.Get_ibin_for_spill(), hitItem.Get_increase_sc_temp_user(i));

        }

        Int_t ratio_product = int(0.95 * hitItem.Get_increase_sc_temp2() + 0.05 * ratio_previous);
        hScaler_per_s[64]->SetBinContent(hitItem.Get_ibin_for_s(), ratio_product);
        hScaler_per_100ms[64]->SetBinContent(hitItem.Get_ibin_for_100ms(), ratio_product);
        hScaler_per_spill[64]->SetBinContent(hitItem.Get_ibin_for_spill(), ratio_product);
        Int_t ratio_product2 = int(0.95 * hitItem.Get_increase_sc_temp3() + 0.05 * ratio_previous2);
        hScaler_per_s[65]->SetBinContent(hitItem.Get_ibin_for_s(), ratio_product2);
        hScaler_per_100ms[65]->SetBinContent(hitItem.Get_ibin_for_100ms(), ratio_product2);
        hScaler_per_spill[65]->SetBinContent(hitItem.Get_ibin_for_spill(), ratio_product2);

        for (int i = 0; i < 32; i++)
        {
            hScaler_per_s[i]->SetBinContent(hitItem.Get_ibin_clean_for_s(), 0);
            hScaler_per_s[i+32]->SetBinContent(hitItem.Get_ibin_clean_for_s(),0);
            hScaler_per_100ms[i]->SetBinContent(hitItem.Get_ibin_clean_for_100ms(), 0);
            hScaler_per_100ms[i+32]->SetBinContent(hitItem.Get_ibin_clean_for_100ms(), 0);
            hScaler_per_spill[i]->SetBinContent(hitItem.Get_ibin_clean_for_spill(), 0);
            hScaler_per_spill[i+32]->SetBinContent(hitItem.Get_ibin_clean_for_spill(), 0);
        }

    }

    //:: EG
    //std::cout << "multhit beginnning" << std::endl;
    for (auto const & multihitItem : *multihitArray)
    {
        if (multihitItem.Get_ID_AoQ_mhtdc() > 0 && multihitItem.Get_ID_z_mhtdc() > 0) h2_Z_vs_AoQ_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), multihitItem.Get_ID_z_mhtdc());

        //:::::::::::z
        h1_z1_MHTDC->Fill(multihitItem.Get_ID_z_mhtdc());
        h1_z2_MHTDC->Fill(multihitItem.Get_ID_z2_mhtdc());

        // :::::: Travel Music ::::::: //
        if (trav_mus_wr > 0)
        {
            if (multihitItem.Get_ID_z_travmus_mhtdc() > 0) 
            {   
                h1_travmus_z_MHTDC->Fill(multihitItem.Get_ID_z_travmus_mhtdc());
            }
        }
    }
    //::

    fNEvents += 1;
}

void FrsOnlineSpectra::FinishEvent()
{

}

void FrsOnlineSpectra::FinishTask()
{   

}

ClassImp(FrsOnlineSpectra)
