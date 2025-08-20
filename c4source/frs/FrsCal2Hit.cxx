/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                             C.E. Jones                                     *
 *                              17.12.24                                      *
 ******************************************************************************/

#include "FrsCal2Hit.h"
#include "c4Logger.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "FairTask.h"
#include "GainShift.h"


#include "TClonesArray.h"
#include "TMath.h"
#include <TMacro.h>
#include <vector>
#include <iostream>
#include <TROOT.h>
#include <chrono>

#define MUSIC_ANA_NEW
#define MUSIC_BETA2 // DEFINED = 1/beta^2, NOT DEFINED = beta
#define TIME_FROM_1MHZ
#define TIME_FROM_100KHZ

FrsCal2Hit::FrsCal2Hit()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   tpatArray(nullptr)   
    ,   scalerArray(nullptr)
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
    ,   tpatArray(nullptr)
    ,   scalerArray(nullptr)
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

    tpatArray = mgr->InitObjectAs<decltype(tpatArray)>("FrsTpatData");
    c4LOG_IF(fatal, !tpatArray, "Branch FrsTpatData not found!");
    scalerArray = mgr->InitObjectAs<decltype(scalerArray)>("FrsScalerData");
    c4LOG_IF(fatal, !scalerArray, "Branch FrsScalerData not found!");
    calSciArray = mgr->InitObjectAs<decltype(calSciArray)>("FrsCalSciData");
    c4LOG_IF(fatal, !calSciArray, "Branch FrsCalSciData not found!");
    calMusicArray = mgr->InitObjectAs<decltype(calMusicArray)>("FrsCalMusicData");
    c4LOG_IF(fatal, !calMusicArray, "Branch FrsCalMusicData not found!");
    calTpcArray = mgr->InitObjectAs<decltype(calTpcArray)>("FrsCalTpcData");
    c4LOG_IF(fatal, !calTpcArray, "Branch FrsCalTpcData not found!");

    mgr->RegisterAny("FrsHitData", hitArray, !fOnline);
    mgr->RegisterAny("FrsMultiHitData", multihitArray, !fOnline);

   
    return kSUCCESS;
}

// :::: Main Execution Block ::: //
void FrsCal2Hit::Exec(Option_t* option)
{   
    //c4LOG(info," ::: Start event :::");
    if (tpatArray->size() == 0) return;
    fNEvents++;

    auto start = std::chrono::high_resolution_clock::now();
    
    // meta item/meta array better name? 
    auto const & tpatItem = tpatArray->at(0);
    wr_t = tpatItem.Get_wr_t();
    tpat = tpatItem.Get_tpat();
    travmus_wr_t = tpatItem.Get_travmus_wr_t();

    auto & anaEntry = hitArray->emplace_back();
    anaEntry.SetMetaData(wr_t, tpat, "", travmus_wr_t);

    ProcessScalers();
    anaEntry.SetScalerData(time_in_ms,
                        time_in_us,
                        ibin_for_s,
                        ibin_for_100ms,
                        ibin_for_spill,
                        ibin_clean_for_s,
                        ibin_clean_for_100ms,
                        ibin_clean_for_spill,
                        extraction_time_ms,
                        increase_scaler_temp);
    
    ProcessSci_TAC();

    anaEntry.SetSciData(sci_e_11,
                        sci_x_11,
                        sci_e_21,
                        sci_x_21,
                        sci_e_22,
                        sci_x_22,
                        sci_e_31,
                        sci_e_41,
                        sci_x_41,
                        sci_e_42,
                        sci_x_42,
                        sci_e_43,
                        sci_x_43,
                        sci_e_81,
                        sci_x_81,
                        sci_tof_11_21,
                        sci_tof_11_21_calib,
                        sci_tof_21_41, // 2
                        sci_tof_21_41_calib,
                        sci_tof_21_42, // 3
                        sci_tof_21_42_calib,
                        sci_tof_21_81, // 4
                        sci_tof_21_81_calib,
                        sci_tof_22_41, // 5
                        sci_tof_22_41_calib,
                        sci_tof_22_81, // 6
                        sci_tof_22_81_calib);

    ProcessMusic();
    anaEntry.SetMusicData(music21_de,
                        music22_de,
                        music41_de,
                        music42_de,
                        music43_de,
                        music21_de_cor,
                        music22_de_cor,
                        music41_de_cor,
                        music42_de_cor,
                        music43_de_cor);

    
    auto const & calTpcItem = calTpcArray->at(0);
    Float_t* tpc_x = const_cast<Float_t*>(calTpcItem.Get_tpc_x());
    Bool_t* b_tpc_xy_cp = const_cast<Bool_t*>(calTpcItem.Get_b_tpc_xy());
    Int_t (*tpc_csum)[4] = const_cast<Int_t (*)[4]>(calTpcItem.Get_tpc_csum());
    anaEntry.SetTPCData(tpc_x,
        b_tpc_xy_cp,
        tpc_csum,
        calTpcItem.Get_tpc_x_s2_foc_21_22(),
        calTpcItem.Get_tpc_y_s2_foc_21_22(),
        calTpcItem.Get_tpc_angle_x_s2_foc_21_22(),
        calTpcItem.Get_tpc_angle_y_s2_foc_21_22(),
        calTpcItem.Get_tpc_x_s2_foc_22_24(),
        calTpcItem.Get_tpc_y_s2_foc_22_24(),
        calTpcItem.Get_tpc_angle_x_s2_foc_22_24(),
        calTpcItem.Get_tpc_angle_y_s2_foc_22_24(),
        calTpcItem.Get_tpc_x_s2_foc_23_24(),
        calTpcItem.Get_tpc_y_s2_foc_23_24(),
        calTpcItem.Get_tpc_angle_x_s2_foc_23_24(),
        calTpcItem.Get_tpc_angle_y_s2_foc_23_24(),
        calTpcItem.Get_tpc_angle_x_s4(),
        calTpcItem.Get_tpc_angle_y_s4(),
        calTpcItem.Get_tpc_x_s4(),
        calTpcItem.Get_tpc_y_s4(),
        calTpcItem.Get_tpc23_24_sc21_y(),
        calTpcItem.Get_tpc23_24_sc22_y(),
        calTpcItem.Get_tpc_sc41_x(),
        calTpcItem.Get_tpc_sc41_y(),
        calTpcItem.Get_tpc_sc42_x(),
        calTpcItem.Get_tpc_sc42_y(),
        calTpcItem.Get_tpc_sc43_x(),
        calTpcItem.Get_tpc21_22_sc21_x(),
        calTpcItem.Get_tpc23_24_sc21_x(),
        calTpcItem.Get_tpc21_22_sc22_x(),
        calTpcItem.Get_tpc23_24_sc22_x(),
        calTpcItem.Get_tpc21_22_music21_x(),
        calTpcItem.Get_tpc21_22_music21_y(),
        calTpcItem.Get_tpc21_22_music22_x(),
        calTpcItem.Get_tpc21_22_music22_y(),
        calTpcItem.Get_tpc23_24_music21_x(),
        calTpcItem.Get_tpc23_24_music21_y(),
        calTpcItem.Get_tpc23_24_music22_x(),
        calTpcItem.Get_tpc23_24_music22_y(),
        calTpcItem.Get_tpc22_24_music21_x(),
        calTpcItem.Get_tpc22_24_music21_y(),
        calTpcItem.Get_tpc22_24_music22_x(),
        calTpcItem.Get_tpc22_24_music22_y(),
        calTpcItem.Get_tpc_music41_x(),
        calTpcItem.Get_tpc_music42_x(),
        calTpcItem.Get_tpc_music43_x(),
        calTpcItem.Get_tpc_angle_x_s2_foc_22_23(),
        calTpcItem.Get_tpc_angle_y_s2_foc_22_23(),
        calTpcItem.Get_tpc_x_s2_foc_22_23(),
        calTpcItem.Get_tpc_y_s2_foc_22_23());

    ProcessIDs();
    anaEntry.SetIDs(id_x1,
                    id_y1,
                    id_a1,
                    id_b1,
                    id_x2,
                    id_y2,
                    id_x4,
                    id_y4,
                    id_a2,
                    id_b2,
                    id_a4,
                    id_b4,
                    id_beta_s1s2,
                    id_AoQ_s1s2,
                    id_AoQ_corr_s1s2,
                    id_z21,
                    id_z22,
                    id_beta_s2s4,
                    id_AoQ_s2s4,
                    id_AoQ_corr_s2s4,
                    id_z41,
                    id_z42,
                    id_z43,
                    id_dEdegoQ,
                    id_dEdeg_z41,
                    id_rho,
                    id_brho);

    FRS_time_mins = (wr_t - exp_config->exp_start_time) / 60E9;
    ProcessDriftCorrections();
    anaEntry.SetDriftCorrections(FRS_time_mins, 
                                id_AoQs1s2_driftcorr,
                                id_AoQs2s4_driftcorr,
                                id_z21_driftcorr,
                                id_z22_driftcorr,
                                id_z41_driftcorr,
                                id_z42_driftcorr,
                                id_z43_driftcorr);
    
    ProcessSci_MHTDC();
    ProcessIDs_MHTDC();    
        
    
    // for (int i = 0; i < hits_in_s2x; i++)
    // {
    //     for (int j = 0; j < hits_in_s1x; j++)
    //     {
    //         int count = i * hits_in_s1x + j;
    //         s1x_mhtdc.emplace_back(temp_s1x_mhtdc[j]);
    //         s1a_mhtdc.emplace_back(temp_a1);
    //         s2x_s1s2_mhtdc.emplace_back(temp_s2x_mhtdc[i]);
    //         s2a_s1s2_mhtdc.emplace_back(temp_a2);
    //         tof_s1s2_mhtdc.emplace_back(id_mhtdc_tof_s1s2[count]);
    //         beta_s1s2_mhtdc.emplace_back(id_mhtdc_beta_s1s2[count]);
    //         aoq_s1s2_mhtdc.emplace_back(id_mhtdc_aoq_s1s2[count]);
    //         aoq_corr_s1s2_mhtdc.emplace_back(id_mhtdc_aoq_corr_s1s2[count]);
    //         z_music21_mhtdc.emplace_back(id_mhtdc_z_music21[count]);
    //         z_music22_mhtdc.emplace_back(id_mhtdc_z_music22[count]);

    //     }
    // }

    auto & multihitEntry = multihitArray->emplace_back();
    multihitEntry.SetS1S2(s1x_mhtdc,
                        s1a_mhtdc,
                        s2x_s1s2_mhtdc,
                        s2a_s1s2_mhtdc,
                        id_mhtdc_tof_s1s2,
                        id_mhtdc_beta_s1s2,
                        id_mhtdc_aoq_s1s2,
                        id_mhtdc_aoq_corr_s1s2,
                        id_mhtdc_z_music21,
                        id_mhtdc_z_music22); // CEJ  FIX

    multihitEntry.SetTOFs1s2Full(mhtdc_tof2111);

    // auto & multihitEntry = multihitArray->emplace_back();
    // multihitEntry.SetS1S2(s1x_mhtdc,
    //                     s1a_mhtdc,
    //                     s2x_s1s2_mhtdc,
    //                     s2a_s1s2_mhtdc,
    //                     tof_s1s2_mhtdc,
    //                     beta_s1s2_mhtdc,
    //                     aoq_s1s2_mhtdc,
    //                     aoq_corr_s1s2_mhtdc,
    //                     z_music21_mhtdc,
    //                     z_music22_mhtdc);

    // for (int i = 0; i < hits_in_s4x; i++)
    // {
    //     for (int j = 0; j < hits_in_s2x; j++)
    //     {
    //         int count = i * hits_in_s2x + j;
    //         s2x_s2s4_mhtdc.emplace_back(temp_s2x_mhtdc[j]);
    //         s2a_s2s4_mhtdc.emplace_back(temp_a2);
    //         s4x_mhtdc.emplace_back(temp_s4x_mhtdc[i]);
    //         s4a_mhtdc.emplace_back(temp_a4);
    //         tof_s2s4_mhtdc.emplace_back(id_mhtdc_tof_s2s4[count]);
    //         beta_s2s4_mhtdc.emplace_back(id_mhtdc_beta_s2s4[count]);
    //         aoq_s2s4_mhtdc.emplace_back(id_mhtdc_aoq_s2s4[count]);
    //         aoq_corr_s2s4_mhtdc.emplace_back(id_mhtdc_aoq_corr_s2s4[count]);
    //         z_music41_mhtdc.emplace_back(id_mhtdc_z_music41[count]);
    //         z_music42_mhtdc.emplace_back(id_mhtdc_z_music42[count]);
    //         z_music43_mhtdc.emplace_back(id_mhtdc_z_music43[count]);
    //         dEdegoQ_s2s4_mhtdc.emplace_back(id_mhtdc_dEdegoQ_s2s4[count]);
    //         dEdeg_z41_mhtdc.emplace_back(id_mhtdc_dEdeg_z41[count]);
    //     }
    // }

    //if (hits_in_s4x_tofs2s4_selected * hits_in_s2x_tofs2s4_selected > 0) aoqfrscal++;

    multihitEntry.SetS2S4(s2x_s2s4_mhtdc,
                        s2a_s2s4_mhtdc,
                        s4x_mhtdc,
                        s4a_mhtdc,
                        id_mhtdc_tof_s2s4,
                        id_mhtdc_beta_s2s4,
                        id_mhtdc_aoq_s2s4,
                        id_mhtdc_aoq_corr_s2s4,
                        id_mhtdc_z_music41,
                        id_mhtdc_z_music42,
                        id_mhtdc_z_music43,
                        id_mhtdc_dEdegoQ_s2s4,
                        id_mhtdc_dEdeg_z41);

    multihitEntry.SetTOFs2s4Full(mhtdc_tof4121);

    // multihitEntry.SetS2S4(s2x_s2s4_mhtdc,
    //                     s2a_s2s4_mhtdc,
    //                     s4x_mhtdc,
    //                     s4a_mhtdc,
    //                     tof_s2s4_mhtdc,
    //                     beta_s2s4_mhtdc,
    //                     aoq_s2s4_mhtdc,
    //                     aoq_corr_s2s4_mhtdc,
    //                     z_music41_mhtdc,
    //                     z_music42_mhtdc,
    //                     z_music43_mhtdc,
    //                     dEdegoQ_s2s4_mhtdc,
    //                     dEdeg_z41_mhtdc);

 
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();

    //c4LOG(info," ::: End event :::");

}

// Adapated by CEJ from M.B. [FRS]
void FrsCal2Hit::ProcessScalers()
{
    if (tpat == 2)
    {
        tpat2_counter += 1;
        return;
    }

    for (auto const & scalerItem : *scalerArray)
    {
        scaler_current[scalerItem.Get_index()-1] = scalerItem.Get_scaler();
    }

    if (scaler_check_first_event == 1)
    {
        scaler_check_first_event = 0;

        scaler_temp_free_for_100s = 0;
        scaler_temp_accept_for_100s = 0;
        scaler_temp_SCI41L_for_100s = 0;
        scaler_temp_SCI42L_for_100s = 0;
        scaler_temp_SCI43L_for_100s = 0;
        scaler_temp_free_for_s = 0;
        scaler_temp_accept_for_s = 0;
        scaler_temp_SCI41L_for_s = 0;
        scaler_temp_SCI42L_for_s = 0;
        scaler_temp_SCI43L_for_s = 0;
        scaler_temp_free_for_100ms = 0;
        scaler_temp_accept_for_100ms = 0;
        scaler_temp_SCI41L_for_100ms = 0;
        scaler_temp_SCI42L_for_100ms = 0;
        scaler_temp_SCI43L_for_100ms = 0;
        scaler_temp_free_for_spill = 0;
        scaler_temp_accept_for_spill = 0;
        scaler_temp_SCI41L_for_spill = 0;
        scaler_temp_SCI42L_for_spill = 0;
        scaler_temp_SCI43L_for_spill = 0;

        time_in_ms = 0.;
        time_in_us = 0.;

        memcpy(scaler_previous, scaler_current, 67 * sizeof(UInt_t));
        return;
    }

    // Increment Scalers from previous event
    #define SCALER_DATA_LENGTH 26
    #define WRAP_VALUE (1ll << (SCALER_DATA_LENGTH))
    #define INVALID_INCREMENT 0xafffffff

    memset(scaler_increment_calculated, 1, sizeof(scaler_increment_calculated));
    bool is_ok = true;

    for (int n = 0; n < 64; n++)
    {
        int64_t temp = (int64_t)scaler_current[n] - (int64_t)scaler_previous[n];
        scaler_increment[n] = (uint32_t)temp;

        if (temp < 0)
        {
            if (std::abs(temp) > WRAP_VALUE / 2)
            {
                scaler_increment[n] = (uint32_t)(WRAP_VALUE + temp);
            }
            else
            {
                scaler_increment[n] = INVALID_INCREMENT;
                scaler_increment_calculated[n] = false;
                is_ok = false;
            }
        }

        if (scaler_increment_calculated[n])
        {
            scaler_cumulative[n] += (uint64_t)scaler_increment[n];
        }
    }

    memcpy(scaler_previous, scaler_current, 67 * sizeof(UInt_t));

    double _roll = std::rand() / (double)RAND_MAX;

    // CEJ: change to TFrsConfig definition, to change from macro
    #if defined(TIME_FROM1MHZ)
    time_in_ms = ((double)scaler_cumulative[scaler_ch_1000kHz] + _roll) / 1e3;
    time_in_us = (double)scaler_cumulative[scaler_ch_1000kHz] + _roll;
    #elif defined(TIME_FROM_100KHZ)
    time_in_ms = ((double)scaler_cumulative[scaler_ch_1000kHz] + _roll) / 1e2;
    time_in_us = (double)scaler_cumulative[scaler_ch_1000kHz] + _roll * 1e1;
    #else
    time_in_ms = ((double)scaler_cumulative[scaler_ch_1000kHz] + _roll);
    time_in_us = (double)scaler_cumulative[scaler_ch_1000kHz] + _roll * 1e3;
    #endif

    int spill_count = 0;
    spill_count = scaler_cumulative[scaler_ch_spillstart];

    ibin_for_100s = ((int)(time_in_ms / 1000 /100) % 50) + 1;
    ibin_for_s = ((int)(time_in_ms / 1000) % 1000) + 1;
    ibin_for_100ms = ((int)(time_in_ms / 100) % 4000) + 1;
    ibin_for_spill = (spill_count % 1000) + 1;
    extraction_time_ms += (int)time_in_ms;

    ibin_clean_for_100s = (((int)(time_in_ms / 1000 /100) +20) % 50) + 1;
    ibin_clean_for_s = (((int)(time_in_ms / 1000) +20) % 1000) + 1;
    ibin_clean_for_100ms = ((int)((time_in_ms / 100) +200 ) % 4000) + 1;
    ibin_clean_for_spill = ((spill_count + 990 )% 20) + 1;

    ibin_for_100s_previous = ibin_for_100s;
    ibin_for_s_previous = ibin_for_s;
    ibin_for_100ms_previous = ibin_for_100ms;
    ibin_for_spill_previous = ibin_for_spill;

    if (scaler_current[scaler_ch_spillstart] - scaler_previous[scaler_ch_spillstart] != 0)
    {
        extraction_time_ms = 0;
    }

    for (int n = 0; n < 64; n++) 
    {
        increase_scaler_temp[n] = scaler_increment[n];
        if (n == 33) increase_scaler_temp[n] -= tpat2_counter;
    }

    Int_t increase_scaler_temp_free = 0;
    Int_t increase_scaler_temp_accept = 0.;
	Int_t increase_scaler_temp_SCI41L = 0.;
	Int_t increase_scaler_temp_SCI42L = 0.;
	Int_t increase_scaler_temp_SCI43L = 0.;
    increase_scaler_temp_free = scaler_increment[32]; 
    increase_scaler_temp_accept = scaler_increment[33] - tpat2_counter;
    
    tpat2_counter = 0;
    // mapping??
    increase_scaler_temp_SCI41L = scaler_increment[49]; 
	increase_scaler_temp_SCI42L = scaler_increment[50];
	increase_scaler_temp_SCI43L = scaler_increment[51];

    if (ibin_for_100s == ibin_for_100s_previous)
    {
        scaler_temp_free_for_100s = scaler_temp_free_for_100s + increase_scaler_temp_free;
        scaler_temp_accept_for_100s = scaler_temp_accept_for_100s + increase_scaler_temp_accept;
        scaler_temp_SCI41L_for_100s = scaler_temp_SCI41L_for_100s + increase_scaler_temp_SCI41L;
        scaler_temp_SCI42L_for_100s = scaler_temp_SCI42L_for_100s + increase_scaler_temp_SCI42L;
        scaler_temp_SCI43L_for_100s = scaler_temp_SCI43L_for_100s + increase_scaler_temp_SCI43L;

        if (scaler_temp_free_for_100s != 0)
        {
            ratio_product_for_100s = (int)(100 * (scaler_temp_accept_for_100s * (1 / scaler_temp_free_for_100s)));
        }
        else
        {
            if (scaler_temp_accept_for_100s == 0)
            {
                ratio_product_for_100s = 100;
            }
        }
        if (scaler_temp_SCI41L_for_100s != 0)
        {
            ratio_product2_for_100s = (int)(100 * (scaler_temp_SCI42L_for_100s * (1 / scaler_temp_SCI41L_for_100s)));
            ratio_product3_for_100s = (int)(100 * (scaler_temp_SCI43L_for_100s * (1 / scaler_temp_SCI41L_for_100s)));
        }
        else
        {
            if (scaler_temp_SCI42L_for_100s == 0)
            {
                ratio_product2_for_100s = 100;
            }
            if (scaler_temp_SCI43L_for_100s == 0)
            {
                ratio_product3_for_100s = 100;
            }
        }
    }
    else
    {
        scaler_temp_free_for_100s = increase_scaler_temp_free;
        scaler_temp_accept_for_100s = increase_scaler_temp_accept;
        scaler_temp_SCI41L_for_100s = increase_scaler_temp_SCI41L;
        scaler_temp_SCI42L_for_100s = increase_scaler_temp_SCI42L;
        scaler_temp_SCI43L_for_100s = increase_scaler_temp_SCI43L;
        
        if (scaler_temp_free_for_100s != 0)
        {
            ratio_product_for_100s = (int)(100 * (scaler_temp_accept_for_100s * (1./scaler_temp_free_for_100s)));	    
        }
        else
        {
            if (scaler_temp_accept_for_100s == 0)
            {
                ratio_product_for_100s = 100;
            }
        }
        if (scaler_temp_SCI41L_for_100s != 0)
        {
            ratio_product2_for_100s = (int)(100 * (scaler_temp_SCI42L_for_100s * (1 / scaler_temp_SCI41L_for_100s)));
            ratio_product3_for_100s = (int)(100 * (scaler_temp_SCI43L_for_100s * (1 / scaler_temp_SCI41L_for_100s)));
        }
        else
        {
            if (scaler_temp_SCI42L_for_100s == 0)
            {
                ratio_product2_for_100s = 100;
            }
            if (scaler_temp_SCI43L_for_100s == 0)
            {
                ratio_product3_for_100s = 100;
            }
        }
    }

    if (ibin_for_s==ibin_for_s_previous)
    {
        scaler_temp_free_for_s = scaler_temp_free_for_s + increase_scaler_temp_free;
        scaler_temp_accept_for_s = scaler_temp_accept_for_s + increase_scaler_temp_accept;
        scaler_temp_SCI41L_for_s = scaler_temp_SCI41L_for_s + increase_scaler_temp_SCI41L;
        scaler_temp_SCI42L_for_s = scaler_temp_SCI42L_for_s + increase_scaler_temp_SCI42L;
        scaler_temp_SCI43L_for_s = scaler_temp_SCI43L_for_s + increase_scaler_temp_SCI43L;
    
        if (scaler_temp_free_for_s != 0)
        {
            ratio_product_for_s = (int)(100 * (scaler_temp_accept_for_s * (1 / scaler_temp_free_for_s)));
        }
        else
        {
            if (scaler_temp_accept_for_s == 0)
            {   
                ratio_product_for_s = 100;
            }
        }
        if (scaler_temp_SCI41L_for_s != 0)
        {
            ratio_product2_for_s = (int)(100 * (scaler_temp_SCI42L_for_s * (1./scaler_temp_SCI41L_for_s)));
            ratio_product3_for_s = (int)(100 * (scaler_temp_SCI43L_for_s * (1./scaler_temp_SCI41L_for_s)));
        }
        else
        {
            if (scaler_temp_SCI42L_for_s == 0)
            {
                ratio_product2_for_s = 100;
            }
            if (scaler_temp_SCI43L_for_s == 0)
            {
                ratio_product3_for_s = 100;
            }
        }
    }
    else
    {
        scaler_temp_free_for_s = increase_scaler_temp_free;
        scaler_temp_accept_for_s = increase_scaler_temp_accept;
        scaler_temp_SCI41L_for_s = increase_scaler_temp_SCI41L;
        scaler_temp_SCI42L_for_s = increase_scaler_temp_SCI42L;
        scaler_temp_SCI43L_for_s = increase_scaler_temp_SCI43L;
        if(scaler_temp_free_for_s != 0)
        {
            ratio_product_for_s = (int)(100 * (scaler_temp_accept_for_s * (1 / scaler_temp_free_for_s)));	    
        }
        else
        {
            if (scaler_temp_accept_for_s == 0)
            {
                ratio_product_for_s = 100;
            }
        }
        if (scaler_temp_SCI41L_for_s != 0)
        {
            ratio_product2_for_s = (int)(100 * (scaler_temp_SCI42L_for_s * (1 / scaler_temp_SCI41L_for_s)));
            ratio_product3_for_s = (int)(100 * (scaler_temp_SCI43L_for_s * (1 / scaler_temp_SCI41L_for_s)));
        }
        else
        {
            if (scaler_temp_SCI42L_for_s == 0)
            {
                ratio_product2_for_s = 100;
            }
            if (scaler_temp_SCI43L_for_s == 0)
            {
                ratio_product3_for_s = 100;
            }
        }
	}
	
	if (ibin_for_100ms == ibin_for_100ms_previous)
    {
        scaler_temp_free_for_100ms = scaler_temp_free_for_100ms + increase_scaler_temp_free;
        scaler_temp_accept_for_100ms = scaler_temp_accept_for_100ms + increase_scaler_temp_accept;  
        scaler_temp_SCI41L_for_100ms = scaler_temp_SCI41L_for_100ms + increase_scaler_temp_SCI41L;
        scaler_temp_SCI42L_for_100ms = scaler_temp_SCI42L_for_100ms + increase_scaler_temp_SCI42L;
        scaler_temp_SCI43L_for_100ms = scaler_temp_SCI43L_for_100ms + increase_scaler_temp_SCI43L;
        if (scaler_temp_free_for_100ms != 0)
        {
            ratio_product_for_100ms = (int)(100 * (scaler_temp_accept_for_100ms * (1 / scaler_temp_free_for_100ms)));
        }
        else
        {
            if (scaler_temp_accept_for_100ms == 0)
            {
                ratio_product_for_100ms = 100;
            }
        }
        if (scaler_temp_SCI41L_for_100ms != 0)
        {
            ratio_product2_for_100ms = (int)(100 * (scaler_temp_SCI42L_for_100ms * (1 / scaler_temp_SCI41L_for_100ms)));
            ratio_product3_for_100ms = (int)(100 * (scaler_temp_SCI43L_for_100ms * (1 / scaler_temp_SCI41L_for_100ms)));
        }
        else
        {
            if (scaler_temp_SCI42L_for_100ms == 0)
            {
                ratio_product2_for_100ms = 100;
            }
            if (scaler_temp_SCI43L_for_100ms == 0)
            {
                ratio_product3_for_100ms = 100;
            }
        }
    }
    else
    {
        scaler_temp_free_for_100ms = increase_scaler_temp_free;
        scaler_temp_accept_for_100ms = increase_scaler_temp_accept;
        scaler_temp_SCI41L_for_100ms = increase_scaler_temp_SCI41L;
        scaler_temp_SCI42L_for_100ms = increase_scaler_temp_SCI42L;
        scaler_temp_SCI43L_for_100ms = increase_scaler_temp_SCI43L;
        
        if(scaler_temp_free_for_100ms != 0)
        {
            ratio_product_for_100ms = (int)(100 * (scaler_temp_accept_for_100ms * (1 / scaler_temp_free_for_100ms)));
        }
        else
        {
            if(scaler_temp_accept_for_100ms == 0)
            {
                ratio_product_for_100ms = 100;
            }
        }
        if(scaler_temp_SCI41L_for_100ms != 0)
        {
            ratio_product2_for_100ms = (int)(100 * (scaler_temp_SCI42L_for_100ms * (1 / scaler_temp_SCI41L_for_100ms)));
            ratio_product3_for_100ms = (int)(100 * (scaler_temp_SCI43L_for_100ms * (1 / scaler_temp_SCI41L_for_100ms)));
        }
        else
        {
            if (scaler_temp_SCI42L_for_100ms == 0)
            {
                ratio_product2_for_100ms = 100;
            }
            if(scaler_temp_SCI43L_for_100ms == 0)
            {
                ratio_product3_for_100ms = 100;
            }
        }
	}

    return;

}

void FrsCal2Hit::ProcessSci_TAC()
{
    auto const & calSciItem = calSciArray->at(0);

    // SCI 11
    de_11l = calSciItem.Get_dE_11l(); bool sci_b_11l = ((de_11l > 0) && (de_11l < 4000));
    de_11r = calSciItem.Get_dE_11r(); bool sci_b_11r = ((de_11r > 0) && (de_11r < 4000));
    if (sci_b_11r && sci_b_11r) sci_e_11 = sqrt((de_11r - sci->le_a[0][1]) * sci->le_a[1][1] * (de_11r - sci->re_a[0][1]) * sci->re_a[1][1]);
    bool sci_b_e_11 = ((sci_e_11 > 0) && (sci_e_11 < 4000));

    sci_tx_11lr = calSciItem.Get_dT_11l_11r() + rand3();
    bool sci_b_tx_11lr = ((sci_tx_11lr > 200) && (sci_tx_11lr < 4000));
    if (sci_b_tx_11lr)
    {
        float R = sci_tx_11lr;
        float power = 1.; float sum = 0;
        for (int i = 0; i < 7; i++)
        {
            sum += sci->x_a[i][1] * power; power *= R;
        }
        sci_x_11 = sum;
    }
    sci_b_x_11 = ((sci_x_11 > -100) && (sci_x_11 < 100));



    // SCI 21
    de_21l = calSciItem.Get_dE_21l(); bool sci_b_21l = ((de_21l > 10) && (de_21l < 4000));
    de_21r = calSciItem.Get_dE_21r(); bool sci_b_21r = ((de_21r > 10) && (de_21r < 4000));
    if (sci_b_21l && sci_b_21r) sci_e_21 = sqrt((de_21l - sci->le_a[0][2]) * sci->le_a[1][2] * (de_21r - sci->re_a[0][2]) * sci->re_a[1][2]);
    bool sci_b_e_21 = ((sci_e_21 > 10) && (sci_e_21 < 4000));
    
    sci_tx_21lr = calSciItem.Get_dT_21l_21r() + rand3();
    bool sci_b_tx_21lr = ((sci_tx_21lr > 200) && (sci_tx_21lr < 4000));
    if (sci_b_tx_21lr)
    {
        float R = sci_tx_21lr;
        float power = 1.; float sum = 0.;
        for (int i = 0; i < 7; i++)
        {
            sum += sci->x_a[i][2] * power; power *= R;
        }
        sci_x_21 = sum;
    }
    sci_b_x_21 = ((sci_x_21 > -100) && (sci_x_21 < 100));

    // SCI 22
    de_22l = calSciItem.Get_dE_22l(); bool sci_b_22l = ((de_22l > 10) && (de_22l < 4000));
    de_22r = calSciItem.Get_dE_22r(); bool sci_b_22r = ((de_22r > 10) && (de_22r < 4000));
    if (sci_b_22l && sci_b_22r) sci_e_22 = sqrt((de_22l - sci->le_a[0][3]) * sci->le_a[1][3] * (de_22r - sci->re_a[0][3]) * sci->re_a[1][3]);
    bool sci_b_e_22 = ((sci_e_22 > 10) && (sci_e_22 < 4000));
    
    sci_tx_22lr = calSciItem.Get_dT_22l_22r() + rand3();
    bool sci_b_tx_22lr = ((sci_tx_22lr > 200) && (sci_tx_22lr < 4000));
    if (sci_b_tx_22lr)
    {
        float R = sci_tx_22lr;
        float power = 1.; float sum = 0.;
        for (int i = 0; i < 7; i++)
        {
            sum += sci->x_a[i][3] * power; power *= R;
        }
        sci_x_22 = sum;
    }
    sci_b_x_22 = ((sci_x_22 > -100) && (sci_x_22 < 100));

    // SCI 31
    de_31l = calSciItem.Get_dE_31l(); bool sci_b_31l = ((de_31l > 10) && (de_31l < 4000));
    de_31r = calSciItem.Get_dE_31r(); bool sci_b_31r = ((de_31r > 10) && (de_31r < 4000));
    if (sci_b_31l && sci_b_31r) sci_e_31 = sqrt((de_31l - sci->le_a[0][4]) * sci->le_a[1][4] * (de_31r - sci->re_a[0][4]) * sci->re_a[1][4]);
    bool sci_b_e_31 = ((sci_e_31 > 10) && (sci_e_31 < 4000));

    // SCI 41
    de_41l = calSciItem.Get_dE_41l(); bool sci_b_41l = ((de_41l > 10) && (de_41l < 4000));
    de_41r = calSciItem.Get_dE_41r(); bool sci_b_41r = ((de_41r > 10) && (de_41r < 4000));
    if (sci_b_41l && sci_b_41r) sci_e_41 = sqrt((de_41l - sci->le_a[0][5]) * sci->le_a[1][5] * (de_41r - sci->re_a[0][5]) * sci->re_a[1][5]);
    bool sci_b_e_41 = ((sci_e_41 > 10) && (sci_e_41 < 4000));
    
    sci_tx_41lr = calSciItem.Get_dT_41l_41r() + rand3();
    bool sci_b_tx_41lr = ((sci_tx_41lr > 200) && (sci_tx_41lr < 4000));
    if (sci_b_tx_41lr)
    {
        float R = sci_tx_41lr;
        float power = 1.; float sum = 0.;
        for (int i = 0; i < 7; i++)
        {
            sum += sci->x_a[i][5] * power; power *= R;
        }
        sci_x_41 = sum;
    }
    sci_b_x_41 = ((sci_x_41 > -100) && (sci_x_41 < 100));

    // SCI 42
    de_42l = calSciItem.Get_dE_42l(); bool sci_b_42l = ((de_42l > 10) && (de_42l < 4000));
    de_42r = calSciItem.Get_dE_42r(); bool sci_b_42r = ((de_42r > 10) && (de_42r < 4000));
    if (sci_b_42l && sci_b_42r) sci_e_42 = sqrt((de_42l - sci->le_a[0][6]) * sci->le_a[1][6] * (de_42r - sci->re_a[0][6]) * sci->re_a[1][6]);
    bool sci_b_e_42 = ((sci_e_42 > 10) && (sci_e_42 < 4000));
    
    sci_tx_42lr = calSciItem.Get_dT_42l_42r() + rand3();
    bool sci_b_tx_42lr = ((sci_tx_42lr > 200) && (sci_tx_42lr < 4000));
    if (sci_b_tx_42lr)
    {
        float R = sci_tx_42lr;
        float power = 1.; float sum = 0.;
        for (int i = 0; i < 7; i++)
        {
            sum += sci->x_a[i][6] * power; power *= R;
        }
        sci_x_42 = sum;
    }
    sci_b_x_42 = ((sci_x_42 > -100) && (sci_x_42 < 100));

    // SCI 43
    de_43l = calSciItem.Get_dE_43l(); bool sci_b_43l = ((de_43l > 10) && (de_43l < 4000));
    de_43r = calSciItem.Get_dE_43r(); bool sci_b_43r = ((de_43r > 10) && (de_43r < 4000));
    if (sci_b_43l && sci_b_43r) sci_e_43 = sqrt((de_43l - sci->le_a[0][7]) * sci->le_a[1][7] * (de_43r - sci->re_a[0][7]) * sci->re_a[1][7]);
    bool sci_b_e_43 = ((sci_e_43 > 10) && (sci_e_43 < 4000));

    sci_tx_43lr = calSciItem.Get_dT_43l_43r() + rand3();
    bool sci_b_tx_43lr = ((sci_tx_43lr > 200) && (sci_tx_43lr < 4000));
    if (sci_b_tx_43lr)
    {
        float R = sci_tx_43lr;
        float power = 1.; float sum = 0.;
        for (int i = 0; i < 7; i++)
        {
            sum += sci->x_a[i][7] * power; power *= R;
        }
        sci_x_43 = sum;
    }
    sci_b_x_43 = ((sci_x_43 > -100) && (sci_x_43 < 100));

    // SCI 81
    de_81l = calSciItem.Get_dE_81l(); bool sci_b_81l = ((de_81l > 10) && (de_81l < 4000));
    de_81r = calSciItem.Get_dE_81r(); bool sci_b_81r = ((de_81r > 10) && (de_81r < 4000));
    if (sci_b_81l && sci_b_81r) sci_e_81 = sqrt((de_81l - sci->le_a[0][10]) * sci->le_a[1][10] * (de_81r - sci->re_a[0][10]) * sci->re_a[1][10]);
    bool sci_b_e_81 = ((sci_e_81 > 10) && (sci_e_81 < 4000));
    
    sci_tx_81lr = calSciItem.Get_dT_81l_81r() + rand3();
    bool sci_b_tx_81lr = ((sci_tx_81lr > 200) && (sci_tx_81lr < 4000));
    if (sci_b_tx_81lr)
    {
        float R = sci_tx_81lr;
        float power = 1.; float sum = 0.;
        for (int i = 0; i < 7; i++)
        {
            sum += sci->x_a[i][10] * power; power *= R;
        }
        sci_x_81 = sum;
    }
    sci_b_x_81 = ((sci_x_81 > -100) && (sci_x_81 < 100));


    /*-----------------------------------*/
    // Calibrated ToF - Todo: boundary conditions should be read in on expt basis
    /*-----------------------------------*/
    // SCI 11 - 21 ["1"] // 2025
    sci_tofll_11_21 = (float)calSciItem.Get_dT_11l_21l() * sci->tac_factor[9] - sci->tac_off[9];
    sci_tofrr_11_21 = (float)calSciItem.Get_dT_11r_21r() * sci->tac_factor[10] - sci->tac_off[10];
    sci_b_tofll_11_21 = ((sci_tofll_11_21 > 10000) && sci_tofll_11_21 < 200000);
    sci_b_tofrr_11_21 = ((sci_tofrr_11_21 > 10000) && sci_tofrr_11_21 < 200000);

    if (sci_b_tofll_11_21 && sci_b_tofrr_11_21)
    {
        // CEJ: seems to break using pareeksha setup file, may need to add to convert_setup.py script
        sci_tof_11_21 = (sci->tof_bll1 * sci_tofrr_11_21 + sci->tof_a1 + sci->tof_brr1 * sci_tofrr_11_21) / 2.0;
        sci_tof_11_21_calib = -1.0 * sci_tof_11_21 + id->id_tofoff1[sci->sci11_select];
    }
    else
    {
        sci_tof_11_21 = 0;
        sci_tof_11_21_calib = 0;
    }


    // SCI 21 - 41 ["2"]
    sci_tofll_21_41 = (float)calSciItem.Get_dT_21l_41l() * sci->tac_factor[2] - sci->tac_off[2];
    sci_tofrr_21_41 = (float)calSciItem.Get_dT_21r_41r() * sci->tac_factor[3] - sci->tac_off[3];
    sci_b_tofll_21_41 = ((sci_tofll_21_41 > 2000) && (sci_tofll_21_41 < 80000));
    sci_b_tofrr_21_41 = ((sci_tofrr_21_41 > 2500) && (sci_tofrr_21_41 < 80000));

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

    // SCI 21 - 42 ["3"]
    sci_tofll_21_42 = calSciItem.Get_dT_42l_21l() * sci->tac_factor[5] - sci->tac_off[5];
    sci_tofrr_21_42 = calSciItem.Get_dT_42r_21r() * sci->tac_factor[6] - sci->tac_off[6];
    sci_b_tofll_21_42 = ((sci_tofll_21_42 > 2500) && (sci_tofll_21_42 < 80000));
    sci_b_tofrr_21_42 = ((sci_tofrr_21_42 > 2500) && (sci_tofrr_21_42 < 80000));
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

    // SCI 21 - 81 ["4"]
    sci_tofll_21_81 = calSciItem.Get_dT_21l_81l() * sci->tac_factor[9] - sci->tac_off[9];
    sci_tofrr_21_81 = calSciItem.Get_dT_21r_81r() * sci->tac_factor[10] - sci->tac_off[10];
    bool sci_b_tofll_21_81 = ((sci_tofll_21_81 > 2500) && (sci_tofll_21_81 < 80000));
    bool sci_b_tofrr_21_81 = ((sci_tofrr_21_81 > 2500) && (sci_tofrr_21_81 < 80000));
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
    sci_tofll_22_41 = calSciItem.Get_dT_22l_41l() * sci->tac_factor[12] - sci->tac_off[12];
    sci_tofrr_22_41 = calSciItem.Get_dT_22r_41r() * sci->tac_factor[13] - sci->tac_off[13];
    sci_b_tofll_22_41 = ((sci_tofll_22_41 > 2500) && (sci_tofll_22_41 < 800000));
    sci_b_tofrr_22_41 = ((sci_tofrr_22_41 > 2500) && (sci_tofrr_22_41 < 800000));
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
    sci_tofll_22_81 = calSciItem.Get_dT_22l_81l() * sci->tac_factor[14] - sci->tac_off[14];
    sci_tofrr_22_81 = calSciItem.Get_dT_22r_81r() * sci->tac_factor[15] - sci->tac_off[15];
    bool sci_b_tofll_22_81 = ((sci_tofll_22_81 > 2500) && (sci_tofll_22_81 < 800000));
    bool sci_b_tofrr_22_81 = ((sci_tofrr_22_81 > 2500) && (sci_tofrr_22_81 < 800000));
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

}

void FrsCal2Hit::ProcessSci_MHTDC()
{
    auto const & calSciItem = calSciArray->at(0);
    auto const & calTpcItem = calTpcArray->at(0);
    b_tpc_xy = calTpcItem.Get_b_tpc_xy();

    // SCI 11 L and R - For Sc11 a "select" is used, there are 4 options?

    // here use the select.. 
    if (sci->sci11_select == 0) sci11l_hits = calSciItem.Get_mhtdc_sci11la_hits();
    else if (sci->sci11_select == 1) sci11l_hits = calSciItem.Get_mhtdc_sci11lb_hits();
    else if (sci->sci11_select == 2) sci11l_hits = calSciItem.Get_mhtdc_sci11lc_hits();
    else if (sci->sci11_select == 3) sci11l_hits = calSciItem.Get_mhtdc_sci11ld_hits();
    int hits_in_11l = sci11l_hits.size();
    
    if (sci->sci11_select == 0) sci11r_hits = calSciItem.Get_mhtdc_sci11ra_hits();
    else if (sci->sci11_select == 1) sci11r_hits = calSciItem.Get_mhtdc_sci11rb_hits();
    else if (sci->sci11_select == 2) sci11r_hits = calSciItem.Get_mhtdc_sci11rc_hits();
    else if (sci->sci11_select == 3) sci11r_hits = calSciItem.Get_mhtdc_sci11rd_hits();
    int hits_in_11r = sci11r_hits.size();

    if (sci->sci11_select == 0) mhtdc_sci11lr_dt = calSciItem.Get_mhtdc_dT_11la_11ra();
    else if (sci->sci11_select == 1) mhtdc_sci11lr_dt = calSciItem.Get_mhtdc_dT_11lb_11rb();
    else if (sci->sci11_select == 2) mhtdc_sci11lr_dt = calSciItem.Get_mhtdc_dT_11lc_11rc();
    else if (sci->sci11_select == 3) mhtdc_sci11lr_dt = calSciItem.Get_mhtdc_dT_11ld_11rd();
    
    if (sci->sci11_select == 0) mhtdc_sci11lr_x = calSciItem.Get_mhtdc_x_sci11lra();
    else if (sci->sci11_select == 1) mhtdc_sci11lr_x = calSciItem.Get_mhtdc_x_sci11lrb();
    else if (sci->sci11_select == 2) mhtdc_sci11lr_x = calSciItem.Get_mhtdc_x_sci11lrc();
    else if (sci->sci11_select == 3) mhtdc_sci11lr_x = calSciItem.Get_mhtdc_x_sci11lrd();

    for (int i = 0; i < hits_in_11l; i++)
    {
        for (int j = 0; j < hits_in_11r; j++)
        {
            double dt = mhtdc_sci11lr_dt[i * hits_in_11r + j];
            if (TMath::Abs(dt) < frs_config->fscilr_mhtdc_limit)
            {
                sci11l_hits_selected.emplace_back(sci11l_hits[i]);
                sci11r_hits_selected.emplace_back(sci11r_hits[j]);
                mhtdc_sci11lr_dt_selected.emplace_back(dt);
                mhtdc_sci11lr_x_selected.emplace_back(mhtdc_sci11lr_x[i * hits_in_11r + j]);
                hits_in_11lr_selected++;
            }
        }
    }
    hits_in_11l_selected = sci11l_hits_selected.size();
    hits_in_11r_selected = sci11r_hits_selected.size();
    
    // SCI 21 L and R
    //c4LOG(info,"SCI21 L R");
    sci21l_hits = calSciItem.Get_mhtdc_sci21l_hits();
    int hits_in_21l = sci21l_hits.size();
    sci21r_hits = calSciItem.Get_mhtdc_sci21r_hits();
    int hits_in_21r = sci21r_hits.size();
    mhtdc_sci21lr_dt = calSciItem.Get_mhtdc_dT_21l_21r();
    mhtdc_sci21lr_x = calSciItem.Get_mhtdc_x_sci21lr();

    mhtdc_sci21lr_dt_selected.clear();
    mhtdc_sci21lr_x_selected.clear();
    sci21l_hits_selected.clear();
    sci21r_hits_selected.clear();
    for (int i = 0; i < hits_in_21l; i++)
    {
        for (int j = 0; j < hits_in_21r; j++)
        {
            double dt = mhtdc_sci21lr_dt[i * hits_in_21r + j];
            if (TMath::Abs(dt) < frs_config->fscilr_mhtdc_limit) 
            {
                sci21l_hits_selected.emplace_back(sci21l_hits[i]);
                sci21r_hits_selected.emplace_back(sci21r_hits[j]);
                mhtdc_sci21lr_dt_selected.emplace_back(dt);
                mhtdc_sci21lr_x_selected.emplace_back(mhtdc_sci21lr_x[i * hits_in_21r + j]);
                hits_in_21lr_selected++;
            }
        }
    }
    hits_in_21l_selected = sci21l_hits_selected.size();
    hits_in_21r_selected = sci21r_hits_selected.size();   

    float sc21pos_from_tpc = -999.;
    if (b_tpc_xy[0] && b_tpc_xy[1])
    {
        sc21pos_from_tpc = calTpcItem.Get_tpc21_22_sc21_x();
    }
    else if (b_tpc_xy[2] && b_tpc_xy[3])
    {
        sc21pos_from_tpc = calTpcItem.Get_tpc23_24_sc21_x();
    }

    // SCI 22 L and R
    //7c4LOG(info,"SCI22 L R");
    sci22l_hits = calSciItem.Get_mhtdc_sci22l_hits();
    int hits_in_22l = sci22l_hits.size();
    sci22r_hits = calSciItem.Get_mhtdc_sci22r_hits();
    int hits_in_22r = sci22r_hits.size();
    mhtdc_sci22lr_dt = calSciItem.Get_mhtdc_dT_22l_22r();
    mhtdc_sci22lr_x = calSciItem.Get_mhtdc_x_sci22lr();

    mhtdc_sci22lr_dt_selected.clear();
    mhtdc_sci22lr_x_selected.clear();
    sci22l_hits_selected.clear();
    sci22r_hits_selected.clear();
    for (int i = 0; i < hits_in_22l; i++)
    {
        for (int j = 0; j < hits_in_22r; j++)
        {
            double dt = mhtdc_sci22lr_dt[i * hits_in_22r + j];
            if (TMath::Abs(dt) < frs_config->fscilr_mhtdc_limit) 
            {
                sci22l_hits_selected.emplace_back(sci22l_hits[i]);
                sci22r_hits_selected.emplace_back(sci22r_hits[j]);
                mhtdc_sci22lr_dt_selected.emplace_back(dt);
                mhtdc_sci22lr_x_selected.emplace_back(mhtdc_sci22lr_x[i * hits_in_22r + j]);
                hits_in_22lr_selected++;
            }
        }
        if (i == 0) //EG: ??
        {
            // only do this if there is a case for 22l and 22r != 0. we don't need to do it 10x though
            float sc22pos_from_tpc = -999.9;
            if (b_tpc_xy[0] && b_tpc_xy[1])
            {
                sc22pos_from_tpc = calTpcItem.Get_tpc21_22_sc22_x();
            }
            else if (b_tpc_xy[2] && b_tpc_xy[3])
            {
                sc22pos_from_tpc = calTpcItem.Get_tpc23_24_sc22_x();
            }
        }
    }
    hits_in_22l_selected = sci22l_hits_selected.size();
    hits_in_22r_selected = sci22r_hits_selected.size(); 

    // SCI 31 L and R
    //c4LOG(info,"SCI31 L R");
    sci31l_hits = calSciItem.Get_mhtdc_sci31l_hits();
    int hits_in_31l = sci31l_hits.size();
    sci31r_hits = calSciItem.Get_mhtdc_sci31r_hits();
    int hits_in_31r = sci31r_hits.size();
    mhtdc_sci31lr_dt = calSciItem.Get_mhtdc_dT_31l_31r();
    mhtdc_sci31lr_x = calSciItem.Get_mhtdc_x_sci31lr();

    mhtdc_sci31lr_dt_selected.clear();
    mhtdc_sci31lr_x_selected.clear();
    sci31l_hits_selected.clear();
    sci31r_hits_selected.clear();
    for (int i = 0; i < hits_in_31l; i++)
    {
        for (int j = 0; j < hits_in_31r; j++)
        {
            double dt = mhtdc_sci31lr_dt[i * hits_in_31r + j];
            if (TMath::Abs(dt) < frs_config->fscilr_mhtdc_limit) 
            {
                sci31l_hits_selected.emplace_back(sci31l_hits[i]);
                sci31r_hits_selected.emplace_back(sci31r_hits[j]);
                mhtdc_sci31lr_dt_selected.emplace_back(dt);
                mhtdc_sci31lr_x_selected.emplace_back(mhtdc_sci31lr_x[i * hits_in_31r + j]);
                hits_in_31lr_selected++;
            }
        }
    }
    hits_in_31l_selected = sci31l_hits_selected.size();
    hits_in_31r_selected = sci31r_hits_selected.size(); 

    // SCI 41 L and R
    //c4LOG(info,"SCI41 L R");
    sci41l_hits = calSciItem.Get_mhtdc_sci41l_hits();
    int hits_in_41l = sci41l_hits.size();
    sci41r_hits = calSciItem.Get_mhtdc_sci41r_hits();
    int hits_in_41r = sci41r_hits.size();
    mhtdc_sci41lr_dt = calSciItem.Get_mhtdc_dT_41l_41r();
    mhtdc_sci41lr_x = calSciItem.Get_mhtdc_x_sci41lr();

    for (int i = 0; i < hits_in_41l; i++)
    {
        for (int j = 0; j < hits_in_41r; j++)
        {
            double dt = mhtdc_sci41lr_dt[i * hits_in_41r + j];
            if (TMath::Abs(dt) < frs_config->fscilr_mhtdc_limit) 
            {
                sci41l_hits_selected.emplace_back(sci41l_hits[i]);
                sci41r_hits_selected.emplace_back(sci41r_hits[j]);
                mhtdc_sci41lr_dt_selected.emplace_back(dt);
                mhtdc_sci41lr_x_selected.emplace_back(mhtdc_sci41lr_x[i * hits_in_41r + j]);
                hits_in_41lr_selected++;
            }
        }
    }
    hits_in_41l_selected = sci41l_hits_selected.size();
    hits_in_41r_selected = sci41r_hits_selected.size(); 

    // SCI 42 L and R
    //c4LOG(info,"SCI42 L R");
    sci42l_hits = calSciItem.Get_mhtdc_sci42l_hits();
    int hits_in_42l = sci42l_hits.size();
    sci42r_hits = calSciItem.Get_mhtdc_sci42r_hits();
    int hits_in_42r = sci42r_hits.size();
    mhtdc_sci42lr_dt = calSciItem.Get_mhtdc_dT_42l_42r();
    mhtdc_sci42lr_x = calSciItem.Get_mhtdc_x_sci42lr();

    mhtdc_sci42lr_dt_selected.clear();
    mhtdc_sci42lr_x_selected.clear();
    sci42l_hits_selected.clear();
    sci42r_hits_selected.clear();
    for (int i = 0; i < hits_in_42l; i++)
    {
        for (int j = 0; j < hits_in_42r; j++)
        {
            double dt = mhtdc_sci42lr_dt[i * hits_in_42r + j];
            if (TMath::Abs(dt) < frs_config->fscilr_mhtdc_limit) 
            {
                sci42l_hits_selected.emplace_back(sci42l_hits[i]);
                sci42r_hits_selected.emplace_back(sci42r_hits[j]);
                mhtdc_sci42lr_dt_selected.emplace_back(dt);
                mhtdc_sci42lr_x_selected.emplace_back(mhtdc_sci42lr_x[i * hits_in_42r + j]);
                hits_in_42lr_selected++;
            }
        }
    } 
    hits_in_42l_selected = sci42l_hits_selected.size();
    hits_in_42r_selected = sci42r_hits_selected.size(); 
    
    // SCI 43 L and R
    //c4LOG(info,"SCI43 L R");
    sci43l_hits = calSciItem.Get_mhtdc_sci43l_hits();
    int hits_in_43l = sci43l_hits.size();
    sci43r_hits = calSciItem.Get_mhtdc_sci43r_hits();
    int hits_in_43r = sci43r_hits.size();
    mhtdc_sci43lr_dt = calSciItem.Get_mhtdc_dT_43l_43r();
    mhtdc_sci43lr_x = calSciItem.Get_mhtdc_x_sci43lr();

    mhtdc_sci43lr_dt_selected.clear();
    mhtdc_sci43lr_x_selected.clear();
    sci43l_hits_selected.clear();
    sci43r_hits_selected.clear();
    for (int i = 0; i < hits_in_43l; i++)
    {
        for (int j = 0; j < hits_in_43r; j++)
        {
            double dt = mhtdc_sci43lr_dt[i * hits_in_43r + j];
            if (TMath::Abs(dt) < frs_config->fscilr_mhtdc_limit) 
            {
                sci43l_hits_selected.emplace_back(sci43l_hits[i]);
                sci43r_hits_selected.emplace_back(sci43r_hits[j]);
                mhtdc_sci43lr_dt_selected.emplace_back(dt);
                mhtdc_sci43lr_x_selected.emplace_back(mhtdc_sci43lr_x[i * hits_in_43r + j]);
                hits_in_43lr_selected++;
            }
        }
    }
    hits_in_43l_selected = sci43l_hits_selected.size();
    hits_in_43r_selected = sci43r_hits_selected.size(); 

    // TOF: loop over selected hits left-right, define tof, apply cuts, define tof_selected
    // 11 -> 21
    // std::cout << "event " << std::endl;
    //c4LOG(info,"TOF 2111");
    //c4LOG(info, " size of mhtdc_sci11lr_x_selected : " << mhtdc_sci11lr_x_selected.size());
    hits_in_tof2111_selected = hits_in_21lr_selected * hits_in_11lr_selected;
    int count = 0;
    for (int i = 0; i < hits_in_21l_selected; i++)
    {
        for (int k = 0; k < hits_in_11l_selected; k++)
        {
            //count = i * hits_in_21r_selected * hits_in_11l_selected * hits_in_11r_selected + i * hits_in_11l_selected * hits_in_11r_selected + k * hits_in_11r_selected + k;
            // EG: this is just an extra check but this condition should already be valid since we are using the selected hits
            if ((sci->mhtdc_factor_ch_to_ns * TMath::Abs(sci21l_hits_selected[i] - sci21r_hits_selected[i]) < frs_config->fscilr_mhtdc_limit) && (sci->mhtdc_factor_ch_to_ns * TMath::Abs(sci11l_hits_selected[k] - sci11r_hits_selected[k]) < frs_config->fscilr_mhtdc_limit))
            {
                float tof = sci->mhtdc_factor_ch_to_ns * (0.5 * (sci21l_hits_selected[i] + sci21r_hits_selected[i]) - 0.5 * (sci11l_hits_selected[k] + sci11r_hits_selected[k])) + sci->mhtdc_offset_21_11[sci->sci11_select];
                mhtdc_tof2111.emplace_back(tof);
                //c4LOG(info,"before tof selection");

                if (tof > frs_config->ftof_2111_min && tof < frs_config->ftof_2111_max) 
                {
                    //c4LOG(info,"after tof selection");
                    mhtdc_tof2111_selected.emplace_back(tof);
                    //c4LOG(info," index for mhtdc : " << k);
                    mhtdc_sci11lr_x_tofs1s2_selected.emplace_back(mhtdc_sci11lr_x_selected[k]);
                    //c4LOG(info,"2");
                    mhtdc_sci21lr_x_tofs1s2_selected.emplace_back(mhtdc_sci21lr_x_selected[i]);
                    //c4LOG(info,"3");
                    sci11l_hits_tofs1s2_selected.emplace_back(sci11l_hits_selected[k]);
                    //c4LOG(info,"4");
                    sci11r_hits_tofs1s2_selected.emplace_back(sci11r_hits_selected[k]);
                    //c4LOG(info,"5");
                    sci21l_hits_tofs1s2_selected.emplace_back(sci21l_hits_selected[i]);
                    sci21r_hits_tofs1s2_selected.emplace_back(sci21r_hits_selected[i]);
                    //c4LOG(info,"end of tof loop");
                }
            }
        }
    }
    //c4LOG(info,"hits size");
    hits_in_11l_tofs1s2_selected = sci11l_hits_tofs1s2_selected.size();
    hits_in_11r_tofs1s2_selected = sci11r_hits_tofs1s2_selected.size();  
    hits_in_21l_tofs1s2_selected = sci11l_hits_tofs1s2_selected.size();
    hits_in_21r_tofs1s2_selected = sci11r_hits_tofs1s2_selected.size(); 

    //c4LOG(info,"hits calc");
    //c4LOG(info, " hits_in_21l_tofs1s2_selected :" << hits_in_21l_tofs1s2_selected);
    hits_in_11lr_tofs1s2_selected = hits_in_11l_tofs1s2_selected;
    hits_in_21lr_tofs1s2_selected = hits_in_21l_tofs1s2_selected;

    //TOF:
    // 21 -> 41
    //c4LOG(info,"TOF 4121");
    hits_in_tof4121_selected = hits_in_41lr_selected * hits_in_21lr_selected;
    count = 0;
    for (int i = 0; i < hits_in_41l_selected; i++)
    {
        for (int k = 0; k < hits_in_21l_tofs1s2_selected; k++) 
        {
            //count = i * hits_in_41r_selected * hits_in_21l_selected * hits_in_21r_selected + j * hits_in_21l_selected * hits_in_21r_selected + k * hits_in_21r_selected + l;
            if ((sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci41l_hits_selected[i] - sci41r_hits_selected[i]) < frs_config->fscilr_mhtdc_limit) && (sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci21l_hits_tofs1s2_selected[k] - sci21r_hits_tofs1s2_selected[k]) < frs_config->fscilr_mhtdc_limit))
            {
                float tof = sci->mhtdc_factor_ch_to_ns * (0.5 * (sci41l_hits_selected[i] + sci41r_hits_selected[i]) - 0.5 * (sci21l_hits_tofs1s2_selected[k] + sci21r_hits_tofs1s2_selected[k])) + sci->mhtdc_offset_41_21;
                mhtdc_tof4121.emplace_back(tof);
                if (tof > frs_config->ftof_4121_min && tof < frs_config->ftof_4121_max)
                {
                    mhtdc_tof4121_selected.emplace_back(tof);
                    //c4LOG(info,"a");
                    mhtdc_sci21lr_x_tofs2s4_selected.emplace_back(mhtdc_sci21lr_x_tofs1s2_selected[k]);
                    mhtdc_sci41lr_x_tofs2s4_selected.emplace_back(mhtdc_sci41lr_x_selected[i]);
                    //c4LOG(info,"b");
                    sci21l_hits_tofs2s4_selected.emplace_back(sci21l_hits_tofs1s2_selected[k]);
                    sci21r_hits_tofs2s4_selected.emplace_back(sci21r_hits_tofs1s2_selected[k]);
                    //c4LOG(info,"c");
                    sci41l_hits_tofs2s4_selected.emplace_back(sci41l_hits_selected[i]);
                    sci41r_hits_tofs2s4_selected.emplace_back(sci41r_hits_selected[i]);
                }     
            }   
        }
    }
    hits_in_21l_tofs2s4_selected = sci21l_hits_tofs2s4_selected.size();
    hits_in_21r_tofs2s4_selected = sci21r_hits_tofs2s4_selected.size();  
    hits_in_41l_tofs2s4_selected = sci41l_hits_tofs2s4_selected.size();
    hits_in_41r_tofs2s4_selected = sci41r_hits_tofs2s4_selected.size();  

    hits_in_21lr_tofs2s4_selected = hits_in_21l_tofs2s4_selected;
    hits_in_41lr_tofs2s4_selected = hits_in_41l_tofs2s4_selected;

    // 22 -> 41
    //c4LOG(info,"TOF 4122");
    hits_in_tof4122_selected = hits_in_41lr_selected * hits_in_22lr_selected;
    count = 0;
    for (int i = 0; i < hits_in_41l_selected; i++) 
    {
        for (int k = 0; k < hits_in_22l_selected; k++) 
        {
            //count = i * hits_in_41r_selected * hits_in_22l_selected *hits_in_22r_selected + j * hits_in_22l_selected * hits_in_22r_selected + k * hits_in_22r_selected + l;
            if ((sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci41l_hits_selected[i] - sci41r_hits_selected[i]) < frs_config->fscilr_mhtdc_limit) && (sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci22l_hits_selected[k] - sci22r_hits_selected[k]) < frs_config->fscilr_mhtdc_limit))
            {
                float tof = sci->mhtdc_factor_ch_to_ns * (0.5 * (sci41l_hits_selected[i] + sci41r_hits_selected[i]) - 0.5 * (sci22l_hits_selected[k] + sci22r_hits_selected[k])) + sci->mhtdc_offset_41_22;
                mhtdc_tof4122.emplace_back(tof);
                if (tof > frs_config->ftof_4122_min && tof < frs_config->ftof_4122_max) mhtdc_tof4122_selected.emplace_back(tof); 
            }  
        }
        
    }

    // 21 -> 42
    //c4LOG(info,"TOF 4221");
    hits_in_tof4221_selected = hits_in_42lr_selected * hits_in_21lr_selected;
    count = 0;
    for (int i = 0; i < hits_in_42l_selected; i++) 
    {
        for (int k = 0; k < hits_in_21l_selected; k++) 
        {
            //count = i * hits_in_42r_selected * hits_in_21l_selected * hits_in_21r_selected + j * hits_in_21l_selected * hits_in_21r_selected + k * hits_in_21r_selected + l;
            if ((sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci42l_hits_selected[i] - sci42r_hits_selected[i]) < frs_config->fscilr_mhtdc_limit) && (sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci21l_hits_selected[k] - sci21r_hits_selected[k]) < frs_config->fscilr_mhtdc_limit))
            {
                float tof = sci->mhtdc_factor_ch_to_ns * (0.5 * (sci42l_hits_selected[i] + sci42r_hits_selected[i]) - 0.5 * (sci21l_hits_selected[k] + sci21r_hits_selected[k])) + sci->mhtdc_offset_42_21;
                mhtdc_tof4221.emplace_back(tof);
                if (tof > frs_config->ftof_4221_min && tof < frs_config->ftof_4221_max) mhtdc_tof4221.emplace_back(tof);
            }    
        }   
    }

    // 21 -> 43
    //c4LOG(info,"TOF 4321");
    int hits_in_tof4321_selected = hits_in_43lr_selected * hits_in_21lr_selected;
    count = 0;
    for (int i = 0; i < hits_in_43l_selected; i++) 
    {
        for (int k = 0; k < hits_in_21l_selected; k++) 
        {
            //count = i * hits_in_43r_selected * hits_in_21l_selected * hits_in_21r_selected + j * hits_in_21l_selected * hits_in_21r_selected + k*hits_in_21r_selected + l;
            if ((sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci43l_hits_selected[i] - sci43r_hits_selected[i]) < frs_config->fscilr_mhtdc_limit) && (sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci21l_hits_selected[k] - sci21r_hits_selected[k]) < frs_config->fscilr_mhtdc_limit))
            {
                float tof = sci->mhtdc_factor_ch_to_ns * (0.5 * (sci43l_hits_selected[i] + sci43r_hits_selected[i]) - 0.5 * (sci21l_hits_selected[k] + sci21r_hits_selected[k])) + sci->mhtdc_offset_43_21;
                mhtdc_tof4221.emplace_back(tof);
                if (tof > frs_config->ftof_4321_min && tof < frs_config->ftof_4321_max) mhtdc_tof4321.emplace_back(tof);
            }
        } 
    }
    
    // 21 -> 31
    //c4LOG(info,"TOF 3121");
    int hits_in_tof3121_selected = hits_in_31lr_selected * hits_in_21lr_selected;
    count = 0;
    for (int i = 0; i < hits_in_31l_selected; i++) 
    {
        for (int k = 0; k < hits_in_21l_selected; k++) 
        {
            //count = i * hits_in_31r_selected * hits_in_21l_selected * hits_in_21r_selected + j * hits_in_21l_selected * hits_in_21r_selected + k * hits_in_21r_selected + l;
            if ((sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci31l_hits_selected[i] - sci31r_hits_selected[i]) < frs_config->fscilr_mhtdc_limit) && (sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci21l_hits_selected[k] - sci21r_hits_selected[k]) < frs_config->fscilr_mhtdc_limit))
            {
                float tof = sci->mhtdc_factor_ch_to_ns * (0.5 * (sci31l_hits_selected[i] + sci31r_hits_selected[i]) - 0.5 * (sci21l_hits_selected[k] + sci21r_hits_selected[k])) + sci->mhtdc_offset_31_21;
                mhtdc_tof3121.emplace_back(tof);
                if (tof > frs_config->ftof_3121_min && tof < frs_config->ftof_3121_max) mhtdc_tof3121.emplace_back(tof);
            }
        }   
    }

    /*
    // 21 -> 81 // CEJ: not sure why uncommented?
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


}

void FrsCal2Hit::ProcessMusic()
{
    auto const & calMusicItem = calMusicArray->at(0);

    music21_e = calMusicItem.Get_music21_e();
    music22_e = calMusicItem.Get_music22_e();
    music41_e = calMusicItem.Get_music41_e();
    music42_e = calMusicItem.Get_music42_e();
    music43_e = calMusicItem.Get_music43_e();
    
    for (int i = 0; i < 8; i++)
    {   
        // ::: 21 ::::
        if (music21_e[i] > 4)
        {
            if (music->exclude_music21_de_adc_channel[i] == kTRUE) music21_b_e[i] = false;
            else music21_b_e[i] = ((music21_e[i] > 10) && (music21_e[i] < 65536)); // from go4

            if (music21_b_e[i]) music21_anodes_cnt++;
        }

        // Time

        // ::: 22 ::::
        if (music22_e[i] > 4)
        {
            if (music->exclude_music22_de_adc_channel[i] == kTRUE) music22_b_e[i] = false;
            else music22_b_e[i] = ((music22_e[i] > 100) && (music22_e[i] < 4086));

            if (music22_b_e[i]) music22_anodes_cnt++;
        }

        // Time

        // ::: 41 ::::
        if (music41_e[i] > 4)
        {
            if (music->exclude_music41_de_adc_channel[i] == kTRUE) music41_b_e[i] = false;
            else music41_b_e[i] = ((music41_e[i] > 100) && (music41_e[i] < 4086));

            if (music41_b_e[i]) music41_anodes_cnt++;
        }

        // Time

        // ::: 42 ::::
        if (music42_e[i] > 4)
        {
            if (music->exclude_music42_de_adc_channel[i] == kTRUE) music42_b_e[i] = false;
            else music42_b_e[i] = ((music42_e[i] > 100) && (music42_e[i] < 4086));

            if (music42_b_e[i]) music42_anodes_cnt++;
        }

        // Time

        // ::: 43 ::::
        if (music43_e[i] > 4)
        {
            if (music->exclude_music43_de_adc_channel[i] == kTRUE) music43_b_e[i] = false;
            else music43_b_e[i] = ((music43_e[i] > 100) && (music43_e[i] < 4086));

            if (music43_b_e[i]) music43_anodes_cnt++;
        }

        // Time

    }

    // std::cout << "anodes count 21:: " << music21_anodes_cnt << std::endl;

    #ifndef MUSIC_ANA_NEW
    if (music21_anodes_count == music->MUSIC21_num_an)
    {
        Float_t r1 = ((music21_e[0]) * music->music21_gain[0] + music->music21_off[0]) * ((music21_e[1]) * music->music21_gain[1] + music->music21_off[1]);
        Float_t r2 = ((music21_e[2]) * music->music21_gain[2] + music->music21_off[2]) * ((music21_e[3]) * music->music21_gain[3] + music->music21_off[3]);
        Float_t r3 = ((music21_e[4]) * music->music21_gain[4] + music->music21_off[4]) * ((music21_e[5]) * music->music21_gain[5] + music->music21_off[5]);
        Float_t r4 = ((music21_e[6]) * music->music21_gain[6] + music->music21_off[6]) * ((music21_e[6]) * music->music21_gain[7] + music->music21_off[7]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            b_music21de = kTRUE;
            music21_de = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            music21_de_cor = music21_de;
        }
    }
    #endif

    #ifdef MUSIC_ANA_NEW
    if (music21_anodes_cnt >= music->MUSIC21_num_an / 2)
    {
        Float_t temp_music21de = 1.0;
        Int_t temp_count21 = 0;
        for (int i = 0; i < 8; i++)
        {
            if (music21_b_e[i])
            {
                temp_music21de *= ((music21_e[i]) * music->music21_e_gain[i] + music->music21_e_off[i]);
                temp_count21++;
            }
        }
        music21_de = TMath::Power(temp_music21de, 1. / ((float)(temp_count21)));
        music21_de_cor = music21_de;
        b_music21de = kTRUE;
    }
    #endif

    #ifndef MUSIC_ANA_NEW
    if (music22_anodes_count == music->MUSIC22_num_an)
    {
        Float_t r1 = ((music22_e[0]) * music->music22_gain[0] + music->music22_off[0]) * ((music22_e[1]) * music->music22_gain[1] + music->music22_off[1]);
        Float_t r2 = ((music22_e[2]) * music->music22_gain[2] + music->music22_off[2]) * ((music22_e[3]) * music->music22_gain[3] + music->music22_off[3]);
        Float_t r3 = ((music22_e[4]) * music->music22_gain[4] + music->music22_off[4]) * ((music22_e[5]) * music->music22_gain[5] + music->music22_off[5]);
        Float_t r4 = ((music22_e[6]) * music->music22_gain[6] + music->music22_off[6]) * ((music22_e[7]) * music->music22_gain[7] + music->music22_off[7]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            b_music22de = kTRUE;
            music22_de = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            music22_de_cor = music22_de;
        }
    }
    #endif

    #ifdef MUSIC_ANA_NEW
    if (music22_anodes_cnt >= music->MUSIC22_num_an / 2)
    {
        Float_t temp_music22de = 1.0;
        Int_t temp_count22 = 0;
        for (int i = 0; i < 8; i++)
        {
            if (music22_b_e[i])
            {
                temp_music22de *= ((music22_e[i]) * music->music22_e_gain[i] + music->music22_e_off[i]);
                temp_count22++;
            }
        }
        music22_de = TMath::Power(temp_music22de, 1. / ((float)(temp_count22)));
        music22_de_cor = music22_de;
        b_music22de = kTRUE;
    }
    #endif

    #ifndef MUSIC_ANA_NEW
    if (music41_anodes_count == music->MUSIC41_num_an)
    {
        Float_t r1 = ((music41_e[0]) * music->music41_gain[0] + music->music41_off[0]) * ((music41_e[1]) * music->music41_gain[1] + music->music41_off[1]);
        Float_t r2 = ((music41_e[2]) * music->music41_gain[2] + music->music41_off[2]) * ((music41_e[3]) * music->music41_gain[3] + music->music41_off[3]);
        Float_t r3 = ((music41_e[4]) * music->music41_gain[4] + music->music41_off[4]) * ((music41_e[5]) * music->music41_gain[5] + music->music41_off[5]);
        Float_t r4 = ((music41_e[6]) * music->music41_gain[6] + music->music41_off[6]) * ((music41_e[7]) * music->music41_gain[7] + music->music41_off[7]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            b_music41de = kTRUE;
            music41_de = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            music41_de_cor = music41_de;
        }
    }
    #endif

    #ifdef MUSIC_ANA_NEW
    if (music41_anodes_cnt >= music->MUSIC41_num_an / 2)
    {
        Float_t temp_music41de = 1.0;
        Int_t temp_count41 = 0;
        for (int i = 0; i < 8; i++)
        {
            if (music41_b_e[i])
            {
                temp_music41de *= ((music41_e[i]) * music->music41_e_gain[i] + music->music41_e_off[i]);
                temp_count41++;
            }
        }
        music41_de = TMath::Power(temp_music41de, 1. / ((float)(temp_count41)));
        music41_de_cor = music41_de;
        b_music41de = kTRUE;
    }
    #endif

    #ifndef MUSIC_ANA_NEW
    if (music42_anodes_count == music->MUSIC42_num_an)
    {
        Float_t r1 = ((music42_e[0]) * music->music42_gain[0] + music->music42_off[0]) * ((music42_e[1]) * music->music42_gain[1] + music->music42_off[1]);
        Float_t r2 = ((music42_e[2]) * music->music42_gain[2] + music->music42_off[2]) * ((music42_e[3]) * music->music42_gain[3] + music->music42_off[3]);
        Float_t r3 = ((music42_e[4]) * music->music42_gain[4] + music->music42_off[4]) * ((music42_e[5]) * music->music42_gain[5] + music->music42_off[5]);
        Float_t r4 = ((music42_e[6]) * music->music42_gain[6] + music->music42_off[6]) * ((music42_e[7]) * music->music42_gain[7] + music->music42_off[7]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            b_music42de = kTRUE;
            music42_de = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            music42_de_cor = music42_de;
        }
    }
    #endif

    #ifdef MUSIC_ANA_NEW
    if (music42_anodes_cnt >= music->MUSIC42_num_an / 2)
    {
        Float_t temp_music42de = 1.0;
        Int_t temp_count42 = 0;
        for (int i = 0; i < 8; i++)
        {
            if (music42_b_e[i])
            {
                temp_music42de *= ((music42_e[i]) * music->music42_e_gain[i] + music->music42_e_off[i]);
                temp_count42++;
            }
        }
        music42_de = TMath::Power(temp_music42de, 1. / ((float)(temp_count42)));
        music42_de_cor = music42_de;
        b_music42de = kTRUE;
    }
    #endif

    #ifndef MUSIC_ANA_NEW
    if (music43_anodes_count == music->MUSIC43_num_an)
    {
        Float_t r1 = ((music43_e[0]) * music->music43_gain[0] + music->music43_off[0]) * ((music43_e[1]) * music->music43_gain[1] + music->music43_off[1]);
        Float_t r2 = ((music43_e[2]) * music->music43_gain[2] + music->music43_off[2]) * ((music43_e[3]) * music->music43_gain[3] + music->music43_off[3]);
        Float_t r3 = ((music43_e[4]) * music->music43_gain[4] + music->music43_off[4]) * ((music43_e[5]) * music->music43_gain[5] + music->music43_off[5]);
        Float_t r4 = ((music43_e[6]) * music->music43_gain[6] + music->music43_off[6]) * ((music43_e[7]) * music->music43_gain[7] + music->music43_off[7]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            b_music43de = kTRUE;
            music43_de = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            music43_de_cor = music43_de;
        }
    }
    #endif

    #ifdef MUSIC_ANA_NEW
    if (music43_anodes_cnt >= music->MUSIC43_num_an / 2)
    {
        Float_t temp_music43de = 1.0;
        Int_t temp_count43 = 0;
        for (int i = 0; i < 8; i++)
        {
            if (music43_b_e[i])
            {
                temp_music43de *= ((music43_e[i]) * music->music43_e_gain[i] + music->music43_e_off[i]);
                temp_count43++;
            }
        }
        music43_de = TMath::Power(temp_music43de, 1. / ((float)(temp_count43)));
        music43_de_cor = music43_de;
        b_music43de = kTRUE;
    }
    #endif

    auto const & calTpcItem = calTpcArray->at(0);
    b_tpc_xy = calTpcItem.Get_b_tpc_xy();

    // ::: Position correction by TPC ::::::
    if (b_tpc_xy[0] && b_tpc_xy[1])
    {
        music21_x_mean = calTpcItem.Get_tpc21_22_music21_x();
        music22_x_mean = calTpcItem.Get_tpc21_22_music22_x();

        Float_t power, Corr;
        if (b_music21de)
        {
            power = 1., Corr = 0.;
            for (int i = 0; i < 7; i++)
            {
                Corr += music->music21_pos_a[i] * power;
                power *= music21_x_mean;
            }
            if (Corr != 0)
            {
                Corr = music->music21_pos_a[0] / Corr;
                music21_de_cor = music21_de * Corr;
            }
        }

        if (b_music22de)
        {
            power = 1., Corr = 0.;
            for (int i = 0; i < 7; i++)
            {
                Corr += music->music22_pos_a[i] * power;
                power *= music22_x_mean;
            }
            if (Corr != 0)
            {
                Corr = music->music22_pos_a[0] / Corr;
                music22_de_cor = music22_de * Corr;
            }
        }
    }
    if (b_tpc_xy[2] && b_tpc_xy[3])
    {
        music21_x_mean = calTpcItem.Get_tpc23_24_music21_x();
        music22_x_mean = calTpcItem.Get_tpc23_24_music22_x();

        Float_t power, Corr;
        if (b_music21de)
        {
            power = 1., Corr = 0.;
            for (int i = 0; i < 7; i++)
            {
                Corr += music->music21_pos_a[i] * power;
                power *= music21_x_mean;
            }
            if (Corr != 0)
            {
                Corr = music->music21_pos_a[0] / Corr;
                music21_de_cor = music21_de * Corr;
            }
        }

        if (b_music22de)
        {
            power = 1., Corr = 0.;
            for (int i = 0; i < 7; i++)
            {
                Corr += music->music22_pos_a[i] * power;
                power *= music22_x_mean;
            }
            if (Corr != 0)
            {
                Corr = music->music22_pos_a[0] / Corr;
                music22_de_cor = music22_de * Corr;
            }
        }
    }

    if (b_tpc_xy[4] && b_tpc_xy[5])
    {
        music41_x_mean = calTpcItem.Get_tpc_music41_x();
        music42_x_mean = calTpcItem.Get_tpc_music42_x();
        music43_x_mean = calTpcItem.Get_tpc_music43_x();

        Float_t power, Corr;
        if (b_music41de)
        {
            power = 1., Corr = 0.;
            for (int i = 0; i < 7; i++)
            {
                Corr += music->music41_pos_a[i] * power;
                power *= music41_x_mean;
            }
            if (Corr != 0)
            {
                Corr = music->music41_pos_a[0] / Corr;
                music41_de_cor = music41_de * Corr;
            }
        }

        if (b_music42de)
        {
            power = 1., Corr = 0.;
            for (int i = 0; i < 7; i++)
            {
                Corr += music->music42_pos_a[i] * power;
                power *= music42_x_mean;
            }
            if (Corr != 0)
            {
                Corr = music->music42_pos_a[0] / Corr;
                music42_de_cor = music42_de * Corr;
            }
        }

        if (b_music43de)
        {
            power = 1., Corr = 0.;
            for (int i = 0; i < 7; i++)
            {
                Corr += music->music43_pos_a[i] * power;
                power *= music43_x_mean;
            }
            if (Corr != 0)
            {
                Corr = music->music43_pos_a[0] / Corr;
                music43_de_cor = music43_de * Corr;
            }
        }
    }
    
}

void FrsCal2Hit::ProcessIDs()
{
    // Calculation of dE and Z from MUSIC41
    // Calibration for MUSIC is done with 1/b2 - last update sept2024
    
    auto const & calTpcItem = calTpcArray->at(0);
    b_tpc_xy = calTpcItem.Get_b_tpc_xy();

    if (sci_b_x_11)
    {
        if (id->use_sc11x == 1) id_x1 = sci_x_11;
        else if (id->use_sc11x == 0) id_x1 = 0;
        id_y1 = 0;
        id_a1 = 0;
        id_b1 = 0;
    }

    if (id->x_s2_select == 1)
    {   
        if (b_tpc_xy[2] && b_tpc_xy[3])
        {   
            id_x2 = calTpcItem.Get_tpc_x_s2_foc_23_24();
            id_y2 = calTpcItem.Get_tpc_y_s2_foc_23_24();
            id_a2 = calTpcItem.Get_tpc_angle_x_s2_foc_23_24();
            id_b2 = calTpcItem.Get_tpc_angle_y_s2_foc_23_24();
        }
        else if (b_tpc_xy[1] && b_tpc_xy[3])
        {
            id_x2 = calTpcItem.Get_tpc_x_s2_foc_22_24();
            id_y2 = calTpcItem.Get_tpc_y_s2_foc_22_24();
            id_a2 = calTpcItem.Get_tpc_angle_x_s2_foc_22_24();
            id_b2 = calTpcItem.Get_tpc_angle_y_s2_foc_22_24();
        }
        else if (b_tpc_xy[0] && b_tpc_xy[1])
        {   
            id_x2 = calTpcItem.Get_tpc_x_s2_foc_21_22();
            id_y2 = calTpcItem.Get_tpc_y_s2_foc_21_22();
            id_a2 = calTpcItem.Get_tpc_angle_x_s2_foc_21_22();
            id_b2 = calTpcItem.Get_tpc_angle_y_s2_foc_21_22();
        }
        

    }
    else if (id->x_s2_select == 2)
    {   
        // SC21
        if (sci_b_x_21)
        {
            id_x2 = sci_x_21;
            id_y2 = 0.0;
            id_a2 = 0.0;
            id_b2 = 0.0;
        }
    }
    else if (id->x_s2_select == 3)
    {
        if (sci_b_x_22)
        {
            id_x2 = sci_x_22;
            id_y2 = 0.0;
            id_a2 = 0.0;
            id_b2 = 0.0;
        }
    }

    if (b_tpc_xy[4] && b_tpc_xy[5])
    {   
        id_x4 = calTpcItem.Get_tpc_x_s4();
        id_y4 = calTpcItem.Get_tpc_y_s4();
        id_a4 = calTpcItem.Get_tpc_angle_x_s4();
        id_b4 = calTpcItem.Get_tpc_angle_y_s4();
    }

    if (sci_b_x_81)
    {
        id_x8 = sci_x_81;
        id_y8 = 0.0;
        id_a8 = 0.0;
        id_b8 = 0.0;
    }


    id_b_x2 = ((id_x2 > -200) && (id_x2 < 100));
    id_b_x4 = ((id_x4 > -200) && (id_x4 < 100));


    /*----------------------------------------------------------*/
    /* Determination of beta                                    */
    /*----------------------------------------------------------*/
    id_beta_s1s2 = 0;
    if (id->tof_s2_select == 1)
    {
        if (sci_b_tofll_11_21 && sci_b_tofrr_11_21) id_beta_s1s2 = id->id_path1 / sci_tof_11_21_calib;
    }

    id_beta_s2s4 = 0;
    if (id->tof_s4_select == 1)
    {
        if (sci_b_tofll_21_41 && sci_b_tofrr_21_41)
        {
            id_beta_s2s4 = id->id_path2 / sci_tof_21_41_calib;
        }
    }
    else if (id->tof_s4_select == 2)
    {
        if (sci_b_tofll_21_42 && sci_b_tofrr_21_42)
        {
            id_beta_s2s4 = id->id_path3 / sci_tof_21_42_calib;
        }
    }
    else if (id->tof_s4_select == 3)
    {
        if (sci_b_tofll_22_41 && sci_b_tofrr_22_41)
        {
            id_beta_s2s4 = id->id_path5 / sci_tof_22_41_calib;
        }
    }

    /*------------------------------------------------------*/
    /* Determination of Brho                                */
    /*------------------------------------------------------*/

    if (id_b_x2)
    {
        id_rho[3] = frs->rho0[0] * (1. - id_x2 / 1000. / frs->dispersion[0]);
        id_brho[3] = (fabs(frs->bfield[0]) + fabs(frs->bfield[1])) / 2. * id_rho[3];

        if (id->use_sc11x == 0) id_brho[0] = id_brho[3];
        else if (id->use_sc11x)
        {
            if (id_b_x1)
            {
                id_rho[0] = frs->rho0[0] = (1. - (id_x2 - frs->magnification[5] * id_x1) / 1000. / frs->dispersion[5]);
                id_brho[0] = fabs(frs->bfield[1]) * id_rho[0];
            }
        } 

        // id_rho[0] = frs->rho0[0] * (1. - id_x2 / 1000. / frs->dispersion[0]);
        // id_brho[0] = (fabs(frs->bfield[0]) + fabs(frs->bfield[1])) / 2. * id_rho[0];

        if (id_b_x4)
        {
            id_rho[1] = frs->rho0[1] * (1. - (id_x4 - frs->magnification[1] * id_x2) / 1000. / frs->dispersion[1]);
            id_brho[1] = (fabs(frs->bfield[2]) + fabs(frs->bfield[3])) / 2. * id_rho[1];

        }
    }

    /*--------------------------------------------------------------*/
    /* Determination of A/Q                                         */
    /*--------------------------------------------------------------*/
    // S1-S2
    if (sci_b_tofll_11_21 && sci_b_tofrr_11_21 && id_b_x1 && id_b_x2)
    {
        if (id_beta_s1s2 > 0. && id_beta_s1s2 < 1.)
        {
            id_gamma_s1s2 = 1. / sqrt(1. - TMath::Power(id_beta_s1s2, 2));
            // CEJ:: deprecating "AoQ_corr" - imo is pointless and confusing when wishing to apply further corrections.
            id_AoQ_s1s2 = id_brho[0] / id_beta_s1s2 / id_gamma_s1s2 / aoq_factor - id->a1AoQCorr * id_a2;
            id_AoQ_corr_s1s2 = id_AoQ_s1s2 - id->a1AoQCorr * id_a2;

            id_b_AoQ_s1s2 = true;
        }
    }
    
    
    // S2-S4

    if (sci_b_tofll_21_41 && sci_b_tofrr_21_41 && id_b_x2 && id_b_x4)
    {
        if ((id_beta_s2s4 > 0.0) && (id_beta_s2s4 < 1.0))
        {
            id_gamma_s2s4 = 1. / sqrt(1. - TMath::Power(id_beta_s2s4, 2));
            id_AoQ_s2s4 = id_brho[1] / id_beta_s2s4 / id_gamma_s2s4 / aoq_factor;
            id_AoQ_corr_s2s4 = id_AoQ_s2s4 - id->a4AoQCorr * id_a4;
            
            id_b_AoQ_s2s4 = true;
        }
    }

    /*------------------------------------------------*/
    /* Determination of Z                           */
    /*------------------------------------------------*/
    // Calibration with MUSIC is done with 1/b2 - last update sept2024
    // S2 (MUSIC 1)
    // CEJ:: can be argued to check de_cor, merge removed it for now
    if ((music21_de_cor > 0.0) && (id_beta_s1s2 > 0.0) && (id_beta_s1s2 < 1.0))
    {
        float power = 1.;
        float sum = 0.;
        for (int i = 0; i < 4; i++)
        {
            sum += power * id->vel_music21_a[i];
            if (frs_config->old_beta_cal) power *= id_beta_s1s2;
            else { power *= 1.0 / TMath::Power(id_beta_s1s2, 2); }
        }
        id_music21_v_cor = sum;

        if (id_music21_v_cor > 0.0)
        {
            id_z21 = frs->primary_z * sqrt(music21_de_cor / id_music21_v_cor) + id->offset_z21;
        }
        if ((id_z21 > 0.0) && (id_z21 < 100.0))
        {   
            id_b_z21 = kTRUE;
        }
    }

    // S2 (MUSIC 2)
    if ((music22_de_cor > 0.0) && (id_beta_s1s2 > 0.0) && (id_beta_s1s2 < 1.0))
    {
        float power = 1.;
        float sum = 0.;
        for (int i = 0; i < 4; i++)
        {
            sum += power * id->vel_music22_a[i];
            if (frs_config->old_beta_cal) power *= id_beta_s1s2;
            else { power *= 1.0 / TMath::Power(id_beta_s1s2, 2); }
        }
        id_music22_v_cor = sum;

        if (id_music22_v_cor > 0.0)
        {
            id_z22 = frs->primary_z * sqrt(music22_de_cor / id_music22_v_cor) + id->offset_z22;
        }
        if ((id_z22 > 0.0) && (id_z22 < 100.0))
        {   
            id_b_z22 = kTRUE;
        }
    }


    // S4 (MUSIC 1)
    if ((music41_de_cor > 0.0) && (id_beta_s2s4 > 0.0) && (id_beta_s2s4 < 1.0))
    {
        float power = 1.;
        float sum = 0.;
        for (int i = 0; i < 4; i++)
        {
            // sum += power * id->vel_a1[i];
            sum += power * id->vel_music41_a[i];
            if (frs_config->old_beta_cal) power *= id_beta_s2s4;
            else { power *= 1.0 / TMath::Power(id_beta_s2s4, 2); }
        }
        id_music41_v_cor = sum;


        if (id_music41_v_cor > 0.0)
        {
            id_z41 = frs->primary_z * sqrt(music41_de_cor / id_music41_v_cor) + id->offset_z41;
        }

        if ((id_z41 > 0.0) && (id_z41 < 100.0))
        {   
            // CEJ: this seems out of order to me, gain matching first?
            id_b_z41 = kTRUE;
        }
    }

    // S4 (MUSIC 2)
    // CEJ::  potentially check de_cor here too
    if ((music42_de_cor > 0.0) && (id_beta_s2s4 > 0.0) && (id_beta_s2s4 < 1.0))
    {
        float power = 1.;
        float sum = 0.;
        for (int i = 0; i < 4; i++)
        {
            // sum += power * id->vel_a2[i];
            sum += power * id->vel_music42_a[i];
            if (frs_config->old_beta_cal) power *= id_beta_s2s4;
            else { power *= 1.0 / TMath::Power(id_beta_s2s4, 2); }
        }
        id_music42_v_cor = sum;

        // GainShift removed, because we have DriftCorr?
        if (id_music42_v_cor > 0.0)
        {
            id_z42 = frs->primary_z * sqrt(music42_de_cor / id_music42_v_cor) + id->offset_z42;
        }
        if ((id_z42 > 0.0) && (id_z42 < 100.0))
        {   
            // CEJ: this seems out of order to me, gain matching first?
            id_b_z42 = kTRUE;
        }

    }

    // S4 (MUSIC 3)
    if ((music43_de_cor > 0.0) && (id_beta_s2s4 > 0.0) && (id_beta_s2s4 < 1.0))
    {
        float power = 1.;
        float sum = 0.;
        for (int i = 0; i < 4; i++)
        {
            sum += power * id->vel_music43_a[i];
            if (frs_config->old_beta_cal) power *= id_beta_s2s4;
            else { power *= 1.0 / TMath::Power(id_beta_s2s4, 2); }
        }
        id_music43_v_cor = sum;

        if (id_music43_v_cor > 0.0)
        {
            id_z43 = frs->primary_z * sqrt(music43_de_cor / id_music43_v_cor) + id->offset_z43;
        }
        if ((id_z43 > 0.0) && (id_z43 < 100.0)) // the island of stability will be discovered one day and you will be sorry - JB
        {   
            id_b_z43 = kTRUE;
        }
    }


    float gamma1square_s2s4 = 1.0 + TMath::Power(((1 / aoq_factor) * (id_brho[0] / id_AoQ_s2s4)), 2);
    id_gamma_ta_s2s4 = TMath::Sqrt(gamma1square_s2s4);
    id_dEdegoQ = (id_gamma_ta_s2s4 - id_gamma_s2s4) * id_AoQ_s2s4;
    id_dEdeg_z41 = id_dEdegoQ * id_z41;

}

void FrsCal2Hit::ProcessIDs_MHTDC()
{
    auto const & calTpcItem = calTpcArray->at(0);
    b_tpc_xy = calTpcItem.Get_b_tpc_xy();

    // ::: X Positions :::::
    // S1
    //c4LOG(info,"S1 xposition");
    if (id->use_sc11x == 1)
    {
        temp_s1x_mhtdc = new Float_t[hits_in_11lr_tofs1s2_selected];
        for (int i = 0; i < hits_in_11lr_tofs1s2_selected; i++) temp_s1x_mhtdc[i] = mhtdc_sci11lr_x_tofs1s2_selected[i];
        hits_in_s1x_tofs1s2_selected = hits_in_11lr_tofs1s2_selected;
        temp_a1 = 0;
        
        
    }
    else
    {
        temp_s1x_mhtdc = new Float_t[hits_in_11lr_tofs1s2_selected];
        for (int i = 0; i < hits_in_11lr_tofs1s2_selected; i++) temp_s1x_mhtdc[i] = 0;
        hits_in_s1x_tofs1s2_selected = hits_in_11lr_tofs1s2_selected;
        temp_a1 = 0;
    }

    // S2
    //c4LOG(info,"S2 xposition");
    //c4LOG(info, " hits_in_21lr_tofs1s2_selected : " << hits_in_21lr_tofs1s2_selected);
    if (id->x_s2_select == 1) // TPCs
    {
        if (id->tof_s2_select == 1)
        {
            temp_s2x_mhtdc = new Float_t[hits_in_21lr_tofs1s2_selected];
            hits_in_s2x_tofs1s2_selected = hits_in_21lr_tofs1s2_selected;
        }
        else if (id->tof_s2_select == 2) 
        {
            temp_s2x_mhtdc = new Float_t[hits_in_22lr_selected];
            hits_in_s2x = hits_in_22lr_selected;
        }
        else c4LOG(fatal, "Invalid S2 TOF selection. Check FRS setup!");

        for (int i = 0; i < hits_in_s2x_tofs1s2_selected; i++) temp_s2x_mhtdc[i] = -999; 
        temp_a2 = -999;
        if (b_tpc_xy[0] && b_tpc_xy[1])
        {
            for (int i = 0; i < hits_in_s2x_tofs1s2_selected; i++) temp_s2x_mhtdc[i] = calTpcItem.Get_tpc_x_s2_foc_21_22();
            temp_a2 = calTpcItem.Get_tpc_angle_x_s2_foc_21_22();
        }
        else if (b_tpc_xy[2] && b_tpc_xy[3])
        {
            for (int i = 0; i < hits_in_s2x_tofs1s2_selected; i++) temp_s2x_mhtdc[i] = calTpcItem.Get_tpc_x_s2_foc_23_24();
            temp_a2 = calTpcItem.Get_tpc_angle_x_s2_foc_23_24();
        }
        else if (b_tpc_xy[1] && b_tpc_xy[3])
        {
            for (int i = 0; i < hits_in_s2x_tofs1s2_selected; i++) temp_s2x_mhtdc[i] = calTpcItem.Get_tpc_x_s2_foc_22_24();
            temp_a2 = calTpcItem.Get_tpc_angle_x_s2_foc_22_24();
        }
    }
    else if (id->x_s2_select == 2) // Sci21
    {
        temp_s2x_mhtdc = new Float_t[hits_in_21lr_tofs1s2_selected];
        for (int i = 0; i < hits_in_21lr_tofs1s2_selected; i++) temp_s2x_mhtdc[i] = mhtdc_sci21lr_x_tofs1s2_selected[i];
        temp_a2 = 0;
        hits_in_s2x_tofs1s2_selected = hits_in_21lr_tofs1s2_selected;

        if (id->tof_s2_select == 2) c4LOG(fatal, "Incompatible S2 X / TOF selection. Check FRS Setup file!");
    }
    else if (id->x_s2_select == 3) // Sci22
    {
        temp_s2x_mhtdc = new Float_t[hits_in_22lr_selected];
        for (int i = 0; i < hits_in_22lr_selected; i++) temp_s2x_mhtdc[i] = mhtdc_sci22lr_x[i];
        temp_a2 = 0;
        hits_in_s2x = hits_in_22lr_selected;

        if (id->tof_s2_select == 1) c4LOG(fatal, "Incompatible S2 X / TOF selection. Check FRS Setup file!");
    }

    // S4 -- no switch for position, always TPC
    //c4LOG(info,"S4 xposition");
    if (id->tof_s4_select == 1) // 21 -> 41
    {
        temp_s4x_mhtdc = new Float_t[hits_in_41lr_tofs2s4_selected];
        hits_in_s4x_tofs2s4_selected = hits_in_41lr_tofs2s4_selected;
        hits_in_s2x_tofs2s4_selected = hits_in_21lr_tofs2s4_selected;
    }
    else if (id->tof_s4_select == 2) // 21 -> 42
    {
        temp_s4x_mhtdc = new Float_t[hits_in_42lr_selected];
        hits_in_s4x = hits_in_42lr_selected;
    }
    else if (id->tof_s4_select == 3) // 22 -> 41
    {
        temp_s4x_mhtdc = new Float_t[hits_in_41lr_selected];
        hits_in_s4x = hits_in_41lr_selected;
    }

    if (b_tpc_xy[4] && b_tpc_xy[5])
    {
        for (int i = 0; i < hits_in_s4x_tofs2s4_selected; i++) temp_s4x_mhtdc[i] = calTpcItem.Get_tpc_x_s4();
        temp_a4 = calTpcItem.Get_tpc_angle_x_s4();
    }
    else
    {
        for (int i = 0; i < hits_in_s4x_tofs2s4_selected; i++) temp_s4x_mhtdc[i] = -999;
        temp_a4 = -999;
    }

    // S8 -- no switch for position, always mhtdc[0]?
    // CEJ deal with if we ever care about S8
    //temp_s8x_mhtdc = mhtdc_sc81lr_x[0];


    // ::::::::::::::::::::::::::::::::::::
    //   S1S2 MultihitTDC ID analysis
    //c4LOG(info,"MultihitTDC analysis");
    float mean_brho_s1s2 = frs->bfield[1]; // "actual mean doesn't work with s1s2 tof"

    // matches hits_in_tof2111 if 11 -> 21 selected, or hits_in_tof2211 if 11 -> 22 selected
    hits_in_s1s2 = hits_in_s2x_tofs1s2_selected;
    //hits_in_s1s2 = hits_in_s2x_selected * hits_in_s1x_selected;

    // id_mhtdc_beta_s1s2 = new Float_t[hits_in_s1s2];
    temp_id_mhtdc_beta_s1s2 = new Float_t[hits_in_s1s2];
    temp_id_mhtdc_tof_s1s2 = new Float_t[hits_in_s1s2];
    // id_mhtdc_tof_s1s2 = new Float_t[hits_in_s1s2];
    id_mhtdc_gamma_s1s2 = new Float_t[hits_in_s1s2];
    id_mhtdc_delta_s1s2 = new Float_t[hits_in_s1s2];
    // id_mhtdc_aoq_s1s2 = new Float_t[hits_in_s1s2];
    // id_mhtdc_aoq_corr_s1s2 = new Float_t[hits_in_s1s2];
    // id_mhtdc_v_cor_music21 = new Float_t[hits_in_s1s2];
    // id_mhtdc_z_music21 = new Float_t[hits_in_s1s2];
    // id_mhtdc_z_shifted_music21 = new Float_t[hits_in_s1s2];
    // id_mhtdc_v_cor_music22 = new Float_t[hits_in_s1s2];
    // id_mhtdc_z_music22 = new Float_t[hits_in_s1s2];
    // id_mhtdc_z_shifted_music22 = new Float_t[hits_in_s1s2];

    // Calculate TOF, Beta
    //c4LOG(info,"TOF");
    //c4LOG(info, " size of mhtdc_tof2111_selected : " << mhtdc_tof2111_selected.size() << " hits in s1s2 : " << hits_in_s1s2);
    if (id->tof_s2_select == 1) 
    {
        //c4LOG(info,"TOFa");
        for (int i = 0; i < hits_in_s1s2; i++) 
        {
            temp_id_mhtdc_tof_s1s2[i] = mhtdc_tof2111_selected[i];
            temp_id_mhtdc_beta_s1s2[i] = (id->mhtdc_length_sc1121 / temp_id_mhtdc_tof_s1s2[i]) / speed_light; // can never be outside 0 and 1
        }
    }
    // CEJ :: removed for testing
    else if (id->tof_s2_select == 2) 
    {
        //c4LOG(info,"TOFb");
        for (int i = 0; i < hits_in_s1s2; i++) 
        {
            temp_id_mhtdc_tof_s1s2[i] = mhtdc_tof2211[i];
            temp_id_mhtdc_beta_s1s2[i] = (id->mhtdc_length_sc1122 / temp_id_mhtdc_tof_s1s2[i]) / speed_light;
        }
    }
    else c4LOG(fatal, "Bad S2 TOF selection. Check FRS setup file!");
    
    // Calculate Gamma
    for (int i = 0; i < hits_in_s1s2; i++) id_mhtdc_gamma_s1s2[i] = (1. / sqrt(1. - TMath::Power(temp_id_mhtdc_beta_s1s2[i], 2)));

    // Calculate Delta, AoQ
    //c4LOG(info,"AoQs1s2");
    for (int i = 0; i < hits_in_s2x_tofs1s2_selected; i++)
    {
        //int count = i * hits_in_s1x_tofs1s2_selected + j;

        if (temp_s2x_mhtdc[i] > -200 && temp_s2x_mhtdc[i] < 200 && temp_s1x_mhtdc[i] > -120 && temp_s1x_mhtdc[i] < 120)
        {
            if (id->use_sc11x == 0) id_mhtdc_delta_s1s2[i] = temp_s2x_mhtdc[i] / (-1.0 * frs->dispersion[0] * 1000.0); //1000 is dispertsion from meter to mm. -1.0 is sign definition.
            else if (id->use_sc11x == 1) id_mhtdc_delta_s1s2[i] = (temp_s2x_mhtdc[i]  - (temp_s1x_mhtdc[i] * frs->magnification[5])) / (-1.0 * frs->dispersion[5] * 1000.0); //1000 is dispertsion from meter to mm. -1.0 is sign definition.
            else c4LOG(fatal, "Invalid Sc11 use selection. Check FRS setup file!");

            if (temp_id_mhtdc_beta_s1s2[i] > 0.0 && temp_id_mhtdc_beta_s1s2[i] < 1.0 && temp_id_mhtdc_tof_s1s2[i] > 0.0)
            {
                s1x_mhtdc.emplace_back(temp_s1x_mhtdc[i]);
                s1a_mhtdc.emplace_back(temp_a1);
                s2x_s1s2_mhtdc.emplace_back(temp_s2x_mhtdc[i]);
                s2a_s1s2_mhtdc.emplace_back(temp_a2);
                id_mhtdc_tof_s1s2.emplace_back(temp_id_mhtdc_tof_s1s2[i]);
                id_mhtdc_beta_s1s2.emplace_back(temp_id_mhtdc_beta_s1s2[i]);
                id_mhtdc_aoq_s1s2.emplace_back(mean_brho_s1s2 * (1. + id_mhtdc_delta_s1s2[i]) * temp_tm_to_MeV / (temp_mu * temp_id_mhtdc_beta_s1s2[i] * id_mhtdc_gamma_s1s2[i]));
                id_mhtdc_aoq_corr_s1s2.emplace_back(id_mhtdc_aoq_s1s2.back() - id->a1AoQCorr * id_a2);
                
            }
        }  
    }

    // Calculate Z (MUSIC 21 / 22)
    //c4LOG(info,"Zs2");
    for (int i = 0; i < id_mhtdc_beta_s1s2.size();  i++)
    {
        if (music21_de_cor > 0.0) //  beta should be >0 <1 by default
        {
            //c4LOG(info,"Za");
            Double_t power = 1., sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->mhtdc_vel_a_music21_s1s2[j];
                if (frs_config->old_beta_cal) power *= id_mhtdc_beta_s1s2.at(i);
                else { power *= 1.0 / TMath::Power(id_mhtdc_beta_s1s2.at(i), 2); }
            }

            //c4LOG(info,"Zb");
            if (sum > 0) // why are we creating some new array for this unless we're going to plot it.. 
            {
                id_mhtdc_z_music21.emplace_back(frs->primary_z * sqrt(music21_de_cor / sum));
                id_mhtdc_z_shifted_music21.emplace_back(id_mhtdc_z_music21.at(i) + id->mhtdc_offset_z_music21); // we don't even use this ?
            }
            else
            {
                id_mhtdc_z_music21.emplace_back(-999.);
                id_mhtdc_z_shifted_music21.emplace_back(-999.);
            }
        }
        else
        {
            //c4LOG(info,"Zc");
            id_mhtdc_z_music21.emplace_back(-999.);
            id_mhtdc_z_shifted_music21.emplace_back(-999.);
        }

        if (music22_de_cor > 0.0)
        {
            //c4LOG(info,"Zd");
            Double_t power = 1., sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->mhtdc_vel_a_music22[j];
                if (frs_config->old_beta_cal) power *= id_mhtdc_beta_s1s2.at(i);
                else { power *= 1.0 / TMath::Power(id_mhtdc_beta_s1s2.at(i), 2); }
            }

            if (sum > 0)
            {
                id_mhtdc_z_music22.emplace_back(frs->primary_z * sqrt(music22_de_cor / sum));
                id_mhtdc_z_shifted_music22.emplace_back(id_mhtdc_z_music22.at(i) + id->mhtdc_offset_z_music22);
            }
            else
            {
                id_mhtdc_z_music22.emplace_back(-999.);
                id_mhtdc_z_shifted_music22.emplace_back(-999.);
            }
        }
        else
        {
            id_mhtdc_z_music22.emplace_back(-999.);
            id_mhtdc_z_shifted_music22.emplace_back(-999.);
        }
    }

    // ::::::::::::::::::::::::::::::::::::
    //   S2S4 MultihitTDC ID analysis
    //c4LOG(info,"S2S4 mhtdc");
    float mean_brho_s2s4 = 0.5 * (frs->bfield[2] + frs->bfield[3]);

    // matches hits_in_tof4121 if 21 -> 41, etc.
    hits_in_s2s4 = hits_in_s4x_tofs2s4_selected;

    temp_id_mhtdc_beta_s2s4 = new Float_t[hits_in_s2s4];
    temp_id_mhtdc_tof_s2s4 = new Float_t[hits_in_s2s4];
    temp_id_mhtdc_gamma_s2s4 = new Float_t[hits_in_s2s4];
    // id_mhtdc_beta_s2s4 = new Float_t[hits_in_s2s4];
    // id_mhtdc_tof_s2s4 = new Float_t[hits_in_s2s4];
    id_mhtdc_delta_s2s4 = new Float_t[hits_in_s2s4];
    // id_mhtdc_aoq_s2s4 = new Float_t[hits_in_s2s4];
    // id_mhtdc_aoq_corr_s2s4 = new Float_t[hits_in_s2s4];
    // id_mhtdc_v_cor_music41 = new Float_t[hits_in_s2s4];
    // id_mhtdc_z_music41 = new Float_t[hits_in_s2s4];
    // id_mhtdc_z_shifted_music41 = new Float_t[hits_in_s2s4];
    // id_mhtdc_v_cor_music42 = new Float_t[hits_in_s2s4];
    // id_mhtdc_z_music42 = new Float_t[hits_in_s2s4];
    // id_mhtdc_z_shifted_music42 = new Float_t[hits_in_s2s4];
    // id_mhtdc_v_cor_music43 = new Float_t[hits_in_s2s4];
    // id_mhtdc_z_music43 = new Float_t[hits_in_s2s4];
    // id_mhtdc_z_shifted_music43 = new Float_t[hits_in_s2s4];

    // Calculate TOF, Beta
    //c4LOG(info,"TOF");
    if (id->tof_s4_select == 1) // 21 -> 41
    {
        for (int i = 0; i < hits_in_s2s4; i++) 
        {
            temp_id_mhtdc_tof_s2s4[i] = mhtdc_tof4121_selected[i];
            temp_id_mhtdc_beta_s2s4[i] = (id->mhtdc_length_sc2141 / temp_id_mhtdc_tof_s2s4[i]) / speed_light;
        }
    }
    else if (id->tof_s4_select == 2) // 21 -> 42
    {
        for (int i = 0; i < hits_in_s2s4; i++) 
        {
            temp_id_mhtdc_tof_s2s4[i] = mhtdc_tof4221_selected[i];
            temp_id_mhtdc_beta_s2s4[i] = (id->mhtdc_length_sc2142 / temp_id_mhtdc_tof_s2s4[i]) / speed_light;
        }
    }
    else if (id->tof_s4_select == 3) // 22 -> 41
    {
        for (int i = 0; i < hits_in_s2s4; i++) 
        {
            temp_id_mhtdc_tof_s2s4[i] = mhtdc_tof4122[i];
            temp_id_mhtdc_beta_s2s4[i] = (id->mhtdc_length_sc2241 / temp_id_mhtdc_tof_s2s4[i]) / speed_light;
        }
    }
    else c4LOG(fatal, "Invalid S4 TOF selection. Check FRS setup!");

    // Calculate Gamma
    for (int i = 0; i < hits_in_s2s4; i++) temp_id_mhtdc_gamma_s2s4[i] = (1. / sqrt(1. - TMath::Power(temp_id_mhtdc_beta_s2s4[i], 2)));

    // Calculate Delta (momentum deviation), AoQ
    //c4LOG(info,"AoQs2s4");
    for (int i = 0; i < hits_in_s4x_tofs2s4_selected; i++)
    {
        //int count = i * hits_in_s2x_tofs2s4_selected + j;

        if (temp_s4x_mhtdc[i] > -200 && temp_s4x_mhtdc[i] < 200 && temp_s2x_mhtdc[i] > -120 && temp_s2x_mhtdc[i] < 120)
        {
            id_mhtdc_delta_s2s4[i] = (temp_s4x_mhtdc[i]  - (temp_s2x_mhtdc[i] * frs->magnification[1])) / (-1.0 * frs->dispersion[1] * 1000.0); //1000 is dispertsion from meter to mm. -1.0 is sign definition. 

            if (temp_id_mhtdc_beta_s2s4[i] > 0.0 && temp_id_mhtdc_beta_s2s4[i] < 1.0)
            {
                s2x_s2s4_mhtdc.emplace_back(temp_s2x_mhtdc[i]);
                s2a_s2s4_mhtdc.emplace_back(temp_a2);
                s4x_mhtdc.emplace_back(temp_s4x_mhtdc[i]);
                s4a_mhtdc.emplace_back(temp_a4);
                id_mhtdc_tof_s2s4.emplace_back(temp_id_mhtdc_tof_s2s4[i]);
                id_mhtdc_beta_s2s4.emplace_back(temp_id_mhtdc_beta_s2s4[i]);
                id_mhtdc_gamma_s2s4.emplace_back(temp_id_mhtdc_gamma_s2s4[i]);
                id_mhtdc_aoq_s2s4.emplace_back(mean_brho_s2s4 * (1. + id_mhtdc_delta_s2s4[i]) * temp_tm_to_MeV / (temp_mu * temp_id_mhtdc_beta_s2s4[i] * temp_id_mhtdc_gamma_s2s4[i]));
                id_mhtdc_aoq_corr_s2s4.emplace_back(id_mhtdc_aoq_s2s4.back() - id->a2AoQCorr * id_a2);
            }
        }  
    }

    // Calculate Z (MUSIC 41 / 42 / 43)
    //c4LOG(info,"Z s4");
    for (int i = 0; i < id_mhtdc_beta_s2s4.size(); i++)
    {
        if (music41_de_cor > 0.0)
        {
            Double_t power = 1., sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->mhtdc_vel_a_music41[j];
                if (frs_config->old_beta_cal) power *= id_mhtdc_beta_s2s4.at(i);
                else { power *= 1.0 / TMath::Power(id_mhtdc_beta_s2s4.at(i), 2); }
            }

            // CEJ:: v_cor went here, but we (despec) don't care right now
            if (sum > 0.0)
            {
                id_mhtdc_z_music41.emplace_back(frs->primary_z * sqrt(music41_de / sum));
                id_mhtdc_z_shifted_music41.emplace_back(id_mhtdc_z_music41.back() + id->mhtdc_offset_z_music41);
            }
            else
            {
                id_mhtdc_z_music41.emplace_back(-999.);
                id_mhtdc_z_shifted_music41.emplace_back(-999.);
            }
        }
        else
        {
            id_mhtdc_z_music41.emplace_back(-999.);
            id_mhtdc_z_shifted_music41.emplace_back(-999.);
        }
        

        if (music42_de_cor > 0.0)
        {
            Double_t power = 1., sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->mhtdc_vel_a_music42[j];
                if (frs_config->old_beta_cal) power *= id_mhtdc_beta_s2s4.at(i);
                else { power *= 1.0 / TMath::Power(id_mhtdc_beta_s2s4.at(i), 2); }
            }

            if (sum > 0.0)
            {
                id_mhtdc_z_music42.emplace_back(frs->primary_z * sqrt(music42_de / sum));
                id_mhtdc_z_shifted_music42.emplace_back(id_mhtdc_z_music42.back() + id->mhtdc_offset_z_music42);
            }
            else
            {
                id_mhtdc_z_music42.emplace_back(-999.);
                id_mhtdc_z_shifted_music42.emplace_back(-999.);
            }
        }
        else
        {
            id_mhtdc_z_music42.emplace_back(-999.);
            id_mhtdc_z_shifted_music42.emplace_back(-999.);
        }

        if (music43_de_cor > 0.0)
        {
            Double_t power = 1., sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->mhtdc_vel_a_music43[j];
                if (frs_config->old_beta_cal) power *= id_mhtdc_beta_s2s4.at(i);
                else { power *= 1.0 / TMath::Power(id_mhtdc_beta_s2s4.at(i), 2); }
            }

            if (sum > 0.0)
            {
                id_mhtdc_z_music43.emplace_back(frs->primary_z * sqrt(music43_de / sum));
                id_mhtdc_z_shifted_music43.emplace_back(id_mhtdc_z_music43.back() + id->mhtdc_offset_z_music43);
            }
            else
            {
                id_mhtdc_z_music43.emplace_back(-999.);
                id_mhtdc_z_shifted_music43.emplace_back(-999.);
            }
        }
        else
        {
            id_mhtdc_z_music43.emplace_back(-999.);
            id_mhtdc_z_shifted_music43.emplace_back(-999.);
        }
    }
   
    // Calculate dEdeg for charge states
    Float_t mhtdc_gamma1square_s2s4 = 0;
    Float_t id_mhtdc_gamma_ta_s2s4 = 0;
  
    for (int i = 0; i < id_mhtdc_beta_s2s4.size(); i++)
    {
        if (id_mhtdc_aoq_s2s4.at(i) > 0 && id_mhtdc_z_music41.at(i) > 0)
        {
            mhtdc_gamma1square_s2s4 = 1.0 + TMath::Power(((1.0 / aoq_factor) * (id_brho[0] / id_mhtdc_aoq_s2s4.at(i))), 2);
            id_mhtdc_gamma_ta_s2s4 = TMath::Sqrt(mhtdc_gamma1square_s2s4);
            id_mhtdc_dEdegoQ_s2s4.emplace_back((id_mhtdc_gamma_ta_s2s4 - id_mhtdc_gamma_s2s4.at(i)) * id_mhtdc_aoq_s2s4.at(i));
            id_mhtdc_dEdeg_z41.emplace_back(id_mhtdc_dEdegoQ_s2s4.back() * id_mhtdc_z_music41.at(i));
            // 42, 43?
        }
        else
        {
            id_mhtdc_dEdegoQ_s2s4.emplace_back(-999);
            id_mhtdc_dEdeg_z41.emplace_back(-999);
            // 42, 43?
        }
    }
}

void FrsCal2Hit::ProcessDriftCorrections()
{
    // CEJ: can be tidied/reconfigured some later
    if (frs_config->AoQDriftLoaded()) // AoQs2s4
    {
        id_AoQs2s4_driftcorr = 0.;
        double drift_aoqs2s4 = 0.0;
        double drift_aoqs2s4_error = 0.0;
        int nentry_aoqs2s4 = 0;
        int aoqs2s4_frs_wr_time_a = 0; 
        int aoqs2s4_frs_wr_time_b = 0;
        double aoqs2s4_reference_value = 2.39;   //!!!! read from exp configuration - expected value
        int bin = 20;  
        
        std::map<int,std::pair<double,double>> aoqs2s4_drift = frs_config->AoQDriftCoefficients();
        for (const auto& entry : aoqs2s4_drift)
        {   
            int aoqs2s4_frs_wr_time = entry.first;
            std::pair<double,double> aoqs2s4_coeffs = entry.second;
            drift_aoqs2s4 = aoqs2s4_coeffs.first;
            drift_aoqs2s4_error = aoqs2s4_coeffs.second;

            double aoqs2s4_shift = drift_aoqs2s4 - aoqs2s4_reference_value;
            
            if ((FRS_time_mins >= (aoqs2s4_frs_wr_time - bin/2)) && (FRS_time_mins < (aoqs2s4_frs_wr_time + bin/2)))
            {
                id_AoQs2s4_driftcorr = id_AoQ_s2s4 - aoqs2s4_shift;
            }
            
            nentry_aoqs2s4++;
        }

    }

    if (frs_config->Z1DriftLoaded()) // Z41DriftLoaded Soon:tm
    {
        id_z41_driftcorr = 0.;
        double drift_z41 = 0.0;
        double drift_z41_error = 0.0;
        int nentry_z41 = 0;
        int z41_frs_wr_time_a = 0; 
        int z41_frs_wr_time_b = 0;
        double z41_reference_value = 41;     //!!!! read from exp configuration - expected value
        int bin = 20;                       //!!!! read from drift file

        std::map<int,std::pair<double,double>> z41_drift = frs_config->Z1DriftCoefficients();
        for (const auto& entry : z41_drift)
        {  
            int z41_frs_wr_time = entry.first;
            std::pair<double,double> z41_coeffs = entry.second;
            drift_z41 = z41_coeffs.first;
            drift_z41_error = z41_coeffs.second;

            double z41_shift = drift_z41 - z41_reference_value;

            if ((FRS_time_mins >= (z41_frs_wr_time - bin/2)) && (FRS_time_mins < (z41_frs_wr_time + bin/2)))
            {
                id_z41_driftcorr = id_z41 - z41_shift;
            }
            
            nentry_z41++;
        }

    }
}


Float_t FrsCal2Hit::rand3()
{
    return random3.Uniform(-0.5,0.5);
}

// Vectors and counters are reset
// IDs are set to unobtrusive values, bools are set to false
void FrsCal2Hit::FinishEvent()
{
    //c4LOG(info, " Start of Finish Event");
    hitArray->clear();
    multihitArray->clear();

    // ::: SCI TAC :::::: //
    sci_x_21 = -999.;
    sci_e_21 = 0.;
    sci_x_22 = -999.;
    sci_e_22 = 0.;
    sci_e_31 = -999.;
    sci_x_41 = -999.;
    sci_e_41 = 0.;
    sci_x_42 = -999.;
    sci_e_42 = 0.;
    sci_x_43 = -999.;
    sci_e_43 = 0.;
    sci_x_81 = -999.;
    sci_e_81 = 0.;

    // ::: SCI MHTDC :::: //

    if (temp_id_mhtdc_tof_s1s2 != nullptr) { delete[] temp_id_mhtdc_tof_s1s2; temp_id_mhtdc_tof_s1s2 = nullptr; }
    if (temp_id_mhtdc_beta_s1s2 != nullptr) { delete[] temp_id_mhtdc_beta_s1s2; temp_id_mhtdc_beta_s1s2 = nullptr; }
    if (id_mhtdc_gamma_s1s2 != nullptr) { delete[] id_mhtdc_gamma_s1s2; id_mhtdc_gamma_s1s2 = nullptr; }
    if (id_mhtdc_delta_s1s2 != nullptr) { delete[] id_mhtdc_delta_s1s2; id_mhtdc_delta_s1s2 = nullptr; }
    // if (id_mhtdc_aoq_s1s2 != nullptr) { delete[] id_mhtdc_aoq_s1s2; id_mhtdc_aoq_s1s2 = nullptr; }
    // if (id_mhtdc_aoq_corr_s1s2 != nullptr) { delete[] id_mhtdc_aoq_corr_s1s2; id_mhtdc_aoq_corr_s1s2 = nullptr; }
    // if (id_mhtdc_v_cor_music21 != nullptr) { delete[] id_mhtdc_v_cor_music21; id_mhtdc_v_cor_music21 = nullptr; }
    // if (id_mhtdc_z_music21 != nullptr) { delete[] id_mhtdc_z_music21; id_mhtdc_z_music21 = nullptr; }
    // if (id_mhtdc_z_shifted_music21 != nullptr) { delete[] id_mhtdc_z_shifted_music21; id_mhtdc_z_shifted_music21 = nullptr; }
    // if (id_mhtdc_v_cor_music22 != nullptr) { delete[] id_mhtdc_v_cor_music22; id_mhtdc_v_cor_music22 = nullptr; }
    // if (id_mhtdc_z_music22 != nullptr) { delete[] id_mhtdc_z_music22; id_mhtdc_z_music22 = nullptr; }
    // if (id_mhtdc_z_shifted_music22 != nullptr) { delete[] id_mhtdc_z_shifted_music22; id_mhtdc_z_shifted_music22 = nullptr; }

    if (temp_id_mhtdc_tof_s2s4 != nullptr) { delete[] temp_id_mhtdc_tof_s2s4; temp_id_mhtdc_tof_s2s4 = nullptr; }
    if (temp_id_mhtdc_beta_s2s4 != nullptr) { delete[] temp_id_mhtdc_beta_s2s4; temp_id_mhtdc_beta_s2s4 = nullptr; }
    if (temp_id_mhtdc_gamma_s2s4 != nullptr) { delete[] temp_id_mhtdc_gamma_s2s4; temp_id_mhtdc_gamma_s2s4 = nullptr; }
    if (id_mhtdc_delta_s2s4 != nullptr) { delete[] id_mhtdc_delta_s2s4; id_mhtdc_delta_s2s4 = nullptr; }
    // if (id_mhtdc_aoq_s2s4 != nullptr) { delete[] id_mhtdc_aoq_s2s4; id_mhtdc_aoq_s2s4 = nullptr; }
    // if (id_mhtdc_aoq_corr_s2s4 != nullptr) { delete[] id_mhtdc_aoq_corr_s2s4; id_mhtdc_aoq_corr_s2s4 = nullptr; }
    // if (id_mhtdc_v_cor_music41 != nullptr) { delete[] id_mhtdc_v_cor_music41; id_mhtdc_v_cor_music41 = nullptr; }
    // if (id_mhtdc_z_music41 != nullptr) { delete[] id_mhtdc_z_music41; id_mhtdc_z_music41 = nullptr; }
    // if (id_mhtdc_z_shifted_music41 != nullptr) { delete[] id_mhtdc_z_shifted_music41; id_mhtdc_z_shifted_music41 = nullptr; }
    // if (id_mhtdc_v_cor_music42 != nullptr) { delete[] id_mhtdc_v_cor_music42; id_mhtdc_v_cor_music42 = nullptr; }
    // if (id_mhtdc_z_music42 != nullptr) { delete[] id_mhtdc_z_music42; id_mhtdc_z_music42 = nullptr; }
    // if (id_mhtdc_z_shifted_music42 != nullptr) { delete[] id_mhtdc_z_shifted_music42; id_mhtdc_z_shifted_music42 = nullptr; }
    // if (id_mhtdc_v_cor_music43 != nullptr) { delete[] id_mhtdc_v_cor_music43; id_mhtdc_v_cor_music43 = nullptr; }
    // if (id_mhtdc_z_music43 != nullptr) { delete[] id_mhtdc_z_music43; id_mhtdc_z_music43 = nullptr; }
    // if (id_mhtdc_z_shifted_music43 != nullptr) { delete[] id_mhtdc_z_shifted_music43; id_mhtdc_z_shifted_music43 = nullptr; }
    // if (mhtdc_gamma1square_s2s4 != nullptr) { delete[] mhtdc_gamma1square_s2s4; mhtdc_gamma1square_s2s4 = nullptr; }
    // if (id_mhtdc_gamma_ta_s2s4 != nullptr) { delete[] id_mhtdc_gamma_ta_s2s4; id_mhtdc_gamma_ta_s2s4 = nullptr; }
    // if (id_mhtdc_dEdegoQ_s2s4 != nullptr) { delete[] id_mhtdc_dEdegoQ_s2s4; id_mhtdc_dEdegoQ_s2s4 = nullptr; }
    // if (id_mhtdc_dEdeg_z41 != nullptr) { delete[] id_mhtdc_dEdeg_z41; id_mhtdc_dEdeg_z41 = nullptr; }
    if (temp_s1x_mhtdc != nullptr) { delete[] temp_s1x_mhtdc; temp_s1x_mhtdc = nullptr; }
    if (temp_s2x_mhtdc != nullptr) { delete[] temp_s2x_mhtdc; temp_s2x_mhtdc = nullptr; }
    if (temp_s4x_mhtdc != nullptr) { delete[] temp_s4x_mhtdc; temp_s4x_mhtdc = nullptr; }
    
    // ::: MUSIC :::::::: //
    memset(music21_b_e, false, sizeof(music21_b_e));
    memset(music22_b_e, false, sizeof(music22_b_e));
    memset(music41_b_e, false, sizeof(music41_b_e));
    memset(music42_b_e, false, sizeof(music42_b_e));
    memset(music43_b_e, false, sizeof(music43_b_e));
    music21_anodes_cnt = 0;
    music22_anodes_cnt = 0;
    music41_anodes_cnt = 0;
    music42_anodes_cnt = 0;
    music43_anodes_cnt = 0;

    // ::: IDs :::::::::: //
    id_x1 = -999.;
    id_y1 = -999.;
    id_a1 = -999.;
    id_b1 = -999.;
    id_x2 = -999.;
    id_y2 = -999.;
    id_a2 = -999.;
    id_b2 = -999.;
    id_x4 = -999.;
    id_y4 = -999.;
    id_a4 = -999.;
    id_b4 = -999.;
    id_x8 = -999.;
    id_y8 = -999.;
    id_a8 = -999.;
    id_b8 = -999.;
    memset(id_rho, 0, sizeof(id_rho));
    memset(id_brho, 0, sizeof(id_brho));
    id_beta_s1s2 = 0.;
    id_beta_s2s4 = 0.;
    id_gamma_s1s2 = 0.;
    id_gamma_s2s4 = 0.;
    id_AoQ_s1s2 = 0.;
    id_AoQ_corr_s1s2 = 0.;
    id_AoQ_s2s4 = 0.;
    id_AoQ_corr_s2s4 = 0.;
    id_music21_v_cor = 0.;
    id_music22_v_cor = 0.;
    id_music41_v_cor = 0.;
    id_music42_v_cor = 0.;
    id_music43_v_cor = 0.;
    id_z21 = 0.;
    id_z22 = 0.;
    id_z41 = 0.;
    id_z42 = 0.;
    id_z43 = 0.;
    id_gamma_ta_s2s4 = 0.;
    id_dEdegoQ = 0.;
    id_dEdeg_z41 = 0.;
    id_b_x1 = false;
    id_b_x2 = false;
    id_b_x4 = false;
    id_b_AoQ_s1s2 = false;
    id_b_AoQ_s2s4 = false;
    id_b_z21 = false;
    id_b_z22 = false;
    id_b_z41 = false;
    id_b_z42 = false;
    id_b_z43 = false;

    //c4LOG(info, " tof clearing ");
    mhtdc_tof2111_selected.clear();
    mhtdc_tof2111.clear();
    mhtdc_tof4121_selected.clear();
    mhtdc_tof4121.clear();
    mhtdc_tof4122_selected.clear();
    mhtdc_tof4122.clear();
    mhtdc_tof4221_selected.clear();
    mhtdc_tof4221.clear();
    mhtdc_tof4321_selected.clear();
    mhtdc_tof4321.clear();
    mhtdc_tof3121_selected.clear();
    mhtdc_tof3121.clear();

    //c4LOG(info, " sci stuff clearing");
    mhtdc_sci11lr_dt_selected.clear();
    mhtdc_sci11lr_x_selected.clear();
    sci11l_hits_selected.clear();
    sci11r_hits_selected.clear();

    mhtdc_sci41lr_dt_selected.clear();
    mhtdc_sci41lr_x_selected.clear();
    sci41l_hits_selected.clear();
    sci41r_hits_selected.clear();

    mhtdc_sci11lr_x_tofs1s2_selected.clear();
    mhtdc_sci21lr_x_tofs1s2_selected.clear();
    mhtdc_sci21lr_x_tofs2s4_selected.clear();
    mhtdc_sci41lr_x_tofs2s4_selected.clear();

    sci11l_hits_tofs1s2_selected.clear();
    sci11r_hits_tofs1s2_selected.clear();
    sci21l_hits_tofs1s2_selected.clear();
    sci21r_hits_tofs1s2_selected.clear();
    sci21l_hits_tofs2s4_selected.clear();
    sci21r_hits_tofs2s4_selected.clear();
    sci41l_hits_tofs2s4_selected.clear();
    sci41r_hits_tofs2s4_selected.clear();

    //c4LOG(info, " stuff already there ");
    s1x_mhtdc.clear();
    s1a_mhtdc.clear();
    s2x_s1s2_mhtdc.clear();
    s2a_s1s2_mhtdc.clear();
    tof_s1s2_mhtdc.clear();
    beta_s1s2_mhtdc.clear();
    aoq_s1s2_mhtdc.clear();
    aoq_corr_s1s2_mhtdc.clear();
    z_music21_mhtdc.clear();
    z_music22_mhtdc.clear();

    s2x_s2s4_mhtdc.clear();
    s2a_s2s4_mhtdc.clear();
    s4x_mhtdc.clear();
    s4a_mhtdc.clear();
    tof_s2s4_mhtdc.clear();
    beta_s2s4_mhtdc.clear();
    aoq_s2s4_mhtdc.clear();
    aoq_corr_s2s4_mhtdc.clear();
    z_music41_mhtdc.clear();
    z_music42_mhtdc.clear();
    z_music43_mhtdc.clear();
    dEdegoQ_s2s4_mhtdc.clear();
    dEdeg_z41_mhtdc.clear();

    id_AoQs1s2_driftcorr = 0.;
    id_AoQs2s4_driftcorr = 0.;
    id_z21_driftcorr = 0.;
    id_z22_driftcorr = 0.;
    id_z41_driftcorr = 0.;
    id_z42_driftcorr = 0.;
    id_z43_driftcorr = 0.;

    id_mhtdc_beta_s1s2.clear();
    id_mhtdc_tof_s1s2.clear();
    id_mhtdc_aoq_s1s2.clear();
    id_mhtdc_aoq_corr_s1s2.clear();
    id_mhtdc_z_music21.clear();
    id_mhtdc_z_shifted_music21.clear();
    id_mhtdc_z_music22.clear();
    id_mhtdc_z_shifted_music22.clear();
    s1x_mhtdc.clear();
    s2x_s1s2_mhtdc.clear();
    s2x_s2s4_mhtdc.clear();
    s4x_mhtdc.clear();
    id_mhtdc_beta_s2s4.clear();
    id_mhtdc_tof_s2s4.clear();
    id_mhtdc_aoq_s2s4.clear();
    id_mhtdc_aoq_corr_s2s4.clear();
    id_mhtdc_z_music41.clear();
    id_mhtdc_z_shifted_music41.clear();
    id_mhtdc_z_music42.clear();
    id_mhtdc_z_shifted_music42.clear();
    id_mhtdc_z_music43.clear();
    id_mhtdc_z_shifted_music43.clear();
    id_mhtdc_dEdegoQ_s2s4.clear();
    id_mhtdc_dEdeg_z41.clear();

    //c4LOG(info, " End of Finish Event");
}

void FrsCal2Hit::FinishTask()
{
    c4LOG(info, Form("Wrote %i events. ", fNEvents));
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents);
    c4LOG(info, "aoqfrscal:: " << aoqfrscal);
}

ClassImp(FrsCal2Hit)
