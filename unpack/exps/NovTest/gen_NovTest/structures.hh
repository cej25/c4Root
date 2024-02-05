/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for BARRIER.
 *
 * Do not edit - automatically generated.
 */

// BARRIER()
#if !PACKER_CODE
# define DECLARED_UNPACK_BARRIER
class BARRIER
#else//PACKER_CODE
# define DECLARED_PACKER_BARRIER
class PACKER_BARRIER
#endif//PACKER_CODE

{
public:
  // UINT32 barrier NOENCODE
  // {
    //  0_19: no;
    // 20_31: ba = RANGE(0xf52,0xf58);
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

  STRUCT_FCNS_DECL(BARRIER);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
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
  // MEMBER(DATA16 channel_trigger_time_hi[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA16,DATA16,16> channel_trigger_time_hi;
  // MEMBER(DATA32 channel_trigger_time_lo[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA32,DATA32,16> channel_trigger_time_lo;
  // MEMBER(DATA8 pileup[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA8,DATA8,16> pileup;
  // MEMBER(DATA8 overflow[16] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA8,DATA8,16> overflow;
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
 * Event unpacker associated structures for VME_CAEN_V830_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V830_FRS()
#if !PACKER_CODE
# define DECLARED_UNPACK_VME_CAEN_V830_FRS
class VME_CAEN_V830_FRS
#else//PACKER_CODE
# define DECLARED_PACKER_VME_CAEN_V830_FRS
class PACKER_VME_CAEN_V830_FRS
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA32 data[32] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA32,DATA32,32> data;
  // UINT32 v830_header NOENCODE
  // {
    //  0_15: trigger_number;
    // 16_17: ts;
    // 18_23: nwords;
    // 24_25: unused;
    //    26: 1;
    // 27_31: geo;
  // }
  // list(0<=i<v830_header.nwords)

    // UINT32 data_word NOENCODE
    // {
      //  0_31: value;
      // ENCODE(data[i],(value=value));
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

  STRUCT_FCNS_DECL(VME_CAEN_V830_FRS);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for ZERO_FILLER.
 *
 * Do not edit - automatically generated.
 */

// ZERO_FILLER()
#if !PACKER_CODE
# define DECLARED_UNPACK_ZERO_FILLER
class ZERO_FILLER
#else//PACKER_CODE
# define DECLARED_PACKER_ZERO_FILLER
class PACKER_ZERO_FILLER
#endif//PACKER_CODE

{
public:
  // UINT32 filler NOENCODE
  // {
    //  0_31: zero = MATCH(0);
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

  STRUCT_FCNS_DECL(ZERO_FILLER);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for VME_CAEN_V792_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V792_FRS()
#if !PACKER_CODE
# define DECLARED_UNPACK_VME_CAEN_V792_FRS
class VME_CAEN_V792_FRS
#else//PACKER_CODE
# define DECLARED_PACKER_VME_CAEN_V792_FRS
class PACKER_VME_CAEN_V792_FRS
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA32 data[32] ZERO_SUPPRESS_MULTI(32));
  raw_array_multi_zero_suppress<DATA32,DATA32,32,32> data;
  // MEMBER(DATA8 geo);
  DATA8 geo;
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
  // UINT32 eob NOENCODE
  // {
    //  0_23: nothing;
    // 24_26: 4;
    // 27_31: geom;
  // }
  // list(0<=i<2)

    // optional UINT32 eob2 NOENCODE
    // {
      //  0_23: nothing;
      // 24_26: id = MATCH(6);
      // 27_31: geom;
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

  STRUCT_FCNS_DECL(VME_CAEN_V792_FRS);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for TDC_HEADER.
 *
 * Do not edit - automatically generated.
 */

// TDC_HEADER()
#if !PACKER_CODE
# define DECLARED_UNPACK_TDC_HEADER
class TDC_HEADER
#else//PACKER_CODE
# define DECLARED_PACKER_TDC_HEADER
class PACKER_TDC_HEADER
#endif//PACKER_CODE

{
public:
  // UINT32 tdc_header NOENCODE
  // {
    //  0_11: bunch_id;
    // 12_23: event_id;
    // 24_25: tdc;
    //    26: unused;
    // 27_31: 1;
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

  STRUCT_FCNS_DECL(TDC_HEADER);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for TDC_DATA_V1290.
 *
 * Do not edit - automatically generated.
 */

// TDC_DATA_V1290(data,leadOrTrail)
#if !PACKER_CODE
# define DECLARED_UNPACK_TDC_DATA_V1290
class TDC_DATA_V1290
#else//PACKER_CODE
# define DECLARED_PACKER_TDC_DATA_V1290
class PACKER_TDC_DATA_V1290
#endif//PACKER_CODE

{
public:
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

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,raw_array_multi_zero_suppress<DATA24,DATA24,128,128> &data
                                      ,raw_array_multi_zero_suppress<DATA8,DATA8,128,128> &leadOrTrail);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer,raw_array_multi_zero_suppress<DATA24,DATA24,128,128> &data
                                       ,raw_array_multi_zero_suppress<DATA8,DATA8,128,128> &leadOrTrail);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(TDC_DATA_V1290);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for TDC_ERROR.
 *
 * Do not edit - automatically generated.
 */

// TDC_ERROR()
#if !PACKER_CODE
# define DECLARED_UNPACK_TDC_ERROR
class TDC_ERROR
#else//PACKER_CODE
# define DECLARED_PACKER_TDC_ERROR
class PACKER_TDC_ERROR
#endif//PACKER_CODE

{
public:
  // UINT32 tdc_err NOENCODE
  // {
    //  0_14: error_flags;
    // 15_23: unused1;
    // 24_25: tdc;
    //    26: unused2;
    // 27_31: 4;
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

  STRUCT_FCNS_DECL(TDC_ERROR);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for TDC_TRAILER.
 *
 * Do not edit - automatically generated.
 */

// TDC_TRAILER()
#if !PACKER_CODE
# define DECLARED_UNPACK_TDC_TRAILER
class TDC_TRAILER
#else//PACKER_CODE
# define DECLARED_PACKER_TDC_TRAILER
class PACKER_TDC_TRAILER
#endif//PACKER_CODE

{
public:
  // UINT32 tdc_trailer NOENCODE
  // {
    //  0_11: word_count;
    // 12_23: event_id;
    // 24_25: tdc;
    //    26: unused;
    // 27_31: 3;
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

  STRUCT_FCNS_DECL(TDC_TRAILER);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for VME_CAEN_V1290_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V1290_FRS()
#if !PACKER_CODE
# define DECLARED_UNPACK_VME_CAEN_V1290_FRS
class VME_CAEN_V1290_FRS
#else//PACKER_CODE
# define DECLARED_PACKER_VME_CAEN_V1290_FRS
class PACKER_VME_CAEN_V1290_FRS
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA24 data[128] ZERO_SUPPRESS_MULTI(128));
  raw_array_multi_zero_suppress<DATA24,DATA24,128,128> data;
  // MEMBER(DATA8 leadOrTrail[128] ZERO_SUPPRESS_MULTI(128));
  raw_array_multi_zero_suppress<DATA8,DATA8,128,128> leadOrTrail;
  // UINT32 header NOENCODE
  // {
    //  0_04: geo;
    //  5_26: event_count;
    // 27_31: 8;
  // }
  // select several

    // tdc_header = TDC_HEADER();
    // measurement = TDC_DATA_V1290(data=data,leadOrTrail=leadOrTrail);
    // tdc_err = TDC_ERROR();
    // tdc_trailer = TDC_TRAILER();
  SINGLE(TDC_HEADER,tdc_header);
  SINGLE(TDC_DATA_V1290,measurement);
  SINGLE(TDC_ERROR,tdc_err);
  SINGLE(TDC_TRAILER,tdc_trailer);
  // optional UINT32 ext_time_tag NOENCODE
  // {
    //  0_26: time_tag;
    // 27_31: 17;
  // }
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
  // optional UINT32 eob NOENCODE;

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

  STRUCT_FCNS_DECL(VME_CAEN_V1290_FRS);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for MAIN_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// MAIN_CRATE_DATA()
#if !PACKER_CODE
# define DECLARED_UNPACK_MAIN_CRATE_DATA
class MAIN_CRATE_DATA
#else//PACKER_CODE
# define DECLARED_PACKER_MAIN_CRATE_DATA
class PACKER_MAIN_CRATE_DATA
#endif//PACKER_CODE

{
public:
  // barrier[0] = BARRIER();
  // v830 = VME_CAEN_V830_FRS();
  // filler[0] = ZERO_FILLER();
  // barrier[1] = BARRIER();
  // v792 = VME_CAEN_V792_FRS();
  // barrier[2] = BARRIER();
  // v1290 = VME_CAEN_V1290_FRS();
  SINGLE(BARRIER,barrier[3]);
  SINGLE(VME_CAEN_V830_FRS,v830);
  SINGLE(ZERO_FILLER,filler[1]);
  SINGLE(VME_CAEN_V792_FRS,v792);
  SINGLE(VME_CAEN_V1290_FRS,v1290);

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

  STRUCT_FCNS_DECL(MAIN_CRATE_DATA);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for MESYTEC_MQDC32_FRS.
 *
 * Do not edit - automatically generated.
 */

// MESYTEC_MQDC32_FRS()
#if !PACKER_CODE
# define DECLARED_UNPACK_MESYTEC_MQDC32_FRS
class MESYTEC_MQDC32_FRS
#else//PACKER_CODE
# define DECLARED_PACKER_MESYTEC_MQDC32_FRS
class PACKER_MESYTEC_MQDC32_FRS
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA12_OVERFLOW data[32] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA12_OVERFLOW,DATA12_OVERFLOW,32> data;
  // UINT32 header NOENCODE
  // {
    //  0_11: word_number;
    // 12_14: 0;
    // 16_23: geom;
    // 24_29: 0;
    // 30_31: 1;
  // }
  // several UINT32 ch_data NOENCODE
  // {
    //  0_11: value;
    //    15: outofrange;
    // 16_20: channel;
    // 21_29: 32;
    // 30_31: 0;
    // ENCODE(data[channel],(value=value,overflow=outofrange));
  // }
  // optional UINT32 zero NOENCODE
  // {
    //  0_31: 0;
  // }
  // UINT32 end_of_event NOENCODE
  // {
    //  0_29: counter;
    // 30_31: 3;
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

  STRUCT_FCNS_DECL(MESYTEC_MQDC32_FRS);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for MESYTEC_MTDC32_FRS.
 *
 * Do not edit - automatically generated.
 */

// MESYTEC_MTDC32_FRS()
#if !PACKER_CODE
# define DECLARED_UNPACK_MESYTEC_MTDC32_FRS
class MESYTEC_MTDC32_FRS
#else//PACKER_CODE
# define DECLARED_PACKER_MESYTEC_MTDC32_FRS
class PACKER_MESYTEC_MTDC32_FRS
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA16 data[34] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA16,DATA16,34> data;
  // UINT32 header NOENCODE
  // {
    //  0_11: word_number;
    // 12_15: tdc_resol;
    // 16_23: geom;
    // 24_29: 0;
    // 30_31: 1;
  // }
  // list(1<=index<header.word_number)

    // optional UINT32 zero NOENCODE
    // {
      //  0_31: ze = MATCH(0);
    // }
    // if((zero.ze != 0))

      // UINT32 ch_data NOENCODE
      // {
        //  0_15: value;
        // 16_20: channel;
        //    21: trig;
        // 22_29: 16;
        // 30_31: 0;
        // ENCODE(data[((trig * 32) + channel)],(value=value));
      // }
  // UINT32 end_of_event NOENCODE
  // {
    //  0_29: counter;
    // 30_31: 3;
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

  STRUCT_FCNS_DECL(MESYTEC_MTDC32_FRS);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for SIS_3820_FRS.
 *
 * Do not edit - automatically generated.
 */

// SIS_3820_FRS()
#if !PACKER_CODE
# define DECLARED_UNPACK_SIS_3820_FRS
class SIS_3820_FRS
#else//PACKER_CODE
# define DECLARED_PACKER_SIS_3820_FRS
class PACKER_SIS_3820_FRS
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA32 data[32] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA32,DATA32,32> data;
  // UINT32 custom_header NOENCODE
  // {
    //  0_07: nchs;
    //  8_21: nevts;
    //    22: latching;
    // 23_26: data_format;
    // 27_31: id;
  // }
  // list(0<=index<custom_header.nchs)

    // if((1 == custom_header.data_format))

      // UINT32 event NOENCODE
      // {
        //  0_31: val;
      // }
      // ENCODE(data[index],(value=event.val));

    // if(((0 == custom_header.data_format) || (3 == custom_header.data_format)))

      // UINT32 event NOENCODE
      // {
        //  0_23: val;
        // 24_28: channel;
        //    29: 0;
        // 30_31: user_bits;
      // }
      // ENCODE(data[event.channel],(value=event.val));


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

  STRUCT_FCNS_DECL(SIS_3820_FRS);
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

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 sfp,uint32 card,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_coarse
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_fine
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_edge
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_channel
                                      ,raw_list_ii_zero_suppress<DATA32,DATA32,1024> &time_epoch);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 sfp,uint32 card);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer,uint32 sfp,uint32 card,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_coarse
                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_fine
                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_edge
                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_channel
                                       ,raw_list_ii_zero_suppress<DATA32,DATA32,1024> &time_epoch);
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

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 sfp,uint32 card,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_coarse
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_fine
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_edge
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_channel
                                      ,raw_list_ii_zero_suppress<DATA32,DATA32,1024> &time_epoch);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 sfp,uint32 card);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer,uint32 sfp,uint32 card,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_coarse
                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_fine
                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_edge
                                       ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_channel
                                       ,raw_list_ii_zero_suppress<DATA32,DATA32,1024> &time_epoch);
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
  // MEMBER(DATA12 time_coarse[1024] NO_INDEX_LIST);
  raw_list_ii_zero_suppress<DATA12,DATA12,1024> time_coarse;
  // MEMBER(DATA12 time_fine[1024] NO_INDEX_LIST);
  raw_list_ii_zero_suppress<DATA12,DATA12,1024> time_fine;
  // MEMBER(DATA12 time_edge[1024] NO_INDEX_LIST);
  raw_list_ii_zero_suppress<DATA12,DATA12,1024> time_edge;
  // MEMBER(DATA12 time_channel[1024] NO_INDEX_LIST);
  raw_list_ii_zero_suppress<DATA12,DATA12,1024> time_channel;
  // MEMBER(DATA32 time_epoch[1024] NO_INDEX_LIST);
  raw_list_ii_zero_suppress<DATA32,DATA32,1024> time_epoch;
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

    // select

      // epoch = TAMEX4_EPOCH_DATA(sfp=sfp,card=card,time_coarse=time_coarse,
                                // time_fine=time_fine,time_edge=time_edge,
                                // time_channel=time_channel,time_epoch=time_epoch);
      // time = TAMEX4_TIME_DATA(sfp=sfp,card=card,time_coarse=time_coarse,
                              // time_fine=time_fine,time_edge=time_edge,
                              // time_channel=time_channel,time_epoch=time_epoch);
    SINGLE(TAMEX4_EPOCH_DATA,epoch);
    SINGLE(TAMEX4_TIME_DATA,time);
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
 * Event unpacker associated structures for TDC_DATA_V1190.
 *
 * Do not edit - automatically generated.
 */

// TDC_DATA_V1190(data,leadOrTrail)
#if !PACKER_CODE
# define DECLARED_UNPACK_TDC_DATA_V1190
class TDC_DATA_V1190
#else//PACKER_CODE
# define DECLARED_PACKER_TDC_DATA_V1190
class PACKER_TDC_DATA_V1190
#endif//PACKER_CODE

{
public:
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

public:
#ifndef __PSDC__
# if !PACKER_CODE
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,raw_array_multi_zero_suppress<DATA24,DATA24,128,128> &data
                                      ,raw_array_multi_zero_suppress<DATA8,DATA8,128,128> &leadOrTrail);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  // void __clean();
# else//PACKER_CODE
template<typename __data_dest_t>
  void __packer(__data_dest_t &__buffer,raw_array_multi_zero_suppress<DATA24,DATA24,128,128> &data
                                       ,raw_array_multi_zero_suppress<DATA8,DATA8,128,128> &leadOrTrail);
# endif//PACKER_CODE

  STRUCT_FCNS_DECL(TDC_DATA_V1190);
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
 * Event unpacker associated structures for VME_CAEN_V7X5_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V7X5_FRS()
#if !PACKER_CODE
# define DECLARED_UNPACK_VME_CAEN_V7X5_FRS
class VME_CAEN_V7X5_FRS
#else//PACKER_CODE
# define DECLARED_PACKER_VME_CAEN_V7X5_FRS
class PACKER_VME_CAEN_V7X5_FRS
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA12_OVERFLOW data[32] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA12_OVERFLOW,DATA12_OVERFLOW,32> data;
  // MEMBER(DATA8 channel[32] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA8,DATA8,32> channel;
  // MEMBER(DATA8 geo[32] ZERO_SUPPRESS);
  raw_array_zero_suppress<DATA8,DATA8,32> geo;
  // UINT32 header NOENCODE
  // {
    //  0_07: undefined;
    //  8_13: count;
    // 16_23: crate;
    // 24_26: 2;
    // 27_31: geom;
  // }
  // list(0<=index<header.count)

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
      // ENCODE(data[index],(value=value,overflow=overflow));
    // }
  // UINT32 eob NOENCODE
  // {
    //  0_23: nothing;
    // 24_26: 4;
    // 27_31: geom;
  // }
  // list(0<=i<2)

    // optional UINT32 eob2 NOENCODE
    // {
      //  0_23: nothing;
      // 24_26: id = MATCH(6);
      // 27_31: geom;
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

  STRUCT_FCNS_DECL(VME_CAEN_V7X5_FRS);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for VME_CAEN_V1190_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V1190_FRS()
#if !PACKER_CODE
# define DECLARED_UNPACK_VME_CAEN_V1190_FRS
class VME_CAEN_V1190_FRS
#else//PACKER_CODE
# define DECLARED_PACKER_VME_CAEN_V1190_FRS
class PACKER_VME_CAEN_V1190_FRS
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA24 data[128] ZERO_SUPPRESS_MULTI(128));
  raw_array_multi_zero_suppress<DATA24,DATA24,128,128> data;
  // MEMBER(DATA8 leadOrTrail[128] ZERO_SUPPRESS_MULTI(128));
  raw_array_multi_zero_suppress<DATA8,DATA8,128,128> leadOrTrail;
  // UINT32 header NOENCODE
  // {
    //  0_04: geo;
    //  5_26: event_count;
    // 27_31: seven_f;
  // }
  // if((header.seven_f != 8))

    // UINT32 second1 NOENCODE
    // {
      //  0_31: 0xffffffff;
    // }
    // UINT32 real_header NOENCODE
    // {
      //  0_04: geo;
      //  5_26: event_count;
      // 27_31: 8;
    // }
  // select several

    // tdc_header = TDC_HEADER();
    // measurement = TDC_DATA_V1190(data=data,leadOrTrail=leadOrTrail);
    // tdc_error = TDC_ERROR();
    // tdc_trailer = TDC_TRAILER();
  SINGLE(TDC_HEADER,tdc_header);
  SINGLE(TDC_DATA_V1190,measurement);
  SINGLE(TDC_ERROR,tdc_error);
  SINGLE(TDC_TRAILER,tdc_trailer);
  // optional UINT32 ext_time_tag NOENCODE
  // {
    //  0_26: time_tag;
    // 27_31: 17;
  // }
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
  // optional UINT32 eob NOENCODE;

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

  STRUCT_FCNS_DECL(VME_CAEN_V1190_FRS);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for TPC_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// TPC_CRATE_DATA()
#if !PACKER_CODE
# define DECLARED_UNPACK_TPC_CRATE_DATA
class TPC_CRATE_DATA
#else//PACKER_CODE
# define DECLARED_PACKER_TPC_CRATE_DATA
class PACKER_TPC_CRATE_DATA
#endif//PACKER_CODE

{
public:
  // barrier[0] = BARRIER();
  // v775 = VME_CAEN_V7X5_FRS();
  // barrier[1] = BARRIER();
  // v785 = VME_CAEN_V7X5_FRS();
  // barrier[2] = BARRIER();
  // v1190 = VME_CAEN_V1190_FRS();
  SINGLE(BARRIER,barrier[3]);
  SINGLE(VME_CAEN_V7X5_FRS,v775);
  SINGLE(VME_CAEN_V7X5_FRS,v785);
  SINGLE(VME_CAEN_V1190_FRS,v1190);

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

  STRUCT_FCNS_DECL(TPC_CRATE_DATA);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for TRIG3EVENT.
 *
 * Do not edit - automatically generated.
 */

// TRIG3EVENT()
#if !PACKER_CODE
# define DECLARED_UNPACK_TRIG3EVENT
class TRIG3EVENT
#else//PACKER_CODE
# define DECLARED_PACKER_TRIG3EVENT
class PACKER_TRIG3EVENT
#endif//PACKER_CODE

{
public:
  // UINT32 trig3 NOENCODE
  // {
    //  0_31: 0x20202020;
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

  STRUCT_FCNS_DECL(TRIG3EVENT);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for USER_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// USER_CRATE_DATA()
#if !PACKER_CODE
# define DECLARED_UNPACK_USER_CRATE_DATA
class USER_CRATE_DATA
#else//PACKER_CODE
# define DECLARED_PACKER_USER_CRATE_DATA
class PACKER_USER_CRATE_DATA
#endif//PACKER_CODE

{
public:
  // barrier[0] = BARRIER();
  // v830 = VME_CAEN_V830_FRS();
  // filler[0] = ZERO_FILLER();
  // barrier[1] = BARRIER();
  // v775[0] = VME_CAEN_V7X5_FRS();
  // barrier[2] = BARRIER();
  // v775[1] = VME_CAEN_V7X5_FRS();
  // barrier[3] = BARRIER();
  // v785[0] = VME_CAEN_V7X5_FRS();
  // barrier[4] = BARRIER();
  // v785[1] = VME_CAEN_V7X5_FRS();
  SINGLE(BARRIER,barrier[5]);
  SINGLE(VME_CAEN_V830_FRS,v830);
  SINGLE(ZERO_FILLER,filler[1]);
  SINGLE(VME_CAEN_V7X5_FRS,v775[2]);
  SINGLE(VME_CAEN_V7X5_FRS,v785[2]);

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

  STRUCT_FCNS_DECL(USER_CRATE_DATA);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for VFTX2.
 *
 * Do not edit - automatically generated.
 */

// VFTX2(id)
#if !PACKER_CODE
# define DECLARED_UNPACK_VFTX2
class VFTX2
#else//PACKER_CODE
# define DECLARED_PACKER_VFTX2
class PACKER_VFTX2
#endif//PACKER_CODE

{
public:
  // MEMBER(DATA12 time_fine[32] ZERO_SUPPRESS_MULTI(100));
  raw_array_multi_zero_suppress<DATA12,DATA12,32,100> time_fine;
  // MEMBER(DATA16 time_coarse[32] ZERO_SUPPRESS_MULTI(100));
  raw_array_multi_zero_suppress<DATA16,DATA16,32,100> time_coarse;
  // MEMBER(DATA16 time_trigger);
  DATA16 time_trigger;
  // UINT32 custom_header NOENCODE
  // {
    //  0_04: id = MATCH(id);
    //  5_08: internal_status;
    //  9_17: count;
    // 24_31: 171;
  // }
  // UINT32 trigger_window NOENCODE;
  // UINT32 status_register NOENCODE;
  // UINT32 mvlc_header NOENCODE
  // {
    //  0_15: words;
    // 16_31: mh = MATCH(0xf500);
  // }
  // UINT32 skip_event_header NOENCODE;
  // list(1<=index<mvlc_header.words)

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

  STRUCT_FCNS_DECL(VFTX2);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for VFTX_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// VFTX_CRATE_DATA()
#if !PACKER_CODE
# define DECLARED_UNPACK_VFTX_CRATE_DATA
class VFTX_CRATE_DATA
#else//PACKER_CODE
# define DECLARED_PACKER_VFTX_CRATE_DATA
class PACKER_VFTX_CRATE_DATA
#endif//PACKER_CODE

{
public:
  // vftx = VFTX2(id=0);
  // barrier[1] = BARRIER();
  // mtdc = MESYTEC_MTDC32_FRS();
  // barrier[2] = BARRIER();
  // select optional

    // mqdc0 = MESYTEC_MQDC32_FRS();
  SINGLE(MESYTEC_MQDC32_FRS,mqdc0);
  // select optional

    // mqdc1 = MESYTEC_MQDC32_FRS();
  SINGLE(MESYTEC_MQDC32_FRS,mqdc1);
  SINGLE(VFTX2,vftx);
  SINGLE(BARRIER,barrier[3]);
  SINGLE(MESYTEC_MTDC32_FRS,mtdc);

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

  STRUCT_FCNS_DECL(VFTX_CRATE_DATA);
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
 * Event unpacker associated structures for bplast_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(bplast_subev)
#if !PACKER_CODE
# define DECLARED_UNPACK_bplast_subev
class bplast_subev
#else//PACKER_CODE
# define DECLARED_PACKER_bplast_subev
class PACKER_bplast_subev
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
    // tamex[3] = TAMEX4_SFP(sfp=0,card=3);
    // tamex[4] = TAMEX4_SFP(sfp=0,card=4);
  SINGLE(TAMEX4_SFP,tamex[5]);
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

  STRUCT_FCNS_DECL(bplast_subev);
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
    // tamex[1] = TAMEX4_SFP(sfp=0,card=1);
  SINGLE(TAMEX4_SFP,tamex[2]);
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
 * Event unpacker associated structures for frs_main_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_main_subev)
#if !PACKER_CODE
# define DECLARED_UNPACK_frs_main_subev
class frs_main_subev
#else//PACKER_CODE
# define DECLARED_PACKER_frs_main_subev
class PACKER_frs_main_subev
#endif//PACKER_CODE
 : public unpack_subevent_base
{
public:
  // select several

    // wr = TIMESTAMP_WHITERABBIT(id=0x100);
  SINGLE(TIMESTAMP_WHITERABBIT,wr);
  // select several

    // trig3 = TRIG3EVENT();
  SINGLE(TRIG3EVENT,trig3);
  // select several

    // data = MAIN_CRATE_DATA();
  SINGLE(MAIN_CRATE_DATA,data);

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

  STRUCT_FCNS_DECL(frs_main_subev);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for frs_tpc_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_tpc_subev)
#if !PACKER_CODE
# define DECLARED_UNPACK_frs_tpc_subev
class frs_tpc_subev
#else//PACKER_CODE
# define DECLARED_PACKER_frs_tpc_subev
class PACKER_frs_tpc_subev
#endif//PACKER_CODE
 : public unpack_subevent_base
{
public:
  // select several

    // trig3 = TRIG3EVENT();
  SINGLE(TRIG3EVENT,trig3);
  // select several

    // data = TPC_CRATE_DATA();
  SINGLE(TPC_CRATE_DATA,data);

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

  STRUCT_FCNS_DECL(frs_tpc_subev);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for frs_user_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_user_subev)
#if !PACKER_CODE
# define DECLARED_UNPACK_frs_user_subev
class frs_user_subev
#else//PACKER_CODE
# define DECLARED_PACKER_frs_user_subev
class PACKER_frs_user_subev
#endif//PACKER_CODE
 : public unpack_subevent_base
{
public:
  // select several

    // trig3 = TRIG3EVENT();
  SINGLE(TRIG3EVENT,trig3);
  // select several

    // data = USER_CRATE_DATA();
  SINGLE(USER_CRATE_DATA,data);

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

  STRUCT_FCNS_DECL(frs_user_subev);
#endif//!__PSDC__
};

/** END_STRUCTURES ****************************************************/
/** BEGIN_STRUCTURES ***************************************************
 *
 * Event unpacker associated structures for frs_vftx_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_vftx_subev)
#if !PACKER_CODE
# define DECLARED_UNPACK_frs_vftx_subev
class frs_vftx_subev
#else//PACKER_CODE
# define DECLARED_PACKER_frs_vftx_subev
class PACKER_frs_vftx_subev
#endif//PACKER_CODE
 : public unpack_subevent_base
{
public:
  // select several

    // trig3 = TRIG3EVENT();
  SINGLE(TRIG3EVENT,trig3);
  // select several

    // data = VFTX_CRATE_DATA();
  SINGLE(VFTX_CRATE_DATA,data);

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

  STRUCT_FCNS_DECL(frs_vftx_subev);
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
  // bplast = bplast_subev(type=10,subtype=1,procid=80,control=20,subcrate=0);
  // frsmain = frs_main_subev(procid=10);
  // frstpc = frs_tpc_subev(procid=20);
  // frsuser = frs_user_subev(procid=30);
  // frsvftx = frs_vftx_subev(procid=40);
  // ignore_unknown_subevent;
SINGLE(aida_subev,aida);
SINGLE(bplast_subev,bplast);
SINGLE(frs_main_subev,frsmain);
SINGLE(frs_tpc_subev,frstpc);
SINGLE(frs_user_subev,frsuser);
SINGLE(frs_vftx_subev,frsvftx);
public:
#ifndef __PSDC__
  bitsone<7> __visited;
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
