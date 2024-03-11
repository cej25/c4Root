#define MEMBERS \
    MEMBER(DATA24 data[128] ZERO_SUPPRESS_MULTI(128)); \
    MEMBER(DATA8 leadOrTrail[128] ZERO_SUPPRESS_MULTI(128)); \
    MEMBER(DATA8 geo);


#define PARAMS_DEF \
    data, \
    leadOrTrail, \
    geo

#define PARAMS \
    data = data, \
    leadOrTrail = leadOrTrail, \
    geo = geo

TDC_HEADER()
{   
    UINT32 tdc_header NOENCODE
    {
        0_11: bunch_id;
        12_23: event_id;
        24_25: tdc;
        26: unused;
        27_31: 0b00001;
    }
}

TDC_DATA_V1290(PARAMS_DEF)
{   
    MEMBERS

    UINT32 tdc_data NOENCODE
    {
        0_20: tdc;
        21_25: chn;
        26: lot;
        27_31: 0b00000;
        
        ENCODE(data[chn],(value = tdc/*,trailing=trailing*/));
        ENCODE(leadOrTrail[chn], (value = lot));
    }
}

TDC_DATA_V1190(PARAMS_DEF)
{   
    MEMBERS

    UINT32 tdc_data NOENCODE
    {
        0_18: tdc;
        19_25: chn;
        26: lot;
        27_31: 0b00000;
        
        ENCODE(data[chn],(value = tdc/*,trailing=trailing*/));
        ENCODE(leadOrTrail[chn], (value = lot));

    }
}

TDC_ERROR()
{
    UINT32 tdc_err NOENCODE
    {
        0_14: error_flags;
        15_23: unused1;
        24_25: tdc;
        26: unused2;    
        27_31: 0b00100;
    }
}

TDC_TRAILER()
{   
    UINT32 tdc_trailer NOENCODE
    {
        0_11: word_count;
        12_23: event_id;
        24_25: tdc;
        26: unused;
        27_31: 0b00011;
    }
}

// CEJ: don't call this _FRS
VME_CAEN_V1290_FRS()
{   
    MEMBERS
    
    // definitely not optional
    UINT32 header NOENCODE
    {   
        0_4: geo;
        5_26: event_count;
        27_31: 0b01000;
        ENCODE(geo, (value = geo));
    };

    select several
    {
        tdc_header = TDC_HEADER();
        measurement = TDC_DATA_V1290(PARAMS);
        tdc_err = TDC_ERROR(); // error causes namespace clash...
        tdc_trailer = TDC_TRAILER(); 
    };

    // if enabled
    optional UINT32 ext_time_tag NOENCODE // type = 17
    {
        0_26: time_tag;
        27_31: 0b10001;
    };

    UINT32 trailer NOENCODE // type = 16
    {
        0_4: geo;
        5_20: word_count;
        21_23: unused;
        24: tdc_error;
        25: overflow;
        26: trigger_lost;
        27_31: 0b10000;
    };
    
    // this needs defining properly.......
    //optional UINT32 eob NOENCODE; // type = 24

}

// CEJ: probably need to not call this _FRS
VME_CAEN_V1190_FRS()
{
    MEMBERS

    // for now (12/2023) we need to catch weird events
    // first two words COULD be 0xFFFFFFFF
    // i don't know how to do this more simply

    UINT32 header NOENCODE
    {
        0_4: geo;
        5_26: event_count;
        27_31: seven_f; // 0b01000; // if global header
        ENCODE(geo, (value = geo));
    };

    if (header.seven_f != 0b01000)
    {
        // first two words are weird
        UINT32 second1 NOENCODE
        {
            0_31: 0xFFFFFFFF;
        };

        UINT32 real_header NOENCODE
        {
            0_4: geo;
            5_26: event_count;
            27_31: 0b01000;
        }
    }

    select several
    {
        tdc_header = TDC_HEADER();
        measurement = TDC_DATA_V1190(PARAMS);
        tdc_error = TDC_ERROR();
        tdc_trailer = TDC_TRAILER();
    };

    // if enabled
    optional UINT32 ext_time_tag NOENCODE // type = 17
    {
        0_26: time_tag;
        27_31: 0b10001;
    };

    UINT32 trailer NOENCODE // type = 16
    {
        0_4: geo;
        5_20: word_count;
        21_23: unused;
        24: tdc_error;
        25: overflow;
        26: trigger_lost;
        27_31: 0b10000;
    };

    optional UINT32 eob NOENCODE; // type = 24

}