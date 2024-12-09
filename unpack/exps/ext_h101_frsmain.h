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
  /* RAW */
  uint32_t SPILL_ON /* [0,255] */;
  uint32_t SPILL_OFF /* [0,255] */;
  uint32_t SCALERS1 /* [0,32] */;
  uint32_t SCALERS1I[32 EXT_STRUCT_CTRL(SCALERS1)] /* [1,32] */;
  uint32_t SCALERS1v[32 EXT_STRUCT_CTRL(SCALERS1)] /* [-1,-1] */;
  uint32_t SCALERS2 /* [0,32] */;
  uint32_t SCALERS2I[32 EXT_STRUCT_CTRL(SCALERS2)] /* [1,32] */;
  uint32_t SCALERS2v[32 EXT_STRUCT_CTRL(SCALERS2)] /* [-1,-1] */;
  uint32_t SCI_TAC_DE /* [0,32] */;
  uint32_t SCI_TAC_DEI[32 EXT_STRUCT_CTRL(SCI_TAC_DE)] /* [1,32] */;
  uint32_t SCI_TAC_DEv[32 EXT_STRUCT_CTRL(SCI_TAC_DE)] /* [-1,-1] */;
  uint32_t SCI_TAC_DT /* [0,16] */;
  uint32_t SCI_TAC_DTI[16 EXT_STRUCT_CTRL(SCI_TAC_DT)] /* [1,16] */;
  uint32_t SCI_TAC_DTv[16 EXT_STRUCT_CTRL(SCI_TAC_DT)] /* [0,16777215] */;
  uint32_t SCI_MHTDC_TM /* [1,16] */;
  uint32_t SCI_MHTDC_TMI[16 EXT_STRUCT_CTRL(SCI_MHTDC_TM)] /* [1,16] */;
  uint32_t SCI_MHTDC_TME[16 EXT_STRUCT_CTRL(SCI_MHTDC_TM)] /* [1,2048] */;
  uint32_t SCI_MHTDC_T /* [0,2048] */;
  uint32_t SCI_MHTDC_Tv[2048 EXT_STRUCT_CTRL(SCI_MHTDC_T)] /* [0,16777215] */;
  uint32_t SCI_MHTDC_LOTM /* [1,16] */;
  uint32_t SCI_MHTDC_LOTMI[16 EXT_STRUCT_CTRL(SCI_MHTDC_LOTM)] /* [1,16] */;
  uint32_t SCI_MHTDC_LOTME[16 EXT_STRUCT_CTRL(SCI_MHTDC_LOTM)] /* [1,2048] */;
  uint32_t SCI_MHTDC_LOT /* [0,2048] */;
  uint32_t SCI_MHTDC_LOTv[2048 EXT_STRUCT_CTRL(SCI_MHTDC_LOT)] /* [0,255] */;
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
  uint32_t MUSIC1TM /* [1,8] */;
  uint32_t MUSIC1TMI[8 EXT_STRUCT_CTRL(MUSIC1TM)] /* [1,8] */;
  uint32_t MUSIC1TME[8 EXT_STRUCT_CTRL(MUSIC1TM)] /* [1,1024] */;
  uint32_t MUSIC1T /* [0,1024] */;
  uint32_t MUSIC1Tv[1024 EXT_STRUCT_CTRL(MUSIC1T)] /* [0,16777215] */;
  uint32_t MUSIC1LOTM /* [1,8] */;
  uint32_t MUSIC1LOTMI[8 EXT_STRUCT_CTRL(MUSIC1LOTM)] /* [1,8] */;
  uint32_t MUSIC1LOTME[8 EXT_STRUCT_CTRL(MUSIC1LOTM)] /* [1,1024] */;
  uint32_t MUSIC1LOT /* [0,1024] */;
  uint32_t MUSIC1LOTv[1024 EXT_STRUCT_CTRL(MUSIC1LOT)] /* [0,255] */;
  uint32_t MUSIC1E /* [0,8] */;
  uint32_t MUSIC1EI[8 EXT_STRUCT_CTRL(MUSIC1E)] /* [1,8] */;
  uint32_t MUSIC1Ev[8 EXT_STRUCT_CTRL(MUSIC1E)] /* [0,16777215] */;
  uint32_t MUSIC2TM /* [1,8] */;
  uint32_t MUSIC2TMI[8 EXT_STRUCT_CTRL(MUSIC2TM)] /* [1,8] */;
  uint32_t MUSIC2TME[8 EXT_STRUCT_CTRL(MUSIC2TM)] /* [1,1024] */;
  uint32_t MUSIC2T /* [0,1024] */;
  uint32_t MUSIC2Tv[1024 EXT_STRUCT_CTRL(MUSIC2T)] /* [0,16777215] */;
  uint32_t MUSIC2LOTM /* [1,8] */;
  uint32_t MUSIC2LOTMI[8 EXT_STRUCT_CTRL(MUSIC2LOTM)] /* [1,8] */;
  uint32_t MUSIC2LOTME[8 EXT_STRUCT_CTRL(MUSIC2LOTM)] /* [1,1024] */;
  uint32_t MUSIC2LOT /* [0,1024] */;
  uint32_t MUSIC2LOTv[1024 EXT_STRUCT_CTRL(MUSIC2LOT)] /* [0,255] */;
  uint32_t MUSIC2E /* [0,8] */;
  uint32_t MUSIC2EI[8 EXT_STRUCT_CTRL(MUSIC2E)] /* [1,8] */;
  uint32_t MUSIC2Ev[8 EXT_STRUCT_CTRL(MUSIC2E)] /* [0,16777215] */;
  uint32_t WR_ID /* [0,65535] */;
  uint32_t WR_T1 /* [0,65535] */;
  uint32_t WR_T2 /* [0,65535] */;
  uint32_t WR_T3 /* [0,65535] */;
  uint32_t WR_T4 /* [0,65535] */;
  uint32_t TPAT /* [0,65535] */;

} EXT_STR_h101_frsmain;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_frsmain_onion_t
{
  /* RAW */
  uint32_t SPILL_ON;
  uint32_t SPILL_OFF;
  struct {
    uint32_t _;
    uint32_t I[32 /*  */];
    uint32_t v[32 /*  */];
  } SCALERS[2];
  uint32_t SCI_TAC_DE;
  uint32_t SCI_TAC_DEI[32 /* SCI_TAC_DE */];
  uint32_t SCI_TAC_DEv[32 /* SCI_TAC_DE */];
  uint32_t SCI_TAC_DT;
  uint32_t SCI_TAC_DTI[16 /* SCI_TAC_DT */];
  uint32_t SCI_TAC_DTv[16 /* SCI_TAC_DT */];
  uint32_t SCI_MHTDC_TM;
  uint32_t SCI_MHTDC_TMI[16 /* SCI_MHTDC_TM */];
  uint32_t SCI_MHTDC_TME[16 /* SCI_MHTDC_TM */];
  uint32_t SCI_MHTDC_T;
  uint32_t SCI_MHTDC_Tv[2048 /* SCI_MHTDC_T */];
  uint32_t SCI_MHTDC_LOTM;
  uint32_t SCI_MHTDC_LOTMI[16 /* SCI_MHTDC_LOTM */];
  uint32_t SCI_MHTDC_LOTME[16 /* SCI_MHTDC_LOTM */];
  uint32_t SCI_MHTDC_LOT;
  uint32_t SCI_MHTDC_LOTv[2048 /* SCI_MHTDC_LOT */];
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
  struct {
    uint32_t TM;
    uint32_t TMI[8 /* TM */];
    uint32_t TME[8 /* TM */];
    uint32_t T;
    uint32_t Tv[1024 /* T */];
    uint32_t LOTM;
    uint32_t LOTMI[8 /* LOTM */];
    uint32_t LOTME[8 /* LOTM */];
    uint32_t LOT;
    uint32_t LOTv[1024 /* LOT */];
    uint32_t E;
    uint32_t EI[8 /* E */];
    uint32_t Ev[8 /* E */];
  } MUSIC[2];
  uint32_t WR_ID;
  uint32_t WR_T[4];
  uint32_t TPAT;

} EXT_STR_h101_frsmain_onion;

/*******************************************************/

#define EXT_STR_h101_frsmain_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* RAW */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SPILL_ON,                        UINT32,\
                    "SPILL_ON",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SPILL_OFF,                       UINT32,\
                    "SPILL_OFF",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCALERS1,                        UINT32,\
                    "SCALERS1",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCALERS1I,                       UINT32,\
                    "SCALERS1I",                       "SCALERS1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCALERS1v,                       UINT32,\
                    "SCALERS1v",                       "SCALERS1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCALERS2,                        UINT32,\
                    "SCALERS2",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCALERS2I,                       UINT32,\
                    "SCALERS2I",                       "SCALERS2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCALERS2v,                       UINT32,\
                    "SCALERS2v",                       "SCALERS2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCI_TAC_DE,                      UINT32,\
                    "SCI_TAC_DE",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_TAC_DEI,                     UINT32,\
                    "SCI_TAC_DEI",                     "SCI_TAC_DE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_TAC_DEv,                     UINT32,\
                    "SCI_TAC_DEv",                     "SCI_TAC_DE",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCI_TAC_DT,                      UINT32,\
                    "SCI_TAC_DT",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_TAC_DTI,                     UINT32,\
                    "SCI_TAC_DTI",                     "SCI_TAC_DT",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_TAC_DTv,                     UINT32,\
                    "SCI_TAC_DTv",                     "SCI_TAC_DT",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCI_MHTDC_TM,                    UINT32,\
                    "SCI_MHTDC_TM",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_MHTDC_TMI,                   UINT32,\
                    "SCI_MHTDC_TMI",                   "SCI_MHTDC_TM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_MHTDC_TME,                   UINT32,\
                    "SCI_MHTDC_TME",                   "SCI_MHTDC_TM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCI_MHTDC_T,                     UINT32,\
                    "SCI_MHTDC_T",2048,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_MHTDC_Tv,                    UINT32,\
                    "SCI_MHTDC_Tv",                    "SCI_MHTDC_T",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCI_MHTDC_LOTM,                  UINT32,\
                    "SCI_MHTDC_LOTM",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_MHTDC_LOTMI,                 UINT32,\
                    "SCI_MHTDC_LOTMI",                 "SCI_MHTDC_LOTM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_MHTDC_LOTME,                 UINT32,\
                    "SCI_MHTDC_LOTME",                 "SCI_MHTDC_LOTM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCI_MHTDC_LOT,                   UINT32,\
                    "SCI_MHTDC_LOT",2048,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_MHTDC_LOTv,                  UINT32,\
                    "SCI_MHTDC_LOTv",                  "SCI_MHTDC_LOT",0/*flags*/); \
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
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     MUSIC1TM,                        UINT32,\
                    "MUSIC1TM",8,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC1TMI,                       UINT32,\
                    "MUSIC1TMI",                       "MUSIC1TM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC1TME,                       UINT32,\
                    "MUSIC1TME",                       "MUSIC1TM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     MUSIC1T,                         UINT32,\
                    "MUSIC1T",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC1Tv,                        UINT32,\
                    "MUSIC1Tv",                        "MUSIC1T",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     MUSIC1LOTM,                      UINT32,\
                    "MUSIC1LOTM",8,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC1LOTMI,                     UINT32,\
                    "MUSIC1LOTMI",                     "MUSIC1LOTM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC1LOTME,                     UINT32,\
                    "MUSIC1LOTME",                     "MUSIC1LOTM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     MUSIC1LOT,                       UINT32,\
                    "MUSIC1LOT",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC1LOTv,                      UINT32,\
                    "MUSIC1LOTv",                      "MUSIC1LOT",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     MUSIC1E,                         UINT32,\
                    "MUSIC1E",8,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC1EI,                        UINT32,\
                    "MUSIC1EI",                        "MUSIC1E",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC1Ev,                        UINT32,\
                    "MUSIC1Ev",                        "MUSIC1E",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     MUSIC2TM,                        UINT32,\
                    "MUSIC2TM",8,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC2TMI,                       UINT32,\
                    "MUSIC2TMI",                       "MUSIC2TM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC2TME,                       UINT32,\
                    "MUSIC2TME",                       "MUSIC2TM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     MUSIC2T,                         UINT32,\
                    "MUSIC2T",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC2Tv,                        UINT32,\
                    "MUSIC2Tv",                        "MUSIC2T",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     MUSIC2LOTM,                      UINT32,\
                    "MUSIC2LOTM",8,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC2LOTMI,                     UINT32,\
                    "MUSIC2LOTMI",                     "MUSIC2LOTM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC2LOTME,                     UINT32,\
                    "MUSIC2LOTME",                     "MUSIC2LOTM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     MUSIC2LOT,                       UINT32,\
                    "MUSIC2LOT",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC2LOTv,                      UINT32,\
                    "MUSIC2LOTv",                      "MUSIC2LOT",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     MUSIC2E,                         UINT32,\
                    "MUSIC2E",8,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC2EI,                        UINT32,\
                    "MUSIC2EI",                        "MUSIC2E",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC2Ev,                        UINT32,\
                    "MUSIC2Ev",                        "MUSIC2E",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     WR_ID,                           UINT32,\
                    "WR_ID",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     WR_T1,                           UINT32,\
                    "WR_T1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     WR_T2,                           UINT32,\
                    "WR_T2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     WR_T3,                           UINT32,\
                    "WR_T3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     WR_T4,                           UINT32,\
                    "WR_T4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     TPAT,                            UINT32,\
                    "TPAT",65535,0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FRSMAIN_EXT_H101_FRSMAIN_H__*/

/*******************************************************/
