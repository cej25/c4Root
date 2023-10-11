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

#define DEBUG_MODE 0

EXT_PLASTIC::EXT_PLASTIC()
{
    __clean();
}

EXT_PLASTIC::~EXT_PLASTIC()
{
}

void EXT_PLASTIC::__clean()
{
    //something clean
    plastic_info.__clean();
}

EXT_DECL_DATA_SRC_FCN(void, EXT_PLASTIC::__unpack)
{   

    if (DEBUG_MODE) std::cout << "======= START EVENT SEPARATOR ======" << std::endl;

    //while (!__buffer.empty())
    //{   
        //auto & item = plastic_info.append_item();
        auto & item = plastic_info;

        item.tamex_end = false;
        item.tamex_iter = 0;

        reset_edges(item);

        while (!item.tamex_end)
        {   
            Process_TAMEX(__buffer, item);
            if (!item.tamex_end)
            {
                item.tamex_iter++;
                __buffer.advance(4);
                /*if (item.tamex_iter > 3)
                {
                    std::cout << "iter over 3" << std::endl;
                }*/
            }   
            //__buffer.advance(4);

        }

        // calibration??
//    }

}

EXT_FORCE_IMPL_DATA_SRC_FCN(void, EXT_PLASTIC::__unpack);

template<typename __data_src_t>
void EXT_PLASTIC::Process_TAMEX(__data_src_t &__buffer, plastic_tamex_item &item)
{
    item.iterator[item.tamex_iter] = 0;
    item.no_edges[item.tamex_iter] = false;

    item.written = false;

    if (item.tamex_iter == 0)
    {
        uint32 trigger_window = 0;
        __buffer.peek_uint32(&trigger_window);

        item.Pre_Trigger_Window = (trigger_window & 0xFFFF);
        item.Post_Trigger_Window = ((trigger_window >> 16) & 0xFFFF);

        __buffer.advance(4);

        skip_padding(__buffer, item);
    }

    uint32 tamex_header = 0;
    __buffer.peek_uint32(&tamex_header);

    bool ongoing = ((tamex_header & 0xFF) == (uint32) item.tamex_identifier) && (((tamex_header >> 24) & 0xFF) == 0) && ((((tamex_header >> 12) & 0xF) == 1) || (((tamex_header >> 12) & 0xF) == 0));
    
    if (!ongoing)
    {
        item.tamex_end = true;
        return;
    }
    if (item.tamex_iter > 0)
    {
        if (((tamex_header >> 16) & 0xFF) <= item.tamex_id[item.tamex_iter - 1])
        {
            item.tamex_end = true;
            return;
        }
    }

    item.sfp_id[item.tamex_iter] = ((tamex_header >> 12) & 0xF);
    item.trigger_type[item.tamex_iter] = ((tamex_header >> 8) & 0xF);
    item.tamex_id[item.tamex_iter] = ((tamex_header >> 16) & 0xFF);

    __buffer.advance(4);

    uint32 tamex_fired = 0;
    __buffer.peek_uint32(&tamex_fired);
    item.am_fired[item.tamex_iter] = (tamex_fired & 0xFFF) / 4 - 2;

    if (DEBUG_MODE) std::cout << "am_fired = " << item.am_fired[item.tamex_iter] << std::endl;

    if (item.am_fired[item.tamex_iter] < 0)
    {
        std::cerr << "NEGATIVE TAMEX FIRED AMOUNT ENCOUNTERED IN bPlast!" << std::endl;
        //exit(0);
        item.error = true;
    }
    else item.error = false;

    __buffer.advance(4);

    uint32 tamex_begin = 0;
    __buffer.peek_uint32(&tamex_begin);
    if (((tamex_begin >> 24) & 0xFF) != (uint32) item.aa)
    {
        std::cerr << "error in TAMEX format! 0xAA... word not found after fired amount!" << std::endl;
        std::cerr << "TAMEX word: " << std::hex << tamex_begin << std::endl;
        item.error = true;
    }
    else item.error = false;

    __buffer.advance(4);

    get_trigger(__buffer, item);

    if (item.am_fired[item.tamex_iter] > 3)
    {
        get_edges(__buffer, item);
    }
    else
    {
        item.no_edges[item.tamex_iter] = true;
    }

    check_trailer(__buffer, item);

}

template<typename __data_src_t>
void EXT_PLASTIC::skip_padding(__data_src_t &__buffer, plastic_tamex_item &item)
{
    bool still_padding = true;
    uint32 padding = 0;
    while (still_padding)
    {
        __buffer.peek_uint32(&padding);

        if (((padding >> 20) & 0xFFF) == 0xADD) // item.add
        {   
            __buffer.advance(4);
        }
        else still_padding = false;
    }
}

template<typename __data_src_t>
void EXT_PLASTIC::get_trigger(__data_src_t &__buffer, plastic_tamex_item &item)
{
    uint32 place_holder = 0;
    __buffer.peek_uint32(&place_holder);

    // unused things with placeholder // error checking
    if (((place_holder >> 28) & 0xF) != 6) // item.six_f
    {
        //std::cerr << "place holder error in TAMEX!" << std::endl;
        tamex_err_count++;
        return;
    }
    else
    {
        if (DEBUG_MODE) std::cout << "we have an epoch? Word: " << std::hex << place_holder << std::dec << std::endl;
    }

    __buffer.advance(4);

    uint32 tamex_data = 0;
    __buffer.peek_uint32(&tamex_data);

    if (DEBUG_MODE)
    {
        if (((tamex_data >> 11) & 0x1) == 1)
        {
            std::cout << "this is a lead... " << std::endl;
            std::cout << "channel.... " << ((tamex_data >> 22) & 0x7F) << std::endl;
        }
        else
        {
            std::cout << "this is a trail... " << std::endl;
            std::cout << "channel.... " << ((tamex_data >> 22) & 0x7F) << std::endl;
        }
    }

    if (item.error == false)
    {
        item.coarse_T[item.tamex_iter] = (double)(tamex_data & 0x7FF);// (double)
        item.fine_T[item.tamex_iter] = (double)((tamex_data >> 12) & 0x3FF);
        item.ch_ID[item.tamex_iter] = ((tamex_data >> 22) & 0x7F);
    }

    __buffer.advance(4);
}

void EXT_PLASTIC::reset_edges(plastic_tamex_item &item)
{
    for (int i = 0; i < 4; i++) ///??????
    {
        for (int j = 0; j < PLASTIC_MAX_ITER; ++j)
        {
            //item.leading_hits[i][j] = 0; // unused
            //item.trailing_hits[i][j] = 0; // unused
            // ---- CEJ: these were all 131313 in g04 code ---- 
            item.ch_num[i][j] = 0;
            item.edge_coarse[i][j] = 0;
            item.edge_fine[i][j] = 0;
            item.ch_ID_edge[i][j] = 0;
        }
    }
}

template<typename __data_src_t>
void EXT_PLASTIC::get_edges(__data_src_t &__buffer, plastic_tamex_item &item)
{
    item.iterator[item.tamex_iter] = 0;

    item.written = false;

    while (no_error_reached(__buffer, item))
    {   

        uint32 place_holder = 0;
        __buffer.peek_uint32(&place_holder);

        if (((place_holder >> 28) & 0xF) != (uint32) item.six_f && item.written)
        {   
            if (DEBUG_MODE)
            {
                std::cout << "Data word: " << std::hex << place_holder << std::dec << std::endl;
                std::cout << "lead or trail!! " << ((place_holder >> 11) & 0x1) << std::endl;
                std::cout << "channel!! " << ((place_holder >> 22) & 0x7F) << std::endl;
            } 
            
            __buffer.advance(4);
            continue;
        }
        else if (((place_holder >> 28) & 0xF) == (uint32) item.six_f)
        {   
            if (DEBUG_MODE) std::cout << "we have an epoch? Word: " << std::hex << place_holder << std::dec << std::endl;
            item.written = false;
        }


         // unused things with placeholder // error checking
        /*if (((place_holder >> 28) & 0xF) != item.six_f)
        {
            std::cerr << "place holder error in TAMEX!" << std::endl;
            //return;
            break;
        }*/

        __buffer.advance(4);

        uint32 tamex_data = 0;
        __buffer.peek_uint32(&tamex_data);

        if (DEBUG_MODE)
        {
            if (((tamex_data >> 11) & 0x1) == 1)
            {
                std::cout << "this is a lead... " << std::endl;
                std::cout << "channel.... " << ((tamex_data >> 22) & 0x7F) << std::endl;
            }
            else
            {
                std::cout << "this is a trail... " << std::endl;
                std::cout << "channel.... " << ((tamex_data >> 22) & 0x7F) << std::endl;
            }
        }

        if (((tamex_data >> 11) & 0x1) == 0)
        {
            std::cout << "this is a trail... " << std::endl;
            std::cout << "channel.... " << ((tamex_data >> 22) & 0x7F) << std::endl;
            std::cout << "fine time... " << ((tamex_data >> 12) & 0x3FF) << std::endl;
            std::cout << "data word: " << std::hex << tamex_data << std::dec << std::endl;
            std::cout << "trigger must be 3? " << item.trigger_type[item.tamex_iter] << std::endl;
        }

        if (item.iterator[item.tamex_iter] > 100) break;
        if (item.error == true) break;

        item.edge_coarse[item.tamex_iter][item.iterator[item.tamex_iter]] = (double) (tamex_data & 0x7FF);
        item.edge_fine[item.tamex_iter][item.iterator[item.tamex_iter]] = (double) ((tamex_data >> 12) & 0x3FF);
        item.ch_ID_edge[item.tamex_iter][item.iterator[item.tamex_iter]] = ((tamex_data >> 22) & 0x7F);
        
        item.lead_arr[item.tamex_iter][item.iterator[item.tamex_iter]] = (((tamex_data >> 22) & 0x7F) % 2); // this bit is wrong?

        if (item.ch_ID_edge[item.tamex_iter][item.iterator[item.tamex_iter]] % 2 == 0) 
        {
            item.ch_num[item.tamex_iter][item.iterator[item.tamex_iter]] = (item.ch_ID_edge[item.tamex_iter][item.iterator[item.tamex_iter]]) / 2 - 1;
        }
        else
        {
            item.ch_num[item.tamex_iter][item.iterator[item.tamex_iter]] = (item.ch_ID_edge[item.tamex_iter][item.iterator[item.tamex_iter]] + 1) / 2 - 1;
        }

        item.iterator[item.tamex_iter]++;
        item.written = true;

        __buffer.advance(4);
    }
}

template<typename __data_src_t>
bool EXT_PLASTIC::no_error_reached(__data_src_t &__buffer, plastic_tamex_item &item)
{
    uint32 tamex_error = 0;
    __buffer.peek_uint32(&tamex_error);

    // 238 or "error_code"
    return (((tamex_error >> 24) & 0xFF) != 238); // item.error_code
}

template<typename __data_src_t>
void EXT_PLASTIC::check_trailer(__data_src_t &__buffer, plastic_tamex_item &item)
{
    __buffer.advance(4); // skips past error

    uint32 tamex_trailer = 0;
    __buffer.peek_uint32(&tamex_trailer);

    if (((tamex_trailer >> 24) & 0xFF) != 187) // item.trailer_code
    {
        // std::cout << 
    }

}


/*
void EXT_PLASTIC::dump(const signal_id &id, pretty_dump_info &pdi) const
{
    if (!IS_PLASTIC_TWINPEAKS)
    {
        plastic_info.dump(signal_id(id, "plastic_info"), pdi);
    }
}

void EXT_PLASTIC::show_members(const signal_id& id, const char* unit) const
{   
    if (!IS_PLASTIC_TWINPEAKS)
    {
        plastic_info.show_members(signal_id(id, "plastic_info"), unit);
    }
}

void EXT_PLASTIC::enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const
{   
    if (!IS_PLASTIC_TWINPEAKS)
    {
        {
            const signal_id &__shadow_id = __id;
            signal_id __id(__shadow_id, "plastic_info");
            {
                plastic_info.enumerate_members(__id, __info, __callback, __extra);
            }
        }
    }
}

void EXT_PLASTIC::zero_suppress_info_ptrs(used_zero_suppress_info& used_info)
{   
    if (!IS_PLASTIC_TWINPEAKS)
    {
        plastic_info.zero_suppress_info_ptrs(used_info);
    }
}

void plastic_tamex_item::dump(const signal_id &id, pretty_dump_info &pdi) const
{
    for (int i = 0; i < 4; i++) // could be PLASTIC_MAX_ITER but only needs to be 3,4
    {   
        ::dump_uint32(am_fired[i], signal_id(id, get_name("am_fired_", i)), pdi);
        ::dump_uint32(sfp_id[i], signal_id(id, get_name("sfp_id_", i)), pdi);
        ::dump_uint32(trigger_type[i], signal_id(id, get_name("trigger_type_", i)), pdi);

        ::dump_double(coarse_T[i], signal_id(id, get_name("coarse_T_", i)), pdi);
        ::dump_double(fine_T[i], signal_id(id, get_name("fine_T_", i)), pdi);
        ::dump_uint32(ch_ID[i], signal_id(id, get_name("ch_ID_", i)), pdi);

        ::dump_uint32(iterator[i], signal_id(id, get_name("iterator_", i)), pdi);
        ::dump_uint32(tamex_id[i], signal_id(id, get_name("tamex_id_", i)), pdi);

        for (int j = 0; j < PLASTIC_MAX_ITER; j++)
        {
            ::dump_uint32(lead_arr[i][j], signal_id(id, get_name2("lead_arr_", i, j)), pdi);
            ::dump_double(edge_coarse[i][j], signal_id(id, get_name2("edge_coarse", i, j)), pdi); // there is some issue here. edge_coarse works but edge_coarse_ doesn't for double digit <j>s
            ::dump_double(edge_fine[i][j], signal_id(id, get_name2("edge_fine_", i, j)), pdi);
            ::dump_uint32(ch_ID_edge[i][j], signal_id(id, get_name2("ch_ID_edge_", i, j)), pdi);
            ::dump_uint32(ch_num[i][j], signal_id(id, get_name2("ch_num_", i, j)), pdi);

        }
    }
}

void plastic_tamex_item::show_members(const signal_id& id, const char* unit) const
{   
    for (int i = 0; i < 4; i++)
    {   
        ::show_members<uint32>(signal_id(id, get_name("am_fired_", i)), unit);
        ::show_members<uint32>(signal_id(id, get_name("sfp_id_", i)), unit);
        ::show_members<uint32>(signal_id(id, get_name("trigger_type_", i)), unit);

        ::show_members<double>(signal_id(id, get_name("coarse_T_", i)), unit);
        ::show_members<double>(signal_id(id, get_name("fine_T_", i)), unit);
        ::show_members<uint32>(signal_id(id, get_name("ch_ID_", i)), unit);

        ::show_members<uint32>(signal_id(id, get_name("iterator_", i)), unit);
        ::show_members<uint32>(signal_id(id, get_name("tamex_id_", i)), unit);

        for (int j = 0; j < PLASTIC_MAX_ITER; j++)
        {
            ::show_members<uint32>(signal_id(id, get_name2("lead_arr_", i, j)), unit);
            ::show_members<double>(signal_id(id, get_name2("edge_coarse", i, j)), unit);
            ::show_members<double>(signal_id(id, get_name2("edge_fine_", i, j)), unit);
            ::show_members<uint32>(signal_id(id, get_name2("ch_ID_edge_", i, j)), unit);
            ::show_members<uint32>(signal_id(id, get_name2("ch_num_", i, j)), unit);
        }
    }
}

void plastic_tamex_item::enumerate_members(const signal_id &id, const enumerate_info &info, enumerate_fcn callback, void *extra) const
{   
    for (int i = 0; i < 4; i++)
    {   
        callback(signal_id(id, get_name("am_fired_", i)), enumerate_info(info, &am_fired[i], ENUM_TYPE_UINT), extra);
        callback(signal_id(id, get_name("sfp_id_", i)), enumerate_info(info, &sfp_id[i], ENUM_TYPE_UINT), extra);
        callback(signal_id(id, get_name("trigger_type_", i)), enumerate_info(info, &trigger_type[i], ENUM_TYPE_UINT), extra);

        callback(signal_id(id, get_name("coarse_T_", i)), enumerate_info(info, &coarse_T[i], ENUM_TYPE_DOUBLE), extra);
        callback(signal_id(id, get_name("fine_T_", i)), enumerate_info(info, &fine_T[i], ENUM_TYPE_DOUBLE), extra);
        callback(signal_id(id, get_name("ch_ID_", i)), enumerate_info(info, &ch_ID[i], ENUM_TYPE_UINT), extra);

        callback(signal_id(id, get_name("iterator_", i)), enumerate_info(info, &iterator[i], ENUM_TYPE_UINT), extra);
        callback(signal_id(id, get_name("tamex_id_", i)), enumerate_info(info, &tamex_id[i], ENUM_TYPE_UINT), extra);

        for (int j = 0; j < PLASTIC_MAX_ITER; j++)
        {

            callback(signal_id(id, get_name2("lead_arr_", i, j)), enumerate_info(info, &lead_arr[i][j], ENUM_TYPE_UINT), extra);
            callback(signal_id(id, get_name2("edge_coarse", i, j)), enumerate_info(info, &edge_coarse[i][j], ENUM_TYPE_DOUBLE), extra);
            callback(signal_id(id, get_name2("edge_fine_", i, j)), enumerate_info(info, &edge_fine[i][j], ENUM_TYPE_DOUBLE), extra);
            callback(signal_id(id, get_name2("ch_ID_edge_", i, j)), enumerate_info(info, &ch_ID_edge[i][j], ENUM_TYPE_UINT), extra);
            callback(signal_id(id, get_name2("ch_num_", i, j)), enumerate_info(info, &ch_num[i][j], ENUM_TYPE_UINT), extra);
        }

    }
}    

void plastic_tamex_item::zero_suppress_info_ptrs(used_zero_suppress_info& used_info)
{
    for (int i = 0; i < 4; i++)
    {
        ::zero_suppress_info_ptrs(&am_fired[i], used_info);
        ::zero_suppress_info_ptrs(&sfp_id[i], used_info);
        ::zero_suppress_info_ptrs(&trigger_type[i], used_info);

        ::zero_suppress_info_ptrs(&coarse_T[i], used_info);
        ::zero_suppress_info_ptrs(&fine_T[i], used_info);
        ::zero_suppress_info_ptrs(&ch_ID[i], used_info);

        ::zero_suppress_info_ptrs(&iterator[i], used_info);
        ::zero_suppress_info_ptrs(&tamex_id[i], used_info);

        for (int j = 0; j < PLASTIC_MAX_ITER; j++)
        {
            ::zero_suppress_info_ptrs(&lead_arr[i][j], used_info);
            ::zero_suppress_info_ptrs(&edge_coarse[i][j], used_info);
            ::zero_suppress_info_ptrs(&edge_fine[i][j], used_info);
            ::zero_suppress_info_ptrs(&ch_ID_edge[i][j], used_info);
            ::zero_suppress_info_ptrs(&ch_num[i][j], used_info);
        }
    }
}
*/
const char* plastic_tamex_item::get_name(const std::string &name, int index) const
{
    std::ostringstream oss;
    oss << name << index;
    std::string str_name = oss.str();
    const char* cstr_name = str_name.c_str();
    return cstr_name;
} 

const char* plastic_tamex_item::get_name2(const std::string &name, int index, int index2) const
{
    std::ostringstream oss;
    oss << name << index << "_" << index2;
    std::string str_name = oss.str();
    const char* cstr_name = str_name.c_str();
    return cstr_name;
} 