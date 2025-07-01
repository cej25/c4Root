/********************************************************
 *
 * Structure for ext_data_fetch_event() filling.
 *
 * Do not edit - automatically generated.
 */

#ifndef __GUARD_H101_TAMEX_EXT_H101_TAMEX_H__
#define __GUARD_H101_TAMEX_EXT_H101_TAMEX_H__

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

typedef struct EXT_STR_h101_tamex_t
{
  /* UNPACK */
  uint32_t tamex_ts_subsystem_id /* [0,65535] */;
  uint32_t tamex_ts_t1 /* [0,65535] */;
  uint32_t tamex_ts_t2 /* [0,65535] */;
  uint32_t tamex_ts_t3 /* [0,65535] */;
  uint32_t tamex_ts_t4 /* [0,65535] */;
  uint32_t tamex_pid /* [-1,-1] */;
  uint32_t tamex_trigger_window_post_trig_ns /* [0,65535] */;
  uint32_t tamex_trigger_window_pre_trig_ns /* [0,65535] */;
  uint32_t tamex_bplast1trig /* [0,65535] */;
  uint32_t tamex_bplast1event_size /* [-1,-1] */;
  uint32_t tamex_bplast1time_coarse /* [0,1024] */;
  uint32_t tamex_bplast1time_coarsev[1024 EXT_STRUCT_CTRL(tamex_bplast1time_coarse)] /* [0,65535] */;
  uint32_t tamex_bplast1time_fine /* [0,1024] */;
  uint32_t tamex_bplast1time_finev[1024 EXT_STRUCT_CTRL(tamex_bplast1time_fine)] /* [0,65535] */;
  uint32_t tamex_bplast1time_edge /* [0,1024] */;
  uint32_t tamex_bplast1time_edgev[1024 EXT_STRUCT_CTRL(tamex_bplast1time_edge)] /* [0,65535] */;
  uint32_t tamex_bplast1time_channel /* [0,1024] */;
  uint32_t tamex_bplast1time_channelv[1024 EXT_STRUCT_CTRL(tamex_bplast1time_channel)] /* [0,65535] */;
  uint32_t tamex_bplast1time_epoch /* [0,1024] */;
  uint32_t tamex_bplast1time_epochv[1024 EXT_STRUCT_CTRL(tamex_bplast1time_epoch)] /* [-1,-1] */;
  uint32_t tamex_bplast2trig /* [0,65535] */;
  uint32_t tamex_bplast2event_size /* [-1,-1] */;
  uint32_t tamex_bplast2time_coarse /* [0,1024] */;
  uint32_t tamex_bplast2time_coarsev[1024 EXT_STRUCT_CTRL(tamex_bplast2time_coarse)] /* [0,65535] */;
  uint32_t tamex_bplast2time_fine /* [0,1024] */;
  uint32_t tamex_bplast2time_finev[1024 EXT_STRUCT_CTRL(tamex_bplast2time_fine)] /* [0,65535] */;
  uint32_t tamex_bplast2time_edge /* [0,1024] */;
  uint32_t tamex_bplast2time_edgev[1024 EXT_STRUCT_CTRL(tamex_bplast2time_edge)] /* [0,65535] */;
  uint32_t tamex_bplast2time_channel /* [0,1024] */;
  uint32_t tamex_bplast2time_channelv[1024 EXT_STRUCT_CTRL(tamex_bplast2time_channel)] /* [0,65535] */;
  uint32_t tamex_bplast2time_epoch /* [0,1024] */;
  uint32_t tamex_bplast2time_epochv[1024 EXT_STRUCT_CTRL(tamex_bplast2time_epoch)] /* [-1,-1] */;
  uint32_t tamex_bplast3trig /* [0,65535] */;
  uint32_t tamex_bplast3event_size /* [-1,-1] */;
  uint32_t tamex_bplast3time_coarse /* [0,1024] */;
  uint32_t tamex_bplast3time_coarsev[1024 EXT_STRUCT_CTRL(tamex_bplast3time_coarse)] /* [0,65535] */;
  uint32_t tamex_bplast3time_fine /* [0,1024] */;
  uint32_t tamex_bplast3time_finev[1024 EXT_STRUCT_CTRL(tamex_bplast3time_fine)] /* [0,65535] */;
  uint32_t tamex_bplast3time_edge /* [0,1024] */;
  uint32_t tamex_bplast3time_edgev[1024 EXT_STRUCT_CTRL(tamex_bplast3time_edge)] /* [0,65535] */;
  uint32_t tamex_bplast3time_channel /* [0,1024] */;
  uint32_t tamex_bplast3time_channelv[1024 EXT_STRUCT_CTRL(tamex_bplast3time_channel)] /* [0,65535] */;
  uint32_t tamex_bplast3time_epoch /* [0,1024] */;
  uint32_t tamex_bplast3time_epochv[1024 EXT_STRUCT_CTRL(tamex_bplast3time_epoch)] /* [-1,-1] */;
  uint32_t tamex_bplast4trig /* [0,65535] */;
  uint32_t tamex_bplast4event_size /* [-1,-1] */;
  uint32_t tamex_bplast4time_coarse /* [0,1024] */;
  uint32_t tamex_bplast4time_coarsev[1024 EXT_STRUCT_CTRL(tamex_bplast4time_coarse)] /* [0,65535] */;
  uint32_t tamex_bplast4time_fine /* [0,1024] */;
  uint32_t tamex_bplast4time_finev[1024 EXT_STRUCT_CTRL(tamex_bplast4time_fine)] /* [0,65535] */;
  uint32_t tamex_bplast4time_edge /* [0,1024] */;
  uint32_t tamex_bplast4time_edgev[1024 EXT_STRUCT_CTRL(tamex_bplast4time_edge)] /* [0,65535] */;
  uint32_t tamex_bplast4time_channel /* [0,1024] */;
  uint32_t tamex_bplast4time_channelv[1024 EXT_STRUCT_CTRL(tamex_bplast4time_channel)] /* [0,65535] */;
  uint32_t tamex_bplast4time_epoch /* [0,1024] */;
  uint32_t tamex_bplast4time_epochv[1024 EXT_STRUCT_CTRL(tamex_bplast4time_epoch)] /* [-1,-1] */;
  uint32_t tamex_bplast5trig /* [0,65535] */;
  uint32_t tamex_bplast5event_size /* [-1,-1] */;
  uint32_t tamex_bplast5time_coarse /* [0,1024] */;
  uint32_t tamex_bplast5time_coarsev[1024 EXT_STRUCT_CTRL(tamex_bplast5time_coarse)] /* [0,65535] */;
  uint32_t tamex_bplast5time_fine /* [0,1024] */;
  uint32_t tamex_bplast5time_finev[1024 EXT_STRUCT_CTRL(tamex_bplast5time_fine)] /* [0,65535] */;
  uint32_t tamex_bplast5time_edge /* [0,1024] */;
  uint32_t tamex_bplast5time_edgev[1024 EXT_STRUCT_CTRL(tamex_bplast5time_edge)] /* [0,65535] */;
  uint32_t tamex_bplast5time_channel /* [0,1024] */;
  uint32_t tamex_bplast5time_channelv[1024 EXT_STRUCT_CTRL(tamex_bplast5time_channel)] /* [0,65535] */;
  uint32_t tamex_bplast5time_epoch /* [0,1024] */;
  uint32_t tamex_bplast5time_epochv[1024 EXT_STRUCT_CTRL(tamex_bplast5time_epoch)] /* [-1,-1] */;
  uint32_t tamex_bplast6trig /* [0,65535] */;
  uint32_t tamex_bplast6event_size /* [-1,-1] */;
  uint32_t tamex_bplast6time_coarse /* [0,1024] */;
  uint32_t tamex_bplast6time_coarsev[1024 EXT_STRUCT_CTRL(tamex_bplast6time_coarse)] /* [0,65535] */;
  uint32_t tamex_bplast6time_fine /* [0,1024] */;
  uint32_t tamex_bplast6time_finev[1024 EXT_STRUCT_CTRL(tamex_bplast6time_fine)] /* [0,65535] */;
  uint32_t tamex_bplast6time_edge /* [0,1024] */;
  uint32_t tamex_bplast6time_edgev[1024 EXT_STRUCT_CTRL(tamex_bplast6time_edge)] /* [0,65535] */;
  uint32_t tamex_bplast6time_channel /* [0,1024] */;
  uint32_t tamex_bplast6time_channelv[1024 EXT_STRUCT_CTRL(tamex_bplast6time_channel)] /* [0,65535] */;
  uint32_t tamex_bplast6time_epoch /* [0,1024] */;
  uint32_t tamex_bplast6time_epochv[1024 EXT_STRUCT_CTRL(tamex_bplast6time_epoch)] /* [-1,-1] */;
  uint32_t tamex_bplast7trig /* [0,65535] */;
  uint32_t tamex_bplast7event_size /* [-1,-1] */;
  uint32_t tamex_bplast7time_coarse /* [0,1024] */;
  uint32_t tamex_bplast7time_coarsev[1024 EXT_STRUCT_CTRL(tamex_bplast7time_coarse)] /* [0,65535] */;
  uint32_t tamex_bplast7time_fine /* [0,1024] */;
  uint32_t tamex_bplast7time_finev[1024 EXT_STRUCT_CTRL(tamex_bplast7time_fine)] /* [0,65535] */;
  uint32_t tamex_bplast7time_edge /* [0,1024] */;
  uint32_t tamex_bplast7time_edgev[1024 EXT_STRUCT_CTRL(tamex_bplast7time_edge)] /* [0,65535] */;
  uint32_t tamex_bplast7time_channel /* [0,1024] */;
  uint32_t tamex_bplast7time_channelv[1024 EXT_STRUCT_CTRL(tamex_bplast7time_channel)] /* [0,65535] */;
  uint32_t tamex_bplast7time_epoch /* [0,1024] */;
  uint32_t tamex_bplast7time_epochv[1024 EXT_STRUCT_CTRL(tamex_bplast7time_epoch)] /* [-1,-1] */;
  uint32_t tamex_bplast8trig /* [0,65535] */;
  uint32_t tamex_bplast8event_size /* [-1,-1] */;
  uint32_t tamex_bplast8time_coarse /* [0,1024] */;
  uint32_t tamex_bplast8time_coarsev[1024 EXT_STRUCT_CTRL(tamex_bplast8time_coarse)] /* [0,65535] */;
  uint32_t tamex_bplast8time_fine /* [0,1024] */;
  uint32_t tamex_bplast8time_finev[1024 EXT_STRUCT_CTRL(tamex_bplast8time_fine)] /* [0,65535] */;
  uint32_t tamex_bplast8time_edge /* [0,1024] */;
  uint32_t tamex_bplast8time_edgev[1024 EXT_STRUCT_CTRL(tamex_bplast8time_edge)] /* [0,65535] */;
  uint32_t tamex_bplast8time_channel /* [0,1024] */;
  uint32_t tamex_bplast8time_channelv[1024 EXT_STRUCT_CTRL(tamex_bplast8time_channel)] /* [0,65535] */;
  uint32_t tamex_bplast8time_epoch /* [0,1024] */;
  uint32_t tamex_bplast8time_epochv[1024 EXT_STRUCT_CTRL(tamex_bplast8time_epoch)] /* [-1,-1] */;
  uint32_t tamex_bplast9trig /* [0,65535] */;
  uint32_t tamex_bplast9event_size /* [-1,-1] */;
  uint32_t tamex_bplast9time_coarse /* [0,1024] */;
  uint32_t tamex_bplast9time_coarsev[1024 EXT_STRUCT_CTRL(tamex_bplast9time_coarse)] /* [0,65535] */;
  uint32_t tamex_bplast9time_fine /* [0,1024] */;
  uint32_t tamex_bplast9time_finev[1024 EXT_STRUCT_CTRL(tamex_bplast9time_fine)] /* [0,65535] */;
  uint32_t tamex_bplast9time_edge /* [0,1024] */;
  uint32_t tamex_bplast9time_edgev[1024 EXT_STRUCT_CTRL(tamex_bplast9time_edge)] /* [0,65535] */;
  uint32_t tamex_bplast9time_channel /* [0,1024] */;
  uint32_t tamex_bplast9time_channelv[1024 EXT_STRUCT_CTRL(tamex_bplast9time_channel)] /* [0,65535] */;
  uint32_t tamex_bplast9time_epoch /* [0,1024] */;
  uint32_t tamex_bplast9time_epochv[1024 EXT_STRUCT_CTRL(tamex_bplast9time_epoch)] /* [-1,-1] */;
  uint32_t tamex_fatima1trig /* [0,65535] */;
  uint32_t tamex_fatima1event_size /* [-1,-1] */;
  uint32_t tamex_fatima1time_coarse /* [0,1024] */;
  uint32_t tamex_fatima1time_coarsev[1024 EXT_STRUCT_CTRL(tamex_fatima1time_coarse)] /* [0,65535] */;
  uint32_t tamex_fatima1time_fine /* [0,1024] */;
  uint32_t tamex_fatima1time_finev[1024 EXT_STRUCT_CTRL(tamex_fatima1time_fine)] /* [0,65535] */;
  uint32_t tamex_fatima1time_edge /* [0,1024] */;
  uint32_t tamex_fatima1time_edgev[1024 EXT_STRUCT_CTRL(tamex_fatima1time_edge)] /* [0,65535] */;
  uint32_t tamex_fatima1time_channel /* [0,1024] */;
  uint32_t tamex_fatima1time_channelv[1024 EXT_STRUCT_CTRL(tamex_fatima1time_channel)] /* [0,65535] */;
  uint32_t tamex_fatima1time_epoch /* [0,1024] */;
  uint32_t tamex_fatima1time_epochv[1024 EXT_STRUCT_CTRL(tamex_fatima1time_epoch)] /* [-1,-1] */;
  uint32_t tamex_fatima2trig /* [0,65535] */;
  uint32_t tamex_fatima2event_size /* [-1,-1] */;
  uint32_t tamex_fatima2time_coarse /* [0,1024] */;
  uint32_t tamex_fatima2time_coarsev[1024 EXT_STRUCT_CTRL(tamex_fatima2time_coarse)] /* [0,65535] */;
  uint32_t tamex_fatima2time_fine /* [0,1024] */;
  uint32_t tamex_fatima2time_finev[1024 EXT_STRUCT_CTRL(tamex_fatima2time_fine)] /* [0,65535] */;
  uint32_t tamex_fatima2time_edge /* [0,1024] */;
  uint32_t tamex_fatima2time_edgev[1024 EXT_STRUCT_CTRL(tamex_fatima2time_edge)] /* [0,65535] */;
  uint32_t tamex_fatima2time_channel /* [0,1024] */;
  uint32_t tamex_fatima2time_channelv[1024 EXT_STRUCT_CTRL(tamex_fatima2time_channel)] /* [0,65535] */;
  uint32_t tamex_fatima2time_epoch /* [0,1024] */;
  uint32_t tamex_fatima2time_epochv[1024 EXT_STRUCT_CTRL(tamex_fatima2time_epoch)] /* [-1,-1] */;
  uint32_t tamex_fatima3trig /* [0,65535] */;
  uint32_t tamex_fatima3event_size /* [-1,-1] */;
  uint32_t tamex_fatima3time_coarse /* [0,1024] */;
  uint32_t tamex_fatima3time_coarsev[1024 EXT_STRUCT_CTRL(tamex_fatima3time_coarse)] /* [0,65535] */;
  uint32_t tamex_fatima3time_fine /* [0,1024] */;
  uint32_t tamex_fatima3time_finev[1024 EXT_STRUCT_CTRL(tamex_fatima3time_fine)] /* [0,65535] */;
  uint32_t tamex_fatima3time_edge /* [0,1024] */;
  uint32_t tamex_fatima3time_edgev[1024 EXT_STRUCT_CTRL(tamex_fatima3time_edge)] /* [0,65535] */;
  uint32_t tamex_fatima3time_channel /* [0,1024] */;
  uint32_t tamex_fatima3time_channelv[1024 EXT_STRUCT_CTRL(tamex_fatima3time_channel)] /* [0,65535] */;
  uint32_t tamex_fatima3time_epoch /* [0,1024] */;
  uint32_t tamex_fatima3time_epochv[1024 EXT_STRUCT_CTRL(tamex_fatima3time_epoch)] /* [-1,-1] */;
  uint32_t tamex_fatima4trig /* [0,65535] */;
  uint32_t tamex_fatima4event_size /* [-1,-1] */;
  uint32_t tamex_fatima4time_coarse /* [0,1024] */;
  uint32_t tamex_fatima4time_coarsev[1024 EXT_STRUCT_CTRL(tamex_fatima4time_coarse)] /* [0,65535] */;
  uint32_t tamex_fatima4time_fine /* [0,1024] */;
  uint32_t tamex_fatima4time_finev[1024 EXT_STRUCT_CTRL(tamex_fatima4time_fine)] /* [0,65535] */;
  uint32_t tamex_fatima4time_edge /* [0,1024] */;
  uint32_t tamex_fatima4time_edgev[1024 EXT_STRUCT_CTRL(tamex_fatima4time_edge)] /* [0,65535] */;
  uint32_t tamex_fatima4time_channel /* [0,1024] */;
  uint32_t tamex_fatima4time_channelv[1024 EXT_STRUCT_CTRL(tamex_fatima4time_channel)] /* [0,65535] */;
  uint32_t tamex_fatima4time_epoch /* [0,1024] */;
  uint32_t tamex_fatima4time_epochv[1024 EXT_STRUCT_CTRL(tamex_fatima4time_epoch)] /* [-1,-1] */;
  uint32_t tamex_fatima5trig /* [0,65535] */;
  uint32_t tamex_fatima5event_size /* [-1,-1] */;
  uint32_t tamex_fatima5time_coarse /* [0,1024] */;
  uint32_t tamex_fatima5time_coarsev[1024 EXT_STRUCT_CTRL(tamex_fatima5time_coarse)] /* [0,65535] */;
  uint32_t tamex_fatima5time_fine /* [0,1024] */;
  uint32_t tamex_fatima5time_finev[1024 EXT_STRUCT_CTRL(tamex_fatima5time_fine)] /* [0,65535] */;
  uint32_t tamex_fatima5time_edge /* [0,1024] */;
  uint32_t tamex_fatima5time_edgev[1024 EXT_STRUCT_CTRL(tamex_fatima5time_edge)] /* [0,65535] */;
  uint32_t tamex_fatima5time_channel /* [0,1024] */;
  uint32_t tamex_fatima5time_channelv[1024 EXT_STRUCT_CTRL(tamex_fatima5time_channel)] /* [0,65535] */;
  uint32_t tamex_fatima5time_epoch /* [0,1024] */;
  uint32_t tamex_fatima5time_epochv[1024 EXT_STRUCT_CTRL(tamex_fatima5time_epoch)] /* [-1,-1] */;
  uint32_t tamex_fatima6trig /* [0,65535] */;
  uint32_t tamex_fatima6event_size /* [-1,-1] */;
  uint32_t tamex_fatima6time_coarse /* [0,1024] */;
  uint32_t tamex_fatima6time_coarsev[1024 EXT_STRUCT_CTRL(tamex_fatima6time_coarse)] /* [0,65535] */;
  uint32_t tamex_fatima6time_fine /* [0,1024] */;
  uint32_t tamex_fatima6time_finev[1024 EXT_STRUCT_CTRL(tamex_fatima6time_fine)] /* [0,65535] */;
  uint32_t tamex_fatima6time_edge /* [0,1024] */;
  uint32_t tamex_fatima6time_edgev[1024 EXT_STRUCT_CTRL(tamex_fatima6time_edge)] /* [0,65535] */;
  uint32_t tamex_fatima6time_channel /* [0,1024] */;
  uint32_t tamex_fatima6time_channelv[1024 EXT_STRUCT_CTRL(tamex_fatima6time_channel)] /* [0,65535] */;
  uint32_t tamex_fatima6time_epoch /* [0,1024] */;
  uint32_t tamex_fatima6time_epochv[1024 EXT_STRUCT_CTRL(tamex_fatima6time_epoch)] /* [-1,-1] */;
  uint32_t tamex_fatima7trig /* [0,65535] */;
  uint32_t tamex_fatima7event_size /* [-1,-1] */;
  uint32_t tamex_fatima7time_coarse /* [0,1024] */;
  uint32_t tamex_fatima7time_coarsev[1024 EXT_STRUCT_CTRL(tamex_fatima7time_coarse)] /* [0,65535] */;
  uint32_t tamex_fatima7time_fine /* [0,1024] */;
  uint32_t tamex_fatima7time_finev[1024 EXT_STRUCT_CTRL(tamex_fatima7time_fine)] /* [0,65535] */;
  uint32_t tamex_fatima7time_edge /* [0,1024] */;
  uint32_t tamex_fatima7time_edgev[1024 EXT_STRUCT_CTRL(tamex_fatima7time_edge)] /* [0,65535] */;
  uint32_t tamex_fatima7time_channel /* [0,1024] */;
  uint32_t tamex_fatima7time_channelv[1024 EXT_STRUCT_CTRL(tamex_fatima7time_channel)] /* [0,65535] */;
  uint32_t tamex_fatima7time_epoch /* [0,1024] */;
  uint32_t tamex_fatima7time_epochv[1024 EXT_STRUCT_CTRL(tamex_fatima7time_epoch)] /* [-1,-1] */;
  uint32_t tamex_fatima8trig /* [0,65535] */;
  uint32_t tamex_fatima8event_size /* [-1,-1] */;
  uint32_t tamex_fatima8time_coarse /* [0,1024] */;
  uint32_t tamex_fatima8time_coarsev[1024 EXT_STRUCT_CTRL(tamex_fatima8time_coarse)] /* [0,65535] */;
  uint32_t tamex_fatima8time_fine /* [0,1024] */;
  uint32_t tamex_fatima8time_finev[1024 EXT_STRUCT_CTRL(tamex_fatima8time_fine)] /* [0,65535] */;
  uint32_t tamex_fatima8time_edge /* [0,1024] */;
  uint32_t tamex_fatima8time_edgev[1024 EXT_STRUCT_CTRL(tamex_fatima8time_edge)] /* [0,65535] */;
  uint32_t tamex_fatima8time_channel /* [0,1024] */;
  uint32_t tamex_fatima8time_channelv[1024 EXT_STRUCT_CTRL(tamex_fatima8time_channel)] /* [0,65535] */;
  uint32_t tamex_fatima8time_epoch /* [0,1024] */;
  uint32_t tamex_fatima8time_epochv[1024 EXT_STRUCT_CTRL(tamex_fatima8time_epoch)] /* [-1,-1] */;
  uint32_t tamex_fatima9trig /* [0,65535] */;
  uint32_t tamex_fatima9event_size /* [-1,-1] */;
  uint32_t tamex_fatima9time_coarse /* [0,1024] */;
  uint32_t tamex_fatima9time_coarsev[1024 EXT_STRUCT_CTRL(tamex_fatima9time_coarse)] /* [0,65535] */;
  uint32_t tamex_fatima9time_fine /* [0,1024] */;
  uint32_t tamex_fatima9time_finev[1024 EXT_STRUCT_CTRL(tamex_fatima9time_fine)] /* [0,65535] */;
  uint32_t tamex_fatima9time_edge /* [0,1024] */;
  uint32_t tamex_fatima9time_edgev[1024 EXT_STRUCT_CTRL(tamex_fatima9time_edge)] /* [0,65535] */;
  uint32_t tamex_fatima9time_channel /* [0,1024] */;
  uint32_t tamex_fatima9time_channelv[1024 EXT_STRUCT_CTRL(tamex_fatima9time_channel)] /* [0,65535] */;
  uint32_t tamex_fatima9time_epoch /* [0,1024] */;
  uint32_t tamex_fatima9time_epochv[1024 EXT_STRUCT_CTRL(tamex_fatima9time_epoch)] /* [-1,-1] */;
  uint32_t tamex_tamex1trig /* [0,65535] */;
  uint32_t tamex_tamex1event_size /* [-1,-1] */;
  uint32_t tamex_tamex1time_coarse /* [0,1024] */;
  uint32_t tamex_tamex1time_coarsev[1024 EXT_STRUCT_CTRL(tamex_tamex1time_coarse)] /* [0,65535] */;
  uint32_t tamex_tamex1time_fine /* [0,1024] */;
  uint32_t tamex_tamex1time_finev[1024 EXT_STRUCT_CTRL(tamex_tamex1time_fine)] /* [0,65535] */;
  uint32_t tamex_tamex1time_edge /* [0,1024] */;
  uint32_t tamex_tamex1time_edgev[1024 EXT_STRUCT_CTRL(tamex_tamex1time_edge)] /* [0,65535] */;
  uint32_t tamex_tamex1time_channel /* [0,1024] */;
  uint32_t tamex_tamex1time_channelv[1024 EXT_STRUCT_CTRL(tamex_tamex1time_channel)] /* [0,65535] */;
  uint32_t tamex_tamex1time_epoch /* [0,1024] */;
  uint32_t tamex_tamex1time_epochv[1024 EXT_STRUCT_CTRL(tamex_tamex1time_epoch)] /* [-1,-1] */;
  uint32_t tamex_tamex2trig /* [0,65535] */;
  uint32_t tamex_tamex2event_size /* [-1,-1] */;
  uint32_t tamex_tamex2time_coarse /* [0,1024] */;
  uint32_t tamex_tamex2time_coarsev[1024 EXT_STRUCT_CTRL(tamex_tamex2time_coarse)] /* [0,65535] */;
  uint32_t tamex_tamex2time_fine /* [0,1024] */;
  uint32_t tamex_tamex2time_finev[1024 EXT_STRUCT_CTRL(tamex_tamex2time_fine)] /* [0,65535] */;
  uint32_t tamex_tamex2time_edge /* [0,1024] */;
  uint32_t tamex_tamex2time_edgev[1024 EXT_STRUCT_CTRL(tamex_tamex2time_edge)] /* [0,65535] */;
  uint32_t tamex_tamex2time_channel /* [0,1024] */;
  uint32_t tamex_tamex2time_channelv[1024 EXT_STRUCT_CTRL(tamex_tamex2time_channel)] /* [0,65535] */;
  uint32_t tamex_tamex2time_epoch /* [0,1024] */;
  uint32_t tamex_tamex2time_epochv[1024 EXT_STRUCT_CTRL(tamex_tamex2time_epoch)] /* [-1,-1] */;
  uint32_t tamex_tamex3trig /* [0,65535] */;
  uint32_t tamex_tamex3event_size /* [-1,-1] */;
  uint32_t tamex_tamex3time_coarse /* [0,1024] */;
  uint32_t tamex_tamex3time_coarsev[1024 EXT_STRUCT_CTRL(tamex_tamex3time_coarse)] /* [0,65535] */;
  uint32_t tamex_tamex3time_fine /* [0,1024] */;
  uint32_t tamex_tamex3time_finev[1024 EXT_STRUCT_CTRL(tamex_tamex3time_fine)] /* [0,65535] */;
  uint32_t tamex_tamex3time_edge /* [0,1024] */;
  uint32_t tamex_tamex3time_edgev[1024 EXT_STRUCT_CTRL(tamex_tamex3time_edge)] /* [0,65535] */;
  uint32_t tamex_tamex3time_channel /* [0,1024] */;
  uint32_t tamex_tamex3time_channelv[1024 EXT_STRUCT_CTRL(tamex_tamex3time_channel)] /* [0,65535] */;
  uint32_t tamex_tamex3time_epoch /* [0,1024] */;
  uint32_t tamex_tamex3time_epochv[1024 EXT_STRUCT_CTRL(tamex_tamex3time_epoch)] /* [-1,-1] */;
  uint32_t tamex_tamex4trig /* [0,65535] */;
  uint32_t tamex_tamex4event_size /* [-1,-1] */;
  uint32_t tamex_tamex4time_coarse /* [0,1024] */;
  uint32_t tamex_tamex4time_coarsev[1024 EXT_STRUCT_CTRL(tamex_tamex4time_coarse)] /* [0,65535] */;
  uint32_t tamex_tamex4time_fine /* [0,1024] */;
  uint32_t tamex_tamex4time_finev[1024 EXT_STRUCT_CTRL(tamex_tamex4time_fine)] /* [0,65535] */;
  uint32_t tamex_tamex4time_edge /* [0,1024] */;
  uint32_t tamex_tamex4time_edgev[1024 EXT_STRUCT_CTRL(tamex_tamex4time_edge)] /* [0,65535] */;
  uint32_t tamex_tamex4time_channel /* [0,1024] */;
  uint32_t tamex_tamex4time_channelv[1024 EXT_STRUCT_CTRL(tamex_tamex4time_channel)] /* [0,65535] */;
  uint32_t tamex_tamex4time_epoch /* [0,1024] */;
  uint32_t tamex_tamex4time_epochv[1024 EXT_STRUCT_CTRL(tamex_tamex4time_epoch)] /* [-1,-1] */;
  uint32_t tamex_tamex5trig /* [0,65535] */;
  uint32_t tamex_tamex5event_size /* [-1,-1] */;
  uint32_t tamex_tamex5time_coarse /* [0,1024] */;
  uint32_t tamex_tamex5time_coarsev[1024 EXT_STRUCT_CTRL(tamex_tamex5time_coarse)] /* [0,65535] */;
  uint32_t tamex_tamex5time_fine /* [0,1024] */;
  uint32_t tamex_tamex5time_finev[1024 EXT_STRUCT_CTRL(tamex_tamex5time_fine)] /* [0,65535] */;
  uint32_t tamex_tamex5time_edge /* [0,1024] */;
  uint32_t tamex_tamex5time_edgev[1024 EXT_STRUCT_CTRL(tamex_tamex5time_edge)] /* [0,65535] */;
  uint32_t tamex_tamex5time_channel /* [0,1024] */;
  uint32_t tamex_tamex5time_channelv[1024 EXT_STRUCT_CTRL(tamex_tamex5time_channel)] /* [0,65535] */;
  uint32_t tamex_tamex5time_epoch /* [0,1024] */;
  uint32_t tamex_tamex5time_epochv[1024 EXT_STRUCT_CTRL(tamex_tamex5time_epoch)] /* [-1,-1] */;
  uint32_t tamex_tamex6trig /* [0,65535] */;
  uint32_t tamex_tamex6event_size /* [-1,-1] */;
  uint32_t tamex_tamex6time_coarse /* [0,1024] */;
  uint32_t tamex_tamex6time_coarsev[1024 EXT_STRUCT_CTRL(tamex_tamex6time_coarse)] /* [0,65535] */;
  uint32_t tamex_tamex6time_fine /* [0,1024] */;
  uint32_t tamex_tamex6time_finev[1024 EXT_STRUCT_CTRL(tamex_tamex6time_fine)] /* [0,65535] */;
  uint32_t tamex_tamex6time_edge /* [0,1024] */;
  uint32_t tamex_tamex6time_edgev[1024 EXT_STRUCT_CTRL(tamex_tamex6time_edge)] /* [0,65535] */;
  uint32_t tamex_tamex6time_channel /* [0,1024] */;
  uint32_t tamex_tamex6time_channelv[1024 EXT_STRUCT_CTRL(tamex_tamex6time_channel)] /* [0,65535] */;
  uint32_t tamex_tamex6time_epoch /* [0,1024] */;
  uint32_t tamex_tamex6time_epochv[1024 EXT_STRUCT_CTRL(tamex_tamex6time_epoch)] /* [-1,-1] */;
  uint32_t tamex_tamex7trig /* [0,65535] */;
  uint32_t tamex_tamex7event_size /* [-1,-1] */;
  uint32_t tamex_tamex7time_coarse /* [0,1024] */;
  uint32_t tamex_tamex7time_coarsev[1024 EXT_STRUCT_CTRL(tamex_tamex7time_coarse)] /* [0,65535] */;
  uint32_t tamex_tamex7time_fine /* [0,1024] */;
  uint32_t tamex_tamex7time_finev[1024 EXT_STRUCT_CTRL(tamex_tamex7time_fine)] /* [0,65535] */;
  uint32_t tamex_tamex7time_edge /* [0,1024] */;
  uint32_t tamex_tamex7time_edgev[1024 EXT_STRUCT_CTRL(tamex_tamex7time_edge)] /* [0,65535] */;
  uint32_t tamex_tamex7time_channel /* [0,1024] */;
  uint32_t tamex_tamex7time_channelv[1024 EXT_STRUCT_CTRL(tamex_tamex7time_channel)] /* [0,65535] */;
  uint32_t tamex_tamex7time_epoch /* [0,1024] */;
  uint32_t tamex_tamex7time_epochv[1024 EXT_STRUCT_CTRL(tamex_tamex7time_epoch)] /* [-1,-1] */;
  uint32_t tamex_tamex8trig /* [0,65535] */;
  uint32_t tamex_tamex8event_size /* [-1,-1] */;
  uint32_t tamex_tamex8time_coarse /* [0,1024] */;
  uint32_t tamex_tamex8time_coarsev[1024 EXT_STRUCT_CTRL(tamex_tamex8time_coarse)] /* [0,65535] */;
  uint32_t tamex_tamex8time_fine /* [0,1024] */;
  uint32_t tamex_tamex8time_finev[1024 EXT_STRUCT_CTRL(tamex_tamex8time_fine)] /* [0,65535] */;
  uint32_t tamex_tamex8time_edge /* [0,1024] */;
  uint32_t tamex_tamex8time_edgev[1024 EXT_STRUCT_CTRL(tamex_tamex8time_edge)] /* [0,65535] */;
  uint32_t tamex_tamex8time_channel /* [0,1024] */;
  uint32_t tamex_tamex8time_channelv[1024 EXT_STRUCT_CTRL(tamex_tamex8time_channel)] /* [0,65535] */;
  uint32_t tamex_tamex8time_epoch /* [0,1024] */;
  uint32_t tamex_tamex8time_epochv[1024 EXT_STRUCT_CTRL(tamex_tamex8time_epoch)] /* [-1,-1] */;
  uint32_t tamex_tamex9trig /* [0,65535] */;
  uint32_t tamex_tamex9event_size /* [-1,-1] */;
  uint32_t tamex_tamex9time_coarse /* [0,1024] */;
  uint32_t tamex_tamex9time_coarsev[1024 EXT_STRUCT_CTRL(tamex_tamex9time_coarse)] /* [0,65535] */;
  uint32_t tamex_tamex9time_fine /* [0,1024] */;
  uint32_t tamex_tamex9time_finev[1024 EXT_STRUCT_CTRL(tamex_tamex9time_fine)] /* [0,65535] */;
  uint32_t tamex_tamex9time_edge /* [0,1024] */;
  uint32_t tamex_tamex9time_edgev[1024 EXT_STRUCT_CTRL(tamex_tamex9time_edge)] /* [0,65535] */;
  uint32_t tamex_tamex9time_channel /* [0,1024] */;
  uint32_t tamex_tamex9time_channelv[1024 EXT_STRUCT_CTRL(tamex_tamex9time_channel)] /* [0,65535] */;
  uint32_t tamex_tamex9time_epoch /* [0,1024] */;
  uint32_t tamex_tamex9time_epochv[1024 EXT_STRUCT_CTRL(tamex_tamex9time_epoch)] /* [-1,-1] */;

} EXT_STR_h101_tamex;

/********************************************************
 *
 * Structure with multiple levels of arrays (partially)
 * recovered (recommended):
 */

typedef struct EXT_STR_h101_tamex_onion_t
{
  /* UNPACK */
  uint32_t tamex_ts_subsystem_id;
  uint32_t tamex_ts_t[4];
  uint32_t tamex_pid;
  uint32_t tamex_trigger_window_post_trig_ns;
  uint32_t tamex_trigger_window_pre_trig_ns;
  struct {
    uint32_t trig;
    uint32_t event_size;
    uint32_t time_coarse;
    uint32_t time_coarsev[1024 /* time_coarse */];
    uint32_t time_fine;
    uint32_t time_finev[1024 /* time_fine */];
    uint32_t time_edge;
    uint32_t time_edgev[1024 /* time_edge */];
    uint32_t time_channel;
    uint32_t time_channelv[1024 /* time_channel */];
    uint32_t time_epoch;
    uint32_t time_epochv[1024 /* time_epoch */];
  } tamex_bplast[9];
  struct {
    uint32_t trig;
    uint32_t event_size;
    uint32_t time_coarse;
    uint32_t time_coarsev[1024 /* time_coarse */];
    uint32_t time_fine;
    uint32_t time_finev[1024 /* time_fine */];
    uint32_t time_edge;
    uint32_t time_edgev[1024 /* time_edge */];
    uint32_t time_channel;
    uint32_t time_channelv[1024 /* time_channel */];
    uint32_t time_epoch;
    uint32_t time_epochv[1024 /* time_epoch */];
  } tamex_fatima[9];
  struct {
    uint32_t trig;
    uint32_t event_size;
    uint32_t time_coarse;
    uint32_t time_coarsev[1024 /* time_coarse */];
    uint32_t time_fine;
    uint32_t time_finev[1024 /* time_fine */];
    uint32_t time_edge;
    uint32_t time_edgev[1024 /* time_edge */];
    uint32_t time_channel;
    uint32_t time_channelv[1024 /* time_channel */];
    uint32_t time_epoch;
    uint32_t time_epochv[1024 /* time_epoch */];
  } tamex_tamex[9];

} EXT_STR_h101_tamex_onion;

/*******************************************************/

#define EXT_STR_h101_tamex_ITEMS_INFO(ok,si,offset,struct_t,printerr) do { \
  ok = 1; \
  /* UNPACK */ \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_ts_subsystem_id,           UINT32,\
                    "tamex_ts_subsystem_id",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_ts_t1,                     UINT32,\
                    "tamex_ts_t1",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_ts_t2,                     UINT32,\
                    "tamex_ts_t2",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_ts_t3,                     UINT32,\
                    "tamex_ts_t3",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_ts_t4,                     UINT32,\
                    "tamex_ts_t4",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_pid,                       UINT32,\
                    "tamex_pid",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_trigger_window_post_trig_ns,UINT32,\
                    "tamex_trigger_window_post_trig_ns",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_trigger_window_pre_trig_ns,UINT32,\
                    "tamex_trigger_window_pre_trig_ns",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1trig,               UINT32,\
                    "tamex_bplast1trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_bplast1event_size,         UINT32,\
                    "tamex_bplast1event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_coarse,        UINT32,\
                    "tamex_bplast1time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_coarsev,       UINT32,\
                    "tamex_bplast1time_coarsev",       "tamex_bplast1time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_fine,          UINT32,\
                    "tamex_bplast1time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_finev,         UINT32,\
                    "tamex_bplast1time_finev",         "tamex_bplast1time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_edge,          UINT32,\
                    "tamex_bplast1time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_edgev,         UINT32,\
                    "tamex_bplast1time_edgev",         "tamex_bplast1time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_channel,       UINT32,\
                    "tamex_bplast1time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_channelv,      UINT32,\
                    "tamex_bplast1time_channelv",      "tamex_bplast1time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_epoch,         UINT32,\
                    "tamex_bplast1time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast1time_epochv,        UINT32,\
                    "tamex_bplast1time_epochv",        "tamex_bplast1time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast2trig,               UINT32,\
                    "tamex_bplast2trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_bplast2event_size,         UINT32,\
                    "tamex_bplast2event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast2time_coarse,        UINT32,\
                    "tamex_bplast2time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast2time_coarsev,       UINT32,\
                    "tamex_bplast2time_coarsev",       "tamex_bplast2time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast2time_fine,          UINT32,\
                    "tamex_bplast2time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast2time_finev,         UINT32,\
                    "tamex_bplast2time_finev",         "tamex_bplast2time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast2time_edge,          UINT32,\
                    "tamex_bplast2time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast2time_edgev,         UINT32,\
                    "tamex_bplast2time_edgev",         "tamex_bplast2time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast2time_channel,       UINT32,\
                    "tamex_bplast2time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast2time_channelv,      UINT32,\
                    "tamex_bplast2time_channelv",      "tamex_bplast2time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast2time_epoch,         UINT32,\
                    "tamex_bplast2time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast2time_epochv,        UINT32,\
                    "tamex_bplast2time_epochv",        "tamex_bplast2time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast3trig,               UINT32,\
                    "tamex_bplast3trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_bplast3event_size,         UINT32,\
                    "tamex_bplast3event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast3time_coarse,        UINT32,\
                    "tamex_bplast3time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast3time_coarsev,       UINT32,\
                    "tamex_bplast3time_coarsev",       "tamex_bplast3time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast3time_fine,          UINT32,\
                    "tamex_bplast3time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast3time_finev,         UINT32,\
                    "tamex_bplast3time_finev",         "tamex_bplast3time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast3time_edge,          UINT32,\
                    "tamex_bplast3time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast3time_edgev,         UINT32,\
                    "tamex_bplast3time_edgev",         "tamex_bplast3time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast3time_channel,       UINT32,\
                    "tamex_bplast3time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast3time_channelv,      UINT32,\
                    "tamex_bplast3time_channelv",      "tamex_bplast3time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast3time_epoch,         UINT32,\
                    "tamex_bplast3time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast3time_epochv,        UINT32,\
                    "tamex_bplast3time_epochv",        "tamex_bplast3time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast4trig,               UINT32,\
                    "tamex_bplast4trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_bplast4event_size,         UINT32,\
                    "tamex_bplast4event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast4time_coarse,        UINT32,\
                    "tamex_bplast4time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast4time_coarsev,       UINT32,\
                    "tamex_bplast4time_coarsev",       "tamex_bplast4time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast4time_fine,          UINT32,\
                    "tamex_bplast4time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast4time_finev,         UINT32,\
                    "tamex_bplast4time_finev",         "tamex_bplast4time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast4time_edge,          UINT32,\
                    "tamex_bplast4time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast4time_edgev,         UINT32,\
                    "tamex_bplast4time_edgev",         "tamex_bplast4time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast4time_channel,       UINT32,\
                    "tamex_bplast4time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast4time_channelv,      UINT32,\
                    "tamex_bplast4time_channelv",      "tamex_bplast4time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast4time_epoch,         UINT32,\
                    "tamex_bplast4time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast4time_epochv,        UINT32,\
                    "tamex_bplast4time_epochv",        "tamex_bplast4time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast5trig,               UINT32,\
                    "tamex_bplast5trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_bplast5event_size,         UINT32,\
                    "tamex_bplast5event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast5time_coarse,        UINT32,\
                    "tamex_bplast5time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast5time_coarsev,       UINT32,\
                    "tamex_bplast5time_coarsev",       "tamex_bplast5time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast5time_fine,          UINT32,\
                    "tamex_bplast5time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast5time_finev,         UINT32,\
                    "tamex_bplast5time_finev",         "tamex_bplast5time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast5time_edge,          UINT32,\
                    "tamex_bplast5time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast5time_edgev,         UINT32,\
                    "tamex_bplast5time_edgev",         "tamex_bplast5time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast5time_channel,       UINT32,\
                    "tamex_bplast5time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast5time_channelv,      UINT32,\
                    "tamex_bplast5time_channelv",      "tamex_bplast5time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast5time_epoch,         UINT32,\
                    "tamex_bplast5time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast5time_epochv,        UINT32,\
                    "tamex_bplast5time_epochv",        "tamex_bplast5time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast6trig,               UINT32,\
                    "tamex_bplast6trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_bplast6event_size,         UINT32,\
                    "tamex_bplast6event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast6time_coarse,        UINT32,\
                    "tamex_bplast6time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast6time_coarsev,       UINT32,\
                    "tamex_bplast6time_coarsev",       "tamex_bplast6time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast6time_fine,          UINT32,\
                    "tamex_bplast6time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast6time_finev,         UINT32,\
                    "tamex_bplast6time_finev",         "tamex_bplast6time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast6time_edge,          UINT32,\
                    "tamex_bplast6time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast6time_edgev,         UINT32,\
                    "tamex_bplast6time_edgev",         "tamex_bplast6time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast6time_channel,       UINT32,\
                    "tamex_bplast6time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast6time_channelv,      UINT32,\
                    "tamex_bplast6time_channelv",      "tamex_bplast6time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast6time_epoch,         UINT32,\
                    "tamex_bplast6time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast6time_epochv,        UINT32,\
                    "tamex_bplast6time_epochv",        "tamex_bplast6time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast7trig,               UINT32,\
                    "tamex_bplast7trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_bplast7event_size,         UINT32,\
                    "tamex_bplast7event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast7time_coarse,        UINT32,\
                    "tamex_bplast7time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast7time_coarsev,       UINT32,\
                    "tamex_bplast7time_coarsev",       "tamex_bplast7time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast7time_fine,          UINT32,\
                    "tamex_bplast7time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast7time_finev,         UINT32,\
                    "tamex_bplast7time_finev",         "tamex_bplast7time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast7time_edge,          UINT32,\
                    "tamex_bplast7time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast7time_edgev,         UINT32,\
                    "tamex_bplast7time_edgev",         "tamex_bplast7time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast7time_channel,       UINT32,\
                    "tamex_bplast7time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast7time_channelv,      UINT32,\
                    "tamex_bplast7time_channelv",      "tamex_bplast7time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast7time_epoch,         UINT32,\
                    "tamex_bplast7time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast7time_epochv,        UINT32,\
                    "tamex_bplast7time_epochv",        "tamex_bplast7time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast8trig,               UINT32,\
                    "tamex_bplast8trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_bplast8event_size,         UINT32,\
                    "tamex_bplast8event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast8time_coarse,        UINT32,\
                    "tamex_bplast8time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast8time_coarsev,       UINT32,\
                    "tamex_bplast8time_coarsev",       "tamex_bplast8time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast8time_fine,          UINT32,\
                    "tamex_bplast8time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast8time_finev,         UINT32,\
                    "tamex_bplast8time_finev",         "tamex_bplast8time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast8time_edge,          UINT32,\
                    "tamex_bplast8time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast8time_edgev,         UINT32,\
                    "tamex_bplast8time_edgev",         "tamex_bplast8time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast8time_channel,       UINT32,\
                    "tamex_bplast8time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast8time_channelv,      UINT32,\
                    "tamex_bplast8time_channelv",      "tamex_bplast8time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast8time_epoch,         UINT32,\
                    "tamex_bplast8time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast8time_epochv,        UINT32,\
                    "tamex_bplast8time_epochv",        "tamex_bplast8time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast9trig,               UINT32,\
                    "tamex_bplast9trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_bplast9event_size,         UINT32,\
                    "tamex_bplast9event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast9time_coarse,        UINT32,\
                    "tamex_bplast9time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast9time_coarsev,       UINT32,\
                    "tamex_bplast9time_coarsev",       "tamex_bplast9time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast9time_fine,          UINT32,\
                    "tamex_bplast9time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast9time_finev,         UINT32,\
                    "tamex_bplast9time_finev",         "tamex_bplast9time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast9time_edge,          UINT32,\
                    "tamex_bplast9time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast9time_edgev,         UINT32,\
                    "tamex_bplast9time_edgev",         "tamex_bplast9time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast9time_channel,       UINT32,\
                    "tamex_bplast9time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast9time_channelv,      UINT32,\
                    "tamex_bplast9time_channelv",      "tamex_bplast9time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_bplast9time_epoch,         UINT32,\
                    "tamex_bplast9time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_bplast9time_epochv,        UINT32,\
                    "tamex_bplast9time_epochv",        "tamex_bplast9time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1trig,               UINT32,\
                    "tamex_fatima1trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_fatima1event_size,         UINT32,\
                    "tamex_fatima1event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_coarse,        UINT32,\
                    "tamex_fatima1time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_coarsev,       UINT32,\
                    "tamex_fatima1time_coarsev",       "tamex_fatima1time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_fine,          UINT32,\
                    "tamex_fatima1time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_finev,         UINT32,\
                    "tamex_fatima1time_finev",         "tamex_fatima1time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_edge,          UINT32,\
                    "tamex_fatima1time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_edgev,         UINT32,\
                    "tamex_fatima1time_edgev",         "tamex_fatima1time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_channel,       UINT32,\
                    "tamex_fatima1time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_channelv,      UINT32,\
                    "tamex_fatima1time_channelv",      "tamex_fatima1time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_epoch,         UINT32,\
                    "tamex_fatima1time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima1time_epochv,        UINT32,\
                    "tamex_fatima1time_epochv",        "tamex_fatima1time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima2trig,               UINT32,\
                    "tamex_fatima2trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_fatima2event_size,         UINT32,\
                    "tamex_fatima2event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima2time_coarse,        UINT32,\
                    "tamex_fatima2time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima2time_coarsev,       UINT32,\
                    "tamex_fatima2time_coarsev",       "tamex_fatima2time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima2time_fine,          UINT32,\
                    "tamex_fatima2time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima2time_finev,         UINT32,\
                    "tamex_fatima2time_finev",         "tamex_fatima2time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima2time_edge,          UINT32,\
                    "tamex_fatima2time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima2time_edgev,         UINT32,\
                    "tamex_fatima2time_edgev",         "tamex_fatima2time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima2time_channel,       UINT32,\
                    "tamex_fatima2time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima2time_channelv,      UINT32,\
                    "tamex_fatima2time_channelv",      "tamex_fatima2time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima2time_epoch,         UINT32,\
                    "tamex_fatima2time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima2time_epochv,        UINT32,\
                    "tamex_fatima2time_epochv",        "tamex_fatima2time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima3trig,               UINT32,\
                    "tamex_fatima3trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_fatima3event_size,         UINT32,\
                    "tamex_fatima3event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima3time_coarse,        UINT32,\
                    "tamex_fatima3time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima3time_coarsev,       UINT32,\
                    "tamex_fatima3time_coarsev",       "tamex_fatima3time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima3time_fine,          UINT32,\
                    "tamex_fatima3time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima3time_finev,         UINT32,\
                    "tamex_fatima3time_finev",         "tamex_fatima3time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima3time_edge,          UINT32,\
                    "tamex_fatima3time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima3time_edgev,         UINT32,\
                    "tamex_fatima3time_edgev",         "tamex_fatima3time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima3time_channel,       UINT32,\
                    "tamex_fatima3time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima3time_channelv,      UINT32,\
                    "tamex_fatima3time_channelv",      "tamex_fatima3time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima3time_epoch,         UINT32,\
                    "tamex_fatima3time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima3time_epochv,        UINT32,\
                    "tamex_fatima3time_epochv",        "tamex_fatima3time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima4trig,               UINT32,\
                    "tamex_fatima4trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_fatima4event_size,         UINT32,\
                    "tamex_fatima4event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima4time_coarse,        UINT32,\
                    "tamex_fatima4time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima4time_coarsev,       UINT32,\
                    "tamex_fatima4time_coarsev",       "tamex_fatima4time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima4time_fine,          UINT32,\
                    "tamex_fatima4time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima4time_finev,         UINT32,\
                    "tamex_fatima4time_finev",         "tamex_fatima4time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima4time_edge,          UINT32,\
                    "tamex_fatima4time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima4time_edgev,         UINT32,\
                    "tamex_fatima4time_edgev",         "tamex_fatima4time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima4time_channel,       UINT32,\
                    "tamex_fatima4time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima4time_channelv,      UINT32,\
                    "tamex_fatima4time_channelv",      "tamex_fatima4time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima4time_epoch,         UINT32,\
                    "tamex_fatima4time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima4time_epochv,        UINT32,\
                    "tamex_fatima4time_epochv",        "tamex_fatima4time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima5trig,               UINT32,\
                    "tamex_fatima5trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_fatima5event_size,         UINT32,\
                    "tamex_fatima5event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima5time_coarse,        UINT32,\
                    "tamex_fatima5time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima5time_coarsev,       UINT32,\
                    "tamex_fatima5time_coarsev",       "tamex_fatima5time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima5time_fine,          UINT32,\
                    "tamex_fatima5time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima5time_finev,         UINT32,\
                    "tamex_fatima5time_finev",         "tamex_fatima5time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima5time_edge,          UINT32,\
                    "tamex_fatima5time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima5time_edgev,         UINT32,\
                    "tamex_fatima5time_edgev",         "tamex_fatima5time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima5time_channel,       UINT32,\
                    "tamex_fatima5time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima5time_channelv,      UINT32,\
                    "tamex_fatima5time_channelv",      "tamex_fatima5time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima5time_epoch,         UINT32,\
                    "tamex_fatima5time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima5time_epochv,        UINT32,\
                    "tamex_fatima5time_epochv",        "tamex_fatima5time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima6trig,               UINT32,\
                    "tamex_fatima6trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_fatima6event_size,         UINT32,\
                    "tamex_fatima6event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima6time_coarse,        UINT32,\
                    "tamex_fatima6time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima6time_coarsev,       UINT32,\
                    "tamex_fatima6time_coarsev",       "tamex_fatima6time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima6time_fine,          UINT32,\
                    "tamex_fatima6time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima6time_finev,         UINT32,\
                    "tamex_fatima6time_finev",         "tamex_fatima6time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima6time_edge,          UINT32,\
                    "tamex_fatima6time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima6time_edgev,         UINT32,\
                    "tamex_fatima6time_edgev",         "tamex_fatima6time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima6time_channel,       UINT32,\
                    "tamex_fatima6time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima6time_channelv,      UINT32,\
                    "tamex_fatima6time_channelv",      "tamex_fatima6time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima6time_epoch,         UINT32,\
                    "tamex_fatima6time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima6time_epochv,        UINT32,\
                    "tamex_fatima6time_epochv",        "tamex_fatima6time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima7trig,               UINT32,\
                    "tamex_fatima7trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_fatima7event_size,         UINT32,\
                    "tamex_fatima7event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima7time_coarse,        UINT32,\
                    "tamex_fatima7time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima7time_coarsev,       UINT32,\
                    "tamex_fatima7time_coarsev",       "tamex_fatima7time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima7time_fine,          UINT32,\
                    "tamex_fatima7time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima7time_finev,         UINT32,\
                    "tamex_fatima7time_finev",         "tamex_fatima7time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima7time_edge,          UINT32,\
                    "tamex_fatima7time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima7time_edgev,         UINT32,\
                    "tamex_fatima7time_edgev",         "tamex_fatima7time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima7time_channel,       UINT32,\
                    "tamex_fatima7time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima7time_channelv,      UINT32,\
                    "tamex_fatima7time_channelv",      "tamex_fatima7time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima7time_epoch,         UINT32,\
                    "tamex_fatima7time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima7time_epochv,        UINT32,\
                    "tamex_fatima7time_epochv",        "tamex_fatima7time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima8trig,               UINT32,\
                    "tamex_fatima8trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_fatima8event_size,         UINT32,\
                    "tamex_fatima8event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima8time_coarse,        UINT32,\
                    "tamex_fatima8time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima8time_coarsev,       UINT32,\
                    "tamex_fatima8time_coarsev",       "tamex_fatima8time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima8time_fine,          UINT32,\
                    "tamex_fatima8time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima8time_finev,         UINT32,\
                    "tamex_fatima8time_finev",         "tamex_fatima8time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima8time_edge,          UINT32,\
                    "tamex_fatima8time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima8time_edgev,         UINT32,\
                    "tamex_fatima8time_edgev",         "tamex_fatima8time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima8time_channel,       UINT32,\
                    "tamex_fatima8time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima8time_channelv,      UINT32,\
                    "tamex_fatima8time_channelv",      "tamex_fatima8time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima8time_epoch,         UINT32,\
                    "tamex_fatima8time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima8time_epochv,        UINT32,\
                    "tamex_fatima8time_epochv",        "tamex_fatima8time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima9trig,               UINT32,\
                    "tamex_fatima9trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_fatima9event_size,         UINT32,\
                    "tamex_fatima9event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima9time_coarse,        UINT32,\
                    "tamex_fatima9time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima9time_coarsev,       UINT32,\
                    "tamex_fatima9time_coarsev",       "tamex_fatima9time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima9time_fine,          UINT32,\
                    "tamex_fatima9time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima9time_finev,         UINT32,\
                    "tamex_fatima9time_finev",         "tamex_fatima9time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima9time_edge,          UINT32,\
                    "tamex_fatima9time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima9time_edgev,         UINT32,\
                    "tamex_fatima9time_edgev",         "tamex_fatima9time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima9time_channel,       UINT32,\
                    "tamex_fatima9time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima9time_channelv,      UINT32,\
                    "tamex_fatima9time_channelv",      "tamex_fatima9time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_fatima9time_epoch,         UINT32,\
                    "tamex_fatima9time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_fatima9time_epochv,        UINT32,\
                    "tamex_fatima9time_epochv",        "tamex_fatima9time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex1trig,                UINT32,\
                    "tamex_tamex1trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_tamex1event_size,          UINT32,\
                    "tamex_tamex1event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex1time_coarse,         UINT32,\
                    "tamex_tamex1time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex1time_coarsev,        UINT32,\
                    "tamex_tamex1time_coarsev",        "tamex_tamex1time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex1time_fine,           UINT32,\
                    "tamex_tamex1time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex1time_finev,          UINT32,\
                    "tamex_tamex1time_finev",          "tamex_tamex1time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex1time_edge,           UINT32,\
                    "tamex_tamex1time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex1time_edgev,          UINT32,\
                    "tamex_tamex1time_edgev",          "tamex_tamex1time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex1time_channel,        UINT32,\
                    "tamex_tamex1time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex1time_channelv,       UINT32,\
                    "tamex_tamex1time_channelv",       "tamex_tamex1time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex1time_epoch,          UINT32,\
                    "tamex_tamex1time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex1time_epochv,         UINT32,\
                    "tamex_tamex1time_epochv",         "tamex_tamex1time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex2trig,                UINT32,\
                    "tamex_tamex2trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_tamex2event_size,          UINT32,\
                    "tamex_tamex2event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex2time_coarse,         UINT32,\
                    "tamex_tamex2time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex2time_coarsev,        UINT32,\
                    "tamex_tamex2time_coarsev",        "tamex_tamex2time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex2time_fine,           UINT32,\
                    "tamex_tamex2time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex2time_finev,          UINT32,\
                    "tamex_tamex2time_finev",          "tamex_tamex2time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex2time_edge,           UINT32,\
                    "tamex_tamex2time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex2time_edgev,          UINT32,\
                    "tamex_tamex2time_edgev",          "tamex_tamex2time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex2time_channel,        UINT32,\
                    "tamex_tamex2time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex2time_channelv,       UINT32,\
                    "tamex_tamex2time_channelv",       "tamex_tamex2time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex2time_epoch,          UINT32,\
                    "tamex_tamex2time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex2time_epochv,         UINT32,\
                    "tamex_tamex2time_epochv",         "tamex_tamex2time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex3trig,                UINT32,\
                    "tamex_tamex3trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_tamex3event_size,          UINT32,\
                    "tamex_tamex3event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex3time_coarse,         UINT32,\
                    "tamex_tamex3time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex3time_coarsev,        UINT32,\
                    "tamex_tamex3time_coarsev",        "tamex_tamex3time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex3time_fine,           UINT32,\
                    "tamex_tamex3time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex3time_finev,          UINT32,\
                    "tamex_tamex3time_finev",          "tamex_tamex3time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex3time_edge,           UINT32,\
                    "tamex_tamex3time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex3time_edgev,          UINT32,\
                    "tamex_tamex3time_edgev",          "tamex_tamex3time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex3time_channel,        UINT32,\
                    "tamex_tamex3time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex3time_channelv,       UINT32,\
                    "tamex_tamex3time_channelv",       "tamex_tamex3time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex3time_epoch,          UINT32,\
                    "tamex_tamex3time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex3time_epochv,         UINT32,\
                    "tamex_tamex3time_epochv",         "tamex_tamex3time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex4trig,                UINT32,\
                    "tamex_tamex4trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_tamex4event_size,          UINT32,\
                    "tamex_tamex4event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex4time_coarse,         UINT32,\
                    "tamex_tamex4time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex4time_coarsev,        UINT32,\
                    "tamex_tamex4time_coarsev",        "tamex_tamex4time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex4time_fine,           UINT32,\
                    "tamex_tamex4time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex4time_finev,          UINT32,\
                    "tamex_tamex4time_finev",          "tamex_tamex4time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex4time_edge,           UINT32,\
                    "tamex_tamex4time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex4time_edgev,          UINT32,\
                    "tamex_tamex4time_edgev",          "tamex_tamex4time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex4time_channel,        UINT32,\
                    "tamex_tamex4time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex4time_channelv,       UINT32,\
                    "tamex_tamex4time_channelv",       "tamex_tamex4time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex4time_epoch,          UINT32,\
                    "tamex_tamex4time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex4time_epochv,         UINT32,\
                    "tamex_tamex4time_epochv",         "tamex_tamex4time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex5trig,                UINT32,\
                    "tamex_tamex5trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_tamex5event_size,          UINT32,\
                    "tamex_tamex5event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex5time_coarse,         UINT32,\
                    "tamex_tamex5time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex5time_coarsev,        UINT32,\
                    "tamex_tamex5time_coarsev",        "tamex_tamex5time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex5time_fine,           UINT32,\
                    "tamex_tamex5time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex5time_finev,          UINT32,\
                    "tamex_tamex5time_finev",          "tamex_tamex5time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex5time_edge,           UINT32,\
                    "tamex_tamex5time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex5time_edgev,          UINT32,\
                    "tamex_tamex5time_edgev",          "tamex_tamex5time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex5time_channel,        UINT32,\
                    "tamex_tamex5time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex5time_channelv,       UINT32,\
                    "tamex_tamex5time_channelv",       "tamex_tamex5time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex5time_epoch,          UINT32,\
                    "tamex_tamex5time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex5time_epochv,         UINT32,\
                    "tamex_tamex5time_epochv",         "tamex_tamex5time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex6trig,                UINT32,\
                    "tamex_tamex6trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_tamex6event_size,          UINT32,\
                    "tamex_tamex6event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex6time_coarse,         UINT32,\
                    "tamex_tamex6time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex6time_coarsev,        UINT32,\
                    "tamex_tamex6time_coarsev",        "tamex_tamex6time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex6time_fine,           UINT32,\
                    "tamex_tamex6time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex6time_finev,          UINT32,\
                    "tamex_tamex6time_finev",          "tamex_tamex6time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex6time_edge,           UINT32,\
                    "tamex_tamex6time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex6time_edgev,          UINT32,\
                    "tamex_tamex6time_edgev",          "tamex_tamex6time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex6time_channel,        UINT32,\
                    "tamex_tamex6time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex6time_channelv,       UINT32,\
                    "tamex_tamex6time_channelv",       "tamex_tamex6time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex6time_epoch,          UINT32,\
                    "tamex_tamex6time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex6time_epochv,         UINT32,\
                    "tamex_tamex6time_epochv",         "tamex_tamex6time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex7trig,                UINT32,\
                    "tamex_tamex7trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_tamex7event_size,          UINT32,\
                    "tamex_tamex7event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex7time_coarse,         UINT32,\
                    "tamex_tamex7time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex7time_coarsev,        UINT32,\
                    "tamex_tamex7time_coarsev",        "tamex_tamex7time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex7time_fine,           UINT32,\
                    "tamex_tamex7time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex7time_finev,          UINT32,\
                    "tamex_tamex7time_finev",          "tamex_tamex7time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex7time_edge,           UINT32,\
                    "tamex_tamex7time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex7time_edgev,          UINT32,\
                    "tamex_tamex7time_edgev",          "tamex_tamex7time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex7time_channel,        UINT32,\
                    "tamex_tamex7time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex7time_channelv,       UINT32,\
                    "tamex_tamex7time_channelv",       "tamex_tamex7time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex7time_epoch,          UINT32,\
                    "tamex_tamex7time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex7time_epochv,         UINT32,\
                    "tamex_tamex7time_epochv",         "tamex_tamex7time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex8trig,                UINT32,\
                    "tamex_tamex8trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_tamex8event_size,          UINT32,\
                    "tamex_tamex8event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex8time_coarse,         UINT32,\
                    "tamex_tamex8time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex8time_coarsev,        UINT32,\
                    "tamex_tamex8time_coarsev",        "tamex_tamex8time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex8time_fine,           UINT32,\
                    "tamex_tamex8time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex8time_finev,          UINT32,\
                    "tamex_tamex8time_finev",          "tamex_tamex8time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex8time_edge,           UINT32,\
                    "tamex_tamex8time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex8time_edgev,          UINT32,\
                    "tamex_tamex8time_edgev",          "tamex_tamex8time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex8time_channel,        UINT32,\
                    "tamex_tamex8time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex8time_channelv,       UINT32,\
                    "tamex_tamex8time_channelv",       "tamex_tamex8time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex8time_epoch,          UINT32,\
                    "tamex_tamex8time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex8time_epochv,         UINT32,\
                    "tamex_tamex8time_epochv",         "tamex_tamex8time_epoch",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex9trig,                UINT32,\
                    "tamex_tamex9trig",65535,0/*flags*/); \
  EXT_STR_ITEM_INFO2    (ok,si,offset,struct_t,printerr,\
                     tamex_tamex9event_size,          UINT32,\
                    "tamex_tamex9event_size",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex9time_coarse,         UINT32,\
                    "tamex_tamex9time_coarse",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex9time_coarsev,        UINT32,\
                    "tamex_tamex9time_coarsev",        "tamex_tamex9time_coarse",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex9time_fine,           UINT32,\
                    "tamex_tamex9time_fine",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex9time_finev,          UINT32,\
                    "tamex_tamex9time_finev",          "tamex_tamex9time_fine",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex9time_edge,           UINT32,\
                    "tamex_tamex9time_edge",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex9time_edgev,          UINT32,\
                    "tamex_tamex9time_edgev",          "tamex_tamex9time_edge",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex9time_channel,        UINT32,\
                    "tamex_tamex9time_channel",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex9time_channelv,       UINT32,\
                    "tamex_tamex9time_channelv",       "tamex_tamex9time_channel",0/*flags*/); \
  EXT_STR_ITEM_INFO2_LIM(ok,si,offset,struct_t,printerr,\
                     tamex_tamex9time_epoch,          UINT32,\
                    "tamex_tamex9time_epoch",1024,0/*flags*/); \
  EXT_STR_ITEM_INFO2_ZZP(ok,si,offset,struct_t,printerr,\
                     tamex_tamex9time_epochv,         UINT32,\
                    "tamex_tamex9time_epochv",         "tamex_tamex9time_epoch",0/*flags*/); \
  \
} while (0);

#endif/*__GUARD_H101_TAMEX_EXT_H101_TAMEX_H__*/

/*******************************************************/
