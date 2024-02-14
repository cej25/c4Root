#include "FrsCal2Hit.h"
#include "c4Logger.h"
#include "FrsMainData.h"
#include "FrsMainCalData.h"
#include "FrsHitData.h"

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

#include "../../config/frs_config.h"
#define MUSIC_ANA_NEW

FrsCal2Hit::FrsCal2Hit(TFRSParameter* ffrs,
        TMWParameter* fmw,
        TTPCParameter* ftpc,
        TMUSICParameter* fmusic,
        TLABRParameter* flabr,
        TSCIParameter* fsci,
        TIDParameter* fid,
        TSIParameter* fsi,
        TMRTOFMSParameter* fmrtof,
        TRangeParameter* frange)
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fCalArrayMain(new TClonesArray("FrsMainCalData"))
    ,   fCalArrayTPC(new TClonesArray("FrsTPCCalData"))
    ,   fCalArrayUser(new TClonesArray("FrsUserCalData"))
    ,   fCalArrayVFTX(new TClonesArray("FrsVFTXCalData"))
    ,   fHitArray(new TClonesArray("FrsHitData"))
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
}

FrsCal2Hit::FrsCal2Hit(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fCalArrayMain(new TClonesArray("FrsMainCalData"))
    ,   fCalArrayTPC(new TClonesArray("FrsTPCCalData"))
    ,   fCalArrayUser(new TClonesArray("FrsUserCalData"))
    ,   fCalArrayVFTX(new TClonesArray("FrsVFTXCalData"))
    ,   fHitArray(new TClonesArray("FrsHitData"))
{
}

FrsCal2Hit::~FrsCal2Hit()
{   
    c4LOG(info, "Deleting FrsCal2Hit task");
    if (fCalArrayMain) delete fCalArrayMain;
    if (fCalArrayTPC) delete fCalArrayTPC;
    if (fCalArrayUser) delete fCalArrayUser;
    if (fCalArrayVFTX) delete fCalArrayVFTX;
    if (fHitArray) delete fHitArray;
}

void FrsCal2Hit::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus FrsCal2Hit::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    fCalArrayMain = (TClonesArray*)mgr->GetObject("FrsMainCalData");
    c4LOG_IF(fatal, !fCalArrayMain, "FrsMainCalData branch not found!");

    fCalArrayTPC = (TClonesArray*)mgr->GetObject("FrsTPCCalData");
    c4LOG_IF(fatal, !fCalArrayTPC, "FrsTPCCalData branch not found!");

    fCalArrayUser = (TClonesArray*)mgr->GetObject("FrsUserCalData");
    c4LOG_IF(fatal, !fCalArrayUser, "FrsUserCalData branch not found!");

    fCalArrayVFTX = (TClonesArray*)mgr->GetObject("FrsVFTXCalData");
    c4LOG_IF(fatal, !fCalArrayVFTX, "FrsVFTXCalData branch not found!");

    mgr->Register("FrsHitData", "FRS Hit Data", fHitArray, !fOnline);

    Setup_Conditions("../../config/frs/");
    c4LOG_IF(fatal,!conditions_files_read, "You must set FrsCal2Hit->Setup_Conditions('your file path') to the folder containing the frs condition gates.");
    
    fCalArrayMain->Clear();
    fCalArrayTPC->Clear();
    fHitArray->Clear();

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
    //c4LOG(info,"EXEC");
    int multMain = fCalArrayMain->GetEntriesFast();
    int multTPC = fCalArrayTPC->GetEntriesFast();
    int multUser = fCalArrayUser->GetEntriesFast();
    int multVFTX = fCalArrayVFTX->GetEntriesFast();
    
    // something strange with VFTX
    if (multMain == 0 || multTPC == 0 || multUser == 0) return;
    
    // not even getting here right now
    fNEvents++;
    fCalHitMain = (FrsMainCalData*)fCalArrayMain->At(0);
    fCalHitTPC = (FrsTPCCalData*)fCalArrayTPC->At(0);
    fCalHitUser = (FrsUserCalData*)fCalArrayUser->At(0);
    fCalHitVFTX = (FrsVFTXCalData*)fCalArrayVFTX->At(0);

    WR_TS = fCalHitMain->Get_WR();


    /* -------------------------------- */
    // Scalers "analysis" 
    // (Moved from Calib in Go4)
    /* -------------------------------- */

    v830_n_main = fCalHitMain->Get_Scalers_N();
    v830_n_user = fCalHitUser->Get_Scalers_N();
    v830_index_main = fCalHitMain->Get_Scalers_Index();
    v830_index_user = fCalHitUser->Get_Scalers_Index();
    v830_scalers_main = fCalHitMain->Get_V830_Scalers();
    v830_scalers_user = fCalHitUser->Get_V830_Scalers();

    // maybe sc_long was better
    if (scaler_check_first_event == 1)
    {
        for (int i = 0; i < 32; i++)
        {
            sc_main_initial[i] = v830_scalers_main[i];
            sc_main_previous[i] = v830_scalers_main[i];
            sc_user_initial[i] = v830_scalers_user[i];
            sc_user_previous[i] = v830_scalers_user[i];
        }

        scaler_check_first_event = 0; 
    }

    time_in_ms = v830_scalers_main[scaler_ch_1kHz] - sc_main_initial[scaler_ch_1kHz];
    
    if (time_in_ms < 0)
    {
        sc_main_initial[scaler_ch_1kHz] = v830_scalers_main[scaler_ch_1kHz];
        time_in_ms = 0;
    }
        
    spill_count = v830_scalers_user[scaler_ch_spillstart] - sc_user_initial[scaler_ch_spillstart];

    ibin_for_s = ((time_in_ms / 1000) % 1000) + 1;
    ibin_for_100ms = ((time_in_ms / 100) % 4000) + 1;
    ibin_for_spill  = (spill_count % 1000) + 1;
            
    for (int k = 0; k < 32; k++)
    {
        increase_sc_temp_main[k] = v830_scalers_main[k] - sc_main_previous[k];
        increase_sc_temp_user[k] = v830_scalers_user[k] - sc_user_previous[k];
    }

    if (increase_sc_temp_user[0] != 0) // not sure how the go4 is dealing with this zero dividing
    {
        increase_sc_temp2 = 100 * increase_sc_temp_user[1] / increase_sc_temp_user[0];
        increase_sc_temp3 = 100 * increase_sc_temp_user[5] / increase_sc_temp_user[6];
    }
    

    extraction_time_ms += v830_scalers_main[scaler_ch_1kHz] - sc_main_previous[scaler_ch_1kHz];

    if((v830_scalers_user[scaler_ch_spillstart] - sc_user_previous[scaler_ch_spillstart]) != 0)
    {
        extraction_time_ms = 0;
    }
            
    ibin_clean_for_s = (((time_in_ms / 1000) + 20) % 1000) + 1;
    ibin_clean_for_100ms = (((time_in_ms / 100) + 200) % 4000) + 1;
    ibin_clean_for_spill = ((spill_count + 990) % 20) + 1;

    for (int i = 0; i < 32; i++)
    {   
        sc_main_previous[i] = v830_scalers_main[i];
        sc_user_previous[i] = v830_scalers_user[i];
    }
            

    /* ---------------------------------------------------- */
    // Start of MUSIC analysis                              //
    /* ---------------------------------------------------- */

    music_e1 = fCalHitUser->Get_music_e1();
    music_e2 = fCalHitUser->Get_music_e2();
    music_t1 = fCalHitMain->Get_music_t1();
    music_t2 = fCalHitMain->Get_music_t2();
    // we don't use music 3


    //c4LOG(info,"MUSIC Energy analysis.");
    music1_anodes_cnt = 0;
    music2_anodes_cnt = 0;

    /* reset de[i] and de_cor[i] etc */

    for (int i = 0; i < 8; i++)
    {
        /*  8 anodes of TUM MUSIC */
        // first MUSIC threshold changed to 4 (01/12/23)
        if (music_e1[i] > 4)
        {
            music_b_e1[i] = Check_WinCond_Multi(music_e1[i], cMusic1_E, i);
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
            music_b_e2[i] = Check_WinCond_Multi(music_e2[i], cMusic2_E, i);
            if (music_b_e2[i])
            {
                music2_anodes_cnt++;
            }
        }
        if (music_t2[i] > 0)
        {
            music_b_t2[i] = Check_WinCond_Multi(music_t2[i], cMusic2_T, i);
        }
    }

    /*for (int i = 0; i < 4; i++)
    {
        // 4 anodes of MUSIC OLD
        // third MUSIC travelling
        if (music_e3[i] > 0)
        {
            music_b_e3[i] = Check_WinCond_Multi(music_e3[i], cMusic3_E, i);
            if (music_b_e3[i])
            {
                music3_anodes_cnt++;
            }
        }
        if (music_t3[i] > 0)
        {
            music_b_t3[i] = Check_WinCond_Multi(music_t3[i], cMusicT_3, i);
        }
    }*/

    #ifndef MUSIC_ANA_NEW
    if (music1_anodes_cnt == 8)
    {
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

    // CEJ: 8 in go4, but how can it be 8?
    /*if (music3_anodes_cnt == 8)
    {
        Float_t r1 = ((music_e3[0]) * music->e3_gain[0] + music->e3_off[0]) * ((music_e3[1]) * music->e3_gain[1] + music->e3_off[1]);
        Float_t r2 = ((music_e3[2]) * music->e3_gain[2] + music->e3_off[2]) * ((music_e3[3]) * music->e3_gain[3] + music->e3_off[3]);

        if ((r1 > 0) && (r2 > 0))
        {
            // b_de3 = kTRUE;
            de[2] = sqrt(sqrt(r1) * sqrt(r2));
            de_cor[2] = de[2];
        }
    }*/

    // Position (X) correction by TPC //
    // this should not be in the music3_anodes_cnt if{}
    // but it is in our Go4
    
    //c4LOG(info,"EXEC TPC analysis");
    b_tpc_xy = fCalHitTPC->Get_b_tpc_xy(); // maybe this should be outside? JEL: Yep this must go here!
    
    
    if (b_tpc_xy[4] && b_tpc_xy[5])
    {
        music1_x_mean = fCalHitTPC->Get_tpc_music41_x();
        music2_x_mean = fCalHitTPC->Get_tpc_music42_x();
        //music3_x_mean = fCalHitTPC->Get_tpc_music43_x();

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
        
        /*if (b_de3)
        {
            power = 1.;
            Corr = 0.;
            for (int i = 0; i < 4; i++)
            {
                Corr += music->pos_a3[i] * power;
                power *= music3_x_mean;
            }
            if (Corr != 0)
            {
                Corr = music->pos_a3[0] / Corr;
                de_cor[2] = de[2] * Corr;
            }
        }*/
    }
    
    /* ----------------------------------------------- */
    // Start of Scintillator Analysis
    /* ----------------------------------------------- */

    
    // V1290
    //c4LOG(info,"EXEC SCI V1290s");

    for (int i = 0; i < 15; i++) tdc_array[i] = fCalHitMain->Get_TDC_channel(i);

    // In Raw2Cal we should make sure no zeros are added to vector     
    // CEJ: 24/01/24 possibly vectors don't work here since [i] hit should match to [i] hit in l/r?
    // SCI 21 L and R
    for (int i = 0; i < tdc_array[2].size(); i++)
    {      
        if (!(tdc_array[2].size()>0 && tdc_array[3].size() > 0)) continue;
        // CEJ: maybe all of this can be rewritten to use vectors..figure out later
        if (i >= tdc_array[3].size()) break; // needed range check

        mhtdc_sc21lr_dt.emplace_back(sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[2].at(i) - tdc_array[3].at(i)));
        mhtdc_sc21lr_x.emplace_back(mhtdc_sc21lr_dt.at(i) * sci->mhtdc_factor_21l_21r + sci->mhtdc_offset_21l_21r);
    }
    // always check these conditions (go4 does it 10x without if-statement)
    float sc21pos_from_tpc = -999.9;
    if (b_tpc_xy[0] && b_tpc_xy[1])
    {
        sc21pos_from_tpc = fCalHitTPC->Get_tpc21_22_sc21_x();
    }
    else if (b_tpc_xy[2] && b_tpc_xy[3])
    {
        sc21pos_from_tpc = fCalHitTPC->Get_tpc23_24_sc21_x();
    }

    // SCI 22 L and R
    for (int i = 0; i < tdc_array[12].size(); i++)
    {
        if (!(tdc_array[12].size()>0 && tdc_array[13].size() > 0)) continue;
        if (i >= tdc_array[13].size()) break; // needed range check // CEJ: this is never true or the analysis doesn't make sense
        mhtdc_sc22lr_dt.emplace_back(sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[12].at(i) - tdc_array[13].at(i)));
        mhtdc_sc22lr_x.emplace_back(mhtdc_sc22lr_dt.at(i) * sci->mhtdc_factor_22l_22r + sci->mhtdc_offset_22l_22r);
        if (i == 0)
        {
            // only do this if there is a case for 22l and 22r != 0. we don't need to do it 10x though
            float sc22pos_from_tpc = -999.9;
            if (b_tpc_xy[0] && b_tpc_xy[1])
            {
                sc22pos_from_tpc = fCalHitTPC->Get_tpc21_22_sc22_x();
            }
            else if (b_tpc_xy[2] && b_tpc_xy[3])
            {
                sc22pos_from_tpc = fCalHitTPC->Get_tpc23_24_sc22_x();
            }
        }
    }
    
    
    // only take first hit (?) for 41, 42, 43, 31, 81
    if (tdc_array[0].size() > 0 && tdc_array[1].size() > 0)
    {
        mhtdc_sc41lr_dt = sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[0].at(0) - tdc_array[1].at(0));
        mhtdc_sc41lr_x = mhtdc_sc41lr_dt * sci->mhtdc_factor_41l_41r + sci->mhtdc_offset_41l_41r;
    }
    if (tdc_array[4].size() > 0 && tdc_array[14].size() > 0)
    {
        mhtdc_sc42lr_dt = sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[4].at(0) - tdc_array[14].at(0));
        mhtdc_sc42lr_x = mhtdc_sc42lr_dt * sci->mhtdc_factor_42l_42r + sci->mhtdc_offset_42l_42r;
    }
    if (tdc_array[5].size() > 0 && tdc_array[6].size() > 0)
    {
        mhtdc_sc43lr_dt = sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[5].at(0) - tdc_array[6].at(0));
        mhtdc_sc43lr_x = mhtdc_sc43lr_dt * sci->mhtdc_factor_43l_43r + sci->mhtdc_offset_43l_43r;
    }
    if (tdc_array[9].size() > 0 && tdc_array[10].size() > 0)
    {
        mhtdc_sc31lr_dt = sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[9].at(0) - tdc_array[10].at(0));
        mhtdc_sc31lr_x = mhtdc_sc31lr_dt * sci->mhtdc_factor_31l_31r + sci->mhtdc_offset_31l_31r;
    }
    if (tdc_array[7].size() > 0 && tdc_array[8].size() > 0)
    {
        mhtdc_sc81lr_dt = sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[7].at(0) - tdc_array[8].at(0));
        mhtdc_sc81lr_x = mhtdc_sc81lr_dt * sci->mhtdc_factor_81l_81r + sci->mhtdc_offset_81l_81r;
    }


    if (tdc_array[0].size() > 0 && tdc_array[1].size() > 0)
    {   
        // 21 -> 41
        if (tdc_array[3].size() > 0 && tdc_array[2].size() > 0)
        {
            for (int i = 0; i < tdc_array[2].size(); i++)
            {
                if (tdc_array[0].size() <= i || tdc_array[1].size() <= i || tdc_array[3].size() <= i) break;
                
                mhtdc_tof4121.emplace_back(sci->mhtdc_factor_ch_to_ns * (0.5 * (tdc_array[0].at(0) + tdc_array[1].at(0)) - 0.5 * (tdc_array[2].at(i) + tdc_array[3].at(i))) + sci->mhtdc_offset_41_21);
            }
        }

        // 22 -> 41
        if (tdc_array[12].size() > 0 && tdc_array[13].size() > 0)
        {
            for (int i = 0; i < tdc_array[12].size(); i++)
            {
                if (tdc_array[0].size() <= i || tdc_array[1].size() <= i || tdc_array[13].size() <= i) break;
                mhtdc_tof4122.emplace_back(sci->mhtdc_factor_ch_to_ns * (0.5 * (tdc_array[0].at(0) + tdc_array[1].at(0)) - 0.5 * (tdc_array[12].at(i) + tdc_array[13].at(i))) + sci->mhtdc_offset_41_22);
            }
        }
    }


    if ((tdc_array[2].size() > 0 ) && (tdc_array[0].size() > 0) && (tdc_array[1].size() > 0))
    {
        if (tdc_array[3].size() > 0) // CEJ: should be implicitly true or this all falls apart..
        {
            // 21 -> 42
            if (tdc_array[4].size() > 0 && tdc_array[14].size() > 0)
            {
                mhtdc_tof4221 = sci->mhtdc_factor_ch_to_ns * (0.5 * (tdc_array[0].at(0) + tdc_array[1].at(0)) - 0.5 * (tdc_array[4].at(0) + tdc_array[14].at(0))) + sci->mhtdc_offset_42_21;
            }
            
            // 21 -> 43
            if (tdc_array[5].size() > 0 && tdc_array[6].size() > 0)
            {
                mhtdc_tof4321 = sci->mhtdc_factor_ch_to_ns * (0.5 * (tdc_array[0].at(0) + tdc_array[1].at(0)) - 0.5 * (tdc_array[5].at(0) + tdc_array[6].at(0))) + sci->mhtdc_offset_43_21;
            }

            // 21 -> 31
            if (tdc_array[9].size() > 0 && tdc_array[10].size() > 0)
            {
                mhtdc_tof3121 = sci->mhtdc_factor_ch_to_ns * (0.5 * (tdc_array[0].at(0) + tdc_array[1].at(0)) - 0.5 * (tdc_array[9].at(0) + tdc_array[10].at(0))) + sci->mhtdc_offset_31_21;
            }

            // 21 -> 81
            if (tdc_array[7].size() > 0 && tdc_array[8].size() > 0)
            {
                mhtdc_tof8121 = sci->mhtdc_factor_ch_to_ns * (0.5 * (tdc_array[0].at(0) + tdc_array[1].at(0)) - 0.5 * (tdc_array[7].at(0) + tdc_array[8].at(0))) + sci->mhtdc_offset_81_21;
            }
        }
    }
    

    //c4LOG(info,"EXEC TAC and ADC's in main crate.");
    for (int index = 0; index < 14; index++) de_array[index] = fCalHitMain->Get_De_channel(index);
    dt_array = fCalHitUser->Get_dt_array();


    c4LOG_IF(fatal, (de_array == nullptr) || (dt_array == nullptr), "These two arrays are not declared correctly." );

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
        // find a way to read in cConditons
        // 'posref' in go4 does nothing
        
        // what even is this code:?
        // CEJ: this code maps FRS array indices to 0-based array here
        // could just create larger arrays, it felt weird but maybe this is weirder
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
            sci_e[i] = (sci_r[i] - sci->re_a[0][j]);
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
                sum += sci->x_a[k][i] * power;
                power *= R;
            }
            sci_x[i] = sum;
            sci_b_x[i] = Check_WinCond(sci_x[i], cSCI_X);
        }
    } // loop for sci values


    //c4LOG(info,"EXEC calibrate TOF");
    /*----------------------------------------------------------*/
    // Calibrated ToF - dt will be in dt_array, from UserCrate
    /*----------------------------------------------------------*/
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

    /*----------------------------------------------------------*/
    // Start of MHTDC ID analysis
    /*----------------------------------------------------------*/
    //c4LOG(info,"EXEC MHTDC ANALYSIS");
    float temp_s8x = mhtdc_sc81lr_x;
    temp_s4x = -999.;
    if (b_tpc_xy[4] && b_tpc_xy[5])
    {
        temp_s4x = fCalHitTPC->Get_tpc_x_s4();
    }

    float temp_s2x = -999.;
    std::vector<float> temp_s2x_mhtdc;
    float temp_a2 = 0;

    if (id->mhtdc_s2pos_option == 1)
    {
        for (int i = 0; i < mhtdc_sc21lr_x.size(); i++)
        {
            temp_s2x_mhtdc.emplace_back(mhtdc_sc21lr_x[i]);
        }
    }
    else if (id->mhtdc_s2pos_option == 3)
    {
        for (int i = 0; i < mhtdc_sc22lr_x.size(); i++)
        {
            temp_s2x_mhtdc.emplace_back(mhtdc_sc22lr_x[i]);
        }
    }
    else if (id->mhtdc_s2pos_option == 2)
    {
        if (b_tpc_xy[2] && b_tpc_xy[3])
        {
            temp_s2x = fCalHitTPC->Get_tpc_x_s2_foc_23_24();
            temp_a2 = fCalHitTPC->Get_tpc_angle_x_s2_foc_23_24();
        }
        else if (b_tpc_xy[1] && b_tpc_xy[3])
        {
            temp_s2x = fCalHitTPC->Get_tpc_x_s2_foc_22_24();
            temp_a2 = fCalHitTPC->Get_tpc_angle_x_s2_foc_22_24();
        }
        else if (b_tpc_xy[0] && b_tpc_xy[1])
        {
            temp_s2x = fCalHitTPC->Get_tpc_x_s2_foc_21_22();
            temp_a2 = fCalHitTPC->Get_tpc_angle_x_s2_foc_21_22();
        }
    }


    //   S2S4 MultihitTDC ID analysis
    float mean_brho_s2s4 = 0.5 * (frs->bfield[2] + frs->bfield[3]);

    // frs go4 doesn't have this selection
    if (id->mhtdc_s2pos_option == 1)
    {

        if (id->tof_s4_select == 1)
        {
            for (int i = 0; i < mhtdc_tof4121.size(); i++)
            {
                if (mhtdc_tof4121.at(i) > -100)
                {
                    id_mhtdc_beta_s2s4.emplace_back((id->mhtdc_length_sc2141 / mhtdc_tof4121.at(i)) / speed_light);
                }
            }
        }
        else if (id->tof_s4_select == 3)
        {
            for (int i = 0; i < mhtdc_tof4122.size(); i++)
            {
                if (mhtdc_tof4122.at(i) > -100)
                {
                    id_mhtdc_beta_s2s4.emplace_back((id->mhtdc_length_sc2241 / mhtdc_tof4122.at(i)) / speed_light);
                }
            }
        }

        // calculate delta (momentum deviation) and AoQ
        for (int i = 0; i < id_mhtdc_beta_s2s4.size(); i++)
        {
            id_mhtdc_gamma_s2s4.emplace_back(1. / sqrt(1. - id_mhtdc_beta_s2s4.at(i) * id_mhtdc_beta_s2s4.at(i)));
            
            // does this bit just clear arrays? can we just clear vectors at the end of event and skip this?
            /*if (temp_s4x == -999 || temp_s2x_mhtdc[i] == -999)
            {
                id_mhtdc_aoq_s2s4[i] = 0;
                id_mhtdc_aoq_corr_s2s4[i] = 0;
            }*/
            /*else*/ 
            if (temp_s4x > -200. && temp_s4x < 200. && temp_s2x_mhtdc[i] > -200. && temp_s2x_mhtdc[i] < 200.)
            {
                id_mhtdc_delta_s2s4.emplace_back((temp_s4x - (temp_s2x_mhtdc[i] * frs->magnification[1])) / (-1.0 * frs->dispersion[1] * 1000.0)); // metre to mm
                if (id_mhtdc_beta_s2s4.at(i) > 0.0 && id_mhtdc_beta_s2s4.at(i) < 1.0)
                {
                    id_mhtdc_aoq_s2s4.emplace_back(mean_brho_s2s4 * (1. + id_mhtdc_delta_s2s4[i]) * temp_tm_to_MeV / (temp_mu * id_mhtdc_beta_s2s4.at(i) * id_mhtdc_gamma_s2s4[i]));

                    // Gain match AoQ
                    for (int j = 0; j < AoQ_Shift_array; j++)
                    {
                        if (ts_mins >= FRS_WR_i[j] && ts_mins < FRS_WR_j[j])
                        {
                            id_mhtdc_aoq_s2s4.at(i) = (id_mhtdc_aoq_s2s4.at(i) - AoQ_shift_Sci21_value[j]) - 0.029100; // Why isn't this float coded in a config file?
                        }
                    }

                    // No angle correction for SCI
                    id_mhtdc_aoq_corr_s2s4.emplace_back(id_mhtdc_aoq_s2s4.at(i));

                    /*mhtdc_gamma1square.emplace_back(1.0 + TMath::Power(((1.0 / aoq_factor) * (id_brho[0] / id_mhtdc_aoq_s2s4[i])), 2));
                    id_mhtdc_gamma_ta_s2.emplace_back(TMath::Sqrt(mhtdc_gamma1square[i]));
                    id_mhtdc_dEdegoQ.emplace_back((id_mhtdc_gamma_ta_s2[i] - id_mhtdc_gamma_s2s4[i]) * id_mhtdc_aoq_s2s4[i]);

                    // doesn't make sense to do this when we have no id_mhtdc_z_music41 yet..
                    id_mhtdc_dEdeg.emplace_back(id_mhtdc_dEdegoQ[i] * id_mhtdc_z_music41[i]);*/

                }
            }
        }
    }
    else if (id->mhtdc_s2pos_option == 2)
    {
        if (id->tof_s4_select == 1)
        {
            for (int i = 0; i < mhtdc_tof4121.size(); i++)
            {
                if (mhtdc_tof4121[i] > -100)
                {
                    id_mhtdc_beta_s2s4.emplace_back((id->mhtdc_length_sc2141 / mhtdc_tof4121[i]) / speed_light);
                }
            }
        }
        else if (id->tof_s4_select == 3)
        {
            for (int i = 0; i < mhtdc_tof4122.size(); i++)
            {
                if (mhtdc_tof4122[i] > -100)
                {
                    id_mhtdc_beta_s2s4.emplace_back((id->mhtdc_length_sc2241 / mhtdc_tof4122[i]) / speed_light);
                }
            }
        }
        
        // Calculation of velocity beta and gamma
        for (int i = 0; i < id_mhtdc_beta_s2s4.size(); i++)
        {
            id_mhtdc_gamma_s2s4.emplace_back(1. / sqrt(1. - id_mhtdc_beta_s2s4.at(i) * id_mhtdc_beta_s2s4.at(i)));

            // Calculate delta (momentum deviation) and AoQ
            /*if(temp_s4x == -999 || temp_s2x == -999)
            {
                id_mhtdc_aoq_s2s4[i]=0;
                id_mhtdc_aoq_corr_s2s4[i]=0;
            }
            else*/ if (temp_s4x > -200. && temp_s4x < 200. && temp_s2x > -200. && temp_s2x < 200.)
            {   
                // CEJ: this is a pointlessly repeated calculation, takes single value
                id_mhtdc_delta_s2s4.emplace_back((temp_s4x - (temp_s2x * frs->magnification[1])) / (-1.0 * frs->dispersion[1] * 1000.0)); //1000 is dispertsion from meter to mm. -1.0 is sign definition.

                if (id_mhtdc_beta_s2s4.at(i) > 0.0 && id_mhtdc_beta_s2s4.at(i) < 1.0)
                {
                    id_mhtdc_aoq_s2s4.emplace_back(mean_brho_s2s4 *(1. + id_mhtdc_delta_s2s4[i]) * temp_tm_to_MeV / (temp_mu * id_mhtdc_beta_s2s4.at(i) * id_mhtdc_gamma_s2s4.at(i)));
                
                    // Gain match AoQ
                    // ** OLD STARTS BELOW ** //
                    for(int j = 0; j < AoQ_Shift_array; j++)
                    {
                        if(ts_mins >= FRS_WR_i[j] && ts_mins < FRS_WR_j[j])
                        {
                            id_mhtdc_aoq_s2s4.at(i) = id_mhtdc_aoq_s2s4.at(i) - AoQ_shift_TPC_value[j] - 0.01097;
                        }
                    }
                    
                    id_mhtdc_aoq_corr_s2s4.emplace_back(id_mhtdc_aoq_s2s4.at(i) - id->a2AoQCorr * temp_a2);
                    
                    /*mhtdc_gamma1square.emplace_back(1.0 + TMath::Power(((1.0 / aoq_factor) * (id_brho[0] / id_mhtdc_aoq_s2s4[i])), 2));
                    id_mhtdc_gamma_ta_s2.emplace_back(TMath::Sqrt(mhtdc_gamma1square[i]));
                    id_mhtdc_dEdegoQ.emplace_back((id_mhtdc_gamma_ta_s2[i]  - id_mhtdc_gamma_s2s4[i]) * id_mhtdc_aoq_s2s4[i]);
                    // CEJ: again pointless...but done below?
                    id_mhtdc_dEdeg.emplace_back(id_mhtdc_dEdegoQ[i] * id_mhtdc_z_music41[i]);*/
                    
                }
            }
        }
    }

    // Calculation of dE and Z from MUSIC41
    for (int i = 0; i < id_mhtdc_beta_s2s4.size(); i++)
    {
        float temp_music41_de = de[0] > 0.0;
        if ((temp_music41_de > 0.0) && (id_mhtdc_beta_s2s4.at(i) > 0.0) && (id_mhtdc_beta_s2s4.at(i) < 1.0))
        {
            power = 1.;
            sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->mhtdc_vel_a_music41[j];
                power *= id_mhtdc_beta_s2s4.at(i);
                
            }
            id_mhtdc_v_cor_music41.emplace_back(sum);

            if (id_mhtdc_v_cor_music41.at(i) > 0.0)
            {
                id_mhtdc_z_music41.emplace_back(frs->primary_z * sqrt(de[0] / id_mhtdc_v_cor_music41.at(i)) + id->mhtdc_offset_z_music41);
            }
        }
        
    }

    for (int i = 0; i < id_mhtdc_beta_s2s4.size(); i++)
    {
        float temp_music42_de = de[1] > 0.0;
        if((temp_music42_de > 0.0)  && (id_mhtdc_beta_s2s4.at(i) > 0.0) && (id_mhtdc_beta_s2s4.at(i) < 1.0))
        {
            power = 1.;
            sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->mhtdc_vel_a_music42[j];
                power *= id_mhtdc_beta_s2s4.at(i);
            }
            id_mhtdc_v_cor_music42.emplace_back(sum);
            
            if (id_mhtdc_v_cor_music42.at(i)> 0.0)
            {
                id_mhtdc_z_music42.emplace_back(frs->primary_z * sqrt(de[1] / id_mhtdc_v_cor_music42.at(i)) + id->mhtdc_offset_z_music42);
            }
        }
    }

    // Gain match Z
    for (int i = 0; i < Z_Shift_array; i++)
    {   
        // music41 and 42 same size
        for (int j = 0; j < id_mhtdc_z_music41.size(); j++)
        {
            if (ts_mins >= FRS_WR_a[i] && ts_mins < FRS_WR_b[i])
            {
                id_mhtdc_z_music41.at(j) = id_mhtdc_z_music41.at(j) - Z1_shift_value[i];
                id_mhtdc_z_music42.at(j) = id_mhtdc_z_music42.at(j) - Z2_shift_value[i];
            }
        }
    }
    for (int i = 0; i < id_mhtdc_beta_s2s4.size(); i++)
    {
        if (id_mhtdc_aoq_s2s4.at(i) != 0)
        {
            mhtdc_gamma1square.emplace_back(1.0 + TMath::Power(((1.0 / aoq_factor) * (id_brho[0] / id_mhtdc_aoq_s2s4.at(i))), 2));
            id_mhtdc_gamma_ta_s2.emplace_back(TMath::Sqrt(mhtdc_gamma1square.at(i)));
            id_mhtdc_dEdegoQ.emplace_back((id_mhtdc_gamma_ta_s2[i] - id_mhtdc_gamma_s2s4[i]) * id_mhtdc_aoq_s2s4.at(i));
            id_mhtdc_dEdeg.emplace_back(id_mhtdc_dEdegoQ[i] * id_mhtdc_z_music41[i]);
        }
    }

    //c4LOG(info,"EXEC EXtraction of TPC values");
    if (id->x_s2_select == 1)
    {   
        if (b_tpc_xy[2] && b_tpc_xy[3])
        {   
            id_x2 = fCalHitTPC->Get_tpc_x_s2_foc_23_24();
            id_y2 = fCalHitTPC->Get_tpc_y_s2_foc_23_24();
            id_a2 = fCalHitTPC->Get_tpc_angle_x_s2_foc_23_24();
            id_b2 = fCalHitTPC->Get_tpc_angle_y_s2_foc_23_24();
        }
        else if (b_tpc_xy[1] && b_tpc_xy[3])
        {
            id_x2 = fCalHitTPC->Get_tpc_x_s2_foc_22_24();
            id_y2 = fCalHitTPC->Get_tpc_y_s2_foc_22_24();
            id_a2 = fCalHitTPC->Get_tpc_angle_x_s2_foc_22_24();
            id_b2 = fCalHitTPC->Get_tpc_angle_y_s2_foc_22_24();
        }
        else if (b_tpc_xy[0] && b_tpc_xy[1])
        {   
            id_x2 = fCalHitTPC->Get_tpc_x_s2_foc_21_22();
            id_y2 = fCalHitTPC->Get_tpc_y_s2_foc_21_22();
            id_a2 = fCalHitTPC->Get_tpc_angle_x_s2_foc_21_22();
            id_b2 = fCalHitTPC->Get_tpc_angle_y_s2_foc_21_22();
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
        id_x4 = fCalHitTPC->Get_tpc_x_s4();
        id_y4 = fCalHitTPC->Get_tpc_y_s4();
        id_a4 = fCalHitTPC->Get_tpc_angle_x_s4();
        id_b4 = fCalHitTPC->Get_tpc_angle_y_s4();
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

    // CEJ: commented because double def?
    /*temp_s4x = -999.;
    if (b_tpc_xy[4] && b_tpc_xy[5])
    {
        temp_s4x = fCalHitTPC->Get_tpc_x_s4();
    }*/

    /* --------------------------------------------------------------------------*/
    // VFTX start here
    // (moved from Go4 as we need id_a2 and it gets calculated twice otherwise?)
    /* --------------------------------------------------------------------------*/
    //c4LOG(info,"EXEC VFTX");

    if (multVFTX > 0)
    {
        TRaw_vftx = fCalHitVFTX->Get_TRaw_vftx();

        // loop over 21 or 22 size, check 41l/r are not empty
        for (int i = 0; i < TRaw_vftx[0].size(); i++)
        {   
            // 2141
            if (TRaw_vftx[4].size() != 0)
            {
                vftx_tof2141.emplace_back((0.5 * ((Double_t)TRaw_vftx[4].at(0) + (Double_t)TRaw_vftx[5].at(0)) - 0.5 * ((Double_t)TRaw_vftx[0].at(i) + (Double_t)TRaw_vftx[1].at(i))));
                vftx_tof2141_calib.emplace_back(vftx_tof2141.at(i) / 1000. + sci->vftx_offset_2141);
            }

            // 2142
            if (TRaw_vftx[6].size() != 0)
            {
                vftx_tof2142.emplace_back((0.5 * ((Double_t)TRaw_vftx[6].at(0) + (Double_t)TRaw_vftx[7].at(0)) - 0.5 * ((Double_t)TRaw_vftx[0].at(i) + (Double_t)TRaw_vftx[1].at(i))));
                vftx_tof2142_calib.emplace_back(vftx_tof2142.at(i) / 1000. + sci->vftx_offset_2142);
        
            }
        }

        for (int i = 0; i < TRaw_vftx[2].size(); i++)
        {
            // 2241
            if (TRaw_vftx[4].size() != 0)
            {
                vftx_tof2241.emplace_back((0.5 * ((Double_t)TRaw_vftx[4].at(0) + (Double_t)TRaw_vftx[5].at(0)) - 0.5 * ((Double_t)TRaw_vftx[2].at(i) + (Double_t)TRaw_vftx[3].at(i))));
                vftx_tof2241_calib.emplace_back(vftx_tof2241.at(i) / 1000. + sci->vftx_offset_2241);
            }

            // 2242
            if (TRaw_vftx[6].size() != 0)
            {
                vftx_tof2242.emplace_back((0.5 * ((Double_t)TRaw_vftx[6].at(0) + (Double_t)TRaw_vftx[7].at(0)) - 0.5 * ((Double_t)TRaw_vftx[2].at(i) + (Double_t)TRaw_vftx[3].at(i))));
                vftx_tof2242_calib.emplace_back(vftx_tof2242.at(i) / 1000. + sci->vftx_offset_2242);
            }
        }

        /*
        temp_s4x = -999.;
        if (b_tpc_xy[4] && b_tpc_xy[5])
        {
            temp_s4x = fCalHitTPC->Get_tpc_x_s4();
        }*/

        float temp_sci21x = -999.;
        if (id->vftx_s2pos_option == 1)
        {
            // do nothing?
        }
        else if (id->vftx_s2pos_option == 2)
        {
            if (b_tpc_xy[0] && b_tpc_xy[1])
            {
                temp_sci21x = fCalHitTPC->Get_tpc_x_s2_foc_21_22();
            }
            else if (b_tpc_xy[2] && b_tpc_xy[3])
            {
                temp_sci21x = fCalHitTPC->Get_tpc_x_s2_foc_23_24();
            }
            else if (b_tpc_xy[1] && b_tpc_xy[3])
            {
                temp_sci21x = fCalHitTPC->Get_tpc_x_s2_foc_22_24();
            }
        }
        
        // number of 21l hits
        for (int i = 0; i < TRaw_vftx[0].size(); i++)
        {
            id_vftx_beta_2141.emplace_back((id->vftx_length_2141 / vftx_tof2141_calib.at(i)) / speed_light);
            id_vftx_beta_2142.emplace_back((id->vftx_length_2142 / vftx_tof2142_calib.at(i)) / speed_light);
            id_vftx_gamma_2141.emplace_back(1. / sqrt(1. - id_vftx_beta_2141.at(i) * id_vftx_beta_2141.at(i)));
            id_vftx_gamma_2142.emplace_back(1. / sqrt(1. - id_vftx_beta_2142.at(i) * id_vftx_beta_2142.at(i)));

            if (temp_s4x > -200. && temp_s4x < 200. && temp_sci21x > -200. && temp_sci21x < 200)
            {
                id_vftx_delta_24 = (temp_s4x - (temp_sci21x * frs->magnification[1])) / (-1.0 * frs->dispersion[1] * 1000.0);
                if (id_vftx_beta_2141.at(i) > 0.0 && id_vftx_beta_2141.at(i) < 1.0)
                {
                    id_vftx_aoq_2141.emplace_back(mean_brho_s2s4 * (1. + id_vftx_delta_24) * temp_tm_to_MeV / (temp_mu * id_vftx_beta_2141.at(i) * id_vftx_gamma_2141.at(i)));
                    id_vftx_aoq_corr_2141.emplace_back(id_vftx_aoq_2141.at(i) - id->a2AoQCorr * id_a2);
                }
                if (id_vftx_beta_2142.at(i) > 0.0 && id_vftx_beta_2142.at(i) < 1.0)
                {
                    id_vftx_aoq_2142.emplace_back(mean_brho_s2s4 * (1. + id_vftx_delta_24) * temp_tm_to_MeV / (temp_mu * id_vftx_beta_2142.at(i) * id_vftx_gamma_2142.at(i)));
                    id_vftx_aoq_corr_2142.emplace_back(id_vftx_aoq_2142.at(i) - id->a2AoQCorr * id_a2);
                }
            }

            if ((de[0] > 0.0) && (id_vftx_beta_2141.at(i) > 0.0) && (id_vftx_beta_2141.at(i) < 1.0))
            {
                power = 1.;
                sum = 0.;
                for (int j = 0; j < 4; j++)
                {
                    sum += power * id->vftx_vel_a_music41[j];
                    power *= id_vftx_beta_2141.at(i);
                }

                id_vftx_vcor_2141.emplace_back(sum);
                
                if (id_vftx_vcor_2141.at(i) > 0.0)
                {
                    id_vftx_z_2141.emplace_back(frs->primary_z * sqrt(de[0] / id_vftx_vcor_2141.at(i)));
                    id_vftx_z2_2141.emplace_back(frs->primary_z * sqrt(de[1] / id_vftx_vcor_2141.at(i)));
                }
            }

            if ((de[0] > 0.0) && (id_vftx_beta_2142.at(i) > 0.0) && (id_vftx_beta_2142.at(i) < 1.0))
            {
                power = 1.;
                sum = 0.;
                for (int j = 0; j < 4; j++)
                {
                    sum += power * id->vftx_vel_a_music41[j];
                    power *= id_vftx_beta_2142.at(i);
                }

                id_vftx_vcor_2142.emplace_back(sum);

                if (id_vftx_vcor_2142.at(i) > 0.0)
                {
                    id_vftx_z_2142.emplace_back(frs->primary_z * sqrt(de[0] / id_vftx_vcor_2142.at(i)));
                    id_vftx_z2_2142.emplace_back(frs->primary_z * sqrt(de[1] / id_vftx_vcor_2142.at(i)));
                }
            }

        }

        // number of 22l hits
        for (int i = 0; i < TRaw_vftx[2].size(); i++)
        {
            id_vftx_beta_2241.emplace_back((id->vftx_length_2241 / vftx_tof2241_calib.at(i)) / speed_light);
            id_vftx_beta_2242.emplace_back((id->vftx_length_2242 / vftx_tof2242_calib.at(i)) / speed_light);
            id_vftx_gamma_2241.emplace_back(1. / sqrt(1. - id_vftx_beta_2241.at(i) * id_vftx_beta_2241.at(i)));
            id_vftx_gamma_2242.emplace_back(1. / sqrt(1. - id_vftx_beta_2242.at(i) * id_vftx_beta_2242.at(i)));

            if (temp_s4x > -200. && temp_s4x < 200. && temp_sci21x > -200. && temp_sci21x < 200)
            {
                id_vftx_delta_24 = (temp_s4x - (temp_sci21x * frs->magnification[1])) / (-1.0 * frs->dispersion[1] * 1000.0);
                if (id_vftx_beta_2241.at(i) > 0.0 && id_vftx_beta_2241.at(i) < 1.0)
                {
                    id_vftx_aoq_2241.emplace_back(mean_brho_s2s4 * (1. + id_vftx_delta_24) * temp_tm_to_MeV / (temp_mu * id_vftx_beta_2241.at(i) * id_vftx_gamma_2241.at(i)));
                    id_vftx_aoq_corr_2241.emplace_back(id_vftx_aoq_2241.at(i) - id->a2AoQCorr * id_a2);
                }
                if (id_vftx_beta_2242.at(i) > 0.0 && id_vftx_beta_2242.at(i) < 1.0)
                {
                    id_vftx_aoq_2242.emplace_back(mean_brho_s2s4 * (1. + id_vftx_delta_24) * temp_tm_to_MeV / (temp_mu * id_vftx_beta_2242.at(i) * id_vftx_gamma_2242.at(i)));
                    id_vftx_aoq_corr_2242.emplace_back(id_vftx_aoq_2242.at(i) - id->a2AoQCorr * id_a2);
                }
            }

            if ((de[0] > 0.0) && (id_vftx_beta_2241.at(i) > 0.0) && (id_vftx_beta_2241.at(i) < 1.0))
            {
                power = 1.;
                sum = 0.;
                for (int j = 0; j < 4; j++)
                {
                    sum += power * id->vftx_vel_a_music41[j];
                    power *= id_vftx_beta_2241.at(i);
                }

                id_vftx_vcor_2241.emplace_back(sum);

                if (id_vftx_vcor_2241.at(i) > 0.0)
                {
                    id_vftx_z_2241.emplace_back(frs->primary_z * sqrt(de[0] / id_vftx_vcor_2241.at(i)));
                    id_vftx_z2_2241.emplace_back(frs->primary_z * sqrt(de[1] / id_vftx_vcor_2241.at(i)));
                }
            }

            if ((de[0] > 0.0) && (id_vftx_beta_2242.at(i) > 0.0) && (id_vftx_beta_2242.at(i) < 1.0))
            {
                power = 1.;
                sum = 0.;
                for (int j = 0; j < 4; j++)
                {
                    sum += power * id->vftx_vel_a_music41[j];
                    power *= id_vftx_beta_2242.at(i);
                }

                id_vftx_vcor_2242.emplace_back(sum);

                if (id_vftx_vcor_2242.at(i) > 0.0)
                {
                    id_vftx_z_2242.emplace_back(frs->primary_z * sqrt(de[0] / id_vftx_vcor_2242.at(i)));
                    id_vftx_z2_2242.emplace_back(frs->primary_z * sqrt(de[1] / id_vftx_vcor_2242.at(i)));
                }
            }

        }
    } // if vftx has data??
    
    /*----------------------------------------------------------*/
    /* End of VFTX  */
    /*----------------------------------------------------------*/


    //c4LOG(info,"EXEC BETA CALC");
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

    //c4LOG(info,"EXEC BROO");
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

    //c4LOG(info,"EXEC A/Q");
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

            // this is not done in FRS Go4, and in DESPEC Go4 I can't understand where "ts_mins" comes from?
            // is it just WR in minutes somehow? 
            // why don't FRS GainMatch?
            if (id_AoQ_corr > 0)
            {
                for (int i = 0; i < AoQ_Shift_array; i++)
                {
                    if (ts_mins >= FRS_WR_i[i] && ts_mins < FRS_WR_j[i])
                    {
                        if (id->x_s2_select == 2)
                        {
                            id_AoQ = id_AoQ - AoQ_shift_Sci21_value[i];
                            id_AoQ_corr = id_AoQ_corr - AoQ_shift_Sci21_value[i];
                        }
                        else if (id->x_s2_select == 3)
                        {
                            id_AoQ = id_AoQ - AoQ_shift_Sci22_value[i];
                            id_AoQ_corr = id_AoQ_corr - AoQ_shift_Sci22_value[i];
                        }
                        else
                        {
                            id_AoQ = id_AoQ - AoQ_shift_TPC_value[i];
                            id_AoQ_corr = id_AoQ_corr - AoQ_shift_TPC_value[i];
                        }
                    }
                }
            }

            id_b_AoQ = true;
        }
    }

    //c4LOG(info,"EXEC ZZ");
    /*------------------------------------------------*/
    /* Determination of Z                             */
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
            id_b_z2 = kTRUE;
        }
    }
    
    // Gain match Z -- unclear where ts_mins comes from
    for (int i = 0; i < Z_Shift_array; i++)
    {
        if (ts_mins >= FRS_WR_a[i] && ts_mins < FRS_WR_b[i])
        {
            id_z = id_z - Z1_shift_value[i];
            id_z2 = id_z2 - Z2_shift_value[i];
        }
    }

    // S4 (MUSIC)
    /*
    if ((de[2] > 0.0) && (id_beta > 0.0) && (id_beta < 1.0))
    {
        power = 1.0;
        sum = 0.;
        for (int i = 0; i < 4; i++)
        {
            sum += power * id->vel_a3[i];
            power *= id_beta;
        }
        id_v_cor3 = sum;
        if (id_v_cor3 > 0.0)
        {
            id_z3 = frs->primary_z * sqrt(de[2] / id_v_cor3) + id->offset_z3;
        }
        if ((id_z3 > 0.0) && (id_z3 < 100.0))
        {
            id_b_z3 = kTRUE;
        }
    }
    */
    //c4LOG(info,"Finalize:");
    // non mhtdc version?


    if (id_b_AoQ != false && id_b_x2 != false && id_b_z != false)
    {   
        float gamma1square = 1.0 + TMath::Power(((1 / aoq_factor) * (id_brho[0] / id_AoQ)), 2);
        id_gamma_ta_s2 = TMath::Sqrt(gamma1square);
        id_dEdegoQ = (id_gamma_ta_s2 - id_gamma) * id_AoQ;
        id_dEdeg = id_dEdegoQ * id_z;

        new ((*fHitArray)[fHitArray->GetEntriesFast()]) FrsHitData(
            WR_TS,
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
            ibin_clean_for_spill,
            de,
            sci_e,
            sci_l,
            sci_r,
            id_x2,
            id_y2,
            id_a2,
            id_b2,
            id_x4,
            id_y4,
            id_a4,
            id_b4,
            id_AoQ,
            id_AoQ_corr,
            id_z,
            id_z2,
            id_beta,
            id_dEdegoQ,
            id_dEdeg
        );
   
    }
    // above is end of FRS_Anl

   
}


void FrsCal2Hit::Setup_Conditions(TString path_to_folder_with_frs_config_files)
{
    std::string line;
    int line_number = 0;

    const char* format = "%f %f %f %f %f %f %f %f %f %f %f %f %f %f";

    std::ifstream cond_a(path_to_folder_with_frs_config_files +  TString("lim_csum.txt"));

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

    std::ifstream cond_b(path_to_folder_with_frs_config_files +  TString("lim_xsum.txt"));

    while(/*cond_b.good()*/getline(cond_b,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&lim_xsum[line_number][0],&lim_xsum[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f";

    std::ifstream cond_c(path_to_folder_with_frs_config_files +  TString("lim_ysum.txt"));

    while(/*cond_c.good()*/getline(cond_c,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&lim_ysum[line_number][0],&lim_ysum[line_number][1]);

        line_number++;
    }

    /*** MUSIC Conditions *** */

    line_number = 0;

    format = "%f %f %f %f";

    std::ifstream cond_d(path_to_folder_with_frs_config_files +  TString("MUSIC1.txt"));

    while(/*cond_d.good()*/getline(cond_d,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic1_E[line_number][0],&cMusic1_E[line_number][1],&cMusic1_T[line_number][0],&cMusic1_T[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f %f %f";

    std::ifstream cond_e(path_to_folder_with_frs_config_files +  TString("MUSIC2.txt"));

    while(/*cond_e.good()*/getline(cond_e,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic2_E[line_number][0],&cMusic2_E[line_number][1],&cMusic2_T[line_number][0],&cMusic2_T[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f %f %f";

    std::ifstream cond_f(path_to_folder_with_frs_config_files +  TString("MUSIC3.txt"));

    while(/*cond_f.good()*/getline(cond_f,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic3_E[line_number][0],&cMusic3_E[line_number][1],&cMusic3_T[line_number][0],&cMusic3_T[line_number][1]);

        line_number++;
    }


    line_number = 0;

    format = "%f %f";

    std::ifstream cond_g(path_to_folder_with_frs_config_files +  TString("MUSIC_dEc3.txt"));

    while(/*cond_g.good()*/getline(cond_g,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic3_dec[0],&cMusic3_dec[1]);
    }

    /***SCINTILATOR Condtions***/

    line_number = 0;

    format = "%f %f";

    std::ifstream cond_h(path_to_folder_with_frs_config_files +  TString("SCI_Cons.txt"));

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

    std::ifstream cond_i(path_to_folder_with_frs_config_files +  TString("SCI_LLRR.txt"));
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

    std::ifstream cond_k(path_to_folder_with_frs_config_files +  TString("ID_x2.txt"));


    while(/*cond_k.good()*/getline(cond_k,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cID_x2[0],&cID_x2[1]);
    }

    std::ifstream cond_l(path_to_folder_with_frs_config_files +  TString("ID_x4.txt"));

    while(/*cond_l.good()*/getline(cond_l,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cID_x4[0],&cID_x4[1]);
    }

    std::ifstream cond_m(path_to_folder_with_frs_config_files +  TString("ID_Z_Z.txt"));

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
    
    file.open("../../config/frs/Z1_Z2_Shift.txt");
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

    file.open("../../config/frs/AoQ_Shift.txt");
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
    fHitArray->Clear();
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
    ZeroArrays();
    ZeroVariables();
    ClearVectors();
}

void FrsCal2Hit::FinishTask()
{
    c4LOG(info, Form("Wrote %i events. ", fNEvents));
}

ClassImp(FrsCal2Hit)