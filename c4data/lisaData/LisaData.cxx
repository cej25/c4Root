#include "LisaData.h"

LisaData::LisaData()
    : fBoard(0)
    , fChn(0)
    , fEn(0)
    , fTs_Lo(0)
    , fTs_Hi(0)
{
}

LisaData::LisaData(uint32_t board, 
                       uint32_t chn, 
                       uint32_t en,
                       uint32_t ts_lo, 
                       uint32_t ts_hi)
    : fBoard(board)
    , fChn(chn)
    , fEn(en)
    , fTs_Lo(ts_lo)
    , fTs_Hi(ts_hi)
{
}

ClassImp(LisaData)