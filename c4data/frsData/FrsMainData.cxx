#include "FrsMainData.h"

FrsMainData::FrsMainData()
    :   fScalers_N(0)
    ,   fScalers_Index(0)
    ,   fV830_Scalers(0)
    ,   fV792_Geo(0)
    ,   fV792_Channel(0)
    ,   fV792_Data(0)
    ,   fV1290_Channel(0)
    ,   fV1290_Data(0)
    ,   fV1290_LoT(0)
{
}

FrsMainData::FrsMainData(uint32_t Scalers_N, 
                std::vector<uint32_t> Scalers_Index, 
                std::vector<uint32_t> V830_Scalers,
                uint32_t V792_Geo,
                std::vector<uint32_t> V792_Channel,
                std::vector<uint32_t> V792_Data,
                std::vector<uint32_t> V1290_Channel,
                std::vector<uint32_t> V1290_Data,
                std::vector<uint32_t> V1290_LoT)
    :   fScalers_N(Scalers_N)
    ,   fScalers_Index(Scalers_Index)
    ,   fV830_Scalers(V830_Scalers)
    ,   fV792_Geo(V792_Geo)
    ,   fV792_Channel(V792_Channel)
    ,   fV792_Data(V792_Data)
    ,   fV1290_Channel(V1290_Channel)
    ,   fV1290_Data(V1290_Data)
    ,   fV1290_LoT(V1290_LoT)
{
}

ClassImp(FrsMainData)