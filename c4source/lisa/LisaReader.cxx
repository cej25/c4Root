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

#define TRACE_CHANNELS 16

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

    //since the febex card has a 100MHz clock which timestamps events.
    event_trigger_time_long = (((uint64_t)(fData->lisa_data_event_trigger_time_hi) << 32) + (fData->lisa_data_event_trigger_time_lo)) * 10;
    
    // white rabbit:
    //wr_t = (((uint64_t)fData->lisa_data_wr_t[3]) << 48) + (((uint64_t)fData->lisa_data_wr_t[2]) << 32) + (((uint64_t)fData->lisa_data_wr_t[1]) << 16) + (uint64_t)(fData->wr_t[0]);

    /*if (WriteZeroMultEvents & (fData->num_channels_fired == 0))
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
    }*/

    for (int index = 0; index < fData->lisa_data_num_channels_fired; index++)
    {
        // if (VetoOverflow & fData->overflow[index]) continue;
        // if (VetoPileup & fData->pileup[index]) continue;

        channel_energy = (int32_t)(fData->lisa_data_channel_energyv[index] & 0x7FFFFFF);

        // combine for 64bit timestamp
        channel_trigger_time_long = (double)(((uint64_t)(fData->lisa_data_channel_trigger_time_hiv[index]) << 32) + (fData->lisa_data_channel_trigger_time_lov[index]));
        // add CF bits and convert to ns time
        channel_trigger_time_long = (((double)fData->lisa_data_channel_cfdv[index]) / 64.0 + channel_trigger_time_long) * 10.0; // units of ns
        
        new ((*fArray)[fArray->GetEntriesFast()]) LisaData(
            fData->lisa_data_num_channels_fired,
            event_trigger_time_long,
            fData->lisa_data_hit_pattern,
            fData->lisa_data_board_id,
            fData->lisa_data_pileup[index],
            fData->lisa_data_overflow[index],
            fData->lisa_data_channel_idv[index],
            channel_trigger_time_long,
            channel_energy,
            0, // fData->lisa_data_wr_subsystem_id,
            0 //wr_t
        );

        for (int channel = 0; channel < TRACE_CHANNELS; channel++)
        {
            for (int sample = 0; sample < fData->lisa_data_traces[channel]._; sample++)
            {   
                // CEJ: shove all into vector, put vector in array? check later
                new ((*fTraceArray)[fTraceArray->GetEntriesFast()]) LisaTraceData(
                    fData->lisa_data_traces[channel].v[sample]);
                
            }
        }
    }

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
