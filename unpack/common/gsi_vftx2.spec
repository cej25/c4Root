VFTX2(id)
{
	MEMBER(DATA12 time_fine[32] ZERO_SUPPRESS_MULTI(100));
	MEMBER(DATA16 time_coarse[32] ZERO_SUPPRESS_MULTI(100));
	MEMBER(DATA16 time_trigger);

	UINT32 custom_header NOENCODE
    {
		0_4:   id = MATCH(id);
		5_8:   internal_status;
		9_17:  count;
		24_31: 0xab;
	};

    UINT32 trigger_window NOENCODE;
    UINT32 status_register NOENCODE;

    UINT32 mvlc_header NOENCODE
    {
        0_15: words;
        16_31: mh = MATCH(0xF500);
    }

    UINT32 skip_event_header NOENCODE;

	list(1 <= index < mvlc_header.words) 
    {
		UINT32 event NOENCODE 
        {
			0_10:  time_fine;
			11_23: time_coarse;
			24:    future;
//			25:    boo_ba_doo_ba_doop;
			25_29: channel;
            30_31: meh;

			ENCODE(time_fine[channel], (value = time_fine));
			ENCODE(time_coarse[channel], (value = time_coarse));
		}
	}

}

/*
VME_GSI_VFTX2_LT(id)
{
	MEMBER(DATA12 time_fine[64] ZERO_SUPPRESS_MULTI(100));
	MEMBER(DATA16 time_coarse[64] ZERO_SUPPRESS_MULTI(100));
	MEMBER(DATA16 time_trigger);

	UINT32 custom_header 
    {
		0_4:   id;// = MATCH(id);
		5_8:   internal_status;
		9_17:  count;
		24_31: 0xab;
	}

	if (0 < custom_header.count) 
    {
		UINT32 event_header 
        {
			0_7:   0xaa;
			11_23: trigger_timestamp;
			29_30: 0b01;
			31:    0b1;

			ENCODE(time_trigger, (value = trigger_timestamp));
		}
	}

	list(1 <= index < custom_header.count) 
    {
		UINT32 event NOENCODE 
        {
			0_10:  time_fine;
			11_23: time_coarse;
			24:    future;
			25_30: channel;

			ENCODE(time_fine[channel], (value = time_fine));
			ENCODE(time_coarse[channel], (value = time_coarse));
		}
	}
}
*/
/*
VME_GSI_VFTX2_7PS(id)
{
	MEMBER(DATA12 time_fine[32] ZERO_SUPPRESS_MULTI(100));
	MEMBER(DATA16 time_coarse[32] ZERO_SUPPRESS_MULTI(100));
	MEMBER(DATA16 time_trigger);

	UINT32 custom_header 
    {
		0_4:   id = MATCH(id);
		5_8:   internal_status;
		9_17:  count;
		24_31: 0xab;
	}

	if (0 < custom_header.count) 
    {
		UINT32 event_header NOENCODE 
        {
			0_7:   0xaa;
			11_23: trigger_timestamp;
			29_30: 0b01;
			31:    0b1;

			ENCODE(time_trigger, (value = trigger_timestamp));
		}
	}

	list(1 <= index < custom_header.count) 
    {
		UINT32 event NOENCODE 
        {
			0_10:  time_fine;
			11_23: time_coarse;
			24:    future;
			25_29: channel;

			ENCODE(time_fine[channel], (value = time_fine));
			ENCODE(time_coarse[channel], (value = time_coarse));
		}
	}
}
*/