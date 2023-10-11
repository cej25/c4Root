//#include "frs_parameter.hh"

TMWParameter::TMWParameter()
{
    for (int i=0;i<13;i++) 
    {
        x_factor[i] = 0.1;
        x_offset[i] = 0.;
        y_factor[i] = 0.1;
        y_offset[i] = 0.;
    }
    
    for(int i=0;i<5;i++)
    {
       for(int j=0;j<13;j++)
       {
            gain_tdc[i][j] = 0.; 
       }
    }
        
}

TMWParameter::TMWParameter(const char* name)
{
    x_factor[0] = 0.25, // MW11 [mm/ns] some old value
    x_factor[1] = 0.25, // MW21
    x_factor[2] = 0.25, // MW22
    x_factor[3] = 0.25, // MW31
    x_factor[4] = 0.25, // MW51
    x_factor[5] = 0.25, // MW71
    x_factor[6] = 0.25, // MW81
    x_factor[7] = 0.125, // MW82

    x_offset[0] = 5.0, // MW11 Feb 2014
    x_offset[1] = -2.0, // MW21 Feb 2014
    x_offset[2] = -1.5, // MW22 Feb 2014
    x_offset[3] = 5.0, // MW31 like MW11 15.11.19
    x_offset[4] = -0.205, // MW51
    x_offset[5] = 1.642, // MW71 //15/05/06
    x_offset[6] = 1.,   // MW81 //11/05/06
    x_offset[7] = -5., // MW82 //27-MAY-2007

    y_factor[0] = 0.25, // MW11 [mm/ns] 14.09.05 CN+AM 2ns/mm delay line
    y_factor[1] = 0.25, // MW21
    y_factor[2] = 0.25, // MW22
    y_factor[3] = 0.25, // MW31
    y_factor[4] = 0.25, // MW51
    y_factor[5] = 0.25, // MW71
    y_factor[6] = 0.25, // MW81
    y_factor[7] = 0.125, // MW82  [mm/ns] 11.05.06  CN 4ns/mm delay line

    y_offset[0] = -14.0,  // MW11 27-MAY-2007 TESTED VALUE WITH SLITS, ok Feb 2014
    y_offset[1] = 21.0,   // Feb 2014
    y_offset[2] = -1.0,   // MW22 27-MAY-2007 TESTED VALUE WITH SLITS, ok Feb 2014
    y_offset[3] = -14.0,    // MW31 like in MW11 15.11.19
    y_offset[4] = 0.0,     //MW51  ???????
    y_offset[5] = -2.736,  // MW71 //15/05/06
    y_offset[6] = 3.2,     // MW81 //11/05/06
    y_offset[7] = 0.764,  // MW82 //11/05/06

    gain_tdc[0][0] = 0.302929, //  MW11 Anode (#ch  0 TDC V775a) // 13.01.2008
    gain_tdc[1][0] = 0.303253, //  MW11 XL    (#ch 17 TDC V775a)
    gain_tdc[2][0] = 0.303975, //  MW11 XR    (#ch 16 TDC V775a)
    gain_tdc[3][0] = 0.308414, //  MW11 YU    (#ch 18 TDC V775a)
    gain_tdc[4][0] = 0.309826, //  MW11 YD    (#ch 19 TDC V775a)

    gain_tdc[0][1] = 0.306064, //  MW21 Anode (#ch  1 TDC V775a) // 13.01.2008
    gain_tdc[1][1] = 0.306958, //  MW21 XL    (#ch 21 TDC V775a)
    gain_tdc[2][1] = 0.307799, //  MW21 XR    (#ch 20 TDC V775a)
    gain_tdc[3][1] = 0.297774, //  MW21 YU    (#ch 22 TDC V775a)
    gain_tdc[4][1] = 0.310235, //  MW21 YD    (#ch 23 TDC V775a)

    gain_tdc[0][2] = 0.301179,  // MW22 Anode (#ch  2 TDC V775a) // 13.01.2008
    gain_tdc[1][2] = 0.311121, //  MW22 XL    (#ch 25 TDC V775a)
    gain_tdc[2][2] = 0.303233, //  MW22 XR    (#ch 24 TDC V775a)
    gain_tdc[3][2] = 0.300558, //  MW22 YU    (#ch 26 TDC V775a)
    gain_tdc[4][2] = 0.301105, //  MW22 YD    (#ch 27 TDC V775a)

    gain_tdc[0][3] = 0.304426, //  MW31 Anode (#ch  3 TDC V775a) // 13.01.2008
    gain_tdc[1][3] = 0.312163, //  MW31 XL    (#ch 29 TDC V775a)
    gain_tdc[2][3] = 0.305609, //  MW31 XR    (#ch 28 TDC V775a)
    gain_tdc[3][3] = 0.304716, //  MW31 YU    (#ch 30 TDC V775a)
    gain_tdc[4][3] = 0.293695, //  MW31 YD    (#ch 31 TDC V775a)

    gain_tdc[0][4] = 0.298871, //  MW41 Anode (#ch  4 TDC V775a) // 13.01.2008
    gain_tdc[1][4] = 0.284086, //  MW41 XL    (#ch 1 TDC V775b)
    gain_tdc[2][4] = 0.288656, //  MW41 XR    (#ch 0 TDC V775b)
    gain_tdc[3][4] = 0.286589, //  MW41 YU    (#ch 2 TDC V775b)
    gain_tdc[4][4] = 0.29269,  //  MW41 YD    (#ch 3 TDC V775b)

    gain_tdc[0][5] = 0.297881, //  MW42 Anode (#ch  5 TDC V775a) // 13.01.2008
    gain_tdc[1][5] = 0.287364, //  MW42 XL    (#ch 5 TDC V775b)
    gain_tdc[2][5] = 0.289636, //  MW42 XR    (#ch 4 TDC V775b)
    gain_tdc[3][5] = 0.291135, //  MW42 YU    (#ch 6 TDC V775b)
    gain_tdc[4][5] = 0.289867, //  MW42 YD    (#ch 7 TDC V775b)

    gain_tdc[0][6] = 0.307892, //  MW51 Anode (#ch  6 TDC V775a) // 13.01.2008
    gain_tdc[1][6] = 0.289894, //  MW51 XL    (#ch  9 TDC V775b)
    gain_tdc[2][6] = 0.292366, //  MW51 XR    (#ch  8 TDC V775b)
    gain_tdc[3][6] = 0.284708, //  MW51 YU    (#ch 10 TDC V775b)
    gain_tdc[4][6] = 0.28186,  //  MW51 YD    (#ch 11 TDC V775b)

    gain_tdc[0][7] = 0.298266, //  MW61 Anode (#ch  7 TDC V775a) // 13.01.2008
    gain_tdc[1][7] = 0.311, //  MW61 XL    (#ch ? TDC V775b)
    gain_tdc[2][7] = 0.305, //  MW61 XR    (#ch ? TDC V775b)
    gain_tdc[3][7] = 0.337, //  MW61 YU    (#ch ? TDC V775b)
    gain_tdc[4][7] = 0.289, //  MW61 YD    (#ch ? TDC V775b)

    gain_tdc[0][8] = 0.303602, //  MW71 Anode (#ch  8 TDC V775a) // 13.01.2008
    gain_tdc[1][8] = 0.300082, //  MW71 XL    (#ch 13 TDC V775b)
    gain_tdc[2][8] = 0.286092, //  MW71 XR    (#ch 12 TDC V775b)
    gain_tdc[3][8] = 0.294287, //  MW71 YU    (#ch 14 TDC V775b)
    gain_tdc[4][8] = 0.291341, //  MW71 YD    (#ch 15 TDC V775b)

    gain_tdc[0][9] = 0.306041, //  MW81 Anode (#ch  9 TDC V775a) // 13.01.2008
    gain_tdc[1][9] = 0.288468, //  MW81 XL    (#ch 17 TDC V775b)
    gain_tdc[2][9] = 0.293831, //  MW81 XR    (#ch 16 TDC V775b)
    gain_tdc[3][9] = 0.281296, //  MW81 YU    (#ch 18 TDC V775b)
    gain_tdc[4][9] = 0.279099, //  MW81 YD    (#ch 19 TDC V775b)

    gain_tdc[0][10] = 0.31314,  //  MW82 Anode (#ch 10 TDC V775a) // 13.01.2008
    gain_tdc[1][10] = 0.287279, //  MW82 XL    (#ch 21 TDC V775b)
    gain_tdc[2][10] = 0.284028, //  MW82 XR    (#ch 20 TDC V775b)
    gain_tdc[3][10] = 0.28051,  //  MW82 YU    (#ch 22 TDC V775b)
    gain_tdc[4][10] = 0.28743,  //  MW82 YD    (#ch 23 TDC V775b)

    gain_tdc[0][11] = 0.299973, //  MWB21 Anode (#ch 11 TDC V775a) // 13.01.2008
    gain_tdc[1][11] = 0.311, //  MWB21 XL    (#ch ? TDC V775b)
    gain_tdc[2][11] = 0.305, //  MWB21 XR    (#ch ? TDC V775b)
    gain_tdc[3][11] = 0.337, //  MWB21 YU    (#ch ? TDC V775b)
    gain_tdc[4][11] = 0.289, //  MWB21 YD    (#ch ? TDC V775b)

    gain_tdc[0][12] = 0.306923, //  MWB22 Anode (#ch 12 TDC V775a) // 13.01.2008
    gain_tdc[1][12] = 0.311, //  MWB22 XL    (#ch ? TDC V775b)
    gain_tdc[2][12] = 0.305, //  MWB22 XR    (#ch ? TDC V775b)
    gain_tdc[3][12] = 0.337, //  MWB22 YU    (#ch ? TDC V775b)
    gain_tdc[4][12] = 0.289, //  MWB22 YD    (#ch ? TDC V775b)    
}

TMWParameter::~TMWParameter()
{
}


TFRSParameter::TFRSParameter()
{
    //S2
    dist_focS2 = 0;
    dist_MW21 = 0; 
    dist_MW22 = 0;
    dist_SC21 = 0;
    dist_SC22 = 0;
    dist_TPC21 = 0;
    dist_TPC22 = 0;
    dist_TPC23 = 0;
    dist_TPC24 = 0;
    dist_S2target = 0;
    
    //S4
    dist_focS4 = 0;
    dist_SC41 = 0;
    dist_SC42 = 0;
    dist_SC43 = 0;
    dist_MUSIC41 = 0;
    dist_MUSIC42 = 0;
    dist_MUSIC43 = 0;
    dist_TPC41 = 0;
    dist_TPC42 = 0;
    dist_S4target = 0;
    //S8
    dist_focS8 = 0;
    dist_MW81 = 0;
    dist_MW82 = 0;
    dist_SC81 = 0;
    
    //filed
    for(int i=0;i<7;i++) 
    {
        dispersion[i] = 0.;  
        rho0[i] = 0.;  
        bfield[i] = 0.;
        magnification[i] = 0.;
    }
    
    primary_z = 0.;
}

TFRSParameter::TFRSParameter(const char* name)
{    
    //S2
    //  frs->dist_focS2 = 2012.5, // degrader disk position stabdard
    dist_focS2 = 3300.0, // low-dispersion S2-S4
    dist_MW21  =  604.0,
    dist_MW22  = 1782.5,
    dist_SC21  = 1554.5,
    dist_SC22  = 2595.0, //BARB 2021 Feb Logbook  
    dist_TPC21 =  604.0,
    dist_TPC22 = 1782.5,
    dist_TPC23 = 2915.0, //BARB 2021 Feb Logbook  
    dist_TPC24 = 3980.0, //BARB 2021 Feb Logbook
    dist_S2target = 3600.0, // Interaction Cross section (01.March 2021)

    //S4
    //  frs->dist_focS4   = 3100.0, //BARB 2021 Feb   ... std
    //frs->dist_focS4   = 2200.0, //S2S4 low dispersion mode
    dist_SC41    = 2245.0,
    dist_SC42    = 2620.0,
    dist_SC43    = 4706.0,
    dist_MUSIC41 = 735.0,
    dist_MUSIC42 = 1215.0,
    dist_MUSIC43 = 5013.0,
    dist_TPC41   =  415.0,
    //  frs->dist_TPC42   = 1535.0, moved to avoid conflict. before 2020april run.
    dist_TPC42 = 1528.0, //for s468. 2020 april 
    dist_S4target= 4000.0, //for some experiments

    //S8
    dist_focS8 = 0,
    dist_MW81 = 0,
    dist_MW82 = 0,
    dist_SC81 = 0,

    rho0[0]   = 1., //TA-S2
    rho0[1]   = 1., //S2-S4
    rho0[2]   = 1., //S4-S8
    rho0[3]   = 0.,
    rho0[4]   = 0.,
    rho0[5]   = 0.,
    rho0[6]   = 0.,
    dispersion[0]    = -6.474266,// RUN81-TA2B-220CM 27.05.2016
    dispersion[1]    =  7.670,  // RUN81-TA2B-220CM 27.05.2016
    magnification[1] =  1.18,   // RUN81-TA2B-220CM 27.05.2016
    dispersion[2]    = 12.397,   //S2-S8 (gicosy sign definition)
    magnification[2] =  1.829,   //S2-S8

    bfield[0] = 13.3474,//                 Please do NOT comment-out old brho and add new brho. Please make a NEW setup file. 
    bfield[1] = 12.5166,//                 Please do NOT comment-out old brho and add new brho. Please make a NEW setup file. 
    bfield[2] = 10.5376, //                 Please do NOT comment-out old brho and add new brho. Please make a NEW setup file. 
    bfield[3] = 10.5376, //                 Please do NOT comment-out old brho and add new brho. Please make a NEW setup file. 
    bfield[4] = 99.999, // D5 (to ESR) not used
    bfield[5] = 99.999, // D6 (to S8)

    primary_z = 82.,

    
}

TFRSParameter::~TFRSParameter()
{
}


TTPCParameter::TTPCParameter()
{
}

TTPCParameter::TTPCParameter(const char* name)
{
}

TTPCParameter::~TTPCParameter()
{
}