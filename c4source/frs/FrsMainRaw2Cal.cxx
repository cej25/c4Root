// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsMainRaw2Cal.h"
#include "FrsMainData.h"
#include "FrsMainCalData.h"
#include "c4Logger.h"

#include "TClonesArray.h"

#include <vector>
#include <iostream>

FrsMainRaw2Cal::FrsMainRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsMainData"))
    ,   fCalArray(new TClonesArray("FrsMainCalData"))
{
}

FrsMainRaw2Cal::FrsMainRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsMainData"))
    ,   fCalArray(new TClonesArray("FrsMainCalData"))
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
    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fRawArray = (TClonesArray*)mgr->GetObject("FrsMainData");
    c4LOG_IF(fatal, !fRawArray, "FRS branch of MainData not found");

    FairRootManager::Instance()->Register("FrsMainCalData", "FRS Main Cal Data", fCalArray, !fOnline);

    fRawArray->Clear();
    fCalArray->Clear();

    return kSUCCESS;
}

/*
Should we have some method here for loading FRS Setup file?
If so we need to register it in the array for FrsAnl step
Or make this Raw2Hit directly
*/


void FrsMainRaw2Cal::Exec(Option_t* option)
{

    int mult = fRawArray->GetEntriesFast();

    if (mult == 0) return;

    //for (int m = 0; m < fRawArray->GetEntriesFast(); m++)
    //{   
        fRawHit = (FrsMainData*)fRawArray->At(0); // event multiplicity
        
        
        WR_TS = fRawHit->Get_wr_t();
        // CEJ: fCalHit->Set_wr_t(fRawHit->Get_wr_t);
        

        // V830 passed through to Hit step

        // V792 
    
        v792_geo = fRawHit->Get_V792_Geo();
        v792_channel = fRawHit->Get_V792_Channel();
        v792_data = fRawHit->Get_V792_Data();

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
        }
        

        // V1290
        
        v1290_channel = fRawHit->Get_V1290_Channel();
        v1290_data = fRawHit->Get_V1290_Data();
        v1290_lot = fRawHit->Get_V1290_LoT();
        
        /*
        these also not used until FrsAnl step. (Good, I think).
        there is probably a nicer way of writing the following,
        but I didn't want to use big 2d arrays that are mostly empty.
        */

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


        // enter into MainCalData
        
        // do we need this? maybe maybe not..
       /* if (v830_scalers_main.size() != 0)
        {   */
    
            new ((*fCalArray)[fCalArray->GetEntriesFast()]) FrsMainCalData(
                // V830 scalers
                WR_TS,
                fRawHit->Get_Scalers_N(),
                fRawHit->Get_Scalers_Index(),
                fRawHit->Get_V830_Scalers(),
                // V792
                de_array,
                // V1290
                tdc_array, music_t1, music_t2
                );
            


      //  }
        
    //}
    fNEvents++;

}

void FrsMainRaw2Cal::ZeroArrays()
{
    memset(de_array, 0, sizeof(de_array));
    memset(music_t1, 0, sizeof(music_t1));
    memset(music_t2, 0, sizeof(music_t2));
    fCalArray->Clear();
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