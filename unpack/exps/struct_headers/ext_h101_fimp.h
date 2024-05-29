/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_FIMP_EXT_H101_FIMP_H__
#define __GUARD_H101_FIMP_EXT_H101_FIMP_H__

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

typedef struct EXT_STR_h101_fimp_t
{
  /* UNPACK */
  uint32_t fimp_ts_subsystem_id /* [0,65535] */;
  uint32_t fimp_ts_t1 /* [0,65535] */;
  uint32_t fimp_ts_t2 /* [0,65535] */;
  uint32_t fimp_ts_t3 /* [0,65535] */;
  uint32_t fimp_ts_t4 /* [0,65535] */;
  uint32_t fimp_data_event_counter_lo /* [-1,-1] */;
  uint32_t fimp_data_event_counter_hi /* [-1,-1] */;
  uint32_t fimp_data_trig_coarse_time_lo /* [-1,-1] */;
  uint32_t fimp_data_trig_coarse_time_hi /* [-1,-1] */;
  uint32_t fimp_data_time_coarseM /* [1,258] */;
  uint32_t fimp_data_time_coarseMI[258 EXT_STRUCT_CTRL(fimp_data_time_coarseM)] /* [1,258] */;
  uint32_t fimp_data_time_coarseME[258 EXT_STRUCT_CTRL(fimp_data_time_coarseM)] /* [1,33024] */;
  uint32_t fimp_data_time_coarse /* [0,33024] */;
  uint32_t fimp_data_time_coarsev[33024 EXT_STRUCT_CTRL(fimp_data_time_coarse)] /* [0,65535] */;
  uint32_t fimp_data_time_fineM /* [1,258] */;
  uint32_t fimp_data_time_fineMI[258 EXT_STRUCT_CTRL(fimp_data_time_fineM)] /* [1,258] */;
  uint32_t fimp_data_time_fineME[258 EXT_STRUCT_CTRL(fimp_data_time_fineM)] /* [1,33024] */;
  uint32_t fimp_data_time_fine /* [0,33024] */;
  uint32_t fimp_data_time_finev[33024 EXT_STRUCT_CTRL(fimp_data_time_fine)] /* [0,65535] */;
  uint32_t fimp_data_lead_or_trailM /* [1,258] */;
  uint32_t fimp_data_lead_or_trailMI[258 EXT_STRUCT_CTRL(fimp_data_lead_or_trailM)] /* [1,258] */;
  uint32_t fimp_data_lead_or_trailME[258 EXT_STRUCT_CTRL(fimp_data_lead_or_trailM)] /* [1,33024] */;
  uint32_t fimp_data_lead_or_trail /* [0,33024] */;
  uint32_t fimp_data_lead_or_trailv[33024 EXT_STRUCT_CTRL(fimp_data_lead_or_trail)] /* [0,255] */;

} EXT_STR_h101_fimp;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_fimp_onion_t
{
  /* UNPACK */
  uint32_t fimp_ts_subsystem_id;
  uint32_t fimp_ts_t[4];
  uint32_t fimp_data_event_counter_lo;
  uint32_t fimp_data_event_counter_hi;
  uint32_t fimp_data_trig_coarse_time_lo;
  uint32_t fimp_data_trig_coarse_time_hi;
  uint32_t fimp_data_time_coarseM;
  uint32_t fimp_data_time_coarseMI[258 /* fimp_data_time_coarseM */];
  uint32_t fimp_data_time_coarseME[258 /* fimp_data_time_coarseM */];
  uint32_t fimp_data_time_coarse;
  uint32_t fimp_data_time_coarsev[33024 /* fimp_data_time_coarse */];
  uint32_t fimp_data_time_fineM;
  uint32_t fimp_data_time_fineMI[258 /* fimp_data_time_fineM */];
  uint32_t fimp_data_time_fineME[258 /* fimp_data_time_fineM */];
  uint32_t fimp_data_time_fine;
  uint32_t fimp_data_time_finev[33024 /* fimp_data_time_fine */];
  uint32_t fimp_data_lead_or_trailM;
  uint32_t fimp_data_lead_or_trailMI[258 /* fimp_data_lead_or_trailM */];
  uint32_t fimp_data_lead_or_trailME[258 /* fimp_data_lead_or_trailM */];
  uint32_t fimp_data_lead_or_trail;
  uint32_t fimp_data_lead_or_trailv[33024 /* fimp_data_lead_or_trail */];

} EXT_STR_h101_fimp_onion;

/*******************************************************/

#define EXT_STR_h101_fimp_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_ts_subsystem_id,            UINT32,\
                    "fimp_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_ts_t1,                      UINT32,\
                    "fimp_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_ts_t2,                      UINT32,\
                    "fimp_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_ts_t3,                      UINT32,\
                    "fimp_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_ts_t4,                      UINT32,\
                    "fimp_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fimp_data_event_counter_lo,      UINT32,\
                    "fimp_data_event_counter_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fimp_data_event_counter_hi,      UINT32,\
                    "fimp_data_event_counter_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fimp_data_trig_coarse_time_lo,   UINT32,\
                    "fimp_data_trig_coarse_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fimp_data_trig_coarse_time_hi,   UINT32,\
                    "fimp_data_trig_coarse_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data_time_coarseM,          UINT32,\
                    "fimp_data_time_coarseM",258,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data_time_coarseMI,         UINT32,\
                    "fimp_data_time_coarseMI",         "fimp_data_time_coarseM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data_time_coarseME,         UINT32,\
                    "fimp_data_time_coarseME",         "fimp_data_time_coarseM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data_time_coarse,           UINT32,\
                    "fimp_data_time_coarse",33024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data_time_coarsev,          UINT32,\
                    "fimp_data_time_coarsev",          "fimp_data_time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data_time_fineM,            UINT32,\
                    "fimp_data_time_fineM",258,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data_time_fineMI,           UINT32,\
                    "fimp_data_time_fineMI",           "fimp_data_time_fineM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data_time_fineME,           UINT32,\
                    "fimp_data_time_fineME",           "fimp_data_time_fineM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data_time_fine,             UINT32,\
                    "fimp_data_time_fine",33024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data_time_finev,            UINT32,\
                    "fimp_data_time_finev",            "fimp_data_time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data_lead_or_trailM,        UINT32,\
                    "fimp_data_lead_or_trailM",258,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data_lead_or_trailMI,       UINT32,\
                    "fimp_data_lead_or_trailMI",       "fimp_data_lead_or_trailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data_lead_or_trailME,       UINT32,\
                    "fimp_data_lead_or_trailME",       "fimp_data_lead_or_trailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data_lead_or_trail,         UINT32,\
                    "fimp_data_lead_or_trail",33024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data_lead_or_trailv,        UINT32,\
                    "fimp_data_lead_or_trailv",        "fimp_data_lead_or_trail",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FIMP_EXT_H101_FIMP_H__*/

/*******************************************************/
