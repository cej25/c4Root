VME_CAEN_V1290_FRS()
{   

    MEMBERS

    UINT32 v1290_header NOENCODE
    {   
        0_4: geo;
        5_26: event_count;
        27_31: 0b01000;
    };

    select several
    {
        tdc_header = TDC_HEADER();
        measurement = TDC_DATA_V1290(PARAMS);
        tdc_error = TDC_ERROR();
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