// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "bPlastTamexData.h"
#include "bPlastReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_bplast.h"
}

bPlastReader::bPlastReader(EXT_STR_h101_BPLAST_onion* data, size_t offset)
    : c4Reader("bPlastReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("bPlastTamexData"))
{
}

bPlastReader::~bPlastReader() { delete fArray; }

Bool_t bPlastReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_BPLAST_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_BPLAST, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }
    
    // Register output array in a tree
    FairRootManager::Instance()->Register("bPlastTamexData", "bPlast Tamex Data", fArray, !fOnline);
    fArray->Clear();
    
    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t bPlastReader::Read()
{
    c4LOG(debug1, "Event Data");

    // BPLAST_TAMEX_MODULES
    for (int det = 0; det < 4; det++)
    {   
        // BPLAST_CHAN_PER_DET
        for (int chan = 0; chan < 16; chan++)
        {       
            // BPLAST_TAMEX_HITS
            for (int hit = 0; hit < 100; hit++)
            {  
                new ((*fArray)[fArray->GetEntriesFast()]) bPlastTamexData(det,
                                                                      chan,
                                                                      fData->plastic_crate[0].card[det].channel[chan].lead_T[hit],
                                                                      fData->plastic_crate[0].card[det].channel[chan].trail_T[hit],
                                                                      fData->plastic_crate[0].card[det].channel[chan].ToT[hit]);
            }

        }
    }

  
    fNEvent += 1;
    return kTRUE;
}

void bPlastReader::Reset()
{
    // reset output array
    fArray->Clear();
}

ClassImp(bPlastReader);