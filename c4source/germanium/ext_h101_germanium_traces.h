/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_GERMANIUM_TRACES_EXT_H101_GERMANIUM_TRACES_H__
#define __GUARD_H101_GERMANIUM_TRACES_EXT_H101_GERMANIUM_TRACES_H__

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

typedef struct EXT_STR_h101_germanium_traces_t
{
  /* UNPACK */
  uint32_t germanium_traces_ts_subsystem_id /* [0,65535] */;
  uint32_t germanium_traces_ts_t1 /* [0,65535] */;
  uint32_t germanium_traces_ts_t2 /* [0,65535] */;
  uint32_t germanium_traces_ts_t3 /* [0,65535] */;
  uint32_t germanium_traces_ts_t4 /* [0,65535] */;
  uint32_t germanium_traces_data1trig /* [0,255] */;
  uint32_t germanium_traces_data1event_trigger_time_hi /* [-1,-1] */;
  uint32_t germanium_traces_data1event_trigger_time_lo /* [-1,-1] */;
  uint32_t germanium_traces_data1hit_pattern /* [0,65535] */;
  uint32_t germanium_traces_data1num_channels_fired /* [-1,-1] */;
  uint32_t germanium_traces_data1board_num /* [0,255] */;
  uint32_t germanium_traces_data1channel_id /* [0,16] */;
  uint32_t germanium_traces_data1channel_idI[16 EXT_STRUCT_CTRL(germanium_traces_data1channel_id)] /* [1,16] */;
  uint32_t germanium_traces_data1channel_idv[16 EXT_STRUCT_CTRL(germanium_traces_data1channel_id)] /* [0,255] */;
  uint32_t germanium_traces_data1channel_trigger_time_hi /* [0,16] */;
  uint32_t germanium_traces_data1channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(germanium_traces_data1channel_trigger_time_hi)] /* [1,16] */;
  uint32_t germanium_traces_data1channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(germanium_traces_data1channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t germanium_traces_data1channel_trigger_time_lo /* [0,16] */;
  uint32_t germanium_traces_data1channel_trigger_time_loI[16 EXT_STRUCT_CTRL(germanium_traces_data1channel_trigger_time_lo)] /* [1,16] */;
  uint32_t germanium_traces_data1channel_trigger_time_lov[16 EXT_STRUCT_CTRL(germanium_traces_data1channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t germanium_traces_data1pileup /* [0,16] */;
  uint32_t germanium_traces_data1pileupI[16 EXT_STRUCT_CTRL(germanium_traces_data1pileup)] /* [1,16] */;
  uint32_t germanium_traces_data1pileupv[16 EXT_STRUCT_CTRL(germanium_traces_data1pileup)] /* [0,255] */;
  uint32_t germanium_traces_data1overflow /* [0,16] */;
  uint32_t germanium_traces_data1overflowI[16 EXT_STRUCT_CTRL(germanium_traces_data1overflow)] /* [1,16] */;
  uint32_t germanium_traces_data1overflowv[16 EXT_STRUCT_CTRL(germanium_traces_data1overflow)] /* [0,255] */;
  uint32_t germanium_traces_data1channel_cfd /* [0,16] */;
  uint32_t germanium_traces_data1channel_cfdI[16 EXT_STRUCT_CTRL(germanium_traces_data1channel_cfd)] /* [1,16] */;
  uint32_t germanium_traces_data1channel_cfdv[16 EXT_STRUCT_CTRL(germanium_traces_data1channel_cfd)] /* [0,255] */;
  uint32_t germanium_traces_data1channel_energy /* [0,16] */;
  uint32_t germanium_traces_data1channel_energyI[16 EXT_STRUCT_CTRL(germanium_traces_data1channel_energy)] /* [1,16] */;
  uint32_t germanium_traces_data1channel_energyv[16 EXT_STRUCT_CTRL(germanium_traces_data1channel_energy)] /* [-1,-1] */;
  uint32_t germanium_traces_data1channel_id_traces /* [0,16] */;
  uint32_t germanium_traces_data1channel_id_tracesI[16 EXT_STRUCT_CTRL(germanium_traces_data1channel_id_traces)] /* [1,16] */;
  uint32_t germanium_traces_data1channel_id_tracesv[16 EXT_STRUCT_CTRL(germanium_traces_data1channel_id_traces)] /* [0,255] */;
  uint32_t germanium_traces_data1traces1 /* [0,4000] */;
  uint32_t germanium_traces_data1traces1I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces1)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces1v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces1)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces2 /* [0,4000] */;
  uint32_t germanium_traces_data1traces2I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces2)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces2v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces2)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces3 /* [0,4000] */;
  uint32_t germanium_traces_data1traces3I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces3)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces3v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces3)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces4 /* [0,4000] */;
  uint32_t germanium_traces_data1traces4I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces4)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces4v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces4)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces5 /* [0,4000] */;
  uint32_t germanium_traces_data1traces5I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces5)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces5v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces5)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces6 /* [0,4000] */;
  uint32_t germanium_traces_data1traces6I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces6)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces6v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces6)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces7 /* [0,4000] */;
  uint32_t germanium_traces_data1traces7I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces7)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces7v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces7)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces8 /* [0,4000] */;
  uint32_t germanium_traces_data1traces8I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces8)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces8v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces8)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces9 /* [0,4000] */;
  uint32_t germanium_traces_data1traces9I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces9)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces9v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces9)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces10 /* [0,4000] */;
  uint32_t germanium_traces_data1traces10I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces10)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces10v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces10)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces11 /* [0,4000] */;
  uint32_t germanium_traces_data1traces11I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces11)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces11v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces11)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces12 /* [0,4000] */;
  uint32_t germanium_traces_data1traces12I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces12)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces12v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces12)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces13 /* [0,4000] */;
  uint32_t germanium_traces_data1traces13I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces13)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces13v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces13)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces14 /* [0,4000] */;
  uint32_t germanium_traces_data1traces14I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces14)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces14v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces14)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces15 /* [0,4000] */;
  uint32_t germanium_traces_data1traces15I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces15)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces15v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces15)] /* [0,65535] */;
  uint32_t germanium_traces_data1traces16 /* [0,4000] */;
  uint32_t germanium_traces_data1traces16I[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces16)] /* [1,4000] */;
  uint32_t germanium_traces_data1traces16v[4000 EXT_STRUCT_CTRL(germanium_traces_data1traces16)] /* [0,65535] */;
  uint32_t germanium_traces_data2trig /* [0,255] */;
  uint32_t germanium_traces_data2event_trigger_time_hi /* [-1,-1] */;
  uint32_t germanium_traces_data2event_trigger_time_lo /* [-1,-1] */;
  uint32_t germanium_traces_data2hit_pattern /* [0,65535] */;
  uint32_t germanium_traces_data2num_channels_fired /* [-1,-1] */;
  uint32_t germanium_traces_data2board_num /* [0,255] */;
  uint32_t germanium_traces_data2channel_id /* [0,16] */;
  uint32_t germanium_traces_data2channel_idI[16 EXT_STRUCT_CTRL(germanium_traces_data2channel_id)] /* [1,16] */;
  uint32_t germanium_traces_data2channel_idv[16 EXT_STRUCT_CTRL(germanium_traces_data2channel_id)] /* [0,255] */;
  uint32_t germanium_traces_data2channel_trigger_time_hi /* [0,16] */;
  uint32_t germanium_traces_data2channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(germanium_traces_data2channel_trigger_time_hi)] /* [1,16] */;
  uint32_t germanium_traces_data2channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(germanium_traces_data2channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t germanium_traces_data2channel_trigger_time_lo /* [0,16] */;
  uint32_t germanium_traces_data2channel_trigger_time_loI[16 EXT_STRUCT_CTRL(germanium_traces_data2channel_trigger_time_lo)] /* [1,16] */;
  uint32_t germanium_traces_data2channel_trigger_time_lov[16 EXT_STRUCT_CTRL(germanium_traces_data2channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t germanium_traces_data2pileup /* [0,16] */;
  uint32_t germanium_traces_data2pileupI[16 EXT_STRUCT_CTRL(germanium_traces_data2pileup)] /* [1,16] */;
  uint32_t germanium_traces_data2pileupv[16 EXT_STRUCT_CTRL(germanium_traces_data2pileup)] /* [0,255] */;
  uint32_t germanium_traces_data2overflow /* [0,16] */;
  uint32_t germanium_traces_data2overflowI[16 EXT_STRUCT_CTRL(germanium_traces_data2overflow)] /* [1,16] */;
  uint32_t germanium_traces_data2overflowv[16 EXT_STRUCT_CTRL(germanium_traces_data2overflow)] /* [0,255] */;
  uint32_t germanium_traces_data2channel_cfd /* [0,16] */;
  uint32_t germanium_traces_data2channel_cfdI[16 EXT_STRUCT_CTRL(germanium_traces_data2channel_cfd)] /* [1,16] */;
  uint32_t germanium_traces_data2channel_cfdv[16 EXT_STRUCT_CTRL(germanium_traces_data2channel_cfd)] /* [0,255] */;
  uint32_t germanium_traces_data2channel_energy /* [0,16] */;
  uint32_t germanium_traces_data2channel_energyI[16 EXT_STRUCT_CTRL(germanium_traces_data2channel_energy)] /* [1,16] */;
  uint32_t germanium_traces_data2channel_energyv[16 EXT_STRUCT_CTRL(germanium_traces_data2channel_energy)] /* [-1,-1] */;
  uint32_t germanium_traces_data2channel_id_traces /* [0,16] */;
  uint32_t germanium_traces_data2channel_id_tracesI[16 EXT_STRUCT_CTRL(germanium_traces_data2channel_id_traces)] /* [1,16] */;
  uint32_t germanium_traces_data2channel_id_tracesv[16 EXT_STRUCT_CTRL(germanium_traces_data2channel_id_traces)] /* [0,255] */;
  uint32_t germanium_traces_data2traces1 /* [0,4000] */;
  uint32_t germanium_traces_data2traces1I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces1)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces1v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces1)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces2 /* [0,4000] */;
  uint32_t germanium_traces_data2traces2I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces2)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces2v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces2)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces3 /* [0,4000] */;
  uint32_t germanium_traces_data2traces3I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces3)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces3v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces3)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces4 /* [0,4000] */;
  uint32_t germanium_traces_data2traces4I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces4)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces4v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces4)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces5 /* [0,4000] */;
  uint32_t germanium_traces_data2traces5I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces5)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces5v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces5)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces6 /* [0,4000] */;
  uint32_t germanium_traces_data2traces6I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces6)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces6v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces6)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces7 /* [0,4000] */;
  uint32_t germanium_traces_data2traces7I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces7)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces7v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces7)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces8 /* [0,4000] */;
  uint32_t germanium_traces_data2traces8I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces8)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces8v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces8)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces9 /* [0,4000] */;
  uint32_t germanium_traces_data2traces9I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces9)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces9v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces9)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces10 /* [0,4000] */;
  uint32_t germanium_traces_data2traces10I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces10)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces10v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces10)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces11 /* [0,4000] */;
  uint32_t germanium_traces_data2traces11I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces11)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces11v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces11)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces12 /* [0,4000] */;
  uint32_t germanium_traces_data2traces12I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces12)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces12v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces12)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces13 /* [0,4000] */;
  uint32_t germanium_traces_data2traces13I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces13)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces13v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces13)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces14 /* [0,4000] */;
  uint32_t germanium_traces_data2traces14I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces14)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces14v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces14)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces15 /* [0,4000] */;
  uint32_t germanium_traces_data2traces15I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces15)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces15v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces15)] /* [0,65535] */;
  uint32_t germanium_traces_data2traces16 /* [0,4000] */;
  uint32_t germanium_traces_data2traces16I[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces16)] /* [1,4000] */;
  uint32_t germanium_traces_data2traces16v[4000 EXT_STRUCT_CTRL(germanium_traces_data2traces16)] /* [0,65535] */;
  uint32_t germanium_traces_data3trig /* [0,255] */;
  uint32_t germanium_traces_data3event_trigger_time_hi /* [-1,-1] */;
  uint32_t germanium_traces_data3event_trigger_time_lo /* [-1,-1] */;
  uint32_t germanium_traces_data3hit_pattern /* [0,65535] */;
  uint32_t germanium_traces_data3num_channels_fired /* [-1,-1] */;
  uint32_t germanium_traces_data3board_num /* [0,255] */;
  uint32_t germanium_traces_data3channel_id /* [0,16] */;
  uint32_t germanium_traces_data3channel_idI[16 EXT_STRUCT_CTRL(germanium_traces_data3channel_id)] /* [1,16] */;
  uint32_t germanium_traces_data3channel_idv[16 EXT_STRUCT_CTRL(germanium_traces_data3channel_id)] /* [0,255] */;
  uint32_t germanium_traces_data3channel_trigger_time_hi /* [0,16] */;
  uint32_t germanium_traces_data3channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(germanium_traces_data3channel_trigger_time_hi)] /* [1,16] */;
  uint32_t germanium_traces_data3channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(germanium_traces_data3channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t germanium_traces_data3channel_trigger_time_lo /* [0,16] */;
  uint32_t germanium_traces_data3channel_trigger_time_loI[16 EXT_STRUCT_CTRL(germanium_traces_data3channel_trigger_time_lo)] /* [1,16] */;
  uint32_t germanium_traces_data3channel_trigger_time_lov[16 EXT_STRUCT_CTRL(germanium_traces_data3channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t germanium_traces_data3pileup /* [0,16] */;
  uint32_t germanium_traces_data3pileupI[16 EXT_STRUCT_CTRL(germanium_traces_data3pileup)] /* [1,16] */;
  uint32_t germanium_traces_data3pileupv[16 EXT_STRUCT_CTRL(germanium_traces_data3pileup)] /* [0,255] */;
  uint32_t germanium_traces_data3overflow /* [0,16] */;
  uint32_t germanium_traces_data3overflowI[16 EXT_STRUCT_CTRL(germanium_traces_data3overflow)] /* [1,16] */;
  uint32_t germanium_traces_data3overflowv[16 EXT_STRUCT_CTRL(germanium_traces_data3overflow)] /* [0,255] */;
  uint32_t germanium_traces_data3channel_cfd /* [0,16] */;
  uint32_t germanium_traces_data3channel_cfdI[16 EXT_STRUCT_CTRL(germanium_traces_data3channel_cfd)] /* [1,16] */;
  uint32_t germanium_traces_data3channel_cfdv[16 EXT_STRUCT_CTRL(germanium_traces_data3channel_cfd)] /* [0,255] */;
  uint32_t germanium_traces_data3channel_energy /* [0,16] */;
  uint32_t germanium_traces_data3channel_energyI[16 EXT_STRUCT_CTRL(germanium_traces_data3channel_energy)] /* [1,16] */;
  uint32_t germanium_traces_data3channel_energyv[16 EXT_STRUCT_CTRL(germanium_traces_data3channel_energy)] /* [-1,-1] */;
  uint32_t germanium_traces_data3channel_id_traces /* [0,16] */;
  uint32_t germanium_traces_data3channel_id_tracesI[16 EXT_STRUCT_CTRL(germanium_traces_data3channel_id_traces)] /* [1,16] */;
  uint32_t germanium_traces_data3channel_id_tracesv[16 EXT_STRUCT_CTRL(germanium_traces_data3channel_id_traces)] /* [0,255] */;
  uint32_t germanium_traces_data3traces1 /* [0,4000] */;
  uint32_t germanium_traces_data3traces1I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces1)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces1v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces1)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces2 /* [0,4000] */;
  uint32_t germanium_traces_data3traces2I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces2)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces2v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces2)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces3 /* [0,4000] */;
  uint32_t germanium_traces_data3traces3I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces3)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces3v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces3)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces4 /* [0,4000] */;
  uint32_t germanium_traces_data3traces4I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces4)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces4v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces4)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces5 /* [0,4000] */;
  uint32_t germanium_traces_data3traces5I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces5)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces5v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces5)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces6 /* [0,4000] */;
  uint32_t germanium_traces_data3traces6I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces6)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces6v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces6)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces7 /* [0,4000] */;
  uint32_t germanium_traces_data3traces7I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces7)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces7v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces7)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces8 /* [0,4000] */;
  uint32_t germanium_traces_data3traces8I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces8)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces8v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces8)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces9 /* [0,4000] */;
  uint32_t germanium_traces_data3traces9I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces9)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces9v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces9)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces10 /* [0,4000] */;
  uint32_t germanium_traces_data3traces10I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces10)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces10v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces10)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces11 /* [0,4000] */;
  uint32_t germanium_traces_data3traces11I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces11)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces11v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces11)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces12 /* [0,4000] */;
  uint32_t germanium_traces_data3traces12I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces12)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces12v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces12)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces13 /* [0,4000] */;
  uint32_t germanium_traces_data3traces13I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces13)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces13v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces13)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces14 /* [0,4000] */;
  uint32_t germanium_traces_data3traces14I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces14)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces14v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces14)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces15 /* [0,4000] */;
  uint32_t germanium_traces_data3traces15I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces15)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces15v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces15)] /* [0,65535] */;
  uint32_t germanium_traces_data3traces16 /* [0,4000] */;
  uint32_t germanium_traces_data3traces16I[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces16)] /* [1,4000] */;
  uint32_t germanium_traces_data3traces16v[4000 EXT_STRUCT_CTRL(germanium_traces_data3traces16)] /* [0,65535] */;
  uint32_t germanium_traces_data4trig /* [0,255] */;
  uint32_t germanium_traces_data4event_trigger_time_hi /* [-1,-1] */;
  uint32_t germanium_traces_data4event_trigger_time_lo /* [-1,-1] */;
  uint32_t germanium_traces_data4hit_pattern /* [0,65535] */;
  uint32_t germanium_traces_data4num_channels_fired /* [-1,-1] */;
  uint32_t germanium_traces_data4board_num /* [0,255] */;
  uint32_t germanium_traces_data4channel_id /* [0,16] */;
  uint32_t germanium_traces_data4channel_idI[16 EXT_STRUCT_CTRL(germanium_traces_data4channel_id)] /* [1,16] */;
  uint32_t germanium_traces_data4channel_idv[16 EXT_STRUCT_CTRL(germanium_traces_data4channel_id)] /* [0,255] */;
  uint32_t germanium_traces_data4channel_trigger_time_hi /* [0,16] */;
  uint32_t germanium_traces_data4channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(germanium_traces_data4channel_trigger_time_hi)] /* [1,16] */;
  uint32_t germanium_traces_data4channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(germanium_traces_data4channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t germanium_traces_data4channel_trigger_time_lo /* [0,16] */;
  uint32_t germanium_traces_data4channel_trigger_time_loI[16 EXT_STRUCT_CTRL(germanium_traces_data4channel_trigger_time_lo)] /* [1,16] */;
  uint32_t germanium_traces_data4channel_trigger_time_lov[16 EXT_STRUCT_CTRL(germanium_traces_data4channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t germanium_traces_data4pileup /* [0,16] */;
  uint32_t germanium_traces_data4pileupI[16 EXT_STRUCT_CTRL(germanium_traces_data4pileup)] /* [1,16] */;
  uint32_t germanium_traces_data4pileupv[16 EXT_STRUCT_CTRL(germanium_traces_data4pileup)] /* [0,255] */;
  uint32_t germanium_traces_data4overflow /* [0,16] */;
  uint32_t germanium_traces_data4overflowI[16 EXT_STRUCT_CTRL(germanium_traces_data4overflow)] /* [1,16] */;
  uint32_t germanium_traces_data4overflowv[16 EXT_STRUCT_CTRL(germanium_traces_data4overflow)] /* [0,255] */;
  uint32_t germanium_traces_data4channel_cfd /* [0,16] */;
  uint32_t germanium_traces_data4channel_cfdI[16 EXT_STRUCT_CTRL(germanium_traces_data4channel_cfd)] /* [1,16] */;
  uint32_t germanium_traces_data4channel_cfdv[16 EXT_STRUCT_CTRL(germanium_traces_data4channel_cfd)] /* [0,255] */;
  uint32_t germanium_traces_data4channel_energy /* [0,16] */;
  uint32_t germanium_traces_data4channel_energyI[16 EXT_STRUCT_CTRL(germanium_traces_data4channel_energy)] /* [1,16] */;
  uint32_t germanium_traces_data4channel_energyv[16 EXT_STRUCT_CTRL(germanium_traces_data4channel_energy)] /* [-1,-1] */;
  uint32_t germanium_traces_data4channel_id_traces /* [0,16] */;
  uint32_t germanium_traces_data4channel_id_tracesI[16 EXT_STRUCT_CTRL(germanium_traces_data4channel_id_traces)] /* [1,16] */;
  uint32_t germanium_traces_data4channel_id_tracesv[16 EXT_STRUCT_CTRL(germanium_traces_data4channel_id_traces)] /* [0,255] */;
  uint32_t germanium_traces_data4traces1 /* [0,4000] */;
  uint32_t germanium_traces_data4traces1I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces1)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces1v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces1)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces2 /* [0,4000] */;
  uint32_t germanium_traces_data4traces2I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces2)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces2v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces2)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces3 /* [0,4000] */;
  uint32_t germanium_traces_data4traces3I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces3)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces3v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces3)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces4 /* [0,4000] */;
  uint32_t germanium_traces_data4traces4I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces4)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces4v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces4)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces5 /* [0,4000] */;
  uint32_t germanium_traces_data4traces5I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces5)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces5v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces5)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces6 /* [0,4000] */;
  uint32_t germanium_traces_data4traces6I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces6)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces6v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces6)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces7 /* [0,4000] */;
  uint32_t germanium_traces_data4traces7I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces7)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces7v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces7)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces8 /* [0,4000] */;
  uint32_t germanium_traces_data4traces8I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces8)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces8v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces8)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces9 /* [0,4000] */;
  uint32_t germanium_traces_data4traces9I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces9)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces9v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces9)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces10 /* [0,4000] */;
  uint32_t germanium_traces_data4traces10I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces10)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces10v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces10)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces11 /* [0,4000] */;
  uint32_t germanium_traces_data4traces11I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces11)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces11v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces11)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces12 /* [0,4000] */;
  uint32_t germanium_traces_data4traces12I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces12)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces12v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces12)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces13 /* [0,4000] */;
  uint32_t germanium_traces_data4traces13I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces13)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces13v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces13)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces14 /* [0,4000] */;
  uint32_t germanium_traces_data4traces14I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces14)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces14v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces14)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces15 /* [0,4000] */;
  uint32_t germanium_traces_data4traces15I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces15)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces15v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces15)] /* [0,65535] */;
  uint32_t germanium_traces_data4traces16 /* [0,4000] */;
  uint32_t germanium_traces_data4traces16I[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces16)] /* [1,4000] */;
  uint32_t germanium_traces_data4traces16v[4000 EXT_STRUCT_CTRL(germanium_traces_data4traces16)] /* [0,65535] */;

} EXT_STR_h101_germanium_traces;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_germanium_traces_onion_t
{
  /* UNPACK */
  uint32_t germanium_traces_ts_subsystem_id;
  uint32_t germanium_traces_ts_t[4];
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
    uint32_t channel_id_traces;
    uint32_t channel_id_tracesI[16 /* channel_id_traces */];
    uint32_t channel_id_tracesv[16 /* channel_id_traces */];
    struct {
      uint32_t _;
      uint32_t I[4000 /*  */];
      uint32_t v[4000 /*  */];
    } traces[16];
  } germanium_traces_data[4];

} EXT_STR_h101_germanium_traces_onion;

/*******************************************************/

#define EXT_STR_h101_germanium_traces_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_ts_subsystem_id,UINT32,\
                    "germanium_traces_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_ts_t1,          UINT32,\
                    "germanium_traces_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_ts_t2,          UINT32,\
                    "germanium_traces_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_ts_t3,          UINT32,\
                    "germanium_traces_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_ts_t4,          UINT32,\
                    "germanium_traces_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1trig,      UINT32,\
                    "germanium_traces_data1trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1event_trigger_time_hi,UINT32,\
                    "germanium_traces_data1event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1event_trigger_time_lo,UINT32,\
                    "germanium_traces_data1event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1hit_pattern,UINT32,\
                    "germanium_traces_data1hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1num_channels_fired,UINT32,\
                    "germanium_traces_data1num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1board_num, UINT32,\
                    "germanium_traces_data1board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_id,UINT32,\
                    "germanium_traces_data1channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_idI,UINT32,\
                    "germanium_traces_data1channel_idI","germanium_traces_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_idv,UINT32,\
                    "germanium_traces_data1channel_idv","germanium_traces_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_trigger_time_hi,UINT32,\
                    "germanium_traces_data1channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_trigger_time_hiI,UINT32,\
                    "germanium_traces_data1channel_trigger_time_hiI","germanium_traces_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_trigger_time_hiv,UINT32,\
                    "germanium_traces_data1channel_trigger_time_hiv","germanium_traces_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_trigger_time_lo,UINT32,\
                    "germanium_traces_data1channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_trigger_time_loI,UINT32,\
                    "germanium_traces_data1channel_trigger_time_loI","germanium_traces_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_trigger_time_lov,UINT32,\
                    "germanium_traces_data1channel_trigger_time_lov","germanium_traces_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1pileup,    UINT32,\
                    "germanium_traces_data1pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1pileupI,   UINT32,\
                    "germanium_traces_data1pileupI",   "germanium_traces_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1pileupv,   UINT32,\
                    "germanium_traces_data1pileupv",   "germanium_traces_data1pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1overflow,  UINT32,\
                    "germanium_traces_data1overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1overflowI, UINT32,\
                    "germanium_traces_data1overflowI", "germanium_traces_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1overflowv, UINT32,\
                    "germanium_traces_data1overflowv", "germanium_traces_data1overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_cfd,UINT32,\
                    "germanium_traces_data1channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_cfdI,UINT32,\
                    "germanium_traces_data1channel_cfdI","germanium_traces_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_cfdv,UINT32,\
                    "germanium_traces_data1channel_cfdv","germanium_traces_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_energy,UINT32,\
                    "germanium_traces_data1channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_energyI,UINT32,\
                    "germanium_traces_data1channel_energyI","germanium_traces_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_energyv,UINT32,\
                    "germanium_traces_data1channel_energyv","germanium_traces_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_id_traces,UINT32,\
                    "germanium_traces_data1channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_id_tracesI,UINT32,\
                    "germanium_traces_data1channel_id_tracesI","germanium_traces_data1channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1channel_id_tracesv,UINT32,\
                    "germanium_traces_data1channel_id_tracesv","germanium_traces_data1channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces1,   UINT32,\
                    "germanium_traces_data1traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces1I,  UINT32,\
                    "germanium_traces_data1traces1I",  "germanium_traces_data1traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces1v,  UINT32,\
                    "germanium_traces_data1traces1v",  "germanium_traces_data1traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces2,   UINT32,\
                    "germanium_traces_data1traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces2I,  UINT32,\
                    "germanium_traces_data1traces2I",  "germanium_traces_data1traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces2v,  UINT32,\
                    "germanium_traces_data1traces2v",  "germanium_traces_data1traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces3,   UINT32,\
                    "germanium_traces_data1traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces3I,  UINT32,\
                    "germanium_traces_data1traces3I",  "germanium_traces_data1traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces3v,  UINT32,\
                    "germanium_traces_data1traces3v",  "germanium_traces_data1traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces4,   UINT32,\
                    "germanium_traces_data1traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces4I,  UINT32,\
                    "germanium_traces_data1traces4I",  "germanium_traces_data1traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces4v,  UINT32,\
                    "germanium_traces_data1traces4v",  "germanium_traces_data1traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces5,   UINT32,\
                    "germanium_traces_data1traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces5I,  UINT32,\
                    "germanium_traces_data1traces5I",  "germanium_traces_data1traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces5v,  UINT32,\
                    "germanium_traces_data1traces5v",  "germanium_traces_data1traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces6,   UINT32,\
                    "germanium_traces_data1traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces6I,  UINT32,\
                    "germanium_traces_data1traces6I",  "germanium_traces_data1traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces6v,  UINT32,\
                    "germanium_traces_data1traces6v",  "germanium_traces_data1traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces7,   UINT32,\
                    "germanium_traces_data1traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces7I,  UINT32,\
                    "germanium_traces_data1traces7I",  "germanium_traces_data1traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces7v,  UINT32,\
                    "germanium_traces_data1traces7v",  "germanium_traces_data1traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces8,   UINT32,\
                    "germanium_traces_data1traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces8I,  UINT32,\
                    "germanium_traces_data1traces8I",  "germanium_traces_data1traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces8v,  UINT32,\
                    "germanium_traces_data1traces8v",  "germanium_traces_data1traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces9,   UINT32,\
                    "germanium_traces_data1traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces9I,  UINT32,\
                    "germanium_traces_data1traces9I",  "germanium_traces_data1traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces9v,  UINT32,\
                    "germanium_traces_data1traces9v",  "germanium_traces_data1traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces10,  UINT32,\
                    "germanium_traces_data1traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces10I, UINT32,\
                    "germanium_traces_data1traces10I", "germanium_traces_data1traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces10v, UINT32,\
                    "germanium_traces_data1traces10v", "germanium_traces_data1traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces11,  UINT32,\
                    "germanium_traces_data1traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces11I, UINT32,\
                    "germanium_traces_data1traces11I", "germanium_traces_data1traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces11v, UINT32,\
                    "germanium_traces_data1traces11v", "germanium_traces_data1traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces12,  UINT32,\
                    "germanium_traces_data1traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces12I, UINT32,\
                    "germanium_traces_data1traces12I", "germanium_traces_data1traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces12v, UINT32,\
                    "germanium_traces_data1traces12v", "germanium_traces_data1traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces13,  UINT32,\
                    "germanium_traces_data1traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces13I, UINT32,\
                    "germanium_traces_data1traces13I", "germanium_traces_data1traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces13v, UINT32,\
                    "germanium_traces_data1traces13v", "germanium_traces_data1traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces14,  UINT32,\
                    "germanium_traces_data1traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces14I, UINT32,\
                    "germanium_traces_data1traces14I", "germanium_traces_data1traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces14v, UINT32,\
                    "germanium_traces_data1traces14v", "germanium_traces_data1traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces15,  UINT32,\
                    "germanium_traces_data1traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces15I, UINT32,\
                    "germanium_traces_data1traces15I", "germanium_traces_data1traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces15v, UINT32,\
                    "germanium_traces_data1traces15v", "germanium_traces_data1traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces16,  UINT32,\
                    "germanium_traces_data1traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces16I, UINT32,\
                    "germanium_traces_data1traces16I", "germanium_traces_data1traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data1traces16v, UINT32,\
                    "germanium_traces_data1traces16v", "germanium_traces_data1traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2trig,      UINT32,\
                    "germanium_traces_data2trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2event_trigger_time_hi,UINT32,\
                    "germanium_traces_data2event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2event_trigger_time_lo,UINT32,\
                    "germanium_traces_data2event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2hit_pattern,UINT32,\
                    "germanium_traces_data2hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2num_channels_fired,UINT32,\
                    "germanium_traces_data2num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2board_num, UINT32,\
                    "germanium_traces_data2board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_id,UINT32,\
                    "germanium_traces_data2channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_idI,UINT32,\
                    "germanium_traces_data2channel_idI","germanium_traces_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_idv,UINT32,\
                    "germanium_traces_data2channel_idv","germanium_traces_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_trigger_time_hi,UINT32,\
                    "germanium_traces_data2channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_trigger_time_hiI,UINT32,\
                    "germanium_traces_data2channel_trigger_time_hiI","germanium_traces_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_trigger_time_hiv,UINT32,\
                    "germanium_traces_data2channel_trigger_time_hiv","germanium_traces_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_trigger_time_lo,UINT32,\
                    "germanium_traces_data2channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_trigger_time_loI,UINT32,\
                    "germanium_traces_data2channel_trigger_time_loI","germanium_traces_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_trigger_time_lov,UINT32,\
                    "germanium_traces_data2channel_trigger_time_lov","germanium_traces_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2pileup,    UINT32,\
                    "germanium_traces_data2pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2pileupI,   UINT32,\
                    "germanium_traces_data2pileupI",   "germanium_traces_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2pileupv,   UINT32,\
                    "germanium_traces_data2pileupv",   "germanium_traces_data2pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2overflow,  UINT32,\
                    "germanium_traces_data2overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2overflowI, UINT32,\
                    "germanium_traces_data2overflowI", "germanium_traces_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2overflowv, UINT32,\
                    "germanium_traces_data2overflowv", "germanium_traces_data2overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_cfd,UINT32,\
                    "germanium_traces_data2channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_cfdI,UINT32,\
                    "germanium_traces_data2channel_cfdI","germanium_traces_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_cfdv,UINT32,\
                    "germanium_traces_data2channel_cfdv","germanium_traces_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_energy,UINT32,\
                    "germanium_traces_data2channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_energyI,UINT32,\
                    "germanium_traces_data2channel_energyI","germanium_traces_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_energyv,UINT32,\
                    "germanium_traces_data2channel_energyv","germanium_traces_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_id_traces,UINT32,\
                    "germanium_traces_data2channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_id_tracesI,UINT32,\
                    "germanium_traces_data2channel_id_tracesI","germanium_traces_data2channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2channel_id_tracesv,UINT32,\
                    "germanium_traces_data2channel_id_tracesv","germanium_traces_data2channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces1,   UINT32,\
                    "germanium_traces_data2traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces1I,  UINT32,\
                    "germanium_traces_data2traces1I",  "germanium_traces_data2traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces1v,  UINT32,\
                    "germanium_traces_data2traces1v",  "germanium_traces_data2traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces2,   UINT32,\
                    "germanium_traces_data2traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces2I,  UINT32,\
                    "germanium_traces_data2traces2I",  "germanium_traces_data2traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces2v,  UINT32,\
                    "germanium_traces_data2traces2v",  "germanium_traces_data2traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces3,   UINT32,\
                    "germanium_traces_data2traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces3I,  UINT32,\
                    "germanium_traces_data2traces3I",  "germanium_traces_data2traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces3v,  UINT32,\
                    "germanium_traces_data2traces3v",  "germanium_traces_data2traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces4,   UINT32,\
                    "germanium_traces_data2traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces4I,  UINT32,\
                    "germanium_traces_data2traces4I",  "germanium_traces_data2traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces4v,  UINT32,\
                    "germanium_traces_data2traces4v",  "germanium_traces_data2traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces5,   UINT32,\
                    "germanium_traces_data2traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces5I,  UINT32,\
                    "germanium_traces_data2traces5I",  "germanium_traces_data2traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces5v,  UINT32,\
                    "germanium_traces_data2traces5v",  "germanium_traces_data2traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces6,   UINT32,\
                    "germanium_traces_data2traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces6I,  UINT32,\
                    "germanium_traces_data2traces6I",  "germanium_traces_data2traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces6v,  UINT32,\
                    "germanium_traces_data2traces6v",  "germanium_traces_data2traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces7,   UINT32,\
                    "germanium_traces_data2traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces7I,  UINT32,\
                    "germanium_traces_data2traces7I",  "germanium_traces_data2traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces7v,  UINT32,\
                    "germanium_traces_data2traces7v",  "germanium_traces_data2traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces8,   UINT32,\
                    "germanium_traces_data2traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces8I,  UINT32,\
                    "germanium_traces_data2traces8I",  "germanium_traces_data2traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces8v,  UINT32,\
                    "germanium_traces_data2traces8v",  "germanium_traces_data2traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces9,   UINT32,\
                    "germanium_traces_data2traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces9I,  UINT32,\
                    "germanium_traces_data2traces9I",  "germanium_traces_data2traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces9v,  UINT32,\
                    "germanium_traces_data2traces9v",  "germanium_traces_data2traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces10,  UINT32,\
                    "germanium_traces_data2traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces10I, UINT32,\
                    "germanium_traces_data2traces10I", "germanium_traces_data2traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces10v, UINT32,\
                    "germanium_traces_data2traces10v", "germanium_traces_data2traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces11,  UINT32,\
                    "germanium_traces_data2traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces11I, UINT32,\
                    "germanium_traces_data2traces11I", "germanium_traces_data2traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces11v, UINT32,\
                    "germanium_traces_data2traces11v", "germanium_traces_data2traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces12,  UINT32,\
                    "germanium_traces_data2traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces12I, UINT32,\
                    "germanium_traces_data2traces12I", "germanium_traces_data2traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces12v, UINT32,\
                    "germanium_traces_data2traces12v", "germanium_traces_data2traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces13,  UINT32,\
                    "germanium_traces_data2traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces13I, UINT32,\
                    "germanium_traces_data2traces13I", "germanium_traces_data2traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces13v, UINT32,\
                    "germanium_traces_data2traces13v", "germanium_traces_data2traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces14,  UINT32,\
                    "germanium_traces_data2traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces14I, UINT32,\
                    "germanium_traces_data2traces14I", "germanium_traces_data2traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces14v, UINT32,\
                    "germanium_traces_data2traces14v", "germanium_traces_data2traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces15,  UINT32,\
                    "germanium_traces_data2traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces15I, UINT32,\
                    "germanium_traces_data2traces15I", "germanium_traces_data2traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces15v, UINT32,\
                    "germanium_traces_data2traces15v", "germanium_traces_data2traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces16,  UINT32,\
                    "germanium_traces_data2traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces16I, UINT32,\
                    "germanium_traces_data2traces16I", "germanium_traces_data2traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data2traces16v, UINT32,\
                    "germanium_traces_data2traces16v", "germanium_traces_data2traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3trig,      UINT32,\
                    "germanium_traces_data3trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3event_trigger_time_hi,UINT32,\
                    "germanium_traces_data3event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3event_trigger_time_lo,UINT32,\
                    "germanium_traces_data3event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3hit_pattern,UINT32,\
                    "germanium_traces_data3hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3num_channels_fired,UINT32,\
                    "germanium_traces_data3num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3board_num, UINT32,\
                    "germanium_traces_data3board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_id,UINT32,\
                    "germanium_traces_data3channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_idI,UINT32,\
                    "germanium_traces_data3channel_idI","germanium_traces_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_idv,UINT32,\
                    "germanium_traces_data3channel_idv","germanium_traces_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_trigger_time_hi,UINT32,\
                    "germanium_traces_data3channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_trigger_time_hiI,UINT32,\
                    "germanium_traces_data3channel_trigger_time_hiI","germanium_traces_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_trigger_time_hiv,UINT32,\
                    "germanium_traces_data3channel_trigger_time_hiv","germanium_traces_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_trigger_time_lo,UINT32,\
                    "germanium_traces_data3channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_trigger_time_loI,UINT32,\
                    "germanium_traces_data3channel_trigger_time_loI","germanium_traces_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_trigger_time_lov,UINT32,\
                    "germanium_traces_data3channel_trigger_time_lov","germanium_traces_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3pileup,    UINT32,\
                    "germanium_traces_data3pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3pileupI,   UINT32,\
                    "germanium_traces_data3pileupI",   "germanium_traces_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3pileupv,   UINT32,\
                    "germanium_traces_data3pileupv",   "germanium_traces_data3pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3overflow,  UINT32,\
                    "germanium_traces_data3overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3overflowI, UINT32,\
                    "germanium_traces_data3overflowI", "germanium_traces_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3overflowv, UINT32,\
                    "germanium_traces_data3overflowv", "germanium_traces_data3overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_cfd,UINT32,\
                    "germanium_traces_data3channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_cfdI,UINT32,\
                    "germanium_traces_data3channel_cfdI","germanium_traces_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_cfdv,UINT32,\
                    "germanium_traces_data3channel_cfdv","germanium_traces_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_energy,UINT32,\
                    "germanium_traces_data3channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_energyI,UINT32,\
                    "germanium_traces_data3channel_energyI","germanium_traces_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_energyv,UINT32,\
                    "germanium_traces_data3channel_energyv","germanium_traces_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_id_traces,UINT32,\
                    "germanium_traces_data3channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_id_tracesI,UINT32,\
                    "germanium_traces_data3channel_id_tracesI","germanium_traces_data3channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3channel_id_tracesv,UINT32,\
                    "germanium_traces_data3channel_id_tracesv","germanium_traces_data3channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces1,   UINT32,\
                    "germanium_traces_data3traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces1I,  UINT32,\
                    "germanium_traces_data3traces1I",  "germanium_traces_data3traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces1v,  UINT32,\
                    "germanium_traces_data3traces1v",  "germanium_traces_data3traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces2,   UINT32,\
                    "germanium_traces_data3traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces2I,  UINT32,\
                    "germanium_traces_data3traces2I",  "germanium_traces_data3traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces2v,  UINT32,\
                    "germanium_traces_data3traces2v",  "germanium_traces_data3traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces3,   UINT32,\
                    "germanium_traces_data3traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces3I,  UINT32,\
                    "germanium_traces_data3traces3I",  "germanium_traces_data3traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces3v,  UINT32,\
                    "germanium_traces_data3traces3v",  "germanium_traces_data3traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces4,   UINT32,\
                    "germanium_traces_data3traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces4I,  UINT32,\
                    "germanium_traces_data3traces4I",  "germanium_traces_data3traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces4v,  UINT32,\
                    "germanium_traces_data3traces4v",  "germanium_traces_data3traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces5,   UINT32,\
                    "germanium_traces_data3traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces5I,  UINT32,\
                    "germanium_traces_data3traces5I",  "germanium_traces_data3traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces5v,  UINT32,\
                    "germanium_traces_data3traces5v",  "germanium_traces_data3traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces6,   UINT32,\
                    "germanium_traces_data3traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces6I,  UINT32,\
                    "germanium_traces_data3traces6I",  "germanium_traces_data3traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces6v,  UINT32,\
                    "germanium_traces_data3traces6v",  "germanium_traces_data3traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces7,   UINT32,\
                    "germanium_traces_data3traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces7I,  UINT32,\
                    "germanium_traces_data3traces7I",  "germanium_traces_data3traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces7v,  UINT32,\
                    "germanium_traces_data3traces7v",  "germanium_traces_data3traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces8,   UINT32,\
                    "germanium_traces_data3traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces8I,  UINT32,\
                    "germanium_traces_data3traces8I",  "germanium_traces_data3traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces8v,  UINT32,\
                    "germanium_traces_data3traces8v",  "germanium_traces_data3traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces9,   UINT32,\
                    "germanium_traces_data3traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces9I,  UINT32,\
                    "germanium_traces_data3traces9I",  "germanium_traces_data3traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces9v,  UINT32,\
                    "germanium_traces_data3traces9v",  "germanium_traces_data3traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces10,  UINT32,\
                    "germanium_traces_data3traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces10I, UINT32,\
                    "germanium_traces_data3traces10I", "germanium_traces_data3traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces10v, UINT32,\
                    "germanium_traces_data3traces10v", "germanium_traces_data3traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces11,  UINT32,\
                    "germanium_traces_data3traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces11I, UINT32,\
                    "germanium_traces_data3traces11I", "germanium_traces_data3traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces11v, UINT32,\
                    "germanium_traces_data3traces11v", "germanium_traces_data3traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces12,  UINT32,\
                    "germanium_traces_data3traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces12I, UINT32,\
                    "germanium_traces_data3traces12I", "germanium_traces_data3traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces12v, UINT32,\
                    "germanium_traces_data3traces12v", "germanium_traces_data3traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces13,  UINT32,\
                    "germanium_traces_data3traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces13I, UINT32,\
                    "germanium_traces_data3traces13I", "germanium_traces_data3traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces13v, UINT32,\
                    "germanium_traces_data3traces13v", "germanium_traces_data3traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces14,  UINT32,\
                    "germanium_traces_data3traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces14I, UINT32,\
                    "germanium_traces_data3traces14I", "germanium_traces_data3traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces14v, UINT32,\
                    "germanium_traces_data3traces14v", "germanium_traces_data3traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces15,  UINT32,\
                    "germanium_traces_data3traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces15I, UINT32,\
                    "germanium_traces_data3traces15I", "germanium_traces_data3traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces15v, UINT32,\
                    "germanium_traces_data3traces15v", "germanium_traces_data3traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces16,  UINT32,\
                    "germanium_traces_data3traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces16I, UINT32,\
                    "germanium_traces_data3traces16I", "germanium_traces_data3traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data3traces16v, UINT32,\
                    "germanium_traces_data3traces16v", "germanium_traces_data3traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4trig,      UINT32,\
                    "germanium_traces_data4trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4event_trigger_time_hi,UINT32,\
                    "germanium_traces_data4event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4event_trigger_time_lo,UINT32,\
                    "germanium_traces_data4event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4hit_pattern,UINT32,\
                    "germanium_traces_data4hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4num_channels_fired,UINT32,\
                    "germanium_traces_data4num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4board_num, UINT32,\
                    "germanium_traces_data4board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_id,UINT32,\
                    "germanium_traces_data4channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_idI,UINT32,\
                    "germanium_traces_data4channel_idI","germanium_traces_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_idv,UINT32,\
                    "germanium_traces_data4channel_idv","germanium_traces_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_trigger_time_hi,UINT32,\
                    "germanium_traces_data4channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_trigger_time_hiI,UINT32,\
                    "germanium_traces_data4channel_trigger_time_hiI","germanium_traces_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_trigger_time_hiv,UINT32,\
                    "germanium_traces_data4channel_trigger_time_hiv","germanium_traces_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_trigger_time_lo,UINT32,\
                    "germanium_traces_data4channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_trigger_time_loI,UINT32,\
                    "germanium_traces_data4channel_trigger_time_loI","germanium_traces_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_trigger_time_lov,UINT32,\
                    "germanium_traces_data4channel_trigger_time_lov","germanium_traces_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4pileup,    UINT32,\
                    "germanium_traces_data4pileup",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4pileupI,   UINT32,\
                    "germanium_traces_data4pileupI",   "germanium_traces_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4pileupv,   UINT32,\
                    "germanium_traces_data4pileupv",   "germanium_traces_data4pileup",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4overflow,  UINT32,\
                    "germanium_traces_data4overflow",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4overflowI, UINT32,\
                    "germanium_traces_data4overflowI", "germanium_traces_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4overflowv, UINT32,\
                    "germanium_traces_data4overflowv", "germanium_traces_data4overflow",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_cfd,UINT32,\
                    "germanium_traces_data4channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_cfdI,UINT32,\
                    "germanium_traces_data4channel_cfdI","germanium_traces_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_cfdv,UINT32,\
                    "germanium_traces_data4channel_cfdv","germanium_traces_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_energy,UINT32,\
                    "germanium_traces_data4channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_energyI,UINT32,\
                    "germanium_traces_data4channel_energyI","germanium_traces_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_energyv,UINT32,\
                    "germanium_traces_data4channel_energyv","germanium_traces_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_id_traces,UINT32,\
                    "germanium_traces_data4channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_id_tracesI,UINT32,\
                    "germanium_traces_data4channel_id_tracesI","germanium_traces_data4channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4channel_id_tracesv,UINT32,\
                    "germanium_traces_data4channel_id_tracesv","germanium_traces_data4channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces1,   UINT32,\
                    "germanium_traces_data4traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces1I,  UINT32,\
                    "germanium_traces_data4traces1I",  "germanium_traces_data4traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces1v,  UINT32,\
                    "germanium_traces_data4traces1v",  "germanium_traces_data4traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces2,   UINT32,\
                    "germanium_traces_data4traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces2I,  UINT32,\
                    "germanium_traces_data4traces2I",  "germanium_traces_data4traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces2v,  UINT32,\
                    "germanium_traces_data4traces2v",  "germanium_traces_data4traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces3,   UINT32,\
                    "germanium_traces_data4traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces3I,  UINT32,\
                    "germanium_traces_data4traces3I",  "germanium_traces_data4traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces3v,  UINT32,\
                    "germanium_traces_data4traces3v",  "germanium_traces_data4traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces4,   UINT32,\
                    "germanium_traces_data4traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces4I,  UINT32,\
                    "germanium_traces_data4traces4I",  "germanium_traces_data4traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces4v,  UINT32,\
                    "germanium_traces_data4traces4v",  "germanium_traces_data4traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces5,   UINT32,\
                    "germanium_traces_data4traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces5I,  UINT32,\
                    "germanium_traces_data4traces5I",  "germanium_traces_data4traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces5v,  UINT32,\
                    "germanium_traces_data4traces5v",  "germanium_traces_data4traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces6,   UINT32,\
                    "germanium_traces_data4traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces6I,  UINT32,\
                    "germanium_traces_data4traces6I",  "germanium_traces_data4traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces6v,  UINT32,\
                    "germanium_traces_data4traces6v",  "germanium_traces_data4traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces7,   UINT32,\
                    "germanium_traces_data4traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces7I,  UINT32,\
                    "germanium_traces_data4traces7I",  "germanium_traces_data4traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces7v,  UINT32,\
                    "germanium_traces_data4traces7v",  "germanium_traces_data4traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces8,   UINT32,\
                    "germanium_traces_data4traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces8I,  UINT32,\
                    "germanium_traces_data4traces8I",  "germanium_traces_data4traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces8v,  UINT32,\
                    "germanium_traces_data4traces8v",  "germanium_traces_data4traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces9,   UINT32,\
                    "germanium_traces_data4traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces9I,  UINT32,\
                    "germanium_traces_data4traces9I",  "germanium_traces_data4traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces9v,  UINT32,\
                    "germanium_traces_data4traces9v",  "germanium_traces_data4traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces10,  UINT32,\
                    "germanium_traces_data4traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces10I, UINT32,\
                    "germanium_traces_data4traces10I", "germanium_traces_data4traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces10v, UINT32,\
                    "germanium_traces_data4traces10v", "germanium_traces_data4traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces11,  UINT32,\
                    "germanium_traces_data4traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces11I, UINT32,\
                    "germanium_traces_data4traces11I", "germanium_traces_data4traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces11v, UINT32,\
                    "germanium_traces_data4traces11v", "germanium_traces_data4traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces12,  UINT32,\
                    "germanium_traces_data4traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces12I, UINT32,\
                    "germanium_traces_data4traces12I", "germanium_traces_data4traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces12v, UINT32,\
                    "germanium_traces_data4traces12v", "germanium_traces_data4traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces13,  UINT32,\
                    "germanium_traces_data4traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces13I, UINT32,\
                    "germanium_traces_data4traces13I", "germanium_traces_data4traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces13v, UINT32,\
                    "germanium_traces_data4traces13v", "germanium_traces_data4traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces14,  UINT32,\
                    "germanium_traces_data4traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces14I, UINT32,\
                    "germanium_traces_data4traces14I", "germanium_traces_data4traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces14v, UINT32,\
                    "germanium_traces_data4traces14v", "germanium_traces_data4traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces15,  UINT32,\
                    "germanium_traces_data4traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces15I, UINT32,\
                    "germanium_traces_data4traces15I", "germanium_traces_data4traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces15v, UINT32,\
                    "germanium_traces_data4traces15v", "germanium_traces_data4traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces16,  UINT32,\
                    "germanium_traces_data4traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces16I, UINT32,\
                    "germanium_traces_data4traces16I", "germanium_traces_data4traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     germanium_traces_data4traces16v, UINT32,\
                    "germanium_traces_data4traces16v", "germanium_traces_data4traces16",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_GERMANIUM_TRACES_EXT_H101_GERMANIUM_TRACES_H__*/

/*******************************************************/
