BAD_EVENT()
{
	UINT32 be NOENCODE 
	{
		0_31: bad = MATCH(0xBAD00BAD);
	};
}

PADDING()
{
	UINT32 padd NOENCODE 
	{
		0_19: counter;
		20_31: 0xADD;
	};
}

CLOCK_TDC_MBS_PARAM(sfp_id_0, sfp_id_1, sfp_id_2, sfp_id_3, chan_per_ctdc)
{
	UINT32 slave_num NOENCODE
	{
		  0_7: sfp0 = MATCH(sfp_id_0);
		 8_15: sfp1 = MATCH(sfp_id_1);
		16_23: sfp2 = MATCH(sfp_id_2);
		24_31: sfp3 = MATCH(sfp_id_3);
	};

	UINT32 trig_window NOENCODE
	{
		0_31: window;
	};

	UINT32 chan_number NOENCODE
	{
		0_31: number = MATCH(chan_per_ctdc);
	}
}

CLOCK_TDC_EVENT(sfp_id, tdc_id)
{
	MEMBER(DATA32 event_counter_lo);
	MEMBER(DATA32 event_counter_hi);
	MEMBER(DATA32 trig_coarse_time_lo);
	MEMBER(DATA32 trig_coarse_time_hi);
	MEMBER(DATA12 time_coarse[258] ZERO_SUPPRESS_MULTI(128));
	MEMBER(DATA12 time_fine[258] ZERO_SUPPRESS_MULTI(128));
	MEMBER(DATA8 lead_or_trail[258] ZERO_SUPPRESS_MULTI(128));

	UINT32 header NOENCODE
	{
		  0_7: threefour = MATCH(0x34);
		 8_11: trig_type;
		12_15: sfp = MATCH(sfp_id);
		16_23: tdc = MATCH(tdc_id);
		24_31: channel_id;
	};

	MATCH_END;

	UINT32 channel_num NOENCODE
	{
		0_31: ch_num;
	}; // maybe we want to...

	UINT32 counter_lo NOENCODE 
	{
		0_31: value;
		ENCODE(event_counter_lo, (value = value));
	};

	UINT32 counter_hi NOENCODE 
	{
		0_15: value;
		ENCODE(event_counter_hi, (value = value));
	};

	UINT32 trig_coarse_lo NOENCODE 
	{
		0_9: ignore;
		10_31: value;
		ENCODE(trig_coarse_time_lo, (value = value));
	};

	UINT32 trig_coarse_hi NOENCODE 
	{
		0_23: value;
		24_31: ignore;
		ENCODE(trig_coarse_time_hi, (value = value));
	};

	UINT32 channel_header NOENCODE
	{
		0_7: threefour = MATCH(0x34);
		8_11: trig_type;
		12_15: sfp = MATCH(sfp_id);
		16_23: tdc = MATCH(tdc_id);
		24_31: channel_id = RANGE(0, 128);
	};

	UINT32 data_bytes NOENCODE
	{
		0_31: bytes;
	};

	list (0 <= i < data_bytes.bytes / 4) 
	{
		UINT32 data NOENCODE
		{
			0_3: time_fine;
			4_15: time_coarse;
			16: time_coarse_ext;
			17: edge;
			18: ws;
			19: time_coarse_overflow;
			20: rb_overflow;
			21_23: status; // if not 4, dummy data
			24_31: channel; // 128 = trigger, >128 = dummy data

			ENCODE(time_coarse[
			    (((128 > channel) || (128 == channel && 0 ==
						  edge)) && (4 == status)) *
			    (channel * 2 + edge) +
			    !(((128 > channel) || (128 == channel && 0 ==
						    edge)) && (4 == status)) *
			    257], (value = time_coarse));
			ENCODE(time_fine[
			    (((128 > channel) || (128 == channel && 0 ==
						  edge)) && (4 == status)) *
			    (channel * 2 + edge) +
			    !(((128 > channel) || (128 == channel && 0 ==
						    edge)) && (4 == status)) *
			    257], (value = time_fine));
			ENCODE(lead_or_trail[
			    (((128 > channel) || (128 == channel && 0 ==
						  edge)) && (4 == status)) *
			    (channel * 2 + edge) +
			    !(((128 > channel) || (128 == channel && 0 ==
						    edge)) && (4 == status)) *
			    257], (value = edge));
		}
	}
}

CLOCK_TDC_EVENT_16PH(sfp_id, tdc_id)
{
	MEMBER(DATA32 event_counter_lo);
	MEMBER(DATA32 event_counter_hi);
	MEMBER(DATA32 trig_coarse_time_lo);
	MEMBER(DATA32 trig_coarse_time_hi);
	MEMBER(DATA12 time_coarse[258] ZERO_SUPPRESS_MULTI(128));
	MEMBER(DATA12 time_fine[258] ZERO_SUPPRESS_MULTI(128));
	MEMBER(DATA8 lead_or_trail[258] ZERO_SUPPRESS_MULTI(128));

	UINT32 header NOENCODE
	{
		0_7: threefour = MATCH(0x34);
		8_11: trig_type;
		12_15: sfp = MATCH(sfp_id);
		16_23: tdc = MATCH(tdc_id);
		24_31: channel_id;
	};

	MATCH_END;

	UINT32 channel_num NOENCODE
	{
		0_31: ch_num;
	};

	UINT32 counter_lo NOENCODE 
	{
		0_31: value;
		ENCODE(event_counter_lo, (value = value));
	};

	UINT32 counter_hi NOENCODE 
	{
		0_15: value;
		ENCODE(event_counter_hi, (value = value));
	};

	UINT32 trig_coarse_lo NOENCODE 
	{
		0_9: ignore;
		10_31: value;
		ENCODE(trig_coarse_time_lo, (value = value));
	};

	UINT32 trig_coarse_hi NOENCODE 
	{
		0_23: value;
		24_31: ignore;
		ENCODE(trig_coarse_time_hi, (value = value));
	};

	UINT32 channel_header NOENCODE
	{
		0_7: threefour = MATCH(0x34);
		8_11: trig_type;
		12_15: sfd = MATCH(sfp_id);
		16_23: tdc = MATCH(tdc_id);
		24_31: channel_id = RANGE(0, 128);
	};

	UINT32 data_bytes NOENCODE
	{
		0_31: bytes;
	};

	list (0 <= i < data_bytes.bytes / 4) 
	{
		UINT32 data NOENCODE
		{
			0_4: time_fine;
			5_16: time_coarse;
			17: time_coarse_ext;
			18: edge;
			19: ws;
			20: time_coarse_overflow;
			21: rb_overflow;
			22: dummy;
			23: is_data;
			24_31: channel; // 128 == trigger, >128 dummy data

			ENCODE(time_coarse[
			    (((128 > channel) || (128 == channel && 0 ==
						  edge)) && is_data) *
			    (channel * 2 + edge) +
			    !(((128 > channel) || (128 == channel && 0 ==
						    edge)) && is_data) *
			    257], (value = time_coarse));
			ENCODE(time_fine[
			    (((128 > channel) || (128 == channel && 0 ==
						  edge)) && is_data) *
			    (channel * 2 + edge) +
			    !(((128 > channel) || (128 == channel && 0 ==
						    edge)) && is_data) *
			    257], (value = time_fine));
			ENCODE(lead_or_trail[
			    (((128 > channel) || (128 == channel && 0 ==
						  edge)) && is_data) *
			    (channel * 2 + edge) +
			    !(((128 > channel) || (128 == channel && 0 ==
						    edge)) && is_data) *
			    257], (value = edge));
		};
	}
}
