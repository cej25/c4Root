#ifndef FATIMA_READER_H
#define FATIMA_READER_H

#include "c4Reader.h"

#include <cstddef>
#include <cstdint>

class FatimaRawData;
class ext_data_struct_info;
struct EXT_STR_h101_fatima_onion_t;
struct EXT_STR_h101_fatimavme_onion_t;

class FatimaReader : public c4Reader
{
public:
    struct TamexInput
    {
        EXT_STR_h101_fatima_onion_t* bank = nullptr;
        std::size_t offset = 0;
        std::uint16_t procid = 0;
    };
    struct VmeInput
    {
        EXT_STR_h101_fatimavme_onion_t* bank = nullptr;
        std::size_t offset = 0;
        std::uint16_t procid = 0;
    };

    FatimaReader(TamexInput tamex, VmeInput vme);
    ~FatimaReader() override;
    Bool_t Init(ext_data_struct_info*) override;
    Bool_t Read() override;
    void Reset() override;
    void SetOnline(Bool_t online) { fOnline = online; }

    ClassDefOverride(FatimaReader, 0);

private:
    TamexInput fTamex; //! Borrowed UCESB input
    VmeInput fVme; //! Borrowed UCESB input
    FatimaRawData* fOutput; //! Owns the detector event
    Bool_t fOnline = kFALSE;
};

#endif
