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
 *                       E.M. Gandolfo, C.E. Jones                            *
 *                               25.11.24                                     *
 ******************************************************************************/

#include "FairLogger.h"
#include "FairRootManager.h"

#include "LisaReader.h"
#include "c4Logger.h"
#include "TVector.h"

#include "ext_data_struct_info.hh"

// This is the adjustment to use TVectors instead of std::vector
//This was to try to read vectors of vectors form external macro without sourcing c4. It does not work.
//template <typename T>
//using StdVector = std::vector<T>;

#define TRACE_SIZE 3000 // used for the trace_x vector

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_lisa.h"
}

LisaReader::LisaReader(EXT_STR_h101_lisa_onion* data, size_t offset)
    : c4Reader("LisaReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , lisaArray(new std::vector<LisaItem>)
{
}

LisaReader::~LisaReader() 
{

}

Bool_t LisaReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_lisa_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_lisa, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    // register output array in a tree
    FairRootManager::Instance()->RegisterAny("LisaData", lisaArray, !fOnline);
    lisaArray->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t LisaReader::Read()
{
    lisaArray->clear();
    // Reading is done in here on a per-event basis!

    //::::::::::::::White Rabbit::::::::::::::
    //WR time stamp
    uint64_t wr_time_long = (((uint64_t)fData->lisa_ts_t[3]) << 48) + 
    (((uint64_t)fData->lisa_ts_t[2]) << 32) + 
    (((uint64_t)fData->lisa_ts_t[1]) << 16) + 
    (uint64_t)(fData->lisa_ts_t[0]);

    //WR ID. It is 700 for lisa (= 1792 in decimal). From May 13 WR = 1200 for LISA
    uint32_t wr_id = fData->lisa_ts_subsystem_id;
    //::::::::::::::::::::::::::::::::::::::::

    const int trace_size = TRACE_SIZE;

    std::vector<int16_t> trace_x(trace_size);
    for (int i = 0; i < trace_size; i++) {
        trace_x[i] = i;
    }
    
    //Loop over board number (NBoards hardcoded as 8 temp)
    for (int it_board_number = 0; it_board_number < NBoards; it_board_number++)
    {
        //::::::::::::::Event Time stamp (converted to ns)
        //P.S: Febex card has a 100MHz, it samples data every 10 ns (hence the unit and the *10 multiplication).
        uint64_t event_trigger_time_long = (((uint64_t)(fData->lisa_data[it_board_number].event_trigger_time_hi) << 32) + 
        (fData->lisa_data[it_board_number].event_trigger_time_lo))*10;

        //For empty event, skip. This filters the fake boards.
        if (event_trigger_time_long == 0) 
        {
            //std::cout<< " ::: iterator ::: " << it_board_number << std::endl;        
            continue;
        }
        
        //::::::::::::::Board Number (=0 may2024)
        uint32_t board_num = fData->lisa_data[it_board_number].board_num;

        //::::::::::::::Multiplicity: Called num_channels_fired from unpacker
        uint32_t M = fData->lisa_data[it_board_number].num_channels_fired; //This is not for cases when header is missing

        //for (int index = 0; index < 8; index++) //ONLY FOR JIKKEN -- All mode
        for (int index = 0; index < M; index++) //GENERAL
        {
            //::::::::::::::Channel ID
            int channel_id = fData->lisa_data[it_board_number].channel_idv[index];
            //std::cout << "Channel ID from header : " << static_cast<int>(channel_id) << std::endl;

            //::::::::::::::Channel Trigger Time
            uint64_t channel_trigger_time_long = (((uint64_t)(fData->lisa_data[it_board_number].channel_trigger_time_hiv[index]) << 32) + 
            (fData->lisa_data[it_board_number].channel_trigger_time_lov[index]))*10;

            /* Old pileup and overflow definition (up to 2024)
            //::::::::::::::Channel PileUp 
            bool pileup = fData->lisa_data[it_board_number].pileup[index] & 0x1; 
            //::::::::::::::Channel OverFlow
            bool overflow = fData->lisa_data[it_board_number].overflow[index] & 0x1;
            */ 
            /* New Pileup and Overflow definition (2025)
            FEBEX_EVENT_TRACES is changed.Now Pileup and Overflow are ZERO_SUPPRESSED
            This makes them into 3 branches {info, infoI, infov}
            (Same as for energy and traces)
            */
            //::::::::::::::Channel PileUp 
            bool pileup = fData->lisa_data[it_board_number].pileupv[index] & 0x1;
            //::::::::::::::Channel OverFlow
            bool overflow = fData->lisa_data[it_board_number].overflowv[index] & 0x1;

            //::::::::::::::Channel Energy
            //according to febex manual on gsi website, the 24th bit of the energy denotes the sign to indicate the polarity of the pulse
            if (fData->lisa_data[it_board_number].channel_energyv[index] & (1 << 23)){
                energy = -(float)(fData->lisa_data[it_board_number].channel_energyv[index] & 0x007FFFFF);
            }else{
                energy = +(float)(fData->lisa_data[it_board_number].channel_energyv[index] & 0x007FFFFF);            
            }
            float ch_energy = energy;

            std::vector<float> trace;
            //std::vector<int16_t> trace_x;
            int channel_id_trace = fData->lisa_data[it_board_number].trace_channel_id_tracesv[index];

            //::::::::::::::Channel Traces with ID from channel header
            for (int l = 0 ; l < fData->lisa_data[it_board_number].trace_traces[channel_id_trace]._ ; l++)
            {
                trace.emplace_back(fData->lisa_data[it_board_number].trace_traces[channel_id_trace].v[l]);    
            }
            
            //::::::::::::::Traces Dimension (This is fixed from Febex (2000) but added for easier displaying)
            // for (int l = 0 ; l < fData->lisa_data[it_board_number].trace_traces[channel_id_trace]._ ; l++)
            // {
            //     trace_x.emplace_back(fData->lisa_data[it_board_number].trace_traces[channel_id_trace].I[l]);    
            // }

            //std::cout << "Channel ID from trace : " << static_cast<int>(channel_id_trace) << std::endl;

            // //::::::::::::::Channel Traces with ID from event header
            // for (int l = 0 ; l < fData->lisa_data[it_board_number].traces[channel_id]._ ; l++)
            // {
            //     trace.emplace_back(fData->lisa_data[it_board_number].traces[channel_id].v[l]);    
            // }

            auto & entry = lisaArray->emplace_back();
            entry.SetAll(
                wr_time_long,
                wr_id, 
                board_num,
                event_trigger_time_long,
                channel_id,
                channel_trigger_time_long,
                pileup,
                overflow,
                ch_energy,
                channel_id_trace,
                trace,
                trace_x
            );

        }

    }

    return kTRUE;
}

// You must clear any arrays and vectors you use or things will get weird
void LisaReader::ZeroArrays()
{ 

}

void LisaReader::ClearVectors()
{

}

void LisaReader::Reset()
{
    ZeroArrays();
    ClearVectors();
}

ClassImp(LisaReader);
