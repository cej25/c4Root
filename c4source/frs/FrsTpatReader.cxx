// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FrsTpatData.h"
#include "FrsTpatReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "TFolder.h"
#include <vector>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h" 
    #include "ext_h101_frstpat.h"
}

FrsTpatReader::FrsTpatReader(EXT_STR_h101_frstpat_onion* data, size_t offset)
    : c4Reader("FrsTpatReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("FrsTpatData"))
{
}

FrsTpatReader::~FrsTpatReader() 
{ 
    if (fArray != nullptr) delete fArray;
    c4LOG(info, "Destroyed FrsTpatReader properly.");
}

Bool_t FrsTpatReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    
    EXT_STR_h101_frstpat_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_frstpat, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    FairRootManager::Instance()->Register("FrsTpatData", "FRS Tpat Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FrsTpatReader::Read()
{
    c4LOG(debug2, "Event data");

    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;

    FrsTpatData* TpatHit = new FrsTpatData();
    wr_t = (((uint64_t)fData->frstpat_wr_t[3]) << 48) + (((uint64_t)fData->frstpat_wr_t[2]) << 32) + (((uint64_t)fData->frstpat_wr_t[1]) << 16) + (uint64_t)(fData->frstpat_wr_t[0]);
    if (wr_t != 0) 
    {
        tpatEvent++;
        written = false;
    }
        
    TpatHit->Set_wr_t(wr_t);

    tpat = fData->frstpat_data_tpat; // single 12bit 
    TpatHit->Set_tpat(tpat);

    new ((*fArray)[fArray->GetEntriesFast()]) FrsTpatData(*TpatHit);
    
    if (tpatEvent % 5000 == 0 && tpatEvent > 0 && written == false)
    {
        c4LOG(info, "FRS WhiteRabbits: " << tpatEvent);
        written = true;
    }
        
    fNEvent += 1;
    
    return kTRUE;

}



void FrsTpatReader::Reset()
{
    fArray->Clear();
}

ClassImp(FrsTpatReader);
