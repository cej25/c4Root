#include "ext_unpacking.hh"
#include "unpack_frs.hh" // won't be needed when everything is complete i think
//#include "unpack_structures.hh"
//#include "config/FRS/setup_file.hh" // "frs_parameter_config.hh" from chat gpt lol

// ucesb internals
#include "data_src.hh"
#include "enumerate.hh"
#include "simple_data_ops.hh"
//#include "zero_suppress.hh"
//#include "zero_suppress_map.hh"
#include "error.hh"

// c++ stuff
#include <algorithm>
#include <iterator>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <bitset>
#include <cstdlib>

EXT_FRS::EXT_FRS()
{
    __clean();
}

EXT_FRS::~EXT_FRS()
{

}

void EXT_FRS::__clean()
{
    frs_info.__clean();
    
}

void EXT_FRS::Setup_FRS_Parameters()
{   
    frs.rho0[0]   = 1.; //TA-S2
    frs.rho0[1]   = 1.; //S2-S4
    frs.rho0[2]   = 1.; //S4-S8
    frs.dispersion[0]    = -6.474266;// RUN81-TA2B-220CM 27.05.2016
    frs.dispersion[1]    =  7.670;  // RUN81-TA2B-220CM 27.05.2016
    frs.dispersion[2]    = 12.397;
    frs.magnification[1] =  1.18;   //S2-S8 (gicosy sign definition)
    frs.magnification[2] =  1.829;   //S2-S8
    frs.dist_focS2 = 3300.0; // low-dispersion S2-S4
    frs.dist_MW21  =  604.0;
    frs.dist_MW22  = 1782.5;
    frs.dist_SC21  = 1554.5;
    frs.dist_SC22  = 2595.0; //BARB 2021 Feb Logbook  
    frs.dist_TPC21 =  604.0;
    frs.dist_TPC22 = 1782.5;
    frs.dist_TPC23 = 2915.0; //BARB 2021 Feb Logbook  
    frs.dist_TPC24 = 3980.0; //BARB 2021 Feb Logbook
    frs.dist_S2target = 3600.0; // Interaction Cross section (01.March 2021)
    frs.dist_SC41    = 2245.0;
    frs.dist_SC42    = 2620.0;
    frs.dist_SC43    = 4706.0;
    frs.dist_MUSIC41 = 735.0;
    frs.dist_MUSIC42 = 1215.0;
    frs.dist_MUSIC43 = 5013.0;
    frs.dist_TPC41   =  415.0;
    //  frs.dist_TPC42   = 1535.0; moved to avoid conflict. before 2020april run.
    frs.dist_TPC42 = 1528.0; //for s468. 2020 april 
    frs.dist_S4target= 4000.0; //for some experiments
    frs.dist_focS8 = 0;
    frs.dist_MW81 = 0;
    frs.dist_MW82 = 0;
    frs.dist_SC81 = 0;
    frs.primary_z = 82.; 
    frs.bfield[0] = 13.3474;//                 Please do NOT comment-out old brho and add new brho. Please make a NEW setup file. 
    frs.bfield[1] = 12.5166;//                 Please do NOT comment-out old brho and add new brho. Please make a NEW setup file. 
    frs.bfield[2] = 10.5376; //                 Please do NOT comment-out old brho and add new brho. Please make a NEW setup file. 
    frs.bfield[3] = 10.5376; //                 Please do NOT comment-out old brho and add new brho. Please make a NEW setup file. 
    frs.bfield[4] = 99.999; // D5 (to ESR) not used
    frs.bfield[5] = 99.999; // D6 (to S8)

    id.x_s2_select   = 1; //1=tpc,2=sc21,3=sc22
    id.tof_s4_select = 1; //1=sc21-41, 2=sc21-42, 3=sc22-41
    id.tof_s8_select = 1; //1=sc21-81, 2=sc22-81
    id.id_tofoff4  = 326337.1;   //SC21-81 [ps]          // quickly done from run156 and 166 (2019/Nov, YT)
    id.id_path4    = 246983.1;   //SC21-81  path/c [ps]  // quickly done from run156 and 166 (2019/Nov, YT)
    id.id_tofoff6  = 405709.2;   //SC22-81 [ps]          // 21feb2020 DK, YT
    id.id_path6    = 278586.5;   //SC22-81  path/c [ps]  // 21feb2020 DK, YT
    id.vel_a_s2tpc[0] =  1400.;// TPC-A was not measured during tof calib.
    id.vel_a_s2tpc[1] =  0.0;// now we estimate from ATIMA. and then
    id.vel_a_s2tpc[2] =  0.0;// translate parameters to fit go4 parametes. (YT)
    id.vel_a_s2tpc[3] =  0.0;
    id.offset_z_s2tpc =  0.0;
    id.vel_a_sc81[0] =   2156.4;// SC81 dE was not propery measured.
    id.vel_a_sc81[1] =  -1470.4;// I skip to set these parameters
    id.vel_a_sc81[2] =   0.0;// this time ...
    id.vel_a_sc81[3] =   0.0;
    id.offset_z_sc81 =   0.0;
    id.mhtdc_length_s2s8 = 85.230; // (2019/Nov, YT)
    id.mhtdc_s2pos_option=1; //(1: sc21x-timediff-mhtdc, 2:tpc);
    id.pos_offset_sc81x  = 7.0;// (2019/Nov, YT)
    id.mhtdc_vel_a_s2tpc[0] =  1400.0;// TPC-A does not look promising...21-feb-2020
    id.mhtdc_vel_a_s2tpc[1] =  0.0;// put constant here
    id.mhtdc_vel_a_s2tpc[2] =  0.0;// 
    id.mhtdc_vel_a_s2tpc[3] =  0.0;
    id.mhtdc_offset_z_s2tpc =  0.0;

    id.mhtdc_vel_a_sc81[0] =  2156.4;// SC81 dE was not propery measured.
    id.mhtdc_vel_a_sc81[1] =  0.0; // I skip to set these parameters
    id.mhtdc_vel_a_sc81[2] =  0.0; // this time ...
    id.mhtdc_vel_a_sc81[3] =  0.0;
    id.mhtdc_offset_z_sc81 =  0.0;

    //not related for S8
    id.offset_z   = 0.0 ;
    id.offset_z2  = 0.0 ;
    id.offset_z3  = 0.0 ;
    id.a2AoQCorr = 0.0012; //2020April12 JP
    id.a4AoQCorr = 0.0;

    //  MUSIC41 velocity 06.03.21 Pb s452
    id.vel_a[0] =   20888.0; //  MUSIC41 velocity corr. s533
    id.vel_a[1] =  -40943.0;   // 
    id.vel_a[2] =   22456.0; // 
    id.vel_a[3] =   0.0;

    // MUSIC42 velocity 06.03.21 Pb s452
    id.vel_a2[0] =  13490.0 ; 
    id.vel_a2[1] = -22027.0;
    id.vel_a2[2] =  10453.0;
    id.vel_a2[3] =  0.0;
    
    id.vel_a3[0] =  13951.37; //MUSIC43 velocity corr. (old)
    id.vel_a3[1] = -38369.9;
    id.vel_a3[2] =  28396.46;
    id.vel_a3[3] =  0.0;
    
    //TOF_SC42_SC21_TAC 06.03.21 Pb s452
    id.id_tofoff3  = 187701.;   // offset (ps)
    id.id_path3    = 134732.;   // path/c [ps]

    //TOF_SC41_SC21_TAC 06.03.21 Pb s452
    id.id_tofoff2 =  176384.;  // offset (ps)
    id.id_path2   =  123877.;  // path/c (ps)

    //TOF_SC41_SC22_TAC 06.03.21 Pb s452
    id.id_tofoff5 =  168010.;  // offset (ps) 
    id.id_path5   =  119612.;  // path/c (ps)

    
    id.mhtdc_length_s2s4 = 0.0;
    id.mhtdc_vel_a_music41[0]=1.0;
    id.mhtdc_vel_a_music41[1]=0.0;
    id.mhtdc_vel_a_music41[2]=0.0;
    id.mhtdc_vel_a_music41[3]=0.0;
    id.mhtdc_vel_a_music42[0]=1.0;
    id.mhtdc_vel_a_music42[1]=0.0;
    id.mhtdc_vel_a_music42[2]=0.0;
    id.mhtdc_vel_a_music42[3]=0.0;
    id.mhtdc_offset_z_music41=0.0;
    id.mhtdc_offset_z_music42=0.0;
    //=====================================================//

    mw.x_factor[0] = 0.25; // MW11 [mm/ns] some old value
    mw.x_factor[1] = 0.25; // MW21
    mw.x_factor[2] = 0.25; // MW22
    mw.x_factor[3] = 0.25; // MW31
    mw.x_factor[4] = 0.25; // MW51
    mw.x_factor[5] = 0.25; // MW71
    mw.x_factor[6] = 0.25; // MW81
    mw.x_factor[7] = 0.125; // MW82

    mw.x_offset[0] = 5.0; // MW11 Feb 2014
    mw.x_offset[1] = -2.0; // MW21 Feb 2014
    mw.x_offset[2] = -1.5; // MW22 Feb 2014
    mw.x_offset[3] = 5.0; // MW31 like MW11 15.11.19
    mw.x_offset[4] = -0.205; // MW51
    mw.x_offset[5] = 1.642; // MW71 //15/05/06
    mw.x_offset[6] = 1.;   // MW81 //11/05/06
    mw.x_offset[7] = -5.; // MW82 //27-MAY-2007

    mw.y_factor[0] = 0.25; // MW11 [mm/ns] 14.09.05 CN+AM 2ns/mm delay line
    mw.y_factor[1] = 0.25; // MW21
    mw.y_factor[2] = 0.25; // MW22
    mw.y_factor[3] = 0.25; // MW31
    mw.y_factor[4] = 0.25; // MW51
    mw.y_factor[5] = 0.25; // MW71
    mw.y_factor[6] = 0.25; // MW81
    mw.y_factor[7] = 0.125; // MW82  [mm/ns] 11.05.06  CN 4ns/mm delay line

    mw.y_offset[0] = -14.0;  // MW11 27-MAY-2007 TESTED VALUE WITH SLITS, ok Feb 2014
    mw.y_offset[1] = 21.0;   // Feb 2014
    mw.y_offset[2] = -1.0;   // MW22 27-MAY-2007 TESTED VALUE WITH SLITS, ok Feb 2014
    mw.y_offset[3] = -14.0;    // MW31 like in MW11 15.11.19
    mw.y_offset[4] = 0.0;     //MW51  ???????
    mw.y_offset[5] = -2.736;  // MW71 //15/05/06
    mw.y_offset[6] = 3.2;     // MW81 //11/05/06
    mw.y_offset[7] = 0.764;  // MW82 //11/05/06

    mw.gain_tdc[0][0] = 0.302929; //  MW11 Anode (#ch  0 TDC V775a) // 13.01.2008
    mw.gain_tdc[1][0] = 0.303253; //  MW11 XL    (#ch 17 TDC V775a)
    mw.gain_tdc[2][0] = 0.303975; //  MW11 XR    (#ch 16 TDC V775a)
    mw.gain_tdc[3][0] = 0.308414; //  MW11 YU    (#ch 18 TDC V775a)
    mw.gain_tdc[4][0] = 0.309826; //  MW11 YD    (#ch 19 TDC V775a)

    mw.gain_tdc[0][1] = 0.306064; //  MW21 Anode (#ch  1 TDC V775a) // 13.01.2008
    mw.gain_tdc[1][1] = 0.306958; //  MW21 XL    (#ch 21 TDC V775a)
    mw.gain_tdc[2][1] = 0.307799; //  MW21 XR    (#ch 20 TDC V775a)
    mw.gain_tdc[3][1] = 0.297774; //  MW21 YU    (#ch 22 TDC V775a)
    mw.gain_tdc[4][1] = 0.310235; //  MW21 YD    (#ch 23 TDC V775a)

    mw.gain_tdc[0][2] = 0.301179;  // MW22 Anode (#ch  2 TDC V775a) // 13.01.2008
    mw.gain_tdc[1][2] = 0.311121; //  MW22 XL    (#ch 25 TDC V775a)
    mw.gain_tdc[2][2] = 0.303233; //  MW22 XR    (#ch 24 TDC V775a)
    mw.gain_tdc[3][2] = 0.300558; //  MW22 YU    (#ch 26 TDC V775a)
    mw.gain_tdc[4][2] = 0.301105; //  MW22 YD    (#ch 27 TDC V775a)

    mw.gain_tdc[0][3] = 0.304426; //  MW31 Anode (#ch  3 TDC V775a) // 13.01.2008
    mw.gain_tdc[1][3] = 0.312163; //  MW31 XL    (#ch 29 TDC V775a)
    mw.gain_tdc[2][3] = 0.305609; //  MW31 XR    (#ch 28 TDC V775a)
    mw.gain_tdc[3][3] = 0.304716; //  MW31 YU    (#ch 30 TDC V775a)
    mw.gain_tdc[4][3] = 0.293695; //  MW31 YD    (#ch 31 TDC V775a)

    mw.gain_tdc[0][4] = 0.298871; //  MW41 Anode (#ch  4 TDC V775a) // 13.01.2008
    mw.gain_tdc[1][4] = 0.284086; //  MW41 XL    (#ch 1 TDC V775b)
    mw.gain_tdc[2][4] = 0.288656; //  MW41 XR    (#ch 0 TDC V775b)
    mw.gain_tdc[3][4] = 0.286589; //  MW41 YU    (#ch 2 TDC V775b)
    mw.gain_tdc[4][4] = 0.29269;  //  MW41 YD    (#ch 3 TDC V775b)

    mw.gain_tdc[0][5] = 0.297881; //  MW42 Anode (#ch  5 TDC V775a) // 13.01.2008
    mw.gain_tdc[1][5] = 0.287364; //  MW42 XL    (#ch 5 TDC V775b)
    mw.gain_tdc[2][5] = 0.289636; //  MW42 XR    (#ch 4 TDC V775b)
    mw.gain_tdc[3][5] = 0.291135; //  MW42 YU    (#ch 6 TDC V775b)
    mw.gain_tdc[4][5] = 0.289867; //  MW42 YD    (#ch 7 TDC V775b)

    mw.gain_tdc[0][6] = 0.307892; //  MW51 Anode (#ch  6 TDC V775a) // 13.01.2008
    mw.gain_tdc[1][6] = 0.289894; //  MW51 XL    (#ch  9 TDC V775b)
    mw.gain_tdc[2][6] = 0.292366; //  MW51 XR    (#ch  8 TDC V775b)
    mw.gain_tdc[3][6] = 0.284708; //  MW51 YU    (#ch 10 TDC V775b)
    mw.gain_tdc[4][6] = 0.28186;  //  MW51 YD    (#ch 11 TDC V775b)

    mw.gain_tdc[0][7] = 0.298266; //  MW61 Anode (#ch  7 TDC V775a) // 13.01.2008
    mw.gain_tdc[1][7] = 0.311; //  MW61 XL    (#ch ? TDC V775b)
    mw.gain_tdc[2][7] = 0.305; //  MW61 XR    (#ch ? TDC V775b)
    mw.gain_tdc[3][7] = 0.337; //  MW61 YU    (#ch ? TDC V775b)
    mw.gain_tdc[4][7] = 0.289; //  MW61 YD    (#ch ? TDC V775b)

    mw.gain_tdc[0][8] = 0.303602; //  MW71 Anode (#ch  8 TDC V775a) // 13.01.2008
    mw.gain_tdc[1][8] = 0.300082; //  MW71 XL    (#ch 13 TDC V775b)
    mw.gain_tdc[2][8] = 0.286092; //  MW71 XR    (#ch 12 TDC V775b)
    mw.gain_tdc[3][8] = 0.294287; //  MW71 YU    (#ch 14 TDC V775b)
    mw.gain_tdc[4][8] = 0.291341; //  MW71 YD    (#ch 15 TDC V775b)

    mw.gain_tdc[0][9] = 0.306041; //  MW81 Anode (#ch  9 TDC V775a) // 13.01.2008
    mw.gain_tdc[1][9] = 0.288468; //  MW81 XL    (#ch 17 TDC V775b)
    mw.gain_tdc[2][9] = 0.293831; //  MW81 XR    (#ch 16 TDC V775b)
    mw.gain_tdc[3][9] = 0.281296; //  MW81 YU    (#ch 18 TDC V775b)
    mw.gain_tdc[4][9] = 0.279099; //  MW81 YD    (#ch 19 TDC V775b)

    mw.gain_tdc[0][10] = 0.31314;  //  MW82 Anode (#ch 10 TDC V775a) // 13.01.2008
    mw.gain_tdc[1][10] = 0.287279; //  MW82 XL    (#ch 21 TDC V775b)
    mw.gain_tdc[2][10] = 0.284028; //  MW82 XR    (#ch 20 TDC V775b)
    mw.gain_tdc[3][10] = 0.28051;  //  MW82 YU    (#ch 22 TDC V775b)
    mw.gain_tdc[4][10] = 0.28743;  //  MW82 YD    (#ch 23 TDC V775b)

    mw.gain_tdc[0][11] = 0.299973; //  MWB21 Anode (#ch 11 TDC V775a) // 13.01.2008
    mw.gain_tdc[1][11] = 0.311; //  MWB21 XL    (#ch ? TDC V775b)
    mw.gain_tdc[2][11] = 0.305; //  MWB21 XR    (#ch ? TDC V775b)
    mw.gain_tdc[3][11] = 0.337; //  MWB21 YU    (#ch ? TDC V775b)
    mw.gain_tdc[4][11] = 0.289; //  MWB21 YD    (#ch ? TDC V775b)

    mw.gain_tdc[0][12] = 0.306923; //  MWB22 Anode (#ch 12 TDC V775a) // 13.01.2008
    mw.gain_tdc[1][12] = 0.311; //  MWB22 XL    (#ch ? TDC V775b)
    mw.gain_tdc[2][12] = 0.305; //  MWB22 XR    (#ch ? TDC V775b)
    mw.gain_tdc[3][12] = 0.337; //  MWB22 YU    (#ch ? TDC V775b)
    mw.gain_tdc[4][12] = 0.289; //  MWB22 YD    (#ch ? TDC V775b)


    //=========
    // MUSICs
    //=========

    // histogram setup
    music.max_adc_music1 =    4096; //tum music
    music.max_adc_music2 =    4096; //tum music
    music.max_adc_music3 =  0x2000; //travel music
    music.max_tdc_music1 =    4096; //tum music
    music.max_tdc_music2 =    4096; //tum music
    music.max_tdc_music3 = 0x10000; //travel music

    music.dist_MUSICa1 = 52.5;  // do not change
    music.dist_MUSICa2 = 157.5; // do not change
    music.dist_MUSICa3 = 262.5; // do not change
    music.dist_MUSICa4 = 367.5; // do not change

    //MUSIC41
    music.e1_off[0]   = 0.; //MUSIC41 offsets
    music.e1_off[1]   = 0.;
    music.e1_off[2]   = 0.;
    music.e1_off[3]   = 0.;
    music.e1_off[4]   = 0.;
    music.e1_off[5]   = 0.;
    music.e1_off[6]   = 0.;
    music.e1_off[7]   = 0.;

    music.e1_gain[0]   = 1.; // MUSIC41 gains
    music.e1_gain[1]   = 1.;
    music.e1_gain[2]   = 1.;
    music.e1_gain[3]   = 1.;
    music.e1_gain[4]   = 1.;
    music.e1_gain[5]   = 1.;
    music.e1_gain[6]   = 1.;
    music.e1_gain[7]   = 1.;

    //MUSIC42
    music.e2_off[0]   = 0.; //MUSIC42 offsets
    music.e2_off[1]   = 0.;
    music.e2_off[2]   = 0.;
    music.e2_off[3]   = 0.;
    music.e2_off[4]   = 0.;
    music.e2_off[5]   = 0.;
    music.e2_off[6]   = 0.;
    music.e2_off[7]   = 0.;

    music.e2_gain[0]   = 1.; //MUSIC42 gains
    music.e2_gain[1]   = 1.;
    music.e2_gain[2]   = 1.;
    music.e2_gain[3]   = 1.;
    music.e2_gain[4]   = 1.;
    music.e2_gain[5]   = 1.;
    music.e2_gain[6]   = 1.;
    music.e2_gain[7]   = 1.;

    //MUSIC43
    music.e3_off[0]   = 2.; //MUSIC3 offsets
    music.e3_off[1]   = 1.;
    music.e3_off[2]   = 1.;
    music.e3_off[3]   = 1.;
    music.e3_off[4]   = 1.;
    music.e3_off[5]   = 1.;
    music.e3_off[6]   = 1.;
    music.e3_off[7]   = 1.;

    music.e3_gain[0]   = 1.; // MUSIC3 gains
    music.e3_gain[1]   = 1.;
    music.e3_gain[2]   = 1.;
    music.e3_gain[3]   = 1.;
    music.e3_gain[4]   = 1.;
    music.e3_gain[5]   = 1.;
    music.e3_gain[6]   = 1.;
    music.e3_gain[7]   = 1.;

    music.pos_a1[0]   = 1.0;   // C0...Cn position correction not used
    music.pos_a1[1]   = 0.0;
    music.pos_a1[2]   = 0.0;
    music.pos_a1[3]   = 0.0;
    music.pos_a1[4]   = 0.0;
    music.pos_a1[5]   = 0.0;
    music.pos_a1[6]   = 0.0;


    //========= 
    //  TPCs
    //=========


    // multihit TDC cut TPC time reference signal
    // After changing cut limits => Launch analysis again in Go4GUI
    tpc.lim_timeref[0][0] = 2000.0; tpc.lim_timeref[0][1] = 48000.0;//time ref (accept trig)
    tpc.lim_timeref[1][0] = 2000.0; tpc.lim_timeref[1][1] = 48000.0;//time ref (sc21)
    tpc.lim_timeref[2][0] = 2000.0; tpc.lim_timeref[2][1] = 48000.0;//time ref (sc22)
    tpc.lim_timeref[3][0] = 2000.0; tpc.lim_timeref[3][1] = 48000.0;//time ref (sc31)
    tpc.lim_timeref[4][0] = 2000.0; tpc.lim_timeref[4][1] = 48000.0;//time ref (sc41)
    tpc.lim_timeref[5][0] = 2000.0; tpc.lim_timeref[5][1] = 48000.0;//time ref (---)
    tpc.lim_timeref[6][0] = 2000.0; tpc.lim_timeref[6][1] = 48000.0;//time ref (---)
    tpc.lim_timeref[7][0] = 2000.0; tpc.lim_timeref[7][1] = 48000.0;//time ref (---)

    // TPC 1 at S2 (TPC 21) in vaccuum //// (BARB 2021 Feb 15) 
    // After changing cut limits => Launch analysis again in Go4GUI
    tpc.id_tpc_timeref[0] = 1; //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
    tpc.lim_dt[0][0][0] = 2000.;  tpc.lim_dt[0][0][1] = 48000.0; //A11 drift time TDC cut
    tpc.lim_dt[0][1][0] = 2000.;  tpc.lim_dt[0][1][1] = 48000.0; //A12 drift time TDC cut
    tpc.lim_dt[0][2][0] = 2000.;  tpc.lim_dt[0][2][1] = 48000.0; //A21 drift time TDC cut
    tpc.lim_dt[0][3][0] = 2000.;  tpc.lim_dt[0][3][1] = 48000.0; //A22 drift time TDC cut
    tpc.lim_lt[0][0][0] = 2000.;  tpc.lim_lt[0][0][1] = 48000.0; //DL1 time TDC cut
    tpc.lim_rt[0][0][0] = 2000.;  tpc.lim_rt[0][0][1] = 48000.0; //DR1 time TDC cut
    tpc.lim_lt[0][1][0] = 2000.;  tpc.lim_lt[0][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_rt[0][1][0] = 2000.;  tpc.lim_rt[0][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_csum1[0][0] = 13700.0;  tpc.lim_csum1[0][1] = 14600.0;
    tpc.lim_csum2[0][0] = 13900.0;  tpc.lim_csum2[0][1] = 14600.0;
    tpc.lim_csum3[0][0] = 13500.0;  tpc.lim_csum3[0][1] = 14600.0; 
    tpc.lim_csum4[0][0] = 13500.0;  tpc.lim_csum4[0][1] = 14600.0;
    tpc.x_offset[0][0] = -0.4-0.5;
    tpc.x_offset[0][1] =  1.2-0.5-2.0;
    tpc.x_factor[0][0] = 0.00786;
    tpc.x_factor[0][1] = 0.00786;
    tpc.y_offset[0][0] = -48.1-7.5-1.0+2.0;//s483, slit +/- 1mm 
    tpc.y_offset[0][1] = -48.2-8.5    +2.0;
    tpc.y_offset[0][2] = -48.0-9.0    +2.0;
    tpc.y_offset[0][3] = -48.2-8.5    +2.0;
    tpc.y_factor[0][0] = 0.004;
    tpc.y_factor[0][1] = 0.004;
    tpc.y_factor[0][2] = 0.004;
    tpc.y_factor[0][3] = 0.004;

    // TPC 2 at S2 (TPC 22) in vaccuum (BARB 2021 Feb 15) 
    // After changing cut limits => Launch analysis again in Go4GUI
    tpc.id_tpc_timeref[1] = 1; //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
    tpc.lim_dt[1][0][0] = 2000.;  tpc.lim_dt[1][0][1] = 48000.0; //A11 drift time TDC cut
    tpc.lim_dt[1][1][0] = 2000.;  tpc.lim_dt[1][1][1] = 48000.0; //A12 drift time TDC cut
    tpc.lim_dt[1][2][0] = 2000.;  tpc.lim_dt[1][2][1] = 48000.0; //A21 drift time TDC cut
    tpc.lim_dt[1][3][0] = 2000.;  tpc.lim_dt[1][3][1] = 48000.0; //A22 drift time TDC cut
    tpc.lim_lt[1][0][0] = 2000.;  tpc.lim_lt[1][0][1] = 48000.0; //DL1 time TDC cut
    tpc.lim_rt[1][0][0] = 2000.;  tpc.lim_rt[1][0][1] = 48000.0; //DR1 time TDC cut
    tpc.lim_lt[1][1][0] = 2000.;  tpc.lim_lt[1][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_rt[1][1][0] = 2000.;  tpc.lim_rt[1][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_csum1[1][0] = 17000.0;    tpc.lim_csum1[1][1] =  19200.0;
    tpc.lim_csum2[1][0] = 17000.0;    tpc.lim_csum2[1][1] =  19200.0;
    tpc.lim_csum3[1][0] = 17000.0;    tpc.lim_csum3[1][1] =  19200.0;
    tpc.lim_csum4[1][0] = 17000.0;    tpc.lim_csum4[1][1] =  19200.0;
    tpc.x_factor[1][0] = 0.0078;
    tpc.x_factor[1][1] = 0.0075;
    tpc.y_factor[1][0] = 0.004;
    tpc.y_factor[1][1] = 0.004;
    tpc.y_factor[1][2] = 0.004;
    tpc.y_factor[1][3] = 0.004;
    tpc.x_offset[1][0] = 1.2+1.0-1.8-1.0;
    tpc.x_offset[1][1] = 0.2-1.6-1.0;
    tpc.y_offset[1][0] = -48.1-9.0+2.7-0.2;//s483, slit +/- 1mm
    tpc.y_offset[1][1] = -48.2-9.0+2.7-0.5;
    tpc.y_offset[1][2] = -48.2-9.5+2.7-0.4;
    tpc.y_offset[1][3] = -47.8-9.3+2.7-0.3;

    // TPC 3 at S2 (TPC 23) in air (BARB 2021 Feb 15)
    // After changing cut limits => Launch analysis again in Go4GUI
    tpc.id_tpc_timeref[2] = 1; ////(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
    tpc.lim_dt[2][0][0] = 2000.;  tpc.lim_dt[2][0][1] = 48000.0; //A11 drift time TDC cut
    tpc.lim_dt[2][1][0] = 2000.;  tpc.lim_dt[2][1][1] = 48000.0; //A12 drift time TDC cut
    tpc.lim_dt[2][2][0] = 2000.;  tpc.lim_dt[2][2][1] = 48000.0; //A21 drift time TDC cut
    tpc.lim_dt[2][3][0] = 2000.;  tpc.lim_dt[2][3][1] = 48000.0; //A22 drift time TDC cut
    tpc.lim_lt[2][0][0] = 2000.;  tpc.lim_lt[2][0][1] = 48000.0; //DL1 time TDC cut
    tpc.lim_rt[2][0][0] = 2000.;  tpc.lim_rt[2][0][1] = 48000.0; //DR1 time TDC cut
    tpc.lim_lt[2][1][0] = 2000.;  tpc.lim_lt[2][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_rt[2][1][0] = 2000.;  tpc.lim_rt[2][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_csum1[2][0] = 13500.0;   tpc.lim_csum1[2][1] = 15000.0; //
    tpc.lim_csum2[2][0] = 13500.0;   tpc.lim_csum2[2][1] = 15000.0;
    tpc.lim_csum3[2][0] = 13500.0;   tpc.lim_csum3[2][1] = 15000.0;
    tpc.lim_csum4[2][0] = 13500.0;   tpc.lim_csum4[2][1] = 15000.0;
    tpc.x_offset[2][0] = 1.8+3.0-7.73+2; // two last alignement file in S511_20_0651
    tpc.x_offset[2][1] = 0.2+2.0-7.73+2;
    tpc.x_factor[2][0] = 0.0081;
    tpc.x_factor[2][1] = 0.0077;
    tpc.y_offset[2][0] = 48.4-1.0;
    tpc.y_offset[2][1] = 48.5-1.0;
    tpc.y_offset[2][2] = 48.4-1.0;
    tpc.y_offset[2][3] = 48.1-1.0;
    tpc.y_factor[2][0] = -0.004;
    tpc.y_factor[2][1] = -0.004;
    tpc.y_factor[2][2] = -0.004;
    tpc.y_factor[2][3] = -0.004;

    // TPC 4 at S2 (TPC 24) in air (BARB 2021 Feb 15)
    // After changing cut limits => Launch analysis again in Go4GUI
    tpc.id_tpc_timeref[3] = 4; //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
    tpc.timeref_calibrun[3] = 1037.0; //sc21
    tpc.lim_dt[3][0][0] = 2000.;  tpc.lim_dt[3][0][1] = 48000.0; //A11 drift time TDC cut
    tpc.lim_dt[3][1][0] = 2000.;  tpc.lim_dt[3][1][1] = 48000.0; //A12 drift time TDC cut
    tpc.lim_dt[3][2][0] = 2000.;  tpc.lim_dt[3][2][1] = 48000.0; //A21 drift time TDC cut
    tpc.lim_dt[3][3][0] = 2000.;  tpc.lim_dt[3][3][1] = 48000.0; //A22 drift time TDC cut
    tpc.lim_lt[3][0][0] = 2000.;  tpc.lim_lt[3][0][1] = 48000.0; //DL1 time TDC cut
    tpc.lim_rt[3][0][0] = 2000.;  tpc.lim_rt[3][0][1] = 48000.0; //DR1 time TDC cut
    tpc.lim_lt[3][1][0] = 2000.;  tpc.lim_lt[3][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_rt[3][1][0] = 2000.;  tpc.lim_rt[3][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_csum1[3][0] = 17500.0;    tpc.lim_csum1[3][1]= 19500.0; //
    tpc.lim_csum2[3][0] = 17500.0;    tpc.lim_csum2[3][1] = 19500.0;
    tpc.lim_csum3[3][0] = 17500.0;    tpc.lim_csum3[3][1] = 19500.0; //
    tpc.lim_csum4[3][0] = 17500.0;    tpc.lim_csum4[3][1] = 19500.0;
    tpc.x_offset[3][0] = 0.8 + 3.0-8.73+0.1; //two last alignement file in S511_20_0651
    tpc.x_offset[3][1] = -1.1 +3.5-8.73+0.1;
    tpc.x_factor[3][0] = 0.00782;
    tpc.x_factor[3][1] = 0.0088;
    tpc.y_offset[3][0] = 48.2 +10.5;
    tpc.y_offset[3][1] = 48.4 +10.5;
    tpc.y_offset[3][2] = 48.1 +10.0;
    tpc.y_offset[3][3] = 48.6 +10.0;
    tpc.y_factor[3][0] = -0.004;
    tpc.y_factor[3][1] = -0.004;
    tpc.y_factor[3][2] = -0.004;
    tpc.y_factor[3][3] = -0.004;
    
    // TPC 5  at S4 (TPC 41) in air (BARB 2021 Feb 15)
    // After changing cut limits => Launch analysis again in Go4GUI
    tpc.id_tpc_timeref[4] = 4; //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
    tpc.lim_dt[4][0][0] = 2000.;  tpc.lim_dt[4][0][1] = 48000.0; //A11 drift time TDC cut
    tpc.lim_dt[4][1][0] = 2000.;  tpc.lim_dt[4][1][1] = 48000.0; //A12 drift time TDC cut
    tpc.lim_dt[4][2][0] = 2000.;  tpc.lim_dt[4][2][1] = 48000.0; //A21 drift time TDC cut
    tpc.lim_dt[4][3][0] = 2000.;  tpc.lim_dt[4][3][1] = 48000.0; //A22 drift time TDC cut
    tpc.lim_lt[4][0][0] = 2000.;  tpc.lim_lt[4][0][1] = 48000.0; //DL1 time TDC cut
    tpc.lim_rt[4][0][0] = 2000.;  tpc.lim_rt[4][0][1] = 48000.0; //DR1 time TDC cut
    tpc.lim_lt[4][1][0] = 2000.;  tpc.lim_lt[4][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_rt[4][1][0] = 2000.;  tpc.lim_rt[4][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_csum1[4][0] = 10000.0;    tpc.lim_csum1[4][1] = 20000.0;
    tpc.lim_csum2[4][0] = 10000.0;    tpc.lim_csum2[4][1] = 20000.0;
    tpc.lim_csum3[4][0] = 10000.0;    tpc.lim_csum3[4][1] = 20000.0;
    tpc.lim_csum4[4][0] = 10000.0;    tpc.lim_csum4[4][1] = 20000.0;
    tpc.x_offset[4][0] = -1.6-1.0;
    tpc.x_offset[4][1] = -1.1-1.8;
    tpc.x_factor[4][0] = 0.00794;
    tpc.x_factor[4][1] = 0.00782;
    tpc.y_offset[4][0] = 56.4-1.5-2.0;
    tpc.y_offset[4][1] = 56.7-2.0-1.5;
    tpc.y_offset[4][2] = 56.5-0.3-2.0;
    tpc.y_offset[4][3] = 56.3-0.3-2.0;
    tpc.y_factor[4][0] = -0.004;
    tpc.y_factor[4][1] = -0.004;
    tpc.y_factor[4][2] = -0.004;
    tpc.y_factor[4][3] = -0.004;

    //-------- TPC42 parameters (BARB 2021 Feb 15)--------------
    // TPC 6 at S4 (TPC 42) in air
    tpc.id_tpc_timeref[5] = 1; //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
    tpc.lim_dt[5][0][0] = 2000.;  tpc.lim_dt[5][0][1] = 48000.0; //A11 drift time TDC cut
    tpc.lim_dt[5][1][0] = 2000.;  tpc.lim_dt[5][1][1] = 48000.0; //A12 drift time TDC cut
    tpc.lim_dt[5][2][0] = 2000.;  tpc.lim_dt[5][2][1] = 48000.0; //A21 drift time TDC cut
    tpc.lim_dt[5][3][0] = 2000.;  tpc.lim_dt[5][3][1] = 48000.0; //A22 drift time TDC cut
    tpc.lim_lt[5][0][0] = 2000.;  tpc.lim_lt[5][0][1] = 48000.0; //DL1 time TDC cut
    tpc.lim_rt[5][0][0] = 2000.;  tpc.lim_rt[5][0][1] = 48000.0; //DR1 time TDC cut
    tpc.lim_lt[5][1][0] = 2000.;  tpc.lim_lt[5][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_rt[5][1][0] = 2000.;  tpc.lim_rt[5][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_csum1[5][0] = 10000.0;    tpc.lim_csum1[5][1] = 20000.0;
    tpc.lim_csum2[5][0] = 10000.0;    tpc.lim_csum2[5][1] = 20000.0;
    tpc.lim_csum3[5][0] = 10000.0;    tpc.lim_csum3[5][1] = 20000.0;
    tpc.lim_csum4[5][0] = 10000.0;    tpc.lim_csum4[5][1] = 20000.0;
    tpc.x_offset[5][0] = 2.0+1.2-1.0;
    tpc.x_offset[5][1] = 1.7+0.51-1.0;
    tpc.x_factor[5][0] = 0.0077;
    tpc.x_factor[5][1] = 0.0078;
    tpc.y_offset[5][0] = 56.5-1.5-1.0;
    tpc.y_offset[5][1] = 57.3-1.5-1.0;
    tpc.y_offset[5][2] = 56.8-2.6-1.0;
    tpc.y_offset[5][3] = 56.4-2.6-1.0;
    tpc.y_factor[5][0] = -0.004;
    tpc.y_factor[5][1] = -0.004;
    tpc.y_factor[5][2] = -0.004;
    tpc.y_factor[5][3] = -0.004;


    //TPC at S3 (TPC 31)
    tpc.id_tpc_timeref[6] = 3; //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
    tpc.lim_dt[6][0][0] = 2000.;  tpc.lim_dt[6][0][1] = 48000.0; //A11 drift time TDC cut
    tpc.lim_dt[6][1][0] = 2000.;  tpc.lim_dt[6][1][1] = 48000.0; //A12 drift time TDC cut
    tpc.lim_dt[6][2][0] = 2000.;  tpc.lim_dt[6][2][1] = 48000.0; //A21 drift time TDC cut
    tpc.lim_dt[6][3][0] = 2000.;  tpc.lim_dt[6][3][1] = 48000.0; //A22 drift time TDC cut
    tpc.lim_lt[6][0][0] = 2000.;  tpc.lim_lt[6][0][1] = 48000.0; //DL1 time TDC cut
    tpc.lim_rt[6][0][0] = 2000.;  tpc.lim_rt[6][0][1] = 48000.0; //DR1 time TDC cut
    tpc.lim_lt[6][1][0] = 2000.;  tpc.lim_lt[6][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_rt[6][1][0] = 2000.;  tpc.lim_rt[6][1][1] = 48000.0; //DL2 time TDC cut
    tpc.lim_csum1[6][0] = 10000.0;    tpc.lim_csum1[6][1] = 20000.0;
    tpc.lim_csum2[6][0] = 10000.0;    tpc.lim_csum2[6][1] = 20000.0;
    tpc.lim_csum3[6][0] = 10000.0;    tpc.lim_csum3[6][1] = 20000.0;
    tpc.lim_csum4[6][0] = 10000.0;    tpc.lim_csum4[6][1] = 20000.0;
    tpc.x_offset[6][0] = -0.9;
    tpc.x_offset[6][1] = -3.4;
    tpc.x_factor[6][0] = 0.0088;
    tpc.x_factor[6][1] = 0.0088;
    tpc.y_offset[6][0] = -55.2;
    tpc.y_offset[6][1] = -57.3;
    tpc.y_offset[6][2] = -54.0;
    tpc.y_offset[6][3] = -53.7;
    tpc.y_factor[6][0] = 0.004;
    tpc.y_factor[6][1] = 0.004;
    tpc.y_factor[6][2] = 0.004;
    tpc.y_factor[6][3] = 0.004;


    //TPC21 ADC pedestal
    tpc.a_offset[0][0] = 999.;
    tpc.a_offset[0][1] = 999.;
    tpc.a_offset[0][2] = 999.;
    tpc.a_offset[0][3] = 999.;
    //TPC22 ADC pedestal
    tpc.a_offset[1][0] = 999.;
    tpc.a_offset[1][1] = 999.;
    tpc.a_offset[1][2] = 999.;
    tpc.a_offset[1][3] = 999.;
    //TPC23 ADC pedestal
    tpc.a_offset[2][0] = 104.; //set large number to exclude (pedestal data) of this tpc
    tpc.a_offset[2][1] = 107.;
    tpc.a_offset[2][2] = 106.;
    tpc.a_offset[2][3] =  91.;
    //TPC24 ADC pedestal
    tpc.a_offset[3][0] = 107.;
    tpc.a_offset[3][1] = 117.;
    tpc.a_offset[3][2] = 123.;
    tpc.a_offset[3][3] =  81.;


    //===========
    // Plastics
    //===========

    //index 2 for Sc21
    sci.x_a[0][2] =    1064.51;  // quickly done for s475plus_05_70Br_0327.lmd (2020/March)
    sci.x_a[1][2] =   -0.581114;  // quickly done for s475plus_05_70Br_0327.lmd (2020/March)
    sci.x_a[2][2] =  0.000000;  //
    sci.x_a[3][2] =  0.000000;  //
    sci.x_a[4][2] =  0.000000;  //
    sci.x_a[5][2] =  0.000000;  //
    sci.x_a[6][2] =  0.000000;  //
    
    //index 3 for Sc22
    // sci.x_a[0][3] =  1370;  //quickly done with run 0139
    // sci.x_a[1][3] =  -0.7;  //
    sci.x_a[0][3] =  1674.29;  //  quickly done with run 0214
    sci.x_a[1][3] = -0.85714;  //
    sci.x_a[2][3] =  0.000000;  //
    sci.x_a[3][3] =  0.000000;  //
    sci.x_a[4][3] =  0.000000;  //
    sci.x_a[5][3] =  0.000000;  //
    sci.x_a[6][3] =  0.000000;  //

    // index 5 for Sc41
    sci.x_a[0][5] = 897.63;  //  quickly done for s475plus_05_70Br_0327.lmd (2020/March)
    sci.x_a[1][5] = -0.72569;  //  quickly done for s475plus_05_70Br_0327.lmd (2020/March)
    sci.x_a[2][5] = 0.000000;   //
    sci.x_a[3][5] = 0.000000;   //
    sci.x_a[4][5] = 0.000000;   //
    sci.x_a[5][5] = 0.000000;   //
    sci.x_a[6][5] = 0.000000;   //

    // index 6 for Sc42
    sci.x_a[0][6] = 635.428;    // quickly done for s475plus_05_70Br_0327.lmd (2020/March)
    sci.x_a[1][6] = -0.5978; // quickly done for s475plus_05_70Br_0327.lmd (2020/March)
    sci.x_a[2][6] = 0.000000;  //
    sci.x_a[3][6] = 0.000000;  //
    sci.x_a[4][6] = 0.000000;  //
    sci.x_a[5][6] = 0.000000;  //
    sci.x_a[6][6] = 0.000000;  //

    // index 7 for Sc43
    sci.x_a[0][7] = 0.; //   SC43 calibration ch.mm
    sci.x_a[1][7] = 1.; //
    sci.x_a[2][7] = 0.000000;  //
    sci.x_a[3][7] = 0.000000;  //
    sci.x_a[4][7] = 0.000000;  //
    sci.x_a[5][7] = 0.000000;  //
    sci.x_a[6][7] = 0.000000;  //

    // index 10 for Sc81
    sci.x_a[0][10] = 707.306;   // 2020/feb/20 run0110,0111,0112.lmd
    sci.x_a[1][10] =-0.45558;   // 
    sci.x_a[2][10] = 0.000000;  //
    sci.x_a[3][10] = 0.000000;  //
    sci.x_a[4][10] = 0.000000;  //
    sci.x_a[5][10] = 0.000000;  //
    sci.x_a[6][10] = 0.000000;  //
    sci.le_a[0][10] = 310.0; //21/feb/2020
    sci.re_a[0][10] = 123.0;

    // For TAC calibration, please only set "factor".
    // To put some "magic number" offset is very confusing!!
    // TOF calibration should be done via setting id.id_tofoff2(3)(4)
    sci.tac_off[0] = 0.0;  //SC21L-R    // fix to 0
    sci.tac_off[1] = 0.0;  //SC41L-R    // fix to 0
    sci.tac_off[2] = 0.0;  //SC41L-SC21L   // fix to 0
    sci.tac_off[3] = 0.0;  //SC41R-SC21R   // fix to 0
    sci.tac_off[4] = 0.0;  //SC42L-R       // fix to 0
    sci.tac_off[5] = 0.0;  //SC42L-SC21L   // fix to 0
    sci.tac_off[6] = 0.0;  //SC42R-SC21R   // fix to 0
    sci.tac_off[7] = 0.0;  //SC43L-R  // fix to 0
    sci.tac_off[8] = 0.0;  //SC81L-R  // fix to 0
    sci.tac_off[9] = 0.0;  //SC81L-SC21L  // fix to 0
    sci.tac_off[10]= 0.0;  //SC81R-SC21R  // fix to 0
    sci.tac_off[11] = 0.0;  //SC22L-R  // fix to 0
    sci.tac_off[12] = 0.0;  //SC41L-SC22L  // fix to 0
    sci.tac_off[13] = 0.0;  //SC41R-SC22R  // fix to 0
    sci.tac_off[14]= 0.0;  //SC81L-SC22L  // fix to 0
    sci.tac_off[15]= 0.0;  //SC81R-SC22R  // fix to 0

    //Offset found from fitting (Commented at this moment, 20-02-2020)
    /*
    sci.tac_off[0]  = 1299.5;  //SC21L-R    // fix to 0
    sci.tac_off[1]  = 1032.4;  //SC41L-R    // fix to 0
    sci.tac_off[2]  = 1295.6;  //SC41L-SC21L   // fix to 0
    sci.tac_off[3]  = 1150.;  //SC41R-SC21R   // fix to 0
    sci.tac_off[4]  = 1101.8;  //SC42L-R       // fix to 0
    sci.tac_off[5]  = 1354.8.;  //SC42L-SC21L   // fix to 0
    sci.tac_off[6]  = 1261.;  //SC42R-SC21R   // fix to 0
    sci.tac_off[7]  = 1276.4;  //SC43L-R  // fix to 0
    sci.tac_off[8]  = 930.5;  //SC81L-R  // fix to 0
    sci.tac_off[9]  = 1476.5;  //SC81L-SC21L  // fix to 0
    sci.tac_off[10] = 2731.3;  //SC81R-SC21R  // fix to 0
    sci.tac_off[11] = 1810.4;  //SC22L-R  // fix to 0
    sci.tac_off[12] = 1268.4;  //SC41L-SC22L  // fix to 0
    sci.tac_off[13] = 1326.2;  //SC41R-SC22R  // fix to 0
    sci.tac_off[14] =  2152.6;  //SC81L-SC22L  // fix to 0
    sci.tac_off[15] = 2040.3;  //SC81R-SC22R  // fix to 0
    */
    //2021/Feb/BARB 
    sci.tac_factor[0]  = 10.5293; //SC21L-R [ps/ch]     >> ch0 of ADC
    sci.tac_factor[1]  = 10.6934; //SC41L-R [ps/ch]     >> ch1 of ADC
    //sci.tac_factor[2]  = 43.6914; //SC41L-SC21L [ps/ch] >> ch5 of ADC
    // sci.tac_factor[3]  = 43.3264; //SC41R-SC21R [ps/ch] >> ch6 of ADC
    sci.tac_factor[4]  = 10.5367; //SC42L-R             >> ch2 of ADC
    //sci.tac_factor[5]  = 42.3307; //SC42L-SC21L [ps/ch] >> ch8 of ADC
    //sci.tac_factor[6]  = 41.6716; //SC42R-SC21R [ps/ch] >> ch7 of ADC
    sci.tac_factor[7]  = 11.0166; //SC43L-R [ps/ch]     >> ch3 of ADC
    sci.tac_factor[8]  = 10.5001; //SC81L-R [ps/ch]     >> ch4 of ADC
    sci.tac_factor[9]  = 20.7879; //SC81L-SC21L         >> ch9
    sci.tac_factor[10] = 19.9815; //SC81R-SC21R         >> ch10
    sci.tac_factor[11] = 10.5536; //SC22L-R             >> ch11
    //sci.tac_factor[12] = 39.9969; //SC41L-SC22L [ps/ch] >> ch12
    //sci.tac_factor[13] = 42.3244; //SC41R-SC22R [ps/ch] >> ch13
    sci.tac_factor[14] = 20.0000; //SC81L-SC22L [ps/ch] >> ch14
    sci.tac_factor[15] = 20.0000; //SC81R-SC22R [ps/ch] >> ch15

    //Interaction cross secton 1.Mar.2021 
    sci.tac_factor[2]  = 11.35; //SC41L-SC21L [ps/ch] >> ch5 of ADC   
    sci.tac_factor[3]  = 11.19; //SC41R-SC21R [ps/ch] >> ch6 of ADC
    sci.tac_factor[12] = 10.17; //SC41L-SC22L [ps/ch] >> ch12
    sci.tac_factor[13] = 10.78; //SC41R-SC22R [ps/ch] >> ch13
    sci.tac_factor[5]  = 10.84; //SC42L-SC21L [ps/ch] >> ch8 of ADC
    sci.tac_factor[6]  = 10.8; //SC42R-SC21R [ps/ch] >> ch7 of ADC

    
    sci.tof_bll2  = 1.;    // not used online [ps/ch]
    sci.tof_brr2  = 1.;    // not used online
    sci.tof_bll3  = 1.;    // not used online
    sci.tof_brr3  = 1.;    // not used online
    sci.tof_bll4  = 1.;    // not used online
    sci.tof_brr4  = 1.;    // not used online

    sci.tof_a2 = 146.46; // [ps] offset   Tof S41-S21
    sci.tof_a3 = 0.; // [ps] offset   Tof S42-S21
    sci.tof_a4 = 0.; // [ps] offset   Tof S81-S21

    // for multihitTDC
    sci.mhtdc_factor_ch_to_ns =  0.025;// tp be set in parameter...
    sci.mhtdc_offset_21l_21r  =  -39.6625+20.0;    sci.mhtdc_factor_21l_21r = 62.5341;  // pos = offset + factor*dt
    sci.mhtdc_offset_41l_41r  =  584.927;          sci.mhtdc_factor_41l_41r = 69.4128; // pos = offset + factor*dt
    sci.mhtdc_offset_42l_42r  =  0.0;              sci.mhtdc_factor_42l_42r = 60.0; // pos = offset + factor*dt
    sci.mhtdc_offset_43l_43r  =  0.0;              sci.mhtdc_factor_43l_43r = 60.0; // pos = offset + factor*dt
    sci.mhtdc_offset_31l_31r  =  0.0;              sci.mhtdc_factor_31l_31r = 60.0; // pos = offset + factor*dt
    sci.mhtdc_offset_81l_81r  =  -410.411;         sci.mhtdc_factor_81l_81r = 43.691; // pos = offset + factor*dt
    sci.mhtdc_offset_22l_22r  =  -39.6625+20.0;    sci.mhtdc_factor_22l_22r = 62.5341;  // pos = offset + factor*dt
    sci.mhtdc_offset_41_21  =  178.0; //ns
    sci.mhtdc_offset_42_21  =  0.0; //ns
    sci.mhtdc_offset_43_21  =  0.0; //ns
    sci.mhtdc_offset_31_21  =  0.0; //ns
    sci.mhtdc_offset_81_21  =  -400.0 + 165.214; //ns
    sci.mhtdc_offset_41_22  =  173.0; //ns

}

void EXT_FRS::Setup_Conditions()
{
    std::string line;
    int line_number = 0;

    const char* format = "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf";

    std::ifstream cond_a("s452/config/FRS/lim_csum.txt");

    constexpr auto ignore = std::numeric_limits<std::streamsize>::max();


    while (getline(cond_a, line, '\n'))
    {
        if (line[0] == '#') continue;

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
    format = "%lf %lf";

    std::ifstream cond_b("s452/config/FRS/lim_xsum.txt");

    while (getline(cond_b, line, '\n'))
    {
        if (line[0] == '#') continue;
        sscanf(line.c_str(),format,&lim_xsum[line_number][0],&lim_xsum[line_number][1]);

        line_number++;

    }

    line_number = 0;
    format = "%lf %lf";

    std::ifstream cond_c("s452/config/FRS/lim_ysum.txt");

    while (getline(cond_c, line, '\n'))
    {
        if (line[0] == '#') continue;
        sscanf(line.c_str(),format,&lim_ysum[line_number][0],&lim_ysum[line_number][1]);

        line_number++;

    }

    line_number = 0;
    format = "%lf %lf %lf %lf";

    std::ifstream cond_d("s452/config/FRS/MUSIC1.txt");

    while (getline(cond_d, line, '\n'))
    {
        if (line[0] == '#') continue;
        sscanf(line.c_str(),format,&cMusic1_E[line_number][0],&cMusic1_E[line_number][1],&cMusic1_T[line_number][0],&cMusic1_T[line_number][1]);

        line_number++;
    }

    line_number = 0;
    format = "%lf %lf %lf %lf";

    std::ifstream cond_e("s452/config/FRS/MUSIC2.txt");

    while (getline(cond_e, line, '\n'))
    {
        if (line[0] == '#') continue;
        sscanf(line.c_str(),format,&cMusic2_E[line_number][0],&cMusic2_E[line_number][1],&cMusic2_T[line_number][0],&cMusic2_T[line_number][1]);

        line_number++;
    }

    line_number = 0;
    format = "%lf %lf %lf %lf";

    std::ifstream cond_f("s452/config/FRS/MUSIC3.txt");
    
    while (getline(cond_f, line, '\n'))
    {
        if (line[0] == '#') continue;
        sscanf(line.c_str(),format,&cMusic3_E[line_number][0],&cMusic3_E[line_number][1],&cMusic3_T[line_number][0],&cMusic3_T[line_number][1]);

        line_number++;

    }

    line_number = 0;
    format = "%lf %lf";

    std::ifstream cond_g("s452/config/FRS/MUSIC_dEc3.txt");

    while (getline(cond_g, line, '\n'))
    {
        if (line[0] == '#') continue;
        sscanf(line.c_str(),format,&cMusic3_dec[0],&cMusic3_dec[1]);
    }

    for (int i = 0; i < 8; i++)
    {
        cTPC_SC_TIMEREF[i][0] = tpc.lim_timeref[i][0];
        cTPC_SC_TIMEREF[i][1] = tpc.lim_timeref[i][1];
    }

    for (int i = 0; i < 7; i++)
    {
        cTPC_LT0[i][0] = tpc.lim_lt[i][0][0];
        cTPC_LT0[i][1] = tpc.lim_lt[i][0][1];
        cTPC_RT0[i][0] = tpc.lim_rt[i][0][0];
        cTPC_RT0[i][1] = tpc.lim_rt[i][0][1];
        
        cTPC_LT1[i][0] = tpc.lim_lt[i][1][0];
        cTPC_LT1[i][1] = tpc.lim_lt[i][1][1];
        cTPC_RT1[i][0] = tpc.lim_rt[i][1][0];
        cTPC_RT1[i][1] = tpc.lim_rt[i][1][1];

        for (int j = 0; j < 4; j++)
        {
            cTPC_DT[i][j][0] = tpc.lim_dt[i][j][0];
            cTPC_DT[i][j][1] = tpc.lim_dt[i][j][1];
        }
    }

    line_number = 0;
    format = "%lf %lf";

    std::ifstream cond_h("s452/config/FRS/SCI_Cons.txt");

    while (getline(cond_h, line, '\n'))
    {
        if (line[0] == '#') continue;
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

    // all these were "%f" for floats
    format = "%lf %lf";

    std::ifstream cond_i("s452/config/FRS/SCI_LLRR.txt");

    while (getline(cond_i, line, '\n'))
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

    line_number = 0;
    format = "%lf %lf";

    std::ifstream cond_j("s452/config/FRS/SCI_dEToF.txt");

    while (getline(cond_j, line, '\n'))
    {
        if (line[0] == '#') continue;
        sscanf(line.c_str(),format,&cSCI_detof[line_number][0],&cSCI_detof[line_number][1]);

        line_number++;

    }

    format = "%lf %lf";

    std::ifstream cond_k("s452/config/FRS/ID_x2.txt");

    while (getline(cond_k, line, '\n'))
    {
        if (line[0] == '#') continue;
        sscanf(line.c_str(),format,&cID_x2[0],&cID_x2[1]);
    }

    std::ifstream cond_l("s452/config/FRS/ID_x4.txt");

    while (getline(cond_l, line, '\n'))
    {
        if (line[0] == '#') continue;
        sscanf(line.c_str(),format,&cID_x4[0],&cID_x4[1]);
    }

    std::ifstream cond_m("s452/config/FRS/ID_Z_Z.txt");

    while (getline(cond_m, line, '\n'))
    {
        if (line[0] == '#') continue;
        sscanf(line.c_str(),format,&cID_Z_Z[0],&cID_Z_Z[1]);
    }

    line_number = 0;

    std::ifstream cond_n("s452/config/FRS/ID_Z_Z.txt");

    while (getline(cond_n, line, '\n'))
    {
        if (line[0] == '#') continue;
        sscanf(line.c_str(),format,&cID_x4AoQ_Z[line_number][0],&cID_x4AoQ_Z[line_number][1]);

        line_number++;
    }

    line_number = 0;

    int selection_number = 0;

    std::ifstream cond_o("s452/config/FRS/ID_x2AoQ.txt");

    while (getline(cond_o, line, '\n'))
    {
        if (line[0] == '#') continue;
        if (line[0] == '&')
        {
            selection_number++;
            line_number = 0;
            continue;
        }

        sscanf(line.c_str(),format,&cID_x2AoQ[selection_number][line_number][0],&cID_x2AoQ[selection_number][line_number][1]);
        
        line_number++;

    }

    line_number = 0;
    int selection_number_2 = 0;

    std::ifstream cond_z("s452/config/FRS/ID_x4AoQ.txt");

    while (getline(cond_z, line, '\n'))
    {
        if (line[0] == '#') continue;
        if (line[0] == '&')
        {
            selection_number_2++;
            line_number = 0;
            continue;
        }
        sscanf(line.c_str(),format,&cID_x4AoQ[selection_number_2][line_number][0],&cID_x4AoQ[selection_number_2][line_number][1]);

        line_number++;
    }

    line_number = 0;
    selection_number = 0;

    std::ifstream cond_p("s452/config/FRS/ID_Z_AoQ.txt");

    while (getline(cond_p, line, '\n'))
    {
        if (line[0] == '#') continue;
        if (line[0] == '&')
        {
            selection_number++;
            line_number = 0;
            continue;
        }
        sscanf(line.c_str(),format,&cID_Z_AoQ[selection_number][line_number][0],&cID_Z_AoQ[selection_number][line_number][1]);

        line_number++;
    }

    line_number = 0;
    selection_number = 0;

    std::ifstream cond_q("s452/config/FRS/ID_dEToF.txt");

    while (getline(cond_q, line, '\n'))
    {
        if (line[0] == '#') continue;
        sscanf(line.c_str(),format,&cID_dEToF[line_number][0],&cID_dEToF[line_number][1]);

        line_number++;
    }

}

//template<typename subevent_header_t>
EXT_DECL_DATA_SRC_FCN_ARG(void, EXT_FRS::__unpack, int procid, int type, int subtype)
{   
    Setup_FRS_Parameters();
    Setup_Conditions();
    
    // auto & item = frs_info.append_item();
    auto & item = frs_info;

    // must do
    FRS_Unpack(__buffer, item, procid, type, subtype);
    // can we?
    FRS_Sort(item, procid, type, subtype);
    // fairroot
    FRS_Calib(item, procid, type, subtype);
    // fairroot
    FRS_Anal(item, procid, type, subtype);

}

EXT_FORCE_IMPL_DATA_SRC_FCN_ARG(void, EXT_FRS::__unpack, int procid, int type, int subtype);

template<typename __data_src_t>
void EXT_FRS::FRS_Unpack(__data_src_t &__buffer, frs_item &item, int procid, int type, int subtype)
{
    int lenMax = (int) __buffer.left() / 4; // number of words left
    int len = 0;
    uint32 data = 0;

    if (type == 36 && subtype == 3600) // tpat
    {
        item.skip = false; // does this need to be part of item?
        item.unbtrig = 0;

        for (int ii = 0; (ii < lenMax && ii < 32); ii++)
        {   
            __buffer.peek_uint32(&data);
            item.tpat_main[ii] = data;
            __buffer.advance(4);
        }

        if (lenMax >= 4)
        {
            item.utpat = (item.tpat_main[4] & 0xFFFF);
        }

        for (int it = 16; it > 0; --it)
        {   
          

            if ((item.utpat & ((int) std::pow(2, it - 1))) > 0)
            {   
                item.uphystrig = it;
                item.unbtrig += 1;
            }
        }

        if (item.unbtrig == 2)
        {   

            for (int it = 0; it < 16; it++)
            {
                if ((item.utpat & ((int) std::pow(2, it))) > 0)
                {   
                    
                    item.umaxtrig = it + 1;
                }
            }
        }

    }
    else if (type == 12 && subtype == 1) // procid = 10 is failing
    {   
        
        uint32 event_flag = 0;
        __buffer.peek_uint32(&event_flag); // unused?
        __buffer.advance(12);
    
        len += 3;

        // needed? cleaning should take care of this.
        for (int i = 0; i < 21; i++)
        {
            for (int j = 0; j < 32; j++)
            {
                 item.vme_main[i][j] = 0;
            }
        }

        switch (procid)
        {
            case 10: // "main crate" - here we are failing!! wait, how..
                
                /*while (!__buffer.empty())
                {
                    uint32 dummy = 0;
                    __buffer.get_uint32(&dummy);
                    std::cout << std::hex << dummy << std::dec << std::endl;
                }
                break;*/

                // this hack deals with all small data events that also screw up everything else
                if (lenMax < 15)
                {   
                    __buffer.peek_uint32(&data);

                    if (data == 0xBABABABA)
                    {
                        __buffer.advance(__buffer.left()); // to end somehow
                        break;
                    }
                }

                // v1290 TDC
                if (len < lenMax)
                {   
                    __buffer.peek_uint32(&data);
                    //int vme_geo = getbits(data, 1, 1, 5); // unusued in this scope
                    int vme_type = getbits(data, 2, 12, 5);
                    __buffer.advance(4);
                    len++;
                    
                    int multihit = 0; // counter = 0;
                    for (int i = 0; i < 32; i++)
                    {
                        for (int j = 0; j < 2; j++)
                        {
                            item.nhit_v1290_main[i][j] = 0;
                        }
                    }
                    
                    if (vme_type == 8)
                    {   
                        while (len < lenMax)
                        {   

                            __buffer.peek_uint32(&data);
                            vme_type = getbits(data, 2, 12, 5);
                            
                            if (vme_type == 1)
                            {
                                __buffer.advance(4);
                                len++;
                            }
                                
                            __buffer.peek_uint32(&data);
                            vme_type = getbits(data, 2, 12, 5);

                            if (vme_type == 0)
                            {   
                                // this indicates a TDC measurement
                                int vme_chn = getbits(data, 2, 6, 5);
                                int LeadingOrTrailing = getbits(data, 2, 11, 1);
                                int value = getbits(data, 1, 1, 21);

                               // std::cout << "channel: " << vme_chn << std::endl;

                                multihit = item.nhit_v1290_main[vme_chn][LeadingOrTrailing];
                                    
                                if (multihit >= 10)
                                {
                                    __buffer.advance(4);
                                    len++;
                                    continue;
                                }

                                    
                                if (LeadingOrTrailing == 0)
                                {   

                                    if (value > 0)
                                    {
                                        //std::cout << "leading" << std::endl;
                                        item.leading_v1290_main[vme_chn][multihit] = value;
                                    }
                                }
                                else
                                {       
                                    std::cout << "trailing without value" << std::endl;
                                    if (value > 0)
                                    {
                                        std::cout << "trailing" << std::endl;
                                        item.trailing_v1290_main[vme_chn][multihit] = value;
                                    }
                                }

                                item.nhit_v1290_main[vme_chn][LeadingOrTrailing]++;

                                __buffer.advance(4);
                                len++;
                            }
                            else
                            {
                                // TDC trailer
                                if (vme_type == 16)
                                {   
                                    //__buffer.peek_uint32(&data);
                                    // unusused here entirely
                                    //int vme_geoEnd = getbits(data, 1, 1, 5); 
                                        
                                    __buffer.advance(4);
                                    len++;
                                    break;
                                }

                                __buffer.advance(4);
                                len++;
                            }
                        } // while len < lenMax loop
                    } // if type == 8
                } // v1290

                __buffer.advance(4);
                len++;

                if (len == lenMax)
                {
                    break;
                }

                // Next is V830 scaler
                {   
                    __buffer.peek_uint32(&data);

                    //int vme_geo = getbits(data, 2, 12, 5); // unused in this scope
                    //int vme_type = getbits(data, 2, 9, 3); // unused in this scope
                    int vme_nlw = getbits(data, 2, 3, 6);

                    __buffer.advance(4);
                    len++;

                    for (int i_ch = 0; i_ch < vme_nlw; i_ch++)
                    {   
                        __buffer.peek_uint32(&data);
                        item.scaler_main[i_ch] = data;

                        __buffer.advance(4);
                        len++;
                    }
                } // end of V830

                // V792
                {   
                    __buffer.peek_uint32(&data);
                    int vme_chn = 0;
                    int vme_geo = getbits(data, 2, 15, 5);
                    int vme_type = getbits(data, 2, 9, 3);
                    int vme_nlw = getbits(data, 1, 9, 6);

                    __buffer.advance(4);
                    len++;

                    if (vme_type == 6)
                    {
                        // not valid data
                    }

                    if ((vme_type == 2) && (vme_nlw > 0))
                    {
                        for (int i = 0; i < vme_nlw; i++)
                        {   
                            __buffer.peek_uint32(&data);
                            //vme_geo = getbits(data, 2, 12, 5); // commenting out for now since it gets reassigned
                            vme_type = getbits(data, 2, 9, 3);
                            vme_chn = getbits(data, 2, 1, 5);

                            vme_geo = 4; // first line seems pointless but ok
                            item.vme_main[vme_geo][vme_chn] = getbits(data, 1, 1, 16);

                            __buffer.advance(4);
                            len++;
                        }

                        __buffer.advance(4);
                        len++;
                    }
                } // end of a while loop in Go4 that is commented out
                    
                // second V792 commented out in Go4

                // janky hack
                if (__buffer.left())
                {
                    for (int n = 0; n < 5; n++)
                    {
                        uint32 test = 0;
                        __buffer.peek_uint32(&test);
                        //std::cout << std::hex << test << std::dec << std::endl;
                        __buffer.advance(4);
                    }
                }
    
                break; // case 10
                
            case 20: // "tpc crate"

                // added in !__buffer.empty() to prevent crashes
                for (int ii = 0; (ii < 17 && !__buffer.empty()); ii++)
                {   
                    __buffer.advance(4);
                    len++;
                }

                for (int ii = 0; ii < 128; ii++)
                {
                    item.nhit_v1190_tpcs2[ii] = 0;
                }

                // checking buffer left rather than len == lenMax is nicer I think.
                if (__buffer.left() == 0)
                {
                    break;
                }
                else
                {
                    __buffer.advance(4);
                    len++;
                    if (__buffer.left() == 0)
                    {
                        break;
                    }
                }

                __buffer.peek_uint32(&data);
                while ((len < lenMax) && (data) != 0xBABABABA)
                {
                    int type_tpc_v1190 = ((data >> 27) & 0x1F);

                    if (type_tpc_v1190 == 0x8)
                    {
                        // global header, ignore
                    }
                    else if (type_tpc_v1190 == 0x1)
                    {
                        // TDC header, ignore
                    }
                    else if (type_tpc_v1190 == 0x3)
                    {
                        // TDC trailer, ignore
                    }
                    else if (type_tpc_v1190 == 0x4)
                    {
                        // error status
                        std::cout << "TPC Crate, V1190, error data are found: " << std::hex << data << std::dec << std::endl; // flush
                    }
                    else if (type_tpc_v1190 == 0x10)
                    {
                        // global trailer, ignore
                    }
                    else if (type_tpc_v1190 == 0x0)
                    {
                        // this is real data
                        int ch_tpc_v1190 = ((data >> 19) & 0x7F);
                        int check_leading_tpc_v1190 = ((data >> 26) & 0x1); // 0 leading, 1 trailing
                        int data_tpc_v1190 = (data & 0x7FFFF); 

                        if (check_leading_tpc_v1190 == 0)
                        {
                            item.tmp_nhit_prev = item.nhit_v1190_tpcs2[ch_tpc_v1190];
                            item.nhit_v1190_tpcs2[ch_tpc_v1190]++;

                            if(item.tmp_nhit_prev < 16) // max 16 prepared. 64 used in sort.
                            {
                                item.leading_v1190_tpcs2[ch_tpc_v1190][item.tmp_nhit_prev] = data_tpc_v1190;
                            }

                        }

                    }
                    else
                    {
                        std::cout << "TPC crate, V1190, strange data are found: " << std::hex << data << std::dec << std::endl; // flush
                    }

                    __buffer.advance(4);
                    len++;
                    __buffer.peek_uint32(&data); // update data now for while loop to continue

                } // end of TDC V1190

                // check if end of this procid (with/without barrier)
                if (len == lenMax)
                {
                    break;
                }
                if (data == 0xBABABABA)
                {
                    __buffer.advance(4);
                    len++;
                }
                if (len == lenMax)
                {
                    break;
                }

                // from here, 2 ADCs (optional)
                while (len < lenMax)
                {   
                    __buffer.peek_uint32(&data);
                    int vme_type = ((data >> 24) & 0x7);
                    int vme_geo = ((data >> 27) & 0x1F);
                        
                    if (vme_type == 2)
                    {
                        // header, ignore
                    }
                    else if (vme_type == 4)
                    {
                        // end-of-block, ignore
                    }
                    else if (vme_type == 0)
                    {
                        // data
                        int vme_chn = ((data >> 16) & 0x3F);
                        int vme_data = (data & 0x3FFF);
                        item.vme_tpcs2[vme_geo][vme_chn] = vme_data;
                    }
                    else if (data == 0xBABABABA)
                    {
                        // barrier between 2 ADCs, for example, ignore
                    }
                    else
                    {
                        // unknown word
                        std::cout << "TPC crate, ADC data, strange data are found: " << std::hex << data << std::dec << std::endl;
                    }

                    __buffer.advance(4);
                    len++;
                }

                break;
                
            case 30: // "frs crate"

                { // start of V830 - do not remove this bracket
                        
                    int isADCgeo2 = 0;

                    __buffer.peek_uint32(&data);

                    int scalertest = getbits(data, 2, 5, 12);
                    if (scalertest == 72) // 0x48
                    {
                        int vme_geo = getbits(data, 2, 12, 5);
                        int vme_type = getbits(data, 2, 9, 3);
                        int vme_nlw = getbits(data, 2, 3, 6);

                        __buffer.advance(4);
                        len++;

                        if (vme_type != 4)
                        {
                            std::cout << "E> Scaler type missed match ! Proc ID 30 GEO " << vme_geo << " type 4 =/=" << vme_type << std::endl; 
                            break;
                        }

                        for (int i_ch = 0; i_ch < vme_nlw; i_ch++)
                        {   
                            __buffer.peek_uint32(&data);
                            item.scaler_frs[i_ch] = data;
                            item.scaler_frs_elements.push_back(i_ch); // CEJ: is this something i added? check
                                  
                            __buffer.advance(4);
                            len++;
                        }
                    } // end of V830

                    // --- V775 TDC / V785 ADC ---- //
                    while (len < lenMax)
                    {   
                        __buffer.peek_uint32(&data);
                        int vme_chn = 0;
                        int vme_geo = getbits(data, 2, 12, 5);
                        int vme_type = getbits(data, 2, 9, 3);
                        int vme_nlw = getbits(data, 1, 9, 6);

                        __buffer.advance(4);
                        len++;

                        if (vme_geo == 2)
                        {
                            isADCgeo2 = 1;
                        }

                        if ((vme_type == 2) && (vme_nlw > 0))
                        {
                            for (int i = 0; i < vme_nlw; i++)
                            {   
                                __buffer.peek_uint32(&data);
                                vme_geo = getbits(data, 2, 12, 5);
                                vme_type = getbits(data, 2, 9, 3);
                                vme_chn = getbits(data, 2, 1, 5);
                                item.vme_frs[vme_geo][vme_chn] = getbits(data, 1, 1, 16);

                                __buffer.advance(4);
                                len++;
                            }
                        }

                        // sanity check after V7X5 unpacking
                        __buffer.peek_uint32(&data);
                        vme_type = getbits(data, 2, 9, 3);
                        if (vme_type != 4)
                        {
                            std::cout << "issue in unpacking Proc Id 30, exiting " <<std::endl; 
                            break;
                        }

                        __buffer.advance(4);
                        len++;

                    } // end of while loop

                    if (isADCgeo2 == 1)
                    {
                        for (int i = 0; i < 32; i++)
                        {
                            item.vme_frs[3][i] = item.vme_frs[2][i];
                        }
                    }

                }

                break; // procid 30
                
            case 35: 
                // vftx at S2 SOFIA

                uint32 p32_tmp, marker;
                uint16 cnt, channel; // how/why are we redefining this???
                int word;

                for (int module = 0; module < VFTX_N; module++)
                {
                    for (int channel = 0; channel < VFTX_MAX_CHN; channel++)
                    {
                        for (int hit = 0; hit < VFTX_MAX_HITS; hit++)
                        {
                            item.vftx_cc[module][channel][hit] = 0;
                            item.vftx_ft[module][channel][hit] = 0;
                        }
                        item.vftx_mult[module][channel] = 0;
                    }
                    
                } // first module loop -- GO4 code is stupid and doesn't use brackets for this.

                for (int module = 0; module < VFTX_N; module++)
                {   
                    __buffer.peek_uint32(&p32_tmp);
                    __buffer.advance(4);
                    len++; // I think this is necessary but GO4 doesn't do

                    marker = ((p32_tmp >> 24) & 0xFF); // most significant 8 bits
                    cnt = ((p32_tmp >> 9) & 0x1FF); // bits 9-17;
                            
                    if (marker == 0xAB000000)
                    {   
                        __buffer.peek_uint32(&p32_tmp);
                        __buffer.advance(4);
                        len++; // I think this is necessary but GO4 doesn't do

                        for (word = 0; word < cnt - 1; word++)
                        {   
                            __buffer.peek_uint32(&p32_tmp);
                            __buffer.advance(4);
                            len++; // i think this is necessary, but it is not done in GO4 code.

                            channel = (uint16) getbits(p32_tmp, 2, 11, 5);

                            if (item.vftx_mult[module][channel] < VFTX_MAX_HITS)
                            {
                                item.vftx_cc[module][channel][item.vftx_mult[module][channel]] = ((p32_tmp >> 11) & 0x1FFF); // bits 11 - 23
                                item.vftx_ft[module][channel][item.vftx_mult[module][channel]] = (p32_tmp & 0x7FF); // least significant 11 digits
                                // histogram filling???? surely not here. //h1_vftx_ft[module][channel]->Fill(vftx_ft[module][channel][0]);
                            }
                            item.vftx_mult[module][channel]++;
                        }

                        #if CALIBRATION_VFTX
                        for (channel = 0; channel < VFTX_MAX_CHN; channel++)
                        {
                            Vftx_Stat[module][channel]++;
                            std::cout << "Vftx_Stat[module][channel] " << Vftx_Stat[module][channel] << " module " << module << " channel " << channel << std::endl;
                            if (Vftx_Stat[module][channel] == 25000)
                            {
                                VFTX_Calibration(module, channel);
                            }
                        }
                        #endif
                                
                    } // marker = 0xAB000000
                            
                } // second module loop

                __buffer.advance(4); // this advances beyond a barrier
                len++;
                if (len == lenMax)
                {
                    break;
                }

                { // Mesytec MQDC-32

                    int vme_geo = 11;
                    while (len < lenMax)
                    {
                        __buffer.advance(4);
                        len++;

                        __buffer.peek_uint32(&data);
                        int vme_type = getbits(data, 2, 15, 2);
                        //int module_id = getbits(data, 2, 1, 8); // unused in this scope

                        if (vme_type == 1) // header
                        {
                            int vme_nlw = getbits(data, 1, 1, 12);
                            __buffer.advance(4);
                            len++;

                            __buffer.peek_uint32(&data);
                            int vme_type = getbits(data, 2, 15, 2);

                            if ((vme_type == 0) && (vme_nlw > 0) && !__buffer.empty()) // data
                            {
                                for (int i = 0; i < vme_nlw; i++)
                                {   
                                    __buffer.peek_uint32(&data);
                                    int vme_chn = getbits(data, 2, 1, 5);
                                    int value = getbits(data, 1, 1, 12);
                                    //int overflow = getbits(data, 1, 16, 1); // unusued in this scope
                                        
                                    if (value > 0)
                                    {
                                        item.vme_tof[vme_geo][vme_chn] = value;
                                    }

                                    __buffer.advance(4);
                                    len++;
                                }
                            }
                            else if (vme_type == 3)
                            {
                                std::cout << "This is the end of module 0." << std::endl;
                            }
                        }
                    }
                } // end of Mesytec MQDC-32

                { // Mesytec MTDC-32
                    int vme_geo = 16;

                    while (len < lenMax)
                    {
                        __buffer.advance(4);
                        len++;
                        __buffer.peek_uint32(&data);
                        //int module_id = getbits(data, 2, 1, 8); // unused in this scope
                        int vme_type = getbits(data, 2, 15, 2);
                        //int hit = 0; // unused in this scope

                        if (vme_type == 1) // oh shit is this going to screw things up..
                        {
                            int vme_nlw = getbits(data, 1, 1, 12);

                            for (int ii = 0; ii < vme_nlw; ii++)
                            {
                                __buffer.advance(4);
                                __buffer.peek_uint32(&data);

                                int value = getbits(data, 1, 1, 16);

                                if (vme_type == 0)
                                {
                                    int vme_chn = getbits(data, 2, 1, 5);
                                    //int vme_trig = getbits(data, 2, 6, 1); // entirely unused in available GO4 code.

                                    item.vme_tof[vme_geo][vme_chn] = value;
                                }
                                else if (getbits(data, 2, 15, 2) == 3)
                                {
                                    std::cout << "This is end of module 0." << std::endl;
                                }
                                else
                                {
                                    std::cout << "Unknown data for vme_tof" << std::endl;
                                }
                            }
                        }
                    }

                    // check if end of this procid (with/without barrier)
                    if (len == lenMax)
                    {
                        break;
                    }
                    if (data != 0xBABABABA)
                    {
                        __buffer.advance(4);
                        len++;
                    }
                    if (len == lenMax) // this kinda seems pointless as it just breaks next anyway?
                    {
                        break;
                    }

                } // end of Mesytec MTDC-32

                break; // procid 35
        } // switch
    }
}

void EXT_FRS::FRS_Sort(frs_item &item, int procid, int type, int subtype)
{
    // CEJ:
    // none of this is used further, deal with in c4 or come back to later
    /*
    item.ts_word[0] = item.timestamp_main[0];
    item.ts_word[1] = item.timestamp_main[1];
    item.ts_word[2] = item.timestamp_main[2];
    item.ts_word[3] = item.timestamp_main[3];
 
    item.timestamp = item.ts_word[0] | (item.ts_word[1] << 16) | (item.ts_word[2] << 32) | (item.ts_word[3] << 48); // static case as uint64?
    
    item.tsys_word[0] = item.ts_word[0] | (item.ts_word[1] << 16); // ts low word
    item.tsys_word[1] = (item.ts_word[2] << 32) | (item.ts_word[3] << 48); // ts high word, we don't use.. thanks FRS team

    if (item.PreviousTS < 0) 
    {
        item.tsys_word[2] = 0;
    }
    else
    {
        item.tsys_word[2] = (item.timestamp - item.PreviousTS) * 1.e-5; // ms time since the previous s time (ftime routine)
    }

    item.systemtime_s = item.tsys_word[2] * 1e-3;
    item.systemtime_ms = item.tsys_word[2];

    if (item.qtrigger == 12)
    {   
        // in FRS code "Spill" is not spelled correctly but its driving me nuts
        item.StartOfSpillTime = item.timestamp;
        item.StartOfSpillTime2 = item.timestamp;
    }
    else if (item.qtrigger = 13)
    {
        item.StartOfSpillTime = -1;
    }

    if (item.StartOfSpillTime >= 0)
    {
        item.timespill = (item.timestamp - item.StartOfSpillTime) * 1e-2; // microsec // 50000000.;
    }

    item.timespill2 = (item.timestamp - item.StartOfSpillTime2) * 1e-2; // microsec // 50000000.;
    */

    // trigger and TPAT
    item.trigger = item.qtrigger; // no bloody clue where this is non-zero
    item.pattern = item.utpat; // either 1 or 256 apparently?
    item.sptrigger = item.uphystrig;
    item.snbtrig = item.unbtrig;
    item.smaxtrig = item.umaxtrig;

    // scalers
    if (procid == 30 && type == 12)
    {
        for (int i = 0; i < 32; ++i)
        {   
            // "long" may just have to be done differently with UCESB...lets see
            item.sc_long[i] = item.scaler_frs[i]; // frs crate
            item.sc_long[i+32] = item.scaler_main[i]; // main crate
        }
    }

    // TPC part
    // ADC

    // TPC 1 at S2 (TPC 21) in vacuum
    item.tpc_a[0][0] = item.vme_tpcs2[12][0] & 0xFFF;
    item.tpc_a[0][1] = item.vme_tpcs2[12][1] & 0xFFF;
    item.tpc_a[0][2] = item.vme_tpcs2[12][2] & 0xFFF;
    item.tpc_a[0][3] = item.vme_tpcs2[12][3] & 0xFFF;
    item.tpc_l[0][0] = item.vme_tpcs2[12][4] & 0xFFF;
    item.tpc_r[0][0] = item.vme_tpcs2[12][5] & 0xFFF;
    item.tpc_l[0][1] = item.vme_tpcs2[12][6] & 0xFFF;
    item.tpc_r[0][1] = item.vme_tpcs2[12][7] & 0xFFF;

    // TPC 2 at S2 (TPC 22) in vacuum
    item.tpc_a[1][0] = item.vme_tpcs2[12][8] & 0xFFF;
    item.tpc_a[1][1] = item.vme_tpcs2[12][9] & 0xFFF;
    item.tpc_a[1][2] = item.vme_tpcs2[12][10] & 0xFFF;
    item.tpc_a[1][3] = item.vme_tpcs2[12][11] & 0xFFF;
    item.tpc_l[1][0] = item.vme_tpcs2[12][12] & 0xFFF;
    item.tpc_r[1][0] = item.vme_tpcs2[12][13] & 0xFFF;
    item.tpc_l[1][1] = item.vme_tpcs2[12][14] & 0xFFF;
    item.tpc_r[1][1] = item.vme_tpcs2[12][15] & 0xFFF;

    // TPC 3 at S2 (TPC 23) in air
    item.tpc_a[2][0] = item.vme_tpcs2[12][16] & 0xFFF;
    item.tpc_a[2][1] = item.vme_tpcs2[12][17] & 0xFFF;
    item.tpc_a[2][2] = item.vme_tpcs2[12][18] & 0xFFF;
    item.tpc_a[2][3] = item.vme_tpcs2[12][19] & 0xFFF;
    item.tpc_l[2][0] = item.vme_tpcs2[12][20] & 0xFFF;
    item.tpc_r[2][0] = item.vme_tpcs2[12][21] & 0xFFF;
    item.tpc_l[2][1] = item.vme_tpcs2[12][22] & 0xFFF;
    item.tpc_r[2][1] = item.vme_tpcs2[12][23] & 0xFFF;

    // TPC 4 at S2 (TPC 24) in air
    item.tpc_a[3][0] = item.vme_tpcs2[12][24] & 0xFFF;
    item.tpc_a[3][1] = item.vme_tpcs2[12][25] & 0xFFF;
    item.tpc_a[3][2] = item.vme_tpcs2[12][26] & 0xFFF;
    item.tpc_a[3][3] = item.vme_tpcs2[12][27] & 0xFFF;
    item.tpc_l[3][0] = item.vme_tpcs2[12][28] & 0xFFF;
    item.tpc_r[3][0] = item.vme_tpcs2[12][29] & 0xFFF;
    item.tpc_l[3][1] = item.vme_tpcs2[12][30] & 0xFFF;
    item.tpc_r[3][1] = item.vme_tpcs2[12][31] & 0xFFF;

    // TPC 5 at S4 (TPC 41) in air
    item.tpc_a[4][0] = item.vme_tpcs2[2][0] & 0xFFF;
    item.tpc_a[4][1] = item.vme_tpcs2[2][1] & 0xFFF;
    item.tpc_a[4][2] = item.vme_tpcs2[2][2] & 0xFFF;
    item.tpc_a[4][3] = item.vme_tpcs2[2][3] & 0xFFF;
    item.tpc_l[4][0] = item.vme_tpcs2[2][4] & 0xFFF;
    item.tpc_r[4][0] = item.vme_tpcs2[2][5] & 0xFFF;
    item.tpc_l[4][1] = item.vme_tpcs2[2][6] & 0xFFF;
    item.tpc_r[4][1] = item.vme_tpcs2[2][7] & 0xFFF;

    // TPC 6 at S4 (TPC 42) in air
    item.tpc_a[5][0] = item.vme_tpcs2[2][8] & 0xFFF;
    item.tpc_a[5][1] = item.vme_tpcs2[2][9] & 0xFFF;
    item.tpc_a[5][2] = item.vme_tpcs2[2][10] & 0xFFF;
    item.tpc_a[5][3] = item.vme_tpcs2[2][11] & 0xFFF;
    item.tpc_l[5][0] = item.vme_tpcs2[2][12] & 0xFFF;
    item.tpc_r[5][0] = item.vme_tpcs2[2][13] & 0xFFF;
    item.tpc_l[5][1] = item.vme_tpcs2[2][14] & 0xFFF;
    item.tpc_r[5][1] = item.vme_tpcs2[2][15] & 0xFFF;

    // TPC at S3 (TPC 31) (checkSB)
    item.tpc_a[6][0] = item.vme_tpcs2[2][16] & 0xFFF;
    item.tpc_a[6][1] = item.vme_tpcs2[2][17] & 0xFFF;
    item.tpc_a[6][2] = item.vme_tpcs2[2][18] & 0xFFF;
    item.tpc_a[6][3] = item.vme_tpcs2[2][19] & 0xFFF;
    item.tpc_l[6][0] = item.vme_tpcs2[2][20] & 0xFFF;
    item.tpc_r[6][0] = item.vme_tpcs2[2][21] & 0xFFF;
    item.tpc_l[6][1] = item.vme_tpcs2[2][22] & 0xFFF;
    item.tpc_r[6][1] = item.vme_tpcs2[2][23] & 0xFFF;

    // TDC

    // NEEDED
    /*
    * tpc_nhit_dt; not nhit_v1190_tpcs, not leading_v1190_tpcs2
    * tpc_dt
    * 
    */
    for (int itpc = 0; itpc < 7; itpc++)
    {
        // anode
        for (int j = 0; j < 4; j++)
        {
            item.tpc_nhit_dt[itpc][j] = item.nhit_v1190_tpcs2[ (item.v1190_channel_dt[itpc][j]) ];
            for (int ihit = 0; ihit < (item.tpc_nhit_dt[itpc][j]); ihit++)
            {
                if (ihit < 64)
                {
                    item.tpc_dt[itpc][j][ihit] = item.leading_v1190_tpcs2[ (item.v1190_channel_dt[itpc][j]) ][ihit];
                }
            }
        }

        // delay line
        for (int j = 0; j < 2; j++)
        {   
            // left side
            item.tpc_nhit_lt[itpc][j] = item.nhit_v1190_tpcs2[ (item.v1190_channel_lt[itpc][j]) ];
            for (int ihit = 0; ihit < (item.tpc_nhit_lt[itpc][j]); ihit++)
            {
                if (ihit < 64)
                {
                    item.tpc_lt[itpc][j][ihit] = item.leading_v1190_tpcs2[ (item.v1190_channel_lt[itpc][j]) ][ihit];
                }
            }

            // right side
            item.tpc_nhit_rt[itpc][j] = item.nhit_v1190_tpcs2[ (item.v1190_channel_rt[itpc][j]) ];
            for (int ihit = 0; ihit < (item.tpc_nhit_rt[itpc][j]); ihit++)
            {
                if (ihit < 64)
                {
                    item.tpc_rt[itpc][j][ihit] = item.leading_v1190_tpcs2[ (item.v1190_channel_rt[itpc][j]) ][ihit];
                }
            }
        }

        // calib grid
        item.tpc_nhit_calibgrid[itpc] = item.nhit_v1190_tpcs2[ (item.v1190_channel_calibgrid[itpc]) ];
        for (int ihit = 0; ihit < (item.tpc_nhit_calibgrid[itpc]); ihit++)
        {
            if (ihit < 64)
            {
                item.tpc_calibgrid[itpc][ihit] = item.leading_v1190_tpcs2[ (item.v1190_channel_calibgrid[itpc]) ][ihit];
            }
        }
    }

    // TPC time ref TDCs
    for (int i = 0; i < 8; i++)
    {
        item.tpc_nhit_timeref[i] = item.nhit_v1190_tpcs2[ (item.v1190_channel_timeref[i]) ];
        for (int ihit = 0; ihit < (item.tpc_nhit_timeref[i]); ihit++)
        {
            if (ihit < 64)
            {
                item.tpc_timeref[i][ihit] = item.leading_v1190_tpcs2[ (item.v1190_channel_timeref[i]) ][ihit];
            }
        }
    }

    // can this possibly be required
    item.de_21l = 0;
    item.de_21r = 0;
    item.de_41l = 0;
    item.de_41r = 0;
    item.de_42l = 0;
    item.de_42r = 0;
    item.de_43l = 0;
    item.de_43r = 0;
    item.de_81l = 0;
    item.de_81r = 0;
    item.de_31l = 0; 
    item.de_31r = 0;
    // i don't think so

    item.de_41l = item.vme_main[4][13] & 0xFFF;
    item.de_41r = item.vme_main[4][1] & 0xFFF;
    item.de_21l = item.vme_main[4][2] & 0xFFF;
    item.de_21r = item.vme_main[4][3] & 0xFFF;
    item.de_42l = item.vme_main[4][4] & 0xFFF;
    item.de_42r = item.vme_main[4][5] & 0xFFF;
    item.de_31l = item.vme_main[4][9] & 0xFFF;
    item.de_31r = item.vme_main[4][7] & 0xFFF;
    item.de_43l = item.vme_main[4][11] & 0xFFF;
    item.de_43r = item.vme_main[4][12] & 0xFFF;
    //  de_81l = vme_main[11][13] & 0xfff; // changed on 21/Feb/2020 23:00
    item.de_81l = item.vme_main[4][15] & 0xFFF; // changed on 21/Feb/2020 23:00
    item.de_81r = item.vme_main[4][14] & 0xFFF;
    item.de_81l = item.vme_main[4][0] & 0xFFF; // sweapped with SC22L. This channel has problem!!! 21 Feb 2021
    item.de_81r = item.vme_main[4][14] & 0xFFF;
    //  de_22l = vme_main[4][0] & 0xfff; // changed on 17/Feb/2021
    item.de_22l = item.vme_main[4][15] & 0xFFF; // changed on 17 Feb 2021, ch0 QDC seems to have a problem
    item.de_22r = item.vme_main[4][8] & 0xFFF;

    
    // SCI times:
    item.dt_21l_21r = item.vme_frs[12][0] & 0xFFF;
    item.dt_41l_41r = item.vme_frs[12][1] & 0xFFF;
    item.dt_42l_42r = item.vme_frs[12][2] & 0xFFF;
    item.dt_43l_43r = item.vme_frs[12][3] & 0xFFF;
    item.dt_81l_81r = item.vme_frs[12][4] & 0xFFF;
    item.dt_21l_41l = item.vme_frs[12][5] & 0xFFF;
    item.dt_21r_41r = item.vme_frs[12][6] & 0xFFF;
    item.dt_42r_21r = item.vme_frs[12][7] & 0xFFF;//swapped recently 28/02/2020
    item.dt_42l_21l = item.vme_frs[12][8] & 0xFFF;//swapped recently 28/02/2020
    item.dt_21l_81l = item.vme_frs[12][9] & 0xFFF;
    item.dt_21r_81r = item.vme_frs[12][10] & 0xFFF;
    item.dt_22l_22r = item.vme_frs[12][11] & 0xFFF;
    item.dt_22l_41l = item.vme_frs[12][12] & 0xFFF;
    item.dt_22r_41r = item.vme_frs[12][13] & 0xFFF;
    item.dt_22l_81l = item.vme_frs[12][14] & 0xFFF;
    item.dt_22r_81r = item.vme_frs[12][15] & 0xFFF;

    // time raw in ps from VFTX module
    if (subtype == 1)
    {
        float r = 0.;
        for (int i = 0; i < 32; i++)
        {
            if ((item.vftx_cc[SCI_MOD][i][0] != 0) && (item.vftx_ft[SCI_MOD][i][0] != 0))
            {   
                // this is a number between 0 and 1 with 0.5 subtracted
                //r  = (double) rand.Rndm() - 0.5; // uses TRandom3 
                //r = (double) rand() - 0.5;
                item.TRaw_vftx[i] = VFTX_GetTraw_ps(item, SCI_MOD, i, item.vftx_cc[SCI_MOD][i][0], item.vftx_ft[SCI_MOD][i][0], rand3());
            }
        }

        item.TRaw_vftx_21l = item.TRaw_vftx[SCI21L_CH];
        item.TRaw_vftx_21r = item.TRaw_vftx[SCI21R_CH];
        item.TRaw_vftx_22l = item.TRaw_vftx[SCI22L_CH];
        item.TRaw_vftx_22r = item.TRaw_vftx[SCI22R_CH];
        item.TRaw_vftx_41l = item.TRaw_vftx[SCI41L_CH];
        item.TRaw_vftx_41r = item.TRaw_vftx[SCI41R_CH];
        item.TRaw_vftx_42l = item.TRaw_vftx[SCI42L_CH];
        item.TRaw_vftx_42r = item.TRaw_vftx[SCI42R_CH];
    }

    for (int i = 0; i < 10; i++)
    {
        item.tdc_sc41l[i] = item.leading_v1290_main[0][i];
        item.tdc_sc41r[i] = item.leading_v1290_main[1][i];
        item.tdc_sc21l[i] = item.leading_v1290_main[2][i];
        item.tdc_sc21r[i] = item.leading_v1290_main[3][i];
        item.tdc_sc42l[i] = item.leading_v1290_main[10][i]; //changed mapping 03.03.21
        item.tdc_sc42r[i] = item.leading_v1290_main[15][i]; //changed mapping 03.03.21
        item.tdc_sc43l[i] = item.leading_v1290_main[6][i];
        item.tdc_sc43r[i] = item.leading_v1290_main[7][i];
        item.tdc_sc81l[i] = item.leading_v1290_main[8][i];
        item.tdc_sc81r[i] = item.leading_v1290_main[9][i];
        //tdc_sc31l[i] = leading_v1290_main[10][i]; //changed mapping 03.03.21
        item.tdc_sc31r[i] = item.leading_v1290_main[11][i];
        item.tdc_sc11[i]  = item.leading_v1290_main[12][i];
        item.tdc_sc22l[i] = item.leading_v1290_main[13][i];
        item.tdc_sc22r[i]  = item.leading_v1290_main[14][i];
    }

    // MUSIC configuration. 2x TUM-MUSIC from FRS crate and 1 TRavel-MUsic from TRMU crate
    for (int i = 0; i < 8; i++)
    {   
        item.music_e1[i] = (item.vme_frs[3][i]) & 0xFFF;
        item.music_e2[i] = (item.vme_frs[3][8+i]) & 0xFFF;
        item.music_e3[i] = (item.vme_trmu_adc[i]);

        item.music_t1[i] = item.leading_v1290_main[16+i][0] & 0xFFF; // TUM-MUSIC
        item.music_t2[i] = item.leading_v1290_main[24+i][0] & 0xFFF; // TUM-MUSIC
        item.music_t3[i] = (item.vme_trmu_tdc[i]); // Travel-MUSIC (from special VME crate)
    }

    // CEJ:
    // these should all be defined somewhere else. it is ridiculous that it is done every time here.
    // also it means that for the first event they are zero.

    item.v1190_channel_dt[0][0] = 0; //TPC21-A11
    item.v1190_channel_dt[0][1] = 1; //TPC21-A12
    item.v1190_channel_dt[0][2] = 2; //TPC21-A21
    item.v1190_channel_dt[0][3] = 3; //TPC21-A22
    item.v1190_channel_lt[0][0] = 4; //TPC21-DL1
    item.v1190_channel_rt[0][0] = 5; //TPC21-DR1
    // 6, 7 empty
    item.v1190_channel_lt[0][1] = 8; //TPC21-DL2
    item.v1190_channel_rt[0][1] = 9; //TPC21-DR2
    item.v1190_channel_dt[1][0] = 10; //TPC22-A11
    item.v1190_channel_dt[1][1] = 11; //TPC22-A12
    item.v1190_channel_dt[1][2] = 12; //TPC22-A21
    item.v1190_channel_dt[1][3] = 13; //TPC22-A22
    // 14, 15 empty
    //17(top channel of 3rd module is dead)
    //18(skip)
    item.v1190_channel_lt[1][0] = 18; //TPC22-DL1
    item.v1190_channel_rt[1][0] = 19; //TPC22-DR1
    item.v1190_channel_lt[1][1] = 20; //TPC22-DL2
    item.v1190_channel_rt[1][1] = 21; //TPC22-DR2
    // 22,23 empty

    // ======= middle NIM crate (TPC23+24)=========
    item.v1190_channel_dt[2][0] = 24; //TPC23-A11
    item.v1190_channel_dt[2][1] = 25; //TPC23-A12
    item.v1190_channel_dt[2][2] = 26; //TPC23-A21
    item.v1190_channel_dt[2][3] = 27; //TPC23-A22
    item.v1190_channel_lt[2][0] = 28; //TPC23-DL1
    item.v1190_channel_rt[2][0] = 29; //TPC23-DR1
    //30,31 empty
    item.v1190_channel_lt[2][1] = 32; //TPC23-DL2
    item.v1190_channel_rt[2][1] = 33; //TPC23-DR2
    item.v1190_channel_dt[3][0] = 34; //TPC24-A11
    item.v1190_channel_dt[3][1] = 35; //TPC24-A12
    item.v1190_channel_dt[3][2] = 36; //TPC24-A21
    item.v1190_channel_dt[3][3] = 37; //TPC24-A22
    //38,39 empty
    item.v1190_channel_lt[3][0] = 40; //TPC24-DL1
    item.v1190_channel_rt[3][0] = 41; //TPC24-DR1
    item.v1190_channel_lt[3][1] = 42; //TPC24-DL2
    item.v1190_channel_rt[3][1] = 43; //TPC24-DR2
    //46,47 empty

    // ======= bottom NIM crate (TPC41+42+31)=========
    item.v1190_channel_dt[4][0] = 64; //TPC41-A11
    item.v1190_channel_dt[4][1] = 65; //TPC41-A12
    item.v1190_channel_dt[4][2] = 66; //TPC41-A21
    item.v1190_channel_dt[4][3] = 67; //TPC41-A22
    item.v1190_channel_lt[4][0] = 68; //TPC41-DL1
    item.v1190_channel_rt[4][0] = 69; //TPC41-DR1
    //70,71 empty
    item.v1190_channel_lt[4][1] = 72; //TPC41-DL2
    item.v1190_channel_rt[4][1] = 73; //TPC41-DR2
    item.v1190_channel_dt[5][0] = 74; //TPC42-A11
    item.v1190_channel_dt[5][1] = 75; //TPC42-A12
    item.v1190_channel_dt[5][2] = 76; //TPC42-A21
    item.v1190_channel_dt[5][3] = 77; //TPC42-A22
    //78,79 empty
    item.v1190_channel_lt[5][0] = 80; //TPC42-DL1
    item.v1190_channel_rt[5][0] = 81; //TPC42-DR1
    item.v1190_channel_lt[5][1] = 82; //TPC42-DL2
    item.v1190_channel_rt[5][1] = 83; //TPC42-DR2
    item.v1190_channel_dt[6][0] = 84; //TPC31-A11
    item.v1190_channel_dt[6][1] = 85; //TPC31-A12
    //86,87 empty
    item.v1190_channel_dt[6][2] = 88; //TPC31-A21
    item.v1190_channel_dt[6][3] = 89; //TPC31-A22
    item.v1190_channel_lt[6][0] = 90; //TPC31-DL1
    item.v1190_channel_rt[6][0] = 91; //TPC31-DR1
    item.v1190_channel_lt[6][1] = 92; //TPC31-DL2
    item.v1190_channel_rt[6][1] = 93; //TPC31-DR2
    //94,95 empty

    //time reference signal
    item.v1190_channel_timeref[0] = 96; //accept trig
    item.v1190_channel_timeref[1] = 97; //sc21
    item.v1190_channel_timeref[2] = 98; //sc22
    item.v1190_channel_timeref[3] = 99; //sc31
    item.v1190_channel_timeref[4] = 100; //sc41
    item.v1190_channel_timeref[5] = 101; //
    item.v1190_channel_timeref[6] = 102; //
    item.v1190_channel_timeref[7] = 103; //

    //
    item.v1190_channel_calibgrid[0] = 104;//tpc21grid
    item.v1190_channel_calibgrid[1] = 105;//tpc22grid
    item.v1190_channel_calibgrid[2] = 106;//tpc23grid
    item.v1190_channel_calibgrid[3] = 107;//tpc24grid
    item.v1190_channel_calibgrid[4] = 108;//tpc41grid
    item.v1190_channel_calibgrid[5] = 109;//tpc42grid
    item.v1190_channel_calibgrid[6] = 110;//tpc31grid //to be checked maybe 111

}


void EXT_FRS::FRS_Calib(frs_item &item, int procid, int type, int subtype)
{
    
    if (procid == 30 && type == 12)
    {   

        if (item.trigger == 13 || item.trigger == 12 || item.trigger == 10 || item.trigger == 11) return; // skip spill trigger
        
        if (item.scaler_check_first_event == 1)
        {
            for (int ii = 0; ii < 64; ii++)
            {
                item.scaler_initial[ii] = item.sc_long[ii];
                item.scaler_previous[ii] = item.sc_long[ii];

            }
            item.scaler_check_first_event = 0;
        }

        item.time_in_ms = item.sc_long[item.scaler_ch_1kHz] - item.scaler_initial[item.scaler_ch_spillstart];

        item.ibin_for_s = ((item.time_in_ms / 1000) % 1000) + 1;
        item.ibin_for_100ms = ((item.time_in_ms / 100) % 4000) + 1;
        item.ibin_for_spill = (item.spill_count % 1000) + 1;

        for (int kk = 0; kk < 64; kk++)
        {
            item.increase_scaler_temp[kk] = item.sc_long[kk] - item.scaler_previous[kk];
        }

        item.extraction_time_ms += item.sc_long[item.scaler_ch_1kHz] - item.scaler_previous[item.scaler_ch_1kHz];
        if ((item.sc_long[item.scaler_ch_spillstart] - item.scaler_previous[item.scaler_ch_spillstart]) != 0)
        {
            item.extraction_time_ms = 0;
        }

        item.ibin_clean_for_s = (((item.time_in_ms / 1000) + 20) % 1000) + 1;
        item.ibin_clean_for_100ms = (((item.time_in_ms / 100) + 200) % 4000) + 1;
        item.ibin_clean_for_spill = ((item.spill_count + 990) % 20) + 1;

        // put current data into previous for the next event
        for (int ii = 0; ii < 64; ii++)
        {
            item.scaler_previous[ii] = item.sc_long[ii]; 
        }
    }

    int max_index = 13;

    for (int i = 0; i < max_index; i++)
    {
        // calculate the sum spectra and conditions
        // better test first existence of xl, xr, an before filling of xsum

        if (item.mw_an[i] && item.mw_xl[i] && item.mw_xr[i])
        {
            item.mw_xsum[i] = 1000 + (item.mw_xl[i] - item.mw_an[i]) + (item.mw_xr[i] - item.mw_an[i]);
        }

        item.b_mw_xsum[i] = Check_WinCond(item.mw_xsum[i], lim_xsum[i]); // was multi

        if (item.mw_an[i] && item.mw_yu[i] && item.mw_yd[i])
        {
            item.mw_ysum[i] = 1000 + (item.mw_yu[i] - item.mw_an[i]) + (item.mw_yd[i] - item.mw_an[i]);
        }

        item.b_mw_ysum[i] = Check_WinCond(item.mw_ysum[i], lim_ysum[i]); // was multi


        if (item.b_mw_xsum[i])
        {
            float r_x = item.mw_xl[i] * mw.gain_tdc[1][i] - item.mw_xr[i] * mw.gain_tdc[2][i];
            item.mw_x[i] = mw.x_factor[i] * r_x + mw.x_offset[i];
        }

        if (item.b_mw_ysum[i])
        {
            float r_y = item.mw_yd[i] * mw.gain_tdc[4][i] - item.mw_yu[i] * mw.gain_tdc[3][i];
            item.mw_y[i] = mw.y_factor[i] * r_y + mw.y_offset[i];
        }

        if (item.b_mw_xsum[i] && item.b_mw_ysum[i])
        {
            // do nothing apparently
        }

    }

    // S2 angle and transformed position spectra

    float dist_MW21_MW22 = frs.dist_MW22 - frs.dist_MW21;
    float dist_MW22_focS2 = frs.dist_focS2 - frs.dist_MW22;
    float dist_MW22_SC21 = frs.dist_SC21 - frs.dist_MW22;
    float dist_MW22_SC22 = frs.dist_SC22 - frs.dist_MW22;

    if (item.b_mw_xsum[1] && item.b_mw_xsum[2])
    {
        // MW21 and MW22 X okay

        // X angle at S2 [mrad]
        item.angle_x_s2 = (item.mw_x[2] - item.mw_x[1]) / dist_MW21_MW22 * 1000.;

        // X at nominal S2 focus
        item.focx_s2 = item.mw_x[2] + dist_MW22_focS2 * item.angle_x_s2 / 1000.;

        // X at SC21 position
        item.mw_sc21_x = item.mw_x[2] + dist_MW22_SC21 * item.angle_x_s2 / 1000.;

        // X at SC22 position
        item.mw_sc22_x = item.mw_x[2] + dist_MW22_SC22 * item.angle_x_s2 / 1000.;

        // real z-position of S2 X focus (cm)
        float rh = (item.angle_x_s2 - item.angle_x_s2m);
        if (fabs(rh) > 1e-4)
        {
            item.z_x_s2 = ((item.focx_s2m - item.focx_s2) / rh) * 100. + frs.dist_focS2 / 10.;
        }

        // keep values for next event
        item.focx_s2m = item.focx_s2;
        item.angle_x_s2m = item.angle_x_s2;

    }

    if (item.b_mw_ysum[1] && item.b_mw_ysum[2])
    {
        // MW21 and MW22 Y okay
        // Y angle at S2 [mrad]
        item.angle_y_s2 = (item.mw_y[2] - item.mw_y[1]) / dist_MW21_MW22 * 1000.;

        // Y at nominal S2 focus:
        item.focy_s2 = item.mw_y[2] + dist_MW22_focS2 * item.angle_y_s2 / 1000.;

        // real z-position of S2 Y focus (cm)
        float rh = (item.angle_y_s2 - item.angle_y_s2m);
        if (fabs(rh) > 1.e-4)
        {
            item.z_y_s2 = ((item.focy_s2m - item.focy_s2) / rh) * 100. + frs.dist_focS2 / 10.;
        }

        // keep values for next event
        item.focy_s2m = item.focy_s2;
        item.angle_y_s2m = item.angle_y_s2;

    }
    
    // TPC Analysis

    for (int u = 0; u < 8; u++)
    {
        item.b_tpc_timeref[u] = false;
        item.tpc_timeref_s[u] = 0;
    }

    for (int k = 0; k < 7; k++)
    {
        item.tpc_dx12[k] = 0;
        item.tpc_x[k] = 0;
        item.tpc_y[k] = 0;
        item.b_tpc_xy[k] = false;
        item.tpc_de[k] = 0;
        item.b_tpc_de[k] = false;

        for (int g = 0; g < 4; g++)
        {
            item.b_tpc_csum[k][g] = false;
            item.tpc_csum[k][g] = 0;
        }

        for (int l = 0; l < 2; l++)
        {
            item.tpc_lt_s[k][l] = 0;
            item.tpc_rt_s[k][l] = 0;
            item.tpc_xraw[k][l] = 0;
        }

        for (int l = 0; l < 4; l++)
        {
            item.tpc_dt_s[k][l] = 0;
            item.tpc_yraw[k][l] = 0;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        for (int ihit = 0; ihit < (item.tpc_nhit_timeref[i]) && ihit < 64; ihit++)
        {
            if (item.tpc_timeref[i][ihit] > tpc.lim_timeref[i][0] && item.tpc_timeref[i][ihit] < tpc.lim_timeref[i][1])
            {
                item.b_tpc_timeref[i] = true;
            }

            if (item.b_tpc_timeref[i])
            {
                if (item.tpc_timeref_s[i] <= 0 || (item.tpc_timeref_s[i] > 0 && item.tpc_timeref[i][ihit] < item.tpc_timeref_s[i]))
                {
                    item.tpc_timeref_s[i] = item.tpc_timeref[i][ihit];
                }
            }
        }
    }

    bool checkrange1 = 0;
    bool checkrange2 = 0;
    bool checkrange3 = 0;
    bool checkrange4 = 0;
    bool checkrange5 = 0;

    for (int i = 0; i < 7; i++)
    {   

        for (int ihit = 0; ihit < (item.tpc_nhit_lt[i][0] && ihit < 64); ihit++)
        {
            int thisdata = item.tpc_lt[i][0][ihit];
            int currently_selected = item.tpc_lt_s[i][0];

            if (thisdata > tpc.lim_lt[i][0][0] && thisdata < tpc.lim_lt[i][0][1]) checkrange1 = true;

            if (checkrange1 && (currently_selected <= 0 || (currently_selected > 0 && thisdata < currently_selected)))
            {
                item.tpc_lt_s[i][0] = thisdata;
            }
        }

        for (int ihit = 0; ihit < (item.tpc_nhit_rt[i][0] && ihit < 64); ihit++)
        {
            int thisdata = item.tpc_rt[i][0][ihit];
            int currently_selected = item.tpc_rt_s[i][0];

            if (thisdata > tpc.lim_rt[i][0][0] && thisdata < tpc.lim_rt[i][0][1]) checkrange2 = true;

            if (checkrange2 && (currently_selected <= 0 || (currently_selected > 0 && thisdata < currently_selected)))
            {
                item.tpc_rt_s[i][0] = thisdata;
            }
        }

        for (int ihit = 0; ihit < (item.tpc_nhit_lt[i][1] && ihit < 64); ihit++)
        {
            int thisdata = item.tpc_lt[i][1][ihit];
            int currently_selected = item.tpc_lt_s[i][1];

            if(thisdata > tpc.lim_lt[i][1][0] && thisdata < tpc.lim_lt[i][1][1]) checkrange3 = true;
            
            if(checkrange3 && (currently_selected <= 0 || (currently_selected > 0 && thisdata < currently_selected)))
            {
                item.tpc_lt_s[i][1] = thisdata;
            }
        }

        for (int ihit = 0; ihit < (item.tpc_nhit_rt[i][1] && ihit < 64); ihit++)
        {
            int thisdata = item.tpc_rt[i][1][ihit];
            int currently_selected = item.tpc_rt_s[i][1];
        
            if (thisdata > tpc.lim_rt[i][1][0] && thisdata < tpc.lim_rt[i][1][1]) checkrange4 = true;
         
            if (checkrange4 && (currently_selected <= 0 || (currently_selected > 0 && thisdata < currently_selected)))
            {
                item.tpc_rt_s[i][1] = thisdata;
            }
        }

        for (int j = 0; j < 4; j++)
        {
            for (int ihit = 0; ihit < (item.tpc_nhit_dt[i][j] && ihit < 64); ihit++)
            {
                int thisdata = item.tpc_dt[i][j][ihit];
                int currently_selected = item.tpc_dt_s[i][j];

                if (thisdata > tpc.lim_dt[i][j][0] && thisdata < tpc.lim_dt[i][j][1]) checkrange5 = true;
                
                if (checkrange5 && (currently_selected <= 0 || (currently_selected > 0 && thisdata < currently_selected)))
                {
                    item.tpc_dt_s[i][j] = thisdata;
                }
            }
        }

        for (int j = 0; j < 4; j++)
        {

            /// calculate control sums
            if (j < 2 && item.tpc_lt_s[i][0] > 0 && item.tpc_rt_s[i][0] > 0 && item.tpc_dt_s[i][j] > 0)
            {
                item.tpc_csum[i][j] = (item.tpc_lt_s[i][0] + item.tpc_rt_s[i][0] - 2 * item.tpc_dt_s[i][j]);
       
            }
            else if (item.tpc_lt_s[i][1] > 0 && item.tpc_rt_s[i][1] > 0 &&  item.tpc_dt_s[i][j] > 0)
            {
                item.tpc_csum[i][j] = (item.tpc_lt_s[i][1] +item. tpc_rt_s[i][1]- 2 * item.tpc_dt_s[i][j]);
    
            }
            else
            {
                item.tpc_csum[i][j] = -9999999;
            }


            // if (item.tpc_csum[i][0] > lim_csum[0][i][0] && item.tpc_csum[i][0] < lim_csum[0][i][1]) 
            if (item.tpc_csum[i][0] > tpc.lim_csum1[i][0] && item.tpc_csum[i][0] < tpc.lim_csum1[i][1]) 
            {   
                
                item.b_tpc_csum[i][0] = true;
            }
            if (item.tpc_csum[i][1] > tpc.lim_csum2[i][0] && item.tpc_csum[i][1] < tpc.lim_csum2[i][1])
            {
                
                item.b_tpc_csum[i][1] = true;
            }
            if (item.tpc_csum[i][2] > tpc.lim_csum3[i][0] && item.tpc_csum[i][2] < tpc.lim_csum3[i][1])
            {
                
                item.b_tpc_csum[i][2] = true;
            }
            if (item.tpc_csum[i][3] > tpc.lim_csum4[i][0] && item.tpc_csum[i][3] < tpc.lim_csum4[i][1])
            {
                
                item.b_tpc_csum[i][3] = true;
            }
        }

        // xraw
        int countx = 0;
        float sumx = 0.0;
        float tmp_tpc_x0 = -99999.;
        float tmp_tpc_x1 = -99999.;

        if ((item.b_tpc_csum[i][0] || item.b_tpc_csum[i][1]))
        {
            item.tpc_xraw[i][0] = item.tpc_lt_s[i][0] - item.tpc_rt_s[i][0];
            tmp_tpc_x0 =  (item.tpc_xraw[i][0]) * (tpc.x_factor[i][0]) + (tpc.x_offset[i][0]);
            sumx += tmp_tpc_x0;
            countx++; 
        }
        if ((item.b_tpc_csum[i][2] || item.b_tpc_csum[i][3]))
        {
            item.tpc_xraw[i][1] = item.tpc_lt_s[i][1] - item.tpc_rt_s[i][1];
            tmp_tpc_x1 = (item.tpc_xraw[i][1]) * (tpc.x_factor[i][1]) + (tpc.x_offset[i][1]);
            sumx += tmp_tpc_x1;
            countx++;
        }
        if (countx > 0)
        {
            item.tpc_x[i] = sumx / ((float) countx);
        }
        if (countx == 2)
        {
            item.tpc_dx12[i] = tmp_tpc_x1 - tmp_tpc_x0;
        }


        // yraw
        int county = 0;
        float sumy = 0.0;
        float tmp_tpc_y[4] = {-99999., -99999., -99999., -99999.};
        int index_timeref = tpc.id_tpc_timeref[i];
       
        for (int j = 0; j < 4; j++)
        {
            if (item.b_tpc_csum[i][j] && item.b_tpc_timeref[index_timeref])
            {
                item.tpc_yraw[i][j] = item.tpc_dt_s[i][j] - item.tpc_timeref_s[index_timeref];
                tmp_tpc_y[j] = (item.tpc_yraw[i][j]) * (tpc.y_factor[i][j]) + (tpc.y_offset[i][j]);
                sumy += tmp_tpc_y[j];
                county++;
            }
        }
        if (county > 0)
        {
            item.tpc_y[i] = sumy / ((double) county);
        }
        
        if (countx > 0 && county > 0)
        {
            item.b_tpc_xy[i] = true; // kTRUE;
        }
        else 
        {
            item.b_tpc_xy[i] = false; // kFALSE;
        }
        
         //TPC anode amplitude quick analysis
        double temp_de = 1.0;
        int temp_count = 0;

        for (int j = 0; j < 4; j++)
        {
            if (item.tpc_a[i][j] - tpc.a_offset[i][j] > 5.0)
            {
                temp_de *= (item.tpc_a[i][j] - tpc.a_offset[i][j]);  
                temp_count++;
            }
        }

        //ADC sqrt-mean is calculated only for 4hit events
        if (temp_count == 4)
        {
            item.tpc_de[i] = sqrt(sqrt(temp_de));
            item.b_tpc_de[i] = true; // kTRUE
        }
    }


    // Distances of TPCs at S2 and S4

    float dist_TPC21_TPC22 = frs.dist_TPC22 - frs.dist_TPC21; 
    float dist_TPC23_TPC24 = frs.dist_TPC24 - frs.dist_TPC23; 
    float dist_TPC22_TPC24 = frs.dist_TPC24 - frs.dist_TPC22; 
    float dist_TPC21_focS2 = frs.dist_TPC21 - frs.dist_focS2; 
    float dist_TPC22_focS2 = frs.dist_TPC22 - frs.dist_focS2; 
    float dist_TPC23_focS2 = frs.dist_TPC23 - frs.dist_focS2; 
    float dist_TPC41_TPC42 = frs.dist_TPC42 - frs.dist_TPC41; 
    float dist_TPC42_focS4 = frs.dist_focS4 - frs.dist_TPC42; 
  
    // Tracking with TPC 21 and TPC 22 
  
    if (item.b_tpc_xy[0] && item.b_tpc_xy[1])
    {
        item.tpc_angle_x_s2_foc_21_22 = (item.tpc_x[1] - item.tpc_x[0]) / dist_TPC21_TPC22 * 1000.;
        item.tpc_angle_y_s2_foc_21_22 = (item.tpc_y[1] - item.tpc_y[0]) / dist_TPC21_TPC22 * 1000.;
        item.tpc_x_s2_foc_21_22 = -item.tpc_angle_x_s2_foc_21_22 * dist_TPC21_focS2 / 1000. + item.tpc_x[0]; //check
        item.tpc_y_s2_foc_21_22 = -item.tpc_angle_y_s2_foc_21_22 * dist_TPC21_focS2 / 1000. + item.tpc_y[0]; //check
        
        float dist_SC21_focS2 = frs.dist_SC21 - frs.dist_focS2;
        item.tpc21_22_sc21_x = (item.tpc_angle_x_s2_foc_21_22 / 1000. * dist_SC21_focS2) + item.tpc_x_s2_foc_21_22;
        item.tpc21_22_sc21_y = (item.tpc_angle_y_s2_foc_21_22 / 1000. * dist_SC21_focS2) + item.tpc_y_s2_foc_21_22;
        
        float dist_SC22_focS2 = frs.dist_SC22 - frs.dist_focS2;
        item.tpc21_22_sc22_x = (item.tpc_angle_x_s2_foc_21_22 / 1000. * dist_SC22_focS2) + item.tpc_x_s2_foc_21_22;
        item.tpc21_22_sc22_y = (item.tpc_angle_y_s2_foc_21_22 / 1000. * dist_SC22_focS2) + item.tpc_y_s2_foc_21_22;
        
        float dist_S2target_focS2 = frs.dist_S2target - frs.dist_focS2;
        item.tpc21_22_s2target_x = (item.tpc_angle_x_s2_foc_21_22 / 1000. * dist_S2target_focS2) + item.tpc_x_s2_foc_21_22;
        item.tpc21_22_s2target_y = (item.tpc_angle_y_s2_foc_21_22 / 1000. * dist_S2target_focS2) + item.tpc_y_s2_foc_21_22;
    }

    // Tracking with TPC 23 and TPC 24 
  
    if (item.b_tpc_xy[2] && item.b_tpc_xy[3])
    {
        item.tpc_angle_x_s2_foc_23_24 = (item.tpc_x[3] - item.tpc_x[2]) / dist_TPC23_TPC24 * 1000.;
      
        item.tpc_angle_y_s2_foc_23_24 = (item.tpc_y[3] - item.tpc_y[2]) / dist_TPC23_TPC24 * 1000.;
        item.tpc_x_s2_foc_23_24 = -item.tpc_angle_x_s2_foc_23_24 * dist_TPC23_focS2 / 1000. + item.tpc_x[2]; //check
       
        item.tpc_y_s2_foc_23_24 = -item.tpc_angle_y_s2_foc_23_24 * dist_TPC23_focS2 / 1000. + item.tpc_y[2]; //check
        
        float dist_SC21_focS2 = frs.dist_SC21 - frs.dist_focS2;
        item.tpc23_24_sc21_x = (item.tpc_angle_x_s2_foc_23_24 / 1000. * dist_SC21_focS2) + item.tpc_x_s2_foc_23_24;
        item.tpc23_24_sc21_y = (item.tpc_angle_y_s2_foc_23_24 / 1000. * dist_SC21_focS2) + item.tpc_y_s2_foc_23_24;
        
        float dist_SC22_focS2 = frs.dist_SC22 - frs.dist_focS2;
        item.tpc23_24_sc22_x = (item.tpc_angle_x_s2_foc_23_24 / 1000. * dist_SC22_focS2) + item.tpc_x_s2_foc_23_24;
        item.tpc23_24_sc22_y = (item.tpc_angle_y_s2_foc_23_24 / 1000. * dist_SC22_focS2) + item.tpc_y_s2_foc_23_24;
        
        float dist_S2target_focS2 = frs.dist_S2target - frs.dist_focS2;
        item.tpc23_24_s2target_x = (item.tpc_angle_x_s2_foc_23_24 / 1000. * dist_S2target_focS2) + item.tpc_x_s2_foc_23_24;
        item.tpc23_24_s2target_y = (item.tpc_angle_y_s2_foc_23_24 / 1000. * dist_S2target_focS2) + item.tpc_y_s2_foc_23_24;
    }
    else
    {
        item.tpc_x_s2_foc_23_24 = -999;
    }

    // Tracking with TPC 22 and TPC 24 
  
    if (item.b_tpc_xy[1] && item.b_tpc_xy[3])
    {
        item.tpc_angle_x_s2_foc_22_24 = (item.tpc_x[3] - item.tpc_x[1]) / dist_TPC22_TPC24 * 1000.;
        item.tpc_angle_y_s2_foc_22_24 = (item.tpc_y[3] - item.tpc_y[1]) / dist_TPC22_TPC24 * 1000.;
        item.tpc_x_s2_foc_22_24 = -item.tpc_angle_x_s2_foc_22_24 * dist_TPC22_focS2 / 1000. + item.tpc_x[1]; //check
        item.tpc_y_s2_foc_22_24 = -item.tpc_angle_y_s2_foc_22_24 * dist_TPC22_focS2 / 1000. + item.tpc_y[1]; //check

        float dist_SC21_focS2 = frs.dist_SC21 - frs.dist_focS2;
        item.tpc22_24_sc21_x = (item.tpc_angle_x_s2_foc_22_24 / 1000. * dist_SC21_focS2) + item.tpc_x_s2_foc_22_24;
        item.tpc22_24_sc21_y = (item.tpc_angle_y_s2_foc_22_24 / 1000. * dist_SC21_focS2) + item.tpc_y_s2_foc_22_24;
        
        float dist_SC22_focS2 = frs.dist_SC22 - frs.dist_focS2;
        item.tpc22_24_sc22_x = (item.tpc_angle_x_s2_foc_22_24 / 1000. * dist_SC22_focS2) + item.tpc_x_s2_foc_22_24;
        item.tpc22_24_sc22_y = (item.tpc_angle_y_s2_foc_22_24 / 1000. * dist_SC22_focS2) + item.tpc_y_s2_foc_22_24;
        
        float dist_S2target_focS2 = frs.dist_S2target - frs.dist_focS2;
        item.tpc22_24_s2target_x = (item.tpc_angle_x_s2_foc_22_24 / 1000. * dist_S2target_focS2) + item.tpc_x_s2_foc_22_24;
        item.tpc22_24_s2target_y = (item.tpc_angle_y_s2_foc_22_24 / 1000. * dist_S2target_focS2) + item.tpc_y_s2_foc_22_24;
    }
    else 
    {
        item.tpc_x_s2_foc_22_24 = -999;
    }
  

    // Tracking with TPC 41 and TPC 42 (TPC 5 and 6) at S4  

    if (item.b_tpc_xy[4] && item.b_tpc_xy[5])
    {
        item.tpc_angle_x_s4 = (item.tpc_x[5] - item.tpc_x[4]) / dist_TPC41_TPC42 * 1000.;
        item.tpc_angle_y_s4 = (item.tpc_y[5] - item.tpc_y[4]) / dist_TPC41_TPC42 * 1000.;
        item.tpc_x_s4 = item.tpc_angle_x_s4 * dist_TPC42_focS4 / 1000. + item.tpc_x[5];
        item.tpc_y_s4 = item.tpc_angle_y_s4 * dist_TPC42_focS4 / 1000. + item.tpc_y[5];
    
        float dist_SC41_focS4 = frs.dist_SC41 - frs.dist_focS4;
        item.tpc_sc41_x = (item.tpc_angle_x_s4 / 1000. * dist_SC41_focS4) + item.tpc_x_s4;
        item.tpc_sc41_y = (item.tpc_angle_y_s4 / 1000. * dist_SC41_focS4) + item.tpc_y_s4;
       
        float dist_SC42_focS4 = frs.dist_SC42 - frs.dist_focS4;
        item.tpc_sc42_x = (item.tpc_angle_x_s4 / 1000. * dist_SC42_focS4) + item.tpc_x_s4;
        item.tpc_sc42_y = (item.tpc_angle_y_s4 / 1000. * dist_SC42_focS4) + item.tpc_y_s4;
       
        float dist_SC43_focS4 = frs.dist_SC43 - frs.dist_focS4;
        item.tpc_sc43_x = (item.tpc_angle_x_s4 / 1000. * dist_SC43_focS4) + item.tpc_x_s4;
        item.tpc_sc43_y = (item.tpc_angle_y_s4 / 1000. * dist_SC43_focS4) + item.tpc_y_s4;

        float dist_MUSIC41_focS4 = frs.dist_MUSIC41 - frs.dist_focS4;
        item.tpc_music41_x = (item.tpc_angle_x_s4 / 1000. * dist_MUSIC41_focS4) + item.tpc_x_s4;
        item.tpc_music41_y = (item.tpc_angle_y_s4 / 1000. * dist_MUSIC41_focS4) + item.tpc_y_s4;
       
        float dist_MUSIC42_focS4 = frs.dist_MUSIC42 - frs.dist_focS4;
        item.tpc_music42_x = (item.tpc_angle_x_s4 / 1000. * dist_MUSIC42_focS4) + item.tpc_x_s4;
        item.tpc_music42_y = (item.tpc_angle_y_s4 / 1000. * dist_MUSIC42_focS4) + item.tpc_y_s4;
       
        float dist_MUSIC43_focS4 = frs.dist_MUSIC43 - frs.dist_focS4;
        item.tpc_music43_x = (item.tpc_angle_x_s4 / 1000. * dist_MUSIC43_focS4) + item.tpc_x_s4;
        item.tpc_music43_y = (item.tpc_angle_y_s4 / 1000. * dist_MUSIC43_focS4) + item.tpc_y_s4;
       
        float dist_S4target_focS4 = frs.dist_S4target - frs.dist_focS4;
        item.tpc_s4target_x = (item.tpc_angle_x_s4 / 1000. * dist_S4target_focS4) + item.tpc_x_s4;
        item.tpc_s4target_y = (item.tpc_angle_y_s4 / 1000. * dist_S4target_focS4) + item.tpc_y_s4;      
    }
  
    // other stuff can be found commented out in S452 Go4 code.

}


void EXT_FRS::FRS_Anal(frs_item &item, int procid, int type, int subtype)
{   

    // Start of MUSIC  analysis
    item.music1_anodes_cnt = 0;  
    item.music2_anodes_cnt = 0;  
    item.music3_anodes_cnt = 0;

   // Munich MUSIC 
    for (int i = 0; i < 8; i++)
    {   
        /* 8 anodes of TUM MUSIC */       
        if (item.music_e1[i] > 5)
        {   
            item.music_b_e1[i] = Check_WinCond(item.music_e1[i], cMusic1_E[i]); // was Multi //cMusic1_E[i]->Test(music_e1[i]);
      
            if (item.music_b_e1[i])
            {
                item.music1_anodes_cnt++;
            }
        }

        if (item.music_t1[i] > 0)
        { 
            item.music_b_t1[i] = Check_WinCond(item.music_t1[i], cMusic1_T[i]); // was Multi // cMusic1_T[i]->Test(music_t1[i]);
        }

        /****** second MUSIC *****/
     
        if (item.music_e2[i] > 5)
        { 
            item.music_b_e2[i] = Check_WinCond(item.music_e2[i], cMusic2_E[i]); // was Multi // cMusic2_E[i]->Test(music_e2[i]);
            if (item.music_b_e2[i])
            {
                item.music2_anodes_cnt++;
            }
        }

        if (item.music_t2[i] > 0)
        { 
            item.music_b_t2[i] = Check_WinCond(item.music_t2[i], cMusic2_T[i]); // was Multi // cMusic2_T[i]->Test(music_t2[i]);
        }
    }

    for (int i = 0; i < 4; i++)
    {
      /* 4 anodes of MUSIC OLD */       
      /****** third MUSIC Travelling*****/
        if (item.music_e3[i] > 0)
        { 

            item.music_b_e3[i] = Check_WinCond(item.music_e3[i], cMusic3_E[i]); // was Multi // cMusic3_E[i]->Test(music_e3[i]);
            if (item.music_b_e3[i])
            {
                item.music3_anodes_cnt++;
            }

        }
        if (item.music_t3[i] > 0)
        { 
            item.music_b_t3[i] = Check_WinCond(item.music_t3[i], cMusic3_T[i]); // was Multi // cMusic3_T[i]->Test(music_t3[i]);
        }
    }
  
    // calculate truncated dE from 8 anodes, Munich MUSIC 

    if (item.music1_anodes_cnt == 8)
    {
        float r1 = ((item.music_e1[0]) * music.e1_gain[0] + music.e1_off[0]) * ((item.music_e1[1]) * music.e1_gain[1] + music.e1_off[1]);
        float r2 = ((item.music_e1[2]) * music.e1_gain[2] + music.e1_off[2]) * ((item.music_e1[3]) * music.e1_gain[3] + music.e1_off[3]);
        float r3 = ((item.music_e1[4]) * music.e1_gain[4] + music.e1_off[4]) * ((item.music_e1[5]) * music.e1_gain[5] + music.e1_off[5]);
        float r4 = ((item.music_e1[6]) * music.e1_gain[6] + music.e1_off[6]) * ((item.music_e1[7]) * music.e1_gain[7] + music.e1_off[7]);

        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {   

            item.b_de1 = true; // kTRUE
            item.de[0] = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            item.de_cor[0] = item.de[0];
        }  
    }

    if (item.music2_anodes_cnt == 8)
    {
      
        float r1 = ((item.music_e2[0]) * music.e2_gain[0] + music.e2_off[0]) * ((item.music_e2[1]) * music.e2_gain[1] + music.e2_off[1]);
        float r2 = ((item.music_e2[2]) * music.e2_gain[2] + music.e2_off[2]) * ((item.music_e2[3]) * music.e2_gain[3] + music.e2_off[3]);
        float r3 = ((item.music_e2[4]) * music.e2_gain[4] + music.e2_off[4]) * ((item.music_e2[5]) * music.e2_gain[5] + music.e2_off[5]);
        float r4 = ((item.music_e2[6]) * music.e2_gain[6] + music.e2_off[6]) * ((item.music_e2[7]) * music.e2_gain[7] + music.e2_off[7]);

      
        if ((r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0))
        {
            item.b_de2 = true; // kTRUE;
            item.de[1] = sqrt(sqrt(sqrt(r1) * sqrt(r2)) * sqrt(sqrt(r3) * sqrt(r4)));
            item.de_cor[1] = item.de[1];
        }  
    }

    if (item.music3_anodes_cnt == 8)
    {         
        // OLD MUSIC
        float r1 = ((item.music_e3[0]) * music.e3_gain[0] + music.e3_off[0]) * ((item.music_e3[1]) * music.e3_gain[1] + music.e3_off[1]);
        float r2 = ((item.music_e3[2]) * music.e3_gain[2] + music.e3_off[2]) * ((item.music_e3[3]) * music.e3_gain[3] + music.e3_off[3]);
      
        if ((r1 > 0) && (r2 > 0))
        {
            item.de[2] = sqrt(sqrt(r1) * sqrt(r2)) ;  // corrrected JSW 19.03.2010
            item.de_cor[2] = item.de[2];
        } 


        /* Position (X) correction by TPC */      
      
        if(item.b_tpc_xy[4] && item.b_tpc_xy[5])
        {

            item.music1_x_mean = item.tpc_music41_x;
            item.music2_x_mean = item.tpc_music42_x;
            item.music3_x_mean = item.tpc_music43_x;

            float power, Corr;
            // correction for MUSIC41
            if(item.b_de1)
            {
                power = 1., Corr = 0.;
                for(int i = 0; i < 4; i++) 
                {
                    Corr += music.pos_a1[i] * power;
                    power *= item.music1_x_mean;
                }
                if (Corr != 0) 
                {
                    Corr = music.pos_a1[0] / Corr;
                    item.de_cor[0] = item.de[0] * Corr;
                } 
            }

            // correction for MUSIC42
            if(item.b_de2)
            {
                power = 1., Corr = 0.;
                for(int i = 0; i < 4; i++) 
                {
                    Corr += music.pos_a2[i] * power;
                    power *= item.music2_x_mean;
                }
                if (Corr != 0) 
                {
                    Corr = music.pos_a2[0] / Corr;
                    item.de_cor[1] = item.de[1] * Corr;
                }
            }

            // correction for MUSIC43
            if(item.b_de3)
            {
                power = 1., Corr = 0.;
                for(int i = 0; i < 4; i++) 
                {
                    Corr += music.pos_a3[i] * power;
                    power *= item.music3_x_mean;
                }
                if (Corr != 0) 
                {
                    Corr = music.pos_a3[0] / Corr;
                    item.de_cor[2] = item.de[2] * Corr;
                }
            }
        }    
    }

    // Start of Scintillator  analysis


    item.mhtdc_sc21lr_dt = 0;
    item.mhtdc_sc31lr_dt = 0;
    item.mhtdc_sc41lr_dt = 0;
    item.mhtdc_sc42lr_dt = 0;

    //SCI 21
    if (item.tdc_sc21l[0] != 0 && item.tdc_sc21r[0] != 0)
    {
        item.mhtdc_sc21lr_dt = sci.mhtdc_factor_ch_to_ns * (rand3() + item.tdc_sc21l[0] - item.tdc_sc21r[0]);
        item.mhtdc_sc21lr_x = item.mhtdc_sc21lr_dt * sci.mhtdc_factor_21l_21r + sci.mhtdc_offset_21l_21r;
   
        float sc21pos_from_tpc = -999.9;
        if(item.b_tpc_xy[0] && item.b_tpc_xy[1])
        {
            sc21pos_from_tpc = item.tpc21_22_sc21_x;
        }
        else if(item.b_tpc_xy[2] && item.b_tpc_xy[3])
        {
            sc21pos_from_tpc = item.tpc23_24_sc21_x;
        }
    }
    
    //SCI22
    if (item.tdc_sc22l[0] != 0 && item.tdc_sc22r[0] != 0)
    {
        item.mhtdc_sc22lr_dt = sci.mhtdc_factor_ch_to_ns * (rand3() + item.tdc_sc22l[0] - item.tdc_sc22r[0]);
        item.mhtdc_sc22lr_x = item.mhtdc_sc22lr_dt * sci.mhtdc_factor_22l_22r + sci.mhtdc_offset_22l_22r;
        float sc22pos_from_tpc = -999.9;
        if (item.b_tpc_xy[0] && item.b_tpc_xy[1])
        {
            sc22pos_from_tpc = item.tpc21_22_sc22_x;
        }
        else if (item.b_tpc_xy[2] && item.b_tpc_xy[3])
        {
            sc22pos_from_tpc =  item.tpc23_24_sc22_x;
        }
    }

    if(item.tdc_sc41l[0] != 0 && item.tdc_sc41r[0] != 0)
    {
        item.mhtdc_sc41lr_dt = sci.mhtdc_factor_ch_to_ns * (rand3() + item.tdc_sc41l[0] - item.tdc_sc41r[0]);
        item.mhtdc_sc41lr_x = item.mhtdc_sc41lr_dt * sci.mhtdc_factor_41l_41r + sci.mhtdc_offset_41l_41r;
    }

    if(item.tdc_sc42l[0] != 0 && item.tdc_sc42r[0] != 0)
    {
        item.mhtdc_sc42lr_dt = sci.mhtdc_factor_ch_to_ns * (rand3() + item.tdc_sc42l[0] - item.tdc_sc42r[0]);
        item.mhtdc_sc42lr_x = item.mhtdc_sc42lr_dt * sci.mhtdc_factor_42l_42r + sci.mhtdc_offset_42l_42r;
    }

    if(item.tdc_sc43l[0] != 0 && item.tdc_sc43r[0] != 0)
    {
        item.mhtdc_sc43lr_dt = sci.mhtdc_factor_ch_to_ns * (rand3() + item.tdc_sc43l[0] - item.tdc_sc43r[0]);
        item.mhtdc_sc43lr_x = item.mhtdc_sc43lr_dt * sci.mhtdc_factor_43l_43r + sci.mhtdc_offset_43l_43r;
    }

    if(item.tdc_sc31l[0] != 0 && item.tdc_sc31r[0] != 0)
    {
        item.mhtdc_sc31lr_dt = sci.mhtdc_factor_ch_to_ns * (rand3() + item.tdc_sc31l[0] - item.tdc_sc31r[0]);
        item.mhtdc_sc31lr_x  = item.mhtdc_sc31lr_dt * sci.mhtdc_factor_31l_31r + sci.mhtdc_offset_31l_31r; 
    }

    if(item.tdc_sc81l[0] != 0 && item.tdc_sc81r[0] != 0)
    {
        item.mhtdc_sc81lr_dt = sci.mhtdc_factor_ch_to_ns * (rand3() + item.tdc_sc81l[0] - item.tdc_sc81r[0]);
        item.mhtdc_sc81lr_x = item.mhtdc_sc81lr_dt * sci.mhtdc_factor_81l_81r + sci.mhtdc_offset_81l_81r;
    }
  
    //21 -> 41
    if(item.tdc_sc21l[0] != 0 && item.tdc_sc21r[0] != 0 && item.tdc_sc41l[0] != 0 && item.tdc_sc41r[0] != 0)
    {
        item.mhtdc_tof4121 = sci.mhtdc_factor_ch_to_ns * (0.5 * (item.tdc_sc41l[0] + item.tdc_sc41r[0]) - 0.5 * (item.tdc_sc21l[0] + item.tdc_sc21r[0])) + sci.mhtdc_offset_41_21;   
    }
  
    //21 -> 42
    if(item.tdc_sc21l[0] != 0 && item.tdc_sc21r[0] != 0 && item.tdc_sc42l[0] != 0 && item.tdc_sc42r[0] != 0)
    {
        item.mhtdc_tof4221 = sci.mhtdc_factor_ch_to_ns * (0.5 * (item.tdc_sc42l[0] + item.tdc_sc42r[0]) - 0.5 * (item.tdc_sc21l[0] + item.tdc_sc21r[0])) + sci.mhtdc_offset_42_21;
    }

    //21 -> 43
    if(item.tdc_sc21l[0] != 0 && item.tdc_sc21r[0] != 0 && item.tdc_sc43l[0] != 0 && item.tdc_sc43r[0] != 0)
    {
        item.mhtdc_tof4321 = sci.mhtdc_factor_ch_to_ns * (0.5 * (item.tdc_sc43l[0] + item.tdc_sc43r[0]) - 0.5 * (item.tdc_sc21l[0] + item.tdc_sc21r[0])) + sci.mhtdc_offset_43_21;
    }

    //21 -> 32
    if(item.tdc_sc21l[0] != 0 && item.tdc_sc21r[0] != 0 && item.tdc_sc31l[0] != 0 && item.tdc_sc31r[0] != 0)
    {
        item.mhtdc_tof3121 = sci.mhtdc_factor_ch_to_ns * (0.5 * (item.tdc_sc31l[0] + item.tdc_sc31r[0]) - 0.5 * (item.tdc_sc21l[0] + item.tdc_sc21r[0])) + sci.mhtdc_offset_31_21;
    }

    //21 -> 81
    if(item.tdc_sc21l[0] != 0 && item.tdc_sc21r[0] != 0 && item.tdc_sc81l[0] != 0 && item.tdc_sc81r[0] != 0)
    {
        item.mhtdc_tof8121 = sci.mhtdc_factor_ch_to_ns * (0.5 * (item.tdc_sc81l[0] + item.tdc_sc81r[0]) - 0.5 * (item.tdc_sc21l[0] + item.tdc_sc21r[0])) + sci.mhtdc_offset_81_21;
    }

    //22 -> 41
    if(item.tdc_sc22l[0] != 0 && item.tdc_sc22r[0] != 0 && item.tdc_sc41l[0] != 0 && item.tdc_sc41r[0] != 0)
    {
        item.mhtdc_tof4122 = sci.mhtdc_factor_ch_to_ns * (0.5 * (item.tdc_sc41l[0] + item.tdc_sc41r[0]) - 0.5 * (item.tdc_sc22l[0] + item.tdc_sc22r[0])) + sci.mhtdc_offset_41_22;
    }

    /*-------------------------------------------------------------------------*/
    /* focus index: detector number                  tof index  tof path       */
    /*       0:     Sc01                                0:     TA - S1         */
    /*       1:     Sc11                                1:     S1 - S2         */
    /*       2:     Sc21                                2:     S2 - S41        */
    /*       3:     Sc22                                3:     S2 - S42        */
    /*       4:     Sc31                                4:     S2 - 81         */
    /*       5:     Sc41                                5:     S2 - E1         */
    /*                                                                         */
    /*       6:     Sc42                              tof index not used up to */
    /*       7:     Sc43 (previously Sc51)             now, only separate      */
    /*       8:     Sc61                              variables for S2-S41 and */
    /*       9:     ScE1 (ESR)                                S2-S42           */
    /*      10:     Sc81                                                       */
    /*      11:     Sc82                                                       */
    /*-------------------------------------------------------------------------*/
    
    for(int i = 0; i < 12; i++)
    {
        item.sci_l[i] = 0;
        item.sci_r[i] = 0;
        item.sci_tx[i] = 0;
        item.sci_x[i] = 0;
    }

    /*  Raw data  */
    item.sci_l[2] = item.de_21l;  /* 21L         */
    item.sci_r[2] = item.de_21r;  /* 21R         */
    item.sci_tx[2] = item.dt_21l_21r + rand3();

    item.sci_l[5] = item.de_41l;  /* 41L         */
    item.sci_r[5] = item.de_41r;  /* 41R         */
    item.sci_tx[5] = item.dt_41l_41r + rand3();
  
    item.sci_l[6] = item.de_42l;  /* 42L         */
   
    item.sci_r[6] = item.de_42r;  /* 42R         */
    item.sci_tx[6] = item.dt_42l_42r + rand3();

    item.sci_l[7] = item.de_43l;  /* 43L         */
    item.sci_r[7] = item.de_43r;  /* 43R         */
    item.sci_tx[7] = item.dt_43l_43r + rand3();

    item.sci_l[10] = item.de_81l; /* 81L         */
    item.sci_r[10] = item.de_81r; /* 81R         */
    item.sci_tx[10] = item.dt_81l_81r + rand3();
   
    item.sci_l[3] = item.de_22l;  /* 21L         */
    item.sci_r[3] = item.de_22r;  /* 21R         */
    item.sci_tx[3] = item.dt_22l_22r + rand3();

    for (int cnt = 0; cnt < 6; cnt++)
    {
        int idx = 0 ;
        float posref =-999;

        switch (cnt)
        {
            case 0:        /* SC21 */
                idx = 2; 
                // posref from tpc
                if (item.b_tpc_xy[0] && item.b_tpc_xy[1])
                {
                    posref = item.tpc21_22_sc21_x;
                }
                else if (item.b_tpc_xy[2] && item.b_tpc_xy[3])
                {
                    posref =  item.tpc23_24_sc21_x;
                }
                break;

            case 1:        /* SC21 delayed */
                idx = 3; 
                if(item.b_tpc_xy[6])
                {
                    posref = item.tpc_x[6]; 
                }
                break;    
            
            case 2:        /* SC41 */
                idx = 5; 
                if(item.b_tpc_xy[4] && item.b_tpc_xy[5])
                {
                    posref = item.tpc_sc41_x;
                }
                break;    
            case 3:        /* SC42 */
                idx = 6;
                if(item.b_tpc_xy[4] && item.b_tpc_xy[5])
                {
                    posref = item.tpc_sc42_x;
                }
                break;
            case 4:
                idx = 7;     /* SC43 */
                if(item.b_tpc_xy[4] && item.b_tpc_xy[5])
                {
                    posref = item.tpc_sc43_x;
                }
                break;
            case 5:
                idx = 10;    /* SC81 */
                // no position reference from tpc
                break;
            
            default: idx = 2;
        }   
     
        item.sci_b_l[idx] = Check_WinCond(item.sci_l[idx], cSCI_L);// cSCI_L[idx]->Test(sci_l[idx]);
        item.sci_b_r[idx] = Check_WinCond(item.sci_r[idx], cSCI_R);// cSCI_R[idx]->Test(sci_r[idx]);

        if(item.sci_b_l[idx] && item.sci_b_r[idx])
        {     
            item.sci_e[idx] = (item.sci_r[idx] - sci.re_a[0][idx]);
            item.sci_b_e[idx] = Check_WinCond(item.sci_e[idx], cSCI_E);// cSCI_E[idx]->Test(sci_e[idx]);
        }
   
        /*   Position in X direction:   */
        item.sci_b_tx[idx] = Check_WinCond(item.sci_tx[idx], cSCI_Tx);// cSCI_Tx[idx]->Test(sci_tx[idx]);
        if (item.sci_b_tx[idx])
        {

            /* mm-calibrated     */
            float R = item.sci_tx[idx] ;//+ rand3(); 
       
            float power = 1., sum = 0.;
            for(int i = 0; i < 7; i++)
            {
                sum += sci.x_a[i][idx] * power;
                power *= R;  
            }
       
            item.sci_x[idx] = sum;
   
            item.sci_b_x[idx] = Check_WinCond(item.sci_x[idx], cSCI_X);// cSCI_X[idx]->Test(sci_x[idx]);
        }
     

    } // end of loop for indices 2,3,5,6,7,10   

    /***  Scintillator Tof  spectra ***/

    /* S21 - S41 */ 

    /*  Calibrated tof  */
    item.sci_tofll2 = item.dt_21l_41l * sci.tac_factor[2] - sci.tac_off[2];   /* S41L- S21L */
 
    item.sci_tofrr2 = item.dt_21r_41r * sci.tac_factor[3] - sci.tac_off[3];   /* S41R- S21R */

    item.sci_b_tofll2 = Check_WinCond(item.sci_tofll2, cSCI_LL2);// cSCI_TofLL2->Test(sci_tofll2);
    item.sci_b_tofrr2 = Check_WinCond(item.sci_tofrr2, cSCI_RR2);// cSCI_TofRR2->Test(sci_tofrr2);
    /* sum of Tof_LL and Tof_RR corrects for position in stop/start scint.      */
   
    if (item.sci_b_tofll2 && item.sci_b_tofrr2)
    {
        /* TOF SC41 - SC21 [ps]  */
        item.sci_tof2 = (sci.tof_bll2 * item.sci_tofll2 + sci.tof_a2 + sci.tof_brr2 * item.sci_tofrr2) / 2.0; // tof_a2  is essentially unnecessary (even confusing) = 0
        item.sci_tof2_calib = -1.0 * item.sci_tof2 + id.id_tofoff2;
    }
    else 
    {
        item.sci_tof2 = 0;
        item.sci_tof2_calib = 0;
    }
  
    /*   S21 - S42 Calibrated tof  */
    item.sci_tofll3 = item.dt_42l_21l * sci.tac_factor[5] - sci.tac_off[5];   /* S42L- S21L */  // tac_off is essentially unnecessary (even confusing)
    item.sci_tofrr3 = item.dt_42r_21r * sci.tac_factor[6] - sci.tac_off[6];   /* S42R- S21R */  // tac_off is essentially unnecessary (even confusing)
    item.sci_b_tofll3 = Check_WinCond(item.sci_tofll3, cSCI_LL3);
    item.sci_b_tofrr3 = Check_WinCond(item.sci_tofrr3, cSCI_LL3);
    if (item.sci_b_tofll3 && item.sci_b_tofrr3)
    {
        item.sci_tof3 = (sci.tof_bll3 * item.sci_tofll3 + sci.tof_a3 + sci.tof_brr3 * item.sci_tofrr3)/2.0 ;  // tof_a3  is essentially unnecessary (even confusing) = 0
        item.sci_tof3_calib = -1.0 * item.sci_tof3 + id.id_tofoff3;
    }
    else 
    {
        item.sci_tof3 = 0;
        item.sci_tof3_calib = 0;
    }
    
    /*   S21 - S81 Calibrated tof  */
    item.sci_tofll4 = item.dt_21l_81l * sci.tac_factor[9] - sci.tac_off[9];     /* S81L- S21L */  // tac_off is essentially unnecessary (even confusing)
    item.sci_tofrr4 = item.dt_21r_81r * sci.tac_factor[10] - sci.tac_off[10];   /* S82R- S21R */  // tac_off is essentially unnecessary (even confusing)
 
    item.sci_b_tofll4 = Check_WinCond(item.sci_tofll4, cSCI_LL4);// cSCI_TofLL4->Test(sci_tofll4);
    item.sci_b_tofrr4 = Check_WinCond(item.sci_tofrr4, cSCI_RR4);// cSCI_TofRR4->Test(sci_tofrr4);
   
    /*   S22 - S41 Calibrated tof  */
    item.sci_tofll5 = item.dt_22l_41l * sci.tac_factor[12] - sci.tac_off[12];     /* S41L- S22L */  // tac_off is essentially unnecessary (even confusing)
    item.sci_tofrr5 = item.dt_22r_41r * sci.tac_factor[13] - sci.tac_off[13];     /* S41R- S22R */  // tac_off is essentially unnecessary (even confusing)

    item.sci_b_tofll5 = Check_WinCond(item.sci_tofll5, cSCI_LL5);
    item.sci_b_tofrr5 = Check_WinCond(item.sci_tofrr5, cSCI_RR5);
 
    if(item.sci_b_tofll5 && item.sci_b_tofrr5)
    {
        item.sci_tof5 = (sci.tof_bll5 * item.sci_tofll5 + sci.tof_a5 + sci.tof_brr5 * item.sci_tofrr5) / 2.0;  // tof_a5  is essentially unnecessary (even confusing) = 0
        item.sci_tof5_calib = -1.0 * item.sci_tof5 + id.id_tofoff5;
    }
    else 
    {
        item.sci_tof5 = 0;
        item.sci_tof5_calib = 0;
    }

    // sum of Tof_LL and Tof_RR corrects for position in stop/start scint.      
    if (item.sci_b_tofll4 && item.sci_b_tofrr4)
    {      // TOF SC81 - SC21 [ps]
        item.sci_tof4 = (sci.tof_bll4 * item.sci_tofll4 + sci.tof_a4 + sci.tof_brr4 * item.sci_tofrr4) / 2.0;
    }
   
    /* check for polygon in raw detof spectrum of SC41 */ // CEJ: hmm..
    item.sci_b_detof = Check_PolyCond_X_Y(item.sci_tof2, item.sci_e[5], cSCI_detof, 4); // cSCI_detof->Test(sci_tof2, sci_e[5]);
    
    // Start of MHTDC ID analysis
    float speed_light = 0.299792458; //m/ns
    float temp_tm_to_MeV = 299.792458;
    float temp_mu = 931.4940954; //MeV
  
    // Extraction of position to be used for momentum analysis
    float temp_s8x = item.mhtdc_sc81lr_x;
    float temp_s4x = -999.;
    if (item.b_tpc_xy[4] && item.b_tpc_xy[5])
    {
        temp_s4x = item.tpc_x_s4;
    }
    
    float temp_s2x = -999.; //fill in the next if part
    if (id.mhtdc_s2pos_option == 1)
    {   //SC21X from multihit tdc is used for S2X
        temp_s2x = item.mhtdc_sc21lr_x;
    }
    if (id.mhtdc_s2pos_option == 2)
    {   //TPCX is used
        if (item.b_tpc_xy[2] && item.b_tpc_xy[3])
        {   //tpc2324
            temp_s2x = item.tpc_x_s2_foc_23_24;
        }
        else if (item.b_tpc_xy[1] && item.b_tpc_xy[3])
        {   //tpc2224
            temp_s2x = item.tpc_x_s2_foc_22_24;
        }
        else if (item.b_tpc_xy[0] && item.b_tpc_xy[1])
        {   //tpc2122
            temp_s2x = item.tpc_x_s2_foc_21_22;
        }
    }

    //   S2S4 MultihitTDC ID analysis
    item.id_mhtdc_beta_s2s4 = 0;
    item.id_mhtdc_gamma_s2s4 = 0;
    float mean_brho_s2s4 = 0;
    item.id_mhtdc_delta_s2s4 = 0;
    item.id_mhtdc_aoq_s2s4 = 0;
    item.id_mhtdc_v_cor_music41 = 0;
    item.id_mhtdc_z_music41 = 0;
    item.id_mhtdc_v_cor_music42 = 0;
    item.id_mhtdc_z_music42 = 0;

    // Calculation of velocity beta and gamma
    item.id_mhtdc_beta_s2s4 = (id.mhtdc_length_s2s4 / item.mhtdc_tof4121) / speed_light;
    item.id_mhtdc_gamma_s2s4 = 1. / sqrt(1. - item.id_mhtdc_beta_s2s4 * item.id_mhtdc_beta_s2s4);

    // calculation of delta(momentum_deviation) and AoQ
    mean_brho_s2s4 = 0.5 * (frs.bfield[2] + frs.bfield[3]);
    if (temp_s4x == -999 || temp_s2x == -999)
    {
        item.id_mhtdc_aoq_s2s4 = 0;
        item.id_mhtdc_aoq_corr_s2s4 = 0;
    }
    else if (-200 < temp_s4x && temp_s4x < 200. && -200. < temp_s2x && temp_s2x < 200.)
    {
        item.id_mhtdc_delta_s2s4 = (temp_s4x - (temp_s2x * frs.magnification[1])) / (-1.0 * frs.dispersion[1] * 1000.0); //1000 is dispertsion from meter to mm. -1.0 is sign definition.
  
        if(0.0 < item.id_mhtdc_beta_s2s4 && item.id_mhtdc_beta_s2s4 < 1.0)
        {
            item.id_mhtdc_aoq_s2s4 = mean_brho_s2s4 * ( 1. + item.id_mhtdc_delta_s2s4) * temp_tm_to_MeV / (temp_mu * item.id_mhtdc_beta_s2s4 * item.id_mhtdc_gamma_s2s4);
            item.id_mhtdc_aoq_corr_s2s4 = item.id_mhtdc_aoq_s2s4 - id.a2AoQCorr * item.id_a4;
        }
    
    }
    else 
    {
        item.id_mhtdc_aoq_s2s4=0;
    }
    
    // calculation of dE and Z
    // from MUSIC41
    float temp_music41_de = item.de[0] > 0.0;
    if ((temp_music41_de > 0.0)  && (item.id_mhtdc_beta_s2s4 > 0.0) && (item.id_mhtdc_beta_s2s4 < 1.0))
    {
        double power = 1., sum = 0.;
        for (int i = 0;i < 4; i++)
        {
            sum += power * id.mhtdc_vel_a_music41[i];
            power *= item.id_mhtdc_beta_s2s4;
        }
        item.id_mhtdc_v_cor_music41 = sum;
        if (item.id_mhtdc_v_cor_music41 > 0.0)
        {
            item.id_mhtdc_z_music41 = frs.primary_z * sqrt(item.de[0] / item.id_mhtdc_v_cor_music41 ) + id.mhtdc_offset_z_music41;
        }
    }

    float temp_music42_de = item.de[1] > 0.0;
    if((temp_music42_de > 0.0) && (item.id_mhtdc_beta_s2s4 > 0.0) && (item.id_mhtdc_beta_s2s4 < 1.0))
    {
        double power = 1., sum = 0.;
        for (int i = 0; i < 4;i++)
        {
            sum += power * id.mhtdc_vel_a_music42[i];
            power *= item.id_mhtdc_beta_s2s4;
        }
        item.id_mhtdc_v_cor_music42 = sum;
        if (item.id_mhtdc_v_cor_music42 > 0.0)
        {
            item.id_mhtdc_z_music42 = frs.primary_z * sqrt(item.de[1] / item.id_mhtdc_v_cor_music42) + id.mhtdc_offset_z_music42;
        }
    }
 
 
    item.id_trigger = item.trigger;
    float mhtdc_gamma1square = 1.0 + pow(((299.792458 / 931.494) * (item.id_brho[0] / item.id_mhtdc_aoq_s2s4)), 2); // TMath::Power
    item.id_mhtdc_gamma_ta_s2 = sqrt(mhtdc_gamma1square); // TMath::Sqrt
    item.id_mhtdc_dEdegoQ = (item.id_mhtdc_gamma_ta_s2 - item.id_mhtdc_gamma_s2s4) * item.id_mhtdc_aoq_s2s4;
    item.id_mhtdc_dEdeg = item.id_mhtdc_dEdegoQ * item.id_mhtdc_z_music41;

    // focal plane information
    // S2 priority: tpc2324 -> tpc2224 -> tpc2122 -> sc22 -> sc21
    if(id.x_s2_select == 1)
    {
        if(item.b_tpc_xy[2] && item.b_tpc_xy[3])
        {   //tpc2324 -- for our expts only this is relevant
            item.id_x2 = item.tpc_x_s2_foc_23_24;
            item.id_y2 = item.tpc_y_s2_foc_23_24;
            item.id_a2 = item.tpc_angle_x_s2_foc_23_24;
            item.id_b2 = item.tpc_angle_y_s2_foc_23_24;
        }
        else if (item.b_tpc_xy[1] && item.b_tpc_xy[3])
        {   //tpc2224
            item.id_x2 = item.tpc_x_s2_foc_22_24;
            item.id_y2 = item.tpc_y_s2_foc_22_24;
            item.id_a2 = item.tpc_angle_x_s2_foc_22_24;
            item.id_b2 = item.tpc_angle_y_s2_foc_22_24;
        }
        else if (item.b_tpc_xy[0] && item.b_tpc_xy[1])
        {   //tpc2122
            item.id_x2 = item.tpc_x_s2_foc_21_22;
            item.id_y2 = item.tpc_y_s2_foc_21_22;
            item.id_a2 = item.tpc_angle_x_s2_foc_21_22;
            item.id_b2 = item.tpc_angle_y_s2_foc_21_22;
        }
    }
    else if (id.x_s2_select == 2)
    {
        if (item.sci_b_x[2])
        {   //sc21
            item.id_x2 = item.sci_x[2];
            item.id_y2 = 0.0;
            item.id_a2 = 0.0;
            item.id_b2 = 0.0;
        }
    }
    else if (id.x_s2_select == 3)
    {
        if (item.sci_b_x[3])
        {   //sc22
            item.id_x2 = item.sci_x[3];
            item.id_y2 = 0.0;
            item.id_a2 = 0.0;
            item.id_b2 = 0.0;
        }
    }
    // S4 only 1 possibility =  TPC4142
    if (item.b_tpc_xy[4] && item.b_tpc_xy[5])
    {   
        item.id_x4 = item.tpc_x_s4;
        item.id_a4 = item.tpc_angle_x_s4;
        item.id_y4 = item.tpc_y_s4;
        item.id_b4 = item.tpc_angle_y_s4;
    }

    // S8 only 1 possibility =  SC81x
    if(item.sci_b_x[10])
    {
        item.id_x8 = item.sci_x[10];
        item.id_a8 = 0.0;
        item.id_y8 = 0.0;
        item.id_b8 = 0.0;
    }

    /*  check that the positions are OK   */
    item.id_b_x2 = Check_WinCond(item.id_x2, cID_x2);// cID_x2->Test(id_x2);
    item.id_b_x4 = Check_WinCond(item.id_x4, cID_x4);// cID_x4->Test(id_x4);
  

    /*----------------------------------------------------------*/
    /* Determination of beta                                    */
    /* id.TofOff(i)                   Flight time offset [ps]   */
    /* id.Path(i)                     Flight path/c [ps]        */
    /* TOF(i)        BIN FLOAT(24),   Flight time  [ps]         */
    /*----------------------------------------------------------*/

    //SC21-SC41
    if (id.tof_s4_select == 1)
    {   //SC21-SC41
        if (item.sci_b_tofll2 && item.sci_b_tofrr2)
        {      
            item.id_beta = id.id_path2 / item.sci_tof2_calib;// calculate non-inverted "real" tof already in sci analysis.
        }
    }
    else if (id.tof_s4_select == 2)
    {   //SC21-SC42
        if (item.sci_b_tofll3 && item.sci_b_tofrr3)
        {
            item.id_beta = id.id_path3 / item.sci_tof3_calib;// calculate non-inverted "real" tof already in sci analysis.
        }
    }
    else if (id.tof_s4_select == 3)
    {   //SC22-SC41
        if (item.sci_b_tofll5 && item.sci_b_tofrr5)
        {
            item.id_beta = id.id_path5 /  item.sci_tof5_calib;// calculate non-inverted "real" tof already in sci analysis.
        }
    }

    // /*------------------------------------------------------*/
    // /* Determination of Brho                                */
    // /* Dispersion and magnification are still the same      */
    // /* variable for S41-S21 and S42-S41, adjust in setup.C  */
    // /*------------------------------------------------------*/

    // first half of FRS, TA-S2
    if (item.id_b_x2)
    {
        item.id_rho[0] = frs.rho0[0] * (1. - item.id_x2 / 1000. / frs.dispersion[0]);
        item.id_brho[0] = (fabs(frs.bfield[0]) + fabs(frs.bfield[1])) / 2. * item.id_rho[0];
    }
    
    // second half S2-S4
    if (item.id_b_x2 && item.id_b_x4)
    {
        item.id_rho[1] = frs.rho0[1] * (1. - (item.id_x4 - frs.magnification[1] * item.id_x2) / 1000. / frs.dispersion[1]);
        item.id_brho[1] = (fabs(frs.bfield[2]) + fabs(frs.bfield[3])) / 2. * item.id_rho[1];
    }
  

    /*--------------------------------------------------------------*/
    /* Determination of A/Q                                         */
    /*--------------------------------------------------------------*/
    /* Beta(i)       BIN FLOAT(24),   Beta = v/c                    */
    /* Gamma(i)      BIN FLOAT(24),   Gamma= sqrt(1/1-beta**2)      */
    /*--------------------------------------------------------------*/
    float f = 931.4940 / 299.792458 ;    /* factor needed for aoq calculation.. the u/(c*10^-6) factor  */

    /* for S2-S4 */
  
    if (item.sci_b_tofll2 && item.sci_b_tofrr2 && item.id_b_x2 && item.id_b_x4)
    {   
        if ((item.id_beta > 0.0) && (item.id_beta < 1.0))
        {   
            item.id_gamma = 1. / sqrt(1. - item.id_beta * item.id_beta);
            item.id_AoQ = item.id_brho[1] / item.id_beta / item.id_gamma / f;
            item.id_AoQ_corr = item.id_AoQ - id.a2AoQCorr * item.id_a2;  //correction for id_a2, JK 16.9.11
            item.id_b_AoQ = true;
        }
    }

    /*------------------------------------------------*/
    /* Determination of Z                             */
    /*------------------------------------------------*/
    /****  S4  (MUSIC 1)   */

    if((item.de[0] > 0.0) && (item.id_beta > 0.0) && (item.id_beta < 1.0))
    {   

        double power = 1., sum = 0.;
        for (int i = 0; i < 4; i++)
        {   
            sum += power * id.vel_a[i];
            power *= item.id_beta;
        }
        item.id_v_cor = sum;
        if (item.id_v_cor > 0.0)
        {   
            item.id_z = frs.primary_z * sqrt(item.de[0] / item.id_v_cor) + id.offset_z;

        }
        if ((item.id_z > 0.0) && (item.id_z < 100.0))
        {
            item.id_b_z = true; // kTRUE
        }
    }

    /****  S4  (MUSIC 2)   */
    if((item.de[1] > 0.0) && (item.id_beta > 0.0) && (item.id_beta < 1.0))
    {
        double power = 1., sum = 0.;
        for (int i = 0; i < 4; i++)
        {
            sum += power * id.vel_a2[i];
            power *= item.id_beta;
        }
        item.id_v_cor2 = sum;
    
        if (item.id_v_cor2 > 0.0)
        {
            item.id_z2 = frs.primary_z * sqrt(item.de[1] / item.id_v_cor2) + id.offset_z2; 
        }
        if ((item.id_z2 > 0.0) && (item.id_z2 < 100.0))
        {
            item.id_b_z2 = true; // kTRUE
        }
    }


    /****  S4  (MUSIC)   */
    if ((item.de[2] > 0.0) && (item.id_beta > 0.0) && (item.id_beta < 1.0))
    {
        double power = 1., sum = 0.;
        for (int i = 0; i < 4;i++)
        {
            sum += power * id.vel_a3[i];
            power *= item.id_beta;
        }
        item.id_v_cor3 = sum;
        if (item.id_v_cor3 > 0.0)
        {
            item.id_z3 = frs.primary_z * sqrt(item.de[2] / item.id_v_cor3) + id.offset_z3;
        }

        if ((item.id_z3 > 0.0) && (item.id_z3 < 100.0))
        {
            item.id_b_z3 = true; // kTRUE
        }
    }

    //Z from tpc21222324
    double temp_s2tpc_de = 1.0; 
    int temp_s2tpc_de_count = 0;
    for (int ii = 0; ii < 4; ii++)
    {
        if (item.b_tpc_de[ii])
        {
            temp_s2tpc_de *= item.tpc_de[ii]; 
            temp_s2tpc_de_count++;
        }
    }
    if (temp_s2tpc_de_count == 2)
    {
        item.id_de_s2tpc = pow(temp_s2tpc_de, 1. / temp_s2tpc_de_count);
        item.id_b_de_s2tpc = true; // kTRUE
    }

    // charge state for high Z
    // S468 2020 April
    if (item.id_b_AoQ && item.id_b_x2 && item.id_b_z)
    {
        float gamma1square = 1.0 + pow(((299.792458 / 931.494) * (item.id_brho[0] / item.id_AoQ)), 2); // TMath
        item.id_gamma_ta_s2 = sqrt(gamma1square); // TMath::Sqrt
        item.id_dEdegoQ = (item.id_gamma_ta_s2 - item.id_gamma) * item.id_AoQ;
        item.id_dEdeg = item.id_dEdegoQ * item.id_z;
    }

    // ID PLOTS REMOVED - CEJ
    
}

// ----- extra functions ---- // 
int EXT_FRS::getbits(uint32 value, int nword, int start, int length)
{   
    uint32 buf = (uint32) value;
    buf = buf >> ((nword - 1) * 16 + start - 1);
    buf = buf & ((1 << length) - 1);
    return buf;
}

int EXT_FRS::get2bits(uint32 value, int nword, int start, int length)
{   
    uint32 buf = (uint32) value;
    buf = buf >> ((nword - 1) * 32 + start - 1);
    buf = buf & ((1 << length) - 1);
    return buf;
}

float EXT_FRS::rand3()
{
    return rand() - 0.5;
    
    //random3.Uniform(-0.5, 0.5);
}

bool EXT_FRS::Check_WinCond(float P, double* V)
{
    if (P >= V[0] && P <= V[1]) return true;
    else return false;
}

bool EXT_FRS::Check_WinCond_Multi(float P, float **V, int cond_num)
{
    if (P >= V[cond_num][0] && P <= V[cond_num][1]) return true;
    else return false;
}

double EXT_FRS::VFTX_GetTraw_ps(frs_item item, int module, int channel, int cc, int ft, float rand)
{
    double gain;
    double calib = (double) item.VFTX_Bin2Ps[module][channel][ft];

    if (calib == 0) calib = ft;
    if (rand < 0)
    {
        double calib_prev = (double) item.VFTX_Bin2Ps[module][channel][ft - 1];
        gain = calib - calib_prev;
    }
    else
    {
        double calib_next = (double) item.VFTX_Bin2Ps[module][channel][ft + 1];
        gain = calib_next - calib;
    }

    double ft_ps = calib + gain * (double) rand;
    double cc_ps = (double) cc;

    return (5000. * cc_ps - ft_ps);
}

bool EXT_FRS::Check_PolyCond_X_Y(float X, float Y, double V[][2], int n)
{   
    int cn = 0;
    for (int i = 0; i < n; i++)
    {
        if (((V[i][1] <= Y) && (V[i+1][1] > Y)) || ((V[i][1] > Y) && (V[i+1][1] <= Y)))
        {   
            // float vt = (float)
            double vt = (double)(Y - V[i][1]) / (V[i+1][1] - V[i][1]);
            if (X < V[i][0] + vt * (V[i+1][0] - V[i][0]))
            {
                cn++;
            }
        }
    }

    if ((cn & 1) == 0) return false;
    if ((cn & 1) == 1) return true;
    else return false;
}
