#define MAX_TDC_HITS 1024

TAMEX4_HEADER()
{
	MEMBER(DATA16 post_trig_ns);
	MEMBER(DATA16 pre_trig_ns);
	UINT32 trigger_window NOENCODE 
	{
		 0_15: post_trig_ns;
		16_31: pre_trig_ns;

		ENCODE(post_trig_ns, (value=post_trig_ns));
		ENCODE(pre_trig_ns, (value=pre_trig_ns));
	}

}

TAMEX4_PADDING()
{
	UINT32 padding NOENCODE 
	{
		 0_11: counter;
		12_19: index;
		20_31: 0xadd;
	}
}

TAMEX4_TIME_DATA(sfp, card, time_coarse, time_fine, time_edge, time_channel, time_epoch)
{
	MEMBER(DATA12 time_coarse[MAX_TDC_HITS] NO_INDEX_LIST);
	MEMBER(DATA12 time_fine[MAX_TDC_HITS] NO_INDEX_LIST);
	MEMBER(DATA12 time_edge[MAX_TDC_HITS] NO_INDEX_LIST);
	MEMBER(DATA12 time_channel[MAX_TDC_HITS] NO_INDEX_LIST);
	MEMBER(DATA32 time_epoch[MAX_TDC_HITS] NO_INDEX_LIST);

	UINT32 data NOENCODE 
	{
		 0_10: coarse;
		   11: is_leading;
		// fine=0x3ff -> no TDC time.
		12_21: fine;
		22_27: channel;
		28_31: type = 0x8;

		ENCODE(time_coarse APPEND_LIST, (value=coarse));
		ENCODE(time_fine APPEND_LIST, (value=fine));
		ENCODE(time_edge APPEND_LIST, (value=is_leading));
		ENCODE(time_channel APPEND_LIST, (value=channel));
		ENCODE(time_epoch APPEND_LIST, (value=0));
	}

}

TAMEX4_EPOCH_DATA(sfp, card, time_coarse, time_fine, time_edge, time_channel, time_epoch)
{
	MEMBER(DATA12 time_coarse[MAX_TDC_HITS] NO_INDEX_LIST);
	MEMBER(DATA12 time_fine[MAX_TDC_HITS] NO_INDEX_LIST);
	MEMBER(DATA12 time_edge[MAX_TDC_HITS] NO_INDEX_LIST);
	MEMBER(DATA12 time_channel[MAX_TDC_HITS] NO_INDEX_LIST);
	MEMBER(DATA32 time_epoch[MAX_TDC_HITS] NO_INDEX_LIST);

	UINT32 data NOENCODE 
	{
		0_27: epoch;
		28_31: 0x6;

		ENCODE(time_coarse APPEND_LIST, (value=0));
		ENCODE(time_fine APPEND_LIST, (value=0));
		ENCODE(time_edge APPEND_LIST, (value=0));
		ENCODE(time_channel APPEND_LIST, (value=0));
		ENCODE(time_epoch APPEND_LIST, (value=epoch));
	}

}

TAMEX4_SFP(sfp, card)
{
    MEMBER(DATA32 event_size);
	MEMBER(DATA12 time_coarse[MAX_TDC_HITS] NO_INDEX_LIST);
	MEMBER(DATA12 time_fine[MAX_TDC_HITS] NO_INDEX_LIST);
	MEMBER(DATA12 time_edge[MAX_TDC_HITS] NO_INDEX_LIST);
	MEMBER(DATA12 time_channel[MAX_TDC_HITS] NO_INDEX_LIST);
	MEMBER(DATA32 time_epoch[MAX_TDC_HITS] NO_INDEX_LIST);

	UINT32 indicator NOENCODE {
		  0_7: 0x34;
		 8_11: trigger_type;
		12_15: sfp = MATCH(sfp);
		16_23: card = MATCH(card);
		24_31: 0;
	}

	MATCH_END;

	UINT32 data_size NOENCODE 
	{
		// TDC header + epocs + times + error + trailer.
		0_31: bytes;

		ENCODE(event_size, (value=bytes));
	}

	UINT32 tdc_header NOENCODE {
		 0_15: lec;
		   16: buf_no;
		17_19: reserved;
		20_23: trigger_type;
		24_31: 0xaa;
	}

	list (0 <= i < data_size.bytes / 4 - 3) 
	{
		select 
		{
			epoch = TAMEX4_EPOCH_DATA(sfp=sfp, card=card, time_coarse=time_coarse, time_fine=time_fine, time_edge=time_edge, time_channel=time_channel, time_epoch=time_epoch);
			time = TAMEX4_TIME_DATA(sfp=sfp, card=card, time_coarse=time_coarse, time_fine=time_fine, time_edge=time_edge, time_channel=time_channel, time_epoch=time_epoch);
		}
	}

	UINT32 error_bits NOENCODE 
	{
		 0_23: bits;
		24_31: 0xee;
	}

	UINT32 trailer NOENCODE 
	{
		0_15: lec;
		16: buf_no;
		17_19: reserved;
		20_23: trigger_type;
		24_31: 0xbb;
	}
}
