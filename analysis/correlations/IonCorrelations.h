#ifndef ION_CORRELATIONS_H
#define ION_CORRELATIONS_H

#include "FairTask.h"

#include <chrono>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

class FrsGate;

// Gate and target settings are applied during Init. FrsGate objects are borrowed.
class IonCorrelations : public FairTask
{
public:
    ~IonCorrelations() override;

    void SetGates(const std::vector<FrsGate*>& gates) { fGates = gates; }
    void RequireFrs(bool required = true) { fRequireFrs = required; }
    void CorrelateTargetStack(const std::string& target) { fTarget = target; }
    void CorrelateTarget(const std::string& target) { CorrelateTargetStack(target); }
    void CorrelateImplants() { fUseImplants = true; }
    void CorrelateImplantBetas(std::chrono::nanoseconds window);
    void CorrelateGammas(const std::string& detector);
    void CorrelateGammas(std::initializer_list<std::string> detectors);
    void CorrelateGammas(const std::string& first, const std::string& second)
    {
        CorrelateGammas({first, second});
    }
    void CorrelatePlastic() { fPlastic = true; }

    InitStatus Init() override;
    void Exec(Option_t*) override;
    void FinishTask() override;

protected:
    IonCorrelations(const char* name, bool online);

private:
    struct State;
    std::unique_ptr<State> fState; //! Runtime branches, histograms and implant history
    std::vector<FrsGate*> fGates; //! Borrowed PID gates
    std::vector<std::string> fGammas;
    std::string fTarget;
    std::chrono::nanoseconds fBetaWindow{0}; //! Configured implant-to-beta interval
    bool fUseBetas = false;
    bool fUseImplants = false;
    bool fPlastic = false;
    bool fRequireFrs = true;
    bool fOnline;

    ClassDefOverride(IonCorrelations, 0);
};

#endif
