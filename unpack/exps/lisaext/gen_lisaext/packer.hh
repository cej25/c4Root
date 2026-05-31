/** BEGIN_PACKER *******************************************************
 *
 * Event packer for BAD_EVENT.
 *
 * Do not edit - automatically generated.
 */

// BAD_EVENT()
template<typename __data_dest_t>
void PACKER_BAD_EVENT::__packer(__data_dest_t &__buffer)
{
  // MEMBER(DATA8 bad);
  // UINT32 be NOENCODE
  // {
    //  0_31: b = MATCH(0xbad00bad);
  // }
  // ENCODE(bad,(value=1));

}
FORCE_IMPL_DATA_SRC_FCN(void,BAD_EVENT::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for DUMMY.
 *
 * Do not edit - automatically generated.
 */

// DUMMY()
template<typename __data_dest_t>
void PACKER_DUMMY::__packer(__data_dest_t &__buffer)
{
  // UINT32 no NOENCODE;
}
FORCE_IMPL_DATA_SRC_FCN(void,DUMMY::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for FEBEX_EVENT.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_EVENT(card)
template<typename __data_dest_t>
void PACKER_FEBEX_EVENT::__packer(__data_dest_t &__buffer,uint32 card)
{
  // MEMBER(DATA8 trig);
  // MEMBER(DATA32 event_trigger_time_hi);
  // MEMBER(DATA32 event_trigger_time_lo);
  // MEMBER(DATA16 hit_pattern);
  // MEMBER(DATA16 channel_trigger_time_hi[16] ZERO_SUPPRESS);
  // MEMBER(DATA32 channel_trigger_time_lo[16] ZERO_SUPPRESS);
  // MEMBER(DATA8 pileup[16] ZERO_SUPPRESS);
  // MEMBER(DATA8 overflow[16] ZERO_SUPPRESS);
  // MEMBER(DATA8 channel_cfd[16] ZERO_SUPPRESS);
  // MEMBER(DATA32 channel_energy[16] ZERO_SUPPRESS);
  // UINT32 sumchannel NOENCODE
  // {
    //  0_07: 52;
    //  8_11: trigger_type;
    // 12_15: sfpnr;
    // 16_23: card = MATCH(card);
    // 24_31: 255;
    // ENCODE(trig,(value=trigger_type));
  // }
  // UINT32 channel_size NOENCODE
  // {
    //  0_01: ignore;
    //  2_31: size;
  // }
  // UINT32 event_timestamp_hi NOENCODE
  // {
    //  0_15: timestamp_hi;
    // 16_31: ignore;
    // ENCODE(event_trigger_time_hi,(value=timestamp_hi));
  // }
  // UINT32 event_timestamp_lo NOENCODE
  // {
    //  0_31: timestamp_lo;
    // ENCODE(event_trigger_time_lo,(value=timestamp_lo));
  // }
  // UINT32 hp NOENCODE
  // {
    //  0_15: hp;
    // 16_31: ignore;
    // ENCODE(hit_pattern,(value=hp));
  // }
  // UINT32 deadbeef NOENCODE
  // {
    //  0_31: 0xdeadbeef;
  // }
  // list(0<=index<((channel_size.size / 4) - 1))

  {
    // UINT32 channelids NOENCODE
    // {
      //  0_15: chan_ts_hi;
      // 16_23: channel_id_bits;
      // 24_31: 240;
      // ENCODE(channel_trigger_time_hi[channelids.channel_id_bits],(value=chan_ts_hi));
    // }
    // UINT32 channel_ts NOENCODE
    // {
      //  0_31: chan_ts_lo;
      // ENCODE(channel_trigger_time_lo[channelids.channel_id_bits],(value=chan_ts_lo));
    // }
    // UINT32 chan_enrgy NOENCODE
    // {
      //  0_23: chan_energy;
      // 24_29: TSF;
      //    30: pileup_flag;
      //    31: overflow_flag;
      // ENCODE(channel_cfd[channelids.channel_id_bits],(value=TSF));
      // ENCODE(channel_energy[channelids.channel_id_bits],(value=chan_energy));
      // ENCODE(pileup[channelids.channel_id_bits],(value=pileup_flag));
      // ENCODE(overflow[channelids.channel_id_bits],(value=overflow_flag));
    // }
    // UINT32 future_use NOENCODE
    // {
      //  0_31: 0;
    // }
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,FEBEX_EVENT::__packer,uint32 card);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TRACE.
 *
 * Do not edit - automatically generated.
 */

// TRACE(board)
template<typename __data_dest_t>
void PACKER_TRACE::__packer(__data_dest_t &__buffer,uint32 board)
{
  // MEMBER(DATA16 traces[16][4000] ZERO_SUPPRESS);
  // MEMBER(DATA8 channel_id_traces[16] ZERO_SUPPRESS);
  // UINT32 header NOENCODE
  // {
    //  0_07: 52;
    //  8_15: other;
    // 16_19: board = MATCH(board);
    // 24_31: ch_id;
    // ENCODE(channel_id_traces[ch_id],(value=ch_id));
  // }
  // UINT32 tracesize NOENCODE
  // {
    //  0_31: size;
  // }
  // UINT32 tracehead NOENCODE
  // {
    //  0_23: other;
    // 24_31: head;
  // }
  // list(0<=j<((tracesize.size / 4) - 2))

  {
    // UINT32 channel_trace NOENCODE
    // {
      //  0_13: data1;
      // 14_15: stuff1;
      // 16_29: data2;
      // 30_31: stuff2;
      // ENCODE(traces[header.ch_id][((2 * j) + 0)],(value=data1));
      // ENCODE(traces[header.ch_id][((2 * j) + 1)],(value=data2));
    // }
  }
  // UINT32 trace_trailer NOENCODE
  // {
    //  0_23: notused;
    // 24_31: id = RANGE(176,191);
  // }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TRACE::__packer,uint32 board);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for FEBEX_EVENT_TRACES.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_EVENT_TRACES(card)
template<typename __data_dest_t>
void PACKER_FEBEX_EVENT_TRACES::__packer(__data_dest_t &__buffer,uint32 card)
{
  // MEMBER(DATA8 trig);
  // MEMBER(DATA32 event_trigger_time_hi);
  // MEMBER(DATA32 event_trigger_time_lo);
  // MEMBER(DATA16 hit_pattern);
  // MEMBER(DATA32 num_channels_fired);
  // MEMBER(DATA8 board_num);
  // MEMBER(DATA8 channel_id[16] ZERO_SUPPRESS);
  // MEMBER(DATA16 channel_trigger_time_hi[16] ZERO_SUPPRESS);
  // MEMBER(DATA32 channel_trigger_time_lo[16] ZERO_SUPPRESS);
  // MEMBER(DATA8 pileup[16] ZERO_SUPPRESS);
  // MEMBER(DATA8 overflow[16] ZERO_SUPPRESS);
  // MEMBER(DATA8 channel_cfd[16] ZERO_SUPPRESS);
  // MEMBER(DATA32 channel_energy[16] ZERO_SUPPRESS);
  // UINT32 sumchannel NOENCODE
  // {
    //  0_07: 52;
    //  8_11: trigger_type;
    // 12_15: sfpnr;
    // 16_23: board_id = MATCH(card);
    // 24_31: 255;
    // ENCODE(board_num,(value=board_id));
    // ENCODE(trig,(value=trigger_type));
  // }
  // UINT32 channel_size NOENCODE
  // {
    //  0_01: ignore;
    //  2_31: size;
    // ENCODE(num_channels_fired,(value=((size / 4) - 1)));
  // }
  // UINT32 event_timestamp_hi NOENCODE
  // {
    //  0_15: timestamp_hi;
    // 16_31: ignore;
    // ENCODE(event_trigger_time_hi,(value=timestamp_hi));
  // }
  // UINT32 event_timestamp_lo NOENCODE
  // {
    //  0_31: timestamp_lo;
    // ENCODE(event_trigger_time_lo,(value=timestamp_lo));
  // }
  // UINT32 hp NOENCODE
  // {
    //  0_15: hp;
    // 16_31: ignore;
    // ENCODE(hit_pattern,(value=hp));
  // }
  // UINT32 deadbeef NOENCODE
  // {
    //  0_31: 0xdeadbeef;
  // }
  // if((sumchannel.trigger_type == 1))

  // else

  if ((sumchannel.trigger_type == 1))
  {
    // list(0<=index<((channel_size.size / 4) - 1))

    {
      // UINT32 channelids NOENCODE
      // {
        //  0_15: chan_ts_hi;
        // 16_23: channel_id_bits;
        // 24_31: 240;
        // ENCODE(channel_id[channelids.channel_id_bits],(value=channel_id_bits));
        // ENCODE(channel_trigger_time_hi[channelids.channel_id_bits],(value=chan_ts_hi));
      // }
      // UINT32 channel_ts NOENCODE
      // {
        //  0_31: chan_ts_lo;
        // ENCODE(channel_trigger_time_lo[channelids.channel_id_bits],(value=chan_ts_lo));
      // }
      // UINT32 chan_enrgy NOENCODE
      // {
        //  0_23: chan_energy;
        // 24_29: TSF;
        //    30: pileup_flag;
        //    31: overflow_flag;
        // ENCODE(channel_cfd[channelids.channel_id_bits],(value=TSF));
        // ENCODE(channel_energy[channelids.channel_id_bits],(value=chan_energy));
        // ENCODE(pileup[channelids.channel_id_bits],(value=pileup_flag));
        // ENCODE(overflow[channelids.channel_id_bits],(value=overflow_flag));
      // }
      // UINT32 future_use NOENCODE
      // {
        //  0_31: 0;
      // }
    }
    // list(0<=index<16)

    {
      // select optional

        // trace = TRACE(board=card);
      {
        PACK_DECL(435,TRACE,trace,/*board*/card);
      }
    }
  }

  else
  {
    // if((sumchannel.trigger_type == 3))

    if ((sumchannel.trigger_type == 3))
    {
      // several UINT32 dummy NOENCODE;
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,FEBEX_EVENT_TRACES::__packer,uint32 card);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for FEBEX_PADDING.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_PADDING()
template<typename __data_dest_t>
void PACKER_FEBEX_PADDING::__packer(__data_dest_t &__buffer)
{
  // UINT32 pads_data NOENCODE
  // {
    //  0_11: counter;
    // 12_19: index;
    // 20_31: 0xadd;
  // }
}
FORCE_IMPL_DATA_SRC_FCN(void,FEBEX_PADDING::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TIMESTAMP_WHITERABBIT.
 *
 * Do not edit - automatically generated.
 */

// TIMESTAMP_WHITERABBIT(id)
template<typename __data_dest_t>
void PACKER_TIMESTAMP_WHITERABBIT::__packer(__data_dest_t &__buffer,uint32 id)
{
  // MEMBER(DATA12 subsystem_id);
  // MEMBER(DATA16 t1);
  // MEMBER(DATA16 t2);
  // MEMBER(DATA16 t3);
  // MEMBER(DATA16 t4);
  // UINT32 header NOENCODE
  // {
    //  0_11: id = MATCH(id);
    // 12_15: 0;
    //    16: error_bit;
    // 17_31: 0;
    // ENCODE(subsystem_id,(value=id));
  // }
  // UINT32 d1 NOENCODE
  // {
    //  0_15: t1;
    // 16_31: 0x3e1;
    // ENCODE(t1,(value=t1));
  // }
  // UINT32 d2 NOENCODE
  // {
    //  0_15: t2;
    // 16_31: 0x4e1;
    // ENCODE(t2,(value=t2));
  // }
  // UINT32 d3 NOENCODE
  // {
    //  0_15: t3;
    // 16_31: 0x5e1;
    // ENCODE(t3,(value=t3));
  // }
  // UINT32 d4 NOENCODE
  // {
    //  0_15: t4;
    // 16_31: 0x6e1;
    // ENCODE(t4,(value=t4));
  // }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TIMESTAMP_WHITERABBIT::__packer,uint32 id);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TIMESTAMP_WHITERABBIT_EXTENDED.
 *
 * Do not edit - automatically generated.
 */

// TIMESTAMP_WHITERABBIT_EXTENDED(id)
template<typename __data_dest_t>
void PACKER_TIMESTAMP_WHITERABBIT_EXTENDED::__packer(__data_dest_t &__buffer,uint32 id)
{
  // MEMBER(DATA16 subsystem_id);
  // MEMBER(DATA16 t1);
  // MEMBER(DATA16 t2);
  // MEMBER(DATA16 t3);
  // MEMBER(DATA16 t4);
  // UINT32 header NOENCODE
  // {
    //  0_12: id = MATCH(id);
    // 13_15: 0;
    //    16: error_bit;
    // 17_31: 0;
    // ENCODE(subsystem_id,(value=id));
  // }
  // UINT32 d1 NOENCODE
  // {
    //  0_15: t1;
    // 16_31: 0x3e1;
    // ENCODE(t1,(value=t1));
  // }
  // UINT32 d2 NOENCODE
  // {
    //  0_15: t2;
    // 16_31: 0x4e1;
    // ENCODE(t2,(value=t2));
  // }
  // UINT32 d3 NOENCODE
  // {
    //  0_15: t3;
    // 16_31: 0x5e1;
    // ENCODE(t3,(value=t3));
  // }
  // UINT32 d4 NOENCODE
  // {
    //  0_15: t4;
    // 16_31: 0x6e1;
    // ENCODE(t4,(value=t4));
  // }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TIMESTAMP_WHITERABBIT_EXTENDED::__packer,uint32 id);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TIMESTAMP_WHITERABBIT_EXTERNAL.
 *
 * Do not edit - automatically generated.
 */

// TIMESTAMP_WHITERABBIT_EXTERNAL(id)
template<typename __data_dest_t>
void PACKER_TIMESTAMP_WHITERABBIT_EXTERNAL::__packer(__data_dest_t &__buffer,uint32 id)
{
  // MEMBER(DATA16 subsystem_id);
  // MEMBER(DATA32 run);
  // MEMBER(DATA32 t1);
  // MEMBER(DATA32 t2);
  // UINT32 header NOENCODE
  // {
    //  0_12: id = MATCH(id);
    // 13_15: 0;
    //    16: error_bit;
    // 17_31: 0;
    // ENCODE(subsystem_id,(value=id));
  // }
  // UINT32 rn NOENCODE
  // {
    //  0_31: run;
    // ENCODE(run,(value=run));
  // }
  // UINT32 d1 NOENCODE
  // {
    //  0_31: t1;
    // ENCODE(t1,(value=t1));
  // }
  // UINT32 d2 NOENCODE
  // {
    //  0_31: t2;
    // ENCODE(t2,(value=t2));
  // }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TIMESTAMP_WHITERABBIT_EXTERNAL::__packer,uint32 id);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for WR_MULTI.
 *
 * Do not edit - automatically generated.
 */

// WR_MULTI()
template<typename __data_dest_t>
void PACKER_WR_MULTI::__packer(__data_dest_t &__buffer)
{
  // MEMBER(DATA32 time_hi);
  // MEMBER(DATA32 time_lo);
  // UINT32 hi NOENCODE
  // {
    //  0_31: time;
    // ENCODE(time_hi,(value=time));
  // }
  // UINT32 lo NOENCODE
  // {
    //  0_31: time;
    // ENCODE(time_lo,(value=time));
  // }
}
FORCE_IMPL_DATA_SRC_FCN(void,WR_MULTI::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for febex_subev_traces.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(febex_subev_traces)
template<typename __data_dest_t>
void PACKER_febex_subev_traces::__packer(__data_dest_t &__buffer)
{
  // select several

    // badevent = BAD_EVENT();
  {
    PACK_DECL(459,BAD_EVENT,badevent);
  }
  // select optional

    // ts = TIMESTAMP_WHITERABBIT_EXTERNAL(id=0x300);
  {
    PACK_DECL(464,TIMESTAMP_WHITERABBIT_EXTERNAL,ts,/*id*/0x300);
  }
  // select several

    // padding = FEBEX_PADDING();
  {
    PACK_DECL(469,FEBEX_PADDING,padding);
  }
  // select several

    // data[0] = FEBEX_EVENT_TRACES(card=0);
    // data[1] = FEBEX_EVENT_TRACES(card=1);
    // data[2] = FEBEX_EVENT_TRACES(card=2);
    // data[3] = FEBEX_EVENT_TRACES(card=3);
    // data[4] = FEBEX_EVENT_TRACES(card=4);
    // data[5] = FEBEX_EVENT_TRACES(card=5);
    // data[6] = FEBEX_EVENT_TRACES(card=6);
    // data[7] = FEBEX_EVENT_TRACES(card=7);
    // data[8] = FEBEX_EVENT_TRACES(card=8);
    // data[9] = FEBEX_EVENT_TRACES(card=9);
  {
    PACK_DECL(475,FEBEX_EVENT_TRACES,data[0],/*card*/0);
    PACK_DECL(476,FEBEX_EVENT_TRACES,data[1],/*card*/1);
    PACK_DECL(477,FEBEX_EVENT_TRACES,data[2],/*card*/2);
    PACK_DECL(478,FEBEX_EVENT_TRACES,data[3],/*card*/3);
    PACK_DECL(479,FEBEX_EVENT_TRACES,data[4],/*card*/4);
    PACK_DECL(480,FEBEX_EVENT_TRACES,data[5],/*card*/5);
    PACK_DECL(481,FEBEX_EVENT_TRACES,data[6],/*card*/6);
    PACK_DECL(482,FEBEX_EVENT_TRACES,data[7],/*card*/7);
    PACK_DECL(483,FEBEX_EVENT_TRACES,data[8],/*card*/8);
    PACK_DECL(484,FEBEX_EVENT_TRACES,data[9],/*card*/9);
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,febex_subev_traces::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for EVENT.
 *
 * Do not edit - automatically generated.
 */

// EVENT
  // lisa = febex_subev_traces(procid=60);
  // ignore_unknown_subevent;
{
}

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for EVENT.
 *
 * Do not edit - automatically generated.
 */

// STICKY_EVENT
{
}

/** END_PACKER ********************************************************/
