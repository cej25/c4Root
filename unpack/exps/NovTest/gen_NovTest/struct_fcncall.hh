/** BEGIN_FUNCTION_CALL_PER_MEMBER *************************************
 *
 * Recursive function calls per member.
 *
 * Do not edit - automatically generated.
 */

#include "gen/default_fcncall_define.hh"

#ifndef USER_DEF_BARRIER
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(BARRIER)::FCNCALL_NAME(BARRIER)
{
  FCNCALL_INIT;
  FCNCALL_RET;
}
#endif//USER_DEF_BARRIER

#ifndef USER_DEF_FEBEX_EVENT
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(FEBEX_EVENT)::FCNCALL_NAME(FEBEX_EVENT)
{
  FCNCALL_INIT;
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
  // raw_array_zero_suppress<DATA16,DATA16,10000> traces[16];
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

#ifndef USER_DEF_VME_CAEN_V830_FRS
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(VME_CAEN_V830_FRS)::FCNCALL_NAME(VME_CAEN_V830_FRS)
{
  FCNCALL_INIT;
  // raw_array_zero_suppress<DATA32,DATA32,32> data;
  {
  FCNCALL_SUBNAME("data");
  { FCNCALL_CALL_CTRL_WRAP(data,data.FCNCALL_CALL(data)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_VME_CAEN_V830_FRS

#ifndef USER_DEF_ZERO_FILLER
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(ZERO_FILLER)::FCNCALL_NAME(ZERO_FILLER)
{
  FCNCALL_INIT;
  FCNCALL_RET;
}
#endif//USER_DEF_ZERO_FILLER

#ifndef USER_DEF_VME_CAEN_V792_FRS
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(VME_CAEN_V792_FRS)::FCNCALL_NAME(VME_CAEN_V792_FRS)
{
  FCNCALL_INIT;
  // raw_array_multi_zero_suppress<DATA32,DATA32,32,32> data;
  {
  FCNCALL_SUBNAME("data");
  { FCNCALL_CALL_CTRL_WRAP(data,data.FCNCALL_CALL(data)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA8 geo;
  {
  FCNCALL_SUBNAME("geo");
  { FCNCALL_CALL_CTRL_WRAP(geo,geo.FCNCALL_CALL(geo)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_VME_CAEN_V792_FRS

#ifndef USER_DEF_TDC_HEADER
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TDC_HEADER)::FCNCALL_NAME(TDC_HEADER)
{
  FCNCALL_INIT;
  FCNCALL_RET;
}
#endif//USER_DEF_TDC_HEADER

#ifndef USER_DEF_TDC_DATA_V1290
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TDC_DATA_V1290)::FCNCALL_NAME(TDC_DATA_V1290)
{
  FCNCALL_INIT;
  FCNCALL_RET;
}
#endif//USER_DEF_TDC_DATA_V1290

#ifndef USER_DEF_TDC_ERROR
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TDC_ERROR)::FCNCALL_NAME(TDC_ERROR)
{
  FCNCALL_INIT;
  FCNCALL_RET;
}
#endif//USER_DEF_TDC_ERROR

#ifndef USER_DEF_TDC_TRAILER
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TDC_TRAILER)::FCNCALL_NAME(TDC_TRAILER)
{
  FCNCALL_INIT;
  FCNCALL_RET;
}
#endif//USER_DEF_TDC_TRAILER

#ifndef USER_DEF_VME_CAEN_V1290_FRS
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(VME_CAEN_V1290_FRS)::FCNCALL_NAME(VME_CAEN_V1290_FRS)
{
  FCNCALL_INIT;
  // raw_array_multi_zero_suppress<DATA24,DATA24,128,128> data;
  {
  FCNCALL_SUBNAME("data");
  { FCNCALL_CALL_CTRL_WRAP(data,data.FCNCALL_CALL(data)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_multi_zero_suppress<DATA8,DATA8,128,128> leadOrTrail;
  {
  FCNCALL_SUBNAME("leadOrTrail");
  { FCNCALL_CALL_CTRL_WRAP(leadOrTrail,leadOrTrail.FCNCALL_CALL(leadOrTrail)); }
  FCNCALL_SUBNAME_END;
  }
  // TDC_HEADER tdc_header;
  {
  FCNCALL_SUBNAME("tdc_header");
  { FCNCALL_CALL_CTRL_WRAP(tdc_header,tdc_header.FCNCALL_CALL(tdc_header)); }
  FCNCALL_SUBNAME_END;
  }
  // TDC_DATA_V1290 measurement;
  {
  FCNCALL_SUBNAME("measurement");
  { FCNCALL_CALL_CTRL_WRAP(measurement,measurement.FCNCALL_CALL(measurement)); }
  FCNCALL_SUBNAME_END;
  }
  // TDC_ERROR tdc_err;
  {
  FCNCALL_SUBNAME("tdc_err");
  { FCNCALL_CALL_CTRL_WRAP(tdc_err,tdc_err.FCNCALL_CALL(tdc_err)); }
  FCNCALL_SUBNAME_END;
  }
  // TDC_TRAILER tdc_trailer;
  {
  FCNCALL_SUBNAME("tdc_trailer");
  { FCNCALL_CALL_CTRL_WRAP(tdc_trailer,tdc_trailer.FCNCALL_CALL(tdc_trailer)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_VME_CAEN_V1290_FRS

#ifndef USER_DEF_MAIN_CRATE_DATA
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(MAIN_CRATE_DATA)::FCNCALL_NAME(MAIN_CRATE_DATA)
{
  FCNCALL_INIT;
  // BARRIER barrier[3];
  {
  FCNCALL_SUBNAME("barrier");
  FCNCALL_FOR(__i0,3)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(barrier__i0,,__i0,barrier[__i0].FCNCALL_CALL(barrier[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
  // VME_CAEN_V830_FRS v830;
  {
  FCNCALL_SUBNAME("v830");
  { FCNCALL_CALL_CTRL_WRAP(v830,v830.FCNCALL_CALL(v830)); }
  FCNCALL_SUBNAME_END;
  }
  // ZERO_FILLER filler[1];
  {
  FCNCALL_SUBNAME("filler");
  FCNCALL_FOR(__i0,1)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(filler__i0,,__i0,filler[__i0].FCNCALL_CALL(filler[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
  // VME_CAEN_V792_FRS v792;
  {
  FCNCALL_SUBNAME("v792");
  { FCNCALL_CALL_CTRL_WRAP(v792,v792.FCNCALL_CALL(v792)); }
  FCNCALL_SUBNAME_END;
  }
  // VME_CAEN_V1290_FRS v1290;
  {
  FCNCALL_SUBNAME("v1290");
  { FCNCALL_CALL_CTRL_WRAP(v1290,v1290.FCNCALL_CALL(v1290)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_MAIN_CRATE_DATA

#ifndef USER_DEF_MESYTEC_MQDC32_FRS
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(MESYTEC_MQDC32_FRS)::FCNCALL_NAME(MESYTEC_MQDC32_FRS)
{
  FCNCALL_INIT;
  // raw_array_zero_suppress<DATA12_OVERFLOW,DATA12_OVERFLOW,32> data;
  {
  FCNCALL_SUBNAME("data");
  { FCNCALL_CALL_CTRL_WRAP(data,data.FCNCALL_CALL(data)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_MESYTEC_MQDC32_FRS

#ifndef USER_DEF_MESYTEC_MTDC32_FRS
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(MESYTEC_MTDC32_FRS)::FCNCALL_NAME(MESYTEC_MTDC32_FRS)
{
  FCNCALL_INIT;
  // raw_array_zero_suppress<DATA16,DATA16,34> data;
  {
  FCNCALL_SUBNAME("data");
  { FCNCALL_CALL_CTRL_WRAP(data,data.FCNCALL_CALL(data)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_MESYTEC_MTDC32_FRS

#ifndef USER_DEF_SIS_3820_FRS
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(SIS_3820_FRS)::FCNCALL_NAME(SIS_3820_FRS)
{
  FCNCALL_INIT;
  // raw_array_zero_suppress<DATA32,DATA32,32> data;
  {
  FCNCALL_SUBNAME("data");
  { FCNCALL_CALL_CTRL_WRAP(data,data.FCNCALL_CALL(data)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_SIS_3820_FRS

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
  // raw_list_ii_zero_suppress<DATA16,DATA16,64> post_trig_ns;
  {
  FCNCALL_SUBNAME("post_trig_ns");
  { FCNCALL_CALL_CTRL_WRAP(post_trig_ns,post_trig_ns.FCNCALL_CALL(post_trig_ns)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_list_ii_zero_suppress<DATA16,DATA16,64> pre_trig_ns;
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

#ifndef USER_DEF_TDC_DATA_V1190
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TDC_DATA_V1190)::FCNCALL_NAME(TDC_DATA_V1190)
{
  FCNCALL_INIT;
  FCNCALL_RET;
}
#endif//USER_DEF_TDC_DATA_V1190

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

#ifndef USER_DEF_VME_CAEN_V7X5_FRS
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(VME_CAEN_V7X5_FRS)::FCNCALL_NAME(VME_CAEN_V7X5_FRS)
{
  FCNCALL_INIT;
  // raw_array_zero_suppress<DATA12_OVERFLOW,DATA12_OVERFLOW,32> data;
  {
  FCNCALL_SUBNAME("data");
  { FCNCALL_CALL_CTRL_WRAP(data,data.FCNCALL_CALL(data)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA8,DATA8,32> channel;
  {
  FCNCALL_SUBNAME("channel");
  { FCNCALL_CALL_CTRL_WRAP(channel,channel.FCNCALL_CALL(channel)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_zero_suppress<DATA8,DATA8,32> geo;
  {
  FCNCALL_SUBNAME("geo");
  { FCNCALL_CALL_CTRL_WRAP(geo,geo.FCNCALL_CALL(geo)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_VME_CAEN_V7X5_FRS

#ifndef USER_DEF_VME_CAEN_V1190_FRS
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(VME_CAEN_V1190_FRS)::FCNCALL_NAME(VME_CAEN_V1190_FRS)
{
  FCNCALL_INIT;
  // raw_array_multi_zero_suppress<DATA24,DATA24,128,128> data;
  {
  FCNCALL_SUBNAME("data");
  { FCNCALL_CALL_CTRL_WRAP(data,data.FCNCALL_CALL(data)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_multi_zero_suppress<DATA8,DATA8,128,128> leadOrTrail;
  {
  FCNCALL_SUBNAME("leadOrTrail");
  { FCNCALL_CALL_CTRL_WRAP(leadOrTrail,leadOrTrail.FCNCALL_CALL(leadOrTrail)); }
  FCNCALL_SUBNAME_END;
  }
  // TDC_HEADER tdc_header;
  {
  FCNCALL_SUBNAME("tdc_header");
  { FCNCALL_CALL_CTRL_WRAP(tdc_header,tdc_header.FCNCALL_CALL(tdc_header)); }
  FCNCALL_SUBNAME_END;
  }
  // TDC_DATA_V1190 measurement;
  {
  FCNCALL_SUBNAME("measurement");
  { FCNCALL_CALL_CTRL_WRAP(measurement,measurement.FCNCALL_CALL(measurement)); }
  FCNCALL_SUBNAME_END;
  }
  // TDC_ERROR tdc_error;
  {
  FCNCALL_SUBNAME("tdc_error");
  { FCNCALL_CALL_CTRL_WRAP(tdc_error,tdc_error.FCNCALL_CALL(tdc_error)); }
  FCNCALL_SUBNAME_END;
  }
  // TDC_TRAILER tdc_trailer;
  {
  FCNCALL_SUBNAME("tdc_trailer");
  { FCNCALL_CALL_CTRL_WRAP(tdc_trailer,tdc_trailer.FCNCALL_CALL(tdc_trailer)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_VME_CAEN_V1190_FRS

#ifndef USER_DEF_TPC_CRATE_DATA
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TPC_CRATE_DATA)::FCNCALL_NAME(TPC_CRATE_DATA)
{
  FCNCALL_INIT;
  // BARRIER barrier[3];
  {
  FCNCALL_SUBNAME("barrier");
  FCNCALL_FOR(__i0,3)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(barrier__i0,,__i0,barrier[__i0].FCNCALL_CALL(barrier[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
  // VME_CAEN_V7X5_FRS v775;
  {
  FCNCALL_SUBNAME("v775");
  { FCNCALL_CALL_CTRL_WRAP(v775,v775.FCNCALL_CALL(v775)); }
  FCNCALL_SUBNAME_END;
  }
  // VME_CAEN_V7X5_FRS v785;
  {
  FCNCALL_SUBNAME("v785");
  { FCNCALL_CALL_CTRL_WRAP(v785,v785.FCNCALL_CALL(v785)); }
  FCNCALL_SUBNAME_END;
  }
  // VME_CAEN_V1190_FRS v1190;
  {
  FCNCALL_SUBNAME("v1190");
  { FCNCALL_CALL_CTRL_WRAP(v1190,v1190.FCNCALL_CALL(v1190)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_TPC_CRATE_DATA

#ifndef USER_DEF_TRIG3EVENT
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(TRIG3EVENT)::FCNCALL_NAME(TRIG3EVENT)
{
  FCNCALL_INIT;
  FCNCALL_RET;
}
#endif//USER_DEF_TRIG3EVENT

#ifndef USER_DEF_USER_CRATE_DATA
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(USER_CRATE_DATA)::FCNCALL_NAME(USER_CRATE_DATA)
{
  FCNCALL_INIT;
  // BARRIER barrier[5];
  {
  FCNCALL_SUBNAME("barrier");
  FCNCALL_FOR(__i0,5)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(barrier__i0,,__i0,barrier[__i0].FCNCALL_CALL(barrier[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
  // VME_CAEN_V830_FRS v830;
  {
  FCNCALL_SUBNAME("v830");
  { FCNCALL_CALL_CTRL_WRAP(v830,v830.FCNCALL_CALL(v830)); }
  FCNCALL_SUBNAME_END;
  }
  // ZERO_FILLER filler[1];
  {
  FCNCALL_SUBNAME("filler");
  FCNCALL_FOR(__i0,1)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(filler__i0,,__i0,filler[__i0].FCNCALL_CALL(filler[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
  // VME_CAEN_V7X5_FRS v775[2];
  {
  FCNCALL_SUBNAME("v775");
  FCNCALL_FOR(__i0,2)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(v775__i0,,__i0,v775[__i0].FCNCALL_CALL(v775[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
  // VME_CAEN_V7X5_FRS v785[2];
  {
  FCNCALL_SUBNAME("v785");
  FCNCALL_FOR(__i0,2)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(v785__i0,,__i0,v785[__i0].FCNCALL_CALL(v785[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_USER_CRATE_DATA

#ifndef USER_DEF_VFTX2
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(VFTX2)::FCNCALL_NAME(VFTX2)
{
  FCNCALL_INIT;
  // raw_array_multi_zero_suppress<DATA12,DATA12,32,100> time_fine;
  {
  FCNCALL_SUBNAME("time_fine");
  { FCNCALL_CALL_CTRL_WRAP(time_fine,time_fine.FCNCALL_CALL(time_fine)); }
  FCNCALL_SUBNAME_END;
  }
  // raw_array_multi_zero_suppress<DATA16,DATA16,32,100> time_coarse;
  {
  FCNCALL_SUBNAME("time_coarse");
  { FCNCALL_CALL_CTRL_WRAP(time_coarse,time_coarse.FCNCALL_CALL(time_coarse)); }
  FCNCALL_SUBNAME_END;
  }
  // DATA16 time_trigger;
  {
  FCNCALL_SUBNAME("time_trigger");
  { FCNCALL_CALL_CTRL_WRAP(time_trigger,time_trigger.FCNCALL_CALL(time_trigger)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_VFTX2

#ifndef USER_DEF_VFTX_CRATE_DATA
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(VFTX_CRATE_DATA)::FCNCALL_NAME(VFTX_CRATE_DATA)
{
  FCNCALL_INIT;
  // MESYTEC_MQDC32_FRS mqdc0;
  {
  FCNCALL_SUBNAME("mqdc0");
  { FCNCALL_CALL_CTRL_WRAP(mqdc0,mqdc0.FCNCALL_CALL(mqdc0)); }
  FCNCALL_SUBNAME_END;
  }
  // MESYTEC_MQDC32_FRS mqdc1;
  {
  FCNCALL_SUBNAME("mqdc1");
  { FCNCALL_CALL_CTRL_WRAP(mqdc1,mqdc1.FCNCALL_CALL(mqdc1)); }
  FCNCALL_SUBNAME_END;
  }
  // VFTX2 vftx;
  {
  FCNCALL_SUBNAME("vftx");
  { FCNCALL_CALL_CTRL_WRAP(vftx,vftx.FCNCALL_CALL(vftx)); }
  FCNCALL_SUBNAME_END;
  }
  // BARRIER barrier[3];
  {
  FCNCALL_SUBNAME("barrier");
  FCNCALL_FOR(__i0,3)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(barrier__i0,,__i0,barrier[__i0].FCNCALL_CALL(barrier[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
  // MESYTEC_MTDC32_FRS mtdc;
  {
  FCNCALL_SUBNAME("mtdc");
  { FCNCALL_CALL_CTRL_WRAP(mtdc,mtdc.FCNCALL_CALL(mtdc)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_VFTX_CRATE_DATA

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

#ifndef USER_DEF_aida_subev
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(aida_subev)::FCNCALL_NAME(aida_subev)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_subevent_base,FCNCALL_CLASS_NAME(unpack_subevent_base)::FCNCALL_CALL_BASE());
  // TIMESTAMP_WHITERABBIT ts;
  {
  FCNCALL_SUBNAME("ts");
  { FCNCALL_CALL_CTRL_WRAP(ts,ts.FCNCALL_CALL(ts)); }
  FCNCALL_SUBNAME_END;
  }
  // EXT_AIDA data;
  {
  FCNCALL_SUBNAME("data");
  { FCNCALL_CALL_CTRL_WRAP(data,data.FCNCALL_CALL(data)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_aida_subev

#ifndef USER_DEF_bplast_subev
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(bplast_subev)::FCNCALL_NAME(bplast_subev)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_subevent_base,FCNCALL_CLASS_NAME(unpack_subevent_base)::FCNCALL_CALL_BASE());
  // TAMEX4_PADDING padding;
  {
  FCNCALL_SUBNAME("padding");
  { FCNCALL_CALL_CTRL_WRAP(padding,padding.FCNCALL_CALL(padding)); }
  FCNCALL_SUBNAME_END;
  }
  // TAMEX4_SFP tamex[5];
  {
  FCNCALL_SUBNAME("tamex");
  FCNCALL_FOR(__i0,5)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(tamex__i0,,__i0,tamex[__i0].FCNCALL_CALL(tamex[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
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
  FCNCALL_RET;
}
#endif//USER_DEF_bplast_subev

#ifndef USER_DEF_fatima_tamex_subev
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(fatima_tamex_subev)::FCNCALL_NAME(fatima_tamex_subev)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_subevent_base,FCNCALL_CLASS_NAME(unpack_subevent_base)::FCNCALL_CALL_BASE());
  // TAMEX4_PADDING padding;
  {
  FCNCALL_SUBNAME("padding");
  { FCNCALL_CALL_CTRL_WRAP(padding,padding.FCNCALL_CALL(padding)); }
  FCNCALL_SUBNAME_END;
  }
  // TAMEX4_SFP tamex[2];
  {
  FCNCALL_SUBNAME("tamex");
  FCNCALL_FOR(__i0,2)
  {
    FCNCALL_SUBINDEX(__i0);
    { FCNCALL_CALL_CTRL_WRAP_ARRAY(tamex__i0,,__i0,tamex[__i0].FCNCALL_CALL(tamex[__i0])); }
    FCNCALL_SUBINDEX_END(__i0);
  }
  FCNCALL_SUBNAME_END;
  }
  // TIMESTAMP_WHITERABBIT_EXTENDED ts;
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
  FCNCALL_RET;
}
#endif//USER_DEF_fatima_tamex_subev

#ifndef USER_DEF_febex_subev
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(febex_subev)::FCNCALL_NAME(febex_subev)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_subevent_base,FCNCALL_CLASS_NAME(unpack_subevent_base)::FCNCALL_CALL_BASE());
  // FEBEX_PADDING padding;
  {
  FCNCALL_SUBNAME("padding");
  { FCNCALL_CALL_CTRL_WRAP(padding,padding.FCNCALL_CALL(padding)); }
  FCNCALL_SUBNAME_END;
  }
  // FEBEX_EVENT data[4];
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
  // TIMESTAMP_WHITERABBIT ts;
  {
  FCNCALL_SUBNAME("ts");
  { FCNCALL_CALL_CTRL_WRAP(ts,ts.FCNCALL_CALL(ts)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_febex_subev

#ifndef USER_DEF_frs_main_subev
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(frs_main_subev)::FCNCALL_NAME(frs_main_subev)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_subevent_base,FCNCALL_CLASS_NAME(unpack_subevent_base)::FCNCALL_CALL_BASE());
  // TIMESTAMP_WHITERABBIT wr;
  {
  FCNCALL_SUBNAME("wr");
  { FCNCALL_CALL_CTRL_WRAP(wr,wr.FCNCALL_CALL(wr)); }
  FCNCALL_SUBNAME_END;
  }
  // TRIG3EVENT trig3;
  {
  FCNCALL_SUBNAME("trig3");
  { FCNCALL_CALL_CTRL_WRAP(trig3,trig3.FCNCALL_CALL(trig3)); }
  FCNCALL_SUBNAME_END;
  }
  // MAIN_CRATE_DATA data;
  {
  FCNCALL_SUBNAME("data");
  { FCNCALL_CALL_CTRL_WRAP(data,data.FCNCALL_CALL(data)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_frs_main_subev

#ifndef USER_DEF_frs_tpc_subev
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(frs_tpc_subev)::FCNCALL_NAME(frs_tpc_subev)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_subevent_base,FCNCALL_CLASS_NAME(unpack_subevent_base)::FCNCALL_CALL_BASE());
  // TRIG3EVENT trig3;
  {
  FCNCALL_SUBNAME("trig3");
  { FCNCALL_CALL_CTRL_WRAP(trig3,trig3.FCNCALL_CALL(trig3)); }
  FCNCALL_SUBNAME_END;
  }
  // TPC_CRATE_DATA data;
  {
  FCNCALL_SUBNAME("data");
  { FCNCALL_CALL_CTRL_WRAP(data,data.FCNCALL_CALL(data)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_frs_tpc_subev

#ifndef USER_DEF_frs_user_subev
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(frs_user_subev)::FCNCALL_NAME(frs_user_subev)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_subevent_base,FCNCALL_CLASS_NAME(unpack_subevent_base)::FCNCALL_CALL_BASE());
  // TRIG3EVENT trig3;
  {
  FCNCALL_SUBNAME("trig3");
  { FCNCALL_CALL_CTRL_WRAP(trig3,trig3.FCNCALL_CALL(trig3)); }
  FCNCALL_SUBNAME_END;
  }
  // USER_CRATE_DATA data;
  {
  FCNCALL_SUBNAME("data");
  { FCNCALL_CALL_CTRL_WRAP(data,data.FCNCALL_CALL(data)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_frs_user_subev

#ifndef USER_DEF_frs_vftx_subev
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(frs_vftx_subev)::FCNCALL_NAME(frs_vftx_subev)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_subevent_base,FCNCALL_CLASS_NAME(unpack_subevent_base)::FCNCALL_CALL_BASE());
  // TRIG3EVENT trig3;
  {
  FCNCALL_SUBNAME("trig3");
  { FCNCALL_CALL_CTRL_WRAP(trig3,trig3.FCNCALL_CALL(trig3)); }
  FCNCALL_SUBNAME_END;
  }
  // VFTX_CRATE_DATA data;
  {
  FCNCALL_SUBNAME("data");
  { FCNCALL_CALL_CTRL_WRAP(data,data.FCNCALL_CALL(data)); }
  FCNCALL_SUBNAME_END;
  }
  FCNCALL_RET;
}
#endif//USER_DEF_frs_vftx_subev

#ifndef USER_DEF_unpack_event
FCNCALL_TEMPLATE
FCNCALL_RET_TYPE FCNCALL_CLASS_NAME(unpack_event)::FCNCALL_NAME(unpack_event)
{
  FCNCALL_INIT;
  FCNCALL_CALL_CTRL_WRAP(unpack_event_base,FCNCALL_CLASS_NAME(unpack_event_base)::FCNCALL_CALL_BASE());
  // aida_subev aida;
  {
  FCNCALL_SUBNAME("aida");
  { FCNCALL_CALL_CTRL_WRAP(aida,aida.FCNCALL_CALL(aida)); }
  FCNCALL_SUBNAME_END;
  }
  // bplast_subev bplast;
  {
  FCNCALL_SUBNAME("bplast");
  { FCNCALL_CALL_CTRL_WRAP(bplast,bplast.FCNCALL_CALL(bplast)); }
  FCNCALL_SUBNAME_END;
  }
  // frs_main_subev frsmain;
  {
  FCNCALL_SUBNAME("frsmain");
  { FCNCALL_CALL_CTRL_WRAP(frsmain,frsmain.FCNCALL_CALL(frsmain)); }
  FCNCALL_SUBNAME_END;
  }
  // frs_tpc_subev frstpc;
  {
  FCNCALL_SUBNAME("frstpc");
  { FCNCALL_CALL_CTRL_WRAP(frstpc,frstpc.FCNCALL_CALL(frstpc)); }
  FCNCALL_SUBNAME_END;
  }
  // frs_user_subev frsuser;
  {
  FCNCALL_SUBNAME("frsuser");
  { FCNCALL_CALL_CTRL_WRAP(frsuser,frsuser.FCNCALL_CALL(frsuser)); }
  FCNCALL_SUBNAME_END;
  }
  // frs_vftx_subev frsvftx;
  {
  FCNCALL_SUBNAME("frsvftx");
  { FCNCALL_CALL_CTRL_WRAP(frsvftx,frsvftx.FCNCALL_CALL(frsvftx)); }
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
