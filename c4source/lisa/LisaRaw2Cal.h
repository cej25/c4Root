#ifndef LisaRaw2Cal_H
#define LisaRaw2Cal_H

#include "TClonesArray.h"
#include "EventHeader.h"
#include "TLisaConfiguration.h"
#include "LisaData.h"
#include "LisaCalData.h"
#include <map>
#include "TClonesArray.h"

class EventHeader;
class LisaData;
class LisaCalData;
class TClonesArray;

class LisaRaw2Cal : public FairTask
{
    public:
        LisaRaw2Cal();

        virtual ~LisaRaw2Cal();

        virtual InitStatus Init();

        virtual void Exec (Option_t* option);

        virtual void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishEvent();
        virtual void FinishTask();

    private:
        TLisaConfiguration const* lisa_config;

        TClonesArray* fLisaArray;
        TClonesArray* fLisaCalArray;
        //TClonesArray* fTimeMachineArray;

        EventHeader* header;
        Bool_t fOnline;
        Int_t fNEvents;

        uint64_t wr_t;

        //int NBoards = 1; 

        std::map<std::pair<int, int>, std::pair<std::pair<int,std::string>, std::pair<int, int>>> detector_mapping;

        std::vector<int> data_boards;
        std::vector<uint32_t> data_channel;
        std::vector<uint32_t> data_energy;
        std::vector<uint32_t> data_traces;
        std::vector<uint32_t> data_multiplicity;


    public:
        ClassDef(LisaRaw2Cal, 1)

};



#endif