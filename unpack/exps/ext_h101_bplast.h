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
  uint32_t aida_ts_subsystem_id /* [0,65535] */;
  uint32_t aida_ts_t1 /* [0,65535] */;
  uint32_t aida_ts_t2 /* [0,65535] */;
  uint32_t aida_ts_t3 /* [0,65535] */;
  uint32_t aida_ts_t4 /* [0,65535] */;
  uint32_t aida_data_adc /* [0,10000] */;
  uint32_t aida_data_adc_timestamp_raw_lo[10000 EXT_STRUCT_CTRL(aida_data_adc)] /* [-1,-1] */;
  uint32_t aida_data_adc_timestamp_raw_hi[10000 EXT_STRUCT_CTRL(aida_data_adc)] /* [-1,-1] */;
  uint32_t aida_data_adc_timestamp_slow_lo[10000 EXT_STRUCT_CTRL(aida_data_adc)] /* [-1,-1] */;
  uint32_t aida_data_adc_timestamp_slow_hi[10000 EXT_STRUCT_CTRL(aida_data_adc)] /* [-1,-1] */;
  uint32_t aida_data_adc_timestamp_fast_lo[10000 EXT_STRUCT_CTRL(aida_data_adc)] /* [-1,-1] */;
  uint32_t aida_data_adc_timestamp_fast_hi[10000 EXT_STRUCT_CTRL(aida_data_adc)] /* [-1,-1] */;
  uint32_t aida_data_adcv[10000 EXT_STRUCT_CTRL(aida_data_adc)] /* [0,65535] */;
  uint32_t aida_data_adc_fee[10000 EXT_STRUCT_CTRL(aida_data_adc)] /* [0,255] */;
  uint32_t aida_data_adc_channel[10000 EXT_STRUCT_CTRL(aida_data_adc)] /* [0,255] */;
  uint32_t aida_data_adc_vernier[10000 EXT_STRUCT_CTRL(aida_data_adc)] /* [0,255] */;
  uint32_t aida_data_adc_range[10000 EXT_STRUCT_CTRL(aida_data_adc)] /* [0,255] */;
  uint32_t aida_data_scaler /* [0,10000] */;
  uint32_t aida_data_scaler_timestamp_lo[10000 EXT_STRUCT_CTRL(aida_data_scaler)] /* [-1,-1] */;
  uint32_t aida_data_scaler_timestamp_hi[10000 EXT_STRUCT_CTRL(aida_data_scaler)] /* [-1,-1] */;
  uint32_t aida_data_scaler_value_lo[10000 EXT_STRUCT_CTRL(aida_data_scaler)] /* [-1,-1] */;
  uint32_t aida_data_scaler_value_hi[10000 EXT_STRUCT_CTRL(aida_data_scaler)] /* [-1,-1] */;
  uint32_t aida_data_scaler_fee[10000 EXT_STRUCT_CTRL(aida_data_scaler)] /* [0,255] */;
  uint32_t aida_data_flow /* [0,10000] */;
  uint32_t aida_data_flow_timestamp_lo[10000 EXT_STRUCT_CTRL(aida_data_flow)] /* [-1,-1] */;
  uint32_t aida_data_flow_timestamp_hi[10000 EXT_STRUCT_CTRL(aida_data_flow)] /* [-1,-1] */;
  uint32_t aida_data_flow_fee[10000 EXT_STRUCT_CTRL(aida_data_flow)] /* [0,255] */;
  uint32_t aida_data_flow_paused[10000 EXT_STRUCT_CTRL(aida_data_flow)] /* [0,255] */;
  uint32_t bplast_tamex1event_size /* [-1,-1] */;
  uint32_t bplast_tamex1time_coarse /* [0,512] */;
  uint32_t bplast_tamex1time_coarsev[512 EXT_STRUCT_CTRL(bplast_tamex1time_coarse)] /* [0,65535] */;
  uint32_t bplast_tamex1time_fine /* [0,512] */;
  uint32_t bplast_tamex1time_finev[512 EXT_STRUCT_CTRL(bplast_tamex1time_fine)] /* [0,65535] */;
  uint32_t bplast_tamex1time_edge /* [0,512] */;
  uint32_t bplast_tamex1time_edgev[512 EXT_STRUCT_CTRL(bplast_tamex1time_edge)] /* [0,65535] */;
  uint32_t bplast_tamex1time_channel /* [0,512] */;
  uint32_t bplast_tamex1time_channelv[512 EXT_STRUCT_CTRL(bplast_tamex1time_channel)] /* [0,65535] */;
  uint32_t bplast_tamex1time_epoch /* [0,512] */;
  uint32_t bplast_tamex1time_epochv[512 EXT_STRUCT_CTRL(bplast_tamex1time_epoch)] /* [-1,-1] */;
  uint32_t bplast_tamex2event_size /* [-1,-1] */;
  uint32_t bplast_tamex2time_coarse /* [0,512] */;
  uint32_t bplast_tamex2time_coarsev[512 EXT_STRUCT_CTRL(bplast_tamex2time_coarse)] /* [0,65535] */;
  uint32_t bplast_tamex2time_fine /* [0,512] */;
  uint32_t bplast_tamex2time_finev[512 EXT_STRUCT_CTRL(bplast_tamex2time_fine)] /* [0,65535] */;
  uint32_t bplast_tamex2time_edge /* [0,512] */;
  uint32_t bplast_tamex2time_edgev[512 EXT_STRUCT_CTRL(bplast_tamex2time_edge)] /* [0,65535] */;
  uint32_t bplast_tamex2time_channel /* [0,512] */;
  uint32_t bplast_tamex2time_channelv[512 EXT_STRUCT_CTRL(bplast_tamex2time_channel)] /* [0,65535] */;
  uint32_t bplast_tamex2time_epoch /* [0,512] */;
  uint32_t bplast_tamex2time_epochv[512 EXT_STRUCT_CTRL(bplast_tamex2time_epoch)] /* [-1,-1] */;
  uint32_t bplast_tamex3event_size /* [-1,-1] */;
  uint32_t bplast_tamex3time_coarse /* [0,512] */;
  uint32_t bplast_tamex3time_coarsev[512 EXT_STRUCT_CTRL(bplast_tamex3time_coarse)] /* [0,65535] */;
  uint32_t bplast_tamex3time_fine /* [0,512] */;
  uint32_t bplast_tamex3time_finev[512 EXT_STRUCT_CTRL(bplast_tamex3time_fine)] /* [0,65535] */;
  uint32_t bplast_tamex3time_edge /* [0,512] */;
  uint32_t bplast_tamex3time_edgev[512 EXT_STRUCT_CTRL(bplast_tamex3time_edge)] /* [0,65535] */;
  uint32_t bplast_tamex3time_channel /* [0,512] */;
  uint32_t bplast_tamex3time_channelv[512 EXT_STRUCT_CTRL(bplast_tamex3time_channel)] /* [0,65535] */;
  uint32_t bplast_tamex3time_epoch /* [0,512] */;
  uint32_t bplast_tamex3time_epochv[512 EXT_STRUCT_CTRL(bplast_tamex3time_epoch)] /* [-1,-1] */;
  uint32_t bplast_ts_subsystem_id /* [0,65535] */;
  uint32_t bplast_ts_t1 /* [0,65535] */;
  uint32_t bplast_ts_t2 /* [0,65535] */;
  uint32_t bplast_ts_t3 /* [0,65535] */;
  uint32_t bplast_ts_t4 /* [0,65535] */;
  uint32_t bplast_trigger_window_post_trig_ns /* [0,64] */;
  uint32_t bplast_trigger_window_post_trig_nsv[64 EXT_STRUCT_CTRL(bplast_trigger_window_post_trig_ns)] /* [0,65535] */;
  uint32_t bplast_trigger_window_pre_trig_ns /* [0,64] */;
  uint32_t bplast_trigger_window_pre_trig_nsv[64 EXT_STRUCT_CTRL(bplast_trigger_window_pre_trig_ns)] /* [0,65535] */;

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
  uint32_t aida_ts_subsystem_id;
  uint32_t aida_ts_t[4];
  uint32_t aida_data_adc;
  uint32_t aida_data_adc_timestamp_raw_lo[10000 /* aida_data_adc */];
  uint32_t aida_data_adc_timestamp_raw_hi[10000 /* aida_data_adc */];
  uint32_t aida_data_adc_timestamp_slow_lo[10000 /* aida_data_adc */];
  uint32_t aida_data_adc_timestamp_slow_hi[10000 /* aida_data_adc */];
  uint32_t aida_data_adc_timestamp_fast_lo[10000 /* aida_data_adc */];
  uint32_t aida_data_adc_timestamp_fast_hi[10000 /* aida_data_adc */];
  uint32_t aida_data_adcv[10000 /* aida_data_adc */];
  uint32_t aida_data_adc_fee[10000 /* aida_data_adc */];
  uint32_t aida_data_adc_channel[10000 /* aida_data_adc */];
  uint32_t aida_data_adc_vernier[10000 /* aida_data_adc */];
  uint32_t aida_data_adc_range[10000 /* aida_data_adc */];
  uint32_t aida_data_scaler;
  uint32_t aida_data_scaler_timestamp_lo[10000 /* aida_data_scaler */];
  uint32_t aida_data_scaler_timestamp_hi[10000 /* aida_data_scaler */];
  uint32_t aida_data_scaler_value_lo[10000 /* aida_data_scaler */];
  uint32_t aida_data_scaler_value_hi[10000 /* aida_data_scaler */];
  uint32_t aida_data_scaler_fee[10000 /* aida_data_scaler */];
  uint32_t aida_data_flow;
  uint32_t aida_data_flow_timestamp_lo[10000 /* aida_data_flow */];
  uint32_t aida_data_flow_timestamp_hi[10000 /* aida_data_flow */];
  uint32_t aida_data_flow_fee[10000 /* aida_data_flow */];
  uint32_t aida_data_flow_paused[10000 /* aida_data_flow */];
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
  } bplast_tamex[3];
  uint32_t bplast_ts_subsystem_id;
  uint32_t bplast_ts_t[4];
  uint32_t bplast_trigger_window_post_trig_ns;
  uint32_t bplast_trigger_window_post_trig_nsv[64 /* bplast_trigger_window_post_trig_ns */];
  uint32_t bplast_trigger_window_pre_trig_ns;
  uint32_t bplast_trigger_window_pre_trig_nsv[64 /* bplast_trigger_window_pre_trig_ns */];

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
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     aida_ts_subsystem_id,            UINT32,\
                    "aida_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     aida_ts_t1,                      UINT32,\
                    "aida_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     aida_ts_t2,                      UINT32,\
                    "aida_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     aida_ts_t3,                      UINT32,\
                    "aida_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     aida_ts_t4,                      UINT32,\
                    "aida_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     aida_data_adc,                   UINT32,\
                    "aida_data_adc",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_adc_timestamp_raw_lo,  UINT32,\
                    "aida_data_adc_timestamp_raw_lo",  "aida_data_adc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_adc_timestamp_raw_hi,  UINT32,\
                    "aida_data_adc_timestamp_raw_hi",  "aida_data_adc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_adc_timestamp_slow_lo, UINT32,\
                    "aida_data_adc_timestamp_slow_lo", "aida_data_adc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_adc_timestamp_slow_hi, UINT32,\
                    "aida_data_adc_timestamp_slow_hi", "aida_data_adc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_adc_timestamp_fast_lo, UINT32,\
                    "aida_data_adc_timestamp_fast_lo", "aida_data_adc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_adc_timestamp_fast_hi, UINT32,\
                    "aida_data_adc_timestamp_fast_hi", "aida_data_adc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_adcv,                  UINT32,\
                    "aida_data_adcv",                  "aida_data_adc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_adc_fee,               UINT32,\
                    "aida_data_adc_fee",               "aida_data_adc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_adc_channel,           UINT32,\
                    "aida_data_adc_channel",           "aida_data_adc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_adc_vernier,           UINT32,\
                    "aida_data_adc_vernier",           "aida_data_adc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_adc_range,             UINT32,\
                    "aida_data_adc_range",             "aida_data_adc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     aida_data_scaler,                UINT32,\
                    "aida_data_scaler",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_scaler_timestamp_lo,   UINT32,\
                    "aida_data_scaler_timestamp_lo",   "aida_data_scaler",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_scaler_timestamp_hi,   UINT32,\
                    "aida_data_scaler_timestamp_hi",   "aida_data_scaler",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_scaler_value_lo,       UINT32,\
                    "aida_data_scaler_value_lo",       "aida_data_scaler",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_scaler_value_hi,       UINT32,\
                    "aida_data_scaler_value_hi",       "aida_data_scaler",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_scaler_fee,            UINT32,\
                    "aida_data_scaler_fee",            "aida_data_scaler",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     aida_data_flow,                  UINT32,\
                    "aida_data_flow",10000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_flow_timestamp_lo,     UINT32,\
                    "aida_data_flow_timestamp_lo",     "aida_data_flow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_flow_timestamp_hi,     UINT32,\
                    "aida_data_flow_timestamp_hi",     "aida_data_flow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_flow_fee,              UINT32,\
                    "aida_data_flow_fee",              "aida_data_flow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     aida_data_flow_paused,           UINT32,\
                    "aida_data_flow_paused",           "aida_data_flow",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bplast_tamex1event_size,         UINT32,\
                    "bplast_tamex1event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_coarse,        UINT32,\
                    "bplast_tamex1time_coarse",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_coarsev,       UINT32,\
                    "bplast_tamex1time_coarsev",       "bplast_tamex1time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_fine,          UINT32,\
                    "bplast_tamex1time_fine",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_finev,         UINT32,\
                    "bplast_tamex1time_finev",         "bplast_tamex1time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_edge,          UINT32,\
                    "bplast_tamex1time_edge",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_edgev,         UINT32,\
                    "bplast_tamex1time_edgev",         "bplast_tamex1time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_channel,       UINT32,\
                    "bplast_tamex1time_channel",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_channelv,      UINT32,\
                    "bplast_tamex1time_channelv",      "bplast_tamex1time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_epoch,         UINT32,\
                    "bplast_tamex1time_epoch",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex1time_epochv,        UINT32,\
                    "bplast_tamex1time_epochv",        "bplast_tamex1time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bplast_tamex2event_size,         UINT32,\
                    "bplast_tamex2event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_coarse,        UINT32,\
                    "bplast_tamex2time_coarse",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_coarsev,       UINT32,\
                    "bplast_tamex2time_coarsev",       "bplast_tamex2time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_fine,          UINT32,\
                    "bplast_tamex2time_fine",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_finev,         UINT32,\
                    "bplast_tamex2time_finev",         "bplast_tamex2time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_edge,          UINT32,\
                    "bplast_tamex2time_edge",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_edgev,         UINT32,\
                    "bplast_tamex2time_edgev",         "bplast_tamex2time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_channel,       UINT32,\
                    "bplast_tamex2time_channel",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_channelv,      UINT32,\
                    "bplast_tamex2time_channelv",      "bplast_tamex2time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_epoch,         UINT32,\
                    "bplast_tamex2time_epoch",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex2time_epochv,        UINT32,\
                    "bplast_tamex2time_epochv",        "bplast_tamex2time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bplast_tamex3event_size,         UINT32,\
                    "bplast_tamex3event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_coarse,        UINT32,\
                    "bplast_tamex3time_coarse",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_coarsev,       UINT32,\
                    "bplast_tamex3time_coarsev",       "bplast_tamex3time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_fine,          UINT32,\
                    "bplast_tamex3time_fine",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_finev,         UINT32,\
                    "bplast_tamex3time_finev",         "bplast_tamex3time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_edge,          UINT32,\
                    "bplast_tamex3time_edge",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_edgev,         UINT32,\
                    "bplast_tamex3time_edgev",         "bplast_tamex3time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_channel,       UINT32,\
                    "bplast_tamex3time_channel",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_channelv,      UINT32,\
                    "bplast_tamex3time_channelv",      "bplast_tamex3time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_epoch,         UINT32,\
                    "bplast_tamex3time_epoch",512,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bplast_tamex3time_epochv,        UINT32,\
                    "bplast_tamex3time_epochv",        "bplast_tamex3time_epoch",0/*flags*/); \
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

#endif/*__GUARD_H101_EXT_H101_BPLAST_H__*/

/*******************************************************/
