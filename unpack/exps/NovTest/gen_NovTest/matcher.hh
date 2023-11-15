/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for EXT_AIDA.
 *
 * Do not edit - automatically generated.
 */


/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for FEBEX_EVENT.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_EVENT(card)
template<typename __data_src_t>
bool FEBEX_EVENT::__match(__data_src_t &__buffer,uint32 card)
{
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
  MATCH_READ_FROM_BUFFER_FULL(268,uint32 ,sumchannel,sumchannel.u32,10);
  MATCH_BITS_EQUAL(262,sumchannel.unnamed_0_7,52);
  MATCH_BITS_EQUAL(265,sumchannel.card,card);
  MATCH_BITS_EQUAL(266,sumchannel.unnamed_24_31,255);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN_ARG(bool,FEBEX_EVENT::__match,uint32 card);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for FEBEX_EVENT_TRACES.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_EVENT_TRACES(card)
template<typename __data_src_t>
bool FEBEX_EVENT_TRACES::__match(__data_src_t &__buffer,uint32 card)
{
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
  MATCH_READ_FROM_BUFFER_FULL(367,uint32 ,sumchannel,sumchannel.u32,30);
  MATCH_BITS_EQUAL(361,sumchannel.unnamed_0_7,52);
  MATCH_BITS_EQUAL(364,sumchannel.board_id,card);
  MATCH_BITS_EQUAL(365,sumchannel.unnamed_24_31,255);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN_ARG(bool,FEBEX_EVENT_TRACES::__match,uint32 card);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for FEBEX_PADDING.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_PADDING()
template<typename __data_src_t>
bool FEBEX_PADDING::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(240,uint32 ,pads_data,pads_data.u32,32);
  MATCH_BITS_EQUAL(239,pads_data.unnamed_20_31,0xadd);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,FEBEX_PADDING::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for TAMEX4_EPOCH_DATA.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_EPOCH_DATA(sfp,card,time_coarse,time_fine,time_edge,time_channel,
                  // time_epoch)
template<typename __data_src_t>
bool TAMEX4_EPOCH_DATA::__match(__data_src_t &__buffer,uint32 sfp,uint32 card)
{
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
  MATCH_READ_FROM_BUFFER_FULL(168,uint32 ,data,data.u32,34);
  MATCH_BITS_EQUAL(161,data.unnamed_29_31,3);
  {
  }
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN_ARG(bool,TAMEX4_EPOCH_DATA::__match,uint32 sfp,uint32 card);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for TAMEX4_HEADER.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_HEADER()
template<typename __data_src_t>
bool TAMEX4_HEADER::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(112,uint32 ,trigger_window,trigger_window.u32,36);
  {
  }
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,TAMEX4_HEADER::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for TAMEX4_PADDING.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_PADDING()
template<typename __data_src_t>
bool TAMEX4_PADDING::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(122,uint32 ,padding,padding.u32,38);
  MATCH_BITS_EQUAL(121,padding.unnamed_20_31,0xadd);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,TAMEX4_PADDING::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for TAMEX4_TIME_DATA.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_TIME_DATA(sfp,card,time_coarse,time_fine,time_edge,time_channel,
                 // time_epoch)
template<typename __data_src_t>
bool TAMEX4_TIME_DATA::__match(__data_src_t &__buffer,uint32 sfp,uint32 card)
{
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
  MATCH_READ_FROM_BUFFER_FULL(146,uint32 ,data,data.u32,40);
  MATCH_BITS_EQUAL(139,data.type,4);
  {
  }
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN_ARG(bool,TAMEX4_TIME_DATA::__match,uint32 sfp,uint32 card);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for TAMEX4_SFP.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_SFP(sfp,card)
template<typename __data_src_t>
bool TAMEX4_SFP::__match(__data_src_t &__buffer,uint32 sfp,uint32 card)
{
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
  MATCH_READ_FROM_BUFFER_FULL(187,uint32 ,indicator,indicator.u32,46);
  MATCH_BITS_EQUAL(182,indicator.unnamed_0_7,52);
  MATCH_BITS_EQUAL(184,indicator.sfp,sfp);
  MATCH_BITS_EQUAL(185,indicator.card,card);
  MATCH_BITS_EQUAL(186,indicator.unnamed_24_31,0);
  // MATCH_END;
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN_ARG(bool,TAMEX4_SFP::__match,uint32 sfp,uint32 card);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for TIMESTAMP_WHITERABBIT.
 *
 * Do not edit - automatically generated.
 */

// TIMESTAMP_WHITERABBIT(id)
template<typename __data_src_t>
bool TIMESTAMP_WHITERABBIT::__match(__data_src_t &__buffer,uint32 id)
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
  MATCH_READ_FROM_BUFFER_FULL(24,uint32 ,header,header.u32,52);
  MATCH_BITS_EQUAL(19,header.id,id);
  MATCH_BITS_EQUAL(20,header.unnamed_12_15,0);
  MATCH_BITS_EQUAL(22,header.unnamed_17_31,0);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN_ARG(bool,TIMESTAMP_WHITERABBIT::__match,uint32 id);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for TIMESTAMP_WHITERABBIT_EXTENDED.
 *
 * Do not edit - automatically generated.
 */

// TIMESTAMP_WHITERABBIT_EXTENDED(id)
template<typename __data_src_t>
bool TIMESTAMP_WHITERABBIT_EXTENDED::__match(__data_src_t &__buffer,uint32 id)
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
  MATCH_READ_FROM_BUFFER_FULL(61,uint32 ,header,header.u32,58);
  MATCH_BITS_EQUAL(56,header.id,id);
  MATCH_BITS_EQUAL(57,header.unnamed_13_15,0);
  MATCH_BITS_EQUAL(59,header.unnamed_17_31,0);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN_ARG(bool,TIMESTAMP_WHITERABBIT_EXTENDED::__match,uint32 id);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for WR_MULTI.
 *
 * Do not edit - automatically generated.
 */

// WR_MULTI()
template<typename __data_src_t>
bool WR_MULTI::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(92,uint32 ,hi,hi.u32,61);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,WR_MULTI::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for aida_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(aida_subev)
// No __match function for subevents.

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for fatima_tamex_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(fatima_tamex_subev)
// No __match function for subevents.

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for febex_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(febex_subev)
// No __match function for subevents.

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for plastic_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(plastic_subev)
// No __match function for subevents.

/** END_MATCHER *******************************************************/
