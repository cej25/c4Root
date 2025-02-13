#ifndef TravMusCalData_H
#define TravMusCalData_H

#include "TObject.h"

class TravMusCalItem : public TObject
{
    public:
        TravMusCalItem();

        void SetAll(uint64_t wr, uint16_t* e, uint16_t* t);
        void Reset();

        // Getters
        uint64_t Get_wr_t() const;
        uint16_t Get_music_energy(int index) const;
        uint16_t Get_music_time(int index) const;

        ClassDefNV(TravMusCalItem, 2);
    
    public:
        uint64_t wr_t;

        uint16_t energy[8];
        uint16_t time[8];
        
};

inline uint64_t TravMusCalItem::Get_wr_t() const
{
    return wr_t;
}

inline uint16_t TravMusCalItem::Get_music_energy(int index) const
{
    return energy[index];
}

inline uint16_t TravMusCalItem::Get_music_time(int index) const
{
    return time[index];
}


#endif