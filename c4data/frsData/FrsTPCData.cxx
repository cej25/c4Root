#include "FrsTPCData.h"

FrsTPCData::FrsTPCData()
    :   fV1190_Channel(0)
    ,   fV1190_Data(0)
    ,   fV1190_LoT(0)
{
    for (int i = 0; i < 2; i++)
    {
        fv7x5_geo[i] = std::vector<uint32_t> ();
        fv7x5_channel[i] = std::vector<uint32_t> ();
        fv7x5_data[i] = std::vector<uint32_t> ();
    }
}

FrsTPCData::FrsTPCData(std::vector<uint32_t>* v7x5_geo,
                    std::vector<uint32_t>* v7x5_channel,
                    std::vector<uint32_t>* v7x5_data,
                    std::vector<uint32_t> V1190_Channel,
                    std::vector<uint32_t> V1190_Data,
                    std::vector<uint32_t> V1190_LoT)
    :   fV1190_Channel(V1190_Channel)
    ,   fV1190_Data(V1190_Data)
    ,   fV1190_LoT(V1190_LoT)
{
    for (int i = 0; i < 2; i++)
    {
        fv7x5_geo[i] = v7x5_geo[i];
        fv7x5_channel[i] = v7x5_channel[i];
        fv7x5_data[i] = v7x5_data[i];
    }
}


FrsTPCV7X5Item::FrsTPCV7X5Item()
{

}

void FrsTPCV7X5Item::SetAll(uint32_t g, uint32_t data, uint32_t ch)
{
    geo = g;
    v7x5_data = data;
    channel = ch;
}

void FrsTPCV7X5Item::Reset()
{
    geo = 0;
    v7x5_data = 0;
    channel = 0;
}

FrsTPCV1190Item::FrsTPCV1190Item()
{

}

void FrsTPCV1190Item::SetAll(uint32_t ch, uint32_t data, uint32_t lot)
{
    channel = ch;
    v1190_data = data;
    leadOrTrail = lot;
}

void FrsTPCV1190Item::Reset()
{
    channel = 0;
    v1190_data = 0;
    leadOrTrail = 0;
}

ClassImp(FrsTPCData)