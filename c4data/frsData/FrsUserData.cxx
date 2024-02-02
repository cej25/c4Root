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
                        std::vector<uint32_t>* v7x5_geo_user,
                        std::vector<uint32_t>* v7x5_channel_user,
                        std::vector<uint32_t>* v7x5_data_user)
    :   fScalers_N(Scalers_N)
    ,   fScalers_Index(Scalers_Index)
    ,   fV830_Scalers(V830_Scalers)
{
    for (int i = 0; i < 4; i++)
    {
        fv7x5_geo_user[i] = v7x5_geo_user[i];
        fv7x5_channel_user[i] = v7x5_channel_user[i];
        fv7x5_data_user[i] = v7x5_data_user[i];
    }
}

ClassImp(FrsUserData)