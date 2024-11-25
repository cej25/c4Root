/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_LISA_EXT_H101_LISA_H__
#define __GUARD_H101_LISA_EXT_H101_LISA_H__

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

typedef struct EXT_STR_h101_lisa_t
{
  /* UNPACK */
  uint32_t lisa_badevent_bad /* [0,255] */;
  uint32_t lisa_ts_subsystem_id /* [0,65535] */;
  uint32_t lisa_ts_t1 /* [0,65535] */;
  uint32_t lisa_ts_t2 /* [0,65535] */;
  uint32_t lisa_ts_t3 /* [0,65535] */;
  uint32_t lisa_ts_t4 /* [0,65535] */;
  uint32_t lisa_data1trig /* [0,255] */;
  uint32_t lisa_data1event_trigger_time_hi /* [-1,-1] */;
  uint32_t lisa_data1event_trigger_time_lo /* [-1,-1] */;
  uint32_t lisa_data1hit_pattern /* [0,65535] */;
  uint32_t lisa_data1num_channels_fired /* [-1,-1] */;
  uint32_t lisa_data1board_num /* [0,255] */;
  uint32_t lisa_data1channel_id /* [0,16] */;
  uint32_t lisa_data1channel_idI[16 EXT_STRUCT_CTRL(lisa_data1channel_id)] /* [1,16] */;
  uint32_t lisa_data1channel_idv[16 EXT_STRUCT_CTRL(lisa_data1channel_id)] /* [0,255] */;
  uint32_t lisa_data1channel_trigger_time_hi /* [0,16] */;
  uint32_t lisa_data1channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(lisa_data1channel_trigger_time_hi)] /* [1,16] */;
  uint32_t lisa_data1channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(lisa_data1channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t lisa_data1channel_trigger_time_lo /* [0,16] */;
  uint32_t lisa_data1channel_trigger_time_loI[16 EXT_STRUCT_CTRL(lisa_data1channel_trigger_time_lo)] /* [1,16] */;
  uint32_t lisa_data1channel_trigger_time_lov[16 EXT_STRUCT_CTRL(lisa_data1channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t lisa_data1pileup1 /* [0,255] */;
  uint32_t lisa_data1pileup2 /* [0,255] */;
  uint32_t lisa_data1pileup3 /* [0,255] */;
  uint32_t lisa_data1pileup4 /* [0,255] */;
  uint32_t lisa_data1pileup5 /* [0,255] */;
  uint32_t lisa_data1pileup6 /* [0,255] */;
  uint32_t lisa_data1pileup7 /* [0,255] */;
  uint32_t lisa_data1pileup8 /* [0,255] */;
  uint32_t lisa_data1pileup9 /* [0,255] */;
  uint32_t lisa_data1pileup10 /* [0,255] */;
  uint32_t lisa_data1pileup11 /* [0,255] */;
  uint32_t lisa_data1pileup12 /* [0,255] */;
  uint32_t lisa_data1pileup13 /* [0,255] */;
  uint32_t lisa_data1pileup14 /* [0,255] */;
  uint32_t lisa_data1pileup15 /* [0,255] */;
  uint32_t lisa_data1pileup16 /* [0,255] */;
  uint32_t lisa_data1overflow1 /* [0,255] */;
  uint32_t lisa_data1overflow2 /* [0,255] */;
  uint32_t lisa_data1overflow3 /* [0,255] */;
  uint32_t lisa_data1overflow4 /* [0,255] */;
  uint32_t lisa_data1overflow5 /* [0,255] */;
  uint32_t lisa_data1overflow6 /* [0,255] */;
  uint32_t lisa_data1overflow7 /* [0,255] */;
  uint32_t lisa_data1overflow8 /* [0,255] */;
  uint32_t lisa_data1overflow9 /* [0,255] */;
  uint32_t lisa_data1overflow10 /* [0,255] */;
  uint32_t lisa_data1overflow11 /* [0,255] */;
  uint32_t lisa_data1overflow12 /* [0,255] */;
  uint32_t lisa_data1overflow13 /* [0,255] */;
  uint32_t lisa_data1overflow14 /* [0,255] */;
  uint32_t lisa_data1overflow15 /* [0,255] */;
  uint32_t lisa_data1overflow16 /* [0,255] */;
  uint32_t lisa_data1channel_cfd /* [0,16] */;
  uint32_t lisa_data1channel_cfdI[16 EXT_STRUCT_CTRL(lisa_data1channel_cfd)] /* [1,16] */;
  uint32_t lisa_data1channel_cfdv[16 EXT_STRUCT_CTRL(lisa_data1channel_cfd)] /* [0,255] */;
  uint32_t lisa_data1channel_energy /* [0,16] */;
  uint32_t lisa_data1channel_energyI[16 EXT_STRUCT_CTRL(lisa_data1channel_energy)] /* [1,16] */;
  uint32_t lisa_data1channel_energyv[16 EXT_STRUCT_CTRL(lisa_data1channel_energy)] /* [-1,-1] */;
  uint32_t lisa_data1channel_id_traces /* [0,16] */;
  uint32_t lisa_data1channel_id_tracesI[16 EXT_STRUCT_CTRL(lisa_data1channel_id_traces)] /* [1,16] */;
  uint32_t lisa_data1channel_id_tracesv[16 EXT_STRUCT_CTRL(lisa_data1channel_id_traces)] /* [0,255] */;
  uint32_t lisa_data1traces1 /* [0,4000] */;
  uint32_t lisa_data1traces1I[4000 EXT_STRUCT_CTRL(lisa_data1traces1)] /* [1,4000] */;
  uint32_t lisa_data1traces1v[4000 EXT_STRUCT_CTRL(lisa_data1traces1)] /* [0,65535] */;
  uint32_t lisa_data1traces2 /* [0,4000] */;
  uint32_t lisa_data1traces2I[4000 EXT_STRUCT_CTRL(lisa_data1traces2)] /* [1,4000] */;
  uint32_t lisa_data1traces2v[4000 EXT_STRUCT_CTRL(lisa_data1traces2)] /* [0,65535] */;
  uint32_t lisa_data1traces3 /* [0,4000] */;
  uint32_t lisa_data1traces3I[4000 EXT_STRUCT_CTRL(lisa_data1traces3)] /* [1,4000] */;
  uint32_t lisa_data1traces3v[4000 EXT_STRUCT_CTRL(lisa_data1traces3)] /* [0,65535] */;
  uint32_t lisa_data1traces4 /* [0,4000] */;
  uint32_t lisa_data1traces4I[4000 EXT_STRUCT_CTRL(lisa_data1traces4)] /* [1,4000] */;
  uint32_t lisa_data1traces4v[4000 EXT_STRUCT_CTRL(lisa_data1traces4)] /* [0,65535] */;
  uint32_t lisa_data1traces5 /* [0,4000] */;
  uint32_t lisa_data1traces5I[4000 EXT_STRUCT_CTRL(lisa_data1traces5)] /* [1,4000] */;
  uint32_t lisa_data1traces5v[4000 EXT_STRUCT_CTRL(lisa_data1traces5)] /* [0,65535] */;
  uint32_t lisa_data1traces6 /* [0,4000] */;
  uint32_t lisa_data1traces6I[4000 EXT_STRUCT_CTRL(lisa_data1traces6)] /* [1,4000] */;
  uint32_t lisa_data1traces6v[4000 EXT_STRUCT_CTRL(lisa_data1traces6)] /* [0,65535] */;
  uint32_t lisa_data1traces7 /* [0,4000] */;
  uint32_t lisa_data1traces7I[4000 EXT_STRUCT_CTRL(lisa_data1traces7)] /* [1,4000] */;
  uint32_t lisa_data1traces7v[4000 EXT_STRUCT_CTRL(lisa_data1traces7)] /* [0,65535] */;
  uint32_t lisa_data1traces8 /* [0,4000] */;
  uint32_t lisa_data1traces8I[4000 EXT_STRUCT_CTRL(lisa_data1traces8)] /* [1,4000] */;
  uint32_t lisa_data1traces8v[4000 EXT_STRUCT_CTRL(lisa_data1traces8)] /* [0,65535] */;
  uint32_t lisa_data1traces9 /* [0,4000] */;
  uint32_t lisa_data1traces9I[4000 EXT_STRUCT_CTRL(lisa_data1traces9)] /* [1,4000] */;
  uint32_t lisa_data1traces9v[4000 EXT_STRUCT_CTRL(lisa_data1traces9)] /* [0,65535] */;
  uint32_t lisa_data1traces10 /* [0,4000] */;
  uint32_t lisa_data1traces10I[4000 EXT_STRUCT_CTRL(lisa_data1traces10)] /* [1,4000] */;
  uint32_t lisa_data1traces10v[4000 EXT_STRUCT_CTRL(lisa_data1traces10)] /* [0,65535] */;
  uint32_t lisa_data1traces11 /* [0,4000] */;
  uint32_t lisa_data1traces11I[4000 EXT_STRUCT_CTRL(lisa_data1traces11)] /* [1,4000] */;
  uint32_t lisa_data1traces11v[4000 EXT_STRUCT_CTRL(lisa_data1traces11)] /* [0,65535] */;
  uint32_t lisa_data1traces12 /* [0,4000] */;
  uint32_t lisa_data1traces12I[4000 EXT_STRUCT_CTRL(lisa_data1traces12)] /* [1,4000] */;
  uint32_t lisa_data1traces12v[4000 EXT_STRUCT_CTRL(lisa_data1traces12)] /* [0,65535] */;
  uint32_t lisa_data1traces13 /* [0,4000] */;
  uint32_t lisa_data1traces13I[4000 EXT_STRUCT_CTRL(lisa_data1traces13)] /* [1,4000] */;
  uint32_t lisa_data1traces13v[4000 EXT_STRUCT_CTRL(lisa_data1traces13)] /* [0,65535] */;
  uint32_t lisa_data1traces14 /* [0,4000] */;
  uint32_t lisa_data1traces14I[4000 EXT_STRUCT_CTRL(lisa_data1traces14)] /* [1,4000] */;
  uint32_t lisa_data1traces14v[4000 EXT_STRUCT_CTRL(lisa_data1traces14)] /* [0,65535] */;
  uint32_t lisa_data1traces15 /* [0,4000] */;
  uint32_t lisa_data1traces15I[4000 EXT_STRUCT_CTRL(lisa_data1traces15)] /* [1,4000] */;
  uint32_t lisa_data1traces15v[4000 EXT_STRUCT_CTRL(lisa_data1traces15)] /* [0,65535] */;
  uint32_t lisa_data1traces16 /* [0,4000] */;
  uint32_t lisa_data1traces16I[4000 EXT_STRUCT_CTRL(lisa_data1traces16)] /* [1,4000] */;
  uint32_t lisa_data1traces16v[4000 EXT_STRUCT_CTRL(lisa_data1traces16)] /* [0,65535] */;
  uint32_t lisa_data2trig /* [0,255] */;
  uint32_t lisa_data2event_trigger_time_hi /* [-1,-1] */;
  uint32_t lisa_data2event_trigger_time_lo /* [-1,-1] */;
  uint32_t lisa_data2hit_pattern /* [0,65535] */;
  uint32_t lisa_data2num_channels_fired /* [-1,-1] */;
  uint32_t lisa_data2board_num /* [0,255] */;
  uint32_t lisa_data2channel_id /* [0,16] */;
  uint32_t lisa_data2channel_idI[16 EXT_STRUCT_CTRL(lisa_data2channel_id)] /* [1,16] */;
  uint32_t lisa_data2channel_idv[16 EXT_STRUCT_CTRL(lisa_data2channel_id)] /* [0,255] */;
  uint32_t lisa_data2channel_trigger_time_hi /* [0,16] */;
  uint32_t lisa_data2channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(lisa_data2channel_trigger_time_hi)] /* [1,16] */;
  uint32_t lisa_data2channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(lisa_data2channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t lisa_data2channel_trigger_time_lo /* [0,16] */;
  uint32_t lisa_data2channel_trigger_time_loI[16 EXT_STRUCT_CTRL(lisa_data2channel_trigger_time_lo)] /* [1,16] */;
  uint32_t lisa_data2channel_trigger_time_lov[16 EXT_STRUCT_CTRL(lisa_data2channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t lisa_data2pileup1 /* [0,255] */;
  uint32_t lisa_data2pileup2 /* [0,255] */;
  uint32_t lisa_data2pileup3 /* [0,255] */;
  uint32_t lisa_data2pileup4 /* [0,255] */;
  uint32_t lisa_data2pileup5 /* [0,255] */;
  uint32_t lisa_data2pileup6 /* [0,255] */;
  uint32_t lisa_data2pileup7 /* [0,255] */;
  uint32_t lisa_data2pileup8 /* [0,255] */;
  uint32_t lisa_data2pileup9 /* [0,255] */;
  uint32_t lisa_data2pileup10 /* [0,255] */;
  uint32_t lisa_data2pileup11 /* [0,255] */;
  uint32_t lisa_data2pileup12 /* [0,255] */;
  uint32_t lisa_data2pileup13 /* [0,255] */;
  uint32_t lisa_data2pileup14 /* [0,255] */;
  uint32_t lisa_data2pileup15 /* [0,255] */;
  uint32_t lisa_data2pileup16 /* [0,255] */;
  uint32_t lisa_data2overflow1 /* [0,255] */;
  uint32_t lisa_data2overflow2 /* [0,255] */;
  uint32_t lisa_data2overflow3 /* [0,255] */;
  uint32_t lisa_data2overflow4 /* [0,255] */;
  uint32_t lisa_data2overflow5 /* [0,255] */;
  uint32_t lisa_data2overflow6 /* [0,255] */;
  uint32_t lisa_data2overflow7 /* [0,255] */;
  uint32_t lisa_data2overflow8 /* [0,255] */;
  uint32_t lisa_data2overflow9 /* [0,255] */;
  uint32_t lisa_data2overflow10 /* [0,255] */;
  uint32_t lisa_data2overflow11 /* [0,255] */;
  uint32_t lisa_data2overflow12 /* [0,255] */;
  uint32_t lisa_data2overflow13 /* [0,255] */;
  uint32_t lisa_data2overflow14 /* [0,255] */;
  uint32_t lisa_data2overflow15 /* [0,255] */;
  uint32_t lisa_data2overflow16 /* [0,255] */;
  uint32_t lisa_data2channel_cfd /* [0,16] */;
  uint32_t lisa_data2channel_cfdI[16 EXT_STRUCT_CTRL(lisa_data2channel_cfd)] /* [1,16] */;
  uint32_t lisa_data2channel_cfdv[16 EXT_STRUCT_CTRL(lisa_data2channel_cfd)] /* [0,255] */;
  uint32_t lisa_data2channel_energy /* [0,16] */;
  uint32_t lisa_data2channel_energyI[16 EXT_STRUCT_CTRL(lisa_data2channel_energy)] /* [1,16] */;
  uint32_t lisa_data2channel_energyv[16 EXT_STRUCT_CTRL(lisa_data2channel_energy)] /* [-1,-1] */;
  uint32_t lisa_data2channel_id_traces /* [0,16] */;
  uint32_t lisa_data2channel_id_tracesI[16 EXT_STRUCT_CTRL(lisa_data2channel_id_traces)] /* [1,16] */;
  uint32_t lisa_data2channel_id_tracesv[16 EXT_STRUCT_CTRL(lisa_data2channel_id_traces)] /* [0,255] */;
  uint32_t lisa_data2traces1 /* [0,4000] */;
  uint32_t lisa_data2traces1I[4000 EXT_STRUCT_CTRL(lisa_data2traces1)] /* [1,4000] */;
  uint32_t lisa_data2traces1v[4000 EXT_STRUCT_CTRL(lisa_data2traces1)] /* [0,65535] */;
  uint32_t lisa_data2traces2 /* [0,4000] */;
  uint32_t lisa_data2traces2I[4000 EXT_STRUCT_CTRL(lisa_data2traces2)] /* [1,4000] */;
  uint32_t lisa_data2traces2v[4000 EXT_STRUCT_CTRL(lisa_data2traces2)] /* [0,65535] */;
  uint32_t lisa_data2traces3 /* [0,4000] */;
  uint32_t lisa_data2traces3I[4000 EXT_STRUCT_CTRL(lisa_data2traces3)] /* [1,4000] */;
  uint32_t lisa_data2traces3v[4000 EXT_STRUCT_CTRL(lisa_data2traces3)] /* [0,65535] */;
  uint32_t lisa_data2traces4 /* [0,4000] */;
  uint32_t lisa_data2traces4I[4000 EXT_STRUCT_CTRL(lisa_data2traces4)] /* [1,4000] */;
  uint32_t lisa_data2traces4v[4000 EXT_STRUCT_CTRL(lisa_data2traces4)] /* [0,65535] */;
  uint32_t lisa_data2traces5 /* [0,4000] */;
  uint32_t lisa_data2traces5I[4000 EXT_STRUCT_CTRL(lisa_data2traces5)] /* [1,4000] */;
  uint32_t lisa_data2traces5v[4000 EXT_STRUCT_CTRL(lisa_data2traces5)] /* [0,65535] */;
  uint32_t lisa_data2traces6 /* [0,4000] */;
  uint32_t lisa_data2traces6I[4000 EXT_STRUCT_CTRL(lisa_data2traces6)] /* [1,4000] */;
  uint32_t lisa_data2traces6v[4000 EXT_STRUCT_CTRL(lisa_data2traces6)] /* [0,65535] */;
  uint32_t lisa_data2traces7 /* [0,4000] */;
  uint32_t lisa_data2traces7I[4000 EXT_STRUCT_CTRL(lisa_data2traces7)] /* [1,4000] */;
  uint32_t lisa_data2traces7v[4000 EXT_STRUCT_CTRL(lisa_data2traces7)] /* [0,65535] */;
  uint32_t lisa_data2traces8 /* [0,4000] */;
  uint32_t lisa_data2traces8I[4000 EXT_STRUCT_CTRL(lisa_data2traces8)] /* [1,4000] */;
  uint32_t lisa_data2traces8v[4000 EXT_STRUCT_CTRL(lisa_data2traces8)] /* [0,65535] */;
  uint32_t lisa_data2traces9 /* [0,4000] */;
  uint32_t lisa_data2traces9I[4000 EXT_STRUCT_CTRL(lisa_data2traces9)] /* [1,4000] */;
  uint32_t lisa_data2traces9v[4000 EXT_STRUCT_CTRL(lisa_data2traces9)] /* [0,65535] */;
  uint32_t lisa_data2traces10 /* [0,4000] */;
  uint32_t lisa_data2traces10I[4000 EXT_STRUCT_CTRL(lisa_data2traces10)] /* [1,4000] */;
  uint32_t lisa_data2traces10v[4000 EXT_STRUCT_CTRL(lisa_data2traces10)] /* [0,65535] */;
  uint32_t lisa_data2traces11 /* [0,4000] */;
  uint32_t lisa_data2traces11I[4000 EXT_STRUCT_CTRL(lisa_data2traces11)] /* [1,4000] */;
  uint32_t lisa_data2traces11v[4000 EXT_STRUCT_CTRL(lisa_data2traces11)] /* [0,65535] */;
  uint32_t lisa_data2traces12 /* [0,4000] */;
  uint32_t lisa_data2traces12I[4000 EXT_STRUCT_CTRL(lisa_data2traces12)] /* [1,4000] */;
  uint32_t lisa_data2traces12v[4000 EXT_STRUCT_CTRL(lisa_data2traces12)] /* [0,65535] */;
  uint32_t lisa_data2traces13 /* [0,4000] */;
  uint32_t lisa_data2traces13I[4000 EXT_STRUCT_CTRL(lisa_data2traces13)] /* [1,4000] */;
  uint32_t lisa_data2traces13v[4000 EXT_STRUCT_CTRL(lisa_data2traces13)] /* [0,65535] */;
  uint32_t lisa_data2traces14 /* [0,4000] */;
  uint32_t lisa_data2traces14I[4000 EXT_STRUCT_CTRL(lisa_data2traces14)] /* [1,4000] */;
  uint32_t lisa_data2traces14v[4000 EXT_STRUCT_CTRL(lisa_data2traces14)] /* [0,65535] */;
  uint32_t lisa_data2traces15 /* [0,4000] */;
  uint32_t lisa_data2traces15I[4000 EXT_STRUCT_CTRL(lisa_data2traces15)] /* [1,4000] */;
  uint32_t lisa_data2traces15v[4000 EXT_STRUCT_CTRL(lisa_data2traces15)] /* [0,65535] */;
  uint32_t lisa_data2traces16 /* [0,4000] */;
  uint32_t lisa_data2traces16I[4000 EXT_STRUCT_CTRL(lisa_data2traces16)] /* [1,4000] */;
  uint32_t lisa_data2traces16v[4000 EXT_STRUCT_CTRL(lisa_data2traces16)] /* [0,65535] */;
  uint32_t lisa_data3trig /* [0,255] */;
  uint32_t lisa_data3event_trigger_time_hi /* [-1,-1] */;
  uint32_t lisa_data3event_trigger_time_lo /* [-1,-1] */;
  uint32_t lisa_data3hit_pattern /* [0,65535] */;
  uint32_t lisa_data3num_channels_fired /* [-1,-1] */;
  uint32_t lisa_data3board_num /* [0,255] */;
  uint32_t lisa_data3channel_id /* [0,16] */;
  uint32_t lisa_data3channel_idI[16 EXT_STRUCT_CTRL(lisa_data3channel_id)] /* [1,16] */;
  uint32_t lisa_data3channel_idv[16 EXT_STRUCT_CTRL(lisa_data3channel_id)] /* [0,255] */;
  uint32_t lisa_data3channel_trigger_time_hi /* [0,16] */;
  uint32_t lisa_data3channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(lisa_data3channel_trigger_time_hi)] /* [1,16] */;
  uint32_t lisa_data3channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(lisa_data3channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t lisa_data3channel_trigger_time_lo /* [0,16] */;
  uint32_t lisa_data3channel_trigger_time_loI[16 EXT_STRUCT_CTRL(lisa_data3channel_trigger_time_lo)] /* [1,16] */;
  uint32_t lisa_data3channel_trigger_time_lov[16 EXT_STRUCT_CTRL(lisa_data3channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t lisa_data3pileup1 /* [0,255] */;
  uint32_t lisa_data3pileup2 /* [0,255] */;
  uint32_t lisa_data3pileup3 /* [0,255] */;
  uint32_t lisa_data3pileup4 /* [0,255] */;
  uint32_t lisa_data3pileup5 /* [0,255] */;
  uint32_t lisa_data3pileup6 /* [0,255] */;
  uint32_t lisa_data3pileup7 /* [0,255] */;
  uint32_t lisa_data3pileup8 /* [0,255] */;
  uint32_t lisa_data3pileup9 /* [0,255] */;
  uint32_t lisa_data3pileup10 /* [0,255] */;
  uint32_t lisa_data3pileup11 /* [0,255] */;
  uint32_t lisa_data3pileup12 /* [0,255] */;
  uint32_t lisa_data3pileup13 /* [0,255] */;
  uint32_t lisa_data3pileup14 /* [0,255] */;
  uint32_t lisa_data3pileup15 /* [0,255] */;
  uint32_t lisa_data3pileup16 /* [0,255] */;
  uint32_t lisa_data3overflow1 /* [0,255] */;
  uint32_t lisa_data3overflow2 /* [0,255] */;
  uint32_t lisa_data3overflow3 /* [0,255] */;
  uint32_t lisa_data3overflow4 /* [0,255] */;
  uint32_t lisa_data3overflow5 /* [0,255] */;
  uint32_t lisa_data3overflow6 /* [0,255] */;
  uint32_t lisa_data3overflow7 /* [0,255] */;
  uint32_t lisa_data3overflow8 /* [0,255] */;
  uint32_t lisa_data3overflow9 /* [0,255] */;
  uint32_t lisa_data3overflow10 /* [0,255] */;
  uint32_t lisa_data3overflow11 /* [0,255] */;
  uint32_t lisa_data3overflow12 /* [0,255] */;
  uint32_t lisa_data3overflow13 /* [0,255] */;
  uint32_t lisa_data3overflow14 /* [0,255] */;
  uint32_t lisa_data3overflow15 /* [0,255] */;
  uint32_t lisa_data3overflow16 /* [0,255] */;
  uint32_t lisa_data3channel_cfd /* [0,16] */;
  uint32_t lisa_data3channel_cfdI[16 EXT_STRUCT_CTRL(lisa_data3channel_cfd)] /* [1,16] */;
  uint32_t lisa_data3channel_cfdv[16 EXT_STRUCT_CTRL(lisa_data3channel_cfd)] /* [0,255] */;
  uint32_t lisa_data3channel_energy /* [0,16] */;
  uint32_t lisa_data3channel_energyI[16 EXT_STRUCT_CTRL(lisa_data3channel_energy)] /* [1,16] */;
  uint32_t lisa_data3channel_energyv[16 EXT_STRUCT_CTRL(lisa_data3channel_energy)] /* [-1,-1] */;
  uint32_t lisa_data3channel_id_traces /* [0,16] */;
  uint32_t lisa_data3channel_id_tracesI[16 EXT_STRUCT_CTRL(lisa_data3channel_id_traces)] /* [1,16] */;
  uint32_t lisa_data3channel_id_tracesv[16 EXT_STRUCT_CTRL(lisa_data3channel_id_traces)] /* [0,255] */;
  uint32_t lisa_data3traces1 /* [0,4000] */;
  uint32_t lisa_data3traces1I[4000 EXT_STRUCT_CTRL(lisa_data3traces1)] /* [1,4000] */;
  uint32_t lisa_data3traces1v[4000 EXT_STRUCT_CTRL(lisa_data3traces1)] /* [0,65535] */;
  uint32_t lisa_data3traces2 /* [0,4000] */;
  uint32_t lisa_data3traces2I[4000 EXT_STRUCT_CTRL(lisa_data3traces2)] /* [1,4000] */;
  uint32_t lisa_data3traces2v[4000 EXT_STRUCT_CTRL(lisa_data3traces2)] /* [0,65535] */;
  uint32_t lisa_data3traces3 /* [0,4000] */;
  uint32_t lisa_data3traces3I[4000 EXT_STRUCT_CTRL(lisa_data3traces3)] /* [1,4000] */;
  uint32_t lisa_data3traces3v[4000 EXT_STRUCT_CTRL(lisa_data3traces3)] /* [0,65535] */;
  uint32_t lisa_data3traces4 /* [0,4000] */;
  uint32_t lisa_data3traces4I[4000 EXT_STRUCT_CTRL(lisa_data3traces4)] /* [1,4000] */;
  uint32_t lisa_data3traces4v[4000 EXT_STRUCT_CTRL(lisa_data3traces4)] /* [0,65535] */;
  uint32_t lisa_data3traces5 /* [0,4000] */;
  uint32_t lisa_data3traces5I[4000 EXT_STRUCT_CTRL(lisa_data3traces5)] /* [1,4000] */;
  uint32_t lisa_data3traces5v[4000 EXT_STRUCT_CTRL(lisa_data3traces5)] /* [0,65535] */;
  uint32_t lisa_data3traces6 /* [0,4000] */;
  uint32_t lisa_data3traces6I[4000 EXT_STRUCT_CTRL(lisa_data3traces6)] /* [1,4000] */;
  uint32_t lisa_data3traces6v[4000 EXT_STRUCT_CTRL(lisa_data3traces6)] /* [0,65535] */;
  uint32_t lisa_data3traces7 /* [0,4000] */;
  uint32_t lisa_data3traces7I[4000 EXT_STRUCT_CTRL(lisa_data3traces7)] /* [1,4000] */;
  uint32_t lisa_data3traces7v[4000 EXT_STRUCT_CTRL(lisa_data3traces7)] /* [0,65535] */;
  uint32_t lisa_data3traces8 /* [0,4000] */;
  uint32_t lisa_data3traces8I[4000 EXT_STRUCT_CTRL(lisa_data3traces8)] /* [1,4000] */;
  uint32_t lisa_data3traces8v[4000 EXT_STRUCT_CTRL(lisa_data3traces8)] /* [0,65535] */;
  uint32_t lisa_data3traces9 /* [0,4000] */;
  uint32_t lisa_data3traces9I[4000 EXT_STRUCT_CTRL(lisa_data3traces9)] /* [1,4000] */;
  uint32_t lisa_data3traces9v[4000 EXT_STRUCT_CTRL(lisa_data3traces9)] /* [0,65535] */;
  uint32_t lisa_data3traces10 /* [0,4000] */;
  uint32_t lisa_data3traces10I[4000 EXT_STRUCT_CTRL(lisa_data3traces10)] /* [1,4000] */;
  uint32_t lisa_data3traces10v[4000 EXT_STRUCT_CTRL(lisa_data3traces10)] /* [0,65535] */;
  uint32_t lisa_data3traces11 /* [0,4000] */;
  uint32_t lisa_data3traces11I[4000 EXT_STRUCT_CTRL(lisa_data3traces11)] /* [1,4000] */;
  uint32_t lisa_data3traces11v[4000 EXT_STRUCT_CTRL(lisa_data3traces11)] /* [0,65535] */;
  uint32_t lisa_data3traces12 /* [0,4000] */;
  uint32_t lisa_data3traces12I[4000 EXT_STRUCT_CTRL(lisa_data3traces12)] /* [1,4000] */;
  uint32_t lisa_data3traces12v[4000 EXT_STRUCT_CTRL(lisa_data3traces12)] /* [0,65535] */;
  uint32_t lisa_data3traces13 /* [0,4000] */;
  uint32_t lisa_data3traces13I[4000 EXT_STRUCT_CTRL(lisa_data3traces13)] /* [1,4000] */;
  uint32_t lisa_data3traces13v[4000 EXT_STRUCT_CTRL(lisa_data3traces13)] /* [0,65535] */;
  uint32_t lisa_data3traces14 /* [0,4000] */;
  uint32_t lisa_data3traces14I[4000 EXT_STRUCT_CTRL(lisa_data3traces14)] /* [1,4000] */;
  uint32_t lisa_data3traces14v[4000 EXT_STRUCT_CTRL(lisa_data3traces14)] /* [0,65535] */;
  uint32_t lisa_data3traces15 /* [0,4000] */;
  uint32_t lisa_data3traces15I[4000 EXT_STRUCT_CTRL(lisa_data3traces15)] /* [1,4000] */;
  uint32_t lisa_data3traces15v[4000 EXT_STRUCT_CTRL(lisa_data3traces15)] /* [0,65535] */;
  uint32_t lisa_data3traces16 /* [0,4000] */;
  uint32_t lisa_data3traces16I[4000 EXT_STRUCT_CTRL(lisa_data3traces16)] /* [1,4000] */;
  uint32_t lisa_data3traces16v[4000 EXT_STRUCT_CTRL(lisa_data3traces16)] /* [0,65535] */;
  uint32_t lisa_data4trig /* [0,255] */;
  uint32_t lisa_data4event_trigger_time_hi /* [-1,-1] */;
  uint32_t lisa_data4event_trigger_time_lo /* [-1,-1] */;
  uint32_t lisa_data4hit_pattern /* [0,65535] */;
  uint32_t lisa_data4num_channels_fired /* [-1,-1] */;
  uint32_t lisa_data4board_num /* [0,255] */;
  uint32_t lisa_data4channel_id /* [0,16] */;
  uint32_t lisa_data4channel_idI[16 EXT_STRUCT_CTRL(lisa_data4channel_id)] /* [1,16] */;
  uint32_t lisa_data4channel_idv[16 EXT_STRUCT_CTRL(lisa_data4channel_id)] /* [0,255] */;
  uint32_t lisa_data4channel_trigger_time_hi /* [0,16] */;
  uint32_t lisa_data4channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(lisa_data4channel_trigger_time_hi)] /* [1,16] */;
  uint32_t lisa_data4channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(lisa_data4channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t lisa_data4channel_trigger_time_lo /* [0,16] */;
  uint32_t lisa_data4channel_trigger_time_loI[16 EXT_STRUCT_CTRL(lisa_data4channel_trigger_time_lo)] /* [1,16] */;
  uint32_t lisa_data4channel_trigger_time_lov[16 EXT_STRUCT_CTRL(lisa_data4channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t lisa_data4pileup1 /* [0,255] */;
  uint32_t lisa_data4pileup2 /* [0,255] */;
  uint32_t lisa_data4pileup3 /* [0,255] */;
  uint32_t lisa_data4pileup4 /* [0,255] */;
  uint32_t lisa_data4pileup5 /* [0,255] */;
  uint32_t lisa_data4pileup6 /* [0,255] */;
  uint32_t lisa_data4pileup7 /* [0,255] */;
  uint32_t lisa_data4pileup8 /* [0,255] */;
  uint32_t lisa_data4pileup9 /* [0,255] */;
  uint32_t lisa_data4pileup10 /* [0,255] */;
  uint32_t lisa_data4pileup11 /* [0,255] */;
  uint32_t lisa_data4pileup12 /* [0,255] */;
  uint32_t lisa_data4pileup13 /* [0,255] */;
  uint32_t lisa_data4pileup14 /* [0,255] */;
  uint32_t lisa_data4pileup15 /* [0,255] */;
  uint32_t lisa_data4pileup16 /* [0,255] */;
  uint32_t lisa_data4overflow1 /* [0,255] */;
  uint32_t lisa_data4overflow2 /* [0,255] */;
  uint32_t lisa_data4overflow3 /* [0,255] */;
  uint32_t lisa_data4overflow4 /* [0,255] */;
  uint32_t lisa_data4overflow5 /* [0,255] */;
  uint32_t lisa_data4overflow6 /* [0,255] */;
  uint32_t lisa_data4overflow7 /* [0,255] */;
  uint32_t lisa_data4overflow8 /* [0,255] */;
  uint32_t lisa_data4overflow9 /* [0,255] */;
  uint32_t lisa_data4overflow10 /* [0,255] */;
  uint32_t lisa_data4overflow11 /* [0,255] */;
  uint32_t lisa_data4overflow12 /* [0,255] */;
  uint32_t lisa_data4overflow13 /* [0,255] */;
  uint32_t lisa_data4overflow14 /* [0,255] */;
  uint32_t lisa_data4overflow15 /* [0,255] */;
  uint32_t lisa_data4overflow16 /* [0,255] */;
  uint32_t lisa_data4channel_cfd /* [0,16] */;
  uint32_t lisa_data4channel_cfdI[16 EXT_STRUCT_CTRL(lisa_data4channel_cfd)] /* [1,16] */;
  uint32_t lisa_data4channel_cfdv[16 EXT_STRUCT_CTRL(lisa_data4channel_cfd)] /* [0,255] */;
  uint32_t lisa_data4channel_energy /* [0,16] */;
  uint32_t lisa_data4channel_energyI[16 EXT_STRUCT_CTRL(lisa_data4channel_energy)] /* [1,16] */;
  uint32_t lisa_data4channel_energyv[16 EXT_STRUCT_CTRL(lisa_data4channel_energy)] /* [-1,-1] */;
  uint32_t lisa_data4channel_id_traces /* [0,16] */;
  uint32_t lisa_data4channel_id_tracesI[16 EXT_STRUCT_CTRL(lisa_data4channel_id_traces)] /* [1,16] */;
  uint32_t lisa_data4channel_id_tracesv[16 EXT_STRUCT_CTRL(lisa_data4channel_id_traces)] /* [0,255] */;
  uint32_t lisa_data4traces1 /* [0,4000] */;
  uint32_t lisa_data4traces1I[4000 EXT_STRUCT_CTRL(lisa_data4traces1)] /* [1,4000] */;
  uint32_t lisa_data4traces1v[4000 EXT_STRUCT_CTRL(lisa_data4traces1)] /* [0,65535] */;
  uint32_t lisa_data4traces2 /* [0,4000] */;
  uint32_t lisa_data4traces2I[4000 EXT_STRUCT_CTRL(lisa_data4traces2)] /* [1,4000] */;
  uint32_t lisa_data4traces2v[4000 EXT_STRUCT_CTRL(lisa_data4traces2)] /* [0,65535] */;
  uint32_t lisa_data4traces3 /* [0,4000] */;
  uint32_t lisa_data4traces3I[4000 EXT_STRUCT_CTRL(lisa_data4traces3)] /* [1,4000] */;
  uint32_t lisa_data4traces3v[4000 EXT_STRUCT_CTRL(lisa_data4traces3)] /* [0,65535] */;
  uint32_t lisa_data4traces4 /* [0,4000] */;
  uint32_t lisa_data4traces4I[4000 EXT_STRUCT_CTRL(lisa_data4traces4)] /* [1,4000] */;
  uint32_t lisa_data4traces4v[4000 EXT_STRUCT_CTRL(lisa_data4traces4)] /* [0,65535] */;
  uint32_t lisa_data4traces5 /* [0,4000] */;
  uint32_t lisa_data4traces5I[4000 EXT_STRUCT_CTRL(lisa_data4traces5)] /* [1,4000] */;
  uint32_t lisa_data4traces5v[4000 EXT_STRUCT_CTRL(lisa_data4traces5)] /* [0,65535] */;
  uint32_t lisa_data4traces6 /* [0,4000] */;
  uint32_t lisa_data4traces6I[4000 EXT_STRUCT_CTRL(lisa_data4traces6)] /* [1,4000] */;
  uint32_t lisa_data4traces6v[4000 EXT_STRUCT_CTRL(lisa_data4traces6)] /* [0,65535] */;
  uint32_t lisa_data4traces7 /* [0,4000] */;
  uint32_t lisa_data4traces7I[4000 EXT_STRUCT_CTRL(lisa_data4traces7)] /* [1,4000] */;
  uint32_t lisa_data4traces7v[4000 EXT_STRUCT_CTRL(lisa_data4traces7)] /* [0,65535] */;
  uint32_t lisa_data4traces8 /* [0,4000] */;
  uint32_t lisa_data4traces8I[4000 EXT_STRUCT_CTRL(lisa_data4traces8)] /* [1,4000] */;
  uint32_t lisa_data4traces8v[4000 EXT_STRUCT_CTRL(lisa_data4traces8)] /* [0,65535] */;
  uint32_t lisa_data4traces9 /* [0,4000] */;
  uint32_t lisa_data4traces9I[4000 EXT_STRUCT_CTRL(lisa_data4traces9)] /* [1,4000] */;
  uint32_t lisa_data4traces9v[4000 EXT_STRUCT_CTRL(lisa_data4traces9)] /* [0,65535] */;
  uint32_t lisa_data4traces10 /* [0,4000] */;
  uint32_t lisa_data4traces10I[4000 EXT_STRUCT_CTRL(lisa_data4traces10)] /* [1,4000] */;
  uint32_t lisa_data4traces10v[4000 EXT_STRUCT_CTRL(lisa_data4traces10)] /* [0,65535] */;
  uint32_t lisa_data4traces11 /* [0,4000] */;
  uint32_t lisa_data4traces11I[4000 EXT_STRUCT_CTRL(lisa_data4traces11)] /* [1,4000] */;
  uint32_t lisa_data4traces11v[4000 EXT_STRUCT_CTRL(lisa_data4traces11)] /* [0,65535] */;
  uint32_t lisa_data4traces12 /* [0,4000] */;
  uint32_t lisa_data4traces12I[4000 EXT_STRUCT_CTRL(lisa_data4traces12)] /* [1,4000] */;
  uint32_t lisa_data4traces12v[4000 EXT_STRUCT_CTRL(lisa_data4traces12)] /* [0,65535] */;
  uint32_t lisa_data4traces13 /* [0,4000] */;
  uint32_t lisa_data4traces13I[4000 EXT_STRUCT_CTRL(lisa_data4traces13)] /* [1,4000] */;
  uint32_t lisa_data4traces13v[4000 EXT_STRUCT_CTRL(lisa_data4traces13)] /* [0,65535] */;
  uint32_t lisa_data4traces14 /* [0,4000] */;
  uint32_t lisa_data4traces14I[4000 EXT_STRUCT_CTRL(lisa_data4traces14)] /* [1,4000] */;
  uint32_t lisa_data4traces14v[4000 EXT_STRUCT_CTRL(lisa_data4traces14)] /* [0,65535] */;
  uint32_t lisa_data4traces15 /* [0,4000] */;
  uint32_t lisa_data4traces15I[4000 EXT_STRUCT_CTRL(lisa_data4traces15)] /* [1,4000] */;
  uint32_t lisa_data4traces15v[4000 EXT_STRUCT_CTRL(lisa_data4traces15)] /* [0,65535] */;
  uint32_t lisa_data4traces16 /* [0,4000] */;
  uint32_t lisa_data4traces16I[4000 EXT_STRUCT_CTRL(lisa_data4traces16)] /* [1,4000] */;
  uint32_t lisa_data4traces16v[4000 EXT_STRUCT_CTRL(lisa_data4traces16)] /* [0,65535] */;
  uint32_t lisa_data5trig /* [0,255] */;
  uint32_t lisa_data5event_trigger_time_hi /* [-1,-1] */;
  uint32_t lisa_data5event_trigger_time_lo /* [-1,-1] */;
  uint32_t lisa_data5hit_pattern /* [0,65535] */;
  uint32_t lisa_data5num_channels_fired /* [-1,-1] */;
  uint32_t lisa_data5board_num /* [0,255] */;
  uint32_t lisa_data5channel_id /* [0,16] */;
  uint32_t lisa_data5channel_idI[16 EXT_STRUCT_CTRL(lisa_data5channel_id)] /* [1,16] */;
  uint32_t lisa_data5channel_idv[16 EXT_STRUCT_CTRL(lisa_data5channel_id)] /* [0,255] */;
  uint32_t lisa_data5channel_trigger_time_hi /* [0,16] */;
  uint32_t lisa_data5channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(lisa_data5channel_trigger_time_hi)] /* [1,16] */;
  uint32_t lisa_data5channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(lisa_data5channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t lisa_data5channel_trigger_time_lo /* [0,16] */;
  uint32_t lisa_data5channel_trigger_time_loI[16 EXT_STRUCT_CTRL(lisa_data5channel_trigger_time_lo)] /* [1,16] */;
  uint32_t lisa_data5channel_trigger_time_lov[16 EXT_STRUCT_CTRL(lisa_data5channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t lisa_data5pileup1 /* [0,255] */;
  uint32_t lisa_data5pileup2 /* [0,255] */;
  uint32_t lisa_data5pileup3 /* [0,255] */;
  uint32_t lisa_data5pileup4 /* [0,255] */;
  uint32_t lisa_data5pileup5 /* [0,255] */;
  uint32_t lisa_data5pileup6 /* [0,255] */;
  uint32_t lisa_data5pileup7 /* [0,255] */;
  uint32_t lisa_data5pileup8 /* [0,255] */;
  uint32_t lisa_data5pileup9 /* [0,255] */;
  uint32_t lisa_data5pileup10 /* [0,255] */;
  uint32_t lisa_data5pileup11 /* [0,255] */;
  uint32_t lisa_data5pileup12 /* [0,255] */;
  uint32_t lisa_data5pileup13 /* [0,255] */;
  uint32_t lisa_data5pileup14 /* [0,255] */;
  uint32_t lisa_data5pileup15 /* [0,255] */;
  uint32_t lisa_data5pileup16 /* [0,255] */;
  uint32_t lisa_data5overflow1 /* [0,255] */;
  uint32_t lisa_data5overflow2 /* [0,255] */;
  uint32_t lisa_data5overflow3 /* [0,255] */;
  uint32_t lisa_data5overflow4 /* [0,255] */;
  uint32_t lisa_data5overflow5 /* [0,255] */;
  uint32_t lisa_data5overflow6 /* [0,255] */;
  uint32_t lisa_data5overflow7 /* [0,255] */;
  uint32_t lisa_data5overflow8 /* [0,255] */;
  uint32_t lisa_data5overflow9 /* [0,255] */;
  uint32_t lisa_data5overflow10 /* [0,255] */;
  uint32_t lisa_data5overflow11 /* [0,255] */;
  uint32_t lisa_data5overflow12 /* [0,255] */;
  uint32_t lisa_data5overflow13 /* [0,255] */;
  uint32_t lisa_data5overflow14 /* [0,255] */;
  uint32_t lisa_data5overflow15 /* [0,255] */;
  uint32_t lisa_data5overflow16 /* [0,255] */;
  uint32_t lisa_data5channel_cfd /* [0,16] */;
  uint32_t lisa_data5channel_cfdI[16 EXT_STRUCT_CTRL(lisa_data5channel_cfd)] /* [1,16] */;
  uint32_t lisa_data5channel_cfdv[16 EXT_STRUCT_CTRL(lisa_data5channel_cfd)] /* [0,255] */;
  uint32_t lisa_data5channel_energy /* [0,16] */;
  uint32_t lisa_data5channel_energyI[16 EXT_STRUCT_CTRL(lisa_data5channel_energy)] /* [1,16] */;
  uint32_t lisa_data5channel_energyv[16 EXT_STRUCT_CTRL(lisa_data5channel_energy)] /* [-1,-1] */;
  uint32_t lisa_data5channel_id_traces /* [0,16] */;
  uint32_t lisa_data5channel_id_tracesI[16 EXT_STRUCT_CTRL(lisa_data5channel_id_traces)] /* [1,16] */;
  uint32_t lisa_data5channel_id_tracesv[16 EXT_STRUCT_CTRL(lisa_data5channel_id_traces)] /* [0,255] */;
  uint32_t lisa_data5traces1 /* [0,4000] */;
  uint32_t lisa_data5traces1I[4000 EXT_STRUCT_CTRL(lisa_data5traces1)] /* [1,4000] */;
  uint32_t lisa_data5traces1v[4000 EXT_STRUCT_CTRL(lisa_data5traces1)] /* [0,65535] */;
  uint32_t lisa_data5traces2 /* [0,4000] */;
  uint32_t lisa_data5traces2I[4000 EXT_STRUCT_CTRL(lisa_data5traces2)] /* [1,4000] */;
  uint32_t lisa_data5traces2v[4000 EXT_STRUCT_CTRL(lisa_data5traces2)] /* [0,65535] */;
  uint32_t lisa_data5traces3 /* [0,4000] */;
  uint32_t lisa_data5traces3I[4000 EXT_STRUCT_CTRL(lisa_data5traces3)] /* [1,4000] */;
  uint32_t lisa_data5traces3v[4000 EXT_STRUCT_CTRL(lisa_data5traces3)] /* [0,65535] */;
  uint32_t lisa_data5traces4 /* [0,4000] */;
  uint32_t lisa_data5traces4I[4000 EXT_STRUCT_CTRL(lisa_data5traces4)] /* [1,4000] */;
  uint32_t lisa_data5traces4v[4000 EXT_STRUCT_CTRL(lisa_data5traces4)] /* [0,65535] */;
  uint32_t lisa_data5traces5 /* [0,4000] */;
  uint32_t lisa_data5traces5I[4000 EXT_STRUCT_CTRL(lisa_data5traces5)] /* [1,4000] */;
  uint32_t lisa_data5traces5v[4000 EXT_STRUCT_CTRL(lisa_data5traces5)] /* [0,65535] */;
  uint32_t lisa_data5traces6 /* [0,4000] */;
  uint32_t lisa_data5traces6I[4000 EXT_STRUCT_CTRL(lisa_data5traces6)] /* [1,4000] */;
  uint32_t lisa_data5traces6v[4000 EXT_STRUCT_CTRL(lisa_data5traces6)] /* [0,65535] */;
  uint32_t lisa_data5traces7 /* [0,4000] */;
  uint32_t lisa_data5traces7I[4000 EXT_STRUCT_CTRL(lisa_data5traces7)] /* [1,4000] */;
  uint32_t lisa_data5traces7v[4000 EXT_STRUCT_CTRL(lisa_data5traces7)] /* [0,65535] */;
  uint32_t lisa_data5traces8 /* [0,4000] */;
  uint32_t lisa_data5traces8I[4000 EXT_STRUCT_CTRL(lisa_data5traces8)] /* [1,4000] */;
  uint32_t lisa_data5traces8v[4000 EXT_STRUCT_CTRL(lisa_data5traces8)] /* [0,65535] */;
  uint32_t lisa_data5traces9 /* [0,4000] */;
  uint32_t lisa_data5traces9I[4000 EXT_STRUCT_CTRL(lisa_data5traces9)] /* [1,4000] */;
  uint32_t lisa_data5traces9v[4000 EXT_STRUCT_CTRL(lisa_data5traces9)] /* [0,65535] */;
  uint32_t lisa_data5traces10 /* [0,4000] */;
  uint32_t lisa_data5traces10I[4000 EXT_STRUCT_CTRL(lisa_data5traces10)] /* [1,4000] */;
  uint32_t lisa_data5traces10v[4000 EXT_STRUCT_CTRL(lisa_data5traces10)] /* [0,65535] */;
  uint32_t lisa_data5traces11 /* [0,4000] */;
  uint32_t lisa_data5traces11I[4000 EXT_STRUCT_CTRL(lisa_data5traces11)] /* [1,4000] */;
  uint32_t lisa_data5traces11v[4000 EXT_STRUCT_CTRL(lisa_data5traces11)] /* [0,65535] */;
  uint32_t lisa_data5traces12 /* [0,4000] */;
  uint32_t lisa_data5traces12I[4000 EXT_STRUCT_CTRL(lisa_data5traces12)] /* [1,4000] */;
  uint32_t lisa_data5traces12v[4000 EXT_STRUCT_CTRL(lisa_data5traces12)] /* [0,65535] */;
  uint32_t lisa_data5traces13 /* [0,4000] */;
  uint32_t lisa_data5traces13I[4000 EXT_STRUCT_CTRL(lisa_data5traces13)] /* [1,4000] */;
  uint32_t lisa_data5traces13v[4000 EXT_STRUCT_CTRL(lisa_data5traces13)] /* [0,65535] */;
  uint32_t lisa_data5traces14 /* [0,4000] */;
  uint32_t lisa_data5traces14I[4000 EXT_STRUCT_CTRL(lisa_data5traces14)] /* [1,4000] */;
  uint32_t lisa_data5traces14v[4000 EXT_STRUCT_CTRL(lisa_data5traces14)] /* [0,65535] */;
  uint32_t lisa_data5traces15 /* [0,4000] */;
  uint32_t lisa_data5traces15I[4000 EXT_STRUCT_CTRL(lisa_data5traces15)] /* [1,4000] */;
  uint32_t lisa_data5traces15v[4000 EXT_STRUCT_CTRL(lisa_data5traces15)] /* [0,65535] */;
  uint32_t lisa_data5traces16 /* [0,4000] */;
  uint32_t lisa_data5traces16I[4000 EXT_STRUCT_CTRL(lisa_data5traces16)] /* [1,4000] */;
  uint32_t lisa_data5traces16v[4000 EXT_STRUCT_CTRL(lisa_data5traces16)] /* [0,65535] */;
  uint32_t lisa_data6trig /* [0,255] */;
  uint32_t lisa_data6event_trigger_time_hi /* [-1,-1] */;
  uint32_t lisa_data6event_trigger_time_lo /* [-1,-1] */;
  uint32_t lisa_data6hit_pattern /* [0,65535] */;
  uint32_t lisa_data6num_channels_fired /* [-1,-1] */;
  uint32_t lisa_data6board_num /* [0,255] */;
  uint32_t lisa_data6channel_id /* [0,16] */;
  uint32_t lisa_data6channel_idI[16 EXT_STRUCT_CTRL(lisa_data6channel_id)] /* [1,16] */;
  uint32_t lisa_data6channel_idv[16 EXT_STRUCT_CTRL(lisa_data6channel_id)] /* [0,255] */;
  uint32_t lisa_data6channel_trigger_time_hi /* [0,16] */;
  uint32_t lisa_data6channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(lisa_data6channel_trigger_time_hi)] /* [1,16] */;
  uint32_t lisa_data6channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(lisa_data6channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t lisa_data6channel_trigger_time_lo /* [0,16] */;
  uint32_t lisa_data6channel_trigger_time_loI[16 EXT_STRUCT_CTRL(lisa_data6channel_trigger_time_lo)] /* [1,16] */;
  uint32_t lisa_data6channel_trigger_time_lov[16 EXT_STRUCT_CTRL(lisa_data6channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t lisa_data6pileup1 /* [0,255] */;
  uint32_t lisa_data6pileup2 /* [0,255] */;
  uint32_t lisa_data6pileup3 /* [0,255] */;
  uint32_t lisa_data6pileup4 /* [0,255] */;
  uint32_t lisa_data6pileup5 /* [0,255] */;
  uint32_t lisa_data6pileup6 /* [0,255] */;
  uint32_t lisa_data6pileup7 /* [0,255] */;
  uint32_t lisa_data6pileup8 /* [0,255] */;
  uint32_t lisa_data6pileup9 /* [0,255] */;
  uint32_t lisa_data6pileup10 /* [0,255] */;
  uint32_t lisa_data6pileup11 /* [0,255] */;
  uint32_t lisa_data6pileup12 /* [0,255] */;
  uint32_t lisa_data6pileup13 /* [0,255] */;
  uint32_t lisa_data6pileup14 /* [0,255] */;
  uint32_t lisa_data6pileup15 /* [0,255] */;
  uint32_t lisa_data6pileup16 /* [0,255] */;
  uint32_t lisa_data6overflow1 /* [0,255] */;
  uint32_t lisa_data6overflow2 /* [0,255] */;
  uint32_t lisa_data6overflow3 /* [0,255] */;
  uint32_t lisa_data6overflow4 /* [0,255] */;
  uint32_t lisa_data6overflow5 /* [0,255] */;
  uint32_t lisa_data6overflow6 /* [0,255] */;
  uint32_t lisa_data6overflow7 /* [0,255] */;
  uint32_t lisa_data6overflow8 /* [0,255] */;
  uint32_t lisa_data6overflow9 /* [0,255] */;
  uint32_t lisa_data6overflow10 /* [0,255] */;
  uint32_t lisa_data6overflow11 /* [0,255] */;
  uint32_t lisa_data6overflow12 /* [0,255] */;
  uint32_t lisa_data6overflow13 /* [0,255] */;
  uint32_t lisa_data6overflow14 /* [0,255] */;
  uint32_t lisa_data6overflow15 /* [0,255] */;
  uint32_t lisa_data6overflow16 /* [0,255] */;
  uint32_t lisa_data6channel_cfd /* [0,16] */;
  uint32_t lisa_data6channel_cfdI[16 EXT_STRUCT_CTRL(lisa_data6channel_cfd)] /* [1,16] */;
  uint32_t lisa_data6channel_cfdv[16 EXT_STRUCT_CTRL(lisa_data6channel_cfd)] /* [0,255] */;
  uint32_t lisa_data6channel_energy /* [0,16] */;
  uint32_t lisa_data6channel_energyI[16 EXT_STRUCT_CTRL(lisa_data6channel_energy)] /* [1,16] */;
  uint32_t lisa_data6channel_energyv[16 EXT_STRUCT_CTRL(lisa_data6channel_energy)] /* [-1,-1] */;
  uint32_t lisa_data6channel_id_traces /* [0,16] */;
  uint32_t lisa_data6channel_id_tracesI[16 EXT_STRUCT_CTRL(lisa_data6channel_id_traces)] /* [1,16] */;
  uint32_t lisa_data6channel_id_tracesv[16 EXT_STRUCT_CTRL(lisa_data6channel_id_traces)] /* [0,255] */;
  uint32_t lisa_data6traces1 /* [0,4000] */;
  uint32_t lisa_data6traces1I[4000 EXT_STRUCT_CTRL(lisa_data6traces1)] /* [1,4000] */;
  uint32_t lisa_data6traces1v[4000 EXT_STRUCT_CTRL(lisa_data6traces1)] /* [0,65535] */;
  uint32_t lisa_data6traces2 /* [0,4000] */;
  uint32_t lisa_data6traces2I[4000 EXT_STRUCT_CTRL(lisa_data6traces2)] /* [1,4000] */;
  uint32_t lisa_data6traces2v[4000 EXT_STRUCT_CTRL(lisa_data6traces2)] /* [0,65535] */;
  uint32_t lisa_data6traces3 /* [0,4000] */;
  uint32_t lisa_data6traces3I[4000 EXT_STRUCT_CTRL(lisa_data6traces3)] /* [1,4000] */;
  uint32_t lisa_data6traces3v[4000 EXT_STRUCT_CTRL(lisa_data6traces3)] /* [0,65535] */;
  uint32_t lisa_data6traces4 /* [0,4000] */;
  uint32_t lisa_data6traces4I[4000 EXT_STRUCT_CTRL(lisa_data6traces4)] /* [1,4000] */;
  uint32_t lisa_data6traces4v[4000 EXT_STRUCT_CTRL(lisa_data6traces4)] /* [0,65535] */;
  uint32_t lisa_data6traces5 /* [0,4000] */;
  uint32_t lisa_data6traces5I[4000 EXT_STRUCT_CTRL(lisa_data6traces5)] /* [1,4000] */;
  uint32_t lisa_data6traces5v[4000 EXT_STRUCT_CTRL(lisa_data6traces5)] /* [0,65535] */;
  uint32_t lisa_data6traces6 /* [0,4000] */;
  uint32_t lisa_data6traces6I[4000 EXT_STRUCT_CTRL(lisa_data6traces6)] /* [1,4000] */;
  uint32_t lisa_data6traces6v[4000 EXT_STRUCT_CTRL(lisa_data6traces6)] /* [0,65535] */;
  uint32_t lisa_data6traces7 /* [0,4000] */;
  uint32_t lisa_data6traces7I[4000 EXT_STRUCT_CTRL(lisa_data6traces7)] /* [1,4000] */;
  uint32_t lisa_data6traces7v[4000 EXT_STRUCT_CTRL(lisa_data6traces7)] /* [0,65535] */;
  uint32_t lisa_data6traces8 /* [0,4000] */;
  uint32_t lisa_data6traces8I[4000 EXT_STRUCT_CTRL(lisa_data6traces8)] /* [1,4000] */;
  uint32_t lisa_data6traces8v[4000 EXT_STRUCT_CTRL(lisa_data6traces8)] /* [0,65535] */;
  uint32_t lisa_data6traces9 /* [0,4000] */;
  uint32_t lisa_data6traces9I[4000 EXT_STRUCT_CTRL(lisa_data6traces9)] /* [1,4000] */;
  uint32_t lisa_data6traces9v[4000 EXT_STRUCT_CTRL(lisa_data6traces9)] /* [0,65535] */;
  uint32_t lisa_data6traces10 /* [0,4000] */;
  uint32_t lisa_data6traces10I[4000 EXT_STRUCT_CTRL(lisa_data6traces10)] /* [1,4000] */;
  uint32_t lisa_data6traces10v[4000 EXT_STRUCT_CTRL(lisa_data6traces10)] /* [0,65535] */;
  uint32_t lisa_data6traces11 /* [0,4000] */;
  uint32_t lisa_data6traces11I[4000 EXT_STRUCT_CTRL(lisa_data6traces11)] /* [1,4000] */;
  uint32_t lisa_data6traces11v[4000 EXT_STRUCT_CTRL(lisa_data6traces11)] /* [0,65535] */;
  uint32_t lisa_data6traces12 /* [0,4000] */;
  uint32_t lisa_data6traces12I[4000 EXT_STRUCT_CTRL(lisa_data6traces12)] /* [1,4000] */;
  uint32_t lisa_data6traces12v[4000 EXT_STRUCT_CTRL(lisa_data6traces12)] /* [0,65535] */;
  uint32_t lisa_data6traces13 /* [0,4000] */;
  uint32_t lisa_data6traces13I[4000 EXT_STRUCT_CTRL(lisa_data6traces13)] /* [1,4000] */;
  uint32_t lisa_data6traces13v[4000 EXT_STRUCT_CTRL(lisa_data6traces13)] /* [0,65535] */;
  uint32_t lisa_data6traces14 /* [0,4000] */;
  uint32_t lisa_data6traces14I[4000 EXT_STRUCT_CTRL(lisa_data6traces14)] /* [1,4000] */;
  uint32_t lisa_data6traces14v[4000 EXT_STRUCT_CTRL(lisa_data6traces14)] /* [0,65535] */;
  uint32_t lisa_data6traces15 /* [0,4000] */;
  uint32_t lisa_data6traces15I[4000 EXT_STRUCT_CTRL(lisa_data6traces15)] /* [1,4000] */;
  uint32_t lisa_data6traces15v[4000 EXT_STRUCT_CTRL(lisa_data6traces15)] /* [0,65535] */;
  uint32_t lisa_data6traces16 /* [0,4000] */;
  uint32_t lisa_data6traces16I[4000 EXT_STRUCT_CTRL(lisa_data6traces16)] /* [1,4000] */;
  uint32_t lisa_data6traces16v[4000 EXT_STRUCT_CTRL(lisa_data6traces16)] /* [0,65535] */;
  uint32_t lisa_data7trig /* [0,255] */;
  uint32_t lisa_data7event_trigger_time_hi /* [-1,-1] */;
  uint32_t lisa_data7event_trigger_time_lo /* [-1,-1] */;
  uint32_t lisa_data7hit_pattern /* [0,65535] */;
  uint32_t lisa_data7num_channels_fired /* [-1,-1] */;
  uint32_t lisa_data7board_num /* [0,255] */;
  uint32_t lisa_data7channel_id /* [0,16] */;
  uint32_t lisa_data7channel_idI[16 EXT_STRUCT_CTRL(lisa_data7channel_id)] /* [1,16] */;
  uint32_t lisa_data7channel_idv[16 EXT_STRUCT_CTRL(lisa_data7channel_id)] /* [0,255] */;
  uint32_t lisa_data7channel_trigger_time_hi /* [0,16] */;
  uint32_t lisa_data7channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(lisa_data7channel_trigger_time_hi)] /* [1,16] */;
  uint32_t lisa_data7channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(lisa_data7channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t lisa_data7channel_trigger_time_lo /* [0,16] */;
  uint32_t lisa_data7channel_trigger_time_loI[16 EXT_STRUCT_CTRL(lisa_data7channel_trigger_time_lo)] /* [1,16] */;
  uint32_t lisa_data7channel_trigger_time_lov[16 EXT_STRUCT_CTRL(lisa_data7channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t lisa_data7pileup1 /* [0,255] */;
  uint32_t lisa_data7pileup2 /* [0,255] */;
  uint32_t lisa_data7pileup3 /* [0,255] */;
  uint32_t lisa_data7pileup4 /* [0,255] */;
  uint32_t lisa_data7pileup5 /* [0,255] */;
  uint32_t lisa_data7pileup6 /* [0,255] */;
  uint32_t lisa_data7pileup7 /* [0,255] */;
  uint32_t lisa_data7pileup8 /* [0,255] */;
  uint32_t lisa_data7pileup9 /* [0,255] */;
  uint32_t lisa_data7pileup10 /* [0,255] */;
  uint32_t lisa_data7pileup11 /* [0,255] */;
  uint32_t lisa_data7pileup12 /* [0,255] */;
  uint32_t lisa_data7pileup13 /* [0,255] */;
  uint32_t lisa_data7pileup14 /* [0,255] */;
  uint32_t lisa_data7pileup15 /* [0,255] */;
  uint32_t lisa_data7pileup16 /* [0,255] */;
  uint32_t lisa_data7overflow1 /* [0,255] */;
  uint32_t lisa_data7overflow2 /* [0,255] */;
  uint32_t lisa_data7overflow3 /* [0,255] */;
  uint32_t lisa_data7overflow4 /* [0,255] */;
  uint32_t lisa_data7overflow5 /* [0,255] */;
  uint32_t lisa_data7overflow6 /* [0,255] */;
  uint32_t lisa_data7overflow7 /* [0,255] */;
  uint32_t lisa_data7overflow8 /* [0,255] */;
  uint32_t lisa_data7overflow9 /* [0,255] */;
  uint32_t lisa_data7overflow10 /* [0,255] */;
  uint32_t lisa_data7overflow11 /* [0,255] */;
  uint32_t lisa_data7overflow12 /* [0,255] */;
  uint32_t lisa_data7overflow13 /* [0,255] */;
  uint32_t lisa_data7overflow14 /* [0,255] */;
  uint32_t lisa_data7overflow15 /* [0,255] */;
  uint32_t lisa_data7overflow16 /* [0,255] */;
  uint32_t lisa_data7channel_cfd /* [0,16] */;
  uint32_t lisa_data7channel_cfdI[16 EXT_STRUCT_CTRL(lisa_data7channel_cfd)] /* [1,16] */;
  uint32_t lisa_data7channel_cfdv[16 EXT_STRUCT_CTRL(lisa_data7channel_cfd)] /* [0,255] */;
  uint32_t lisa_data7channel_energy /* [0,16] */;
  uint32_t lisa_data7channel_energyI[16 EXT_STRUCT_CTRL(lisa_data7channel_energy)] /* [1,16] */;
  uint32_t lisa_data7channel_energyv[16 EXT_STRUCT_CTRL(lisa_data7channel_energy)] /* [-1,-1] */;
  uint32_t lisa_data7channel_id_traces /* [0,16] */;
  uint32_t lisa_data7channel_id_tracesI[16 EXT_STRUCT_CTRL(lisa_data7channel_id_traces)] /* [1,16] */;
  uint32_t lisa_data7channel_id_tracesv[16 EXT_STRUCT_CTRL(lisa_data7channel_id_traces)] /* [0,255] */;
  uint32_t lisa_data7traces1 /* [0,4000] */;
  uint32_t lisa_data7traces1I[4000 EXT_STRUCT_CTRL(lisa_data7traces1)] /* [1,4000] */;
  uint32_t lisa_data7traces1v[4000 EXT_STRUCT_CTRL(lisa_data7traces1)] /* [0,65535] */;
  uint32_t lisa_data7traces2 /* [0,4000] */;
  uint32_t lisa_data7traces2I[4000 EXT_STRUCT_CTRL(lisa_data7traces2)] /* [1,4000] */;
  uint32_t lisa_data7traces2v[4000 EXT_STRUCT_CTRL(lisa_data7traces2)] /* [0,65535] */;
  uint32_t lisa_data7traces3 /* [0,4000] */;
  uint32_t lisa_data7traces3I[4000 EXT_STRUCT_CTRL(lisa_data7traces3)] /* [1,4000] */;
  uint32_t lisa_data7traces3v[4000 EXT_STRUCT_CTRL(lisa_data7traces3)] /* [0,65535] */;
  uint32_t lisa_data7traces4 /* [0,4000] */;
  uint32_t lisa_data7traces4I[4000 EXT_STRUCT_CTRL(lisa_data7traces4)] /* [1,4000] */;
  uint32_t lisa_data7traces4v[4000 EXT_STRUCT_CTRL(lisa_data7traces4)] /* [0,65535] */;
  uint32_t lisa_data7traces5 /* [0,4000] */;
  uint32_t lisa_data7traces5I[4000 EXT_STRUCT_CTRL(lisa_data7traces5)] /* [1,4000] */;
  uint32_t lisa_data7traces5v[4000 EXT_STRUCT_CTRL(lisa_data7traces5)] /* [0,65535] */;
  uint32_t lisa_data7traces6 /* [0,4000] */;
  uint32_t lisa_data7traces6I[4000 EXT_STRUCT_CTRL(lisa_data7traces6)] /* [1,4000] */;
  uint32_t lisa_data7traces6v[4000 EXT_STRUCT_CTRL(lisa_data7traces6)] /* [0,65535] */;
  uint32_t lisa_data7traces7 /* [0,4000] */;
  uint32_t lisa_data7traces7I[4000 EXT_STRUCT_CTRL(lisa_data7traces7)] /* [1,4000] */;
  uint32_t lisa_data7traces7v[4000 EXT_STRUCT_CTRL(lisa_data7traces7)] /* [0,65535] */;
  uint32_t lisa_data7traces8 /* [0,4000] */;
  uint32_t lisa_data7traces8I[4000 EXT_STRUCT_CTRL(lisa_data7traces8)] /* [1,4000] */;
  uint32_t lisa_data7traces8v[4000 EXT_STRUCT_CTRL(lisa_data7traces8)] /* [0,65535] */;
  uint32_t lisa_data7traces9 /* [0,4000] */;
  uint32_t lisa_data7traces9I[4000 EXT_STRUCT_CTRL(lisa_data7traces9)] /* [1,4000] */;
  uint32_t lisa_data7traces9v[4000 EXT_STRUCT_CTRL(lisa_data7traces9)] /* [0,65535] */;
  uint32_t lisa_data7traces10 /* [0,4000] */;
  uint32_t lisa_data7traces10I[4000 EXT_STRUCT_CTRL(lisa_data7traces10)] /* [1,4000] */;
  uint32_t lisa_data7traces10v[4000 EXT_STRUCT_CTRL(lisa_data7traces10)] /* [0,65535] */;
  uint32_t lisa_data7traces11 /* [0,4000] */;
  uint32_t lisa_data7traces11I[4000 EXT_STRUCT_CTRL(lisa_data7traces11)] /* [1,4000] */;
  uint32_t lisa_data7traces11v[4000 EXT_STRUCT_CTRL(lisa_data7traces11)] /* [0,65535] */;
  uint32_t lisa_data7traces12 /* [0,4000] */;
  uint32_t lisa_data7traces12I[4000 EXT_STRUCT_CTRL(lisa_data7traces12)] /* [1,4000] */;
  uint32_t lisa_data7traces12v[4000 EXT_STRUCT_CTRL(lisa_data7traces12)] /* [0,65535] */;
  uint32_t lisa_data7traces13 /* [0,4000] */;
  uint32_t lisa_data7traces13I[4000 EXT_STRUCT_CTRL(lisa_data7traces13)] /* [1,4000] */;
  uint32_t lisa_data7traces13v[4000 EXT_STRUCT_CTRL(lisa_data7traces13)] /* [0,65535] */;
  uint32_t lisa_data7traces14 /* [0,4000] */;
  uint32_t lisa_data7traces14I[4000 EXT_STRUCT_CTRL(lisa_data7traces14)] /* [1,4000] */;
  uint32_t lisa_data7traces14v[4000 EXT_STRUCT_CTRL(lisa_data7traces14)] /* [0,65535] */;
  uint32_t lisa_data7traces15 /* [0,4000] */;
  uint32_t lisa_data7traces15I[4000 EXT_STRUCT_CTRL(lisa_data7traces15)] /* [1,4000] */;
  uint32_t lisa_data7traces15v[4000 EXT_STRUCT_CTRL(lisa_data7traces15)] /* [0,65535] */;
  uint32_t lisa_data7traces16 /* [0,4000] */;
  uint32_t lisa_data7traces16I[4000 EXT_STRUCT_CTRL(lisa_data7traces16)] /* [1,4000] */;
  uint32_t lisa_data7traces16v[4000 EXT_STRUCT_CTRL(lisa_data7traces16)] /* [0,65535] */;
  uint32_t lisa_data8trig /* [0,255] */;
  uint32_t lisa_data8event_trigger_time_hi /* [-1,-1] */;
  uint32_t lisa_data8event_trigger_time_lo /* [-1,-1] */;
  uint32_t lisa_data8hit_pattern /* [0,65535] */;
  uint32_t lisa_data8num_channels_fired /* [-1,-1] */;
  uint32_t lisa_data8board_num /* [0,255] */;
  uint32_t lisa_data8channel_id /* [0,16] */;
  uint32_t lisa_data8channel_idI[16 EXT_STRUCT_CTRL(lisa_data8channel_id)] /* [1,16] */;
  uint32_t lisa_data8channel_idv[16 EXT_STRUCT_CTRL(lisa_data8channel_id)] /* [0,255] */;
  uint32_t lisa_data8channel_trigger_time_hi /* [0,16] */;
  uint32_t lisa_data8channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(lisa_data8channel_trigger_time_hi)] /* [1,16] */;
  uint32_t lisa_data8channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(lisa_data8channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t lisa_data8channel_trigger_time_lo /* [0,16] */;
  uint32_t lisa_data8channel_trigger_time_loI[16 EXT_STRUCT_CTRL(lisa_data8channel_trigger_time_lo)] /* [1,16] */;
  uint32_t lisa_data8channel_trigger_time_lov[16 EXT_STRUCT_CTRL(lisa_data8channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t lisa_data8pileup1 /* [0,255] */;
  uint32_t lisa_data8pileup2 /* [0,255] */;
  uint32_t lisa_data8pileup3 /* [0,255] */;
  uint32_t lisa_data8pileup4 /* [0,255] */;
  uint32_t lisa_data8pileup5 /* [0,255] */;
  uint32_t lisa_data8pileup6 /* [0,255] */;
  uint32_t lisa_data8pileup7 /* [0,255] */;
  uint32_t lisa_data8pileup8 /* [0,255] */;
  uint32_t lisa_data8pileup9 /* [0,255] */;
  uint32_t lisa_data8pileup10 /* [0,255] */;
  uint32_t lisa_data8pileup11 /* [0,255] */;
  uint32_t lisa_data8pileup12 /* [0,255] */;
  uint32_t lisa_data8pileup13 /* [0,255] */;
  uint32_t lisa_data8pileup14 /* [0,255] */;
  uint32_t lisa_data8pileup15 /* [0,255] */;
  uint32_t lisa_data8pileup16 /* [0,255] */;
  uint32_t lisa_data8overflow1 /* [0,255] */;
  uint32_t lisa_data8overflow2 /* [0,255] */;
  uint32_t lisa_data8overflow3 /* [0,255] */;
  uint32_t lisa_data8overflow4 /* [0,255] */;
  uint32_t lisa_data8overflow5 /* [0,255] */;
  uint32_t lisa_data8overflow6 /* [0,255] */;
  uint32_t lisa_data8overflow7 /* [0,255] */;
  uint32_t lisa_data8overflow8 /* [0,255] */;
  uint32_t lisa_data8overflow9 /* [0,255] */;
  uint32_t lisa_data8overflow10 /* [0,255] */;
  uint32_t lisa_data8overflow11 /* [0,255] */;
  uint32_t lisa_data8overflow12 /* [0,255] */;
  uint32_t lisa_data8overflow13 /* [0,255] */;
  uint32_t lisa_data8overflow14 /* [0,255] */;
  uint32_t lisa_data8overflow15 /* [0,255] */;
  uint32_t lisa_data8overflow16 /* [0,255] */;
  uint32_t lisa_data8channel_cfd /* [0,16] */;
  uint32_t lisa_data8channel_cfdI[16 EXT_STRUCT_CTRL(lisa_data8channel_cfd)] /* [1,16] */;
  uint32_t lisa_data8channel_cfdv[16 EXT_STRUCT_CTRL(lisa_data8channel_cfd)] /* [0,255] */;
  uint32_t lisa_data8channel_energy /* [0,16] */;
  uint32_t lisa_data8channel_energyI[16 EXT_STRUCT_CTRL(lisa_data8channel_energy)] /* [1,16] */;
  uint32_t lisa_data8channel_energyv[16 EXT_STRUCT_CTRL(lisa_data8channel_energy)] /* [-1,-1] */;
  uint32_t lisa_data8channel_id_traces /* [0,16] */;
  uint32_t lisa_data8channel_id_tracesI[16 EXT_STRUCT_CTRL(lisa_data8channel_id_traces)] /* [1,16] */;
  uint32_t lisa_data8channel_id_tracesv[16 EXT_STRUCT_CTRL(lisa_data8channel_id_traces)] /* [0,255] */;
  uint32_t lisa_data8traces1 /* [0,4000] */;
  uint32_t lisa_data8traces1I[4000 EXT_STRUCT_CTRL(lisa_data8traces1)] /* [1,4000] */;
  uint32_t lisa_data8traces1v[4000 EXT_STRUCT_CTRL(lisa_data8traces1)] /* [0,65535] */;
  uint32_t lisa_data8traces2 /* [0,4000] */;
  uint32_t lisa_data8traces2I[4000 EXT_STRUCT_CTRL(lisa_data8traces2)] /* [1,4000] */;
  uint32_t lisa_data8traces2v[4000 EXT_STRUCT_CTRL(lisa_data8traces2)] /* [0,65535] */;
  uint32_t lisa_data8traces3 /* [0,4000] */;
  uint32_t lisa_data8traces3I[4000 EXT_STRUCT_CTRL(lisa_data8traces3)] /* [1,4000] */;
  uint32_t lisa_data8traces3v[4000 EXT_STRUCT_CTRL(lisa_data8traces3)] /* [0,65535] */;
  uint32_t lisa_data8traces4 /* [0,4000] */;
  uint32_t lisa_data8traces4I[4000 EXT_STRUCT_CTRL(lisa_data8traces4)] /* [1,4000] */;
  uint32_t lisa_data8traces4v[4000 EXT_STRUCT_CTRL(lisa_data8traces4)] /* [0,65535] */;
  uint32_t lisa_data8traces5 /* [0,4000] */;
  uint32_t lisa_data8traces5I[4000 EXT_STRUCT_CTRL(lisa_data8traces5)] /* [1,4000] */;
  uint32_t lisa_data8traces5v[4000 EXT_STRUCT_CTRL(lisa_data8traces5)] /* [0,65535] */;
  uint32_t lisa_data8traces6 /* [0,4000] */;
  uint32_t lisa_data8traces6I[4000 EXT_STRUCT_CTRL(lisa_data8traces6)] /* [1,4000] */;
  uint32_t lisa_data8traces6v[4000 EXT_STRUCT_CTRL(lisa_data8traces6)] /* [0,65535] */;
  uint32_t lisa_data8traces7 /* [0,4000] */;
  uint32_t lisa_data8traces7I[4000 EXT_STRUCT_CTRL(lisa_data8traces7)] /* [1,4000] */;
  uint32_t lisa_data8traces7v[4000 EXT_STRUCT_CTRL(lisa_data8traces7)] /* [0,65535] */;
  uint32_t lisa_data8traces8 /* [0,4000] */;
  uint32_t lisa_data8traces8I[4000 EXT_STRUCT_CTRL(lisa_data8traces8)] /* [1,4000] */;
  uint32_t lisa_data8traces8v[4000 EXT_STRUCT_CTRL(lisa_data8traces8)] /* [0,65535] */;
  uint32_t lisa_data8traces9 /* [0,4000] */;
  uint32_t lisa_data8traces9I[4000 EXT_STRUCT_CTRL(lisa_data8traces9)] /* [1,4000] */;
  uint32_t lisa_data8traces9v[4000 EXT_STRUCT_CTRL(lisa_data8traces9)] /* [0,65535] */;
  uint32_t lisa_data8traces10 /* [0,4000] */;
  uint32_t lisa_data8traces10I[4000 EXT_STRUCT_CTRL(lisa_data8traces10)] /* [1,4000] */;
  uint32_t lisa_data8traces10v[4000 EXT_STRUCT_CTRL(lisa_data8traces10)] /* [0,65535] */;
  uint32_t lisa_data8traces11 /* [0,4000] */;
  uint32_t lisa_data8traces11I[4000 EXT_STRUCT_CTRL(lisa_data8traces11)] /* [1,4000] */;
  uint32_t lisa_data8traces11v[4000 EXT_STRUCT_CTRL(lisa_data8traces11)] /* [0,65535] */;
  uint32_t lisa_data8traces12 /* [0,4000] */;
  uint32_t lisa_data8traces12I[4000 EXT_STRUCT_CTRL(lisa_data8traces12)] /* [1,4000] */;
  uint32_t lisa_data8traces12v[4000 EXT_STRUCT_CTRL(lisa_data8traces12)] /* [0,65535] */;
  uint32_t lisa_data8traces13 /* [0,4000] */;
  uint32_t lisa_data8traces13I[4000 EXT_STRUCT_CTRL(lisa_data8traces13)] /* [1,4000] */;
  uint32_t lisa_data8traces13v[4000 EXT_STRUCT_CTRL(lisa_data8traces13)] /* [0,65535] */;
  uint32_t lisa_data8traces14 /* [0,4000] */;
  uint32_t lisa_data8traces14I[4000 EXT_STRUCT_CTRL(lisa_data8traces14)] /* [1,4000] */;
  uint32_t lisa_data8traces14v[4000 EXT_STRUCT_CTRL(lisa_data8traces14)] /* [0,65535] */;
  uint32_t lisa_data8traces15 /* [0,4000] */;
  uint32_t lisa_data8traces15I[4000 EXT_STRUCT_CTRL(lisa_data8traces15)] /* [1,4000] */;
  uint32_t lisa_data8traces15v[4000 EXT_STRUCT_CTRL(lisa_data8traces15)] /* [0,65535] */;
  uint32_t lisa_data8traces16 /* [0,4000] */;
  uint32_t lisa_data8traces16I[4000 EXT_STRUCT_CTRL(lisa_data8traces16)] /* [1,4000] */;
  uint32_t lisa_data8traces16v[4000 EXT_STRUCT_CTRL(lisa_data8traces16)] /* [0,65535] */;
  uint32_t lisa_data9trig /* [0,255] */;
  uint32_t lisa_data9event_trigger_time_hi /* [-1,-1] */;
  uint32_t lisa_data9event_trigger_time_lo /* [-1,-1] */;
  uint32_t lisa_data9hit_pattern /* [0,65535] */;
  uint32_t lisa_data9num_channels_fired /* [-1,-1] */;
  uint32_t lisa_data9board_num /* [0,255] */;
  uint32_t lisa_data9channel_id /* [0,16] */;
  uint32_t lisa_data9channel_idI[16 EXT_STRUCT_CTRL(lisa_data9channel_id)] /* [1,16] */;
  uint32_t lisa_data9channel_idv[16 EXT_STRUCT_CTRL(lisa_data9channel_id)] /* [0,255] */;
  uint32_t lisa_data9channel_trigger_time_hi /* [0,16] */;
  uint32_t lisa_data9channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(lisa_data9channel_trigger_time_hi)] /* [1,16] */;
  uint32_t lisa_data9channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(lisa_data9channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t lisa_data9channel_trigger_time_lo /* [0,16] */;
  uint32_t lisa_data9channel_trigger_time_loI[16 EXT_STRUCT_CTRL(lisa_data9channel_trigger_time_lo)] /* [1,16] */;
  uint32_t lisa_data9channel_trigger_time_lov[16 EXT_STRUCT_CTRL(lisa_data9channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t lisa_data9pileup1 /* [0,255] */;
  uint32_t lisa_data9pileup2 /* [0,255] */;
  uint32_t lisa_data9pileup3 /* [0,255] */;
  uint32_t lisa_data9pileup4 /* [0,255] */;
  uint32_t lisa_data9pileup5 /* [0,255] */;
  uint32_t lisa_data9pileup6 /* [0,255] */;
  uint32_t lisa_data9pileup7 /* [0,255] */;
  uint32_t lisa_data9pileup8 /* [0,255] */;
  uint32_t lisa_data9pileup9 /* [0,255] */;
  uint32_t lisa_data9pileup10 /* [0,255] */;
  uint32_t lisa_data9pileup11 /* [0,255] */;
  uint32_t lisa_data9pileup12 /* [0,255] */;
  uint32_t lisa_data9pileup13 /* [0,255] */;
  uint32_t lisa_data9pileup14 /* [0,255] */;
  uint32_t lisa_data9pileup15 /* [0,255] */;
  uint32_t lisa_data9pileup16 /* [0,255] */;
  uint32_t lisa_data9overflow1 /* [0,255] */;
  uint32_t lisa_data9overflow2 /* [0,255] */;
  uint32_t lisa_data9overflow3 /* [0,255] */;
  uint32_t lisa_data9overflow4 /* [0,255] */;
  uint32_t lisa_data9overflow5 /* [0,255] */;
  uint32_t lisa_data9overflow6 /* [0,255] */;
  uint32_t lisa_data9overflow7 /* [0,255] */;
  uint32_t lisa_data9overflow8 /* [0,255] */;
  uint32_t lisa_data9overflow9 /* [0,255] */;
  uint32_t lisa_data9overflow10 /* [0,255] */;
  uint32_t lisa_data9overflow11 /* [0,255] */;
  uint32_t lisa_data9overflow12 /* [0,255] */;
  uint32_t lisa_data9overflow13 /* [0,255] */;
  uint32_t lisa_data9overflow14 /* [0,255] */;
  uint32_t lisa_data9overflow15 /* [0,255] */;
  uint32_t lisa_data9overflow16 /* [0,255] */;
  uint32_t lisa_data9channel_cfd /* [0,16] */;
  uint32_t lisa_data9channel_cfdI[16 EXT_STRUCT_CTRL(lisa_data9channel_cfd)] /* [1,16] */;
  uint32_t lisa_data9channel_cfdv[16 EXT_STRUCT_CTRL(lisa_data9channel_cfd)] /* [0,255] */;
  uint32_t lisa_data9channel_energy /* [0,16] */;
  uint32_t lisa_data9channel_energyI[16 EXT_STRUCT_CTRL(lisa_data9channel_energy)] /* [1,16] */;
  uint32_t lisa_data9channel_energyv[16 EXT_STRUCT_CTRL(lisa_data9channel_energy)] /* [-1,-1] */;
  uint32_t lisa_data9channel_id_traces /* [0,16] */;
  uint32_t lisa_data9channel_id_tracesI[16 EXT_STRUCT_CTRL(lisa_data9channel_id_traces)] /* [1,16] */;
  uint32_t lisa_data9channel_id_tracesv[16 EXT_STRUCT_CTRL(lisa_data9channel_id_traces)] /* [0,255] */;
  uint32_t lisa_data9traces1 /* [0,4000] */;
  uint32_t lisa_data9traces1I[4000 EXT_STRUCT_CTRL(lisa_data9traces1)] /* [1,4000] */;
  uint32_t lisa_data9traces1v[4000 EXT_STRUCT_CTRL(lisa_data9traces1)] /* [0,65535] */;
  uint32_t lisa_data9traces2 /* [0,4000] */;
  uint32_t lisa_data9traces2I[4000 EXT_STRUCT_CTRL(lisa_data9traces2)] /* [1,4000] */;
  uint32_t lisa_data9traces2v[4000 EXT_STRUCT_CTRL(lisa_data9traces2)] /* [0,65535] */;
  uint32_t lisa_data9traces3 /* [0,4000] */;
  uint32_t lisa_data9traces3I[4000 EXT_STRUCT_CTRL(lisa_data9traces3)] /* [1,4000] */;
  uint32_t lisa_data9traces3v[4000 EXT_STRUCT_CTRL(lisa_data9traces3)] /* [0,65535] */;
  uint32_t lisa_data9traces4 /* [0,4000] */;
  uint32_t lisa_data9traces4I[4000 EXT_STRUCT_CTRL(lisa_data9traces4)] /* [1,4000] */;
  uint32_t lisa_data9traces4v[4000 EXT_STRUCT_CTRL(lisa_data9traces4)] /* [0,65535] */;
  uint32_t lisa_data9traces5 /* [0,4000] */;
  uint32_t lisa_data9traces5I[4000 EXT_STRUCT_CTRL(lisa_data9traces5)] /* [1,4000] */;
  uint32_t lisa_data9traces5v[4000 EXT_STRUCT_CTRL(lisa_data9traces5)] /* [0,65535] */;
  uint32_t lisa_data9traces6 /* [0,4000] */;
  uint32_t lisa_data9traces6I[4000 EXT_STRUCT_CTRL(lisa_data9traces6)] /* [1,4000] */;
  uint32_t lisa_data9traces6v[4000 EXT_STRUCT_CTRL(lisa_data9traces6)] /* [0,65535] */;
  uint32_t lisa_data9traces7 /* [0,4000] */;
  uint32_t lisa_data9traces7I[4000 EXT_STRUCT_CTRL(lisa_data9traces7)] /* [1,4000] */;
  uint32_t lisa_data9traces7v[4000 EXT_STRUCT_CTRL(lisa_data9traces7)] /* [0,65535] */;
  uint32_t lisa_data9traces8 /* [0,4000] */;
  uint32_t lisa_data9traces8I[4000 EXT_STRUCT_CTRL(lisa_data9traces8)] /* [1,4000] */;
  uint32_t lisa_data9traces8v[4000 EXT_STRUCT_CTRL(lisa_data9traces8)] /* [0,65535] */;
  uint32_t lisa_data9traces9 /* [0,4000] */;
  uint32_t lisa_data9traces9I[4000 EXT_STRUCT_CTRL(lisa_data9traces9)] /* [1,4000] */;
  uint32_t lisa_data9traces9v[4000 EXT_STRUCT_CTRL(lisa_data9traces9)] /* [0,65535] */;
  uint32_t lisa_data9traces10 /* [0,4000] */;
  uint32_t lisa_data9traces10I[4000 EXT_STRUCT_CTRL(lisa_data9traces10)] /* [1,4000] */;
  uint32_t lisa_data9traces10v[4000 EXT_STRUCT_CTRL(lisa_data9traces10)] /* [0,65535] */;
  uint32_t lisa_data9traces11 /* [0,4000] */;
  uint32_t lisa_data9traces11I[4000 EXT_STRUCT_CTRL(lisa_data9traces11)] /* [1,4000] */;
  uint32_t lisa_data9traces11v[4000 EXT_STRUCT_CTRL(lisa_data9traces11)] /* [0,65535] */;
  uint32_t lisa_data9traces12 /* [0,4000] */;
  uint32_t lisa_data9traces12I[4000 EXT_STRUCT_CTRL(lisa_data9traces12)] /* [1,4000] */;
  uint32_t lisa_data9traces12v[4000 EXT_STRUCT_CTRL(lisa_data9traces12)] /* [0,65535] */;
  uint32_t lisa_data9traces13 /* [0,4000] */;
  uint32_t lisa_data9traces13I[4000 EXT_STRUCT_CTRL(lisa_data9traces13)] /* [1,4000] */;
  uint32_t lisa_data9traces13v[4000 EXT_STRUCT_CTRL(lisa_data9traces13)] /* [0,65535] */;
  uint32_t lisa_data9traces14 /* [0,4000] */;
  uint32_t lisa_data9traces14I[4000 EXT_STRUCT_CTRL(lisa_data9traces14)] /* [1,4000] */;
  uint32_t lisa_data9traces14v[4000 EXT_STRUCT_CTRL(lisa_data9traces14)] /* [0,65535] */;
  uint32_t lisa_data9traces15 /* [0,4000] */;
  uint32_t lisa_data9traces15I[4000 EXT_STRUCT_CTRL(lisa_data9traces15)] /* [1,4000] */;
  uint32_t lisa_data9traces15v[4000 EXT_STRUCT_CTRL(lisa_data9traces15)] /* [0,65535] */;
  uint32_t lisa_data9traces16 /* [0,4000] */;
  uint32_t lisa_data9traces16I[4000 EXT_STRUCT_CTRL(lisa_data9traces16)] /* [1,4000] */;
  uint32_t lisa_data9traces16v[4000 EXT_STRUCT_CTRL(lisa_data9traces16)] /* [0,65535] */;
  uint32_t lisa_data10trig /* [0,255] */;
  uint32_t lisa_data10event_trigger_time_hi /* [-1,-1] */;
  uint32_t lisa_data10event_trigger_time_lo /* [-1,-1] */;
  uint32_t lisa_data10hit_pattern /* [0,65535] */;
  uint32_t lisa_data10num_channels_fired /* [-1,-1] */;
  uint32_t lisa_data10board_num /* [0,255] */;
  uint32_t lisa_data10channel_id /* [0,16] */;
  uint32_t lisa_data10channel_idI[16 EXT_STRUCT_CTRL(lisa_data10channel_id)] /* [1,16] */;
  uint32_t lisa_data10channel_idv[16 EXT_STRUCT_CTRL(lisa_data10channel_id)] /* [0,255] */;
  uint32_t lisa_data10channel_trigger_time_hi /* [0,16] */;
  uint32_t lisa_data10channel_trigger_time_hiI[16 EXT_STRUCT_CTRL(lisa_data10channel_trigger_time_hi)] /* [1,16] */;
  uint32_t lisa_data10channel_trigger_time_hiv[16 EXT_STRUCT_CTRL(lisa_data10channel_trigger_time_hi)] /* [0,65535] */;
  uint32_t lisa_data10channel_trigger_time_lo /* [0,16] */;
  uint32_t lisa_data10channel_trigger_time_loI[16 EXT_STRUCT_CTRL(lisa_data10channel_trigger_time_lo)] /* [1,16] */;
  uint32_t lisa_data10channel_trigger_time_lov[16 EXT_STRUCT_CTRL(lisa_data10channel_trigger_time_lo)] /* [-1,-1] */;
  uint32_t lisa_data10pileup1 /* [0,255] */;
  uint32_t lisa_data10pileup2 /* [0,255] */;
  uint32_t lisa_data10pileup3 /* [0,255] */;
  uint32_t lisa_data10pileup4 /* [0,255] */;
  uint32_t lisa_data10pileup5 /* [0,255] */;
  uint32_t lisa_data10pileup6 /* [0,255] */;
  uint32_t lisa_data10pileup7 /* [0,255] */;
  uint32_t lisa_data10pileup8 /* [0,255] */;
  uint32_t lisa_data10pileup9 /* [0,255] */;
  uint32_t lisa_data10pileup10 /* [0,255] */;
  uint32_t lisa_data10pileup11 /* [0,255] */;
  uint32_t lisa_data10pileup12 /* [0,255] */;
  uint32_t lisa_data10pileup13 /* [0,255] */;
  uint32_t lisa_data10pileup14 /* [0,255] */;
  uint32_t lisa_data10pileup15 /* [0,255] */;
  uint32_t lisa_data10pileup16 /* [0,255] */;
  uint32_t lisa_data10overflow1 /* [0,255] */;
  uint32_t lisa_data10overflow2 /* [0,255] */;
  uint32_t lisa_data10overflow3 /* [0,255] */;
  uint32_t lisa_data10overflow4 /* [0,255] */;
  uint32_t lisa_data10overflow5 /* [0,255] */;
  uint32_t lisa_data10overflow6 /* [0,255] */;
  uint32_t lisa_data10overflow7 /* [0,255] */;
  uint32_t lisa_data10overflow8 /* [0,255] */;
  uint32_t lisa_data10overflow9 /* [0,255] */;
  uint32_t lisa_data10overflow10 /* [0,255] */;
  uint32_t lisa_data10overflow11 /* [0,255] */;
  uint32_t lisa_data10overflow12 /* [0,255] */;
  uint32_t lisa_data10overflow13 /* [0,255] */;
  uint32_t lisa_data10overflow14 /* [0,255] */;
  uint32_t lisa_data10overflow15 /* [0,255] */;
  uint32_t lisa_data10overflow16 /* [0,255] */;
  uint32_t lisa_data10channel_cfd /* [0,16] */;
  uint32_t lisa_data10channel_cfdI[16 EXT_STRUCT_CTRL(lisa_data10channel_cfd)] /* [1,16] */;
  uint32_t lisa_data10channel_cfdv[16 EXT_STRUCT_CTRL(lisa_data10channel_cfd)] /* [0,255] */;
  uint32_t lisa_data10channel_energy /* [0,16] */;
  uint32_t lisa_data10channel_energyI[16 EXT_STRUCT_CTRL(lisa_data10channel_energy)] /* [1,16] */;
  uint32_t lisa_data10channel_energyv[16 EXT_STRUCT_CTRL(lisa_data10channel_energy)] /* [-1,-1] */;
  uint32_t lisa_data10channel_id_traces /* [0,16] */;
  uint32_t lisa_data10channel_id_tracesI[16 EXT_STRUCT_CTRL(lisa_data10channel_id_traces)] /* [1,16] */;
  uint32_t lisa_data10channel_id_tracesv[16 EXT_STRUCT_CTRL(lisa_data10channel_id_traces)] /* [0,255] */;
  uint32_t lisa_data10traces1 /* [0,4000] */;
  uint32_t lisa_data10traces1I[4000 EXT_STRUCT_CTRL(lisa_data10traces1)] /* [1,4000] */;
  uint32_t lisa_data10traces1v[4000 EXT_STRUCT_CTRL(lisa_data10traces1)] /* [0,65535] */;
  uint32_t lisa_data10traces2 /* [0,4000] */;
  uint32_t lisa_data10traces2I[4000 EXT_STRUCT_CTRL(lisa_data10traces2)] /* [1,4000] */;
  uint32_t lisa_data10traces2v[4000 EXT_STRUCT_CTRL(lisa_data10traces2)] /* [0,65535] */;
  uint32_t lisa_data10traces3 /* [0,4000] */;
  uint32_t lisa_data10traces3I[4000 EXT_STRUCT_CTRL(lisa_data10traces3)] /* [1,4000] */;
  uint32_t lisa_data10traces3v[4000 EXT_STRUCT_CTRL(lisa_data10traces3)] /* [0,65535] */;
  uint32_t lisa_data10traces4 /* [0,4000] */;
  uint32_t lisa_data10traces4I[4000 EXT_STRUCT_CTRL(lisa_data10traces4)] /* [1,4000] */;
  uint32_t lisa_data10traces4v[4000 EXT_STRUCT_CTRL(lisa_data10traces4)] /* [0,65535] */;
  uint32_t lisa_data10traces5 /* [0,4000] */;
  uint32_t lisa_data10traces5I[4000 EXT_STRUCT_CTRL(lisa_data10traces5)] /* [1,4000] */;
  uint32_t lisa_data10traces5v[4000 EXT_STRUCT_CTRL(lisa_data10traces5)] /* [0,65535] */;
  uint32_t lisa_data10traces6 /* [0,4000] */;
  uint32_t lisa_data10traces6I[4000 EXT_STRUCT_CTRL(lisa_data10traces6)] /* [1,4000] */;
  uint32_t lisa_data10traces6v[4000 EXT_STRUCT_CTRL(lisa_data10traces6)] /* [0,65535] */;
  uint32_t lisa_data10traces7 /* [0,4000] */;
  uint32_t lisa_data10traces7I[4000 EXT_STRUCT_CTRL(lisa_data10traces7)] /* [1,4000] */;
  uint32_t lisa_data10traces7v[4000 EXT_STRUCT_CTRL(lisa_data10traces7)] /* [0,65535] */;
  uint32_t lisa_data10traces8 /* [0,4000] */;
  uint32_t lisa_data10traces8I[4000 EXT_STRUCT_CTRL(lisa_data10traces8)] /* [1,4000] */;
  uint32_t lisa_data10traces8v[4000 EXT_STRUCT_CTRL(lisa_data10traces8)] /* [0,65535] */;
  uint32_t lisa_data10traces9 /* [0,4000] */;
  uint32_t lisa_data10traces9I[4000 EXT_STRUCT_CTRL(lisa_data10traces9)] /* [1,4000] */;
  uint32_t lisa_data10traces9v[4000 EXT_STRUCT_CTRL(lisa_data10traces9)] /* [0,65535] */;
  uint32_t lisa_data10traces10 /* [0,4000] */;
  uint32_t lisa_data10traces10I[4000 EXT_STRUCT_CTRL(lisa_data10traces10)] /* [1,4000] */;
  uint32_t lisa_data10traces10v[4000 EXT_STRUCT_CTRL(lisa_data10traces10)] /* [0,65535] */;
  uint32_t lisa_data10traces11 /* [0,4000] */;
  uint32_t lisa_data10traces11I[4000 EXT_STRUCT_CTRL(lisa_data10traces11)] /* [1,4000] */;
  uint32_t lisa_data10traces11v[4000 EXT_STRUCT_CTRL(lisa_data10traces11)] /* [0,65535] */;
  uint32_t lisa_data10traces12 /* [0,4000] */;
  uint32_t lisa_data10traces12I[4000 EXT_STRUCT_CTRL(lisa_data10traces12)] /* [1,4000] */;
  uint32_t lisa_data10traces12v[4000 EXT_STRUCT_CTRL(lisa_data10traces12)] /* [0,65535] */;
  uint32_t lisa_data10traces13 /* [0,4000] */;
  uint32_t lisa_data10traces13I[4000 EXT_STRUCT_CTRL(lisa_data10traces13)] /* [1,4000] */;
  uint32_t lisa_data10traces13v[4000 EXT_STRUCT_CTRL(lisa_data10traces13)] /* [0,65535] */;
  uint32_t lisa_data10traces14 /* [0,4000] */;
  uint32_t lisa_data10traces14I[4000 EXT_STRUCT_CTRL(lisa_data10traces14)] /* [1,4000] */;
  uint32_t lisa_data10traces14v[4000 EXT_STRUCT_CTRL(lisa_data10traces14)] /* [0,65535] */;
  uint32_t lisa_data10traces15 /* [0,4000] */;
  uint32_t lisa_data10traces15I[4000 EXT_STRUCT_CTRL(lisa_data10traces15)] /* [1,4000] */;
  uint32_t lisa_data10traces15v[4000 EXT_STRUCT_CTRL(lisa_data10traces15)] /* [0,65535] */;
  uint32_t lisa_data10traces16 /* [0,4000] */;
  uint32_t lisa_data10traces16I[4000 EXT_STRUCT_CTRL(lisa_data10traces16)] /* [1,4000] */;
  uint32_t lisa_data10traces16v[4000 EXT_STRUCT_CTRL(lisa_data10traces16)] /* [0,65535] */;

} EXT_STR_h101_lisa;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_lisa_onion_t
{
  /* UNPACK */
  uint32_t lisa_badevent_bad;
  uint32_t lisa_ts_subsystem_id;
  uint32_t lisa_ts_t[4];
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
    uint32_t pileup[16];
    uint32_t overflow[16];
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
  } lisa_data[10];

} EXT_STR_h101_lisa_onion;

/*******************************************************/

#define EXT_STR_h101_lisa_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_badevent_bad,               UINT32,\
                    "lisa_badevent_bad",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_ts_subsystem_id,            UINT32,\
                    "lisa_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_ts_t1,                      UINT32,\
                    "lisa_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_ts_t2,                      UINT32,\
                    "lisa_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_ts_t3,                      UINT32,\
                    "lisa_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_ts_t4,                      UINT32,\
                    "lisa_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1trig,                  UINT32,\
                    "lisa_data1trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data1event_trigger_time_hi, UINT32,\
                    "lisa_data1event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data1event_trigger_time_lo, UINT32,\
                    "lisa_data1event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1hit_pattern,           UINT32,\
                    "lisa_data1hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data1num_channels_fired,    UINT32,\
                    "lisa_data1num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1board_num,             UINT32,\
                    "lisa_data1board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_id,            UINT32,\
                    "lisa_data1channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_idI,           UINT32,\
                    "lisa_data1channel_idI",           "lisa_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_idv,           UINT32,\
                    "lisa_data1channel_idv",           "lisa_data1channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_trigger_time_hi,UINT32,\
                    "lisa_data1channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_trigger_time_hiI,UINT32,\
                    "lisa_data1channel_trigger_time_hiI","lisa_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_trigger_time_hiv,UINT32,\
                    "lisa_data1channel_trigger_time_hiv","lisa_data1channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_trigger_time_lo,UINT32,\
                    "lisa_data1channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_trigger_time_loI,UINT32,\
                    "lisa_data1channel_trigger_time_loI","lisa_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_trigger_time_lov,UINT32,\
                    "lisa_data1channel_trigger_time_lov","lisa_data1channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup1,               UINT32,\
                    "lisa_data1pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup2,               UINT32,\
                    "lisa_data1pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup3,               UINT32,\
                    "lisa_data1pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup4,               UINT32,\
                    "lisa_data1pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup5,               UINT32,\
                    "lisa_data1pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup6,               UINT32,\
                    "lisa_data1pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup7,               UINT32,\
                    "lisa_data1pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup8,               UINT32,\
                    "lisa_data1pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup9,               UINT32,\
                    "lisa_data1pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup10,              UINT32,\
                    "lisa_data1pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup11,              UINT32,\
                    "lisa_data1pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup12,              UINT32,\
                    "lisa_data1pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup13,              UINT32,\
                    "lisa_data1pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup14,              UINT32,\
                    "lisa_data1pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup15,              UINT32,\
                    "lisa_data1pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1pileup16,              UINT32,\
                    "lisa_data1pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow1,             UINT32,\
                    "lisa_data1overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow2,             UINT32,\
                    "lisa_data1overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow3,             UINT32,\
                    "lisa_data1overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow4,             UINT32,\
                    "lisa_data1overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow5,             UINT32,\
                    "lisa_data1overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow6,             UINT32,\
                    "lisa_data1overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow7,             UINT32,\
                    "lisa_data1overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow8,             UINT32,\
                    "lisa_data1overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow9,             UINT32,\
                    "lisa_data1overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow10,            UINT32,\
                    "lisa_data1overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow11,            UINT32,\
                    "lisa_data1overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow12,            UINT32,\
                    "lisa_data1overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow13,            UINT32,\
                    "lisa_data1overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow14,            UINT32,\
                    "lisa_data1overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow15,            UINT32,\
                    "lisa_data1overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1overflow16,            UINT32,\
                    "lisa_data1overflow16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_cfd,           UINT32,\
                    "lisa_data1channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_cfdI,          UINT32,\
                    "lisa_data1channel_cfdI",          "lisa_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_cfdv,          UINT32,\
                    "lisa_data1channel_cfdv",          "lisa_data1channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_energy,        UINT32,\
                    "lisa_data1channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_energyI,       UINT32,\
                    "lisa_data1channel_energyI",       "lisa_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_energyv,       UINT32,\
                    "lisa_data1channel_energyv",       "lisa_data1channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_id_traces,     UINT32,\
                    "lisa_data1channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_id_tracesI,    UINT32,\
                    "lisa_data1channel_id_tracesI",    "lisa_data1channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1channel_id_tracesv,    UINT32,\
                    "lisa_data1channel_id_tracesv",    "lisa_data1channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces1,               UINT32,\
                    "lisa_data1traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces1I,              UINT32,\
                    "lisa_data1traces1I",              "lisa_data1traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces1v,              UINT32,\
                    "lisa_data1traces1v",              "lisa_data1traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces2,               UINT32,\
                    "lisa_data1traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces2I,              UINT32,\
                    "lisa_data1traces2I",              "lisa_data1traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces2v,              UINT32,\
                    "lisa_data1traces2v",              "lisa_data1traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces3,               UINT32,\
                    "lisa_data1traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces3I,              UINT32,\
                    "lisa_data1traces3I",              "lisa_data1traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces3v,              UINT32,\
                    "lisa_data1traces3v",              "lisa_data1traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces4,               UINT32,\
                    "lisa_data1traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces4I,              UINT32,\
                    "lisa_data1traces4I",              "lisa_data1traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces4v,              UINT32,\
                    "lisa_data1traces4v",              "lisa_data1traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces5,               UINT32,\
                    "lisa_data1traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces5I,              UINT32,\
                    "lisa_data1traces5I",              "lisa_data1traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces5v,              UINT32,\
                    "lisa_data1traces5v",              "lisa_data1traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces6,               UINT32,\
                    "lisa_data1traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces6I,              UINT32,\
                    "lisa_data1traces6I",              "lisa_data1traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces6v,              UINT32,\
                    "lisa_data1traces6v",              "lisa_data1traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces7,               UINT32,\
                    "lisa_data1traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces7I,              UINT32,\
                    "lisa_data1traces7I",              "lisa_data1traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces7v,              UINT32,\
                    "lisa_data1traces7v",              "lisa_data1traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces8,               UINT32,\
                    "lisa_data1traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces8I,              UINT32,\
                    "lisa_data1traces8I",              "lisa_data1traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces8v,              UINT32,\
                    "lisa_data1traces8v",              "lisa_data1traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces9,               UINT32,\
                    "lisa_data1traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces9I,              UINT32,\
                    "lisa_data1traces9I",              "lisa_data1traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces9v,              UINT32,\
                    "lisa_data1traces9v",              "lisa_data1traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces10,              UINT32,\
                    "lisa_data1traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces10I,             UINT32,\
                    "lisa_data1traces10I",             "lisa_data1traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces10v,             UINT32,\
                    "lisa_data1traces10v",             "lisa_data1traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces11,              UINT32,\
                    "lisa_data1traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces11I,             UINT32,\
                    "lisa_data1traces11I",             "lisa_data1traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces11v,             UINT32,\
                    "lisa_data1traces11v",             "lisa_data1traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces12,              UINT32,\
                    "lisa_data1traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces12I,             UINT32,\
                    "lisa_data1traces12I",             "lisa_data1traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces12v,             UINT32,\
                    "lisa_data1traces12v",             "lisa_data1traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces13,              UINT32,\
                    "lisa_data1traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces13I,             UINT32,\
                    "lisa_data1traces13I",             "lisa_data1traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces13v,             UINT32,\
                    "lisa_data1traces13v",             "lisa_data1traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces14,              UINT32,\
                    "lisa_data1traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces14I,             UINT32,\
                    "lisa_data1traces14I",             "lisa_data1traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces14v,             UINT32,\
                    "lisa_data1traces14v",             "lisa_data1traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces15,              UINT32,\
                    "lisa_data1traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces15I,             UINT32,\
                    "lisa_data1traces15I",             "lisa_data1traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces15v,             UINT32,\
                    "lisa_data1traces15v",             "lisa_data1traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces16,              UINT32,\
                    "lisa_data1traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces16I,             UINT32,\
                    "lisa_data1traces16I",             "lisa_data1traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data1traces16v,             UINT32,\
                    "lisa_data1traces16v",             "lisa_data1traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2trig,                  UINT32,\
                    "lisa_data2trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data2event_trigger_time_hi, UINT32,\
                    "lisa_data2event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data2event_trigger_time_lo, UINT32,\
                    "lisa_data2event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2hit_pattern,           UINT32,\
                    "lisa_data2hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data2num_channels_fired,    UINT32,\
                    "lisa_data2num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2board_num,             UINT32,\
                    "lisa_data2board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_id,            UINT32,\
                    "lisa_data2channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_idI,           UINT32,\
                    "lisa_data2channel_idI",           "lisa_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_idv,           UINT32,\
                    "lisa_data2channel_idv",           "lisa_data2channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_trigger_time_hi,UINT32,\
                    "lisa_data2channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_trigger_time_hiI,UINT32,\
                    "lisa_data2channel_trigger_time_hiI","lisa_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_trigger_time_hiv,UINT32,\
                    "lisa_data2channel_trigger_time_hiv","lisa_data2channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_trigger_time_lo,UINT32,\
                    "lisa_data2channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_trigger_time_loI,UINT32,\
                    "lisa_data2channel_trigger_time_loI","lisa_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_trigger_time_lov,UINT32,\
                    "lisa_data2channel_trigger_time_lov","lisa_data2channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup1,               UINT32,\
                    "lisa_data2pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup2,               UINT32,\
                    "lisa_data2pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup3,               UINT32,\
                    "lisa_data2pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup4,               UINT32,\
                    "lisa_data2pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup5,               UINT32,\
                    "lisa_data2pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup6,               UINT32,\
                    "lisa_data2pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup7,               UINT32,\
                    "lisa_data2pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup8,               UINT32,\
                    "lisa_data2pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup9,               UINT32,\
                    "lisa_data2pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup10,              UINT32,\
                    "lisa_data2pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup11,              UINT32,\
                    "lisa_data2pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup12,              UINT32,\
                    "lisa_data2pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup13,              UINT32,\
                    "lisa_data2pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup14,              UINT32,\
                    "lisa_data2pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup15,              UINT32,\
                    "lisa_data2pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2pileup16,              UINT32,\
                    "lisa_data2pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow1,             UINT32,\
                    "lisa_data2overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow2,             UINT32,\
                    "lisa_data2overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow3,             UINT32,\
                    "lisa_data2overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow4,             UINT32,\
                    "lisa_data2overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow5,             UINT32,\
                    "lisa_data2overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow6,             UINT32,\
                    "lisa_data2overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow7,             UINT32,\
                    "lisa_data2overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow8,             UINT32,\
                    "lisa_data2overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow9,             UINT32,\
                    "lisa_data2overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow10,            UINT32,\
                    "lisa_data2overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow11,            UINT32,\
                    "lisa_data2overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow12,            UINT32,\
                    "lisa_data2overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow13,            UINT32,\
                    "lisa_data2overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow14,            UINT32,\
                    "lisa_data2overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow15,            UINT32,\
                    "lisa_data2overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2overflow16,            UINT32,\
                    "lisa_data2overflow16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_cfd,           UINT32,\
                    "lisa_data2channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_cfdI,          UINT32,\
                    "lisa_data2channel_cfdI",          "lisa_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_cfdv,          UINT32,\
                    "lisa_data2channel_cfdv",          "lisa_data2channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_energy,        UINT32,\
                    "lisa_data2channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_energyI,       UINT32,\
                    "lisa_data2channel_energyI",       "lisa_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_energyv,       UINT32,\
                    "lisa_data2channel_energyv",       "lisa_data2channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_id_traces,     UINT32,\
                    "lisa_data2channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_id_tracesI,    UINT32,\
                    "lisa_data2channel_id_tracesI",    "lisa_data2channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2channel_id_tracesv,    UINT32,\
                    "lisa_data2channel_id_tracesv",    "lisa_data2channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces1,               UINT32,\
                    "lisa_data2traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces1I,              UINT32,\
                    "lisa_data2traces1I",              "lisa_data2traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces1v,              UINT32,\
                    "lisa_data2traces1v",              "lisa_data2traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces2,               UINT32,\
                    "lisa_data2traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces2I,              UINT32,\
                    "lisa_data2traces2I",              "lisa_data2traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces2v,              UINT32,\
                    "lisa_data2traces2v",              "lisa_data2traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces3,               UINT32,\
                    "lisa_data2traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces3I,              UINT32,\
                    "lisa_data2traces3I",              "lisa_data2traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces3v,              UINT32,\
                    "lisa_data2traces3v",              "lisa_data2traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces4,               UINT32,\
                    "lisa_data2traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces4I,              UINT32,\
                    "lisa_data2traces4I",              "lisa_data2traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces4v,              UINT32,\
                    "lisa_data2traces4v",              "lisa_data2traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces5,               UINT32,\
                    "lisa_data2traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces5I,              UINT32,\
                    "lisa_data2traces5I",              "lisa_data2traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces5v,              UINT32,\
                    "lisa_data2traces5v",              "lisa_data2traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces6,               UINT32,\
                    "lisa_data2traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces6I,              UINT32,\
                    "lisa_data2traces6I",              "lisa_data2traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces6v,              UINT32,\
                    "lisa_data2traces6v",              "lisa_data2traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces7,               UINT32,\
                    "lisa_data2traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces7I,              UINT32,\
                    "lisa_data2traces7I",              "lisa_data2traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces7v,              UINT32,\
                    "lisa_data2traces7v",              "lisa_data2traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces8,               UINT32,\
                    "lisa_data2traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces8I,              UINT32,\
                    "lisa_data2traces8I",              "lisa_data2traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces8v,              UINT32,\
                    "lisa_data2traces8v",              "lisa_data2traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces9,               UINT32,\
                    "lisa_data2traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces9I,              UINT32,\
                    "lisa_data2traces9I",              "lisa_data2traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces9v,              UINT32,\
                    "lisa_data2traces9v",              "lisa_data2traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces10,              UINT32,\
                    "lisa_data2traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces10I,             UINT32,\
                    "lisa_data2traces10I",             "lisa_data2traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces10v,             UINT32,\
                    "lisa_data2traces10v",             "lisa_data2traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces11,              UINT32,\
                    "lisa_data2traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces11I,             UINT32,\
                    "lisa_data2traces11I",             "lisa_data2traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces11v,             UINT32,\
                    "lisa_data2traces11v",             "lisa_data2traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces12,              UINT32,\
                    "lisa_data2traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces12I,             UINT32,\
                    "lisa_data2traces12I",             "lisa_data2traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces12v,             UINT32,\
                    "lisa_data2traces12v",             "lisa_data2traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces13,              UINT32,\
                    "lisa_data2traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces13I,             UINT32,\
                    "lisa_data2traces13I",             "lisa_data2traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces13v,             UINT32,\
                    "lisa_data2traces13v",             "lisa_data2traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces14,              UINT32,\
                    "lisa_data2traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces14I,             UINT32,\
                    "lisa_data2traces14I",             "lisa_data2traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces14v,             UINT32,\
                    "lisa_data2traces14v",             "lisa_data2traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces15,              UINT32,\
                    "lisa_data2traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces15I,             UINT32,\
                    "lisa_data2traces15I",             "lisa_data2traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces15v,             UINT32,\
                    "lisa_data2traces15v",             "lisa_data2traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces16,              UINT32,\
                    "lisa_data2traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces16I,             UINT32,\
                    "lisa_data2traces16I",             "lisa_data2traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data2traces16v,             UINT32,\
                    "lisa_data2traces16v",             "lisa_data2traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3trig,                  UINT32,\
                    "lisa_data3trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data3event_trigger_time_hi, UINT32,\
                    "lisa_data3event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data3event_trigger_time_lo, UINT32,\
                    "lisa_data3event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3hit_pattern,           UINT32,\
                    "lisa_data3hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data3num_channels_fired,    UINT32,\
                    "lisa_data3num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3board_num,             UINT32,\
                    "lisa_data3board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_id,            UINT32,\
                    "lisa_data3channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_idI,           UINT32,\
                    "lisa_data3channel_idI",           "lisa_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_idv,           UINT32,\
                    "lisa_data3channel_idv",           "lisa_data3channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_trigger_time_hi,UINT32,\
                    "lisa_data3channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_trigger_time_hiI,UINT32,\
                    "lisa_data3channel_trigger_time_hiI","lisa_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_trigger_time_hiv,UINT32,\
                    "lisa_data3channel_trigger_time_hiv","lisa_data3channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_trigger_time_lo,UINT32,\
                    "lisa_data3channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_trigger_time_loI,UINT32,\
                    "lisa_data3channel_trigger_time_loI","lisa_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_trigger_time_lov,UINT32,\
                    "lisa_data3channel_trigger_time_lov","lisa_data3channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup1,               UINT32,\
                    "lisa_data3pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup2,               UINT32,\
                    "lisa_data3pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup3,               UINT32,\
                    "lisa_data3pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup4,               UINT32,\
                    "lisa_data3pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup5,               UINT32,\
                    "lisa_data3pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup6,               UINT32,\
                    "lisa_data3pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup7,               UINT32,\
                    "lisa_data3pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup8,               UINT32,\
                    "lisa_data3pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup9,               UINT32,\
                    "lisa_data3pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup10,              UINT32,\
                    "lisa_data3pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup11,              UINT32,\
                    "lisa_data3pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup12,              UINT32,\
                    "lisa_data3pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup13,              UINT32,\
                    "lisa_data3pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup14,              UINT32,\
                    "lisa_data3pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup15,              UINT32,\
                    "lisa_data3pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3pileup16,              UINT32,\
                    "lisa_data3pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow1,             UINT32,\
                    "lisa_data3overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow2,             UINT32,\
                    "lisa_data3overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow3,             UINT32,\
                    "lisa_data3overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow4,             UINT32,\
                    "lisa_data3overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow5,             UINT32,\
                    "lisa_data3overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow6,             UINT32,\
                    "lisa_data3overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow7,             UINT32,\
                    "lisa_data3overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow8,             UINT32,\
                    "lisa_data3overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow9,             UINT32,\
                    "lisa_data3overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow10,            UINT32,\
                    "lisa_data3overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow11,            UINT32,\
                    "lisa_data3overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow12,            UINT32,\
                    "lisa_data3overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow13,            UINT32,\
                    "lisa_data3overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow14,            UINT32,\
                    "lisa_data3overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow15,            UINT32,\
                    "lisa_data3overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3overflow16,            UINT32,\
                    "lisa_data3overflow16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_cfd,           UINT32,\
                    "lisa_data3channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_cfdI,          UINT32,\
                    "lisa_data3channel_cfdI",          "lisa_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_cfdv,          UINT32,\
                    "lisa_data3channel_cfdv",          "lisa_data3channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_energy,        UINT32,\
                    "lisa_data3channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_energyI,       UINT32,\
                    "lisa_data3channel_energyI",       "lisa_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_energyv,       UINT32,\
                    "lisa_data3channel_energyv",       "lisa_data3channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_id_traces,     UINT32,\
                    "lisa_data3channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_id_tracesI,    UINT32,\
                    "lisa_data3channel_id_tracesI",    "lisa_data3channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3channel_id_tracesv,    UINT32,\
                    "lisa_data3channel_id_tracesv",    "lisa_data3channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces1,               UINT32,\
                    "lisa_data3traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces1I,              UINT32,\
                    "lisa_data3traces1I",              "lisa_data3traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces1v,              UINT32,\
                    "lisa_data3traces1v",              "lisa_data3traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces2,               UINT32,\
                    "lisa_data3traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces2I,              UINT32,\
                    "lisa_data3traces2I",              "lisa_data3traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces2v,              UINT32,\
                    "lisa_data3traces2v",              "lisa_data3traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces3,               UINT32,\
                    "lisa_data3traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces3I,              UINT32,\
                    "lisa_data3traces3I",              "lisa_data3traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces3v,              UINT32,\
                    "lisa_data3traces3v",              "lisa_data3traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces4,               UINT32,\
                    "lisa_data3traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces4I,              UINT32,\
                    "lisa_data3traces4I",              "lisa_data3traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces4v,              UINT32,\
                    "lisa_data3traces4v",              "lisa_data3traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces5,               UINT32,\
                    "lisa_data3traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces5I,              UINT32,\
                    "lisa_data3traces5I",              "lisa_data3traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces5v,              UINT32,\
                    "lisa_data3traces5v",              "lisa_data3traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces6,               UINT32,\
                    "lisa_data3traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces6I,              UINT32,\
                    "lisa_data3traces6I",              "lisa_data3traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces6v,              UINT32,\
                    "lisa_data3traces6v",              "lisa_data3traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces7,               UINT32,\
                    "lisa_data3traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces7I,              UINT32,\
                    "lisa_data3traces7I",              "lisa_data3traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces7v,              UINT32,\
                    "lisa_data3traces7v",              "lisa_data3traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces8,               UINT32,\
                    "lisa_data3traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces8I,              UINT32,\
                    "lisa_data3traces8I",              "lisa_data3traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces8v,              UINT32,\
                    "lisa_data3traces8v",              "lisa_data3traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces9,               UINT32,\
                    "lisa_data3traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces9I,              UINT32,\
                    "lisa_data3traces9I",              "lisa_data3traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces9v,              UINT32,\
                    "lisa_data3traces9v",              "lisa_data3traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces10,              UINT32,\
                    "lisa_data3traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces10I,             UINT32,\
                    "lisa_data3traces10I",             "lisa_data3traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces10v,             UINT32,\
                    "lisa_data3traces10v",             "lisa_data3traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces11,              UINT32,\
                    "lisa_data3traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces11I,             UINT32,\
                    "lisa_data3traces11I",             "lisa_data3traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces11v,             UINT32,\
                    "lisa_data3traces11v",             "lisa_data3traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces12,              UINT32,\
                    "lisa_data3traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces12I,             UINT32,\
                    "lisa_data3traces12I",             "lisa_data3traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces12v,             UINT32,\
                    "lisa_data3traces12v",             "lisa_data3traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces13,              UINT32,\
                    "lisa_data3traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces13I,             UINT32,\
                    "lisa_data3traces13I",             "lisa_data3traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces13v,             UINT32,\
                    "lisa_data3traces13v",             "lisa_data3traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces14,              UINT32,\
                    "lisa_data3traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces14I,             UINT32,\
                    "lisa_data3traces14I",             "lisa_data3traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces14v,             UINT32,\
                    "lisa_data3traces14v",             "lisa_data3traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces15,              UINT32,\
                    "lisa_data3traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces15I,             UINT32,\
                    "lisa_data3traces15I",             "lisa_data3traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces15v,             UINT32,\
                    "lisa_data3traces15v",             "lisa_data3traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces16,              UINT32,\
                    "lisa_data3traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces16I,             UINT32,\
                    "lisa_data3traces16I",             "lisa_data3traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data3traces16v,             UINT32,\
                    "lisa_data3traces16v",             "lisa_data3traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4trig,                  UINT32,\
                    "lisa_data4trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data4event_trigger_time_hi, UINT32,\
                    "lisa_data4event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data4event_trigger_time_lo, UINT32,\
                    "lisa_data4event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4hit_pattern,           UINT32,\
                    "lisa_data4hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data4num_channels_fired,    UINT32,\
                    "lisa_data4num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4board_num,             UINT32,\
                    "lisa_data4board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_id,            UINT32,\
                    "lisa_data4channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_idI,           UINT32,\
                    "lisa_data4channel_idI",           "lisa_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_idv,           UINT32,\
                    "lisa_data4channel_idv",           "lisa_data4channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_trigger_time_hi,UINT32,\
                    "lisa_data4channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_trigger_time_hiI,UINT32,\
                    "lisa_data4channel_trigger_time_hiI","lisa_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_trigger_time_hiv,UINT32,\
                    "lisa_data4channel_trigger_time_hiv","lisa_data4channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_trigger_time_lo,UINT32,\
                    "lisa_data4channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_trigger_time_loI,UINT32,\
                    "lisa_data4channel_trigger_time_loI","lisa_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_trigger_time_lov,UINT32,\
                    "lisa_data4channel_trigger_time_lov","lisa_data4channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup1,               UINT32,\
                    "lisa_data4pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup2,               UINT32,\
                    "lisa_data4pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup3,               UINT32,\
                    "lisa_data4pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup4,               UINT32,\
                    "lisa_data4pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup5,               UINT32,\
                    "lisa_data4pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup6,               UINT32,\
                    "lisa_data4pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup7,               UINT32,\
                    "lisa_data4pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup8,               UINT32,\
                    "lisa_data4pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup9,               UINT32,\
                    "lisa_data4pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup10,              UINT32,\
                    "lisa_data4pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup11,              UINT32,\
                    "lisa_data4pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup12,              UINT32,\
                    "lisa_data4pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup13,              UINT32,\
                    "lisa_data4pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup14,              UINT32,\
                    "lisa_data4pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup15,              UINT32,\
                    "lisa_data4pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4pileup16,              UINT32,\
                    "lisa_data4pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow1,             UINT32,\
                    "lisa_data4overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow2,             UINT32,\
                    "lisa_data4overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow3,             UINT32,\
                    "lisa_data4overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow4,             UINT32,\
                    "lisa_data4overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow5,             UINT32,\
                    "lisa_data4overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow6,             UINT32,\
                    "lisa_data4overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow7,             UINT32,\
                    "lisa_data4overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow8,             UINT32,\
                    "lisa_data4overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow9,             UINT32,\
                    "lisa_data4overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow10,            UINT32,\
                    "lisa_data4overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow11,            UINT32,\
                    "lisa_data4overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow12,            UINT32,\
                    "lisa_data4overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow13,            UINT32,\
                    "lisa_data4overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow14,            UINT32,\
                    "lisa_data4overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow15,            UINT32,\
                    "lisa_data4overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4overflow16,            UINT32,\
                    "lisa_data4overflow16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_cfd,           UINT32,\
                    "lisa_data4channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_cfdI,          UINT32,\
                    "lisa_data4channel_cfdI",          "lisa_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_cfdv,          UINT32,\
                    "lisa_data4channel_cfdv",          "lisa_data4channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_energy,        UINT32,\
                    "lisa_data4channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_energyI,       UINT32,\
                    "lisa_data4channel_energyI",       "lisa_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_energyv,       UINT32,\
                    "lisa_data4channel_energyv",       "lisa_data4channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_id_traces,     UINT32,\
                    "lisa_data4channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_id_tracesI,    UINT32,\
                    "lisa_data4channel_id_tracesI",    "lisa_data4channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4channel_id_tracesv,    UINT32,\
                    "lisa_data4channel_id_tracesv",    "lisa_data4channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces1,               UINT32,\
                    "lisa_data4traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces1I,              UINT32,\
                    "lisa_data4traces1I",              "lisa_data4traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces1v,              UINT32,\
                    "lisa_data4traces1v",              "lisa_data4traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces2,               UINT32,\
                    "lisa_data4traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces2I,              UINT32,\
                    "lisa_data4traces2I",              "lisa_data4traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces2v,              UINT32,\
                    "lisa_data4traces2v",              "lisa_data4traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces3,               UINT32,\
                    "lisa_data4traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces3I,              UINT32,\
                    "lisa_data4traces3I",              "lisa_data4traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces3v,              UINT32,\
                    "lisa_data4traces3v",              "lisa_data4traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces4,               UINT32,\
                    "lisa_data4traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces4I,              UINT32,\
                    "lisa_data4traces4I",              "lisa_data4traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces4v,              UINT32,\
                    "lisa_data4traces4v",              "lisa_data4traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces5,               UINT32,\
                    "lisa_data4traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces5I,              UINT32,\
                    "lisa_data4traces5I",              "lisa_data4traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces5v,              UINT32,\
                    "lisa_data4traces5v",              "lisa_data4traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces6,               UINT32,\
                    "lisa_data4traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces6I,              UINT32,\
                    "lisa_data4traces6I",              "lisa_data4traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces6v,              UINT32,\
                    "lisa_data4traces6v",              "lisa_data4traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces7,               UINT32,\
                    "lisa_data4traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces7I,              UINT32,\
                    "lisa_data4traces7I",              "lisa_data4traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces7v,              UINT32,\
                    "lisa_data4traces7v",              "lisa_data4traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces8,               UINT32,\
                    "lisa_data4traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces8I,              UINT32,\
                    "lisa_data4traces8I",              "lisa_data4traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces8v,              UINT32,\
                    "lisa_data4traces8v",              "lisa_data4traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces9,               UINT32,\
                    "lisa_data4traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces9I,              UINT32,\
                    "lisa_data4traces9I",              "lisa_data4traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces9v,              UINT32,\
                    "lisa_data4traces9v",              "lisa_data4traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces10,              UINT32,\
                    "lisa_data4traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces10I,             UINT32,\
                    "lisa_data4traces10I",             "lisa_data4traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces10v,             UINT32,\
                    "lisa_data4traces10v",             "lisa_data4traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces11,              UINT32,\
                    "lisa_data4traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces11I,             UINT32,\
                    "lisa_data4traces11I",             "lisa_data4traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces11v,             UINT32,\
                    "lisa_data4traces11v",             "lisa_data4traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces12,              UINT32,\
                    "lisa_data4traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces12I,             UINT32,\
                    "lisa_data4traces12I",             "lisa_data4traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces12v,             UINT32,\
                    "lisa_data4traces12v",             "lisa_data4traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces13,              UINT32,\
                    "lisa_data4traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces13I,             UINT32,\
                    "lisa_data4traces13I",             "lisa_data4traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces13v,             UINT32,\
                    "lisa_data4traces13v",             "lisa_data4traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces14,              UINT32,\
                    "lisa_data4traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces14I,             UINT32,\
                    "lisa_data4traces14I",             "lisa_data4traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces14v,             UINT32,\
                    "lisa_data4traces14v",             "lisa_data4traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces15,              UINT32,\
                    "lisa_data4traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces15I,             UINT32,\
                    "lisa_data4traces15I",             "lisa_data4traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces15v,             UINT32,\
                    "lisa_data4traces15v",             "lisa_data4traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces16,              UINT32,\
                    "lisa_data4traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces16I,             UINT32,\
                    "lisa_data4traces16I",             "lisa_data4traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data4traces16v,             UINT32,\
                    "lisa_data4traces16v",             "lisa_data4traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5trig,                  UINT32,\
                    "lisa_data5trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data5event_trigger_time_hi, UINT32,\
                    "lisa_data5event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data5event_trigger_time_lo, UINT32,\
                    "lisa_data5event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5hit_pattern,           UINT32,\
                    "lisa_data5hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data5num_channels_fired,    UINT32,\
                    "lisa_data5num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5board_num,             UINT32,\
                    "lisa_data5board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_id,            UINT32,\
                    "lisa_data5channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_idI,           UINT32,\
                    "lisa_data5channel_idI",           "lisa_data5channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_idv,           UINT32,\
                    "lisa_data5channel_idv",           "lisa_data5channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_trigger_time_hi,UINT32,\
                    "lisa_data5channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_trigger_time_hiI,UINT32,\
                    "lisa_data5channel_trigger_time_hiI","lisa_data5channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_trigger_time_hiv,UINT32,\
                    "lisa_data5channel_trigger_time_hiv","lisa_data5channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_trigger_time_lo,UINT32,\
                    "lisa_data5channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_trigger_time_loI,UINT32,\
                    "lisa_data5channel_trigger_time_loI","lisa_data5channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_trigger_time_lov,UINT32,\
                    "lisa_data5channel_trigger_time_lov","lisa_data5channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup1,               UINT32,\
                    "lisa_data5pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup2,               UINT32,\
                    "lisa_data5pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup3,               UINT32,\
                    "lisa_data5pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup4,               UINT32,\
                    "lisa_data5pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup5,               UINT32,\
                    "lisa_data5pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup6,               UINT32,\
                    "lisa_data5pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup7,               UINT32,\
                    "lisa_data5pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup8,               UINT32,\
                    "lisa_data5pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup9,               UINT32,\
                    "lisa_data5pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup10,              UINT32,\
                    "lisa_data5pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup11,              UINT32,\
                    "lisa_data5pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup12,              UINT32,\
                    "lisa_data5pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup13,              UINT32,\
                    "lisa_data5pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup14,              UINT32,\
                    "lisa_data5pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup15,              UINT32,\
                    "lisa_data5pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5pileup16,              UINT32,\
                    "lisa_data5pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow1,             UINT32,\
                    "lisa_data5overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow2,             UINT32,\
                    "lisa_data5overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow3,             UINT32,\
                    "lisa_data5overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow4,             UINT32,\
                    "lisa_data5overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow5,             UINT32,\
                    "lisa_data5overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow6,             UINT32,\
                    "lisa_data5overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow7,             UINT32,\
                    "lisa_data5overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow8,             UINT32,\
                    "lisa_data5overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow9,             UINT32,\
                    "lisa_data5overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow10,            UINT32,\
                    "lisa_data5overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow11,            UINT32,\
                    "lisa_data5overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow12,            UINT32,\
                    "lisa_data5overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow13,            UINT32,\
                    "lisa_data5overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow14,            UINT32,\
                    "lisa_data5overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow15,            UINT32,\
                    "lisa_data5overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5overflow16,            UINT32,\
                    "lisa_data5overflow16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_cfd,           UINT32,\
                    "lisa_data5channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_cfdI,          UINT32,\
                    "lisa_data5channel_cfdI",          "lisa_data5channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_cfdv,          UINT32,\
                    "lisa_data5channel_cfdv",          "lisa_data5channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_energy,        UINT32,\
                    "lisa_data5channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_energyI,       UINT32,\
                    "lisa_data5channel_energyI",       "lisa_data5channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_energyv,       UINT32,\
                    "lisa_data5channel_energyv",       "lisa_data5channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_id_traces,     UINT32,\
                    "lisa_data5channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_id_tracesI,    UINT32,\
                    "lisa_data5channel_id_tracesI",    "lisa_data5channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5channel_id_tracesv,    UINT32,\
                    "lisa_data5channel_id_tracesv",    "lisa_data5channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces1,               UINT32,\
                    "lisa_data5traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces1I,              UINT32,\
                    "lisa_data5traces1I",              "lisa_data5traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces1v,              UINT32,\
                    "lisa_data5traces1v",              "lisa_data5traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces2,               UINT32,\
                    "lisa_data5traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces2I,              UINT32,\
                    "lisa_data5traces2I",              "lisa_data5traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces2v,              UINT32,\
                    "lisa_data5traces2v",              "lisa_data5traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces3,               UINT32,\
                    "lisa_data5traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces3I,              UINT32,\
                    "lisa_data5traces3I",              "lisa_data5traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces3v,              UINT32,\
                    "lisa_data5traces3v",              "lisa_data5traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces4,               UINT32,\
                    "lisa_data5traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces4I,              UINT32,\
                    "lisa_data5traces4I",              "lisa_data5traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces4v,              UINT32,\
                    "lisa_data5traces4v",              "lisa_data5traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces5,               UINT32,\
                    "lisa_data5traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces5I,              UINT32,\
                    "lisa_data5traces5I",              "lisa_data5traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces5v,              UINT32,\
                    "lisa_data5traces5v",              "lisa_data5traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces6,               UINT32,\
                    "lisa_data5traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces6I,              UINT32,\
                    "lisa_data5traces6I",              "lisa_data5traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces6v,              UINT32,\
                    "lisa_data5traces6v",              "lisa_data5traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces7,               UINT32,\
                    "lisa_data5traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces7I,              UINT32,\
                    "lisa_data5traces7I",              "lisa_data5traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces7v,              UINT32,\
                    "lisa_data5traces7v",              "lisa_data5traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces8,               UINT32,\
                    "lisa_data5traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces8I,              UINT32,\
                    "lisa_data5traces8I",              "lisa_data5traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces8v,              UINT32,\
                    "lisa_data5traces8v",              "lisa_data5traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces9,               UINT32,\
                    "lisa_data5traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces9I,              UINT32,\
                    "lisa_data5traces9I",              "lisa_data5traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces9v,              UINT32,\
                    "lisa_data5traces9v",              "lisa_data5traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces10,              UINT32,\
                    "lisa_data5traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces10I,             UINT32,\
                    "lisa_data5traces10I",             "lisa_data5traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces10v,             UINT32,\
                    "lisa_data5traces10v",             "lisa_data5traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces11,              UINT32,\
                    "lisa_data5traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces11I,             UINT32,\
                    "lisa_data5traces11I",             "lisa_data5traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces11v,             UINT32,\
                    "lisa_data5traces11v",             "lisa_data5traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces12,              UINT32,\
                    "lisa_data5traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces12I,             UINT32,\
                    "lisa_data5traces12I",             "lisa_data5traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces12v,             UINT32,\
                    "lisa_data5traces12v",             "lisa_data5traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces13,              UINT32,\
                    "lisa_data5traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces13I,             UINT32,\
                    "lisa_data5traces13I",             "lisa_data5traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces13v,             UINT32,\
                    "lisa_data5traces13v",             "lisa_data5traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces14,              UINT32,\
                    "lisa_data5traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces14I,             UINT32,\
                    "lisa_data5traces14I",             "lisa_data5traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces14v,             UINT32,\
                    "lisa_data5traces14v",             "lisa_data5traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces15,              UINT32,\
                    "lisa_data5traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces15I,             UINT32,\
                    "lisa_data5traces15I",             "lisa_data5traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces15v,             UINT32,\
                    "lisa_data5traces15v",             "lisa_data5traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces16,              UINT32,\
                    "lisa_data5traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces16I,             UINT32,\
                    "lisa_data5traces16I",             "lisa_data5traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data5traces16v,             UINT32,\
                    "lisa_data5traces16v",             "lisa_data5traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6trig,                  UINT32,\
                    "lisa_data6trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data6event_trigger_time_hi, UINT32,\
                    "lisa_data6event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data6event_trigger_time_lo, UINT32,\
                    "lisa_data6event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6hit_pattern,           UINT32,\
                    "lisa_data6hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data6num_channels_fired,    UINT32,\
                    "lisa_data6num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6board_num,             UINT32,\
                    "lisa_data6board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_id,            UINT32,\
                    "lisa_data6channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_idI,           UINT32,\
                    "lisa_data6channel_idI",           "lisa_data6channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_idv,           UINT32,\
                    "lisa_data6channel_idv",           "lisa_data6channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_trigger_time_hi,UINT32,\
                    "lisa_data6channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_trigger_time_hiI,UINT32,\
                    "lisa_data6channel_trigger_time_hiI","lisa_data6channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_trigger_time_hiv,UINT32,\
                    "lisa_data6channel_trigger_time_hiv","lisa_data6channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_trigger_time_lo,UINT32,\
                    "lisa_data6channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_trigger_time_loI,UINT32,\
                    "lisa_data6channel_trigger_time_loI","lisa_data6channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_trigger_time_lov,UINT32,\
                    "lisa_data6channel_trigger_time_lov","lisa_data6channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup1,               UINT32,\
                    "lisa_data6pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup2,               UINT32,\
                    "lisa_data6pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup3,               UINT32,\
                    "lisa_data6pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup4,               UINT32,\
                    "lisa_data6pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup5,               UINT32,\
                    "lisa_data6pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup6,               UINT32,\
                    "lisa_data6pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup7,               UINT32,\
                    "lisa_data6pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup8,               UINT32,\
                    "lisa_data6pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup9,               UINT32,\
                    "lisa_data6pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup10,              UINT32,\
                    "lisa_data6pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup11,              UINT32,\
                    "lisa_data6pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup12,              UINT32,\
                    "lisa_data6pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup13,              UINT32,\
                    "lisa_data6pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup14,              UINT32,\
                    "lisa_data6pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup15,              UINT32,\
                    "lisa_data6pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6pileup16,              UINT32,\
                    "lisa_data6pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow1,             UINT32,\
                    "lisa_data6overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow2,             UINT32,\
                    "lisa_data6overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow3,             UINT32,\
                    "lisa_data6overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow4,             UINT32,\
                    "lisa_data6overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow5,             UINT32,\
                    "lisa_data6overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow6,             UINT32,\
                    "lisa_data6overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow7,             UINT32,\
                    "lisa_data6overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow8,             UINT32,\
                    "lisa_data6overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow9,             UINT32,\
                    "lisa_data6overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow10,            UINT32,\
                    "lisa_data6overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow11,            UINT32,\
                    "lisa_data6overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow12,            UINT32,\
                    "lisa_data6overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow13,            UINT32,\
                    "lisa_data6overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow14,            UINT32,\
                    "lisa_data6overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow15,            UINT32,\
                    "lisa_data6overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6overflow16,            UINT32,\
                    "lisa_data6overflow16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_cfd,           UINT32,\
                    "lisa_data6channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_cfdI,          UINT32,\
                    "lisa_data6channel_cfdI",          "lisa_data6channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_cfdv,          UINT32,\
                    "lisa_data6channel_cfdv",          "lisa_data6channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_energy,        UINT32,\
                    "lisa_data6channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_energyI,       UINT32,\
                    "lisa_data6channel_energyI",       "lisa_data6channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_energyv,       UINT32,\
                    "lisa_data6channel_energyv",       "lisa_data6channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_id_traces,     UINT32,\
                    "lisa_data6channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_id_tracesI,    UINT32,\
                    "lisa_data6channel_id_tracesI",    "lisa_data6channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6channel_id_tracesv,    UINT32,\
                    "lisa_data6channel_id_tracesv",    "lisa_data6channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces1,               UINT32,\
                    "lisa_data6traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces1I,              UINT32,\
                    "lisa_data6traces1I",              "lisa_data6traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces1v,              UINT32,\
                    "lisa_data6traces1v",              "lisa_data6traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces2,               UINT32,\
                    "lisa_data6traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces2I,              UINT32,\
                    "lisa_data6traces2I",              "lisa_data6traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces2v,              UINT32,\
                    "lisa_data6traces2v",              "lisa_data6traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces3,               UINT32,\
                    "lisa_data6traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces3I,              UINT32,\
                    "lisa_data6traces3I",              "lisa_data6traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces3v,              UINT32,\
                    "lisa_data6traces3v",              "lisa_data6traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces4,               UINT32,\
                    "lisa_data6traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces4I,              UINT32,\
                    "lisa_data6traces4I",              "lisa_data6traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces4v,              UINT32,\
                    "lisa_data6traces4v",              "lisa_data6traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces5,               UINT32,\
                    "lisa_data6traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces5I,              UINT32,\
                    "lisa_data6traces5I",              "lisa_data6traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces5v,              UINT32,\
                    "lisa_data6traces5v",              "lisa_data6traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces6,               UINT32,\
                    "lisa_data6traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces6I,              UINT32,\
                    "lisa_data6traces6I",              "lisa_data6traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces6v,              UINT32,\
                    "lisa_data6traces6v",              "lisa_data6traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces7,               UINT32,\
                    "lisa_data6traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces7I,              UINT32,\
                    "lisa_data6traces7I",              "lisa_data6traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces7v,              UINT32,\
                    "lisa_data6traces7v",              "lisa_data6traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces8,               UINT32,\
                    "lisa_data6traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces8I,              UINT32,\
                    "lisa_data6traces8I",              "lisa_data6traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces8v,              UINT32,\
                    "lisa_data6traces8v",              "lisa_data6traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces9,               UINT32,\
                    "lisa_data6traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces9I,              UINT32,\
                    "lisa_data6traces9I",              "lisa_data6traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces9v,              UINT32,\
                    "lisa_data6traces9v",              "lisa_data6traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces10,              UINT32,\
                    "lisa_data6traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces10I,             UINT32,\
                    "lisa_data6traces10I",             "lisa_data6traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces10v,             UINT32,\
                    "lisa_data6traces10v",             "lisa_data6traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces11,              UINT32,\
                    "lisa_data6traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces11I,             UINT32,\
                    "lisa_data6traces11I",             "lisa_data6traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces11v,             UINT32,\
                    "lisa_data6traces11v",             "lisa_data6traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces12,              UINT32,\
                    "lisa_data6traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces12I,             UINT32,\
                    "lisa_data6traces12I",             "lisa_data6traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces12v,             UINT32,\
                    "lisa_data6traces12v",             "lisa_data6traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces13,              UINT32,\
                    "lisa_data6traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces13I,             UINT32,\
                    "lisa_data6traces13I",             "lisa_data6traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces13v,             UINT32,\
                    "lisa_data6traces13v",             "lisa_data6traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces14,              UINT32,\
                    "lisa_data6traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces14I,             UINT32,\
                    "lisa_data6traces14I",             "lisa_data6traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces14v,             UINT32,\
                    "lisa_data6traces14v",             "lisa_data6traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces15,              UINT32,\
                    "lisa_data6traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces15I,             UINT32,\
                    "lisa_data6traces15I",             "lisa_data6traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces15v,             UINT32,\
                    "lisa_data6traces15v",             "lisa_data6traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces16,              UINT32,\
                    "lisa_data6traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces16I,             UINT32,\
                    "lisa_data6traces16I",             "lisa_data6traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data6traces16v,             UINT32,\
                    "lisa_data6traces16v",             "lisa_data6traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7trig,                  UINT32,\
                    "lisa_data7trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data7event_trigger_time_hi, UINT32,\
                    "lisa_data7event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data7event_trigger_time_lo, UINT32,\
                    "lisa_data7event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7hit_pattern,           UINT32,\
                    "lisa_data7hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data7num_channels_fired,    UINT32,\
                    "lisa_data7num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7board_num,             UINT32,\
                    "lisa_data7board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_id,            UINT32,\
                    "lisa_data7channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_idI,           UINT32,\
                    "lisa_data7channel_idI",           "lisa_data7channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_idv,           UINT32,\
                    "lisa_data7channel_idv",           "lisa_data7channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_trigger_time_hi,UINT32,\
                    "lisa_data7channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_trigger_time_hiI,UINT32,\
                    "lisa_data7channel_trigger_time_hiI","lisa_data7channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_trigger_time_hiv,UINT32,\
                    "lisa_data7channel_trigger_time_hiv","lisa_data7channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_trigger_time_lo,UINT32,\
                    "lisa_data7channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_trigger_time_loI,UINT32,\
                    "lisa_data7channel_trigger_time_loI","lisa_data7channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_trigger_time_lov,UINT32,\
                    "lisa_data7channel_trigger_time_lov","lisa_data7channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup1,               UINT32,\
                    "lisa_data7pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup2,               UINT32,\
                    "lisa_data7pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup3,               UINT32,\
                    "lisa_data7pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup4,               UINT32,\
                    "lisa_data7pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup5,               UINT32,\
                    "lisa_data7pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup6,               UINT32,\
                    "lisa_data7pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup7,               UINT32,\
                    "lisa_data7pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup8,               UINT32,\
                    "lisa_data7pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup9,               UINT32,\
                    "lisa_data7pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup10,              UINT32,\
                    "lisa_data7pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup11,              UINT32,\
                    "lisa_data7pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup12,              UINT32,\
                    "lisa_data7pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup13,              UINT32,\
                    "lisa_data7pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup14,              UINT32,\
                    "lisa_data7pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup15,              UINT32,\
                    "lisa_data7pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7pileup16,              UINT32,\
                    "lisa_data7pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow1,             UINT32,\
                    "lisa_data7overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow2,             UINT32,\
                    "lisa_data7overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow3,             UINT32,\
                    "lisa_data7overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow4,             UINT32,\
                    "lisa_data7overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow5,             UINT32,\
                    "lisa_data7overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow6,             UINT32,\
                    "lisa_data7overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow7,             UINT32,\
                    "lisa_data7overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow8,             UINT32,\
                    "lisa_data7overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow9,             UINT32,\
                    "lisa_data7overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow10,            UINT32,\
                    "lisa_data7overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow11,            UINT32,\
                    "lisa_data7overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow12,            UINT32,\
                    "lisa_data7overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow13,            UINT32,\
                    "lisa_data7overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow14,            UINT32,\
                    "lisa_data7overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow15,            UINT32,\
                    "lisa_data7overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7overflow16,            UINT32,\
                    "lisa_data7overflow16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_cfd,           UINT32,\
                    "lisa_data7channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_cfdI,          UINT32,\
                    "lisa_data7channel_cfdI",          "lisa_data7channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_cfdv,          UINT32,\
                    "lisa_data7channel_cfdv",          "lisa_data7channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_energy,        UINT32,\
                    "lisa_data7channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_energyI,       UINT32,\
                    "lisa_data7channel_energyI",       "lisa_data7channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_energyv,       UINT32,\
                    "lisa_data7channel_energyv",       "lisa_data7channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_id_traces,     UINT32,\
                    "lisa_data7channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_id_tracesI,    UINT32,\
                    "lisa_data7channel_id_tracesI",    "lisa_data7channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7channel_id_tracesv,    UINT32,\
                    "lisa_data7channel_id_tracesv",    "lisa_data7channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces1,               UINT32,\
                    "lisa_data7traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces1I,              UINT32,\
                    "lisa_data7traces1I",              "lisa_data7traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces1v,              UINT32,\
                    "lisa_data7traces1v",              "lisa_data7traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces2,               UINT32,\
                    "lisa_data7traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces2I,              UINT32,\
                    "lisa_data7traces2I",              "lisa_data7traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces2v,              UINT32,\
                    "lisa_data7traces2v",              "lisa_data7traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces3,               UINT32,\
                    "lisa_data7traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces3I,              UINT32,\
                    "lisa_data7traces3I",              "lisa_data7traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces3v,              UINT32,\
                    "lisa_data7traces3v",              "lisa_data7traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces4,               UINT32,\
                    "lisa_data7traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces4I,              UINT32,\
                    "lisa_data7traces4I",              "lisa_data7traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces4v,              UINT32,\
                    "lisa_data7traces4v",              "lisa_data7traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces5,               UINT32,\
                    "lisa_data7traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces5I,              UINT32,\
                    "lisa_data7traces5I",              "lisa_data7traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces5v,              UINT32,\
                    "lisa_data7traces5v",              "lisa_data7traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces6,               UINT32,\
                    "lisa_data7traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces6I,              UINT32,\
                    "lisa_data7traces6I",              "lisa_data7traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces6v,              UINT32,\
                    "lisa_data7traces6v",              "lisa_data7traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces7,               UINT32,\
                    "lisa_data7traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces7I,              UINT32,\
                    "lisa_data7traces7I",              "lisa_data7traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces7v,              UINT32,\
                    "lisa_data7traces7v",              "lisa_data7traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces8,               UINT32,\
                    "lisa_data7traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces8I,              UINT32,\
                    "lisa_data7traces8I",              "lisa_data7traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces8v,              UINT32,\
                    "lisa_data7traces8v",              "lisa_data7traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces9,               UINT32,\
                    "lisa_data7traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces9I,              UINT32,\
                    "lisa_data7traces9I",              "lisa_data7traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces9v,              UINT32,\
                    "lisa_data7traces9v",              "lisa_data7traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces10,              UINT32,\
                    "lisa_data7traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces10I,             UINT32,\
                    "lisa_data7traces10I",             "lisa_data7traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces10v,             UINT32,\
                    "lisa_data7traces10v",             "lisa_data7traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces11,              UINT32,\
                    "lisa_data7traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces11I,             UINT32,\
                    "lisa_data7traces11I",             "lisa_data7traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces11v,             UINT32,\
                    "lisa_data7traces11v",             "lisa_data7traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces12,              UINT32,\
                    "lisa_data7traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces12I,             UINT32,\
                    "lisa_data7traces12I",             "lisa_data7traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces12v,             UINT32,\
                    "lisa_data7traces12v",             "lisa_data7traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces13,              UINT32,\
                    "lisa_data7traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces13I,             UINT32,\
                    "lisa_data7traces13I",             "lisa_data7traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces13v,             UINT32,\
                    "lisa_data7traces13v",             "lisa_data7traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces14,              UINT32,\
                    "lisa_data7traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces14I,             UINT32,\
                    "lisa_data7traces14I",             "lisa_data7traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces14v,             UINT32,\
                    "lisa_data7traces14v",             "lisa_data7traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces15,              UINT32,\
                    "lisa_data7traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces15I,             UINT32,\
                    "lisa_data7traces15I",             "lisa_data7traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces15v,             UINT32,\
                    "lisa_data7traces15v",             "lisa_data7traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces16,              UINT32,\
                    "lisa_data7traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces16I,             UINT32,\
                    "lisa_data7traces16I",             "lisa_data7traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data7traces16v,             UINT32,\
                    "lisa_data7traces16v",             "lisa_data7traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8trig,                  UINT32,\
                    "lisa_data8trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data8event_trigger_time_hi, UINT32,\
                    "lisa_data8event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data8event_trigger_time_lo, UINT32,\
                    "lisa_data8event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8hit_pattern,           UINT32,\
                    "lisa_data8hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data8num_channels_fired,    UINT32,\
                    "lisa_data8num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8board_num,             UINT32,\
                    "lisa_data8board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_id,            UINT32,\
                    "lisa_data8channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_idI,           UINT32,\
                    "lisa_data8channel_idI",           "lisa_data8channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_idv,           UINT32,\
                    "lisa_data8channel_idv",           "lisa_data8channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_trigger_time_hi,UINT32,\
                    "lisa_data8channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_trigger_time_hiI,UINT32,\
                    "lisa_data8channel_trigger_time_hiI","lisa_data8channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_trigger_time_hiv,UINT32,\
                    "lisa_data8channel_trigger_time_hiv","lisa_data8channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_trigger_time_lo,UINT32,\
                    "lisa_data8channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_trigger_time_loI,UINT32,\
                    "lisa_data8channel_trigger_time_loI","lisa_data8channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_trigger_time_lov,UINT32,\
                    "lisa_data8channel_trigger_time_lov","lisa_data8channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup1,               UINT32,\
                    "lisa_data8pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup2,               UINT32,\
                    "lisa_data8pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup3,               UINT32,\
                    "lisa_data8pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup4,               UINT32,\
                    "lisa_data8pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup5,               UINT32,\
                    "lisa_data8pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup6,               UINT32,\
                    "lisa_data8pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup7,               UINT32,\
                    "lisa_data8pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup8,               UINT32,\
                    "lisa_data8pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup9,               UINT32,\
                    "lisa_data8pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup10,              UINT32,\
                    "lisa_data8pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup11,              UINT32,\
                    "lisa_data8pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup12,              UINT32,\
                    "lisa_data8pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup13,              UINT32,\
                    "lisa_data8pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup14,              UINT32,\
                    "lisa_data8pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup15,              UINT32,\
                    "lisa_data8pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8pileup16,              UINT32,\
                    "lisa_data8pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow1,             UINT32,\
                    "lisa_data8overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow2,             UINT32,\
                    "lisa_data8overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow3,             UINT32,\
                    "lisa_data8overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow4,             UINT32,\
                    "lisa_data8overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow5,             UINT32,\
                    "lisa_data8overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow6,             UINT32,\
                    "lisa_data8overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow7,             UINT32,\
                    "lisa_data8overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow8,             UINT32,\
                    "lisa_data8overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow9,             UINT32,\
                    "lisa_data8overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow10,            UINT32,\
                    "lisa_data8overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow11,            UINT32,\
                    "lisa_data8overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow12,            UINT32,\
                    "lisa_data8overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow13,            UINT32,\
                    "lisa_data8overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow14,            UINT32,\
                    "lisa_data8overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow15,            UINT32,\
                    "lisa_data8overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8overflow16,            UINT32,\
                    "lisa_data8overflow16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_cfd,           UINT32,\
                    "lisa_data8channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_cfdI,          UINT32,\
                    "lisa_data8channel_cfdI",          "lisa_data8channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_cfdv,          UINT32,\
                    "lisa_data8channel_cfdv",          "lisa_data8channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_energy,        UINT32,\
                    "lisa_data8channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_energyI,       UINT32,\
                    "lisa_data8channel_energyI",       "lisa_data8channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_energyv,       UINT32,\
                    "lisa_data8channel_energyv",       "lisa_data8channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_id_traces,     UINT32,\
                    "lisa_data8channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_id_tracesI,    UINT32,\
                    "lisa_data8channel_id_tracesI",    "lisa_data8channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8channel_id_tracesv,    UINT32,\
                    "lisa_data8channel_id_tracesv",    "lisa_data8channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces1,               UINT32,\
                    "lisa_data8traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces1I,              UINT32,\
                    "lisa_data8traces1I",              "lisa_data8traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces1v,              UINT32,\
                    "lisa_data8traces1v",              "lisa_data8traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces2,               UINT32,\
                    "lisa_data8traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces2I,              UINT32,\
                    "lisa_data8traces2I",              "lisa_data8traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces2v,              UINT32,\
                    "lisa_data8traces2v",              "lisa_data8traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces3,               UINT32,\
                    "lisa_data8traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces3I,              UINT32,\
                    "lisa_data8traces3I",              "lisa_data8traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces3v,              UINT32,\
                    "lisa_data8traces3v",              "lisa_data8traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces4,               UINT32,\
                    "lisa_data8traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces4I,              UINT32,\
                    "lisa_data8traces4I",              "lisa_data8traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces4v,              UINT32,\
                    "lisa_data8traces4v",              "lisa_data8traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces5,               UINT32,\
                    "lisa_data8traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces5I,              UINT32,\
                    "lisa_data8traces5I",              "lisa_data8traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces5v,              UINT32,\
                    "lisa_data8traces5v",              "lisa_data8traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces6,               UINT32,\
                    "lisa_data8traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces6I,              UINT32,\
                    "lisa_data8traces6I",              "lisa_data8traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces6v,              UINT32,\
                    "lisa_data8traces6v",              "lisa_data8traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces7,               UINT32,\
                    "lisa_data8traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces7I,              UINT32,\
                    "lisa_data8traces7I",              "lisa_data8traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces7v,              UINT32,\
                    "lisa_data8traces7v",              "lisa_data8traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces8,               UINT32,\
                    "lisa_data8traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces8I,              UINT32,\
                    "lisa_data8traces8I",              "lisa_data8traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces8v,              UINT32,\
                    "lisa_data8traces8v",              "lisa_data8traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces9,               UINT32,\
                    "lisa_data8traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces9I,              UINT32,\
                    "lisa_data8traces9I",              "lisa_data8traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces9v,              UINT32,\
                    "lisa_data8traces9v",              "lisa_data8traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces10,              UINT32,\
                    "lisa_data8traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces10I,             UINT32,\
                    "lisa_data8traces10I",             "lisa_data8traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces10v,             UINT32,\
                    "lisa_data8traces10v",             "lisa_data8traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces11,              UINT32,\
                    "lisa_data8traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces11I,             UINT32,\
                    "lisa_data8traces11I",             "lisa_data8traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces11v,             UINT32,\
                    "lisa_data8traces11v",             "lisa_data8traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces12,              UINT32,\
                    "lisa_data8traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces12I,             UINT32,\
                    "lisa_data8traces12I",             "lisa_data8traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces12v,             UINT32,\
                    "lisa_data8traces12v",             "lisa_data8traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces13,              UINT32,\
                    "lisa_data8traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces13I,             UINT32,\
                    "lisa_data8traces13I",             "lisa_data8traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces13v,             UINT32,\
                    "lisa_data8traces13v",             "lisa_data8traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces14,              UINT32,\
                    "lisa_data8traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces14I,             UINT32,\
                    "lisa_data8traces14I",             "lisa_data8traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces14v,             UINT32,\
                    "lisa_data8traces14v",             "lisa_data8traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces15,              UINT32,\
                    "lisa_data8traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces15I,             UINT32,\
                    "lisa_data8traces15I",             "lisa_data8traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces15v,             UINT32,\
                    "lisa_data8traces15v",             "lisa_data8traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces16,              UINT32,\
                    "lisa_data8traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces16I,             UINT32,\
                    "lisa_data8traces16I",             "lisa_data8traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data8traces16v,             UINT32,\
                    "lisa_data8traces16v",             "lisa_data8traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9trig,                  UINT32,\
                    "lisa_data9trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data9event_trigger_time_hi, UINT32,\
                    "lisa_data9event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data9event_trigger_time_lo, UINT32,\
                    "lisa_data9event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9hit_pattern,           UINT32,\
                    "lisa_data9hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data9num_channels_fired,    UINT32,\
                    "lisa_data9num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9board_num,             UINT32,\
                    "lisa_data9board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_id,            UINT32,\
                    "lisa_data9channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_idI,           UINT32,\
                    "lisa_data9channel_idI",           "lisa_data9channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_idv,           UINT32,\
                    "lisa_data9channel_idv",           "lisa_data9channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_trigger_time_hi,UINT32,\
                    "lisa_data9channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_trigger_time_hiI,UINT32,\
                    "lisa_data9channel_trigger_time_hiI","lisa_data9channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_trigger_time_hiv,UINT32,\
                    "lisa_data9channel_trigger_time_hiv","lisa_data9channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_trigger_time_lo,UINT32,\
                    "lisa_data9channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_trigger_time_loI,UINT32,\
                    "lisa_data9channel_trigger_time_loI","lisa_data9channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_trigger_time_lov,UINT32,\
                    "lisa_data9channel_trigger_time_lov","lisa_data9channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup1,               UINT32,\
                    "lisa_data9pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup2,               UINT32,\
                    "lisa_data9pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup3,               UINT32,\
                    "lisa_data9pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup4,               UINT32,\
                    "lisa_data9pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup5,               UINT32,\
                    "lisa_data9pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup6,               UINT32,\
                    "lisa_data9pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup7,               UINT32,\
                    "lisa_data9pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup8,               UINT32,\
                    "lisa_data9pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup9,               UINT32,\
                    "lisa_data9pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup10,              UINT32,\
                    "lisa_data9pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup11,              UINT32,\
                    "lisa_data9pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup12,              UINT32,\
                    "lisa_data9pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup13,              UINT32,\
                    "lisa_data9pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup14,              UINT32,\
                    "lisa_data9pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup15,              UINT32,\
                    "lisa_data9pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9pileup16,              UINT32,\
                    "lisa_data9pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow1,             UINT32,\
                    "lisa_data9overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow2,             UINT32,\
                    "lisa_data9overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow3,             UINT32,\
                    "lisa_data9overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow4,             UINT32,\
                    "lisa_data9overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow5,             UINT32,\
                    "lisa_data9overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow6,             UINT32,\
                    "lisa_data9overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow7,             UINT32,\
                    "lisa_data9overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow8,             UINT32,\
                    "lisa_data9overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow9,             UINT32,\
                    "lisa_data9overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow10,            UINT32,\
                    "lisa_data9overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow11,            UINT32,\
                    "lisa_data9overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow12,            UINT32,\
                    "lisa_data9overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow13,            UINT32,\
                    "lisa_data9overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow14,            UINT32,\
                    "lisa_data9overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow15,            UINT32,\
                    "lisa_data9overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9overflow16,            UINT32,\
                    "lisa_data9overflow16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_cfd,           UINT32,\
                    "lisa_data9channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_cfdI,          UINT32,\
                    "lisa_data9channel_cfdI",          "lisa_data9channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_cfdv,          UINT32,\
                    "lisa_data9channel_cfdv",          "lisa_data9channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_energy,        UINT32,\
                    "lisa_data9channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_energyI,       UINT32,\
                    "lisa_data9channel_energyI",       "lisa_data9channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_energyv,       UINT32,\
                    "lisa_data9channel_energyv",       "lisa_data9channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_id_traces,     UINT32,\
                    "lisa_data9channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_id_tracesI,    UINT32,\
                    "lisa_data9channel_id_tracesI",    "lisa_data9channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9channel_id_tracesv,    UINT32,\
                    "lisa_data9channel_id_tracesv",    "lisa_data9channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces1,               UINT32,\
                    "lisa_data9traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces1I,              UINT32,\
                    "lisa_data9traces1I",              "lisa_data9traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces1v,              UINT32,\
                    "lisa_data9traces1v",              "lisa_data9traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces2,               UINT32,\
                    "lisa_data9traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces2I,              UINT32,\
                    "lisa_data9traces2I",              "lisa_data9traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces2v,              UINT32,\
                    "lisa_data9traces2v",              "lisa_data9traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces3,               UINT32,\
                    "lisa_data9traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces3I,              UINT32,\
                    "lisa_data9traces3I",              "lisa_data9traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces3v,              UINT32,\
                    "lisa_data9traces3v",              "lisa_data9traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces4,               UINT32,\
                    "lisa_data9traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces4I,              UINT32,\
                    "lisa_data9traces4I",              "lisa_data9traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces4v,              UINT32,\
                    "lisa_data9traces4v",              "lisa_data9traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces5,               UINT32,\
                    "lisa_data9traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces5I,              UINT32,\
                    "lisa_data9traces5I",              "lisa_data9traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces5v,              UINT32,\
                    "lisa_data9traces5v",              "lisa_data9traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces6,               UINT32,\
                    "lisa_data9traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces6I,              UINT32,\
                    "lisa_data9traces6I",              "lisa_data9traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces6v,              UINT32,\
                    "lisa_data9traces6v",              "lisa_data9traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces7,               UINT32,\
                    "lisa_data9traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces7I,              UINT32,\
                    "lisa_data9traces7I",              "lisa_data9traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces7v,              UINT32,\
                    "lisa_data9traces7v",              "lisa_data9traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces8,               UINT32,\
                    "lisa_data9traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces8I,              UINT32,\
                    "lisa_data9traces8I",              "lisa_data9traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces8v,              UINT32,\
                    "lisa_data9traces8v",              "lisa_data9traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces9,               UINT32,\
                    "lisa_data9traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces9I,              UINT32,\
                    "lisa_data9traces9I",              "lisa_data9traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces9v,              UINT32,\
                    "lisa_data9traces9v",              "lisa_data9traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces10,              UINT32,\
                    "lisa_data9traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces10I,             UINT32,\
                    "lisa_data9traces10I",             "lisa_data9traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces10v,             UINT32,\
                    "lisa_data9traces10v",             "lisa_data9traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces11,              UINT32,\
                    "lisa_data9traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces11I,             UINT32,\
                    "lisa_data9traces11I",             "lisa_data9traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces11v,             UINT32,\
                    "lisa_data9traces11v",             "lisa_data9traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces12,              UINT32,\
                    "lisa_data9traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces12I,             UINT32,\
                    "lisa_data9traces12I",             "lisa_data9traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces12v,             UINT32,\
                    "lisa_data9traces12v",             "lisa_data9traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces13,              UINT32,\
                    "lisa_data9traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces13I,             UINT32,\
                    "lisa_data9traces13I",             "lisa_data9traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces13v,             UINT32,\
                    "lisa_data9traces13v",             "lisa_data9traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces14,              UINT32,\
                    "lisa_data9traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces14I,             UINT32,\
                    "lisa_data9traces14I",             "lisa_data9traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces14v,             UINT32,\
                    "lisa_data9traces14v",             "lisa_data9traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces15,              UINT32,\
                    "lisa_data9traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces15I,             UINT32,\
                    "lisa_data9traces15I",             "lisa_data9traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces15v,             UINT32,\
                    "lisa_data9traces15v",             "lisa_data9traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces16,              UINT32,\
                    "lisa_data9traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces16I,             UINT32,\
                    "lisa_data9traces16I",             "lisa_data9traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data9traces16v,             UINT32,\
                    "lisa_data9traces16v",             "lisa_data9traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10trig,                 UINT32,\
                    "lisa_data10trig",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data10event_trigger_time_hi,UINT32,\
                    "lisa_data10event_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data10event_trigger_time_lo,UINT32,\
                    "lisa_data10event_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10hit_pattern,          UINT32,\
                    "lisa_data10hit_pattern",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     lisa_data10num_channels_fired,   UINT32,\
                    "lisa_data10num_channels_fired",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10board_num,            UINT32,\
                    "lisa_data10board_num",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_id,           UINT32,\
                    "lisa_data10channel_id",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_idI,          UINT32,\
                    "lisa_data10channel_idI",          "lisa_data10channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_idv,          UINT32,\
                    "lisa_data10channel_idv",          "lisa_data10channel_id",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_trigger_time_hi,UINT32,\
                    "lisa_data10channel_trigger_time_hi",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_trigger_time_hiI,UINT32,\
                    "lisa_data10channel_trigger_time_hiI","lisa_data10channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_trigger_time_hiv,UINT32,\
                    "lisa_data10channel_trigger_time_hiv","lisa_data10channel_trigger_time_hi",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_trigger_time_lo,UINT32,\
                    "lisa_data10channel_trigger_time_lo",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_trigger_time_loI,UINT32,\
                    "lisa_data10channel_trigger_time_loI","lisa_data10channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_trigger_time_lov,UINT32,\
                    "lisa_data10channel_trigger_time_lov","lisa_data10channel_trigger_time_lo",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup1,              UINT32,\
                    "lisa_data10pileup1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup2,              UINT32,\
                    "lisa_data10pileup2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup3,              UINT32,\
                    "lisa_data10pileup3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup4,              UINT32,\
                    "lisa_data10pileup4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup5,              UINT32,\
                    "lisa_data10pileup5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup6,              UINT32,\
                    "lisa_data10pileup6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup7,              UINT32,\
                    "lisa_data10pileup7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup8,              UINT32,\
                    "lisa_data10pileup8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup9,              UINT32,\
                    "lisa_data10pileup9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup10,             UINT32,\
                    "lisa_data10pileup10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup11,             UINT32,\
                    "lisa_data10pileup11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup12,             UINT32,\
                    "lisa_data10pileup12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup13,             UINT32,\
                    "lisa_data10pileup13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup14,             UINT32,\
                    "lisa_data10pileup14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup15,             UINT32,\
                    "lisa_data10pileup15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10pileup16,             UINT32,\
                    "lisa_data10pileup16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow1,            UINT32,\
                    "lisa_data10overflow1",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow2,            UINT32,\
                    "lisa_data10overflow2",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow3,            UINT32,\
                    "lisa_data10overflow3",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow4,            UINT32,\
                    "lisa_data10overflow4",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow5,            UINT32,\
                    "lisa_data10overflow5",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow6,            UINT32,\
                    "lisa_data10overflow6",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow7,            UINT32,\
                    "lisa_data10overflow7",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow8,            UINT32,\
                    "lisa_data10overflow8",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow9,            UINT32,\
                    "lisa_data10overflow9",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow10,           UINT32,\
                    "lisa_data10overflow10",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow11,           UINT32,\
                    "lisa_data10overflow11",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow12,           UINT32,\
                    "lisa_data10overflow12",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow13,           UINT32,\
                    "lisa_data10overflow13",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow14,           UINT32,\
                    "lisa_data10overflow14",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow15,           UINT32,\
                    "lisa_data10overflow15",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10overflow16,           UINT32,\
                    "lisa_data10overflow16",255,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_cfd,          UINT32,\
                    "lisa_data10channel_cfd",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_cfdI,         UINT32,\
                    "lisa_data10channel_cfdI",         "lisa_data10channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_cfdv,         UINT32,\
                    "lisa_data10channel_cfdv",         "lisa_data10channel_cfd",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_energy,       UINT32,\
                    "lisa_data10channel_energy",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_energyI,      UINT32,\
                    "lisa_data10channel_energyI",      "lisa_data10channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_energyv,      UINT32,\
                    "lisa_data10channel_energyv",      "lisa_data10channel_energy",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_id_traces,    UINT32,\
                    "lisa_data10channel_id_traces",16,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_id_tracesI,   UINT32,\
                    "lisa_data10channel_id_tracesI",   "lisa_data10channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10channel_id_tracesv,   UINT32,\
                    "lisa_data10channel_id_tracesv",   "lisa_data10channel_id_traces",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces1,              UINT32,\
                    "lisa_data10traces1",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces1I,             UINT32,\
                    "lisa_data10traces1I",             "lisa_data10traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces1v,             UINT32,\
                    "lisa_data10traces1v",             "lisa_data10traces1",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces2,              UINT32,\
                    "lisa_data10traces2",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces2I,             UINT32,\
                    "lisa_data10traces2I",             "lisa_data10traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces2v,             UINT32,\
                    "lisa_data10traces2v",             "lisa_data10traces2",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces3,              UINT32,\
                    "lisa_data10traces3",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces3I,             UINT32,\
                    "lisa_data10traces3I",             "lisa_data10traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces3v,             UINT32,\
                    "lisa_data10traces3v",             "lisa_data10traces3",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces4,              UINT32,\
                    "lisa_data10traces4",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces4I,             UINT32,\
                    "lisa_data10traces4I",             "lisa_data10traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces4v,             UINT32,\
                    "lisa_data10traces4v",             "lisa_data10traces4",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces5,              UINT32,\
                    "lisa_data10traces5",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces5I,             UINT32,\
                    "lisa_data10traces5I",             "lisa_data10traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces5v,             UINT32,\
                    "lisa_data10traces5v",             "lisa_data10traces5",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces6,              UINT32,\
                    "lisa_data10traces6",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces6I,             UINT32,\
                    "lisa_data10traces6I",             "lisa_data10traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces6v,             UINT32,\
                    "lisa_data10traces6v",             "lisa_data10traces6",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces7,              UINT32,\
                    "lisa_data10traces7",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces7I,             UINT32,\
                    "lisa_data10traces7I",             "lisa_data10traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces7v,             UINT32,\
                    "lisa_data10traces7v",             "lisa_data10traces7",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces8,              UINT32,\
                    "lisa_data10traces8",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces8I,             UINT32,\
                    "lisa_data10traces8I",             "lisa_data10traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces8v,             UINT32,\
                    "lisa_data10traces8v",             "lisa_data10traces8",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces9,              UINT32,\
                    "lisa_data10traces9",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces9I,             UINT32,\
                    "lisa_data10traces9I",             "lisa_data10traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces9v,             UINT32,\
                    "lisa_data10traces9v",             "lisa_data10traces9",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces10,             UINT32,\
                    "lisa_data10traces10",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces10I,            UINT32,\
                    "lisa_data10traces10I",            "lisa_data10traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces10v,            UINT32,\
                    "lisa_data10traces10v",            "lisa_data10traces10",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces11,             UINT32,\
                    "lisa_data10traces11",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces11I,            UINT32,\
                    "lisa_data10traces11I",            "lisa_data10traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces11v,            UINT32,\
                    "lisa_data10traces11v",            "lisa_data10traces11",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces12,             UINT32,\
                    "lisa_data10traces12",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces12I,            UINT32,\
                    "lisa_data10traces12I",            "lisa_data10traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces12v,            UINT32,\
                    "lisa_data10traces12v",            "lisa_data10traces12",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces13,             UINT32,\
                    "lisa_data10traces13",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces13I,            UINT32,\
                    "lisa_data10traces13I",            "lisa_data10traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces13v,            UINT32,\
                    "lisa_data10traces13v",            "lisa_data10traces13",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces14,             UINT32,\
                    "lisa_data10traces14",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces14I,            UINT32,\
                    "lisa_data10traces14I",            "lisa_data10traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces14v,            UINT32,\
                    "lisa_data10traces14v",            "lisa_data10traces14",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces15,             UINT32,\
                    "lisa_data10traces15",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces15I,            UINT32,\
                    "lisa_data10traces15I",            "lisa_data10traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces15v,            UINT32,\
                    "lisa_data10traces15v",            "lisa_data10traces15",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces16,             UINT32,\
                    "lisa_data10traces16",4000,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces16I,            UINT32,\
                    "lisa_data10traces16I",            "lisa_data10traces16",0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     lisa_data10traces16v,            UINT32,\
                    "lisa_data10traces16v",            "lisa_data10traces16",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_LISA_EXT_H101_LISA_H__*/

/*******************************************************/
