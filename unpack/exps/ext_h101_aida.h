/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_AIDA_EXT_H101_AIDA_H__
#define __GUARD_H101_AIDA_EXT_H101_AIDA_H__

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

typedef struct EXT_STR_h101_aida_t
{
  /* UNPACK */
  uint32_t aida_ts_subsystem_id /* [0,65535] */;
  uint32_t aida_ts_t1 /* [0,65535] */;
  uint32_t aida_ts_t2 /* [0,65535] */;
  uint32_t aida_ts_t3 /* [0,65535] */;
  uint32_t aida_ts_t4 /* [0,65535] */;
  uint32_t aida_data_adc /* [0,13000] */;
  uint32_t aida_data_adc_timestamp_raw_lo[13000 EXT_STRUCT_CTRL(aida_data_adc)] /* [-1,-1] */;
  uint32_t aida_data_adc_timestamp_raw_hi[13000 EXT_STRUCT_CTRL(aida_data_adc)] /* [-1,-1] */;
  uint32_t aida_data_adc_timestamp_slow_lo[13000 EXT_STRUCT_CTRL(aida_data_adc)] /* [-1,-1] */;
  uint32_t aida_data_adc_timestamp_slow_hi[13000 EXT_STRUCT_CTRL(aida_data_adc)] /* [-1,-1] */;
  uint32_t aida_data_adc_timestamp_fast_lo[13000 EXT_STRUCT_CTRL(aida_data_adc)] /* [-1,-1] */;
  uint32_t aida_data_adc_timestamp_fast_hi[13000 EXT_STRUCT_CTRL(aida_data_adc)] /* [-1,-1] */;
  uint32_t aida_data_adcv[13000 EXT_STRUCT_CTRL(aida_data_adc)] /* [0,65535] */;
  uint32_t aida_data_adc_fee[13000 EXT_STRUCT_CTRL(aida_data_adc)] /* [0,255] */;
  uint32_t aida_data_adc_channel[13000 EXT_STRUCT_CTRL(aida_data_adc)] /* [0,255] */;
  uint32_t aida_data_adc_vernier[13000 EXT_STRUCT_CTRL(aida_data_adc)] /* [0,255] */;
  uint32_t aida_data_adc_range[13000 EXT_STRUCT_CTRL(aida_data_adc)] /* [0,255] */;
  uint32_t aida_data_scaler /* [0,13000] */;
  uint32_t aida_data_scaler_timestamp_lo[13000 EXT_STRUCT_CTRL(aida_data_scaler)] /* [-1,-1] */;
  uint32_t aida_data_scaler_timestamp_hi[13000 EXT_STRUCT_CTRL(aida_data_scaler)] /* [-1,-1] */;
  uint32_t aida_data_scaler_value_lo[13000 EXT_STRUCT_CTRL(aida_data_scaler)] /* [-1,-1] */;
  uint32_t aida_data_scaler_value_hi[13000 EXT_STRUCT_CTRL(aida_data_scaler)] /* [-1,-1] */;
  uint32_t aida_data_scaler_fee[13000 EXT_STRUCT_CTRL(aida_data_scaler)] /* [0,255] */;
  uint32_t aida_data_flow /* [0,13000] */;
  uint32_t aida_data_flow_timestamp_lo[13000 EXT_STRUCT_CTRL(aida_data_flow)] /* [-1,-1] */;
  uint32_t aida_data_flow_timestamp_hi[13000 EXT_STRUCT_CTRL(aida_data_flow)] /* [-1,-1] */;
  uint32_t aida_data_flow_fee[13000 EXT_STRUCT_CTRL(aida_data_flow)] /* [0,255] */;
  uint32_t aida_data_flow_paused[13000 EXT_STRUCT_CTRL(aida_data_flow)] /* [0,255] */;

} EXT_STR_h101_aida;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_aida_onion_t
{
  /* UNPACK */
  uint32_t aida_ts_subsystem_id;
  uint32_t aida_ts_t[4];
  uint32_t aida_data_adc;
  uint32_t aida_data_adc_timestamp_raw_lo[13000 /* aida_data_adc */];
  uint32_t aida_data_adc_timestamp_raw_hi[13000 /* aida_data_adc */];
  uint32_t aida_data_adc_timestamp_slow_lo[13000 /* aida_data_adc */];
  uint32_t aida_data_adc_timestamp_slow_hi[13000 /* aida_data_adc */];
  uint32_t aida_data_adc_timestamp_fast_lo[13000 /* aida_data_adc */];
  uint32_t aida_data_adc_timestamp_fast_hi[13000 /* aida_data_adc */];
  uint32_t aida_data_adcv[13000 /* aida_data_adc */];
  uint32_t aida_data_adc_fee[13000 /* aida_data_adc */];
  uint32_t aida_data_adc_channel[13000 /* aida_data_adc */];
  uint32_t aida_data_adc_vernier[13000 /* aida_data_adc */];
  uint32_t aida_data_adc_range[13000 /* aida_data_adc */];
  uint32_t aida_data_scaler;
  uint32_t aida_data_scaler_timestamp_lo[13000 /* aida_data_scaler */];
  uint32_t aida_data_scaler_timestamp_hi[13000 /* aida_data_scaler */];
  uint32_t aida_data_scaler_value_lo[13000 /* aida_data_scaler */];
  uint32_t aida_data_scaler_value_hi[13000 /* aida_data_scaler */];
  uint32_t aida_data_scaler_fee[13000 /* aida_data_scaler */];
  uint32_t aida_data_flow;
  uint32_t aida_data_flow_timestamp_lo[13000 /* aida_data_flow */];
  uint32_t aida_data_flow_timestamp_hi[13000 /* aida_data_flow */];
  uint32_t aida_data_flow_fee[13000 /* aida_data_flow */];
  uint32_t aida_data_flow_paused[13000 /* aida_data_flow */];

} EXT_STR_h101_aida_onion;

/*******************************************************/

#define EXT_STR_h101_aida_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
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
                    "aida_data_adc",13000,0/*flags*/); \
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
                    "aida_data_scaler",13000,0/*flags*/); \
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
                    "aida_data_flow",13000,0/*flags*/); \
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
  \
} while (0);

#endif/*__GUARD_H101_AIDA_EXT_H101_AIDA_H__*/

/*******************************************************/
