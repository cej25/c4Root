#define TRACE_SIZE 10000 // some maximum size?
#define TRACE_CHANNELS 16


//Reads the Padding between FEBEX events:
FEBEX_PADDING(){
    UINT32 pads_data NOENCODE{
    0_11: counter;
    12_19: index;
    20_31: 0xadd;
    }
}


FEBEX_EVENT(){
	MEMBER(DATA8 board_id);
	MEMBER(DATA32 event_trigger_time_hi); // trigger time
	MEMBER(DATA32 event_trigger_time_lo); // "..."
    MEMBER(DATA16 hit_pattern);
    MEMBER(DATA32 num_channels_fired);


	MEMBER(DATA8 channel_id[16] ZERO_SUPPRESS);
	MEMBER(DATA16 channel_trigger_time_hi[16] ZERO_SUPPRESS);
    
	MEMBER(DATA32 channel_trigger_time_lo[16] ZERO_SUPPRESS);
	
    MEMBER(DATA8 pileup[16]);
	MEMBER(DATA8 overflow[16]);
    MEMBER(DATA8 channel_cfd[16] ZERO_SUPPRESS);
	MEMBER(DATA32 channel_energy[16] ZERO_SUPPRESS);
 
    UINT32 sumchannel NOENCODE{ //this is the header.
        0_7: 0x34;
        8_11: trigger_type;
        12_15: sfpnr;
        16_23: board_id;
        24_31: 0xFF;

        ENCODE(board_id, (value = board_id));
    }

    UINT32 channel_size NOENCODE{
        0_1: ignore;
        2_31: size;

        ENCODE( num_channels_fired ,  (value = size/4 - 1 ));
    }

    //sum channel data header
    UINT32 event_timestamp_hi NOENCODE{
        0_15: timestamp_hi;
        16_31: ignore;
        
        ENCODE(event_trigger_time_hi, (value = timestamp_hi));
    }

    UINT32 event_timestamp_lo NOENCODE{
        0_31: timestamp_lo;
        ENCODE(event_trigger_time_lo, (value = timestamp_lo));
    }

    UINT32 hp NOENCODE{
        0_15: hp;
        16_31: ignore;

        ENCODE(hit_pattern, (value = hp));
    }

    UINT32 deadbeef NOENCODE{
        0_31: 0xDEADBEEF;
    }

    list(0 <= index < (((channel_size.size) / 4) - 1)){
        UINT32 channelids NOENCODE{
            0_15: chan_ts_hi;
            16_23: channel_id_bits;
            24_31: 0xF0;

            ENCODE(channel_id[index], (value = channel_id_bits));
            ENCODE(channel_trigger_time_hi[index], (value = chan_ts_hi));
        }
        UINT32 channel_ts NOENCODE{
            0_31: chan_ts_lo;
            ENCODE(channel_trigger_time_lo[index], (value = chan_ts_lo));
        }
        UINT32 chan_enrgy NOENCODE{
            0_23: chan_energy;
            24_29: TSF;
            30: pileup_flag;
            31: overflow_flag;
            
            ENCODE(channel_cfd[index], (value = TSF));
            ENCODE(channel_energy[index], (value = chan_energy));
            ENCODE(pileup[index], (value = pileup_flag));
            ENCODE(overflow[index], (value = overflow_flag));
        }
        UINT32 future_use NOENCODE{
            0_31: 0x00000000;
        }
    }
}
