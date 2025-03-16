#ifndef BB7FebexData_H
#define BB7FebexData_H
#include "TObject.h"
#include <vector>

class BB7FebexItem : public TObject
{
    public:
        BB7FebexItem();

        void SetAll(Long64_t wr,
                    UShort_t id,
                    Int_t cr_id,
                    UInt_t b_id,
                    ULong64_t ev_time,
                    UInt_t ch_id,
                    ULong64_t ch_time,
                    Bool_t p,
                    Bool_t o,
                    UInt_t ch_energy,
                    UInt_t ch_id_traces,
                    std::vector<UShort_t> tr);
        void Reset();

        ULong64_t Get_wr_t() const { return wr_t; }
        UShort_t Get_wr_id() const { return wr_id; }
        Int_t Get_crate_id() const { return crate_id; }
        UInt_t Get_board_id() const { return board_id; }
        ULong64_t Get_board_event_time() const { return board_event_time; }
        UInt_t Get_channel_id() const { return channel_id; }
        ULong64_t Get_channel_time() const { return channel_time; }
        Bool_t Get_pileup() const { return pileup; }
        Bool_t Get_overflow() const { return overflow; }
        UInt_t Get_channel_energy() const { return channel_energy; }
        UInt_t Get_channel_id_traces() const { return channel_id_traces; }
        std::vector<UShort_t> Get_trace() const { return trace; }

        ClassDef(BB7FebexItem, 1);
    
    private:
        Long64_t wr_t;
        UShort_t wr_id;
        Int_t crate_id;
        UInt_t board_id;
        ULong64_t board_event_time;
        UInt_t channel_id;
        ULong64_t channel_time;
        Bool_t pileup;
        Bool_t overflow;
        UInt_t channel_energy;
        UInt_t channel_id_traces;
        std::vector<UShort_t> trace; 

};

class BB7EmptyItem : public TObject
{
    public:
        BB7EmptyItem();

        void SetAll(Long64_t wr,
                    UShort_t id,
                    Int_t cr_id,
                    UInt_t b_id,
                    ULong64_t ev_time);

        Long64_t Get_wr_t() const { return wr_t; }
        UShort_t Get_wr_id() const { return wr_id; }
        Int_t Get_crate_id() const{ return crate_id; } 
        UInt_t Get_board_id() const { return board_id; }
        ULong64_t Get_board_event_time() const { return board_event_time; }

        ClassDef(BB7EmptyItem, 1);
    
    private:
        Long64_t wr_t;
        UShort_t wr_id;
        Int_t crate_id;
        UInt_t board_id;
        ULong64_t board_event_time;

};

#endif