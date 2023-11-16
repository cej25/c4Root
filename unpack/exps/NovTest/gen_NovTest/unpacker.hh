/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for EXT_AIDA.
 *
 * Do not edit - automatically generated.
 */


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
  // MEMBER(DATA32 event_trigger_time_hi);
  // MEMBER(DATA32 event_trigger_time_lo);
  // MEMBER(DATA16 hit_pattern);
  // MEMBER(DATA32 num_channels_fired);
  // MEMBER(DATA8 channel_id[16] ZERO_SUPPRESS);
  // MEMBER(DATA16 channel_trigger_time_hi[16] ZERO_SUPPRESS);
  // MEMBER(DATA32 channel_trigger_time_lo[16] ZERO_SUPPRESS);
  // MEMBER(DATA8 pileup[16]);
  // MEMBER(DATA8 overflow[16]);
  // MEMBER(DATA8 channel_cfd[16] ZERO_SUPPRESS);
  // MEMBER(DATA32 channel_energy[16] ZERO_SUPPRESS);
  // UINT32 sumchannel NOENCODE
  // {
    //  0_07: 52;
    //  8_11: trigger_type;
    // 12_15: sfpnr;
    // 16_23: card = MATCH(card);
    // 24_31: 255;
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
  READ_FROM_BUFFER_FULL(268,uint32 ,sumchannel,sumchannel.u32,0);
  CHECK_BITS_EQUAL(262,sumchannel.unnamed_0_7,52);
  CHECK_BITS_EQUAL(265,sumchannel.card,card);
  CHECK_BITS_EQUAL(266,sumchannel.unnamed_24_31,255);
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
  READ_FROM_BUFFER_FULL(276,uint32 ,channel_size,channel_size.u32,1);
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
  READ_FROM_BUFFER_FULL(285,uint32 ,event_timestamp_hi,event_timestamp_hi.u32,2);
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
  READ_FROM_BUFFER_FULL(291,uint32 ,event_timestamp_lo,event_timestamp_lo.u32,3);
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
  READ_FROM_BUFFER_FULL(299,uint32 ,hp,hp.u32,4);
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
  READ_FROM_BUFFER_FULL(304,uint32 ,deadbeef,deadbeef.u32,5);
  CHECK_BITS_EQUAL(303,deadbeef.unnamed_0_31,0xdeadbeef);
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
    READ_FROM_BUFFER_FULL(315,uint32 ,channelids,channelids.u32,6);
    CHECK_BITS_EQUAL(311,channelids.unnamed_24_31,240);
    {
      {
        typedef __typeof__(*(&(channel_id))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_id.insert_index(313,index);
        __item.value = channelids.channel_id_bits;
      }
      {
        typedef __typeof__(*(&(channel_trigger_time_hi))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_trigger_time_hi.insert_index(314,index);
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
    READ_FROM_BUFFER_FULL(320,uint32 ,channel_ts,channel_ts.u32,7);
    {
      typedef __typeof__(*(&(channel_trigger_time_lo))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = channel_trigger_time_lo.insert_index(319,index);
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
    READ_FROM_BUFFER_FULL(332,uint32 ,chan_enrgy,chan_enrgy.u32,8);
    {
      {
        typedef __typeof__(*(&(channel_cfd))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_cfd.insert_index(328,index);
        __item.value = chan_enrgy.TSF;
      }
      {
        typedef __typeof__(*(&(channel_energy))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_energy.insert_index(329,index);
        __item.value = chan_enrgy.chan_energy;
      }
      {
        typedef __typeof__(*(&(pileup))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = pileup.insert_index(330,index);
        __item.value = chan_enrgy.pileup_flag;
      }
      {
        typedef __typeof__(*(&(overflow))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = overflow.insert_index(331,index);
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
    READ_FROM_BUFFER_FULL(336,uint32 ,future_use,future_use.u32,9);
    CHECK_BITS_EQUAL(335,future_use.unnamed_0_31,0);
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
  // MEMBER(DATA32 event_trigger_time_hi);
  // MEMBER(DATA32 event_trigger_time_lo);
  // MEMBER(DATA16 hit_pattern);
  // MEMBER(DATA32 num_channels_fired);
  // MEMBER(DATA8 channel_id[16] ZERO_SUPPRESS);
  // MEMBER(DATA16 channel_trigger_time_hi[16] ZERO_SUPPRESS);
  // MEMBER(DATA32 channel_trigger_time_lo[16] ZERO_SUPPRESS);
  // MEMBER(DATA8 pileup[16]);
  // MEMBER(DATA8 overflow[16]);
  // MEMBER(DATA8 channel_cfd[16] ZERO_SUPPRESS);
  // MEMBER(DATA32 channel_energy[16] ZERO_SUPPRESS);
  // MEMBER(DATA16 traces[16][10000] ZERO_SUPPRESS);
  // UINT32 sumchannel NOENCODE
  // {
    //  0_07: 52;
    //  8_11: trigger_type;
    // 12_15: sfpnr;
    // 16_23: board_id = MATCH(card);
    // 24_31: 255;
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
  READ_FROM_BUFFER_FULL(367,uint32 ,sumchannel,sumchannel.u32,11);
  CHECK_BITS_EQUAL(361,sumchannel.unnamed_0_7,52);
  CHECK_BITS_EQUAL(364,sumchannel.board_id,card);
  CHECK_BITS_EQUAL(365,sumchannel.unnamed_24_31,255);
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
  READ_FROM_BUFFER_FULL(375,uint32 ,channel_size,channel_size.u32,12);
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
  READ_FROM_BUFFER_FULL(384,uint32 ,event_timestamp_hi,event_timestamp_hi.u32,13);
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
  READ_FROM_BUFFER_FULL(390,uint32 ,event_timestamp_lo,event_timestamp_lo.u32,14);
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
  READ_FROM_BUFFER_FULL(398,uint32 ,hp,hp.u32,15);
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
  READ_FROM_BUFFER_FULL(403,uint32 ,deadbeef,deadbeef.u32,16);
  CHECK_BITS_EQUAL(402,deadbeef.unnamed_0_31,0xdeadbeef);
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
      READ_FROM_BUFFER_FULL(416,uint32 ,channelids,channelids.u32,17);
      CHECK_BITS_EQUAL(412,channelids.unnamed_24_31,240);
      {
        {
          typedef __typeof__(*(&(channel_id))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_id.insert_index(414,index);
          __item.value = channelids.channel_id_bits;
        }
        {
          typedef __typeof__(*(&(channel_trigger_time_hi))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_trigger_time_hi.insert_index(415,index);
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
      READ_FROM_BUFFER_FULL(421,uint32 ,channel_ts,channel_ts.u32,18);
      {
        typedef __typeof__(*(&(channel_trigger_time_lo))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_trigger_time_lo.insert_index(420,index);
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
      READ_FROM_BUFFER_FULL(433,uint32 ,chan_enrgy,chan_enrgy.u32,19);
      {
        {
          typedef __typeof__(*(&(channel_cfd))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_cfd.insert_index(429,index);
          __item.value = chan_enrgy.TSF;
        }
        {
          typedef __typeof__(*(&(channel_energy))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_energy.insert_index(430,index);
          __item.value = chan_enrgy.chan_energy;
        }
        {
          typedef __typeof__(*(&(pileup))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = pileup.insert_index(431,index);
          __item.value = chan_enrgy.pileup_flag;
        }
        {
          typedef __typeof__(*(&(overflow))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = overflow.insert_index(432,index);
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
      READ_FROM_BUFFER_FULL(437,uint32 ,future_use,future_use.u32,20);
      CHECK_BITS_EQUAL(436,future_use.unnamed_0_31,0);
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: future_use ", CT_OUT(BOLD), future_use.u32, CT_OUT(NORM));
        printf("\n");
      }
    }
    // list(0<=i<16)

    for (uint32 i = 0; i < (uint32) (16); ++i)
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
      READ_FROM_BUFFER_FULL(447,uint32 ,header,header.u32,21);
      CHECK_BITS_EQUAL(444,header.unnamed_0_7,52);
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
      READ_FROM_BUFFER_FULL(452,uint32 ,tracesize,tracesize.u32,22);
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
      READ_FROM_BUFFER_FULL(458,uint32 ,tracehead,tracehead.u32,23);
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
        READ_FROM_BUFFER_FULL(478,uint32 ,channel_trace,channel_trace.u32,24);
        {
          {
            typedef __typeof__(*(&(traces[header.ch_id]))) __array_t;
            typedef typename __array_t::item_t __item_t;
            __item_t &__item = traces[header.ch_id].insert_index(476,((2 * j) + 0));
            __item.value = channel_trace.data1;
          }
          {
            typedef __typeof__(*(&(traces[header.ch_id]))) __array_t;
            typedef typename __array_t::item_t __item_t;
            __item_t &__item = traces[header.ch_id].insert_index(477,((2 * j) + 1));
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
      READ_FROM_BUFFER_FULL(487,uint32 ,trace_trailer,trace_trailer.u32,25);
      CHECK_BITS_RANGE(486,trace_trailer.id,176,191);
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
      // list(0<=i<16)

      for (uint32 i = 0; i < (uint32) (16); ++i)
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
        READ_FROM_BUFFER_FULL(502,uint32 ,header,header.u32,26);
        CHECK_BITS_EQUAL(499,header.unnamed_0_7,52);
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
        READ_FROM_BUFFER_FULL(507,uint32 ,tracesize,tracesize.u32,27);
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
        READ_FROM_BUFFER_FULL(513,uint32 ,tracehead,tracehead.u32,28);
        if (__buffer.is_memberdump())
        {
          printf("%s%08" PRIx32 "%s: tracehead ", CT_OUT(BOLD), tracehead.u32, CT_OUT(NORM));
          printf(".other=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tracehead.other, CT_OUT(NORM));
          printf(".head=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tracehead.head, CT_OUT(NORM));
          printf("\n");
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
        READ_FROM_BUFFER_FULL(519,uint32 ,trace_trailer,trace_trailer.u32,29);
        CHECK_BITS_RANGE(518,trace_trailer.id,176,191);
        if (__buffer.is_memberdump())
        {
          printf("%s%08" PRIx32 "%s: trace_trailer ", CT_OUT(BOLD), trace_trailer.u32, CT_OUT(NORM));
          printf(".notused=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trace_trailer.notused, CT_OUT(NORM));
          printf(".id=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trace_trailer.id, CT_OUT(NORM));
          printf("\n");
        }
      }
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
  READ_FROM_BUFFER_FULL(240,uint32 ,pads_data,pads_data.u32,31);
  CHECK_BITS_EQUAL(239,pads_data.unnamed_20_31,0xadd);
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
                                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_coarse
                                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_fine
                                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_edge
                                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_channel
                                                       ,raw_list_ii_zero_suppress<DATA32,DATA32,512> &time_epoch)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TAMEX4_EPOCH_DATA",CT_OUT(NORM));
  }
  // MEMBER(DATA12 time_coarse[512] NO_INDEX_LIST);
  // MEMBER(DATA12 time_fine[512] NO_INDEX_LIST);
  // MEMBER(DATA12 time_edge[512] NO_INDEX_LIST);
  // MEMBER(DATA12 time_channel[512] NO_INDEX_LIST);
  // MEMBER(DATA32 time_epoch[512] NO_INDEX_LIST);
  // UINT32 data NOENCODE
  // {
    //  0_27: epoch;
    //    28: reserved;
    // 29_31: 3;
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
      uint32 reserved : 1; // 28
      uint32 unnamed_29_31 : 3; // 29..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_29_31 : 3; // 29..31
      uint32 reserved : 1; // 28
      uint32 epoch : 28; // 0..27
#endif
    };
    uint32  u32;
  } data;
  READ_FROM_BUFFER_FULL(168,uint32 ,data,data.u32,33);
  CHECK_BITS_EQUAL(161,data.unnamed_29_31,3);
  {
    {
      typedef __typeof__(*(&(time_coarse))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_coarse.append_item(163);
      __item.value = 0;
    }
    {
      typedef __typeof__(*(&(time_fine))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_fine.append_item(164);
      __item.value = 0;
    }
    {
      typedef __typeof__(*(&(time_edge))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_edge.append_item(165);
      __item.value = 0;
    }
    {
      typedef __typeof__(*(&(time_channel))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_channel.append_item(166);
      __item.value = 0;
    }
    {
      typedef __typeof__(*(&(time_epoch))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_epoch.append_item(167);
      __item.value = data.epoch;
    }
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: data ", CT_OUT(BOLD), data.u32, CT_OUT(NORM));
    printf(".epoch=%s%7" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  data.epoch, CT_OUT(NORM));
    printf(".reserved=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  data.reserved, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TAMEX4_EPOCH_DATA::__unpack,uint32 sfp,uint32 card
                                                            ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_coarse
                                                            ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_fine
                                                            ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_edge
                                                            ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_channel
                                                            ,raw_list_ii_zero_suppress<DATA32,DATA32,512> &time_epoch);

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
  // MEMBER(DATA16 post_trig_ns[64] NO_INDEX_LIST);
  // MEMBER(DATA16 pre_trig_ns[64] NO_INDEX_LIST);
  // UINT32 trigger_window NOENCODE
  // {
    //  0_15: post_trig_ns;
    // 16_31: pre_trig_ns;
    // ENCODE(post_trig_ns APPEND_LIST,(value=post_trig_ns));
    // ENCODE(pre_trig_ns APPEND_LIST,(value=pre_trig_ns));
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
  READ_FROM_BUFFER_FULL(112,uint32 ,trigger_window,trigger_window.u32,35);
  {
    {
      typedef __typeof__(*(&(post_trig_ns))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = post_trig_ns.append_item(110);
      __item.value = trigger_window.post_trig_ns;
    }
    {
      typedef __typeof__(*(&(pre_trig_ns))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = pre_trig_ns.append_item(111);
      __item.value = trigger_window.pre_trig_ns;
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
  READ_FROM_BUFFER_FULL(122,uint32 ,padding,padding.u32,37);
  CHECK_BITS_EQUAL(121,padding.unnamed_20_31,0xadd);
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
                                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_coarse
                                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_fine
                                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_edge
                                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_channel
                                                      ,raw_list_ii_zero_suppress<DATA32,DATA32,512> &time_epoch)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TAMEX4_TIME_DATA",CT_OUT(NORM));
  }
  // MEMBER(DATA12 time_coarse[512] NO_INDEX_LIST);
  // MEMBER(DATA12 time_fine[512] NO_INDEX_LIST);
  // MEMBER(DATA12 time_edge[512] NO_INDEX_LIST);
  // MEMBER(DATA12 time_channel[512] NO_INDEX_LIST);
  // MEMBER(DATA32 time_epoch[512] NO_INDEX_LIST);
  // UINT32 data NOENCODE
  // {
    //  0_10: coarse;
    //    11: is_leading;
    // 12_21: fine;
    // 22_28: channel;
    // 29_31: type = CHECK(4);
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
      uint32 channel : 7; // 22..28
      uint32 type : 3; // 29..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 type : 3; // 29..31
      uint32 channel : 7; // 22..28
      uint32 fine : 10; // 12..21
      uint32 is_leading : 1; // 11
      uint32 coarse : 11; // 0..10
#endif
    };
    uint32  u32;
  } data;
  READ_FROM_BUFFER_FULL(146,uint32 ,data,data.u32,39);
  CHECK_BITS_EQUAL(139,data.type,4);
  {
    {
      typedef __typeof__(*(&(time_coarse))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_coarse.append_item(141);
      __item.value = data.coarse;
    }
    {
      typedef __typeof__(*(&(time_fine))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_fine.append_item(142);
      __item.value = data.fine;
    }
    {
      typedef __typeof__(*(&(time_edge))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_edge.append_item(143);
      __item.value = data.is_leading;
    }
    {
      typedef __typeof__(*(&(time_channel))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_channel.append_item(144);
      __item.value = data.channel;
    }
    {
      typedef __typeof__(*(&(time_epoch))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = time_epoch.append_item(145);
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
                                                           ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_coarse
                                                           ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_fine
                                                           ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_edge
                                                           ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_channel
                                                           ,raw_list_ii_zero_suppress<DATA32,DATA32,512> &time_epoch);

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
  // MEMBER(DATA32 event_size);
  // MEMBER(DATA12 time_coarse[512] NO_INDEX_LIST);
  // MEMBER(DATA12 time_fine[512] NO_INDEX_LIST);
  // MEMBER(DATA12 time_edge[512] NO_INDEX_LIST);
  // MEMBER(DATA12 time_channel[512] NO_INDEX_LIST);
  // MEMBER(DATA32 time_epoch[512] NO_INDEX_LIST);
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
  READ_FROM_BUFFER_FULL(187,uint32 ,indicator,indicator.u32,41);
  CHECK_BITS_EQUAL(182,indicator.unnamed_0_7,52);
  CHECK_BITS_EQUAL(184,indicator.sfp,sfp);
  CHECK_BITS_EQUAL(185,indicator.card,card);
  CHECK_BITS_EQUAL(186,indicator.unnamed_24_31,0);
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
  READ_FROM_BUFFER_FULL(196,uint32 ,data_size,data_size.u32,42);
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
  READ_FROM_BUFFER_FULL(204,uint32 ,tdc_header,tdc_header.u32,43);
  CHECK_BITS_EQUAL(203,tdc_header.unnamed_24_31,170);
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
    // select several

      // time = TAMEX4_TIME_DATA(sfp=sfp,card=card,time_coarse=time_coarse,
                              // time_fine=time_fine,time_edge=time_edge,
                              // time_channel=time_channel,time_epoch=time_epoch);
      // epoch = TAMEX4_EPOCH_DATA(sfp=sfp,card=card,time_coarse=time_coarse,
                                // time_fine=time_fine,time_edge=time_edge,
                                // time_channel=time_channel,time_epoch=time_epoch);
    for ( ; ; )
    {
      if (__buffer.empty()) break;
      int __match_no = 0;
      // optimized match 1: TAMEX4_TIME_DATA time: (s32) => (0xe0000000,0x80000000)
      // optimized match 2: TAMEX4_EPOCH_DATA epoch: (s32) => (0xe0000000,0x60000000)
      {
      uint32 __match_peek;
      PEEK_FROM_BUFFER(210,uint32,__match_peek);
      // differ = e0000000 : 29 30 31
      uint32 __match_index = 0 | /* 29,31 */ ((__match_peek >> 29) & 0x00000007);
      static const sint8 __match_index_array[8] = { 0, 0, 0, 2, 1, 0, 0, 0, };
      __match_no = __match_index_array[__match_index];
      // last_subevent_item = 0
      }
      if (!__match_no) break;
      switch (__match_no)
      {
        case 1:
          CHECK_SPURIOUS_MATCH_DECL(208,spurious_match_abort_loop_0,TAMEX4_TIME_DATA,/*sfp*/sfp,/*card*/card/*,time_coarse:member*//*,time_fine:member*//*,time_edge:member*//*,time_channel:member*//*,time_epoch:member*/);
          UNPACK_DECL(208,TAMEX4_TIME_DATA,time,/*sfp*/sfp,/*card*/card,/*time_coarse*/time_coarse,/*time_fine*/time_fine,/*time_edge*/time_edge,/*time_channel*/time_channel,/*time_epoch*/time_epoch);
          break;
        case 2:
          CHECK_SPURIOUS_MATCH_DECL(209,spurious_match_abort_loop_0,TAMEX4_EPOCH_DATA,/*sfp*/sfp,/*card*/card/*,time_coarse:member*//*,time_fine:member*//*,time_edge:member*//*,time_channel:member*//*,time_epoch:member*/);
          UNPACK_DECL(209,TAMEX4_EPOCH_DATA,epoch,/*sfp*/sfp,/*card*/card,/*time_coarse*/time_coarse,/*time_fine*/time_fine,/*time_edge*/time_edge,/*time_channel*/time_channel,/*time_epoch*/time_epoch);
          break;
      }
    }
    spurious_match_abort_loop_0:;
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
  READ_FROM_BUFFER_FULL(216,uint32 ,error_bits,error_bits.u32,44);
  CHECK_BITS_EQUAL(215,error_bits.unnamed_24_31,238);
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
  READ_FROM_BUFFER_FULL(224,uint32 ,trailer,trailer.u32,45);
  CHECK_BITS_EQUAL(223,trailer.unnamed_24_31,187);
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
  READ_FROM_BUFFER_FULL(24,uint32 ,header,header.u32,47);
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
  READ_FROM_BUFFER_FULL(29,uint32 ,d1,d1.u32,48);
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
  READ_FROM_BUFFER_FULL(34,uint32 ,d2,d2.u32,49);
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
  READ_FROM_BUFFER_FULL(39,uint32 ,d3,d3.u32,50);
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
  READ_FROM_BUFFER_FULL(44,uint32 ,d4,d4.u32,51);
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
  READ_FROM_BUFFER_FULL(61,uint32 ,header,header.u32,53);
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
  READ_FROM_BUFFER_FULL(66,uint32 ,d1,d1.u32,54);
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
  READ_FROM_BUFFER_FULL(71,uint32 ,d2,d2.u32,55);
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
  READ_FROM_BUFFER_FULL(76,uint32 ,d3,d3.u32,56);
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
  READ_FROM_BUFFER_FULL(81,uint32 ,d4,d4.u32,57);
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
  READ_FROM_BUFFER_FULL(92,uint32 ,hi,hi.u32,59);
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
  READ_FROM_BUFFER_FULL(96,uint32 ,lo,lo.u32,60);
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
 * Event unpacker for aida_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(aida_subev)
template<typename __data_src_t>
void aida_subev::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_MAGENTA),  "aida_subev",CT_OUT(NORM));
  }
  // ts = TIMESTAMP_WHITERABBIT(id=0x700);
  UNPACK_DECL(535,TIMESTAMP_WHITERABBIT,ts,/*id*/0x700);
  // external data = EXT_AIDA();
  UNPACK_DECL(536,EXT_AIDA,data);
}
FORCE_IMPL_DATA_SRC_FCN(void,aida_subev::__unpack);

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
  // ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1600);
  UNPACK_DECL(560,TIMESTAMP_WHITERABBIT_EXTENDED,ts,/*id*/0x1600);
  // trigger_window = TAMEX4_HEADER();
  UNPACK_DECL(561,TAMEX4_HEADER,trigger_window);
  // select several

    // padding = TAMEX4_PADDING();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TAMEX4_PADDING padding: (s32) => (0xfff00000,0xadd00000)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(565,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(564,spurious_match_abort_loop_1,TAMEX4_PADDING);
        UNPACK_DECL(564,TAMEX4_PADDING,padding);
        break;
    }
  }
  spurious_match_abort_loop_1:;
  // select several

    // tamex[0] = TAMEX4_SFP(sfp=0,card=0);
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TAMEX4_SFP tamex[0]: (s32) => (0xfffff0ff,0x00000034)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(569,uint32,__match_peek);
    // differ = 00000000 :
    uint32 __match_index = 0;
    static const sint8 __match_index_array[1] = { 1, };
    __match_no = __match_index_array[__match_index];
    // last_subevent_item = 1
    }
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        UNPACK_DECL(568,TAMEX4_SFP,tamex[0],/*sfp*/0,/*card*/0);
        break;
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,fatima_tamex_subev::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for febex_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(febex_subev)
template<typename __data_src_t>
void febex_subev::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_MAGENTA),  "febex_subev",CT_OUT(NORM));
  }
  // ts = TIMESTAMP_WHITERABBIT(id=0x400);
  UNPACK_DECL(543,TIMESTAMP_WHITERABBIT,ts,/*id*/0x400);
  // select several

    // padding = FEBEX_PADDING();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: FEBEX_PADDING padding: (s32) => (0xfff00000,0xadd00000)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(548,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(547,spurious_match_abort_loop_2,FEBEX_PADDING);
        UNPACK_DECL(547,FEBEX_PADDING,padding);
        break;
    }
  }
  spurious_match_abort_loop_2:;
  // select several

    // data[0] = FEBEX_EVENT(card=0);
    // data[1] = FEBEX_EVENT(card=1);
    // data[2] = FEBEX_EVENT(card=2);
    // data[3] = FEBEX_EVENT(card=3);
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: FEBEX_EVENT data[0]: (s32) => (0xffff00ff,0xff000034)
    // optimized match 2: FEBEX_EVENT data[1]: (s32) => (0xffff00ff,0xff010034)
    // optimized match 3: FEBEX_EVENT data[2]: (s32) => (0xffff00ff,0xff020034)
    // optimized match 4: FEBEX_EVENT data[3]: (s32) => (0xffff00ff,0xff030034)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(555,uint32,__match_peek);
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
        UNPACK_DECL(551,FEBEX_EVENT,data[0],/*card*/0);
        break;
      case 2:
        UNPACK_DECL(552,FEBEX_EVENT,data[1],/*card*/1);
        break;
      case 3:
        UNPACK_DECL(553,FEBEX_EVENT,data[2],/*card*/2);
        break;
      case 4:
        UNPACK_DECL(554,FEBEX_EVENT,data[3],/*card*/3);
        break;
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,febex_subev::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for plastic_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(plastic_subev)
template<typename __data_src_t>
void plastic_subev::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_MAGENTA),  "plastic_subev",CT_OUT(NORM));
  }
  // ts = TIMESTAMP_WHITERABBIT(id=0x500);
  UNPACK_DECL(574,TIMESTAMP_WHITERABBIT,ts,/*id*/0x500);
  // trigger_window = TAMEX4_HEADER();
  UNPACK_DECL(575,TAMEX4_HEADER,trigger_window);
  // select several

    // padding = TAMEX4_PADDING();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TAMEX4_PADDING padding: (s32) => (0xfff00000,0xadd00000)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(579,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(578,spurious_match_abort_loop_3,TAMEX4_PADDING);
        UNPACK_DECL(578,TAMEX4_PADDING,padding);
        break;
    }
  }
  spurious_match_abort_loop_3:;
  // select several

    // tamex[0] = TAMEX4_SFP(sfp=0,card=0);
    // tamex[1] = TAMEX4_SFP(sfp=0,card=1);
    // tamex[2] = TAMEX4_SFP(sfp=0,card=2);
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TAMEX4_SFP tamex[0]: (s32) => (0xfffff0ff,0x00000034)
    // optimized match 2: TAMEX4_SFP tamex[1]: (s32) => (0xfffff0ff,0x00010034)
    // optimized match 3: TAMEX4_SFP tamex[2]: (s32) => (0xfffff0ff,0x00020034)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(585,uint32,__match_peek);
    // differ = 00030000 : 16 17
    uint32 __match_index = 0 | /* 16,17 */ ((__match_peek >> 16) & 0x00000003);
    static const sint8 __match_index_array[4] = { 1, 2, 3, 0, };
    __match_no = __match_index_array[__match_index];
    // last_subevent_item = 1
    }
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        UNPACK_DECL(582,TAMEX4_SFP,tamex[0],/*sfp*/0,/*card*/0);
        break;
      case 2:
        UNPACK_DECL(583,TAMEX4_SFP,tamex[1],/*sfp*/0,/*card*/1);
        break;
      case 3:
        UNPACK_DECL(584,TAMEX4_SFP,tamex[2],/*sfp*/0,/*card*/2);
        break;
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,plastic_subev::__unpack);

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
  // revisit aida = aida_subev(type=10,subtype=1,procid=90,control=37);
  // germanium = febex_subev(type=10,subtype=1,procid=60,control=20);
  // fatima = fatima_tamex_subev(type=10,subtype=1,procid=75,control=20,
                              // subcrate=0);
  // plastic = plastic_subev(type=10,subtype=1,procid=80,control=20,
                          // subcrate=0);
  // ignore_unknown_subevent;
{
  int __match_no = 0;
  MATCH_SUBEVENT_DECL(593,__match_no,1,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==37)&&(VES10_1_procid==90)),aida);
  MATCH_SUBEVENT_DECL(594,__match_no,2,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==20)&&(VES10_1_procid==60)),germanium);
  MATCH_SUBEVENT_DECL(596,__match_no,3,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==20)&&(VES10_1_subcrate==0)&&(VES10_1_procid==75)),fatima);
  MATCH_SUBEVENT_DECL(597,__match_no,4,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==20)&&(VES10_1_subcrate==0)&&(VES10_1_procid==80)),plastic);
  if (!__match_no) return 0;
  switch (__match_no)
  {
    case 1:
      UNPACK_SUBEVENT_DECL(593,0,aida_subev,aida);
      break;
    case 2:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(594,febex_subev,germanium,0);
      UNPACK_SUBEVENT_DECL(594,0,febex_subev,germanium);
      break;
    case 3:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(596,fatima_tamex_subev,fatima,1);
      UNPACK_SUBEVENT_DECL(596,0,fatima_tamex_subev,fatima);
      break;
    case 4:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(597,plastic_subev,plastic,2);
      UNPACK_SUBEVENT_DECL(597,0,plastic_subev,plastic);
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
