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
 *                             J.E.L. Larsson                                 *
 *                                06.05.25                                    *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "GermaniumFebexData.h"
#include "AgataTraceReader.h"
#include "AgataSuperTraceData.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_agata.h"
}

AgataTraceReader::AgataTraceReader(EXT_STR_h101_agata_onion* data, size_t offset)
    : c4Reader("AgataTraceReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("GermaniumFebexTraceData"))
{
}

AgataTraceReader::~AgataTraceReader() { 
    delete fArray;

}

Bool_t AgataTraceReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;

    EXT_STR_h101_agata_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_agata, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->Register("GermaniumFebexTraceData", "Germanium Febex Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}


Bool_t AgataTraceReader::Read()
{
    c4LOG(debug1, "Event Data");

    if(!fData) return kTRUE;
    
    //whiterabbit timestamp:
    wr_t = (((uint64_t)fData->agata_ts_t[3]) << 48) + (((uint64_t)fData->agata_ts_t[2]) << 32) + (((uint64_t)fData->agata_ts_t[1]) << 16) + (uint64_t)(fData->agata_ts_t[0]);
    
    for (int it_board_number = 0; it_board_number < NBoards; it_board_number ++){
        //since the febex card has a 100MHz clock which timestamps events.
        //the event trigger time is to within a
        //((uint64_t)(fData->agata_data[it_board_number].event_trigger_time_hi) << 32)
        event_trigger_time_long = ((fData->agata_data[it_board_number].event_trigger_time_lo & 0x00FFFFFF ))*10;
    
        if (WriteZeroMultEvents & (fData->agata_data[it_board_number].channel_energy == 0)){ 
            // Write if flag is true. See setter to change behaviour.
            new ((*fArray)[fArray->GetEntriesFast()]) GermaniumFebexTraceData(
                fData->agata_data[it_board_number].channel_energy,
                event_trigger_time_long,
                fData->agata_data[it_board_number].hit_pattern,
                it_board_number,
                0,
                0,
                0,
                0,
                0,
                0,//fData->agata_ts_subsystem_id,
                wr_t
            );
        }
        
        //the fData->germ.channel_energy/channel_cfd/etc contain the length of their individual arrays, and the channel_energyI arrays are the indices that they were written with in ucesb, which in our case is the channel id. Lastly the channel_energyv is the value.
        if (fData->agata_data[it_board_number].channel_energy != fData->agata_data[it_board_number].channel_cfd) c4LOG(warning,"Inconsistent size of arrays");

        for (int index = 0; index < fData->agata_data[it_board_number].channel_energy; index++)
        {   
            
            
            //c4LOG(info,Form("channel_energy = %i, channel_energyI[%i] = %d, channel_energyv[%i] = %d;",fData->agata_data[it_board_number].channel_energy,index,fData->agata_data[it_board_number].channel_energyI[index],index,fData->agata_data[it_board_number].channel_energyv[index]));
            //c4LOG(info,Form("channel_id = %i, channel_idI[%i] = %d, channel_idv[%i] = %d;",fData->agata_data[it_board_number].channel_id,index,fData->agata_data[it_board_number].channel_idI[index],index,fData->agata_data[it_board_number].channel_idv[index]));
            if (fData->agata_data[it_board_number].channel_trigger_time_hiI[index] != fData->agata_data[it_board_number].channel_trigger_time_loI[index]) c4LOG(fatal, "Wrong in array fillings. channel_trigger_time_loI != channel_trigger_time_hiI "); 
            if (fData->agata_data[it_board_number].channel_trigger_time_hiI[index] != fData->agata_data[it_board_number].pileupI[index]) c4LOG(fatal, "Wrong in array fillings. pileupI != channel_trigger_time_hiI ");
            if (fData->agata_data[it_board_number].channel_trigger_time_hiI[index] != fData->agata_data[it_board_number].overflowI[index]) c4LOG(fatal, "Wrong in array fillings. overflowI != channel_trigger_time_hiI ");
            if (fData->agata_data[it_board_number].channel_trigger_time_hiI[index] != fData->agata_data[it_board_number].channel_cfdI[index]) c4LOG(fatal, "Wrong in array fillings. channel_cfdI != channel_trigger_time_hiI ");
            if (fData->agata_data[it_board_number].channel_trigger_time_hiI[index] != fData->agata_data[it_board_number].channel_energyI[index]) c4LOG(fatal, "Wrong in array fillings. channel_energyI != channel_trigger_time_hiI ");
            

            if (VetoOverflow && fData->agata_data[it_board_number].overflowv[index]) continue;
            if (VetoPileup && fData->agata_data[it_board_number].pileupv[index]) continue;
            

            //according to febex manual on gsi website, the 24th bit of the energy denotes the sign to indicate the polarity of the pulse
            if (fData->agata_data[it_board_number].channel_energyv[index] & (1 << 23)){
                channel_energy = -(int32_t)(fData->agata_data[it_board_number].channel_energyv[index] & 0x007FFFFF);
            }else{
                channel_energy = +(int32_t)(fData->agata_data[it_board_number].channel_energyv[index] & 0x007FFFFF);            
            }


            //collect the LSB and MSB into one variable for channel trigger time
            //((uint64_t)(fData->agata_data[it_board_number].channel_trigger_time_hiv[index]) << 32)
            //chop some more digits of it:
            channel_trigger_time_long = (double)( (fData->agata_data[it_board_number].channel_trigger_time_lov[index]) & 0x00FFFFFF );
            //add the CF from the constant fraction. It is denoted by 6 bits in the energy word of the FEBEX data format
            channel_trigger_time_long = (((double)(fData->agata_data[it_board_number].channel_cfdv[index] & 0x3F))/64.0 + channel_trigger_time_long)*10.0; // units of ns 




            GermaniumFebexTraceData * last_entry = new ((*fArray)[fArray->GetEntriesFast()]) GermaniumFebexTraceData(
                fData->agata_data[it_board_number].channel_energy,
                event_trigger_time_long,
                fData->agata_data[it_board_number].hit_pattern,
                it_board_number,
                fData->agata_data[it_board_number].pileupv[index],
                fData->agata_data[it_board_number].overflowv[index],
                fData->agata_data[it_board_number].channel_energyI[index], //this is the channel id
                channel_trigger_time_long,
                channel_energy,
                fData->agata_ts_subsystem_id,
                wr_t //+ (uint64_t)((int64_t)channel_trigger_time_long - (int64_t)event_trigger_time_long)
            );

        }

        for (int index = 0; index < fData->agata_data[it_board_number].trace_channel_id_traces; index++){
            int channel_id_trace = fData->agata_data[it_board_number].trace_channel_id_tracesv[index];
            GermaniumFebexTraceData * entry = nullptr;

            for (int ich = 0; ich < fArray->GetEntriesFast(); ich++){
                if (((GermaniumFebexTraceData*)fArray->At(ich))->Get_channel_id() != channel_id_trace+1 || ((GermaniumFebexTraceData*)fArray->At(ich))->Get_board_id() != it_board_number){
                    continue;
                }else{
                    entry = (GermaniumFebexTraceData *)fArray->At(ich);
                }
            }
            
            if (entry == nullptr) {
                entry = new ((*fArray)[fArray->GetEntriesFast()]) GermaniumFebexTraceData(
                0,
                event_trigger_time_long,
                fData->agata_data[it_board_number].hit_pattern,
                it_board_number,
                0,
                0,
                channel_id_trace+1, //this is the channel id
                0,
                0,
                fData->agata_ts_subsystem_id,
                wr_t //+ (uint64_t)((int64_t)channel_trigger_time_long - (int64_t)event_trigger_time_long)
                );

            }

            for (int l = 0 ; l < fData->agata_data[it_board_number].trace_traces[channel_id_trace]._ ; l++)
            {
                if (l>=TRACE_LENGTH) break;
                entry->Set_trace_value(fData->agata_data[it_board_number].trace_traces[channel_id_trace].v[l],l);
            }
            //c4LOG(info,Form("board = %i, ch = %i", it_board_number, channel_id_trace));
        }
    }
    fNEvent += 1;
    return kTRUE;
}



void AgataTraceReader::Reset()
{
    // reset output array
    fArray->Clear();
}

ClassImp(AgataTraceReader)
