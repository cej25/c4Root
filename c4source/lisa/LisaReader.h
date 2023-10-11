#ifndef LisaReader_H
#define LisaReader_H 

#include "c4Reader.h"
#include <Rtypes.h>

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_lisa.h"
}

class TClonesArray;

struct EXT_STR_h101_LISA_t;
typedef struct EXT_STR_h101_LISA_t EXT_STR_h101_LISA;
typedef struct EXT_STR_h101_LISA_onion_t EXT_STR_h101_LISA_onion;
class ext_data_struct_info;

class LisaReader : public c4Reader
{
    public:
        LisaReader(EXT_STR_h101_LISA_onion*, size_t);

        virtual ~LisaReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }
        void SetVetoPileupStatus(Bool_t v) { VetoPileup = v; }
        void SetVetoOverflowStatus(Bool_t v) { VetoOverflow = v; }
        void SetWriteZeroMultEvents(Bool_t v) { WriteZeroMultEvents = v; }

    private:
        unsigned fNEvent;

        EXT_STR_h101_LISA_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;
        TClonesArray* fTraceArray;

        uint64_t event_trigger_time_long;
        uint64_t channel_trigger_time_long;

        int32_t channel_energy;

        uint64_t wr_t;

        bool VetoPileup = 0;
        bool VetoOverflow = 0;
        bool WriteZeroMultEvents = 0;

    public:
        ClassDefOverride(LisaReader, 0);
};

#endif
