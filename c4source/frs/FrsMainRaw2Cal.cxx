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
    // ,   fRawArray(new TClonesArray("FrsMainData"))
    // ,   fCalArray(new TClonesArray("FrsMainCalData"))
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
    // ,   fRawArray(new TClonesArray("FrsMainData"))
    // ,   fCalArray(new TClonesArray("FrsMainCalData"))
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
    if (fCalArray) delete fCalArray;
}

InitStatus FrsMainRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fRawArray = (TClonesArray*)mgr->GetObject("FrsMainData");
    c4LOG_IF(fatal, !fRawArray, "FRS branch of MainData not found");

    FairRootManager::Instance()->Register("FrsMainCalData", "FRS Main Cal Data", fCalArray, !fOnline);

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
    tdc = new uint32_t*[15];
    for (int i = 0; i < 15; i++) tdc[i] = new uint32_t[max_hits_in_v1290];
    music_t1 = new uint32_t[8];
    music_t2 = new uint32_t[8];

    // fRawArray->Clear();
    // fCalArray->Clear();

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

    for (int i = 0; i < 14; i++) de[i] = 0;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 10; j++) tdc[i][j] = 0;
    }
    for (int i = 0; i < 8; i++) music_t1[i] = 0;
    for (int i = 0; i < 8; i++) music_t2[i] = 0;
    
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
    
    
    /*
    these also not used until FrsAnl step. (Good, I think).
    there is probably a nicer way of writing the following,
    but I didn't want to use big 2d arrays that are mostly empty.
    */

    // CEJ caving and using arrays instead of vectors for multhit atm
    // come back and maybe change to SciDE and SciT?

    int mh_counter[31];
    for (int i = 0; i<31; i++) mh_counter[i] = 0;

    for (auto const & v1290_item : *v1290array)
    {
        if (v1290_item.Get_leadOrTrail() == 0) // lead 0, trail 1
        {
            switch (v1290_item.Get_channel()) // for some reason the data readout of v1290 starts from 1 .... Verified that sci41L is ch 0 in MH 08.05.24
            {
                case 0: // 41l
                    if (mh_counter[0] < max_hits_in_v1290) tdc[0][mh_counter[0]] = v1290_item.Get_v1290_data();
                    mh_counter[0]++;
                    break;
                case 1: // 41r
                    if (mh_counter[1] < max_hits_in_v1290) tdc[1][mh_counter[1]] = v1290_item.Get_v1290_data();
                    mh_counter[1]++;
                    break;
                case 2: // 21l
                    if (mh_counter[2] < max_hits_in_v1290) tdc[2][mh_counter[2]] = v1290_item.Get_v1290_data();
                    mh_counter[2]++;
                    break;
                case 3: // 21r
                    if (mh_counter[3] < max_hits_in_v1290) tdc[3][mh_counter[3]] = v1290_item.Get_v1290_data();
                    mh_counter[3]++;
                    break;
                case 4: // 42l
                    if (mh_counter[4] < max_hits_in_v1290) tdc[4][mh_counter[4]] = v1290_item.Get_v1290_data();
                    mh_counter[4]++;
                    break;
                case 5: // not used
                    break;
                case 6: // 43l
                    if (mh_counter[5] < max_hits_in_v1290) tdc[5][mh_counter[5]] = v1290_item.Get_v1290_data();
                    mh_counter[5]++;
                    break;
                case 7: // 43r
                    if (mh_counter[6] < max_hits_in_v1290) tdc[6][mh_counter[6]] = v1290_item.Get_v1290_data();
                    mh_counter[6]++;
                    break;
                case 8: // 81l
                    if (mh_counter[7] < max_hits_in_v1290) tdc[7][mh_counter[7]] = v1290_item.Get_v1290_data();
                    mh_counter[7]++;
                    break;
                case 9: // 81r
                    if (mh_counter[8] < max_hits_in_v1290) tdc[8][mh_counter[8]] = v1290_item.Get_v1290_data();
                    mh_counter[8]++;
                    break;
                case 10: // 31l
                    if (mh_counter[9] < max_hits_in_v1290) tdc[9][mh_counter[9]] = v1290_item.Get_v1290_data();
                    mh_counter[9]++;
                    break;
                case 11: // 31r
                    if (mh_counter[10] < max_hits_in_v1290) tdc[10][mh_counter[10]] = v1290_item.Get_v1290_data();
                    mh_counter[10]++;
                    break;
                case 12: // 11
                    if (mh_counter[11] < max_hits_in_v1290) tdc[11][mh_counter[11]] = v1290_item.Get_v1290_data();
                    mh_counter[11]++;
                    break;
                case 13: // 22l
                    if (mh_counter[12] < max_hits_in_v1290) tdc[12][mh_counter[12]] = v1290_item.Get_v1290_data();
                    mh_counter[12]++;
                    break;
                case 14: // 22r
                    if (mh_counter[13] < max_hits_in_v1290) tdc[13][mh_counter[13]] = v1290_item.Get_v1290_data();
                    mh_counter[13]++;
                    break;
                case 15: // 42r
                    if (mh_counter[14] < max_hits_in_v1290) tdc[14][mh_counter[14]] = v1290_item.Get_v1290_data();
                    mh_counter[14]++;
                    break;
                case 16:
                    if (mh_counter[15] == 0) music_t1[0] = v1290_item.Get_v1290_data();
                    mh_counter[15]++;
                    break;
                case 17:
                    if (mh_counter[16] == 0) music_t1[1] = v1290_item.Get_v1290_data();
                    mh_counter[16]++;
                    break;
                case 18:
                    if (mh_counter[17] == 0) music_t1[2] = v1290_item.Get_v1290_data();
                    mh_counter[17]++;
                    break;
                case 19:
                    if (mh_counter[18] == 0) music_t1[3] = v1290_item.Get_v1290_data();
                    mh_counter[18]++;
                    break;
                case 20:
                    if (mh_counter[19] == 0) music_t1[4] = v1290_item.Get_v1290_data();
                    mh_counter[19]++;
                    break;
                case 21:
                    if (mh_counter[20] == 0) music_t1[5] = v1290_item.Get_v1290_data();
                    mh_counter[20]++;
                    break;
                case 22:
                    if (mh_counter[21] == 0) music_t1[6] = v1290_item.Get_v1290_data();
                    mh_counter[21]++;
                    break;
                case 23:
                    if (mh_counter[22] == 0) music_t1[7] = v1290_item.Get_v1290_data();
                    mh_counter[22]++;
                    break;
                case 24:
                    if (mh_counter[23] == 0) music_t2[0] = v1290_item.Get_v1290_data();
                    mh_counter[23]++;
                    break;
                case 25:
                    if (mh_counter[24] == 0) music_t2[1] = v1290_item.Get_v1290_data();
                    mh_counter[24]++;
                    break;
                case 26:
                    if (mh_counter[25] == 0) music_t2[2] = v1290_item.Get_v1290_data();
                    mh_counter[25]++;
                    break;
                case 27:
                    if (mh_counter[26] == 0) music_t2[3] = v1290_item.Get_v1290_data();
                    mh_counter[26]++;
                    break;
                case 28:
                    if (mh_counter[27] == 0) music_t2[4] = v1290_item.Get_v1290_data();
                    mh_counter[27]++;
                    break;
                case 29:
                    if (mh_counter[28] == 0) music_t2[5] = v1290_item.Get_v1290_data();
                    mh_counter[28]++;
                    break;
                case 30:
                    if (mh_counter[29] == 0) music_t2[6] = v1290_item.Get_v1290_data();
                    mh_counter[29]++;
                    break;
                case 31:
                    if (mh_counter[30] == 0) music_t2[7] = v1290_item.Get_v1290_data();
                    mh_counter[30]++;
                    break;
            }
        }
    }

    auto & sciEntry = sciArray->emplace_back();
    sciEntry.SetAll(de, tdc);

    auto & musicEntry = musicArray->emplace_back();
    musicEntry.SetAll(music_t1, music_t2);

    fNEvents++;

}

void FrsMainRaw2Cal::ZeroArrays()
{
    memset(de_array, 0, sizeof(de_array));
    //memset(music_t1, 0, sizeof(music_t1));
    //memset(music_t2, 0, sizeof(music_t2));
    // fCalArray->Clear();
}

void FrsMainRaw2Cal::ClearVectors()
{
    for (int i = 0; i < 15; i++) tdc_array[i].clear();
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