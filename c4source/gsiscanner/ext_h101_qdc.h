/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_QDC_EXT_H101_QDC_H__
#define __GUARD_H101_QDC_EXT_H101_QDC_H__

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

typedef struct EXT_STR_h101_qdc_t
{
  /* UNPACK */
  uint32_t qdc_data1n /* [0,32] */;
  uint32_t qdc_data1nI[32 EXT_STRUCT_CTRL(qdc_data1n)] /* [1,32] */;
  uint32_t qdc_data1data[32 EXT_STRUCT_CTRL(qdc_data1n)] /* [0,16777215] */;
  uint32_t qdc_data2n /* [0,32] */;
  uint32_t qdc_data2nI[32 EXT_STRUCT_CTRL(qdc_data2n)] /* [1,32] */;
  uint32_t qdc_data2data[32 EXT_STRUCT_CTRL(qdc_data2n)] /* [0,16777215] */;

} EXT_STR_h101_qdc;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_qdc_onion_t
{
  /* UNPACK */
  struct {
    uint32_t n;
    uint32_t nI[32 /* n */];
    uint32_t data[32 /* n */];
  } qdc_data[2];

} EXT_STR_h101_qdc_onion;

/*******************************************************/

#define EXT_STR_h101_qdc_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     qdc_data1n,                      UINT32,\
                    "qdc_data1n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     qdc_data1nI,                     UINT32,\
                    "qdc_data1nI",                     "qdc_data1n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     qdc_data1data,                   UINT32,\
                    "qdc_data1data",                   "qdc_data1n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     qdc_data2n,                      UINT32,\
                    "qdc_data2n",32,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     qdc_data2nI,                     UINT32,\
                    "qdc_data2nI",                     "qdc_data2n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     qdc_data2data,                   UINT32,\
                    "qdc_data2data",                   "qdc_data2n",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_QDC_EXT_H101_QDC_H__*/

/*******************************************************/
