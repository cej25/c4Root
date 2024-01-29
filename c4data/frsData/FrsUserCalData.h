#ifndef FrsUserCalData_H
#define FrsUserCalData_H

#include <vector>
#include "TObject.h"

class FrsUserCalData : public TObject
{
    public:
        FrsUserCalData();

        FrsUserCalData(const uint32_t* dt_array,
                    const uint32_t* music_e1,
                    const uint32_t* music_e2);

        virtual ~FrsUserCalData() {}

        // Getters
        inline const uint32_t* Get_dt_array() const { return fdt_array; }
        inline const uint32_t* Get_music_e1() const { return fmusic_e1; }
        inline const uint32_t* Get_music_e2() const { return fmusic_e2; }

    private:

        uint32_t fdt_array[16];
        uint32_t fmusic_e1[8];
        uint32_t fmusic_e2[8];
        

    public:
        ClassDef(FrsUserCalData, 1);
    
};


#endif