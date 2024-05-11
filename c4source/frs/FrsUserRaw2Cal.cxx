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
    ,   fRawArray(new TClonesArray("FrsUserData"))
    ,   fCalArray(new TClonesArray("FrsUserCalData"))
    ,   v7x5array(nullptr)
    ,   v830array(nullptr)
    ,   scalerArray(new std::vector<FrsUserCalScalerItem>)
    ,   sciArray(new std::vector<FrsUserCalSciItem>)
    ,   musicArray(new std::vector<FrsUserCalMusicItem>)
{
}

FrsUserRaw2Cal::FrsUserRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsUserData"))
    ,   fCalArray(new TClonesArray("FrsUserCalData"))
    ,   v7x5array(nullptr)
    ,   v830array(nullptr)
    ,   scalerArray(new std::vector<FrsUserCalScalerItem>)
    ,   sciArray(new std::vector<FrsUserCalSciItem>)
    ,   musicArray(new std::vector<FrsUserCalMusicItem>)
{
}

FrsUserRaw2Cal::~FrsUserRaw2Cal()
{
    c4LOG(info, "Deleting FrsUserRaw2Cal task");
    //if (fRawArray) delete fRawArray;
    //if (fCalArray) delete fCalArray;
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

    // new code
    // CEJ: we're looping over 4 modules but only care about geo == 12 and 10? is this right?
    for (auto const & v7x5item : *v7x5array)
    {
        uint32_t channel = v7x5item.Get_channel(); 
        uint32_t data = v7x5item.Get_v7x5_data();
        uint32_t geo = v7x5item.Get_geo();

        switch (channel)
        {
            case 0:
                if (geo == 12) dt_array[0] = data; // dt_21l_21r
                if (geo == 10) music_e1[0] = data;
                break;
            case 1:
                if (geo == 12) dt_array[1] = data; // dt_41l_41r
                if (geo == 10) music_e1[1] = data;
                break;
            case 2:
                if (geo == 12) dt_array[2] = data; // dt_42l_42r
                if (geo == 10) music_e1[2] = data;
                break;
            case 3:
                if (geo == 12) dt_array[3] = data; // dt_43l_43r
                if (geo == 10) music_e1[3] = data;
                break;
            case 4:
                if (geo == 12) dt_array[4] = data; // dt_81l_81r
                if (geo == 10) music_e1[4] = data;
                break;
            case 5:
                if (geo == 12) dt_array[5] = data; // dt_21l_41l
                if (geo == 10) music_e1[5] = data;
                break;
            case 6:
                if (geo == 12) dt_array[6] = data; // dt_21r_41r
                if (geo == 10) music_e1[6] = data;
                break;
            case 7:
                if (geo == 12) dt_array[7] = data; // dt_42r_21r
                if (geo == 10) music_e1[7] = data;
                break;
            case 8:
                if (geo == 12) dt_array[8] = data; // dt_42l_21l
                if (geo == 10) music_e2[0] = data;
                break;
            case 9:
                if (geo == 12) dt_array[9] = data; // dt_2l_81l
                if (geo == 10) music_e2[1] = data;
                break;
            case 10:
                if (geo == 12) dt_array[10] = data; // dt_21r_81r
                if (geo == 10) music_e2[2] = data;
                break;
            case 11:
                if (geo == 12) dt_array[11] = data; // dt_22l_22r
                if (geo == 10) music_e2[3] = data;
                break;
            case 12:
                if (geo == 12) dt_array[12] = data; // dt_22l_41l
                if (geo == 10) music_e2[4] = data;
                break;
            case 13:
                if (geo == 12) dt_array[13] = data; // dt_22r_41r
                if (geo == 10) music_e2[5] = data;
                break;
            case 14:
                if (geo == 12) dt_array[14] = data; // dt_22l_81l
                if (geo == 10) music_e2[6] = data;
                break;
            case 15:
                if (geo == 12) dt_array[15] = data; // dt_22r_81r
                if (geo == 10) music_e2[7] = data;
                break;
        }
    }

    auto & sciEntry = sciArray->emplace_back();
    sciEntry.SetAll(dt_array);

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
}

void FrsUserRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.", fNEvents));
}

ClassImp(FrsUserRaw2Cal)