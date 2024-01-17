#include "FrsData.h"

FrsData::FrsData()
    :   fWR_TS(0)
    ,   fScalers_N(0)
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

FrsData::FrsData(uint64_t WR_TS, 
                uint32_t Scalers_N, 
                std::vector<uint32_t> Scalers_Index, 
                std::vector<uint32_t> V830_Scalers,
                uint32_t V792_Geo,
                std::vector<uint32_t> V792_Channel,
                std::vector<uint32_t> V792_Data,
                std::vector<uint32_t> V1290_Channel,
                std::vector<uint32_t> V1290_Data,
                std::vector<uint32_t> V1290_LoT)
    :   fWR_TS(WR_TS)
    ,   fScalers_N(Scalers_N)
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


ClassImp(FrsData)
/*
FrsData::FrsData(UInt_t time, UInt_t trig, UInt_t data)
    : tpat_ts(time) // tpat subev
    , tpat_trig(trig)
    , tpat_data(data)
{
}

FrsUnpackTpatItem::FrsUnpackTpatItem()
{
}

void FrsUnpackTpatItem::SetAll(uint64_t time, UInt_t trig, UInt_t value)
{
    ts_long = time;
    trigger = trig;
    data = value;
}

FrsUnpackFrsItem::FrsUnpackFrsItem()
{
}

void FrsUnpackFrsItem::SetV830(UInt_t i, UInt_t d)
{
    index = i;
    v830_data = d;
}

void FrsUnpackFrsItem::SetV7X5(UInt_t g, UInt_t c, UInt_t d)
{
    geo = g;
    channel = c;
    v7x5_data = d;
}

FrsUnpackV830::FrsUnpackV830()
{
}

void FrsUnpackV830::SetAll(UInt_t i, UInt_t d)
{
    index = i;
    v830_data = d;
}

FrsUnpackV7X5::FrsUnpackV7X5()
{
}

void FrsUnpackV7X5::SetAll(UInt_t g, UInt_t c, UInt_t d)
{
    geo = g;
    channel = c;
    v7x5_data = d;
}

ClassImp(FrsData)
ClassImp(FrsUnpackTpatItem)
ClassImp(FrsUnpackFrsItem)
ClassImp(FrsUnpackV830)
ClassImp(FrsUnpackV7X5)
*/