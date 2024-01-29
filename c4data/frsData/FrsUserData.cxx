#include "FrsUserData.h"

FrsUserData::FrsUserData()
    :   fScalers_N(0)
    ,   fScalers_Index(0)
    ,   fV830_Scalers(0)
{
}

FrsUserData::FrsUserData(uint32_t Scalers_N, 
                        std::vector<uint32_t> Scalers_Index, 
                        std::vector<uint32_t> V830_Scalers,
                        std::vector<uint32_t>* v7x5_geo,
                        std::vector<uint32_t>* v7x5_channel,
                        std::vector<uint32_t>* v7x5_data)
    :   fScalers_N(Scalers_N)
    ,   fScalers_Index(Scalers_Index)
    ,   fV830_Scalers(V830_Scalers)
{
    for (int i = 0; i < 4; i++)
    {
        fv7x5_geo[i] = v7x5_geo[i];
        fv7x5_channel[i] = v7x5_channel[i];
        fv7x5_data[i] = v7x5_data[i];
    }
}

ClassImp(FrsUserData)