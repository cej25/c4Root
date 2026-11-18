#ifndef C4_FATIMA_VME_ELECTRONICS_RAW2CAL_H
#define C4_FATIMA_VME_ELECTRONICS_RAW2CAL_H

#include "FairTask.h"
#include "TClonesArray.h"
#include <map>
#include <utility>

class TFatimaVmeConfiguration;

// Detector-specific layer: map and calibrate generic electronics records.
// No legacy vector raw data and no per-event fixed-size scratch arrays.
class FatimaVmeElectronicsRaw2Cal : public FairTask {
public:
    FatimaVmeElectronicsRaw2Cal();
    ~FatimaVmeElectronicsRaw2Cal() override;
    InitStatus Init() override;
    void Exec(Option_t*) override;
    void FinishEvent() override;
    void SetOnline(Bool_t on) { fOnline = on; }
private:
    Bool_t fOnline = kFALSE;
    TClonesArray* fQdcInput = nullptr; //! Borrowed
    TClonesArray* fTdcInput = nullptr; //! Borrowed
    TClonesArray* fQdcOutput = nullptr; //! Owned
    TClonesArray* fTdcOutput = nullptr; //! Owned
    const TFatimaVmeConfiguration* fConfig = nullptr; //!
    std::map<std::pair<int,int>,int> fQdcMapping;
    std::map<std::pair<int,int>,int> fTdcMapping;
    double** fEnergyCoefficients = nullptr; //!
    double* fQdcTimeOffsets = nullptr; //!
    double* fTdcTimeOffsets = nullptr; //!
    ClassDefOverride(FatimaVmeElectronicsRaw2Cal, 1);
};
#endif
