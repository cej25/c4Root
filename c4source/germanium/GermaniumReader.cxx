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

GermaniumReader::~GermaniumReader() { 
    delete fArray;

}

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

    //since the febex card has a 100MHz clock which timestamps events.
    event_trigger_time_long = (((uint64_t)(fData->event_trigger_time_hi) << 32) + (fData->event_trigger_time_lo))*10;
    //whiterabbit timestamp:
    wr_t = (((uint64_t)fData->wr_t[3]) << 48) + (((uint64_t)fData->wr_t[2]) << 32) + (((uint64_t)fData->wr_t[1]) << 16) + (uint64_t)(fData->wr_t[0]);

    if (WriteZeroMultEvents & (fData->num_channels_fired == 0)){ 
        // Write if flag is true. See setter to change behaviour.
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
            fData->wr_subsystem_id,
            wr_t
        );
    }

    for (int index = 0; index < fData->num_channels_fired; index++)
    {   

        if (VetoOverflow & fData->overflow[index]) continue;
        if (VetoPileup & fData->pileup[index]) continue;
        

        //according to febex manual on gsi website the 24th bit of the energy bits denotes the sign to indicate the polarity of the pulse?
        if (fData->channel_energy[index] & (1 << 23)){
            channel_energy = -(int32_t)(fData->channel_energy[index] & 0x007FFFFF);
        }else{
            channel_energy = +(int32_t)(fData->channel_energy[index] & 0x007FFFFF);            
        }


        //collect the LSB and MSB into one variable for channel trigger time
        channel_trigger_time_long = (double)(((uint64_t)(fData->channel_trigger_time_hi[index]) << 32) + (fData->channel_trigger_time_lo[index]));
        //add the CF from the constant fraction. It is denoted by 6 bits in the energy word of the FEBEX data format
        channel_trigger_time_long = (((double)fData->channel_cfd[index])/64.0 + channel_trigger_time_long)*10.0; // units of ns 


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

ClassImp(GermaniumReader)
