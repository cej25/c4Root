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
    // CEJ: this is not working!! does not register fZ etc when !fOnline == true!
    FairRootManager::Instance()->RegisterAny("TpatData", tpatArray, !fOnline);
    tpatArray->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FrsReader::Read()
{
    c4LOG(debug1, "Event data");

    tpatArray->clear();

    // is n the same value as number of trigs etc? hopefully
    for (UInt_t i = 0; i < fData->tpat_data_n; i++)
    {
        auto & entry = tpatArray->emplace_back();
        uint64_t ts_long = fData->tpat_data_ts_lov[i] | ((uint64_t)fData->tpat_data_ts_hiv[i] << 32);
        UInt_t trigger = fData->tpat_data_trigv[i];
        UInt_t data = fData->tpat_data_tpatv[i];
        entry.SetAll(ts_long, trigger, data);
    }

    fNEvent += 1;
    return kTRUE;

}

void FrsReader::Reset()
{
    // reset output array
    tpatArray->clear();
}

ClassImp(FrsReader);