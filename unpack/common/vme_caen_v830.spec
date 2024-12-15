VME_CAEN_V830(geom)
{
    MEMBER(DATA32 data[32] ZERO_SUPPRESS);

    UINT32 header
    {
        0_15:  event_number;
        16_17: ts;
        18_23: count;
        24_25: undefined;
        26:    1;
        27_31: geom = MATCH(geom);
    };

    list (0 <= index < header.count)
    {
        UINT32 ch_data NOENCODE
	      {
	          0_25:  value;
	          26:    0;
	          27_31: channel;

	          ENCODE(data[channel],(value=value));
	      }
    }
}