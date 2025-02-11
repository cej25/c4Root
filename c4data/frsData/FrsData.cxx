#include "FrsData.h"
#include <iostream> // testing purposes

FrsTpatItem::FrsTpatItem() {}

void FrsTpatItem::SetAll(Long64_t wr, Short_t tp)
{
    wr_t = wr;
    tpat = tp;
}

void FrsTpatItem::Reset()
{
    wr_t = 0;
    tpat = 0;
}

ClassImp(FrsTpatItem)


FrsScalerItem::FrsScalerItem() {}

void FrsScalerItem::SetAll(Int_t i, UInt_t sc)
{   
    index = i;
    scaler = sc;
}

void FrsScalerItem::Reset()
{
    index = -1;
    scaler = 0;
}

ClassImp(FrsScalerItem)


FrsSciItem::FrsSciItem() {}

void FrsSciItem::SetAll(UInt_t de[18], UInt_t dt[19], std::vector<Int_t> mhtdc[24])
{
    for (int i = 0; i < 18; i++) sciDE[i] = de[i];
    for (int i = 0; i < 19; i++) sciDT[i] = dt[i];
    for (int i = 0; i < 24; i++) sciMHTDC[i] = mhtdc[i];

}

ClassImp(FrsSciItem)

FrsMusicItem::FrsMusicItem() {}

void FrsMusicItem::SetAll(uint32_t e[2][8], uint32_t t[2][8])
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 8; j++) musicE[i][j] = e[i][j];
        for (int j = 0; j < 8; j++) musicT[i][j] = t[i][j];
    }
}

ClassImp(FrsMusicItem)


FrsTpcItem::FrsTpcItem() {}

void FrsTpcItem::SetAll(UInt_t adc[7][8], std::vector<UInt_t> tdc[128])
{
    for (int i = 0; i < 7; i++) for (int j = 0; j < 8; j++) adcData[i][j] = adc[i][j];
    for (int i = 0; i < 128; i++) tdcData[i] = tdc[i];
}

ClassImp(FrsTpcItem)