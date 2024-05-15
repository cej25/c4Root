#ifndef FrsMainData_H
#define FrsMainData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

class TClonesArray;   

class FrsMainV1290Item : public TObject
{
    public:
        FrsMainV1290Item();

        void SetAll(uint32_t ch, uint32_t data, uint32_t lot);
        uint32_t Get_channel() const;
        uint32_t Get_v1290_data() const;
        uint32_t Get_leadOrTrail() const;
        void Reset();

        ClassDefNV(FrsMainV1290Item, 2);
    private:
        // members
        uint32_t channel;
        uint32_t v1290_data;
        uint32_t leadOrTrail;
};


class FrsMainV830Item : public TObject
{
    public:
        FrsMainV830Item();
        
        void SetAll(uint32_t in, uint32_t sc);
        void Reset();
        uint32_t Get_index() const;
        uint32_t Get_scaler() const;

        ClassDefNV(FrsMainV830Item, 2);
    private:
        // members
        uint32_t index;
        uint32_t scaler;

};

class FrsMainV792Item : public TObject
{
    public:
        FrsMainV792Item();

        void SetAll(uint32_t ch, uint32_t data, uint32_t g);
        void Reset();
        uint32_t Get_channel() const;
        uint32_t Get_v792_data() const;
        uint32_t Get_geo() const;

        ClassDefNV(FrsMainV792Item, 2);
    private:
        // members
        uint32_t channel;
        uint32_t v792_data;
        uint32_t geo;

};

inline uint32_t FrsMainV792Item::Get_channel() const
{
    return channel;
}

inline uint32_t FrsMainV792Item::Get_v792_data() const
{
    return v792_data;
}

inline uint32_t FrsMainV792Item::Get_geo() const
{
    return geo;
}

inline uint32_t FrsMainV1290Item::Get_v1290_data() const
{
    return v1290_data;
}

inline uint32_t FrsMainV1290Item::Get_leadOrTrail() const
{
    return leadOrTrail;
}

inline uint32_t FrsMainV1290Item::Get_channel() const
{
    return channel;
}

inline uint32_t FrsMainV830Item::Get_index() const
{
    return index;
}

inline uint32_t FrsMainV830Item::Get_scaler() const
{
    return scaler;
}


#endif


