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
    : FairTask(name, iVerbose)
    , fFrsMainCalArray(NULL)
    , fFrsUserCalArray(NULL)
    , fFrsTPCArray(NULL)
    , fFrsTPCCalArray(NULL)
    , fFrsVFTXCalArray(NULL)
    , fNEvents(0)
    , header(nullptr)
{
}

FrsCalSpectra::~FrsCalSpectra()
{
    c4LOG(info, "");
    if (fFrsMainCalArray)
        delete fFrsMainCalArray;
}

// Public Method SetParContainers
void FrsCalSpectra::SetParContainers()
{
    // Parameter Containers
    FairRuntimeDb* rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus FrsCalSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fFrsMainCalArray = (TClonesArray*)mgr->GetObject("FrsMainCalData");
    c4LOG_IF(fatal, !fFrsMainCalArray, "Branch FrsMainCalData not found");
    fFrsUserCalArray = (TClonesArray*)mgr->GetObject("FrsUserCalData");
    c4LOG_IF(fatal, !fFrsUserCalArray, "Branch FrsUserCalData not found");
    fFrsTPCArray = (TClonesArray*)mgr->GetObject("FrsTPCData");
    c4LOG_IF(fatal, !fFrsTPCArray, "Branch FrsTPCData not found");
    fFrsTPCCalArray = (TClonesArray*)mgr->GetObject("FrsTPCCalData");
    c4LOG_IF(fatal, !fFrsTPCCalArray, "Branch FrsTPCCalData not found");
    fFrsVFTXCalArray = (TClonesArray*)mgr->GetObject("FrsVFTXCalData");
    c4LOG_IF(fatal, !fFrsVFTXCalArray, "Branch FrsVFTXCalData not found");
    
    TDirectory::TContext ctx(nullptr);

    
    folder_frs_hists = (TFolder*)mgr->GetObject("FRS");
    if (!folder_frs_hists) folder_frs_hists = new TFolder("FRS", "FRS");
    

    TFolder* folder_frs_cal_hists = new TFolder("Cal Histograms", "Cal Histograms");
    folder_frs_hists->Add(folder_frs_cal_hists);

    //TFolder * folder_frs_cal_hists = new TFolder("frs_detectors_histograms", "frs_detectors_histograms");

    //run->AddObject(folder_frs_cal_hists);

    //Main crate detectors:

    //SCIs
    int sc_xx_bins = 1000;
    int sc_xx_max_e= 4096; //12 bit adc
    h_sci_21l_de = new TH1D("h_sci_21l_de", "FRS Scintillator 21 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    folder_frs_cal_hists->Add(h_sci_21l_de);
    h_sci_21r_de = new TH1D("h_sci_21r_de", "FRS Scintillator 21 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    folder_frs_cal_hists->Add(h_sci_21r_de);
    h_sci_22l_de = new TH1D("h_sci_22l_de", "FRS Scintillator 22 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    folder_frs_cal_hists->Add(h_sci_22l_de);
    h_sci_22r_de = new TH1D("h_sci_22r_de", "FRS Scintillator 22 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    folder_frs_cal_hists->Add(h_sci_22r_de);
    h_sci_41l_de = new TH1D("h_sci_41l_de", "FRS Scintillator 41 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    folder_frs_cal_hists->Add(h_sci_41l_de);
    h_sci_41r_de = new TH1D("h_sci_41r_de", "FRS Scintillator 41 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    folder_frs_cal_hists->Add(h_sci_41r_de);
    h_sci_42l_de = new TH1D("h_sci_42l_de", "FRS Scintillator 42 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    folder_frs_cal_hists->Add(h_sci_42l_de);
    h_sci_42r_de = new TH1D("h_sci_42r_de", "FRS Scintillator 42 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    folder_frs_cal_hists->Add(h_sci_42r_de);
    h_sci_43l_de = new TH1D("h_sci_43l_de", "FRS Scintillator 43 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    folder_frs_cal_hists->Add(h_sci_43l_de);
    h_sci_43r_de = new TH1D("h_sci_43r_de", "FRS Scintillator 43 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    folder_frs_cal_hists->Add(h_sci_43r_de);
    h_sci_81l_de = new TH1D("h_sci_81l_de", "FRS Scintillator 81 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    folder_frs_cal_hists->Add(h_sci_81l_de);
    h_sci_81r_de = new TH1D("h_sci_81r_de", "FRS Scintillator 81 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    folder_frs_cal_hists->Add(h_sci_81r_de);

    int sc_xx_bins_t = 1000;
    double sc_xx_max_t = 1048576; // 2^20 bits in v1290 data word
    h_sci_21l_t = new TH1D("h_sci_21l_t", "FRS Scintillator 21 l time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    folder_frs_cal_hists->Add(h_sci_21l_t);
    h_sci_21r_t = new TH1D("h_sci_21r_t", "FRS Scintillator 21 r time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    folder_frs_cal_hists->Add(h_sci_21r_t);
    h_sci_22l_t = new TH1D("h_sci_22l_t", "FRS Scintillator 22 l time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    folder_frs_cal_hists->Add(h_sci_22l_t);
    h_sci_22r_t = new TH1D("h_sci_22r_t", "FRS Scintillator 22 r time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    folder_frs_cal_hists->Add(h_sci_22r_t);
    h_sci_41l_t = new TH1D("h_sci_41l_t", "FRS Scintillator 41 l time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    folder_frs_cal_hists->Add(h_sci_41l_t);
    h_sci_41r_t = new TH1D("h_sci_41r_t", "FRS Scintillator 41 r time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    folder_frs_cal_hists->Add(h_sci_41r_t);
    h_sci_42l_t = new TH1D("h_sci_42l_t", "FRS Scintillator 42 l time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    folder_frs_cal_hists->Add(h_sci_42l_t);
    h_sci_42r_t = new TH1D("h_sci_42r_t", "FRS Scintillator 42 r time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    folder_frs_cal_hists->Add(h_sci_42r_t);
    h_sci_43l_t = new TH1D("h_sci_43l_t", "FRS Scintillator 43 l time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    folder_frs_cal_hists->Add(h_sci_43l_t);
    h_sci_43r_t = new TH1D("h_sci_43r_t", "FRS Scintillator 43 r time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    folder_frs_cal_hists->Add(h_sci_43r_t);
    h_sci_81l_t = new TH1D("h_sci_81l_t", "FRS Scintillator 81 l time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    folder_frs_cal_hists->Add(h_sci_81l_t);
    h_sci_81r_t = new TH1D("h_sci_81r_t", "FRS Scintillator 81 r time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    folder_frs_cal_hists->Add(h_sci_81r_t);
    
    //MUSIC timings:
    int music_xx_bins = 1000;
    double music_xx_max_t = 1048576; // 2^20 bits in v1290 data word
    h_music41_t = new TH2D("h_music41_t", "FRS MUSIC 41 Timestamps V1190 main crate",8,-0.5,7.5,music_xx_bins,0,music_xx_max_t);
    folder_frs_cal_hists->Add(h_music41_t);
    h_music42_t = new TH2D("h_music42_t", "FRS MUSIC 42 Timestamps V1190 main crate",8,-0.5,7.5,music_xx_bins,0,music_xx_max_t); 
    folder_frs_cal_hists->Add(h_music42_t);

    
    //TPC timings:
    int tpc_v1190_channels = 128;
    int tpc_v1190_max = 262144; // 2^18 bits in read out word from CAEN manual
    int tpc_v1190_bins = 1000;
    
    h_tpc_timings_lead = new TH2D("h_tpc_timings_lead","TPC lead timings V1190 TPC crate vs channels",tpc_v1190_channels,0,tpc_v1190_channels,tpc_v1190_bins,0,tpc_v1190_max);
    folder_frs_cal_hists->Add(h_tpc_timings_lead);
    h_tpc_timings_trail = new TH2D("h_tpc_timings_trail","TPC trail timings V1190 TPC crate vs channels",tpc_v1190_channels,0,tpc_v1190_channels,tpc_v1190_bins,0,tpc_v1190_max);
    folder_frs_cal_hists->Add(h_tpc_timings_trail);


    int check_sums_bins = 1000;
    int check_sums_max = 20000;
    h_tpc_check_sums = new TH2D("h_tpc_check_sums","Check sums calculated for each anode (7 tpcs * 4 anodes)", number_of_anodes_per_tpc*number_of_tpcs,0,number_of_anodes_per_tpc*number_of_tpcs, check_sums_bins,0,check_sums_max);
    folder_frs_cal_hists->Add(h_tpc_check_sums);

    int tpc_min_x = -100;
    int tpc_min_y = -100;
    int tpc_max_x = 100;
    int tpc_max_y = 100;
    int tpc_min_angle = -3.14*100;
    int tpc_max_angle = 3.14*100;
    int tpc_bins = 100;

    h_tpc_angle_x_s2_foc_21_22 = new TH1D("h_tpc_angle_x_s2_foc_21_22", "TPC h_tpc_angle_x_s2_foc_21_22",tpc_bins,tpc_min_angle,tpc_max_angle);
    folder_frs_cal_hists->Add(h_tpc_angle_x_s2_foc_21_22);
    h_tpc_angle_y_s2_foc_21_22 = new TH1D("h_tpc_angle_y_s2_foc_21_22", "TPC h_tpc_angle_y_s2_foc_21_22",tpc_bins,tpc_min_angle,tpc_max_angle);
    folder_frs_cal_hists->Add(h_tpc_angle_y_s2_foc_21_22);
    h_tpc_x_s2_foc_21_22 = new TH1D("h_tpc_x_s2_foc_21_22", "TPC h_tpc_x_s2_foc_21_22",tpc_bins,tpc_min_x,tpc_max_x);
    folder_frs_cal_hists->Add(h_tpc_x_s2_foc_21_22);
    h_tpc_y_s2_foc_21_22 = new TH1D("h_tpc_y_s2_foc_21_22", "TPC h_tpc_y_s2_foc_21_22",tpc_bins,tpc_min_y,tpc_max_y);
    folder_frs_cal_hists->Add(h_tpc_y_s2_foc_21_22);
    h_tpc21_22_sc21_x = new TH1D("h_tpc21_22_sc21_x", "TPC h_tpc21_22_sc21_x",tpc_bins,tpc_min_x,tpc_max_x);
    folder_frs_cal_hists->Add(h_tpc21_22_sc21_x);
    h_tpc21_22_sc22_x = new TH1D("h_tpc21_22_sc22_x", "TPC h_tpc21_22_sc22_x",tpc_bins,tpc_min_y,tpc_max_y);
    folder_frs_cal_hists->Add(h_tpc21_22_sc22_x);
    h_tpc_angle_x_s2_foc_23_24 = new TH1D("h_tpc_angle_x_s2_foc_23_24", "TPC h_tpc_angle_x_s2_foc_23_24",tpc_bins,tpc_min_angle,tpc_max_angle);
    folder_frs_cal_hists->Add(h_tpc_angle_x_s2_foc_23_24);
    h_tpc_angle_y_s2_foc_23_24 = new TH1D("h_tpc_angle_y_s2_foc_23_24", "TPC h_tpc_angle_y_s2_foc_23_24",tpc_bins,tpc_min_angle,tpc_max_angle);
    folder_frs_cal_hists->Add(h_tpc_angle_y_s2_foc_23_24);
    h_tpc_x_s2_foc_23_24 = new TH1D("h_tpc_x_s2_foc_23_24", "TPC h_tpc_x_s2_foc_23_24",tpc_bins,tpc_min_x,tpc_max_x);
    folder_frs_cal_hists->Add(h_tpc_x_s2_foc_23_24);
    h_tpc_y_s2_foc_23_24 = new TH1D("h_tpc_y_s2_foc_23_24", "TPC h_tpc_y_s2_foc_23_24",tpc_bins,tpc_min_y,tpc_max_y);
    folder_frs_cal_hists->Add(h_tpc_y_s2_foc_23_24);
    h_tpc23_24_sc21_x = new TH1D("h_tpc23_24_sc21_x", "TPC h_tpc23_24_sc21_x",tpc_bins,tpc_min_x,tpc_max_x);
    folder_frs_cal_hists->Add(h_tpc23_24_sc21_x);
    h_tpc23_24_sc21_y = new TH1D("h_tpc23_24_sc21_y", "TPC h_tpc23_24_sc21_y",tpc_bins,tpc_min_y,tpc_max_y);
    folder_frs_cal_hists->Add(h_tpc23_24_sc21_y);
    h_tpc23_24_sc22_x = new TH1D("h_tpc23_24_sc22_x", "TPC h_tpc23_24_sc22_x",tpc_bins,tpc_min_x,tpc_max_x);
    folder_frs_cal_hists->Add(h_tpc23_24_sc22_x);
    h_tpc23_24_sc22_y = new TH1D("h_tpc23_24_sc22_y", "TPC h_tpc23_24_sc22_y",tpc_bins,tpc_min_y,tpc_max_y);
    folder_frs_cal_hists->Add(h_tpc23_24_sc22_y);
    h_tpc_angle_x_s2_foc_22_24 = new TH1D("h_tpc_angle_x_s2_foc_22_24", "TPC h_tpc_angle_x_s2_foc_22_24",tpc_bins,tpc_min_angle,tpc_max_angle);
    folder_frs_cal_hists->Add(h_tpc_angle_x_s2_foc_22_24);
    h_tpc_angle_y_s2_foc_22_24 = new TH1D("h_tpc_angle_y_s2_foc_22_24", "TPC h_tpc_angle_y_s2_foc_22_24",tpc_bins,tpc_min_angle,tpc_max_angle);
    folder_frs_cal_hists->Add(h_tpc_angle_y_s2_foc_22_24);
    h_tpc_x_s2_foc_22_24 = new TH1D("h_tpc_x_s2_foc_22_24", "TPC h_tpc_x_s2_foc_22_24",tpc_bins,tpc_min_x,tpc_max_x);
    folder_frs_cal_hists->Add(h_tpc_x_s2_foc_22_24);
    h_tpc_y_s2_foc_22_24 = new TH1D("h_tpc_y_s2_foc_22_24", "TPC h_tpc_y_s2_foc_22_24",tpc_bins,tpc_min_y,tpc_max_y);
    folder_frs_cal_hists->Add(h_tpc_y_s2_foc_22_24);
    h_tpc_angle_x_s4 = new TH1D("h_tpc_angle_x_s4", "TPC h_tpc_angle_x_s4",tpc_bins,tpc_min_angle,tpc_max_angle);
    folder_frs_cal_hists->Add(h_tpc_angle_x_s4);
    h_tpc_angle_y_s4 = new TH1D("h_tpc_angle_y_s4", "TPC h_tpc_angle_y_s4",tpc_bins,tpc_min_angle,tpc_max_angle);
    folder_frs_cal_hists->Add(h_tpc_angle_y_s4);
    h_tpc_x_s4 = new TH1D("h_tpc_x_s4", "TPC h_tpc_x_s4",tpc_bins,tpc_min_x,tpc_max_x);
    folder_frs_cal_hists->Add(h_tpc_x_s4);
    h_tpc_y_s4 = new TH1D("h_tpc_y_s4", "TPC h_tpc_y_s4",tpc_bins,tpc_min_y,tpc_max_y);
    folder_frs_cal_hists->Add(h_tpc_y_s4);
    h_tpc_sc41_x = new TH1D("h_tpc_sc41_x", "TPC h_tpc_sc41_x",tpc_bins,tpc_min_x,tpc_max_x);
    folder_frs_cal_hists->Add(h_tpc_sc41_x);
    h_tpc_sc41_y = new TH1D("h_tpc_sc41_y", "TPC h_tpc_sc41_y",tpc_bins,tpc_min_y,tpc_max_y);
    folder_frs_cal_hists->Add(h_tpc_sc41_y);
    h_tpc_sc42_x = new TH1D("h_tpc_sc42_x", "TPC h_tpc_sc42_x",tpc_bins,tpc_min_x,tpc_max_x);
    folder_frs_cal_hists->Add(h_tpc_sc42_x);
    h_tpc_sc42_y = new TH1D("h_tpc_sc42_y", "TPC h_tpc_sc42_y",tpc_bins,tpc_min_y,tpc_max_y);
    folder_frs_cal_hists->Add(h_tpc_sc42_y);
    h_tpc_sc43_x = new TH1D("h_tpc_sc43_x", "TPC h_tpc_sc43_x",tpc_bins,tpc_min_x,tpc_max_x);
    folder_frs_cal_hists->Add(h_tpc_sc43_x);
    h_tpc_music41_x = new TH1D("h_tpc_music41_x", "TPC h_tpc_music41_x",tpc_bins,tpc_min_x,tpc_max_x);
    folder_frs_cal_hists->Add(h_tpc_music41_x);
    h_tpc_music42_x = new TH1D("h_tpc_music42_x", "TPC h_tpc_music42_x",tpc_bins,tpc_min_x,tpc_max_x);
    folder_frs_cal_hists->Add(h_tpc_music42_x);
    h_tpc_music43_x = new TH1D("h_tpc_music43_x", "TPC h_tpc_music43_x",tpc_bins,tpc_min_x,tpc_max_x);
    folder_frs_cal_hists->Add(h_tpc_music43_x);


    int tac_bins = 1000;
    int max_tac_value = 5000;
    h_tac_user_dt_21l_21r = new TH1D("h_tac_user_dt_21l_21r","dt sci 21l - 21r TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_21l_21r);
    h_tac_user_dt_41l_41r = new TH1D("h_tac_user_dt_41l_41r","dt sci 41l - 41r TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_41l_41r);
    h_tac_user_dt_42l_42r = new TH1D("h_tac_user_dt_42l_42r","dt sci 42l - 42r TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_42l_42r);
    h_tac_user_dt_43l_43r = new TH1D("h_tac_user_dt_43l_43r","dt sci 43l - 43r TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_43l_43r);
    h_tac_user_dt_81l_81r = new TH1D("h_tac_user_dt_81l_81r","dt sci 81l - 81r TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_81l_81r);
    h_tac_user_dt_21l_41l = new TH1D("h_tac_user_dt_21l_41l","dt sci 21l - 41l TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_21l_41l);
    h_tac_user_dt_21r_41r = new TH1D("h_tac_user_dt_21r_41r","dt sci 21r - 41r TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_21r_41r);
    h_tac_user_dt_42r_21r = new TH1D("h_tac_user_dt_42r_21r","dt sci 42r - 21r TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_42r_21r);
    h_tac_user_dt_42l_21l = new TH1D("h_tac_user_dt_42l_21l","dt sci 42l - 21l TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_42l_21l);
    h_tac_user_dt_21l_81l = new TH1D("h_tac_user_dt_21l_81l","dt sci 21l - 81l TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_21l_81l);
    h_tac_user_dt_21r_81r = new TH1D("h_tac_user_dt_21r_81r","dt sci 21r - 81r TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_21r_81r);
    h_tac_user_dt_22l_22r = new TH1D("h_tac_user_dt_22l_22r","dt sci 22l - 22r TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_22l_22r);
    h_tac_user_dt_22l_41l = new TH1D("h_tac_user_dt_22l_41l","dt sci 22l - 41l TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_22l_41l);
    h_tac_user_dt_22r_41r = new TH1D("h_tac_user_dt_22r_41r","dt sci 22r - 41r TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_22r_41r);
    h_tac_user_dt_22l_81l = new TH1D("h_tac_user_dt_22l_81l","dt sci 22l - 81l TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_22l_81l);
    h_tac_user_dt_22r_81r = new TH1D("h_tac_user_dt_22r_81r","dt sci 22r - 81r TAC in User Crate",tac_bins,0,max_tac_value);
    folder_frs_cal_hists->Add(h_tac_user_dt_22r_81r);

    // Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_IncomingID_HIST", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;

}

void FrsCalSpectra::Reset_Histo()
{
    c4LOG(info, "");
   // fh1_TdcRaw->Clear();
   // fh1_TdcChan->Clear();
}

void FrsCalSpectra::Exec(Option_t* option)
{
    // MainCrate:
    if (fFrsMainCalArray && fFrsMainCalArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fFrsMainCalArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            fHitFrsMainCal = (FrsMainCalData*)fFrsMainCalArray->At(ihit);
            if (!fHitFrsMainCal) continue;
                    
            const uint32_t* sci_de = fHitFrsMainCal->Get_De_array(); // size 14
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

            //music timings:
            const uint32_t* music_t1 = fHitFrsMainCal->Get_music_t1(); // size 8 arrays
            const uint32_t* music_t2 = fHitFrsMainCal->Get_music_t2(); // size 8 arrays
            if (music_t1!=nullptr && music_t2 != nullptr) for (int anode = 0; anode<8; anode++) {h_music41_t->Fill(anode,music_t1[anode]); h_music42_t->Fill(anode,music_t2[anode]);}
        
        
            std::vector<uint32_t> sci_21l_t = fHitFrsMainCal->Get_TDC_channel(2);
            if (sci_21l_t.size()>0) h_sci_21l_t->Fill(sci_21l_t.at(0));
            std::vector<uint32_t> sci_21r_t = fHitFrsMainCal->Get_TDC_channel(3);
            if (sci_21r_t.size()>0) h_sci_21r_t->Fill(sci_21r_t.at(0));
            std::vector<uint32_t> sci_22l_t = fHitFrsMainCal->Get_TDC_channel(12);
            if (sci_22l_t.size()>0) h_sci_22l_t->Fill(sci_22l_t.at(0));
            std::vector<uint32_t> sci_22r_t = fHitFrsMainCal->Get_TDC_channel(13);
            if (sci_22r_t.size()>0) h_sci_22r_t->Fill(sci_22r_t.at(0));
            std::vector<uint32_t> sci_41l_t = fHitFrsMainCal->Get_TDC_channel(0);
            if (sci_41l_t.size()>0) h_sci_41l_t->Fill(sci_41l_t.at(0));
            std::vector<uint32_t> sci_41r_t = fHitFrsMainCal->Get_TDC_channel(1);
            if (sci_41r_t.size()>0) h_sci_41r_t->Fill(sci_41r_t.at(0));
            std::vector<uint32_t> sci_42l_t = fHitFrsMainCal->Get_TDC_channel(4);
            if (sci_42l_t.size()>0) h_sci_42l_t->Fill(sci_42l_t.at(0));
            std::vector<uint32_t> sci_42r_t = fHitFrsMainCal->Get_TDC_channel(14);
            if (sci_42r_t.size()>0) h_sci_42r_t->Fill(sci_42r_t.at(0));
            std::vector<uint32_t> sci_43l_t = fHitFrsMainCal->Get_TDC_channel(5);
            if (sci_43l_t.size()>0) h_sci_43l_t->Fill(sci_43l_t.at(0));
            std::vector<uint32_t> sci_43r_t = fHitFrsMainCal->Get_TDC_channel(6);
            if (sci_43r_t.size()>0) h_sci_43r_t->Fill(sci_43r_t.at(0));
            std::vector<uint32_t> sci_81l_t = fHitFrsMainCal->Get_TDC_channel(7);
            if (sci_81l_t.size()>0) h_sci_81l_t->Fill(sci_81l_t.at(0));
            std::vector<uint32_t> sci_81r_t = fHitFrsMainCal->Get_TDC_channel(8);
            if (sci_81r_t.size()>0) h_sci_81r_t->Fill(sci_81r_t.at(0));

        }
    }

    if (fFrsTPCArray && fFrsTPCArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fFrsTPCArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            fHitFrsTPC = (FrsTPCData*)fFrsTPCArray->At(ihit);
            if (!fHitFrsTPC) continue;

            std::vector<uint32_t> tpc_v1190_channels;
            std::vector<uint32_t> tpc_v1190_lot;
            std::vector<uint32_t> tpc_v1190_data;
            tpc_v1190_channels = fHitFrsTPC->Get_V1190_Channel();
            tpc_v1190_lot = fHitFrsTPC->Get_V1190_LoT();
            tpc_v1190_data = fHitFrsTPC->Get_V1190_Data();

            for (int v1190_hit = 0; v1190_hit<tpc_v1190_channels.size(); v1190_hit++)
            {
                if (!tpc_v1190_lot.at(v1190_hit))
                {
                    h_tpc_timings_lead->Fill(tpc_v1190_channels.at(v1190_hit),tpc_v1190_data.at(v1190_hit));
                }
                else
                {
                    h_tpc_timings_trail->Fill(tpc_v1190_channels.at(v1190_hit),tpc_v1190_data.at(v1190_hit));
                }
            }
        }
    }


    if (fFrsTPCCalArray && fFrsTPCCalArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fFrsTPCCalArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            fHitFrsTPCCal = (FrsTPCCalData*)fFrsTPCCalArray->At(ihit);
            if (!fHitFrsTPCCal) continue;

            for (int an = 0; an < number_of_anodes_per_tpc; an++){
                for (int ntpc = 0; ntpc < number_of_tpcs; ntpc ++){
                    h_tpc_check_sums->Fill(ntpc*number_of_anodes_per_tpc + an, fHitFrsTPCCal->Get_tpc_csum(ntpc,an));
                }

                h_tpc_angle_x_s2_foc_21_22->Fill(fHitFrsTPCCal->Get_tpc_angle_x_s2_foc_21_22());
                h_tpc_angle_y_s2_foc_21_22->Fill(fHitFrsTPCCal->Get_tpc_angle_y_s2_foc_21_22());
                h_tpc_x_s2_foc_21_22->Fill(fHitFrsTPCCal->Get_tpc_x_s2_foc_21_22());
                h_tpc_y_s2_foc_21_22->Fill(fHitFrsTPCCal->Get_tpc_y_s2_foc_21_22());
                h_tpc21_22_sc21_x->Fill(fHitFrsTPCCal->Get_tpc21_22_sc21_x());
                h_tpc21_22_sc22_x->Fill(fHitFrsTPCCal->Get_tpc21_22_sc22_x());
                h_tpc_angle_x_s2_foc_23_24->Fill(fHitFrsTPCCal->Get_tpc_angle_x_s2_foc_23_24());
                h_tpc_angle_y_s2_foc_23_24->Fill(fHitFrsTPCCal->Get_tpc_angle_y_s2_foc_23_24());
                h_tpc_x_s2_foc_23_24->Fill(fHitFrsTPCCal->Get_tpc_x_s2_foc_23_24());
                h_tpc_y_s2_foc_23_24->Fill(fHitFrsTPCCal->Get_tpc_y_s2_foc_23_24());
                h_tpc23_24_sc21_x->Fill(fHitFrsTPCCal->Get_tpc23_24_sc21_x());
                h_tpc23_24_sc21_y->Fill(fHitFrsTPCCal->Get_tpc23_24_sc21_y());
                h_tpc23_24_sc22_x->Fill(fHitFrsTPCCal->Get_tpc23_24_sc22_x());
                h_tpc23_24_sc22_y->Fill(fHitFrsTPCCal->Get_tpc23_24_sc22_y());
                h_tpc_angle_x_s2_foc_22_24->Fill(fHitFrsTPCCal->Get_tpc_angle_x_s2_foc_22_24());
                h_tpc_angle_y_s2_foc_22_24->Fill(fHitFrsTPCCal->Get_tpc_angle_y_s2_foc_22_24());
                h_tpc_x_s2_foc_22_24->Fill(fHitFrsTPCCal->Get_tpc_x_s2_foc_22_24());
                h_tpc_y_s2_foc_22_24->Fill(fHitFrsTPCCal->Get_tpc_y_s2_foc_22_24());
                h_tpc_angle_x_s4->Fill(fHitFrsTPCCal->Get_tpc_angle_x_s4());
                h_tpc_angle_y_s4->Fill(fHitFrsTPCCal->Get_tpc_angle_y_s4());
                h_tpc_x_s4->Fill(fHitFrsTPCCal->Get_tpc_x_s4());
                h_tpc_y_s4->Fill(fHitFrsTPCCal->Get_tpc_y_s4());
                h_tpc_sc41_x->Fill(fHitFrsTPCCal->Get_tpc_sc41_x());
                h_tpc_sc41_y->Fill(fHitFrsTPCCal->Get_tpc_sc41_y());
                h_tpc_sc42_x->Fill(fHitFrsTPCCal->Get_tpc_sc42_x());
                h_tpc_sc42_y->Fill(fHitFrsTPCCal->Get_tpc_sc42_y());
                h_tpc_sc43_x->Fill(fHitFrsTPCCal->Get_tpc_sc43_x());
                h_tpc_music41_x->Fill(fHitFrsTPCCal->Get_tpc_music41_x());
                h_tpc_music42_x->Fill(fHitFrsTPCCal->Get_tpc_music42_x());
                h_tpc_music43_x->Fill(fHitFrsTPCCal->Get_tpc_music43_x());
            }
        }
    }

    if (fFrsUserCalArray && fFrsUserCalArray->GetEntriesFast() > 0){
        Int_t nhits = fFrsUserCalArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit<nhits; ihit++){
            fHitFrsUserCal = (FrsUserCalData*)fFrsUserCalArray->At(ihit);
            if (!fHitFrsUserCal) continue;
            dt_array = fHitFrsUserCal->Get_dt_array();
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


        }
    }

    fNEvents += 1;
}

void FrsCalSpectra::FinishEvent()
{
    if(fFrsUserCalArray) fFrsUserCalArray->Clear();
    if(fFrsMainCalArray) fFrsMainCalArray->Clear();
    if(fFrsTPCArray) fFrsTPCArray->Clear();
    if(fFrsTPCCalArray) fFrsTPCCalArray->Clear();
    if(fFrsVFTXCalArray) fFrsVFTXCalArray->Clear();
}

void FrsCalSpectra::FinishTask()
{
    //folder_frs_cal_hists->Write();
}

ClassImp(FrsCalSpectra)
