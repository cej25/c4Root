/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                               C.E. Jones                                   *
 *                                06.05.25                                    *
 ******************************************************************************/

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
    #include "ext_h101_bbfebex.h"
}

BB7FebexReader::BB7FebexReader(EXT_STR_h101_bbfebex_onion* data, size_t offset)
    :   c4Reader("BB7FebexReader")
    ,   fNEvent(0)
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   bb7array(new std::vector<BB7FebexItem>)
    ,   bb7empty(new std::vector<BB7EmptyItem>)
{

}

BB7FebexReader::~BB7FebexReader()
{
    delete bb7array;
    delete bb7empty;
}

Bool_t BB7FebexReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_bbfebex_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_bbfebex, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    FairRootManager::Instance()->RegisterAny("BB7FebexData", bb7array, !fOnline);
    FairRootManager::Instance()->RegisterAny("BB7EmptyData", bb7empty, !fOnline);
    bb7array->clear();
    bb7empty->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t BB7FebexReader::Read()
{
    if (!fData) return kTRUE;
    bb7array->clear();
    bb7empty->clear();
    wr_t_first = 0;
    wr_t_second = 0;

    //int64_t wr_t = (((uint64_t)fData->bbsfebex_ts_t[3]) << 48) + (((uint64_t)fData->bbsfebex_ts_t[2]) << 32) + (((uint64_t)fData->bbsfebex_ts_t[1]) << 16) + (uint64_t)(fData->bbsfebex_ts_t[0]);
    wr_t_first = (((uint64_t)fData->bbfirst_ts_t[3]) << 48) + (((uint64_t)fData->bbfirst_ts_t[2]) << 32) + (((uint64_t)fData->bbfirst_ts_t[1]) << 16) + (uint64_t)(fData->bbfirst_ts_t[0]);
    uint32_t wr_id_first = fData->bbfirst_ts_subsystem_id;
    
    if (wr_t_first != 0)
    {
        nReads++;
        for (int it_board_number = 0; it_board_number < 5; it_board_number++)
        {
            //since the febex card has a 100MHz clock which timestamps events.
            uint16_t trig = fData->bbfirst_data[it_board_number].trig;
            uint64_t event_trigger_time_long = (((uint64_t)(fData->bbfirst_data[it_board_number].event_trigger_time_hi) << 32) + (fData->bbfirst_data[it_board_number].event_trigger_time_lo))*10;
            
            if (event_trigger_time_long <= 0) continue; // skip boards that don't fire, since NBoards is set to absolute maximum
    
            uint32_t board_num = fData->bbfirst_data[it_board_number].board_num;

            //::::::::::::::Multiplicity: Called num_channels_fired from unpacker
            uint32_t M = fData->bbfirst_data[it_board_number].num_channels_fired;

            if (M == 0 && n_zero_f0_0 == 0)
            {
                auto & entry = bb7empty->emplace_back();
                entry.SetAll(
                    wr_t_first,
                    wr_id_first,
                    0, // crate
                    board_num,
                    event_trigger_time_long
                );
                n_zero_f0_0++;
            }

            for (int index = 0; index < M; index++) //GENERAL
            {
                //::::::::::::::Channel ID
                uint32_t channel_id = fData->bbfirst_data[it_board_number].channel_idv[index];

                //::::::::::::::Channel Trigger Time
                uint64_t channel_trigger_time_long = (((uint64_t)(fData->bbfirst_data[it_board_number].channel_trigger_time_hiv[index]) << 32) + 
                (fData->bbfirst_data[it_board_number].channel_trigger_time_lov[index]))*10;

                //::::::::::::::Channel PileUp
                bool pileup = fData->bbfirst_data[it_board_number].pileupv[index] & 0x1;
        
                //::::::::::::::Channel OverFlow
                bool overflow = fData->bbfirst_data[it_board_number].overflowv[index] & 0x1;



                //::::::::::::::Channel Energy
                //according to febex manual on gsi website, the 24th bit of the energy denotes the sign to indicate the polarity of the pulse
                if (fData->bbfirst_data[it_board_number].channel_energyv[index] & (1 << 23))
                {
                    energy = -(int32_t)(fData->bbfirst_data[it_board_number].channel_energyv[index] & 0x007FFFFF);
                }
                else
                {
                    energy = +(int32_t)(fData->bbfirst_data[it_board_number].channel_energyv[index] & 0x007FFFFF);            
                }

                std::vector<UShort_t> trace;


                // this is changed from "index" to "channel_id" since sometimes we get less than 16 channels fired, but we always get 16 traces in order

                //::::::::::::::Channel Traces with ID from channel header
                for (int l = 0; l < fData->bbfirst_data[it_board_number].trace_traces[channel_id]._ ; l++)
                {
                    trace.emplace_back(fData->bbfirst_data[it_board_number].trace_traces[channel_id].v[l]);    
                }

                // if (energy < 0)
                // {
                //     std::cout << "trace size w neg energy: " << trace.size() << std::endl;
                // } 
                // else
                // {
                //     if (trace.size() > 0) std::cout << "yay?" << std::endl;
                // }


                auto & entry = bb7array->emplace_back();
                entry.SetAll(
                    wr_t_first,
                    wr_id_first,
                    0,
                    board_num,
                    event_trigger_time_long,
                    channel_id,
                    channel_trigger_time_long,
                    pileup,
                    overflow,
                    energy,
                    channel_id, // can be removed, "ID from trace header"
                    trace
                );

            }
        }
    } // check first wr to loop

    // bb7array->clear();

    // second crate solution I guess
    wr_t_second = (((uint64_t)fData->bbsecond_ts_t[3]) << 48) + (((uint64_t)fData->bbsecond_ts_t[2]) << 32) + (((uint64_t)fData->bbsecond_ts_t[1]) << 16) + (uint64_t)(fData->bbsecond_ts_t[0]);
    uint32_t wr_id_second = fData->bbsecond_ts_subsystem_id;

    if (wr_t_second != 0)
    {
        nReads++;
        for (int it_board_number = 0; it_board_number < 4; it_board_number++)
        {
            //since the febex card has a 100MHz clock which timestamps events.
            uint16_t trig = fData->bbsecond_data[it_board_number].trig;
            uint64_t event_trigger_time_long = (((uint64_t)(fData->bbsecond_data[it_board_number].event_trigger_time_hi) << 32) + (fData->bbsecond_data[it_board_number].event_trigger_time_lo))*10;
            
            if (event_trigger_time_long <= 0) continue; // skip boards that don't fire, since NBoards is set to absolute maximum
    
            uint32_t board_num = fData->bbsecond_data[it_board_number].board_num;

            //::::::::::::::Multiplicity: Called num_channels_fired from unpacker
            uint32_t M = fData->bbsecond_data[it_board_number].num_channels_fired;

            if (M == 0 && n_zero_f0_1 == 0)
            {
                auto & entry = bb7empty->emplace_back();
                entry.SetAll(
                    wr_t_second,
                    wr_id_second,
                    1, // crate
                    board_num,
                    event_trigger_time_long
                );
                n_zero_f0_1++;
            }

            for (int index = 0; index < M; index++) //GENERAL
            {
                //::::::::::::::Channel ID
                uint32_t channel_id = fData->bbsecond_data[it_board_number].channel_idv[index];

                //::::::::::::::Channel Trigger Time
                uint64_t channel_trigger_time_long = (((uint64_t)(fData->bbsecond_data[it_board_number].channel_trigger_time_hiv[index]) << 32) + 
                (fData->bbsecond_data[it_board_number].channel_trigger_time_lov[index]))*10;

                //::::::::::::::Channel PileUp
                bool pileup = fData->bbsecond_data[it_board_number].pileupv[index] & 0x1;
        
                //::::::::::::::Channel OverFlow
                bool overflow = fData->bbsecond_data[it_board_number].overflowv[index] & 0x1;

                //::::::::::::::Channel Energy
                //according to febex manual on gsi website, the 24th bit of the energy denotes the sign to indicate the polarity of the pulse
                bool check_polarity = fData->bbsecond_data[it_board_number].channel_energyv[index] & (1 << 23);
                if (check_polarity)
                {
                    energy = -(int32_t)(fData->bbsecond_data[it_board_number].channel_energyv[index] & 0x007FFFFF);
                }
                else
                {
                    energy = +(int32_t)(fData->bbsecond_data[it_board_number].channel_energyv[index] & 0x007FFFFF);            
                }

                std::vector<uint16_t> trace;

                // if (energy < 0) 
                // {
                //     std::cout << std::hex << energy << std::dec << std::endl;
                // }

                // this is changed from "index" to "channel_id" since sometimes we get less than 16 channels fired, but we always get 16 traces in order
                // not really sure what the solution for LISA is 

                //::::::::::::::Channel Traces with ID from channel header
                for (int l = 0 ; l < fData->bbsecond_data[it_board_number].trace_traces[channel_id]._ ; l++)
                {
                    trace.emplace_back(fData->bbsecond_data[it_board_number].trace_traces[channel_id].v[l]);    
                    // if (energy > 0) std::cout << trace.at(l) << std::endl;
                }

                // if (energy < 0)
                // {
                //     std::cout << "trace size w neg energy: " << trace.size() << std::endl;
                //     std::cout << "energy:: " << energy << std::endl;
                // } 
                // else
                // {
                //     if (trace.size() > 0) std::cout << "yay?" << std::endl;
                // }

                auto & entry = bb7array->emplace_back();
                entry.SetAll(
                    wr_t_second,
                    wr_id_second,
                    1, // crate
                    board_num,
                    event_trigger_time_long,
                    channel_id,
                    channel_trigger_time_long,
                    pileup,
                    overflow,
                    energy,
                    channel_id, // can be removed, "ID from trace header"
                    trace
                );

            }
        }
    }

    fNEvent += 1;
    return kTRUE;

}

void BB7FebexReader::Reset()
{
    energy = 0;
    n_zero_f0_0 = 0;
    n_zero_f0_1 = 0;
}

ClassImp(BB7FebexReader)