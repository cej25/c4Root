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

FrsTPCReader::FrsTPCReader(EXT_STR_h101_frstpc_onion* data, size_t offset)
    : c4Reader("FrsTPCReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("FrsTPCData"))
{
}

FrsTPCReader::~FrsTPCReader() 
{ 
    if (fArray != nullptr) delete fArray;
    c4LOG(info, "Destroyed FrsTPCReader properly.");
}

Bool_t FrsTPCReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");
    
    EXT_STR_h101_frstpc_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_frstpc, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->Register("FrsTPCData", "FRS TPC Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    c4LOG(info, "FrsTPCReader init complete.");

    return kTRUE;
}

Bool_t FrsTPCReader::Read()
{
    c4LOG(debug1, "Event data");

    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;


    // v775
    for (int i = 0; i < fData->frstpc_data_v775_n; i++)
    {   
        v7x5_geo[0].emplace_back(fData->frstpc_data_v775_geov[i]);
        v7x5_channel[0].emplace_back(fData->frstpc_data_v775_channelv[i]);
        v7x5_data[0].emplace_back(fData->frstpc_data_v775_data[i]);
    }

    // v785
    for (int i = 0; i < fData->frstpc_data_v775_n; i++)
    {   
        v7x5_geo[1].emplace_back(fData->frstpc_data_v785_geov[i]);
        v7x5_channel[1].emplace_back(fData->frstpc_data_v785_channelv[i]);
        v7x5_data[1].emplace_back(fData->frstpc_data_v785_data[i]);
    }

    // v1190
    uint32_t chn_first_hit = 0;
    uint32_t next_chn_first_hit, hits;

    for (uint32_t i = 0; i < fData->frstpc_data_v1190_nM; i++)
    {   
        next_chn_first_hit = fData->frstpc_data_v1190_nME[i];
        hits = next_chn_first_hit - chn_first_hit;

        for (uint32_t j = 0; j < hits; j++)
        {
            if (fData->frstpc_data_v1190_data[i * 128 + j] > 0)
            {
                v1190_channel.emplace_back(fData->frstpc_data_v1190_nMI[i]);
                v1190_data.emplace_back(fData->frstpc_data_v1190_data[i * 128 + j]);
                v1190_lot.emplace_back(fData->frstpc_data_v1190_leadOrTrailv[i * 128 + j]);
            }
            
        }

        chn_first_hit = next_chn_first_hit;
    }


    new ((*fArray)[fArray->GetEntriesFast()]) FrsTPCData(
        v7x5_geo,
        v7x5_channel,
        v7x5_data,
        v1190_channel,
        v1190_data,
        v1190_lot);
    

    fNEvent += 1;
    return kTRUE;

}

void FrsTPCReader::ZeroArrays()
{
    fArray->Clear();
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