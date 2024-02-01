#include "FrsCal2Hit.h"
#include "c4Logger.h"
#include "FrsMainData.h"
#include "FrsMainCalData.h"
#include "FrsHitData.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "FairTask.h"

#include "TClonesArray.h"
#include "TMath.h"
#include <vector>
#include <iostream>

#include "../../config/frs_config.h"

FrsCal2Hit::FrsCal2Hit()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fCalArrayMain(new TClonesArray("FrsMainCalData"))
    ,   fCalArrayTPC(new TClonesArray("FrsTPCCalData"))
    ,   fCalArrayUser(new TClonesArray("FrsUserCalData"))
    ,   fCalArrayVFTX(new TClonesArray("FrsVFTXCalData"))
    ,   fHitArray(new TClonesArray("FrsHitData"))
{
}

FrsCal2Hit::FrsCal2Hit(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fCalArrayMain(new TClonesArray("FrsMainCalData"))
    ,   fCalArrayTPC(new TClonesArray("FrsTPCCalData"))
    ,   fCalArrayUser(new TClonesArray("FrsUserCalData"))
    ,   fCalArrayVFTX(new TClonesArray("FrsVFTXCalData"))
    ,   fHitArray(new TClonesArray("FrsHitData"))
{
}


FrsCal2Hit::~FrsCal2Hit()
{   
    c4LOG(info, "Deleting FrsCal2Hit task");
    if (fCalArrayMain) delete fCalArrayMain;
    if (fCalArrayTPC) delete fCalArrayTPC;
    if (fCalArrayUser) delete fCalArrayUser;
    if (fCalArrayVFTX) delete fCalArrayVFTX;
    if (fHitArray) delete fHitArray;
}

void FrsCal2Hit::SetParameters()
{   
    frs = new TFRSParameter;
    mw = new TMWParameter;
    tpc = new TTPCParameter;
    music = new TMUSICParameter;
    labr = new TLABRParameter;
    sci = new TSCIParameter;
    id = new TIDParameter;
    si = new TSIParameter;
    mrtof = new TMRTOFMSParameter;
    range = new TRangeParameter;

    // CEJ: assuming we can read this somehow so we don't need to copy it across? 
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
    frs->bfield[0] = 14.5368;    // 238U, 1000 MeV/u, eng run  
    frs->bfield[1] = 14.5368;    // 238U, 1000 MeV/u, eng run
    frs->bfield[2] = 13.9572;   //  238U, 1000 MeV/u, eng run 
    frs->bfield[3] = 13.8315;   //  238U, 1000 MeV/u, eng run
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
    id->mhtdc_length_sc2141 = 36.68196; // SCI 21-41 s450
    id->mhtdc_length_sc2241 = 35.227152; // SCI 22-41 s450 208Pb
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
    music->max_tdc_music1 =    4096; //tum music
    music->max_tdc_music2 =    4096; //tum music
    music->max_tdc_music3 = 0x10000; //travel music
    music->max_tdc_music4 =    4096; //tum music

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
    
    //  MUSIC41 velocity 12.05.2022 208Pb, s450
    id->vel_a[0] =   11588.7; //  MUSIC41 velocity corr. 
    id->vel_a[1] =   -18321.8;   // 
    id->vel_a[2] =   8528.11; // 
    id->vel_a[3] =   0.0;

    // MUSIC42 velocity 12.05.2022 208Pb
    id->vel_a2[0] =  12837.8; 
    id->vel_a2[1] = -21519.3;
    id->vel_a2[2] =  10434.3;
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
    tpc->lim_timeref[1][0] = 5000.0; tpc->lim_timeref[1][1] = 48000.0;//time ref (sc21) changed to narrow gate, 2023-Nov-28
    tpc->lim_timeref[2][0] = 1000.0; tpc->lim_timeref[2][1] = 48500.0;//time ref (sc22)
    tpc->lim_timeref[3][0] = 5000.0; tpc->lim_timeref[3][1] = 20000.0;//time ref (sc31) changed to narrow gate, 2023-Nov-28
    tpc->lim_timeref[4][0] = 5000.0; tpc->lim_timeref[4][1] = 20000.0;//time ref (sc41) changed to narrow gate, 2023-Nov-28
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
    tpc->y_offset[0][0] = -55.037378 -0.6 -1.5;
    tpc->y_factor[0][0] = 0.003956; //vacuum tpc is drift to bottom. positive y-factor
    tpc->y_offset[0][1] = -55.193154 -0.6 -1.5;
    tpc->y_factor[0][1] = 0.003953;
    tpc->y_offset[0][2] = -56.659256 -0.6 -1.5;
    tpc->y_factor[0][2] = 0.004082;
    tpc->y_offset[0][3] = -55.009200 -0.6 -1.5;
    tpc->y_factor[0][3] = 0.003934;
    
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
    tpc->y_offset[1][0] = -57.558218 +1.4 -3.0;
    tpc->y_factor[1][0] = 0.004107;   //vacuum tpc is drift to bottom. positive y-factor
    tpc->y_offset[1][1] = -56.781388 +1.4 -3.0;
    tpc->y_factor[1][1] = 0.004016;
    tpc->y_offset[1][2] = -57.216335 +1.4 -3.0;
    tpc->y_factor[1][2] = 0.004024;
    tpc->y_offset[1][3] = -56.691696 +1.4 -3.0;
    tpc->y_factor[1][3] = 0.004046;
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
    tpc->y_offset[3][0] = 57.682383-1.5+9.0+(1.706-6.991)+1.2;
    tpc->y_factor[3][0] = -0.004033; //air tpc is drift to top. negative y-factor
    tpc->y_offset[3][1] = 58.217353-1.5+9.0+(1.706-6.991)+1.2;
    tpc->y_factor[3][1] = -0.004044;
    tpc->y_offset[3][2] = 57.839351-1.5+9.0+(1.706-6.991)+1.2;
    tpc->y_factor[3][2] = -0.004039;
    tpc->y_offset[3][3] = 57.901361-1.5+9.0+(1.706-6.991)+1.2;
    tpc->y_factor[3][3] = -0.004029;

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
    tpc->x_offset[4][0] = -0.657524+2.0 +1.8-3.8-0.25;// 19/June/2021
    tpc->x_factor[4][0] = 0.007779*12./11.;
    tpc->x_offset[4][1] = -1.806150+2.0 +1.8-3.8-0.25; // 19/June/2021//trust more final grid in front of IC, and correct for TPC41/42
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
    tpc->x_offset[5][0] = 2.821206-2.0 +8.0 -1.8-4.5-0.2; // 19/June/2021
    tpc->x_factor[5][0] = 0.007828*24./23.;
    tpc->x_offset[5][1] = 1.989353-2.0 +8.0 -1.8-4.5-0.2; // 19/June/2021 //trust more final grid in front of IC, and correct for TPC41/42
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
    //TOF_SC41_SC21_TAC 12.05.22 Pb s450, beta 0.74 to 0.87, 5 points 
    id->id_tofoff2 =  197454.8;  // offset (ps)
    id->id_path2   =  122486.0;  // path/c (ps)
    
    //TOF_SC42_SC21_TAC 12.05.22 Pb s450
    id->id_tofoff3  = 196914.0;   // offset (ps)
    id->id_path3    = 125574.9;   // path/c [ps
    
    // TOF calibration SC21-SC81 (TAC)
    id->id_tofoff4  = 326337.1;   //SC21-81 [ps]          // quickly done from run156 and 166 (2019/Nov, YT)
    id->id_path4    = 246983.1;   //SC21-81  path/c [ps]  // quickly done from run156 and 166 (2019/Nov, YT)

    //TOF_SC41_SC22_TAC 12.05.22 Pb s450
    id->id_tofoff5 =  187952.5;  // offset (ps) 
    id->id_path5   =  117471.1;  // path/c (ps)
    
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
    sci->mhtdc_offset_41_21  =  171.4 ; //ns //s450 208Pb
    sci->mhtdc_offset_42_21  =  171.5; //ns // s452 Pb 210311
    sci->mhtdc_offset_43_21  =  0.0; //ns
    sci->mhtdc_offset_31_21  =  85.0; //ns
    sci->mhtdc_offset_81_21  =  -400.0 + 165.214; //ns
    sci->mhtdc_offset_41_22  =  203.3; //ns //s526 107Ag it was 253.3ns
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


    // CEJ: this bit doesn't work so well with copy/pasting FRS setup file..
    // for now we comment out, find a way to read file and exclude? or grab specific bits?
    /*
    Float_t my_cID_dEToF_points[4][2] =
        {{    0.,    0.},
        {    0., 4000.},
        {40000., 4000.},
        {40000.,    0.}};
    an->SetupPolyCond("cID_dEToF", 4, my_cID_dEToF_points);
    */

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

}

void FrsCal2Hit::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}


InitStatus FrsCal2Hit::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    fCalArrayMain = (TClonesArray*)mgr->GetObject("FrsMainCalData");
    c4LOG_IF(fatal, !fCalArrayMain, "FrsMainCalData branch not found!");

    fCalArrayTPC = (TClonesArray*)mgr->GetObject("FrsTPCCalData");
    c4LOG_IF(fatal, !fCalArrayTPC, "FrsTPCCalData branch not found!");

    fCalArrayUser = (TClonesArray*)mgr->GetObject("FrsUserCalData");
    c4LOG_IF(fatal, !fCalArrayUser, "FrsUserCalData branch not found!");

    fCalArrayVFTX = (TClonesArray*)mgr->GetObject("FrsVFTXCalData");
    c4LOG_IF(fatal, !fCalArrayVFTX, "FrsVFTXCalData branch not found!");

    mgr->Register("FrsHitData", "FRS Hit Data", fHitArray, !fOnline);

    SetParameters();
    Setup_Conditions();

    fCalArrayMain->Clear();
    fCalArrayTPC->Clear();
    fHitArray->Clear();

    return kSUCCESS;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus FrsCal2Hit::ReInit()
{
    SetParContainers();
    SetParameters();
    return kSUCCESS;
}

void FrsCal2Hit::Exec(Option_t* option)
{   
    int multMain = fCalArrayMain->GetEntriesFast();
    int multTPC = fCalArrayTPC->GetEntriesFast();
    int multUser = fCalArrayUser->GetEntriesFast();
    int multVFTX = fCalArrayVFTX->GetEntriesFast();
    
    if (!multMain || !multTPC || !multUser || !multVFTX) return;

    fNEvents++;
    // this mult thing is nonsense i'm sure
    fCalHitMain = (FrsMainCalData*)fCalArrayMain->At(multMain-1);
    fCalHitTPC = (FrsTPCCalData*)fCalArrayTPC->At(multTPC-1);
    fCalHitUser = (FrsUserCalData*)fCalArrayUser->At(multUser-1);
    fCalHitVFTX = (FrsVFTXCalData*)fCalArrayVFTX->At(multVFTX-1);

    WR_TS = fCalHitMain->Get_WR();

    /* ---------------------------------------------------- */
    // Start of MUSIC analysis                              //
    /* ---------------------------------------------------- */

    music_e1 = fCalHitUser->Get_music_e1();
    music_e2 = fCalHitUser->Get_music_e2();
    music_t1 = fCalHitMain->Get_music_t1();
    music_t2 = fCalHitMain->Get_music_t2();
    // we don't use music 3

    music1_anodes_cnt = 0;
    music2_anodes_cnt = 0;

    /* reset de[i] and de_cor[i] etc */

    for (int i = 0; i < 8; i++)
    {
        /*  8 anodes of TUM MUSIC */
        // first MUSIC
        if (music_e1[i] > 5)
        {
            music_b_e1[i] = Check_WinCond_Multi(music_e1[i], cMusic1_E, i);
            if (music_b_e1[i])
            {
                music1_anodes_cnt++;
            }
        }
        if (music_t1[i] > 0)
        {
            music_b_t1[i] = Check_WinCond_Multi(music_t1[i], cMusic1_T, i);
        }

        // second MUSIC
        if (music_e2[i] > 5)
        {
            music_b_e2[i] = Check_WinCond_Multi(music_e2[i], cMusic2_E, i);
            if (music_b_e2[i])
            {
                music2_anodes_cnt++;
            }
        }
        if (music_t2[i] > 0)
        {
            music_b_t2[i] = Check_WinCond_Multi(music_t2[i], cMusic2_T, i);
        }
    }

    /*for (int i = 0; i < 4; i++)
    {
        // 4 anodes of MUSIC OLD
        // third MUSIC travelling
        if (music_e3[i] > 0)
        {
            music_b_e3[i] = Check_WinCond_Multi(music_e3[i], cMusic3_E, i);
            if (music_b_e3[i])
            {
                music3_anodes_cnt++;
            }
        }
        if (music_t3[i] > 0)
        {
            music_b_t3[i] = Check_WinCond_Multi(music_t3[i], cMusicT_3, i);
        }
    }*/

    if (music1_anodes_cnt == 8)
    {
        Float_t r1 = ((music_e1[0]) * music->e1_gain[0] + music->e1_off[0]) * ((music_e1[1]) * music->e1_gain[1] + music->e1_off[1]);
        Float_t r2 = ((music_e1[2]) * music->e1_gain[2] + music->e1_off[2]) * ((music_e1[3]) * music->e1_gain[3] + music->e1_off[3]);
        Float_t r3 = ((music_e1[4]) * music->e1_gain[4] + music->e1_off[4]) * ((music_e1[5]) * music->e1_gain[5] + music->e1_off[5]);
        Float_t r4 = ((music_e1[6]) * music->e1_gain[6] + music->e1_off[6]) * ((music_e1[7]) * music->e1_gain[7] + music->e1_off[7]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            b_de1 = kTRUE;
            de[0] = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            de_cor[0] = de[0];
        }
    }

    if (music2_anodes_cnt == 8)
    {
        Float_t r1 = ((music_e2[0]) * music->e2_gain[0] + music->e2_off[0]) * ((music_e2[1]) * music->e2_gain[1] + music->e2_off[1]);
        Float_t r2 = ((music_e2[2]) * music->e2_gain[2] + music->e2_off[2]) * ((music_e2[3]) * music->e2_gain[3] + music->e2_off[3]);
        Float_t r3 = ((music_e2[4]) * music->e2_gain[4] + music->e2_off[4]) * ((music_e2[5]) * music->e2_gain[5] + music->e2_off[5]);
        Float_t r4 = ((music_e2[6]) * music->e2_gain[6] + music->e2_off[6]) * ((music_e2[7]) * music->e2_gain[7] + music->e2_off[7]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            b_de2 = kTRUE;
            de[1] = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            de_cor[1] = de[1];
        }
    }

    // CEJ: 8 in go4, but how can it be 8?
    /*if (music3_anodes_cnt == 8)
    {
        Float_t r1 = ((music_e3[0]) * music->e3_gain[0] + music->e3_off[0]) * ((music_e3[1]) * music->e3_gain[1] + music->e3_off[1]);
        Float_t r2 = ((music_e3[2]) * music->e3_gain[2] + music->e3_off[2]) * ((music_e3[3]) * music->e3_gain[3] + music->e3_off[3]);

        if ((r1 > 0) && (r2 > 0))
        {
            // b_de3 = kTRUE;
            de[2] = sqrt(sqrt(r1) * sqrt(r2));
            de_cor[2] = de[2];
        }
    }*/

    // Position (X) correction by TPC //
    // this should not be in the music3_anodes_cnt if{}
    // but it is in our Go4
    
    
    b_tpc_xy = fCalHitTPC->Get_b_tpc_xy(); // maybe this should be outside? JEL: Yep this must go here!
    
    
    if (b_tpc_xy[4] && b_tpc_xy[5])
    {
        music1_x_mean = fCalHitTPC->Get_tpc_music41_x();
        music2_x_mean = fCalHitTPC->Get_tpc_music42_x();
        //music3_x_mean = fCalHitTPC->Get_tpc_music43_x();

        if (b_de1)
        {
            power = 1.;
            Corr = 0.;
            for (int i = 0; i < 4; i++)
            {
                Corr += music->pos_a1[i] * power;
                power *= music1_x_mean;
            }
            if (Corr != 0)
            {
                Corr = music->pos_a1[0] / Corr;
                de_cor[0] = de[0] * Corr;
            }
        }

        if (b_de2)
        {
            power = 1.;
            Corr = 0.;
            for (int i = 0; i < 4; i++)
            {
                Corr += music->pos_a2[i] * power;
                power *= music2_x_mean;
            }
            if (Corr != 0)
            {
                Corr = music->pos_a2[0] / Corr;
                de_cor[1] = de[1] * Corr;
            }
        }
        
        /*if (b_de3)
        {
            power = 1.;
            Corr = 0.;
            for (int i = 0; i < 4; i++)
            {
                Corr += music->pos_a3[i] * power;
                power *= music3_x_mean;
            }
            if (Corr != 0)
            {
                Corr = music->pos_a3[0] / Corr;
                de_cor[2] = de[2] * Corr;
            }
        }*/
    }
    
    /* ----------------------------------------------- */
    // Start of Scintillator Analysis
    /* ----------------------------------------------- */

    
    // V1290
    for (int i = 0; i<15; i++) tdc_array[i] = fCalHitMain->Get_TDC_channel(i);

    // In Raw2Cal we should make sure no zeros are added to vector     
    // CEJ: 24/01/24 possibly vectors don't work here since [i] hit should match to [i] hit in l/r?
    // SCI 21 L and R
    for (int i = 0; i < tdc_array[2].size(); i++)
    {      
        if (!(tdc_array[2].size()>0 && tdc_array[3].size() > 0)) continue;
        // CEJ: maybe all of this can be rewritten to use vectors..figure out later
        mhtdc_sc21lr_dt.emplace_back(sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[2].at(i) - tdc_array[3].at(i)));
        mhtdc_sc21lr_x.emplace_back(mhtdc_sc21lr_dt.at(i) * sci->mhtdc_factor_21l_21r + sci->mhtdc_offset_21l_21r);
    }
    // always check these conditions (go4 does it 10x without if-statement)
    float sc21pos_from_tpc = -999.9;
    if (b_tpc_xy[0] && b_tpc_xy[1])
    {
        sc21pos_from_tpc = fCalHitTPC->Get_tpc21_22_sc21_x();
    }
    else if (b_tpc_xy[2] && b_tpc_xy[3])
    {
        sc21pos_from_tpc = fCalHitTPC->Get_tpc23_24_sc21_x();
    }

    // SCI 22 L and R
    for (int i = 0; i < tdc_array[12].size(); i++)
    {
        if (!(tdc_array[12].size()>0 && tdc_array[13].size() > 0)) continue;
        mhtdc_sc22lr_dt.emplace_back(sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[12].at(i) - tdc_array[13].at(i)));
        mhtdc_sc22lr_x.emplace_back(mhtdc_sc22lr_dt.at(i) * sci->mhtdc_factor_22l_22r + sci->mhtdc_offset_22l_22r);
        if (i == 0)
        {
            // only do this if there is a case for 22l and 22r != 0. we don't need to do it 10x though
            float sc22pos_from_tpc = -999.9;
            if (b_tpc_xy[0] && b_tpc_xy[1])
            {
                sc22pos_from_tpc = fCalHitTPC->Get_tpc21_22_sc22_x();
            }
            else if (b_tpc_xy[2] && b_tpc_xy[3])
            {
                sc22pos_from_tpc = fCalHitTPC->Get_tpc23_24_sc22_x();
            }
        }
    }
    
    
    // only take first hit (?) for 41, 42, 43, 31, 81
    if (tdc_array[0].size() > 0 && tdc_array[1].size() > 0)
    {
        mhtdc_sc41lr_dt = sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[0].at(0) - tdc_array[1].at(0));
        mhtdc_sc41lr_x = mhtdc_sc41lr_dt * sci->mhtdc_factor_41l_41r + sci->mhtdc_offset_41l_41r;
    }
    if (tdc_array[4].size() > 0 && tdc_array[14].size() > 0)
    {
        mhtdc_sc42lr_dt = sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[4].at(0) - tdc_array[14].at(0));
        mhtdc_sc42lr_x = mhtdc_sc42lr_dt * sci->mhtdc_factor_42l_42r + sci->mhtdc_offset_42l_42r;
    }
    if (tdc_array[5].size() > 0 && tdc_array[6].size() > 0)
    {
        mhtdc_sc43lr_dt = sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[5].at(0) - tdc_array[6].at(0));
        mhtdc_sc43lr_x = mhtdc_sc43lr_dt * sci->mhtdc_factor_43l_43r + sci->mhtdc_offset_43l_43r;
    }
    if (tdc_array[9].size() > 0 && tdc_array[10].size() > 0)
    {
        mhtdc_sc31lr_dt = sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[9].at(0) - tdc_array[10].at(0));
        mhtdc_sc31lr_x = mhtdc_sc31lr_dt * sci->mhtdc_factor_31l_31r + sci->mhtdc_offset_31l_31r;
    }
    if (tdc_array[7].size() > 0 && tdc_array[8].size() > 0)
    {
        mhtdc_sc81lr_dt = sci->mhtdc_factor_ch_to_ns * (rand3() + tdc_array[7].at(0) - tdc_array[8].at(0));
        mhtdc_sc81lr_x = mhtdc_sc81lr_dt * sci->mhtdc_factor_81l_81r + sci->mhtdc_offset_81l_81r;
    }


    if (tdc_array[0].size() > 0 && tdc_array[1].size() > 0)
    {   
        // 21 -> 41
        if (tdc_array[3].size() > 0 && tdc_array[2].size() > 0){
        for (int i = 0; i < tdc_array[2].size(); i++)
        {
            mhtdc_tof4121.emplace_back(sci->mhtdc_factor_ch_to_ns * (0.5 * (tdc_array[0].at(0) + tdc_array[1].at(0)) - 0.5 * (tdc_array[2].at(i) + tdc_array[3].at(i))) + sci->mhtdc_offset_41_21);
        }
        }

        // 22 -> 41
        if (tdc_array[12].size() > 0 && tdc_array[13].size() > 0){
        for (int i = 0; i < tdc_array[12].size(); i++)
        {
            mhtdc_tof4122.emplace_back(sci->mhtdc_factor_ch_to_ns * (0.5 * (tdc_array[0].at(0) + tdc_array[1].at(0)) - 0.5 * (tdc_array[12].at(i) + tdc_array[13].at(i))) + sci->mhtdc_offset_41_22);
        }
        }
    }


    if ((tdc_array[2].size() > 0 ) && (tdc_array[0].size() > 0) && (tdc_array[1].size() > 0))
    {
        if (tdc_array[3].size() > 0) // CEJ should be implicitly true or this all falls apart..
        {
            // 21 -> 42
            if (tdc_array[4].size() > 0 && tdc_array[14].size() > 0)
            {
                mhtdc_tof4221 = sci->mhtdc_factor_ch_to_ns * (0.5 * (tdc_array[0].at(0) + tdc_array[1].at(0)) - 0.5 * (tdc_array[4].at(0) + tdc_array[14].at(0))) + sci->mhtdc_offset_42_21;
            }
            
            // 21 -> 43
            if (tdc_array[5].size() > 0 && tdc_array[6].size() > 0)
            {
                mhtdc_tof4321 = sci->mhtdc_factor_ch_to_ns * (0.5 * (tdc_array[0].at(0) + tdc_array[1].at(0)) - 0.5 * (tdc_array[5].at(0) + tdc_array[6].at(0))) + sci->mhtdc_offset_43_21;
            }

            // 21 -> 31
            if (tdc_array[9].size() > 0 && tdc_array[10].size() > 0)
            {
                mhtdc_tof3121 = sci->mhtdc_factor_ch_to_ns * (0.5 * (tdc_array[0].at(0) + tdc_array[1].at(0)) - 0.5 * (tdc_array[9].at(0) + tdc_array[10].at(0))) + sci->mhtdc_offset_31_21;
            }

            // 21 -> 81
            if (tdc_array[7].size() > 0 && tdc_array[8].size() > 0)
            {
                mhtdc_tof8121 = sci->mhtdc_factor_ch_to_ns * (0.5 * (tdc_array[0].at(0) + tdc_array[1].at(0)) - 0.5 * (tdc_array[7].at(0) + tdc_array[8].at(0))) + sci->mhtdc_offset_81_21;
            }
        }
    }
    

    de_array = fCalHitMain->Get_De_array();
    dt_array = fCalHitUser->Get_dt_array();


    c4LOG_IF(fatal, (de_array == nullptr) || (dt_array == nullptr), "These two arrays are not declared correctly." );

    dt_21l_21r = dt_array[0];
    dt_41l_41r = dt_array[1];
    dt_42l_42r = dt_array[2];
    dt_43l_43r = dt_array[3];
    dt_81l_81r = dt_array[4];
    dt_21l_41l = dt_array[5];
    dt_21r_41r = dt_array[6];
    dt_42r_21r = dt_array[7];
    dt_42l_21l = dt_array[8];
    dt_21l_81l = dt_array[9];
    dt_21r_81r = dt_array[10];
    dt_22l_22r = dt_array[11];
    dt_22l_41l = dt_array[12];
    dt_22r_41r = dt_array[13];
    dt_22l_81l = dt_array[14];
    dt_22r_81r = dt_array[15];

    // 2 in go4, 0 now?
    sci_l[0] = de_array[1]; // de_21l;
    sci_r[0] = de_array[2]; // de_21r;
    sci_tx[0] = dt_21l_21r + rand3();

    // 3 in go4, 1 now?
    sci_l[1] = de_array[13]; // de_22l
    sci_r[1] = de_array[6]; // de_22r
    sci_tx[1] = dt_22l_22r + rand3();

    // 5 in go4, 2 now?
    sci_l[2] = de_array[0]; // de_41l
    sci_r[2] = de_array[11]; // de_41r;
    sci_tx[2] = dt_41l_41r + rand3();

    // 6 in go4, 3 now?
    sci_l[3] = de_array[3]; // de_42l
    sci_r[3] = de_array[4]; // de_42r
    sci_tx[3] = dt_42l_42r + rand3();

    // 7 in go4, 4 now?
    sci_l[4] = de_array[9]; // de_43l
    sci_r[4] = de_array[10]; // de_43r
    sci_tx[4] = dt_43l_43r + rand3();

    // 10 in go4, 5 now?
    sci_l[5] = de_array[5]; // de_81l
    sci_r[5] = de_array[12]; // de_81r
    sci_tx[5] = dt_81l_81r + rand3();


    for (int i = 0; i < 6; i++)
    {   
        // find a way to read in cConditons
        // 'posref' in go4 does nothing
        
        // what even is this code:?
        int j;
        switch(i)
        {
            case 0:
                j = 2;
                break;
            case 1:
                j = 3;
                break;
            case 2:
                j = 5;
                break;
            case 3:
                j = 6;
                break;
            case 4:
                j = 7;
                break;
            case 5:
                j = 10;
                break;
            default:
                j = 2;
        }

        sci_b_l[i] = Check_WinCond(sci_l[i], cSCI_L);
        sci_b_r[i] = Check_WinCond(sci_r[i], cSCI_R);

        if (sci_b_l[i] && sci_b_r[i])
        {
            sci_e[i] = (sci_r[i] - sci->re_a[0][j]);
            sci_b_e[i] = Check_WinCond(sci_e[i], cSCI_E);
        }

        /* Position in X direction: */
        sci_b_tx[i] = Check_WinCond(sci_tx[i], cSCI_Tx);
        if (sci_b_tx[i])
        {
            Float_t R = sci_tx[i];
            power = 1.;
            sum = 0.;
            for (int k = 0; k < 7; k++)
            {
                sum += sci->x_a[k][i] * power;
                power *= R;
            }
            sci_x[i] = sum;
            sci_b_x[i] = Check_WinCond(sci_x[i], cSCI_X);
        }
    } // loop for sci values


    /*----------------------------------------------------------*/
    // Calibrated ToF - dt will be in dt_array, from UserCrate
    /*----------------------------------------------------------*/
    sci_tofll2 = dt_21l_41l * sci->tac_factor[2] - sci->tac_off[2];
    sci_tofrr2 = dt_21r_41r * sci->tac_factor[3] - sci->tac_off[3];
    sci_b_tofll2 = Check_WinCond(sci_tofll2, cSCI_LL2);
    sci_b_tofrr2 = Check_WinCond(sci_tofrr2, cSCI_RR2);
    if (sci_b_tofll2 && sci_b_tofrr2)
    {
        sci_tof2 = (sci->tof_bll2 * sci_tofll2 + sci->tof_a2 + sci->tof_brr2 * sci_tofrr2) / 2.0;
        sci_tof2_calib = -1.0 * sci_tof2 + id->id_tofoff2;
    }
    else
    {
        sci_tof2 = 0;
        sci_tof2_calib = 0;
    }

    sci_tofll3 = dt_42l_21l * sci->tac_factor[5] - sci->tac_off[5];
    sci_tofrr3 = dt_42r_21r * sci->tac_factor[6] - sci->tac_off[6];
    sci_b_tofll3 = Check_WinCond(sci_tofll3, cSCI_LL3);
    sci_b_tofrr3 = Check_WinCond(sci_tofrr3, cSCI_RR3);
    if (sci_b_tofll3 && sci_b_tofrr3)
    {
        sci_tof3 = (sci->tof_bll3 * sci_tofll3 + sci->tof_a3 + sci->tof_brr3 * sci_tofrr3) / 2.0;
        sci_tof3_calib = -1.0 * sci_tof3 + id->id_tofoff3;
    }
    else
    {
        sci_tof3 = 0;
        sci_tof3_calib = 0;
    }

    sci_tofll4 = dt_21l_81l * sci->tac_factor[9] - sci->tac_off[9];
    sci_tofrr4 = dt_21r_81r * sci->tac_factor[10] - sci->tac_off[10];
    sci_b_tofll4 = Check_WinCond(sci_tofll4, cSCI_LL4);
    sci_b_tofrr4 = Check_WinCond(sci_tofrr4, cSCI_RR4);
    if (sci_b_tofll4 && sci_b_tofrr4)
    {
        sci_tof4 = (sci->tof_bll4 * sci_tofll4 + sci->tof_a4 + sci->tof_brr4 * sci_tofrr4) / 2.0;
        sci_tof4_calib = -1.0 * sci_tof4 + id->id_tofoff4;
    }
    else
    {
        sci_tof4 = 0;
        sci_tof4_calib = 0;
    }

    sci_tofll5 = dt_22l_41l * sci->tac_factor[12] - sci->tac_off[12];
    sci_tofrr5 = dt_22r_41r * sci->tac_factor[13] - sci->tac_off[13];
    sci_b_tofll5 = Check_WinCond(sci_tofll5, cSCI_LL5);
    sci_b_tofrr5 = Check_WinCond(sci_tofrr5, cSCI_RR5);
    if (sci_b_tofll5 && sci_b_tofrr5)
    {
        sci_tof5 = (sci->tof_bll5 * sci_tofll5 + sci->tof_a5 + sci->tof_brr5 * sci_tofrr5) / 2.0;
        sci_tof5_calib = -1.0 * sci_tof5 + id->id_tofoff5;
    }
    else
    {
        sci_tof5 = 0;
        sci_tof5_calib = 0;
    }

    /*----------------------------------------------------------*/
    // Start of MHTDC ID analysis
    /*----------------------------------------------------------*/

    float temp_s8x = mhtdc_sc81lr_x;
    temp_s4x = -999.;
    if (b_tpc_xy[4] && b_tpc_xy[5])
    {
        temp_s4x = tpc_x_s4;
    }

    float temp_s2x = -999.;
    std::vector<float> temp_s2x_mhtdc;
    float temp_a2 = 0;

    if (id->mhtdc_s2pos_option == 1)
    {
        for (int i = 0; i < mhtdc_sc21lr_x.size(); i++)
        {
            temp_s2x_mhtdc.emplace_back(mhtdc_sc21lr_x[i]);
        }
    }
    else if (id->mhtdc_s2pos_option == 3)
    {
        for (int i = 0; i < mhtdc_sc22lr_x.size(); i++)
        {
            temp_s2x_mhtdc.emplace_back(mhtdc_sc22lr_x[i]);
        }
    }
    else if (id->mhtdc_s2pos_option == 2)
    {
        if (b_tpc_xy[2] && b_tpc_xy[3])
        {
            temp_s2x = fCalHitTPC->Get_tpc_x_s2_foc_23_24();
            temp_a2 = fCalHitTPC->Get_tpc_angle_x_s2_foc_23_24();
        }
        else if (b_tpc_xy[1] && b_tpc_xy[3])
        {
            temp_s2x = fCalHitTPC->Get_tpc_x_s2_foc_22_24();
            temp_a2 = fCalHitTPC->Get_tpc_angle_x_s2_foc_22_24();
        }
        else if (b_tpc_xy[0] && b_tpc_xy[1])
        {
            temp_s2x = fCalHitTPC->Get_tpc_x_s2_foc_21_22();
            temp_a2 = fCalHitTPC->Get_tpc_angle_x_s2_foc_21_22();
        }
    }


    //   S2S4 MultihitTDC ID analysis
    float mean_brho_s2s4 = 0.5 * (frs->bfield[2] + frs->bfield[3]);

    // frs go4 doesn't have this selection
    if (id->mhtdc_s2pos_option == 1)
    {

        if (id->tof_s4_select == 1)
        {
            for (int i = 0; i < mhtdc_tof4121.size(); i++)
            {
                if (mhtdc_tof4121.at(i) > -100)
                {
                    id_mhtdc_beta_s2s4.emplace_back((id->mhtdc_length_sc2141 / mhtdc_tof4121.at(i)) / speed_light);
                }
            }
        }
        else if (id->tof_s4_select == 3)
        {
            for (int i = 0; i < mhtdc_tof4122.size(); i++)
            {
                if (mhtdc_tof4122.at(i) > -100)
                {
                    id_mhtdc_beta_s2s4.emplace_back((id->mhtdc_length_sc2241 / mhtdc_tof4122.at(i)) / speed_light);
                }
            }
        }

        // calculate delta (momentum deviation) and AoQ
        for (int i = 0; i < id_mhtdc_beta_s2s4.size(); i++)
        {
            id_mhtdc_gamma_s2s4.emplace_back(1. / sqrt(1. - id_mhtdc_beta_s2s4.at(i) * id_mhtdc_beta_s2s4.at(i)));
            
            // does this bit just clear arrays? can we just clear vectors at the end of event and skip this?
            /*if (temp_s4x == -999 || temp_s2x_mhtdc[i] == -999)
            {
                id_mhtdc_aoq_s2s4[i] = 0;
                id_mhtdc_aoq_corr_s2s4[i] = 0;
            }*/
            /*else*/ 
            if (temp_s4x > -200. && temp_s4x < 200. && temp_s2x_mhtdc[i] > -200. && temp_s2x_mhtdc[i] < 200.)
            {
                id_mhtdc_delta_s2s4.emplace_back((temp_s4x - (temp_s2x_mhtdc[i] * frs->magnification[1])) / (-1.0 * frs->dispersion[1] * 1000.0)); // metre to mm
                if (id_mhtdc_beta_s2s4.at(i) > 0.0 && id_mhtdc_beta_s2s4.at(i) < 1.0)
                {
                    id_mhtdc_aoq_s2s4.emplace_back(mean_brho_s2s4 * (1. + id_mhtdc_delta_s2s4[i]) * temp_tm_to_MeV / (temp_mu * id_mhtdc_beta_s2s4.at(i) * id_mhtdc_gamma_s2s4[i]));

                    // Gain match AoQ
                    for (int j = 0; j < AoQ_Shift_array; j++)
                    {
                        if (ts_mins >= FRS_WR_i[j] && ts_mins < FRS_WR_j[j])
                        {
                            id_mhtdc_aoq_s2s4.at(i) = (id_mhtdc_aoq_s2s4.at(i) - AoQ_shift_Sci21_value[j]) - 0.029100; // Why isn't this float coded in a config file?
                        }
                    }

                    // No angle correction for SCI
                    id_mhtdc_aoq_corr_s2s4.emplace_back(id_mhtdc_aoq_s2s4.at(i));

                    /*mhtdc_gamma1square.emplace_back(1.0 + TMath::Power(((1.0 / aoq_factor) * (id_brho[0] / id_mhtdc_aoq_s2s4[i])), 2));
                    id_mhtdc_gamma_ta_s2.emplace_back(TMath::Sqrt(mhtdc_gamma1square[i]));
                    id_mhtdc_dEdegoQ.emplace_back((id_mhtdc_gamma_ta_s2[i] - id_mhtdc_gamma_s2s4[i]) * id_mhtdc_aoq_s2s4[i]);

                    // doesn't make sense to do this when we have no id_mhtdc_z_music41 yet..
                    id_mhtdc_dEdeg.emplace_back(id_mhtdc_dEdegoQ[i] * id_mhtdc_z_music41[i]);*/

                }
            }
        }
    }
    else if (id->mhtdc_s2pos_option == 2)
    {
        if (id->tof_s4_select == 1)
        {
            for (int i = 0; i < mhtdc_tof4121.size(); i++)
            {
                if (mhtdc_tof4121[i] > -100)
                {
                    id_mhtdc_beta_s2s4.emplace_back((id->mhtdc_length_sc2141 / mhtdc_tof4121[i]) / speed_light);
                }
            }
        }
        else if (id->tof_s4_select == 3)
        {
            for (int i = 0; i < mhtdc_tof4122.size(); i++)
            {
                if (mhtdc_tof4122[i] > -100)
                {
                    id_mhtdc_beta_s2s4.emplace_back((id->mhtdc_length_sc2241 / mhtdc_tof4122[i]) / speed_light);
                }
            }
        }
        
        // Calculation of velocity beta and gamma
        for (int i = 0; i < id_mhtdc_beta_s2s4.size(); i++)
        {
            id_mhtdc_gamma_s2s4.emplace_back(1. / sqrt(1. - id_mhtdc_beta_s2s4.at(i) * id_mhtdc_beta_s2s4.at(i)));

            // Calculate delta (momentum deviation) and AoQ
            /*if(temp_s4x == -999 || temp_s2x == -999)
            {
                id_mhtdc_aoq_s2s4[i]=0;
                id_mhtdc_aoq_corr_s2s4[i]=0;
            }
            else*/ if (temp_s4x > -200. && temp_s4x < 200. && temp_s2x > -200. && temp_s2x < 200.)
            {   
                // CEJ: this is a pointlessly repeated calculation, takes single value
                id_mhtdc_delta_s2s4.emplace_back((temp_s4x - (temp_s2x * frs->magnification[1])) / (-1.0 * frs->dispersion[1] * 1000.0)); //1000 is dispertsion from meter to mm. -1.0 is sign definition.

                if (id_mhtdc_beta_s2s4.at(i) > 0.0 && id_mhtdc_beta_s2s4.at(i) < 1.0)
                {
                    id_mhtdc_aoq_s2s4.emplace_back(mean_brho_s2s4 *(1. + id_mhtdc_delta_s2s4[i]) * temp_tm_to_MeV / (temp_mu * id_mhtdc_beta_s2s4.at(i) * id_mhtdc_gamma_s2s4.at(i)));
                
                    // Gain match AoQ
                    // ** OLD STARTS BELOW ** //
                    for(int j = 0; j < AoQ_Shift_array; j++)
                    {
                        if(ts_mins >= FRS_WR_i[j] && ts_mins < FRS_WR_j[j])
                        {
                            id_mhtdc_aoq_s2s4.at(i) = id_mhtdc_aoq_s2s4.at(i) - AoQ_shift_TPC_value[j] - 0.01097;
                        }
                    }
                    
                    id_mhtdc_aoq_corr_s2s4.emplace_back(id_mhtdc_aoq_s2s4.at(i) - id->a2AoQCorr * temp_a2);
                    
                    /*mhtdc_gamma1square.emplace_back(1.0 + TMath::Power(((1.0 / aoq_factor) * (id_brho[0] / id_mhtdc_aoq_s2s4[i])), 2));
                    id_mhtdc_gamma_ta_s2.emplace_back(TMath::Sqrt(mhtdc_gamma1square[i]));
                    id_mhtdc_dEdegoQ.emplace_back((id_mhtdc_gamma_ta_s2[i]  - id_mhtdc_gamma_s2s4[i]) * id_mhtdc_aoq_s2s4[i]);
                    // CEJ: again pointless...but done below?
                    id_mhtdc_dEdeg.emplace_back(id_mhtdc_dEdegoQ[i] * id_mhtdc_z_music41[i]);*/
                    
                }
            }
        }
    }

    // Calculation of dE and Z from MUSIC41
    for (int i = 0; i < id_mhtdc_beta_s2s4.size(); i++)
    {
        float temp_music41_de = de[0] > 0.0;
        if ((temp_music41_de > 0.0) && (id_mhtdc_beta_s2s4.at(i) > 0.0) && (id_mhtdc_beta_s2s4.at(i) < 1.0))
        {
            power = 1.;
            sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->mhtdc_vel_a_music41[j];
                power *= id_mhtdc_beta_s2s4.at(i);
                
            }
            id_mhtdc_v_cor_music41.emplace_back(sum);

            if (id_mhtdc_v_cor_music41.at(i) > 0.0)
            {
                id_mhtdc_z_music41.emplace_back(frs->primary_z * sqrt(de[0] / id_mhtdc_v_cor_music41.at(i)) + id->mhtdc_offset_z_music41);
            }
        }
        
    }

    for (int i = 0; i < id_mhtdc_beta_s2s4.size(); i++)
    {
        float temp_music42_de = de[1] > 0.0;
        if((temp_music42_de > 0.0)  && (id_mhtdc_beta_s2s4.at(i) > 0.0) && (id_mhtdc_beta_s2s4.at(i) < 1.0))
        {
            power = 1.;
            sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->mhtdc_vel_a_music42[j];
                power *= id_mhtdc_beta_s2s4.at(i);
            }
            id_mhtdc_v_cor_music42.emplace_back(sum);
            
            if (id_mhtdc_v_cor_music42.at(i)> 0.0)
            {
                id_mhtdc_z_music42.emplace_back(frs->primary_z * sqrt(de[1] / id_mhtdc_v_cor_music42.at(i)) + id->mhtdc_offset_z_music42);
            }
        }
    }

    // Gain match Z
    for (int i = 0; i < Z_Shift_array; i++)
    {   
        // music41 and 42 same size
        for (int j = 0; j < id_mhtdc_z_music41.size(); j++)
        {
            if (ts_mins >= FRS_WR_a[i] && ts_mins < FRS_WR_b[i])
            {
                id_mhtdc_z_music41.at(j) = id_mhtdc_z_music41.at(j) - Z1_shift_value[i];
                id_mhtdc_z_music42.at(j) = id_mhtdc_z_music42.at(j) - Z2_shift_value[i];
            }
        }
    }
    for (int i = 0; i < id_mhtdc_beta_s2s4.size(); i++)
    {
        if (id_mhtdc_aoq_s2s4.at(i) != 0)
        {
            mhtdc_gamma1square.emplace_back(1.0 + TMath::Power(((1.0 / aoq_factor) * (id_brho[0] / id_mhtdc_aoq_s2s4.at(i))), 2));
            id_mhtdc_gamma_ta_s2.emplace_back(TMath::Sqrt(mhtdc_gamma1square.at(i)));
            id_mhtdc_dEdegoQ.emplace_back((id_mhtdc_gamma_ta_s2[i] - id_mhtdc_gamma_s2s4[i]) * id_mhtdc_aoq_s2s4.at(i));
            id_mhtdc_dEdeg.emplace_back(id_mhtdc_dEdegoQ[i] * id_mhtdc_z_music41[i]);
        }
    }


    if (id->x_s2_select == 1)
    {   
        std::cout << "this is true, but none of the following statements appear..?" << std::endl;
        if (b_tpc_xy[2] && b_tpc_xy[3])
        {   
            std::cout << "b_tpc_2 and b_tpc_3 are true" << std::endl;
            id_x2 = fCalHitTPC->Get_tpc_x_s2_foc_23_24();
            id_y2 = fCalHitTPC->Get_tpc_y_s2_foc_23_24();
            id_a2 = fCalHitTPC->Get_tpc_angle_x_s2_foc_23_24();
            id_b2 = fCalHitTPC->Get_tpc_angle_y_s2_foc_23_24();
        }
        else if (b_tpc_xy[1] && b_tpc_xy[3])
        {
            std::cout << "b_tpc_1 and b_tpc_3 are true" << std::endl;
            id_x2 = fCalHitTPC->Get_tpc_x_s2_foc_22_24();
            id_y2 = fCalHitTPC->Get_tpc_y_s2_foc_22_24();
            id_a2 = fCalHitTPC->Get_tpc_angle_x_s2_foc_22_24();
            id_b2 = fCalHitTPC->Get_tpc_angle_y_s2_foc_22_24();
        }
        else if (b_tpc_xy[0] && b_tpc_xy[1])
        {   
            std::cout << "b_tpc_0 and b_tpc_1 are true" << std::endl;
            id_x2 = fCalHitTPC->Get_tpc_x_s2_foc_21_22();
            id_y2 = fCalHitTPC->Get_tpc_y_s2_foc_21_22();
            id_a2 = fCalHitTPC->Get_tpc_angle_x_s2_foc_21_22();
            id_b2 = fCalHitTPC->Get_tpc_angle_y_s2_foc_21_22();
        }
    }
    else if (id->x_s2_select == 2)
    {   
        // SC21
        if (sci_b_x[0]) // we only use 2 and 3??
        {
            id_x2 = sci_x[0];
            id_y2 = 0.0;
            id_a2 = 0.0;
            id_b2 = 0.0;
        }
    }
    else if (id->x_s2_select == 3)
    {
        if (sci_b_x[1])
        {
            id_x2 = sci_x[1];
            id_y2 = 0.0;
            id_a2 = 0.0;
            id_b2 = 0.0;
        }
    }

    if (b_tpc_xy[4] && b_tpc_xy[5])
    {
        id_x4 = fCalHitTPC->Get_tpc_x_s4();
        id_y4 = fCalHitTPC->Get_tpc_y_s4();
        id_a4 = fCalHitTPC->Get_tpc_angle_x_s4();
        id_b4 = fCalHitTPC->Get_tpc_angle_y_s4();
    }

    if (sci_b_x[5])
    {
        id_x8 = sci_x[5];
        id_y8 = 0.0;
        id_a8 = 0.0;
        id_b8 = 0.0;
    }

    id_b_x2 = Check_WinCond(id_x2, cID_x2);
    id_b_x4 = Check_WinCond(id_x4, cID_x4);


    /* --------------------------------------------------------------------------*/
    // VFTX start here
    // (moved from Go4 as we need id_a2 and it gets calculated twice otherwise?)
    /* --------------------------------------------------------------------------*/
    
    TRaw_vftx = fCalHitVFTX->Get_TRaw_vftx();

    // loop over 21 or 22 size, check 41l/r are not empty
    for (int i = 0; i < TRaw_vftx[0].size(); i++)
    {   
        // 2141
        if (TRaw_vftx[4].size() != 0)
        {
            vftx_tof2141.emplace_back((0.5 * ((Double_t)TRaw_vftx[4].at(0) + (Double_t)TRaw_vftx[5].at(0)) - 0.5 * ((Double_t)TRaw_vftx[0].at(i) + (Double_t)TRaw_vftx[1].at(i))));
            vftx_tof2141_calib.emplace_back(vftx_tof2141.at(i) / 1000. + sci->vftx_offset_2141);
        }

        // 2142
        if (TRaw_vftx[6].size() != 0)
        {
            vftx_tof2142.emplace_back((0.5 * ((Double_t)TRaw_vftx[6].at(0) + (Double_t)TRaw_vftx[7].at(0)) - 0.5 * ((Double_t)TRaw_vftx[0].at(i) + (Double_t)TRaw_vftx[1].at(i))));
            vftx_tof2142_calib.emplace_back(vftx_tof2142.at(i) / 1000. + sci->vftx_offset_2142);
    
        }
    }

    for (int i = 0; i < TRaw_vftx[2].size(); i++)
    {
        // 2241
        if (TRaw_vftx[4].size() != 0)
        {
            vftx_tof2241.emplace_back((0.5 * ((Double_t)TRaw_vftx[4].at(0) + (Double_t)TRaw_vftx[5].at(0)) - 0.5 * ((Double_t)TRaw_vftx[2].at(i) + (Double_t)TRaw_vftx[3].at(i))));
            vftx_tof2241_calib.emplace_back(vftx_tof2241.at(i) / 1000. + sci->vftx_offset_2241);
        }

        // 2242
        if (TRaw_vftx[6].size() != 0)
        {
            vftx_tof2242.emplace_back((0.5 * ((Double_t)TRaw_vftx[6].at(0) + (Double_t)TRaw_vftx[7].at(0)) - 0.5 * ((Double_t)TRaw_vftx[2].at(i) + (Double_t)TRaw_vftx[3].at(i))));
            vftx_tof2242_calib.emplace_back(vftx_tof2242.at(i) / 1000. + sci->vftx_offset_2242);
        }
    }


    temp_s4x = -999.;
    if (b_tpc_xy[4] && b_tpc_xy[5])
    {
        temp_s4x = tpc_x_s4; // ->Get_
    }

    float temp_sci21x = -999.;
    if (id->vftx_s2pos_option == 1)
    {
        // do nothing?
    }
    else if (id->vftx_s2pos_option == 2)
    {
        if (b_tpc_xy[0] && b_tpc_xy[1])
        {
            temp_sci21x = fCalHitTPC->Get_tpc_x_s2_foc_21_22();
        }
        else if (b_tpc_xy[2] && b_tpc_xy[3])
        {
            temp_sci21x = fCalHitTPC->Get_tpc_x_s2_foc_23_24();
        }
        else if (b_tpc_xy[1] && b_tpc_xy[3])
        {
            temp_sci21x = fCalHitTPC->Get_tpc_x_s2_foc_22_24();
        }
    }
    
    // number of 21l hits
    for (int i = 0; i < TRaw_vftx[0].size(); i++)
    {
        id_vftx_beta_2141.emplace_back((id->vftx_length_2141 / vftx_tof2141_calib.at(i)) / speed_light);
        id_vftx_beta_2142.emplace_back((id->vftx_length_2142 / vftx_tof2142_calib.at(i)) / speed_light);
        id_vftx_gamma_2141.emplace_back(1. / sqrt(1. - id_vftx_beta_2141.at(i) * id_vftx_beta_2141.at(i)));
        id_vftx_gamma_2142.emplace_back(1. / sqrt(1. - id_vftx_beta_2142.at(i) * id_vftx_beta_2142.at(i)));

        if (temp_s4x > -200. && temp_s4x < 200. && temp_sci21x > -200. && temp_sci21x < 200)
        {
            id_vftx_delta_24 = (temp_s4x - (temp_sci21x * frs->magnification[1])) / (-1.0 * frs->dispersion[1] * 1000.0);
            if (id_vftx_beta_2141.at(i) > 0.0 && id_vftx_beta_2141.at(i) < 1.0)
            {
                id_vftx_aoq_2141.emplace_back(mean_brho_s2s4 * (1. + id_vftx_delta_24) * temp_tm_to_MeV / (temp_mu * id_vftx_beta_2141.at(i) * id_vftx_gamma_2141.at(i)));
                id_vftx_aoq_corr_2141.emplace_back(id_vftx_aoq_2141.at(i) - id->a2AoQCorr * id_a2);
            }
            if (id_vftx_beta_2142.at(i) > 0.0 && id_vftx_beta_2142.at(i) < 1.0)
            {
                id_vftx_aoq_2142.emplace_back(mean_brho_s2s4 * (1. + id_vftx_delta_24) * temp_tm_to_MeV / (temp_mu * id_vftx_beta_2142.at(i) * id_vftx_gamma_2142.at(i)));
                id_vftx_aoq_corr_2142.emplace_back(id_vftx_aoq_2142.at(i) - id->a2AoQCorr * id_a2);
            }
        }

        if ((de[0] > 0.0) && (id_vftx_beta_2141.at(i) > 0.0) && (id_vftx_beta_2141.at(i) < 1.0))
        {
            power = 1.;
            sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->vftx_vel_a_music41[j];
                power *= id_vftx_beta_2141.at(i);
            }

            id_vftx_vcor_2141.emplace_back(sum);
            
            if (id_vftx_vcor_2141.at(i) > 0.0)
            {
                id_vftx_z_2141.emplace_back(frs->primary_z * sqrt(de[0] / id_vftx_vcor_2141.at(i)));
                id_vftx_z2_2141.emplace_back(frs->primary_z * sqrt(de[1] / id_vftx_vcor_2141.at(i)));
            }
        }

        if ((de[0] > 0.0) && (id_vftx_beta_2142.at(i) > 0.0) && (id_vftx_beta_2142.at(i) < 1.0))
        {
            power = 1.;
            sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->vftx_vel_a_music41[j];
                power *= id_vftx_beta_2142.at(i);
            }

            id_vftx_vcor_2142.emplace_back(sum);

            if (id_vftx_vcor_2142.at(i) > 0.0)
            {
                id_vftx_z_2142.emplace_back(frs->primary_z * sqrt(de[0] / id_vftx_vcor_2142.at(i)));
                id_vftx_z2_2142.emplace_back(frs->primary_z * sqrt(de[1] / id_vftx_vcor_2142.at(i)));
            }
        }

    }

    // number of 22l hits
    for (int i = 0; i < TRaw_vftx[2].size(); i++)
    {
        id_vftx_beta_2241.emplace_back((id->vftx_length_2241 / vftx_tof2241_calib.at(i)) / speed_light);
        id_vftx_beta_2242.emplace_back((id->vftx_length_2242 / vftx_tof2242_calib.at(i)) / speed_light);
        id_vftx_gamma_2241.emplace_back(1. / sqrt(1. - id_vftx_beta_2241.at(i) * id_vftx_beta_2241.at(i)));
        id_vftx_gamma_2242.emplace_back(1. / sqrt(1. - id_vftx_beta_2242.at(i) * id_vftx_beta_2242.at(i)));

        if (temp_s4x > -200. && temp_s4x < 200. && temp_sci21x > -200. && temp_sci21x < 200)
        {
            id_vftx_delta_24 = (temp_s4x - (temp_sci21x * frs->magnification[1])) / (-1.0 * frs->dispersion[1] * 1000.0);
            if (id_vftx_beta_2241.at(i) > 0.0 && id_vftx_beta_2241.at(i) < 1.0)
            {
                id_vftx_aoq_2241.emplace_back(mean_brho_s2s4 * (1. + id_vftx_delta_24) * temp_tm_to_MeV / (temp_mu * id_vftx_beta_2241.at(i) * id_vftx_gamma_2241.at(i)));
                id_vftx_aoq_corr_2241.emplace_back(id_vftx_aoq_2241.at(i) - id->a2AoQCorr * id_a2);
            }
            if (id_vftx_beta_2242.at(i) > 0.0 && id_vftx_beta_2242.at(i) < 1.0)
            {
                id_vftx_aoq_2242.emplace_back(mean_brho_s2s4 * (1. + id_vftx_delta_24) * temp_tm_to_MeV / (temp_mu * id_vftx_beta_2242.at(i) * id_vftx_gamma_2242.at(i)));
                id_vftx_aoq_corr_2242.emplace_back(id_vftx_aoq_2242.at(i) - id->a2AoQCorr * id_a2);
            }
        }

        if ((de[0] > 0.0) && (id_vftx_beta_2241.at(i) > 0.0) && (id_vftx_beta_2241.at(i) < 1.0))
        {
            power = 1.;
            sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->vftx_vel_a_music41[j];
                power *= id_vftx_beta_2241.at(i);
            }

            id_vftx_vcor_2241.emplace_back(sum);

            if (id_vftx_vcor_2241.at(i) > 0.0)
            {
                id_vftx_z_2241.emplace_back(frs->primary_z * sqrt(de[0] / id_vftx_vcor_2241.at(i)));
                id_vftx_z2_2241.emplace_back(frs->primary_z * sqrt(de[1] / id_vftx_vcor_2241.at(i)));
            }
        }

        if ((de[0] > 0.0) && (id_vftx_beta_2242.at(i) > 0.0) && (id_vftx_beta_2242.at(i) < 1.0))
        {
            power = 1.;
            sum = 0.;
            for (int j = 0; j < 4; j++)
            {
                sum += power * id->vftx_vel_a_music41[j];
                power *= id_vftx_beta_2242.at(i);
            }

            id_vftx_vcor_2242.emplace_back(sum);

            if (id_vftx_vcor_2242.at(i) > 0.0)
            {
                id_vftx_z_2242.emplace_back(frs->primary_z * sqrt(de[0] / id_vftx_vcor_2242.at(i)));
                id_vftx_z2_2242.emplace_back(frs->primary_z * sqrt(de[1] / id_vftx_vcor_2242.at(i)));
            }
        }

    }
    
    /*----------------------------------------------------------*/
    /* End of VFTX  */
    /*----------------------------------------------------------*/


    /*----------------------------------------------------------*/
    /* Determination of beta                                    */
    /*----------------------------------------------------------*/
    id_beta = 0;
    if (id->tof_s4_select == 1)
    {
        if (sci_b_tofll2 && sci_b_tofrr2)
        {
            id_beta = id->id_path2 / sci_tof2_calib;
        }
    }
    else if (id->tof_s4_select == 2)
    {
        if (sci_b_tofll3 && sci_b_tofrr3)
        {
            id_beta = id->id_path3 / sci_tof3_calib;
        }
    }
    else if (id->tof_s4_select == 3)
    {
        if (sci_b_tofll5 && sci_b_tofrr5)
        {
            id_beta = id->id_path5 / sci_tof5_calib;
        }
    }

    /*------------------------------------------------------*/
    /* Determination of Brho                                */
    /*------------------------------------------------------*/

    if (id_b_x2)
    {
        id_rho[0] = frs->rho0[0] * (1. - id_x2 / 1000. / frs->dispersion[0]);
        id_brho[0] = (fabs(frs->bfield[0]) + fabs(frs->bfield[1])) / 2. * id_rho[0];

        if (id_b_x4)
        {
            id_rho[1] = frs->rho0[1] * (1. - (id_x4 - frs->magnification[1] * id_x2) / 1000. / frs->dispersion[1]);
            id_brho[1] = (fabs(frs->bfield[2]) + fabs(frs->bfield[3])) / 2. * id_rho[1];
        }
    }

    /*--------------------------------------------------------------*/
    /* Determination of A/Q                                         */
    /*--------------------------------------------------------------*/
    // for S2-S4
    if (sci_b_tofll2 && sci_b_tofrr2 && id_b_x2 && id_b_x4)
    {
        if ((id_beta > 0.0) && (id_beta < 1.0))
        {
            id_gamma = 1. / sqrt(1. - id_beta * id_beta);
            id_AoQ = id_brho[1] / id_beta / id_gamma / aoq_factor;
            id_AoQ_corr = id_AoQ - id->a2AoQCorr * id_a2;

            // this is not done in FRS Go4, and in DESPEC Go4 I can't understand where "ts_mins" comes from?
            // is it just WR in minutes somehow? 
            // why don't FRS GainMatch?
            if (id_AoQ_corr > 0)
            {
                for (int i = 0; i < AoQ_Shift_array; i++)
                {
                    if (ts_mins >= FRS_WR_i[i] && ts_mins < FRS_WR_j[i])
                    {
                        if (id->x_s2_select == 2)
                        {
                            id_AoQ = id_AoQ - AoQ_shift_Sci21_value[i];
                            id_AoQ_corr = id_AoQ_corr - AoQ_shift_Sci21_value[i];
                        }
                        else if (id->x_s2_select == 3)
                        {
                            id_AoQ = id_AoQ - AoQ_shift_Sci22_value[i];
                            id_AoQ_corr = id_AoQ_corr - AoQ_shift_Sci22_value[i];
                        }
                        else
                        {
                            id_AoQ = id_AoQ - AoQ_shift_TPC_value[i];
                            id_AoQ_corr = id_AoQ_corr - AoQ_shift_TPC_value[i];
                        }
                    }
                }
            }

            id_b_AoQ = true;
        }
    }

    /*------------------------------------------------*/
    /* Determination of Z                             */
    /*------------------------------------------------*/
    // S4 (MUSIC 1)
    if ((de[0] > 0.0) && (id_beta > 0.0) && (id_beta < 1.0))
    {
        power = 1.;
        sum = 0.;
        for (int i = 0; i < 4; i++)
        {
            sum += power * id->vel_a[i];
            power *= id_beta;
        }
        id_v_cor = sum;
        if (id_v_cor > 0.0)
        {
            id_z = frs->primary_z * sqrt(de[0] / id_v_cor) + id->offset_z;
        }
        if ((id_z > 0.0) && (id_z < 100.0))
        {
            id_b_z = kTRUE;
        }
    }

    // S4 (MUSIC 2)
    if ((de[1] > 0.0) && (id_beta > 0.0) && (id_beta < 1.0))
    {
        power = 1.;
        sum = 0.;
        for (int i = 0; i < 4; i++)
        {
            sum += power * id->vel_a2[i];
            power *= id_beta;
        }
        id_v_cor2 = sum;

        if (id_v_cor2 > 0.0)
        {
            id_z2 = frs->primary_z * sqrt(de[1] / id_v_cor2) + id->offset_z2;
        }
        if ((id_z2 > 0.0) && (id_z2 < 100.0))
        {
            id_b_z2 = kTRUE;
        }
    }
    
    // Gain match Z
    for (int i = 0; i < Z_Shift_array; i++)
    {
        if (ts_mins >= FRS_WR_a[i] && ts_mins < FRS_WR_b[i])
        {
            id_z = id_z - Z1_shift_value[i];
            id_z2 = id_z2 - Z2_shift_value[i];
        }
    }

    // S4 (MUSIC)
    /*
    if ((de[2] > 0.0) && (id_beta > 0.0) && (id_beta < 1.0))
    {
        power = 1.0;
        sum = 0.;
        for (int i = 0; i < 4; i++)
        {
            sum += power * id->vel_a3[i];
            power *= id_beta;
        }
        id_v_cor3 = sum;
        if (id_v_cor3 > 0.0)
        {
            id_z3 = frs->primary_z * sqrt(de[2] / id_v_cor3) + id->offset_z3;
        }
        if ((id_z3 > 0.0) && (id_z3 < 100.0))
        {
            id_b_z3 = kTRUE;
        }
    }
    */
    
    // non mhtdc version?
    //std::cout << " id_b_AoQ: " << id_b_AoQ << " id_b_x2: " << id_b_x2 << " id_b_z: " << id_b_z << std::endl;
    if (id_b_AoQ && id_b_x2 && id_b_z)
    {
        float gamma1square = 1.0 + TMath::Power(((1 / aoq_factor) * (id_brho[0] / id_AoQ)), 2);
        id_gamma_ta_s2 = TMath::Sqrt(gamma1square);
        id_dEdegoQ = (id_gamma_ta_s2 - id_gamma) * id_AoQ;
        id_dEdeg = id_dEdegoQ * id_z;
    }
    // above is end of FRS_Anl

    new ((*fHitArray)[fHitArray->GetEntriesFast()]) FrsHitData(
            WR_TS,
            id_x2,
            id_x4,
            id_AoQ,
            id_AoQ_corr,
            id_z,
            id_z2
    );
   
}


void FrsCal2Hit::Setup_Conditions()
{
    std::string line;
    int line_number = 0;

    const char* format = "%f %f %f %f %f %f %f %f %f %f %f %f %f %f";

    std::ifstream cond_a("../../config/frs/lim_csum.txt");

    while(/*cond_a.good()*/getline(cond_a,line,'\n'))
    {
        if(line[0] == '#') continue;


            sscanf(line.c_str(),format,&lim_csum[line_number][0][0],&lim_csum[line_number][0][1]
                        ,&lim_csum[line_number][1][0],&lim_csum[line_number][1][1]
                        ,&lim_csum[line_number][2][0],&lim_csum[line_number][2][1]
                        ,&lim_csum[line_number][3][0],&lim_csum[line_number][3][1]
                        ,&lim_csum[line_number][4][0],&lim_csum[line_number][4][1]
                        ,&lim_csum[line_number][5][0],&lim_csum[line_number][5][1]
                        ,&lim_csum[line_number][6][0],&lim_csum[line_number][6][1]);

        line_number++;

    }

    line_number = 0;

    format = "%f %f";

    std::ifstream cond_b("../../config/frs/lim_xsum.txt");

    while(/*cond_b.good()*/getline(cond_b,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&lim_xsum[line_number][0],&lim_xsum[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f";

    std::ifstream cond_c("../../config/frs/lim_ysum.txt");

    while(/*cond_c.good()*/getline(cond_c,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&lim_ysum[line_number][0],&lim_ysum[line_number][1]);

        line_number++;
    }

    /*** MUSIC Conditions *** */

    line_number = 0;

    format = "%f %f %f %f";

    std::ifstream cond_d("../../config/frs/MUSIC1.txt");

    while(/*cond_d.good()*/getline(cond_d,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic1_E[line_number][0],&cMusic1_E[line_number][1],&cMusic1_T[line_number][0],&cMusic1_T[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f %f %f";

    std::ifstream cond_e("../../config/frs/MUSIC2.txt");

    while(/*cond_e.good()*/getline(cond_e,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic2_E[line_number][0],&cMusic2_E[line_number][1],&cMusic2_T[line_number][0],&cMusic2_T[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f %f %f";

    std::ifstream cond_f("../../config/frs/MUSIC3.txt");

    while(/*cond_f.good()*/getline(cond_f,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic3_E[line_number][0],&cMusic3_E[line_number][1],&cMusic3_T[line_number][0],&cMusic3_T[line_number][1]);

        line_number++;
    }


    line_number = 0;

    format = "%f %f";

    std::ifstream cond_g("../../config/frs/MUSIC_dEc3.txt");

    while(/*cond_g.good()*/getline(cond_g,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic3_dec[0],&cMusic3_dec[1]);
    }

    /***SCINTILATOR Condtions***/

    line_number = 0;

    format = "%f %f";

    std::ifstream cond_h("../../config/frs/SCI_Cons.txt");

    while(/*cond_h.good()*/getline(cond_h,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cSCI_L[0],&cSCI_L[1]);

        getline(cond_h,line,'\n');
            sscanf(line.c_str(),format,&cSCI_R[0],&cSCI_R[1]);

        getline(cond_h,line,'\n');
            sscanf(line.c_str(),format,&cSCI_E[0],&cSCI_E[1]);

        getline(cond_h,line,'\n');
            sscanf(line.c_str(),format,&cSCI_Tx[0],&cSCI_Tx[1]);

        getline(cond_h,line,'\n');
            sscanf(line.c_str(),format,&cSCI_X[0],&cSCI_X[1]);

    }

    format = "%f %f";

    std::ifstream cond_i("../../config/frs/SCI_LLRR.txt");

    while(/*cond_i.good()*/getline(cond_i,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cSCI_LL2[0],&cSCI_LL2[1]);
        getline(cond_i,line,'\n');
            sscanf(line.c_str(),format,&cSCI_RR2[0],&cSCI_RR2[1]);

        getline(cond_i,line,'\n');
            sscanf(line.c_str(),format,&cSCI_LL3[0],&cSCI_LL3[1]);

        getline(cond_i,line,'\n');
            sscanf(line.c_str(),format,&cSCI_RR3[0],&cSCI_RR3[1]);


        getline(cond_i,line,'\n');
            sscanf(line.c_str(),format,&cSCI_LL4[0],&cSCI_LL4[1]);

        getline(cond_i,line,'\n');
            sscanf(line.c_str(),format,&cSCI_RR4[0],&cSCI_RR4[1]);

        getline(cond_i,line,'\n');
            sscanf(line.c_str(),format,&cSCI_LL5[0],&cSCI_LL5[1]);

        getline(cond_i,line,'\n');
            sscanf(line.c_str(),format,&cSCI_RR5[0],&cSCI_RR5[1]);

    }

    /***ID Condtions***/

    format = "%f %f";

    std::ifstream cond_k("../../config/frs/ID_x2.txt");


    while(/*cond_k.good()*/getline(cond_k,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cID_x2[0],&cID_x2[1]);
    }

    std::ifstream cond_l("../../config/frs/ID_x4.txt");

    while(/*cond_l.good()*/getline(cond_l,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cID_x4[0],&cID_x4[1]);
    }

    std::ifstream cond_m("../../config/frs/ID_Z_Z.txt");

    while(/*cond_m.good()*/getline(cond_m,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cID_Z_Z[0],&cID_Z_Z[1]);
    }

}

void FrsCal2Hit::FRS_GainMatching()
{
    std::ifstream file;
    std::string line;
    Float_t frs_wr_a;
    Float_t frs_wr_b;
    Float_t frs_wr_i;
    Float_t frs_wr_j;
    Float_t z1_shift_value;
    Float_t z2_shift_value;
    Float_t aoq_shift_value;
    Float_t aoq_shift_tpc_value;
    Float_t aoq_shift_sci21_value;
    Float_t aoq_shift_sci22_value;

    int f = 0;
    int d = 0;
    
    file.open("../../config/frs/Z1_Z2_Shift.txt");
    while (file.good())
    {
        getline(file, line, '\n');
        if (line[0] == '#') continue;
        sscanf(line.c_str(), "%f %f %f %f", &frs_wr_a, &frs_wr_b, &z1_shift_value, &z2_shift_value);
        FRS_WR_a[f] = frs_wr_a;
        FRS_WR_b[f] = frs_wr_b;
        Z1_shift_value[f] = z1_shift_value;
        Z2_shift_value[f] = z2_shift_value;
        Z_Shift_array = f;
        f++;
    }
    file.close();

    file.open("../../config/frs/AoQ_Shift.txt");
    while (file.good())
    {
        getline(file, line, '\n');
        if (line[0] == '#') continue;
        sscanf(line.c_str(), "%f %f %f %f %f", &frs_wr_i, &frs_wr_j, &aoq_shift_tpc_value, &aoq_shift_sci21_value, &aoq_shift_sci22_value);
        FRS_WR_i[d] = frs_wr_i;
        FRS_WR_j[d] = frs_wr_j;
        AoQ_shift_TPC_value[d] = aoq_shift_tpc_value;
        AoQ_shift_Sci21_value[d] = aoq_shift_sci21_value;
        AoQ_shift_Sci22_value[d] = aoq_shift_sci22_value;
        AoQ_Shift_array = d;
        d++;
    }
    file.close();

}

Bool_t FrsCal2Hit::Check_WinCond(Float_t P, Float_t* V)
{
    if (P >= V[0] && P <= V[1]) return true;
    else return false;
}

Bool_t FrsCal2Hit::Check_WinCond_Multi(Float_t P, Float_t V[8][2], int cond_num)
{
    if (P >= V[cond_num][0] && P <= V[cond_num][1]) return true;
    else return false;
}

Float_t FrsCal2Hit::rand3()
{
    return random3.Uniform(-0.5,0.5);
}


void FrsCal2Hit::ZeroArrays()
{
    fHitArray->Clear();
}

void FrsCal2Hit::ZeroVariables()
{
    id_b_AoQ = false;
    id_b_x2 = false;
    id_b_x4 = false;
    id_b_z = false;
    id_x2 = 0;
    id_y2 = 0;
    id_a2 = 0;
    id_b2 = 0;
    id_x4 = 0;
    id_y4 = 0;
    id_a4 = 0;
    id_b4 = 0;
    id_AoQ = 0;
    id_AoQ_corr = 0;
    id_z = 0;
    id_z2 = 0;
}

void FrsCal2Hit::ClearVectors()
{

}



void FrsCal2Hit::FinishEvent()
{
    ZeroArrays();
    ZeroVariables();
    ClearVectors();
}

void FrsCal2Hit::FinishTask()
{
    c4LOG(info, Form("Wrote %i events. ", fNEvents));
}

ClassImp(FrsCal2Hit)