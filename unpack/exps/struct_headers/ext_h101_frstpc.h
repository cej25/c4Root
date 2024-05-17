/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_FRSTPC_EXT_H101_FRSTPC_H__
#define __GUARD_H101_FRSTPC_EXT_H101_FRSTPC_H__

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

typedef struct EXT_STR_h101_frstpc_t
{
  /* UNPACK */
  uint32_t frstpc_be /* [-1,-1] */;
  uint32_t frstpc_spill_on_spillon /* [0,255] */;
  uint32_t frstpc_spill_off_spilloff /* [0,255] */;
  uint32_t frstpc_data_v775_n /* [0,32] */;
  uint32_t frstpc_data_v775_nI[32 EXT_STRUCT_CTRL(frstpc_data_v775_n)] /* [1,32] */;
  uint32_t frstpc_data_v775_data[32 EXT_STRUCT_CTRL(frstpc_data_v775_n)] /* [0,16777215] */;
  uint32_t frstpc_data_v775_channel /* [0,32] */;
  uint32_t frstpc_data_v775_channelI[32 EXT_STRUCT_CTRL(frstpc_data_v775_channel)] /* [1,32] */;
  uint32_t frstpc_data_v775_channelv[32 EXT_STRUCT_CTRL(frstpc_data_v775_channel)] /* [0,255] */;
  uint32_t frstpc_data_v775_geo /* [0,32] */;
  uint32_t frstpc_data_v775_geoI[32 EXT_STRUCT_CTRL(frstpc_data_v775_geo)] /* [1,32] */;
  uint32_t frstpc_data_v775_geov[32 EXT_STRUCT_CTRL(frstpc_data_v775_geo)] /* [0,255] */;
  uint32_t frstpc_data_v785_n /* [0,32] */;
  uint32_t frstpc_data_v785_nI[32 EXT_STRUCT_CTRL(frstpc_data_v785_n)] /* [1,32] */;
  uint32_t frstpc_data_v785_data[32 EXT_STRUCT_CTRL(frstpc_data_v785_n)] /* [0,16777215] */;
  uint32_t frstpc_data_v785_channel /* [0,32] */;
  uint32_t frstpc_data_v785_channelI[32 EXT_STRUCT_CTRL(frstpc_data_v785_channel)] /* [1,32] */;
  uint32_t frstpc_data_v785_channelv[32 EXT_STRUCT_CTRL(frstpc_data_v785_channel)] /* [0,255] */;
  uint32_t frstpc_data_v785_geo /* [0,32] */;
  uint32_t frstpc_data_v785_geoI[32 EXT_STRUCT_CTRL(frstpc_data_v785_geo)] /* [1,32] */;
  uint32_t frstpc_data_v785_geov[32 EXT_STRUCT_CTRL(frstpc_data_v785_geo)] /* [0,255] */;
  uint32_t frstpc_data_v1190_nM /* [1,128] */;
  uint32_t frstpc_data_v1190_nMI[128 EXT_STRUCT_CTRL(frstpc_data_v1190_nM)] /* [1,128] */;
  uint32_t frstpc_data_v1190_nME[128 EXT_STRUCT_CTRL(frstpc_data_v1190_nM)] /* [1,16384] */;
  uint32_t frstpc_data_v1190_n /* [0,16384] */;
  uint32_t frstpc_data_v1190_data[16384 EXT_STRUCT_CTRL(frstpc_data_v1190_n)] /* [0,16777215] */;
  uint32_t frstpc_data_v1190_leadOrTrailM /* [1,128] */;
  uint32_t frstpc_data_v1190_leadOrTrailMI[128 EXT_STRUCT_CTRL(frstpc_data_v1190_leadOrTrailM)] /* [1,128] */;
  uint32_t frstpc_data_v1190_leadOrTrailME[128 EXT_STRUCT_CTRL(frstpc_data_v1190_leadOrTrailM)] /* [1,16384] */;
  uint32_t frstpc_data_v1190_leadOrTrail /* [0,16384] */;
  uint32_t frstpc_data_v1190_leadOrTrailv[16384 EXT_STRUCT_CTRL(frstpc_data_v1190_leadOrTrail)] /* [0,255] */;
  uint32_t frstpc_data_v1190_geo /* [0,255] */;

} EXT_STR_h101_frstpc;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_frstpc_onion_t
{
  /* UNPACK */
  uint32_t frstpc_be;
  uint32_t frstpc_spill_on_spillon;
  uint32_t frstpc_spill_off_spilloff;
  uint32_t frstpc_data_v775_n;
  uint32_t frstpc_data_v775_nI[32 /* frstpc_data_v775_n */];
  uint32_t frstpc_data_v775_data[32 /* frstpc_data_v775_n */];
  uint32_t frstpc_data_v775_channel;
  uint32_t frstpc_data_v775_channelI[32 /* frstpc_data_v775_channel */];
  uint32_t frstpc_data_v775_channelv[32 /* frstpc_data_v775_channel */];
  uint32_t frstpc_data_v775_geo;
  uint32_t frstpc_data_v775_geoI[32 /* frstpc_data_v775_geo */];
  uint32_t frstpc_data_v775_geov[32 /* frstpc_data_v775_geo */];
  uint32_t frstpc_data_v785_n;
  uint32_t frstpc_data_v785_nI[32 /* frstpc_data_v785_n */];
  uint32_t frstpc_data_v785_data[32 /* frstpc_data_v785_n */];
  uint32_t frstpc_data_v785_channel;
  uint32_t frstpc_data_v785_channelI[32 /* frstpc_data_v785_channel */];
  uint32_t frstpc_data_v785_channelv[32 /* frstpc_data_v785_channel */];
  uint32_t frstpc_data_v785_geo;
  uint32_t frstpc_data_v785_geoI[32 /* frstpc_data_v785_geo */];
  uint32_t frstpc_data_v785_geov[32 /* frstpc_data_v785_geo */];
  uint32_t frstpc_data_v1190_nM;
  uint32_t frstpc_data_v1190_nMI[128 /* frstpc_data_v1190_nM */];
  uint32_t frstpc_data_v1190_nME[128 /* frstpc_data_v1190_nM */];
  uint32_t frstpc_data_v1190_n;
  uint32_t frstpc_data_v1190_data[16384 /* frstpc_data_v1190_n */];
  uint32_t frstpc_data_v1190_leadOrTrailM;
  uint32_t frstpc_data_v1190_leadOrTrailMI[128 /* frstpc_data_v1190_leadOrTrailM */];
  uint32_t frstpc_data_v1190_leadOrTrailME[128 /* frstpc_data_v1190_leadOrTrailM */];
  uint32_t frstpc_data_v1190_leadOrTrail;
  uint32_t frstpc_data_v1190_leadOrTrailv[16384 /* frstpc_data_v1190_leadOrTrail */];
  uint32_t frstpc_data_v1190_geo;

} EXT_STR_h101_frstpc_onion;

/*******************************************************/

#define EXT_STR_h101_frstpc_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     frstpc_be,                       UINT32,\
                    "frstpc_be",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpc_spill_on_spillon,         UINT32,\
                    "frstpc_spill_on_spillon",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpc_spill_off_spilloff,       UINT32,\
                    "frstpc_spill_off_spilloff",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v775_n,              UINT32,\
                    "frstpc_data_v775_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v775_nI,             UINT32,\
                    "frstpc_data_v775_nI",             "frstpc_data_v775_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v775_data,           UINT32,\
                    "frstpc_data_v775_data",           "frstpc_data_v775_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v775_channel,        UINT32,\
                    "frstpc_data_v775_channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v775_channelI,       UINT32,\
                    "frstpc_data_v775_channelI",       "frstpc_data_v775_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v775_channelv,       UINT32,\
                    "frstpc_data_v775_channelv",       "frstpc_data_v775_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v775_geo,            UINT32,\
                    "frstpc_data_v775_geo",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v775_geoI,           UINT32,\
                    "frstpc_data_v775_geoI",           "frstpc_data_v775_geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v775_geov,           UINT32,\
                    "frstpc_data_v775_geov",           "frstpc_data_v775_geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v785_n,              UINT32,\
                    "frstpc_data_v785_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v785_nI,             UINT32,\
                    "frstpc_data_v785_nI",             "frstpc_data_v785_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v785_data,           UINT32,\
                    "frstpc_data_v785_data",           "frstpc_data_v785_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v785_channel,        UINT32,\
                    "frstpc_data_v785_channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v785_channelI,       UINT32,\
                    "frstpc_data_v785_channelI",       "frstpc_data_v785_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v785_channelv,       UINT32,\
                    "frstpc_data_v785_channelv",       "frstpc_data_v785_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v785_geo,            UINT32,\
                    "frstpc_data_v785_geo",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v785_geoI,           UINT32,\
                    "frstpc_data_v785_geoI",           "frstpc_data_v785_geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v785_geov,           UINT32,\
                    "frstpc_data_v785_geov",           "frstpc_data_v785_geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v1190_nM,            UINT32,\
                    "frstpc_data_v1190_nM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v1190_nMI,           UINT32,\
                    "frstpc_data_v1190_nMI",           "frstpc_data_v1190_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v1190_nME,           UINT32,\
                    "frstpc_data_v1190_nME",           "frstpc_data_v1190_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v1190_n,             UINT32,\
                    "frstpc_data_v1190_n",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v1190_data,          UINT32,\
                    "frstpc_data_v1190_data",          "frstpc_data_v1190_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v1190_leadOrTrailM,  UINT32,\
                    "frstpc_data_v1190_leadOrTrailM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v1190_leadOrTrailMI, UINT32,\
                    "frstpc_data_v1190_leadOrTrailMI", "frstpc_data_v1190_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v1190_leadOrTrailME, UINT32,\
                    "frstpc_data_v1190_leadOrTrailME", "frstpc_data_v1190_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v1190_leadOrTrail,   UINT32,\
                    "frstpc_data_v1190_leadOrTrail",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v1190_leadOrTrailv,  UINT32,\
                    "frstpc_data_v1190_leadOrTrailv",  "frstpc_data_v1190_leadOrTrail",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v1190_geo,           UINT32,\
                    "frstpc_data_v1190_geo",255,0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FRSTPC_EXT_H101_FRSTPC_H__*/

/*******************************************************/
