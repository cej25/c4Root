#define TRACE_SIZE 10000 // some maximum size?
#define TRACE_CHANNELS 16

FEBEX_TRACES()
{
	MEMBER(DATA16 ftrace[16][TRACE_SIZE] ZERO_SUPPRESS);
	MEMBER(DATA8 channel_id[16] ZERO_SUPPRESS);	


	list (0 <= i < TRACE_CHANNELS)
	{
		UINT32 header NOENCODE
		{
			0_7: 0x34;
			8_23: other;
			24_31: ch_id;
			ENCODE(channel_id[ch_id], (value = ch_id)); // channel id?
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
			
		//ENCODE(flength[header.ch_id], (value = tracesize.size / 2 - 4)); // i think this is correct

		/*
		for example, when trace_length = 4000:
		tracesize = 8008
		tracesize / 2 - 4 gives total tracelength
		tracesize / 4 - 2 gives loop length requirement (2000)
		*/
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

	/*UINT32 trace_trailer NOENCODE 
	{
		0_23: notused;
		24_31: 0xb0;
	}*/

}
