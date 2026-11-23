#ifndef FATIMA_VME_CALIBRATOR_H
#define FATIMA_VME_CALIBRATOR_H

#include "RtypesCore.h"
#include "TClonesArray.h"
#include <map>
#include <utility>

class FairRootManager;
struct FatimaVmeChainRaw;
class V1751RawData;
class V1290RawData;
class TFatimaVmeConfiguration;

// Internal FATIMA VME processor, not a FairTask. FatimaRaw2Cal owns
// the lifecycle; generic V1751/V1290 readers own raw electronics decoding.
class FatimaVmeCalibrator {
public:
    FatimaVmeCalibrator();
    ~FatimaVmeCalibrator();

    FatimaVmeCalibrator(const FatimaVmeCalibrator&) = delete;
    FatimaVmeCalibrator& operator=(const FatimaVmeCalibrator&) = delete;

    bool Init(FairRootManager* manager, Bool_t persist, const FatimaVmeChainRaw* chain);
    void Process();
    void Clear();

private:
    void ProcessQdc(const V1751RawData& raw);
    void ProcessTdc(const V1290RawData& raw, int allocationChannel);

    const FatimaVmeChainRaw* fChain = nullptr; // borrowed
    TClonesArray* fQdcInput = nullptr; // borrowed
    TClonesArray* fTdcInput = nullptr; // borrowed
    TClonesArray* fQdcOutput = nullptr; // owned
    TClonesArray* fTdcOutput = nullptr; // owned
    std::map<std::pair<int, int>, int> fQdcMapping;
    std::map<std::pair<int, int>, int> fTdcMapping;
    double** fEnergyCoefficients = nullptr; // borrowed from configuration
    double* fQdcTimeOffsets = nullptr; // borrowed from configuration
    double* fTdcTimeOffsets = nullptr; // borrowed from configuration
};
#endif
