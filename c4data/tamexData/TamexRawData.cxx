#include "TamexRawData.h"

TamexRawData::TamexRawData(std::uint16_t source, std::uint16_t board, std::uint16_t trigger,
                           std::uint16_t wr_subsystem, std::uint64_t wr_timestamp,
                           std::uint16_t format_version)
    : source_(source),
      board_(board),
      trigger_(trigger),
      wr_subsystem_(wr_subsystem),
      wr_timestamp_(wr_timestamp),
      format_version_(format_version)
{
}

void TamexRawData::Reset()
{
    source_ = 0;
    board_ = 0;
    trigger_ = 0;
    wr_subsystem_ = 0;
    wr_timestamp_ = 0;
    format_version_ = 0;
    words_.clear();
}

ClassImp(TamexRawWord)
ClassImp(TamexRawData)
