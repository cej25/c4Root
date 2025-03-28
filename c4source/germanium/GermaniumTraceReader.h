#ifndef GermaniumTraceReader_H
#define GermaniumTraceReader_H

#include "c4Reader.h"

#include <Rtypes.h>

extern "C"
{
    #include "ext_h101_germanium_traces.h"
}

class TClonesArray;

struct EXT_STR_h101_germanium_traces_t;
typedef struct EXT_STR_h101_germanium_traces_t EXT_STR_h101_germanium_traces;
typedef struct EXT_STR_h101_germanium_traces_onion_t EXT_STR_h101_germanium_traces_onion;
class ext_data_struct_info;

class GermaniumTraceReader : public c4Reader
{
    public:
        GermaniumTraceReader(EXT_STR_h101_germanium_traces_onion*, size_t);

        virtual ~GermaniumTraceReader();


        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }


        void SetVetoPileupStatus(bool v){VetoPileup = v;}
        void SetVetoOverflowStatus(bool v){VetoOverflow = v;}
        void SetWriteZeroMultEvents(bool v){WriteZeroMultEvents = v;}
    
    private:
        unsigned int fNEvent;

        EXT_STR_h101_germanium_traces_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;


        const int NBoards = 4; //change

        uint64_t event_trigger_time_long;
        double channel_trigger_time_long;

        int32_t channel_energy;


        uint64_t wr_t;


        bool VetoPileup = 1; //should I veto on Pileup flag?
        bool VetoOverflow = 1; //should I veto on overflow flag?
        bool WriteZeroMultEvents = 0; // Write triggered DAQ events with no channels fired?


    public:
        ClassDefOverride(GermaniumTraceReader, 0);
};

#endif