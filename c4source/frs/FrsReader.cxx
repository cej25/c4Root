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
    , mainArray(new std::vector<FrsUnpackMainItem>)
    , tpatArray(new std::vector<FrsUnpackTpatItem>)
    , frsArray(new std::vector<FrsUnpackFrsItem>)
    //, v830Array(new std::vector<FrsUnpackV830>)
    //, v7X5Array(new std::vector<FrsUnpackV7X5>)
{
}

FrsReader::~FrsReader() 
{ 
    delete tpatArray;
    delete frsArray;
    //delete v830Array; 
    //delete v7X5Array;
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
    FairRootManager::Instance()->RegisterAny("MainData", mainArray, !fOnline);
    FairRootManager::Instance()->RegisterAny("TpatData", tpatArray, !fOnline);
    FairRootManager::Instance()->RegisterAny("FrsData", frsArray, !fOnline);
    mainArray->clear();
    tpatArray->clear();
    frsArray->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FrsReader::Read()
{
    c4LOG(debug1, "Event data");

    // -- MAIN CRATE -- //
    mainArray->clear();
    auto & mainEntry = mainArray->emplace_back();
    std::vector<V1290_item> v1290;
    std::vector<V830_item> v830_FIX;
    std::vector<V792_item> v792;
    UInt_t count = 0;
    for (UInt_t i = 0; i < fData->frs_main_crate_data_v1290_n; i++)
    {
        auto & item = v1290.emplace_back();
        item.channel = fData->frs_main_crate_data_v1290_channelv[i];
        item.leadOrTrail = fData->frs_main_crate_data_v1290_leadOrTrailv[i];
        item.data = fData->frs_main_crate_data_v1290_data[]; // 32 * item.channel + i?
        count += fData->frs_main_crate_data_v1290_n;
    }

    mainEntry.SetAll(v1290, v830_FIX, v792);


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
    //v830Array->clear();
    frsArray->clear();

    auto & frsEntry = frsArray->emplace_back();
    std::vector<V830_item> v830; // redeclare fix
    std::vector<V7X5_item> v7x5;
    for (UInt_t i = 0; i < fData->frs_crate_frs_v830_n; i++)
    {   
        auto & item = v830.emplace_back();
        item.data = fData->frs_crate_frs_v830_data[i];
        item.index = i;
    }

    for (UInt_t i = 0; i < fData->frs_crate_frs_v7x5_n; i++)
    {   
        auto & item = v7x5.emplace_back();
        item.geo = fData->frs_crate_frs_v7x5_geov[i];
        item.channel = fData->frs_crate_frs_v7x5_channelv[i];
        item.data = fData->frs_crate_frs_v7x5_data[i]; // vme_frs[geo][channel] later..
    }

    frsEntry.SetAll(v830, v7x5);

    fNEvent += 1;
    return kTRUE;

}

void FrsReader::Reset()
{
    // reset output array
    tpatArray->clear();
    frsArray->clear();
}

ClassImp(FrsReader);