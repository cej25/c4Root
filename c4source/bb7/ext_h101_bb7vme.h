/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_BB7VME_EXT_H101_BB7VME_H__
#define __GUARD_H101_BB7VME_EXT_H101_BB7VME_H__

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

typedef struct EXT_STR_h101_bb7vme_t
{
  /* UNPACK */
  uint32_t bbseven_ts_subsystem_id /* [0,65535] */;
  uint32_t bbseven_ts_t1 /* [0,65535] */;
  uint32_t bbseven_ts_t2 /* [0,65535] */;
  uint32_t bbseven_ts_t3 /* [0,65535] */;
  uint32_t bbseven_ts_t4 /* [0,65535] */;
  uint32_t bbseven_v7x5_module1n /* [0,32] */;
  uint32_t bbseven_v7x5_module1nI[32 EXT_STRUCT_CTRL(bbseven_v7x5_module1n)] /* [1,32] */;
  uint32_t bbseven_v7x5_module1data[32 EXT_STRUCT_CTRL(bbseven_v7x5_module1n)] /* [0,16777215] */;
  uint32_t bbseven_v7x5_module1channel /* [0,32] */;
  uint32_t bbseven_v7x5_module1channelI[32 EXT_STRUCT_CTRL(bbseven_v7x5_module1channel)] /* [1,32] */;
  uint32_t bbseven_v7x5_module1channelv[32 EXT_STRUCT_CTRL(bbseven_v7x5_module1channel)] /* [0,255] */;
  uint32_t bbseven_v7x5_module1geo /* [0,32] */;
  uint32_t bbseven_v7x5_module1geoI[32 EXT_STRUCT_CTRL(bbseven_v7x5_module1geo)] /* [1,32] */;
  uint32_t bbseven_v7x5_module1geov[32 EXT_STRUCT_CTRL(bbseven_v7x5_module1geo)] /* [0,255] */;
  uint32_t bbseven_v7x5_module2n /* [0,32] */;
  uint32_t bbseven_v7x5_module2nI[32 EXT_STRUCT_CTRL(bbseven_v7x5_module2n)] /* [1,32] */;
  uint32_t bbseven_v7x5_module2data[32 EXT_STRUCT_CTRL(bbseven_v7x5_module2n)] /* [0,16777215] */;
  uint32_t bbseven_v7x5_module2channel /* [0,32] */;
  uint32_t bbseven_v7x5_module2channelI[32 EXT_STRUCT_CTRL(bbseven_v7x5_module2channel)] /* [1,32] */;
  uint32_t bbseven_v7x5_module2channelv[32 EXT_STRUCT_CTRL(bbseven_v7x5_module2channel)] /* [0,255] */;
  uint32_t bbseven_v7x5_module2geo /* [0,32] */;
  uint32_t bbseven_v7x5_module2geoI[32 EXT_STRUCT_CTRL(bbseven_v7x5_module2geo)] /* [1,32] */;
  uint32_t bbseven_v7x5_module2geov[32 EXT_STRUCT_CTRL(bbseven_v7x5_module2geo)] /* [0,255] */;
  uint32_t bbseven_v7x5_module3n /* [0,32] */;
  uint32_t bbseven_v7x5_module3nI[32 EXT_STRUCT_CTRL(bbseven_v7x5_module3n)] /* [1,32] */;
  uint32_t bbseven_v7x5_module3data[32 EXT_STRUCT_CTRL(bbseven_v7x5_module3n)] /* [0,16777215] */;
  uint32_t bbseven_v7x5_module3channel /* [0,32] */;
  uint32_t bbseven_v7x5_module3channelI[32 EXT_STRUCT_CTRL(bbseven_v7x5_module3channel)] /* [1,32] */;
  uint32_t bbseven_v7x5_module3channelv[32 EXT_STRUCT_CTRL(bbseven_v7x5_module3channel)] /* [0,255] */;
  uint32_t bbseven_v7x5_module3geo /* [0,32] */;
  uint32_t bbseven_v7x5_module3geoI[32 EXT_STRUCT_CTRL(bbseven_v7x5_module3geo)] /* [1,32] */;
  uint32_t bbseven_v7x5_module3geov[32 EXT_STRUCT_CTRL(bbseven_v7x5_module3geo)] /* [0,255] */;
  uint32_t bbseven_v7x5_module4n /* [0,32] */;
  uint32_t bbseven_v7x5_module4nI[32 EXT_STRUCT_CTRL(bbseven_v7x5_module4n)] /* [1,32] */;
  uint32_t bbseven_v7x5_module4data[32 EXT_STRUCT_CTRL(bbseven_v7x5_module4n)] /* [0,16777215] */;
  uint32_t bbseven_v7x5_module4channel /* [0,32] */;
  uint32_t bbseven_v7x5_module4channelI[32 EXT_STRUCT_CTRL(bbseven_v7x5_module4channel)] /* [1,32] */;
  uint32_t bbseven_v7x5_module4channelv[32 EXT_STRUCT_CTRL(bbseven_v7x5_module4channel)] /* [0,255] */;
  uint32_t bbseven_v7x5_module4geo /* [0,32] */;
  uint32_t bbseven_v7x5_module4geoI[32 EXT_STRUCT_CTRL(bbseven_v7x5_module4geo)] /* [1,32] */;
  uint32_t bbseven_v7x5_module4geov[32 EXT_STRUCT_CTRL(bbseven_v7x5_module4geo)] /* [0,255] */;
  uint32_t bbseven_v1290_module_nM /* [1,128] */;
  uint32_t bbseven_v1290_module_nMI[128 EXT_STRUCT_CTRL(bbseven_v1290_module_nM)] /* [1,128] */;
  uint32_t bbseven_v1290_module_nME[128 EXT_STRUCT_CTRL(bbseven_v1290_module_nM)] /* [1,16384] */;
  uint32_t bbseven_v1290_module_n /* [0,16384] */;
  uint32_t bbseven_v1290_module_data[16384 EXT_STRUCT_CTRL(bbseven_v1290_module_n)] /* [0,16777215] */;
  uint32_t bbseven_v1290_module_leadOrTrailM /* [1,128] */;
  uint32_t bbseven_v1290_module_leadOrTrailMI[128 EXT_STRUCT_CTRL(bbseven_v1290_module_leadOrTrailM)] /* [1,128] */;
  uint32_t bbseven_v1290_module_leadOrTrailME[128 EXT_STRUCT_CTRL(bbseven_v1290_module_leadOrTrailM)] /* [1,16384] */;
  uint32_t bbseven_v1290_module_leadOrTrail /* [0,16384] */;
  uint32_t bbseven_v1290_module_leadOrTrailv[16384 EXT_STRUCT_CTRL(bbseven_v1290_module_leadOrTrail)] /* [0,255] */;
  uint32_t bbseven_v1290_module_geo /* [0,255] */;

} EXT_STR_h101_bb7vme;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_bb7vme_onion_t
{
  /* UNPACK */
  uint32_t bbseven_ts_subsystem_id;
  uint32_t bbseven_ts_t[4];
  uint32_t bbseven_v7x5_module1n;
  uint32_t bbseven_v7x5_module1nI[32 /* bbseven_v7x5_module1n */];
  uint32_t bbseven_v7x5_module1data[32 /* bbseven_v7x5_module1n */];
  uint32_t bbseven_v7x5_module1channel;
  uint32_t bbseven_v7x5_module1channelI[32 /* bbseven_v7x5_module1channel */];
  uint32_t bbseven_v7x5_module1channelv[32 /* bbseven_v7x5_module1channel */];
  uint32_t bbseven_v7x5_module1geo;
  uint32_t bbseven_v7x5_module1geoI[32 /* bbseven_v7x5_module1geo */];
  uint32_t bbseven_v7x5_module1geov[32 /* bbseven_v7x5_module1geo */];
  uint32_t bbseven_v7x5_module2n;
  uint32_t bbseven_v7x5_module2nI[32 /* bbseven_v7x5_module2n */];
  uint32_t bbseven_v7x5_module2data[32 /* bbseven_v7x5_module2n */];
  uint32_t bbseven_v7x5_module2channel;
  uint32_t bbseven_v7x5_module2channelI[32 /* bbseven_v7x5_module2channel */];
  uint32_t bbseven_v7x5_module2channelv[32 /* bbseven_v7x5_module2channel */];
  uint32_t bbseven_v7x5_module2geo;
  uint32_t bbseven_v7x5_module2geoI[32 /* bbseven_v7x5_module2geo */];
  uint32_t bbseven_v7x5_module2geov[32 /* bbseven_v7x5_module2geo */];
  uint32_t bbseven_v7x5_module3n;
  uint32_t bbseven_v7x5_module3nI[32 /* bbseven_v7x5_module3n */];
  uint32_t bbseven_v7x5_module3data[32 /* bbseven_v7x5_module3n */];
  uint32_t bbseven_v7x5_module3channel;
  uint32_t bbseven_v7x5_module3channelI[32 /* bbseven_v7x5_module3channel */];
  uint32_t bbseven_v7x5_module3channelv[32 /* bbseven_v7x5_module3channel */];
  uint32_t bbseven_v7x5_module3geo;
  uint32_t bbseven_v7x5_module3geoI[32 /* bbseven_v7x5_module3geo */];
  uint32_t bbseven_v7x5_module3geov[32 /* bbseven_v7x5_module3geo */];
  uint32_t bbseven_v7x5_module4n;
  uint32_t bbseven_v7x5_module4nI[32 /* bbseven_v7x5_module4n */];
  uint32_t bbseven_v7x5_module4data[32 /* bbseven_v7x5_module4n */];
  uint32_t bbseven_v7x5_module4channel;
  uint32_t bbseven_v7x5_module4channelI[32 /* bbseven_v7x5_module4channel */];
  uint32_t bbseven_v7x5_module4channelv[32 /* bbseven_v7x5_module4channel */];
  uint32_t bbseven_v7x5_module4geo;
  uint32_t bbseven_v7x5_module4geoI[32 /* bbseven_v7x5_module4geo */];
  uint32_t bbseven_v7x5_module4geov[32 /* bbseven_v7x5_module4geo */];
  uint32_t bbseven_v1290_module_nM;
  uint32_t bbseven_v1290_module_nMI[128 /* bbseven_v1290_module_nM */];
  uint32_t bbseven_v1290_module_nME[128 /* bbseven_v1290_module_nM */];
  uint32_t bbseven_v1290_module_n;
  uint32_t bbseven_v1290_module_data[16384 /* bbseven_v1290_module_n */];
  uint32_t bbseven_v1290_module_leadOrTrailM;
  uint32_t bbseven_v1290_module_leadOrTrailMI[128 /* bbseven_v1290_module_leadOrTrailM */];
  uint32_t bbseven_v1290_module_leadOrTrailME[128 /* bbseven_v1290_module_leadOrTrailM */];
  uint32_t bbseven_v1290_module_leadOrTrail;
  uint32_t bbseven_v1290_module_leadOrTrailv[16384 /* bbseven_v1290_module_leadOrTrail */];
  uint32_t bbseven_v1290_module_geo;

} EXT_STR_h101_bb7vme_onion;

/*******************************************************/

#define EXT_STR_h101_bb7vme_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_ts_subsystem_id,         UINT32,\
                    "bbseven_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_ts_t1,                   UINT32,\
                    "bbseven_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_ts_t2,                   UINT32,\
                    "bbseven_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_ts_t3,                   UINT32,\
                    "bbseven_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_ts_t4,                   UINT32,\
                    "bbseven_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module1n,           UINT32,\
                    "bbseven_v7x5_module1n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module1nI,          UINT32,\
                    "bbseven_v7x5_module1nI",          "bbseven_v7x5_module1n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module1data,        UINT32,\
                    "bbseven_v7x5_module1data",        "bbseven_v7x5_module1n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module1channel,     UINT32,\
                    "bbseven_v7x5_module1channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module1channelI,    UINT32,\
                    "bbseven_v7x5_module1channelI",    "bbseven_v7x5_module1channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module1channelv,    UINT32,\
                    "bbseven_v7x5_module1channelv",    "bbseven_v7x5_module1channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module1geo,         UINT32,\
                    "bbseven_v7x5_module1geo",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module1geoI,        UINT32,\
                    "bbseven_v7x5_module1geoI",        "bbseven_v7x5_module1geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module1geov,        UINT32,\
                    "bbseven_v7x5_module1geov",        "bbseven_v7x5_module1geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module2n,           UINT32,\
                    "bbseven_v7x5_module2n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module2nI,          UINT32,\
                    "bbseven_v7x5_module2nI",          "bbseven_v7x5_module2n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module2data,        UINT32,\
                    "bbseven_v7x5_module2data",        "bbseven_v7x5_module2n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module2channel,     UINT32,\
                    "bbseven_v7x5_module2channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module2channelI,    UINT32,\
                    "bbseven_v7x5_module2channelI",    "bbseven_v7x5_module2channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module2channelv,    UINT32,\
                    "bbseven_v7x5_module2channelv",    "bbseven_v7x5_module2channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module2geo,         UINT32,\
                    "bbseven_v7x5_module2geo",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module2geoI,        UINT32,\
                    "bbseven_v7x5_module2geoI",        "bbseven_v7x5_module2geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module2geov,        UINT32,\
                    "bbseven_v7x5_module2geov",        "bbseven_v7x5_module2geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module3n,           UINT32,\
                    "bbseven_v7x5_module3n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module3nI,          UINT32,\
                    "bbseven_v7x5_module3nI",          "bbseven_v7x5_module3n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module3data,        UINT32,\
                    "bbseven_v7x5_module3data",        "bbseven_v7x5_module3n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module3channel,     UINT32,\
                    "bbseven_v7x5_module3channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module3channelI,    UINT32,\
                    "bbseven_v7x5_module3channelI",    "bbseven_v7x5_module3channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module3channelv,    UINT32,\
                    "bbseven_v7x5_module3channelv",    "bbseven_v7x5_module3channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module3geo,         UINT32,\
                    "bbseven_v7x5_module3geo",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module3geoI,        UINT32,\
                    "bbseven_v7x5_module3geoI",        "bbseven_v7x5_module3geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module3geov,        UINT32,\
                    "bbseven_v7x5_module3geov",        "bbseven_v7x5_module3geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module4n,           UINT32,\
                    "bbseven_v7x5_module4n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module4nI,          UINT32,\
                    "bbseven_v7x5_module4nI",          "bbseven_v7x5_module4n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module4data,        UINT32,\
                    "bbseven_v7x5_module4data",        "bbseven_v7x5_module4n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module4channel,     UINT32,\
                    "bbseven_v7x5_module4channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module4channelI,    UINT32,\
                    "bbseven_v7x5_module4channelI",    "bbseven_v7x5_module4channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module4channelv,    UINT32,\
                    "bbseven_v7x5_module4channelv",    "bbseven_v7x5_module4channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module4geo,         UINT32,\
                    "bbseven_v7x5_module4geo",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module4geoI,        UINT32,\
                    "bbseven_v7x5_module4geoI",        "bbseven_v7x5_module4geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x5_module4geov,        UINT32,\
                    "bbseven_v7x5_module4geov",        "bbseven_v7x5_module4geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_module_nM,         UINT32,\
                    "bbseven_v1290_module_nM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_module_nMI,        UINT32,\
                    "bbseven_v1290_module_nMI",        "bbseven_v1290_module_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_module_nME,        UINT32,\
                    "bbseven_v1290_module_nME",        "bbseven_v1290_module_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_module_n,          UINT32,\
                    "bbseven_v1290_module_n",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_module_data,       UINT32,\
                    "bbseven_v1290_module_data",       "bbseven_v1290_module_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_module_leadOrTrailM,UINT32,\
                    "bbseven_v1290_module_leadOrTrailM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_module_leadOrTrailMI,UINT32,\
                    "bbseven_v1290_module_leadOrTrailMI","bbseven_v1290_module_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_module_leadOrTrailME,UINT32,\
                    "bbseven_v1290_module_leadOrTrailME","bbseven_v1290_module_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_module_leadOrTrail,UINT32,\
                    "bbseven_v1290_module_leadOrTrail",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_module_leadOrTrailv,UINT32,\
                    "bbseven_v1290_module_leadOrTrailv","bbseven_v1290_module_leadOrTrail",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_module_geo,        UINT32,\
                    "bbseven_v1290_module_geo",255,0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_BB7VME_EXT_H101_BB7VME_H__*/

/*******************************************************/
