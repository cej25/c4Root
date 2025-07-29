/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_AGATA_EXT_H101_AGATA_H__
#define __GUARD_H101_AGATA_EXT_H101_AGATA_H__

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

typedef struct EXT_STR_h101_agata_t
{
  /* UNPACK */
  uint32_t agata_badevent_bad /* [0,255] */;
  uint32_t agata_ts_subsystem_id /* [0,65535] */;
  uint32_t agata_ts_t1 /* [0,65535] */;
  uint32_t agata_ts_t2 /* [0,65535] */;
  uint32_t agata_ts_t3 /* [0,65535] */;
  uint32_t agata_ts_t4 /* [0,65535] */;
  uint32_t agata_data1trig /* [0,255] */;
  uint32_t agata_data1event_trigger_time_hi /* [-1,-1] */;
  uint32_t agata_data1event_trigger_time_lo /* [-1,-1] */;
  uint32_t agata_data1hit_pattern /* [0,65535] */;
  uint32_t agata_data1num_channels_fired /* [-1,-1] */;
  uint32_t agata_data1board_num /* [0,255] */;
  uint32_t agata_data1channel_id /* [0,16] */;
  uint32_t agata_data1channel_idI[16 EXT_STRUCT_CTRL(agata_data1channel_id)] /* [1,16] */;
  uint32_t agata_data1channel_idv[16 EXT_STRUCT_CTRL(agata_data1channel_id)] /* [0,255] */;
  uint32_t agata_data1channel_trigger_time_hi /* [0,16] */;
  uint32_t agata_data1channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(agata_data1channel_trigger_time_hi)] /* [1,16] */;
  uint32_t agata_data1channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(agata_data1channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t agata_data1channel_trigger_time_lo /* [0,16] */;
  uint32_t agata_data1channel_trigger_time_loI[16 EXT_STRUCT_CTRL(agata_data1channel_trigger_time_lo)] /* [1,16] */;
  uint32_t agata_data1channel_trigger_time_lov[16 EXT_STRUCT_CTRL(agata_data1channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t agata_data1pileup /* [0,16] */;
  uint32_t agata_data1pileupI[16 EXT_STRUCT_CTRL(agata_data1pileup)] /* [1,16] */;
  uint32_t agata_data1pileupv[16 EXT_STRUCT_CTRL(agata_data1pileup)] /* [0,255] */;
  uint32_t agata_data1overflow /* [0,16] */;
  uint32_t agata_data1overflowI[16 EXT_STRUCT_CTRL(agata_data1overflow)] /* [1,16] */;
  uint32_t agata_data1overflowv[16 EXT_STRUCT_CTRL(agata_data1overflow)] /* [0,255] */;
  uint32_t agata_data1channel_cfd /* [0,16] */;
  uint32_t agata_data1channel_cfdI[16 EXT_STRUCT_CTRL(agata_data1channel_cfd)] /* [1,16] */;
  uint32_t agata_data1channel_cfdv[16 EXT_STRUCT_CTRL(agata_data1channel_cfd)] /* [0,255] */;
  uint32_t agata_data1channel_energy /* [0,16] */;
  uint32_t agata_data1channel_energyI[16 EXT_STRUCT_CTRL(agata_data1channel_energy)] /* [1,16] */;
  uint32_t agata_data1channel_energyv[16 EXT_STRUCT_CTRL(agata_data1channel_energy)] /* [-1,-1] */;
  uint32_t agata_data1trace_traces1 /* [0,4000] */;
  uint32_t agata_data1trace_traces1I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces1)] /* [1,4000] */;
  uint32_t agata_data1trace_traces1v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces1)] /* [0,65535] */;
  uint32_t agata_data1trace_traces2 /* [0,4000] */;
  uint32_t agata_data1trace_traces2I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces2)] /* [1,4000] */;
  uint32_t agata_data1trace_traces2v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces2)] /* [0,65535] */;
  uint32_t agata_data1trace_traces3 /* [0,4000] */;
  uint32_t agata_data1trace_traces3I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces3)] /* [1,4000] */;
  uint32_t agata_data1trace_traces3v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces3)] /* [0,65535] */;
  uint32_t agata_data1trace_traces4 /* [0,4000] */;
  uint32_t agata_data1trace_traces4I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces4)] /* [1,4000] */;
  uint32_t agata_data1trace_traces4v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces4)] /* [0,65535] */;
  uint32_t agata_data1trace_traces5 /* [0,4000] */;
  uint32_t agata_data1trace_traces5I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces5)] /* [1,4000] */;
  uint32_t agata_data1trace_traces5v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces5)] /* [0,65535] */;
  uint32_t agata_data1trace_traces6 /* [0,4000] */;
  uint32_t agata_data1trace_traces6I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces6)] /* [1,4000] */;
  uint32_t agata_data1trace_traces6v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces6)] /* [0,65535] */;
  uint32_t agata_data1trace_traces7 /* [0,4000] */;
  uint32_t agata_data1trace_traces7I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces7)] /* [1,4000] */;
  uint32_t agata_data1trace_traces7v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces7)] /* [0,65535] */;
  uint32_t agata_data1trace_traces8 /* [0,4000] */;
  uint32_t agata_data1trace_traces8I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces8)] /* [1,4000] */;
  uint32_t agata_data1trace_traces8v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces8)] /* [0,65535] */;
  uint32_t agata_data1trace_traces9 /* [0,4000] */;
  uint32_t agata_data1trace_traces9I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces9)] /* [1,4000] */;
  uint32_t agata_data1trace_traces9v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces9)] /* [0,65535] */;
  uint32_t agata_data1trace_traces10 /* [0,4000] */;
  uint32_t agata_data1trace_traces10I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces10)] /* [1,4000] */;
  uint32_t agata_data1trace_traces10v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces10)] /* [0,65535] */;
  uint32_t agata_data1trace_traces11 /* [0,4000] */;
  uint32_t agata_data1trace_traces11I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces11)] /* [1,4000] */;
  uint32_t agata_data1trace_traces11v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces11)] /* [0,65535] */;
  uint32_t agata_data1trace_traces12 /* [0,4000] */;
  uint32_t agata_data1trace_traces12I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces12)] /* [1,4000] */;
  uint32_t agata_data1trace_traces12v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces12)] /* [0,65535] */;
  uint32_t agata_data1trace_traces13 /* [0,4000] */;
  uint32_t agata_data1trace_traces13I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces13)] /* [1,4000] */;
  uint32_t agata_data1trace_traces13v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces13)] /* [0,65535] */;
  uint32_t agata_data1trace_traces14 /* [0,4000] */;
  uint32_t agata_data1trace_traces14I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces14)] /* [1,4000] */;
  uint32_t agata_data1trace_traces14v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces14)] /* [0,65535] */;
  uint32_t agata_data1trace_traces15 /* [0,4000] */;
  uint32_t agata_data1trace_traces15I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces15)] /* [1,4000] */;
  uint32_t agata_data1trace_traces15v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces15)] /* [0,65535] */;
  uint32_t agata_data1trace_traces16 /* [0,4000] */;
  uint32_t agata_data1trace_traces16I[4000 EXT_STRUCT_CTRL(agata_data1trace_traces16)] /* [1,4000] */;
  uint32_t agata_data1trace_traces16v[4000 EXT_STRUCT_CTRL(agata_data1trace_traces16)] /* [0,65535] */;
  uint32_t agata_data1trace_channel_id_traces /* [0,16] */;
  uint32_t agata_data1trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(agata_data1trace_channel_id_traces)] /* [1,16] */;
  uint32_t agata_data1trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(agata_data1trace_channel_id_traces)] /* [0,255] */;
  uint32_t agata_data2trig /* [0,255] */;
  uint32_t agata_data2event_trigger_time_hi /* [-1,-1] */;
  uint32_t agata_data2event_trigger_time_lo /* [-1,-1] */;
  uint32_t agata_data2hit_pattern /* [0,65535] */;
  uint32_t agata_data2num_channels_fired /* [-1,-1] */;
  uint32_t agata_data2board_num /* [0,255] */;
  uint32_t agata_data2channel_id /* [0,16] */;
  uint32_t agata_data2channel_idI[16 EXT_STRUCT_CTRL(agata_data2channel_id)] /* [1,16] */;
  uint32_t agata_data2channel_idv[16 EXT_STRUCT_CTRL(agata_data2channel_id)] /* [0,255] */;
  uint32_t agata_data2channel_trigger_time_hi /* [0,16] */;
  uint32_t agata_data2channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(agata_data2channel_trigger_time_hi)] /* [1,16] */;
  uint32_t agata_data2channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(agata_data2channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t agata_data2channel_trigger_time_lo /* [0,16] */;
  uint32_t agata_data2channel_trigger_time_loI[16 EXT_STRUCT_CTRL(agata_data2channel_trigger_time_lo)] /* [1,16] */;
  uint32_t agata_data2channel_trigger_time_lov[16 EXT_STRUCT_CTRL(agata_data2channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t agata_data2pileup /* [0,16] */;
  uint32_t agata_data2pileupI[16 EXT_STRUCT_CTRL(agata_data2pileup)] /* [1,16] */;
  uint32_t agata_data2pileupv[16 EXT_STRUCT_CTRL(agata_data2pileup)] /* [0,255] */;
  uint32_t agata_data2overflow /* [0,16] */;
  uint32_t agata_data2overflowI[16 EXT_STRUCT_CTRL(agata_data2overflow)] /* [1,16] */;
  uint32_t agata_data2overflowv[16 EXT_STRUCT_CTRL(agata_data2overflow)] /* [0,255] */;
  uint32_t agata_data2channel_cfd /* [0,16] */;
  uint32_t agata_data2channel_cfdI[16 EXT_STRUCT_CTRL(agata_data2channel_cfd)] /* [1,16] */;
  uint32_t agata_data2channel_cfdv[16 EXT_STRUCT_CTRL(agata_data2channel_cfd)] /* [0,255] */;
  uint32_t agata_data2channel_energy /* [0,16] */;
  uint32_t agata_data2channel_energyI[16 EXT_STRUCT_CTRL(agata_data2channel_energy)] /* [1,16] */;
  uint32_t agata_data2channel_energyv[16 EXT_STRUCT_CTRL(agata_data2channel_energy)] /* [-1,-1] */;
  uint32_t agata_data2trace_traces1 /* [0,4000] */;
  uint32_t agata_data2trace_traces1I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces1)] /* [1,4000] */;
  uint32_t agata_data2trace_traces1v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces1)] /* [0,65535] */;
  uint32_t agata_data2trace_traces2 /* [0,4000] */;
  uint32_t agata_data2trace_traces2I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces2)] /* [1,4000] */;
  uint32_t agata_data2trace_traces2v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces2)] /* [0,65535] */;
  uint32_t agata_data2trace_traces3 /* [0,4000] */;
  uint32_t agata_data2trace_traces3I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces3)] /* [1,4000] */;
  uint32_t agata_data2trace_traces3v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces3)] /* [0,65535] */;
  uint32_t agata_data2trace_traces4 /* [0,4000] */;
  uint32_t agata_data2trace_traces4I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces4)] /* [1,4000] */;
  uint32_t agata_data2trace_traces4v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces4)] /* [0,65535] */;
  uint32_t agata_data2trace_traces5 /* [0,4000] */;
  uint32_t agata_data2trace_traces5I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces5)] /* [1,4000] */;
  uint32_t agata_data2trace_traces5v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces5)] /* [0,65535] */;
  uint32_t agata_data2trace_traces6 /* [0,4000] */;
  uint32_t agata_data2trace_traces6I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces6)] /* [1,4000] */;
  uint32_t agata_data2trace_traces6v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces6)] /* [0,65535] */;
  uint32_t agata_data2trace_traces7 /* [0,4000] */;
  uint32_t agata_data2trace_traces7I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces7)] /* [1,4000] */;
  uint32_t agata_data2trace_traces7v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces7)] /* [0,65535] */;
  uint32_t agata_data2trace_traces8 /* [0,4000] */;
  uint32_t agata_data2trace_traces8I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces8)] /* [1,4000] */;
  uint32_t agata_data2trace_traces8v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces8)] /* [0,65535] */;
  uint32_t agata_data2trace_traces9 /* [0,4000] */;
  uint32_t agata_data2trace_traces9I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces9)] /* [1,4000] */;
  uint32_t agata_data2trace_traces9v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces9)] /* [0,65535] */;
  uint32_t agata_data2trace_traces10 /* [0,4000] */;
  uint32_t agata_data2trace_traces10I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces10)] /* [1,4000] */;
  uint32_t agata_data2trace_traces10v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces10)] /* [0,65535] */;
  uint32_t agata_data2trace_traces11 /* [0,4000] */;
  uint32_t agata_data2trace_traces11I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces11)] /* [1,4000] */;
  uint32_t agata_data2trace_traces11v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces11)] /* [0,65535] */;
  uint32_t agata_data2trace_traces12 /* [0,4000] */;
  uint32_t agata_data2trace_traces12I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces12)] /* [1,4000] */;
  uint32_t agata_data2trace_traces12v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces12)] /* [0,65535] */;
  uint32_t agata_data2trace_traces13 /* [0,4000] */;
  uint32_t agata_data2trace_traces13I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces13)] /* [1,4000] */;
  uint32_t agata_data2trace_traces13v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces13)] /* [0,65535] */;
  uint32_t agata_data2trace_traces14 /* [0,4000] */;
  uint32_t agata_data2trace_traces14I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces14)] /* [1,4000] */;
  uint32_t agata_data2trace_traces14v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces14)] /* [0,65535] */;
  uint32_t agata_data2trace_traces15 /* [0,4000] */;
  uint32_t agata_data2trace_traces15I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces15)] /* [1,4000] */;
  uint32_t agata_data2trace_traces15v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces15)] /* [0,65535] */;
  uint32_t agata_data2trace_traces16 /* [0,4000] */;
  uint32_t agata_data2trace_traces16I[4000 EXT_STRUCT_CTRL(agata_data2trace_traces16)] /* [1,4000] */;
  uint32_t agata_data2trace_traces16v[4000 EXT_STRUCT_CTRL(agata_data2trace_traces16)] /* [0,65535] */;
  uint32_t agata_data2trace_channel_id_traces /* [0,16] */;
  uint32_t agata_data2trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(agata_data2trace_channel_id_traces)] /* [1,16] */;
  uint32_t agata_data2trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(agata_data2trace_channel_id_traces)] /* [0,255] */;
  uint32_t agata_data3trig /* [0,255] */;
  uint32_t agata_data3event_trigger_time_hi /* [-1,-1] */;
  uint32_t agata_data3event_trigger_time_lo /* [-1,-1] */;
  uint32_t agata_data3hit_pattern /* [0,65535] */;
  uint32_t agata_data3num_channels_fired /* [-1,-1] */;
  uint32_t agata_data3board_num /* [0,255] */;
  uint32_t agata_data3channel_id /* [0,16] */;
  uint32_t agata_data3channel_idI[16 EXT_STRUCT_CTRL(agata_data3channel_id)] /* [1,16] */;
  uint32_t agata_data3channel_idv[16 EXT_STRUCT_CTRL(agata_data3channel_id)] /* [0,255] */;
  uint32_t agata_data3channel_trigger_time_hi /* [0,16] */;
  uint32_t agata_data3channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(agata_data3channel_trigger_time_hi)] /* [1,16] */;
  uint32_t agata_data3channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(agata_data3channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t agata_data3channel_trigger_time_lo /* [0,16] */;
  uint32_t agata_data3channel_trigger_time_loI[16 EXT_STRUCT_CTRL(agata_data3channel_trigger_time_lo)] /* [1,16] */;
  uint32_t agata_data3channel_trigger_time_lov[16 EXT_STRUCT_CTRL(agata_data3channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t agata_data3pileup /* [0,16] */;
  uint32_t agata_data3pileupI[16 EXT_STRUCT_CTRL(agata_data3pileup)] /* [1,16] */;
  uint32_t agata_data3pileupv[16 EXT_STRUCT_CTRL(agata_data3pileup)] /* [0,255] */;
  uint32_t agata_data3overflow /* [0,16] */;
  uint32_t agata_data3overflowI[16 EXT_STRUCT_CTRL(agata_data3overflow)] /* [1,16] */;
  uint32_t agata_data3overflowv[16 EXT_STRUCT_CTRL(agata_data3overflow)] /* [0,255] */;
  uint32_t agata_data3channel_cfd /* [0,16] */;
  uint32_t agata_data3channel_cfdI[16 EXT_STRUCT_CTRL(agata_data3channel_cfd)] /* [1,16] */;
  uint32_t agata_data3channel_cfdv[16 EXT_STRUCT_CTRL(agata_data3channel_cfd)] /* [0,255] */;
  uint32_t agata_data3channel_energy /* [0,16] */;
  uint32_t agata_data3channel_energyI[16 EXT_STRUCT_CTRL(agata_data3channel_energy)] /* [1,16] */;
  uint32_t agata_data3channel_energyv[16 EXT_STRUCT_CTRL(agata_data3channel_energy)] /* [-1,-1] */;
  uint32_t agata_data3trace_traces1 /* [0,4000] */;
  uint32_t agata_data3trace_traces1I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces1)] /* [1,4000] */;
  uint32_t agata_data3trace_traces1v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces1)] /* [0,65535] */;
  uint32_t agata_data3trace_traces2 /* [0,4000] */;
  uint32_t agata_data3trace_traces2I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces2)] /* [1,4000] */;
  uint32_t agata_data3trace_traces2v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces2)] /* [0,65535] */;
  uint32_t agata_data3trace_traces3 /* [0,4000] */;
  uint32_t agata_data3trace_traces3I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces3)] /* [1,4000] */;
  uint32_t agata_data3trace_traces3v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces3)] /* [0,65535] */;
  uint32_t agata_data3trace_traces4 /* [0,4000] */;
  uint32_t agata_data3trace_traces4I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces4)] /* [1,4000] */;
  uint32_t agata_data3trace_traces4v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces4)] /* [0,65535] */;
  uint32_t agata_data3trace_traces5 /* [0,4000] */;
  uint32_t agata_data3trace_traces5I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces5)] /* [1,4000] */;
  uint32_t agata_data3trace_traces5v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces5)] /* [0,65535] */;
  uint32_t agata_data3trace_traces6 /* [0,4000] */;
  uint32_t agata_data3trace_traces6I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces6)] /* [1,4000] */;
  uint32_t agata_data3trace_traces6v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces6)] /* [0,65535] */;
  uint32_t agata_data3trace_traces7 /* [0,4000] */;
  uint32_t agata_data3trace_traces7I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces7)] /* [1,4000] */;
  uint32_t agata_data3trace_traces7v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces7)] /* [0,65535] */;
  uint32_t agata_data3trace_traces8 /* [0,4000] */;
  uint32_t agata_data3trace_traces8I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces8)] /* [1,4000] */;
  uint32_t agata_data3trace_traces8v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces8)] /* [0,65535] */;
  uint32_t agata_data3trace_traces9 /* [0,4000] */;
  uint32_t agata_data3trace_traces9I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces9)] /* [1,4000] */;
  uint32_t agata_data3trace_traces9v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces9)] /* [0,65535] */;
  uint32_t agata_data3trace_traces10 /* [0,4000] */;
  uint32_t agata_data3trace_traces10I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces10)] /* [1,4000] */;
  uint32_t agata_data3trace_traces10v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces10)] /* [0,65535] */;
  uint32_t agata_data3trace_traces11 /* [0,4000] */;
  uint32_t agata_data3trace_traces11I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces11)] /* [1,4000] */;
  uint32_t agata_data3trace_traces11v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces11)] /* [0,65535] */;
  uint32_t agata_data3trace_traces12 /* [0,4000] */;
  uint32_t agata_data3trace_traces12I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces12)] /* [1,4000] */;
  uint32_t agata_data3trace_traces12v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces12)] /* [0,65535] */;
  uint32_t agata_data3trace_traces13 /* [0,4000] */;
  uint32_t agata_data3trace_traces13I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces13)] /* [1,4000] */;
  uint32_t agata_data3trace_traces13v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces13)] /* [0,65535] */;
  uint32_t agata_data3trace_traces14 /* [0,4000] */;
  uint32_t agata_data3trace_traces14I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces14)] /* [1,4000] */;
  uint32_t agata_data3trace_traces14v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces14)] /* [0,65535] */;
  uint32_t agata_data3trace_traces15 /* [0,4000] */;
  uint32_t agata_data3trace_traces15I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces15)] /* [1,4000] */;
  uint32_t agata_data3trace_traces15v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces15)] /* [0,65535] */;
  uint32_t agata_data3trace_traces16 /* [0,4000] */;
  uint32_t agata_data3trace_traces16I[4000 EXT_STRUCT_CTRL(agata_data3trace_traces16)] /* [1,4000] */;
  uint32_t agata_data3trace_traces16v[4000 EXT_STRUCT_CTRL(agata_data3trace_traces16)] /* [0,65535] */;
  uint32_t agata_data3trace_channel_id_traces /* [0,16] */;
  uint32_t agata_data3trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(agata_data3trace_channel_id_traces)] /* [1,16] */;
  uint32_t agata_data3trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(agata_data3trace_channel_id_traces)] /* [0,255] */;
  uint32_t agata_data4trig /* [0,255] */;
  uint32_t agata_data4event_trigger_time_hi /* [-1,-1] */;
  uint32_t agata_data4event_trigger_time_lo /* [-1,-1] */;
  uint32_t agata_data4hit_pattern /* [0,65535] */;
  uint32_t agata_data4num_channels_fired /* [-1,-1] */;
  uint32_t agata_data4board_num /* [0,255] */;
  uint32_t agata_data4channel_id /* [0,16] */;
  uint32_t agata_data4channel_idI[16 EXT_STRUCT_CTRL(agata_data4channel_id)] /* [1,16] */;
  uint32_t agata_data4channel_idv[16 EXT_STRUCT_CTRL(agata_data4channel_id)] /* [0,255] */;
  uint32_t agata_data4channel_trigger_time_hi /* [0,16] */;
  uint32_t agata_data4channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(agata_data4channel_trigger_time_hi)] /* [1,16] */;
  uint32_t agata_data4channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(agata_data4channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t agata_data4channel_trigger_time_lo /* [0,16] */;
  uint32_t agata_data4channel_trigger_time_loI[16 EXT_STRUCT_CTRL(agata_data4channel_trigger_time_lo)] /* [1,16] */;
  uint32_t agata_data4channel_trigger_time_lov[16 EXT_STRUCT_CTRL(agata_data4channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t agata_data4pileup /* [0,16] */;
  uint32_t agata_data4pileupI[16 EXT_STRUCT_CTRL(agata_data4pileup)] /* [1,16] */;
  uint32_t agata_data4pileupv[16 EXT_STRUCT_CTRL(agata_data4pileup)] /* [0,255] */;
  uint32_t agata_data4overflow /* [0,16] */;
  uint32_t agata_data4overflowI[16 EXT_STRUCT_CTRL(agata_data4overflow)] /* [1,16] */;
  uint32_t agata_data4overflowv[16 EXT_STRUCT_CTRL(agata_data4overflow)] /* [0,255] */;
  uint32_t agata_data4channel_cfd /* [0,16] */;
  uint32_t agata_data4channel_cfdI[16 EXT_STRUCT_CTRL(agata_data4channel_cfd)] /* [1,16] */;
  uint32_t agata_data4channel_cfdv[16 EXT_STRUCT_CTRL(agata_data4channel_cfd)] /* [0,255] */;
  uint32_t agata_data4channel_energy /* [0,16] */;
  uint32_t agata_data4channel_energyI[16 EXT_STRUCT_CTRL(agata_data4channel_energy)] /* [1,16] */;
  uint32_t agata_data4channel_energyv[16 EXT_STRUCT_CTRL(agata_data4channel_energy)] /* [-1,-1] */;
  uint32_t agata_data4trace_traces1 /* [0,4000] */;
  uint32_t agata_data4trace_traces1I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces1)] /* [1,4000] */;
  uint32_t agata_data4trace_traces1v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces1)] /* [0,65535] */;
  uint32_t agata_data4trace_traces2 /* [0,4000] */;
  uint32_t agata_data4trace_traces2I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces2)] /* [1,4000] */;
  uint32_t agata_data4trace_traces2v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces2)] /* [0,65535] */;
  uint32_t agata_data4trace_traces3 /* [0,4000] */;
  uint32_t agata_data4trace_traces3I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces3)] /* [1,4000] */;
  uint32_t agata_data4trace_traces3v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces3)] /* [0,65535] */;
  uint32_t agata_data4trace_traces4 /* [0,4000] */;
  uint32_t agata_data4trace_traces4I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces4)] /* [1,4000] */;
  uint32_t agata_data4trace_traces4v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces4)] /* [0,65535] */;
  uint32_t agata_data4trace_traces5 /* [0,4000] */;
  uint32_t agata_data4trace_traces5I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces5)] /* [1,4000] */;
  uint32_t agata_data4trace_traces5v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces5)] /* [0,65535] */;
  uint32_t agata_data4trace_traces6 /* [0,4000] */;
  uint32_t agata_data4trace_traces6I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces6)] /* [1,4000] */;
  uint32_t agata_data4trace_traces6v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces6)] /* [0,65535] */;
  uint32_t agata_data4trace_traces7 /* [0,4000] */;
  uint32_t agata_data4trace_traces7I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces7)] /* [1,4000] */;
  uint32_t agata_data4trace_traces7v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces7)] /* [0,65535] */;
  uint32_t agata_data4trace_traces8 /* [0,4000] */;
  uint32_t agata_data4trace_traces8I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces8)] /* [1,4000] */;
  uint32_t agata_data4trace_traces8v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces8)] /* [0,65535] */;
  uint32_t agata_data4trace_traces9 /* [0,4000] */;
  uint32_t agata_data4trace_traces9I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces9)] /* [1,4000] */;
  uint32_t agata_data4trace_traces9v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces9)] /* [0,65535] */;
  uint32_t agata_data4trace_traces10 /* [0,4000] */;
  uint32_t agata_data4trace_traces10I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces10)] /* [1,4000] */;
  uint32_t agata_data4trace_traces10v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces10)] /* [0,65535] */;
  uint32_t agata_data4trace_traces11 /* [0,4000] */;
  uint32_t agata_data4trace_traces11I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces11)] /* [1,4000] */;
  uint32_t agata_data4trace_traces11v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces11)] /* [0,65535] */;
  uint32_t agata_data4trace_traces12 /* [0,4000] */;
  uint32_t agata_data4trace_traces12I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces12)] /* [1,4000] */;
  uint32_t agata_data4trace_traces12v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces12)] /* [0,65535] */;
  uint32_t agata_data4trace_traces13 /* [0,4000] */;
  uint32_t agata_data4trace_traces13I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces13)] /* [1,4000] */;
  uint32_t agata_data4trace_traces13v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces13)] /* [0,65535] */;
  uint32_t agata_data4trace_traces14 /* [0,4000] */;
  uint32_t agata_data4trace_traces14I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces14)] /* [1,4000] */;
  uint32_t agata_data4trace_traces14v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces14)] /* [0,65535] */;
  uint32_t agata_data4trace_traces15 /* [0,4000] */;
  uint32_t agata_data4trace_traces15I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces15)] /* [1,4000] */;
  uint32_t agata_data4trace_traces15v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces15)] /* [0,65535] */;
  uint32_t agata_data4trace_traces16 /* [0,4000] */;
  uint32_t agata_data4trace_traces16I[4000 EXT_STRUCT_CTRL(agata_data4trace_traces16)] /* [1,4000] */;
  uint32_t agata_data4trace_traces16v[4000 EXT_STRUCT_CTRL(agata_data4trace_traces16)] /* [0,65535] */;
  uint32_t agata_data4trace_channel_id_traces /* [0,16] */;
  uint32_t agata_data4trace_channel_id_tracesI[16 EXT_STRUCT_CTRL(agata_data4trace_channel_id_traces)] /* [1,16] */;
  uint32_t agata_data4trace_channel_id_tracesv[16 EXT_STRUCT_CTRL(agata_data4trace_channel_id_traces)] /* [0,255] */;

} EXT_STR_h101_agata;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_agata_onion_t
{
  /* UNPACK */
  uint32_t agata_badevent_bad;
  uint32_t agata_ts_subsystem_id;
  uint32_t agata_ts_t[4];
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
  } agata_data[4];

} EXT_STR_h101_agata_onion;

/*******************************************************/

#define EXT_STR_h101_agata_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_badevent_bad,              UINT32,\
                    "agata_badevent_bad",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_ts_subsystem_id,           UINT32,\
                    "agata_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_ts_t1,                     UINT32,\
                    "agata_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_ts_t2,                     UINT32,\
                    "agata_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_ts_t3,                     UINT32,\
                    "agata_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_ts_t4,                     UINT32,\
                    "agata_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trig,                 UINT32,\
                    "agata_data1trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     agata_data1event_trigger_time_hi,UINT32,\
                    "agata_data1event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     agata_data1event_trigger_time_lo,UINT32,\
                    "agata_data1event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1hit_pattern,          UINT32,\
                    "agata_data1hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     agata_data1num_channels_fired,   UINT32,\
                    "agata_data1num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1board_num,            UINT32,\
                    "agata_data1board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_id,           UINT32,\
                    "agata_data1channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_idI,          UINT32,\
                    "agata_data1channel_idI",          "agata_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_idv,          UINT32,\
                    "agata_data1channel_idv",          "agata_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_trigger_time_hi,UINT32,\
                    "agata_data1channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_trigger_time_hiI,UINT32,\
                    "agata_data1channel_trigger_time_hiI","agata_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_trigger_time_hiv,UINT32,\
                    "agata_data1channel_trigger_time_hiv","agata_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_trigger_time_lo,UINT32,\
                    "agata_data1channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_trigger_time_loI,UINT32,\
                    "agata_data1channel_trigger_time_loI","agata_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_trigger_time_lov,UINT32,\
                    "agata_data1channel_trigger_time_lov","agata_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1pileup,               UINT32,\
                    "agata_data1pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1pileupI,              UINT32,\
                    "agata_data1pileupI",              "agata_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1pileupv,              UINT32,\
                    "agata_data1pileupv",              "agata_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1overflow,             UINT32,\
                    "agata_data1overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1overflowI,            UINT32,\
                    "agata_data1overflowI",            "agata_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1overflowv,            UINT32,\
                    "agata_data1overflowv",            "agata_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_cfd,          UINT32,\
                    "agata_data1channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_cfdI,         UINT32,\
                    "agata_data1channel_cfdI",         "agata_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_cfdv,         UINT32,\
                    "agata_data1channel_cfdv",         "agata_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_energy,       UINT32,\
                    "agata_data1channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_energyI,      UINT32,\
                    "agata_data1channel_energyI",      "agata_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1channel_energyv,      UINT32,\
                    "agata_data1channel_energyv",      "agata_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces1,        UINT32,\
                    "agata_data1trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces1I,       UINT32,\
                    "agata_data1trace_traces1I",       "agata_data1trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces1v,       UINT32,\
                    "agata_data1trace_traces1v",       "agata_data1trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces2,        UINT32,\
                    "agata_data1trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces2I,       UINT32,\
                    "agata_data1trace_traces2I",       "agata_data1trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces2v,       UINT32,\
                    "agata_data1trace_traces2v",       "agata_data1trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces3,        UINT32,\
                    "agata_data1trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces3I,       UINT32,\
                    "agata_data1trace_traces3I",       "agata_data1trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces3v,       UINT32,\
                    "agata_data1trace_traces3v",       "agata_data1trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces4,        UINT32,\
                    "agata_data1trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces4I,       UINT32,\
                    "agata_data1trace_traces4I",       "agata_data1trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces4v,       UINT32,\
                    "agata_data1trace_traces4v",       "agata_data1trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces5,        UINT32,\
                    "agata_data1trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces5I,       UINT32,\
                    "agata_data1trace_traces5I",       "agata_data1trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces5v,       UINT32,\
                    "agata_data1trace_traces5v",       "agata_data1trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces6,        UINT32,\
                    "agata_data1trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces6I,       UINT32,\
                    "agata_data1trace_traces6I",       "agata_data1trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces6v,       UINT32,\
                    "agata_data1trace_traces6v",       "agata_data1trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces7,        UINT32,\
                    "agata_data1trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces7I,       UINT32,\
                    "agata_data1trace_traces7I",       "agata_data1trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces7v,       UINT32,\
                    "agata_data1trace_traces7v",       "agata_data1trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces8,        UINT32,\
                    "agata_data1trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces8I,       UINT32,\
                    "agata_data1trace_traces8I",       "agata_data1trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces8v,       UINT32,\
                    "agata_data1trace_traces8v",       "agata_data1trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces9,        UINT32,\
                    "agata_data1trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces9I,       UINT32,\
                    "agata_data1trace_traces9I",       "agata_data1trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces9v,       UINT32,\
                    "agata_data1trace_traces9v",       "agata_data1trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces10,       UINT32,\
                    "agata_data1trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces10I,      UINT32,\
                    "agata_data1trace_traces10I",      "agata_data1trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces10v,      UINT32,\
                    "agata_data1trace_traces10v",      "agata_data1trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces11,       UINT32,\
                    "agata_data1trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces11I,      UINT32,\
                    "agata_data1trace_traces11I",      "agata_data1trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces11v,      UINT32,\
                    "agata_data1trace_traces11v",      "agata_data1trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces12,       UINT32,\
                    "agata_data1trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces12I,      UINT32,\
                    "agata_data1trace_traces12I",      "agata_data1trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces12v,      UINT32,\
                    "agata_data1trace_traces12v",      "agata_data1trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces13,       UINT32,\
                    "agata_data1trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces13I,      UINT32,\
                    "agata_data1trace_traces13I",      "agata_data1trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces13v,      UINT32,\
                    "agata_data1trace_traces13v",      "agata_data1trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces14,       UINT32,\
                    "agata_data1trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces14I,      UINT32,\
                    "agata_data1trace_traces14I",      "agata_data1trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces14v,      UINT32,\
                    "agata_data1trace_traces14v",      "agata_data1trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces15,       UINT32,\
                    "agata_data1trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces15I,      UINT32,\
                    "agata_data1trace_traces15I",      "agata_data1trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces15v,      UINT32,\
                    "agata_data1trace_traces15v",      "agata_data1trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces16,       UINT32,\
                    "agata_data1trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces16I,      UINT32,\
                    "agata_data1trace_traces16I",      "agata_data1trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_traces16v,      UINT32,\
                    "agata_data1trace_traces16v",      "agata_data1trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_channel_id_traces,UINT32,\
                    "agata_data1trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_channel_id_tracesI,UINT32,\
                    "agata_data1trace_channel_id_tracesI","agata_data1trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data1trace_channel_id_tracesv,UINT32,\
                    "agata_data1trace_channel_id_tracesv","agata_data1trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trig,                 UINT32,\
                    "agata_data2trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     agata_data2event_trigger_time_hi,UINT32,\
                    "agata_data2event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     agata_data2event_trigger_time_lo,UINT32,\
                    "agata_data2event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2hit_pattern,          UINT32,\
                    "agata_data2hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     agata_data2num_channels_fired,   UINT32,\
                    "agata_data2num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2board_num,            UINT32,\
                    "agata_data2board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_id,           UINT32,\
                    "agata_data2channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_idI,          UINT32,\
                    "agata_data2channel_idI",          "agata_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_idv,          UINT32,\
                    "agata_data2channel_idv",          "agata_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_trigger_time_hi,UINT32,\
                    "agata_data2channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_trigger_time_hiI,UINT32,\
                    "agata_data2channel_trigger_time_hiI","agata_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_trigger_time_hiv,UINT32,\
                    "agata_data2channel_trigger_time_hiv","agata_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_trigger_time_lo,UINT32,\
                    "agata_data2channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_trigger_time_loI,UINT32,\
                    "agata_data2channel_trigger_time_loI","agata_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_trigger_time_lov,UINT32,\
                    "agata_data2channel_trigger_time_lov","agata_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2pileup,               UINT32,\
                    "agata_data2pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2pileupI,              UINT32,\
                    "agata_data2pileupI",              "agata_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2pileupv,              UINT32,\
                    "agata_data2pileupv",              "agata_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2overflow,             UINT32,\
                    "agata_data2overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2overflowI,            UINT32,\
                    "agata_data2overflowI",            "agata_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2overflowv,            UINT32,\
                    "agata_data2overflowv",            "agata_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_cfd,          UINT32,\
                    "agata_data2channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_cfdI,         UINT32,\
                    "agata_data2channel_cfdI",         "agata_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_cfdv,         UINT32,\
                    "agata_data2channel_cfdv",         "agata_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_energy,       UINT32,\
                    "agata_data2channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_energyI,      UINT32,\
                    "agata_data2channel_energyI",      "agata_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2channel_energyv,      UINT32,\
                    "agata_data2channel_energyv",      "agata_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces1,        UINT32,\
                    "agata_data2trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces1I,       UINT32,\
                    "agata_data2trace_traces1I",       "agata_data2trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces1v,       UINT32,\
                    "agata_data2trace_traces1v",       "agata_data2trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces2,        UINT32,\
                    "agata_data2trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces2I,       UINT32,\
                    "agata_data2trace_traces2I",       "agata_data2trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces2v,       UINT32,\
                    "agata_data2trace_traces2v",       "agata_data2trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces3,        UINT32,\
                    "agata_data2trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces3I,       UINT32,\
                    "agata_data2trace_traces3I",       "agata_data2trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces3v,       UINT32,\
                    "agata_data2trace_traces3v",       "agata_data2trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces4,        UINT32,\
                    "agata_data2trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces4I,       UINT32,\
                    "agata_data2trace_traces4I",       "agata_data2trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces4v,       UINT32,\
                    "agata_data2trace_traces4v",       "agata_data2trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces5,        UINT32,\
                    "agata_data2trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces5I,       UINT32,\
                    "agata_data2trace_traces5I",       "agata_data2trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces5v,       UINT32,\
                    "agata_data2trace_traces5v",       "agata_data2trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces6,        UINT32,\
                    "agata_data2trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces6I,       UINT32,\
                    "agata_data2trace_traces6I",       "agata_data2trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces6v,       UINT32,\
                    "agata_data2trace_traces6v",       "agata_data2trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces7,        UINT32,\
                    "agata_data2trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces7I,       UINT32,\
                    "agata_data2trace_traces7I",       "agata_data2trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces7v,       UINT32,\
                    "agata_data2trace_traces7v",       "agata_data2trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces8,        UINT32,\
                    "agata_data2trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces8I,       UINT32,\
                    "agata_data2trace_traces8I",       "agata_data2trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces8v,       UINT32,\
                    "agata_data2trace_traces8v",       "agata_data2trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces9,        UINT32,\
                    "agata_data2trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces9I,       UINT32,\
                    "agata_data2trace_traces9I",       "agata_data2trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces9v,       UINT32,\
                    "agata_data2trace_traces9v",       "agata_data2trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces10,       UINT32,\
                    "agata_data2trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces10I,      UINT32,\
                    "agata_data2trace_traces10I",      "agata_data2trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces10v,      UINT32,\
                    "agata_data2trace_traces10v",      "agata_data2trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces11,       UINT32,\
                    "agata_data2trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces11I,      UINT32,\
                    "agata_data2trace_traces11I",      "agata_data2trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces11v,      UINT32,\
                    "agata_data2trace_traces11v",      "agata_data2trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces12,       UINT32,\
                    "agata_data2trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces12I,      UINT32,\
                    "agata_data2trace_traces12I",      "agata_data2trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces12v,      UINT32,\
                    "agata_data2trace_traces12v",      "agata_data2trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces13,       UINT32,\
                    "agata_data2trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces13I,      UINT32,\
                    "agata_data2trace_traces13I",      "agata_data2trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces13v,      UINT32,\
                    "agata_data2trace_traces13v",      "agata_data2trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces14,       UINT32,\
                    "agata_data2trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces14I,      UINT32,\
                    "agata_data2trace_traces14I",      "agata_data2trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces14v,      UINT32,\
                    "agata_data2trace_traces14v",      "agata_data2trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces15,       UINT32,\
                    "agata_data2trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces15I,      UINT32,\
                    "agata_data2trace_traces15I",      "agata_data2trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces15v,      UINT32,\
                    "agata_data2trace_traces15v",      "agata_data2trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces16,       UINT32,\
                    "agata_data2trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces16I,      UINT32,\
                    "agata_data2trace_traces16I",      "agata_data2trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_traces16v,      UINT32,\
                    "agata_data2trace_traces16v",      "agata_data2trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_channel_id_traces,UINT32,\
                    "agata_data2trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_channel_id_tracesI,UINT32,\
                    "agata_data2trace_channel_id_tracesI","agata_data2trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data2trace_channel_id_tracesv,UINT32,\
                    "agata_data2trace_channel_id_tracesv","agata_data2trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trig,                 UINT32,\
                    "agata_data3trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     agata_data3event_trigger_time_hi,UINT32,\
                    "agata_data3event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     agata_data3event_trigger_time_lo,UINT32,\
                    "agata_data3event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3hit_pattern,          UINT32,\
                    "agata_data3hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     agata_data3num_channels_fired,   UINT32,\
                    "agata_data3num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3board_num,            UINT32,\
                    "agata_data3board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_id,           UINT32,\
                    "agata_data3channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_idI,          UINT32,\
                    "agata_data3channel_idI",          "agata_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_idv,          UINT32,\
                    "agata_data3channel_idv",          "agata_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_trigger_time_hi,UINT32,\
                    "agata_data3channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_trigger_time_hiI,UINT32,\
                    "agata_data3channel_trigger_time_hiI","agata_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_trigger_time_hiv,UINT32,\
                    "agata_data3channel_trigger_time_hiv","agata_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_trigger_time_lo,UINT32,\
                    "agata_data3channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_trigger_time_loI,UINT32,\
                    "agata_data3channel_trigger_time_loI","agata_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_trigger_time_lov,UINT32,\
                    "agata_data3channel_trigger_time_lov","agata_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3pileup,               UINT32,\
                    "agata_data3pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3pileupI,              UINT32,\
                    "agata_data3pileupI",              "agata_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3pileupv,              UINT32,\
                    "agata_data3pileupv",              "agata_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3overflow,             UINT32,\
                    "agata_data3overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3overflowI,            UINT32,\
                    "agata_data3overflowI",            "agata_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3overflowv,            UINT32,\
                    "agata_data3overflowv",            "agata_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_cfd,          UINT32,\
                    "agata_data3channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_cfdI,         UINT32,\
                    "agata_data3channel_cfdI",         "agata_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_cfdv,         UINT32,\
                    "agata_data3channel_cfdv",         "agata_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_energy,       UINT32,\
                    "agata_data3channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_energyI,      UINT32,\
                    "agata_data3channel_energyI",      "agata_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3channel_energyv,      UINT32,\
                    "agata_data3channel_energyv",      "agata_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces1,        UINT32,\
                    "agata_data3trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces1I,       UINT32,\
                    "agata_data3trace_traces1I",       "agata_data3trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces1v,       UINT32,\
                    "agata_data3trace_traces1v",       "agata_data3trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces2,        UINT32,\
                    "agata_data3trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces2I,       UINT32,\
                    "agata_data3trace_traces2I",       "agata_data3trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces2v,       UINT32,\
                    "agata_data3trace_traces2v",       "agata_data3trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces3,        UINT32,\
                    "agata_data3trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces3I,       UINT32,\
                    "agata_data3trace_traces3I",       "agata_data3trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces3v,       UINT32,\
                    "agata_data3trace_traces3v",       "agata_data3trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces4,        UINT32,\
                    "agata_data3trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces4I,       UINT32,\
                    "agata_data3trace_traces4I",       "agata_data3trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces4v,       UINT32,\
                    "agata_data3trace_traces4v",       "agata_data3trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces5,        UINT32,\
                    "agata_data3trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces5I,       UINT32,\
                    "agata_data3trace_traces5I",       "agata_data3trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces5v,       UINT32,\
                    "agata_data3trace_traces5v",       "agata_data3trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces6,        UINT32,\
                    "agata_data3trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces6I,       UINT32,\
                    "agata_data3trace_traces6I",       "agata_data3trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces6v,       UINT32,\
                    "agata_data3trace_traces6v",       "agata_data3trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces7,        UINT32,\
                    "agata_data3trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces7I,       UINT32,\
                    "agata_data3trace_traces7I",       "agata_data3trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces7v,       UINT32,\
                    "agata_data3trace_traces7v",       "agata_data3trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces8,        UINT32,\
                    "agata_data3trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces8I,       UINT32,\
                    "agata_data3trace_traces8I",       "agata_data3trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces8v,       UINT32,\
                    "agata_data3trace_traces8v",       "agata_data3trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces9,        UINT32,\
                    "agata_data3trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces9I,       UINT32,\
                    "agata_data3trace_traces9I",       "agata_data3trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces9v,       UINT32,\
                    "agata_data3trace_traces9v",       "agata_data3trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces10,       UINT32,\
                    "agata_data3trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces10I,      UINT32,\
                    "agata_data3trace_traces10I",      "agata_data3trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces10v,      UINT32,\
                    "agata_data3trace_traces10v",      "agata_data3trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces11,       UINT32,\
                    "agata_data3trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces11I,      UINT32,\
                    "agata_data3trace_traces11I",      "agata_data3trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces11v,      UINT32,\
                    "agata_data3trace_traces11v",      "agata_data3trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces12,       UINT32,\
                    "agata_data3trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces12I,      UINT32,\
                    "agata_data3trace_traces12I",      "agata_data3trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces12v,      UINT32,\
                    "agata_data3trace_traces12v",      "agata_data3trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces13,       UINT32,\
                    "agata_data3trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces13I,      UINT32,\
                    "agata_data3trace_traces13I",      "agata_data3trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces13v,      UINT32,\
                    "agata_data3trace_traces13v",      "agata_data3trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces14,       UINT32,\
                    "agata_data3trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces14I,      UINT32,\
                    "agata_data3trace_traces14I",      "agata_data3trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces14v,      UINT32,\
                    "agata_data3trace_traces14v",      "agata_data3trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces15,       UINT32,\
                    "agata_data3trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces15I,      UINT32,\
                    "agata_data3trace_traces15I",      "agata_data3trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces15v,      UINT32,\
                    "agata_data3trace_traces15v",      "agata_data3trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces16,       UINT32,\
                    "agata_data3trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces16I,      UINT32,\
                    "agata_data3trace_traces16I",      "agata_data3trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_traces16v,      UINT32,\
                    "agata_data3trace_traces16v",      "agata_data3trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_channel_id_traces,UINT32,\
                    "agata_data3trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_channel_id_tracesI,UINT32,\
                    "agata_data3trace_channel_id_tracesI","agata_data3trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data3trace_channel_id_tracesv,UINT32,\
                    "agata_data3trace_channel_id_tracesv","agata_data3trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trig,                 UINT32,\
                    "agata_data4trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     agata_data4event_trigger_time_hi,UINT32,\
                    "agata_data4event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     agata_data4event_trigger_time_lo,UINT32,\
                    "agata_data4event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4hit_pattern,          UINT32,\
                    "agata_data4hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     agata_data4num_channels_fired,   UINT32,\
                    "agata_data4num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4board_num,            UINT32,\
                    "agata_data4board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_id,           UINT32,\
                    "agata_data4channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_idI,          UINT32,\
                    "agata_data4channel_idI",          "agata_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_idv,          UINT32,\
                    "agata_data4channel_idv",          "agata_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_trigger_time_hi,UINT32,\
                    "agata_data4channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_trigger_time_hiI,UINT32,\
                    "agata_data4channel_trigger_time_hiI","agata_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_trigger_time_hiv,UINT32,\
                    "agata_data4channel_trigger_time_hiv","agata_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_trigger_time_lo,UINT32,\
                    "agata_data4channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_trigger_time_loI,UINT32,\
                    "agata_data4channel_trigger_time_loI","agata_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_trigger_time_lov,UINT32,\
                    "agata_data4channel_trigger_time_lov","agata_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4pileup,               UINT32,\
                    "agata_data4pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4pileupI,              UINT32,\
                    "agata_data4pileupI",              "agata_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4pileupv,              UINT32,\
                    "agata_data4pileupv",              "agata_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4overflow,             UINT32,\
                    "agata_data4overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4overflowI,            UINT32,\
                    "agata_data4overflowI",            "agata_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4overflowv,            UINT32,\
                    "agata_data4overflowv",            "agata_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_cfd,          UINT32,\
                    "agata_data4channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_cfdI,         UINT32,\
                    "agata_data4channel_cfdI",         "agata_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_cfdv,         UINT32,\
                    "agata_data4channel_cfdv",         "agata_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_energy,       UINT32,\
                    "agata_data4channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_energyI,      UINT32,\
                    "agata_data4channel_energyI",      "agata_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4channel_energyv,      UINT32,\
                    "agata_data4channel_energyv",      "agata_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces1,        UINT32,\
                    "agata_data4trace_traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces1I,       UINT32,\
                    "agata_data4trace_traces1I",       "agata_data4trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces1v,       UINT32,\
                    "agata_data4trace_traces1v",       "agata_data4trace_traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces2,        UINT32,\
                    "agata_data4trace_traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces2I,       UINT32,\
                    "agata_data4trace_traces2I",       "agata_data4trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces2v,       UINT32,\
                    "agata_data4trace_traces2v",       "agata_data4trace_traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces3,        UINT32,\
                    "agata_data4trace_traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces3I,       UINT32,\
                    "agata_data4trace_traces3I",       "agata_data4trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces3v,       UINT32,\
                    "agata_data4trace_traces3v",       "agata_data4trace_traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces4,        UINT32,\
                    "agata_data4trace_traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces4I,       UINT32,\
                    "agata_data4trace_traces4I",       "agata_data4trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces4v,       UINT32,\
                    "agata_data4trace_traces4v",       "agata_data4trace_traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces5,        UINT32,\
                    "agata_data4trace_traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces5I,       UINT32,\
                    "agata_data4trace_traces5I",       "agata_data4trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces5v,       UINT32,\
                    "agata_data4trace_traces5v",       "agata_data4trace_traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces6,        UINT32,\
                    "agata_data4trace_traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces6I,       UINT32,\
                    "agata_data4trace_traces6I",       "agata_data4trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces6v,       UINT32,\
                    "agata_data4trace_traces6v",       "agata_data4trace_traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces7,        UINT32,\
                    "agata_data4trace_traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces7I,       UINT32,\
                    "agata_data4trace_traces7I",       "agata_data4trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces7v,       UINT32,\
                    "agata_data4trace_traces7v",       "agata_data4trace_traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces8,        UINT32,\
                    "agata_data4trace_traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces8I,       UINT32,\
                    "agata_data4trace_traces8I",       "agata_data4trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces8v,       UINT32,\
                    "agata_data4trace_traces8v",       "agata_data4trace_traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces9,        UINT32,\
                    "agata_data4trace_traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces9I,       UINT32,\
                    "agata_data4trace_traces9I",       "agata_data4trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces9v,       UINT32,\
                    "agata_data4trace_traces9v",       "agata_data4trace_traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces10,       UINT32,\
                    "agata_data4trace_traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces10I,      UINT32,\
                    "agata_data4trace_traces10I",      "agata_data4trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces10v,      UINT32,\
                    "agata_data4trace_traces10v",      "agata_data4trace_traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces11,       UINT32,\
                    "agata_data4trace_traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces11I,      UINT32,\
                    "agata_data4trace_traces11I",      "agata_data4trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces11v,      UINT32,\
                    "agata_data4trace_traces11v",      "agata_data4trace_traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces12,       UINT32,\
                    "agata_data4trace_traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces12I,      UINT32,\
                    "agata_data4trace_traces12I",      "agata_data4trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces12v,      UINT32,\
                    "agata_data4trace_traces12v",      "agata_data4trace_traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces13,       UINT32,\
                    "agata_data4trace_traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces13I,      UINT32,\
                    "agata_data4trace_traces13I",      "agata_data4trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces13v,      UINT32,\
                    "agata_data4trace_traces13v",      "agata_data4trace_traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces14,       UINT32,\
                    "agata_data4trace_traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces14I,      UINT32,\
                    "agata_data4trace_traces14I",      "agata_data4trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces14v,      UINT32,\
                    "agata_data4trace_traces14v",      "agata_data4trace_traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces15,       UINT32,\
                    "agata_data4trace_traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces15I,      UINT32,\
                    "agata_data4trace_traces15I",      "agata_data4trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces15v,      UINT32,\
                    "agata_data4trace_traces15v",      "agata_data4trace_traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces16,       UINT32,\
                    "agata_data4trace_traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces16I,      UINT32,\
                    "agata_data4trace_traces16I",      "agata_data4trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_traces16v,      UINT32,\
                    "agata_data4trace_traces16v",      "agata_data4trace_traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_channel_id_traces,UINT32,\
                    "agata_data4trace_channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_channel_id_tracesI,UINT32,\
                    "agata_data4trace_channel_id_tracesI","agata_data4trace_channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     agata_data4trace_channel_id_tracesv,UINT32,\
                    "agata_data4trace_channel_id_tracesv","agata_data4trace_channel_id_traces",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_AGATA_EXT_H101_AGATA_H__*/

/*******************************************************/
