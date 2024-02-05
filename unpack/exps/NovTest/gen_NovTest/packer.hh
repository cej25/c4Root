/** BEGIN_PACKER *******************************************************
 *
 * Event packer for BARRIER.
 *
 * Do not edit - automatically generated.
 */

// BARRIER()
template<typename __data_dest_t>
void PACKER_BARRIER::__packer(__data_dest_t &__buffer)
{
  // UINT32 barrier NOENCODE
  // {
    //  0_19: no;
    // 20_31: ba = RANGE(0xf52,0xf58);
  // }
}
FORCE_IMPL_DATA_SRC_FCN(void,BARRIER::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for EXT_AIDA.
 *
 * Do not edit - automatically generated.
 */


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
 * Event packer for FEBEX_EVENT_TRACES.
 *
 * Do not edit - automatically generated.
 */

// FEBEX_EVENT_TRACES(card)
template<typename __data_dest_t>
void PACKER_FEBEX_EVENT_TRACES::__packer(__data_dest_t &__buffer,uint32 card)
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
    }
    // list(0<=i<16)

    {
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
  }

  else
  {
    // if((sumchannel.trigger_type == 3))

    if ((sumchannel.trigger_type == 3))
    {
      // list(0<=i<16)

      {
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
      }
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
 * Event packer for VME_CAEN_V830_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V830_FRS()
template<typename __data_dest_t>
void PACKER_VME_CAEN_V830_FRS::__packer(__data_dest_t &__buffer)
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
  // list(0<=i<v830_header.nwords)

  {
    // UINT32 data_word NOENCODE
    // {
      //  0_31: value;
      // ENCODE(data[i],(value=value));
    // }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,VME_CAEN_V830_FRS::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for ZERO_FILLER.
 *
 * Do not edit - automatically generated.
 */

// ZERO_FILLER()
template<typename __data_dest_t>
void PACKER_ZERO_FILLER::__packer(__data_dest_t &__buffer)
{
  // UINT32 filler NOENCODE
  // {
    //  0_31: zero = MATCH(0);
  // }
}
FORCE_IMPL_DATA_SRC_FCN(void,ZERO_FILLER::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for VME_CAEN_V792_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V792_FRS()
template<typename __data_dest_t>
void PACKER_VME_CAEN_V792_FRS::__packer(__data_dest_t &__buffer)
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

  {
    // optional UINT32 eob2 NOENCODE
    // {
      //  0_23: nothing;
      // 24_26: id = MATCH(6);
      // 27_31: geom;
    // }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,VME_CAEN_V792_FRS::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TDC_HEADER.
 *
 * Do not edit - automatically generated.
 */

// TDC_HEADER()
template<typename __data_dest_t>
void PACKER_TDC_HEADER::__packer(__data_dest_t &__buffer)
{
  // UINT32 tdc_header NOENCODE
  // {
    //  0_11: bunch_id;
    // 12_23: event_id;
    // 24_25: tdc;
    //    26: unused;
    // 27_31: 1;
  // }
}
FORCE_IMPL_DATA_SRC_FCN(void,TDC_HEADER::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TDC_DATA_V1290.
 *
 * Do not edit - automatically generated.
 */

// TDC_DATA_V1290(data,leadOrTrail)
template<typename __data_dest_t>
void PACKER_TDC_DATA_V1290::__packer(__data_dest_t &__buffer,raw_array_multi_zero_suppress<DATA24,DATA24,128,128> &data
                                                            ,raw_array_multi_zero_suppress<DATA8,DATA8,128,128> &leadOrTrail)
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
}
FORCE_IMPL_DATA_SRC_FCN(void,TDC_DATA_V1290::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TDC_ERROR.
 *
 * Do not edit - automatically generated.
 */

// TDC_ERROR()
template<typename __data_dest_t>
void PACKER_TDC_ERROR::__packer(__data_dest_t &__buffer)
{
  // UINT32 tdc_err NOENCODE
  // {
    //  0_14: error_flags;
    // 15_23: unused1;
    // 24_25: tdc;
    //    26: unused2;
    // 27_31: 4;
  // }
}
FORCE_IMPL_DATA_SRC_FCN(void,TDC_ERROR::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TDC_TRAILER.
 *
 * Do not edit - automatically generated.
 */

// TDC_TRAILER()
template<typename __data_dest_t>
void PACKER_TDC_TRAILER::__packer(__data_dest_t &__buffer)
{
  // UINT32 tdc_trailer NOENCODE
  // {
    //  0_11: word_count;
    // 12_23: event_id;
    // 24_25: tdc;
    //    26: unused;
    // 27_31: 3;
  // }
}
FORCE_IMPL_DATA_SRC_FCN(void,TDC_TRAILER::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for VME_CAEN_V1290_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V1290_FRS()
template<typename __data_dest_t>
void PACKER_VME_CAEN_V1290_FRS::__packer(__data_dest_t &__buffer)
{
  // MEMBER(DATA24 data[128] ZERO_SUPPRESS_MULTI(128));
  // MEMBER(DATA8 leadOrTrail[128] ZERO_SUPPRESS_MULTI(128));
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
  {
    PACK_DECL(610,TDC_HEADER,tdc_header);
    PACK_DECL(611,TDC_DATA_V1290,measurement,/*data*/data,/*leadOrTrail*/leadOrTrail);
    PACK_DECL(612,TDC_ERROR,tdc_err);
    PACK_DECL(613,TDC_TRAILER,tdc_trailer);
  }
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
}
FORCE_IMPL_DATA_SRC_FCN(void,VME_CAEN_V1290_FRS::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for MAIN_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// MAIN_CRATE_DATA()
template<typename __data_dest_t>
void PACKER_MAIN_CRATE_DATA::__packer(__data_dest_t &__buffer)
{
  // barrier[0] = BARRIER();
  PACK_DECL(1023,BARRIER,barrier[0]);
  // v830 = VME_CAEN_V830_FRS();
  PACK_DECL(1024,VME_CAEN_V830_FRS,v830);
  // filler[0] = ZERO_FILLER();
  PACK_DECL(1026,ZERO_FILLER,filler[0]);
  // barrier[1] = BARRIER();
  PACK_DECL(1027,BARRIER,barrier[1]);
  // v792 = VME_CAEN_V792_FRS();
  PACK_DECL(1028,VME_CAEN_V792_FRS,v792);
  // barrier[2] = BARRIER();
  PACK_DECL(1030,BARRIER,barrier[2]);
  // v1290 = VME_CAEN_V1290_FRS();
  PACK_DECL(1031,VME_CAEN_V1290_FRS,v1290);
}
FORCE_IMPL_DATA_SRC_FCN(void,MAIN_CRATE_DATA::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for MESYTEC_MQDC32_FRS.
 *
 * Do not edit - automatically generated.
 */

// MESYTEC_MQDC32_FRS()
template<typename __data_dest_t>
void PACKER_MESYTEC_MQDC32_FRS::__packer(__data_dest_t &__buffer)
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
}
FORCE_IMPL_DATA_SRC_FCN(void,MESYTEC_MQDC32_FRS::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for MESYTEC_MTDC32_FRS.
 *
 * Do not edit - automatically generated.
 */

// MESYTEC_MTDC32_FRS()
template<typename __data_dest_t>
void PACKER_MESYTEC_MTDC32_FRS::__packer(__data_dest_t &__buffer)
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
  // list(1<=index<header.word_number)

  {
    // optional UINT32 zero NOENCODE
    // {
      //  0_31: ze = MATCH(0);
    // }
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
    }
  }
  // UINT32 end_of_event NOENCODE
  // {
    //  0_29: counter;
    // 30_31: 3;
  // }
}
FORCE_IMPL_DATA_SRC_FCN(void,MESYTEC_MTDC32_FRS::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for SIS_3820_FRS.
 *
 * Do not edit - automatically generated.
 */

// SIS_3820_FRS()
template<typename __data_dest_t>
void PACKER_SIS_3820_FRS::__packer(__data_dest_t &__buffer)
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
  // list(0<=index<custom_header.nchs)

  {
    // if((1 == custom_header.data_format))

    if ((1 == custom_header.data_format))
    {
      // UINT32 event NOENCODE
      // {
        //  0_31: val;
      // }
      // ENCODE(data[index],(value=event.val));

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
      // ENCODE(data[event.channel],(value=event.val));

    }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,SIS_3820_FRS::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TAMEX4_EPOCH_DATA.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_EPOCH_DATA(sfp,card,time_coarse,time_fine,time_edge,time_channel,
                  // time_epoch)
template<typename __data_dest_t>
void PACKER_TAMEX4_EPOCH_DATA::__packer(__data_dest_t &__buffer,uint32 sfp
                                                               ,uint32 card
                                                               ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_coarse
                                                               ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_fine
                                                               ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_edge
                                                               ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_channel
                                                               ,raw_list_ii_zero_suppress<DATA32,DATA32,1024> &time_epoch)
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
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TAMEX4_EPOCH_DATA::__packer,uint32 sfp,uint32 card);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TAMEX4_HEADER.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_HEADER()
template<typename __data_dest_t>
void PACKER_TAMEX4_HEADER::__packer(__data_dest_t &__buffer)
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
}
FORCE_IMPL_DATA_SRC_FCN(void,TAMEX4_HEADER::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TAMEX4_PADDING.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_PADDING()
template<typename __data_dest_t>
void PACKER_TAMEX4_PADDING::__packer(__data_dest_t &__buffer)
{
  // UINT32 padding NOENCODE
  // {
    //  0_11: counter;
    // 12_19: index;
    // 20_31: 0xadd;
  // }
}
FORCE_IMPL_DATA_SRC_FCN(void,TAMEX4_PADDING::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TAMEX4_TIME_DATA.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_TIME_DATA(sfp,card,time_coarse,time_fine,time_edge,time_channel,
                 // time_epoch)
template<typename __data_dest_t>
void PACKER_TAMEX4_TIME_DATA::__packer(__data_dest_t &__buffer,uint32 sfp
                                                              ,uint32 card
                                                              ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_coarse
                                                              ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_fine
                                                              ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_edge
                                                              ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_channel
                                                              ,raw_list_ii_zero_suppress<DATA32,DATA32,1024> &time_epoch)
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
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TAMEX4_TIME_DATA::__packer,uint32 sfp,uint32 card);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TAMEX4_SFP.
 *
 * Do not edit - automatically generated.
 */

// TAMEX4_SFP(sfp,card)
template<typename __data_dest_t>
void PACKER_TAMEX4_SFP::__packer(__data_dest_t &__buffer,uint32 sfp,uint32 card)
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

  {
    // select

      // epoch = TAMEX4_EPOCH_DATA(sfp=sfp,card=card,time_coarse=time_coarse,
                                // time_fine=time_fine,time_edge=time_edge,
                                // time_channel=time_channel,time_epoch=time_epoch);
      // time = TAMEX4_TIME_DATA(sfp=sfp,card=card,time_coarse=time_coarse,
                              // time_fine=time_fine,time_edge=time_edge,
                              // time_channel=time_channel,time_epoch=time_epoch);
    {
      PACK_DECL(208,TAMEX4_EPOCH_DATA,epoch,/*sfp*/sfp,/*card*/card,/*time_coarse*/time_coarse,/*time_fine*/time_fine,/*time_edge*/time_edge,/*time_channel*/time_channel,/*time_epoch*/time_epoch);
      PACK_DECL(209,TAMEX4_TIME_DATA,time,/*sfp*/sfp,/*card*/card,/*time_coarse*/time_coarse,/*time_fine*/time_fine,/*time_edge*/time_edge,/*time_channel*/time_channel,/*time_epoch*/time_epoch);
    }
  }
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
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,TAMEX4_SFP::__packer,uint32 sfp,uint32 card);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TDC_DATA_V1190.
 *
 * Do not edit - automatically generated.
 */

// TDC_DATA_V1190(data,leadOrTrail)
template<typename __data_dest_t>
void PACKER_TDC_DATA_V1190::__packer(__data_dest_t &__buffer,raw_array_multi_zero_suppress<DATA24,DATA24,128,128> &data
                                                            ,raw_array_multi_zero_suppress<DATA8,DATA8,128,128> &leadOrTrail)
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
}
FORCE_IMPL_DATA_SRC_FCN(void,TDC_DATA_V1190::__packer);

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
 * Event packer for VME_CAEN_V7X5_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V7X5_FRS()
template<typename __data_dest_t>
void PACKER_VME_CAEN_V7X5_FRS::__packer(__data_dest_t &__buffer)
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
  // list(0<=index<header.count)

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
      // ENCODE(data[index],(value=value,overflow=overflow));
    // }
  }
  // UINT32 eob NOENCODE
  // {
    //  0_23: nothing;
    // 24_26: 4;
    // 27_31: geom;
  // }
  // list(0<=i<2)

  {
    // optional UINT32 eob2 NOENCODE
    // {
      //  0_23: nothing;
      // 24_26: id = MATCH(6);
      // 27_31: geom;
    // }
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,VME_CAEN_V7X5_FRS::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for VME_CAEN_V1190_FRS.
 *
 * Do not edit - automatically generated.
 */

// VME_CAEN_V1190_FRS()
template<typename __data_dest_t>
void PACKER_VME_CAEN_V1190_FRS::__packer(__data_dest_t &__buffer)
{
  // MEMBER(DATA24 data[128] ZERO_SUPPRESS_MULTI(128));
  // MEMBER(DATA8 leadOrTrail[128] ZERO_SUPPRESS_MULTI(128));
  // UINT32 header NOENCODE
  // {
    //  0_04: geo;
    //  5_26: event_count;
    // 27_31: seven_f;
  // }
  // if((header.seven_f != 8))

  if ((header.seven_f != 8))
  {
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
  }
  // select several

    // tdc_header = TDC_HEADER();
    // measurement = TDC_DATA_V1190(data=data,leadOrTrail=leadOrTrail);
    // tdc_error = TDC_ERROR();
    // tdc_trailer = TDC_TRAILER();
  {
    PACK_DECL(671,TDC_HEADER,tdc_header);
    PACK_DECL(672,TDC_DATA_V1190,measurement,/*data*/data,/*leadOrTrail*/leadOrTrail);
    PACK_DECL(673,TDC_ERROR,tdc_error);
    PACK_DECL(674,TDC_TRAILER,tdc_trailer);
  }
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
}
FORCE_IMPL_DATA_SRC_FCN(void,VME_CAEN_V1190_FRS::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TPC_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// TPC_CRATE_DATA()
template<typename __data_dest_t>
void PACKER_TPC_CRATE_DATA::__packer(__data_dest_t &__buffer)
{
  // barrier[0] = BARRIER();
  PACK_DECL(1038,BARRIER,barrier[0]);
  // v775 = VME_CAEN_V7X5_FRS();
  PACK_DECL(1039,VME_CAEN_V7X5_FRS,v775);
  // barrier[1] = BARRIER();
  PACK_DECL(1041,BARRIER,barrier[1]);
  // v785 = VME_CAEN_V7X5_FRS();
  PACK_DECL(1042,VME_CAEN_V7X5_FRS,v785);
  // barrier[2] = BARRIER();
  PACK_DECL(1045,BARRIER,barrier[2]);
  // v1190 = VME_CAEN_V1190_FRS();
  PACK_DECL(1046,VME_CAEN_V1190_FRS,v1190);
}
FORCE_IMPL_DATA_SRC_FCN(void,TPC_CRATE_DATA::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for TRIG3EVENT.
 *
 * Do not edit - automatically generated.
 */

// TRIG3EVENT()
template<typename __data_dest_t>
void PACKER_TRIG3EVENT::__packer(__data_dest_t &__buffer)
{
  // UINT32 trig3 NOENCODE
  // {
    //  0_31: 0x20202020;
  // }
}
FORCE_IMPL_DATA_SRC_FCN(void,TRIG3EVENT::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for USER_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// USER_CRATE_DATA()
template<typename __data_dest_t>
void PACKER_USER_CRATE_DATA::__packer(__data_dest_t &__buffer)
{
  // barrier[0] = BARRIER();
  PACK_DECL(1052,BARRIER,barrier[0]);
  // v830 = VME_CAEN_V830_FRS();
  PACK_DECL(1053,VME_CAEN_V830_FRS,v830);
  // filler[0] = ZERO_FILLER();
  PACK_DECL(1056,ZERO_FILLER,filler[0]);
  // barrier[1] = BARRIER();
  PACK_DECL(1057,BARRIER,barrier[1]);
  // v775[0] = VME_CAEN_V7X5_FRS();
  PACK_DECL(1058,VME_CAEN_V7X5_FRS,v775[0]);
  // barrier[2] = BARRIER();
  PACK_DECL(1060,BARRIER,barrier[2]);
  // v775[1] = VME_CAEN_V7X5_FRS();
  PACK_DECL(1061,VME_CAEN_V7X5_FRS,v775[1]);
  // barrier[3] = BARRIER();
  PACK_DECL(1063,BARRIER,barrier[3]);
  // v785[0] = VME_CAEN_V7X5_FRS();
  PACK_DECL(1064,VME_CAEN_V7X5_FRS,v785[0]);
  // barrier[4] = BARRIER();
  PACK_DECL(1066,BARRIER,barrier[4]);
  // v785[1] = VME_CAEN_V7X5_FRS();
  PACK_DECL(1067,VME_CAEN_V7X5_FRS,v785[1]);
}
FORCE_IMPL_DATA_SRC_FCN(void,USER_CRATE_DATA::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for VFTX2.
 *
 * Do not edit - automatically generated.
 */

// VFTX2(id)
template<typename __data_dest_t>
void PACKER_VFTX2::__packer(__data_dest_t &__buffer,uint32 id)
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
  // UINT32 trigger_window NOENCODE;
  // UINT32 status_register NOENCODE;
  // UINT32 mvlc_header NOENCODE
  // {
    //  0_15: words;
    // 16_31: mh = MATCH(0xf500);
  // }
  // UINT32 skip_event_header NOENCODE;
  // list(1<=index<mvlc_header.words)

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
  }
}
FORCE_IMPL_DATA_SRC_FCN_ARG(void,VFTX2::__packer,uint32 id);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for VFTX_CRATE_DATA.
 *
 * Do not edit - automatically generated.
 */

// VFTX_CRATE_DATA()
template<typename __data_dest_t>
void PACKER_VFTX_CRATE_DATA::__packer(__data_dest_t &__buffer)
{
  // vftx = VFTX2(id=0);
  PACK_DECL(1074,VFTX2,vftx,/*id*/0);
  // barrier[1] = BARRIER();
  PACK_DECL(1077,BARRIER,barrier[1]);
  // mtdc = MESYTEC_MTDC32_FRS();
  PACK_DECL(1078,MESYTEC_MTDC32_FRS,mtdc);
  // barrier[2] = BARRIER();
  PACK_DECL(1082,BARRIER,barrier[2]);
  // select optional

    // mqdc0 = MESYTEC_MQDC32_FRS();
  {
    PACK_DECL(1085,MESYTEC_MQDC32_FRS,mqdc0);
  }
  // select optional

    // mqdc1 = MESYTEC_MQDC32_FRS();
  {
    PACK_DECL(1089,MESYTEC_MQDC32_FRS,mqdc1);
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,VFTX_CRATE_DATA::__packer);

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
 * Event packer for aida_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(aida_subev)
template<typename __data_dest_t>
void PACKER_aida_subev::__packer(__data_dest_t &__buffer)
{
  // ts = TIMESTAMP_WHITERABBIT(id=0x700);
  PACK_DECL(1104,TIMESTAMP_WHITERABBIT,ts,/*id*/0x700);
  // external data = EXT_AIDA();
  PACK_DECL(1105,EXT_AIDA,data);
}
FORCE_IMPL_DATA_SRC_FCN(void,aida_subev::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for bplast_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(bplast_subev)
template<typename __data_dest_t>
void PACKER_bplast_subev::__packer(__data_dest_t &__buffer)
{
  // ts = TIMESTAMP_WHITERABBIT(id=0x500);
  PACK_DECL(1144,TIMESTAMP_WHITERABBIT,ts,/*id*/0x500);
  // trigger_window = TAMEX4_HEADER();
  PACK_DECL(1145,TAMEX4_HEADER,trigger_window);
  // select several

    // padding = TAMEX4_PADDING();
  {
    PACK_DECL(1148,TAMEX4_PADDING,padding);
  }
  // select several

    // tamex[0] = TAMEX4_SFP(sfp=0,card=0);
    // tamex[1] = TAMEX4_SFP(sfp=0,card=1);
    // tamex[2] = TAMEX4_SFP(sfp=0,card=2);
    // tamex[3] = TAMEX4_SFP(sfp=0,card=3);
    // tamex[4] = TAMEX4_SFP(sfp=0,card=4);
  {
    PACK_DECL(1152,TAMEX4_SFP,tamex[0],/*sfp*/0,/*card*/0);
    PACK_DECL(1153,TAMEX4_SFP,tamex[1],/*sfp*/0,/*card*/1);
    PACK_DECL(1154,TAMEX4_SFP,tamex[2],/*sfp*/0,/*card*/2);
    PACK_DECL(1155,TAMEX4_SFP,tamex[3],/*sfp*/0,/*card*/3);
    PACK_DECL(1156,TAMEX4_SFP,tamex[4],/*sfp*/0,/*card*/4);
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,bplast_subev::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for fatima_tamex_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(fatima_tamex_subev)
template<typename __data_dest_t>
void PACKER_fatima_tamex_subev::__packer(__data_dest_t &__buffer)
{
  // ts = TIMESTAMP_WHITERABBIT_EXTENDED(id=0x1600);
  PACK_DECL(1129,TIMESTAMP_WHITERABBIT_EXTENDED,ts,/*id*/0x1600);
  // trigger_window = TAMEX4_HEADER();
  PACK_DECL(1130,TAMEX4_HEADER,trigger_window);
  // select several

    // padding = TAMEX4_PADDING();
  {
    PACK_DECL(1133,TAMEX4_PADDING,padding);
  }
  // select several

    // tamex[0] = TAMEX4_SFP(sfp=0,card=0);
    // tamex[1] = TAMEX4_SFP(sfp=0,card=1);
  {
    PACK_DECL(1137,TAMEX4_SFP,tamex[0],/*sfp*/0,/*card*/0);
    PACK_DECL(1138,TAMEX4_SFP,tamex[1],/*sfp*/0,/*card*/1);
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,fatima_tamex_subev::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for febex_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(febex_subev)
template<typename __data_dest_t>
void PACKER_febex_subev::__packer(__data_dest_t &__buffer)
{
  // ts = TIMESTAMP_WHITERABBIT(id=0x400);
  PACK_DECL(1112,TIMESTAMP_WHITERABBIT,ts,/*id*/0x400);
  // select several

    // padding = FEBEX_PADDING();
  {
    PACK_DECL(1116,FEBEX_PADDING,padding);
  }
  // select several

    // data[0] = FEBEX_EVENT(card=0);
    // data[1] = FEBEX_EVENT(card=1);
    // data[2] = FEBEX_EVENT(card=2);
    // data[3] = FEBEX_EVENT(card=3);
  {
    PACK_DECL(1120,FEBEX_EVENT,data[0],/*card*/0);
    PACK_DECL(1121,FEBEX_EVENT,data[1],/*card*/1);
    PACK_DECL(1122,FEBEX_EVENT,data[2],/*card*/2);
    PACK_DECL(1123,FEBEX_EVENT,data[3],/*card*/3);
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,febex_subev::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for frs_main_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_main_subev)
template<typename __data_dest_t>
void PACKER_frs_main_subev::__packer(__data_dest_t &__buffer)
{
  // select several

    // wr = TIMESTAMP_WHITERABBIT(id=0x100);
  {
    PACK_DECL(1165,TIMESTAMP_WHITERABBIT,wr,/*id*/0x100);
  }
  // select several

    // trig3 = TRIG3EVENT();
  {
    PACK_DECL(1171,TRIG3EVENT,trig3);
  }
  // select several

    // data = MAIN_CRATE_DATA();
  {
    PACK_DECL(1177,MAIN_CRATE_DATA,data);
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,frs_main_subev::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for frs_tpc_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_tpc_subev)
template<typename __data_dest_t>
void PACKER_frs_tpc_subev::__packer(__data_dest_t &__buffer)
{
  // select several

    // trig3 = TRIG3EVENT();
  {
    PACK_DECL(1185,TRIG3EVENT,trig3);
  }
  // select several

    // data = TPC_CRATE_DATA();
  {
    PACK_DECL(1191,TPC_CRATE_DATA,data);
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,frs_tpc_subev::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for frs_user_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_user_subev)
template<typename __data_dest_t>
void PACKER_frs_user_subev::__packer(__data_dest_t &__buffer)
{
  // select several

    // trig3 = TRIG3EVENT();
  {
    PACK_DECL(1199,TRIG3EVENT,trig3);
  }
  // select several

    // data = USER_CRATE_DATA();
  {
    PACK_DECL(1205,USER_CRATE_DATA,data);
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,frs_user_subev::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for frs_vftx_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(frs_vftx_subev)
template<typename __data_dest_t>
void PACKER_frs_vftx_subev::__packer(__data_dest_t &__buffer)
{
  // select several

    // trig3 = TRIG3EVENT();
  {
    PACK_DECL(1213,TRIG3EVENT,trig3);
  }
  // select several

    // data = VFTX_CRATE_DATA();
  {
    PACK_DECL(1219,VFTX_CRATE_DATA,data);
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,frs_vftx_subev::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for EVENT.
 *
 * Do not edit - automatically generated.
 */

// EVENT
  // revisit aida = aida_subev(type=10,subtype=1,procid=90,control=37);
  // bplast = bplast_subev(type=10,subtype=1,procid=80,control=20,subcrate=0);
  // frsmain = frs_main_subev(procid=10);
  // frstpc = frs_tpc_subev(procid=20);
  // frsuser = frs_user_subev(procid=30);
  // frsvftx = frs_vftx_subev(procid=40);
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
