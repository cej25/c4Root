#ifndef FrsTravMusData_H
#define FrsTravMusData_H

#include "TObject.h"

class FrsTravMusAdcItem : public TObject
{
    public:
        FrsTravMusAdcItem();

        void SetAll(uint64_t wr, uint8_t ch, uint16_t adc);
        void Reset();

        uint64_t Get_wr_t() const;
        uint16_t Get_adc_data() const;
        uint8_t Get_channel() const;

        ClassDefNV(FrsTravMusAdcItem, 2);
    
    public:
        uint64_t wr_t;
        uint16_t adc_data;
        uint8_t channel;
};

class FrsTravMusTdcItem : public TObject
{
    public:
        FrsTravMusTdcItem();

        void SetAll(uint8_t ch, uint16_t tdc);
        void Reset();

        uint16_t Get_tdc_data() const;
        uint8_t Get_channel() const;

        ClassDefNV(FrsTravMusTdcItem, 2);
    
    public:
        uint16_t tdc_data;
        uint8_t channel;
};

inline uint64_t FrsTravMusAdcItem::Get_wr_t() const
{
    return wr_t;
}

inline uint16_t FrsTravMusAdcItem::Get_adc_data() const
{
    return adc_data;
}

inline uint8_t FrsTravMusAdcItem::Get_channel() const
{
    return channel;
}

inline uint16_t FrsTravMusTdcItem::Get_tdc_data() const
{
    return tdc_data;
}

inline uint8_t FrsTravMusTdcItem::Get_channel() const
{
    return channel;
}


#endif