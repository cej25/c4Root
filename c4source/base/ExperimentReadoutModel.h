#ifndef C4_EXPERIMENT_READOUT_MODEL_H
#define C4_EXPERIMENT_READOUT_MODEL_H

#include <cstdint>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// Configuration model, independent of ROOT, FairRoot and YAML parsing.
// A readout path can combine several UCESB sources, and each source can
// contain several digitiser modules (e.g. FATIMA VME QDC + TDC).
namespace c4 {
namespace experiment {

struct DigitiserModule {
    std::string type;
    unsigned version = 0;          // 0 = unspecified / not applicable
    std::string role;              // e.g. energy, timing
    std::string address;           // experiment-local module identifier
};

struct ElectronicsSource {
    std::string event_member;      // field in the UCESB EVENT structure
    std::uint16_t procid = 0;
    std::uint16_t whiterabbit = 0; // 0 = no configured WR identifier
    std::vector<DigitiserModule> modules;
};

struct ReadoutPath {
    std::string name;              // e.g. tamex, vme
    std::vector<ElectronicsSource> sources;
};

struct Subsystem {
    std::string name;              // e.g. FATIMA, LISA, FRS
    std::vector<ReadoutPath> readouts;
};

class ReadoutModel {
public:
    void AddSubsystem(Subsystem subsystem) {
        if (subsystem.name.empty())
            throw std::invalid_argument("Subsystem name must not be empty");
        for (const auto& existing : subsystems_)
            if (existing.name == subsystem.name)
                throw std::invalid_argument("Duplicate subsystem: " + subsystem.name);
        subsystems_.push_back(std::move(subsystem));
        try { Validate(); }
        catch (...) { subsystems_.pop_back(); throw; }
    }

    const Subsystem& GetSubsystem(const std::string& name) const {
        for (const auto& subsystem : subsystems_)
            if (subsystem.name == name) return subsystem;
        throw std::invalid_argument("Unknown subsystem: " + name);
    }

    const ReadoutPath& Select(const std::string& subsystem_name,
                              const std::string& readout_name) const {
        const auto& subsystem = GetSubsystem(subsystem_name);
        for (const auto& path : subsystem.readouts)
            if (path.name == readout_name) return path;
        throw std::invalid_argument("Unknown readout " + subsystem_name + "/" + readout_name);
    }

    void Validate() const {
        std::set<std::string> names;
        std::set<std::string> event_members;
        std::set<std::uint16_t> procids;
        for (const auto& subsystem : subsystems_) {
            if (subsystem.name.empty() || !names.insert(subsystem.name).second)
                throw std::invalid_argument("Empty or duplicate subsystem name");
            if (subsystem.readouts.empty())
                throw std::invalid_argument("No readout paths for " + subsystem.name);
            std::set<std::string> paths;
            for (const auto& path : subsystem.readouts) {
                if (path.name.empty() || !paths.insert(path.name).second)
                    throw std::invalid_argument("Empty or duplicate readout path in " + subsystem.name);
                if (path.sources.empty())
                    throw std::invalid_argument("No sources for " + subsystem.name + "/" + path.name);
                for (const auto& source : path.sources) {
                    if (source.event_member.empty() ||
                        !event_members.insert(source.event_member).second)
                        throw std::invalid_argument("Empty or reused UCESB EVENT member: " + source.event_member);
                    if (!procids.insert(source.procid).second)
                        throw std::invalid_argument("Repeated source procid: " + std::to_string(source.procid));
                    if (source.modules.empty())
                        throw std::invalid_argument("No digitiser modules for " + source.event_member);
                    std::set<std::string> addresses;
                    for (const auto& module : source.modules) {
                        if (module.type.empty() || module.role.empty())
                            throw std::invalid_argument("Digitiser type and role are required for " + source.event_member);
                        if (!module.address.empty() && !addresses.insert(module.address).second)
                            throw std::invalid_argument("Duplicate module address in " + source.event_member);
                    }
                }
            }
        }
    }

    const std::vector<Subsystem>& Subsystems() const { return subsystems_; }

private:
    std::vector<Subsystem> subsystems_;
};

} // namespace experiment
} // namespace c4

#endif
