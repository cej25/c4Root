/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_EXT_H101_FRS_H__
#define __GUARD_H101_EXT_H101_FRS_H__

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

typedef struct EXT_STR_h101_FRS_t
{
  /* INFO */
  uint32_t TRIGGER /* [0,15] */;
  uint32_t EVENTNO /* [-1,-1] */;
  /* RAW */
  float    Z /* [-1,-1] */;
  float    AoQ /* [-1,-1] */;
  float    Xtwo /* [-1,-1] */;
  float    Xfour /* [-1,-1] */;
  float    Atwo /* [-1,-1] */;
  float    Afour /* [-1,-1] */;
  float    beta /* [-1,-1] */;

} EXT_STR_h101_FRS;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_FRS_onion_t
{
  /* INFO */
  uint32_t TRIGGER;
  uint32_t EVENTNO;
  /* RAW */
  float    Z;
  float    AoQ;
  float    Xtwo;
  float    Xfour;
  float    Atwo;
  float    Afour;
  float    beta;

} EXT_STR_h101_FRS_onion;

/*******************************************************/

#define EXT_STR_h101_FRS_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* INFO */ \
  EXT_STR_ITEM_INFO_LIM(ok,si,offset,struct_t,printerr,\
                     TRIGGER,                         UINT32,\
                    "TRIGGER",15); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     EVENTNO,                         UINT32,\
                    "EVENTNO"); \
  /* RAW */ \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     Z,                               FLOAT32,\
                    "Z"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     AoQ,                             FLOAT32,\
                    "AoQ"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     Xtwo,                            FLOAT32,\
                    "Xtwo"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     Xfour,                           FLOAT32,\
                    "Xfour"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     Atwo,                            FLOAT32,\
                    "Atwo"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     Afour,                           FLOAT32,\
                    "Afour"); \
  EXT_STR_ITEM_INFO    (ok,si,offset,struct_t,printerr,\
                     beta,                            FLOAT32,\
                    "beta"); \
  \
} while (0);

/********************************************************
 *
 * For internal use by the network data reader:
 * (version checks, etc)
 */

typedef struct EXT_STR_h101_FRS_layout_t
{
  uint32_t _magic;
  uint32_t _size_info;
  uint32_t _size_struct;
  uint32_t _size_struct_onion;
  uint32_t _pack_list_items;

  uint32_t _num_items;
  struct {
    uint32_t _offset;
    uint32_t _size;
    uint32_t _xor;
    const char *_name;
  } _items[1];
  uint32_t _pack_list[18];
} EXT_STR_h101_FRS_layout;

#define EXT_STR_h101_FRS_LAYOUT_INIT { \
  0x57e65c97, \
  sizeof(EXT_STR_h101_FRS_layout), \
  sizeof(EXT_STR_h101_FRS), \
  sizeof(EXT_STR_h101_FRS_onion), \
  18, \
  1, \
  { \
    { 0, sizeof(EXT_STR_h101_FRS), 0x3acb357f, "h101" }, \
  }, \
  { \
   /*    0 */ 0x40a52000, 0x00000000, 0x40a52000, 0x00000004, \
   /*    4 */ 0x00a50000, 0x00000008, 0x00a50000, 0x0000000c, \
   /*    8 */ 0x00a50000, 0x00000010, 0x00a50000, 0x00000014, \
   /*   12 */ 0x00a50000, 0x00000018, 0x00a50000, 0x0000001c, \
   /*   16 */ 0x00a50000, 0x00000020, \
  } \
};

#endif/*__GUARD_H101_EXT_H101_FRS_H__*/

/*******************************************************/
