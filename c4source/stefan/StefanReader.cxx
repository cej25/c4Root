// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "StefanReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_stefan.h"
}

StefanReader::StefanReader(EXT_STR_h101_stefan_onion* data, size_t offset)
    : c4Reader("StefanReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , stefanArray(new std::vector<StefanFebexItem>)
{
}

StefanReader::~StefanReader() { 
    delete stefanArray;

}

Bool_t StefanReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;

    EXT_STR_h101_stefan_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_stefan, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->RegisterAny("StefanFebexData", stefanArray, !fOnline);
    stefanArray->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}


Bool_t StefanReader::Read()
{
    c4LOG(debug1, "Event Data");

    if(!fData) return kTRUE;
    
    //whiterabbit timestamp:
    wr_t = (((Long64_t)fData->stefan_ts_t[3]) << 48) + (((Long64_t)fData->stefan_ts_t[2]) << 32) + (((Long64_t)fData->stefan_ts_t[1]) << 16) + (Long64_t)(fData->stefan_ts_t[0]);
    

    for (int it_board_number = 0; it_board_number < NBoards; it_board_number ++)
    {
        //since the febex card has a 100MHz clock which timestamps events.
        //the event trigger time is to within a
        UShort_t trig = fData->stefan_data[it_board_number].trig;
        event_trigger_time_long = (((Long64_t)(fData->stefan_data[it_board_number].event_trigger_time_hi) << 32) + (fData->stefan_data[it_board_number].event_trigger_time_lo))*10;
    
        if (event_trigger_time_long == 0) continue; // skip boards that don't fire, since NBoards is set to absolute maximum
 
        //the fData->germ.channel_energy/channel_cfd/etc contain the length of their individual arrays, and the channel_energyI arrays are the indices that they were written with in ucesb, which in our case is the channel id. Lastly the channel_energyv is the value.
        if (fData->stefan_data[it_board_number].channel_energy != fData->stefan_data[it_board_number].channel_cfd) c4LOG(warning,"Inconsistent size of arrays");

        for (int index = 0; index < fData->stefan_data[it_board_number].channel_energy; index++)
        {   
            
            //c4LOG(info,Form("channel_energy = %i, channel_energyI[%i] = %d, channel_energyv[%i] = %d;",fData->stefan_data[it_board_number].channel_energy,index,fData->stefan_data[it_board_number].channel_energyI[index],index,fData->stefan_data[it_board_number].channel_energyv[index]));
            //c4LOG(info,Form("channel_id = %i, channel_idI[%i] = %d, channel_idv[%i] = %d;",fData->stefan_data[it_board_number].channel_id,index,fData->stefan_data[it_board_number].channel_idI[index],index,fData->stefan_data[it_board_number].channel_idv[index]));
            if (fData->stefan_data[it_board_number].channel_trigger_time_hiI[index] != fData->stefan_data[it_board_number].channel_trigger_time_loI[index]) c4LOG(fatal, "Wrong in array fillings. channel_trigger_time_loI != channel_trigger_time_hiI "); 
            if (fData->stefan_data[it_board_number].channel_trigger_time_hiI[index] != fData->stefan_data[it_board_number].pileupI[index]) c4LOG(fatal, "Wrong in array fillings. pileupI != channel_trigger_time_hiI ");
            if (fData->stefan_data[it_board_number].channel_trigger_time_hiI[index] != fData->stefan_data[it_board_number].overflowI[index]) c4LOG(fatal, "Wrong in array fillings. overflowI != channel_trigger_time_hiI ");
            if (fData->stefan_data[it_board_number].channel_trigger_time_hiI[index] != fData->stefan_data[it_board_number].channel_cfdI[index]) c4LOG(fatal, "Wrong in array fillings. channel_cfdI != channel_trigger_time_hiI ");
            if (fData->stefan_data[it_board_number].channel_trigger_time_hiI[index] != fData->stefan_data[it_board_number].channel_energyI[index]) c4LOG(fatal, "Wrong in array fillings. channel_energyI != channel_trigger_time_hiI ");
            
            
            
            
            

            if (VetoOverflow && fData->stefan_data[it_board_number].overflowv[index]) continue;
            if (VetoPileup && fData->stefan_data[it_board_number].pileupv[index]) continue;
            

            //according to febex manual on gsi website, the 24th bit of the energy denotes the sign to indicate the polarity of the pulse
            if (fData->stefan_data[it_board_number].channel_energyv[index] & (1 << 23)){
                channel_energy = -(int32_t)(fData->stefan_data[it_board_number].channel_energyv[index] & 0x007FFFFF);
            }else{
                channel_energy = +(int32_t)(fData->stefan_data[it_board_number].channel_energyv[index] & 0x007FFFFF);            
            }


            //collect the LSB and MSB into one variable for channel trigger time
            //chop some more digits of it:
            channel_trigger_time_long = (double)( (fData->stefan_data[it_board_number].channel_trigger_time_lov[index]) & 0x00FFFFFF );
            //add the CF from the constant fraction. It is denoted by 6 bits in the energy word of the FEBEX data format
            channel_trigger_time_long = (((double)(fData->stefan_data[it_board_number].channel_cfdv[index] & 0x3F))/64.0 + channel_trigger_time_long)*10.0; // units of ns 
            
            // if (fData->stefan_data[it_board_number].pileupv[index] == 1) std::cout << "pileup!! " << fData->stefan_data[it_board_number].pileupv[index] << std::endl; 

            auto & entry = stefanArray->emplace_back();
            entry.SetAll(wr_t,
                        fData->stefan_ts_subsystem_id,
                        it_board_number,
                        event_trigger_time_long,
                        fData->stefan_data[it_board_number].channel_energyI[index],
                        channel_trigger_time_long,
                        fData->stefan_data[it_board_number].pileupv[index],
                        fData->stefan_data[it_board_number].overflowv[index],
                        channel_energy);

        }

    }
    fNEvent += 1;
    return kTRUE;
}

void StefanReader::Reset()
{
    // reset output array
    stefanArray->clear();
}

ClassImp(StefanReader)
