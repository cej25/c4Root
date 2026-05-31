/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for BAD_EVENT.
 *
 * Do not edit - automatically generated.
 */

// BAD_EVENT()
template<typename __data_src_t>
void BAD_EVENT::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "BAD_EVENT",CT_OUT(NORM));
  }
  // MEMBER(DATA8 bad);
  // UINT32 be NOENCODE
  // {
    //  0_31: b = MATCH(0xbad00bad);
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 b : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 b : 32; // 0..31
#endif
    };
    uint32  u32;
  } be;
  READ_FROM_BUFFER_FULL(144,uint32 ,be,be.u32,0);
  CHECK_BITS_EQUAL(143,be.b,0xbad00bad);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: be ", CT_OUT(BOLD), be.u32, CT_OUT(NORM));
    printf(".b=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  be.b, CT_OUT(NORM));
    printf("\n");
  }
  // ENCODE(bad,(value=1));

  {
    bad.value = 1;
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,BAD_EVENT::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for DUMMY.
 *
 * Do not edit - automatically generated.
 */

// DUMMY()
template<typename __data_src_t>
void DUMMY::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "DUMMY",CT_OUT(NORM));
  }
  // UINT32 no NOENCODE;
  uint32  no;READ_FROM_BUFFER(151,uint32 ,no,2);
}
FORCE_IMPL_DATA_SRC_FCN(void,DUMMY::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for FEBEX_EVENT.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_EVENT(card)
template<typename __data_src_t>
void FEBEX_EVENT::__unpack(__data_src_t &__buffer,uint32 card)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "FEBEX_EVENT",CT_OUT(NORM));
  }
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
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 unnamed_0_7 : 8; // 0..7
      uint32 trigger_type : 4; // 8..11
      uint32 sfpnr : 4; // 12..15
      uint32 card : 8; // 16..23
      uint32 unnamed_24_31 : 8; // 24..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_24_31 : 8; // 24..31
      uint32 card : 8; // 16..23
      uint32 sfpnr : 4; // 12..15
      uint32 trigger_type : 4; // 8..11
      uint32 unnamed_0_7 : 8; // 0..7
#endif
    };
    uint32  u32;
  } sumchannel;
  READ_FROM_BUFFER_FULL(188,uint32 ,sumchannel,sumchannel.u32,4);
  CHECK_BITS_EQUAL(182,sumchannel.unnamed_0_7,52);
  CHECK_BITS_EQUAL(185,sumchannel.card,card);
  CHECK_BITS_EQUAL(186,sumchannel.unnamed_24_31,255);
  {
    trig.value = sumchannel.trigger_type;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: sumchannel ", CT_OUT(BOLD), sumchannel.u32, CT_OUT(NORM));
    printf(".trigger_type=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  sumchannel.trigger_type, CT_OUT(NORM));
    printf(".sfpnr=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  sumchannel.sfpnr, CT_OUT(NORM));
    printf(".card=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  sumchannel.card, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 channel_size NOENCODE
  // {
    //  0_01: ignore;
    //  2_31: size;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 ignore : 2; // 0..1
      uint32 size : 30; // 2..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 size : 30; // 2..31
      uint32 ignore : 2; // 0..1
#endif
    };
    uint32  u32;
  } channel_size;
  READ_FROM_BUFFER_FULL(196,uint32 ,channel_size,channel_size.u32,5);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: channel_size ", CT_OUT(BOLD), channel_size.u32, CT_OUT(NORM));
    printf(".ignore=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_size.ignore, CT_OUT(NORM));
    printf(".size=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_size.size, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 event_timestamp_hi NOENCODE
  // {
    //  0_15: timestamp_hi;
    // 16_31: ignore;
    // ENCODE(event_trigger_time_hi,(value=timestamp_hi));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 timestamp_hi : 16; // 0..15
      uint32 ignore : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 ignore : 16; // 16..31
      uint32 timestamp_hi : 16; // 0..15
#endif
    };
    uint32  u32;
  } event_timestamp_hi;
  READ_FROM_BUFFER_FULL(205,uint32 ,event_timestamp_hi,event_timestamp_hi.u32,6);
  {
    event_trigger_time_hi.value = event_timestamp_hi.timestamp_hi;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: event_timestamp_hi ", CT_OUT(BOLD), event_timestamp_hi.u32, CT_OUT(NORM));
    printf(".timestamp_hi=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event_timestamp_hi.timestamp_hi, CT_OUT(NORM));
    printf(".ignore=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event_timestamp_hi.ignore, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 event_timestamp_lo NOENCODE
  // {
    //  0_31: timestamp_lo;
    // ENCODE(event_trigger_time_lo,(value=timestamp_lo));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 timestamp_lo : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 timestamp_lo : 32; // 0..31
#endif
    };
    uint32  u32;
  } event_timestamp_lo;
  READ_FROM_BUFFER_FULL(211,uint32 ,event_timestamp_lo,event_timestamp_lo.u32,7);
  {
    event_trigger_time_lo.value = event_timestamp_lo.timestamp_lo;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: event_timestamp_lo ", CT_OUT(BOLD), event_timestamp_lo.u32, CT_OUT(NORM));
    printf(".timestamp_lo=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event_timestamp_lo.timestamp_lo, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 hp NOENCODE
  // {
    //  0_15: hp;
    // 16_31: ignore;
    // ENCODE(hit_pattern,(value=hp));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 hp : 16; // 0..15
      uint32 ignore : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 ignore : 16; // 16..31
      uint32 hp : 16; // 0..15
#endif
    };
    uint32  u32;
  } hp;
  READ_FROM_BUFFER_FULL(219,uint32 ,hp,hp.u32,8);
  {
    hit_pattern.value = hp.hp;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: hp ", CT_OUT(BOLD), hp.u32, CT_OUT(NORM));
    printf(".hp=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  hp.hp, CT_OUT(NORM));
    printf(".ignore=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  hp.ignore, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 deadbeef NOENCODE
  // {
    //  0_31: 0xdeadbeef;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 unnamed_0_31 : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_0_31 : 32; // 0..31
#endif
    };
    uint32  u32;
  } deadbeef;
  READ_FROM_BUFFER_FULL(224,uint32 ,deadbeef,deadbeef.u32,9);
  CHECK_BITS_EQUAL(223,deadbeef.unnamed_0_31,0xdeadbeef);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: deadbeef ", CT_OUT(BOLD), deadbeef.u32, CT_OUT(NORM));
    printf("\n");
  }
  // list(0<=index<((channel_size.size / 4) - 1))

  for (uint32 index = 0; index < (uint32) (((channel_size.size / 4) - 1)); ++index)
  {
    // UINT32 channelids NOENCODE
    // {
      //  0_15: chan_ts_hi;
      // 16_23: channel_id_bits;
      // 24_31: 240;
      // ENCODE(channel_trigger_time_hi[channelids.channel_id_bits],(value=chan_ts_hi));
    // }
    union
    {
      struct
      {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint32 chan_ts_hi : 16; // 0..15
        uint32 channel_id_bits : 8; // 16..23
        uint32 unnamed_24_31 : 8; // 24..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32 unnamed_24_31 : 8; // 24..31
        uint32 channel_id_bits : 8; // 16..23
        uint32 chan_ts_hi : 16; // 0..15
#endif
      };
      uint32  u32;
    } channelids;
    READ_FROM_BUFFER_FULL(235,uint32 ,channelids,channelids.u32,10);
    CHECK_BITS_EQUAL(231,channelids.unnamed_24_31,240);
    {
      typedef __typeof__(*(&(channel_trigger_time_hi))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = channel_trigger_time_hi.insert_index(234,channelids.channel_id_bits);
      __item.value = channelids.chan_ts_hi;
    }
    if (__buffer.is_memberdump())
    {
      printf("%s%08" PRIx32 "%s: channelids ", CT_OUT(BOLD), channelids.u32, CT_OUT(NORM));
      printf(".chan_ts_hi=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channelids.chan_ts_hi, CT_OUT(NORM));
      printf(".channel_id_bits=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channelids.channel_id_bits, CT_OUT(NORM));
      printf("\n");
    }
    // UINT32 channel_ts NOENCODE
    // {
      //  0_31: chan_ts_lo;
      // ENCODE(channel_trigger_time_lo[channelids.channel_id_bits],(value=chan_ts_lo));
    // }
    union
    {
      struct
      {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint32 chan_ts_lo : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32 chan_ts_lo : 32; // 0..31
#endif
      };
      uint32  u32;
    } channel_ts;
    READ_FROM_BUFFER_FULL(240,uint32 ,channel_ts,channel_ts.u32,11);
    {
      typedef __typeof__(*(&(channel_trigger_time_lo))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = channel_trigger_time_lo.insert_index(239,channelids.channel_id_bits);
      __item.value = channel_ts.chan_ts_lo;
    }
    if (__buffer.is_memberdump())
    {
      printf("%s%08" PRIx32 "%s: channel_ts ", CT_OUT(BOLD), channel_ts.u32, CT_OUT(NORM));
      printf(".chan_ts_lo=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_ts.chan_ts_lo, CT_OUT(NORM));
      printf("\n");
    }
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
    union
    {
      struct
      {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint32 chan_energy : 24; // 0..23
        uint32 TSF : 6; // 24..29
        uint32 pileup_flag : 1; // 30
        uint32 overflow_flag : 1; // 31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32 overflow_flag : 1; // 31
        uint32 pileup_flag : 1; // 30
        uint32 TSF : 6; // 24..29
        uint32 chan_energy : 24; // 0..23
#endif
      };
      uint32  u32;
    } chan_enrgy;
    READ_FROM_BUFFER_FULL(252,uint32 ,chan_enrgy,chan_enrgy.u32,12);
    {
      {
        typedef __typeof__(*(&(channel_cfd))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_cfd.insert_index(248,channelids.channel_id_bits);
        __item.value = chan_enrgy.TSF;
      }
      {
        typedef __typeof__(*(&(channel_energy))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_energy.insert_index(249,channelids.channel_id_bits);
        __item.value = chan_enrgy.chan_energy;
      }
      {
        typedef __typeof__(*(&(pileup))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = pileup.insert_index(250,channelids.channel_id_bits);
        __item.value = chan_enrgy.pileup_flag;
      }
      {
        typedef __typeof__(*(&(overflow))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = overflow.insert_index(251,channelids.channel_id_bits);
        __item.value = chan_enrgy.overflow_flag;
      }
    }
    if (__buffer.is_memberdump())
    {
      printf("%s%08" PRIx32 "%s: chan_enrgy ", CT_OUT(BOLD), chan_enrgy.u32, CT_OUT(NORM));
      printf(".chan_energy=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  chan_enrgy.chan_energy, CT_OUT(NORM));
      printf(".TSF=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  chan_enrgy.TSF, CT_OUT(NORM));
      printf(".pileup_flag=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  chan_enrgy.pileup_flag, CT_OUT(NORM));
      printf(".overflow_flag=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  chan_enrgy.overflow_flag, CT_OUT(NORM));
      printf("\n");
    }
    // UINT32 future_use NOENCODE
    // {
      //  0_31: 0;
    // }
    union
    {
      struct
      {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint32 unnamed_0_31 : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32 unnamed_0_31 : 32; // 0..31
#endif
      };
      uint32  u32;
    } future_use;
    READ_FROM_BUFFER_FULL(256,uint32 ,future_use,future_use.u32,13);
    CHECK_BITS_EQUAL(255,future_use.unnamed_0_31,0);
    if (__buffer.is_memberdump())
    {
      printf("%s%08" PRIx32 "%s: future_use ", CT_OUT(BOLD), future_use.u32, CT_OUT(NORM));
      printf("\n");
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,FEBEX_EVENT::__unpack,uint32 card);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TRACE.
 *
 * Do not edit - automatically generated.
 */

// TRACE(board)
template<typename __data_src_t>
void TRACE::__unpack(__data_src_t &__buffer,uint32 board)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TRACE",CT_OUT(NORM));
  }
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
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 unnamed_0_7 : 8; // 0..7
      uint32 other : 8; // 8..15
      uint32 board : 4; // 16..19
      uint32 dummy_20_23 : 4;
      uint32 ch_id : 8; // 24..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 ch_id : 8; // 24..31
      uint32 dummy_20_23 : 4;
      uint32 board : 4; // 16..19
      uint32 other : 8; // 8..15
      uint32 unnamed_0_7 : 8; // 0..7
#endif
    };
    uint32  u32;
  } header;
  READ_FROM_BUFFER_FULL(273,uint32 ,header,header.u32,15);
  CHECK_BITS_EQUAL(267,header.unnamed_0_7,52);
  CHECK_BITS_EQUAL(269,header.board,board);
  CHECK_UNNAMED_BITS_ZERO(273,header.u32,0x00f00000);
  {
    typedef __typeof__(*(&(channel_id_traces))) __array_t;
    typedef typename __array_t::item_t __item_t;
    __item_t &__item = channel_id_traces.insert_index(271,header.ch_id);
    __item.value = header.ch_id;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: header ", CT_OUT(BOLD), header.u32, CT_OUT(NORM));
    printf(".other=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.other, CT_OUT(NORM));
    printf(".board=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.board, CT_OUT(NORM));
    printf(".ch_id=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.ch_id, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 tracesize NOENCODE
  // {
    //  0_31: size;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 size : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 size : 32; // 0..31
#endif
    };
    uint32  u32;
  } tracesize;
  READ_FROM_BUFFER_FULL(278,uint32 ,tracesize,tracesize.u32,16);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: tracesize ", CT_OUT(BOLD), tracesize.u32, CT_OUT(NORM));
    printf(".size=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tracesize.size, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 tracehead NOENCODE
  // {
    //  0_23: other;
    // 24_31: head;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 other : 24; // 0..23
      uint32 head : 8; // 24..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 head : 8; // 24..31
      uint32 other : 24; // 0..23
#endif
    };
    uint32  u32;
  } tracehead;
  READ_FROM_BUFFER_FULL(284,uint32 ,tracehead,tracehead.u32,17);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: tracehead ", CT_OUT(BOLD), tracehead.u32, CT_OUT(NORM));
    printf(".other=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tracehead.other, CT_OUT(NORM));
    printf(".head=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tracehead.head, CT_OUT(NORM));
    printf("\n");
  }
  // list(0<=j<((tracesize.size / 4) - 2))

  for (uint32 j = 0; j < (uint32) (((tracesize.size / 4) - 2)); ++j)
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
    union
    {
      struct
      {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint32 data1 : 14; // 0..13
        uint32 stuff1 : 2; // 14..15
        uint32 data2 : 14; // 16..29
        uint32 stuff2 : 2; // 30..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32 stuff2 : 2; // 30..31
        uint32 data2 : 14; // 16..29
        uint32 stuff1 : 2; // 14..15
        uint32 data1 : 14; // 0..13
#endif
      };
      uint32  u32;
    } channel_trace;
    READ_FROM_BUFFER_FULL(304,uint32 ,channel_trace,channel_trace.u32,18);
    {
      {
        typedef __typeof__(*(&(traces[header.ch_id]))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = traces[header.ch_id].insert_index(302,((2 * j) + 0));
        __item.value = channel_trace.data1;
      }
      {
        typedef __typeof__(*(&(traces[header.ch_id]))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = traces[header.ch_id].insert_index(303,((2 * j) + 1));
        __item.value = channel_trace.data2;
      }
    }
    if (__buffer.is_memberdump())
    {
      printf("%s%08" PRIx32 "%s: channel_trace ", CT_OUT(BOLD), channel_trace.u32, CT_OUT(NORM));
      printf(".data1=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_trace.data1, CT_OUT(NORM));
      printf(".stuff1=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_trace.stuff1, CT_OUT(NORM));
      printf(".data2=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_trace.data2, CT_OUT(NORM));
      printf(".stuff2=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_trace.stuff2, CT_OUT(NORM));
      printf("\n");
    }
  }
  // UINT32 trace_trailer NOENCODE
  // {
    //  0_23: notused;
    // 24_31: id = RANGE(176,191);
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 notused : 24; // 0..23
      uint32 id : 8; // 24..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 id : 8; // 24..31
      uint32 notused : 24; // 0..23
#endif
    };
    uint32  u32;
  } trace_trailer;
  READ_FROM_BUFFER_FULL(313,uint32 ,trace_trailer,trace_trailer.u32,19);
  CHECK_BITS_RANGE(312,trace_trailer.id,176,191);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: trace_trailer ", CT_OUT(BOLD), trace_trailer.u32, CT_OUT(NORM));
    printf(".notused=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trace_trailer.notused, CT_OUT(NORM));
    printf(".id=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trace_trailer.id, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TRACE::__unpack,uint32 board);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for FEBEX_EVENT_TRACES.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_EVENT_TRACES(card)
template<typename __data_src_t>
void FEBEX_EVENT_TRACES::__unpack(__data_src_t &__buffer,uint32 card)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "FEBEX_EVENT_TRACES",CT_OUT(NORM));
  }
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
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 unnamed_0_7 : 8; // 0..7
      uint32 trigger_type : 4; // 8..11
      uint32 sfpnr : 4; // 12..15
      uint32 board_id : 8; // 16..23
      uint32 unnamed_24_31 : 8; // 24..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_24_31 : 8; // 24..31
      uint32 board_id : 8; // 16..23
      uint32 sfpnr : 4; // 12..15
      uint32 trigger_type : 4; // 8..11
      uint32 unnamed_0_7 : 8; // 0..7
#endif
    };
    uint32  u32;
  } sumchannel;
  READ_FROM_BUFFER_FULL(350,uint32 ,sumchannel,sumchannel.u32,21);
  CHECK_BITS_EQUAL(343,sumchannel.unnamed_0_7,52);
  CHECK_BITS_EQUAL(346,sumchannel.board_id,card);
  CHECK_BITS_EQUAL(347,sumchannel.unnamed_24_31,255);
  {
    {
      board_num.value = sumchannel.board_id;
    }
    {
      trig.value = sumchannel.trigger_type;
    }
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: sumchannel ", CT_OUT(BOLD), sumchannel.u32, CT_OUT(NORM));
    printf(".trigger_type=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  sumchannel.trigger_type, CT_OUT(NORM));
    printf(".sfpnr=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  sumchannel.sfpnr, CT_OUT(NORM));
    printf(".board_id=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  sumchannel.board_id, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 channel_size NOENCODE
  // {
    //  0_01: ignore;
    //  2_31: size;
    // ENCODE(num_channels_fired,(value=((size / 4) - 1)));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 ignore : 2; // 0..1
      uint32 size : 30; // 2..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 size : 30; // 2..31
      uint32 ignore : 2; // 0..1
#endif
    };
    uint32  u32;
  } channel_size;
  READ_FROM_BUFFER_FULL(360,uint32 ,channel_size,channel_size.u32,22);
  {
    num_channels_fired.value = ((channel_size.size / 4) - 1);
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: channel_size ", CT_OUT(BOLD), channel_size.u32, CT_OUT(NORM));
    printf(".ignore=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_size.ignore, CT_OUT(NORM));
    printf(".size=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_size.size, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 event_timestamp_hi NOENCODE
  // {
    //  0_15: timestamp_hi;
    // 16_31: ignore;
    // ENCODE(event_trigger_time_hi,(value=timestamp_hi));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 timestamp_hi : 16; // 0..15
      uint32 ignore : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 ignore : 16; // 16..31
      uint32 timestamp_hi : 16; // 0..15
#endif
    };
    uint32  u32;
  } event_timestamp_hi;
  READ_FROM_BUFFER_FULL(369,uint32 ,event_timestamp_hi,event_timestamp_hi.u32,23);
  {
    event_trigger_time_hi.value = event_timestamp_hi.timestamp_hi;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: event_timestamp_hi ", CT_OUT(BOLD), event_timestamp_hi.u32, CT_OUT(NORM));
    printf(".timestamp_hi=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event_timestamp_hi.timestamp_hi, CT_OUT(NORM));
    printf(".ignore=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event_timestamp_hi.ignore, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 event_timestamp_lo NOENCODE
  // {
    //  0_31: timestamp_lo;
    // ENCODE(event_trigger_time_lo,(value=timestamp_lo));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 timestamp_lo : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 timestamp_lo : 32; // 0..31
#endif
    };
    uint32  u32;
  } event_timestamp_lo;
  READ_FROM_BUFFER_FULL(375,uint32 ,event_timestamp_lo,event_timestamp_lo.u32,24);
  {
    event_trigger_time_lo.value = event_timestamp_lo.timestamp_lo;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: event_timestamp_lo ", CT_OUT(BOLD), event_timestamp_lo.u32, CT_OUT(NORM));
    printf(".timestamp_lo=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event_timestamp_lo.timestamp_lo, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 hp NOENCODE
  // {
    //  0_15: hp;
    // 16_31: ignore;
    // ENCODE(hit_pattern,(value=hp));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 hp : 16; // 0..15
      uint32 ignore : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 ignore : 16; // 16..31
      uint32 hp : 16; // 0..15
#endif
    };
    uint32  u32;
  } hp;
  READ_FROM_BUFFER_FULL(383,uint32 ,hp,hp.u32,25);
  {
    hit_pattern.value = hp.hp;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: hp ", CT_OUT(BOLD), hp.u32, CT_OUT(NORM));
    printf(".hp=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  hp.hp, CT_OUT(NORM));
    printf(".ignore=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  hp.ignore, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 deadbeef NOENCODE
  // {
    //  0_31: 0xdeadbeef;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 unnamed_0_31 : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_0_31 : 32; // 0..31
#endif
    };
    uint32  u32;
  } deadbeef;
  READ_FROM_BUFFER_FULL(388,uint32 ,deadbeef,deadbeef.u32,26);
  CHECK_BITS_EQUAL(387,deadbeef.unnamed_0_31,0xdeadbeef);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: deadbeef ", CT_OUT(BOLD), deadbeef.u32, CT_OUT(NORM));
    printf("\n");
  }
  // if((sumchannel.trigger_type == 1))

  // else

  if ((sumchannel.trigger_type == 1))
  {
    // list(0<=index<((channel_size.size / 4) - 1))

    for (uint32 index = 0; index < (uint32) (((channel_size.size / 4) - 1)); ++index)
    {
      // UINT32 channelids NOENCODE
      // {
        //  0_15: chan_ts_hi;
        // 16_23: channel_id_bits;
        // 24_31: 240;
        // ENCODE(channel_id[channelids.channel_id_bits],(value=channel_id_bits));
        // ENCODE(channel_trigger_time_hi[channelids.channel_id_bits],(value=chan_ts_hi));
      // }
      union
      {
        struct
        {
#if __BYTE_ORDER == __LITTLE_ENDIAN
          uint32 chan_ts_hi : 16; // 0..15
          uint32 channel_id_bits : 8; // 16..23
          uint32 unnamed_24_31 : 8; // 24..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
          uint32 unnamed_24_31 : 8; // 24..31
          uint32 channel_id_bits : 8; // 16..23
          uint32 chan_ts_hi : 16; // 0..15
#endif
        };
        uint32  u32;
      } channelids;
      READ_FROM_BUFFER_FULL(402,uint32 ,channelids,channelids.u32,27);
      CHECK_BITS_EQUAL(398,channelids.unnamed_24_31,240);
      {
        {
          typedef __typeof__(*(&(channel_id))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_id.insert_index(400,channelids.channel_id_bits);
          __item.value = channelids.channel_id_bits;
        }
        {
          typedef __typeof__(*(&(channel_trigger_time_hi))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_trigger_time_hi.insert_index(401,channelids.channel_id_bits);
          __item.value = channelids.chan_ts_hi;
        }
      }
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: channelids ", CT_OUT(BOLD), channelids.u32, CT_OUT(NORM));
        printf(".chan_ts_hi=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channelids.chan_ts_hi, CT_OUT(NORM));
        printf(".channel_id_bits=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channelids.channel_id_bits, CT_OUT(NORM));
        printf("\n");
      }
      // UINT32 channel_ts NOENCODE
      // {
        //  0_31: chan_ts_lo;
        // ENCODE(channel_trigger_time_lo[channelids.channel_id_bits],(value=chan_ts_lo));
      // }
      union
      {
        struct
        {
#if __BYTE_ORDER == __LITTLE_ENDIAN
          uint32 chan_ts_lo : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
          uint32 chan_ts_lo : 32; // 0..31
#endif
        };
        uint32  u32;
      } channel_ts;
      READ_FROM_BUFFER_FULL(407,uint32 ,channel_ts,channel_ts.u32,28);
      {
        typedef __typeof__(*(&(channel_trigger_time_lo))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_trigger_time_lo.insert_index(406,channelids.channel_id_bits);
        __item.value = channel_ts.chan_ts_lo;
      }
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: channel_ts ", CT_OUT(BOLD), channel_ts.u32, CT_OUT(NORM));
        printf(".chan_ts_lo=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_ts.chan_ts_lo, CT_OUT(NORM));
        printf("\n");
      }
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
      union
      {
        struct
        {
#if __BYTE_ORDER == __LITTLE_ENDIAN
          uint32 chan_energy : 24; // 0..23
          uint32 TSF : 6; // 24..29
          uint32 pileup_flag : 1; // 30
          uint32 overflow_flag : 1; // 31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
          uint32 overflow_flag : 1; // 31
          uint32 pileup_flag : 1; // 30
          uint32 TSF : 6; // 24..29
          uint32 chan_energy : 24; // 0..23
#endif
        };
        uint32  u32;
      } chan_enrgy;
      READ_FROM_BUFFER_FULL(419,uint32 ,chan_enrgy,chan_enrgy.u32,29);
      {
        {
          typedef __typeof__(*(&(channel_cfd))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_cfd.insert_index(415,channelids.channel_id_bits);
          __item.value = chan_enrgy.TSF;
        }
        {
          typedef __typeof__(*(&(channel_energy))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_energy.insert_index(416,channelids.channel_id_bits);
          __item.value = chan_enrgy.chan_energy;
        }
        {
          typedef __typeof__(*(&(pileup))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = pileup.insert_index(417,channelids.channel_id_bits);
          __item.value = chan_enrgy.pileup_flag;
        }
        {
          typedef __typeof__(*(&(overflow))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = overflow.insert_index(418,channelids.channel_id_bits);
          __item.value = chan_enrgy.overflow_flag;
        }
      }
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: chan_enrgy ", CT_OUT(BOLD), chan_enrgy.u32, CT_OUT(NORM));
        printf(".chan_energy=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  chan_enrgy.chan_energy, CT_OUT(NORM));
        printf(".TSF=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  chan_enrgy.TSF, CT_OUT(NORM));
        printf(".pileup_flag=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  chan_enrgy.pileup_flag, CT_OUT(NORM));
        printf(".overflow_flag=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  chan_enrgy.overflow_flag, CT_OUT(NORM));
        printf("\n");
      }
      // UINT32 future_use NOENCODE
      // {
        //  0_31: 0;
      // }
      union
      {
        struct
        {
#if __BYTE_ORDER == __LITTLE_ENDIAN
          uint32 unnamed_0_31 : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
          uint32 unnamed_0_31 : 32; // 0..31
#endif
        };
        uint32  u32;
      } future_use;
      READ_FROM_BUFFER_FULL(423,uint32 ,future_use,future_use.u32,30);
      CHECK_BITS_EQUAL(422,future_use.unnamed_0_31,0);
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: future_use ", CT_OUT(BOLD), future_use.u32, CT_OUT(NORM));
        printf("\n");
      }
    }
    // list(0<=index<16)

    for (uint32 index = 0; index < (uint32) (16); ++index)
    {
      // select optional

        // trace = TRACE(board=card);
      do
      {
        if (__buffer.empty()) goto no_match_1;
        int __match_no = 0;
        // optimized match 1: TRACE trace: (s32) => (0x00f000ff,0x00000034)
        {
        uint32 __match_peek;
        PEEK_FROM_BUFFER(436,uint32,__match_peek);
        // differ = 00000000 :
        uint32 __match_index = 0;
        static const sint8 __match_index_array[1] = { 1, };
        __match_no = __match_index_array[__match_index];
        // last_subevent_item = 0
        }
        if (!__match_no) goto no_match_1;
        switch (__match_no)
        {
          case 1:
            CHECK_SPURIOUS_MATCH_DECL(435,spurious_match_abort_loop_0,TRACE,/*board*/card);
            UNPACK_DECL(435,TRACE,trace,/*board*/card);
            break;
        }
      }
      while (0);
      spurious_match_abort_loop_0:;
        no_match_1:;
    }
  }

  else
  {
    // if((sumchannel.trigger_type == 3))

    if ((sumchannel.trigger_type == 3))
    {
      // several UINT32 dummy NOENCODE;
      for ( ; ; ) {
      uint32  dummy;if (__buffer.empty()) goto data_done_0;
      READ_FROM_BUFFER(447,uint32 ,dummy,31);
      }
      data_done_0:;
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,FEBEX_EVENT_TRACES::__unpack,uint32 card);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for FEBEX_PADDING.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_PADDING()
template<typename __data_src_t>
void FEBEX_PADDING::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "FEBEX_PADDING",CT_OUT(NORM));
  }
  // UINT32 pads_data NOENCODE
  // {
    //  0_11: counter;
    // 12_19: index;
    // 20_31: 0xadd;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 counter : 12; // 0..11
      uint32 index : 8; // 12..19
      uint32 unnamed_20_31 : 12; // 20..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_20_31 : 12; // 20..31
      uint32 index : 8; // 12..19
      uint32 counter : 12; // 0..11
#endif
    };
    uint32  u32;
  } pads_data;
  READ_FROM_BUFFER_FULL(163,uint32 ,pads_data,pads_data.u32,33);
  CHECK_BITS_EQUAL(162,pads_data.unnamed_20_31,0xadd);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: pads_data ", CT_OUT(BOLD), pads_data.u32, CT_OUT(NORM));
    printf(".counter=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  pads_data.counter, CT_OUT(NORM));
    printf(".index=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  pads_data.index, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,FEBEX_PADDING::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TIMESTAMP_WHITERABBIT.
 *
 * Do not edit - automatically generated.
 */

// TIMESTAMP_WHITERABBIT(id)
template<typename __data_src_t>
void TIMESTAMP_WHITERABBIT::__unpack(__data_src_t &__buffer,uint32 id)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TIMESTAMP_WHITERABBIT",CT_OUT(NORM));
  }
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
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 id : 12; // 0..11
      uint32 unnamed_12_15 : 4; // 12..15
      uint32 error_bit : 1; // 16
      uint32 unnamed_17_31 : 15; // 17..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_17_31 : 15; // 17..31
      uint32 error_bit : 1; // 16
      uint32 unnamed_12_15 : 4; // 12..15
      uint32 id : 12; // 0..11
#endif
    };
    uint32  u32;
  } header;
  READ_FROM_BUFFER_FULL(24,uint32 ,header,header.u32,35);
  CHECK_BITS_EQUAL(19,header.id,id);
  CHECK_BITS_EQUAL(20,header.unnamed_12_15,0);
  CHECK_BITS_EQUAL(22,header.unnamed_17_31,0);
  {
    subsystem_id.value = header.id;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: header ", CT_OUT(BOLD), header.u32, CT_OUT(NORM));
    printf(".id=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.id, CT_OUT(NORM));
    printf(".error_bit=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.error_bit, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 d1 NOENCODE
  // {
    //  0_15: t1;
    // 16_31: 0x3e1;
    // ENCODE(t1,(value=t1));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 t1 : 16; // 0..15
      uint32 unnamed_16_31 : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_16_31 : 16; // 16..31
      uint32 t1 : 16; // 0..15
#endif
    };
    uint32  u32;
  } d1;
  READ_FROM_BUFFER_FULL(29,uint32 ,d1,d1.u32,36);
  CHECK_BITS_EQUAL(27,d1.unnamed_16_31,0x3e1);
  {
    t1.value = d1.t1;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: d1 ", CT_OUT(BOLD), d1.u32, CT_OUT(NORM));
    printf(".t1=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  d1.t1, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 d2 NOENCODE
  // {
    //  0_15: t2;
    // 16_31: 0x4e1;
    // ENCODE(t2,(value=t2));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 t2 : 16; // 0..15
      uint32 unnamed_16_31 : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_16_31 : 16; // 16..31
      uint32 t2 : 16; // 0..15
#endif
    };
    uint32  u32;
  } d2;
  READ_FROM_BUFFER_FULL(34,uint32 ,d2,d2.u32,37);
  CHECK_BITS_EQUAL(32,d2.unnamed_16_31,0x4e1);
  {
    t2.value = d2.t2;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: d2 ", CT_OUT(BOLD), d2.u32, CT_OUT(NORM));
    printf(".t2=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  d2.t2, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 d3 NOENCODE
  // {
    //  0_15: t3;
    // 16_31: 0x5e1;
    // ENCODE(t3,(value=t3));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 t3 : 16; // 0..15
      uint32 unnamed_16_31 : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_16_31 : 16; // 16..31
      uint32 t3 : 16; // 0..15
#endif
    };
    uint32  u32;
  } d3;
  READ_FROM_BUFFER_FULL(39,uint32 ,d3,d3.u32,38);
  CHECK_BITS_EQUAL(37,d3.unnamed_16_31,0x5e1);
  {
    t3.value = d3.t3;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: d3 ", CT_OUT(BOLD), d3.u32, CT_OUT(NORM));
    printf(".t3=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  d3.t3, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 d4 NOENCODE
  // {
    //  0_15: t4;
    // 16_31: 0x6e1;
    // ENCODE(t4,(value=t4));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 t4 : 16; // 0..15
      uint32 unnamed_16_31 : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_16_31 : 16; // 16..31
      uint32 t4 : 16; // 0..15
#endif
    };
    uint32  u32;
  } d4;
  READ_FROM_BUFFER_FULL(44,uint32 ,d4,d4.u32,39);
  CHECK_BITS_EQUAL(42,d4.unnamed_16_31,0x6e1);
  {
    t4.value = d4.t4;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: d4 ", CT_OUT(BOLD), d4.u32, CT_OUT(NORM));
    printf(".t4=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  d4.t4, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TIMESTAMP_WHITERABBIT::__unpack,uint32 id);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TIMESTAMP_WHITERABBIT_EXTENDED.
 *
 * Do not edit - automatically generated.
 */

// TIMESTAMP_WHITERABBIT_EXTENDED(id)
template<typename __data_src_t>
void TIMESTAMP_WHITERABBIT_EXTENDED::__unpack(__data_src_t &__buffer,uint32 id)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TIMESTAMP_WHITERABBIT_EXTENDED",CT_OUT(NORM));
  }
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
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 id : 13; // 0..12
      uint32 unnamed_13_15 : 3; // 13..15
      uint32 error_bit : 1; // 16
      uint32 unnamed_17_31 : 15; // 17..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_17_31 : 15; // 17..31
      uint32 error_bit : 1; // 16
      uint32 unnamed_13_15 : 3; // 13..15
      uint32 id : 13; // 0..12
#endif
    };
    uint32  u32;
  } header;
  READ_FROM_BUFFER_FULL(61,uint32 ,header,header.u32,41);
  CHECK_BITS_EQUAL(56,header.id,id);
  CHECK_BITS_EQUAL(57,header.unnamed_13_15,0);
  CHECK_BITS_EQUAL(59,header.unnamed_17_31,0);
  {
    subsystem_id.value = header.id;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: header ", CT_OUT(BOLD), header.u32, CT_OUT(NORM));
    printf(".id=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.id, CT_OUT(NORM));
    printf(".error_bit=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.error_bit, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 d1 NOENCODE
  // {
    //  0_15: t1;
    // 16_31: 0x3e1;
    // ENCODE(t1,(value=t1));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 t1 : 16; // 0..15
      uint32 unnamed_16_31 : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_16_31 : 16; // 16..31
      uint32 t1 : 16; // 0..15
#endif
    };
    uint32  u32;
  } d1;
  READ_FROM_BUFFER_FULL(66,uint32 ,d1,d1.u32,42);
  CHECK_BITS_EQUAL(64,d1.unnamed_16_31,0x3e1);
  {
    t1.value = d1.t1;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: d1 ", CT_OUT(BOLD), d1.u32, CT_OUT(NORM));
    printf(".t1=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  d1.t1, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 d2 NOENCODE
  // {
    //  0_15: t2;
    // 16_31: 0x4e1;
    // ENCODE(t2,(value=t2));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 t2 : 16; // 0..15
      uint32 unnamed_16_31 : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_16_31 : 16; // 16..31
      uint32 t2 : 16; // 0..15
#endif
    };
    uint32  u32;
  } d2;
  READ_FROM_BUFFER_FULL(71,uint32 ,d2,d2.u32,43);
  CHECK_BITS_EQUAL(69,d2.unnamed_16_31,0x4e1);
  {
    t2.value = d2.t2;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: d2 ", CT_OUT(BOLD), d2.u32, CT_OUT(NORM));
    printf(".t2=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  d2.t2, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 d3 NOENCODE
  // {
    //  0_15: t3;
    // 16_31: 0x5e1;
    // ENCODE(t3,(value=t3));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 t3 : 16; // 0..15
      uint32 unnamed_16_31 : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_16_31 : 16; // 16..31
      uint32 t3 : 16; // 0..15
#endif
    };
    uint32  u32;
  } d3;
  READ_FROM_BUFFER_FULL(76,uint32 ,d3,d3.u32,44);
  CHECK_BITS_EQUAL(74,d3.unnamed_16_31,0x5e1);
  {
    t3.value = d3.t3;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: d3 ", CT_OUT(BOLD), d3.u32, CT_OUT(NORM));
    printf(".t3=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  d3.t3, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 d4 NOENCODE
  // {
    //  0_15: t4;
    // 16_31: 0x6e1;
    // ENCODE(t4,(value=t4));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 t4 : 16; // 0..15
      uint32 unnamed_16_31 : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_16_31 : 16; // 16..31
      uint32 t4 : 16; // 0..15
#endif
    };
    uint32  u32;
  } d4;
  READ_FROM_BUFFER_FULL(81,uint32 ,d4,d4.u32,45);
  CHECK_BITS_EQUAL(79,d4.unnamed_16_31,0x6e1);
  {
    t4.value = d4.t4;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: d4 ", CT_OUT(BOLD), d4.u32, CT_OUT(NORM));
    printf(".t4=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  d4.t4, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TIMESTAMP_WHITERABBIT_EXTENDED::__unpack,uint32 id);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TIMESTAMP_WHITERABBIT_EXTERNAL.
 *
 * Do not edit - automatically generated.
 */

// TIMESTAMP_WHITERABBIT_EXTERNAL(id)
template<typename __data_src_t>
void TIMESTAMP_WHITERABBIT_EXTERNAL::__unpack(__data_src_t &__buffer,uint32 id)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TIMESTAMP_WHITERABBIT_EXTERNAL",CT_OUT(NORM));
  }
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
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 id : 13; // 0..12
      uint32 unnamed_13_15 : 3; // 13..15
      uint32 error_bit : 1; // 16
      uint32 unnamed_17_31 : 15; // 17..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_17_31 : 15; // 17..31
      uint32 error_bit : 1; // 16
      uint32 unnamed_13_15 : 3; // 13..15
      uint32 id : 13; // 0..12
#endif
    };
    uint32  u32;
  } header;
  READ_FROM_BUFFER_FULL(112,uint32 ,header,header.u32,47);
  CHECK_BITS_EQUAL(107,header.id,id);
  CHECK_BITS_EQUAL(108,header.unnamed_13_15,0);
  CHECK_BITS_EQUAL(110,header.unnamed_17_31,0);
  {
    subsystem_id.value = header.id;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: header ", CT_OUT(BOLD), header.u32, CT_OUT(NORM));
    printf(".id=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.id, CT_OUT(NORM));
    printf(".error_bit=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.error_bit, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 rn NOENCODE
  // {
    //  0_31: run;
    // ENCODE(run,(value=run));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 run : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 run : 32; // 0..31
#endif
    };
    uint32  u32;
  } rn;
  READ_FROM_BUFFER_FULL(116,uint32 ,rn,rn.u32,48);
  {
    run.value = rn.run;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: rn ", CT_OUT(BOLD), rn.u32, CT_OUT(NORM));
    printf(".run=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  rn.run, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 d1 NOENCODE
  // {
    //  0_31: t1;
    // ENCODE(t1,(value=t1));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 t1 : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 t1 : 32; // 0..31
#endif
    };
    uint32  u32;
  } d1;
  READ_FROM_BUFFER_FULL(120,uint32 ,d1,d1.u32,49);
  {
    t1.value = d1.t1;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: d1 ", CT_OUT(BOLD), d1.u32, CT_OUT(NORM));
    printf(".t1=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  d1.t1, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 d2 NOENCODE
  // {
    //  0_31: t2;
    // ENCODE(t2,(value=t2));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 t2 : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 t2 : 32; // 0..31
#endif
    };
    uint32  u32;
  } d2;
  READ_FROM_BUFFER_FULL(124,uint32 ,d2,d2.u32,50);
  {
    t2.value = d2.t2;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: d2 ", CT_OUT(BOLD), d2.u32, CT_OUT(NORM));
    printf(".t2=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  d2.t2, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TIMESTAMP_WHITERABBIT_EXTERNAL::__unpack,uint32 id);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for WR_MULTI.
 *
 * Do not edit - automatically generated.
 */

// WR_MULTI()
template<typename __data_src_t>
void WR_MULTI::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "WR_MULTI",CT_OUT(NORM));
  }
  // MEMBER(DATA32 time_hi);
  // MEMBER(DATA32 time_lo);
  // UINT32 hi NOENCODE
  // {
    //  0_31: time;
    // ENCODE(time_hi,(value=time));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 time : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 time : 32; // 0..31
#endif
    };
    uint32  u32;
  } hi;
  READ_FROM_BUFFER_FULL(92,uint32 ,hi,hi.u32,52);
  {
    time_hi.value = hi.time;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: hi ", CT_OUT(BOLD), hi.u32, CT_OUT(NORM));
    printf(".time=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  hi.time, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 lo NOENCODE
  // {
    //  0_31: time;
    // ENCODE(time_lo,(value=time));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 time : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 time : 32; // 0..31
#endif
    };
    uint32  u32;
  } lo;
  READ_FROM_BUFFER_FULL(96,uint32 ,lo,lo.u32,53);
  {
    time_lo.value = lo.time;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: lo ", CT_OUT(BOLD), lo.u32, CT_OUT(NORM));
    printf(".time=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  lo.time, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,WR_MULTI::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for febex_subev_traces.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(febex_subev_traces)
template<typename __data_src_t>
void febex_subev_traces::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_MAGENTA),  "febex_subev_traces",CT_OUT(NORM));
  }
  // select several

    // badevent = BAD_EVENT();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: BAD_EVENT badevent: (s32) => (0xffffffff,0xbad00bad)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(460,uint32,__match_peek);
    // differ = 00000000 :
    uint32 __match_index = 0;
    static const sint8 __match_index_array[1] = { 1, };
    __match_no = __match_index_array[__match_index];
    // last_subevent_item = 0
    }
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        CHECK_SPURIOUS_MATCH_DECL(459,spurious_match_abort_loop_1,BAD_EVENT);
        UNPACK_DECL(459,BAD_EVENT,badevent);
        break;
    }
  }
  spurious_match_abort_loop_1:;
  // select optional

    // ts = TIMESTAMP_WHITERABBIT_EXTERNAL(id=0x300);
  do
  {
    if (__buffer.empty()) goto no_match_2;
    int __match_no = 0;
    // optimized match 1: TIMESTAMP_WHITERABBIT_EXTERNAL ts: (s32) => (0xfffeffff,0x00000300)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(465,uint32,__match_peek);
    // differ = 00000000 :
    uint32 __match_index = 0;
    static const sint8 __match_index_array[1] = { 1, };
    __match_no = __match_index_array[__match_index];
    // last_subevent_item = 0
    }
    if (!__match_no) goto no_match_2;
    switch (__match_no)
    {
      case 1:
        CHECK_SPURIOUS_MATCH_DECL(464,spurious_match_abort_loop_2,TIMESTAMP_WHITERABBIT_EXTERNAL,/*id*/0x300);
        UNPACK_DECL(464,TIMESTAMP_WHITERABBIT_EXTERNAL,ts,/*id*/0x300);
        break;
    }
  }
  while (0);
  spurious_match_abort_loop_2:;
    no_match_2:;
  // select several

    // padding = FEBEX_PADDING();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: FEBEX_PADDING padding: (s32) => (0xfff00000,0xadd00000)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(470,uint32,__match_peek);
    // differ = 00000000 :
    uint32 __match_index = 0;
    static const sint8 __match_index_array[1] = { 1, };
    __match_no = __match_index_array[__match_index];
    // last_subevent_item = 0
    }
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        CHECK_SPURIOUS_MATCH_DECL(469,spurious_match_abort_loop_3,FEBEX_PADDING);
        UNPACK_DECL(469,FEBEX_PADDING,padding);
        break;
    }
  }
  spurious_match_abort_loop_3:;
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
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: FEBEX_EVENT_TRACES data[0]: (s32) => (0xffff00ff,0xff000034)
    // optimized match 2: FEBEX_EVENT_TRACES data[1]: (s32) => (0xffff00ff,0xff010034)
    // optimized match 3: FEBEX_EVENT_TRACES data[2]: (s32) => (0xffff00ff,0xff020034)
    // optimized match 4: FEBEX_EVENT_TRACES data[3]: (s32) => (0xffff00ff,0xff030034)
    // optimized match 5: FEBEX_EVENT_TRACES data[4]: (s32) => (0xffff00ff,0xff040034)
    // optimized match 6: FEBEX_EVENT_TRACES data[5]: (s32) => (0xffff00ff,0xff050034)
    // optimized match 7: FEBEX_EVENT_TRACES data[6]: (s32) => (0xffff00ff,0xff060034)
    // optimized match 8: FEBEX_EVENT_TRACES data[7]: (s32) => (0xffff00ff,0xff070034)
    // optimized match 9: FEBEX_EVENT_TRACES data[8]: (s32) => (0xffff00ff,0xff080034)
    // optimized match 10: FEBEX_EVENT_TRACES data[9]: (s32) => (0xffff00ff,0xff090034)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(485,uint32,__match_peek);
    // differ = 000f0000 : 16 17 18 19
    uint32 __match_index = 0 | /* 16,19 */ ((__match_peek >> 16) & 0x0000000f);
    static const sint8 __match_index_array[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 0, 0, 0, 0, 0, };
    __match_no = __match_index_array[__match_index];
    // last_subevent_item = 1
    }
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        UNPACK_DECL(475,FEBEX_EVENT_TRACES,data[0],/*card*/0);
        break;
      case 2:
        UNPACK_DECL(476,FEBEX_EVENT_TRACES,data[1],/*card*/1);
        break;
      case 3:
        UNPACK_DECL(477,FEBEX_EVENT_TRACES,data[2],/*card*/2);
        break;
      case 4:
        UNPACK_DECL(478,FEBEX_EVENT_TRACES,data[3],/*card*/3);
        break;
      case 5:
        UNPACK_DECL(479,FEBEX_EVENT_TRACES,data[4],/*card*/4);
        break;
      case 6:
        UNPACK_DECL(480,FEBEX_EVENT_TRACES,data[5],/*card*/5);
        break;
      case 7:
        UNPACK_DECL(481,FEBEX_EVENT_TRACES,data[6],/*card*/6);
        break;
      case 8:
        UNPACK_DECL(482,FEBEX_EVENT_TRACES,data[7],/*card*/7);
        break;
      case 9:
        UNPACK_DECL(483,FEBEX_EVENT_TRACES,data[8],/*card*/8);
        break;
      case 10:
        UNPACK_DECL(484,FEBEX_EVENT_TRACES,data[9],/*card*/9);
        break;
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,febex_subev_traces::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for EVENT.
 *
 * Do not edit - automatically generated.
 */

// EVENT
template<typename __data_src_t>
int unpack_event::__unpack_subevent(subevent_header *__header,__data_src_t &__buffer)
  // lisa = febex_subev_traces(procid=60);
  // ignore_unknown_subevent;
{
  int __match_no = 0;
  MATCH_SUBEVENT_DECL(491,__match_no,1,((VES10_1_procid==60)),lisa);
  if (!__match_no) return 0;
  switch (__match_no)
  {
    case 1:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(491,febex_subev_traces,lisa,0);
      UNPACK_SUBEVENT_DECL(491,0,febex_subev_traces,lisa);
      break;
  }
  return 0;
}
FORCE_IMPL_DATA_SRC_FCN_HDR(int,unpack_event::__unpack_subevent);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for EVENT.
 *
 * Do not edit - automatically generated.
 */

// STICKY_EVENT
template<typename __data_src_t>
int unpack_sticky_event::__unpack_subevent(subevent_header *__header,__data_src_t &__buffer)
{
  int __match_no = 0;
  if (!__match_no) return 0;
  switch (__match_no)
  {
  }
  return 0;
}
FORCE_IMPL_DATA_SRC_FCN_HDR(int,unpack_sticky_event::__unpack_subevent);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER_DEFINES *********************************************
 *
 * Control
 *
 * Do not edit - automatically generated.
 */

#define STICKY_EVENT_IS_NONTRIVIAL  0


/** END_UNPACKER_DEFINES **********************************************/
