/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_TAMEX_EXT_H101_TAMEX_H__
#define __GUARD_H101_TAMEX_EXT_H101_TAMEX_H__

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

typedef struct EXT_STR_h101_tamex_t
{
  /* UNPACK */
  uint32_t tamex_ts_subsystem_id /* [0,65535] */;
  uint32_t tamex_ts_t1 /* [0,65535] */;
  uint32_t tamex_ts_t2 /* [0,65535] */;
  uint32_t tamex_ts_t3 /* [0,65535] */;
  uint32_t tamex_ts_t4 /* [0,65535] */;
  uint32_t tamex_pid /* [-1,-1] */;
  uint32_t tamex_trigger_window_post_trig_ns /* [0,65535] */;
  uint32_t tamex_trigger_window_pre_trig_ns /* [0,65535] */;
  uint32_t tamex_bplast1trig /* [0,65535] */;
  uint32_t tamex_bplast1event_size /* [-1,-1] */;
  uint32_t tamex_bplast1time_coarse /* [0,1024] */;
  uint32_t tamex_bplast1time_coarsev[1024 EXT_STRUCT_CTRL(tamex_bplast1time_coarse)] /* [0,65535] */;
  uint32_t tamex_bplast1time_fine /* [0,1024] */;
  uint32_t tamex_bplast1time_finev[1024 EXT_STRUCT_CTRL(tamex_bplast1time_fine)] /* [0,65535] */;
  uint32_t tamex_bplast1time_edge /* [0,1024] */;
  uint32_t tamex_bplast1time_edgev[1024 EXT_STRUCT_CTRL(tamex_bplast1time_edge)] /* [0,65535] */;
  uint32_t tamex_bplast1time_channel /* [0,1024] */;
  uint32_t tamex_bplast1time_channelv[1024 EXT_STRUCT_CTRL(tamex_bplast1time_channel)] /* [0,65535] */;
  uint32_t tamex_bplast1time_epoch /* [0,1024] */;
  uint32_t tamex_bplast1time_epochv[1024 EXT_STRUCT_CTRL(tamex_bplast1time_epoch)] /* [-1,-1] */;
  uint32_t tamex_fatima1trig /* [0,65535] */;
  uint32_t tamex_fatima1event_size /* [-1,-1] */;
  uint32_t tamex_fatima1time_coarse /* [0,1024] */;
  uint32_t tamex_fatima1time_coarsev[1024 EXT_STRUCT_CTRL(tamex_fatima1time_coarse)] /* [0,65535] */;
  uint32_t tamex_fatima1time_fine /* [0,1024] */;
  uint32_t tamex_fatima1time_finev[1024 EXT_STRUCT_CTRL(tamex_fatima1time_fine)] /* [0,65535] */;
  uint32_t tamex_fatima1time_edge /* [0,1024] */;
  uint32_t tamex_fatima1time_edgev[1024 EXT_STRUCT_CTRL(tamex_fatima1time_edge)] /* [0,65535] */;
  uint32_t tamex_fatima1time_channel /* [0,1024] */;
  uint32_t tamex_fatima1time_channelv[1024 EXT_STRUCT_CTRL(tamex_fatima1time_channel)] /* [0,65535] */;
  uint32_t tamex_fatima1time_epoch /* [0,1024] */;
  uint32_t tamex_fatima1time_epochv[1024 EXT_STRUCT_CTRL(tamex_fatima1time_epoch)] /* [-1,-1] */;

} EXT_STR_h101_tamex;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_tamex_onion_t
{
  /* UNPACK */
  uint32_t tamex_ts_subsystem_id;
  uint32_t tamex_ts_t[4];
  uint32_t tamex_pid;
  uint32_t tamex_trigger_window_post_trig_ns;
  uint32_t tamex_trigger_window_pre_trig_ns;
  struct {
    uint32_t trig;
    uint32_t event_size;
    uint32_t time_coarse;
    uint32_t time_coarsev[1024 /* time_coarse */];
    uint32_t time_fine;
    uint32_t time_finev[1024 /* time_fine */];
    uint32_t time_edge;
    uint32_t time_edgev[1024 /* time_edge */];
    uint32_t time_channel;
    uint32_t time_channelv[1024 /* time_channel */];
    uint32_t time_epoch;
    uint32_t time_epochv[1024 /* time_epoch */];
  } tamex_bplast[1];
  struct {
    uint32_t trig;
    uint32_t event_size;
    uint32_t time_coarse;
    uint32_t time_coarsev[1024 /* time_coarse */];
    uint32_t time_fine;
    uint32_t time_finev[1024 /* time_fine */];
    uint32_t time_edge;
    uint32_t time_edgev[1024 /* time_edge */];
    uint32_t time_channel;
    uint32_t time_channelv[1024 /* time_channel */];
    uint32_t time_epoch;
    uint32_t time_epochv[1024 /* time_epoch */];
  } tamex_fatima[1];

} EXT_STR_h101_tamex_onion;

/*******************************************************/

#define EXT_STR_h101_tamex_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_ts_subsystem_id,           UINT32,\
                    "tamex_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_ts_t1,                     UINT32,\
                    "tamex_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_ts_t2,                     UINT32,\
                    "tamex_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_ts_t3,                     UINT32,\
                    "tamex_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_ts_t4,                     UINT32,\
                    "tamex_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_pid,                       UINT32,\
                    "tamex_pid",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_trigger_window_post_trig_ns,UINT32,\
                    "tamex_trigger_window_post_trig_ns",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_trigger_window_pre_trig_ns,UINT32,\
                    "tamex_trigger_window_pre_trig_ns",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1trig,               UINT32,\
                    "tamex_bplast1trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_bplast1event_size,         UINT32,\
                    "tamex_bplast1event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_coarse,        UINT32,\
                    "tamex_bplast1time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_coarsev,       UINT32,\
                    "tamex_bplast1time_coarsev",       "tamex_bplast1time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_fine,          UINT32,\
                    "tamex_bplast1time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_finev,         UINT32,\
                    "tamex_bplast1time_finev",         "tamex_bplast1time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_edge,          UINT32,\
                    "tamex_bplast1time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_edgev,         UINT32,\
                    "tamex_bplast1time_edgev",         "tamex_bplast1time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_channel,       UINT32,\
                    "tamex_bplast1time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_channelv,      UINT32,\
                    "tamex_bplast1time_channelv",      "tamex_bplast1time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_epoch,         UINT32,\
                    "tamex_bplast1time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_epochv,        UINT32,\
                    "tamex_bplast1time_epochv",        "tamex_bplast1time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1trig,               UINT32,\
                    "tamex_fatima1trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_fatima1event_size,         UINT32,\
                    "tamex_fatima1event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_coarse,        UINT32,\
                    "tamex_fatima1time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_coarsev,       UINT32,\
                    "tamex_fatima1time_coarsev",       "tamex_fatima1time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_fine,          UINT32,\
                    "tamex_fatima1time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_finev,         UINT32,\
                    "tamex_fatima1time_finev",         "tamex_fatima1time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_edge,          UINT32,\
                    "tamex_fatima1time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_edgev,         UINT32,\
                    "tamex_fatima1time_edgev",         "tamex_fatima1time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_channel,       UINT32,\
                    "tamex_fatima1time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_channelv,      UINT32,\
                    "tamex_fatima1time_channelv",      "tamex_fatima1time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_epoch,         UINT32,\
                    "tamex_fatima1time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_epochv,        UINT32,\
                    "tamex_fatima1time_epochv",        "tamex_fatima1time_epoch",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_TAMEX_EXT_H101_TAMEX_H__*/

/*******************************************************/
