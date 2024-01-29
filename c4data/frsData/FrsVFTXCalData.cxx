#include "FrsVFTXCalData.h"

FrsVFTXCalData::FrsVFTXCalData()
{
    
}


FrsVFTXCalData::FrsVFTXCalData(std::vector<uint32_t>* TRaw_vftx)
{
    for (int i = 0; i < 8; i++)
    {
        fTRaw_vftx[i] = TRaw_vftx[i];
    }
}


ClassImp(FrsVFTXCalData)
