/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_EXT_H101_LISA_H__
#define __GUARD_H101_EXT_H101_LISA_H__

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

typedef struct EXT_STR_h101_LISA_t
{
  /* INFO */
  uint32_t TRIGGER /* [0,15] */;
  uint32_t EVENTNO /* [-1,-1] */;
  /* UNPACK */
  uint32_t lisa_data_board_id /* [0,255] */;
  uint32_t lisa_data_event_trigger_time_hi /* [-1,-1] */;
  uint32_t lisa_data_event_trigger_time_lo /* [-1,-1] */;
  uint32_t lisa_data_hit_pattern /* [0,65535] */;
  uint32_t lisa_data_num_channels_fired /* [-1,-1] */;
  uint32_t lisa_data_channel_id /* [0,16] */;
  uint32_t lisa_data_channel_idI[16 EXT_STRUCT_CTRL(lisa_data_channel_id)] /* [1,16] */;
  uint32_t lisa_data_channel_idv[16 EXT_STRUCT_CTRL(lisa_data_channel_id)] /* [0,255] */;
  uint32_t lisa_data_channel_trigger_time_hi /* [0,16] */;
  uint32_t lisa_data_channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(lisa_data_channel_trigger_time_hi)] /* [1,16] */;
  uint32_t lisa_data_channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(lisa_data_channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t lisa_data_channel_trigger_time_lo /* [0,16] */;
  uint32_t lisa_data_channel_trigger_time_loI[16 EXT_STRUCT_CTRL(lisa_data_channel_trigger_time_lo)] /* [1,16] */;
  uint32_t lisa_data_channel_trigger_time_lov[16 EXT_STRUCT_CTRL(lisa_data_channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t lisa_data_pileup1 /* [0,255] */;
  uint32_t lisa_data_pileup2 /* [0,255] */;
  uint32_t lisa_data_pileup3 /* [0,255] */;
  uint32_t lisa_data_pileup4 /* [0,255] */;
  uint32_t lisa_data_pileup5 /* [0,255] */;
  uint32_t lisa_data_pileup6 /* [0,255] */;
  uint32_t lisa_data_pileup7 /* [0,255] */;
  uint32_t lisa_data_pileup8 /* [0,255] */;
  uint32_t lisa_data_pileup9 /* [0,255] */;
  uint32_t lisa_data_pileup10 /* [0,255] */;
  uint32_t lisa_data_pileup11 /* [0,255] */;
  uint32_t lisa_data_pileup12 /* [0,255] */;
  uint32_t lisa_data_pileup13 /* [0,255] */;
  uint32_t lisa_data_pileup14 /* [0,255] */;
  uint32_t lisa_data_pileup15 /* [0,255] */;
  uint32_t lisa_data_pileup16 /* [0,255] */;
  uint32_t lisa_data_overflow1 /* [0,255] */;
  uint32_t lisa_data_overflow2 /* [0,255] */;
  uint32_t lisa_data_overflow3 /* [0,255] */;
  uint32_t lisa_data_overflow4 /* [0,255] */;
  uint32_t lisa_data_overflow5 /* [0,255] */;
  uint32_t lisa_data_overflow6 /* [0,255] */;
  uint32_t lisa_data_overflow7 /* [0,255] */;
  uint32_t lisa_data_overflow8 /* [0,255] */;
  uint32_t lisa_data_overflow9 /* [0,255] */;
  uint32_t lisa_data_overflow10 /* [0,255] */;
  uint32_t lisa_data_overflow11 /* [0,255] */;
  uint32_t lisa_data_overflow12 /* [0,255] */;
  uint32_t lisa_data_overflow13 /* [0,255] */;
  uint32_t lisa_data_overflow14 /* [0,255] */;
  uint32_t lisa_data_overflow15 /* [0,255] */;
  uint32_t lisa_data_overflow16 /* [0,255] */;
  uint32_t lisa_data_channel_cfd /* [0,16] */;
  uint32_t lisa_data_channel_cfdI[16 EXT_STRUCT_CTRL(lisa_data_channel_cfd)] /* [1,16] */;
  uint32_t lisa_data_channel_cfdv[16 EXT_STRUCT_CTRL(lisa_data_channel_cfd)] /* [0,255] */;
  uint32_t lisa_data_channel_energy /* [0,16] */;
  uint32_t lisa_data_channel_energyI[16 EXT_STRUCT_CTRL(lisa_data_channel_energy)] /* [1,16] */;
  uint32_t lisa_data_channel_energyv[16 EXT_STRUCT_CTRL(lisa_data_channel_energy)] /* [-1,-1] */;
  uint32_t lisa_data_traces1 /* [0,10000] */;
  uint32_t lisa_data_traces1I[10000 EXT_STRUCT_CTRL(lisa_data_traces1)] /* [1,10000] */;
  uint32_t lisa_data_traces1v[10000 EXT_STRUCT_CTRL(lisa_data_traces1)] /* [0,65535] */;
  uint32_t lisa_data_traces2 /* [0,10000] */;
  uint32_t lisa_data_traces2I[10000 EXT_STRUCT_CTRL(lisa_data_traces2)] /* [1,10000] */;
  uint32_t lisa_data_traces2v[10000 EXT_STRUCT_CTRL(lisa_data_traces2)] /* [0,65535] */;
  uint32_t lisa_data_traces3 /* [0,10000] */;
  uint32_t lisa_data_traces3I[10000 EXT_STRUCT_CTRL(lisa_data_traces3)] /* [1,10000] */;
  uint32_t lisa_data_traces3v[10000 EXT_STRUCT_CTRL(lisa_data_traces3)] /* [0,65535] */;
  uint32_t lisa_data_traces4 /* [0,10000] */;
  uint32_t lisa_data_traces4I[10000 EXT_STRUCT_CTRL(lisa_data_traces4)] /* [1,10000] */;
  uint32_t lisa_data_traces4v[10000 EXT_STRUCT_CTRL(lisa_data_traces4)] /* [0,65535] */;
  uint32_t lisa_data_traces5 /* [0,10000] */;
  uint32_t lisa_data_traces5I[10000 EXT_STRUCT_CTRL(lisa_data_traces5)] /* [1,10000] */;
  uint32_t lisa_data_traces5v[10000 EXT_STRUCT_CTRL(lisa_data_traces5)] /* [0,65535] */;
  uint32_t lisa_data_traces6 /* [0,10000] */;
  uint32_t lisa_data_traces6I[10000 EXT_STRUCT_CTRL(lisa_data_traces6)] /* [1,10000] */;
  uint32_t lisa_data_traces6v[10000 EXT_STRUCT_CTRL(lisa_data_traces6)] /* [0,65535] */;
  uint32_t lisa_data_traces7 /* [0,10000] */;
  uint32_t lisa_data_traces7I[10000 EXT_STRUCT_CTRL(lisa_data_traces7)] /* [1,10000] */;
  uint32_t lisa_data_traces7v[10000 EXT_STRUCT_CTRL(lisa_data_traces7)] /* [0,65535] */;
  uint32_t lisa_data_traces8 /* [0,10000] */;
  uint32_t lisa_data_traces8I[10000 EXT_STRUCT_CTRL(lisa_data_traces8)] /* [1,10000] */;
  uint32_t lisa_data_traces8v[10000 EXT_STRUCT_CTRL(lisa_data_traces8)] /* [0,65535] */;
  uint32_t lisa_data_traces9 /* [0,10000] */;
  uint32_t lisa_data_traces9I[10000 EXT_STRUCT_CTRL(lisa_data_traces9)] /* [1,10000] */;
  uint32_t lisa_data_traces9v[10000 EXT_STRUCT_CTRL(lisa_data_traces9)] /* [0,65535] */;
  uint32_t lisa_data_traces10 /* [0,10000] */;
  uint32_t lisa_data_traces10I[10000 EXT_STRUCT_CTRL(lisa_data_traces10)] /* [1,10000] */;
  uint32_t lisa_data_traces10v[10000 EXT_STRUCT_CTRL(lisa_data_traces10)] /* [0,65535] */;
  uint32_t lisa_data_traces11 /* [0,10000] */;
  uint32_t lisa_data_traces11I[10000 EXT_STRUCT_CTRL(lisa_data_traces11)] /* [1,10000] */;
  uint32_t lisa_data_traces11v[10000 EXT_STRUCT_CTRL(lisa_data_traces11)] /* [0,65535] */;
  uint32_t lisa_data_traces12 /* [0,10000] */;
  uint32_t lisa_data_traces12I[10000 EXT_STRUCT_CTRL(lisa_data_traces12)] /* [1,10000] */;
  uint32_t lisa_data_traces12v[10000 EXT_STRUCT_CTRL(lisa_data_traces12)] /* [0,65535] */;
  uint32_t lisa_data_traces13 /* [0,10000] */;
  uint32_t lisa_data_traces13I[10000 EXT_STRUCT_CTRL(lisa_data_traces13)] /* [1,10000] */;
  uint32_t lisa_data_traces13v[10000 EXT_STRUCT_CTRL(lisa_data_traces13)] /* [0,65535] */;
  uint32_t lisa_data_traces14 /* [0,10000] */;
  uint32_t lisa_data_traces14I[10000 EXT_STRUCT_CTRL(lisa_data_traces14)] /* [1,10000] */;
  uint32_t lisa_data_traces14v[10000 EXT_STRUCT_CTRL(lisa_data_traces14)] /* [0,65535] */;
  uint32_t lisa_data_traces15 /* [0,10000] */;
  uint32_t lisa_data_traces15I[10000 EXT_STRUCT_CTRL(lisa_data_traces15)] /* [1,10000] */;
  uint32_t lisa_data_traces15v[10000 EXT_STRUCT_CTRL(lisa_data_traces15)] /* [0,65535] */;
  uint32_t lisa_data_traces16 /* [0,10000] */;
  uint32_t lisa_data_traces16I[10000 EXT_STRUCT_CTRL(lisa_data_traces16)] /* [1,10000] */;
  uint32_t lisa_data_traces16v[10000 EXT_STRUCT_CTRL(lisa_data_traces16)] /* [0,65535] */;

} EXT_STR_h101_LISA;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_LISA_onion_t
{
  /* INFO */
  uint32_t TRIGGER;
  uint32_t EVENTNO;
  /* UNPACK */
  uint32_t lisa_data_board_id;
  uint32_t lisa_data_event_trigger_time_hi;
  uint32_t lisa_data_event_trigger_time_lo;
  uint32_t lisa_data_hit_pattern;
  uint32_t lisa_data_num_channels_fired;
  uint32_t lisa_data_channel_id;
  uint32_t lisa_data_channel_idI[16 /* lisa_data_channel_id */];
  uint32_t lisa_data_channel_idv[16 /* lisa_data_channel_id */];
  uint32_t lisa_data_channel_trigger_time_hi;
  uint32_t lisa_data_channel_trigger_time_hiI[16 /* lisa_data_channel_trigger_time_hi */];
  uint32_t lisa_data_channel_trigger_time_hiv[16 /* lisa_data_channel_trigger_time_hi */];
  uint32_t lisa_data_channel_trigger_time_lo;
  uint32_t lisa_data_channel_trigger_time_loI[16 /* lisa_data_channel_trigger_time_lo */];
  uint32_t lisa_data_channel_trigger_time_lov[16 /* lisa_data_channel_trigger_time_lo */];
  uint32_t lisa_data_pileup[16];
  uint32_t lisa_data_overflow[16];
  uint32_t lisa_data_channel_cfd;
  uint32_t lisa_data_channel_cfdI[16 /* lisa_data_channel_cfd */];
  uint32_t lisa_data_channel_cfdv[16 /* lisa_data_channel_cfd */];
  uint32_t lisa_data_channel_energy;
  uint32_t lisa_data_channel_energyI[16 /* lisa_data_channel_energy */];
  uint32_t lisa_data_channel_energyv[16 /* lisa_data_channel_energy */];
  struct {
    uint32_t _;
    uint32_t I[10000 /*  */];
    uint32_t v[10000 /*  */];
  } lisa_data_traces[16];

} EXT_STR_h101_LISA_onion;

/*******************************************************/

#define EXT_STR_h101_LISA_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* INFO */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TRIGGER,                         UINT32,\
                    "TRIGGER",15,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     EVENTNO,                         UINT32,\
                    "EVENTNO",0/*flags*/); \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_board_id,              UINT32,\
                    "lisa_data_board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data_event_trigger_time_hi, UINT32,\
                    "lisa_data_event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data_event_trigger_time_lo, UINT32,\
                    "lisa_data_event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_hit_pattern,           UINT32,\
                    "lisa_data_hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data_num_channels_fired,    UINT32,\
                    "lisa_data_num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_id,            UINT32,\
                    "lisa_data_channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_idI,           UINT32,\
                    "lisa_data_channel_idI",           "lisa_data_channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_idv,           UINT32,\
                    "lisa_data_channel_idv",           "lisa_data_channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_trigger_time_hi,UINT32,\
                    "lisa_data_channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_trigger_time_hiI,UINT32,\
                    "lisa_data_channel_trigger_time_hiI","lisa_data_channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_trigger_time_hiv,UINT32,\
                    "lisa_data_channel_trigger_time_hiv","lisa_data_channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_trigger_time_lo,UINT32,\
                    "lisa_data_channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_trigger_time_loI,UINT32,\
                    "lisa_data_channel_trigger_time_loI","lisa_data_channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_trigger_time_lov,UINT32,\
                    "lisa_data_channel_trigger_time_lov","lisa_data_channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup1,               UINT32,\
                    "lisa_data_pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup2,               UINT32,\
                    "lisa_data_pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup3,               UINT32,\
                    "lisa_data_pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup4,               UINT32,\
                    "lisa_data_pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup5,               UINT32,\
                    "lisa_data_pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup6,               UINT32,\
                    "lisa_data_pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup7,               UINT32,\
                    "lisa_data_pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup8,               UINT32,\
                    "lisa_data_pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup9,               UINT32,\
                    "lisa_data_pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup10,              UINT32,\
                    "lisa_data_pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup11,              UINT32,\
                    "lisa_data_pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup12,              UINT32,\
                    "lisa_data_pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup13,              UINT32,\
                    "lisa_data_pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup14,              UINT32,\
                    "lisa_data_pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup15,              UINT32,\
                    "lisa_data_pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_pileup16,              UINT32,\
                    "lisa_data_pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow1,             UINT32,\
                    "lisa_data_overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow2,             UINT32,\
                    "lisa_data_overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow3,             UINT32,\
                    "lisa_data_overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow4,             UINT32,\
                    "lisa_data_overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow5,             UINT32,\
                    "lisa_data_overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow6,             UINT32,\
                    "lisa_data_overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow7,             UINT32,\
                    "lisa_data_overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow8,             UINT32,\
                    "lisa_data_overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow9,             UINT32,\
                    "lisa_data_overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow10,            UINT32,\
                    "lisa_data_overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow11,            UINT32,\
                    "lisa_data_overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow12,            UINT32,\
                    "lisa_data_overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow13,            UINT32,\
                    "lisa_data_overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow14,            UINT32,\
                    "lisa_data_overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow15,            UINT32,\
                    "lisa_data_overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_overflow16,            UINT32,\
                    "lisa_data_overflow16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_cfd,           UINT32,\
                    "lisa_data_channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_cfdI,          UINT32,\
                    "lisa_data_channel_cfdI",          "lisa_data_channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_cfdv,          UINT32,\
                    "lisa_data_channel_cfdv",          "lisa_data_channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_energy,        UINT32,\
                    "lisa_data_channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_energyI,       UINT32,\
                    "lisa_data_channel_energyI",       "lisa_data_channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_channel_energyv,       UINT32,\
                    "lisa_data_channel_energyv",       "lisa_data_channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces1,               UINT32,\
                    "lisa_data_traces1",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces1I,              UINT32,\
                    "lisa_data_traces1I",              "lisa_data_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces1v,              UINT32,\
                    "lisa_data_traces1v",              "lisa_data_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces2,               UINT32,\
                    "lisa_data_traces2",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces2I,              UINT32,\
                    "lisa_data_traces2I",              "lisa_data_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces2v,              UINT32,\
                    "lisa_data_traces2v",              "lisa_data_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces3,               UINT32,\
                    "lisa_data_traces3",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces3I,              UINT32,\
                    "lisa_data_traces3I",              "lisa_data_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces3v,              UINT32,\
                    "lisa_data_traces3v",              "lisa_data_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces4,               UINT32,\
                    "lisa_data_traces4",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces4I,              UINT32,\
                    "lisa_data_traces4I",              "lisa_data_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces4v,              UINT32,\
                    "lisa_data_traces4v",              "lisa_data_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces5,               UINT32,\
                    "lisa_data_traces5",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces5I,              UINT32,\
                    "lisa_data_traces5I",              "lisa_data_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces5v,              UINT32,\
                    "lisa_data_traces5v",              "lisa_data_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces6,               UINT32,\
                    "lisa_data_traces6",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces6I,              UINT32,\
                    "lisa_data_traces6I",              "lisa_data_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces6v,              UINT32,\
                    "lisa_data_traces6v",              "lisa_data_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces7,               UINT32,\
                    "lisa_data_traces7",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces7I,              UINT32,\
                    "lisa_data_traces7I",              "lisa_data_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces7v,              UINT32,\
                    "lisa_data_traces7v",              "lisa_data_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces8,               UINT32,\
                    "lisa_data_traces8",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces8I,              UINT32,\
                    "lisa_data_traces8I",              "lisa_data_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces8v,              UINT32,\
                    "lisa_data_traces8v",              "lisa_data_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces9,               UINT32,\
                    "lisa_data_traces9",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces9I,              UINT32,\
                    "lisa_data_traces9I",              "lisa_data_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces9v,              UINT32,\
                    "lisa_data_traces9v",              "lisa_data_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces10,              UINT32,\
                    "lisa_data_traces10",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces10I,             UINT32,\
                    "lisa_data_traces10I",             "lisa_data_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces10v,             UINT32,\
                    "lisa_data_traces10v",             "lisa_data_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces11,              UINT32,\
                    "lisa_data_traces11",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces11I,             UINT32,\
                    "lisa_data_traces11I",             "lisa_data_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces11v,             UINT32,\
                    "lisa_data_traces11v",             "lisa_data_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces12,              UINT32,\
                    "lisa_data_traces12",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces12I,             UINT32,\
                    "lisa_data_traces12I",             "lisa_data_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces12v,             UINT32,\
                    "lisa_data_traces12v",             "lisa_data_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces13,              UINT32,\
                    "lisa_data_traces13",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces13I,             UINT32,\
                    "lisa_data_traces13I",             "lisa_data_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces13v,             UINT32,\
                    "lisa_data_traces13v",             "lisa_data_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces14,              UINT32,\
                    "lisa_data_traces14",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces14I,             UINT32,\
                    "lisa_data_traces14I",             "lisa_data_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces14v,             UINT32,\
                    "lisa_data_traces14v",             "lisa_data_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces15,              UINT32,\
                    "lisa_data_traces15",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces15I,             UINT32,\
                    "lisa_data_traces15I",             "lisa_data_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces15v,             UINT32,\
                    "lisa_data_traces15v",             "lisa_data_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces16,              UINT32,\
                    "lisa_data_traces16",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces16I,             UINT32,\
                    "lisa_data_traces16I",             "lisa_data_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data_traces16v,             UINT32,\
                    "lisa_data_traces16v",             "lisa_data_traces16",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_EXT_H101_LISA_H__*/

/*******************************************************/
