#include "FrsVFTXData.h"


FrsVFTXData::FrsVFTXData()
{
    /*for (int i = 0; i < 32; i++)
    {
        fvftx_lead_times[i] = std::vector<uint32_t>();
    }*/
}


FrsVFTXData::FrsVFTXData(std::vector<uint32_t>* vftx_leading_cc,
                        std::vector<uint32_t>* vftx_leading_ft,
                        std::vector<uint32_t>* vftx_leading_time,
                        std::vector<uint32_t>* vftx_trailing_cc,
                        std::vector<uint32_t>* vftx_trailing_ft,
                        std::vector<uint32_t>* vftx_trailing_time)
{
    for (int i = 0; i < VFTX_MAX_CHN; i++)
    {
        fvftx_leading_cc[i] = vftx_leading_cc[i];
        fvftx_leading_ft[i] = vftx_leading_ft[i];
        fvftx_leading_time[i] = vftx_leading_time[i];
        fvftx_trailing_cc[i] = vftx_trailing_cc[i];
        fvftx_trailing_ft[i] = vftx_trailing_ft[i];
        fvftx_trailing_time[i] = vftx_trailing_time[i];
    }
}


ClassImp(FrsVFTXData)