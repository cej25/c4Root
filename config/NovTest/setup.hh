#ifndef DespecSetup_H
#define DespecSetup_H

// general
#define NO_UINT64 1 // define until uint64 unpacking is supported 
// used systems
#define FRS_USED 0
#define GERMANIUM_USED 0
#define BPLAST_USED 1
#define FATIMA_USED 0
#define AIDA_USED 0
#define WR_USED 1

// aida
#define AIDA_MAX_FEES 12
#define AIDA_MAX_HITS 13000 // 13k?
#define AIDA_UCESB_SHIFT 14000 // ns ucesb1 shifts MBS timestamps of AIDA

// germaniums
#define GE_MAX_DETS 4
#define GE_MAX_CRYSTALS 7
#define GE_MAX_HITS (GE_MAX_DETS * GE_MAX_CRYSTALS)
#define GE_FEBEX_MODULES 2
#define GE_MAX_CHANNELS 49

// fatima vme
#define SCALER_MODULE_ON 1
#define FAT_TDC_NUMBER 2
#define FAT_MAX_VME_CHANNELS 51
#define FAT_MAX_HITS 1000 // made up for now lol
#define MAX_AM_DETS_VME 60
#define MAX_SCALERS_VME 32

// fatima tamex
#define MAX_CHA_INPUT 33 // maximum physical input channels per module. must be modulo 4 -- CEJ: is this same for fatima and bplast tp?


// bplast tamex
#define PLASTIC_MAX_HITS 1 // something made up for item_append purposes // CEJ fix... 1000? 100? 10?
// this never goes over 3 for test file. 
#define PLASTIC_MAX_ITER 100
// 0 for regular tamex, 1 for twinpeaks
#define IS_PLASTIC_TWINPEAKS 1
#define BPLAST_TAMEX_MODULES 9 // 9 in S450? 3 in S452
#define PLASTIC_TWINPEAKS_MAX_ITER 200 
#define BPLAST_CHAN_PER_DET 64 // S452
// is this redundant?
#define BPLAST_TAMEX_CHANNELS 16

// frs
#define FRS_TPAT_MAX_HITS 30 // idek if this is needed seriously. append item? cmon.
#define FRS_CRATE_MAX_HITS 30
#define FRS_MAIN_CRATE_MAX_HITS 30
#define FRS_MAX_HITS 1
#define VFTX_N 1 // will this ever be more than 1 cus seems pointless rn.
#define VFTX_MAX_CHN 32
#define VFTX_MAX_HITS 20

#define SCI_MOD 0
#define SCI21L_CH 5
#define SCI21R_CH 6
#define SCI22L_CH 12
#define SCI22R_CH 13
#define SCI41L_CH 7
#define SCI41R_CH 8
#define SCI42L_CH 3 
#define SCI42R_CH 4

#endif /* DespecSetup_H */
