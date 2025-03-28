/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_STEFAN_EXT_H101_STEFAN_H__
#define __GUARD_H101_STEFAN_EXT_H101_STEFAN_H__

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

typedef struct EXT_STR_h101_stefan_t
{
  /* UNPACK */
  uint32_t stefan_ts_subsystem_id /* [0,65535] */;
  uint32_t stefan_ts_t1 /* [0,65535] */;
  uint32_t stefan_ts_t2 /* [0,65535] */;
  uint32_t stefan_ts_t3 /* [0,65535] */;
  uint32_t stefan_ts_t4 /* [0,65535] */;
  uint32_t stefan_data1trig /* [0,255] */;
  uint32_t stefan_data1event_trigger_time_hi /* [-1,-1] */;
  uint32_t stefan_data1event_trigger_time_lo /* [-1,-1] */;
  uint32_t stefan_data1hit_pattern /* [0,65535] */;
  uint32_t stefan_data1channel_trigger_time_hi /* [0,16] */;
  uint32_t stefan_data1channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(stefan_data1channel_trigger_time_hi)] /* [1,16] */;
  uint32_t stefan_data1channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(stefan_data1channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t stefan_data1channel_trigger_time_lo /* [0,16] */;
  uint32_t stefan_data1channel_trigger_time_loI[16 EXT_STRUCT_CTRL(stefan_data1channel_trigger_time_lo)] /* [1,16] */;
  uint32_t stefan_data1channel_trigger_time_lov[16 EXT_STRUCT_CTRL(stefan_data1channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t stefan_data1pileup /* [0,16] */;
  uint32_t stefan_data1pileupI[16 EXT_STRUCT_CTRL(stefan_data1pileup)] /* [1,16] */;
  uint32_t stefan_data1pileupv[16 EXT_STRUCT_CTRL(stefan_data1pileup)] /* [0,255] */;
  uint32_t stefan_data1overflow /* [0,16] */;
  uint32_t stefan_data1overflowI[16 EXT_STRUCT_CTRL(stefan_data1overflow)] /* [1,16] */;
  uint32_t stefan_data1overflowv[16 EXT_STRUCT_CTRL(stefan_data1overflow)] /* [0,255] */;
  uint32_t stefan_data1channel_cfd /* [0,16] */;
  uint32_t stefan_data1channel_cfdI[16 EXT_STRUCT_CTRL(stefan_data1channel_cfd)] /* [1,16] */;
  uint32_t stefan_data1channel_cfdv[16 EXT_STRUCT_CTRL(stefan_data1channel_cfd)] /* [0,255] */;
  uint32_t stefan_data1channel_energy /* [0,16] */;
  uint32_t stefan_data1channel_energyI[16 EXT_STRUCT_CTRL(stefan_data1channel_energy)] /* [1,16] */;
  uint32_t stefan_data1channel_energyv[16 EXT_STRUCT_CTRL(stefan_data1channel_energy)] /* [-1,-1] */;
  uint32_t stefan_data2trig /* [0,255] */;
  uint32_t stefan_data2event_trigger_time_hi /* [-1,-1] */;
  uint32_t stefan_data2event_trigger_time_lo /* [-1,-1] */;
  uint32_t stefan_data2hit_pattern /* [0,65535] */;
  uint32_t stefan_data2channel_trigger_time_hi /* [0,16] */;
  uint32_t stefan_data2channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(stefan_data2channel_trigger_time_hi)] /* [1,16] */;
  uint32_t stefan_data2channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(stefan_data2channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t stefan_data2channel_trigger_time_lo /* [0,16] */;
  uint32_t stefan_data2channel_trigger_time_loI[16 EXT_STRUCT_CTRL(stefan_data2channel_trigger_time_lo)] /* [1,16] */;
  uint32_t stefan_data2channel_trigger_time_lov[16 EXT_STRUCT_CTRL(stefan_data2channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t stefan_data2pileup /* [0,16] */;
  uint32_t stefan_data2pileupI[16 EXT_STRUCT_CTRL(stefan_data2pileup)] /* [1,16] */;
  uint32_t stefan_data2pileupv[16 EXT_STRUCT_CTRL(stefan_data2pileup)] /* [0,255] */;
  uint32_t stefan_data2overflow /* [0,16] */;
  uint32_t stefan_data2overflowI[16 EXT_STRUCT_CTRL(stefan_data2overflow)] /* [1,16] */;
  uint32_t stefan_data2overflowv[16 EXT_STRUCT_CTRL(stefan_data2overflow)] /* [0,255] */;
  uint32_t stefan_data2channel_cfd /* [0,16] */;
  uint32_t stefan_data2channel_cfdI[16 EXT_STRUCT_CTRL(stefan_data2channel_cfd)] /* [1,16] */;
  uint32_t stefan_data2channel_cfdv[16 EXT_STRUCT_CTRL(stefan_data2channel_cfd)] /* [0,255] */;
  uint32_t stefan_data2channel_energy /* [0,16] */;
  uint32_t stefan_data2channel_energyI[16 EXT_STRUCT_CTRL(stefan_data2channel_energy)] /* [1,16] */;
  uint32_t stefan_data2channel_energyv[16 EXT_STRUCT_CTRL(stefan_data2channel_energy)] /* [-1,-1] */;
  uint32_t stefan_data3trig /* [0,255] */;
  uint32_t stefan_data3event_trigger_time_hi /* [-1,-1] */;
  uint32_t stefan_data3event_trigger_time_lo /* [-1,-1] */;
  uint32_t stefan_data3hit_pattern /* [0,65535] */;
  uint32_t stefan_data3channel_trigger_time_hi /* [0,16] */;
  uint32_t stefan_data3channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(stefan_data3channel_trigger_time_hi)] /* [1,16] */;
  uint32_t stefan_data3channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(stefan_data3channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t stefan_data3channel_trigger_time_lo /* [0,16] */;
  uint32_t stefan_data3channel_trigger_time_loI[16 EXT_STRUCT_CTRL(stefan_data3channel_trigger_time_lo)] /* [1,16] */;
  uint32_t stefan_data3channel_trigger_time_lov[16 EXT_STRUCT_CTRL(stefan_data3channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t stefan_data3pileup /* [0,16] */;
  uint32_t stefan_data3pileupI[16 EXT_STRUCT_CTRL(stefan_data3pileup)] /* [1,16] */;
  uint32_t stefan_data3pileupv[16 EXT_STRUCT_CTRL(stefan_data3pileup)] /* [0,255] */;
  uint32_t stefan_data3overflow /* [0,16] */;
  uint32_t stefan_data3overflowI[16 EXT_STRUCT_CTRL(stefan_data3overflow)] /* [1,16] */;
  uint32_t stefan_data3overflowv[16 EXT_STRUCT_CTRL(stefan_data3overflow)] /* [0,255] */;
  uint32_t stefan_data3channel_cfd /* [0,16] */;
  uint32_t stefan_data3channel_cfdI[16 EXT_STRUCT_CTRL(stefan_data3channel_cfd)] /* [1,16] */;
  uint32_t stefan_data3channel_cfdv[16 EXT_STRUCT_CTRL(stefan_data3channel_cfd)] /* [0,255] */;
  uint32_t stefan_data3channel_energy /* [0,16] */;
  uint32_t stefan_data3channel_energyI[16 EXT_STRUCT_CTRL(stefan_data3channel_energy)] /* [1,16] */;
  uint32_t stefan_data3channel_energyv[16 EXT_STRUCT_CTRL(stefan_data3channel_energy)] /* [-1,-1] */;
  uint32_t stefan_data4trig /* [0,255] */;
  uint32_t stefan_data4event_trigger_time_hi /* [-1,-1] */;
  uint32_t stefan_data4event_trigger_time_lo /* [-1,-1] */;
  uint32_t stefan_data4hit_pattern /* [0,65535] */;
  uint32_t stefan_data4channel_trigger_time_hi /* [0,16] */;
  uint32_t stefan_data4channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(stefan_data4channel_trigger_time_hi)] /* [1,16] */;
  uint32_t stefan_data4channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(stefan_data4channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t stefan_data4channel_trigger_time_lo /* [0,16] */;
  uint32_t stefan_data4channel_trigger_time_loI[16 EXT_STRUCT_CTRL(stefan_data4channel_trigger_time_lo)] /* [1,16] */;
  uint32_t stefan_data4channel_trigger_time_lov[16 EXT_STRUCT_CTRL(stefan_data4channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t stefan_data4pileup /* [0,16] */;
  uint32_t stefan_data4pileupI[16 EXT_STRUCT_CTRL(stefan_data4pileup)] /* [1,16] */;
  uint32_t stefan_data4pileupv[16 EXT_STRUCT_CTRL(stefan_data4pileup)] /* [0,255] */;
  uint32_t stefan_data4overflow /* [0,16] */;
  uint32_t stefan_data4overflowI[16 EXT_STRUCT_CTRL(stefan_data4overflow)] /* [1,16] */;
  uint32_t stefan_data4overflowv[16 EXT_STRUCT_CTRL(stefan_data4overflow)] /* [0,255] */;
  uint32_t stefan_data4channel_cfd /* [0,16] */;
  uint32_t stefan_data4channel_cfdI[16 EXT_STRUCT_CTRL(stefan_data4channel_cfd)] /* [1,16] */;
  uint32_t stefan_data4channel_cfdv[16 EXT_STRUCT_CTRL(stefan_data4channel_cfd)] /* [0,255] */;
  uint32_t stefan_data4channel_energy /* [0,16] */;
  uint32_t stefan_data4channel_energyI[16 EXT_STRUCT_CTRL(stefan_data4channel_energy)] /* [1,16] */;
  uint32_t stefan_data4channel_energyv[16 EXT_STRUCT_CTRL(stefan_data4channel_energy)] /* [-1,-1] */;

} EXT_STR_h101_stefan;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_stefan_onion_t
{
  /* UNPACK */
  uint32_t stefan_ts_subsystem_id;
  uint32_t stefan_ts_t[4];
  struct {
    uint32_t trig;
    uint32_t event_trigger_time_hi;
    uint32_t event_trigger_time_lo;
    uint32_t hit_pattern;
    uint32_t channel_trigger_time_hi;
    uint32_t channel_trigger_time_hiI[16 /* channel_trigger_time_hi */];
    uint32_t channel_trigger_time_hiv[16 /* channel_trigger_time_hi */];
    uint32_t channel_trigger_time_lo;
    uint32_t channel_trigger_time_loI[16 /* channel_trigger_time_lo */];
    uint32_t channel_trigger_time_lov[16 /* channel_trigger_time_lo */];
    uint32_t pileup;
    uint32_t pileupI[16 /* pileup */];
    uint32_t pileupv[16 /* pileup */];
    uint32_t overflow;
    uint32_t overflowI[16 /* overflow */];
    uint32_t overflowv[16 /* overflow */];
    uint32_t channel_cfd;
    uint32_t channel_cfdI[16 /* channel_cfd */];
    uint32_t channel_cfdv[16 /* channel_cfd */];
    uint32_t channel_energy;
    uint32_t channel_energyI[16 /* channel_energy */];
    uint32_t channel_energyv[16 /* channel_energy */];
  } stefan_data[4];

} EXT_STR_h101_stefan_onion;

/*******************************************************/

#define EXT_STR_h101_stefan_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_ts_subsystem_id,          UINT32,\
                    "stefan_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_ts_t1,                    UINT32,\
                    "stefan_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_ts_t2,                    UINT32,\
                    "stefan_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_ts_t3,                    UINT32,\
                    "stefan_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_ts_t4,                    UINT32,\
                    "stefan_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data1trig,                UINT32,\
                    "stefan_data1trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     stefan_data1event_trigger_time_hi,UINT32,\
                    "stefan_data1event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     stefan_data1event_trigger_time_lo,UINT32,\
                    "stefan_data1event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data1hit_pattern,         UINT32,\
                    "stefan_data1hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data1channel_trigger_time_hi,UINT32,\
                    "stefan_data1channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data1channel_trigger_time_hiI,UINT32,\
                    "stefan_data1channel_trigger_time_hiI","stefan_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data1channel_trigger_time_hiv,UINT32,\
                    "stefan_data1channel_trigger_time_hiv","stefan_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data1channel_trigger_time_lo,UINT32,\
                    "stefan_data1channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data1channel_trigger_time_loI,UINT32,\
                    "stefan_data1channel_trigger_time_loI","stefan_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data1channel_trigger_time_lov,UINT32,\
                    "stefan_data1channel_trigger_time_lov","stefan_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data1pileup,              UINT32,\
                    "stefan_data1pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data1pileupI,             UINT32,\
                    "stefan_data1pileupI",             "stefan_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data1pileupv,             UINT32,\
                    "stefan_data1pileupv",             "stefan_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data1overflow,            UINT32,\
                    "stefan_data1overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data1overflowI,           UINT32,\
                    "stefan_data1overflowI",           "stefan_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data1overflowv,           UINT32,\
                    "stefan_data1overflowv",           "stefan_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data1channel_cfd,         UINT32,\
                    "stefan_data1channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data1channel_cfdI,        UINT32,\
                    "stefan_data1channel_cfdI",        "stefan_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data1channel_cfdv,        UINT32,\
                    "stefan_data1channel_cfdv",        "stefan_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data1channel_energy,      UINT32,\
                    "stefan_data1channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data1channel_energyI,     UINT32,\
                    "stefan_data1channel_energyI",     "stefan_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data1channel_energyv,     UINT32,\
                    "stefan_data1channel_energyv",     "stefan_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data2trig,                UINT32,\
                    "stefan_data2trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     stefan_data2event_trigger_time_hi,UINT32,\
                    "stefan_data2event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     stefan_data2event_trigger_time_lo,UINT32,\
                    "stefan_data2event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data2hit_pattern,         UINT32,\
                    "stefan_data2hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data2channel_trigger_time_hi,UINT32,\
                    "stefan_data2channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data2channel_trigger_time_hiI,UINT32,\
                    "stefan_data2channel_trigger_time_hiI","stefan_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data2channel_trigger_time_hiv,UINT32,\
                    "stefan_data2channel_trigger_time_hiv","stefan_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data2channel_trigger_time_lo,UINT32,\
                    "stefan_data2channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data2channel_trigger_time_loI,UINT32,\
                    "stefan_data2channel_trigger_time_loI","stefan_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data2channel_trigger_time_lov,UINT32,\
                    "stefan_data2channel_trigger_time_lov","stefan_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data2pileup,              UINT32,\
                    "stefan_data2pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data2pileupI,             UINT32,\
                    "stefan_data2pileupI",             "stefan_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data2pileupv,             UINT32,\
                    "stefan_data2pileupv",             "stefan_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data2overflow,            UINT32,\
                    "stefan_data2overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data2overflowI,           UINT32,\
                    "stefan_data2overflowI",           "stefan_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data2overflowv,           UINT32,\
                    "stefan_data2overflowv",           "stefan_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data2channel_cfd,         UINT32,\
                    "stefan_data2channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data2channel_cfdI,        UINT32,\
                    "stefan_data2channel_cfdI",        "stefan_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data2channel_cfdv,        UINT32,\
                    "stefan_data2channel_cfdv",        "stefan_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data2channel_energy,      UINT32,\
                    "stefan_data2channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data2channel_energyI,     UINT32,\
                    "stefan_data2channel_energyI",     "stefan_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data2channel_energyv,     UINT32,\
                    "stefan_data2channel_energyv",     "stefan_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data3trig,                UINT32,\
                    "stefan_data3trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     stefan_data3event_trigger_time_hi,UINT32,\
                    "stefan_data3event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     stefan_data3event_trigger_time_lo,UINT32,\
                    "stefan_data3event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data3hit_pattern,         UINT32,\
                    "stefan_data3hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data3channel_trigger_time_hi,UINT32,\
                    "stefan_data3channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data3channel_trigger_time_hiI,UINT32,\
                    "stefan_data3channel_trigger_time_hiI","stefan_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data3channel_trigger_time_hiv,UINT32,\
                    "stefan_data3channel_trigger_time_hiv","stefan_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data3channel_trigger_time_lo,UINT32,\
                    "stefan_data3channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data3channel_trigger_time_loI,UINT32,\
                    "stefan_data3channel_trigger_time_loI","stefan_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data3channel_trigger_time_lov,UINT32,\
                    "stefan_data3channel_trigger_time_lov","stefan_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data3pileup,              UINT32,\
                    "stefan_data3pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data3pileupI,             UINT32,\
                    "stefan_data3pileupI",             "stefan_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data3pileupv,             UINT32,\
                    "stefan_data3pileupv",             "stefan_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data3overflow,            UINT32,\
                    "stefan_data3overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data3overflowI,           UINT32,\
                    "stefan_data3overflowI",           "stefan_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data3overflowv,           UINT32,\
                    "stefan_data3overflowv",           "stefan_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data3channel_cfd,         UINT32,\
                    "stefan_data3channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data3channel_cfdI,        UINT32,\
                    "stefan_data3channel_cfdI",        "stefan_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data3channel_cfdv,        UINT32,\
                    "stefan_data3channel_cfdv",        "stefan_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data3channel_energy,      UINT32,\
                    "stefan_data3channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data3channel_energyI,     UINT32,\
                    "stefan_data3channel_energyI",     "stefan_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data3channel_energyv,     UINT32,\
                    "stefan_data3channel_energyv",     "stefan_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data4trig,                UINT32,\
                    "stefan_data4trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     stefan_data4event_trigger_time_hi,UINT32,\
                    "stefan_data4event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     stefan_data4event_trigger_time_lo,UINT32,\
                    "stefan_data4event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data4hit_pattern,         UINT32,\
                    "stefan_data4hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data4channel_trigger_time_hi,UINT32,\
                    "stefan_data4channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data4channel_trigger_time_hiI,UINT32,\
                    "stefan_data4channel_trigger_time_hiI","stefan_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data4channel_trigger_time_hiv,UINT32,\
                    "stefan_data4channel_trigger_time_hiv","stefan_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data4channel_trigger_time_lo,UINT32,\
                    "stefan_data4channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data4channel_trigger_time_loI,UINT32,\
                    "stefan_data4channel_trigger_time_loI","stefan_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data4channel_trigger_time_lov,UINT32,\
                    "stefan_data4channel_trigger_time_lov","stefan_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data4pileup,              UINT32,\
                    "stefan_data4pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data4pileupI,             UINT32,\
                    "stefan_data4pileupI",             "stefan_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data4pileupv,             UINT32,\
                    "stefan_data4pileupv",             "stefan_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data4overflow,            UINT32,\
                    "stefan_data4overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data4overflowI,           UINT32,\
                    "stefan_data4overflowI",           "stefan_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data4overflowv,           UINT32,\
                    "stefan_data4overflowv",           "stefan_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data4channel_cfd,         UINT32,\
                    "stefan_data4channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data4channel_cfdI,        UINT32,\
                    "stefan_data4channel_cfdI",        "stefan_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data4channel_cfdv,        UINT32,\
                    "stefan_data4channel_cfdv",        "stefan_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     stefan_data4channel_energy,      UINT32,\
                    "stefan_data4channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data4channel_energyI,     UINT32,\
                    "stefan_data4channel_energyI",     "stefan_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     stefan_data4channel_energyv,     UINT32,\
                    "stefan_data4channel_energyv",     "stefan_data4channel_energy",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_STEFAN_EXT_H101_STEFAN_H__*/

/*******************************************************/
