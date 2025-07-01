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
  uint32_t fimp_data1event_counter_lo /* [-1,-1] */;
  uint32_t fimp_data1event_counter_hi /* [-1,-1] */;
  uint32_t fimp_data1trig_coarse_time_lo /* [-1,-1] */;
  uint32_t fimp_data1trig_coarse_time_hi /* [-1,-1] */;
  uint32_t fimp_data1time_coarseM /* [1,258] */;
  uint32_t fimp_data1time_coarseMI[258 EXT_STRUCT_CTRL(fimp_data1time_coarseM)] /* [1,258] */;
  uint32_t fimp_data1time_coarseME[258 EXT_STRUCT_CTRL(fimp_data1time_coarseM)] /* [1,33024] */;
  uint32_t fimp_data1time_coarse /* [0,33024] */;
  uint32_t fimp_data1time_coarsev[33024 EXT_STRUCT_CTRL(fimp_data1time_coarse)] /* [0,65535] */;
  uint32_t fimp_data1time_fineM /* [1,258] */;
  uint32_t fimp_data1time_fineMI[258 EXT_STRUCT_CTRL(fimp_data1time_fineM)] /* [1,258] */;
  uint32_t fimp_data1time_fineME[258 EXT_STRUCT_CTRL(fimp_data1time_fineM)] /* [1,33024] */;
  uint32_t fimp_data1time_fine /* [0,33024] */;
  uint32_t fimp_data1time_finev[33024 EXT_STRUCT_CTRL(fimp_data1time_fine)] /* [0,65535] */;
  uint32_t fimp_data1lead_or_trailM /* [1,258] */;
  uint32_t fimp_data1lead_or_trailMI[258 EXT_STRUCT_CTRL(fimp_data1lead_or_trailM)] /* [1,258] */;
  uint32_t fimp_data1lead_or_trailME[258 EXT_STRUCT_CTRL(fimp_data1lead_or_trailM)] /* [1,33024] */;
  uint32_t fimp_data1lead_or_trail /* [0,33024] */;
  uint32_t fimp_data1lead_or_trailv[33024 EXT_STRUCT_CTRL(fimp_data1lead_or_trail)] /* [0,255] */;
  uint32_t fimp_data2event_counter_lo /* [-1,-1] */;
  uint32_t fimp_data2event_counter_hi /* [-1,-1] */;
  uint32_t fimp_data2trig_coarse_time_lo /* [-1,-1] */;
  uint32_t fimp_data2trig_coarse_time_hi /* [-1,-1] */;
  uint32_t fimp_data2time_coarseM /* [1,258] */;
  uint32_t fimp_data2time_coarseMI[258 EXT_STRUCT_CTRL(fimp_data2time_coarseM)] /* [1,258] */;
  uint32_t fimp_data2time_coarseME[258 EXT_STRUCT_CTRL(fimp_data2time_coarseM)] /* [1,33024] */;
  uint32_t fimp_data2time_coarse /* [0,33024] */;
  uint32_t fimp_data2time_coarsev[33024 EXT_STRUCT_CTRL(fimp_data2time_coarse)] /* [0,65535] */;
  uint32_t fimp_data2time_fineM /* [1,258] */;
  uint32_t fimp_data2time_fineMI[258 EXT_STRUCT_CTRL(fimp_data2time_fineM)] /* [1,258] */;
  uint32_t fimp_data2time_fineME[258 EXT_STRUCT_CTRL(fimp_data2time_fineM)] /* [1,33024] */;
  uint32_t fimp_data2time_fine /* [0,33024] */;
  uint32_t fimp_data2time_finev[33024 EXT_STRUCT_CTRL(fimp_data2time_fine)] /* [0,65535] */;
  uint32_t fimp_data2lead_or_trailM /* [1,258] */;
  uint32_t fimp_data2lead_or_trailMI[258 EXT_STRUCT_CTRL(fimp_data2lead_or_trailM)] /* [1,258] */;
  uint32_t fimp_data2lead_or_trailME[258 EXT_STRUCT_CTRL(fimp_data2lead_or_trailM)] /* [1,33024] */;
  uint32_t fimp_data2lead_or_trail /* [0,33024] */;
  uint32_t fimp_data2lead_or_trailv[33024 EXT_STRUCT_CTRL(fimp_data2lead_or_trail)] /* [0,255] */;

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
  struct {
    uint32_t event_counter_lo;
    uint32_t event_counter_hi;
    uint32_t trig_coarse_time_lo;
    uint32_t trig_coarse_time_hi;
    uint32_t time_coarseM;
    uint32_t time_coarseMI[258 /* time_coarseM */];
    uint32_t time_coarseME[258 /* time_coarseM */];
    uint32_t time_coarse;
    uint32_t time_coarsev[33024 /* time_coarse */];
    uint32_t time_fineM;
    uint32_t time_fineMI[258 /* time_fineM */];
    uint32_t time_fineME[258 /* time_fineM */];
    uint32_t time_fine;
    uint32_t time_finev[33024 /* time_fine */];
    uint32_t lead_or_trailM;
    uint32_t lead_or_trailMI[258 /* lead_or_trailM */];
    uint32_t lead_or_trailME[258 /* lead_or_trailM */];
    uint32_t lead_or_trail;
    uint32_t lead_or_trailv[33024 /* lead_or_trail */];
  } fimp_data[2];

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
                     fimp_data1event_counter_lo,      UINT32,\
                    "fimp_data1event_counter_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fimp_data1event_counter_hi,      UINT32,\
                    "fimp_data1event_counter_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fimp_data1trig_coarse_time_lo,   UINT32,\
                    "fimp_data1trig_coarse_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fimp_data1trig_coarse_time_hi,   UINT32,\
                    "fimp_data1trig_coarse_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data1time_coarseM,          UINT32,\
                    "fimp_data1time_coarseM",258,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data1time_coarseMI,         UINT32,\
                    "fimp_data1time_coarseMI",         "fimp_data1time_coarseM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data1time_coarseME,         UINT32,\
                    "fimp_data1time_coarseME",         "fimp_data1time_coarseM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data1time_coarse,           UINT32,\
                    "fimp_data1time_coarse",33024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data1time_coarsev,          UINT32,\
                    "fimp_data1time_coarsev",          "fimp_data1time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data1time_fineM,            UINT32,\
                    "fimp_data1time_fineM",258,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data1time_fineMI,           UINT32,\
                    "fimp_data1time_fineMI",           "fimp_data1time_fineM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data1time_fineME,           UINT32,\
                    "fimp_data1time_fineME",           "fimp_data1time_fineM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data1time_fine,             UINT32,\
                    "fimp_data1time_fine",33024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data1time_finev,            UINT32,\
                    "fimp_data1time_finev",            "fimp_data1time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data1lead_or_trailM,        UINT32,\
                    "fimp_data1lead_or_trailM",258,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data1lead_or_trailMI,       UINT32,\
                    "fimp_data1lead_or_trailMI",       "fimp_data1lead_or_trailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data1lead_or_trailME,       UINT32,\
                    "fimp_data1lead_or_trailME",       "fimp_data1lead_or_trailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data1lead_or_trail,         UINT32,\
                    "fimp_data1lead_or_trail",33024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data1lead_or_trailv,        UINT32,\
                    "fimp_data1lead_or_trailv",        "fimp_data1lead_or_trail",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fimp_data2event_counter_lo,      UINT32,\
                    "fimp_data2event_counter_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fimp_data2event_counter_hi,      UINT32,\
                    "fimp_data2event_counter_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fimp_data2trig_coarse_time_lo,   UINT32,\
                    "fimp_data2trig_coarse_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fimp_data2trig_coarse_time_hi,   UINT32,\
                    "fimp_data2trig_coarse_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data2time_coarseM,          UINT32,\
                    "fimp_data2time_coarseM",258,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data2time_coarseMI,         UINT32,\
                    "fimp_data2time_coarseMI",         "fimp_data2time_coarseM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data2time_coarseME,         UINT32,\
                    "fimp_data2time_coarseME",         "fimp_data2time_coarseM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data2time_coarse,           UINT32,\
                    "fimp_data2time_coarse",33024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data2time_coarsev,          UINT32,\
                    "fimp_data2time_coarsev",          "fimp_data2time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data2time_fineM,            UINT32,\
                    "fimp_data2time_fineM",258,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data2time_fineMI,           UINT32,\
                    "fimp_data2time_fineMI",           "fimp_data2time_fineM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data2time_fineME,           UINT32,\
                    "fimp_data2time_fineME",           "fimp_data2time_fineM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data2time_fine,             UINT32,\
                    "fimp_data2time_fine",33024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data2time_finev,            UINT32,\
                    "fimp_data2time_finev",            "fimp_data2time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data2lead_or_trailM,        UINT32,\
                    "fimp_data2lead_or_trailM",258,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data2lead_or_trailMI,       UINT32,\
                    "fimp_data2lead_or_trailMI",       "fimp_data2lead_or_trailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data2lead_or_trailME,       UINT32,\
                    "fimp_data2lead_or_trailME",       "fimp_data2lead_or_trailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fimp_data2lead_or_trail,         UINT32,\
                    "fimp_data2lead_or_trail",33024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fimp_data2lead_or_trailv,        UINT32,\
                    "fimp_data2lead_or_trailv",        "fimp_data2lead_or_trail",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FIMP_EXT_H101_FIMP_H__*/

/*******************************************************/
