#ifndef DEGAS_READER_H
#define DEGAS_READER_H

#include "c4Reader.h"

#include <cstddef>
#include <cstdint>

class DegasRawData;
class ext_data_struct_info;
struct EXT_STR_h101_degas_onion_t;

class DegasReader : public c4Reader
{
public:
    DegasReader(EXT_STR_h101_degas_onion_t* input, std::size_t offset,
                std::uint16_t procid);
    ~DegasReader() override;

    Bool_t Init(ext_data_struct_info*) override;
    Bool_t Read() override;
    void Reset() override;
    void SetOnline(Bool_t online) { fOnline = online; }

    ClassDefOverride(DegasReader, 0);

private:
    EXT_STR_h101_degas_onion_t* fInput; //! UCESB input
    std::size_t fOffset;
    std::uint16_t fProcId;
    Bool_t fOnline = kFALSE;
    DegasRawData* fOutput; //! Owns detector data
};

#endif
