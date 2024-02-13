VME_CAEN_V792_FRS()
{
    MEMBER(DATA32 data[32] ZERO_SUPPRESS_MULTI(32));
    //MEMBER(DATA8 channel[32] NO_INDEX_LIST);
    MEMBER(DATA8 geo);

    UINT32 v792_header NOENCODE
    {   
        0_7: unused;
        8_13: cnt;
        14_15: 0b00;
        16_23: crate;
        24_26: 0b010;
        27_31: geo;
        ENCODE(geo, (value = geo));
    };

    // this can be a list presumably?
    // damn we need to document this hard
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
        
        ENCODE(data[channel], (value = adc));
    };

    // hastily changed this for v792, might be incorrect
    UINT32 eob NOENCODE
    {
        0_23: nothing; //eventcounter;
        24_26: 0b100;
        27_31: geom;
    }

    list (0 <= i < 2)
    {
        optional UINT32 eob2 NOENCODE 
        {  
            0_23: nothing; //eventcounter;
            24_26: id = MATCH(0b110);
            27_31: geom;
        };
    }
}
