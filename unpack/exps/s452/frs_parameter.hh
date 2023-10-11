// a lot of floats became doubles, but oh well

class TMWParameter
{
    public:

        /*TMWParameter();
        TMWParameter(const char* name); // initialise
        virtual ~TMWParameter();*/

        double x_factor[13];
        double x_offset[13];
        double y_factor[13];
        double y_offset[13];

        double gain_tdc[5][13];

};

class TFRSParameter
{
    public:

        /*
        TFRSParameter();
        TFRSParameter(const char* name); // initialise
        virtual ~TFRSParameter();*/

        double rho0[7];         /* S2/4 Sollbahnradius s */
        double primary_z;       /* Z of primary beam     */
        double bfield[7];       /* D1/D2 D3/D4 Feld      */
        double dispersion[7];   /* d* Disp. S0-S2,S2-S4  */
        double magnification[7];
        //S2
        //  frs->dist_focS2 = 2012.5; // degrader disk position stabdard
        double dist_focS2; // low-dispersion S2-S4
        double dist_MW21;
        double dist_MW22;
        double dist_SC21;
        double dist_SC22;  
        double dist_TPC21;
        double dist_TPC22;
        double dist_TPC23;
        double dist_TPC24;
        double dist_S2target;

        /*    distanes  S4      */
        double dist_focS4;      /* All distances from    */
        double dist_SC41;       /*        in mm          */
        double dist_SC42;       /*        in mm          */
        double dist_SC43;       /*        in mm          */
        double dist_TPC41;
        double dist_TPC42;
        double dist_MUSIC41;     /*  MUSIC1               */
        double dist_MUSIC42;     /*  MUSIC2               */
        double dist_MUSIC43;     /*  MUSIC3               */
        double dist_S4target;

        double dist_focS8;
        double dist_MW81;
        double dist_MW82;
        double dist_SC81;
         
};

class TTPCParameter
{
    public:

        /*
        TTPCParameter();
        TTPCParameter(const char* name); // initialise
        virtual ~TTPCParameter();*/

        double x_factor[7][2];     /* [mm/ch]                  */
        double x_offset[7][2];     /*                          */
        double y_factor[7][4];     /* [mm/ch]                  */
        double y_offset[7][4];     /*                          */

        double a_offset[7][4];
        double tdc1_factor[32];
        double tdc2_factor[32];

        int id_tpc_timeref[7];
        double timeref_calibrun[7];

        double lim_csum1[7][2];
        double lim_csum2[7][2];
        double lim_csum3[7][2];
        double lim_csum4[7][2];
  
        double lim_dt[7][4][2];
        double lim_lt[7][2][2];
        double lim_rt[7][2][2];
        double lim_timeref[8][2];   
};

class TMUSICParameter
{
    public:
        
        /*
        TMUSICParameter();
        TMUSICParameter(const char* name); // initialise
        virtual ~TMUSICParameter();*/

        int e1_off[8]; /* ADC offsets              */
        double e1_gain[8]; /* ADC gains                */
        int e2_off[8]; /* ADC offsets              */
        double e2_gain[8];      /* ADC gains                */
        int e3_off[8];       /* ADC offsets              */
        double e3_gain[8];      /* ADC gains                */
        bool b_selfcorr1;     /* 1 => Music1 x correction */
        double pos_a1[7];       /* pos. corr. de(i) ->  MUSIC41 */
        double pos_a2[7];       /* pos. corr. de(i) ->  MUSIC42 */
        double pos_a3[7];       /* pos. corr. de(i) ->  MUSIC43 */
        double dist_MUSICa1;    /*  MUSIC(window-anode1) */
        double dist_MUSICa2;    /*  MUSIC(window-anode2) */
        double dist_MUSICa3;    /*  MUSIC(window-anode3) */
        double dist_MUSICa4;    /*  MUSIC(window-anode4) */

        // MUSIC histogram setup
        int max_adc_music1;
        int max_adc_music2;
        int max_adc_music3;
        int max_tdc_music1;
        int max_tdc_music2;
        int max_tdc_music3;
};

class TSCIParameter
{
    public:

        /*
        TSCIParameter();
        TSCIParameter(const char* name); // initialise
        virtual ~TSCIParameter();*/

        double le_a[2][12];     /* dE-left   shift,gain     */
        double re_a[2][12];     /* dE-right  shift,gain     */
        double le_veto_a[2][3]; /* veto dE-left  shift,gain */
        double re_veto_a[2][3]; /* veto dE-right shift,gain */

        double tac_factor[16];   /* TAC factor               */
        double tac_off[16];      /* TAC offset               */
        double x_a[7][12];      /* pos. corr. de(i) ->  (1) */
        double y5_a[7];         /* pos. corr. de(i) ->  (1) */

        double tof_bll2;        /* [ps/channel]             */
        double tof_brr2;        /* [ps/channel]             */
        double tof_a2;          /* shift [channels]         */
        double tof_bll3;        /* [ps/channel]             */
        double tof_brr3;        /* [ps/channel]             */
        double tof_a3;          /* shift [channels]         */
        double tof_bll4;        /* [ps/channel]             */
        double tof_brr4;        /* [ps/channel]             */
        double tof_a4;          /* shift [channels]         */
        double tof_bll5;        /* [ps/channel]             */
        double tof_brr5;        /* [ps/channel]             */
        double tof_a5;          /* shift [channels]         */
        double tof_bll6;        /* [ps/channel]             */
        double tof_brr6;        /* [ps/channel]             */
        double tof_a6;          /* shift [channels]         */

        //-----for multihit TDC analysis------
        double mhtdc_factor_ch_to_ns;
        double mhtdc_offset_21l_21r;  double mhtdc_factor_21l_21r ;
        double mhtdc_offset_41l_41r;  double mhtdc_factor_41l_41r ;
        double mhtdc_offset_42l_42r;  double mhtdc_factor_42l_42r ;
        double mhtdc_offset_43l_43r;  double mhtdc_factor_43l_43r ;
        double mhtdc_offset_31l_31r;  double mhtdc_factor_31l_31r ;
        double mhtdc_offset_81l_81r;  double mhtdc_factor_81l_81r ;
        double mhtdc_offset_22l_22r;  double mhtdc_factor_22l_22r;
        double mhtdc_offset_41_21;
        double mhtdc_offset_42_21;
        double mhtdc_offset_43_21;
        double mhtdc_offset_31_21;
        double mhtdc_offset_81_21;
        double mhtdc_offset_41_22;
        double mhtdc_offset_81_22;
};

class TIDParameter
{
    public:

        /*
        TIDParameter();
        TIDParameter(const char* name); // initialise
        virtual ~TIDParameter();*/

        int x_s2_select; //1=tpc,2=sc21,3=sc22
        int tof_s4_select; //1=sc21-41, 2=sc21-42, 3=sc22-41
        int tof_s8_select; //1=sc21-81, 2=sc22-81
  
        double id_tofoff2;      /* Tof offset S2-S4 [ps]    */
        double id_tofoff3;      /* Tof offset S2-S4 [ps]    */ //2nd tof from S2 - S4
        double id_tofoff4;      /* Tof offset S2-S8 [ps]    */
        double id_tofoff5;      /* Tof offset S2-S4 [ps]    */ //Plastic22
        double id_tofoff6;      /* Tof offset S2-S8 [ps]    */ //Plastic22
        double id_path2;        /* Flight path/c S2-S4 [ps] */
        double id_path3;        /* Flight path/c S2-S4 [ps] */ //2nd tof from S2 - S4
        double id_path4;        /* Flight path/c S2-S8 [ps] */
        double id_path5;        /* Flight path/c S2-S4 [ps] */ //Plastic22
        double id_path6;        /* Flight path/c S2-S8 [ps] */ //Plastic22
        double id_tofcorr2;     /* Tof correction for x4    */
        double id_tofcorr3;     /* Tof correction for x4    */ //2nd tof from S2 - S4
        double id_tofcorr4;     /* Tof correction for x8    */
        double id_tofcorr5;     /* Tof correction for x4    */ //Plastic 22
        double id_tofcorr6;     /* Tof correction for x8    */ //Plastic 22

        double offset_z;
        double offset_z2;
        double offset_z3;
        double offset_z_sc81;
        double offset_z_s2tpc;

        double a2AoQCorr;  /* Correction of AoQ based on S2 angle in x */
        double a4AoQCorr;  /* Correction of AoQ based on S4 angle in x */

        double vel_a[4];
        double vel_a2[4];
        double vel_a3[4];
        double vel_a_sc81[4];
        double vel_a_s2tpc[4];

        double pos_offset_sc81x;

        // id analysis with multihit tdc
        int mhtdc_s2pos_option;
        double mhtdc_length_s2s8;
        double mhtdc_vel_a_sc81[4];
        double mhtdc_vel_a_s2tpc[4];
        double mhtdc_offset_z_s2tpc;
        double mhtdc_offset_z_sc81;
        double mhtdc_length_s2s4;
        double mhtdc_vel_a_music41[4];
        double mhtdc_vel_a_music42[4];
        double mhtdc_offset_z_music41;
        double mhtdc_offset_z_music42;

        double min_aoq_plot;
        double max_aoq_plot;
        double min_z_plot;
        double max_z_plot;

        int   ID_Z_AoverQ_num[5];
        double ID_Z_AoverQ [5][5][2];

        int   ID_x2AoverQ_num[6];
        double ID_x2AoverQ [6][5][2];

        int   ID_x4AoverQ_num[6];
        double ID_x4AoverQ [6][5][2];

};

class TSIParameter
{
    public:

        /*
        TSIParameter();
        TSIParameter(const char* name); // initialise
        virtual ~TSIParameter();
        */

        double si_factor1;
        double si_factor2;
        double si_factor3;
        double si_factor4;
        double si_factor5;

        double si_offset1;
        double si_offset2;
        double si_offset3;
        double si_offset4;
        double si_offset5;

        //double dssd_offset[32];
        //double dssd_factor[32];

        double dssd_offset_det1[32];
        double dssd_factor_det1[32];

        double dssd_offset_det2[32];
        double dssd_factor_det2[32];

        double dssd_offset_det3[32];
        double dssd_factor_det3[32];

        double dssd_offset_det4[32];
        double dssd_factor_det4[32];

        double dssd_offset_det5[32];
        double dssd_factor_det5[32];

        double dssd_offset_det6[32];
        double dssd_factor_det6[32];
};

class TMRTOFMSParameter
{
    public:

        /*
        TMRTOFMSParameter();
        TMRTOFMSParameter(const char* name); // initialise
        virtual ~TMRTOFMSParameter();
        */

        double MRTOFMS_a;
        double MRTOFMS_b;
        double MRTOFMS_t0;
        double MRTOFMS_tFRS;
};
