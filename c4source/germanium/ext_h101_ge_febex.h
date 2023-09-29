/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_GE_FEBEX_EXT_H101_GE_FEBEX_H__
#define __GUARD_H101_GE_FEBEX_EXT_H101_GE_FEBEX_H__

#ifndef __CINT__
# include <stdint.h>
#else
/* For CINT (old version trouble with stdint.h): */
# ifndef uint32_t
typedef unsigned int uint32_t;
typedef          int  int32_t;
# endif
#endif
#ifndef EXT_STRUCT_CTRL
# define EXT_STRUCT_CTRL(x)
#endif

/********************************************************
 *
 * Plain structure (layout as ntuple/root file):
 */

typedef struct EXT_STR_h101_GE_FEBEX_t
{
  /* RAW */
  uint32_t wr_subsystem_id /* [0,65535] */;
  uint32_t wr_t1 /* [0,65535] */;
  uint32_t wr_t2 /* [0,65535] */;
  uint32_t wr_t3 /* [0,65535] */;
  uint32_t wr_t4 /* [0,65535] */;
  uint32_t board_id /* [0,255] */;
  uint32_t event_trigger_time_hi /* [-1,-1] */;
  uint32_t event_trigger_time_lo /* [-1,-1] */;
  uint32_t hit_pattern /* [0,65535] */;
  uint32_t num_channels_fired /* [-1,-1] */;
  uint32_t pileup1 /* [0,255] */;
  uint32_t pileup2 /* [0,255] */;
  uint32_t pileup3 /* [0,255] */;
  uint32_t pileup4 /* [0,255] */;
  uint32_t pileup5 /* [0,255] */;
  uint32_t pileup6 /* [0,255] */;
  uint32_t pileup7 /* [0,255] */;
  uint32_t pileup8 /* [0,255] */;
  uint32_t pileup9 /* [0,255] */;
  uint32_t pileup10 /* [0,255] */;
  uint32_t pileup11 /* [0,255] */;
  uint32_t pileup12 /* [0,255] */;
  uint32_t pileup13 /* [0,255] */;
  uint32_t pileup14 /* [0,255] */;
  uint32_t pileup15 /* [0,255] */;
  uint32_t pileup16 /* [0,255] */;
  uint32_t overflow1 /* [0,255] */;
  uint32_t overflow2 /* [0,255] */;
  uint32_t overflow3 /* [0,255] */;
  uint32_t overflow4 /* [0,255] */;
  uint32_t overflow5 /* [0,255] */;
  uint32_t overflow6 /* [0,255] */;
  uint32_t overflow7 /* [0,255] */;
  uint32_t overflow8 /* [0,255] */;
  uint32_t overflow9 /* [0,255] */;
  uint32_t overflow10 /* [0,255] */;
  uint32_t overflow11 /* [0,255] */;
  uint32_t overflow12 /* [0,255] */;
  uint32_t overflow13 /* [0,255] */;
  uint32_t overflow14 /* [0,255] */;
  uint32_t overflow15 /* [0,255] */;
  uint32_t overflow16 /* [0,255] */;
  uint32_t channel_id1 /* [0,255] */;
  uint32_t channel_id2 /* [0,255] */;
  uint32_t channel_id3 /* [0,255] */;
  uint32_t channel_id4 /* [0,255] */;
  uint32_t channel_id5 /* [0,255] */;
  uint32_t channel_id6 /* [0,255] */;
  uint32_t channel_id7 /* [0,255] */;
  uint32_t channel_id8 /* [0,255] */;
  uint32_t channel_id9 /* [0,255] */;
  uint32_t channel_id10 /* [0,255] */;
  uint32_t channel_id11 /* [0,255] */;
  uint32_t channel_id12 /* [0,255] */;
  uint32_t channel_id13 /* [0,255] */;
  uint32_t channel_id14 /* [0,255] */;
  uint32_t channel_id15 /* [0,255] */;
  uint32_t channel_id16 /* [0,255] */;
  uint32_t channel_trigger_time_hi1 /* [0,65535] */;
  uint32_t channel_trigger_time_hi2 /* [0,65535] */;
  uint32_t channel_trigger_time_hi3 /* [0,65535] */;
  uint32_t channel_trigger_time_hi4 /* [0,65535] */;
  uint32_t channel_trigger_time_hi5 /* [0,65535] */;
  uint32_t channel_trigger_time_hi6 /* [0,65535] */;
  uint32_t channel_trigger_time_hi7 /* [0,65535] */;
  uint32_t channel_trigger_time_hi8 /* [0,65535] */;
  uint32_t channel_trigger_time_hi9 /* [0,65535] */;
  uint32_t channel_trigger_time_hi10 /* [0,65535] */;
  uint32_t channel_trigger_time_hi11 /* [0,65535] */;
  uint32_t channel_trigger_time_hi12 /* [0,65535] */;
  uint32_t channel_trigger_time_hi13 /* [0,65535] */;
  uint32_t channel_trigger_time_hi14 /* [0,65535] */;
  uint32_t channel_trigger_time_hi15 /* [0,65535] */;
  uint32_t channel_trigger_time_hi16 /* [0,65535] */;
  uint32_t channel_trigger_time_lo1 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo2 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo3 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo4 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo5 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo6 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo7 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo8 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo9 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo10 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo11 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo12 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo13 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo14 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo15 /* [-1,-1] */;
  uint32_t channel_trigger_time_lo16 /* [-1,-1] */;
  uint32_t channel_energy1 /* [-1,-1] */;
  uint32_t channel_energy2 /* [-1,-1] */;
  uint32_t channel_energy3 /* [-1,-1] */;
  uint32_t channel_energy4 /* [-1,-1] */;
  uint32_t channel_energy5 /* [-1,-1] */;
  uint32_t channel_energy6 /* [-1,-1] */;
  uint32_t channel_energy7 /* [-1,-1] */;
  uint32_t channel_energy8 /* [-1,-1] */;
  uint32_t channel_energy9 /* [-1,-1] */;
  uint32_t channel_energy10 /* [-1,-1] */;
  uint32_t channel_energy11 /* [-1,-1] */;
  uint32_t channel_energy12 /* [-1,-1] */;
  uint32_t channel_energy13 /* [-1,-1] */;
  uint32_t channel_energy14 /* [-1,-1] */;
  uint32_t channel_energy15 /* [-1,-1] */;
  uint32_t channel_energy16 /* [-1,-1] */;

} EXT_STR_h101_GE_FEBEX;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_GE_FEBEX_onion_t
{
  /* RAW */
  uint32_t wr_subsystem_id;
  uint32_t wr_t[4];
  uint32_t board_id;
  uint32_t event_trigger_time_hi;
  uint32_t event_trigger_time_lo;
  uint32_t hit_pattern;
  uint32_t num_channels_fired;
  uint32_t pileup[16];
  uint32_t overflow[16];
  uint32_t channel_id[16];
  uint32_t channel_trigger_time_hi[16];
  uint32_t channel_trigger_time_lo[16];
  uint32_t channel_energy[16];

} EXT_STR_h101_GE_FEBEX_onion;

/*******************************************************/

#define EXT_STR_h101_GE_FEBEX_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* RAW */ \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     wr_subsystem_id,                 UINT32,\
                    "wr_subsystem_id",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     wr_t1,                           UINT32,\
                    "wr_t1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     wr_t2,                           UINT32,\
                    "wr_t2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     wr_t3,                           UINT32,\
                    "wr_t3",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     wr_t4,                           UINT32,\
                    "wr_t4",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     board_id,                        UINT32,\
                    "board_id",255); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     event_trigger_time_hi,           UINT32,\
                    "event_trigger_time_hi"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     event_trigger_time_lo,           UINT32,\
                    "event_trigger_time_lo"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     hit_pattern,                     UINT32,\
                    "hit_pattern",65535); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     num_channels_fired,              UINT32,\
                    "num_channels_fired"); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup1,                         UINT32,\
                    "pileup1",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup2,                         UINT32,\
                    "pileup2",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup3,                         UINT32,\
                    "pileup3",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup4,                         UINT32,\
                    "pileup4",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup5,                         UINT32,\
                    "pileup5",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup6,                         UINT32,\
                    "pileup6",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup7,                         UINT32,\
                    "pileup7",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup8,                         UINT32,\
                    "pileup8",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup9,                         UINT32,\
                    "pileup9",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup10,                        UINT32,\
                    "pileup10",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup11,                        UINT32,\
                    "pileup11",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup12,                        UINT32,\
                    "pileup12",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup13,                        UINT32,\
                    "pileup13",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup14,                        UINT32,\
                    "pileup14",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup15,                        UINT32,\
                    "pileup15",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     pileup16,                        UINT32,\
                    "pileup16",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow1,                       UINT32,\
                    "overflow1",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow2,                       UINT32,\
                    "overflow2",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow3,                       UINT32,\
                    "overflow3",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow4,                       UINT32,\
                    "overflow4",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow5,                       UINT32,\
                    "overflow5",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow6,                       UINT32,\
                    "overflow6",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow7,                       UINT32,\
                    "overflow7",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow8,                       UINT32,\
                    "overflow8",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow9,                       UINT32,\
                    "overflow9",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow10,                      UINT32,\
                    "overflow10",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow11,                      UINT32,\
                    "overflow11",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow12,                      UINT32,\
                    "overflow12",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow13,                      UINT32,\
                    "overflow13",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow14,                      UINT32,\
                    "overflow14",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow15,                      UINT32,\
                    "overflow15",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     overflow16,                      UINT32,\
                    "overflow16",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id1,                     UINT32,\
                    "channel_id1",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id2,                     UINT32,\
                    "channel_id2",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id3,                     UINT32,\
                    "channel_id3",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id4,                     UINT32,\
                    "channel_id4",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id5,                     UINT32,\
                    "channel_id5",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id6,                     UINT32,\
                    "channel_id6",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id7,                     UINT32,\
                    "channel_id7",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id8,                     UINT32,\
                    "channel_id8",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id9,                     UINT32,\
                    "channel_id9",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id10,                    UINT32,\
                    "channel_id10",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id11,                    UINT32,\
                    "channel_id11",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id12,                    UINT32,\
                    "channel_id12",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id13,                    UINT32,\
                    "channel_id13",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id14,                    UINT32,\
                    "channel_id14",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id15,                    UINT32,\
                    "channel_id15",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_id16,                    UINT32,\
                    "channel_id16",255); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi1,        UINT32,\
                    "channel_trigger_time_hi1",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi2,        UINT32,\
                    "channel_trigger_time_hi2",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi3,        UINT32,\
                    "channel_trigger_time_hi3",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi4,        UINT32,\
                    "channel_trigger_time_hi4",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi5,        UINT32,\
                    "channel_trigger_time_hi5",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi6,        UINT32,\
                    "channel_trigger_time_hi6",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi7,        UINT32,\
                    "channel_trigger_time_hi7",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi8,        UINT32,\
                    "channel_trigger_time_hi8",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi9,        UINT32,\
                    "channel_trigger_time_hi9",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi10,       UINT32,\
                    "channel_trigger_time_hi10",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi11,       UINT32,\
                    "channel_trigger_time_hi11",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi12,       UINT32,\
                    "channel_trigger_time_hi12",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi13,       UINT32,\
                    "channel_trigger_time_hi13",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi14,       UINT32,\
                    "channel_trigger_time_hi14",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi15,       UINT32,\
                    "channel_trigger_time_hi15",65535); \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_hi16,       UINT32,\
                    "channel_trigger_time_hi16",65535); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo1,        UINT32,\
                    "channel_trigger_time_lo1"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo2,        UINT32,\
                    "channel_trigger_time_lo2"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo3,        UINT32,\
                    "channel_trigger_time_lo3"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo4,        UINT32,\
                    "channel_trigger_time_lo4"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo5,        UINT32,\
                    "channel_trigger_time_lo5"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo6,        UINT32,\
                    "channel_trigger_time_lo6"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo7,        UINT32,\
                    "channel_trigger_time_lo7"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo8,        UINT32,\
                    "channel_trigger_time_lo8"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo9,        UINT32,\
                    "channel_trigger_time_lo9"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo10,       UINT32,\
                    "channel_trigger_time_lo10"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo11,       UINT32,\
                    "channel_trigger_time_lo11"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo12,       UINT32,\
                    "channel_trigger_time_lo12"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo13,       UINT32,\
                    "channel_trigger_time_lo13"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo14,       UINT32,\
                    "channel_trigger_time_lo14"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo15,       UINT32,\
                    "channel_trigger_time_lo15"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_trigger_time_lo16,       UINT32,\
                    "channel_trigger_time_lo16"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy1,                 UINT32,\
                    "channel_energy1"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy2,                 UINT32,\
                    "channel_energy2"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy3,                 UINT32,\
                    "channel_energy3"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy4,                 UINT32,\
                    "channel_energy4"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy5,                 UINT32,\
                    "channel_energy5"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy6,                 UINT32,\
                    "channel_energy6"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy7,                 UINT32,\
                    "channel_energy7"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy8,                 UINT32,\
                    "channel_energy8"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy9,                 UINT32,\
                    "channel_energy9"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy10,                UINT32,\
                    "channel_energy10"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy11,                UINT32,\
                    "channel_energy11"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy12,                UINT32,\
                    "channel_energy12"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy13,                UINT32,\
                    "channel_energy13"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy14,                UINT32,\
                    "channel_energy14"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy15,                UINT32,\
                    "channel_energy15"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     channel_energy16,                UINT32,\
                    "channel_energy16"); \
  \
} while (0);

/********************************************************
 *
 * For internal use by the network data reader:
 * (version checks, etc)
 */

typedef struct EXT_STR_h101_GE_FEBEX_layout_t
{
  uint32_t _magic;
  uint32_t _size_info;
  uint32_t _size_struct;
  uint32_t _size_struct_onion;
  uint32_t _pack_list_items;

  uint32_t _num_items;
  struct {
    uint32_t _offset;
    uint32_t _size;
    uint32_t _xor;
    const char *_name;
  } _items[1];
  uint32_t _pack_list[212];
} EXT_STR_h101_GE_FEBEX_layout;

#define EXT_STR_h101_GE_FEBEX_LAYOUT_INIT { \
  0x57e65c97, \
  sizeof(EXT_STR_h101_GE_FEBEX_layout), \
  sizeof(EXT_STR_h101_GE_FEBEX), \
  sizeof(EXT_STR_h101_GE_FEBEX_onion), \
  212, \
  1, \
  { \
    { 0, sizeof(EXT_STR_h101_GE_FEBEX), 0x8202430f, "h101_GE_FEBEX" }, \
  }, \
  { \
   /*    0 */ 0x40a50000, 0x00000000, 0x40a50000, 0x00000004, \
   /*    4 */ 0x40a50000, 0x00000008, 0x40a50000, 0x0000000c, \
   /*    8 */ 0x40a50000, 0x00000010, 0x40a50000, 0x00000014, \
   /*   12 */ 0x40a50000, 0x00000018, 0x40a50000, 0x0000001c, \
   /*   16 */ 0x40a50000, 0x00000020, 0x40a50000, 0x00000024, \
   /*   20 */ 0x40a50000, 0x00000028, 0x40a50000, 0x0000002c, \
   /*   24 */ 0x40a50000, 0x00000030, 0x40a50000, 0x00000034, \
   /*   28 */ 0x40a50000, 0x00000038, 0x40a50000, 0x0000003c, \
   /*   32 */ 0x40a50000, 0x00000040, 0x40a50000, 0x00000044, \
   /*   36 */ 0x40a50000, 0x00000048, 0x40a50000, 0x0000004c, \
   /*   40 */ 0x40a50000, 0x00000050, 0x40a50000, 0x00000054, \
   /*   44 */ 0x40a50000, 0x00000058, 0x40a50000, 0x0000005c, \
   /*   48 */ 0x40a50000, 0x00000060, 0x40a50000, 0x00000064, \
   /*   52 */ 0x40a50000, 0x00000068, 0x40a50000, 0x0000006c, \
   /*   56 */ 0x40a50000, 0x00000070, 0x40a50000, 0x00000074, \
   /*   60 */ 0x40a50000, 0x00000078, 0x40a50000, 0x0000007c, \
   /*   64 */ 0x40a50000, 0x00000080, 0x40a50000, 0x00000084, \
   /*   68 */ 0x40a50000, 0x00000088, 0x40a50000, 0x0000008c, \
   /*   72 */ 0x40a50000, 0x00000090, 0x40a50000, 0x00000094, \
   /*   76 */ 0x40a50000, 0x00000098, 0x40a50000, 0x0000009c, \
   /*   80 */ 0x40a50000, 0x000000a0, 0x40a50000, 0x000000a4, \
   /*   84 */ 0x40a50000, 0x000000a8, 0x40a50000, 0x000000ac, \
   /*   88 */ 0x40a50000, 0x000000b0, 0x40a50000, 0x000000b4, \
   /*   92 */ 0x40a50000, 0x000000b8, 0x40a50000, 0x000000bc, \
   /*   96 */ 0x40a50000, 0x000000c0, 0x40a50000, 0x000000c4, \
   /*  100 */ 0x40a50000, 0x000000c8, 0x40a50000, 0x000000cc, \
   /*  104 */ 0x40a50000, 0x000000d0, 0x40a50000, 0x000000d4, \
   /*  108 */ 0x40a50000, 0x000000d8, 0x40a50000, 0x000000dc, \
   /*  112 */ 0x40a50000, 0x000000e0, 0x40a50000, 0x000000e4, \
   /*  116 */ 0x40a50000, 0x000000e8, 0x40a50000, 0x000000ec, \
   /*  120 */ 0x40a50000, 0x000000f0, 0x40a50000, 0x000000f4, \
   /*  124 */ 0x40a50000, 0x000000f8, 0x40a50000, 0x000000fc, \
   /*  128 */ 0x40a50000, 0x00000100, 0x40a50000, 0x00000104, \
   /*  132 */ 0x40a50000, 0x00000108, 0x40a50000, 0x0000010c, \
   /*  136 */ 0x40a50000, 0x00000110, 0x40a50000, 0x00000114, \
   /*  140 */ 0x40a50000, 0x00000118, 0x40a50000, 0x0000011c, \
   /*  144 */ 0x40a50000, 0x00000120, 0x40a50000, 0x00000124, \
   /*  148 */ 0x40a50000, 0x00000128, 0x40a50000, 0x0000012c, \
   /*  152 */ 0x40a50000, 0x00000130, 0x40a50000, 0x00000134, \
   /*  156 */ 0x40a50000, 0x00000138, 0x40a50000, 0x0000013c, \
   /*  160 */ 0x40a50000, 0x00000140, 0x40a50000, 0x00000144, \
   /*  164 */ 0x40a50000, 0x00000148, 0x40a50000, 0x0000014c, \
   /*  168 */ 0x40a50000, 0x00000150, 0x40a50000, 0x00000154, \
   /*  172 */ 0x40a50000, 0x00000158, 0x40a50000, 0x0000015c, \
   /*  176 */ 0x40a50000, 0x00000160, 0x40a50000, 0x00000164, \
   /*  180 */ 0x40a50000, 0x00000168, 0x40a50000, 0x0000016c, \
   /*  184 */ 0x40a50000, 0x00000170, 0x40a50000, 0x00000174, \
   /*  188 */ 0x40a50000, 0x00000178, 0x40a50000, 0x0000017c, \
   /*  192 */ 0x40a50000, 0x00000180, 0x40a50000, 0x00000184, \
   /*  196 */ 0x40a50000, 0x00000188, 0x40a50000, 0x0000018c, \
   /*  200 */ 0x40a50000, 0x00000190, 0x40a50000, 0x00000194, \
   /*  204 */ 0x40a50000, 0x00000198, 0x40a50000, 0x0000019c, \
   /*  208 */ 0x40a50000, 0x000001a0, 0x40a50000, 0x000001a4, \
  } \
};

#endif/*__GUARD_h101_GE_FEBEX_EXT_h101_GE_FEBEX_H__*/

/*******************************************************/
