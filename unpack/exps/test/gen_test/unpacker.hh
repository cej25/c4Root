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
  READ_FROM_BUFFER_FULL(720,uint32 ,be,be.u32,0);
  CHECK_BITS_EQUAL(719,be.b,0xbad00bad);
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
  uint32  no;READ_FROM_BUFFER(727,uint32 ,no,2);
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
  READ_FROM_BUFFER_FULL(145,uint32 ,sumchannel,sumchannel.u32,4);
  CHECK_BITS_EQUAL(139,sumchannel.unnamed_0_7,52);
  CHECK_BITS_EQUAL(142,sumchannel.card,card);
  CHECK_BITS_EQUAL(143,sumchannel.unnamed_24_31,255);
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
  READ_FROM_BUFFER_FULL(153,uint32 ,channel_size,channel_size.u32,5);
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
  READ_FROM_BUFFER_FULL(162,uint32 ,event_timestamp_hi,event_timestamp_hi.u32,6);
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
  READ_FROM_BUFFER_FULL(168,uint32 ,event_timestamp_lo,event_timestamp_lo.u32,7);
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
  READ_FROM_BUFFER_FULL(176,uint32 ,hp,hp.u32,8);
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
  READ_FROM_BUFFER_FULL(181,uint32 ,deadbeef,deadbeef.u32,9);
  CHECK_BITS_EQUAL(180,deadbeef.unnamed_0_31,0xdeadbeef);
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
    READ_FROM_BUFFER_FULL(192,uint32 ,channelids,channelids.u32,10);
    CHECK_BITS_EQUAL(188,channelids.unnamed_24_31,240);
    {
      typedef __typeof__(*(&(channel_trigger_time_hi))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = channel_trigger_time_hi.insert_index(191,channelids.channel_id_bits);
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
    READ_FROM_BUFFER_FULL(197,uint32 ,channel_ts,channel_ts.u32,11);
    {
      typedef __typeof__(*(&(channel_trigger_time_lo))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = channel_trigger_time_lo.insert_index(196,channelids.channel_id_bits);
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
    READ_FROM_BUFFER_FULL(209,uint32 ,chan_enrgy,chan_enrgy.u32,12);
    {
      {
        typedef __typeof__(*(&(channel_cfd))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_cfd.insert_index(205,channelids.channel_id_bits);
        __item.value = chan_enrgy.TSF;
      }
      {
        typedef __typeof__(*(&(channel_energy))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_energy.insert_index(206,channelids.channel_id_bits);
        __item.value = chan_enrgy.chan_energy;
      }
      {
        typedef __typeof__(*(&(pileup))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = pileup.insert_index(207,channelids.channel_id_bits);
        __item.value = chan_enrgy.pileup_flag;
      }
      {
        typedef __typeof__(*(&(overflow))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = overflow.insert_index(208,channelids.channel_id_bits);
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
    READ_FROM_BUFFER_FULL(213,uint32 ,future_use,future_use.u32,13);
    CHECK_BITS_EQUAL(212,future_use.unnamed_0_31,0);
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
  // MEMBER(DATA8 pileup[16]);
  // MEMBER(DATA8 overflow[16]);
  // MEMBER(DATA8 channel_cfd[16] ZERO_SUPPRESS);
  // MEMBER(DATA32 channel_energy[16] ZERO_SUPPRESS);
  // MEMBER(DATA16 traces[16][4000] ZERO_SUPPRESS);
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
  READ_FROM_BUFFER_FULL(247,uint32 ,sumchannel,sumchannel.u32,15);
  CHECK_BITS_EQUAL(240,sumchannel.unnamed_0_7,52);
  CHECK_BITS_EQUAL(243,sumchannel.board_id,card);
  CHECK_BITS_EQUAL(244,sumchannel.unnamed_24_31,255);
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
  READ_FROM_BUFFER_FULL(257,uint32 ,channel_size,channel_size.u32,16);
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
  READ_FROM_BUFFER_FULL(266,uint32 ,event_timestamp_hi,event_timestamp_hi.u32,17);
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
  READ_FROM_BUFFER_FULL(272,uint32 ,event_timestamp_lo,event_timestamp_lo.u32,18);
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
  READ_FROM_BUFFER_FULL(280,uint32 ,hp,hp.u32,19);
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
  READ_FROM_BUFFER_FULL(285,uint32 ,deadbeef,deadbeef.u32,20);
  CHECK_BITS_EQUAL(284,deadbeef.unnamed_0_31,0xdeadbeef);
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
        // ENCODE(channel_id[index],(value=channel_id_bits));
        // ENCODE(channel_trigger_time_hi[index],(value=chan_ts_hi));
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
      READ_FROM_BUFFER_FULL(299,uint32 ,channelids,channelids.u32,21);
      CHECK_BITS_EQUAL(295,channelids.unnamed_24_31,240);
      {
        {
          typedef __typeof__(*(&(channel_id))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_id.insert_index(297,index);
          __item.value = channelids.channel_id_bits;
        }
        {
          typedef __typeof__(*(&(channel_trigger_time_hi))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_trigger_time_hi.insert_index(298,index);
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
        // ENCODE(channel_trigger_time_lo[index],(value=chan_ts_lo));
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
      READ_FROM_BUFFER_FULL(304,uint32 ,channel_ts,channel_ts.u32,22);
      {
        typedef __typeof__(*(&(channel_trigger_time_lo))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_trigger_time_lo.insert_index(303,index);
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
        // ENCODE(channel_cfd[index],(value=TSF));
        // ENCODE(channel_energy[index],(value=chan_energy));
        // ENCODE(pileup[index],(value=pileup_flag));
        // ENCODE(overflow[index],(value=overflow_flag));
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
      READ_FROM_BUFFER_FULL(316,uint32 ,chan_enrgy,chan_enrgy.u32,23);
      {
        {
          typedef __typeof__(*(&(channel_cfd))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_cfd.insert_index(312,index);
          __item.value = chan_enrgy.TSF;
        }
        {
          typedef __typeof__(*(&(channel_energy))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_energy.insert_index(313,index);
          __item.value = chan_enrgy.chan_energy;
        }
        {
          typedef __typeof__(*(&(pileup))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = pileup.insert_index(314,index);
          __item.value = chan_enrgy.pileup_flag;
        }
        {
          typedef __typeof__(*(&(overflow))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = overflow.insert_index(315,index);
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
      READ_FROM_BUFFER_FULL(320,uint32 ,future_use,future_use.u32,24);
      CHECK_BITS_EQUAL(319,future_use.unnamed_0_31,0);
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: future_use ", CT_OUT(BOLD), future_use.u32, CT_OUT(NORM));
        printf("\n");
      }
    }
    // list(0<=i<((channel_size.size / 4) - 1))

    for (uint32 i = 0; i < (uint32) (((channel_size.size / 4) - 1)); ++i)
    {
      // UINT32 header NOENCODE
      // {
        //  0_07: 52;
        //  8_23: other;
        // 24_31: ch_id;
      // }
      union
      {
        struct
        {
#if __BYTE_ORDER == __LITTLE_ENDIAN
          uint32 unnamed_0_7 : 8; // 0..7
          uint32 other : 16; // 8..23
          uint32 ch_id : 8; // 24..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
          uint32 ch_id : 8; // 24..31
          uint32 other : 16; // 8..23
          uint32 unnamed_0_7 : 8; // 0..7
#endif
        };
        uint32  u32;
      } header;
      READ_FROM_BUFFER_FULL(330,uint32 ,header,header.u32,25);
      CHECK_BITS_EQUAL(327,header.unnamed_0_7,52);
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: header ", CT_OUT(BOLD), header.u32, CT_OUT(NORM));
        printf(".other=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.other, CT_OUT(NORM));
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
      READ_FROM_BUFFER_FULL(335,uint32 ,tracesize,tracesize.u32,26);
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
      READ_FROM_BUFFER_FULL(341,uint32 ,tracehead,tracehead.u32,27);
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
        READ_FROM_BUFFER_FULL(361,uint32 ,channel_trace,channel_trace.u32,28);
        {
          {
            typedef __typeof__(*(&(traces[header.ch_id]))) __array_t;
            typedef typename __array_t::item_t __item_t;
            __item_t &__item = traces[header.ch_id].insert_index(359,((2 * j) + 0));
            __item.value = channel_trace.data1;
          }
          {
            typedef __typeof__(*(&(traces[header.ch_id]))) __array_t;
            typedef typename __array_t::item_t __item_t;
            __item_t &__item = traces[header.ch_id].insert_index(360,((2 * j) + 1));
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
      READ_FROM_BUFFER_FULL(370,uint32 ,trace_trailer,trace_trailer.u32,29);
      CHECK_BITS_RANGE(369,trace_trailer.id,176,191);
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: trace_trailer ", CT_OUT(BOLD), trace_trailer.u32, CT_OUT(NORM));
        printf(".notused=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trace_trailer.notused, CT_OUT(NORM));
        printf(".id=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trace_trailer.id, CT_OUT(NORM));
        printf("\n");
      }
    }
  }

  else
  {
    // if((sumchannel.trigger_type == 3))

    if ((sumchannel.trigger_type == 3))
    {
      // select several

        // dummy = DUMMY();
      for ( ; ; )
      {
        if (__buffer.empty()) break;
        int __match_no = 0;
        // optimized match 1: DUMMY dummy: (s32)
        {
        uint32 __match_peek;
        PEEK_FROM_BUFFER(379,uint32,__match_peek);
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
            CHECK_SPURIOUS_MATCH_DECL(378,spurious_match_abort_loop_0,DUMMY);
            UNPACK_DECL(378,DUMMY,dummy);
            break;
        }
      }
      spurious_match_abort_loop_0:;
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
  READ_FROM_BUFFER_FULL(117,uint32 ,pads_data,pads_data.u32,31);
  CHECK_BITS_EQUAL(116,pads_data.unnamed_20_31,0xadd);
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
 * Event unpacker for TAMEX4_EPOCH_DATA.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_EPOCH_DATA(sfp,card,time_coarse,time_fine,time_edge,time_channel,
                  // time_epoch)
template<typename __data_src_t>
void TAMEX4_EPOCH_DATA::__unpack(__data_src_t &__buffer,uint32 sfp,uint32 card
                                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_coarse
                                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_fine
                                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_edge
                                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_channel
                                                       ,raw_list_ii_zero_suppress<DATA32,DATA32,1024> &time_epoch)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TAMEX4_EPOCH_DATA",CT_OUT(NORM));
  }
  // MEMBER(DATA12 time_coarse[1024] NO_INDEX_LIST);
  // MEMBER(DATA12 time_fine[1024] NO_INDEX_LIST);
  // MEMBER(DATA12 time_edge[1024] NO_INDEX_LIST);
  // MEMBER(DATA12 time_channel[1024] NO_INDEX_LIST);
  // MEMBER(DATA32 time_epoch[1024] NO_INDEX_LIST);
  // UINT32 data NOENCODE
  // {
    //  0_27: epoch;
    // 28_31: 6;
    // ENCODE(time_coarse APPEND_LIST,(value=0));
    // ENCODE(time_fine APPEND_LIST,(value=0));
    // ENCODE(time_edge APPEND_LIST,(value=0));
    // ENCODE(time_channel APPEND_LIST,(value=0));
    // ENCODE(time_epoch APPEND_LIST,(value=epoch));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 epoch : 28; // 0..27
      uint32 unnamed_28_31 : 4; // 28..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_28_31 : 4; // 28..31
      uint32 epoch : 28; // 0..27
#endif
    };
    uint32  u32;
  } data;
  READ_FROM_BUFFER_FULL(456,uint32 ,data,data.u32,33);
  CHECK_BITS_EQUAL(449,data.unnamed_28_31,6);
  {
    {
      typedef __typeof__(*(&(time_coarse))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_coarse.append_item(451);
      __item.value = 0;
    }
    {
      typedef __typeof__(*(&(time_fine))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_fine.append_item(452);
      __item.value = 0;
    }
    {
      typedef __typeof__(*(&(time_edge))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_edge.append_item(453);
      __item.value = 0;
    }
    {
      typedef __typeof__(*(&(time_channel))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_channel.append_item(454);
      __item.value = 0;
    }
    {
      typedef __typeof__(*(&(time_epoch))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_epoch.append_item(455);
      __item.value = data.epoch;
    }
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: data ", CT_OUT(BOLD), data.u32, CT_OUT(NORM));
    printf(".epoch=%s%7" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  data.epoch, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TAMEX4_EPOCH_DATA::__unpack,uint32 sfp,uint32 card
                                                            ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_coarse
                                                            ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_fine
                                                            ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_edge
                                                            ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_channel
                                                            ,raw_list_ii_zero_suppress<DATA32,DATA32,1024> &time_epoch);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TAMEX4_HEADER.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_HEADER()
template<typename __data_src_t>
void TAMEX4_HEADER::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TAMEX4_HEADER",CT_OUT(NORM));
  }
  // MEMBER(DATA16 post_trig_ns);
  // MEMBER(DATA16 pre_trig_ns);
  // UINT32 trigger_window NOENCODE
  // {
    //  0_15: post_trig_ns;
    // 16_31: pre_trig_ns;
    // ENCODE(post_trig_ns,(value=post_trig_ns));
    // ENCODE(pre_trig_ns,(value=pre_trig_ns));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 post_trig_ns : 16; // 0..15
      uint32 pre_trig_ns : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 pre_trig_ns : 16; // 16..31
      uint32 post_trig_ns : 16; // 0..15
#endif
    };
    uint32  u32;
  } trigger_window;
  READ_FROM_BUFFER_FULL(398,uint32 ,trigger_window,trigger_window.u32,35);
  {
    {
      post_trig_ns.value = trigger_window.post_trig_ns;
    }
    {
      pre_trig_ns.value = trigger_window.pre_trig_ns;
    }
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: trigger_window ", CT_OUT(BOLD), trigger_window.u32, CT_OUT(NORM));
    printf(".post_trig_ns=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trigger_window.post_trig_ns, CT_OUT(NORM));
    printf(".pre_trig_ns=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trigger_window.pre_trig_ns, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,TAMEX4_HEADER::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TAMEX4_PADDING.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_PADDING()
template<typename __data_src_t>
void TAMEX4_PADDING::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TAMEX4_PADDING",CT_OUT(NORM));
  }
  // UINT32 padding NOENCODE
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
  } padding;
  READ_FROM_BUFFER_FULL(409,uint32 ,padding,padding.u32,37);
  CHECK_BITS_EQUAL(408,padding.unnamed_20_31,0xadd);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: padding ", CT_OUT(BOLD), padding.u32, CT_OUT(NORM));
    printf(".counter=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  padding.counter, CT_OUT(NORM));
    printf(".index=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  padding.index, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,TAMEX4_PADDING::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TAMEX4_TIME_DATA.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_TIME_DATA(sfp,card,time_coarse,time_fine,time_edge,time_channel,
                 // time_epoch)
template<typename __data_src_t>
void TAMEX4_TIME_DATA::__unpack(__data_src_t &__buffer,uint32 sfp,uint32 card
                                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_coarse
                                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_fine
                                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_edge
                                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_channel
                                                      ,raw_list_ii_zero_suppress<DATA32,DATA32,1024> &time_epoch)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TAMEX4_TIME_DATA",CT_OUT(NORM));
  }
  // MEMBER(DATA12 time_coarse[1024] NO_INDEX_LIST);
  // MEMBER(DATA12 time_fine[1024] NO_INDEX_LIST);
  // MEMBER(DATA12 time_edge[1024] NO_INDEX_LIST);
  // MEMBER(DATA12 time_channel[1024] NO_INDEX_LIST);
  // MEMBER(DATA32 time_epoch[1024] NO_INDEX_LIST);
  // UINT32 data NOENCODE
  // {
    //  0_10: coarse;
    //    11: is_leading;
    // 12_21: fine;
    // 22_27: channel;
    // 28_31: type = CHECK(8);
    // ENCODE(time_coarse APPEND_LIST,(value=coarse));
    // ENCODE(time_fine APPEND_LIST,(value=fine));
    // ENCODE(time_edge APPEND_LIST,(value=is_leading));
    // ENCODE(time_channel APPEND_LIST,(value=channel));
    // ENCODE(time_epoch APPEND_LIST,(value=0));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 coarse : 11; // 0..10
      uint32 is_leading : 1; // 11
      uint32 fine : 10; // 12..21
      uint32 channel : 6; // 22..27
      uint32 type : 4; // 28..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 type : 4; // 28..31
      uint32 channel : 6; // 22..27
      uint32 fine : 10; // 12..21
      uint32 is_leading : 1; // 11
      uint32 coarse : 11; // 0..10
#endif
    };
    uint32  u32;
  } data;
  READ_FROM_BUFFER_FULL(434,uint32 ,data,data.u32,39);
  CHECK_BITS_EQUAL(427,data.type,8);
  {
    {
      typedef __typeof__(*(&(time_coarse))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_coarse.append_item(429);
      __item.value = data.coarse;
    }
    {
      typedef __typeof__(*(&(time_fine))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_fine.append_item(430);
      __item.value = data.fine;
    }
    {
      typedef __typeof__(*(&(time_edge))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_edge.append_item(431);
      __item.value = data.is_leading;
    }
    {
      typedef __typeof__(*(&(time_channel))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_channel.append_item(432);
      __item.value = data.channel;
    }
    {
      typedef __typeof__(*(&(time_epoch))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_epoch.append_item(433);
      __item.value = 0;
    }
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: data ", CT_OUT(BOLD), data.u32, CT_OUT(NORM));
    printf(".coarse=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  data.coarse, CT_OUT(NORM));
    printf(".is_leading=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  data.is_leading, CT_OUT(NORM));
    printf(".fine=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  data.fine, CT_OUT(NORM));
    printf(".channel=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  data.channel, CT_OUT(NORM));
    printf(".type=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  data.type, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TAMEX4_TIME_DATA::__unpack,uint32 sfp,uint32 card
                                                           ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_coarse
                                                           ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_fine
                                                           ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_edge
                                                           ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_channel
                                                           ,raw_list_ii_zero_suppress<DATA32,DATA32,1024> &time_epoch);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TAMEX4_SFP.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_SFP(sfp,card)
template<typename __data_src_t>
void TAMEX4_SFP::__unpack(__data_src_t &__buffer,uint32 sfp,uint32 card)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TAMEX4_SFP",CT_OUT(NORM));
  }
  // MEMBER(DATA16 trig);
  // MEMBER(DATA32 event_size);
  // MEMBER(DATA12 time_coarse[1024] NO_INDEX_LIST);
  // MEMBER(DATA12 time_fine[1024] NO_INDEX_LIST);
  // MEMBER(DATA12 time_edge[1024] NO_INDEX_LIST);
  // MEMBER(DATA12 time_channel[1024] NO_INDEX_LIST);
  // MEMBER(DATA32 time_epoch[1024] NO_INDEX_LIST);
  // UINT32 indicator NOENCODE
  // {
    //  0_07: 52;
    //  8_11: trigger_type;
    // 12_15: sfp = MATCH(sfp);
    // 16_23: card = MATCH(card);
    // 24_31: 0;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 unnamed_0_7 : 8; // 0..7
      uint32 trigger_type : 4; // 8..11
      uint32 sfp : 4; // 12..15
      uint32 card : 8; // 16..23
      uint32 unnamed_24_31 : 8; // 24..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_24_31 : 8; // 24..31
      uint32 card : 8; // 16..23
      uint32 sfp : 4; // 12..15
      uint32 trigger_type : 4; // 8..11
      uint32 unnamed_0_7 : 8; // 0..7
#endif
    };
    uint32  u32;
  } indicator;
  READ_FROM_BUFFER_FULL(478,uint32 ,indicator,indicator.u32,41);
  CHECK_BITS_EQUAL(472,indicator.unnamed_0_7,52);
  CHECK_BITS_EQUAL(474,indicator.sfp,sfp);
  CHECK_BITS_EQUAL(475,indicator.card,card);
  CHECK_BITS_EQUAL(476,indicator.unnamed_24_31,0);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: indicator ", CT_OUT(BOLD), indicator.u32, CT_OUT(NORM));
    printf(".trigger_type=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  indicator.trigger_type, CT_OUT(NORM));
    printf(".sfp=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  indicator.sfp, CT_OUT(NORM));
    printf(".card=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  indicator.card, CT_OUT(NORM));
    printf("\n");
  }
  // MATCH_END;
  // UINT32 data_size NOENCODE
  // {
    //  0_31: bytes;
    // ENCODE(event_size,(value=bytes));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 bytes : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 bytes : 32; // 0..31
#endif
    };
    uint32  u32;
  } data_size;
  READ_FROM_BUFFER_FULL(488,uint32 ,data_size,data_size.u32,42);
  {
    event_size.value = data_size.bytes;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: data_size ", CT_OUT(BOLD), data_size.u32, CT_OUT(NORM));
    printf(".bytes=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  data_size.bytes, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 tdc_header NOENCODE
  // {
    //  0_15: lec;
    //    16: buf_no;
    // 17_19: reserved;
    // 20_23: trigger_type;
    // 24_31: 170;
    // ENCODE(trig,(value=trigger_type));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 lec : 16; // 0..15
      uint32 buf_no : 1; // 16
      uint32 reserved : 3; // 17..19
      uint32 trigger_type : 4; // 20..23
      uint32 unnamed_24_31 : 8; // 24..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_24_31 : 8; // 24..31
      uint32 trigger_type : 4; // 20..23
      uint32 reserved : 3; // 17..19
      uint32 buf_no : 1; // 16
      uint32 lec : 16; // 0..15
#endif
    };
    uint32  u32;
  } tdc_header;
  READ_FROM_BUFFER_FULL(497,uint32 ,tdc_header,tdc_header.u32,43);
  CHECK_BITS_EQUAL(495,tdc_header.unnamed_24_31,170);
  {
    trig.value = tdc_header.trigger_type;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: tdc_header ", CT_OUT(BOLD), tdc_header.u32, CT_OUT(NORM));
    printf(".lec=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_header.lec, CT_OUT(NORM));
    printf(".buf_no=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_header.buf_no, CT_OUT(NORM));
    printf(".reserved=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_header.reserved, CT_OUT(NORM));
    printf(".trigger_type=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_header.trigger_type, CT_OUT(NORM));
    printf("\n");
  }
  // list(0<=i<((data_size.bytes / 4) - 3))

  for (uint32 i = 0; i < (uint32) (((data_size.bytes / 4) - 3)); ++i)
  {
    // select

      // epoch = TAMEX4_EPOCH_DATA(sfp=sfp,card=card,time_coarse=time_coarse,
                                // time_fine=time_fine,time_edge=time_edge,
                                // time_channel=time_channel,time_epoch=time_epoch);
      // time = TAMEX4_TIME_DATA(sfp=sfp,card=card,time_coarse=time_coarse,
                              // time_fine=time_fine,time_edge=time_edge,
                              // time_channel=time_channel,time_epoch=time_epoch);
    do
    {
      int __match_no = 0;
      // optimized match 1: TAMEX4_EPOCH_DATA epoch: (s32) => (0xf0000000,0x60000000)
      // optimized match 2: TAMEX4_TIME_DATA time: (s32) => (0xf0000000,0x80000000)
      {
      uint32 __match_peek;
      PEEK_FROM_BUFFER(505,uint32,__match_peek);
      // differ = e0000000 : 29 30 31
      uint32 __match_index = 0 | /* 29,31 */ ((__match_peek >> 29) & 0x00000007);
      static const sint8 __match_index_array[8] = { 0, 0, 0, 1, 2, 0, 0, 0, };
      __match_no = __match_index_array[__match_index];
      // last_subevent_item = 0
      }
      if (!__match_no) ERROR_U_LOC(505,"No match for select statement.");
      switch (__match_no)
      {
        case 1:
          CHECK_SPURIOUS_MATCH_DECL(503,spurious_match_abort_loop_1,TAMEX4_EPOCH_DATA,/*sfp*/sfp,/*card*/card/*,time_coarse:member*//*,time_fine:member*//*,time_edge:member*//*,time_channel:member*//*,time_epoch:member*/);
          UNPACK_DECL(503,TAMEX4_EPOCH_DATA,epoch,/*sfp*/sfp,/*card*/card,/*time_coarse*/time_coarse,/*time_fine*/time_fine,/*time_edge*/time_edge,/*time_channel*/time_channel,/*time_epoch*/time_epoch);
          break;
        case 2:
          CHECK_SPURIOUS_MATCH_DECL(504,spurious_match_abort_loop_1,TAMEX4_TIME_DATA,/*sfp*/sfp,/*card*/card/*,time_coarse:member*//*,time_fine:member*//*,time_edge:member*//*,time_channel:member*//*,time_epoch:member*/);
          UNPACK_DECL(504,TAMEX4_TIME_DATA,time,/*sfp*/sfp,/*card*/card,/*time_coarse*/time_coarse,/*time_fine*/time_fine,/*time_edge*/time_edge,/*time_channel*/time_channel,/*time_epoch*/time_epoch);
          break;
      }
    }
    while (0);
    spurious_match_abort_loop_1:;
  }
  // UINT32 error_bits NOENCODE
  // {
    //  0_23: bits;
    // 24_31: 238;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 bits : 24; // 0..23
      uint32 unnamed_24_31 : 8; // 24..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_24_31 : 8; // 24..31
      uint32 bits : 24; // 0..23
#endif
    };
    uint32  u32;
  } error_bits;
  READ_FROM_BUFFER_FULL(512,uint32 ,error_bits,error_bits.u32,44);
  CHECK_BITS_EQUAL(511,error_bits.unnamed_24_31,238);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: error_bits ", CT_OUT(BOLD), error_bits.u32, CT_OUT(NORM));
    printf(".bits=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  error_bits.bits, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 trailer NOENCODE
  // {
    //  0_15: lec;
    //    16: buf_no;
    // 17_19: reserved;
    // 20_23: trigger_type;
    // 24_31: 187;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 lec : 16; // 0..15
      uint32 buf_no : 1; // 16
      uint32 reserved : 3; // 17..19
      uint32 trigger_type : 4; // 20..23
      uint32 unnamed_24_31 : 8; // 24..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_24_31 : 8; // 24..31
      uint32 trigger_type : 4; // 20..23
      uint32 reserved : 3; // 17..19
      uint32 buf_no : 1; // 16
      uint32 lec : 16; // 0..15
#endif
    };
    uint32  u32;
  } trailer;
  READ_FROM_BUFFER_FULL(521,uint32 ,trailer,trailer.u32,45);
  CHECK_BITS_EQUAL(520,trailer.unnamed_24_31,187);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: trailer ", CT_OUT(BOLD), trailer.u32, CT_OUT(NORM));
    printf(".lec=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.lec, CT_OUT(NORM));
    printf(".buf_no=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.buf_no, CT_OUT(NORM));
    printf(".reserved=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.reserved, CT_OUT(NORM));
    printf(".trigger_type=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.trigger_type, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TAMEX4_SFP::__unpack,uint32 sfp,uint32 card);

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
  READ_FROM_BUFFER_FULL(30,uint32 ,header,header.u32,47);
  CHECK_BITS_EQUAL(25,header.id,id);
  CHECK_BITS_EQUAL(26,header.unnamed_12_15,0);
  CHECK_BITS_EQUAL(28,header.unnamed_17_31,0);
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
  READ_FROM_BUFFER_FULL(35,uint32 ,d1,d1.u32,48);
  CHECK_BITS_EQUAL(33,d1.unnamed_16_31,0x3e1);
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
  READ_FROM_BUFFER_FULL(40,uint32 ,d2,d2.u32,49);
  CHECK_BITS_EQUAL(38,d2.unnamed_16_31,0x4e1);
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
  READ_FROM_BUFFER_FULL(45,uint32 ,d3,d3.u32,50);
  CHECK_BITS_EQUAL(43,d3.unnamed_16_31,0x5e1);
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
  READ_FROM_BUFFER_FULL(50,uint32 ,d4,d4.u32,51);
  CHECK_BITS_EQUAL(48,d4.unnamed_16_31,0x6e1);
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
  READ_FROM_BUFFER_FULL(67,uint32 ,header,header.u32,53);
  CHECK_BITS_EQUAL(62,header.id,id);
  CHECK_BITS_EQUAL(63,header.unnamed_13_15,0);
  CHECK_BITS_EQUAL(65,header.unnamed_17_31,0);
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
  READ_FROM_BUFFER_FULL(72,uint32 ,d1,d1.u32,54);
  CHECK_BITS_EQUAL(70,d1.unnamed_16_31,0x3e1);
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
  READ_FROM_BUFFER_FULL(77,uint32 ,d2,d2.u32,55);
  CHECK_BITS_EQUAL(75,d2.unnamed_16_31,0x4e1);
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
  READ_FROM_BUFFER_FULL(82,uint32 ,d3,d3.u32,56);
  CHECK_BITS_EQUAL(80,d3.unnamed_16_31,0x5e1);
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
  READ_FROM_BUFFER_FULL(87,uint32 ,d4,d4.u32,57);
  CHECK_BITS_EQUAL(85,d4.unnamed_16_31,0x6e1);
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
 * Event unpacker for VME_CAEN_V1751.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V1751(board)
template<typename __data_src_t>
void VME_CAEN_V1751::__unpack(__data_src_t &__buffer,uint32 board)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "VME_CAEN_V1751",CT_OUT(NORM));
  }
  // MEMBER(DATA8 board_id);
  // MEMBER(DATA8 channels);
  // MEMBER(DATA32 board_time);
  // MEMBER(DATA32 channel_time[64] NO_INDEX_LIST);
  // MEMBER(DATA16 chan_ext_time[64] NO_INDEX_LIST);
  // MEMBER(DATA12 chan_fine_time[64] NO_INDEX_LIST);
  // MEMBER(DATA16 qshort[64] NO_INDEX_LIST);
  // MEMBER(DATA16 qlong[64] NO_INDEX_LIST);
  // UINT32 board_agg_size NOENCODE
  // {
    //  0_27: event_size;
    // 28_31: 10;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 event_size : 28; // 0..27
      uint32 unnamed_28_31 : 4; // 28..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_28_31 : 4; // 28..31
      uint32 event_size : 28; // 0..27
#endif
    };
    uint32  u32;
  } board_agg_size;
  READ_FROM_BUFFER_FULL(541,uint32 ,board_agg_size,board_agg_size.u32,59);
  CHECK_BITS_EQUAL(540,board_agg_size.unnamed_28_31,10);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: board_agg_size ", CT_OUT(BOLD), board_agg_size.u32, CT_OUT(NORM));
    printf(".event_size=%s%7" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  board_agg_size.event_size, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 board_details NOENCODE
  // {
    //  0_07: channels;
    //  8_23: pattern;
    // 24_25: empty;
    //    26: board_fail;
    // 27_31: id = MATCH(board);
    // ENCODE(channels,(value=channels));
    // ENCODE(board_id,(value=id));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 channels : 8; // 0..7
      uint32 pattern : 16; // 8..23
      uint32 empty : 2; // 24..25
      uint32 board_fail : 1; // 26
      uint32 id : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 id : 5; // 27..31
      uint32 board_fail : 1; // 26
      uint32 empty : 2; // 24..25
      uint32 pattern : 16; // 8..23
      uint32 channels : 8; // 0..7
#endif
    };
    uint32  u32;
  } board_details;
  READ_FROM_BUFFER_FULL(552,uint32 ,board_details,board_details.u32,60);
  CHECK_BITS_EQUAL(549,board_details.id,board);
  {
    {
      channels.value = board_details.channels;
    }
    {
      board_id.value = board_details.id;
    }
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: board_details ", CT_OUT(BOLD), board_details.u32, CT_OUT(NORM));
    printf(".channels=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  board_details.channels, CT_OUT(NORM));
    printf(".pattern=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  board_details.pattern, CT_OUT(NORM));
    printf(".empty=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  board_details.empty, CT_OUT(NORM));
    printf(".board_fail=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  board_details.board_fail, CT_OUT(NORM));
    printf(".id=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  board_details.id, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 board_agg_counter NOENCODE
  // {
    //  0_22: counter;
    // 23_31: empty;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 counter : 23; // 0..22
      uint32 empty : 9; // 23..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 empty : 9; // 23..31
      uint32 counter : 23; // 0..22
#endif
    };
    uint32  u32;
  } board_agg_counter;
  READ_FROM_BUFFER_FULL(558,uint32 ,board_agg_counter,board_agg_counter.u32,61);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: board_agg_counter ", CT_OUT(BOLD), board_agg_counter.u32, CT_OUT(NORM));
    printf(".counter=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  board_agg_counter.counter, CT_OUT(NORM));
    printf(".empty=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  board_agg_counter.empty, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 board_agg_timetag NOENCODE
  // {
    //  0_31: time_tag;
    // ENCODE(board_time,(value=time_tag));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 time_tag : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 time_tag : 32; // 0..31
#endif
    };
    uint32  u32;
  } board_agg_timetag;
  READ_FROM_BUFFER_FULL(564,uint32 ,board_agg_timetag,board_agg_timetag.u32,62);
  {
    board_time.value = board_agg_timetag.time_tag;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: board_agg_timetag ", CT_OUT(BOLD), board_agg_timetag.u32, CT_OUT(NORM));
    printf(".time_tag=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  board_agg_timetag.time_tag, CT_OUT(NORM));
    printf("\n");
  }
  // if((board_agg_size.event_size > 4))

  if ((board_agg_size.event_size > 4))
  {
    // list(0<=index<((board_agg_size.event_size - 4) / 6))

    for (uint32 index = 0; index < (uint32) (((board_agg_size.event_size - 4) / 6)); ++index)
    {
      // UINT32 channel_agg_size NOENCODE
      // {
        //  0_21: size;
        // 22_27: empty;
        // 28_31: format;
      // }
      union
      {
        struct
        {
#if __BYTE_ORDER == __LITTLE_ENDIAN
          uint32 size : 22; // 0..21
          uint32 empty : 6; // 22..27
          uint32 format : 4; // 28..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
          uint32 format : 4; // 28..31
          uint32 empty : 6; // 22..27
          uint32 size : 22; // 0..21
#endif
        };
        uint32  u32;
      } channel_agg_size;
      READ_FROM_BUFFER_FULL(582,uint32 ,channel_agg_size,channel_agg_size.u32,63);
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: channel_agg_size ", CT_OUT(BOLD), channel_agg_size.u32, CT_OUT(NORM));
        printf(".size=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_agg_size.size, CT_OUT(NORM));
        printf(".empty=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_agg_size.empty, CT_OUT(NORM));
        printf(".format=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_agg_size.format, CT_OUT(NORM));
        printf("\n");
      }
      // UINT32 format_one NOENCODE
      // {
        //  0_15: no_wave_samples;
        // 16_17: empty;
        //    18: ed;
        // 19_21: dp1;
        // 22_24: dp2;
        // 25_26: ap;
        //    27: es;
        //    28: ee;
        //    29: et;
        //    30: eq;
        //    31: dt;
      // }
      union
      {
        struct
        {
#if __BYTE_ORDER == __LITTLE_ENDIAN
          uint32 no_wave_samples : 16; // 0..15
          uint32 empty : 2; // 16..17
          uint32 ed : 1; // 18
          uint32 dp1 : 3; // 19..21
          uint32 dp2 : 3; // 22..24
          uint32 ap : 2; // 25..26
          uint32 es : 1; // 27
          uint32 ee : 1; // 28
          uint32 et : 1; // 29
          uint32 eq : 1; // 30
          uint32 dt : 1; // 31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
          uint32 dt : 1; // 31
          uint32 eq : 1; // 30
          uint32 et : 1; // 29
          uint32 ee : 1; // 28
          uint32 es : 1; // 27
          uint32 ap : 2; // 25..26
          uint32 dp2 : 3; // 22..24
          uint32 dp1 : 3; // 19..21
          uint32 ed : 1; // 18
          uint32 empty : 2; // 16..17
          uint32 no_wave_samples : 16; // 0..15
#endif
        };
        uint32  u32;
      } format_one;
      READ_FROM_BUFFER_FULL(597,uint32 ,format_one,format_one.u32,64);
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: format_one ", CT_OUT(BOLD), format_one.u32, CT_OUT(NORM));
        printf(".no_wave_samples=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_one.no_wave_samples, CT_OUT(NORM));
        printf(".empty=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_one.empty, CT_OUT(NORM));
        printf(".ed=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_one.ed, CT_OUT(NORM));
        printf(".dp1=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_one.dp1, CT_OUT(NORM));
        printf(".dp2=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_one.dp2, CT_OUT(NORM));
        printf(".ap=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_one.ap, CT_OUT(NORM));
        printf(".es=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_one.es, CT_OUT(NORM));
        printf(".ee=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_one.ee, CT_OUT(NORM));
        printf(".et=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_one.et, CT_OUT(NORM));
        printf(".eq=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_one.eq, CT_OUT(NORM));
        printf(".dt=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_one.dt, CT_OUT(NORM));
        printf("\n");
      }
      // if((channel_agg_size.format == 4))

      // else

      if ((channel_agg_size.format == 4))
      {
        // UINT32 format_two NOENCODE
        // {
          //  0_02: ex;
          //     3: pp;
          //     4: dm;
          //  5_07: interp;
          //  8_31: empty;
        // }
        union
        {
          struct
          {
#if __BYTE_ORDER == __LITTLE_ENDIAN
            uint32 ex : 3; // 0..2
            uint32 pp : 1; // 3
            uint32 dm : 1; // 4
            uint32 interp : 3; // 5..7
            uint32 empty : 24; // 8..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
            uint32 empty : 24; // 8..31
            uint32 interp : 3; // 5..7
            uint32 dm : 1; // 4
            uint32 pp : 1; // 3
            uint32 ex : 3; // 0..2
#endif
          };
          uint32  u32;
        } format_two;
        READ_FROM_BUFFER_FULL(608,uint32 ,format_two,format_two.u32,65);
        if (__buffer.is_memberdump())
        {
          printf("%s%08" PRIx32 "%s: format_two ", CT_OUT(BOLD), format_two.u32, CT_OUT(NORM));
          printf(".ex=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_two.ex, CT_OUT(NORM));
          printf(".pp=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_two.pp, CT_OUT(NORM));
          printf(".dm=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_two.dm, CT_OUT(NORM));
          printf(".interp=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_two.interp, CT_OUT(NORM));
          printf(".empty=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  format_two.empty, CT_OUT(NORM));
          printf("\n");
        }
        // if((format_one.et == 1))

        if ((format_one.et == 1))
        {
          // UINT32 channel_time_tag NOENCODE
          // {
            //  0_31: time_tag;
            // ENCODE(channel_time APPEND_LIST,(value=time_tag));
          // }
          union
          {
            struct
            {
#if __BYTE_ORDER == __LITTLE_ENDIAN
              uint32 time_tag : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
              uint32 time_tag : 32; // 0..31
#endif
            };
            uint32  u32;
          } channel_time_tag;
          READ_FROM_BUFFER_FULL(616,uint32 ,channel_time_tag,channel_time_tag.u32,66);
          {
            typedef __typeof__(*(&(channel_time))) __array_t;
            typedef typename __array_t::item_t __item_t;
            __item_t &__item = channel_time.append_item(615);
            __item.value = channel_time_tag.time_tag;
          }
          if (__buffer.is_memberdump())
          {
            printf("%s%08" PRIx32 "%s: channel_time_tag ", CT_OUT(BOLD), channel_time_tag.u32, CT_OUT(NORM));
            printf(".time_tag=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_time_tag.time_tag, CT_OUT(NORM));
            printf("\n");
          }
        }
        // if(((format_one.ee == 1) && (channel_agg_size.format == 4)))

        if (((format_one.ee == 1) && (channel_agg_size.format == 4)))
        {
          // if((format_two.ex == 0))

          // else

          if ((format_two.ex == 0))
          {
            // UINT32 extras NOENCODE
            // {
              //  0_15: baseline;
              // 16_31: ext_time;
              // ENCODE(chan_ext_time APPEND_LIST,(value=ext_time));
            // }
            union
            {
              struct
              {
#if __BYTE_ORDER == __LITTLE_ENDIAN
                uint32 baseline : 16; // 0..15
                uint32 ext_time : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
                uint32 ext_time : 16; // 16..31
                uint32 baseline : 16; // 0..15
#endif
              };
              uint32  u32;
            } extras;
            READ_FROM_BUFFER_FULL(630,uint32 ,extras,extras.u32,67);
            {
              typedef __typeof__(*(&(chan_ext_time))) __array_t;
              typedef typename __array_t::item_t __item_t;
              __item_t &__item = chan_ext_time.append_item(629);
              __item.value = extras.ext_time;
            }
            if (__buffer.is_memberdump())
            {
              printf("%s%08" PRIx32 "%s: extras ", CT_OUT(BOLD), extras.u32, CT_OUT(NORM));
              printf(".baseline=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.baseline, CT_OUT(NORM));
              printf(".ext_time=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.ext_time, CT_OUT(NORM));
              printf("\n");
            }
          }

          else
          {
            // if((format_two.ex == 1))

            // else

            if ((format_two.ex == 1))
            {
              // UINT32 extras NOENCODE
              // {
                //  0_15: flags;
                // 16_31: ext_time;
                // ENCODE(chan_ext_time APPEND_LIST,(value=ext_time));
              // }
              union
              {
                struct
                {
#if __BYTE_ORDER == __LITTLE_ENDIAN
                  uint32 flags : 16; // 0..15
                  uint32 ext_time : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
                  uint32 ext_time : 16; // 16..31
                  uint32 flags : 16; // 0..15
#endif
                };
                uint32  u32;
              } extras;
              READ_FROM_BUFFER_FULL(639,uint32 ,extras,extras.u32,68);
              {
                typedef __typeof__(*(&(chan_ext_time))) __array_t;
                typedef typename __array_t::item_t __item_t;
                __item_t &__item = chan_ext_time.append_item(638);
                __item.value = extras.ext_time;
              }
              if (__buffer.is_memberdump())
              {
                printf("%s%08" PRIx32 "%s: extras ", CT_OUT(BOLD), extras.u32, CT_OUT(NORM));
                printf(".flags=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.flags, CT_OUT(NORM));
                printf(".ext_time=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.ext_time, CT_OUT(NORM));
                printf("\n");
              }
            }

            else
            {
              // if((format_two.ex == 2))

              // else

              if ((format_two.ex == 2))
              {
                // UINT32 extras NOENCODE
                // {
                  //  0_09: fine_time;
                  // 10_15: flags;
                  // 16_31: ext_time;
                  // ENCODE(chan_fine_time APPEND_LIST,(value=fine_time));
                  // ENCODE(chan_ext_time APPEND_LIST,(value=ext_time));
                // }
                union
                {
                  struct
                  {
#if __BYTE_ORDER == __LITTLE_ENDIAN
                    uint32 fine_time : 10; // 0..9
                    uint32 flags : 6; // 10..15
                    uint32 ext_time : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
                    uint32 ext_time : 16; // 16..31
                    uint32 flags : 6; // 10..15
                    uint32 fine_time : 10; // 0..9
#endif
                  };
                  uint32  u32;
                } extras;
                READ_FROM_BUFFER_FULL(650,uint32 ,extras,extras.u32,69);
                {
                  {
                    typedef __typeof__(*(&(chan_fine_time))) __array_t;
                    typedef typename __array_t::item_t __item_t;
                    __item_t &__item = chan_fine_time.append_item(648);
                    __item.value = extras.fine_time;
                  }
                  {
                    typedef __typeof__(*(&(chan_ext_time))) __array_t;
                    typedef typename __array_t::item_t __item_t;
                    __item_t &__item = chan_ext_time.append_item(649);
                    __item.value = extras.ext_time;
                  }
                }
                if (__buffer.is_memberdump())
                {
                  printf("%s%08" PRIx32 "%s: extras ", CT_OUT(BOLD), extras.u32, CT_OUT(NORM));
                  printf(".fine_time=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.fine_time, CT_OUT(NORM));
                  printf(".flags=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.flags, CT_OUT(NORM));
                  printf(".ext_time=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.ext_time, CT_OUT(NORM));
                  printf("\n");
                }
              }

              else
              {
                // if((format_two.ex == 4))

                // else

                if ((format_two.ex == 4))
                {
                  // UINT32 extras NOENCODE
                  // {
                    //  0_15: baseline;
                    // 16_26: fine_time;
                    // 27_31: flags;
                    // ENCODE(chan_fine_time APPEND_LIST,(value=fine_time));
                  // }
                  union
                  {
                    struct
                    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
                      uint32 baseline : 16; // 0..15
                      uint32 fine_time : 11; // 16..26
                      uint32 flags : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
                      uint32 flags : 5; // 27..31
                      uint32 fine_time : 11; // 16..26
                      uint32 baseline : 16; // 0..15
#endif
                    };
                    uint32  u32;
                  } extras;
                  READ_FROM_BUFFER_FULL(660,uint32 ,extras,extras.u32,70);
                  {
                    typedef __typeof__(*(&(chan_fine_time))) __array_t;
                    typedef typename __array_t::item_t __item_t;
                    __item_t &__item = chan_fine_time.append_item(659);
                    __item.value = extras.fine_time;
                  }
                  if (__buffer.is_memberdump())
                  {
                    printf("%s%08" PRIx32 "%s: extras ", CT_OUT(BOLD), extras.u32, CT_OUT(NORM));
                    printf(".baseline=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.baseline, CT_OUT(NORM));
                    printf(".fine_time=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.fine_time, CT_OUT(NORM));
                    printf(".flags=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.flags, CT_OUT(NORM));
                    printf("\n");
                  }
                }

                else
                {
                  // if((format_two.ex == 5))

                  if ((format_two.ex == 5))
                  {
                    // UINT32 extras NOENCODE
                    // {
                      //  0_09: midscale;
                      // 10_19: sazc;
                      // 20_29: sbzc;
                      //    30: pp;
                      //    31: dm;
                    // }
                    union
                    {
                      struct
                      {
#if __BYTE_ORDER == __LITTLE_ENDIAN
                        uint32 midscale : 10; // 0..9
                        uint32 sazc : 10; // 10..19
                        uint32 sbzc : 10; // 20..29
                        uint32 pp : 1; // 30
                        uint32 dm : 1; // 31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
                        uint32 dm : 1; // 31
                        uint32 pp : 1; // 30
                        uint32 sbzc : 10; // 20..29
                        uint32 sazc : 10; // 10..19
                        uint32 midscale : 10; // 0..9
#endif
                      };
                      uint32  u32;
                    } extras;
                    READ_FROM_BUFFER_FULL(671,uint32 ,extras,extras.u32,71);
                    if (__buffer.is_memberdump())
                    {
                      printf("%s%08" PRIx32 "%s: extras ", CT_OUT(BOLD), extras.u32, CT_OUT(NORM));
                      printf(".midscale=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.midscale, CT_OUT(NORM));
                      printf(".sazc=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.sazc, CT_OUT(NORM));
                      printf(".sbzc=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.sbzc, CT_OUT(NORM));
                      printf(".pp=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.pp, CT_OUT(NORM));
                      printf(".dm=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  extras.dm, CT_OUT(NORM));
                      printf("\n");
                    }
                  }
                }
              }
            }
          }
        }
      }

      else
      {
        // if((format_one.et == 1))

        if ((format_one.et == 1))
        {
          // UINT32 channel_time_tag NOENCODE
          // {
            //  0_31: time_tag;
            // ENCODE(channel_time APPEND_LIST,(value=time_tag));
          // }
          union
          {
            struct
            {
#if __BYTE_ORDER == __LITTLE_ENDIAN
              uint32 time_tag : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
              uint32 time_tag : 32; // 0..31
#endif
            };
            uint32  u32;
          } channel_time_tag;
          READ_FROM_BUFFER_FULL(685,uint32 ,channel_time_tag,channel_time_tag.u32,72);
          {
            typedef __typeof__(*(&(channel_time))) __array_t;
            typedef typename __array_t::item_t __item_t;
            __item_t &__item = channel_time.append_item(684);
            __item.value = channel_time_tag.time_tag;
          }
          if (__buffer.is_memberdump())
          {
            printf("%s%08" PRIx32 "%s: channel_time_tag ", CT_OUT(BOLD), channel_time_tag.u32, CT_OUT(NORM));
            printf(".time_tag=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  channel_time_tag.time_tag, CT_OUT(NORM));
            printf("\n");
          }
        }
      }
      // if((format_one.eq == 1))

      if ((format_one.eq == 1))
      {
        // UINT32 qdata NOENCODE
        // {
          //  0_14: qshort;
          //    15: empty;
          // 16_31: qlong;
          // ENCODE(qshort APPEND_LIST,(value=qshort));
          // ENCODE(qlong APPEND_LIST,(value=qlong));
        // }
        union
        {
          struct
          {
#if __BYTE_ORDER == __LITTLE_ENDIAN
            uint32 qshort : 15; // 0..14
            uint32 empty : 1; // 15
            uint32 qlong : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
            uint32 qlong : 16; // 16..31
            uint32 empty : 1; // 15
            uint32 qshort : 15; // 0..14
#endif
          };
          uint32  u32;
        } qdata;
        READ_FROM_BUFFER_FULL(700,uint32 ,qdata,qdata.u32,73);
        {
          {
            typedef __typeof__(*(&(qshort))) __array_t;
            typedef typename __array_t::item_t __item_t;
            __item_t &__item = qshort.append_item(698);
            __item.value = qdata.qshort;
          }
          {
            typedef __typeof__(*(&(qlong))) __array_t;
            typedef typename __array_t::item_t __item_t;
            __item_t &__item = qlong.append_item(699);
            __item.value = qdata.qlong;
          }
        }
        if (__buffer.is_memberdump())
        {
          printf("%s%08" PRIx32 "%s: qdata ", CT_OUT(BOLD), qdata.u32, CT_OUT(NORM));
          printf(".qshort=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  qdata.qshort, CT_OUT(NORM));
          printf(".empty=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  qdata.empty, CT_OUT(NORM));
          printf(".qlong=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  qdata.qlong, CT_OUT(NORM));
          printf("\n");
        }
      }
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,VME_CAEN_V1751::__unpack,uint32 board);

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
  READ_FROM_BUFFER_FULL(98,uint32 ,hi,hi.u32,75);
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
  READ_FROM_BUFFER_FULL(102,uint32 ,lo,lo.u32,76);
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
 * Event unpacker for bplast_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(bplast_subev)
template<typename __data_src_t>
void bplast_subev::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_MAGENTA),  "bplast_subev",CT_OUT(NORM));
  }
  // select optional

    // ts = TIMESTAMP_WHITERABBIT(id=0x500);
  do
  {
    if (__buffer.empty()) goto no_match_1;
    int __match_no = 0;
    // optimized match 1: TIMESTAMP_WHITERABBIT ts: (s32) => (0xfffeffff,0x00000500)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(756,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(755,spurious_match_abort_loop_2,TIMESTAMP_WHITERABBIT,/*id*/0x500);
        UNPACK_DECL(755,TIMESTAMP_WHITERABBIT,ts,/*id*/0x500);
        break;
    }
  }
  while (0);
  spurious_match_abort_loop_2:;
    no_match_1:;
  // select optional

    // trigger_window = TAMEX4_HEADER();
  do
  {
    if (__buffer.empty()) goto no_match_2;
    int __match_no = 0;
    // optimized match 1: TAMEX4_HEADER trigger_window: (s32) => (0x00000000,0x00000000)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(762,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(761,spurious_match_abort_loop_3,TAMEX4_HEADER);
        UNPACK_DECL(761,TAMEX4_HEADER,trigger_window);
        break;
    }
  }
  while (0);
  spurious_match_abort_loop_3:;
    no_match_2:;
  // select several

    // padding = TAMEX4_PADDING();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TAMEX4_PADDING padding: (s32) => (0xfff00000,0xadd00000)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(767,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(766,spurious_match_abort_loop_4,TAMEX4_PADDING);
        UNPACK_DECL(766,TAMEX4_PADDING,padding);
        break;
    }
  }
  spurious_match_abort_loop_4:;
  // select several

    // tamex[0] = TAMEX4_SFP(sfp=0,card=0);
    // tamex[1] = TAMEX4_SFP(sfp=0,card=1);
    // tamex[2] = TAMEX4_SFP(sfp=0,card=2);
    // tamex[3] = TAMEX4_SFP(sfp=0,card=3);
    // tamex[4] = TAMEX4_SFP(sfp=0,card=4);
    // tamex[5] = TAMEX4_SFP(sfp=0,card=5);
    // tamex[6] = TAMEX4_SFP(sfp=0,card=6);
    // tamex[7] = TAMEX4_SFP(sfp=0,card=7);
    // tamex[8] = TAMEX4_SFP(sfp=0,card=8);
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TAMEX4_SFP tamex[0]: (s32) => (0xfffff0ff,0x00000034)
    // optimized match 2: TAMEX4_SFP tamex[1]: (s32) => (0xfffff0ff,0x00010034)
    // optimized match 3: TAMEX4_SFP tamex[2]: (s32) => (0xfffff0ff,0x00020034)
    // optimized match 4: TAMEX4_SFP tamex[3]: (s32) => (0xfffff0ff,0x00030034)
    // optimized match 5: TAMEX4_SFP tamex[4]: (s32) => (0xfffff0ff,0x00040034)
    // optimized match 6: TAMEX4_SFP tamex[5]: (s32) => (0xfffff0ff,0x00050034)
    // optimized match 7: TAMEX4_SFP tamex[6]: (s32) => (0xfffff0ff,0x00060034)
    // optimized match 8: TAMEX4_SFP tamex[7]: (s32) => (0xfffff0ff,0x00070034)
    // optimized match 9: TAMEX4_SFP tamex[8]: (s32) => (0xfffff0ff,0x00080034)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(781,uint32,__match_peek);
    // differ = 000f0000 : 16 17 18 19
    uint32 __match_index = 0 | /* 16,19 */ ((__match_peek >> 16) & 0x0000000f);
    static const sint8 __match_index_array[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, };
    __match_no = __match_index_array[__match_index];
    // last_subevent_item = 1
    }
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        UNPACK_DECL(772,TAMEX4_SFP,tamex[0],/*sfp*/0,/*card*/0);
        break;
      case 2:
        UNPACK_DECL(773,TAMEX4_SFP,tamex[1],/*sfp*/0,/*card*/1);
        break;
      case 3:
        UNPACK_DECL(774,TAMEX4_SFP,tamex[2],/*sfp*/0,/*card*/2);
        break;
      case 4:
        UNPACK_DECL(775,TAMEX4_SFP,tamex[3],/*sfp*/0,/*card*/3);
        break;
      case 5:
        UNPACK_DECL(776,TAMEX4_SFP,tamex[4],/*sfp*/0,/*card*/4);
        break;
      case 6:
        UNPACK_DECL(777,TAMEX4_SFP,tamex[5],/*sfp*/0,/*card*/5);
        break;
      case 7:
        UNPACK_DECL(778,TAMEX4_SFP,tamex[6],/*sfp*/0,/*card*/6);
        break;
      case 8:
        UNPACK_DECL(779,TAMEX4_SFP,tamex[7],/*sfp*/0,/*card*/7);
        break;
      case 9:
        UNPACK_DECL(780,TAMEX4_SFP,tamex[8],/*sfp*/0,/*card*/8);
        break;
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,bplast_subev::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for fatima_tamex_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(fatima_tamex_subev)
template<typename __data_src_t>
void fatima_tamex_subev::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_MAGENTA),  "fatima_tamex_subev",CT_OUT(NORM));
  }
  // select optional

    // ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1600);
  do
  {
    if (__buffer.empty()) goto no_match_3;
    int __match_no = 0;
    // optimized match 1: TIMESTAMP_WHITERABBIT_EXTENDED ts: (s32) => (0xfffeffff,0x00001600)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(738,uint32,__match_peek);
    // differ = 00000000 :
    uint32 __match_index = 0;
    static const sint8 __match_index_array[1] = { 1, };
    __match_no = __match_index_array[__match_index];
    // last_subevent_item = 0
    }
    if (!__match_no) goto no_match_3;
    switch (__match_no)
    {
      case 1:
        CHECK_SPURIOUS_MATCH_DECL(737,spurious_match_abort_loop_5,TIMESTAMP_WHITERABBIT_EXTENDED,/*id*/0x1600);
        UNPACK_DECL(737,TIMESTAMP_WHITERABBIT_EXTENDED,ts,/*id*/0x1600);
        break;
    }
  }
  while (0);
  spurious_match_abort_loop_5:;
    no_match_3:;
  // select several

    // data[0] = TAMEX4_SFP(sfp=0,card=0);
    // data[1] = TAMEX4_SFP(sfp=0,card=1);
    // data[2] = TAMEX4_SFP(sfp=0,card=2);
    // data[3] = TAMEX4_SFP(sfp=0,card=3);
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TAMEX4_SFP data[0]: (s32) => (0xfffff0ff,0x00000034)
    // optimized match 2: TAMEX4_SFP data[1]: (s32) => (0xfffff0ff,0x00010034)
    // optimized match 3: TAMEX4_SFP data[2]: (s32) => (0xfffff0ff,0x00020034)
    // optimized match 4: TAMEX4_SFP data[3]: (s32) => (0xfffff0ff,0x00030034)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(746,uint32,__match_peek);
    // differ = 00030000 : 16 17
    uint32 __match_index = 0 | /* 16,17 */ ((__match_peek >> 16) & 0x00000003);
    static const sint8 __match_index_array[4] = { 1, 2, 3, 4, };
    __match_no = __match_index_array[__match_index];
    // last_subevent_item = 1
    }
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        UNPACK_DECL(742,TAMEX4_SFP,data[0],/*sfp*/0,/*card*/0);
        break;
      case 2:
        UNPACK_DECL(743,TAMEX4_SFP,data[1],/*sfp*/0,/*card*/1);
        break;
      case 3:
        UNPACK_DECL(744,TAMEX4_SFP,data[2],/*sfp*/0,/*card*/2);
        break;
      case 4:
        UNPACK_DECL(745,TAMEX4_SFP,data[3],/*sfp*/0,/*card*/3);
        break;
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,fatima_tamex_subev::__unpack);

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
  // fatima = fatima_tamex_subev(type=10,subtype=1,procid=75,control=20);
  // bplast = bplast_subev(type=10,subtype=1,procid=80,control=20);
  // ignore_unknown_subevent;
{
  int __match_no = 0;
  MATCH_SUBEVENT_DECL(788,__match_no,1,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==20)&&(VES10_1_procid==75)),fatima);
  MATCH_SUBEVENT_DECL(789,__match_no,2,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==20)&&(VES10_1_procid==80)),bplast);
  if (!__match_no) return 0;
  switch (__match_no)
  {
    case 1:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(788,fatima_tamex_subev,fatima,0);
      UNPACK_SUBEVENT_DECL(788,0,fatima_tamex_subev,fatima);
      break;
    case 2:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(789,bplast_subev,bplast,1);
      UNPACK_SUBEVENT_DECL(789,0,bplast_subev,bplast);
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
