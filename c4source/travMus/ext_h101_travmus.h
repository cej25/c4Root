/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_TRAVMUS_EXT_H101_TRAVMUS_H__
#define __GUARD_H101_TRAVMUS_EXT_H101_TRAVMUS_H__

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

typedef struct EXT_STR_h101_travmus_t
{
  /* UNPACK */
  uint32_t travmus_ts_subsystem_id /* [0,65535] */;
  uint32_t travmus_ts_t1 /* [0,65535] */;
  uint32_t travmus_ts_t2 /* [0,65535] */;
  uint32_t travmus_ts_t3 /* [0,65535] */;
  uint32_t travmus_ts_t4 /* [0,65535] */;
  uint32_t travmus_data_adcM /* [1,16] */;
  uint32_t travmus_data_adcMI[16 EXT_STRUCT_CTRL(travmus_data_adcM)] /* [1,16] */;
  uint32_t travmus_data_adcME[16 EXT_STRUCT_CTRL(travmus_data_adcM)] /* [1,320] */;
  uint32_t travmus_data_adc /* [0,320] */;
  uint32_t travmus_data_adcv[320 EXT_STRUCT_CTRL(travmus_data_adc)] /* [0,1048575] */;
  uint32_t travmus_data_tdcM /* [1,16] */;
  uint32_t travmus_data_tdcMI[16 EXT_STRUCT_CTRL(travmus_data_tdcM)] /* [1,16] */;
  uint32_t travmus_data_tdcME[16 EXT_STRUCT_CTRL(travmus_data_tdcM)] /* [1,320] */;
  uint32_t travmus_data_tdc /* [0,320] */;
  uint32_t travmus_data_tdcv[320 EXT_STRUCT_CTRL(travmus_data_tdc)] /* [0,1048575] */;
  uint32_t travmus_data_trig_tdcM /* [1,16] */;
  uint32_t travmus_data_trig_tdcMI[16 EXT_STRUCT_CTRL(travmus_data_trig_tdcM)] /* [1,16] */;
  uint32_t travmus_data_trig_tdcME[16 EXT_STRUCT_CTRL(travmus_data_trig_tdcM)] /* [1,320] */;
  uint32_t travmus_data_trig_tdc /* [0,320] */;
  uint32_t travmus_data_trig_tdcv[320 EXT_STRUCT_CTRL(travmus_data_trig_tdc)] /* [0,1048575] */;
  uint32_t travmus_data_adc_shortM /* [1,16] */;
  uint32_t travmus_data_adc_shortMI[16 EXT_STRUCT_CTRL(travmus_data_adc_shortM)] /* [1,16] */;
  uint32_t travmus_data_adc_shortME[16 EXT_STRUCT_CTRL(travmus_data_adc_shortM)] /* [1,320] */;
  uint32_t travmus_data_adc_short /* [0,320] */;
  uint32_t travmus_data_adc_shortv[320 EXT_STRUCT_CTRL(travmus_data_adc_short)] /* [0,1048575] */;
  uint32_t travmus_data_end_of_event /* [-1,-1] */;

} EXT_STR_h101_travmus;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_travmus_onion_t
{
  /* UNPACK */
  uint32_t travmus_ts_subsystem_id;
  uint32_t travmus_ts_t[4];
  uint32_t travmus_data_adcM;
  uint32_t travmus_data_adcMI[16 /* travmus_data_adcM */];
  uint32_t travmus_data_adcME[16 /* travmus_data_adcM */];
  uint32_t travmus_data_adc;
  uint32_t travmus_data_adcv[320 /* travmus_data_adc */];
  uint32_t travmus_data_tdcM;
  uint32_t travmus_data_tdcMI[16 /* travmus_data_tdcM */];
  uint32_t travmus_data_tdcME[16 /* travmus_data_tdcM */];
  uint32_t travmus_data_tdc;
  uint32_t travmus_data_tdcv[320 /* travmus_data_tdc */];
  uint32_t travmus_data_trig_tdcM;
  uint32_t travmus_data_trig_tdcMI[16 /* travmus_data_trig_tdcM */];
  uint32_t travmus_data_trig_tdcME[16 /* travmus_data_trig_tdcM */];
  uint32_t travmus_data_trig_tdc;
  uint32_t travmus_data_trig_tdcv[320 /* travmus_data_trig_tdc */];
  uint32_t travmus_data_adc_shortM;
  uint32_t travmus_data_adc_shortMI[16 /* travmus_data_adc_shortM */];
  uint32_t travmus_data_adc_shortME[16 /* travmus_data_adc_shortM */];
  uint32_t travmus_data_adc_short;
  uint32_t travmus_data_adc_shortv[320 /* travmus_data_adc_short */];
  uint32_t travmus_data_end_of_event;

} EXT_STR_h101_travmus_onion;

/*******************************************************/

#define EXT_STR_h101_travmus_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     travmus_ts_subsystem_id,         UINT32,\
                    "travmus_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     travmus_ts_t1,                   UINT32,\
                    "travmus_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     travmus_ts_t2,                   UINT32,\
                    "travmus_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     travmus_ts_t3,                   UINT32,\
                    "travmus_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     travmus_ts_t4,                   UINT32,\
                    "travmus_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     travmus_data_adcM,               UINT32,\
                    "travmus_data_adcM",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     travmus_data_adcMI,              UINT32,\
                    "travmus_data_adcMI",              "travmus_data_adcM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     travmus_data_adcME,              UINT32,\
                    "travmus_data_adcME",              "travmus_data_adcM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     travmus_data_adc,                UINT32,\
                    "travmus_data_adc",320,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     travmus_data_adcv,               UINT32,\
                    "travmus_data_adcv",               "travmus_data_adc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     travmus_data_tdcM,               UINT32,\
                    "travmus_data_tdcM",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     travmus_data_tdcMI,              UINT32,\
                    "travmus_data_tdcMI",              "travmus_data_tdcM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     travmus_data_tdcME,              UINT32,\
                    "travmus_data_tdcME",              "travmus_data_tdcM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     travmus_data_tdc,                UINT32,\
                    "travmus_data_tdc",320,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     travmus_data_tdcv,               UINT32,\
                    "travmus_data_tdcv",               "travmus_data_tdc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     travmus_data_trig_tdcM,          UINT32,\
                    "travmus_data_trig_tdcM",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     travmus_data_trig_tdcMI,         UINT32,\
                    "travmus_data_trig_tdcMI",         "travmus_data_trig_tdcM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     travmus_data_trig_tdcME,         UINT32,\
                    "travmus_data_trig_tdcME",         "travmus_data_trig_tdcM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     travmus_data_trig_tdc,           UINT32,\
                    "travmus_data_trig_tdc",320,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     travmus_data_trig_tdcv,          UINT32,\
                    "travmus_data_trig_tdcv",          "travmus_data_trig_tdc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     travmus_data_adc_shortM,         UINT32,\
                    "travmus_data_adc_shortM",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     travmus_data_adc_shortMI,        UINT32,\
                    "travmus_data_adc_shortMI",        "travmus_data_adc_shortM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     travmus_data_adc_shortME,        UINT32,\
                    "travmus_data_adc_shortME",        "travmus_data_adc_shortM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     travmus_data_adc_short,          UINT32,\
                    "travmus_data_adc_short",320,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     travmus_data_adc_shortv,         UINT32,\
                    "travmus_data_adc_shortv",         "travmus_data_adc_short",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     travmus_data_end_of_event,       UINT32,\
                    "travmus_data_end_of_event",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_TRAVMUS_EXT_H101_TRAVMUS_H__*/

/*******************************************************/
