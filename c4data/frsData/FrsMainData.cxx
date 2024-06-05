#include "FrsMainData.h"

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

ClassImp(FrsMainV792Item)

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

ClassImp(FrsMainV1290Item)

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

ClassImp(FrsMainV830Item)