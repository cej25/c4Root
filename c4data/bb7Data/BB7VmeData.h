#ifndef BB7VmeData_H
#define BB7VmeData_H

#include "TObject.h"
#include <vector>

class BB7V7x5Item : public TObject
{
    public:
        BB7V7x5Item();

        void SetAll(uint64_t wr, uint32_t g, uint32_t data, uint32_t ch);
        void Reset();

        uint64_t Get_wr_t() const;
        uint32_t Get_geo() const;
        uint32_t Get_v7x5_data() const;
        uint32_t Get_channel() const;

        ClassDefNV(BB7V7x5Item, 1);

    private:

        uint64_t wr_t;
        uint32_t geo;
        uint32_t v7x5_data;
        uint32_t channel;

};

class BB7V1290Item : public TObject
{
    public:
        BB7V1290Item();

        void SetAll(uint32_t ch, uint32_t data, uint32_t lot);
        uint32_t Get_channel() const;
        uint32_t Get_v1290_data() const;
        uint32_t Get_leadOrTrail() const;
        void Reset();

        ClassDefNV(BB7V1290Item, 1);

    private:
        uint32_t channel;
        uint32_t v1290_data;
        uint32_t leadOrTrail;

};

inline uint64_t BB7V7x5Item::Get_wr_t() const
{
    return wr_t;
}

inline uint32_t BB7V7x5Item::Get_geo() const
{
    return geo;
}

inline uint32_t BB7V7x5Item::Get_channel() const
{
    return channel;
}

inline uint32_t BB7V7x5Item::Get_v7x5_data() const
{
    return v7x5_data;
}

inline uint32_t BB7V1290Item::Get_v1290_data() const
{
    return v1290_data;
}

inline uint32_t BB7V1290Item::Get_leadOrTrail() const
{
    return leadOrTrail;
}

inline uint32_t BB7V1290Item::Get_channel() const
{
    return channel;
}

#endif