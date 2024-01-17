// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsRaw2Cal.h"
#include "FrsData.h"
#include "FrsCalData.h"
#include "c4Logger.h"

#include "TClonesArray.h"

#include <vector>
#include <iostream>

FrsRaw2Cal::FrsRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsData"))
    ,   fCalArray(new TClonesArray("FrsCalData"))
{
}

FrsRaw2Cal::FrsRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsData"))
    ,   fCalArray(new TClonesArray("FrsCalData"))
{
}

FrsRaw2Cal::~FrsRaw2Cal()
{
    c4LOG(info, "Deleting FrsRaw2Cal task");
    if (fRawArray) delete fRawArray;
    if (fCalArray) delete fCalArray;
}

InitStatus FrsRaw2Cal::Init()
{
    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    // not sure this can be a TClonesArray? what about TObjArray?
    fRawArray = (TClonesArray*)mgr->GetObject("FrsData");
    c4LOG_IF(fatal, !fRawArray, "FRS branch of FrsData not found");

    FairRootManager::Instance()->Register("FrsCalData", "FRS Cal Data", fCalArray, !fOnline);

    fRawArray->Clear();
    fCalArray->Clear();

    return kSUCCESS;
}

/*
Should we have some method here for loading FRS Setup file?
If so we need to register it in the array for FrsAnl step
Or make this Raw2Hit directly
*/


void FrsRaw2Cal::Exec(Option_t* option)
{
    std::cout << "start of exec" << std::endl;

    int mult = fRawArray->GetEntriesFast();
    //for (int m = 0; m < fRawArray->GetEntriesFast(); m++)
    //{   
        std::cout << "mult: " << mult << std::endl;
        fRawHit = (FrsData*)fRawArray->At(0); // event multiplicity
        
        
        WR_TS = fRawHit->Get_WR();
        
        // V830
        // this has a FrsCalib step.
        v830_scalers_main = fRawHit->Get_V830_Scalers();

        std::cout << "v830 size: " << v830_scalers_main.size() << std::endl;

        // i think this must be done in FrsReader surely..
        if (v830_scalers_main.size() != 0)
        {

            // I'm not convinced sc_long is necessary. Maybe it was one for efficiency/memory reasons but I don't see how it's better?
            if (scaler_check_first_event == 1) // we need to keep this value somehow? unsure.
            {
                for (int i = 0; i < 32; i++)
                {
                    sc_main_initial[i] = v830_scalers_main[i];
                    sc_main_previous[i] = v830_scalers_main[i];
                    // sc_frs_initial[i] = some_array[i];
                    // sc_frs_previous[i] = some_array[i];
                }
                // CEJ: I don't see how this would even work for Go4
                // scaler_check is surely flipped after a single procid runs through
                // will leave for now..
                scaler_check_first_event = 0; 
            }

            time_in_ms = v830_scalers_main[scaler_ch_1kHz] - sc_main_initial[scaler_ch_1kHz];
            
            if (time_in_ms < 0)
            {
                sc_main_initial[scaler_ch_1kHz] = v830_scalers_main[scaler_ch_1kHz];
                time_in_ms = 0;
            }
            
            
            // spill_count = sc_long[scaler_ch_spillstart] - scaler_initial[scaler_ch_spillstart];

            ibin_for_s = ((time_in_ms / 1000) % 1000) + 1;
            ibin_for_100ms = ((time_in_ms / 100) % 4000) + 1;
            // ibin_for_spill  = (spill_count % 1000) +1;

            // from FrsCalib
            // scaler_ch_spillstart=8; // 8 of scaler_frs
            
            for (int k = 0; k < 32; k++)
            {
                increase_scaler_temp[k] = v830_scalers_main[k] - sc_main_previous[k];
                // same for scaler_frs should be added
            }

            extraction_time_ms += v830_scalers_main[scaler_ch_1kHz] - sc_main_previous[scaler_ch_1kHz];

            // following is some scaler_frs condition, idk how it goes with scalers_main honestly.
            
            /*if(0 != sc_long[scaler_ch_spillstart] - scaler_previous[scaler_ch_spillstart])
            {
                extraction_time_ms = 0;
            }*/
            
            ibin_clean_for_s = (((time_in_ms / 1000) + 20) % 1000) + 1;
            ibin_clean_for_100ms = (((time_in_ms / 100) + 200) % 4000) + 1;
            // ibin_clean_for_spill = ((spill_count + 990) % 20) + 1;

            for (int i = 0; i < 32; i++)
            {   
                // these need to be maintained, not cleared
                sc_main_previous[i] = v830_scalers_main[i];
                // same for scalers_frs;
            }
            
            // everything from the V830 appears to end at Calib
        
        }

        // V792 
    
        v792_geo = fRawHit->Get_V792_Geo();
        v792_channel = fRawHit->Get_V792_Channel();
        v792_data = fRawHit->Get_V792_Data();

        std::cout << "v792 size: " << v792_data.size() << std::endl;

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
                    /*default:
                        // do nothing
                        break;*/
                }
            }
        }
        

        // V1290
        
        v1290_channel = fRawHit->Get_V1290_Channel();
        v1290_data = fRawHit->Get_V1290_Data();
        v1290_lot = fRawHit->Get_V1290_LoT();
        
        std::cout << "v1290 size: " << v1290_data.size() << std::endl;

        /*
        these also not used until FrsAnl step. (Good, I think).
        there is probably a nicer way of writing the following,
        but I didn't want to use big 2d arrays that are mostly empty.
        */

        for (uint32_t i = 0; i < v1290_channel.size(); i++)
        {   

            if (v1290_lot[i] == 1)
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
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                        if (i == 0) music_t1[v1290_channel[i] - 16] = v1290_data[i]; // music_tX ends here before spectra
                        break;
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                        if (i == 0) music_t2[v1290_channel[i] - 24] = v1290_data[i]; // music_tX ends here before spectra
                        break;
                    /*default:
                        // nothing? all cases covered?
                        break;  */   
                }
            }
        }


        // enter into CalData
        
        if (v830_scalers_main.size() != 0)
        {   
            std::cout << v792_data.size() << std::endl;
            std::cout << v1290_data.size() << std::endl;
            std::cout << "wr_ts: " << WR_TS << std::endl;
            std::cout << "time_in_ms: " << time_in_ms << std::endl;
            std::cout << "ibin_for_s: " << ibin_for_s << std::endl;
            std::cout << "ibin_for_100ms: " << ibin_for_100ms << std::endl; 
            std::cout << "extraction_time_ms: " <<  extraction_time_ms << std::endl;
            std::cout << "ibin_clean_for_s: " << ibin_clean_for_s << std::endl;
            std::cout << "ibin_clean_for_100ms: " << ibin_clean_for_100ms << std::endl;

            std::cout << "fCalArray->GetEntriesFast(): " << fCalArray->GetEntriesFast() << std::endl;

            
            // this isn't working but neither are all zeroes
            // well ok this bit "works" but doesn't write? 
            new ((*fCalArray)[fCalArray->GetEntriesFast()]) FrsCalData(
                // V830 scalers
                WR_TS,
                time_in_ms, ibin_for_s, ibin_for_100ms, 
                //increase_scaler_temp, 
                extraction_time_ms, 
                ibin_clean_for_s, ibin_clean_for_100ms//,
                // V792
                //de_array,
                // V1290
                //tdc_array
                //, music_t1, music_t2
                );
            

            std::cout << "fCalArray->GetEntriesFast(): " << fCalArray->GetEntriesFast() << std::endl;

        }
        
    //}
    fNEvents++;
    std::cout << "are we here?" << std::endl;

}

// clear all TClonesArray used in this Task here
void FrsRaw2Cal::FinishEvent()
{   
    std::cout << "do we finish event?" << std::endl;
    for (int i = 0; i < 15; i++) tdc_array[i].clear(); 
    v830_scalers_main.clear();
    v792_channel.clear();
    v792_data.clear();
    v1290_channel.clear();
    v1290_data.clear();
    v1290_lot.clear();
    fRawArray->Clear();
    fCalArray->Clear();
};

void FrsRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.",fNEvents));
}

ClassImp(FrsRaw2Cal)