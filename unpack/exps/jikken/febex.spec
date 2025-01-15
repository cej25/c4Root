#define TRACE_SIZE 10000 // some maximum size?
#define TRACE_CHANNELS 16

FEBEX_PADDING()
{
	UINT32 pads_data NOENCODE 
	{
		0_11:  counter;
		12_19: index;
		20_31: 0xadd;
	}
}

FEBEX_TRACES()
{

	MEMBER(DATA8 fboard);
	MEMBER(DATA32 ftrig_time_hi); // trigger time
	MEMBER(DATA32 ftrig_time_lo); // "..."
	MEMBER(DATA8 channel_id[16] NO_INDEX_LIST);
	MEMBER(DATA16 pileup);
	MEMBER(DATA32 fts_hi[16] ZERO_SUPPRESS);
	MEMBER(DATA32 fts_lo[16] ZERO_SUPPRESS);
	MEMBER(DATA32 fen[16] ZERO_SUPPRESS);
	MEMBER(DATA16 ftrace[16][TRACE_SIZE] ZERO_SUPPRESS);

	UINT32 FF_header NOENCODE // "sum channel header"
	{
		0_7:   three_four;
		8_11:  trigger_type;
		12_15: sfp;
		16_23: board_id;
		24_31: 0xFF;

		ENCODE(fboard, (value = board_id));
	}

	UINT32 febex_chan_size NOENCODE
	{	
		0_1: ignore;
		2_31: size;
	}

	UINT32 febex_half_time NOENCODE 
	{
		0_15: ext_time;
		16_31: other;
		
		ENCODE(ftrig_time_hi, (value = ext_time)); 
	}

	UINT32 febex_event_time NOENCODE 
	{
		0_31: time;

		ENCODE(ftrig_time_lo, (value = time));
	}

	UINT32 febex_flags NOENCODE
	{
		0_15: hit_pattern;
		16_31: pile_flags;

		ENCODE(pileup, (value=pile_flags));

	}

	UINT32 deadbeef NOENCODE
	{
		0_31: 0xdeadbeef;
	}

	if (FF_header.trigger_type == 3)
	{

		// if trigger = 3 ("pulser trigger") only header information
		list (0 <= i < 16)
		{
			UINT32 pulse_header NOENCODE
			{
				0_7: 0x34; // check for perfect match to make sure
				8_31: stuff;
			}

			UINT32 pulse_trace_size NOENCODE
			{
				0_31: size;
			}

			UINT32 pulse_trace_header NOENCODE
			{
				0_31: head;
			}

			UINT32 pulse_trace_trailer NOENCODE
			{
				0_31: trailer;
			}
		}

	}
	else
	{
		list (0 <= i < ((febex_chan_size.size / 4) - 1)) 
		{

			UINT32 F0_header NOENCODE
			{
				0_15: ext_chan_ts;
				16_23: ch_id;
				24_31: 0xF0;

				ENCODE(fts_hi[ch_id], (value = ext_chan_ts)); // i should == ch_id
				ENCODE(channel_id APPEND_LIST, (value = ch_id)); // channel id?
			}

			UINT32 febex_chan_ts NOENCODE
			{
				0_31: chan_ts;

				ENCODE(fts_lo[F0_header.ch_id], (value = chan_ts));
			}

			UINT32 febex_chan_en NOENCODE
			{
				0_23: chan_en;
				24_29: cf;
				30: pileup;
				31: overflow; 

				ENCODE(fen[F0_header.ch_id], (value = chan_en));
			}

			UINT32 future_use NOENCODE 
			{
				0_31: future;
			}
		}

		list (0 <= i < TRACE_CHANNELS)
		{
			UINT32 header NOENCODE
			{
				0_7: 0x34;
				8_23: other;
				24_31: ch_id;
			}

			UINT32 tracesize NOENCODE
			{
				0_31: size;
			}

			UINT32 tracehead NOENCODE
			{
				0_23: other;
				24_31: head;
			}
			
			//for example, when trace_length = 4000:
			//tracesize = 8008
			//tracesize / 2 - 4 gives total tracelength
			//tracesize / 4 - 2 gives loop length requirement (2000)
			
			list (0 <= j < (tracesize.size / 4 - 2))
			{
				
				UINT32 channel_trace NOENCODE
				{
					0_13: data1;
					14_15: stuff1; 
					16_29: data2;
					30_31: stuff2;

					ENCODE(ftrace[header.ch_id][2*j+0], (value = data1));
					ENCODE(ftrace[header.ch_id][2*j+1], (value = data2));
				}

			}

			UINT32 trace_trailer NOENCODE
			{
				0_23: notused;
				24_31: id = RANGE(0xb0,0xbf);
			}
		}
	}

}
