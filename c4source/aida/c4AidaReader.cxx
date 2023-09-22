#include "c4AidaReader.h"

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "AidaData.h"
#include "c4Logger.h"

// ucesb
#include "ext_data_struct_info.hh"
#include "ext_h101_aida.h"

extern "C"
{
#include "ext_data_client.h"
}

AidaReader::AidaReader(EXT_STR_h101_aida_onion* data, size_t offset)
    : c4Reader("AidaReader"),
      fNEvent(0),
      fData(data),
      fOffset(offset),
      fOnline(false)
{
}

AidaReader::~AidaReader()
{
}

Bool_t AidaReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    EXT_STR_h101_AIDA_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_aida, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // Register vector(?) of data here
    //
    return kTRUE;
}

Bool_t AidaReader::Read()
{
    // fData is valid here, shove it into the vector
    //
    return kTRUE;
}

void AidaReader::Reset()
{
    // Clear the vector
}

ClassImp(AidaReader);

