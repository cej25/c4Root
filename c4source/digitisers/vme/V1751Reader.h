#ifndef C4_V1751_READER_H
#define C4_V1751_READER_H
#include "c4Reader.h"
#include <cstddef>
#include <cstdint>
struct EXT_STR_h101_fatimavme_onion_t;
class ext_data_struct_info;
class TClonesArray;

class V1751Reader : public c4Reader {
public:
    V1751Reader(EXT_STR_h101_fatimavme_onion_t* input, std::size_t offset,
                std::uint16_t procid);
    ~V1751Reader() override;
    Bool_t Init(ext_data_struct_info*) override;
    Bool_t Read() override;
    void Reset() override;
    void SetOnline(Bool_t online) { fOnline = online; }
private:
    EXT_STR_h101_fatimavme_onion_t* fInput = nullptr; //! Borrowed UCESB memory
    std::size_t fOffset = 0;
    std::uint16_t fProcId = 0;
    Bool_t fOnline = kFALSE;
    TClonesArray* fOutput = nullptr; //! Owned by reader
public:
    ClassDefOverride(V1751Reader, 0);
};
#endif
