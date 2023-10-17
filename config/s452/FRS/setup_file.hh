
//#include "../../frs_parameter.hh"

namespace FRSGlobalParameters
{
    TFRSParameter* frs = new TFRSParameter
    {
        // For the momemnt, we put 1 m for radius,
        // because we get brho from control system.
        frs->rho0[0]   = 1., //TA-S2
        frs->rho0[1]   = 1., //S2-S4
        frs->rho0[2]   = 1., //S4-S8
        frs->rho0[3]   = 0.,
        frs->rho0[4]   = 0.,
        frs->rho0[5]   = 0.,
        frs->rho0[6]   = 0.,
        frs->dispersion[0]    = -6.474266,// RUN81-TA2B-220CM 27.05.2016
        frs->dispersion[1]    =  7.670,  // RUN81-TA2B-220CM 27.05.2016
        frs->magnification[1] =  1.18,   // RUN81-TA2B-220CM 27.05.2016
        frs->dispersion[2]    = 12.397,   //S2-S8 (gicosy sign definition)
        frs->magnification[2] =  1.829,   //S2-S8
        
        //S2
        //  frs->dist_focS2 = 2012.5, // degrader disk position stabdard
        frs->dist_focS2 = 3300.0, // low-dispersion S2-S4
        frs->dist_MW21  =  604.0,
        frs->dist_MW22  = 1782.5,
        frs->dist_SC21  = 1554.5,
        frs->dist_SC22  = 2595.0, //BARB 2021 Feb Logbook  
        frs->dist_TPC21 =  604.0,
        frs->dist_TPC22 = 1782.5,
        frs->dist_TPC23 = 2915.0, //BARB 2021 Feb Logbook  
        frs->dist_TPC24 = 3980.0, //BARB 2021 Feb Logbook
        frs->dist_S2target = 3600.0, // Interaction Cross section (01.March 2021)

        //S4
        //  frs->dist_focS4   = 3100.0, //BARB 2021 Feb   ... std
        //frs->dist_focS4   = 2200.0, //S2S4 low dispersion mode
        frs->dist_SC41    = 2245.0,
        frs->dist_SC42    = 2620.0,
        frs->dist_SC43    = 4706.0,
        frs->dist_MUSIC41 = 735.0,
        frs->dist_MUSIC42 = 1215.0,
        frs->dist_MUSIC43 = 5013.0,
        frs->dist_TPC41   =  415.0,
        //  frs->dist_TPC42   = 1535.0, moved to avoid conflict. before 2020april run.
        frs->dist_TPC42 = 1528.0, //for s468. 2020 april 
        frs->dist_S4target= 4000.0, //for some experiments

        //S8
        frs->dist_focS8 = 0,
        frs->dist_MW81 = 0,
        frs->dist_MW82 = 0,
        frs->dist_SC81 = 0,

        frs->primary_z = 82.,

        frs->bfield[0] = 13.3474,//                 Please do NOT comment-out old brho and add new brho. Please make a NEW setup file. 
        frs->bfield[1] = 12.5166,//                 Please do NOT comment-out old brho and add new brho. Please make a NEW setup file. 
        frs->bfield[2] = 10.5376, //                 Please do NOT comment-out old brho and add new brho. Please make a NEW setup file. 
        frs->bfield[3] = 10.5376, //                 Please do NOT comment-out old brho and add new brho. Please make a NEW setup file. 
        frs->bfield[4] = 99.999, // D5 (to ESR) not used
        frs->bfield[5] = 99.999, // D6 (to S8)
    };
 
    static TIDParameter* id = new TIDParameter
    {
        id->x_s2_select   = 1, //1=tpc,2=sc21,3=sc22
        id->tof_s4_select = 1, //1=sc21-41, 2=sc21-42, 3=sc22-41
        id->tof_s8_select = 1, //1=sc21-81, 2=sc22-81

        id->min_aoq_plot = 2,
        id->max_aoq_plot = 3,
        id->min_z_plot   = 30.0,
        id->max_z_plot   = 90.0,

        // TOF calibration SC21-SC81 (TAC)
        id->id_tofoff4  = 326337.1,   //SC21-81 [ps]          // quickly done from run156 and 166 (2019/Nov, YT)
        id->id_path4    = 246983.1,   //SC21-81  path/c [ps]  // quickly done from run156 and 166 (2019/Nov, YT)

      // TOF calibration SC21-SC81 (TAC)
        id->id_tofoff6  = 405709.2,   //SC22-81 [ps]          // 21feb2020 DK, YT
        id->id_path6    = 278586.5,   //SC22-81  path/c [ps]  // 21feb2020 DK, YT

        // TPC@S2->Z estimation, velocity correction (TAC)
        id->vel_a_s2tpc[0] =  1400.,// TPC-A was not measured during tof calib.
        id->vel_a_s2tpc[1] =  0.0,// now we estimate from ATIMA. and then
        id->vel_a_s2tpc[2] =  0.0,// translate parameters to fit go4 parametes. (YT)
        id->vel_a_s2tpc[3] =  0.0,
        id->offset_z_s2tpc =  0.0,

        // SC81->Z estimation, velocity correction (TAC)
        id->vel_a_sc81[0] =   2156.4,// SC81 dE was not propery measured.
        id->vel_a_sc81[1] =  -1470.4,// I skip to set these parameters
        id->vel_a_sc81[2] =   0.0,// this time ...
        id->vel_a_sc81[3] =   0.0,
        id->offset_z_sc81 =   0.0,
        
        // From here Multi-HitTDC analysis
        id->mhtdc_length_s2s8 = 85.230, // (2019/Nov, YT)
        id->mhtdc_s2pos_option=1, //(1: sc21x-timediff-mhtdc, 2:tpc),
        id->pos_offset_sc81x  = 7.0,// (2019/Nov, YT)

        // MHTDCAnalysis TPC@S2dE => Z estimation, velocity correction
        id->mhtdc_vel_a_s2tpc[0] =  1400.0,// TPC-A does not look promising...21-feb-2020
        id->mhtdc_vel_a_s2tpc[1] =  0.0,// put constant here
        id->mhtdc_vel_a_s2tpc[2] =  0.0,// 
        id->mhtdc_vel_a_s2tpc[3] =  0.0,
        id->mhtdc_offset_z_s2tpc =  0.0,

        // MHTDCAnalysis, velocity correction SC81dE => Z estimation
        id->mhtdc_vel_a_sc81[0] =  2156.4,// SC81 dE was not propery measured.
        id->mhtdc_vel_a_sc81[1] =  0.0, // I skip to set these parameters
        id->mhtdc_vel_a_sc81[2] =  0.0, // this time ...
        id->mhtdc_vel_a_sc81[3] =  0.0,
        id->mhtdc_offset_z_sc81 =  0.0,

        //not related for S8
        id->offset_z   = 0.0 ,
        id->offset_z2  = 0.0 ,
        id->offset_z3  = 0.0 ,
        id->a2AoQCorr = 0.0012, //2020April12 JP
        id->a4AoQCorr = 0.0,

        //  MUSIC41 velocity 06.03.21 Pb s452
        id->vel_a[0] =   20888.0, //  MUSIC41 velocity corr. s533
        id->vel_a[1] =  -40943.0,   // 
        id->vel_a[2] =   22456.0, // 
        id->vel_a[3] =   0.0,

      // MUSIC42 velocity 06.03.21 Pb s452
        id->vel_a2[0] =  13490.0 , 
        id->vel_a2[1] = -22027.0,
        id->vel_a2[2] =  10453.0,
        id->vel_a2[3] =  0.0,
        
        id->vel_a3[0] =  13951.37, //MUSIC43 velocity corr. (old)
        id->vel_a3[1] = -38369.9,
        id->vel_a3[2] =  28396.46,
        id->vel_a3[3] =  0.0,
        
        //TOF_SC42_SC21_TAC 06.03.21 Pb s452
        id->id_tofoff3  = 187701.,   // offset (ps)
        id->id_path3    = 134732.,   // path/c [ps]

        //TOF_SC41_SC21_TAC 06.03.21 Pb s452
        id->id_tofoff2 =  176384.,  // offset (ps)
        id->id_path2   =  123877.,  // path/c (ps)

        //TOF_SC41_SC22_TAC 06.03.21 Pb s452
        id->id_tofoff5 =  168010.,  // offset (ps) 
        id->id_path5   =  119612.,  // path/c (ps)

        
        id->mhtdc_length_s2s4 = 36.7760, // SCI 21-41 s452 E.S.
        id->mhtdc_vel_a_music41[0]=20888.0,
        id->mhtdc_vel_a_music41[1]=-40943.0,
        id->mhtdc_vel_a_music41[2]=22456.0,
        id->mhtdc_vel_a_music41[3]=0.0,
        id->mhtdc_vel_a_music42[0]=13490.0,
        id->mhtdc_vel_a_music42[1]=-22027.0,
        id->mhtdc_vel_a_music42[2]=10453.0,
        id->mhtdc_vel_a_music42[3]=0.0,
        id->mhtdc_offset_z_music41=0.0,
        id->mhtdc_offset_z_music42=0.0,

        //---- initial value for Z vs AoQ PID -----//
        id->ID_Z_AoverQ_num[0]=5,
        id->ID_Z_AoverQ_num[1]=5,
        id->ID_Z_AoverQ_num[2]=5,
        id->ID_Z_AoverQ_num[3]=5,
        id->ID_Z_AoverQ_num[4]=5,

        //203Pt
        id->ID_Z_AoverQ[0][0][0]=2.602      , id->ID_Z_AoverQ[0][0][1]=78.1,
        id->ID_Z_AoverQ[0][1][0]=2.602      , id->ID_Z_AoverQ[0][1][1]=77.3,
        id->ID_Z_AoverQ[0][2][0]=2.587      , id->ID_Z_AoverQ[0][2][1]=77.3,
        id->ID_Z_AoverQ[0][3][0]=2.587      , id->ID_Z_AoverQ[0][3][1]=78.1 ,
        id->ID_Z_AoverQ[0][4][0]=2.587      , id->ID_Z_AoverQ[0][4][1]=78.1,

        //Ir200
        id->ID_Z_AoverQ[1][0][0]=2.600, id->ID_Z_AoverQ[1][0][1]=77.2,
        id->ID_Z_AoverQ[1][1][0]=2.600, id->ID_Z_AoverQ[1][1][1]=76.6,
        id->ID_Z_AoverQ[1][2][0]=2.587, id->ID_Z_AoverQ[1][2][1]=76.6,
        id->ID_Z_AoverQ[1][3][0]=2.587, id->ID_Z_AoverQ[1][3][1]=77.2,
        id->ID_Z_AoverQ[1][4][0]=2.600, id->ID_Z_AoverQ[1][4][1]=77.2,

        // all
        id->ID_Z_AoverQ[2][0][0]=2.4, id->ID_Z_AoverQ[2][0][1]=70.,
        id->ID_Z_AoverQ[2][1][0]=2.4, id->ID_Z_AoverQ[2][1][1]=80.,
        id->ID_Z_AoverQ[2][2][0]=2.8, id->ID_Z_AoverQ[2][2][1]=80.,
        id->ID_Z_AoverQ[2][3][0]=2.8, id->ID_Z_AoverQ[2][3][1]=70.,
        id->ID_Z_AoverQ[2][4][0]=2.4, id->ID_Z_AoverQ[2][4][1]=70.,

        id->ID_Z_AoverQ[3][0][0]=2.208+0.036, id->ID_Z_AoverQ[3][0][1]=1180,
        id->ID_Z_AoverQ[3][1][0]=2.208+0.036, id->ID_Z_AoverQ[3][1][1]=60,
        id->ID_Z_AoverQ[3][2][0]=2.220+0.036, id->ID_Z_AoverQ[3][2][1]=60,
        id->ID_Z_AoverQ[3][3][0]=2.220+0.036, id->ID_Z_AoverQ[3][3][1]=1180,
        id->ID_Z_AoverQ[3][4][0]=2.208+0.036, id->ID_Z_AoverQ[3][4][1]=1180,

        id->ID_Z_AoverQ[4][0][0]=2.208+0.048, id->ID_Z_AoverQ[4][0][1]=1180,
        id->ID_Z_AoverQ[4][1][0]=2.208+0.048, id->ID_Z_AoverQ[4][1][1]=60,
        id->ID_Z_AoverQ[4][2][0]=2.220+0.048, id->ID_Z_AoverQ[4][2][1]=60,
        id->ID_Z_AoverQ[4][3][0]=2.220+0.048, id->ID_Z_AoverQ[4][3][1]=1180,
        id->ID_Z_AoverQ[4][4][0]=2.208+0.048, id->ID_Z_AoverQ[4][4][1]=1180,

        //---- initial value for x2 vs AoQ PID -----//
        id->ID_x2AoverQ_num[0]=5,
        id->ID_x2AoverQ_num[1]=5,
        id->ID_x2AoverQ_num[2]=5,
        id->ID_x2AoverQ_num[3]=5,
        id->ID_x2AoverQ_num[4]=5,

        id->ID_x2AoverQ[0][0][0]=2.24433, id->ID_x2AoverQ[0][0][1]=42.5864,
        id->ID_x2AoverQ[0][1][0]=2.17429, id->ID_x2AoverQ[0][1][1]=-68.2431,
        id->ID_x2AoverQ[0][2][0]=2.18351, id->ID_x2AoverQ[0][2][1]=-70.9073,
        id->ID_x2AoverQ[0][3][0]=2.2573, id->ID_x2AoverQ[0][3][1]=40.9879,
        id->ID_x2AoverQ[0][4][0]=2.24433,id->ID_x2AoverQ[0][4][1]=42.5864,

        id->ID_x2AoverQ[1][0][0]=2.27782, id->ID_x2AoverQ[1][0][1]=58.1797,
        id->ID_x2AoverQ[1][1][0]=2.18477, id->ID_x2AoverQ[1][1][1]=-66.2442,
        id->ID_x2AoverQ[1][2][0]=2.19417, id->ID_x2AoverQ[1][2][1]=-69.7005,
        id->ID_x2AoverQ[1][3][0]=2.29192, id->ID_x2AoverQ[1][3][1]=57.0277,
        id->ID_x2AoverQ[1][4][0]=2.27782, id->ID_x2AoverQ[1][4][1]=58.1797,

        id->ID_x2AoverQ[2][0][0]=2.28597, id->ID_x2AoverQ[2][0][1]=40.8986,
        id->ID_x2AoverQ[2][1][0]=2.19548, id->ID_x2AoverQ[2][1][1]=-69.1244,
        id->ID_x2AoverQ[2][2][0]=2.21129, id->ID_x2AoverQ[2][2][1]=-69.1244,
        id->ID_x2AoverQ[2][3][0]=2.30014, id->ID_x2AoverQ[2][3][1]=40.3226,
        id->ID_x2AoverQ[2][4][0]=2.28597, id->ID_x2AoverQ[2][4][1]=40.8986,

        id->ID_x2AoverQ[3][0][0]=2.30468, id->ID_x2AoverQ[3][0][1]=41.0484,
        id->ID_x2AoverQ[3][1][0]=2.20712, id->ID_x2AoverQ[3][1][1]=-73.4407,
        id->ID_x2AoverQ[3][2][0]=2.22237, id->ID_x2AoverQ[3][2][1]=-73.1567,
        id->ID_x2AoverQ[3][3][0]=2.32009, id->ID_x2AoverQ[3][3][1]=41.0484,
        id->ID_x2AoverQ[3][4][0]=2.30468, id->ID_x2AoverQ[3][4][1]=41.0484,

        id->ID_x2AoverQ[4][0][0]=2.32064, id->ID_x2AoverQ[4][0][1]=39.6964,
        id->ID_x2AoverQ[4][1][0]=2.22332, id->ID_x2AoverQ[4][1][1]=-73.875,
        id->ID_x2AoverQ[4][2][0]=2.23886, id->ID_x2AoverQ[4][2][1]=-73.517,
        id->ID_x2AoverQ[4][3][0]=2.33663, id->ID_x2AoverQ[4][3][1]=39.6964,
        id->ID_x2AoverQ[4][4][0]=2.32064, id->ID_x2AoverQ[4][4][1]=39.6964,

        //---- initial value for x4 vs AoQ PID -----//
        id->ID_x4AoverQ_num[0]=5,
        id->ID_x4AoverQ_num[1]=5,
        id->ID_x4AoverQ_num[2]=5,
        id->ID_x4AoverQ_num[3]=5,
        id->ID_x4AoverQ_num[4]=5,

        id->ID_x4AoverQ[0][0][0]=2.24433, id->ID_x4AoverQ[0][0][1]=42.5864,
        id->ID_x4AoverQ[0][1][0]=2.17429, id->ID_x4AoverQ[0][1][1]=-68.2431,
        id->ID_x4AoverQ[0][2][0]=2.18351, id->ID_x4AoverQ[0][2][1]=-70.9073,
        id->ID_x4AoverQ[0][3][0]=2.2573, id->ID_x4AoverQ[0][3][1]=40.9879,
        id->ID_x4AoverQ[0][4][0]=2.24433,id->ID_x4AoverQ[0][4][1]=42.5864,

        id->ID_x4AoverQ[1][0][0]=2.27782, id->ID_x4AoverQ[1][0][1]=58.1797,
        id->ID_x4AoverQ[1][1][0]=2.18477, id->ID_x4AoverQ[1][1][1]=-66.2442,
        id->ID_x4AoverQ[1][2][0]=2.19417, id->ID_x4AoverQ[1][2][1]=-69.7005,
        id->ID_x4AoverQ[1][3][0]=2.29192, id->ID_x4AoverQ[1][3][1]=57.0277,
        id->ID_x4AoverQ[1][4][0]=2.27782, id->ID_x4AoverQ[1][4][1]=58.1797,

        id->ID_x4AoverQ[2][0][0]=2.28597, id->ID_x4AoverQ[2][0][1]=40.8986,
        id->ID_x4AoverQ[2][1][0]=2.19548, id->ID_x4AoverQ[2][1][1]=-69.1244,
        id->ID_x4AoverQ[2][2][0]=2.21129, id->ID_x4AoverQ[2][2][1]=-69.1244,
        id->ID_x4AoverQ[2][3][0]=2.30014, id->ID_x4AoverQ[2][3][1]=40.3226,
        id->ID_x4AoverQ[2][4][0]=2.28597, id->ID_x4AoverQ[2][4][1]=40.8986,

        id->ID_x4AoverQ[3][0][0]=2.30468, id->ID_x4AoverQ[3][0][1]=41.0484,
        id->ID_x4AoverQ[3][1][0]=2.20712, id->ID_x4AoverQ[3][1][1]=-73.4407,
        id->ID_x4AoverQ[3][2][0]=2.22237, id->ID_x4AoverQ[3][2][1]=-73.1567,
        id->ID_x4AoverQ[3][3][0]=2.32009, id->ID_x4AoverQ[3][3][1]=41.0484,
        id->ID_x4AoverQ[3][4][0]=2.30468, id->ID_x4AoverQ[3][4][1]=41.0484,

        id->ID_x4AoverQ[4][0][0]=2.32064, id->ID_x4AoverQ[4][0][1]=39.6964,
        id->ID_x4AoverQ[4][1][0]=2.22332, id->ID_x4AoverQ[4][1][1]=-73.875,
        id->ID_x4AoverQ[4][2][0]=2.23886, id->ID_x4AoverQ[4][2][1]=-73.517,
        id->ID_x4AoverQ[4][3][0]=2.33663, id->ID_x4AoverQ[4][3][1]=39.6964,
        id->ID_x4AoverQ[4][4][0]=2.32064, id->ID_x4AoverQ[4][4][1]=39.6964,

    };

    static TMWParameter* mw = new TMWParameter
    {
        mw->x_factor[0] = 0.25, // MW11 [mm/ns] some old value
        mw->x_factor[1] = 0.25, // MW21
        mw->x_factor[2] = 0.25, // MW22
        mw->x_factor[3] = 0.25, // MW31
        mw->x_factor[4] = 0.25, // MW51
        mw->x_factor[5] = 0.25, // MW71
        mw->x_factor[6] = 0.25, // MW81
        mw->x_factor[7] = 0.125, // MW82

        mw->x_offset[0] = 5.0, // MW11 Feb 2014
        mw->x_offset[1] = -2.0, // MW21 Feb 2014
        mw->x_offset[2] = -1.5, // MW22 Feb 2014
        mw->x_offset[3] = 5.0, // MW31 like MW11 15.11.19
        mw->x_offset[4] = -0.205, // MW51
        mw->x_offset[5] = 1.642, // MW71 //15/05/06
        mw->x_offset[6] = 1.,   // MW81 //11/05/06
        mw->x_offset[7] = -5., // MW82 //27-MAY-2007

        mw->y_factor[0] = 0.25, // MW11 [mm/ns] 14.09.05 CN+AM 2ns/mm delay line
        mw->y_factor[1] = 0.25, // MW21
        mw->y_factor[2] = 0.25, // MW22
        mw->y_factor[3] = 0.25, // MW31
        mw->y_factor[4] = 0.25, // MW51
        mw->y_factor[5] = 0.25, // MW71
        mw->y_factor[6] = 0.25, // MW81
        mw->y_factor[7] = 0.125, // MW82  [mm/ns] 11.05.06  CN 4ns/mm delay line

        mw->y_offset[0] = -14.0,  // MW11 27-MAY-2007 TESTED VALUE WITH SLITS, ok Feb 2014
        mw->y_offset[1] = 21.0,   // Feb 2014
        mw->y_offset[2] = -1.0,   // MW22 27-MAY-2007 TESTED VALUE WITH SLITS, ok Feb 2014
        mw->y_offset[3] = -14.0,    // MW31 like in MW11 15.11.19
        mw->y_offset[4] = 0.0,     //MW51  ???????
        mw->y_offset[5] = -2.736,  // MW71 //15/05/06
        mw->y_offset[6] = 3.2,     // MW81 //11/05/06
        mw->y_offset[7] = 0.764,  // MW82 //11/05/06


        mw->gain_tdc[0][0] = 0.302929, //  MW11 Anode (#ch  0 TDC V775a) // 13.01.2008
        mw->gain_tdc[1][0] = 0.303253, //  MW11 XL    (#ch 17 TDC V775a)
        mw->gain_tdc[2][0] = 0.303975, //  MW11 XR    (#ch 16 TDC V775a)
        mw->gain_tdc[3][0] = 0.308414, //  MW11 YU    (#ch 18 TDC V775a)
        mw->gain_tdc[4][0] = 0.309826, //  MW11 YD    (#ch 19 TDC V775a)

        mw->gain_tdc[0][1] = 0.306064, //  MW21 Anode (#ch  1 TDC V775a) // 13.01.2008
        mw->gain_tdc[1][1] = 0.306958, //  MW21 XL    (#ch 21 TDC V775a)
        mw->gain_tdc[2][1] = 0.307799, //  MW21 XR    (#ch 20 TDC V775a)
        mw->gain_tdc[3][1] = 0.297774, //  MW21 YU    (#ch 22 TDC V775a)
        mw->gain_tdc[4][1] = 0.310235, //  MW21 YD    (#ch 23 TDC V775a)

        mw->gain_tdc[0][2] = 0.301179,  // MW22 Anode (#ch  2 TDC V775a) // 13.01.2008
        mw->gain_tdc[1][2] = 0.311121, //  MW22 XL    (#ch 25 TDC V775a)
        mw->gain_tdc[2][2] = 0.303233, //  MW22 XR    (#ch 24 TDC V775a)
        mw->gain_tdc[3][2] = 0.300558, //  MW22 YU    (#ch 26 TDC V775a)
        mw->gain_tdc[4][2] = 0.301105, //  MW22 YD    (#ch 27 TDC V775a)

        mw->gain_tdc[0][3] = 0.304426, //  MW31 Anode (#ch  3 TDC V775a) // 13.01.2008
        mw->gain_tdc[1][3] = 0.312163, //  MW31 XL    (#ch 29 TDC V775a)
        mw->gain_tdc[2][3] = 0.305609, //  MW31 XR    (#ch 28 TDC V775a)
        mw->gain_tdc[3][3] = 0.304716, //  MW31 YU    (#ch 30 TDC V775a)
        mw->gain_tdc[4][3] = 0.293695, //  MW31 YD    (#ch 31 TDC V775a)

        mw->gain_tdc[0][4] = 0.298871, //  MW41 Anode (#ch  4 TDC V775a) // 13.01.2008
        mw->gain_tdc[1][4] = 0.284086, //  MW41 XL    (#ch 1 TDC V775b)
        mw->gain_tdc[2][4] = 0.288656, //  MW41 XR    (#ch 0 TDC V775b)
        mw->gain_tdc[3][4] = 0.286589, //  MW41 YU    (#ch 2 TDC V775b)
        mw->gain_tdc[4][4] = 0.29269,  //  MW41 YD    (#ch 3 TDC V775b)

        mw->gain_tdc[0][5] = 0.297881, //  MW42 Anode (#ch  5 TDC V775a) // 13.01.2008
        mw->gain_tdc[1][5] = 0.287364, //  MW42 XL    (#ch 5 TDC V775b)
        mw->gain_tdc[2][5] = 0.289636, //  MW42 XR    (#ch 4 TDC V775b)
        mw->gain_tdc[3][5] = 0.291135, //  MW42 YU    (#ch 6 TDC V775b)
        mw->gain_tdc[4][5] = 0.289867, //  MW42 YD    (#ch 7 TDC V775b)

        mw->gain_tdc[0][6] = 0.307892, //  MW51 Anode (#ch  6 TDC V775a) // 13.01.2008
        mw->gain_tdc[1][6] = 0.289894, //  MW51 XL    (#ch  9 TDC V775b)
        mw->gain_tdc[2][6] = 0.292366, //  MW51 XR    (#ch  8 TDC V775b)
        mw->gain_tdc[3][6] = 0.284708, //  MW51 YU    (#ch 10 TDC V775b)
        mw->gain_tdc[4][6] = 0.28186,  //  MW51 YD    (#ch 11 TDC V775b)

        mw->gain_tdc[0][7] = 0.298266, //  MW61 Anode (#ch  7 TDC V775a) // 13.01.2008
        mw->gain_tdc[1][7] = 0.311, //  MW61 XL    (#ch ? TDC V775b)
        mw->gain_tdc[2][7] = 0.305, //  MW61 XR    (#ch ? TDC V775b)
        mw->gain_tdc[3][7] = 0.337, //  MW61 YU    (#ch ? TDC V775b)
        mw->gain_tdc[4][7] = 0.289, //  MW61 YD    (#ch ? TDC V775b)

        mw->gain_tdc[0][8] = 0.303602, //  MW71 Anode (#ch  8 TDC V775a) // 13.01.2008
        mw->gain_tdc[1][8] = 0.300082, //  MW71 XL    (#ch 13 TDC V775b)
        mw->gain_tdc[2][8] = 0.286092, //  MW71 XR    (#ch 12 TDC V775b)
        mw->gain_tdc[3][8] = 0.294287, //  MW71 YU    (#ch 14 TDC V775b)
        mw->gain_tdc[4][8] = 0.291341, //  MW71 YD    (#ch 15 TDC V775b)

        mw->gain_tdc[0][9] = 0.306041, //  MW81 Anode (#ch  9 TDC V775a) // 13.01.2008
        mw->gain_tdc[1][9] = 0.288468, //  MW81 XL    (#ch 17 TDC V775b)
        mw->gain_tdc[2][9] = 0.293831, //  MW81 XR    (#ch 16 TDC V775b)
        mw->gain_tdc[3][9] = 0.281296, //  MW81 YU    (#ch 18 TDC V775b)
        mw->gain_tdc[4][9] = 0.279099, //  MW81 YD    (#ch 19 TDC V775b)

        mw->gain_tdc[0][10] = 0.31314,  //  MW82 Anode (#ch 10 TDC V775a) // 13.01.2008
        mw->gain_tdc[1][10] = 0.287279, //  MW82 XL    (#ch 21 TDC V775b)
        mw->gain_tdc[2][10] = 0.284028, //  MW82 XR    (#ch 20 TDC V775b)
        mw->gain_tdc[3][10] = 0.28051,  //  MW82 YU    (#ch 22 TDC V775b)
        mw->gain_tdc[4][10] = 0.28743,  //  MW82 YD    (#ch 23 TDC V775b)

        mw->gain_tdc[0][11] = 0.299973, //  MWB21 Anode (#ch 11 TDC V775a) // 13.01.2008
        mw->gain_tdc[1][11] = 0.311, //  MWB21 XL    (#ch ? TDC V775b)
        mw->gain_tdc[2][11] = 0.305, //  MWB21 XR    (#ch ? TDC V775b)
        mw->gain_tdc[3][11] = 0.337, //  MWB21 YU    (#ch ? TDC V775b)
        mw->gain_tdc[4][11] = 0.289, //  MWB21 YD    (#ch ? TDC V775b)

        mw->gain_tdc[0][12] = 0.306923, //  MWB22 Anode (#ch 12 TDC V775a) // 13.01.2008
        mw->gain_tdc[1][12] = 0.311, //  MWB22 XL    (#ch ? TDC V775b)
        mw->gain_tdc[2][12] = 0.305, //  MWB22 XR    (#ch ? TDC V775b)
        mw->gain_tdc[3][12] = 0.337, //  MWB22 YU    (#ch ? TDC V775b)
        mw->gain_tdc[4][12] = 0.289, //  MWB22 YD    (#ch ? TDC V775b)
    };

    static TMUSICParameter* music = new TMUSICParameter
    {
         // histogram setup
        music->max_adc_music1 =    4096, //tum music
        music->max_adc_music2 =    4096, //tum music
        music->max_adc_music3 =  0x2000, //travel music
        music->max_tdc_music1 =    4096, //tum music
        music->max_tdc_music2 =    4096, //tum music
        music->max_tdc_music3 = 0x10000, //travel music
    
        music->dist_MUSICa1 = 52.5,  // do not change
        music->dist_MUSICa2 = 157.5, // do not change
        music->dist_MUSICa3 = 262.5, // do not change
        music->dist_MUSICa4 = 367.5, // do not change

        //MUSIC41
        music->e1_off[0]   = 0., //MUSIC41 offsets
        music->e1_off[1]   = 0.,
        music->e1_off[2]   = 0.,
        music->e1_off[3]   = 0.,
        music->e1_off[4]   = 0.,
        music->e1_off[5]   = 0.,
        music->e1_off[6]   = 0.,
        music->e1_off[7]   = 0.,

        music->e1_gain[0]   = 1., // MUSIC41 gains
        music->e1_gain[1]   = 1.,
        music->e1_gain[2]   = 1.,
        music->e1_gain[3]   = 1.,
        music->e1_gain[4]   = 1.,
        music->e1_gain[5]   = 1.,
        music->e1_gain[6]   = 1.,
        music->e1_gain[7]   = 1.,

        //MUSIC42
        music->e2_off[0]   = 0., //MUSIC42 offsets
        music->e2_off[1]   = 0.,
        music->e2_off[2]   = 0.,
        music->e2_off[3]   = 0.,
        music->e2_off[4]   = 0.,
        music->e2_off[5]   = 0.,
        music->e2_off[6]   = 0.,
        music->e2_off[7]   = 0.,

        music->e2_gain[0]   = 1., //MUSIC42 gains
        music->e2_gain[1]   = 1.,
        music->e2_gain[2]   = 1.,
        music->e2_gain[3]   = 1.,
        music->e2_gain[4]   = 1.,
        music->e2_gain[5]   = 1.,
        music->e2_gain[6]   = 1.,
        music->e2_gain[7]   = 1.,

        //MUSIC43
        music->e3_off[0]   = 2., //MUSIC3 offsets
        music->e3_off[1]   = 1.,
        music->e3_off[2]   = 1.,
        music->e3_off[3]   = 1.,
        music->e3_off[4]   = 1.,
        music->e3_off[5]   = 1.,
        music->e3_off[6]   = 1.,
        music->e3_off[7]   = 1.,

        music->e3_gain[0]   = 1., // MUSIC3 gains
        music->e3_gain[1]   = 1.,
        music->e3_gain[2]   = 1.,
        music->e3_gain[3]   = 1.,
        music->e3_gain[4]   = 1.,
        music->e3_gain[5]   = 1.,
        music->e3_gain[6]   = 1.,
        music->e3_gain[7]   = 1.,

        music->pos_a1[0]   = 1.0,   // C0...Cn position correction not used
        music->pos_a1[1]   = 0.0,
        music->pos_a1[2]   = 0.0,
        music->pos_a1[3]   = 0.0,
        music->pos_a1[4]   = 0.0,
        music->pos_a1[5]   = 0.0,
        music->pos_a1[6]   = 0.0,
    };
  
    static TTPCParameter* tpc = new TTPCParameter
    {
        // multihit TDC cut TPC time reference signal
        // After changing cut limits => Launch analysis again in Go4GUI
        tpc->lim_timeref[0][0] = 1000.0, tpc->lim_timeref[0][1] = 48000.0,//time ref (accept trig)
        tpc->lim_timeref[1][0] = 1000.0, tpc->lim_timeref[1][1] =  8500.0,//time ref (sc21)
        tpc->lim_timeref[2][0] = 1000.0, tpc->lim_timeref[2][1] =  9500.0,//time ref (sc22)
        tpc->lim_timeref[3][0] = 1000.0, tpc->lim_timeref[3][1] = 48000.0,//time ref (sc31)
        tpc->lim_timeref[4][0] = 1000.0, tpc->lim_timeref[4][1] = 48000.0,//time ref (sc41)
        tpc->lim_timeref[5][0] = 2000.0, tpc->lim_timeref[5][1] = 48000.0,//time ref (---)
        tpc->lim_timeref[6][0] = 2000.0, tpc->lim_timeref[6][1] = 48000.0,//time ref (---)
        tpc->lim_timeref[7][0] = 2000.0, tpc->lim_timeref[7][1] = 48000.0,//time ref (---)

        // TPC 1 at S2 (TPC 21) in vaccuum //// (BARB 2021 Feb 15) 
        // After changing cut limits => Launch analysis again in Go4GUI
        tpc->id_tpc_timeref[0] = 1, //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
        tpc->lim_dt[0][0][0] = 2000.,  tpc->lim_dt[0][0][1] = 48000.0, //A11 drift time TDC cut
        tpc->lim_dt[0][1][0] = 2000.,  tpc->lim_dt[0][1][1] = 48000.0, //A12 drift time TDC cut
        tpc->lim_dt[0][2][0] = 2000.,  tpc->lim_dt[0][2][1] = 48000.0, //A21 drift time TDC cut
        tpc->lim_dt[0][3][0] = 2000.,  tpc->lim_dt[0][3][1] = 48000.0, //A22 drift time TDC cut
        tpc->lim_lt[0][0][0] = 2000.,  tpc->lim_lt[0][0][1] = 48000.0, //DL1 time TDC cut
        tpc->lim_rt[0][0][0] = 2000.,  tpc->lim_rt[0][0][1] = 48000.0, //DR1 time TDC cut
        tpc->lim_lt[0][1][0] = 2000.,  tpc->lim_lt[0][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_rt[0][1][0] = 2000.,  tpc->lim_rt[0][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_csum1[0][0] = 13700.0,  tpc->lim_csum1[0][1] = 14600.0,
        tpc->lim_csum2[0][0] = 13900.0,  tpc->lim_csum2[0][1] = 14600.0,
        tpc->lim_csum3[0][0] = 13500.0,  tpc->lim_csum3[0][1] = 14600.0, 
        tpc->lim_csum4[0][0] = 13500.0,  tpc->lim_csum4[0][1] = 14600.0,
        tpc->x_offset[0][0] = -0.4-0.5,
        tpc->x_offset[0][1] =  1.2-0.5-2.0,
        tpc->x_factor[0][0] = 0.00786,
        tpc->x_factor[0][1] = 0.00786,
        tpc->y_offset[0][0] = -48.1-7.5-1.0+2.0,//s483, slit +/- 1mm 
        tpc->y_offset[0][1] = -48.2-8.5    +2.0,
        tpc->y_offset[0][2] = -48.0-9.0    +2.0,
        tpc->y_offset[0][3] = -48.2-8.5    +2.0,
        tpc->y_factor[0][0] = 0.004,
        tpc->y_factor[0][1] = 0.004,
        tpc->y_factor[0][2] = 0.004,
        tpc->y_factor[0][3] = 0.004,

        // TPC 2 at S2 (TPC 22) in vaccuum (BARB 2021 Feb 15) 
        // After changing cut limits => Launch analysis again in Go4GUI
        tpc->id_tpc_timeref[1] = 1, //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
        tpc->lim_dt[1][0][0] = 2000.,  tpc->lim_dt[1][0][1] = 48000.0, //A11 drift time TDC cut
        tpc->lim_dt[1][1][0] = 2000.,  tpc->lim_dt[1][1][1] = 48000.0, //A12 drift time TDC cut
        tpc->lim_dt[1][2][0] = 2000.,  tpc->lim_dt[1][2][1] = 48000.0, //A21 drift time TDC cut
        tpc->lim_dt[1][3][0] = 2000.,  tpc->lim_dt[1][3][1] = 48000.0, //A22 drift time TDC cut
        tpc->lim_lt[1][0][0] = 2000.,  tpc->lim_lt[1][0][1] = 48000.0, //DL1 time TDC cut
        tpc->lim_rt[1][0][0] = 2000.,  tpc->lim_rt[1][0][1] = 48000.0, //DR1 time TDC cut
        tpc->lim_lt[1][1][0] = 2000.,  tpc->lim_lt[1][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_rt[1][1][0] = 2000.,  tpc->lim_rt[1][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_csum1[1][0] = 17000.0,    tpc->lim_csum1[1][1] =  19200.0,
        tpc->lim_csum2[1][0] = 17000.0,    tpc->lim_csum2[1][1] =  19200.0,
        tpc->lim_csum3[1][0] = 17000.0,    tpc->lim_csum3[1][1] =  19200.0,
        tpc->lim_csum4[1][0] = 17000.0,    tpc->lim_csum4[1][1] =  19200.0,
        tpc->x_factor[1][0] = 0.0078,
        tpc->x_factor[1][1] = 0.0075,
        tpc->y_factor[1][0] = 0.004,
        tpc->y_factor[1][1] = 0.004,
        tpc->y_factor[1][2] = 0.004,
        tpc->y_factor[1][3] = 0.004,
        tpc->x_offset[1][0] = 1.2+1.0-1.8-1.0,
        tpc->x_offset[1][1] = 0.2-1.6-1.0,
        tpc->y_offset[1][0] = -48.1-9.0+2.7-0.2,//s483, slit +/- 1mm
        tpc->y_offset[1][1] = -48.2-9.0+2.7-0.5,
        tpc->y_offset[1][2] = -48.2-9.5+2.7-0.4,
        tpc->y_offset[1][3] = -47.8-9.3+2.7-0.3,

        // TPC 3 at S2 (TPC 23) in air (BARB 2021 Feb 15)
        // After changing cut limits => Launch analysis again in Go4GUI
        tpc->id_tpc_timeref[2] = 1, ////(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
        tpc->lim_dt[2][0][0] = 2000.,  tpc->lim_dt[2][0][1] = 48000.0, //A11 drift time TDC cut
        tpc->lim_dt[2][1][0] = 2000.,  tpc->lim_dt[2][1][1] = 48000.0, //A12 drift time TDC cut
        tpc->lim_dt[2][2][0] = 2000.,  tpc->lim_dt[2][2][1] = 48000.0, //A21 drift time TDC cut
        tpc->lim_dt[2][3][0] = 2000.,  tpc->lim_dt[2][3][1] = 48000.0, //A22 drift time TDC cut
        tpc->lim_lt[2][0][0] = 2000.,  tpc->lim_lt[2][0][1] = 48000.0, //DL1 time TDC cut
        tpc->lim_rt[2][0][0] = 2000.,  tpc->lim_rt[2][0][1] = 48000.0, //DR1 time TDC cut
        tpc->lim_lt[2][1][0] = 2000.,  tpc->lim_lt[2][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_rt[2][1][0] = 2000.,  tpc->lim_rt[2][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_csum1[2][0] = 13500.0,   tpc->lim_csum1[2][1] = 15000.0, //
        tpc->lim_csum2[2][0] = 13500.0,   tpc->lim_csum2[2][1] = 15000.0,
        tpc->lim_csum3[2][0] = 13500.0,   tpc->lim_csum3[2][1] = 15000.0,
        tpc->lim_csum4[2][0] = 13500.0,   tpc->lim_csum4[2][1] = 15000.0,
        tpc->x_offset[2][0] = 1.8+3.0-7.73+2, // two last alignement file in S511_20_0651
        tpc->x_offset[2][1] = 0.2+2.0-7.73+2,
        tpc->x_factor[2][0] = 0.0081,
        tpc->x_factor[2][1] = 0.0077,
        tpc->y_offset[2][0] = 48.4-1.0,
        tpc->y_offset[2][1] = 48.5-1.0,
        tpc->y_offset[2][2] = 48.4-1.0,
        tpc->y_offset[2][3] = 48.1-1.0,
        tpc->y_factor[2][0] = -0.004,
        tpc->y_factor[2][1] = -0.004,
        tpc->y_factor[2][2] = -0.004,
        tpc->y_factor[2][3] = -0.004,

        
        // TPC 4 at S2 (TPC 24) in air (BARB 2021 Feb 15)
        // After changing cut limits => Launch analysis again in Go4GUI
        tpc->id_tpc_timeref[3] = 4, //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
        tpc->timeref_calibrun[3] = 1037.0, //sc21
        tpc->lim_dt[3][0][0] = 2000.,  tpc->lim_dt[3][0][1] = 48000.0, //A11 drift time TDC cut
        tpc->lim_dt[3][1][0] = 2000.,  tpc->lim_dt[3][1][1] = 48000.0, //A12 drift time TDC cut
        tpc->lim_dt[3][2][0] = 2000.,  tpc->lim_dt[3][2][1] = 48000.0, //A21 drift time TDC cut
        tpc->lim_dt[3][3][0] = 2000.,  tpc->lim_dt[3][3][1] = 48000.0, //A22 drift time TDC cut
        tpc->lim_lt[3][0][0] = 2000.,  tpc->lim_lt[3][0][1] = 48000.0, //DL1 time TDC cut
        tpc->lim_rt[3][0][0] = 2000.,  tpc->lim_rt[3][0][1] = 48000.0, //DR1 time TDC cut
        tpc->lim_lt[3][1][0] = 2000.,  tpc->lim_lt[3][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_rt[3][1][0] = 2000.,  tpc->lim_rt[3][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_csum1[3][0] = 17500.0,    tpc->lim_csum1[3][1] = 19500.0, //
        tpc->lim_csum2[3][0] = 17500.0,    tpc->lim_csum2[3][1] = 19500.0,
        tpc->lim_csum3[3][0] = 17500.0,    tpc->lim_csum3[3][1] = 19500.0, //
        tpc->lim_csum4[3][0] = 17500.0,    tpc->lim_csum4[3][1] = 19500.0,
        tpc->x_offset[3][0] = 0.8 + 3.0-8.73+0.1, //two last alignement file in S511_20_0651
      tpc->x_offset[3][1] = -1.1 +3.5-8.73+0.1,
        tpc->x_factor[3][0] = 0.00782,
        tpc->x_factor[3][1] = 0.0088,
        tpc->y_offset[3][0] = 48.2 +10.5,
        tpc->y_offset[3][1] = 48.4 +10.5,
        tpc->y_offset[3][2] = 48.1 +10.0,
        tpc->y_offset[3][3] = 48.6 +10.0,
        tpc->y_factor[3][0] = -0.004,
        tpc->y_factor[3][1] = -0.004,
        tpc->y_factor[3][2] = -0.004,
        tpc->y_factor[3][3] = -0.004,
        
        // TPC 5  at S4 (TPC 41) in air (BARB 2021 Feb 15)
        // After changing cut limits => Launch analysis again in Go4GUI
        tpc->id_tpc_timeref[4] = 4, //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
        tpc->lim_dt[4][0][0] = 2000.,  tpc->lim_dt[4][0][1] = 48000.0, //A11 drift time TDC cut
        tpc->lim_dt[4][1][0] = 2000.,  tpc->lim_dt[4][1][1] = 48000.0, //A12 drift time TDC cut
        tpc->lim_dt[4][2][0] = 2000.,  tpc->lim_dt[4][2][1] = 48000.0, //A21 drift time TDC cut
        tpc->lim_dt[4][3][0] = 2000.,  tpc->lim_dt[4][3][1] = 48000.0, //A22 drift time TDC cut
        tpc->lim_lt[4][0][0] = 2000.,  tpc->lim_lt[4][0][1] = 48000.0, //DL1 time TDC cut
        tpc->lim_rt[4][0][0] = 2000.,  tpc->lim_rt[4][0][1] = 48000.0, //DR1 time TDC cut
        tpc->lim_lt[4][1][0] = 2000.,  tpc->lim_lt[4][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_rt[4][1][0] = 2000.,  tpc->lim_rt[4][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_csum1[4][0] = 13500.0,    tpc->lim_csum1[4][1] = 15500.0,
        tpc->lim_csum2[4][0] = 13500.0,    tpc->lim_csum2[4][1] = 15500.0,
        tpc->lim_csum3[4][0] = 13500.0,    tpc->lim_csum3[4][1] = 15500.0,
        tpc->lim_csum4[4][0] = 13500.0,    tpc->lim_csum4[4][1] = 15500.0,
        tpc->x_offset[4][0] = -1.6-1.0,
        tpc->x_offset[4][1] = -1.1-1.8,
        tpc->x_factor[4][0] = 0.00794,
        tpc->x_factor[4][1] = 0.00782,
        tpc->y_offset[4][0] = 56.4-1.5-2.0,
        tpc->y_offset[4][1] = 56.7-2.0-1.5,
        tpc->y_offset[4][2] = 56.5-0.3-2.0,
        tpc->y_offset[4][3] = 56.3-0.3-2.0,
        tpc->y_factor[4][0] = -0.004,
        tpc->y_factor[4][1] = -0.004,
        tpc->y_factor[4][2] = -0.004,
        tpc->y_factor[4][3] = -0.004,

        //-------- TPC42 parameters (BARB 2021 Feb 15)--------------
        // TPC 6 at S4 (TPC 42) in air
        tpc->id_tpc_timeref[5] = 1, //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
        tpc->lim_dt[5][0][0] = 2000.,  tpc->lim_dt[5][0][1] = 48000.0, //A11 drift time TDC cut
        tpc->lim_dt[5][1][0] = 2000.,  tpc->lim_dt[5][1][1] = 48000.0, //A12 drift time TDC cut
        tpc->lim_dt[5][2][0] = 2000.,  tpc->lim_dt[5][2][1] = 48000.0, //A21 drift time TDC cut
        tpc->lim_dt[5][3][0] = 2000.,  tpc->lim_dt[5][3][1] = 48000.0, //A22 drift time TDC cut
        tpc->lim_lt[5][0][0] = 2000.,  tpc->lim_lt[5][0][1] = 48000.0, //DL1 time TDC cut
        tpc->lim_rt[5][0][0] = 2000.,  tpc->lim_rt[5][0][1] = 48000.0, //DR1 time TDC cut
        tpc->lim_lt[5][1][0] = 2000.,  tpc->lim_lt[5][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_rt[5][1][0] = 2000.,  tpc->lim_rt[5][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_csum1[5][0] = 13500.0,    tpc->lim_csum1[5][1] = 15500.0,
        tpc->lim_csum2[5][0] = 13500.0,    tpc->lim_csum2[5][1] = 15500.0,
        tpc->lim_csum3[5][0] = 13500.0,    tpc->lim_csum3[5][1] = 15500.0,
        tpc->lim_csum4[5][0] = 13500.0,    tpc->lim_csum4[5][1] = 15500.0,
        tpc->x_offset[5][0] = 2.0+1.2-1.0,
        tpc->x_offset[5][1] = 1.7+0.51-1.0,
        tpc->x_factor[5][0] = 0.0077,
        tpc->x_factor[5][1] = 0.0078,
        tpc->y_offset[5][0] = 56.5-1.5-1.0,
        tpc->y_offset[5][1] = 57.3-1.5-1.0,
        tpc->y_offset[5][2] = 56.8-2.6-1.0,
        tpc->y_offset[5][3] = 56.4-2.6-1.0,
        tpc->y_factor[5][0] = -0.004,
        tpc->y_factor[5][1] = -0.004,
        tpc->y_factor[5][2] = -0.004,
        tpc->y_factor[5][3] = -0.004,


        //TPC at S3 (TPC 31)
        tpc->id_tpc_timeref[6] = 3, //(0:accepttrig, 1:sc21, 2:sc22, 3:sc31, 4:sc41)
        tpc->lim_dt[6][0][0] = 2000.,  tpc->lim_dt[6][0][1] = 48000.0, //A11 drift time TDC cut
        tpc->lim_dt[6][1][0] = 2000.,  tpc->lim_dt[6][1][1] = 48000.0, //A12 drift time TDC cut
        tpc->lim_dt[6][2][0] = 2000.,  tpc->lim_dt[6][2][1] = 48000.0, //A21 drift time TDC cut
        tpc->lim_dt[6][3][0] = 2000.,  tpc->lim_dt[6][3][1] = 48000.0, //A22 drift time TDC cut
        tpc->lim_lt[6][0][0] = 2000.,  tpc->lim_lt[6][0][1] = 48000.0, //DL1 time TDC cut
        tpc->lim_rt[6][0][0] = 2000.,  tpc->lim_rt[6][0][1] = 48000.0, //DR1 time TDC cut
        tpc->lim_lt[6][1][0] = 2000.,  tpc->lim_lt[6][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_rt[6][1][0] = 2000.,  tpc->lim_rt[6][1][1] = 48000.0, //DL2 time TDC cut
        tpc->lim_csum1[6][0] = 10000.0,    tpc->lim_csum1[6][1] = 20000.0,
        tpc->lim_csum2[6][0] = 10000.0,    tpc->lim_csum2[6][1] = 20000.0,
        tpc->lim_csum3[6][0] = 10000.0,    tpc->lim_csum3[6][1] = 20000.0,
        tpc->lim_csum4[6][0] = 10000.0,    tpc->lim_csum4[6][1] = 20000.0,
        tpc->x_offset[6][0] = -0.9,
        tpc->x_offset[6][1] = -3.4,
        tpc->x_factor[6][0] = 0.0088,
        tpc->x_factor[6][1] = 0.0088,
        tpc->y_offset[6][0] = -55.2,
        tpc->y_offset[6][1] = -57.3,
        tpc->y_offset[6][2] = -54.0,
        tpc->y_offset[6][3] = -53.7,
        tpc->y_factor[6][0] = 0.004,
        tpc->y_factor[6][1] = 0.004,
        tpc->y_factor[6][2] = 0.004,
        tpc->y_factor[6][3] = 0.004,


        //TPC21 ADC pedestal
        tpc->a_offset[0][0] = 999.,
        tpc->a_offset[0][1] = 999.,
        tpc->a_offset[0][2] = 999.,
        tpc->a_offset[0][3] = 999.,
        //TPC22 ADC pedestal
        tpc->a_offset[1][0] = 999.,
        tpc->a_offset[1][1] = 999.,
        tpc->a_offset[1][2] = 999.,
        tpc->a_offset[1][3] = 999.,
        //TPC23 ADC pedestal
        tpc->a_offset[2][0] = 104., //set large number to exclude (pedestal data) of this tpc
        tpc->a_offset[2][1] = 107.,
        tpc->a_offset[2][2] = 106.,
        tpc->a_offset[2][3] =  91.,
        //TPC24 ADC pedestal
        tpc->a_offset[3][0] = 107.,
        tpc->a_offset[3][1] = 117.,
        tpc->a_offset[3][2] = 123.,
        tpc->a_offset[3][3] =  81.,
    };
   
    static TSCIParameter* sci = new TSCIParameter
    {
        //index 2 for Sc21
        sci->x_a[0][2] =    477.29,  // quickly done for s452 on 08.03.2021 (from online)
        sci->x_a[1][2] =   -0.2619,  // quickly done for s452 on 08.03.2021 (from online)
        sci->x_a[2][2] =  0.000000,  //
        sci->x_a[3][2] =  0.000000,  //
        sci->x_a[4][2] =  0.000000,  //
        sci->x_a[5][2] =  0.000000,  //
        sci->x_a[6][2] =  0.000000,  //
        
        //index 3 for Sc22
      // sci->x_a[0][3] =  1370,  //quickly done with run 0139
      // sci->x_a[1][3] =  -0.7,  //
        sci->x_a[0][3] =  627.52,  // quickly done for s452 on 08.03.2021 (from online)
        sci->x_a[1][3] = -0.3751,  //quickly done for s452 on 08.03.2021 (from online)
        sci->x_a[2][3] =  0.0000,  //
        sci->x_a[3][3] =  0.000000,  //
        sci->x_a[4][3] =  0.000000,  //
        sci->x_a[5][3] =  0.000000,  //
        sci->x_a[6][3] =  0.000000,  //

        // index 5 for Sc41
        sci->x_a[0][5] = 641.56,  //  quickly done for s452 on 08.03.2021 (from online)
        sci->x_a[1][5] = -0.2782,  // quickly done for s452 on 08.03.2021 (from online)
        sci->x_a[2][5] = 0.0000,   //
        sci->x_a[3][5] = 0.000000,   //
        sci->x_a[4][5] = 0.000000,   //
        sci->x_a[5][5] = 0.000000,   //
        sci->x_a[6][5] = 0.000000,   //

        // index 6 for Sc42
        sci->x_a[0][6] = 559.44,  // quickly done for s452 on 08.03.2021 (from online)
        sci->x_a[1][6] = -0.2973, // quickly done for s452 on 08.03.2021 (from online)
        sci->x_a[2][6] = 0.000000,  //
        sci->x_a[3][6] = 0.000000,  //
        sci->x_a[4][6] = 0.000000,  //
        sci->x_a[5][6] = 0.000000,  //
        sci->x_a[6][6] = 0.000000,  //

        // index 7 for Sc43
        sci->x_a[0][7] = 0., //   SC43 calibration ch->mm
        sci->x_a[1][7] = 1., //
        sci->x_a[2][7] = 0.000000,  //
        sci->x_a[3][7] = 0.000000,  //
        sci->x_a[4][7] = 0.000000,  //
        sci->x_a[5][7] = 0.000000,  //
        sci->x_a[6][7] = 0.000000,  //

        // index 10 for Sc81
        sci->x_a[0][10] = 707.306,   // 2020/feb/20 run0110,0111,0112.lmd
        sci->x_a[1][10] =-0.45558,   // 
        sci->x_a[2][10] = 0.000000,  //
        sci->x_a[3][10] = 0.000000,  //
        sci->x_a[4][10] = 0.000000,  //
        sci->x_a[5][10] = 0.000000,  //
        sci->x_a[6][10] = 0.000000,  //
        sci->le_a[0][10] = 310.0, //21/feb/2020
        sci->re_a[0][10] = 123.0,

        // For TAC calibration, please only set "factor".
        // To put some "magic number" offset is very confusing!!
        // TOF calibration should be done via setting id->id_tofoff2(3)(4)
        sci->tac_off[0] = 0.0,  //SC21L-R    // fix to 0
        sci->tac_off[1] = 0.0,  //SC41L-R    // fix to 0
        sci->tac_off[2] = 0.0,  //SC41L-SC21L   // fix to 0
        sci->tac_off[3] = 0.0,  //SC41R-SC21R   // fix to 0
        sci->tac_off[4] = 0.0,  //SC42L-R       // fix to 0
        sci->tac_off[5] = 0.0,  //SC42L-SC21L   // fix to 0
        sci->tac_off[6] = 0.0,  //SC42R-SC21R   // fix to 0
        sci->tac_off[7] = 0.0,  //SC43L-R  // fix to 0
        sci->tac_off[8] = 0.0,  //SC81L-R  // fix to 0
        sci->tac_off[9] = 0.0,  //SC81L-SC21L  // fix to 0
        sci->tac_off[10]= 0.0,  //SC81R-SC21R  // fix to 0
        sci->tac_off[11] = 0.0,  //SC22L-R  // fix to 0
        sci->tac_off[12] = 0.0,  //SC41L-SC22L  // fix to 0
        sci->tac_off[13] = 0.0,  //SC41R-SC22R  // fix to 0
        sci->tac_off[14]= 0.0,  //SC81L-SC22L  // fix to 0
        sci->tac_off[15]= 0.0,  //SC81R-SC22R  // fix to 0

        //Offset found from fitting (Commented at this moment, 20-02-2020)
        /*
        sci->tac_off[0]  = 1299.5,  //SC21L-R    // fix to 0
        sci->tac_off[1]  = 1032.4,  //SC41L-R    // fix to 0
        sci->tac_off[2]  = 1295.6,  //SC41L-SC21L   // fix to 0
        sci->tac_off[3]  = 1150.,  //SC41R-SC21R   // fix to 0
        sci->tac_off[4]  = 1101.8,  //SC42L-R       // fix to 0
        sci->tac_off[5]  = 1354.8.,  //SC42L-SC21L   // fix to 0
        sci->tac_off[6]  = 1261.,  //SC42R-SC21R   // fix to 0
        sci->tac_off[7]  = 1276.4,  //SC43L-R  // fix to 0
        sci->tac_off[8]  = 930.5,  //SC81L-R  // fix to 0
        sci->tac_off[9]  = 1476.5,  //SC81L-SC21L  // fix to 0
        sci->tac_off[10] = 2731.3,  //SC81R-SC21R  // fix to 0
        sci->tac_off[11] = 1810.4,  //SC22L-R  // fix to 0
        sci->tac_off[12] = 1268.4,  //SC41L-SC22L  // fix to 0
        sci->tac_off[13] = 1326.2,  //SC41R-SC22R  // fix to 0
        sci->tac_off[14] =  2152.6,  //SC81L-SC22L  // fix to 0
        sci->tac_off[15] = 2040.3,  //SC81R-SC22R  // fix to 0
        */
        //2021/Feb/BARB 
        sci->tac_factor[0]  = 10.5293, //SC21L-R [ps/ch]     >> ch0 of ADC
        sci->tac_factor[1]  = 10.6934, //SC41L-R [ps/ch]     >> ch1 of ADC
        //sci->tac_factor[2]  = 43.6914, //SC41L-SC21L [ps/ch] >> ch5 of ADC
        // sci->tac_factor[3]  = 43.3264, //SC41R-SC21R [ps/ch] >> ch6 of ADC
        sci->tac_factor[4]  = 10.5367, //SC42L-R             >> ch2 of ADC
        //sci->tac_factor[5]  = 42.3307, //SC42L-SC21L [ps/ch] >> ch8 of ADC
        //sci->tac_factor[6]  = 41.6716, //SC42R-SC21R [ps/ch] >> ch7 of ADC
        sci->tac_factor[7]  = 11.0166, //SC43L-R [ps/ch]     >> ch3 of ADC
        sci->tac_factor[8]  = 10.5001, //SC81L-R [ps/ch]     >> ch4 of ADC
        sci->tac_factor[9]  = 20.7879, //SC81L-SC21L         >> ch9
        sci->tac_factor[10] = 19.9815, //SC81R-SC21R         >> ch10
        sci->tac_factor[11] = 10.5536, //SC22L-R             >> ch11
        //sci->tac_factor[12] = 39.9969, //SC41L-SC22L [ps/ch] >> ch12
        //sci->tac_factor[13] = 42.3244, //SC41R-SC22R [ps/ch] >> ch13
        sci->tac_factor[14] = 20.0000, //SC81L-SC22L [ps/ch] >> ch14
        sci->tac_factor[15] = 20.0000, //SC81R-SC22R [ps/ch] >> ch15

        //Interaction cross secton 1.Mar.2021 
        sci->tac_factor[2]  = 11.35, //SC41L-SC21L [ps/ch] >> ch5 of ADC   
        sci->tac_factor[3]  = 11.19, //SC41R-SC21R [ps/ch] >> ch6 of ADC
        sci->tac_factor[12] = 10.17, //SC41L-SC22L [ps/ch] >> ch12
        sci->tac_factor[13] = 10.78, //SC41R-SC22R [ps/ch] >> ch13
        sci->tac_factor[5]  = 10.84, //SC42L-SC21L [ps/ch] >> ch8 of ADC
        sci->tac_factor[6]  = 10.8, //SC42R-SC21R [ps/ch] >> ch7 of ADC

        
        sci->tof_bll2  = 1.,    // not used online [ps/ch]
        sci->tof_brr2  = 1.,    // not used online
        sci->tof_bll3  = 1.,    // not used online
        sci->tof_brr3  = 1.,    // not used online
        sci->tof_bll4  = 1.,    // not used online
        sci->tof_brr4  = 1.,    // not used online

        sci->tof_a2 = 146.46, // [ps] offset   Tof S41-S21
        sci->tof_a3 = 0., // [ps] offset   Tof S42-S21
        sci->tof_a4 = 0., // [ps] offset   Tof S81-S21

        // for multihitTDC
        sci->mhtdc_factor_ch_to_ns =  0.025,// tp be set in parameter...
        sci->mhtdc_offset_21l_21r  =  -39.6625+20.0,    sci->mhtdc_factor_21l_21r = 62.5341,  // pos = offset + factor*dt
        sci->mhtdc_offset_41l_41r  =  584.927,          sci->mhtdc_factor_41l_41r = 69.4128, // pos = offset + factor*dt
        sci->mhtdc_offset_42l_42r  =  0.0,              sci->mhtdc_factor_42l_42r = 60.0, // pos = offset + factor*dt
        sci->mhtdc_offset_43l_43r  =  0.0,              sci->mhtdc_factor_43l_43r = 60.0, // pos = offset + factor*dt
        sci->mhtdc_offset_31l_31r  =  0.0,              sci->mhtdc_factor_31l_31r = 60.0, // pos = offset + factor*dt
        sci->mhtdc_offset_81l_81r  =  -410.411,         sci->mhtdc_factor_81l_81r = 43.691, // pos = offset + factor*dt
        sci->mhtdc_offset_22l_22r  =  -39.6625+20.0,    sci->mhtdc_factor_22l_22r = 62.5341,  // pos = offset + factor*dt
        sci->mhtdc_offset_41_21  =  173.82, //ns // s452 Pb E.S.
        sci->mhtdc_offset_42_21  =  163.79, //ns // s452 Pb 210311
        sci->mhtdc_offset_43_21  =  0.0, //ns
        sci->mhtdc_offset_31_21  =  0.0, //ns
        sci->mhtdc_offset_81_21  =  -400.0 + 165.214, //ns
        sci->mhtdc_offset_41_22  =  266.9, //ns // s452 Pb 210311
    };
  
}