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
    #include "ext_h101_germanium.h"
}

GermaniumReader::GermaniumReader(EXT_STR_h101_germanium_onion* data, size_t offset)
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

    EXT_STR_h101_germanium_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_germanium, 0);

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


Bool_t GermaniumReader::Read()
{
    c4LOG(debug1, "Event Data");

    if(!fData) return kTRUE;
    
    //whiterabbit timestamp:
    wr_t = (((uint64_t)fData->germanium_ts_t[3]) << 48) + (((uint64_t)fData->germanium_ts_t[2]) << 32) + (((uint64_t)fData->germanium_ts_t[1]) << 16) + (uint64_t)(fData->germanium_ts_t[0]);
    
    for (int it_board_number = 0; it_board_number < NBoards; it_board_number ++){
        //since the febex card has a 100MHz clock which timestamps events.
        //the event trigger time is to within a
        event_trigger_time_long = (((uint64_t)(fData->germanium_data[it_board_number].event_trigger_time_hi) << 32) + (fData->germanium_data[it_board_number].event_trigger_time_lo))*10;
    
        if (WriteZeroMultEvents & (fData->germanium_data[it_board_number].channel_energy == 0)){ 
            // Write if flag is true. See setter to change behaviour.
            new ((*fArray)[fArray->GetEntriesFast()]) GermaniumFebexData(
                fData->germanium_data[it_board_number].channel_energy,
                event_trigger_time_long,
                fData->germanium_data[it_board_number].hit_pattern,
                it_board_number,
                0,
                0,
                0,
                0,
                0,
                0,//fData->germanium_ts_subsystem_id,
                wr_t
            );
        }
        
        //the fData->germ.channel_energy/channel_cfd/etc contain the length of their individual arrays, and the channel_energyI arrays are the indices that they were written with in ucesb, which in our case is the channel id. Lastly the channel_energyv is the value.
        if (fData->germanium_data[it_board_number].channel_energy != fData->germanium_data[it_board_number].channel_cfd) c4LOG(warning,"Inconsistent size of arrays");

        for (int index = 0; index < fData->germanium_data[it_board_number].channel_energy; index++)
        {   
            
            
            //c4LOG(info,Form("channel_energy = %i, channel_energyI[%i] = %d, channel_energyv[%i] = %d;",fData->germanium_data[it_board_number].channel_energy,index,fData->germanium_data[it_board_number].channel_energyI[index],index,fData->germanium_data[it_board_number].channel_energyv[index]));
            //c4LOG(info,Form("channel_id = %i, channel_idI[%i] = %d, channel_idv[%i] = %d;",fData->germanium_data[it_board_number].channel_id,index,fData->germanium_data[it_board_number].channel_idI[index],index,fData->germanium_data[it_board_number].channel_idv[index]));
            if (fData->germanium_data[it_board_number].channel_trigger_time_hiI[index] != fData->germanium_data[it_board_number].channel_trigger_time_loI[index]) c4LOG(fatal, "Wrong in array fillings. channel_trigger_time_loI != channel_trigger_time_hiI "); 
            if (fData->germanium_data[it_board_number].channel_trigger_time_hiI[index] != fData->germanium_data[it_board_number].pileupI[index]) c4LOG(fatal, "Wrong in array fillings. pileupI != channel_trigger_time_hiI ");
            if (fData->germanium_data[it_board_number].channel_trigger_time_hiI[index] != fData->germanium_data[it_board_number].overflowI[index]) c4LOG(fatal, "Wrong in array fillings. overflowI != channel_trigger_time_hiI ");
            if (fData->germanium_data[it_board_number].channel_trigger_time_hiI[index] != fData->germanium_data[it_board_number].channel_cfdI[index]) c4LOG(fatal, "Wrong in array fillings. channel_cfdI != channel_trigger_time_hiI ");
            if (fData->germanium_data[it_board_number].channel_trigger_time_hiI[index] != fData->germanium_data[it_board_number].channel_energyI[index]) c4LOG(fatal, "Wrong in array fillings. channel_energyI != channel_trigger_time_hiI ");
            
            
            
            
            

            if (VetoOverflow & fData->germanium_data[it_board_number].overflowv[index]) continue;
            if (VetoPileup & fData->germanium_data[it_board_number].pileupv[index]) continue;
            

            //according to febex manual on gsi website, the 24th bit of the energy denotes the sign to indicate the polarity of the pulse
            if (fData->germanium_data[it_board_number].channel_energyv[index] & (1 << 23)){
                channel_energy = -(int32_t)(fData->germanium_data[it_board_number].channel_energyv[index] & 0x007FFFFF);
            }else{
                channel_energy = +(int32_t)(fData->germanium_data[it_board_number].channel_energyv[index] & 0x007FFFFF);            
            }


            //collect the LSB and MSB into one variable for channel trigger time
            channel_trigger_time_long = (double)(((uint64_t)(fData->germanium_data[it_board_number].channel_trigger_time_hiv[index]) << 32) + (fData->germanium_data[it_board_number].channel_trigger_time_lov[index]));
            //add the CF from the constant fraction. It is denoted by 6 bits in the energy word of the FEBEX data format
            channel_trigger_time_long = (((double)fData->germanium_data[it_board_number].channel_cfdv[index])/64.0 + channel_trigger_time_long)*10.0; // units of ns 


            new ((*fArray)[fArray->GetEntriesFast()]) GermaniumFebexData(
                fData->germanium_data[it_board_number].channel_energy,
                event_trigger_time_long,
                fData->germanium_data[it_board_number].hit_pattern,
                it_board_number,
                fData->germanium_data[it_board_number].pileupv[index],
                fData->germanium_data[it_board_number].overflowv[index],
                fData->germanium_data[it_board_number].channel_energyI[index], //this is the channel id
                channel_trigger_time_long,
                channel_energy,
                fData->germanium_ts_subsystem_id,
                wr_t //+ (uint64_t)((int64_t)channel_trigger_time_long - (int64_t)event_trigger_time_long)
            );
        }

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
