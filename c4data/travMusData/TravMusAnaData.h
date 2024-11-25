#ifndef TravMusAnaData_H
#define TravMusAnaData_H

#include "TObject.h"

class TravMusAnaItem : public TObject
{
    public:
        TravMusAnaItem();

        void SetAll(int64_t wr, double de);
        void Reset();

        // Getters
        int64_t Get_wr_t() const;
        double Get_travmusic_dE() const;
   

        ClassDefNV(TravMusAnaItem, 2);
    
    public:

        int64_t wr_t;
        double de_travmus;
      
        
};

inline int64_t TravMusAnaItem::Get_wr_t() const
{
    return wr_t;
}

inline double TravMusAnaItem::Get_travmusic_dE() const
{
    return de_travmus;
}


#endif