#define TRACE_SIZE 4000 // some maximum size
#include "general.spec" 

// Reads the Padding between FEBEX events:
FEBEX_PADDING()
{
    UINT32 pads_data NOENCODE
    {
        0_11: counter;
        12_19: index;
        20_31: 0xADD;
    }
}

FEBEX_EVENT(card)
{
    MEMBER(DATA8 trig);
	MEMBER(DATA32 event_trigger_time_hi); // trigger time
	MEMBER(DATA32 event_trigger_time_lo); // "..."
    MEMBER(DATA16 hit_pattern);
	MEMBER(DATA16 channel_trigger_time_hi[16] ZERO_SUPPRESS);
	MEMBER(DATA32 channel_trigger_time_lo[16] ZERO_SUPPRESS);
	
    MEMBER(DATA8 pileup[16] ZERO_SUPPRESS);
	MEMBER(DATA8 overflow[16] ZERO_SUPPRESS);
    MEMBER(DATA8 channel_cfd[16] ZERO_SUPPRESS);
	MEMBER(DATA32 channel_energy[16] ZERO_SUPPRESS);
 
    UINT32 sumchannel NOENCODE
    { //this is the header.
        0_7: 0x34;
        8_11: trigger_type;
        12_15: sfpnr;
        16_23: card = MATCH(card);
        24_31: 0xFF;
        ENCODE(trig, (value=trigger_type));
    }

    UINT32 channel_size NOENCODE
    {
        0_1: ignore;
        2_31: size;

        //ENCODE(num_channels_fired ,  (value = size/4 - 1 ));
    }

    //sum channel data header
    UINT32 event_timestamp_hi NOENCODE
    {
        0_15: timestamp_hi;
        16_31: ignore;
        
        ENCODE(event_trigger_time_hi, (value = timestamp_hi));
    }

    UINT32 event_timestamp_lo NOENCODE
    {
        0_31: timestamp_lo;
        ENCODE(event_trigger_time_lo, (value = timestamp_lo));
    }

    UINT32 hp NOENCODE
    {
        0_15: hp;
        16_31: ignore;

        ENCODE(hit_pattern, (value = hp));
    }

    UINT32 deadbeef NOENCODE
    {
        0_31: 0xDEADBEEF;
    }

    list(0 <= index < (((channel_size.size) / 4) - 1))
    {
        UINT32 channelids NOENCODE{
            0_15: chan_ts_hi;
            16_23: channel_id_bits;
            24_31: 0xF0;

            //ENCODE(channel_id[index], (value = channel_id_bits));
            ENCODE(channel_trigger_time_hi[channelids.channel_id_bits], (value = chan_ts_hi));
        }
        UINT32 channel_ts NOENCODE
        {
            0_31: chan_ts_lo;
            ENCODE(channel_trigger_time_lo[channelids.channel_id_bits], (value = chan_ts_lo));
        }
        UINT32 chan_enrgy NOENCODE
        {
            0_23: chan_energy;
            24_29: TSF;
            30: pileup_flag;
            31: overflow_flag;
            
            ENCODE(channel_cfd[channelids.channel_id_bits], (value = TSF));
            ENCODE(channel_energy[channelids.channel_id_bits], (value = chan_energy));
            ENCODE(pileup[channelids.channel_id_bits], (value = pileup_flag));
            ENCODE(overflow[channelids.channel_id_bits], (value = overflow_flag));
        }
        UINT32 future_use NOENCODE
        {
            0_31: 0x00000000;
        }
    }
}

TRACE(board)
{
    MEMBER(DATA16 traces[16][TRACE_SIZE] ZERO_SUPPRESS);
    MEMBER(DATA8 channel_id_traces[16] ZERO_SUPPRESS);

    UINT32 header NOENCODE
    {
        0_7: 0x34;
        8_15: other;
        16_19: board = MATCH(board);
        24_31: ch_id;
        ENCODE(channel_id_traces[ch_id], (value = ch_id));
        //Info on channel ID from trace (in case no information from event header) -- Sept2024 EG
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
        
    // for example, when trace_length = 4000:
    // tracesize = 8008
    // tracesize / 2 - 4 gives total tracelength
    // tracesize / 4 - 2 gives loop length requirement (2000)


    list (0 <= j < (tracesize.size / 4 - 2))
    {
        
        UINT32 channel_trace NOENCODE
        {
            0_13: data1;
            14_15: stuff1; 
            16_29: data2;
            30_31: stuff2;

            ENCODE(traces[header.ch_id][2*j+0], (value = data1));
            ENCODE(traces[header.ch_id][2*j+1], (value = data2));
        }

    } 
        

    UINT32 trace_trailer NOENCODE
    {
        0_23: notused;
        24_31: id = RANGE(0xb0,0xbf);
    }
}




FEBEX_EVENT_TRACES(card)
{
    MEMBER(DATA8 trig);
	MEMBER(DATA32 event_trigger_time_hi); // trigger time
	MEMBER(DATA32 event_trigger_time_lo); // "..."
    MEMBER(DATA16 hit_pattern);
    MEMBER(DATA32 num_channels_fired);
    MEMBER(DATA8 board_num);

	MEMBER(DATA8 channel_id[16] ZERO_SUPPRESS);
	MEMBER(DATA16 channel_trigger_time_hi[16] ZERO_SUPPRESS);
	MEMBER(DATA32 channel_trigger_time_lo[16] ZERO_SUPPRESS);
	
    MEMBER(DATA8 pileup[16] ZERO_SUPPRESS);
	MEMBER(DATA8 overflow[16] ZERO_SUPPRESS);
    MEMBER(DATA8 channel_cfd[16] ZERO_SUPPRESS);
	MEMBER(DATA32 channel_energy[16] ZERO_SUPPRESS);

    //:::  Trace info :::
    // MEMBER(DATA8 channel_id_traces[16] ZERO_SUPPRESS);  //Info on channel ID from trace (in case no information from event header) -- Sept2024 EG
    // MEMBER(DATA16 traces[16][TRACE_SIZE] ZERO_SUPPRESS);

    UINT32 sumchannel NOENCODE
    { //this is the header.
        0_7: 0x34;
        8_11: trigger_type;
        12_15: sfpnr;
        16_23: board_id = MATCH(card);
        24_31: 0xFF;
        ENCODE(board_num, (value = board_id));
        ENCODE(trig, (value=trigger_type));
    }

    //ENCODE(Nboards, (value = sumchannel.board_id));

    UINT32 channel_size NOENCODE
    {
        0_1: ignore;
        2_31: size;

        ENCODE(num_channels_fired,  (value = size/4 - 1 ));
    }

    //sum channel data header
    UINT32 event_timestamp_hi NOENCODE
    {
        0_15: timestamp_hi;
        16_31: ignore;
        
        ENCODE(event_trigger_time_hi, (value = timestamp_hi));
    }

    UINT32 event_timestamp_lo NOENCODE
    {
        0_31: timestamp_lo;
        ENCODE(event_trigger_time_lo, (value = timestamp_lo));
    }

    UINT32 hp NOENCODE
    {
        0_15: hp;
        16_31: ignore;

        ENCODE(hit_pattern, (value = hp));
    }

    UINT32 deadbeef NOENCODE
    {
        0_31: 0xDEADBEEF;
    }

    if (sumchannel.trigger_type == 1)
    {
        list(0 <= index < (((channel_size.size) / 4) - 1))
        {
            UINT32 channelids NOENCODE
            {
                0_15: chan_ts_hi;
                16_23: channel_id_bits;
                24_31: 0xF0;

                ENCODE(channel_id[channelids.channel_id_bits], (value = channel_id_bits));
                ENCODE(channel_trigger_time_hi[channelids.channel_id_bits], (value = chan_ts_hi));
            }
            UINT32 channel_ts NOENCODE
            {
                0_31: chan_ts_lo;
                ENCODE(channel_trigger_time_lo[channelids.channel_id_bits], (value = chan_ts_lo));
            }
            UINT32 chan_enrgy NOENCODE
            {
                0_23: chan_energy;
                24_29: TSF;
                30: pileup_flag;
                31: overflow_flag;
                
                ENCODE(channel_cfd[channelids.channel_id_bits], (value = TSF));
                ENCODE(channel_energy[channelids.channel_id_bits], (value = chan_energy));
                ENCODE(pileup[channelids.channel_id_bits], (value = pileup_flag));
                ENCODE(overflow[channelids.channel_id_bits], (value = overflow_flag));
            }
            UINT32 future_use NOENCODE
            {
                0_31: 0x00000000;
            }
        }


        // can't do a list based on channel size, because sometimes there is no channel size
        // can't do a list based on 16, because sometimes there is not 16.. but it tries..

        list (0 <= index < 16)
        //list (0 <= index < (((channel_size.size) / 4) - 1)) // i have no idea.
        {
            select optional
            {
                trace = TRACE(board=card);
            }
        }

        //select several
        //{
        //    trace = TRACE();
        //}

    }
    else if (sumchannel.trigger_type == 3)
    {
        several  UINT32 dummy NOENCODE;
    }

}
