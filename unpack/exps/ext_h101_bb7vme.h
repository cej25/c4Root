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
  uint32_t bb7_ts_subsystem_id /* [0,65535] */;
  uint32_t bb7_ts_t1 /* [0,65535] */;
  uint32_t bb7_ts_t2 /* [0,65535] */;
  uint32_t bb7_ts_t3 /* [0,65535] */;
  uint32_t bb7_ts_t4 /* [0,65535] */;
  uint32_t bb7_v7x51n /* [0,32] */;
  uint32_t bb7_v7x51nI[32 EXT_STRUCT_CTRL(bb7_v7x51n)] /* [1,32] */;
  uint32_t bb7_v7x51data[32 EXT_STRUCT_CTRL(bb7_v7x51n)] /* [0,16777215] */;
  uint32_t bb7_v7x51channel /* [0,32] */;
  uint32_t bb7_v7x51channelI[32 EXT_STRUCT_CTRL(bb7_v7x51channel)] /* [1,32] */;
  uint32_t bb7_v7x51channelv[32 EXT_STRUCT_CTRL(bb7_v7x51channel)] /* [0,255] */;
  uint32_t bb7_v7x51geo /* [0,32] */;
  uint32_t bb7_v7x51geoI[32 EXT_STRUCT_CTRL(bb7_v7x51geo)] /* [1,32] */;
  uint32_t bb7_v7x51geov[32 EXT_STRUCT_CTRL(bb7_v7x51geo)] /* [0,255] */;

} EXT_STR_h101_bb7vme;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_bb7vme_onion_t
{
  /* UNPACK */
  uint32_t bb7_ts_subsystem_id;
  uint32_t bb7_ts_t1;
  uint32_t bb7_ts_t2;
  uint32_t bb7_ts_t3;
  uint32_t bb7_ts_t4;
  uint32_t bb7_v7x51n;
  uint32_t bb7_v7x51nI[32 /* bb7_v7x51n */];
  uint32_t bb7_v7x51data[32 /* bb7_v7x51n */];
  uint32_t bb7_v7x51channel;
  uint32_t bb7_v7x51channelI[32 /* bb7_v7x51channel */];
  uint32_t bb7_v7x51channelv[32 /* bb7_v7x51channel */];
  uint32_t bb7_v7x51geo;
  uint32_t bb7_v7x51geoI[32 /* bb7_v7x51geo */];
  uint32_t bb7_v7x51geov[32 /* bb7_v7x51geo */];

} EXT_STR_h101_bb7vme_onion;

/*******************************************************/

#define EXT_STR_h101_bb7vme_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bb7_ts_subsystem_id,             UINT32,\
                    "bb7_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bb7_ts_t1,                       UINT32,\
                    "bb7_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bb7_ts_t2,                       UINT32,\
                    "bb7_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bb7_ts_t3,                       UINT32,\
                    "bb7_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bb7_ts_t4,                       UINT32,\
                    "bb7_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bb7_v7x51n,                      UINT32,\
                    "bb7_v7x51n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bb7_v7x51nI,                     UINT32,\
                    "bb7_v7x51nI",                     "bb7_v7x51n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bb7_v7x51data,                   UINT32,\
                    "bb7_v7x51data",                   "bb7_v7x51n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bb7_v7x51channel,                UINT32,\
                    "bb7_v7x51channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bb7_v7x51channelI,               UINT32,\
                    "bb7_v7x51channelI",               "bb7_v7x51channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bb7_v7x51channelv,               UINT32,\
                    "bb7_v7x51channelv",               "bb7_v7x51channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bb7_v7x51geo,                    UINT32,\
                    "bb7_v7x51geo",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bb7_v7x51geoI,                   UINT32,\
                    "bb7_v7x51geoI",                   "bb7_v7x51geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bb7_v7x51geov,                   UINT32,\
                    "bb7_v7x51geov",                   "bb7_v7x51geo",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_BB7VME_EXT_H101_BB7VME_H__*/

/*******************************************************/
