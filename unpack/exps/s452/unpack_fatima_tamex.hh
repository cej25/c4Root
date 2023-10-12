#ifndef __FAT_TAMEX_UNPACK__
#define __FAT_TAMEX_UNPACK__

#include "config/setup.hh"

#include "data_src.hh"
#include "dummy_external.hh"
#include "external_data.hh"
#include "zero_suppress.hh"
#include <map>

struct fatima_tamex_item
{   
    public:

        // this is a mess need to sort out
        bool tamex_end;
        bool no_edges[100];
        bool written;
        
        bool CALIBRATE = false; // for now
        bool Calibration_Done = false;
        int cal_count;

        int tamex_identifier = 52;

        int trailer_code;

        int am_fired[100];
        int sfp_id[100];
        int trigger_type[100];
        int iterator[200];
        int tamex_id[100];

        int tamex_iter;

        int Pre_Trigger_Window;
        int Post_Trigger_Window;

        bool leading_hit; // bool_t?
        //double** edge_coarse;
        //double** edge_fine;

        uint32 ch_ID_edge_lead[100][100];
        uint32 ch_ID_edge_trail[100][100];

        double coarse_T[200];
        double fine_T[200];
        uint32 ch_ID[200];

        double edge_coarse[200][200]; // * or **?
        double edge_fine[200][200]; // * or **?
        uint32 ch_ID_edge[200][200];

        int lead_arr[200][200];
        int leading_hits[200][200];
        int trailing_hits[200][200];

        void __clean() {};


};


class EXT_FATIMA_TAMEX
{
    public:
        EXT_FATIMA_TAMEX();
        ~EXT_FATIMA_TAMEX();

        EXT_DECL_UNPACK();

        void __clean();
        void reset_edges(fatima_tamex_item &item);

        template<typename __data_src_t>
        bool no_error_reached(__data_src_t &__buffer);
        template<typename __data_src_t>
        void check_trailer(__data_src_t &__buffer);
        template<typename __data_src_t>
        void get_edges(__data_src_t &__buffer, fatima_tamex_item &item);
        template<typename __data_src_t>
        void get_trigger(__data_src_t &__buffer, fatima_tamex_item &item);
        template<typename __data_src_t>
        void skip_padding(__data_src_t &__buffer);
        template<typename __data_src_t>
        void Process_TAMEX(__data_src_t &__buffer, fatima_tamex_item &item);
        void calibrate_ONLINE();
        void calibrate_OFFLINE();

        void get_Calib_type();

        void dump(const signal_id &id,pretty_dump_info &pdi) const;
        void show_members(const signal_id &id,const char *unit) const;
        void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
        void zero_suppress_info_ptrs(used_zero_suppress_info &used_info);

    public:
        // ?
        raw_list_ii_zero_suppress<fatima_tamex_item, fatima_tamex_item, FAT_MAX_HITS> fat_tamex_info;
};

DUMMY_EXTERNAL_MAP_STRUCT(EXT_FATIMA_TAMEX);
DUMMY_EXTERNAL_WATCHER_STRUCT(EXT_FATIMA_TAMEX);
DUMMY_EXTERNAL_CORRELATION_STRUCT(EXT_FATIMA_TAMEX);
DUMMY_EXTERNAL_CALIB_MAP_STRUCT(EXT_FATIMA_TAMEX);

#endif /* __FAT_TAMEX_UNPACK__ */