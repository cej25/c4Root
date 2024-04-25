// FairRoot
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairTask.h"

// c4
#include "FrsNearlineSpectra.h"
#include "FrsHitData.h"
#include "c4Logger.h"

// ROOT
#include "TClonesArray.h"
#include <vector>
#include "TDirectory.h"

// under(?)load, in case no gates provided
FrsNearlineSpectra::FrsNearlineSpectra() : FrsNearlineSpectra("FrsNearlineSpectra", 1)
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

FrsNearlineSpectra::FrsNearlineSpectra(std::vector<FrsGate*> fg)
    :   FairTask()
    ,   fNEvents()
    ,   header(nullptr)
    ,   hitArray(nullptr)
    ,   multihitArray(nullptr)
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
    FrsGates = fg;

}

FrsNearlineSpectra::FrsNearlineSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents()
    ,   header(nullptr)
    ,   hitArray(nullptr)
    ,   multihitArray(nullptr)
{

}

FrsNearlineSpectra::~FrsNearlineSpectra()
{
    c4LOG(info, "Deleting FrsNearlineSpectra task.");
}

InitStatus FrsNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    // don't look for Ana specifically, we want to test this online

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    hitArray = mgr->InitObjectAs<decltype(hitArray)>("FrsHitData");
    c4LOG_IF(fatal, !hitArray, "Branch FrsHitData not found!");
    multihitArray = mgr->InitObjectAs<decltype(multihitArray)>("FrsMultiHitData");
    c4LOG_IF(fatal, !multihitArray, "Branch FrsMultiHitData not found!");

    dir_frs = (TDirectory*)mgr->GetObject("FRS");
    if (dir_frs == nullptr) 
    {
        LOG(info) << "Creating FRS Directory";
        //dir_frs = new TDirectory("FRS", "FRS", "", 0);
        FairRootManager::Instance()->GetOutFile()->cd();
        dir_frs = gDirectory->mkdir("FRS");
        mgr->Register("FRS", "FRS Directory", dir_frs, false); // allow other tasks to find this
        found_dir_frs = false;
    }
    
    dir_tac_hists = dir_frs->mkdir("TAC");
    dir_mhtdc_hists = dir_frs->mkdir("MHTDC");
    dir_ZvsAoQ_hists = dir_tac_hists->mkdir("ZvsAoQgated");
    dir_Z1vsZ2_hists = dir_tac_hists->mkdir("Z1vsZ2gated");
    dir_x2vsAoQ_hists =  dir_tac_hists->mkdir("x2vsAoQgated");
    dir_x4vsAoQ_hists =  dir_tac_hists->mkdir("x4vsAoQgated");
    dir_dEdegvsZ_hists =  dir_tac_hists->mkdir("dEdegvsZgated");
    dir_x2vsAoQ_Z1vsZ2_hists = dir_tac_hists->mkdir("x2vsAoQ_Z1vsZ2gated");
    dir_x4vsAoQ_Z1vsZ2_hists = dir_tac_hists->mkdir("x4vsAoQ_Z1vsZ2gated");
    dir_ZvsAoQ_hists_mhtdc = dir_mhtdc_hists->mkdir("ZvsAoQgated_mhtdc");
    dir_Z1vsZ2_hists_mhtdc = dir_mhtdc_hists->mkdir("Z1vsZ2gated_mhtdc");
    dir_x2vsAoQ_hists_mhtdc = dir_mhtdc_hists->mkdir("x2vsAoQgated_mhtdc");
    dir_x4vsAoQ_hists_mhtdc = dir_mhtdc_hists->mkdir("x4vsAoQgated_mhtdc");
    dir_dEdegvsZ_hists_mhtdc = dir_mhtdc_hists->mkdir("dEdegvsZgated_mhtdc");
    dir_x2vsAoQ_Z1vsZ2_hists_mhtdc = dir_mhtdc_hists->mkdir("x2vsAoQ_Z1vsZ2gated_mhtdc");
    dir_x4vsAoQ_Z1vsZ2_hists_mhtdc = dir_mhtdc_hists->mkdir("x4vsAoQ_Z1vsZ2gated_mhtdc");    

    dir_tac_hists->cd();
    // init histograms
    //h1_frs_wr = new TH1I("h1_frs_wr", "FRS WR", 1000, 1.71401265e18,1.7140148e18);
    h2_Z1_vs_T = new TH2D("h2_Z1_vs_T", "Z1 vs. Time [mins]", 5000, 0, 10000, 1500, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_AoQ_vs_T = new TH2D("h2_AoQ_vs_T", "A/Q vs. Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ);
    h2_Z_vs_AoQ = new TH2D("h2_Z_vs_AoQ", "Z1 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_AoQ_corr = new TH2D("h2_Z_vs_AoQ_corr", "Z1 vs. A/Q (corr)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_Z2 = new TH2D("h2_Z_vs_Z2", "Z1 vs. Z2", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_AoQ_Zsame = new TH2D("h2_Z_vs_AoQ_Zsame", "Z1 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_x4_vs_AoQ_Zsame = new TH2D("h2_x4_vs_AoQ_Zsame", "x4 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 300, frs_config->fMin_x4, frs_config->fMax_x4); // CEJ: should these lims not be defined somewhere..
    h2_x2_vs_AoQ_Zsame = new TH2D("h2_x2_vs_AoQ_Zsame", "x2 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_Z, frs_config->fMax_Z, 300, frs_config->fMin_x2, frs_config->fMax_x2);   
    h2_x2_vs_AoQ = new TH2D("h2_x2_vs_AoQ", "x2 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2);
    h2_x4_vs_AoQ = new TH2D("h2_x4_vs_AoQ", "x4 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_dEdegoQ_vs_Z = new TH2D("h2_dEdegoQ_vs_Z", "dE in S2 degrader / Q vs. Z1", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ);
    h2_dEdeg_vs_Z = new TH2D("h2_dEdeg_vs_Z", "dE in S2 degrader vs. Z1", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dE, frs_config->fMax_dE);
    h2_a2_vs_AoQ = new TH2D("h2_a2_vs_AoQ", "A/Q vs. Angle (S2)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a2, frs_config->fMax_a2);
    h2_a4_vs_AoQ = new TH2D("h2_a4_vs_AoQ", "A/Q vs. Angle (S4)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a4, frs_config->fMax_a4);
    h2_Z_vs_dE2 = new TH2D("h2_Z_vs_dE2", "Z1 vs. dE in MUSIC2", 400, id->min_z_plot, id->max_z_plot, 250, 0., 4000.);
    h2_x2_vs_x4 = new TH2D("h2_x2_vs_x4", "x2 vs. x4", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_SC41dE_vs_AoQ = new TH2D("h2_SC41dE_vs_AoQ", "A/Q vs. dE in SC41", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000.);
    h2_SC42dE_vs_AoQ = new TH2D("h2_SC42dE_vs_AoQ", "A/Q vs. dE in SC42", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000.);
    h2_SC41dE_vs_Z = new TH2D("h2_SC41dE_vs_Z", "Z (MUSIC 1) vs. dE in SC41", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, 0., 4000.);
    h2_SC42dE_vs_Z = new TH2D("h2_SC42dE_vs_Z", "Z (MUSIC 1) vs. dE in SC42", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, 0., 4000.);
    h2_dE_vs_ToF = new TH2D("h2_dE_vs_ToF", "ToF S2-S4 vs. dE in MUSIC1", 2000, 0., 70000., 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);
    h2_x2_vs_Z = new TH2D("h2_x2_vs_Z", "x2 vs. Z1", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x2, frs_config->fMax_x2);
    h2_x4_vs_Z = new TH2D("h2_x4_vs_Z", "x4 vs. Z1", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x4, frs_config->fMax_x4);  
    h2_dE1_vs_x2 = new TH2D("h2_dE1_vs_x2", "x2 vs. dE in MUSIC1", 200, frs_config->fMin_x2, frs_config->fMax_x2, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);
    h2_dE1_vs_x4 = new TH2D("h2_dE1_vs_x4", "x4 vs. dE in MUSIC1", 200, frs_config->fMin_x4, frs_config->fMax_x4, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);
    h2_x2_vs_a2 = new TH2D("h2_x2_vs_a2", "x2 vs. AngleX (S2)", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_a2, frs_config->fMax_a2);
    h2_y2_vs_b2 = new TH2D("h2_y2_vs_b2", "y2 vs. AngleY (S2)", 200, frs_config->fMin_y2, frs_config->fMax_y2, 200, frs_config->fMin_b2, frs_config->fMax_b2);
    h2_x4_vs_a4 = new TH2D("h2_x4_vs_a4", "x4 vs. AngleX (S4)", 200, frs_config->fMin_x4, frs_config->fMax_x4, 200, frs_config->fMin_a4, frs_config->fMax_a4);
    h2_y4_vs_b4 = new TH2D("h2_y4_vs_b4", "y4 vs. AngleY (S4)", 200, frs_config->fMin_y4, frs_config->fMax_y4, 200, frs_config->fMin_b4, frs_config->fMax_b4);
    h2_Z_vs_Sc21E = new TH2D("h2_Z_vs_Sc21E", "Z1 vs. SQRT(Sc21_L * Sc21_R)", 300, frs_config->fMin_Z, frs_config->fMax_Z, 400, 0., 4000.);
    h1_sci21_tx = new TH1D("h1_sci21_tx", "S2 Position SCI21", 200, frs_config->fMin_x2, frs_config->fMax_x2);

    // ----------- MHTDC --------------
    dir_mhtdc_hists->cd();
    h2_Z1_vs_T_mhtdc = new TH2D("h2_Z1_vs_T_mhtdc", "Z1 (MHTDC) vs. Time [mins]", 1240, 16600, 29000, 1500, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_AoQ_vs_T_mhtdc = new TH2D("h2_AoQ_vs_T_mhtdc", "A/Q (MHTDC) vs. Time [mins]", 1200, 17000, 29000, 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ);
    h2_Z_vs_AoQ_mhtdc = new TH2D("h2_Z_vs_AoQ_mhtdc", "Z1 vs. A/Q (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_AoQ_corr_mhtdc = new TH2D("h2_Z_vs_AoQ_corr_mhtdc", "Z1 vs. A/Q (corr)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_Z2_mhtdc = new TH2D("h2_Z_vs_Z2_mhtdc", "Z1 vs. Z2 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_AoQ_Zsame_mhtdc = new TH2D("h2_Z_vs_AoQ_Zsame_mhtdc", "Z1 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_x4_vs_AoQ_Zsame_mhtdc = new TH2D("h2_x4_vs_AoQ_Zsame_mhtdc", "x4 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 300, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_x2_vs_AoQ_Zsame_mhtdc = new TH2D("h2_x2_vs_AoQ_Zsame_mhtdc", "x2 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 300, frs_config->fMin_x2, frs_config->fMax_x2);
    h2_x2_vs_AoQ_mhtdc = new TH2D("h2_x2_vs_AoQ_mhtdc", "x2 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2);
    h2_x4_vs_AoQ_mhtdc = new TH2D("h2_x4_vs_AoQ_mhtdc", "x4 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_dEdegoQ_vs_Z_mhtdc = new TH2D("h2_dEdegoQ_vs_Z_mhtdc", "dE in S2 degrader / Q vs. Z1", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ);
    h2_dEdeg_vs_Z_mhtdc = new TH2D("h2_dEdeg_vs_Z_mhtdc", "dE in S2 degrader vs. Z1", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dE, frs_config->fMax_dE);
    h2_a2_vs_AoQ_mhtdc = new TH2D("h2_a2_vs_AoQ_mhtdc", "A/Q vs. Angle (S2)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a2, frs_config->fMax_a2);
    h2_a4_vs_AoQ_mhtdc = new TH2D("h2_a4_vs_AoQ_mhtdc", "A/Q vs. Angle (S4)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, -25, 25);
    h2_Z_vs_dE2_mhtdc = new TH2D("h2_Z_vs_dE2_mhtdc", "Z1 vs. dE in MUSIC2", 400, frs_config->fMin_Z, frs_config->fMax_Z, 250, frs_config->fMin_dE_Music2, frs_config->fMax_dE_Music2);
    h2_Z_vs_Sc21E_mhtdc = new TH2D("h2_Z_vs_Sc21E_mhtdc", "Z1 vs. SQRT(Sc21_L * Sc21_R)", 300, frs_config->fMin_Z, frs_config->fMax_Z, 400, 0., 4000.);
    h2_x2_vs_Z_mhtdc = new TH2D("h2_x2_vs_Z_mhtdc", "x2 vs. Z1", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x2, frs_config->fMax_x2);
    h2_x4_vs_Z_mhtdc = new TH2D("h2_x4_vs_Z_mhtdc", "x4 vs. Z1", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_x2_vs_x4_mhtdc = new TH2D("h2_x2_vs_x4_mhtdc", "x2 vs. x4", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_x4, frs_config->fMax_x4);
    h2_SC41dE_vs_AoQ_mhtdc = new TH2D("h2_SC41dE_vs_AoQ_mhtdc", "A/Q vs. dE in SC41", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000.);
    h2_dE_vs_ToF_mhtdc = new TH2D("h2_dE_vs_ToF_mhtdc", "ToF S2-S4 vs. dE in MUSIC1", 2000, 0., 70000., 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);
    h2_dE1_vs_x2_mhtdc = new TH2D("h2_dE1_vs_x2_mhtdc", "x2 vs. dE in MUSIC1", 200, frs_config->fMin_x2, frs_config->fMax_x2, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);
    h2_dE1_vs_x4_mhtdc = new TH2D("h2_dE1_vs_x4_mhtdc", "x4 vs. dE in MUSIC1", 200, frs_config->fMin_x4, frs_config->fMax_x4, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1);

    // ZvsAoQ gates
    if (!FrsGates.empty())
    {   
        h2_Z_vs_AoQ_ZAoQgate.resize(FrsGates.size());
        h2_Z1_vs_Z2_ZAoQgate.resize(FrsGates.size());
        h2_x2_vs_AoQ_ZAoQgate.resize(FrsGates.size());
        h2_x4_vs_AoQ_ZAoQgate.resize(FrsGates.size());
        h2_dEdeg_vs_Z_ZAoQgate.resize(FrsGates.size());
        h2_dedegoQ_vs_Z_ZAoQgate.resize(FrsGates.size());
        h1_a2_ZAoQ_gate.resize(FrsGates.size());
        h1_a4_ZAoQ_gate.resize(FrsGates.size());
        h2_x2_vs_AoQ_ZAoQgate_mhtdc.resize(FrsGates.size());
        h2_x4_vs_AoQ_ZAoQgate_mhtdc.resize(FrsGates.size());
        h2_Z_vs_AoQ_ZAoQgate_mhtdc.resize(FrsGates.size());
        h2_Z1_vs_Z2_ZAoQgate_mhtdc.resize(FrsGates.size());
        h2_dEdeg_vs_Z_ZAoQgate_mhtdc.resize(FrsGates.size());
        h2_dedegoQ_vs_Z_ZAoQgate_mhtdc.resize(FrsGates.size());
        h1_a2_ZAoQ_gate_mhtdc.resize(FrsGates.size());
        h1_a4_ZAoQ_gate_mhtdc.resize(FrsGates.size());

        for (int gate = 0; gate < FrsGates.size(); gate++)
        {
            dir_ZvsAoQ_hists->cd();
            h2_Z_vs_AoQ_ZAoQgate[gate] = new TH2I(Form("h2_Z_vs_AoQ_ZAoQgate%d",gate), Form("Z vs. A/Q - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);
            h2_Z1_vs_Z2_ZAoQgate[gate] = new TH2I(Form("h2_Z1_vs_Z2_ZAoQgate%d", gate), Form("Z1 vs. Z2 - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);
            h2_x2_vs_AoQ_ZAoQgate[gate] = new TH2I(Form("h2_x2_vs_AoQ_ZAoQgate%d", gate), Form("x2 vs. A/Q - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);
            h2_x4_vs_AoQ_ZAoQgate[gate] = new TH2I(Form("h2_x4_vs_AoQ_ZAoQgate%d", gate), Form("x4 vs. A/Q - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);
            h2_dEdeg_vs_Z_ZAoQgate[gate] = new TH2I(Form("h2_dEdeg_vs_Z_ZAoQgate%d", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 50.);
            h2_dedegoQ_vs_Z_ZAoQgate[gate] = new TH2I(Form("h2_dedegoQ_vs_Z_ZAoQgate%d", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 50.);
            h1_a2_ZAoQ_gate[gate] = new TH1I(Form("h1_a2_ZAoQ_gate%d", gate), Form("Angle S2 [mrad] - ZAoQ Gate: %d", gate), 100, -1000, 1000); 
            h1_a4_ZAoQ_gate[gate] = new TH1I(Form("h1_a4_ZAoQ_gate%d", gate), Form("Angle S4 [mrad] - ZAoQ Gate: %d", gate), 100, -1000, 1000);
            
            // ----- MHTDC --------
            dir_ZvsAoQ_hists_mhtdc->cd();
            h2_x2_vs_AoQ_ZAoQgate_mhtdc[gate] = new TH2I(Form("h2_x2_vs_AoQ_ZAoQgate%d_mhtdc", gate), Form("x2 vs. A/Q - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);    
            h2_x4_vs_AoQ_ZAoQgate_mhtdc[gate] = new TH2I(Form("h2_x4_vs_AoQ_ZAoQgate%d_mhtdc", gate), Form("x4 vs. A/Q - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);
            h2_Z_vs_AoQ_ZAoQgate_mhtdc[gate] = new TH2I(Form("h2_Z_vs_AoQ_ZAoQgate%d_mhtdc",gate), Form("Z vs. A/Q - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot); // CEJ: why are we using FRS_HISTO_BIN like this here?
            h2_Z1_vs_Z2_ZAoQgate_mhtdc[gate] = new TH2I(Form("h2_Z1_vs_Z2_ZAoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);            
            h2_dEdeg_vs_Z_ZAoQgate_mhtdc[gate] = new TH2I(Form("h2_dEdeg_vs_Z_ZAoQgate%d_mhtdc", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 50.);            
            h2_dedegoQ_vs_Z_ZAoQgate_mhtdc[gate] = new TH2I(Form("h2_dedegoQ_vs_Z_ZAoQgate%d_mhtdc", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 50.);          
            h1_a2_ZAoQ_gate_mhtdc[gate] = new TH1I(Form("h1_a2_ZAoQ_gate%d_mhtdc", gate), Form("Angle S2 [mrad] - ZAoQ Gate: %d", gate), 100, -1000, 1000);    
            h1_a4_ZAoQ_gate_mhtdc[gate] = new TH1I(Form("h1_a4_ZAoQ_gate%d_mhtdc", gate), Form("Angle S4 [mrad] - ZAoQ Gate: %d", gate), 100, -1000, 1000);
        }

    }

    if (!FrsGates.empty())
    {
        h2_dEdeg_vs_Z_Z1Z2gate.resize(FrsGates.size());
        h2_dEdegoQ_vs_Z_Z1Z2gate.resize(FrsGates.size());
        h2_Z1_vs_Z2_Z1Z2gate.resize(FrsGates.size());
        h1_a2_Z1Z2gate.resize(FrsGates.size());
        h1_a4_Z1Z2gate.resize(FrsGates.size());
        h2_x2_vs_AoQ_Z1Z2gate.resize(FrsGates.size());
        h2_x4_vs_AoQ_Z1Z2gate.resize(FrsGates.size());
        h2_Z_vs_AoQ_Z1Z2gate.resize(FrsGates.size());
        h2_dEdeg_vs_Z_Z1Z2gate_mhtdc.resize(FrsGates.size());
        h2_dEdegoQ_vs_Z_Z1Z2gate_mhtdc.resize(FrsGates.size());
        h2_Z1_vs_Z2_Z1Z2gate_mhtdc.resize(FrsGates.size());
        h1_a2_Z1Z2gate_mhtdc.resize(FrsGates.size());
        h1_a4_Z1Z2gate_mhtdc.resize(FrsGates.size());
        h2_x2_vs_AoQ_Z1Z2gate_mhtdc.resize(FrsGates.size());
        h2_x4_vs_AoQ_Z1Z2gate_mhtdc.resize(FrsGates.size());
        h2_Z_vs_AoQ_Z1Z2gate_mhtdc.resize(FrsGates.size());

        // Z1vsZ2 gates
        for (int gate = 0; gate < FrsGates.size(); gate++)
        {   
            dir_Z1vsZ2_hists->cd();
            h2_dEdeg_vs_Z_Z1Z2gate[gate] = new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2gate%d", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.);            
            h2_dEdegoQ_vs_Z_Z1Z2gate[gate] = new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2gate%d", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.);            
            h2_Z1_vs_Z2_Z1Z2gate[gate] = new TH2I(Form("h2_Z1_vs_Z2_Z1Z2gate%d", gate), Form("Z1 vs. Z2 - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);            
            h1_a2_Z1Z2gate[gate] = new TH1I(Form("h1_a2_Z1Z2gate%d", gate), Form("Angle S2 [mrad] - Z1Z2 Gate: %d", gate), 100, -1000, 1000);            
            h1_a4_Z1Z2gate[gate] = new TH1I(Form("h1_a4_Z1Z2gate%d", gate), Form("Angle S4 [mrad] - Z1Z2 Gate: %d", gate), 100, -1000, 1000);            
            h2_x2_vs_AoQ_Z1Z2gate[gate] = new TH2I(Form("h2_x2_vs_AoQ_Z1Z2gate%d", gate), Form("x2 vs. A/Q - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);            
            h2_x4_vs_AoQ_Z1Z2gate[gate] = new TH2I(Form("h2_x4_vs_AoQ_Z1Z2gate%d", gate), Form("x4 vs. A/Q - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);            
            h2_Z_vs_AoQ_Z1Z2gate[gate] = new TH2I(Form("h2_Z_vs_AoQ_Z1Z2gate%d", gate), Form("Z1 vs. A/Q - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);

            // ------- MHTDC ----------
            dir_Z1vsZ2_hists_mhtdc->cd();
            h2_dEdeg_vs_Z_Z1Z2gate_mhtdc[gate] = new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2gate%d_mhtdc", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.);            
            h2_dEdegoQ_vs_Z_Z1Z2gate_mhtdc[gate] = new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2gate%d_mhtdc", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.);            
            h2_Z1_vs_Z2_Z1Z2gate_mhtdc[gate] = new TH2I(Form("h2_Z1_vs_Z2_Z1Z2gate%d_mhtdc", gate), Form("Z1 vs. Z2 - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);            
            h1_a2_Z1Z2gate_mhtdc[gate] = new TH1I(Form("h1_a2_Z1Z2gate%d_mhtdc", gate), Form("Angle S2 [mrad] - Z1Z2 Gate: %d", gate), 100, -1000, 1000);
            h1_a4_Z1Z2gate_mhtdc[gate] = new TH1I(Form("h1_a4_Z1Z2gate%d_mhtdc", gate), Form("Angle S4 [mrad] - Z1Z2 Gate: %d", gate), 100, -1000, 1000);            
            h2_x2_vs_AoQ_Z1Z2gate_mhtdc[gate] = new TH2I(Form("h2_x2_vs_AoQ_Z1Z2gate%d_mhtdc", gate), Form("x2 vs. A/Q - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);            
            h2_x4_vs_AoQ_Z1Z2gate_mhtdc[gate] = new TH2I(Form("h2_x4_vs_AoQ_Z1Z2gate%d_mhtdc", gate), Form("x4 vs. A/Q - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);            
            h2_Z_vs_AoQ_Z1Z2gate_mhtdc[gate] = new TH2I(Form("h2_Z_vs_AoQ_Z1Z2gate%d_mhtdc", gate), Form("Z1 vs. A/Q - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);
        }
    }

    if (!FrsGates.empty())
    {
        h2_x2_vs_AoQ_x2AoQgate.resize(FrsGates.size());
        h2_Z1_vs_Z2_x2AoQgate.resize(FrsGates.size());
        h2_x2_vs_AoQ_x2AoQgate_mhtdc.resize(FrsGates.size());
        h2_Z1_vs_Z2_x2AoQgate_mhtdc.resize(FrsGates.size());
        h2_x2_vs_AoQ_Z1Z2x2AoQgate.resize(FrsGates.size());
        h2_x4_vs_AoQ_Z1Z2x2AoQgate.resize(FrsGates.size());
        h2_Z_vs_AoQ_Z1Z2x2AoQgate.resize(FrsGates.size());
        h2_dEdeg_vs_Z_Z1Z2x2AoQgate.resize(FrsGates.size());
        h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate.resize(FrsGates.size());
        h1_a2_Z1Z2x2AoQgate.resize(FrsGates.size());
        h1_a4_Z1Z2x2AoQgate.resize(FrsGates.size());
        h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
        h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
        h2_Z_vs_AoQ_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
        h2_Z1_vs_Z2_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
        h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
        h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
        h1_a2_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
        h1_a4_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());

        // x2vsAoQ gates
        for (int gate = 0; gate < FrsGates.size(); gate++)
        {
            dir_x2vsAoQ_hists->cd();
            h2_x2_vs_AoQ_x2AoQgate[gate] = new TH2I(Form("h2_x2_vs_AoQ_x2AoQgate%d", gate), Form("x2 vs. A/Q - x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);
            h2_Z1_vs_Z2_x2AoQgate[gate] = new TH2I(Form("h2_Z1_vs_Z2_x2AoQgate%d", gate), Form("Z1 vs. Z2 - x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);

            // ------ MHTDC --------
            dir_x2vsAoQ_hists_mhtdc->cd();
            h2_x2_vs_AoQ_x2AoQgate_mhtdc[gate] = new TH2I(Form("h2_x2_vs_AoQ_x2AoQgate%d_mhtdc", gate), Form("x2 vs. A/Q - x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);
            h2_Z1_vs_Z2_x2AoQgate_mhtdc[gate] = new TH2I(Form("h2_Z1_vs_Z2_x2AoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);

            // Second gate - Z1 vs Z2
            dir_x2vsAoQ_Z1vsZ2_hists->cd();
            h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate] = new TH2I(Form("h2_x2_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);                
            h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate] = new TH2I(Form("h2_x4_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);                
            h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate] = new TH2I(Form("h2_Z_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("Z1 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);                
            h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate] = new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2x2AoQgate%d", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.);                
            h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate] = new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate%d", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.);               
            h1_a2_Z1Z2x2AoQgate[gate] = new TH1I(Form("h1_a2_Z1Z2x2AoQgate%d", gate), Form("Angle S2 [mrad] - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 100, -1000, 1000);           
            h1_a4_Z1Z2x2AoQgate[gate] = new TH1I(Form("h1_a4_Z1Z2x2AoQgate%d", gate), Form("Angle S4 [mrad] - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 100, -1000, 1000);

            // ----- MHTDC ---------
            dir_x2vsAoQ_Z1vsZ2_hists_mhtdc->cd();
            h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate] = new TH2I(Form("h2_x2_vs_AoQ_Z1Z2x2AoQgate%d_mhtdc", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);                
            h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate] = new TH2I(Form("h2_x4_vs_AoQ_Z1Z2x2AoQgate%d_mhtdc", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);                
            h2_Z_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate] = new TH2I(Form("h2_Z_vs_AoQ_Z1Z2x2AoQgate%d_mhtdc", gate), Form("Z1 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);              
            h2_Z1_vs_Z2_Z1Z2x2AoQgate_mhtdc[gate] = new TH2I(Form("h2_Z1_vs_Z2_Z1Z2x2AoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);                
            h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc[gate] = new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2x2AoQgate%d_mhtdc", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.);                
            h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc[gate] = new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate%d_mhtdc", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.);                
            h1_a2_Z1Z2x2AoQgate_mhtdc[gate] = new TH1I(Form("h1_a2_Z1Z2x2AoQgate%d_mhtdc", gate), Form("Angle S2 [mrad] - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 100, -1000, 1000);                
            h1_a4_Z1Z2x2AoQgate_mhtdc[gate] = new TH1I(Form("h1_a4_Z1Z2x2AoQgate%d_mhtdc", gate), Form("Angle S4 [mrad] - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 100, -1000, 1000);
               
        }
    }
    
    if (!FrsGates.empty())
    {
        h2_x4_vs_AoQ_x4AoQgate.resize(FrsGates.size());
        h2_Z1_vs_Z2_x4AoQgate.resize(FrsGates.size());
        h2_x4_vs_AoQ_x4AoQgate_mhtdc.resize(FrsGates.size());
        h2_Z1_vs_Z2_x4AoQgate_mhtdc.resize(FrsGates.size());
        h2_x2_vs_AoQ_Z1Z2x4AoQgate.resize(FrsGates.size());
        h2_x4_vs_AoQ_Z1Z2x4AoQgate.resize(FrsGates.size());
        h2_Z_vs_AoQ_Z1Z2x4AoQgate.resize(FrsGates.size());
        h2_dEdeg_vs_Z_Z1Z2x4AoQgate.resize(FrsGates.size());
        h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate.resize(FrsGates.size());
        h1_a2_Z1Z2x4AoQgate.resize(FrsGates.size());
        h1_a4_Z1Z2x4AoQgate.resize(FrsGates.size());
        h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
        h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
        h2_Z_vs_AoQ_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
        h2_Z1_vs_Z2_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
        h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
        h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
        h1_a2_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
        h1_a4_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());

        // x4vsAoQ gate
        for (int gate = 0; gate < FrsGates.size(); gate++)
        {
            dir_x4vsAoQ_hists->cd();
            h2_x4_vs_AoQ_x4AoQgate[gate] = new TH2I(Form("h2_x4_vs_AoQ_x4AoQgate%d", gate), Form("x4 vs. A/Q - x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);            
            h2_Z1_vs_Z2_x4AoQgate[gate] = new TH2I(Form("h2_Z1_vs_Z2_x4AoQgate%d", gate), Form("Z1 vs. Z2 - x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);

            // ------ MHTDC --------
            dir_x4vsAoQ_hists_mhtdc->cd();
            h2_x4_vs_AoQ_x4AoQgate_mhtdc[gate] = new TH2I(Form("h2_x4_vs_AoQ_x4AoQgate%d_mhtdc", gate), Form("x4 vs. A/Q - x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);            
            h2_Z1_vs_Z2_x4AoQgate_mhtdc[gate] = new TH2I(Form("h2_Z1_vs_Z2_x4AoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);

            // Second gate - Z1 vs Z2
            dir_x4vsAoQ_Z1vsZ2_hists->cd();
            h2_x2_vs_AoQ_Z1Z2x4AoQgate[gate] = new TH2I(Form("h2_x2_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);               
            h2_x4_vs_AoQ_Z1Z2x4AoQgate[gate] = new TH2I(Form("h2_x4_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);                
            h2_Z_vs_AoQ_Z1Z2x4AoQgate[gate] = new TH2I(Form("h2_Z_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("Z1 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);                
            h2_dEdeg_vs_Z_Z1Z2x4AoQgate[gate] = new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2x4AoQgate%d", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.);                
            h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[gate] = new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate%d", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.);                
            h1_a2_Z1Z2x4AoQgate[gate] = new TH1I(Form("h1_a2_Z1Z2x4AoQgate%d", gate), Form("Angle S2 [mrad] - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 100, -1000, 1000);                
            h1_a4_Z1Z2x4AoQgate[gate] = new TH1I(Form("h1_a4_Z1Z2x4AoQgate%d", gate), Form("Angle S4 [mrad] - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 100, -1000, 1000);

            // -------- MHTDC -----------
            dir_x4vsAoQ_Z1vsZ2_hists_mhtdc->cd();
            h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate] = new TH2I(Form("h2_x2_vs_AoQ_Z1Z2x4AoQgate%d_mhtdc", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);                
            h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate] = new TH2I(Form("h2_x4_vs_AoQ_Z1Z2x4AoQgate%d_mhtdc", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);               
            h2_Z1_vs_Z2_Z1Z2x4AoQgate_mhtdc[gate] = new TH2I(Form("h2_Z1_vs_Z2_Z1Z2x4AoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);
            h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc[gate] = new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2x4AoQgate%d_mhtdc", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.);                
            h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc[gate] = new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate%d_mhtdc", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.);                
            h1_a2_Z1Z2x4AoQgate_mhtdc[gate] = new TH1I(Form("h1_a2_Z1Z2x4AoQgate%d_mhtdc", gate), Form("Angle S2 [mrad] - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 100, -1000, 1000);                
            h1_a4_Z1Z2x4AoQgate_mhtdc[gate] = new TH1I(Form("h1_a4_Z1Z2x4AoQgate%d_mhtdc", gate), Form("Angle S4 [mrad] - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 100, -1000, 1000);
        }
    }
    

    if (!FrsGates.empty())
    {
        h2_Z_vs_AoQ_dEdegZgate.resize(FrsGates.size());
        h2_Z1_vs_Z2_dEdegZgate.resize(FrsGates.size());
        h2_x2_vs_AoQ_dEdegZgate.resize(FrsGates.size());
        h2_x4_vs_AoQ_dEdegZgate.resize(FrsGates.size());
        h1_a2_dEdegZgate.resize(FrsGates.size());
        h1_a4_dEdegZgate.resize(FrsGates.size());
        h2_Z_vs_AoQ_Zsame_dEdegZgate.resize(FrsGates.size());
        h2_Z_vs_dEdeg_dEdegZgate_mhtdc.resize(FrsGates.size());
        h2_Z_vs_AoQ_dEdegZgate_mhtdc.resize(FrsGates.size());
        h2_Z1_vs_Z2_dEdegZgate_mhtdc.resize(FrsGates.size());
        h2_x2_vs_AoQ_dEdegZgate_mhtdc.resize(FrsGates.size());
        h2_x4_vs_AoQ_dEdegZgate_mhtdc.resize(FrsGates.size());
        h1_a2_dEdegZgate_mhtdc.resize(FrsGates.size());
        h1_a4_dEdegZgate_mhtdc.resize(FrsGates.size());
        h2_Z_vs_AoQ_Zsame_dEdegZgate_mhtdc.resize(FrsGates.size());
        
        // dEdegZ gates
        for (int gate = 0; gate < FrsGates.size(); gate++) 
        {
            dir_dEdegvsZ_hists->cd();
            h2_Z_vs_AoQ_dEdegZgate[gate] = new TH2I(Form("h2_Z_vs_AoQ_dEdegZgate%d", gate), Form("Z1 vs. A/Q - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);            
            h2_Z1_vs_Z2_dEdegZgate[gate] = new TH2I(Form("h2_Z1_vs_Z2_dEdegZgate%d", gate), Form("Z1 vs. Z2 - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);            
            h2_x2_vs_AoQ_dEdegZgate[gate] = new TH2I(Form("h2_x2_vs_AoQ_dEdegZgate%d", gate), Form("x2 vs. A/Q - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);            
            h2_x4_vs_AoQ_dEdegZgate[gate] = new TH2I(Form("h2_x4_vs_AoQ_dEdegZgate%d", gate), Form("x4 vs. A/Q - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);            
            h1_a2_dEdegZgate[gate] = new TH1I(Form("h1_a2_dEdegZgate%d", gate), Form("Angle S2 [mrad] - dEdegZ Gate: %d", gate), 100, -1000, 1000);            
            h1_a4_dEdegZgate[gate] = new TH1I(Form("h1_a4_dEdegZgate%d", gate), Form("Angle S4 [mrad] - dEdegZ Gate: %d", gate), 100, -1000, 1000);       
            h2_Z_vs_AoQ_Zsame_dEdegZgate[gate] = new TH2I(Form("h2_Z_vs_AoQ_Zsame_dEdegZgate%d", gate), Form("Z vs. A/Q [ABS(Z1 - Z2) < 0.4] - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);

            // ------- MHTDC -----------------
            dir_dEdegvsZ_hists_mhtdc->cd();
            h2_Z_vs_dEdeg_dEdegZgate_mhtdc[gate] = new TH2I(Form("h2_Z_vs_dEdeg_dEdegZgate%d_mhtdc", gate), Form("Z1 vs. dE in S2 degrader - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.);            
            h2_Z_vs_AoQ_dEdegZgate_mhtdc[gate] = new TH2I(Form("h2_Z_vs_AoQ_dEdegZgate%d_mhtdc", gate), Form("Z1 vs. A/Q - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);       
            h2_Z1_vs_Z2_dEdegZgate_mhtdc[gate] = new TH2I(Form("h2_Z1_vs_Z2_dEdegZgate%d_mhtdc", gate), Form("Z1 vs. Z2 - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);            
            h2_x2_vs_AoQ_dEdegZgate_mhtdc[gate] = new TH2I(Form("h2_x2_vs_AoQ_dEdegZgate%d_mhtdc", gate), Form("x2 vs. A/Q - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);     
            h2_x4_vs_AoQ_dEdegZgate_mhtdc[gate] = new TH2I(Form("h2_x4_vs_AoQ_dEdegZgate%d_mhtdc", gate), Form("x4 vs. A/Q - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.);   
            h1_a2_dEdegZgate_mhtdc[gate] = new TH1I(Form("h1_a2_dEdegZgate%d_mhtdc", gate), Form("Angle S2 [mrad] - dEdegZ Gate: %d", gate), 100, -1000, 1000);
            h1_a4_dEdegZgate_mhtdc[gate] = new TH1I(Form("h1_a4_dEdegZgate%d_mhtdc", gate), Form("Angle S4 [mrad] - dEdegZ Gate: %d", gate), 100, -1000, 1000);
            h2_Z_vs_AoQ_Zsame_dEdegZgate_mhtdc[gate] = new TH2I(Form("h2_Z_vs_AoQ_Zsame_dEdegZgate%d_mhtdc", gate), Form("Z vs. A/Q [ABS(Z1 - Z2) < 0.4] - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot);
        }
    }

    dir_frs->cd();
    //gDirectory = tmp;

    return kSUCCESS;

}

void FrsNearlineSpectra::Exec(Option_t* option)
{   
    if (hitArray->size() <= 0) return;

    Long64_t FRS_time_mins = 0;
    auto const & hitItem = hitArray->at(0); // should only be size=1! check

    //h1_frs_wr->Fill(hitItem.Get_wr_t());

    if(hitItem.Get_wr_t() > 0) FRS_time_mins = (hitItem.Get_wr_t() - 1713704823000000000)/ 60E9;

    /* --------  TAC and PID gates ----------- */
    if (hitItem.Get_ID_z() > 0 && FRS_time_mins > 0) h2_Z1_vs_T->Fill(FRS_time_mins, hitItem.Get_ID_z());

    if (hitItem.Get_ID_AoQ() > 0 && FRS_time_mins > 0) h2_AoQ_vs_T->Fill(FRS_time_mins, hitItem.Get_ID_AoQ());

    if (hitItem.Get_ID_AoQ() > 0 && hitItem.Get_ID_z() > 0) h2_Z_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
    if (hitItem.Get_ID_AoQ_corr() > 0 && hitItem.Get_ID_z() > 0) h2_Z_vs_AoQ_corr->Fill(hitItem.Get_ID_AoQ_corr(), hitItem.Get_ID_z());

    if (hitItem.Get_ID_z() > 0 && hitItem.Get_ID_z2() > 0) h2_Z_vs_Z2->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_z2());
    if (TMath::Abs(hitItem.Get_ID_z() - hitItem.Get_ID_z2()) < 0.4) // CEJ: should we .config this condition?
    {
        h2_Z_vs_AoQ_Zsame->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
        h2_x4_vs_AoQ_Zsame->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
        h2_x2_vs_AoQ_Zsame->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
    }

    // CEJ: "analysis" taken from Go4 (DESPEC/FRS)
    // is stupid, we already demand the x2 condition to fill the hit.
    // this should be reconidered
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
    if (hitItem.Get_ID_AoQ() != 0 && hitItem.Get_sci_e(3) != 0) h2_SC42dE_vs_AoQ->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_sci_e(3));
    if (hitItem.Get_ID_z() != 0 && hitItem.Get_sci_e(2) != 0) h2_SC41dE_vs_Z->Fill(hitItem.Get_ID_z(), hitItem.Get_sci_e(2));
    if (hitItem.Get_ID_z() != 0 && hitItem.Get_sci_e(3) != 0) h2_SC42dE_vs_Z->Fill(hitItem.Get_ID_z(), hitItem.Get_sci_e(3));

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
    if (hitItem.Get_ID_z() != 0 && hitItem.Get_sci_l(0) != 0 && hitItem.Get_sci_r(0)  != 0) h2_Z_vs_Sc21E->Fill(hitItem.Get_ID_z(), sqrt(hitItem.Get_sci_l(0) * hitItem.Get_sci_r(0)));

    if (hitItem.Get_sci_x(0)  != 0) h1_sci21_tx->Fill(hitItem.Get_sci_x(0) );

    if (!FrsGates.empty())
    {
        for (int gate = 0; gate < FrsGates.size(); gate++)
        {   
            if (FrsGates[gate]->Passed_ZvsAoQ(hitItem.Get_ID_z(), hitItem.Get_ID_AoQ()))
            {
                h2_Z_vs_AoQ_ZAoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
                h2_Z1_vs_Z2_ZAoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_z2());
                h2_x2_vs_AoQ_ZAoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
                h2_x4_vs_AoQ_ZAoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
                h2_dEdeg_vs_Z_ZAoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdeg());
                h2_dedegoQ_vs_Z_ZAoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdegoQ());
                h1_a2_ZAoQ_gate[gate]->Fill(hitItem.Get_ID_a2());
                h1_a4_ZAoQ_gate[gate]->Fill(hitItem.Get_ID_a4());
            }
        
            if (FrsGates[gate]->Passed_ZvsZ2(hitItem.Get_ID_z(), hitItem.Get_ID_z2()))
            {
                h2_dEdeg_vs_Z_Z1Z2gate[gate]->Fill(hitItem.Get_ID_z(),hitItem.Get_ID_dEdeg());
                h2_dEdegoQ_vs_Z_Z1Z2gate[gate]->Fill(hitItem.Get_ID_z(),hitItem.Get_ID_dEdegoQ());
                h2_Z1_vs_Z2_Z1Z2gate[gate]->Fill(hitItem.Get_ID_z(),hitItem.Get_ID_z2());
                h1_a2_Z1Z2gate[gate]->Fill(hitItem.Get_ID_a2());
                h1_a4_Z1Z2gate[gate]->Fill(hitItem.Get_ID_a4());

                if(hitItem.Get_ID_AoQ() > 1 && hitItem.Get_ID_AoQ() < 3 && hitItem.Get_ID_x2() > -100 && hitItem.Get_ID_x2() < 100) h2_x2_vs_AoQ_Z1Z2gate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
                if(hitItem.Get_ID_AoQ() > 1 && hitItem.Get_ID_AoQ() < 3 && hitItem.Get_ID_x4() > -100 && hitItem.Get_ID_x4() < 100) h2_x4_vs_AoQ_Z1Z2gate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
                if(hitItem.Get_ID_AoQ() > 1 && hitItem.Get_ID_AoQ() < 3) h2_Z_vs_AoQ_Z1Z2gate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
            }
            
            if (FrsGates[gate]->Passed_x2vsAoQ(hitItem.Get_ID_x2(), hitItem.Get_ID_AoQ()))
            {
                h2_x2_vs_AoQ_x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
                h2_Z1_vs_Z2_x2AoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_z2());
                
                if (FrsGates[gate]->Passed_ZvsZ2(hitItem.Get_ID_z(), hitItem.Get_ID_z2()))
                {
                    h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
                    h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
                    h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
                    h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdeg());
                    h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_dEdegoQ());
                    h1_a2_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_a2());
                    h1_a4_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_a4()); 
                }
            }

            if (FrsGates[gate]->Passed_x4vsAoQ(hitItem.Get_ID_x4(), hitItem.Get_ID_AoQ()))
            {
                h2_x4_vs_AoQ_x4AoQgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
                h2_Z1_vs_Z2_x4AoQgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_z2());
                
                if (FrsGates[gate]->Passed_ZvsZ2(hitItem.Get_ID_z(), hitItem.Get_ID_z2()))
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
                    
            if (FrsGates[gate]->Passed_dEdegvsZ(hitItem.Get_ID_z(), hitItem.Get_ID_dEdeg()))
            {
                h2_Z_vs_AoQ_dEdegZgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
                h2_Z1_vs_Z2_dEdegZgate[gate]->Fill(hitItem.Get_ID_z(), hitItem.Get_ID_z2());
                h2_x2_vs_AoQ_dEdegZgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x2());
                h2_x4_vs_AoQ_dEdegZgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_x4());
                h1_a2_dEdegZgate[gate]->Fill(hitItem.Get_ID_a2());
                h1_a4_dEdegZgate[gate]->Fill(hitItem.Get_ID_a4());
            
                if(fabs(hitItem.Get_ID_z2() - hitItem.Get_ID_z()) < 0.4) h2_Z_vs_AoQ_Zsame_dEdegZgate[gate]->Fill(hitItem.Get_ID_AoQ(), hitItem.Get_ID_z());
            }
        }
    }
    
    for (auto const & multihitItem : *multihitArray)
    {    
        // Z1 vs Time
        if (multihitItem.Get_ID_z_mhtdc() > 0 && FRS_time_mins > 0) h2_Z1_vs_T_mhtdc->Fill(FRS_time_mins, multihitItem.Get_ID_z_mhtdc());
        // AoQ vs Time
        if (multihitItem.Get_ID_AoQ_mhtdc() > 0 && FRS_time_mins > 0) h2_AoQ_vs_T_mhtdc->Fill(FRS_time_mins, multihitItem.Get_ID_AoQ_mhtdc());
        // AoQ vs Z
        if(multihitItem.Get_ID_AoQ_mhtdc() > 0 && multihitItem.Get_ID_z_mhtdc() > 0) h2_Z_vs_AoQ_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), multihitItem.Get_ID_z_mhtdc());
        if(multihitItem.Get_ID_AoQ_corr_mhtdc() > 0 && multihitItem.Get_ID_z_mhtdc() > 0) h2_Z_vs_AoQ_corr_mhtdc->Fill(multihitItem.Get_ID_AoQ_corr_mhtdc(), multihitItem.Get_ID_z_mhtdc());
    
        //Z1 Z2 
        if(multihitItem.Get_ID_z_mhtdc() > 0 && multihitItem.Get_ID_z2_mhtdc() > 0) h2_Z_vs_Z2_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_z2_mhtdc());
    
        if(TMath::Abs(multihitItem.Get_ID_z_mhtdc() - multihitItem.Get_ID_z2_mhtdc()) < 0.4)
        {
            h2_Z_vs_AoQ_Zsame_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), multihitItem.Get_ID_z_mhtdc());
            h2_x4_vs_AoQ_Zsame_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x4());
            h2_x2_vs_AoQ_Zsame_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x2());
        }
 
        // AoQ vs X2
        if(multihitItem.Get_ID_AoQ_mhtdc() > 0 && hitItem.Get_ID_x2() > -100 && hitItem.Get_ID_x2() < 100)  h2_x2_vs_AoQ_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x2());
    
        if(multihitItem.Get_ID_AoQ_mhtdc() > 0 && hitItem.Get_ID_x4() > -100 && hitItem.Get_ID_x4() < 100)  h2_x4_vs_AoQ_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x4());
        
        // Charge states
        // CEJ: dEdeg mhtdc is not used in the check, but it is filled. Why??
        if(multihitItem.Get_ID_z_mhtdc() > 0 && multihitItem.Get_ID_dEdegoQ_mhtdc() != 0) h2_dEdegoQ_vs_Z_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_dEdegoQ_mhtdc());
        if(multihitItem.Get_ID_z_mhtdc() > 0 && multihitItem.Get_ID_dEdeg_mhtdc() != 0) h2_dEdeg_vs_Z_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_dEdeg_mhtdc());
    
        // Angles vs AoQ 
        if(multihitItem.Get_ID_AoQ_mhtdc() != 0 && hitItem.Get_ID_a2() != 0) h2_a2_vs_AoQ_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_a2());
        if(multihitItem.Get_ID_AoQ_mhtdc() != 0 && hitItem.Get_ID_a4() != 0) h2_a4_vs_AoQ_mhtdc->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_a4());
    
        if(multihitItem.Get_ID_z_mhtdc() != 0 && hitItem.Get_music_dE(1)  != 0) h2_Z_vs_dE2_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), hitItem.Get_music_dE(1));
        
        if(multihitItem.Get_ID_z_mhtdc() != 0 && hitItem.Get_sci_l(0) != 0 && hitItem.Get_sci_r(0) != 0) h2_Z_vs_Sc21E_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), sqrt(hitItem.Get_sci_l(0) * hitItem.Get_sci_r(0)));
    
        // if > 0 conditions necessary
        h2_x2_vs_Z_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), hitItem.Get_ID_x2());
        
        h2_x4_vs_Z_mhtdc->Fill(multihitItem.Get_ID_z_mhtdc(), hitItem.Get_ID_x4());

        // MHTDC PID Gates
        // Z vs AoQ
        if (!FrsGates.empty())
        {
            for (int gate = 0; gate < FrsGates.size(); gate++)
            { 
                if (FrsGates[gate]->Passed_ZvsAoQ(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_AoQ_mhtdc()))
                {
                    // CEJ: this will change based on final hit?
                    h2_x2_vs_AoQ_ZAoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x2());
                    h2_x4_vs_AoQ_ZAoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x4());
                    h2_Z_vs_AoQ_ZAoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), multihitItem.Get_ID_z_mhtdc());
                    h2_Z1_vs_Z2_ZAoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_z2_mhtdc());
                    h2_dEdeg_vs_Z_ZAoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_dEdeg_mhtdc());
                    h2_dedegoQ_vs_Z_ZAoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_dEdegoQ_mhtdc());
                    h1_a2_ZAoQ_gate_mhtdc[gate]->Fill(hitItem.Get_ID_a2());
                    h1_a4_ZAoQ_gate_mhtdc[gate]->Fill(hitItem.Get_ID_a4());
                }
                    
                if (FrsGates[gate]->Passed_ZvsZ2(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_z2_mhtdc()))
                {
                    h2_dEdeg_vs_Z_Z1Z2gate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_dEdeg_mhtdc());
                    h2_dEdegoQ_vs_Z_Z1Z2gate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_dEdegoQ_mhtdc());
                    h2_Z1_vs_Z2_Z1Z2gate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_z2_mhtdc());
                    if(hitItem.Get_ID_a2() != 0) h1_a2_Z1Z2gate_mhtdc[gate]->Fill(hitItem.Get_ID_a2());
                    if(hitItem.Get_ID_a4() != 0) h1_a4_Z1Z2gate_mhtdc[gate]->Fill(hitItem.Get_ID_a4());
                
                    // X2 AoQ gated on Z1 Z2
                    if(hitItem.Get_ID_x2() > -100 && hitItem.Get_ID_x2() < 100)
                    {
                        h2_x2_vs_AoQ_Z1Z2gate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x2());
                    }
                        
                    if(hitItem.Get_ID_x4() > -100 && hitItem.Get_ID_x4() < 100)
                    {
                        h2_x4_vs_AoQ_Z1Z2gate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x4());
                        
                        // Z1 AoQ gated on Z1 Z2
                        if(multihitItem.Get_ID_AoQ_mhtdc() != 0 && multihitItem.Get_ID_z_mhtdc() != 0) h2_Z_vs_AoQ_Z1Z2gate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), multihitItem.Get_ID_z_mhtdc());
                        
                    }
                }
                    
                if (FrsGates[gate]->Passed_x2vsAoQ(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x2()))
                {
                    h2_x2_vs_AoQ_x2AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x2());
                    h2_Z1_vs_Z2_x2AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_z2_mhtdc());
                    
                    if (FrsGates[gate]->Passed_ZvsZ2(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_z2_mhtdc()))
                    {      
                        h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x2());
                        h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x4());
                        h2_Z1_vs_Z2_Z1Z2x2AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_z2_mhtdc());
                        h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_dEdeg_mhtdc());
                        h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_dEdegoQ_mhtdc());
                        h1_a2_Z1Z2x2AoQgate_mhtdc[gate]->Fill(hitItem.Get_ID_a2());
                        h1_a4_Z1Z2x2AoQgate_mhtdc[gate]->Fill(hitItem.Get_ID_a4());
                    }
                }
                        
                if (FrsGates[gate]->Passed_x4vsAoQ(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x4()))
                {
                    h2_x4_vs_AoQ_x4AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x4());
                    h2_Z1_vs_Z2_x4AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_z2_mhtdc());
                    
                    if (FrsGates[gate]->Passed_ZvsZ2(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_z2_mhtdc()))
                    {      
                        h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x2());
                        h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x4());
                        h2_Z1_vs_Z2_Z1Z2x4AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_z2_mhtdc());
                        h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_dEdeg_mhtdc());
                        h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_dEdegoQ_mhtdc());
                        h1_a2_Z1Z2x4AoQgate_mhtdc[gate]->Fill(hitItem.Get_ID_a2());
                        h1_a4_Z1Z2x4AoQgate_mhtdc[gate]->Fill(hitItem.Get_ID_a4());
                        
                    }
                }
                        
                if (FrsGates[gate]->Passed_dEdegvsZ(multihitItem.Get_ID_z_mhtdc(), hitItem.Get_ID_dEdeg()))
                {
                    
                    h2_Z_vs_dEdeg_dEdegZgate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_dEdeg_mhtdc());
                    h2_Z_vs_AoQ_dEdegZgate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), multihitItem.Get_ID_z_mhtdc());
                    h2_Z1_vs_Z2_dEdegZgate_mhtdc[gate]->Fill(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_z_mhtdc());
                    h2_x2_vs_AoQ_dEdegZgate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x2());
                    h2_x4_vs_AoQ_dEdegZgate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), hitItem.Get_ID_x4());
                    h1_a2_dEdegZgate_mhtdc[gate]->Fill(hitItem.Get_ID_a2());
                    h1_a4_dEdegZgate_mhtdc[gate]->Fill(hitItem.Get_ID_a4());
            
                    if (fabs(multihitItem.Get_ID_z2_mhtdc() - multihitItem.Get_ID_z_mhtdc()) < 0.4) h2_Z_vs_AoQ_Zsame_dEdegZgate_mhtdc[gate]->Fill(multihitItem.Get_ID_AoQ_mhtdc(), multihitItem.Get_ID_z_mhtdc());
                }
            }
        }
    } // multihitArray
}


void FrsNearlineSpectra::FinishEvent()
{
    
}

void FrsNearlineSpectra::FinishTask()
{
    if (found_dir_frs == false)
    {
        TDirectory* tmp = gDirectory;
        FairRootManager::Instance()->GetOutFile()->cd();
        dir_frs->Write();
        gDirectory = tmp;
        c4LOG(info, "Written FRS analysis histograms to file.");
    }
}

ClassImp(FrsNearlineSpectra)
