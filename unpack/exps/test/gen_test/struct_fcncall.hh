/** BEGIN_FUNCTION_CALL_PER_MEMBER *************************************
 *
 * Recursive function calls per member.
 *
 * Do not edit - automatically generated.
 */

#include "gen/default_fcncall_define.hh"

#ifndef USER_DEF_BAD_EVENT
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(BAD_EVENT)::FCNCALL_NAME(BAD_EVENT)
{
  FCNCALL_INIT;
  // DATA8 bad;
  {
  FCNCALL_SUBNAME("bad");
  { FCNCALL_CALL_CTRL_WRAP(bad,bad.FCNCALL_CALL(bad)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_BAD_EVENT

#ifndef USER_DEF_DUMMY
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(DUMMY)::FCNCALL_NAME(DUMMY)
{
  FCNCALL_INIT;
  FCNCALL_RET;
}
#endif//USER_DEF_DUMMY

#ifndef USER_DEF_FEBEX_EVENT
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(FEBEX_EVENT)::FCNCALL_NAME(FEBEX_EVENT)
{
  FCNCALL_INIT;
  // DATA8 trig;
  {
  FCNCALL_SUBNAME("trig");
  { FCNCALL_CALL_CTRL_WRAP(trig,trig.FCNCALL_CALL(trig)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA32 event_trigger_time_hi;
  {
  FCNCALL_SUBNAME("event_trigger_time_hi");
  { FCNCALL_CALL_CTRL_WRAP(event_trigger_time_hi,event_trigger_time_hi.FCNCALL_CALL(event_trigger_time_hi)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA32 event_trigger_time_lo;
  {
  FCNCALL_SUBNAME("event_trigger_time_lo");
  { FCNCALL_CALL_CTRL_WRAP(event_trigger_time_lo,event_trigger_time_lo.FCNCALL_CALL(event_trigger_time_lo)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA16 hit_pattern;
  {
  FCNCALL_SUBNAME("hit_pattern");
  { FCNCALL_CALL_CTRL_WRAP(hit_pattern,hit_pattern.FCNCALL_CALL(hit_pattern)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA16,DATA16,16> channel_trigger_time_hi;
  {
  FCNCALL_SUBNAME("channel_trigger_time_hi");
  { FCNCALL_CALL_CTRL_WRAP(channel_trigger_time_hi,channel_trigger_time_hi.FCNCALL_CALL(channel_trigger_time_hi)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA32,DATA32,16> channel_trigger_time_lo;
  {
  FCNCALL_SUBNAME("channel_trigger_time_lo");
  { FCNCALL_CALL_CTRL_WRAP(channel_trigger_time_lo,channel_trigger_time_lo.FCNCALL_CALL(channel_trigger_time_lo)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA8,DATA8,16> pileup;
  {
  FCNCALL_SUBNAME("pileup");
  { FCNCALL_CALL_CTRL_WRAP(pileup,pileup.FCNCALL_CALL(pileup)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA8,DATA8,16> overflow;
  {
  FCNCALL_SUBNAME("overflow");
  { FCNCALL_CALL_CTRL_WRAP(overflow,overflow.FCNCALL_CALL(overflow)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA8,DATA8,16> channel_cfd;
  {
  FCNCALL_SUBNAME("channel_cfd");
  { FCNCALL_CALL_CTRL_WRAP(channel_cfd,channel_cfd.FCNCALL_CALL(channel_cfd)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA32,DATA32,16> channel_energy;
  {
  FCNCALL_SUBNAME("channel_energy");
  { FCNCALL_CALL_CTRL_WRAP(channel_energy,channel_energy.FCNCALL_CALL(channel_energy)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_FEBEX_EVENT

#ifndef USER_DEF_FEBEX_EVENT_TRACES
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(FEBEX_EVENT_TRACES)::FCNCALL_NAME(FEBEX_EVENT_TRACES)
{
  FCNCALL_INIT;
  // DATA8 trig;
  {
  FCNCALL_SUBNAME("trig");
  { FCNCALL_CALL_CTRL_WRAP(trig,trig.FCNCALL_CALL(trig)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA32 event_trigger_time_hi;
  {
  FCNCALL_SUBNAME("event_trigger_time_hi");
  { FCNCALL_CALL_CTRL_WRAP(event_trigger_time_hi,event_trigger_time_hi.FCNCALL_CALL(event_trigger_time_hi)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA32 event_trigger_time_lo;
  {
  FCNCALL_SUBNAME("event_trigger_time_lo");
  { FCNCALL_CALL_CTRL_WRAP(event_trigger_time_lo,event_trigger_time_lo.FCNCALL_CALL(event_trigger_time_lo)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA16 hit_pattern;
  {
  FCNCALL_SUBNAME("hit_pattern");
  { FCNCALL_CALL_CTRL_WRAP(hit_pattern,hit_pattern.FCNCALL_CALL(hit_pattern)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA32 num_channels_fired;
  {
  FCNCALL_SUBNAME("num_channels_fired");
  { FCNCALL_CALL_CTRL_WRAP(num_channels_fired,num_channels_fired.FCNCALL_CALL(num_channels_fired)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA8 board_num;
  {
  FCNCALL_SUBNAME("board_num");
  { FCNCALL_CALL_CTRL_WRAP(board_num,board_num.FCNCALL_CALL(board_num)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA8,DATA8,16> channel_id;
  {
  FCNCALL_SUBNAME("channel_id");
  { FCNCALL_CALL_CTRL_WRAP(channel_id,channel_id.FCNCALL_CALL(channel_id)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA16,DATA16,16> channel_trigger_time_hi;
  {
  FCNCALL_SUBNAME("channel_trigger_time_hi");
  { FCNCALL_CALL_CTRL_WRAP(channel_trigger_time_hi,channel_trigger_time_hi.FCNCALL_CALL(channel_trigger_time_hi)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA32,DATA32,16> channel_trigger_time_lo;
  {
  FCNCALL_SUBNAME("channel_trigger_time_lo");
  { FCNCALL_CALL_CTRL_WRAP(channel_trigger_time_lo,channel_trigger_time_lo.FCNCALL_CALL(channel_trigger_time_lo)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array<DATA8,DATA8,16> pileup;
  {
  FCNCALL_SUBNAME("pileup");
  { FCNCALL_CALL_CTRL_WRAP(pileup,pileup.FCNCALL_CALL(pileup)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array<DATA8,DATA8,16> overflow;
  {
  FCNCALL_SUBNAME("overflow");
  { FCNCALL_CALL_CTRL_WRAP(overflow,overflow.FCNCALL_CALL(overflow)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA8,DATA8,16> channel_cfd;
  {
  FCNCALL_SUBNAME("channel_cfd");
  { FCNCALL_CALL_CTRL_WRAP(channel_cfd,channel_cfd.FCNCALL_CALL(channel_cfd)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA32,DATA32,16> channel_energy;
  {
  FCNCALL_SUBNAME("channel_energy");
  { FCNCALL_CALL_CTRL_WRAP(channel_energy,channel_energy.FCNCALL_CALL(channel_energy)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA16,DATA16,4000> traces[16];
  {
  FCNCALL_SUBNAME("traces");
  FCNCALL_FOR(__i0,16)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(traces__i0,,__i0,traces[__i0].FCNCALL_CALL(traces[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
  // DUMMY dummy;
  {
  FCNCALL_SUBNAME("dummy");
  { FCNCALL_CALL_CTRL_WRAP(dummy,dummy.FCNCALL_CALL(dummy)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_FEBEX_EVENT_TRACES

#ifndef USER_DEF_FEBEX_PADDING
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(FEBEX_PADDING)::FCNCALL_NAME(FEBEX_PADDING)
{
  FCNCALL_INIT;
  FCNCALL_RET;
}
#endif//USER_DEF_FEBEX_PADDING

#ifndef USER_DEF_TAMEX4_EPOCH_DATA
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TAMEX4_EPOCH_DATA)::FCNCALL_NAME(TAMEX4_EPOCH_DATA)
{
  FCNCALL_INIT;
  FCNCALL_RET;
}
#endif//USER_DEF_TAMEX4_EPOCH_DATA

#ifndef USER_DEF_TAMEX4_HEADER
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TAMEX4_HEADER)::FCNCALL_NAME(TAMEX4_HEADER)
{
  FCNCALL_INIT;
  // DATA16 post_trig_ns;
  {
  FCNCALL_SUBNAME("post_trig_ns");
  { FCNCALL_CALL_CTRL_WRAP(post_trig_ns,post_trig_ns.FCNCALL_CALL(post_trig_ns)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA16 pre_trig_ns;
  {
  FCNCALL_SUBNAME("pre_trig_ns");
  { FCNCALL_CALL_CTRL_WRAP(pre_trig_ns,pre_trig_ns.FCNCALL_CALL(pre_trig_ns)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_TAMEX4_HEADER

#ifndef USER_DEF_TAMEX4_PADDING
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TAMEX4_PADDING)::FCNCALL_NAME(TAMEX4_PADDING)
{
  FCNCALL_INIT;
  FCNCALL_RET;
}
#endif//USER_DEF_TAMEX4_PADDING

#ifndef USER_DEF_TAMEX4_TIME_DATA
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TAMEX4_TIME_DATA)::FCNCALL_NAME(TAMEX4_TIME_DATA)
{
  FCNCALL_INIT;
  FCNCALL_RET;
}
#endif//USER_DEF_TAMEX4_TIME_DATA

#ifndef USER_DEF_TAMEX4_SFP
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TAMEX4_SFP)::FCNCALL_NAME(TAMEX4_SFP)
{
  FCNCALL_INIT;
  // DATA16 trig;
  {
  FCNCALL_SUBNAME("trig");
  { FCNCALL_CALL_CTRL_WRAP(trig,trig.FCNCALL_CALL(trig)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA32 event_size;
  {
  FCNCALL_SUBNAME("event_size");
  { FCNCALL_CALL_CTRL_WRAP(event_size,event_size.FCNCALL_CALL(event_size)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_list_ii_zero_suppress<DATA12,DATA12,1024> time_coarse;
  {
  FCNCALL_SUBNAME("time_coarse");
  { FCNCALL_CALL_CTRL_WRAP(time_coarse,time_coarse.FCNCALL_CALL(time_coarse)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_list_ii_zero_suppress<DATA12,DATA12,1024> time_fine;
  {
  FCNCALL_SUBNAME("time_fine");
  { FCNCALL_CALL_CTRL_WRAP(time_fine,time_fine.FCNCALL_CALL(time_fine)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_list_ii_zero_suppress<DATA12,DATA12,1024> time_edge;
  {
  FCNCALL_SUBNAME("time_edge");
  { FCNCALL_CALL_CTRL_WRAP(time_edge,time_edge.FCNCALL_CALL(time_edge)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_list_ii_zero_suppress<DATA12,DATA12,1024> time_channel;
  {
  FCNCALL_SUBNAME("time_channel");
  { FCNCALL_CALL_CTRL_WRAP(time_channel,time_channel.FCNCALL_CALL(time_channel)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_list_ii_zero_suppress<DATA32,DATA32,1024> time_epoch;
  {
  FCNCALL_SUBNAME("time_epoch");
  { FCNCALL_CALL_CTRL_WRAP(time_epoch,time_epoch.FCNCALL_CALL(time_epoch)); }
  FCNCALL_SUBNAME_END;
  }
  // TAMEX4_EPOCH_DATA epoch;
  {
  FCNCALL_SUBNAME("epoch");
  { FCNCALL_CALL_CTRL_WRAP(epoch,epoch.FCNCALL_CALL(epoch)); }
  FCNCALL_SUBNAME_END;
  }
  // TAMEX4_TIME_DATA time;
  {
  FCNCALL_SUBNAME("time");
  { FCNCALL_CALL_CTRL_WRAP(time,time.FCNCALL_CALL(time)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_TAMEX4_SFP

#ifndef USER_DEF_TIMESTAMP_WHITERABBIT
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TIMESTAMP_WHITERABBIT)::FCNCALL_NAME(TIMESTAMP_WHITERABBIT)
{
  FCNCALL_INIT;
  // DATA12 subsystem_id;
  {
  FCNCALL_SUBNAME("subsystem_id");
  { FCNCALL_CALL_CTRL_WRAP(subsystem_id,subsystem_id.FCNCALL_CALL(subsystem_id)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA16 t1;
  {
  FCNCALL_SUBNAME("t1");
  { FCNCALL_CALL_CTRL_WRAP(t1,t1.FCNCALL_CALL(t1)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA16 t2;
  {
  FCNCALL_SUBNAME("t2");
  { FCNCALL_CALL_CTRL_WRAP(t2,t2.FCNCALL_CALL(t2)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA16 t3;
  {
  FCNCALL_SUBNAME("t3");
  { FCNCALL_CALL_CTRL_WRAP(t3,t3.FCNCALL_CALL(t3)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA16 t4;
  {
  FCNCALL_SUBNAME("t4");
  { FCNCALL_CALL_CTRL_WRAP(t4,t4.FCNCALL_CALL(t4)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_TIMESTAMP_WHITERABBIT

#ifndef USER_DEF_TIMESTAMP_WHITERABBIT_EXTENDED
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TIMESTAMP_WHITERABBIT_EXTENDED)::FCNCALL_NAME(TIMESTAMP_WHITERABBIT_EXTENDED)
{
  FCNCALL_INIT;
  // DATA16 subsystem_id;
  {
  FCNCALL_SUBNAME("subsystem_id");
  { FCNCALL_CALL_CTRL_WRAP(subsystem_id,subsystem_id.FCNCALL_CALL(subsystem_id)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA16 t1;
  {
  FCNCALL_SUBNAME("t1");
  { FCNCALL_CALL_CTRL_WRAP(t1,t1.FCNCALL_CALL(t1)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA16 t2;
  {
  FCNCALL_SUBNAME("t2");
  { FCNCALL_CALL_CTRL_WRAP(t2,t2.FCNCALL_CALL(t2)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA16 t3;
  {
  FCNCALL_SUBNAME("t3");
  { FCNCALL_CALL_CTRL_WRAP(t3,t3.FCNCALL_CALL(t3)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA16 t4;
  {
  FCNCALL_SUBNAME("t4");
  { FCNCALL_CALL_CTRL_WRAP(t4,t4.FCNCALL_CALL(t4)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_TIMESTAMP_WHITERABBIT_EXTENDED

#ifndef USER_DEF_VME_CAEN_V1751
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(VME_CAEN_V1751)::FCNCALL_NAME(VME_CAEN_V1751)
{
  FCNCALL_INIT;
  // DATA8 board_id;
  {
  FCNCALL_SUBNAME("board_id");
  { FCNCALL_CALL_CTRL_WRAP(board_id,board_id.FCNCALL_CALL(board_id)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA8 channels;
  {
  FCNCALL_SUBNAME("channels");
  { FCNCALL_CALL_CTRL_WRAP(channels,channels.FCNCALL_CALL(channels)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA32 board_time;
  {
  FCNCALL_SUBNAME("board_time");
  { FCNCALL_CALL_CTRL_WRAP(board_time,board_time.FCNCALL_CALL(board_time)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_list_ii_zero_suppress<DATA32,DATA32,64> channel_time;
  {
  FCNCALL_SUBNAME("channel_time");
  { FCNCALL_CALL_CTRL_WRAP(channel_time,channel_time.FCNCALL_CALL(channel_time)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_list_ii_zero_suppress<DATA16,DATA16,64> chan_ext_time;
  {
  FCNCALL_SUBNAME("chan_ext_time");
  { FCNCALL_CALL_CTRL_WRAP(chan_ext_time,chan_ext_time.FCNCALL_CALL(chan_ext_time)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_list_ii_zero_suppress<DATA12,DATA12,64> chan_fine_time;
  {
  FCNCALL_SUBNAME("chan_fine_time");
  { FCNCALL_CALL_CTRL_WRAP(chan_fine_time,chan_fine_time.FCNCALL_CALL(chan_fine_time)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_list_ii_zero_suppress<DATA16,DATA16,64> qshort;
  {
  FCNCALL_SUBNAME("qshort");
  { FCNCALL_CALL_CTRL_WRAP(qshort,qshort.FCNCALL_CALL(qshort)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_list_ii_zero_suppress<DATA16,DATA16,64> qlong;
  {
  FCNCALL_SUBNAME("qlong");
  { FCNCALL_CALL_CTRL_WRAP(qlong,qlong.FCNCALL_CALL(qlong)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_VME_CAEN_V1751

#ifndef USER_DEF_WR_MULTI
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(WR_MULTI)::FCNCALL_NAME(WR_MULTI)
{
  FCNCALL_INIT;
  // DATA32 time_hi;
  {
  FCNCALL_SUBNAME("time_hi");
  { FCNCALL_CALL_CTRL_WRAP(time_hi,time_hi.FCNCALL_CALL(time_hi)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA32 time_lo;
  {
  FCNCALL_SUBNAME("time_lo");
  { FCNCALL_CALL_CTRL_WRAP(time_lo,time_lo.FCNCALL_CALL(time_lo)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_WR_MULTI

#ifndef USER_DEF_bplast_subev
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(bplast_subev)::FCNCALL_NAME(bplast_subev)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_subevent_base,FCNCALL_CLASS_NAME(unpack_subevent_base)::FCNCALL_CALL_BASE());
  // TIMESTAMP_WHITERABBIT ts;
  {
  FCNCALL_SUBNAME("ts");
  { FCNCALL_CALL_CTRL_WRAP(ts,ts.FCNCALL_CALL(ts)); }
  FCNCALL_SUBNAME_END;
  }
  // TAMEX4_HEADER trigger_window;
  {
  FCNCALL_SUBNAME("trigger_window");
  { FCNCALL_CALL_CTRL_WRAP(trigger_window,trigger_window.FCNCALL_CALL(trigger_window)); }
  FCNCALL_SUBNAME_END;
  }
  // TAMEX4_PADDING padding;
  {
  FCNCALL_SUBNAME("padding");
  { FCNCALL_CALL_CTRL_WRAP(padding,padding.FCNCALL_CALL(padding)); }
  FCNCALL_SUBNAME_END;
  }
  // TAMEX4_SFP tamex[9];
  {
  FCNCALL_SUBNAME("tamex");
  FCNCALL_FOR(__i0,9)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(tamex__i0,,__i0,tamex[__i0].FCNCALL_CALL(tamex[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_bplast_subev

#ifndef USER_DEF_fatima_tamex_subev
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(fatima_tamex_subev)::FCNCALL_NAME(fatima_tamex_subev)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_subevent_base,FCNCALL_CLASS_NAME(unpack_subevent_base)::FCNCALL_CALL_BASE());
  // TIMESTAMP_WHITERABBIT_EXTENDED ts;
  {
  FCNCALL_SUBNAME("ts");
  { FCNCALL_CALL_CTRL_WRAP(ts,ts.FCNCALL_CALL(ts)); }
  FCNCALL_SUBNAME_END;
  }
  // TAMEX4_SFP data[4];
  {
  FCNCALL_SUBNAME("data");
  FCNCALL_FOR(__i0,4)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(data__i0,,__i0,data[__i0].FCNCALL_CALL(data[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_fatima_tamex_subev

#ifndef USER_DEF_unpack_event
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(unpack_event)::FCNCALL_NAME(unpack_event)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_event_base,FCNCALL_CLASS_NAME(unpack_event_base)::FCNCALL_CALL_BASE());
  // fatima_tamex_subev fatima;
  {
  FCNCALL_SUBNAME("fatima");
  { FCNCALL_CALL_CTRL_WRAP(fatima,fatima.FCNCALL_CALL(fatima)); }
  FCNCALL_SUBNAME_END;
  }
  // bplast_subev bplast;
  {
  FCNCALL_SUBNAME("bplast");
  { FCNCALL_CALL_CTRL_WRAP(bplast,bplast.FCNCALL_CALL(bplast)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_unpack_event

#ifndef USER_DEF_unpack_sticky_event
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(unpack_sticky_event)::FCNCALL_NAME(unpack_sticky_event)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_sticky_event_base,FCNCALL_CLASS_NAME(unpack_sticky_event_base)::FCNCALL_CALL_BASE());
  FCNCALL_RET;
}
#endif//USER_DEF_unpack_sticky_event

#include "gen/default_fcncall_undef.hh"


/** END_FUNCTION_CALL_PER_MEMBER **************************************/
