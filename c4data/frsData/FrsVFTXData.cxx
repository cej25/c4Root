#include "FrsVFTXData.h"

FrsVFTXData::FrsVFTXData()
{
}


FrsVFTXData::FrsVFTXData(std::vector<uint32_t>* vftx_lead_times)
{
    for (int i = 0; i < 16; i++)
    {
        fvftx_lead_times[i] = vftx_lead_times[i];
    }
}


ClassImp(FrsVFTXData)