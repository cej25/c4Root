#ifndef DEGAS_CAL2ANL_H
#define DEGAS_CAL2ANL_H

#include "FairTask.h"

class TBGOTwinpeaksConfiguration;
class TDegasConfiguration;
class TClonesArray;

class DegasCal2Anl : public FairTask
{
public:
    DegasCal2Anl(const TString& name = "DegasCal2Anl", Int_t verbose = 1);
    ~DegasCal2Anl() override;

    InitStatus Init() override;
    void Exec(Option_t*) override;
    void FinishEvent() override;

    void SetOnline(Bool_t online) { fOnline = online; }
    void SetBGOVeto(bool enabled) { fBGOVeto = enabled; }
    void SetAddBackVeto(bool enabled) { fAddBack = enabled; }
    void SetAddBackVetoThresholdEnergy(double energy) { fAddBackThreshold = energy; }

private:
    Bool_t fOnline = kFALSE;
    bool fBGOVeto = true;
    bool fAddBack = true;
    double fAddBackThreshold = 100; // keV

    const TDegasConfiguration* fConfig = nullptr; //! Run configuration
    const TBGOTwinpeaksConfiguration* fBGOConfig = nullptr; //! Veto timing
    const TClonesArray* fCal = nullptr; //! Calibrated DEGAS input
    const TClonesArray* fBGO = nullptr; //! Calibrated BGO input
    TClonesArray* fAnl; //! Analyzed DEGAS output

    ClassDefOverride(DegasCal2Anl, 1);
};

#endif
