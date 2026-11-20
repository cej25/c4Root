#ifndef BB7FebexReader_H
#define BB7FebexReader_H

#include "BB7FebexData.h"
#include "c4Reader.h"

#include <Rtypes.h>
#include <vector>

extern "C"
{
    #include "ext_h101_bbfebex.h"
}

class BB7FebexRawData;

struct EXT_STR_h101_bbfebex_t;
typedef struct EXT_STR_h101_bbfebex_t EXT_STR_h101_bbfebex;
typedef struct EXT_STR_h101_bbfebex_onion_t EXT_STR_h101_bbfebex_onion;
class ext_data_struct_info;

class BB7FebexReader : public c4Reader
{
    public:
        BB7FebexReader(EXT_STR_h101_bbfebex_onion*, size_t);

        virtual ~BB7FebexReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:
        EXT_STR_h101_bbfebex_onion* fData;
        size_t fOffset;
        Bool_t fOnline;
        BB7FebexRawData* fRaw; //! Owns the detector raw branch
        std::vector<BB7FebexItem>* bb7array;
        std::vector<BB7EmptyItem>* bb7empty;

    public:
        ClassDefOverride(BB7FebexReader, 2);


};

#endif