#include "FrsData.h"

FrsData::FrsData()
    : tpat_ts(0)
    , tpat_trig(0)
    , tpat_data(0)
{
}

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

/*FrsUnpackFrsItem::FrsUnpackFrsItem()
{
}

void FrsUnpackFrsItem::SetAll(UInt_t g, UInt_t c, UInt_t v)
{
    // stuff
    geo = g;
    channel = c;
    data = v;
}*/

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
ClassImp(FrsUnpackV830)
ClassImp(FrsUnpackV7X5)
