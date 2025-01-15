#include "FairLogger.h"
#include "FairRootManager.h"

#include "BB7VmeData.h"
#include "BB7Reader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_bb7vme.h"
}

BB7Reader::BB7Reader(EXT_STR_h101_bb7vme_onion* data, size_t offset)
    :   c4Reader("BB7Reader")
    ,   fNEvent(0)
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   v7x5array(new std::vector<BB7V7x5Item>)
    ,   v1290array(new std::vector<BB7V1290Item>)
{

}

BB7Reader::~BB7Reader()
{
    delete v7x5array;
    delete v1290array;
}

Bool_t BB7Reader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_bb7vme_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_bb7vme, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    FairRootManager::Instance()->RegisterAny("BB7V7x5Data", v7x5array, !fOnline);
    FairRootManager::Instance()->RegisterAny("BB7V1290Data", v1290array, !fOnline);
    v7x5array->clear();
    v1290array->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t BB7Reader::Read()
{
    if (!fData) return kTRUE;

    wr_t = (((uint64_t)fData->bbseven_ts_t[3]) << 48) + (((uint64_t)fData->bbseven_ts_t[2]) << 32) + (((uint64_t)fData->bbseven_ts_t[1]) << 16) + (uint64_t)(fData->bbseven_ts_t[0]);

    for (int i = 0; i < fData->bbseven_v7x5_module1n; i++)
    {   
        uint32_t geo = fData->bbseven_v7x5_module1geov[i];
        uint32_t data = fData->bbseven_v7x5_module1data[i];
        uint32_t channel = fData->bbseven_v7x5_module1channelv[i];

        auto & entry = v7x5array->emplace_back();
        entry.SetAll(wr_t, geo, data, channel);
    }

    for (int i = 0; i < fData->bbseven_v7x5_module2n; i++)
    {   
        uint32_t geo = fData->bbseven_v7x5_module2geov[i];
        uint32_t data = fData->bbseven_v7x5_module2data[i];
        uint32_t channel = fData->bbseven_v7x5_module2channelv[i];

        auto & entry = v7x5array->emplace_back();
        entry.SetAll(wr_t, geo, data, channel);
    }

    for (int i = 0; i < fData->bbseven_v7x5_module3n; i++)
    {   
        uint32_t geo = fData->bbseven_v7x5_module3geov[i];
        uint32_t data = fData->bbseven_v7x5_module3data[i];
        uint32_t channel = fData->bbseven_v7x5_module3channelv[i];

        auto & entry = v7x5array->emplace_back();
        entry.SetAll(wr_t, geo, data, channel);
    }

    for (int i = 0; i < fData->bbseven_v7x5_module4n; i++)
    {   
        uint32_t geo = fData->bbseven_v7x5_module4geov[i];
        uint32_t data = fData->bbseven_v7x5_module4data[i];
        uint32_t channel = fData->bbseven_v7x5_module4channelv[i];

        auto & entry = v7x5array->emplace_back();
        entry.SetAll(wr_t, geo, data, channel);
    }

    // V1290
    int hit_index = 0;
    for (uint32_t channel_index = 0; channel_index < fData->bbseven_v1290_module_nM; channel_index++)
    {   
        int current_channel = fData->bbseven_v1290_module_nMI[channel_index]; // channel to read now!
        int next_channel_start = fData->bbseven_v1290_module_nME[channel_index]; // we read this channel until we hit this index
        
        for (uint32_t j = hit_index; j < next_channel_start; j++)
        {            
            uint32_t channel = current_channel - 1;
            uint32_t data = fData->bbseven_v1290_module_data[j];
            uint32_t lot = fData->bbseven_v1290_module_leadOrTrailv[j];
            
            auto & entry = v1290array->emplace_back();
            entry.SetAll(channel, data, lot);
        }
        hit_index = next_channel_start;
    }

    fNEvent += 1;
    return kTRUE;

}

void BB7Reader::Reset()
{
    v7x5array->clear();
    v1290array->clear();
}

ClassImp(BB7Reader)