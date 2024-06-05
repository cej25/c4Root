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
//#define TRAVMUS_TAC_OR_MHTDC

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
    ,   travMusicArray(nullptr)
    ,   hitArray(new std::vector<FrsHitItem>)
    ,   multihitArray(new std::vector<FrsMultiHitItem>)
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
    ,   travMusicArray(nullptr)
    ,   hitArray(new std::vector<FrsHitItem>)
    ,   multihitArray(new std::vector<FrsMultiHitItem>)
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
    travMusicArray = mgr->InitObjectAs<decltype(travMusicArray)>("FrsTravMusCalData");
    // travMusic optional

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
    //travmusic_e = new uint16_t[8];
    music_t1 = new uint32_t[8];
    music_t2 = new uint32_t[8];
    //travmusic_t = new uint16_t[8];

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

    if (wr_t == 0) return; // ACTUAL no whiterabbit

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

    if (travMusicArray)
    {
        auto const & travMusicItem = travMusicArray->at(0);
        wr_travmus = travMusicItem.Get_wr_t();
        for (int i = 0; i < 8; i++) travmusic_t[i] = travMusicItem.Get_music_time(i);
        for (int i = 0; i < 8; i++) travmusic_e[i] = travMusicItem.Get_music_energy(i);
    }

    music1_anodes_cnt = 0;
    music2_anodes_cnt = 0;
    travmusic_anodes_cnt = 0;

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

        // TRAVEL MUSIC
        if (travMusicArray)
        {
            if (travmusic_e[i] > 4)
            {
                if (music->exclude_de3_adc_channel[i] == kTRUE) travmusic_b_e[i] = false;
                else travmusic_b_e[i] = Check_WinCond_Multi(travmusic_e[i], cMusicTRAV_E, i);

                if (travmusic_b_e[i])
                {
                    travmusic_anodes_cnt++;
                }
            }
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

    #ifndef MUSIC_ANA_NEW
    if (travmusic_anodes_cnt == 8)
    {
        Float_t r1 = ((travmusic_e[0]) * music->e3_gain[0] + music->e3_off[0]) * ((travmusic_e[1]) * music->e3_gain[1] + music->e3_off[1]);
        Float_t r2 = ((travmusic_e[2]) * music->e3_gain[2] + music->e3_off[2]) * ((travmusic_e[3]) * music->e3_gain[3] + music->e3_off[3]);
        Float_t r3 = ((travmusic_e[4]) * music->e3_gain[4] + music->e3_off[4]) * ((travmusic_e[5]) * music->e3_gain[5] + music->e3_off[5]);
        Float_t r4 = ((travmusic_e[6]) * music->e3_gain[6] + music->e3_off[6]) * ((travmusic_e[7]) * music->e3_gain[7] + music->e3_off[7]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            b_de_travmus = kTRUE;
            de_travmus = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            de_cor_travmus = de_travmus;
        }
    }
    #endif

    #ifdef MUSIC_ANA_NEW
    if (travmusic_anodes_cnt >= 4)
    {
        Float_t temp_de_travmus = 1.0;
        Int_t temp_count_travmus = 0;
        for (int i = 0; i < 8; i++)
        {
            if (travmusic_b_e[i])
            {
                temp_de_travmus *= ((travmusic_e[i]) * music->e3_gain[i] + music->e3_off[i]);
                temp_count_travmus++;
            }
        }
        de_travmus = TMath::Power(temp_de_travmus, 1. / ((float)(temp_count_travmus)));
        de_cor_travmus = de_travmus;
        b_de_travmus = kTRUE;
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
        travmusic_x_mean = tpcCalItem.Get_tpc_music43_x();

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
        
        if (travMusicArray)
        {
            if (b_de_travmus)
            {
                power = 1.;
                Corr = 0.;
                for (int i = 0; i < 4; i++)
                {
                    Corr += music->pos_a3[i] * power;
                    power *= travmusic_x_mean;
                }
                if (Corr != 0)
                {
                    Corr = music->pos_a3[0] / Corr;
                    de_cor_travmus = de_travmus * Corr;
                }
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
        //mhtdc_sc21lr_x[i*hits_in_21r + j] = mhtdc_sc21lr_dt[i*hits_in_21r + j] * sci->mhtdc_factor_21l_21r + sci->mhtdc_offset_21l_21r;

        double p0 = -72.5554;
        double p1 =  54.9136;
        double p2 =  1.14567;
        double p3 = -5.12242;
        double p4 =  3.70734;
        double p5 = -0.72347;

        mhtdc_sc21lr_x[i*hits_in_21r + j] = TMath::Power(mhtdc_sc21lr_dt[i*hits_in_21r + j],5)*p5 +TMath::Power(mhtdc_sc21lr_dt[i*hits_in_21r + j],4)*p4 +TMath::Power(mhtdc_sc21lr_dt[i*hits_in_21r + j],3)*p3 +TMath::Power(mhtdc_sc21lr_dt[i*hits_in_21r + j],2)*p2 +TMath::Power(mhtdc_sc21lr_dt[i*hits_in_21r + j],1)*p1 + p0;

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

    de_array = mainSciItem.Get_de_array();
    dt_array = userSciItem.Get_dt_array();

    //TAC:
    dt_21l_21r = dt_array[0];
    dt_41l_41r = dt_array[1];
    dt_42l_42r = dt_array[2];
    dt_43l_43r = dt_array[3];
    dt_81l_81r = dt_array[4];
    dt_21l_41l = dt_array[5];
    dt_21r_41r = dt_array[6];
    dt_42r_21r = dt_array[7];
    dt_42l_21l = dt_array[8];
    dt_21l_81l = dt_array[9];
    dt_21r_81r = dt_array[10];
    dt_22l_22r = dt_array[11];
    dt_22l_41l = dt_array[12];
    dt_22r_41r = dt_array[13];
    dt_22l_81l = dt_array[14];
    dt_22r_81r = dt_array[15];

    // 2 in go4, 0 now?
    sci_l[0] = de_array[1]; // de_21l;
    sci_r[0] = de_array[2]; // de_21r;
    sci_tx[0] = dt_21l_21r + rand3();

    // 3 in go4, 1 now?
    sci_l[1] = de_array[13]; // de_22l
    sci_r[1] = de_array[6]; // de_22r
    sci_tx[1] = dt_22l_22r + rand3();

    // 5 in go4, 2 now?
    sci_l[2] = de_array[0]; // de_41l
    sci_r[2] = de_array[11]; // de_41r;
    sci_tx[2] = dt_41l_41r + rand3();

    // 6 in go4, 3 now?
    sci_l[3] = de_array[3]; // de_42l
    sci_r[3] = de_array[4]; // de_42r
    sci_tx[3] = dt_42l_42r + rand3();

    // 7 in go4, 4 now?
    sci_l[4] = de_array[9]; // de_43l
    sci_r[4] = de_array[10]; // de_43r
    sci_tx[4] = dt_43l_43r + rand3();

    // 10 in go4, 5 now?
    sci_l[5] = de_array[5]; // de_81l
    sci_r[5] = de_array[12]; // de_81r
    sci_tx[5] = dt_81l_81r + rand3();

    for (int i = 0; i < 6; i++)
    {
        int j;
        switch(i)
        {
            case 0:
                j = 2;
                break;
            case 1:
                j = 3;
                break;
            case 2:
                j = 5;
                break;
            case 3:
                j = 6;
                break;
            case 4:
                j = 7;
                break;
            case 5:
                j = 10;
                break;
            default:
                j = 2;
        }

        sci_b_l[i] = Check_WinCond(sci_l[i], cSCI_L);
        sci_b_r[i] = Check_WinCond(sci_r[i], cSCI_R);

        if (sci_b_l[i] && sci_b_r[i])
        {
            //sci_e[i] = (sci_r[i] - sci->re_a[0][j]); // CEJ: old calculation (?? no idea what this was even doing)
            sci_e[i] = sqrt( (sci_l[i] - sci->le_a[0][j]) * sci->le_a[1][j]
	   			  * (sci_r[i] - sci->re_a[0][j]) * sci->re_a[1][j]);
            sci_b_e[i] = Check_WinCond(sci_e[i], cSCI_E);
        }

        /* Position in X direction: */
        sci_b_tx[i] = Check_WinCond(sci_tx[i], cSCI_Tx);
        if (sci_b_tx[i])
        {
            Float_t R = sci_tx[i];
            power = 1.;
            sum = 0.;
            for (int k = 0; k < 7; k++)
            {
                //sum += sci->x_a[k][i] * power;
                sum += sci->x_a[k][j] * power;
                power *= R;
            }
            sci_x[i] = sum;
            sci_b_x[i] = Check_WinCond(sci_x[i], cSCI_X);
        }
    } // loop for sci values


    // std::cout << ":::::: TESTING SCI SIGNALS :::::" << std::endl;
    // for (int i = 0; i < 6; i++)
    // {   
    //     std::cout << "i: " << i << std::endl;
    //     std::cout << "sci_l: " << sci_l[i] << std::endl;
    //     std::cout << "sci_r: " << sci_r[i] << std::endl;
    //     std::cout << "sci_tx: " << sci_tx[i] << std::endl;
    //     std::cout << "sci_e: " << sci_e[i] << std::endl;
    //     std::cout << "sci_x: " << sci_x[i] << std::endl;
    // }


    /*----------------------------------------------------------*/
    // Calibrated ToF - dt will be in dt_array, from UserCrate
    /*----------------------------------------------------------*/
    Float_t sci_tof[6];
    Float_t sci_tof_calib[6];

    sci_tofll2 = dt_21l_41l * sci->tac_factor[2] - sci->tac_off[2];
    sci_tofrr2 = dt_21r_41r * sci->tac_factor[3] - sci->tac_off[3];
    sci_b_tofll2 = Check_WinCond(sci_tofll2, cSCI_LL2);
    sci_b_tofrr2 = Check_WinCond(sci_tofrr2, cSCI_RR2);
    //c4LOG(info,Form("tof 21l 41l = %f, tof 21r 41r = %f, sci windows = %d %d, cSCILL2 = %f, cSCIRR2 = %f",sci_tofll2, sci_tofrr2,sci_b_tofll2,sci_b_tofrr2,cSCI_LL2[1],cSCI_RR2[1]));
    if (sci_b_tofll2 && sci_b_tofrr2)
    {
        sci_tof2 = (sci->tof_bll2 * sci_tofll2 + sci->tof_a2 + sci->tof_brr2 * sci_tofrr2) / 2.0;
        sci_tof2_calib = -1.0 * sci_tof2 + id->id_tofoff2;
    }
    else
    {
        sci_tof2 = 0;
        sci_tof2_calib = 0;
    }

    sci_tof[2] = sci_tof2;
    sci_tof_calib[2] = sci_tof2_calib;

    sci_tofll3 = dt_42l_21l * sci->tac_factor[5] - sci->tac_off[5];
    sci_tofrr3 = dt_42r_21r * sci->tac_factor[6] - sci->tac_off[6];
    sci_b_tofll3 = Check_WinCond(sci_tofll3, cSCI_LL3);
    sci_b_tofrr3 = Check_WinCond(sci_tofrr3, cSCI_RR3);
    if (sci_b_tofll3 && sci_b_tofrr3)
    {
        sci_tof3 = (sci->tof_bll3 * sci_tofll3 + sci->tof_a3 + sci->tof_brr3 * sci_tofrr3) / 2.0;
        sci_tof3_calib = -1.0 * sci_tof3 + id->id_tofoff3;
    }
    else
    {
        sci_tof3 = 0;
        sci_tof3_calib = 0;
    }

    sci_tof[3] = sci_tof3;
    sci_tof_calib[3] = sci_tof3_calib;

    sci_tofll4 = dt_21l_81l * sci->tac_factor[9] - sci->tac_off[9];
    sci_tofrr4 = dt_21r_81r * sci->tac_factor[10] - sci->tac_off[10];
    sci_b_tofll4 = Check_WinCond(sci_tofll4, cSCI_LL4);
    sci_b_tofrr4 = Check_WinCond(sci_tofrr4, cSCI_RR4);
    if (sci_b_tofll4 && sci_b_tofrr4)
    {
        sci_tof4 = (sci->tof_bll4 * sci_tofll4 + sci->tof_a4 + sci->tof_brr4 * sci_tofrr4) / 2.0;
        sci_tof4_calib = -1.0 * sci_tof4 + id->id_tofoff4;
    }
    else
    {
        sci_tof4 = 0;
        sci_tof4_calib = 0;
    }

    sci_tof[4] = sci_tof4;
    sci_tof_calib[4] = sci_tof4_calib;

    sci_tofll5 = dt_22l_41l * sci->tac_factor[12] - sci->tac_off[12];
    sci_tofrr5 = dt_22r_41r * sci->tac_factor[13] - sci->tac_off[13];
    sci_b_tofll5 = Check_WinCond(sci_tofll5, cSCI_LL5);
    sci_b_tofrr5 = Check_WinCond(sci_tofrr5, cSCI_RR5);
    if (sci_b_tofll5 && sci_b_tofrr5)
    {
        sci_tof5 = (sci->tof_bll5 * sci_tofll5 + sci->tof_a5 + sci->tof_brr5 * sci_tofrr5) / 2.0;
        sci_tof5_calib = -1.0 * sci_tof5 + id->id_tofoff5;
    }
    else
    {
        sci_tof5 = 0;
        sci_tof5_calib = 0;
    }
    
    sci_tof[5] = sci_tof5;
    sci_tof_calib[5] = sci_tof5_calib;

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
                id_mhtdc_beta_s2s4[i] = (id->mhtdc_length_sc2141 / mhtdc_tof4121[i]);
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
                id_mhtdc_beta_s2s4[i] = (id->mhtdc_length_sc2241 / mhtdc_tof4122[i]);
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
    id_mhtdc_v_cor_music41 = new Float_t[hits_in_beta_s2s4];
    id_mhtdc_v_cor_music42 = new Float_t[hits_in_beta_s2s4];
    id_mhtdc_v_cor_travmus = new Float_t[hits_in_beta_s2s4];

    id_mhtdc_z_music41 = new Float_t[hits_in_beta_s2s4];
    id_mhtdc_z_music42 = new Float_t[hits_in_beta_s2s4];
    id_mhtdc_z_travmus = new Float_t[hits_in_beta_s2s4];

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

                if (music41_mhtdc_z_gain_shifts != nullptr){
                id_mhtdc_z_music41[i] = id_mhtdc_z_music41[i]  + music41_mhtdc_z_gain_shifts->GetGain(wr_t);
                }
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

                if (music42_mhtdc_z_gain_shifts != nullptr){
                id_mhtdc_z_music42[i] = id_mhtdc_z_music42[i] + music42_mhtdc_z_gain_shifts->GetGain(wr_t);
                }
            }
        }

        if (travMusicArray)
        {
            float temp_travmus_de = de_travmus > 0.0;
            if ((temp_travmus_de > 0.0) && (id_mhtdc_beta_s2s4[i] > 0.0) && (id_mhtdc_beta_s2s4[i] < 1.0))
            {
                power = 1.;
                sum = 0.;
                for (int j = 0; j < 4; j++)
                {
                    sum += power * id->vel_a3[j]; // same parameters for mhtdc as TAC for now....stupid
                    #ifndef TRAVMUS_TAC_OR_MHTDC
                    power *= id_mhtdc_beta_s2s4[i];
                    #endif
                    #ifdef TRAVMUS_TAC_OR_MHTDC
                    power *= 1.0/(id_mhtdc_beta_s2s4[i]*id_mhtdc_beta_s2s4[i]);
                    #endif
                } 
                id_mhtdc_v_cor_travmus[i] = sum;
                
                if (id_mhtdc_v_cor_travmus[i] > 0.0)
                {   
                    id_mhtdc_z_travmus[i] = frs->primary_z * sqrt(de_travmus / id_mhtdc_v_cor_travmus[i]) + id->offset_z3; // same as TAC....for now
                }
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
        if (sci_b_tofll2 && sci_b_tofrr2)
        {
            id_beta = id->id_path2 / sci_tof2_calib;
        }
    }
    else if (id->tof_s4_select == 2)
    {
        if (sci_b_tofll3 && sci_b_tofrr3)
        {
            id_beta = id->id_path3 / sci_tof3_calib;
        }
    }
    else if (id->tof_s4_select == 3)
    {
        if (sci_b_tofll5 && sci_b_tofrr5)
        {
            id_beta = id->id_path5 / sci_tof5_calib;
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

    if (sci_b_tofll2 && sci_b_tofrr2 && id_b_x2 && id_b_x4)
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
    // S4 (MUSIC 1)
    if ((de[0] > 0.0) && (id_beta > 0.0) && (id_beta < 1.0))
    {
        power = 1.;
        sum = 0.;
        for (int i = 0; i < 4; i++)
        {
            sum += power * id->vel_a[i];
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

    if (travMusicArray)
    {
        if ((de_travmus > 0.0) && (id_beta > 0.0) && (id_beta < 1.0))
        {
            power = 1.;
            sum = 0.;
            for (int i = 0; i < 4; i++)
            {
                sum += power * id->vel_a3[i];
                power *= id_beta;
            }
            id_v_cor_travmus = sum;

            if (id_v_cor_travmus > 0.0)
            {
                id_z_travmus = frs->primary_z * sqrt(de_travmus / id_v_cor_travmus) + id->offset_z3;
            }
            if ((id_z_travmus > 0.0) && (id_z_travmus < 100.0))
            {   
                // CEJ: this seems out of order to me, gain matching first?
                id_b_z_travmus = kTRUE;
            }
        }
    }
    
    

    float gamma1square = 1.0 + TMath::Power(((1 / aoq_factor) * (id_brho[0] / id_AoQ)), 2);
    id_gamma_ta_s2 = TMath::Sqrt(gamma1square);
    id_dEdegoQ = (id_gamma_ta_s2 - id_gamma) * id_AoQ;
    id_dEdeg = id_dEdegoQ * id_z;

    auto & hitEntry = hitArray->emplace_back();
    hitEntry.SetAll(wr_t,
                    tpat,
                    wr_travmus,
                    id_x2,
                    id_y2,
                    id_x4,
                    id_y4,
                    id_a2,
                    id_b2,
                    id_a4,
                    id_b4,
                    id_AoQ,
                    id_AoQ_corr,
                    id_z,
                    id_z2,
                    id_z_travmus, // here
                    id_beta,
                    id_dEdeg,
                    id_dEdegoQ,
                    id_rho,
                    id_brho,
                    de,
                    de_cor,
                    de_travmus, // here
                    de_cor_travmus, // here
                    sci_e,
                    sci_l,
                    sci_r,
                    sci_x,
                    sci_tof,
                    sci_tof_calib,
                    sci_tof2,
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
                            id_mhtdc_z_travmus[i],
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

    // ::::: Inserting TRAVEL MUSIC ::::::: //
    line_number = 0;

    format = "%f %f %f %f";

    std::ifstream cond_travmus(path_to_config_files +  TString("TRAVMUSIC.txt"));

    while(/*cond_f.good()*/getline(cond_travmus,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusicTRAV_E[line_number][0],&cMusicTRAV_E[line_number][1],&cMusicTRAV_T[line_number][0],&cMusicTRAV_T[line_number][1]);

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
