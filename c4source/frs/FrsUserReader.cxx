// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FrsUserData.h"
#include "FrsUserReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include <vector>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h" 
    #include "ext_h101_frsuser.h"
}

FrsUserReader::FrsUserReader(EXT_STR_h101_frsuser_onion* data, size_t offset)
    :   c4Reader("FrsUserReader")
    ,   fNEvent(0)
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   v7x5array(new std::vector<FrsUserV7X5Item>)
    ,   v830array(new std::vector<FrsUserV830Item>)
{
}

FrsUserReader::~FrsUserReader()
{
    c4LOG(info, "Destroyed FrsUserReader properly.");
}

Bool_t FrsUserReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;

    EXT_STR_h101_frsuser_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_frsuser, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    FairRootManager::Instance()->RegisterAny("FrsUserV7X5Data", v7x5array, !fOnline);
    FairRootManager::Instance()->RegisterAny("FrsUserV830Data", v830array, !fOnline);
    v830array->clear();
    v7x5array->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FrsUserReader::Read()
{
    v830array->clear();
    v7x5array->clear();

    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;


    // nothing to do if all arrays are empty:   
    // if (fData->frsuser_data_v7751n == 0 &&  fData->frsuser_data_v7752n == 0 && fData->frsuser_data_v7851n == 0 && fData->frsuser_data_v7852n == 0) return kTRUE;

    // V830 Scalers -- we should rename to be general
    for (int i = 0; i < fData->SCALERS[1]._; i++)
    {
        uint32_t index = fData->SCALERS[1].I[i];
        uint32_t scaler = fData->SCALERS[1].v[i];
        auto & entry = v830array->emplace_back();
        entry.SetAll(index, scaler);
    }

    // // v830 scalers
    // scalers_n = fData->frsuser_data_v830_n;
    // for (uint32_t i = 0; i < scalers_n; i++)
    // {   
    //     auto & entry = v830array->emplace_back();
    //     uint32_t index = fData->frsuser_data_v830_nI[i];
    //     uint32_t scaler = fData->frsuser_data_v830_data[i];
    //     entry.SetAll(index, scaler);
    // }

    // v775 x2
    // for (int i = 0; i < fData->frsuser_data_v7751n; i++)
    // {
    //     auto & entry = v7x5array->emplace_back();
    //     uint32_t geo = fData->frsuser_data_v7751geov[i];
    //     uint32_t channel = fData->frsuser_data_v7751channelv[i];
    //     uint32_t data = fData->frsuser_data_v7751data[i];
    //     entry.SetAll(geo, channel, data);
    // }
    // for (int i = 0; i < fData->frsuser_data_v7752n; i++)
    // {
    //     auto & entry = v7x5array->emplace_back();
    //     uint32_t geo = fData->frsuser_data_v7752geov[i];
    //     uint32_t channel = fData->frsuser_data_v7752channelv[i];
    //     uint32_t data = fData->frsuser_data_v7752data[i];
    //     entry.SetAll(geo, channel, data);
    //     v7x5_geo[1].emplace_back(fData->frsuser_data_v7752geov[i]);
    //     v7x5_channel[1].emplace_back(fData->frsuser_data_v7752channelv[i]);
    //     v7x5_data[1].emplace_back(fData->frsuser_data_v7752data[i]);
    // }

    // v785
    // for (int i = 0; i < fData->frsuser_data_v7851n; i++)
    // {
    //     auto & entry = v7x5array->emplace_back();
    //     uint32_t geo = fData->frsuser_data_v7851geov[i];
    //     uint32_t channel = fData->frsuser_data_v7851channelv[i];
    //     uint32_t data = fData->frsuser_data_v7851data[i];
    //     entry.SetAll(geo, channel, data);
    // }
    // for (int i = 0; i < fData->frsuser_data_v7852n; i++)
    // {
    //     auto & entry = v7x5array->emplace_back();
    //     uint32_t geo = fData->frsuser_data_v7852geov[i];
    //     uint32_t channel = fData->frsuser_data_v7852channelv[i];
    //     uint32_t data = fData->frsuser_data_v7852data[i];
    //     entry.SetAll(geo, channel, data);
    // }

    //c4LOG(info,Form("size of vectors: %d %d %d",v7x5_geo[1].at(0),v7x5_geo[2].at(0),v7x5_geo[3].at(0)));
    //c4LOG(info,Form("size of vectors: %d %d %d %d",fData->frsuser_data_v7751n,fData->frsuser_data_v7752n,fData->frsuser_data_v7851n,fData->frsuser_data_v7852n));
    //c4LOG(info,Form("size of vectors: %d %d %d %d",v7x5_data[0].size(),v7x5_data[1].size(),v7x5_data[2].size(),v7x5_data[3].size()));
    //c4LOG(info,Form("size of vectors: %d %d %d",v7x5_data[1].at(0),v7x5_data[2].at(0),v7x5_data[3].at(0)));

    fNEvent++;
    return kTRUE;

}

void FrsUserReader::ZeroArrays()
{
}

void FrsUserReader::ClearVectors()
{
    for (int i = 0; i < 4; i++)
    {
        v7x5_geo[i].clear();
        v7x5_channel[i].clear();
        v7x5_data[i].clear();
    }
    scalers_index.clear();
    scalers_user.clear();
}


void FrsUserReader::Reset()
{
    ZeroArrays();
    ClearVectors();
}

ClassImp(FrsUserReader)