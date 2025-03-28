#ifndef StefanReader_H
#define StefanReader_H

#include "c4Reader.h"
#include "StefanFebexData.h"
#include <Rtypes.h>

extern "C"
{
    #include "ext_h101_stefan.h"
}

class TClonesArray;

struct EXT_STR_h101_stefan_t;
typedef struct EXT_STR_h101_stefan_t EXT_STR_h101_stefan;
typedef struct EXT_STR_h101_stefan_onion_t EXT_STR_h101_stefan_onion;
class ext_data_struct_info;

class StefanReader : public c4Reader
{
    public:
        StefanReader(EXT_STR_h101_stefan_onion*, size_t);

        virtual ~StefanReader();


        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }


        void SetVetoPileupStatus(bool v){VetoPileup = v;}
        void SetVetoOverflowStatus(bool v){VetoOverflow = v;}
        void SetWriteZeroMultEvents(bool v){WriteZeroMultEvents = v;}
    
    private:
        unsigned int fNEvent;

        EXT_STR_h101_stefan_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        std::vector<StefanFebexItem>* stefanArray;


        const int NBoards = 6; // absolutely maximum for D28 :: (28 * 3 + 4 sci signals) / (16 ch/board)

        uint64_t event_trigger_time_long;
        double channel_trigger_time_long;

        int32_t channel_energy;


        uint64_t wr_t;


        bool VetoPileup = 1; //should I veto on Pileup flag?
        bool VetoOverflow = 1; //should I veto on overflow flag?
        bool WriteZeroMultEvents = 0; // Write triggered DAQ events with no channels fired?


    public:
        ClassDefOverride(StefanReader, 0);
};

#endif