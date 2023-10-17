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

ClassImp(FrsData)
ClassImp(FrsUnpackTpatItem)