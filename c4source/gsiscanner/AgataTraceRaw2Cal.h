#ifndef AgataTraceRaw2Cal_H
#define AgataTraceRaw2Cal_H

#include "FairTask.h"
#include "TAgataConfiguration.h"

class TClonesArray;
class EventHeader;
class GermaniumFebexTraceData;
class AgataSuperTraceData;

class AgataTraceRaw2Cal : public FairTask
{
    public:
        AgataTraceRaw2Cal();

        AgataTraceRaw2Cal(const TString& name, Int_t verbose);

        virtual ~AgataTraceRaw2Cal();
        
        void SetOnline(Bool_t set_online){fOnline = set_online;}

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void SetParContainers();

        virtual InitStatus Init();

    private:
        Bool_t fOnline;

        TClonesArray* fcal_data;
        TClonesArray* funcal_data;
        
        const TAgataConfiguration *  agata_configuration;

        GermaniumFebexTraceData* funcal_hit;
        AgataSuperTraceData* fcal_hit;


        EventHeader * header;
        Int_t fNEvents = 0;


    public:
        ClassDef(AgataTraceRaw2Cal, 1);
};

#endif
