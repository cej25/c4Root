// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FrsVFTXData.h"
#include "FrsVFTXReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include <vector>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h" 
    #include "ext_h101_frsvftx.h"
}

FrsVFTXReader::FrsVFTXReader(EXT_STR_h101_frsvftx_onion* data, size_t offset)
    :   c4Reader("FrsVFTXReader")
    ,   fNEvent(0)
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   fArray(new TClonesArray("FrsVFTXData"))
{
}

FrsVFTXReader::~FrsVFTXReader()
{
    if (fArray != nullptr) delete fArray;
    c4LOG(info, "Destroyed FrsVFTXReader properly.");
}

Bool_t FrsVFTXReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;

    c4LOG(info, "");
    
    EXT_STR_h101_frsvftx_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_frsvftx, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    FairRootManager::Instance()->Register("FrsVFTXReader", "FRS VFTX Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    c4LOG(info, "FrsVFTXReader init complete.");

    return kTRUE;
}

Bool_t FrsVFTXReader::Read()
{
    c4LOG(debug1, "Event data");

    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;


    // do the reading

    fNEvent++;
    return kTRUE;
}

void FrsVFTXReader::Reset()
{
    fArray->Clear();
}

ClassImp(FrsVFTXReader)