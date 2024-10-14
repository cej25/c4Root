#include "LisaAnaData.h"

LisaAnaData::LisaAnaData()
{

}

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
                    bool o,
                    uint32_t ch_energy,
                    uint32_t ch_energy_ana,
                    uint8_t ch_id_tr,
                    std::vector<uint16_t> tr
                    )
{   
    wr_t = wr;
    wr_id = id;
    board_id = b_id;
    board_event_time = ev_time;
    channel_id = ch_id;
    channel_time = ch_time;
    pileup = p;
    overflow = o;
    channel_energy = ch_energy;
    channel_energy_ana = ch_energy_ana;
    channel_id_traces = ch_id_tr;
    trace = tr;
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
    overflow = 0;
    channel_energy = 0;
    channel_energy_ana = 0;
    channel_id = 0;
    trace = {};

}

ClassImp(LisaAnaData)