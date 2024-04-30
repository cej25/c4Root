#ifndef FrsUserCalData_H
#define FrsUserCalData_H

#include <vector>
#include "TObject.h"

class FrsUserCalData : public TObject
{
    public:
        FrsUserCalData();

        FrsUserCalData(uint32_t Scalers_N, 
                    std::vector<uint32_t> Scalers_Index, 
                    std::vector<uint32_t> V830_Scalers,
                    uint32_t* dt_array,
                    uint32_t* music_e1,
                    uint32_t* music_e2);

        virtual ~FrsUserCalData() {}

        // Getters
        inline const Int_t Get_Scalers_N() const { return fScalers_N; }
        inline const std::vector<uint32_t>& Get_Scalers_Index() const { return fScalers_Index; }
        inline const std::vector<uint32_t>& Get_V830_Scalers() const { return fV830_Scalers; }

        inline uint32_t* Get_dt_array() { return fdt_array; }
        inline uint32_t* Get_music_e1() { return fmusic_e1; }
        inline uint32_t* Get_music_e2() { return fmusic_e2; }

    private:

        Int_t fScalers_N;
        std::vector<uint32_t> fScalers_Index;
        std::vector<uint32_t> fV830_Scalers;

        uint32_t fdt_array[16];
        uint32_t fmusic_e1[8];
        uint32_t fmusic_e2[8];
        

    public:
        ClassDef(FrsUserCalData, 1);
    
};

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