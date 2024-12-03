// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsMainRaw2Cal.h"
#include "c4Logger.h"

#include "TClonesArray.h"

#include <vector>
#include <iostream>

FrsMainRaw2Cal::FrsMainRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   v830array(nullptr)
    ,   v792array(nullptr)
    ,   v1290array(nullptr)
    ,   scalerArray(new std::vector<FrsMainCalScalerItem>)
    ,   sciArray(new std::vector<FrsMainCalSciItem>)
    ,   musicArray(new std::vector<FrsMainCalMusicItem>)
{
    frs_config = TFrsConfiguration::GetInstance();
}

FrsMainRaw2Cal::FrsMainRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   v830array(nullptr)
    ,   v792array(nullptr)
    ,   v1290array(nullptr)
    ,   scalerArray(new std::vector<FrsMainCalScalerItem>)
    ,   sciArray(new std::vector<FrsMainCalSciItem>)
    ,   musicArray(new std::vector<FrsMainCalMusicItem>)
{
    frs_config = TFrsConfiguration::GetInstance();
}

FrsMainRaw2Cal::~FrsMainRaw2Cal()
{
    c4LOG(info, "Deleting FrsMainRaw2Cal task");
}

InitStatus FrsMainRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    v830array = mgr->InitObjectAs<decltype(v830array)>("FrsMainV830Data");
    c4LOG_IF(fatal, !v830array, "Branch v830array not found!");
    v792array = mgr->InitObjectAs<decltype(v792array)>("FrsMainV792Data");
    c4LOG_IF(fatal, !v792array, "Branch v792array not found!");
    v1290array = mgr->InitObjectAs<decltype(v1290array)>("FrsMainV1290Data");
    c4LOG_IF(fatal, !v1290array, "Branch v1290array not found!");

    mgr->RegisterAny("FrsMainCalScalerData", scalerArray, !fOnline);
    mgr->RegisterAny("FrsMainCalSciData", sciArray, !fOnline);
    mgr->RegisterAny("FrsMainCalMusicData", musicArray, !fOnline);

    scalerArray->clear();
    sciArray->clear();
    musicArray->clear();

    de = new uint32_t[14];
    music_t1 = new uint32_t[8];
    music_t2 = new uint32_t[8];

    ZeroArrays();


    return kSUCCESS;
}

void FrsMainRaw2Cal::Exec(Option_t* option)
{
    // V830 passed through to Hit step

    for (auto const & v830item : *v830array)
    {
        auto & entry = scalerArray->emplace_back();
        uint32_t index = v830item.Get_index();
        uint32_t scaler = v830item.Get_scaler();
        entry.SetAll(index, scaler);
    }


    // V792 
    for (auto const & v792item : *v792array)
    {
        uint32_t geo = v792item.Get_geo();
        uint32_t data = v792item.Get_v792_data();
        uint32_t channel = v792item.Get_channel();

        if (geo == frs_config->Get_sci_dE_geo())
        {
            if (channel == frs_config->Get_dE_21l_chan()) de_21l = data;
            else if (channel == frs_config->Get_dE_21r_chan()) de_21r = data;
            else if (channel == frs_config->Get_dE_22l_chan()) de_22l = data;
            else if (channel == frs_config->Get_dE_22r_chan()) de_22r = data;
            else if (channel == frs_config->Get_dE_31l_chan()) de_31l = data;
            else if (channel == frs_config->Get_dE_31r_chan()) de_31r = data;
            else if (channel == frs_config->Get_dE_41l_chan()) de_41l = data;
            else if (channel == frs_config->Get_dE_41r_chan()) de_41r = data;
            else if (channel == frs_config->Get_dE_42l_chan()) de_42l = data;
            else if (channel == frs_config->Get_dE_42r_chan()) de_42r = data;
            else if (channel == frs_config->Get_dE_43l_chan()) de_43l = data;
            else if (channel == frs_config->Get_dE_43r_chan()) de_43r = data;
            else if (channel == frs_config->Get_dE_81l_chan()) de_81l = data;
            else if (channel == frs_config->Get_dE_81r_chan()) de_81r = data;            
        }
    }

    auto & sciEntry = sciArray->emplace_back();
    sciEntry.Set_dE(de_21l,
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
                    de_81r);


    // V1290
    // CEJ: will add mapping to this at some point
    for (auto const & v1290_item : *v1290array)
    {
        uint32_t channel = v1290_item.Get_channel();
        uint32_t lot = v1290_item.Get_leadOrTrail();
        int32_t data = v1290_item.Get_v1290_data();

        if (lot != 0) continue; // lead = 0, trail = 1
        
        if (channel == frs_config->Get_ts_11_ch()) sciEntry.Add_mhtdc_sc11_hit(data);
        else if (channel == frs_config->Get_ts_21L_ch()) sciEntry.Add_mhtdc_sc21l_hit(data);
        else if (channel == frs_config->Get_ts_21R_ch()) sciEntry.Add_mhtdc_sc21r_hit(data);
        else if (channel == frs_config->Get_ts_22L_ch()) sciEntry.Add_mhtdc_sc22l_hit(data);
        else if (channel == frs_config->Get_ts_22R_ch()) sciEntry.Add_mhtdc_sc22r_hit(data);
        else if (channel == frs_config->Get_ts_31L_ch()) sciEntry.Add_mhtdc_sc31l_hit(data);
        else if (channel == frs_config->Get_ts_31R_ch()) sciEntry.Add_mhtdc_sc31r_hit(data);
        else if (channel == frs_config->Get_ts_41L_ch()) sciEntry.Add_mhtdc_sc41l_hit(data);
        else if (channel == frs_config->Get_ts_41R_ch()) sciEntry.Add_mhtdc_sc41r_hit(data);
        else if (channel == frs_config->Get_ts_42L_ch()) sciEntry.Add_mhtdc_sc42l_hit(data);
        else if (channel == frs_config->Get_ts_42R_ch()) sciEntry.Add_mhtdc_sc42r_hit(data);
        else if (channel == frs_config->Get_ts_43L_ch()) sciEntry.Add_mhtdc_sc43l_hit(data);
        else if (channel == frs_config->Get_ts_43R_ch()) sciEntry.Add_mhtdc_sc43r_hit(data);
        else if (channel == frs_config->Get_ts_81L_ch()) sciEntry.Add_mhtdc_sc81l_hit(data);
        else if (channel == frs_config->Get_ts_81R_ch()) sciEntry.Add_mhtdc_sc81r_hit(data);

        // CEJ: possibly need to fill only first value (if multiple) but music_t not used currently, so don't know
        else if (channel > 15 && channel < 24) music_t1[channel - 16] = data;
        else if (channel > 23 && channel < 32) music_t1[channel - 24] = data;
        
    }

    auto & musicEntry = musicArray->emplace_back();
    musicEntry.SetAll(music_t1, music_t2);

    fNEvents++;

}

void FrsMainRaw2Cal::ZeroArrays()
{

    for (int i = 0; i < 14; i++) de[i] = 0;
    for (int i = 0; i < 8; i++) music_t1[i] = 0;
    for (int i = 0; i < 8; i++) music_t2[i] = 0;
    
}

void FrsMainRaw2Cal::ClearVectors()
{
    v830_scalers_index.clear();
    v830_scalers_main.clear();
    v792_channel.clear();
    v792_data.clear();
    v1290_channel.clear();
    v1290_data.clear();
    v1290_lot.clear();

    scalerArray->clear();
    sciArray->clear();
    musicArray->clear();

}

void FrsMainRaw2Cal::FinishEvent()
{   
    ClearVectors();
    ZeroArrays();

    de_21l = 0;
    de_21r = 0;
    de_22l = 0;
    de_22r = 0;
    de_31l = 0;
    de_31r = 0;
    de_41l = 0;
    de_41r = 0;
    de_42l = 0;
    de_42r = 0;
    de_43l = 0;
    de_43r = 0;
    de_81l = 0;
    de_81r = 0;
};

void FrsMainRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.",fNEvents));

}

ClassImp(FrsMainRaw2Cal)