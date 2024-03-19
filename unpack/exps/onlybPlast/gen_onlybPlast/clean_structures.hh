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
class bplast_subev
 : public unpack_subevent_base
{
  SINGLE(TAMEX4_PADDING,padding);
  SINGLE(TAMEX4_SFP,tamex[9]);
  SINGLE(TIMESTAMP_WHITERABBIT_EXTENDED,ts);
  SINGLE(TAMEX4_HEADER,trigger_window);
template<typename __data_src_t>
  void __unpack(__data_src_t &__buffer);
template<typename __data_src_t>
  static bool __match(__data_src_t &__buffer);
  STRUCT_FCNS_DECL(bplast_subev);
};
class unpack_event : public unpack_event_base
{
SINGLE(bplast_subev,bplast);
  bitsone<1> __visited;
  void __clear_visited() { __visited.clear(); }
  bool ignore_unknown_subevent() { return false; }
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
