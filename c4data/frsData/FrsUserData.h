#ifndef FrsUserData_H
#define FrsUserData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

class TClonesArray;

class FrsUserV830Item : public TObject
{
    public:
        FrsUserV830Item();

        void SetAll(uint32_t in, uint32_t sc);
        void Reset();

        uint32_t Get_scaler() const;
        uint32_t Get_index() const;

        ClassDefNV(FrsUserV830Item, 2);

    private:

        uint32_t scaler;
        uint32_t index;

};

class FrsUserV7X5Item : public TObject
{
    public:
        FrsUserV7X5Item();

        void SetAll(uint32_t g, uint32_t ch, uint32_t data);
        void Reset();

        uint32_t Get_geo() const;
        uint32_t Get_channel() const;
        uint32_t Get_v7x5_data() const;

        ClassDefNV(FrsUserV7X5Item, 2);
    
    private:
    
        uint32_t geo;
        uint32_t channel;
        uint32_t v7x5_data;
};

inline uint32_t FrsUserV7X5Item::Get_geo() const
{
    return geo;
}

inline uint32_t FrsUserV7X5Item::Get_channel() const
{
    return channel;
}

inline uint32_t FrsUserV7X5Item::Get_v7x5_data() const
{
    return v7x5_data;
}

inline uint32_t FrsUserV830Item::Get_scaler() const
{
    return scaler;
}

inline uint32_t FrsUserV830Item::Get_index() const
{
    return index;
}


#endif