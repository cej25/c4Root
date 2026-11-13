#include "structures.hh"
#include <cmath>
#include <cstdint>

void map_unpack_raw_foot(EXT_FOOT &unpack,
    DATA12 &tss,
    raw_array_zero_suppress<raw_event_FOOT, raw_event_FOOT, 640> &raw)
{
  bitsone_iterator iter;
  int i;

  if (!unpack.avail.value) {
    return;
  }

  tss.value = unpack.ts_status.value;
  while ((i = (int) unpack.data._valid.next(iter)) >= 0)
  {
    DATA16 value = unpack.data._items[i];
    raw.insert_index(-1,i).E = value;
  }
}

void raw_user_function(unpack_event *event, raw_event *raw_event)
{
#define UNPACK_RAW_FOOT(idx) \
  raw_event->FOOTTS[idx-1].WR.LO = event->foot##idx.foot.ts_lo; \
  raw_event->FOOTTS[idx-1].WR.HI = event->foot##idx.foot.ts_hi; \
  map_unpack_raw_foot(event->foot##idx.foot,\
	raw_event->FOOTTSS[idx-1], raw_event->FOOT[idx-1]);

  UNPACK_RAW_FOOT(1)
  UNPACK_RAW_FOOT(2)
  UNPACK_RAW_FOOT(3)
  UNPACK_RAW_FOOT(4)
  UNPACK_RAW_FOOT(5)
  UNPACK_RAW_FOOT(6)
  UNPACK_RAW_FOOT(7)
  UNPACK_RAW_FOOT(8)
}
