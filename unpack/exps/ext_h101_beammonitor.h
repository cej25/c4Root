/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_BEAMMONITOR_EXT_H101_BEAMMONITOR_H__
#define __GUARD_H101_BEAMMONITOR_EXT_H101_BEAMMONITOR_H__

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

typedef struct EXT_STR_h101_beammonitor_t
{
  /* UNPACK */
  uint32_t beammonitor_dataS2 /* [0,100000] */;
  uint32_t beammonitor_dataS2v[100000 EXT_STRUCT_CTRL(beammonitor_dataS2)] /* [-1,-1] */;
  uint32_t beammonitor_dataS4 /* [0,100000] */;
  uint32_t beammonitor_dataS4v[100000 EXT_STRUCT_CTRL(beammonitor_dataS4)] /* [-1,-1] */;

} EXT_STR_h101_beammonitor;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_beammonitor_onion_t
{
  /* UNPACK */
  uint32_t beammonitor_dataS2;
  uint32_t beammonitor_dataS2v[100000 /* beammonitor_dataS2 */];
  uint32_t beammonitor_dataS4;
  uint32_t beammonitor_dataS4v[100000 /* beammonitor_dataS4 */];

} EXT_STR_h101_beammonitor_onion;

/*******************************************************/

#define EXT_STR_h101_beammonitor_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     beammonitor_dataS2,              UINT32,\
                    "beammonitor_dataS2",100000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     beammonitor_dataS2v,             UINT32,\
                    "beammonitor_dataS2v",             "beammonitor_dataS2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     beammonitor_dataS4,              UINT32,\
                    "beammonitor_dataS4",100000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     beammonitor_dataS4v,             UINT32,\
                    "beammonitor_dataS4v",             "beammonitor_dataS4",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_BEAMMONITOR_EXT_H101_BEAMMONITOR_H__*/

/*******************************************************/
