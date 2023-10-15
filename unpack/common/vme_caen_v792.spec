VME_CAEN_V792_FRS()
{
    UINT32 v792_header NOENCODE
    {   
        0_7: unused;
        8_13: cnt;
        14_15: 0b00;
        16_23: crate;
        24_26: 0b010;
        27_31: geo;
    };
    
    several UINT32 adc_data NOENCODE
    {   
        0_11: adc;
        12: overflow;
        13: underthreshold;
        14_15: unused;
        16_20: channel;
        21_23: unused2;
        24_26: 0b000;
        27_31: geo;
    };

    UINT32 eob NOENCODE
    {   
        0_23: eventcounter;
        24_26: 0b100;
        27_31: geo;
    };
}
