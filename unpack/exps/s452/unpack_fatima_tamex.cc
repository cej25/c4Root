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

EXT_FATIMA_TAMEX::EXT_FATIMA_TAMEX()
{
    __clean();
}

EXT_FATIMA_TAMEX::~EXT_FATIMA_TAMEX()
{
}

void EXT_FATIMA_TAMEX::__clean()
{
    //something clean
    fat_tamex_info.__clean();
}

EXT_DECL_DATA_SRC_FCN(void, EXT_FATIMA_TAMEX::__unpack)
{   

    while (!__buffer.empty())
    {   
        auto & item = fat_tamex_info.append_item();

        // reset stuff - can be done with clean?
        reset_edges(item); //

        item.tamex_end = false;
        item.tamex_iter = 0;

        while (!item.tamex_end)
        {   

            Process_TAMEX(__buffer, item);
            /*if (!item.tamex_end) item.tamex_iter++;

            // i think this is causing uint64 wraparound issue
            // even tho we've ended, we've advanced the buffer, so now a new item
            __buffer.advance(4);*/

            //////// TEST //////// -- this seems to work, need to check actual unpack though
            if (!item.tamex_end)
            {
                item.tamex_iter++;
                __buffer.advance(4);
            }

        }


        // CALIBRATION ??
        /*
        if (item.CALIBRATE) calibrate_ONLINE();
        else calibrate_OFFLINE();
        */

    }
}

EXT_FORCE_IMPL_DATA_SRC_FCN(void, EXT_FATIMA_TAMEX::__unpack);


void EXT_FATIMA_TAMEX::reset_edges(fatima_tamex_item &item)
{   

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 200; j++)
        {
            item.leading_hits[i][j] = 0;
            item.trailing_hits[i][j] = 0;
            item.edge_coarse[i][j] = (double) 131313;
            item.edge_fine[i][j] = (double) 131313;
            item.ch_ID_edge[i][j] = (double) 131313;
        }
    }
}

template<typename __data_src_t>
void EXT_FATIMA_TAMEX::Process_TAMEX(__data_src_t &__buffer, fatima_tamex_item &item)
{   

    item.iterator[item.tamex_iter] = 0;
    item.no_edges[item.tamex_iter] = false;

    item.written = false;

    // check for trigger window (beginning of TAMEX MBS
    if (item.tamex_iter == 0)
    {
        uint32 window = 0;
        __buffer.peek_uint32(&window);

        item.Pre_Trigger_Window = (window & 0xFFFF); // least significant 16 bits
        item.Post_Trigger_Window = ((window >> 16) & 0xFFFF); // most significant 16 bits

        __buffer.advance(4);

        skip_padding(__buffer);

    }

    uint32 tamex_header = 0;
    __buffer.peek_uint32(&tamex_header);

    bool ongoing = ((tamex_header & 0xFF) == (uint32)item.tamex_identifier) && (((tamex_header >> 24) & 0xFF) == 0) && ((((tamex_header >> 12) & 0xF) == 1) || (((tamex_header >> 12) & 0xF) == 0));

    if (!ongoing)
    {
        item.tamex_end = true;
        return;
    }

    if (item.tamex_iter > 0)
    {
        if (((tamex_header >> 16) & 0xFF) <= (uint32) item.tamex_id[item.tamex_iter - 1])
        {   
            item.tamex_end = true;
            return;
        }
    }

    item.sfp_id[item.tamex_iter] = ((tamex_header >> 12) & 0xF);
    item.trigger_type[item.tamex_iter] = ((tamex_header >> 8) & 0xF);
    item.tamex_id[item.tamex_iter] = ((tamex_header >> 16) & 0xFF);

    __buffer.advance(4);

    uint32 tamex_fire = 0;
    __buffer.peek_uint32(&tamex_fire);

    item.am_fired[item.tamex_iter] = (tamex_fire & 0xFFF) / 4 - 2;
    if (item.am_fired[item.tamex_iter] < 0)
    {
        std::cerr << "NEGATIVE TAMEX FIRED AMOUNT ENCOUNTERED IN FATIMA" << std::endl;
        //exit(0);
    }

    __buffer.advance(4);

    uint32 tamex_begin = 0;
    __buffer.peek_uint32(&tamex_begin);

    if (((tamex_begin >> 24) & 0xFF) != 0xAA)
    {
        std::cerr << "error in TAMEX format! 0xAA...word not found after fired amount!" << std::endl;
        std::cerr << "TAMEX WORD: " << std::hex << tamex_begin << std::endl;
    }

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

    check_trailer(__buffer);

}

template<typename __data_src_t>
void EXT_FATIMA_TAMEX::skip_padding(__data_src_t &__buffer)
{
    bool still_padding = true;
    while (still_padding)
    {
        uint32 padding = 0;
        __buffer.peek_uint32(&padding);
        if (((padding >> 20) & 0xFFF) == 0xADD)
        {
            __buffer.advance(4);
        } 
        else 
        {
            still_padding = false;
        }
    }
}

template<typename __data_src_t>
void EXT_FATIMA_TAMEX::get_trigger(__data_src_t &__buffer, fatima_tamex_item &item)
{
    uint32 place_holder = 0;
    __buffer.peek_uint32(&place_holder);

    // unused things with placeholder

    __buffer.advance(4);

    uint32 tamex_data = 0;
    __buffer.peek_uint32(&tamex_data);

    item.coarse_T[item.tamex_iter] = (double) (tamex_data & 0x7FF);
    item.fine_T[item.tamex_iter] = (double) ((tamex_data >> 12) & 0x3FF);
    item.ch_ID[item.tamex_iter] = ((tamex_data >> 22) & 0x7F);

    __buffer.advance(4);
}

template<typename __data_src_t>
void EXT_FATIMA_TAMEX::get_edges(__data_src_t &__buffer, fatima_tamex_item &item)
{   
    // set iterator[tamex_iter] of edges to 0
    item.iterator[item.tamex_iter] = 0;

    // loop over remaining words (getting leading and trailing edge data)
    item.written = false;

    while (no_error_reached(__buffer))
    {
        uint32 place_holder = 0;
        __buffer.peek_uint32(&place_holder);

        // == six_f instead of == 6? even though six_f = 6? check Go4
        if (((place_holder >> 28) & 0xF) == 6)
        {
            __buffer.advance(4);
            continue;
        }

        if (((place_holder >> 28) & 0xF) != 6)
        {
            item.written = false;
        }

        uint32 tamex_data = 0;
        __buffer.peek_uint32(&tamex_data);

        if (((tamex_data >> 11) & 0x1) == 1)
        {
            item.leading_hit = ((tamex_data >> 11) & 0x1);
            item.edge_coarse[item.tamex_iter][item.iterator[item.tamex_iter]] = (double) (tamex_data & 0x7FF);
            item.edge_fine[item.tamex_iter][item.iterator[item.tamex_iter]] = (double) ((tamex_data >> 12) & 0x3FF);
            item.ch_ID_edge[item.tamex_iter][item.iterator[item.tamex_iter]] = ((tamex_data >> 22) & 0x7F);
            item.lead_arr[item.tamex_iter][item.iterator[item.tamex_iter]] =  (((tamex_data >> 22) & 0x7F) % 2);
        }

        if (((tamex_data >> 11) & 0x1) == 0)
        {
            item.leading_hit = ((tamex_data >> 11) & 0x1);
            item.edge_coarse[item.tamex_iter][item.iterator[item.tamex_iter]] = (double) (tamex_data & 0x7FF);
            item.edge_fine[item.tamex_iter][item.iterator[item.tamex_iter]] = (double) ((tamex_data >> 12) & 0x3FF);
            item.ch_ID_edge[item.tamex_iter][item.iterator[item.tamex_iter]] = ((tamex_data >> 22) & 0x7F) + MAX_CHA_INPUT;
        }

        item.iterator[item.tamex_iter]++;
        item.written = true;

        __buffer.advance(4);
    }
}

template<typename __data_src_t>
bool EXT_FATIMA_TAMEX::no_error_reached(__data_src_t &__buffer)
{
    uint32 tamex_error = 0;
    __buffer.peek_uint32(&tamex_error);

    // "error code" vs 238? check go4
    return ((tamex_error >> 24) & 0xFF) != 238; 

}


template<typename __data_src_t>
void EXT_FATIMA_TAMEX::check_trailer(__data_src_t &__buffer)
{
    __buffer.advance(4);

    uint32 tamex_trailer = 0;
    __buffer.peek_uint32(&tamex_trailer);

    // trailer_code instead of 187? check Go4
    if (((tamex_trailer >> 24) & 0xFF) != 187)
    {
        // std::cerr << "Unknown TAMEX trailer format!" << std::endl;
        // exit(0);
    }
}

void EXT_FATIMA_TAMEX::calibrate_ONLINE()
{

}

void EXT_FATIMA_TAMEX::dump(const signal_id &id, pretty_dump_info &pdi) const
{
}

void EXT_FATIMA_TAMEX::show_members(const signal_id& id, const char* unit) const
{
}

void EXT_FATIMA_TAMEX::enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const
{
}

void EXT_FATIMA_TAMEX::zero_suppress_info_ptrs(used_zero_suppress_info& used_info)
{
}