#include "TamexRawData.h"

TamexRawData::TamexRawData(std::uint16_t source, std::uint16_t board, std::uint16_t trigger,
                           std::uint16_t wr_subsystem, std::uint64_t wr_timestamp,
                           std::uint16_t format_version)
    : source(source),
      board(board),
      trigger(trigger),
      wr_subsystem(wr_subsystem),
      wr_timestamp(wr_timestamp),
      format_version(format_version)
{
}

void TamexRawData::SetMetadata(std::uint16_t source, std::uint16_t board,
                               std::uint16_t trigger, std::uint16_t wr_subsystem,
                               std::uint64_t wr_timestamp, std::uint16_t format_version)
{
    this->source = source;
    this->board = board;
    this->trigger = trigger;
    this->wr_subsystem = wr_subsystem;
    this->wr_timestamp = wr_timestamp;
    this->format_version = format_version;
}

void TamexRawData::Clear(Option_t*)
{
    Reset();
}

void TamexRawData::Reset()
{
    source = 0;
    board = 0;
    trigger = 0;
    wr_subsystem = 0;
    wr_timestamp = 0;
    format_version = 0;
    words.clear();
}

ClassImp(TamexRawWord)
ClassImp(TamexRawData)
