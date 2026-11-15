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
    TamexRawData(std::uint16_t source, std::uint16_t board, std::uint16_t trigger,
                 std::uint16_t wr_subsystem, std::uint64_t wr_timestamp,
                 std::uint16_t format_version);

    std::uint16_t Source() const { return source_; }
    std::uint16_t Board() const { return board_; }
    std::uint16_t Trigger() const { return trigger_; }
    std::uint16_t WrSubsystem() const { return wr_subsystem_; }
    std::uint64_t WrTimestamp() const { return wr_timestamp_; }
    std::uint16_t FormatVersion() const { return format_version_; }
    const std::vector<TamexRawWord>& Words() const { return words_; }

    void AddWord(const TamexRawWord& word) { words_.push_back(word); }
    void ReserveWords(std::size_t count) { words_.reserve(count); }

    void SetMetadata(std::uint16_t source, std::uint16_t board,
                     std::uint16_t trigger, std::uint16_t wr_subsystem,
                     std::uint64_t wr_timestamp, std::uint16_t format_version);
    void Reset();
    void Clear(Option_t* option = "") override;

    ClassDef(TamexRawData, 1);

private:
    std::uint16_t source_ = 0;
    std::uint16_t board_ = 0;
    std::uint16_t trigger_ = 0;
    std::uint16_t wr_subsystem_ = 0;
    std::uint64_t wr_timestamp_ = 0;
    std::uint16_t format_version_ = 0;
    std::vector<TamexRawWord> words_;
};

#endif
