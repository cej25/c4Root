#ifndef C4_EXPERIMENT_READOUT_CONFIG_H
#define C4_EXPERIMENT_READOUT_CONFIG_H

#include "ExperimentReadoutModel.h"
#include <cctype>
#include <fstream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace c4 { namespace experiment {

// Strict map-only subset of YAML, intentionally rejecting unsupported syntax.
// No ROOT, FairRoot or third-party YAML dependency. For readouts.yaml schema.
class ReadoutConfig {
    struct Node {
        std::map<std::string, Node> children;
        std::string value;
        bool scalar = false;
    };

    static std::string Trim(const std::string& s) {
        const auto b = s.find_first_not_of(" \t\r");
        if (b == std::string::npos) return {};
        const auto e = s.find_last_not_of(" \t\r");
        return s.substr(b, e - b + 1);
    }
    static const Node* Child(const Node& parent, const std::string& key,
                             const std::string& context) {
        const auto it = parent.children.find(key);
        if (it == parent.children.end())
            throw std::invalid_argument("Missing " + context + "." + key);
        return &it->second;
    }
    static void Keys(const Node& node, const std::string& context,
                     const std::vector<std::string>& allowed) {
        for (const auto& item : node.children) {
            bool found = false;
            for (const auto& key : allowed) if (item.first == key) found = true;
            if (!found)
                throw std::invalid_argument("Unsupported key " + context + "." + item.first);
        }
    }
    static std::string Scalar(const Node& node, const std::string& context) {
        if (!node.scalar || !node.children.empty() || node.value.empty())
            throw std::invalid_argument("Expected scalar at " + context);
        return node.value;
    }
    static std::string GetScalar(const Node& parent, const std::string& key,
                                 const std::string& context) {
        return Scalar(*Child(parent, key, context), context + "." + key);
    }
    static unsigned Number(const std::string& s, const std::string& context, unsigned max) {
        if (s.empty() || s[0] == '-' || s[0] == '+')
            throw std::invalid_argument("Invalid numeric value at " + context);
        const bool hex = s.size() > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X');
        if (hex && s.size() == 2)
            throw std::invalid_argument("Empty hex value at " + context);
        for (std::size_t i = hex ? 2 : 0; i < s.size(); ++i) {
            const unsigned char c = static_cast<unsigned char>(s[i]);
            if (hex ? !std::isxdigit(c) : !std::isdigit(c))
                throw std::invalid_argument("Invalid numeric value at " + context);
        }
        try {
            const unsigned long value = std::stoul(s, nullptr, hex ? 16 : 10);
            if (value > max) throw std::out_of_range("out of range");
            return static_cast<unsigned>(value);
        } catch (const std::exception&) {
            throw std::invalid_argument("Numeric value out of range at " + context);
        }
    }
    static Node Parse(std::istream& input) {
        Node root;
        std::vector<Node*> parents{&root};
        std::string line;
        unsigned lineno = 0;
        while (std::getline(input, line)) {
            ++lineno;
            if (line.find('\t') != std::string::npos)
                throw std::invalid_argument("Tabs not supported at line " + std::to_string(lineno));
            const auto comment = line.find('#');
            if (comment != std::string::npos) line.resize(comment);
            if (Trim(line).empty()) continue;
            const auto n = line.find_first_not_of(' ');
            if (n == std::string::npos || n % 2 != 0)
                throw std::invalid_argument("Expected two-space indentation at line " + std::to_string(lineno));
            const auto depth = n / 2;
            if (depth >= parents.size())
                throw std::invalid_argument("Skipped indentation level at line " + std::to_string(lineno));
            const std::string entry = line.substr(n);
            const auto colon = entry.find(':');
            if (colon == std::string::npos)
                throw std::invalid_argument("Expected map entry at line " + std::to_string(lineno));
            const std::string key = Trim(entry.substr(0, colon));
            const std::string value = Trim(entry.substr(colon + 1));
            if (key.empty() || key.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-") != std::string::npos)
                throw std::invalid_argument("Invalid mapping key at line " + std::to_string(lineno));
            parents.resize(depth + 1);
            Node* parent = parents.back();
            if (parent->scalar)
                throw std::invalid_argument("Scalar cannot contain children at line " + std::to_string(lineno));
            const auto inserted = parent->children.emplace(key, Node{});
            if (!inserted.second)
                throw std::invalid_argument("Duplicate mapping key " + key + " at line " + std::to_string(lineno));
            Node* child = &inserted.first->second;
            child->scalar = !value.empty();
            child->value = value;
            parents.push_back(child);
        }
        return root;
    }

public:
    static ReadoutModel Load(std::istream& input) {
        const Node root = Parse(input);
        if (root.children.empty())
            throw std::invalid_argument("Readout configuration is empty");
        ReadoutModel model;
        for (const auto& subsystem_item : root.children) {
            const auto& cfg = subsystem_item.second;
            const auto ctx = subsystem_item.first;
            Keys(cfg, ctx, {"readouts"});
            Subsystem subsystem;
            subsystem.name = ctx;
            const auto& paths = *Child(cfg, "readouts", ctx);
            if (paths.scalar)
                throw std::invalid_argument("Expected readouts map at " + ctx);
            for (const auto& path_item : paths.children) {
                ReadoutPath path;
                path.name = path_item.first;
                const auto path_ctx = ctx + ".readouts." + path.name;
                Keys(path_item.second, path_ctx, {"sources"});
                const auto& sources = *Child(path_item.second, "sources", path_ctx);
                if (sources.scalar)
                    throw std::invalid_argument("Expected sources map at " + path_ctx);
                for (const auto& source_item : sources.children) {
                    const auto src_ctx = path_ctx + ".sources." + source_item.first;
                    const auto& source_cfg = source_item.second;
                    Keys(source_cfg, src_ctx, {"procid", "whiterabbit", "modules"});
                    ElectronicsSource source;
                    source.event_member = source_item.first;
                    source.procid = static_cast<std::uint16_t>(Number(
                        GetScalar(source_cfg, "procid", src_ctx), src_ctx + ".procid", 65535));
                    if (source_cfg.children.count("whiterabbit"))
                        source.whiterabbit = static_cast<std::uint16_t>(Number(
                            GetScalar(source_cfg, "whiterabbit", src_ctx), src_ctx + ".whiterabbit", 65535));
                    const auto& modules = *Child(source_cfg, "modules", src_ctx);
                    if (modules.scalar)
                        throw std::invalid_argument("Expected modules map at " + src_ctx);
                    for (const auto& module_item : modules.children) {
                        const auto mod_ctx = src_ctx + ".modules." + module_item.first;
                        const auto& module_cfg = module_item.second;
                        Keys(module_cfg, mod_ctx, {"digitiser", "version", "role"});
                        DigitiserModule module;
                        module.address = module_item.first;
                        module.type = GetScalar(module_cfg, "digitiser", mod_ctx);
                        module.role = GetScalar(module_cfg, "role", mod_ctx);
                        if (module_cfg.children.count("version"))
                            module.version = Number(GetScalar(module_cfg, "version", mod_ctx),
                                                    mod_ctx + ".version", std::numeric_limits<unsigned>::max());
                        source.modules.push_back(std::move(module));
                    }
                    path.sources.push_back(std::move(source));
                }
                subsystem.readouts.push_back(std::move(path));
            }
            model.AddSubsystem(std::move(subsystem));
        }
        return model;
    }
    static ReadoutModel LoadFile(const std::string& filename) {
        std::ifstream input(filename);
        if (!input)
            throw std::runtime_error("Cannot open readout configuration: " + filename);
        return Load(input);
    }
};
}} // namespace c4::experiment
#endif
