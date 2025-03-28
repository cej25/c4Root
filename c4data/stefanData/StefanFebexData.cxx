#include "StefanFebexData.h"

StefanFebexItem::StefanFebexItem()
{
}

void StefanFebexItem::SetAll(Long64_t wr,
                        UShort_t id,
                        UInt_t b_id,
                        ULong64_t ev_time,
                        UInt_t ch_id,
                        ULong64_t ch_time,
                        Bool_t p,
                        Bool_t o,
                        UInt_t ch_energy
                        // UInt_t ch_id_tr,
                        /*std::vector<UShort_t> tr*/)
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
    // channel_id_traces = ch_id_tr;
    // trace = tr;
}

void StefanFebexItem::Reset()
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
    // channel_id = 0;
    // trace = {};
}

ClassImp(StefanFebexItem)
