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
    musicArray = mgr->InitObjectAs<decltype(musicArray)>("FrsMusicData");
    c4LOG_IF(fatal, !musicArray, "Branch FrsMusicData not found!");
    calTpcArray = mgr->InitObjectAs<decltype(calTpcArray)>("FrsCalTpcData");
    c4LOG_IF(fatal, !calTpcArray, "Branch FrsCalTpcData not found!");

    mgr->RegisterAny("FrsHitData", hitArray, !fOnline);
    mgr->RegisterAny("FrsMultiHitData", multihitArray, !fOnline);

   
    return kSUCCESS;
}

// :::: Main Execution Block ::: //
void FrsCal2Hit::Exec(Option_t* option)
{   
    if (tpatArray->size() == 0) return;
    fNEvents++;

    auto start = std::chrono::high_resolution_clock::now();

    auto const & tpatItem = tpatArray->at(0);
    wr_t = tpatItem.Get_wr_t();
    tpat = tpatItem.Get_tpat();

    auto & anaEntry = hitArray->emplace_back();
    anaEntry.SetMetaData(wr_t, tpat);

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

    anaEntry.SetSciData(sci_e_21,
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
    anaEntry.SetMusicData(de, de_cor);

    ProcessIDs();
    anaEntry.SetIDs(id_x2,
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
                    id_beta,
                    id_dEdeg,
                    id_dEdegoQ,
                    id_rho,
                    id_brho);

    FRS_time_mins = (wr_t - exp_config->exp_start_time) / 60E9;
    ProcessDriftCorrections();
    anaEntry.SetDriftCorrections(FRS_time_mins, id_AoQ_driftcorr, id_z_driftcorr);
    
    ProcessSci_MHTDC();
    ProcessIDs_MHTDC();    
        
    for (int i = 0; i < hits_in_beta_s2s4; i++)
    {
        for (int j = 0; j<hits_in_s2x; j ++)
        {
            if (temp_s2x_mhtdc[j] > - 200 &&  temp_s2x_mhtdc[j] < 200 &&
                id_mhtdc_beta_s2s4[i] > 0 && id_mhtdc_beta_s2s4[i] < 1 &&
                id_mhtdc_aoq_s2s4[i*hits_in_s2x + j] > 1.0 && id_mhtdc_aoq_s2s4[i] < 3.5)
            {
                auto & multihitEntry = multihitArray->emplace_back();
                multihitEntry.SetAll(temp_s2x_mhtdc[j],
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
                                    id_mhtdc_dEdegoQ[i*hits_in_s2x + j]);
                multihitEntry.SetMetaData(wr_t, tpat);
            }
        }
    }
   
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
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
    sci_b_x_21 = ((sci_x_21 > -100) && (sci_tx_21lr < 100));

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
    // Calibrated ToF
    /*-----------------------------------*/
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

    // SCI 21 L and R
    sci21l_hits = calSciItem.Get_mhtdc_sci21l_hits();
    hits_in_21l = sci21l_hits.size();
    sci21r_hits = calSciItem.Get_mhtdc_sci21r_hits();
    hits_in_21r = sci21r_hits.size();
    hits_in_21lr = hits_in_21l * hits_in_21r;

    mhtdc_sc21lr_dt = new Float_t[hits_in_21lr];
    mhtdc_sc21lr_x = new Float_t[hits_in_21lr];
    for (int i = 0; i < hits_in_21l; i++)
    {
        for (int j = 0; j < hits_in_21r; j ++)
        {
            mhtdc_sc21lr_dt[i * hits_in_21r + j] = sci->mhtdc_factor_ch_to_ns * (rand3() + sci21l_hits[i] - sci21r_hits[j]);
            mhtdc_sc21lr_x[i * hits_in_21r + j] = mhtdc_sc21lr_dt[i * hits_in_21r + j] * sci->mhtdc_factor_21l_21r + sci->mhtdc_offset_21l_21r;
        }
    }

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
    sci22l_hits = calSciItem.Get_mhtdc_sci22l_hits();
    hits_in_22l = sci22l_hits.size();
    sci22r_hits = calSciItem.Get_mhtdc_sci22r_hits();
    hits_in_22r = sci22r_hits.size();
    hits_in_22lr = hits_in_22l * hits_in_22r;

    mhtdc_sc22lr_dt = new Float_t[hits_in_22lr];
    mhtdc_sc22lr_x = new Float_t[hits_in_22lr];
    for (int i = 0; i < hits_in_22l; i++)
    {
        for (int j = 0; j < hits_in_22r; j ++)
        {
            mhtdc_sc22lr_dt[i * hits_in_22r + j] = sci->mhtdc_factor_ch_to_ns * (rand3() + sci22l_hits[i] - sci22r_hits[j]);
            mhtdc_sc22lr_x[i * hits_in_22r + j] = mhtdc_sc22lr_dt[i * hits_in_22r + j] * sci->mhtdc_factor_22l_22r + sci->mhtdc_offset_22l_22r;
        }
        if (i == 0)
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

    // SCI 41 L and R
    sci41l_hits = calSciItem.Get_mhtdc_sci41l_hits();
    int hits_in_41l = sci41l_hits.size();
    sci41r_hits = calSciItem.Get_mhtdc_sci41r_hits();
    int hits_in_41r = sci41r_hits.size();
    int hits_in_41lr = hits_in_41l * hits_in_41r;

    mhtdc_sc41lr_dt = new Float_t[hits_in_41lr];
    mhtdc_sc41lr_x = new Float_t[hits_in_41lr];
    for (int i = 0; i < hits_in_41l; i++)
    {
        for (int j = 0; j < hits_in_41r; j ++)
        {
            mhtdc_sc41lr_dt[i * hits_in_41r + j] = sci->mhtdc_factor_ch_to_ns * (rand3() + sci41l_hits[i] - sci41r_hits[j]);
            mhtdc_sc41lr_x[i * hits_in_41r + j] = mhtdc_sc41lr_dt[i * hits_in_41r + j] * sci->mhtdc_factor_41l_41r + sci->mhtdc_offset_41l_41r;
        }
    }

    // SCI 42 L and R
    sci42l_hits = calSciItem.Get_mhtdc_sci42l_hits();
    int hits_in_42l = sci42l_hits.size();
    sci42r_hits = calSciItem.Get_mhtdc_sci42r_hits();
    int hits_in_42r = sci42r_hits.size();
    int hits_in_42lr = hits_in_42l * hits_in_42r;

    mhtdc_sc42lr_dt = new Float_t[hits_in_42lr];
    mhtdc_sc42lr_x = new Float_t[hits_in_42lr];
    for (int i = 0; i < hits_in_42l; i++)
    {
        for (int j = 0; j < hits_in_42r; j ++)
        {
            mhtdc_sc42lr_dt[i * hits_in_42r + j] = sci->mhtdc_factor_ch_to_ns * (rand3() + sci42l_hits[i] - sci42r_hits[j]);
            mhtdc_sc42lr_x[i * hits_in_42r + j] = mhtdc_sc42lr_dt[i*hits_in_42r + j] * sci->mhtdc_factor_42l_42r + sci->mhtdc_offset_42l_42r;
        }
    }    
    
    // SCI 43 L and R
    sci43l_hits = calSciItem.Get_mhtdc_sci43l_hits();
    int hits_in_43l = sci43l_hits.size();
    sci43r_hits = calSciItem.Get_mhtdc_sci43r_hits();
    int hits_in_43r = sci43r_hits.size();
    int hits_in_43lr = hits_in_43l * hits_in_43r;

    mhtdc_sc43lr_dt = new Float_t[hits_in_43lr];
    mhtdc_sc43lr_x = new Float_t[hits_in_43lr];
    for (int i = 0; i < hits_in_43l; i++)
    {
        for (int j = 0; j < hits_in_43r; j ++)
        {
            mhtdc_sc43lr_dt[i * hits_in_43r + j] = sci->mhtdc_factor_ch_to_ns * (rand3() + sci43l_hits[i] - sci43r_hits[j]);
            mhtdc_sc43lr_x[i * hits_in_43r + j] = mhtdc_sc43lr_dt[i * hits_in_43r + j] * sci->mhtdc_factor_43l_43r + sci->mhtdc_offset_43l_43r;
        }
    }

    // SCI 31 L and R
    sci31l_hits = calSciItem.Get_mhtdc_sci31l_hits();
    int hits_in_31l = sci31l_hits.size();
    sci31r_hits = calSciItem.Get_mhtdc_sci31r_hits();
    int hits_in_31r = sci31r_hits.size();
    int hits_in_31lr = hits_in_31l * hits_in_31r;

    mhtdc_sc31lr_dt = new Float_t[hits_in_31lr];
    mhtdc_sc31lr_x = new Float_t[hits_in_31lr];
    for (int i = 0; i < hits_in_31l; i++)
    {
        for (int j = 0; j < hits_in_31r; j ++)
        {
            mhtdc_sc31lr_dt[i * hits_in_31r + j] = sci->mhtdc_factor_ch_to_ns * (rand3() + sci31l_hits[i] - sci31r_hits[j]);
            mhtdc_sc31lr_x[i * hits_in_31r + j] = mhtdc_sc31lr_dt[i * hits_in_31r + j] * sci->mhtdc_factor_31l_31r + sci->mhtdc_offset_31l_31r;
        }
    }

      
    //TOF:
    // 21 -> 41
    hits_in_tof4121 = hits_in_41lr * hits_in_21lr;
    mhtdc_tof4121 = new Float_t[hits_in_tof4121];
    for (int i = 0; i < hits_in_41l; i++)
    {
        for (int j = 0; j < hits_in_41r; j++)
        {
            for (int k = 0; k < hits_in_21l; k++) 
            {
                for (int l = 0; l < hits_in_21r; l++)
                {
                    if ((sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci41l_hits[i] - sci41r_hits[j]) < 200) && (sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci21l_hits[k] - sci21r_hits[l]) < 200))
                    {
                        mhtdc_tof4121[i * hits_in_41r * hits_in_21l * hits_in_21r + j * hits_in_21l * hits_in_21r + k * hits_in_21r + l] = sci->mhtdc_factor_ch_to_ns * (0.5 * (sci41l_hits[i] - sci41r_hits[j]) - 0.5 * (sci21l_hits[k] - sci21r_hits[l])) + sci->mhtdc_offset_41_21;
                    }
                    else
                    {
                        mhtdc_tof4121[i * hits_in_41r * hits_in_21l * hits_in_21r + j * hits_in_21l * hits_in_21r + k * hits_in_21r + l] = -999;
                    }
                }
            }
        }
    }

    // 22 -> 41
    hits_in_tof4122 = hits_in_41lr * hits_in_22lr;
    mhtdc_tof4122 = new Float_t[hits_in_tof4122];
    for (int i = 0; i < hits_in_41l; i++) 
    {
        for (int j = 0; j<hits_in_41r; j++)
        {
            for (int k = 0; k < hits_in_22l; k++) 
            {
                for (int l = 0; l<hits_in_22r; l++)
                {
                    if ((sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci41l_hits[i] - sci41r_hits[j]) < 40) && (sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci22l_hits[k] - sci22r_hits[l]) < 40))
                    {
                        mhtdc_tof4122[i * hits_in_41r * hits_in_22l*hits_in_22r + j * hits_in_22l * hits_in_22r + k * hits_in_22r + l] = sci->mhtdc_factor_ch_to_ns * (0.5 * (sci41l_hits[i] - sci41r_hits[j]) - 0.5 * (sci22l_hits[k] - sci22r_hits[l])) + sci->mhtdc_offset_41_22;
                    }
                    else
                    {
                        mhtdc_tof4122[i * hits_in_41r * hits_in_22l*hits_in_22r + j * hits_in_22l * hits_in_22r + k * hits_in_22r + l] = -999;
                    }
                }
            }
        }
    }

    // 21 -> 42
    hits_in_tof4221 = hits_in_42lr * hits_in_21lr;
    mhtdc_tof4221 = new Float_t[hits_in_tof4221];
    for (int i = 0; i < hits_in_42l; i++) 
    {
        for (int j = 0; j < hits_in_42r; j++)
        {
            for (int k = 0; k < hits_in_21l; k++) 
            {
                for (int l = 0; l < hits_in_21r; l++)
                {
                    if ((sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci42l_hits[i] - sci42r_hits[j]) < 40) && (sci->mhtdc_factor_ch_to_ns*TMath::Abs(sci21l_hits[k] - sci21r_hits[l]) < 40))
                    {
                        mhtdc_tof4221[i * hits_in_42r * hits_in_21l * hits_in_21r + j * hits_in_21l * hits_in_21r + k * hits_in_21r + l] = sci->mhtdc_factor_ch_to_ns * (0.5 * (sci42l_hits[i] - sci42r_hits[j]) - 0.5 * (sci21l_hits[k] - sci21r_hits[l])) + sci->mhtdc_offset_42_21;
                    }
                    else
                    {
                        mhtdc_tof4221[i * hits_in_42r * hits_in_21l * hits_in_21r + j * hits_in_21l * hits_in_21r + k * hits_in_21r + l] = -999;
                    }
                }
            }
        }
    }


    // 21 -> 43
    int hits_in_tof4321 = hits_in_43lr * hits_in_21lr;
    mhtdc_tof4321 = new Float_t[hits_in_tof4321];
    for (int i = 0; i < hits_in_43l; i++) 
    {
        for (int j = 0; j < hits_in_43r; j++)
        {
            for (int k = 0; k < hits_in_21l; k++) 
            {
                for (int l = 0; l < hits_in_21r; l++)
                {
                    mhtdc_tof4321[i * hits_in_43r * hits_in_21l * hits_in_21r + j * hits_in_21l*hits_in_21r + k*hits_in_21r + l] = sci->mhtdc_factor_ch_to_ns * (0.5 * (sci43l_hits[i] - sci43r_hits[j]) - 0.5 * (sci21l_hits[k] - sci21r_hits[l])) + sci->mhtdc_offset_43_21;
                }
            }
        }
    }
    
    // 21 -> 31
    int hits_in_tof3121 = hits_in_31lr * hits_in_21lr;
    mhtdc_tof3121 = new Float_t[hits_in_tof3121];
    for (int i = 0; i < hits_in_31l; i++) 
    {
        for (int j = 0; j < hits_in_31r; j++)
        {
            for (int k = 0; k < hits_in_21l; k++) 
            {
                for (int l = 0; l < hits_in_21r; l++)
                {
                    mhtdc_tof3121[i * hits_in_31r * hits_in_21l * hits_in_21r + j * hits_in_21l * hits_in_21r + k * hits_in_21r + l] = sci->mhtdc_factor_ch_to_ns * (0.5 * (sci31l_hits[i] - sci31r_hits[j]) - 0.5 * (sci21l_hits[k] - sci21r_hits[l])) + sci->mhtdc_offset_31_21;
                }
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
    auto const & musicItem = musicArray->at(0);

    musicE = musicItem.Get_music_e();
    musicT = musicItem.Get_music_t();
    
    // For now, we can't loop over # of musics, because frs_setup file can't handle
    for (int i = 0; i < 8; i++)
    {
        if (musicE[0][i] > 4)
        {
            if (music->exclude_de1_adc_channel[i] == kTRUE) music_b_e[0][i] = false;
            else music_b_e[0][i] = ((musicE[0][i] > 100) && (musicE[0][i] < 4086)); // could set in TFrsConfig later
            
            if (music_b_e[0][i]) music_anodes_count[0]++;
        }

        if (musicT[0][i] > 0)
        {
            music_b_t[0][i] = ((musicT[0][i] > 10) && (musicT[0][i] < 4086));
        }

        if (musicE[1][i] > 4)
        {
            if (music->exclude_de2_adc_channel[i] == kTRUE) music_b_e[1][i] = false;
            else music_b_e[1][i] = ((musicE[1][i] > 10) && (musicE[1][i] < 4086));
            
            if (music_b_e[1][i]) music_anodes_count[1]++;
        }

        if (musicT[1][i] > 0)
        {
            music_b_t[1][i] = ((musicT[1][i] > 10) && (musicT[1][i] < 4086));
        }
    }
    

    #ifndef MUSIC_ANA_NEW
    if (music_anodes_count[0] == 8)
    {
        // What is up with the indexing here??
        //Float_t r1 = ((musicE[0][0]) * music->e1_gain[0] + music->e1_off[0]) * ((musicE[0][1]) * music->e1_gain[1] + music->e1_off[1]);
        Float_t r1 = ((musicE[0][1]) * music->e1_gain[1] + music->e1_off[1]) * ((musicE[0][1]) * music->e1_gain[1] + music->e1_off[1]);
        Float_t r2 = ((musicE[0][2]) * music->e1_gain[2] + music->e1_off[2]) * ((musicE[0][3]) * music->e1_gain[3] + music->e1_off[3]);
        Float_t r3 = ((musicE[0][4]) * music->e1_gain[4] + music->e1_off[4]) * ((musicE[0][5]) * music->e1_gain[5] + music->e1_off[5]);
        //Float_t r4 = ((musicE[0][6]) * music->e1_gain[6] + music->e1_off[6]) * ((musicE[0][7]) * music->e1_gain[7] + music->e1_off[7]);
        Float_t r4 = ((musicE[0][6]) * music->e1_gain[6] + music->e1_off[6]) * ((musicE[0][6]) * music->e1_gain[6] + music->e1_off[6]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            b_de[0] = kTRUE;
            de[0] = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            de_cor[0] = de[0];
        }
    }
    #endif

    #ifdef MUSIC_ANA_NEW
    if (music_anodes_count[0] >= 4)
    {
        float temp_de = 1.0;
        int temp_count = 0;
        for (int i = 0; i < 8; i++)
        {
            if (music_b_e[0][i])
            {
                temp_de *= ((musicE[0][i]) * music->e1_gain[i] + music->e1_off[i]);
                temp_count++;
            }
        }
        de[0] = TMath::Power(temp_de, 1. / ((float)(temp_count)));
        de_cor[0] = de[0];
        b_de[0] = kTRUE;
    }
    #endif

    #ifndef MUSIC_ANA_NEW
    if (music_anodes_count[1] == 8)
    {
        Float_t r1 = ((musicE[1][0]) * music->e2_gain[0] + music->e2_off[0]) * ((musicE[1][1]) * music->e2_gain[1] + music->e2_off[1]);
        Float_t r2 = ((musicE[1][2]) * music->e2_gain[2] + music->e2_off[2]) * ((musicE[1][3]) * music->e2_gain[3] + music->e2_off[3]);
        Float_t r3 = ((musicE[1][4]) * music->e2_gain[4] + music->e2_off[4]) * ((musicE[1][5]) * music->e2_gain[5] + music->e2_off[5]);
        Float_t r4 = ((musicE[1][6]) * music->e2_gain[6] + music->e2_off[6]) * ((musicE[1][7]) * music->e2_gain[7] + music->e2_off[7]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            b_de[1] = kTRUE;
            de[1] = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            de_cor[1] = de[1];
        }
    }
    #endif

    #ifdef MUSIC_ANA_NEW
    if (music_anodes_count[1] >= 4)
    {
        float temp_de = 1.0;
        int temp_count = 0;
        for (int i = 0; i < 8; i++)
        {
            if (music_b_e[1][i])
            {
                temp_de *= ((musicE[1][i]) * music->e2_gain[i] + music->e2_off[i]);
                temp_count++;
            }
        }
        de[1] = TMath::Power(temp_de, 1. / ((float)(temp_count)));
        de_cor[1] = de[1];
        b_de[1] = kTRUE;
    }
    #endif
}

void FrsCal2Hit::ProcessIDs()
{
    // Calculation of dE and Z from MUSIC41
    // Calibration for MUSIC is done with 1/b2 - last update sept2024
    
    auto const & calTpcItem = calTpcArray->at(0);
    b_tpc_xy = calTpcItem.Get_b_tpc_xy();

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
            id_AoQ_corr = id_AoQ - id->a4AoQCorr * id_a4;
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
        float power = 1.;
        float sum = 0.;
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

            if (music41_tac_z_gain_shifts != nullptr){
                id_z = id_z + music41_tac_z_gain_shifts->GetGain((uint64_t)wr_t);
            }

        }
        if ((id_z > 0.0) && (id_z < 100.0))
        {
            id_b_z = kTRUE;
        }
    }

    // S4 (MUSIC 2)
    if ((de[1] > 0.0) && (id_beta > 0.0) && (id_beta < 1.0))
    {
        float power = 1.;
        float sum = 0.;
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

            if (music42_tac_z_gain_shifts != nullptr){
                id_z2 = id_z2 + music42_tac_z_gain_shifts->GetGain((uint64_t)wr_t);
            }
        }
        if ((id_z2 > 0.0) && (id_z2 < 100.0))
        {   
            // CEJ: this seems out of order to me, gain matching first?
            id_b_z2 = kTRUE;
        }
    }


    float gamma1square = 1.0 + TMath::Power(((1 / aoq_factor) * (id_brho[0] / id_AoQ)), 2);
    id_gamma_ta_s2 = TMath::Sqrt(gamma1square);
    id_dEdegoQ = (id_gamma_ta_s2 - id_gamma) * id_AoQ;
    id_dEdeg = id_dEdegoQ * id_z;

}

void FrsCal2Hit::ProcessIDs_MHTDC()
{
    auto const & calTpcItem = calTpcArray->at(0);
    b_tpc_xy = calTpcItem.Get_b_tpc_xy();

    
    Float_t temp_s8x = mhtdc_sc81lr_x[0]; // NB mhtdc! ??
    temp_s4x = -999.;
    temp_a4 = -999;
    if (b_tpc_xy[4] && b_tpc_xy[5])
    {
        temp_s4x = calTpcItem.Get_tpc_x_s4();
        temp_a4 = calTpcItem.Get_tpc_angle_x_s4();
    }

    //float temp_s2x = -999.;
    temp_a2 = 0;
    hits_in_s2x = 0;

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
            temp_s2x_mhtdc[0] = calTpcItem.Get_tpc_x_s2_foc_23_24();
            temp_a2 = calTpcItem.Get_tpc_angle_x_s2_foc_23_24();
        }
        else if (b_tpc_xy[1] && b_tpc_xy[3])
        {
            temp_s2x_mhtdc[0] = calTpcItem.Get_tpc_x_s2_foc_22_24();
            temp_a2 = calTpcItem.Get_tpc_angle_x_s2_foc_22_24();
        }
        else if (b_tpc_xy[0] && b_tpc_xy[1])
        {
            temp_s2x_mhtdc[0] = calTpcItem.Get_tpc_x_s2_foc_21_22();
            temp_a2 = calTpcItem.Get_tpc_angle_x_s2_foc_21_22();
        }
        hits_in_s2x = 1;
    }

    //   S2S4 MultihitTDC ID analysis
    float mean_brho_s2s4 = 0.5 * (frs->bfield[2] + frs->bfield[3]);

    hits_in_beta_s2s4 = 0;
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
            }
            else id_mhtdc_beta_s2s4[i] = 0;
            
        }
    }else if (id->tof_s4_select == 2)
    {
        hits_in_beta_s2s4 = hits_in_tof4221;            
        id_mhtdc_beta_s2s4 = new Float_t[hits_in_tof4221];
        id_mhtdc_tof_s2s4 = new Float_t[hits_in_tof4221];
        for (int i = 0; i < hits_in_tof4221; i++)
        {
            id_mhtdc_tof_s2s4[i] = mhtdc_tof4221[i];
            if (mhtdc_tof4221[i] > 0)
            {
                id_mhtdc_beta_s2s4[i] = (id->mhtdc_length_sc2142 / mhtdc_tof4221[i]);
            }else{
                id_mhtdc_beta_s2s4[i] = 0;
            }
        }
    }
    else if (id->tof_s4_select == 3)
    {
        hits_in_beta_s2s4 = hits_in_tof4122;            
        id_mhtdc_beta_s2s4 = new Float_t[hits_in_tof4122];
        id_mhtdc_tof_s2s4 = new Float_t[hits_in_tof4122];
        for (int i = 0; i < hits_in_tof4122; i++)
        {
            id_mhtdc_tof_s2s4[i] = mhtdc_tof4122[i];
            if (mhtdc_tof4122[i] > 0)
            {
                id_mhtdc_beta_s2s4[i] = (id->mhtdc_length_sc2241 / mhtdc_tof4122[i])/speed_light;
            }
            else id_mhtdc_beta_s2s4[i] = 0;
            
        }
    }
    else c4LOG(fatal, "Unrecognized option, tof_s4_select != 1 || 3?.");
    

    // calculate delta (momentum deviation) and AoQ
    int hits_in_aoq = hits_in_beta_s2s4 * hits_in_s2x;
    id_mhtdc_gamma_s2s4 = new Float_t[hits_in_beta_s2s4];
    id_mhtdc_delta_s2s4 = new Float_t[hits_in_aoq];
    id_mhtdc_aoq_s2s4 = new Float_t[hits_in_aoq];
    id_mhtdc_aoq_corr_s2s4 = new Float_t[hits_in_aoq];

    for (int i = 0; i < hits_in_beta_s2s4; i++)
    {
        id_mhtdc_gamma_s2s4[i] = 1. / sqrt(1. - id_mhtdc_beta_s2s4[i] * id_mhtdc_beta_s2s4[i]);
        
        for (int j = 0; j < hits_in_s2x; j++)
        {
            if (temp_s4x > -200. && temp_s4x < 200. && temp_s2x_mhtdc[j] > -200. && temp_s2x_mhtdc[j] < 200.)
            {

                id_mhtdc_delta_s2s4[i*hits_in_s2x + j] = (temp_s4x - (temp_s2x_mhtdc[j] * frs->magnification[1])) / (1.0 * frs->dispersion[1] * 1000.0); // metre to mm
                
                if (id->x_s2_select == 2 && id->tof_s4_select == 1)
                {
                    // need to make sure that beta and s2x are from the same time stamp (i.e. a time gate is needed)
                    int time_stamp_sc21r_x = sci21r_hits[j % hits_in_21r];
                    int time_stamp_sc21r_beta = sci21r_hits[i % hits_in_21r];
                    if (TMath::Abs(time_stamp_sc21r_beta - time_stamp_sc21r_x) > 500)
                    {
                        id_mhtdc_aoq_s2s4[i*hits_in_s2x + j] = -999;
                        id_mhtdc_aoq_corr_s2s4[i*hits_in_s2x + j] = -999;
                        continue;
                    }
                }
                else if (id->x_s2_select == 3 && id->tof_s4_select == 3){ // need to make sure that beta and s2x are from the same time stamp (i.e. a time gate is needed)
                    int time_stamp_sc22r_x = sci21r_hits[j%hits_in_22r];
                    int time_stamp_sc22r_beta = sci21r_hits[i%hits_in_22r];
                    if (TMath::Abs(time_stamp_sc22r_beta - time_stamp_sc22r_x) > 500){
                        id_mhtdc_aoq_s2s4[i*hits_in_s2x + j] = -999;
                        id_mhtdc_aoq_corr_s2s4[i*hits_in_s2x + j] = -999;
                        continue;
                    }
                }

                if (id_mhtdc_beta_s2s4[i] > 0.1 && id_mhtdc_beta_s2s4[i] < 1)
                {
                    id_mhtdc_aoq_s2s4[i * hits_in_s2x + j] = mean_brho_s2s4 * (1. - id_mhtdc_delta_s2s4[i * hits_in_s2x + j]) * temp_tm_to_MeV / (temp_mu * id_mhtdc_beta_s2s4[i] * id_mhtdc_gamma_s2s4[i]);

                    // using angle at S4 to correct AoQ
                    id_mhtdc_aoq_corr_s2s4[i * hits_in_s2x + j] = id_mhtdc_aoq_s2s4[i * hits_in_s2x + j] - id->a4AoQCorr * temp_a4;

                }
                else
                {
                    id_mhtdc_aoq_s2s4[i * hits_in_s2x + j] = -999;
                    id_mhtdc_aoq_corr_s2s4[i * hits_in_s2x + j] = -999;
                }
            }
            else
            {
                id_mhtdc_aoq_s2s4[i * hits_in_s2x + j] = -999;
                id_mhtdc_aoq_corr_s2s4[i * hits_in_s2x + j] = -999;
            }
        }
    }

    id_mhtdc_v_cor_music41 = new Float_t[hits_in_beta_s2s4];
    id_mhtdc_v_cor_music42 = new Float_t[hits_in_beta_s2s4];

    id_mhtdc_z_music41 = new Float_t[hits_in_beta_s2s4];
    id_mhtdc_z_music42 = new Float_t[hits_in_beta_s2s4];

    for (int i = 0; i < hits_in_beta_s2s4; i++)
    {
        float temp_music41_de = de_cor[0] > 0.0;
        if ((temp_music41_de > 0.0) && (id_mhtdc_beta_s2s4[i] > 0.0) && (id_mhtdc_beta_s2s4[i] < 1.0))
        {
            float power = 1.;
            float sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->mhtdc_vel_a_music41[j];
                power *= id_mhtdc_beta_s2s4[i]; // to be consistent with the FRS convention from the TAC - this means in principle the vel_a coeffs are the same for MHTDC and TAC (which they should be given that beta is the same).
            }
            id_mhtdc_v_cor_music41[i] = sum;

            
            if (id_mhtdc_v_cor_music41[i] > 0.0)
            {
                id_mhtdc_z_music41[i] = frs->primary_z * sqrt(de_cor[0] / id_mhtdc_v_cor_music41[i]) + id->mhtdc_offset_z_music41;

                if (music41_mhtdc_z_gain_shifts != nullptr){
                id_mhtdc_z_music41[i] = id_mhtdc_z_music41[i]  + music41_mhtdc_z_gain_shifts->GetGain((uint64_t)wr_t);
                //c4LOG(info,Form("music41_mhtdc_z_gain_shifts->GetGain((uint64_t)wr_t) = %f",music41_mhtdc_z_gain_shifts->GetGain((uint64_t)wr_t)));
                }
            } // else???
        }

        float temp_music42_de = de_cor[1] > 0.0;
        if((temp_music42_de > 0.0)  && (id_mhtdc_beta_s2s4[i] > 0.0) && (id_mhtdc_beta_s2s4[i] < 1.0))
        {
            float power = 1.;
            float sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->mhtdc_vel_a_music42[j];
                power *= id_mhtdc_beta_s2s4[i];
                //power *= 1.0/(id_mhtdc_beta_s2s4[i]*id_mhtdc_beta_s2s4[i]);
            }
            id_mhtdc_v_cor_music42[i] = sum;
            
            if (id_mhtdc_v_cor_music42[i] > 0.0)
            {
                id_mhtdc_z_music42[i] = frs->primary_z * sqrt(de_cor[1] / id_mhtdc_v_cor_music42[i]) + id->mhtdc_offset_z_music42;

                if (music42_mhtdc_z_gain_shifts != nullptr){
                id_mhtdc_z_music42[i] = id_mhtdc_z_music42[i] + music42_mhtdc_z_gain_shifts->GetGain((uint64_t)wr_t);
                //c4LOG(info,Form("music42_mhtdc_z_gain_shifts->GetGain((uint64_t)wr_t) = %f",music42_mhtdc_z_gain_shifts->GetGain((uint64_t)wr_t)));
                }
            }
        }

    }

    mhtdc_gamma1square = new Float_t[hits_in_aoq];
    id_mhtdc_gamma_ta_s2 = new Float_t[hits_in_aoq];
    id_mhtdc_dEdegoQ = new Float_t[hits_in_aoq];
    id_mhtdc_dEdeg = new Float_t[hits_in_aoq];
    id_mhtdc_brho0 = new Float_t[hits_in_s2x];
    id_mhtdc_rho0 = new Float_t[hits_in_s2x];
 
    for (int i = 0; i < hits_in_beta_s2s4; i++)
    {        
        for (int j = 0; j<hits_in_s2x; j++){
            if (id_mhtdc_aoq_s2s4[i*hits_in_s2x + j] > 0) // ELSE????
            {
                id_mhtdc_brho0[j] = frs->rho0[0] * (1. - temp_s2x_mhtdc[j] / 1000. / frs->dispersion[0]);
                id_mhtdc_rho0[j] = (fabs(frs->bfield[0]) + fabs(frs->bfield[1])) / 2. * id_mhtdc_brho0[j];

                mhtdc_gamma1square[i*hits_in_s2x + j] = 1.0 + TMath::Power(((1.0 / aoq_factor) * (id_mhtdc_rho0[j] / id_mhtdc_aoq_s2s4[i*hits_in_s2x + j])), 2);
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



}

void FrsCal2Hit::ProcessDriftCorrections()
{
    // CEJ: can be tidied/reconfigured some later
    if (frs_config->AoQDriftLoaded())
    {
        id_AoQ_driftcorr = 0.;
        double drift_aoq = 0.0;
        double drift_aoq_error = 0.0;
        int nentry_aoq = 0;
        int aoq_frs_wr_time_a = 0; 
        int aoq_frs_wr_time_b = 0;
        double aoq_reference_value = 2.39;   //!!!! read from exp configuration - expected value
        int bin = 20;  
        
        std::map<int,std::pair<double,double>> aoq_drift = frs_config->AoQDriftCoefficients();
        for (const auto& entry : aoq_drift)
        {   
            int aoq_frs_wr_time = entry.first;
            std::pair<double,double> aoq_coeffs = entry.second;
            drift_aoq = aoq_coeffs.first;
            drift_aoq_error = aoq_coeffs.second;

            double aoq_shift = drift_aoq - aoq_reference_value;
            
            if ((FRS_time_mins >= (aoq_frs_wr_time - bin/2)) && (FRS_time_mins < (aoq_frs_wr_time + bin/2)))
            {
                id_AoQ_driftcorr = id_AoQ - aoq_shift;
            }
            
            nentry_aoq++;
        }

    }

    if (frs_config->Z1DriftLoaded())
    {
        id_z_driftcorr = 0.;
        double drift_z1 = 0.0;
        double drift_z1_error = 0.0;
        int nentry_z1 = 0;
        int z1_frs_wr_time_a = 0; 
        int z1_frs_wr_time_b = 0;
        double z1_reference_value = 41;     //!!!! read from exp configuration - expected value
        int bin = 20;                       //!!!! read from drift file

        std::map<int,std::pair<double,double>> z1_drift = frs_config->Z1DriftCoefficients();
        for (const auto& entry : z1_drift)
        {  
            int z1_frs_wr_time = entry.first;
            std::pair<double,double> z1_coeffs = entry.second;
            drift_z1 = z1_coeffs.first;
            drift_z1_error = z1_coeffs.second;

            double z1_shift = drift_z1 - z1_reference_value;

            if ((FRS_time_mins >= (z1_frs_wr_time - bin/2)) && (FRS_time_mins < (z1_frs_wr_time + bin/2)))
            {
                id_z_driftcorr = id_z - z1_shift;
            }
            
            nentry_z1++;
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
    if (mhtdc_sc21lr_dt != nullptr) { delete[] mhtdc_sc21lr_dt; mhtdc_sc21lr_dt = nullptr; }
    if (mhtdc_sc22lr_dt != nullptr) { delete[] mhtdc_sc22lr_dt; mhtdc_sc22lr_dt = nullptr; }
    if (mhtdc_sc31lr_dt != nullptr) { delete[] mhtdc_sc31lr_dt; mhtdc_sc31lr_dt = nullptr; }
    if (mhtdc_sc41lr_dt != nullptr) { delete[] mhtdc_sc41lr_dt; mhtdc_sc41lr_dt = nullptr; }
    if (mhtdc_sc42lr_dt != nullptr) { delete[] mhtdc_sc42lr_dt; mhtdc_sc42lr_dt = nullptr; }
    if (mhtdc_sc43lr_dt != nullptr) { delete[] mhtdc_sc43lr_dt; mhtdc_sc43lr_dt = nullptr; }
    if (mhtdc_sc81lr_dt != nullptr) { delete[] mhtdc_sc81lr_dt; mhtdc_sc81lr_dt = nullptr; }
    if (mhtdc_sc21lr_x != nullptr) { delete[] mhtdc_sc21lr_x; mhtdc_sc21lr_x = nullptr; }
    if (mhtdc_sc22lr_x != nullptr) { delete[] mhtdc_sc22lr_x; mhtdc_sc22lr_x = nullptr; }
    if (mhtdc_sc31lr_x != nullptr) { delete[] mhtdc_sc31lr_x; mhtdc_sc31lr_x = nullptr; }
    if (mhtdc_sc41lr_x != nullptr) { delete[] mhtdc_sc41lr_x; mhtdc_sc41lr_x = nullptr; }
    if (mhtdc_sc42lr_x != nullptr) { delete[] mhtdc_sc42lr_x; mhtdc_sc42lr_x = nullptr; }
    if (mhtdc_sc43lr_x != nullptr) { delete[] mhtdc_sc43lr_x; mhtdc_sc43lr_x = nullptr; }
    if (mhtdc_sc81lr_x != nullptr) { delete[] mhtdc_sc81lr_x; mhtdc_sc81lr_x = nullptr; }
    if (mhtdc_tof4121 != nullptr) { delete[] mhtdc_tof4121; mhtdc_tof4121 = nullptr; }
    if (mhtdc_tof4122 != nullptr) { delete[] mhtdc_tof4122; mhtdc_tof4122 = nullptr; }
    if (mhtdc_tof4221 != nullptr) { delete[] mhtdc_tof4221; mhtdc_tof4221 = nullptr; }
    if (mhtdc_tof4321 != nullptr) { delete[] mhtdc_tof4321; mhtdc_tof4321 = nullptr; }
    if (mhtdc_tof8121 != nullptr) { delete[] mhtdc_tof8121; mhtdc_tof8121 = nullptr; }
    if (mhtdc_tof3121 != nullptr) { delete[] mhtdc_tof3121; mhtdc_tof3121 = nullptr; }
    if (id_mhtdc_beta_s2s4 != nullptr) { delete[] id_mhtdc_beta_s2s4; id_mhtdc_beta_s2s4 = nullptr; }
    if (id_mhtdc_gamma_s2s4 != nullptr) { delete[] id_mhtdc_gamma_s2s4; id_mhtdc_gamma_s2s4 = nullptr; }
    if (id_mhtdc_delta_s2s4 != nullptr) { delete[] id_mhtdc_delta_s2s4; id_mhtdc_delta_s2s4 = nullptr; }
    if (id_mhtdc_aoq_s2s4 != nullptr) { delete[] id_mhtdc_aoq_s2s4; id_mhtdc_aoq_s2s4 = nullptr; }
    if (id_mhtdc_aoq_corr_s2s4 != nullptr) { delete[] id_mhtdc_aoq_corr_s2s4; id_mhtdc_aoq_corr_s2s4 = nullptr; }
    if (id_mhtdc_z_music41 != nullptr) { delete[] id_mhtdc_z_music41; id_mhtdc_z_music41 = nullptr; }
    if (id_mhtdc_zcor_music41 != nullptr) { delete[] id_mhtdc_zcor_music41; id_mhtdc_zcor_music41 = nullptr; }
    if (id_mhtdc_v_cor_music41 != nullptr) { delete[] id_mhtdc_v_cor_music41; id_mhtdc_v_cor_music41 = nullptr; }
    if (id_mhtdc_z_music42 != nullptr) { delete[] id_mhtdc_z_music42; id_mhtdc_z_music42 = nullptr; }
    if (id_mhtdc_zcor_music42 != nullptr) { delete[] id_mhtdc_zcor_music42; id_mhtdc_zcor_music42 = nullptr; }
    if (id_mhtdc_v_cor_music42 != nullptr) { delete[] id_mhtdc_v_cor_music42; id_mhtdc_v_cor_music42 = nullptr; }
    if (id_mhtdc_dEdegoQ!=nullptr) { delete[] id_mhtdc_dEdegoQ; id_mhtdc_dEdegoQ = nullptr; }
    if (id_mhtdc_rho0!=nullptr) { delete[] id_mhtdc_rho0; id_mhtdc_rho0 = nullptr; }
    if (id_mhtdc_brho0!=nullptr) { delete[] id_mhtdc_brho0; id_mhtdc_brho0 = nullptr; }
    if (id_mhtdc_gamma_ta_s2!=nullptr) { delete[] id_mhtdc_gamma_ta_s2; id_mhtdc_gamma_ta_s2 = nullptr; }
    if (mhtdc_gamma1square!=nullptr) { delete[] mhtdc_gamma1square; mhtdc_gamma1square = nullptr; }
    if (id_mhtdc_dEdeg!=nullptr) { delete[] id_mhtdc_dEdeg; id_mhtdc_dEdeg = nullptr; }
    if (temp_s2x_mhtdc!=nullptr) { delete[] temp_s2x_mhtdc; temp_s2x_mhtdc = nullptr; }
    if (id_mhtdc_tof_s2s4!=nullptr) { delete[] id_mhtdc_tof_s2s4; id_mhtdc_tof_s2s4 = nullptr; }
    
    // ::: MUSIC :::::::: //
    memset(music_anodes_count, 0, sizeof(music_anodes_count));
    memset(music_b_e, false, sizeof(music_b_e));
    memset(music_b_t, false, sizeof(music_b_t));

    // ::: IDs :::::::::: //
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
    id_beta = 0.;
    id_gamma = 0.;
    id_AoQ = 0.;
    id_AoQ_corr = 0.;
    id_v_cor = 0.;
    id_v_cor2 = 0.;
    id_z = 0.;
    id_z2 = 0.;
    id_gamma_ta_s2 = 0.;
    id_dEdegoQ = 0.;
    id_dEdeg = 0.;
    id_b_x2 = false;
    id_b_x4 = false;
    id_b_AoQ = false;
    id_b_z = false;
    id_b_z2 = false;

    id_AoQ_driftcorr = 0.;
    id_z_driftcorr = 0.;

    
    
}

void FrsCal2Hit::FinishTask()
{
    c4LOG(info, Form("Wrote %i events. ", fNEvents));
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents);
}

ClassImp(FrsCal2Hit)
