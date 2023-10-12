#ifndef __GE_FEBEX_UNPACK_HH__
#define __GE_FEBEX_UNPACK_HH__

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

DUMMY_EXTERNAL_MAP_STRUCT_FORW(EXT_GERMANIUM);

struct febex_item
{   

    // ulong64 broken into 2x uint32
    uint32 Sum_Time_lo[GE_MAX_HITS]; // ulong64
    uint32 Sum_Time_hi[GE_MAX_HITS]; // ulong64
    uint32 Hit_Pattern[GE_MAX_HITS]; // int
    uint32 Chan_Time_lo[GE_MAX_HITS]; // ulong64
    uint32 Chan_Time_hi[GE_MAX_HITS]; // ulong64
    uint32 Chan_Energy[GE_MAX_HITS]; // double 
    uint32 Chan_CF_lo[GE_MAX_HITS]; // ulong64
    uint8 Chan_CF_hi[GE_MAX_HITS]; // ulong64
    bool Pileup[GE_MAX_HITS]; // bool
    bool Overflow[GE_MAX_HITS]; // bool
    uint32 det_ids[GE_MAX_HITS]; // int
    uint32 crystal_ids[GE_MAX_HITS]; // int
    uint32 Ge_Fired; 

    void __clean() {};

    void dump(const signal_id &id,pretty_dump_info &pdi) const;
    void show_members(const signal_id &id,const char *unit) const;
    void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
    void zero_suppress_info_ptrs(used_zero_suppress_info& used_info);
    const char* get_name(const std::string &name, int index) const;

};

class EXT_GERMANIUM
{
    public:
        EXT_GERMANIUM();
        ~EXT_GERMANIUM();

        void __clean();

        EXT_DECL_UNPACK();
        //EXT_DECL_UNPACK_HDR();

        void load_board_channel_file();

        void dump(const signal_id &id,pretty_dump_info &pdi) const;
        void show_members(const signal_id &id,const char *unit) const;
        void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
        void zero_suppress_info_ptrs(used_zero_suppress_info &used_info);

    public:
        //raw_list_ii_zero_suppress<febex_item, febex_item, 1> febex_info;
        febex_item febex_info;

        std::map<std::pair<int, int>, std::pair<int, int>> Germanium_map;
    
    private:

        //int fired_FEBEX_amount;
        //int num_channels_fired;
        uint32 Sum_Time_lo[GE_MAX_HITS];
        uint32 Sum_Time_hi[GE_MAX_HITS];
        uint32 Hit_Pattern[GE_MAX_HITS];
        uint32 Chan_Time_lo[GE_MAX_HITS];
        uint32 Chan_Time_hi[GE_MAX_HITS];
        uint32 Chan_Energy[GE_MAX_HITS];
        uint32 Chan_CF_lo[GE_MAX_HITS];
        uint32 Chan_CF_hi[GE_MAX_HITS];
        bool Pileup[GE_MAX_HITS];
        bool Overflow[GE_MAX_HITS];
        uint32 det_ids[GE_MAX_HITS];
        uint32 crystal_ids[GE_MAX_HITS];

        int pileup_flags[16];
        int Ge_channels[16];

};

DUMMY_EXTERNAL_MAP_STRUCT(EXT_GERMANIUM);
DUMMY_EXTERNAL_WATCHER_STRUCT(EXT_GERMANIUM);
DUMMY_EXTERNAL_CORRELATION_STRUCT(EXT_GERMANIUM);
DUMMY_EXTERNAL_CALIB_MAP_STRUCT(EXT_GERMANIUM);

#endif /* __GE_FEBEX_UNPACK_HH__ */