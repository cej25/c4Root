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

// maybe no longer needed to define
#define TRACE_CHANNELS 16


LisaReader::LisaReader(EXT_STR_h101_lisa_onion* data, size_t offset)
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

    EXT_STR_h101_lisa_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_lisa, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    // register output array in a tree
    // CALUM: I set this up originally having two branches
    // 1. one for energy, channel ids etc
    // 2. one for trace data
    // you don't need to do that, necessarily. 
    FairRootManager::Instance()->Register("LisaData", "LISA Data", fArray, !fOnline);
    FairRootManager::Instance()->Register("LisaTraceData", "LISA Trace Data", fTraceArray, !fOnline);
    fArray->Clear();
    fTraceArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t LisaReader::Read()
{
    // Reading is done in here on a per-event basis!

    LisaData* lisa_item = new LisaData(); // LisaData class item

    //::::::::::::::White Rabbit::::::::::::::
    //WR time stamp
    uint64_t wr_time_long = (((uint64_t)fData->lisa_ts_t[3]) << 48) + 
    (((uint64_t)fData->lisa_ts_t[2]) << 32) + 
    (((uint64_t)fData->lisa_ts_t[1]) << 16) + 
    (uint64_t)(fData->lisa_ts_t[0]);
    lisa_item->Set_wr_t(wr_time_long);

    //WR ID. It is 0700 for lisa (= 1792 in decimal)
    uint32_t wr_id = fData->lisa_ts_subsystem_id;
    lisa_item->Set_wr_subsystem_id(wr_id);
    //::::::::::::::::::::::::::::::::::::::::

    //Loop over board number (NBoards hardcoded as 8 temp)
    for (int it_board_number = 0; it_board_number < NBoards; it_board_number++)
    {
        //LisaData* lisa_item = new LisaData(); // LisaData class item

        //::::::::::::::Board Number (=0 may2024)
        uint32_t board_num = fData->lisa_data[it_board_number].board_num;
        lisa_item->SetBoardNum(board_num);

        //::::::::::::::Event Time stamp (converted to ns)
        //P.S: Febex card has a 100MHz, it samples data every 10 ns (hence the unit and the *10 multiplication).
        uint64_t event_trigger_time_long = (((uint64_t)(fData->lisa_data[it_board_number].event_trigger_time_hi) << 32) + 
        (fData->lisa_data[it_board_number].event_trigger_time_lo))*10;
        lisa_item->SetEventTime(event_trigger_time_long);
        
        //::::::::::::::Hit Pattern
        uint32_t hit_pattern = fData->lisa_data[it_board_number].hit_pattern;
        std::vector<int> hitpattern = Get_Channels(hit_pattern);
        lisa_item->SetHitPattern(hitpattern);

        //::::::::::::::Multiplicity: Called num_channels_fired from unpacker
        uint32_t M = fData->lisa_data[it_board_number].num_channels_fired;
        lisa_item->SetMultiplicity(M);
        //std::cout<<M<<std::endl;

        std::vector<uint32_t> ch_ID; 
        std::vector<uint64_t> channel_trigger_time_long;
        std::vector<bool> pile_up;
        std::vector<bool> over_flow;
        std::vector<uint32_t> ch_energy;
        std::vector<uint32_t> traces;

        for (int index = 0; index < M; index++) 
        {
            //::::::::::::::Channel ID
            ch_ID.emplace_back(fData->lisa_data[it_board_number].channel_idv[index]);

            //::::::::::::::Channel Trigger Time
            channel_trigger_time_long.emplace_back((((uint64_t)(fData->lisa_data[it_board_number].channel_trigger_time_hiv[index]) << 32) + 
            (fData->lisa_data[it_board_number].channel_trigger_time_lov[index]))*10);

            //::::::::::::::Channel PileUp
            pile_up.emplace_back(fData->lisa_data[it_board_number].pileup[index] & 0x1);
    
            //::::::::::::::Channel OverFlow
            over_flow.emplace_back(fData->lisa_data[it_board_number].overflow[index] & 0x1);

            //::::::::::::::Channel Energy
            //according to febex manual on gsi website, the 24th bit of the energy denotes the sign to indicate the polarity of the pulse
            if (fData->lisa_data[it_board_number].channel_energyv[index] & (1 << 23)){
                energy = -(int32_t)(fData->lisa_data[it_board_number].channel_energyv[index] & 0x007FFFFF);
            }else{
                energy = +(int32_t)(fData->lisa_data[it_board_number].channel_energyv[index] & 0x007FFFFF);            
            }
            ch_energy.emplace_back(energy);
            
            //::::::::::::::Channel Traces
            for (int l = 0 ; l < fData->lisa_data[it_board_number].traces[index]._ ; l++)
            {
                traces.emplace_back(fData->lisa_data[it_board_number].traces[index].v[l]);

                std::cout<< fData->lisa_data[it_board_number].traces[index].I[l] <<std::endl;
            }

        }

        lisa_item->SetID(ch_ID);
        lisa_item->SetChannelTime(channel_trigger_time_long);
        lisa_item->SetPileUp(pile_up);
        lisa_item->SetOverFlow(over_flow);
        lisa_item->SetEnergy(ch_energy);
        lisa_item->SetTraces(traces);

        //Fill array with lisa_item
        new ((*fArray)[fArray->GetEntriesFast()]) LisaData(*lisa_item);

    }
    
    return kTRUE;
}


std::vector<int> LisaReader::Get_Channels(uint32_t channel_mask)
{
    std::vector<int> channels;

    for (int i = 15; i >= 0; i--)
    {
        if (channel_mask >= pow(2, i))
        {
            channels.push_back(i);
            channel_mask -= pow(2, i);
        }
    }

    std::sort(channels.begin(), channels.end());

    return channels;
}

// You must clear any arrays and vectors you use or things will get weird
void LisaReader::ZeroArrays()
{   
    fArray->Clear();
    fTraceArray->Clear();
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
