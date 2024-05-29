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
  uint32_t fatimavme_ts_subsystem_id /* [0,65535] */;
  uint32_t fatimavme_ts_t1 /* [0,65535] */;
  uint32_t fatimavme_ts_t2 /* [0,65535] */;
  uint32_t fatimavme_ts_t3 /* [0,65535] */;
  uint32_t fatimavme_ts_t4 /* [0,65535] */;
  uint32_t fatimavme_scalers_n /* [0,32] */;
  uint32_t fatimavme_scalers_nI[32 EXT_STRUCT_CTRL(fatimavme_scalers_n)] /* [1,32] */;
  uint32_t fatimavme_scalers_data[32 EXT_STRUCT_CTRL(fatimavme_scalers_n)] /* [-1,-1] */;
  uint32_t fatimavme_qdc1_board_id /* [0,255] */;
  uint32_t fatimavme_qdc1_channels /* [0,255] */;
  uint32_t fatimavme_qdc1_board_time /* [-1,-1] */;
  uint32_t fatimavme_qdc1_channel_time /* [0,64] */;
  uint32_t fatimavme_qdc1_channel_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc1_channel_time)] /* [-1,-1] */;
  uint32_t fatimavme_qdc1_chan_ext_time /* [0,64] */;
  uint32_t fatimavme_qdc1_chan_ext_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc1_chan_ext_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_chan_fine_time /* [0,64] */;
  uint32_t fatimavme_qdc1_chan_fine_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc1_chan_fine_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_qshort /* [0,64] */;
  uint32_t fatimavme_qdc1_qshortv[64 EXT_STRUCT_CTRL(fatimavme_qdc1_qshort)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_qlong /* [0,64] */;
  uint32_t fatimavme_qdc1_qlongv[64 EXT_STRUCT_CTRL(fatimavme_qdc1_qlong)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_board_id /* [0,255] */;
  uint32_t fatimavme_qdc2_channels /* [0,255] */;
  uint32_t fatimavme_qdc2_board_time /* [-1,-1] */;
  uint32_t fatimavme_qdc2_channel_time /* [0,64] */;
  uint32_t fatimavme_qdc2_channel_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc2_channel_time)] /* [-1,-1] */;
  uint32_t fatimavme_qdc2_chan_ext_time /* [0,64] */;
  uint32_t fatimavme_qdc2_chan_ext_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc2_chan_ext_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_chan_fine_time /* [0,64] */;
  uint32_t fatimavme_qdc2_chan_fine_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc2_chan_fine_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_qshort /* [0,64] */;
  uint32_t fatimavme_qdc2_qshortv[64 EXT_STRUCT_CTRL(fatimavme_qdc2_qshort)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_qlong /* [0,64] */;
  uint32_t fatimavme_qdc2_qlongv[64 EXT_STRUCT_CTRL(fatimavme_qdc2_qlong)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_board_id /* [0,255] */;
  uint32_t fatimavme_qdc3_channels /* [0,255] */;
  uint32_t fatimavme_qdc3_board_time /* [-1,-1] */;
  uint32_t fatimavme_qdc3_channel_time /* [0,64] */;
  uint32_t fatimavme_qdc3_channel_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc3_channel_time)] /* [-1,-1] */;
  uint32_t fatimavme_qdc3_chan_ext_time /* [0,64] */;
  uint32_t fatimavme_qdc3_chan_ext_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc3_chan_ext_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_chan_fine_time /* [0,64] */;
  uint32_t fatimavme_qdc3_chan_fine_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc3_chan_fine_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_qshort /* [0,64] */;
  uint32_t fatimavme_qdc3_qshortv[64 EXT_STRUCT_CTRL(fatimavme_qdc3_qshort)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_qlong /* [0,64] */;
  uint32_t fatimavme_qdc3_qlongv[64 EXT_STRUCT_CTRL(fatimavme_qdc3_qlong)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_board_id /* [0,255] */;
  uint32_t fatimavme_qdc4_channels /* [0,255] */;
  uint32_t fatimavme_qdc4_board_time /* [-1,-1] */;
  uint32_t fatimavme_qdc4_channel_time /* [0,64] */;
  uint32_t fatimavme_qdc4_channel_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc4_channel_time)] /* [-1,-1] */;
  uint32_t fatimavme_qdc4_chan_ext_time /* [0,64] */;
  uint32_t fatimavme_qdc4_chan_ext_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc4_chan_ext_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_chan_fine_time /* [0,64] */;
  uint32_t fatimavme_qdc4_chan_fine_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc4_chan_fine_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_qshort /* [0,64] */;
  uint32_t fatimavme_qdc4_qshortv[64 EXT_STRUCT_CTRL(fatimavme_qdc4_qshort)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_qlong /* [0,64] */;
  uint32_t fatimavme_qdc4_qlongv[64 EXT_STRUCT_CTRL(fatimavme_qdc4_qlong)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_board_id /* [0,255] */;
  uint32_t fatimavme_qdc5_channels /* [0,255] */;
  uint32_t fatimavme_qdc5_board_time /* [-1,-1] */;
  uint32_t fatimavme_qdc5_channel_time /* [0,64] */;
  uint32_t fatimavme_qdc5_channel_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc5_channel_time)] /* [-1,-1] */;
  uint32_t fatimavme_qdc5_chan_ext_time /* [0,64] */;
  uint32_t fatimavme_qdc5_chan_ext_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc5_chan_ext_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_chan_fine_time /* [0,64] */;
  uint32_t fatimavme_qdc5_chan_fine_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc5_chan_fine_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_qshort /* [0,64] */;
  uint32_t fatimavme_qdc5_qshortv[64 EXT_STRUCT_CTRL(fatimavme_qdc5_qshort)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_qlong /* [0,64] */;
  uint32_t fatimavme_qdc5_qlongv[64 EXT_STRUCT_CTRL(fatimavme_qdc5_qlong)] /* [0,65535] */;
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
  uint32_t fatimavme_tdc1_geo /* [0,255] */;
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
  uint32_t fatimavme_tdc2_geo /* [0,255] */;

} EXT_STR_h101_fatimavme;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_fatimavme_onion_t
{
  /* UNPACK */
  uint32_t fatimavme_ts_subsystem_id;
  uint32_t fatimavme_ts_t[4];
  uint32_t fatimavme_scalers_n;
  uint32_t fatimavme_scalers_nI[32 /* fatimavme_scalers_n */];
  uint32_t fatimavme_scalers_data[32 /* fatimavme_scalers_n */];
  struct {
    uint32_t _board_id;
    uint32_t _channels;
    uint32_t _board_time;
    uint32_t _channel_time;
    uint32_t _channel_timev[64 /* _channel_time */];
    uint32_t _chan_ext_time;
    uint32_t _chan_ext_timev[64 /* _chan_ext_time */];
    uint32_t _chan_fine_time;
    uint32_t _chan_fine_timev[64 /* _chan_fine_time */];
    uint32_t _qshort;
    uint32_t _qshortv[64 /* _qshort */];
    uint32_t _qlong;
    uint32_t _qlongv[64 /* _qlong */];
  } fatimavme_qdc[5];
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
    uint32_t _geo;
  } fatimavme_tdc[2];

} EXT_STR_h101_fatimavme_onion;

/*******************************************************/

#define EXT_STR_h101_fatimavme_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
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
                     fatimavme_scalers_n,             UINT32,\
                    "fatimavme_scalers_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_scalers_nI,            UINT32,\
                    "fatimavme_scalers_nI",            "fatimavme_scalers_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_scalers_data,          UINT32,\
                    "fatimavme_scalers_data",          "fatimavme_scalers_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_board_id,         UINT32,\
                    "fatimavme_qdc1_board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_channels,         UINT32,\
                    "fatimavme_qdc1_channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_board_time,       UINT32,\
                    "fatimavme_qdc1_board_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_channel_time,     UINT32,\
                    "fatimavme_qdc1_channel_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_channel_timev,    UINT32,\
                    "fatimavme_qdc1_channel_timev",    "fatimavme_qdc1_channel_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_chan_ext_time,    UINT32,\
                    "fatimavme_qdc1_chan_ext_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_chan_ext_timev,   UINT32,\
                    "fatimavme_qdc1_chan_ext_timev",   "fatimavme_qdc1_chan_ext_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_chan_fine_time,   UINT32,\
                    "fatimavme_qdc1_chan_fine_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_chan_fine_timev,  UINT32,\
                    "fatimavme_qdc1_chan_fine_timev",  "fatimavme_qdc1_chan_fine_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_qshort,           UINT32,\
                    "fatimavme_qdc1_qshort",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_qshortv,          UINT32,\
                    "fatimavme_qdc1_qshortv",          "fatimavme_qdc1_qshort",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_qlong,            UINT32,\
                    "fatimavme_qdc1_qlong",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_qlongv,           UINT32,\
                    "fatimavme_qdc1_qlongv",           "fatimavme_qdc1_qlong",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_board_id,         UINT32,\
                    "fatimavme_qdc2_board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_channels,         UINT32,\
                    "fatimavme_qdc2_channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_board_time,       UINT32,\
                    "fatimavme_qdc2_board_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_channel_time,     UINT32,\
                    "fatimavme_qdc2_channel_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_channel_timev,    UINT32,\
                    "fatimavme_qdc2_channel_timev",    "fatimavme_qdc2_channel_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_chan_ext_time,    UINT32,\
                    "fatimavme_qdc2_chan_ext_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_chan_ext_timev,   UINT32,\
                    "fatimavme_qdc2_chan_ext_timev",   "fatimavme_qdc2_chan_ext_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_chan_fine_time,   UINT32,\
                    "fatimavme_qdc2_chan_fine_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_chan_fine_timev,  UINT32,\
                    "fatimavme_qdc2_chan_fine_timev",  "fatimavme_qdc2_chan_fine_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_qshort,           UINT32,\
                    "fatimavme_qdc2_qshort",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_qshortv,          UINT32,\
                    "fatimavme_qdc2_qshortv",          "fatimavme_qdc2_qshort",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_qlong,            UINT32,\
                    "fatimavme_qdc2_qlong",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_qlongv,           UINT32,\
                    "fatimavme_qdc2_qlongv",           "fatimavme_qdc2_qlong",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_board_id,         UINT32,\
                    "fatimavme_qdc3_board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_channels,         UINT32,\
                    "fatimavme_qdc3_channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_board_time,       UINT32,\
                    "fatimavme_qdc3_board_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_channel_time,     UINT32,\
                    "fatimavme_qdc3_channel_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_channel_timev,    UINT32,\
                    "fatimavme_qdc3_channel_timev",    "fatimavme_qdc3_channel_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_chan_ext_time,    UINT32,\
                    "fatimavme_qdc3_chan_ext_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_chan_ext_timev,   UINT32,\
                    "fatimavme_qdc3_chan_ext_timev",   "fatimavme_qdc3_chan_ext_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_chan_fine_time,   UINT32,\
                    "fatimavme_qdc3_chan_fine_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_chan_fine_timev,  UINT32,\
                    "fatimavme_qdc3_chan_fine_timev",  "fatimavme_qdc3_chan_fine_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_qshort,           UINT32,\
                    "fatimavme_qdc3_qshort",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_qshortv,          UINT32,\
                    "fatimavme_qdc3_qshortv",          "fatimavme_qdc3_qshort",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_qlong,            UINT32,\
                    "fatimavme_qdc3_qlong",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_qlongv,           UINT32,\
                    "fatimavme_qdc3_qlongv",           "fatimavme_qdc3_qlong",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_board_id,         UINT32,\
                    "fatimavme_qdc4_board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_channels,         UINT32,\
                    "fatimavme_qdc4_channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_board_time,       UINT32,\
                    "fatimavme_qdc4_board_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_channel_time,     UINT32,\
                    "fatimavme_qdc4_channel_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_channel_timev,    UINT32,\
                    "fatimavme_qdc4_channel_timev",    "fatimavme_qdc4_channel_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_chan_ext_time,    UINT32,\
                    "fatimavme_qdc4_chan_ext_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_chan_ext_timev,   UINT32,\
                    "fatimavme_qdc4_chan_ext_timev",   "fatimavme_qdc4_chan_ext_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_chan_fine_time,   UINT32,\
                    "fatimavme_qdc4_chan_fine_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_chan_fine_timev,  UINT32,\
                    "fatimavme_qdc4_chan_fine_timev",  "fatimavme_qdc4_chan_fine_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_qshort,           UINT32,\
                    "fatimavme_qdc4_qshort",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_qshortv,          UINT32,\
                    "fatimavme_qdc4_qshortv",          "fatimavme_qdc4_qshort",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_qlong,            UINT32,\
                    "fatimavme_qdc4_qlong",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_qlongv,           UINT32,\
                    "fatimavme_qdc4_qlongv",           "fatimavme_qdc4_qlong",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_board_id,         UINT32,\
                    "fatimavme_qdc5_board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_channels,         UINT32,\
                    "fatimavme_qdc5_channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_board_time,       UINT32,\
                    "fatimavme_qdc5_board_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_channel_time,     UINT32,\
                    "fatimavme_qdc5_channel_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_channel_timev,    UINT32,\
                    "fatimavme_qdc5_channel_timev",    "fatimavme_qdc5_channel_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_chan_ext_time,    UINT32,\
                    "fatimavme_qdc5_chan_ext_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_chan_ext_timev,   UINT32,\
                    "fatimavme_qdc5_chan_ext_timev",   "fatimavme_qdc5_chan_ext_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_chan_fine_time,   UINT32,\
                    "fatimavme_qdc5_chan_fine_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_chan_fine_timev,  UINT32,\
                    "fatimavme_qdc5_chan_fine_timev",  "fatimavme_qdc5_chan_fine_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_qshort,           UINT32,\
                    "fatimavme_qdc5_qshort",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_qshortv,          UINT32,\
                    "fatimavme_qdc5_qshortv",          "fatimavme_qdc5_qshort",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_qlong,            UINT32,\
                    "fatimavme_qdc5_qlong",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_qlongv,           UINT32,\
                    "fatimavme_qdc5_qlongv",           "fatimavme_qdc5_qlong",0/*flags*/); \
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
                     fatimavme_tdc1_geo,              UINT32,\
                    "fatimavme_tdc1_geo",255,0/*flags*/); \
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
                     fatimavme_tdc2_geo,              UINT32,\
                    "fatimavme_tdc2_geo",255,0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FATIMAVME_EXT_H101_FATIMAVME_H__*/

/*******************************************************/
