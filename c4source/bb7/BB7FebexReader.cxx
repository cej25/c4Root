#include "FairLogger.h"
#include "FairRootManager.h"

#include "BB7FebexData.h"
#include "BB7FebexReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_bb7febex.h"
}

BB7FebexReader::BB7FebexReader(EXT_STR_h101_bb7febex_onion* data, size_t offset)
    :   c4Reader("BB7FebexReader")
    ,   fNEvent(0)
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   bb7array(new std::vector<BB7FebexItem>)
{

}

BB7FebexReader::~BB7FebexReader()
{
    delete bb7array;
}

Bool_t BB7FebexReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_bb7febex_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_bb7febex, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    FairRootManager::Instance()->RegisterAny("BB7FebexData", bb7array, !fOnline);
    bb7array->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t BB7FebexReader::Read()
{
    if (!fData) return kTRUE;
    bb7array->clear();

    int64_t wr_t = (((uint64_t)fData->bbsfebex_ts_t[3]) << 48) + (((uint64_t)fData->bbsfebex_ts_t[2]) << 32) + (((uint64_t)fData->bbsfebex_ts_t[1]) << 16) + (uint64_t)(fData->bbsfebex_ts_t[0]);
    uint32_t wr_id = fData->bbsfebex_ts_subsystem_id;

    for (int it_board_number = 0; it_board_number < NBoards; it_board_number ++)
    {
        //since the febex card has a 100MHz clock which timestamps events.
        uint16_t trig = fData->bbsfebex_data[it_board_number].trig;
        uint64_t event_trigger_time_long = (((uint64_t)(fData->bbsfebex_data[it_board_number].event_trigger_time_hi) << 32) + (fData->bbsfebex_data[it_board_number].event_trigger_time_lo))*10;
        
        if (event_trigger_time_long <= 0) continue; // skip boards that don't fire, since NBoards is set to absolute maximum
  
        uint32_t board_num = fData->bbsfebex_data[it_board_number].board_num;

        //::::::::::::::Multiplicity: Called num_channels_fired from unpacker
        uint32_t M = fData->bbsfebex_data[it_board_number].num_channels_fired;

        for (int index = 0; index < M; index++) //GENERAL
        {
            //::::::::::::::Channel ID
            uint8_t channel_id = fData->bbsfebex_data[it_board_number].channel_idv[index];

            //::::::::::::::Channel Trigger Time
            uint64_t channel_trigger_time_long = (((uint64_t)(fData->bbsfebex_data[it_board_number].channel_trigger_time_hiv[index]) << 32) + 
            (fData->bbsfebex_data[it_board_number].channel_trigger_time_lov[index]))*10;

            //::::::::::::::Channel PileUp
            bool pileup = fData->bbsfebex_data[it_board_number].pileupv[index] & 0x1;
    
            //::::::::::::::Channel OverFlow
            bool overflow = fData->bbsfebex_data[it_board_number].overflowv[index] & 0x1;

            //::::::::::::::Channel Energy
            //according to febex manual on gsi website, the 24th bit of the energy denotes the sign to indicate the polarity of the pulse
            if (fData->bbsfebex_data[it_board_number].channel_energyv[index] & (1 << 23))
            {
                energy = -(int32_t)(fData->bbsfebex_data[it_board_number].channel_energyv[index] & 0x007FFFFF);
            }
            else
            {
                energy = +(int32_t)(fData->bbsfebex_data[it_board_number].channel_energyv[index] & 0x007FFFFF);            
            }

            // uint32_t ch_energy = energy;

            std::vector<uint16_t> trace;
        
            uint8_t channel_id_trace = fData->bbsfebex_data[it_board_number].trace_channel_id_tracesv[index];

            //::::::::::::::Channel Traces with ID from channel header
            for (int l = 0 ; l < fData->bbsfebex_data[it_board_number].trace_traces[channel_id_trace]._ ; l++)
            {
                trace.emplace_back(fData->bbsfebex_data[it_board_number].trace_traces[channel_id_trace].v[l]);    
            }

            auto & entry = bb7array->emplace_back();
            entry.SetAll(
                wr_t,
                wr_id, 
                board_num,
                event_trigger_time_long,
                channel_id,
                channel_trigger_time_long,
                pileup,
                overflow,
                energy,
                channel_id_trace,
                trace
            );

        }
    }

    fNEvent += 1;
    return kTRUE;

}

void BB7FebexReader::Reset()
{

}

ClassImp(BB7FebexReader)