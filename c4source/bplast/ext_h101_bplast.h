/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_BPLAST_EXT_H101_BPLAST_H__
#define __GUARD_H101_BPLAST_EXT_H101_BPLAST_H__

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

typedef struct EXT_STR_h101_bplast_t
{
  /* UNPACK */
  uint32_t bplast_tamex1event_size /* [-1,-1] */;
  uint32_t bplast_tamex1time_coarse /* [0,1024] */;
  uint32_t bplast_tamex1time_coarsev[1024 EXT_STRUCT_CTRL(bplast_tamex1time_coarse)] /* [0,65535] */;
  uint32_t bplast_tamex1time_fine /* [0,1024] */;
  uint32_t bplast_tamex1time_finev[1024 EXT_STRUCT_CTRL(bplast_tamex1time_fine)] /* [0,65535] */;
  uint32_t bplast_tamex1time_edge /* [0,1024] */;
  uint32_t bplast_tamex1time_edgev[1024 EXT_STRUCT_CTRL(bplast_tamex1time_edge)] /* [0,65535] */;
  uint32_t bplast_tamex1time_channel /* [0,1024] */;
  uint32_t bplast_tamex1time_channelv[1024 EXT_STRUCT_CTRL(bplast_tamex1time_channel)] /* [0,65535] */;
  uint32_t bplast_tamex1time_epoch /* [0,1024] */;
  uint32_t bplast_tamex1time_epochv[1024 EXT_STRUCT_CTRL(bplast_tamex1time_epoch)] /* [-1,-1] */;
  uint32_t bplast_tamex2event_size /* [-1,-1] */;
  uint32_t bplast_tamex2time_coarse /* [0,1024] */;
  uint32_t bplast_tamex2time_coarsev[1024 EXT_STRUCT_CTRL(bplast_tamex2time_coarse)] /* [0,65535] */;
  uint32_t bplast_tamex2time_fine /* [0,1024] */;
  uint32_t bplast_tamex2time_finev[1024 EXT_STRUCT_CTRL(bplast_tamex2time_fine)] /* [0,65535] */;
  uint32_t bplast_tamex2time_edge /* [0,1024] */;
  uint32_t bplast_tamex2time_edgev[1024 EXT_STRUCT_CTRL(bplast_tamex2time_edge)] /* [0,65535] */;
  uint32_t bplast_tamex2time_channel /* [0,1024] */;
  uint32_t bplast_tamex2time_channelv[1024 EXT_STRUCT_CTRL(bplast_tamex2time_channel)] /* [0,65535] */;
  uint32_t bplast_tamex2time_epoch /* [0,1024] */;
  uint32_t bplast_tamex2time_epochv[1024 EXT_STRUCT_CTRL(bplast_tamex2time_epoch)] /* [-1,-1] */;
  uint32_t bplast_tamex3event_size /* [-1,-1] */;
  uint32_t bplast_tamex3time_coarse /* [0,1024] */;
  uint32_t bplast_tamex3time_coarsev[1024 EXT_STRUCT_CTRL(bplast_tamex3time_coarse)] /* [0,65535] */;
  uint32_t bplast_tamex3time_fine /* [0,1024] */;
  uint32_t bplast_tamex3time_finev[1024 EXT_STRUCT_CTRL(bplast_tamex3time_fine)] /* [0,65535] */;
  uint32_t bplast_tamex3time_edge /* [0,1024] */;
  uint32_t bplast_tamex3time_edgev[1024 EXT_STRUCT_CTRL(bplast_tamex3time_edge)] /* [0,65535] */;
  uint32_t bplast_tamex3time_channel /* [0,1024] */;
  uint32_t bplast_tamex3time_channelv[1024 EXT_STRUCT_CTRL(bplast_tamex3time_channel)] /* [0,65535] */;
  uint32_t bplast_tamex3time_epoch /* [0,1024] */;
  uint32_t bplast_tamex3time_epochv[1024 EXT_STRUCT_CTRL(bplast_tamex3time_epoch)] /* [-1,-1] */;
  uint32_t bplast_tamex4event_size /* [-1,-1] */;
  uint32_t bplast_tamex4time_coarse /* [0,1024] */;
  uint32_t bplast_tamex4time_coarsev[1024 EXT_STRUCT_CTRL(bplast_tamex4time_coarse)] /* [0,65535] */;
  uint32_t bplast_tamex4time_fine /* [0,1024] */;
  uint32_t bplast_tamex4time_finev[1024 EXT_STRUCT_CTRL(bplast_tamex4time_fine)] /* [0,65535] */;
  uint32_t bplast_tamex4time_edge /* [0,1024] */;
  uint32_t bplast_tamex4time_edgev[1024 EXT_STRUCT_CTRL(bplast_tamex4time_edge)] /* [0,65535] */;
  uint32_t bplast_tamex4time_channel /* [0,1024] */;
  uint32_t bplast_tamex4time_channelv[1024 EXT_STRUCT_CTRL(bplast_tamex4time_channel)] /* [0,65535] */;
  uint32_t bplast_tamex4time_epoch /* [0,1024] */;
  uint32_t bplast_tamex4time_epochv[1024 EXT_STRUCT_CTRL(bplast_tamex4time_epoch)] /* [-1,-1] */;
  uint32_t bplast_tamex5event_size /* [-1,-1] */;
  uint32_t bplast_tamex5time_coarse /* [0,1024] */;
  uint32_t bplast_tamex5time_coarsev[1024 EXT_STRUCT_CTRL(bplast_tamex5time_coarse)] /* [0,65535] */;
  uint32_t bplast_tamex5time_fine /* [0,1024] */;
  uint32_t bplast_tamex5time_finev[1024 EXT_STRUCT_CTRL(bplast_tamex5time_fine)] /* [0,65535] */;
  uint32_t bplast_tamex5time_edge /* [0,1024] */;
  uint32_t bplast_tamex5time_edgev[1024 EXT_STRUCT_CTRL(bplast_tamex5time_edge)] /* [0,65535] */;
  uint32_t bplast_tamex5time_channel /* [0,1024] */;
  uint32_t bplast_tamex5time_channelv[1024 EXT_STRUCT_CTRL(bplast_tamex5time_channel)] /* [0,65535] */;
  uint32_t bplast_tamex5time_epoch /* [0,1024] */;
  uint32_t bplast_tamex5time_epochv[1024 EXT_STRUCT_CTRL(bplast_tamex5time_epoch)] /* [-1,-1] */;
  uint32_t bplast_ts_subsystem_id /* [0,65535] */;
  uint32_t bplast_ts_t1 /* [0,65535] */;
  uint32_t bplast_ts_t2 /* [0,65535] */;
  uint32_t bplast_ts_t3 /* [0,65535] */;
  uint32_t bplast_ts_t4 /* [0,65535] */;
  uint32_t bplast_trigger_window_post_trig_ns /* [0,64] */;
  uint32_t bplast_trigger_window_post_trig_nsv[64 EXT_STRUCT_CTRL(bplast_trigger_window_post_trig_ns)] /* [0,65535] */;
  uint32_t bplast_trigger_window_pre_trig_ns /* [0,64] */;
  uint32_t bplast_trigger_window_pre_trig_nsv[64 EXT_STRUCT_CTRL(bplast_trigger_window_pre_trig_ns)] /* [0,65535] */;

} EXT_STR_h101_bplast;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_bplast_onion_t
{
  /* UNPACK */
  struct {
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
  } bplast_tamex[5];
  uint32_t bplast_ts_subsystem_id;
  uint32_t bplast_ts_t[4];
  uint32_t bplast_trigger_window_post_trig_ns;
  uint32_t bplast_trigger_window_post_trig_nsv[64 /* bplast_trigger_window_post_trig_ns */];
  uint32_t bplast_trigger_window_pre_trig_ns;
  uint32_t bplast_trigger_window_pre_trig_nsv[64 /* bplast_trigger_window_pre_trig_ns */];

} EXT_STR_h101_bplast_onion;

/*******************************************************/

#define EXT_STR_h101_bplast_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bplast_tamex1event_size,         UINT32,\
                    "bplast_tamex1event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_coarse,        UINT32,\
                    "bplast_tamex1time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_coarsev,       UINT32,\
                    "bplast_tamex1time_coarsev",       "bplast_tamex1time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_fine,          UINT32,\
                    "bplast_tamex1time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_finev,         UINT32,\
                    "bplast_tamex1time_finev",         "bplast_tamex1time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_edge,          UINT32,\
                    "bplast_tamex1time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_edgev,         UINT32,\
                    "bplast_tamex1time_edgev",         "bplast_tamex1time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_channel,       UINT32,\
                    "bplast_tamex1time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_channelv,      UINT32,\
                    "bplast_tamex1time_channelv",      "bplast_tamex1time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_epoch,         UINT32,\
                    "bplast_tamex1time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_epochv,        UINT32,\
                    "bplast_tamex1time_epochv",        "bplast_tamex1time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bplast_tamex2event_size,         UINT32,\
                    "bplast_tamex2event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_coarse,        UINT32,\
                    "bplast_tamex2time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_coarsev,       UINT32,\
                    "bplast_tamex2time_coarsev",       "bplast_tamex2time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_fine,          UINT32,\
                    "bplast_tamex2time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_finev,         UINT32,\
                    "bplast_tamex2time_finev",         "bplast_tamex2time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_edge,          UINT32,\
                    "bplast_tamex2time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_edgev,         UINT32,\
                    "bplast_tamex2time_edgev",         "bplast_tamex2time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_channel,       UINT32,\
                    "bplast_tamex2time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_channelv,      UINT32,\
                    "bplast_tamex2time_channelv",      "bplast_tamex2time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_epoch,         UINT32,\
                    "bplast_tamex2time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_epochv,        UINT32,\
                    "bplast_tamex2time_epochv",        "bplast_tamex2time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bplast_tamex3event_size,         UINT32,\
                    "bplast_tamex3event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_coarse,        UINT32,\
                    "bplast_tamex3time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_coarsev,       UINT32,\
                    "bplast_tamex3time_coarsev",       "bplast_tamex3time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_fine,          UINT32,\
                    "bplast_tamex3time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_finev,         UINT32,\
                    "bplast_tamex3time_finev",         "bplast_tamex3time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_edge,          UINT32,\
                    "bplast_tamex3time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_edgev,         UINT32,\
                    "bplast_tamex3time_edgev",         "bplast_tamex3time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_channel,       UINT32,\
                    "bplast_tamex3time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_channelv,      UINT32,\
                    "bplast_tamex3time_channelv",      "bplast_tamex3time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_epoch,         UINT32,\
                    "bplast_tamex3time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_epochv,        UINT32,\
                    "bplast_tamex3time_epochv",        "bplast_tamex3time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bplast_tamex4event_size,         UINT32,\
                    "bplast_tamex4event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex4time_coarse,        UINT32,\
                    "bplast_tamex4time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex4time_coarsev,       UINT32,\
                    "bplast_tamex4time_coarsev",       "bplast_tamex4time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex4time_fine,          UINT32,\
                    "bplast_tamex4time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex4time_finev,         UINT32,\
                    "bplast_tamex4time_finev",         "bplast_tamex4time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex4time_edge,          UINT32,\
                    "bplast_tamex4time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex4time_edgev,         UINT32,\
                    "bplast_tamex4time_edgev",         "bplast_tamex4time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex4time_channel,       UINT32,\
                    "bplast_tamex4time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex4time_channelv,      UINT32,\
                    "bplast_tamex4time_channelv",      "bplast_tamex4time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex4time_epoch,         UINT32,\
                    "bplast_tamex4time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex4time_epochv,        UINT32,\
                    "bplast_tamex4time_epochv",        "bplast_tamex4time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bplast_tamex5event_size,         UINT32,\
                    "bplast_tamex5event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex5time_coarse,        UINT32,\
                    "bplast_tamex5time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex5time_coarsev,       UINT32,\
                    "bplast_tamex5time_coarsev",       "bplast_tamex5time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex5time_fine,          UINT32,\
                    "bplast_tamex5time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex5time_finev,         UINT32,\
                    "bplast_tamex5time_finev",         "bplast_tamex5time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex5time_edge,          UINT32,\
                    "bplast_tamex5time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex5time_edgev,         UINT32,\
                    "bplast_tamex5time_edgev",         "bplast_tamex5time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex5time_channel,       UINT32,\
                    "bplast_tamex5time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex5time_channelv,      UINT32,\
                    "bplast_tamex5time_channelv",      "bplast_tamex5time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex5time_epoch,         UINT32,\
                    "bplast_tamex5time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex5time_epochv,        UINT32,\
                    "bplast_tamex5time_epochv",        "bplast_tamex5time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_ts_subsystem_id,          UINT32,\
                    "bplast_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_ts_t1,                    UINT32,\
                    "bplast_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_ts_t2,                    UINT32,\
                    "bplast_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_ts_t3,                    UINT32,\
                    "bplast_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_ts_t4,                    UINT32,\
                    "bplast_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_trigger_window_post_trig_ns,UINT32,\
                    "bplast_trigger_window_post_trig_ns",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_trigger_window_post_trig_nsv,UINT32,\
                    "bplast_trigger_window_post_trig_nsv","bplast_trigger_window_post_trig_ns",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_trigger_window_pre_trig_ns,UINT32,\
                    "bplast_trigger_window_pre_trig_ns",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_trigger_window_pre_trig_nsv,UINT32,\
                    "bplast_trigger_window_pre_trig_nsv","bplast_trigger_window_pre_trig_ns",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_BPLAST_EXT_H101_BPLAST_H__*/

/*******************************************************/
