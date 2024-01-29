#include "FrsData.h"

FrsUnpackMainItem::FrsUnpackMainItem()
{
}

void FrsUnpackMainItem::SetAll(std::vector<V1290_item>& v1290, std::vector<V830_item>& v830, std::vector<V792_item>& v792)
{
    v1290Array = v1290;
    v830Array = v830;
    v792Array = v792;
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

void FrsUnpackFrsItem::SetAll(std::vector<V830_item>& v830, std::vector<V7X5_item>& v7x5)
{   
    v830Array = v830;
    v7x5Array = v7x5;
}

ClassImp(FrsUnpackMainItem)
ClassImp(FrsUnpackTpatItem)
ClassImp(FrsUnpackFrsItem)

