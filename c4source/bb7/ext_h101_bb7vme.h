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
  uint32_t bbseven_v7x51geo /* [0,255] */;
  uint32_t bbseven_v7x51n /* [0,32] */;
  uint32_t bbseven_v7x51nI[32 EXT_STRUCT_CTRL(bbseven_v7x51n)] /* [1,32] */;
  uint32_t bbseven_v7x51data[32 EXT_STRUCT_CTRL(bbseven_v7x51n)] /* [0,65535] */;
  uint32_t bbseven_v7x52geo /* [0,255] */;
  uint32_t bbseven_v7x52n /* [0,32] */;
  uint32_t bbseven_v7x52nI[32 EXT_STRUCT_CTRL(bbseven_v7x52n)] /* [1,32] */;
  uint32_t bbseven_v7x52data[32 EXT_STRUCT_CTRL(bbseven_v7x52n)] /* [0,65535] */;
  uint32_t bbseven_v7x53geo /* [0,255] */;
  uint32_t bbseven_v7x53n /* [0,32] */;
  uint32_t bbseven_v7x53nI[32 EXT_STRUCT_CTRL(bbseven_v7x53n)] /* [1,32] */;
  uint32_t bbseven_v7x53data[32 EXT_STRUCT_CTRL(bbseven_v7x53n)] /* [0,65535] */;
  uint32_t bbseven_v7x54geo /* [0,255] */;
  uint32_t bbseven_v7x54n /* [0,32] */;
  uint32_t bbseven_v7x54nI[32 EXT_STRUCT_CTRL(bbseven_v7x54n)] /* [1,32] */;
  uint32_t bbseven_v7x54data[32 EXT_STRUCT_CTRL(bbseven_v7x54n)] /* [0,65535] */;
  uint32_t bbseven_v1290_geo /* [0,255] */;
  uint32_t bbseven_v1290_measurement_nM /* [1,128] */;
  uint32_t bbseven_v1290_measurement_nMI[128 EXT_STRUCT_CTRL(bbseven_v1290_measurement_nM)] /* [1,128] */;
  uint32_t bbseven_v1290_measurement_nME[128 EXT_STRUCT_CTRL(bbseven_v1290_measurement_nM)] /* [1,16384] */;
  uint32_t bbseven_v1290_measurement_n /* [0,16384] */;
  uint32_t bbseven_v1290_measurement_data[16384 EXT_STRUCT_CTRL(bbseven_v1290_measurement_n)] /* [0,16777215] */;
  uint32_t bbseven_v1290_measurement_leadOrTrailM /* [1,128] */;
  uint32_t bbseven_v1290_measurement_leadOrTrailMI[128 EXT_STRUCT_CTRL(bbseven_v1290_measurement_leadOrTrailM)] /* [1,128] */;
  uint32_t bbseven_v1290_measurement_leadOrTrailME[128 EXT_STRUCT_CTRL(bbseven_v1290_measurement_leadOrTrailM)] /* [1,16384] */;
  uint32_t bbseven_v1290_measurement_leadOrTrail /* [0,16384] */;
  uint32_t bbseven_v1290_measurement_leadOrTrailv[16384 EXT_STRUCT_CTRL(bbseven_v1290_measurement_leadOrTrail)] /* [0,255] */;

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
  uint32_t bbseven_v7x51geo;
  uint32_t bbseven_v7x51n;
  uint32_t bbseven_v7x51nI[32 /* bbseven_v7x51n */];
  uint32_t bbseven_v7x51data[32 /* bbseven_v7x51n */];
  uint32_t bbseven_v7x52geo;
  uint32_t bbseven_v7x52n;
  uint32_t bbseven_v7x52nI[32 /* bbseven_v7x52n */];
  uint32_t bbseven_v7x52data[32 /* bbseven_v7x52n */];
  uint32_t bbseven_v7x53geo;
  uint32_t bbseven_v7x53n;
  uint32_t bbseven_v7x53nI[32 /* bbseven_v7x53n */];
  uint32_t bbseven_v7x53data[32 /* bbseven_v7x53n */];
  uint32_t bbseven_v7x54geo;
  uint32_t bbseven_v7x54n;
  uint32_t bbseven_v7x54nI[32 /* bbseven_v7x54n */];
  uint32_t bbseven_v7x54data[32 /* bbseven_v7x54n */];
  uint32_t bbseven_v1290_geo;
  uint32_t bbseven_v1290_measurement_nM;
  uint32_t bbseven_v1290_measurement_nMI[128 /* bbseven_v1290_measurement_nM */];
  uint32_t bbseven_v1290_measurement_nME[128 /* bbseven_v1290_measurement_nM */];
  uint32_t bbseven_v1290_measurement_n;
  uint32_t bbseven_v1290_measurement_data[16384 /* bbseven_v1290_measurement_n */];
  uint32_t bbseven_v1290_measurement_leadOrTrailM;
  uint32_t bbseven_v1290_measurement_leadOrTrailMI[128 /* bbseven_v1290_measurement_leadOrTrailM */];
  uint32_t bbseven_v1290_measurement_leadOrTrailME[128 /* bbseven_v1290_measurement_leadOrTrailM */];
  uint32_t bbseven_v1290_measurement_leadOrTrail;
  uint32_t bbseven_v1290_measurement_leadOrTrailv[16384 /* bbseven_v1290_measurement_leadOrTrail */];

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
                     bbseven_v7x51geo,                UINT32,\
                    "bbseven_v7x51geo",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x51n,                  UINT32,\
                    "bbseven_v7x51n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x51nI,                 UINT32,\
                    "bbseven_v7x51nI",                 "bbseven_v7x51n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x51data,               UINT32,\
                    "bbseven_v7x51data",               "bbseven_v7x51n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x52geo,                UINT32,\
                    "bbseven_v7x52geo",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x52n,                  UINT32,\
                    "bbseven_v7x52n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x52nI,                 UINT32,\
                    "bbseven_v7x52nI",                 "bbseven_v7x52n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x52data,               UINT32,\
                    "bbseven_v7x52data",               "bbseven_v7x52n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x53geo,                UINT32,\
                    "bbseven_v7x53geo",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x53n,                  UINT32,\
                    "bbseven_v7x53n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x53nI,                 UINT32,\
                    "bbseven_v7x53nI",                 "bbseven_v7x53n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x53data,               UINT32,\
                    "bbseven_v7x53data",               "bbseven_v7x53n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x54geo,                UINT32,\
                    "bbseven_v7x54geo",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x54n,                  UINT32,\
                    "bbseven_v7x54n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x54nI,                 UINT32,\
                    "bbseven_v7x54nI",                 "bbseven_v7x54n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v7x54data,               UINT32,\
                    "bbseven_v7x54data",               "bbseven_v7x54n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_geo,               UINT32,\
                    "bbseven_v1290_geo",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_measurement_nM,    UINT32,\
                    "bbseven_v1290_measurement_nM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_measurement_nMI,   UINT32,\
                    "bbseven_v1290_measurement_nMI",   "bbseven_v1290_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_measurement_nME,   UINT32,\
                    "bbseven_v1290_measurement_nME",   "bbseven_v1290_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_measurement_n,     UINT32,\
                    "bbseven_v1290_measurement_n",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_measurement_data,  UINT32,\
                    "bbseven_v1290_measurement_data",  "bbseven_v1290_measurement_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_measurement_leadOrTrailM,UINT32,\
                    "bbseven_v1290_measurement_leadOrTrailM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_measurement_leadOrTrailMI,UINT32,\
                    "bbseven_v1290_measurement_leadOrTrailMI","bbseven_v1290_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_measurement_leadOrTrailME,UINT32,\
                    "bbseven_v1290_measurement_leadOrTrailME","bbseven_v1290_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_measurement_leadOrTrail,UINT32,\
                    "bbseven_v1290_measurement_leadOrTrail",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbseven_v1290_measurement_leadOrTrailv,UINT32,\
                    "bbseven_v1290_measurement_leadOrTrailv","bbseven_v1290_measurement_leadOrTrail",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_BB7VME_EXT_H101_BB7VME_H__*/

/*******************************************************/
