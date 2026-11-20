#include "TamexRawData.h"

TamexRawData::TamexRawData(std::uint16_t procidValue, std::uint16_t boardValue, std::uint16_t triggerValue,
                           std::uint16_t wr_subsystemValue, std::uint64_t wr_timestampValue,
                           std::uint16_t format_versionValue, const std::string& detectorNameValue)
    : procid(procidValue),
      detector_name(detectorNameValue),
      board(boardValue),
      trigger(triggerValue),
      wr_subsystem(wr_subsystemValue),
      wr_timestamp(wr_timestampValue),
      format_version(format_versionValue)
{
}

void TamexRawData::SetMetadata(std::uint16_t procidValue, std::uint16_t boardValue,
                               std::uint16_t triggerValue, std::uint16_t wr_subsystemValue,
                               std::uint64_t wr_timestampValue, std::uint16_t format_versionValue,
                               const std::string& detectorNameValue)
{
    this->procid = procidValue;
    this->detector_name = detectorNameValue;
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
    procid = 0;
    detector_name.clear();
    board = 0;
    trigger = 0;
    wr_subsystem = 0;
    wr_timestamp = 0;
    format_version = 0;
    words.clear();
}

ClassImp(TamexRawWord)
ClassImp(TamexRawData)
