// FairRoot
#include "FairRootManager.h"
#include "FairRunOnline.h"
#include "FairTask.h"

// c4
#include "FrsAnalysisSpectra.h"
#include "FrsHitData.h"
#include "FrsAnalysisData.h"
#include "TCutGGates.h"
#include "c4Logger.h"

// ROOT
#include "TClonesArray.h"
#include <vector>
#include "TDirectory.h"
#include "THttpServer.h"

FrsAnalysisSpectra::FrsAnalysisSpectra(TFRSParameter* ffrs,
        TMWParameter* fmw,
        TTPCParameter* ftpc,
        TMUSICParameter* fmusic,
        TLABRParameter* flabr,
        TSCIParameter* fsci,
        TIDParameter* fid,
        TSIParameter* fsi,
        TMRTOFMSParameter* fmrtof,
        TRangeParameter* frange,
        std::vector<TCutGGates*> fFrsGates)
    :   FairTask()
    ,   fNEvents()
    ,   header(nullptr)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
    ,   fFrsAnalysisArray(new TClonesArray("FrsAnalysisData"))
{
    frs = ffrs;
    mw = fmw;
    tpc = ftpc;
    music = fmusic;
    labr = flabr;
    sci = fsci;
    id = fid;
    si = fsi;
    mrtof = fmrtof;
    range = frange;

    // Set gates
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

}

FrsAnalysisSpectra::FrsAnalysisSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents()
    ,   header(nullptr)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
    ,   fFrsAnalysisArray(new TClonesArray("FrsAnalysisData"))
{

}

FrsAnalysisSpectra::~FrsAnalysisSpectra()
{
    c4LOG(info, "Deleting FrsAnalysisSpectra task.");
    if (fFrsHitArray) delete fFrsHitArray;
}

InitStatus FrsAnalysisSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    fFrsHitArray = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fFrsHitArray, "FrsHitData branch not found!");

    //mgr->Register("FrsAnalysisData", "FRS Analysis Data", fFrsAnalysisArray, !fOnline);
    //TDirectory::TContext ctx(nullptr);

    
    folder_frs_hists = (TFolder*)mgr->GetObject("FRS");
    //if (!folder_frs_hists) folder_frs_hists = new TFolder("FRS", "FRS");

    frs_analysis_hists = new TFolder("FRS Analysis Histograms", "FRS Analysis Histograms");
    
    //run->AddObject(frs_analysis_hists);
    
    folder_frs_hists->Add(frs_analysis_hists);

    frs_tac_hists = new TFolder("TAC", "TAC");
    frs_analysis_hists->Add(frs_tac_hists);
    frs_mhtdc_hists = new TFolder("MHTDC", "MHTDC");
    frs_analysis_hists->Add(frs_mhtdc_hists);

    frs_ZvsAoQ_hists = new TFolder("ZvsAoQgated", "ZvsAoQgated");
    frs_tac_hists->Add(frs_ZvsAoQ_hists);
    frs_Z1vsZ2_hists = new TFolder("Z1vsZ2gated", "Z1vsZ2gated");
    frs_tac_hists->Add(frs_Z1vsZ2_hists);
    frs_x2vsAoQ_hists = new TFolder("x2vsAoQgated", "x2vsAoQgated");
    frs_tac_hists->Add(frs_x2vsAoQ_hists);
    frs_x4vsAoQ_hists = new TFolder("x4vsAoQgated", "x4vsAoQgated");
    frs_tac_hists->Add(frs_x4vsAoQ_hists);
    frs_dEdegvsZ_hists = new TFolder("dEdegvsZgated", "dEdegvsZgated");
    frs_tac_hists->Add(frs_dEdegvsZ_hists);
    frs_x2vsAoQ_Z1vsZ2_hists = new TFolder("x2vsAoQ_Z1vsZ2gated", "x2vsAoQ_Z1vsZ2gated");
    frs_tac_hists->Add(frs_x2vsAoQ_Z1vsZ2_hists);
    frs_x4vsAoQ_Z1vsZ2_hists = new TFolder("x4vsAoQ_Z1vsZ2gated", "x4vsAoQ_Z1vsZ2gated");
    frs_tac_hists->Add(frs_x4vsAoQ_Z1vsZ2_hists);

    frs_ZvsAoQ_hists_mhtdc = new TFolder("ZvsAoQgated_mhtdc", "ZvsAoQgated_mhtdc");
    frs_mhtdc_hists->Add(frs_ZvsAoQ_hists_mhtdc);
    frs_Z1vsZ2_hists_mhtdc = new TFolder("Z1vsZ2gated_mhtdc", "Z1vsZ2gated_mhtdc");
    frs_mhtdc_hists->Add(frs_Z1vsZ2_hists_mhtdc);
    frs_x2vsAoQ_hists_mhtdc = new TFolder("x2vsAoQgated_mhtdc", "x2vsAoQgated_mhtdc");
    frs_mhtdc_hists->Add(frs_x2vsAoQ_hists_mhtdc);
    frs_x4vsAoQ_hists_mhtdc = new TFolder("x4vsAoQgated_mhtdc", "x4vsAoQgated_mhtdc");
    frs_mhtdc_hists->Add(frs_x4vsAoQ_hists_mhtdc);
    frs_dEdegvsZ_hists_mhtdc = new TFolder("dEdegvsZgated_mhtdc", "dEdegvsZgated_mhtdc");
    frs_mhtdc_hists->Add(frs_dEdegvsZ_hists_mhtdc);
    frs_x2vsAoQ_Z1vsZ2_hists_mhtdc = new TFolder("x2vsAoQ_Z1vsZ2gated_mhtdc", "x2vsAoQ_Z1vsZ2gated_mhtdc");
    frs_mhtdc_hists->Add(frs_x2vsAoQ_Z1vsZ2_hists_mhtdc);
    frs_x4vsAoQ_Z1vsZ2_hists_mhtdc = new TFolder("x4vsAoQ_Z1vsZ2gated_mhtdc", "x4vsAoQ_Z1vsZ2gated_mhtdc");
    frs_mhtdc_hists->Add(frs_x4vsAoQ_Z1vsZ2_hists_mhtdc);

    // init histograms
    //hID_Z1_vs_T
    h2_Z1_vs_T = new TH2D("h2_Z1_vs_T", "Z1 vs. Time [mins]", 1240, 16600, 29000, 1500, id->min_z_plot, id->max_z_plot);
    frs_tac_hists->Add(h2_Z1_vs_T);
    //hID_AoQ_vs_T
    h2_AoQ_vs_T = new TH2D("h2_AoQ_vs_T", "A/Q vs. Time [mins]", 1200, 17000, 29000, 1500, id->min_aoq_plot, 3.0);
    frs_tac_hists->Add(h2_AoQ_vs_T);
    //hID_Z_AoQ
    h2_Z_vs_AoQ = new TH2D("h2_Z_vs_AoQ", "Z1 vs. A/Q", 1500, id->min_aoq_plot, 3.0, 1000, id->min_z_plot, id->max_z_plot);
    frs_tac_hists->Add(h2_Z_vs_AoQ);
    //hID_Z_AoQ_corr
    h2_Z_vs_AoQ_corr = new TH2D("h2_Z_vs_AoQ_corr", "Z1 vs. A/Q (corr)", 1500, id->min_aoq_plot, 3.0, 1000, id->min_z_plot, id->max_z_plot);
    frs_tac_hists->Add(h2_Z_vs_AoQ_corr);
    //hID_Z_Z2
    h2_Z_vs_Z2 = new TH2D("h2_Z_vs_Z2", "Z1 vs. Z2", 1000, id->min_z_plot, id->max_z_plot, 400, id->min_z_plot, id->max_z_plot);
    frs_tac_hists->Add(h2_Z_vs_Z2);
    //hID_Z_AoQ_zsame
    h2_Z_vs_AoQ_Zsame = new TH2D("h2_Z_vs_AoQ_Zsame", "Z1 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, id->min_aoq_plot, 3.0, 1000, id->min_z_plot, id->max_z_plot);
    frs_tac_hists->Add(h2_Z_vs_AoQ_Zsame);
    //hID_x4AoQ_zsame
    h2_x4_vs_AoQ_Zsame = new TH2D("h2_x4_vs_AoQ_Zsame", "x4 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, id->min_aoq_plot, 3.0, 300, -150., 100.); // CEJ: should these lims not be defined somewhere..
    frs_tac_hists->Add(h2_x4_vs_AoQ_Zsame);
    //hID_x2AoQ_zsame
    h2_x2_vs_AoQ_Zsame = new TH2D("h2_x2_vs_AoQ_Zsame", "x4 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, id->min_aoq_plot, 3.0, 300, -150., 100.);
    frs_tac_hists->Add(h2_x2_vs_AoQ_Zsame);
    //hID_x2AoQ
    h2_x2_vs_AoQ = new TH2D("h2_x2_vs_AoQ", "x2 vs. A/Q", 1500, id->min_aoq_plot, 3.0, 200, -100., 100.);
    frs_tac_hists->Add(h2_x2_vs_AoQ);
    //hID_x4AoQ
    h2_x4_vs_AoQ = new TH2D("h2_x4_vs_AoQ", "x4 vs. A/Q", 1500, id->min_aoq_plot, 3.0, 200, -100., 100.);
    frs_tac_hists->Add(h2_x4_vs_AoQ);
    //hdEdegoQ_Z
    h2_dEdegoQ_vs_Z = new TH2D("h2_dEdegoQ_vs_Z", "dE in S2 degrader / Q vs. Z1", 1000, id->min_z_plot, id->max_z_plot, 1000, 0.1, 0.8);
    frs_tac_hists->Add(h2_dEdegoQ_vs_Z);
    //hdEdeg
    h2_dEdeg_vs_Z = new TH2D("h2_dEdeg_vs_Z", "dE in S2 degrader vs. Z1", 1000, id->min_z_plot, id->max_z_plot, 1000, 10, 100);
    frs_tac_hists->Add(h2_dEdeg_vs_Z);
    //hID_a2AoQ
    h2_a2_vs_AoQ = new TH2D("h2_a2_vs_AoQ", "A/Q vs. Angle (S2)", 500, id->min_aoq_plot, 3.0, 500, -25, 25);
    frs_tac_hists->Add(h2_a2_vs_AoQ);
    //hID_a4AoQ
    h2_a4_vs_AoQ = new TH2D("h2_a4_vs_AoQ", "A/Q vs. Angle (S4)", 500, id->min_aoq_plot, 3.0, 500, -25, 25);
    frs_tac_hists->Add(h2_a4_vs_AoQ);
    //hID_Z_dE2
    h2_Z_vs_dE2 = new TH2D("h2_Z_vs_dE2", "Z1 vs. dE in MUSIC2", 400, id->min_z_plot, id->max_z_plot, 250, 0., 4000.);
    frs_tac_hists->Add(h2_Z_vs_dE2);
    //hID_x2x4
    h2_x2_vs_x4 = new TH2D("h2_x2_vs_x4", "x2 vs. x4", 200, -100, 100, 200, -100, 100);
    frs_tac_hists->Add(h2_x2_vs_x4);
    //hID_SC41dE_AoQ
    h2_SC41dE_vs_AoQ = new TH2D("h2_SC41dE_vs_AoQ", "A/Q vs. dE in SC41", 1000, 1.2, 3.0, 1000, 0., 4000.); // CEJ: why not min/max aoq?
    frs_tac_hists->Add(h2_SC41dE_vs_AoQ);
    //hID_dEToF
    h2_dE_vs_ToF = new TH2D("h2_dE_vs_ToF", "ToF S2-S4 vs. dE in MUSIC1", 2000, 0., 70000., 400, 0, 4000);
    frs_tac_hists->Add(h2_dE_vs_ToF);
    //hID_x2z
    h2_x2_vs_Z = new TH2D("h2_x2_vs_Z", "x2 vs. Z1", 400, id->min_z_plot, id->max_z_plot, 200, -100., 100.);
    frs_tac_hists->Add(h2_x2_vs_Z);
    //hID_x2z
    h2_x4_vs_Z = new TH2D("h2_x4_vs_Z", "x4 vs. Z1", 400, id->min_z_plot, id->max_z_plot, 200, -100., 100.);
    frs_tac_hists->Add(h2_x4_vs_Z);
    //hID_E_Xs2
    h2_dE1_vs_x2 = new TH2D("h2_dE1_vs_x2", "x2 vs. dE in MUSIC1", 200, -100., 100., 400, 0., 4000.);
    frs_tac_hists->Add(h2_dE1_vs_x2);
    //hID_E_Xs4
    h2_dE1_vs_x4 = new TH2D("h2_dE1_vs_x4", "x4 vs. dE in MUSIC1", 200, -100., 100., 400, 0., 4000.);
    frs_tac_hists->Add(h2_dE1_vs_x4);
    //hID_x2a2
    h2_x2_vs_a2 = new TH2D("h2_x2_vs_a2", "x2 vs. AngleX (S2)", 200, -100., 100., 200, -100., 100.);
    frs_tac_hists->Add(h2_x2_vs_a2);
    //hID_y2b2
    h2_y2_vs_b2 = new TH2D("h2_y2_vs_b2", "y2 vs. AngleY (S2)", 200, -100., 100., 200, -100., 100.);
    frs_tac_hists->Add(h2_y2_vs_b2);
    //hID_x4a4
    h2_x4_vs_a4 = new TH2D("h2_x4_vs_a4", "x4 vs. AngleX (S4)", 200, -100., 100., 200, -100., 100.);
    frs_tac_hists->Add(h2_x4_vs_a4);
    //hID_y4b4
    h2_y4_vs_b4 = new TH2D("h2_y4_vs_b4", "y4 vs. AngleY (S4)", 200, -100., 100., 200, -100., 100.);
    frs_tac_hists->Add(h2_y4_vs_b4);
    //hID_Z_Sc21E
    h2_Z_vs_Sc21E = new TH2D("h2_Z_vs_Sc21E", "Z1 vs. SQRT(Sc21_L * Sc21_R)", 300, 0, 25., 400, 0., 4000.); // CEJ: why are Z limits so low?
    frs_tac_hists->Add(h2_Z_vs_Sc21E);

    // ----------- MHTDC --------------
    //hID_Z1_vs_T
    h2_Z1_vs_T_mhtdc = new TH2D("h2_Z1_vs_T_mhtdc", "Z1 (MHTDC) vs. Time [mins]", 1240, 16600, 29000, 1500, id->min_z_plot, id->max_z_plot);
    frs_mhtdc_hists->Add(h2_Z1_vs_T_mhtdc);
    //hID_AoQ_vs_T
    h2_AoQ_vs_T_mhtdc = new TH2D("h2_AoQ_vs_T_mhtdc", "A/Q (MHTDC) vs. Time [mins]", 1200, 17000, 29000, 1500, id->min_aoq_plot, 3.0);
    frs_mhtdc_hists->Add(h2_AoQ_vs_T_mhtdc);
    //hID_Z_AoQ
    h2_Z_vs_AoQ_mhtdc = new TH2D("h2_Z_vs_AoQ_mhtdc", "Z1 vs. A/Q (MHTDC)", 1500, id->min_aoq_plot, 3.0, 1000, id->min_z_plot, id->max_z_plot);
    frs_mhtdc_hists->Add(h2_Z_vs_AoQ_mhtdc);
    //hID_Z_AoQ_corr
    h2_Z_vs_AoQ_corr_mhtdc = new TH2D("h2_Z_vs_AoQ_corr_mhtdc", "Z1 vs. A/Q (corr)", 1500, id->min_aoq_plot, 3.0, 1000, id->min_z_plot, id->max_z_plot);
    frs_mhtdc_hists->Add(h2_Z_vs_AoQ_corr_mhtdc);
    //hID_Z_Z2
    h2_Z_vs_Z2_mhtdc = new TH2D("h2_Z_vs_Z2_mhtdc", "Z1 vs. Z2 (MHTDC)", 1000, id->min_z_plot, id->max_z_plot, 400, id->min_z_plot, id->max_z_plot);
    frs_mhtdc_hists->Add(h2_Z_vs_Z2_mhtdc);
    //hID_Z_AoQ_zsame
    h2_Z_vs_AoQ_Zsame_mhtdc = new TH2D("h2_Z_vs_AoQ_Zsame_mhtdc", "Z1 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, id->min_aoq_plot, 3.0, 1000, id->min_z_plot, id->max_z_plot);
    frs_mhtdc_hists->Add(h2_Z_vs_AoQ_Zsame_mhtdc);
    //hID_x4AoQ_zsame
    h2_x4_vs_AoQ_Zsame_mhtdc = new TH2D("h2_x4_vs_AoQ_Zsame_mhtdc", "x4 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, id->min_aoq_plot, 3.0, 300, -150., 100.); // CEJ: should these lims not be defined somewhere..
    frs_mhtdc_hists->Add(h2_x4_vs_AoQ_Zsame_mhtdc);
    //hID_x2AoQ_zsame
    h2_x2_vs_AoQ_Zsame_mhtdc = new TH2D("h2_x2_vs_AoQ_Zsame_mhtdc", "x4 vs. A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, id->min_aoq_plot, 3.0, 300, -150., 100.);
    frs_mhtdc_hists->Add(h2_x2_vs_AoQ_Zsame_mhtdc);
    //hID_x2AoQ
    h2_x2_vs_AoQ_mhtdc = new TH2D("h2_x2_vs_AoQ_mhtdc", "x2 vs. A/Q", 1500, id->min_aoq_plot, 3.0, 200, -100., 100.);
    frs_mhtdc_hists->Add(h2_x2_vs_AoQ_mhtdc);
    //hID_x4AoQ
    h2_x4_vs_AoQ_mhtdc = new TH2D("h2_x4_vs_AoQ_mhtdc", "x4 vs. A/Q", 1500, id->min_aoq_plot, 3.0, 200, -100., 100.);
    frs_mhtdc_hists->Add(h2_x4_vs_AoQ_mhtdc);
    //hdEdegoQ_Z
    h2_dEdegoQ_vs_Z_mhtdc = new TH2D("h2_dEdegoQ_vs_Z_mhtdc", "dE in S2 degrader / Q vs. Z1", 1000, id->min_z_plot, id->max_z_plot, 1000, 0.1, 0.8);
    frs_mhtdc_hists->Add(h2_dEdegoQ_vs_Z_mhtdc);
    //hdEdeg
    h2_dEdeg_vs_Z_mhtdc = new TH2D("h2_dEdeg_vs_Z_mhtdc", "dE in S2 degrader vs. Z1", 1000, id->min_z_plot, id->max_z_plot, 1000, 10, 100);
    frs_mhtdc_hists->Add(h2_dEdeg_vs_Z_mhtdc);
    //hID_a2AoQ
    h2_a2_vs_AoQ_mhtdc = new TH2D("h2_a2_vs_AoQ_mhtdc", "A/Q vs. Angle (S2)", 500, id->min_aoq_plot, 3.0, 500, -25, 25);
    frs_mhtdc_hists->Add(h2_a2_vs_AoQ_mhtdc);
    //hID_a4AoQ
    h2_a4_vs_AoQ_mhtdc = new TH2D("h2_a4_vs_AoQ_mhtdc", "A/Q vs. Angle (S4)", 500, id->min_aoq_plot, 3.0, 500, -25, 25);
    frs_mhtdc_hists->Add(h2_a4_vs_AoQ_mhtdc);
    //hID_Z_dE2
    h2_Z_vs_dE2_mhtdc = new TH2D("h2_Z_vs_dE2_mhtdc", "Z1 vs. dE in MUSIC2", 400, id->min_z_plot, id->max_z_plot, 250, 0., 4000.);
    frs_mhtdc_hists->Add(h2_Z_vs_dE2_mhtdc);
    // hID_Z_Sc21E_mhtdc
    h2_Z_vs_Sc21E_mhtdc = new TH2D("h2_Z_vs_Sc21E_mhtdc", "Z1 vs. SQRT(Sc21_L * Sc21_R)", 300, 0, 25., 400, 0., 4000.); // CEJ: why are Z limits so low?
    frs_mhtdc_hists->Add(h2_Z_vs_Sc21E_mhtdc);
    //hID_x2z
    h2_x2_vs_Z_mhtdc = new TH2D("h2_x2_vs_Z_mhtdc", "x2 vs. Z1", 400, id->min_z_plot, id->max_z_plot, 200, -100., 100.);
    frs_mhtdc_hists->Add(h2_x2_vs_Z_mhtdc);
    //hID_x2z
    h2_x4_vs_Z_mhtdc = new TH2D("h2_x4_vs_Z_mhtdc", "x4 vs. Z1", 400, id->min_z_plot, id->max_z_plot, 200, -100., 100.);
    frs_mhtdc_hists->Add(h2_x4_vs_Z_mhtdc);
    //hID_x2x4
    h2_x2_vs_x4_mhtdc = new TH2D("h2_x2_vs_x4_mhtdc", "x2 vs. x4", 200, -100, 100, 200, -100, 100);
    frs_mhtdc_hists->Add(h2_x2_vs_x4_mhtdc);
    //hID_SC41dE_AoQ
    h2_SC41dE_vs_AoQ_mhtdc = new TH2D("h2_SC41dE_vs_AoQ_mhtdc", "A/Q vs. dE in SC41", 1000, 1.2, 3.0, 1000, 0., 4000.); // CEJ: why not min/max aoq?
    frs_mhtdc_hists->Add(h2_SC41dE_vs_AoQ_mhtdc);
    //hID_dEToF
    h2_dE_vs_ToF_mhtdc = new TH2D("h2_dE_vs_ToF_mhtdc", "ToF S2-S4 vs. dE in MUSIC1", 2000, 0., 70000., 400, 0, 4000);
    frs_mhtdc_hists->Add(h2_dE_vs_ToF_mhtdc);
    //hID_E_Xs2
    h2_dE1_vs_x2_mhtdc = new TH2D("h2_dE1_vs_x2_mhtdc", "x2 vs. dE in MUSIC1", 200, -100., 100., 400, 0., 4000.);
    frs_mhtdc_hists->Add(h2_dE1_vs_x2_mhtdc);
    //hID_E_Xs4
    h2_dE1_vs_x4_mhtdc = new TH2D("h2_dE1_vs_x4_mhtdc", "x4 vs. dE in MUSIC1", 200, -100., 100., 400, 0., 4000.);
    frs_mhtdc_hists->Add(h2_dE1_vs_x4_mhtdc);

    // ZvsAoQ gates
    if (cutID_Z_AoQ[0] != nullptr)
    {   
        for (int gate = 0; gate < cutID_Z_AoQ.size(); gate++)
        {
            //hID_ZAoQ_ZAoQgate
            h2_Z_vs_AoQ_ZAoQgate.emplace_back(new TH2I(Form("h2_Z_vs_AoQ_ZAoQgate%d",gate), Form("Z vs. A/Q - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot)); // CEJ: why are we using FRS_HISTO_BIN like this here?
            frs_ZvsAoQ_hists->Add(h2_Z_vs_AoQ_ZAoQgate[gate]);
            //hID_Z1Z2_ZAoQgate
            h2_Z1_vs_Z2_ZAoQgate.emplace_back(new TH2I(Form("h2_Z1_vs_Z2_ZAoQgate%d", gate), Form("Z1 vs. Z2 - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_ZvsAoQ_hists->Add(h2_Z1_vs_Z2_ZAoQgate[gate]);
            //hID_x2AoQ_Z1AoQgate
            h2_x2_vs_AoQ_ZAoQgate.emplace_back(new TH2I(Form("h2_x2_vs_AoQ_ZAoQgate%d", gate), Form("x2 vs. A/Q - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_ZvsAoQ_hists->Add(h2_x2_vs_AoQ_ZAoQgate[gate]);
            //hID_x4AoQ_Z1AoQgate
            h2_x4_vs_AoQ_ZAoQgate.emplace_back(new TH2I(Form("h2_x4_vs_AoQ_ZAoQgate%d", gate), Form("x4 vs. A/Q - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_ZvsAoQ_hists->Add(h2_x4_vs_AoQ_ZAoQgate[gate]);
            //hID_dEdegZ1_Z1AoQgate
            h2_dEdeg_vs_Z_ZAoQgate.emplace_back(new TH2I(Form("h2_dEdeg_vs_Z_ZAoQgate%d", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 50.));
            frs_ZvsAoQ_hists->Add(h2_dEdeg_vs_Z_ZAoQgate[gate]);
            //hID_dEdegoQ_Z1_Z1AoQgate
            h2_dedegoQ_vs_Z_ZAoQgate.emplace_back(new TH2I(Form("h2_dedegoQ_vs_Z_ZAoQgate%d", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 50.));
            frs_ZvsAoQ_hists->Add(h2_dedegoQ_vs_Z_ZAoQgate[gate]);
            //hID_a2_Z1AoQgate
            h1_a2_ZAoQ_gate.emplace_back(new TH1I(Form("h1_a2_ZAoQ_gate%d", gate), Form("Angle S2 [mrad] - ZAoQ Gate: %d", gate), 100, -1000, 1000));
            frs_ZvsAoQ_hists->Add(h1_a2_ZAoQ_gate[gate]);
            //hID_a4_Z1AoQgate
            h1_a4_ZAoQ_gate.emplace_back(new TH1I(Form("h1_a4_ZAoQ_gate%d", gate), Form("Angle S4 [mrad] - ZAoQ Gate: %d", gate), 100, -1000, 1000));
            frs_ZvsAoQ_hists->Add(h1_a4_ZAoQ_gate[gate]);

            // ----- MHTDC --------
            //hID_x2AoQ_Z1AoQgate
            h2_x2_vs_AoQ_ZAoQgate_mhtdc.emplace_back(new TH2I(Form("h2_x2_vs_AoQ_ZAoQgate%d_mhtdc", gate), Form("x2 vs. A/Q - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_ZvsAoQ_hists_mhtdc->Add(h2_x2_vs_AoQ_ZAoQgate_mhtdc[gate]);
            //hID_x4AoQ_Z1AoQgate
            h2_x4_vs_AoQ_ZAoQgate_mhtdc.emplace_back(new TH2I(Form("h2_x4_vs_AoQ_ZAoQgate%d_mhtdc", gate), Form("x4 vs. A/Q - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_ZvsAoQ_hists_mhtdc->Add(h2_x4_vs_AoQ_ZAoQgate_mhtdc[gate]);
            //hID_ZAoQ_ZAoQgate
            h2_Z_vs_AoQ_ZAoQgate_mhtdc.emplace_back(new TH2I(Form("h2_Z_vs_AoQ_ZAoQgate%d_mhtdc",gate), Form("Z vs. A/Q - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot)); // CEJ: why are we using FRS_HISTO_BIN like this here?
            frs_ZvsAoQ_hists_mhtdc->Add(h2_Z_vs_AoQ_ZAoQgate_mhtdc[gate]);
            //hID_Z1Z2_ZAoQgate
            h2_Z1_vs_Z2_ZAoQgate_mhtdc.emplace_back(new TH2I(Form("h2_Z1_vs_Z2_ZAoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_ZvsAoQ_hists_mhtdc->Add(h2_Z1_vs_Z2_ZAoQgate_mhtdc[gate]);
            //hID_dEdegZ1_Z1AoQgate
            h2_dEdeg_vs_Z_ZAoQgate_mhtdc.emplace_back(new TH2I(Form("h2_dEdeg_vs_Z_ZAoQgate%d_mhtdc", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 50.));
            frs_ZvsAoQ_hists_mhtdc->Add(h2_dEdeg_vs_Z_ZAoQgate_mhtdc[gate]);
            //hID_dEdegoQ_Z1_Z1AoQgate
            h2_dedegoQ_vs_Z_ZAoQgate_mhtdc.emplace_back(new TH2I(Form("h2_dedegoQ_vs_Z_ZAoQgate%d_mhtdc", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 50.));
            frs_ZvsAoQ_hists_mhtdc->Add(h2_dedegoQ_vs_Z_ZAoQgate_mhtdc[gate]);
            //hID_a2_Z1AoQgate
            h1_a2_ZAoQ_gate_mhtdc.emplace_back(new TH1I(Form("h1_a2_ZAoQ_gate%d_mhtdc", gate), Form("Angle S2 [mrad] - ZAoQ Gate: %d", gate), 100, -1000, 1000));
            frs_ZvsAoQ_hists_mhtdc->Add(h1_a2_ZAoQ_gate_mhtdc[gate]);
            //hID_a4_Z1AoQgate
            h1_a4_ZAoQ_gate_mhtdc.emplace_back(new TH1I(Form("h1_a4_ZAoQ_gate%d_mhtdc", gate), Form("Angle S4 [mrad] - ZAoQ Gate: %d", gate), 100, -1000, 1000));
            frs_ZvsAoQ_hists_mhtdc->Add(h1_a4_ZAoQ_gate_mhtdc[gate]);
        }

    }

    if (cutID_Z_Z2[0] != nullptr)
    {
        // Z1vsZ2 gates
        for (int gate = 0; gate < cutID_Z_Z2.size(); gate++)
        {
            //hID_dEdegZ1_Z1Z2gate
            h2_dEdeg_vs_Z_Z1Z2gate.emplace_back(new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2gate%d", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.));
            frs_Z1vsZ2_hists->Add(h2_dEdeg_vs_Z_Z1Z2gate[gate]);
            //hID_dEdegoQ_Z1_Z1Z2gate
            h2_dEdegoQ_vs_Z_Z1Z2gate.emplace_back(new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2gate%d", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.));
            frs_Z1vsZ2_hists->Add(h2_dEdegoQ_vs_Z_Z1Z2gate[gate]);
            //hID_Z1_Z2gate
            h2_Z1_vs_Z2_Z1Z2gate.emplace_back(new TH2I(Form("h2_Z1_vs_Z2_Z1Z2gate%d", gate), Form("Z1 vs. Z2 - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_Z1vsZ2_hists->Add(h2_Z1_vs_Z2_Z1Z2gate[gate]);
            //hID_a2_Z1Z2gate
            h1_a2_Z1Z2gate.emplace_back(new TH1I(Form("h1_a2_Z1Z2gate%d", gate), Form("Angle S2 [mrad] - Z1Z2 Gate: %d", gate), 100, -1000, 1000));
            frs_Z1vsZ2_hists->Add(h1_a2_Z1Z2gate[gate]);
            //hID_a4_Z1Z2gate
            h1_a4_Z1Z2gate.emplace_back(new TH1I(Form("h1_a4_Z1Z2gate%d", gate), Form("Angle S4 [mrad] - Z1Z2 Gate: %d", gate), 100, -1000, 1000));
            frs_Z1vsZ2_hists->Add(h1_a4_Z1Z2gate[gate]);
            //hID_x2AoQ_Z1Z2gate
            h2_x2_vs_AoQ_Z1Z2gate.emplace_back(new TH2I(Form("h2_x2_vs_AoQ_Z1Z2gate%d", gate), Form("x2 vs. A/Q - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_Z1vsZ2_hists->Add(h2_x2_vs_AoQ_Z1Z2gate[gate]);
            //hID_x4AoQ_Z1Z2gate
            h2_x4_vs_AoQ_Z1Z2gate.emplace_back(new TH2I(Form("h2_x4_vs_AoQ_Z1Z2gate%d", gate), Form("x4 vs. A/Q - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_Z1vsZ2_hists->Add(h2_x4_vs_AoQ_Z1Z2gate[gate]);
            //hID_ZAoQ_Z1Z2gate
            h2_Z_vs_AoQ_Z1Z2gate.emplace_back(new TH2I(Form("h2_Z_vs_AoQ_Z1Z2gate%d", gate), Form("Z1 vs. A/Q - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_Z1vsZ2_hists->Add(h2_Z_vs_AoQ_Z1Z2gate[gate]);

            // ------- MHTDC ----------
            //hID_dEdegZ1_Z1Z2gate
            h2_dEdeg_vs_Z_Z1Z2gate_mhtdc.emplace_back(new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2gate%d_mhtdc", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.));
            frs_Z1vsZ2_hists_mhtdc->Add(h2_dEdeg_vs_Z_Z1Z2gate_mhtdc[gate]);
            //hID_dEdegoQ_Z1_Z1Z2gate
            h2_dEdegoQ_vs_Z_Z1Z2gate_mhtdc.emplace_back(new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2gate%d_mhtdc", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.));
            frs_Z1vsZ2_hists_mhtdc->Add(h2_dEdegoQ_vs_Z_Z1Z2gate_mhtdc[gate]);
            //hID_Z1_Z2gate
            h2_Z1_vs_Z2_Z1Z2gate_mhtdc.emplace_back(new TH2I(Form("h2_Z1_vs_Z2_Z1Z2gate%d_mhtdc", gate), Form("Z1 vs. Z2 - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_Z1vsZ2_hists_mhtdc->Add(h2_Z1_vs_Z2_Z1Z2gate_mhtdc[gate]);
            //hID_a2_Z1Z2gate
            h1_a2_Z1Z2gate_mhtdc.emplace_back(new TH1I(Form("h1_a2_Z1Z2gate%d_mhtdc", gate), Form("Angle S2 [mrad] - Z1Z2 Gate: %d", gate), 100, -1000, 1000));
            frs_Z1vsZ2_hists_mhtdc->Add(h1_a2_Z1Z2gate_mhtdc[gate]);
            //hID_a4_Z1Z2gate
            h1_a4_Z1Z2gate_mhtdc.emplace_back(new TH1I(Form("h1_a4_Z1Z2gate%d_mhtdc", gate), Form("Angle S4 [mrad] - Z1Z2 Gate: %d", gate), 100, -1000, 1000));
            frs_Z1vsZ2_hists_mhtdc->Add(h1_a4_Z1Z2gate_mhtdc[gate]);
            //hID_x2AoQ_Z1Z2gate
            h2_x2_vs_AoQ_Z1Z2gate_mhtdc.emplace_back(new TH2I(Form("h2_x2_vs_AoQ_Z1Z2gate%d_mhtdc", gate), Form("x2 vs. A/Q - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_Z1vsZ2_hists_mhtdc->Add(h2_x2_vs_AoQ_Z1Z2gate_mhtdc[gate]);
            //hID_x4AoQ_Z1Z2gate
            h2_x4_vs_AoQ_Z1Z2gate_mhtdc.emplace_back(new TH2I(Form("h2_x4_vs_AoQ_Z1Z2gate%d_mhtdc", gate), Form("x4 vs. A/Q - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_Z1vsZ2_hists_mhtdc->Add(h2_x4_vs_AoQ_Z1Z2gate_mhtdc[gate]);
            //hID_ZAoQ_Z1Z2gate
            h2_Z_vs_AoQ_Z1Z2gate_mhtdc.emplace_back(new TH2I(Form("h2_Z_vs_AoQ_Z1Z2gate%d_mhtdc", gate), Form("Z1 vs. A/Q - Z1Z2 Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_Z1vsZ2_hists_mhtdc->Add(h2_Z_vs_AoQ_Z1Z2gate_mhtdc[gate]);
        }
    }

    if (cutID_x2AoQ[0] != nullptr)
    {
        // x2vsAoQ gates
        for (int gate = 0; gate < cutID_x2AoQ.size(); gate++)
        {
            //hID_x2AoQ_x2AoQgate
            h2_x2_vs_AoQ_x2AoQgate.emplace_back(new TH2I(Form("h2_x2_vs_AoQ_x2AoQgate%d", gate), Form("x2 vs. A/Q - x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_x2vsAoQ_hists->Add(h2_x2_vs_AoQ_x2AoQgate[gate]);
            //hID_Z1Z2_x2AoQgate
            h2_Z1_vs_Z2_x2AoQgate.emplace_back(new TH2I(Form("h2_Z1_vs_Z2_x2AoQgate%d", gate), Form("Z1 vs. Z2 - x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_x2vsAoQ_hists->Add(h2_Z1_vs_Z2_x2AoQgate[gate]);

            // ------ MHTDC --------
            //hID_x2AoQ_x2AoQgate
            h2_x2_vs_AoQ_x2AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_x2_vs_AoQ_x2AoQgate%d_mhtdc", gate), Form("x2 vs. A/Q - x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_x2vsAoQ_hists_mhtdc->Add(h2_x2_vs_AoQ_x2AoQgate_mhtdc[gate]);
            //hID_Z1Z2_x2AoQgate
            h2_Z1_vs_Z2_x2AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_Z1_vs_Z2_x2AoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_x2vsAoQ_hists_mhtdc->Add(h2_Z1_vs_Z2_x2AoQgate_mhtdc[gate]);

            if (cutID_Z_Z2[0] != nullptr)
            {
                //hID_x2AoQ_Z1Z2x2AoQgate
                h2_x2_vs_AoQ_Z1Z2x2AoQgate.emplace_back(new TH2I(Form("h2_x2_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
                frs_x2vsAoQ_Z1vsZ2_hists->Add(h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate]);
                //hID_x4AoQ_Z1Z2x2AoQgate
                h2_x4_vs_AoQ_Z1Z2x2AoQgate.emplace_back(new TH2I(Form("h2_x4_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
                frs_x2vsAoQ_Z1vsZ2_hists->Add(h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate]);
                //hID_ZAoQ_Z1Z2x2AoQgate
                h2_Z_vs_AoQ_Z1Z2x2AoQgate.emplace_back(new TH2I(Form("h2_Z_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("Z1 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
                frs_x2vsAoQ_Z1vsZ2_hists->Add(h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate]);
                //hID_dEdegZ1_Z1Z2x2AoQgate
                h2_dEdeg_vs_Z_Z1Z2x2AoQgate.emplace_back(new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2x2AoQgate%d", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.));
                frs_x2vsAoQ_Z1vsZ2_hists->Add(h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate]);
                //hID_dEdegoQ_Z1_Z1Z2x2AoQgate
                h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate.emplace_back(new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate%d", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.));
                frs_x2vsAoQ_Z1vsZ2_hists->Add(h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate]);
                //hID_a2_Z1Z2x2AoQgate
                h1_a2_Z1Z2x2AoQgate.emplace_back(new TH1I(Form("h1_a2_Z1Z2x2AoQgate%d", gate), Form("Angle S2 [mrad] - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 100, -1000, 1000));
                frs_x2vsAoQ_Z1vsZ2_hists->Add(h1_a2_Z1Z2x2AoQgate[gate]);
                //hID_a4_Z1Z2x2AoQgate
                h1_a4_Z1Z2x2AoQgate.emplace_back(new TH1I(Form("h1_a4_Z1Z2x2AoQgate%d", gate), Form("Angle S4 [mrad] - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 100, -1000, 1000));
                frs_x2vsAoQ_Z1vsZ2_hists->Add(h1_a4_Z1Z2x2AoQgate[gate]);

                // ----- MHTDC ---------
                //hID_x2AoQ_Z1Z2x2AoQgate
                h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_x2_vs_AoQ_Z1Z2x2AoQgate%d_mhtdc", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
                frs_x2vsAoQ_Z1vsZ2_hists_mhtdc->Add(h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate]);
                //hID_x4AoQ_Z1Z2x2AoQgate
                h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_x4_vs_AoQ_Z1Z2x2AoQgate%d_mhtdc", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
                frs_x2vsAoQ_Z1vsZ2_hists_mhtdc->Add(h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate]);
                //hID_ZAoQ_Z1Z2x2AoQgate
                h2_Z_vs_AoQ_Z1Z2x2AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_Z_vs_AoQ_Z1Z2x2AoQgate%d_mhtdc", gate), Form("Z1 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
                frs_x2vsAoQ_Z1vsZ2_hists_mhtdc->Add(h2_Z_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate]);
                //hID_Z1Z2_Z1Z2x2AoQgate_mhtdc
                h2_Z1_vs_Z2_Z1Z2x2AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_Z1_vs_Z2_Z1Z2x2AoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
                frs_x2vsAoQ_Z1vsZ2_hists_mhtdc->Add(h2_Z1_vs_Z2_Z1Z2x2AoQgate_mhtdc[gate]);
                //hID_dEdegZ1_Z1Z2x2AoQgate
                h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2x2AoQgate%d_mhtdc", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.));
                frs_x2vsAoQ_Z1vsZ2_hists_mhtdc->Add(h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc[gate]);
                //hID_dEdegoQ_Z1_Z1Z2x2AoQgate
                h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate%d_mhtdc", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.));
                frs_x2vsAoQ_Z1vsZ2_hists_mhtdc->Add(h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc[gate]);
                //hID_a2_Z1Z2x2AoQgate
                h1_a2_Z1Z2x2AoQgate_mhtdc.emplace_back(new TH1I(Form("h1_a2_Z1Z2x2AoQgate%d_mhtdc", gate), Form("Angle S2 [mrad] - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 100, -1000, 1000));
                frs_x2vsAoQ_Z1vsZ2_hists_mhtdc->Add(h1_a2_Z1Z2x2AoQgate_mhtdc[gate]);
                //hID_a4_Z1Z2x2AoQgate
                h1_a4_Z1Z2x2AoQgate_mhtdc.emplace_back(new TH1I(Form("h1_a4_Z1Z2x2AoQgate%d_mhtdc", gate), Form("Angle S4 [mrad] - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 100, -1000, 1000));
                frs_x2vsAoQ_Z1vsZ2_hists_mhtdc->Add(h1_a4_Z1Z2x2AoQgate_mhtdc[gate]);
            }     
        }
    }
    
    if (cutID_x4AoQ[0] != nullptr)
    {
        // x4vsAoQ gate
        for (int gate = 0; gate < cutID_x4AoQ.size(); gate++)
        {
            //hID_x4AoQ_x4AoQgate
            h2_x4_vs_AoQ_x4AoQgate.emplace_back(new TH2I(Form("h2_x4_vs_AoQ_x4AoQgate%d", gate), Form("x4 vs. A/Q - x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_x4vsAoQ_hists->Add(h2_x4_vs_AoQ_x4AoQgate[gate]);
            //hID_Z1Z2_x4AoQgate
            h2_Z1_vs_Z2_x4AoQgate.emplace_back(new TH2I(Form("h2_Z1_vs_Z2_x4AoQgate%d", gate), Form("Z1 vs. Z2 - x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_x4vsAoQ_hists->Add(h2_Z1_vs_Z2_x4AoQgate[gate]);

            // ------ MHTDC --------
            //hID_x4AoQ_x4AoQgate
            h2_x4_vs_AoQ_x4AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_x4_vs_AoQ_x4AoQgate%d_mhtdc", gate), Form("x4 vs. A/Q - x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_x4vsAoQ_hists_mhtdc->Add(h2_x4_vs_AoQ_x4AoQgate_mhtdc[gate]);
            //hID_Z1Z2_x4AoQgate
            h2_Z1_vs_Z2_x4AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_Z1_vs_Z2_x4AoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_x4vsAoQ_hists_mhtdc->Add(h2_Z1_vs_Z2_x4AoQgate_mhtdc[gate]);

            if (cutID_Z_Z2[0] != nullptr)
            {
                //hID_x2AoQ_Z1Z2x4AoQgate
                h2_x2_vs_AoQ_Z1Z2x4AoQgate.emplace_back(new TH2I(Form("h2_x2_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
                frs_x4vsAoQ_Z1vsZ2_hists->Add(h2_x2_vs_AoQ_Z1Z2x4AoQgate[gate]);
                //hID_x4AoQ_Z1Z2x4AoQgate
                h2_x4_vs_AoQ_Z1Z2x4AoQgate.emplace_back(new TH2I(Form("h2_x4_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
                frs_x4vsAoQ_Z1vsZ2_hists->Add(h2_x4_vs_AoQ_Z1Z2x4AoQgate[gate]);
                //hID_ZAoQ_Z1Z2x4AoQgate
                h2_Z_vs_AoQ_Z1Z2x4AoQgate.emplace_back(new TH2I(Form("h2_Z_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("Z1 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
                frs_x4vsAoQ_Z1vsZ2_hists->Add(h2_Z_vs_AoQ_Z1Z2x4AoQgate[gate]);
                //hID_dEdegZ1_Z1Z2x4AoQgate -- CEJ: limits for sure defined incorrectly in Go4
                h2_dEdeg_vs_Z_Z1Z2x4AoQgate.emplace_back(new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2x4AoQgate%d", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.));
                frs_x4vsAoQ_Z1vsZ2_hists->Add(h2_dEdeg_vs_Z_Z1Z2x4AoQgate[gate]);
                //hID_dEdegoQ_Z1_Z1Z2x4AoQgate -- CEJ: same as above
                h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate.emplace_back(new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate%d", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.));
                frs_x4vsAoQ_Z1vsZ2_hists->Add(h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[gate]);
                //hID_a2_Z1Z2x4AoQgate
                h1_a2_Z1Z2x4AoQgate.emplace_back(new TH1I(Form("h1_a2_Z1Z2x4AoQgate%d", gate), Form("Angle S2 [mrad] - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 100, -1000, 1000));
                frs_x4vsAoQ_Z1vsZ2_hists->Add(h1_a2_Z1Z2x4AoQgate[gate]);
                //hID_a4_Z1Z2x4AoQgate
                h1_a4_Z1Z2x4AoQgate.emplace_back(new TH1I(Form("h1_a4_Z1Z2x4AoQgate%d", gate), Form("Angle S4 [mrad] - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 100, -1000, 1000));
                frs_x4vsAoQ_Z1vsZ2_hists->Add(h1_a4_Z1Z2x4AoQgate[gate]);

                // -------- MHTDC -----------
                //hID_x2AoQ_Z1Z2x4AoQgate
                h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_x2_vs_AoQ_Z1Z2x4AoQgate%d_mhtdc", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
                frs_x4vsAoQ_Z1vsZ2_hists_mhtdc->Add(h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate]);
                //hID_x4AoQ_Z1Z2x4AoQgate
                h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_x4_vs_AoQ_Z1Z2x4AoQgate%d_mhtdc", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
                frs_x4vsAoQ_Z1vsZ2_hists_mhtdc->Add(h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate]);
                //hID_Z1Z2_Z1Z2x4AoQgate
                h2_Z1_vs_Z2_Z1Z2x4AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_Z1_vs_Z2_Z1Z2x4AoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
                frs_x4vsAoQ_Z1vsZ2_hists_mhtdc->Add(h2_Z1_vs_Z2_Z1Z2x4AoQgate_mhtdc[gate]);
                //hID_dEdegZ1_Z1Z2x4AoQgate -- CEJ: limits for sure defined incorrectly in Go4
                h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_dEdeg_vs_Z_Z1Z2x4AoQgate%d_mhtdc", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.));
                frs_x4vsAoQ_Z1vsZ2_hists_mhtdc->Add(h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc[gate]);
                //hID_dEdegoQ_Z1_Z1Z2x4AoQgate -- CEJ: same as above
                h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc.emplace_back(new TH2I(Form("h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate%d_mhtdc", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.));
                frs_x4vsAoQ_Z1vsZ2_hists_mhtdc->Add(h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc[gate]);
                //hID_a2_Z1Z2x4AoQgate
                h1_a2_Z1Z2x4AoQgate_mhtdc.emplace_back(new TH1I(Form("h1_a2_Z1Z2x4AoQgate%d_mhtdc", gate), Form("Angle S2 [mrad] - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 100, -1000, 1000));
                frs_x4vsAoQ_Z1vsZ2_hists_mhtdc->Add(h1_a2_Z1Z2x4AoQgate_mhtdc[gate]);
                //hID_a4_Z1Z2x4AoQgate
                h1_a4_Z1Z2x4AoQgate_mhtdc.emplace_back(new TH1I(Form("h1_a4_Z1Z2x4AoQgate%d_mhtdc", gate), Form("Angle S4 [mrad] - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 100, -1000, 1000));
                frs_x4vsAoQ_Z1vsZ2_hists_mhtdc->Add(h1_a4_Z1Z2x4AoQgate_mhtdc[gate]);
            } 
        }
    }
    

    if (cutID_dEdegZ[0] != nullptr)
    {
        // dEdegZ gates
        for (int gate = 0; gate < cutID_dEdegZ.size(); gate++) 
        {
            //hID_Z1AoQ_dEdegZgate
            h2_Z_vs_AoQ_dEdegZgate.emplace_back(new TH2I(Form("h2_Z_vs_AoQ_dEdegZgate%d", gate), Form("Z1 vs. A/Q - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_dEdegvsZ_hists->Add(h2_Z_vs_AoQ_dEdegZgate[gate]);
            //hID_Z1Z2_dEdegZgate
            h2_Z1_vs_Z2_dEdegZgate.emplace_back(new TH2I(Form("h2_Z1_vs_Z2_dEdegZgate%d", gate), Form("Z1 vs. Z2 - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_dEdegvsZ_hists->Add(h2_Z1_vs_Z2_dEdegZgate[gate]);
            //hID_x2AoQ_dEdegZgate
            h2_x2_vs_AoQ_dEdegZgate.emplace_back(new TH2I(Form("h2_x2_vs_AoQ_dEdegZgate%d", gate), Form("x2 vs. A/Q - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_dEdegvsZ_hists->Add(h2_x2_vs_AoQ_dEdegZgate[gate]);
            //hID_x4AoQ_dEdegZgate
            h2_x4_vs_AoQ_dEdegZgate.emplace_back(new TH2I(Form("h2_x4_vs_AoQ_dEdegZgate%d", gate), Form("x4 vs. A/Q - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_dEdegvsZ_hists->Add(h2_x4_vs_AoQ_dEdegZgate[gate]);
            //hID_a2_dEdegZgate
            h1_a2_dEdegZgate.emplace_back(new TH1I(Form("h1_a2_dEdegZgate%d", gate), Form("Angle S2 [mrad] - dEdegZ Gate: %d", gate), 100, -1000, 1000));
            frs_dEdegvsZ_hists->Add(h1_a2_dEdegZgate[gate]);
            //hID_a4_dEdegZgate
            h1_a4_dEdegZgate.emplace_back(new TH1I(Form("h1_a4_dEdegZgate%d", gate), Form("Angle S4 [mrad] - dEdegZ Gate: %d", gate), 100, -1000, 1000));
            frs_dEdegvsZ_hists->Add(h1_a4_dEdegZgate[gate]);
            //hID_Z1AoQ_zsame_dEdegZgate
            h2_Z_vs_AoQ_Zsame_dEdegZgate.emplace_back(new TH2I(Form("h2_Z_vs_AoQ_Zsame_dEdegZgate%d", gate), Form("Z vs. A/Q [ABS(Z1 - Z2) < 0.4] - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_dEdegvsZ_hists->Add(h2_Z_vs_AoQ_Zsame_dEdegZgate[gate]);

            // ------- MHTDC -----------------
            // hID_dEdegZ1_dEdegZ1Gated_mhtdc
            h2_Z_vs_dEdeg_dEdegZgate_mhtdc.emplace_back(new TH2I(Form("h2_Z_vs_dEdeg_dEdegZgate%d_mhtdc", gate), Form("Z1 vs. dE in S2 degrader - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, 10., 100.));
            frs_dEdegvsZ_hists_mhtdc->Add(h2_Z_vs_dEdeg_dEdegZgate_mhtdc[gate]);
            //hID_Z1AoQ_dEdegZgate
            h2_Z_vs_AoQ_dEdegZgate_mhtdc.emplace_back(new TH2I(Form("h2_Z_vs_AoQ_dEdegZgate%d_mhtdc", gate), Form("Z1 vs. A/Q - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_dEdegvsZ_hists_mhtdc->Add(h2_Z_vs_AoQ_dEdegZgate_mhtdc[gate]);
            //hID_Z1Z2_dEdegZgate
            h2_Z1_vs_Z2_dEdegZgate_mhtdc.emplace_back(new TH2I(Form("h2_Z1_vs_Z2_dEdegZgate%d_mhtdc", gate), Form("Z1 vs. Z2 - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_dEdegvsZ_hists_mhtdc->Add(h2_Z1_vs_Z2_dEdegZgate_mhtdc[gate]);
            //hID_x2AoQ_dEdegZgate
            h2_x2_vs_AoQ_dEdegZgate_mhtdc.emplace_back(new TH2I(Form("h2_x2_vs_AoQ_dEdegZgate%d_mhtdc", gate), Form("x2 vs. A/Q - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_dEdegvsZ_hists_mhtdc->Add(h2_x2_vs_AoQ_dEdegZgate_mhtdc[gate]);
            //hID_x4AoQ_dEdegZgate
            h2_x4_vs_AoQ_dEdegZgate_mhtdc.emplace_back(new TH2I(Form("h2_x4_vs_AoQ_dEdegZgate%d_mhtdc", gate), Form("x4 vs. A/Q - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, 200, -100., 100.));
            frs_dEdegvsZ_hists_mhtdc->Add(h2_x4_vs_AoQ_dEdegZgate_mhtdc[gate]);
            //hID_a2_dEdegZgate
            h1_a2_dEdegZgate_mhtdc.emplace_back(new TH1I(Form("h1_a2_dEdegZgate%d_mhtdc", gate), Form("Angle S2 [mrad] - dEdegZ Gate: %d", gate), 100, -1000, 1000));
            frs_dEdegvsZ_hists_mhtdc->Add(h1_a2_dEdegZgate_mhtdc[gate]);
            //hID_a4_dEdegZgate
            h1_a4_dEdegZgate_mhtdc.emplace_back(new TH1I(Form("h1_a4_dEdegZgate%d_mhtdc", gate), Form("Angle S4 [mrad] - dEdegZ Gate: %d", gate), 100, -1000, 1000));
            frs_dEdegvsZ_hists_mhtdc->Add(h1_a4_dEdegZgate_mhtdc[gate]);
            //hID_Z1AoQ_zsame_dEdegZgate
            h2_Z_vs_AoQ_Zsame_dEdegZgate_mhtdc.emplace_back(new TH2I(Form("h2_Z_vs_AoQ_Zsame_dEdegZgate%d_mhtdc", gate), Form("Z vs. A/Q [ABS(Z1 - Z2) < 0.4] - dEdegZ Gate: %d", gate), FRS_HISTO_BIN, id->min_aoq_plot, 3.0, FRS_HISTO_BIN, id->min_z_plot, id->max_z_plot));
            frs_dEdegvsZ_hists_mhtdc->Add(h2_Z_vs_AoQ_Zsame_dEdegZgate_mhtdc[gate]);
        }
    }

    return kSUCCESS;

}

void FrsAnalysisSpectra::Exec(Option_t* option)
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

            if (cutID_Z_AoQ[0] != nullptr)
            {   
                for (int gate = 0; gate < cutID_Z_AoQ.size(); gate++)
                {   
                    if (cutID_Z_AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z()))
                    {
                        h2_Z_vs_AoQ_ZAoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                        h2_Z1_vs_Z2_ZAoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
                        h2_x2_vs_AoQ_ZAoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                        h2_x4_vs_AoQ_ZAoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                        h2_dEdeg_vs_Z_ZAoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdeg());
                        h2_dedegoQ_vs_Z_ZAoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdegoQ());
                        h1_a2_ZAoQ_gate[gate]->Fill(FrsHit->Get_ID_a2());
                        h1_a4_ZAoQ_gate[gate]->Fill(FrsHit->Get_ID_a4());
                    }
                }
            }

            // Z1 vs Z2
            if (cutID_Z_Z2[0] != nullptr)
            {
                for (int gate = 0; gate < cutID_Z_Z2.size(); gate++)
                {
                    if(cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                    {

                        h2_dEdeg_vs_Z_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_z(),FrsHit->Get_ID_dEdeg());
                        h2_dEdegoQ_vs_Z_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_z(),FrsHit->Get_ID_dEdegoQ());
                        h2_Z1_vs_Z2_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_z(),FrsHit->Get_ID_z2());
                        h1_a2_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_a2());
                        h1_a4_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_a4());
                        // CEJ: this is so weird
                        if(FrsHit->Get_ID_AoQ() > 1 && FrsHit->Get_ID_AoQ() < 3 && FrsHit->Get_ID_x2() > -100 && FrsHit->Get_ID_x2() < 100) h2_x2_vs_AoQ_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                        if(FrsHit->Get_ID_AoQ() > 1 && FrsHit->Get_ID_AoQ() < 3 && FrsHit->Get_ID_x4() > -100 && FrsHit->Get_ID_x4() < 100) h2_x4_vs_AoQ_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                        if(FrsHit->Get_ID_AoQ() > 1 && FrsHit->Get_ID_AoQ() < 3) h2_Z_vs_AoQ_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                    }
                }
            }

            // x2 vs AoQ
            if (cutID_x2AoQ[0] != nullptr)
            {   
                for (int gate = 0; gate < cutID_x2AoQ.size(); gate++)
                {
                    if(cutID_x2AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2()))
                    {
                        h2_x2_vs_AoQ_x2AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                        h2_Z1_vs_Z2_x2AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
                        
                        // Z1 Z2 + x2AoQ
                        if (cutID_Z_Z2[0] != nullptr)
                        {   
                            if(cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                            {

                                h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                                h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                                h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                                h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdeg());
                                h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdegoQ());
                                h1_a2_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_a2());
                                h1_a4_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_a4()); 
                            }
                        }
                    }
                }
            }

            // x4 vs AoQ
            if (cutID_x4AoQ[0] != nullptr)
            {   
                for (int gate = 0; gate < cutID_x4AoQ.size(); gate++)
                {
                    if(cutID_x4AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4()))
                    { 
                        h2_x4_vs_AoQ_x4AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                        h2_Z1_vs_Z2_x4AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
                        
                        ///Z1 Z2 + x4AoQ
                        if (cutID_Z_Z2[0] != nullptr)
                        {
                            if(cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                            {
                                h2_x2_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                                h2_x4_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                                h2_Z_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                                h2_dEdeg_vs_Z_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdeg());
                                h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdegoQ());
                                h1_a2_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_a2());
                                h1_a4_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_a4());
                            }
                        }
                    }
                }
            }

            // GATE: Energy loss S2 vs Z (Charge states)
            if (cutID_dEdegZ[0] != nullptr)
            {   
                for (int gate = 0; gate < cutID_dEdegZ.size(); gate++)
                {
                    if(cutID_dEdegZ[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_dEdeg()))
                    {
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
            if (cutID_Z_AoQ[0] != nullptr)
            {
                for(int gate = 0; gate < cutID_Z_AoQ.size(); gate++)
                {
                    for (int i = 0; i < MAX_MHTDC_MULT; i++)
                    {
                        if(cutID_Z_AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i)))
                        {   
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
                    }
                }
            }

            // Z1 vs Z2
            if (cutID_Z_Z2[0] != nullptr)
            {
                for(int gate = 0; gate < cutID_Z_Z2.size(); gate++)
                {
                    for (int i = 0; i < MAX_MHTDC_MULT; i++)
                    {
                        if(cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i)))
                        {
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
                    }
                }
            }

            // ID x2 vs AoQ
            if (cutID_x2AoQ[0] != nullptr)
            {
                for(int gate = 0; gate < cutID_x2AoQ.size(); gate++)
                {
                    for (int i = 0; i < MAX_MHTDC_MULT; i++)
                    {
                        if(cutID_x2AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2()))
                        {
                            h2_x2_vs_AoQ_x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                            h2_Z1_vs_Z2_x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                            // The selected Z1 Z2 gate for this part can be found in the Correlations_config.dat file
                            // Z1 Z2 +X2 AoQ
                            if (cutID_Z_Z2[0] != nullptr)
                            {
                                if(cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i)))
                                {
                                    h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                                    h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                                    h2_Z1_vs_Z2_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                                    h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdeg_mhtdc(i));
                                    h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdegoQ_mhtdc(i));
                                    h1_a2_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a2());
                                    h1_a4_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a4());
                                }
                            }
                        }
                    }
                }
            }
            
            // ID x4 vs AoQ
            if (cutID_x4AoQ[0] != nullptr)
            {
                for(int gate = 0; gate < cutID_x4AoQ.size(); gate++)
                {
                    for (int i = 0; i < MAX_MHTDC_MULT; i++)
                    {
                        if(cutID_x4AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4()))
                        {   
                            h2_x4_vs_AoQ_x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                            h2_Z1_vs_Z2_x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                            // Z1 Z2 +X4 AoQ
                            if (cutID_Z_Z2[0] != nullptr)
                            {
                                if(cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i)))
                                {
                                    h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                                    h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                                    h2_Z1_vs_Z2_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                                    h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdeg_mhtdc(i));
                                    h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdegoQ_mhtdc(i));
                                    h1_a2_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a2());
                                    h1_a4_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a4());
                                    
                                }
                            }
                        }
                    }
                }
            }

            // GATE: Energy loss S2 vs Z (Charge states)
            if (cutID_dEdegZ[0] != nullptr)
            {
                for(int gate = 0; gate < cutID_dEdegZ.size(); gate++)
                {
                    for (int i = 0; i < MAX_MHTDC_MULT; i++)
                    {
                        if (cutID_dEdegZ[gate]->IsInside(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdeg()))
                        {
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

void FrsAnalysisSpectra::FinishEvent()
{
    // clear any arrays/vectors if needed
    
}

void FrsAnalysisSpectra::FinishTask()
{
    c4LOG(info, "Writing FRS analysis histograms to file.");
    //frs_analysis_hists->Write();
}

ClassImp(FrsAnalysisSpectra)
