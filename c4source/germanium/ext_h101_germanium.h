/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_GERMANIUM_EXT_H101_GERMANIUM_H__
#define __GUARD_H101_GERMANIUM_EXT_H101_GERMANIUM_H__

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

typedef struct EXT_STR_h101_germanium_t
{
  /* UNPACK */
  uint32_t germanium_data1event_trigger_time_hi /* [-1,-1] */;
  uint32_t germanium_data1event_trigger_time_lo /* [-1,-1] */;
  uint32_t germanium_data1hit_pattern /* [0,65535] */;
  uint32_t germanium_data1num_channels_fired /* [-1,-1] */;
  uint32_t germanium_data1channel_id /* [0,16] */;
  uint32_t germanium_data1channel_idI[16 EXT_STRUCT_CTRL(germanium_data1channel_id)] /* [1,16] */;
  uint32_t germanium_data1channel_idv[16 EXT_STRUCT_CTRL(germanium_data1channel_id)] /* [0,255] */;
  uint32_t germanium_data1channel_trigger_time_hi /* [0,16] */;
  uint32_t germanium_data1channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(germanium_data1channel_trigger_time_hi)] /* [1,16] */;
  uint32_t germanium_data1channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(germanium_data1channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t germanium_data1channel_trigger_time_lo /* [0,16] */;
  uint32_t germanium_data1channel_trigger_time_loI[16 EXT_STRUCT_CTRL(germanium_data1channel_trigger_time_lo)] /* [1,16] */;
  uint32_t germanium_data1channel_trigger_time_lov[16 EXT_STRUCT_CTRL(germanium_data1channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t germanium_data1pileup /* [0,16] */;
  uint32_t germanium_data1pileupI[16 EXT_STRUCT_CTRL(germanium_data1pileup)] /* [1,16] */;
  uint32_t germanium_data1pileupv[16 EXT_STRUCT_CTRL(germanium_data1pileup)] /* [0,255] */;
  uint32_t germanium_data1overflow /* [0,16] */;
  uint32_t germanium_data1overflowI[16 EXT_STRUCT_CTRL(germanium_data1overflow)] /* [1,16] */;
  uint32_t germanium_data1overflowv[16 EXT_STRUCT_CTRL(germanium_data1overflow)] /* [0,255] */;
  uint32_t germanium_data1channel_cfd /* [0,16] */;
  uint32_t germanium_data1channel_cfdI[16 EXT_STRUCT_CTRL(germanium_data1channel_cfd)] /* [1,16] */;
  uint32_t germanium_data1channel_cfdv[16 EXT_STRUCT_CTRL(germanium_data1channel_cfd)] /* [0,255] */;
  uint32_t germanium_data1channel_energy /* [0,16] */;
  uint32_t germanium_data1channel_energyI[16 EXT_STRUCT_CTRL(germanium_data1channel_energy)] /* [1,16] */;
  uint32_t germanium_data1channel_energyv[16 EXT_STRUCT_CTRL(germanium_data1channel_energy)] /* [-1,-1] */;
  uint32_t germanium_data2event_trigger_time_hi /* [-1,-1] */;
  uint32_t germanium_data2event_trigger_time_lo /* [-1,-1] */;
  uint32_t germanium_data2hit_pattern /* [0,65535] */;
  uint32_t germanium_data2num_channels_fired /* [-1,-1] */;
  uint32_t germanium_data2channel_id /* [0,16] */;
  uint32_t germanium_data2channel_idI[16 EXT_STRUCT_CTRL(germanium_data2channel_id)] /* [1,16] */;
  uint32_t germanium_data2channel_idv[16 EXT_STRUCT_CTRL(germanium_data2channel_id)] /* [0,255] */;
  uint32_t germanium_data2channel_trigger_time_hi /* [0,16] */;
  uint32_t germanium_data2channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(germanium_data2channel_trigger_time_hi)] /* [1,16] */;
  uint32_t germanium_data2channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(germanium_data2channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t germanium_data2channel_trigger_time_lo /* [0,16] */;
  uint32_t germanium_data2channel_trigger_time_loI[16 EXT_STRUCT_CTRL(germanium_data2channel_trigger_time_lo)] /* [1,16] */;
  uint32_t germanium_data2channel_trigger_time_lov[16 EXT_STRUCT_CTRL(germanium_data2channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t germanium_data2pileup /* [0,16] */;
  uint32_t germanium_data2pileupI[16 EXT_STRUCT_CTRL(germanium_data2pileup)] /* [1,16] */;
  uint32_t germanium_data2pileupv[16 EXT_STRUCT_CTRL(germanium_data2pileup)] /* [0,255] */;
  uint32_t germanium_data2overflow /* [0,16] */;
  uint32_t germanium_data2overflowI[16 EXT_STRUCT_CTRL(germanium_data2overflow)] /* [1,16] */;
  uint32_t germanium_data2overflowv[16 EXT_STRUCT_CTRL(germanium_data2overflow)] /* [0,255] */;
  uint32_t germanium_data2channel_cfd /* [0,16] */;
  uint32_t germanium_data2channel_cfdI[16 EXT_STRUCT_CTRL(germanium_data2channel_cfd)] /* [1,16] */;
  uint32_t germanium_data2channel_cfdv[16 EXT_STRUCT_CTRL(germanium_data2channel_cfd)] /* [0,255] */;
  uint32_t germanium_data2channel_energy /* [0,16] */;
  uint32_t germanium_data2channel_energyI[16 EXT_STRUCT_CTRL(germanium_data2channel_energy)] /* [1,16] */;
  uint32_t germanium_data2channel_energyv[16 EXT_STRUCT_CTRL(germanium_data2channel_energy)] /* [-1,-1] */;
  uint32_t germanium_data3event_trigger_time_hi /* [-1,-1] */;
  uint32_t germanium_data3event_trigger_time_lo /* [-1,-1] */;
  uint32_t germanium_data3hit_pattern /* [0,65535] */;
  uint32_t germanium_data3num_channels_fired /* [-1,-1] */;
  uint32_t germanium_data3channel_id /* [0,16] */;
  uint32_t germanium_data3channel_idI[16 EXT_STRUCT_CTRL(germanium_data3channel_id)] /* [1,16] */;
  uint32_t germanium_data3channel_idv[16 EXT_STRUCT_CTRL(germanium_data3channel_id)] /* [0,255] */;
  uint32_t germanium_data3channel_trigger_time_hi /* [0,16] */;
  uint32_t germanium_data3channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(germanium_data3channel_trigger_time_hi)] /* [1,16] */;
  uint32_t germanium_data3channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(germanium_data3channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t germanium_data3channel_trigger_time_lo /* [0,16] */;
  uint32_t germanium_data3channel_trigger_time_loI[16 EXT_STRUCT_CTRL(germanium_data3channel_trigger_time_lo)] /* [1,16] */;
  uint32_t germanium_data3channel_trigger_time_lov[16 EXT_STRUCT_CTRL(germanium_data3channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t germanium_data3pileup /* [0,16] */;
  uint32_t germanium_data3pileupI[16 EXT_STRUCT_CTRL(germanium_data3pileup)] /* [1,16] */;
  uint32_t germanium_data3pileupv[16 EXT_STRUCT_CTRL(germanium_data3pileup)] /* [0,255] */;
  uint32_t germanium_data3overflow /* [0,16] */;
  uint32_t germanium_data3overflowI[16 EXT_STRUCT_CTRL(germanium_data3overflow)] /* [1,16] */;
  uint32_t germanium_data3overflowv[16 EXT_STRUCT_CTRL(germanium_data3overflow)] /* [0,255] */;
  uint32_t germanium_data3channel_cfd /* [0,16] */;
  uint32_t germanium_data3channel_cfdI[16 EXT_STRUCT_CTRL(germanium_data3channel_cfd)] /* [1,16] */;
  uint32_t germanium_data3channel_cfdv[16 EXT_STRUCT_CTRL(germanium_data3channel_cfd)] /* [0,255] */;
  uint32_t germanium_data3channel_energy /* [0,16] */;
  uint32_t germanium_data3channel_energyI[16 EXT_STRUCT_CTRL(germanium_data3channel_energy)] /* [1,16] */;
  uint32_t germanium_data3channel_energyv[16 EXT_STRUCT_CTRL(germanium_data3channel_energy)] /* [-1,-1] */;
  uint32_t germanium_data4event_trigger_time_hi /* [-1,-1] */;
  uint32_t germanium_data4event_trigger_time_lo /* [-1,-1] */;
  uint32_t germanium_data4hit_pattern /* [0,65535] */;
  uint32_t germanium_data4num_channels_fired /* [-1,-1] */;
  uint32_t germanium_data4channel_id /* [0,16] */;
  uint32_t germanium_data4channel_idI[16 EXT_STRUCT_CTRL(germanium_data4channel_id)] /* [1,16] */;
  uint32_t germanium_data4channel_idv[16 EXT_STRUCT_CTRL(germanium_data4channel_id)] /* [0,255] */;
  uint32_t germanium_data4channel_trigger_time_hi /* [0,16] */;
  uint32_t germanium_data4channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(germanium_data4channel_trigger_time_hi)] /* [1,16] */;
  uint32_t germanium_data4channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(germanium_data4channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t germanium_data4channel_trigger_time_lo /* [0,16] */;
  uint32_t germanium_data4channel_trigger_time_loI[16 EXT_STRUCT_CTRL(germanium_data4channel_trigger_time_lo)] /* [1,16] */;
  uint32_t germanium_data4channel_trigger_time_lov[16 EXT_STRUCT_CTRL(germanium_data4channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t germanium_data4pileup /* [0,16] */;
  uint32_t germanium_data4pileupI[16 EXT_STRUCT_CTRL(germanium_data4pileup)] /* [1,16] */;
  uint32_t germanium_data4pileupv[16 EXT_STRUCT_CTRL(germanium_data4pileup)] /* [0,255] */;
  uint32_t germanium_data4overflow /* [0,16] */;
  uint32_t germanium_data4overflowI[16 EXT_STRUCT_CTRL(germanium_data4overflow)] /* [1,16] */;
  uint32_t germanium_data4overflowv[16 EXT_STRUCT_CTRL(germanium_data4overflow)] /* [0,255] */;
  uint32_t germanium_data4channel_cfd /* [0,16] */;
  uint32_t germanium_data4channel_cfdI[16 EXT_STRUCT_CTRL(germanium_data4channel_cfd)] /* [1,16] */;
  uint32_t germanium_data4channel_cfdv[16 EXT_STRUCT_CTRL(germanium_data4channel_cfd)] /* [0,255] */;
  uint32_t germanium_data4channel_energy /* [0,16] */;
  uint32_t germanium_data4channel_energyI[16 EXT_STRUCT_CTRL(germanium_data4channel_energy)] /* [1,16] */;
  uint32_t germanium_data4channel_energyv[16 EXT_STRUCT_CTRL(germanium_data4channel_energy)] /* [-1,-1] */;
  uint32_t germanium_ts_subsystem_id /* [0,65535] */;
  uint32_t germanium_ts_t1 /* [0,65535] */;
  uint32_t germanium_ts_t2 /* [0,65535] */;
  uint32_t germanium_ts_t3 /* [0,65535] */;
  uint32_t germanium_ts_t4 /* [0,65535] */;

} EXT_STR_h101_germanium;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_germanium_onion_t
{
  /* UNPACK */
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
  } germanium_data[4];
  uint32_t germanium_ts_subsystem_id;
  uint32_t germanium_ts_t[4];

} EXT_STR_h101_germanium_onion;

/*******************************************************/

#define EXT_STR_h101_germanium_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_data1event_trigger_time_hi,UINT32,\
                    "germanium_data1event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_data1event_trigger_time_lo,UINT32,\
                    "germanium_data1event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1hit_pattern,      UINT32,\
                    "germanium_data1hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_data1num_channels_fired,UINT32,\
                    "germanium_data1num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_id,       UINT32,\
                    "germanium_data1channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_idI,      UINT32,\
                    "germanium_data1channel_idI",      "germanium_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_idv,      UINT32,\
                    "germanium_data1channel_idv",      "germanium_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_trigger_time_hi,UINT32,\
                    "germanium_data1channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_trigger_time_hiI,UINT32,\
                    "germanium_data1channel_trigger_time_hiI","germanium_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_trigger_time_hiv,UINT32,\
                    "germanium_data1channel_trigger_time_hiv","germanium_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_trigger_time_lo,UINT32,\
                    "germanium_data1channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_trigger_time_loI,UINT32,\
                    "germanium_data1channel_trigger_time_loI","germanium_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_trigger_time_lov,UINT32,\
                    "germanium_data1channel_trigger_time_lov","germanium_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup,           UINT32,\
                    "germanium_data1pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileupI,          UINT32,\
                    "germanium_data1pileupI",          "germanium_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileupv,          UINT32,\
                    "germanium_data1pileupv",          "germanium_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow,         UINT32,\
                    "germanium_data1overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflowI,        UINT32,\
                    "germanium_data1overflowI",        "germanium_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflowv,        UINT32,\
                    "germanium_data1overflowv",        "germanium_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_cfd,      UINT32,\
                    "germanium_data1channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_cfdI,     UINT32,\
                    "germanium_data1channel_cfdI",     "germanium_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_cfdv,     UINT32,\
                    "germanium_data1channel_cfdv",     "germanium_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_energy,   UINT32,\
                    "germanium_data1channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_energyI,  UINT32,\
                    "germanium_data1channel_energyI",  "germanium_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data1channel_energyv,  UINT32,\
                    "germanium_data1channel_energyv",  "germanium_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_data2event_trigger_time_hi,UINT32,\
                    "germanium_data2event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_data2event_trigger_time_lo,UINT32,\
                    "germanium_data2event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2hit_pattern,      UINT32,\
                    "germanium_data2hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_data2num_channels_fired,UINT32,\
                    "germanium_data2num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_id,       UINT32,\
                    "germanium_data2channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_idI,      UINT32,\
                    "germanium_data2channel_idI",      "germanium_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_idv,      UINT32,\
                    "germanium_data2channel_idv",      "germanium_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_trigger_time_hi,UINT32,\
                    "germanium_data2channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_trigger_time_hiI,UINT32,\
                    "germanium_data2channel_trigger_time_hiI","germanium_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_trigger_time_hiv,UINT32,\
                    "germanium_data2channel_trigger_time_hiv","germanium_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_trigger_time_lo,UINT32,\
                    "germanium_data2channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_trigger_time_loI,UINT32,\
                    "germanium_data2channel_trigger_time_loI","germanium_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_trigger_time_lov,UINT32,\
                    "germanium_data2channel_trigger_time_lov","germanium_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup,           UINT32,\
                    "germanium_data2pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileupI,          UINT32,\
                    "germanium_data2pileupI",          "germanium_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileupv,          UINT32,\
                    "germanium_data2pileupv",          "germanium_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow,         UINT32,\
                    "germanium_data2overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflowI,        UINT32,\
                    "germanium_data2overflowI",        "germanium_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflowv,        UINT32,\
                    "germanium_data2overflowv",        "germanium_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_cfd,      UINT32,\
                    "germanium_data2channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_cfdI,     UINT32,\
                    "germanium_data2channel_cfdI",     "germanium_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_cfdv,     UINT32,\
                    "germanium_data2channel_cfdv",     "germanium_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_energy,   UINT32,\
                    "germanium_data2channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_energyI,  UINT32,\
                    "germanium_data2channel_energyI",  "germanium_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data2channel_energyv,  UINT32,\
                    "germanium_data2channel_energyv",  "germanium_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_data3event_trigger_time_hi,UINT32,\
                    "germanium_data3event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_data3event_trigger_time_lo,UINT32,\
                    "germanium_data3event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3hit_pattern,      UINT32,\
                    "germanium_data3hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_data3num_channels_fired,UINT32,\
                    "germanium_data3num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_id,       UINT32,\
                    "germanium_data3channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_idI,      UINT32,\
                    "germanium_data3channel_idI",      "germanium_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_idv,      UINT32,\
                    "germanium_data3channel_idv",      "germanium_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_trigger_time_hi,UINT32,\
                    "germanium_data3channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_trigger_time_hiI,UINT32,\
                    "germanium_data3channel_trigger_time_hiI","germanium_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_trigger_time_hiv,UINT32,\
                    "germanium_data3channel_trigger_time_hiv","germanium_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_trigger_time_lo,UINT32,\
                    "germanium_data3channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_trigger_time_loI,UINT32,\
                    "germanium_data3channel_trigger_time_loI","germanium_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_trigger_time_lov,UINT32,\
                    "germanium_data3channel_trigger_time_lov","germanium_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup,           UINT32,\
                    "germanium_data3pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileupI,          UINT32,\
                    "germanium_data3pileupI",          "germanium_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileupv,          UINT32,\
                    "germanium_data3pileupv",          "germanium_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow,         UINT32,\
                    "germanium_data3overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflowI,        UINT32,\
                    "germanium_data3overflowI",        "germanium_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflowv,        UINT32,\
                    "germanium_data3overflowv",        "germanium_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_cfd,      UINT32,\
                    "germanium_data3channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_cfdI,     UINT32,\
                    "germanium_data3channel_cfdI",     "germanium_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_cfdv,     UINT32,\
                    "germanium_data3channel_cfdv",     "germanium_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_energy,   UINT32,\
                    "germanium_data3channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_energyI,  UINT32,\
                    "germanium_data3channel_energyI",  "germanium_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data3channel_energyv,  UINT32,\
                    "germanium_data3channel_energyv",  "germanium_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_data4event_trigger_time_hi,UINT32,\
                    "germanium_data4event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_data4event_trigger_time_lo,UINT32,\
                    "germanium_data4event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4hit_pattern,      UINT32,\
                    "germanium_data4hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_data4num_channels_fired,UINT32,\
                    "germanium_data4num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_id,       UINT32,\
                    "germanium_data4channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_idI,      UINT32,\
                    "germanium_data4channel_idI",      "germanium_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_idv,      UINT32,\
                    "germanium_data4channel_idv",      "germanium_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_trigger_time_hi,UINT32,\
                    "germanium_data4channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_trigger_time_hiI,UINT32,\
                    "germanium_data4channel_trigger_time_hiI","germanium_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_trigger_time_hiv,UINT32,\
                    "germanium_data4channel_trigger_time_hiv","germanium_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_trigger_time_lo,UINT32,\
                    "germanium_data4channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_trigger_time_loI,UINT32,\
                    "germanium_data4channel_trigger_time_loI","germanium_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_trigger_time_lov,UINT32,\
                    "germanium_data4channel_trigger_time_lov","germanium_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup,           UINT32,\
                    "germanium_data4pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileupI,          UINT32,\
                    "germanium_data4pileupI",          "germanium_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileupv,          UINT32,\
                    "germanium_data4pileupv",          "germanium_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow,         UINT32,\
                    "germanium_data4overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflowI,        UINT32,\
                    "germanium_data4overflowI",        "germanium_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflowv,        UINT32,\
                    "germanium_data4overflowv",        "germanium_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_cfd,      UINT32,\
                    "germanium_data4channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_cfdI,     UINT32,\
                    "germanium_data4channel_cfdI",     "germanium_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_cfdv,     UINT32,\
                    "germanium_data4channel_cfdv",     "germanium_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_energy,   UINT32,\
                    "germanium_data4channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_energyI,  UINT32,\
                    "germanium_data4channel_energyI",  "germanium_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_data4channel_energyv,  UINT32,\
                    "germanium_data4channel_energyv",  "germanium_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_ts_subsystem_id,       UINT32,\
                    "germanium_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_ts_t1,                 UINT32,\
                    "germanium_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_ts_t2,                 UINT32,\
                    "germanium_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_ts_t3,                 UINT32,\
                    "germanium_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_ts_t4,                 UINT32,\
                    "germanium_ts_t4",65535,0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_GERMANIUM_EXT_H101_GERMANIUM_H__*/

/*******************************************************/
