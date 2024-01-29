#include "FrsUserCalData.h"

FrsUserCalData::FrsUserCalData()
{
    
}


FrsUserCalData::FrsUserCalData(uint32_t* dt_array,
                            uint32_t* music_e1,
                            uint32_t* music_e2)
{   
    for (int i = 0; i < 16; i++) fdt_array[i] = dt_array[i];
    for (int i = 0; i < 8; i++)
    {
        fmusic_e1[i] = music_e1[i];
        fmusic_e2[i] = music_e2[i];
    }
}


ClassImp(FrsUserCalData)
