#ifndef BeamMonitorReader_H
#define BeamMonitorReader_H

#include "c4Reader.h"

#include <Rtypes.h>

extern "C"
{
    #include "ext_h101_bm.h"
}

class TClonesArray;

struct EXT_STR_h101_BM_t;
typedef struct EXT_STR_h101_BM_t EXT_STR_h101_BM;
typedef struct EXT_STR_h101_BM_onion_t EXT_STR_h101_BM_onion;
class ext_data_struct_info;

class BeamMonitorReader : public c4Reader
{
    public:
        BeamMonitorReader(EXT_STR_h101_BM_onion*, size_t);

        virtual ~BeamMonitorReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }
    
    private:
        unsigned int fNEvent;

        EXT_STR_h101_BM_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;
    
    public:
        ClassDefOverride(BeamMonitorReader, 0);
};

#endif