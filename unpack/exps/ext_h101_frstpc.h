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
  uint32_t frstpc_data_v785_n /* [0,32] */;
  uint32_t frstpc_data_v785_nI[32 EXT_STRUCT_CTRL(frstpc_data_v785_n)] /* [1,32] */;
  uint32_t frstpc_data_v785_data[32 EXT_STRUCT_CTRL(frstpc_data_v785_n)] /* [0,16777215] */;
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
  /* RAW */
  uint32_t TPC_ADC1 /* [0,32] */;
  uint32_t TPC_ADC1I[32 EXT_STRUCT_CTRL(TPC_ADC1)] /* [1,32] */;
  uint32_t TPC_ADC1v[32 EXT_STRUCT_CTRL(TPC_ADC1)] /* [0,16777215] */;
  uint32_t TPC_ADC2 /* [0,32] */;
  uint32_t TPC_ADC2I[32 EXT_STRUCT_CTRL(TPC_ADC2)] /* [1,32] */;
  uint32_t TPC_ADC2v[32 EXT_STRUCT_CTRL(TPC_ADC2)] /* [0,16777215] */;
  uint32_t TPC_ADC3 /* [0,32] */;
  uint32_t TPC_ADC3I[32 EXT_STRUCT_CTRL(TPC_ADC3)] /* [1,32] */;
  uint32_t TPC_ADC3v[32 EXT_STRUCT_CTRL(TPC_ADC3)] /* [0,16777215] */;
  uint32_t TPC_ADC4 /* [0,32] */;
  uint32_t TPC_ADC4I[32 EXT_STRUCT_CTRL(TPC_ADC4)] /* [1,32] */;
  uint32_t TPC_ADC4v[32 EXT_STRUCT_CTRL(TPC_ADC4)] /* [0,16777215] */;
  uint32_t TPC_ADC5 /* [0,32] */;
  uint32_t TPC_ADC5I[32 EXT_STRUCT_CTRL(TPC_ADC5)] /* [1,32] */;
  uint32_t TPC_ADC5v[32 EXT_STRUCT_CTRL(TPC_ADC5)] /* [0,16777215] */;
  uint32_t TPC_ADC6 /* [0,32] */;
  uint32_t TPC_ADC6I[32 EXT_STRUCT_CTRL(TPC_ADC6)] /* [1,32] */;
  uint32_t TPC_ADC6v[32 EXT_STRUCT_CTRL(TPC_ADC6)] /* [0,16777215] */;
  uint32_t TPC_ADC7 /* [0,32] */;
  uint32_t TPC_ADC7I[32 EXT_STRUCT_CTRL(TPC_ADC7)] /* [1,32] */;
  uint32_t TPC_ADC7v[32 EXT_STRUCT_CTRL(TPC_ADC7)] /* [0,16777215] */;
  uint32_t TPC_TDC_TM /* [1,128] */;
  uint32_t TPC_TDC_TMI[128 EXT_STRUCT_CTRL(TPC_TDC_TM)] /* [1,128] */;
  uint32_t TPC_TDC_TME[128 EXT_STRUCT_CTRL(TPC_TDC_TM)] /* [1,16384] */;
  uint32_t TPC_TDC_T /* [0,16384] */;
  uint32_t TPC_TDC_Tv[16384 EXT_STRUCT_CTRL(TPC_TDC_T)] /* [0,16777215] */;
  uint32_t TPC_TDC_LOTM /* [1,128] */;
  uint32_t TPC_TDC_LOTMI[128 EXT_STRUCT_CTRL(TPC_TDC_LOTM)] /* [1,128] */;
  uint32_t TPC_TDC_LOTME[128 EXT_STRUCT_CTRL(TPC_TDC_LOTM)] /* [1,16384] */;
  uint32_t TPC_TDC_LOT /* [0,16384] */;
  uint32_t TPC_TDC_LOTv[16384 EXT_STRUCT_CTRL(TPC_TDC_LOT)] /* [0,255] */;

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
  uint32_t frstpc_data_v785_n;
  uint32_t frstpc_data_v785_nI[32 /* frstpc_data_v785_n */];
  uint32_t frstpc_data_v785_data[32 /* frstpc_data_v785_n */];
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
  /* RAW */
  struct {
    uint32_t _;
    uint32_t I[32 /*  */];
    uint32_t v[32 /*  */];
  } TPC_ADC[7];
  uint32_t TPC_TDC_TM;
  uint32_t TPC_TDC_TMI[128 /* TPC_TDC_TM */];
  uint32_t TPC_TDC_TME[128 /* TPC_TDC_TM */];
  uint32_t TPC_TDC_T;
  uint32_t TPC_TDC_Tv[16384 /* TPC_TDC_T */];
  uint32_t TPC_TDC_LOTM;
  uint32_t TPC_TDC_LOTMI[128 /* TPC_TDC_LOTM */];
  uint32_t TPC_TDC_LOTME[128 /* TPC_TDC_LOTM */];
  uint32_t TPC_TDC_LOT;
  uint32_t TPC_TDC_LOTv[16384 /* TPC_TDC_LOT */];

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
                     frstpc_data_v785_n,              UINT32,\
                    "frstpc_data_v785_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v785_nI,             UINT32,\
                    "frstpc_data_v785_nI",             "frstpc_data_v785_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frstpc_data_v785_data,           UINT32,\
                    "frstpc_data_v785_data",           "frstpc_data_v785_n",0/*flags*/); \
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
  /* RAW */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TPC_ADC1,                        UINT32,\
                    "TPC_ADC1",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC1I,                       UINT32,\
                    "TPC_ADC1I",                       "TPC_ADC1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC1v,                       UINT32,\
                    "TPC_ADC1v",                       "TPC_ADC1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TPC_ADC2,                        UINT32,\
                    "TPC_ADC2",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC2I,                       UINT32,\
                    "TPC_ADC2I",                       "TPC_ADC2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC2v,                       UINT32,\
                    "TPC_ADC2v",                       "TPC_ADC2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TPC_ADC3,                        UINT32,\
                    "TPC_ADC3",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC3I,                       UINT32,\
                    "TPC_ADC3I",                       "TPC_ADC3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC3v,                       UINT32,\
                    "TPC_ADC3v",                       "TPC_ADC3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TPC_ADC4,                        UINT32,\
                    "TPC_ADC4",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC4I,                       UINT32,\
                    "TPC_ADC4I",                       "TPC_ADC4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC4v,                       UINT32,\
                    "TPC_ADC4v",                       "TPC_ADC4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TPC_ADC5,                        UINT32,\
                    "TPC_ADC5",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC5I,                       UINT32,\
                    "TPC_ADC5I",                       "TPC_ADC5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC5v,                       UINT32,\
                    "TPC_ADC5v",                       "TPC_ADC5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TPC_ADC6,                        UINT32,\
                    "TPC_ADC6",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC6I,                       UINT32,\
                    "TPC_ADC6I",                       "TPC_ADC6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC6v,                       UINT32,\
                    "TPC_ADC6v",                       "TPC_ADC6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TPC_ADC7,                        UINT32,\
                    "TPC_ADC7",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC7I,                       UINT32,\
                    "TPC_ADC7I",                       "TPC_ADC7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_ADC7v,                       UINT32,\
                    "TPC_ADC7v",                       "TPC_ADC7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TPC_TDC_TM,                      UINT32,\
                    "TPC_TDC_TM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_TDC_TMI,                     UINT32,\
                    "TPC_TDC_TMI",                     "TPC_TDC_TM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_TDC_TME,                     UINT32,\
                    "TPC_TDC_TME",                     "TPC_TDC_TM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TPC_TDC_T,                       UINT32,\
                    "TPC_TDC_T",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_TDC_Tv,                      UINT32,\
                    "TPC_TDC_Tv",                      "TPC_TDC_T",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TPC_TDC_LOTM,                    UINT32,\
                    "TPC_TDC_LOTM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_TDC_LOTMI,                   UINT32,\
                    "TPC_TDC_LOTMI",                   "TPC_TDC_LOTM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_TDC_LOTME,                   UINT32,\
                    "TPC_TDC_LOTME",                   "TPC_TDC_LOTM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TPC_TDC_LOT,                     UINT32,\
                    "TPC_TDC_LOT",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     TPC_TDC_LOTv,                    UINT32,\
                    "TPC_TDC_LOTv",                    "TPC_TDC_LOT",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FRSTPC_EXT_H101_FRSTPC_H__*/

/*******************************************************/
