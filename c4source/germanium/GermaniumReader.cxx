// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "GermaniumFebexData.h"
#include "GermaniumReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_ge_febex.h"
}

GermaniumReader::GermaniumReader(EXT_STR_h101_GE_FEBEX_onion* data, size_t offset)
    : c4Reader("GermaniumReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("GermaniumFebexData"))
{
}

GermaniumReader::~GermaniumReader() { delete fArray; }

Bool_t GermaniumReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_GE_FEBEX_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_GE_FEBEX, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->Register("GermaniumFebexData", "Germanium Febex Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t GermaniumReader::Read() // do the detector mapping here:
{
    c4LOG(debug1, "Event Data");


    event_trigger_time_long = ((uint64_t)(fData->event_trigger_time_hi) << 32) + (fData->event_trigger_time_lo);


    //whiterabbit timestamp:
    wr_t = (((uint64_t)fData->wr_t[3]) << 48) + (((uint64_t)fData->wr_t[2]) << 32) + (((uint64_t)fData->wr_t[1]) << 16) + (uint64_t)(fData->wr_t[0]);

    if (fData->num_channels_fired == 0 & false){ //write multiplicity zero events?
        new ((*fArray)[fArray->GetEntriesFast()]) GermaniumFebexData(
            fData->num_channels_fired,
            event_trigger_time_long,
            fData->hit_pattern,
            fData->board_id,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            fData->wr_subsystem_id,
            wr_t
        );
    }

    for (int index = 0; index < fData->num_channels_fired; index++)
    {   

        //do the detector mapping here:
        // board_id,channel_id -> det_id,crystal_id
        //temp:
        detector_id = fData->board_id;
        crystal_id  = fData->channel_id[index];
        

        //according to febex manual on gsi website the 24th bit of the energy bits denotes the sign to indicate the polarity of the pulse?
        if (fData->channel_energy[index] & (1 << 23)){
            channel_energy = -(int32_t)(fData->channel_energy[index] & 0x007FFFFF);
        }else{
            channel_energy = +(int32_t)(fData->channel_energy[index] & 0x007FFFFF);            
        }


        channel_trigger_time_long = ((uint64_t)(fData->channel_trigger_time_hi[index]) << 32) + (fData->channel_trigger_time_lo[index]);

        new ((*fArray)[fArray->GetEntriesFast()]) GermaniumFebexData(
            fData->num_channels_fired,
            event_trigger_time_long,
            fData->hit_pattern,
            fData->board_id,
            fData->pileup[index],
            fData->overflow[index],
            fData->channel_id[index],
            channel_trigger_time_long,
            channel_energy,
            crystal_id,
            detector_id,
            fData->wr_subsystem_id,
            wr_t
        );
    }


    fNEvent += 1;
    return kTRUE;
}

void GermaniumReader::Reset()
{
    // reset output array
    fArray->Clear();
}

ClassImp(GermaniumReader);
