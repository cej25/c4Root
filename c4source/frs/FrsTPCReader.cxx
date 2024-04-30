// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FrsTPCData.h"
#include "FrsTPCReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include <vector>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h" 
    #include "ext_h101_frstpc.h"
}

#include <stdio.h>

FrsTPCReader::FrsTPCReader(EXT_STR_h101_frstpc_onion* data, size_t offset)
    : c4Reader("FrsTPCReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , v7x5array(new std::vector<FrsTPCV7X5Item>)
    , v1190array(new std::vector<FrsTPCV1190Item>)
{
}

FrsTPCReader::~FrsTPCReader() 
{ 
    c4LOG(info, "Destroyed FrsTPCReader properly.");
}

Bool_t FrsTPCReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    
    EXT_STR_h101_frstpc_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_frstpc, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->RegisterAny("FrsTPCV7X5Data", v7x5array, !fOnline);
    FairRootManager::Instance()->RegisterAny("FrsTPCV1190Data", v1190array, !fOnline);

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FrsTPCReader::Read()
{
    v7x5array->clear();
    v1190array->clear();

    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;

    bool bad_event = fData->frstpc_be;
    if (bad_event)
    {   
        bad_event_counter++;
        printf("\033[999;999H"); // move to bottom of screen
        printf("\033[2A"); // move up 2 lines?
        printf("\033[K"); // clear the line
        c4LOG(info, "TPC bad event! Number: " << bad_event_counter);
        printf("\033[1B"); // move down 1 line
        return kTRUE;
    }

    if (fData->frstpc_data_v775_n == 0 && fData->frstpc_data_v785_n == 0 && fData->frstpc_data_v1190_nM == 0) return kTRUE;
    ClearVectors();

    // v775 -- geo is 12??
    for (int i = 0; i < fData->frstpc_data_v775_n; i++)
    {   
        uint32_t geo = fData->frstpc_data_v775_geov[i];
        uint32_t channel = fData->frstpc_data_v775_channelv[i];
        uint32_t data = fData->frstpc_data_v775_data[i];
    
        auto & entry = v7x5array->emplace_back();
        entry.SetAll(geo, data, channel);
    }

    // v785 -- geo is 8???
    for (int i = 0; i < fData->frstpc_data_v785_n; i++)
    {   
        uint32_t geo = fData->frstpc_data_v785_geov[i];
        uint32_t channel = fData->frstpc_data_v785_channelv[i];
        uint32_t data = fData->frstpc_data_v785_data[i];

        auto & entry = v7x5array->emplace_back();
        entry.SetAll(geo, data, channel);
    }

    // v1190
  
    // this loops over a number of channels..is it a mistake?
    // should we loop over a number of hits? 
    int hit_index = 0;
    for (uint32_t channel_index = 0; channel_index < fData->frstpc_data_v1190_nM; channel_index++)
    {   
        int current_channel = fData->frstpc_data_v1190_nMI[channel_index];
        int next_channel_start = fData->frstpc_data_v1190_nME[channel_index];

        for (uint32_t j = hit_index; j < next_channel_start; j++)
        {   
            uint32_t channel = current_channel;
            uint32_t data = fData->frstpc_data_v1190_data[j];
            uint32_t lot = fData->frstpc_data_v1190_leadOrTrailv[j];

            auto & entry = v1190array->emplace_back();
            entry.SetAll(channel, data, lot);
        }

        hit_index = next_channel_start;
  
    }

    fNEvent += 1;
    return kTRUE;

}

void FrsTPCReader::ZeroArrays()
{

}

void FrsTPCReader::ClearVectors()
{
    for (int i = 0; i < 2; i++)
    {
        v7x5_geo[i].clear();
        v7x5_channel[i].clear();
        v7x5_data[i].clear();
    }
    v1190_channel.clear();
    v1190_data.clear();
    v1190_lot.clear();
}

void FrsTPCReader::Reset()
{
    ZeroArrays();
    ClearVectors();
}

ClassImp(FrsTPCReader);