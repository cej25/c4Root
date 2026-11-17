#include "TamexRawData.h"

TamexRawData::TamexRawData(std::uint16_t sourceValue, std::uint16_t boardValue, std::uint16_t triggerValue,
                           std::uint16_t wr_subsystemValue, std::uint64_t wr_timestampValue,
                           std::uint16_t format_versionValue)
    : source(sourceValue),
      board(boardValue),
      trigger(triggerValue),
      wr_subsystem(wr_subsystemValue),
      wr_timestamp(wr_timestampValue),
      format_version(format_versionValue)
{
}

void TamexRawData::SetMetadata(std::uint16_t sourceValue, std::uint16_t boardValue,
                               std::uint16_t triggerValue, std::uint16_t wr_subsystemValue,
                               std::uint64_t wr_timestampValue, std::uint16_t format_versionValue)
{
    this->source = sourceValue;
    this->board = boardValue;
    this->trigger = triggerValue;
    this->wr_subsystem = wr_subsystemValue;
    this->wr_timestamp = wr_timestampValue;
    this->format_version = format_versionValue;
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
