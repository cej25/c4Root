/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_FRSUSER_EXT_H101_FRSUSER_H__
#define __GUARD_H101_FRSUSER_EXT_H101_FRSUSER_H__

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

typedef struct EXT_STR_h101_frsuser_t
{
  /* UNPACK */
  uint32_t frsuser_data_v830_n /* [0,32] */;
  uint32_t frsuser_data_v830_nI[32 EXT_STRUCT_CTRL(frsuser_data_v830_n)] /* [1,32] */;
  uint32_t frsuser_data_v830_data[32 EXT_STRUCT_CTRL(frsuser_data_v830_n)] /* [-1,-1] */;
  uint32_t frsuser_data_v7751n /* [0,32] */;
  uint32_t frsuser_data_v7751nI[32 EXT_STRUCT_CTRL(frsuser_data_v7751n)] /* [1,32] */;
  uint32_t frsuser_data_v7751data[32 EXT_STRUCT_CTRL(frsuser_data_v7751n)] /* [0,16777215] */;
  uint32_t frsuser_data_v7751channel /* [0,32] */;
  uint32_t frsuser_data_v7751channelI[32 EXT_STRUCT_CTRL(frsuser_data_v7751channel)] /* [1,32] */;
  uint32_t frsuser_data_v7751channelv[32 EXT_STRUCT_CTRL(frsuser_data_v7751channel)] /* [0,255] */;
  uint32_t frsuser_data_v7751geo /* [0,32] */;
  uint32_t frsuser_data_v7751geoI[32 EXT_STRUCT_CTRL(frsuser_data_v7751geo)] /* [1,32] */;
  uint32_t frsuser_data_v7751geov[32 EXT_STRUCT_CTRL(frsuser_data_v7751geo)] /* [0,255] */;
  uint32_t frsuser_data_v7752n /* [0,32] */;
  uint32_t frsuser_data_v7752nI[32 EXT_STRUCT_CTRL(frsuser_data_v7752n)] /* [1,32] */;
  uint32_t frsuser_data_v7752data[32 EXT_STRUCT_CTRL(frsuser_data_v7752n)] /* [0,16777215] */;
  uint32_t frsuser_data_v7752channel /* [0,32] */;
  uint32_t frsuser_data_v7752channelI[32 EXT_STRUCT_CTRL(frsuser_data_v7752channel)] /* [1,32] */;
  uint32_t frsuser_data_v7752channelv[32 EXT_STRUCT_CTRL(frsuser_data_v7752channel)] /* [0,255] */;
  uint32_t frsuser_data_v7752geo /* [0,32] */;
  uint32_t frsuser_data_v7752geoI[32 EXT_STRUCT_CTRL(frsuser_data_v7752geo)] /* [1,32] */;
  uint32_t frsuser_data_v7752geov[32 EXT_STRUCT_CTRL(frsuser_data_v7752geo)] /* [0,255] */;
  uint32_t frsuser_data_v7851n /* [0,32] */;
  uint32_t frsuser_data_v7851nI[32 EXT_STRUCT_CTRL(frsuser_data_v7851n)] /* [1,32] */;
  uint32_t frsuser_data_v7851data[32 EXT_STRUCT_CTRL(frsuser_data_v7851n)] /* [0,16777215] */;
  uint32_t frsuser_data_v7851channel /* [0,32] */;
  uint32_t frsuser_data_v7851channelI[32 EXT_STRUCT_CTRL(frsuser_data_v7851channel)] /* [1,32] */;
  uint32_t frsuser_data_v7851channelv[32 EXT_STRUCT_CTRL(frsuser_data_v7851channel)] /* [0,255] */;
  uint32_t frsuser_data_v7851geo /* [0,32] */;
  uint32_t frsuser_data_v7851geoI[32 EXT_STRUCT_CTRL(frsuser_data_v7851geo)] /* [1,32] */;
  uint32_t frsuser_data_v7851geov[32 EXT_STRUCT_CTRL(frsuser_data_v7851geo)] /* [0,255] */;
  uint32_t frsuser_data_v7852n /* [0,32] */;
  uint32_t frsuser_data_v7852nI[32 EXT_STRUCT_CTRL(frsuser_data_v7852n)] /* [1,32] */;
  uint32_t frsuser_data_v7852data[32 EXT_STRUCT_CTRL(frsuser_data_v7852n)] /* [0,16777215] */;
  uint32_t frsuser_data_v7852channel /* [0,32] */;
  uint32_t frsuser_data_v7852channelI[32 EXT_STRUCT_CTRL(frsuser_data_v7852channel)] /* [1,32] */;
  uint32_t frsuser_data_v7852channelv[32 EXT_STRUCT_CTRL(frsuser_data_v7852channel)] /* [0,255] */;
  uint32_t frsuser_data_v7852geo /* [0,32] */;
  uint32_t frsuser_data_v7852geoI[32 EXT_STRUCT_CTRL(frsuser_data_v7852geo)] /* [1,32] */;
  uint32_t frsuser_data_v7852geov[32 EXT_STRUCT_CTRL(frsuser_data_v7852geo)] /* [0,255] */;

} EXT_STR_h101_frsuser;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_frsuser_onion_t
{
  /* UNPACK */
  uint32_t frsuser_data_v830_n;
  uint32_t frsuser_data_v830_nI[32 /* frsuser_data_v830_n */];
  uint32_t frsuser_data_v830_data[32 /* frsuser_data_v830_n */];
  uint32_t frsuser_data_v7751n;
  uint32_t frsuser_data_v7751nI[32 /* frsuser_data_v7751n */];
  uint32_t frsuser_data_v7751data[32 /* frsuser_data_v7751n */];
  uint32_t frsuser_data_v7751channel;
  uint32_t frsuser_data_v7751channelI[32 /* frsuser_data_v7751channel */];
  uint32_t frsuser_data_v7751channelv[32 /* frsuser_data_v7751channel */];
  uint32_t frsuser_data_v7751geo;
  uint32_t frsuser_data_v7751geoI[32 /* frsuser_data_v7751geo */];
  uint32_t frsuser_data_v7751geov[32 /* frsuser_data_v7751geo */];
  uint32_t frsuser_data_v7752n;
  uint32_t frsuser_data_v7752nI[32 /* frsuser_data_v7752n */];
  uint32_t frsuser_data_v7752data[32 /* frsuser_data_v7752n */];
  uint32_t frsuser_data_v7752channel;
  uint32_t frsuser_data_v7752channelI[32 /* frsuser_data_v7752channel */];
  uint32_t frsuser_data_v7752channelv[32 /* frsuser_data_v7752channel */];
  uint32_t frsuser_data_v7752geo;
  uint32_t frsuser_data_v7752geoI[32 /* frsuser_data_v7752geo */];
  uint32_t frsuser_data_v7752geov[32 /* frsuser_data_v7752geo */];
  uint32_t frsuser_data_v7851n;
  uint32_t frsuser_data_v7851nI[32 /* frsuser_data_v7851n */];
  uint32_t frsuser_data_v7851data[32 /* frsuser_data_v7851n */];
  uint32_t frsuser_data_v7851channel;
  uint32_t frsuser_data_v7851channelI[32 /* frsuser_data_v7851channel */];
  uint32_t frsuser_data_v7851channelv[32 /* frsuser_data_v7851channel */];
  uint32_t frsuser_data_v7851geo;
  uint32_t frsuser_data_v7851geoI[32 /* frsuser_data_v7851geo */];
  uint32_t frsuser_data_v7851geov[32 /* frsuser_data_v7851geo */];
  uint32_t frsuser_data_v7852n;
  uint32_t frsuser_data_v7852nI[32 /* frsuser_data_v7852n */];
  uint32_t frsuser_data_v7852data[32 /* frsuser_data_v7852n */];
  uint32_t frsuser_data_v7852channel;
  uint32_t frsuser_data_v7852channelI[32 /* frsuser_data_v7852channel */];
  uint32_t frsuser_data_v7852channelv[32 /* frsuser_data_v7852channel */];
  uint32_t frsuser_data_v7852geo;
  uint32_t frsuser_data_v7852geoI[32 /* frsuser_data_v7852geo */];
  uint32_t frsuser_data_v7852geov[32 /* frsuser_data_v7852geo */];

} EXT_STR_h101_frsuser_onion;

/*******************************************************/

#define EXT_STR_h101_frsuser_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v830_n,             UINT32,\
                    "frsuser_data_v830_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v830_nI,            UINT32,\
                    "frsuser_data_v830_nI",            "frsuser_data_v830_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v830_data,          UINT32,\
                    "frsuser_data_v830_data",          "frsuser_data_v830_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7751n,             UINT32,\
                    "frsuser_data_v7751n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7751nI,            UINT32,\
                    "frsuser_data_v7751nI",            "frsuser_data_v7751n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7751data,          UINT32,\
                    "frsuser_data_v7751data",          "frsuser_data_v7751n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7751channel,       UINT32,\
                    "frsuser_data_v7751channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7751channelI,      UINT32,\
                    "frsuser_data_v7751channelI",      "frsuser_data_v7751channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7751channelv,      UINT32,\
                    "frsuser_data_v7751channelv",      "frsuser_data_v7751channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7751geo,           UINT32,\
                    "frsuser_data_v7751geo",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7751geoI,          UINT32,\
                    "frsuser_data_v7751geoI",          "frsuser_data_v7751geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7751geov,          UINT32,\
                    "frsuser_data_v7751geov",          "frsuser_data_v7751geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7752n,             UINT32,\
                    "frsuser_data_v7752n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7752nI,            UINT32,\
                    "frsuser_data_v7752nI",            "frsuser_data_v7752n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7752data,          UINT32,\
                    "frsuser_data_v7752data",          "frsuser_data_v7752n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7752channel,       UINT32,\
                    "frsuser_data_v7752channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7752channelI,      UINT32,\
                    "frsuser_data_v7752channelI",      "frsuser_data_v7752channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7752channelv,      UINT32,\
                    "frsuser_data_v7752channelv",      "frsuser_data_v7752channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7752geo,           UINT32,\
                    "frsuser_data_v7752geo",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7752geoI,          UINT32,\
                    "frsuser_data_v7752geoI",          "frsuser_data_v7752geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7752geov,          UINT32,\
                    "frsuser_data_v7752geov",          "frsuser_data_v7752geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7851n,             UINT32,\
                    "frsuser_data_v7851n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7851nI,            UINT32,\
                    "frsuser_data_v7851nI",            "frsuser_data_v7851n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7851data,          UINT32,\
                    "frsuser_data_v7851data",          "frsuser_data_v7851n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7851channel,       UINT32,\
                    "frsuser_data_v7851channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7851channelI,      UINT32,\
                    "frsuser_data_v7851channelI",      "frsuser_data_v7851channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7851channelv,      UINT32,\
                    "frsuser_data_v7851channelv",      "frsuser_data_v7851channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7851geo,           UINT32,\
                    "frsuser_data_v7851geo",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7851geoI,          UINT32,\
                    "frsuser_data_v7851geoI",          "frsuser_data_v7851geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7851geov,          UINT32,\
                    "frsuser_data_v7851geov",          "frsuser_data_v7851geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7852n,             UINT32,\
                    "frsuser_data_v7852n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7852nI,            UINT32,\
                    "frsuser_data_v7852nI",            "frsuser_data_v7852n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7852data,          UINT32,\
                    "frsuser_data_v7852data",          "frsuser_data_v7852n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7852channel,       UINT32,\
                    "frsuser_data_v7852channel",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7852channelI,      UINT32,\
                    "frsuser_data_v7852channelI",      "frsuser_data_v7852channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7852channelv,      UINT32,\
                    "frsuser_data_v7852channelv",      "frsuser_data_v7852channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7852geo,           UINT32,\
                    "frsuser_data_v7852geo",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7852geoI,          UINT32,\
                    "frsuser_data_v7852geoI",          "frsuser_data_v7852geo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsuser_data_v7852geov,          UINT32,\
                    "frsuser_data_v7852geov",          "frsuser_data_v7852geo",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FRSUSER_EXT_H101_FRSUSER_H__*/

/*******************************************************/
