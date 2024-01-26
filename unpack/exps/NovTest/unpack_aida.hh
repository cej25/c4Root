#ifndef __AIDA_UNPACK__
#define __AIDA_UNPACK__

#include "../../../config/NovTest/setup.hh"

#include "data_src.hh"
#include "dummy_external.hh"
#include "external_data.hh"
#include "zero_suppress.hh"

DUMMY_EXTERNAL_MAP_STRUCT_FORW(EXT_AIDA);

struct aida_adc_item
{
#ifdef NO_UINT64
  uint32 timestamp_raw_lo;
  uint32 timestamp_raw_hi;
  uint32 timestamp_slow_lo;
  uint32 timestamp_slow_hi;
  uint32 timestamp_fast_lo;
  uint32 timestamp_fast_hi;
#else
  uint64 timestamp_raw;
  uint64 timestamp_slow;
  uint64 timestamp_fast;
#endif
  uint16 data;
  uint8 fee;
  uint8 channel;
  uint8 vernier;
  uint8 range;

  void __clean() {};
  void dump(const signal_id &id,pretty_dump_info &pdi) const;
  void show_members(const signal_id &id,const char *unit) const;
  void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
  void zero_suppress_info_ptrs(used_zero_suppress_info& used_info);
};

struct aida_wave_item
{
#ifdef NO_UINT64
  uint32 timestamp_lo;
  uint32 timestamp_hi;
#else
  uint64 timestamp;
#endif
  uint16 length;
  uint8 fee;
  uint8 channel;
  raw_list_ii_zero_suppress<uint16, uint16, 1024> data;

  void __clean() { data.__clean(); }
  void dump(const signal_id& id, pretty_dump_info& pdi) const;
  void show_members(const signal_id &id,const char *unit) const;
  void enumerate_members(const signal_id& id, const enumerate_info& info, enumerate_fcn callback, void* extra) const;
  void zero_suppress_info_ptrs(used_zero_suppress_info& used_info);
};

struct aida_scaler_item
{
#ifdef NO_UINT64
  uint32 timestamp_lo;
  uint32 timestamp_hi;
  uint32 value_lo;
  uint32 value_hi;
#else
  uint64 timestamp;
  uint64 value;
#endif
  uint8 fee;

  void __clean() {}
  void dump(const signal_id& id, pretty_dump_info& pdi) const;
  void show_members(const signal_id &id,const char *unit) const;
  void enumerate_members(const signal_id& id, const enumerate_info& info, enumerate_fcn callback, void* extra) const;
  void zero_suppress_info_ptrs(used_zero_suppress_info& used_info);
};

struct aida_flow_item
{
#ifdef NO_UINT64
  uint32 timestamp_lo;
  uint32 timestamp_hi;
#else
  uint64 timestamp;
#endif
  uint8 fee;
  uint8 paused;

  void __clean() {}
  void dump(const signal_id& id, pretty_dump_info& pdi) const;
  void show_members(const signal_id &id,const char *unit) const;
  void enumerate_members(const signal_id& id, const enumerate_info& info, enumerate_fcn callback, void* extra) const;
  void zero_suppress_info_ptrs(used_zero_suppress_info& used_info);
};

class EXT_AIDA
{
  public:
    EXT_AIDA();
    ~EXT_AIDA();

    void __clean();
    EXT_DECL_UNPACK();

    void dump(const signal_id &id,pretty_dump_info &pdi) const;
    void show_members(const signal_id &id,const char *unit) const;
    void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
    void zero_suppress_info_ptrs(used_zero_suppress_info &used_info);

  public:
    raw_list_ii_zero_suppress<aida_adc_item, aida_adc_item, 10000> adc;
    raw_list_ii_zero_suppress<aida_wave_item, aida_wave_item, 10000> wave;
    raw_list_ii_zero_suppress<aida_scaler_item, aida_scaler_item, 10000> scaler;
    raw_list_ii_zero_suppress<aida_flow_item, aida_flow_item, 10000> flow;

  private:
    uint64 fast_times[AIDA_MAX_FEES][64];
    uint64 scalers[AIDA_MAX_FEES];
    uint64 asic_last[AIDA_MAX_FEES][4];
    unsigned int multiplexer[AIDA_MAX_FEES][4];
};

DUMMY_EXTERNAL_MAP_STRUCT(EXT_AIDA);
DUMMY_EXTERNAL_WATCHER_STRUCT(EXT_AIDA);
DUMMY_EXTERNAL_CORRELATION_STRUCT(EXT_AIDA);
DUMMY_EXTERNAL_CALIB_MAP_STRUCT(EXT_AIDA);


#endif /* __AIDA_UNPACK__ */
