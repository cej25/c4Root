#ifndef DespecSetup_H
#define DespecSetup_H

// general
#define NO_UINT64 1 // define until uint64 unpacking is supported

// "detector" numbers, pick some large int that won't overlap with mappings
#define TM_U 1000
#define TM_D 1001
#define SC41L_A 1002
#define SC41R_A 1003
#define SC41L_D 1004
#define SC41R_D 1005

// fatima tamex
#define MAX_CHA_INPUT 33

// fatima vme
#define IS_SCALERS_ON 1
#define QDC_BOARDS 5
#define CHANNELS_PER_QDC 8
#define TDC_BOARDS 2
#define FAT_VME_MAX_SCALERS 32
#define FAT_VME_MAX_HITS 51
#define FAT_VME_MAX_DETS 60

// aida
#define AIDA_MAX_FEES 12
#define AIDA_MAX_HITS 13000
#define AIDA_UCESB_SHIFT 14000 // ns ucesb1 shifts MBS timestamps of AIDA
#define AIDA_DSSDS 3

// bplast
#define BPLAST_TAMEX_MODULES 9
#define IS_BPLAST_TWINPEAKS 1
#define BPLAST_CHANNELS_PER_TAMEX 16
#define BPLAST_CHANNELS_PER_DET 64

// germaniums
#define GE_MAX_DETS 4
#define GE_MAX_CRYSTALS 7
#define GE_MAX_HITS (GE_MAX_DETS * GE_MAX_CRYSTALS)
#define GE_FEBEX_MODULES 2
#define GE_MAX_CHANNELS 49


#endif /* DespecSetup_H */
