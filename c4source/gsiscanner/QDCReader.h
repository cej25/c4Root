#ifndef QDCReader_H
#define QDCReader_H

#include "c4Reader.h"

#include <Rtypes.h>

extern "C"
{
    #include "ext_h101_qdc.h"
}

class TClonesArray;

struct EXT_STR_h101_qdc_t;
typedef struct EXT_STR_h101_qdc_t EXT_STR_h101_qdc;
typedef struct EXT_STR_h101_qdc_onion_t EXT_STR_h101_qdc_onion;
class ext_data_struct_info;

class QDCReader : public c4Reader
{
    public:
        QDCReader(EXT_STR_h101_qdc_onion*, size_t);

        virtual ~QDCReader();


        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }
    
    private:
        unsigned int fNEvent;

        EXT_STR_h101_qdc_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;


        const int NBoards = 2; //change


        int32_t channel_q;
        int32_t channel_id;


        uint64_t wr_t;

    public:
        ClassDefOverride(QDCReader, 0);
};

#endif