#ifndef BB7VmeCalData_H
#define BB7VmeCalData_H

#include "TObject.h"
#include <vector>

class BB7VmeImplantItem : public TObject
{
    public:
        BB7VmeImplantItem();

        void SetAll(uint64_t wr, int det, int si, int st, uint32_t adc);
        void Reset();

        uint64_t Get_wr_t() const;
        int Get_detector() const;
        int Get_side() const;
        int Get_strip() const;
        uint32_t Get_raw_adc() const;

        ClassDefNV(BB7VmeImplantItem, 1);
    
    private:

        uint64_t wr_t;
        int detector;
        int side;
        int strip;
        uint32_t raw_adc;

};

class BB7VmeDecayItem : public TObject
{
    public:
        BB7VmeDecayItem();

        void SetAll(uint64_t wr, int det, int si, int st, uint32_t adc);
        void Reset();

        uint64_t Get_wr_t() const;
        int Get_detector() const;
        int Get_side() const;
        int Get_strip() const;
        uint32_t Get_raw_adc() const;

        ClassDefNV(BB7VmeDecayItem, 1);
    
    private:

        uint64_t wr_t;
        int detector;
        int side;
        int strip;
        uint32_t raw_adc;
};

class BB7VmeResidualItem : public TObject
{
    public:
        BB7VmeResidualItem();

        void Reset();
        void SetAll(uint32_t left, uint32_t right, uint32_t tmd, uint32_t tmu);

        double Get_SC41L() const;
        double Get_SC41R() const;
        double Get_TM_Delayed() const;
        double Get_TM_Undelayed() const;

        ClassDefNV(BB7VmeResidualItem, 2);

    private:
        uint32_t sc41l;
        uint32_t sc41r;
        uint32_t tm_delayed;
        uint32_t tm_undelayed;
};

inline uint64_t BB7VmeImplantItem::Get_wr_t() const
{
    return wr_t;
}

inline int BB7VmeImplantItem::Get_detector() const
{
    return detector;
}

inline int BB7VmeImplantItem::Get_side() const
{
    return side;
}

inline int BB7VmeImplantItem::Get_strip() const
{
    return strip;
}

inline uint32_t BB7VmeImplantItem::Get_raw_adc() const
{
    return raw_adc;
}

inline uint64_t BB7VmeDecayItem::Get_wr_t() const
{
    return wr_t;
}

inline int BB7VmeDecayItem::Get_detector() const
{
    return detector;
}

inline int BB7VmeDecayItem::Get_side() const
{
    return side;
}

inline int BB7VmeDecayItem::Get_strip() const
{
    return strip;
}

inline uint32_t BB7VmeDecayItem::Get_raw_adc() const
{
    return raw_adc;
}

inline double BB7VmeResidualItem::Get_SC41L() const
{
    return sc41l;
} 

inline double BB7VmeResidualItem::Get_SC41R() const
{
    return sc41r;
} 

inline double BB7VmeResidualItem::Get_TM_Delayed() const
{
    return tm_delayed;
} 

inline double BB7VmeResidualItem::Get_TM_Undelayed() const
{
    return tm_undelayed;
} 

#endif