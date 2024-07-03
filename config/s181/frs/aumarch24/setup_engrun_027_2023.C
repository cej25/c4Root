////////TPC Y Calibration Parameters Updated/////// 
#include "Riostream.h"

void setup_engrun_027_2023()
{
  // look up analysis object and all parameters

  TFRSAnalysis* an = dynamic_cast<TFRSAnalysis*> (TGo4Analysis::Instance());
  if (an==0) {
    cout << "!!!  Script should be run in FRS analysis" << endl;
    return;
  }

  TFRSParameter* frs = dynamic_cast<TFRSParameter*> (an->GetParameter("FRSPar"));
  if (frs==0) {
    cout << "!!!  Parameter FRSPar not found" << endl;
    return;
  }

  TMWParameter* mw = dynamic_cast<TMWParameter*> (an->GetParameter("MWPar"));
  if (mw==0) {
    cout << "!!!  Parameter MWPar not found" << endl;
    return;
  }

  TMUSICParameter* music = dynamic_cast<TMUSICParameter*> (an->GetParameter("MUSICPar"));
  if (music==0) {
    cout << "!!!  Parameter MUSICPar not found" << endl;
    return;
  }

  TSCIParameter* sci = dynamic_cast<TSCIParameter*> (an->GetParameter("SCIPar"));
  if (sci==0) {
    cout << "!!!  Parameter SCIPar not found" << endl;
return;
  }

  TIDParameter* id = dynamic_cast<TIDParameter*> (an->GetParameter("IDPar"));
  if (id==0) {
    cout << "!!!  Parameter IDPar not found" << endl;
    return;
  }

  TTPCParameter* tpc = dynamic_cast<TTPCParameter*> (an->GetParameter("TPCPar"));
  if (tpc==0) {
    cout << "!!!  Parameter TPCPar not found" << endl;
    return;
  }

  TLABRParameter* labr = dynamic_cast<TLABRParameter*> (an->GetParameter("LABRPar"));
  if (labr==0) {
    cout << "!!!  Parameter LABRPar not found" << endl;
    return;
  }

  TSIParameter* si = dynamic_cast<TSIParameter*> (an->GetParameter("SIPar"));
  if (si==0) {
    cout << "!!!  Parameter SIPar not found" << endl;
    return;
  }

  TMRTOFMSParameter* mrtof = dynamic_cast<TMRTOFMSParameter*> (an->GetParameter("MRTOFMSPar"));
  if (mrtof==0) {
    cout << "!!!  Parameter MR-TOF-MSPar not found" << endl;
    return;
  }
  
  TRangeParameter* range = dynamic_cast<TRangeParameter*> (an->GetParameter("RangePar"));
  if (range==0) {
    cout << "!!!  Parameter RangePar not found" << endl;
    return;
  } 
 /*
  TModParameter* ElecMod = dynamic_cast<TModParameter*>(an->GetParameter("ModPar"));
   */
  cout << endl << "setup script started" << endl;

  // For the momemnt, we put 1 m for radius,
  // because we get brho from control system.
  frs->rho0[0]   = 1.; //TA-S2
  frs->rho0[1]   = 1.; //S2-S4
  frs->rho0[2]   = 1.; //S4-S8
  frs->dispersion[0]    = -6.490186; // run81-ta2-2020
  frs->dispersion[1]    =  7.670405; // run81-ta2-2020
  frs->magnification[1] =  1.181874; // run81-ta2-2020
  frs->dispersion[2]    = 12.397;   //S2-S8 (gicosy sign definition)
  frs->magnification[2] =  1.829;   //S2-S8
  frs->dispersion[3]    = 3.723;   //S2-HTM 08.05.2021
  frs->magnification[3] =  0.762;   //S2-HTM 08.05.2021
  
  //=============distances=============//
  //S2
  frs->dist_focS2 = 2012.5; //s2 disk eng-run 2023-11-16
  frs->dist_MW21  =  604.0; //eng-run 2023-11-16
  frs->dist_MW22  = 1782.5; //eng-run 2023-11-16
  frs->dist_TPC21 =  604.0; // eng-run 2023-11-16
  frs->dist_TPC22 = 1782.5; //eng-run 2023-11-16
  frs->dist_TPC23 = 4560.0-1670.0; //eng-run 2023-11-16
  frs->dist_TPC24 = 4560.0-578.5; //eng-run 2023-11-16
  frs->dist_SC21  = 1554.5; //eng-run 2023-11-16
  frs->dist_SC22  = 4560.0-1814.5; //eng-run 2023-11-16
  frs->dist_S2target = 1228.0; // S2 Xslit from eng-run 2023-11-16

  //S4
  frs->dist_SC41    = 2156.0+125.0; // eng-run 2023-11-16
  frs->dist_SC42    = 2600.0+125.0; // eng-run 2023-11-16
  frs->dist_SC43    = 4706.0+125.0; // not installed
  frs->dist_MUSIC41 = 600.0+125.0;  // eng-run 2023-11-16
  frs->dist_MUSIC42 = 1096.0+125.0; // eng-run 2023-11-16
  frs->dist_MUSIC43 = 3500.0; // estimated
  frs->dist_MUSIC44 = 5000.0; // estimated
  frs->dist_TPC41   =  220.0+125.0; // eng-run 2023-11-16
  frs->dist_TPC42   = 1457.0+125.0; // eng-run 2023-11-16
  frs->dist_S4target= 5200.0; // FRS-IC beam window estimated
  frs->dist_focS4   = 3300.0; // eng-run 2023-12-01
 
  //S8
  frs->dist_focS8 = 0;
  frs->dist_MW81 = 0;
  frs->dist_MW82 = 0;
  frs->dist_SC81 = 0;
  
  //=============switches=============//
  id->x_s2_select   = 1; //1=tpc,2=sc21,3=sc22
  id->tof_s4_select = 1; //1=sc21-41, 2=sc21-42, 3=sc22-41 used for TAC and MHTDC
  id->tof_s8_select = 1; //1=sc21-81, 2=sc22-81
  
  id->tof_HTM_select = 1; //1=sc21-M01, 2=sc22-M01
  id->Z_HTM_select = 3; //1=sc21, 2=sc22, 3=scM01
  
  //=============primary Z and plot ranges=============//
  frs->primary_z = 92.;   
  id->min_aoq_plot = 2.0;
  id->max_aoq_plot = 3.0;
  id->min_z_plot   = 70;
  id->max_z_plot   = 100;
   
  // bfield (Tm) for new control system. (we put rho = 1)
  frs->bfield[0] = 14.5374;    // 238U, 1000 MeV/u, eng run  
  frs->bfield[1] = 14.5374;    // 238U, 1000 MeV/u, eng run
  frs->bfield[2] = 12.494;   //  238U, 1000 MeV/u, eng run 
  frs->bfield[3] = 12.494;   //  238U, 1000 MeV/u, eng run
  frs->bfield[4] = 4.8347;   //  D5 (to ESR) not used
  frs->bfield[5] = 4.8347;  //   D6 (to S8)


  // From here VFTXMulti-HitTDC analysis
  id->vftx_s2pos_option=2; //(1: sc21x-timediff(not implemented), 2:tpc) 
  id->vftx_length_2141 = 36.68196; // SCI 21-41 s450 
  id->vftx_length_2241 = 35.22715; // SCI 22-41 s450
  id->vftx_length_2142 = 37.64317; // SCI 21-42 s450
  id->vftx_length_2242 = 35.0; // SCI 22-42 
  id->vftx_length_218 = 85.230; // to be checked!!! DK
  id->vftx_length_228 = 85.230; // to be checked!!! DK

  id->vftx_vel_a_music41[0]=6459.55; //s496 Xe 210512
  id->vftx_vel_a_music41[1]=-11135.1;
  id->vftx_vel_a_music41[2]=5581.45;
  id->vftx_vel_a_music41[3]=0.0;

  id->vftx_vel_a_music42[0]=6459.55; //DUMMY!!
  id->vftx_vel_a_music42[1]=-11135.1;
  id->vftx_vel_a_music42[2]=5581.45;
  id->vftx_vel_a_music42[3]=0.0;
  
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

  // MHTDCAnalysis S2-S4
  id->mhtdc_length_sc2141 = 37.204244; // 36.68196; // SCI 21-41 s450
  id->mhtdc_length_sc2241 = 36.850489; //35.227152; // SCI 22-41 s450 208Pb
  id->mhtdc_vel_a_music41[0]=6459.55; //s496 Xe 210512
  id->mhtdc_vel_a_music41[1]=-11135.1;
  id->mhtdc_vel_a_music41[2]=5581.45;
  id->mhtdc_vel_a_music41[3]=0.0;
  id->mhtdc_vel_a_music42[0]=7522.75; //s496 Xe 210512
  id->mhtdc_vel_a_music42[1]=-13599.0;
  id->mhtdc_vel_a_music42[2]=7039.16;
  id->mhtdc_vel_a_music42[3]=0.0;
  id->mhtdc_offset_z_music41=0.0; //s526 107Ag ..earlier 10.7
  id->mhtdc_offset_z_music42=0.0;

  // MHTDCAnalysis S2-HTM
  id->mhtdc_length_sc21HTM = 161.384 - 34.937; // meter SCI 21-M01 update 07.05.21
  id->mhtdc_length_sc22HTM = 161.384 - 34.937 - 1.; // meter SCI 22-M01 update 07.05.21
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
  id->mhtdc_offset_z_scM01=0.0;
  id->mhtdc_offset_z_sc21=0.0;
  id->mhtdc_offset_z_sc22=0.0;
  
  //not related for S8
  id->a2AoQCorr = 0.0012; //2020April12 JP
  id->a4AoQCorr = 0.0;
  
  //======
  //  MW
  //======
  /*   Naming conventions:  index     detector                      		 */
  /*                         0         MW11                                 */
  /*                         1         MW21                                 */
  /*                         2         MW22                                  */
  /*                         3         MW31                                 */
  /*                         4         MW51                                  */
  /*                         5         MW71                                  */
  /*                         6         MW81                                  */
  /*                         7         MW82                                  */
  /////////////////////////////////////////////////////////////////////////////

  mw->x_factor[0] = 0.25; // MW11 [mm/ns] some old value
  mw->x_factor[1] = 0.25; // MW21
  mw->x_factor[2] = 0.25; // MW22
  mw->x_factor[3] = 0.25; // MW31
  mw->x_factor[4] = 0.25; // MW51
  mw->x_factor[5] = 0.25; // MW71
  mw->x_factor[6] = 0.25; // MW81
  mw->x_factor[7] = 0.125; // MW82

  mw->x_offset[0] = 5.0; // MW11 Feb 2014
  mw->x_offset[1] = -2.0; // MW21 Feb 2014
  mw->x_offset[2] = -1.5; // MW22 Feb 2014
  mw->x_offset[3] = 5.0; // MW31 like MW11 15.11.19
  mw->x_offset[4] = -0.205; // MW51
  mw->x_offset[5] = 1.642; // MW71 //15/05/06
  mw->x_offset[6] = 1.;   // MW81 //11/05/06
  mw->x_offset[7] = -5.; // MW82 //27-MAY-2007

  mw->y_factor[0] = 0.25; // MW11 [mm/ns] 14.09.05 CN+AM 2ns/mm delay line
  mw->y_factor[1] = 0.25; // MW21
  mw->y_factor[2] = 0.25; // MW22
  mw->y_factor[3] = 0.25; // MW31
  mw->y_factor[4] = 0.25; // MW51
  mw->y_factor[5] = 0.25; // MW71
  mw->y_factor[6] = 0.25; // MW81
  mw->y_factor[7] = 0.125; // MW82  [mm/ns] 11.05.06  CN 4ns/mm delay line

  mw->y_offset[0] = -14.0;  // MW11 27-MAY-2007 TESTED VALUE WITH SLITS, ok Feb 2014
  mw->y_offset[1] = 21.0;   // Feb 2014
  mw->y_offset[2] = -1.0;   // MW22 27-MAY-2007 TESTED VALUE WITH SLITS, ok Feb 2014
  mw->y_offset[3] = -14.0;    // MW31 like in MW11 15.11.19
  mw->y_offset[4] = 0.0;     //MW51  ???????
  mw->y_offset[5] = -2.736;  // MW71 //15/05/06
  mw->y_offset[6] = 3.2;     // MW81 //11/05/06
  mw->y_offset[7] = 0.764;  // MW82 //11/05/06


  mw->gain_tdc[0][0] = 0.302929; //  MW11 Anode (#ch  0 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][0] = 0.303253; //  MW11 XL    (#ch 17 TDC V775a)
  mw->gain_tdc[2][0] = 0.303975; //  MW11 XR    (#ch 16 TDC V775a)
  mw->gain_tdc[3][0] = 0.308414; //  MW11 YU    (#ch 18 TDC V775a)
  mw->gain_tdc[4][0] = 0.309826; //  MW11 YD    (#ch 19 TDC V775a)

  mw->gain_tdc[0][1] = 0.306064; //  MW21 Anode (#ch  1 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][1] = 0.306958; //  MW21 XL    (#ch 21 TDC V775a)
  mw->gain_tdc[2][1] = 0.307799; //  MW21 XR    (#ch 20 TDC V775a)
  mw->gain_tdc[3][1] = 0.297774; //  MW21 YU    (#ch 22 TDC V775a)
  mw->gain_tdc[4][1] = 0.310235; //  MW21 YD    (#ch 23 TDC V775a)

  mw->gain_tdc[0][2] = 0.301179;  // MW22 Anode (#ch  2 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][2] = 0.311121; //  MW22 XL    (#ch 25 TDC V775a)
  mw->gain_tdc[2][2] = 0.303233; //  MW22 XR    (#ch 24 TDC V775a)
  mw->gain_tdc[3][2] = 0.300558; //  MW22 YU    (#ch 26 TDC V775a)
  mw->gain_tdc[4][2] = 0.301105; //  MW22 YD    (#ch 27 TDC V775a)

  mw->gain_tdc[0][3] = 0.304426; //  MW31 Anode (#ch  3 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][3] = 0.312163; //  MW31 XL    (#ch 29 TDC V775a)
  mw->gain_tdc[2][3] = 0.305609; //  MW31 XR    (#ch 28 TDC V775a)
  mw->gain_tdc[3][3] = 0.304716; //  MW31 YU    (#ch 30 TDC V775a)
  mw->gain_tdc[4][3] = 0.293695; //  MW31 YD    (#ch 31 TDC V775a)

  mw->gain_tdc[0][4] = 0.298871; //  MW41 Anode (#ch  4 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][4] = 0.284086; //  MW41 XL    (#ch 1 TDC V775b)
  mw->gain_tdc[2][4] = 0.288656; //  MW41 XR    (#ch 0 TDC V775b)
  mw->gain_tdc[3][4] = 0.286589; //  MW41 YU    (#ch 2 TDC V775b)
  mw->gain_tdc[4][4] = 0.29269;  //  MW41 YD    (#ch 3 TDC V775b)

  mw->gain_tdc[0][5] = 0.297881; //  MW42 Anode (#ch  5 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][5] = 0.287364; //  MW42 XL    (#ch 5 TDC V775b)
  mw->gain_tdc[2][5] = 0.289636; //  MW42 XR    (#ch 4 TDC V775b)
  mw->gain_tdc[3][5] = 0.291135; //  MW42 YU    (#ch 6 TDC V775b)
  mw->gain_tdc[4][5] = 0.289867; //  MW42 YD    (#ch 7 TDC V775b)

  mw->gain_tdc[0][6] = 0.307892; //  MW51 Anode (#ch  6 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][6] = 0.289894; //  MW51 XL    (#ch  9 TDC V775b)
  mw->gain_tdc[2][6] = 0.292366; //  MW51 XR    (#ch  8 TDC V775b)
  mw->gain_tdc[3][6] = 0.284708; //  MW51 YU    (#ch 10 TDC V775b)
  mw->gain_tdc[4][6] = 0.28186;  //  MW51 YD    (#ch 11 TDC V775b)

  mw->gain_tdc[0][7] = 0.298266; //  MW61 Anode (#ch  7 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][7] = 0.311; //  MW61 XL    (#ch ? TDC V775b)
  mw->gain_tdc[2][7] = 0.305; //  MW61 XR    (#ch ? TDC V775b)
  mw->gain_tdc[3][7] = 0.337; //  MW61 YU    (#ch ? TDC V775b)
  mw->gain_tdc[4][7] = 0.289; //  MW61 YD    (#ch ? TDC V775b)

  mw->gain_tdc[0][8] = 0.303602; //  MW71 Anode (#ch  8 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][8] = 0.300082; //  MW71 XL    (#ch 13 TDC V775b)
  mw->gain_tdc[2][8] = 0.286092; //  MW71 XR    (#ch 12 TDC V775b)
  mw->gain_tdc[3][8] = 0.294287; //  MW71 YU    (#ch 14 TDC V775b)
  mw->gain_tdc[4][8] = 0.291341; //  MW71 YD    (#ch 15 TDC V775b)

  mw->gain_tdc[0][9] = 0.306041; //  MW81 Anode (#ch  9 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][9] = 0.288468; //  MW81 XL    (#ch 17 TDC V775b)
  mw->gain_tdc[2][9] = 0.293831; //  MW81 XR    (#ch 16 TDC V775b)
  mw->gain_tdc[3][9] = 0.281296; //  MW81 YU    (#ch 18 TDC V775b)
  mw->gain_tdc[4][9] = 0.279099; //  MW81 YD    (#ch 19 TDC V775b)

  mw->gain_tdc[0][10] = 0.31314;  //  MW82 Anode (#ch 10 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][10] = 0.287279; //  MW82 XL    (#ch 21 TDC V775b)
  mw->gain_tdc[2][10] = 0.284028; //  MW82 XR    (#ch 20 TDC V775b)
  mw->gain_tdc[3][10] = 0.28051;  //  MW82 YU    (#ch 22 TDC V775b)
  mw->gain_tdc[4][10] = 0.28743;  //  MW82 YD    (#ch 23 TDC V775b)

  mw->gain_tdc[0][11] = 0.299973; //  MWB21 Anode (#ch 11 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][11] = 0.311; //  MWB21 XL    (#ch ? TDC V775b)
  mw->gain_tdc[2][11] = 0.305; //  MWB21 XR    (#ch ? TDC V775b)
  mw->gain_tdc[3][11] = 0.337; //  MWB21 YU    (#ch ? TDC V775b)
  mw->gain_tdc[4][11] = 0.289; //  MWB21 YD    (#ch ? TDC V775b)

  mw->gain_tdc[0][12] = 0.306923; //  MWB22 Anode (#ch 12 TDC V775a) // 13.01.2008
  mw->gain_tdc[1][12] = 0.311; //  MWB22 XL    (#ch ? TDC V775b)
  mw->gain_tdc[2][12] = 0.305; //  MWB22 XR    (#ch ? TDC V775b)
  mw->gain_tdc[3][12] = 0.337; //  MWB22 YU    (#ch ? TDC V775b)
  mw->gain_tdc[4][12] = 0.289; //  MWB22 YD    (#ch ? TDC V775b)


  //=========
  // MUSICs
  //=========

  // histogram setup
  music->max_adc_music1 =    4096; //tum music
  music->max_adc_music2 =    4096; //tum music
  music->max_adc_music3 =  0x10000; //travel music
  music->max_adc_music4 =    4096; //tum music
  music->max_tdc_music1 =    120000; //tum music
  music->max_tdc_music2 =    120000; //tum music
  music->max_tdc_music3 = 0x10000; //travel music
  music->max_tdc_music4 =    120000; //tum music

  //MUSIC noisy channel to be excluded in dE calculation
  //TRUE means exclude.
  //default is FALSE
  for(int ii=0; ii<8; ii++){
    music->exclude_de1_adc_channel[ii] = kFALSE;
    music->exclude_de2_adc_channel[ii] = kFALSE;
    music->exclude_de3_adc_channel[ii] = kFALSE;
    music->exclude_de4_adc_channel[ii] = kFALSE;
  }
  music->exclude_de1_adc_channel[5] = kTRUE; //added 01:50/May-12/2022 S450
  music->exclude_de4_adc_channel[4] = kTRUE; //Prototype MUSIC used with only 4 anodes
  music->exclude_de4_adc_channel[5] = kTRUE;
  music->exclude_de4_adc_channel[6] = kTRUE;
  music->exclude_de4_adc_channel[7] = kTRUE;

  //  
  music->dist_MUSICa1 = 52.5;  // do not change
  music->dist_MUSICa2 = 157.5; // do not change
  music->dist_MUSICa3 = 262.5; // do not change
  music->dist_MUSICa4 = 367.5; // do not change

  //MUSIC41
  music->e1_off[0]   = 0.; //MUSIC41 offsets
  music->e1_off[1]   = 0.;
  music->e1_off[2]   = 0.;
  music->e1_off[3]   = 0.;
  music->e1_off[4]   = 0.;
  music->e1_off[5]   = 0.;
  music->e1_off[6]   = 0.;
  music->e1_off[7]   = 0.;

  music->e1_gain[0]   = 1.; // MUSIC41 gains
  music->e1_gain[1]   = 1.;
  music->e1_gain[2]   = 1.;
  music->e1_gain[3]   = 1.;
  music->e1_gain[4]   = 1.;
  music->e1_gain[5]   = 1.;
  music->e1_gain[6]   = 1.;
  music->e1_gain[7]   = 1.;

  //MUSIC42
  music->e2_off[0]   = 0.; //MUSIC42 offsets
  music->e2_off[1]   = 0.;
  music->e2_off[2]   = 0.;
  music->e2_off[3]   = 0.;
  music->e2_off[4]   = 0.;
  music->e2_off[5]   = 0.;
  music->e2_off[6]   = 0.;
  music->e2_off[7]   = 0.;

  music->e2_gain[0]   = 1.; //MUSIC42 gains
  music->e2_gain[1]   = 1.;
  music->e2_gain[2]   = 1.;
  music->e2_gain[3]   = 1.;
  music->e2_gain[4]   = 1.;
  music->e2_gain[5]   = 1.;
  music->e2_gain[6]   = 1.;
  music->e2_gain[7]   = 1.;

  //MUSIC43
  music->e3_off[0]   = 0.; //MUSIC3 offsets
  music->e3_off[1]   = 0.;
  music->e3_off[2]   = 0.;
  music->e3_off[3]   = 0.;
  music->e3_off[4]   = 0.;
  music->e3_off[5]   = 0.;
  music->e3_off[6]   = 0.;
  music->e3_off[7]   = 0.;

  music->e3_gain[0]   = 1.; // MUSIC3 gains
  music->e3_gain[1]   = 1.;
  music->e3_gain[2]   = 1.;
  music->e3_gain[3]   = 1.;
  music->e3_gain[4]   = 1.;
  music->e3_gain[5]   = 1.;
  music->e3_gain[6]   = 1.;
  music->e3_gain[7]   = 1.;

  //MUSIC44
  music->e4_off[0]   = 0.; //MUSIC4 offsets
  music->e4_off[1]   = 0.;
  music->e4_off[2]   = 0.;
  music->e4_off[3]   = 0.;
  music->e4_off[4]   = 0.;
  music->e4_off[5]   = 0.;
  music->e4_off[6]   = 0.;
  music->e4_off[7]   = 0.;

  music->e4_gain[0]   = 1.; // MUSIC4 gains
  music->e4_gain[1]   = 1.;
  music->e4_gain[2]   = 1.;
  music->e4_gain[3]   = 1.;
  music->e4_gain[4]   = 1.;
  music->e4_gain[5]   = 1.;
  music->e4_gain[6]   = 1.;
  music->e4_gain[7]   = 1.;

  music->pos_a1[0]   = 0.998;   // C0...Cn position correction not used
  music->pos_a1[1]   = -1.991e-5;
  music->pos_a1[2]   = 1.969e-6;
  music->pos_a1[3]   = 1.114e-8;
  music->pos_a1[4]   = -3.841e-10;
  music->pos_a1[5]   = -2.950e-13;
  music->pos_a1[6]   = 0.0;

  music->pos_a2[0]   = 0.998;   // C0...Cn position correction not used
  music->pos_a2[1]   = -1.991e-5;
  music->pos_a2[2]   = 1.969e-6;
  music->pos_a2[3]   = 1.114e-8;
  music->pos_a2[4]   = -3.841e-10;
  music->pos_a2[5]   = -2.950e-13;
  music->pos_a2[6]   = 0.0;

  music->pos_a3[0]   = 0.998;   // C0...Cn position correction not used
  music->pos_a3[1]   = -1.991e-5;
  music->pos_a3[2]   = 1.969e-6;
  music->pos_a3[3]   = 1.114e-8;
  music->pos_a3[4]   = -3.841e-10;
  music->pos_a3[5]   = -2.950e-13;
  music->pos_a3[6]   = 0.0;

  music->pos_a4[0]   = 0.998;   // C0...Cn position correction not used
  music->pos_a4[1]   = -1.991e-5;
  music->pos_a4[2]   = 1.969e-6;
  music->pos_a4[3]   = 1.114e-8;
  music->pos_a4[4]   = -3.841e-10;
  music->pos_a4[5]   = -2.950e-13;
  music->pos_a4[6]   = 0.0;
  
  //  MUSIC41 velocity 09.12.2023 238U //eng run
  id->vel_a[0] =   10455.0; //  MUSIC41 velocity corr. //eng run
  id->vel_a[1] =   -14923.0;   // eng run
  id->vel_a[2] =   6308.0; // eng run
  id->vel_a[3] =   0.0;

  // MUSIC42 velocity 09.12.2023 238U //eng run
  id->vel_a2[0] =  10570.0; //eng run
  id->vel_a2[1] = -15105.0; //eng run
  id->vel_a2[2] =  6366.0;//eng run
  id->vel_a2[3] =  0.0;

  //MUSIC43 velocity corr. (old)
  id->vel_a3[0] =  13951.37; 
  id->vel_a3[1] = -38369.9;
  id->vel_a3[2] =  28396.46;
  id->vel_a3[3] =  0.0;

  //MUSIC44 velocity corr. (not determined)
  id->vel_a4[0] =  11588.7; 
  id->vel_a4[1] = -18321.8;
  id->vel_a4[2] =  8528.11;
  id->vel_a4[3] =  0.0; 
  
  id->offset_z   = 0.0;
  id->offset_z2  = 0.0;
  id->offset_z3  = 0.0;
  id->offset_z4  = 0.0;
  
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
  tpc->x_offset[0][0] = -0.408463 +0.2 -3.0;//update on 2021/June/19 slitx, degr.center as ref
  tpc->x_factor[0][0] = 0.007978;
  tpc->x_offset[0][1] = 0.959454  +0.2 -3.0;
  tpc->x_factor[0][1] = 0.008105;
  tpc->y_offset[0][0] = -56.3389688;//-55.037378 -0.6 -1.5;
  tpc->y_factor[0][0] = 0.0038418; //0.003956; //vacuum tpc is drift to bottom. positive y-factor
  tpc->y_offset[0][1] =-56.9720263;// -55.193154 -0.6 -1.5;
  tpc->y_factor[0][1] = 0.0038732;//0.003953;
  tpc->y_offset[0][2] = -57.2758022;//-56.659256 -0.6 -1.5;
  tpc->y_factor[0][2] = 0.0038965;//0.004082;
  tpc->y_offset[0][3] = -57.7001232;//-55.009200 -0.6 -1.5;
  tpc->y_factor[0][3] = 0.0039169;//0.003934;
  
  // TPC21 gate conditions:  After changing cut limits => Launch analysis again in Go4GUI
  tpc->lim_dt[0][0][0] = 13000.;  tpc->lim_dt[0][0][1] = 43000.0; //A11 drift time TDC cut
  tpc->lim_dt[0][1][0] = 13000.;  tpc->lim_dt[0][1][1] = 43000.0; //A12 drift time TDC cut
  tpc->lim_dt[0][2][0] = 13000.;  tpc->lim_dt[0][2][1] = 43000.0; //A21 drift time TDC cut
  tpc->lim_dt[0][3][0] = 13000.;  tpc->lim_dt[0][3][1] = 43000.0; //A22 drift time TDC cut
  tpc->lim_lt[0][0][0] = 20000.;  tpc->lim_lt[0][0][1] = 50000.0; //DL1 time TDC cut`
  tpc->lim_rt[0][0][0] = 20000.;  tpc->lim_rt[0][0][1] = 50000.0; //DR1 time TDC cut
  tpc->lim_lt[0][1][0] = 20000.;  tpc->lim_lt[0][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_rt[0][1][0] = 20000.;  tpc->lim_rt[0][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_csum1[0][0] = 13700.0;  tpc->lim_csum1[0][1] = 14600.0;
  tpc->lim_csum2[0][0] = 13900.0;  tpc->lim_csum2[0][1] = 14600.0;
  tpc->lim_csum3[0][0] = 13500.0;  tpc->lim_csum3[0][1] = 14600.0; 
  tpc->lim_csum4[0][0] = 13500.0;  tpc->lim_csum4[0][1] = 14600.0;

  
  //-------- TPC22 parameters after Repair in May 2021 (updated on // 19/June/2021, BARB june 2021) ----------
  // TPC22 at S2 in vacuum
  //
  tpc->id_tpc_timeref[1] = 1; // Do not change id_tpc_timeref. (0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
  // because calibration parameters (y) are valid only with timeref used during calibration.
  // if you want to change timeref, you need to calibrate y-position  again ! )
  tpc->x_offset[1][0] = 2.483279 +0.7 -0.5;//update on 2021/June/19 slitx, degr.center as ref
  tpc->x_factor[1][0] = 0.007781;
  tpc->x_offset[1][1] = 0.561674 +0.7 -0.5;
  tpc->x_factor[1][1] = 0.007574;
  tpc->y_offset[1][0] = -58.1084677;//-57.558218 +1.4 -3.0;
  tpc->y_factor[1][0] = 0.0039634;//0.004107;   //vacuum tpc is drift to bottom. positive y-factor
  tpc->y_offset[1][1] = -58.7300878;//-56.781388 +1.4 -3.0;
  tpc->y_factor[1][1] = 0.0039666;//0.004016;
  tpc->y_offset[1][2] = -59.094806;//-57.216335 +1.4 -3.0;
  tpc->y_factor[1][2] = 0.0039668;//0.004024;
  tpc->y_offset[1][3] = -58.5754908;//-56.691696 +1.4 -3.0;
  tpc->y_factor[1][3] = 0.0039793;//0.004046;
  // TPC22 gate condition... After changing cut limits => Launch analysis again in Go4GUI
  tpc->lim_dt[1][0][0] = 13000.;  tpc->lim_dt[1][0][1] = 43000.0; //A11 drift time TDC cut
  tpc->lim_dt[1][1][0] = 13000.;  tpc->lim_dt[1][1][1] = 43000.0; //A12 drift time TDC cut
  tpc->lim_dt[1][2][0] = 13000.;  tpc->lim_dt[1][2][1] = 43000.0; //A21 drift time TDC cut
  tpc->lim_dt[1][3][0] = 13000.;  tpc->lim_dt[1][3][1] = 43000.0; //A22 drift time TDC cut
  tpc->lim_lt[1][0][0] = 20000.;  tpc->lim_lt[1][0][1] = 50000.0; //DL1 time TDC cut
  tpc->lim_rt[1][0][0] = 20000.;  tpc->lim_rt[1][0][1] = 50000.0; //DR1 time TDC cut
  tpc->lim_lt[1][1][0] = 20000.;  tpc->lim_lt[1][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_rt[1][1][0] = 20000.;  tpc->lim_rt[1][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_csum1[1][0] = 17000.0;    tpc->lim_csum1[1][1] =  19200.0;
  tpc->lim_csum2[1][0] = 17000.0;    tpc->lim_csum2[1][1] =  19200.0;
  tpc->lim_csum3[1][0] = 17000.0;    tpc->lim_csum3[1][1] =  19200.0;
  tpc->lim_csum4[1][0] = 17000.0;    tpc->lim_csum4[1][1] =  19200.0;
  
  
  //-------- TPC23 parameters  (updated on 2021/May31, begeinnig of S526, timeref=2, U beam)--------------
  // TPC23 at S2 in air
  //
  tpc->id_tpc_timeref[2] = 1;// Do not change id_tpc_timeref. (0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
  // because calibration parameters (y) are valid only with timeref used during calibration.
  // if you want to change timeref, you need to calibrate y-position  again ! )
  tpc->x_offset[2][0] = 4.389925 +1.5-1.5+1.6-0.57-0.6+1.0-3.0-6.2; //11.05.22 -6.2 is to djust for disc-center //update on 2021/Mar/31 tpc calib for timeref id=2 (sc22).
  tpc->x_factor[2][0] = 0.008002;
  tpc->x_offset[2][1] = -0.136026 +1.5-1.5+1.6-0.57-0.6+1.0-3.0-6.2; //11.05.22 -6.2 is to djust for disc-center
  tpc->x_factor[2][1] = 0.007852;
  tpc->y_offset[2][0] = 48.588674+7.5+(2.286-7.958)-0.8;
  tpc->y_factor[2][0] = -0.004231; //air tpc is drift to top. negative y-factor
  tpc->y_offset[2][1] = 48.726112+7.5+(2.286-7.958)-0.8;
  tpc->y_factor[2][1] = -0.004244;
  tpc->y_offset[2][2] = 48.746238+7.5+(2.286-7.958)-0.8;
  tpc->y_factor[2][2] = -0.004246;
  tpc->y_offset[2][3] = 48.308878+7.5+(2.286-7.958)-0.8;
  tpc->y_factor[2][3] = -0.004220;

  // TPC23 gate conditions:  After changing cut limits => Launch analysis again in Go4GUI
  tpc->lim_dt[2][0][0] = 13000.;  tpc->lim_dt[2][0][1] = 43000.0; //A11 drift time TDC cut
  tpc->lim_dt[2][1][0] = 13000.;  tpc->lim_dt[2][1][1] = 43000.0; //A12 drift time TDC cut
  tpc->lim_dt[2][2][0] = 13000.;  tpc->lim_dt[2][2][1] = 43000.0; //A21 drift time TDC cut
  tpc->lim_dt[2][3][0] = 13000.;  tpc->lim_dt[2][3][1] = 43000.0; //A22 drift time TDC cut
  tpc->lim_lt[2][0][0] = 20000.;  tpc->lim_lt[2][0][1] = 50000.0; //DL1 time TDC cut
  tpc->lim_rt[2][0][0] = 20000.;  tpc->lim_rt[2][0][1] = 50000.0; //DR1 time TDC cut
  tpc->lim_lt[2][1][0] = 20000.;  tpc->lim_lt[2][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_rt[2][1][0] = 20000.;  tpc->lim_rt[2][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_csum1[2][0] = 13800.0;   tpc->lim_csum1[2][1] = 14800.0; //, 15:00 2022-May-12
  tpc->lim_csum2[2][0] = 14000.0;   tpc->lim_csum2[2][1] = 14800.0;//, 15:00 2022-May-12
  tpc->lim_csum3[2][0] = 14000.0;   tpc->lim_csum3[2][1] = 14800.0;//, 15:00 2022-May-12
  tpc->lim_csum4[2][0] = 14000.0;   tpc->lim_csum4[2][1] = 14800.0; //, 15:00 2022-May-12
  
  
  //-------- TPC24 parameters  ------- (updated on 2021/May31, begeinnig of S526, timeref=2, U beam)--------------
  // TPC24 at S2 in air
  //
  tpc->id_tpc_timeref[3] = 1;// Do not change id_tpc_timeref. (0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
  // because calibration parameters (for y) are valid only with timeref used during calibration.
  // if you want to change timeref, you need to calibrate y-position  again ! )
  tpc->x_offset[3][0] = 3.539890 -0.6-14.0+14.0-0.57+1.0-0.25-6.2; //11.05.22 -6.2 is to djust for disc-center /2021/March/31 for all these paramters with timeref=2
  tpc->x_factor[3][0] = 0.008047;
  tpc->x_offset[3][1] = 2.242643 -0.6-14.0+14.0-0.57+1.0-0.25-6.2; //11.05.22 -6.2 is to djust for disc-center
  tpc->x_factor[3][1] = 0.007796;
  tpc->y_offset[3][0] = 63.4310738;//57.682383-1.5+9.0+(1.706-6.991)+1.2;
  tpc->y_factor[3][0] = -0.0040971;//-0.004033; //air tpc is drift to top. negative y-factor
  tpc->y_offset[3][1] = 63.8444714;//58.217353-1.5+9.0+(1.706-6.991)+1.2;
  tpc->y_factor[3][1] = -0.0040887;//-0.004044;
  tpc->y_offset[3][2] = 62.8678718;//57.839351-1.5+9.0+(1.706-6.991)+1.2;
  tpc->y_factor[3][2] = -0.0040725;//-0.004039;
  tpc->y_offset[3][3] = 62.9917085;//57.901361-1.5+9.0+(1.706-6.991)+1.2;
  tpc->y_factor[3][3] = -0.0040386;//-0.004029;

  // TPC24 gate conditions:  After changing cut limits => Launch analysis again in Go4GUI
  tpc->lim_dt[3][0][0] = 13000.;  tpc->lim_dt[3][0][1] = 43000.0; //A11 drift time TDC cut
  tpc->lim_dt[3][1][0] = 13000.;  tpc->lim_dt[3][1][1] = 43000.0; //A12 drift time TDC cut
  tpc->lim_dt[3][2][0] = 13000.;  tpc->lim_dt[3][2][1] = 43000.0; //A21 drift time TDC cut
  tpc->lim_dt[3][3][0] = 13000.;  tpc->lim_dt[3][3][1] = 43000.0; //A22 drift time TDC cut
  tpc->lim_lt[3][0][0] = 20000.;  tpc->lim_lt[3][0][1] = 50000.0; //DL1 time TDC cut
  tpc->lim_rt[3][0][0] = 20000.;  tpc->lim_rt[3][0][1] = 50000.0; //DR1 time TDC cut
  tpc->lim_lt[3][1][0] = 20000.;  tpc->lim_lt[3][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_rt[3][1][0] = 20000.;  tpc->lim_rt[3][1][1] = 50000.0; //DL2 time TDC cut
  tpc->lim_csum1[3][0] = 18100.0 -200.;    tpc->lim_csum1[3][1] = 18800.0+200.; ////, 15:00 2022-May-12
  tpc->lim_csum2[3][0] = 17900.0 -200.;    tpc->lim_csum2[3][1] = 18700.0+200.; ////, 15:00 2022-May-12
  tpc->lim_csum3[3][0] = 18600.0 -200.;    tpc->lim_csum3[3][1] = 19400.0+200.; ////, 15:00 2022-May-12
  tpc->lim_csum4[3][0] = 18200.0 -200.;    tpc->lim_csum4[3][1] = 19000.0+200.; ////, 15:00 2022-May-12
  
  
  //-------- TPC41 parameters  (updated on // 19/June/2021, BARB june 2021) -------
  // TPC41 at S4 in air
  //
  tpc->id_tpc_timeref[4] = 4; // Do not change id_tpc_timeref. (0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
  // because calibration parameters (for y) are valid only with timeref used during calibration.
  // if you want to change timeref, you need to calibrate y-position  again ! )
  tpc->x_offset[4][0] = -0.657524+2.0 +1.8-3.8-0.25+1.5;// 19/June/2021, +1.5 Dec.02 2023
  tpc->x_factor[4][0] = 0.007779*12./11.;
  tpc->x_offset[4][1] = -1.806150+2.0 +1.8-3.8-0.25+1.5; // 19/June/2021//trust more final grid in front of IC, and correct for TPC41/42
  tpc->x_factor[4][1] = 0.007802*12./11.;
  tpc->y_offset[4][0] = 54.670698 -1.3 -0.5+0.8+0.8;// 19/June/2021
  tpc->y_factor[4][0] = -0.004075;  //air tpc is drift to top. negative y-factor
  tpc->y_offset[4][1] = 54.704890 -1.3 -0.5 +0.8+0.8;// 19/June/2021
  tpc->y_factor[4][1] = -0.004077;
  tpc->y_offset[4][2] = 55.482351 -1.3 -0.5+0.8+0.8;// 19/June/2021
  tpc->y_factor[4][2] = -0.004049;
  tpc->y_offset[4][3] = 55.628042 -1.3 -0.5+0.8+0.8;// 19/June/2021
  tpc->y_factor[4][3] = -0.004074;
  // TPC41 gate conditions: After changing cut limits => Launch analysis again in Go4GUI
  tpc->lim_dt[4][0][0] = 10000.;  tpc->lim_dt[4][0][1] = 40000.0; //A11 drift time TDC cut
  tpc->lim_dt[4][1][0] = 10000.;  tpc->lim_dt[4][1][1] = 40000.0; //A12 drift time TDC cut
  tpc->lim_dt[4][2][0] = 10000.;  tpc->lim_dt[4][2][1] = 40000.0; //A21 drift time TDC cut
  tpc->lim_dt[4][3][0] = 10000.;  tpc->lim_dt[4][3][1] = 40000.0; //A22 drift time TDC cut
  tpc->lim_lt[4][0][0] = 20000.;  tpc->lim_lt[4][0][1] = 45000.0; //DL1 time TDC cut
  tpc->lim_rt[4][0][0] = 20000.;  tpc->lim_rt[4][0][1] = 45000.0; //DR1 time TDC cut
  tpc->lim_lt[4][1][0] = 20000.;  tpc->lim_lt[4][1][1] = 45000.0; //DL2 time TDC cut
  tpc->lim_rt[4][1][0] = 20000.;  tpc->lim_rt[4][1][1] = 45000.0; //DL2 time TDC cut
  tpc->lim_csum1[4][0] = 14000.0;    tpc->lim_csum1[4][1] = 14900.0;
  tpc->lim_csum2[4][0] = 14050.0;    tpc->lim_csum2[4][1] = 14650.0;
  tpc->lim_csum3[4][0] = 14100.0;    tpc->lim_csum3[4][1] = 14600.0;
  tpc->lim_csum4[4][0] = 14100.0;    tpc->lim_csum4[4][1] = 14700.0;
  

  //-------- TPC42 parameters (updated on // 19/June/2021, BARB june 2021)
  // TPC42 at S4 in air 
  tpc->id_tpc_timeref[5] = 4; // Do not change id_tpc_timeref. (0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
  // because calibration parameters (y) are valid only with timeref used during calibration.
  // if you want to change timeref, you need to calibrate y-position again ! )
  tpc->x_offset[5][0] = 2.821206-2.0 +8.0 -1.8-4.5-0.2-1.5; // 19/June/2021, -1.5 Dec.02 2023 
  tpc->x_factor[5][0] = 0.007828*24./23.;
  tpc->x_offset[5][1] = 1.989353-2.0 +8.0 -1.8-4.5-0.2-1.5; // 19/June/2021 //trust more final grid in front of IC, and correct for TPC41/42
  tpc->x_factor[5][1] = 0.007999*24./23.;
  tpc->y_offset[5][0] = 55.137927 +1.3 +0.5-0.8-1.1;// 19/June/2021
  tpc->y_factor[5][0] = -0.004056; //air tpc is drift to top. negative y-factor
  tpc->y_offset[5][1] = 55.897006 +1.3 +0.5-0.8-1.1;// 19/June/2021
  tpc->y_factor[5][1] = -0.004060;
  tpc->y_offset[5][2] = 54.034448 +1.3 +0.5-0.8-1.1;// 19/June/2021
  tpc->y_factor[5][2] = -0.004039;
  tpc->y_offset[5][3] = 53.536067 +1.3 +0.5-0.8-1.1;// 19/June/2021
  tpc->y_factor[5][3] = -0.004036;
  // TPC42 gate conditions:  After changing cut limits => Launch analysis again in Go4GUI
  tpc->lim_dt[5][0][0] = 10000.;  tpc->lim_dt[5][0][1] = 40000.0; //A11 drift time TDC cut
  tpc->lim_dt[5][1][0] = 10000.;  tpc->lim_dt[5][1][1] = 40000.0; //A12 drift time TDC cut
  tpc->lim_dt[5][2][0] = 10000.;  tpc->lim_dt[5][2][1] = 40000.0; //A21 drift time TDC cut
  tpc->lim_dt[5][3][0] = 10000.;  tpc->lim_dt[5][3][1] = 40000.0; //A22 drift time TDC cut
  tpc->lim_lt[5][0][0] = 20000.;  tpc->lim_lt[5][0][1] = 45000.0; //DL1 time TDC cut
  tpc->lim_rt[5][0][0] = 20000.;  tpc->lim_rt[5][0][1] = 45000.0; //DR1 time TDC cut
  tpc->lim_lt[5][1][0] = 20000.;  tpc->lim_lt[5][1][1] = 45000.0; //DL2 time TDC cut
  tpc->lim_rt[5][1][0] = 20000.;  tpc->lim_rt[5][1][1] = 45000.0; //DL2 time TDC cut
  tpc->lim_csum1[5][0] = 14300.0;    tpc->lim_csum1[5][1] = 14900.0;
  tpc->lim_csum2[5][0] = 14100.0;    tpc->lim_csum2[5][1] = 14500.0;
  tpc->lim_csum3[5][0] = 13650.0;    tpc->lim_csum3[5][1] = 14050.0;
  tpc->lim_csum4[5][0] = 13750.0;    tpc->lim_csum4[5][1] = 14250.0;


  //TPC at S3 (TPC 31) calibration updated on 19/June/2021
   tpc->id_tpc_timeref[6] = 3; //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
  tpc->x_offset[6][0] = -1.37;
  tpc->x_offset[6][1] = -3.30;
  tpc->x_factor[6][0] = 0.007981;
  tpc->x_factor[6][1] = 0.007888;
  tpc->y_offset[6][0] = -55.2-11.5 -7.0;//19/June/2021  y parameters were deduced from SC31 edge
  tpc->y_offset[6][1] = -57.3-11.5 -7.0;//19/June/2021  y in go4 follows y of S3 chamber (sc31 laddeer)
  tpc->y_offset[6][2] = -54.0-11.5 -7.0;//19/June/2021
  tpc->y_offset[6][3] = -53.7-11.5 -7.0;//19/June/2021
  tpc->y_factor[6][0] = 0.004*45./44.;
  tpc->y_factor[6][1] = 0.004*45./44.;
  tpc->y_factor[6][2] = 0.004*45./44;
  tpc->y_factor[6][3] = 0.004*45./44;
  tpc->lim_dt[6][0][0] = 10000.;  tpc->lim_dt[6][0][1] = 40000.0; //A11 drift time TDC cut
  tpc->lim_dt[6][1][0] = 10000.;  tpc->lim_dt[6][1][1] = 40000.0; //A12 drift time TDC cut
  tpc->lim_dt[6][2][0] = 10000.;  tpc->lim_dt[6][2][1] = 40000.0; //A21 drift time TDC cut
  tpc->lim_dt[6][3][0] = 10000.;  tpc->lim_dt[6][3][1] = 40000.0; //A22 drift time TDC cut
  tpc->lim_lt[6][0][0] = 20000.;  tpc->lim_lt[6][0][1] = 45000.0; //DL1 time TDC cut
  tpc->lim_rt[6][0][0] = 20000.;  tpc->lim_rt[6][0][1] = 45000.0; //DR1 time TDC cut
  tpc->lim_lt[6][1][0] = 20000.;  tpc->lim_lt[6][1][1] = 45000.0; //DL2 time TDC cut
  tpc->lim_rt[6][1][0] = 20000.;  tpc->lim_rt[6][1][1] = 45000.0; //DL2 time TDC cut
  tpc->lim_csum1[6][0] = 11500.0;    tpc->lim_csum1[6][1] = 14500.0;
  tpc->lim_csum2[6][0] = 11000.0;    tpc->lim_csum2[6][1] = 14000.0;
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
  id->id_tofoff2 =  199353; //197454.8;  // offset (ps)
  id->id_path2   =  122663; //122486.0;  // path/c (ps)
  
  //TOF_SC42_SC21_TAC 09.12.23 U engrun
  id->id_tofoff3  = 201945; // 196914.0;   // offset (ps)
  id->id_path3    = 123401; // 125574.9;   // path/c [ps
  
  // TOF calibration SC21-SC81 (TAC)
  id->id_tofoff4  = 326337.1;   //SC21-81 [ps]          // quickly done from run156 and 166 (2019/Nov, YT)
  id->id_path4    = 246983.1;   //SC21-81  path/c [ps]  // quickly done from run156 and 166 (2019/Nov, YT)

  //TOF_SC41_SC22_TAC 09.12.23 U engrun
  id->id_tofoff5 =  178527; // 187952.5;  // offset (ps) 
  id->id_path5   =  121304; //117471.1;  // path/c (ps)
  
  // TOF calibration SC21-SC81 (TAC)
  id->id_tofoff6  = 405709.2;   //SC22-81 [ps]          // 21feb2020 DK, YT
  id->id_path6    = 278586.5;   //SC22-81  path/c [ps]  // 21feb2020 DK, YT
  

  //index 2 for Sc21
  sci->x_a[0][2] =    543.599;  // quickly done for s526 on 02.06.2021 (from online)
  sci->x_a[1][2] =   -0.2957;  // quickly done for s526 on 02.06.2021 (from online)
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
  sci->tac_off[8] = 0.0;  //SC81L-R  // fix to 0
  sci->tac_off[9] = 0.0;  //SC81L-SC21L  // fix to 0
  sci->tac_off[10]= 0.0;  //SC81R-SC21R  // fix to 0
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
  sci->tac_factor[8]  = 10.51; //SC81L-R [ps/ch]     >> ch4 of ADC
  sci->tac_factor[9]  = 20.84; //SC81L-SC21L 100ns range        >> ch9          //10.27 for 50ns range
  sci->tac_factor[10] = 20.79; //SC81R-SC21R 100ns range        >> ch10         //10.49 for 50ns range
  
  sci->tof_bll2  = 1.;    // not used online [ps/ch]
  sci->tof_brr2  = 1.;    // not used online
  sci->tof_bll3  = 1.;    // not used online
  sci->tof_brr3  = 1.;    // not used online
  sci->tof_bll4  = 1.;    // not used online
  sci->tof_brr4  = 1.;    // not used online

  sci->tof_a2 = 146.46; // [ps] offset   Tof S41-S21
  sci->tof_a3 = 0.; // [ps] offset   Tof S42-S21
  sci->tof_a4 = 0.; // [ps] offset   Tof S81-S21

  // for VFTX
  sci->vftx_offset_2141  =  -203.1; //ns test pulse simulating 150 ns TOF
  sci->vftx_offset_2241  =  -155.8; //ns test pulse simulating 150 ns TOF
  sci->vftx_offset_2142  =  -190.6; //ns test pulse simulating 150 ns TOF
  sci->vftx_offset_2242  =  -156.0 + 3.0 + 8.0; //ns test pulse simulating 150 ns TOF
  sci->vftx_offset_218  =  -187.29; //ns // DUMMY needs calibration
  sci->vftx_offset_228  =  -170.2; //ns // DUMMY needs calibration
  
  // for multihitTDC
  sci->mhtdc_factor_ch_to_ns =  0.025;// tp be set in parameter...
  sci->mhtdc_offset_21l_21r  =  -39.6625+20.0 -48.0; //-48 is added for 2021JuneBARB file 230
  sci->mhtdc_factor_21l_21r = 62.5341;  // pos = offset + factor*dt
  sci->mhtdc_offset_41l_41r  =  584.927;          sci->mhtdc_factor_41l_41r = 69.4128; // pos = offset + factor*dt
  sci->mhtdc_offset_42l_42r  =  0.0;              sci->mhtdc_factor_42l_42r = 60.0; // pos = offset + factor*dt
  sci->mhtdc_offset_43l_43r  =  0.0;              sci->mhtdc_factor_43l_43r = 60.0; // pos = offset + factor*dt
  sci->mhtdc_offset_31l_31r  =  910.7;             sci->mhtdc_factor_31l_31r = 60.0; // pos = offset + factor*dt
  sci->mhtdc_offset_81l_81r  =  -410.411;         sci->mhtdc_factor_81l_81r = 43.691; // pos = offset + factor*dt
  sci->mhtdc_offset_22l_22r  =  -39.6625+20.0;    sci->mhtdc_factor_22l_22r = 62.5341;  // pos = offset + factor*dt
  sci->mhtdc_offset_M01l_M01r  =  338.677 + 650 + 14.0;    sci->mhtdc_factor_M01l_M01r = 52.6692; //rough guess with scattered particles
  sci->mhtdc_offset_41_21  =  -9.95+171.4 ; //ns //s450 208Pb
  sci->mhtdc_offset_42_21  =  -7.53+171.5; //ns // s452 Pb 210311
  sci->mhtdc_offset_43_21  =  0.0; //ns
  sci->mhtdc_offset_31_21  =  85.0; //ns
  sci->mhtdc_offset_81_21  =  -400.0 + 165.214; //ns
  sci->mhtdc_offset_41_22  =  -44.91+203.3; //ns //s526 107Ag it was 253.3ns
  sci->mhtdc_offset_M01_21  =  -543.38095 + (681.88795 - 628.5) - 7.552; //ns 08.09.2021
  sci->mhtdc_offset_M01_22  =  0.0; //ns

  //---- initial value for Z vs AoQ PID -----//
  id->ID_Z_AoverQ_num[0]=5;
  id->ID_Z_AoverQ_num[1]=5;
  id->ID_Z_AoverQ_num[2]=5;
  id->ID_Z_AoverQ_num[3]=5;
  id->ID_Z_AoverQ_num[4]=5;

  // 73Kr for 73Rb setting
  id->ID_Z_AoverQ[0][0][0]=1.980      ; id->ID_Z_AoverQ[0][0][1]=37.1;
  id->ID_Z_AoverQ[0][1][0]=2.002      ; id->ID_Z_AoverQ[0][1][1]=37.1;
  id->ID_Z_AoverQ[0][2][0]=2.002      ; id->ID_Z_AoverQ[0][2][1]=36.1;
  id->ID_Z_AoverQ[0][3][0]=1.980      ; id->ID_Z_AoverQ[0][3][1]=36.1 ;
  id->ID_Z_AoverQ[0][4][0]=1.980      ; id->ID_Z_AoverQ[0][4][1]=37.1;

  // 88Tc
  id->ID_Z_AoverQ[1][0][0]=2.03; id->ID_Z_AoverQ[1][0][1]=43.9;
  id->ID_Z_AoverQ[1][1][0]=2.05; id->ID_Z_AoverQ[1][1][1]=43.9;
  id->ID_Z_AoverQ[1][2][0]=2.05; id->ID_Z_AoverQ[1][2][1]=42.8;
  id->ID_Z_AoverQ[1][3][0]=2.03; id->ID_Z_AoverQ[1][3][1]=42.8;
  id->ID_Z_AoverQ[1][4][0]=2.03; id->ID_Z_AoverQ[1][4][1]=43.9;

  // all below Z=32
  id->ID_Z_AoverQ[2][0][0]=1.90; id->ID_Z_AoverQ[2][0][1]=25.;
  id->ID_Z_AoverQ[2][1][0]=1.90; id->ID_Z_AoverQ[2][1][1]=31.65;
  id->ID_Z_AoverQ[2][2][0]=2.3; id->ID_Z_AoverQ[2][2][1]=31.65;
  id->ID_Z_AoverQ[2][3][0]=2.3; id->ID_Z_AoverQ[2][3][1]=25.;
  id->ID_Z_AoverQ[2][4][0]=1.90; id->ID_Z_AoverQ[2][4][1]=25.;
  
  // 81Br
  id->ID_Z_AoverQ[3][0][0]=2.01; id->ID_Z_AoverQ[3][0][1]=34.5;
  id->ID_Z_AoverQ[3][1][0]=2.03; id->ID_Z_AoverQ[3][1][1]=34.5;
  id->ID_Z_AoverQ[3][2][0]=2.03; id->ID_Z_AoverQ[3][2][1]=35.3;
  id->ID_Z_AoverQ[3][3][0]=2.01; id->ID_Z_AoverQ[3][3][1]=35.3;
  id->ID_Z_AoverQ[3][4][0]=2.01; id->ID_Z_AoverQ[3][4][1]=34.5;

  // Rb
  id->ID_Z_AoverQ[4][0][0]=1.90; id->ID_Z_AoverQ[4][0][1]=37.4;
  id->ID_Z_AoverQ[4][1][0]=1.90; id->ID_Z_AoverQ[4][1][1]=38.1;
  id->ID_Z_AoverQ[4][2][0]=2.3; id->ID_Z_AoverQ[4][2][1]=38.1;
  id->ID_Z_AoverQ[4][3][0]=2.3; id->ID_Z_AoverQ[4][3][1]=37.4;
  id->ID_Z_AoverQ[4][4][0]=1.90; id->ID_Z_AoverQ[4][4][1]=37.4;

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


  Float_t my_cID_dEToF_points[4][2] =
    {{    0.,    0.},
     {    0., 4000.},
     {40000., 4000.},
     {40000.,    0.}};
  an->SetupPolyCond("cID_dEToF", 4, my_cID_dEToF_points);

  //======
  //LaBr
  //======
   labr->labr_factor_2_1 = 0.;
   labr->labr_factor_2_2 = 0.;
   labr->labr_factor_2_3 = 0.;
   labr->labr_factor_2_4 = 0.;
   labr->labr_factor_2_5 = 0.;
   labr->labr_factor_2_6 = 0.;
   labr->labr_factor_2_7 = 0.;
   labr->labr_factor_2_8 = 0.;

   labr->labr_factor_1_1 = 1.;
   labr->labr_factor_1_2 = 1.;
   labr->labr_factor_1_3 = 1.;
   labr->labr_factor_1_4 = 1.;
   labr->labr_factor_1_5 = 1.;
   labr->labr_factor_1_6 = 1.;
   labr->labr_factor_1_7 = 1.;
   labr->labr_factor_1_8 = 1.;
  
   labr->labr_offset1 = 0.;
   labr->labr_offset2 = 0.;
   labr->labr_offset3 = 0.;
   labr->labr_offset4 = 0.;
   labr->labr_offset5 = 0.;
   labr->labr_offset6 = 0.;
   labr->labr_offset7 = 0.;
   labr->labr_offset8 = 0.;

  //=======
  //  Si
  //=======

  si->si_factor1=5.82775; //CH 03/06/2016
  si->si_offset1=-381.593; //CH 03/06/2016

  si->si_factor2=3.809; //CH 18.10.2014
  si->si_offset2=-529.01; //CH 18.10.2014

  si->si_factor3=3.2596; //CH 21.05.2016
  si->si_offset3=-550.59; //CH 21.05.2016|

  si->si_factor4=3.2596; //CH 21.05.2016
  si->si_offset4=-550.59; //CH 21.05.2016

  for(int i = 0; i<32; i++){
    si->dssd_factor_det1[i]=1.;
    si->dssd_factor_det2[i]=1.;
    si->dssd_factor_det3[i]=1.;
    si->dssd_factor_det4[i]=1.;
    si->dssd_factor_det5[i]=1.;
    si->dssd_factor_det6[i]=1.;

    si->dssd_factor2_det1[i]=0.;
    si->dssd_factor2_det2[i]=0.;
    si->dssd_factor2_det3[i]=0.;
    si->dssd_factor2_det4[i]=0.;
    si->dssd_factor2_det5[i]=0.;
    si->dssd_factor2_det6[i]=0.;

    si->dssd_offset_det1[i]=0.;
    si->dssd_offset_det2[i]=0.;
    si->dssd_offset_det3[i]=0.;
    si->dssd_offset_det4[i]=0.;
    si->dssd_offset_det5[i]=0.;
    si->dssd_offset_det6[i]=0.;
  }

  //=========
  //MR-TOF-MS
  //=========

  mrtof->MRTOFMS_a=0.069;
  mrtof->MRTOFMS_b=0.71;
  mrtof->MRTOFMS_t0=0;
  mrtof->MRTOFMS_tFRS=0;

  //=========
  //range
  //=========
  range->s4_matter = 1700.0; //mg/cm2
  range->s41_deg_matter = 0.0; //mg/cm2
  range->degrader_rho = 2670; // mg/cm3
  //disk
  range->wedge_disk_in = false;
  range->wedge_disk_sum_thick = 3.6720947; // in mm
  range->wedge_disk_slope = -16./1000.; //mrad/1000
  //wedge
  range->plate_1_in = true;
  range->plate_2_in = true;
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
