#ifndef AidaUnpack2Cal_H
#define AidaUnpack2Cal_H

#include "AidaData.h"
#include "AidaCalData.h"
#include "FairTask.h"
#include "TAidaConfiguration.h"
#include <vector>

class TClonesArray;
class TimeMachineData;


class AidaUnpack2Cal : public FairTask
{
public:
    AidaUnpack2Cal();
    virtual ~AidaUnpack2Cal();
    virtual void Exec(Option_t* option);
    virtual void SetParContainers();
    virtual InitStatus Init();
    void SetOnline(Bool_t option);
    void SetImplantOnline(Bool_t option) { fImplantOnline = option; }
    void SetDecayOnline(Bool_t option) { fDecayOnline = option; }
    void SetScalersOnline(Bool_t option) { fScalersOnline = option; }

    virtual void FinishTask();

private:
    std::vector<AidaUnpackAdcItem> const* unpackArray;
    std::vector<AidaUnpackScalerItem> const* scalerArray;
    std::vector<AidaCalAdcItem>* implantCalArray;
    std::vector<AidaCalAdcItem>* decayCalArray;
    TClonesArray* aidaTimeMachineArray;

    void SetParameter();
    bool fImplantOnline;
    bool fDecayOnline;
    bool fScalersOnline;

    TAidaConfiguration const* conf;
    unsigned int ignoredEvents;

    Int_t fExecs = 0;
    int total_time_microsecs = 0;

public:
    ClassDef(AidaUnpack2Cal, 2)
};

inline void AidaUnpack2Cal::SetOnline(Bool_t option)
{
    SetImplantOnline(option);
    SetDecayOnline(option);
    SetScalersOnline(option);
}

#endif /* AidaUnpack2Cal_H */

