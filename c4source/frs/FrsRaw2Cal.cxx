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
#include "FrsCalData.h" // doesn't exist yet
#include "c4Logger.h"

#include "TClonesArray.h"

FrsRaw2Cal::FrsRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsData"))
    ,   fCalArray(new TClonesArray("FrsCalData"))
{
}

FrsRaw2Cal::FrsRaw2Cal()
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

    fRawHit = (FrsData*)fRawArray->At(ihit);

    // V830
    // this has a FrsCalib step.
    v830_scalers_main = fRawHit->Get_V830_Scalers();

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

    // V792 
    v792_geo = fRawHit->Get_V792_Geo();
    v792_channel = fRawHit->Get_V792_Channel();
    v792_data = fRawHit->Get_V792_Data();

    for (uint32_t i; i < v792_channel->GetEntriesFast(); i++)
    {   
        if (v792_geo == 14) 
        {
            switch (v792_channel[i])
            {   
                // these are not used until Anl.
                case 1:
                    de_41r = v792_data[i];
                case 2:
                    de_21l = v792_data[i];
                case 3:
                    de_21r = v792_data[i];
                case 4:
                    de_42l = v792_data[i];
                case 5:
                    de_42r = v792_data[i];
                case 6:
                    de_81l = v792_data[i];
                case 7:
                    // unused
                case 8:
                    de_22r = v792_data[i];
                case 9:
                    de_31l = v792_data[i];
                case 10:
                    de_31r = v792_data[i];
                case 11:
                    de_43l = v792_data[i];
                case 12:
                    de_43r = v792_data[i];
                case 13:
                    de_41l = v792_data[i];
                case 14:
                    de_81r = v792_data[i];
                case 15:
                    de_22l = v792_data[i];
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
    for (uint32_t i = 0; i < v1290_channel->GetEntriesFast(); i++)
    {
        // if leading (trails go unused?)
        if (v1290_lot[i] == 1)
        {
            switch (v1290_channel[i])
            {   
                // reject multihit > 10
                case 0:
                    if (tdc_sc41l.size() < 10) tdc_sc41l.emplace_back(v1290_data[i]);
                    break;
                case 1:
                    if (tdc_sc41r.size() < 10) tdc_sc41r.emplace_back(v1290_data[i]);
                    break;
                case 2:
                    if (tdc_sc21l.size() < 10) tdc_sc21l.emplace_back(v1290_data[i]);
                    break;
                case 3:
                    if (tdc_sc21r.size() < 10) tdc_sc21r.emplace_back(v1290_data[i]);
                    break;
                case 4:
                    if (tdc_sc42l.size() < 10) tdc_sc42l.emplace_back(v1290_data[i]);
                    break;
                case 5:
                    // unused
                    break;
                case 6:
                    if (tdc_sc43l.size() < 10) tdc_sc43l.emplace_back(v1290_data[i]);
                    break;
                case 7:
                    if (tdc_sc43r.size() < 10) tdc_sc43r.emplace_back(v1290_data[i]);
                    break;
                case 8:
                    if (tdc_sc81l.size() < 10) tdc_sc81l.emplace_back(v1290_data[i]);
                    break;
                case 9:
                    if (tdc_sc81r.size() < 10) tdc_sc81r.emplace_back(v1290_data[i]);
                    break;
                case 10: 
                    if (tdc_sc31l.size() < 10) tdc_sc31l.emplace_back(v1290_data[i]);
                    break;
                case 11:
                    if (tdc_sc31r.size() < 10) tdc_sc31r.emplace_back(v1290_data[i]);
                    break;
                case 12:
                    if (tdc_sc11.size() < 10) tdc_sc11.emplace_back(v1290_data[i]);
                    break;
                case 13:
                    if (tdc_sc22l.size() < 10) tdc_sc22l.emplace_back(v1290_data[i]);
                    break;
                case 14:
                    if (tdc_sc22r.size() < 10) tdc_sc22r.emplace_back(v1290_data[i]);
                    break;
                case 15:
                    if (tdc_sc42r.size() < 10) tdc_sc42r.emplace_back(v1290_data[i]);
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

            }
        }
    }
}

// clear all TClonesArray used in this Task here
void FrsRaw2Cal::FinishEvent()
{   
    v830_scalers_main.clear();
    v792_channel.clear();
    v792_data.clear();
    v1290_channel.clear();
    v1290_data.clear();
    v1290_lot.clear();
    fRawArray->Clear();
    fCalArray->Clear();
}

void FrsRaw2Cal::FinishTask()
{
}

ClassImp(FrsRaw2Cal)