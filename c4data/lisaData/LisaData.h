#ifndef LisaData_H
#define LisaData_H
#include "TObject.h"

class LisaData : public TObject
{
    public:
        LisaData();

        // Destructor
        virtual ~LisaData() {}

        // Getters
        inline uint64_t Get_wr_t() { return f_wr_time; }
        inline uint32_t Get_wr_subsystem_id() { return f_wr_id; }
        inline uint32_t GetBoardNum() { return f_board_num; }
        inline uint64_t GetEventTime() { return f_event_time; }
        inline uint32_t GetHitPattern() { return f_hit_pattern; }
        inline uint32_t GetMultiplicity() { return f_M; }
        inline uint32_t SetID() { return f_ID; }
        inline uint64_t GetChannelTime() { return f_channel_time; }
        inline bool GetPileUp() { return f_pile_up; }
        inline bool GetOverFlow() { return f_over_flow; }
        inline int32_t GetEnergy() { return f_energy; }

        // Setters
        inline void Set_wr_t(uint64_t wr_time) { f_wr_time = wr_time; }
        inline void Set_wr_subsystem_id(uint32_t wr_id) { f_wr_id = wr_id; }
        inline void SetBoardNum(uint32_t board_num) { f_board_num = board_num; }
        inline void SetEventTime(uint64_t event_time) { f_event_time = event_time; }
        inline void SetHitPattern(uint32_t hit_pattern) { f_hit_pattern = hit_pattern; }
        inline void SetMultiplicity(uint32_t M) { f_M = M; }
        inline void SetID(uint32_t ID) { f_ID = ID; }
        inline void SetChannelTime(uint64_t channel_time ) { f_channel_time = channel_time; }
        inline void SetPileUp(bool pile_up ) { f_pile_up = pile_up; }
        inline void SetOverFlow(bool over_flow ) { f_over_flow = over_flow; }
        inline void SetEnergy(int32_t energy ) { f_energy = energy; }

    protected:
        // Data items
        uint64_t f_board_num;
        uint64_t f_event_time;
        uint64_t f_wr_time;
        uint32_t f_wr_id;
        uint32_t f_hit_pattern;
        uint32_t f_M;
        uint32_t f_ID;
        uint64_t f_channel_time;
        bool f_pile_up;
        bool f_over_flow;
        int32_t f_energy;


    public:
        ClassDef(LisaData, 1)
};

#endif