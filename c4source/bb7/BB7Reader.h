#ifndef BB7Reader_H
#define BB7Reader_H

#include "c4Reader.h"

#include <cstddef>

struct EXT_STR_h101_bbfebex_onion_t;
struct EXT_STR_h101_bb7vme_onion_t;
class BB7FebexRawData;
class BB7VmeRawData;

class BB7Reader : public c4Reader
{
    public:
        BB7Reader(EXT_STR_h101_bbfebex_onion_t*, std::size_t);
        BB7Reader(EXT_STR_h101_bb7vme_onion_t*, std::size_t);
        ~BB7Reader() override;

        Bool_t Init(ext_data_struct_info*) override;
        Bool_t Read() override;
        void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:
        void ReadFebex();
        void ReadVme();

        EXT_STR_h101_bbfebex_onion_t* fFebexData = nullptr; //! UCESB input
        EXT_STR_h101_bb7vme_onion_t* fVmeData = nullptr; //! UCESB input
        std::size_t fOffset;
        Bool_t fOnline = kFALSE;
        BB7FebexRawData* fFebexRaw = nullptr; //! Owned output
        BB7VmeRawData* fVmeRaw = nullptr; //! Owned output

    public:
        ClassDefOverride(BB7Reader, 3);
};

#endif
