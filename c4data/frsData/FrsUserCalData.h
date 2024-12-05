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
        void Set_dT(uint32_t dt21l_21r,
                    uint32_t dt41l_41r,
                    uint32_t dt42l_42r,
                    uint32_t dt43l_43r,
                    uint32_t dt81l_81r,
                    uint32_t dt21l_41l,
                    uint32_t dt21r_41r,
                    uint32_t dt42r_21r,
                    uint32_t dt42l_21l,
                    uint32_t dt21l_81l,
                    uint32_t dt21r_81r,
                    uint32_t dt22l_22r,
                    uint32_t dt22l_41l,
                    uint32_t dt22r_41r,
                    uint32_t dt22l_81l,
                    uint32_t dt22r_81r);
        void Reset();

        uint32_t* Get_dt_array() const;
        uint32_t Get_dT_21l_21r() const;
        uint32_t Get_dT_41l_41r() const;
        uint32_t Get_dT_42l_42r() const;
        uint32_t Get_dT_43l_43r() const;
        uint32_t Get_dT_81l_81r() const;
        uint32_t Get_dT_21l_41l() const;
        uint32_t Get_dT_21r_41r() const;
        uint32_t Get_dT_42r_21r() const;
        uint32_t Get_dT_42l_21l() const;
        uint32_t Get_dT_21l_81l() const;
        uint32_t Get_dT_21r_81r() const;
        uint32_t Get_dT_22l_22r() const;
        uint32_t Get_dT_22l_41l() const;
        uint32_t Get_dT_22r_41r() const;
        uint32_t Get_dT_22l_81l() const;
        uint32_t Get_dT_22r_81r() const;
        
        ClassDefNV(FrsUserCalSciItem, 1);

    private:

        uint32_t* dt_array; // [16]
        uint32_t dt_21l_21r;
        uint32_t dt_41l_41r;
        uint32_t dt_42l_42r;
        uint32_t dt_43l_43r;
        uint32_t dt_81l_81r;
        uint32_t dt_21l_41l;
        uint32_t dt_21r_41r;
        uint32_t dt_42r_21r;
        uint32_t dt_42l_21l;
        uint32_t dt_21l_81l;
        uint32_t dt_21r_81r;
        uint32_t dt_22l_22r;
        uint32_t dt_22l_41l;
        uint32_t dt_22r_41r;
        uint32_t dt_22l_81l;
        uint32_t dt_22r_81r;
};

class FrsUserCalMusicItem : public TObject
{
    public:
        FrsUserCalMusicItem();

        void SetAll(uint32_t* me1, uint32_t* me2);
        void Reset();

        uint32_t* Get_music_e1() const;
        uint32_t* Get_music_e2() const;

        ClassDefNV(FrsUserCalMusicItem, 1);

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

inline uint32_t FrsUserCalSciItem::Get_dT_21l_21r() const
{
    return dt_21l_21r;
}

inline uint32_t FrsUserCalSciItem::Get_dT_22l_22r() const
{
    return dt_22l_22r;
}

inline uint32_t FrsUserCalSciItem::Get_dT_41l_41r() const
{
    return dt_41l_41r;
}

inline uint32_t FrsUserCalSciItem::Get_dT_42l_42r() const
{
    return dt_42l_42r;
}

inline uint32_t FrsUserCalSciItem::Get_dT_43l_43r() const
{
    return dt_43l_43r;
}

inline uint32_t FrsUserCalSciItem::Get_dT_81l_81r() const
{
    return dt_81l_81r;
}

inline uint32_t FrsUserCalSciItem::Get_dT_21l_41l() const
{
    return dt_21l_41l;
}

inline uint32_t FrsUserCalSciItem::Get_dT_21r_41r() const
{
    return dt_21r_41r;
}

inline uint32_t FrsUserCalSciItem::Get_dT_42l_21l() const
{
    return dt_42l_21l;
}

inline uint32_t FrsUserCalSciItem::Get_dT_42r_21r() const
{
    return dt_42r_21r;
}

inline uint32_t FrsUserCalSciItem::Get_dT_21l_81l() const
{
    return dt_21l_81l;
}

inline uint32_t FrsUserCalSciItem::Get_dT_21r_81r() const
{
    return dt_21r_81r;
}

inline uint32_t FrsUserCalSciItem::Get_dT_22l_41l() const
{
    return dt_22l_41l;
}

inline uint32_t FrsUserCalSciItem::Get_dT_22r_41r() const
{
    return dt_22r_41r;
}

inline uint32_t FrsUserCalSciItem::Get_dT_22l_81l() const
{
    return dt_22l_81l;
}

inline uint32_t FrsUserCalSciItem::Get_dT_22r_81r() const
{
    return dt_22r_81r;
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