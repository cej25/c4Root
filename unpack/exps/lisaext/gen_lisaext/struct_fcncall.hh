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

#ifndef USER_DEF_TRACE
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TRACE)::FCNCALL_NAME(TRACE)
{
  FCNCALL_INIT;
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
  // raw_array_zero_suppress<DATA8,DATA8,16> channel_id_traces;
  {
  FCNCALL_SUBNAME("channel_id_traces");
  { FCNCALL_CALL_CTRL_WRAP(channel_id_traces,channel_id_traces.FCNCALL_CALL(channel_id_traces)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_TRACE

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
  // TRACE trace;
  {
  FCNCALL_SUBNAME("trace");
  { FCNCALL_CALL_CTRL_WRAP(trace,trace.FCNCALL_CALL(trace)); }
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

#ifndef USER_DEF_TIMESTAMP_WHITERABBIT_EXTERNAL
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TIMESTAMP_WHITERABBIT_EXTERNAL)::FCNCALL_NAME(TIMESTAMP_WHITERABBIT_EXTERNAL)
{
  FCNCALL_INIT;
  // DATA16 subsystem_id;
  {
  FCNCALL_SUBNAME("subsystem_id");
  { FCNCALL_CALL_CTRL_WRAP(subsystem_id,subsystem_id.FCNCALL_CALL(subsystem_id)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA32 run;
  {
  FCNCALL_SUBNAME("run");
  { FCNCALL_CALL_CTRL_WRAP(run,run.FCNCALL_CALL(run)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA32 t1;
  {
  FCNCALL_SUBNAME("t1");
  { FCNCALL_CALL_CTRL_WRAP(t1,t1.FCNCALL_CALL(t1)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA32 t2;
  {
  FCNCALL_SUBNAME("t2");
  { FCNCALL_CALL_CTRL_WRAP(t2,t2.FCNCALL_CALL(t2)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_TIMESTAMP_WHITERABBIT_EXTERNAL

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

#ifndef USER_DEF_febex_subev_traces
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(febex_subev_traces)::FCNCALL_NAME(febex_subev_traces)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_subevent_base,FCNCALL_CLASS_NAME(unpack_subevent_base)::FCNCALL_CALL_BASE());
  // BAD_EVENT badevent;
  {
  FCNCALL_SUBNAME("badevent");
  { FCNCALL_CALL_CTRL_WRAP(badevent,badevent.FCNCALL_CALL(badevent)); }
  FCNCALL_SUBNAME_END;
  }
  // TIMESTAMP_WHITERABBIT_EXTERNAL ts;
  {
  FCNCALL_SUBNAME("ts");
  { FCNCALL_CALL_CTRL_WRAP(ts,ts.FCNCALL_CALL(ts)); }
  FCNCALL_SUBNAME_END;
  }
  // FEBEX_PADDING padding;
  {
  FCNCALL_SUBNAME("padding");
  { FCNCALL_CALL_CTRL_WRAP(padding,padding.FCNCALL_CALL(padding)); }
  FCNCALL_SUBNAME_END;
  }
  // FEBEX_EVENT_TRACES data[10];
  {
  FCNCALL_SUBNAME("data");
  FCNCALL_FOR(__i0,10)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(data__i0,,__i0,data[__i0].FCNCALL_CALL(data[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_febex_subev_traces

#ifndef USER_DEF_unpack_event
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(unpack_event)::FCNCALL_NAME(unpack_event)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_event_base,FCNCALL_CLASS_NAME(unpack_event_base)::FCNCALL_CALL_BASE());
  // febex_subev_traces lisa;
  {
  FCNCALL_SUBNAME("lisa");
  { FCNCALL_CALL_CTRL_WRAP(lisa,lisa.FCNCALL_CALL(lisa)); }
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
