#define VME_CAEN_V775 VME_CAEN_V7X5
#define VME_CAEN_V785 VME_CAEN_V7X5
#define VME_CAEN_V792 VME_CAEN_V7X5

VME_CAEN_V7X5(geom) // V775, V785 and V792 unpack the same
{
    MEMBER(DATA24 data[32] ZERO_SUPPRESS);

    UINT32 header NOENCODE
    {
        0_7: undefined;
        8_13:  count;
        16_23: crate;
        24_26: 0b010;
        27_31: geom = MATCH(geom);
    }

    list(0 <= index < header.count)
    {
        UINT32 ch_data NOENCODE
	      {
            0_11: value;
            12: overflow;
            13: underflow;
            14: valid;
            15: undefined;
            16_20: channel;
            21_23: undefined2;
            24_26: 0b000;
            27_31: geom;


            ENCODE(data[channel],(value = value));
        }
    };

    UINT32 eob NOENCODE
    {
        0_23: nothing; // eventcounter?
        24_26: 0b100;
        27_31: id = MATCH(geom);
    }

    list (0 <= i < 2)
    {
        optional UINT32 eob2 NOENCODE 
        {  
            0_23: nothing;
            24_26: id = MATCH(0b110);
            27_31: geom; // unnecessary for us to match
        };
    }
}