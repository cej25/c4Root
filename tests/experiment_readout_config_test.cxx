#include "ExperimentReadoutConfig.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

static void rejected(const std::string& yaml) {
    std::istringstream input(yaml);
    try { c4::experiment::ReadoutConfig::Load(input); }
    catch (const std::exception&) { return; }
    throw std::runtime_error("Invalid readout YAML was accepted");
}

int main(int argc, char** argv) {
    if (argc != 2) throw std::runtime_error("Supply the readouts.yaml file path");
    const auto model = c4::experiment::ReadoutConfig::LoadFile(argv[1]);
    const auto& tamex = model.Select("FATIMA", "tamex");
    const auto& vme = model.Select("FATIMA", "vme");
    if (tamex.sources.at(0).procid != 75 ||
        tamex.sources.at(0).whiterabbit != 0x1600 ||
        vme.sources.at(0).modules.size() != 2 ||
        model.Select("bPlast", "tamex").sources.at(0).procid != 80 ||
        model.Select("BGO", "tamex").sources.at(0).procid != 100)
        throw std::runtime_error("Unexpected s100 readout model");

    rejected("FATIMA:\n  readouts:\n    tamex:\n      sources:\n        fatima:\n          procid: 75\n          procid: 80\n");
    rejected("FATIMA:\n  readouts:\n    tamex:\n      sources:\n        fatima:\n          procid: -1\n          modules:\n            sfp0:\n              digitiser: tamex\n              role: timing\n");
    rejected("FATIMA:\n  readouts:\n    tamex:\n      sources:\n        fatima:\n          procid: 75\n          modules:\n            sfp0:\n              digitiser: tamex\n              role: timing\n    vme:\n      sources:\n        fatimavme:\n          procid: 75\n          modules:\n            qdc:\n              digitiser: caen_v1751\n              role: energy\n");
    std::cout << "PASS: readout YAML loaded and invalid configurations rejected\n";
}
