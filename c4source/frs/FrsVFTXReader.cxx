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

    Int_t chn_first_hit = 0;
    Int_t next_chn_first_hit = 0;
    bool trailing;

    for (Int_t i = 0; i < fData->frsvftx_data_vftx_time_coarseM; i++)
    {
        next_chn_first_hit = fData->frsvftx_data_vftx_time_coarseME[i];
        hits = next_chn_first_hit - chn_first_hit;

        for (Int_t j = 0; j < hits; j++)
        {   
            // check if leading somehow
            channel = fData->frsvftx_data_vftx_time_coarseMI[i];
            trailing = channel % 2;
            if ((!trailing) && (vftx_leading_time[channel].size() < VFTX_MAX_HITS))
            {
                cc = fData->frsvftx_data_vftx_time_coarsev[i * 100 + j];
                ft = fData->frsvftx_data_vftx_time_finev[i * 100 + j];
                r = (double)rand.Rndm() - 0.5;
                ti = VFTX_GetTraw_Ps(channel, cc, ft, r);
                vftx_leading_time[channel].emplace_back(ti);
            }
        }
    }


    // CEJ: MTDC and MQDC read but not used by DESPEC
    // ...do nothing for now...


    fNEvent++;
    return kTRUE;
}


// CEJ: module is not needed! There is only 1!
// it is only assigned = 0 in unpacking anyway!
Double_t FrsVFTXReader::VFTX_GetTraw_ps(int module, int channel, int cc, int ft, float rand) 
{
    Double_t gain;
    Double_t calib = (Double_t)VFTX_Bin2Ps[module][channel][ft];

    if (calib == 0) calib = ft;

    if(rand < 0) 
    {
        Double_t calib_prev = (Double_t)VFTX_Bin2Ps[module][channel][ft-1];
        gain = calib - calib_prev;
    }
    else 
    {
        Double_t calib_next = (Double_t)VFTX_Bin2Ps[module][channel][ft+1];
        gain = calib_next - calib;
    }

    double ft_ps = calib + gain * (double)rand;

    return (5000. * cc - ft_ps);
}



void FrsVFTXReader::Reset()
{
    fArray->Clear();
}

ClassImp(FrsVFTXReader)