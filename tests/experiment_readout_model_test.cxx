#include "ExperimentReadoutModel.h"
#include <cassert>
#include <stdexcept>

int main() {
    using namespace c4::experiment;
    ReadoutModel model;
    model.AddSubsystem({"FATIMA", {
        {"tamex", {{"fatima", 75, 0x1600, {{"tamex", 4, "time_and_tot", "sfp0"}}}}},
        {"vme", {{"fatimavme", 70, 0x1500, {
            {"caen_v1751", 0, "energy", "qdc0"},
            {"caen_v1290", 0, "timing", "tdc0"}}}}}
    }});
    assert(model.Select("FATIMA", "tamex").sources[0].procid == 75);
    assert(model.Select("FATIMA", "vme").sources[0].modules.size() == 2);
    try {
        model.AddSubsystem({"BGO", {{"tamex", {{"bgo", 75, 0x1900, {{"tamex", 4, "timing", "sfp1"}}}}}}});
        assert(false && "Duplicate procid accepted");
    } catch (const std::invalid_argument&) {}
    assert(model.Subsystems().size() == 1); // AddSubsystem failure rolls back
    try { model.Select("FATIMA", "missing"); assert(false); }
    catch (const std::invalid_argument&) {}
}
