// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "TPCCorrections.h"
#include "FrsHitData.h"
#include "FrsMainCalData.h"
#include "FrsTPCData.h"
#include "FrsTPCCalData.h"
#include "FrsUserCalData.h"
#include "FrsHitData.h"
#include "EventHeader.h"
#include "c4Logger.h"


// ROOT
#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TDirectory.h"

#include "TRandom3.h"

Float_t TPCCorrections::rand3()
{
    return random3.Uniform(-0.5,0.5);
}

TPCCorrections::TPCCorrections()
    : TPCCorrections("TPCCorrections", 1)
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

TPCCorrections::TPCCorrections(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   fNEvents(0)
    ,   header(nullptr)
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

TPCCorrections::~TPCCorrections()
{
    c4LOG(info, "");
    
}

InitStatus TPCCorrections::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    // also needs TPC raw I think
    mainScalerArray = mgr->InitObjectAs<decltype(mainScalerArray)>("FrsMainCalScalerData");
    c4LOG_IF(fatal, !mainScalerArray, "Branch FrsMainCalScalerData not found!");
    mainSciArray = mgr->InitObjectAs<decltype(mainSciArray)>("FrsMainCalSciData");
    c4LOG_IF(fatal, !mainSciArray, "Branch FrsMainCalSciData not found!");
    mainMusicArray = mgr->InitObjectAs<decltype(mainMusicArray)>("FrsMainCalMusicData");
    c4LOG_IF(fatal, !mainMusicArray, "Branch FrsMainCalMusicData not found!");
    tpcCalArray = mgr->InitObjectAs<decltype(tpcCalArray)>("FrsTPCCalData");
    c4LOG_IF(fatal, !tpcCalArray, "Branch FrsTPCCalData not found!");
    userScalerArray = mgr->InitObjectAs<decltype(userScalerArray)>("FrsUserCalScalerData");
    c4LOG_IF(fatal, !userScalerArray, "Branch FrsUserCalScalerData not found!");
    userSciArray = mgr->InitObjectAs<decltype(userSciArray)>("FrsUserCalSciData");
    c4LOG_IF(fatal, !userSciArray, "Branch FrsUserCalSciData not found!");
    userMusicArray = mgr->InitObjectAs<decltype(userMusicArray)>("FrsUserCalMusicData");
    c4LOG_IF(fatal, !userMusicArray, "Branch FrsUserCalMusicData not found!");
    tpatArray = mgr->InitObjectAs<decltype(tpatArray)>("FrsTpatData");
    c4LOG_IF(fatal, !tpatArray, "Branch FrsTpatData not found!");


    hitArray = mgr->InitObjectAs<decltype(hitArray)>("FrsHitData");
    c4LOG_IF(fatal, !hitArray, "Branch FrsHitData not found!");



    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    // look for FRS directory, create it if not found
    dir_frs = (TDirectory*)mgr->GetObject("TPC corrections");
    if (dir_frs == nullptr) 
    {
        LOG(info) << "Creating TPC corrections Online Directory";
        dir_frs = new TDirectory("TPC corrections Online", "TPC corrections Online", "", 0);
        mgr->Register("TPC corrections", "TPC corrections Online Directory", dir_frs, false); // allow other tasks to find this
        histograms->Add(dir_frs);
    }

    //Main crate detectors:

    dir_frs->cd();


    h_sci_21l_21r_dt = new TH1D("h_sci_21l_21r_dt", "h_sci_21l_21r_dt", 2000,-1000,1000);
    h_sci_22l_22r_dt = new TH1D("h_sci_22l_22r_dt", "h_sci_22l_22r_dt", 2000,-1000,1000);
    h_sci_41l_41r_dt = new TH1D("h_sci_41l_41r_dt", "h_sci_41l_41r_dt", 2000,-1000,1000);
    h_sci_42l_42r_dt = new TH1D("h_sci_42l_42r_dt", "h_sci_42l_42r_dt", 2000,-1000,1000);

    //dx:
    h_sci21_x = new TH1D("h_sci21_x", "h_sci21_x", 2000,-1000,1000);
    h_sci22_x = new TH1D("h_sci22_x", "h_sci22_x", 2000,-1000,1000);
    h_sci41_x = new TH1D("h_sci41_x", "h_sci41_x", 2000,-1000,1000);
    h_sci42_x = new TH1D("h_sci42_x", "h_sci42_x", 2000,-1000,1000);


    h_sci21_tpc_x = new TH2D("h_sci21_tpc_x","h_sci21_tpc_x",2000,-50,50,2000,-200,200);
    h_sci22_tpc_x = new TH2D("h_sci22_tpc_x","h_sci22_tpc_x",2000,-50,50,2000,-200,200);
    h_sci42_tpc_x = new TH2D("h_sci42_tpc_x","h_sci42_tpc_x",2000,-50,50,2000,-200,200);
    h_sci41_tpc_x = new TH2D("h_sci41_tpc_x","h_sci41_tpc_x",2000,-50,50,2000,-200,200);


    //dx:
    h_sci21_tpc_x_tac = new TH2D("h_sci21_tpc_x_tac","h_sci21_tpc_x_tac",2000,500,2500,2000,-200,200);
    h_sci22_tpc_x_tac = new TH2D("h_sci22_tpc_x_tac","h_sci22_tpc_x_tac",2000,500,2500,2000,-200,200);
    h_sci42_tpc_x_tac = new TH2D("h_sci42_tpc_x_tac","h_sci42_tpc_x_tac",2000,500,2500,2000,-200,200);
    h_sci41_tpc_x_tac = new TH2D("h_sci41_tpc_x_tac","h_sci41_tpc_x_tac",2000,500,2500,2000,-200,200);
    
    h_music41_x = new TH2D("h_music41_x","h_music41_x",2000,-200,200,1000,2000,3000);
    h_music42_x = new TH2D("h_music42_x","h_music42_x",2000,-200,200,1000,2000,3000);

    
    h_music41_x_cor = new TH2D("h_music41_x_cor","h_music41_x_cor",2000,-200,200,1000,2000,3000);
    h_music42_x_cor = new TH2D("h_music42_x_cor","h_music42_x_cor",2000,-200,200,1000,2000,3000);

    


    return kSUCCESS;

}

void TPCCorrections::Reset_Histo()
{
    c4LOG(info, "");
    // incoming
}

void TPCCorrections::Exec(Option_t* option)
{   
    int hits = mainSciArray->size();

    if (mainSciArray->size() < 1 || tpcCalArray->size() < 1 || hitArray->size() < 1) return;

    auto const & mainSciItem  = mainSciArray->at(0);
    auto const & tpcCalItem = tpcCalArray->at(0);
    auto const & hitItem = hitArray->at(0);

    
    // SCI 21 L and R
    int hits_in_21lr = mainSciItem.Get_mhtdc_sc21l_nr_hits()*mainSciItem.Get_mhtdc_sc21r_nr_hits();
    for (int i = 0; i < mainSciItem.Get_mhtdc_sc21l_nr_hits(); i++)
    {
        for (int j = 0; j < mainSciItem.Get_mhtdc_sc21r_nr_hits(); j ++){
            double sci_21l_21r_dt = ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc21l_hit(i) - mainSciItem.Get_mhtdc_sc21r_hit(j));
            h_sci_21l_21r_dt->Fill(sci_21l_21r_dt);
            h_sci21_x->Fill(sci_21l_21r_dt * mhtdc_factor_21l_21r + mhtdc_offset_21l_21r);
            h_sci21_tpc_x->Fill(sci_21l_21r_dt,tpcCalItem.Get_tpc21_22_sc21_x());
        }
    }

    // SCI 22 L and R
    int hits_in_22lr = mainSciItem.Get_mhtdc_sc22l_nr_hits()*mainSciItem.Get_mhtdc_sc22r_nr_hits();
    for (int i = 0; i < mainSciItem.Get_mhtdc_sc22l_nr_hits(); i++)
    {
        for (int j = 0; j < mainSciItem.Get_mhtdc_sc22r_nr_hits(); j ++){
            double sci_22l_22r_dt = ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc22l_hit(i) - mainSciItem.Get_mhtdc_sc22r_hit(j));
            h_sci_22l_22r_dt->Fill(sci_22l_22r_dt);
            h_sci22_x->Fill(sci_22l_22r_dt * mhtdc_factor_22l_22r + mhtdc_offset_22l_22r);
            h_sci22_tpc_x->Fill(sci_22l_22r_dt,tpcCalItem.Get_tpc21_22_sc22_x());
        

        }
    }

    

    // SCI 41 L and R
    int hits_in_41lr = mainSciItem.Get_mhtdc_sc41l_nr_hits()*mainSciItem.Get_mhtdc_sc41r_nr_hits();
    for (int i = 0; i < mainSciItem.Get_mhtdc_sc41l_nr_hits(); i++)
    {
        for (int j = 0; j < mainSciItem.Get_mhtdc_sc41r_nr_hits(); j ++){
            double sci_41l_41r_dt = ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc41l_hit(i) - mainSciItem.Get_mhtdc_sc41r_hit(j));
            h_sci_41l_41r_dt->Fill(sci_41l_41r_dt);
            h_sci41_x->Fill(sci_41l_41r_dt * mhtdc_factor_41l_41r + mhtdc_offset_41l_41r);
            h_sci41_tpc_x->Fill(sci_41l_41r_dt,tpcCalItem.Get_tpc_sc41_x());

        }
    }


    // SCI 42 L and R
    int hits_in_42lr = mainSciItem.Get_mhtdc_sc42l_nr_hits()*mainSciItem.Get_mhtdc_sc42r_nr_hits();
    for (int i = 0; i < mainSciItem.Get_mhtdc_sc42l_nr_hits(); i++)
    {
        for (int j = 0; j < mainSciItem.Get_mhtdc_sc42r_nr_hits(); j ++){
            double sci_42l_42r_dt = ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc42l_hit(i) - mainSciItem.Get_mhtdc_sc42r_hit(j));
            h_sci_42l_42r_dt->Fill(sci_42l_42r_dt);
            h_sci42_x->Fill(sci_42l_42r_dt * mhtdc_factor_42l_42r + mhtdc_offset_42l_42r);
            h_sci42_tpc_x->Fill(sci_42l_42r_dt,tpcCalItem.Get_tpc_sc42_x());
        }
    }

    
    h_music41_x_cor->Fill(tpcCalItem.Get_tpc_music41_x(),hitItem.Get_music_dE_cor(0));
    h_music42_x_cor->Fill(tpcCalItem.Get_tpc_music42_x(),hitItem.Get_music_dE_cor(1));
    h_music41_x->Fill(tpcCalItem.Get_tpc_music41_x(),hitItem.Get_music_dE(0));
    h_music42_x->Fill(tpcCalItem.Get_tpc_music42_x(),hitItem.Get_music_dE(1));

    if (userSciArray->size() <= 0) return;
    auto const & userSciItem = userSciArray->at(0);


    double dt_21l_21r = userSciItem.Get_dt_index(0);
    double dt_41l_41r = userSciItem.Get_dt_index(1);
    double dt_42l_42r = userSciItem.Get_dt_index(2);
    double dt_22l_22r = userSciItem.Get_dt_index(11);

    h_sci21_tpc_x_tac->Fill(dt_21l_21r,tpcCalItem.Get_tpc21_22_sc21_x());
    h_sci22_tpc_x_tac->Fill(dt_22l_22r,tpcCalItem.Get_tpc21_22_sc22_x());
    h_sci42_tpc_x_tac->Fill(dt_41l_41r,tpcCalItem.Get_tpc_sc41_x());
    h_sci41_tpc_x_tac->Fill(dt_42l_42r,tpcCalItem.Get_tpc_sc42_x());




    fNEvents += 1;

}

void TPCCorrections::FinishEvent()
{
}

void TPCCorrections::FinishTask()
{
    
}

ClassImp(TPCCorrections)
