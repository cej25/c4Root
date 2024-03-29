/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_FRSMAIN_EXT_H101_FRSMAIN_H__
#define __GUARD_H101_FRSMAIN_EXT_H101_FRSMAIN_H__

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

typedef struct EXT_STR_h101_frsmain_t
{
  /* UNPACK */
  uint32_t frsmain_spill_on_spillon /* [0,255] */;
  uint32_t frsmain_spill_off_spilloff /* [0,255] */;
  uint32_t frsmain_data_v830_n /* [0,32] */;
  uint32_t frsmain_data_v830_nI[32 EXT_STRUCT_CTRL(frsmain_data_v830_n)] /* [1,32] */;
  uint32_t frsmain_data_v830_data[32 EXT_STRUCT_CTRL(frsmain_data_v830_n)] /* [-1,-1] */;
  uint32_t frsmain_data_v792_nM /* [1,32] */;
  uint32_t frsmain_data_v792_nMI[32 EXT_STRUCT_CTRL(frsmain_data_v792_nM)] /* [1,32] */;
  uint32_t frsmain_data_v792_nME[32 EXT_STRUCT_CTRL(frsmain_data_v792_nM)] /* [1,1024] */;
  uint32_t frsmain_data_v792_n /* [0,1024] */;
  uint32_t frsmain_data_v792_data[1024 EXT_STRUCT_CTRL(frsmain_data_v792_n)] /* [-1,-1] */;
  uint32_t frsmain_data_v792_geo /* [0,255] */;
  uint32_t frsmain_data_v1290_nM /* [1,128] */;
  uint32_t frsmain_data_v1290_nMI[128 EXT_STRUCT_CTRL(frsmain_data_v1290_nM)] /* [1,128] */;
  uint32_t frsmain_data_v1290_nME[128 EXT_STRUCT_CTRL(frsmain_data_v1290_nM)] /* [1,16384] */;
  uint32_t frsmain_data_v1290_n /* [0,16384] */;
  uint32_t frsmain_data_v1290_data[16384 EXT_STRUCT_CTRL(frsmain_data_v1290_n)] /* [0,16777215] */;
  uint32_t frsmain_data_v1290_leadOrTrailM /* [1,128] */;
  uint32_t frsmain_data_v1290_leadOrTrailMI[128 EXT_STRUCT_CTRL(frsmain_data_v1290_leadOrTrailM)] /* [1,128] */;
  uint32_t frsmain_data_v1290_leadOrTrailME[128 EXT_STRUCT_CTRL(frsmain_data_v1290_leadOrTrailM)] /* [1,16384] */;
  uint32_t frsmain_data_v1290_leadOrTrail /* [0,16384] */;
  uint32_t frsmain_data_v1290_leadOrTrailv[16384 EXT_STRUCT_CTRL(frsmain_data_v1290_leadOrTrail)] /* [0,255] */;
  uint32_t frsmain_data_v1290_geo /* [0,255] */;

} EXT_STR_h101_frsmain;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_frsmain_onion_t
{
  /* UNPACK */
  uint32_t frsmain_spill_on_spillon;
  uint32_t frsmain_spill_off_spilloff;
  uint32_t frsmain_data_v830_n;
  uint32_t frsmain_data_v830_nI[32 /* frsmain_data_v830_n */];
  uint32_t frsmain_data_v830_data[32 /* frsmain_data_v830_n */];
  uint32_t frsmain_data_v792_nM;
  uint32_t frsmain_data_v792_nMI[32 /* frsmain_data_v792_nM */];
  uint32_t frsmain_data_v792_nME[32 /* frsmain_data_v792_nM */];
  uint32_t frsmain_data_v792_n;
  uint32_t frsmain_data_v792_data[1024 /* frsmain_data_v792_n */];
  uint32_t frsmain_data_v792_geo;
  uint32_t frsmain_data_v1290_nM;
  uint32_t frsmain_data_v1290_nMI[128 /* frsmain_data_v1290_nM */];
  uint32_t frsmain_data_v1290_nME[128 /* frsmain_data_v1290_nM */];
  uint32_t frsmain_data_v1290_n;
  uint32_t frsmain_data_v1290_data[16384 /* frsmain_data_v1290_n */];
  uint32_t frsmain_data_v1290_leadOrTrailM;
  uint32_t frsmain_data_v1290_leadOrTrailMI[128 /* frsmain_data_v1290_leadOrTrailM */];
  uint32_t frsmain_data_v1290_leadOrTrailME[128 /* frsmain_data_v1290_leadOrTrailM */];
  uint32_t frsmain_data_v1290_leadOrTrail;
  uint32_t frsmain_data_v1290_leadOrTrailv[16384 /* frsmain_data_v1290_leadOrTrail */];
  uint32_t frsmain_data_v1290_geo;

} EXT_STR_h101_frsmain_onion;

/*******************************************************/

#define EXT_STR_h101_frsmain_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmain_spill_on_spillon,        UINT32,\
                    "frsmain_spill_on_spillon",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmain_spill_off_spilloff,      UINT32,\
                    "frsmain_spill_off_spilloff",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v830_n,             UINT32,\
                    "frsmain_data_v830_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v830_nI,            UINT32,\
                    "frsmain_data_v830_nI",            "frsmain_data_v830_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v830_data,          UINT32,\
                    "frsmain_data_v830_data",          "frsmain_data_v830_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v792_nM,            UINT32,\
                    "frsmain_data_v792_nM",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v792_nMI,           UINT32,\
                    "frsmain_data_v792_nMI",           "frsmain_data_v792_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v792_nME,           UINT32,\
                    "frsmain_data_v792_nME",           "frsmain_data_v792_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v792_n,             UINT32,\
                    "frsmain_data_v792_n",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v792_data,          UINT32,\
                    "frsmain_data_v792_data",          "frsmain_data_v792_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v792_geo,           UINT32,\
                    "frsmain_data_v792_geo",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v1290_nM,           UINT32,\
                    "frsmain_data_v1290_nM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v1290_nMI,          UINT32,\
                    "frsmain_data_v1290_nMI",          "frsmain_data_v1290_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v1290_nME,          UINT32,\
                    "frsmain_data_v1290_nME",          "frsmain_data_v1290_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v1290_n,            UINT32,\
                    "frsmain_data_v1290_n",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v1290_data,         UINT32,\
                    "frsmain_data_v1290_data",         "frsmain_data_v1290_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v1290_leadOrTrailM, UINT32,\
                    "frsmain_data_v1290_leadOrTrailM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v1290_leadOrTrailMI,UINT32,\
                    "frsmain_data_v1290_leadOrTrailMI","frsmain_data_v1290_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v1290_leadOrTrailME,UINT32,\
                    "frsmain_data_v1290_leadOrTrailME","frsmain_data_v1290_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v1290_leadOrTrail,  UINT32,\
                    "frsmain_data_v1290_leadOrTrail",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v1290_leadOrTrailv, UINT32,\
                    "frsmain_data_v1290_leadOrTrailv", "frsmain_data_v1290_leadOrTrail",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v1290_geo,          UINT32,\
                    "frsmain_data_v1290_geo",255,0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FRSMAIN_EXT_H101_FRSMAIN_H__*/

/*******************************************************/
