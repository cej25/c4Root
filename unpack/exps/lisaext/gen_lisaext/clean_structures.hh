class BAD_EVENT
{
  DATA8 bad;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(BAD_EVENT);
};
class DUMMY
{
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(DUMMY);
};
class FEBEX_EVENT
{
  DATA8 trig;
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
class TRACE
{
  raw_array_zero_suppress<DATA16,DATA16,4000> traces[16];
  raw_array_zero_suppress<DATA8,DATA8,16> channel_id_traces;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 board);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 board);
  STRUCT_FCNS_DECL(TRACE);
};
class FEBEX_EVENT_TRACES
{
  DATA8 trig;
  DATA32 event_trigger_time_hi;
  DATA32 event_trigger_time_lo;
  DATA16 hit_pattern;
  DATA32 num_channels_fired;
  DATA8 board_num;
  raw_array_zero_suppress<DATA8,DATA8,16> channel_id;
  raw_array_zero_suppress<DATA16,DATA16,16> channel_trigger_time_hi;
  raw_array_zero_suppress<DATA32,DATA32,16> channel_trigger_time_lo;
  raw_array_zero_suppress<DATA8,DATA8,16> pileup;
  raw_array_zero_suppress<DATA8,DATA8,16> overflow;
  raw_array_zero_suppress<DATA8,DATA8,16> channel_cfd;
  raw_array_zero_suppress<DATA32,DATA32,16> channel_energy;
      SINGLE(TRACE,trace);
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
class TIMESTAMP_WHITERABBIT_EXTERNAL
{
  DATA16 subsystem_id;
  DATA32 run;
  DATA32 t1;
  DATA32 t2;
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer,uint32 id);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer,uint32 id);
  STRUCT_FCNS_DECL(TIMESTAMP_WHITERABBIT_EXTERNAL);
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
class febex_subev_traces
 : public unpack_subevent_base
{
  SINGLE(BAD_EVENT,badevent);
  SINGLE(TIMESTAMP_WHITERABBIT_EXTERNAL,ts);
  SINGLE(FEBEX_PADDING,padding);
  SINGLE(FEBEX_EVENT_TRACES,data[10]);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(febex_subev_traces);
};
class unpack_event : public unpack_event_base
{
SINGLE(febex_subev_traces,lisa);
  bitsone<2> __visited;
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
