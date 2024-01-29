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

    // v830 scalers
    scalers_n = fData->frsuser_data_v830_n;
    for (uint32_t i = 0; i < scalers_n; i++)
    {   
        scalers_index.emplace_back(fData->frsuser_data_v830_nI[i]);
        scalers_user.emplace_back(fData->frsuser_data_v830_data[fData->frsuser_data_v830_nI[i]]);
    }

    // CEJ: this will change because we don't need to "unpack" the channel
    // also it reads a bit horribly
    // v775 x2
    for (int i = 0; i < fData->frsuser_data_v7751n; i++)
    {
        v7x5_geo[0].emplace_back(fData->frsuser_data_v7751geov[i]);
        v7x5_channel[0].emplace_back(fData->frsuser_data_v7751channelv[i]);
        v7x5_data[0].emplace_back(fData->frsuser_data_v7751data[i]);
    }
    for (int i = 0; i < fData->frsuser_data_v7752n; i++)
    {
        v7x5_geo[1].emplace_back(fData->frsuser_data_v7752geov[i]);
        v7x5_channel[1].emplace_back(fData->frsuser_data_v7752channelv[i]);
        v7x5_data[1].emplace_back(fData->frsuser_data_v7752data[i]);
    }

    // v785
    for (int i = 0; i < fData->frsuser_data_v7852n; i++)
    {
        v7x5_geo[2].emplace_back(fData->frsuser_data_v7852geov[i]);
        v7x5_channel[2].emplace_back(fData->frsuser_data_v7852channelv[i]);
        v7x5_data[2].emplace_back(fData->frsuser_data_v7852data[i]);
    }
    for (int i = 0; i < fData->frsuser_data_v7852n; i++)
    {
        v7x5_geo[3].emplace_back(fData->frsuser_data_v7852geov[i]);
        v7x5_channel[3].emplace_back(fData->frsuser_data_v7852channelv[i]);
        v7x5_data[3].emplace_back(fData->frsuser_data_v7852data[i]);
    }


    new ((*fArray)[fArray->GetEntriesFast()]) FrsUserData(
        scalers_n,
        scalers_index,
        scalers_user,
        v7x5_geo,
        v7x5_channel,
        v7x5_data);


    fNEvent++;
    return kTRUE;
}

void FrsUserReader::Reset()
{
    scalers_index.clear();
    scalers_user.clear();
    fArray->Clear();
}

ClassImp(FrsUserReader)