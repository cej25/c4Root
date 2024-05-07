// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsCalSpectra.h"
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

FrsCalSpectra::FrsCalSpectra()
    : FrsCalSpectra("FrsCalSpectra", 1)
{
}

FrsCalSpectra::FrsCalSpectra(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   mainScalerArray(nullptr)
    ,   mainSciArray(nullptr)
    ,   mainMusicArray(nullptr)
    ,   tpcCalArray(nullptr)
    ,   userScalerArray(nullptr)
    ,   userSciArray(nullptr)
    ,   userMusicArray(nullptr)
    ,   tpatArray(nullptr)
{
}

FrsCalSpectra::~FrsCalSpectra()
{
    c4LOG(info, "");
    
}

InitStatus FrsCalSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    // also needs TPC raw I think
    v7x5array = mgr->InitObjectAs<decltype(v7x5array)>("FrsTPCV7X5Data");
    c4LOG_IF(fatal, !v7x5array, "Branch v7x5array not found!");
    v1190array = mgr->InitObjectAs<decltype(v1190array)>("FrsTPCV1190Data");
    c4LOG_IF(fatal, !v1190array, "Branch v1190array not found!");
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

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    // look for FRS directory, create it if not found
    dir_frs = (TDirectory*)mgr->GetObject("FRS");
    if (dir_frs == nullptr) 
    {
        LOG(info) << "Creating FRS Online Directory";
        dir_frs = new TDirectory("FRS Online", "FRS Online", "", 0);
        mgr->Register("FRS", "FRS Online Directory", dir_frs, false); // allow other tasks to find this
        histograms->Add(dir_frs);
    }

    dir_frs_cal = dir_frs->mkdir("FRS Cal Spectra");
    dir_frs_cal_main = dir_frs_cal->mkdir("Main Crate");
    dir_frs_cal_tpc = dir_frs_cal->mkdir("TPC Crate");
    dir_frs_cal_user = dir_frs_cal->mkdir("User Crate");

    //Main crate detectors:

    //SCIs
    dir_frs_cal_main->cd();
    int sc_xx_bins = 1000;
    int sc_xx_max_e= 4096; //12 bit adc
    h_sci_21l_de = new TH1D("h_sci_21l_de", "FRS Scintillator 21 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    h_sci_21r_de = new TH1D("h_sci_21r_de", "FRS Scintillator 21 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    h_sci_22l_de = new TH1D("h_sci_22l_de", "FRS Scintillator 22 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    h_sci_22r_de = new TH1D("h_sci_22r_de", "FRS Scintillator 22 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    h_sci_41l_de = new TH1D("h_sci_41l_de", "FRS Scintillator 41 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    h_sci_41r_de = new TH1D("h_sci_41r_de", "FRS Scintillator 41 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    h_sci_42l_de = new TH1D("h_sci_42l_de", "FRS Scintillator 42 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    h_sci_42r_de = new TH1D("h_sci_42r_de", "FRS Scintillator 42 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    h_sci_43l_de = new TH1D("h_sci_43l_de", "FRS Scintillator 43 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    h_sci_43r_de = new TH1D("h_sci_43r_de", "FRS Scintillator 43 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    h_sci_81l_de = new TH1D("h_sci_81l_de", "FRS Scintillator 81 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    h_sci_81r_de = new TH1D("h_sci_81r_de", "FRS Scintillator 81 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);

    int sc_xx_bins_t = 1000;
    double sc_xx_max_t = 1048576; // 2^20 bits in v1290 data word
    h_sci_21l_t = new TH1D("h_sci_21l_t", "FRS Scintillator 21 l time V1290 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    h_sci_21r_t = new TH1D("h_sci_21r_t", "FRS Scintillator 21 r time V1290 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    h_sci_22l_t = new TH1D("h_sci_22l_t", "FRS Scintillator 22 l time V1290 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    h_sci_22r_t = new TH1D("h_sci_22r_t", "FRS Scintillator 22 r time V1290 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    h_sci_41l_t = new TH1D("h_sci_41l_t", "FRS Scintillator 41 l time V1290 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    h_sci_41r_t = new TH1D("h_sci_41r_t", "FRS Scintillator 41 r time V1290 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    h_sci_42l_t = new TH1D("h_sci_42l_t", "FRS Scintillator 42 l time V1290 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    h_sci_42r_t = new TH1D("h_sci_42r_t", "FRS Scintillator 42 r time V1290 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    h_sci_43l_t = new TH1D("h_sci_43l_t", "FRS Scintillator 43 l time V1290 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    h_sci_43r_t = new TH1D("h_sci_43r_t", "FRS Scintillator 43 r time V1290 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    h_sci_81l_t = new TH1D("h_sci_81l_t", "FRS Scintillator 81 l time V1290 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    h_sci_81r_t = new TH1D("h_sci_81r_t", "FRS Scintillator 81 r time V1290 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    
    //MUSIC timings:
    int music_xx_bins = 1000;
    double music_xx_max_t = 1048576; // 2^20 bits in v1290 data word
    h_music41_t = new TH2D("h_music41_t", "FRS MUSIC 41 Timestamps V1290 main crate",8,-0.5,7.5,music_xx_bins,0,music_xx_max_t);
    h_music42_t = new TH2D("h_music42_t", "FRS MUSIC 42 Timestamps V1290 main crate",8,-0.5,7.5,music_xx_bins,0,music_xx_max_t); 

    //TPC timings:
    dir_frs_cal_tpc->cd();

    int tpc_v1190_channels = 128;
    int tpc_v1190_max = 262144; // 2^18 bits in read out word from CAEN manual
    int tpc_v1190_bins = 1000;
    h_tpc_timings_lead = new TH2D("h_tpc_timings_lead","TPC lead timings V1190 TPC crate vs channels",tpc_v1190_channels,0,tpc_v1190_channels,tpc_v1190_bins,0,tpc_v1190_max);
    h_tpc_timings_trail = new TH2D("h_tpc_timings_trail","TPC trail timings V1190 TPC crate vs channels",tpc_v1190_channels,0,tpc_v1190_channels,tpc_v1190_bins,0,tpc_v1190_max);

    int check_sums_bins = 1000;
    int check_sums_max = 20000;
    h_tpc_check_sums = new TH2D("h_tpc_check_sums","Check sums calculated for each anode (7 tpcs * 4 anodes)", number_of_anodes_per_tpc*number_of_tpcs,0,number_of_anodes_per_tpc*number_of_tpcs, check_sums_bins,0,check_sums_max);

    int tpc_min_x = -100;
    int tpc_min_y = -100;
    int tpc_max_x = 100;
    int tpc_max_y = 100;
    int tpc_min_angle = -3.14*100;
    int tpc_max_angle = 3.14*100;
    int tpc_bins = 100;
    h_tpc_angle_x_s2_foc_21_22 = new TH1D("h_tpc_angle_x_s2_foc_21_22", "TPC h_tpc_angle_x_s2_foc_21_22",tpc_bins,tpc_min_angle,tpc_max_angle);
    h_tpc_angle_y_s2_foc_21_22 = new TH1D("h_tpc_angle_y_s2_foc_21_22", "TPC h_tpc_angle_y_s2_foc_21_22",tpc_bins,tpc_min_angle,tpc_max_angle);
    h_tpc_x_s2_foc_21_22 = new TH1D("h_tpc_x_s2_foc_21_22", "TPC h_tpc_x_s2_foc_21_22",tpc_bins,tpc_min_x,tpc_max_x);
    h_tpc_y_s2_foc_21_22 = new TH1D("h_tpc_y_s2_foc_21_22", "TPC h_tpc_y_s2_foc_21_22",tpc_bins,tpc_min_y,tpc_max_y);
    h_tpc21_22_sc21_x = new TH1D("h_tpc21_22_sc21_x", "TPC h_tpc21_22_sc21_x",tpc_bins,tpc_min_x,tpc_max_x);
    h_tpc21_22_sc22_x = new TH1D("h_tpc21_22_sc22_x", "TPC h_tpc21_22_sc22_x",tpc_bins,tpc_min_y,tpc_max_y);
    h_tpc_angle_x_s2_foc_23_24 = new TH1D("h_tpc_angle_x_s2_foc_23_24", "TPC h_tpc_angle_x_s2_foc_23_24",tpc_bins,tpc_min_angle,tpc_max_angle);
    h_tpc_angle_y_s2_foc_23_24 = new TH1D("h_tpc_angle_y_s2_foc_23_24", "TPC h_tpc_angle_y_s2_foc_23_24",tpc_bins,tpc_min_angle,tpc_max_angle);
    h_tpc_x_s2_foc_23_24 = new TH1D("h_tpc_x_s2_foc_23_24", "TPC h_tpc_x_s2_foc_23_24",tpc_bins,tpc_min_x,tpc_max_x);
    h_tpc_y_s2_foc_23_24 = new TH1D("h_tpc_y_s2_foc_23_24", "TPC h_tpc_y_s2_foc_23_24",tpc_bins,tpc_min_y,tpc_max_y);
    h_tpc23_24_sc21_x = new TH1D("h_tpc23_24_sc21_x", "TPC h_tpc23_24_sc21_x",tpc_bins,tpc_min_x,tpc_max_x);
    h_tpc23_24_sc21_y = new TH1D("h_tpc23_24_sc21_y", "TPC h_tpc23_24_sc21_y",tpc_bins,tpc_min_y,tpc_max_y);
    h_tpc23_24_sc22_x = new TH1D("h_tpc23_24_sc22_x", "TPC h_tpc23_24_sc22_x",tpc_bins,tpc_min_x,tpc_max_x);
    h_tpc23_24_sc22_y = new TH1D("h_tpc23_24_sc22_y", "TPC h_tpc23_24_sc22_y",tpc_bins,tpc_min_y,tpc_max_y);
    h_tpc_angle_x_s2_foc_22_24 = new TH1D("h_tpc_angle_x_s2_foc_22_24", "TPC h_tpc_angle_x_s2_foc_22_24",tpc_bins,tpc_min_angle,tpc_max_angle);
    h_tpc_angle_y_s2_foc_22_24 = new TH1D("h_tpc_angle_y_s2_foc_22_24", "TPC h_tpc_angle_y_s2_foc_22_24",tpc_bins,tpc_min_angle,tpc_max_angle);
    h_tpc_x_s2_foc_22_24 = new TH1D("h_tpc_x_s2_foc_22_24", "TPC h_tpc_x_s2_foc_22_24",tpc_bins,tpc_min_x,tpc_max_x);
    h_tpc_y_s2_foc_22_24 = new TH1D("h_tpc_y_s2_foc_22_24", "TPC h_tpc_y_s2_foc_22_24",tpc_bins,tpc_min_y,tpc_max_y);
    h_tpc_angle_x_s4 = new TH1D("h_tpc_angle_x_s4", "TPC h_tpc_angle_x_s4",tpc_bins,tpc_min_angle,tpc_max_angle);
    h_tpc_angle_y_s4 = new TH1D("h_tpc_angle_y_s4", "TPC h_tpc_angle_y_s4",tpc_bins,tpc_min_angle,tpc_max_angle);
    h_tpc_x_s4 = new TH1D("h_tpc_x_s4", "TPC h_tpc_x_s4",tpc_bins,tpc_min_x,tpc_max_x);
    h_tpc_y_s4 = new TH1D("h_tpc_y_s4", "TPC h_tpc_y_s4",tpc_bins,tpc_min_y,tpc_max_y);
    h_tpc_sc41_x = new TH1D("h_tpc_sc41_x", "TPC h_tpc_sc41_x",tpc_bins,tpc_min_x,tpc_max_x);
    h_tpc_sc41_y = new TH1D("h_tpc_sc41_y", "TPC h_tpc_sc41_y",tpc_bins,tpc_min_y,tpc_max_y);
    h_tpc_sc42_x = new TH1D("h_tpc_sc42_x", "TPC h_tpc_sc42_x",tpc_bins,tpc_min_x,tpc_max_x);
    h_tpc_sc42_y = new TH1D("h_tpc_sc42_y", "TPC h_tpc_sc42_y",tpc_bins,tpc_min_y,tpc_max_y);
    h_tpc_sc43_x = new TH1D("h_tpc_sc43_x", "TPC h_tpc_sc43_x",tpc_bins,tpc_min_x,tpc_max_x);
    h_tpc_music41_x = new TH1D("h_tpc_music41_x", "TPC h_tpc_music41_x",tpc_bins,tpc_min_x,tpc_max_x);
    h_tpc_music42_x = new TH1D("h_tpc_music42_x", "TPC h_tpc_music42_x",tpc_bins,tpc_min_x,tpc_max_x);
    h_tpc_music43_x = new TH1D("h_tpc_music43_x", "TPC h_tpc_music43_x",tpc_bins,tpc_min_x,tpc_max_x);
    
    h1_sci21_x = new TH1D("h1_sci21_x", "S2 position SCI21", 200, -100, 100);

    dir_frs_cal_user->cd();
    int tac_bins = 1000;
    int max_tac_value = 5000;
    h_tac_user_dt_21l_21r = new TH1D("h_tac_user_dt_21l_21r","dt sci 21l - 21r TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_41l_41r = new TH1D("h_tac_user_dt_41l_41r","dt sci 41l - 41r TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_42l_42r = new TH1D("h_tac_user_dt_42l_42r","dt sci 42l - 42r TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_43l_43r = new TH1D("h_tac_user_dt_43l_43r","dt sci 43l - 43r TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_81l_81r = new TH1D("h_tac_user_dt_81l_81r","dt sci 81l - 81r TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_21l_41l = new TH1D("h_tac_user_dt_21l_41l","dt sci 21l - 41l TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_21r_41r = new TH1D("h_tac_user_dt_21r_41r","dt sci 21r - 41r TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_42r_21r = new TH1D("h_tac_user_dt_42r_21r","dt sci 42r - 21r TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_42l_21l = new TH1D("h_tac_user_dt_42l_21l","dt sci 42l - 21l TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_21l_81l = new TH1D("h_tac_user_dt_21l_81l","dt sci 21l - 81l TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_21r_81r = new TH1D("h_tac_user_dt_21r_81r","dt sci 21r - 81r TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_22l_22r = new TH1D("h_tac_user_dt_22l_22r","dt sci 22l - 22r TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_22l_41l = new TH1D("h_tac_user_dt_22l_41l","dt sci 22l - 41l TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_22r_41r = new TH1D("h_tac_user_dt_22r_41r","dt sci 22r - 41r TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_22l_81l = new TH1D("h_tac_user_dt_22l_81l","dt sci 22l - 81l TAC in User Crate",tac_bins,0,max_tac_value);
    h_tac_user_dt_22r_81r = new TH1D("h_tac_user_dt_22r_81r","dt sci 22r - 81r TAC in User Crate",tac_bins,0,max_tac_value);

    dir_frs->cd();

    run->GetHttpServer()->RegisterCommand("Reset_IncomingID_HIST", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;

}

void FrsCalSpectra::Reset_Histo()
{
    c4LOG(info, "");
    // incoming
}

void FrsCalSpectra::Exec(Option_t* option)
{   
    uint64_t wr_t = 0;
    auto const & tpatItem = tpatArray->at(0);
    wr_t = tpatItem.Get_wr_t();
    if (wr_t == 0) return;
    if (mainMusicArray->size() > 1) std::cout << "weird FRS event" << std::endl;

    auto const & mainSciItem  = mainSciArray->at(0);
       
    uint32_t* sci_de = mainSciItem.Get_de_array(); // size 14
    uint32_t sci_21l_de = sci_de[1];
    uint32_t sci_21r_de = sci_de[2];  
    uint32_t sci_22l_de = sci_de[13];  
    uint32_t sci_22r_de = sci_de[6];  
    uint32_t sci_41l_de = sci_de[0];  
    uint32_t sci_41r_de = sci_de[11];  
    uint32_t sci_42l_de = sci_de[3];  
    uint32_t sci_42r_de = sci_de[4];  
    uint32_t sci_43l_de = sci_de[9];  
    uint32_t sci_43r_de = sci_de[10];  
    uint32_t sci_81l_de = sci_de[5];  
    uint32_t sci_81r_de = sci_de[12];

    h_sci_21l_de->Fill(sci_21l_de);
    h_sci_21r_de->Fill(sci_21r_de);
    h_sci_22l_de->Fill(sci_22l_de);
    h_sci_22r_de->Fill(sci_22r_de);
    h_sci_41l_de->Fill(sci_41l_de);
    h_sci_41r_de->Fill(sci_41r_de);
    h_sci_42l_de->Fill(sci_42l_de);
    h_sci_42r_de->Fill(sci_42r_de);
    h_sci_43l_de->Fill(sci_43l_de);
    h_sci_43r_de->Fill(sci_43r_de);
    h_sci_81l_de->Fill(sci_81l_de);
    h_sci_81r_de->Fill(sci_81r_de);

    uint32_t** tdc_array = mainSciItem.Get_tdc_array();

    h_sci_21l_t->Fill(tdc_array[2][0]);
    h_sci_21r_t->Fill(tdc_array[3][0]);
    h_sci_22l_t->Fill(tdc_array[12][0]);
    h_sci_22r_t->Fill(tdc_array[13][0]);
    h_sci_41l_t->Fill(tdc_array[0][0]);
    h_sci_41r_t->Fill(tdc_array[1][0]);
    h_sci_42l_t->Fill(tdc_array[4][0]);
    h_sci_42r_t->Fill(tdc_array[14][0]);
    h_sci_43l_t->Fill(tdc_array[5][0]);
    h_sci_43r_t->Fill(tdc_array[6][0]);
    h_sci_81l_t->Fill(tdc_array[7][0]);
    h_sci_81r_t->Fill(tdc_array[8][0]);
    
    auto const & mainMusicItem  = mainMusicArray->at(0);

    //music timings:
    uint32_t* music_t1 = mainMusicItem.Get_music_t1();
    uint32_t* music_t2 = mainMusicItem.Get_music_t2();
    if (music_t1 != nullptr && music_t2 != nullptr) 
    {
        for (int anode = 0; anode<8; anode++) 
        {
            h_music41_t->Fill(anode,music_t1[anode]); 
            h_music42_t->Fill(anode,music_t2[anode]);
        }
    }

    for (auto const & v1190item : *v1190array)
    {
        uint32_t channel = v1190item.Get_channel();
        uint32_t data = v1190item.Get_v1190_data();
        uint32_t lot = v1190item.Get_leadOrTrail();

        if (lot == 0)
        {
            h_tpc_timings_lead->Fill(channel, data);
        }
        else if (lot == 1)
        {
            h_tpc_timings_trail->Fill(channel, data);
        }
    }

    auto const & tpcCalItem = tpcCalArray->at(0);
    Int_t** tpc_csum = tpcCalItem.Get_tpc_csum();
    for (int an = 0; an < number_of_anodes_per_tpc; an++)
    {
        for (int ntpc = 0; ntpc < number_of_tpcs; ntpc ++)
        {
            h_tpc_check_sums->Fill(ntpc*number_of_anodes_per_tpc + an, tpc_csum[ntpc][an]);
        }
    }

    h_tpc_angle_x_s2_foc_21_22->Fill(tpcCalItem.Get_tpc_angle_x_s2_foc_21_22());
    h_tpc_angle_y_s2_foc_21_22->Fill(tpcCalItem.Get_tpc_angle_y_s2_foc_21_22());
    h_tpc_x_s2_foc_21_22->Fill(tpcCalItem.Get_tpc_x_s2_foc_21_22());
    h_tpc_y_s2_foc_21_22->Fill(tpcCalItem.Get_tpc_y_s2_foc_21_22());
    h_tpc21_22_sc21_x->Fill(tpcCalItem.Get_tpc21_22_sc21_x());
    h_tpc21_22_sc22_x->Fill(tpcCalItem.Get_tpc21_22_sc22_x());
    h_tpc_angle_x_s2_foc_23_24->Fill(tpcCalItem.Get_tpc_angle_x_s2_foc_23_24());
    h_tpc_angle_y_s2_foc_23_24->Fill(tpcCalItem.Get_tpc_angle_y_s2_foc_23_24());
    h_tpc_x_s2_foc_23_24->Fill(tpcCalItem.Get_tpc_x_s2_foc_23_24());
    h_tpc_y_s2_foc_23_24->Fill(tpcCalItem.Get_tpc_y_s2_foc_23_24());
    h_tpc23_24_sc21_x->Fill(tpcCalItem.Get_tpc23_24_sc21_x());
    h_tpc23_24_sc21_y->Fill(tpcCalItem.Get_tpc23_24_sc21_y());
    h_tpc23_24_sc22_x->Fill(tpcCalItem.Get_tpc23_24_sc22_x());
    h_tpc23_24_sc22_y->Fill(tpcCalItem.Get_tpc23_24_sc22_y());
    h_tpc_angle_x_s2_foc_22_24->Fill(tpcCalItem.Get_tpc_angle_x_s2_foc_22_24());
    h_tpc_angle_y_s2_foc_22_24->Fill(tpcCalItem.Get_tpc_angle_y_s2_foc_22_24());
    h_tpc_x_s2_foc_22_24->Fill(tpcCalItem.Get_tpc_x_s2_foc_22_24());
    h_tpc_y_s2_foc_22_24->Fill(tpcCalItem.Get_tpc_y_s2_foc_22_24());
    h_tpc_angle_x_s4->Fill(tpcCalItem.Get_tpc_angle_x_s4());
    h_tpc_angle_y_s4->Fill(tpcCalItem.Get_tpc_angle_y_s4());
    h_tpc_x_s4->Fill(tpcCalItem.Get_tpc_x_s4());
    h_tpc_y_s4->Fill(tpcCalItem.Get_tpc_y_s4());
    h_tpc_sc41_x->Fill(tpcCalItem.Get_tpc_sc41_x());
    h_tpc_sc41_y->Fill(tpcCalItem.Get_tpc_sc41_y());
    h_tpc_sc42_x->Fill(tpcCalItem.Get_tpc_sc42_x());
    h_tpc_sc42_y->Fill(tpcCalItem.Get_tpc_sc42_y());
    h_tpc_sc43_x->Fill(tpcCalItem.Get_tpc_sc43_x());
    h_tpc_music41_x->Fill(tpcCalItem.Get_tpc_music41_x());
    h_tpc_music42_x->Fill(tpcCalItem.Get_tpc_music42_x());
    h_tpc_music43_x->Fill(tpcCalItem.Get_tpc_music43_x());
            
    auto const & userSciItem = userSciArray->at(0);
    uint32_t* dt_array = userSciItem.Get_dt_array();

    uint32_t dt_21l_21r = dt_array[0];
    h_tac_user_dt_21l_21r->Fill(dt_21l_21r);
    uint32_t dt_41l_41r = dt_array[1];
    h_tac_user_dt_41l_41r->Fill(dt_41l_41r);
    uint32_t dt_42l_42r = dt_array[2];
    h_tac_user_dt_42l_42r->Fill(dt_42l_42r);
    uint32_t dt_43l_43r = dt_array[3];
    h_tac_user_dt_43l_43r->Fill(dt_43l_43r);
    uint32_t dt_81l_81r = dt_array[4];
    h_tac_user_dt_81l_81r->Fill(dt_81l_81r);
    uint32_t dt_21l_41l = dt_array[5];
    h_tac_user_dt_21l_41l->Fill(dt_21l_41l);
    uint32_t dt_21r_41r = dt_array[6];
    h_tac_user_dt_21r_41r->Fill(dt_21r_41r);
    uint32_t dt_42r_21r = dt_array[7];
    h_tac_user_dt_42r_21r->Fill(dt_42r_21r);
    uint32_t dt_42l_21l = dt_array[8];
    h_tac_user_dt_42l_21l->Fill(dt_42l_21l);
    uint32_t dt_21l_81l = dt_array[9];
    h_tac_user_dt_21l_81l->Fill(dt_21l_81l);
    uint32_t dt_21r_81r = dt_array[10];
    h_tac_user_dt_21r_81r->Fill(dt_21r_81r);
    uint32_t dt_22l_22r = dt_array[11];
    h_tac_user_dt_22l_22r->Fill(dt_22l_22r);
    uint32_t dt_22l_41l = dt_array[12];
    h_tac_user_dt_22l_41l->Fill(dt_22l_41l);
    uint32_t dt_22r_41r = dt_array[13];
    h_tac_user_dt_22r_41r->Fill(dt_22r_41r);
    uint32_t dt_22l_81l = dt_array[14];
    h_tac_user_dt_22l_81l->Fill(dt_22l_81l);
    uint32_t dt_22r_81r = dt_array[15];
    h_tac_user_dt_22r_81r->Fill(dt_22r_81r);

    fNEvents += 1;

}

void FrsCalSpectra::FinishEvent()
{
}

void FrsCalSpectra::FinishTask()
{
    
}

ClassImp(FrsCalSpectra)
