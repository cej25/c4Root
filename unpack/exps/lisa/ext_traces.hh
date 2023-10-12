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
//#include "TObject.h"

#define NO_UINT64 1

#define GEID 60
#define FEBEX_MODULES 1
#define withWR 0

static const uint32 SIZE = 4000;
static const uint8 NCH = 1;

DUMMY_EXTERNAL_MAP_STRUCT_FORW(EXT_TRACES);

struct Trace
{
    public:

        void SetTS(uint32 ts_lo, uint32 ts_hi) 
        {
            fts_lo = ts_lo;
            fts_hi = ts_hi;
        }
        void SetLength(int length)
        {
            flength = length;
            ftrace.resize(length);
        }

        void SetBoard(uint32 boardid) {fboard = boardid;}
        void SetChn(uint32 chnid) {fchn = chnid;}
        void SetEnergy(uint32 en) {fen = en;}
        void SetTrace(uint32 n, uint32 v) {ftrace[n] = v;}

        std::pair<uint32, uint32> GetTS() {return std::pair<uint32, uint32>(fts_lo, fts_hi);}
        int GetLength() {return flength;}
        int GetBoard() {return fboard;}
        int GetChn() {return fchn;}
        int GetEnergy() {return fen;}

        std::vector <uint32> GetTrace() {return ftrace;}
        void Print()
        {
            std::cout << "--------------------- Trace Print ------------------------" << std::endl;
            std::cout << "flength  = " << flength  << std::endl;
            std::cout << "fboard   = " << fboard   << std::endl;
            std::cout << "fchn     = " << fchn     << std::endl;
            std::cout << "fts_lo   = " << fts_lo   << std::endl;
            std::cout << "fts_hi   = " << fts_hi   << std::endl;
            std::cout << "fen      = " << fen      << std::endl;
        }

        void __clean() {};
        void dump(const signal_id &id,pretty_dump_info &pdi) const;
        void show_members(const signal_id &id,const char *unit) const;
        void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
        void zero_suppress_info_ptrs(used_zero_suppress_info& used_info);
    
    public:

        //! The timestamp. (2x UINT32 required probably)
        uint32 fts_lo;
        uint32 fts_hi;
        uint32 flength;
        uint32 fboard;
        uint32 fchn;
        uint32 fen;
        //! The wave form.
        std::vector <uint32> ftrace;

};

struct TraceEvent
{
    public:

        void AddTrace(Trace add)
        {
            ftraces.push_back(add);
            fmult++;
            for (uint32 i = 0; i < SIZE; i++)
            {
                trace_array._items[i] = add.ftrace[i];
            }
        }

        uint32 GetMult() {return fmult;}
        Trace* GetTrace(int n) {return &ftraces[n];}
        std::vector<Trace>* GetTrace() {return &ftraces;}
        
        void __clean() {};
        void dump(const signal_id &id,pretty_dump_info &pdi) const;
        void show_members(const signal_id &id,const char *unit) const;
        void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
        void zero_suppress_info_ptrs(used_zero_suppress_info& used_info);

    public:
        uint32 fmult;
        std::vector<Trace> ftraces;
        raw_array_zero_suppress<uint32,uint32,SIZE> trace_array;
    
};

class EXT_TRACES
{
    public:
        EXT_TRACES();
        ~EXT_TRACES();

        void __clean();
        EXT_DECL_UNPACK();

        void AddTrace(Trace add)
        {
            for (uint32 i = 0; i < SIZE; i++)
            {
                trace_array._items[i] = add.ftrace[i];
            }
        }

        void dump(const signal_id &id,pretty_dump_info &pdi) const;
        void show_members(const signal_id &id,const char *unit) const;
        void enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const;
        void zero_suppress_info_ptrs(used_zero_suppress_info &used_info);
    
    public:
        raw_list_ii_zero_suppress<TraceEvent, TraceEvent, SIZE> trEvent;
        //TraceEvent trEvent;
        raw_list_ii_zero_suppress<Trace, Trace, SIZE> trace;
        raw_array_zero_suppress<uint32, uint32, SIZE> trace_array;
        
        
        // this is how the unpacker code looks from spec file generation for febex_withtraces
        //raw_array_zero_suppress<DATA12, DATA12, 1000> trace[16]; // 16 channels, length 1000
    
};

DUMMY_EXTERNAL_MAP_STRUCT(EXT_TRACES);
DUMMY_EXTERNAL_WATCHER_STRUCT(EXT_TRACES);
DUMMY_EXTERNAL_CORRELATION_STRUCT(EXT_TRACES);
DUMMY_EXTERNAL_CALIB_MAP_STRUCT(EXT_TRACES);

#endif