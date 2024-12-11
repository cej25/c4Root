#include "LisaAnaData.h"

// LisaAnaData::LisaAnaData()
// {

// }

LisaAnaItem::LisaAnaItem()
{

}

void LisaAnaItem::SetAll(uint64_t wr,
                    uint16_t id,
                    uint8_t b_id,
                    uint64_t ev_time,
                    uint8_t ch_id,
                    uint64_t ch_time,
                    bool p,
                    //bool p_MWD,
                    bool o,
                    //bool o_MWD,
                    uint32_t ch_energy,
                    uint32_t ch_energy_MWD,
                    uint8_t ch_id_tr,
                    std::vector<int16_t> tr,
                    std::vector<int16_t> tr_MWD
                    )
{   
    wr_t = wr;
    wr_id = id;
    board_id = b_id;
    board_event_time = ev_time;
    channel_id = ch_id;
    channel_time = ch_time;
    pileup = p;
    //pileup_MWD = p_MWD;
    overflow = o;
    //overflow_MWD = o_MWD;
    channel_energy = ch_energy;
    channel_energy_MWD = ch_energy_MWD;
    channel_id_traces = ch_id_tr;
    trace = tr;
    trace_MWD = tr_MWD;
}


void LisaAnaItem::Reset()
{   
    // maybe reset stuff to -1 since 0 is used occasionally for positions
    wr_t = 0;
    wr_id = 0;
    board_id = 0;
    board_event_time = 0;
    channel_id = 0;
    channel_time = 0;
    pileup = 0;
    //pileup_MWD = 0;
    overflow = 0;
    //overflow_MWD = 0;
    channel_energy = 0;
    channel_energy_MWD = 0;
    channel_id = 0;
    trace = {};
    trace_MWD = {};

}

ClassImp(LisaAnaItem)