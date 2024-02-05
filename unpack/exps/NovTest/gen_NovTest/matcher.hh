/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for BARRIER.
 *
 * Do not edit - automatically generated.
 */

// BARRIER()
template<typename __data_src_t>
bool BARRIER::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(1009,uint32 ,barrier,barrier.u32,1);
  MATCH_BITS_RANGE(1008,barrier.ba,0xf52,0xf58);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,BARRIER::__match);

/** END_MATCHER *******************************************************/
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
  MATCH_READ_FROM_BUFFER_FULL(268,uint32 ,sumchannel,sumchannel.u32,12);
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
  MATCH_READ_FROM_BUFFER_FULL(367,uint32 ,sumchannel,sumchannel.u32,32);
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
  MATCH_READ_FROM_BUFFER_FULL(240,uint32 ,pads_data,pads_data.u32,34);
  MATCH_BITS_EQUAL(239,pads_data.unnamed_20_31,0xadd);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,FEBEX_PADDING::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for VME_CAEN_V830_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V830_FRS()
template<typename __data_src_t>
bool VME_CAEN_V830_FRS::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(712,uint32 ,v830_header,v830_header.u32,37);
  MATCH_BITS_EQUAL(710,v830_header.unnamed_26_26,1);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,VME_CAEN_V830_FRS::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for ZERO_FILLER.
 *
 * Do not edit - automatically generated.
 */

// ZERO_FILLER()
template<typename __data_src_t>
bool ZERO_FILLER::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(1017,uint32 ,filler,filler.u32,39);
  MATCH_BITS_EQUAL(1016,filler.zero,0);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,ZERO_FILLER::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for VME_CAEN_V792_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V792_FRS()
template<typename __data_src_t>
bool VME_CAEN_V792_FRS::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(740,uint32 ,v792_header,v792_header.u32,44);
  MATCH_BITS_EQUAL(735,v792_header.unnamed_14_15,0);
  MATCH_BITS_EQUAL(737,v792_header.unnamed_24_26,2);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,VME_CAEN_V792_FRS::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for TDC_HEADER.
 *
 * Do not edit - automatically generated.
 */

// TDC_HEADER()
template<typename __data_src_t>
bool TDC_HEADER::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(537,uint32 ,tdc_header,tdc_header.u32,46);
  MATCH_BITS_EQUAL(536,tdc_header.unnamed_27_31,1);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,TDC_HEADER::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for TDC_DATA_V1290.
 *
 * Do not edit - automatically generated.
 */

// TDC_DATA_V1290(data,leadOrTrail)
template<typename __data_src_t>
bool TDC_DATA_V1290::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(553,uint32 ,tdc_data,tdc_data.u32,48);
  MATCH_BITS_EQUAL(549,tdc_data.unnamed_27_31,0);
  {
  }
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,TDC_DATA_V1290::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for TDC_ERROR.
 *
 * Do not edit - automatically generated.
 */

// TDC_ERROR()
template<typename __data_src_t>
bool TDC_ERROR::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(582,uint32 ,tdc_err,tdc_err.u32,50);
  MATCH_BITS_EQUAL(581,tdc_err.unnamed_27_31,4);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,TDC_ERROR::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for TDC_TRAILER.
 *
 * Do not edit - automatically generated.
 */

// TDC_TRAILER()
template<typename __data_src_t>
bool TDC_TRAILER::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(594,uint32 ,tdc_trailer,tdc_trailer.u32,52);
  MATCH_BITS_EQUAL(593,tdc_trailer.unnamed_27_31,3);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,TDC_TRAILER::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for VME_CAEN_V1290_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V1290_FRS()
template<typename __data_src_t>
bool VME_CAEN_V1290_FRS::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(606,uint32 ,header,header.u32,57);
  MATCH_BITS_EQUAL(605,header.unnamed_27_31,8);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,VME_CAEN_V1290_FRS::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for MAIN_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// MAIN_CRATE_DATA()
template<typename __data_src_t>
bool MAIN_CRATE_DATA::__match(__data_src_t &__buffer)
{
  // barrier[0] = BARRIER();
  CHECK_MATCH_DECL(1023,BARRIER,barrier[0]);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,MAIN_CRATE_DATA::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for MESYTEC_MQDC32_FRS.
 *
 * Do not edit - automatically generated.
 */

// MESYTEC_MQDC32_FRS()
template<typename __data_src_t>
bool MESYTEC_MQDC32_FRS::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(844,uint32 ,header,header.u32,62);
  MATCH_BITS_EQUAL(840,header.unnamed_12_14,0);
  MATCH_BITS_EQUAL(842,header.unnamed_24_29,0);
  MATCH_BITS_EQUAL(843,header.unnamed_30_31,1);
  MATCH_UNNAMED_BITS_ZERO(844,header.u32,0x00008000);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,MESYTEC_MQDC32_FRS::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for MESYTEC_MTDC32_FRS.
 *
 * Do not edit - automatically generated.
 */

// MESYTEC_MTDC32_FRS()
template<typename __data_src_t>
bool MESYTEC_MTDC32_FRS::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(882,uint32 ,header,header.u32,67);
  MATCH_BITS_EQUAL(880,header.unnamed_24_29,0);
  MATCH_BITS_EQUAL(881,header.unnamed_30_31,1);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,MESYTEC_MTDC32_FRS::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for SIS_3820_FRS.
 *
 * Do not edit - automatically generated.
 */

// SIS_3820_FRS()
template<typename __data_src_t>
bool SIS_3820_FRS::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(928,uint32 ,custom_header,custom_header.u32,71);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,SIS_3820_FRS::__match);

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
  MATCH_READ_FROM_BUFFER_FULL(168,uint32 ,data,data.u32,73);
  MATCH_BITS_EQUAL(161,data.unnamed_28_31,6);
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
  MATCH_READ_FROM_BUFFER_FULL(112,uint32 ,trigger_window,trigger_window.u32,75);
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
  MATCH_READ_FROM_BUFFER_FULL(122,uint32 ,padding,padding.u32,77);
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
  MATCH_READ_FROM_BUFFER_FULL(146,uint32 ,data,data.u32,79);
  MATCH_BITS_EQUAL(139,data.type,8);
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
  MATCH_READ_FROM_BUFFER_FULL(187,uint32 ,indicator,indicator.u32,85);
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
 * Event matcher for TDC_DATA_V1190.
 *
 * Do not edit - automatically generated.
 */

// TDC_DATA_V1190(data,leadOrTrail)
template<typename __data_src_t>
bool TDC_DATA_V1190::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(570,uint32 ,tdc_data,tdc_data.u32,87);
  MATCH_BITS_EQUAL(565,tdc_data.unnamed_27_31,0);
  {
  }
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,TDC_DATA_V1190::__match);

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
  MATCH_READ_FROM_BUFFER_FULL(24,uint32 ,header,header.u32,93);
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
  MATCH_READ_FROM_BUFFER_FULL(61,uint32 ,header,header.u32,99);
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
 * Event matcher for VME_CAEN_V7X5_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V7X5_FRS()
template<typename __data_src_t>
bool VME_CAEN_V7X5_FRS::__match(__data_src_t &__buffer)
{
  // MEMBER(DATA12_OVERFLOW data[32] ZERO_SUPPRESS);
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
  MATCH_READ_FROM_BUFFER_FULL(791,uint32 ,header,header.u32,104);
  MATCH_BITS_EQUAL(789,header.unnamed_24_26,2);
  MATCH_UNNAMED_BITS_ZERO(791,header.u32,0x0000c000);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,VME_CAEN_V7X5_FRS::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for VME_CAEN_V1190_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V1190_FRS()
template<typename __data_src_t>
bool VME_CAEN_V1190_FRS::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(651,uint32 ,header,header.u32,111);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,VME_CAEN_V1190_FRS::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for TPC_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// TPC_CRATE_DATA()
template<typename __data_src_t>
bool TPC_CRATE_DATA::__match(__data_src_t &__buffer)
{
  // barrier[0] = BARRIER();
  CHECK_MATCH_DECL(1038,BARRIER,barrier[0]);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,TPC_CRATE_DATA::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for TRIG3EVENT.
 *
 * Do not edit - automatically generated.
 */

// TRIG3EVENT()
template<typename __data_src_t>
bool TRIG3EVENT::__match(__data_src_t &__buffer)
{
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
  MATCH_READ_FROM_BUFFER_FULL(1000,uint32 ,trig3,trig3.u32,113);
  MATCH_BITS_EQUAL(999,trig3.unnamed_0_31,0x20202020);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,TRIG3EVENT::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for USER_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// USER_CRATE_DATA()
template<typename __data_src_t>
bool USER_CRATE_DATA::__match(__data_src_t &__buffer)
{
  // barrier[0] = BARRIER();
  CHECK_MATCH_DECL(1052,BARRIER,barrier[0]);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,USER_CRATE_DATA::__match);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for VFTX2.
 *
 * Do not edit - automatically generated.
 */

// VFTX2(id)
template<typename __data_src_t>
bool VFTX2::__match(__data_src_t &__buffer,uint32 id)
{
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
  MATCH_READ_FROM_BUFFER_FULL(963,uint32 ,custom_header,custom_header.u32,120);
  MATCH_BITS_EQUAL(959,custom_header.id,id);
  MATCH_BITS_EQUAL(962,custom_header.unnamed_24_31,171);
  MATCH_UNNAMED_BITS_ZERO(963,custom_header.u32,0x00fc0000);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN_ARG(bool,VFTX2::__match,uint32 id);

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for VFTX_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// VFTX_CRATE_DATA()
template<typename __data_src_t>
bool VFTX_CRATE_DATA::__match(__data_src_t &__buffer)
{
  // vftx = VFTX2(id=0);
  CHECK_MATCH_DECL(1074,VFTX2,vftx,/*id*/0);
  return true;
  return false;
}
FORCE_IMPL_DATA_SRC_FCN(bool,VFTX_CRATE_DATA::__match);

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
  MATCH_READ_FROM_BUFFER_FULL(92,uint32 ,hi,hi.u32,123);
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
 * Event matcher for bplast_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(bplast_subev)
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
 * Event matcher for frs_main_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_main_subev)
// No __match function for subevents.

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for frs_tpc_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_tpc_subev)
// No __match function for subevents.

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for frs_user_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_user_subev)
// No __match function for subevents.

/** END_MATCHER *******************************************************/
/** BEGIN_MATCHER ******************************************************
 *
 * Event matcher for frs_vftx_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_vftx_subev)
// No __match function for subevents.

/** END_MATCHER *******************************************************/
