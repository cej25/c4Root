/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_FATIMA_EXT_H101_FATIMA_H__
#define __GUARD_H101_FATIMA_EXT_H101_FATIMA_H__

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

typedef struct EXT_STR_h101_fatima_t
{
  /* UNPACK */
  uint32_t fatima_ts_subsystem_id /* [0,65535] */;
  uint32_t fatima_ts_t1 /* [0,65535] */;
  uint32_t fatima_ts_t2 /* [0,65535] */;
  uint32_t fatima_ts_t3 /* [0,65535] */;
  uint32_t fatima_ts_t4 /* [0,65535] */;
  uint32_t fatima_trigger_window_post_trig_ns /* [0,65535] */;
  uint32_t fatima_trigger_window_pre_trig_ns /* [0,65535] */;
  uint32_t fatima_tamex1event_size /* [-1,-1] */;
  uint32_t fatima_tamex1time_coarse /* [0,1024] */;
  uint32_t fatima_tamex1time_coarsev[1024 EXT_STRUCT_CTRL(fatima_tamex1time_coarse)] /* [0,65535] */;
  uint32_t fatima_tamex1time_fine /* [0,1024] */;
  uint32_t fatima_tamex1time_finev[1024 EXT_STRUCT_CTRL(fatima_tamex1time_fine)] /* [0,65535] */;
  uint32_t fatima_tamex1time_edge /* [0,1024] */;
  uint32_t fatima_tamex1time_edgev[1024 EXT_STRUCT_CTRL(fatima_tamex1time_edge)] /* [0,65535] */;
  uint32_t fatima_tamex1time_channel /* [0,1024] */;
  uint32_t fatima_tamex1time_channelv[1024 EXT_STRUCT_CTRL(fatima_tamex1time_channel)] /* [0,65535] */;
  uint32_t fatima_tamex1time_epoch /* [0,1024] */;
  uint32_t fatima_tamex1time_epochv[1024 EXT_STRUCT_CTRL(fatima_tamex1time_epoch)] /* [-1,-1] */;
  uint32_t fatima_tamex2event_size /* [-1,-1] */;
  uint32_t fatima_tamex2time_coarse /* [0,1024] */;
  uint32_t fatima_tamex2time_coarsev[1024 EXT_STRUCT_CTRL(fatima_tamex2time_coarse)] /* [0,65535] */;
  uint32_t fatima_tamex2time_fine /* [0,1024] */;
  uint32_t fatima_tamex2time_finev[1024 EXT_STRUCT_CTRL(fatima_tamex2time_fine)] /* [0,65535] */;
  uint32_t fatima_tamex2time_edge /* [0,1024] */;
  uint32_t fatima_tamex2time_edgev[1024 EXT_STRUCT_CTRL(fatima_tamex2time_edge)] /* [0,65535] */;
  uint32_t fatima_tamex2time_channel /* [0,1024] */;
  uint32_t fatima_tamex2time_channelv[1024 EXT_STRUCT_CTRL(fatima_tamex2time_channel)] /* [0,65535] */;
  uint32_t fatima_tamex2time_epoch /* [0,1024] */;
  uint32_t fatima_tamex2time_epochv[1024 EXT_STRUCT_CTRL(fatima_tamex2time_epoch)] /* [-1,-1] */;
  uint32_t fatima_tamex3event_size /* [-1,-1] */;
  uint32_t fatima_tamex3time_coarse /* [0,1024] */;
  uint32_t fatima_tamex3time_coarsev[1024 EXT_STRUCT_CTRL(fatima_tamex3time_coarse)] /* [0,65535] */;
  uint32_t fatima_tamex3time_fine /* [0,1024] */;
  uint32_t fatima_tamex3time_finev[1024 EXT_STRUCT_CTRL(fatima_tamex3time_fine)] /* [0,65535] */;
  uint32_t fatima_tamex3time_edge /* [0,1024] */;
  uint32_t fatima_tamex3time_edgev[1024 EXT_STRUCT_CTRL(fatima_tamex3time_edge)] /* [0,65535] */;
  uint32_t fatima_tamex3time_channel /* [0,1024] */;
  uint32_t fatima_tamex3time_channelv[1024 EXT_STRUCT_CTRL(fatima_tamex3time_channel)] /* [0,65535] */;
  uint32_t fatima_tamex3time_epoch /* [0,1024] */;
  uint32_t fatima_tamex3time_epochv[1024 EXT_STRUCT_CTRL(fatima_tamex3time_epoch)] /* [-1,-1] */;
  uint32_t fatima_tamex4event_size /* [-1,-1] */;
  uint32_t fatima_tamex4time_coarse /* [0,1024] */;
  uint32_t fatima_tamex4time_coarsev[1024 EXT_STRUCT_CTRL(fatima_tamex4time_coarse)] /* [0,65535] */;
  uint32_t fatima_tamex4time_fine /* [0,1024] */;
  uint32_t fatima_tamex4time_finev[1024 EXT_STRUCT_CTRL(fatima_tamex4time_fine)] /* [0,65535] */;
  uint32_t fatima_tamex4time_edge /* [0,1024] */;
  uint32_t fatima_tamex4time_edgev[1024 EXT_STRUCT_CTRL(fatima_tamex4time_edge)] /* [0,65535] */;
  uint32_t fatima_tamex4time_channel /* [0,1024] */;
  uint32_t fatima_tamex4time_channelv[1024 EXT_STRUCT_CTRL(fatima_tamex4time_channel)] /* [0,65535] */;
  uint32_t fatima_tamex4time_epoch /* [0,1024] */;
  uint32_t fatima_tamex4time_epochv[1024 EXT_STRUCT_CTRL(fatima_tamex4time_epoch)] /* [-1,-1] */;

} EXT_STR_h101_fatima;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_fatima_onion_t
{
  /* UNPACK */
  uint32_t fatima_ts_subsystem_id;
  uint32_t fatima_ts_t[4];
  uint32_t fatima_trigger_window_post_trig_ns;
  uint32_t fatima_trigger_window_pre_trig_ns;
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
  } fatima_tamex[4];

} EXT_STR_h101_fatima_onion;

/*******************************************************/

#define EXT_STR_h101_fatima_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_ts_subsystem_id,          UINT32,\
                    "fatima_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_ts_t1,                    UINT32,\
                    "fatima_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_ts_t2,                    UINT32,\
                    "fatima_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_ts_t3,                    UINT32,\
                    "fatima_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_ts_t4,                    UINT32,\
                    "fatima_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_trigger_window_post_trig_ns,UINT32,\
                    "fatima_trigger_window_post_trig_ns",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_trigger_window_pre_trig_ns,UINT32,\
                    "fatima_trigger_window_pre_trig_ns",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatima_tamex1event_size,         UINT32,\
                    "fatima_tamex1event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex1time_coarse,        UINT32,\
                    "fatima_tamex1time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex1time_coarsev,       UINT32,\
                    "fatima_tamex1time_coarsev",       "fatima_tamex1time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex1time_fine,          UINT32,\
                    "fatima_tamex1time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex1time_finev,         UINT32,\
                    "fatima_tamex1time_finev",         "fatima_tamex1time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex1time_edge,          UINT32,\
                    "fatima_tamex1time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex1time_edgev,         UINT32,\
                    "fatima_tamex1time_edgev",         "fatima_tamex1time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex1time_channel,       UINT32,\
                    "fatima_tamex1time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex1time_channelv,      UINT32,\
                    "fatima_tamex1time_channelv",      "fatima_tamex1time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex1time_epoch,         UINT32,\
                    "fatima_tamex1time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex1time_epochv,        UINT32,\
                    "fatima_tamex1time_epochv",        "fatima_tamex1time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatima_tamex2event_size,         UINT32,\
                    "fatima_tamex2event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex2time_coarse,        UINT32,\
                    "fatima_tamex2time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex2time_coarsev,       UINT32,\
                    "fatima_tamex2time_coarsev",       "fatima_tamex2time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex2time_fine,          UINT32,\
                    "fatima_tamex2time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex2time_finev,         UINT32,\
                    "fatima_tamex2time_finev",         "fatima_tamex2time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex2time_edge,          UINT32,\
                    "fatima_tamex2time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex2time_edgev,         UINT32,\
                    "fatima_tamex2time_edgev",         "fatima_tamex2time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex2time_channel,       UINT32,\
                    "fatima_tamex2time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex2time_channelv,      UINT32,\
                    "fatima_tamex2time_channelv",      "fatima_tamex2time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex2time_epoch,         UINT32,\
                    "fatima_tamex2time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex2time_epochv,        UINT32,\
                    "fatima_tamex2time_epochv",        "fatima_tamex2time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatima_tamex3event_size,         UINT32,\
                    "fatima_tamex3event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex3time_coarse,        UINT32,\
                    "fatima_tamex3time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex3time_coarsev,       UINT32,\
                    "fatima_tamex3time_coarsev",       "fatima_tamex3time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex3time_fine,          UINT32,\
                    "fatima_tamex3time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex3time_finev,         UINT32,\
                    "fatima_tamex3time_finev",         "fatima_tamex3time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex3time_edge,          UINT32,\
                    "fatima_tamex3time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex3time_edgev,         UINT32,\
                    "fatima_tamex3time_edgev",         "fatima_tamex3time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex3time_channel,       UINT32,\
                    "fatima_tamex3time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex3time_channelv,      UINT32,\
                    "fatima_tamex3time_channelv",      "fatima_tamex3time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex3time_epoch,         UINT32,\
                    "fatima_tamex3time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex3time_epochv,        UINT32,\
                    "fatima_tamex3time_epochv",        "fatima_tamex3time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatima_tamex4event_size,         UINT32,\
                    "fatima_tamex4event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex4time_coarse,        UINT32,\
                    "fatima_tamex4time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex4time_coarsev,       UINT32,\
                    "fatima_tamex4time_coarsev",       "fatima_tamex4time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex4time_fine,          UINT32,\
                    "fatima_tamex4time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex4time_finev,         UINT32,\
                    "fatima_tamex4time_finev",         "fatima_tamex4time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex4time_edge,          UINT32,\
                    "fatima_tamex4time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex4time_edgev,         UINT32,\
                    "fatima_tamex4time_edgev",         "fatima_tamex4time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex4time_channel,       UINT32,\
                    "fatima_tamex4time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex4time_channelv,      UINT32,\
                    "fatima_tamex4time_channelv",      "fatima_tamex4time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatima_tamex4time_epoch,         UINT32,\
                    "fatima_tamex4time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatima_tamex4time_epochv,        UINT32,\
                    "fatima_tamex4time_epochv",        "fatima_tamex4time_epoch",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FATIMA_EXT_H101_FATIMA_H__*/

/*******************************************************/
