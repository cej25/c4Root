/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_h101_GERMANIUM_EXT_h101_GERMANIUM_H__
#define __GUARD_h101_GERMANIUM_EXT_h101_GERMANIUM_H__

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

typedef struct EXT_STR_h101_GERMANIUM_t
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
  uint32_t germanium_data1pileup1 /* [0,255] */;
  uint32_t germanium_data1pileup2 /* [0,255] */;
  uint32_t germanium_data1pileup3 /* [0,255] */;
  uint32_t germanium_data1pileup4 /* [0,255] */;
  uint32_t germanium_data1pileup5 /* [0,255] */;
  uint32_t germanium_data1pileup6 /* [0,255] */;
  uint32_t germanium_data1pileup7 /* [0,255] */;
  uint32_t germanium_data1pileup8 /* [0,255] */;
  uint32_t germanium_data1pileup9 /* [0,255] */;
  uint32_t germanium_data1pileup10 /* [0,255] */;
  uint32_t germanium_data1pileup11 /* [0,255] */;
  uint32_t germanium_data1pileup12 /* [0,255] */;
  uint32_t germanium_data1pileup13 /* [0,255] */;
  uint32_t germanium_data1pileup14 /* [0,255] */;
  uint32_t germanium_data1pileup15 /* [0,255] */;
  uint32_t germanium_data1pileup16 /* [0,255] */;
  uint32_t germanium_data1overflow1 /* [0,255] */;
  uint32_t germanium_data1overflow2 /* [0,255] */;
  uint32_t germanium_data1overflow3 /* [0,255] */;
  uint32_t germanium_data1overflow4 /* [0,255] */;
  uint32_t germanium_data1overflow5 /* [0,255] */;
  uint32_t germanium_data1overflow6 /* [0,255] */;
  uint32_t germanium_data1overflow7 /* [0,255] */;
  uint32_t germanium_data1overflow8 /* [0,255] */;
  uint32_t germanium_data1overflow9 /* [0,255] */;
  uint32_t germanium_data1overflow10 /* [0,255] */;
  uint32_t germanium_data1overflow11 /* [0,255] */;
  uint32_t germanium_data1overflow12 /* [0,255] */;
  uint32_t germanium_data1overflow13 /* [0,255] */;
  uint32_t germanium_data1overflow14 /* [0,255] */;
  uint32_t germanium_data1overflow15 /* [0,255] */;
  uint32_t germanium_data1overflow16 /* [0,255] */;
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
  uint32_t germanium_data2pileup1 /* [0,255] */;
  uint32_t germanium_data2pileup2 /* [0,255] */;
  uint32_t germanium_data2pileup3 /* [0,255] */;
  uint32_t germanium_data2pileup4 /* [0,255] */;
  uint32_t germanium_data2pileup5 /* [0,255] */;
  uint32_t germanium_data2pileup6 /* [0,255] */;
  uint32_t germanium_data2pileup7 /* [0,255] */;
  uint32_t germanium_data2pileup8 /* [0,255] */;
  uint32_t germanium_data2pileup9 /* [0,255] */;
  uint32_t germanium_data2pileup10 /* [0,255] */;
  uint32_t germanium_data2pileup11 /* [0,255] */;
  uint32_t germanium_data2pileup12 /* [0,255] */;
  uint32_t germanium_data2pileup13 /* [0,255] */;
  uint32_t germanium_data2pileup14 /* [0,255] */;
  uint32_t germanium_data2pileup15 /* [0,255] */;
  uint32_t germanium_data2pileup16 /* [0,255] */;
  uint32_t germanium_data2overflow1 /* [0,255] */;
  uint32_t germanium_data2overflow2 /* [0,255] */;
  uint32_t germanium_data2overflow3 /* [0,255] */;
  uint32_t germanium_data2overflow4 /* [0,255] */;
  uint32_t germanium_data2overflow5 /* [0,255] */;
  uint32_t germanium_data2overflow6 /* [0,255] */;
  uint32_t germanium_data2overflow7 /* [0,255] */;
  uint32_t germanium_data2overflow8 /* [0,255] */;
  uint32_t germanium_data2overflow9 /* [0,255] */;
  uint32_t germanium_data2overflow10 /* [0,255] */;
  uint32_t germanium_data2overflow11 /* [0,255] */;
  uint32_t germanium_data2overflow12 /* [0,255] */;
  uint32_t germanium_data2overflow13 /* [0,255] */;
  uint32_t germanium_data2overflow14 /* [0,255] */;
  uint32_t germanium_data2overflow15 /* [0,255] */;
  uint32_t germanium_data2overflow16 /* [0,255] */;
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
  uint32_t germanium_data3pileup1 /* [0,255] */;
  uint32_t germanium_data3pileup2 /* [0,255] */;
  uint32_t germanium_data3pileup3 /* [0,255] */;
  uint32_t germanium_data3pileup4 /* [0,255] */;
  uint32_t germanium_data3pileup5 /* [0,255] */;
  uint32_t germanium_data3pileup6 /* [0,255] */;
  uint32_t germanium_data3pileup7 /* [0,255] */;
  uint32_t germanium_data3pileup8 /* [0,255] */;
  uint32_t germanium_data3pileup9 /* [0,255] */;
  uint32_t germanium_data3pileup10 /* [0,255] */;
  uint32_t germanium_data3pileup11 /* [0,255] */;
  uint32_t germanium_data3pileup12 /* [0,255] */;
  uint32_t germanium_data3pileup13 /* [0,255] */;
  uint32_t germanium_data3pileup14 /* [0,255] */;
  uint32_t germanium_data3pileup15 /* [0,255] */;
  uint32_t germanium_data3pileup16 /* [0,255] */;
  uint32_t germanium_data3overflow1 /* [0,255] */;
  uint32_t germanium_data3overflow2 /* [0,255] */;
  uint32_t germanium_data3overflow3 /* [0,255] */;
  uint32_t germanium_data3overflow4 /* [0,255] */;
  uint32_t germanium_data3overflow5 /* [0,255] */;
  uint32_t germanium_data3overflow6 /* [0,255] */;
  uint32_t germanium_data3overflow7 /* [0,255] */;
  uint32_t germanium_data3overflow8 /* [0,255] */;
  uint32_t germanium_data3overflow9 /* [0,255] */;
  uint32_t germanium_data3overflow10 /* [0,255] */;
  uint32_t germanium_data3overflow11 /* [0,255] */;
  uint32_t germanium_data3overflow12 /* [0,255] */;
  uint32_t germanium_data3overflow13 /* [0,255] */;
  uint32_t germanium_data3overflow14 /* [0,255] */;
  uint32_t germanium_data3overflow15 /* [0,255] */;
  uint32_t germanium_data3overflow16 /* [0,255] */;
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
  uint32_t germanium_data4pileup1 /* [0,255] */;
  uint32_t germanium_data4pileup2 /* [0,255] */;
  uint32_t germanium_data4pileup3 /* [0,255] */;
  uint32_t germanium_data4pileup4 /* [0,255] */;
  uint32_t germanium_data4pileup5 /* [0,255] */;
  uint32_t germanium_data4pileup6 /* [0,255] */;
  uint32_t germanium_data4pileup7 /* [0,255] */;
  uint32_t germanium_data4pileup8 /* [0,255] */;
  uint32_t germanium_data4pileup9 /* [0,255] */;
  uint32_t germanium_data4pileup10 /* [0,255] */;
  uint32_t germanium_data4pileup11 /* [0,255] */;
  uint32_t germanium_data4pileup12 /* [0,255] */;
  uint32_t germanium_data4pileup13 /* [0,255] */;
  uint32_t germanium_data4pileup14 /* [0,255] */;
  uint32_t germanium_data4pileup15 /* [0,255] */;
  uint32_t germanium_data4pileup16 /* [0,255] */;
  uint32_t germanium_data4overflow1 /* [0,255] */;
  uint32_t germanium_data4overflow2 /* [0,255] */;
  uint32_t germanium_data4overflow3 /* [0,255] */;
  uint32_t germanium_data4overflow4 /* [0,255] */;
  uint32_t germanium_data4overflow5 /* [0,255] */;
  uint32_t germanium_data4overflow6 /* [0,255] */;
  uint32_t germanium_data4overflow7 /* [0,255] */;
  uint32_t germanium_data4overflow8 /* [0,255] */;
  uint32_t germanium_data4overflow9 /* [0,255] */;
  uint32_t germanium_data4overflow10 /* [0,255] */;
  uint32_t germanium_data4overflow11 /* [0,255] */;
  uint32_t germanium_data4overflow12 /* [0,255] */;
  uint32_t germanium_data4overflow13 /* [0,255] */;
  uint32_t germanium_data4overflow14 /* [0,255] */;
  uint32_t germanium_data4overflow15 /* [0,255] */;
  uint32_t germanium_data4overflow16 /* [0,255] */;
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

} EXT_STR_h101_GERMANIUM;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_GERMANIUM_onion_t
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
    uint32_t pileup[16];
    uint32_t overflow[16];
    uint32_t channel_cfd;
    uint32_t channel_cfdI[16 /* channel_cfd */];
    uint32_t channel_cfdv[16 /* channel_cfd */];
    uint32_t channel_energy;
    uint32_t channel_energyI[16 /* channel_energy */];
    uint32_t channel_energyv[16 /* channel_energy */];
  } germanium_data[4];
  uint32_t germanium_ts_subsystem_id;
  uint32_t germanium_ts_t[4];

} EXT_STR_h101_GERMANIUM_onion;

/*******************************************************/

#define EXT_STR_h101_GERMANIUM_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
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
                     germanium_data1pileup1,          UINT32,\
                    "germanium_data1pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup2,          UINT32,\
                    "germanium_data1pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup3,          UINT32,\
                    "germanium_data1pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup4,          UINT32,\
                    "germanium_data1pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup5,          UINT32,\
                    "germanium_data1pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup6,          UINT32,\
                    "germanium_data1pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup7,          UINT32,\
                    "germanium_data1pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup8,          UINT32,\
                    "germanium_data1pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup9,          UINT32,\
                    "germanium_data1pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup10,         UINT32,\
                    "germanium_data1pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup11,         UINT32,\
                    "germanium_data1pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup12,         UINT32,\
                    "germanium_data1pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup13,         UINT32,\
                    "germanium_data1pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup14,         UINT32,\
                    "germanium_data1pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup15,         UINT32,\
                    "germanium_data1pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1pileup16,         UINT32,\
                    "germanium_data1pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow1,        UINT32,\
                    "germanium_data1overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow2,        UINT32,\
                    "germanium_data1overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow3,        UINT32,\
                    "germanium_data1overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow4,        UINT32,\
                    "germanium_data1overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow5,        UINT32,\
                    "germanium_data1overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow6,        UINT32,\
                    "germanium_data1overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow7,        UINT32,\
                    "germanium_data1overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow8,        UINT32,\
                    "germanium_data1overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow9,        UINT32,\
                    "germanium_data1overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow10,       UINT32,\
                    "germanium_data1overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow11,       UINT32,\
                    "germanium_data1overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow12,       UINT32,\
                    "germanium_data1overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow13,       UINT32,\
                    "germanium_data1overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow14,       UINT32,\
                    "germanium_data1overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow15,       UINT32,\
                    "germanium_data1overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data1overflow16,       UINT32,\
                    "germanium_data1overflow16",255,0/*flags*/); \
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
                     germanium_data2pileup1,          UINT32,\
                    "germanium_data2pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup2,          UINT32,\
                    "germanium_data2pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup3,          UINT32,\
                    "germanium_data2pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup4,          UINT32,\
                    "germanium_data2pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup5,          UINT32,\
                    "germanium_data2pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup6,          UINT32,\
                    "germanium_data2pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup7,          UINT32,\
                    "germanium_data2pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup8,          UINT32,\
                    "germanium_data2pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup9,          UINT32,\
                    "germanium_data2pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup10,         UINT32,\
                    "germanium_data2pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup11,         UINT32,\
                    "germanium_data2pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup12,         UINT32,\
                    "germanium_data2pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup13,         UINT32,\
                    "germanium_data2pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup14,         UINT32,\
                    "germanium_data2pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup15,         UINT32,\
                    "germanium_data2pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2pileup16,         UINT32,\
                    "germanium_data2pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow1,        UINT32,\
                    "germanium_data2overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow2,        UINT32,\
                    "germanium_data2overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow3,        UINT32,\
                    "germanium_data2overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow4,        UINT32,\
                    "germanium_data2overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow5,        UINT32,\
                    "germanium_data2overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow6,        UINT32,\
                    "germanium_data2overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow7,        UINT32,\
                    "germanium_data2overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow8,        UINT32,\
                    "germanium_data2overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow9,        UINT32,\
                    "germanium_data2overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow10,       UINT32,\
                    "germanium_data2overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow11,       UINT32,\
                    "germanium_data2overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow12,       UINT32,\
                    "germanium_data2overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow13,       UINT32,\
                    "germanium_data2overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow14,       UINT32,\
                    "germanium_data2overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow15,       UINT32,\
                    "germanium_data2overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data2overflow16,       UINT32,\
                    "germanium_data2overflow16",255,0/*flags*/); \
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
                     germanium_data3pileup1,          UINT32,\
                    "germanium_data3pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup2,          UINT32,\
                    "germanium_data3pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup3,          UINT32,\
                    "germanium_data3pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup4,          UINT32,\
                    "germanium_data3pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup5,          UINT32,\
                    "germanium_data3pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup6,          UINT32,\
                    "germanium_data3pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup7,          UINT32,\
                    "germanium_data3pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup8,          UINT32,\
                    "germanium_data3pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup9,          UINT32,\
                    "germanium_data3pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup10,         UINT32,\
                    "germanium_data3pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup11,         UINT32,\
                    "germanium_data3pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup12,         UINT32,\
                    "germanium_data3pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup13,         UINT32,\
                    "germanium_data3pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup14,         UINT32,\
                    "germanium_data3pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup15,         UINT32,\
                    "germanium_data3pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3pileup16,         UINT32,\
                    "germanium_data3pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow1,        UINT32,\
                    "germanium_data3overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow2,        UINT32,\
                    "germanium_data3overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow3,        UINT32,\
                    "germanium_data3overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow4,        UINT32,\
                    "germanium_data3overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow5,        UINT32,\
                    "germanium_data3overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow6,        UINT32,\
                    "germanium_data3overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow7,        UINT32,\
                    "germanium_data3overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow8,        UINT32,\
                    "germanium_data3overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow9,        UINT32,\
                    "germanium_data3overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow10,       UINT32,\
                    "germanium_data3overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow11,       UINT32,\
                    "germanium_data3overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow12,       UINT32,\
                    "germanium_data3overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow13,       UINT32,\
                    "germanium_data3overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow14,       UINT32,\
                    "germanium_data3overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow15,       UINT32,\
                    "germanium_data3overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data3overflow16,       UINT32,\
                    "germanium_data3overflow16",255,0/*flags*/); \
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
                     germanium_data4pileup1,          UINT32,\
                    "germanium_data4pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup2,          UINT32,\
                    "germanium_data4pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup3,          UINT32,\
                    "germanium_data4pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup4,          UINT32,\
                    "germanium_data4pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup5,          UINT32,\
                    "germanium_data4pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup6,          UINT32,\
                    "germanium_data4pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup7,          UINT32,\
                    "germanium_data4pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup8,          UINT32,\
                    "germanium_data4pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup9,          UINT32,\
                    "germanium_data4pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup10,         UINT32,\
                    "germanium_data4pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup11,         UINT32,\
                    "germanium_data4pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup12,         UINT32,\
                    "germanium_data4pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup13,         UINT32,\
                    "germanium_data4pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup14,         UINT32,\
                    "germanium_data4pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup15,         UINT32,\
                    "germanium_data4pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4pileup16,         UINT32,\
                    "germanium_data4pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow1,        UINT32,\
                    "germanium_data4overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow2,        UINT32,\
                    "germanium_data4overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow3,        UINT32,\
                    "germanium_data4overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow4,        UINT32,\
                    "germanium_data4overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow5,        UINT32,\
                    "germanium_data4overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow6,        UINT32,\
                    "germanium_data4overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow7,        UINT32,\
                    "germanium_data4overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow8,        UINT32,\
                    "germanium_data4overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow9,        UINT32,\
                    "germanium_data4overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow10,       UINT32,\
                    "germanium_data4overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow11,       UINT32,\
                    "germanium_data4overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow12,       UINT32,\
                    "germanium_data4overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow13,       UINT32,\
                    "germanium_data4overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow14,       UINT32,\
                    "germanium_data4overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow15,       UINT32,\
                    "germanium_data4overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_data4overflow16,       UINT32,\
                    "germanium_data4overflow16",255,0/*flags*/); \
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

#endif/*__GUARD_h101_GERMANIUM_EXT_h101_GERMANIUM_GERMANIUM_H__*/

/*******************************************************/
