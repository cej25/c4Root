/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for BARRIER.
 *
 * Do not edit - automatically generated.
 */

// BARRIER()
template<typename __data_src_t>
void BARRIER::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "BARRIER",CT_OUT(NORM));
  }
  // UINT32 barrier NOENCODE
  // {
    //  0_19: no;
    // 20_31: ba = RANGE(0xf52,0xf58);
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 no : 20; // 0..19
      uint32 ba : 12; // 20..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 ba : 12; // 20..31
      uint32 no : 20; // 0..19
#endif
    };
    uint32  u32;
  } barrier;
  READ_FROM_BUFFER_FULL(1004,uint32 ,barrier,barrier.u32,0);
  CHECK_BITS_RANGE(1003,barrier.ba,0xf52,0xf58);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: barrier ", CT_OUT(BOLD), barrier.u32, CT_OUT(NORM));
    printf(".no=%s%5" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  barrier.no, CT_OUT(NORM));
    printf(".ba=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  barrier.ba, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,BARRIER::__unpack);

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
  uint32  no;READ_FROM_BUFFER(234,uint32 ,no,2);
}
FORCE_IMPL_DATA_SRC_FCN(void,DUMMY::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for EXT_AIDA.
 *
 * Do not edit - automatically generated.
 */


/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for FEBEX_BAD_EVENT.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_BAD_EVENT()
template<typename __data_src_t>
void FEBEX_BAD_EVENT::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "FEBEX_BAD_EVENT",CT_OUT(NORM));
  }
  // UINT32 bad NOENCODE
  // {
    //  0_31: 0xbad00bad;
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
  } bad;
  READ_FROM_BUFFER_FULL(242,uint32 ,bad,bad.u32,4);
  CHECK_BITS_EQUAL(241,bad.unnamed_0_31,0xbad00bad);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: bad ", CT_OUT(BOLD), bad.u32, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,FEBEX_BAD_EVENT::__unpack);

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
  READ_FROM_BUFFER_FULL(283,uint32 ,sumchannel,sumchannel.u32,6);
  CHECK_BITS_EQUAL(277,sumchannel.unnamed_0_7,52);
  CHECK_BITS_EQUAL(280,sumchannel.card,card);
  CHECK_BITS_EQUAL(281,sumchannel.unnamed_24_31,255);
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
  READ_FROM_BUFFER_FULL(291,uint32 ,channel_size,channel_size.u32,7);
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
  READ_FROM_BUFFER_FULL(300,uint32 ,event_timestamp_hi,event_timestamp_hi.u32,8);
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
  READ_FROM_BUFFER_FULL(306,uint32 ,event_timestamp_lo,event_timestamp_lo.u32,9);
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
  READ_FROM_BUFFER_FULL(314,uint32 ,hp,hp.u32,10);
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
  READ_FROM_BUFFER_FULL(319,uint32 ,deadbeef,deadbeef.u32,11);
  CHECK_BITS_EQUAL(318,deadbeef.unnamed_0_31,0xdeadbeef);
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
    READ_FROM_BUFFER_FULL(330,uint32 ,channelids,channelids.u32,12);
    CHECK_BITS_EQUAL(326,channelids.unnamed_24_31,240);
    {
      typedef __typeof__(*(&(channel_trigger_time_hi))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = channel_trigger_time_hi.insert_index(329,channelids.channel_id_bits);
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
    READ_FROM_BUFFER_FULL(335,uint32 ,channel_ts,channel_ts.u32,13);
    {
      typedef __typeof__(*(&(channel_trigger_time_lo))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = channel_trigger_time_lo.insert_index(334,channelids.channel_id_bits);
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
    READ_FROM_BUFFER_FULL(347,uint32 ,chan_enrgy,chan_enrgy.u32,14);
    {
      {
        typedef __typeof__(*(&(channel_cfd))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_cfd.insert_index(343,channelids.channel_id_bits);
        __item.value = chan_enrgy.TSF;
      }
      {
        typedef __typeof__(*(&(channel_energy))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_energy.insert_index(344,channelids.channel_id_bits);
        __item.value = chan_enrgy.chan_energy;
      }
      {
        typedef __typeof__(*(&(pileup))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = pileup.insert_index(345,channelids.channel_id_bits);
        __item.value = chan_enrgy.pileup_flag;
      }
      {
        typedef __typeof__(*(&(overflow))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = overflow.insert_index(346,channelids.channel_id_bits);
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
    READ_FROM_BUFFER_FULL(351,uint32 ,future_use,future_use.u32,15);
    CHECK_BITS_EQUAL(350,future_use.unnamed_0_31,0);
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
  READ_FROM_BUFFER_FULL(382,uint32 ,sumchannel,sumchannel.u32,17);
  CHECK_BITS_EQUAL(376,sumchannel.unnamed_0_7,52);
  CHECK_BITS_EQUAL(379,sumchannel.board_id,card);
  CHECK_BITS_EQUAL(380,sumchannel.unnamed_24_31,255);
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
  READ_FROM_BUFFER_FULL(390,uint32 ,channel_size,channel_size.u32,18);
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
  READ_FROM_BUFFER_FULL(399,uint32 ,event_timestamp_hi,event_timestamp_hi.u32,19);
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
  READ_FROM_BUFFER_FULL(405,uint32 ,event_timestamp_lo,event_timestamp_lo.u32,20);
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
  READ_FROM_BUFFER_FULL(413,uint32 ,hp,hp.u32,21);
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
  READ_FROM_BUFFER_FULL(418,uint32 ,deadbeef,deadbeef.u32,22);
  CHECK_BITS_EQUAL(417,deadbeef.unnamed_0_31,0xdeadbeef);
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
      READ_FROM_BUFFER_FULL(431,uint32 ,channelids,channelids.u32,23);
      CHECK_BITS_EQUAL(427,channelids.unnamed_24_31,240);
      {
        {
          typedef __typeof__(*(&(channel_id))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_id.insert_index(429,index);
          __item.value = channelids.channel_id_bits;
        }
        {
          typedef __typeof__(*(&(channel_trigger_time_hi))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_trigger_time_hi.insert_index(430,index);
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
      READ_FROM_BUFFER_FULL(436,uint32 ,channel_ts,channel_ts.u32,24);
      {
        typedef __typeof__(*(&(channel_trigger_time_lo))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel_trigger_time_lo.insert_index(435,index);
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
      READ_FROM_BUFFER_FULL(448,uint32 ,chan_enrgy,chan_enrgy.u32,25);
      {
        {
          typedef __typeof__(*(&(channel_cfd))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_cfd.insert_index(444,index);
          __item.value = chan_enrgy.TSF;
        }
        {
          typedef __typeof__(*(&(channel_energy))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = channel_energy.insert_index(445,index);
          __item.value = chan_enrgy.chan_energy;
        }
        {
          typedef __typeof__(*(&(pileup))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = pileup.insert_index(446,index);
          __item.value = chan_enrgy.pileup_flag;
        }
        {
          typedef __typeof__(*(&(overflow))) __array_t;
          typedef typename __array_t::item_t __item_t;
          __item_t &__item = overflow.insert_index(447,index);
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
      READ_FROM_BUFFER_FULL(452,uint32 ,future_use,future_use.u32,26);
      CHECK_BITS_EQUAL(451,future_use.unnamed_0_31,0);
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: future_use ", CT_OUT(BOLD), future_use.u32, CT_OUT(NORM));
        printf("\n");
      }
    }
    // if((hp.hp != 0))

    if ((hp.hp != 0))
    {
      // list(0<=i<1)

      for (uint32 i = 0; i < (uint32) (1); ++i)
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
        READ_FROM_BUFFER_FULL(464,uint32 ,header,header.u32,27);
        CHECK_BITS_EQUAL(461,header.unnamed_0_7,52);
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
        READ_FROM_BUFFER_FULL(469,uint32 ,tracesize,tracesize.u32,28);
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
        READ_FROM_BUFFER_FULL(475,uint32 ,tracehead,tracehead.u32,29);
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
          READ_FROM_BUFFER_FULL(495,uint32 ,channel_trace,channel_trace.u32,30);
          {
            {
              typedef __typeof__(*(&(traces[header.ch_id]))) __array_t;
              typedef typename __array_t::item_t __item_t;
              __item_t &__item = traces[header.ch_id].insert_index(493,((2 * j) + 0));
              __item.value = channel_trace.data1;
            }
            {
              typedef __typeof__(*(&(traces[header.ch_id]))) __array_t;
              typedef typename __array_t::item_t __item_t;
              __item_t &__item = traces[header.ch_id].insert_index(494,((2 * j) + 1));
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
        READ_FROM_BUFFER_FULL(504,uint32 ,trace_trailer,trace_trailer.u32,31);
        CHECK_BITS_RANGE(503,trace_trailer.id,176,191);
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
        PEEK_FROM_BUFFER(514,uint32,__match_peek);
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
            CHECK_SPURIOUS_MATCH_DECL(513,spurious_match_abort_loop_0,DUMMY);
            UNPACK_DECL(513,DUMMY,dummy);
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
  READ_FROM_BUFFER_FULL(253,uint32 ,pads_data,pads_data.u32,33);
  CHECK_BITS_EQUAL(252,pads_data.unnamed_20_31,0xadd);
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
 * Event unpacker for VME_CAEN_V830_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V830_FRS()
template<typename __data_src_t>
void VME_CAEN_V830_FRS::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "VME_CAEN_V830_FRS",CT_OUT(NORM));
  }
  // MEMBER(DATA32 data[32] ZERO_SUPPRESS);
  // UINT32 v830_header NOENCODE
  // {
    //  0_15: trigger_number;
    // 16_17: ts;
    // 18_23: nwords;
    // 24_25: unused;
    //    26: 1;
    // 27_31: geo;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 trigger_number : 16; // 0..15
      uint32 ts : 2; // 16..17
      uint32 nwords : 6; // 18..23
      uint32 unused : 2; // 24..25
      uint32 unnamed_26_26 : 1; // 26
      uint32 geo : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 geo : 5; // 27..31
      uint32 unnamed_26_26 : 1; // 26
      uint32 unused : 2; // 24..25
      uint32 nwords : 6; // 18..23
      uint32 ts : 2; // 16..17
      uint32 trigger_number : 16; // 0..15
#endif
    };
    uint32  u32;
  } v830_header;
  READ_FROM_BUFFER_FULL(707,uint32 ,v830_header,v830_header.u32,35);
  CHECK_BITS_EQUAL(705,v830_header.unnamed_26_26,1);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: v830_header ", CT_OUT(BOLD), v830_header.u32, CT_OUT(NORM));
    printf(".trigger_number=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  v830_header.trigger_number, CT_OUT(NORM));
    printf(".ts=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  v830_header.ts, CT_OUT(NORM));
    printf(".nwords=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  v830_header.nwords, CT_OUT(NORM));
    printf(".unused=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  v830_header.unused, CT_OUT(NORM));
    printf(".geo=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  v830_header.geo, CT_OUT(NORM));
    printf("\n");
  }
  // list(0<=i<v830_header.nwords)

  for (uint32 i = 0; i < (uint32) (v830_header.nwords); ++i)
  {
    // UINT32 data_word NOENCODE
    // {
      //  0_31: value;
      // ENCODE(data[i],(value=value));
    // }
    union
    {
      struct
      {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint32 value : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32 value : 32; // 0..31
#endif
      };
      uint32  u32;
    } data_word;
    READ_FROM_BUFFER_FULL(715,uint32 ,data_word,data_word.u32,36);
    {
      typedef __typeof__(*(&(data))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = data.insert_index(714,i);
      __item.value = data_word.value;
    }
    if (__buffer.is_memberdump())
    {
      printf("%s%08" PRIx32 "%s: data_word ", CT_OUT(BOLD), data_word.u32, CT_OUT(NORM));
      printf(".value=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  data_word.value, CT_OUT(NORM));
      printf("\n");
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,VME_CAEN_V830_FRS::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for ZERO_FILLER.
 *
 * Do not edit - automatically generated.
 */

// ZERO_FILLER()
template<typename __data_src_t>
void ZERO_FILLER::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "ZERO_FILLER",CT_OUT(NORM));
  }
  // UINT32 filler NOENCODE
  // {
    //  0_31: zero = MATCH(0);
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 zero : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 zero : 32; // 0..31
#endif
    };
    uint32  u32;
  } filler;
  READ_FROM_BUFFER_FULL(1012,uint32 ,filler,filler.u32,38);
  CHECK_BITS_EQUAL(1011,filler.zero,0);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: filler ", CT_OUT(BOLD), filler.u32, CT_OUT(NORM));
    printf(".zero=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  filler.zero, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,ZERO_FILLER::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for VME_CAEN_V792_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V792_FRS()
template<typename __data_src_t>
void VME_CAEN_V792_FRS::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "VME_CAEN_V792_FRS",CT_OUT(NORM));
  }
  // MEMBER(DATA32 data[32] ZERO_SUPPRESS_MULTI(32));
  // MEMBER(DATA8 geo);
  // UINT32 v792_header NOENCODE
  // {
    //  0_07: unused;
    //  8_13: cnt;
    // 14_15: 0;
    // 16_23: crate;
    // 24_26: 2;
    // 27_31: geo;
    // ENCODE(geo,(value=geo));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 unused : 8; // 0..7
      uint32 cnt : 6; // 8..13
      uint32 unnamed_14_15 : 2; // 14..15
      uint32 crate : 8; // 16..23
      uint32 unnamed_24_26 : 3; // 24..26
      uint32 geo : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 geo : 5; // 27..31
      uint32 unnamed_24_26 : 3; // 24..26
      uint32 crate : 8; // 16..23
      uint32 unnamed_14_15 : 2; // 14..15
      uint32 cnt : 6; // 8..13
      uint32 unused : 8; // 0..7
#endif
    };
    uint32  u32;
  } v792_header;
  READ_FROM_BUFFER_FULL(735,uint32 ,v792_header,v792_header.u32,40);
  CHECK_BITS_EQUAL(730,v792_header.unnamed_14_15,0);
  CHECK_BITS_EQUAL(732,v792_header.unnamed_24_26,2);
  {
    geo.value = v792_header.geo;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: v792_header ", CT_OUT(BOLD), v792_header.u32, CT_OUT(NORM));
    printf(".unused=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  v792_header.unused, CT_OUT(NORM));
    printf(".cnt=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  v792_header.cnt, CT_OUT(NORM));
    printf(".crate=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  v792_header.crate, CT_OUT(NORM));
    printf(".geo=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  v792_header.geo, CT_OUT(NORM));
    printf("\n");
  }
  // several UINT32 adc_data NOENCODE
  // {
    //  0_11: adc;
    //    12: overflow;
    //    13: underthreshold;
    // 14_15: unused;
    // 16_20: channel;
    // 21_23: unused2;
    // 24_26: 0;
    // 27_31: geo;
    // ENCODE(data[channel],(value=adc));
  // }
  for ( ; ; ) {
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 adc : 12; // 0..11
      uint32 overflow : 1; // 12
      uint32 underthreshold : 1; // 13
      uint32 unused : 2; // 14..15
      uint32 channel : 5; // 16..20
      uint32 unused2 : 3; // 21..23
      uint32 unnamed_24_26 : 3; // 24..26
      uint32 geo : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 geo : 5; // 27..31
      uint32 unnamed_24_26 : 3; // 24..26
      uint32 unused2 : 3; // 21..23
      uint32 channel : 5; // 16..20
      uint32 unused : 2; // 14..15
      uint32 underthreshold : 1; // 13
      uint32 overflow : 1; // 12
      uint32 adc : 12; // 0..11
#endif
    };
    uint32  u32;
  } adc_data;
  if (__buffer.empty()) goto data_done_0;
  PEEK_FROM_BUFFER_FULL(751,uint32 ,adc_data,adc_data.u32,41);
  CHECK_JUMP_BITS_EQUAL(747,adc_data.unnamed_24_26,0,data_done_0);
  __buffer.advance(sizeof(adc_data.u32));
  {
    typedef __typeof__(*(&(data))) __array_t;
    typedef typename __array_t::item_t __item_t;
    __item_t &__item = data.insert_index(750,adc_data.channel);
    __item.value = adc_data.adc;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: adc_data ", CT_OUT(BOLD), adc_data.u32, CT_OUT(NORM));
    printf(".adc=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  adc_data.adc, CT_OUT(NORM));
    printf(".overflow=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  adc_data.overflow, CT_OUT(NORM));
    printf(".underthreshold=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  adc_data.underthreshold, CT_OUT(NORM));
    printf(".unused=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  adc_data.unused, CT_OUT(NORM));
    printf(".channel=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  adc_data.channel, CT_OUT(NORM));
    printf(".unused2=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  adc_data.unused2, CT_OUT(NORM));
    printf(".geo=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  adc_data.geo, CT_OUT(NORM));
    printf("\n");
  }
  }
  data_done_0:;
  // UINT32 eob NOENCODE
  // {
    //  0_23: nothing;
    // 24_26: 4;
    // 27_31: geom;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 nothing : 24; // 0..23
      uint32 unnamed_24_26 : 3; // 24..26
      uint32 geom : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 geom : 5; // 27..31
      uint32 unnamed_24_26 : 3; // 24..26
      uint32 nothing : 24; // 0..23
#endif
    };
    uint32  u32;
  } eob;
  READ_FROM_BUFFER_FULL(759,uint32 ,eob,eob.u32,42);
  CHECK_BITS_EQUAL(757,eob.unnamed_24_26,4);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: eob ", CT_OUT(BOLD), eob.u32, CT_OUT(NORM));
    printf(".nothing=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  eob.nothing, CT_OUT(NORM));
    printf(".geom=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  eob.geom, CT_OUT(NORM));
    printf("\n");
  }
  // list(0<=i<2)

  for (uint32 i = 0; i < (uint32) (2); ++i)
  {
    // optional UINT32 eob2 NOENCODE
    // {
      //  0_23: nothing;
      // 24_26: id = MATCH(6);
      // 27_31: geom;
    // }
    union
    {
      struct
      {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint32 nothing : 24; // 0..23
        uint32 id : 3; // 24..26
        uint32 geom : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32 geom : 5; // 27..31
        uint32 id : 3; // 24..26
        uint32 nothing : 24; // 0..23
#endif
      };
      uint32  u32;
    } eob2;
    if (__buffer.empty()) goto data_done_1;
    PEEK_FROM_BUFFER_FULL(768,uint32 ,eob2,eob2.u32,43);
    CHECK_JUMP_BITS_EQUAL(766,eob2.id,6,data_done_1);
    __buffer.advance(sizeof(eob2.u32));
    if (__buffer.is_memberdump())
    {
      printf("%s%08" PRIx32 "%s: eob2 ", CT_OUT(BOLD), eob2.u32, CT_OUT(NORM));
      printf(".nothing=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  eob2.nothing, CT_OUT(NORM));
      printf(".id=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  eob2.id, CT_OUT(NORM));
      printf(".geom=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  eob2.geom, CT_OUT(NORM));
      printf("\n");
    }
    data_done_1:;
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,VME_CAEN_V792_FRS::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TDC_HEADER.
 *
 * Do not edit - automatically generated.
 */

// TDC_HEADER()
template<typename __data_src_t>
void TDC_HEADER::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TDC_HEADER",CT_OUT(NORM));
  }
  // UINT32 tdc_header NOENCODE
  // {
    //  0_11: bunch_id;
    // 12_23: event_id;
    // 24_25: tdc;
    //    26: unused;
    // 27_31: 1;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 bunch_id : 12; // 0..11
      uint32 event_id : 12; // 12..23
      uint32 tdc : 2; // 24..25
      uint32 unused : 1; // 26
      uint32 unnamed_27_31 : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_27_31 : 5; // 27..31
      uint32 unused : 1; // 26
      uint32 tdc : 2; // 24..25
      uint32 event_id : 12; // 12..23
      uint32 bunch_id : 12; // 0..11
#endif
    };
    uint32  u32;
  } tdc_header;
  READ_FROM_BUFFER_FULL(532,uint32 ,tdc_header,tdc_header.u32,45);
  CHECK_BITS_EQUAL(531,tdc_header.unnamed_27_31,1);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: tdc_header ", CT_OUT(BOLD), tdc_header.u32, CT_OUT(NORM));
    printf(".bunch_id=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_header.bunch_id, CT_OUT(NORM));
    printf(".event_id=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_header.event_id, CT_OUT(NORM));
    printf(".tdc=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_header.tdc, CT_OUT(NORM));
    printf(".unused=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_header.unused, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,TDC_HEADER::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TDC_DATA_V1290.
 *
 * Do not edit - automatically generated.
 */

// TDC_DATA_V1290(data,leadOrTrail)
template<typename __data_src_t>
void TDC_DATA_V1290::__unpack(__data_src_t &__buffer,raw_array_multi_zero_suppress<DATA24,DATA24,128,128> &data
                                                    ,raw_array_multi_zero_suppress<DATA8,DATA8,128,128> &leadOrTrail)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TDC_DATA_V1290",CT_OUT(NORM));
  }
  // MEMBER(DATA24 data[128] ZERO_SUPPRESS_MULTI(128));
  // MEMBER(DATA8 leadOrTrail[128] ZERO_SUPPRESS_MULTI(128));
  // UINT32 tdc_data NOENCODE
  // {
    //  0_20: tdc;
    // 21_25: chn;
    //    26: lot;
    // 27_31: 0;
    // ENCODE(data[chn],(value=tdc));
    // ENCODE(leadOrTrail[chn],(value=lot));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 tdc : 21; // 0..20
      uint32 chn : 5; // 21..25
      uint32 lot : 1; // 26
      uint32 unnamed_27_31 : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_27_31 : 5; // 27..31
      uint32 lot : 1; // 26
      uint32 chn : 5; // 21..25
      uint32 tdc : 21; // 0..20
#endif
    };
    uint32  u32;
  } tdc_data;
  READ_FROM_BUFFER_FULL(548,uint32 ,tdc_data,tdc_data.u32,47);
  CHECK_BITS_EQUAL(544,tdc_data.unnamed_27_31,0);
  {
    {
      typedef __typeof__(*(&(data))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = data.insert_index(546,tdc_data.chn);
      __item.value = tdc_data.tdc;
    }
    {
      typedef __typeof__(*(&(leadOrTrail))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = leadOrTrail.insert_index(547,tdc_data.chn);
      __item.value = tdc_data.lot;
    }
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: tdc_data ", CT_OUT(BOLD), tdc_data.u32, CT_OUT(NORM));
    printf(".tdc=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_data.tdc, CT_OUT(NORM));
    printf(".chn=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_data.chn, CT_OUT(NORM));
    printf(".lot=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_data.lot, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TDC_DATA_V1290::__unpack,raw_array_multi_zero_suppress<DATA24,DATA24,128,128> &data
                                                         ,raw_array_multi_zero_suppress<DATA8,DATA8,128,128> &leadOrTrail);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TDC_ERROR.
 *
 * Do not edit - automatically generated.
 */

// TDC_ERROR()
template<typename __data_src_t>
void TDC_ERROR::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TDC_ERROR",CT_OUT(NORM));
  }
  // UINT32 tdc_err NOENCODE
  // {
    //  0_14: error_flags;
    // 15_23: unused1;
    // 24_25: tdc;
    //    26: unused2;
    // 27_31: 4;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 error_flags : 15; // 0..14
      uint32 unused1 : 9; // 15..23
      uint32 tdc : 2; // 24..25
      uint32 unused2 : 1; // 26
      uint32 unnamed_27_31 : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_27_31 : 5; // 27..31
      uint32 unused2 : 1; // 26
      uint32 tdc : 2; // 24..25
      uint32 unused1 : 9; // 15..23
      uint32 error_flags : 15; // 0..14
#endif
    };
    uint32  u32;
  } tdc_err;
  READ_FROM_BUFFER_FULL(577,uint32 ,tdc_err,tdc_err.u32,49);
  CHECK_BITS_EQUAL(576,tdc_err.unnamed_27_31,4);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: tdc_err ", CT_OUT(BOLD), tdc_err.u32, CT_OUT(NORM));
    printf(".error_flags=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_err.error_flags, CT_OUT(NORM));
    printf(".unused1=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_err.unused1, CT_OUT(NORM));
    printf(".tdc=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_err.tdc, CT_OUT(NORM));
    printf(".unused2=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_err.unused2, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,TDC_ERROR::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TDC_TRAILER.
 *
 * Do not edit - automatically generated.
 */

// TDC_TRAILER()
template<typename __data_src_t>
void TDC_TRAILER::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TDC_TRAILER",CT_OUT(NORM));
  }
  // UINT32 tdc_trailer NOENCODE
  // {
    //  0_11: word_count;
    // 12_23: event_id;
    // 24_25: tdc;
    //    26: unused;
    // 27_31: 3;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 word_count : 12; // 0..11
      uint32 event_id : 12; // 12..23
      uint32 tdc : 2; // 24..25
      uint32 unused : 1; // 26
      uint32 unnamed_27_31 : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_27_31 : 5; // 27..31
      uint32 unused : 1; // 26
      uint32 tdc : 2; // 24..25
      uint32 event_id : 12; // 12..23
      uint32 word_count : 12; // 0..11
#endif
    };
    uint32  u32;
  } tdc_trailer;
  READ_FROM_BUFFER_FULL(589,uint32 ,tdc_trailer,tdc_trailer.u32,51);
  CHECK_BITS_EQUAL(588,tdc_trailer.unnamed_27_31,3);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: tdc_trailer ", CT_OUT(BOLD), tdc_trailer.u32, CT_OUT(NORM));
    printf(".word_count=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_trailer.word_count, CT_OUT(NORM));
    printf(".event_id=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_trailer.event_id, CT_OUT(NORM));
    printf(".tdc=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_trailer.tdc, CT_OUT(NORM));
    printf(".unused=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_trailer.unused, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,TDC_TRAILER::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for VME_CAEN_V1290_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V1290_FRS()
template<typename __data_src_t>
void VME_CAEN_V1290_FRS::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "VME_CAEN_V1290_FRS",CT_OUT(NORM));
  }
  // MEMBER(DATA24 data[128] ZERO_SUPPRESS_MULTI(128));
  // MEMBER(DATA8 leadOrTrail[128] ZERO_SUPPRESS_MULTI(128));
  // UINT32 header NOENCODE
  // {
    //  0_04: geo;
    //  5_26: event_count;
    // 27_31: 8;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 geo : 5; // 0..4
      uint32 event_count : 22; // 5..26
      uint32 unnamed_27_31 : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_27_31 : 5; // 27..31
      uint32 event_count : 22; // 5..26
      uint32 geo : 5; // 0..4
#endif
    };
    uint32  u32;
  } header;
  READ_FROM_BUFFER_FULL(601,uint32 ,header,header.u32,53);
  CHECK_BITS_EQUAL(600,header.unnamed_27_31,8);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: header ", CT_OUT(BOLD), header.u32, CT_OUT(NORM));
    printf(".geo=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.geo, CT_OUT(NORM));
    printf(".event_count=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.event_count, CT_OUT(NORM));
    printf("\n");
  }
  // select several

    // tdc_header = TDC_HEADER();
    // measurement = TDC_DATA_V1290(data=data,leadOrTrail=leadOrTrail);
    // tdc_err = TDC_ERROR();
    // tdc_trailer = TDC_TRAILER();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TDC_HEADER tdc_header: (s32) => (0xf8000000,0x08000000)
    // optimized match 2: TDC_DATA_V1290 measurement: (s32) => (0xf8000000,0x00000000)
    // optimized match 3: TDC_ERROR tdc_err: (s32) => (0xf8000000,0x20000000)
    // optimized match 4: TDC_TRAILER tdc_trailer: (s32) => (0xf8000000,0x18000000)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(609,uint32,__match_peek);
    // differ = 38000000 : 27 28 29
    uint32 __match_index = 0 | /* 27,29 */ ((__match_peek >> 27) & 0x00000007);
    static const sint8 __match_index_array[8] = { 2, 1, 0, 4, 3, 0, 0, 0, };
    __match_no = __match_index_array[__match_index];
    // last_subevent_item = 0
    }
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        CHECK_SPURIOUS_MATCH_DECL(605,spurious_match_abort_loop_1,TDC_HEADER);
        UNPACK_DECL(605,TDC_HEADER,tdc_header);
        break;
      case 2:
        CHECK_SPURIOUS_MATCH_DECL(606,spurious_match_abort_loop_1,TDC_DATA_V1290/*,data:member*//*,leadOrTrail:member*/);
        UNPACK_DECL(606,TDC_DATA_V1290,measurement,/*data*/data,/*leadOrTrail*/leadOrTrail);
        break;
      case 3:
        CHECK_SPURIOUS_MATCH_DECL(607,spurious_match_abort_loop_1,TDC_ERROR);
        UNPACK_DECL(607,TDC_ERROR,tdc_err);
        break;
      case 4:
        CHECK_SPURIOUS_MATCH_DECL(608,spurious_match_abort_loop_1,TDC_TRAILER);
        UNPACK_DECL(608,TDC_TRAILER,tdc_trailer);
        break;
    }
  }
  spurious_match_abort_loop_1:;
  // optional UINT32 ext_time_tag NOENCODE
  // {
    //  0_26: time_tag;
    // 27_31: 17;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 time_tag : 27; // 0..26
      uint32 unnamed_27_31 : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_27_31 : 5; // 27..31
      uint32 time_tag : 27; // 0..26
#endif
    };
    uint32  u32;
  } ext_time_tag;
  if (__buffer.empty()) goto data_done_2;
  PEEK_FROM_BUFFER_FULL(616,uint32 ,ext_time_tag,ext_time_tag.u32,54);
  CHECK_JUMP_BITS_EQUAL(615,ext_time_tag.unnamed_27_31,17,data_done_2);
  __buffer.advance(sizeof(ext_time_tag.u32));
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: ext_time_tag ", CT_OUT(BOLD), ext_time_tag.u32, CT_OUT(NORM));
    printf(".time_tag=%s%7" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ext_time_tag.time_tag, CT_OUT(NORM));
    printf("\n");
  }
  data_done_2:;
  // UINT32 trailer NOENCODE
  // {
    //  0_04: geo;
    //  5_20: word_count;
    // 21_23: unused;
    //    24: tdc_error;
    //    25: overflow;
    //    26: trigger_lost;
    // 27_31: 16;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 geo : 5; // 0..4
      uint32 word_count : 16; // 5..20
      uint32 unused : 3; // 21..23
      uint32 tdc_error : 1; // 24
      uint32 overflow : 1; // 25
      uint32 trigger_lost : 1; // 26
      uint32 unnamed_27_31 : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_27_31 : 5; // 27..31
      uint32 trigger_lost : 1; // 26
      uint32 overflow : 1; // 25
      uint32 tdc_error : 1; // 24
      uint32 unused : 3; // 21..23
      uint32 word_count : 16; // 5..20
      uint32 geo : 5; // 0..4
#endif
    };
    uint32  u32;
  } trailer;
  READ_FROM_BUFFER_FULL(627,uint32 ,trailer,trailer.u32,55);
  CHECK_BITS_EQUAL(626,trailer.unnamed_27_31,16);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: trailer ", CT_OUT(BOLD), trailer.u32, CT_OUT(NORM));
    printf(".geo=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.geo, CT_OUT(NORM));
    printf(".word_count=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.word_count, CT_OUT(NORM));
    printf(".unused=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.unused, CT_OUT(NORM));
    printf(".tdc_error=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.tdc_error, CT_OUT(NORM));
    printf(".overflow=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.overflow, CT_OUT(NORM));
    printf(".trigger_lost=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.trigger_lost, CT_OUT(NORM));
    printf("\n");
  }
  // optional UINT32 eob NOENCODE;
  uint32  eob;if (__buffer.empty()) goto data_done_3;
  READ_FROM_BUFFER(629,uint32 ,eob,56);
  data_done_3:;
}
FORCE_IMPL_DATA_SRC_FCN(void,VME_CAEN_V1290_FRS::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for MAIN_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// MAIN_CRATE_DATA()
template<typename __data_src_t>
void MAIN_CRATE_DATA::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "MAIN_CRATE_DATA",CT_OUT(NORM));
  }
  // barrier[0] = BARRIER();
  UNPACK_DECL(1020,BARRIER,barrier[0]);
  // v830 = VME_CAEN_V830_FRS();
  UNPACK_DECL(1021,VME_CAEN_V830_FRS,v830);
  // filler[0] = ZERO_FILLER();
  UNPACK_DECL(1023,ZERO_FILLER,filler[0]);
  // barrier[1] = BARRIER();
  UNPACK_DECL(1024,BARRIER,barrier[1]);
  // v792 = VME_CAEN_V792_FRS();
  UNPACK_DECL(1025,VME_CAEN_V792_FRS,v792);
  // barrier[2] = BARRIER();
  UNPACK_DECL(1027,BARRIER,barrier[2]);
  // v1290 = VME_CAEN_V1290_FRS();
  UNPACK_DECL(1028,VME_CAEN_V1290_FRS,v1290);
}
FORCE_IMPL_DATA_SRC_FCN(void,MAIN_CRATE_DATA::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for MESYTEC_MQDC32_FRS.
 *
 * Do not edit - automatically generated.
 */

// MESYTEC_MQDC32_FRS()
template<typename __data_src_t>
void MESYTEC_MQDC32_FRS::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "MESYTEC_MQDC32_FRS",CT_OUT(NORM));
  }
  // MEMBER(DATA12_OVERFLOW data[32] ZERO_SUPPRESS);
  // UINT32 header NOENCODE
  // {
    //  0_11: word_number;
    // 12_14: 0;
    // 16_23: geom;
    // 24_29: 0;
    // 30_31: 1;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 word_number : 12; // 0..11
      uint32 unnamed_12_14 : 3; // 12..14
      uint32 dummy_15 : 1;
      uint32 geom : 8; // 16..23
      uint32 unnamed_24_29 : 6; // 24..29
      uint32 unnamed_30_31 : 2; // 30..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_30_31 : 2; // 30..31
      uint32 unnamed_24_29 : 6; // 24..29
      uint32 geom : 8; // 16..23
      uint32 dummy_15 : 1;
      uint32 unnamed_12_14 : 3; // 12..14
      uint32 word_number : 12; // 0..11
#endif
    };
    uint32  u32;
  } header;
  READ_FROM_BUFFER_FULL(839,uint32 ,header,header.u32,58);
  CHECK_BITS_EQUAL(835,header.unnamed_12_14,0);
  CHECK_BITS_EQUAL(837,header.unnamed_24_29,0);
  CHECK_BITS_EQUAL(838,header.unnamed_30_31,1);
  CHECK_UNNAMED_BITS_ZERO(839,header.u32,0x00008000);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: header ", CT_OUT(BOLD), header.u32, CT_OUT(NORM));
    printf(".word_number=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.word_number, CT_OUT(NORM));
    printf(".geom=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.geom, CT_OUT(NORM));
    printf("\n");
  }
  // several UINT32 ch_data NOENCODE
  // {
    //  0_11: value;
    //    15: outofrange;
    // 16_20: channel;
    // 21_29: 32;
    // 30_31: 0;
    // ENCODE(data[channel],(value=value,overflow=outofrange));
  // }
  for ( ; ; ) {
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 value : 12; // 0..11
      uint32 dummy_12_14 : 3;
      uint32 outofrange : 1; // 15
      uint32 channel : 5; // 16..20
      uint32 unnamed_21_29 : 9; // 21..29
      uint32 unnamed_30_31 : 2; // 30..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_30_31 : 2; // 30..31
      uint32 unnamed_21_29 : 9; // 21..29
      uint32 channel : 5; // 16..20
      uint32 outofrange : 1; // 15
      uint32 dummy_12_14 : 3;
      uint32 value : 12; // 0..11
#endif
    };
    uint32  u32;
  } ch_data;
  if (__buffer.empty()) goto data_done_4;
  PEEK_FROM_BUFFER_FULL(850,uint32 ,ch_data,ch_data.u32,59);
  CHECK_JUMP_BITS_EQUAL(846,ch_data.unnamed_21_29,32,data_done_4);
  CHECK_JUMP_BITS_EQUAL(847,ch_data.unnamed_30_31,0,data_done_4);
  CHECK_JUMP_UNNAMED_BITS_ZERO(850,ch_data.u32,0x00007000,data_done_4);
  __buffer.advance(sizeof(ch_data.u32));
  {
    typedef __typeof__(*(&(data))) __array_t;
    typedef typename __array_t::item_t __item_t;
    __item_t &__item = data.insert_index(849,ch_data.channel);
    __item.value = ch_data.value;
    __item.overflow = ch_data.outofrange;
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: ch_data ", CT_OUT(BOLD), ch_data.u32, CT_OUT(NORM));
    printf(".value=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.value, CT_OUT(NORM));
    printf(".outofrange=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.outofrange, CT_OUT(NORM));
    printf(".channel=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.channel, CT_OUT(NORM));
    printf("\n");
  }
  }
  data_done_4:;
  // optional UINT32 zero NOENCODE
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
  } zero;
  if (__buffer.empty()) goto data_done_5;
  PEEK_FROM_BUFFER_FULL(855,uint32 ,zero,zero.u32,60);
  CHECK_JUMP_BITS_EQUAL(854,zero.unnamed_0_31,0,data_done_5);
  __buffer.advance(sizeof(zero.u32));
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: zero ", CT_OUT(BOLD), zero.u32, CT_OUT(NORM));
    printf("\n");
  }
  data_done_5:;
  // UINT32 end_of_event NOENCODE
  // {
    //  0_29: counter;
    // 30_31: 3;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 counter : 30; // 0..29
      uint32 unnamed_30_31 : 2; // 30..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_30_31 : 2; // 30..31
      uint32 counter : 30; // 0..29
#endif
    };
    uint32  u32;
  } end_of_event;
  READ_FROM_BUFFER_FULL(861,uint32 ,end_of_event,end_of_event.u32,61);
  CHECK_BITS_EQUAL(860,end_of_event.unnamed_30_31,3);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: end_of_event ", CT_OUT(BOLD), end_of_event.u32, CT_OUT(NORM));
    printf(".counter=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  end_of_event.counter, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,MESYTEC_MQDC32_FRS::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for MESYTEC_MTDC32_FRS.
 *
 * Do not edit - automatically generated.
 */

// MESYTEC_MTDC32_FRS()
template<typename __data_src_t>
void MESYTEC_MTDC32_FRS::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "MESYTEC_MTDC32_FRS",CT_OUT(NORM));
  }
  // MEMBER(DATA16 data[34] ZERO_SUPPRESS);
  // UINT32 header NOENCODE
  // {
    //  0_11: word_number;
    // 12_15: tdc_resol;
    // 16_23: geom;
    // 24_29: 0;
    // 30_31: 1;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 word_number : 12; // 0..11
      uint32 tdc_resol : 4; // 12..15
      uint32 geom : 8; // 16..23
      uint32 unnamed_24_29 : 6; // 24..29
      uint32 unnamed_30_31 : 2; // 30..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_30_31 : 2; // 30..31
      uint32 unnamed_24_29 : 6; // 24..29
      uint32 geom : 8; // 16..23
      uint32 tdc_resol : 4; // 12..15
      uint32 word_number : 12; // 0..11
#endif
    };
    uint32  u32;
  } header;
  READ_FROM_BUFFER_FULL(877,uint32 ,header,header.u32,63);
  CHECK_BITS_EQUAL(875,header.unnamed_24_29,0);
  CHECK_BITS_EQUAL(876,header.unnamed_30_31,1);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: header ", CT_OUT(BOLD), header.u32, CT_OUT(NORM));
    printf(".word_number=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.word_number, CT_OUT(NORM));
    printf(".tdc_resol=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.tdc_resol, CT_OUT(NORM));
    printf(".geom=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.geom, CT_OUT(NORM));
    printf("\n");
  }
  // list(1<=index<header.word_number)

  for (uint32 index = 1; index < (uint32) (header.word_number); ++index)
  {
    // optional UINT32 zero NOENCODE
    // {
      //  0_31: ze = MATCH(0);
    // }
    union
    {
      struct
      {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint32 ze : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32 ze : 32; // 0..31
#endif
      };
      uint32  u32;
    } zero;
    if (__buffer.empty()) goto data_done_6;
    PEEK_FROM_BUFFER_FULL(885,uint32 ,zero,zero.u32,64);
    CHECK_JUMP_BITS_EQUAL(884,zero.ze,0,data_done_6);
    __buffer.advance(sizeof(zero.u32));
    if (__buffer.is_memberdump())
    {
      printf("%s%08" PRIx32 "%s: zero ", CT_OUT(BOLD), zero.u32, CT_OUT(NORM));
      printf(".ze=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  zero.ze, CT_OUT(NORM));
      printf("\n");
    }
    data_done_6:;
    // if((zero.ze != 0))

    if ((zero.ze != 0))
    {
      // UINT32 ch_data NOENCODE
      // {
        //  0_15: value;
        // 16_20: channel;
        //    21: trig;
        // 22_29: 16;
        // 30_31: 0;
        // ENCODE(data[((trig * 32) + channel)],(value=value));
      // }
      union
      {
        struct
        {
#if __BYTE_ORDER == __LITTLE_ENDIAN
          uint32 value : 16; // 0..15
          uint32 channel : 5; // 16..20
          uint32 trig : 1; // 21
          uint32 unnamed_22_29 : 8; // 22..29
          uint32 unnamed_30_31 : 2; // 30..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
          uint32 unnamed_30_31 : 2; // 30..31
          uint32 unnamed_22_29 : 8; // 22..29
          uint32 trig : 1; // 21
          uint32 channel : 5; // 16..20
          uint32 value : 16; // 0..15
#endif
        };
        uint32  u32;
      } ch_data;
      READ_FROM_BUFFER_FULL(898,uint32 ,ch_data,ch_data.u32,65);
      CHECK_BITS_EQUAL(894,ch_data.unnamed_22_29,16);
      CHECK_BITS_EQUAL(895,ch_data.unnamed_30_31,0);
      {
        typedef __typeof__(*(&(data))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = data.insert_index(897,((ch_data.trig * 32) + ch_data.channel));
        __item.value = ch_data.value;
      }
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: ch_data ", CT_OUT(BOLD), ch_data.u32, CT_OUT(NORM));
        printf(".value=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.value, CT_OUT(NORM));
        printf(".channel=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.channel, CT_OUT(NORM));
        printf(".trig=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.trig, CT_OUT(NORM));
        printf("\n");
      }
    }
  }
  // UINT32 end_of_event NOENCODE
  // {
    //  0_29: counter;
    // 30_31: 3;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 counter : 30; // 0..29
      uint32 unnamed_30_31 : 2; // 30..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_30_31 : 2; // 30..31
      uint32 counter : 30; // 0..29
#endif
    };
    uint32  u32;
  } end_of_event;
  READ_FROM_BUFFER_FULL(907,uint32 ,end_of_event,end_of_event.u32,66);
  CHECK_BITS_EQUAL(906,end_of_event.unnamed_30_31,3);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: end_of_event ", CT_OUT(BOLD), end_of_event.u32, CT_OUT(NORM));
    printf(".counter=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  end_of_event.counter, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,MESYTEC_MTDC32_FRS::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for SIS_3820_FRS.
 *
 * Do not edit - automatically generated.
 */

// SIS_3820_FRS()
template<typename __data_src_t>
void SIS_3820_FRS::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "SIS_3820_FRS",CT_OUT(NORM));
  }
  // MEMBER(DATA32 data[32] ZERO_SUPPRESS);
  // UINT32 custom_header NOENCODE
  // {
    //  0_07: nchs;
    //  8_21: nevts;
    //    22: latching;
    // 23_26: data_format;
    // 27_31: id;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 nchs : 8; // 0..7
      uint32 nevts : 14; // 8..21
      uint32 latching : 1; // 22
      uint32 data_format : 4; // 23..26
      uint32 id : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 id : 5; // 27..31
      uint32 data_format : 4; // 23..26
      uint32 latching : 1; // 22
      uint32 nevts : 14; // 8..21
      uint32 nchs : 8; // 0..7
#endif
    };
    uint32  u32;
  } custom_header;
  READ_FROM_BUFFER_FULL(923,uint32 ,custom_header,custom_header.u32,68);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: custom_header ", CT_OUT(BOLD), custom_header.u32, CT_OUT(NORM));
    printf(".nchs=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  custom_header.nchs, CT_OUT(NORM));
    printf(".nevts=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  custom_header.nevts, CT_OUT(NORM));
    printf(".latching=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  custom_header.latching, CT_OUT(NORM));
    printf(".data_format=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  custom_header.data_format, CT_OUT(NORM));
    printf(".id=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  custom_header.id, CT_OUT(NORM));
    printf("\n");
  }
  // list(0<=index<custom_header.nchs)

  for (uint32 index = 0; index < (uint32) (custom_header.nchs); ++index)
  {
    // if((1 == custom_header.data_format))

    if ((1 == custom_header.data_format))
    {
      // UINT32 event NOENCODE
      // {
        //  0_31: val;
      // }
      union
      {
        struct
        {
#if __BYTE_ORDER == __LITTLE_ENDIAN
          uint32 val : 32; // 0..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
          uint32 val : 32; // 0..31
#endif
        };
        uint32  u32;
      } event;
      READ_FROM_BUFFER_FULL(929,uint32 ,event,event.u32,69);
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: event ", CT_OUT(BOLD), event.u32, CT_OUT(NORM));
        printf(".val=%s%8" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event.val, CT_OUT(NORM));
        printf("\n");
      }
      // ENCODE(data[index],(value=event.val));

      {
        typedef __typeof__(*(&(data))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = data.insert_index(930,index);
        __item.value = event.val;
      }
    }
    // if(((0 == custom_header.data_format) || (3 == custom_header.data_format)))

    if (((0 == custom_header.data_format) || (3 == custom_header.data_format)))
    {
      // UINT32 event NOENCODE
      // {
        //  0_23: val;
        // 24_28: channel;
        //    29: 0;
        // 30_31: user_bits;
      // }
      union
      {
        struct
        {
#if __BYTE_ORDER == __LITTLE_ENDIAN
          uint32 val : 24; // 0..23
          uint32 channel : 5; // 24..28
          uint32 unnamed_29_29 : 1; // 29
          uint32 user_bits : 2; // 30..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
          uint32 user_bits : 2; // 30..31
          uint32 unnamed_29_29 : 1; // 29
          uint32 channel : 5; // 24..28
          uint32 val : 24; // 0..23
#endif
        };
        uint32  u32;
      } event;
      READ_FROM_BUFFER_FULL(938,uint32 ,event,event.u32,70);
      CHECK_BITS_EQUAL(936,event.unnamed_29_29,0);
      if (__buffer.is_memberdump())
      {
        printf("%s%08" PRIx32 "%s: event ", CT_OUT(BOLD), event.u32, CT_OUT(NORM));
        printf(".val=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event.val, CT_OUT(NORM));
        printf(".channel=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event.channel, CT_OUT(NORM));
        printf(".user_bits=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event.user_bits, CT_OUT(NORM));
        printf("\n");
      }
      // ENCODE(data[event.channel],(value=event.val));

      {
        typedef __typeof__(*(&(data))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = data.insert_index(939,event.channel);
        __item.value = event.val;
      }
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,SIS_3820_FRS::__unpack);

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
  READ_FROM_BUFFER_FULL(168,uint32 ,data,data.u32,72);
  CHECK_BITS_EQUAL(161,data.unnamed_28_31,6);
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
  READ_FROM_BUFFER_FULL(112,uint32 ,trigger_window,trigger_window.u32,74);
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
  READ_FROM_BUFFER_FULL(122,uint32 ,padding,padding.u32,76);
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
  READ_FROM_BUFFER_FULL(146,uint32 ,data,data.u32,78);
  CHECK_BITS_EQUAL(139,data.type,8);
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
  READ_FROM_BUFFER_FULL(187,uint32 ,indicator,indicator.u32,80);
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
  READ_FROM_BUFFER_FULL(196,uint32 ,data_size,data_size.u32,81);
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
  READ_FROM_BUFFER_FULL(204,uint32 ,tdc_header,tdc_header.u32,82);
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
      PEEK_FROM_BUFFER(210,uint32,__match_peek);
      // differ = e0000000 : 29 30 31
      uint32 __match_index = 0 | /* 29,31 */ ((__match_peek >> 29) & 0x00000007);
      static const sint8 __match_index_array[8] = { 0, 0, 0, 1, 2, 0, 0, 0, };
      __match_no = __match_index_array[__match_index];
      // last_subevent_item = 0
      }
      if (!__match_no) ERROR_U_LOC(210,"No match for select statement.");
      switch (__match_no)
      {
        case 1:
          CHECK_SPURIOUS_MATCH_DECL(208,spurious_match_abort_loop_2,TAMEX4_EPOCH_DATA,/*sfp*/sfp,/*card*/card/*,time_coarse:member*//*,time_fine:member*//*,time_edge:member*//*,time_channel:member*//*,time_epoch:member*/);
          UNPACK_DECL(208,TAMEX4_EPOCH_DATA,epoch,/*sfp*/sfp,/*card*/card,/*time_coarse*/time_coarse,/*time_fine*/time_fine,/*time_edge*/time_edge,/*time_channel*/time_channel,/*time_epoch*/time_epoch);
          break;
        case 2:
          CHECK_SPURIOUS_MATCH_DECL(209,spurious_match_abort_loop_2,TAMEX4_TIME_DATA,/*sfp*/sfp,/*card*/card/*,time_coarse:member*//*,time_fine:member*//*,time_edge:member*//*,time_channel:member*//*,time_epoch:member*/);
          UNPACK_DECL(209,TAMEX4_TIME_DATA,time,/*sfp*/sfp,/*card*/card,/*time_coarse*/time_coarse,/*time_fine*/time_fine,/*time_edge*/time_edge,/*time_channel*/time_channel,/*time_epoch*/time_epoch);
          break;
      }
    }
    while (0);
    spurious_match_abort_loop_2:;
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
  READ_FROM_BUFFER_FULL(216,uint32 ,error_bits,error_bits.u32,83);
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
  READ_FROM_BUFFER_FULL(224,uint32 ,trailer,trailer.u32,84);
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
 * Event unpacker for TDC_DATA_V1190.
 *
 * Do not edit - automatically generated.
 */

// TDC_DATA_V1190(data,leadOrTrail)
template<typename __data_src_t>
void TDC_DATA_V1190::__unpack(__data_src_t &__buffer,raw_array_multi_zero_suppress<DATA24,DATA24,128,128> &data
                                                    ,raw_array_multi_zero_suppress<DATA8,DATA8,128,128> &leadOrTrail)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TDC_DATA_V1190",CT_OUT(NORM));
  }
  // MEMBER(DATA24 data[128] ZERO_SUPPRESS_MULTI(128));
  // MEMBER(DATA8 leadOrTrail[128] ZERO_SUPPRESS_MULTI(128));
  // UINT32 tdc_data NOENCODE
  // {
    //  0_18: tdc;
    // 19_25: chn;
    //    26: lot;
    // 27_31: 0;
    // ENCODE(data[chn],(value=tdc));
    // ENCODE(leadOrTrail[chn],(value=lot));
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 tdc : 19; // 0..18
      uint32 chn : 7; // 19..25
      uint32 lot : 1; // 26
      uint32 unnamed_27_31 : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_27_31 : 5; // 27..31
      uint32 lot : 1; // 26
      uint32 chn : 7; // 19..25
      uint32 tdc : 19; // 0..18
#endif
    };
    uint32  u32;
  } tdc_data;
  READ_FROM_BUFFER_FULL(565,uint32 ,tdc_data,tdc_data.u32,86);
  CHECK_BITS_EQUAL(560,tdc_data.unnamed_27_31,0);
  {
    {
      typedef __typeof__(*(&(data))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = data.insert_index(562,tdc_data.chn);
      __item.value = tdc_data.tdc;
    }
    {
      typedef __typeof__(*(&(leadOrTrail))) __array_t;
      typedef typename __array_t::item_t __item_t;
      __item_t &__item = leadOrTrail.insert_index(563,tdc_data.chn);
      __item.value = tdc_data.lot;
    }
  }
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: tdc_data ", CT_OUT(BOLD), tdc_data.u32, CT_OUT(NORM));
    printf(".tdc=%s%5" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_data.tdc, CT_OUT(NORM));
    printf(".chn=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_data.chn, CT_OUT(NORM));
    printf(".lot=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  tdc_data.lot, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TDC_DATA_V1190::__unpack,raw_array_multi_zero_suppress<DATA24,DATA24,128,128> &data
                                                         ,raw_array_multi_zero_suppress<DATA8,DATA8,128,128> &leadOrTrail);

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
  READ_FROM_BUFFER_FULL(24,uint32 ,header,header.u32,88);
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
  READ_FROM_BUFFER_FULL(29,uint32 ,d1,d1.u32,89);
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
  READ_FROM_BUFFER_FULL(34,uint32 ,d2,d2.u32,90);
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
  READ_FROM_BUFFER_FULL(39,uint32 ,d3,d3.u32,91);
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
  READ_FROM_BUFFER_FULL(44,uint32 ,d4,d4.u32,92);
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
  READ_FROM_BUFFER_FULL(61,uint32 ,header,header.u32,94);
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
  READ_FROM_BUFFER_FULL(66,uint32 ,d1,d1.u32,95);
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
  READ_FROM_BUFFER_FULL(71,uint32 ,d2,d2.u32,96);
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
  READ_FROM_BUFFER_FULL(76,uint32 ,d3,d3.u32,97);
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
  READ_FROM_BUFFER_FULL(81,uint32 ,d4,d4.u32,98);
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
 * Event unpacker for VME_CAEN_V7X5_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V7X5_FRS()
template<typename __data_src_t>
void VME_CAEN_V7X5_FRS::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "VME_CAEN_V7X5_FRS",CT_OUT(NORM));
  }
  // MEMBER(DATA24 data[32] ZERO_SUPPRESS);
  // MEMBER(DATA8 channel[32] ZERO_SUPPRESS);
  // MEMBER(DATA8 geo[32] ZERO_SUPPRESS);
  // UINT32 header NOENCODE
  // {
    //  0_07: undefined;
    //  8_13: count;
    // 16_23: crate;
    // 24_26: 2;
    // 27_31: geom;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 undefined : 8; // 0..7
      uint32 count : 6; // 8..13
      uint32 dummy_14_15 : 2;
      uint32 crate : 8; // 16..23
      uint32 unnamed_24_26 : 3; // 24..26
      uint32 geom : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 geom : 5; // 27..31
      uint32 unnamed_24_26 : 3; // 24..26
      uint32 crate : 8; // 16..23
      uint32 dummy_14_15 : 2;
      uint32 count : 6; // 8..13
      uint32 undefined : 8; // 0..7
#endif
    };
    uint32  u32;
  } header;
  READ_FROM_BUFFER_FULL(786,uint32 ,header,header.u32,100);
  CHECK_BITS_EQUAL(784,header.unnamed_24_26,2);
  CHECK_UNNAMED_BITS_ZERO(786,header.u32,0x0000c000);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: header ", CT_OUT(BOLD), header.u32, CT_OUT(NORM));
    printf(".undefined=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.undefined, CT_OUT(NORM));
    printf(".count=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.count, CT_OUT(NORM));
    printf(".crate=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.crate, CT_OUT(NORM));
    printf(".geom=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.geom, CT_OUT(NORM));
    printf("\n");
  }
  // list(0<=index<header.count)

  for (uint32 index = 0; index < (uint32) (header.count); ++index)
  {
    // UINT32 ch_data NOENCODE
    // {
      //  0_11: value;
      //    12: overflow;
      //    13: underflow;
      //    14: valid;
      //    15: undefined;
      // 16_20: channel;
      // 21_23: undefined2;
      // 24_26: 0;
      // 27_31: geom;
      // ENCODE(geo[index],(value=geom));
      // ENCODE(channel[index],(value=channel));
      // ENCODE(data[index],(value=value));
    // }
    union
    {
      struct
      {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint32 value : 12; // 0..11
        uint32 overflow : 1; // 12
        uint32 underflow : 1; // 13
        uint32 valid : 1; // 14
        uint32 undefined : 1; // 15
        uint32 channel : 5; // 16..20
        uint32 undefined2 : 3; // 21..23
        uint32 unnamed_24_26 : 3; // 24..26
        uint32 geom : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32 geom : 5; // 27..31
        uint32 unnamed_24_26 : 3; // 24..26
        uint32 undefined2 : 3; // 21..23
        uint32 channel : 5; // 16..20
        uint32 undefined : 1; // 15
        uint32 valid : 1; // 14
        uint32 underflow : 1; // 13
        uint32 overflow : 1; // 12
        uint32 value : 12; // 0..11
#endif
      };
      uint32  u32;
    } ch_data;
    READ_FROM_BUFFER_FULL(805,uint32 ,ch_data,ch_data.u32,101);
    CHECK_BITS_EQUAL(799,ch_data.unnamed_24_26,0);
    {
      {
        typedef __typeof__(*(&(geo))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = geo.insert_index(802,index);
        __item.value = ch_data.geom;
      }
      {
        typedef __typeof__(*(&(channel))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = channel.insert_index(803,index);
        __item.value = ch_data.channel;
      }
      {
        typedef __typeof__(*(&(data))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = data.insert_index(804,index);
        __item.value = ch_data.value;
      }
    }
    if (__buffer.is_memberdump())
    {
      printf("%s%08" PRIx32 "%s: ch_data ", CT_OUT(BOLD), ch_data.u32, CT_OUT(NORM));
      printf(".value=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.value, CT_OUT(NORM));
      printf(".overflow=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.overflow, CT_OUT(NORM));
      printf(".underflow=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.underflow, CT_OUT(NORM));
      printf(".valid=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.valid, CT_OUT(NORM));
      printf(".undefined=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.undefined, CT_OUT(NORM));
      printf(".channel=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.channel, CT_OUT(NORM));
      printf(".undefined2=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.undefined2, CT_OUT(NORM));
      printf(".geom=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ch_data.geom, CT_OUT(NORM));
      printf("\n");
    }
  }
  // UINT32 eob NOENCODE
  // {
    //  0_23: nothing;
    // 24_26: 4;
    // 27_31: geom;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 nothing : 24; // 0..23
      uint32 unnamed_24_26 : 3; // 24..26
      uint32 geom : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 geom : 5; // 27..31
      uint32 unnamed_24_26 : 3; // 24..26
      uint32 nothing : 24; // 0..23
#endif
    };
    uint32  u32;
  } eob;
  READ_FROM_BUFFER_FULL(813,uint32 ,eob,eob.u32,102);
  CHECK_BITS_EQUAL(811,eob.unnamed_24_26,4);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: eob ", CT_OUT(BOLD), eob.u32, CT_OUT(NORM));
    printf(".nothing=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  eob.nothing, CT_OUT(NORM));
    printf(".geom=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  eob.geom, CT_OUT(NORM));
    printf("\n");
  }
  // list(0<=i<2)

  for (uint32 i = 0; i < (uint32) (2); ++i)
  {
    // optional UINT32 eob2 NOENCODE
    // {
      //  0_23: nothing;
      // 24_26: id = MATCH(6);
      // 27_31: geom;
    // }
    union
    {
      struct
      {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint32 nothing : 24; // 0..23
        uint32 id : 3; // 24..26
        uint32 geom : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32 geom : 5; // 27..31
        uint32 id : 3; // 24..26
        uint32 nothing : 24; // 0..23
#endif
      };
      uint32  u32;
    } eob2;
    if (__buffer.empty()) goto data_done_7;
    PEEK_FROM_BUFFER_FULL(822,uint32 ,eob2,eob2.u32,103);
    CHECK_JUMP_BITS_EQUAL(820,eob2.id,6,data_done_7);
    __buffer.advance(sizeof(eob2.u32));
    if (__buffer.is_memberdump())
    {
      printf("%s%08" PRIx32 "%s: eob2 ", CT_OUT(BOLD), eob2.u32, CT_OUT(NORM));
      printf(".nothing=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  eob2.nothing, CT_OUT(NORM));
      printf(".id=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  eob2.id, CT_OUT(NORM));
      printf(".geom=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  eob2.geom, CT_OUT(NORM));
      printf("\n");
    }
    data_done_7:;
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,VME_CAEN_V7X5_FRS::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for VME_CAEN_V1190_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V1190_FRS()
template<typename __data_src_t>
void VME_CAEN_V1190_FRS::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "VME_CAEN_V1190_FRS",CT_OUT(NORM));
  }
  // MEMBER(DATA24 data[128] ZERO_SUPPRESS_MULTI(128));
  // MEMBER(DATA8 leadOrTrail[128] ZERO_SUPPRESS_MULTI(128));
  // UINT32 header NOENCODE
  // {
    //  0_04: geo;
    //  5_26: event_count;
    // 27_31: seven_f;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 geo : 5; // 0..4
      uint32 event_count : 22; // 5..26
      uint32 seven_f : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 seven_f : 5; // 27..31
      uint32 event_count : 22; // 5..26
      uint32 geo : 5; // 0..4
#endif
    };
    uint32  u32;
  } header;
  READ_FROM_BUFFER_FULL(646,uint32 ,header,header.u32,105);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: header ", CT_OUT(BOLD), header.u32, CT_OUT(NORM));
    printf(".geo=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.geo, CT_OUT(NORM));
    printf(".event_count=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.event_count, CT_OUT(NORM));
    printf(".seven_f=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  header.seven_f, CT_OUT(NORM));
    printf("\n");
  }
  // if((header.seven_f != 8))

  if ((header.seven_f != 8))
  {
    // UINT32 second1 NOENCODE
    // {
      //  0_31: 0xffffffff;
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
    } second1;
    READ_FROM_BUFFER_FULL(654,uint32 ,second1,second1.u32,106);
    CHECK_BITS_EQUAL(653,second1.unnamed_0_31,0xffffffff);
    if (__buffer.is_memberdump())
    {
      printf("%s%08" PRIx32 "%s: second1 ", CT_OUT(BOLD), second1.u32, CT_OUT(NORM));
      printf("\n");
    }
    // UINT32 real_header NOENCODE
    // {
      //  0_04: geo;
      //  5_26: event_count;
      // 27_31: 8;
    // }
    union
    {
      struct
      {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint32 geo : 5; // 0..4
        uint32 event_count : 22; // 5..26
        uint32 unnamed_27_31 : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32 unnamed_27_31 : 5; // 27..31
        uint32 event_count : 22; // 5..26
        uint32 geo : 5; // 0..4
#endif
      };
      uint32  u32;
    } real_header;
    READ_FROM_BUFFER_FULL(661,uint32 ,real_header,real_header.u32,107);
    CHECK_BITS_EQUAL(660,real_header.unnamed_27_31,8);
    if (__buffer.is_memberdump())
    {
      printf("%s%08" PRIx32 "%s: real_header ", CT_OUT(BOLD), real_header.u32, CT_OUT(NORM));
      printf(".geo=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  real_header.geo, CT_OUT(NORM));
      printf(".event_count=%s%6" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  real_header.event_count, CT_OUT(NORM));
      printf("\n");
    }
  }
  // select several

    // tdc_header = TDC_HEADER();
    // measurement = TDC_DATA_V1190(data=data,leadOrTrail=leadOrTrail);
    // tdc_error = TDC_ERROR();
    // tdc_trailer = TDC_TRAILER();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TDC_HEADER tdc_header: (s32) => (0xf8000000,0x08000000)
    // optimized match 2: TDC_DATA_V1190 measurement: (s32) => (0xf8000000,0x00000000)
    // optimized match 3: TDC_ERROR tdc_error: (s32) => (0xf8000000,0x20000000)
    // optimized match 4: TDC_TRAILER tdc_trailer: (s32) => (0xf8000000,0x18000000)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(670,uint32,__match_peek);
    // differ = 38000000 : 27 28 29
    uint32 __match_index = 0 | /* 27,29 */ ((__match_peek >> 27) & 0x00000007);
    static const sint8 __match_index_array[8] = { 2, 1, 0, 4, 3, 0, 0, 0, };
    __match_no = __match_index_array[__match_index];
    // last_subevent_item = 0
    }
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        CHECK_SPURIOUS_MATCH_DECL(666,spurious_match_abort_loop_3,TDC_HEADER);
        UNPACK_DECL(666,TDC_HEADER,tdc_header);
        break;
      case 2:
        CHECK_SPURIOUS_MATCH_DECL(667,spurious_match_abort_loop_3,TDC_DATA_V1190/*,data:member*//*,leadOrTrail:member*/);
        UNPACK_DECL(667,TDC_DATA_V1190,measurement,/*data*/data,/*leadOrTrail*/leadOrTrail);
        break;
      case 3:
        CHECK_SPURIOUS_MATCH_DECL(668,spurious_match_abort_loop_3,TDC_ERROR);
        UNPACK_DECL(668,TDC_ERROR,tdc_error);
        break;
      case 4:
        CHECK_SPURIOUS_MATCH_DECL(669,spurious_match_abort_loop_3,TDC_TRAILER);
        UNPACK_DECL(669,TDC_TRAILER,tdc_trailer);
        break;
    }
  }
  spurious_match_abort_loop_3:;
  // optional UINT32 ext_time_tag NOENCODE
  // {
    //  0_26: time_tag;
    // 27_31: 17;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 time_tag : 27; // 0..26
      uint32 unnamed_27_31 : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_27_31 : 5; // 27..31
      uint32 time_tag : 27; // 0..26
#endif
    };
    uint32  u32;
  } ext_time_tag;
  if (__buffer.empty()) goto data_done_8;
  PEEK_FROM_BUFFER_FULL(677,uint32 ,ext_time_tag,ext_time_tag.u32,108);
  CHECK_JUMP_BITS_EQUAL(676,ext_time_tag.unnamed_27_31,17,data_done_8);
  __buffer.advance(sizeof(ext_time_tag.u32));
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: ext_time_tag ", CT_OUT(BOLD), ext_time_tag.u32, CT_OUT(NORM));
    printf(".time_tag=%s%7" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  ext_time_tag.time_tag, CT_OUT(NORM));
    printf("\n");
  }
  data_done_8:;
  // UINT32 trailer NOENCODE
  // {
    //  0_04: geo;
    //  5_20: word_count;
    // 21_23: unused;
    //    24: tdc_error;
    //    25: overflow;
    //    26: trigger_lost;
    // 27_31: 16;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 geo : 5; // 0..4
      uint32 word_count : 16; // 5..20
      uint32 unused : 3; // 21..23
      uint32 tdc_error : 1; // 24
      uint32 overflow : 1; // 25
      uint32 trigger_lost : 1; // 26
      uint32 unnamed_27_31 : 5; // 27..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_27_31 : 5; // 27..31
      uint32 trigger_lost : 1; // 26
      uint32 overflow : 1; // 25
      uint32 tdc_error : 1; // 24
      uint32 unused : 3; // 21..23
      uint32 word_count : 16; // 5..20
      uint32 geo : 5; // 0..4
#endif
    };
    uint32  u32;
  } trailer;
  READ_FROM_BUFFER_FULL(688,uint32 ,trailer,trailer.u32,109);
  CHECK_BITS_EQUAL(687,trailer.unnamed_27_31,16);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: trailer ", CT_OUT(BOLD), trailer.u32, CT_OUT(NORM));
    printf(".geo=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.geo, CT_OUT(NORM));
    printf(".word_count=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.word_count, CT_OUT(NORM));
    printf(".unused=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.unused, CT_OUT(NORM));
    printf(".tdc_error=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.tdc_error, CT_OUT(NORM));
    printf(".overflow=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.overflow, CT_OUT(NORM));
    printf(".trigger_lost=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  trailer.trigger_lost, CT_OUT(NORM));
    printf("\n");
  }
  // optional UINT32 eob NOENCODE;
  uint32  eob;if (__buffer.empty()) goto data_done_9;
  READ_FROM_BUFFER(690,uint32 ,eob,110);
  data_done_9:;
}
FORCE_IMPL_DATA_SRC_FCN(void,VME_CAEN_V1190_FRS::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TPC_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// TPC_CRATE_DATA()
template<typename __data_src_t>
void TPC_CRATE_DATA::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TPC_CRATE_DATA",CT_OUT(NORM));
  }
  // barrier[0] = BARRIER();
  UNPACK_DECL(1036,BARRIER,barrier[0]);
  // v775 = VME_CAEN_V7X5_FRS();
  UNPACK_DECL(1037,VME_CAEN_V7X5_FRS,v775);
  // barrier[1] = BARRIER();
  UNPACK_DECL(1039,BARRIER,barrier[1]);
  // v785 = VME_CAEN_V7X5_FRS();
  UNPACK_DECL(1040,VME_CAEN_V7X5_FRS,v785);
  // barrier[2] = BARRIER();
  UNPACK_DECL(1043,BARRIER,barrier[2]);
  // v1190 = VME_CAEN_V1190_FRS();
  UNPACK_DECL(1044,VME_CAEN_V1190_FRS,v1190);
}
FORCE_IMPL_DATA_SRC_FCN(void,TPC_CRATE_DATA::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for TRIG3EVENT.
 *
 * Do not edit - automatically generated.
 */

// TRIG3EVENT()
template<typename __data_src_t>
void TRIG3EVENT::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "TRIG3EVENT",CT_OUT(NORM));
  }
  // UINT32 trig3 NOENCODE
  // {
    //  0_31: 0x20202020;
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
  } trig3;
  READ_FROM_BUFFER_FULL(995,uint32 ,trig3,trig3.u32,112);
  CHECK_BITS_EQUAL(994,trig3.unnamed_0_31,0x20202020);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: trig3 ", CT_OUT(BOLD), trig3.u32, CT_OUT(NORM));
    printf("\n");
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,TRIG3EVENT::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for USER_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// USER_CRATE_DATA()
template<typename __data_src_t>
void USER_CRATE_DATA::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "USER_CRATE_DATA",CT_OUT(NORM));
  }
  // barrier[0] = BARRIER();
  UNPACK_DECL(1051,BARRIER,barrier[0]);
  // v830 = VME_CAEN_V830_FRS();
  UNPACK_DECL(1052,VME_CAEN_V830_FRS,v830);
  // filler[0] = ZERO_FILLER();
  UNPACK_DECL(1055,ZERO_FILLER,filler[0]);
  // barrier[1] = BARRIER();
  UNPACK_DECL(1056,BARRIER,barrier[1]);
  // v775[0] = VME_CAEN_V7X5_FRS();
  UNPACK_DECL(1057,VME_CAEN_V7X5_FRS,v775[0]);
  // barrier[2] = BARRIER();
  UNPACK_DECL(1059,BARRIER,barrier[2]);
  // v775[1] = VME_CAEN_V7X5_FRS();
  UNPACK_DECL(1060,VME_CAEN_V7X5_FRS,v775[1]);
  // barrier[3] = BARRIER();
  UNPACK_DECL(1062,BARRIER,barrier[3]);
  // v785[0] = VME_CAEN_V7X5_FRS();
  UNPACK_DECL(1063,VME_CAEN_V7X5_FRS,v785[0]);
  // barrier[4] = BARRIER();
  UNPACK_DECL(1065,BARRIER,barrier[4]);
  // v785[1] = VME_CAEN_V7X5_FRS();
  UNPACK_DECL(1066,VME_CAEN_V7X5_FRS,v785[1]);
}
FORCE_IMPL_DATA_SRC_FCN(void,USER_CRATE_DATA::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for VFTX2.
 *
 * Do not edit - automatically generated.
 */

// VFTX2(id)
template<typename __data_src_t>
void VFTX2::__unpack(__data_src_t &__buffer,uint32 id)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "VFTX2",CT_OUT(NORM));
  }
  // MEMBER(DATA12 time_fine[32] ZERO_SUPPRESS_MULTI(100));
  // MEMBER(DATA16 time_coarse[32] ZERO_SUPPRESS_MULTI(100));
  // MEMBER(DATA16 time_trigger);
  // UINT32 custom_header NOENCODE
  // {
    //  0_04: id = MATCH(id);
    //  5_08: internal_status;
    //  9_17: count;
    // 24_31: 171;
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 id : 5; // 0..4
      uint32 internal_status : 4; // 5..8
      uint32 count : 9; // 9..17
      uint32 dummy_18_23 : 6;
      uint32 unnamed_24_31 : 8; // 24..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 unnamed_24_31 : 8; // 24..31
      uint32 dummy_18_23 : 6;
      uint32 count : 9; // 9..17
      uint32 internal_status : 4; // 5..8
      uint32 id : 5; // 0..4
#endif
    };
    uint32  u32;
  } custom_header;
  READ_FROM_BUFFER_FULL(958,uint32 ,custom_header,custom_header.u32,114);
  CHECK_BITS_EQUAL(954,custom_header.id,id);
  CHECK_BITS_EQUAL(957,custom_header.unnamed_24_31,171);
  CHECK_UNNAMED_BITS_ZERO(958,custom_header.u32,0x00fc0000);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: custom_header ", CT_OUT(BOLD), custom_header.u32, CT_OUT(NORM));
    printf(".id=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  custom_header.id, CT_OUT(NORM));
    printf(".internal_status=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  custom_header.internal_status, CT_OUT(NORM));
    printf(".count=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  custom_header.count, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 trigger_window NOENCODE;
  uint32  trigger_window;READ_FROM_BUFFER(960,uint32 ,trigger_window,115);
  // UINT32 status_register NOENCODE;
  uint32  status_register;READ_FROM_BUFFER(961,uint32 ,status_register,116);
  // UINT32 mvlc_header NOENCODE
  // {
    //  0_15: words;
    // 16_31: mh = MATCH(0xf500);
  // }
  union
  {
    struct
    {
#if __BYTE_ORDER == __LITTLE_ENDIAN
      uint32 words : 16; // 0..15
      uint32 mh : 16; // 16..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
      uint32 mh : 16; // 16..31
      uint32 words : 16; // 0..15
#endif
    };
    uint32  u32;
  } mvlc_header;
  READ_FROM_BUFFER_FULL(967,uint32 ,mvlc_header,mvlc_header.u32,117);
  CHECK_BITS_EQUAL(966,mvlc_header.mh,0xf500);
  if (__buffer.is_memberdump())
  {
    printf("%s%08" PRIx32 "%s: mvlc_header ", CT_OUT(BOLD), mvlc_header.u32, CT_OUT(NORM));
    printf(".words=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  mvlc_header.words, CT_OUT(NORM));
    printf(".mh=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  mvlc_header.mh, CT_OUT(NORM));
    printf("\n");
  }
  // UINT32 skip_event_header NOENCODE;
  uint32  skip_event_header;READ_FROM_BUFFER(969,uint32 ,skip_event_header,118);
  // list(1<=index<mvlc_header.words)

  for (uint32 index = 1; index < (uint32) (mvlc_header.words); ++index)
  {
    // UINT32 event NOENCODE
    // {
      //  0_10: time_fine;
      // 11_23: time_coarse;
      //    24: future;
      // 25_29: channel;
      // 30_31: meh;
      // ENCODE(time_fine[channel],(value=time_fine));
      // ENCODE(time_coarse[channel],(value=time_coarse));
    // }
    union
    {
      struct
      {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint32 time_fine : 11; // 0..10
        uint32 time_coarse : 13; // 11..23
        uint32 future : 1; // 24
        uint32 channel : 5; // 25..29
        uint32 meh : 2; // 30..31
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32 meh : 2; // 30..31
        uint32 channel : 5; // 25..29
        uint32 future : 1; // 24
        uint32 time_coarse : 13; // 11..23
        uint32 time_fine : 11; // 0..10
#endif
      };
      uint32  u32;
    } event;
    READ_FROM_BUFFER_FULL(984,uint32 ,event,event.u32,119);
    {
      {
        typedef __typeof__(*(&(time_fine))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = time_fine.insert_index(982,event.channel);
        __item.value = event.time_fine;
      }
      {
        typedef __typeof__(*(&(time_coarse))) __array_t;
        typedef typename __array_t::item_t __item_t;
        __item_t &__item = time_coarse.insert_index(983,event.channel);
        __item.value = event.time_coarse;
      }
    }
    if (__buffer.is_memberdump())
    {
      printf("%s%08" PRIx32 "%s: event ", CT_OUT(BOLD), event.u32, CT_OUT(NORM));
      printf(".time_fine=%s%3" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event.time_fine, CT_OUT(NORM));
      printf(".time_coarse=%s%4" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event.time_coarse, CT_OUT(NORM));
      printf(".future=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event.future, CT_OUT(NORM));
      printf(".channel=%s%2" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event.channel, CT_OUT(NORM));
      printf(".meh=%s%1" PRIx64 "%s ", CT_OUT(BOLD), (uint64_t)  event.meh, CT_OUT(NORM));
      printf("\n");
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,VFTX2::__unpack,uint32 id);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for VFTX_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// VFTX_CRATE_DATA()
template<typename __data_src_t>
void VFTX_CRATE_DATA::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_BLUE),  "VFTX_CRATE_DATA",CT_OUT(NORM));
  }
  // vftx = VFTX2(id=0);
  UNPACK_DECL(1074,VFTX2,vftx,/*id*/0);
  // barrier[1] = BARRIER();
  UNPACK_DECL(1077,BARRIER,barrier[1]);
  // mtdc = MESYTEC_MTDC32_FRS();
  UNPACK_DECL(1078,MESYTEC_MTDC32_FRS,mtdc);
  // barrier[2] = BARRIER();
  UNPACK_DECL(1082,BARRIER,barrier[2]);
  // select optional

    // mqdc0 = MESYTEC_MQDC32_FRS();
  do
  {
    if (__buffer.empty()) goto no_match_1;
    int __match_no = 0;
    // optimized match 1: MESYTEC_MQDC32_FRS mqdc0: (s32) => (0xff00f000,0x40000000)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(1086,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(1085,spurious_match_abort_loop_4,MESYTEC_MQDC32_FRS);
        UNPACK_DECL(1085,MESYTEC_MQDC32_FRS,mqdc0);
        break;
    }
  }
  while (0);
  spurious_match_abort_loop_4:;
    no_match_1:;
  // select optional

    // mqdc1 = MESYTEC_MQDC32_FRS();
  do
  {
    if (__buffer.empty()) goto no_match_2;
    int __match_no = 0;
    // optimized match 1: MESYTEC_MQDC32_FRS mqdc1: (s32) => (0xff00f000,0x40000000)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(1090,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(1089,spurious_match_abort_loop_5,MESYTEC_MQDC32_FRS);
        UNPACK_DECL(1089,MESYTEC_MQDC32_FRS,mqdc1);
        break;
    }
  }
  while (0);
  spurious_match_abort_loop_5:;
    no_match_2:;
}
FORCE_IMPL_DATA_SRC_FCN(void,VFTX_CRATE_DATA::__unpack);

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
  READ_FROM_BUFFER_FULL(92,uint32 ,hi,hi.u32,121);
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
  READ_FROM_BUFFER_FULL(96,uint32 ,lo,lo.u32,122);
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
  UNPACK_DECL(1104,TIMESTAMP_WHITERABBIT,ts,/*id*/0x700);
  // external data = EXT_AIDA();
  UNPACK_DECL(1105,EXT_AIDA,data);
}
FORCE_IMPL_DATA_SRC_FCN(void,aida_subev::__unpack);

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
  // ts = TIMESTAMP_WHITERABBIT(id=0x500);
  UNPACK_DECL(1144,TIMESTAMP_WHITERABBIT,ts,/*id*/0x500);
  // trigger_window = TAMEX4_HEADER();
  UNPACK_DECL(1145,TAMEX4_HEADER,trigger_window);
  // select several

    // padding = TAMEX4_PADDING();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TAMEX4_PADDING padding: (s32) => (0xfff00000,0xadd00000)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(1149,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(1148,spurious_match_abort_loop_6,TAMEX4_PADDING);
        UNPACK_DECL(1148,TAMEX4_PADDING,padding);
        break;
    }
  }
  spurious_match_abort_loop_6:;
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
    PEEK_FROM_BUFFER(1157,uint32,__match_peek);
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
        UNPACK_DECL(1152,TAMEX4_SFP,tamex[0],/*sfp*/0,/*card*/0);
        break;
      case 2:
        UNPACK_DECL(1153,TAMEX4_SFP,tamex[1],/*sfp*/0,/*card*/1);
        break;
      case 3:
        UNPACK_DECL(1154,TAMEX4_SFP,tamex[2],/*sfp*/0,/*card*/2);
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
  // ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1600);
  UNPACK_DECL(1129,TIMESTAMP_WHITERABBIT_EXTENDED,ts,/*id*/0x1600);
  // trigger_window = TAMEX4_HEADER();
  UNPACK_DECL(1130,TAMEX4_HEADER,trigger_window);
  // select several

    // padding = TAMEX4_PADDING();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TAMEX4_PADDING padding: (s32) => (0xfff00000,0xadd00000)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(1134,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(1133,spurious_match_abort_loop_7,TAMEX4_PADDING);
        UNPACK_DECL(1133,TAMEX4_PADDING,padding);
        break;
    }
  }
  spurious_match_abort_loop_7:;
  // select several

    // tamex[0] = TAMEX4_SFP(sfp=0,card=0);
    // tamex[1] = TAMEX4_SFP(sfp=0,card=1);
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TAMEX4_SFP tamex[0]: (s32) => (0xfffff0ff,0x00000034)
    // optimized match 2: TAMEX4_SFP tamex[1]: (s32) => (0xfffff0ff,0x00010034)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(1139,uint32,__match_peek);
    // differ = 00010000 : 16
    uint32 __match_index = 0 | /* 16,16 */ ((__match_peek >> 16) & 0x00000001);
    static const sint8 __match_index_array[2] = { 1, 2, };
    __match_no = __match_index_array[__match_index];
    // last_subevent_item = 1
    }
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        UNPACK_DECL(1137,TAMEX4_SFP,tamex[0],/*sfp*/0,/*card*/0);
        break;
      case 2:
        UNPACK_DECL(1138,TAMEX4_SFP,tamex[1],/*sfp*/0,/*card*/1);
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
  UNPACK_DECL(1112,TIMESTAMP_WHITERABBIT,ts,/*id*/0x400);
  // select several

    // padding = FEBEX_PADDING();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: FEBEX_PADDING padding: (s32) => (0xfff00000,0xadd00000)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(1117,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(1116,spurious_match_abort_loop_8,FEBEX_PADDING);
        UNPACK_DECL(1116,FEBEX_PADDING,padding);
        break;
    }
  }
  spurious_match_abort_loop_8:;
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
    PEEK_FROM_BUFFER(1124,uint32,__match_peek);
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
        UNPACK_DECL(1120,FEBEX_EVENT,data[0],/*card*/0);
        break;
      case 2:
        UNPACK_DECL(1121,FEBEX_EVENT,data[1],/*card*/1);
        break;
      case 3:
        UNPACK_DECL(1122,FEBEX_EVENT,data[2],/*card*/2);
        break;
      case 4:
        UNPACK_DECL(1123,FEBEX_EVENT,data[3],/*card*/3);
        break;
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,febex_subev::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for frs_main_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_main_subev)
template<typename __data_src_t>
void frs_main_subev::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_MAGENTA),  "frs_main_subev",CT_OUT(NORM));
  }
  // select several

    // wr = TIMESTAMP_WHITERABBIT(id=0x100);
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TIMESTAMP_WHITERABBIT wr: (s32) => (0xfffeffff,0x00000100)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(1166,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(1165,spurious_match_abort_loop_9,TIMESTAMP_WHITERABBIT,/*id*/0x100);
        UNPACK_DECL(1165,TIMESTAMP_WHITERABBIT,wr,/*id*/0x100);
        break;
    }
  }
  spurious_match_abort_loop_9:;
  // select several

    // trig3 = TRIG3EVENT();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TRIG3EVENT trig3: (s32) => (0xffffffff,0x20202020)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(1172,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(1171,spurious_match_abort_loop_10,TRIG3EVENT);
        UNPACK_DECL(1171,TRIG3EVENT,trig3);
        break;
    }
  }
  spurious_match_abort_loop_10:;
  // select several

    // data = MAIN_CRATE_DATA();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: MAIN_CRATE_DATA data: could not get bits
    __buffer.peeking();
    MATCH_DECL(1177,__match_no,1,MAIN_CRATE_DATA,data);
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        UNPACK_DECL(1177,MAIN_CRATE_DATA,data);
        break;
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,frs_main_subev::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for frs_tpc_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_tpc_subev)
template<typename __data_src_t>
void frs_tpc_subev::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_MAGENTA),  "frs_tpc_subev",CT_OUT(NORM));
  }
  // select several

    // trig3 = TRIG3EVENT();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TRIG3EVENT trig3: (s32) => (0xffffffff,0x20202020)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(1186,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(1185,spurious_match_abort_loop_11,TRIG3EVENT);
        UNPACK_DECL(1185,TRIG3EVENT,trig3);
        break;
    }
  }
  spurious_match_abort_loop_11:;
  // select several

    // data = TPC_CRATE_DATA();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TPC_CRATE_DATA data: could not get bits
    __buffer.peeking();
    MATCH_DECL(1191,__match_no,1,TPC_CRATE_DATA,data);
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        UNPACK_DECL(1191,TPC_CRATE_DATA,data);
        break;
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,frs_tpc_subev::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for frs_user_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_user_subev)
template<typename __data_src_t>
void frs_user_subev::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_MAGENTA),  "frs_user_subev",CT_OUT(NORM));
  }
  // select several

    // trig3 = TRIG3EVENT();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TRIG3EVENT trig3: (s32) => (0xffffffff,0x20202020)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(1200,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(1199,spurious_match_abort_loop_12,TRIG3EVENT);
        UNPACK_DECL(1199,TRIG3EVENT,trig3);
        break;
    }
  }
  spurious_match_abort_loop_12:;
  // select several

    // data = USER_CRATE_DATA();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: USER_CRATE_DATA data: could not get bits
    __buffer.peeking();
    MATCH_DECL(1205,__match_no,1,USER_CRATE_DATA,data);
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        UNPACK_DECL(1205,USER_CRATE_DATA,data);
        break;
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,frs_user_subev::__unpack);

/** END_UNPACKER ******************************************************/
/** BEGIN_UNPACKER *****************************************************
 *
 * Event unpacker for frs_vftx_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_vftx_subev)
template<typename __data_src_t>
void frs_vftx_subev::__unpack(__data_src_t &__buffer)
{
  if (__buffer.is_memberdump())
  {
    printf("          %s%s%s: \n", CT_OUT(BOLD_MAGENTA),  "frs_vftx_subev",CT_OUT(NORM));
  }
  // select several

    // trig3 = TRIG3EVENT();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: TRIG3EVENT trig3: (s32) => (0xffffffff,0x20202020)
    {
    uint32 __match_peek;
    PEEK_FROM_BUFFER(1214,uint32,__match_peek);
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
        CHECK_SPURIOUS_MATCH_DECL(1213,spurious_match_abort_loop_13,TRIG3EVENT);
        UNPACK_DECL(1213,TRIG3EVENT,trig3);
        break;
    }
  }
  spurious_match_abort_loop_13:;
  // select several

    // data = VFTX_CRATE_DATA();
  for ( ; ; )
  {
    if (__buffer.empty()) break;
    int __match_no = 0;
    // optimized match 1: VFTX_CRATE_DATA data: could not get bits
    __buffer.peeking();
    MATCH_DECL(1219,__match_no,1,VFTX_CRATE_DATA,data);
    if (!__match_no) break;
    switch (__match_no)
    {
      case 1:
        UNPACK_DECL(1219,VFTX_CRATE_DATA,data);
        break;
    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,frs_vftx_subev::__unpack);

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
  // fatima = fatima_tamex_subev(type=10,subtype=1,procid=75,control=20,
                              // subcrate=0);
  // bplast = bplast_subev(type=10,subtype=1,procid=80,control=20,subcrate=0);
  // frsmain = frs_main_subev(procid=10);
  // frstpc = frs_tpc_subev(procid=20);
  // frsuser = frs_user_subev(procid=30);
  // frsvftx = frs_vftx_subev(procid=40);
  // ignore_unknown_subevent;
{
  int __match_no = 0;
  MATCH_SUBEVENT_DECL(1228,__match_no,1,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==37)&&(VES10_1_procid==90)),aida);
  MATCH_SUBEVENT_DECL(1231,__match_no,2,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==20)&&(VES10_1_subcrate==0)&&(VES10_1_procid==75)),fatima);
  MATCH_SUBEVENT_DECL(1232,__match_no,3,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==20)&&(VES10_1_subcrate==0)&&(VES10_1_procid==80)),bplast);
  MATCH_SUBEVENT_DECL(1234,__match_no,4,((VES10_1_procid==10)),frsmain);
  MATCH_SUBEVENT_DECL(1235,__match_no,5,((VES10_1_procid==20)),frstpc);
  MATCH_SUBEVENT_DECL(1236,__match_no,6,((VES10_1_procid==30)),frsuser);
  MATCH_SUBEVENT_DECL(1237,__match_no,7,((VES10_1_procid==40)),frsvftx);
  if (!__match_no) return 0;
  switch (__match_no)
  {
    case 1:
      UNPACK_SUBEVENT_DECL(1228,0,aida_subev,aida);
      break;
    case 2:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(1231,fatima_tamex_subev,fatima,0);
      UNPACK_SUBEVENT_DECL(1231,0,fatima_tamex_subev,fatima);
      break;
    case 3:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(1232,bplast_subev,bplast,1);
      UNPACK_SUBEVENT_DECL(1232,0,bplast_subev,bplast);
      break;
    case 4:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(1234,frs_main_subev,frsmain,2);
      UNPACK_SUBEVENT_DECL(1234,0,frs_main_subev,frsmain);
      break;
    case 5:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(1235,frs_tpc_subev,frstpc,3);
      UNPACK_SUBEVENT_DECL(1235,0,frs_tpc_subev,frstpc);
      break;
    case 6:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(1236,frs_user_subev,frsuser,4);
      UNPACK_SUBEVENT_DECL(1236,0,frs_user_subev,frsuser);
      break;
    case 7:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(1237,frs_vftx_subev,frsvftx,5);
      UNPACK_SUBEVENT_DECL(1237,0,frs_vftx_subev,frsvftx);
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
