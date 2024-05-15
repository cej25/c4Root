#ifndef FrsUserCalData_H
#define FrsUserCalData_H

#include <vector>
#include "TObject.h"


class FrsUserCalScalerItem : public TObject
{
    public:
        FrsUserCalScalerItem();

        void SetAll(uint32_t in, uint32_t sc);
        void Reset();

        uint32_t Get_index() const;
        uint32_t Get_scaler() const;

        ClassDefNV(FrsUserCalScalerItem, 2);
    
    private:
        // members
        uint32_t index;
        uint32_t scaler;
};

class FrsUserCalSciItem : public TObject
{
    public:
        FrsUserCalSciItem();

        void SetAll(uint32_t* dt);
        void Reset();

        uint32_t* Get_dt_array() const;
        
        ClassDefNV(FrsUserCalSciItem, 2);

    private:

        uint32_t* dt_array; // [16]
};

class FrsUserCalMusicItem : public TObject
{
    public:
        FrsUserCalMusicItem();

        void SetAll(uint32_t* me1, uint32_t* me2);
        void Reset();

        uint32_t* Get_music_e1() const;
        uint32_t* Get_music_e2() const;

        ClassDefNV(FrsUserCalMusicItem, 2);

    private:

        uint32_t* music_e1; // [8]
        uint32_t* music_e2; // [8]

};

inline uint32_t FrsUserCalScalerItem::Get_index() const
{
    return index;
}

inline uint32_t FrsUserCalScalerItem::Get_scaler() const
{
    return scaler;
}

inline uint32_t* FrsUserCalSciItem::Get_dt_array() const
{
    return dt_array;
}

inline uint32_t* FrsUserCalMusicItem::Get_music_e1() const
{
    return music_e1;
}

inline uint32_t* FrsUserCalMusicItem::Get_music_e2() const
{
    return music_e2;
}



#endif