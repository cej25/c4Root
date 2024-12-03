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
  uint32_t frsmain_data_v830_header /* [-1,-1] */;
  uint32_t frsmain_data_v792_n /* [0,32] */;
  uint32_t frsmain_data_v792_nI[32 EXT_STRUCT_CTRL(frsmain_data_v792_n)] /* [1,32] */;
  uint32_t frsmain_data_v792_data[32 EXT_STRUCT_CTRL(frsmain_data_v792_n)] /* [-1,-1] */;
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
  /* RAW */
  uint32_t SPILL_ON /* [0,255] */;
  uint32_t SPILL_OFF /* [0,255] */;
  uint32_t MAIN_SCALERS /* [0,32] */;
  uint32_t MAIN_SCALERSI[32 EXT_STRUCT_CTRL(MAIN_SCALERS)] /* [1,32] */;
  uint32_t MAIN_SCALERSv[32 EXT_STRUCT_CTRL(MAIN_SCALERS)] /* [-1,-1] */;
  uint32_t SCI_DE_TAC /* [0,32] */;
  uint32_t SCI_DE_TACI[32 EXT_STRUCT_CTRL(SCI_DE_TAC)] /* [1,32] */;
  uint32_t SCI_DE_TACv[32 EXT_STRUCT_CTRL(SCI_DE_TAC)] /* [-1,-1] */;
  uint32_t SCI_DE_GEO /* [0,255] */;
  uint32_t SCI_T_MHTDCM /* [1,16] */;
  uint32_t SCI_T_MHTDCMI[16 EXT_STRUCT_CTRL(SCI_T_MHTDCM)] /* [1,16] */;
  uint32_t SCI_T_MHTDCME[16 EXT_STRUCT_CTRL(SCI_T_MHTDCM)] /* [1,2048] */;
  uint32_t SCI_T_MHTDC /* [0,2048] */;
  uint32_t SCI_T_MHTDCv[2048 EXT_STRUCT_CTRL(SCI_T_MHTDC)] /* [0,16777215] */;
  uint32_t SCI_LOT_MHTDCM /* [1,16] */;
  uint32_t SCI_LOT_MHTDCMI[16 EXT_STRUCT_CTRL(SCI_LOT_MHTDCM)] /* [1,16] */;
  uint32_t SCI_LOT_MHTDCME[16 EXT_STRUCT_CTRL(SCI_LOT_MHTDCM)] /* [1,2048] */;
  uint32_t SCI_LOT_MHTDC /* [0,2048] */;
  uint32_t SCI_LOT_MHTDCv[2048 EXT_STRUCT_CTRL(SCI_LOT_MHTDC)] /* [0,255] */;
  uint32_t MUSIC1TM /* [1,8] */;
  uint32_t MUSIC1TMI[8 EXT_STRUCT_CTRL(MUSIC1TM)] /* [1,8] */;
  uint32_t MUSIC1TME[8 EXT_STRUCT_CTRL(MUSIC1TM)] /* [1,1024] */;
  uint32_t MUSIC1T /* [0,1024] */;
  uint32_t MUSIC1Tv[1024 EXT_STRUCT_CTRL(MUSIC1T)] /* [0,16777215] */;
  uint32_t MUSIC1LOT_TM /* [1,8] */;
  uint32_t MUSIC1LOT_TMI[8 EXT_STRUCT_CTRL(MUSIC1LOT_TM)] /* [1,8] */;
  uint32_t MUSIC1LOT_TME[8 EXT_STRUCT_CTRL(MUSIC1LOT_TM)] /* [1,1024] */;
  uint32_t MUSIC1LOT_T /* [0,1024] */;
  uint32_t MUSIC1LOT_Tv[1024 EXT_STRUCT_CTRL(MUSIC1LOT_T)] /* [0,255] */;
  uint32_t MUSIC2TM /* [1,8] */;
  uint32_t MUSIC2TMI[8 EXT_STRUCT_CTRL(MUSIC2TM)] /* [1,8] */;
  uint32_t MUSIC2TME[8 EXT_STRUCT_CTRL(MUSIC2TM)] /* [1,1024] */;
  uint32_t MUSIC2T /* [0,1024] */;
  uint32_t MUSIC2Tv[1024 EXT_STRUCT_CTRL(MUSIC2T)] /* [0,16777215] */;
  uint32_t MUSIC2LOT_TM /* [1,8] */;
  uint32_t MUSIC2LOT_TMI[8 EXT_STRUCT_CTRL(MUSIC2LOT_TM)] /* [1,8] */;
  uint32_t MUSIC2LOT_TME[8 EXT_STRUCT_CTRL(MUSIC2LOT_TM)] /* [1,1024] */;
  uint32_t MUSIC2LOT_T /* [0,1024] */;
  uint32_t MUSIC2LOT_Tv[1024 EXT_STRUCT_CTRL(MUSIC2LOT_T)] /* [0,255] */;

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
  uint32_t frsmain_data_v830_header;
  uint32_t frsmain_data_v792_n;
  uint32_t frsmain_data_v792_nI[32 /* frsmain_data_v792_n */];
  uint32_t frsmain_data_v792_data[32 /* frsmain_data_v792_n */];
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
  /* RAW */
  uint32_t SPILL_ON;
  uint32_t SPILL_OFF;
  uint32_t MAIN_SCALERS;
  uint32_t MAIN_SCALERSI[32 /* MAIN_SCALERS */];
  uint32_t MAIN_SCALERSv[32 /* MAIN_SCALERS */];
  uint32_t SCI_DE_TAC;
  uint32_t SCI_DE_TACI[32 /* SCI_DE_TAC */];
  uint32_t SCI_DE_TACv[32 /* SCI_DE_TAC */];
  uint32_t SCI_DE_GEO;
  uint32_t SCI_T_MHTDCM;
  uint32_t SCI_T_MHTDCMI[16 /* SCI_T_MHTDCM */];
  uint32_t SCI_T_MHTDCME[16 /* SCI_T_MHTDCM */];
  uint32_t SCI_T_MHTDC;
  uint32_t SCI_T_MHTDCv[2048 /* SCI_T_MHTDC */];
  uint32_t SCI_LOT_MHTDCM;
  uint32_t SCI_LOT_MHTDCMI[16 /* SCI_LOT_MHTDCM */];
  uint32_t SCI_LOT_MHTDCME[16 /* SCI_LOT_MHTDCM */];
  uint32_t SCI_LOT_MHTDC;
  uint32_t SCI_LOT_MHTDCv[2048 /* SCI_LOT_MHTDC */];
  struct {
    uint32_t TM;
    uint32_t TMI[8 /* TM */];
    uint32_t TME[8 /* TM */];
    uint32_t T;
    uint32_t Tv[1024 /* T */];
    uint32_t LOT_TM;
    uint32_t LOT_TMI[8 /* LOT_TM */];
    uint32_t LOT_TME[8 /* LOT_TM */];
    uint32_t LOT_T;
    uint32_t LOT_Tv[1024 /* LOT_T */];
  } MUSIC[2];

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
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     frsmain_data_v830_header,        UINT32,\
                    "frsmain_data_v830_header",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v792_n,             UINT32,\
                    "frsmain_data_v792_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsmain_data_v792_nI,            UINT32,\
                    "frsmain_data_v792_nI",            "frsmain_data_v792_n",0/*flags*/); \
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
  /* RAW */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SPILL_ON,                        UINT32,\
                    "SPILL_ON",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SPILL_OFF,                       UINT32,\
                    "SPILL_OFF",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     MAIN_SCALERS,                    UINT32,\
                    "MAIN_SCALERS",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MAIN_SCALERSI,                   UINT32,\
                    "MAIN_SCALERSI",                   "MAIN_SCALERS",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MAIN_SCALERSv,                   UINT32,\
                    "MAIN_SCALERSv",                   "MAIN_SCALERS",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCI_DE_TAC,                      UINT32,\
                    "SCI_DE_TAC",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_DE_TACI,                     UINT32,\
                    "SCI_DE_TACI",                     "SCI_DE_TAC",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_DE_TACv,                     UINT32,\
                    "SCI_DE_TACv",                     "SCI_DE_TAC",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCI_DE_GEO,                      UINT32,\
                    "SCI_DE_GEO",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCI_T_MHTDCM,                    UINT32,\
                    "SCI_T_MHTDCM",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_T_MHTDCMI,                   UINT32,\
                    "SCI_T_MHTDCMI",                   "SCI_T_MHTDCM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_T_MHTDCME,                   UINT32,\
                    "SCI_T_MHTDCME",                   "SCI_T_MHTDCM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCI_T_MHTDC,                     UINT32,\
                    "SCI_T_MHTDC",2048,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_T_MHTDCv,                    UINT32,\
                    "SCI_T_MHTDCv",                    "SCI_T_MHTDC",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCI_LOT_MHTDCM,                  UINT32,\
                    "SCI_LOT_MHTDCM",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_LOT_MHTDCMI,                 UINT32,\
                    "SCI_LOT_MHTDCMI",                 "SCI_LOT_MHTDCM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_LOT_MHTDCME,                 UINT32,\
                    "SCI_LOT_MHTDCME",                 "SCI_LOT_MHTDCM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     SCI_LOT_MHTDC,                   UINT32,\
                    "SCI_LOT_MHTDC",2048,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     SCI_LOT_MHTDCv,                  UINT32,\
                    "SCI_LOT_MHTDCv",                  "SCI_LOT_MHTDC",0/*flags*/); \
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
                     MUSIC1LOT_TM,                    UINT32,\
                    "MUSIC1LOT_TM",8,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC1LOT_TMI,                   UINT32,\
                    "MUSIC1LOT_TMI",                   "MUSIC1LOT_TM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC1LOT_TME,                   UINT32,\
                    "MUSIC1LOT_TME",                   "MUSIC1LOT_TM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     MUSIC1LOT_T,                     UINT32,\
                    "MUSIC1LOT_T",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC1LOT_Tv,                    UINT32,\
                    "MUSIC1LOT_Tv",                    "MUSIC1LOT_T",0/*flags*/); \
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
                     MUSIC2LOT_TM,                    UINT32,\
                    "MUSIC2LOT_TM",8,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC2LOT_TMI,                   UINT32,\
                    "MUSIC2LOT_TMI",                   "MUSIC2LOT_TM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC2LOT_TME,                   UINT32,\
                    "MUSIC2LOT_TME",                   "MUSIC2LOT_TM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     MUSIC2LOT_T,                     UINT32,\
                    "MUSIC2LOT_T",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     MUSIC2LOT_Tv,                    UINT32,\
                    "MUSIC2LOT_Tv",                    "MUSIC2LOT_T",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FRSMAIN_EXT_H101_FRSMAIN_H__*/

/*******************************************************/
