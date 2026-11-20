#ifndef V1751_READER_H
#define V1751_READER_H
#include "c4Reader.h"
#include <cstddef>
#include <cstdint>
#include <ostream>
struct EXT_STR_h101_fatimavme_onion_t;
struct EXT_STR_h101_fatimavme_fixed_onion_t;
class ext_data_struct_info;
class TClonesArray;

class V1751Reader : public c4Reader {
public:
    V1751Reader(EXT_STR_h101_fatimavme_onion_t* input, std::size_t offset,
                std::uint16_t procid);
    V1751Reader(EXT_STR_h101_fatimavme_fixed_onion_t* input, std::size_t offset,
                std::uint16_t procid);
    ~V1751Reader() override;
    Bool_t Init(ext_data_struct_info*) override;
    Bool_t Read() override;
    void Reset() override;
    void PrintDiagnostics(std::ostream& output) const;
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
    std::uint64_t fEventsRead = 0;
    std::uint64_t fBanksWithMask = 0;
    std::uint64_t fBanksWithPackedCounts = 0;
    std::uint64_t fCandidateChannels = 0;
    std::uint64_t fAcceptedChannels = 0;
public:
    ClassDefOverride(V1751Reader, 0);
};
#endif
