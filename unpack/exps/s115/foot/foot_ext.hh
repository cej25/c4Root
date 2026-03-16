#ifndef __FOOT_EXT_HH__
#define __FOOT_EXT_HH__

#include "data_src.hh"
#include "dummy_external.hh"
#include "external_data.hh"
#include "zero_suppress.hh"
#include "raw_data.hh"

/*---------------------------------------------------------------------------*/

DUMMY_EXTERNAL_MAP_STRUCT_FORW(EXT_FOOT);

class EXT_FOOT
{
public:
  EXT_FOOT();
  ~EXT_FOOT();

public:
  DATA16 avail;
  DATA12 ts_status;
  DATA32 ts_lo;
  DATA32 ts_hi;
  DATA8  sync_check;
#if defined(UNPACKER_IS_foot_640)
  raw_array_zero_suppress<DATA16,DATA16,1280> data;
#else
  raw_array_zero_suppress<DATA16,DATA16,640> data;
#endif

public:
  void __clean();
  EXT_DECL_UNPACK();
  // Needed if it is part of a select statement
  EXT_DECL_MATCH();

public:
  DUMMY_EXTERNAL_DUMP(EXT_FOOT);
  DUMMY_EXTERNAL_SHOW_MEMBERS(EXT_FOOT);
  DUMMY_EXTERNAL_ENUMERATE_MEMBERS(EXT_FOOT);
  DUMMY_EXTERNAL_ZERO_SUPPRESS_INFO_PTRS(EXT_FOOT);
};

DUMMY_EXTERNAL_MAP_STRUCT(EXT_FOOT);
DUMMY_EXTERNAL_WATCHER_STRUCT(EXT_FOOT);
DUMMY_EXTERNAL_CORRELATION_STRUCT(EXT_FOOT);

/*---------------------------------------------------------------------------*/

#endif//__FOOT_EXT_HH__
