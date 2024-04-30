#include "FairLogger.h"
#include "FairRootManager.h"

#include "FimpReader.h"
#include "c4Logger.h"

#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_fimp.h"
}

FimpReader::FimpReader(EXT_STR_h101_fimp_onion* data, size_t offset)
    : c4Reader("FimpReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fimpArray(new std::vector<FimpItem>)
{
}

FimpReader::~FimpReader() 
{

}

Bool_t FimpReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_fimp_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_fimp, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    // register output array in a tree
    FairRootManager::Instance()->RegisterAny("FimpData", fimpArray, !fOnline);
    fimpArray->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FimpReader::Read()
{
    fimpArray->clear();

    //WR time stamp
    uint64_t wr_t = (((uint64_t)fData->fimp_ts_t[3]) << 48) + 
    (((uint64_t)fData->fimp_ts_t[2]) << 32) + 
    (((uint64_t)fData->fimp_ts_t[1]) << 16) + 
    (uint64_t)(fData->fimp_ts_t[0]);

    uint32_t wr_id = fData->fimp_ts_subsystem_id;


    return kTRUE;
}

// You must clear any arrays and vectors you use or things will get weird
void FimpReader::ZeroArrays()
{ 

}

void FimpReader::ClearVectors()
{

}

void FimpReader::Reset()
{
    ZeroArrays();
    ClearVectors();
}

ClassImp(FimpReader);
