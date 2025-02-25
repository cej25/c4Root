/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_BBFEBEX_EXT_H101_BBFEBEX_H__
#define __GUARD_H101_BBFEBEX_EXT_H101_BBFEBEX_H__

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

typedef struct EXT_STR_h101_bbfebex_t
{
  /* UNPACK */
  uint32_t bbfirst_ts_subsystem_id /* [0,65535] */;
  uint32_t bbfirst_ts_t1 /* [0,65535] */;
  uint32_t bbfirst_ts_t2 /* [0,65535] */;
  uint32_t bbfirst_ts_t3 /* [0,65535] */;
  uint32_t bbfirst_ts_t4 /* [0,65535] */;
  uint32_t bbfirst_data1trig /* [0,255] */;
  uint32_t bbfirst_data1event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbfirst_data1event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbfirst_data1hit_pattern /* [0,65535] */;
  uint32_t bbfirst_data1num_channels_fired /* [-1,-1] */;
  uint32_t bbfirst_data1board_num /* [0,255] */;
  uint32_t bbfirst_data1channel_id /* [0,16] */;
  uint32_t bbfirst_data1channel_idI[16 EXT_STRUCT_CTRL(bbfirst_data1channel_id)] /* [1,16] */;
  uint32_t bbfirst_data1channel_idv[16 EXT_STRUCT_CTRL(bbfirst_data1channel_id)] /* [0,255] */;
  uint32_t bbfirst_data1channel_trigger_time_hi /* [0,16] */;
  uint32_t bbfirst_data1channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbfirst_data1channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbfirst_data1channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbfirst_data1channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbfirst_data1channel_trigger_time_lo /* [0,16] */;
  uint32_t bbfirst_data1channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbfirst_data1channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbfirst_data1channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbfirst_data1channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbfirst_data1pileup /* [0,16] */;
  uint32_t bbfirst_data1pileupI[16 EXT_STRUCT_CTRL(bbfirst_data1pileup)] /* [1,16] */;
  uint32_t bbfirst_data1pileupv[16 EXT_STRUCT_CTRL(bbfirst_data1pileup)] /* [0,255] */;
  uint32_t bbfirst_data1overflow /* [0,16] */;
  uint32_t bbfirst_data1overflowI[16 EXT_STRUCT_CTRL(bbfirst_data1overflow)] /* [1,16] */;
  uint32_t bbfirst_data1overflowv[16 EXT_STRUCT_CTRL(bbfirst_data1overflow)] /* [0,255] */;
  uint32_t bbfirst_data1channel_cfd /* [0,16] */;
  uint32_t bbfirst_data1channel_cfdI[16 EXT_STRUCT_CTRL(bbfirst_data1channel_cfd)] /* [1,16] */;
  uint32_t bbfirst_data1channel_cfdv[16 EXT_STRUCT_CTRL(bbfirst_data1channel_cfd)] /* [0,255] */;
  uint32_t bbfirst_data1channel_energy /* [0,16] */;
  uint32_t bbfirst_data1channel_energyI[16 EXT_STRUCT_CTRL(bbfirst_data1channel_energy)] /* [1,16] */;
  uint32_t bbfirst_data1channel_energyv[16 EXT_STRUCT_CTRL(bbfirst_data1channel_energy)] /* [-1,-1] */;
  uint32_t bbfirst_data1trace_traces1 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces1I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces1)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces1v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces1)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces2 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces2I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces2)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces2v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces2)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces3 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces3I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces3)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces3v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces3)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces4 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces4I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces4)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces4v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces4)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces5 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces5I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces5)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces5v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces5)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces6 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces6I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces6)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces6v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces6)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces7 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces7I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces7)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces7v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces7)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces8 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces8I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces8)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces8v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces8)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces9 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces9I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces9)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces9v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces9)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces10 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces10I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces10)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces10v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces10)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces11 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces11I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces11)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces11v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces11)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces12 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces12I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces12)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces12v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces12)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces13 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces13I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces13)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces13v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces13)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces14 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces14I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces14)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces14v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces14)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces15 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces15I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces15)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces15v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces15)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_traces16 /* [0,4000] */;
  uint32_t bbfirst_data1trace_traces16I[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces16)] /* [1,4000] */;
  uint32_t bbfirst_data1trace_traces16v[4000 EXT_STRUCT_CTRL(bbfirst_data1trace_traces16)] /* [0,65535] */;
  uint32_t bbfirst_data1trace_channel_id_traces /* [0,16] */;
  uint32_t bbfirst_data1trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbfirst_data1trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbfirst_data1trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbfirst_data1trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbfirst_data2trig /* [0,255] */;
  uint32_t bbfirst_data2event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbfirst_data2event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbfirst_data2hit_pattern /* [0,65535] */;
  uint32_t bbfirst_data2num_channels_fired /* [-1,-1] */;
  uint32_t bbfirst_data2board_num /* [0,255] */;
  uint32_t bbfirst_data2channel_id /* [0,16] */;
  uint32_t bbfirst_data2channel_idI[16 EXT_STRUCT_CTRL(bbfirst_data2channel_id)] /* [1,16] */;
  uint32_t bbfirst_data2channel_idv[16 EXT_STRUCT_CTRL(bbfirst_data2channel_id)] /* [0,255] */;
  uint32_t bbfirst_data2channel_trigger_time_hi /* [0,16] */;
  uint32_t bbfirst_data2channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbfirst_data2channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbfirst_data2channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbfirst_data2channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbfirst_data2channel_trigger_time_lo /* [0,16] */;
  uint32_t bbfirst_data2channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbfirst_data2channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbfirst_data2channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbfirst_data2channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbfirst_data2pileup /* [0,16] */;
  uint32_t bbfirst_data2pileupI[16 EXT_STRUCT_CTRL(bbfirst_data2pileup)] /* [1,16] */;
  uint32_t bbfirst_data2pileupv[16 EXT_STRUCT_CTRL(bbfirst_data2pileup)] /* [0,255] */;
  uint32_t bbfirst_data2overflow /* [0,16] */;
  uint32_t bbfirst_data2overflowI[16 EXT_STRUCT_CTRL(bbfirst_data2overflow)] /* [1,16] */;
  uint32_t bbfirst_data2overflowv[16 EXT_STRUCT_CTRL(bbfirst_data2overflow)] /* [0,255] */;
  uint32_t bbfirst_data2channel_cfd /* [0,16] */;
  uint32_t bbfirst_data2channel_cfdI[16 EXT_STRUCT_CTRL(bbfirst_data2channel_cfd)] /* [1,16] */;
  uint32_t bbfirst_data2channel_cfdv[16 EXT_STRUCT_CTRL(bbfirst_data2channel_cfd)] /* [0,255] */;
  uint32_t bbfirst_data2channel_energy /* [0,16] */;
  uint32_t bbfirst_data2channel_energyI[16 EXT_STRUCT_CTRL(bbfirst_data2channel_energy)] /* [1,16] */;
  uint32_t bbfirst_data2channel_energyv[16 EXT_STRUCT_CTRL(bbfirst_data2channel_energy)] /* [-1,-1] */;
  uint32_t bbfirst_data2trace_traces1 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces1I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces1)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces1v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces1)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces2 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces2I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces2)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces2v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces2)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces3 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces3I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces3)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces3v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces3)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces4 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces4I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces4)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces4v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces4)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces5 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces5I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces5)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces5v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces5)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces6 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces6I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces6)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces6v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces6)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces7 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces7I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces7)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces7v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces7)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces8 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces8I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces8)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces8v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces8)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces9 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces9I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces9)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces9v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces9)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces10 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces10I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces10)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces10v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces10)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces11 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces11I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces11)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces11v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces11)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces12 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces12I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces12)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces12v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces12)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces13 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces13I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces13)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces13v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces13)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces14 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces14I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces14)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces14v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces14)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces15 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces15I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces15)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces15v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces15)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_traces16 /* [0,4000] */;
  uint32_t bbfirst_data2trace_traces16I[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces16)] /* [1,4000] */;
  uint32_t bbfirst_data2trace_traces16v[4000 EXT_STRUCT_CTRL(bbfirst_data2trace_traces16)] /* [0,65535] */;
  uint32_t bbfirst_data2trace_channel_id_traces /* [0,16] */;
  uint32_t bbfirst_data2trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbfirst_data2trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbfirst_data2trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbfirst_data2trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbfirst_data3trig /* [0,255] */;
  uint32_t bbfirst_data3event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbfirst_data3event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbfirst_data3hit_pattern /* [0,65535] */;
  uint32_t bbfirst_data3num_channels_fired /* [-1,-1] */;
  uint32_t bbfirst_data3board_num /* [0,255] */;
  uint32_t bbfirst_data3channel_id /* [0,16] */;
  uint32_t bbfirst_data3channel_idI[16 EXT_STRUCT_CTRL(bbfirst_data3channel_id)] /* [1,16] */;
  uint32_t bbfirst_data3channel_idv[16 EXT_STRUCT_CTRL(bbfirst_data3channel_id)] /* [0,255] */;
  uint32_t bbfirst_data3channel_trigger_time_hi /* [0,16] */;
  uint32_t bbfirst_data3channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbfirst_data3channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbfirst_data3channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbfirst_data3channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbfirst_data3channel_trigger_time_lo /* [0,16] */;
  uint32_t bbfirst_data3channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbfirst_data3channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbfirst_data3channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbfirst_data3channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbfirst_data3pileup /* [0,16] */;
  uint32_t bbfirst_data3pileupI[16 EXT_STRUCT_CTRL(bbfirst_data3pileup)] /* [1,16] */;
  uint32_t bbfirst_data3pileupv[16 EXT_STRUCT_CTRL(bbfirst_data3pileup)] /* [0,255] */;
  uint32_t bbfirst_data3overflow /* [0,16] */;
  uint32_t bbfirst_data3overflowI[16 EXT_STRUCT_CTRL(bbfirst_data3overflow)] /* [1,16] */;
  uint32_t bbfirst_data3overflowv[16 EXT_STRUCT_CTRL(bbfirst_data3overflow)] /* [0,255] */;
  uint32_t bbfirst_data3channel_cfd /* [0,16] */;
  uint32_t bbfirst_data3channel_cfdI[16 EXT_STRUCT_CTRL(bbfirst_data3channel_cfd)] /* [1,16] */;
  uint32_t bbfirst_data3channel_cfdv[16 EXT_STRUCT_CTRL(bbfirst_data3channel_cfd)] /* [0,255] */;
  uint32_t bbfirst_data3channel_energy /* [0,16] */;
  uint32_t bbfirst_data3channel_energyI[16 EXT_STRUCT_CTRL(bbfirst_data3channel_energy)] /* [1,16] */;
  uint32_t bbfirst_data3channel_energyv[16 EXT_STRUCT_CTRL(bbfirst_data3channel_energy)] /* [-1,-1] */;
  uint32_t bbfirst_data3trace_traces1 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces1I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces1)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces1v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces1)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces2 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces2I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces2)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces2v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces2)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces3 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces3I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces3)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces3v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces3)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces4 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces4I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces4)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces4v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces4)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces5 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces5I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces5)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces5v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces5)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces6 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces6I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces6)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces6v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces6)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces7 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces7I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces7)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces7v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces7)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces8 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces8I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces8)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces8v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces8)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces9 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces9I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces9)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces9v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces9)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces10 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces10I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces10)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces10v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces10)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces11 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces11I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces11)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces11v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces11)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces12 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces12I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces12)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces12v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces12)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces13 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces13I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces13)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces13v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces13)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces14 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces14I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces14)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces14v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces14)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces15 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces15I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces15)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces15v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces15)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_traces16 /* [0,4000] */;
  uint32_t bbfirst_data3trace_traces16I[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces16)] /* [1,4000] */;
  uint32_t bbfirst_data3trace_traces16v[4000 EXT_STRUCT_CTRL(bbfirst_data3trace_traces16)] /* [0,65535] */;
  uint32_t bbfirst_data3trace_channel_id_traces /* [0,16] */;
  uint32_t bbfirst_data3trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbfirst_data3trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbfirst_data3trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbfirst_data3trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbfirst_data4trig /* [0,255] */;
  uint32_t bbfirst_data4event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbfirst_data4event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbfirst_data4hit_pattern /* [0,65535] */;
  uint32_t bbfirst_data4num_channels_fired /* [-1,-1] */;
  uint32_t bbfirst_data4board_num /* [0,255] */;
  uint32_t bbfirst_data4channel_id /* [0,16] */;
  uint32_t bbfirst_data4channel_idI[16 EXT_STRUCT_CTRL(bbfirst_data4channel_id)] /* [1,16] */;
  uint32_t bbfirst_data4channel_idv[16 EXT_STRUCT_CTRL(bbfirst_data4channel_id)] /* [0,255] */;
  uint32_t bbfirst_data4channel_trigger_time_hi /* [0,16] */;
  uint32_t bbfirst_data4channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbfirst_data4channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbfirst_data4channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbfirst_data4channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbfirst_data4channel_trigger_time_lo /* [0,16] */;
  uint32_t bbfirst_data4channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbfirst_data4channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbfirst_data4channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbfirst_data4channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbfirst_data4pileup /* [0,16] */;
  uint32_t bbfirst_data4pileupI[16 EXT_STRUCT_CTRL(bbfirst_data4pileup)] /* [1,16] */;
  uint32_t bbfirst_data4pileupv[16 EXT_STRUCT_CTRL(bbfirst_data4pileup)] /* [0,255] */;
  uint32_t bbfirst_data4overflow /* [0,16] */;
  uint32_t bbfirst_data4overflowI[16 EXT_STRUCT_CTRL(bbfirst_data4overflow)] /* [1,16] */;
  uint32_t bbfirst_data4overflowv[16 EXT_STRUCT_CTRL(bbfirst_data4overflow)] /* [0,255] */;
  uint32_t bbfirst_data4channel_cfd /* [0,16] */;
  uint32_t bbfirst_data4channel_cfdI[16 EXT_STRUCT_CTRL(bbfirst_data4channel_cfd)] /* [1,16] */;
  uint32_t bbfirst_data4channel_cfdv[16 EXT_STRUCT_CTRL(bbfirst_data4channel_cfd)] /* [0,255] */;
  uint32_t bbfirst_data4channel_energy /* [0,16] */;
  uint32_t bbfirst_data4channel_energyI[16 EXT_STRUCT_CTRL(bbfirst_data4channel_energy)] /* [1,16] */;
  uint32_t bbfirst_data4channel_energyv[16 EXT_STRUCT_CTRL(bbfirst_data4channel_energy)] /* [-1,-1] */;
  uint32_t bbfirst_data4trace_traces1 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces1I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces1)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces1v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces1)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces2 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces2I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces2)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces2v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces2)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces3 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces3I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces3)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces3v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces3)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces4 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces4I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces4)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces4v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces4)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces5 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces5I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces5)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces5v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces5)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces6 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces6I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces6)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces6v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces6)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces7 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces7I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces7)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces7v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces7)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces8 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces8I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces8)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces8v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces8)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces9 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces9I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces9)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces9v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces9)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces10 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces10I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces10)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces10v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces10)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces11 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces11I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces11)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces11v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces11)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces12 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces12I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces12)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces12v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces12)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces13 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces13I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces13)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces13v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces13)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces14 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces14I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces14)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces14v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces14)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces15 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces15I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces15)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces15v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces15)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_traces16 /* [0,4000] */;
  uint32_t bbfirst_data4trace_traces16I[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces16)] /* [1,4000] */;
  uint32_t bbfirst_data4trace_traces16v[4000 EXT_STRUCT_CTRL(bbfirst_data4trace_traces16)] /* [0,65535] */;
  uint32_t bbfirst_data4trace_channel_id_traces /* [0,16] */;
  uint32_t bbfirst_data4trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbfirst_data4trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbfirst_data4trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbfirst_data4trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbfirst_data5trig /* [0,255] */;
  uint32_t bbfirst_data5event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbfirst_data5event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbfirst_data5hit_pattern /* [0,65535] */;
  uint32_t bbfirst_data5num_channels_fired /* [-1,-1] */;
  uint32_t bbfirst_data5board_num /* [0,255] */;
  uint32_t bbfirst_data5channel_id /* [0,16] */;
  uint32_t bbfirst_data5channel_idI[16 EXT_STRUCT_CTRL(bbfirst_data5channel_id)] /* [1,16] */;
  uint32_t bbfirst_data5channel_idv[16 EXT_STRUCT_CTRL(bbfirst_data5channel_id)] /* [0,255] */;
  uint32_t bbfirst_data5channel_trigger_time_hi /* [0,16] */;
  uint32_t bbfirst_data5channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbfirst_data5channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbfirst_data5channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbfirst_data5channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbfirst_data5channel_trigger_time_lo /* [0,16] */;
  uint32_t bbfirst_data5channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbfirst_data5channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbfirst_data5channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbfirst_data5channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbfirst_data5pileup /* [0,16] */;
  uint32_t bbfirst_data5pileupI[16 EXT_STRUCT_CTRL(bbfirst_data5pileup)] /* [1,16] */;
  uint32_t bbfirst_data5pileupv[16 EXT_STRUCT_CTRL(bbfirst_data5pileup)] /* [0,255] */;
  uint32_t bbfirst_data5overflow /* [0,16] */;
  uint32_t bbfirst_data5overflowI[16 EXT_STRUCT_CTRL(bbfirst_data5overflow)] /* [1,16] */;
  uint32_t bbfirst_data5overflowv[16 EXT_STRUCT_CTRL(bbfirst_data5overflow)] /* [0,255] */;
  uint32_t bbfirst_data5channel_cfd /* [0,16] */;
  uint32_t bbfirst_data5channel_cfdI[16 EXT_STRUCT_CTRL(bbfirst_data5channel_cfd)] /* [1,16] */;
  uint32_t bbfirst_data5channel_cfdv[16 EXT_STRUCT_CTRL(bbfirst_data5channel_cfd)] /* [0,255] */;
  uint32_t bbfirst_data5channel_energy /* [0,16] */;
  uint32_t bbfirst_data5channel_energyI[16 EXT_STRUCT_CTRL(bbfirst_data5channel_energy)] /* [1,16] */;
  uint32_t bbfirst_data5channel_energyv[16 EXT_STRUCT_CTRL(bbfirst_data5channel_energy)] /* [-1,-1] */;
  uint32_t bbfirst_data5trace_traces1 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces1I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces1)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces1v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces1)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces2 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces2I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces2)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces2v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces2)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces3 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces3I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces3)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces3v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces3)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces4 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces4I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces4)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces4v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces4)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces5 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces5I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces5)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces5v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces5)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces6 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces6I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces6)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces6v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces6)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces7 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces7I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces7)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces7v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces7)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces8 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces8I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces8)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces8v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces8)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces9 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces9I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces9)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces9v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces9)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces10 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces10I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces10)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces10v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces10)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces11 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces11I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces11)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces11v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces11)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces12 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces12I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces12)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces12v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces12)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces13 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces13I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces13)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces13v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces13)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces14 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces14I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces14)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces14v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces14)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces15 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces15I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces15)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces15v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces15)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_traces16 /* [0,4000] */;
  uint32_t bbfirst_data5trace_traces16I[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces16)] /* [1,4000] */;
  uint32_t bbfirst_data5trace_traces16v[4000 EXT_STRUCT_CTRL(bbfirst_data5trace_traces16)] /* [0,65535] */;
  uint32_t bbfirst_data5trace_channel_id_traces /* [0,16] */;
  uint32_t bbfirst_data5trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbfirst_data5trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbfirst_data5trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbfirst_data5trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbsecond_ts_subsystem_id /* [0,65535] */;
  uint32_t bbsecond_ts_t1 /* [0,65535] */;
  uint32_t bbsecond_ts_t2 /* [0,65535] */;
  uint32_t bbsecond_ts_t3 /* [0,65535] */;
  uint32_t bbsecond_ts_t4 /* [0,65535] */;
  uint32_t bbsecond_data1trig /* [0,255] */;
  uint32_t bbsecond_data1event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbsecond_data1event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbsecond_data1hit_pattern /* [0,65535] */;
  uint32_t bbsecond_data1num_channels_fired /* [-1,-1] */;
  uint32_t bbsecond_data1board_num /* [0,255] */;
  uint32_t bbsecond_data1channel_id /* [0,16] */;
  uint32_t bbsecond_data1channel_idI[16 EXT_STRUCT_CTRL(bbsecond_data1channel_id)] /* [1,16] */;
  uint32_t bbsecond_data1channel_idv[16 EXT_STRUCT_CTRL(bbsecond_data1channel_id)] /* [0,255] */;
  uint32_t bbsecond_data1channel_trigger_time_hi /* [0,16] */;
  uint32_t bbsecond_data1channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbsecond_data1channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbsecond_data1channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbsecond_data1channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbsecond_data1channel_trigger_time_lo /* [0,16] */;
  uint32_t bbsecond_data1channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbsecond_data1channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbsecond_data1channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbsecond_data1channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbsecond_data1pileup /* [0,16] */;
  uint32_t bbsecond_data1pileupI[16 EXT_STRUCT_CTRL(bbsecond_data1pileup)] /* [1,16] */;
  uint32_t bbsecond_data1pileupv[16 EXT_STRUCT_CTRL(bbsecond_data1pileup)] /* [0,255] */;
  uint32_t bbsecond_data1overflow /* [0,16] */;
  uint32_t bbsecond_data1overflowI[16 EXT_STRUCT_CTRL(bbsecond_data1overflow)] /* [1,16] */;
  uint32_t bbsecond_data1overflowv[16 EXT_STRUCT_CTRL(bbsecond_data1overflow)] /* [0,255] */;
  uint32_t bbsecond_data1channel_cfd /* [0,16] */;
  uint32_t bbsecond_data1channel_cfdI[16 EXT_STRUCT_CTRL(bbsecond_data1channel_cfd)] /* [1,16] */;
  uint32_t bbsecond_data1channel_cfdv[16 EXT_STRUCT_CTRL(bbsecond_data1channel_cfd)] /* [0,255] */;
  uint32_t bbsecond_data1channel_energy /* [0,16] */;
  uint32_t bbsecond_data1channel_energyI[16 EXT_STRUCT_CTRL(bbsecond_data1channel_energy)] /* [1,16] */;
  uint32_t bbsecond_data1channel_energyv[16 EXT_STRUCT_CTRL(bbsecond_data1channel_energy)] /* [-1,-1] */;
  uint32_t bbsecond_data1trace_traces1 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces1I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces1)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces1v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces1)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces2 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces2I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces2)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces2v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces2)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces3 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces3I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces3)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces3v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces3)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces4 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces4I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces4)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces4v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces4)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces5 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces5I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces5)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces5v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces5)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces6 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces6I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces6)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces6v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces6)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces7 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces7I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces7)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces7v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces7)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces8 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces8I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces8)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces8v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces8)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces9 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces9I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces9)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces9v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces9)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces10 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces10I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces10)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces10v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces10)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces11 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces11I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces11)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces11v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces11)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces12 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces12I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces12)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces12v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces12)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces13 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces13I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces13)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces13v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces13)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces14 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces14I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces14)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces14v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces14)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces15 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces15I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces15)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces15v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces15)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_traces16 /* [0,4000] */;
  uint32_t bbsecond_data1trace_traces16I[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces16)] /* [1,4000] */;
  uint32_t bbsecond_data1trace_traces16v[4000 EXT_STRUCT_CTRL(bbsecond_data1trace_traces16)] /* [0,65535] */;
  uint32_t bbsecond_data1trace_channel_id_traces /* [0,16] */;
  uint32_t bbsecond_data1trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbsecond_data1trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbsecond_data1trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbsecond_data1trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbsecond_data2trig /* [0,255] */;
  uint32_t bbsecond_data2event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbsecond_data2event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbsecond_data2hit_pattern /* [0,65535] */;
  uint32_t bbsecond_data2num_channels_fired /* [-1,-1] */;
  uint32_t bbsecond_data2board_num /* [0,255] */;
  uint32_t bbsecond_data2channel_id /* [0,16] */;
  uint32_t bbsecond_data2channel_idI[16 EXT_STRUCT_CTRL(bbsecond_data2channel_id)] /* [1,16] */;
  uint32_t bbsecond_data2channel_idv[16 EXT_STRUCT_CTRL(bbsecond_data2channel_id)] /* [0,255] */;
  uint32_t bbsecond_data2channel_trigger_time_hi /* [0,16] */;
  uint32_t bbsecond_data2channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbsecond_data2channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbsecond_data2channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbsecond_data2channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbsecond_data2channel_trigger_time_lo /* [0,16] */;
  uint32_t bbsecond_data2channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbsecond_data2channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbsecond_data2channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbsecond_data2channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbsecond_data2pileup /* [0,16] */;
  uint32_t bbsecond_data2pileupI[16 EXT_STRUCT_CTRL(bbsecond_data2pileup)] /* [1,16] */;
  uint32_t bbsecond_data2pileupv[16 EXT_STRUCT_CTRL(bbsecond_data2pileup)] /* [0,255] */;
  uint32_t bbsecond_data2overflow /* [0,16] */;
  uint32_t bbsecond_data2overflowI[16 EXT_STRUCT_CTRL(bbsecond_data2overflow)] /* [1,16] */;
  uint32_t bbsecond_data2overflowv[16 EXT_STRUCT_CTRL(bbsecond_data2overflow)] /* [0,255] */;
  uint32_t bbsecond_data2channel_cfd /* [0,16] */;
  uint32_t bbsecond_data2channel_cfdI[16 EXT_STRUCT_CTRL(bbsecond_data2channel_cfd)] /* [1,16] */;
  uint32_t bbsecond_data2channel_cfdv[16 EXT_STRUCT_CTRL(bbsecond_data2channel_cfd)] /* [0,255] */;
  uint32_t bbsecond_data2channel_energy /* [0,16] */;
  uint32_t bbsecond_data2channel_energyI[16 EXT_STRUCT_CTRL(bbsecond_data2channel_energy)] /* [1,16] */;
  uint32_t bbsecond_data2channel_energyv[16 EXT_STRUCT_CTRL(bbsecond_data2channel_energy)] /* [-1,-1] */;
  uint32_t bbsecond_data2trace_traces1 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces1I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces1)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces1v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces1)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces2 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces2I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces2)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces2v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces2)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces3 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces3I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces3)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces3v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces3)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces4 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces4I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces4)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces4v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces4)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces5 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces5I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces5)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces5v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces5)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces6 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces6I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces6)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces6v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces6)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces7 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces7I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces7)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces7v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces7)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces8 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces8I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces8)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces8v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces8)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces9 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces9I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces9)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces9v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces9)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces10 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces10I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces10)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces10v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces10)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces11 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces11I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces11)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces11v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces11)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces12 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces12I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces12)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces12v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces12)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces13 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces13I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces13)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces13v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces13)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces14 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces14I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces14)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces14v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces14)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces15 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces15I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces15)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces15v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces15)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_traces16 /* [0,4000] */;
  uint32_t bbsecond_data2trace_traces16I[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces16)] /* [1,4000] */;
  uint32_t bbsecond_data2trace_traces16v[4000 EXT_STRUCT_CTRL(bbsecond_data2trace_traces16)] /* [0,65535] */;
  uint32_t bbsecond_data2trace_channel_id_traces /* [0,16] */;
  uint32_t bbsecond_data2trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbsecond_data2trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbsecond_data2trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbsecond_data2trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbsecond_data3trig /* [0,255] */;
  uint32_t bbsecond_data3event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbsecond_data3event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbsecond_data3hit_pattern /* [0,65535] */;
  uint32_t bbsecond_data3num_channels_fired /* [-1,-1] */;
  uint32_t bbsecond_data3board_num /* [0,255] */;
  uint32_t bbsecond_data3channel_id /* [0,16] */;
  uint32_t bbsecond_data3channel_idI[16 EXT_STRUCT_CTRL(bbsecond_data3channel_id)] /* [1,16] */;
  uint32_t bbsecond_data3channel_idv[16 EXT_STRUCT_CTRL(bbsecond_data3channel_id)] /* [0,255] */;
  uint32_t bbsecond_data3channel_trigger_time_hi /* [0,16] */;
  uint32_t bbsecond_data3channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbsecond_data3channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbsecond_data3channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbsecond_data3channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbsecond_data3channel_trigger_time_lo /* [0,16] */;
  uint32_t bbsecond_data3channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbsecond_data3channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbsecond_data3channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbsecond_data3channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbsecond_data3pileup /* [0,16] */;
  uint32_t bbsecond_data3pileupI[16 EXT_STRUCT_CTRL(bbsecond_data3pileup)] /* [1,16] */;
  uint32_t bbsecond_data3pileupv[16 EXT_STRUCT_CTRL(bbsecond_data3pileup)] /* [0,255] */;
  uint32_t bbsecond_data3overflow /* [0,16] */;
  uint32_t bbsecond_data3overflowI[16 EXT_STRUCT_CTRL(bbsecond_data3overflow)] /* [1,16] */;
  uint32_t bbsecond_data3overflowv[16 EXT_STRUCT_CTRL(bbsecond_data3overflow)] /* [0,255] */;
  uint32_t bbsecond_data3channel_cfd /* [0,16] */;
  uint32_t bbsecond_data3channel_cfdI[16 EXT_STRUCT_CTRL(bbsecond_data3channel_cfd)] /* [1,16] */;
  uint32_t bbsecond_data3channel_cfdv[16 EXT_STRUCT_CTRL(bbsecond_data3channel_cfd)] /* [0,255] */;
  uint32_t bbsecond_data3channel_energy /* [0,16] */;
  uint32_t bbsecond_data3channel_energyI[16 EXT_STRUCT_CTRL(bbsecond_data3channel_energy)] /* [1,16] */;
  uint32_t bbsecond_data3channel_energyv[16 EXT_STRUCT_CTRL(bbsecond_data3channel_energy)] /* [-1,-1] */;
  uint32_t bbsecond_data3trace_traces1 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces1I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces1)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces1v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces1)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces2 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces2I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces2)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces2v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces2)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces3 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces3I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces3)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces3v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces3)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces4 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces4I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces4)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces4v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces4)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces5 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces5I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces5)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces5v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces5)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces6 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces6I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces6)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces6v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces6)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces7 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces7I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces7)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces7v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces7)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces8 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces8I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces8)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces8v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces8)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces9 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces9I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces9)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces9v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces9)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces10 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces10I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces10)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces10v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces10)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces11 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces11I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces11)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces11v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces11)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces12 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces12I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces12)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces12v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces12)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces13 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces13I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces13)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces13v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces13)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces14 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces14I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces14)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces14v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces14)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces15 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces15I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces15)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces15v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces15)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_traces16 /* [0,4000] */;
  uint32_t bbsecond_data3trace_traces16I[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces16)] /* [1,4000] */;
  uint32_t bbsecond_data3trace_traces16v[4000 EXT_STRUCT_CTRL(bbsecond_data3trace_traces16)] /* [0,65535] */;
  uint32_t bbsecond_data3trace_channel_id_traces /* [0,16] */;
  uint32_t bbsecond_data3trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbsecond_data3trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbsecond_data3trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbsecond_data3trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbsecond_data4trig /* [0,255] */;
  uint32_t bbsecond_data4event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbsecond_data4event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbsecond_data4hit_pattern /* [0,65535] */;
  uint32_t bbsecond_data4num_channels_fired /* [-1,-1] */;
  uint32_t bbsecond_data4board_num /* [0,255] */;
  uint32_t bbsecond_data4channel_id /* [0,16] */;
  uint32_t bbsecond_data4channel_idI[16 EXT_STRUCT_CTRL(bbsecond_data4channel_id)] /* [1,16] */;
  uint32_t bbsecond_data4channel_idv[16 EXT_STRUCT_CTRL(bbsecond_data4channel_id)] /* [0,255] */;
  uint32_t bbsecond_data4channel_trigger_time_hi /* [0,16] */;
  uint32_t bbsecond_data4channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbsecond_data4channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbsecond_data4channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbsecond_data4channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbsecond_data4channel_trigger_time_lo /* [0,16] */;
  uint32_t bbsecond_data4channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbsecond_data4channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbsecond_data4channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbsecond_data4channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbsecond_data4pileup /* [0,16] */;
  uint32_t bbsecond_data4pileupI[16 EXT_STRUCT_CTRL(bbsecond_data4pileup)] /* [1,16] */;
  uint32_t bbsecond_data4pileupv[16 EXT_STRUCT_CTRL(bbsecond_data4pileup)] /* [0,255] */;
  uint32_t bbsecond_data4overflow /* [0,16] */;
  uint32_t bbsecond_data4overflowI[16 EXT_STRUCT_CTRL(bbsecond_data4overflow)] /* [1,16] */;
  uint32_t bbsecond_data4overflowv[16 EXT_STRUCT_CTRL(bbsecond_data4overflow)] /* [0,255] */;
  uint32_t bbsecond_data4channel_cfd /* [0,16] */;
  uint32_t bbsecond_data4channel_cfdI[16 EXT_STRUCT_CTRL(bbsecond_data4channel_cfd)] /* [1,16] */;
  uint32_t bbsecond_data4channel_cfdv[16 EXT_STRUCT_CTRL(bbsecond_data4channel_cfd)] /* [0,255] */;
  uint32_t bbsecond_data4channel_energy /* [0,16] */;
  uint32_t bbsecond_data4channel_energyI[16 EXT_STRUCT_CTRL(bbsecond_data4channel_energy)] /* [1,16] */;
  uint32_t bbsecond_data4channel_energyv[16 EXT_STRUCT_CTRL(bbsecond_data4channel_energy)] /* [-1,-1] */;
  uint32_t bbsecond_data4trace_traces1 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces1I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces1)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces1v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces1)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces2 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces2I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces2)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces2v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces2)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces3 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces3I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces3)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces3v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces3)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces4 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces4I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces4)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces4v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces4)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces5 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces5I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces5)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces5v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces5)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces6 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces6I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces6)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces6v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces6)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces7 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces7I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces7)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces7v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces7)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces8 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces8I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces8)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces8v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces8)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces9 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces9I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces9)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces9v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces9)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces10 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces10I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces10)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces10v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces10)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces11 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces11I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces11)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces11v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces11)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces12 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces12I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces12)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces12v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces12)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces13 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces13I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces13)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces13v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces13)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces14 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces14I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces14)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces14v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces14)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces15 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces15I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces15)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces15v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces15)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_traces16 /* [0,4000] */;
  uint32_t bbsecond_data4trace_traces16I[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces16)] /* [1,4000] */;
  uint32_t bbsecond_data4trace_traces16v[4000 EXT_STRUCT_CTRL(bbsecond_data4trace_traces16)] /* [0,65535] */;
  uint32_t bbsecond_data4trace_channel_id_traces /* [0,16] */;
  uint32_t bbsecond_data4trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbsecond_data4trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbsecond_data4trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbsecond_data4trace_channel_id_traces)] /* [0,255] */;

} EXT_STR_h101_bbfebex;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_bbfebex_onion_t
{
  /* UNPACK */
  uint32_t bbfirst_ts_subsystem_id;
  uint32_t bbfirst_ts_t[4];
  struct {
    uint32_t trig;
    uint32_t event_trigger_time_hi;
    uint32_t event_trigger_time_lo;
    uint32_t hit_pattern;
    uint32_t num_channels_fired;
    uint32_t board_num;
    uint32_t channel_id;
    uint32_t channel_idI[16 /* channel_id */];
    uint32_t channel_idv[16 /* channel_id */];
    uint32_t channel_trigger_time_hi;
    uint32_t channel_trigger_time_hiI[16 /* channel_trigger_time_hi */];
    uint32_t channel_trigger_time_hiv[16 /* channel_trigger_time_hi */];
    uint32_t channel_trigger_time_lo;
    uint32_t channel_trigger_time_loI[16 /* channel_trigger_time_lo */];
    uint32_t channel_trigger_time_lov[16 /* channel_trigger_time_lo */];
    uint32_t pileup;
    uint32_t pileupI[16 /* pileup */];
    uint32_t pileupv[16 /* pileup */];
    uint32_t overflow;
    uint32_t overflowI[16 /* overflow */];
    uint32_t overflowv[16 /* overflow */];
    uint32_t channel_cfd;
    uint32_t channel_cfdI[16 /* channel_cfd */];
    uint32_t channel_cfdv[16 /* channel_cfd */];
    uint32_t channel_energy;
    uint32_t channel_energyI[16 /* channel_energy */];
    uint32_t channel_energyv[16 /* channel_energy */];
    struct {
      uint32_t _;
      uint32_t I[4000 /*  */];
      uint32_t v[4000 /*  */];
    } trace_traces[16];
    uint32_t trace_channel_id_traces;
    uint32_t trace_channel_id_tracesI[16 /* trace_channel_id_traces */];
    uint32_t trace_channel_id_tracesv[16 /* trace_channel_id_traces */];
  } bbfirst_data[5];
  uint32_t bbsecond_ts_subsystem_id;
  uint32_t bbsecond_ts_t[4];
  struct {
    uint32_t trig;
    uint32_t event_trigger_time_hi;
    uint32_t event_trigger_time_lo;
    uint32_t hit_pattern;
    uint32_t num_channels_fired;
    uint32_t board_num;
    uint32_t channel_id;
    uint32_t channel_idI[16 /* channel_id */];
    uint32_t channel_idv[16 /* channel_id */];
    uint32_t channel_trigger_time_hi;
    uint32_t channel_trigger_time_hiI[16 /* channel_trigger_time_hi */];
    uint32_t channel_trigger_time_hiv[16 /* channel_trigger_time_hi */];
    uint32_t channel_trigger_time_lo;
    uint32_t channel_trigger_time_loI[16 /* channel_trigger_time_lo */];
    uint32_t channel_trigger_time_lov[16 /* channel_trigger_time_lo */];
    uint32_t pileup;
    uint32_t pileupI[16 /* pileup */];
    uint32_t pileupv[16 /* pileup */];
    uint32_t overflow;
    uint32_t overflowI[16 /* overflow */];
    uint32_t overflowv[16 /* overflow */];
    uint32_t channel_cfd;
    uint32_t channel_cfdI[16 /* channel_cfd */];
    uint32_t channel_cfdv[16 /* channel_cfd */];
    uint32_t channel_energy;
    uint32_t channel_energyI[16 /* channel_energy */];
    uint32_t channel_energyv[16 /* channel_energy */];
    struct {
      uint32_t _;
      uint32_t I[4000 /*  */];
      uint32_t v[4000 /*  */];
    } trace_traces[16];
    uint32_t trace_channel_id_traces;
    uint32_t trace_channel_id_tracesI[16 /* trace_channel_id_traces */];
    uint32_t trace_channel_id_tracesv[16 /* trace_channel_id_traces */];
  } bbsecond_data[4];

} EXT_STR_h101_bbfebex_onion;

/*******************************************************/

#define EXT_STR_h101_bbfebex_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_ts_subsystem_id,         UINT32,\
                    "bbfirst_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_ts_t1,                   UINT32,\
                    "bbfirst_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_ts_t2,                   UINT32,\
                    "bbfirst_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_ts_t3,                   UINT32,\
                    "bbfirst_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_ts_t4,                   UINT32,\
                    "bbfirst_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trig,               UINT32,\
                    "bbfirst_data1trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data1event_trigger_time_hi,UINT32,\
                    "bbfirst_data1event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data1event_trigger_time_lo,UINT32,\
                    "bbfirst_data1event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1hit_pattern,        UINT32,\
                    "bbfirst_data1hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data1num_channels_fired, UINT32,\
                    "bbfirst_data1num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1board_num,          UINT32,\
                    "bbfirst_data1board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_id,         UINT32,\
                    "bbfirst_data1channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_idI,        UINT32,\
                    "bbfirst_data1channel_idI",        "bbfirst_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_idv,        UINT32,\
                    "bbfirst_data1channel_idv",        "bbfirst_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_trigger_time_hi,UINT32,\
                    "bbfirst_data1channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_trigger_time_hiI,UINT32,\
                    "bbfirst_data1channel_trigger_time_hiI","bbfirst_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_trigger_time_hiv,UINT32,\
                    "bbfirst_data1channel_trigger_time_hiv","bbfirst_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_trigger_time_lo,UINT32,\
                    "bbfirst_data1channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_trigger_time_loI,UINT32,\
                    "bbfirst_data1channel_trigger_time_loI","bbfirst_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_trigger_time_lov,UINT32,\
                    "bbfirst_data1channel_trigger_time_lov","bbfirst_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1pileup,             UINT32,\
                    "bbfirst_data1pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1pileupI,            UINT32,\
                    "bbfirst_data1pileupI",            "bbfirst_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1pileupv,            UINT32,\
                    "bbfirst_data1pileupv",            "bbfirst_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1overflow,           UINT32,\
                    "bbfirst_data1overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1overflowI,          UINT32,\
                    "bbfirst_data1overflowI",          "bbfirst_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1overflowv,          UINT32,\
                    "bbfirst_data1overflowv",          "bbfirst_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_cfd,        UINT32,\
                    "bbfirst_data1channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_cfdI,       UINT32,\
                    "bbfirst_data1channel_cfdI",       "bbfirst_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_cfdv,       UINT32,\
                    "bbfirst_data1channel_cfdv",       "bbfirst_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_energy,     UINT32,\
                    "bbfirst_data1channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_energyI,    UINT32,\
                    "bbfirst_data1channel_energyI",    "bbfirst_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1channel_energyv,    UINT32,\
                    "bbfirst_data1channel_energyv",    "bbfirst_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces1,      UINT32,\
                    "bbfirst_data1trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces1I,     UINT32,\
                    "bbfirst_data1trace_traces1I",     "bbfirst_data1trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces1v,     UINT32,\
                    "bbfirst_data1trace_traces1v",     "bbfirst_data1trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces2,      UINT32,\
                    "bbfirst_data1trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces2I,     UINT32,\
                    "bbfirst_data1trace_traces2I",     "bbfirst_data1trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces2v,     UINT32,\
                    "bbfirst_data1trace_traces2v",     "bbfirst_data1trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces3,      UINT32,\
                    "bbfirst_data1trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces3I,     UINT32,\
                    "bbfirst_data1trace_traces3I",     "bbfirst_data1trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces3v,     UINT32,\
                    "bbfirst_data1trace_traces3v",     "bbfirst_data1trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces4,      UINT32,\
                    "bbfirst_data1trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces4I,     UINT32,\
                    "bbfirst_data1trace_traces4I",     "bbfirst_data1trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces4v,     UINT32,\
                    "bbfirst_data1trace_traces4v",     "bbfirst_data1trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces5,      UINT32,\
                    "bbfirst_data1trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces5I,     UINT32,\
                    "bbfirst_data1trace_traces5I",     "bbfirst_data1trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces5v,     UINT32,\
                    "bbfirst_data1trace_traces5v",     "bbfirst_data1trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces6,      UINT32,\
                    "bbfirst_data1trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces6I,     UINT32,\
                    "bbfirst_data1trace_traces6I",     "bbfirst_data1trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces6v,     UINT32,\
                    "bbfirst_data1trace_traces6v",     "bbfirst_data1trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces7,      UINT32,\
                    "bbfirst_data1trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces7I,     UINT32,\
                    "bbfirst_data1trace_traces7I",     "bbfirst_data1trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces7v,     UINT32,\
                    "bbfirst_data1trace_traces7v",     "bbfirst_data1trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces8,      UINT32,\
                    "bbfirst_data1trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces8I,     UINT32,\
                    "bbfirst_data1trace_traces8I",     "bbfirst_data1trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces8v,     UINT32,\
                    "bbfirst_data1trace_traces8v",     "bbfirst_data1trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces9,      UINT32,\
                    "bbfirst_data1trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces9I,     UINT32,\
                    "bbfirst_data1trace_traces9I",     "bbfirst_data1trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces9v,     UINT32,\
                    "bbfirst_data1trace_traces9v",     "bbfirst_data1trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces10,     UINT32,\
                    "bbfirst_data1trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces10I,    UINT32,\
                    "bbfirst_data1trace_traces10I",    "bbfirst_data1trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces10v,    UINT32,\
                    "bbfirst_data1trace_traces10v",    "bbfirst_data1trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces11,     UINT32,\
                    "bbfirst_data1trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces11I,    UINT32,\
                    "bbfirst_data1trace_traces11I",    "bbfirst_data1trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces11v,    UINT32,\
                    "bbfirst_data1trace_traces11v",    "bbfirst_data1trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces12,     UINT32,\
                    "bbfirst_data1trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces12I,    UINT32,\
                    "bbfirst_data1trace_traces12I",    "bbfirst_data1trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces12v,    UINT32,\
                    "bbfirst_data1trace_traces12v",    "bbfirst_data1trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces13,     UINT32,\
                    "bbfirst_data1trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces13I,    UINT32,\
                    "bbfirst_data1trace_traces13I",    "bbfirst_data1trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces13v,    UINT32,\
                    "bbfirst_data1trace_traces13v",    "bbfirst_data1trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces14,     UINT32,\
                    "bbfirst_data1trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces14I,    UINT32,\
                    "bbfirst_data1trace_traces14I",    "bbfirst_data1trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces14v,    UINT32,\
                    "bbfirst_data1trace_traces14v",    "bbfirst_data1trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces15,     UINT32,\
                    "bbfirst_data1trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces15I,    UINT32,\
                    "bbfirst_data1trace_traces15I",    "bbfirst_data1trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces15v,    UINT32,\
                    "bbfirst_data1trace_traces15v",    "bbfirst_data1trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces16,     UINT32,\
                    "bbfirst_data1trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces16I,    UINT32,\
                    "bbfirst_data1trace_traces16I",    "bbfirst_data1trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_traces16v,    UINT32,\
                    "bbfirst_data1trace_traces16v",    "bbfirst_data1trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_channel_id_traces,UINT32,\
                    "bbfirst_data1trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_channel_id_tracesI,UINT32,\
                    "bbfirst_data1trace_channel_id_tracesI","bbfirst_data1trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data1trace_channel_id_tracesv,UINT32,\
                    "bbfirst_data1trace_channel_id_tracesv","bbfirst_data1trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trig,               UINT32,\
                    "bbfirst_data2trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data2event_trigger_time_hi,UINT32,\
                    "bbfirst_data2event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data2event_trigger_time_lo,UINT32,\
                    "bbfirst_data2event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2hit_pattern,        UINT32,\
                    "bbfirst_data2hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data2num_channels_fired, UINT32,\
                    "bbfirst_data2num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2board_num,          UINT32,\
                    "bbfirst_data2board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_id,         UINT32,\
                    "bbfirst_data2channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_idI,        UINT32,\
                    "bbfirst_data2channel_idI",        "bbfirst_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_idv,        UINT32,\
                    "bbfirst_data2channel_idv",        "bbfirst_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_trigger_time_hi,UINT32,\
                    "bbfirst_data2channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_trigger_time_hiI,UINT32,\
                    "bbfirst_data2channel_trigger_time_hiI","bbfirst_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_trigger_time_hiv,UINT32,\
                    "bbfirst_data2channel_trigger_time_hiv","bbfirst_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_trigger_time_lo,UINT32,\
                    "bbfirst_data2channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_trigger_time_loI,UINT32,\
                    "bbfirst_data2channel_trigger_time_loI","bbfirst_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_trigger_time_lov,UINT32,\
                    "bbfirst_data2channel_trigger_time_lov","bbfirst_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2pileup,             UINT32,\
                    "bbfirst_data2pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2pileupI,            UINT32,\
                    "bbfirst_data2pileupI",            "bbfirst_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2pileupv,            UINT32,\
                    "bbfirst_data2pileupv",            "bbfirst_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2overflow,           UINT32,\
                    "bbfirst_data2overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2overflowI,          UINT32,\
                    "bbfirst_data2overflowI",          "bbfirst_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2overflowv,          UINT32,\
                    "bbfirst_data2overflowv",          "bbfirst_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_cfd,        UINT32,\
                    "bbfirst_data2channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_cfdI,       UINT32,\
                    "bbfirst_data2channel_cfdI",       "bbfirst_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_cfdv,       UINT32,\
                    "bbfirst_data2channel_cfdv",       "bbfirst_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_energy,     UINT32,\
                    "bbfirst_data2channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_energyI,    UINT32,\
                    "bbfirst_data2channel_energyI",    "bbfirst_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2channel_energyv,    UINT32,\
                    "bbfirst_data2channel_energyv",    "bbfirst_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces1,      UINT32,\
                    "bbfirst_data2trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces1I,     UINT32,\
                    "bbfirst_data2trace_traces1I",     "bbfirst_data2trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces1v,     UINT32,\
                    "bbfirst_data2trace_traces1v",     "bbfirst_data2trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces2,      UINT32,\
                    "bbfirst_data2trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces2I,     UINT32,\
                    "bbfirst_data2trace_traces2I",     "bbfirst_data2trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces2v,     UINT32,\
                    "bbfirst_data2trace_traces2v",     "bbfirst_data2trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces3,      UINT32,\
                    "bbfirst_data2trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces3I,     UINT32,\
                    "bbfirst_data2trace_traces3I",     "bbfirst_data2trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces3v,     UINT32,\
                    "bbfirst_data2trace_traces3v",     "bbfirst_data2trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces4,      UINT32,\
                    "bbfirst_data2trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces4I,     UINT32,\
                    "bbfirst_data2trace_traces4I",     "bbfirst_data2trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces4v,     UINT32,\
                    "bbfirst_data2trace_traces4v",     "bbfirst_data2trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces5,      UINT32,\
                    "bbfirst_data2trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces5I,     UINT32,\
                    "bbfirst_data2trace_traces5I",     "bbfirst_data2trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces5v,     UINT32,\
                    "bbfirst_data2trace_traces5v",     "bbfirst_data2trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces6,      UINT32,\
                    "bbfirst_data2trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces6I,     UINT32,\
                    "bbfirst_data2trace_traces6I",     "bbfirst_data2trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces6v,     UINT32,\
                    "bbfirst_data2trace_traces6v",     "bbfirst_data2trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces7,      UINT32,\
                    "bbfirst_data2trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces7I,     UINT32,\
                    "bbfirst_data2trace_traces7I",     "bbfirst_data2trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces7v,     UINT32,\
                    "bbfirst_data2trace_traces7v",     "bbfirst_data2trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces8,      UINT32,\
                    "bbfirst_data2trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces8I,     UINT32,\
                    "bbfirst_data2trace_traces8I",     "bbfirst_data2trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces8v,     UINT32,\
                    "bbfirst_data2trace_traces8v",     "bbfirst_data2trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces9,      UINT32,\
                    "bbfirst_data2trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces9I,     UINT32,\
                    "bbfirst_data2trace_traces9I",     "bbfirst_data2trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces9v,     UINT32,\
                    "bbfirst_data2trace_traces9v",     "bbfirst_data2trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces10,     UINT32,\
                    "bbfirst_data2trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces10I,    UINT32,\
                    "bbfirst_data2trace_traces10I",    "bbfirst_data2trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces10v,    UINT32,\
                    "bbfirst_data2trace_traces10v",    "bbfirst_data2trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces11,     UINT32,\
                    "bbfirst_data2trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces11I,    UINT32,\
                    "bbfirst_data2trace_traces11I",    "bbfirst_data2trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces11v,    UINT32,\
                    "bbfirst_data2trace_traces11v",    "bbfirst_data2trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces12,     UINT32,\
                    "bbfirst_data2trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces12I,    UINT32,\
                    "bbfirst_data2trace_traces12I",    "bbfirst_data2trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces12v,    UINT32,\
                    "bbfirst_data2trace_traces12v",    "bbfirst_data2trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces13,     UINT32,\
                    "bbfirst_data2trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces13I,    UINT32,\
                    "bbfirst_data2trace_traces13I",    "bbfirst_data2trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces13v,    UINT32,\
                    "bbfirst_data2trace_traces13v",    "bbfirst_data2trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces14,     UINT32,\
                    "bbfirst_data2trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces14I,    UINT32,\
                    "bbfirst_data2trace_traces14I",    "bbfirst_data2trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces14v,    UINT32,\
                    "bbfirst_data2trace_traces14v",    "bbfirst_data2trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces15,     UINT32,\
                    "bbfirst_data2trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces15I,    UINT32,\
                    "bbfirst_data2trace_traces15I",    "bbfirst_data2trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces15v,    UINT32,\
                    "bbfirst_data2trace_traces15v",    "bbfirst_data2trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces16,     UINT32,\
                    "bbfirst_data2trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces16I,    UINT32,\
                    "bbfirst_data2trace_traces16I",    "bbfirst_data2trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_traces16v,    UINT32,\
                    "bbfirst_data2trace_traces16v",    "bbfirst_data2trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_channel_id_traces,UINT32,\
                    "bbfirst_data2trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_channel_id_tracesI,UINT32,\
                    "bbfirst_data2trace_channel_id_tracesI","bbfirst_data2trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data2trace_channel_id_tracesv,UINT32,\
                    "bbfirst_data2trace_channel_id_tracesv","bbfirst_data2trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trig,               UINT32,\
                    "bbfirst_data3trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data3event_trigger_time_hi,UINT32,\
                    "bbfirst_data3event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data3event_trigger_time_lo,UINT32,\
                    "bbfirst_data3event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3hit_pattern,        UINT32,\
                    "bbfirst_data3hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data3num_channels_fired, UINT32,\
                    "bbfirst_data3num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3board_num,          UINT32,\
                    "bbfirst_data3board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_id,         UINT32,\
                    "bbfirst_data3channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_idI,        UINT32,\
                    "bbfirst_data3channel_idI",        "bbfirst_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_idv,        UINT32,\
                    "bbfirst_data3channel_idv",        "bbfirst_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_trigger_time_hi,UINT32,\
                    "bbfirst_data3channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_trigger_time_hiI,UINT32,\
                    "bbfirst_data3channel_trigger_time_hiI","bbfirst_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_trigger_time_hiv,UINT32,\
                    "bbfirst_data3channel_trigger_time_hiv","bbfirst_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_trigger_time_lo,UINT32,\
                    "bbfirst_data3channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_trigger_time_loI,UINT32,\
                    "bbfirst_data3channel_trigger_time_loI","bbfirst_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_trigger_time_lov,UINT32,\
                    "bbfirst_data3channel_trigger_time_lov","bbfirst_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3pileup,             UINT32,\
                    "bbfirst_data3pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3pileupI,            UINT32,\
                    "bbfirst_data3pileupI",            "bbfirst_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3pileupv,            UINT32,\
                    "bbfirst_data3pileupv",            "bbfirst_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3overflow,           UINT32,\
                    "bbfirst_data3overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3overflowI,          UINT32,\
                    "bbfirst_data3overflowI",          "bbfirst_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3overflowv,          UINT32,\
                    "bbfirst_data3overflowv",          "bbfirst_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_cfd,        UINT32,\
                    "bbfirst_data3channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_cfdI,       UINT32,\
                    "bbfirst_data3channel_cfdI",       "bbfirst_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_cfdv,       UINT32,\
                    "bbfirst_data3channel_cfdv",       "bbfirst_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_energy,     UINT32,\
                    "bbfirst_data3channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_energyI,    UINT32,\
                    "bbfirst_data3channel_energyI",    "bbfirst_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3channel_energyv,    UINT32,\
                    "bbfirst_data3channel_energyv",    "bbfirst_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces1,      UINT32,\
                    "bbfirst_data3trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces1I,     UINT32,\
                    "bbfirst_data3trace_traces1I",     "bbfirst_data3trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces1v,     UINT32,\
                    "bbfirst_data3trace_traces1v",     "bbfirst_data3trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces2,      UINT32,\
                    "bbfirst_data3trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces2I,     UINT32,\
                    "bbfirst_data3trace_traces2I",     "bbfirst_data3trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces2v,     UINT32,\
                    "bbfirst_data3trace_traces2v",     "bbfirst_data3trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces3,      UINT32,\
                    "bbfirst_data3trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces3I,     UINT32,\
                    "bbfirst_data3trace_traces3I",     "bbfirst_data3trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces3v,     UINT32,\
                    "bbfirst_data3trace_traces3v",     "bbfirst_data3trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces4,      UINT32,\
                    "bbfirst_data3trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces4I,     UINT32,\
                    "bbfirst_data3trace_traces4I",     "bbfirst_data3trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces4v,     UINT32,\
                    "bbfirst_data3trace_traces4v",     "bbfirst_data3trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces5,      UINT32,\
                    "bbfirst_data3trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces5I,     UINT32,\
                    "bbfirst_data3trace_traces5I",     "bbfirst_data3trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces5v,     UINT32,\
                    "bbfirst_data3trace_traces5v",     "bbfirst_data3trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces6,      UINT32,\
                    "bbfirst_data3trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces6I,     UINT32,\
                    "bbfirst_data3trace_traces6I",     "bbfirst_data3trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces6v,     UINT32,\
                    "bbfirst_data3trace_traces6v",     "bbfirst_data3trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces7,      UINT32,\
                    "bbfirst_data3trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces7I,     UINT32,\
                    "bbfirst_data3trace_traces7I",     "bbfirst_data3trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces7v,     UINT32,\
                    "bbfirst_data3trace_traces7v",     "bbfirst_data3trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces8,      UINT32,\
                    "bbfirst_data3trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces8I,     UINT32,\
                    "bbfirst_data3trace_traces8I",     "bbfirst_data3trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces8v,     UINT32,\
                    "bbfirst_data3trace_traces8v",     "bbfirst_data3trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces9,      UINT32,\
                    "bbfirst_data3trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces9I,     UINT32,\
                    "bbfirst_data3trace_traces9I",     "bbfirst_data3trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces9v,     UINT32,\
                    "bbfirst_data3trace_traces9v",     "bbfirst_data3trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces10,     UINT32,\
                    "bbfirst_data3trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces10I,    UINT32,\
                    "bbfirst_data3trace_traces10I",    "bbfirst_data3trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces10v,    UINT32,\
                    "bbfirst_data3trace_traces10v",    "bbfirst_data3trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces11,     UINT32,\
                    "bbfirst_data3trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces11I,    UINT32,\
                    "bbfirst_data3trace_traces11I",    "bbfirst_data3trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces11v,    UINT32,\
                    "bbfirst_data3trace_traces11v",    "bbfirst_data3trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces12,     UINT32,\
                    "bbfirst_data3trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces12I,    UINT32,\
                    "bbfirst_data3trace_traces12I",    "bbfirst_data3trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces12v,    UINT32,\
                    "bbfirst_data3trace_traces12v",    "bbfirst_data3trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces13,     UINT32,\
                    "bbfirst_data3trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces13I,    UINT32,\
                    "bbfirst_data3trace_traces13I",    "bbfirst_data3trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces13v,    UINT32,\
                    "bbfirst_data3trace_traces13v",    "bbfirst_data3trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces14,     UINT32,\
                    "bbfirst_data3trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces14I,    UINT32,\
                    "bbfirst_data3trace_traces14I",    "bbfirst_data3trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces14v,    UINT32,\
                    "bbfirst_data3trace_traces14v",    "bbfirst_data3trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces15,     UINT32,\
                    "bbfirst_data3trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces15I,    UINT32,\
                    "bbfirst_data3trace_traces15I",    "bbfirst_data3trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces15v,    UINT32,\
                    "bbfirst_data3trace_traces15v",    "bbfirst_data3trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces16,     UINT32,\
                    "bbfirst_data3trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces16I,    UINT32,\
                    "bbfirst_data3trace_traces16I",    "bbfirst_data3trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_traces16v,    UINT32,\
                    "bbfirst_data3trace_traces16v",    "bbfirst_data3trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_channel_id_traces,UINT32,\
                    "bbfirst_data3trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_channel_id_tracesI,UINT32,\
                    "bbfirst_data3trace_channel_id_tracesI","bbfirst_data3trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data3trace_channel_id_tracesv,UINT32,\
                    "bbfirst_data3trace_channel_id_tracesv","bbfirst_data3trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trig,               UINT32,\
                    "bbfirst_data4trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data4event_trigger_time_hi,UINT32,\
                    "bbfirst_data4event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data4event_trigger_time_lo,UINT32,\
                    "bbfirst_data4event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4hit_pattern,        UINT32,\
                    "bbfirst_data4hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data4num_channels_fired, UINT32,\
                    "bbfirst_data4num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4board_num,          UINT32,\
                    "bbfirst_data4board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_id,         UINT32,\
                    "bbfirst_data4channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_idI,        UINT32,\
                    "bbfirst_data4channel_idI",        "bbfirst_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_idv,        UINT32,\
                    "bbfirst_data4channel_idv",        "bbfirst_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_trigger_time_hi,UINT32,\
                    "bbfirst_data4channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_trigger_time_hiI,UINT32,\
                    "bbfirst_data4channel_trigger_time_hiI","bbfirst_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_trigger_time_hiv,UINT32,\
                    "bbfirst_data4channel_trigger_time_hiv","bbfirst_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_trigger_time_lo,UINT32,\
                    "bbfirst_data4channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_trigger_time_loI,UINT32,\
                    "bbfirst_data4channel_trigger_time_loI","bbfirst_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_trigger_time_lov,UINT32,\
                    "bbfirst_data4channel_trigger_time_lov","bbfirst_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4pileup,             UINT32,\
                    "bbfirst_data4pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4pileupI,            UINT32,\
                    "bbfirst_data4pileupI",            "bbfirst_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4pileupv,            UINT32,\
                    "bbfirst_data4pileupv",            "bbfirst_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4overflow,           UINT32,\
                    "bbfirst_data4overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4overflowI,          UINT32,\
                    "bbfirst_data4overflowI",          "bbfirst_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4overflowv,          UINT32,\
                    "bbfirst_data4overflowv",          "bbfirst_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_cfd,        UINT32,\
                    "bbfirst_data4channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_cfdI,       UINT32,\
                    "bbfirst_data4channel_cfdI",       "bbfirst_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_cfdv,       UINT32,\
                    "bbfirst_data4channel_cfdv",       "bbfirst_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_energy,     UINT32,\
                    "bbfirst_data4channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_energyI,    UINT32,\
                    "bbfirst_data4channel_energyI",    "bbfirst_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4channel_energyv,    UINT32,\
                    "bbfirst_data4channel_energyv",    "bbfirst_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces1,      UINT32,\
                    "bbfirst_data4trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces1I,     UINT32,\
                    "bbfirst_data4trace_traces1I",     "bbfirst_data4trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces1v,     UINT32,\
                    "bbfirst_data4trace_traces1v",     "bbfirst_data4trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces2,      UINT32,\
                    "bbfirst_data4trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces2I,     UINT32,\
                    "bbfirst_data4trace_traces2I",     "bbfirst_data4trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces2v,     UINT32,\
                    "bbfirst_data4trace_traces2v",     "bbfirst_data4trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces3,      UINT32,\
                    "bbfirst_data4trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces3I,     UINT32,\
                    "bbfirst_data4trace_traces3I",     "bbfirst_data4trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces3v,     UINT32,\
                    "bbfirst_data4trace_traces3v",     "bbfirst_data4trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces4,      UINT32,\
                    "bbfirst_data4trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces4I,     UINT32,\
                    "bbfirst_data4trace_traces4I",     "bbfirst_data4trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces4v,     UINT32,\
                    "bbfirst_data4trace_traces4v",     "bbfirst_data4trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces5,      UINT32,\
                    "bbfirst_data4trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces5I,     UINT32,\
                    "bbfirst_data4trace_traces5I",     "bbfirst_data4trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces5v,     UINT32,\
                    "bbfirst_data4trace_traces5v",     "bbfirst_data4trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces6,      UINT32,\
                    "bbfirst_data4trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces6I,     UINT32,\
                    "bbfirst_data4trace_traces6I",     "bbfirst_data4trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces6v,     UINT32,\
                    "bbfirst_data4trace_traces6v",     "bbfirst_data4trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces7,      UINT32,\
                    "bbfirst_data4trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces7I,     UINT32,\
                    "bbfirst_data4trace_traces7I",     "bbfirst_data4trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces7v,     UINT32,\
                    "bbfirst_data4trace_traces7v",     "bbfirst_data4trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces8,      UINT32,\
                    "bbfirst_data4trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces8I,     UINT32,\
                    "bbfirst_data4trace_traces8I",     "bbfirst_data4trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces8v,     UINT32,\
                    "bbfirst_data4trace_traces8v",     "bbfirst_data4trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces9,      UINT32,\
                    "bbfirst_data4trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces9I,     UINT32,\
                    "bbfirst_data4trace_traces9I",     "bbfirst_data4trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces9v,     UINT32,\
                    "bbfirst_data4trace_traces9v",     "bbfirst_data4trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces10,     UINT32,\
                    "bbfirst_data4trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces10I,    UINT32,\
                    "bbfirst_data4trace_traces10I",    "bbfirst_data4trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces10v,    UINT32,\
                    "bbfirst_data4trace_traces10v",    "bbfirst_data4trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces11,     UINT32,\
                    "bbfirst_data4trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces11I,    UINT32,\
                    "bbfirst_data4trace_traces11I",    "bbfirst_data4trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces11v,    UINT32,\
                    "bbfirst_data4trace_traces11v",    "bbfirst_data4trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces12,     UINT32,\
                    "bbfirst_data4trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces12I,    UINT32,\
                    "bbfirst_data4trace_traces12I",    "bbfirst_data4trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces12v,    UINT32,\
                    "bbfirst_data4trace_traces12v",    "bbfirst_data4trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces13,     UINT32,\
                    "bbfirst_data4trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces13I,    UINT32,\
                    "bbfirst_data4trace_traces13I",    "bbfirst_data4trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces13v,    UINT32,\
                    "bbfirst_data4trace_traces13v",    "bbfirst_data4trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces14,     UINT32,\
                    "bbfirst_data4trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces14I,    UINT32,\
                    "bbfirst_data4trace_traces14I",    "bbfirst_data4trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces14v,    UINT32,\
                    "bbfirst_data4trace_traces14v",    "bbfirst_data4trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces15,     UINT32,\
                    "bbfirst_data4trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces15I,    UINT32,\
                    "bbfirst_data4trace_traces15I",    "bbfirst_data4trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces15v,    UINT32,\
                    "bbfirst_data4trace_traces15v",    "bbfirst_data4trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces16,     UINT32,\
                    "bbfirst_data4trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces16I,    UINT32,\
                    "bbfirst_data4trace_traces16I",    "bbfirst_data4trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_traces16v,    UINT32,\
                    "bbfirst_data4trace_traces16v",    "bbfirst_data4trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_channel_id_traces,UINT32,\
                    "bbfirst_data4trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_channel_id_tracesI,UINT32,\
                    "bbfirst_data4trace_channel_id_tracesI","bbfirst_data4trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data4trace_channel_id_tracesv,UINT32,\
                    "bbfirst_data4trace_channel_id_tracesv","bbfirst_data4trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trig,               UINT32,\
                    "bbfirst_data5trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data5event_trigger_time_hi,UINT32,\
                    "bbfirst_data5event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data5event_trigger_time_lo,UINT32,\
                    "bbfirst_data5event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5hit_pattern,        UINT32,\
                    "bbfirst_data5hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbfirst_data5num_channels_fired, UINT32,\
                    "bbfirst_data5num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5board_num,          UINT32,\
                    "bbfirst_data5board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_id,         UINT32,\
                    "bbfirst_data5channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_idI,        UINT32,\
                    "bbfirst_data5channel_idI",        "bbfirst_data5channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_idv,        UINT32,\
                    "bbfirst_data5channel_idv",        "bbfirst_data5channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_trigger_time_hi,UINT32,\
                    "bbfirst_data5channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_trigger_time_hiI,UINT32,\
                    "bbfirst_data5channel_trigger_time_hiI","bbfirst_data5channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_trigger_time_hiv,UINT32,\
                    "bbfirst_data5channel_trigger_time_hiv","bbfirst_data5channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_trigger_time_lo,UINT32,\
                    "bbfirst_data5channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_trigger_time_loI,UINT32,\
                    "bbfirst_data5channel_trigger_time_loI","bbfirst_data5channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_trigger_time_lov,UINT32,\
                    "bbfirst_data5channel_trigger_time_lov","bbfirst_data5channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5pileup,             UINT32,\
                    "bbfirst_data5pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5pileupI,            UINT32,\
                    "bbfirst_data5pileupI",            "bbfirst_data5pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5pileupv,            UINT32,\
                    "bbfirst_data5pileupv",            "bbfirst_data5pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5overflow,           UINT32,\
                    "bbfirst_data5overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5overflowI,          UINT32,\
                    "bbfirst_data5overflowI",          "bbfirst_data5overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5overflowv,          UINT32,\
                    "bbfirst_data5overflowv",          "bbfirst_data5overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_cfd,        UINT32,\
                    "bbfirst_data5channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_cfdI,       UINT32,\
                    "bbfirst_data5channel_cfdI",       "bbfirst_data5channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_cfdv,       UINT32,\
                    "bbfirst_data5channel_cfdv",       "bbfirst_data5channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_energy,     UINT32,\
                    "bbfirst_data5channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_energyI,    UINT32,\
                    "bbfirst_data5channel_energyI",    "bbfirst_data5channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5channel_energyv,    UINT32,\
                    "bbfirst_data5channel_energyv",    "bbfirst_data5channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces1,      UINT32,\
                    "bbfirst_data5trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces1I,     UINT32,\
                    "bbfirst_data5trace_traces1I",     "bbfirst_data5trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces1v,     UINT32,\
                    "bbfirst_data5trace_traces1v",     "bbfirst_data5trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces2,      UINT32,\
                    "bbfirst_data5trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces2I,     UINT32,\
                    "bbfirst_data5trace_traces2I",     "bbfirst_data5trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces2v,     UINT32,\
                    "bbfirst_data5trace_traces2v",     "bbfirst_data5trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces3,      UINT32,\
                    "bbfirst_data5trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces3I,     UINT32,\
                    "bbfirst_data5trace_traces3I",     "bbfirst_data5trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces3v,     UINT32,\
                    "bbfirst_data5trace_traces3v",     "bbfirst_data5trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces4,      UINT32,\
                    "bbfirst_data5trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces4I,     UINT32,\
                    "bbfirst_data5trace_traces4I",     "bbfirst_data5trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces4v,     UINT32,\
                    "bbfirst_data5trace_traces4v",     "bbfirst_data5trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces5,      UINT32,\
                    "bbfirst_data5trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces5I,     UINT32,\
                    "bbfirst_data5trace_traces5I",     "bbfirst_data5trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces5v,     UINT32,\
                    "bbfirst_data5trace_traces5v",     "bbfirst_data5trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces6,      UINT32,\
                    "bbfirst_data5trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces6I,     UINT32,\
                    "bbfirst_data5trace_traces6I",     "bbfirst_data5trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces6v,     UINT32,\
                    "bbfirst_data5trace_traces6v",     "bbfirst_data5trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces7,      UINT32,\
                    "bbfirst_data5trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces7I,     UINT32,\
                    "bbfirst_data5trace_traces7I",     "bbfirst_data5trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces7v,     UINT32,\
                    "bbfirst_data5trace_traces7v",     "bbfirst_data5trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces8,      UINT32,\
                    "bbfirst_data5trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces8I,     UINT32,\
                    "bbfirst_data5trace_traces8I",     "bbfirst_data5trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces8v,     UINT32,\
                    "bbfirst_data5trace_traces8v",     "bbfirst_data5trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces9,      UINT32,\
                    "bbfirst_data5trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces9I,     UINT32,\
                    "bbfirst_data5trace_traces9I",     "bbfirst_data5trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces9v,     UINT32,\
                    "bbfirst_data5trace_traces9v",     "bbfirst_data5trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces10,     UINT32,\
                    "bbfirst_data5trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces10I,    UINT32,\
                    "bbfirst_data5trace_traces10I",    "bbfirst_data5trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces10v,    UINT32,\
                    "bbfirst_data5trace_traces10v",    "bbfirst_data5trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces11,     UINT32,\
                    "bbfirst_data5trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces11I,    UINT32,\
                    "bbfirst_data5trace_traces11I",    "bbfirst_data5trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces11v,    UINT32,\
                    "bbfirst_data5trace_traces11v",    "bbfirst_data5trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces12,     UINT32,\
                    "bbfirst_data5trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces12I,    UINT32,\
                    "bbfirst_data5trace_traces12I",    "bbfirst_data5trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces12v,    UINT32,\
                    "bbfirst_data5trace_traces12v",    "bbfirst_data5trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces13,     UINT32,\
                    "bbfirst_data5trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces13I,    UINT32,\
                    "bbfirst_data5trace_traces13I",    "bbfirst_data5trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces13v,    UINT32,\
                    "bbfirst_data5trace_traces13v",    "bbfirst_data5trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces14,     UINT32,\
                    "bbfirst_data5trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces14I,    UINT32,\
                    "bbfirst_data5trace_traces14I",    "bbfirst_data5trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces14v,    UINT32,\
                    "bbfirst_data5trace_traces14v",    "bbfirst_data5trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces15,     UINT32,\
                    "bbfirst_data5trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces15I,    UINT32,\
                    "bbfirst_data5trace_traces15I",    "bbfirst_data5trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces15v,    UINT32,\
                    "bbfirst_data5trace_traces15v",    "bbfirst_data5trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces16,     UINT32,\
                    "bbfirst_data5trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces16I,    UINT32,\
                    "bbfirst_data5trace_traces16I",    "bbfirst_data5trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_traces16v,    UINT32,\
                    "bbfirst_data5trace_traces16v",    "bbfirst_data5trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_channel_id_traces,UINT32,\
                    "bbfirst_data5trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_channel_id_tracesI,UINT32,\
                    "bbfirst_data5trace_channel_id_tracesI","bbfirst_data5trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbfirst_data5trace_channel_id_tracesv,UINT32,\
                    "bbfirst_data5trace_channel_id_tracesv","bbfirst_data5trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_ts_subsystem_id,        UINT32,\
                    "bbsecond_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_ts_t1,                  UINT32,\
                    "bbsecond_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_ts_t2,                  UINT32,\
                    "bbsecond_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_ts_t3,                  UINT32,\
                    "bbsecond_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_ts_t4,                  UINT32,\
                    "bbsecond_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trig,              UINT32,\
                    "bbsecond_data1trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsecond_data1event_trigger_time_hi,UINT32,\
                    "bbsecond_data1event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsecond_data1event_trigger_time_lo,UINT32,\
                    "bbsecond_data1event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1hit_pattern,       UINT32,\
                    "bbsecond_data1hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsecond_data1num_channels_fired,UINT32,\
                    "bbsecond_data1num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1board_num,         UINT32,\
                    "bbsecond_data1board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_id,        UINT32,\
                    "bbsecond_data1channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_idI,       UINT32,\
                    "bbsecond_data1channel_idI",       "bbsecond_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_idv,       UINT32,\
                    "bbsecond_data1channel_idv",       "bbsecond_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_trigger_time_hi,UINT32,\
                    "bbsecond_data1channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_trigger_time_hiI,UINT32,\
                    "bbsecond_data1channel_trigger_time_hiI","bbsecond_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_trigger_time_hiv,UINT32,\
                    "bbsecond_data1channel_trigger_time_hiv","bbsecond_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_trigger_time_lo,UINT32,\
                    "bbsecond_data1channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_trigger_time_loI,UINT32,\
                    "bbsecond_data1channel_trigger_time_loI","bbsecond_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_trigger_time_lov,UINT32,\
                    "bbsecond_data1channel_trigger_time_lov","bbsecond_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1pileup,            UINT32,\
                    "bbsecond_data1pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1pileupI,           UINT32,\
                    "bbsecond_data1pileupI",           "bbsecond_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1pileupv,           UINT32,\
                    "bbsecond_data1pileupv",           "bbsecond_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1overflow,          UINT32,\
                    "bbsecond_data1overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1overflowI,         UINT32,\
                    "bbsecond_data1overflowI",         "bbsecond_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1overflowv,         UINT32,\
                    "bbsecond_data1overflowv",         "bbsecond_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_cfd,       UINT32,\
                    "bbsecond_data1channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_cfdI,      UINT32,\
                    "bbsecond_data1channel_cfdI",      "bbsecond_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_cfdv,      UINT32,\
                    "bbsecond_data1channel_cfdv",      "bbsecond_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_energy,    UINT32,\
                    "bbsecond_data1channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_energyI,   UINT32,\
                    "bbsecond_data1channel_energyI",   "bbsecond_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1channel_energyv,   UINT32,\
                    "bbsecond_data1channel_energyv",   "bbsecond_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces1,     UINT32,\
                    "bbsecond_data1trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces1I,    UINT32,\
                    "bbsecond_data1trace_traces1I",    "bbsecond_data1trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces1v,    UINT32,\
                    "bbsecond_data1trace_traces1v",    "bbsecond_data1trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces2,     UINT32,\
                    "bbsecond_data1trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces2I,    UINT32,\
                    "bbsecond_data1trace_traces2I",    "bbsecond_data1trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces2v,    UINT32,\
                    "bbsecond_data1trace_traces2v",    "bbsecond_data1trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces3,     UINT32,\
                    "bbsecond_data1trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces3I,    UINT32,\
                    "bbsecond_data1trace_traces3I",    "bbsecond_data1trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces3v,    UINT32,\
                    "bbsecond_data1trace_traces3v",    "bbsecond_data1trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces4,     UINT32,\
                    "bbsecond_data1trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces4I,    UINT32,\
                    "bbsecond_data1trace_traces4I",    "bbsecond_data1trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces4v,    UINT32,\
                    "bbsecond_data1trace_traces4v",    "bbsecond_data1trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces5,     UINT32,\
                    "bbsecond_data1trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces5I,    UINT32,\
                    "bbsecond_data1trace_traces5I",    "bbsecond_data1trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces5v,    UINT32,\
                    "bbsecond_data1trace_traces5v",    "bbsecond_data1trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces6,     UINT32,\
                    "bbsecond_data1trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces6I,    UINT32,\
                    "bbsecond_data1trace_traces6I",    "bbsecond_data1trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces6v,    UINT32,\
                    "bbsecond_data1trace_traces6v",    "bbsecond_data1trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces7,     UINT32,\
                    "bbsecond_data1trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces7I,    UINT32,\
                    "bbsecond_data1trace_traces7I",    "bbsecond_data1trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces7v,    UINT32,\
                    "bbsecond_data1trace_traces7v",    "bbsecond_data1trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces8,     UINT32,\
                    "bbsecond_data1trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces8I,    UINT32,\
                    "bbsecond_data1trace_traces8I",    "bbsecond_data1trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces8v,    UINT32,\
                    "bbsecond_data1trace_traces8v",    "bbsecond_data1trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces9,     UINT32,\
                    "bbsecond_data1trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces9I,    UINT32,\
                    "bbsecond_data1trace_traces9I",    "bbsecond_data1trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces9v,    UINT32,\
                    "bbsecond_data1trace_traces9v",    "bbsecond_data1trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces10,    UINT32,\
                    "bbsecond_data1trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces10I,   UINT32,\
                    "bbsecond_data1trace_traces10I",   "bbsecond_data1trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces10v,   UINT32,\
                    "bbsecond_data1trace_traces10v",   "bbsecond_data1trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces11,    UINT32,\
                    "bbsecond_data1trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces11I,   UINT32,\
                    "bbsecond_data1trace_traces11I",   "bbsecond_data1trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces11v,   UINT32,\
                    "bbsecond_data1trace_traces11v",   "bbsecond_data1trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces12,    UINT32,\
                    "bbsecond_data1trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces12I,   UINT32,\
                    "bbsecond_data1trace_traces12I",   "bbsecond_data1trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces12v,   UINT32,\
                    "bbsecond_data1trace_traces12v",   "bbsecond_data1trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces13,    UINT32,\
                    "bbsecond_data1trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces13I,   UINT32,\
                    "bbsecond_data1trace_traces13I",   "bbsecond_data1trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces13v,   UINT32,\
                    "bbsecond_data1trace_traces13v",   "bbsecond_data1trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces14,    UINT32,\
                    "bbsecond_data1trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces14I,   UINT32,\
                    "bbsecond_data1trace_traces14I",   "bbsecond_data1trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces14v,   UINT32,\
                    "bbsecond_data1trace_traces14v",   "bbsecond_data1trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces15,    UINT32,\
                    "bbsecond_data1trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces15I,   UINT32,\
                    "bbsecond_data1trace_traces15I",   "bbsecond_data1trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces15v,   UINT32,\
                    "bbsecond_data1trace_traces15v",   "bbsecond_data1trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces16,    UINT32,\
                    "bbsecond_data1trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces16I,   UINT32,\
                    "bbsecond_data1trace_traces16I",   "bbsecond_data1trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_traces16v,   UINT32,\
                    "bbsecond_data1trace_traces16v",   "bbsecond_data1trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_channel_id_traces,UINT32,\
                    "bbsecond_data1trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_channel_id_tracesI,UINT32,\
                    "bbsecond_data1trace_channel_id_tracesI","bbsecond_data1trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data1trace_channel_id_tracesv,UINT32,\
                    "bbsecond_data1trace_channel_id_tracesv","bbsecond_data1trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trig,              UINT32,\
                    "bbsecond_data2trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsecond_data2event_trigger_time_hi,UINT32,\
                    "bbsecond_data2event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsecond_data2event_trigger_time_lo,UINT32,\
                    "bbsecond_data2event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2hit_pattern,       UINT32,\
                    "bbsecond_data2hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsecond_data2num_channels_fired,UINT32,\
                    "bbsecond_data2num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2board_num,         UINT32,\
                    "bbsecond_data2board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_id,        UINT32,\
                    "bbsecond_data2channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_idI,       UINT32,\
                    "bbsecond_data2channel_idI",       "bbsecond_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_idv,       UINT32,\
                    "bbsecond_data2channel_idv",       "bbsecond_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_trigger_time_hi,UINT32,\
                    "bbsecond_data2channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_trigger_time_hiI,UINT32,\
                    "bbsecond_data2channel_trigger_time_hiI","bbsecond_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_trigger_time_hiv,UINT32,\
                    "bbsecond_data2channel_trigger_time_hiv","bbsecond_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_trigger_time_lo,UINT32,\
                    "bbsecond_data2channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_trigger_time_loI,UINT32,\
                    "bbsecond_data2channel_trigger_time_loI","bbsecond_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_trigger_time_lov,UINT32,\
                    "bbsecond_data2channel_trigger_time_lov","bbsecond_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2pileup,            UINT32,\
                    "bbsecond_data2pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2pileupI,           UINT32,\
                    "bbsecond_data2pileupI",           "bbsecond_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2pileupv,           UINT32,\
                    "bbsecond_data2pileupv",           "bbsecond_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2overflow,          UINT32,\
                    "bbsecond_data2overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2overflowI,         UINT32,\
                    "bbsecond_data2overflowI",         "bbsecond_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2overflowv,         UINT32,\
                    "bbsecond_data2overflowv",         "bbsecond_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_cfd,       UINT32,\
                    "bbsecond_data2channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_cfdI,      UINT32,\
                    "bbsecond_data2channel_cfdI",      "bbsecond_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_cfdv,      UINT32,\
                    "bbsecond_data2channel_cfdv",      "bbsecond_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_energy,    UINT32,\
                    "bbsecond_data2channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_energyI,   UINT32,\
                    "bbsecond_data2channel_energyI",   "bbsecond_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2channel_energyv,   UINT32,\
                    "bbsecond_data2channel_energyv",   "bbsecond_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces1,     UINT32,\
                    "bbsecond_data2trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces1I,    UINT32,\
                    "bbsecond_data2trace_traces1I",    "bbsecond_data2trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces1v,    UINT32,\
                    "bbsecond_data2trace_traces1v",    "bbsecond_data2trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces2,     UINT32,\
                    "bbsecond_data2trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces2I,    UINT32,\
                    "bbsecond_data2trace_traces2I",    "bbsecond_data2trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces2v,    UINT32,\
                    "bbsecond_data2trace_traces2v",    "bbsecond_data2trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces3,     UINT32,\
                    "bbsecond_data2trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces3I,    UINT32,\
                    "bbsecond_data2trace_traces3I",    "bbsecond_data2trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces3v,    UINT32,\
                    "bbsecond_data2trace_traces3v",    "bbsecond_data2trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces4,     UINT32,\
                    "bbsecond_data2trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces4I,    UINT32,\
                    "bbsecond_data2trace_traces4I",    "bbsecond_data2trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces4v,    UINT32,\
                    "bbsecond_data2trace_traces4v",    "bbsecond_data2trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces5,     UINT32,\
                    "bbsecond_data2trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces5I,    UINT32,\
                    "bbsecond_data2trace_traces5I",    "bbsecond_data2trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces5v,    UINT32,\
                    "bbsecond_data2trace_traces5v",    "bbsecond_data2trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces6,     UINT32,\
                    "bbsecond_data2trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces6I,    UINT32,\
                    "bbsecond_data2trace_traces6I",    "bbsecond_data2trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces6v,    UINT32,\
                    "bbsecond_data2trace_traces6v",    "bbsecond_data2trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces7,     UINT32,\
                    "bbsecond_data2trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces7I,    UINT32,\
                    "bbsecond_data2trace_traces7I",    "bbsecond_data2trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces7v,    UINT32,\
                    "bbsecond_data2trace_traces7v",    "bbsecond_data2trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces8,     UINT32,\
                    "bbsecond_data2trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces8I,    UINT32,\
                    "bbsecond_data2trace_traces8I",    "bbsecond_data2trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces8v,    UINT32,\
                    "bbsecond_data2trace_traces8v",    "bbsecond_data2trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces9,     UINT32,\
                    "bbsecond_data2trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces9I,    UINT32,\
                    "bbsecond_data2trace_traces9I",    "bbsecond_data2trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces9v,    UINT32,\
                    "bbsecond_data2trace_traces9v",    "bbsecond_data2trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces10,    UINT32,\
                    "bbsecond_data2trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces10I,   UINT32,\
                    "bbsecond_data2trace_traces10I",   "bbsecond_data2trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces10v,   UINT32,\
                    "bbsecond_data2trace_traces10v",   "bbsecond_data2trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces11,    UINT32,\
                    "bbsecond_data2trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces11I,   UINT32,\
                    "bbsecond_data2trace_traces11I",   "bbsecond_data2trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces11v,   UINT32,\
                    "bbsecond_data2trace_traces11v",   "bbsecond_data2trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces12,    UINT32,\
                    "bbsecond_data2trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces12I,   UINT32,\
                    "bbsecond_data2trace_traces12I",   "bbsecond_data2trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces12v,   UINT32,\
                    "bbsecond_data2trace_traces12v",   "bbsecond_data2trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces13,    UINT32,\
                    "bbsecond_data2trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces13I,   UINT32,\
                    "bbsecond_data2trace_traces13I",   "bbsecond_data2trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces13v,   UINT32,\
                    "bbsecond_data2trace_traces13v",   "bbsecond_data2trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces14,    UINT32,\
                    "bbsecond_data2trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces14I,   UINT32,\
                    "bbsecond_data2trace_traces14I",   "bbsecond_data2trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces14v,   UINT32,\
                    "bbsecond_data2trace_traces14v",   "bbsecond_data2trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces15,    UINT32,\
                    "bbsecond_data2trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces15I,   UINT32,\
                    "bbsecond_data2trace_traces15I",   "bbsecond_data2trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces15v,   UINT32,\
                    "bbsecond_data2trace_traces15v",   "bbsecond_data2trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces16,    UINT32,\
                    "bbsecond_data2trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces16I,   UINT32,\
                    "bbsecond_data2trace_traces16I",   "bbsecond_data2trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_traces16v,   UINT32,\
                    "bbsecond_data2trace_traces16v",   "bbsecond_data2trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_channel_id_traces,UINT32,\
                    "bbsecond_data2trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_channel_id_tracesI,UINT32,\
                    "bbsecond_data2trace_channel_id_tracesI","bbsecond_data2trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data2trace_channel_id_tracesv,UINT32,\
                    "bbsecond_data2trace_channel_id_tracesv","bbsecond_data2trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trig,              UINT32,\
                    "bbsecond_data3trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsecond_data3event_trigger_time_hi,UINT32,\
                    "bbsecond_data3event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsecond_data3event_trigger_time_lo,UINT32,\
                    "bbsecond_data3event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3hit_pattern,       UINT32,\
                    "bbsecond_data3hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsecond_data3num_channels_fired,UINT32,\
                    "bbsecond_data3num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3board_num,         UINT32,\
                    "bbsecond_data3board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_id,        UINT32,\
                    "bbsecond_data3channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_idI,       UINT32,\
                    "bbsecond_data3channel_idI",       "bbsecond_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_idv,       UINT32,\
                    "bbsecond_data3channel_idv",       "bbsecond_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_trigger_time_hi,UINT32,\
                    "bbsecond_data3channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_trigger_time_hiI,UINT32,\
                    "bbsecond_data3channel_trigger_time_hiI","bbsecond_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_trigger_time_hiv,UINT32,\
                    "bbsecond_data3channel_trigger_time_hiv","bbsecond_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_trigger_time_lo,UINT32,\
                    "bbsecond_data3channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_trigger_time_loI,UINT32,\
                    "bbsecond_data3channel_trigger_time_loI","bbsecond_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_trigger_time_lov,UINT32,\
                    "bbsecond_data3channel_trigger_time_lov","bbsecond_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3pileup,            UINT32,\
                    "bbsecond_data3pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3pileupI,           UINT32,\
                    "bbsecond_data3pileupI",           "bbsecond_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3pileupv,           UINT32,\
                    "bbsecond_data3pileupv",           "bbsecond_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3overflow,          UINT32,\
                    "bbsecond_data3overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3overflowI,         UINT32,\
                    "bbsecond_data3overflowI",         "bbsecond_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3overflowv,         UINT32,\
                    "bbsecond_data3overflowv",         "bbsecond_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_cfd,       UINT32,\
                    "bbsecond_data3channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_cfdI,      UINT32,\
                    "bbsecond_data3channel_cfdI",      "bbsecond_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_cfdv,      UINT32,\
                    "bbsecond_data3channel_cfdv",      "bbsecond_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_energy,    UINT32,\
                    "bbsecond_data3channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_energyI,   UINT32,\
                    "bbsecond_data3channel_energyI",   "bbsecond_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3channel_energyv,   UINT32,\
                    "bbsecond_data3channel_energyv",   "bbsecond_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces1,     UINT32,\
                    "bbsecond_data3trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces1I,    UINT32,\
                    "bbsecond_data3trace_traces1I",    "bbsecond_data3trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces1v,    UINT32,\
                    "bbsecond_data3trace_traces1v",    "bbsecond_data3trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces2,     UINT32,\
                    "bbsecond_data3trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces2I,    UINT32,\
                    "bbsecond_data3trace_traces2I",    "bbsecond_data3trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces2v,    UINT32,\
                    "bbsecond_data3trace_traces2v",    "bbsecond_data3trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces3,     UINT32,\
                    "bbsecond_data3trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces3I,    UINT32,\
                    "bbsecond_data3trace_traces3I",    "bbsecond_data3trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces3v,    UINT32,\
                    "bbsecond_data3trace_traces3v",    "bbsecond_data3trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces4,     UINT32,\
                    "bbsecond_data3trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces4I,    UINT32,\
                    "bbsecond_data3trace_traces4I",    "bbsecond_data3trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces4v,    UINT32,\
                    "bbsecond_data3trace_traces4v",    "bbsecond_data3trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces5,     UINT32,\
                    "bbsecond_data3trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces5I,    UINT32,\
                    "bbsecond_data3trace_traces5I",    "bbsecond_data3trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces5v,    UINT32,\
                    "bbsecond_data3trace_traces5v",    "bbsecond_data3trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces6,     UINT32,\
                    "bbsecond_data3trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces6I,    UINT32,\
                    "bbsecond_data3trace_traces6I",    "bbsecond_data3trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces6v,    UINT32,\
                    "bbsecond_data3trace_traces6v",    "bbsecond_data3trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces7,     UINT32,\
                    "bbsecond_data3trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces7I,    UINT32,\
                    "bbsecond_data3trace_traces7I",    "bbsecond_data3trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces7v,    UINT32,\
                    "bbsecond_data3trace_traces7v",    "bbsecond_data3trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces8,     UINT32,\
                    "bbsecond_data3trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces8I,    UINT32,\
                    "bbsecond_data3trace_traces8I",    "bbsecond_data3trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces8v,    UINT32,\
                    "bbsecond_data3trace_traces8v",    "bbsecond_data3trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces9,     UINT32,\
                    "bbsecond_data3trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces9I,    UINT32,\
                    "bbsecond_data3trace_traces9I",    "bbsecond_data3trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces9v,    UINT32,\
                    "bbsecond_data3trace_traces9v",    "bbsecond_data3trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces10,    UINT32,\
                    "bbsecond_data3trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces10I,   UINT32,\
                    "bbsecond_data3trace_traces10I",   "bbsecond_data3trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces10v,   UINT32,\
                    "bbsecond_data3trace_traces10v",   "bbsecond_data3trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces11,    UINT32,\
                    "bbsecond_data3trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces11I,   UINT32,\
                    "bbsecond_data3trace_traces11I",   "bbsecond_data3trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces11v,   UINT32,\
                    "bbsecond_data3trace_traces11v",   "bbsecond_data3trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces12,    UINT32,\
                    "bbsecond_data3trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces12I,   UINT32,\
                    "bbsecond_data3trace_traces12I",   "bbsecond_data3trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces12v,   UINT32,\
                    "bbsecond_data3trace_traces12v",   "bbsecond_data3trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces13,    UINT32,\
                    "bbsecond_data3trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces13I,   UINT32,\
                    "bbsecond_data3trace_traces13I",   "bbsecond_data3trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces13v,   UINT32,\
                    "bbsecond_data3trace_traces13v",   "bbsecond_data3trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces14,    UINT32,\
                    "bbsecond_data3trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces14I,   UINT32,\
                    "bbsecond_data3trace_traces14I",   "bbsecond_data3trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces14v,   UINT32,\
                    "bbsecond_data3trace_traces14v",   "bbsecond_data3trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces15,    UINT32,\
                    "bbsecond_data3trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces15I,   UINT32,\
                    "bbsecond_data3trace_traces15I",   "bbsecond_data3trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces15v,   UINT32,\
                    "bbsecond_data3trace_traces15v",   "bbsecond_data3trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces16,    UINT32,\
                    "bbsecond_data3trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces16I,   UINT32,\
                    "bbsecond_data3trace_traces16I",   "bbsecond_data3trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_traces16v,   UINT32,\
                    "bbsecond_data3trace_traces16v",   "bbsecond_data3trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_channel_id_traces,UINT32,\
                    "bbsecond_data3trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_channel_id_tracesI,UINT32,\
                    "bbsecond_data3trace_channel_id_tracesI","bbsecond_data3trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data3trace_channel_id_tracesv,UINT32,\
                    "bbsecond_data3trace_channel_id_tracesv","bbsecond_data3trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trig,              UINT32,\
                    "bbsecond_data4trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsecond_data4event_trigger_time_hi,UINT32,\
                    "bbsecond_data4event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsecond_data4event_trigger_time_lo,UINT32,\
                    "bbsecond_data4event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4hit_pattern,       UINT32,\
                    "bbsecond_data4hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsecond_data4num_channels_fired,UINT32,\
                    "bbsecond_data4num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4board_num,         UINT32,\
                    "bbsecond_data4board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_id,        UINT32,\
                    "bbsecond_data4channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_idI,       UINT32,\
                    "bbsecond_data4channel_idI",       "bbsecond_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_idv,       UINT32,\
                    "bbsecond_data4channel_idv",       "bbsecond_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_trigger_time_hi,UINT32,\
                    "bbsecond_data4channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_trigger_time_hiI,UINT32,\
                    "bbsecond_data4channel_trigger_time_hiI","bbsecond_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_trigger_time_hiv,UINT32,\
                    "bbsecond_data4channel_trigger_time_hiv","bbsecond_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_trigger_time_lo,UINT32,\
                    "bbsecond_data4channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_trigger_time_loI,UINT32,\
                    "bbsecond_data4channel_trigger_time_loI","bbsecond_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_trigger_time_lov,UINT32,\
                    "bbsecond_data4channel_trigger_time_lov","bbsecond_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4pileup,            UINT32,\
                    "bbsecond_data4pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4pileupI,           UINT32,\
                    "bbsecond_data4pileupI",           "bbsecond_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4pileupv,           UINT32,\
                    "bbsecond_data4pileupv",           "bbsecond_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4overflow,          UINT32,\
                    "bbsecond_data4overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4overflowI,         UINT32,\
                    "bbsecond_data4overflowI",         "bbsecond_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4overflowv,         UINT32,\
                    "bbsecond_data4overflowv",         "bbsecond_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_cfd,       UINT32,\
                    "bbsecond_data4channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_cfdI,      UINT32,\
                    "bbsecond_data4channel_cfdI",      "bbsecond_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_cfdv,      UINT32,\
                    "bbsecond_data4channel_cfdv",      "bbsecond_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_energy,    UINT32,\
                    "bbsecond_data4channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_energyI,   UINT32,\
                    "bbsecond_data4channel_energyI",   "bbsecond_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4channel_energyv,   UINT32,\
                    "bbsecond_data4channel_energyv",   "bbsecond_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces1,     UINT32,\
                    "bbsecond_data4trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces1I,    UINT32,\
                    "bbsecond_data4trace_traces1I",    "bbsecond_data4trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces1v,    UINT32,\
                    "bbsecond_data4trace_traces1v",    "bbsecond_data4trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces2,     UINT32,\
                    "bbsecond_data4trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces2I,    UINT32,\
                    "bbsecond_data4trace_traces2I",    "bbsecond_data4trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces2v,    UINT32,\
                    "bbsecond_data4trace_traces2v",    "bbsecond_data4trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces3,     UINT32,\
                    "bbsecond_data4trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces3I,    UINT32,\
                    "bbsecond_data4trace_traces3I",    "bbsecond_data4trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces3v,    UINT32,\
                    "bbsecond_data4trace_traces3v",    "bbsecond_data4trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces4,     UINT32,\
                    "bbsecond_data4trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces4I,    UINT32,\
                    "bbsecond_data4trace_traces4I",    "bbsecond_data4trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces4v,    UINT32,\
                    "bbsecond_data4trace_traces4v",    "bbsecond_data4trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces5,     UINT32,\
                    "bbsecond_data4trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces5I,    UINT32,\
                    "bbsecond_data4trace_traces5I",    "bbsecond_data4trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces5v,    UINT32,\
                    "bbsecond_data4trace_traces5v",    "bbsecond_data4trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces6,     UINT32,\
                    "bbsecond_data4trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces6I,    UINT32,\
                    "bbsecond_data4trace_traces6I",    "bbsecond_data4trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces6v,    UINT32,\
                    "bbsecond_data4trace_traces6v",    "bbsecond_data4trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces7,     UINT32,\
                    "bbsecond_data4trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces7I,    UINT32,\
                    "bbsecond_data4trace_traces7I",    "bbsecond_data4trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces7v,    UINT32,\
                    "bbsecond_data4trace_traces7v",    "bbsecond_data4trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces8,     UINT32,\
                    "bbsecond_data4trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces8I,    UINT32,\
                    "bbsecond_data4trace_traces8I",    "bbsecond_data4trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces8v,    UINT32,\
                    "bbsecond_data4trace_traces8v",    "bbsecond_data4trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces9,     UINT32,\
                    "bbsecond_data4trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces9I,    UINT32,\
                    "bbsecond_data4trace_traces9I",    "bbsecond_data4trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces9v,    UINT32,\
                    "bbsecond_data4trace_traces9v",    "bbsecond_data4trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces10,    UINT32,\
                    "bbsecond_data4trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces10I,   UINT32,\
                    "bbsecond_data4trace_traces10I",   "bbsecond_data4trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces10v,   UINT32,\
                    "bbsecond_data4trace_traces10v",   "bbsecond_data4trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces11,    UINT32,\
                    "bbsecond_data4trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces11I,   UINT32,\
                    "bbsecond_data4trace_traces11I",   "bbsecond_data4trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces11v,   UINT32,\
                    "bbsecond_data4trace_traces11v",   "bbsecond_data4trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces12,    UINT32,\
                    "bbsecond_data4trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces12I,   UINT32,\
                    "bbsecond_data4trace_traces12I",   "bbsecond_data4trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces12v,   UINT32,\
                    "bbsecond_data4trace_traces12v",   "bbsecond_data4trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces13,    UINT32,\
                    "bbsecond_data4trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces13I,   UINT32,\
                    "bbsecond_data4trace_traces13I",   "bbsecond_data4trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces13v,   UINT32,\
                    "bbsecond_data4trace_traces13v",   "bbsecond_data4trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces14,    UINT32,\
                    "bbsecond_data4trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces14I,   UINT32,\
                    "bbsecond_data4trace_traces14I",   "bbsecond_data4trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces14v,   UINT32,\
                    "bbsecond_data4trace_traces14v",   "bbsecond_data4trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces15,    UINT32,\
                    "bbsecond_data4trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces15I,   UINT32,\
                    "bbsecond_data4trace_traces15I",   "bbsecond_data4trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces15v,   UINT32,\
                    "bbsecond_data4trace_traces15v",   "bbsecond_data4trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces16,    UINT32,\
                    "bbsecond_data4trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces16I,   UINT32,\
                    "bbsecond_data4trace_traces16I",   "bbsecond_data4trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_traces16v,   UINT32,\
                    "bbsecond_data4trace_traces16v",   "bbsecond_data4trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_channel_id_traces,UINT32,\
                    "bbsecond_data4trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_channel_id_tracesI,UINT32,\
                    "bbsecond_data4trace_channel_id_tracesI","bbsecond_data4trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsecond_data4trace_channel_id_tracesv,UINT32,\
                    "bbsecond_data4trace_channel_id_tracesv","bbsecond_data4trace_channel_id_traces",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_BBFEBEX_EXT_H101_BBFEBEX_H__*/

/*******************************************************/
