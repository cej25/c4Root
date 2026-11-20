#ifndef DEGAS_RAW_TO_CAL_H
#define DEGAS_RAW_TO_CAL_H

#include "FairTask.h"

class DegasRawData;
class TClonesArray;
class TGermaniumConfiguration;

class DegasRaw2Cal : public FairTask
{
public:
    DegasRaw2Cal();
    ~DegasRaw2Cal() override;

    InitStatus Init() override;
    void Exec(Option_t*) override;
    void FinishEvent() override;

    void SetOnline(Bool_t online) { fOnline = online; }
    void SetVetoPileup(bool veto) { fVetoPileup = veto; }
    void SetVetoOverflow(bool veto) { fVetoOverflow = veto; }

    ClassDefOverride(DegasRaw2Cal, 0);

private:
    const DegasRawData* fRaw = nullptr; //! Borrowed detector input
    const TGermaniumConfiguration* fConfig = nullptr; //! Run configuration
    TClonesArray* fCal = nullptr; //! Owns calibrated hits
    TClonesArray* fTimeMachine = nullptr; //! Owns timing records
    Bool_t fOnline = kFALSE;
    bool fVetoPileup = true;
    bool fVetoOverflow = true;
};

#endif
