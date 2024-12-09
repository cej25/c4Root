// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsUserRaw2Cal.h"
#include "FrsUserData.h"
#include "FrsUserCalData.h"
#include "TFRSParameter.h"
#include "c4Logger.h"

#include "TClonesArray.h"

#include <vector>
#include <iostream>

FrsUserRaw2Cal::FrsUserRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   v7x5array(nullptr)
    ,   v830array(nullptr)
    ,   scalerArray(new std::vector<FrsUserCalScalerItem>)
    ,   sciArray(new std::vector<FrsUserCalSciItem>)
    ,   musicArray(new std::vector<FrsUserCalMusicItem>)
{
    frs_config = TFrsConfiguration::GetInstance();
}

FrsUserRaw2Cal::FrsUserRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   v7x5array(nullptr)
    ,   v830array(nullptr)
    ,   scalerArray(new std::vector<FrsUserCalScalerItem>)
    ,   sciArray(new std::vector<FrsUserCalSciItem>)
    ,   musicArray(new std::vector<FrsUserCalMusicItem>)
{
    frs_config = TFrsConfiguration::GetInstance();
}

FrsUserRaw2Cal::~FrsUserRaw2Cal()
{
    c4LOG(info, "Deleting FrsUserRaw2Cal task");
}



InitStatus FrsUserRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    v7x5array = mgr->InitObjectAs<decltype(v7x5array)>("FrsUserV7X5Data");
    c4LOG_IF(fatal, !v7x5array, "Branch FrsUserV7X5Data not found!");
    v830array = mgr->InitObjectAs<decltype(v830array)>("FrsUserV830Data");
    c4LOG_IF(fatal, !v830array, "Branch FrsUserV830Data not found!");


    mgr->RegisterAny("FrsUserCalScalerData", scalerArray, !fOnline);
    mgr->RegisterAny("FrsUserCalSciData", sciArray, !fOnline);
    mgr->RegisterAny("FrsUserCalMusicData", musicArray, !fOnline);

    scalerArray->clear();
    sciArray->clear();
    musicArray->clear();

    dt_array = new uint32_t[16];
    music_e1 = new uint32_t[8];
    music_e2 = new uint32_t[8];

    return kSUCCESS;
}

void FrsUserRaw2Cal::Exec(Option_t* option)
{
    scalerArray->clear();
    sciArray->clear();
    musicArray->clear();

    for (int i = 0; i < 16; i++) dt_array[i] = 0;
    for (int i = 0; i < 8; i++) music_e1[i] = 0;
    for (int i = 0; i < 8; i++) music_e2[i] = 0;

    for (auto const & v830item : *v830array)
    {   
        auto & entry = scalerArray->emplace_back(); 
        uint32_t index = v830item.Get_index();
        uint32_t scaler = v830item.Get_scaler();
        entry.SetAll(index, scaler);
    }

    // CEJ: we're looping over 4 modules but only care about geo == 12 and 10? is this right?
    for (auto const & v7x5item : *v7x5array)
    {
        uint32_t channel = v7x5item.Get_channel(); 
        uint32_t data = v7x5item.Get_v7x5_data();
        uint32_t geo = v7x5item.Get_geo();

        if (geo == frs_config->Get_sci_dT_geo())
        {
            if (channel == frs_config->Get_dT_21l_21r_chan()) dt_21l_21r = data;
            else if (channel == frs_config->Get_dT_41l_41r_chan()) dt_41l_41r = data;
            else if (channel == frs_config->Get_dT_42l_42r_chan()) dt_42l_42r = data;
            else if (channel == frs_config->Get_dT_43l_43r_chan()) dt_43l_43r = data;
            else if (channel == frs_config->Get_dT_81l_81r_chan()) dt_81l_81r = data;
            else if (channel == frs_config->Get_dT_21l_41l_chan()) dt_21l_41l = data;
            else if (channel == frs_config->Get_dT_21r_41r_chan()) dt_21r_41r = data;
            else if (channel == frs_config->Get_dT_42r_21r_chan()) dt_42r_21r = data;
            else if (channel == frs_config->Get_dT_42l_21l_chan()) dt_42l_21l = data;
            else if (channel == frs_config->Get_dT_21l_81l_chan()) dt_21l_81l = data;
            else if (channel == frs_config->Get_dT_21r_81r_chan()) dt_21r_81r = data;
            else if (channel == frs_config->Get_dT_22l_22r_chan()) dt_22l_22r = data;
            else if (channel == frs_config->Get_dT_22l_41l_chan()) dt_22l_41l = data;
            else if (channel == frs_config->Get_dT_22r_41r_chan()) dt_22r_41r = data;
            else if (channel == frs_config->Get_dT_22l_81l_chan()) dt_22l_81l = data;
            else if (channel == frs_config->Get_dT_22r_81r_chan()) dt_22r_81r = data;
        }
        else if (geo == frs_config->Get_music_e_geo())
        {   
            // this works until the mapping becomes stupid
            if (channel <= 7) music_e1[channel] = data;
            else if (channel > 7 && channel <= 15) music_e2[channel - 8] = data;
        }
    
    }

    auto & sciEntry = sciArray->emplace_back();
    sciEntry.SetAll(dt_array);
    sciEntry.Set_dT(dt_21l_21r,
                    dt_41l_41r,
                    dt_42l_42r,
                    dt_43l_43r,
                    dt_81l_81r,
                    dt_21l_41l,
                    dt_21r_41r,
                    dt_42r_21r,
                    dt_42l_21l,
                    dt_21l_81l,
                    dt_21r_81r,
                    dt_22l_22r,
                    dt_22l_41l,
                    dt_22r_41r,
                    dt_22l_81l,
                    dt_22r_81r);

    auto & musicEntry = musicArray->emplace_back();
    musicEntry.SetAll(music_e1, music_e2);
    

    fNEvents++;

}


void FrsUserRaw2Cal::ZeroArrays()
{
}

void FrsUserRaw2Cal::ClearVectors()
{
}


void FrsUserRaw2Cal::FinishEvent()
{   
    ZeroArrays();
    ClearVectors();
    dt_21l_21r = 0;
    dt_41l_41r = 0;
    dt_42l_42r = 0;
    dt_43l_43r = 0;
    dt_81l_81r = 0;
    dt_21l_41l = 0;
    dt_21r_41r = 0;
    dt_42r_21r = 0;
    dt_42l_21l = 0;
    dt_21l_81l = 0;
    dt_21r_81r = 0;
    dt_22l_22r = 0;
    dt_22l_41l = 0;
    dt_22r_41r = 0;
    dt_22l_81l = 0;
    dt_22r_81r = 0;   
}

void FrsUserRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.", fNEvents));
}

ClassImp(FrsUserRaw2Cal)