#include "FrsTravMusData.h"

FrsTravMusAdcItem::FrsTravMusAdcItem()
{

}

void FrsTravMusAdcItem::SetAll(uint64_t wr, uint8_t ch, uint16_t adc)
{   
    wr_t = wr;
    channel = ch;
    adc_data = adc;
}

void FrsTravMusAdcItem::Reset()
{
    wr_t = 0;
    channel = 0;
    adc_data = 0; 
}

FrsTravMusTdcItem::FrsTravMusTdcItem()
{

}

void FrsTravMusTdcItem::SetAll(uint8_t ch, uint16_t tdc)
{
    channel = ch;
    tdc_data = tdc;
}

void FrsTravMusTdcItem::Reset()
{
    channel = 0;
    tdc_data = 0;
}