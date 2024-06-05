#include "FrsTPCData.h"


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


ClassImp(FrsTPCV7X5Item)

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

ClassImp(FrsTPCV1190Item)