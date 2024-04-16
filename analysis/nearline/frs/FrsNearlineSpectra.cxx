// FairRoot
#include "FairRootManager.h"
#include "FairRunAna.h"
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
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
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

    // Set gates
    /*
    for (auto & Gate : fFrsGates)
    {
        if (Gate->Type == "ZAoQ")
        {
            cutID_Z_AoQ = Gate->Gates;
        }
        else if (Gate->Type == "Z1Z2")
        {
            cutID_Z_Z2 = Gate->Gates;
        }
        else if (Gate->Type == "x2AoQ")
        {
            cutID_x2AoQ = Gate->Gates;
        }
        else if (Gate->Type == "x4AoQ")
        {
            cutID_x4AoQ = Gate->Gates;
        }
        else if (Gate->Type == "dEdegZ")
        {
            cutID_dEdegZ = Gate->Gates;
        }
    }
    */

}

FrsNearlineSpectra::FrsNearlineSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents()
    ,   header(nullptr)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
{

}

FrsNearlineSpectra::~FrsNearlineSpectra()
{
    c4LOG(info, "Deleting FrsNearlineSpectra task.");
    if (fFrsHitArray) delete fFrsHitArray;
}

InitStatus FrsNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();
    
    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    fFrsHitArray = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fFrsHitArray, "FrsHitData branch not found!");

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_frs = gDirectory->mkdir("FRS");
    gDirectory->cd("FRS");
    
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

    // init histograms
    dir_tac_hists->cd();
    h2_Z1_vs_T = new TH2D("h2_Z1_vs_T", "Z1 vs. Time [mins]", 1240, 16600, 29000, 1500, id->min_z_plot, id->max_z_plot);
    h2_AoQ_vs_T = new TH2D("h2_AoQ_vs_T", "A/Q vs. Time [mins]", 1200, 17000, 29000, 1500, id->min_aoq_plot, 3.0);
    h2_Z_vs_AoQ = new TH2D("h2_Z_vs_AoQ", "Z1 vs. A/Q", 1500, id->min_aoq_plot, 3.0, 1000, id->min_z_plot, id->max_z_plot);
    h2_Z_vs_AoQ_corr = new TH2D("h2_Z_vs_AoQ_corr", "Z1 vs. A/Q (corr)", 1500, id->min_aoq_plot, 3.0, 1000, id->min_z_plot, id->max_z_plot);
    h2_Z_vs_Z2 = new TH2D("h2_Z_vs_Z2", "Z1 vs. Z2", 1000, id->min_z_plot, id->max_z_plot, 400, id->min_z_plot, id->max_z_plot);
    h2_Z_vs_AoQ_Zsame = new TH2D("h2_Z_vs_AoQ_Zsame", "Z1 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, id->min_aoq_plot, 3.0, 1000, id->min_z_plot, id->max_z_plot);
    h2_x4_vs_AoQ_Zsame = new TH2D("h2_x4_vs_AoQ_Zsame", "x4 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, id->min_aoq_plot, 3.0, 300, -150., 100.); // CEJ: should these lims not be defined somewhere..
    h2_x2_vs_AoQ_Zsame = new TH2D("h2_x2_vs_AoQ_Zsame", "x4 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, id->min_aoq_plot, 3.0, 300, -150., 100.);   
    h2_x2_vs_AoQ = new TH2D("h2_x2_vs_AoQ", "x2 vs. A/Q", 1500, id->min_aoq_plot, 3.0, 200, -100., 100.);
    h2_x4_vs_AoQ = new TH2D("h2_x4_vs_AoQ", "x4 vs. A/Q", 1500, id->min_aoq_plot, 3.0, 200, -100., 100.);
    h2_dEdegoQ_vs_Z = new TH2D("h2_dEdegoQ_vs_Z", "dE in S2 degrader / Q vs. Z1", 1000, id->min_z_plot, id->max_z_plot, 1000, 0.1, 0.8);
    h2_dEdeg_vs_Z = new TH2D("h2_dEdeg_vs_Z", "dE in S2 degrader vs. Z1", 1000, id->min_z_plot, id->max_z_plot, 1000, 10, 100);
    h2_a2_vs_AoQ = new TH2D("h2_a2_vs_AoQ", "A/Q vs. Angle (S2)", 500, id->min_aoq_plot, 3.0, 500, -25, 25);
    h2_a4_vs_AoQ = new TH2D("h2_a4_vs_AoQ", "A/Q vs. Angle (S4)", 500, id->min_aoq_plot, 3.0, 500, -25, 25);
    h2_Z_vs_dE2 = new TH2D("h2_Z_vs_dE2", "Z1 vs. dE in MUSIC2", 400, id->min_z_plot, id->max_z_plot, 250, 0., 4000.);
    h2_x2_vs_x4 = new TH2D("h2_x2_vs_x4", "x2 vs. x4", 200, -100, 100, 200, -100, 100);
    h2_SC41dE_vs_AoQ = new TH2D("h2_SC41dE_vs_AoQ", "A/Q vs. dE in SC41", 1000, 1.2, 3.0, 1000, 0., 4000.); // CEJ: why not min/max aoq?
    h2_dE_vs_ToF = new TH2D("h2_dE_vs_ToF", "ToF S2-S4 vs. dE in MUSIC1", 2000, 0., 70000., 400, 0, 4000);
    h2_x2_vs_Z = new TH2D("h2_x2_vs_Z", "x2 vs. Z1", 400, id->min_z_plot, id->max_z_plot, 200, -100., 100.);
    h2_x4_vs_Z = new TH2D("h2_x4_vs_Z", "x4 vs. Z1", 400, id->min_z_plot, id->max_z_plot, 200, -100., 100.);  
    h2_dE1_vs_x2 = new TH2D("h2_dE1_vs_x2", "x2 vs. dE in MUSIC1", 200, -100., 100., 400, 0., 4000.);
    h2_dE1_vs_x4 = new TH2D("h2_dE1_vs_x4", "x4 vs. dE in MUSIC1", 200, -100., 100., 400, 0., 4000.);
    h2_x2_vs_a2 = new TH2D("h2_x2_vs_a2", "x2 vs. AngleX (S2)", 200, -100., 100., 200, -100., 100.);
    h2_y2_vs_b2 = new TH2D("h2_y2_vs_b2", "y2 vs. AngleY (S2)", 200, -100., 100., 200, -100., 100.);
    h2_x4_vs_a4 = new TH2D("h2_x4_vs_a4", "x4 vs. AngleX (S4)", 200, -100., 100., 200, -100., 100.);
    h2_y4_vs_b4 = new TH2D("h2_y4_vs_b4", "y4 vs. AngleY (S4)", 200, -100., 100., 200, -100., 100.);
    h2_Z_vs_Sc21E = new TH2D("h2_Z_vs_Sc21E", "Z1 vs. SQRT(Sc21_L * Sc21_R)", 300, 60, 100, 400, 0., 4000.); // CEJ: why are Z limits so low?

    // ----------- MHTDC --------------
    dir_mhtdc_hists->cd();
    h2_Z1_vs_T_mhtdc = new TH2D("h2_Z1_vs_T_mhtdc", "Z1 (MHTDC) vs. Time [mins]", 1240, 16600, 29000, 1500, id->min_z_plot, id->max_z_plot);
    h2_AoQ_vs_T_mhtdc = new TH2D("h2_AoQ_vs_T_mhtdc", "A/Q (MHTDC) vs. Time [mins]", 1200, 17000, 29000, 1500, id->min_aoq_plot, 3.0);
    h2_Z_vs_AoQ_mhtdc = new TH2D("h2_Z_vs_AoQ_mhtdc", "Z1 vs. A/Q (MHTDC)", 1500, id->min_aoq_plot, 3.0, 1000, id->min_z_plot, id->max_z_plot);
    h2_Z_vs_AoQ_corr_mhtdc = new TH2D("h2_Z_vs_AoQ_corr_mhtdc", "Z1 vs. A/Q (corr)", 1500, id->min_aoq_plot, 3.0, 1000, id->min_z_plot, id->max_z_plot);
    h2_Z_vs_Z2_mhtdc = new TH2D("h2_Z_vs_Z2_mhtdc", "Z1 vs. Z2 (MHTDC)", 1000, id->min_z_plot, id->max_z_plot, 400, id->min_z_plot, id->max_z_plot);
    h2_Z_vs_AoQ_Zsame_mhtdc = new TH2D("h2_Z_vs_AoQ_Zsame_mhtdc", "Z1 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, id->min_aoq_plot, 3.0, 1000, id->min_z_plot, id->max_z_plot);
    h2_x4_vs_AoQ_Zsame_mhtdc = new TH2D("h2_x4_vs_AoQ_Zsame_mhtdc", "x4 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, id->min_aoq_plot, 3.0, 300, -150., 100.); // CEJ: should these lims not be defined somewhere..
    h2_x2_vs_AoQ_Zsame_mhtdc = new TH2D("h2_x2_vs_AoQ_Zsame_mhtdc", "x4 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, id->min_aoq_plot, 3.0, 300, -150., 100.);
    h2_x2_vs_AoQ_mhtdc = new TH2D("h2_x2_vs_AoQ_mhtdc", "x2 vs. A/Q", 1500, id->min_aoq_plot, 3.0, 200, -100., 100.);
    h2_x4_vs_AoQ_mhtdc = new TH2D("h2_x4_vs_AoQ_mhtdc", "x4 vs. A/Q", 1500, id->min_aoq_plot, 3.0, 200, -100., 100.);
    h2_dEdegoQ_vs_Z_mhtdc = new TH2D("h2_dEdegoQ_vs_Z_mhtdc", "dE in S2 degrader / Q vs. Z1", 1000, id->min_z_plot, id->max_z_plot, 1000, 0.1, 0.8);
    h2_dEdeg_vs_Z_mhtdc = new TH2D("h2_dEdeg_vs_Z_mhtdc", "dE in S2 degrader vs. Z1", 1000, id->min_z_plot, id->max_z_plot, 1000, 10, 100);
    h2_a2_vs_AoQ_mhtdc = new TH2D("h2_a2_vs_AoQ_mhtdc", "A/Q vs. Angle (S2)", 500, id->min_aoq_plot, 3.0, 500, -25, 25);
    h2_a4_vs_AoQ_mhtdc = new TH2D("h2_a4_vs_AoQ_mhtdc", "A/Q vs. Angle (S4)", 500, id->min_aoq_plot, 3.0, 500, -25, 25);
    h2_Z_vs_dE2_mhtdc = new TH2D("h2_Z_vs_dE2_mhtdc", "Z1 vs. dE in MUSIC2", 400, id->min_z_plot, id->max_z_plot, 250, 0., 4000.);
    h2_Z_vs_Sc21E_mhtdc = new TH2D("h2_Z_vs_Sc21E_mhtdc", "Z1 vs. SQRT(Sc21_L * Sc21_R)", 300, 0, 25., 400, 0., 4000.); // CEJ: why are Z limits so low?
    h2_x2_vs_Z_mhtdc = new TH2D("h2_x2_vs_Z_mhtdc", "x2 vs. Z1", 400, id->min_z_plot, id->max_z_plot, 200, -100., 100.);
    h2_x4_vs_Z_mhtdc = new TH2D("h2_x4_vs_Z_mhtdc", "x4 vs. Z1", 400, id->min_z_plot, id->max_z_plot, 200, -100., 100.);
    h2_x2_vs_x4_mhtdc = new TH2D("h2_x2_vs_x4_mhtdc", "x2 vs. x4", 200, -100, 100, 200, -100, 100);
    h2_SC41dE_vs_AoQ_mhtdc = new TH2D("h2_SC41dE_vs_AoQ_mhtdc", "A/Q vs. dE in SC41", 1000, 1.2, 3.0, 1000, 0., 4000.); // CEJ: why not min/max aoq?
    h2_dE_vs_ToF_mhtdc = new TH2D("h2_dE_vs_ToF_mhtdc", "ToF S2-S4 vs. dE in MUSIC1", 2000, 0., 70000., 400, 0, 4000);
    h2_dE1_vs_x2_mhtdc = new TH2D("h2_dE1_vs_x2_mhtdc", "x2 vs. dE in MUSIC1", 200, -100., 100., 400, 0., 4000.);
    h2_dE1_vs_x4_mhtdc = new TH2D("h2_dE1_vs_x4_mhtdc", "x4 vs. dE in MUSIC1", 200, -100., 100., 400, 0., 4000.);

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
    gDirectory = tmp;

    return kSUCCESS;

}

void FrsNearlineSpectra::Exec(Option_t* option)
{
    if (fFrsHitArray && fFrsHitArray->GetEntriesFast() > 0)
    {   
        Int_t nHits = fFrsHitArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FrsHitData* FrsHit = (FrsHitData*)fFrsHitArray->At(ihit);
            if (!FrsHit) continue;

            Long64_t FRS_time_mins = 0;
            if(FrsHit->Get_wr_t() > 0) FRS_time_mins = (FrsHit->Get_wr_t() / 60E9) - 26900000; // CEJ: taken from Go4..

            /* --------  TAC and PID gates ----------- */
            if (FrsHit->Get_ID_z() > 0 && FRS_time_mins > 0) h2_Z1_vs_T->Fill(FRS_time_mins, FrsHit->Get_ID_z());

            if (FrsHit->Get_ID_AoQ() > 0 && FRS_time_mins > 0) h2_AoQ_vs_T->Fill(FRS_time_mins, FrsHit->Get_ID_AoQ());

            if (FrsHit->Get_ID_AoQ() > 0 && FrsHit->Get_ID_z() > 0) h2_Z_vs_AoQ->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
            if (FrsHit->Get_ID_AoQ_corr() > 0 && FrsHit->Get_ID_z() > 0) h2_Z_vs_AoQ_corr->Fill(FrsHit->Get_ID_AoQ_corr(), FrsHit->Get_ID_z());

            if (FrsHit->Get_ID_z() > 0 && FrsHit->Get_ID_z2() > 0) h2_Z_vs_Z2->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
            if (TMath::Abs(FrsHit->Get_ID_z() - FrsHit->Get_ID_z2()) < 0.4) // CEJ: should we .config this condition?
            {
                h2_Z_vs_AoQ_Zsame->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                h2_x4_vs_AoQ_Zsame->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                h2_x2_vs_AoQ_Zsame->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
            }

            // CEJ: "analysis" taken from Go4 (DESPEC/FRS)
            // is stupid, we already demand the x2 condition to fill the hit.
            // this should be reconidered
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

            // Define PID gates
            // Z1 vs AoQ

            if (!FrsGates.empty())
            {

            /*if (cutID_Z_AoQ[0] != nullptr)
            {*/  
                for (int gate = 0; gate < FrsGates.size(); gate++)
                {   
                    if (FrsGates[gate]->Passed_ZvsAoQ(FrsHit->Get_ID_z(), FrsHit->Get_ID_AoQ()))
                    {
                    /*if (cutID_Z_AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z()))
                    {*/
                        h2_Z_vs_AoQ_ZAoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                        h2_Z1_vs_Z2_ZAoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
                        h2_x2_vs_AoQ_ZAoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                        h2_x4_vs_AoQ_ZAoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                        h2_dEdeg_vs_Z_ZAoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdeg());
                        h2_dedegoQ_vs_Z_ZAoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdegoQ());
                        h1_a2_ZAoQ_gate[gate]->Fill(FrsHit->Get_ID_a2());
                        h1_a4_ZAoQ_gate[gate]->Fill(FrsHit->Get_ID_a4());
                    }
                /*}
            
            }

            // Z1 vs Z2
            if (cutID_Z_Z2[0] != nullptr)
            {
                for (int gate = 0; gate < cutID_Z_Z2.size(); gate++)
                {*/
                    if (FrsGates[gate]->Passed_ZvsZ2(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                    {
                    /*if(cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                    {*/
                        h2_dEdeg_vs_Z_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_z(),FrsHit->Get_ID_dEdeg());
                        h2_dEdegoQ_vs_Z_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_z(),FrsHit->Get_ID_dEdegoQ());
                        h2_Z1_vs_Z2_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_z(),FrsHit->Get_ID_z2());
                        h1_a2_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_a2());
                        h1_a4_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_a4());

                        if(FrsHit->Get_ID_AoQ() > 1 && FrsHit->Get_ID_AoQ() < 3 && FrsHit->Get_ID_x2() > -100 && FrsHit->Get_ID_x2() < 100) h2_x2_vs_AoQ_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                        if(FrsHit->Get_ID_AoQ() > 1 && FrsHit->Get_ID_AoQ() < 3 && FrsHit->Get_ID_x4() > -100 && FrsHit->Get_ID_x4() < 100) h2_x4_vs_AoQ_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                        if(FrsHit->Get_ID_AoQ() > 1 && FrsHit->Get_ID_AoQ() < 3) h2_Z_vs_AoQ_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                    }
                /*}
            }

            // x2 vs AoQ
            if (cutID_x2AoQ[0] != nullptr)
            {   
                for (int gate = 0; gate < cutID_x2AoQ.size(); gate++)
                {*/
                    if (FrsGates[gate]->Passed_x2vsAoQ(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2()))
                    {
                    /*if(cutID_x2AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2()))
                    {*/
                        h2_x2_vs_AoQ_x2AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                        h2_Z1_vs_Z2_x2AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
                        
                        // Z1 Z2 + x2AoQ
                        /*if (cutID_Z_Z2[0] != nullptr)
                        {*/ 
                            if (FrsGates[gate]->Passed_ZvsZ2(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                            {
                            /*if(cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                            {*/

                                h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                                h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                                h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                                h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdeg());
                                h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdegoQ());
                                h1_a2_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_a2());
                                h1_a4_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_a4()); 
                            }
                        }
                    /*}
                }
            }

            // x4 vs AoQ
            if (cutID_x4AoQ[0] != nullptr)
            {   
                for (int gate = 0; gate < cutID_x4AoQ.size(); gate++)
                {*/
                    if (FrsGates[gate]->Passed_x4vsAoQ(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4()))
                    {
                    /*if(cutID_x4AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4()))
                    {*/
                        h2_x4_vs_AoQ_x4AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                        h2_Z1_vs_Z2_x4AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
                        
                        ///Z1 Z2 + x4AoQ
                        /*if (cutID_Z_Z2[0] != nullptr)
                        {*/
                            if (FrsGates[gate]->Passed_ZvsZ2(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                            {
                            /*if(cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                            {*/
                                h2_x2_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                                h2_x4_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                                h2_Z_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                                h2_dEdeg_vs_Z_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdeg());
                                h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdegoQ());
                                h1_a2_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_a2());
                                h1_a4_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_a4());
                            }
                        }
                    /*}
                }
            }

            // GATE: Energy loss S2 vs Z (Charge states)
            if (cutID_dEdegZ[0] != nullptr)
            {   
                for (int gate = 0; gate < cutID_dEdegZ.size(); gate++)
                {*/ 
                    if (FrsGates[gate]->Passed_dEdegvsZ(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdeg()))
                    {
                    /*if(cutID_dEdegZ[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdeg()))
                    {*/
                        h2_Z_vs_AoQ_dEdegZgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                        h2_Z1_vs_Z2_dEdegZgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
                        h2_x2_vs_AoQ_dEdegZgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                        h2_x4_vs_AoQ_dEdegZgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                        h1_a2_dEdegZgate[gate]->Fill(FrsHit->Get_ID_a2());
                        h1_a4_dEdegZgate[gate]->Fill(FrsHit->Get_ID_a4());
                    
                        if(fabs(FrsHit->Get_ID_z2() - FrsHit->Get_ID_z()) < 0.4) h2_Z_vs_AoQ_Zsame_dEdegZgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                    }
                }
            }

            // CEJ I hate this bit
            /* ----- MHTDC Histograms and PID Gates -------------------------------------------- */
            for (int i = 0; i < MAX_MHTDC_MULT; i++)
            {   
                // Z1 vs Time
                if (FrsHit->Get_ID_z_mhtdc(i) > 0 && FRS_time_mins > 0) h2_Z1_vs_T_mhtdc->Fill(FRS_time_mins, FrsHit->Get_ID_z_mhtdc(i));
                // AoQ vs Time
                if (FrsHit->Get_ID_AoQ_mhtdc(i) > 0 && FRS_time_mins > 0) h2_AoQ_vs_T_mhtdc->Fill(FRS_time_mins, FrsHit->Get_ID_AoQ_mhtdc(i));
                // AoQ vs Z
                if(FrsHit->Get_ID_AoQ_mhtdc(i) > 0 && FrsHit->Get_ID_z_mhtdc(i) > 0) h2_Z_vs_AoQ_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                if(FrsHit->Get_ID_AoQ_corr_mhtdc(i) > 0 && FrsHit->Get_ID_z_mhtdc(i) > 0) h2_Z_vs_AoQ_corr_mhtdc->Fill(FrsHit->Get_ID_AoQ_corr_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
            
                //Z1 Z2 
                if(FrsHit->Get_ID_z_mhtdc(i) > 0 && FrsHit->Get_ID_z2_mhtdc(i) > 0) h2_Z_vs_Z2_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
            
                if(TMath::Abs(FrsHit->Get_ID_z_mhtdc(i) - FrsHit->Get_ID_z2_mhtdc(i)) < 0.4)
                {
                    h2_Z_vs_AoQ_Zsame_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                    h2_x4_vs_AoQ_Zsame_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                    h2_x2_vs_AoQ_Zsame_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                }
            
                // AoQ vs X2
                if(FrsHit->Get_ID_AoQ_mhtdc(i) > 0 && FrsHit->Get_ID_x2() > -100 && FrsHit->Get_ID_x2() < 100)  h2_x2_vs_AoQ_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
            
                if(FrsHit->Get_ID_AoQ_mhtdc(i) > 0 && FrsHit->Get_ID_x4() > -100 && FrsHit->Get_ID_x4() < 100)  h2_x4_vs_AoQ_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                
                // Charge states
                // CEJ: dEdeg mhtdc is not used in the check, but it is filled. Why??
                if(FrsHit->Get_ID_z_mhtdc(i) > 0 && FrsHit->Get_ID_dEdegoQ() != 0) h2_dEdegoQ_vs_Z_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdegoQ_mhtdc(i));
                if(FrsHit->Get_ID_z_mhtdc(i) > 0 && FrsHit->Get_ID_dEdeg() != 0) h2_dEdeg_vs_Z_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdeg_mhtdc(i));
            
                // Angles vs AoQ 
                if(FrsHit->Get_ID_AoQ_mhtdc(i) != 0 && FrsHit->Get_ID_a2() != 0) h2_a2_vs_AoQ_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_a2());
                if(FrsHit->Get_ID_AoQ_mhtdc(i) != 0 && FrsHit->Get_ID_a4() != 0) h2_a4_vs_AoQ_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_a4());
            
                if(FrsHit->Get_ID_z_mhtdc(i) != 0 && FrsHit->Get_music_dE(1) != 0) h2_Z_vs_dE2_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_music_dE(1));
                
                if(FrsHit->Get_ID_z_mhtdc(i) != 0 && FrsHit->Get_sci_l(0) != 0 && FrsHit->Get_sci_r(0) != 0) h2_Z_vs_Sc21E_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), sqrt(FrsHit->Get_sci_l(0) * FrsHit->Get_sci_r(0)));
            
                // if > 0 conditions necessary
                h2_x2_vs_Z_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_x2());
                
                h2_x4_vs_Z_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_x4());

            } // multihit loop

            // MHTDC PID Gates
            // Z vs AoQ
            if (!FrsGates.empty())
            {
            /*if (cutID_Z_AoQ[0] != nullptr)
            {*/
                for(int gate = 0; gate < FrsGates.size(); gate++)
                {
                    for (int i = 0; i < MAX_MHTDC_MULT; i++)
                    {   
                        if (FrsGates[gate]->Passed_ZvsAoQ(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_AoQ_mhtdc(i)))
                        {
                        /*if(cutID_Z_AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i)))
                        {*/ 
                            // CEJ: this will change based on final hit?
                            h2_x2_vs_AoQ_ZAoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                            h2_x4_vs_AoQ_ZAoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                            h2_Z_vs_AoQ_ZAoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                            h2_Z1_vs_Z2_ZAoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                            h2_dEdeg_vs_Z_ZAoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdeg_mhtdc(i));
                            h2_dedegoQ_vs_Z_ZAoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdegoQ_mhtdc(i));
                            h1_a2_ZAoQ_gate_mhtdc[gate]->Fill(FrsHit->Get_ID_a2());
                            h1_a4_ZAoQ_gate_mhtdc[gate]->Fill(FrsHit->Get_ID_a4());
                        }
                    /*}
                }
            }

            // Z1 vs Z2
            if (cutID_Z_Z2[0] != nullptr)
            {
                for(int gate = 0; gate < cutID_Z_Z2.size(); gate++)
                {
                    for (int i = 0; i < MAX_MHTDC_MULT; i++)
                    {*/ 
                        if (FrsGates[gate]->Passed_ZvsZ2(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i)))
                        {
                        /*if(cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i)))
                        {*/
                            h2_dEdeg_vs_Z_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdeg_mhtdc(i));
                            h2_dEdegoQ_vs_Z_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdegoQ_mhtdc(i));
                            h2_Z1_vs_Z2_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                            if(FrsHit->Get_ID_a2() != 0) h1_a2_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_a2());
                            if(FrsHit->Get_ID_a4() != 0) h1_a4_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_a4());
                        
                            // X2 AoQ gated on Z1 Z2
                            if(FrsHit->Get_ID_x2() > -100 && FrsHit->Get_ID_x2() < 100)
                            {
                                h2_x2_vs_AoQ_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                            }
                            
                            if(FrsHit->Get_ID_x4() > -100 && FrsHit->Get_ID_x4() < 100)
                            {
                                h2_x4_vs_AoQ_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                                
                                // Z1 AoQ gated on Z1 Z2
                                if(FrsHit->Get_ID_AoQ_mhtdc(i) != 0 && FrsHit->Get_ID_z_mhtdc(i) != 0) h2_Z_vs_AoQ_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                                
                            }
                        }
                    /*}
                }
            }

            // ID x2 vs AoQ
            if (cutID_x2AoQ[0] != nullptr)
            {
                for(int gate = 0; gate < cutID_x2AoQ.size(); gate++)
                {
                    for (int i = 0; i < MAX_MHTDC_MULT; i++)
                    {*/
                        if (FrsGates[gate]->Passed_x2vsAoQ(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2()))
                        {
                        /*if(cutID_x2AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2()))
                        {*/
                            h2_x2_vs_AoQ_x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                            h2_Z1_vs_Z2_x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                            // The selected Z1 Z2 gate for this part can be found in the Correlations_config.dat file
                            // Z1 Z2 +X2 AoQ
                            /*if (cutID_Z_Z2[0] != nullptr)
                            {*/
                                if (FrsGates[gate]->Passed_ZvsZ2(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i)))
                                {
                                /*if(cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i)))
                                {*/
                                    h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                                    h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                                    h2_Z1_vs_Z2_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                                    h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdeg_mhtdc(i));
                                    h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdegoQ_mhtdc(i));
                                    h1_a2_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a2());
                                    h1_a4_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a4());
                                }
                            }
                        /*}
                    }
                }
            }
            
            // ID x4 vs AoQ
            if (cutID_x4AoQ[0] != nullptr)
            {
                for(int gate = 0; gate < cutID_x4AoQ.size(); gate++)
                {
                    for (int i = 0; i < MAX_MHTDC_MULT; i++)
                    {*/ 
                        if (FrsGates[gate]->Passed_x4vsAoQ(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4()))
                        {
                        /*if(cutID_x4AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4()))
                        {*/
                            h2_x4_vs_AoQ_x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                            h2_Z1_vs_Z2_x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                            // Z1 Z2 +X4 AoQ
                            /*if (cutID_Z_Z2[0] != nullptr)
                            {*/
                                if (FrsGates[gate]->Passed_ZvsZ2(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i)))
                                {
                                /*if(cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i)))
                                {*/
                                    h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                                    h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                                    h2_Z1_vs_Z2_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                                    h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdeg_mhtdc(i));
                                    h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdegoQ_mhtdc(i));
                                    h1_a2_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a2());
                                    h1_a4_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a4());
                                    
                                }
                            }
                        /*}
                    }
                }
            }

            // GATE: Energy loss S2 vs Z (Charge states)
            if (cutID_dEdegZ[0] != nullptr)
            {
                for(int gate = 0; gate < cutID_dEdegZ.size(); gate++)
                {
                    for (int i = 0; i < MAX_MHTDC_MULT; i++)
                    {*/ 
                        if (FrsGates[gate]->Passed_dEdegvsZ(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdeg()))
                        {
                        /*if (cutID_dEdegZ[gate]->IsInside(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdeg()))
                        {*/
                            h2_Z_vs_dEdeg_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdeg()); // CEJ: again why not MHTDC here
                            h2_Z_vs_AoQ_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                            h2_Z1_vs_Z2_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                            h2_x2_vs_AoQ_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                            h2_x4_vs_AoQ_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                            h1_a2_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a2());
                            h1_a4_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a4());
                    
                            if (fabs(FrsHit->Get_ID_z2_mhtdc(i) - FrsHit->Get_ID_z_mhtdc(i)) < 0.4) h2_Z_vs_AoQ_Zsame_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                        }
                    }
                }
            }
        } // ihits
    } // non-zero FRS entries
    
}

void FrsNearlineSpectra::FinishEvent()
{
    // clear any arrays/vectors if needed
    
}

void FrsNearlineSpectra::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_frs->Write();
    gDirectory = tmp;
    c4LOG(info, "Written FRS analysis histograms to file.");
}

ClassImp(FrsNearlineSpectra)
