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

FrsMainV792Item::FrsMainV792Item()
{

}

void FrsMainV792Item::SetAll(uint32_t ch, uint32_t data, uint32_t g)
{
    channel = ch;
    v792_data = data;
    geo = g;
}

void FrsMainV792Item::Reset()
{
    channel = 0;
    v792_data = 0;
    geo = 0;
}

FrsMainV1290Item::FrsMainV1290Item()
{

}

void FrsMainV1290Item::SetAll(uint32_t ch, uint32_t data, uint32_t lot)
{
    channel = ch;
    v1290_data = data;
    leadOrTrail = lot;
}

void FrsMainV1290Item::Reset()
{
    channel = 0;
    v1290_data = 0;
    leadOrTrail = 0;
}

FrsMainV830Item::FrsMainV830Item()
{

}

void FrsMainV830Item::SetAll(uint32_t in, uint32_t sc)
{
    index = in;
    scaler = sc;
}

void FrsMainV830Item::Reset()
{
    index = 0;
    scaler = 0;
}

ClassImp(FrsMainData)