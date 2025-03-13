#ifndef GermaniumCal2Anl_H
#define GermaniumCal2Anl_H

#include "FairTask.h"
#include "TGermaniumConfiguration.h"
#include "BGOTwinpeaksCalData.h"

class TClonesArray;
class EventHeader;
class GermaniumCalData;

class GermaniumCal2Anl : public FairTask
{
    public:
        GermaniumCal2Anl();

        GermaniumCal2Anl(const TString& name, Int_t verbose);

        virtual ~GermaniumCal2Anl();
        
        void SetOnline(Bool_t set_online){fOnline = set_online;}


        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void SetParContainers();

        virtual InitStatus Init();


        void SetBGOVeto(bool v){BGO_veto = v;};
        void SetAddBackVeto(bool v){AddBack_veto = v;};
        void SetAddBackVetoThresholdEnergy(double v){addback_energy_threshold = v;};
        

    private:
        Bool_t fOnline;

        bool BGO_veto = true;
        bool AddBack_veto = true;
        
        double addback_energy_threshold = 100; //keV
        
        TClonesArray* fcal_ge_data;
        TClonesArray* fanl_ge_data;
        TClonesArray* fcal_bgo_data;
        
        TClonesArray* ftime_machine_array;
        
        const TGermaniumConfiguration *  germanium_configuration;

        GermaniumCalData* fcal_ge_hit;
        GermaniumCalData* fcal_ge_hit2;
        BGOTwinpeaksCalData* fcal_bgo_hit;



        EventHeader * header;
        Int_t fNEvents = 0;


    public:
        ClassDef(GermaniumCal2Anl, 1);
};

#endif
