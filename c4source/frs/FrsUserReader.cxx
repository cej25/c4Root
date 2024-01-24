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
    ,   fArray(new TClonesArray("FrsUserData"))
{
}

FrsUserReader::~FrsUserReader()
{
    if (fArray != nullptr) delete fArray;
    c4LOG(info, "Destroyed FrsUserReader properly.");
}

Bool_t FrsUserReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;

    c4LOG(info, "");
    
    EXT_STR_h101_frsuser_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_frsuser, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    FairRootManager::Instance()->Register("FrsUserData", "FRS User Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    c4LOG(info, "FrsUserReader init complete.");

    return kTRUE;
}

Bool_t FrsUserReader::Read()
{
    c4LOG(debug1, "Event data");

    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;


    // do the reading

    fNEvent++;
    return kTRUE;
}

void FrsUserReader::Reset()
{
    fArray->Clear();
}

ClassImp(FrsUserReader)