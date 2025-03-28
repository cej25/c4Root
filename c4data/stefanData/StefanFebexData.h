#ifndef StefanFebexData_H
#define StefanFebexData_H
#include "TObject.h"
#include <vector>

class StefanFebexItem : public TObject
{
    public:
        StefanFebexItem();

        void SetAll(Long64_t wr,
                    UShort_t id,
                    UInt_t b_id,
                    ULong64_t ev_time,
                    UInt_t ch_id,
                    ULong64_t ch_time,
                    Bool_t p,
                    Bool_t o,
                    UInt_t ch_energy
                    //UInt_t ch_id_traces,
                    /*std::vector<UShort_t> tr*/);
        void Reset();

        ULong64_t Get_wr_t() const { return wr_t; }
        UShort_t Get_wr_id() const { return wr_id; }
        UInt_t Get_board_id() const { return board_id; }
        ULong64_t Get_board_event_time() const { return board_event_time; }
        UInt_t Get_channel_id() const { return channel_id; }
        ULong64_t Get_channel_time() const { return channel_time; }
        Bool_t Get_pileup() const { return pileup; }
        Bool_t Get_overflow() const { return overflow; }
        UInt_t Get_channel_energy() const { return channel_energy; }
        // UInt_t Get_channel_id_traces() const { return channel_id_traces; }
        // std::vector<UShort_t> Get_trace() const { return trace; }

        ClassDef(StefanFebexItem, 1);
    
    private:
        Long64_t wr_t;
        UShort_t wr_id;
        UInt_t board_id;
        ULong64_t board_event_time;
        UInt_t channel_id;
        ULong64_t channel_time;
        Bool_t pileup;
        Bool_t overflow;
        UInt_t channel_energy;
        // UInt_t channel_id_traces;
        // std::vector<UShort_t> trace; 

};

#endif