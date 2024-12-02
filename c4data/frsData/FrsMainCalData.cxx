#include "FrsMainCalData.h"

FrsMainCalScalerItem::FrsMainCalScalerItem()
{

}

void FrsMainCalScalerItem::SetAll(uint32_t in, uint32_t sc)
{
    index = in;
    scaler = sc;
}

void FrsMainCalScalerItem::Reset()
{

}

ClassImp(FrsMainCalScalerItem)

FrsMainCalSciItem::FrsMainCalSciItem()
{

}

// void FrsMainCalSciItem::SetdEArray(uint32_t* de)
// {
//     de_array = de;
// }

void FrsMainCalSciItem::Set_dE(uint32_t de21l,
                                    uint32_t de21r,
                                    uint32_t de22l,
                                    uint32_t de22r,
                                    uint32_t de31l,
                                    uint32_t de31r,
                                    uint32_t de41l,
                                    uint32_t de41r,
                                    uint32_t de42l,
                                    uint32_t de42r,
                                    uint32_t de43l,
                                    uint32_t de43r,
                                    uint32_t de81l,
                                    uint32_t de81r)
{
    de_21l = de21l;
    de_21r = de21r;
    de_22l = de22l;
    de_22r = de22r;
    de_31l = de31l;
    de_31r = de31r;
    de_41l = de41l;
    de_41r = de41r;
    de_42l = de42l;
    de_42r = de42r;
    de_43l = de43l;
    de_43r = de43r;
    de_81l = de81l;
    de_81r = de81r;
}


// void FrsMainCalSciItem::SetAll(uint32_t* de, uint32_t** tdc, int * multi)
// {
//     de_array = de;
//     tdc_array = tdc;
//     mh_counter = multi;
// }

void FrsMainCalSciItem::SetAll(uint32_t de21l,
                    uint32_t de21r,
                    uint32_t de22l,
                    uint32_t de22r,
                    uint32_t de31l,
                    uint32_t de31r,
                    uint32_t de41l,
                    uint32_t de41r,
                    uint32_t de42l,
                    uint32_t de42r,
                    uint32_t de43l,
                    uint32_t de43r,
                    uint32_t de81l,
                    uint32_t de81r,
                    uint32_t** tdc,
                    int* multi)
{
    de_21l = de21l;
    de_21r = de21r;
    de_22l = de22l;
    de_22r = de22r;
    de_31l = de31l;
    de_31r = de31r;
    de_41l = de41l;
    de_41r = de41r;
    de_42l = de42l;
    de_42r = de42r;
    de_43l = de43l;
    de_43r = de43r;
    de_81l = de81l;
    de_81r = de81r;
    tdc_array = tdc;
    mh_counter = multi;
}

void FrsMainCalSciItem::Reset() //?
{
    de_21l = 0;
    de_21r = 0;
    de_22l = 0;
    de_22r = 0;
    de_31l = 0;
    de_31r = 0;
    de_41l = 0;
    de_41r = 0;
    de_42l = 0;
    de_42r = 0;
    de_43l = 0;
    de_43r = 0;
    de_81l = 0;
    de_81r = 0;
    de_array = 0;
    tdc_array = 0;
}

ClassImp(FrsMainCalSciItem)

FrsMainCalMusicItem::FrsMainCalMusicItem()
{

}

void FrsMainCalMusicItem::SetAll(uint32_t* mt1, uint32_t* mt2)
{
    music_t1 = mt1;
    music_t2 = mt2;
}

void FrsMainCalMusicItem::Reset()
{
    music_t1 = 0;
    music_t2 = 0;
}

ClassImp(FrsMainCalMusicItem)