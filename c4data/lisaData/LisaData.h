#ifndef LisaData_H
#define LisaData_H
#include "TObject.h"
#include <vector>

class LisaData : public TObject
{
    public:
        LisaData();

        // Destructor
        virtual ~LisaData() {}

        // Getters
        inline uint64_t Get_wr_t() { return f_wr_time; }
        inline uint32_t Get_wr_subsystem_id() { return f_wr_id; }
        inline std::vector<int> GetBoardNum() { return f_board_num; }
        inline std::vector<uint64_t> GetEventTime() { return f_event_time; }
        inline std::vector<int> GetHitPattern() { return f_hit_pattern; }
        inline std::vector<uint32_t> GetMultiplicity() { return f_M; }
        
        inline std::vector<uint32_t> GetID() { return f_ch_ID; }
        inline std::vector<uint64_t> GetChannelTime() {return f_channel_time;}
        inline std::vector<bool> GetPileUp() { return f_pile_up; }
        inline std::vector<bool> GetOverFlow() { return f_over_flow; }
        inline std::vector<uint32_t> GetEnergy() { return f_ch_energy; }
        inline std::vector<uint32_t> GetTraces() { return f_traces;}
        inline std::vector<uint32_t> GetTracesI() { return f_tracesI;}
        //inline uint32_t GetTracesL() { return f_traces_l;}



        // Setters
        inline void Set_wr_t(uint64_t wr_time) { f_wr_time = wr_time; }
        inline void Set_wr_subsystem_id(uint32_t wr_id) { f_wr_id = wr_id; }
        inline void SetBoardNum(std::vector<int> board_num) { f_board_num = board_num; }
        inline void SetEventTime(std::vector<uint64_t> event_time) { f_event_time = event_time; }
        inline void SetHitPattern(std::vector<int> hit_pattern) { f_hit_pattern = hit_pattern; }
        inline void SetMultiplicity(std::vector<uint32_t> M) { f_M = M; }
        
        inline void SetID(std::vector<uint32_t> ch_ID) { f_ch_ID = ch_ID; }
        inline void SetChannelTime(std::vector<uint64_t> channel_time ) { f_channel_time = channel_time; }
        inline void SetPileUp(std::vector<bool> pile_up ) { f_pile_up = pile_up; }
        inline void SetOverFlow(std::vector<bool> over_flow ) { f_over_flow = over_flow; }
        inline void SetEnergy(std::vector<uint32_t> ch_energy ) { f_ch_energy = ch_energy; }
        inline void SetTraces(std::vector<uint32_t> traces) { f_traces = traces;}
        inline void SetTracesI(std::vector<uint32_t> tracesI) { f_tracesI = tracesI;}
        //inline void SetTracesL(uint32_t traces_l) { f_traces_l = traces_l;}

        //inline void SetTraces_(std::vector<uint32_t> traces_) { f_traces_ = traces_;}

    protected:
        // Data items
        std::vector<int> f_board_num;
        std::vector<uint64_t> f_event_time;
        uint64_t f_wr_time;
        uint32_t f_wr_id;
        std::vector<int> f_hit_pattern;
        std::vector<uint32_t> f_M;

        std::vector<uint32_t> f_ch_ID;
        std::vector<uint64_t> f_channel_time;
        std::vector<bool> f_pile_up;
        std::vector<bool> f_over_flow;
        std::vector<uint32_t> f_ch_energy;
        std::vector<uint32_t> f_traces;
        std::vector<uint32_t> f_tracesI;
        //uint32_t f_traces_l;



    public:
        ClassDef(LisaData, 1)
};

#endif