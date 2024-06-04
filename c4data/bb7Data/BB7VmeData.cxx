#include "BB7VmeData.h"

BB7VmeData::BB7VmeData()
{

}

ClassImp(BB7VmeData)


BB7V7x5Item::BB7V7x5Item()
{

}

void BB7V7x5Item::SetAll(uint64_t wr, uint32_t g, uint32_t data, uint32_t ch)
{   
    wr_t = wr;
    geo = g;
    v7x5_data = data;
    channel = ch;
}

void BB7V7x5Item::Reset()
{   
    wr_t = 0;
    geo = 0;
    v7x5_data = 0;
    channel = 0;
}

ClassImp(BB7V7x5Item)
