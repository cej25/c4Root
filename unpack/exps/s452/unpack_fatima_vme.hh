#ifndef __FAT_VME_UNPACK_HH__
#define __FAT_VME_UNPACK_HH__

#include "config/setup.hh"

#include "data_src.hh"
#include "dummy_external.hh"
#include "external_data.hh"
#include "zero_suppress.hh"
#include <map>

DUMMY_EXTERNAL_MAP_STRUCT_FORW(EXT_FATIMA_VME);

struct fatima_vme_item 
{
    //int fired_QDC_amount = 0;
    //int fired_TDC_amount = 0;

    double QLong[MAX_AM_DETS_VME];
    double QLong_Raw[MAX_AM_DETS_VME];
    double QShort_Raw[MAX_AM_DETS_VME];
    
    uint32 QDC_Time_Coarse[MAX_AM_DETS_VME]; // stores without "ext trig"
    double QDC_Time_Ext[MAX_AM_DETS_VME];
    double QDC_Time_Fine[MAX_AM_DETS_VME];

    /*
    uint32 TDC_Time_raw_lo[MAX_AM_DETS];
    uint32 TDC_Time_raw_hi[MAX_AM_DETS]; 
    */
    uint32 TDC_Time_Raw[MAX_AM_DETS_VME];
    double TDC_Time_ns[MAX_AM_DETS_VME];

    int det_ids_QDC[MAX_AM_DETS_VME];
    int det_ids_TDC[MAX_AM_DETS_VME];

    double Scaler_Data[MAX_SCALERS_VME];

    bool gain_match_used;
    int num_TDC_modules = 0;
    int num_TDC_modules_fixed = 0;
    bool Scaler_Module;
    bool Scaler_module; // wut? this is stupid 

    int Fired_QDC_Channels[100][2];

    void __clean() {};
    void dump(const signal_id& id, pretty_dump_info& pdi) const;
    void show_members(const signal_id &id,const char *unit) const;
    void enumerate_members(const signal_id& id, const enumerate_info& info, enumerate_fcn callback, void* extra) const;
    void zero_suppress_info_ptrs(used_zero_suppress_info& used_info);

};


class EXT_FATIMA_VME
{
    public:
        EXT_FATIMA_VME();
        ~EXT_FATIMA_VME();

        void __clean();
        EXT_DECL_UNPACK();

        void load_board_channel_file();

        template<typename __data_src_t>
        int CHECK_SCALER_DATA(__data_src_t &__buffer, uint32 &geo, fatima_vme_item &fat_info);
        template<typename __data_src_t>
        int CHECK_QDC_DATA(__data_src_t &__buffer, fatima_vme_item &fat_info);
        template<typename __data_src_t>
        int CHECK_TDC_DATA(__data_src_t &__buffer, fatima_vme_item &fat_info);
        bool wired_QDC(int board_id, int ch_num, fatima_vme_item &fat_info);
        bool wired_TDC(int board_id, int ch_num, fatima_vme_item &fat_info);

        void Calibrate_QDC(int id);
        void Calibrate_TDC(int id);

        void dump(const signal_id &id,pretty_dump_info &pdi) const;
        void show_members(const signal_id &id,const char *unit) const;
        void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
        void zero_suppress_info_ptrs(used_zero_suppress_info &used_info);

    public:
        
        // needed?
        raw_list_ii_zero_suppress<fatima_vme_item, fatima_vme_item, FAT_MAX_HITS> fatima_vme_info;

        // Fatima VME allocation map
        int det_ID_QDC[100][100];
        int det_ID_TDC[100][100];

    
    private:

        //stuff

};

DUMMY_EXTERNAL_MAP_STRUCT(EXT_FATIMA_VME);
DUMMY_EXTERNAL_WATCHER_STRUCT(EXT_FATIMA_VME);
DUMMY_EXTERNAL_CORRELATION_STRUCT(EXT_FATIMA_VME);
DUMMY_EXTERNAL_CALIB_MAP_STRUCT(EXT_FATIMA_VME);

#endif /* __FAT_VME_UNPACK_HH__ */