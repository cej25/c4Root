#include "FrsUserCalData.h"


FrsUserCalScalerItem::FrsUserCalScalerItem()
{

}

void FrsUserCalScalerItem::SetAll(uint32_t in, uint32_t sc)
{
    index = in;
    scaler = sc;
}

void FrsUserCalScalerItem::Reset()
{
    index = 0;
    scaler = 0;
}

ClassImp(FrsUserCalScalerItem)


FrsUserCalSciItem::FrsUserCalSciItem()
{

}

void FrsUserCalSciItem::SetAll(uint32_t* dt)
{
    dt_array = dt;
}

void FrsUserCalSciItem::Set_dT(uint32_t dt21l_21r,
                                uint32_t dt41l_41r,
                                uint32_t dt42l_42r,
                                uint32_t dt43l_43r,
                                uint32_t dt81l_81r,
                                uint32_t dt21l_41l,
                                uint32_t dt21r_41r,
                                uint32_t dt42r_21r,
                                uint32_t dt42l_21l,
                                uint32_t dt21l_81l,
                                uint32_t dt21r_81r,
                                uint32_t dt22l_22r,
                                uint32_t dt22l_41l,
                                uint32_t dt22r_41r,
                                uint32_t dt22l_81l,
                                uint32_t dt22r_81r)
{
    dt_21l_21r = dt21l_21r;
    dt_41l_41r = dt41l_41r;
    dt_42l_42r = dt42l_42r;
    dt_43l_43r = dt43l_43r;
    dt_81l_81r = dt81l_81r;
    dt_21l_41l = dt21l_41l;
    dt_21r_41r = dt21r_41r;
    dt_42r_21r = dt42r_21r;
    dt_42l_21l = dt42l_21l;
    dt_21l_81l = dt21l_81l;
    dt_21r_81r = dt21r_81r;
    dt_22l_22r = dt22l_22r;
    dt_22l_41l = dt22l_41l;
    dt_22r_41r = dt22r_41r;
    dt_22l_81l = dt22l_81l;
    dt_22r_81r = dt22r_81r;

}



ClassImp(FrsUserCalSciItem)


FrsUserCalMusicItem::FrsUserCalMusicItem()
{

}

void FrsUserCalMusicItem::SetAll(uint32_t* me1, uint32_t* me2)
{
    music_e1 = me1;
    music_e2 = me2;
}

void FrsUserCalMusicItem::Reset()
{

}

ClassImp(FrsUserCalMusicItem)
