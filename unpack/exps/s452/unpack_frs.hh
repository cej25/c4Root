#ifndef __FRS_UNPACK_HH__
#define __FRS_UNPACK_HH__

#include "config/setup.hh"
#include "frs_parameter.hh"

#include "data_src.hh"
#include "dummy_external.hh"
#include "external_data.hh"
//#include "zero_suppress.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <limits>
#include <vector>

DUMMY_EXTERNAL_MAP_STRUCT_FORW(EXT_FRS);

struct frs_item
{   

    // ****** UNPACK ******* //
    // tpat stuff
    bool skip;
    uint32 tpat_main[32];
    uint32 utpat; // ints before vv? // uint8?
    uint32 uphystrig;
    uint32 unbtrig;
    uint32 umaxtrig; // ^^

    // frs crate
    uint32 vme_frs[21][32];
    uint32 scaler_frs[32];
    // lets start here
    std::vector<int> scaler_frs_elements;
    uint32 vme_main[21][32];

    // tpc crate
    uint32 leading_v1190_tpcs2[128][64]; // TPC crate (S2 TPC)
    uint32 nhit_v1190_tpcs2[128];
    int tmp_nhit_prev;
    uint32 vme_tpcs2[21][32]; // TPC crate (S2 TPC)

    // vftx / tof crate
    uint32 vftx_cc[VFTX_N][VFTX_MAX_CHN][VFTX_MAX_HITS]; // maybe uint16 or uint8 works too
    uint32 vftx_ft[VFTX_N][VFTX_MAX_CHN][VFTX_MAX_HITS];
    uint32 vftx_mult[VFTX_N][VFTX_MAX_CHN];
    uint32 vme_tof[21][32]; // TOF crate

    // frs main
    uint32 nhit_v1290_main[32][2]; 
    uint32 leading_v1290_main[32][10]; 
    uint32 trailing_v1290_main[32][10];
    uint32 scaler_main[32];

    // ************************************************* //

    // ******** SORT ******** //
    // MAX_MHTDC instead of 10?
    int tdc_sc41l[10]; 
    int tdc_sc41r[10];
    int tdc_sc21l[10];
    int tdc_sc21r[10];
    int tdc_sc42l[10];
    int tdc_sc42r[10];
    int tdc_sc43l[10];
    int tdc_sc43r[10];
    int tdc_sc81l[10];
    int tdc_sc81r[10];
    int tdc_sc31l[10];
    int tdc_sc31r[10];
    int tdc_sc11[10];
    int tdc_sc22l[10];
    int tdc_sc22r[10];

    int tpc_dt[7][4][64];
    int tpc_lt[7][2][64];
    int tpc_rt[7][2][64];
    int tpc_nhit_dt[7][4];
    int tpc_nhit_lt[7][2];
    int tpc_nhit_rt[7][2];

    int tpc_l[7][2];
    int tpc_r[7][2];
    int tpc_a[7][4];

    int tpc_csum[7][4];

    int tpc_nhit_calibgrid[7];
    int tpc_nhit_timeref[8];
    int tpc_timeref[8][64];

    uint32 timestamp_lo;
    uint32 timestamp_hi;
    uint64 timestamp;
    uint32 timestamp_main[32]; // 64? wat
    uint32 ts_word[4]; // 64?
    int tsys_word[3];
    double timespill;
    double timespill2;
    int time_in_ms;
    int spill_count;
    int ibin_for_s;
    int ibin_for_100ms;
    int ibin_for_spill;
    int ibin_clean_for_s;
    int ibin_clean_for_100ms;
    int ibin_clean_for_spill;
    uint32 increase_scaler_temp[64];

    int extraction_time_ms;

    uint32 vme_tpcs4[21][32];

    float id_x2;
    float id_x4;
    float id_AoQ;
    float id_AoQ_corr;
    float id_dEdeg;
    float id_dEdegoQ;

    int music_e1[8];
    int music_e2[8];
    int music_e3[8];
    int music_t1[8];
    int music_t2[8];
    int music_t3[8];

    int dt_21l_21r;
    int dt_41l_41r;
    int dt_21l_41l;
    int dt_21r_41r;
    int dt_42l_42r;
    int dt_43l_43r;
    int dt_42l_21l;
    int dt_42r_21r;
    int dt_41u_41d;
    int dt_81l_81r;
    int dt_21l_81l;
    int dt_21r_81r;
    int dt_22l_22r;
    int dt_22l_41l;
    int dt_22r_41r; 
    int dt_22l_81l;
    int dt_22r_81r;

    int de_21l;
    int de_21r;
    int de_41l;
    int de_41r;
    int de_42l;
    int de_42r;
    int de_43l;
    int de_43r;
    int de_81l;
    int de_81r;
    int de_31l; 
    int de_31r;
    int de_22l;
    int de_22r;

    double TRaw_vftx_21l;
    double TRaw_vftx_21r;
    double TRaw_vftx_22l;
    double TRaw_vftx_22r;
    double TRaw_vftx_41l;
    double TRaw_vftx_41r;
    double TRaw_vftx_42l;
    double TRaw_vftx_42r;
    double TRaw_vftx[32];

    uint64 StartOfSpillTime; // spelled wrong in FRS
    uint64 StartOfSpillTime2; //does not reset at end of extraction
    int PreviousTS; // this can never be negative if uint64

    double systemtime_ms;
    double systemtime_s;

    int qtrigger;
    int trigger;
    int pattern;
    int sptrigger;
    int snbtrig;
    int smaxtrig;

    uint32 sc_long[64];
    uint32 sc_long2[64]; // UNUSED or i made a mistake? check

    int v1190_channel_dt[7][4];
    int v1190_channel_lt[7][2];
    int v1190_channel_rt[7][2];
    int v1190_channel_timeref[8];
    int v1190_channel_calibgrid[7];

    int tpc_calibgrid[7][64];

    uint32 vme_trmu_adc[16];
    uint32 vme_trmu_tdc[16];

    uint32 scaler_initial[64];
    uint32 scaler_previous[64];
    int scaler_ch_1kHz = 0;
    int scaler_ch_spillstart = 0;
    int scaler_check_first_event = 1;

    float mw_x[13];
    float mw_y[13];
    float mw_xsum[13];
    float mw_ysum[13];

    int mw_an[13];
    int mw_xl[13];
    int mw_xr[13];
    int mw_yu[13];
    int mw_yd[13];

    bool b_mw_xsum[13];
    bool b_mw_ysum[13];

    float lim_xsum[13][2];
    float lim_ysum[13][2];

    float angle_x_s2;
    float angle_x_s2m;
    float angle_y_s2;
    float angle_y_s2m;

    float focx_s2;
    float focx_s2m;
    float focy_s2;
    float focy_s2m;

    float mw_sc21_x;

    float mw_sc22_x;

    float z_x_s2;
    float z_y_s2;

    bool b_tpc_timeref[8];
    int tpc_timeref_s[8];

    float tpc_dx12[7];
    float tpc_x[7];
    float tpc_y[7];
    float tpc_de[7];

    bool b_tpc_xy[7];
    bool b_tpc_de[7];
    bool b_tpc_csum[7][4];
    
    int tpc_lt_s[7][2];
    int tpc_rt_s[7][2];
    int tpc_xraw[7][2];
    int tpc_dt_s[7][4];//selected from multihit
    int tpc_yraw[7][4];

    float tpc_x_s2_foc_21_22;
    float tpc_y_s2_foc_21_22;
    float tpc_angle_x_s2_foc_21_22;
    float tpc_angle_y_s2_foc_21_22;

    float tpc21_22_sc21_x;
    float tpc21_22_sc21_y;
    float tpc21_22_sc22_x;
    float tpc21_22_sc22_y;
    float tpc21_22_s2target_x;
    float tpc21_22_s2target_y;
    float tpc_angle_x_s2_foc_23_24;
    float tpc_angle_y_s2_foc_23_24;
    float tpc_x_s2_foc_23_24;
    float tpc_y_s2_foc_23_24;
    float tpc23_24_sc21_x;
    float tpc23_24_sc21_y;
    float tpc23_24_sc22_x;
    float tpc23_24_sc22_y;
    float tpc23_24_s2target_x;
    float tpc23_24_s2target_y;
    float tpc_angle_x_s2_foc_22_24;
    float tpc_angle_y_s2_foc_22_24;
    float tpc_x_s2_foc_22_24;
    float tpc_y_s2_foc_22_24;
    float tpc22_24_sc21_x;
    float tpc22_24_sc21_y;
    float tpc22_24_sc22_x;
    float tpc22_24_sc22_y;
    float tpc22_24_s2target_x;
    float tpc22_24_s2target_y;
    float tpc_angle_x_s4;
    float tpc_angle_y_s4;
    float tpc_x_s4;
    float tpc_y_s4;
    float tpc_sc41_x;
    float tpc_sc41_y;
    float tpc_sc42_x;
    float tpc_sc42_y;
    float tpc_sc43_x;
    float tpc_sc43_y;
    float tpc_music41_x;
    float tpc_music41_y;
    float tpc_music42_x;
    float tpc_music42_y;
    float tpc_music43_x;
    float tpc_music43_y;
    float tpc_s4target_x;
    float tpc_s4target_y;

    int music1_anodes_cnt;
    int music2_anodes_cnt;
    int music3_anodes_cnt;

    bool music_b_e1[8];
    bool music_b_e2[8];
    bool music_b_e3[8];
    bool music_b_t1[8];
    bool music_b_t2[8];
    bool music_b_t3[8];

    float cMusic1_E[8][2];
    float cMusic2_E[8][2];
    float cMusic3_E[4][2];
    float cMusic1_T[8][2];
    float cMusic2_T[8][2];
    float cMusic3_T[4][2];
    
    bool b_de1;
    bool b_de2;
    bool b_de3;

    float de[3];
    float de_cor[3];

    float music1_x_mean;
    float music2_x_mean;
    float music3_x_mean;

    float mhtdc_sc21lr_dt;
    float mhtdc_sc31lr_dt;
    float mhtdc_sc41lr_dt;
    float mhtdc_sc42lr_dt;
    float mhtdc_sc21lr_x;
    float mhtdc_sc22lr_dt;
    float mhtdc_sc22lr_x;
    float mhtdc_sc41lr_x;
    float mhtdc_sc42lr_x;
    float mhtdc_sc43lr_dt;
    float mhtdc_sc43lr_x;
    float mhtdc_sc31lr_x;
    float mhtdc_sc81lr_dt;
    float mhtdc_sc81lr_x;
    
    float mhtdc_tof4121;
    float mhtdc_tof4221;
    float mhtdc_tof4321;
    float mhtdc_tof3121;
    float mhtdc_tof8121;
    float mhtdc_tof4122;

    float sci_l[12];
    float sci_r[12];
    float sci_tx[12];
    float sci_x[12];
    float sci_e[12];

    bool sci_b_l[12];
    bool sci_b_r[12];
    bool sci_b_e[12];
    bool sci_b_tx[12];
    bool sci_b_x[12];

    float cSCI_L[2];
    float cSCI_R[2];
    float cSCI_E[2];
    float cSCI_Tx[2];
    float cSCI_X[2];
    float cSCI_LL2[2];
    float cSCI_RR2[2];
    float cSCI_LL3[2];
    float cSCI_RR3[2];
    float cSCI_LL4[2];
    float cSCI_RR4[2];
    float cSCI_LL5[2];
    float cSCI_RR5[2];
    float cSCI_detof[5][2];

    float sci_tofll2;
    float sci_tofrr2;
    bool sci_b_tofll2;
    bool sci_b_tofrr2;
    float sci_tofll3;
    float sci_tofrr3;
    bool sci_b_tofll3;
    bool sci_b_tofrr3;
    float sci_tofll4;
    float sci_tofrr4;
    bool sci_b_tofll4;
    bool sci_b_tofrr4;
    float sci_tofll5;
    float sci_tofrr5;
    bool sci_b_tofll5;
    bool sci_b_tofrr5;

    float sci_tof2;
    float sci_tof2_calib;
    float sci_tof3;
    float sci_tof3_calib;
    float sci_tof4;
    float sci_tof4_calib;
    float sci_tof5;
    float sci_tof5_calib;
    
    bool sci_b_detof;

    float id_mhtdc_beta_s2s4;
    float id_mhtdc_gamma_s2s4;
    float id_mhtdc_delta_s2s4;
    float id_mhtdc_aoq_s2s4;
    float id_mhtdc_aoq_corr_s2s4;
    float id_mhtdc_z_music41;
    float id_mhtdc_zcor_music41;
    float id_mhtdc_v_cor_music41;
    float id_mhtdc_z_music42;
    float id_mhtdc_zcor_music42;
    float id_mhtdc_v_cor_music42;
    float id_mhtdc_dEdegoQ;
    float id_mhtdc_gamma_ta_s2;
    float id_mhtdc_dEdeg;

	float id_y2;
	float id_a2;
	float id_b2;
	float id_y4;
	float id_a4;
	float id_b4;
	float id_x8;
	float id_y8;
	float id_a8;
	float id_b8;

    int id_trigger;

    float id_brho[2];
    float id_rho[2];

    bool id_b_x2;
	bool id_b_x4;
	bool id_b_x8;
	bool id_b_detof2;

    float cID_x2[2];
    float cID_x4[2];
    float cID_Z_Z[2];

    float id_beta;        /* Beta from TOF            */
	float id_beta3;        /* Beta from TOF            */
	float id_gamma;       /* Gamma from TOF           */

    bool id_b_AoQ;
    bool id_b_z;
    bool id_b_z2;
    bool id_b_z3;

    float id_v_cor;
    float id_v_cor2;
    float id_v_cor3;
    float id_z;
    float id_z2;
    float id_z3;

    float id_de_s2tpc;
    bool id_b_de_s2tpc;
    float id_gamma_ta_s2;

    float  VFTX_Bin2Ps[VFTX_N][VFTX_MAX_CHN][1000];

    void __clean() {};

   // void dump(const signal_id &id,pretty_dump_info &pdi) const;
   void show_members(const signal_id &id,const char *unit) const;
   // void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
    void zero_suppress_info_ptrs(used_zero_suppress_info &used_info);
   // const char* get_name(const std::string &name, int index) const;
   // const char* get_name2(const std::string &name, int index, int index2) const;

};

struct store_item
{
    public:
        float id_beta;
        int count = 0;
};

class EXT_FRS
{
    public:
        EXT_FRS();
        ~EXT_FRS();

        EXT_DECL_UNPACK_ARG(int procid, int type, int subtype);

        void __clean();

        void Setup_Conditions();
        void Setup_FRS_Parameters();

        template<typename __data_src_t>
        void FRS_Unpack(__data_src_t &__buffer, frs_item &item, int procid, int type, int subtype);
        void FRS_Sort(frs_item &item, int procid, int type, int subtype);
        void FRS_Calib(frs_item &item, int procid, int type, int subtype);
        void FRS_Anal(frs_item &item, int procid, int type, int subtype);

        int getbits(uint32 value, int nword, int start, int length);
        int get2bits(uint32 value, int nword, int start, int length);
        float rand3();
        // float float
        bool Check_WinCond(float P, double *V);
        // float float int
        bool Check_WinCond_Multi(float P, float **V, int cond_num);
        double VFTX_GetTraw_ps(frs_item item, int module, int channel, int cc, int ft, float rand);
        // float float float int
        bool Check_PolyCond_X_Y(float X, float Y, double V[][2], int n);

        // void dump(const signal_id &id,pretty_dump_info &pdi) const;
        // void show_members(const signal_id &id,const char *unit) const;
        // void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
        //void zero_suppress_info_ptrs(used_zero_suppress_info& used_info);
        // const char* get_name(const std::string &name, int index) const;
        DUMMY_EXTERNAL_DUMP(EXT_FRS);
        DUMMY_EXTERNAL_SHOW_MEMBERS(EXT_FRS);
        DUMMY_EXTERNAL_ENUMERATE_MEMBERS(EXT_FRS);
        DUMMY_EXTERNAL_ZERO_SUPPRESS_INFO_PTRS(EXT_FRS);

    public:
        //raw_list_ii_zero_suppress<frs_item, frs_item, FRS_MAX_HITS> frs_info;
        frs_item frs_info; // works but is not zero suppressed -> issue

        store_item store;

        float test;

        // well these were all floats but whatever

        // ***** SETUP CONDITIONS ******** //
        double lim_csum[4][7][2]; // float
        double lim_xsum[13][2];
        double lim_ysum[13][2];

        double cMusic1_E[8][2];
        double cMusic1_T[8][2];
        double cMusic2_E[8][2];
        double cMusic2_T[8][2];
        double cMusic3_E[4][2];
        double cMusic3_T[4][2];

        double cMusic3_dec[2];

        double cTPC_LT0[7][2];
        double cTPC_RT0[7][2];
        double cTPC_LT1[7][2];
        double cTPC_RT1[7][2];
        double cTPC_DT[7][4][2];
        double cTPC_SC_TIMEREF[8][2];

        double cSCI_L[2];
        double cSCI_R[2];
        double cSCI_E[2];
        double cSCI_Tx[2];
        double cSCI_X[2];

        double cSCI_LL2[2];
        double cSCI_RR2[2];
        double cSCI_LL3[2];
        double cSCI_RR3[2];
        double cSCI_LL4[2];
        double cSCI_RR4[2];
        double cSCI_LL5[2];
        double cSCI_RR5[2];

        double cSCI_detof[5][2];

        double cID_x2[2];
        double cID_x4[2];
        double cID_Z_Z[2];
        double cID_x4AoQ_Z[5][2];
        double cID_x2AoQ[6][6][2];
        double cID_x4AoQ[6][6][2];
        double cID_Z_AoQ[5][6][2];
        double cID_dEToF[5][2];
        
        TMWParameter mw;
        TFRSParameter frs;
        TTPCParameter tpc;
        TMUSICParameter music;
        TSCIParameter sci;
        TIDParameter id;
        
};

DUMMY_EXTERNAL_MAP_STRUCT(EXT_FRS);
DUMMY_EXTERNAL_WATCHER_STRUCT(EXT_FRS);
DUMMY_EXTERNAL_CORRELATION_STRUCT(EXT_FRS);
DUMMY_EXTERNAL_CALIB_MAP_STRUCT(EXT_FRS);

#endif