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

EXT_FATIMA_VME::EXT_FATIMA_VME()
{
    __clean();
}

EXT_FATIMA_VME::~EXT_FATIMA_VME()
{
}

void EXT_FATIMA_VME::__clean()
{
    //something clean
    fatima_vme_info.__clean();
}

void EXT_FATIMA_VME::load_board_channel_file()
{
    const char* format = "%d %d %d %d %d %d";

    std::ifstream file("${HOME}/ucesb/s452/config/FATIMA_VME_allocation.txt");

    if (file.fail())
    {
        std::cerr << "Could not find QDC_FATIMA Board_Channel to DetNum file!" << std::endl;
        exit(0);
    }

    std::string line;
    int detector_number, board_id, channel_num, board_id_TDC, TDC_ch, enabled;

    while (file.good())
    {
        getline(file, line, '\n');
        if (line[0] == '#') continue;
        sscanf(line.c_str(), format, &detector_number, &board_id,
        &channel_num, &board_id_TDC, &TDC_ch, &enabled);
        if (enabled == 1)
        {
            det_ID_QDC[board_id][channel_num] = detector_number;
            det_ID_TDC[board_id_TDC][TDC_ch] = detector_number;
        }
    }

}

EXT_DECL_DATA_SRC_FCN(void, EXT_FATIMA_VME::__unpack)
{   

    load_board_channel_file();

    while (!__buffer.empty())
    {   
        auto &fat_info = fatima_vme_info.append_item();

        uint32 sc_geo = 15;
        if (SCALER_MODULE_ON == 1)
        {   
            if (CHECK_SCALER_DATA(__buffer, sc_geo, fat_info) < 1)
            {
                // in go4 this is this->pdata. Not required here.
            }
        }

        int nqdc = 0;

        for (int qdcboards = 0; qdcboards < 5; qdcboards++)
        {
            uint32 QDC_header = 0;

            // perhaps we can use peek so we don't advance buffer?
            __buffer.peek_uint32(&QDC_header);

            if (((QDC_header >> 28) & 0xF) == 10 && (QDC_header & 0xFFFFFF) == 4)
            {   

                for (int i = 0; i < 4; ++i) // I 
                {
                    // advance data buffer
                    __buffer.advance(4);
                    
                }

                nqdc++;
            }
            else if (((QDC_header >> 28) & 0xF) == 10)
            {
                
                if (!CHECK_QDC_DATA(__buffer, fat_info))
                {   
                    std::cout << "WARNING: FATIMA QDC readout error" << std::endl;
                }

                nqdc++;

            }
            else
            {   
                std::cout << "WARNING: FATIMA QDC readout encountered unknown header" << std::endl;
                break;
            }

            // more hacky bullshit
            if (__buffer.left() == 0)
            {
                break;
            }

        }
        
        //uint32 TDC_header = 0;
        //__buffer.get_uint32(&TDC_header);
        int num_TDC_modules = 0;
        for (int i = 0; i < FAT_TDC_NUMBER; i++)
        {
            if (CHECK_TDC_DATA(__buffer, fat_info))
            {   
                num_TDC_modules++;
            }
            else
            {   
                std::cout << "WARNING: FATIMA TDC readout error" << std::endl;
            }

            // hacky?
            if (__buffer.left() == 0)
            {
                break;
            }
        }

        if (num_TDC_modules != FAT_TDC_NUMBER)
        {
            std::cout << "WARNING: FATIMA TDC readout error. Only found " << num_TDC_modules << " of " << FAT_TDC_NUMBER << " TDCs." << std::endl;
        }
        
    } // buffer empty
}

EXT_FORCE_IMPL_DATA_SRC_FCN(void, EXT_FATIMA_VME::__unpack);

template<typename __data_src_t>
int EXT_FATIMA_VME::CHECK_SCALER_DATA(__data_src_t &__buffer, uint32 &geo, fatima_vme_item &fat_info)
{   
    int Scaler_iterator = 0;
    uint32 sc_header = 0;
    __buffer.peek_uint32(&sc_header);

    int nwords = 0;

    if (((sc_header & 0xF8000000) >> 27) == geo)
    {
        nwords = ((sc_header & 0x1F00) >> 8);

        uint32 scaler_data = 0;
        for (int i = 0; i < nwords; i++)
        {   
            
            __buffer.advance(4);
            __buffer.peek_uint32(&scaler_data);
            fat_info.Scaler_Data[Scaler_iterator] = scaler_data;
            Scaler_iterator++;
        }

        __buffer.advance(4);
        uint32 scaler_trailer = 0;
        __buffer.peek_uint32(&scaler_trailer);

        if (scaler_trailer != (uint32) (geo << 27) + 0x400000)
        {
            // std::cout << "Correct trailer word" << std::endl;
        }
        else
        {
            std::cout << "WARNING: FATIMA SCALER readout, trailer not found" << std::endl;
        }

        __buffer.advance(4);
        return 1;
    }
    else if (sc_header == 0x06000000)
    {   
        // Filler word, no scaler data
        __buffer.advance(4);
        return 1;
    }
    else
    {
        std::cout << "WARNING: FATIMA SCALER enabled but not found. " << std::endl;
        std::cout << "Readout sequence is SCALER-QDC-TDC." << std::endl;
        return 0;
    }
}


template<typename __data_src_t>
int EXT_FATIMA_VME::CHECK_QDC_DATA(__data_src_t &__buffer, fatima_vme_item &fat_info)
{   

    __buffer.advance(4);
    uint32 QDC_head_2 = 0;
    __buffer.peek_uint32(&QDC_head_2);
    
    int board_ID = ((QDC_head_2 >> 27) & 0x1F); // most significant 5 bits
    int num_Channels = (QDC_head_2 & 0xFF); // least significant 8 bits
    int num_channels_fired = 0;

    if (board_ID != 13)
    {   
        // loop retrieves channels fired from integer value
        for (int j = 7; j >= 0; j--)
        {   
            if (num_Channels >= (int) pow(2, j))
            {   
                // fill Fired_Channel array with corresponding ids
                if (wired_QDC(board_ID, j, fat_info))
                {
                    fat_info.Fired_QDC_Channels[num_channels_fired][0] = board_ID;
                    fat_info.Fired_QDC_Channels[num_channels_fired][1] = j;
                    num_channels_fired++;
                }
                else
                {
                    fat_info.Fired_QDC_Channels[num_channels_fired][0] = board_ID;
                    fat_info.Fired_QDC_Channels[num_channels_fired][1] = -1;
                    num_channels_fired++;
                }
                num_Channels -= (int) pow(2, j);
            }
        }

        // move from 2nd to 4th header value
        __buffer.advance(8);

        int active_Channel = 0;
        int active_board = 0;
        int active_det = 0;
        //double fine_time = 0; // unused atm
        int fired_QDC_amount = 0;

        for (int i = (num_channels_fired - 1); i >= 0; --i)
        {
            __buffer.advance(4);
            uint32 QDC_format_size = 0;
            __buffer.peek_uint32(&QDC_format_size);

            if (fat_info.Fired_QDC_Channels[i][1] == -1)
            {
                std::cout << "WARNING: FATIMA channel ID = -1!" << std::endl;
                return 0;
            }
            else
            {
                active_board = fat_info.Fired_QDC_Channels[i][0];
                active_Channel = fat_info.Fired_QDC_Channels[i][0];
                active_det = det_ID_QDC[active_board][active_Channel];
                fat_info.det_ids_QDC[fired_QDC_amount] = active_det;

                // advance 3 words
                __buffer.advance(12);

                uint32 QDC_time = 0;
                __buffer.peek_uint32(&QDC_time);
                fat_info.QDC_Time_Coarse[fired_QDC_amount] = QDC_time; // all 32 bits
                // No need for Time_Coarse_lo and Time_Coarse_hi in this instance then.

                __buffer.advance(4);
                uint32 QDC_extras = 0;
                __buffer.peek_uint32(&QDC_extras);

                // must be careful to take care of time stuff in analyis.
                // Here is unpacked as UINT32 only. There are doubles and 64bit ints required...

                fat_info.QDC_Time_Ext[fired_QDC_amount] = ((QDC_extras >> 16) & 0xFFFF);
                fat_info.QDC_Time_Fine[fired_QDC_amount] = (QDC_extras & 0x3FF); // least significant 10

                __buffer.advance(4);
                uint32 QDC_data = 0;
                __buffer.peek_uint32(&QDC_data);

                fat_info.QLong_Raw[fired_QDC_amount] = ((QDC_data >> 16) & 0xFFFF); 
                fat_info.QShort_Raw[fired_QDC_amount] = (QDC_data & 0x7FFF); // least significant 15

                // calibrate here??
                Calibrate_QDC(fired_QDC_amount);
                
                fired_QDC_amount++;

            }

        }

        __buffer.advance(4);

        return 1;
    }

    else 
    {
        std::cout << "WARNING: FATIMA QDC readout, unknown ID 13." << std::endl;
        __buffer.advance(4);
        return 0;
    }
}

template<typename __data_src_t>
int EXT_FATIMA_VME::CHECK_TDC_DATA(__data_src_t &__buffer, fatima_vme_item &fat_info)
{   
    bool trail = false;

    int check = 0;
    int tdc_board_ID = 0;
    int TDC_channel = 0;
    int active_det = 0;
    //bool no_data = true;

    int loop_counter = 0;
    int fired_TDC_amount = 0;

    while (!trail)
    {
        loop_counter++;

        uint32 TDC_check = 0;
        __buffer.peek_uint32(&TDC_check);

        check = ((TDC_check >> 27) & 0x1F); // most significant 5 bits

        if (TDC_check == 0x06000000)
        {   
            // empty TDC
            __buffer.advance(4);
            return 1;
        }
        else if (check == 8)
        {
            // don't get this bit, "global header" is same as "check"?
            tdc_board_ID = (TDC_check & 0x1F);
            __buffer.advance(4);
        }
        else if (check == 1) // TDC header condition
        {
            __buffer.advance(4);
        }
        else if (check == 0)
        {   
            TDC_channel = ((TDC_check >> 21) & 0x1F);
            if (!wired_TDC(tdc_board_ID, TDC_channel, fat_info))
            {
                //no_data = true;
            }
            else
            {   
                active_det = det_ID_TDC[tdc_board_ID][TDC_channel];
                fat_info.det_ids_TDC[fired_TDC_amount] = active_det;
                fat_info.TDC_Time_Raw[fired_TDC_amount] = (TDC_check & 0x1FFFF); // least significant 21 bits
                Calibrate_TDC(fired_TDC_amount);
                Calibrate_TDC(fired_TDC_amount); // wtf? why twice?
                fired_TDC_amount++;
                //no_data = false;
            }
            __buffer.advance(4);
        }
        else if (check == 16)
        {
            __buffer.advance(4);
            return 1;
        }
        else 
        {   
            // fix this somehow
            std::cout << "WARNING: FATIMA TDC wrong - header is " << std::hex << TDC_check << std::dec << std::endl;
            __buffer.advance(4);
        }

        if (loop_counter > 100)
        {
            std::cerr << "WARNING: FATIMA TDC loop not reaching trailer! data iteration problem possible." << std::endl;
            __buffer.advance(4);
            return 0;
        }
    }
    std::cout << "ERROR: FATIMA should never get here!" << std::endl;
    return 0;
    
}

bool EXT_FATIMA_VME::wired_QDC(int board_id, int ch_num, fatima_vme_item &fat_info)
{   
    // alternatively just store ints?
    return det_ID_QDC[board_id][ch_num] != -1;
}

bool EXT_FATIMA_VME::wired_TDC(int board_id, int ch_num, fatima_vme_item &fat_info)
{   
    return det_ID_TDC[board_id][ch_num] != -1;
}

void EXT_FATIMA_VME::Calibrate_QDC(int id)
{   

    // not sure if this can be done tbh...maybe in analysis? times are not correct

    /*Q_Long[id] = FATIMA_E_CALIB->Calibrate(QLong_Raw[id], det_ids_QDC[id]);
    QDC_Time_Coarse[id] = FATIMA_T_CALIB->Calibrate_QDC(QDC_Time_Coarse[id], det_ids_TDC[id]);
    QDC_Time_Fine[id] = FATIMA_T_CALIB->Calibrate_QDC(QDC_Time_Fine[id], det_ids_TDC[id]);*/
}

void EXT_FATIMA_VME::Calibrate_TDC(int id)
{   

    // again probably can't be done here thanks for uint32 limitation

    /*TDC_Time_ns[id] = FATIMA_T_CALIB->Calibrate_TDC(TDC_Time_Raw[id], det_ids_TDC[id]);
    */
}

void EXT_FATIMA_VME::dump(const signal_id &id, pretty_dump_info &pdi) const
{
}

void EXT_FATIMA_VME::show_members(const signal_id& id, const char* unit) const
{
}

void EXT_FATIMA_VME::enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const
{
}

void EXT_FATIMA_VME::zero_suppress_info_ptrs(used_zero_suppress_info& used_info)
{
}
