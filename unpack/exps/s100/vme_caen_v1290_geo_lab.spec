// Experimental GEO-discriminated V1290. Keep the shared FRS V1290 unchanged.
// Requires common vme_caen_v1x90.spec to have been included by frs_s100.spec.
VME_CAEN_V1290_GEO(geom_expected)
{
    MEMBER(DATA8 geo);

    UINT32 header NOENCODE
    {   
        0_4: geom = MATCH(geom_expected);
        5_26: event_count;
        27_31: type = MATCH(0b01000);

        ENCODE(geo, (value=geom));
    };

    // Distinguish board GEO before UCESB selects between TDC alternatives.
    MATCH_END;

    select several
    {
        tdc_header = TDC_HEADER();
        measurement = TDC_DATA_V1290();
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
        0_4: geom;
        5_20: word_count;
        21_23: unused;
        24: tdc_error;
        25: overflow;
        26: trigger_lost;
        27_31: 0b10000;
    };

}

