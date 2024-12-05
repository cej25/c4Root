#include "TravMusData.h"

TravMusAdcItem::TravMusAdcItem()
{

}

void TravMusAdcItem::SetAll(uint64_t wr, uint8_t ch, uint16_t adc)
{   
    wr_t = wr;
    channel = ch;
    adc_data = adc;
}

void TravMusAdcItem::Reset()
{
    wr_t = 0;
    channel = 0;
    adc_data = 0; 
}

TravMusTdcItem::TravMusTdcItem()
{

}

void TravMusTdcItem::SetAll(uint8_t ch, uint16_t tdc)
{
    channel = ch;
    tdc_data = tdc;
}

void TravMusTdcItem::Reset()
{
    channel = 0;
    tdc_data = 0;
}