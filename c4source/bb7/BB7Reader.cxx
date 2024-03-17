#include "FairLogger.h"
#include "FairRootManager.h"

#include "BB7FebexData.h"
#include "BB7Reader.h"


#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_bb7febex.h"
}

BB7Reader::BB7Reader(EXT_STR_h101_bb7febex_onion* data, size_t offset)
    :   c4Reader("BB7Reader")
    ,   fNEvent(0)
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   fArray(new TClonesArray("BB7FebexData"))
{

}

BB7Reader::~BB7Reader()
{
    delete fArray;
}

Bool_t BB7Reader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_bb7febex_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_bb7febex, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    FairRootManager::Instance()->Register("BB7FebexData", "BB7 Febex Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t BB7Reader::Read()
{
    c4LOG(debug1, "Event Data");

    if (!fData) return kTRUE;

    // CEJ: none of these are confirmed assests of structure header yet, without data its not possible
    // we're just setting up something basic
    wr_t = (((uint64_t)fData->bb7_ts_t[3]) << 48) + (((uint64_t)fData->bb7_ts_t[2]) << 32) + (((uint64_t)fData->bb7_ts_t[1]) << 16) + (uint64_t)(fData->bb7_ts_t[0]);

    // NBoards can come from configuration
    for (int it_board_number = 0; it_board_number < NBoards; it_board_number++)
    {
        event_trigger_time_long = (((uint64_t)(fData->bb7_data[it_board_number].event_trigger_time_hi) << 32) + (fData->bb7_data[it_board_number].event_trigger_time_lo)) * 10;

        // WriteZeroMultEvents

        if (fData->bb7_data[it_board_number].channel_energy != fData->bb7_data[it_board_number].channel_cfd) c4LOG(warn, "Inconsistent size of arrays");

        for (int index = 0; index < fData->bb7_data[it_board_number].channel_energy; index++)
        {
            // crash on mismatches, fix unpacker
            if (fData->bb7_data[it_board_number].channel_trigger_time_hiI[index] != fData->bb7_data[it_board_number].channel_trigger_time_loI[index]) c4LOG(fatal, "Wrong in array fillings. channel_trigger_time_loI != channel_trigger_time_hiI "); 
            if (fData->bb7_data[it_board_number].channel_trigger_time_hiI[index] != fData->bb7_data[it_board_number].pileupI[index]) c4LOG(fatal, "Wrong in array fillings. pileupI != channel_trigger_time_hiI ");
            if (fData->bb7_data[it_board_number].channel_trigger_time_hiI[index] != fData->bb7_data[it_board_number].overflowI[index]) c4LOG(fatal, "Wrong in array fillings. overflowI != channel_trigger_time_hiI ");
            if (fData->bb7_data[it_board_number].channel_trigger_time_hiI[index] != fData->bb7_data[it_board_number].channel_cfdI[index]) c4LOG(fatal, "Wrong in array fillings. channel_cfdI != channel_trigger_time_hiI ");
            if (fData->bb7_data[it_board_number].channel_trigger_time_hiI[index] != fData->bb7_data[it_board_number].channel_energyI[index]) c4LOG(fatal, "Wrong in array fillings. channel_energyI != channel_trigger_time_hiI ");

            // see germanium reader
            if (fData->bb7_data[it_board_number].channel_energyv[index] & (1 << 23))
            {
                channel_energy = -(int32_t)(fData->bb7_data[it_board_number].channel_energyv[index] & 0x007FFFFF);
            }
            else
            {
                channel_energy = +(int32_t)(fData->bb7_data[it_board_number].channel_energyv[index] & 0x007FFFFF);            
            }

            // collect the LSB and MSB into one variable for channel trigger time
            channel_trigger_time_long = (double)(((uint64_t)(fData->bb7_data[it_board_number].channel_trigger_time_hiv[index]) << 32) + (fData->bb7_data[it_board_number].channel_trigger_time_lov[index]));
            // add the CF from the constant fraction. It is denoted by 6 bits in the energy word of the FEBEX data format
            channel_trigger_time_long = (((double)fData->bb7_data[it_board_number].channel_cfdv[index])/64.0 + channel_trigger_time_long) * 10.0; // units of ns 

            new ((*fArray)[fArray->GetEntriesFast()]) BB7FebexData(
                fData->bb7_data[it_board_number].channel_energy,
                event_trigger_time_long,
                fData->bb7_data[it_board_number].hit_pattern,
                it_board_number,
                fData->bb7_data[it_board_number].pileupv[index],
                fData->bb7_data[it_board_number].overflowv[index],
                fData->bb7_data[it_board_number].channel_energyI[index], //this is the channel id
                channel_trigger_time_long,
                channel_energy,
                fData->bb7_ts_subsystem_id,
                wr_t
            );

        }

    }

    fNEvent += 1;
    return kTRUE;

}

void BB7Reader::Reset()
{
    fArray->Clear();
}

ClassImp(BB7Reader)