/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_FRSVFTX_EXT_H101_FRSVFTX_H__
#define __GUARD_H101_FRSVFTX_EXT_H101_FRSVFTX_H__

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

typedef struct EXT_STR_h101_frsvftx_t
{
  /* UNPACK */
  uint32_t frsvftx_data_mqdc0_n /* [0,32] */;
  uint32_t frsvftx_data_mqdc0_nI[32 EXT_STRUCT_CTRL(frsvftx_data_mqdc0_n)] /* [1,32] */;
  uint32_t frsvftx_data_mqdc0_data[32 EXT_STRUCT_CTRL(frsvftx_data_mqdc0_n)] /* [0,65535] */;
  uint32_t frsvftx_data_mqdc1_n /* [0,32] */;
  uint32_t frsvftx_data_mqdc1_nI[32 EXT_STRUCT_CTRL(frsvftx_data_mqdc1_n)] /* [1,32] */;
  uint32_t frsvftx_data_mqdc1_data[32 EXT_STRUCT_CTRL(frsvftx_data_mqdc1_n)] /* [0,65535] */;
  uint32_t frsvftx_data_vftx_time_fineM /* [1,32] */;
  uint32_t frsvftx_data_vftx_time_fineMI[32 EXT_STRUCT_CTRL(frsvftx_data_vftx_time_fineM)] /* [1,32] */;
  uint32_t frsvftx_data_vftx_time_fineME[32 EXT_STRUCT_CTRL(frsvftx_data_vftx_time_fineM)] /* [1,3200] */;
  uint32_t frsvftx_data_vftx_time_fine /* [0,3200] */;
  uint32_t frsvftx_data_vftx_time_finev[3200 EXT_STRUCT_CTRL(frsvftx_data_vftx_time_fine)] /* [0,65535] */;
  uint32_t frsvftx_data_vftx_time_coarseM /* [1,32] */;
  uint32_t frsvftx_data_vftx_time_coarseMI[32 EXT_STRUCT_CTRL(frsvftx_data_vftx_time_coarseM)] /* [1,32] */;
  uint32_t frsvftx_data_vftx_time_coarseME[32 EXT_STRUCT_CTRL(frsvftx_data_vftx_time_coarseM)] /* [1,3200] */;
  uint32_t frsvftx_data_vftx_time_coarse /* [0,3200] */;
  uint32_t frsvftx_data_vftx_time_coarsev[3200 EXT_STRUCT_CTRL(frsvftx_data_vftx_time_coarse)] /* [0,65535] */;
  uint32_t frsvftx_data_vftx_time_trigger /* [0,65535] */;
  uint32_t frsvftx_data_mtdc_n /* [0,34] */;
  uint32_t frsvftx_data_mtdc_nI[34 EXT_STRUCT_CTRL(frsvftx_data_mtdc_n)] /* [1,34] */;
  uint32_t frsvftx_data_mtdc_data[34 EXT_STRUCT_CTRL(frsvftx_data_mtdc_n)] /* [0,65535] */;

} EXT_STR_h101_frsvftx;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_frsvftx_onion_t
{
  /* UNPACK */
  uint32_t frsvftx_data_mqdc0_n;
  uint32_t frsvftx_data_mqdc0_nI[32 /* frsvftx_data_mqdc0_n */];
  uint32_t frsvftx_data_mqdc0_data[32 /* frsvftx_data_mqdc0_n */];
  struct {
    uint32_t _n;
    uint32_t _nI[32 /* _n */];
    uint32_t _data[32 /* _n */];
  } frsvftx_data_mqdc[1];
  uint32_t frsvftx_data_vftx_time_fineM;
  uint32_t frsvftx_data_vftx_time_fineMI[32 /* frsvftx_data_vftx_time_fineM */];
  uint32_t frsvftx_data_vftx_time_fineME[32 /* frsvftx_data_vftx_time_fineM */];
  uint32_t frsvftx_data_vftx_time_fine;
  uint32_t frsvftx_data_vftx_time_finev[3200 /* frsvftx_data_vftx_time_fine */];
  uint32_t frsvftx_data_vftx_time_coarseM;
  uint32_t frsvftx_data_vftx_time_coarseMI[32 /* frsvftx_data_vftx_time_coarseM */];
  uint32_t frsvftx_data_vftx_time_coarseME[32 /* frsvftx_data_vftx_time_coarseM */];
  uint32_t frsvftx_data_vftx_time_coarse;
  uint32_t frsvftx_data_vftx_time_coarsev[3200 /* frsvftx_data_vftx_time_coarse */];
  uint32_t frsvftx_data_vftx_time_trigger;
  uint32_t frsvftx_data_mtdc_n;
  uint32_t frsvftx_data_mtdc_nI[34 /* frsvftx_data_mtdc_n */];
  uint32_t frsvftx_data_mtdc_data[34 /* frsvftx_data_mtdc_n */];

} EXT_STR_h101_frsvftx_onion;

/*******************************************************/

#define EXT_STR_h101_frsvftx_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_mqdc0_n,            UINT32,\
                    "frsvftx_data_mqdc0_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_mqdc0_nI,           UINT32,\
                    "frsvftx_data_mqdc0_nI",           "frsvftx_data_mqdc0_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_mqdc0_data,         UINT32,\
                    "frsvftx_data_mqdc0_data",         "frsvftx_data_mqdc0_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_mqdc1_n,            UINT32,\
                    "frsvftx_data_mqdc1_n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_mqdc1_nI,           UINT32,\
                    "frsvftx_data_mqdc1_nI",           "frsvftx_data_mqdc1_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_mqdc1_data,         UINT32,\
                    "frsvftx_data_mqdc1_data",         "frsvftx_data_mqdc1_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_vftx_time_fineM,    UINT32,\
                    "frsvftx_data_vftx_time_fineM",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_vftx_time_fineMI,   UINT32,\
                    "frsvftx_data_vftx_time_fineMI",   "frsvftx_data_vftx_time_fineM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_vftx_time_fineME,   UINT32,\
                    "frsvftx_data_vftx_time_fineME",   "frsvftx_data_vftx_time_fineM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_vftx_time_fine,     UINT32,\
                    "frsvftx_data_vftx_time_fine",3200,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_vftx_time_finev,    UINT32,\
                    "frsvftx_data_vftx_time_finev",    "frsvftx_data_vftx_time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_vftx_time_coarseM,  UINT32,\
                    "frsvftx_data_vftx_time_coarseM",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_vftx_time_coarseMI, UINT32,\
                    "frsvftx_data_vftx_time_coarseMI", "frsvftx_data_vftx_time_coarseM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_vftx_time_coarseME, UINT32,\
                    "frsvftx_data_vftx_time_coarseME", "frsvftx_data_vftx_time_coarseM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_vftx_time_coarse,   UINT32,\
                    "frsvftx_data_vftx_time_coarse",3200,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_vftx_time_coarsev,  UINT32,\
                    "frsvftx_data_vftx_time_coarsev",  "frsvftx_data_vftx_time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_vftx_time_trigger,  UINT32,\
                    "frsvftx_data_vftx_time_trigger",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_mtdc_n,             UINT32,\
                    "frsvftx_data_mtdc_n",34,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_mtdc_nI,            UINT32,\
                    "frsvftx_data_mtdc_nI",            "frsvftx_data_mtdc_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     frsvftx_data_mtdc_data,          UINT32,\
                    "frsvftx_data_mtdc_data",          "frsvftx_data_mtdc_n",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FRSVFTX_EXT_H101_FRSVFTX_H__*/

/*******************************************************/
