#ifndef FrsUserCalData_H
#define FrsUserCalData_H

#include <vector>
#include "TObject.h"

class FrsUserCalData : public TObject
{
    public:
        FrsUserCalData();

        FrsUserCalData(uint32_t* dt_array,
                    uint32_t* music_e1,
                    uint32_t* music_e2);

        virtual ~FrsUserCalData() {}

        // Getters
        inline uint32_t* Get_dt_array() { return fdt_array; }
        inline uint32_t* Get_music_e1() { return fmusic_e1; }
        inline uint32_t* Get_music_e2() { return fmusic_e2; }

    private:

        uint32_t fdt_array[16];
        uint32_t fmusic_e1[8];
        uint32_t fmusic_e2[8];
        

    public:
        ClassDef(FrsUserCalData, 1);
    
};


#endif