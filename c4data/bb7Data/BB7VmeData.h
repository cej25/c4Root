#ifndef BB7VmeData_H
#define BB7VmeData_H

#include "TObject.h"
#include <vector>

class BB7VmeData : public TObject
{
    public:
        BB7VmeData();

        virtual ~BB7VmeData() {};

        // Getters
        inline uint64_t Get_wr_t() const { return fwr_t; }
        
        inline std::vector<uint32_t> Get_v7x5_geo() const { return fv7x5_geo; }
        inline std::vector<uint32_t> Get_v7x5_channel() const { return fv7x5_channel; }
        inline std::vector<uint32_t> Get_v7x5_data() const { return fv7x5_data; }


        // Setters
        inline void Set_wr_t(uint64_t wr) { fwr_t = wr; }

        inline void Set_v7x5_geo(std::vector<uint32_t> geos) { fv7x5_geo = geos; }
        inline void Set_v7x5_channel(std::vector<uint32_t> channels) { fv7x5_channel = channels; }
        inline void Set_v7x5_data(std::vector<uint32_t> data) { fv7x5_data = data; }

    protected:

        // variables
        uint64_t fwr_t;

        std::vector<uint32_t> fv7x5_geo;
        std::vector<uint32_t> fv7x5_channel;
        std::vector<uint32_t> fv7x5_data;

    
    public:
        ClassDef(BB7VmeData, 1);
};


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