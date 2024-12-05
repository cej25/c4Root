#ifndef __TR_EXT_HH__
#define __TR_EXT_HH__

#include "data_src.hh"
#include "dummy_external.hh"
#include "external_data.hh"
#include "zero_suppress.hh"
#include <map>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>

DUMMY_EXTERNAL_MAP_STRUCT_FORW(EXT_LISA);

struct FebexEvent
{
    public:
        uint32 fts_lo[16];
        uint32 fts_hi[16];
        uint32 flength;
        uint32 fboard;
        uint32 fchn;
        uint32 fen[16];
        uint32 pileup_flags[16];
        uint32 fhitpat[16]; // Ge_channels in Go4. Take a look later.
        uint32 fpileup[16]; // max_hits in Go4. Just 16 here for now not dets x crystals?
        uint32 foverflow[16]; // same as above.
    
    public:
        void __clean() {};
        void dump(const signal_id &id,pretty_dump_info &pdi) const;
        void show_members(const signal_id &id,const char *unit) const;
        void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
        void zero_suppress_info_ptrs(used_zero_suppress_info& used_info);

        const char* get_name(const std::string &name, int index) const;
};

class EXT_LISA
{
    public:
        EXT_LISA();
        ~EXT_LISA();

        void __clean();
        EXT_DECL_UNPACK();

        void dump(const signal_id &id,pretty_dump_info &pdi) const;
        void show_members(const signal_id &id,const char *unit) const;
        void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
        void zero_suppress_info_ptrs(used_zero_suppress_info &used_info);
    
    public:
        raw_list_ii_zero_suppress<FebexEvent, FebexEvent, 1> event;
        
};

DUMMY_EXTERNAL_MAP_STRUCT(EXT_LISA);
DUMMY_EXTERNAL_WATCHER_STRUCT(EXT_LISA);
DUMMY_EXTERNAL_CORRELATION_STRUCT(EXT_LISA);
DUMMY_EXTERNAL_CALIB_MAP_STRUCT(EXT_LISA);

#endif
