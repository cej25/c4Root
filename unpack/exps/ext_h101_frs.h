/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_EXT_H101_FRS_H__
#define __GUARD_H101_EXT_H101_FRS_H__

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
  uint32_t frs_crate_frs_v830_n /* [0,32] */;
  uint32_t frs_crate_frs_v830_nI[32 EXT_STRUCT_CTRL(frs_crate_frs_v830_n)] /* [1,32] */;
  uint32_t frs_crate_frs_v830_data[32 EXT_STRUCT_CTRL(frs_crate_frs_v830_n)] /* [-1,-1] */;
  uint32_t frs_crate_frs_v7x5_n /* [0,32] */;
  uint32_t frs_crate_frs_v7x5_nI[32 EXT_STRUCT_CTRL(frs_crate_frs_v7x5_n)] /* [1,32] */;
  uint32_t frs_crate_frs_v7x5_data[32 EXT_STRUCT_CTRL(frs_crate_frs_v7x5_n)] /* [0,65535] */;
  uint32_t frs_crate_frs_v7x5_channel /* [0,32] */;
  uint32_t frs_crate_frs_v7x5_channelI[32 EXT_STRUCT_CTRL(frs_crate_frs_v7x5_channel)] /* [1,32] */;
  uint32_t frs_crate_frs_v7x5_channelv[32 EXT_STRUCT_CTRL(frs_crate_frs_v7x5_channel)] /* [0,255] */;
  uint32_t frs_crate_frs_v7x5_geo /* [0,32] */;
  uint32_t frs_crate_frs_v7x5_geoI[32 EXT_STRUCT_CTRL(frs_crate_frs_v7x5_geo)] /* [1,32] */;
  uint32_t frs_crate_frs_v7x5_geov[32 EXT_STRUCT_CTRL(frs_crate_frs_v7x5_geo)] /* [0,255] */;

} EXT_STR_h101;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_onion_t
{
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
  uint32_t frs_crate_frs_v830_n;
  uint32_t frs_crate_frs_v830_nI[32 /* frs_crate_frs_v830_n */];
  uint32_t frs_crate_frs_v830_data[32 /* frs_crate_frs_v830_n */];
  uint32_t frs_crate_frs_v7x5_n;
  uint32_t frs_crate_frs_v7x5_nI[32 /* frs_crate_frs_v7x5_n */];
  uint32_t frs_crate_frs_v7x5_data[32 /* frs_crate_frs_v7x5_n */];
  uint32_t frs_crate_frs_v7x5_channel;
  uint32_t frs_crate_frs_v7x5_channelI[32 /* frs_crate_frs_v7x5_channel */];
  uint32_t frs_crate_frs_v7x5_channelv[32 /* frs_crate_frs_v7x5_channel */];
  uint32_t frs_crate_frs_v7x5_geo;
  uint32_t frs_crate_frs_v7x5_geoI[32 /* frs_crate_frs_v7x5_geo */];
  uint32_t frs_crate_frs_v7x5_geov[32 /* frs_crate_frs_v7x5_geo */];

} EXT_STR_h101_onion;

/*******************************************************/

#define EXT_STR_h101_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
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
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frs_crate_frs_v830_n,            UINT32,\
                    "frs_crate_frs_v830_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frs_crate_frs_v830_nI,           UINT32,\
                    "frs_crate_frs_v830_nI",           "frs_crate_frs_v830_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frs_crate_frs_v830_data,         UINT32,\
                    "frs_crate_frs_v830_data",         "frs_crate_frs_v830_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frs_crate_frs_v7x5_n,            UINT32,\
                    "frs_crate_frs_v7x5_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frs_crate_frs_v7x5_nI,           UINT32,\
                    "frs_crate_frs_v7x5_nI",           "frs_crate_frs_v7x5_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frs_crate_frs_v7x5_data,         UINT32,\
                    "frs_crate_frs_v7x5_data",         "frs_crate_frs_v7x5_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frs_crate_frs_v7x5_channel,      UINT32,\
                    "frs_crate_frs_v7x5_channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frs_crate_frs_v7x5_channelI,     UINT32,\
                    "frs_crate_frs_v7x5_channelI",     "frs_crate_frs_v7x5_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frs_crate_frs_v7x5_channelv,     UINT32,\
                    "frs_crate_frs_v7x5_channelv",     "frs_crate_frs_v7x5_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frs_crate_frs_v7x5_geo,          UINT32,\
                    "frs_crate_frs_v7x5_geo",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frs_crate_frs_v7x5_geoI,         UINT32,\
                    "frs_crate_frs_v7x5_geoI",         "frs_crate_frs_v7x5_geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frs_crate_frs_v7x5_geov,         UINT32,\
                    "frs_crate_frs_v7x5_geov",         "frs_crate_frs_v7x5_geo",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_EXT_H101_FRS_H__*/

/*******************************************************/
