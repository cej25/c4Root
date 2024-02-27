// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

#include "TH1.h"
#include "TFile.h"

#include <iomanip>

// c4
#include "FatimaVmeData.h"
#include "FatimaVmeReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_fatimavme.h"
}

FatimaVmeReader::FatimaVmeReader(EXT_STR_h101_fatimavme_onion* data, size_t offset)
    :   c4Reader("FatimaVmeReader")
    ,   fNEvent(0)
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   fArray(new TClonesArray("FatimaVmeData"))
{
}

FatimaVmeReader::~FatimaVmeReader()
{   
    c4LOG(info, "");
    if (fArray) delete fArray;
}

Bool_t FatimaVmeReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_fatimavme_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_fatimavme, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // bunch of stuff


    FairRootManager::Instance()->Register("FatimaVmeData", "FatimaVmeDataFolder", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    c4LOG(info, "FatimaVmeReader init setup completed.");

    return kTRUE;

}

Bool_t FatimaVmeReader::Read()
{
    c4LOG(debug1, "Event Data");

    if (!fData) return kTRUE;

     //whiterabbit timestamp:
    wr_t = (((uint64_t)fData->fatimavme_ts_t[3]) << 48) + (((uint64_t)fData->fatimavme_ts_t[2]) << 32) + (((uint64_t)fData->fatimavme_ts_t[1]) << 16) + (uint64_t)(fData->fatimavme_ts_t[0]);

    // CEJ fix later obviously
    if (wr_t != 0)
    {
       new ((*fArray)[fArray->GetEntriesFast()]) FatimaVmeData(
                    wr_t); 
    }
   

    fNEvent++;
    return kTRUE;


}

void FatimaVmeReader::Reset()
{
    fArray->Clear();
}


ClassImp(FatimaVmeReader)