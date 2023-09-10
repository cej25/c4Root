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
    , fOnline(kFALSE)
    , fArray(new TClonesArray("FrsReader"))
{
}

FrsReader::~FrsReader() { delete fArray; }

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
    FairRootManager::Instance()->Register("FrsData", "FRS Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FrsReader::Read()
{
    c4LOG(debug1, "Event data");
    
    new ((*fArray)[fArray->GetEntriesFast()]) FrsData(fData->Z,
                                                        fData->AoQ,
                                                        fData->Atwo,
                                                        fData->Afour,
                                                        fData->Xtwo,
                                                        fData->Xfour,
                                                        fData->beta);//,
                                                        //fData->frs_tpc_crate_data_frs_info_id_brho0[0],
                                                        //fData->frs_tpc_crate_data_frs_info_id_brho[0][0]); // stupid ass UCESB - FIX IT CALUM
    
    fNEvent += 1;
    return kTRUE;

}

void FrsReader::Reset()
{
    // reset output array
    fArray->Clear();
}

ClassImp(FrsReader);