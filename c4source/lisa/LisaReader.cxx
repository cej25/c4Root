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
    c4LOG(debug1, "Event data");

    event_trigger_time_long = ((uint64_t)(fData->event_trigger_time_hi) << 32) + (fData->event_trigger_time_lo);
    
    // wr timestamp
    wr_t = (((uint64_t)fData->wr_t[3]) << 48) + (((uint64_t)fData->wr_t[2]) << 32) + (((uint64_t)fData->wr_t[1]) << 16) + ((uint64_t)(fData->wr_t[0]));

    for (int index = 0; index < fData->num_channels_fired; index++)
    {
        // 24th bit denotes sign, but we'll skip worrying about this for now
        channel_energy = (int32_t)(fData->channel_energy[index] & 0x7FFFFF);

        if (DetectorMap_loaded)
        {
            // detector mapping

            if (DetectorCal_loaded)
            {
                // detector calibration if mapping is functional
            }
        }
        else // no map or cal
        {
            detector_id = 0;
            crystal_id = 0;
            channel_energy_cal = -1;
        }

        // combined channel timestamp
        channel_trigger_time_long = (double)(((uint64_t)fData->channel_trigger_time_hi[index] << 32) + (fData->channel_trigger_time_lo[index])); 
        // add CF from constant fraction
        channel_trigger_time_long = (double)
    }
    
    








    // Read 16 channels
    for (Int_t chan = 0; chan < 16; chan++)
    {   
        // we should avoid zeros where we can, i.e. only fill from active channels.
        // or borrow some __cool__ ucesb zero_suppression. Otherwise..works..
        // janky until the structure file can be fixed. Mapping?
        /*if (chan == 0)
        {
            ts_lo = fData->trace_data_fts_lo_0[0];
            ts_hi = fData->trace_data_fts_hi_0[0];
        }
        else
        {
            ts_lo = 0;
            ts_hi = 0;
        }*/

        new ((*fArray)[fArray->GetEntriesFast()]) LisaData(fData->lisa_data_fboard,
                                                         fData->lisa_data_channel_idv[chan],
                                                         fData->lisa_data_fenv[chan],
                                                         fData->lisa_data_fts_lov[chan],
                                                         fData->lisa_data_fts_hiv[chan]);

        for (Int_t sample = 0; sample < fData->lisa_data_ftrace[chan]._; sample++)
        {
            new ((*fTraceArray)[fTraceArray->GetEntriesFast()]) LisaTraceData(fData->lisa_data_ftrace[chan].v[sample]);
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
