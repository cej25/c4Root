#include "Riostream.h"

void setup(TFRSParameter* frs,
        TMWParameter* mw,
        TTPCParameter* tpc,
        TMUSICParameter* music,
        TLABRParameter* labr,
        TSCIParameter* sci,
        TIDParameter* id,
        TSIParameter* si,
        TMRTOFMSParameter* mrtof,
        TRangeParameter* range)
{
  frs->rho0[0]   = 1.; //TA-S2
  frs->rho0[1]   = 1.; //S2-S4
  frs->rho0[2]   = 1.; //S4-S8
  frs->rho0[4]   = 1.; //TA-S1
  frs->rho0[5]   = 1.; //S1-S2
  frs->rho0[6]   = 1.; //S2-S3

  // note: dispersion same sign as gicosy. Unit in m.

  //--------TA2-F4 4m 2025March31 G22-150  
  frs->magnification[0] =  0.7810135; frs->dispersion[0] = -6.490297;//  TA-S2
  frs->magnification[1] =  1.218618;   frs->dispersion[1] = 7.909082; //8.50;//  S2-S4
  frs->magnification[2] =  1.;       frs->dispersion[2] = 1.;//  S2-S8   not used in this experiment
  frs->magnification[3] =  1.;       frs->dispersion[3] = 1.;//  S2-HTM  not used in this experiment
  frs->magnification[4] = -0.53286 ;  frs->dispersion[4] = 2.151157;//  TA-S1
  frs->magnification[5] = -1.444855 ;  frs->dispersion[5] = -3.370861;//  S1-S2
  frs->magnification[6] = -0.76816;  frs->dispersion[6] = -2.0066;//  S2-S3

 //=============distances=============//
  //S1
  frs->dist_focS1 = 1280; //Assumed to be at degrader position
  frs->dist_SC11 = 2060; //
  
  //S2
  frs->dist_focS2 = 2012.5; //s2 disk eng-run 2023-11-16
  frs->dist_TPC21 =  604.0; // eng-run 2023-11-16
  frs->dist_TPC22 = 1782.5; //eng-run 2023-11-16
  frs->dist_TPC23 = 4560.0-1670.0; //G-22-00160 2025-01-31
  frs->dist_TPC24 = 4560.0-577.0; //G-22-00160 2025-01-31
  frs->dist_MUSIC21 = 4560.0-1276.0;  //G-22-00160 2025-01-31
  frs->dist_MUSIC22 = 4560.0-853.0; //G-22-00160 2025-01-31
  frs->dist_SC21  = 1554.5; //eng-run 2023-11-16
  frs->dist_SC22  = 4560.0-1837.0; //G-22-00160 2025-01-31
  frs->dist_S2target = 4560.0-1557.0; // Target ladder G-22-00160 2025-01-31
  //frs->dist_S2target = 4560.0-853.0; // Expert G-22-00160 2025-01-31
  //frs->dist_S2target = 4560.0-853.0-55.0-400.0/2.0; // Expert target G-22-00160 2025-01-31

  //S3
  frs->dist_SC31 = 1714.0; //added by XXu, 21.02.2025
  frs->dist_focS3 = 1279.0; //s3 slits, by XXu, 21.02.2025

  //S4
  frs->dist_SC41    = 2156.0+125.0; // eng-run 2023-11-16
  frs->dist_SC42    = 2575.0 + 125.0; // G-22-00160 2025-02-01
  frs->dist_SC43    = 5145.0+125.0; // G-22-00160 2025-02-04
  frs->dist_MUSIC41 = 600.0+125.0;  // eng-run 2023-11-16
  frs->dist_MUSIC42 = 1096.0+125.0; // eng-run 2023-11-16
  frs->dist_MUSIC43 = 3500.0; // not installed
  frs->dist_MUSIC44 = 5000.0; // not installed
  frs->dist_TPC41   =  220.0+125.0; // eng-run 2023-11-16
  frs->dist_TPC42   = 1457.0+125.0; // eng-run 2023-11-16
  //frs->dist_S4target= 1800.0+125.0; // S4 x slits G-22-00160 2025-02-04
  //frs->dist_S4target= 2385.0+125.0; // S4 degrader G-22-00160 2025-02-04
  //frs->dist_S4target= 4050.0+125.0; // FRS-IC degrader G-22-00160 2025-02-01
  frs->dist_S4target= 4937.0+125.0; // FRS-IC Fiber G-22-00160 2025-02-01
  //frs->dist_S4target= 4955.0+125.0; // FRS-IC fluorecencs screen G-22-00160 2025-02-01
  //frs->dist_S4target= 5145.0+ 168.0 +125.0; // FRS-IC G-22-00160 2025-02-04
  frs->dist_focS4   =4000.0; // FRS optics run81-ta2-2021-4m.txt

  //S8
  frs->dist_focS8 = 0;
  frs->dist_SC81 = 0;

  //=============switches=============//
  id->x_s2_select   = 1; //1=tpc,2=sc21,3=sc22
  id->tof_s2_select = 1; //1 = sc11-21, 2 = sc11-22(not in TAC)
  id->tof_s4_select = 1; //1=sc21-41, 2=sc21-42, 3=sc22-41 used for TAC and MHTDC
  id->tof_s8_select = 1; //1=sc21-81, 2=sc22-81

  id->tof_HTM_select = 1; //1=sc21-M01, 2=sc22-M01
  id->Z_HTM_select = 3; //1=sc21, 2=sc22, 3=scM01

  //S1S2 PID options
  id->use_sc11x = 0; //0 = brho from TA-S2, no s1 x used, 1 = x from sc11 lr dt
  
  //=============primary Z and plot ranges=============//
  frs->primary_z = 26.;
  id->min_aoq_plot = 1.7;
  id->max_aoq_plot = 2.3;
  id->min_z_plot   = 12;
  id->max_z_plot   = 28;

  // bfield (Tm) for new control system. (we put rho = 1)
  frs->bfield[0] = 6.3096;// run4 56Fe TA2-F1
  frs->bfield[1] = 6.1643;// run4 56Fe F1-F2
  frs->bfield[2] = 5.4718;// run4 56Fe F2-F3
  frs->bfield[3] = 5.4718;// run4 56Fe F3-F4
  frs->bfield[4] = 4.8347;   //  D5 (to ESR) not used
  frs->bfield[5] = 4.8347;  //   D6 (to S8)

  // From here Multi-HitTDC analysis
  id->mhtdc_length_s2s8 = 85.230; // (2019/Nov, YT)
  id->pos_offset_sc81x  = 7.0;// (2019/Nov, YT)

  // MHTDCAnalysis TPC@S2dE => Z estimation, velocity correction
  id->mhtdc_vel_a_s2tpc[0] =  1400.0;// TPC-A does not look promising...21-feb-2020
  id->mhtdc_vel_a_s2tpc[1] =  0.0;// put constant here
  id->mhtdc_vel_a_s2tpc[2] =  0.0;//
  id->mhtdc_vel_a_s2tpc[3] =  0.0;
  id->mhtdc_offset_z_s2tpc =  0.0;

  // MHTDCAnalysis, velocity correction SC81dE => Z estimation
  id->mhtdc_vel_a_sc81[0] =  2156.4;// SC81 dE was not propery measured.
  id->mhtdc_vel_a_sc81[1] =  0.0; // I skip to set these parameters
  id->mhtdc_vel_a_sc81[2] =  0.0; // this time ...
  id->mhtdc_vel_a_sc81[3] =  0.0;
  id->mhtdc_offset_z_sc81 =  0.0;

  // MHTDCAnalysis S1-S2
  //id->mhtdc_length_sc1121 = (18.07667 + 0.001*(frs->dist_SC21 - frs->dist_focS2) + 0.001*(frs->dist_focS1 - frs->dist_SC11) );// SCI 11-21
  //id->mhtdc_length_sc1122 = (18.07667 + 0.001*(frs->dist_SC21 - frs->dist_focS2) + 0.001*(frs->dist_focS1 - frs->dist_SC11) );// SCI 11-22
  id->mhtdc_length_sc1121 =	56.745	*0.299792458 ;// updated 	2025/05/09
  id->mhtdc_length_sc1122 =	61.4416884	*0.299792458 ;// updated 	2025/02/27

  // MHTDCAnalysis S2-S3
  id->mhtdc_length_sc2131 = (18.07667 + 0.001*(frs->dist_SC21 - frs->dist_focS2) + 0.001*(frs->dist_focS3 - frs->dist_SC31) );// SCI 31-21, added by XXu, 21.02.2025
 
  // MHTDCAnalysis S2-S4
  id->mhtdc_length_sc2141 =	127.308444	*0.299792458; //  updated *2	2025/05/09	
  id->mhtdc_length_sc2142 =	127.720820	*0.299792458 ;// updated 	2025/05/09	
  id->mhtdc_length_sc2241 =	122.4751556	*0.299792458 ;// updated 	2025/02/27	
  //id->mhtdc_length_sc2141 =	124.5858539	*0.299792458 ;// updated 	2025/02/21
  //id->mhtdc_length_sc2142 =	127.2291434	*0.299792458 ;// updated 	2025/02/21
  //id->mhtdc_length_sc2241 =	122.4657914	*0.299792458 ;// updated 	2025/02/21

  sci->mhtdc_offset_41_21  =  183.4148170 - 4.010343; //183.4148170 - 4.010343; //183.4148170 + 0.010343; //Updated 09/05/2025 ns update //G-22-103 56Fe
  sci->mhtdc_offset_42_21  =  183.16 -2.625508775	-0.3117607688 + 2.758419; // updated 	2025/05/09
  sci->mhtdc_offset_41_22  =  240.33 -0.5586602465 +0.06468333655	; // updated 	2025/02/21

  // MHTDCAnalysis S2-HTM
  id->mhtdc_length_sc21HTM = 161.384 - 34.937; // meter SCI 21-M01 update 07.05.21
  id->mhtdc_length_sc22HTM = 161.384 - 34.937 - 1.; // meter SCI 22-M01 update 07.05.21

  //not related for S8
  id->a1AoQCorr = 0; //s1-s2 - actually correction for angle at s2 as there is no angle measurement at s1
  id->a2AoQCorr = -0.0012; //correction for s2s4 -- 0.0012; //2020April12 JP
  id->a4AoQCorr = 0.0;

  //=========
  // MUSICs
  //=========
	
  // number of anodes
  music->MUSIC21_num_an = 8;
  music->MUSIC22_num_an = 8;
  music->MUSIC41_num_an = 8;
  music->MUSIC42_num_an = 8;
  music->MUSIC43_num_an = 4;
  
  //MUSIC electronics: 0-2 electronics in Messhuette, 3-4 electronics in traveling MUSIC crate
	music->MUSIC21_elec = 3; 
	music->MUSIC22_elec = 4;
	music->MUSIC41_elec = 0;
	music->MUSIC42_elec = 1;
	music->MUSIC43_elec = 2;
	
  // histogram setup
  music->max_adc_music21 =  65536; //0x10000; //travel music MDPP --Martin
  music->max_adc_music22 =  65536; //0x10000; //travel music MDPP --Martin
  music->max_adc_music41 =  4096; //tum music
  music->max_adc_music42 =    4096; //tum music
  music->max_adc_music43 =    4096; //prototype music
  music->max_tdc_music21 =    0x10000; //travel music ??
  music->max_tdc_music22 =    0x10000; //travel music ??
  music->max_tdc_music41 =    120000; //tum music
  music->max_tdc_music42 =    120000; //tum music
  music->max_tdc_music43 =    120000; //tum music

  //MUSIC noisy channel to be excluded in dE calculation
  //TRUE means exclude.
  //default is FALSE
  for(int ii=0; ii<8; ii++){
    music->exclude_music21_de_adc_channel[ii] = kFALSE;
    music->exclude_music22_de_adc_channel[ii] = kFALSE;
    music->exclude_music41_de_adc_channel[ii] = kFALSE;
    music->exclude_music42_de_adc_channel[ii] = kFALSE;
    music->exclude_music43_de_adc_channel[ii] = kFALSE;
  }
  music->exclude_music41_de_adc_channel[5] = kTRUE; //added 01:50/May-12/2022 S450
  music->exclude_music43_de_adc_channel[4] = kTRUE; //Prototype MUSIC used with only 4 anodes
  music->exclude_music43_de_adc_channel[5] = kTRUE;
  music->exclude_music43_de_adc_channel[6] = kTRUE;
  music->exclude_music43_de_adc_channel[7] = kTRUE;
  music->exclude_music21_de_adc_channel[7] = kTRUE; //added 12:50 AM/Feb-07/2025 S160
  music->exclude_music42_de_adc_channel[2] = kTRUE; //added 12:50 AM/Feb-07/2025 S160
  music->exclude_music42_de_adc_channel[4] = kTRUE; //added 12:50 AM/Feb-07/2025 S160

  //
  music->dist_MUSICa1 = 52.5;  // do not change
  music->dist_MUSICa2 = 157.5; // do not change
  music->dist_MUSICa3 = 262.5; // do not change
  music->dist_MUSICa4 = 367.5; // do not change


  //MUSIC21
  music->music21_e_off[0]   = 0.; //MUSIC21 offsets
  music->music21_e_off[1]   = 0.;
  music->music21_e_off[2]   = 0.;
  music->music21_e_off[3]   = 0.;
  music->music21_e_off[4]   = 0.;
  music->music21_e_off[5]   = 0.;
  music->music21_e_off[6]   = 0.;
  music->music21_e_off[7]   = 0.;

  music->music21_e_gain[0]   = 1.; // MUSIC21 gains
  music->music21_e_gain[1]   = 1.;
  music->music21_e_gain[2]   = 1.;
  music->music21_e_gain[3]   = 1.;
  music->music21_e_gain[4]   = 1.;
  music->music21_e_gain[5]   = 1.;
  music->music21_e_gain[6]   = 1.;
  music->music21_e_gain[7]   = 1.;

  //MUSIC22
  music->music22_e_off[0]   = 0.; //MUSIC22 offsets
  music->music22_e_off[1]   = 0.;
  music->music22_e_off[2]   = 0.;
  music->music22_e_off[3]   = 0.;
  music->music22_e_off[4]   = 0.;
  music->music22_e_off[5]   = 0.;
  music->music22_e_off[6]   = 0.;
  music->music22_e_off[7]   = 0.;

  music->music22_e_gain[0]   = 1.; //MUSIC22 gains
  music->music22_e_gain[1]   = 1.;
  music->music22_e_gain[2]   = 1.;
  music->music22_e_gain[3]   = 1.;
  music->music22_e_gain[4]   = 1.;
  music->music22_e_gain[5]   = 1.;
  music->music22_e_gain[6]   = 1.;
  music->music22_e_gain[7]   = 1.;

  //MUSIC41
  music->music41_e_off[0]   = 0.; //MUSIC41 offsets
  music->music41_e_off[1]   = 0.;
  music->music41_e_off[2]   = 0.;
  music->music41_e_off[3]   = 0.;
  music->music41_e_off[4]   = 0.;
  music->music41_e_off[5]   = 0.;
  music->music41_e_off[6]   = 0.;
  music->music41_e_off[7]   = 0.;

  music->music41_e_gain[0]   = 1.; // MUSIC41 gains
  music->music41_e_gain[1]   = 1.;
  music->music41_e_gain[2]   = 1.;
  music->music41_e_gain[3]   = 1.;
  music->music41_e_gain[4]   = 1.;
  music->music41_e_gain[5]   = 1.;
  music->music41_e_gain[6]   = 1.;
  music->music41_e_gain[7]   = 1.;

  //MUSIC42
  music->music42_e_off[0]   = 0.; //MUSIC42 offsets
  music->music42_e_off[1]   = 0.;
  music->music42_e_off[2]   = 0.;
  music->music42_e_off[3]   = 0.;
  music->music42_e_off[4]   = 0.;
  music->music42_e_off[5]   = 0.;
  music->music42_e_off[6]   = 0.;
  music->music42_e_off[7]   = 0.;

  music->music42_e_gain[0]   = 1.; //MUSIC42 gains
  music->music42_e_gain[1]   = 1.;
  music->music42_e_gain[2]   = 1.;
  music->music42_e_gain[3]   = 1.;
  music->music42_e_gain[4]   = 1.;
  music->music42_e_gain[5]   = 1.;
  music->music42_e_gain[6]   = 1.;
  music->music42_e_gain[7]   = 1.;

  //MUSIC43
  music->music43_e_off[0]   = 0.; //MUSIC43 offsets
  music->music43_e_off[1]   = 0.;
  music->music43_e_off[2]   = 0.;
  music->music43_e_off[3]   = 0.;
  music->music43_e_off[4]   = 0.;
  music->music43_e_off[5]   = 0.;
  music->music43_e_off[6]   = 0.;
  music->music43_e_off[7]   = 0.;

  music->music43_e_gain[0]   = 1.; // MUSIC43 gains
  music->music43_e_gain[1]   = 1.;
  music->music43_e_gain[2]   = 1.;
  music->music43_e_gain[3]   = 1.;
  music->music43_e_gain[4]   = 1.;
  music->music43_e_gain[5]   = 1.;
  music->music43_e_gain[6]   = 1.;
  music->music43_e_gain[7]   = 1.;

  //MUSIC21 (parameters from 41)
  music->music21_pos_a[0]   =  2540.78; // C0...Cn position correction not used
  music->music21_pos_a[1]   = 0.0745079; 
  music->music21_pos_a[2]   = 0.00154773;
  music->music21_pos_a[3]   = -2.34361e-5; 
  music->music21_pos_a[4]   = -8.04959e-7;
  music->music21_pos_a[5]   =  2.65658e-9;         
  music->music21_pos_a[6]   =  1.73325e-11;

  //MUSIC22 (parameters from 41)
  music->music22_pos_a[0]   = 2540.78; // C0...Cn position correction not used
  music->music22_pos_a[1]   = 0.0745079;
  music->music22_pos_a[2]   = 0.00154773;
  music->music22_pos_a[3]   = -2.34361e-5; 
  music->music22_pos_a[4]   = -8.04959e-7;
  music->music22_pos_a[5]   = 2.65658e-9;   
  music->music22_pos_a[6]   = 1.73325e-11;

  //MUSIC41
  music->music41_pos_a[0]   =  2540.78; // C0...Cn position correction not used
  music->music41_pos_a[1]   = 0.0745079; 
  music->music41_pos_a[2]   = 0.00154773;
  music->music41_pos_a[3]   = -2.34361e-5; 
  music->music41_pos_a[4]   = -8.04959e-7;
  music->music41_pos_a[5]   =  2.65658e-9;      
  music->music41_pos_a[6]   =  1.73325e-11;

  //MUSIC42
  music->music42_pos_a[0]   = 2477.01; // C0...Cn position correction not used
  music->music42_pos_a[1]   = 0.0485704; 
  music->music42_pos_a[2]   = 0.000521307; 
  music->music42_pos_a[3]   = -2.15519e-5; 
  music->music42_pos_a[4]   = -4.11621e-7; 
  music->music42_pos_a[5]   = 1.9045e-9; 
  music->music42_pos_a[6]   = 4.46969e-12; 

  //MUSIC43
  music->music43_pos_a[0]   = 0.998;   // C0...Cn position correction not used
  music->music43_pos_a[1]   = -1.991e-5;
  music->music43_pos_a[2]   = 1.969e-6;
  music->music43_pos_a[3]   = 1.114e-8;
  music->music43_pos_a[4]   = -3.841e-10;
  music->music43_pos_a[5]   = -2.950e-13;
  music->music43_pos_a[6]   = 0.0;

//  MUSIC21 velocity (08.02.2025)
  id->vel_music21_a[0] =   2625.4;//Updated 10/02/2025	//4813.8;//609.38;
  id->vel_music21_a[1] =   13997;//Updated 10/02/2025	//11333.88;//1167.8;
  id->vel_music21_a[2] =   -743.4;//Updated 10/02/2025	//119.49;//0.0;
  id->vel_music21_a[3] =   0.0;

//  MUSIC22 velocity (not determined, values from MUSIC41)
  id->vel_music22_a[0] =   609.38;
  id->vel_music22_a[1] =   1167.8;
  id->vel_music22_a[2] =   0.0;
  id->vel_music22_a[3] =   0.0;

//  MUSIC41 velocity 
  id->vel_music41_a[0] =  419.9431;//updated 2025/04/02 G-22-150 208Pb
  id->vel_music41_a[1] =  1097.9367;// updated 2025/04/02
  id->vel_music41_a[2] =  0.0;
  id->vel_music41_a[3] =  0.0;

// MUSIC42 velocity 
  id->vel_music42_a[0] = 351.698;//updated 2025/04/02 G-22-150 208Pb
  id->vel_music42_a[1] = 1163.352;// updated 2025/04/02
  id->vel_music42_a[2] =  0.0;
  id->vel_music42_a[3] =  0.0;

  //MUSIC43 velocity corr. (old)
  id->vel_music43_a[0] =  29030.0; 
  id->vel_music43_a[1] =  -19790.0;
  id->vel_music43_a[2] =  3635.0;
  id->vel_music43_a[3] =  0.0;
  
 //  MUSIC21 velocity MHTDC 
  //id->mhtdc_vel_a_music21_s1s2[0] = 4813.8; //107Ag  MUSIC21 calibration
  //id->mhtdc_vel_a_music21_s1s2[1] = 11333.88;
  //id->mhtdc_vel_a_music21_s1s2[2] = 119.49;
  //id->mhtdc_vel_a_music21_s1s2[3] = 0.;
  id->mhtdc_vel_a_music21_s1s2[0] = 957.52+770;//1610.668662; // online, 2025/Feb/27 (YT) 2025/05/09
  id->mhtdc_vel_a_music21_s1s2[1] = 8927.7;//7632.695383; // online, 2025/Feb/27 (YT) 2025/05/09
  id->mhtdc_vel_a_music21_s1s2[2] = 0.;
  id->mhtdc_vel_a_music21_s1s2[3] = 0.;

  id->mhtdc_vel_a_music21_s2s3[0] = 4813.8; //107Ag  MUSIC21 calibration
  id->mhtdc_vel_a_music21_s2s3[1] = 11333.88;
  id->mhtdc_vel_a_music21_s2s3[2] = 119.49;
  id->mhtdc_vel_a_music21_s2s3[3] = 0.;
  
   //  MUSIC22 velocity MHTDC 
  id->mhtdc_vel_a_music22[0] = 0.;
  id->mhtdc_vel_a_music22[1] = 1.;
  id->mhtdc_vel_a_music22[2] = 0.;
  id->mhtdc_vel_a_music22[3] = 0.;
  
   //  MUSIC41 velocity MHTDC 
  id->mhtdc_vel_a_music41[0] = 272.79;//419.9431;//updated 2025/04/02 G-22-150 208Pb 2025/05/09
  id->mhtdc_vel_a_music41[1] = 888.9;//1097.9367;// updated 2025/04/02 2025/05/09
  id->mhtdc_vel_a_music41[2] = 0.0;//
  id->mhtdc_vel_a_music41[3] = 0.0;//
  
  //  MUSIC42 velocity MHTDC 
  id->mhtdc_vel_a_music42[0] = 276.81;//351.698;//updated 2025/04/02 G-22-150 208Pb 2025/05/09
  id->mhtdc_vel_a_music42[1] = 872.39;//1163.352;// updated 2025/04/02 2025/05/09
  id->mhtdc_vel_a_music42[2] = 0.0; //
  id->mhtdc_vel_a_music42[3] = 0.0; //
  
 
  //  MUSIC43 velocity MHTDC 
  id->mhtdc_vel_a_music43[0] = 0.;
  id->mhtdc_vel_a_music43[1] = 1.;
  id->mhtdc_vel_a_music43[2] = 0.;
  id->mhtdc_vel_a_music43[3] = 0.;
  
  // velocity HTM Analysis MHTDC
  id->mhtdc_vel_a_scM01[0]=1684.0;
  id->mhtdc_vel_a_scM01[1]=0.0;
  id->mhtdc_vel_a_scM01[2]=0.0;
  id->mhtdc_vel_a_scM01[3]=0.0;
  id->mhtdc_vel_a_sc21[0]=1753.48;
  id->mhtdc_vel_a_sc21[1]=-646.343;
  id->mhtdc_vel_a_sc21[2]=0.0;
  id->mhtdc_vel_a_sc21[3]=0.0;
  id->mhtdc_vel_a_sc22[0]=1600.0;
  id->mhtdc_vel_a_sc22[1]=0.0;
  id->mhtdc_vel_a_sc22[2]=0.0;
  id->mhtdc_vel_a_sc22[3]=0.0;
  
  id->mhtdc_offset_z_music21_s1s2=0.0;
  id->mhtdc_offset_z_music21_s2s3=0.0;
  id->mhtdc_offset_z_music22 = 0.;
  id->mhtdc_offset_z_music41 = 0.00;
  id->mhtdc_offset_z_music42 = 0.00;
  id->mhtdc_offset_z_music43 = 0.;
  id->mhtdc_offset_z_scM01=0.0;
  id->mhtdc_offset_z_sc21=0.0;
  id->mhtdc_offset_z_sc22=0.0;

  id->offset_z21  = 0.0; 
  id->offset_z22  = 0.0;
  id->offset_z41  = 0.0;
  id->offset_z42  = 0.0;
  id->offset_z43  = 0.0;

  // KW selector which beta to use for Z calculations
  // 0 is for S1-S2
  // 1 is for S2-S4
  id->beta_z21 = 0;
  id->beta_z22 = 0;
  id->beta_z41 = 1;
  id->beta_z42 = 1;
  id->beta_z43 = 1;
  // end KW
  
  //=========
  //  TPCs
  //=========
  // multihit TDC cut TPC time reference signal
  // After changing cut limits => Launch analysis again in Go4GUI
  // [Updated on 2021/Mar/21, YT, EH, IM] to catch all timeref signals.
  tpc->lim_timeref[0][0] = 1000.0; tpc->lim_timeref[0][1] = 48000.0;//time ref (accept trig)
  tpc->lim_timeref[1][0] = 5000.0; tpc->lim_timeref[1][1] = 30000.0;//time ref (sc21) changed to narrow gate, 2023-Nov-28
  tpc->lim_timeref[2][0] = 1000.0; tpc->lim_timeref[2][1] = 48500.0;//time ref (sc22)
  tpc->lim_timeref[3][0] = 5000.0; tpc->lim_timeref[3][1] = 30000.0;//time ref (sc31) changed to narrow gate, 2023-Nov-28
  tpc->lim_timeref[4][0] = 5000.0; tpc->lim_timeref[4][1] = 30000.0;//time ref (sc41) changed to narrow gate, 2023-Nov-28
  tpc->lim_timeref[5][0] = 1000.0; tpc->lim_timeref[5][1] = 48000.0;//time ref (---)
  tpc->lim_timeref[6][0] = 1000.0; tpc->lim_timeref[6][1] = 48000.0;//time ref (---)
  tpc->lim_timeref[7][0] = 1000.0; tpc->lim_timeref[7][1] = 48000.0;//time ref (---)


  //-------- TPC21 parameters (updated on // 19/June/2021, BARB june 2021) ---------
  // TPC21 at S2 in vacuum
  //
  tpc->id_tpc_timeref[0] = 1; // Do not change id_tpc_timeref. (0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
  // because calibration parameters (for y) are valid only with timeref used during calibration.
  // if you want to change timeref, you need to calibrate y-position  again ! )
  tpc->x_offset[0][0] = -0.408463 +0.2 -3.0+3.4 -1.0+1.7 - 1.3-0.5908 -0.238-0.172;//SKS, ER 9.05.25
  tpc->x_factor[0][0] = 0.007978*1.0096;	//Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->x_offset[0][1] = 0.959454  +0.2 -3.0+3.4 -1.0+1.7 - 1.3-0.5908-0.238-0.172;//SKS, ER 9.05.25
  tpc->x_factor[0][1] = 0.008105*1.0096;	//Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->y_offset[0][0] = -56.3389688 +0.85 +0.5+21.67 +2.6658 -23.6 -3.05;//SKS ER 09.05.2025
  tpc->y_factor[0][0] = 0.0038418; //0.003956; //vacuum tpc is drift to bottom. positive y-factor
  tpc->y_offset[0][1] =-56.9720263 +0.85+0.5+21.67 +2.6658-23.6 -3.05;//SKS ER 09.05.2025;
  tpc->y_factor[0][1] = 0.0038732;//0.003953;
  tpc->y_offset[0][2] = -57.2758022 +0.85+0.5+21.67+2.6658-23.6 -3.05;//SKS ER 09.05.2025
  tpc->y_factor[0][2] = 0.0038965;//0.004082;
  tpc->y_offset[0][3] = -57.7001232 +0.85+0.5+21.67+2.6658-23.6 -3.05;//SKS ER 09.05.2025
  tpc->y_factor[0][3] = 0.0039169;//0.003934;

  // TPC21 gate conditions:  After changing cut limits => Launch analysis again in Go4GUI
  tpc->lim_dt[0][0][0] = 5000.;  tpc->lim_dt[0][0][1] = 50000.0; //A11 drift time TDC cut
  tpc->lim_dt[0][1][0] = 5000.;  tpc->lim_dt[0][1][1] = 50000.0; //A12 drift time TDC cut
  tpc->lim_dt[0][2][0] = 5000.;  tpc->lim_dt[0][2][1] = 50000.0; //A21 drift time TDC cut
  tpc->lim_dt[0][3][0] = 5000.;  tpc->lim_dt[0][3][1] = 50000.0; //A22 drift time TDC cut
  tpc->lim_lt[0][0][0] = 5000.;  tpc->lim_lt[0][0][1] = 50000.0; //DL1 time TDC cut`
  tpc->lim_rt[0][0][0] = 5000.;  tpc->lim_rt[0][0][1] = 50000.0; //DR1 time TDC cut
  tpc->lim_lt[0][1][0] = 5000.;  tpc->lim_lt[0][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_rt[0][1][0] = 5000.;  tpc->lim_rt[0][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_csum1[0][0] = 13700.0 - 200.;  tpc->lim_csum1[0][1] = 14600.0;
  tpc->lim_csum2[0][0] = 13900.0 - 200.;  tpc->lim_csum2[0][1] = 14600.0;
  tpc->lim_csum3[0][0] = 13500.0 - 200.;  tpc->lim_csum3[0][1] = 14600.0 - 100.;
  tpc->lim_csum4[0][0] = 13500.0 - 200.;  tpc->lim_csum4[0][1] = 14600.0 - 100.;


  //-------- TPC22 parameters after Repair in May 2021 (updated on // 19/June/2021, BARB june 2021) ----------
  // TPC22 at S2 in vacuum
  //
  tpc->id_tpc_timeref[1] = 1; // Do not change id_tpc_timeref. (0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
  // because calibration parameters (y) are valid only with timeref used during calibration.
  // if you want to change timeref, you need to calibrate y-position  again ! )
  tpc->x_offset[1][0] = 2.483279 +0.7 -0.5 -0.6+1.7-1.549 +0.0625-0.238+0.534;//SKS, ER 9.05.25
  tpc->x_factor[1][0] = 0.007781*1.0105;	//Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->x_offset[1][1] = 0.561674 +0.7 -0.5-0.6+1.7-1.549 +0.0625-0.238+0.534;//SKS, ER 9.05.25
  tpc->x_factor[1][1] = 0.007574*1.0105;	//Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->y_offset[1][0] = -58.1084677+0.6+0.2+21.67 +3.138-23.6 -0.297;//SKS ER 09.05.2025
  tpc->y_factor[1][0] = 0.0039634;//0.004107;   //vacuum tpc is drift to bottom. positive y-factor
  tpc->y_offset[1][1] = -58.7300878+0.6+0.2+21.67+3.138-23.6 -0.297;//SKS ER 09.05.2025
  tpc->y_factor[1][1] = 0.0039666;//0.004016;
  tpc->y_offset[1][2] = -59.094806+0.6+0.2+21.67+3.138-23.6 -0.297;//SKS ER 09.05.2025
  tpc->y_factor[1][2] = 0.0039668;//0.004024;
  tpc->y_offset[1][3] = -58.5754908+0.6+0.2+21.67+3.138-23.6 -0.297;//SKS ER 09.05.2025
  tpc->y_factor[1][3] = 0.0039793;//0.004046;
  // TPC22 gate condition... After changing cut limits => Launch analysis again in Go4GUI
  tpc->lim_dt[1][0][0] = 5000.;  tpc->lim_dt[1][0][1] = 50000.0; //A11 drift time TDC cut
  tpc->lim_dt[1][1][0] = 5000.;  tpc->lim_dt[1][1][1] = 50000.0; //A12 drift time TDC cut
  tpc->lim_dt[1][2][0] = 5000.;  tpc->lim_dt[1][2][1] = 50000.0; //A21 drift time TDC cut
  tpc->lim_dt[1][3][0] = 5000.;  tpc->lim_dt[1][3][1] = 50000.0; //A22 drift time TDC cut
  tpc->lim_lt[1][0][0] = 5000.;  tpc->lim_lt[1][0][1] = 50000.0; //DL1 time TDC cut
  tpc->lim_rt[1][0][0] = 5000.;  tpc->lim_rt[1][0][1] = 50000.0; //DR1 time TDC cut
  tpc->lim_lt[1][1][0] = 5000.;  tpc->lim_lt[1][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_rt[1][1][0] = 5000.;  tpc->lim_rt[1][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_csum1[1][0] = 17000.0 + 500.;    tpc->lim_csum1[1][1] =  19200.0 - 200.;
  tpc->lim_csum2[1][0] = 17000.0;    tpc->lim_csum2[1][1] =  19200.0;
  tpc->lim_csum3[1][0] = 17000.0 + 500.;    tpc->lim_csum3[1][1] =  19200.0 - 200.;
  tpc->lim_csum4[1][0] = 17000.0 + 500.;    tpc->lim_csum4[1][1] =  19200.0 + 200.;


  //-------- TPC23 parameters  (updated on 2021/May31, begeinnig of S526, timeref=2, U beam)--------------
  // TPC23 at S2 in air
  //
  tpc->id_tpc_timeref[2] = 1;// Do not change id_tpc_timeref. (0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
  // because calibration parameters (y) are valid only with timeref used during calibration.
  // if you want to change timeref, you need to calibrate y-position  again ! )
  tpc->x_offset[2][0] = 4.389925 +1.5-1.5+1.6-0.57-0.6+1.0-3.0-6.2+5.8+0.3-0.1874-0.2187-0.446 +0.57-0.541; //ER SKS 09.05.2025
  tpc->x_factor[2][0] = 0.008002*1.0127;	//Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->x_offset[2][1] = -0.136026 +1.5-1.5+1.6-0.57-0.6+1.0-3.0-6.2+5.8+0.3-0.1874-0.2187-0.446+0.57-0.541; //ER SKS 09.05.2025
  tpc->x_factor[2][1] = 0.007852*1.0127;	//Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->y_offset[2][0] = 48.588674+7.5+(2.286-7.958)-0.8+2.2-21.83-2.811 + 20.68+2.32 +0.598; //ER SKS 09.05.2025
  tpc->y_factor[2][0] = -0.004231; //air tpc is drift to top. negative y-factor
  tpc->y_offset[2][1] = 48.726112+7.5+(2.286-7.958)-0.8+2.2-21.83-2.811+20.68+2.32 +0.598; //ER SKS 09.05.2025
  tpc->y_factor[2][1] = -0.004244;
  tpc->y_offset[2][2] = 48.746238+7.5+(2.286-7.958)-0.8+2.2-21.83-2.811+20.68+2.32+0.598; //ER SKS 09.05.2025
  tpc->y_factor[2][2] = -0.004246;
  tpc->y_offset[2][3] = 48.308878+7.5+(2.286-7.958)-0.8+2.2-21.83-2.811+20.68+2.32+0.598; //ER SKS 09.05.2025
  tpc->y_factor[2][3] = -0.004220;

  // TPC23 gate conditions:  After changing cut limits => Launch analysis again in Go4GUI
  tpc->lim_dt[2][0][0] = 15000.;  tpc->lim_dt[2][0][1] = 25000.0; //A11 drift time TDC cut
  tpc->lim_dt[2][1][0] = 15000.;  tpc->lim_dt[2][1][1] = 25000.0; //A12 drift time TDC cut
  tpc->lim_dt[2][2][0] = 15000.;  tpc->lim_dt[2][2][1] = 25000.0; //A21 drift time TDC cut
  tpc->lim_dt[2][3][0] = 15000.;  tpc->lim_dt[2][3][1] = 25000.0; //A22 drift time TDC cut
  tpc->lim_lt[2][0][0] = 10000.;  tpc->lim_lt[2][0][1] = 40000.0; //DL1 time TDC cut
  tpc->lim_rt[2][0][0] = 10000.;  tpc->lim_rt[2][0][1] = 40000.0; //DR1 time TDC cut
  tpc->lim_lt[2][1][0] = 10000.;  tpc->lim_lt[2][1][1] = 40000.0; //DL2 time TDC cut
  tpc->lim_rt[2][1][0] = 10000.;  tpc->lim_rt[2][1][1] = 40000.0; //DL2 time TDC cut
  tpc->lim_csum1[2][0] = 13800.0 -100.;   tpc->lim_csum1[2][1] = 14800.0 -100.; //, 15:00 2022-May-12
  tpc->lim_csum2[2][0] = 14000.0 -100.;   tpc->lim_csum2[2][1] = 14800.0 -100.;//, 15:00 2022-May-12
  tpc->lim_csum3[2][0] = 14000.0 -100.;   tpc->lim_csum3[2][1] = 14800.0;//, 15:00 2022-May-12
  tpc->lim_csum4[2][0] = 14000.0 -100.;   tpc->lim_csum4[2][1] = 14800.0; //, 15:00 2022-May-12


  //-------- TPC24 parameters  ------- (updated on 2021/May31, begeinnig of S526, timeref=2, U beam)--------------
  // TPC24 at S2 in air
  //
  tpc->id_tpc_timeref[3] = 1;// Do not change id_tpc_timeref. (0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
  // because calibration parameters (for y) are valid only with timeref used during calibration.
  // if you want to change timeref, you need to calibrate y-position  again ! )
  tpc->x_offset[3][0] = 3.539890 -0.6-14.0+14.0-0.57+1.0-0.25-6.2+5.6-0.2482+1.085-0.446+0.63 +0.180; //ER SKS 09.05.2025
  tpc->x_factor[3][0] = 0.008047*1.0127;	//Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->x_offset[3][1] = 2.242643 -0.6-14.0+14.0-0.57+1.0-0.25-6.2+5.6-0.2482+1.085-0.446+0.63+0.180; //ER SKS 09.05.2025
  tpc->x_factor[3][1] = 0.007796*1.0127;	//Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->y_offset[3][0] = 63.4310738-1.3-0.5-22.43-2.196+20.68+4.18-0.301; //ER SKS 09.05.2025
  tpc->y_factor[3][0] = -0.0040971;//-0.004033; //air tpc is drift to top. negative y-factor
  tpc->y_offset[3][1] = 63.8444714-1.3-0.5-22.43-2.196+20.68+4.18-0.301; //ER SKS 09.05.2025
  tpc->y_factor[3][1] = -0.0040887;//-0.004044;
  tpc->y_offset[3][2] = 62.8678718-1.3-0.5-22.43-2.196+20.68+4.18-0.301; //ER SKS 09.05.2025
  tpc->y_factor[3][2] = -0.0040725;//-0.004039;
  tpc->y_offset[3][3] = 62.9917085-1.3-0.5-22.43-2.196+20.68+4.18-0.301; //ER SKS 09.05.2025
  tpc->y_factor[3][3] = -0.0040386;//-0.004029;

  // TPC24 gate conditions:  After changing cut limits => Launch analysis again in Go4GUI
  tpc->lim_dt[3][0][0] = 15000.;  tpc->lim_dt[3][0][1] = 30000.0; //A11 drift time TDC cut
  tpc->lim_dt[3][1][0] = 15000.;  tpc->lim_dt[3][1][1] = 30000.0; //A12 drift time TDC cut
  tpc->lim_dt[3][2][0] = 15000.;  tpc->lim_dt[3][2][1] = 30000.0; //A21 drift time TDC cut
  tpc->lim_dt[3][3][0] = 15000.;  tpc->lim_dt[3][3][1] = 30000.0; //A22 drift time TDC cut
  tpc->lim_lt[3][0][0] = 15000.;  tpc->lim_lt[3][0][1] = 50000.0; //DL1 time TDC cut
  tpc->lim_rt[3][0][0] = 15000.;  tpc->lim_rt[3][0][1] = 50000.0; //DR1 time TDC cut
  tpc->lim_lt[3][1][0] = 15000.;  tpc->lim_lt[3][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_rt[3][1][0] = 15000.;  tpc->lim_rt[3][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_csum1[3][0] = 18100.0 -400.;    tpc->lim_csum1[3][1] = 18800.0+0.;
  tpc->lim_csum2[3][0] = 17900.0 -400.;    tpc->lim_csum2[3][1] = 18700.0+0.; ////, 15:00 2022-May-12
  tpc->lim_csum3[3][0] = 18600.0 -400.;    tpc->lim_csum3[3][1] = 19400.0+0.; ////, 15:00 2022-May-12
  tpc->lim_csum4[3][0] = 18200.0 -400.;    tpc->lim_csum4[3][1] = 19000.0+0.; ////, 15:00 2022-May-12


  //-------- TPC41 parameters  (updated on // 19/June/2021, BARB june 2021) -------
  // TPC41 at S4 in air
  //
  tpc->id_tpc_timeref[4] = 4; // Do not change id_tpc_timeref. (0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
  // because calibration parameters (for y) are valid only with timeref used during calibration.
  // if you want to change timeref, you need to calibrate y-position  again ! )
  tpc->x_offset[4][0] = -0.657524+2.0 +1.8-3.8-0.25+1.5-1.1+0.2-0.4+0.4156+0.1+0.4;// 19/June/2021, +1.5 Dec.02 2023 // Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->x_factor[4][0] = 0.007779*12./11.*0.9338; // Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->x_offset[4][1] = -1.806150+2.0 +1.8-3.8-0.25+1.5-1.1+0.2-0.4+0.4156+0.1+0.4; // 19/June/2021//trust more final grid in front of IC, and correct for TPC41/42 // Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->x_factor[4][1] = 0.007802*12./11.*0.9338; // Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->y_offset[4][0] = 54.670698 -1.3 -0.5+0.8+0.8+1.4-0.8-1.931-0.486;// 19/June/2021
  tpc->y_factor[4][0] = -0.004075;  //air tpc is drift to top. negative y-factor
  tpc->y_offset[4][1] = 54.704890 -1.3 -0.5 +0.8+0.8+1.4-0.8-1.931-0.486;// 19/June/2021
  tpc->y_factor[4][1] = -0.004077;
  tpc->y_offset[4][2] = 55.482351 -1.3 -0.5+0.8+0.8+1.4-0.8-1.931-0.486;// 19/June/2021
  tpc->y_factor[4][2] = -0.004049;
  tpc->y_offset[4][3] = 55.628042 -1.3 -0.5+0.8+0.8+1.4-0.8-1.931-0.486;// 19/June/2021
  tpc->y_factor[4][3] = -0.004074;
  // TPC41 gate conditions: After changing cut limits => Launch analysis again in Go4GUI
  tpc->lim_dt[4][0][0] = 5000.;  tpc->lim_dt[4][0][1] = 50000.0; //A11 drift time TDC cut
  tpc->lim_dt[4][1][0] = 5000.;  tpc->lim_dt[4][1][1] = 50000.0; //A12 drift time TDC cut
  tpc->lim_dt[4][2][0] = 5000.;  tpc->lim_dt[4][2][1] = 50000.0; //A21 drift time TDC cut
  tpc->lim_dt[4][3][0] = 5000.;  tpc->lim_dt[4][3][1] = 50000.0; //A22 drift time TDC cut
  tpc->lim_lt[4][0][0] = 5000.;  tpc->lim_lt[4][0][1] = 50000.0; //DL1 time TDC cut
  tpc->lim_rt[4][0][0] = 5000.;  tpc->lim_rt[4][0][1] = 50000.0; //DR1 time TDC cut
  tpc->lim_lt[4][1][0] = 5000.;  tpc->lim_lt[4][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_rt[4][1][0] = 5000.;  tpc->lim_rt[4][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_csum1[4][0] = 13400.0;    tpc->lim_csum1[4][1] = 14900.0;
  tpc->lim_csum2[4][0] = 13600.0;    tpc->lim_csum2[4][1] = 14650.0;
  tpc->lim_csum3[4][0] = 13650.0;    tpc->lim_csum3[4][1] = 14600.0;
  tpc->lim_csum4[4][0] = 13750.0;    tpc->lim_csum4[4][1] = 14700.0;


  //-------- TPC42 parameters (updated on // 19/June/2021, BARB june 2021)
  // TPC42 at S4 in air
  tpc->id_tpc_timeref[5] = 4; // Do not change id_tpc_timeref. (0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
  // because calibration parameters (y) are valid only with timeref used during calibration.
  // if you want to change timeref, you need to calibrate y-position again ! )
  tpc->x_offset[5][0] = 2.821206-2.0 +8.0 -1.8-4.5-0.2-1.5+1.2+0.41-0.1+0.8; // Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->x_factor[5][0] = 0.007828*24./23.*0.9917; // Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->x_offset[5][1] = 1.989353-2.0 +8.0 -1.8-4.5-0.2-1.5+1.2+0.41-0.1+0.8; // Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->x_factor[5][1] = 0.007999*24./23.*0.9917; // Updated 10/02/2025 J.E. E.H. D.J.M.
  tpc->y_offset[5][0] = 55.137927 +1.3 +0.5-0.8-1.1+1.1-0.7-2.206+2.7;// 19/June/2021
  tpc->y_factor[5][0] = -0.004056; //air tpc is drift to top. negative y-factor
  tpc->y_offset[5][1] = 55.897006 +1.3 +0.5-0.8-1.1+1.1-0.7-2.206+2.7;// 19/June/2021
  tpc->y_factor[5][1] = -0.004060;
  tpc->y_offset[5][2] = 54.034448 +1.3 +0.5-0.8-1.1+1.1-0.7-2.206+2.7;// 19/June/2021
  tpc->y_factor[5][2] = -0.004039;
  tpc->y_offset[5][3] = 53.536067 +1.3 +0.5-0.8-1.1+1.1-0.7-2.206+2.7;// 19/June/2021
  tpc->y_factor[5][3] = -0.004036;
  // TPC42 gate conditions:  After changing cut limits => Launch analysis again in Go4GUI
  tpc->lim_dt[5][0][0] = 5000.;  tpc->lim_dt[5][0][1] = 50000.0; //A11 drift time TDC cut
  tpc->lim_dt[5][1][0] = 5000.;  tpc->lim_dt[5][1][1] = 50000.0; //A12 drift time TDC cut
  tpc->lim_dt[5][2][0] = 5000.;  tpc->lim_dt[5][2][1] = 50000.0; //A21 drift time TDC cut
  tpc->lim_dt[5][3][0] = 5000.;  tpc->lim_dt[5][3][1] = 50000.0; //A22 drift time TDC cut
  tpc->lim_lt[5][0][0] = 5000.;  tpc->lim_lt[5][0][1] = 50000.0; //DL1 time TDC cut
  tpc->lim_rt[5][0][0] = 5000.;  tpc->lim_rt[5][0][1] = 50000.0; //DR1 time TDC cut
  tpc->lim_lt[5][1][0] = 5000.;  tpc->lim_lt[5][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_rt[5][1][0] = 5000.;  tpc->lim_rt[5][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_csum1[5][0] = 14200.0;    tpc->lim_csum1[5][1] = 14900.0;
  tpc->lim_csum2[5][0] = 13900.0;    tpc->lim_csum2[5][1] = 14500.0;
  tpc->lim_csum3[5][0] = 13400.0;    tpc->lim_csum3[5][1] = 14150.0;
  tpc->lim_csum4[5][0] = 13500.0;    tpc->lim_csum4[5][1] = 14250.0;


  //TPC at S3 (TPC 31) calibration updated on 19/June/2021
   tpc->id_tpc_timeref[6] = 3; //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
  tpc->x_offset[6][0] = -1.37;
  tpc->x_offset[6][1] = -3.30;
  tpc->x_factor[6][0] = 0.007981;
  tpc->x_factor[6][1] = 0.007888;
  tpc->y_offset[6][0] = -55.2-1.3;//Dec11/2023  y parameters were deduced from SC31 edge
  tpc->y_offset[6][1] = -57.3-1.3;//Dec11/2023  y in go4 follows y of S3 chamber (sc31 laddeer)
  tpc->y_offset[6][2] = -54.0-1.3;//Dec11/2023
  tpc->y_offset[6][3] = -53.7-1.3;//Dec11/2023
  tpc->y_factor[6][0] = 0.004*45./44.;
  tpc->y_factor[6][1] = 0.004*45./44.;
  tpc->y_factor[6][2] = 0.004*45./44;
  tpc->y_factor[6][3] = 0.004*45./44;
  tpc->lim_dt[6][0][0] = 5000.;  tpc->lim_dt[6][0][1] = 50000.0; //A11 drift time TDC cut
  tpc->lim_dt[6][1][0] = 5000.;  tpc->lim_dt[6][1][1] = 50000.0; //A12 drift time TDC cut
  tpc->lim_dt[6][2][0] = 5000.;  tpc->lim_dt[6][2][1] = 50000.0; //A21 drift time TDC cut
  tpc->lim_dt[6][3][0] = 5000.;  tpc->lim_dt[6][3][1] = 50000.0; //A22 drift time TDC cut
  tpc->lim_lt[6][0][0] = 5000.;  tpc->lim_lt[6][0][1] = 50000.0; //DL1 time TDC cut
  tpc->lim_rt[6][0][0] = 5000.;  tpc->lim_rt[6][0][1] = 50000.0; //DR1 time TDC cut
  tpc->lim_lt[6][1][0] = 5000.;  tpc->lim_lt[6][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_rt[6][1][0] = 5000.;  tpc->lim_rt[6][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_csum1[6][0] = 11250.0;    tpc->lim_csum1[6][1] = 13500.0;
  tpc->lim_csum2[6][0] = 10600.0;    tpc->lim_csum2[6][1] = 12400.0;
  tpc->lim_csum3[6][0] = 12500.0;    tpc->lim_csum3[6][1] = 14200.0;
  tpc->lim_csum4[6][0] = 12500.0;    tpc->lim_csum4[6][1] = 14000.0;

  //TPC21 ADC pedestal
  tpc->a_offset[0][0] = 999.;
  tpc->a_offset[0][1] = 999.;
  tpc->a_offset[0][2] = 999.;
  tpc->a_offset[0][3] = 999.;
  //TPC22 ADC pedestal
  tpc->a_offset[1][0] = 999.;
  tpc->a_offset[1][1] = 999.;
  tpc->a_offset[1][2] = 999.;
  tpc->a_offset[1][3] = 999.;
  //TPC23 ADC pedestal
  tpc->a_offset[2][0] = 104.; //set large number to exclude (pedestal data) of this tpc
  tpc->a_offset[2][1] = 107.;
  tpc->a_offset[2][2] = 106.;
  tpc->a_offset[2][3] =  91.;
  //TPC24 ADC pedestal
  tpc->a_offset[3][0] = 107.;
  tpc->a_offset[3][1] = 117.;
  tpc->a_offset[3][2] = 123.;
  tpc->a_offset[3][3] =  81.;

  // TPC@S2->Z estimation, velocity correction (TAC)
  id->vel_a_s2tpc[0] =  1400.;// TPC-A was not measured during tof calib.
  id->vel_a_s2tpc[1] =  0.0;// now we estimate from ATIMA. and then
  id->vel_a_s2tpc[2] =  0.0;// translate parameters to fit go4 parametes. (YT)
  id->vel_a_s2tpc[3] =  0.0;
  id->offset_z_s2tpc =  0.0;

  //===========
  // Plastics
  //===========
  //TOF_SC41_SC21_TAC 09.12.23 U engrun, beta 0.800 to 0.866, 3 points
 // id->id_tofoff2 =  199353; //197454.8;  // offset (ps)
 // id->id_path2   =  122663; //122486.0;  // path/c (ps)

//SC11 options
  sci->sci11_select = 0;    // a=0, b=1, c=2, d=3;    //Variable also used for id->sc11_select at line 852
  
//TOF_SC11_SC22 (Not actually in TAC) (estimated from pulser data)
  id->id_tofoff0[0] =  100000+72500;        // sc11a-sc22 offset (ps)
  id->id_tofoff0[1] =  100000+72500+28000;  // sc11b-sc22 offset (ps)
  id->id_tofoff0[2] =  100000+72500+28000;  // sc11c-sc22 offset (ps)
  id->id_tofoff0[3] =  100000+72500-31000;  // sc11d-sc22 offset (ps)
  id->id_path0   =  1000*id->mhtdc_length_sc1122/0.299792458;  // path/c (ps)

//TOF_SC11_SC21_TAC (estimated from pulser data)
  id->id_tofoff1[0] =  100000-17175;  // sc11a-sc21 offset (ps)  //averaged offset from 2 energy points 08.02.25
  id->id_tofoff1[1] =  100000+28000;  // sc11b-sc21 offset (ps)
  id->id_tofoff1[2] =  100000+28000;  // sc11c-sc21 offset (ps)
  id->id_tofoff1[3] =  100000-31000;  // sc11d-sc21 offset (ps)
  id->id_path1   =  1000*id->mhtdc_length_sc1121/0.299792458;  // path/c (ps)

//TOF_SC41_SC21_TAC 21.03.24 Au engrun,
  id->id_tofoff2 =  210321.123552;  //updated on 02/04/2025 offset (ps)
  id->id_path2   =  124427.470333;//updated on 02/04/2025 path/c (ps)

  //TOF_SC42_SC21_TAC 21.03.24 Au engrun //09.12.23 U engrun
  id->id_tofoff3  = 186504.0;//200808.;//157092; //201945; // 196914.0;   // offset (ps)
  id->id_path3    = 123571.0; //125647.;//84169; // 123401; // 125574.9;   // path/c [ps

  // TOF calibration SC21-SC81 (TAC)
  id->id_tofoff4  = 326337.1;   //SC21-81 [ps]          // quickly done from run156 and 166 (2019/Nov, YT)
  id->id_path4    = 246983.1;   //SC21-81  path/c [ps]  // quickly done from run156 and 166 (2019/Nov, YT)

  //TOF_SC41_SC22_TAC 21.03.24 Au engrun //09.12.23 U engrun
  id->id_tofoff5 = 201361.0; //202225.;//190750.8;//254767; //178527; // 187952.5;  // offset (ps)
  id->id_path5   = 119129.0; //127448.;//120604.0;//160518; //121304; //117471.1;  // path/c (ps)

  // TOF calibration SC21-SC81 (TAC)
  id->id_tofoff6  = 405709.2;   //SC22-81 [ps]          // 21feb2020 DK, YT
  id->id_path6    = 278586.5;   //SC22-81  path/c [ps]  // 21feb2020 DK, YT

  //SC11 X from dE:  sc11_dE_X_factor * ln(dE_r/dE_l) + sc11_dE_X_offset
  //indices 0 = sc11 a, 1 = sc11 b, etc.
  //offset should theoretically be 0, factor should theoretically be 0.5*attenuation of light in the scintillator
  sci->sc11_dE_X_factor[0] = 1.0;
  sci->sc11_dE_X_factor[1] = 1.0;
  sci->sc11_dE_X_factor[2] = 1.0;
  sci->sc11_dE_X_factor[3] = 1.0;
  sci->sc11_dE_X_offset[0] = 0.0; 
  sci->sc11_dE_X_offset[1] = 0.0;
  sci->sc11_dE_X_offset[2] = 0.0;
  sci->sc11_dE_X_offset[3] = 0.0;

  
  //index 1 for Sc11
  sci->x_a[0][1] =  120; //0.0;  //made up to check x histograms fill properly
  sci->x_a[1][1] =  -0.295; //1.0;  // made up to check x histograms fill properly
  sci->x_a[2][1] =  0.000000;  //
  sci->x_a[3][1] =  0.000000;  //
  sci->x_a[4][1] =  0.000000;  //
  sci->x_a[5][1] =  0.000000;  //
  sci->x_a[6][1] =  0.000000;  //
  sci->le_a[0][1] = 0.0;
  sci->re_a[0][1] = 0.0;

  //index 2 for Sc21
  sci->x_a[0][2] =    614.025;  // UPDATED 12/02/2025 Exp. 056 107Ag
  sci->x_a[1][2] =   -0.295448;	// UPDATED 12/02/2025 Exp. 056 107Ag
  sci->x_a[2][2] =  0.000000;  //
  sci->x_a[3][2] =  0.000000;  //
  sci->x_a[4][2] =  0.000000;  //
  sci->x_a[5][2] =  0.000000;  //
  sci->x_a[6][2] =  0.000000;  //
  sci->le_a[0][2] = 0.0;
  sci->re_a[0][2] = 0.0;

  //index 3 for Sc22
  sci->x_a[0][3] =  405.789;  // quickly done for s526 on 02.06.2021 (from online)
  sci->x_a[1][3] =  -0.254;  //quickly done for s526 on 02.06.2021 (from online)
  sci->x_a[2][3] =  0.000000;  // quickly done for s526 on 02.06.2021 (from online)
  sci->x_a[3][3] =  0.000000;  // quickly done for s526 on 02.06.2021 (from online)
  sci->x_a[4][3] =  0.000000;  //
  sci->x_a[5][3] =  0.000000;  //
  sci->x_a[6][3] =  0.000000;  //
  sci->le_a[0][3] = 0.0;
  sci->re_a[0][3] = 0.0;

  //index 4 for Sc31
  sci->x_a[0][4] =  600.0;  // SC31 calibration ch->mm
  sci->x_a[1][4] =  -0.29;  //
  sci->x_a[2][4] =  0.000000;  //
  sci->x_a[3][4] =  0.000000;  //
  sci->x_a[4][4] =  0.000000;  //
  sci->x_a[5][4] =  0.000000;  //
  sci->x_a[6][4] =  0.000000;  //
  sci->le_a[0][4] = 0.0;
  sci->re_a[0][4] = 0.0;

  // index 5 for Sc41
  sci->x_a[0][5] = 641.56;  //  quickly done for s452 on 08.03.2021 (from online)
  sci->x_a[1][5] = -0.2782;  // quickly done for s452 on 08.03.2021 (from online)
  sci->x_a[2][5] = 0.0000;   //
  sci->x_a[3][5] = 0.000000;   //
  sci->x_a[4][5] = 0.000000;   //
  sci->x_a[5][5] = 0.000000;   //
  sci->x_a[6][5] = 0.000000;   //

  // index 6 for Sc42
  sci->x_a[0][6] = 559.44;  // quickly done for s452 on 08.03.2021 (from online)
  sci->x_a[1][6] = -0.2973; // quickly done for s452 on 08.03.2021 (from online)
  sci->x_a[2][6] = 0.000000;  //
  sci->x_a[3][6] = 0.000000;  //
  sci->x_a[4][6] = 0.000000;  //
  sci->x_a[5][6] = 0.000000;  //
  sci->x_a[6][6] = 0.000000;  //

   // index 7 for Sc43
  sci->x_a[0][7] = 0.; //   SC43 calibration ch->mm
  sci->x_a[1][7] = 1.; //
  sci->x_a[2][7] = 0.000000;  //
  sci->x_a[3][7] = 0.000000;  //
  sci->x_a[4][7] = 0.000000;  //
  sci->x_a[5][7] = 0.000000;  //
  sci->x_a[6][7] = 0.000000;  //

   // index 10 for Sc81
  sci->x_a[0][10] = 707.306;   // 2020/feb/20 run0110,0111,0112.lmd
  sci->x_a[1][10] =-0.45558;   //
  sci->x_a[2][10] = 0.000000;  //
  sci->x_a[3][10] = 0.000000;  //
  sci->x_a[4][10] = 0.000000;  //
  sci->x_a[5][10] = 0.000000;  //
  sci->x_a[6][10] = 0.000000;  //
  sci->le_a[0][10] = 310.0; //21/feb/2020
  sci->re_a[0][10] = 123.0;

  // index 12 for ScM01
  sci->le_a[0][12] = 0.0; //sci_e = sqrt( (sci_l - sci->le_a[0]) * sci->le_a[1]* (sci_r - sci->re_a[0]) * sci->re_a[1]);
  sci->re_a[0][12] = 0.0;
  sci->le_a[1][12] = 1.0;
  sci->re_a[1][12] = 1.0;

  // SC81->Z estimation, velocity correction (TAC)
  id->vel_a_sc81[0] =   2156.4;// SC81 dE was not propery measured.
  id->vel_a_sc81[1] =  -1470.4;// I skip to set these parameters
  id->vel_a_sc81[2] =   0.0;// this time ...
  id->vel_a_sc81[3] =   0.0;
  id->offset_z_sc81 =   0.0;

  // For TAC calibration, please only set "factor".
  // To put some "magic number" offset is very confusing!!
  // TOF calibration should be done via setting id->id_tofoff2(3)(4)
  sci->tac_off[0] = 0.0;  //SC21L-R    // fix to 0
  sci->tac_off[1] = 0.0;  //SC41L-R    // fix to 0
  sci->tac_off[2] = 0.0;  //SC41L-SC21L   // fix to 0
  sci->tac_off[3] = 0.0;  //SC41R-SC21R   // fix to 0
  sci->tac_off[4] = 0.0;  //SC42L-R       // fix to 0
  sci->tac_off[5] = 0.0;  //SC42L-SC21L   // fix to 0
  sci->tac_off[6] = 0.0;  //SC42R-SC21R   // fix to 0
  sci->tac_off[7] = 0.0;  //SC43L-R  // fix to 0
  sci->tac_off[8] = 0.0;  //SC81L-R  // fix to 0 // BORROWED FOR SC11
  sci->tac_off[9] = 0.0;  //SC81L-SC21L  // fix to 0  // BORROWED FOR SC11
  sci->tac_off[10]= 0.0;  //SC81R-SC21R  // fix to 0  // BORROWED FOR SC11
  sci->tac_off[11] = 0.0;  //SC22L-R  // fix to 0
  sci->tac_off[12] = 0.0;  //SC41L-SC22L  // fix to 0
  sci->tac_off[13] = 0.0;  //SC41R-SC22R  // fix to 0
  sci->tac_off[14]= 0.0;  //SC81L-SC22L  // fix to 0
  sci->tac_off[15]= 0.0;  //SC81R-SC22R  // fix to 0

  //2021/Feb/BARB
  sci->tac_factor[0]  = 10.5293; //SC21L-R [ps/ch]     >> ch0 of ADC
  sci->tac_factor[1]  = 10.6934; //SC41L-R [ps/ch]     >> ch1 of ADC
  sci->tac_factor[4]  = 10.5367; //SC42L-R             >> ch2 of ADC
  sci->tac_factor[7]  = 11.0166; //SC43L-R [ps/ch]     >> ch3 of ADC
  sci->tac_factor[11] = 10.5536; //SC22L-R             >> ch11
  sci->tac_factor[14] = 20.0000; //SC81L-SC22L [ps/ch] >> ch14
  sci->tac_factor[15] = 20.0000; //SC81R-SC22R [ps/ch] >> ch15

    //s450, tac range 85ns 06.May.2022
  sci->tac_factor[2]  = 18.829; //SC41L-SC21L [ps/ch] >> ch5 of ADC
  sci->tac_factor[3]  = 18.529; //SC41R-SC21R [ps/ch] >> ch6 of ADC
  sci->tac_factor[12] = 17.170; //SC41L-SC22L [ps/ch] >> ch12
  sci->tac_factor[13] = 18.176; //SC41R-SC22R [ps/ch] >> ch13
  sci->tac_factor[5]  = 18.294; //SC42L-SC21L [ps/ch] >> ch8 of ADC
  sci->tac_factor[6]  = 18.083; //SC42R-SC21R [ps/ch] >> ch7 of ADC

  //S455 15.03.21
  /*
  sci->tac_factor[8]  = 10.51; //SC81L-R [ps/ch]     >> ch4 of ADC
  sci->tac_factor[9]  = 20.84; //SC81L-SC21L 100ns range        >> ch9          //10.27 for 50ns range
  sci->tac_factor[10] = 20.79; //SC81R-SC21R 100ns range        >> ch10         //10.49 for 50ns range
  */

  /*
   * BORROWING SC81 PARAMETERS FOR SC11
   */
  sci->tac_factor[8]  = 10.51; //SC81L-R [ps/ch]     >> ch4 of ADC
  sci->tac_factor[9]  = 20.84; //SC11L-SC21L //SC81L-SC21L 100ns range        >> ch9          //10.27 for 50ns range
  sci->tac_factor[10] = 20.79; //SC11R-SC21R //SC81R-SC21R 100ns range        >> ch10         //10.49 for 50ns range
  
  sci->tof_bll0  = 1.;
  sci->tof_brr0  = 1.; 
  sci->tof_bll1  = 1.;    // not used online [ps/ch]
  sci->tof_bll2  = 1.;    // not used online
  sci->tof_brr2  = 1.;    // not used online
  sci->tof_bll3  = 1.;    // not used online
  sci->tof_brr3  = 1.;    // not used online
  sci->tof_bll4  = 1.;    // not used online
  sci->tof_brr4  = 1.;    // not used online

  sci->tof_a1 = 0; // [ps] offset   Tof S21-S11 - not needed - just set id_tofoff1
  sci->tof_a2 = 0.0; //146.46; // [ps] offset   Tof S41-S21
  sci->tof_a3 = 0.; // [ps] offset   Tof S42-S21
  sci->tof_a4 = 0.; // [ps] offset   Tof S81-S21

   // for multihitTDC

  /*
   * SCI11 [0,1,2,3] = [a,b,c,d]
   */
//  sci->mhtdc_offset_21_11[0] = 142.5-16.35;//estimated from pulser data //roughly calibrated 08.02.25
  sci->mhtdc_offset_21_11[0] = 142.5 - 16.35 + 1.093576878 - 5.2343; //142.5 - 16.35 + 1.093576878 - 5.2343; //142.5-16.35+1.093576878 - 2.2343; //correction added online, 2025/May/09
  sci->mhtdc_offset_21_11[1] = 142.5-28;//estimated from pulser data and delays seen on scope
  sci->mhtdc_offset_21_11[2] = 142.5-28;
  sci->mhtdc_offset_21_11[3] = 142.5+31;

//  sci->mhtdc_offset_22_11[0] = 70.0;//estimated from pulser data and other offsets
  sci->mhtdc_offset_22_11[0] = 70.0-2.636925587; //correction added online, 2025/Feb/27 (YT)
  sci->mhtdc_offset_22_11[1] = 70.0-28;
  sci->mhtdc_offset_22_11[2] = 70.0-28;
  sci->mhtdc_offset_22_11[3] = 70.0+31;

// pos = offset + factor*dts
  sci->mhtdc_factor_ch_to_ns =  0.025;// tp be set in parameter...
  sci->mhtdc_offset_11l_11r  =  55.1177 +10.3;//correction added online, 2025/Feb/27 (YT)
  sci->mhtdc_factor_11l_11r  =  39.6434;  // from LISE++
  sci->mhtdc_offset_21l_21r  =  -39.6625+20.0 -48.0;//-39.6625+20.0 -48.0; //-48 is added for 2021JuneBARB file 230
  sci->mhtdc_factor_21l_21r  =  62.5341;  // pos = offset + factor*dt
  sci->mhtdc_offset_41l_41r  =  584.927;          sci->mhtdc_factor_41l_41r = 69.4128; // pos = offset + factor*dt
  sci->mhtdc_offset_42l_42r  =  0.0;              sci->mhtdc_factor_42l_42r = 60.0; // pos = offset + factor*dt
  sci->mhtdc_offset_43l_43r  =  0.0;              sci->mhtdc_factor_43l_43r = 60.0; // pos = offset + factor*dt
  sci->mhtdc_offset_31l_31r  =  910.7 + 17.9;             sci->mhtdc_factor_31l_31r = 60.0; // pos = offset + factor*dt
  sci->mhtdc_offset_81l_81r  =  -410.411;         sci->mhtdc_factor_81l_81r = 43.691; // pos = offset + factor*dt
  sci->mhtdc_offset_22l_22r  =  -39.6625+20.0;    sci->mhtdc_factor_22l_22r = 62.5341;  // pos = offset + factor*dt
  sci->mhtdc_offset_M01l_M01r  =  338.677 + 650 + 14.0;    sci->mhtdc_factor_M01l_M01r = 52.6692; //rough guess with scattered particles
  //  sci->mhtdc_offset_41_21  =  178.95;//Updated 10/02/2025 //-8.8+19.2661-9.95+171.4 +0.7 -0.2-4.1+10.79; //ns //s450 208Pb
  //  sci->mhtdc_offset_42_21  =  183.16;//Updated 10/02/2025  //171.5+13.1+7.0754; //ns // to be checked
  sci->mhtdc_offset_43_21  =  0.0; //ns
  sci->mhtdc_offset_31_21  =  85.0; //ns
  sci->mhtdc_offset_31_22  =  85.0+50.0; //ns
  sci->mhtdc_offset_81_21  =  -400.0 + 165.214; //ns
  //  sci->mhtdc_offset_41_22  =  240.33;//Updated 10/02/2025 //-44.91+203.3+96.7 +0.7-4.2+10.426; //ns //s526 107Ag it was 253.3ns
  sci->mhtdc_offset_M01_21  =  -543.38095 + (681.88795 - 628.5) - 7.552; //ns 08.09.2021
  sci->mhtdc_offset_M01_22  =  0.0; //ns
  //
  //sci->mhtdc_offset_41_21  =  178.95 -1.651279236;  //Updated 10/02/2025 //-8.8+19.2661-9.95+171.4 +0.7 -0.2-4.1+10.79; //ns //s450 208Pb
  //sci->mhtdc_offset_42_21  =  183.16 -2.625508775     ; // updated    2025/02/21
  //sci->mhtdc_offset_41_22  =  240.33 -0.5586602465 ;

  id->mhtdc_AoQ_offset_S1S2 = 0. ;
  id->mhtdc_AoQ_offset_S2S3 = 0. ; //added by XXu, 26.02.2025
  id->mhtdc_AoQ_offset_S2S4 = 0. ;

  //---- initial value for Z vs AoQ PID -----//
  id->ID_Z41_AoverQ_num[0]=5;
  id->ID_Z41_AoverQ_num[1]=5;
  id->ID_Z41_AoverQ_num[2]=5;
  id->ID_Z41_AoverQ_num[3]=5;
  id->ID_Z41_AoverQ_num[4]=5;
  
  //	88Tc
  id->ID_Z41_AoverQ[0][0][0]=2.03     ; id->ID_Z41_AoverQ[0][0][1]=42.6;
  id->ID_Z41_AoverQ[0][1][0]=2.055     ; id->ID_Z41_AoverQ[0][1][1]=42.6;
  id->ID_Z41_AoverQ[0][2][0]=2.055      ; id->ID_Z41_AoverQ[0][2][1]=43.2;
  id->ID_Z41_AoverQ[0][3][0]=2.03      ; id->ID_Z41_AoverQ[0][3][1]=43.2;
  id->ID_Z41_AoverQ[0][4][0]=2.03      ; id->ID_Z41_AoverQ[0][4][1]=42.6;

//	93Rh
//  id->ID_Z41_AoverQ[0][0][0]=1.836      ; id->ID_Z41_AoverQ[0][0][1]=47.9;
//  id->ID_Z41_AoverQ[0][1][0]=1.856     ; id->ID_Z41_AoverQ[0][1][1]=47.9;
//  id->ID_Z41_AoverQ[0][2][0]=1.856      ; id->ID_Z41_AoverQ[0][2][1]=48.6;
//  id->ID_Z41_AoverQ[0][3][0]=1.836      ; id->ID_Z41_AoverQ[0][3][1]=48.6 ;
//  id->ID_Z41_AoverQ[0][4][0]=1.836      ; id->ID_Z41_AoverQ[0][4][1]=47.9;
  
  // 94Rh
  id->ID_Z41_AoverQ[1][0][0]=1.857; id->ID_Z41_AoverQ[1][0][1]=47;
  id->ID_Z41_AoverQ[1][1][0]=1.872; id->ID_Z41_AoverQ[1][1][1]=47;
  id->ID_Z41_AoverQ[1][2][0]=1.872; id->ID_Z41_AoverQ[1][2][1]=47.8;
  id->ID_Z41_AoverQ[1][3][0]=1.857; id->ID_Z41_AoverQ[1][3][1]=47.8;
  id->ID_Z41_AoverQ[1][4][0]=1.857; id->ID_Z41_AoverQ[1][4][1]=47;

  // all below Z=32
  id->ID_Z41_AoverQ[2][0][0]=1.90; id->ID_Z41_AoverQ[2][0][1]=25.;
  id->ID_Z41_AoverQ[2][1][0]=1.90; id->ID_Z41_AoverQ[2][1][1]=31.65;
  id->ID_Z41_AoverQ[2][2][0]=2.3; id->ID_Z41_AoverQ[2][2][1]=31.65;
  id->ID_Z41_AoverQ[2][3][0]=2.3; id->ID_Z41_AoverQ[2][3][1]=25.;
  id->ID_Z41_AoverQ[2][4][0]=1.90; id->ID_Z41_AoverQ[2][4][1]=25.;

  // 81Br
  id->ID_Z41_AoverQ[3][0][0]=2.01; id->ID_Z41_AoverQ[3][0][1]=34.5;
  id->ID_Z41_AoverQ[3][1][0]=2.03; id->ID_Z41_AoverQ[3][1][1]=34.5;
  id->ID_Z41_AoverQ[3][2][0]=2.03; id->ID_Z41_AoverQ[3][2][1]=35.3;
  id->ID_Z41_AoverQ[3][3][0]=2.01; id->ID_Z41_AoverQ[3][3][1]=35.3;
  id->ID_Z41_AoverQ[3][4][0]=2.01; id->ID_Z41_AoverQ[3][4][1]=34.5;

  // Rb
  id->ID_Z41_AoverQ[4][0][0]=1.90; id->ID_Z41_AoverQ[4][0][1]=37.4;
  id->ID_Z41_AoverQ[4][1][0]=1.90; id->ID_Z41_AoverQ[4][1][1]=38.1;
  id->ID_Z41_AoverQ[4][2][0]=2.3; id->ID_Z41_AoverQ[4][2][1]=38.1;
  id->ID_Z41_AoverQ[4][3][0]=2.3; id->ID_Z41_AoverQ[4][3][1]=37.4;
  id->ID_Z41_AoverQ[4][4][0]=1.90; id->ID_Z41_AoverQ[4][4][1]=37.4;

  //---- initial value for x2 vs AoQ PID -----//
  id->ID_x2AoverQ_num[0]=5;
  id->ID_x2AoverQ_num[1]=5;
  id->ID_x2AoverQ_num[2]=5;
  id->ID_x2AoverQ_num[3]=5;
  id->ID_x2AoverQ_num[4]=5;

  id->ID_x2AoverQ[0][0][0]=2.01; id->ID_x2AoverQ[0][0][1]=43.9;
  id->ID_x2AoverQ[0][1][0]=2.03; id->ID_x2AoverQ[0][1][1]=43.9;
  id->ID_x2AoverQ[0][2][0]=2.03; id->ID_x2AoverQ[0][2][1]=42.8;
  id->ID_x2AoverQ[0][3][0]=2.01; id->ID_x2AoverQ[0][3][1]=42.8;
  id->ID_x2AoverQ[0][4][0]=2.01; id->ID_x2AoverQ[0][4][1]=43.9;

  id->ID_x2AoverQ[1][0][0]=2.27782; id->ID_x2AoverQ[1][0][1]=58.1797;
  id->ID_x2AoverQ[1][1][0]=2.18477; id->ID_x2AoverQ[1][1][1]=-66.2442;
  id->ID_x2AoverQ[1][2][0]=2.19417; id->ID_x2AoverQ[1][2][1]=-69.7005;
  id->ID_x2AoverQ[1][3][0]=2.29192; id->ID_x2AoverQ[1][3][1]=57.0277;
  id->ID_x2AoverQ[1][4][0]=2.27782; id->ID_x2AoverQ[1][4][1]=58.1797;

  id->ID_x2AoverQ[2][0][0]=2.28597; id->ID_x2AoverQ[2][0][1]=40.8986;
  id->ID_x2AoverQ[2][1][0]=2.19548; id->ID_x2AoverQ[2][1][1]=-69.1244;
  id->ID_x2AoverQ[2][2][0]=2.21129; id->ID_x2AoverQ[2][2][1]=-69.1244;
  id->ID_x2AoverQ[2][3][0]=2.30014; id->ID_x2AoverQ[2][3][1]=40.3226;
  id->ID_x2AoverQ[2][4][0]=2.28597; id->ID_x2AoverQ[2][4][1]=40.8986;

  id->ID_x2AoverQ[3][0][0]=2.30468; id->ID_x2AoverQ[3][0][1]=41.0484;
  id->ID_x2AoverQ[3][1][0]=2.20712; id->ID_x2AoverQ[3][1][1]=-73.4407;
  id->ID_x2AoverQ[3][2][0]=2.22237; id->ID_x2AoverQ[3][2][1]=-73.1567;
  id->ID_x2AoverQ[3][3][0]=2.32009; id->ID_x2AoverQ[3][3][1]=41.0484;
  id->ID_x2AoverQ[3][4][0]=2.30468; id->ID_x2AoverQ[3][4][1]=41.0484;

  id->ID_x2AoverQ[4][0][0]=2.32064; id->ID_x2AoverQ[4][0][1]=39.6964;
  id->ID_x2AoverQ[4][1][0]=2.22332; id->ID_x2AoverQ[4][1][1]=-73.875;
  id->ID_x2AoverQ[4][2][0]=2.23886; id->ID_x2AoverQ[4][2][1]=-73.517;
  id->ID_x2AoverQ[4][3][0]=2.33663; id->ID_x2AoverQ[4][3][1]=39.6964;
  id->ID_x2AoverQ[4][4][0]=2.32064; id->ID_x2AoverQ[4][4][1]=39.6964;

  //---- initial value for x4 vs AoQ PID -----//
  id->ID_x4AoverQ_num[0]=5;
  id->ID_x4AoverQ_num[1]=5;
  id->ID_x4AoverQ_num[2]=5;
  id->ID_x4AoverQ_num[3]=5;
  id->ID_x4AoverQ_num[4]=5;

  id->ID_x4AoverQ[0][0][0]=2.24433; id->ID_x4AoverQ[0][0][1]=42.5864;
  id->ID_x4AoverQ[0][1][0]=2.17429; id->ID_x4AoverQ[0][1][1]=-68.2431;
  id->ID_x4AoverQ[0][2][0]=2.18351; id->ID_x4AoverQ[0][2][1]=-70.9073;
  id->ID_x4AoverQ[0][3][0]=2.2573; id->ID_x4AoverQ[0][3][1]=40.9879;
  id->ID_x4AoverQ[0][4][0]=2.24433;id->ID_x4AoverQ[0][4][1]=42.5864;

  id->ID_x4AoverQ[1][0][0]=2.27782; id->ID_x4AoverQ[1][0][1]=58.1797;
  id->ID_x4AoverQ[1][1][0]=2.18477; id->ID_x4AoverQ[1][1][1]=-66.2442;
  id->ID_x4AoverQ[1][2][0]=2.19417; id->ID_x4AoverQ[1][2][1]=-69.7005;
  id->ID_x4AoverQ[1][3][0]=2.29192; id->ID_x4AoverQ[1][3][1]=57.0277;
  id->ID_x4AoverQ[1][4][0]=2.27782; id->ID_x4AoverQ[1][4][1]=58.1797;

  id->ID_x4AoverQ[2][0][0]=2.28597; id->ID_x4AoverQ[2][0][1]=40.8986;
  id->ID_x4AoverQ[2][1][0]=2.19548; id->ID_x4AoverQ[2][1][1]=-69.1244;
  id->ID_x4AoverQ[2][2][0]=2.21129; id->ID_x4AoverQ[2][2][1]=-69.1244;
  id->ID_x4AoverQ[2][3][0]=2.30014; id->ID_x4AoverQ[2][3][1]=40.3226;
  id->ID_x4AoverQ[2][4][0]=2.28597; id->ID_x4AoverQ[2][4][1]=40.8986;

  id->ID_x4AoverQ[3][0][0]=2.30468; id->ID_x4AoverQ[3][0][1]=41.0484;
  id->ID_x4AoverQ[3][1][0]=2.20712; id->ID_x4AoverQ[3][1][1]=-73.4407;
  id->ID_x4AoverQ[3][2][0]=2.22237; id->ID_x4AoverQ[3][2][1]=-73.1567;
  id->ID_x4AoverQ[3][3][0]=2.32009; id->ID_x4AoverQ[3][3][1]=41.0484;
  id->ID_x4AoverQ[3][4][0]=2.30468; id->ID_x4AoverQ[3][4][1]=41.0484;

  id->ID_x4AoverQ[4][0][0]=2.32064; id->ID_x4AoverQ[4][0][1]=39.6964;
  id->ID_x4AoverQ[4][1][0]=2.22332; id->ID_x4AoverQ[4][1][1]=-73.875;
  id->ID_x4AoverQ[4][2][0]=2.23886; id->ID_x4AoverQ[4][2][1]=-73.517;
  id->ID_x4AoverQ[4][3][0]=2.33663; id->ID_x4AoverQ[4][3][1]=39.6964;
  id->ID_x4AoverQ[4][4][0]=2.32064; id->ID_x4AoverQ[4][4][1]=39.6964;
  
//---- initial value for Z vs AoQ S1S2 PID -----//
  id->ID_Z21_AoverQ_num[0]=5;
  id->ID_Z21_AoverQ_num[1]=5;
  id->ID_Z21_AoverQ_num[2]=5;
  id->ID_Z21_AoverQ_num[3]=5;
  id->ID_Z21_AoverQ_num[4]=5;

  // 73Kr for 73Rb setting
  id->ID_Z21_AoverQ[0][0][0]=1.980      ; id->ID_Z21_AoverQ[0][0][1]=37.1;
  id->ID_Z21_AoverQ[0][1][0]=2.002      ; id->ID_Z21_AoverQ[0][1][1]=37.1;
  id->ID_Z21_AoverQ[0][2][0]=2.002      ; id->ID_Z21_AoverQ[0][2][1]=36.1;
  id->ID_Z21_AoverQ[0][3][0]=1.980      ; id->ID_Z21_AoverQ[0][3][1]=36.1 ;
  id->ID_Z21_AoverQ[0][4][0]=1.980      ; id->ID_Z21_AoverQ[0][4][1]=37.1;

  // 88Tc
  id->ID_Z21_AoverQ[1][0][0]=2.03; id->ID_Z21_AoverQ[1][0][1]=43.9;
  id->ID_Z21_AoverQ[1][1][0]=2.05; id->ID_Z21_AoverQ[1][1][1]=43.9;
  id->ID_Z21_AoverQ[1][2][0]=2.05; id->ID_Z21_AoverQ[1][2][1]=42.8;
  id->ID_Z21_AoverQ[1][3][0]=2.03; id->ID_Z21_AoverQ[1][3][1]=42.8;
  id->ID_Z21_AoverQ[1][4][0]=2.03; id->ID_Z21_AoverQ[1][4][1]=43.9;

  // all below Z=32
  id->ID_Z21_AoverQ[2][0][0]=1.90; id->ID_Z21_AoverQ[2][0][1]=25.;
  id->ID_Z21_AoverQ[2][1][0]=1.90; id->ID_Z21_AoverQ[2][1][1]=31.65;
  id->ID_Z21_AoverQ[2][2][0]=2.3; id->ID_Z21_AoverQ[2][2][1]=31.65;
  id->ID_Z21_AoverQ[2][3][0]=2.3; id->ID_Z21_AoverQ[2][3][1]=25.;
  id->ID_Z21_AoverQ[2][4][0]=1.90; id->ID_Z21_AoverQ[2][4][1]=25.;

  // 81Br
  id->ID_Z21_AoverQ[3][0][0]=2.01; id->ID_Z21_AoverQ[3][0][1]=34.5;
  id->ID_Z21_AoverQ[3][1][0]=2.03; id->ID_Z21_AoverQ[3][1][1]=34.5;
  id->ID_Z21_AoverQ[3][2][0]=2.03; id->ID_Z21_AoverQ[3][2][1]=35.3;
  id->ID_Z21_AoverQ[3][3][0]=2.01; id->ID_Z21_AoverQ[3][3][1]=35.3;
  id->ID_Z21_AoverQ[3][4][0]=2.01; id->ID_Z21_AoverQ[3][4][1]=34.5;

  // Rb
  id->ID_Z21_AoverQ[4][0][0]=1.90; id->ID_Z21_AoverQ[4][0][1]=37.4;
  id->ID_Z21_AoverQ[4][1][0]=1.90; id->ID_Z21_AoverQ[4][1][1]=38.1;
  id->ID_Z21_AoverQ[4][2][0]=2.3; id->ID_Z21_AoverQ[4][2][1]=38.1;
  id->ID_Z21_AoverQ[4][3][0]=2.3; id->ID_Z21_AoverQ[4][3][1]=37.4;
  id->ID_Z21_AoverQ[4][4][0]=1.90; id->ID_Z21_AoverQ[4][4][1]=37.4;

  //=========
  //range
  //=========
  range->id_z_offset = 0.; // do not change/use
  // Range from 238U primary beam plot (4440 mg) - 940 (S41 deg) - 1080 (Wedge) + Distance to AIDA: 600
  range->s4_matter = 3520.0 - 1079.6 + 600; //mg/cm2
  range->s41_deg_matter = 0.0; //mg/cm2
  range->degrader_rho = 2670; // mg/cm3
  //disk
  range->wedge_disk_in = true;
  range->wedge_disk_sum_thick = 4.0; // in mm
  range->wedge_disk_slope = -18./1000.; //mrad/1000
  range->dist_wedge_disk = 1710; // y-slit position
  //wedge
  range->plate_1_in = false;
  range->plate_2_in = false;
  range->plate_1_pos = -189.9; //mm
  range->plate_2_pos = -19; //mm
  // Wedge on degrader ladder HFSEM1GL
  range->ladder_1_in = false;
  range->ladder_1_slope = -0.0175;
  // Wedge on degrader ladder HFSEM1GR
  range->ladder_2_in = false;
  range->ladder_2_slope = -0.01691;

  cout << "Focus distance S4: " << frs->dist_focS4 << endl;
  cout << "Setup done " << endl;
  
}
