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
    , fNEvents(0)
    , header(nullptr)
    , tpcCalArray(nullptr)
    , hitArray(nullptr)
    , multihitArray(nullptr)
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
    FrsGates = fg;
}

FrsOnlineSpectra::FrsOnlineSpectra(const TString& name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fNEvents(0)
    , header(nullptr)
    , tpcCalArray(nullptr)
    , hitArray(nullptr)
    , multihitArray(nullptr)
{
    frs_config = TFrsConfiguration::GetInstance();
    exp_config = TExperimentConfiguration::GetInstance();
}

FrsOnlineSpectra::~FrsOnlineSpectra()
{
    c4LOG(info, "");
    if (hitArray) delete hitArray;
    if (multihitArray) delete multihitArray;
}

InitStatus FrsOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    tpcCalArray = mgr->InitObjectAs<decltype(tpcCalArray)>("FrsTPCCalData");
    c4LOG_IF(fatal, !tpcCalArray, "Branch FrsTPCCalData not found!");

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
    dir_travmus_tac = dir_travmus->mkdir("TAC"); // travel music is "special" for now..
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
    dir_rates = dir_frs->mkdir("Rate Monitors");
    
    h1_tpat = MakeTH1(dir_scalers, "I", "h1_tpat", "Trigger Pattern", 20, 0, 20, "Trigger Pattern", kRed-3, kBlack);
    for (int i = 0; i < 66; i++) hScaler_per_s[i] = MakeTH1(dir_scalers, "D", Form("hScaler_per_s_%s", frs_config->ScalerName(i).c_str()), Form("Scaler %s per 1s ", frs_config->ScalerName(i).c_str()), 1000, 0., 1000., "Time [s]", kCyan, kViolet);
    for (int i = 0; i < 66; i++) hScaler_per_100ms[i] = MakeTH1(dir_scalers, "D", Form("hScaler_per_100ms_%s", frs_config->ScalerName(i).c_str()), Form("Scaler %s per 0.1s", frs_config->ScalerName(i).c_str()), 4000, 0, 400, "Time [100 ms]", kCyan, kViolet);
    for (int i = 0; i < 66; i++) hScaler_per_spill[i] = MakeTH1(dir_scalers, "D", Form("hScaler_per_spill_%s", frs_config->ScalerName(i).c_str()), Form("Scaler %s per spill ", frs_config->ScalerName(i).c_str()), 1000, 0, 1000, "Spill", kCyan, kViolet);

    if (frs_config->plot_tac_2d)
    {
        // directory, type, name, title, xbins, xmin, xmax, ybins, ymin, ymax, xtitle, ytitle
        h2_Z_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_AoQ", "Z1 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
        h2_Z_vs_AoQ_corr = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_AoQ_corr", "Z1 vs. A/Q (corr)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z,"A/Q", "Z (MUSIC 1)");
        h2_Z_vs_Z2 = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_Z2", "Z1 vs. Z2", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z, "Z (MUSIC 1)", "Z (MUSIC 2)");
        h2_travmus_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_travmus_vs_Z", "Z (Travel MUSIC) vs Z (MUSIC 1)", 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_Z, frs_config->fMax_Z, "Z (Travel MUSIC)", "Z (MUSIC 1)");
        h2_Z_vs_AoQ_Zsame = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_AoQ_Zsame", "Z1 vs. A/Q [ABS (Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
        h2_x2_vs_AoQ_Zsame = MakeTH2(dir_tac_2d, "D", "h2_x2_vs_AoQ_Zsame", "x2 vs A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
        h2_x4_vs_AoQ_Zsame = MakeTH2(dir_tac_2d, "D", "h2_x4_vs_AoQ_Zsame", "x4 vs A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
        h2_x2_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_x2_vs_AoQ", "x2 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
        h2_x4_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_x4_vs_AoQ", "x4 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
        h2_dEdegoQ_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_dEdegoQ_vs_Z", "dE in S2 degrader / Q vs. Z1", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ, "dE in S2 degrader / Q", "Z (MUSIC 1)");
        h2_dEdeg_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_dEdeg_vs_Z", "dE in S2 degrader vs. Z1", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dE, frs_config->fMax_dE, "dE in S2 degrader", "Z (MUSIC 1)");
        h2_a2_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_a2_vs_AoQ", "A/Q vs. AngleX (S2)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a2, frs_config->fMax_a2, "A/Q", "AngleX (S2)");
        h2_a4_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_a4_vs_AoQ", "A/Q vs. AngleX (S4)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a4, frs_config->fMax_a4, "A/Q", "AngleX (S4)");
        h2_Z_vs_dE2 = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_dE2", "Z1 vs. dE in MUSIC2", 400, frs_config->fMin_Z, frs_config->fMax_Z, 250, frs_config->fMin_dE_Music2, frs_config->fMax_dE_Music2, "Z (MUSIC 1)", "dE in MUSIC 2");
        h2_x2_vs_x4 = MakeTH2(dir_tac_2d, "D", "h2_x2_vs_x4", "x2 vs. x4", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_x4, frs_config->fMax_x4, "S2 x-position", "S4 x-position");
        h2_SC41dE_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_SC41dE_vs_AoQ", "A/Q vs. dE in SC41", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000., "A/Q", "dE in SC41");
        h2_dE_vs_ToF = MakeTH2(dir_tac_2d, "D", "h2_dE_vs_ToF", "ToF S2-S4 vs. dE in MUSIC1", 2000, 0., 70000., 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1, "Time of Flight (S2 - S4)", "dE in MUSIC 1");
        h2_x2_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_x2_vs_Z", "x2 vs. Z1", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x2, frs_config->fMax_x2, "Z (MUSIC 1)", "S2 x-position");
        h2_x4_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_x4_vs_Z", "x4 vs. Z1", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x4, frs_config->fMax_x4, "Z (MUSIC 1)", "S4 x-position");
        h2_dE1_vs_x2 = MakeTH2(dir_tac_2d, "D", "h2_dE1_vs_x2", "x2 vs. dE in MUSIC1", 200, frs_config->fMin_x2, frs_config->fMax_x2, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1, "S2 x-position", "dE in MUSIC 1");
        h2_dE1_vs_x4 = MakeTH2(dir_tac_2d, "D", "h2_dE1_vs_x4", "x4 vs. dE in MUSIC1", 200, frs_config->fMin_x4, frs_config->fMax_x4, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1, "S4 x-position", "dE in MUSIC 1");
        h2_x2_vs_a2 = MakeTH2(dir_tac_2d, "D", "h2_x2_vs_a2", "x2 vs. AngleX (S2)", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_a2, frs_config->fMax_a2, "S2 x-position", "AngleX (S2)");
        h2_y2_vs_b2 = MakeTH2(dir_tac_2d, "D", "h2_y2_vs_b2", "y2 vs. AngleY (S2)", 200, frs_config->fMin_y2, frs_config->fMax_y2, 200, frs_config->fMin_b2, frs_config->fMax_b2, "S2 y-position", "AngleY (S2)");
        h2_x4_vs_a4 = MakeTH2(dir_tac_2d, "D", "h2_x4_vs_a4", "x4 vs. AngleX (S4)", 200, frs_config->fMin_x4, frs_config->fMax_x4, 200, frs_config->fMin_a4, frs_config->fMax_a4, "S4 x-position", "AngleX (S4)");
        h2_y4_vs_b4 = MakeTH2(dir_tac_2d, "D", "h2_y4_vs_b4", "y4 vs. AngleY (S4)", 200, frs_config->fMin_y4, frs_config->fMax_y4, 200, frs_config->fMin_b4, frs_config->fMax_b4, "S4 y-position", "AngleY (S4)");
        h2_Z_vs_Sc21E = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_Sc21E", "Z1 vs. SQRT(Sc21_L * Sc21_R)", 300, frs_config->fMin_Z, frs_config->fMax_Z, 400, 0., 4000., "Z (MUSIC 1)", "Sc21 E");
    
        // ZvsZ2 gates
        if (!FrsGates.empty())
        {
            h2_Z_vs_AoQ_Z1Z2gate.resize(FrsGates.size());
            h2_Z1_vs_Z2_Z1Z2gate.resize(FrsGates.size());
            h2_x2_vs_AoQ_Z1Z2gate.resize(FrsGates.size());
            h2_x4_vs_AoQ_Z1Z2gate.resize(FrsGates.size());
            h2_dEdeg_vs_Z_Z1Z2gate.resize(FrsGates.size());
            h2_dedegoQ_vs_Z_Z1Z2gate.resize(FrsGates.size());
            h2_x2_vs_AoQ_Z1Z2x2AoQgate.resize(FrsGates.size());
            h2_x4_vs_AoQ_Z1Z2x2AoQgate.resize(FrsGates.size());
            h2_Z_vs_AoQ_Z1Z2x2AoQgate.resize(FrsGates.size());
            h2_dEdeg_vs_Z_Z1Z2x2AoQgate.resize(FrsGates.size());
            h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate.resize(FrsGates.size());
            h2_x2_vs_AoQ_Z1Z2x4AoQgate.resize(FrsGates.size());
            h2_x4_vs_AoQ_Z1Z2x4AoQgate.resize(FrsGates.size());
            h2_Z_vs_AoQ_Z1Z2x4AoQgate.resize(FrsGates.size());
            h2_dEdeg_vs_Z_Z1Z2x4AoQgate.resize(FrsGates.size());
            h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate.resize(FrsGates.size());
         
            for (int gate = 0; gate < FrsGates.size(); gate++)
            {   
                h2_Z_vs_AoQ_Z1Z2gate[gate] = MakeTH2(dir_ZvsZ2, "I", Form("h2_Z_vs_AoQ_ZAoQgate%s", FrsGates[gate]->GetName().c_str()), Form("Z vs. A/Q - ZAoQ Gate %i", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 750, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
                h2_Z1_vs_Z2_Z1Z2gate[gate] = MakeTH2(dir_ZvsZ2, "I", Form("h2_Z1_vs_Z2_ZAoQgate%i", gate), Form("Z1 vs. Z2 - ZAoQ Gate %i", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_Z, frs_config->fMax_Z, "Z (MUSIC 1)", "Z (MUSIC 2)");
                h2_x2_vs_AoQ_Z1Z2gate[gate] = MakeTH2(dir_ZvsZ2, "I", Form("h2_x2_vs_AoQ_ZAoQgate%i", gate), Form("x2 vs. A/Q - ZAoQ Gate %i", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
                h2_x4_vs_AoQ_Z1Z2gate[gate] = MakeTH2(dir_ZvsZ2, "I", Form("h2_x4_vs_AoQ_ZAoQgate%i", gate), Form("x4 vs. A/Q - ZAoQ Gate %i", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
                h2_dEdeg_vs_Z_Z1Z2gate[gate] = MakeTH2(dir_ZvsZ2, "I", Form("h2_dEdeg_vs_Z_ZAoQgate%i", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate %i", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dE, frs_config->fMax_dE, "Z (MUSIC 1)", "dE in S2 degrader");
                h2_dedegoQ_vs_Z_Z1Z2gate[gate] = MakeTH2(dir_ZvsZ2, "I", Form("h2_dedegoQ_vs_Z_ZAoQgate%i", gate), Form("Z1 vs. dE in S2 degrader / Q - ZAoQ Gate %i", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ, "Z (MUSIC 1)", "dE in S2 degrader / Q");
                
                // Second gate - x2 vs AoQ
                h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate] = MakeTH2(dir_ZvsZ2_x2vsAoQ, "I", Form("h2_x2_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
                h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate] = MakeTH2(dir_ZvsZ2_x2vsAoQ, "I", Form("h2_x4_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
                h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate] = MakeTH2(dir_ZvsZ2_x2vsAoQ, "I", Form("h2_Z_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("Z1 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 750, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
                h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate] = MakeTH2(dir_ZvsZ2_x2vsAoQ, "I", Form("h2_dEdeg_vs_Z_Z1Z2x2AoQgate%d", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dE, frs_config->fMax_dE, "Z (MUSIC 1)", "dE in S2 degrader");
                h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate] = MakeTH2(dir_ZvsZ2_x2vsAoQ, "I", Form("h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate%d", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ, "Z (MUSIC 1)", "dE in S2 degrader / Q");

                // Second gate - x4 vs AoQ
                h2_x2_vs_AoQ_Z1Z2x4AoQgate[gate] = MakeTH2(dir_ZvsZ2_x4vsAoQ, "I", Form("h2_x2_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
                h2_x4_vs_AoQ_Z1Z2x4AoQgate[gate] = MakeTH2(dir_ZvsZ2_x4vsAoQ, "I", Form("h2_x4_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
                h2_Z_vs_AoQ_Z1Z2x4AoQgate[gate] = MakeTH2(dir_ZvsZ2_x4vsAoQ, "I", Form("h2_Z_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("Z1 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 750, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
                h2_dEdeg_vs_Z_Z1Z2x4AoQgate[gate] = MakeTH2(dir_ZvsZ2_x4vsAoQ, "I", Form("h2_dEdeg_vs_Z_Z1Z2x4AoQgate%d", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dE, frs_config->fMax_dE, "Z (MUSIC 1)", "dE in S2 degrader");
                h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[gate] = MakeTH2(dir_ZvsZ2_x4vsAoQ, "I", Form("h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate%d", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ, "Z (MUSIC 1)", "dE in S2 degrader / Q");               
               
            }
        }
    }

    if (frs_config->plot_tac_1d)
    {   
        // preset wide ranges to "always" see peak, in case there's something funky with the FRS
        h1_Z = MakeTH1(dir_tac_1d, "D", "h1_Z", "Z (MUSIC 1)", 500, 10, 100, "Z (MUSIC 1)", kPink-3, kBlue+2);
        h1_Z2 = MakeTH1(dir_tac_1d, "D", "h1_Z2", "Z (MUSIC 2)", 500, 10, 100, "Z (MUSIC 2)", kPink-3, kBlue+2);
        h1_Z_travmus = MakeTH1(dir_tac_1d, "D", "h1_Z_travmus", "Z (Travel MUSIC)", 750, 10, 100, "Z (Travel MUSIC)", kPink-3, kBlue+2);
        h1_AoQ = MakeTH1(dir_tac_1d, "D", "h1_AoQ", "A/Q", 500, 1.0, 4.0, "A/Q", kPink-3, kBlue+2); 
        h1_AoQ_corr = MakeTH1(dir_tac_1d, "D", "h1_AoQ_corr", "A/Q (corr)", 500, 1.0, 4.0, "A/Q", kPink-3, kBlue+2);
        h1_x2 = MakeTH1(dir_tac_1d, "D", "h1_x2", "S2 x-position", 200, -100, 100, "S2 x-position", kYellow-7, kBlack);
        h1_x4 = MakeTH1(dir_tac_1d, "D", "h1_x4", "S4 x-position", 200, -100, 100, "S4 x-position",kYellow-7, kBlack);
        h1_a2 = MakeTH1(dir_tac_1d, "D", "h1_a2", "AngleX S2", 200, -100, 100, "AngleX S2", kYellow-7, kBlack);
        h1_a4 = MakeTH1(dir_tac_1d, "D", "h1_a4", "AngleX S4", 200, -100, 100, "AngleX S4", kYellow-7, kBlack);
        h1_y2 = MakeTH1(dir_tac_1d, "D", "h1_y2", "S2 y-position", 200, -100, 100, "S2 y-position", kYellow-7, kBlack);
        h1_y4 = MakeTH1(dir_tac_1d, "D", "h1_y4", "S4 y-position", 200, -100, 100, "S4 y-position", kYellow-7, kBlack);
        h1_b2 = MakeTH1(dir_tac_1d, "D", "h1_b2", "AngleY S2", 200, -100, 100, "AngleY S2", kYellow-7, kBlack);
        h1_b4 = MakeTH1(dir_tac_1d, "D", "h1_b4", "AngleY S4", 200, -100, 100, "AngleY S4", kYellow-7, kBlack);
        h1_beta = MakeTH1(dir_tac_1d, "D", "h1_beta", "Beta", 500, 0.0, 1.0, "Beta", kPink-3, kBlue+2);
        h1_dEdeg = MakeTH1(dir_tac_1d, "D", "h1_dEdeg", "dE in S2 degrader", 1000, 0.0, 1000., "dE", kPink-3, kBlue+2);
        h1_dEdegoQ = MakeTH1(dir_tac_1d, "D", "h1_dEdegoQ", "dE in S2 degrader / Q", 1000, 0.0, 10.0, "dE / Q", kPink-3, kBlue+2);
        for (int i = 0; i < 2; i++) h1_rho[i] = MakeTH1(dir_tac_1d, "D", Form("h1_rho_%i", i), Form("rho %i", i), 100, 0.0, 1.0, Form("rho %i", i), kPink-3, kBlue+2); 
        for (int i = 0; i < 2; i++) h1_brho[i] = MakeTH1(dir_tac_1d, "D", Form("h1_brho_%i", i), Form("brho %i", i), 100, 0.0, 1.0, Form("brho %i", i), kPink-3, kBlue+2);
        for (int i = 0; i < 2; i++) h1_music_dE[i] = MakeTH1(dir_tac_1d, "D", Form("h1_music_dE_%i", i), Form("Energy loss in MUSIC %i", i+1), 1000, 0.0, 4000.0, Form("dE MUSIC %i", i+1), kPink-3, kBlue+2);
        h1_travmus_dE = MakeTH1(dir_tac_1d, "D", "h1_travmus_dE", "dE (Travel MUSIC)", 1000, 0, 4000., "dE (Travel MUSIC)", kPink-3, kBlue+2);
        for (int i = 0; i < 2; i++) h1_music_dEcorr[i] = MakeTH1(dir_tac_1d, "D", Form("h1_music_dEcorr_%i", i), Form("Energy loss (corr) in MUSIC %i", i+1), 4000, 0.0, 4000.0, Form("dE (corr) MUSIC %i", i+1), kPink-3, kBlue+2);
        for (int i = 0; i < 6; i++) h1_sci_e[i] = MakeTH1(dir_tac_1d, "D", Form("h1_sci_e_%i", i), Form("SCI E %i", i), 4000, 0.0, 4000.0, Form("SCI E %i", i), kPink-3, kBlue+2);
        for (int i = 0; i < 6; i++) h1_sci_l[i] = MakeTH1(dir_tac_1d, "D", Form("h1_sci_l_%i", i), Form("SCI L %i", i), 4000, 0.0, 4000.0, Form("SCI L %i", i), kPink-3, kBlue+2);
        for (int i = 0; i < 6; i++) h1_sci_r[i] = MakeTH1(dir_tac_1d, "D", Form("h1_sci_r_%i", i), Form("SCI R %i", i), 4000, 0.0, 4000.0, Form("SCI R %i", i), kPink-3, kBlue+2);
        for (int i = 0; i < 6; i++) h1_sci_x[i] = MakeTH1(dir_tac_1d, "D", Form("h1_sci_x_%i", i), Form("SCI X %i", i), 4000, 0.0, 4000.0, Form("SCI X %i", i), kYellow-7, kBlack);
        for (int i = 0; i < 6; i++) h1_sci_tof[i] = MakeTH1(dir_tac_1d, "D", Form("h1_sci_tof_%i", i), Form("SCI TOF %i", i), 4000, 0.0, 200000.0, Form("SCI TOF %i", i), kPink-3, kBlue+2);
        for (int i = 0; i < 6; i++) h1_sci_tof_calib[i] = MakeTH1(dir_tac_1d, "D", Form("h1_sci_tof_calib_%i", i), Form("SCI TOF CALIB %i", i), 4000, 0.0, 4000.0, Form("SCI TOF (Calib) %i", i), kPink-3, kBlue+2);

        // Are Gated 1D desired?
    }

    if (frs_config->plot_mhtdc_2d)
    {
        // directory, type, name, title, xbins, xmin, xmax, ybins, ymin, ymax, xtitle, ytitle
        h2_Z_vs_AoQ_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_Z_vs_AoQ_mhtdc", "Z1 vs. A/Q (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
        h2_Z_vs_AoQ_corr_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_Z_vs_AoQ_corr_mhtdc", "Z1 vs. A/Q (corr) (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z,"A/Q", "Z (MUSIC 1)");
        h2_Z_vs_Z2_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_Z_vs_Z2_mhtdc", "Z1 vs. Z2 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z, "Z (MUSIC 1)", "Z (MUSIC 2)");
        h2_travmus_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_travmus_vs_Z_mhtdc", "Z (Trav) vs. Z1 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z, "Z (Travel MUSIC)", "Z (MUSIC 1)");
        h2_Z_vs_AoQ_Zsame_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_Z_vs_AoQ_Zsame_mhtdc", "Z1 vs. A/Q [ABS (Z1 - Z2) < 0.4] (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
        h2_x2_vs_AoQ_Zsame_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_x2_vs_AoQ_Zsame_mhtdc", "x2 vs A/Q - [ABS(Z1 - Z2) < 0.4] (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
        h2_x4_vs_AoQ_Zsame_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_x4_vs_AoQ_Zsame_mhtdc", "x4 vs A/Q - [ABS(Z1 - Z2) < 0.4] (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
        h2_x2_vs_AoQ_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_x2_vs_AoQ_mhtdc", "x2 vs. A/Q (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
        h2_x4_vs_AoQ_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_x4_vs_AoQ_mhtdc", "x4 vs. A/Q (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
        h2_dEdegoQ_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_dEdegoQ_vs_Z_mhtdc", "dE in S2 degrader / Q vs. Z1 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ, "dE in S2 degrader / Q", "Z (MUSIC 1)");
        h2_dEdeg_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_dEdeg_vs_Z_mhtdc", "dE in S2 degrader vs. Z1 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dE, frs_config->fMax_dE, "dE in S2 degrader", "Z (MUSIC 1)");
        h2_a2_vs_AoQ_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_a2_vs_AoQ_mhtdc", "A/Q vs. AngleX (S2) (MHTDC)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a2, frs_config->fMax_a2, "A/Q", "AngleX (S2)");
        h2_a4_vs_AoQ_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_a4_vs_AoQ_mhtdc", "A/Q vs. AngleX (S4) (MHTDC)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a4, frs_config->fMax_a4, "A/Q", "AngleX (S4)");
        h2_Z_vs_dE2_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_Z_vs_dE2_mhtdc", "Z1 vs. dE in MUSIC2 (MHTDC)", 400, frs_config->fMin_Z, frs_config->fMax_Z, 250, frs_config->fMin_dE_Music2, frs_config->fMax_dE_Music2, "Z (MUSIC 1)", "dE in MUSIC 2");
        h2_SC41dE_vs_AoQ_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_SC41dE_vs_AoQ_mhtdc", "A/Q vs. dE in SC41 (MHTDC)", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000., "A/Q", "dE in SC41");
        h2_x2_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_x2_vs_Z_mhtdc", "x2 vs. Z1 (MHTDC)", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x2, frs_config->fMax_x2, "Z (MUSIC 1)", "S2 x-position");
        h2_x4_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_x4_vs_Z_mhtdc", "x4 vs. Z1 (MHTDC)", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x4, frs_config->fMax_x4, "Z (MUSIC 1)", "S4 x-position");
        h2_Z_vs_Sc21E_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_Z_vs_Sc21E_mhtdc", "Z1 vs. SQRT(Sc21_L * Sc21_R) (MHTDC)", 300, frs_config->fMin_Z, frs_config->fMax_Z, 400, 0., 4000., "Z (MUSIC 1)", "Sc21 E");
        
        // neither TAC nor MHTDC, don't plot twice..
        if (!frs_config->plot_tac_2d)
        {
            h2_x2_vs_x4 = MakeTH2(dir_mhtdc_2d, "D", "h2_x2_vs_x4", "x2 vs. x4", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_x4, frs_config->fMax_x4, "S2 x-position", "S4 x-position");
            h2_dE_vs_ToF = MakeTH2(dir_mhtdc_2d, "D", "h2_dE_vs_ToF", "ToF S2-S4 vs. dE in MUSIC1", 2000, 0., 70000., 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1, "Time of Flight (S2 - S4)", "dE in MUSIC 1");
            h2_dE1_vs_x2 = MakeTH2(dir_mhtdc_2d, "D", "h2_dE1_vs_x2", "x2 vs. dE in MUSIC1", 200, frs_config->fMin_x2, frs_config->fMax_x2, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1, "S2 x-position", "dE in MUSIC 1");
            h2_dE1_vs_x4 = MakeTH2(dir_mhtdc_2d, "D", "h2_dE1_vs_x4", "x4 vs. dE in MUSIC1", 200, frs_config->fMin_x4, frs_config->fMax_x4, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1, "S4 x-position", "dE in MUSIC 1");
            h2_x2_vs_a2 = MakeTH2(dir_mhtdc_2d, "D", "h2_x2_vs_a2", "x2 vs. AngleX (S2)", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_a2, frs_config->fMax_a2, "S2 x-position", "AngleX (S2)");
            h2_y2_vs_b2 = MakeTH2(dir_mhtdc_2d, "D", "h2_y2_vs_b2", "y2 vs. AngleY (S2)", 200, frs_config->fMin_y2, frs_config->fMax_y2, 200, frs_config->fMin_b2, frs_config->fMax_b2, "S2 y-position", "AngleY (S2)");
            h2_x4_vs_a4 = MakeTH2(dir_mhtdc_2d, "D", "h2_x4_vs_a4", "x4 vs. AngleX (S4)", 200, frs_config->fMin_x4, frs_config->fMax_x4, 200, frs_config->fMin_a4, frs_config->fMax_a4, "S4 x-position", "AngleX (S4)");
            h2_y4_vs_b4 = MakeTH2(dir_mhtdc_2d, "D", "h2_y4_vs_b4", "y4 vs. AngleY (S4)", 200, frs_config->fMin_y4, frs_config->fMax_y4, 200, frs_config->fMin_b4, frs_config->fMax_b4, "S4 y-position", "AngleY (S4)");
        }

        // ZvsZ2 gates
        if (!FrsGates.empty())
        {
            h2_Z_vs_AoQ_Z1Z2gate_mhtdc.resize(FrsGates.size());
            h2_Z1_vs_Z2_Z1Z2gate_mhtdc.resize(FrsGates.size());
            h2_x2_vs_AoQ_Z1Z2gate_mhtdc.resize(FrsGates.size());
            h2_x4_vs_AoQ_Z1Z2gate_mhtdc.resize(FrsGates.size());
            h2_dEdeg_vs_Z_Z1Z2gate_mhtdc.resize(FrsGates.size());
            h2_dedegoQ_vs_Z_Z1Z2gate_mhtdc.resize(FrsGates.size());
            h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
            h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
            h2_Z_vs_AoQ_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
            h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
            h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
            h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
            h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
            h2_Z_vs_AoQ_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
            h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
            h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
         
            for (int gate = 0; gate < FrsGates.size(); gate++)
            {   
                h2_Z_vs_AoQ_Z1Z2gate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_mhtdc, "I", Form("h2_Z_vs_AoQ_ZAoQgate%s_mhtdc", FrsGates[gate]->GetName().c_str()), Form("Z vs. A/Q (MHTDC) - ZAoQ Gate %i", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 750, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
                h2_Z1_vs_Z2_Z1Z2gate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_mhtdc, "I", Form("h2_Z1_vs_Z2_ZAoQgate%i_mhtdc", gate), Form("Z1 vs. Z2 (MHTDC) - ZAoQ Gate %i", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_Z, frs_config->fMax_Z, "Z (MUSIC 1)", "Z (MUSIC 2)");
                h2_x2_vs_AoQ_Z1Z2gate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_mhtdc, "I", Form("h2_x2_vs_AoQ_ZAoQgate%i_mhtdc", gate), Form("x2 vs. A/Q (MHTDC) - ZAoQ Gate %i", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
                h2_x4_vs_AoQ_Z1Z2gate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_mhtdc, "I", Form("h2_x4_vs_AoQ_ZAoQgate%i_mhtdc", gate), Form("x4 vs. A/Q (MHTDC) - ZAoQ Gate %i", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
                h2_dEdeg_vs_Z_Z1Z2gate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_mhtdc, "I", Form("h2_dEdeg_vs_Z_ZAoQgate%i_mhtdc", gate), Form("Z1 vs. dE in S2 degrader (MHTDC) - ZAoQ Gate %i", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dE, frs_config->fMax_dE, "Z (MUSIC 1)", "dE in S2 degrader");
                h2_dedegoQ_vs_Z_Z1Z2gate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_mhtdc, "I", Form("h2_dedegoQ_vs_Z_ZAoQgate%i_mhtdc", gate), Form("Z1 vs. dE in S2 degrader / Q (MHTDC) - ZAoQ Gate %i", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ, "Z (MUSIC 1)", "dE in S2 degrader / Q");
                
                // Second gate - x2 vs AoQ
                h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_x2vsAoQ_mhtdc, "I", Form("h2_x2_vs_AoQ_Z1Z2x2AoQgate%d_mhtdc", gate), Form("x2 vs. A/Q (MHTDC) - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
                h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_x2vsAoQ_mhtdc, "I", Form("h2_x4_vs_AoQ_Z1Z2x2AoQgate%d_mhtdc", gate), Form("x4 vs. A/Q (MHTDC) - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
                h2_Z_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_x2vsAoQ_mhtdc, "I", Form("h2_Z_vs_AoQ_Z1Z2x2AoQgate%d_mhtdc", gate), Form("Z1 vs. A/Q (MHTDC) - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 750, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
                h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_x2vsAoQ_mhtdc, "I", Form("h2_dEdeg_vs_Z_Z1Z2x2AoQgate%d_mhtdc", gate), Form("dE in S2 degrader vs. Z1 (MHTDC) - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dE, frs_config->fMax_dE, "Z (MUSIC 1)", "dE in S2 degrader");
                h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_x2vsAoQ_mhtdc, "I", Form("h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate%d_mhtdc", gate), Form("dE in S2 degrader / Q vs. Z1 (MHTDC) - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ, "Z (MUSIC 1)", "dE in S2 degrader / Q");

                // Second gate - x4 vs AoQ
                h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_x4vsAoQ_mhtdc, "I", Form("h2_x2_vs_AoQ_Z1Z2x4AoQgate%d_mhtdc", gate), Form("x2 vs. A/Q (MHTDC) - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
                h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_x4vsAoQ_mhtdc, "I", Form("h2_x4_vs_AoQ_Z1Z2x4AoQgate%d_mhtdc", gate), Form("x4 vs. A/Q (MHTDC) - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
                h2_Z_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_x4vsAoQ_mhtdc, "I", Form("h2_Z_vs_AoQ_Z1Z2x4AoQgate%d_mhtdc", gate), Form("Z1 vs. A/Q (MHTDC) - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 750, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
                h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_x4vsAoQ_mhtdc, "I", Form("h2_dEdeg_vs_Z_Z1Z2x4AoQgate%d_mhtdc", gate), Form("dE in S2 degrader vs. Z1 (MHTDC) - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dE, frs_config->fMax_dE, "Z (MUSIC 1)", "dE in S2 degrader");
                h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc[gate] = MakeTH2(dir_ZvsZ2_x4vsAoQ_mhtdc, "I", Form("h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate%d_mhtdc", gate), Form("dE in S2 degrader / Q vs. Z1 (MHTDC) - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ, "Z (MUSIC 1)", "dE in S2 degrader / Q");               
               
            }
        }
    }

    if (frs_config->plot_mhtdc_1d)
    {
        h1_beta_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_beta_mhtdc", "Beta (MHTDC)", 500, 0.0, 1.0, "Beta", kPink-3, kBlue+2);
        h1_AoQ_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_AoQ_mhtdc", "A/Q (MHTDC)", 500, 1.0, 4.0, "A/Q", kPink-3, kBlue+2);
        h1_AoQ_corr_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_AoQ_corr_mhtdc", "A/Q (corr) (MHTDC)", 500, 1.0, 4.0, "A/Q", kPink-3, kBlue+2);
        h1_z_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_z_mhtdc", "Z (MUSIC 1) (MHTDC)", 1000, 0, 100, "Z (MUSIC 1)", kPink-3, kBlue+2);
        h1_z2_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_z2_mhtdc", "Z (MUSIC 2) (MHTDC)", 1000, 0, 100, "Z (MUSIC 2)", kPink-3, kBlue+2);
        h1_z_travmus_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_z_travmus_mhtdc", "Z (Travel MUSIC) (MHTDC)", 1000, 0, 100, "Z (Travel MUSIC)", kPink-3, kBlue+2);
        h1_dEdeg_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_dEdeg_mhtdc", "dE in S2 degrader (MHTDC)", 1000, 0, 100, "dE", kPink-3, kBlue+2);
        h1_dEdegoQ_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_dEdegoQ_mhtdc", "dE in S2 degrader / Q (MHTDC)", 1000, 0.0, 2.0, "dE / Q", kPink-3, kBlue+2);

        if (!frs_config->plot_tac_1d)
        {
            h1_x2 = MakeTH1(dir_tac_1d, "D", "h1_x2", "S2 x-position", 200, -100, 100, "x2", kYellow-7, kBlack);
            h1_x4 = MakeTH1(dir_tac_1d, "D", "h1_x4", "S4 x-position", 200, -100, 100, "x4", kYellow-7, kBlack);
            h1_a2 = MakeTH1(dir_tac_1d, "D", "h1_a2", "AngleX S2", 200, -100, 100, "a2", kYellow-7, kBlack);
            h1_a4 = MakeTH1(dir_tac_1d, "D", "h1_a4", "AngleX S4", 200, -100, 100, "a4", kYellow-7, kBlack);
            h1_y2 = MakeTH1(dir_tac_1d, "D", "h1_y2", "S2 y-position", 200, -100, 100, "y2", kYellow-7, kBlack);
            h1_y4 = MakeTH1(dir_tac_1d, "D", "h1_y4", "S4 y-position", 200, -100, 100, "y4", kYellow-7, kBlack);
            h1_b2 = MakeTH1(dir_tac_1d, "D", "h1_b2", "AngleY S2", 200, -100, 100, "b2", kYellow-7, kBlack);
            h1_b4 = MakeTH1(dir_tac_1d, "D", "h1_b4", "AngleY S4", 200, -100, 100, "b4", kYellow-7, kBlack);
        }
    }

    // :::::: Rates ::::::: //
    h1_tpc21_rate = MakeTH1(dir_rates, "I", "h1_tpc21_rate", "TPC 21 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    h1_tpc22_rate = MakeTH1(dir_rates, "I", "h1_tpc22_rate", "TPC 22 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    h1_tpc23_rate = MakeTH1(dir_rates, "I", "h1_tpc23_rate", "TPC 23 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    h1_tpc24_rate = MakeTH1(dir_rates, "I", "h1_tpc24_rate", "TPC 24 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    h1_tpc41_rate = MakeTH1(dir_rates, "I", "h1_tpc41_rate", "TPC 41 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    h1_tpc42_rate = MakeTH1(dir_rates, "I", "h1_tpc42_rate", "TPC 42 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    // h1_sci21_rate = MakeTH1(dir_rates, "I", "h1_sci21_rate", "SCI 21 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    // h1_sci22_rate = MakeTH1(dir_rates, "I", "h1_sci22_rate", "SCI 22 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    // h1_sci41_rate = MakeTH1(dir_rates, "I", "h1_sci41_rate", "SCI 41 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    // h1_sci42_rate = MakeTH1(dir_rates, "I", "h1_sci42_rate", "SCI 42 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);




    // Here we can draw any canvases we need, but we don't need to make histos /

    // ::::: Travel MUSIC - treated separately until FRS sorts themselves out ::::: 
    h1_wr_frs_travmus = MakeTH1(dir_travmus, "I", "h1_wr_frs_travmus", "White Rabbit dT FRS - Travel MUSIC", 500, -3000, -1000);

    c_z_compare = new TCanvas("c_z_compare", "Z from 3 x MUSIC", 650, 350);
    c_z_compare->Divide(1, 3);
    c_z_compare->cd(1);
    h1_Z_travmus->Draw();
    c_z_compare->cd(2);
    h1_Z->Draw();
    c_z_compare->cd(3);
    h1_Z2->Draw();
    c_z_compare->cd(0);
    dir_travmus_tac->Append(c_z_compare);

    c_dE_compare = new TCanvas("c_dE_compare", "dE from 3 x MUSIC", 650, 350);
    c_dE_compare->Divide(1, 3);
    c_dE_compare->cd(1);
    h1_travmus_dE->Draw();
    c_dE_compare->cd(2);
    h1_music_dE[0]->Draw();
    c_dE_compare->cd(3);
    h1_music_dE[1]->Draw();
    c_dE_compare->cd(0);
    dir_travmus_tac->Append(c_dE_compare);

    c_z_compare_mhtdc = new TCanvas("c_z_compare_mhtdc", "Z from 3 x MUSIC MHTDC", 650, 350);
    c_z_compare_mhtdc->Divide(1, 3);
    c_z_compare_mhtdc->cd(1);
    h1_z_travmus_mhtdc->Draw();
    c_z_compare_mhtdc->cd(2);
    h1_z_mhtdc->Draw();
    c_z_compare_mhtdc->cd(3);
    h1_z2_mhtdc->Draw();
    c_z_compare_mhtdc->cd(0);
    dir_travmus_mhtdc->Append(c_z_compare_mhtdc);
    // :::::::::::::::::::: //

    // Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_FRS_Histo", Form("/Objects/%s/->Reset_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_FRS_Histo", Form("/Objects/%s/->Snapshot_Histo()", GetName()));

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
   //h1_wr->Reset();

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
            h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate]->Reset();
            h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate]->Reset();
            h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate]->Reset();
            h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate]->Reset();
            h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate]->Reset();
            h2_x2_vs_AoQ_Z1Z2x4AoQgate[gate]->Reset();
            h2_x4_vs_AoQ_Z1Z2x4AoQgate[gate]->Reset();
            h2_Z_vs_AoQ_Z1Z2x4AoQgate[gate]->Reset();
            h2_dEdeg_vs_Z_Z1Z2x4AoQgate[gate]->Reset();
            h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[gate]->Reset();
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
            h1_tpat->Draw();
            c_frs_snapshot->SaveAs("h1_tpat.png");
            c_frs_snapshot->Clear();         
        }
    }
    c4LOG(info,"FRS Spectra Snapshot saved in: " << screenshot_path + snapshot_dir);

}

void FrsOnlineSpectra::Exec(Option_t* option)
{   
    int64_t frs_wr = 0; int64_t trav_mus_wr = 0;
    if (hitArray->size() <= 0) return;
    auto const & hitItem  = hitArray->at(0); // should only ever be 1 frs item per event, so take first
    frs_wr = hitItem.Get_wr_t();
    trav_mus_wr = hitItem.Get_wr_travmus();

    // :::::::::: TAC ::::::::::::: //
    // ---------------------------- //
    if (frs_config->plot_tac_2d)
    {
        if (hitItem.Get_ID_AoQ() > 0 && hitItem.Get_ID_z() > 0) h2_Z_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
        if (hitItem.Get_ID_AoQ_corr() > 0 && hitItem.Get_ID_z() > 0) h2_Z_vs_AoQ_corr->Fill(hitItem.Get_ID_AoQ_corr(), hitItem.Get_ID_z());
        if (hitItem.Get_ID_z() > 0 && hitItem.Get_ID_z2() > 0) h2_Z_vs_Z2->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_z2());
        if (trav_mus_wr > 0 && hitItem.Get_ID_z() > 0 && hitItem.Get_ID_z_travmus() > 0) h2_travmus_vs_Z->Fill(hitItem.Get_ID_z_travmus(), hitItem.Get_ID_z());

        if (TMath::Abs(hitItem.Get_ID_z() - hitItem.Get_ID_z2()) < 0.4)
        {
            h2_Z_vs_AoQ_Zsame->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
            h2_x4_vs_AoQ_Zsame->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
            h2_x2_vs_AoQ_Zsame->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
        }

        if (hitItem.Get_ID_AoQ() > 0 && hitItem.Get_ID_x2() > -100 && hitItem.Get_ID_x2() < 100) h2_x2_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
        if (hitItem.Get_ID_AoQ() > 0 && hitItem.Get_ID_x4() > -100 && hitItem.Get_ID_x4() < 100) h2_x4_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
        if (hitItem.Get_ID_z() > 0 && hitItem.Get_ID_dEdegoQ() != 0) h2_dEdegoQ_vs_Z->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdegoQ()); // Charge states
        if (hitItem.Get_ID_z() > 0 && hitItem.Get_ID_dEdeg() != 0) h2_dEdeg_vs_Z->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdeg());
        if (hitItem.Get_ID_AoQ() != 0 && hitItem.Get_ID_a2() != 0) h2_a2_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_a2());
        if (hitItem.Get_ID_AoQ() != 0 && hitItem.Get_ID_a4() != 0) h2_a4_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_a4());
        if (hitItem.Get_ID_z() != 0 && hitItem.Get_music_dE(1) != 0) h2_Z_vs_dE2->Fill(hitItem.Get_ID_z(), hitItem.Get_music_dE(1));
        if (hitItem.Get_ID_x2() != 0 && hitItem.Get_ID_x4() != 0) h2_x2_vs_x4->Fill(hitItem.Get_ID_x2(), hitItem.Get_ID_x4());
        if (hitItem.Get_ID_AoQ() != 0 && hitItem.Get_sci_e(2) != 0) h2_SC41dE_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_sci_e(2)); // CEJ: changed from Go4, [5] -> [2]
        if (hitItem.Get_sci_tof2() != 0 && hitItem.Get_music_dE(0) != 0) h2_dE_vs_ToF->Fill(hitItem.Get_sci_tof2(), hitItem.Get_music_dE(0));
        if (hitItem.Get_ID_z() != 0 && hitItem.Get_ID_x2() != 0) h2_x2_vs_Z->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_x2());
        if (hitItem.Get_ID_z() != 0 && hitItem.Get_ID_x4() != 0) h2_x4_vs_Z->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_x4());
        if (hitItem.Get_ID_x2() != 0 && hitItem.Get_music_dE(0) != 0) h2_dE1_vs_x2->Fill(hitItem.Get_ID_x2(), hitItem.Get_music_dE(0));
        if (hitItem.Get_ID_x4() != 0 && hitItem.Get_music_dE(0) != 0) h2_dE1_vs_x4->Fill(hitItem.Get_ID_x4(), hitItem.Get_music_dE(0));
        if (hitItem.Get_ID_x2() != 0 && hitItem.Get_ID_a2() != 0) h2_x2_vs_a2->Fill(hitItem.Get_ID_x2(), hitItem.Get_ID_a2());
        if (hitItem.Get_ID_y2() != 0 && hitItem.Get_ID_b2() != 0) h2_y2_vs_b2->Fill(hitItem.Get_ID_y2(), hitItem.Get_ID_b2());
        if (hitItem.Get_ID_x4() != 0 && hitItem.Get_ID_a4() != 0) h2_x4_vs_a4->Fill(hitItem.Get_ID_x4(), hitItem.Get_ID_a4());
        if (hitItem.Get_ID_y4() != 0 && hitItem.Get_ID_b4() != 0) h2_y4_vs_b4->Fill(hitItem.Get_ID_y4(), hitItem.Get_ID_b4());
        if (hitItem.Get_ID_z() != 0 && hitItem.Get_sci_l(0) != 0 && hitItem.Get_sci_r(0) != 0) h2_Z_vs_Sc21E->Fill(hitItem.Get_ID_z(), sqrt(hitItem.Get_sci_l(0) * hitItem.Get_sci_r(0))); // CEJ: changed [2] -> [0]

        // 2D Gated
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

                    if (FrsGates[gate]->Passed_x2vsAoQ(hitItem.Get_ID_x2(), hitItem.Get_ID_AoQ()))
                    {
                        h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
                        h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
                        h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
                        h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdeg());
                        h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdegoQ());
                    }

                    if (FrsGates[gate]->Passed_x4vsAoQ(hitItem.Get_ID_x4(), hitItem.Get_ID_AoQ()))
                    {
                        h2_x2_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
                        h2_x4_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
                        h2_Z_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
                        h2_dEdeg_vs_Z_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdeg());
                        h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdegoQ());
                    }
                }
            }
        }
    }

    if (frs_config->plot_tac_1d)
    {
        if (hitItem.Get_ID_z() > 0) h1_Z->Fill(hitItem.Get_ID_z());
        if (hitItem.Get_ID_z2() > 0) h1_Z2->Fill(hitItem.Get_ID_z2());
        if (trav_mus_wr > 0 && hitItem.Get_ID_z_travmus() > 0) h1_Z_travmus->Fill(hitItem.Get_ID_z_travmus());
        if (hitItem.Get_ID_AoQ() > 0) h1_AoQ->Fill(hitItem.Get_ID_AoQ());
        if (hitItem.Get_ID_AoQ_corr() > 0) h1_AoQ_corr->Fill(hitItem.Get_ID_AoQ_corr());
        h1_x2->Fill(hitItem.Get_ID_x2());
        h1_x4->Fill(hitItem.Get_ID_x4());
        h1_a2->Fill(hitItem.Get_ID_a2());
        h1_a4->Fill(hitItem.Get_ID_a4());
        h1_y2->Fill(hitItem.Get_ID_y2());
        h1_y4->Fill(hitItem.Get_ID_y4());
        h1_b2->Fill(hitItem.Get_ID_b2());
        h1_b4->Fill(hitItem.Get_ID_b4());
        if (hitItem.Get_ID_beta() > 0) h1_beta->Fill(hitItem.Get_ID_beta()); 
        if (hitItem.Get_ID_dEdeg() > 0) h1_dEdeg->Fill(hitItem.Get_ID_dEdeg());
        if (hitItem.Get_ID_dEdegoQ() > 0) h1_dEdegoQ->Fill(hitItem.Get_ID_dEdegoQ());
        for (int i = 0; i < 2; i++) if (hitItem.Get_ID_rho(i) > 0) h1_rho[i]->Fill(hitItem.Get_ID_rho(i));
        for (int i = 0; i < 2; i++) if (hitItem.Get_ID_brho(i) > 0) h1_brho[i]->Fill(hitItem.Get_ID_brho(i));
        for (int i = 0; i < 2; i++) if (hitItem.Get_music_dE(i) > 0) h1_music_dE[i]->Fill(hitItem.Get_music_dE(i));
        if (trav_mus_wr > 0 && hitItem.Get_travmusic_dE() > 0) h1_travmus_dE->Fill(hitItem.Get_travmusic_dE());
        for (int i = 0; i < 2; i++) if (hitItem.Get_music_dE_cor(i) > 0) h1_music_dEcorr[i]->Fill(hitItem.Get_music_dE_cor(i));
        for (int i = 0; i < 6; i++) if (hitItem.Get_sci_e(i) > 0) h1_sci_e[i]->Fill(hitItem.Get_sci_e(i));
        for (int i = 0; i < 6; i++) if (hitItem.Get_sci_l(i) > 0) h1_sci_l[i]->Fill(hitItem.Get_sci_l(i));
        for (int i = 0; i < 6; i++) if (hitItem.Get_sci_r(i) > 0) h1_sci_r[i]->Fill(hitItem.Get_sci_r(i));
        for (int i = 0; i < 6; i++) h1_sci_x[i]->Fill(hitItem.Get_sci_x(i));
        for (int i = 0; i < 6; i++) if (hitItem.Get_sci_tof(i) > 0) h1_sci_tof[i]->Fill(hitItem.Get_sci_tof(i));
        for (int i = 0; i < 6; i++) if (hitItem.Get_sci_tof_calib(i) > 0) h1_sci_tof_calib[i]->Fill(hitItem.Get_sci_tof_calib(i));

        // 1D Gated?
    }

    // :::::: Multi-hit TDC ::::::: //
    // ---------------------------- //
    for (auto const & multihitItem : *multihitArray)
    {
        if (frs_config->plot_mhtdc_2d)
        {   
            if (multihitItem.Get_ID_z_mhtdc() > 0 && multihitItem.Get_ID_AoQ_mhtdc() > 0) h2_Z_vs_AoQ_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_AoQ_mhtdc());
            if (multihitItem.Get_ID_z_mhtdc() > 0 && multihitItem.Get_ID_AoQ_corr_mhtdc() > 0) h2_Z_vs_AoQ_corr_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_AoQ_corr_mhtdc());
            if (multihitItem.Get_ID_z_mhtdc() > 0 && multihitItem.Get_ID_z2_mhtdc() > 0) h2_Z_vs_Z2_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_z2_mhtdc());
            if (trav_mus_wr > 0 && multihitItem.Get_ID_z_mhtdc() > 0 && multihitItem.Get_ID_z_travmus_mhtdc() > 0) h2_travmus_vs_Z_mhtdc->Fill(multihitItem.Get_ID_z_travmus_mhtdc(), multihitItem.Get_ID_z_mhtdc());
            if (multihitItem.Get_ID_z_mhtdc() > 0 && multihitItem.Get_ID_AoQ_mhtdc() > 0 && TMath::Abs(multihitItem.Get_ID_z_mhtdc() - multihitItem.Get_ID_z2_mhtdc()) < 0.4) h2_Z_vs_AoQ_Zsame_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_AoQ_mhtdc());
            if (multihitItem.Get_ID_AoQ_mhtdc() > 0 && TMath::Abs(multihitItem.Get_ID_z_mhtdc() - multihitItem.Get_ID_z2_mhtdc()) < 0.4) h2_x2_vs_AoQ_Zsame_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x2());
            if (multihitItem.Get_ID_AoQ_mhtdc() > 0 && TMath::Abs(multihitItem.Get_ID_z_mhtdc() - multihitItem.Get_ID_z2_mhtdc()) < 0.4) h2_x4_vs_AoQ_Zsame_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x4());
            if (multihitItem.Get_ID_AoQ_mhtdc() > 0) h2_x2_vs_AoQ_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x2());
            if (multihitItem.Get_ID_AoQ_mhtdc() > 0) h2_x4_vs_AoQ_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x4());
            if (multihitItem.Get_ID_z_mhtdc() > 0 && multihitItem.Get_ID_dEdeg_mhtdc() > 0) h2_dEdeg_vs_Z_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_dEdeg_mhtdc());
            if (multihitItem.Get_ID_z_mhtdc() > 0 && multihitItem.Get_ID_dEdegoQ_mhtdc() > 0) h2_dEdegoQ_vs_Z_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_dEdegoQ_mhtdc());
            if (multihitItem.Get_ID_AoQ_mhtdc() > 0) h2_a2_vs_AoQ_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_a2());
            if (multihitItem.Get_ID_AoQ_mhtdc() > 0) h2_a4_vs_AoQ_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_a4());
            if (multihitItem.Get_ID_z_mhtdc() > 0 && hitItem.Get_music_dE(1) > 0) h2_Z_vs_dE2_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), hitItem.Get_music_dE(1));
            if (multihitItem.Get_ID_AoQ_mhtdc() > 0 && hitItem.Get_sci_e(2) > 0) h2_SC41dE_vs_AoQ_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_sci_e(2));
            if (multihitItem.Get_ID_z_mhtdc() > 0) h2_x2_vs_Z_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), hitItem.Get_ID_x2());
            if (multihitItem.Get_ID_z_mhtdc() > 0) h2_x4_vs_Z_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), hitItem.Get_ID_x4());
            if (multihitItem.Get_ID_z_mhtdc() > 0 && hitItem.Get_sci_l(0) != 0 && hitItem.Get_sci_r(0) != 0) h2_Z_vs_Sc21E_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), sqrt(hitItem.Get_sci_l(0) * hitItem.Get_sci_r(0)));
        }

        if (frs_config->plot_mhtdc_1d)
        {
            if (multihitItem.Get_ID_beta_mhtdc() > 0) h1_beta_mhtdc->Fill(multihitItem.Get_ID_beta_mhtdc());
            if (multihitItem.Get_ID_AoQ_mhtdc() > 0) h1_AoQ_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc());
            if (multihitItem.Get_ID_AoQ_corr_mhtdc() > 0) h1_AoQ_corr_mhtdc->Fill(multihitItem.Get_ID_AoQ_corr_mhtdc());
            if (multihitItem.Get_ID_z_mhtdc() > 0) h1_z_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc());
            if (multihitItem.Get_ID_z2_mhtdc() > 0) h1_z2_mhtdc->Fill(multihitItem.Get_ID_z2_mhtdc());
            if (trav_mus_wr > 0 && multihitItem.Get_ID_z_travmus_mhtdc() > 0) h1_z_travmus_mhtdc->Fill(multihitItem.Get_ID_z_travmus_mhtdc());
            if (multihitItem.Get_ID_z_travmus_mhtdc() > 0) h1_z_travmus_mhtdc->Fill(multihitItem.Get_ID_z_travmus_mhtdc());
            if (multihitItem.Get_ID_dEdeg_mhtdc() > 0) h1_dEdeg_mhtdc->Fill(multihitItem.Get_ID_dEdeg_mhtdc());
            if (multihitItem.Get_ID_dEdegoQ_mhtdc() > 0) h1_dEdegoQ_mhtdc->Fill(multihitItem.Get_ID_dEdegoQ_mhtdc());

            if (!frs_config->plot_tac_1d)
            {
                h1_x2->Fill(hitItem.Get_ID_x2());
                h1_x4->Fill(hitItem.Get_ID_x4());
                h1_a2->Fill(hitItem.Get_ID_a2());
                h1_a4->Fill(hitItem.Get_ID_a4());
                h1_y2->Fill(hitItem.Get_ID_y2());
                h1_y4->Fill(hitItem.Get_ID_y4());
                h1_b2->Fill(hitItem.Get_ID_b2());
                h1_b4->Fill(hitItem.Get_ID_b4());
            }
        }
    }

    // :::::::: Scalers ::::::::::: //
    // ---------------------------- //
    h1_tpat->Fill(hitItem.Get_tpat());

    for (int i = 0; i < 32; i++)
    {   
        //std::cout << "i: " << i << " - ibin for s: " << hitItem.Get_ibin_for_s() << " - sc_temp_main: " << hitItem.Get_increase_sc_temp_main(i) << " - sc_temp_user: " << hitItem.Get_increase_sc_temp_user(i) <<std::endl;

        // CEJ: swapped main and user (hopefully correct) 29/05/24
        hScaler_per_s[i]->AddBinContent(hitItem.Get_ibin_for_s(), hitItem.Get_increase_sc_temp_user(i));
        hScaler_per_s[i+32]->AddBinContent(hitItem.Get_ibin_for_s(), hitItem.Get_increase_sc_temp_main(i));
        hScaler_per_100ms[i]->AddBinContent(hitItem.Get_ibin_for_100ms(), hitItem.Get_increase_sc_temp_user(i));
        hScaler_per_100ms[i+32]->AddBinContent(hitItem.Get_ibin_for_100ms(), hitItem.Get_increase_sc_temp_main(i));
        hScaler_per_spill[i]->AddBinContent(hitItem.Get_ibin_for_spill(), hitItem.Get_increase_sc_temp_user(i));
        hScaler_per_spill[i+32]->AddBinContent(hitItem.Get_ibin_for_spill(), hitItem.Get_increase_sc_temp_main(i));
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

    auto const & tpcCalItem = tpcCalArray->at(0);
    tpc_x = tpcCalItem.Get_tpc_x();

    int64_t wr_dt = (frs_wr - saved_frs_wr) / 1e9; // conv to s

    if (wr_dt < 2 && saved_frs_wr != 0)
    {
        for (int i = 0; i < 6; i++)
        {
            if (tpc_x[i]) tpc_counters[i]++;
        }
    }
    else 
    {
        for (int i = 0; i < 6; i++)
        {
            tpc_rates[i] = tpc_counters[i] / wr_dt;
            tpc_counters[i] = 0;

            if (i == 0) h1_tpc21_rate->SetBinContent(tpc_running_count, tpc_rates[i]);
            else if (i == 1) h1_tpc22_rate->SetBinContent(tpc_running_count, tpc_rates[i]);
            else if (i == 2) h1_tpc23_rate->SetBinContent(tpc_running_count, tpc_rates[i]);
            else if (i == 3) h1_tpc24_rate->SetBinContent(tpc_running_count, tpc_rates[i]);
            else if (i == 4) h1_tpc41_rate->SetBinContent(tpc_running_count, tpc_rates[i]);
            else if (i == 5) h1_tpc42_rate->SetBinContent(tpc_running_count, tpc_rates[i]);

        }

        saved_frs_wr = frs_wr;

        tpc_running_count++;

        if (tpc_running_count == 1800) tpc_running_count = 0;
    }
    

    fNEvents += 1;
}

void FrsOnlineSpectra::FinishEvent()
{

}

void FrsOnlineSpectra::FinishTask()
{   

}

ClassImp(FrsOnlineSpectra)
