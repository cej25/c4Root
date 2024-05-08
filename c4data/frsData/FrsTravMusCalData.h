#ifndef FrsTravMusCalData_H
#define FrsTravMusCalData_H

#include "TObject.h"

class FrsTravMusCalItem : public TObject
{
    public:
        FrsTravMusCalItem();

        void SetAll(uint64_t wr, uint16_t* e, uint16_t* t);
        void Reset();

        // Getters
        uint64_t Get_wr_t() const;
        uint16_t* Get_music_energy() const;
        uint16_t* Get_music_time() const;

        ClassDefNV(FrsTravMusCalItem, 2);
    
    public:
        uint64_t wr_t;

        // can't be written to tree like this..
        uint16_t* energy;
        uint16_t* time;
        
};

inline uint64_t FrsTravMusCalItem::Get_wr_t() const
{
    return wr_t;
}

inline uint16_t* FrsTravMusCalItem::Get_music_energy() const
{
    return energy;
}

inline uint16_t* FrsTravMusCalItem::Get_music_time() const
{
    return time;
}


#endif