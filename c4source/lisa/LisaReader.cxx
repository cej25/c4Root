#include "FairLogger.h"
#include "FairRootManager.h"

#include "LisaData.h"
#include "LisaTraceData.h"
#include "LisaReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_lisa.h"
}

LisaReader::LisaReader(EXT_STR_h101_LISA_onion* data, size_t offset)
    : c4Reader("LisaReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("LisaData"))
    , fTraceArray(new TClonesArray("LisaTraceData"))
{
}

LisaReader::~LisaReader() 
{ 
    delete fArray;
    delete fTraceArray;
}

Bool_t LisaReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_LISA_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_LISA, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    // register output array in a tree
    FairRootManager::Instance()->Register("LisaData", "LISA Data", fArray, !fOnline);
    FairRootManager::Instance()->Register("LisaTraceData", "LISA Trace Data", fTraceArray, !fOnline);
    fArray->Clear();
    fTraceArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t LisaReader::Read()
{
    c4LOG(debug1, "Event Data");

<<<<<<< HEAD
    
    





=======
    //since the febex card has a 100MHz clock which timestamps events.
    event_trigger_time_long = (((uint64_t)(fData->event_trigger_time_hi) << 32) + (fData->event_trigger_time_lo)) * 10;
    
    // white rabbit:
    wr_t = (((uint64_t)fData->wr_t[3]) << 48) + (((uint64_t)fData->wr_t[2]) << 32) + (((uint64_t)fData->wr_t[1]) << 16) + (uint64_t)(fData->wr_t[0]);

    if (WriteZeroMultEvents & (fData->num_channels_fired == 0))
    {
         new ((*fArray)[fArray->GetEntriesFast()]) LisaData(
            fData->num_channels_fired,
            event_trigger_time_long,
            fData->hit_pattern,
            fData->board_id,
            0,
            0,
            0,
            0,
            0,
            fData->wr_subsystem_id,
            wr_t);
    }
>>>>>>> main

    for (int index = 0; index < fData->num_channels_fired; index++)
    {
        // if (VetoOverflow & fData->overflow[index]) continue;
        // if (VetoPileup & fData->pileup[index]) continue;

        channel_energy = (int32_t)(fData->channel_energy[index] & 0x7FFFFFF);

        // combine for 64bit timestamp
        channel_trigger_time_long = (double)(((uint64_t)(fData->channel_trigger_time_hi[index]) << 32) + (fData->channel_trigger_time_lo[index]));
        // add CF bits and convert to ns time
        channel_trigger_time_long = (((double)fData->channel_cfd[index]) / 64.0 + channel_trigger_time_long) * 10.0; // units of ns
        
        new ((*fArray)[fArray->GetEntriesFast()]) LisaData(
            fData->num_channels_fired,
            event_trigger_time_long,
            fData->hit_pattern,
            fData->board_id,
            fData->pileup[index],
            fData->overflow[index],
            fData->channel_id[index],
            channel_trigger_time_long,
            channel_energy,
            fData->wr_subsystem_id,
            wr_t
        );

<<<<<<< HEAD
=======
    }
>>>>>>> main

    fNEvent += 1;
    return kTRUE;
}

void LisaReader::Reset()
{   
    // reset output array
    fArray->Clear();
    fTraceArray->Clear();
}

ClassImp(LisaReader);
