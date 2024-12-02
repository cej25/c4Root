#include "FrsCal2Hit.h"
#include "c4Logger.h"
#include "FrsMainData.h"
#include "FrsMainCalData.h"
#include "FrsHitData.h"
#include "EventData.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "FairTask.h"

#include "TClonesArray.h"
#include "TMath.h"
#include <TMacro.h>
#include <vector>
#include <iostream>
#include <TROOT.h>
#include <chrono>

#define MUSIC_ANA_NEW

FrsCal2Hit::FrsCal2Hit()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   mainScalerArray(nullptr)
    ,   mainSciArray(nullptr)
    ,   mainMusicArray(nullptr)
    ,   tpcCalArray(nullptr)
    ,   userScalerArray(nullptr)
    ,   userSciArray(nullptr)
    ,   userMusicArray(nullptr)
    ,   tpatArray(nullptr)
    ,   hitArray(new std::vector<FrsHitItem>)
    ,   multihitArray(new std::vector<FrsMultiHitItem>)
{
    frs_config = TFrsConfiguration::GetInstance();
    exp_config = TExperimentConfiguration::GetInstance();
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
    pathToConfigFiles = frs_config->GetConfigPath();
}

FrsCal2Hit::FrsCal2Hit(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   mainScalerArray(nullptr)
    ,   mainSciArray(nullptr)
    ,   mainMusicArray(nullptr)
    ,   tpcCalArray(nullptr)
    ,   userScalerArray(nullptr)
    ,   userSciArray(nullptr)
    ,   userMusicArray(nullptr)
    ,   tpatArray(nullptr)
    ,   hitArray(new std::vector<FrsHitItem>)
    ,   multihitArray(new std::vector<FrsMultiHitItem>)
{
    frs_config = TFrsConfiguration::GetInstance();
    exp_config = TExperimentConfiguration::GetInstance();

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
    pathToConfigFiles = frs_config->GetConfigPath();
}

FrsCal2Hit::~FrsCal2Hit()
{   
    c4LOG(info, "Deleting FrsCal2Hit task");
}

InitStatus FrsCal2Hit::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");
    
    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

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

    mgr->RegisterAny("FrsHitData", hitArray, !fOnline);
    mgr->RegisterAny("FrsMultiHitData", multihitArray, !fOnline);
    
    Setup_Conditions(pathToConfigFiles);
    c4LOG_IF(fatal,!conditions_files_read, "You must set FrsCal2Hit->Setup_Conditions('your file path') to the folder containing the frs condition gates.");
    
    hitArray->clear();
    multihitArray->clear();

    de_array = new uint32_t[14];
    dt_array = new uint32_t[16];
    de = new Float_t[3];
    de_cor = new Float_t[3];
    sci_l = new Float_t[6];
    sci_r = new Float_t[6];
    sci_tx = new Float_t[6];
    sci_e = new Float_t[6];
    sci_x = new Float_t[6];
    music_e1 = new uint32_t[8];
    music_e2 = new uint32_t[8];
    music_t1 = new uint32_t[8];
    music_t2 = new uint32_t[8];

    return kSUCCESS;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus FrsCal2Hit::ReInit()
{
    SetParContainers();
    return kSUCCESS;
}

void FrsCal2Hit::Exec(Option_t* option)
{   
    auto start = std::chrono::high_resolution_clock::now();

    hitArray->clear();
    multihitArray->clear();

    if (mainMusicArray->size() == 0) return;
    fNEvents++;
    
    uint64_t wr_t = 0; uint16_t tpat = 0;

    auto const & tpatItem = tpatArray->at(0);

    wr_t = tpatItem.Get_wr_t();
    tpat = tpatItem.Get_tpat();
    if (wr_t == 0) return;

    Long64_t FRS_time_mins = 0;
    FRS_time_mins = (wr_t - exp_config->exp_start_time)/ 60E9;


    if (scaler_check_first_event == 1)
    {
        for (auto const & mainScalerItem : *mainScalerArray)
        {
            uint32_t index = mainScalerItem.Get_index();
            uint32_t scaler = mainScalerItem.Get_scaler();
            sc_main_initial[index-1] = scaler;
            sc_main_previous[index-1] = scaler;
            sc_main_current[index-1] = scaler;
        }

        for (auto const & userScalerItem : *userScalerArray)
        {
            uint32_t index = userScalerItem.Get_index();
            uint32_t scaler = userScalerItem.Get_scaler();
            sc_user_initial[index-1] = scaler;
            sc_user_previous[index-1] = scaler;
            sc_user_current[index-1] = scaler;
        }

        scaler_check_first_event = 0;
    }
    else
    {
        for (auto const & mainScalerItem : *mainScalerArray)
        {
            uint32_t index = mainScalerItem.Get_index();
            uint32_t scaler = mainScalerItem.Get_scaler();
            sc_main_current[index-1] = scaler;
        }

        for (auto const & userScalerItem : *userScalerArray)
        {
            uint32_t index = userScalerItem.Get_index();
            uint32_t scaler = userScalerItem.Get_scaler();
            sc_user_current[index-1] = scaler;
        }
    }

    time_in_ms = sc_main_current[scaler_ch_1kHz] - sc_main_initial[scaler_ch_1kHz];

    if (time_in_ms < 0)
    {
        sc_main_initial[scaler_ch_1kHz] = sc_main_current[scaler_ch_1kHz];
        time_in_ms = 0;
    }

    spill_count = sc_user_current[scaler_ch_spillstart] - sc_user_initial[scaler_ch_spillstart];

    ibin_for_s = ((time_in_ms / 1000) % 1000) + 1;
    ibin_for_100ms = ((time_in_ms / 100) % 4000) + 1;
    ibin_for_spill  = (spill_count % 1000) + 1;

    for (int k = 0; k < 32; k++)
    {
        increase_sc_temp_main[k] = sc_main_current[k] - sc_main_previous[k];
        increase_sc_temp_user[k] = sc_user_current[k] - sc_user_previous[k];
    }

    if (increase_sc_temp_user[0] != 0 && increase_sc_temp_user[6] != 0) // not sure how the go4 is dealing with this zero dividing
    {
        increase_sc_temp2 = 100 * increase_sc_temp_user[1] / increase_sc_temp_user[0];
        increase_sc_temp3 = 100 * increase_sc_temp_user[5] / increase_sc_temp_user[6];
    }

    extraction_time_ms += sc_main_current[scaler_ch_1kHz] - sc_main_previous[scaler_ch_1kHz];

    if((sc_user_current[scaler_ch_spillstart] - sc_user_previous[scaler_ch_spillstart]) != 0)
    {
        extraction_time_ms = 0;
    }

    ibin_clean_for_s = (((time_in_ms / 1000) + 20) % 1000) + 1;
    ibin_clean_for_100ms = (((time_in_ms / 100) + 200) % 4000) + 1;
    ibin_clean_for_spill = ((spill_count + 990) % 20) + 1;

    for (int i = 0; i < 32; i++)
    {   
        sc_main_previous[i] = sc_main_current[i];
        sc_user_previous[i] = sc_user_current[i];
    }


    /* ---------------------------------------------------- */
    // Start of MUSIC analysis                              //
    /* ---------------------------------------------------- */
    
    auto const & mainMusicItem = mainMusicArray->at(0);
    
    music_t1 = mainMusicItem.Get_music_t1();
    music_t2 = mainMusicItem.Get_music_t2();

    auto const & userMusicItem = userMusicArray->at(0);
    music_e1 = userMusicItem.Get_music_e1();
    music_e2 = userMusicItem.Get_music_e2();

    music1_anodes_cnt = 0;
    music2_anodes_cnt = 0;

    /* reset de[i] and de_cor[i] etc */

    for (int i = 0; i < 8; i++)
    {
        /*  8 anodes of TUM MUSIC */
        // first MUSIC threshold changed to 4 (01/12/23)
        if (music_e1[i] > 4)
        {   
            if (music->exclude_de1_adc_channel[i] == kTRUE) music_b_e1[i] = false;
            else music_b_e1[i] = Check_WinCond_Multi(music_e1[i], cMusic1_E, i);

            if (music_b_e1[i])
            {
                music1_anodes_cnt++;
            }
        }
        if (music_t1[i] > 0)
        {
            music_b_t1[i] = Check_WinCond_Multi(music_t1[i], cMusic1_T, i);
        }

        // second MUSIC
        if (music_e2[i] > 4)
        {
            if (music->exclude_de2_adc_channel[i] == kTRUE) music_b_e2[i] = false;
            else music_b_e2[i] = Check_WinCond_Multi(music_e2[i], cMusic2_E, i);
            
            if (music_b_e2[i])
            {
                music2_anodes_cnt++;
            }
        }
        
        if (music_t2[i] > 0)
        {
            music_b_t2[i] = Check_WinCond_Multi(music_t2[i], cMusic2_T, i);
        }

    } // i loop

    #ifndef MUSIC_ANA_NEW
    if (music1_anodes_cnt == 8)
    {
        // What is up with the indexing here??
        //Float_t r1 = ((music_e1[0]) * music->e1_gain[0] + music->e1_off[0]) * ((music_e1[1]) * music->e1_gain[1] + music->e1_off[1]);
        Float_t r1 = ((music_e1[1]) * music->e1_gain[1] + music->e1_off[1]) * ((music_e1[1]) * music->e1_gain[1] + music->e1_off[1]);
        Float_t r2 = ((music_e1[2]) * music->e1_gain[2] + music->e1_off[2]) * ((music_e1[3]) * music->e1_gain[3] + music->e1_off[3]);
        Float_t r3 = ((music_e1[4]) * music->e1_gain[4] + music->e1_off[4]) * ((music_e1[5]) * music->e1_gain[5] + music->e1_off[5]);
        //Float_t r4 = ((music_e1[6]) * music->e1_gain[6] + music->e1_off[6]) * ((music_e1[7]) * music->e1_gain[7] + music->e1_off[7]);
        Float_t r4 = ((music_e1[6]) * music->e1_gain[6] + music->e1_off[6]) * ((music_e1[6]) * music->e1_gain[6] + music->e1_off[6]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            b_de1 = kTRUE;
            de[0] = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            de_cor[0] = de[0];
        }
    }
    #endif

    #ifdef MUSIC_ANA_NEW
    if (music1_anodes_cnt >= 4)
    {
        Float_t temp_de1 = 1.0;
        Float_t temp_count1 = 0;
        for (int i = 0; i < 8; i++)
        {
            if (music_b_e1[i])
            {
                temp_de1 *= ((music_e1[i]) * music->e1_gain[i] + music->e1_off[i]);
                temp_count1++;
            }
        }
        de[0] = TMath::Power(temp_de1, 1. / ((float)(temp_count1)));
        de_cor[0] = de[0];
        b_de1 = kTRUE;
    }
    #endif

    #ifndef MUSIC_ANA_NEW
    if (music2_anodes_cnt == 8)
    {
        Float_t r1 = ((music_e2[0]) * music->e2_gain[0] + music->e2_off[0]) * ((music_e2[1]) * music->e2_gain[1] + music->e2_off[1]);
        Float_t r2 = ((music_e2[2]) * music->e2_gain[2] + music->e2_off[2]) * ((music_e2[3]) * music->e2_gain[3] + music->e2_off[3]);
        Float_t r3 = ((music_e2[4]) * music->e2_gain[4] + music->e2_off[4]) * ((music_e2[5]) * music->e2_gain[5] + music->e2_off[5]);
        Float_t r4 = ((music_e2[6]) * music->e2_gain[6] + music->e2_off[6]) * ((music_e2[7]) * music->e2_gain[7] + music->e2_off[7]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            b_de2 = kTRUE;
            de[1] = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            de_cor[1] = de[1];
        }
    }
    #endif

    #ifdef MUSIC_ANA_NEW
    if (music2_anodes_cnt >= 4)
    {
        Float_t temp_de2 = 1.0;
        Int_t temp_count2 = 0;
        for (int i = 0; i < 8; i++)
        {
            if (music_b_e2[i])
            {
                temp_de2 *= ((music_e2[i]) * music->e2_gain[i] + music->e2_off[i]);
                temp_count2++;
            }
        }
        de[1] = TMath::Power(temp_de2, 1. / ((float)(temp_count2)));
        de_cor[1] = de[1];
        b_de2 = kTRUE;
    }
    #endif
    

    // Position (X) correction by TPC //
    // this should not be in the music3_anodes_cnt if{}
    // but it is in our Go4

    // we should extract everything from tpc.....
    auto const & tpcCalItem = tpcCalArray->at(0);

    // calculate "rates" for TPC here perhaps

    b_tpc_xy = tpcCalItem.Get_b_tpc_xy();
    
    if (b_tpc_xy[4] && b_tpc_xy[5])
    {
        music1_x_mean = tpcCalItem.Get_tpc_music41_x();
        music2_x_mean = tpcCalItem.Get_tpc_music42_x();

        if (b_de1)
        {
            power = 1.;
            Corr = 0.;
            for (int i = 0; i < 4; i++)
            {
                Corr += music->pos_a1[i] * power;
                power *= music1_x_mean;
            }
            if (Corr != 0)
            {
                Corr = music->pos_a1[0] / Corr;
                de_cor[0] = de[0] * Corr;
            }
        }

        if (b_de2)
        {
            power = 1.;
            Corr = 0.;
            for (int i = 0; i < 4; i++)
            {
                Corr += music->pos_a2[i] * power;
                power *= music2_x_mean;
            }
            if (Corr != 0)
            {
                Corr = music->pos_a2[0] / Corr;
                de_cor[1] = de[1] * Corr;
            }
        }
        
    }


    /* ----------------------------------------------- */
    // Start of Scintillator Analysis
    /* ----------------------------------------------- */

    auto const & mainSciItem = mainSciArray->at(0);
    auto const & userSciItem = userSciArray->at(0);

    
    // SCI 21 L and R
    int hits_in_21l = mainSciItem.Get_mhtdc_sc21l_nr_hits();
    int hits_in_21r = mainSciItem.Get_mhtdc_sc21r_nr_hits();
    
    int hits_in_21lr = hits_in_21l*hits_in_21r;
    mhtdc_sc21lr_dt = new Float_t[hits_in_21lr];
    mhtdc_sc21lr_x = new Float_t[hits_in_21lr];
    for (int i = 0; i < hits_in_21l; i++)
    {
        for (int j = 0; j < hits_in_21r; j ++){
        mhtdc_sc21lr_dt[i*hits_in_21r + j] = sci->mhtdc_factor_ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc21l_hit(i) - mainSciItem.Get_mhtdc_sc21r_hit(j));
        mhtdc_sc21lr_x[i*hits_in_21r + j] = mhtdc_sc21lr_dt[i*hits_in_21r + j] * sci->mhtdc_factor_21l_21r + sci->mhtdc_offset_21l_21r;

        // double p0 = -72.5554;
        // double p1 =  54.9136;
        // double p2 =  1.14567;
        // double p3 = -5.12242;
        // double p4 =  3.70734;
        // double p5 = -0.72347;

        //mhtdc_sc21lr_x[i*hits_in_21r + j] = TMath::Power(mhtdc_sc21lr_dt[i*hits_in_21r + j],5)*p5 +TMath::Power(mhtdc_sc21lr_dt[i*hits_in_21r + j],4)*p4 +TMath::Power(mhtdc_sc21lr_dt[i*hits_in_21r + j],3)*p3 +TMath::Power(mhtdc_sc21lr_dt[i*hits_in_21r + j],2)*p2 +TMath::Power(mhtdc_sc21lr_dt[i*hits_in_21r + j],1)*p1 + p0;

        }
    }

    float sc21pos_from_tpc = -999.9;
    if (b_tpc_xy[0] && b_tpc_xy[1])
    {
        sc21pos_from_tpc = tpcCalItem.Get_tpc21_22_sc21_x();
    }
    else if (b_tpc_xy[2] && b_tpc_xy[3])
    {
        sc21pos_from_tpc = tpcCalItem.Get_tpc23_24_sc21_x();
    }

    // SCI 21 L and R
    int hits_in_22l = mainSciItem.Get_mhtdc_sc22l_nr_hits();
    int hits_in_22r = mainSciItem.Get_mhtdc_sc22r_nr_hits();
    
    int hits_in_22lr = mainSciItem.Get_mhtdc_sc22l_nr_hits()*mainSciItem.Get_mhtdc_sc22r_nr_hits();
    mhtdc_sc22lr_dt = new Float_t[hits_in_22lr];
    mhtdc_sc22lr_x = new Float_t[hits_in_22lr];
    for (int i = 0; i < mainSciItem.Get_mhtdc_sc22l_nr_hits(); i++)
    {
        for (int j = 0; j < mainSciItem.Get_mhtdc_sc22r_nr_hits(); j ++){
        mhtdc_sc22lr_dt[i*mainSciItem.Get_mhtdc_sc22r_nr_hits() + j] = sci->mhtdc_factor_ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc22l_hit(i) - mainSciItem.Get_mhtdc_sc22r_hit(j));
        mhtdc_sc22lr_x[i*mainSciItem.Get_mhtdc_sc22r_nr_hits() + j] = mhtdc_sc22lr_dt[i*mainSciItem.Get_mhtdc_sc22r_nr_hits() + j] * sci->mhtdc_factor_22l_22r + sci->mhtdc_offset_22l_22r;
        }
        if (i == 0)
        {
            // only do this if there is a case for 22l and 22r != 0. we don't need to do it 10x though
            float sc22pos_from_tpc = -999.9;
            if (b_tpc_xy[0] && b_tpc_xy[1])
            {
                sc22pos_from_tpc = tpcCalItem.Get_tpc21_22_sc22_x();
            }
            else if (b_tpc_xy[2] && b_tpc_xy[3])
            {
                sc22pos_from_tpc = tpcCalItem.Get_tpc23_24_sc22_x();
            }
        }
    }

    // SCI 41 L and R
    int hits_in_41l = mainSciItem.Get_mhtdc_sc41l_nr_hits();
    int hits_in_41r = mainSciItem.Get_mhtdc_sc41r_nr_hits();
    int hits_in_41lr = hits_in_41l*hits_in_41r;
    mhtdc_sc41lr_dt = new Float_t[hits_in_41lr];
    mhtdc_sc41lr_x = new Float_t[hits_in_41lr];
    for (int i = 0; i < hits_in_41l; i++)
    {
        for (int j = 0; j < hits_in_41r; j ++){
        mhtdc_sc41lr_dt[i*hits_in_41r + j] = sci->mhtdc_factor_ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc41l_hit(i) - mainSciItem.Get_mhtdc_sc41r_hit(j));
        mhtdc_sc41lr_x[i*hits_in_41r + j] = mhtdc_sc41lr_dt[i*hits_in_41r + j] * sci->mhtdc_factor_41l_41r + sci->mhtdc_offset_41l_41r;
        }
    }
    // SCI 42 L and R
    int hits_in_42l = mainSciItem.Get_mhtdc_sc42l_nr_hits();
    int hits_in_42r = mainSciItem.Get_mhtdc_sc42r_nr_hits();
    int hits_in_42lr = hits_in_42l*hits_in_42r;
    mhtdc_sc42lr_dt = new Float_t[hits_in_42lr];
    mhtdc_sc42lr_x = new Float_t[hits_in_42lr];
    for (int i = 0; i < hits_in_42l; i++)
    {
        for (int j = 0; j < hits_in_42r; j ++){
        mhtdc_sc42lr_dt[i*hits_in_42r + j] = sci->mhtdc_factor_ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc42l_hit(i) - mainSciItem.Get_mhtdc_sc42r_hit(j));
        mhtdc_sc42lr_x[i*hits_in_42r + j] = mhtdc_sc42lr_dt[i*hits_in_42r + j] * sci->mhtdc_factor_42l_42r + sci->mhtdc_offset_42l_42r;
        }
    }    
    
    // SCI 43 L and R
    int hits_in_43l = mainSciItem.Get_mhtdc_sc43l_nr_hits();
    int hits_in_43r = mainSciItem.Get_mhtdc_sc43r_nr_hits();
    int hits_in_43lr = hits_in_43l*hits_in_43r;
    mhtdc_sc43lr_dt = new Float_t[hits_in_43lr];
    mhtdc_sc43lr_x = new Float_t[hits_in_43lr];
    for (int i = 0; i < hits_in_43l; i++)
    {
        for (int j = 0; j < hits_in_43r; j ++){
        mhtdc_sc43lr_dt[i*hits_in_43r + j] = sci->mhtdc_factor_ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc43l_hit(i) - mainSciItem.Get_mhtdc_sc43r_hit(j));
        mhtdc_sc43lr_x[i*hits_in_43r + j] = mhtdc_sc43lr_dt[i*hits_in_43r + j] * sci->mhtdc_factor_43l_43r + sci->mhtdc_offset_43l_43r;
        }
    }

    // SCI 31 L and R
    int hits_in_31l = mainSciItem.Get_mhtdc_sc31l_nr_hits();
    int hits_in_31r = mainSciItem.Get_mhtdc_sc31r_nr_hits();
    int hits_in_31lr = hits_in_31l*hits_in_31r;
    mhtdc_sc31lr_dt = new Float_t[hits_in_31lr];
    mhtdc_sc31lr_x = new Float_t[hits_in_31lr];
    for (int i = 0; i < hits_in_31l; i++)
    {
        for (int j = 0; j < hits_in_31r; j ++){
        mhtdc_sc31lr_dt[i*hits_in_31r + j] = sci->mhtdc_factor_ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc31l_hit(i) - mainSciItem.Get_mhtdc_sc31r_hit(j));
        mhtdc_sc31lr_x[i*hits_in_31r + j] = mhtdc_sc31lr_dt[i*hits_in_31r + j] * sci->mhtdc_factor_31l_31r + sci->mhtdc_offset_31l_31r;
        }
    }

      
    //TOF:
    // 21 -> 41
    int hits_in_tof4121 = hits_in_41lr*hits_in_21lr;
    mhtdc_tof4121 = new Float_t[hits_in_tof4121];
    //c4LOG(info,hits_in_tof4121);
    //c4LOG(info,hits_in_41lr);
    for (int i = 0; i < hits_in_41l; i++)
    {
        for (int j = 0; j<hits_in_41r; j++)
        {
            //c4LOG(info,0.5*sci->mhtdc_factor_ch_to_ns * (mainSciItem.Get_mhtdc_sc41l_hit(i) + mainSciItem.Get_mhtdc_sc41r_hit(j)));
            //c4LOG(info,sci->mhtdc_factor_ch_to_ns * (mainSciItem.Get_mhtdc_sc41l_hit(i)));
            //c4LOG(info,sci->mhtdc_factor_ch_to_ns * (mainSciItem.Get_mhtdc_sc41r_hit(j)));
            //c4LOG(info,sci->mhtdc_factor_ch_to_ns * (mainSciItem.Get_mhtdc_sc41l_hit(i)-mainSciItem.Get_mhtdc_sc41r_hit(j)));
            for (int k = 0; k < hits_in_21l; k++) 
            {
                for (int l = 0; l<hits_in_21r; l++)
                {
                    if ((sci->mhtdc_factor_ch_to_ns*TMath::Abs(mainSciItem.Get_mhtdc_sc41l_hit(i) - mainSciItem.Get_mhtdc_sc41r_hit(j)) < 40) && (sci->mhtdc_factor_ch_to_ns*TMath::Abs(mainSciItem.Get_mhtdc_sc21l_hit(k) - mainSciItem.Get_mhtdc_sc21r_hit(l)) < 40)){
                    mhtdc_tof4121[i*hits_in_41r*hits_in_21l*hits_in_21r + j*hits_in_21l*hits_in_21r + k*hits_in_21r + l] = sci->mhtdc_factor_ch_to_ns * (0.5 * (mainSciItem.Get_mhtdc_sc41l_hit(i) + mainSciItem.Get_mhtdc_sc41r_hit(j)) - 0.5 * (mainSciItem.Get_mhtdc_sc21l_hit(k) + mainSciItem.Get_mhtdc_sc21r_hit(l))) + sci->mhtdc_offset_41_21;
                    }else{
                    mhtdc_tof4121[i*hits_in_41r*hits_in_21l*hits_in_21r + j*hits_in_21l*hits_in_21r + k*hits_in_21r + l] = -999;
                    }
                }
            }
        }
    }

    // 22 -> 41
    int hits_in_tof4122 = hits_in_41lr*hits_in_22lr;
    mhtdc_tof4122 = new Float_t[hits_in_tof4122];
    for (int i = 0; i < hits_in_41l; i++) 
    {
        for (int j = 0; j<hits_in_41r; j++)
        {
            for (int k = 0; k < hits_in_22l; k++) 
            {
                for (int l = 0; l<hits_in_22r; l++)
                {
                    if ((sci->mhtdc_factor_ch_to_ns*TMath::Abs(mainSciItem.Get_mhtdc_sc41l_hit(i) - mainSciItem.Get_mhtdc_sc41r_hit(j)) < 40) && (sci->mhtdc_factor_ch_to_ns*TMath::Abs(mainSciItem.Get_mhtdc_sc22l_hit(k) - mainSciItem.Get_mhtdc_sc22r_hit(l)) < 40)){
                    mhtdc_tof4122[i*hits_in_41r*hits_in_22l*hits_in_22r + j*hits_in_22l*hits_in_22r + k*hits_in_22r + l] = sci->mhtdc_factor_ch_to_ns * (0.5 * (mainSciItem.Get_mhtdc_sc41l_hit(i) + mainSciItem.Get_mhtdc_sc41r_hit(j)) - 0.5 * (mainSciItem.Get_mhtdc_sc22l_hit(k) + mainSciItem.Get_mhtdc_sc22r_hit(l))) + sci->mhtdc_offset_41_22;
                    }else{
                    mhtdc_tof4122[i*hits_in_41r*hits_in_22l*hits_in_22r + j*hits_in_22l*hits_in_22r + k*hits_in_22r + l] = -999;
                    }
                }
            }
        }
    }

    // 21 -> 42
    int hits_in_tof4221 = hits_in_42lr*hits_in_21lr;
    mhtdc_tof4221 = new Float_t[hits_in_tof4221];
    for (int i = 0; i < hits_in_42l; i++) 
    {
        for (int j = 0; j<hits_in_42r; j++)
        {
            for (int k = 0; k < hits_in_21l; k++) 
            {
                for (int l = 0; l<hits_in_21r; l++)
                {
                    if ((sci->mhtdc_factor_ch_to_ns*TMath::Abs(mainSciItem.Get_mhtdc_sc42l_hit(i) - mainSciItem.Get_mhtdc_sc42r_hit(j)) < 40) && (sci->mhtdc_factor_ch_to_ns*TMath::Abs(mainSciItem.Get_mhtdc_sc21l_hit(k) - mainSciItem.Get_mhtdc_sc21r_hit(l)) < 40)){
                    mhtdc_tof4221[i*hits_in_42r*hits_in_21l*hits_in_21r + j*hits_in_21l*hits_in_21r + k*hits_in_21r + l] = sci->mhtdc_factor_ch_to_ns * (0.5 * (mainSciItem.Get_mhtdc_sc42l_hit(i) + mainSciItem.Get_mhtdc_sc42r_hit(j)) - 0.5 * (mainSciItem.Get_mhtdc_sc21l_hit(k) + mainSciItem.Get_mhtdc_sc21r_hit(l))) + sci->mhtdc_offset_42_21;
                    }else{
                    mhtdc_tof4221[i*hits_in_42r*hits_in_21l*hits_in_21r + j*hits_in_21l*hits_in_21r + k*hits_in_21r + l] = -999;
                    }
                }
            }
        }
    }


    // 21 -> 43
    int hits_in_tof4321 = hits_in_43lr*hits_in_21lr;
    mhtdc_tof4321 = new Float_t[hits_in_tof4321];
    for (int i = 0; i < hits_in_43l; i++) 
    {
        for (int j = 0; j<hits_in_43r; j++)
        {
            for (int k = 0; k < hits_in_21l; k++) 
            {
                for (int l = 0; l<hits_in_21r; l++)
                {
                    mhtdc_tof4321[i*hits_in_43r*hits_in_21l*hits_in_21r + j*hits_in_21l*hits_in_21r + k*hits_in_21r + l] = sci->mhtdc_factor_ch_to_ns * (0.5 * (mainSciItem.Get_mhtdc_sc43l_hit(i) + mainSciItem.Get_mhtdc_sc43r_hit(j)) - 0.5 * (mainSciItem.Get_mhtdc_sc21l_hit(k) + mainSciItem.Get_mhtdc_sc21r_hit(l))) + sci->mhtdc_offset_43_21;
                }
            }
        }
    }
    
    // 21 -> 31
    
    int hits_in_tof3121 = hits_in_31lr*hits_in_21lr;
    mhtdc_tof3121 = new Float_t[hits_in_tof3121];
    for (int i = 0; i < hits_in_31l; i++) 
    {
        for (int j = 0; j<hits_in_31r; j++)
        {
            for (int k = 0; k < hits_in_21l; k++) 
            {
                for (int l = 0; l<hits_in_21r; l++)
                {
                    mhtdc_tof3121[i*hits_in_31r*hits_in_21l*hits_in_21r + j*hits_in_21l*hits_in_21r + k*hits_in_21r + l] = sci->mhtdc_factor_ch_to_ns * (0.5 * (mainSciItem.Get_mhtdc_sc31l_hit(i) + mainSciItem.Get_mhtdc_sc31r_hit(j)) - 0.5 * (mainSciItem.Get_mhtdc_sc21l_hit(k) + mainSciItem.Get_mhtdc_sc21r_hit(l))) + sci->mhtdc_offset_31_21;
                }
            }
        }
    }


    /*
    // 21 -> 81
    int hits_in_tof8121 = hits_in_81lr*hits_in_21lr;
    mhtdc_tof8121 = new Float_t[hits_in_tof8121];
    
    for (int i = 0; i < hits_in_81l; i++) 
    {
        for (int j = 0; j<hits_in_81r; j++)
        {
            for (int k = 0; k < hits_in_21l; k++) 
            {
                for (int l = 0; l<hits_in_21r; l++)
                {
                    mhtdc_tof8121[i*hits_in_81r*hits_in_21l*hits_in_21r + j*hits_in_21l*hits_in_21r + k*hits_in_21r + l] = sci->mhtdc_factor_ch_to_ns * (0.5 * (mainSciItem.Get_mhtdc_sc81l_hit(i) + mainSciItem.Get_mhtdc_sc81r_hit(j)) - 0.5 * (mainSciItem.Get_mhtdc_sc21l_hit(k) + mainSciItem.Get_mhtdc_sc21r_hit(l))) + sci->mhtdc_offset_81_21;
                }
            }
        }
    }
    */


    // SCI 21
    de_21l = mainSciItem.Get_dE_21l(); bool sci_b_21l = Check_WinCond(de_21l, cSCI_L);
    de_21r = mainSciItem.Get_dE_21r(); bool sci_b_21r = Check_WinCond(de_21r, cSCI_R);
    if (sci_b_21l && sci_b_21r) sci_e_21 = sqrt((de_21l - sci->le_a[0][2]) * sci->le_a[1][2] * (de_21r - sci->re_a[0][2]) * sci->re_a[1][2]);
    bool sci_b_e_21 = Check_WinCond(sci_e_21, cSCI_E);
    
    sci_tx_21lr = userSciItem.Get_dT_21l_21r() + rand3();
    bool sci_b_tx_21lr = Check_WinCond(sci_tx_21lr, cSCI_Tx);
    if (sci_b_tx_21lr)
    {
        Float_t R = sci_tx_21lr;
        power = 1.; sum = 0.;
        for (int i = 0; i < 7; i++)
        {
            sum += sci->x_a[i][2] * power; power *= R;
        }
        sci_x_21 = sum;
    }
    bool sci_b_x_21 = Check_WinCond(sci_x_21, cSCI_X);
    

    // SCI 22
    de_22l = mainSciItem.Get_dE_22l(); bool sci_b_22l = Check_WinCond(de_22l, cSCI_L);
    de_22r = mainSciItem.Get_dE_22r(); bool sci_b_22r = Check_WinCond(de_22r, cSCI_R);
    if (sci_b_22l && sci_b_22r) sci_e_22 = sqrt((de_22l - sci->le_a[0][3]) * sci->le_a[1][3] * (de_22r - sci->re_a[0][3]) * sci->re_a[1][3]);
    bool sci_b_e_22 = Check_WinCond(sci_e_22, cSCI_E);
    
    sci_tx_22lr = userSciItem.Get_dT_22l_22r() + rand3();
    bool sci_b_tx_22lr = Check_WinCond(sci_tx_22lr, cSCI_Tx);
    if (sci_b_tx_22lr)
    {
        Float_t R = sci_tx_22lr;
        power = 1.; sum = 0.;
        for (int i = 0; i < 7; i++)
        {
            sum += sci->x_a[i][3] * power; power *= R;
        }
        sci_x_22 = sum;
    }
    bool sci_b_x_22 = Check_WinCond(sci_x_22, cSCI_X);

    // SCI 31
    de_31l = mainSciItem.Get_dE_31l(); bool sci_b_31l = Check_WinCond(de_31l, cSCI_L);
    de_31r = mainSciItem.Get_dE_31r(); bool sci_b_31r = Check_WinCond(de_31r, cSCI_R);
    if (sci_b_31l && sci_b_31r) sci_e_31 = sqrt((de_31l - sci->le_a[0][4]) * sci->le_a[1][4] * (de_31r - sci->re_a[0][4]) * sci->re_a[1][4]);
    bool sci_b_e_31 = Check_WinCond(sci_e_31, cSCI_E);

    // SCI 41
    de_41l = mainSciItem.Get_dE_41l(); bool sci_b_41l = Check_WinCond(de_41l, cSCI_L);
    de_41r = mainSciItem.Get_dE_41r(); bool sci_b_41r = Check_WinCond(de_41r, cSCI_R);
    if (sci_b_41l && sci_b_41r) sci_e_41 = sqrt((de_41l - sci->le_a[0][5]) * sci->le_a[1][5] * (de_41r - sci->re_a[0][5]) * sci->re_a[1][5]);
    bool sci_b_e_41 = Check_WinCond(sci_e_41, cSCI_E);
    
    sci_tx_41lr = userSciItem.Get_dT_41l_41r() + rand3();
    bool sci_b_tx_41lr = Check_WinCond(sci_tx_41lr, cSCI_Tx);
    if (sci_b_tx_41lr)
    {
        Float_t R = sci_tx_41lr;
        power = 1.; sum = 0.;
        for (int i = 0; i < 7; i++)
        {
            sum += sci->x_a[i][5] * power; power *= R;
        }
        sci_x_41 = sum;
    }
    bool sci_b_x_41 = Check_WinCond(sci_x_41, cSCI_X);

    // SCI 42
    de_42l = mainSciItem.Get_dE_42l(); bool sci_b_42l = Check_WinCond(de_42l, cSCI_L);
    de_42r = mainSciItem.Get_dE_42r(); bool sci_b_42r = Check_WinCond(de_42r, cSCI_R);
    if (sci_b_42l && sci_b_42r) sci_e_42 = sqrt((de_42l - sci->le_a[0][6]) * sci->le_a[1][6] * (de_42r - sci->re_a[0][6]) * sci->re_a[1][6]);
    bool sci_b_e_42 = Check_WinCond(sci_e_42, cSCI_E);
    
    sci_tx_42lr = userSciItem.Get_dT_42l_42r() + rand3();
    bool sci_b_tx_42lr = Check_WinCond(sci_tx_42lr, cSCI_Tx);
    if (sci_b_tx_42lr)
    {
        Float_t R = sci_tx_42lr;
        power = 1.; sum = 0.;
        for (int i = 0; i < 7; i++)
        {
            sum += sci->x_a[i][6] * power; power *= R;
        }
        sci_x_42 = sum;
    }
    bool sci_b_x_42 = Check_WinCond(sci_x_42, cSCI_X);

    // SCI 43
    de_43l = mainSciItem.Get_dE_43l(); bool sci_b_43l = Check_WinCond(de_43l, cSCI_L);
    de_43r = mainSciItem.Get_dE_43r(); bool sci_b_43r = Check_WinCond(de_43r, cSCI_R);
    if (sci_b_43l && sci_b_43r) sci_e_43 = sqrt((de_43l - sci->le_a[0][7]) * sci->le_a[1][7] * (de_43r - sci->re_a[0][7]) * sci->re_a[1][7]);
    bool sci_b_e_43 = Check_WinCond(sci_e_43, cSCI_E);

    sci_tx_43lr = userSciItem.Get_dT_43l_43r() + rand3();
    bool sci_b_tx_43lr = Check_WinCond(sci_tx_43lr, cSCI_Tx);
    if (sci_b_tx_43lr)
    {
        Float_t R = sci_tx_43lr;
        power = 1.; sum = 0.;
        for (int i = 0; i < 7; i++)
        {
            sum += sci->x_a[i][7] * power; power *= R;
        }
        sci_x_43 = sum;
    }
    bool sci_b_x_43 = Check_WinCond(sci_x_43, cSCI_X);

    // SCI 81
    de_81l = mainSciItem.Get_dE_81l(); bool sci_b_81l = Check_WinCond(de_81l, cSCI_L);
    de_81r = mainSciItem.Get_dE_81r(); bool sci_b_81r = Check_WinCond(de_81r, cSCI_R);
    if (sci_b_81l && sci_b_81r) sci_e_81 = sqrt((de_81l - sci->le_a[0][10]) * sci->le_a[1][10] * (de_81r - sci->re_a[0][10]) * sci->re_a[1][10]);
    bool sci_b_e_81 = Check_WinCond(sci_e_81, cSCI_E);
    
    sci_tx_81lr = userSciItem.Get_dT_81l_81r() + rand3();
    bool sci_b_tx_81lr = Check_WinCond(sci_tx_81lr, cSCI_Tx);
    if (sci_b_tx_81lr)
    {
        Float_t R = sci_tx_81lr;
        power = 1.; sum = 0.;
        for (int i = 0; i < 7; i++)
        {
            sum += sci->x_a[i][10] * power; power *= R;
        }
        sci_x_81 = sum;
    }
    bool sci_b_x_81 = Check_WinCond(sci_x_81, cSCI_X);


    /*-----------------------------------*/
    // Calibrated ToF
    /*-----------------------------------*/
    // SCI 21 - 41
    sci_tofll_21_41 = userSciItem.Get_dT_21l_41l() * sci->tac_factor[2] - sci->tac_off[2];
    sci_tofrr_21_41 = userSciItem.Get_dT_21r_41r() * sci->tac_factor[3] - sci->tac_off[3];
    bool sci_b_tofll_21_41 = Check_WinCond(sci_tofll_21_41, cSCI_LL2);
    bool sci_b_tofrr_21_41 = Check_WinCond(sci_tofrr_21_41, cSCI_RR2);

    if (sci_b_tofll_21_41 && sci_b_tofrr_21_41)
    {
        sci_tof_21_41 = (sci->tof_bll2 * sci_tofll_21_41 + sci->tof_a2 + sci->tof_brr2 * sci_tofrr_21_41) / 2.0;
        sci_tof_21_41_calib = -1.0 * sci_tof_21_41 + id->id_tofoff2;
    }
    else
    {
        sci_tof_21_41 = 0;
        sci_tof_21_41_calib = 0;
    }

    // SCI 21 - 42
    sci_tofll_21_42 = userSciItem.Get_dT_42l_21l() * sci->tac_factor[5] - sci->tac_off[5];
    sci_tofrr_21_42 = userSciItem.Get_dT_42r_21r() * sci->tac_factor[6] - sci->tac_off[6];
    bool sci_b_tofll_21_42 = Check_WinCond(sci_tofll_21_42, cSCI_LL3);
    bool sci_b_tofrr_21_42 = Check_WinCond(sci_tofrr_21_42, cSCI_RR3);
    if (sci_b_tofll_21_42 && sci_b_tofrr_21_42)
    {
        sci_tof_21_42 = (sci->tof_bll3 * sci_tofll_21_42 + sci->tof_a3 + sci->tof_brr3 * sci_tofrr_21_42) / 2.0;
        sci_tof_21_42_calib = -1.0 * sci_tof_21_42 + id->id_tofoff3;
    }
    else
    {
        sci_tof_21_42 = 0;
        sci_tof_21_42_calib = 0;
    }

    // SCI 21 - 81
    sci_tofll_21_81 = userSciItem.Get_dT_21l_81l() * sci->tac_factor[9] - sci->tac_off[9];
    sci_tofrr_21_81 = userSciItem.Get_dT_21r_81r() * sci->tac_factor[10] - sci->tac_off[10];
    bool sci_b_tofll_21_81 = Check_WinCond(sci_tofll_21_81, cSCI_LL4);
    bool sci_b_tofrr_21_81 = Check_WinCond(sci_tofrr_21_81, cSCI_RR4);
    if (sci_b_tofll_21_81 && sci_b_tofrr_21_81)
    {
        sci_tof_21_81 = (sci->tof_bll4 * sci_tofll_21_81 + sci->tof_a4 + sci->tof_brr4 * sci_tofrr_21_81) / 2.0;
        sci_tof_21_81_calib = -1.0 * sci_tof_21_81 + id->id_tofoff4;
    }
    else
    {
        sci_tof_21_81 = 0;
        sci_tof_21_81_calib = 0;
    }

    // SCI 22 - 41
    sci_tofll_22_41 = userSciItem.Get_dT_22l_41l() * sci->tac_factor[12] - sci->tac_off[12];
    sci_tofrr_22_41 = userSciItem.Get_dT_22r_41r() * sci->tac_factor[13] - sci->tac_off[13];
    bool sci_b_tofll_22_41 = Check_WinCond(sci_tofll_22_41, cSCI_LL5);
    bool sci_b_tofrr_22_41 = Check_WinCond(sci_tofrr_22_41, cSCI_RR5);
    if (sci_b_tofll_22_41 && sci_b_tofrr_22_41)
    {
        sci_tof_22_41 = (sci->tof_bll5 * sci_tofll_22_41 + sci->tof_a5 + sci->tof_brr5 * sci_tofrr_22_41) / 2.0;
        sci_tof_22_41_calib = -1.0 * sci_tof_22_41 + id->id_tofoff5;
    }
    else
    {
        sci_tof_22_41 = 0;
        sci_tof_22_41_calib = 0;
    }

    // SCI 22 - 81
    sci_tofll_22_81 = userSciItem.Get_dT_22l_81l() * sci->tac_factor[14] - sci->tac_off[14];
    sci_tofrr_22_81 = userSciItem.Get_dT_22r_81r() * sci->tac_factor[15] - sci->tac_off[15];
    bool sci_b_tofll_22_81 = Check_WinCond(sci_tofll_22_81, cSCI_LL6);
    bool sci_b_tofrr_22_81 = Check_WinCond(sci_tofrr_22_81, cSCI_RR6);
    if (sci_b_tofll_22_81 && sci_b_tofrr_22_81)
    {
        sci_tof_22_81 = (sci->tof_bll6 * sci_tofll_22_81 + sci->tof_a6 + sci->tof_brr6 * sci_tofrr_22_81) / 2.0;
        sci_tof_22_81_calib = -1.0 * sci_tof_22_81 + id->id_tofoff6;
    }
    else
    {
        sci_tof_22_81 = 0;
        sci_tof_22_81_calib = 0;
    }




    /*----------------------------------------------------------*/
    // Start of MHTDC ID analysis
    /*----------------------------------------------------------*/
   
    float temp_s8x = mhtdc_sc81lr_x[0]; // NB mhtdc!
    temp_s4x = -999.;
    float temp_a4 = -999;
    if (b_tpc_xy[4] && b_tpc_xy[5])
    {
        temp_s4x = tpcCalItem.Get_tpc_x_s4();
        temp_a4 = tpcCalItem.Get_tpc_angle_x_s4();
    }

    //float temp_s2x = -999.;
    float temp_a2 = 0;
    int hits_in_s2x = 0;

    if (id->x_s2_select == 2)
    {
        temp_s2x_mhtdc = new Float_t[hits_in_21lr];
        for (int i = 0; i<hits_in_21lr; i++) temp_s2x_mhtdc[i] = mhtdc_sc21lr_x[i];
        hits_in_s2x = hits_in_21lr;
        temp_a2 = 0;
    }
    else if (id->x_s2_select == 3)
    {
        temp_s2x_mhtdc = new Float_t[hits_in_22lr];
        for (int i = 0; i < hits_in_22lr; i++) temp_s2x_mhtdc[i] = mhtdc_sc22lr_x[i];
        hits_in_s2x = hits_in_22lr;
        temp_a2 = 0;
    }
    else if (id->x_s2_select == 1)
    {
        temp_s2x_mhtdc = new Float_t[1];
        if (b_tpc_xy[2] && b_tpc_xy[3])
        {
            temp_s2x_mhtdc[0] = tpcCalItem.Get_tpc_x_s2_foc_23_24();
            temp_a2 = tpcCalItem.Get_tpc_angle_x_s2_foc_23_24();
        }
        else if (b_tpc_xy[1] && b_tpc_xy[3])
        {
            temp_s2x_mhtdc[0] = tpcCalItem.Get_tpc_x_s2_foc_22_24();
            temp_a2 = tpcCalItem.Get_tpc_angle_x_s2_foc_22_24();
        }
        else if (b_tpc_xy[0] && b_tpc_xy[1])
        {
            temp_s2x_mhtdc[0] = tpcCalItem.Get_tpc_x_s2_foc_21_22();
            temp_a2 = tpcCalItem.Get_tpc_angle_x_s2_foc_21_22();
        }
        hits_in_s2x = 1;
    }


    //   S2S4 MultihitTDC ID analysis
    float mean_brho_s2s4 = 0.5 * (frs->bfield[2] + frs->bfield[3]);

    int hits_in_beta_s2s4 = 0;
    if (id->tof_s4_select == 1)
    {
        hits_in_beta_s2s4 = hits_in_tof4121;
        id_mhtdc_beta_s2s4 = new Float_t[hits_in_tof4121];
        id_mhtdc_tof_s2s4 = new Float_t[hits_in_tof4121];
        for (int i = 0; i < hits_in_tof4121; i++)
        {
            id_mhtdc_tof_s2s4[i] = mhtdc_tof4121[i];
            if (mhtdc_tof4121[i] > 0) // what is the value set to if this test fails ... ?
            {
                id_mhtdc_beta_s2s4[i] = (id->mhtdc_length_sc2141 / mhtdc_tof4121[i])/ speed_light;
            }else{
                id_mhtdc_beta_s2s4[i] = 0;
            }
        }
    }
    else if (id->tof_s4_select == 3)
    {
        hits_in_beta_s2s4 = hits_in_tof4122;            
        id_mhtdc_beta_s2s4 = new Float_t[hits_in_tof4122];
        id_mhtdc_tof_s2s4 = new Float_t[hits_in_tof4121];
        for (int i = 0; i < hits_in_tof4122; i++)
        {
            id_mhtdc_tof_s2s4[i] = mhtdc_tof4122[i];
            if (mhtdc_tof4122[i] > 0)
            {
                id_mhtdc_beta_s2s4[i] = (id->mhtdc_length_sc2241 / mhtdc_tof4122[i])/speed_light;
            }else{
                id_mhtdc_beta_s2s4[i] = 0;
            }
        }
    }else{
        c4LOG(fatal, "Unrecognized option, tof_s4_select != 1 || 3?.");
    }

    // calculate delta (momentum deviation) and AoQ
    int hits_in_aoq = hits_in_beta_s2s4*hits_in_s2x;
    id_mhtdc_gamma_s2s4 = new Float_t[hits_in_beta_s2s4];
    id_mhtdc_delta_s2s4 = new Float_t[hits_in_aoq];
    id_mhtdc_aoq_s2s4 = new Float_t[hits_in_aoq];
    id_mhtdc_aoq_corr_s2s4 = new Float_t[hits_in_aoq];

    for (int i = 0; i < hits_in_beta_s2s4; i++)
    {
        id_mhtdc_gamma_s2s4[i] = 1. / sqrt(1. - id_mhtdc_beta_s2s4[i] * id_mhtdc_beta_s2s4[i]);
        
        for (int j = 0; j<hits_in_s2x; j++){
            if (temp_s4x > -200. && temp_s4x < 200. && temp_s2x_mhtdc[j] > -200. && temp_s2x_mhtdc[j] < 200.)
            {

                id_mhtdc_delta_s2s4[i*hits_in_s2x + j] = (temp_s4x - (temp_s2x_mhtdc[j] * frs->magnification[1])) / (1.0 * frs->dispersion[1] * 1000.0); // metre to mm
                
                if (id->x_s2_select == 2 && id->tof_s4_select == 1){ // need to make sure that beta and s2x are from the same time stamp (i.e. a time gate is needed)
                    int time_stamp_sc21r_x = mainSciItem.Get_mhtdc_sc21r_hit(j%hits_in_21r);
                    int time_stamp_sc21r_beta = mainSciItem.Get_mhtdc_sc21r_hit(i%hits_in_21r);
                    if (TMath::Abs(time_stamp_sc21r_beta - time_stamp_sc21r_x) > 500){
                        id_mhtdc_aoq_s2s4[i*hits_in_s2x + j] = -999;
                        id_mhtdc_aoq_corr_s2s4[i*hits_in_s2x + j] = -999;
                        continue;
                    }
                }

                if (id_mhtdc_beta_s2s4[i] > 0.5 && id_mhtdc_beta_s2s4[i] < 1)
                {
                    id_mhtdc_aoq_s2s4[i*hits_in_s2x + j] = mean_brho_s2s4 * (1. - id_mhtdc_delta_s2s4[i*hits_in_s2x + j]) * temp_tm_to_MeV / (temp_mu * id_mhtdc_beta_s2s4[i] * id_mhtdc_gamma_s2s4[i]);

                    // using angle at S4 to correct AoQ
                    id_mhtdc_aoq_corr_s2s4[i*hits_in_s2x + j] = id_mhtdc_aoq_s2s4[i*hits_in_s2x + j] - id->a4AoQCorr * temp_a4;

                }else{
                    id_mhtdc_aoq_s2s4[i*hits_in_s2x + j] = -999;
                    id_mhtdc_aoq_corr_s2s4[i*hits_in_s2x + j] = -999;
                }
            }else{
                id_mhtdc_aoq_s2s4[i*hits_in_s2x + j] = -999;
                id_mhtdc_aoq_corr_s2s4[i*hits_in_s2x + j] = -999;
            }
        }
    }


    // Calculation of dE and Z from MUSIC41
    // Calibration for MUSIC is done with 1/b2 - last update sept2024
    id_mhtdc_v_cor_music41 = new Float_t[hits_in_beta_s2s4];
    id_mhtdc_v_cor_music42 = new Float_t[hits_in_beta_s2s4];

    id_mhtdc_z_music41 = new Float_t[hits_in_beta_s2s4];
    id_mhtdc_z_music42 = new Float_t[hits_in_beta_s2s4];

    for (int i = 0; i < hits_in_beta_s2s4; i++)
    {
        float temp_music41_de = de[0] > 0.0;
        if ((temp_music41_de > 0.0) && (id_mhtdc_beta_s2s4[i] > 0.0) && (id_mhtdc_beta_s2s4[i] < 1.0))
        {
            power = 1.;
            sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->mhtdc_vel_a_music41[j];
                //power *= id_mhtdc_beta_s2s4[i];
                power *= 1.0/(id_mhtdc_beta_s2s4[i]*id_mhtdc_beta_s2s4[i]);
            }
            id_mhtdc_v_cor_music41[i] = sum;

            
            if (id_mhtdc_v_cor_music41[i] > 0.0)
            {
                id_mhtdc_z_music41[i] = frs->primary_z * sqrt(de[0] / id_mhtdc_v_cor_music41[i]) + id->mhtdc_offset_z_music41;

                //if (music41_mhtdc_z_gain_shifts != nullptr){
                //id_mhtdc_z_music41[i] = id_mhtdc_z_music41[i]  + music41_mhtdc_z_gain_shifts->GetGain(wr_t);
                //}
            } // else???
        }

        float temp_music42_de = de[1] > 0.0;
        if((temp_music42_de > 0.0)  && (id_mhtdc_beta_s2s4[i] > 0.0) && (id_mhtdc_beta_s2s4[i] < 1.0))
        {
            power = 1.;
            sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->mhtdc_vel_a_music42[j];
                //power *= id_mhtdc_beta_s2s4[i];
                power *= 1.0/(id_mhtdc_beta_s2s4[i]*id_mhtdc_beta_s2s4[i]);
            }
            id_mhtdc_v_cor_music42[i] = sum;
            
            if (id_mhtdc_v_cor_music42[i] > 0.0)
            {
                id_mhtdc_z_music42[i] = frs->primary_z * sqrt(de[1] / id_mhtdc_v_cor_music42[i]) + id->mhtdc_offset_z_music42;

                //if (music42_mhtdc_z_gain_shifts != nullptr){
                //id_mhtdc_z_music42[i] = id_mhtdc_z_music42[i] + music42_mhtdc_z_gain_shifts->GetGain(wr_t);
                //}
            }
        }

    }

    mhtdc_gamma1square = new Float_t[hits_in_aoq];
    id_mhtdc_gamma_ta_s2 = new Float_t[hits_in_aoq];
    id_mhtdc_dEdegoQ = new Float_t[hits_in_aoq];
    id_mhtdc_dEdeg = new Float_t[hits_in_aoq];
    for (int i = 0; i < hits_in_beta_s2s4; i++)
    {        
        for (int j = 0; j<hits_in_s2x; j++){
            if (id_mhtdc_aoq_s2s4[i*hits_in_s2x + j] > 0) // ELSE????
            {
                mhtdc_gamma1square[i*hits_in_s2x + j] = 1.0 + TMath::Power(((1.0 / aoq_factor) * (id_brho[0] / id_mhtdc_aoq_s2s4[i*hits_in_s2x + j])), 2);
                id_mhtdc_gamma_ta_s2[i*hits_in_s2x + j] = TMath::Sqrt(mhtdc_gamma1square[i*hits_in_s2x + j]);
                id_mhtdc_dEdegoQ[i*hits_in_s2x + j] = (id_mhtdc_gamma_ta_s2[i*hits_in_s2x + j] - id_mhtdc_gamma_s2s4[i]) * id_mhtdc_aoq_s2s4[i*hits_in_s2x + j];
                id_mhtdc_dEdeg[i*hits_in_s2x + j] = id_mhtdc_dEdegoQ[i*hits_in_s2x + j] * id_mhtdc_z_music41[i];
            }else{
                mhtdc_gamma1square[i*hits_in_s2x + j] = -999;
                id_mhtdc_gamma_ta_s2[i*hits_in_s2x + j] = -999;
                id_mhtdc_dEdegoQ[i*hits_in_s2x + j] = -999;
                id_mhtdc_dEdeg[i*hits_in_s2x + j] = -999;
            }
        }
    }
    
    if (id->x_s2_select == 1)
    {   
        if (b_tpc_xy[2] && b_tpc_xy[3])
        {   
            id_x2 = tpcCalItem.Get_tpc_x_s2_foc_23_24();
            id_y2 = tpcCalItem.Get_tpc_y_s2_foc_23_24();
            id_a2 = tpcCalItem.Get_tpc_angle_x_s2_foc_23_24();
            id_b2 = tpcCalItem.Get_tpc_angle_y_s2_foc_23_24();
        }
        else if (b_tpc_xy[1] && b_tpc_xy[3])
        {
            id_x2 = tpcCalItem.Get_tpc_x_s2_foc_22_24();
            id_y2 = tpcCalItem.Get_tpc_y_s2_foc_22_24();
            id_a2 = tpcCalItem.Get_tpc_angle_x_s2_foc_22_24();
            id_b2 = tpcCalItem.Get_tpc_angle_y_s2_foc_22_24();
        }
        else if (b_tpc_xy[0] && b_tpc_xy[1])
        {   
            id_x2 = tpcCalItem.Get_tpc_x_s2_foc_21_22();
            id_y2 = tpcCalItem.Get_tpc_y_s2_foc_21_22();
            id_a2 = tpcCalItem.Get_tpc_angle_x_s2_foc_21_22();
            id_b2 = tpcCalItem.Get_tpc_angle_y_s2_foc_21_22();
        }
        

    }
    else if (id->x_s2_select == 2)
    {   
        // SC21
        if (sci_b_x[0]) // we only use 2 and 3??
        {
            id_x2 = sci_x[0];
            id_y2 = 0.0;
            id_a2 = 0.0;
            id_b2 = 0.0;
        }
    }
    else if (id->x_s2_select == 3)
    {
        if (sci_b_x[1])
        {
            id_x2 = sci_x[1];
            id_y2 = 0.0;
            id_a2 = 0.0;
            id_b2 = 0.0;
        }
    }

    if (b_tpc_xy[4] && b_tpc_xy[5])
    {   
        id_x4 = tpcCalItem.Get_tpc_x_s4();
        id_y4 = tpcCalItem.Get_tpc_y_s4();
        id_a4 = tpcCalItem.Get_tpc_angle_x_s4();
        id_b4 = tpcCalItem.Get_tpc_angle_y_s4();
    }

    if (sci_b_x[5])
    {
        id_x8 = sci_x[5];
        id_y8 = 0.0;
        id_a8 = 0.0;
        id_b8 = 0.0;
    }

    id_b_x2 = Check_WinCond(id_x2, cID_x2);
    id_b_x4 = Check_WinCond(id_x4, cID_x4);
    

    /*----------------------------------------------------------*/
    /* Determination of beta                                    */
    /*----------------------------------------------------------*/
    id_beta = 0;
    if (id->tof_s4_select == 1)
    {
        if (sci_b_tofll_21_41 && sci_b_tofrr_21_41)
        {
            id_beta = id->id_path2 / sci_tof_21_41_calib;
        }
    }
    else if (id->tof_s4_select == 2)
    {
        if (sci_b_tofll_21_42 && sci_b_tofrr_21_42)
        {
            id_beta = id->id_path3 / sci_tof_21_42_calib;
        }
    }
    else if (id->tof_s4_select == 3)
    {
        if (sci_b_tofll_22_41 && sci_b_tofrr_22_41)
        {
            id_beta = id->id_path5 / sci_tof_22_41_calib;
        }
    }

    /*------------------------------------------------------*/
    /* Determination of Brho                                */
    /*------------------------------------------------------*/

    if (id_b_x2)
    {
        id_rho[0] = frs->rho0[0] * (1. - id_x2 / 1000. / frs->dispersion[0]);
        id_brho[0] = (fabs(frs->bfield[0]) + fabs(frs->bfield[1])) / 2. * id_rho[0];

        if (id_b_x4)
        {
            id_rho[1] = frs->rho0[1] * (1. - (id_x4 - frs->magnification[1] * id_x2) / 1000. / frs->dispersion[1]);
            id_brho[1] = (fabs(frs->bfield[2]) + fabs(frs->bfield[3])) / 2. * id_rho[1];

        }
    }

    /*--------------------------------------------------------------*/
    /* Determination of A/Q                                         */
    /*--------------------------------------------------------------*/
    // for S2-S4
    // only use 21_41?
    if (sci_b_tofll_21_41 && sci_b_tofrr_21_41 && id_b_x2 && id_b_x4)
    {
        if ((id_beta > 0.0) && (id_beta < 1.0))
        {
            id_gamma = 1. / sqrt(1. - id_beta * id_beta);
            id_AoQ = id_brho[1] / id_beta / id_gamma / aoq_factor;
            id_AoQ_corr = id_AoQ - id->a2AoQCorr * id_a2;
            id_b_AoQ = true;

        }
    }

    /*------------------------------------------------*/
    /* Determination of Z                           */
    /*------------------------------------------------*/
    // Calibration with MUSIC is done with 1/b2 - last update sept2024

    // S4 (MUSIC 1)
    if ((de[0] > 0.0) && (id_beta > 0.0) && (id_beta < 1.0))
    {
        power = 1.;
        sum = 0.;
        for (int i = 0; i < 4; i++)
        {
            sum += power * id->vel_a[i];
            //power *= 1.0/(id_beta*id_beta);
            power *= id_beta;
        }
        id_v_cor = sum;
        if (id_v_cor > 0.0)
        {
            id_z = frs->primary_z * sqrt(de[0] / id_v_cor) + id->offset_z;

        }
        if ((id_z > 0.0) && (id_z < 100.0))
        {
            id_b_z = kTRUE;
        }
    }

    // S4 (MUSIC 2)
    if ((de[1] > 0.0) && (id_beta > 0.0) && (id_beta < 1.0))
    {
        power = 1.;
        sum = 0.;
        for (int i = 0; i < 4; i++)
        {
            sum += power * id->vel_a2[i];
            //power *= 1.0/(id_beta*id_beta);
            power *= id_beta;
        }
        id_v_cor2 = sum;

        if (id_v_cor2 > 0.0)
        {
            id_z2 = frs->primary_z * sqrt(de[1] / id_v_cor2) + id->offset_z2;
        }
        if ((id_z2 > 0.0) && (id_z2 < 100.0))
        {   
            // CEJ: this seems out of order to me, gain matching first?
            id_b_z2 = kTRUE;
        }
    }

    // CEJ: can be tidied/reconfigured some later
    if (frs_config->AoQDriftLoaded())
    {
        id_AoQ_driftcorr = 0;
        double drift_aoq = 0.0;
        double drift_aoq_error = 0.0;
        int nentry_aoq = 0;
        int aoq_frs_wr_time_a = 0; 
        int aoq_frs_wr_time_b = 0;
        double aoq_reference_value = 2.39;   //!!!! read from exp configuration - expected value
        int bin = 20;  
        
        //std::cout << "::::  AoQ :::: " << "\n";
        //std::cout << "::::  AoQ " << id_AoQ <<"\n";


        std::map<int,std::pair<double,double>> aoq_drift = frs_config->AoQDriftCoefficients();
        for (const auto& entry : aoq_drift)
        {            
            // std::cout << " AoQ Key (travmus_wr_time): " << entry.first 
            //   << ", AoQ Value (coeffs): (" << entry.second.first 
            //   << ", " << entry.second.second << ")\n";
            
            int aoq_frs_wr_time = entry.first;
            std::pair<double,double> aoq_coeffs = entry.second;
            drift_aoq = aoq_coeffs.first;
            drift_aoq_error = aoq_coeffs.second;

            double aoq_shift = drift_aoq - aoq_reference_value;
            //std::cout << "::::  AoQ value  " << id_AoQ <<"\n";
            
            if ((FRS_time_mins >= (aoq_frs_wr_time - bin/2)) && (FRS_time_mins < (aoq_frs_wr_time + bin/2)))
            {
                id_AoQ_driftcorr = id_AoQ - aoq_shift;
                // std::cout  << " reference :" << aoq_reference_value
                //     << " drift (1 coeff) :" << drift_aoq 
                //     << " aoq shift :" << aoq_shift 
                //     << " aoq original : " << id_AoQ
                //     << " aoq corrected : " << id_AoQ_driftcorr << "\n";
            
            }
            
            nentry_aoq ++ ;
        }

    }

    if (frs_config->Z1DriftLoaded())
    {
        id_z_driftcorr = 0;
        double drift_z1 = 0.0;
        double drift_z1_error = 0.0;
        int nentry_z1 = 0;
        int z1_frs_wr_time_a = 0; 
        int z1_frs_wr_time_b = 0;
        double z1_reference_value = 41;     //!!!! read from exp configuration - expected value
        int bin = 20;                       //!!!! read from drift file

        //std::cout << "::::  Z1 :::: " << "\n";
        //std::cout << "::::  Z1 " << id_z <<"\n";

        std::map<int,std::pair<double,double>> z1_drift = frs_config->Z1DriftCoefficients();
        for (const auto& entry : z1_drift)
        {            
            // std::cout << "Z1 Key (travmus_wr_time): " << entry.first 
            // << ", Z1 Value (coeffs): (" << entry.second.first 
            // << ", " << entry.second.second << ")\n";
            
            int z1_frs_wr_time = entry.first;
            std::pair<double,double> z1_coeffs = entry.second;
            drift_z1 = z1_coeffs.first;
            drift_z1_error = z1_coeffs.second;

            double z1_shift = drift_z1 - z1_reference_value;
            //std::cout << "::::  Z1 " << id_z <<"\n";

            if ((FRS_time_mins >= (z1_frs_wr_time - bin/2)) && (FRS_time_mins < (z1_frs_wr_time + bin/2)))
            {
                //std::cout << "::::  in loop  Z1 " << id_z <<"\n";
                id_z_driftcorr = id_z - z1_shift;
                // std::cout  << " reference :" << z1_reference_value
                //     << " drift (1 coeff) :" << drift_z1 
                //     << " shift :" << z1_shift 
                //     << " Z1 original : " << id_z
                //     << " Z1 corr : " << id_z_driftcorr << "\n";
            }
            
            nentry_z1 ++ ;
        }

    }
    
    float gamma1square = 1.0 + TMath::Power(((1 / aoq_factor) * (id_brho[0] / id_AoQ)), 2);
    id_gamma_ta_s2 = TMath::Sqrt(gamma1square);
    id_dEdegoQ = (id_gamma_ta_s2 - id_gamma) * id_AoQ;
    id_dEdeg = id_dEdegoQ * id_z;

    auto & hitEntry = hitArray->emplace_back();
    hitEntry.SetAll(wr_t,
                    tpat,
                    id_x2,
                    id_y2,
                    id_x4,
                    id_y4,
                    id_a2,
                    id_b2,
                    id_a4,
                    id_b4,
                    id_AoQ,
                    id_AoQ_driftcorr,
                    id_AoQ_corr,
                    id_z,
                    id_z_driftcorr,
                    id_z2,
                    id_beta,
                    id_dEdeg,
                    id_dEdegoQ,
                    id_rho,
                    id_brho,
                    de,
                    de_cor,
                    de_21l,
                    de_21r,
                    de_22l,
                    de_22r,
                    de_31l,
                    de_31r,
                    de_41l,
                    de_41r,
                    de_42l,
                    de_42r,
                    de_43l,
                    de_43r,
                    de_81l,
                    de_81r,
                    sci_e_21,
                    sci_e_22,
                    sci_e_31,
                    sci_e_41,
                    sci_e_42,
                    sci_e_43,
                    sci_e_81,
                    sci_x_21,
                    sci_x_22,
                    sci_x_41,
                    sci_x_42,
                    sci_x_43,
                    sci_x_81,
                    sci_tof_21_41, // 2
                    sci_tof_21_41_calib,
                    sci_tof_21_42, // 3
                    sci_tof_21_42_calib,
                    sci_tof_21_81, // 4
                    sci_tof_21_81_calib,
                    sci_tof_22_41, // 5
                    sci_tof_22_41_calib,
                    sci_tof_22_81, // 6
                    sci_tof_22_81_calib,
                    time_in_ms,
                    ibin_for_s,
                    ibin_for_100ms,
                    ibin_for_spill,
                    increase_sc_temp_main,
                    increase_sc_temp_user,
                    increase_sc_temp2,
                    increase_sc_temp3,
                    extraction_time_ms,
                    ibin_clean_for_s,
                    ibin_clean_for_100ms,
                    ibin_clean_for_spill);

    for (int i = 0; i < hits_in_beta_s2s4; i++)
    {
        for (int j = 0; j<hits_in_s2x; j ++)
        {
        if (
        temp_s2x_mhtdc[j] > - 200 &&  temp_s2x_mhtdc[j] < 200 &&
        id_mhtdc_beta_s2s4[i] > 0 && id_mhtdc_beta_s2s4[i] < 1 &&
        id_mhtdc_aoq_s2s4[i*hits_in_s2x + j] > 1.0 && id_mhtdc_aoq_s2s4[i] < 3.5 )
        {
        auto & multihitEntry = multihitArray->emplace_back();
        multihitEntry.SetAll(
                            temp_s2x_mhtdc[j],
                            temp_a2,
                            temp_s4x,
                            temp_a4,
                            id_mhtdc_tof_s2s4[i],
                            id_mhtdc_beta_s2s4[i], 
                            id_mhtdc_aoq_s2s4[i*hits_in_s2x + j], 
                            id_mhtdc_aoq_corr_s2s4[i*hits_in_s2x + j], 
                            id_mhtdc_z_music41[i],
                            id_mhtdc_z_music42[i],
                            id_mhtdc_dEdeg[i*hits_in_s2x + j],
                            id_mhtdc_dEdegoQ[i*hits_in_s2x + j]
                            );
        }
        }
    }
   
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}


void FrsCal2Hit::Setup_Conditions(std::string path_to_config_files)
{
    std::string line;
    int line_number = 0;

    const char* format = "%f %f %f %f %f %f %f %f %f %f %f %f %f %f";

    std::ifstream cond_a(path_to_config_files +  TString("lim_csum.txt"));

    while(/*cond_a.good()*/getline(cond_a,line,'\n'))
    {
        if(line[0] == '#') continue;


            sscanf(line.c_str(),format,&lim_csum[line_number][0][0],&lim_csum[line_number][0][1]
                        ,&lim_csum[line_number][1][0],&lim_csum[line_number][1][1]
                        ,&lim_csum[line_number][2][0],&lim_csum[line_number][2][1]
                        ,&lim_csum[line_number][3][0],&lim_csum[line_number][3][1]
                        ,&lim_csum[line_number][4][0],&lim_csum[line_number][4][1]
                        ,&lim_csum[line_number][5][0],&lim_csum[line_number][5][1]
                        ,&lim_csum[line_number][6][0],&lim_csum[line_number][6][1]);

        line_number++;

    }

    line_number = 0;

    format = "%f %f";

    std::ifstream cond_b(path_to_config_files +  TString("lim_xsum.txt"));

    while(/*cond_b.good()*/getline(cond_b,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&lim_xsum[line_number][0],&lim_xsum[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f";

    std::ifstream cond_c(path_to_config_files +  TString("lim_ysum.txt"));

    while(/*cond_c.good()*/getline(cond_c,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&lim_ysum[line_number][0],&lim_ysum[line_number][1]);

        line_number++;
    }

    /*** MUSIC Conditions *** */

    line_number = 0;

    format = "%f %f %f %f";

    std::ifstream cond_d(path_to_config_files +  TString("MUSIC1.txt"));

    while(/*cond_d.good()*/getline(cond_d,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic1_E[line_number][0],&cMusic1_E[line_number][1],&cMusic1_T[line_number][0],&cMusic1_T[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f %f %f";

    std::ifstream cond_e(path_to_config_files +  TString("MUSIC2.txt"));

    while(/*cond_e.good()*/getline(cond_e,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic2_E[line_number][0],&cMusic2_E[line_number][1],&cMusic2_T[line_number][0],&cMusic2_T[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f %f %f";

    std::ifstream cond_f(path_to_config_files +  TString("MUSIC3.txt"));

    while(/*cond_f.good()*/getline(cond_f,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic3_E[line_number][0],&cMusic3_E[line_number][1],&cMusic3_T[line_number][0],&cMusic3_T[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f";

    std::ifstream cond_g(path_to_config_files +  TString("MUSIC_dEc3.txt"));

    while(/*cond_g.good()*/getline(cond_g,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic3_dec[0],&cMusic3_dec[1]);
    }

    /***SCINTILATOR Condtions***/

    line_number = 0;

    format = "%f %f";

    std::ifstream cond_h(path_to_config_files +  TString("SCI_Cons.txt"));

    while(/*cond_h.good()*/getline(cond_h,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cSCI_L[0],&cSCI_L[1]);

        getline(cond_h,line,'\n');
            sscanf(line.c_str(),format,&cSCI_R[0],&cSCI_R[1]);

        getline(cond_h,line,'\n');
            sscanf(line.c_str(),format,&cSCI_E[0],&cSCI_E[1]);

        getline(cond_h,line,'\n');
            sscanf(line.c_str(),format,&cSCI_Tx[0],&cSCI_Tx[1]);

        getline(cond_h,line,'\n');
            sscanf(line.c_str(),format,&cSCI_X[0],&cSCI_X[1]);

    }

    format = "%f %f";

    std::ifstream cond_i(path_to_config_files +  TString("SCI_LLRR.txt"));
    c4LOG_IF(fatal, !cond_i.is_open(), "Failed to open SCI_LLRR config file");
    while(cond_i.good())
    {
        getline(cond_i,line,'\n');
        if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&cSCI_LL2[0],&cSCI_LL2[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR2[0],&cSCI_RR2[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_LL3[0],&cSCI_LL3[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR3[0],&cSCI_RR3[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_LL4[0],&cSCI_LL4[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR4[0],&cSCI_RR4[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_LL5[0],&cSCI_LL5[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR5[0],&cSCI_RR5[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_LL6[0],&cSCI_LL6[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR6[0],&cSCI_RR6[1]);

        break;

    }

    /***ID Condtions***/

    format = "%f %f";

    std::ifstream cond_k(path_to_config_files +  TString("ID_x2.txt"));


    while(/*cond_k.good()*/getline(cond_k,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cID_x2[0],&cID_x2[1]);
    }

    std::ifstream cond_l(path_to_config_files +  TString("ID_x4.txt"));

    while(/*cond_l.good()*/getline(cond_l,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cID_x4[0],&cID_x4[1]);
    }

    std::ifstream cond_m(path_to_config_files +  TString("ID_Z_Z.txt"));

    while(/*cond_m.good()*/getline(cond_m,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cID_Z_Z[0],&cID_Z_Z[1]);
    }

    conditions_files_read = true;

}

// not used in FRS Go4?
void FrsCal2Hit::FRS_GainMatching()
{
    std::ifstream file;
    std::string line;
    Float_t frs_wr_a;
    Float_t frs_wr_b;
    Float_t frs_wr_i;
    Float_t frs_wr_j;
    Float_t z1_shift_value;
    Float_t z2_shift_value;
    Float_t aoq_shift_value;
    Float_t aoq_shift_tpc_value;
    Float_t aoq_shift_sci21_value;
    Float_t aoq_shift_sci22_value;

    int f = 0;
    int d = 0;
    
    file.open("../../config/frs/NovTest/Z1_Z2_Shift.txt");
    while (file.good())
    {
        getline(file, line, '\n');
        if (line[0] == '#') continue;
        sscanf(line.c_str(), "%f %f %f %f", &frs_wr_a, &frs_wr_b, &z1_shift_value, &z2_shift_value);
        FRS_WR_a[f] = frs_wr_a;
        FRS_WR_b[f] = frs_wr_b;
        Z1_shift_value[f] = z1_shift_value;
        Z2_shift_value[f] = z2_shift_value;
        Z_Shift_array = f;
        f++;
    }
    file.close();

    file.open("../../config/frs/NovTest/AoQ_Shift.txt");
    while (file.good())
    {
        getline(file, line, '\n');
        if (line[0] == '#') continue;
        sscanf(line.c_str(), "%f %f %f %f %f", &frs_wr_i, &frs_wr_j, &aoq_shift_tpc_value, &aoq_shift_sci21_value, &aoq_shift_sci22_value);
        FRS_WR_i[d] = frs_wr_i;
        FRS_WR_j[d] = frs_wr_j;
        AoQ_shift_TPC_value[d] = aoq_shift_tpc_value;
        AoQ_shift_Sci21_value[d] = aoq_shift_sci21_value;
        AoQ_shift_Sci22_value[d] = aoq_shift_sci22_value;
        AoQ_Shift_array = d;
        d++;
    }
    file.close();

}

Bool_t FrsCal2Hit::Check_WinCond(Float_t P, Float_t* V)
{
    if (P >= V[0] && P <= V[1]) return true;
    else return false;
}

Bool_t FrsCal2Hit::Check_WinCond_Multi(Float_t P, Float_t V[8][2], int cond_num)
{
    if (P >= V[cond_num][0] && P <= V[cond_num][1]) return true;
    else return false;
}

Float_t FrsCal2Hit::rand3()
{
    return random3.Uniform(-0.5,0.5);
}


void FrsCal2Hit::ZeroArrays()
{
    //fHitArray->Clear();
    //fEventItems->Clear();
}

void FrsCal2Hit::ZeroVariables()
{
    id_b_AoQ = false;
    id_b_x2 = false;
    id_b_x4 = false;
    id_b_z = false;
    id_x2 = -999;
    id_y2 = -999;
    id_a2 = -999;
    id_b2 = -999;
    id_x4 = -999;
    id_y4 = -999;
    id_a4 = -999;
    id_b4 = -999;
    id_AoQ = 0;
    id_AoQ_corr = 0;
    id_z = 0;
    id_z2 = 0;
}

void FrsCal2Hit::ClearVectors()
{

}



void FrsCal2Hit::FinishEvent()
{
    ZeroVariables();
    if (mhtdc_sc21lr_dt!=nullptr) {
        delete[] mhtdc_sc21lr_dt;
        mhtdc_sc21lr_dt = nullptr;

    }
    
    if (mhtdc_sc22lr_dt!=nullptr) {
        delete[] mhtdc_sc22lr_dt;
        mhtdc_sc22lr_dt = nullptr;

    }
    if (mhtdc_sc41lr_dt!=nullptr) {
        delete[] mhtdc_sc41lr_dt;
        mhtdc_sc41lr_dt = nullptr;

    }
    if (mhtdc_sc31lr_dt!=nullptr) {
        delete[] mhtdc_sc31lr_dt;
        mhtdc_sc31lr_dt = nullptr;

    }
    if (mhtdc_sc42lr_dt!=nullptr) {
        delete[] mhtdc_sc42lr_dt;
        mhtdc_sc42lr_dt = nullptr;

    }
    if (mhtdc_sc43lr_dt!=nullptr) {
        delete[] mhtdc_sc43lr_dt;
        mhtdc_sc43lr_dt = nullptr;

    }
    if (mhtdc_sc81lr_dt!=nullptr) {
        delete[] mhtdc_sc81lr_dt;
        mhtdc_sc81lr_dt = nullptr;

    }
    
    if (mhtdc_sc21lr_x!=nullptr) {
        delete[] mhtdc_sc21lr_x;
        mhtdc_sc21lr_x = nullptr;

    }
    if (mhtdc_sc22lr_x!=nullptr) {
        delete[] mhtdc_sc22lr_x;
        mhtdc_sc22lr_x = nullptr;

    }
    if (mhtdc_sc41lr_x!=nullptr) {
        delete[] mhtdc_sc41lr_x;
        mhtdc_sc41lr_x = nullptr;

    }
    if (mhtdc_sc31lr_x!=nullptr) {
        delete[] mhtdc_sc31lr_x;
        mhtdc_sc31lr_x = nullptr;

    }
    if (mhtdc_sc81lr_x!=nullptr) {
        delete[] mhtdc_sc81lr_x;
        mhtdc_sc81lr_x = nullptr;

    }
    if (mhtdc_sc42lr_x!=nullptr) {
        delete[] mhtdc_sc42lr_x;
        mhtdc_sc42lr_x = nullptr;

    }
    if (mhtdc_sc43lr_x!=nullptr) {
        delete[] mhtdc_sc43lr_x;
        mhtdc_sc43lr_x = nullptr;

    }

    if (mhtdc_tof4121!=nullptr) {
        delete[] mhtdc_tof4121;
        mhtdc_tof4121 = nullptr;

    }
    if (mhtdc_tof4122!=nullptr) {
        delete[] mhtdc_tof4122;
        mhtdc_tof4122 = nullptr;

    }
    if (mhtdc_tof4221!=nullptr) {
        delete[] mhtdc_tof4221;
        mhtdc_tof4221 = nullptr;

    }
    if (mhtdc_tof4321!=nullptr) {
        delete[] mhtdc_tof4321;
        mhtdc_tof4321 = nullptr;

    }
    if (mhtdc_tof8121!=nullptr) {
        delete[] mhtdc_tof8121;
        mhtdc_tof8121 = nullptr;

    }
    if (mhtdc_tof3121!=nullptr) {
        delete[] mhtdc_tof3121;
        mhtdc_tof3121 = nullptr;

    }

    if (id_mhtdc_beta_s2s4!=nullptr) {
        delete[] id_mhtdc_beta_s2s4;
        id_mhtdc_beta_s2s4 = nullptr;

    }
    if (id_mhtdc_gamma_s2s4!=nullptr) {
        delete[] id_mhtdc_gamma_s2s4;
        id_mhtdc_gamma_s2s4 = nullptr;

    }
    if (id_mhtdc_delta_s2s4!=nullptr) {
        delete[] id_mhtdc_delta_s2s4; // not sure this needs to be a vector
        id_mhtdc_delta_s2s4 = nullptr;
    }
    
    if (id_mhtdc_aoq_s2s4!=nullptr) {
        delete[] id_mhtdc_aoq_s2s4;
        id_mhtdc_aoq_s2s4 = nullptr;

    }
    if (id_mhtdc_aoq_corr_s2s4!=nullptr) {
        delete[] id_mhtdc_aoq_corr_s2s4;
        id_mhtdc_aoq_corr_s2s4 = nullptr;

    }
    if (id_mhtdc_z_music41!=nullptr) {
        delete[] id_mhtdc_z_music41;
        id_mhtdc_z_music41 = nullptr;

    }
    if (id_mhtdc_zcor_music41!=nullptr) {
        delete[] id_mhtdc_zcor_music41;
        id_mhtdc_zcor_music41 = nullptr;

    }
    if (id_mhtdc_v_cor_music41!=nullptr) {
        delete[] id_mhtdc_v_cor_music41;
        id_mhtdc_v_cor_music41 = nullptr;

    }
    if (id_mhtdc_z_music42!=nullptr) {
        delete[] id_mhtdc_z_music42;
        id_mhtdc_z_music42 = nullptr;

    }
    if (id_mhtdc_zcor_music42!=nullptr) {
        delete[] id_mhtdc_zcor_music42;
        id_mhtdc_zcor_music42 = nullptr;

    }
    if (id_mhtdc_v_cor_music42!=nullptr) {
        delete[] id_mhtdc_v_cor_music42;
        id_mhtdc_v_cor_music42 = nullptr;

    }
    if (id_mhtdc_dEdegoQ!=nullptr) {
        delete[] id_mhtdc_dEdegoQ;
        id_mhtdc_dEdegoQ = nullptr;

    }
    if (id_mhtdc_gamma_ta_s2!=nullptr) {
        delete[] id_mhtdc_gamma_ta_s2;
        id_mhtdc_gamma_ta_s2 = nullptr;

    }
    if (mhtdc_gamma1square!=nullptr) {
        delete[] mhtdc_gamma1square;
        mhtdc_gamma1square = nullptr;

    }
    if (id_mhtdc_dEdeg!=nullptr) {
        delete[] id_mhtdc_dEdeg;
        id_mhtdc_dEdeg = nullptr;
    }
    if (temp_s2x_mhtdc!=nullptr) {
        delete[] temp_s2x_mhtdc;
        temp_s2x_mhtdc = nullptr;
    }

    if (id_mhtdc_tof_s2s4!=nullptr) {
        delete[] id_mhtdc_tof_s2s4;
        id_mhtdc_tof_s2s4 = nullptr;

    }

}

void FrsCal2Hit::FinishTask()
{
    c4LOG(info, Form("Wrote %i events. ", fNEvents));
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents);
}

ClassImp(FrsCal2Hit)
