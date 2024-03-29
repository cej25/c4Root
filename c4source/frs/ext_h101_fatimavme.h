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
  uint32_t fatimavme_tdc2_nM /* [1,128] */;
  uint32_t fatimavme_tdc2_nMI[128 EXT_STRUCT_CTRL(fatimavme_tdc2_nM)] /* [1,128] */;
  uint32_t fatimavme_tdc2_nME[128 EXT_STRUCT_CTRL(fatimavme_tdc2_nM)] /* [1,16384] */;
  uint32_t fatimavme_tdc2_n /* [0,16384] */;
  uint32_t fatimavme_tdc2_data[16384 EXT_STRUCT_CTRL(fatimavme_tdc2_n)] /* [0,16777215] */;
  uint32_t fatimavme_tdc2_leadOrTrailM /* [1,128] */;
  uint32_t fatimavme_tdc2_leadOrTrailMI[128 EXT_STRUCT_CTRL(fatimavme_tdc2_leadOrTrailM)] /* [1,128] */;
  uint32_t fatimavme_tdc2_leadOrTrailME[128 EXT_STRUCT_CTRL(fatimavme_tdc2_leadOrTrailM)] /* [1,16384] */;
  uint32_t fatimavme_tdc2_leadOrTrail /* [0,16384] */;
  uint32_t fatimavme_tdc2_leadOrTrailv[16384 EXT_STRUCT_CTRL(fatimavme_tdc2_leadOrTrail)] /* [0,255] */;
  uint32_t fatimavme_ts_subsystem_id /* [0,65535] */;
  uint32_t fatimavme_ts_t1 /* [0,65535] */;
  uint32_t fatimavme_ts_t2 /* [0,65535] */;
  uint32_t fatimavme_ts_t3 /* [0,65535] */;
  uint32_t fatimavme_ts_t4 /* [0,65535] */;
  uint32_t fatimavme_qdc1board_id /* [0,255] */;
  uint32_t fatimavme_qdc1channels /* [0,255] */;
  uint32_t fatimavme_qdc1board_time /* [-1,-1] */;
  uint32_t fatimavme_qdc1channel_time /* [0,64] */;
  uint32_t fatimavme_qdc1channel_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc1channel_time)] /* [-1,-1] */;
  uint32_t fatimavme_qdc1chan_ext_time /* [0,64] */;
  uint32_t fatimavme_qdc1chan_ext_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc1chan_ext_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc1chan_fine_time /* [0,64] */;
  uint32_t fatimavme_qdc1chan_fine_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc1chan_fine_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc1qshort /* [0,64] */;
  uint32_t fatimavme_qdc1qshortv[64 EXT_STRUCT_CTRL(fatimavme_qdc1qshort)] /* [0,65535] */;
  uint32_t fatimavme_qdc1qlong /* [0,64] */;
  uint32_t fatimavme_qdc1qlongv[64 EXT_STRUCT_CTRL(fatimavme_qdc1qlong)] /* [0,65535] */;
  uint32_t fatimavme_qdc2board_id /* [0,255] */;
  uint32_t fatimavme_qdc2channels /* [0,255] */;
  uint32_t fatimavme_qdc2board_time /* [-1,-1] */;
  uint32_t fatimavme_qdc2channel_time /* [0,64] */;
  uint32_t fatimavme_qdc2channel_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc2channel_time)] /* [-1,-1] */;
  uint32_t fatimavme_qdc2chan_ext_time /* [0,64] */;
  uint32_t fatimavme_qdc2chan_ext_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc2chan_ext_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc2chan_fine_time /* [0,64] */;
  uint32_t fatimavme_qdc2chan_fine_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc2chan_fine_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc2qshort /* [0,64] */;
  uint32_t fatimavme_qdc2qshortv[64 EXT_STRUCT_CTRL(fatimavme_qdc2qshort)] /* [0,65535] */;
  uint32_t fatimavme_qdc2qlong /* [0,64] */;
  uint32_t fatimavme_qdc2qlongv[64 EXT_STRUCT_CTRL(fatimavme_qdc2qlong)] /* [0,65535] */;
  uint32_t fatimavme_qdc3board_id /* [0,255] */;
  uint32_t fatimavme_qdc3channels /* [0,255] */;
  uint32_t fatimavme_qdc3board_time /* [-1,-1] */;
  uint32_t fatimavme_qdc3channel_time /* [0,64] */;
  uint32_t fatimavme_qdc3channel_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc3channel_time)] /* [-1,-1] */;
  uint32_t fatimavme_qdc3chan_ext_time /* [0,64] */;
  uint32_t fatimavme_qdc3chan_ext_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc3chan_ext_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc3chan_fine_time /* [0,64] */;
  uint32_t fatimavme_qdc3chan_fine_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc3chan_fine_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc3qshort /* [0,64] */;
  uint32_t fatimavme_qdc3qshortv[64 EXT_STRUCT_CTRL(fatimavme_qdc3qshort)] /* [0,65535] */;
  uint32_t fatimavme_qdc3qlong /* [0,64] */;
  uint32_t fatimavme_qdc3qlongv[64 EXT_STRUCT_CTRL(fatimavme_qdc3qlong)] /* [0,65535] */;
  uint32_t fatimavme_qdc4board_id /* [0,255] */;
  uint32_t fatimavme_qdc4channels /* [0,255] */;
  uint32_t fatimavme_qdc4board_time /* [-1,-1] */;
  uint32_t fatimavme_qdc4channel_time /* [0,64] */;
  uint32_t fatimavme_qdc4channel_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc4channel_time)] /* [-1,-1] */;
  uint32_t fatimavme_qdc4chan_ext_time /* [0,64] */;
  uint32_t fatimavme_qdc4chan_ext_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc4chan_ext_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc4chan_fine_time /* [0,64] */;
  uint32_t fatimavme_qdc4chan_fine_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc4chan_fine_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc4qshort /* [0,64] */;
  uint32_t fatimavme_qdc4qshortv[64 EXT_STRUCT_CTRL(fatimavme_qdc4qshort)] /* [0,65535] */;
  uint32_t fatimavme_qdc4qlong /* [0,64] */;
  uint32_t fatimavme_qdc4qlongv[64 EXT_STRUCT_CTRL(fatimavme_qdc4qlong)] /* [0,65535] */;
  uint32_t fatimavme_qdc5board_id /* [0,255] */;
  uint32_t fatimavme_qdc5channels /* [0,255] */;
  uint32_t fatimavme_qdc5board_time /* [-1,-1] */;
  uint32_t fatimavme_qdc5channel_time /* [0,64] */;
  uint32_t fatimavme_qdc5channel_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc5channel_time)] /* [-1,-1] */;
  uint32_t fatimavme_qdc5chan_ext_time /* [0,64] */;
  uint32_t fatimavme_qdc5chan_ext_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc5chan_ext_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc5chan_fine_time /* [0,64] */;
  uint32_t fatimavme_qdc5chan_fine_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc5chan_fine_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc5qshort /* [0,64] */;
  uint32_t fatimavme_qdc5qshortv[64 EXT_STRUCT_CTRL(fatimavme_qdc5qshort)] /* [0,65535] */;
  uint32_t fatimavme_qdc5qlong /* [0,64] */;
  uint32_t fatimavme_qdc5qlongv[64 EXT_STRUCT_CTRL(fatimavme_qdc5qlong)] /* [0,65535] */;

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
  } fatimavme_tdc[2];
  uint32_t fatimavme_ts_subsystem_id;
  uint32_t fatimavme_ts_t[4];
  struct {
    uint32_t board_id;
    uint32_t channels;
    uint32_t board_time;
    uint32_t channel_time;
    uint32_t channel_timev[64 /* channel_time */];
    uint32_t chan_ext_time;
    uint32_t chan_ext_timev[64 /* chan_ext_time */];
    uint32_t chan_fine_time;
    uint32_t chan_fine_timev[64 /* chan_fine_time */];
    uint32_t qshort;
    uint32_t qshortv[64 /* qshort */];
    uint32_t qlong;
    uint32_t qlongv[64 /* qlong */];
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
                     fatimavme_tdc2_nM,               UINT32,\
                    "fatimavme_tdc2_nM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_nMI,              UINT32,\
                    "fatimavme_tdc2_nMI",              "fatimavme_tdc2_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_nME,              UINT32,\
                    "fatimavme_tdc2_nME",              "fatimavme_tdc2_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_n,                UINT32,\
                    "fatimavme_tdc2_n",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_data,             UINT32,\
                    "fatimavme_tdc2_data",             "fatimavme_tdc2_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_leadOrTrailM,     UINT32,\
                    "fatimavme_tdc2_leadOrTrailM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_leadOrTrailMI,    UINT32,\
                    "fatimavme_tdc2_leadOrTrailMI",    "fatimavme_tdc2_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_leadOrTrailME,    UINT32,\
                    "fatimavme_tdc2_leadOrTrailME",    "fatimavme_tdc2_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_leadOrTrail,      UINT32,\
                    "fatimavme_tdc2_leadOrTrail",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_leadOrTrailv,     UINT32,\
                    "fatimavme_tdc2_leadOrTrailv",     "fatimavme_tdc2_leadOrTrail",0/*flags*/); \
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
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1board_time,        UINT32,\
                    "fatimavme_qdc1board_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1channel_time,      UINT32,\
                    "fatimavme_qdc1channel_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1channel_timev,     UINT32,\
                    "fatimavme_qdc1channel_timev",     "fatimavme_qdc1channel_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1chan_ext_time,     UINT32,\
                    "fatimavme_qdc1chan_ext_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1chan_ext_timev,    UINT32,\
                    "fatimavme_qdc1chan_ext_timev",    "fatimavme_qdc1chan_ext_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1chan_fine_time,    UINT32,\
                    "fatimavme_qdc1chan_fine_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1chan_fine_timev,   UINT32,\
                    "fatimavme_qdc1chan_fine_timev",   "fatimavme_qdc1chan_fine_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1qshort,            UINT32,\
                    "fatimavme_qdc1qshort",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1qshortv,           UINT32,\
                    "fatimavme_qdc1qshortv",           "fatimavme_qdc1qshort",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1qlong,             UINT32,\
                    "fatimavme_qdc1qlong",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1qlongv,            UINT32,\
                    "fatimavme_qdc1qlongv",            "fatimavme_qdc1qlong",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2board_id,          UINT32,\
                    "fatimavme_qdc2board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2channels,          UINT32,\
                    "fatimavme_qdc2channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2board_time,        UINT32,\
                    "fatimavme_qdc2board_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2channel_time,      UINT32,\
                    "fatimavme_qdc2channel_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2channel_timev,     UINT32,\
                    "fatimavme_qdc2channel_timev",     "fatimavme_qdc2channel_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2chan_ext_time,     UINT32,\
                    "fatimavme_qdc2chan_ext_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2chan_ext_timev,    UINT32,\
                    "fatimavme_qdc2chan_ext_timev",    "fatimavme_qdc2chan_ext_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2chan_fine_time,    UINT32,\
                    "fatimavme_qdc2chan_fine_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2chan_fine_timev,   UINT32,\
                    "fatimavme_qdc2chan_fine_timev",   "fatimavme_qdc2chan_fine_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2qshort,            UINT32,\
                    "fatimavme_qdc2qshort",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2qshortv,           UINT32,\
                    "fatimavme_qdc2qshortv",           "fatimavme_qdc2qshort",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2qlong,             UINT32,\
                    "fatimavme_qdc2qlong",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2qlongv,            UINT32,\
                    "fatimavme_qdc2qlongv",            "fatimavme_qdc2qlong",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3board_id,          UINT32,\
                    "fatimavme_qdc3board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3channels,          UINT32,\
                    "fatimavme_qdc3channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3board_time,        UINT32,\
                    "fatimavme_qdc3board_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3channel_time,      UINT32,\
                    "fatimavme_qdc3channel_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3channel_timev,     UINT32,\
                    "fatimavme_qdc3channel_timev",     "fatimavme_qdc3channel_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3chan_ext_time,     UINT32,\
                    "fatimavme_qdc3chan_ext_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3chan_ext_timev,    UINT32,\
                    "fatimavme_qdc3chan_ext_timev",    "fatimavme_qdc3chan_ext_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3chan_fine_time,    UINT32,\
                    "fatimavme_qdc3chan_fine_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3chan_fine_timev,   UINT32,\
                    "fatimavme_qdc3chan_fine_timev",   "fatimavme_qdc3chan_fine_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3qshort,            UINT32,\
                    "fatimavme_qdc3qshort",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3qshortv,           UINT32,\
                    "fatimavme_qdc3qshortv",           "fatimavme_qdc3qshort",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3qlong,             UINT32,\
                    "fatimavme_qdc3qlong",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3qlongv,            UINT32,\
                    "fatimavme_qdc3qlongv",            "fatimavme_qdc3qlong",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4board_id,          UINT32,\
                    "fatimavme_qdc4board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4channels,          UINT32,\
                    "fatimavme_qdc4channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4board_time,        UINT32,\
                    "fatimavme_qdc4board_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4channel_time,      UINT32,\
                    "fatimavme_qdc4channel_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4channel_timev,     UINT32,\
                    "fatimavme_qdc4channel_timev",     "fatimavme_qdc4channel_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4chan_ext_time,     UINT32,\
                    "fatimavme_qdc4chan_ext_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4chan_ext_timev,    UINT32,\
                    "fatimavme_qdc4chan_ext_timev",    "fatimavme_qdc4chan_ext_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4chan_fine_time,    UINT32,\
                    "fatimavme_qdc4chan_fine_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4chan_fine_timev,   UINT32,\
                    "fatimavme_qdc4chan_fine_timev",   "fatimavme_qdc4chan_fine_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4qshort,            UINT32,\
                    "fatimavme_qdc4qshort",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4qshortv,           UINT32,\
                    "fatimavme_qdc4qshortv",           "fatimavme_qdc4qshort",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4qlong,             UINT32,\
                    "fatimavme_qdc4qlong",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4qlongv,            UINT32,\
                    "fatimavme_qdc4qlongv",            "fatimavme_qdc4qlong",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5board_id,          UINT32,\
                    "fatimavme_qdc5board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5channels,          UINT32,\
                    "fatimavme_qdc5channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5board_time,        UINT32,\
                    "fatimavme_qdc5board_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5channel_time,      UINT32,\
                    "fatimavme_qdc5channel_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5channel_timev,     UINT32,\
                    "fatimavme_qdc5channel_timev",     "fatimavme_qdc5channel_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5chan_ext_time,     UINT32,\
                    "fatimavme_qdc5chan_ext_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5chan_ext_timev,    UINT32,\
                    "fatimavme_qdc5chan_ext_timev",    "fatimavme_qdc5chan_ext_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5chan_fine_time,    UINT32,\
                    "fatimavme_qdc5chan_fine_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5chan_fine_timev,   UINT32,\
                    "fatimavme_qdc5chan_fine_timev",   "fatimavme_qdc5chan_fine_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5qshort,            UINT32,\
                    "fatimavme_qdc5qshort",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5qshortv,           UINT32,\
                    "fatimavme_qdc5qshortv",           "fatimavme_qdc5qshort",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5qlong,             UINT32,\
                    "fatimavme_qdc5qlong",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5qlongv,            UINT32,\
                    "fatimavme_qdc5qlongv",            "fatimavme_qdc5qlong",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FATIMAVME_EXT_H101_FATIMAVME_H__*/

/*******************************************************/
