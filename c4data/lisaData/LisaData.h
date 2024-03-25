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
        inline uint64_t GetEventTime() { return f_event_time; }
        inline uint32_t GetBoardNum() { return f_board_num; }

        // Setters
        inline void SetEventTime(uint64_t event_time) { f_event_time = event_time; }
        inline void SetBoardNum(uint32_t board_num) { f_board_num = board_num; }



    protected:
        // Data items
        uint64_t f_event_time;
        uint64_t f_board_num;
        
        // whiterabbit

    public:
        ClassDef(LisaData, 1)
};

#endif