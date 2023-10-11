#ifndef __PLASTIC_TWINPEAKS_UNPACK_HH__
#define __PLASTIC_TWINPEAKS_UNPACK_HH__

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

DUMMY_EXTERNAL_MAP_STRUCT_FORW(EXT_PLASTIC_TP);

struct plastic_twinpeaks_item
{
    
    // PLASTIC_TAMEX MBS words
    int add = 2781;
    int aa = 170;
    int six_eight = 104;
    int six_f = 6;
    int trailer_code = 187;
    int error_code = 238;
    int tamex_identifier = 52;

    uint32 iterator[PLASTIC_TWINPEAKS_MAX_ITER]; // int
    uint32 tamex_id[PLASTIC_TWINPEAKS_MAX_ITER]; // int

    int tamex_iter;

    uint32 am_fired[PLASTIC_TWINPEAKS_MAX_ITER]; // int
    uint32 sfp_id[PLASTIC_TWINPEAKS_MAX_ITER]; // int
    uint32 trigger_type[PLASTIC_TWINPEAKS_MAX_ITER]; // int

    double coarse_T[PLASTIC_TWINPEAKS_MAX_ITER]; // 0-2 (first 3)
    double fine_T[PLASTIC_TWINPEAKS_MAX_ITER]; 
    uint32 ch_ID[PLASTIC_TWINPEAKS_MAX_ITER];

    uint32 lead_arr[BPLAST_TAMEX_MODULES][PLASTIC_TWINPEAKS_MAX_ITER]; // was 100 100 // int
    //int leading_hits[BPLAST_TAMEX_MODULES][PLASTIC_TWINPEAKS_MAX_ITER]; // unused leaving for now
    //int trailing_hits[BPLAST_TAMEX_MODULES][PLASTIC_TWINPEAKS_MAX_ITER]; // unused leaving for now

    double edge_coarse[BPLAST_TAMEX_MODULES][PLASTIC_TWINPEAKS_MAX_ITER];
    double edge_fine[BPLAST_TAMEX_MODULES][PLASTIC_TWINPEAKS_MAX_ITER];
    uint32 ch_ID_edge[BPLAST_TAMEX_MODULES][PLASTIC_TWINPEAKS_MAX_ITER];
    uint32 ch_num[BPLAST_TAMEX_MODULES][PLASTIC_TWINPEAKS_MAX_ITER];
     
    bool tamex_end;
    bool written;
    bool no_edges[PLASTIC_TWINPEAKS_MAX_ITER]; // how the fuck do i unpack a bool. turn it into 1 vs 0?
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

class EXT_PLASTIC_TP
{
    public:
        EXT_PLASTIC_TP();
        ~EXT_PLASTIC_TP();

        EXT_DECL_UNPACK();

        void __clean();
        void reset_edges(plastic_twinpeaks_item &item);

        template<typename __data_src_t>
        bool no_error_reached(__data_src_t &__buffer, plastic_twinpeaks_item &item);
        template<typename __data_src_t>
        void check_trailer(__data_src_t &__buffer, plastic_twinpeaks_item &item);
        template<typename __data_src_t>
        void get_edges(__data_src_t &__buffer, plastic_twinpeaks_item &item);
        template<typename __data_src_t>
        void get_trigger(__data_src_t &__buffer, plastic_twinpeaks_item &item);
        template<typename __data_src_t>
        void skip_padding(__data_src_t &__buffer, plastic_twinpeaks_item &item);
        template<typename __data_src_t>
        void Process_TAMEX(__data_src_t &__buffer, plastic_twinpeaks_item &item);
        void calibrate_ONLINE();
        void calibrate_OFFLINE();
    
        void dump(const signal_id &id,pretty_dump_info &pdi) const;
        void show_members(const signal_id &id,const char *unit) const;
        void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
        void zero_suppress_info_ptrs(used_zero_suppress_info &used_info);

    public:
        raw_list_ii_zero_suppress<plastic_twinpeaks_item, plastic_twinpeaks_item, PLASTIC_MAX_HITS> plastic_tp_info;
        int tamex_err_count;

};

DUMMY_EXTERNAL_MAP_STRUCT(EXT_PLASTIC_TP);
DUMMY_EXTERNAL_WATCHER_STRUCT(EXT_PLASTIC_TP);
DUMMY_EXTERNAL_CORRELATION_STRUCT(EXT_PLASTIC_TP);
DUMMY_EXTERNAL_CALIB_MAP_STRUCT(EXT_PLASTIC_TP);

#endif /* __PLASTIC_TWINPEAKS_UNPACK_HH__ */

