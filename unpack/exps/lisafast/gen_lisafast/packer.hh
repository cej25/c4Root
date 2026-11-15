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
  // MEMBER(DATA16 post_trig_ns);
  // MEMBER(DATA16 pre_trig_ns);
  // UINT32 trigger_window NOENCODE
  // {
    //  0_15: post_trig_ns;
    // 16_31: pre_trig_ns;
    // ENCODE(post_trig_ns,(value=post_trig_ns));
    // ENCODE(pre_trig_ns,(value=pre_trig_ns));
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
    // ENCODE(trig,(value=trigger_type));
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
      PACK_DECL(246,TAMEX4_EPOCH_DATA,epoch,/*sfp*/sfp,/*card*/card,/*time_coarse*/time_coarse,/*time_fine*/time_fine,/*time_edge*/time_edge,/*time_channel*/time_channel,/*time_epoch*/time_epoch);
      PACK_DECL(247,TAMEX4_TIME_DATA,time,/*sfp*/sfp,/*card*/card,/*time_coarse*/time_coarse,/*time_fine*/time_fine,/*time_edge*/time_edge,/*time_channel*/time_channel,/*time_epoch*/time_epoch);
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
  // MEMBER(DATA32 subsystem_id);
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
 * Event packer for lisa_tamex_subev.
 *
 * Do not edit - automatically generated.
 */

// SUBEVENT(lisa_tamex_subev)
template<typename __data_dest_t>
void PACKER_lisa_tamex_subev::__packer(__data_dest_t &__buffer)
{
  // trigger_window = TAMEX4_HEADER();
  PACK_DECL(271,TAMEX4_HEADER,trigger_window);
  // select several

    // padding = TAMEX4_PADDING();
  {
    PACK_DECL(274,TAMEX4_PADDING,padding);
  }
  // select several

    // tamex[0] = TAMEX4_SFP(sfp=0,card=0);
    // tamex[1] = TAMEX4_SFP(sfp=0,card=1);
    // tamex[2] = TAMEX4_SFP(sfp=0,card=2);
    // tamex[3] = TAMEX4_SFP(sfp=0,card=3);
  {
    PACK_DECL(278,TAMEX4_SFP,tamex[0],/*sfp*/0,/*card*/0);
    PACK_DECL(279,TAMEX4_SFP,tamex[1],/*sfp*/0,/*card*/1);
    PACK_DECL(280,TAMEX4_SFP,tamex[2],/*sfp*/0,/*card*/2);
    PACK_DECL(281,TAMEX4_SFP,tamex[3],/*sfp*/0,/*card*/3);
  }
}
FORCE_IMPL_DATA_SRC_FCN(void,lisa_tamex_subev::__packer);

/** END_PACKER ********************************************************/
/** BEGIN_PACKER *******************************************************
 *
 * Event packer for EVENT.
 *
 * Do not edit - automatically generated.
 */

// EVENT
  // lisafast = lisa_tamex_subev(type=10,subtype=1,procid=100,control=9,
                              // subcrate=0);
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
