#ifndef FEBEX_READER_H
#define FEBEX_READER_H

#include "c4Reader.h"

#include <cstddef>
#include <cstdint>
#include <string>

struct EXT_STR_h101_febex_onion_t;
class TClonesArray;
class ext_data_struct_info;

class FebexReader : public c4Reader
{
public:
    FebexReader(EXT_STR_h101_febex_onion_t* input, std::size_t offset,
                std::uint16_t procid, const std::string& detectorName = "");
    ~FebexReader() override;

    Bool_t Init(ext_data_struct_info*) override;
    Bool_t Read() override;
    void Reset() override;
    void SetOnline(Bool_t online) { fOnline = online; }

    ClassDefOverride(FebexReader, 0);

private:
    EXT_STR_h101_febex_onion_t* fInput; //! UCESB input
    std::size_t fOffset;
    std::uint16_t fProcId;
    std::string fDetectorName;
    Bool_t fOnline = kFALSE;
    TClonesArray* fArray = nullptr; //! Owns FEBEX board records
};

#endif
