// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "TravMusCal2Ana.h"
#include "c4Logger.h"

#include <vector>
#include <iostream>
#include "TMath.h"

// change to some config option
#define TRAVMUS_TAC_OR_MHTDC

TravMusCal2Ana::TravMusCal2Ana()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   travMusArray(nullptr)
    ,   anaArray(new std::vector<TravMusAnaItem>)
{
    frs_config = TFrsConfiguration::GetInstance();
    music = frs_config->MUSIC();
}

TravMusCal2Ana::TravMusCal2Ana(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   travMusArray(nullptr)
    ,   anaArray(new std::vector<TravMusAnaItem>)
{
    frs_config = TFrsConfiguration::GetInstance();
    music = frs_config->MUSIC();
}

TravMusCal2Ana::~TravMusCal2Ana()
{
    c4LOG(info, "Deleting TravMusCal2Ana task");
}

InitStatus TravMusCal2Ana::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    travMusArray = mgr->InitObjectAs<decltype(travMusArray)>("TravMusCalData");
    c4LOG_IF(fatal, !travMusArray, "Branch TravMusCalData not found!");

    mgr->RegisterAny("TravMusAnaData", anaArray, !fOnline);
 
    return kSUCCESS;
}

void TravMusCal2Ana::Exec(Option_t* option)
{
    anaArray->clear();

    if (travMusArray->size() == 0) return;

    uint64_t wr_travmus = 0;
    auto const & travMusicItem = travMusArray->at(0);
    wr_travmus = travMusicItem.Get_wr_t();
    for (int i = 0; i < 8; i++) travmusic_t[i] = travMusicItem.Get_music_time(i);
    for (int i = 0; i < 8; i++) travmusic_e[i] = travMusicItem.Get_music_energy(i);

    travmusic_anodes_cnt = 0;

    for (int i = 0; i < 8; i++)
    {
        if (travmusic_e[i] > 4)
        {
            if (music->exclude_de3_adc_channel[i] == kTRUE) travmusic_b_e[i] = false;
            //else travmusic_b_e[i] = Check_WinCond_Multi(travmusic_e[i], cMusicTRAV_E, i); // these ranges are always 10 - 4086
            else if (travmusic_e[i] > 10 && travmusic_e[i] < 4086) travmusic_b_e[i] = true;

            if (travmusic_b_e[i])
            {
                travmusic_anodes_cnt++;
            }
        }
    } // i loop

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
    
    // b_tpc_xy = tpcCalItem.Get_b_tpc_xy();

    // if (b_tpc_xy[4] && b_tpc_xy[5]) // needs changing with S1 scintillator
    // {

    //     travmusic_x_mean = tpcCalItem.Get_tpc_music43_x();

    //     if (b_de_travmus)
    //     {
    //         power = 1.;
    //         Corr = 0.;
    //         for (int i = 0; i < 4; i++)
    //         {
    //             Corr += music->pos_a3[i] * power;
    //             power *= travmusic_x_mean;
    //         }
    //         if (Corr != 0)
    //         {
    //             Corr = music->pos_a3[0] / Corr;
    //             de_cor_travmus = de_travmus * Corr;
    //         }
    //     }
    // }

    // doesn't make sense without a real tof/beta
    // if ((de_travmus > 0.0) && (id_beta > 0.0) && (id_beta < 1.0))
    // {
    //     power = 1.;
    //     sum = 0.;
    //     for (int i = 0; i < 4; i++)
    //     {
    //         sum += power * id->vel_a3[i];
    //         power *= id_beta;
    //     }
    //     id_v_cor_travmus = sum;

    //     if (id_v_cor_travmus > 0.0)
    //     {
    //         id_z_travmus = frs->primary_z * sqrt(de_travmus / id_v_cor_travmus) + id->offset_z3;
    //     }
    //     if ((id_z_travmus > 0.0) && (id_z_travmus < 100.0))
    //     {   
    //         // CEJ: this seems out of order to me, gain matching first?
    //         id_b_z_travmus = kTRUE;
    //     }
    // }
    
    // mhtdc stuff?


    // if (frs_config->TravMusDriftLoaded())
    // {
    //     de_travmus_driftcorr = 0;
    //     double drift_tm = 0.0;
    //     double drift_tm_error = 0.0;
    //     int nentry = 0;
    //     int travmus_wr_time_a = 0; 
    //     int travmus_wr_time_b = 0;
    //     double reference_value = 1956.62;   //!!!! read from file
    //     int bin = 20;                       //!!!! read from file

    //     std::map<int,std::pair<double,double>> travmus_drift = frs_config->TravMusDriftCoefficients();
    //     //std::cout << "::::  TM :::: " << "\n";
    //     for (const auto& entry : travmus_drift)
    //     {
    //         // std::cout << "Key (travmus_wr_time): " << entry.first 
    //         //   << ", Value (coeffs): (" << entry.second.first 
    //         //   << ", " << entry.second.second << ")\n";
            
    //         int travmus_wr_time = entry.first;
    //         std::pair<double,double> coeffs = entry.second;
    //         drift_tm = coeffs.first;
    //         drift_tm_error = coeffs.second;

    //         // if (nentry == 0)
    //         // {
    //         //     travmus_wr_time_a = travmus_wr_time;
    //         //     //reference_value = drift_tm;
    //         // }
    //         // else if (nentry == 1)
    //         // {
    //         //     travmus_wr_time_b = travmus_wr_time;
    //         //     //bin = travmus_wr_time_b - travmus_wr_time_a;
    //         // }

    //         double tm_shift = drift_tm - reference_value;
            
    //         //std::cout << "bin : " << bin << "\n";
    //         //std::cout << "drift travMus : " << drift_tm << " reference value : " << reference_value << "\n";

    //         //std::cout << "min limit : " << (travmus_wr_time - bin/2) << " max limit : " << (travmus_wr_time + bin/2) << "\n";
    //         if ((FRS_TM_time_mins >= (travmus_wr_time - bin/2)) && (FRS_TM_time_mins < (travmus_wr_time + bin/2)))
    //         {
    //             de_travmus_driftcorr = de_travmus - tm_shift;
    //             // std::cout  << " reference :" << reference_value
    //             //     << " drift (1 coeff) :" << drift_tm 
    //             //     << " shift :" << tm_shift 
    //             //     << " TM dE original : " << de_travmus
    //             //     << " TM dE corr : " << de_travmus_driftcorr << "\n";
    //         }
            
    //         nentry ++ ;
    //     }

    // }
    
    fNEvents++;

}

void TravMusCal2Ana::ZeroArrays()
{

}

void TravMusCal2Ana::ClearVectors()
{

}

void TravMusCal2Ana::FinishEvent()
{   
    ZeroArrays();
    ClearVectors();
};

void TravMusCal2Ana::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.",fNEvents));
}

ClassImp(TravMusCal2Ana)