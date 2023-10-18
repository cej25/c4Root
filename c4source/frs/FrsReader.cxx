// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FrsData.h"
#include "FrsReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h" 
    #include "ext_h101_frs.h"
}

FrsReader::FrsReader(EXT_STR_h101_FRS_onion* data, size_t offset)
    : c4Reader("FrsReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(false) // kFALSE
    , tpatArray(new std::vector<FrsUnpackTpatItem>)
    , v830Array(new std::vector<FrsUnpackV830>)
    , v7X5Array(new std::vector<FrsUnpackV7X5>)
{
}

FrsReader::~FrsReader() 
{ 
    delete tpatArray;
    delete v830Array; 
    delete v7X5Array;
}

Bool_t FrsReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");
    
    EXT_STR_h101_FRS_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_FRS, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->RegisterAny("TpatData", tpatArray, !fOnline);
    FairRootManager::Instance()->RegisterAny("FrsData", v830Array, !fOnline);
    FairRootManager::Instance()->RegisterAny("FrsData", v7X5Array, !fOnline);
    tpatArray->clear();
    v830Array->clear();
    v7X5Array->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FrsReader::Read()
{
    c4LOG(debug1, "Event data");

    // -- TPAT -- // 
    // no anaysis can be done without another procid...
    tpatArray->clear();

    for (UInt_t i = 0; i < fData->tpat_data_n; i++)
    {
        auto & entry = tpatArray->emplace_back();
        uint64_t ts_long = fData->tpat_data_ts_lov[i] | ((uint64_t)fData->tpat_data_ts_hiv[i] << 32);
        UInt_t trigger = fData->tpat_data_trigv[i];
        UInt_t data = fData->tpat_data_tpatv[i];
        entry.SetAll(ts_long, trigger, data);
    }

    // -- FRS crate -- //
    v830Array->clear();

    for (UInt_t i = 0; i < fData->frs_crate_frs_v830_n; i++)
    {     
        auto & entry = v830Array->emplace_back();
        UInt_t data = fData->frs_crate_frs_v830_data[i]; // scaler_frs[i] later...
        entry.SetAll(i, data);
    }

    v7X5Array->clear();

    for (UInt_t i = 0; i < fData->frs_crate_frs_v7x5_n; i++)
    {   
        auto & entry = v7X5Array->emplace_back();
        UInt_t geo = fData->frs_crate_frs_v7x5_geov[i];
        UInt_t channel = fData->frs_crate_frs_v7x5_channelv[i];
        UInt_t data = fData->frs_crate_frs_v7x5_data[i]; // vme_frs[geo][channel] later..
        entry.SetAll(geo, channel, data);
    }

    fNEvent += 1;
    return kTRUE;

}

void FrsReader::Reset()
{
    // reset output array
    tpatArray->clear();
    v830Array->clear();
    v7X5Array->clear();
}

ClassImp(FrsReader);