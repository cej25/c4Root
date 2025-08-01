/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_VME_EXT_H101_VME_H__
#define __GUARD_H101_VME_EXT_H101_VME_H__

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

typedef struct EXT_STR_h101_vme_t
{
  /* UNPACK */
  uint32_t vme_qdc_n /* [0,32] */;
  uint32_t vme_qdc_nI[32 EXT_STRUCT_CTRL(vme_qdc_n)] /* [1,32] */;
  uint32_t vme_qdc_data[32 EXT_STRUCT_CTRL(vme_qdc_n)] /* [0,16777215] */;
  uint32_t vme_v1751_board_id /* [0,255] */;
  uint32_t vme_v1751_channels1 /* [0,255] */;
  uint32_t vme_v1751_channels2 /* [0,255] */;
  uint32_t vme_v1751_channels3 /* [0,255] */;
  uint32_t vme_v1751_channels4 /* [0,255] */;
  uint32_t vme_v1751_channels5 /* [0,255] */;
  uint32_t vme_v1751_channels6 /* [0,255] */;
  uint32_t vme_v1751_channels7 /* [0,255] */;
  uint32_t vme_v1751_channels8 /* [0,255] */;
  uint32_t vme_v1751_board_time /* [-1,-1] */;
  uint32_t vme_v1751_event_size /* [-1,-1] */;
  uint32_t vme_v1751_nsamples_trace1 /* [0,65535] */;
  uint32_t vme_v1751_nsamples_trace2 /* [0,65535] */;
  uint32_t vme_v1751_nsamples_trace3 /* [0,65535] */;
  uint32_t vme_v1751_nsamples_trace4 /* [0,65535] */;
  uint32_t vme_v1751_nsamples_trace5 /* [0,65535] */;
  uint32_t vme_v1751_nsamples_trace6 /* [0,65535] */;
  uint32_t vme_v1751_nsamples_trace7 /* [0,65535] */;
  uint32_t vme_v1751_nsamples_trace8 /* [0,65535] */;
  uint32_t vme_v1751_trigger_time1 /* [-1,-1] */;
  uint32_t vme_v1751_trigger_time2 /* [-1,-1] */;
  uint32_t vme_v1751_trigger_time3 /* [-1,-1] */;
  uint32_t vme_v1751_trigger_time4 /* [-1,-1] */;
  uint32_t vme_v1751_trigger_time5 /* [-1,-1] */;
  uint32_t vme_v1751_trigger_time6 /* [-1,-1] */;
  uint32_t vme_v1751_trigger_time7 /* [-1,-1] */;
  uint32_t vme_v1751_trigger_time8 /* [-1,-1] */;
  uint32_t vme_v1751_sample_trace1 /* [0,2000] */;
  uint32_t vme_v1751_sample_trace1I[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace1)] /* [1,2000] */;
  uint32_t vme_v1751_sample_trace1v[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace1)] /* [0,65535] */;
  uint32_t vme_v1751_sample_trace2 /* [0,2000] */;
  uint32_t vme_v1751_sample_trace2I[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace2)] /* [1,2000] */;
  uint32_t vme_v1751_sample_trace2v[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace2)] /* [0,65535] */;
  uint32_t vme_v1751_sample_trace3 /* [0,2000] */;
  uint32_t vme_v1751_sample_trace3I[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace3)] /* [1,2000] */;
  uint32_t vme_v1751_sample_trace3v[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace3)] /* [0,65535] */;
  uint32_t vme_v1751_sample_trace4 /* [0,2000] */;
  uint32_t vme_v1751_sample_trace4I[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace4)] /* [1,2000] */;
  uint32_t vme_v1751_sample_trace4v[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace4)] /* [0,65535] */;
  uint32_t vme_v1751_sample_trace5 /* [0,2000] */;
  uint32_t vme_v1751_sample_trace5I[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace5)] /* [1,2000] */;
  uint32_t vme_v1751_sample_trace5v[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace5)] /* [0,65535] */;
  uint32_t vme_v1751_sample_trace6 /* [0,2000] */;
  uint32_t vme_v1751_sample_trace6I[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace6)] /* [1,2000] */;
  uint32_t vme_v1751_sample_trace6v[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace6)] /* [0,65535] */;
  uint32_t vme_v1751_sample_trace7 /* [0,2000] */;
  uint32_t vme_v1751_sample_trace7I[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace7)] /* [1,2000] */;
  uint32_t vme_v1751_sample_trace7v[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace7)] /* [0,65535] */;
  uint32_t vme_v1751_sample_trace8 /* [0,2000] */;
  uint32_t vme_v1751_sample_trace8I[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace8)] /* [1,2000] */;
  uint32_t vme_v1751_sample_trace8v[2000 EXT_STRUCT_CTRL(vme_v1751_sample_trace8)] /* [0,65535] */;

} EXT_STR_h101_vme;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_vme_onion_t
{
  /* UNPACK */
  uint32_t vme_qdc_n;
  uint32_t vme_qdc_nI[32 /* vme_qdc_n */];
  uint32_t vme_qdc_data[32 /* vme_qdc_n */];
  uint32_t vme_v1751_board_id;
  uint32_t vme_v1751_channels1;
  uint32_t vme_v1751_channels2;
  uint32_t vme_v1751_channels3;
  uint32_t vme_v1751_channels4;
  uint32_t vme_v1751_channels5;
  uint32_t vme_v1751_channels6;
  uint32_t vme_v1751_channels7;
  uint32_t vme_v1751_channels8;
  uint32_t vme_v1751_board_time;
  uint32_t vme_v1751_event_size;
  uint32_t vme_v1751_nsamples_trace1;
  uint32_t vme_v1751_nsamples_trace2;
  uint32_t vme_v1751_nsamples_trace3;
  uint32_t vme_v1751_nsamples_trace4;
  uint32_t vme_v1751_nsamples_trace5;
  uint32_t vme_v1751_nsamples_trace6;
  uint32_t vme_v1751_nsamples_trace7;
  uint32_t vme_v1751_nsamples_trace8;
  uint32_t vme_v1751_trigger_time1;
  uint32_t vme_v1751_trigger_time2;
  uint32_t vme_v1751_trigger_time3;
  uint32_t vme_v1751_trigger_time4;
  uint32_t vme_v1751_trigger_time5;
  uint32_t vme_v1751_trigger_time6;
  uint32_t vme_v1751_trigger_time7;
  uint32_t vme_v1751_trigger_time8;
  uint32_t vme_v1751_sample_trace1;
  uint32_t vme_v1751_sample_trace1I[2000 /* vme_v1751_sample_trace1 */];
  uint32_t vme_v1751_sample_trace1v[2000 /* vme_v1751_sample_trace1 */];
  uint32_t vme_v1751_sample_trace2;
  uint32_t vme_v1751_sample_trace2I[2000 /* vme_v1751_sample_trace2 */];
  uint32_t vme_v1751_sample_trace2v[2000 /* vme_v1751_sample_trace2 */];
  uint32_t vme_v1751_sample_trace3;
  uint32_t vme_v1751_sample_trace3I[2000 /* vme_v1751_sample_trace3 */];
  uint32_t vme_v1751_sample_trace3v[2000 /* vme_v1751_sample_trace3 */];
  uint32_t vme_v1751_sample_trace4;
  uint32_t vme_v1751_sample_trace4I[2000 /* vme_v1751_sample_trace4 */];
  uint32_t vme_v1751_sample_trace4v[2000 /* vme_v1751_sample_trace4 */];
  uint32_t vme_v1751_sample_trace5;
  uint32_t vme_v1751_sample_trace5I[2000 /* vme_v1751_sample_trace5 */];
  uint32_t vme_v1751_sample_trace5v[2000 /* vme_v1751_sample_trace5 */];
  uint32_t vme_v1751_sample_trace6;
  uint32_t vme_v1751_sample_trace6I[2000 /* vme_v1751_sample_trace6 */];
  uint32_t vme_v1751_sample_trace6v[2000 /* vme_v1751_sample_trace6 */];
  uint32_t vme_v1751_sample_trace7;
  uint32_t vme_v1751_sample_trace7I[2000 /* vme_v1751_sample_trace7 */];
  uint32_t vme_v1751_sample_trace7v[2000 /* vme_v1751_sample_trace7 */];
  uint32_t vme_v1751_sample_trace8;
  uint32_t vme_v1751_sample_trace8I[2000 /* vme_v1751_sample_trace8 */];
  uint32_t vme_v1751_sample_trace8v[2000 /* vme_v1751_sample_trace8 */];

} EXT_STR_h101_vme_onion;

/*******************************************************/

#define EXT_STR_h101_vme_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_qdc_n,                       UINT32,\
                    "vme_qdc_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_qdc_nI,                      UINT32,\
                    "vme_qdc_nI",                      "vme_qdc_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_qdc_data,                    UINT32,\
                    "vme_qdc_data",                    "vme_qdc_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_board_id,              UINT32,\
                    "vme_v1751_board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_channels1,             UINT32,\
                    "vme_v1751_channels1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_channels2,             UINT32,\
                    "vme_v1751_channels2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_channels3,             UINT32,\
                    "vme_v1751_channels3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_channels4,             UINT32,\
                    "vme_v1751_channels4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_channels5,             UINT32,\
                    "vme_v1751_channels5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_channels6,             UINT32,\
                    "vme_v1751_channels6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_channels7,             UINT32,\
                    "vme_v1751_channels7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_channels8,             UINT32,\
                    "vme_v1751_channels8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     vme_v1751_board_time,            UINT32,\
                    "vme_v1751_board_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     vme_v1751_event_size,            UINT32,\
                    "vme_v1751_event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_nsamples_trace1,       UINT32,\
                    "vme_v1751_nsamples_trace1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_nsamples_trace2,       UINT32,\
                    "vme_v1751_nsamples_trace2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_nsamples_trace3,       UINT32,\
                    "vme_v1751_nsamples_trace3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_nsamples_trace4,       UINT32,\
                    "vme_v1751_nsamples_trace4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_nsamples_trace5,       UINT32,\
                    "vme_v1751_nsamples_trace5",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_nsamples_trace6,       UINT32,\
                    "vme_v1751_nsamples_trace6",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_nsamples_trace7,       UINT32,\
                    "vme_v1751_nsamples_trace7",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_nsamples_trace8,       UINT32,\
                    "vme_v1751_nsamples_trace8",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     vme_v1751_trigger_time1,         UINT32,\
                    "vme_v1751_trigger_time1",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     vme_v1751_trigger_time2,         UINT32,\
                    "vme_v1751_trigger_time2",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     vme_v1751_trigger_time3,         UINT32,\
                    "vme_v1751_trigger_time3",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     vme_v1751_trigger_time4,         UINT32,\
                    "vme_v1751_trigger_time4",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     vme_v1751_trigger_time5,         UINT32,\
                    "vme_v1751_trigger_time5",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     vme_v1751_trigger_time6,         UINT32,\
                    "vme_v1751_trigger_time6",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     vme_v1751_trigger_time7,         UINT32,\
                    "vme_v1751_trigger_time7",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     vme_v1751_trigger_time8,         UINT32,\
                    "vme_v1751_trigger_time8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace1,         UINT32,\
                    "vme_v1751_sample_trace1",2000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace1I,        UINT32,\
                    "vme_v1751_sample_trace1I",        "vme_v1751_sample_trace1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace1v,        UINT32,\
                    "vme_v1751_sample_trace1v",        "vme_v1751_sample_trace1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace2,         UINT32,\
                    "vme_v1751_sample_trace2",2000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace2I,        UINT32,\
                    "vme_v1751_sample_trace2I",        "vme_v1751_sample_trace2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace2v,        UINT32,\
                    "vme_v1751_sample_trace2v",        "vme_v1751_sample_trace2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace3,         UINT32,\
                    "vme_v1751_sample_trace3",2000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace3I,        UINT32,\
                    "vme_v1751_sample_trace3I",        "vme_v1751_sample_trace3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace3v,        UINT32,\
                    "vme_v1751_sample_trace3v",        "vme_v1751_sample_trace3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace4,         UINT32,\
                    "vme_v1751_sample_trace4",2000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace4I,        UINT32,\
                    "vme_v1751_sample_trace4I",        "vme_v1751_sample_trace4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace4v,        UINT32,\
                    "vme_v1751_sample_trace4v",        "vme_v1751_sample_trace4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace5,         UINT32,\
                    "vme_v1751_sample_trace5",2000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace5I,        UINT32,\
                    "vme_v1751_sample_trace5I",        "vme_v1751_sample_trace5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace5v,        UINT32,\
                    "vme_v1751_sample_trace5v",        "vme_v1751_sample_trace5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace6,         UINT32,\
                    "vme_v1751_sample_trace6",2000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace6I,        UINT32,\
                    "vme_v1751_sample_trace6I",        "vme_v1751_sample_trace6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace6v,        UINT32,\
                    "vme_v1751_sample_trace6v",        "vme_v1751_sample_trace6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace7,         UINT32,\
                    "vme_v1751_sample_trace7",2000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace7I,        UINT32,\
                    "vme_v1751_sample_trace7I",        "vme_v1751_sample_trace7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace7v,        UINT32,\
                    "vme_v1751_sample_trace7v",        "vme_v1751_sample_trace7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace8,         UINT32,\
                    "vme_v1751_sample_trace8",2000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace8I,        UINT32,\
                    "vme_v1751_sample_trace8I",        "vme_v1751_sample_trace8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     vme_v1751_sample_trace8v,        UINT32,\
                    "vme_v1751_sample_trace8v",        "vme_v1751_sample_trace8",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_VME_EXT_H101_VME_H__*/

/*******************************************************/
