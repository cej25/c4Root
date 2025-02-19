/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_BB7FEBEX_EXT_H101_BB7FEBEX_H__
#define __GUARD_H101_BB7FEBEX_EXT_H101_BB7FEBEX_H__

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

typedef struct EXT_STR_h101_bb7febex_t
{
  /* UNPACK */
  uint32_t bbsfebex_ts_subsystem_id /* [0,65535] */;
  uint32_t bbsfebex_ts_t1 /* [0,65535] */;
  uint32_t bbsfebex_ts_t2 /* [0,65535] */;
  uint32_t bbsfebex_ts_t3 /* [0,65535] */;
  uint32_t bbsfebex_ts_t4 /* [0,65535] */;
  uint32_t bbsfebex_data1trig /* [0,255] */;
  uint32_t bbsfebex_data1event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbsfebex_data1event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbsfebex_data1hit_pattern /* [0,65535] */;
  uint32_t bbsfebex_data1num_channels_fired /* [-1,-1] */;
  uint32_t bbsfebex_data1board_num /* [0,255] */;
  uint32_t bbsfebex_data1channel_id /* [0,16] */;
  uint32_t bbsfebex_data1channel_idI[16 EXT_STRUCT_CTRL(bbsfebex_data1channel_id)] /* [1,16] */;
  uint32_t bbsfebex_data1channel_idv[16 EXT_STRUCT_CTRL(bbsfebex_data1channel_id)] /* [0,255] */;
  uint32_t bbsfebex_data1channel_trigger_time_hi /* [0,16] */;
  uint32_t bbsfebex_data1channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbsfebex_data1channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbsfebex_data1channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbsfebex_data1channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbsfebex_data1channel_trigger_time_lo /* [0,16] */;
  uint32_t bbsfebex_data1channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbsfebex_data1channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbsfebex_data1channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbsfebex_data1channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbsfebex_data1pileup /* [0,16] */;
  uint32_t bbsfebex_data1pileupI[16 EXT_STRUCT_CTRL(bbsfebex_data1pileup)] /* [1,16] */;
  uint32_t bbsfebex_data1pileupv[16 EXT_STRUCT_CTRL(bbsfebex_data1pileup)] /* [0,255] */;
  uint32_t bbsfebex_data1overflow /* [0,16] */;
  uint32_t bbsfebex_data1overflowI[16 EXT_STRUCT_CTRL(bbsfebex_data1overflow)] /* [1,16] */;
  uint32_t bbsfebex_data1overflowv[16 EXT_STRUCT_CTRL(bbsfebex_data1overflow)] /* [0,255] */;
  uint32_t bbsfebex_data1channel_cfd /* [0,16] */;
  uint32_t bbsfebex_data1channel_cfdI[16 EXT_STRUCT_CTRL(bbsfebex_data1channel_cfd)] /* [1,16] */;
  uint32_t bbsfebex_data1channel_cfdv[16 EXT_STRUCT_CTRL(bbsfebex_data1channel_cfd)] /* [0,255] */;
  uint32_t bbsfebex_data1channel_energy /* [0,16] */;
  uint32_t bbsfebex_data1channel_energyI[16 EXT_STRUCT_CTRL(bbsfebex_data1channel_energy)] /* [1,16] */;
  uint32_t bbsfebex_data1channel_energyv[16 EXT_STRUCT_CTRL(bbsfebex_data1channel_energy)] /* [-1,-1] */;
  uint32_t bbsfebex_data1trace_traces1 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces1I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces1)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces1v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces1)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces2 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces2I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces2)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces2v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces2)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces3 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces3I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces3)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces3v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces3)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces4 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces4I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces4)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces4v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces4)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces5 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces5I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces5)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces5v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces5)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces6 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces6I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces6)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces6v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces6)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces7 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces7I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces7)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces7v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces7)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces8 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces8I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces8)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces8v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces8)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces9 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces9I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces9)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces9v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces9)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces10 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces10I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces10)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces10v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces10)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces11 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces11I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces11)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces11v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces11)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces12 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces12I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces12)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces12v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces12)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces13 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces13I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces13)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces13v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces13)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces14 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces14I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces14)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces14v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces14)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces15 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces15I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces15)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces15v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces15)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_traces16 /* [0,4000] */;
  uint32_t bbsfebex_data1trace_traces16I[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces16)] /* [1,4000] */;
  uint32_t bbsfebex_data1trace_traces16v[4000 EXT_STRUCT_CTRL(bbsfebex_data1trace_traces16)] /* [0,65535] */;
  uint32_t bbsfebex_data1trace_channel_id_traces /* [0,16] */;
  uint32_t bbsfebex_data1trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbsfebex_data1trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbsfebex_data1trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbsfebex_data1trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbsfebex_data2trig /* [0,255] */;
  uint32_t bbsfebex_data2event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbsfebex_data2event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbsfebex_data2hit_pattern /* [0,65535] */;
  uint32_t bbsfebex_data2num_channels_fired /* [-1,-1] */;
  uint32_t bbsfebex_data2board_num /* [0,255] */;
  uint32_t bbsfebex_data2channel_id /* [0,16] */;
  uint32_t bbsfebex_data2channel_idI[16 EXT_STRUCT_CTRL(bbsfebex_data2channel_id)] /* [1,16] */;
  uint32_t bbsfebex_data2channel_idv[16 EXT_STRUCT_CTRL(bbsfebex_data2channel_id)] /* [0,255] */;
  uint32_t bbsfebex_data2channel_trigger_time_hi /* [0,16] */;
  uint32_t bbsfebex_data2channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbsfebex_data2channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbsfebex_data2channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbsfebex_data2channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbsfebex_data2channel_trigger_time_lo /* [0,16] */;
  uint32_t bbsfebex_data2channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbsfebex_data2channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbsfebex_data2channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbsfebex_data2channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbsfebex_data2pileup /* [0,16] */;
  uint32_t bbsfebex_data2pileupI[16 EXT_STRUCT_CTRL(bbsfebex_data2pileup)] /* [1,16] */;
  uint32_t bbsfebex_data2pileupv[16 EXT_STRUCT_CTRL(bbsfebex_data2pileup)] /* [0,255] */;
  uint32_t bbsfebex_data2overflow /* [0,16] */;
  uint32_t bbsfebex_data2overflowI[16 EXT_STRUCT_CTRL(bbsfebex_data2overflow)] /* [1,16] */;
  uint32_t bbsfebex_data2overflowv[16 EXT_STRUCT_CTRL(bbsfebex_data2overflow)] /* [0,255] */;
  uint32_t bbsfebex_data2channel_cfd /* [0,16] */;
  uint32_t bbsfebex_data2channel_cfdI[16 EXT_STRUCT_CTRL(bbsfebex_data2channel_cfd)] /* [1,16] */;
  uint32_t bbsfebex_data2channel_cfdv[16 EXT_STRUCT_CTRL(bbsfebex_data2channel_cfd)] /* [0,255] */;
  uint32_t bbsfebex_data2channel_energy /* [0,16] */;
  uint32_t bbsfebex_data2channel_energyI[16 EXT_STRUCT_CTRL(bbsfebex_data2channel_energy)] /* [1,16] */;
  uint32_t bbsfebex_data2channel_energyv[16 EXT_STRUCT_CTRL(bbsfebex_data2channel_energy)] /* [-1,-1] */;
  uint32_t bbsfebex_data2trace_traces1 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces1I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces1)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces1v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces1)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces2 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces2I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces2)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces2v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces2)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces3 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces3I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces3)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces3v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces3)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces4 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces4I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces4)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces4v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces4)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces5 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces5I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces5)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces5v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces5)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces6 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces6I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces6)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces6v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces6)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces7 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces7I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces7)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces7v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces7)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces8 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces8I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces8)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces8v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces8)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces9 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces9I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces9)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces9v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces9)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces10 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces10I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces10)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces10v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces10)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces11 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces11I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces11)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces11v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces11)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces12 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces12I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces12)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces12v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces12)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces13 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces13I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces13)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces13v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces13)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces14 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces14I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces14)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces14v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces14)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces15 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces15I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces15)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces15v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces15)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_traces16 /* [0,4000] */;
  uint32_t bbsfebex_data2trace_traces16I[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces16)] /* [1,4000] */;
  uint32_t bbsfebex_data2trace_traces16v[4000 EXT_STRUCT_CTRL(bbsfebex_data2trace_traces16)] /* [0,65535] */;
  uint32_t bbsfebex_data2trace_channel_id_traces /* [0,16] */;
  uint32_t bbsfebex_data2trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbsfebex_data2trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbsfebex_data2trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbsfebex_data2trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbsfebex_data3trig /* [0,255] */;
  uint32_t bbsfebex_data3event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbsfebex_data3event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbsfebex_data3hit_pattern /* [0,65535] */;
  uint32_t bbsfebex_data3num_channels_fired /* [-1,-1] */;
  uint32_t bbsfebex_data3board_num /* [0,255] */;
  uint32_t bbsfebex_data3channel_id /* [0,16] */;
  uint32_t bbsfebex_data3channel_idI[16 EXT_STRUCT_CTRL(bbsfebex_data3channel_id)] /* [1,16] */;
  uint32_t bbsfebex_data3channel_idv[16 EXT_STRUCT_CTRL(bbsfebex_data3channel_id)] /* [0,255] */;
  uint32_t bbsfebex_data3channel_trigger_time_hi /* [0,16] */;
  uint32_t bbsfebex_data3channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbsfebex_data3channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbsfebex_data3channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbsfebex_data3channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbsfebex_data3channel_trigger_time_lo /* [0,16] */;
  uint32_t bbsfebex_data3channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbsfebex_data3channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbsfebex_data3channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbsfebex_data3channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbsfebex_data3pileup /* [0,16] */;
  uint32_t bbsfebex_data3pileupI[16 EXT_STRUCT_CTRL(bbsfebex_data3pileup)] /* [1,16] */;
  uint32_t bbsfebex_data3pileupv[16 EXT_STRUCT_CTRL(bbsfebex_data3pileup)] /* [0,255] */;
  uint32_t bbsfebex_data3overflow /* [0,16] */;
  uint32_t bbsfebex_data3overflowI[16 EXT_STRUCT_CTRL(bbsfebex_data3overflow)] /* [1,16] */;
  uint32_t bbsfebex_data3overflowv[16 EXT_STRUCT_CTRL(bbsfebex_data3overflow)] /* [0,255] */;
  uint32_t bbsfebex_data3channel_cfd /* [0,16] */;
  uint32_t bbsfebex_data3channel_cfdI[16 EXT_STRUCT_CTRL(bbsfebex_data3channel_cfd)] /* [1,16] */;
  uint32_t bbsfebex_data3channel_cfdv[16 EXT_STRUCT_CTRL(bbsfebex_data3channel_cfd)] /* [0,255] */;
  uint32_t bbsfebex_data3channel_energy /* [0,16] */;
  uint32_t bbsfebex_data3channel_energyI[16 EXT_STRUCT_CTRL(bbsfebex_data3channel_energy)] /* [1,16] */;
  uint32_t bbsfebex_data3channel_energyv[16 EXT_STRUCT_CTRL(bbsfebex_data3channel_energy)] /* [-1,-1] */;
  uint32_t bbsfebex_data3trace_traces1 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces1I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces1)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces1v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces1)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces2 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces2I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces2)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces2v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces2)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces3 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces3I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces3)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces3v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces3)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces4 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces4I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces4)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces4v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces4)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces5 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces5I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces5)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces5v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces5)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces6 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces6I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces6)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces6v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces6)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces7 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces7I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces7)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces7v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces7)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces8 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces8I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces8)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces8v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces8)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces9 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces9I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces9)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces9v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces9)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces10 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces10I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces10)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces10v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces10)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces11 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces11I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces11)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces11v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces11)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces12 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces12I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces12)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces12v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces12)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces13 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces13I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces13)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces13v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces13)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces14 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces14I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces14)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces14v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces14)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces15 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces15I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces15)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces15v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces15)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_traces16 /* [0,4000] */;
  uint32_t bbsfebex_data3trace_traces16I[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces16)] /* [1,4000] */;
  uint32_t bbsfebex_data3trace_traces16v[4000 EXT_STRUCT_CTRL(bbsfebex_data3trace_traces16)] /* [0,65535] */;
  uint32_t bbsfebex_data3trace_channel_id_traces /* [0,16] */;
  uint32_t bbsfebex_data3trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbsfebex_data3trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbsfebex_data3trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbsfebex_data3trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbsfebex_data4trig /* [0,255] */;
  uint32_t bbsfebex_data4event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbsfebex_data4event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbsfebex_data4hit_pattern /* [0,65535] */;
  uint32_t bbsfebex_data4num_channels_fired /* [-1,-1] */;
  uint32_t bbsfebex_data4board_num /* [0,255] */;
  uint32_t bbsfebex_data4channel_id /* [0,16] */;
  uint32_t bbsfebex_data4channel_idI[16 EXT_STRUCT_CTRL(bbsfebex_data4channel_id)] /* [1,16] */;
  uint32_t bbsfebex_data4channel_idv[16 EXT_STRUCT_CTRL(bbsfebex_data4channel_id)] /* [0,255] */;
  uint32_t bbsfebex_data4channel_trigger_time_hi /* [0,16] */;
  uint32_t bbsfebex_data4channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbsfebex_data4channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbsfebex_data4channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbsfebex_data4channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbsfebex_data4channel_trigger_time_lo /* [0,16] */;
  uint32_t bbsfebex_data4channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbsfebex_data4channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbsfebex_data4channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbsfebex_data4channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbsfebex_data4pileup /* [0,16] */;
  uint32_t bbsfebex_data4pileupI[16 EXT_STRUCT_CTRL(bbsfebex_data4pileup)] /* [1,16] */;
  uint32_t bbsfebex_data4pileupv[16 EXT_STRUCT_CTRL(bbsfebex_data4pileup)] /* [0,255] */;
  uint32_t bbsfebex_data4overflow /* [0,16] */;
  uint32_t bbsfebex_data4overflowI[16 EXT_STRUCT_CTRL(bbsfebex_data4overflow)] /* [1,16] */;
  uint32_t bbsfebex_data4overflowv[16 EXT_STRUCT_CTRL(bbsfebex_data4overflow)] /* [0,255] */;
  uint32_t bbsfebex_data4channel_cfd /* [0,16] */;
  uint32_t bbsfebex_data4channel_cfdI[16 EXT_STRUCT_CTRL(bbsfebex_data4channel_cfd)] /* [1,16] */;
  uint32_t bbsfebex_data4channel_cfdv[16 EXT_STRUCT_CTRL(bbsfebex_data4channel_cfd)] /* [0,255] */;
  uint32_t bbsfebex_data4channel_energy /* [0,16] */;
  uint32_t bbsfebex_data4channel_energyI[16 EXT_STRUCT_CTRL(bbsfebex_data4channel_energy)] /* [1,16] */;
  uint32_t bbsfebex_data4channel_energyv[16 EXT_STRUCT_CTRL(bbsfebex_data4channel_energy)] /* [-1,-1] */;
  uint32_t bbsfebex_data4trace_traces1 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces1I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces1)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces1v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces1)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces2 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces2I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces2)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces2v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces2)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces3 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces3I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces3)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces3v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces3)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces4 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces4I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces4)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces4v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces4)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces5 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces5I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces5)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces5v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces5)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces6 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces6I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces6)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces6v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces6)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces7 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces7I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces7)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces7v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces7)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces8 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces8I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces8)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces8v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces8)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces9 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces9I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces9)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces9v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces9)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces10 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces10I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces10)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces10v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces10)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces11 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces11I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces11)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces11v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces11)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces12 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces12I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces12)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces12v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces12)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces13 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces13I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces13)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces13v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces13)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces14 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces14I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces14)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces14v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces14)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces15 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces15I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces15)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces15v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces15)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_traces16 /* [0,4000] */;
  uint32_t bbsfebex_data4trace_traces16I[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces16)] /* [1,4000] */;
  uint32_t bbsfebex_data4trace_traces16v[4000 EXT_STRUCT_CTRL(bbsfebex_data4trace_traces16)] /* [0,65535] */;
  uint32_t bbsfebex_data4trace_channel_id_traces /* [0,16] */;
  uint32_t bbsfebex_data4trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbsfebex_data4trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbsfebex_data4trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbsfebex_data4trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbsfebex_data5trig /* [0,255] */;
  uint32_t bbsfebex_data5event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbsfebex_data5event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbsfebex_data5hit_pattern /* [0,65535] */;
  uint32_t bbsfebex_data5num_channels_fired /* [-1,-1] */;
  uint32_t bbsfebex_data5board_num /* [0,255] */;
  uint32_t bbsfebex_data5channel_id /* [0,16] */;
  uint32_t bbsfebex_data5channel_idI[16 EXT_STRUCT_CTRL(bbsfebex_data5channel_id)] /* [1,16] */;
  uint32_t bbsfebex_data5channel_idv[16 EXT_STRUCT_CTRL(bbsfebex_data5channel_id)] /* [0,255] */;
  uint32_t bbsfebex_data5channel_trigger_time_hi /* [0,16] */;
  uint32_t bbsfebex_data5channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbsfebex_data5channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbsfebex_data5channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbsfebex_data5channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbsfebex_data5channel_trigger_time_lo /* [0,16] */;
  uint32_t bbsfebex_data5channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbsfebex_data5channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbsfebex_data5channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbsfebex_data5channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbsfebex_data5pileup /* [0,16] */;
  uint32_t bbsfebex_data5pileupI[16 EXT_STRUCT_CTRL(bbsfebex_data5pileup)] /* [1,16] */;
  uint32_t bbsfebex_data5pileupv[16 EXT_STRUCT_CTRL(bbsfebex_data5pileup)] /* [0,255] */;
  uint32_t bbsfebex_data5overflow /* [0,16] */;
  uint32_t bbsfebex_data5overflowI[16 EXT_STRUCT_CTRL(bbsfebex_data5overflow)] /* [1,16] */;
  uint32_t bbsfebex_data5overflowv[16 EXT_STRUCT_CTRL(bbsfebex_data5overflow)] /* [0,255] */;
  uint32_t bbsfebex_data5channel_cfd /* [0,16] */;
  uint32_t bbsfebex_data5channel_cfdI[16 EXT_STRUCT_CTRL(bbsfebex_data5channel_cfd)] /* [1,16] */;
  uint32_t bbsfebex_data5channel_cfdv[16 EXT_STRUCT_CTRL(bbsfebex_data5channel_cfd)] /* [0,255] */;
  uint32_t bbsfebex_data5channel_energy /* [0,16] */;
  uint32_t bbsfebex_data5channel_energyI[16 EXT_STRUCT_CTRL(bbsfebex_data5channel_energy)] /* [1,16] */;
  uint32_t bbsfebex_data5channel_energyv[16 EXT_STRUCT_CTRL(bbsfebex_data5channel_energy)] /* [-1,-1] */;
  uint32_t bbsfebex_data5trace_traces1 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces1I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces1)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces1v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces1)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces2 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces2I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces2)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces2v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces2)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces3 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces3I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces3)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces3v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces3)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces4 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces4I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces4)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces4v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces4)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces5 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces5I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces5)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces5v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces5)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces6 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces6I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces6)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces6v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces6)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces7 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces7I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces7)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces7v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces7)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces8 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces8I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces8)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces8v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces8)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces9 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces9I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces9)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces9v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces9)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces10 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces10I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces10)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces10v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces10)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces11 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces11I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces11)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces11v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces11)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces12 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces12I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces12)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces12v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces12)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces13 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces13I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces13)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces13v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces13)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces14 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces14I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces14)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces14v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces14)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces15 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces15I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces15)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces15v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces15)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_traces16 /* [0,4000] */;
  uint32_t bbsfebex_data5trace_traces16I[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces16)] /* [1,4000] */;
  uint32_t bbsfebex_data5trace_traces16v[4000 EXT_STRUCT_CTRL(bbsfebex_data5trace_traces16)] /* [0,65535] */;
  uint32_t bbsfebex_data5trace_channel_id_traces /* [0,16] */;
  uint32_t bbsfebex_data5trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbsfebex_data5trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbsfebex_data5trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbsfebex_data5trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbsfebex_data6trig /* [0,255] */;
  uint32_t bbsfebex_data6event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbsfebex_data6event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbsfebex_data6hit_pattern /* [0,65535] */;
  uint32_t bbsfebex_data6num_channels_fired /* [-1,-1] */;
  uint32_t bbsfebex_data6board_num /* [0,255] */;
  uint32_t bbsfebex_data6channel_id /* [0,16] */;
  uint32_t bbsfebex_data6channel_idI[16 EXT_STRUCT_CTRL(bbsfebex_data6channel_id)] /* [1,16] */;
  uint32_t bbsfebex_data6channel_idv[16 EXT_STRUCT_CTRL(bbsfebex_data6channel_id)] /* [0,255] */;
  uint32_t bbsfebex_data6channel_trigger_time_hi /* [0,16] */;
  uint32_t bbsfebex_data6channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbsfebex_data6channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbsfebex_data6channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbsfebex_data6channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbsfebex_data6channel_trigger_time_lo /* [0,16] */;
  uint32_t bbsfebex_data6channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbsfebex_data6channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbsfebex_data6channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbsfebex_data6channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbsfebex_data6pileup /* [0,16] */;
  uint32_t bbsfebex_data6pileupI[16 EXT_STRUCT_CTRL(bbsfebex_data6pileup)] /* [1,16] */;
  uint32_t bbsfebex_data6pileupv[16 EXT_STRUCT_CTRL(bbsfebex_data6pileup)] /* [0,255] */;
  uint32_t bbsfebex_data6overflow /* [0,16] */;
  uint32_t bbsfebex_data6overflowI[16 EXT_STRUCT_CTRL(bbsfebex_data6overflow)] /* [1,16] */;
  uint32_t bbsfebex_data6overflowv[16 EXT_STRUCT_CTRL(bbsfebex_data6overflow)] /* [0,255] */;
  uint32_t bbsfebex_data6channel_cfd /* [0,16] */;
  uint32_t bbsfebex_data6channel_cfdI[16 EXT_STRUCT_CTRL(bbsfebex_data6channel_cfd)] /* [1,16] */;
  uint32_t bbsfebex_data6channel_cfdv[16 EXT_STRUCT_CTRL(bbsfebex_data6channel_cfd)] /* [0,255] */;
  uint32_t bbsfebex_data6channel_energy /* [0,16] */;
  uint32_t bbsfebex_data6channel_energyI[16 EXT_STRUCT_CTRL(bbsfebex_data6channel_energy)] /* [1,16] */;
  uint32_t bbsfebex_data6channel_energyv[16 EXT_STRUCT_CTRL(bbsfebex_data6channel_energy)] /* [-1,-1] */;
  uint32_t bbsfebex_data6trace_traces1 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces1I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces1)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces1v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces1)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces2 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces2I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces2)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces2v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces2)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces3 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces3I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces3)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces3v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces3)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces4 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces4I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces4)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces4v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces4)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces5 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces5I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces5)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces5v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces5)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces6 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces6I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces6)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces6v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces6)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces7 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces7I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces7)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces7v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces7)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces8 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces8I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces8)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces8v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces8)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces9 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces9I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces9)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces9v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces9)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces10 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces10I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces10)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces10v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces10)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces11 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces11I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces11)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces11v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces11)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces12 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces12I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces12)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces12v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces12)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces13 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces13I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces13)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces13v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces13)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces14 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces14I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces14)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces14v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces14)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces15 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces15I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces15)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces15v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces15)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_traces16 /* [0,4000] */;
  uint32_t bbsfebex_data6trace_traces16I[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces16)] /* [1,4000] */;
  uint32_t bbsfebex_data6trace_traces16v[4000 EXT_STRUCT_CTRL(bbsfebex_data6trace_traces16)] /* [0,65535] */;
  uint32_t bbsfebex_data6trace_channel_id_traces /* [0,16] */;
  uint32_t bbsfebex_data6trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbsfebex_data6trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbsfebex_data6trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbsfebex_data6trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbsfebex_data7trig /* [0,255] */;
  uint32_t bbsfebex_data7event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbsfebex_data7event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbsfebex_data7hit_pattern /* [0,65535] */;
  uint32_t bbsfebex_data7num_channels_fired /* [-1,-1] */;
  uint32_t bbsfebex_data7board_num /* [0,255] */;
  uint32_t bbsfebex_data7channel_id /* [0,16] */;
  uint32_t bbsfebex_data7channel_idI[16 EXT_STRUCT_CTRL(bbsfebex_data7channel_id)] /* [1,16] */;
  uint32_t bbsfebex_data7channel_idv[16 EXT_STRUCT_CTRL(bbsfebex_data7channel_id)] /* [0,255] */;
  uint32_t bbsfebex_data7channel_trigger_time_hi /* [0,16] */;
  uint32_t bbsfebex_data7channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbsfebex_data7channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbsfebex_data7channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbsfebex_data7channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbsfebex_data7channel_trigger_time_lo /* [0,16] */;
  uint32_t bbsfebex_data7channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbsfebex_data7channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbsfebex_data7channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbsfebex_data7channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbsfebex_data7pileup /* [0,16] */;
  uint32_t bbsfebex_data7pileupI[16 EXT_STRUCT_CTRL(bbsfebex_data7pileup)] /* [1,16] */;
  uint32_t bbsfebex_data7pileupv[16 EXT_STRUCT_CTRL(bbsfebex_data7pileup)] /* [0,255] */;
  uint32_t bbsfebex_data7overflow /* [0,16] */;
  uint32_t bbsfebex_data7overflowI[16 EXT_STRUCT_CTRL(bbsfebex_data7overflow)] /* [1,16] */;
  uint32_t bbsfebex_data7overflowv[16 EXT_STRUCT_CTRL(bbsfebex_data7overflow)] /* [0,255] */;
  uint32_t bbsfebex_data7channel_cfd /* [0,16] */;
  uint32_t bbsfebex_data7channel_cfdI[16 EXT_STRUCT_CTRL(bbsfebex_data7channel_cfd)] /* [1,16] */;
  uint32_t bbsfebex_data7channel_cfdv[16 EXT_STRUCT_CTRL(bbsfebex_data7channel_cfd)] /* [0,255] */;
  uint32_t bbsfebex_data7channel_energy /* [0,16] */;
  uint32_t bbsfebex_data7channel_energyI[16 EXT_STRUCT_CTRL(bbsfebex_data7channel_energy)] /* [1,16] */;
  uint32_t bbsfebex_data7channel_energyv[16 EXT_STRUCT_CTRL(bbsfebex_data7channel_energy)] /* [-1,-1] */;
  uint32_t bbsfebex_data7trace_traces1 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces1I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces1)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces1v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces1)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces2 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces2I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces2)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces2v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces2)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces3 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces3I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces3)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces3v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces3)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces4 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces4I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces4)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces4v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces4)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces5 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces5I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces5)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces5v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces5)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces6 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces6I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces6)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces6v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces6)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces7 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces7I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces7)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces7v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces7)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces8 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces8I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces8)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces8v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces8)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces9 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces9I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces9)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces9v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces9)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces10 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces10I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces10)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces10v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces10)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces11 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces11I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces11)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces11v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces11)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces12 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces12I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces12)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces12v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces12)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces13 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces13I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces13)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces13v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces13)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces14 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces14I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces14)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces14v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces14)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces15 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces15I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces15)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces15v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces15)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_traces16 /* [0,4000] */;
  uint32_t bbsfebex_data7trace_traces16I[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces16)] /* [1,4000] */;
  uint32_t bbsfebex_data7trace_traces16v[4000 EXT_STRUCT_CTRL(bbsfebex_data7trace_traces16)] /* [0,65535] */;
  uint32_t bbsfebex_data7trace_channel_id_traces /* [0,16] */;
  uint32_t bbsfebex_data7trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbsfebex_data7trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbsfebex_data7trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbsfebex_data7trace_channel_id_traces)] /* [0,255] */;
  uint32_t bbsfebex_data8trig /* [0,255] */;
  uint32_t bbsfebex_data8event_trigger_time_hi /* [-1,-1] */;
  uint32_t bbsfebex_data8event_trigger_time_lo /* [-1,-1] */;
  uint32_t bbsfebex_data8hit_pattern /* [0,65535] */;
  uint32_t bbsfebex_data8num_channels_fired /* [-1,-1] */;
  uint32_t bbsfebex_data8board_num /* [0,255] */;
  uint32_t bbsfebex_data8channel_id /* [0,16] */;
  uint32_t bbsfebex_data8channel_idI[16 EXT_STRUCT_CTRL(bbsfebex_data8channel_id)] /* [1,16] */;
  uint32_t bbsfebex_data8channel_idv[16 EXT_STRUCT_CTRL(bbsfebex_data8channel_id)] /* [0,255] */;
  uint32_t bbsfebex_data8channel_trigger_time_hi /* [0,16] */;
  uint32_t bbsfebex_data8channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(bbsfebex_data8channel_trigger_time_hi)] /* [1,16] */;
  uint32_t bbsfebex_data8channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(bbsfebex_data8channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t bbsfebex_data8channel_trigger_time_lo /* [0,16] */;
  uint32_t bbsfebex_data8channel_trigger_time_loI[16 EXT_STRUCT_CTRL(bbsfebex_data8channel_trigger_time_lo)] /* [1,16] */;
  uint32_t bbsfebex_data8channel_trigger_time_lov[16 EXT_STRUCT_CTRL(bbsfebex_data8channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t bbsfebex_data8pileup /* [0,16] */;
  uint32_t bbsfebex_data8pileupI[16 EXT_STRUCT_CTRL(bbsfebex_data8pileup)] /* [1,16] */;
  uint32_t bbsfebex_data8pileupv[16 EXT_STRUCT_CTRL(bbsfebex_data8pileup)] /* [0,255] */;
  uint32_t bbsfebex_data8overflow /* [0,16] */;
  uint32_t bbsfebex_data8overflowI[16 EXT_STRUCT_CTRL(bbsfebex_data8overflow)] /* [1,16] */;
  uint32_t bbsfebex_data8overflowv[16 EXT_STRUCT_CTRL(bbsfebex_data8overflow)] /* [0,255] */;
  uint32_t bbsfebex_data8channel_cfd /* [0,16] */;
  uint32_t bbsfebex_data8channel_cfdI[16 EXT_STRUCT_CTRL(bbsfebex_data8channel_cfd)] /* [1,16] */;
  uint32_t bbsfebex_data8channel_cfdv[16 EXT_STRUCT_CTRL(bbsfebex_data8channel_cfd)] /* [0,255] */;
  uint32_t bbsfebex_data8channel_energy /* [0,16] */;
  uint32_t bbsfebex_data8channel_energyI[16 EXT_STRUCT_CTRL(bbsfebex_data8channel_energy)] /* [1,16] */;
  uint32_t bbsfebex_data8channel_energyv[16 EXT_STRUCT_CTRL(bbsfebex_data8channel_energy)] /* [-1,-1] */;
  uint32_t bbsfebex_data8trace_traces1 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces1I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces1)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces1v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces1)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces2 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces2I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces2)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces2v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces2)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces3 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces3I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces3)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces3v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces3)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces4 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces4I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces4)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces4v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces4)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces5 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces5I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces5)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces5v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces5)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces6 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces6I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces6)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces6v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces6)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces7 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces7I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces7)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces7v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces7)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces8 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces8I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces8)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces8v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces8)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces9 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces9I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces9)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces9v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces9)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces10 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces10I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces10)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces10v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces10)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces11 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces11I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces11)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces11v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces11)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces12 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces12I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces12)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces12v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces12)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces13 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces13I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces13)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces13v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces13)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces14 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces14I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces14)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces14v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces14)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces15 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces15I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces15)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces15v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces15)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_traces16 /* [0,4000] */;
  uint32_t bbsfebex_data8trace_traces16I[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces16)] /* [1,4000] */;
  uint32_t bbsfebex_data8trace_traces16v[4000 EXT_STRUCT_CTRL(bbsfebex_data8trace_traces16)] /* [0,65535] */;
  uint32_t bbsfebex_data8trace_channel_id_traces /* [0,16] */;
  uint32_t bbsfebex_data8trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(bbsfebex_data8trace_channel_id_traces)] /* [1,16] */;
  uint32_t bbsfebex_data8trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(bbsfebex_data8trace_channel_id_traces)] /* [0,255] */;

} EXT_STR_h101_bb7febex;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_bb7febex_onion_t
{
  /* UNPACK */
  uint32_t bbsfebex_ts_subsystem_id;
  uint32_t bbsfebex_ts_t[4];
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
  } bbsfebex_data[8];

} EXT_STR_h101_bb7febex_onion;

/*******************************************************/

#define EXT_STR_h101_bb7febex_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_ts_subsystem_id,        UINT32,\
                    "bbsfebex_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_ts_t1,                  UINT32,\
                    "bbsfebex_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_ts_t2,                  UINT32,\
                    "bbsfebex_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_ts_t3,                  UINT32,\
                    "bbsfebex_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_ts_t4,                  UINT32,\
                    "bbsfebex_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trig,              UINT32,\
                    "bbsfebex_data1trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1event_trigger_time_hi,UINT32,\
                    "bbsfebex_data1event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1event_trigger_time_lo,UINT32,\
                    "bbsfebex_data1event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1hit_pattern,       UINT32,\
                    "bbsfebex_data1hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1num_channels_fired,UINT32,\
                    "bbsfebex_data1num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1board_num,         UINT32,\
                    "bbsfebex_data1board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_id,        UINT32,\
                    "bbsfebex_data1channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_idI,       UINT32,\
                    "bbsfebex_data1channel_idI",       "bbsfebex_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_idv,       UINT32,\
                    "bbsfebex_data1channel_idv",       "bbsfebex_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_trigger_time_hi,UINT32,\
                    "bbsfebex_data1channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_trigger_time_hiI,UINT32,\
                    "bbsfebex_data1channel_trigger_time_hiI","bbsfebex_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_trigger_time_hiv,UINT32,\
                    "bbsfebex_data1channel_trigger_time_hiv","bbsfebex_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_trigger_time_lo,UINT32,\
                    "bbsfebex_data1channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_trigger_time_loI,UINT32,\
                    "bbsfebex_data1channel_trigger_time_loI","bbsfebex_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_trigger_time_lov,UINT32,\
                    "bbsfebex_data1channel_trigger_time_lov","bbsfebex_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1pileup,            UINT32,\
                    "bbsfebex_data1pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1pileupI,           UINT32,\
                    "bbsfebex_data1pileupI",           "bbsfebex_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1pileupv,           UINT32,\
                    "bbsfebex_data1pileupv",           "bbsfebex_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1overflow,          UINT32,\
                    "bbsfebex_data1overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1overflowI,         UINT32,\
                    "bbsfebex_data1overflowI",         "bbsfebex_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1overflowv,         UINT32,\
                    "bbsfebex_data1overflowv",         "bbsfebex_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_cfd,       UINT32,\
                    "bbsfebex_data1channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_cfdI,      UINT32,\
                    "bbsfebex_data1channel_cfdI",      "bbsfebex_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_cfdv,      UINT32,\
                    "bbsfebex_data1channel_cfdv",      "bbsfebex_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_energy,    UINT32,\
                    "bbsfebex_data1channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_energyI,   UINT32,\
                    "bbsfebex_data1channel_energyI",   "bbsfebex_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1channel_energyv,   UINT32,\
                    "bbsfebex_data1channel_energyv",   "bbsfebex_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces1,     UINT32,\
                    "bbsfebex_data1trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces1I,    UINT32,\
                    "bbsfebex_data1trace_traces1I",    "bbsfebex_data1trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces1v,    UINT32,\
                    "bbsfebex_data1trace_traces1v",    "bbsfebex_data1trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces2,     UINT32,\
                    "bbsfebex_data1trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces2I,    UINT32,\
                    "bbsfebex_data1trace_traces2I",    "bbsfebex_data1trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces2v,    UINT32,\
                    "bbsfebex_data1trace_traces2v",    "bbsfebex_data1trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces3,     UINT32,\
                    "bbsfebex_data1trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces3I,    UINT32,\
                    "bbsfebex_data1trace_traces3I",    "bbsfebex_data1trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces3v,    UINT32,\
                    "bbsfebex_data1trace_traces3v",    "bbsfebex_data1trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces4,     UINT32,\
                    "bbsfebex_data1trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces4I,    UINT32,\
                    "bbsfebex_data1trace_traces4I",    "bbsfebex_data1trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces4v,    UINT32,\
                    "bbsfebex_data1trace_traces4v",    "bbsfebex_data1trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces5,     UINT32,\
                    "bbsfebex_data1trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces5I,    UINT32,\
                    "bbsfebex_data1trace_traces5I",    "bbsfebex_data1trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces5v,    UINT32,\
                    "bbsfebex_data1trace_traces5v",    "bbsfebex_data1trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces6,     UINT32,\
                    "bbsfebex_data1trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces6I,    UINT32,\
                    "bbsfebex_data1trace_traces6I",    "bbsfebex_data1trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces6v,    UINT32,\
                    "bbsfebex_data1trace_traces6v",    "bbsfebex_data1trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces7,     UINT32,\
                    "bbsfebex_data1trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces7I,    UINT32,\
                    "bbsfebex_data1trace_traces7I",    "bbsfebex_data1trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces7v,    UINT32,\
                    "bbsfebex_data1trace_traces7v",    "bbsfebex_data1trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces8,     UINT32,\
                    "bbsfebex_data1trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces8I,    UINT32,\
                    "bbsfebex_data1trace_traces8I",    "bbsfebex_data1trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces8v,    UINT32,\
                    "bbsfebex_data1trace_traces8v",    "bbsfebex_data1trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces9,     UINT32,\
                    "bbsfebex_data1trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces9I,    UINT32,\
                    "bbsfebex_data1trace_traces9I",    "bbsfebex_data1trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces9v,    UINT32,\
                    "bbsfebex_data1trace_traces9v",    "bbsfebex_data1trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces10,    UINT32,\
                    "bbsfebex_data1trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces10I,   UINT32,\
                    "bbsfebex_data1trace_traces10I",   "bbsfebex_data1trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces10v,   UINT32,\
                    "bbsfebex_data1trace_traces10v",   "bbsfebex_data1trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces11,    UINT32,\
                    "bbsfebex_data1trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces11I,   UINT32,\
                    "bbsfebex_data1trace_traces11I",   "bbsfebex_data1trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces11v,   UINT32,\
                    "bbsfebex_data1trace_traces11v",   "bbsfebex_data1trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces12,    UINT32,\
                    "bbsfebex_data1trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces12I,   UINT32,\
                    "bbsfebex_data1trace_traces12I",   "bbsfebex_data1trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces12v,   UINT32,\
                    "bbsfebex_data1trace_traces12v",   "bbsfebex_data1trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces13,    UINT32,\
                    "bbsfebex_data1trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces13I,   UINT32,\
                    "bbsfebex_data1trace_traces13I",   "bbsfebex_data1trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces13v,   UINT32,\
                    "bbsfebex_data1trace_traces13v",   "bbsfebex_data1trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces14,    UINT32,\
                    "bbsfebex_data1trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces14I,   UINT32,\
                    "bbsfebex_data1trace_traces14I",   "bbsfebex_data1trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces14v,   UINT32,\
                    "bbsfebex_data1trace_traces14v",   "bbsfebex_data1trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces15,    UINT32,\
                    "bbsfebex_data1trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces15I,   UINT32,\
                    "bbsfebex_data1trace_traces15I",   "bbsfebex_data1trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces15v,   UINT32,\
                    "bbsfebex_data1trace_traces15v",   "bbsfebex_data1trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces16,    UINT32,\
                    "bbsfebex_data1trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces16I,   UINT32,\
                    "bbsfebex_data1trace_traces16I",   "bbsfebex_data1trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_traces16v,   UINT32,\
                    "bbsfebex_data1trace_traces16v",   "bbsfebex_data1trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_channel_id_traces,UINT32,\
                    "bbsfebex_data1trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_channel_id_tracesI,UINT32,\
                    "bbsfebex_data1trace_channel_id_tracesI","bbsfebex_data1trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data1trace_channel_id_tracesv,UINT32,\
                    "bbsfebex_data1trace_channel_id_tracesv","bbsfebex_data1trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trig,              UINT32,\
                    "bbsfebex_data2trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2event_trigger_time_hi,UINT32,\
                    "bbsfebex_data2event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2event_trigger_time_lo,UINT32,\
                    "bbsfebex_data2event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2hit_pattern,       UINT32,\
                    "bbsfebex_data2hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2num_channels_fired,UINT32,\
                    "bbsfebex_data2num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2board_num,         UINT32,\
                    "bbsfebex_data2board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_id,        UINT32,\
                    "bbsfebex_data2channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_idI,       UINT32,\
                    "bbsfebex_data2channel_idI",       "bbsfebex_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_idv,       UINT32,\
                    "bbsfebex_data2channel_idv",       "bbsfebex_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_trigger_time_hi,UINT32,\
                    "bbsfebex_data2channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_trigger_time_hiI,UINT32,\
                    "bbsfebex_data2channel_trigger_time_hiI","bbsfebex_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_trigger_time_hiv,UINT32,\
                    "bbsfebex_data2channel_trigger_time_hiv","bbsfebex_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_trigger_time_lo,UINT32,\
                    "bbsfebex_data2channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_trigger_time_loI,UINT32,\
                    "bbsfebex_data2channel_trigger_time_loI","bbsfebex_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_trigger_time_lov,UINT32,\
                    "bbsfebex_data2channel_trigger_time_lov","bbsfebex_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2pileup,            UINT32,\
                    "bbsfebex_data2pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2pileupI,           UINT32,\
                    "bbsfebex_data2pileupI",           "bbsfebex_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2pileupv,           UINT32,\
                    "bbsfebex_data2pileupv",           "bbsfebex_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2overflow,          UINT32,\
                    "bbsfebex_data2overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2overflowI,         UINT32,\
                    "bbsfebex_data2overflowI",         "bbsfebex_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2overflowv,         UINT32,\
                    "bbsfebex_data2overflowv",         "bbsfebex_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_cfd,       UINT32,\
                    "bbsfebex_data2channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_cfdI,      UINT32,\
                    "bbsfebex_data2channel_cfdI",      "bbsfebex_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_cfdv,      UINT32,\
                    "bbsfebex_data2channel_cfdv",      "bbsfebex_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_energy,    UINT32,\
                    "bbsfebex_data2channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_energyI,   UINT32,\
                    "bbsfebex_data2channel_energyI",   "bbsfebex_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2channel_energyv,   UINT32,\
                    "bbsfebex_data2channel_energyv",   "bbsfebex_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces1,     UINT32,\
                    "bbsfebex_data2trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces1I,    UINT32,\
                    "bbsfebex_data2trace_traces1I",    "bbsfebex_data2trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces1v,    UINT32,\
                    "bbsfebex_data2trace_traces1v",    "bbsfebex_data2trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces2,     UINT32,\
                    "bbsfebex_data2trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces2I,    UINT32,\
                    "bbsfebex_data2trace_traces2I",    "bbsfebex_data2trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces2v,    UINT32,\
                    "bbsfebex_data2trace_traces2v",    "bbsfebex_data2trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces3,     UINT32,\
                    "bbsfebex_data2trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces3I,    UINT32,\
                    "bbsfebex_data2trace_traces3I",    "bbsfebex_data2trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces3v,    UINT32,\
                    "bbsfebex_data2trace_traces3v",    "bbsfebex_data2trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces4,     UINT32,\
                    "bbsfebex_data2trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces4I,    UINT32,\
                    "bbsfebex_data2trace_traces4I",    "bbsfebex_data2trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces4v,    UINT32,\
                    "bbsfebex_data2trace_traces4v",    "bbsfebex_data2trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces5,     UINT32,\
                    "bbsfebex_data2trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces5I,    UINT32,\
                    "bbsfebex_data2trace_traces5I",    "bbsfebex_data2trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces5v,    UINT32,\
                    "bbsfebex_data2trace_traces5v",    "bbsfebex_data2trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces6,     UINT32,\
                    "bbsfebex_data2trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces6I,    UINT32,\
                    "bbsfebex_data2trace_traces6I",    "bbsfebex_data2trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces6v,    UINT32,\
                    "bbsfebex_data2trace_traces6v",    "bbsfebex_data2trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces7,     UINT32,\
                    "bbsfebex_data2trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces7I,    UINT32,\
                    "bbsfebex_data2trace_traces7I",    "bbsfebex_data2trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces7v,    UINT32,\
                    "bbsfebex_data2trace_traces7v",    "bbsfebex_data2trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces8,     UINT32,\
                    "bbsfebex_data2trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces8I,    UINT32,\
                    "bbsfebex_data2trace_traces8I",    "bbsfebex_data2trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces8v,    UINT32,\
                    "bbsfebex_data2trace_traces8v",    "bbsfebex_data2trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces9,     UINT32,\
                    "bbsfebex_data2trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces9I,    UINT32,\
                    "bbsfebex_data2trace_traces9I",    "bbsfebex_data2trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces9v,    UINT32,\
                    "bbsfebex_data2trace_traces9v",    "bbsfebex_data2trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces10,    UINT32,\
                    "bbsfebex_data2trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces10I,   UINT32,\
                    "bbsfebex_data2trace_traces10I",   "bbsfebex_data2trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces10v,   UINT32,\
                    "bbsfebex_data2trace_traces10v",   "bbsfebex_data2trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces11,    UINT32,\
                    "bbsfebex_data2trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces11I,   UINT32,\
                    "bbsfebex_data2trace_traces11I",   "bbsfebex_data2trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces11v,   UINT32,\
                    "bbsfebex_data2trace_traces11v",   "bbsfebex_data2trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces12,    UINT32,\
                    "bbsfebex_data2trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces12I,   UINT32,\
                    "bbsfebex_data2trace_traces12I",   "bbsfebex_data2trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces12v,   UINT32,\
                    "bbsfebex_data2trace_traces12v",   "bbsfebex_data2trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces13,    UINT32,\
                    "bbsfebex_data2trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces13I,   UINT32,\
                    "bbsfebex_data2trace_traces13I",   "bbsfebex_data2trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces13v,   UINT32,\
                    "bbsfebex_data2trace_traces13v",   "bbsfebex_data2trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces14,    UINT32,\
                    "bbsfebex_data2trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces14I,   UINT32,\
                    "bbsfebex_data2trace_traces14I",   "bbsfebex_data2trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces14v,   UINT32,\
                    "bbsfebex_data2trace_traces14v",   "bbsfebex_data2trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces15,    UINT32,\
                    "bbsfebex_data2trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces15I,   UINT32,\
                    "bbsfebex_data2trace_traces15I",   "bbsfebex_data2trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces15v,   UINT32,\
                    "bbsfebex_data2trace_traces15v",   "bbsfebex_data2trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces16,    UINT32,\
                    "bbsfebex_data2trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces16I,   UINT32,\
                    "bbsfebex_data2trace_traces16I",   "bbsfebex_data2trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_traces16v,   UINT32,\
                    "bbsfebex_data2trace_traces16v",   "bbsfebex_data2trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_channel_id_traces,UINT32,\
                    "bbsfebex_data2trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_channel_id_tracesI,UINT32,\
                    "bbsfebex_data2trace_channel_id_tracesI","bbsfebex_data2trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data2trace_channel_id_tracesv,UINT32,\
                    "bbsfebex_data2trace_channel_id_tracesv","bbsfebex_data2trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trig,              UINT32,\
                    "bbsfebex_data3trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3event_trigger_time_hi,UINT32,\
                    "bbsfebex_data3event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3event_trigger_time_lo,UINT32,\
                    "bbsfebex_data3event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3hit_pattern,       UINT32,\
                    "bbsfebex_data3hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3num_channels_fired,UINT32,\
                    "bbsfebex_data3num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3board_num,         UINT32,\
                    "bbsfebex_data3board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_id,        UINT32,\
                    "bbsfebex_data3channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_idI,       UINT32,\
                    "bbsfebex_data3channel_idI",       "bbsfebex_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_idv,       UINT32,\
                    "bbsfebex_data3channel_idv",       "bbsfebex_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_trigger_time_hi,UINT32,\
                    "bbsfebex_data3channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_trigger_time_hiI,UINT32,\
                    "bbsfebex_data3channel_trigger_time_hiI","bbsfebex_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_trigger_time_hiv,UINT32,\
                    "bbsfebex_data3channel_trigger_time_hiv","bbsfebex_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_trigger_time_lo,UINT32,\
                    "bbsfebex_data3channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_trigger_time_loI,UINT32,\
                    "bbsfebex_data3channel_trigger_time_loI","bbsfebex_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_trigger_time_lov,UINT32,\
                    "bbsfebex_data3channel_trigger_time_lov","bbsfebex_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3pileup,            UINT32,\
                    "bbsfebex_data3pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3pileupI,           UINT32,\
                    "bbsfebex_data3pileupI",           "bbsfebex_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3pileupv,           UINT32,\
                    "bbsfebex_data3pileupv",           "bbsfebex_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3overflow,          UINT32,\
                    "bbsfebex_data3overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3overflowI,         UINT32,\
                    "bbsfebex_data3overflowI",         "bbsfebex_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3overflowv,         UINT32,\
                    "bbsfebex_data3overflowv",         "bbsfebex_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_cfd,       UINT32,\
                    "bbsfebex_data3channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_cfdI,      UINT32,\
                    "bbsfebex_data3channel_cfdI",      "bbsfebex_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_cfdv,      UINT32,\
                    "bbsfebex_data3channel_cfdv",      "bbsfebex_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_energy,    UINT32,\
                    "bbsfebex_data3channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_energyI,   UINT32,\
                    "bbsfebex_data3channel_energyI",   "bbsfebex_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3channel_energyv,   UINT32,\
                    "bbsfebex_data3channel_energyv",   "bbsfebex_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces1,     UINT32,\
                    "bbsfebex_data3trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces1I,    UINT32,\
                    "bbsfebex_data3trace_traces1I",    "bbsfebex_data3trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces1v,    UINT32,\
                    "bbsfebex_data3trace_traces1v",    "bbsfebex_data3trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces2,     UINT32,\
                    "bbsfebex_data3trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces2I,    UINT32,\
                    "bbsfebex_data3trace_traces2I",    "bbsfebex_data3trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces2v,    UINT32,\
                    "bbsfebex_data3trace_traces2v",    "bbsfebex_data3trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces3,     UINT32,\
                    "bbsfebex_data3trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces3I,    UINT32,\
                    "bbsfebex_data3trace_traces3I",    "bbsfebex_data3trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces3v,    UINT32,\
                    "bbsfebex_data3trace_traces3v",    "bbsfebex_data3trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces4,     UINT32,\
                    "bbsfebex_data3trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces4I,    UINT32,\
                    "bbsfebex_data3trace_traces4I",    "bbsfebex_data3trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces4v,    UINT32,\
                    "bbsfebex_data3trace_traces4v",    "bbsfebex_data3trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces5,     UINT32,\
                    "bbsfebex_data3trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces5I,    UINT32,\
                    "bbsfebex_data3trace_traces5I",    "bbsfebex_data3trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces5v,    UINT32,\
                    "bbsfebex_data3trace_traces5v",    "bbsfebex_data3trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces6,     UINT32,\
                    "bbsfebex_data3trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces6I,    UINT32,\
                    "bbsfebex_data3trace_traces6I",    "bbsfebex_data3trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces6v,    UINT32,\
                    "bbsfebex_data3trace_traces6v",    "bbsfebex_data3trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces7,     UINT32,\
                    "bbsfebex_data3trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces7I,    UINT32,\
                    "bbsfebex_data3trace_traces7I",    "bbsfebex_data3trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces7v,    UINT32,\
                    "bbsfebex_data3trace_traces7v",    "bbsfebex_data3trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces8,     UINT32,\
                    "bbsfebex_data3trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces8I,    UINT32,\
                    "bbsfebex_data3trace_traces8I",    "bbsfebex_data3trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces8v,    UINT32,\
                    "bbsfebex_data3trace_traces8v",    "bbsfebex_data3trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces9,     UINT32,\
                    "bbsfebex_data3trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces9I,    UINT32,\
                    "bbsfebex_data3trace_traces9I",    "bbsfebex_data3trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces9v,    UINT32,\
                    "bbsfebex_data3trace_traces9v",    "bbsfebex_data3trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces10,    UINT32,\
                    "bbsfebex_data3trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces10I,   UINT32,\
                    "bbsfebex_data3trace_traces10I",   "bbsfebex_data3trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces10v,   UINT32,\
                    "bbsfebex_data3trace_traces10v",   "bbsfebex_data3trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces11,    UINT32,\
                    "bbsfebex_data3trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces11I,   UINT32,\
                    "bbsfebex_data3trace_traces11I",   "bbsfebex_data3trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces11v,   UINT32,\
                    "bbsfebex_data3trace_traces11v",   "bbsfebex_data3trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces12,    UINT32,\
                    "bbsfebex_data3trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces12I,   UINT32,\
                    "bbsfebex_data3trace_traces12I",   "bbsfebex_data3trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces12v,   UINT32,\
                    "bbsfebex_data3trace_traces12v",   "bbsfebex_data3trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces13,    UINT32,\
                    "bbsfebex_data3trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces13I,   UINT32,\
                    "bbsfebex_data3trace_traces13I",   "bbsfebex_data3trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces13v,   UINT32,\
                    "bbsfebex_data3trace_traces13v",   "bbsfebex_data3trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces14,    UINT32,\
                    "bbsfebex_data3trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces14I,   UINT32,\
                    "bbsfebex_data3trace_traces14I",   "bbsfebex_data3trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces14v,   UINT32,\
                    "bbsfebex_data3trace_traces14v",   "bbsfebex_data3trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces15,    UINT32,\
                    "bbsfebex_data3trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces15I,   UINT32,\
                    "bbsfebex_data3trace_traces15I",   "bbsfebex_data3trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces15v,   UINT32,\
                    "bbsfebex_data3trace_traces15v",   "bbsfebex_data3trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces16,    UINT32,\
                    "bbsfebex_data3trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces16I,   UINT32,\
                    "bbsfebex_data3trace_traces16I",   "bbsfebex_data3trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_traces16v,   UINT32,\
                    "bbsfebex_data3trace_traces16v",   "bbsfebex_data3trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_channel_id_traces,UINT32,\
                    "bbsfebex_data3trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_channel_id_tracesI,UINT32,\
                    "bbsfebex_data3trace_channel_id_tracesI","bbsfebex_data3trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data3trace_channel_id_tracesv,UINT32,\
                    "bbsfebex_data3trace_channel_id_tracesv","bbsfebex_data3trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trig,              UINT32,\
                    "bbsfebex_data4trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4event_trigger_time_hi,UINT32,\
                    "bbsfebex_data4event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4event_trigger_time_lo,UINT32,\
                    "bbsfebex_data4event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4hit_pattern,       UINT32,\
                    "bbsfebex_data4hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4num_channels_fired,UINT32,\
                    "bbsfebex_data4num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4board_num,         UINT32,\
                    "bbsfebex_data4board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_id,        UINT32,\
                    "bbsfebex_data4channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_idI,       UINT32,\
                    "bbsfebex_data4channel_idI",       "bbsfebex_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_idv,       UINT32,\
                    "bbsfebex_data4channel_idv",       "bbsfebex_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_trigger_time_hi,UINT32,\
                    "bbsfebex_data4channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_trigger_time_hiI,UINT32,\
                    "bbsfebex_data4channel_trigger_time_hiI","bbsfebex_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_trigger_time_hiv,UINT32,\
                    "bbsfebex_data4channel_trigger_time_hiv","bbsfebex_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_trigger_time_lo,UINT32,\
                    "bbsfebex_data4channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_trigger_time_loI,UINT32,\
                    "bbsfebex_data4channel_trigger_time_loI","bbsfebex_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_trigger_time_lov,UINT32,\
                    "bbsfebex_data4channel_trigger_time_lov","bbsfebex_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4pileup,            UINT32,\
                    "bbsfebex_data4pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4pileupI,           UINT32,\
                    "bbsfebex_data4pileupI",           "bbsfebex_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4pileupv,           UINT32,\
                    "bbsfebex_data4pileupv",           "bbsfebex_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4overflow,          UINT32,\
                    "bbsfebex_data4overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4overflowI,         UINT32,\
                    "bbsfebex_data4overflowI",         "bbsfebex_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4overflowv,         UINT32,\
                    "bbsfebex_data4overflowv",         "bbsfebex_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_cfd,       UINT32,\
                    "bbsfebex_data4channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_cfdI,      UINT32,\
                    "bbsfebex_data4channel_cfdI",      "bbsfebex_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_cfdv,      UINT32,\
                    "bbsfebex_data4channel_cfdv",      "bbsfebex_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_energy,    UINT32,\
                    "bbsfebex_data4channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_energyI,   UINT32,\
                    "bbsfebex_data4channel_energyI",   "bbsfebex_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4channel_energyv,   UINT32,\
                    "bbsfebex_data4channel_energyv",   "bbsfebex_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces1,     UINT32,\
                    "bbsfebex_data4trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces1I,    UINT32,\
                    "bbsfebex_data4trace_traces1I",    "bbsfebex_data4trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces1v,    UINT32,\
                    "bbsfebex_data4trace_traces1v",    "bbsfebex_data4trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces2,     UINT32,\
                    "bbsfebex_data4trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces2I,    UINT32,\
                    "bbsfebex_data4trace_traces2I",    "bbsfebex_data4trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces2v,    UINT32,\
                    "bbsfebex_data4trace_traces2v",    "bbsfebex_data4trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces3,     UINT32,\
                    "bbsfebex_data4trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces3I,    UINT32,\
                    "bbsfebex_data4trace_traces3I",    "bbsfebex_data4trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces3v,    UINT32,\
                    "bbsfebex_data4trace_traces3v",    "bbsfebex_data4trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces4,     UINT32,\
                    "bbsfebex_data4trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces4I,    UINT32,\
                    "bbsfebex_data4trace_traces4I",    "bbsfebex_data4trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces4v,    UINT32,\
                    "bbsfebex_data4trace_traces4v",    "bbsfebex_data4trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces5,     UINT32,\
                    "bbsfebex_data4trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces5I,    UINT32,\
                    "bbsfebex_data4trace_traces5I",    "bbsfebex_data4trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces5v,    UINT32,\
                    "bbsfebex_data4trace_traces5v",    "bbsfebex_data4trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces6,     UINT32,\
                    "bbsfebex_data4trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces6I,    UINT32,\
                    "bbsfebex_data4trace_traces6I",    "bbsfebex_data4trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces6v,    UINT32,\
                    "bbsfebex_data4trace_traces6v",    "bbsfebex_data4trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces7,     UINT32,\
                    "bbsfebex_data4trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces7I,    UINT32,\
                    "bbsfebex_data4trace_traces7I",    "bbsfebex_data4trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces7v,    UINT32,\
                    "bbsfebex_data4trace_traces7v",    "bbsfebex_data4trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces8,     UINT32,\
                    "bbsfebex_data4trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces8I,    UINT32,\
                    "bbsfebex_data4trace_traces8I",    "bbsfebex_data4trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces8v,    UINT32,\
                    "bbsfebex_data4trace_traces8v",    "bbsfebex_data4trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces9,     UINT32,\
                    "bbsfebex_data4trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces9I,    UINT32,\
                    "bbsfebex_data4trace_traces9I",    "bbsfebex_data4trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces9v,    UINT32,\
                    "bbsfebex_data4trace_traces9v",    "bbsfebex_data4trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces10,    UINT32,\
                    "bbsfebex_data4trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces10I,   UINT32,\
                    "bbsfebex_data4trace_traces10I",   "bbsfebex_data4trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces10v,   UINT32,\
                    "bbsfebex_data4trace_traces10v",   "bbsfebex_data4trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces11,    UINT32,\
                    "bbsfebex_data4trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces11I,   UINT32,\
                    "bbsfebex_data4trace_traces11I",   "bbsfebex_data4trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces11v,   UINT32,\
                    "bbsfebex_data4trace_traces11v",   "bbsfebex_data4trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces12,    UINT32,\
                    "bbsfebex_data4trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces12I,   UINT32,\
                    "bbsfebex_data4trace_traces12I",   "bbsfebex_data4trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces12v,   UINT32,\
                    "bbsfebex_data4trace_traces12v",   "bbsfebex_data4trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces13,    UINT32,\
                    "bbsfebex_data4trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces13I,   UINT32,\
                    "bbsfebex_data4trace_traces13I",   "bbsfebex_data4trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces13v,   UINT32,\
                    "bbsfebex_data4trace_traces13v",   "bbsfebex_data4trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces14,    UINT32,\
                    "bbsfebex_data4trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces14I,   UINT32,\
                    "bbsfebex_data4trace_traces14I",   "bbsfebex_data4trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces14v,   UINT32,\
                    "bbsfebex_data4trace_traces14v",   "bbsfebex_data4trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces15,    UINT32,\
                    "bbsfebex_data4trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces15I,   UINT32,\
                    "bbsfebex_data4trace_traces15I",   "bbsfebex_data4trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces15v,   UINT32,\
                    "bbsfebex_data4trace_traces15v",   "bbsfebex_data4trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces16,    UINT32,\
                    "bbsfebex_data4trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces16I,   UINT32,\
                    "bbsfebex_data4trace_traces16I",   "bbsfebex_data4trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_traces16v,   UINT32,\
                    "bbsfebex_data4trace_traces16v",   "bbsfebex_data4trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_channel_id_traces,UINT32,\
                    "bbsfebex_data4trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_channel_id_tracesI,UINT32,\
                    "bbsfebex_data4trace_channel_id_tracesI","bbsfebex_data4trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data4trace_channel_id_tracesv,UINT32,\
                    "bbsfebex_data4trace_channel_id_tracesv","bbsfebex_data4trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trig,              UINT32,\
                    "bbsfebex_data5trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5event_trigger_time_hi,UINT32,\
                    "bbsfebex_data5event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5event_trigger_time_lo,UINT32,\
                    "bbsfebex_data5event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5hit_pattern,       UINT32,\
                    "bbsfebex_data5hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5num_channels_fired,UINT32,\
                    "bbsfebex_data5num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5board_num,         UINT32,\
                    "bbsfebex_data5board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_id,        UINT32,\
                    "bbsfebex_data5channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_idI,       UINT32,\
                    "bbsfebex_data5channel_idI",       "bbsfebex_data5channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_idv,       UINT32,\
                    "bbsfebex_data5channel_idv",       "bbsfebex_data5channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_trigger_time_hi,UINT32,\
                    "bbsfebex_data5channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_trigger_time_hiI,UINT32,\
                    "bbsfebex_data5channel_trigger_time_hiI","bbsfebex_data5channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_trigger_time_hiv,UINT32,\
                    "bbsfebex_data5channel_trigger_time_hiv","bbsfebex_data5channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_trigger_time_lo,UINT32,\
                    "bbsfebex_data5channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_trigger_time_loI,UINT32,\
                    "bbsfebex_data5channel_trigger_time_loI","bbsfebex_data5channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_trigger_time_lov,UINT32,\
                    "bbsfebex_data5channel_trigger_time_lov","bbsfebex_data5channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5pileup,            UINT32,\
                    "bbsfebex_data5pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5pileupI,           UINT32,\
                    "bbsfebex_data5pileupI",           "bbsfebex_data5pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5pileupv,           UINT32,\
                    "bbsfebex_data5pileupv",           "bbsfebex_data5pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5overflow,          UINT32,\
                    "bbsfebex_data5overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5overflowI,         UINT32,\
                    "bbsfebex_data5overflowI",         "bbsfebex_data5overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5overflowv,         UINT32,\
                    "bbsfebex_data5overflowv",         "bbsfebex_data5overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_cfd,       UINT32,\
                    "bbsfebex_data5channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_cfdI,      UINT32,\
                    "bbsfebex_data5channel_cfdI",      "bbsfebex_data5channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_cfdv,      UINT32,\
                    "bbsfebex_data5channel_cfdv",      "bbsfebex_data5channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_energy,    UINT32,\
                    "bbsfebex_data5channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_energyI,   UINT32,\
                    "bbsfebex_data5channel_energyI",   "bbsfebex_data5channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5channel_energyv,   UINT32,\
                    "bbsfebex_data5channel_energyv",   "bbsfebex_data5channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces1,     UINT32,\
                    "bbsfebex_data5trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces1I,    UINT32,\
                    "bbsfebex_data5trace_traces1I",    "bbsfebex_data5trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces1v,    UINT32,\
                    "bbsfebex_data5trace_traces1v",    "bbsfebex_data5trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces2,     UINT32,\
                    "bbsfebex_data5trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces2I,    UINT32,\
                    "bbsfebex_data5trace_traces2I",    "bbsfebex_data5trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces2v,    UINT32,\
                    "bbsfebex_data5trace_traces2v",    "bbsfebex_data5trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces3,     UINT32,\
                    "bbsfebex_data5trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces3I,    UINT32,\
                    "bbsfebex_data5trace_traces3I",    "bbsfebex_data5trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces3v,    UINT32,\
                    "bbsfebex_data5trace_traces3v",    "bbsfebex_data5trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces4,     UINT32,\
                    "bbsfebex_data5trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces4I,    UINT32,\
                    "bbsfebex_data5trace_traces4I",    "bbsfebex_data5trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces4v,    UINT32,\
                    "bbsfebex_data5trace_traces4v",    "bbsfebex_data5trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces5,     UINT32,\
                    "bbsfebex_data5trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces5I,    UINT32,\
                    "bbsfebex_data5trace_traces5I",    "bbsfebex_data5trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces5v,    UINT32,\
                    "bbsfebex_data5trace_traces5v",    "bbsfebex_data5trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces6,     UINT32,\
                    "bbsfebex_data5trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces6I,    UINT32,\
                    "bbsfebex_data5trace_traces6I",    "bbsfebex_data5trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces6v,    UINT32,\
                    "bbsfebex_data5trace_traces6v",    "bbsfebex_data5trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces7,     UINT32,\
                    "bbsfebex_data5trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces7I,    UINT32,\
                    "bbsfebex_data5trace_traces7I",    "bbsfebex_data5trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces7v,    UINT32,\
                    "bbsfebex_data5trace_traces7v",    "bbsfebex_data5trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces8,     UINT32,\
                    "bbsfebex_data5trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces8I,    UINT32,\
                    "bbsfebex_data5trace_traces8I",    "bbsfebex_data5trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces8v,    UINT32,\
                    "bbsfebex_data5trace_traces8v",    "bbsfebex_data5trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces9,     UINT32,\
                    "bbsfebex_data5trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces9I,    UINT32,\
                    "bbsfebex_data5trace_traces9I",    "bbsfebex_data5trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces9v,    UINT32,\
                    "bbsfebex_data5trace_traces9v",    "bbsfebex_data5trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces10,    UINT32,\
                    "bbsfebex_data5trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces10I,   UINT32,\
                    "bbsfebex_data5trace_traces10I",   "bbsfebex_data5trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces10v,   UINT32,\
                    "bbsfebex_data5trace_traces10v",   "bbsfebex_data5trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces11,    UINT32,\
                    "bbsfebex_data5trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces11I,   UINT32,\
                    "bbsfebex_data5trace_traces11I",   "bbsfebex_data5trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces11v,   UINT32,\
                    "bbsfebex_data5trace_traces11v",   "bbsfebex_data5trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces12,    UINT32,\
                    "bbsfebex_data5trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces12I,   UINT32,\
                    "bbsfebex_data5trace_traces12I",   "bbsfebex_data5trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces12v,   UINT32,\
                    "bbsfebex_data5trace_traces12v",   "bbsfebex_data5trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces13,    UINT32,\
                    "bbsfebex_data5trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces13I,   UINT32,\
                    "bbsfebex_data5trace_traces13I",   "bbsfebex_data5trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces13v,   UINT32,\
                    "bbsfebex_data5trace_traces13v",   "bbsfebex_data5trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces14,    UINT32,\
                    "bbsfebex_data5trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces14I,   UINT32,\
                    "bbsfebex_data5trace_traces14I",   "bbsfebex_data5trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces14v,   UINT32,\
                    "bbsfebex_data5trace_traces14v",   "bbsfebex_data5trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces15,    UINT32,\
                    "bbsfebex_data5trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces15I,   UINT32,\
                    "bbsfebex_data5trace_traces15I",   "bbsfebex_data5trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces15v,   UINT32,\
                    "bbsfebex_data5trace_traces15v",   "bbsfebex_data5trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces16,    UINT32,\
                    "bbsfebex_data5trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces16I,   UINT32,\
                    "bbsfebex_data5trace_traces16I",   "bbsfebex_data5trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_traces16v,   UINT32,\
                    "bbsfebex_data5trace_traces16v",   "bbsfebex_data5trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_channel_id_traces,UINT32,\
                    "bbsfebex_data5trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_channel_id_tracesI,UINT32,\
                    "bbsfebex_data5trace_channel_id_tracesI","bbsfebex_data5trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data5trace_channel_id_tracesv,UINT32,\
                    "bbsfebex_data5trace_channel_id_tracesv","bbsfebex_data5trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trig,              UINT32,\
                    "bbsfebex_data6trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6event_trigger_time_hi,UINT32,\
                    "bbsfebex_data6event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6event_trigger_time_lo,UINT32,\
                    "bbsfebex_data6event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6hit_pattern,       UINT32,\
                    "bbsfebex_data6hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6num_channels_fired,UINT32,\
                    "bbsfebex_data6num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6board_num,         UINT32,\
                    "bbsfebex_data6board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_id,        UINT32,\
                    "bbsfebex_data6channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_idI,       UINT32,\
                    "bbsfebex_data6channel_idI",       "bbsfebex_data6channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_idv,       UINT32,\
                    "bbsfebex_data6channel_idv",       "bbsfebex_data6channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_trigger_time_hi,UINT32,\
                    "bbsfebex_data6channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_trigger_time_hiI,UINT32,\
                    "bbsfebex_data6channel_trigger_time_hiI","bbsfebex_data6channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_trigger_time_hiv,UINT32,\
                    "bbsfebex_data6channel_trigger_time_hiv","bbsfebex_data6channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_trigger_time_lo,UINT32,\
                    "bbsfebex_data6channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_trigger_time_loI,UINT32,\
                    "bbsfebex_data6channel_trigger_time_loI","bbsfebex_data6channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_trigger_time_lov,UINT32,\
                    "bbsfebex_data6channel_trigger_time_lov","bbsfebex_data6channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6pileup,            UINT32,\
                    "bbsfebex_data6pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6pileupI,           UINT32,\
                    "bbsfebex_data6pileupI",           "bbsfebex_data6pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6pileupv,           UINT32,\
                    "bbsfebex_data6pileupv",           "bbsfebex_data6pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6overflow,          UINT32,\
                    "bbsfebex_data6overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6overflowI,         UINT32,\
                    "bbsfebex_data6overflowI",         "bbsfebex_data6overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6overflowv,         UINT32,\
                    "bbsfebex_data6overflowv",         "bbsfebex_data6overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_cfd,       UINT32,\
                    "bbsfebex_data6channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_cfdI,      UINT32,\
                    "bbsfebex_data6channel_cfdI",      "bbsfebex_data6channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_cfdv,      UINT32,\
                    "bbsfebex_data6channel_cfdv",      "bbsfebex_data6channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_energy,    UINT32,\
                    "bbsfebex_data6channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_energyI,   UINT32,\
                    "bbsfebex_data6channel_energyI",   "bbsfebex_data6channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6channel_energyv,   UINT32,\
                    "bbsfebex_data6channel_energyv",   "bbsfebex_data6channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces1,     UINT32,\
                    "bbsfebex_data6trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces1I,    UINT32,\
                    "bbsfebex_data6trace_traces1I",    "bbsfebex_data6trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces1v,    UINT32,\
                    "bbsfebex_data6trace_traces1v",    "bbsfebex_data6trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces2,     UINT32,\
                    "bbsfebex_data6trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces2I,    UINT32,\
                    "bbsfebex_data6trace_traces2I",    "bbsfebex_data6trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces2v,    UINT32,\
                    "bbsfebex_data6trace_traces2v",    "bbsfebex_data6trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces3,     UINT32,\
                    "bbsfebex_data6trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces3I,    UINT32,\
                    "bbsfebex_data6trace_traces3I",    "bbsfebex_data6trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces3v,    UINT32,\
                    "bbsfebex_data6trace_traces3v",    "bbsfebex_data6trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces4,     UINT32,\
                    "bbsfebex_data6trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces4I,    UINT32,\
                    "bbsfebex_data6trace_traces4I",    "bbsfebex_data6trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces4v,    UINT32,\
                    "bbsfebex_data6trace_traces4v",    "bbsfebex_data6trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces5,     UINT32,\
                    "bbsfebex_data6trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces5I,    UINT32,\
                    "bbsfebex_data6trace_traces5I",    "bbsfebex_data6trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces5v,    UINT32,\
                    "bbsfebex_data6trace_traces5v",    "bbsfebex_data6trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces6,     UINT32,\
                    "bbsfebex_data6trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces6I,    UINT32,\
                    "bbsfebex_data6trace_traces6I",    "bbsfebex_data6trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces6v,    UINT32,\
                    "bbsfebex_data6trace_traces6v",    "bbsfebex_data6trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces7,     UINT32,\
                    "bbsfebex_data6trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces7I,    UINT32,\
                    "bbsfebex_data6trace_traces7I",    "bbsfebex_data6trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces7v,    UINT32,\
                    "bbsfebex_data6trace_traces7v",    "bbsfebex_data6trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces8,     UINT32,\
                    "bbsfebex_data6trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces8I,    UINT32,\
                    "bbsfebex_data6trace_traces8I",    "bbsfebex_data6trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces8v,    UINT32,\
                    "bbsfebex_data6trace_traces8v",    "bbsfebex_data6trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces9,     UINT32,\
                    "bbsfebex_data6trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces9I,    UINT32,\
                    "bbsfebex_data6trace_traces9I",    "bbsfebex_data6trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces9v,    UINT32,\
                    "bbsfebex_data6trace_traces9v",    "bbsfebex_data6trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces10,    UINT32,\
                    "bbsfebex_data6trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces10I,   UINT32,\
                    "bbsfebex_data6trace_traces10I",   "bbsfebex_data6trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces10v,   UINT32,\
                    "bbsfebex_data6trace_traces10v",   "bbsfebex_data6trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces11,    UINT32,\
                    "bbsfebex_data6trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces11I,   UINT32,\
                    "bbsfebex_data6trace_traces11I",   "bbsfebex_data6trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces11v,   UINT32,\
                    "bbsfebex_data6trace_traces11v",   "bbsfebex_data6trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces12,    UINT32,\
                    "bbsfebex_data6trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces12I,   UINT32,\
                    "bbsfebex_data6trace_traces12I",   "bbsfebex_data6trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces12v,   UINT32,\
                    "bbsfebex_data6trace_traces12v",   "bbsfebex_data6trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces13,    UINT32,\
                    "bbsfebex_data6trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces13I,   UINT32,\
                    "bbsfebex_data6trace_traces13I",   "bbsfebex_data6trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces13v,   UINT32,\
                    "bbsfebex_data6trace_traces13v",   "bbsfebex_data6trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces14,    UINT32,\
                    "bbsfebex_data6trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces14I,   UINT32,\
                    "bbsfebex_data6trace_traces14I",   "bbsfebex_data6trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces14v,   UINT32,\
                    "bbsfebex_data6trace_traces14v",   "bbsfebex_data6trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces15,    UINT32,\
                    "bbsfebex_data6trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces15I,   UINT32,\
                    "bbsfebex_data6trace_traces15I",   "bbsfebex_data6trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces15v,   UINT32,\
                    "bbsfebex_data6trace_traces15v",   "bbsfebex_data6trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces16,    UINT32,\
                    "bbsfebex_data6trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces16I,   UINT32,\
                    "bbsfebex_data6trace_traces16I",   "bbsfebex_data6trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_traces16v,   UINT32,\
                    "bbsfebex_data6trace_traces16v",   "bbsfebex_data6trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_channel_id_traces,UINT32,\
                    "bbsfebex_data6trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_channel_id_tracesI,UINT32,\
                    "bbsfebex_data6trace_channel_id_tracesI","bbsfebex_data6trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data6trace_channel_id_tracesv,UINT32,\
                    "bbsfebex_data6trace_channel_id_tracesv","bbsfebex_data6trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trig,              UINT32,\
                    "bbsfebex_data7trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7event_trigger_time_hi,UINT32,\
                    "bbsfebex_data7event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7event_trigger_time_lo,UINT32,\
                    "bbsfebex_data7event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7hit_pattern,       UINT32,\
                    "bbsfebex_data7hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7num_channels_fired,UINT32,\
                    "bbsfebex_data7num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7board_num,         UINT32,\
                    "bbsfebex_data7board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_id,        UINT32,\
                    "bbsfebex_data7channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_idI,       UINT32,\
                    "bbsfebex_data7channel_idI",       "bbsfebex_data7channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_idv,       UINT32,\
                    "bbsfebex_data7channel_idv",       "bbsfebex_data7channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_trigger_time_hi,UINT32,\
                    "bbsfebex_data7channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_trigger_time_hiI,UINT32,\
                    "bbsfebex_data7channel_trigger_time_hiI","bbsfebex_data7channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_trigger_time_hiv,UINT32,\
                    "bbsfebex_data7channel_trigger_time_hiv","bbsfebex_data7channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_trigger_time_lo,UINT32,\
                    "bbsfebex_data7channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_trigger_time_loI,UINT32,\
                    "bbsfebex_data7channel_trigger_time_loI","bbsfebex_data7channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_trigger_time_lov,UINT32,\
                    "bbsfebex_data7channel_trigger_time_lov","bbsfebex_data7channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7pileup,            UINT32,\
                    "bbsfebex_data7pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7pileupI,           UINT32,\
                    "bbsfebex_data7pileupI",           "bbsfebex_data7pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7pileupv,           UINT32,\
                    "bbsfebex_data7pileupv",           "bbsfebex_data7pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7overflow,          UINT32,\
                    "bbsfebex_data7overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7overflowI,         UINT32,\
                    "bbsfebex_data7overflowI",         "bbsfebex_data7overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7overflowv,         UINT32,\
                    "bbsfebex_data7overflowv",         "bbsfebex_data7overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_cfd,       UINT32,\
                    "bbsfebex_data7channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_cfdI,      UINT32,\
                    "bbsfebex_data7channel_cfdI",      "bbsfebex_data7channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_cfdv,      UINT32,\
                    "bbsfebex_data7channel_cfdv",      "bbsfebex_data7channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_energy,    UINT32,\
                    "bbsfebex_data7channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_energyI,   UINT32,\
                    "bbsfebex_data7channel_energyI",   "bbsfebex_data7channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7channel_energyv,   UINT32,\
                    "bbsfebex_data7channel_energyv",   "bbsfebex_data7channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces1,     UINT32,\
                    "bbsfebex_data7trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces1I,    UINT32,\
                    "bbsfebex_data7trace_traces1I",    "bbsfebex_data7trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces1v,    UINT32,\
                    "bbsfebex_data7trace_traces1v",    "bbsfebex_data7trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces2,     UINT32,\
                    "bbsfebex_data7trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces2I,    UINT32,\
                    "bbsfebex_data7trace_traces2I",    "bbsfebex_data7trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces2v,    UINT32,\
                    "bbsfebex_data7trace_traces2v",    "bbsfebex_data7trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces3,     UINT32,\
                    "bbsfebex_data7trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces3I,    UINT32,\
                    "bbsfebex_data7trace_traces3I",    "bbsfebex_data7trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces3v,    UINT32,\
                    "bbsfebex_data7trace_traces3v",    "bbsfebex_data7trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces4,     UINT32,\
                    "bbsfebex_data7trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces4I,    UINT32,\
                    "bbsfebex_data7trace_traces4I",    "bbsfebex_data7trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces4v,    UINT32,\
                    "bbsfebex_data7trace_traces4v",    "bbsfebex_data7trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces5,     UINT32,\
                    "bbsfebex_data7trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces5I,    UINT32,\
                    "bbsfebex_data7trace_traces5I",    "bbsfebex_data7trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces5v,    UINT32,\
                    "bbsfebex_data7trace_traces5v",    "bbsfebex_data7trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces6,     UINT32,\
                    "bbsfebex_data7trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces6I,    UINT32,\
                    "bbsfebex_data7trace_traces6I",    "bbsfebex_data7trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces6v,    UINT32,\
                    "bbsfebex_data7trace_traces6v",    "bbsfebex_data7trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces7,     UINT32,\
                    "bbsfebex_data7trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces7I,    UINT32,\
                    "bbsfebex_data7trace_traces7I",    "bbsfebex_data7trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces7v,    UINT32,\
                    "bbsfebex_data7trace_traces7v",    "bbsfebex_data7trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces8,     UINT32,\
                    "bbsfebex_data7trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces8I,    UINT32,\
                    "bbsfebex_data7trace_traces8I",    "bbsfebex_data7trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces8v,    UINT32,\
                    "bbsfebex_data7trace_traces8v",    "bbsfebex_data7trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces9,     UINT32,\
                    "bbsfebex_data7trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces9I,    UINT32,\
                    "bbsfebex_data7trace_traces9I",    "bbsfebex_data7trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces9v,    UINT32,\
                    "bbsfebex_data7trace_traces9v",    "bbsfebex_data7trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces10,    UINT32,\
                    "bbsfebex_data7trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces10I,   UINT32,\
                    "bbsfebex_data7trace_traces10I",   "bbsfebex_data7trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces10v,   UINT32,\
                    "bbsfebex_data7trace_traces10v",   "bbsfebex_data7trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces11,    UINT32,\
                    "bbsfebex_data7trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces11I,   UINT32,\
                    "bbsfebex_data7trace_traces11I",   "bbsfebex_data7trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces11v,   UINT32,\
                    "bbsfebex_data7trace_traces11v",   "bbsfebex_data7trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces12,    UINT32,\
                    "bbsfebex_data7trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces12I,   UINT32,\
                    "bbsfebex_data7trace_traces12I",   "bbsfebex_data7trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces12v,   UINT32,\
                    "bbsfebex_data7trace_traces12v",   "bbsfebex_data7trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces13,    UINT32,\
                    "bbsfebex_data7trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces13I,   UINT32,\
                    "bbsfebex_data7trace_traces13I",   "bbsfebex_data7trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces13v,   UINT32,\
                    "bbsfebex_data7trace_traces13v",   "bbsfebex_data7trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces14,    UINT32,\
                    "bbsfebex_data7trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces14I,   UINT32,\
                    "bbsfebex_data7trace_traces14I",   "bbsfebex_data7trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces14v,   UINT32,\
                    "bbsfebex_data7trace_traces14v",   "bbsfebex_data7trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces15,    UINT32,\
                    "bbsfebex_data7trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces15I,   UINT32,\
                    "bbsfebex_data7trace_traces15I",   "bbsfebex_data7trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces15v,   UINT32,\
                    "bbsfebex_data7trace_traces15v",   "bbsfebex_data7trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces16,    UINT32,\
                    "bbsfebex_data7trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces16I,   UINT32,\
                    "bbsfebex_data7trace_traces16I",   "bbsfebex_data7trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_traces16v,   UINT32,\
                    "bbsfebex_data7trace_traces16v",   "bbsfebex_data7trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_channel_id_traces,UINT32,\
                    "bbsfebex_data7trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_channel_id_tracesI,UINT32,\
                    "bbsfebex_data7trace_channel_id_tracesI","bbsfebex_data7trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data7trace_channel_id_tracesv,UINT32,\
                    "bbsfebex_data7trace_channel_id_tracesv","bbsfebex_data7trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trig,              UINT32,\
                    "bbsfebex_data8trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8event_trigger_time_hi,UINT32,\
                    "bbsfebex_data8event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8event_trigger_time_lo,UINT32,\
                    "bbsfebex_data8event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8hit_pattern,       UINT32,\
                    "bbsfebex_data8hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8num_channels_fired,UINT32,\
                    "bbsfebex_data8num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8board_num,         UINT32,\
                    "bbsfebex_data8board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_id,        UINT32,\
                    "bbsfebex_data8channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_idI,       UINT32,\
                    "bbsfebex_data8channel_idI",       "bbsfebex_data8channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_idv,       UINT32,\
                    "bbsfebex_data8channel_idv",       "bbsfebex_data8channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_trigger_time_hi,UINT32,\
                    "bbsfebex_data8channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_trigger_time_hiI,UINT32,\
                    "bbsfebex_data8channel_trigger_time_hiI","bbsfebex_data8channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_trigger_time_hiv,UINT32,\
                    "bbsfebex_data8channel_trigger_time_hiv","bbsfebex_data8channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_trigger_time_lo,UINT32,\
                    "bbsfebex_data8channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_trigger_time_loI,UINT32,\
                    "bbsfebex_data8channel_trigger_time_loI","bbsfebex_data8channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_trigger_time_lov,UINT32,\
                    "bbsfebex_data8channel_trigger_time_lov","bbsfebex_data8channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8pileup,            UINT32,\
                    "bbsfebex_data8pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8pileupI,           UINT32,\
                    "bbsfebex_data8pileupI",           "bbsfebex_data8pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8pileupv,           UINT32,\
                    "bbsfebex_data8pileupv",           "bbsfebex_data8pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8overflow,          UINT32,\
                    "bbsfebex_data8overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8overflowI,         UINT32,\
                    "bbsfebex_data8overflowI",         "bbsfebex_data8overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8overflowv,         UINT32,\
                    "bbsfebex_data8overflowv",         "bbsfebex_data8overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_cfd,       UINT32,\
                    "bbsfebex_data8channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_cfdI,      UINT32,\
                    "bbsfebex_data8channel_cfdI",      "bbsfebex_data8channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_cfdv,      UINT32,\
                    "bbsfebex_data8channel_cfdv",      "bbsfebex_data8channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_energy,    UINT32,\
                    "bbsfebex_data8channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_energyI,   UINT32,\
                    "bbsfebex_data8channel_energyI",   "bbsfebex_data8channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8channel_energyv,   UINT32,\
                    "bbsfebex_data8channel_energyv",   "bbsfebex_data8channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces1,     UINT32,\
                    "bbsfebex_data8trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces1I,    UINT32,\
                    "bbsfebex_data8trace_traces1I",    "bbsfebex_data8trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces1v,    UINT32,\
                    "bbsfebex_data8trace_traces1v",    "bbsfebex_data8trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces2,     UINT32,\
                    "bbsfebex_data8trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces2I,    UINT32,\
                    "bbsfebex_data8trace_traces2I",    "bbsfebex_data8trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces2v,    UINT32,\
                    "bbsfebex_data8trace_traces2v",    "bbsfebex_data8trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces3,     UINT32,\
                    "bbsfebex_data8trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces3I,    UINT32,\
                    "bbsfebex_data8trace_traces3I",    "bbsfebex_data8trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces3v,    UINT32,\
                    "bbsfebex_data8trace_traces3v",    "bbsfebex_data8trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces4,     UINT32,\
                    "bbsfebex_data8trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces4I,    UINT32,\
                    "bbsfebex_data8trace_traces4I",    "bbsfebex_data8trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces4v,    UINT32,\
                    "bbsfebex_data8trace_traces4v",    "bbsfebex_data8trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces5,     UINT32,\
                    "bbsfebex_data8trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces5I,    UINT32,\
                    "bbsfebex_data8trace_traces5I",    "bbsfebex_data8trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces5v,    UINT32,\
                    "bbsfebex_data8trace_traces5v",    "bbsfebex_data8trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces6,     UINT32,\
                    "bbsfebex_data8trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces6I,    UINT32,\
                    "bbsfebex_data8trace_traces6I",    "bbsfebex_data8trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces6v,    UINT32,\
                    "bbsfebex_data8trace_traces6v",    "bbsfebex_data8trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces7,     UINT32,\
                    "bbsfebex_data8trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces7I,    UINT32,\
                    "bbsfebex_data8trace_traces7I",    "bbsfebex_data8trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces7v,    UINT32,\
                    "bbsfebex_data8trace_traces7v",    "bbsfebex_data8trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces8,     UINT32,\
                    "bbsfebex_data8trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces8I,    UINT32,\
                    "bbsfebex_data8trace_traces8I",    "bbsfebex_data8trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces8v,    UINT32,\
                    "bbsfebex_data8trace_traces8v",    "bbsfebex_data8trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces9,     UINT32,\
                    "bbsfebex_data8trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces9I,    UINT32,\
                    "bbsfebex_data8trace_traces9I",    "bbsfebex_data8trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces9v,    UINT32,\
                    "bbsfebex_data8trace_traces9v",    "bbsfebex_data8trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces10,    UINT32,\
                    "bbsfebex_data8trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces10I,   UINT32,\
                    "bbsfebex_data8trace_traces10I",   "bbsfebex_data8trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces10v,   UINT32,\
                    "bbsfebex_data8trace_traces10v",   "bbsfebex_data8trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces11,    UINT32,\
                    "bbsfebex_data8trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces11I,   UINT32,\
                    "bbsfebex_data8trace_traces11I",   "bbsfebex_data8trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces11v,   UINT32,\
                    "bbsfebex_data8trace_traces11v",   "bbsfebex_data8trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces12,    UINT32,\
                    "bbsfebex_data8trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces12I,   UINT32,\
                    "bbsfebex_data8trace_traces12I",   "bbsfebex_data8trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces12v,   UINT32,\
                    "bbsfebex_data8trace_traces12v",   "bbsfebex_data8trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces13,    UINT32,\
                    "bbsfebex_data8trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces13I,   UINT32,\
                    "bbsfebex_data8trace_traces13I",   "bbsfebex_data8trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces13v,   UINT32,\
                    "bbsfebex_data8trace_traces13v",   "bbsfebex_data8trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces14,    UINT32,\
                    "bbsfebex_data8trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces14I,   UINT32,\
                    "bbsfebex_data8trace_traces14I",   "bbsfebex_data8trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces14v,   UINT32,\
                    "bbsfebex_data8trace_traces14v",   "bbsfebex_data8trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces15,    UINT32,\
                    "bbsfebex_data8trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces15I,   UINT32,\
                    "bbsfebex_data8trace_traces15I",   "bbsfebex_data8trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces15v,   UINT32,\
                    "bbsfebex_data8trace_traces15v",   "bbsfebex_data8trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces16,    UINT32,\
                    "bbsfebex_data8trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces16I,   UINT32,\
                    "bbsfebex_data8trace_traces16I",   "bbsfebex_data8trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_traces16v,   UINT32,\
                    "bbsfebex_data8trace_traces16v",   "bbsfebex_data8trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_channel_id_traces,UINT32,\
                    "bbsfebex_data8trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_channel_id_tracesI,UINT32,\
                    "bbsfebex_data8trace_channel_id_tracesI","bbsfebex_data8trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     bbsfebex_data8trace_channel_id_tracesv,UINT32,\
                    "bbsfebex_data8trace_channel_id_tracesv","bbsfebex_data8trace_channel_id_traces",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_BB7FEBEX_EXT_H101_BB7FEBEX_H__*/

/*******************************************************/
