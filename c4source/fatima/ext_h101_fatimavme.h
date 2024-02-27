/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_FATIMAVME_EXT_H101_FATIMAVME_H__
#define __GUARD_H101_FATIMAVME_EXT_H101_FATIMAVME_H__

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

typedef struct EXT_STR_h101_fatimavme_t
{
  /* UNPACK */
  uint32_t fatimavme_scalers_n /* [0,32] */;
  uint32_t fatimavme_scalers_nI[32 EXT_STRUCT_CTRL(fatimavme_scalers_n)] /* [1,32] */;
  uint32_t fatimavme_scalers_data[32 EXT_STRUCT_CTRL(fatimavme_scalers_n)] /* [-1,-1] */;
  uint32_t fatimavme_tdc0_nM /* [1,128] */;
  uint32_t fatimavme_tdc0_nMI[128 EXT_STRUCT_CTRL(fatimavme_tdc0_nM)] /* [1,128] */;
  uint32_t fatimavme_tdc0_nME[128 EXT_STRUCT_CTRL(fatimavme_tdc0_nM)] /* [1,16384] */;
  uint32_t fatimavme_tdc0_n /* [0,16384] */;
  uint32_t fatimavme_tdc0_data[16384 EXT_STRUCT_CTRL(fatimavme_tdc0_n)] /* [0,16777215] */;
  uint32_t fatimavme_tdc0_leadOrTrailM /* [1,128] */;
  uint32_t fatimavme_tdc0_leadOrTrailMI[128 EXT_STRUCT_CTRL(fatimavme_tdc0_leadOrTrailM)] /* [1,128] */;
  uint32_t fatimavme_tdc0_leadOrTrailME[128 EXT_STRUCT_CTRL(fatimavme_tdc0_leadOrTrailM)] /* [1,16384] */;
  uint32_t fatimavme_tdc0_leadOrTrail /* [0,16384] */;
  uint32_t fatimavme_tdc0_leadOrTrailv[16384 EXT_STRUCT_CTRL(fatimavme_tdc0_leadOrTrail)] /* [0,255] */;
  uint32_t fatimavme_tdc1_nM /* [1,128] */;
  uint32_t fatimavme_tdc1_nMI[128 EXT_STRUCT_CTRL(fatimavme_tdc1_nM)] /* [1,128] */;
  uint32_t fatimavme_tdc1_nME[128 EXT_STRUCT_CTRL(fatimavme_tdc1_nM)] /* [1,16384] */;
  uint32_t fatimavme_tdc1_n /* [0,16384] */;
  uint32_t fatimavme_tdc1_data[16384 EXT_STRUCT_CTRL(fatimavme_tdc1_n)] /* [0,16777215] */;
  uint32_t fatimavme_tdc1_leadOrTrailM /* [1,128] */;
  uint32_t fatimavme_tdc1_leadOrTrailMI[128 EXT_STRUCT_CTRL(fatimavme_tdc1_leadOrTrailM)] /* [1,128] */;
  uint32_t fatimavme_tdc1_leadOrTrailME[128 EXT_STRUCT_CTRL(fatimavme_tdc1_leadOrTrailM)] /* [1,16384] */;
  uint32_t fatimavme_tdc1_leadOrTrail /* [0,16384] */;
  uint32_t fatimavme_tdc1_leadOrTrailv[16384 EXT_STRUCT_CTRL(fatimavme_tdc1_leadOrTrail)] /* [0,255] */;
  uint32_t fatimavme_ts_subsystem_id /* [0,65535] */;
  uint32_t fatimavme_ts_t1 /* [0,65535] */;
  uint32_t fatimavme_ts_t2 /* [0,65535] */;
  uint32_t fatimavme_ts_t3 /* [0,65535] */;
  uint32_t fatimavme_ts_t4 /* [0,65535] */;
  uint32_t fatimavme_qdc1board_id /* [0,255] */;
  uint32_t fatimavme_qdc1channels /* [0,255] */;
  uint32_t fatimavme_qdc1n /* [0,64] */;
  uint32_t fatimavme_qdc1data[64 EXT_STRUCT_CTRL(fatimavme_qdc1n)] /* [-1,-1] */;
  uint32_t fatimavme_qdc2board_id /* [0,255] */;
  uint32_t fatimavme_qdc2channels /* [0,255] */;
  uint32_t fatimavme_qdc2n /* [0,64] */;
  uint32_t fatimavme_qdc2data[64 EXT_STRUCT_CTRL(fatimavme_qdc2n)] /* [-1,-1] */;
  uint32_t fatimavme_qdc3board_id /* [0,255] */;
  uint32_t fatimavme_qdc3channels /* [0,255] */;
  uint32_t fatimavme_qdc3n /* [0,64] */;
  uint32_t fatimavme_qdc3data[64 EXT_STRUCT_CTRL(fatimavme_qdc3n)] /* [-1,-1] */;
  uint32_t fatimavme_qdc4board_id /* [0,255] */;
  uint32_t fatimavme_qdc4channels /* [0,255] */;
  uint32_t fatimavme_qdc4n /* [0,64] */;
  uint32_t fatimavme_qdc4data[64 EXT_STRUCT_CTRL(fatimavme_qdc4n)] /* [-1,-1] */;
  uint32_t fatimavme_qdc5board_id /* [0,255] */;
  uint32_t fatimavme_qdc5channels /* [0,255] */;
  uint32_t fatimavme_qdc5n /* [0,64] */;
  uint32_t fatimavme_qdc5data[64 EXT_STRUCT_CTRL(fatimavme_qdc5n)] /* [-1,-1] */;

} EXT_STR_h101_fatimavme;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_fatimavme_onion_t
{
  /* UNPACK */
  uint32_t fatimavme_scalers_n;
  uint32_t fatimavme_scalers_nI[32 /* fatimavme_scalers_n */];
  uint32_t fatimavme_scalers_data[32 /* fatimavme_scalers_n */];
  uint32_t fatimavme_tdc0_nM;
  uint32_t fatimavme_tdc0_nMI[128 /* fatimavme_tdc0_nM */];
  uint32_t fatimavme_tdc0_nME[128 /* fatimavme_tdc0_nM */];
  uint32_t fatimavme_tdc0_n;
  uint32_t fatimavme_tdc0_data[16384 /* fatimavme_tdc0_n */];
  uint32_t fatimavme_tdc0_leadOrTrailM;
  uint32_t fatimavme_tdc0_leadOrTrailMI[128 /* fatimavme_tdc0_leadOrTrailM */];
  uint32_t fatimavme_tdc0_leadOrTrailME[128 /* fatimavme_tdc0_leadOrTrailM */];
  uint32_t fatimavme_tdc0_leadOrTrail;
  uint32_t fatimavme_tdc0_leadOrTrailv[16384 /* fatimavme_tdc0_leadOrTrail */];
  struct {
    uint32_t _nM;
    uint32_t _nMI[128 /* _nM */];
    uint32_t _nME[128 /* _nM */];
    uint32_t _n;
    uint32_t _data[16384 /* _n */];
    uint32_t _leadOrTrailM;
    uint32_t _leadOrTrailMI[128 /* _leadOrTrailM */];
    uint32_t _leadOrTrailME[128 /* _leadOrTrailM */];
    uint32_t _leadOrTrail;
    uint32_t _leadOrTrailv[16384 /* _leadOrTrail */];
  } fatimavme_tdc[1];
  uint32_t fatimavme_ts_subsystem_id;
  uint32_t fatimavme_ts_t[4];
  struct {
    uint32_t board_id;
    uint32_t channels;
    uint32_t n;
    uint32_t data[64 /* n */];
  } fatimavme_qdc[5];

} EXT_STR_h101_fatimavme_onion;

/*******************************************************/

#define EXT_STR_h101_fatimavme_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_scalers_n,             UINT32,\
                    "fatimavme_scalers_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_scalers_nI,            UINT32,\
                    "fatimavme_scalers_nI",            "fatimavme_scalers_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_scalers_data,          UINT32,\
                    "fatimavme_scalers_data",          "fatimavme_scalers_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc0_nM,               UINT32,\
                    "fatimavme_tdc0_nM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc0_nMI,              UINT32,\
                    "fatimavme_tdc0_nMI",              "fatimavme_tdc0_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc0_nME,              UINT32,\
                    "fatimavme_tdc0_nME",              "fatimavme_tdc0_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc0_n,                UINT32,\
                    "fatimavme_tdc0_n",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc0_data,             UINT32,\
                    "fatimavme_tdc0_data",             "fatimavme_tdc0_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc0_leadOrTrailM,     UINT32,\
                    "fatimavme_tdc0_leadOrTrailM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc0_leadOrTrailMI,    UINT32,\
                    "fatimavme_tdc0_leadOrTrailMI",    "fatimavme_tdc0_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc0_leadOrTrailME,    UINT32,\
                    "fatimavme_tdc0_leadOrTrailME",    "fatimavme_tdc0_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc0_leadOrTrail,      UINT32,\
                    "fatimavme_tdc0_leadOrTrail",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc0_leadOrTrailv,     UINT32,\
                    "fatimavme_tdc0_leadOrTrailv",     "fatimavme_tdc0_leadOrTrail",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_nM,               UINT32,\
                    "fatimavme_tdc1_nM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_nMI,              UINT32,\
                    "fatimavme_tdc1_nMI",              "fatimavme_tdc1_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_nME,              UINT32,\
                    "fatimavme_tdc1_nME",              "fatimavme_tdc1_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_n,                UINT32,\
                    "fatimavme_tdc1_n",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_data,             UINT32,\
                    "fatimavme_tdc1_data",             "fatimavme_tdc1_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_leadOrTrailM,     UINT32,\
                    "fatimavme_tdc1_leadOrTrailM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_leadOrTrailMI,    UINT32,\
                    "fatimavme_tdc1_leadOrTrailMI",    "fatimavme_tdc1_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_leadOrTrailME,    UINT32,\
                    "fatimavme_tdc1_leadOrTrailME",    "fatimavme_tdc1_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_leadOrTrail,      UINT32,\
                    "fatimavme_tdc1_leadOrTrail",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_leadOrTrailv,     UINT32,\
                    "fatimavme_tdc1_leadOrTrailv",     "fatimavme_tdc1_leadOrTrail",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_ts_subsystem_id,       UINT32,\
                    "fatimavme_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_ts_t1,                 UINT32,\
                    "fatimavme_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_ts_t2,                 UINT32,\
                    "fatimavme_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_ts_t3,                 UINT32,\
                    "fatimavme_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_ts_t4,                 UINT32,\
                    "fatimavme_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1board_id,          UINT32,\
                    "fatimavme_qdc1board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1channels,          UINT32,\
                    "fatimavme_qdc1channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1n,                 UINT32,\
                    "fatimavme_qdc1n",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1data,              UINT32,\
                    "fatimavme_qdc1data",              "fatimavme_qdc1n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2board_id,          UINT32,\
                    "fatimavme_qdc2board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2channels,          UINT32,\
                    "fatimavme_qdc2channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2n,                 UINT32,\
                    "fatimavme_qdc2n",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2data,              UINT32,\
                    "fatimavme_qdc2data",              "fatimavme_qdc2n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3board_id,          UINT32,\
                    "fatimavme_qdc3board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3channels,          UINT32,\
                    "fatimavme_qdc3channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3n,                 UINT32,\
                    "fatimavme_qdc3n",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3data,              UINT32,\
                    "fatimavme_qdc3data",              "fatimavme_qdc3n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4board_id,          UINT32,\
                    "fatimavme_qdc4board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4channels,          UINT32,\
                    "fatimavme_qdc4channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4n,                 UINT32,\
                    "fatimavme_qdc4n",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4data,              UINT32,\
                    "fatimavme_qdc4data",              "fatimavme_qdc4n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5board_id,          UINT32,\
                    "fatimavme_qdc5board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5channels,          UINT32,\
                    "fatimavme_qdc5channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5n,                 UINT32,\
                    "fatimavme_qdc5n",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5data,              UINT32,\
                    "fatimavme_qdc5data",              "fatimavme_qdc5n",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FATIMAVME_EXT_H101_FATIMAVME_H__*/

/*******************************************************/
