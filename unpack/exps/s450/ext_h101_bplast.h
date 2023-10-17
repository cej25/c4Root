/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_EXT_H101_BPLAST_H__
#define __GUARD_H101_EXT_H101_BPLAST_H__

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

typedef struct EXT_STR_h101_t
{
  /* INFO */
  uint32_t TRIGGER /* [0,15] */;
  uint32_t EVENTNO /* [-1,-1] */;
  /* UNPACK */
  uint32_t plastic_tamex1event_size /* [-1,-1] */;
  uint32_t plastic_tamex1time_coarse /* [0,512] */;
  uint32_t plastic_tamex1time_coarsev[512 EXT_STRUCT_CTRL(plastic_tamex1time_coarse)] /* [0,65535] */;
  uint32_t plastic_tamex1time_fine /* [0,512] */;
  uint32_t plastic_tamex1time_finev[512 EXT_STRUCT_CTRL(plastic_tamex1time_fine)] /* [0,65535] */;
  uint32_t plastic_tamex1time_edge /* [0,512] */;
  uint32_t plastic_tamex1time_edgev[512 EXT_STRUCT_CTRL(plastic_tamex1time_edge)] /* [0,65535] */;
  uint32_t plastic_tamex1time_channel /* [0,512] */;
  uint32_t plastic_tamex1time_channelv[512 EXT_STRUCT_CTRL(plastic_tamex1time_channel)] /* [0,65535] */;
  uint32_t plastic_tamex1time_epoch /* [0,512] */;
  uint32_t plastic_tamex1time_epochv[512 EXT_STRUCT_CTRL(plastic_tamex1time_epoch)] /* [-1,-1] */;
  uint32_t plastic_tamex2event_size /* [-1,-1] */;
  uint32_t plastic_tamex2time_coarse /* [0,512] */;
  uint32_t plastic_tamex2time_coarsev[512 EXT_STRUCT_CTRL(plastic_tamex2time_coarse)] /* [0,65535] */;
  uint32_t plastic_tamex2time_fine /* [0,512] */;
  uint32_t plastic_tamex2time_finev[512 EXT_STRUCT_CTRL(plastic_tamex2time_fine)] /* [0,65535] */;
  uint32_t plastic_tamex2time_edge /* [0,512] */;
  uint32_t plastic_tamex2time_edgev[512 EXT_STRUCT_CTRL(plastic_tamex2time_edge)] /* [0,65535] */;
  uint32_t plastic_tamex2time_channel /* [0,512] */;
  uint32_t plastic_tamex2time_channelv[512 EXT_STRUCT_CTRL(plastic_tamex2time_channel)] /* [0,65535] */;
  uint32_t plastic_tamex2time_epoch /* [0,512] */;
  uint32_t plastic_tamex2time_epochv[512 EXT_STRUCT_CTRL(plastic_tamex2time_epoch)] /* [-1,-1] */;
  uint32_t plastic_tamex3event_size /* [-1,-1] */;
  uint32_t plastic_tamex3time_coarse /* [0,512] */;
  uint32_t plastic_tamex3time_coarsev[512 EXT_STRUCT_CTRL(plastic_tamex3time_coarse)] /* [0,65535] */;
  uint32_t plastic_tamex3time_fine /* [0,512] */;
  uint32_t plastic_tamex3time_finev[512 EXT_STRUCT_CTRL(plastic_tamex3time_fine)] /* [0,65535] */;
  uint32_t plastic_tamex3time_edge /* [0,512] */;
  uint32_t plastic_tamex3time_edgev[512 EXT_STRUCT_CTRL(plastic_tamex3time_edge)] /* [0,65535] */;
  uint32_t plastic_tamex3time_channel /* [0,512] */;
  uint32_t plastic_tamex3time_channelv[512 EXT_STRUCT_CTRL(plastic_tamex3time_channel)] /* [0,65535] */;
  uint32_t plastic_tamex3time_epoch /* [0,512] */;
  uint32_t plastic_tamex3time_epochv[512 EXT_STRUCT_CTRL(plastic_tamex3time_epoch)] /* [-1,-1] */;
  uint32_t plastic_tamex4event_size /* [-1,-1] */;
  uint32_t plastic_tamex4time_coarse /* [0,512] */;
  uint32_t plastic_tamex4time_coarsev[512 EXT_STRUCT_CTRL(plastic_tamex4time_coarse)] /* [0,65535] */;
  uint32_t plastic_tamex4time_fine /* [0,512] */;
  uint32_t plastic_tamex4time_finev[512 EXT_STRUCT_CTRL(plastic_tamex4time_fine)] /* [0,65535] */;
  uint32_t plastic_tamex4time_edge /* [0,512] */;
  uint32_t plastic_tamex4time_edgev[512 EXT_STRUCT_CTRL(plastic_tamex4time_edge)] /* [0,65535] */;
  uint32_t plastic_tamex4time_channel /* [0,512] */;
  uint32_t plastic_tamex4time_channelv[512 EXT_STRUCT_CTRL(plastic_tamex4time_channel)] /* [0,65535] */;
  uint32_t plastic_tamex4time_epoch /* [0,512] */;
  uint32_t plastic_tamex4time_epochv[512 EXT_STRUCT_CTRL(plastic_tamex4time_epoch)] /* [-1,-1] */;
  uint32_t plastic_tamex5event_size /* [-1,-1] */;
  uint32_t plastic_tamex5time_coarse /* [0,512] */;
  uint32_t plastic_tamex5time_coarsev[512 EXT_STRUCT_CTRL(plastic_tamex5time_coarse)] /* [0,65535] */;
  uint32_t plastic_tamex5time_fine /* [0,512] */;
  uint32_t plastic_tamex5time_finev[512 EXT_STRUCT_CTRL(plastic_tamex5time_fine)] /* [0,65535] */;
  uint32_t plastic_tamex5time_edge /* [0,512] */;
  uint32_t plastic_tamex5time_edgev[512 EXT_STRUCT_CTRL(plastic_tamex5time_edge)] /* [0,65535] */;
  uint32_t plastic_tamex5time_channel /* [0,512] */;
  uint32_t plastic_tamex5time_channelv[512 EXT_STRUCT_CTRL(plastic_tamex5time_channel)] /* [0,65535] */;
  uint32_t plastic_tamex5time_epoch /* [0,512] */;
  uint32_t plastic_tamex5time_epochv[512 EXT_STRUCT_CTRL(plastic_tamex5time_epoch)] /* [-1,-1] */;
  uint32_t plastic_tamex6event_size /* [-1,-1] */;
  uint32_t plastic_tamex6time_coarse /* [0,512] */;
  uint32_t plastic_tamex6time_coarsev[512 EXT_STRUCT_CTRL(plastic_tamex6time_coarse)] /* [0,65535] */;
  uint32_t plastic_tamex6time_fine /* [0,512] */;
  uint32_t plastic_tamex6time_finev[512 EXT_STRUCT_CTRL(plastic_tamex6time_fine)] /* [0,65535] */;
  uint32_t plastic_tamex6time_edge /* [0,512] */;
  uint32_t plastic_tamex6time_edgev[512 EXT_STRUCT_CTRL(plastic_tamex6time_edge)] /* [0,65535] */;
  uint32_t plastic_tamex6time_channel /* [0,512] */;
  uint32_t plastic_tamex6time_channelv[512 EXT_STRUCT_CTRL(plastic_tamex6time_channel)] /* [0,65535] */;
  uint32_t plastic_tamex6time_epoch /* [0,512] */;
  uint32_t plastic_tamex6time_epochv[512 EXT_STRUCT_CTRL(plastic_tamex6time_epoch)] /* [-1,-1] */;
  uint32_t plastic_tamex7event_size /* [-1,-1] */;
  uint32_t plastic_tamex7time_coarse /* [0,512] */;
  uint32_t plastic_tamex7time_coarsev[512 EXT_STRUCT_CTRL(plastic_tamex7time_coarse)] /* [0,65535] */;
  uint32_t plastic_tamex7time_fine /* [0,512] */;
  uint32_t plastic_tamex7time_finev[512 EXT_STRUCT_CTRL(plastic_tamex7time_fine)] /* [0,65535] */;
  uint32_t plastic_tamex7time_edge /* [0,512] */;
  uint32_t plastic_tamex7time_edgev[512 EXT_STRUCT_CTRL(plastic_tamex7time_edge)] /* [0,65535] */;
  uint32_t plastic_tamex7time_channel /* [0,512] */;
  uint32_t plastic_tamex7time_channelv[512 EXT_STRUCT_CTRL(plastic_tamex7time_channel)] /* [0,65535] */;
  uint32_t plastic_tamex7time_epoch /* [0,512] */;
  uint32_t plastic_tamex7time_epochv[512 EXT_STRUCT_CTRL(plastic_tamex7time_epoch)] /* [-1,-1] */;
  uint32_t plastic_tamex8event_size /* [-1,-1] */;
  uint32_t plastic_tamex8time_coarse /* [0,512] */;
  uint32_t plastic_tamex8time_coarsev[512 EXT_STRUCT_CTRL(plastic_tamex8time_coarse)] /* [0,65535] */;
  uint32_t plastic_tamex8time_fine /* [0,512] */;
  uint32_t plastic_tamex8time_finev[512 EXT_STRUCT_CTRL(plastic_tamex8time_fine)] /* [0,65535] */;
  uint32_t plastic_tamex8time_edge /* [0,512] */;
  uint32_t plastic_tamex8time_edgev[512 EXT_STRUCT_CTRL(plastic_tamex8time_edge)] /* [0,65535] */;
  uint32_t plastic_tamex8time_channel /* [0,512] */;
  uint32_t plastic_tamex8time_channelv[512 EXT_STRUCT_CTRL(plastic_tamex8time_channel)] /* [0,65535] */;
  uint32_t plastic_tamex8time_epoch /* [0,512] */;
  uint32_t plastic_tamex8time_epochv[512 EXT_STRUCT_CTRL(plastic_tamex8time_epoch)] /* [-1,-1] */;
  uint32_t plastic_tamex9event_size /* [-1,-1] */;
  uint32_t plastic_tamex9time_coarse /* [0,512] */;
  uint32_t plastic_tamex9time_coarsev[512 EXT_STRUCT_CTRL(plastic_tamex9time_coarse)] /* [0,65535] */;
  uint32_t plastic_tamex9time_fine /* [0,512] */;
  uint32_t plastic_tamex9time_finev[512 EXT_STRUCT_CTRL(plastic_tamex9time_fine)] /* [0,65535] */;
  uint32_t plastic_tamex9time_edge /* [0,512] */;
  uint32_t plastic_tamex9time_edgev[512 EXT_STRUCT_CTRL(plastic_tamex9time_edge)] /* [0,65535] */;
  uint32_t plastic_tamex9time_channel /* [0,512] */;
  uint32_t plastic_tamex9time_channelv[512 EXT_STRUCT_CTRL(plastic_tamex9time_channel)] /* [0,65535] */;
  uint32_t plastic_tamex9time_epoch /* [0,512] */;
  uint32_t plastic_tamex9time_epochv[512 EXT_STRUCT_CTRL(plastic_tamex9time_epoch)] /* [-1,-1] */;
  uint32_t plastic_ts_subsystem_id /* [0,65535] */;
  uint32_t plastic_ts_t1 /* [0,65535] */;
  uint32_t plastic_ts_t2 /* [0,65535] */;
  uint32_t plastic_ts_t3 /* [0,65535] */;
  uint32_t plastic_ts_t4 /* [0,65535] */;
  uint32_t plastic_trigger_window_post_trig_ns /* [0,64] */;
  uint32_t plastic_trigger_window_post_trig_nsv[64 EXT_STRUCT_CTRL(plastic_trigger_window_post_trig_ns)] /* [0,65535] */;
  uint32_t plastic_trigger_window_pre_trig_ns /* [0,64] */;
  uint32_t plastic_trigger_window_pre_trig_nsv[64 EXT_STRUCT_CTRL(plastic_trigger_window_pre_trig_ns)] /* [0,65535] */;

} EXT_STR_h101;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_onion_t
{
  /* INFO */
  uint32_t TRIGGER;
  uint32_t EVENTNO;
  /* UNPACK */
  struct {
    uint32_t event_size;
    uint32_t time_coarse;
    uint32_t time_coarsev[512 /* time_coarse */];
    uint32_t time_fine;
    uint32_t time_finev[512 /* time_fine */];
    uint32_t time_edge;
    uint32_t time_edgev[512 /* time_edge */];
    uint32_t time_channel;
    uint32_t time_channelv[512 /* time_channel */];
    uint32_t time_epoch;
    uint32_t time_epochv[512 /* time_epoch */];
  } plastic_tamex[9];
  uint32_t plastic_ts_subsystem_id;
  uint32_t plastic_ts_t[4];
  uint32_t plastic_trigger_window_post_trig_ns;
  uint32_t plastic_trigger_window_post_trig_nsv[64 /* plastic_trigger_window_post_trig_ns */];
  uint32_t plastic_trigger_window_pre_trig_ns;
  uint32_t plastic_trigger_window_pre_trig_nsv[64 /* plastic_trigger_window_pre_trig_ns */];

} EXT_STR_h101_onion;

/*******************************************************/

#define EXT_STR_h101_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* INFO */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TRIGGER,                         UINT32,\
                    "TRIGGER",15,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     EVENTNO,                         UINT32,\
                    "EVENTNO",0/*flags*/); \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     plastic_tamex1event_size,        UINT32,\
                    "plastic_tamex1event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex1time_coarse,       UINT32,\
                    "plastic_tamex1time_coarse",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex1time_coarsev,      UINT32,\
                    "plastic_tamex1time_coarsev",      "plastic_tamex1time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex1time_fine,         UINT32,\
                    "plastic_tamex1time_fine",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex1time_finev,        UINT32,\
                    "plastic_tamex1time_finev",        "plastic_tamex1time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex1time_edge,         UINT32,\
                    "plastic_tamex1time_edge",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex1time_edgev,        UINT32,\
                    "plastic_tamex1time_edgev",        "plastic_tamex1time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex1time_channel,      UINT32,\
                    "plastic_tamex1time_channel",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex1time_channelv,     UINT32,\
                    "plastic_tamex1time_channelv",     "plastic_tamex1time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex1time_epoch,        UINT32,\
                    "plastic_tamex1time_epoch",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex1time_epochv,       UINT32,\
                    "plastic_tamex1time_epochv",       "plastic_tamex1time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     plastic_tamex2event_size,        UINT32,\
                    "plastic_tamex2event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex2time_coarse,       UINT32,\
                    "plastic_tamex2time_coarse",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex2time_coarsev,      UINT32,\
                    "plastic_tamex2time_coarsev",      "plastic_tamex2time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex2time_fine,         UINT32,\
                    "plastic_tamex2time_fine",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex2time_finev,        UINT32,\
                    "plastic_tamex2time_finev",        "plastic_tamex2time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex2time_edge,         UINT32,\
                    "plastic_tamex2time_edge",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex2time_edgev,        UINT32,\
                    "plastic_tamex2time_edgev",        "plastic_tamex2time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex2time_channel,      UINT32,\
                    "plastic_tamex2time_channel",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex2time_channelv,     UINT32,\
                    "plastic_tamex2time_channelv",     "plastic_tamex2time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex2time_epoch,        UINT32,\
                    "plastic_tamex2time_epoch",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex2time_epochv,       UINT32,\
                    "plastic_tamex2time_epochv",       "plastic_tamex2time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     plastic_tamex3event_size,        UINT32,\
                    "plastic_tamex3event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex3time_coarse,       UINT32,\
                    "plastic_tamex3time_coarse",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex3time_coarsev,      UINT32,\
                    "plastic_tamex3time_coarsev",      "plastic_tamex3time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex3time_fine,         UINT32,\
                    "plastic_tamex3time_fine",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex3time_finev,        UINT32,\
                    "plastic_tamex3time_finev",        "plastic_tamex3time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex3time_edge,         UINT32,\
                    "plastic_tamex3time_edge",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex3time_edgev,        UINT32,\
                    "plastic_tamex3time_edgev",        "plastic_tamex3time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex3time_channel,      UINT32,\
                    "plastic_tamex3time_channel",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex3time_channelv,     UINT32,\
                    "plastic_tamex3time_channelv",     "plastic_tamex3time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex3time_epoch,        UINT32,\
                    "plastic_tamex3time_epoch",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex3time_epochv,       UINT32,\
                    "plastic_tamex3time_epochv",       "plastic_tamex3time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     plastic_tamex4event_size,        UINT32,\
                    "plastic_tamex4event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex4time_coarse,       UINT32,\
                    "plastic_tamex4time_coarse",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex4time_coarsev,      UINT32,\
                    "plastic_tamex4time_coarsev",      "plastic_tamex4time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex4time_fine,         UINT32,\
                    "plastic_tamex4time_fine",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex4time_finev,        UINT32,\
                    "plastic_tamex4time_finev",        "plastic_tamex4time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex4time_edge,         UINT32,\
                    "plastic_tamex4time_edge",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex4time_edgev,        UINT32,\
                    "plastic_tamex4time_edgev",        "plastic_tamex4time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex4time_channel,      UINT32,\
                    "plastic_tamex4time_channel",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex4time_channelv,     UINT32,\
                    "plastic_tamex4time_channelv",     "plastic_tamex4time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex4time_epoch,        UINT32,\
                    "plastic_tamex4time_epoch",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex4time_epochv,       UINT32,\
                    "plastic_tamex4time_epochv",       "plastic_tamex4time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     plastic_tamex5event_size,        UINT32,\
                    "plastic_tamex5event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex5time_coarse,       UINT32,\
                    "plastic_tamex5time_coarse",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex5time_coarsev,      UINT32,\
                    "plastic_tamex5time_coarsev",      "plastic_tamex5time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex5time_fine,         UINT32,\
                    "plastic_tamex5time_fine",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex5time_finev,        UINT32,\
                    "plastic_tamex5time_finev",        "plastic_tamex5time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex5time_edge,         UINT32,\
                    "plastic_tamex5time_edge",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex5time_edgev,        UINT32,\
                    "plastic_tamex5time_edgev",        "plastic_tamex5time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex5time_channel,      UINT32,\
                    "plastic_tamex5time_channel",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex5time_channelv,     UINT32,\
                    "plastic_tamex5time_channelv",     "plastic_tamex5time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex5time_epoch,        UINT32,\
                    "plastic_tamex5time_epoch",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex5time_epochv,       UINT32,\
                    "plastic_tamex5time_epochv",       "plastic_tamex5time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     plastic_tamex6event_size,        UINT32,\
                    "plastic_tamex6event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex6time_coarse,       UINT32,\
                    "plastic_tamex6time_coarse",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex6time_coarsev,      UINT32,\
                    "plastic_tamex6time_coarsev",      "plastic_tamex6time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex6time_fine,         UINT32,\
                    "plastic_tamex6time_fine",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex6time_finev,        UINT32,\
                    "plastic_tamex6time_finev",        "plastic_tamex6time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex6time_edge,         UINT32,\
                    "plastic_tamex6time_edge",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex6time_edgev,        UINT32,\
                    "plastic_tamex6time_edgev",        "plastic_tamex6time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex6time_channel,      UINT32,\
                    "plastic_tamex6time_channel",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex6time_channelv,     UINT32,\
                    "plastic_tamex6time_channelv",     "plastic_tamex6time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex6time_epoch,        UINT32,\
                    "plastic_tamex6time_epoch",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex6time_epochv,       UINT32,\
                    "plastic_tamex6time_epochv",       "plastic_tamex6time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     plastic_tamex7event_size,        UINT32,\
                    "plastic_tamex7event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex7time_coarse,       UINT32,\
                    "plastic_tamex7time_coarse",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex7time_coarsev,      UINT32,\
                    "plastic_tamex7time_coarsev",      "plastic_tamex7time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex7time_fine,         UINT32,\
                    "plastic_tamex7time_fine",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex7time_finev,        UINT32,\
                    "plastic_tamex7time_finev",        "plastic_tamex7time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex7time_edge,         UINT32,\
                    "plastic_tamex7time_edge",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex7time_edgev,        UINT32,\
                    "plastic_tamex7time_edgev",        "plastic_tamex7time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex7time_channel,      UINT32,\
                    "plastic_tamex7time_channel",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex7time_channelv,     UINT32,\
                    "plastic_tamex7time_channelv",     "plastic_tamex7time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex7time_epoch,        UINT32,\
                    "plastic_tamex7time_epoch",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex7time_epochv,       UINT32,\
                    "plastic_tamex7time_epochv",       "plastic_tamex7time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     plastic_tamex8event_size,        UINT32,\
                    "plastic_tamex8event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex8time_coarse,       UINT32,\
                    "plastic_tamex8time_coarse",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex8time_coarsev,      UINT32,\
                    "plastic_tamex8time_coarsev",      "plastic_tamex8time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex8time_fine,         UINT32,\
                    "plastic_tamex8time_fine",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex8time_finev,        UINT32,\
                    "plastic_tamex8time_finev",        "plastic_tamex8time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex8time_edge,         UINT32,\
                    "plastic_tamex8time_edge",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex8time_edgev,        UINT32,\
                    "plastic_tamex8time_edgev",        "plastic_tamex8time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex8time_channel,      UINT32,\
                    "plastic_tamex8time_channel",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex8time_channelv,     UINT32,\
                    "plastic_tamex8time_channelv",     "plastic_tamex8time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex8time_epoch,        UINT32,\
                    "plastic_tamex8time_epoch",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex8time_epochv,       UINT32,\
                    "plastic_tamex8time_epochv",       "plastic_tamex8time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     plastic_tamex9event_size,        UINT32,\
                    "plastic_tamex9event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex9time_coarse,       UINT32,\
                    "plastic_tamex9time_coarse",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex9time_coarsev,      UINT32,\
                    "plastic_tamex9time_coarsev",      "plastic_tamex9time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex9time_fine,         UINT32,\
                    "plastic_tamex9time_fine",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex9time_finev,        UINT32,\
                    "plastic_tamex9time_finev",        "plastic_tamex9time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex9time_edge,         UINT32,\
                    "plastic_tamex9time_edge",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex9time_edgev,        UINT32,\
                    "plastic_tamex9time_edgev",        "plastic_tamex9time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex9time_channel,      UINT32,\
                    "plastic_tamex9time_channel",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex9time_channelv,     UINT32,\
                    "plastic_tamex9time_channelv",     "plastic_tamex9time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_tamex9time_epoch,        UINT32,\
                    "plastic_tamex9time_epoch",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_tamex9time_epochv,       UINT32,\
                    "plastic_tamex9time_epochv",       "plastic_tamex9time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_ts_subsystem_id,         UINT32,\
                    "plastic_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_ts_t1,                   UINT32,\
                    "plastic_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_ts_t2,                   UINT32,\
                    "plastic_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_ts_t3,                   UINT32,\
                    "plastic_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_ts_t4,                   UINT32,\
                    "plastic_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_trigger_window_post_trig_ns,UINT32,\
                    "plastic_trigger_window_post_trig_ns",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_trigger_window_post_trig_nsv,UINT32,\
                    "plastic_trigger_window_post_trig_nsv","plastic_trigger_window_post_trig_ns",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     plastic_trigger_window_pre_trig_ns,UINT32,\
                    "plastic_trigger_window_pre_trig_ns",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     plastic_trigger_window_pre_trig_nsv,UINT32,\
                    "plastic_trigger_window_pre_trig_nsv","plastic_trigger_window_pre_trig_ns",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_EXT_H101_BPLAST_H__*/

/*******************************************************/
