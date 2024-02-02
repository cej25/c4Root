/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_LISA_EXT_H101_LISA_H__
#define __GUARD_H101_LISA_EXT_H101_LISA_H__

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

typedef struct EXT_STR_h101_lisa_t
{
  /* UNPACK */
  uint32_t lisa_ts_subsystem_id /* [0,65535] */;
  uint32_t lisa_ts_t1 /* [0,65535] */;
  uint32_t lisa_ts_t2 /* [0,65535] */;
  uint32_t lisa_ts_t3 /* [0,65535] */;
  uint32_t lisa_ts_t4 /* [0,65535] */;
  uint32_t lisa_data1event_trigger_time_hi /* [-1,-1] */;
  uint32_t lisa_data1event_trigger_time_lo /* [-1,-1] */;
  uint32_t lisa_data1hit_pattern /* [0,65535] */;
  uint32_t lisa_data1num_channels_fired /* [-1,-1] */;
  uint32_t lisa_data1channel_id /* [0,16] */;
  uint32_t lisa_data1channel_idI[16 EXT_STRUCT_CTRL(lisa_data1channel_id)] /* [1,16] */;
  uint32_t lisa_data1channel_idv[16 EXT_STRUCT_CTRL(lisa_data1channel_id)] /* [0,255] */;
  uint32_t lisa_data1channel_trigger_time_hi /* [0,16] */;
  uint32_t lisa_data1channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(lisa_data1channel_trigger_time_hi)] /* [1,16] */;
  uint32_t lisa_data1channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(lisa_data1channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t lisa_data1channel_trigger_time_lo /* [0,16] */;
  uint32_t lisa_data1channel_trigger_time_loI[16 EXT_STRUCT_CTRL(lisa_data1channel_trigger_time_lo)] /* [1,16] */;
  uint32_t lisa_data1channel_trigger_time_lov[16 EXT_STRUCT_CTRL(lisa_data1channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t lisa_data1pileup1 /* [0,255] */;
  uint32_t lisa_data1pileup2 /* [0,255] */;
  uint32_t lisa_data1pileup3 /* [0,255] */;
  uint32_t lisa_data1pileup4 /* [0,255] */;
  uint32_t lisa_data1pileup5 /* [0,255] */;
  uint32_t lisa_data1pileup6 /* [0,255] */;
  uint32_t lisa_data1pileup7 /* [0,255] */;
  uint32_t lisa_data1pileup8 /* [0,255] */;
  uint32_t lisa_data1pileup9 /* [0,255] */;
  uint32_t lisa_data1pileup10 /* [0,255] */;
  uint32_t lisa_data1pileup11 /* [0,255] */;
  uint32_t lisa_data1pileup12 /* [0,255] */;
  uint32_t lisa_data1pileup13 /* [0,255] */;
  uint32_t lisa_data1pileup14 /* [0,255] */;
  uint32_t lisa_data1pileup15 /* [0,255] */;
  uint32_t lisa_data1pileup16 /* [0,255] */;
  uint32_t lisa_data1overflow1 /* [0,255] */;
  uint32_t lisa_data1overflow2 /* [0,255] */;
  uint32_t lisa_data1overflow3 /* [0,255] */;
  uint32_t lisa_data1overflow4 /* [0,255] */;
  uint32_t lisa_data1overflow5 /* [0,255] */;
  uint32_t lisa_data1overflow6 /* [0,255] */;
  uint32_t lisa_data1overflow7 /* [0,255] */;
  uint32_t lisa_data1overflow8 /* [0,255] */;
  uint32_t lisa_data1overflow9 /* [0,255] */;
  uint32_t lisa_data1overflow10 /* [0,255] */;
  uint32_t lisa_data1overflow11 /* [0,255] */;
  uint32_t lisa_data1overflow12 /* [0,255] */;
  uint32_t lisa_data1overflow13 /* [0,255] */;
  uint32_t lisa_data1overflow14 /* [0,255] */;
  uint32_t lisa_data1overflow15 /* [0,255] */;
  uint32_t lisa_data1overflow16 /* [0,255] */;
  uint32_t lisa_data1channel_cfd /* [0,16] */;
  uint32_t lisa_data1channel_cfdI[16 EXT_STRUCT_CTRL(lisa_data1channel_cfd)] /* [1,16] */;
  uint32_t lisa_data1channel_cfdv[16 EXT_STRUCT_CTRL(lisa_data1channel_cfd)] /* [0,255] */;
  uint32_t lisa_data1channel_energy /* [0,16] */;
  uint32_t lisa_data1channel_energyI[16 EXT_STRUCT_CTRL(lisa_data1channel_energy)] /* [1,16] */;
  uint32_t lisa_data1channel_energyv[16 EXT_STRUCT_CTRL(lisa_data1channel_energy)] /* [-1,-1] */;
  uint32_t lisa_data1traces1 /* [0,10000] */;
  uint32_t lisa_data1traces1I[10000 EXT_STRUCT_CTRL(lisa_data1traces1)] /* [1,10000] */;
  uint32_t lisa_data1traces1v[10000 EXT_STRUCT_CTRL(lisa_data1traces1)] /* [0,65535] */;
  uint32_t lisa_data1traces2 /* [0,10000] */;
  uint32_t lisa_data1traces2I[10000 EXT_STRUCT_CTRL(lisa_data1traces2)] /* [1,10000] */;
  uint32_t lisa_data1traces2v[10000 EXT_STRUCT_CTRL(lisa_data1traces2)] /* [0,65535] */;
  uint32_t lisa_data1traces3 /* [0,10000] */;
  uint32_t lisa_data1traces3I[10000 EXT_STRUCT_CTRL(lisa_data1traces3)] /* [1,10000] */;
  uint32_t lisa_data1traces3v[10000 EXT_STRUCT_CTRL(lisa_data1traces3)] /* [0,65535] */;
  uint32_t lisa_data1traces4 /* [0,10000] */;
  uint32_t lisa_data1traces4I[10000 EXT_STRUCT_CTRL(lisa_data1traces4)] /* [1,10000] */;
  uint32_t lisa_data1traces4v[10000 EXT_STRUCT_CTRL(lisa_data1traces4)] /* [0,65535] */;
  uint32_t lisa_data1traces5 /* [0,10000] */;
  uint32_t lisa_data1traces5I[10000 EXT_STRUCT_CTRL(lisa_data1traces5)] /* [1,10000] */;
  uint32_t lisa_data1traces5v[10000 EXT_STRUCT_CTRL(lisa_data1traces5)] /* [0,65535] */;
  uint32_t lisa_data1traces6 /* [0,10000] */;
  uint32_t lisa_data1traces6I[10000 EXT_STRUCT_CTRL(lisa_data1traces6)] /* [1,10000] */;
  uint32_t lisa_data1traces6v[10000 EXT_STRUCT_CTRL(lisa_data1traces6)] /* [0,65535] */;
  uint32_t lisa_data1traces7 /* [0,10000] */;
  uint32_t lisa_data1traces7I[10000 EXT_STRUCT_CTRL(lisa_data1traces7)] /* [1,10000] */;
  uint32_t lisa_data1traces7v[10000 EXT_STRUCT_CTRL(lisa_data1traces7)] /* [0,65535] */;
  uint32_t lisa_data1traces8 /* [0,10000] */;
  uint32_t lisa_data1traces8I[10000 EXT_STRUCT_CTRL(lisa_data1traces8)] /* [1,10000] */;
  uint32_t lisa_data1traces8v[10000 EXT_STRUCT_CTRL(lisa_data1traces8)] /* [0,65535] */;
  uint32_t lisa_data1traces9 /* [0,10000] */;
  uint32_t lisa_data1traces9I[10000 EXT_STRUCT_CTRL(lisa_data1traces9)] /* [1,10000] */;
  uint32_t lisa_data1traces9v[10000 EXT_STRUCT_CTRL(lisa_data1traces9)] /* [0,65535] */;
  uint32_t lisa_data1traces10 /* [0,10000] */;
  uint32_t lisa_data1traces10I[10000 EXT_STRUCT_CTRL(lisa_data1traces10)] /* [1,10000] */;
  uint32_t lisa_data1traces10v[10000 EXT_STRUCT_CTRL(lisa_data1traces10)] /* [0,65535] */;
  uint32_t lisa_data1traces11 /* [0,10000] */;
  uint32_t lisa_data1traces11I[10000 EXT_STRUCT_CTRL(lisa_data1traces11)] /* [1,10000] */;
  uint32_t lisa_data1traces11v[10000 EXT_STRUCT_CTRL(lisa_data1traces11)] /* [0,65535] */;
  uint32_t lisa_data1traces12 /* [0,10000] */;
  uint32_t lisa_data1traces12I[10000 EXT_STRUCT_CTRL(lisa_data1traces12)] /* [1,10000] */;
  uint32_t lisa_data1traces12v[10000 EXT_STRUCT_CTRL(lisa_data1traces12)] /* [0,65535] */;
  uint32_t lisa_data1traces13 /* [0,10000] */;
  uint32_t lisa_data1traces13I[10000 EXT_STRUCT_CTRL(lisa_data1traces13)] /* [1,10000] */;
  uint32_t lisa_data1traces13v[10000 EXT_STRUCT_CTRL(lisa_data1traces13)] /* [0,65535] */;
  uint32_t lisa_data1traces14 /* [0,10000] */;
  uint32_t lisa_data1traces14I[10000 EXT_STRUCT_CTRL(lisa_data1traces14)] /* [1,10000] */;
  uint32_t lisa_data1traces14v[10000 EXT_STRUCT_CTRL(lisa_data1traces14)] /* [0,65535] */;
  uint32_t lisa_data1traces15 /* [0,10000] */;
  uint32_t lisa_data1traces15I[10000 EXT_STRUCT_CTRL(lisa_data1traces15)] /* [1,10000] */;
  uint32_t lisa_data1traces15v[10000 EXT_STRUCT_CTRL(lisa_data1traces15)] /* [0,65535] */;
  uint32_t lisa_data1traces16 /* [0,10000] */;
  uint32_t lisa_data1traces16I[10000 EXT_STRUCT_CTRL(lisa_data1traces16)] /* [1,10000] */;
  uint32_t lisa_data1traces16v[10000 EXT_STRUCT_CTRL(lisa_data1traces16)] /* [0,65535] */;

} EXT_STR_h101_lisa;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_lisa_onion_t
{
  /* UNPACK */
  uint32_t lisa_ts_subsystem_id;
  uint32_t lisa_ts_t[4];
  struct {
    uint32_t event_trigger_time_hi;
    uint32_t event_trigger_time_lo;
    uint32_t hit_pattern;
    uint32_t num_channels_fired;
    uint32_t channel_id;
    uint32_t channel_idI[16 /* channel_id */];
    uint32_t channel_idv[16 /* channel_id */];
    uint32_t channel_trigger_time_hi;
    uint32_t channel_trigger_time_hiI[16 /* channel_trigger_time_hi */];
    uint32_t channel_trigger_time_hiv[16 /* channel_trigger_time_hi */];
    uint32_t channel_trigger_time_lo;
    uint32_t channel_trigger_time_loI[16 /* channel_trigger_time_lo */];
    uint32_t channel_trigger_time_lov[16 /* channel_trigger_time_lo */];
    uint32_t pileup[16];
    uint32_t overflow[16];
    uint32_t channel_cfd;
    uint32_t channel_cfdI[16 /* channel_cfd */];
    uint32_t channel_cfdv[16 /* channel_cfd */];
    uint32_t channel_energy;
    uint32_t channel_energyI[16 /* channel_energy */];
    uint32_t channel_energyv[16 /* channel_energy */];
    struct {
      uint32_t _;
      uint32_t I[10000 /*  */];
      uint32_t v[10000 /*  */];
    } traces[16];
  } lisa_data[1];

} EXT_STR_h101_lisa_onion;

/*******************************************************/

#define EXT_STR_h101_lisa_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_ts_subsystem_id,            UINT32,\
                    "lisa_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_ts_t1,                      UINT32,\
                    "lisa_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_ts_t2,                      UINT32,\
                    "lisa_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_ts_t3,                      UINT32,\
                    "lisa_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_ts_t4,                      UINT32,\
                    "lisa_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data1event_trigger_time_hi, UINT32,\
                    "lisa_data1event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data1event_trigger_time_lo, UINT32,\
                    "lisa_data1event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1hit_pattern,           UINT32,\
                    "lisa_data1hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data1num_channels_fired,    UINT32,\
                    "lisa_data1num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_id,            UINT32,\
                    "lisa_data1channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_idI,           UINT32,\
                    "lisa_data1channel_idI",           "lisa_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_idv,           UINT32,\
                    "lisa_data1channel_idv",           "lisa_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_trigger_time_hi,UINT32,\
                    "lisa_data1channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_trigger_time_hiI,UINT32,\
                    "lisa_data1channel_trigger_time_hiI","lisa_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_trigger_time_hiv,UINT32,\
                    "lisa_data1channel_trigger_time_hiv","lisa_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_trigger_time_lo,UINT32,\
                    "lisa_data1channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_trigger_time_loI,UINT32,\
                    "lisa_data1channel_trigger_time_loI","lisa_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_trigger_time_lov,UINT32,\
                    "lisa_data1channel_trigger_time_lov","lisa_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup1,               UINT32,\
                    "lisa_data1pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup2,               UINT32,\
                    "lisa_data1pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup3,               UINT32,\
                    "lisa_data1pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup4,               UINT32,\
                    "lisa_data1pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup5,               UINT32,\
                    "lisa_data1pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup6,               UINT32,\
                    "lisa_data1pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup7,               UINT32,\
                    "lisa_data1pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup8,               UINT32,\
                    "lisa_data1pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup9,               UINT32,\
                    "lisa_data1pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup10,              UINT32,\
                    "lisa_data1pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup11,              UINT32,\
                    "lisa_data1pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup12,              UINT32,\
                    "lisa_data1pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup13,              UINT32,\
                    "lisa_data1pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup14,              UINT32,\
                    "lisa_data1pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup15,              UINT32,\
                    "lisa_data1pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup16,              UINT32,\
                    "lisa_data1pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow1,             UINT32,\
                    "lisa_data1overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow2,             UINT32,\
                    "lisa_data1overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow3,             UINT32,\
                    "lisa_data1overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow4,             UINT32,\
                    "lisa_data1overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow5,             UINT32,\
                    "lisa_data1overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow6,             UINT32,\
                    "lisa_data1overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow7,             UINT32,\
                    "lisa_data1overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow8,             UINT32,\
                    "lisa_data1overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow9,             UINT32,\
                    "lisa_data1overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow10,            UINT32,\
                    "lisa_data1overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow11,            UINT32,\
                    "lisa_data1overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow12,            UINT32,\
                    "lisa_data1overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow13,            UINT32,\
                    "lisa_data1overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow14,            UINT32,\
                    "lisa_data1overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow15,            UINT32,\
                    "lisa_data1overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow16,            UINT32,\
                    "lisa_data1overflow16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_cfd,           UINT32,\
                    "lisa_data1channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_cfdI,          UINT32,\
                    "lisa_data1channel_cfdI",          "lisa_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_cfdv,          UINT32,\
                    "lisa_data1channel_cfdv",          "lisa_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_energy,        UINT32,\
                    "lisa_data1channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_energyI,       UINT32,\
                    "lisa_data1channel_energyI",       "lisa_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_energyv,       UINT32,\
                    "lisa_data1channel_energyv",       "lisa_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces1,               UINT32,\
                    "lisa_data1traces1",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces1I,              UINT32,\
                    "lisa_data1traces1I",              "lisa_data1traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces1v,              UINT32,\
                    "lisa_data1traces1v",              "lisa_data1traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces2,               UINT32,\
                    "lisa_data1traces2",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces2I,              UINT32,\
                    "lisa_data1traces2I",              "lisa_data1traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces2v,              UINT32,\
                    "lisa_data1traces2v",              "lisa_data1traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces3,               UINT32,\
                    "lisa_data1traces3",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces3I,              UINT32,\
                    "lisa_data1traces3I",              "lisa_data1traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces3v,              UINT32,\
                    "lisa_data1traces3v",              "lisa_data1traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces4,               UINT32,\
                    "lisa_data1traces4",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces4I,              UINT32,\
                    "lisa_data1traces4I",              "lisa_data1traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces4v,              UINT32,\
                    "lisa_data1traces4v",              "lisa_data1traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces5,               UINT32,\
                    "lisa_data1traces5",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces5I,              UINT32,\
                    "lisa_data1traces5I",              "lisa_data1traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces5v,              UINT32,\
                    "lisa_data1traces5v",              "lisa_data1traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces6,               UINT32,\
                    "lisa_data1traces6",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces6I,              UINT32,\
                    "lisa_data1traces6I",              "lisa_data1traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces6v,              UINT32,\
                    "lisa_data1traces6v",              "lisa_data1traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces7,               UINT32,\
                    "lisa_data1traces7",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces7I,              UINT32,\
                    "lisa_data1traces7I",              "lisa_data1traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces7v,              UINT32,\
                    "lisa_data1traces7v",              "lisa_data1traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces8,               UINT32,\
                    "lisa_data1traces8",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces8I,              UINT32,\
                    "lisa_data1traces8I",              "lisa_data1traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces8v,              UINT32,\
                    "lisa_data1traces8v",              "lisa_data1traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces9,               UINT32,\
                    "lisa_data1traces9",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces9I,              UINT32,\
                    "lisa_data1traces9I",              "lisa_data1traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces9v,              UINT32,\
                    "lisa_data1traces9v",              "lisa_data1traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces10,              UINT32,\
                    "lisa_data1traces10",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces10I,             UINT32,\
                    "lisa_data1traces10I",             "lisa_data1traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces10v,             UINT32,\
                    "lisa_data1traces10v",             "lisa_data1traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces11,              UINT32,\
                    "lisa_data1traces11",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces11I,             UINT32,\
                    "lisa_data1traces11I",             "lisa_data1traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces11v,             UINT32,\
                    "lisa_data1traces11v",             "lisa_data1traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces12,              UINT32,\
                    "lisa_data1traces12",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces12I,             UINT32,\
                    "lisa_data1traces12I",             "lisa_data1traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces12v,             UINT32,\
                    "lisa_data1traces12v",             "lisa_data1traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces13,              UINT32,\
                    "lisa_data1traces13",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces13I,             UINT32,\
                    "lisa_data1traces13I",             "lisa_data1traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces13v,             UINT32,\
                    "lisa_data1traces13v",             "lisa_data1traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces14,              UINT32,\
                    "lisa_data1traces14",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces14I,             UINT32,\
                    "lisa_data1traces14I",             "lisa_data1traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces14v,             UINT32,\
                    "lisa_data1traces14v",             "lisa_data1traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces15,              UINT32,\
                    "lisa_data1traces15",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces15I,             UINT32,\
                    "lisa_data1traces15I",             "lisa_data1traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces15v,             UINT32,\
                    "lisa_data1traces15v",             "lisa_data1traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces16,              UINT32,\
                    "lisa_data1traces16",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces16I,             UINT32,\
                    "lisa_data1traces16I",             "lisa_data1traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces16v,             UINT32,\
                    "lisa_data1traces16v",             "lisa_data1traces16",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_LISA_EXT_H101_LISA_H__*/

/*******************************************************/
