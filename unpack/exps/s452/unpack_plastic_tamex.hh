#ifndef __PLASTIC_TAMEX_UNPACK_HH__
#define __PLASTIC_TAMEX_UNPACK_HH__

#include "config/setup.hh"

#include "data_src.hh"
#include "dummy_external.hh"
#include "external_data.hh"
#include "zero_suppress.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <limits>

DUMMY_EXTERNAL_MAP_STRUCT_FORW(EXT_PLASTIC);

struct plastic_tamex_item
{
    // PLASTIC_TAMEX MBS words
    int add = 2781;
    int aa = 170;
    int six_eight = 104;
    int six_f = 6;
    int trailer_code = 187;
    int error_code = 238;
    int tamex_identifier = 52;

    uint32 iterator[PLASTIC_MAX_ITER]; // int
    uint32 tamex_id[PLASTIC_MAX_ITER]; // int

    int tamex_iter;

    uint32 am_fired[PLASTIC_MAX_ITER]; // int
    uint32 sfp_id[PLASTIC_MAX_ITER]; // int
    uint32 trigger_type[PLASTIC_MAX_ITER]; // int

    double coarse_T[PLASTIC_MAX_ITER]; // 0-2 (first 3)
    double fine_T[PLASTIC_MAX_ITER]; 
    uint32 ch_ID[PLASTIC_MAX_ITER];

    uint32 lead_arr[PLASTIC_MAX_ITER][PLASTIC_MAX_ITER]; // was 100 100 // int
    //int leading_hits[4][PLASTIC_MAX_ITER]; // unused
    //int trailing_hits[4][PLASTIC_MAX_ITER]; // unused

    // i changed these to 4 at some point
    double edge_coarse[PLASTIC_MAX_ITER][PLASTIC_MAX_ITER];
    double edge_fine[PLASTIC_MAX_ITER][PLASTIC_MAX_ITER];
    uint32 ch_ID_edge[PLASTIC_MAX_ITER][PLASTIC_MAX_ITER];
    uint32 ch_num[PLASTIC_MAX_ITER][PLASTIC_MAX_ITER];
     
    bool tamex_end;
    bool written;
    bool no_edges[PLASTIC_MAX_ITER]; // how the fuck do i unpack a bool. turn it into 1 vs 0?
    bool error;
    bool leading_hit; // = false;
    
    // calibration stuff?
    bool CALIBRATE = false;
    bool Calibration_Done = false;
    int cal_count = 0;

    int Pre_Trigger_Window = 0;
    int Post_Trigger_Window = 0;

    void __clean() {};

    void dump(const signal_id &id,pretty_dump_info &pdi) const;
    void show_members(const signal_id &id,const char *unit) const;
    void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
    void zero_suppress_info_ptrs(used_zero_suppress_info& used_info);
    const char* get_name(const std::string &name, int index) const;
    const char* get_name2(const std::string &name, int index, int index2) const;
};

class EXT_PLASTIC
{
    public:
        EXT_PLASTIC();
        ~EXT_PLASTIC();

        EXT_DECL_UNPACK();

        void __clean();
        void reset_edges(plastic_tamex_item &item);

        template<typename __data_src_t>
        bool no_error_reached(__data_src_t &__buffer, plastic_tamex_item &item);
        template<typename __data_src_t>
        void check_trailer(__data_src_t &__buffer, plastic_tamex_item &item);
        template<typename __data_src_t>
        void get_edges(__data_src_t &__buffer, plastic_tamex_item &item);
        template<typename __data_src_t>
        void get_trigger(__data_src_t &__buffer, plastic_tamex_item &item);
        template<typename __data_src_t>
        void skip_padding(__data_src_t &__buffer, plastic_tamex_item &item);
        template<typename __data_src_t>
        void Process_TAMEX(__data_src_t &__buffer, plastic_tamex_item &item);
        void calibrate_ONLINE();
        void calibrate_OFFLINE();
    
       /* void dump(const signal_id &id,pretty_dump_info &pdi) const;
        void show_members(const signal_id &id,const char *unit) const;
        void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
        void zero_suppress_info_ptrs(used_zero_suppress_info &used_info);*/

        DUMMY_EXTERNAL_DUMP(EXT_PLASTIC);
        DUMMY_EXTERNAL_SHOW_MEMBERS(EXT_PLASTIC);
        DUMMY_EXTERNAL_ENUMERATE_MEMBERS(EXT_PLASTIC);
        DUMMY_EXTERNAL_ZERO_SUPPRESS_INFO_PTRS(EXT_PLASTIC);

    public:
        //raw_list_ii_zero_suppress<plastic_tamex_item, plastic_tamex_item, PLASTIC_MAX_HITS> plastic_info;
        plastic_tamex_item plastic_info;
        int tamex_err_count;

};

DUMMY_EXTERNAL_MAP_STRUCT(EXT_PLASTIC);
DUMMY_EXTERNAL_WATCHER_STRUCT(EXT_PLASTIC);
DUMMY_EXTERNAL_CORRELATION_STRUCT(EXT_PLASTIC);
DUMMY_EXTERNAL_CALIB_MAP_STRUCT(EXT_PLASTIC);

#endif /* __PLASTIC_TAMEX_UNPACK_HH__ */

