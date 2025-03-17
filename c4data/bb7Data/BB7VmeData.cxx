#include "BB7VmeData.h"


BB7V7x5Item::BB7V7x5Item()
{

}

void BB7V7x5Item::SetAll(Long64_t wr, UInt_t g, UInt_t data, UInt_t ch)
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

BB7V1290Item::BB7V1290Item()
{

}

void BB7V1290Item::SetAll(UInt_t ch, UInt_t data, UInt_t lot)
{
    channel = ch;
    v1290_data = data;
    leadOrTrail = lot;
}

void BB7V1290Item::Reset()
{
    channel = 0;
    v1290_data = 0;
    leadOrTrail = 0;
}

ClassImp(BB7V1290Item)
