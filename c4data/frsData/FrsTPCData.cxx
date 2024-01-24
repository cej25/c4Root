#include "FrsTPCData.h"

FrsTPCData::FrsTPCData()
    :   fV775_Geo(0)
    ,   fV775_Channel(0)
    ,   fV775_Data(0)
    ,   fV785_Geo(0)
    ,   fV785_Channel(0)
    ,   fV785_Data(0)
    ,   fV1190_Channel(0)
    ,   fV1190_Data(0)
    ,   fV1190_LoT(0)
{
}

FrsTPCData::FrsTPCData(std::vector<uint32_t> V775_Geo,
                    std::vector<uint32_t> V775_Channel,
                    std::vector<uint32_t> V775_Data,
                    std::vector<uint32_t> V785_Geo,
                    std::vector<uint32_t> V785_Channel,
                    std::vector<uint32_t> V785_Data,
                    std::vector<uint32_t> V1190_Channel,
                    std::vector<uint32_t> V1190_Data,
                    std::vector<uint32_t> V1190_LoT)
    :   fV775_Geo(V775_Geo)
    ,   fV775_Channel(V775_Channel)
    ,   fV775_Data(V775_Data)
    ,   fV785_Geo(V785_Geo)
    ,   fV785_Channel(V785_Channel)
    ,   fV785_Data(V785_Data)
    ,   fV1190_Channel(V1190_Channel)
    ,   fV1190_Data(V1190_Data)
    ,   fV1190_LoT(V1190_LoT)
{
}

ClassImp(FrsTPCData)