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
  uint32_t fatimavme_qdc1_extras /* [0,65535] */;
  uint32_t fatimavme_qdc1_dm /* [0,65535] */;
  uint32_t fatimavme_qdc1_chan_baseline /* [0,64] */;
  uint32_t fatimavme_qdc1_chan_baselinev[64 EXT_STRUCT_CTRL(fatimavme_qdc1_chan_baseline)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_chan_midscale /* [0,64] */;
  uint32_t fatimavme_qdc1_chan_midscalev[64 EXT_STRUCT_CTRL(fatimavme_qdc1_chan_midscale)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_chan_sazc /* [0,64] */;
  uint32_t fatimavme_qdc1_chan_sazcv[64 EXT_STRUCT_CTRL(fatimavme_qdc1_chan_sazc)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_chan_sbzc /* [0,64] */;
  uint32_t fatimavme_qdc1_chan_sbzcv[64 EXT_STRUCT_CTRL(fatimavme_qdc1_chan_sbzc)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_one1 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_one1I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one1)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_one1v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one1)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_one2 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_one2I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one2)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_one2v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one2)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_one3 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_one3I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one3)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_one3v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one3)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_one4 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_one4I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one4)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_one4v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one4)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_one5 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_one5I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one5)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_one5v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one5)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_one6 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_one6I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one6)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_one6v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one6)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_one7 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_one7I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one7)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_one7v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one7)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_one8 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_one8I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one8)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_one8v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_one8)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_two1 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_two1I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two1)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_two1v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two1)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_two2 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_two2I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two2)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_two2v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two2)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_two3 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_two3I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two3)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_two3v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two3)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_two4 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_two4I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two4)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_two4v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two4)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_two5 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_two5I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two5)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_two5v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two5)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_two6 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_two6I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two6)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_two6v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two6)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_two7 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_two7I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two7)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_two7v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two7)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_two8 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_two8I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two8)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_two8v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_two8)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_three1 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_three1I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three1)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_three1v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three1)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_three2 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_three2I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three2)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_three2v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three2)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_three3 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_three3I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three3)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_three3v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three3)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_three4 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_three4I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three4)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_three4v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three4)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_three5 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_three5I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three5)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_three5v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three5)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_three6 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_three6I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three6)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_three6v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three6)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_three7 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_three7I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three7)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_three7v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three7)] /* [0,65535] */;
  uint32_t fatimavme_qdc1_sample_three8 /* [0,224] */;
  uint32_t fatimavme_qdc1_sample_three8I[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three8)] /* [1,224] */;
  uint32_t fatimavme_qdc1_sample_three8v[224 EXT_STRUCT_CTRL(fatimavme_qdc1_sample_three8)] /* [0,65535] */;
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
  uint32_t fatimavme_qdc2_extras /* [0,65535] */;
  uint32_t fatimavme_qdc2_dm /* [0,65535] */;
  uint32_t fatimavme_qdc2_chan_baseline /* [0,64] */;
  uint32_t fatimavme_qdc2_chan_baselinev[64 EXT_STRUCT_CTRL(fatimavme_qdc2_chan_baseline)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_chan_midscale /* [0,64] */;
  uint32_t fatimavme_qdc2_chan_midscalev[64 EXT_STRUCT_CTRL(fatimavme_qdc2_chan_midscale)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_chan_sazc /* [0,64] */;
  uint32_t fatimavme_qdc2_chan_sazcv[64 EXT_STRUCT_CTRL(fatimavme_qdc2_chan_sazc)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_chan_sbzc /* [0,64] */;
  uint32_t fatimavme_qdc2_chan_sbzcv[64 EXT_STRUCT_CTRL(fatimavme_qdc2_chan_sbzc)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_one1 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_one1I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one1)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_one1v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one1)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_one2 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_one2I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one2)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_one2v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one2)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_one3 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_one3I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one3)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_one3v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one3)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_one4 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_one4I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one4)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_one4v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one4)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_one5 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_one5I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one5)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_one5v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one5)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_one6 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_one6I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one6)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_one6v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one6)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_one7 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_one7I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one7)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_one7v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one7)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_one8 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_one8I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one8)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_one8v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_one8)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_two1 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_two1I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two1)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_two1v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two1)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_two2 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_two2I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two2)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_two2v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two2)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_two3 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_two3I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two3)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_two3v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two3)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_two4 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_two4I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two4)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_two4v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two4)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_two5 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_two5I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two5)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_two5v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two5)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_two6 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_two6I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two6)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_two6v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two6)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_two7 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_two7I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two7)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_two7v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two7)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_two8 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_two8I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two8)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_two8v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_two8)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_three1 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_three1I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three1)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_three1v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three1)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_three2 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_three2I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three2)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_three2v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three2)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_three3 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_three3I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three3)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_three3v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three3)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_three4 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_three4I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three4)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_three4v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three4)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_three5 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_three5I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three5)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_three5v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three5)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_three6 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_three6I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three6)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_three6v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three6)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_three7 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_three7I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three7)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_three7v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three7)] /* [0,65535] */;
  uint32_t fatimavme_qdc2_sample_three8 /* [0,224] */;
  uint32_t fatimavme_qdc2_sample_three8I[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three8)] /* [1,224] */;
  uint32_t fatimavme_qdc2_sample_three8v[224 EXT_STRUCT_CTRL(fatimavme_qdc2_sample_three8)] /* [0,65535] */;
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
  uint32_t fatimavme_qdc3_extras /* [0,65535] */;
  uint32_t fatimavme_qdc3_dm /* [0,65535] */;
  uint32_t fatimavme_qdc3_chan_baseline /* [0,64] */;
  uint32_t fatimavme_qdc3_chan_baselinev[64 EXT_STRUCT_CTRL(fatimavme_qdc3_chan_baseline)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_chan_midscale /* [0,64] */;
  uint32_t fatimavme_qdc3_chan_midscalev[64 EXT_STRUCT_CTRL(fatimavme_qdc3_chan_midscale)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_chan_sazc /* [0,64] */;
  uint32_t fatimavme_qdc3_chan_sazcv[64 EXT_STRUCT_CTRL(fatimavme_qdc3_chan_sazc)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_chan_sbzc /* [0,64] */;
  uint32_t fatimavme_qdc3_chan_sbzcv[64 EXT_STRUCT_CTRL(fatimavme_qdc3_chan_sbzc)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_one1 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_one1I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one1)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_one1v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one1)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_one2 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_one2I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one2)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_one2v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one2)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_one3 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_one3I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one3)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_one3v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one3)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_one4 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_one4I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one4)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_one4v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one4)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_one5 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_one5I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one5)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_one5v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one5)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_one6 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_one6I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one6)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_one6v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one6)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_one7 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_one7I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one7)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_one7v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one7)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_one8 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_one8I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one8)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_one8v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_one8)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_two1 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_two1I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two1)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_two1v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two1)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_two2 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_two2I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two2)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_two2v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two2)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_two3 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_two3I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two3)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_two3v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two3)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_two4 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_two4I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two4)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_two4v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two4)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_two5 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_two5I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two5)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_two5v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two5)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_two6 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_two6I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two6)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_two6v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two6)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_two7 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_two7I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two7)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_two7v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two7)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_two8 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_two8I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two8)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_two8v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_two8)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_three1 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_three1I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three1)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_three1v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three1)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_three2 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_three2I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three2)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_three2v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three2)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_three3 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_three3I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three3)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_three3v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three3)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_three4 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_three4I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three4)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_three4v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three4)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_three5 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_three5I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three5)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_three5v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three5)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_three6 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_three6I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three6)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_three6v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three6)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_three7 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_three7I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three7)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_three7v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three7)] /* [0,65535] */;
  uint32_t fatimavme_qdc3_sample_three8 /* [0,224] */;
  uint32_t fatimavme_qdc3_sample_three8I[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three8)] /* [1,224] */;
  uint32_t fatimavme_qdc3_sample_three8v[224 EXT_STRUCT_CTRL(fatimavme_qdc3_sample_three8)] /* [0,65535] */;
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
  uint32_t fatimavme_qdc4_extras /* [0,65535] */;
  uint32_t fatimavme_qdc4_dm /* [0,65535] */;
  uint32_t fatimavme_qdc4_chan_baseline /* [0,64] */;
  uint32_t fatimavme_qdc4_chan_baselinev[64 EXT_STRUCT_CTRL(fatimavme_qdc4_chan_baseline)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_chan_midscale /* [0,64] */;
  uint32_t fatimavme_qdc4_chan_midscalev[64 EXT_STRUCT_CTRL(fatimavme_qdc4_chan_midscale)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_chan_sazc /* [0,64] */;
  uint32_t fatimavme_qdc4_chan_sazcv[64 EXT_STRUCT_CTRL(fatimavme_qdc4_chan_sazc)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_chan_sbzc /* [0,64] */;
  uint32_t fatimavme_qdc4_chan_sbzcv[64 EXT_STRUCT_CTRL(fatimavme_qdc4_chan_sbzc)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_one1 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_one1I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one1)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_one1v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one1)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_one2 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_one2I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one2)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_one2v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one2)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_one3 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_one3I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one3)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_one3v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one3)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_one4 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_one4I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one4)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_one4v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one4)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_one5 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_one5I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one5)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_one5v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one5)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_one6 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_one6I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one6)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_one6v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one6)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_one7 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_one7I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one7)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_one7v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one7)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_one8 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_one8I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one8)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_one8v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_one8)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_two1 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_two1I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two1)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_two1v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two1)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_two2 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_two2I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two2)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_two2v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two2)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_two3 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_two3I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two3)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_two3v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two3)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_two4 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_two4I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two4)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_two4v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two4)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_two5 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_two5I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two5)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_two5v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two5)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_two6 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_two6I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two6)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_two6v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two6)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_two7 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_two7I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two7)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_two7v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two7)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_two8 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_two8I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two8)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_two8v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_two8)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_three1 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_three1I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three1)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_three1v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three1)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_three2 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_three2I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three2)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_three2v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three2)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_three3 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_three3I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three3)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_three3v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three3)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_three4 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_three4I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three4)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_three4v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three4)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_three5 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_three5I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three5)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_three5v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three5)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_three6 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_three6I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three6)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_three6v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three6)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_three7 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_three7I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three7)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_three7v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three7)] /* [0,65535] */;
  uint32_t fatimavme_qdc4_sample_three8 /* [0,224] */;
  uint32_t fatimavme_qdc4_sample_three8I[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three8)] /* [1,224] */;
  uint32_t fatimavme_qdc4_sample_three8v[224 EXT_STRUCT_CTRL(fatimavme_qdc4_sample_three8)] /* [0,65535] */;
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
  uint32_t fatimavme_qdc5_extras /* [0,65535] */;
  uint32_t fatimavme_qdc5_dm /* [0,65535] */;
  uint32_t fatimavme_qdc5_chan_baseline /* [0,64] */;
  uint32_t fatimavme_qdc5_chan_baselinev[64 EXT_STRUCT_CTRL(fatimavme_qdc5_chan_baseline)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_chan_midscale /* [0,64] */;
  uint32_t fatimavme_qdc5_chan_midscalev[64 EXT_STRUCT_CTRL(fatimavme_qdc5_chan_midscale)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_chan_sazc /* [0,64] */;
  uint32_t fatimavme_qdc5_chan_sazcv[64 EXT_STRUCT_CTRL(fatimavme_qdc5_chan_sazc)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_chan_sbzc /* [0,64] */;
  uint32_t fatimavme_qdc5_chan_sbzcv[64 EXT_STRUCT_CTRL(fatimavme_qdc5_chan_sbzc)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_one1 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_one1I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one1)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_one1v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one1)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_one2 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_one2I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one2)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_one2v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one2)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_one3 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_one3I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one3)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_one3v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one3)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_one4 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_one4I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one4)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_one4v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one4)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_one5 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_one5I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one5)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_one5v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one5)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_one6 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_one6I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one6)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_one6v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one6)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_one7 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_one7I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one7)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_one7v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one7)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_one8 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_one8I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one8)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_one8v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_one8)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_two1 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_two1I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two1)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_two1v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two1)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_two2 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_two2I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two2)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_two2v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two2)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_two3 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_two3I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two3)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_two3v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two3)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_two4 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_two4I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two4)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_two4v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two4)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_two5 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_two5I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two5)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_two5v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two5)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_two6 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_two6I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two6)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_two6v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two6)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_two7 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_two7I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two7)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_two7v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two7)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_two8 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_two8I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two8)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_two8v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_two8)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_three1 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_three1I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three1)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_three1v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three1)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_three2 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_three2I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three2)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_three2v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three2)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_three3 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_three3I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three3)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_three3v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three3)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_three4 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_three4I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three4)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_three4v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three4)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_three5 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_three5I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three5)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_three5v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three5)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_three6 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_three6I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three6)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_three6v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three6)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_three7 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_three7I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three7)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_three7v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three7)] /* [0,65535] */;
  uint32_t fatimavme_qdc5_sample_three8 /* [0,224] */;
  uint32_t fatimavme_qdc5_sample_three8I[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three8)] /* [1,224] */;
  uint32_t fatimavme_qdc5_sample_three8v[224 EXT_STRUCT_CTRL(fatimavme_qdc5_sample_three8)] /* [0,65535] */;
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
    uint32_t _extras;
    uint32_t _dm;
    uint32_t _chan_baseline;
    uint32_t _chan_baselinev[64 /* _chan_baseline */];
    uint32_t _chan_midscale;
    uint32_t _chan_midscalev[64 /* _chan_midscale */];
    uint32_t _chan_sazc;
    uint32_t _chan_sazcv[64 /* _chan_sazc */];
    uint32_t _chan_sbzc;
    uint32_t _chan_sbzcv[64 /* _chan_sbzc */];
    struct {
      uint32_t _;
      uint32_t I[224 /*  */];
      uint32_t v[224 /*  */];
    } _sample_one[8];
    struct {
      uint32_t _;
      uint32_t I[224 /*  */];
      uint32_t v[224 /*  */];
    } _sample_two[8];
    struct {
      uint32_t _;
      uint32_t I[224 /*  */];
      uint32_t v[224 /*  */];
    } _sample_three[8];
  } fatimavme_qdc[5];
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
                     fatimavme_qdc1_extras,           UINT32,\
                    "fatimavme_qdc1_extras",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_dm,               UINT32,\
                    "fatimavme_qdc1_dm",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_chan_baseline,    UINT32,\
                    "fatimavme_qdc1_chan_baseline",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_chan_baselinev,   UINT32,\
                    "fatimavme_qdc1_chan_baselinev",   "fatimavme_qdc1_chan_baseline",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_chan_midscale,    UINT32,\
                    "fatimavme_qdc1_chan_midscale",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_chan_midscalev,   UINT32,\
                    "fatimavme_qdc1_chan_midscalev",   "fatimavme_qdc1_chan_midscale",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_chan_sazc,        UINT32,\
                    "fatimavme_qdc1_chan_sazc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_chan_sazcv,       UINT32,\
                    "fatimavme_qdc1_chan_sazcv",       "fatimavme_qdc1_chan_sazc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_chan_sbzc,        UINT32,\
                    "fatimavme_qdc1_chan_sbzc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_chan_sbzcv,       UINT32,\
                    "fatimavme_qdc1_chan_sbzcv",       "fatimavme_qdc1_chan_sbzc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one1,      UINT32,\
                    "fatimavme_qdc1_sample_one1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one1I,     UINT32,\
                    "fatimavme_qdc1_sample_one1I",     "fatimavme_qdc1_sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one1v,     UINT32,\
                    "fatimavme_qdc1_sample_one1v",     "fatimavme_qdc1_sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one2,      UINT32,\
                    "fatimavme_qdc1_sample_one2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one2I,     UINT32,\
                    "fatimavme_qdc1_sample_one2I",     "fatimavme_qdc1_sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one2v,     UINT32,\
                    "fatimavme_qdc1_sample_one2v",     "fatimavme_qdc1_sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one3,      UINT32,\
                    "fatimavme_qdc1_sample_one3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one3I,     UINT32,\
                    "fatimavme_qdc1_sample_one3I",     "fatimavme_qdc1_sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one3v,     UINT32,\
                    "fatimavme_qdc1_sample_one3v",     "fatimavme_qdc1_sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one4,      UINT32,\
                    "fatimavme_qdc1_sample_one4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one4I,     UINT32,\
                    "fatimavme_qdc1_sample_one4I",     "fatimavme_qdc1_sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one4v,     UINT32,\
                    "fatimavme_qdc1_sample_one4v",     "fatimavme_qdc1_sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one5,      UINT32,\
                    "fatimavme_qdc1_sample_one5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one5I,     UINT32,\
                    "fatimavme_qdc1_sample_one5I",     "fatimavme_qdc1_sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one5v,     UINT32,\
                    "fatimavme_qdc1_sample_one5v",     "fatimavme_qdc1_sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one6,      UINT32,\
                    "fatimavme_qdc1_sample_one6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one6I,     UINT32,\
                    "fatimavme_qdc1_sample_one6I",     "fatimavme_qdc1_sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one6v,     UINT32,\
                    "fatimavme_qdc1_sample_one6v",     "fatimavme_qdc1_sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one7,      UINT32,\
                    "fatimavme_qdc1_sample_one7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one7I,     UINT32,\
                    "fatimavme_qdc1_sample_one7I",     "fatimavme_qdc1_sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one7v,     UINT32,\
                    "fatimavme_qdc1_sample_one7v",     "fatimavme_qdc1_sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one8,      UINT32,\
                    "fatimavme_qdc1_sample_one8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one8I,     UINT32,\
                    "fatimavme_qdc1_sample_one8I",     "fatimavme_qdc1_sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_one8v,     UINT32,\
                    "fatimavme_qdc1_sample_one8v",     "fatimavme_qdc1_sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two1,      UINT32,\
                    "fatimavme_qdc1_sample_two1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two1I,     UINT32,\
                    "fatimavme_qdc1_sample_two1I",     "fatimavme_qdc1_sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two1v,     UINT32,\
                    "fatimavme_qdc1_sample_two1v",     "fatimavme_qdc1_sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two2,      UINT32,\
                    "fatimavme_qdc1_sample_two2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two2I,     UINT32,\
                    "fatimavme_qdc1_sample_two2I",     "fatimavme_qdc1_sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two2v,     UINT32,\
                    "fatimavme_qdc1_sample_two2v",     "fatimavme_qdc1_sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two3,      UINT32,\
                    "fatimavme_qdc1_sample_two3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two3I,     UINT32,\
                    "fatimavme_qdc1_sample_two3I",     "fatimavme_qdc1_sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two3v,     UINT32,\
                    "fatimavme_qdc1_sample_two3v",     "fatimavme_qdc1_sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two4,      UINT32,\
                    "fatimavme_qdc1_sample_two4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two4I,     UINT32,\
                    "fatimavme_qdc1_sample_two4I",     "fatimavme_qdc1_sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two4v,     UINT32,\
                    "fatimavme_qdc1_sample_two4v",     "fatimavme_qdc1_sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two5,      UINT32,\
                    "fatimavme_qdc1_sample_two5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two5I,     UINT32,\
                    "fatimavme_qdc1_sample_two5I",     "fatimavme_qdc1_sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two5v,     UINT32,\
                    "fatimavme_qdc1_sample_two5v",     "fatimavme_qdc1_sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two6,      UINT32,\
                    "fatimavme_qdc1_sample_two6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two6I,     UINT32,\
                    "fatimavme_qdc1_sample_two6I",     "fatimavme_qdc1_sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two6v,     UINT32,\
                    "fatimavme_qdc1_sample_two6v",     "fatimavme_qdc1_sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two7,      UINT32,\
                    "fatimavme_qdc1_sample_two7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two7I,     UINT32,\
                    "fatimavme_qdc1_sample_two7I",     "fatimavme_qdc1_sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two7v,     UINT32,\
                    "fatimavme_qdc1_sample_two7v",     "fatimavme_qdc1_sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two8,      UINT32,\
                    "fatimavme_qdc1_sample_two8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two8I,     UINT32,\
                    "fatimavme_qdc1_sample_two8I",     "fatimavme_qdc1_sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_two8v,     UINT32,\
                    "fatimavme_qdc1_sample_two8v",     "fatimavme_qdc1_sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three1,    UINT32,\
                    "fatimavme_qdc1_sample_three1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three1I,   UINT32,\
                    "fatimavme_qdc1_sample_three1I",   "fatimavme_qdc1_sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three1v,   UINT32,\
                    "fatimavme_qdc1_sample_three1v",   "fatimavme_qdc1_sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three2,    UINT32,\
                    "fatimavme_qdc1_sample_three2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three2I,   UINT32,\
                    "fatimavme_qdc1_sample_three2I",   "fatimavme_qdc1_sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three2v,   UINT32,\
                    "fatimavme_qdc1_sample_three2v",   "fatimavme_qdc1_sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three3,    UINT32,\
                    "fatimavme_qdc1_sample_three3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three3I,   UINT32,\
                    "fatimavme_qdc1_sample_three3I",   "fatimavme_qdc1_sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three3v,   UINT32,\
                    "fatimavme_qdc1_sample_three3v",   "fatimavme_qdc1_sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three4,    UINT32,\
                    "fatimavme_qdc1_sample_three4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three4I,   UINT32,\
                    "fatimavme_qdc1_sample_three4I",   "fatimavme_qdc1_sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three4v,   UINT32,\
                    "fatimavme_qdc1_sample_three4v",   "fatimavme_qdc1_sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three5,    UINT32,\
                    "fatimavme_qdc1_sample_three5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three5I,   UINT32,\
                    "fatimavme_qdc1_sample_three5I",   "fatimavme_qdc1_sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three5v,   UINT32,\
                    "fatimavme_qdc1_sample_three5v",   "fatimavme_qdc1_sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three6,    UINT32,\
                    "fatimavme_qdc1_sample_three6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three6I,   UINT32,\
                    "fatimavme_qdc1_sample_three6I",   "fatimavme_qdc1_sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three6v,   UINT32,\
                    "fatimavme_qdc1_sample_three6v",   "fatimavme_qdc1_sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three7,    UINT32,\
                    "fatimavme_qdc1_sample_three7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three7I,   UINT32,\
                    "fatimavme_qdc1_sample_three7I",   "fatimavme_qdc1_sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three7v,   UINT32,\
                    "fatimavme_qdc1_sample_three7v",   "fatimavme_qdc1_sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three8,    UINT32,\
                    "fatimavme_qdc1_sample_three8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three8I,   UINT32,\
                    "fatimavme_qdc1_sample_three8I",   "fatimavme_qdc1_sample_three8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc1_sample_three8v,   UINT32,\
                    "fatimavme_qdc1_sample_three8v",   "fatimavme_qdc1_sample_three8",0/*flags*/); \
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
                     fatimavme_qdc2_extras,           UINT32,\
                    "fatimavme_qdc2_extras",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_dm,               UINT32,\
                    "fatimavme_qdc2_dm",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_chan_baseline,    UINT32,\
                    "fatimavme_qdc2_chan_baseline",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_chan_baselinev,   UINT32,\
                    "fatimavme_qdc2_chan_baselinev",   "fatimavme_qdc2_chan_baseline",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_chan_midscale,    UINT32,\
                    "fatimavme_qdc2_chan_midscale",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_chan_midscalev,   UINT32,\
                    "fatimavme_qdc2_chan_midscalev",   "fatimavme_qdc2_chan_midscale",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_chan_sazc,        UINT32,\
                    "fatimavme_qdc2_chan_sazc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_chan_sazcv,       UINT32,\
                    "fatimavme_qdc2_chan_sazcv",       "fatimavme_qdc2_chan_sazc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_chan_sbzc,        UINT32,\
                    "fatimavme_qdc2_chan_sbzc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_chan_sbzcv,       UINT32,\
                    "fatimavme_qdc2_chan_sbzcv",       "fatimavme_qdc2_chan_sbzc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one1,      UINT32,\
                    "fatimavme_qdc2_sample_one1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one1I,     UINT32,\
                    "fatimavme_qdc2_sample_one1I",     "fatimavme_qdc2_sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one1v,     UINT32,\
                    "fatimavme_qdc2_sample_one1v",     "fatimavme_qdc2_sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one2,      UINT32,\
                    "fatimavme_qdc2_sample_one2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one2I,     UINT32,\
                    "fatimavme_qdc2_sample_one2I",     "fatimavme_qdc2_sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one2v,     UINT32,\
                    "fatimavme_qdc2_sample_one2v",     "fatimavme_qdc2_sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one3,      UINT32,\
                    "fatimavme_qdc2_sample_one3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one3I,     UINT32,\
                    "fatimavme_qdc2_sample_one3I",     "fatimavme_qdc2_sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one3v,     UINT32,\
                    "fatimavme_qdc2_sample_one3v",     "fatimavme_qdc2_sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one4,      UINT32,\
                    "fatimavme_qdc2_sample_one4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one4I,     UINT32,\
                    "fatimavme_qdc2_sample_one4I",     "fatimavme_qdc2_sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one4v,     UINT32,\
                    "fatimavme_qdc2_sample_one4v",     "fatimavme_qdc2_sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one5,      UINT32,\
                    "fatimavme_qdc2_sample_one5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one5I,     UINT32,\
                    "fatimavme_qdc2_sample_one5I",     "fatimavme_qdc2_sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one5v,     UINT32,\
                    "fatimavme_qdc2_sample_one5v",     "fatimavme_qdc2_sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one6,      UINT32,\
                    "fatimavme_qdc2_sample_one6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one6I,     UINT32,\
                    "fatimavme_qdc2_sample_one6I",     "fatimavme_qdc2_sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one6v,     UINT32,\
                    "fatimavme_qdc2_sample_one6v",     "fatimavme_qdc2_sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one7,      UINT32,\
                    "fatimavme_qdc2_sample_one7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one7I,     UINT32,\
                    "fatimavme_qdc2_sample_one7I",     "fatimavme_qdc2_sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one7v,     UINT32,\
                    "fatimavme_qdc2_sample_one7v",     "fatimavme_qdc2_sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one8,      UINT32,\
                    "fatimavme_qdc2_sample_one8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one8I,     UINT32,\
                    "fatimavme_qdc2_sample_one8I",     "fatimavme_qdc2_sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_one8v,     UINT32,\
                    "fatimavme_qdc2_sample_one8v",     "fatimavme_qdc2_sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two1,      UINT32,\
                    "fatimavme_qdc2_sample_two1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two1I,     UINT32,\
                    "fatimavme_qdc2_sample_two1I",     "fatimavme_qdc2_sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two1v,     UINT32,\
                    "fatimavme_qdc2_sample_two1v",     "fatimavme_qdc2_sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two2,      UINT32,\
                    "fatimavme_qdc2_sample_two2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two2I,     UINT32,\
                    "fatimavme_qdc2_sample_two2I",     "fatimavme_qdc2_sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two2v,     UINT32,\
                    "fatimavme_qdc2_sample_two2v",     "fatimavme_qdc2_sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two3,      UINT32,\
                    "fatimavme_qdc2_sample_two3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two3I,     UINT32,\
                    "fatimavme_qdc2_sample_two3I",     "fatimavme_qdc2_sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two3v,     UINT32,\
                    "fatimavme_qdc2_sample_two3v",     "fatimavme_qdc2_sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two4,      UINT32,\
                    "fatimavme_qdc2_sample_two4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two4I,     UINT32,\
                    "fatimavme_qdc2_sample_two4I",     "fatimavme_qdc2_sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two4v,     UINT32,\
                    "fatimavme_qdc2_sample_two4v",     "fatimavme_qdc2_sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two5,      UINT32,\
                    "fatimavme_qdc2_sample_two5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two5I,     UINT32,\
                    "fatimavme_qdc2_sample_two5I",     "fatimavme_qdc2_sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two5v,     UINT32,\
                    "fatimavme_qdc2_sample_two5v",     "fatimavme_qdc2_sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two6,      UINT32,\
                    "fatimavme_qdc2_sample_two6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two6I,     UINT32,\
                    "fatimavme_qdc2_sample_two6I",     "fatimavme_qdc2_sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two6v,     UINT32,\
                    "fatimavme_qdc2_sample_two6v",     "fatimavme_qdc2_sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two7,      UINT32,\
                    "fatimavme_qdc2_sample_two7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two7I,     UINT32,\
                    "fatimavme_qdc2_sample_two7I",     "fatimavme_qdc2_sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two7v,     UINT32,\
                    "fatimavme_qdc2_sample_two7v",     "fatimavme_qdc2_sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two8,      UINT32,\
                    "fatimavme_qdc2_sample_two8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two8I,     UINT32,\
                    "fatimavme_qdc2_sample_two8I",     "fatimavme_qdc2_sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_two8v,     UINT32,\
                    "fatimavme_qdc2_sample_two8v",     "fatimavme_qdc2_sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three1,    UINT32,\
                    "fatimavme_qdc2_sample_three1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three1I,   UINT32,\
                    "fatimavme_qdc2_sample_three1I",   "fatimavme_qdc2_sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three1v,   UINT32,\
                    "fatimavme_qdc2_sample_three1v",   "fatimavme_qdc2_sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three2,    UINT32,\
                    "fatimavme_qdc2_sample_three2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three2I,   UINT32,\
                    "fatimavme_qdc2_sample_three2I",   "fatimavme_qdc2_sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three2v,   UINT32,\
                    "fatimavme_qdc2_sample_three2v",   "fatimavme_qdc2_sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three3,    UINT32,\
                    "fatimavme_qdc2_sample_three3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three3I,   UINT32,\
                    "fatimavme_qdc2_sample_three3I",   "fatimavme_qdc2_sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three3v,   UINT32,\
                    "fatimavme_qdc2_sample_three3v",   "fatimavme_qdc2_sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three4,    UINT32,\
                    "fatimavme_qdc2_sample_three4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three4I,   UINT32,\
                    "fatimavme_qdc2_sample_three4I",   "fatimavme_qdc2_sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three4v,   UINT32,\
                    "fatimavme_qdc2_sample_three4v",   "fatimavme_qdc2_sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three5,    UINT32,\
                    "fatimavme_qdc2_sample_three5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three5I,   UINT32,\
                    "fatimavme_qdc2_sample_three5I",   "fatimavme_qdc2_sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three5v,   UINT32,\
                    "fatimavme_qdc2_sample_three5v",   "fatimavme_qdc2_sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three6,    UINT32,\
                    "fatimavme_qdc2_sample_three6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three6I,   UINT32,\
                    "fatimavme_qdc2_sample_three6I",   "fatimavme_qdc2_sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three6v,   UINT32,\
                    "fatimavme_qdc2_sample_three6v",   "fatimavme_qdc2_sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three7,    UINT32,\
                    "fatimavme_qdc2_sample_three7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three7I,   UINT32,\
                    "fatimavme_qdc2_sample_three7I",   "fatimavme_qdc2_sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three7v,   UINT32,\
                    "fatimavme_qdc2_sample_three7v",   "fatimavme_qdc2_sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three8,    UINT32,\
                    "fatimavme_qdc2_sample_three8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three8I,   UINT32,\
                    "fatimavme_qdc2_sample_three8I",   "fatimavme_qdc2_sample_three8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc2_sample_three8v,   UINT32,\
                    "fatimavme_qdc2_sample_three8v",   "fatimavme_qdc2_sample_three8",0/*flags*/); \
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
                     fatimavme_qdc3_extras,           UINT32,\
                    "fatimavme_qdc3_extras",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_dm,               UINT32,\
                    "fatimavme_qdc3_dm",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_chan_baseline,    UINT32,\
                    "fatimavme_qdc3_chan_baseline",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_chan_baselinev,   UINT32,\
                    "fatimavme_qdc3_chan_baselinev",   "fatimavme_qdc3_chan_baseline",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_chan_midscale,    UINT32,\
                    "fatimavme_qdc3_chan_midscale",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_chan_midscalev,   UINT32,\
                    "fatimavme_qdc3_chan_midscalev",   "fatimavme_qdc3_chan_midscale",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_chan_sazc,        UINT32,\
                    "fatimavme_qdc3_chan_sazc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_chan_sazcv,       UINT32,\
                    "fatimavme_qdc3_chan_sazcv",       "fatimavme_qdc3_chan_sazc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_chan_sbzc,        UINT32,\
                    "fatimavme_qdc3_chan_sbzc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_chan_sbzcv,       UINT32,\
                    "fatimavme_qdc3_chan_sbzcv",       "fatimavme_qdc3_chan_sbzc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one1,      UINT32,\
                    "fatimavme_qdc3_sample_one1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one1I,     UINT32,\
                    "fatimavme_qdc3_sample_one1I",     "fatimavme_qdc3_sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one1v,     UINT32,\
                    "fatimavme_qdc3_sample_one1v",     "fatimavme_qdc3_sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one2,      UINT32,\
                    "fatimavme_qdc3_sample_one2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one2I,     UINT32,\
                    "fatimavme_qdc3_sample_one2I",     "fatimavme_qdc3_sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one2v,     UINT32,\
                    "fatimavme_qdc3_sample_one2v",     "fatimavme_qdc3_sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one3,      UINT32,\
                    "fatimavme_qdc3_sample_one3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one3I,     UINT32,\
                    "fatimavme_qdc3_sample_one3I",     "fatimavme_qdc3_sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one3v,     UINT32,\
                    "fatimavme_qdc3_sample_one3v",     "fatimavme_qdc3_sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one4,      UINT32,\
                    "fatimavme_qdc3_sample_one4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one4I,     UINT32,\
                    "fatimavme_qdc3_sample_one4I",     "fatimavme_qdc3_sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one4v,     UINT32,\
                    "fatimavme_qdc3_sample_one4v",     "fatimavme_qdc3_sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one5,      UINT32,\
                    "fatimavme_qdc3_sample_one5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one5I,     UINT32,\
                    "fatimavme_qdc3_sample_one5I",     "fatimavme_qdc3_sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one5v,     UINT32,\
                    "fatimavme_qdc3_sample_one5v",     "fatimavme_qdc3_sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one6,      UINT32,\
                    "fatimavme_qdc3_sample_one6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one6I,     UINT32,\
                    "fatimavme_qdc3_sample_one6I",     "fatimavme_qdc3_sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one6v,     UINT32,\
                    "fatimavme_qdc3_sample_one6v",     "fatimavme_qdc3_sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one7,      UINT32,\
                    "fatimavme_qdc3_sample_one7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one7I,     UINT32,\
                    "fatimavme_qdc3_sample_one7I",     "fatimavme_qdc3_sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one7v,     UINT32,\
                    "fatimavme_qdc3_sample_one7v",     "fatimavme_qdc3_sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one8,      UINT32,\
                    "fatimavme_qdc3_sample_one8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one8I,     UINT32,\
                    "fatimavme_qdc3_sample_one8I",     "fatimavme_qdc3_sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_one8v,     UINT32,\
                    "fatimavme_qdc3_sample_one8v",     "fatimavme_qdc3_sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two1,      UINT32,\
                    "fatimavme_qdc3_sample_two1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two1I,     UINT32,\
                    "fatimavme_qdc3_sample_two1I",     "fatimavme_qdc3_sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two1v,     UINT32,\
                    "fatimavme_qdc3_sample_two1v",     "fatimavme_qdc3_sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two2,      UINT32,\
                    "fatimavme_qdc3_sample_two2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two2I,     UINT32,\
                    "fatimavme_qdc3_sample_two2I",     "fatimavme_qdc3_sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two2v,     UINT32,\
                    "fatimavme_qdc3_sample_two2v",     "fatimavme_qdc3_sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two3,      UINT32,\
                    "fatimavme_qdc3_sample_two3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two3I,     UINT32,\
                    "fatimavme_qdc3_sample_two3I",     "fatimavme_qdc3_sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two3v,     UINT32,\
                    "fatimavme_qdc3_sample_two3v",     "fatimavme_qdc3_sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two4,      UINT32,\
                    "fatimavme_qdc3_sample_two4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two4I,     UINT32,\
                    "fatimavme_qdc3_sample_two4I",     "fatimavme_qdc3_sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two4v,     UINT32,\
                    "fatimavme_qdc3_sample_two4v",     "fatimavme_qdc3_sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two5,      UINT32,\
                    "fatimavme_qdc3_sample_two5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two5I,     UINT32,\
                    "fatimavme_qdc3_sample_two5I",     "fatimavme_qdc3_sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two5v,     UINT32,\
                    "fatimavme_qdc3_sample_two5v",     "fatimavme_qdc3_sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two6,      UINT32,\
                    "fatimavme_qdc3_sample_two6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two6I,     UINT32,\
                    "fatimavme_qdc3_sample_two6I",     "fatimavme_qdc3_sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two6v,     UINT32,\
                    "fatimavme_qdc3_sample_two6v",     "fatimavme_qdc3_sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two7,      UINT32,\
                    "fatimavme_qdc3_sample_two7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two7I,     UINT32,\
                    "fatimavme_qdc3_sample_two7I",     "fatimavme_qdc3_sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two7v,     UINT32,\
                    "fatimavme_qdc3_sample_two7v",     "fatimavme_qdc3_sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two8,      UINT32,\
                    "fatimavme_qdc3_sample_two8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two8I,     UINT32,\
                    "fatimavme_qdc3_sample_two8I",     "fatimavme_qdc3_sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_two8v,     UINT32,\
                    "fatimavme_qdc3_sample_two8v",     "fatimavme_qdc3_sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three1,    UINT32,\
                    "fatimavme_qdc3_sample_three1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three1I,   UINT32,\
                    "fatimavme_qdc3_sample_three1I",   "fatimavme_qdc3_sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three1v,   UINT32,\
                    "fatimavme_qdc3_sample_three1v",   "fatimavme_qdc3_sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three2,    UINT32,\
                    "fatimavme_qdc3_sample_three2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three2I,   UINT32,\
                    "fatimavme_qdc3_sample_three2I",   "fatimavme_qdc3_sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three2v,   UINT32,\
                    "fatimavme_qdc3_sample_three2v",   "fatimavme_qdc3_sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three3,    UINT32,\
                    "fatimavme_qdc3_sample_three3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three3I,   UINT32,\
                    "fatimavme_qdc3_sample_three3I",   "fatimavme_qdc3_sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three3v,   UINT32,\
                    "fatimavme_qdc3_sample_three3v",   "fatimavme_qdc3_sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three4,    UINT32,\
                    "fatimavme_qdc3_sample_three4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three4I,   UINT32,\
                    "fatimavme_qdc3_sample_three4I",   "fatimavme_qdc3_sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three4v,   UINT32,\
                    "fatimavme_qdc3_sample_three4v",   "fatimavme_qdc3_sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three5,    UINT32,\
                    "fatimavme_qdc3_sample_three5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three5I,   UINT32,\
                    "fatimavme_qdc3_sample_three5I",   "fatimavme_qdc3_sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three5v,   UINT32,\
                    "fatimavme_qdc3_sample_three5v",   "fatimavme_qdc3_sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three6,    UINT32,\
                    "fatimavme_qdc3_sample_three6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three6I,   UINT32,\
                    "fatimavme_qdc3_sample_three6I",   "fatimavme_qdc3_sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three6v,   UINT32,\
                    "fatimavme_qdc3_sample_three6v",   "fatimavme_qdc3_sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three7,    UINT32,\
                    "fatimavme_qdc3_sample_three7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three7I,   UINT32,\
                    "fatimavme_qdc3_sample_three7I",   "fatimavme_qdc3_sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three7v,   UINT32,\
                    "fatimavme_qdc3_sample_three7v",   "fatimavme_qdc3_sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three8,    UINT32,\
                    "fatimavme_qdc3_sample_three8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three8I,   UINT32,\
                    "fatimavme_qdc3_sample_three8I",   "fatimavme_qdc3_sample_three8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc3_sample_three8v,   UINT32,\
                    "fatimavme_qdc3_sample_three8v",   "fatimavme_qdc3_sample_three8",0/*flags*/); \
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
                     fatimavme_qdc4_extras,           UINT32,\
                    "fatimavme_qdc4_extras",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_dm,               UINT32,\
                    "fatimavme_qdc4_dm",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_chan_baseline,    UINT32,\
                    "fatimavme_qdc4_chan_baseline",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_chan_baselinev,   UINT32,\
                    "fatimavme_qdc4_chan_baselinev",   "fatimavme_qdc4_chan_baseline",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_chan_midscale,    UINT32,\
                    "fatimavme_qdc4_chan_midscale",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_chan_midscalev,   UINT32,\
                    "fatimavme_qdc4_chan_midscalev",   "fatimavme_qdc4_chan_midscale",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_chan_sazc,        UINT32,\
                    "fatimavme_qdc4_chan_sazc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_chan_sazcv,       UINT32,\
                    "fatimavme_qdc4_chan_sazcv",       "fatimavme_qdc4_chan_sazc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_chan_sbzc,        UINT32,\
                    "fatimavme_qdc4_chan_sbzc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_chan_sbzcv,       UINT32,\
                    "fatimavme_qdc4_chan_sbzcv",       "fatimavme_qdc4_chan_sbzc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one1,      UINT32,\
                    "fatimavme_qdc4_sample_one1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one1I,     UINT32,\
                    "fatimavme_qdc4_sample_one1I",     "fatimavme_qdc4_sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one1v,     UINT32,\
                    "fatimavme_qdc4_sample_one1v",     "fatimavme_qdc4_sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one2,      UINT32,\
                    "fatimavme_qdc4_sample_one2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one2I,     UINT32,\
                    "fatimavme_qdc4_sample_one2I",     "fatimavme_qdc4_sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one2v,     UINT32,\
                    "fatimavme_qdc4_sample_one2v",     "fatimavme_qdc4_sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one3,      UINT32,\
                    "fatimavme_qdc4_sample_one3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one3I,     UINT32,\
                    "fatimavme_qdc4_sample_one3I",     "fatimavme_qdc4_sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one3v,     UINT32,\
                    "fatimavme_qdc4_sample_one3v",     "fatimavme_qdc4_sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one4,      UINT32,\
                    "fatimavme_qdc4_sample_one4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one4I,     UINT32,\
                    "fatimavme_qdc4_sample_one4I",     "fatimavme_qdc4_sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one4v,     UINT32,\
                    "fatimavme_qdc4_sample_one4v",     "fatimavme_qdc4_sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one5,      UINT32,\
                    "fatimavme_qdc4_sample_one5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one5I,     UINT32,\
                    "fatimavme_qdc4_sample_one5I",     "fatimavme_qdc4_sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one5v,     UINT32,\
                    "fatimavme_qdc4_sample_one5v",     "fatimavme_qdc4_sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one6,      UINT32,\
                    "fatimavme_qdc4_sample_one6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one6I,     UINT32,\
                    "fatimavme_qdc4_sample_one6I",     "fatimavme_qdc4_sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one6v,     UINT32,\
                    "fatimavme_qdc4_sample_one6v",     "fatimavme_qdc4_sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one7,      UINT32,\
                    "fatimavme_qdc4_sample_one7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one7I,     UINT32,\
                    "fatimavme_qdc4_sample_one7I",     "fatimavme_qdc4_sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one7v,     UINT32,\
                    "fatimavme_qdc4_sample_one7v",     "fatimavme_qdc4_sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one8,      UINT32,\
                    "fatimavme_qdc4_sample_one8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one8I,     UINT32,\
                    "fatimavme_qdc4_sample_one8I",     "fatimavme_qdc4_sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_one8v,     UINT32,\
                    "fatimavme_qdc4_sample_one8v",     "fatimavme_qdc4_sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two1,      UINT32,\
                    "fatimavme_qdc4_sample_two1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two1I,     UINT32,\
                    "fatimavme_qdc4_sample_two1I",     "fatimavme_qdc4_sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two1v,     UINT32,\
                    "fatimavme_qdc4_sample_two1v",     "fatimavme_qdc4_sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two2,      UINT32,\
                    "fatimavme_qdc4_sample_two2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two2I,     UINT32,\
                    "fatimavme_qdc4_sample_two2I",     "fatimavme_qdc4_sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two2v,     UINT32,\
                    "fatimavme_qdc4_sample_two2v",     "fatimavme_qdc4_sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two3,      UINT32,\
                    "fatimavme_qdc4_sample_two3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two3I,     UINT32,\
                    "fatimavme_qdc4_sample_two3I",     "fatimavme_qdc4_sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two3v,     UINT32,\
                    "fatimavme_qdc4_sample_two3v",     "fatimavme_qdc4_sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two4,      UINT32,\
                    "fatimavme_qdc4_sample_two4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two4I,     UINT32,\
                    "fatimavme_qdc4_sample_two4I",     "fatimavme_qdc4_sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two4v,     UINT32,\
                    "fatimavme_qdc4_sample_two4v",     "fatimavme_qdc4_sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two5,      UINT32,\
                    "fatimavme_qdc4_sample_two5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two5I,     UINT32,\
                    "fatimavme_qdc4_sample_two5I",     "fatimavme_qdc4_sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two5v,     UINT32,\
                    "fatimavme_qdc4_sample_two5v",     "fatimavme_qdc4_sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two6,      UINT32,\
                    "fatimavme_qdc4_sample_two6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two6I,     UINT32,\
                    "fatimavme_qdc4_sample_two6I",     "fatimavme_qdc4_sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two6v,     UINT32,\
                    "fatimavme_qdc4_sample_two6v",     "fatimavme_qdc4_sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two7,      UINT32,\
                    "fatimavme_qdc4_sample_two7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two7I,     UINT32,\
                    "fatimavme_qdc4_sample_two7I",     "fatimavme_qdc4_sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two7v,     UINT32,\
                    "fatimavme_qdc4_sample_two7v",     "fatimavme_qdc4_sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two8,      UINT32,\
                    "fatimavme_qdc4_sample_two8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two8I,     UINT32,\
                    "fatimavme_qdc4_sample_two8I",     "fatimavme_qdc4_sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_two8v,     UINT32,\
                    "fatimavme_qdc4_sample_two8v",     "fatimavme_qdc4_sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three1,    UINT32,\
                    "fatimavme_qdc4_sample_three1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three1I,   UINT32,\
                    "fatimavme_qdc4_sample_three1I",   "fatimavme_qdc4_sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three1v,   UINT32,\
                    "fatimavme_qdc4_sample_three1v",   "fatimavme_qdc4_sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three2,    UINT32,\
                    "fatimavme_qdc4_sample_three2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three2I,   UINT32,\
                    "fatimavme_qdc4_sample_three2I",   "fatimavme_qdc4_sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three2v,   UINT32,\
                    "fatimavme_qdc4_sample_three2v",   "fatimavme_qdc4_sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three3,    UINT32,\
                    "fatimavme_qdc4_sample_three3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three3I,   UINT32,\
                    "fatimavme_qdc4_sample_three3I",   "fatimavme_qdc4_sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three3v,   UINT32,\
                    "fatimavme_qdc4_sample_three3v",   "fatimavme_qdc4_sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three4,    UINT32,\
                    "fatimavme_qdc4_sample_three4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three4I,   UINT32,\
                    "fatimavme_qdc4_sample_three4I",   "fatimavme_qdc4_sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three4v,   UINT32,\
                    "fatimavme_qdc4_sample_three4v",   "fatimavme_qdc4_sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three5,    UINT32,\
                    "fatimavme_qdc4_sample_three5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three5I,   UINT32,\
                    "fatimavme_qdc4_sample_three5I",   "fatimavme_qdc4_sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three5v,   UINT32,\
                    "fatimavme_qdc4_sample_three5v",   "fatimavme_qdc4_sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three6,    UINT32,\
                    "fatimavme_qdc4_sample_three6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three6I,   UINT32,\
                    "fatimavme_qdc4_sample_three6I",   "fatimavme_qdc4_sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three6v,   UINT32,\
                    "fatimavme_qdc4_sample_three6v",   "fatimavme_qdc4_sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three7,    UINT32,\
                    "fatimavme_qdc4_sample_three7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three7I,   UINT32,\
                    "fatimavme_qdc4_sample_three7I",   "fatimavme_qdc4_sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three7v,   UINT32,\
                    "fatimavme_qdc4_sample_three7v",   "fatimavme_qdc4_sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three8,    UINT32,\
                    "fatimavme_qdc4_sample_three8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three8I,   UINT32,\
                    "fatimavme_qdc4_sample_three8I",   "fatimavme_qdc4_sample_three8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc4_sample_three8v,   UINT32,\
                    "fatimavme_qdc4_sample_three8v",   "fatimavme_qdc4_sample_three8",0/*flags*/); \
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
                     fatimavme_qdc5_extras,           UINT32,\
                    "fatimavme_qdc5_extras",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_dm,               UINT32,\
                    "fatimavme_qdc5_dm",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_chan_baseline,    UINT32,\
                    "fatimavme_qdc5_chan_baseline",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_chan_baselinev,   UINT32,\
                    "fatimavme_qdc5_chan_baselinev",   "fatimavme_qdc5_chan_baseline",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_chan_midscale,    UINT32,\
                    "fatimavme_qdc5_chan_midscale",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_chan_midscalev,   UINT32,\
                    "fatimavme_qdc5_chan_midscalev",   "fatimavme_qdc5_chan_midscale",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_chan_sazc,        UINT32,\
                    "fatimavme_qdc5_chan_sazc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_chan_sazcv,       UINT32,\
                    "fatimavme_qdc5_chan_sazcv",       "fatimavme_qdc5_chan_sazc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_chan_sbzc,        UINT32,\
                    "fatimavme_qdc5_chan_sbzc",64,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_chan_sbzcv,       UINT32,\
                    "fatimavme_qdc5_chan_sbzcv",       "fatimavme_qdc5_chan_sbzc",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one1,      UINT32,\
                    "fatimavme_qdc5_sample_one1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one1I,     UINT32,\
                    "fatimavme_qdc5_sample_one1I",     "fatimavme_qdc5_sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one1v,     UINT32,\
                    "fatimavme_qdc5_sample_one1v",     "fatimavme_qdc5_sample_one1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one2,      UINT32,\
                    "fatimavme_qdc5_sample_one2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one2I,     UINT32,\
                    "fatimavme_qdc5_sample_one2I",     "fatimavme_qdc5_sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one2v,     UINT32,\
                    "fatimavme_qdc5_sample_one2v",     "fatimavme_qdc5_sample_one2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one3,      UINT32,\
                    "fatimavme_qdc5_sample_one3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one3I,     UINT32,\
                    "fatimavme_qdc5_sample_one3I",     "fatimavme_qdc5_sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one3v,     UINT32,\
                    "fatimavme_qdc5_sample_one3v",     "fatimavme_qdc5_sample_one3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one4,      UINT32,\
                    "fatimavme_qdc5_sample_one4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one4I,     UINT32,\
                    "fatimavme_qdc5_sample_one4I",     "fatimavme_qdc5_sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one4v,     UINT32,\
                    "fatimavme_qdc5_sample_one4v",     "fatimavme_qdc5_sample_one4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one5,      UINT32,\
                    "fatimavme_qdc5_sample_one5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one5I,     UINT32,\
                    "fatimavme_qdc5_sample_one5I",     "fatimavme_qdc5_sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one5v,     UINT32,\
                    "fatimavme_qdc5_sample_one5v",     "fatimavme_qdc5_sample_one5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one6,      UINT32,\
                    "fatimavme_qdc5_sample_one6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one6I,     UINT32,\
                    "fatimavme_qdc5_sample_one6I",     "fatimavme_qdc5_sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one6v,     UINT32,\
                    "fatimavme_qdc5_sample_one6v",     "fatimavme_qdc5_sample_one6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one7,      UINT32,\
                    "fatimavme_qdc5_sample_one7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one7I,     UINT32,\
                    "fatimavme_qdc5_sample_one7I",     "fatimavme_qdc5_sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one7v,     UINT32,\
                    "fatimavme_qdc5_sample_one7v",     "fatimavme_qdc5_sample_one7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one8,      UINT32,\
                    "fatimavme_qdc5_sample_one8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one8I,     UINT32,\
                    "fatimavme_qdc5_sample_one8I",     "fatimavme_qdc5_sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_one8v,     UINT32,\
                    "fatimavme_qdc5_sample_one8v",     "fatimavme_qdc5_sample_one8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two1,      UINT32,\
                    "fatimavme_qdc5_sample_two1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two1I,     UINT32,\
                    "fatimavme_qdc5_sample_two1I",     "fatimavme_qdc5_sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two1v,     UINT32,\
                    "fatimavme_qdc5_sample_two1v",     "fatimavme_qdc5_sample_two1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two2,      UINT32,\
                    "fatimavme_qdc5_sample_two2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two2I,     UINT32,\
                    "fatimavme_qdc5_sample_two2I",     "fatimavme_qdc5_sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two2v,     UINT32,\
                    "fatimavme_qdc5_sample_two2v",     "fatimavme_qdc5_sample_two2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two3,      UINT32,\
                    "fatimavme_qdc5_sample_two3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two3I,     UINT32,\
                    "fatimavme_qdc5_sample_two3I",     "fatimavme_qdc5_sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two3v,     UINT32,\
                    "fatimavme_qdc5_sample_two3v",     "fatimavme_qdc5_sample_two3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two4,      UINT32,\
                    "fatimavme_qdc5_sample_two4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two4I,     UINT32,\
                    "fatimavme_qdc5_sample_two4I",     "fatimavme_qdc5_sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two4v,     UINT32,\
                    "fatimavme_qdc5_sample_two4v",     "fatimavme_qdc5_sample_two4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two5,      UINT32,\
                    "fatimavme_qdc5_sample_two5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two5I,     UINT32,\
                    "fatimavme_qdc5_sample_two5I",     "fatimavme_qdc5_sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two5v,     UINT32,\
                    "fatimavme_qdc5_sample_two5v",     "fatimavme_qdc5_sample_two5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two6,      UINT32,\
                    "fatimavme_qdc5_sample_two6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two6I,     UINT32,\
                    "fatimavme_qdc5_sample_two6I",     "fatimavme_qdc5_sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two6v,     UINT32,\
                    "fatimavme_qdc5_sample_two6v",     "fatimavme_qdc5_sample_two6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two7,      UINT32,\
                    "fatimavme_qdc5_sample_two7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two7I,     UINT32,\
                    "fatimavme_qdc5_sample_two7I",     "fatimavme_qdc5_sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two7v,     UINT32,\
                    "fatimavme_qdc5_sample_two7v",     "fatimavme_qdc5_sample_two7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two8,      UINT32,\
                    "fatimavme_qdc5_sample_two8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two8I,     UINT32,\
                    "fatimavme_qdc5_sample_two8I",     "fatimavme_qdc5_sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_two8v,     UINT32,\
                    "fatimavme_qdc5_sample_two8v",     "fatimavme_qdc5_sample_two8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three1,    UINT32,\
                    "fatimavme_qdc5_sample_three1",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three1I,   UINT32,\
                    "fatimavme_qdc5_sample_three1I",   "fatimavme_qdc5_sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three1v,   UINT32,\
                    "fatimavme_qdc5_sample_three1v",   "fatimavme_qdc5_sample_three1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three2,    UINT32,\
                    "fatimavme_qdc5_sample_three2",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three2I,   UINT32,\
                    "fatimavme_qdc5_sample_three2I",   "fatimavme_qdc5_sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three2v,   UINT32,\
                    "fatimavme_qdc5_sample_three2v",   "fatimavme_qdc5_sample_three2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three3,    UINT32,\
                    "fatimavme_qdc5_sample_three3",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three3I,   UINT32,\
                    "fatimavme_qdc5_sample_three3I",   "fatimavme_qdc5_sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three3v,   UINT32,\
                    "fatimavme_qdc5_sample_three3v",   "fatimavme_qdc5_sample_three3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three4,    UINT32,\
                    "fatimavme_qdc5_sample_three4",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three4I,   UINT32,\
                    "fatimavme_qdc5_sample_three4I",   "fatimavme_qdc5_sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three4v,   UINT32,\
                    "fatimavme_qdc5_sample_three4v",   "fatimavme_qdc5_sample_three4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three5,    UINT32,\
                    "fatimavme_qdc5_sample_three5",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three5I,   UINT32,\
                    "fatimavme_qdc5_sample_three5I",   "fatimavme_qdc5_sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three5v,   UINT32,\
                    "fatimavme_qdc5_sample_three5v",   "fatimavme_qdc5_sample_three5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three6,    UINT32,\
                    "fatimavme_qdc5_sample_three6",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three6I,   UINT32,\
                    "fatimavme_qdc5_sample_three6I",   "fatimavme_qdc5_sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three6v,   UINT32,\
                    "fatimavme_qdc5_sample_three6v",   "fatimavme_qdc5_sample_three6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three7,    UINT32,\
                    "fatimavme_qdc5_sample_three7",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three7I,   UINT32,\
                    "fatimavme_qdc5_sample_three7I",   "fatimavme_qdc5_sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three7v,   UINT32,\
                    "fatimavme_qdc5_sample_three7v",   "fatimavme_qdc5_sample_three7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three8,    UINT32,\
                    "fatimavme_qdc5_sample_three8",224,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three8I,   UINT32,\
                    "fatimavme_qdc5_sample_three8I",   "fatimavme_qdc5_sample_three8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     fatimavme_qdc5_sample_three8v,   UINT32,\
                    "fatimavme_qdc5_sample_three8v",   "fatimavme_qdc5_sample_three8",0/*flags*/); \
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
  \
} while (0);

#endif/*__GUARD_H101_FATIMAVME_EXT_H101_FATIMAVME_H__*/

/*******************************************************/
