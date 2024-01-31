#include "FrsVFTXData.h"


FrsVFTXData::FrsVFTXData()
{
    for (int i = 0; i < 32; i++)
    {
        fvftx_lead_times[i] = std::vector<uint32_t>();
    }
}




ClassImp(FrsVFTXData)