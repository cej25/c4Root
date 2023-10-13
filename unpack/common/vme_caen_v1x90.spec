#define MEMBERS \
    MEMBER(DATA24 data[32] ZERO_SUPPRESS_MULTI(32)); \
    MEMBER(DATA8 channel[32] NO_INDEX_LIST); \
    MEMBER(DATA8 leadOrTrail[32] NO_INDEX_LIST);// not sure how to define this properly

#define PARAMS_DEF \
    data, \
	channel, \
    leadOrTrail

#define PARAMS \
    data = data, \
	channel = channel, \
    leadOrTrail = leadOrTrail

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
        0_20: value;
        21_25: chn;
        26: lot;
        27_31: 0b00000;
        
        ENCODE(data[chn],(value = value/*,trailing=trailing*/));
        ENCODE(channel APPEND_LIST, (value = chn));
        ENCODE(leadOrTrail APPEND_LIST, (value = lot));
    }
}

TDC_DATA_V1190() // PARAMS_DEF
{   
    //MEMBERS

    UINT32 tdc_data NOENCODE
    {
        0_18: value;
        19_25: chn;
        26: lot;
        27_31: 0b00000;
        
       //ENCODE(data[chn],(value = value/*,trailing=trailing*/));
       //ENCODE(channel APPEND_LIST, (value = chn));
       //ENCODE(leadOrTrail APPEND_LIST, (value = lot));
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

VME_CAEN_V1290_FRS()
{   

    MEMBERS

    UINT32 header NOENCODE
    {   
        0_4: geo;
        5_26: event_count;
        27_31: 0b01000;
    };

    select several
    {
        tdc_header = TDC_HEADER();
        measurement = TDC_DATA_V1290(PARAMS);
        tdc_err = TDC_ERROR(); // error causes namespace clash...
        tdc_trailer = TDC_TRAILER(); 
    };

    // if enabled
    optional UINT32 ext_time_tag NOENCODE
    {
        0_26: time_tag;
        27_31: 0b10001;
    };

    UINT32 trailer NOENCODE
    {
        0_4: geo;
        5_20: word_count;
        21_23: unused;
        24: tdc_error;
        25: overflow;
        26: trigger_lost;
        27_31: 0b10000;
    };

}

VME_CAEN_V1190_FRS()
{
    //MEMBERS

    UINT32 header NOENCODE
    {
        0_4: geo;
        5_26: event_count;
        27_31: 0b01000;
    };

    select several
    {
        tdc_header = TDC_HEADER();
        measurement = TDC_DATA_V1190(); // PARAMS
        tdc_error = TDC_ERROR();
        tdc_trailer = TDC_TRAILER();
    }

    // if enabled
    optional UINT32 ext_time_tag NOENCODE
    {
        0_26: time_tag;
        27_31: 0b10001;
    };

    UINT32 trailer NOENCODE
    {
        0_4: geo;
        5_20: word_count;
        21_23: unused;
        24: tdc_error;
        25: overflow;
        26: trigger_lost;
        27_31: 0b10000;
    };
}