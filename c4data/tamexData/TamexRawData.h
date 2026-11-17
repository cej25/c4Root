#ifndef TAMEX_RAW_DATA_H
#define TAMEX_RAW_DATA_H

#include "TObject.h"

#include <cstdint>
#include <vector>

// One ordered TAMEX electronics word. Epoch words are retained explicitly.
struct TamexRawWord
{
    enum : std::uint8_t { Epoch = 0, Edge = 1 };
    enum : std::uint8_t
    {
        HasPrecedingEpoch = 1u << 0,
        MissingEpochOnChannelChange = 1u << 1,
        DescendingChannel = 1u << 2,
        InvalidFine = 1u << 3
    };

    std::uint8_t kind = Epoch;
    std::uint32_t packed_index = 0;
    std::uint32_t epoch = 0;
    std::uint16_t channel = 0;
    std::uint16_t coarse = 0;
    std::uint32_t fine = 0;
    bool leading = false;
    std::uint8_t flags = 0;

    ClassDefNV(TamexRawWord, 1);
};

// One board's digitiser data for an event. No detector identity or calibration.
class TamexRawData : public TObject
{
public:
    TamexRawData() = default;
    TamexRawData(std::uint16_t sourceValue, std::uint16_t boardValue, std::uint16_t triggerValue,
                 std::uint16_t wr_subsystemValue, std::uint64_t wr_timestampValue,
                 std::uint16_t format_versionValue);

    std::uint16_t Source() const { return source; }
    std::uint16_t Board() const { return board; }
    std::uint16_t Trigger() const { return trigger; }
    std::uint16_t WrSubsystem() const { return wr_subsystem; }
    std::uint64_t WrTimestamp() const { return wr_timestamp; }
    std::uint16_t FormatVersion() const { return format_version; }
    const std::vector<TamexRawWord>& Words() const { return words; }

    void AddWord(const TamexRawWord& word) { words.push_back(word); }
    void ReserveWords(std::size_t count) { words.reserve(count); }

    void SetMetadata(std::uint16_t sourceValue, std::uint16_t boardValue,
                     std::uint16_t triggerValue, std::uint16_t wr_subsystemValue,
                     std::uint64_t wr_timestampValue, std::uint16_t format_versionValue);
    void Reset();
    void Clear(Option_t* option = "") override;

    ClassDef(TamexRawData, 2);

private:
    std::uint16_t source = 0;
    std::uint16_t board = 0;
    std::uint16_t trigger = 0;
    std::uint16_t wr_subsystem = 0;
    std::uint64_t wr_timestamp = 0;
    std::uint16_t format_version = 0;
    std::vector<TamexRawWord> words;
};

#endif
