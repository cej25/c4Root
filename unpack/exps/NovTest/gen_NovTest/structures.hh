/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for EXT_AIDA.
 *
 * Do not edit - automatically generated.
 */


/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for FEBEX_EVENT.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_EVENT(card)
#if !PACKER_CODE
# define DECLARED_UNPACK_FEBEX_EVENT
class FEBEX_EVENT
#else//PACKER_CODE
# define DECLARED_PACKER_FEBEX_EVENT
class PACKER_FEBEX_EVENT
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA32 event_trigger_time_hi);
  DATA32 event_trigger_time_hi;
  // MEMBER(DATA32 event_trigger_time_lo);
  DATA32 event_trigger_time_lo;
  // MEMBER(DATA16 hit_pattern);
  DATA16 hit_pattern;
  // MEMBER(DATA32 num_channels_fired);
  DATA32 num_channels_fired;
  // MEMBER(DATA8 channel_id[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA8,DATA8,16> channel_id;
  // MEMBER(DATA16 channel_trigger_time_hi[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA16,DATA16,16> channel_trigger_time_hi;
  // MEMBER(DATA32 channel_trigger_time_lo[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA32,DATA32,16> channel_trigger_time_lo;
  // MEMBER(DATA8 pileup[16]);
  raw_array<DATA8,DATA8,16> pileup;
  // MEMBER(DATA8 overflow[16]);
  raw_array<DATA8,DATA8,16> overflow;
  // MEMBER(DATA8 channel_cfd[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA8,DATA8,16> channel_cfd;
  // MEMBER(DATA32 channel_energy[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA32,DATA32,16> channel_energy;
  // UINT32 sumchannel NOENCODE
  // {
    //  0_07: 52;
    //  8_11: trigger_type;
    // 12_15: sfpnr;
    // 16_23: card = MATCH(card);
    // 24_31: 255;
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
  // list(0<=index<((channel_size.size / 4) - 1))

    // UINT32 channelids NOENCODE
    // {
      //  0_15: chan_ts_hi;
      // 16_23: channel_id_bits;
      // 24_31: 240;
      // ENCODE(channel_id[index],(value=channel_id_bits));
      // ENCODE(channel_trigger_time_hi[index],(value=chan_ts_hi));
    // }
    // UINT32 channel_ts NOENCODE
    // {
      //  0_31: chan_ts_lo;
      // ENCODE(channel_trigger_time_lo[index],(value=chan_ts_lo));
    // }
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
    // UINT32 future_use NOENCODE
    // {
      //  0_31: 0;
    // }

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 card);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 card);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer,uint32 card);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(FEBEX_EVENT);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for FEBEX_EVENT_TRACES.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_EVENT_TRACES(card)
#if !PACKER_CODE
# define DECLARED_UNPACK_FEBEX_EVENT_TRACES
class FEBEX_EVENT_TRACES
#else//PACKER_CODE
# define DECLARED_PACKER_FEBEX_EVENT_TRACES
class PACKER_FEBEX_EVENT_TRACES
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA32 event_trigger_time_hi);
  DATA32 event_trigger_time_hi;
  // MEMBER(DATA32 event_trigger_time_lo);
  DATA32 event_trigger_time_lo;
  // MEMBER(DATA16 hit_pattern);
  DATA16 hit_pattern;
  // MEMBER(DATA32 num_channels_fired);
  DATA32 num_channels_fired;
  // MEMBER(DATA8 channel_id[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA8,DATA8,16> channel_id;
  // MEMBER(DATA16 channel_trigger_time_hi[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA16,DATA16,16> channel_trigger_time_hi;
  // MEMBER(DATA32 channel_trigger_time_lo[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA32,DATA32,16> channel_trigger_time_lo;
  // MEMBER(DATA8 pileup[16]);
  raw_array<DATA8,DATA8,16> pileup;
  // MEMBER(DATA8 overflow[16]);
  raw_array<DATA8,DATA8,16> overflow;
  // MEMBER(DATA8 channel_cfd[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA8,DATA8,16> channel_cfd;
  // MEMBER(DATA32 channel_energy[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA32,DATA32,16> channel_energy;
  // MEMBER(DATA16 traces[16][10000] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA16,DATA16,10000> traces[16];
  // UINT32 sumchannel NOENCODE
  // {
    //  0_07: 52;
    //  8_11: trigger_type;
    // 12_15: sfpnr;
    // 16_23: board_id = MATCH(card);
    // 24_31: 255;
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

    // list(0<=index<((channel_size.size / 4) - 1))

      // UINT32 channelids NOENCODE
      // {
        //  0_15: chan_ts_hi;
        // 16_23: channel_id_bits;
        // 24_31: 240;
        // ENCODE(channel_id[index],(value=channel_id_bits));
        // ENCODE(channel_trigger_time_hi[index],(value=chan_ts_hi));
      // }
      // UINT32 channel_ts NOENCODE
      // {
        //  0_31: chan_ts_lo;
        // ENCODE(channel_trigger_time_lo[index],(value=chan_ts_lo));
      // }
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
      // UINT32 future_use NOENCODE
      // {
        //  0_31: 0;
      // }
    // list(0<=i<16)

      // UINT32 header NOENCODE
      // {
        //  0_07: 52;
        //  8_23: other;
        // 24_31: ch_id;
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

        // UINT32 channel_trace NOENCODE
        // {
          //  0_13: data1;
          // 14_15: stuff1;
          // 16_29: data2;
          // 30_31: stuff2;
          // ENCODE(traces[header.ch_id][((2 * j) + 0)],(value=data1));
          // ENCODE(traces[header.ch_id][((2 * j) + 1)],(value=data2));
        // }
      // UINT32 trace_trailer NOENCODE
      // {
        //  0_23: notused;
        // 24_31: id = RANGE(176,191);
      // }
    // if((sumchannel.trigger_type == 3))

      // list(0<=i<16)

        // UINT32 header NOENCODE
        // {
          //  0_07: 52;
          //  8_23: other;
          // 24_31: ch_id;
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
        // UINT32 trace_trailer NOENCODE
        // {
          //  0_23: notused;
          // 24_31: id = RANGE(176,191);
        // }

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 card);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 card);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer,uint32 card);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(FEBEX_EVENT_TRACES);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for FEBEX_PADDING.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_PADDING()
#if !PACKER_CODE
# define DECLARED_UNPACK_FEBEX_PADDING
class FEBEX_PADDING
#else//PACKER_CODE
# define DECLARED_PACKER_FEBEX_PADDING
class PACKER_FEBEX_PADDING
#endif//PACKER_CODE

{
public:
  // UINT32 pads_data NOENCODE
  // {
    //  0_11: counter;
    // 12_19: index;
    // 20_31: 0xadd;
  // }

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(FEBEX_PADDING);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for TAMEX4_EPOCH_DATA.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_EPOCH_DATA(sfp,card,time_coarse,time_fine,time_edge,time_channel,
                  // time_epoch)
#if !PACKER_CODE
# define DECLARED_UNPACK_TAMEX4_EPOCH_DATA
class TAMEX4_EPOCH_DATA
#else//PACKER_CODE
# define DECLARED_PACKER_TAMEX4_EPOCH_DATA
class PACKER_TAMEX4_EPOCH_DATA
#endif//PACKER_CODE

{
public:
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

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 sfp,uint32 card,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_coarse
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_fine
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_edge
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_channel
                                      ,raw_list_ii_zero_suppress<DATA32,DATA32,512> &time_epoch);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 sfp,uint32 card);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer,uint32 sfp,uint32 card,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_coarse
                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_fine
                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_edge
                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_channel
                                       ,raw_list_ii_zero_suppress<DATA32,DATA32,512> &time_epoch);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(TAMEX4_EPOCH_DATA);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for TAMEX4_HEADER.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_HEADER()
#if !PACKER_CODE
# define DECLARED_UNPACK_TAMEX4_HEADER
class TAMEX4_HEADER
#else//PACKER_CODE
# define DECLARED_PACKER_TAMEX4_HEADER
class PACKER_TAMEX4_HEADER
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA16 post_trig_ns[64] NO_INDEX_LIST);
  raw_list_ii_zero_suppress<DATA16,DATA16,64> post_trig_ns;
  // MEMBER(DATA16 pre_trig_ns[64] NO_INDEX_LIST);
  raw_list_ii_zero_suppress<DATA16,DATA16,64> pre_trig_ns;
  // UINT32 trigger_window NOENCODE
  // {
    //  0_15: post_trig_ns;
    // 16_31: pre_trig_ns;
    // ENCODE(post_trig_ns APPEND_LIST,(value=post_trig_ns));
    // ENCODE(pre_trig_ns APPEND_LIST,(value=pre_trig_ns));
  // }

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(TAMEX4_HEADER);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for TAMEX4_PADDING.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_PADDING()
#if !PACKER_CODE
# define DECLARED_UNPACK_TAMEX4_PADDING
class TAMEX4_PADDING
#else//PACKER_CODE
# define DECLARED_PACKER_TAMEX4_PADDING
class PACKER_TAMEX4_PADDING
#endif//PACKER_CODE

{
public:
  // UINT32 padding NOENCODE
  // {
    //  0_11: counter;
    // 12_19: index;
    // 20_31: 0xadd;
  // }

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(TAMEX4_PADDING);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for TAMEX4_TIME_DATA.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_TIME_DATA(sfp,card,time_coarse,time_fine,time_edge,time_channel,
                 // time_epoch)
#if !PACKER_CODE
# define DECLARED_UNPACK_TAMEX4_TIME_DATA
class TAMEX4_TIME_DATA
#else//PACKER_CODE
# define DECLARED_PACKER_TAMEX4_TIME_DATA
class PACKER_TAMEX4_TIME_DATA
#endif//PACKER_CODE

{
public:
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

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 sfp,uint32 card,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_coarse
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_fine
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_edge
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_channel
                                      ,raw_list_ii_zero_suppress<DATA32,DATA32,512> &time_epoch);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 sfp,uint32 card);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer,uint32 sfp,uint32 card,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_coarse
                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_fine
                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_edge
                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,512> &time_channel
                                       ,raw_list_ii_zero_suppress<DATA32,DATA32,512> &time_epoch);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(TAMEX4_TIME_DATA);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for TAMEX4_SFP.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_SFP(sfp,card)
#if !PACKER_CODE
# define DECLARED_UNPACK_TAMEX4_SFP
class TAMEX4_SFP
#else//PACKER_CODE
# define DECLARED_PACKER_TAMEX4_SFP
class PACKER_TAMEX4_SFP
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA32 event_size);
  DATA32 event_size;
  // MEMBER(DATA12 time_coarse[512] NO_INDEX_LIST);
  raw_list_ii_zero_suppress<DATA12,DATA12,512> time_coarse;
  // MEMBER(DATA12 time_fine[512] NO_INDEX_LIST);
  raw_list_ii_zero_suppress<DATA12,DATA12,512> time_fine;
  // MEMBER(DATA12 time_edge[512] NO_INDEX_LIST);
  raw_list_ii_zero_suppress<DATA12,DATA12,512> time_edge;
  // MEMBER(DATA12 time_channel[512] NO_INDEX_LIST);
  raw_list_ii_zero_suppress<DATA12,DATA12,512> time_channel;
  // MEMBER(DATA32 time_epoch[512] NO_INDEX_LIST);
  raw_list_ii_zero_suppress<DATA32,DATA32,512> time_epoch;
  // UINT32 indicator NOENCODE
  // {
    //  0_07: 52;
    //  8_11: trigger_type;
    // 12_15: sfp = MATCH(sfp);
    // 16_23: card = MATCH(card);
    // 24_31: 0;
  // }
  // MATCH_END;
  // UINT32 data_size NOENCODE
  // {
    //  0_31: bytes;
    // ENCODE(event_size,(value=bytes));
  // }
  // UINT32 tdc_header NOENCODE
  // {
    //  0_15: lec;
    //    16: buf_no;
    // 17_19: reserved;
    // 20_23: trigger_type;
    // 24_31: 170;
  // }
  // list(0<=i<((data_size.bytes / 4) - 3))

    // select several

      // time = TAMEX4_TIME_DATA(sfp=sfp,card=card,time_coarse=time_coarse,
                              // time_fine=time_fine,time_edge=time_edge,
                              // time_channel=time_channel,time_epoch=time_epoch);
      // epoch = TAMEX4_EPOCH_DATA(sfp=sfp,card=card,time_coarse=time_coarse,
                                // time_fine=time_fine,time_edge=time_edge,
                                // time_channel=time_channel,time_epoch=time_epoch);
    SINGLE(TAMEX4_TIME_DATA,time);
    SINGLE(TAMEX4_EPOCH_DATA,epoch);
  // UINT32 error_bits NOENCODE
  // {
    //  0_23: bits;
    // 24_31: 238;
  // }
  // UINT32 trailer NOENCODE
  // {
    //  0_15: lec;
    //    16: buf_no;
    // 17_19: reserved;
    // 20_23: trigger_type;
    // 24_31: 187;
  // }

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 sfp,uint32 card);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 sfp,uint32 card);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer,uint32 sfp,uint32 card);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(TAMEX4_SFP);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for TIMESTAMP_WHITERABBIT.
 *
 * Do not edit - automatically generated.
 */

// TIMESTAMP_WHITERABBIT(id)
#if !PACKER_CODE
# define DECLARED_UNPACK_TIMESTAMP_WHITERABBIT
class TIMESTAMP_WHITERABBIT
#else//PACKER_CODE
# define DECLARED_PACKER_TIMESTAMP_WHITERABBIT
class PACKER_TIMESTAMP_WHITERABBIT
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA12 subsystem_id);
  DATA12 subsystem_id;
  // MEMBER(DATA16 t1);
  DATA16 t1;
  // MEMBER(DATA16 t2);
  DATA16 t2;
  // MEMBER(DATA16 t3);
  DATA16 t3;
  // MEMBER(DATA16 t4);
  DATA16 t4;
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

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 id);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 id);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer,uint32 id);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(TIMESTAMP_WHITERABBIT);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for TIMESTAMP_WHITERABBIT_EXTENDED.
 *
 * Do not edit - automatically generated.
 */

// TIMESTAMP_WHITERABBIT_EXTENDED(id)
#if !PACKER_CODE
# define DECLARED_UNPACK_TIMESTAMP_WHITERABBIT_EXTENDED
class TIMESTAMP_WHITERABBIT_EXTENDED
#else//PACKER_CODE
# define DECLARED_PACKER_TIMESTAMP_WHITERABBIT_EXTENDED
class PACKER_TIMESTAMP_WHITERABBIT_EXTENDED
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA16 subsystem_id);
  DATA16 subsystem_id;
  // MEMBER(DATA16 t1);
  DATA16 t1;
  // MEMBER(DATA16 t2);
  DATA16 t2;
  // MEMBER(DATA16 t3);
  DATA16 t3;
  // MEMBER(DATA16 t4);
  DATA16 t4;
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

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 id);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 id);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer,uint32 id);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(TIMESTAMP_WHITERABBIT_EXTENDED);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for WR_MULTI.
 *
 * Do not edit - automatically generated.
 */

// WR_MULTI()
#if !PACKER_CODE
# define DECLARED_UNPACK_WR_MULTI
class WR_MULTI
#else//PACKER_CODE
# define DECLARED_PACKER_WR_MULTI
class PACKER_WR_MULTI
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA32 time_hi);
  DATA32 time_hi;
  // MEMBER(DATA32 time_lo);
  DATA32 time_lo;
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

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(WR_MULTI);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for aida_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(aida_subev)
#if !PACKER_CODE
# define DECLARED_UNPACK_aida_subev
class aida_subev
#else//PACKER_CODE
# define DECLARED_PACKER_aida_subev
class PACKER_aida_subev
#endif//PACKER_CODE
 : public unpack_subevent_base
{
public:
  // ts = TIMESTAMP_WHITERABBIT(id=0x700);
  // external data = EXT_AIDA();
  SINGLE(TIMESTAMP_WHITERABBIT,ts);
  SINGLE(EXT_AIDA,data);

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(aida_subev);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for fatima_tamex_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(fatima_tamex_subev)
#if !PACKER_CODE
# define DECLARED_UNPACK_fatima_tamex_subev
class fatima_tamex_subev
#else//PACKER_CODE
# define DECLARED_PACKER_fatima_tamex_subev
class PACKER_fatima_tamex_subev
#endif//PACKER_CODE
 : public unpack_subevent_base
{
public:
  // ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1600);
  // trigger_window = TAMEX4_HEADER();
  // select several

    // padding = TAMEX4_PADDING();
  SINGLE(TAMEX4_PADDING,padding);
  // select several

    // tamex[0] = TAMEX4_SFP(sfp=0,card=0);
  SINGLE(TAMEX4_SFP,tamex[1]);
  SINGLE(TIMESTAMP_WHITERABBIT_EXTENDED,ts);
  SINGLE(TAMEX4_HEADER,trigger_window);

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(fatima_tamex_subev);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for febex_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(febex_subev)
#if !PACKER_CODE
# define DECLARED_UNPACK_febex_subev
class febex_subev
#else//PACKER_CODE
# define DECLARED_PACKER_febex_subev
class PACKER_febex_subev
#endif//PACKER_CODE
 : public unpack_subevent_base
{
public:
  // ts = TIMESTAMP_WHITERABBIT(id=0x400);
  // select several

    // padding = FEBEX_PADDING();
  SINGLE(FEBEX_PADDING,padding);
  // select several

    // data[0] = FEBEX_EVENT(card=0);
    // data[1] = FEBEX_EVENT(card=1);
    // data[2] = FEBEX_EVENT(card=2);
    // data[3] = FEBEX_EVENT(card=3);
  SINGLE(FEBEX_EVENT,data[4]);
  SINGLE(TIMESTAMP_WHITERABBIT,ts);

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(febex_subev);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for plastic_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(plastic_subev)
#if !PACKER_CODE
# define DECLARED_UNPACK_plastic_subev
class plastic_subev
#else//PACKER_CODE
# define DECLARED_PACKER_plastic_subev
class PACKER_plastic_subev
#endif//PACKER_CODE
 : public unpack_subevent_base
{
public:
  // ts = TIMESTAMP_WHITERABBIT(id=0x500);
  // trigger_window = TAMEX4_HEADER();
  // select several

    // padding = TAMEX4_PADDING();
  SINGLE(TAMEX4_PADDING,padding);
  // select several

    // tamex[0] = TAMEX4_SFP(sfp=0,card=0);
    // tamex[1] = TAMEX4_SFP(sfp=0,card=1);
    // tamex[2] = TAMEX4_SFP(sfp=0,card=2);
  SINGLE(TAMEX4_SFP,tamex[3]);
  SINGLE(TIMESTAMP_WHITERABBIT,ts);
  SINGLE(TAMEX4_HEADER,trigger_window);

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(plastic_subev);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for EVENT.
 *
 * Do not edit - automatically generated.
 */

// EVENT
class unpack_event : public unpack_event_base
{
public:
  // revisit aida = aida_subev(type=10,subtype=1,procid=90,control=37);
  // germanium = febex_subev(type=10,subtype=1,procid=60,control=20);
  // fatima = fatima_tamex_subev(type=10,subtype=1,procid=75,control=20,
                              // subcrate=0);
  // plastic = plastic_subev(type=10,subtype=1,procid=80,control=20,
                          // subcrate=0);
  // ignore_unknown_subevent;
SINGLE(aida_subev,aida);
SINGLE(febex_subev,germanium);
SINGLE(fatima_tamex_subev,fatima);
SINGLE(plastic_subev,plastic);
public:
#ifndef __PSDC__
  bitsone<5> __visited;
  void __clear_visited() { __visited.clear(); }
  bool ignore_unknown_subevent() { return true; }
#endif//!__PSDC__

public:
#ifndef __PSDC__
template<typename __data_src_t>
  int __unpack_subevent(subevent_header *__header,__data_src_t &__buffer);
  int __revoke_subevent(subevent_header *__header);
  // void __clean_event();

  STRUCT_FCNS_DECL(unpack_event);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for EVENT.
 *
 * Do not edit - automatically generated.
 */

// STICKY_EVENT
class unpack_sticky_event : public unpack_sticky_event_base
{
public:
public:
#ifndef __PSDC__
  void __clear_visited() { }
  bool ignore_unknown_subevent() { return false; }
#endif//!__PSDC__

public:
#ifndef __PSDC__
template<typename __data_src_t>
  int __unpack_subevent(subevent_header *__header,__data_src_t &__buffer);
  int __revoke_subevent(subevent_header *__header);
  // void __clean_event();

  STRUCT_FCNS_DECL(unpack_sticky_event);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
