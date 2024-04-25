#ifndef FrsUserData_H
#define FrsUserData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

class TClonesArray;

class FrsUserData : public TObject
{
    public:
        FrsUserData();
        FrsUserData(uint32_t Scalers_N, 
                    std::vector<uint32_t> Scalers_Index, 
                    std::vector<uint32_t> V830_Scalers,
                    std::vector<uint32_t>* v7x5_geo,
                    std::vector<uint32_t>* v7x5_channel,
                    std::vector<uint32_t>* v7x5_data);
        
        virtual ~FrsUserData() {}

        // Getters
        inline const Int_t Get_Scalers_N() const { return fScalers_N; }
        inline const std::vector<uint32_t>& Get_Scalers_Index() const { return fScalers_Index; }
        inline const std::vector<uint32_t>& Get_V830_Scalers() const { return fV830_Scalers; }

        inline std::vector<uint32_t>* Get_v7x5_geo_user() { return fv7x5_geo_user; }
        inline std::vector<uint32_t>* Get_v7x5_channel_user() { return fv7x5_channel_user; }
        inline std::vector<uint32_t>* Get_v7x5_data_user() { return fv7x5_data_user; }


        // Setters
    
    private:
        Int_t fScalers_N;
        std::vector<uint32_t> fScalers_Index;
        std::vector<uint32_t> fV830_Scalers;

        std::vector<uint32_t> fv7x5_geo_user[4];
        std::vector<uint32_t> fv7x5_channel_user[4];
        std::vector<uint32_t> fv7x5_data_user[4];
    

    public:
        ClassDef(FrsUserData, 1)
};

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