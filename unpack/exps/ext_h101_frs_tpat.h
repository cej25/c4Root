/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_EXT_H101_FRS_TPAT_H__
#define __GUARD_H101_EXT_H101_FRS_TPAT_H__

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
  uint32_t tpat_data_n /* [-1,-1] */;
  uint32_t tpat_data_tpat /* [0,170] */;
  uint32_t tpat_data_tpatv[170 EXT_STRUCT_CTRL(tpat_data_tpat)] /* [0,65535] */;
  uint32_t tpat_data_trig /* [0,170] */;
  uint32_t tpat_data_trigv[170 EXT_STRUCT_CTRL(tpat_data_trig)] /* [0,255] */;
  uint32_t tpat_data_ts_lo /* [0,170] */;
  uint32_t tpat_data_ts_lov[170 EXT_STRUCT_CTRL(tpat_data_ts_lo)] /* [-1,-1] */;
  uint32_t tpat_data_ts_hi /* [0,170] */;
  uint32_t tpat_data_ts_hiv[170 EXT_STRUCT_CTRL(tpat_data_ts_hi)] /* [-1,-1] */;

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
  uint32_t tpat_data_n;
  uint32_t tpat_data_tpat;
  uint32_t tpat_data_tpatv[170 /* tpat_data_tpat */];
  uint32_t tpat_data_trig;
  uint32_t tpat_data_trigv[170 /* tpat_data_trig */];
  uint32_t tpat_data_ts_lo;
  uint32_t tpat_data_ts_lov[170 /* tpat_data_ts_lo */];
  uint32_t tpat_data_ts_hi;
  uint32_t tpat_data_ts_hiv[170 /* tpat_data_ts_hi */];

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
                     tpat_data_n,                     UINT32,\
                    "tpat_data_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tpat_data_tpat,                  UINT32,\
                    "tpat_data_tpat",170,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tpat_data_tpatv,                 UINT32,\
                    "tpat_data_tpatv",                 "tpat_data_tpat",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tpat_data_trig,                  UINT32,\
                    "tpat_data_trig",170,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tpat_data_trigv,                 UINT32,\
                    "tpat_data_trigv",                 "tpat_data_trig",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tpat_data_ts_lo,                 UINT32,\
                    "tpat_data_ts_lo",170,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tpat_data_ts_lov,                UINT32,\
                    "tpat_data_ts_lov",                "tpat_data_ts_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tpat_data_ts_hi,                 UINT32,\
                    "tpat_data_ts_hi",170,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tpat_data_ts_hiv,                UINT32,\
                    "tpat_data_ts_hiv",                "tpat_data_ts_hi",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_EXT_H101_FRS_TPAT_H__*/

/*******************************************************/
