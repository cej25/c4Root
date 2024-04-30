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
    for (int i = 0; i < 15; i++) tdc[i] = new uint32_t[10];
    music_t1 = new uint32_t[8];
    music_t2 = new uint32_t[8];

    // fRawArray->Clear();
    // fCalArray->Clear();

    return kSUCCESS;
}

void FrsMainRaw2Cal::Exec(Option_t* option)
{
    scalerArray->clear();
    sciArray->clear();
    musicArray->clear();

    // int mult = fRawArray->GetEntriesFast();

    // if (mult == 0) return;

    //for (int m = 0; m < fRawArray->GetEntriesFast(); m++)
    //{   
   // fRawHit = (FrsMainData*)fRawArray->At(0); // event multiplicity
        
        
    // no wr in main now
    //WR_TS = fRawHit->Get_wr_t();
    // CEJ: fCalHit->Set_wr_t(fRawHit->Get_wr_t);
    

    // V830 passed through to Hit step

    for (auto const & v830item : *v830array)
    {
        auto & entry = scalerArray->emplace_back();
        uint32_t index = v830item.Get_index();
        uint32_t scaler = v830item.Get_scaler();
        entry.SetAll(index, scaler);
    }


    // V792 
    
        // v792_geo = fRawHit->Get_V792_Geo();
        // v792_channel = fRawHit->Get_V792_Channel();
        // v792_data = fRawHit->Get_V792_Data();

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

        /*

        for (uint32_t i = 0; i < v792_channel.size(); i++)
        {   
            
            if (v792_geo == 14)
            {   
                switch (v792_channel[i])
                {   
                    // these are not used until Anl.
                    case 1:
                        //de_41r = v792_data[i];
                        de_array[0] = v792_data[i];
                        break;
                    case 2:
                        //de_21l = v792_data[i];
                        de_array[1] = v792_data[i];
                        break;
                    case 3:
                        //de_21r = v792_data[i];
                        de_array[2] = v792_data[i];
                        break;
                    case 4:
                        //de_42l = v792_data[i];
                        de_array[3] = v792_data[i];
                        break;
                    case 5:
                        //de_42r = v792_data[i];
                        de_array[4] = v792_data[i];
                        break;
                    case 6:
                        //de_81l = v792_data[i];
                        de_array[5] = v792_data[i];
                        break;
                    case 7:
                        // unused
                        break;
                    case 8:
                        //de_22r = v792_data[i];
                        de_array[6] = v792_data[i];
                        break;
                    case 9:
                        //de_31l = v792_data[i];
                        de_array[7] = v792_data[i];
                        break;
                    case 10:
                        //de_31r = v792_data[i];
                        de_array[8] = v792_data[i];
                        break;
                    case 11:
                        //de_43l = v792_data[i];
                        de_array[9] = v792_data[i];
                        break;
                    case 12:
                        //de_43r = v792_data[i];
                        de_array[10] = v792_data[i];
                        break;
                    case 13:
                        //de_41l = v792_data[i];
                        de_array[11] = v792_data[i];
                        break;
                    case 14:
                        //de_81r = v792_data[i];
                        de_array[12] = v792_data[i];
                        break;
                    case 15:
                        //de_22l = v792_data[i];
                        de_array[13] = v792_data[i];
                        break;
                }
            }
        }*/
        

        // V1290
        
       /* v1290_channel = fRawHit->Get_V1290_Channel();
        v1290_data = fRawHit->Get_V1290_Data();
        v1290_lot = fRawHit->Get_V1290_LoT();*/
        
        /*
        these also not used until FrsAnl step. (Good, I think).
        there is probably a nicer way of writing the following,
        but I didn't want to use big 2d arrays that are mostly empty.
        */

       // CEJ caving and using arrays instead of vectors for multhit atm
       // come back and maybe change to SciDE and SciT?

       //uint32_t tdc[15][10];
       //uint32_t music_t1[8];
       //uint32_t music_t2[8];
       int mh_counter[31] = {0};

        for (auto const & v1290_item : *v1290array)
        {
            if (v1290_item.Get_leadOrTrail() == 0) // lead 0, trail 1
            {
                switch (v1290_item.Get_channel())
                {
                    case 0: // 41l
                        if (mh_counter[0] < 10) tdc[0][mh_counter[0]] = v1290_item.Get_v1290_data();
                        mh_counter[0]++;
                        break;
                    case 1: // 41r
                        if (mh_counter[1] < 10) tdc[1][mh_counter[1]] = v1290_item.Get_v1290_data();
                        mh_counter[1]++;
                        break;
                    case 2: // 21l
                        if (mh_counter[2] < 10) tdc[2][mh_counter[2]] = v1290_item.Get_v1290_data();
                        mh_counter[2]++;
                        break;
                    case 3: // 21r
                        if (mh_counter[3] < 10) tdc[3][mh_counter[3]] = v1290_item.Get_v1290_data();
                        mh_counter[3]++;
                        break;
                    case 4: // 42l
                        if (mh_counter[4] < 10) tdc[4][mh_counter[4]] = v1290_item.Get_v1290_data();
                        mh_counter[4]++;
                        break;
                    case 5: // not used
                        break;
                    case 6: // 43l
                        if (mh_counter[5] < 10) tdc[5][mh_counter[5]] = v1290_item.Get_v1290_data();
                        mh_counter[5]++;
                        break;
                    case 7: // 43r
                        if (mh_counter[6] < 10) tdc[6][mh_counter[6]] = v1290_item.Get_v1290_data();
                        mh_counter[6]++;
                        break;
                    case 8: // 81l
                        if (mh_counter[7] < 10) tdc[7][mh_counter[7]] = v1290_item.Get_v1290_data();
                        mh_counter[7]++;
                        break;
                    case 9: // 81r
                        if (mh_counter[8] < 10) tdc[8][mh_counter[8]] = v1290_item.Get_v1290_data();
                        mh_counter[8]++;
                        break;
                    case 10: // 31l
                        if (mh_counter[9] < 10) tdc[9][mh_counter[9]] = v1290_item.Get_v1290_data();
                        mh_counter[9]++;
                        break;
                    case 11: // 31r
                        if (mh_counter[10] < 10) tdc[10][mh_counter[10]] = v1290_item.Get_v1290_data();
                        mh_counter[10]++;
                        break;
                    case 12: // 11
                        if (mh_counter[11] < 10) tdc[11][mh_counter[11]] = v1290_item.Get_v1290_data();
                        mh_counter[11]++;
                        break;
                    case 13: // 22l
                        if (mh_counter[12] < 10) tdc[12][mh_counter[12]] = v1290_item.Get_v1290_data();
                        mh_counter[12]++;
                        break;
                    case 14: // 22r
                        if (mh_counter[13] < 10) tdc[13][mh_counter[13]] = v1290_item.Get_v1290_data();
                        mh_counter[13]++;
                        break;
                    case 15: // 42r
                        if (mh_counter[14] < 10) tdc[14][mh_counter[14]] = v1290_item.Get_v1290_data();
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


        /*
        for (uint32_t i = 0; i < v1290_channel.size(); i++)
        {   

            if (v1290_lot[i] == 0) // lead 0, trail 1
            {
                switch (v1290_channel[i])
                {   
                    // reject multihit > 10
                    case 0:
                        //if (tdc_sc41l.size() < 10) tdc_sc41l.emplace_back(v1290_data[i]);
                        if (tdc_array[0].size() < 10) tdc_array[0].emplace_back(v1290_data[i]);
                        break;
                    case 1:
                        //if (tdc_sc41r.size() < 10) tdc_sc41r.emplace_back(v1290_data[i]);
                        if (tdc_array[1].size() < 10) tdc_array[1].emplace_back(v1290_data[i]);
                        break;
                    case 2:
                        //if (tdc_sc21l.size() < 10) tdc_sc21l.emplace_back(v1290_data[i]);
                        if (tdc_array[2].size() < 10) tdc_array[2].emplace_back(v1290_data[i]);
                        break;
                    case 3:
                        //if (tdc_sc21r.size() < 10) tdc_sc21r.emplace_back(v1290_data[i]);
                        if (tdc_array[3].size() < 10) tdc_array[3].emplace_back(v1290_data[i]);
                        break;
                    case 4:
                        //if (tdc_sc42l.size() < 10) tdc_sc42l.emplace_back(v1290_data[i]);
                        if (tdc_array[4].size() < 10) tdc_array[4].emplace_back(v1290_data[i]);
                        break;
                    case 5:
                        // unused
                        break;
                    case 6:
                        //if (tdc_sc43l.size() < 10) tdc_sc43l.emplace_back(v1290_data[i]);
                        if (tdc_array[5].size() < 10) tdc_array[5].emplace_back(v1290_data[i]);
                        break;
                    case 7:
                        //if (tdc_sc43r.size() < 10) tdc_sc43r.emplace_back(v1290_data[i]);
                        if (tdc_array[6].size() < 10) tdc_array[6].emplace_back(v1290_data[i]);
                        break;
                    case 8:
                        //if (tdc_sc81l.size() < 10) tdc_sc81l.emplace_back(v1290_data[i]);
                        if (tdc_array[7].size() < 10) tdc_array[7].emplace_back(v1290_data[i]);
                        break;
                    case 9:
                        //if (tdc_sc81r.size() < 10) tdc_sc81r.emplace_back(v1290_data[i]);
                        if (tdc_array[8].size() < 10) tdc_array[8].emplace_back(v1290_data[i]);
                        break;
                    case 10: 
                        //if (tdc_sc31l.size() < 10) tdc_sc31l.emplace_back(v1290_data[i]);
                        if (tdc_array[9].size() < 10) tdc_array[9].emplace_back(v1290_data[i]);
                        break;
                    case 11:
                        //if (tdc_sc31r.size() < 10) tdc_sc31r.emplace_back(v1290_data[i]);
                        if (tdc_array[10].size() < 10) tdc_array[10].emplace_back(v1290_data[i]);
                        break;
                    case 12:
                        //if (tdc_sc11.size() < 10) tdc_sc11.emplace_back(v1290_data[i]);
                        if (tdc_array[11].size() < 10) tdc_array[11].emplace_back(v1290_data[i]);
                        break;
                    case 13:
                        //if (tdc_sc22l.size() < 10) tdc_sc22l.emplace_back(v1290_data[i]);
                        if (tdc_array[12].size() < 10) tdc_array[12].emplace_back(v1290_data[i]);
                        break;
                    case 14:
                        //if (tdc_sc22r.size() < 10) tdc_sc22r.emplace_back(v1290_data[i]);
                        if (tdc_array[13].size() < 10) tdc_array[13].emplace_back(v1290_data[i]);
                        break;
                    case 15:
                        //if (tdc_sc42r.size() < 10) tdc_sc42r.emplace_back(v1290_data[i]);
                        if (tdc_array[14].size() < 10) tdc_array[14].emplace_back(v1290_data[i]);
                        break;
                    case 16:
                        // this is wrong but it doesn't matter because we don't plot or use it yet..
                        if (i == 0) music_t1[v1290_channel[i] - 16] = v1290_data[i]; // huh? 23 - 16 = 7 always ...?
                        break;
                    case 17:
                        if (i == 0) music_t1[v1290_channel[i] - 16] = v1290_data[i]; // huh? 23 - 16 = 7 always ...?
                        break;
                    case 18:
                        if (i == 0) music_t1[v1290_channel[i] - 16] = v1290_data[i]; // huh? 23 - 16 = 7 always ...?
                        break;
                    case 19:
                        if (i == 0) music_t1[v1290_channel[i] - 16] = v1290_data[i]; // huh? 23 - 16 = 7 always ...?
                        break;
                    case 20:
                        if (i == 0) music_t1[v1290_channel[i] - 16] = v1290_data[i]; // huh? 23 - 16 = 7 always ...?
                        break;
                    case 21:
                        if (i == 0) music_t1[v1290_channel[i] - 16] = v1290_data[i]; // huh? 23 - 16 = 7 always ...?
                        break;
                    case 22:
                        if (i == 0) music_t1[v1290_channel[i] - 16] = v1290_data[i]; // huh? 23 - 16 = 7 always ...?
                        break;
                    case 23:
                        if (i == 0) music_t1[v1290_channel[i] - 16] = v1290_data[i]; // huh? 23 - 16 = 7 always ...?
                        break;
                    case 24:
                        if (i == 0) music_t2[v1290_channel[i] - 24] = v1290_data[i]; // music_tX ends here before spectra
                        break;
                    case 25:
                        if (i == 0) music_t2[v1290_channel[i] - 24] = v1290_data[i]; // music_tX ends here before spectra
                        break;
                    case 26:
                        if (i == 0) music_t2[v1290_channel[i] - 24] = v1290_data[i]; // music_tX ends here before spectra
                        break;
                    case 27:
                        if (i == 0) music_t2[v1290_channel[i] - 24] = v1290_data[i]; // music_tX ends here before spectra
                        break;
                    case 28:
                        if (i == 0) music_t2[v1290_channel[i] - 24] = v1290_data[i]; // music_tX ends here before spectra
                        break;
                    case 29:
                        if (i == 0) music_t2[v1290_channel[i] - 24] = v1290_data[i]; // music_tX ends here before spectra
                        break;
                    case 30:
                        if (i == 0) music_t2[v1290_channel[i] - 24] = v1290_data[i]; // music_tX ends here before spectra
                        break;
                    case 31:
                        if (i == 0) music_t2[v1290_channel[i] - 24] = v1290_data[i]; // music_tX ends here before spectra
                        break;
                }
            }
        }
        */


        // enter into MainCalData
        
        // do we need this? maybe maybe not..
       /* if (v830_scalers_main.size() != 0)
        {   */
    
           /* new ((*fCalArray)[fCalArray->GetEntriesFast()]) FrsMainCalData(
                // V830 scalers
                //WR_TS,
                fRawHit->Get_Scalers_N(),
                fRawHit->Get_Scalers_Index(),
                fRawHit->Get_V830_Scalers(),
                // V792
                de_array,
                // V1290
                tdc_array, music_t1, music_t2
                );*/
            


      //  }
        
    //}
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
    ZeroArrays();
    ClearVectors();
};

void FrsMainRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.",fNEvents));

}

ClassImp(FrsMainRaw2Cal)