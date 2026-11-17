#ifndef TAMEX_READER_H
#define TAMEX_READER_H

#include "c4Reader.h"

#include <cstddef>
#include <cstdint>

class TClonesArray;
class ext_data_struct_info;
struct EXT_STR_h101_bgo_onion_t;
struct EXT_STR_h101_fatima_onion_t;
struct EXT_STR_h101_bplast_onion_t;
struct EXT_STR_h101_mcp_onion_t;

// Generic TAMEX electronics reader. Input variants only describe the
// generated UCESB bank layout; the emitted Raw data is detector-independent.
class TamexReader : public c4Reader
{
public:
    TamexReader(EXT_STR_h101_bgo_onion_t* input, std::size_t offset,
                std::uint16_t source);
    TamexReader(EXT_STR_h101_fatima_onion_t* input, std::size_t offset,
                std::uint16_t source);
    TamexReader(EXT_STR_h101_bplast_onion_t* input, std::size_t offset,
                std::uint16_t source);
    TamexReader(EXT_STR_h101_mcp_onion_t* input, std::size_t offset,
                std::uint16_t source);
    ~TamexReader() override;

    Bool_t Init(ext_data_struct_info*) override;
    Bool_t Read() override;
    void Reset() override;

    void SetOnline(Bool_t online) { fOnline = online; }

private:
    enum class InputKind : std::uint8_t { BGO, Fatima, bPlast, MCP };
    TamexReader(void* input, std::size_t offset, std::uint16_t source,
                InputKind kind);

    void* fInput = nullptr; //! UCESB owns this memory
    std::size_t fOffset = 0;
    std::uint16_t fSource = 0;
    InputKind fKind = InputKind::BGO;
    Bool_t fOnline = kFALSE;
    TClonesArray* fArray = nullptr; //! Shared FairRoot output branch
    bool fOwnsArray = false; //! Only the registering reader owns the array

public:
    ClassDefOverride(TamexReader, 0);
};

#endif
