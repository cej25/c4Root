#ifndef V1290_READER_H
#define V1290_READER_H
#include "c4Reader.h"
#include <cstddef>
#include <cstdint>
struct EXT_STR_h101_fatimavme_onion_t;
struct EXT_STR_h101_fatimavme_fixed_onion_t;
class ext_data_struct_info;
class TClonesArray;

class V1290Reader : public c4Reader {
public:
    V1290Reader(EXT_STR_h101_fatimavme_onion_t* input, std::size_t offset,
                std::uint16_t procid);
    V1290Reader(EXT_STR_h101_fatimavme_fixed_onion_t* input, std::size_t offset,
                std::uint16_t procid);
    ~V1290Reader() override;
    Bool_t Init(ext_data_struct_info*) override;
    Bool_t Read() override;
    void Reset() override;
    void SetOnline(Bool_t online) { fOnline = online; }
    // Only one reader for a shared UCESB subevent registers the structure.
    void SetRegisterStructure(bool value) { fRegisterStructure = value; }
private:
    template <typename Bank> Bool_t ReadBanks(const Bank* input);
    EXT_STR_h101_fatimavme_fixed_onion_t* fFixedInput = nullptr; //! Borrowed UCESB memory
    EXT_STR_h101_fatimavme_onion_t* fInput = nullptr; //! Borrowed UCESB memory
    std::size_t fOffset = 0;
    std::uint16_t fProcId = 0;
    Bool_t fOnline = kFALSE;
    bool fRegisterStructure = true;
    TClonesArray* fOutput = nullptr; //! Owned by reader
public:
    ClassDefOverride(V1290Reader, 0);
};
#endif
