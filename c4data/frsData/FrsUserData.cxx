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

FrsUserV830Item::FrsUserV830Item()
{

}

void FrsUserV830Item::SetAll(uint32_t in, uint32_t sc)
{
    index = in;
    scaler = sc;
}

void FrsUserV830Item::Reset()
{
    index = 0;
    scaler = 0;
}

FrsUserV7X5Item::FrsUserV7X5Item()
{

}

void FrsUserV7X5Item::SetAll(uint32_t g, uint32_t ch, uint32_t data)
{
    geo = g;
    channel = ch;
    v7x5_data = data;
}

void FrsUserV7X5Item::Reset()
{
    geo = 0;
    channel = 0;
    v7x5_data = 0;
}

ClassImp(FrsUserData)