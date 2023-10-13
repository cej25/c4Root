// header link
#include "ext_unpacking.hh"
#include "unpack_structures.hh"

// ucesb internals
#include "data_src.hh"
#include "enumerate.hh"
#include "simple_data_ops.hh"
#include "zero_suppress.hh"
#include "zero_suppress_map.hh"
#include "error.hh"

// c++ stuff
#include <algorithm>
#include <iterator>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>


void EXT_GERMANIUM::load_board_channel_file()
{   
   // std::string = getenv("HOME");
    std::ifstream file("/u/cjones/ucesb/s452/config/Germanium_Detector_Map.txt");

    if (file.fail())
    {
        std::cerr << "Could not find FEBEX Germanium Mapping File" << std::endl;
        exit(0);
    }

    constexpr auto ignore = std::numeric_limits<std::streamsize>::max();

    while (file.good())
    {   

        if (file.peek() == '#')
        {   
            file.ignore(ignore, '\n');
            continue;
        }

        // Board ID     Ch ID       Det Num     Crystal Num
        int board_id, channel_num, det_num, crystal_num;
        file >> board_id >> channel_num >> det_num >> crystal_num;
        
        file.ignore(ignore, '\n');

        // Map board, channel to detector, crystal
        auto board_chan = std::make_pair(board_id, channel_num);
        auto det_crystal = std::make_pair(det_num, crystal_num);
        Germanium_map[board_chan] = det_crystal;
    }
}


EXT_GERMANIUM::EXT_GERMANIUM()
{
    __clean();
}

EXT_GERMANIUM::~EXT_GERMANIUM()
{
}

void EXT_GERMANIUM::__clean()
{
    febex_info.__clean();
}

EXT_DECL_DATA_SRC_FCN(void, EXT_GERMANIUM::__unpack)
{
    
    load_board_channel_file();

    while (!__buffer.empty())
    {   
            
        //std::cout << "Now inside __buffer.empty() loop:" << std::endl;
        //std::cout << "-----------------------------------" << std::endl;

        //auto & item = febex_info.append_item();
        auto & item = febex_info;

        int fired_FEBEX_amount = 0;
        int num_channels_fired = 0;

        bool febex_data = true;

        uint32 num_modules = GE_FEBEX_MODULES;

        uint32 febex_add = 0;
        __buffer.get_uint32(&febex_add); 

        //std::cout << "febex add: " << std::hex << febex_add << std::dec << std::endl;

        // MOST significant 12 bits.
        // can change this to "febex padding"  i think, in line with "tamex padding"
        while ((febex_add & 0xFFF00000) == 0xadd00000)
        {
            
            __buffer.get_uint32(&febex_add);
            //std::cout << "Inside febex_add loop" << std::endl;

           


        }

        // once most significant 12 bits are not "add", "febex_add" becomes "febex_header"
        uint32 febex_header = febex_add;
    
        //std::cout << "febex header: " << std::hex << febex_header << std::dec << std::endl;

        uint32 num_channels = 0;
        uint32 board_id = 0;
        uint32 tmp_sum_time_lo = 0;
        uint32 tmp_sum_time_hi = 0;
        uint32 tmp_chan_energy = 0;
        uint32 deadbeef = 0;
        uint32 febex_chan_header;

        while (febex_data)
        {   
                       
            // most significant byte / 8 bits
            if (((febex_header >> 24) & 0xFF) == 0xFF)
            {   

                //std::cout << "Inside ((febex_header >> 24) & 0xFF) == 0xFF loop" << std::endl; 
                //std::cout << "==================================================" << std::endl;
                
                board_id = ((febex_header >> 16) & 0xFF);
                
                //std::cout << "board id (decimal): " << board_id << std::endl;

                uint32 febex_chan_size = 0;
                __buffer.get_uint32(&febex_chan_size);

                //std::cout <<  "febex_chan_size: " << std::hex << febex_chan_size << std::dec << std::endl;
                //std::cout <<  "febex_chan_size (decimal): "  << febex_chan_size << std::endl;

                // needs to be MOST signficant 30 bits
                num_channels = (((febex_chan_size >> 2) & 0x3FFFFFFF) / 4) - 1;

                //std::cout << "num_channels: " << num_channels << std::endl;
                
                if (num_channels == 0) num_modules--;

                uint32 febex_half_time = 0; // contains hi part of timestamp
                //uint32 tmp_sum_time_lo = 0; // lo part of timestamp

                __buffer.get_uint32(&febex_half_time);
                __buffer.get_uint32(&tmp_sum_time_lo);

                //std::cout <<  "febex_half_time: " << std::hex << febex_half_time << std::dec << std::endl;
                //std::cout <<  "febex_half_time (decimal): " << febex_half_time << std::endl;
                //std::cout <<  "tmp_sum_time_lo: " << std::hex << tmp_sum_time_lo << std::dec << std::endl;
                //std::cout <<  "tmp_sum_time_lo (decimal): " << tmp_sum_time_lo << std::endl;

                tmp_sum_time_hi = (febex_half_time & 0xFFFF); // remove 16 bitshift
                //std::cout << "tmp_sum_time_hi: " << std::hex << tmp_sum_time_hi << std::dec << std::endl;

                // tmp_sum_time = febex_event_time + (tmp_ext_time << 32);
                // std::cout <<  "tmp_sum_time: " << std::dec << tmp_sum_time << std::dec << std::endl;

                uint32 febex_flags = 0;
                __buffer.get_uint32(&febex_flags);

                //std::cout <<  "febex_flags: " << std::hex << febex_flags << std::dec << std::endl;

                uint32 tmp_pileup = ((febex_flags >> 16) & 0xFFFF);
                uint32 tmp_hit_pattern = (febex_flags & 0xFFFF);
                
                //std::cout << "tmp_pileup: " << tmp_pileup << std::endl;
                //std::cout << "tmp_hit_pattern: " << tmp_hit_pattern << std::endl;
                
                for (int i = 15; i >= 0; i--)
                {   
                    if (tmp_pileup & (1 << i))
                    {
                        pileup_flags[i] = 1;
                    }
                    if (tmp_hit_pattern & (1 << i))
                    {   
                        Ge_channels[i] = i;
                        num_channels_fired++;
                    }
                }

                __buffer.get_uint32(&deadbeef);
                //std::cout << "deadbeef: " << std::hex << deadbeef << std::dec << std::endl;

            }

            else if (((febex_header >> 24) & 0xFF) == 0xF0)
            {
                
                //std::cout << "Inside ((febex_header >> 24) & 0xFF) == 0xF0 loop" << std::endl; 
                //std::cout << "==================================================" << std::endl;

                __buffer.reverse(4); // move back a word

                for (uint32 j = 0; j < num_channels; ++j)
                {   

                    //std::cout << "num channels: " << num_channels << ", j: " << j << std::endl;

                    febex_chan_header = 0;
                    __buffer.get_uint32(&febex_chan_header);

                    //std::cout << "febex_chan_header: " << std::hex << febex_chan_header << std::dec << std::endl;

                    int tmp_ch_id = ((febex_chan_header >> 16) & 0xFF);

                    //std::cout <<  "tmp_ch_id (decimal): " << tmp_ch_id << std::endl;

                    auto idx = std::make_pair(board_id, tmp_ch_id);

                    //std::cout << "idx: " << idx.first << ", " << idx.second << std::endl;

                    //std::cout << Germanium_map << std::endl;

                    // not sure if Germanium_map or .find works
                    if (Germanium_map.find(idx) != Germanium_map.end())
                    {   
                        
                        //std::cout << "==========================" << std::endl;
                        //std::cout << "INSIDE GERMANIUM MAP!!!!" << std::endl;
                        //std::cout << "==========================" << std::endl;
                        
                        //Sum_Time[fired_FEBEX_amount] = tmp_sum_time;
                        item.Sum_Time_lo[fired_FEBEX_amount] = tmp_sum_time_lo;
                        item.Sum_Time_hi[fired_FEBEX_amount] = tmp_sum_time_hi;

                        uint32 tmp_chan_ts_lo = 0;
                        __buffer.get_uint32(&tmp_chan_ts_lo);

                        //std::cout << "tmp_chan_ts_lo: " << std::hex << tmp_chan_ts_lo << std::dec << std::endl;

                        uint32 tmp_chan_ts_hi = (febex_chan_header  & 0xFFFF); // least significant 16 bits = hi part of channel ts




                        //Chan_Time[fired_FEBEX_amount] = (febex_chan_ts  + (tmp_ext_chan_ts << 32)) * 10; // nanoseconds
                        item.Chan_Time_lo[fired_FEBEX_amount] = tmp_chan_ts_lo;
                        item.Chan_Time_hi[fired_FEBEX_amount] = tmp_chan_ts_hi;

                        uint32 febex_chan_energy = 0;
                        __buffer.get_uint32(&febex_chan_energy);

                        //std::cout << "febex_chan_energy: " << std::hex << febex_chan_energy << std::dec << std::endl;
                        
                        tmp_chan_energy = (febex_chan_energy & 0xFFFFFF); // should be least signficant 24 bits
                        item.Chan_Energy[fired_FEBEX_amount] = tmp_chan_energy;

                        //tmp_cf = 10.0 * (tmp_chan_ts_lo + ((febex_chan_energy >> 24) & 0x3F) / 64.0);
                        // do calculation in analysis or something
                        item.Chan_CF_lo[fired_FEBEX_amount] = tmp_chan_ts_lo; //lower 32
                        item.Chan_CF_hi[fired_FEBEX_amount] = ((febex_chan_energy >> 24) & 0x3F); // higher 6

                        if (tmp_chan_energy & 0x00800000)
                        {   
                            // sets most significant 8 bits to 0xFF, least significant 24 are tmp_chan_energy
                            uint32 energy = 0xFF000000 | tmp_chan_energy;
                            Chan_Energy[fired_FEBEX_amount] = energy;
                        }

                        item.Pileup[fired_FEBEX_amount] = ((febex_chan_energy >> 30) & 0x01);
                        item.Overflow[fired_FEBEX_amount] = ((febex_chan_energy >> 31) & 0x01);
                        item.det_ids[fired_FEBEX_amount] = Germanium_map[idx].first;
                        item.crystal_ids[fired_FEBEX_amount] = Germanium_map[idx].second;

                        //__buffer.get_uint32(&future_use);
                        __buffer.advance(4);

                        fired_FEBEX_amount++;

                        // TRACES WOULD GO HERE//


                    }
                    else
                    {         
                        // move forward 3 words (32bit int = 4 bytes each)
                        __buffer.advance(12);
                    }

                }

                item.Ge_Fired = fired_FEBEX_amount;

                num_modules--;
            
            }

            if (num_modules != 0)
            {
                __buffer.get_uint32(&febex_header);
            }
            else
            {   
                febex_data = false;
            }
            
        } // while febex_data = true

    } // while buffer isn't empty

}



EXT_FORCE_IMPL_DATA_SRC_FCN(void, EXT_GERMANIUM::__unpack);

void EXT_GERMANIUM::dump(const signal_id &id, pretty_dump_info &pdi) const
{
    // do something
    febex_info.dump(signal_id(id, "febex_info"), pdi);
}

void EXT_GERMANIUM::show_members(const signal_id& id, const char* unit) const
{
    febex_info.show_members(signal_id(id, "febex_info"), unit);
}


void EXT_GERMANIUM::enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const
{
    {
        const signal_id &__shadow_id = __id;
        signal_id __id(__shadow_id, "febex_info");
        {
            febex_info.enumerate_members(__id, __info, __callback, __extra);
        }
    }
}

void EXT_GERMANIUM::zero_suppress_info_ptrs(used_zero_suppress_info& used_info)
{
    febex_info.zero_suppress_info_ptrs(used_info);
}

#ifdef NO_UINT64
#define dump32(name) ::dump_uint32(name, signal_id(id, #name), pdi);
#define show32(name) ::show_members<uint32>(signal_id(id, #name), unit);
#define callback32(name) callback(signal_id(id, #name), enumerate_info(info, &name, ENUM_TYPE_UINT), extra);
#define suppress32(name) ::zero_suppress_info_ptrs(&name, used_info);
#else
#define dump64(name) ::dump_uint64(name, signal_id(id, #name), pdi);
#define show64(name) ::show_members<uint64>(signal_id(id, #name), unit);
#define callback64(name) callback(signal_id(id, #name), enumerate_info(info, &name, ENUM_TYPE_UINT64), extra);
#define suppress64(name) ::zero_suppress_info_ptrs(&name, used_info);
#endif

void febex_item::dump(const signal_id &id, pretty_dump_info &pdi) const
{   
    for (int i = 0; i < GE_MAX_HITS; i++)
    {
        ::dump_uint32(Sum_Time_lo[i], signal_id(id, get_name("Sum_Time_lo_", i)), pdi);
        ::dump_uint32(Sum_Time_hi[i], signal_id(id, get_name("Sum_Time_hi_", i)), pdi);
        ::dump_uint32(Hit_Pattern[i], signal_id(id, get_name("Hit_Pattern_", i)), pdi);
        ::dump_uint32(Chan_Time_lo[i], signal_id(id, get_name("Chan_Time_lo_", i)), pdi);
        ::dump_uint32(Chan_Time_hi[i], signal_id(id, get_name("Chan_Time_hi_", i)), pdi);
        ::dump_uint32(Chan_Energy[i], signal_id(id, get_name("Chan_Energy_", i)), pdi);
        ::dump_uint32(Chan_CF_lo[i], signal_id(id, get_name("Chan_CF_lo_", i)), pdi);
        ::dump_uint32(Chan_CF_hi[i], signal_id(id, get_name("Chan_CF_hi_", i)), pdi);
        ::dump_uint32(Pileup[i], signal_id(id, get_name("Pileup_", i)), pdi); // bool?
        ::dump_uint32(Overflow[i], signal_id(id, get_name("Overflow_", i)), pdi); // bool?
        ::dump_uint32(det_ids[i], signal_id(id, get_name("det_ids_", i)), pdi);
        ::dump_uint32(crystal_ids[i], signal_id(id, get_name("crystal_ids_", i)), pdi);
    }
}

void febex_item::show_members(const signal_id &id, const char* unit) const
{
    for (int i = 0; i < GE_MAX_HITS; i++)
    {
        ::show_members<uint32>(signal_id(id, get_name("Sum_Time_lo_", i)), unit);
        ::show_members<uint32>(signal_id(id, get_name("Sum_Time_hi_", i)), unit);
        ::show_members<uint32>(signal_id(id, get_name("Hit_Pattern_", i)), unit);
        ::show_members<uint32>(signal_id(id, get_name("Chan_Time_lo_", i)), unit);
        ::show_members<uint32>(signal_id(id, get_name("Chan_Time_hi_", i)), unit);
        ::show_members<uint32>(signal_id(id, get_name("Chan_Energy_", i)), unit);
        ::show_members<uint32>(signal_id(id, get_name("Chan_CF_lo_", i)), unit);
        ::show_members<uint32>(signal_id(id, get_name("Chan_CF_hi_", i)), unit);
        ::show_members<uint32>(signal_id(id, get_name("Pileup_", i)), unit); // bool?
        ::show_members<uint32>(signal_id(id, get_name("Overflow_", i)), unit); // bool?
        ::show_members<uint32>(signal_id(id, get_name("det_ids_", i)), unit);
        ::show_members<uint32>(signal_id(id, get_name("crystal_ids_", i)), unit);
    }
}

void febex_item::zero_suppress_info_ptrs(used_zero_suppress_info &used_info)
{
    for (int i = 0; i < GE_MAX_HITS; i++)
    {
        ::zero_suppress_info_ptrs(&Sum_Time_lo[i], used_info);
        ::zero_suppress_info_ptrs(&Sum_Time_hi[i], used_info);
        ::zero_suppress_info_ptrs(&Hit_Pattern[i], used_info);
        ::zero_suppress_info_ptrs(&Chan_Time_lo[i], used_info);
        ::zero_suppress_info_ptrs(&Chan_Time_hi[i], used_info);
        ::zero_suppress_info_ptrs(&Chan_Energy[i], used_info);
        ::zero_suppress_info_ptrs(&Chan_CF_lo[i], used_info);
        ::zero_suppress_info_ptrs(&Chan_CF_hi[i], used_info);
        ::zero_suppress_info_ptrs(&Pileup[i], used_info); // bool?
        ::zero_suppress_info_ptrs(&Overflow[i], used_info); // bool?
        ::zero_suppress_info_ptrs(&det_ids[i], used_info);
        ::zero_suppress_info_ptrs(&crystal_ids[i], used_info);
    }
}

// this function actually writes the stuff to the tree
void febex_item::enumerate_members(const signal_id &id, const enumerate_info &info, enumerate_fcn callback, void *extra) const
{   

    for (int i = 0; i < GE_MAX_HITS; i++)
    {   
        callback(signal_id(id, get_name("Sum_Time_lo_", i)), enumerate_info(info, &Sum_Time_lo[i], ENUM_TYPE_UINT), extra);
        callback(signal_id(id, get_name("Sum_Time_hi_", i)), enumerate_info(info, &Sum_Time_hi[i], ENUM_TYPE_UINT), extra);
        callback(signal_id(id, get_name("Hit_Pattern_", i)), enumerate_info(info, &Hit_Pattern[i], ENUM_TYPE_UINT), extra);
        callback(signal_id(id, get_name("Chan_Time_lo_", i)), enumerate_info(info, &Chan_Time_lo[i], ENUM_TYPE_UINT), extra);
        callback(signal_id(id, get_name("Chan_Time_hi_", i)), enumerate_info(info, &Chan_Time_hi[i], ENUM_TYPE_UINT), extra);
        callback(signal_id(id, get_name("Chan_Energy_", i)), enumerate_info(info, &Chan_Energy[i], ENUM_TYPE_UINT), extra);
        callback(signal_id(id, get_name("Chan_CF_lo", i)), enumerate_info(info, &Chan_CF_lo[i], ENUM_TYPE_UINT), extra);
        callback(signal_id(id, get_name("Chan_CF_hi", i)), enumerate_info(info, &Chan_CF_hi[i], ENUM_TYPE_UINT), extra);
        callback(signal_id(id, get_name("Pileup_", i)), enumerate_info(info, &Pileup[i], ENUM_TYPE_UINT), extra); // bool?
        callback(signal_id(id, get_name("Overflow_", i)), enumerate_info(info, &Overflow[i], ENUM_TYPE_UINT), extra); // bool?
        callback(signal_id(id, get_name("det_ids_", i)), enumerate_info(info, &det_ids[i], ENUM_TYPE_UINT), extra);
        callback(signal_id(id, get_name("crystal_ids_", i)), enumerate_info(info, &crystal_ids[i], ENUM_TYPE_UINT), extra);
        
    }
}

const char* febex_item::get_name(const std::string &name, int index) const
{
    std::ostringstream oss;
    oss << name << index;
    std::string str_name = oss.str();
    const char* cstr_name = str_name.c_str();
    return cstr_name;
} 