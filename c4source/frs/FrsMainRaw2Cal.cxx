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
}

FrsMainRaw2Cal::~FrsMainRaw2Cal()
{
    c4LOG(info, "Deleting FrsMainRaw2Cal task");
    if (fRawArray) delete fRawArray;
}

InitStatus FrsMainRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fRawArray = (TClonesArray*)mgr->GetObject("FrsMainData");
    c4LOG_IF(fatal, !fRawArray, "FRS branch of MainData not found");


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

    // should only be 1 entry for this vector of items?
    for (auto const & v792item : *v792array)
    {
        uint32_t geo = v792item.Get_geo();
        uint32_t data = v792item.Get_v792_data();
        uint32_t channel = v792item.Get_channel();
        if (geo == 14)
        {
            switch (channel)
            {
                case 1: // 41r
                    de[0] = data;
                    break;
                case 2: // 21l
                    de[1] = data;
                    break;
                case 3: // 21r
                    de[2] = data;
                    break;
                case 4: // 42l
                    de[3] = data;
                    break;
                case 5: // 42r
                    de[4] = data;
                    break;
                case 6: // 81l
                    de[5] = data;
                    break;
                case 7: // not used
                    break;
                case 8: // 22r
                    de[6] = data;
                    break;
                case 9: // 31l
                    de[7] = data;
                    break;
                case 10: // 31r
                    de[8] = data;
                    break;
                case 11: // 43l
                    de[9] = data;
                    break;
                case 12: // 43r
                    de[10] = data;
                    break;
                case 13: // 41l
                    de[11] = data;
                    break;
                case 14: // 81r
                    de[12] = data;
                    break;
                case 15: // 22l
                    de[13] = data;
                    break;

            }
        }
    }


    // V1290

    auto & sciEntry = sciArray->emplace_back();

    sciEntry.SetdEArray(de);

    for (auto const & v1290_item : *v1290array)
    {
        if (v1290_item.Get_leadOrTrail() == 0) // lead 0, trail 1
        {
            switch (v1290_item.Get_channel()) // for some reason the data readout of v1290 starts from 1 .... Verified that sci41L is ch 0 in MH 08.05.24
            {
                case 0: // 41l
                    sciEntry.Add_mhtdc_sc41l_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 1: // 41r
                    sciEntry.Add_mhtdc_sc41r_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 2: // 21l
                    sciEntry.Add_mhtdc_sc21l_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 3: // 21r
                    sciEntry.Add_mhtdc_sc21r_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 4: // 42l
                    sciEntry.Add_mhtdc_sc42l_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 5: // not used
                    break;
                case 6: // 43l
                    sciEntry.Add_mhtdc_sc43l_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 7: // 43r
                    sciEntry.Add_mhtdc_sc43r_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 8: // 81l
                    sciEntry.Add_mhtdc_sc81l_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 9: // 81r
                    sciEntry.Add_mhtdc_sc81r_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 10: // 31l
                    sciEntry.Add_mhtdc_sc31l_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 11: // 31r
                    sciEntry.Add_mhtdc_sc31r_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 12: // 11
                    sciEntry.Add_mhtdc_sc11_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 13: // 22l
                    sciEntry.Add_mhtdc_sc22l_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 14: // 22r
                    sciEntry.Add_mhtdc_sc22r_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 15: // 42r
                    sciEntry.Add_mhtdc_sc42r_hit((int32_t)v1290_item.Get_v1290_data());
                    break;
                case 16:
                    if (music_t1[0] != 0) music_t1[0] = v1290_item.Get_v1290_data();
                    break;
                case 17:
                    if (music_t1[1] != 0) music_t1[1] = v1290_item.Get_v1290_data();
                    break;
                case 18:
                    if (music_t1[2] != 0) music_t1[2] = v1290_item.Get_v1290_data();
                    break;
                case 19:
                    if (music_t1[3] != 0) music_t1[3] = v1290_item.Get_v1290_data();
                    break;
                case 20:
                    if (music_t1[4] != 0) music_t1[4] = v1290_item.Get_v1290_data();
                    break;
                case 21:
                    if (music_t1[5] != 0) music_t1[5] = v1290_item.Get_v1290_data();
                    break;
                case 22:
                    if (music_t1[6] != 0) music_t1[6] = v1290_item.Get_v1290_data();
                    break;
                case 23:
                    if (music_t1[7] != 0) music_t1[7] = v1290_item.Get_v1290_data();
                    break;
                case 24:
                    if (music_t2[0] != 0) music_t2[0] = v1290_item.Get_v1290_data();
                    break;
                case 25:
                    if (music_t2[1] != 0) music_t2[1] = v1290_item.Get_v1290_data();
                    break;
                case 26:
                    if (music_t2[2] != 0) music_t2[2] = v1290_item.Get_v1290_data();
                    break;
                case 27:
                    if (music_t2[3] != 0) music_t2[3] = v1290_item.Get_v1290_data();
                    break;
                case 28:
                    if (music_t2[4] != 0) music_t2[4] = v1290_item.Get_v1290_data();
                    break;
                case 29:
                    if (music_t2[5] != 0) music_t2[5] = v1290_item.Get_v1290_data();
                    break;
                case 30:
                    if (music_t2[6] != 0) music_t2[6] = v1290_item.Get_v1290_data();
                    break;
                case 31:
                    if (music_t2[7] != 0) music_t2[7] = v1290_item.Get_v1290_data();
                    break;
            }
        }
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
}

void FrsMainRaw2Cal::FinishEvent()
{   
    scalerArray->clear();
    sciArray->clear();
    musicArray->clear();
    ClearVectors();
    ZeroArrays();
};

void FrsMainRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.",fNEvents));

}

ClassImp(FrsMainRaw2Cal)