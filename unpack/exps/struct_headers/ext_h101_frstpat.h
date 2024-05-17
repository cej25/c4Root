/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_FRSTPAT_EXT_H101_FRSTPAT_H__
#define __GUARD_H101_FRSTPAT_EXT_H101_FRSTPAT_H__

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

typedef struct EXT_STR_h101_frstpat_t
{
  /* UNPACK */
  uint32_t frstpat_wr_subsystem_id /* [0,65535] */;
  uint32_t frstpat_wr_t1 /* [0,65535] */;
  uint32_t frstpat_wr_t2 /* [0,65535] */;
  uint32_t frstpat_wr_t3 /* [0,65535] */;
  uint32_t frstpat_wr_t4 /* [0,65535] */;
  uint32_t frstpat_data_tpat /* [0,65535] */;
  uint32_t frstpat_data_w1 /* [-1,-1] */;
  uint32_t frstpat_data_w2 /* [-1,-1] */;
  uint32_t frstpat_data_w3 /* [-1,-1] */;
  uint32_t frstpat_data_trigger_pattern /* [-1,-1] */;

} EXT_STR_h101_frstpat;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_frstpat_onion_t
{
  /* UNPACK */
  uint32_t frstpat_wr_subsystem_id;
  uint32_t frstpat_wr_t[4];
  uint32_t frstpat_data_tpat;
  uint32_t frstpat_data_w[3];
  uint32_t frstpat_data_trigger_pattern;

} EXT_STR_h101_frstpat_onion;

/*******************************************************/

#define EXT_STR_h101_frstpat_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpat_wr_subsystem_id,         UINT32,\
                    "frstpat_wr_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpat_wr_t1,                   UINT32,\
                    "frstpat_wr_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpat_wr_t2,                   UINT32,\
                    "frstpat_wr_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpat_wr_t3,                   UINT32,\
                    "frstpat_wr_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpat_wr_t4,                   UINT32,\
                    "frstpat_wr_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     frstpat_data_tpat,               UINT32,\
                    "frstpat_data_tpat",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     frstpat_data_w1,                 UINT32,\
                    "frstpat_data_w1",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     frstpat_data_w2,                 UINT32,\
                    "frstpat_data_w2",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     frstpat_data_w3,                 UINT32,\
                    "frstpat_data_w3",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     frstpat_data_trigger_pattern,    UINT32,\
                    "frstpat_data_trigger_pattern",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FRSTPAT_EXT_H101_FRSTPAT_H__*/

/*******************************************************/
