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
    , frsArray(new std::vector<FrsUnpackFrsItem>)
{
}

FrsReader::~FrsReader() { delete tpatArray; }

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
    FairRootManager::Instance()->RegisterAny("FrsData", frsArray, !fOnline);
    tpatArray->clear();
    frsArray->clear();

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
    frsArray->clear();

    for (UInt_t i = 0; i < fData->frs_crate_frs_v830_n; i++)
    {   
        std::cout << "this should be 32.. for now ... " << fData->frs_crate_frs_v830_n << std::endl
        scaler_frs[i] = fData->fData->frs_crate_frs_v830_data[i]; // goes into sc_long[i] later...
    }

    for (UInt_t i = 0; i < fData->frs_crate_frs_v7x5_n; i++)
    {   
        geo = fData->frs_crate_frs_v7x5_geov[i];
        channel = fData->frs_crate_frs_v7x5_channelv[i];
        vme_frs[geo][channel] = fData->frs_crate_frs_v7x5_data[i];
    }

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