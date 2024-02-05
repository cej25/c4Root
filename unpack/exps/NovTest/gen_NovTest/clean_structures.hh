class BARRIER
{
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(BARRIER);
};
class FEBEX_EVENT
{
  DATA32 event_trigger_time_hi;
  DATA32 event_trigger_time_lo;
  DATA16 hit_pattern;
  raw_array_zero_suppress<DATA16,DATA16,16> channel_trigger_time_hi;
  raw_array_zero_suppress<DATA32,DATA32,16> channel_trigger_time_lo;
  raw_array_zero_suppress<DATA8,DATA8,16> pileup;
  raw_array_zero_suppress<DATA8,DATA8,16> overflow;
  raw_array_zero_suppress<DATA8,DATA8,16> channel_cfd;
  raw_array_zero_suppress<DATA32,DATA32,16> channel_energy;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 card);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 card);
  STRUCT_FCNS_DECL(FEBEX_EVENT);
};
class FEBEX_EVENT_TRACES
{
  DATA32 event_trigger_time_hi;
  DATA32 event_trigger_time_lo;
  DATA16 hit_pattern;
  DATA32 num_channels_fired;
  raw_array_zero_suppress<DATA8,DATA8,16> channel_id;
  raw_array_zero_suppress<DATA16,DATA16,16> channel_trigger_time_hi;
  raw_array_zero_suppress<DATA32,DATA32,16> channel_trigger_time_lo;
  raw_array<DATA8,DATA8,16> pileup;
  raw_array<DATA8,DATA8,16> overflow;
  raw_array_zero_suppress<DATA8,DATA8,16> channel_cfd;
  raw_array_zero_suppress<DATA32,DATA32,16> channel_energy;
  raw_array_zero_suppress<DATA16,DATA16,10000> traces[16];
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 card);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 card);
  STRUCT_FCNS_DECL(FEBEX_EVENT_TRACES);
};
class FEBEX_PADDING
{
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(FEBEX_PADDING);
};
class VME_CAEN_V830_FRS
{
  raw_array_zero_suppress<DATA32,DATA32,32> data;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(VME_CAEN_V830_FRS);
};
class ZERO_FILLER
{
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(ZERO_FILLER);
};
class VME_CAEN_V792_FRS
{
  raw_array_multi_zero_suppress<DATA32,DATA32,32,32> data;
  DATA8 geo;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(VME_CAEN_V792_FRS);
};
class TDC_HEADER
{
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(TDC_HEADER);
};
class TDC_DATA_V1290
{
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,raw_array_multi_zero_suppress<DATA24,DATA24,128,128> &data
                                      ,raw_array_multi_zero_suppress<DATA8,DATA8,128,128> &leadOrTrail);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(TDC_DATA_V1290);
};
class TDC_ERROR
{
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(TDC_ERROR);
};
class TDC_TRAILER
{
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(TDC_TRAILER);
};
class VME_CAEN_V1290_FRS
{
  raw_array_multi_zero_suppress<DATA24,DATA24,128,128> data;
  raw_array_multi_zero_suppress<DATA8,DATA8,128,128> leadOrTrail;
  SINGLE(TDC_HEADER,tdc_header);
  SINGLE(TDC_DATA_V1290,measurement);
  SINGLE(TDC_ERROR,tdc_err);
  SINGLE(TDC_TRAILER,tdc_trailer);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(VME_CAEN_V1290_FRS);
};
class MAIN_CRATE_DATA
{
  SINGLE(BARRIER,barrier[3]);
  SINGLE(VME_CAEN_V830_FRS,v830);
  SINGLE(ZERO_FILLER,filler[1]);
  SINGLE(VME_CAEN_V792_FRS,v792);
  SINGLE(VME_CAEN_V1290_FRS,v1290);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(MAIN_CRATE_DATA);
};
class MESYTEC_MQDC32_FRS
{
  raw_array_zero_suppress<DATA12_OVERFLOW,DATA12_OVERFLOW,32> data;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(MESYTEC_MQDC32_FRS);
};
class MESYTEC_MTDC32_FRS
{
  raw_array_zero_suppress<DATA16,DATA16,34> data;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(MESYTEC_MTDC32_FRS);
};
class SIS_3820_FRS
{
  raw_array_zero_suppress<DATA32,DATA32,32> data;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(SIS_3820_FRS);
};
class TAMEX4_EPOCH_DATA
{
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 sfp,uint32 card,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_coarse
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_fine
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_edge
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_channel
                                      ,raw_list_ii_zero_suppress<DATA32,DATA32,1024> &time_epoch);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 sfp,uint32 card);
  STRUCT_FCNS_DECL(TAMEX4_EPOCH_DATA);
};
class TAMEX4_HEADER
{
  raw_list_ii_zero_suppress<DATA16,DATA16,64> post_trig_ns;
  raw_list_ii_zero_suppress<DATA16,DATA16,64> pre_trig_ns;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(TAMEX4_HEADER);
};
class TAMEX4_PADDING
{
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(TAMEX4_PADDING);
};
class TAMEX4_TIME_DATA
{
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 sfp,uint32 card,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_coarse
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_fine
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_edge
                                      ,raw_list_ii_zero_suppress<DATA12,DATA12,1024> &time_channel
                                      ,raw_list_ii_zero_suppress<DATA32,DATA32,1024> &time_epoch);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 sfp,uint32 card);
  STRUCT_FCNS_DECL(TAMEX4_TIME_DATA);
};
class TAMEX4_SFP
{
  DATA32 event_size;
  raw_list_ii_zero_suppress<DATA12,DATA12,1024> time_coarse;
  raw_list_ii_zero_suppress<DATA12,DATA12,1024> time_fine;
  raw_list_ii_zero_suppress<DATA12,DATA12,1024> time_edge;
  raw_list_ii_zero_suppress<DATA12,DATA12,1024> time_channel;
  raw_list_ii_zero_suppress<DATA32,DATA32,1024> time_epoch;
    SINGLE(TAMEX4_EPOCH_DATA,epoch);
    SINGLE(TAMEX4_TIME_DATA,time);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 sfp,uint32 card);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 sfp,uint32 card);
  STRUCT_FCNS_DECL(TAMEX4_SFP);
};
class TDC_DATA_V1190
{
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,raw_array_multi_zero_suppress<DATA24,DATA24,128,128> &data
                                      ,raw_array_multi_zero_suppress<DATA8,DATA8,128,128> &leadOrTrail);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(TDC_DATA_V1190);
};
class TIMESTAMP_WHITERABBIT
{
  DATA12 subsystem_id;
  DATA16 t1;
  DATA16 t2;
  DATA16 t3;
  DATA16 t4;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 id);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 id);
  STRUCT_FCNS_DECL(TIMESTAMP_WHITERABBIT);
};
class TIMESTAMP_WHITERABBIT_EXTENDED
{
  DATA16 subsystem_id;
  DATA16 t1;
  DATA16 t2;
  DATA16 t3;
  DATA16 t4;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 id);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 id);
  STRUCT_FCNS_DECL(TIMESTAMP_WHITERABBIT_EXTENDED);
};
class VME_CAEN_V7X5_FRS
{
  raw_array_zero_suppress<DATA12_OVERFLOW,DATA12_OVERFLOW,32> data;
  raw_array_zero_suppress<DATA8,DATA8,32> channel;
  raw_array_zero_suppress<DATA8,DATA8,32> geo;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(VME_CAEN_V7X5_FRS);
};
class VME_CAEN_V1190_FRS
{
  raw_array_multi_zero_suppress<DATA24,DATA24,128,128> data;
  raw_array_multi_zero_suppress<DATA8,DATA8,128,128> leadOrTrail;
  SINGLE(TDC_HEADER,tdc_header);
  SINGLE(TDC_DATA_V1190,measurement);
  SINGLE(TDC_ERROR,tdc_error);
  SINGLE(TDC_TRAILER,tdc_trailer);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(VME_CAEN_V1190_FRS);
};
class TPC_CRATE_DATA
{
  SINGLE(BARRIER,barrier[3]);
  SINGLE(VME_CAEN_V7X5_FRS,v775);
  SINGLE(VME_CAEN_V7X5_FRS,v785);
  SINGLE(VME_CAEN_V1190_FRS,v1190);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(TPC_CRATE_DATA);
};
class TRIG3EVENT
{
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(TRIG3EVENT);
};
class USER_CRATE_DATA
{
  SINGLE(BARRIER,barrier[5]);
  SINGLE(VME_CAEN_V830_FRS,v830);
  SINGLE(ZERO_FILLER,filler[1]);
  SINGLE(VME_CAEN_V7X5_FRS,v775[2]);
  SINGLE(VME_CAEN_V7X5_FRS,v785[2]);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(USER_CRATE_DATA);
};
class VFTX2
{
  raw_array_multi_zero_suppress<DATA12,DATA12,32,100> time_fine;
  raw_array_multi_zero_suppress<DATA16,DATA16,32,100> time_coarse;
  DATA16 time_trigger;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 id);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 id);
  STRUCT_FCNS_DECL(VFTX2);
};
class VFTX_CRATE_DATA
{
  SINGLE(MESYTEC_MQDC32_FRS,mqdc0);
  SINGLE(MESYTEC_MQDC32_FRS,mqdc1);
  SINGLE(VFTX2,vftx);
  SINGLE(BARRIER,barrier[3]);
  SINGLE(MESYTEC_MTDC32_FRS,mtdc);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(VFTX_CRATE_DATA);
};
class WR_MULTI
{
  DATA32 time_hi;
  DATA32 time_lo;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(WR_MULTI);
};
class aida_subev
 : public unpack_subevent_base
{
  SINGLE(TIMESTAMP_WHITERABBIT,ts);
  SINGLE(EXT_AIDA,data);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(aida_subev);
};
class bplast_subev
 : public unpack_subevent_base
{
  SINGLE(TAMEX4_PADDING,padding);
  SINGLE(TAMEX4_SFP,tamex[5]);
  SINGLE(TIMESTAMP_WHITERABBIT,ts);
  SINGLE(TAMEX4_HEADER,trigger_window);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(bplast_subev);
};
class fatima_tamex_subev
 : public unpack_subevent_base
{
  SINGLE(TAMEX4_PADDING,padding);
  SINGLE(TAMEX4_SFP,tamex[2]);
  SINGLE(TIMESTAMP_WHITERABBIT_EXTENDED,ts);
  SINGLE(TAMEX4_HEADER,trigger_window);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(fatima_tamex_subev);
};
class febex_subev
 : public unpack_subevent_base
{
  SINGLE(FEBEX_PADDING,padding);
  SINGLE(FEBEX_EVENT,data[4]);
  SINGLE(TIMESTAMP_WHITERABBIT,ts);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(febex_subev);
};
class frs_main_subev
 : public unpack_subevent_base
{
  SINGLE(TIMESTAMP_WHITERABBIT,wr);
  SINGLE(TRIG3EVENT,trig3);
  SINGLE(MAIN_CRATE_DATA,data);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(frs_main_subev);
};
class frs_tpc_subev
 : public unpack_subevent_base
{
  SINGLE(TRIG3EVENT,trig3);
  SINGLE(TPC_CRATE_DATA,data);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(frs_tpc_subev);
};
class frs_user_subev
 : public unpack_subevent_base
{
  SINGLE(TRIG3EVENT,trig3);
  SINGLE(USER_CRATE_DATA,data);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(frs_user_subev);
};
class frs_vftx_subev
 : public unpack_subevent_base
{
  SINGLE(TRIG3EVENT,trig3);
  SINGLE(VFTX_CRATE_DATA,data);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(frs_vftx_subev);
};
class unpack_event : public unpack_event_base
{
SINGLE(aida_subev,aida);
SINGLE(bplast_subev,bplast);
SINGLE(frs_main_subev,frsmain);
SINGLE(frs_tpc_subev,frstpc);
SINGLE(frs_user_subev,frsuser);
SINGLE(frs_vftx_subev,frsvftx);
  bitsone<7> __visited;
  void __clear_visited() { __visited.clear(); }
  bool ignore_unknown_subevent() { return true; }
template<typename __data_src_t>
  int __unpack_subevent(subevent_header *__header,__data_src_t &__buffer);
  int __revoke_subevent(subevent_header *__header);
  STRUCT_FCNS_DECL(unpack_event);
};
class unpack_sticky_event : public unpack_sticky_event_base
{
  void __clear_visited() { }
  bool ignore_unknown_subevent() { return false; }
template<typename __data_src_t>
  int __unpack_subevent(subevent_header *__header,__data_src_t &__buffer);
  int __revoke_subevent(subevent_header *__header);
  STRUCT_FCNS_DECL(unpack_sticky_event);
};
