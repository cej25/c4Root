#include "LisaData.h"

LisaData::LisaData()
{
}

LisaItem::LisaItem()
{

}

void LisaItem::SetAll(uint64_t wr,
                    uint16_t id,
                    uint8_t b_id,
                    uint64_t ev_time,
                    uint8_t ch_id,
                    uint64_t ch_time,
                    bool p,
                    bool o,
                    uint32_t ch_energy,
                    std::vector<uint16_t> tr)
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
    trace = tr;
}

void LisaItem::Reset()
{
    wr_t = 0;
    wr_id = 0;
    board_id = 0;
    board_event_time = 0;
    channel_id = 0;
    channel_time = 0;
    pileup = 0;
    overflow = 0;
    channel_energy = 0;
    trace = {};
}

ClassImp(LisaData)