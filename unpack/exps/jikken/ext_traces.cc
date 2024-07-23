#include "ext_traces.hh"
#include "enumerate.hh"
#include "simple_data_ops.hh"
#include "zero_suppress.hh"
#include "zero_suppress_map.hh"
#include "error.hh"
#include <algorithm>
#include <iterator>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>

// can use ~/lustre/gamma/LISA/data/Spring2023/FebexData/lmd/lisa_Feb09_test.lmd

struct used_zero_suppress_info
{
    public:
        used_zero_suppress_info(const zero_suppress_info *info)
        {
            _info = info;
            _used = false;
        }

        ~used_zero_suppress_info()
        {
            if (!_used)
                delete _info;
        }

    public:
        const zero_suppress_info *_info;
        bool                      _used;
};

template<typename Tsingle,typename T,int n>
void raw_list_ii_zero_suppress<Tsingle,T,n>::zero_suppress_info_ptrs(used_zero_suppress_info &used_info)
{
  
    for (int i = 0; i < n; ++i)
    {
        zero_suppress_info *info =
	    new zero_suppress_info(used_info._info,true);
        zzp_on_insert_index(i,*info);
        used_zero_suppress_info sub_used_info(info);

        call_zero_suppress_info_ptrs(&_items[i],sub_used_info);
    }
}

template<typename Tsingle,typename T,int n>
void raw_array_zero_suppress<Tsingle,T,n>::
zero_suppress_info_ptrs(used_zero_suppress_info &used_info)
{
  if ((used_info._info->_type & ZZP_INFO_MASK) != ZZP_INFO_NONE)
    ERROR("Two levels of zero suppression not supported!");

  for (int i = 0; i < n; ++i)
    {
      zero_suppress_info *info = new zero_suppress_info(used_info._info);
      zzp_on_insert_index(i,*info);
      used_zero_suppress_info sub_used_info(info);

      call_zero_suppress_info_ptrs(&_items[i],sub_used_info);
    }
}


template<typename T>
void show_members(const signal_id &id, const char *unit)
{
    char buf[256];
    id.format(buf, sizeof(buf));

    char buf_paw[256];
    id.format_paw(buf_paw, sizeof(buf_paw));

    printf ("%-30s %-30s %s\n",buf_paw,buf,unit ? unit : "");
}

EXT_TRACES::EXT_TRACES()
{
    __clean();
}

EXT_TRACES::~EXT_TRACES()
{
}

void EXT_TRACES::__clean()
{
    trEvent.__clean();
    trace.__clean();
}

EXT_DECL_DATA_SRC_FCN(void, EXT_TRACES::__unpack)
{

    while (!__buffer.empty())
    {

        auto & tr = trEvent.append_item();

        uint32 febex_add = 0;
        __buffer.get_uint32(&febex_add);
        while ((febex_add & 0xFFF00000) == 0xadd00000)
        {
            __buffer.get_uint32(&febex_add);

            //std::cout << "febex_add: " << std::hex << febex_add << std::dec << std::endl;
        }

        uint32 febex_header = febex_add;

        int board_id = -1; // board_id
        int nchan = 0;// num_channels
        int nmod = FEBEX_MODULES;
        bool febex_data = true;

        // test if this works in ext_germanium

        while (febex_data)
        {   

            if (((febex_header >> 24) & 0xFF) == 0xFF)
            {   

                std::cout << "febex header: " << std::hex << febex_header << std::dec << std::endl; 

                board_id = ((febex_header >> 16) & 0xFF);

                uint32 febex_chan_size;
                __buffer.get_uint32(&febex_chan_size);

                std::cout << "febex chan size: " << std::hex << febex_chan_size << std::dec << std::endl; 
                nchan = (((febex_chan_size >> 2) & 0x3FFFFFFF) / 4) - 1;

                std::cout << "nchan: " << nchan << std::endl;

                if (nchan == 0) nmod--;

                /*
                uint32 febex_half_time, febex_event_time;
                __buffer.get_uint32(&febex_half_time);
                __buffer.get_uint32(&febex_event_time);

                std::cout << "febex half time: " << std::hex << febex_half_time << std::dec << std::endl;
                std::cout << "febex event time: " << std::hex << febex_event_time << std::dec << std::endl; 

                uint32 tmp_sum_time_lo = febex_event_time;
                uint32 tmp_sum_time_hi = ((febex_half_time >> 16) & 0xFFFF);
                */

                // skip sum_time and ext_time?
                __buffer.advance(8);

                // skip febex_flags
                __buffer.advance(4);

                // can skip deadbeef but always nice to check..
                uint32 deadbeef = 0;
                __buffer.get_uint32(&deadbeef);

                std::cout << "deadbeef: " << std::hex << deadbeef << std::dec << std::endl;
                //_buffer.advance(4);

            } // FF

            else if (((febex_header >> 24) & 0xFF) == 0xF0)
            {
                __buffer.reverse(4); // move back a word
                
                std::cout << "febex header: " << std::hex << febex_header << std::dec << std::endl; 

                //std::vector<Trace> traces;

                auto & traces = trace.append_item();//?

                //traces.resize(nchan);

                for (int i = 0; i < nchan; i++)
                {   
                    uint32 febex_chan_header = 0;
                    __buffer.get_uint32(&febex_chan_header);

                    std::cout << "febex chan header: " << std::hex << febex_chan_header << std::dec << std::endl; 

                    int tmp_ch_id = ((febex_chan_header >> 16) & 0xFF);

                    std::cout << "tmp_ch_id: " << tmp_ch_id << std::endl;
                    
                    if (board_id < 0)
                    {
                        std::cout << "Something wrong, don't have the board ID" << std::endl;
                        __buffer.advance(12);
                        continue;
                    }

                    //traces.at(i).SetBoard(board_id);

                    traces.SetBoard(board_id);

                    //traces.at(i).SetChn(tmp_ch_id);

                    traces.SetChn(tmp_ch_id);

                    uint32 tmp_chan_ts_lo = 0;
                    __buffer.get_uint32(&tmp_chan_ts_lo);
                    uint32 tmp_chan_ts_hi = (febex_chan_header  & 0xFFFF);

                    //traces.at(i).SetTS(tmp_chan_ts_lo, tmp_chan_ts_hi);

                    traces.SetTS(tmp_chan_ts_lo, tmp_chan_ts_hi);

                    std::cout << "tmp_chan_ts_lo: " << std::hex << tmp_chan_ts_lo << std::dec << std::endl; 
                    std::cout << "tmp_chan_ts_hi: " << std::hex << tmp_chan_ts_hi << std::dec << std::endl;

                    uint32 febex_chan_energy = 0;
                    __buffer.get_uint32(&febex_chan_energy);
                    uint32 tmp_chan_energy = (febex_chan_energy & 0xFFFFFF);

                    std::cout << "febex_chan_energy: " << std::hex << febex_chan_energy << std::dec << std::endl;

                    //int energy = 0;
                    if (tmp_chan_energy & 0x00800000)
                    {
                        tmp_chan_energy = 0xFF000000 | tmp_chan_energy; // uint32?
                    }

                    //traces.at(i).SetEnergy(energy);
                    
                    // temporary fix to see hist properly // ah lol this is so wanky
                    if (tmp_chan_energy > 4000000000)
                    {
                        traces.SetEnergy(0);
                    } 
                    else
                    {
                       traces.SetEnergy(tmp_chan_energy); 
                    }

                    __buffer.advance(4); // is this future use?
                } // nchan 


                nmod--;
                
                // now comes the traces

                for (int i = 0; i < nchan; i++)
                {   
                    uint32 header = 0;
                    __buffer.get_uint32(&header);

                    if ((header & 0xFF) == 0x00000034)
                    {
                        uint32 tracesize = 0, tracehead = 0;
                        __buffer.get_uint32(&tracesize);
                        __buffer.get_uint32(&tracehead);

                        // std::cout << "size " << tracesize << " head " << tracehead << " = " std::hex << tracehead << std::dec << std::endl;

                        if (((tracehead & 0xF0000000) >> 24) != 0xa0)
                        {
                            std::cout << "wrong trace head " << tracehead << std::hex << " = " << tracehead << std::dec << std::endl;
                            continue;
                        }

                        tracesize = 2 * (tracesize / 4 - 2);
                        //traces.at(i).SetLength(tracesize);

                        traces.SetLength(tracesize);

                        for (uint32 t = 0; t < tracesize; t+= 2)
                        {
                            uint32 data = 0;
                            __buffer.get_uint32(&data);
                            int part1 = (data & 0x3FFF);
                            int part2 = ((data >> 16) & 0x3FFFF);

                            //traces.at(i).SetTrace(t, part1);
                            //traces.at(i).SetTrace(t+1, part2);

                            traces.SetTrace(t,part1);
                            traces.SetTrace(t+1, part2);

                        }

                        // hacky? works for lisa_Feb09_test
                        __buffer.advance(4);

                        //traces.at(i).Print();

                        traces.Print();

                    } // header

                } // nchan

                for (int i = 0; i < nchan; i++)
                {
                    //tr.AddTrace(traces.at(i));

                    tr.AddTrace(traces);

                }

                AddTrace(traces);

                std::cout << "fmult: " << tr.GetMult() << std::endl;

                /*for (int i = 0; i < 4000; i++)
                {
                    std::cout << tr.trace_array._items[i] << std::endl;
                }*/

            } // F0

            if (nmod != 0)
            {   
                __buffer.get_uint32(&febex_header);
            }
            else
            {   
                std::cout << "exiting...left in buffer is: " << __buffer.left() << std::endl;
                febex_data = false;
            }

        } // febex data

    } // while buffer is not empty

}

EXT_FORCE_IMPL_DATA_SRC_FCN(void, EXT_TRACES::__unpack);

void EXT_TRACES::dump(const signal_id &id, pretty_dump_info &pdi) const
{
    trEvent.dump(signal_id(id, "trace event"), pdi);
    trace.dump(signal_id(id, "traces"), pdi);
    trace_array.dump(signal_id(id, "trace_array"), pdi);
}

void EXT_TRACES::show_members(const signal_id& id, const char* unit) const
{
    trEvent.show_members(signal_id(id, "trace event"), unit);
    trace.show_members(signal_id(id, "trace"), unit);
}

void EXT_TRACES::enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const
{
    
    trEvent.enumerate_members(__id, __info, __callback, __extra);
    trace.enumerate_members(__id, __info, __callback, __extra);
    /*for (uint32 i = 0; i < SIZE; i++)
    {
        call_enumerate_members(&trace_array._items[i], signal_id(__id, "trace array"), __info, __callback, __extra);
    } */
}

void EXT_TRACES::zero_suppress_info_ptrs(used_zero_suppress_info& used_info)
{
    trEvent.zero_suppress_info_ptrs(used_info);
    trace.zero_suppress_info_ptrs(used_info);
    trace_array.zero_suppress_info_ptrs(used_info); // does this even work..who knows   
}

void TraceEvent::dump(const signal_id &id, pretty_dump_info &pdi) const
{
    ::dump_uint32(fmult, signal_id(id, "fmult"), pdi);
    // dump stuff for trace array
}

void TraceEvent::show_members(const signal_id &id, const char* unit) const
{
    ::show_members<uint32>(signal_id(id, "fmult"), unit);
}

void TraceEvent::zero_suppress_info_ptrs(used_zero_suppress_info &used_info)
{
    // zero suppress
    ::zero_suppress_info_ptrs(&fmult, used_info);
    //trace_array.zero_suppress_info_ptrs(used_info);
    for (int i = 0; i < 4000; i++)
    {   
       // std::cout << trace_array._items[i] << std::endl;
        ::zero_suppress_info_ptrs(&trace_array._items[i], used_info);
    }
}

void TraceEvent::enumerate_members(const signal_id &id, const enumerate_info &info, enumerate_fcn callback, void *extra) const
{   
    // enum
    callback(signal_id(id, "fmult"), enumerate_info(info, &fmult, ENUM_TYPE_UINT), extra);
    //callback(signal_id(id, "trace_array"),enumerate_info(info,&trace_array._num_entries[0],ENUM_TYPE_UINT,0,4000),extra);

    //trace_array.enumerate_members(signal_id(id, "trace array"), info, callback, extra);
    for (int i = 0; i < 4000; i++)
    {
        callback(signal_id(id, "trace_array"), enumerate_info(info, &trace_array._items[i], ENUM_TYPE_UINT), extra);
    }
}

void Trace::dump(const signal_id &id, pretty_dump_info &pdi) const
{
    ::dump_uint32(fboard, signal_id(id, "fboard"), pdi);
    ::dump_uint32(fchn, signal_id(id, "fchn"), pdi);
    ::dump_uint32(fts_lo, signal_id(id, "ts_lo"), pdi);
    ::dump_uint32(fts_hi, signal_id(id, "ts_hi"), pdi);
    ::dump_uint32(fen, signal_id(id, "fen"), pdi);
    ::dump_uint32(flength, signal_id(id, "flength"), pdi);
}

void Trace::show_members(const signal_id &id, const char* unit) const
{
    ::show_members<uint32>(signal_id(id, "fboard"), unit);
    ::show_members<uint32>(signal_id(id, "fchn"), unit);
    ::show_members<uint32>(signal_id(id, "ts_lo"), unit);
    ::show_members<uint32>(signal_id(id, "ts_hi"), unit);
    ::show_members<uint32>(signal_id(id, "fen"), unit);
    ::show_members<uint32>(signal_id(id, "flength"), unit);
}

void Trace::zero_suppress_info_ptrs(used_zero_suppress_info &used_info)
{
    ::zero_suppress_info_ptrs(&fboard, used_info);
    ::zero_suppress_info_ptrs(&fchn, used_info);
    ::zero_suppress_info_ptrs(&fts_lo, used_info);
    ::zero_suppress_info_ptrs(&fts_hi, used_info);
    ::zero_suppress_info_ptrs(&fen, used_info);
    ::zero_suppress_info_ptrs(&flength, used_info);
}

void Trace::enumerate_members(const signal_id &id, const enumerate_info &info, enumerate_fcn callback, void *extra) const
{
    callback(signal_id(id, "fboard"), enumerate_info(info, &fboard, ENUM_TYPE_UINT), extra);
    callback(signal_id(id, "fchn"), enumerate_info(info, &fchn, ENUM_TYPE_UINT), extra);
    callback(signal_id(id, "fts_lo"), enumerate_info(info, &fts_lo, ENUM_TYPE_UINT), extra);
    callback(signal_id(id, "fts_hi"), enumerate_info(info, &fts_hi, ENUM_TYPE_UINT), extra);
    callback(signal_id(id, "fen"), enumerate_info(info, &fen, ENUM_TYPE_UINT), extra);
    callback(signal_id(id, "flength"), enumerate_info(info, &flength, ENUM_TYPE_UINT), extra);
}
