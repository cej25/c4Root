#ifndef LYSORaw2Cal_H
#define LYSORaw2Cal_H

#include "FairTask.h"
#include "TLYSOConfiguration.h"

class TClonesArray;
class EventHeader;
class QDCData;
class LYSOCalData;

class LYSORaw2Cal : public FairTask
{
    public:
        LYSORaw2Cal();

        LYSORaw2Cal(const TString& name, Int_t verbose);

        virtual ~LYSORaw2Cal();
        
        void SetOnline(Bool_t set_online){fOnline = set_online;}

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void SetParContainers();

        virtual InitStatus Init();        

    private:
        Bool_t fOnline;

        TClonesArray* fcal_data;
        TClonesArray* funcal_data;
        
        const TLYSOConfiguration *  lyso_configuration;

        QDCData* funcal_hit;
        LYSOCalData* fcal_hit;


        EventHeader * header;
        Int_t fNEvents = 0;


    public:
        ClassDef(LYSORaw2Cal, 1);
};

#endif
