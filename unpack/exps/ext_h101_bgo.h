/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_BGO_EXT_H101_BGO_H__
#define __GUARD_H101_BGO_EXT_H101_BGO_H__

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

typedef struct EXT_STR_h101_bgo_t
{
  /* UNPACK */
  uint32_t bgo_ts_subsystem_id /* [0,65535] */;
  uint32_t bgo_ts_t1 /* [0,65535] */;
  uint32_t bgo_ts_t2 /* [0,65535] */;
  uint32_t bgo_ts_t3 /* [0,65535] */;
  uint32_t bgo_ts_t4 /* [0,65535] */;
  uint32_t bgo_be /* [-1,-1] */;
  uint32_t bgo_trigger_window_post_trig_ns /* [0,65535] */;
  uint32_t bgo_trigger_window_pre_trig_ns /* [0,65535] */;
  uint32_t bgo_tamex1trig /* [0,255] */;
  uint32_t bgo_tamex1event_size /* [-1,-1] */;
  uint32_t bgo_tamex1time_coarse /* [0,1024] */;
  uint32_t bgo_tamex1time_coarsev[1024 EXT_STRUCT_CTRL(bgo_tamex1time_coarse)] /* [0,65535] */;
  uint32_t bgo_tamex1time_fine /* [0,1024] */;
  uint32_t bgo_tamex1time_finev[1024 EXT_STRUCT_CTRL(bgo_tamex1time_fine)] /* [0,65535] */;
  uint32_t bgo_tamex1time_edge /* [0,1024] */;
  uint32_t bgo_tamex1time_edgev[1024 EXT_STRUCT_CTRL(bgo_tamex1time_edge)] /* [0,65535] */;
  uint32_t bgo_tamex1time_channel /* [0,1024] */;
  uint32_t bgo_tamex1time_channelv[1024 EXT_STRUCT_CTRL(bgo_tamex1time_channel)] /* [0,65535] */;
  uint32_t bgo_tamex1time_epoch /* [0,1024] */;
  uint32_t bgo_tamex1time_epochv[1024 EXT_STRUCT_CTRL(bgo_tamex1time_epoch)] /* [-1,-1] */;
  uint32_t bgo_tamex2trig /* [0,255] */;
  uint32_t bgo_tamex2event_size /* [-1,-1] */;
  uint32_t bgo_tamex2time_coarse /* [0,1024] */;
  uint32_t bgo_tamex2time_coarsev[1024 EXT_STRUCT_CTRL(bgo_tamex2time_coarse)] /* [0,65535] */;
  uint32_t bgo_tamex2time_fine /* [0,1024] */;
  uint32_t bgo_tamex2time_finev[1024 EXT_STRUCT_CTRL(bgo_tamex2time_fine)] /* [0,65535] */;
  uint32_t bgo_tamex2time_edge /* [0,1024] */;
  uint32_t bgo_tamex2time_edgev[1024 EXT_STRUCT_CTRL(bgo_tamex2time_edge)] /* [0,65535] */;
  uint32_t bgo_tamex2time_channel /* [0,1024] */;
  uint32_t bgo_tamex2time_channelv[1024 EXT_STRUCT_CTRL(bgo_tamex2time_channel)] /* [0,65535] */;
  uint32_t bgo_tamex2time_epoch /* [0,1024] */;
  uint32_t bgo_tamex2time_epochv[1024 EXT_STRUCT_CTRL(bgo_tamex2time_epoch)] /* [-1,-1] */;
  uint32_t bgo_tamex3trig /* [0,255] */;
  uint32_t bgo_tamex3event_size /* [-1,-1] */;
  uint32_t bgo_tamex3time_coarse /* [0,1024] */;
  uint32_t bgo_tamex3time_coarsev[1024 EXT_STRUCT_CTRL(bgo_tamex3time_coarse)] /* [0,65535] */;
  uint32_t bgo_tamex3time_fine /* [0,1024] */;
  uint32_t bgo_tamex3time_finev[1024 EXT_STRUCT_CTRL(bgo_tamex3time_fine)] /* [0,65535] */;
  uint32_t bgo_tamex3time_edge /* [0,1024] */;
  uint32_t bgo_tamex3time_edgev[1024 EXT_STRUCT_CTRL(bgo_tamex3time_edge)] /* [0,65535] */;
  uint32_t bgo_tamex3time_channel /* [0,1024] */;
  uint32_t bgo_tamex3time_channelv[1024 EXT_STRUCT_CTRL(bgo_tamex3time_channel)] /* [0,65535] */;
  uint32_t bgo_tamex3time_epoch /* [0,1024] */;
  uint32_t bgo_tamex3time_epochv[1024 EXT_STRUCT_CTRL(bgo_tamex3time_epoch)] /* [-1,-1] */;

} EXT_STR_h101_bgo;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_bgo_onion_t
{
  /* UNPACK */
  uint32_t bgo_ts_subsystem_id;
  uint32_t bgo_ts_t[4];
  uint32_t bgo_be;
  uint32_t bgo_trigger_window_post_trig_ns;
  uint32_t bgo_trigger_window_pre_trig_ns;
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
  } bgo_tamex[3];

} EXT_STR_h101_bgo_onion;

/*******************************************************/

#define EXT_STR_h101_bgo_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_ts_subsystem_id,             UINT32,\
                    "bgo_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_ts_t1,                       UINT32,\
                    "bgo_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_ts_t2,                       UINT32,\
                    "bgo_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_ts_t3,                       UINT32,\
                    "bgo_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_ts_t4,                       UINT32,\
                    "bgo_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bgo_be,                          UINT32,\
                    "bgo_be",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_trigger_window_post_trig_ns, UINT32,\
                    "bgo_trigger_window_post_trig_ns",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_trigger_window_pre_trig_ns,  UINT32,\
                    "bgo_trigger_window_pre_trig_ns",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex1trig,                  UINT32,\
                    "bgo_tamex1trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bgo_tamex1event_size,            UINT32,\
                    "bgo_tamex1event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex1time_coarse,           UINT32,\
                    "bgo_tamex1time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex1time_coarsev,          UINT32,\
                    "bgo_tamex1time_coarsev",          "bgo_tamex1time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex1time_fine,             UINT32,\
                    "bgo_tamex1time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex1time_finev,            UINT32,\
                    "bgo_tamex1time_finev",            "bgo_tamex1time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex1time_edge,             UINT32,\
                    "bgo_tamex1time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex1time_edgev,            UINT32,\
                    "bgo_tamex1time_edgev",            "bgo_tamex1time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex1time_channel,          UINT32,\
                    "bgo_tamex1time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex1time_channelv,         UINT32,\
                    "bgo_tamex1time_channelv",         "bgo_tamex1time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex1time_epoch,            UINT32,\
                    "bgo_tamex1time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex1time_epochv,           UINT32,\
                    "bgo_tamex1time_epochv",           "bgo_tamex1time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex2trig,                  UINT32,\
                    "bgo_tamex2trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bgo_tamex2event_size,            UINT32,\
                    "bgo_tamex2event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex2time_coarse,           UINT32,\
                    "bgo_tamex2time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex2time_coarsev,          UINT32,\
                    "bgo_tamex2time_coarsev",          "bgo_tamex2time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex2time_fine,             UINT32,\
                    "bgo_tamex2time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex2time_finev,            UINT32,\
                    "bgo_tamex2time_finev",            "bgo_tamex2time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex2time_edge,             UINT32,\
                    "bgo_tamex2time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex2time_edgev,            UINT32,\
                    "bgo_tamex2time_edgev",            "bgo_tamex2time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex2time_channel,          UINT32,\
                    "bgo_tamex2time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex2time_channelv,         UINT32,\
                    "bgo_tamex2time_channelv",         "bgo_tamex2time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex2time_epoch,            UINT32,\
                    "bgo_tamex2time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex2time_epochv,           UINT32,\
                    "bgo_tamex2time_epochv",           "bgo_tamex2time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex3trig,                  UINT32,\
                    "bgo_tamex3trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bgo_tamex3event_size,            UINT32,\
                    "bgo_tamex3event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex3time_coarse,           UINT32,\
                    "bgo_tamex3time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex3time_coarsev,          UINT32,\
                    "bgo_tamex3time_coarsev",          "bgo_tamex3time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex3time_fine,             UINT32,\
                    "bgo_tamex3time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex3time_finev,            UINT32,\
                    "bgo_tamex3time_finev",            "bgo_tamex3time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex3time_edge,             UINT32,\
                    "bgo_tamex3time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex3time_edgev,            UINT32,\
                    "bgo_tamex3time_edgev",            "bgo_tamex3time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex3time_channel,          UINT32,\
                    "bgo_tamex3time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex3time_channelv,         UINT32,\
                    "bgo_tamex3time_channelv",         "bgo_tamex3time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bgo_tamex3time_epoch,            UINT32,\
                    "bgo_tamex3time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bgo_tamex3time_epochv,           UINT32,\
                    "bgo_tamex3time_epochv",           "bgo_tamex3time_epoch",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_BGO_EXT_H101_BGO_H__*/

/*******************************************************/
