#include "FrsUserData.h"


FrsUserV830Item::FrsUserV830Item()
{

}

void FrsUserV830Item::SetAll(uint32_t in, uint32_t sc)
{
    index = in;
    scaler = sc;
}

void FrsUserV830Item::Reset()
{
    index = 0;
    scaler = 0;
}

ClassImp(FrsUserV830Item)


FrsUserV7X5Item::FrsUserV7X5Item()
{

}

void FrsUserV7X5Item::SetAll(uint32_t g, uint32_t ch, uint32_t data)
{
    geo = g;
    channel = ch;
    v7x5_data = data;
}

void FrsUserV7X5Item::Reset()
{
    geo = 0;
    channel = 0;
    v7x5_data = 0;
}

ClassImp(FrsUserV7X5Item)