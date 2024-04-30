#ifndef AidaReader_h
#define AidaReader_h

#include "AidaData.h"
#include "c4Reader.h"

#include <Rtypes.h>

extern "C"
{
    #include "ext_h101_aida.h" // name??
}

class AidaReader : public c4Reader
{
    public:
        AidaReader(EXT_STR_h101_aida_onion*, size_t);

        virtual ~AidaReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetAdcOnline(Bool_t option) { fAdcOnline = option; }
        void SetFlowScalerOnline(Bool_t option) { fFlowScalerOnline = option; }
        void SetOnline(Bool_t option) { SetAdcOnline(option); SetFlowScalerOnline(option); }
    
    private:
        Int_t fNEvent = 0;
        int total_time_microsecs = 0;
        EventHeader* header;

        EXT_STR_h101_aida_onion* fData;

        size_t fOffset;

        Bool_t fAdcOnline;
        Bool_t fFlowScalerOnline;

        // Data to register here
        std::vector<AidaUnpackAdcItem>* adcArray;
        std::vector<AidaUnpackFlowItem>* flowArray;
        std::vector<AidaUnpackScalerItem>* scalerArray;
    
    public:
        ClassDefOverride(AidaReader, 0);
};

#endif
