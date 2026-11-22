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
  uint32_t fatimavme_qdc1extras /* [0,65535] */;
  uint32_t fatimavme_qdc1dm /* [0,65535] */;
  uint32_t fatimavme_qdc1chan_baseline /* [0,64] */;
  uint32_t fatimavme_qdc1chan_baselinev[64 EXT_STRUCT_CTRL(fatimavme_qdc1chan_baseline)] /* [0,65535] */;
  uint32_t fatimavme_qdc1chan_midscale /* [0,64] */;
  uint32_t fatimavme_qdc1chan_midscalev[64 EXT_STRUCT_CTRL(fatimavme_qdc1chan_midscale)] /* [0,65535] */;
  uint32_t fatimavme_qdc1chan_sazc /* [0,64] */;
  uint32_t fatimavme_qdc1chan_sazcv[64 EXT_STRUCT_CTRL(fatimavme_qdc1chan_sazc)] /* [0,65535] */;
  uint32_t fatimavme_qdc1chan_sbzc /* [0,64] */;
  uint32_t fatimavme_qdc1chan_sbzcv[64 EXT_STRUCT_CTRL(fatimavme_qdc1chan_sbzc)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_one1 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_one1I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one1)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_one1v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one1)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_one2 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_one2I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one2)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_one2v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one2)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_one3 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_one3I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one3)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_one3v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one3)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_one4 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_one4I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one4)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_one4v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one4)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_one5 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_one5I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one5)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_one5v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one5)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_one6 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_one6I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one6)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_one6v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one6)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_one7 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_one7I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one7)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_one7v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one7)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_one8 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_one8I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one8)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_one8v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_one8)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_two1 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_two1I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two1)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_two1v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two1)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_two2 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_two2I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two2)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_two2v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two2)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_two3 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_two3I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two3)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_two3v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two3)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_two4 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_two4I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two4)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_two4v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two4)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_two5 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_two5I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two5)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_two5v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two5)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_two6 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_two6I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two6)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_two6v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two6)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_two7 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_two7I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two7)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_two7v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two7)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_two8 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_two8I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two8)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_two8v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_two8)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_three1 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_three1I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three1)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_three1v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three1)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_three2 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_three2I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three2)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_three2v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three2)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_three3 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_three3I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three3)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_three3v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three3)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_three4 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_three4I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three4)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_three4v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three4)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_three5 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_three5I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three5)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_three5v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three5)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_three6 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_three6I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three6)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_three6v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three6)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_three7 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_three7I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three7)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_three7v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three7)] /* [0,65535] */;
  uint32_t fatimavme_qdc1sample_three8 /* [0,120] */;
  uint32_t fatimavme_qdc1sample_three8I[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three8)] /* [1,120] */;
  uint32_t fatimavme_qdc1sample_three8v[120 EXT_STRUCT_CTRL(fatimavme_qdc1sample_three8)] /* [0,65535] */;
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
  uint32_t fatimavme_qdc2extras /* [0,65535] */;
  uint32_t fatimavme_qdc2dm /* [0,65535] */;
  uint32_t fatimavme_qdc2chan_baseline /* [0,64] */;
  uint32_t fatimavme_qdc2chan_baselinev[64 EXT_STRUCT_CTRL(fatimavme_qdc2chan_baseline)] /* [0,65535] */;
  uint32_t fatimavme_qdc2chan_midscale /* [0,64] */;
  uint32_t fatimavme_qdc2chan_midscalev[64 EXT_STRUCT_CTRL(fatimavme_qdc2chan_midscale)] /* [0,65535] */;
  uint32_t fatimavme_qdc2chan_sazc /* [0,64] */;
  uint32_t fatimavme_qdc2chan_sazcv[64 EXT_STRUCT_CTRL(fatimavme_qdc2chan_sazc)] /* [0,65535] */;
  uint32_t fatimavme_qdc2chan_sbzc /* [0,64] */;
  uint32_t fatimavme_qdc2chan_sbzcv[64 EXT_STRUCT_CTRL(fatimavme_qdc2chan_sbzc)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_one1 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_one1I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one1)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_one1v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one1)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_one2 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_one2I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one2)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_one2v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one2)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_one3 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_one3I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one3)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_one3v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one3)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_one4 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_one4I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one4)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_one4v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one4)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_one5 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_one5I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one5)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_one5v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one5)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_one6 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_one6I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one6)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_one6v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one6)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_one7 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_one7I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one7)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_one7v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one7)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_one8 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_one8I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one8)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_one8v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_one8)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_two1 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_two1I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two1)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_two1v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two1)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_two2 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_two2I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two2)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_two2v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two2)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_two3 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_two3I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two3)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_two3v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two3)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_two4 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_two4I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two4)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_two4v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two4)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_two5 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_two5I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two5)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_two5v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two5)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_two6 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_two6I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two6)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_two6v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two6)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_two7 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_two7I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two7)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_two7v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two7)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_two8 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_two8I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two8)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_two8v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_two8)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_three1 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_three1I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three1)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_three1v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three1)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_three2 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_three2I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three2)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_three2v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three2)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_three3 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_three3I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three3)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_three3v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three3)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_three4 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_three4I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three4)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_three4v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three4)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_three5 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_three5I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three5)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_three5v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three5)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_three6 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_three6I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three6)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_three6v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three6)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_three7 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_three7I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three7)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_three7v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three7)] /* [0,65535] */;
  uint32_t fatimavme_qdc2sample_three8 /* [0,120] */;
  uint32_t fatimavme_qdc2sample_three8I[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three8)] /* [1,120] */;
  uint32_t fatimavme_qdc2sample_three8v[120 EXT_STRUCT_CTRL(fatimavme_qdc2sample_three8)] /* [0,65535] */;
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
  uint32_t fatimavme_qdc3extras /* [0,65535] */;
  uint32_t fatimavme_qdc3dm /* [0,65535] */;
  uint32_t fatimavme_qdc3chan_baseline /* [0,64] */;
  uint32_t fatimavme_qdc3chan_baselinev[64 EXT_STRUCT_CTRL(fatimavme_qdc3chan_baseline)] /* [0,65535] */;
  uint32_t fatimavme_qdc3chan_midscale /* [0,64] */;
  uint32_t fatimavme_qdc3chan_midscalev[64 EXT_STRUCT_CTRL(fatimavme_qdc3chan_midscale)] /* [0,65535] */;
  uint32_t fatimavme_qdc3chan_sazc /* [0,64] */;
  uint32_t fatimavme_qdc3chan_sazcv[64 EXT_STRUCT_CTRL(fatimavme_qdc3chan_sazc)] /* [0,65535] */;
  uint32_t fatimavme_qdc3chan_sbzc /* [0,64] */;
  uint32_t fatimavme_qdc3chan_sbzcv[64 EXT_STRUCT_CTRL(fatimavme_qdc3chan_sbzc)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_one1 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_one1I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one1)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_one1v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one1)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_one2 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_one2I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one2)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_one2v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one2)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_one3 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_one3I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one3)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_one3v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one3)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_one4 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_one4I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one4)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_one4v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one4)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_one5 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_one5I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one5)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_one5v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one5)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_one6 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_one6I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one6)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_one6v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one6)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_one7 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_one7I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one7)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_one7v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one7)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_one8 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_one8I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one8)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_one8v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_one8)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_two1 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_two1I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two1)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_two1v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two1)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_two2 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_two2I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two2)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_two2v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two2)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_two3 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_two3I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two3)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_two3v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two3)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_two4 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_two4I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two4)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_two4v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two4)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_two5 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_two5I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two5)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_two5v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two5)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_two6 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_two6I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two6)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_two6v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two6)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_two7 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_two7I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two7)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_two7v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two7)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_two8 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_two8I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two8)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_two8v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_two8)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_three1 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_three1I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three1)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_three1v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three1)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_three2 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_three2I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three2)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_three2v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three2)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_three3 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_three3I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three3)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_three3v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three3)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_three4 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_three4I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three4)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_three4v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three4)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_three5 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_three5I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three5)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_three5v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three5)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_three6 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_three6I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three6)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_three6v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three6)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_three7 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_three7I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three7)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_three7v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three7)] /* [0,65535] */;
  uint32_t fatimavme_qdc3sample_three8 /* [0,120] */;
  uint32_t fatimavme_qdc3sample_three8I[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three8)] /* [1,120] */;
  uint32_t fatimavme_qdc3sample_three8v[120 EXT_STRUCT_CTRL(fatimavme_qdc3sample_three8)] /* [0,65535] */;
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
  uint32_t fatimavme_qdc4extras /* [0,65535] */;
  uint32_t fatimavme_qdc4dm /* [0,65535] */;
  uint32_t fatimavme_qdc4chan_baseline /* [0,64] */;
  uint32_t fatimavme_qdc4chan_baselinev[64 EXT_STRUCT_CTRL(fatimavme_qdc4chan_baseline)] /* [0,65535] */;
  uint32_t fatimavme_qdc4chan_midscale /* [0,64] */;
  uint32_t fatimavme_qdc4chan_midscalev[64 EXT_STRUCT_CTRL(fatimavme_qdc4chan_midscale)] /* [0,65535] */;
  uint32_t fatimavme_qdc4chan_sazc /* [0,64] */;
  uint32_t fatimavme_qdc4chan_sazcv[64 EXT_STRUCT_CTRL(fatimavme_qdc4chan_sazc)] /* [0,65535] */;
  uint32_t fatimavme_qdc4chan_sbzc /* [0,64] */;
  uint32_t fatimavme_qdc4chan_sbzcv[64 EXT_STRUCT_CTRL(fatimavme_qdc4chan_sbzc)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_one1 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_one1I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one1)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_one1v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one1)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_one2 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_one2I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one2)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_one2v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one2)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_one3 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_one3I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one3)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_one3v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one3)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_one4 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_one4I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one4)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_one4v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one4)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_one5 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_one5I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one5)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_one5v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one5)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_one6 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_one6I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one6)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_one6v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one6)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_one7 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_one7I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one7)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_one7v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one7)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_one8 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_one8I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one8)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_one8v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_one8)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_two1 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_two1I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two1)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_two1v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two1)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_two2 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_two2I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two2)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_two2v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two2)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_two3 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_two3I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two3)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_two3v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two3)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_two4 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_two4I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two4)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_two4v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two4)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_two5 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_two5I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two5)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_two5v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two5)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_two6 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_two6I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two6)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_two6v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two6)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_two7 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_two7I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two7)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_two7v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two7)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_two8 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_two8I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two8)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_two8v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_two8)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_three1 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_three1I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three1)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_three1v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three1)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_three2 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_three2I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three2)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_three2v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three2)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_three3 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_three3I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three3)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_three3v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three3)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_three4 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_three4I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three4)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_three4v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three4)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_three5 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_three5I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three5)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_three5v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three5)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_three6 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_three6I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three6)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_three6v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three6)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_three7 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_three7I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three7)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_three7v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three7)] /* [0,65535] */;
  uint32_t fatimavme_qdc4sample_three8 /* [0,120] */;
  uint32_t fatimavme_qdc4sample_three8I[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three8)] /* [1,120] */;
  uint32_t fatimavme_qdc4sample_three8v[120 EXT_STRUCT_CTRL(fatimavme_qdc4sample_three8)] /* [0,65535] */;
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
  uint32_t fatimavme_qdc5extras /* [0,65535] */;
  uint32_t fatimavme_qdc5dm /* [0,65535] */;
  uint32_t fatimavme_qdc5chan_baseline /* [0,64] */;
  uint32_t fatimavme_qdc5chan_baselinev[64 EXT_STRUCT_CTRL(fatimavme_qdc5chan_baseline)] /* [0,65535] */;
  uint32_t fatimavme_qdc5chan_midscale /* [0,64] */;
  uint32_t fatimavme_qdc5chan_midscalev[64 EXT_STRUCT_CTRL(fatimavme_qdc5chan_midscale)] /* [0,65535] */;
  uint32_t fatimavme_qdc5chan_sazc /* [0,64] */;
  uint32_t fatimavme_qdc5chan_sazcv[64 EXT_STRUCT_CTRL(fatimavme_qdc5chan_sazc)] /* [0,65535] */;
  uint32_t fatimavme_qdc5chan_sbzc /* [0,64] */;
  uint32_t fatimavme_qdc5chan_sbzcv[64 EXT_STRUCT_CTRL(fatimavme_qdc5chan_sbzc)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_one1 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_one1I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one1)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_one1v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one1)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_one2 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_one2I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one2)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_one2v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one2)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_one3 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_one3I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one3)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_one3v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one3)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_one4 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_one4I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one4)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_one4v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one4)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_one5 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_one5I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one5)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_one5v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one5)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_one6 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_one6I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one6)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_one6v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one6)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_one7 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_one7I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one7)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_one7v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one7)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_one8 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_one8I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one8)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_one8v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_one8)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_two1 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_two1I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two1)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_two1v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two1)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_two2 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_two2I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two2)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_two2v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two2)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_two3 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_two3I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two3)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_two3v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two3)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_two4 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_two4I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two4)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_two4v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two4)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_two5 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_two5I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two5)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_two5v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two5)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_two6 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_two6I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two6)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_two6v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two6)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_two7 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_two7I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two7)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_two7v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two7)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_two8 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_two8I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two8)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_two8v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_two8)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_three1 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_three1I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three1)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_three1v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three1)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_three2 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_three2I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three2)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_three2v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three2)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_three3 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_three3I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three3)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_three3v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three3)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_three4 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_three4I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three4)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_three4v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three4)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_three5 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_three5I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three5)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_three5v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three5)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_three6 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_three6I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three6)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_three6v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three6)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_three7 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_three7I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three7)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_three7v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three7)] /* [0,65535] */;
  uint32_t fatimavme_qdc5sample_three8 /* [0,120] */;
  uint32_t fatimavme_qdc5sample_three8I[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three8)] /* [1,120] */;
  uint32_t fatimavme_qdc5sample_three8v[120 EXT_STRUCT_CTRL(fatimavme_qdc5sample_three8)] /* [0,65535] */;
  uint32_t fatimavme_qdc6board_id /* [0,255] */;
  uint32_t fatimavme_qdc6channels /* [0,255] */;
  uint32_t fatimavme_qdc6board_time /* [-1,-1] */;
  uint32_t fatimavme_qdc6channel_time /* [0,64] */;
  uint32_t fatimavme_qdc6channel_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc6channel_time)] /* [-1,-1] */;
  uint32_t fatimavme_qdc6chan_ext_time /* [0,64] */;
  uint32_t fatimavme_qdc6chan_ext_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc6chan_ext_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc6chan_fine_time /* [0,64] */;
  uint32_t fatimavme_qdc6chan_fine_timev[64 EXT_STRUCT_CTRL(fatimavme_qdc6chan_fine_time)] /* [0,65535] */;
  uint32_t fatimavme_qdc6qshort /* [0,64] */;
  uint32_t fatimavme_qdc6qshortv[64 EXT_STRUCT_CTRL(fatimavme_qdc6qshort)] /* [0,65535] */;
  uint32_t fatimavme_qdc6qlong /* [0,64] */;
  uint32_t fatimavme_qdc6qlongv[64 EXT_STRUCT_CTRL(fatimavme_qdc6qlong)] /* [0,65535] */;
  uint32_t fatimavme_qdc6extras /* [0,65535] */;
  uint32_t fatimavme_qdc6dm /* [0,65535] */;
  uint32_t fatimavme_qdc6chan_baseline /* [0,64] */;
  uint32_t fatimavme_qdc6chan_baselinev[64 EXT_STRUCT_CTRL(fatimavme_qdc6chan_baseline)] /* [0,65535] */;
  uint32_t fatimavme_qdc6chan_midscale /* [0,64] */;
  uint32_t fatimavme_qdc6chan_midscalev[64 EXT_STRUCT_CTRL(fatimavme_qdc6chan_midscale)] /* [0,65535] */;
  uint32_t fatimavme_qdc6chan_sazc /* [0,64] */;
  uint32_t fatimavme_qdc6chan_sazcv[64 EXT_STRUCT_CTRL(fatimavme_qdc6chan_sazc)] /* [0,65535] */;
  uint32_t fatimavme_qdc6chan_sbzc /* [0,64] */;
  uint32_t fatimavme_qdc6chan_sbzcv[64 EXT_STRUCT_CTRL(fatimavme_qdc6chan_sbzc)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_one1 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_one1I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one1)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_one1v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one1)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_one2 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_one2I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one2)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_one2v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one2)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_one3 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_one3I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one3)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_one3v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one3)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_one4 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_one4I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one4)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_one4v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one4)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_one5 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_one5I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one5)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_one5v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one5)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_one6 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_one6I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one6)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_one6v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one6)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_one7 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_one7I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one7)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_one7v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one7)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_one8 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_one8I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one8)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_one8v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_one8)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_two1 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_two1I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two1)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_two1v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two1)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_two2 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_two2I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two2)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_two2v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two2)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_two3 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_two3I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two3)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_two3v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two3)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_two4 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_two4I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two4)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_two4v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two4)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_two5 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_two5I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two5)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_two5v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two5)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_two6 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_two6I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two6)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_two6v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two6)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_two7 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_two7I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two7)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_two7v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two7)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_two8 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_two8I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two8)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_two8v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_two8)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_three1 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_three1I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three1)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_three1v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three1)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_three2 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_three2I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three2)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_three2v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three2)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_three3 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_three3I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three3)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_three3v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three3)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_three4 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_three4I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three4)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_three4v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three4)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_three5 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_three5I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three5)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_three5v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three5)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_three6 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_three6I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three6)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_three6v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three6)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_three7 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_three7I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three7)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_three7v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three7)] /* [0,65535] */;
  uint32_t fatimavme_qdc6sample_three8 /* [0,120] */;
  uint32_t fatimavme_qdc6sample_three8I[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three8)] /* [1,120] */;
  uint32_t fatimavme_qdc6sample_three8v[120 EXT_STRUCT_CTRL(fatimavme_qdc6sample_three8)] /* [0,65535] */;
  uint32_t fatimavme_tdc1_geo /* [0,255] */;
  uint32_t fatimavme_tdc1_measurement_nM /* [1,128] */;
  uint32_t fatimavme_tdc1_measurement_nMI[128 EXT_STRUCT_CTRL(fatimavme_tdc1_measurement_nM)] /* [1,128] */;
  uint32_t fatimavme_tdc1_measurement_nME[128 EXT_STRUCT_CTRL(fatimavme_tdc1_measurement_nM)] /* [1,16384] */;
  uint32_t fatimavme_tdc1_measurement_n /* [0,16384] */;
  uint32_t fatimavme_tdc1_measurement_data[16384 EXT_STRUCT_CTRL(fatimavme_tdc1_measurement_n)] /* [0,16777215] */;
  uint32_t fatimavme_tdc1_measurement_leadOrTrailM /* [1,128] */;
  uint32_t fatimavme_tdc1_measurement_leadOrTrailMI[128 EXT_STRUCT_CTRL(fatimavme_tdc1_measurement_leadOrTrailM)] /* [1,128] */;
  uint32_t fatimavme_tdc1_measurement_leadOrTrailME[128 EXT_STRUCT_CTRL(fatimavme_tdc1_measurement_leadOrTrailM)] /* [1,16384] */;
  uint32_t fatimavme_tdc1_measurement_leadOrTrail /* [0,16384] */;
  uint32_t fatimavme_tdc1_measurement_leadOrTrailv[16384 EXT_STRUCT_CTRL(fatimavme_tdc1_measurement_leadOrTrail)] /* [0,255] */;
  uint32_t fatimavme_tdc2_geo /* [0,255] */;
  uint32_t fatimavme_tdc2_measurement_nM /* [1,128] */;
  uint32_t fatimavme_tdc2_measurement_nMI[128 EXT_STRUCT_CTRL(fatimavme_tdc2_measurement_nM)] /* [1,128] */;
  uint32_t fatimavme_tdc2_measurement_nME[128 EXT_STRUCT_CTRL(fatimavme_tdc2_measurement_nM)] /* [1,16384] */;
  uint32_t fatimavme_tdc2_measurement_n /* [0,16384] */;
  uint32_t fatimavme_tdc2_measurement_data[16384 EXT_STRUCT_CTRL(fatimavme_tdc2_measurement_n)] /* [0,16777215] */;
  uint32_t fatimavme_tdc2_measurement_leadOrTrailM /* [1,128] */;
  uint32_t fatimavme_tdc2_measurement_leadOrTrailMI[128 EXT_STRUCT_CTRL(fatimavme_tdc2_measurement_leadOrTrailM)] /* [1,128] */;
  uint32_t fatimavme_tdc2_measurement_leadOrTrailME[128 EXT_STRUCT_CTRL(fatimavme_tdc2_measurement_leadOrTrailM)] /* [1,16384] */;
  uint32_t fatimavme_tdc2_measurement_leadOrTrail /* [0,16384] */;
  uint32_t fatimavme_tdc2_measurement_leadOrTrailv[16384 EXT_STRUCT_CTRL(fatimavme_tdc2_measurement_leadOrTrail)] /* [0,255] */;
  uint32_t fatimavme_tdc3_geo /* [0,255] */;
  uint32_t fatimavme_tdc3_measurement_nM /* [1,128] */;
  uint32_t fatimavme_tdc3_measurement_nMI[128 EXT_STRUCT_CTRL(fatimavme_tdc3_measurement_nM)] /* [1,128] */;
  uint32_t fatimavme_tdc3_measurement_nME[128 EXT_STRUCT_CTRL(fatimavme_tdc3_measurement_nM)] /* [1,16384] */;
  uint32_t fatimavme_tdc3_measurement_n /* [0,16384] */;
  uint32_t fatimavme_tdc3_measurement_data[16384 EXT_STRUCT_CTRL(fatimavme_tdc3_measurement_n)] /* [0,16777215] */;
  uint32_t fatimavme_tdc3_measurement_leadOrTrailM /* [1,128] */;
  uint32_t fatimavme_tdc3_measurement_leadOrTrailMI[128 EXT_STRUCT_CTRL(fatimavme_tdc3_measurement_leadOrTrailM)] /* [1,128] */;
  uint32_t fatimavme_tdc3_measurement_leadOrTrailME[128 EXT_STRUCT_CTRL(fatimavme_tdc3_measurement_leadOrTrailM)] /* [1,16384] */;
  uint32_t fatimavme_tdc3_measurement_leadOrTrail /* [0,16384] */;
  uint32_t fatimavme_tdc3_measurement_leadOrTrailv[16384 EXT_STRUCT_CTRL(fatimavme_tdc3_measurement_leadOrTrail)] /* [0,255] */;
  uint32_t fatimavme_tdc4_geo /* [0,255] */;
  uint32_t fatimavme_tdc4_measurement_nM /* [1,128] */;
  uint32_t fatimavme_tdc4_measurement_nMI[128 EXT_STRUCT_CTRL(fatimavme_tdc4_measurement_nM)] /* [1,128] */;
  uint32_t fatimavme_tdc4_measurement_nME[128 EXT_STRUCT_CTRL(fatimavme_tdc4_measurement_nM)] /* [1,16384] */;
  uint32_t fatimavme_tdc4_measurement_n /* [0,16384] */;
  uint32_t fatimavme_tdc4_measurement_data[16384 EXT_STRUCT_CTRL(fatimavme_tdc4_measurement_n)] /* [0,16777215] */;
  uint32_t fatimavme_tdc4_measurement_leadOrTrailM /* [1,128] */;
  uint32_t fatimavme_tdc4_measurement_leadOrTrailMI[128 EXT_STRUCT_CTRL(fatimavme_tdc4_measurement_leadOrTrailM)] /* [1,128] */;
  uint32_t fatimavme_tdc4_measurement_leadOrTrailME[128 EXT_STRUCT_CTRL(fatimavme_tdc4_measurement_leadOrTrailM)] /* [1,16384] */;
  uint32_t fatimavme_tdc4_measurement_leadOrTrail /* [0,16384] */;
  uint32_t fatimavme_tdc4_measurement_leadOrTrailv[16384 EXT_STRUCT_CTRL(fatimavme_tdc4_measurement_leadOrTrail)] /* [0,255] */;
  uint32_t fatimavme_tdc5_geo /* [0,255] */;
  uint32_t fatimavme_tdc5_measurement_nM /* [1,128] */;
  uint32_t fatimavme_tdc5_measurement_nMI[128 EXT_STRUCT_CTRL(fatimavme_tdc5_measurement_nM)] /* [1,128] */;
  uint32_t fatimavme_tdc5_measurement_nME[128 EXT_STRUCT_CTRL(fatimavme_tdc5_measurement_nM)] /* [1,16384] */;
  uint32_t fatimavme_tdc5_measurement_n /* [0,16384] */;
  uint32_t fatimavme_tdc5_measurement_data[16384 EXT_STRUCT_CTRL(fatimavme_tdc5_measurement_n)] /* [0,16777215] */;
  uint32_t fatimavme_tdc5_measurement_leadOrTrailM /* [1,128] */;
  uint32_t fatimavme_tdc5_measurement_leadOrTrailMI[128 EXT_STRUCT_CTRL(fatimavme_tdc5_measurement_leadOrTrailM)] /* [1,128] */;
  uint32_t fatimavme_tdc5_measurement_leadOrTrailME[128 EXT_STRUCT_CTRL(fatimavme_tdc5_measurement_leadOrTrailM)] /* [1,16384] */;
  uint32_t fatimavme_tdc5_measurement_leadOrTrail /* [0,16384] */;
  uint32_t fatimavme_tdc5_measurement_leadOrTrailv[16384 EXT_STRUCT_CTRL(fatimavme_tdc5_measurement_leadOrTrail)] /* [0,255] */;
  uint32_t fatimavme_tdc6_geo /* [0,255] */;
  uint32_t fatimavme_tdc6_measurement_nM /* [1,128] */;
  uint32_t fatimavme_tdc6_measurement_nMI[128 EXT_STRUCT_CTRL(fatimavme_tdc6_measurement_nM)] /* [1,128] */;
  uint32_t fatimavme_tdc6_measurement_nME[128 EXT_STRUCT_CTRL(fatimavme_tdc6_measurement_nM)] /* [1,16384] */;
  uint32_t fatimavme_tdc6_measurement_n /* [0,16384] */;
  uint32_t fatimavme_tdc6_measurement_data[16384 EXT_STRUCT_CTRL(fatimavme_tdc6_measurement_n)] /* [0,16777215] */;
  uint32_t fatimavme_tdc6_measurement_leadOrTrailM /* [1,128] */;
  uint32_t fatimavme_tdc6_measurement_leadOrTrailMI[128 EXT_STRUCT_CTRL(fatimavme_tdc6_measurement_leadOrTrailM)] /* [1,128] */;
  uint32_t fatimavme_tdc6_measurement_leadOrTrailME[128 EXT_STRUCT_CTRL(fatimavme_tdc6_measurement_leadOrTrailM)] /* [1,16384] */;
  uint32_t fatimavme_tdc6_measurement_leadOrTrail /* [0,16384] */;
  uint32_t fatimavme_tdc6_measurement_leadOrTrailv[16384 EXT_STRUCT_CTRL(fatimavme_tdc6_measurement_leadOrTrail)] /* [0,255] */;

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
    uint32_t extras;
    uint32_t dm;
    uint32_t chan_baseline;
    uint32_t chan_baselinev[64 /* chan_baseline */];
    uint32_t chan_midscale;
    uint32_t chan_midscalev[64 /* chan_midscale */];
    uint32_t chan_sazc;
    uint32_t chan_sazcv[64 /* chan_sazc */];
    uint32_t chan_sbzc;
    uint32_t chan_sbzcv[64 /* chan_sbzc */];
    struct {
      uint32_t _;
      uint32_t I[120 /*  */];
      uint32_t v[120 /*  */];
    } sample_one[8];
    struct {
      uint32_t _;
      uint32_t I[120 /*  */];
      uint32_t v[120 /*  */];
    } sample_two[8];
    struct {
      uint32_t _;
      uint32_t I[120 /*  */];
      uint32_t v[120 /*  */];
    } sample_three[8];
  } fatimavme_qdc[6];
  struct {
    uint32_t _geo;
    uint32_t _measurement_nM;
    uint32_t _measurement_nMI[128 /* _measurement_nM */];
    uint32_t _measurement_nME[128 /* _measurement_nM */];
    uint32_t _measurement_n;
    uint32_t _measurement_data[16384 /* _measurement_n */];
    uint32_t _measurement_leadOrTrailM;
    uint32_t _measurement_leadOrTrailMI[128 /* _measurement_leadOrTrailM */];
    uint32_t _measurement_leadOrTrailME[128 /* _measurement_leadOrTrailM */];
    uint32_t _measurement_leadOrTrail;
    uint32_t _measurement_leadOrTrailv[16384 /* _measurement_leadOrTrail */];
  } fatimavme_tdc[6];

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
                     fatimavme_qdc1extras,            UINT32,\
                    "fatimavme_qdc1extras",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1dm,                UINT32,\
                    "fatimavme_qdc1dm",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1chan_baseline,     UINT32,\
                    "fatimavme_qdc1chan_baseline",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1chan_baselinev,    UINT32,\
                    "fatimavme_qdc1chan_baselinev",    "fatimavme_qdc1chan_baseline",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1chan_midscale,     UINT32,\
                    "fatimavme_qdc1chan_midscale",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1chan_midscalev,    UINT32,\
                    "fatimavme_qdc1chan_midscalev",    "fatimavme_qdc1chan_midscale",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1chan_sazc,         UINT32,\
                    "fatimavme_qdc1chan_sazc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1chan_sazcv,        UINT32,\
                    "fatimavme_qdc1chan_sazcv",        "fatimavme_qdc1chan_sazc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1chan_sbzc,         UINT32,\
                    "fatimavme_qdc1chan_sbzc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1chan_sbzcv,        UINT32,\
                    "fatimavme_qdc1chan_sbzcv",        "fatimavme_qdc1chan_sbzc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one1,       UINT32,\
                    "fatimavme_qdc1sample_one1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one1I,      UINT32,\
                    "fatimavme_qdc1sample_one1I",      "fatimavme_qdc1sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one1v,      UINT32,\
                    "fatimavme_qdc1sample_one1v",      "fatimavme_qdc1sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one2,       UINT32,\
                    "fatimavme_qdc1sample_one2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one2I,      UINT32,\
                    "fatimavme_qdc1sample_one2I",      "fatimavme_qdc1sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one2v,      UINT32,\
                    "fatimavme_qdc1sample_one2v",      "fatimavme_qdc1sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one3,       UINT32,\
                    "fatimavme_qdc1sample_one3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one3I,      UINT32,\
                    "fatimavme_qdc1sample_one3I",      "fatimavme_qdc1sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one3v,      UINT32,\
                    "fatimavme_qdc1sample_one3v",      "fatimavme_qdc1sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one4,       UINT32,\
                    "fatimavme_qdc1sample_one4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one4I,      UINT32,\
                    "fatimavme_qdc1sample_one4I",      "fatimavme_qdc1sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one4v,      UINT32,\
                    "fatimavme_qdc1sample_one4v",      "fatimavme_qdc1sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one5,       UINT32,\
                    "fatimavme_qdc1sample_one5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one5I,      UINT32,\
                    "fatimavme_qdc1sample_one5I",      "fatimavme_qdc1sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one5v,      UINT32,\
                    "fatimavme_qdc1sample_one5v",      "fatimavme_qdc1sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one6,       UINT32,\
                    "fatimavme_qdc1sample_one6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one6I,      UINT32,\
                    "fatimavme_qdc1sample_one6I",      "fatimavme_qdc1sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one6v,      UINT32,\
                    "fatimavme_qdc1sample_one6v",      "fatimavme_qdc1sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one7,       UINT32,\
                    "fatimavme_qdc1sample_one7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one7I,      UINT32,\
                    "fatimavme_qdc1sample_one7I",      "fatimavme_qdc1sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one7v,      UINT32,\
                    "fatimavme_qdc1sample_one7v",      "fatimavme_qdc1sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one8,       UINT32,\
                    "fatimavme_qdc1sample_one8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one8I,      UINT32,\
                    "fatimavme_qdc1sample_one8I",      "fatimavme_qdc1sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_one8v,      UINT32,\
                    "fatimavme_qdc1sample_one8v",      "fatimavme_qdc1sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two1,       UINT32,\
                    "fatimavme_qdc1sample_two1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two1I,      UINT32,\
                    "fatimavme_qdc1sample_two1I",      "fatimavme_qdc1sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two1v,      UINT32,\
                    "fatimavme_qdc1sample_two1v",      "fatimavme_qdc1sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two2,       UINT32,\
                    "fatimavme_qdc1sample_two2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two2I,      UINT32,\
                    "fatimavme_qdc1sample_two2I",      "fatimavme_qdc1sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two2v,      UINT32,\
                    "fatimavme_qdc1sample_two2v",      "fatimavme_qdc1sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two3,       UINT32,\
                    "fatimavme_qdc1sample_two3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two3I,      UINT32,\
                    "fatimavme_qdc1sample_two3I",      "fatimavme_qdc1sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two3v,      UINT32,\
                    "fatimavme_qdc1sample_two3v",      "fatimavme_qdc1sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two4,       UINT32,\
                    "fatimavme_qdc1sample_two4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two4I,      UINT32,\
                    "fatimavme_qdc1sample_two4I",      "fatimavme_qdc1sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two4v,      UINT32,\
                    "fatimavme_qdc1sample_two4v",      "fatimavme_qdc1sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two5,       UINT32,\
                    "fatimavme_qdc1sample_two5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two5I,      UINT32,\
                    "fatimavme_qdc1sample_two5I",      "fatimavme_qdc1sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two5v,      UINT32,\
                    "fatimavme_qdc1sample_two5v",      "fatimavme_qdc1sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two6,       UINT32,\
                    "fatimavme_qdc1sample_two6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two6I,      UINT32,\
                    "fatimavme_qdc1sample_two6I",      "fatimavme_qdc1sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two6v,      UINT32,\
                    "fatimavme_qdc1sample_two6v",      "fatimavme_qdc1sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two7,       UINT32,\
                    "fatimavme_qdc1sample_two7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two7I,      UINT32,\
                    "fatimavme_qdc1sample_two7I",      "fatimavme_qdc1sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two7v,      UINT32,\
                    "fatimavme_qdc1sample_two7v",      "fatimavme_qdc1sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two8,       UINT32,\
                    "fatimavme_qdc1sample_two8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two8I,      UINT32,\
                    "fatimavme_qdc1sample_two8I",      "fatimavme_qdc1sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_two8v,      UINT32,\
                    "fatimavme_qdc1sample_two8v",      "fatimavme_qdc1sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three1,     UINT32,\
                    "fatimavme_qdc1sample_three1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three1I,    UINT32,\
                    "fatimavme_qdc1sample_three1I",    "fatimavme_qdc1sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three1v,    UINT32,\
                    "fatimavme_qdc1sample_three1v",    "fatimavme_qdc1sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three2,     UINT32,\
                    "fatimavme_qdc1sample_three2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three2I,    UINT32,\
                    "fatimavme_qdc1sample_three2I",    "fatimavme_qdc1sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three2v,    UINT32,\
                    "fatimavme_qdc1sample_three2v",    "fatimavme_qdc1sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three3,     UINT32,\
                    "fatimavme_qdc1sample_three3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three3I,    UINT32,\
                    "fatimavme_qdc1sample_three3I",    "fatimavme_qdc1sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three3v,    UINT32,\
                    "fatimavme_qdc1sample_three3v",    "fatimavme_qdc1sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three4,     UINT32,\
                    "fatimavme_qdc1sample_three4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three4I,    UINT32,\
                    "fatimavme_qdc1sample_three4I",    "fatimavme_qdc1sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three4v,    UINT32,\
                    "fatimavme_qdc1sample_three4v",    "fatimavme_qdc1sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three5,     UINT32,\
                    "fatimavme_qdc1sample_three5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three5I,    UINT32,\
                    "fatimavme_qdc1sample_three5I",    "fatimavme_qdc1sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three5v,    UINT32,\
                    "fatimavme_qdc1sample_three5v",    "fatimavme_qdc1sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three6,     UINT32,\
                    "fatimavme_qdc1sample_three6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three6I,    UINT32,\
                    "fatimavme_qdc1sample_three6I",    "fatimavme_qdc1sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three6v,    UINT32,\
                    "fatimavme_qdc1sample_three6v",    "fatimavme_qdc1sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three7,     UINT32,\
                    "fatimavme_qdc1sample_three7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three7I,    UINT32,\
                    "fatimavme_qdc1sample_three7I",    "fatimavme_qdc1sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three7v,    UINT32,\
                    "fatimavme_qdc1sample_three7v",    "fatimavme_qdc1sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three8,     UINT32,\
                    "fatimavme_qdc1sample_three8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three8I,    UINT32,\
                    "fatimavme_qdc1sample_three8I",    "fatimavme_qdc1sample_three8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1sample_three8v,    UINT32,\
                    "fatimavme_qdc1sample_three8v",    "fatimavme_qdc1sample_three8",0/*flags*/); \
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
                     fatimavme_qdc2extras,            UINT32,\
                    "fatimavme_qdc2extras",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2dm,                UINT32,\
                    "fatimavme_qdc2dm",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2chan_baseline,     UINT32,\
                    "fatimavme_qdc2chan_baseline",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2chan_baselinev,    UINT32,\
                    "fatimavme_qdc2chan_baselinev",    "fatimavme_qdc2chan_baseline",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2chan_midscale,     UINT32,\
                    "fatimavme_qdc2chan_midscale",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2chan_midscalev,    UINT32,\
                    "fatimavme_qdc2chan_midscalev",    "fatimavme_qdc2chan_midscale",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2chan_sazc,         UINT32,\
                    "fatimavme_qdc2chan_sazc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2chan_sazcv,        UINT32,\
                    "fatimavme_qdc2chan_sazcv",        "fatimavme_qdc2chan_sazc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2chan_sbzc,         UINT32,\
                    "fatimavme_qdc2chan_sbzc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2chan_sbzcv,        UINT32,\
                    "fatimavme_qdc2chan_sbzcv",        "fatimavme_qdc2chan_sbzc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one1,       UINT32,\
                    "fatimavme_qdc2sample_one1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one1I,      UINT32,\
                    "fatimavme_qdc2sample_one1I",      "fatimavme_qdc2sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one1v,      UINT32,\
                    "fatimavme_qdc2sample_one1v",      "fatimavme_qdc2sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one2,       UINT32,\
                    "fatimavme_qdc2sample_one2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one2I,      UINT32,\
                    "fatimavme_qdc2sample_one2I",      "fatimavme_qdc2sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one2v,      UINT32,\
                    "fatimavme_qdc2sample_one2v",      "fatimavme_qdc2sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one3,       UINT32,\
                    "fatimavme_qdc2sample_one3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one3I,      UINT32,\
                    "fatimavme_qdc2sample_one3I",      "fatimavme_qdc2sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one3v,      UINT32,\
                    "fatimavme_qdc2sample_one3v",      "fatimavme_qdc2sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one4,       UINT32,\
                    "fatimavme_qdc2sample_one4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one4I,      UINT32,\
                    "fatimavme_qdc2sample_one4I",      "fatimavme_qdc2sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one4v,      UINT32,\
                    "fatimavme_qdc2sample_one4v",      "fatimavme_qdc2sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one5,       UINT32,\
                    "fatimavme_qdc2sample_one5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one5I,      UINT32,\
                    "fatimavme_qdc2sample_one5I",      "fatimavme_qdc2sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one5v,      UINT32,\
                    "fatimavme_qdc2sample_one5v",      "fatimavme_qdc2sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one6,       UINT32,\
                    "fatimavme_qdc2sample_one6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one6I,      UINT32,\
                    "fatimavme_qdc2sample_one6I",      "fatimavme_qdc2sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one6v,      UINT32,\
                    "fatimavme_qdc2sample_one6v",      "fatimavme_qdc2sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one7,       UINT32,\
                    "fatimavme_qdc2sample_one7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one7I,      UINT32,\
                    "fatimavme_qdc2sample_one7I",      "fatimavme_qdc2sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one7v,      UINT32,\
                    "fatimavme_qdc2sample_one7v",      "fatimavme_qdc2sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one8,       UINT32,\
                    "fatimavme_qdc2sample_one8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one8I,      UINT32,\
                    "fatimavme_qdc2sample_one8I",      "fatimavme_qdc2sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_one8v,      UINT32,\
                    "fatimavme_qdc2sample_one8v",      "fatimavme_qdc2sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two1,       UINT32,\
                    "fatimavme_qdc2sample_two1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two1I,      UINT32,\
                    "fatimavme_qdc2sample_two1I",      "fatimavme_qdc2sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two1v,      UINT32,\
                    "fatimavme_qdc2sample_two1v",      "fatimavme_qdc2sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two2,       UINT32,\
                    "fatimavme_qdc2sample_two2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two2I,      UINT32,\
                    "fatimavme_qdc2sample_two2I",      "fatimavme_qdc2sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two2v,      UINT32,\
                    "fatimavme_qdc2sample_two2v",      "fatimavme_qdc2sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two3,       UINT32,\
                    "fatimavme_qdc2sample_two3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two3I,      UINT32,\
                    "fatimavme_qdc2sample_two3I",      "fatimavme_qdc2sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two3v,      UINT32,\
                    "fatimavme_qdc2sample_two3v",      "fatimavme_qdc2sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two4,       UINT32,\
                    "fatimavme_qdc2sample_two4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two4I,      UINT32,\
                    "fatimavme_qdc2sample_two4I",      "fatimavme_qdc2sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two4v,      UINT32,\
                    "fatimavme_qdc2sample_two4v",      "fatimavme_qdc2sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two5,       UINT32,\
                    "fatimavme_qdc2sample_two5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two5I,      UINT32,\
                    "fatimavme_qdc2sample_two5I",      "fatimavme_qdc2sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two5v,      UINT32,\
                    "fatimavme_qdc2sample_two5v",      "fatimavme_qdc2sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two6,       UINT32,\
                    "fatimavme_qdc2sample_two6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two6I,      UINT32,\
                    "fatimavme_qdc2sample_two6I",      "fatimavme_qdc2sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two6v,      UINT32,\
                    "fatimavme_qdc2sample_two6v",      "fatimavme_qdc2sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two7,       UINT32,\
                    "fatimavme_qdc2sample_two7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two7I,      UINT32,\
                    "fatimavme_qdc2sample_two7I",      "fatimavme_qdc2sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two7v,      UINT32,\
                    "fatimavme_qdc2sample_two7v",      "fatimavme_qdc2sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two8,       UINT32,\
                    "fatimavme_qdc2sample_two8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two8I,      UINT32,\
                    "fatimavme_qdc2sample_two8I",      "fatimavme_qdc2sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_two8v,      UINT32,\
                    "fatimavme_qdc2sample_two8v",      "fatimavme_qdc2sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three1,     UINT32,\
                    "fatimavme_qdc2sample_three1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three1I,    UINT32,\
                    "fatimavme_qdc2sample_three1I",    "fatimavme_qdc2sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three1v,    UINT32,\
                    "fatimavme_qdc2sample_three1v",    "fatimavme_qdc2sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three2,     UINT32,\
                    "fatimavme_qdc2sample_three2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three2I,    UINT32,\
                    "fatimavme_qdc2sample_three2I",    "fatimavme_qdc2sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three2v,    UINT32,\
                    "fatimavme_qdc2sample_three2v",    "fatimavme_qdc2sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three3,     UINT32,\
                    "fatimavme_qdc2sample_three3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three3I,    UINT32,\
                    "fatimavme_qdc2sample_three3I",    "fatimavme_qdc2sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three3v,    UINT32,\
                    "fatimavme_qdc2sample_three3v",    "fatimavme_qdc2sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three4,     UINT32,\
                    "fatimavme_qdc2sample_three4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three4I,    UINT32,\
                    "fatimavme_qdc2sample_three4I",    "fatimavme_qdc2sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three4v,    UINT32,\
                    "fatimavme_qdc2sample_three4v",    "fatimavme_qdc2sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three5,     UINT32,\
                    "fatimavme_qdc2sample_three5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three5I,    UINT32,\
                    "fatimavme_qdc2sample_three5I",    "fatimavme_qdc2sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three5v,    UINT32,\
                    "fatimavme_qdc2sample_three5v",    "fatimavme_qdc2sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three6,     UINT32,\
                    "fatimavme_qdc2sample_three6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three6I,    UINT32,\
                    "fatimavme_qdc2sample_three6I",    "fatimavme_qdc2sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three6v,    UINT32,\
                    "fatimavme_qdc2sample_three6v",    "fatimavme_qdc2sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three7,     UINT32,\
                    "fatimavme_qdc2sample_three7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three7I,    UINT32,\
                    "fatimavme_qdc2sample_three7I",    "fatimavme_qdc2sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three7v,    UINT32,\
                    "fatimavme_qdc2sample_three7v",    "fatimavme_qdc2sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three8,     UINT32,\
                    "fatimavme_qdc2sample_three8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three8I,    UINT32,\
                    "fatimavme_qdc2sample_three8I",    "fatimavme_qdc2sample_three8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2sample_three8v,    UINT32,\
                    "fatimavme_qdc2sample_three8v",    "fatimavme_qdc2sample_three8",0/*flags*/); \
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
                     fatimavme_qdc3extras,            UINT32,\
                    "fatimavme_qdc3extras",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3dm,                UINT32,\
                    "fatimavme_qdc3dm",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3chan_baseline,     UINT32,\
                    "fatimavme_qdc3chan_baseline",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3chan_baselinev,    UINT32,\
                    "fatimavme_qdc3chan_baselinev",    "fatimavme_qdc3chan_baseline",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3chan_midscale,     UINT32,\
                    "fatimavme_qdc3chan_midscale",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3chan_midscalev,    UINT32,\
                    "fatimavme_qdc3chan_midscalev",    "fatimavme_qdc3chan_midscale",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3chan_sazc,         UINT32,\
                    "fatimavme_qdc3chan_sazc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3chan_sazcv,        UINT32,\
                    "fatimavme_qdc3chan_sazcv",        "fatimavme_qdc3chan_sazc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3chan_sbzc,         UINT32,\
                    "fatimavme_qdc3chan_sbzc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3chan_sbzcv,        UINT32,\
                    "fatimavme_qdc3chan_sbzcv",        "fatimavme_qdc3chan_sbzc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one1,       UINT32,\
                    "fatimavme_qdc3sample_one1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one1I,      UINT32,\
                    "fatimavme_qdc3sample_one1I",      "fatimavme_qdc3sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one1v,      UINT32,\
                    "fatimavme_qdc3sample_one1v",      "fatimavme_qdc3sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one2,       UINT32,\
                    "fatimavme_qdc3sample_one2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one2I,      UINT32,\
                    "fatimavme_qdc3sample_one2I",      "fatimavme_qdc3sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one2v,      UINT32,\
                    "fatimavme_qdc3sample_one2v",      "fatimavme_qdc3sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one3,       UINT32,\
                    "fatimavme_qdc3sample_one3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one3I,      UINT32,\
                    "fatimavme_qdc3sample_one3I",      "fatimavme_qdc3sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one3v,      UINT32,\
                    "fatimavme_qdc3sample_one3v",      "fatimavme_qdc3sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one4,       UINT32,\
                    "fatimavme_qdc3sample_one4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one4I,      UINT32,\
                    "fatimavme_qdc3sample_one4I",      "fatimavme_qdc3sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one4v,      UINT32,\
                    "fatimavme_qdc3sample_one4v",      "fatimavme_qdc3sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one5,       UINT32,\
                    "fatimavme_qdc3sample_one5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one5I,      UINT32,\
                    "fatimavme_qdc3sample_one5I",      "fatimavme_qdc3sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one5v,      UINT32,\
                    "fatimavme_qdc3sample_one5v",      "fatimavme_qdc3sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one6,       UINT32,\
                    "fatimavme_qdc3sample_one6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one6I,      UINT32,\
                    "fatimavme_qdc3sample_one6I",      "fatimavme_qdc3sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one6v,      UINT32,\
                    "fatimavme_qdc3sample_one6v",      "fatimavme_qdc3sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one7,       UINT32,\
                    "fatimavme_qdc3sample_one7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one7I,      UINT32,\
                    "fatimavme_qdc3sample_one7I",      "fatimavme_qdc3sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one7v,      UINT32,\
                    "fatimavme_qdc3sample_one7v",      "fatimavme_qdc3sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one8,       UINT32,\
                    "fatimavme_qdc3sample_one8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one8I,      UINT32,\
                    "fatimavme_qdc3sample_one8I",      "fatimavme_qdc3sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_one8v,      UINT32,\
                    "fatimavme_qdc3sample_one8v",      "fatimavme_qdc3sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two1,       UINT32,\
                    "fatimavme_qdc3sample_two1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two1I,      UINT32,\
                    "fatimavme_qdc3sample_two1I",      "fatimavme_qdc3sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two1v,      UINT32,\
                    "fatimavme_qdc3sample_two1v",      "fatimavme_qdc3sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two2,       UINT32,\
                    "fatimavme_qdc3sample_two2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two2I,      UINT32,\
                    "fatimavme_qdc3sample_two2I",      "fatimavme_qdc3sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two2v,      UINT32,\
                    "fatimavme_qdc3sample_two2v",      "fatimavme_qdc3sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two3,       UINT32,\
                    "fatimavme_qdc3sample_two3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two3I,      UINT32,\
                    "fatimavme_qdc3sample_two3I",      "fatimavme_qdc3sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two3v,      UINT32,\
                    "fatimavme_qdc3sample_two3v",      "fatimavme_qdc3sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two4,       UINT32,\
                    "fatimavme_qdc3sample_two4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two4I,      UINT32,\
                    "fatimavme_qdc3sample_two4I",      "fatimavme_qdc3sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two4v,      UINT32,\
                    "fatimavme_qdc3sample_two4v",      "fatimavme_qdc3sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two5,       UINT32,\
                    "fatimavme_qdc3sample_two5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two5I,      UINT32,\
                    "fatimavme_qdc3sample_two5I",      "fatimavme_qdc3sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two5v,      UINT32,\
                    "fatimavme_qdc3sample_two5v",      "fatimavme_qdc3sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two6,       UINT32,\
                    "fatimavme_qdc3sample_two6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two6I,      UINT32,\
                    "fatimavme_qdc3sample_two6I",      "fatimavme_qdc3sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two6v,      UINT32,\
                    "fatimavme_qdc3sample_two6v",      "fatimavme_qdc3sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two7,       UINT32,\
                    "fatimavme_qdc3sample_two7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two7I,      UINT32,\
                    "fatimavme_qdc3sample_two7I",      "fatimavme_qdc3sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two7v,      UINT32,\
                    "fatimavme_qdc3sample_two7v",      "fatimavme_qdc3sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two8,       UINT32,\
                    "fatimavme_qdc3sample_two8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two8I,      UINT32,\
                    "fatimavme_qdc3sample_two8I",      "fatimavme_qdc3sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_two8v,      UINT32,\
                    "fatimavme_qdc3sample_two8v",      "fatimavme_qdc3sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three1,     UINT32,\
                    "fatimavme_qdc3sample_three1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three1I,    UINT32,\
                    "fatimavme_qdc3sample_three1I",    "fatimavme_qdc3sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three1v,    UINT32,\
                    "fatimavme_qdc3sample_three1v",    "fatimavme_qdc3sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three2,     UINT32,\
                    "fatimavme_qdc3sample_three2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three2I,    UINT32,\
                    "fatimavme_qdc3sample_three2I",    "fatimavme_qdc3sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three2v,    UINT32,\
                    "fatimavme_qdc3sample_three2v",    "fatimavme_qdc3sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three3,     UINT32,\
                    "fatimavme_qdc3sample_three3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three3I,    UINT32,\
                    "fatimavme_qdc3sample_three3I",    "fatimavme_qdc3sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three3v,    UINT32,\
                    "fatimavme_qdc3sample_three3v",    "fatimavme_qdc3sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three4,     UINT32,\
                    "fatimavme_qdc3sample_three4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three4I,    UINT32,\
                    "fatimavme_qdc3sample_three4I",    "fatimavme_qdc3sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three4v,    UINT32,\
                    "fatimavme_qdc3sample_three4v",    "fatimavme_qdc3sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three5,     UINT32,\
                    "fatimavme_qdc3sample_three5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three5I,    UINT32,\
                    "fatimavme_qdc3sample_three5I",    "fatimavme_qdc3sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three5v,    UINT32,\
                    "fatimavme_qdc3sample_three5v",    "fatimavme_qdc3sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three6,     UINT32,\
                    "fatimavme_qdc3sample_three6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three6I,    UINT32,\
                    "fatimavme_qdc3sample_three6I",    "fatimavme_qdc3sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three6v,    UINT32,\
                    "fatimavme_qdc3sample_three6v",    "fatimavme_qdc3sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three7,     UINT32,\
                    "fatimavme_qdc3sample_three7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three7I,    UINT32,\
                    "fatimavme_qdc3sample_three7I",    "fatimavme_qdc3sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three7v,    UINT32,\
                    "fatimavme_qdc3sample_three7v",    "fatimavme_qdc3sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three8,     UINT32,\
                    "fatimavme_qdc3sample_three8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three8I,    UINT32,\
                    "fatimavme_qdc3sample_three8I",    "fatimavme_qdc3sample_three8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3sample_three8v,    UINT32,\
                    "fatimavme_qdc3sample_three8v",    "fatimavme_qdc3sample_three8",0/*flags*/); \
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
                     fatimavme_qdc4extras,            UINT32,\
                    "fatimavme_qdc4extras",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4dm,                UINT32,\
                    "fatimavme_qdc4dm",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4chan_baseline,     UINT32,\
                    "fatimavme_qdc4chan_baseline",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4chan_baselinev,    UINT32,\
                    "fatimavme_qdc4chan_baselinev",    "fatimavme_qdc4chan_baseline",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4chan_midscale,     UINT32,\
                    "fatimavme_qdc4chan_midscale",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4chan_midscalev,    UINT32,\
                    "fatimavme_qdc4chan_midscalev",    "fatimavme_qdc4chan_midscale",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4chan_sazc,         UINT32,\
                    "fatimavme_qdc4chan_sazc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4chan_sazcv,        UINT32,\
                    "fatimavme_qdc4chan_sazcv",        "fatimavme_qdc4chan_sazc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4chan_sbzc,         UINT32,\
                    "fatimavme_qdc4chan_sbzc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4chan_sbzcv,        UINT32,\
                    "fatimavme_qdc4chan_sbzcv",        "fatimavme_qdc4chan_sbzc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one1,       UINT32,\
                    "fatimavme_qdc4sample_one1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one1I,      UINT32,\
                    "fatimavme_qdc4sample_one1I",      "fatimavme_qdc4sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one1v,      UINT32,\
                    "fatimavme_qdc4sample_one1v",      "fatimavme_qdc4sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one2,       UINT32,\
                    "fatimavme_qdc4sample_one2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one2I,      UINT32,\
                    "fatimavme_qdc4sample_one2I",      "fatimavme_qdc4sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one2v,      UINT32,\
                    "fatimavme_qdc4sample_one2v",      "fatimavme_qdc4sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one3,       UINT32,\
                    "fatimavme_qdc4sample_one3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one3I,      UINT32,\
                    "fatimavme_qdc4sample_one3I",      "fatimavme_qdc4sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one3v,      UINT32,\
                    "fatimavme_qdc4sample_one3v",      "fatimavme_qdc4sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one4,       UINT32,\
                    "fatimavme_qdc4sample_one4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one4I,      UINT32,\
                    "fatimavme_qdc4sample_one4I",      "fatimavme_qdc4sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one4v,      UINT32,\
                    "fatimavme_qdc4sample_one4v",      "fatimavme_qdc4sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one5,       UINT32,\
                    "fatimavme_qdc4sample_one5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one5I,      UINT32,\
                    "fatimavme_qdc4sample_one5I",      "fatimavme_qdc4sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one5v,      UINT32,\
                    "fatimavme_qdc4sample_one5v",      "fatimavme_qdc4sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one6,       UINT32,\
                    "fatimavme_qdc4sample_one6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one6I,      UINT32,\
                    "fatimavme_qdc4sample_one6I",      "fatimavme_qdc4sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one6v,      UINT32,\
                    "fatimavme_qdc4sample_one6v",      "fatimavme_qdc4sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one7,       UINT32,\
                    "fatimavme_qdc4sample_one7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one7I,      UINT32,\
                    "fatimavme_qdc4sample_one7I",      "fatimavme_qdc4sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one7v,      UINT32,\
                    "fatimavme_qdc4sample_one7v",      "fatimavme_qdc4sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one8,       UINT32,\
                    "fatimavme_qdc4sample_one8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one8I,      UINT32,\
                    "fatimavme_qdc4sample_one8I",      "fatimavme_qdc4sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_one8v,      UINT32,\
                    "fatimavme_qdc4sample_one8v",      "fatimavme_qdc4sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two1,       UINT32,\
                    "fatimavme_qdc4sample_two1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two1I,      UINT32,\
                    "fatimavme_qdc4sample_two1I",      "fatimavme_qdc4sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two1v,      UINT32,\
                    "fatimavme_qdc4sample_two1v",      "fatimavme_qdc4sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two2,       UINT32,\
                    "fatimavme_qdc4sample_two2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two2I,      UINT32,\
                    "fatimavme_qdc4sample_two2I",      "fatimavme_qdc4sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two2v,      UINT32,\
                    "fatimavme_qdc4sample_two2v",      "fatimavme_qdc4sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two3,       UINT32,\
                    "fatimavme_qdc4sample_two3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two3I,      UINT32,\
                    "fatimavme_qdc4sample_two3I",      "fatimavme_qdc4sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two3v,      UINT32,\
                    "fatimavme_qdc4sample_two3v",      "fatimavme_qdc4sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two4,       UINT32,\
                    "fatimavme_qdc4sample_two4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two4I,      UINT32,\
                    "fatimavme_qdc4sample_two4I",      "fatimavme_qdc4sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two4v,      UINT32,\
                    "fatimavme_qdc4sample_two4v",      "fatimavme_qdc4sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two5,       UINT32,\
                    "fatimavme_qdc4sample_two5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two5I,      UINT32,\
                    "fatimavme_qdc4sample_two5I",      "fatimavme_qdc4sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two5v,      UINT32,\
                    "fatimavme_qdc4sample_two5v",      "fatimavme_qdc4sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two6,       UINT32,\
                    "fatimavme_qdc4sample_two6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two6I,      UINT32,\
                    "fatimavme_qdc4sample_two6I",      "fatimavme_qdc4sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two6v,      UINT32,\
                    "fatimavme_qdc4sample_two6v",      "fatimavme_qdc4sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two7,       UINT32,\
                    "fatimavme_qdc4sample_two7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two7I,      UINT32,\
                    "fatimavme_qdc4sample_two7I",      "fatimavme_qdc4sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two7v,      UINT32,\
                    "fatimavme_qdc4sample_two7v",      "fatimavme_qdc4sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two8,       UINT32,\
                    "fatimavme_qdc4sample_two8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two8I,      UINT32,\
                    "fatimavme_qdc4sample_two8I",      "fatimavme_qdc4sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_two8v,      UINT32,\
                    "fatimavme_qdc4sample_two8v",      "fatimavme_qdc4sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three1,     UINT32,\
                    "fatimavme_qdc4sample_three1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three1I,    UINT32,\
                    "fatimavme_qdc4sample_three1I",    "fatimavme_qdc4sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three1v,    UINT32,\
                    "fatimavme_qdc4sample_three1v",    "fatimavme_qdc4sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three2,     UINT32,\
                    "fatimavme_qdc4sample_three2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three2I,    UINT32,\
                    "fatimavme_qdc4sample_three2I",    "fatimavme_qdc4sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three2v,    UINT32,\
                    "fatimavme_qdc4sample_three2v",    "fatimavme_qdc4sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three3,     UINT32,\
                    "fatimavme_qdc4sample_three3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three3I,    UINT32,\
                    "fatimavme_qdc4sample_three3I",    "fatimavme_qdc4sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three3v,    UINT32,\
                    "fatimavme_qdc4sample_three3v",    "fatimavme_qdc4sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three4,     UINT32,\
                    "fatimavme_qdc4sample_three4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three4I,    UINT32,\
                    "fatimavme_qdc4sample_three4I",    "fatimavme_qdc4sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three4v,    UINT32,\
                    "fatimavme_qdc4sample_three4v",    "fatimavme_qdc4sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three5,     UINT32,\
                    "fatimavme_qdc4sample_three5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three5I,    UINT32,\
                    "fatimavme_qdc4sample_three5I",    "fatimavme_qdc4sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three5v,    UINT32,\
                    "fatimavme_qdc4sample_three5v",    "fatimavme_qdc4sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three6,     UINT32,\
                    "fatimavme_qdc4sample_three6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three6I,    UINT32,\
                    "fatimavme_qdc4sample_three6I",    "fatimavme_qdc4sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three6v,    UINT32,\
                    "fatimavme_qdc4sample_three6v",    "fatimavme_qdc4sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three7,     UINT32,\
                    "fatimavme_qdc4sample_three7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three7I,    UINT32,\
                    "fatimavme_qdc4sample_three7I",    "fatimavme_qdc4sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three7v,    UINT32,\
                    "fatimavme_qdc4sample_three7v",    "fatimavme_qdc4sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three8,     UINT32,\
                    "fatimavme_qdc4sample_three8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three8I,    UINT32,\
                    "fatimavme_qdc4sample_three8I",    "fatimavme_qdc4sample_three8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4sample_three8v,    UINT32,\
                    "fatimavme_qdc4sample_three8v",    "fatimavme_qdc4sample_three8",0/*flags*/); \
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
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5extras,            UINT32,\
                    "fatimavme_qdc5extras",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5dm,                UINT32,\
                    "fatimavme_qdc5dm",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5chan_baseline,     UINT32,\
                    "fatimavme_qdc5chan_baseline",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5chan_baselinev,    UINT32,\
                    "fatimavme_qdc5chan_baselinev",    "fatimavme_qdc5chan_baseline",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5chan_midscale,     UINT32,\
                    "fatimavme_qdc5chan_midscale",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5chan_midscalev,    UINT32,\
                    "fatimavme_qdc5chan_midscalev",    "fatimavme_qdc5chan_midscale",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5chan_sazc,         UINT32,\
                    "fatimavme_qdc5chan_sazc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5chan_sazcv,        UINT32,\
                    "fatimavme_qdc5chan_sazcv",        "fatimavme_qdc5chan_sazc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5chan_sbzc,         UINT32,\
                    "fatimavme_qdc5chan_sbzc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5chan_sbzcv,        UINT32,\
                    "fatimavme_qdc5chan_sbzcv",        "fatimavme_qdc5chan_sbzc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one1,       UINT32,\
                    "fatimavme_qdc5sample_one1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one1I,      UINT32,\
                    "fatimavme_qdc5sample_one1I",      "fatimavme_qdc5sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one1v,      UINT32,\
                    "fatimavme_qdc5sample_one1v",      "fatimavme_qdc5sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one2,       UINT32,\
                    "fatimavme_qdc5sample_one2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one2I,      UINT32,\
                    "fatimavme_qdc5sample_one2I",      "fatimavme_qdc5sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one2v,      UINT32,\
                    "fatimavme_qdc5sample_one2v",      "fatimavme_qdc5sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one3,       UINT32,\
                    "fatimavme_qdc5sample_one3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one3I,      UINT32,\
                    "fatimavme_qdc5sample_one3I",      "fatimavme_qdc5sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one3v,      UINT32,\
                    "fatimavme_qdc5sample_one3v",      "fatimavme_qdc5sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one4,       UINT32,\
                    "fatimavme_qdc5sample_one4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one4I,      UINT32,\
                    "fatimavme_qdc5sample_one4I",      "fatimavme_qdc5sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one4v,      UINT32,\
                    "fatimavme_qdc5sample_one4v",      "fatimavme_qdc5sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one5,       UINT32,\
                    "fatimavme_qdc5sample_one5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one5I,      UINT32,\
                    "fatimavme_qdc5sample_one5I",      "fatimavme_qdc5sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one5v,      UINT32,\
                    "fatimavme_qdc5sample_one5v",      "fatimavme_qdc5sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one6,       UINT32,\
                    "fatimavme_qdc5sample_one6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one6I,      UINT32,\
                    "fatimavme_qdc5sample_one6I",      "fatimavme_qdc5sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one6v,      UINT32,\
                    "fatimavme_qdc5sample_one6v",      "fatimavme_qdc5sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one7,       UINT32,\
                    "fatimavme_qdc5sample_one7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one7I,      UINT32,\
                    "fatimavme_qdc5sample_one7I",      "fatimavme_qdc5sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one7v,      UINT32,\
                    "fatimavme_qdc5sample_one7v",      "fatimavme_qdc5sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one8,       UINT32,\
                    "fatimavme_qdc5sample_one8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one8I,      UINT32,\
                    "fatimavme_qdc5sample_one8I",      "fatimavme_qdc5sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_one8v,      UINT32,\
                    "fatimavme_qdc5sample_one8v",      "fatimavme_qdc5sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two1,       UINT32,\
                    "fatimavme_qdc5sample_two1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two1I,      UINT32,\
                    "fatimavme_qdc5sample_two1I",      "fatimavme_qdc5sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two1v,      UINT32,\
                    "fatimavme_qdc5sample_two1v",      "fatimavme_qdc5sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two2,       UINT32,\
                    "fatimavme_qdc5sample_two2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two2I,      UINT32,\
                    "fatimavme_qdc5sample_two2I",      "fatimavme_qdc5sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two2v,      UINT32,\
                    "fatimavme_qdc5sample_two2v",      "fatimavme_qdc5sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two3,       UINT32,\
                    "fatimavme_qdc5sample_two3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two3I,      UINT32,\
                    "fatimavme_qdc5sample_two3I",      "fatimavme_qdc5sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two3v,      UINT32,\
                    "fatimavme_qdc5sample_two3v",      "fatimavme_qdc5sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two4,       UINT32,\
                    "fatimavme_qdc5sample_two4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two4I,      UINT32,\
                    "fatimavme_qdc5sample_two4I",      "fatimavme_qdc5sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two4v,      UINT32,\
                    "fatimavme_qdc5sample_two4v",      "fatimavme_qdc5sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two5,       UINT32,\
                    "fatimavme_qdc5sample_two5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two5I,      UINT32,\
                    "fatimavme_qdc5sample_two5I",      "fatimavme_qdc5sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two5v,      UINT32,\
                    "fatimavme_qdc5sample_two5v",      "fatimavme_qdc5sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two6,       UINT32,\
                    "fatimavme_qdc5sample_two6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two6I,      UINT32,\
                    "fatimavme_qdc5sample_two6I",      "fatimavme_qdc5sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two6v,      UINT32,\
                    "fatimavme_qdc5sample_two6v",      "fatimavme_qdc5sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two7,       UINT32,\
                    "fatimavme_qdc5sample_two7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two7I,      UINT32,\
                    "fatimavme_qdc5sample_two7I",      "fatimavme_qdc5sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two7v,      UINT32,\
                    "fatimavme_qdc5sample_two7v",      "fatimavme_qdc5sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two8,       UINT32,\
                    "fatimavme_qdc5sample_two8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two8I,      UINT32,\
                    "fatimavme_qdc5sample_two8I",      "fatimavme_qdc5sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_two8v,      UINT32,\
                    "fatimavme_qdc5sample_two8v",      "fatimavme_qdc5sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three1,     UINT32,\
                    "fatimavme_qdc5sample_three1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three1I,    UINT32,\
                    "fatimavme_qdc5sample_three1I",    "fatimavme_qdc5sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three1v,    UINT32,\
                    "fatimavme_qdc5sample_three1v",    "fatimavme_qdc5sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three2,     UINT32,\
                    "fatimavme_qdc5sample_three2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three2I,    UINT32,\
                    "fatimavme_qdc5sample_three2I",    "fatimavme_qdc5sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three2v,    UINT32,\
                    "fatimavme_qdc5sample_three2v",    "fatimavme_qdc5sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three3,     UINT32,\
                    "fatimavme_qdc5sample_three3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three3I,    UINT32,\
                    "fatimavme_qdc5sample_three3I",    "fatimavme_qdc5sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three3v,    UINT32,\
                    "fatimavme_qdc5sample_three3v",    "fatimavme_qdc5sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three4,     UINT32,\
                    "fatimavme_qdc5sample_three4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three4I,    UINT32,\
                    "fatimavme_qdc5sample_three4I",    "fatimavme_qdc5sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three4v,    UINT32,\
                    "fatimavme_qdc5sample_three4v",    "fatimavme_qdc5sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three5,     UINT32,\
                    "fatimavme_qdc5sample_three5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three5I,    UINT32,\
                    "fatimavme_qdc5sample_three5I",    "fatimavme_qdc5sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three5v,    UINT32,\
                    "fatimavme_qdc5sample_three5v",    "fatimavme_qdc5sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three6,     UINT32,\
                    "fatimavme_qdc5sample_three6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three6I,    UINT32,\
                    "fatimavme_qdc5sample_three6I",    "fatimavme_qdc5sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three6v,    UINT32,\
                    "fatimavme_qdc5sample_three6v",    "fatimavme_qdc5sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three7,     UINT32,\
                    "fatimavme_qdc5sample_three7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three7I,    UINT32,\
                    "fatimavme_qdc5sample_three7I",    "fatimavme_qdc5sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three7v,    UINT32,\
                    "fatimavme_qdc5sample_three7v",    "fatimavme_qdc5sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three8,     UINT32,\
                    "fatimavme_qdc5sample_three8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three8I,    UINT32,\
                    "fatimavme_qdc5sample_three8I",    "fatimavme_qdc5sample_three8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5sample_three8v,    UINT32,\
                    "fatimavme_qdc5sample_three8v",    "fatimavme_qdc5sample_three8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6board_id,          UINT32,\
                    "fatimavme_qdc6board_id",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6channels,          UINT32,\
                    "fatimavme_qdc6channels",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6board_time,        UINT32,\
                    "fatimavme_qdc6board_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6channel_time,      UINT32,\
                    "fatimavme_qdc6channel_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6channel_timev,     UINT32,\
                    "fatimavme_qdc6channel_timev",     "fatimavme_qdc6channel_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6chan_ext_time,     UINT32,\
                    "fatimavme_qdc6chan_ext_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6chan_ext_timev,    UINT32,\
                    "fatimavme_qdc6chan_ext_timev",    "fatimavme_qdc6chan_ext_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6chan_fine_time,    UINT32,\
                    "fatimavme_qdc6chan_fine_time",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6chan_fine_timev,   UINT32,\
                    "fatimavme_qdc6chan_fine_timev",   "fatimavme_qdc6chan_fine_time",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6qshort,            UINT32,\
                    "fatimavme_qdc6qshort",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6qshortv,           UINT32,\
                    "fatimavme_qdc6qshortv",           "fatimavme_qdc6qshort",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6qlong,             UINT32,\
                    "fatimavme_qdc6qlong",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6qlongv,            UINT32,\
                    "fatimavme_qdc6qlongv",            "fatimavme_qdc6qlong",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6extras,            UINT32,\
                    "fatimavme_qdc6extras",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6dm,                UINT32,\
                    "fatimavme_qdc6dm",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6chan_baseline,     UINT32,\
                    "fatimavme_qdc6chan_baseline",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6chan_baselinev,    UINT32,\
                    "fatimavme_qdc6chan_baselinev",    "fatimavme_qdc6chan_baseline",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6chan_midscale,     UINT32,\
                    "fatimavme_qdc6chan_midscale",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6chan_midscalev,    UINT32,\
                    "fatimavme_qdc6chan_midscalev",    "fatimavme_qdc6chan_midscale",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6chan_sazc,         UINT32,\
                    "fatimavme_qdc6chan_sazc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6chan_sazcv,        UINT32,\
                    "fatimavme_qdc6chan_sazcv",        "fatimavme_qdc6chan_sazc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6chan_sbzc,         UINT32,\
                    "fatimavme_qdc6chan_sbzc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6chan_sbzcv,        UINT32,\
                    "fatimavme_qdc6chan_sbzcv",        "fatimavme_qdc6chan_sbzc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one1,       UINT32,\
                    "fatimavme_qdc6sample_one1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one1I,      UINT32,\
                    "fatimavme_qdc6sample_one1I",      "fatimavme_qdc6sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one1v,      UINT32,\
                    "fatimavme_qdc6sample_one1v",      "fatimavme_qdc6sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one2,       UINT32,\
                    "fatimavme_qdc6sample_one2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one2I,      UINT32,\
                    "fatimavme_qdc6sample_one2I",      "fatimavme_qdc6sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one2v,      UINT32,\
                    "fatimavme_qdc6sample_one2v",      "fatimavme_qdc6sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one3,       UINT32,\
                    "fatimavme_qdc6sample_one3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one3I,      UINT32,\
                    "fatimavme_qdc6sample_one3I",      "fatimavme_qdc6sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one3v,      UINT32,\
                    "fatimavme_qdc6sample_one3v",      "fatimavme_qdc6sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one4,       UINT32,\
                    "fatimavme_qdc6sample_one4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one4I,      UINT32,\
                    "fatimavme_qdc6sample_one4I",      "fatimavme_qdc6sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one4v,      UINT32,\
                    "fatimavme_qdc6sample_one4v",      "fatimavme_qdc6sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one5,       UINT32,\
                    "fatimavme_qdc6sample_one5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one5I,      UINT32,\
                    "fatimavme_qdc6sample_one5I",      "fatimavme_qdc6sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one5v,      UINT32,\
                    "fatimavme_qdc6sample_one5v",      "fatimavme_qdc6sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one6,       UINT32,\
                    "fatimavme_qdc6sample_one6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one6I,      UINT32,\
                    "fatimavme_qdc6sample_one6I",      "fatimavme_qdc6sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one6v,      UINT32,\
                    "fatimavme_qdc6sample_one6v",      "fatimavme_qdc6sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one7,       UINT32,\
                    "fatimavme_qdc6sample_one7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one7I,      UINT32,\
                    "fatimavme_qdc6sample_one7I",      "fatimavme_qdc6sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one7v,      UINT32,\
                    "fatimavme_qdc6sample_one7v",      "fatimavme_qdc6sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one8,       UINT32,\
                    "fatimavme_qdc6sample_one8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one8I,      UINT32,\
                    "fatimavme_qdc6sample_one8I",      "fatimavme_qdc6sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_one8v,      UINT32,\
                    "fatimavme_qdc6sample_one8v",      "fatimavme_qdc6sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two1,       UINT32,\
                    "fatimavme_qdc6sample_two1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two1I,      UINT32,\
                    "fatimavme_qdc6sample_two1I",      "fatimavme_qdc6sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two1v,      UINT32,\
                    "fatimavme_qdc6sample_two1v",      "fatimavme_qdc6sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two2,       UINT32,\
                    "fatimavme_qdc6sample_two2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two2I,      UINT32,\
                    "fatimavme_qdc6sample_two2I",      "fatimavme_qdc6sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two2v,      UINT32,\
                    "fatimavme_qdc6sample_two2v",      "fatimavme_qdc6sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two3,       UINT32,\
                    "fatimavme_qdc6sample_two3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two3I,      UINT32,\
                    "fatimavme_qdc6sample_two3I",      "fatimavme_qdc6sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two3v,      UINT32,\
                    "fatimavme_qdc6sample_two3v",      "fatimavme_qdc6sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two4,       UINT32,\
                    "fatimavme_qdc6sample_two4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two4I,      UINT32,\
                    "fatimavme_qdc6sample_two4I",      "fatimavme_qdc6sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two4v,      UINT32,\
                    "fatimavme_qdc6sample_two4v",      "fatimavme_qdc6sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two5,       UINT32,\
                    "fatimavme_qdc6sample_two5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two5I,      UINT32,\
                    "fatimavme_qdc6sample_two5I",      "fatimavme_qdc6sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two5v,      UINT32,\
                    "fatimavme_qdc6sample_two5v",      "fatimavme_qdc6sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two6,       UINT32,\
                    "fatimavme_qdc6sample_two6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two6I,      UINT32,\
                    "fatimavme_qdc6sample_two6I",      "fatimavme_qdc6sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two6v,      UINT32,\
                    "fatimavme_qdc6sample_two6v",      "fatimavme_qdc6sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two7,       UINT32,\
                    "fatimavme_qdc6sample_two7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two7I,      UINT32,\
                    "fatimavme_qdc6sample_two7I",      "fatimavme_qdc6sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two7v,      UINT32,\
                    "fatimavme_qdc6sample_two7v",      "fatimavme_qdc6sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two8,       UINT32,\
                    "fatimavme_qdc6sample_two8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two8I,      UINT32,\
                    "fatimavme_qdc6sample_two8I",      "fatimavme_qdc6sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_two8v,      UINT32,\
                    "fatimavme_qdc6sample_two8v",      "fatimavme_qdc6sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three1,     UINT32,\
                    "fatimavme_qdc6sample_three1",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three1I,    UINT32,\
                    "fatimavme_qdc6sample_three1I",    "fatimavme_qdc6sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three1v,    UINT32,\
                    "fatimavme_qdc6sample_three1v",    "fatimavme_qdc6sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three2,     UINT32,\
                    "fatimavme_qdc6sample_three2",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three2I,    UINT32,\
                    "fatimavme_qdc6sample_three2I",    "fatimavme_qdc6sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three2v,    UINT32,\
                    "fatimavme_qdc6sample_three2v",    "fatimavme_qdc6sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three3,     UINT32,\
                    "fatimavme_qdc6sample_three3",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three3I,    UINT32,\
                    "fatimavme_qdc6sample_three3I",    "fatimavme_qdc6sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three3v,    UINT32,\
                    "fatimavme_qdc6sample_three3v",    "fatimavme_qdc6sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three4,     UINT32,\
                    "fatimavme_qdc6sample_three4",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three4I,    UINT32,\
                    "fatimavme_qdc6sample_three4I",    "fatimavme_qdc6sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three4v,    UINT32,\
                    "fatimavme_qdc6sample_three4v",    "fatimavme_qdc6sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three5,     UINT32,\
                    "fatimavme_qdc6sample_three5",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three5I,    UINT32,\
                    "fatimavme_qdc6sample_three5I",    "fatimavme_qdc6sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three5v,    UINT32,\
                    "fatimavme_qdc6sample_three5v",    "fatimavme_qdc6sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three6,     UINT32,\
                    "fatimavme_qdc6sample_three6",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three6I,    UINT32,\
                    "fatimavme_qdc6sample_three6I",    "fatimavme_qdc6sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three6v,    UINT32,\
                    "fatimavme_qdc6sample_three6v",    "fatimavme_qdc6sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three7,     UINT32,\
                    "fatimavme_qdc6sample_three7",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three7I,    UINT32,\
                    "fatimavme_qdc6sample_three7I",    "fatimavme_qdc6sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three7v,    UINT32,\
                    "fatimavme_qdc6sample_three7v",    "fatimavme_qdc6sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three8,     UINT32,\
                    "fatimavme_qdc6sample_three8",120,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three8I,    UINT32,\
                    "fatimavme_qdc6sample_three8I",    "fatimavme_qdc6sample_three8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc6sample_three8v,    UINT32,\
                    "fatimavme_qdc6sample_three8v",    "fatimavme_qdc6sample_three8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_geo,              UINT32,\
                    "fatimavme_tdc1_geo",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_measurement_nM,   UINT32,\
                    "fatimavme_tdc1_measurement_nM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_measurement_nMI,  UINT32,\
                    "fatimavme_tdc1_measurement_nMI",  "fatimavme_tdc1_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_measurement_nME,  UINT32,\
                    "fatimavme_tdc1_measurement_nME",  "fatimavme_tdc1_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_measurement_n,    UINT32,\
                    "fatimavme_tdc1_measurement_n",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_measurement_data, UINT32,\
                    "fatimavme_tdc1_measurement_data", "fatimavme_tdc1_measurement_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_measurement_leadOrTrailM,UINT32,\
                    "fatimavme_tdc1_measurement_leadOrTrailM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_measurement_leadOrTrailMI,UINT32,\
                    "fatimavme_tdc1_measurement_leadOrTrailMI","fatimavme_tdc1_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_measurement_leadOrTrailME,UINT32,\
                    "fatimavme_tdc1_measurement_leadOrTrailME","fatimavme_tdc1_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_measurement_leadOrTrail,UINT32,\
                    "fatimavme_tdc1_measurement_leadOrTrail",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc1_measurement_leadOrTrailv,UINT32,\
                    "fatimavme_tdc1_measurement_leadOrTrailv","fatimavme_tdc1_measurement_leadOrTrail",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_geo,              UINT32,\
                    "fatimavme_tdc2_geo",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_measurement_nM,   UINT32,\
                    "fatimavme_tdc2_measurement_nM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_measurement_nMI,  UINT32,\
                    "fatimavme_tdc2_measurement_nMI",  "fatimavme_tdc2_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_measurement_nME,  UINT32,\
                    "fatimavme_tdc2_measurement_nME",  "fatimavme_tdc2_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_measurement_n,    UINT32,\
                    "fatimavme_tdc2_measurement_n",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_measurement_data, UINT32,\
                    "fatimavme_tdc2_measurement_data", "fatimavme_tdc2_measurement_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_measurement_leadOrTrailM,UINT32,\
                    "fatimavme_tdc2_measurement_leadOrTrailM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_measurement_leadOrTrailMI,UINT32,\
                    "fatimavme_tdc2_measurement_leadOrTrailMI","fatimavme_tdc2_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_measurement_leadOrTrailME,UINT32,\
                    "fatimavme_tdc2_measurement_leadOrTrailME","fatimavme_tdc2_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_measurement_leadOrTrail,UINT32,\
                    "fatimavme_tdc2_measurement_leadOrTrail",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc2_measurement_leadOrTrailv,UINT32,\
                    "fatimavme_tdc2_measurement_leadOrTrailv","fatimavme_tdc2_measurement_leadOrTrail",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc3_geo,              UINT32,\
                    "fatimavme_tdc3_geo",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc3_measurement_nM,   UINT32,\
                    "fatimavme_tdc3_measurement_nM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc3_measurement_nMI,  UINT32,\
                    "fatimavme_tdc3_measurement_nMI",  "fatimavme_tdc3_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc3_measurement_nME,  UINT32,\
                    "fatimavme_tdc3_measurement_nME",  "fatimavme_tdc3_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc3_measurement_n,    UINT32,\
                    "fatimavme_tdc3_measurement_n",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc3_measurement_data, UINT32,\
                    "fatimavme_tdc3_measurement_data", "fatimavme_tdc3_measurement_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc3_measurement_leadOrTrailM,UINT32,\
                    "fatimavme_tdc3_measurement_leadOrTrailM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc3_measurement_leadOrTrailMI,UINT32,\
                    "fatimavme_tdc3_measurement_leadOrTrailMI","fatimavme_tdc3_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc3_measurement_leadOrTrailME,UINT32,\
                    "fatimavme_tdc3_measurement_leadOrTrailME","fatimavme_tdc3_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc3_measurement_leadOrTrail,UINT32,\
                    "fatimavme_tdc3_measurement_leadOrTrail",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc3_measurement_leadOrTrailv,UINT32,\
                    "fatimavme_tdc3_measurement_leadOrTrailv","fatimavme_tdc3_measurement_leadOrTrail",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc4_geo,              UINT32,\
                    "fatimavme_tdc4_geo",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc4_measurement_nM,   UINT32,\
                    "fatimavme_tdc4_measurement_nM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc4_measurement_nMI,  UINT32,\
                    "fatimavme_tdc4_measurement_nMI",  "fatimavme_tdc4_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc4_measurement_nME,  UINT32,\
                    "fatimavme_tdc4_measurement_nME",  "fatimavme_tdc4_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc4_measurement_n,    UINT32,\
                    "fatimavme_tdc4_measurement_n",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc4_measurement_data, UINT32,\
                    "fatimavme_tdc4_measurement_data", "fatimavme_tdc4_measurement_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc4_measurement_leadOrTrailM,UINT32,\
                    "fatimavme_tdc4_measurement_leadOrTrailM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc4_measurement_leadOrTrailMI,UINT32,\
                    "fatimavme_tdc4_measurement_leadOrTrailMI","fatimavme_tdc4_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc4_measurement_leadOrTrailME,UINT32,\
                    "fatimavme_tdc4_measurement_leadOrTrailME","fatimavme_tdc4_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc4_measurement_leadOrTrail,UINT32,\
                    "fatimavme_tdc4_measurement_leadOrTrail",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc4_measurement_leadOrTrailv,UINT32,\
                    "fatimavme_tdc4_measurement_leadOrTrailv","fatimavme_tdc4_measurement_leadOrTrail",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc5_geo,              UINT32,\
                    "fatimavme_tdc5_geo",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc5_measurement_nM,   UINT32,\
                    "fatimavme_tdc5_measurement_nM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc5_measurement_nMI,  UINT32,\
                    "fatimavme_tdc5_measurement_nMI",  "fatimavme_tdc5_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc5_measurement_nME,  UINT32,\
                    "fatimavme_tdc5_measurement_nME",  "fatimavme_tdc5_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc5_measurement_n,    UINT32,\
                    "fatimavme_tdc5_measurement_n",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc5_measurement_data, UINT32,\
                    "fatimavme_tdc5_measurement_data", "fatimavme_tdc5_measurement_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc5_measurement_leadOrTrailM,UINT32,\
                    "fatimavme_tdc5_measurement_leadOrTrailM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc5_measurement_leadOrTrailMI,UINT32,\
                    "fatimavme_tdc5_measurement_leadOrTrailMI","fatimavme_tdc5_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc5_measurement_leadOrTrailME,UINT32,\
                    "fatimavme_tdc5_measurement_leadOrTrailME","fatimavme_tdc5_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc5_measurement_leadOrTrail,UINT32,\
                    "fatimavme_tdc5_measurement_leadOrTrail",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc5_measurement_leadOrTrailv,UINT32,\
                    "fatimavme_tdc5_measurement_leadOrTrailv","fatimavme_tdc5_measurement_leadOrTrail",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc6_geo,              UINT32,\
                    "fatimavme_tdc6_geo",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc6_measurement_nM,   UINT32,\
                    "fatimavme_tdc6_measurement_nM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc6_measurement_nMI,  UINT32,\
                    "fatimavme_tdc6_measurement_nMI",  "fatimavme_tdc6_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc6_measurement_nME,  UINT32,\
                    "fatimavme_tdc6_measurement_nME",  "fatimavme_tdc6_measurement_nM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc6_measurement_n,    UINT32,\
                    "fatimavme_tdc6_measurement_n",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc6_measurement_data, UINT32,\
                    "fatimavme_tdc6_measurement_data", "fatimavme_tdc6_measurement_n",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc6_measurement_leadOrTrailM,UINT32,\
                    "fatimavme_tdc6_measurement_leadOrTrailM",128,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc6_measurement_leadOrTrailMI,UINT32,\
                    "fatimavme_tdc6_measurement_leadOrTrailMI","fatimavme_tdc6_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc6_measurement_leadOrTrailME,UINT32,\
                    "fatimavme_tdc6_measurement_leadOrTrailME","fatimavme_tdc6_measurement_leadOrTrailM",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc6_measurement_leadOrTrail,UINT32,\
                    "fatimavme_tdc6_measurement_leadOrTrail",16384,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_tdc6_measurement_leadOrTrailv,UINT32,\
                    "fatimavme_tdc6_measurement_leadOrTrailv","fatimavme_tdc6_measurement_leadOrTrail",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_FATIMAVME_EXT_H101_FATIMAVME_H__*/

/*******************************************************/
