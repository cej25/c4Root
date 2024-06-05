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
    ,   fArray(new TClonesArray("BB7VmeData"))
    ,   v7x5array(new std::vector<BB7V7x5Item>)
{

}

BB7Reader::~BB7Reader()
{
    delete fArray;
    delete v7x5array;
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

    FairRootManager::Instance()->Register("BB7VmeData", "BB7 Vme Data", fArray, !fOnline);
    FairRootManager::Instance()->RegisterAny("BB7V7x5Data", v7x5array, !fOnline);
    fArray->Clear();
    v7x5array->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t BB7Reader::Read()
{
    c4LOG(debug1, "Event Data");

    if (!fData) return kTRUE;

    BB7VmeData* bb7VmeHit = new BB7VmeData();

    wr_t = (((uint64_t)fData->bb7_ts_t4) << 48) + (((uint64_t)fData->bb7_ts_t3) << 32) + (((uint64_t)fData->bb7_ts_t2) << 16) + (uint64_t)(fData->bb7_ts_t1);

    bb7VmeHit->Set_wr_t(wr_t);

  
    for (int i = 0; i < fData->bb7_v7x5_module1n; i++)
    {   
        uint32_t geo = fData->bb7_v7x5_module1geov[i];
        uint32_t data = fData->bb7_v7x5_module1data[i];
        uint32_t channel = fData->bb7_v7x5_module1channelv[i];

        auto & entry = v7x5array->emplace_back();
        entry.SetAll(wr_t, geo, data, channel);

        v7x5_geo.emplace_back(fData->bb7_v7x5_module1geov[i]);
        v7x5_channel.emplace_back(fData->bb7_v7x5_module1channelv[i]);
        v7x5_data.emplace_back(fData->bb7_v7x5_module1data[i]);
    }

    for (int i = 0; i < fData->bb7_v7x5_module2n; i++)
    {   
        uint32_t geo = fData->bb7_v7x5_module2geov[i];
        uint32_t data = fData->bb7_v7x5_module2data[i];
        uint32_t channel = fData->bb7_v7x5_module2channelv[i];

        auto & entry = v7x5array->emplace_back();
        entry.SetAll(wr_t, geo, data, channel);

        v7x5_geo.emplace_back(fData->bb7_v7x5_module2geov[i]);
        v7x5_channel.emplace_back(fData->bb7_v7x5_module2channelv[i]);
        v7x5_data.emplace_back(fData->bb7_v7x5_module2data[i]);
    }

    bb7VmeHit->Set_v7x5_geo(v7x5_geo);
    bb7VmeHit->Set_v7x5_channel(v7x5_channel);
    bb7VmeHit->Set_v7x5_data(v7x5_data);

    new ((*fArray)[fArray->GetEntriesFast()]) BB7VmeData(*bb7VmeHit);




    fNEvent += 1;
    return kTRUE;

}

void BB7Reader::Reset()
{
    v7x5_geo.clear();
    v7x5_channel.clear();
    v7x5_data.clear();
    fArray->Clear();
    v7x5array->clear();
}

ClassImp(BB7Reader)