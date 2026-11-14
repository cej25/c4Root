#include "../c4source/base/TamexPackedSafety.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    // CI executes standalone tests from the repository root. The same command
    // works locally: g++ -std=c++17 tests/detector_fixture_regression_test.cxx
    // -o /tmp/detector_fixtures && /tmp/detector_fixtures
    std::ifstream input("tests/fixtures/tamex_payload_cases.txt");
    if (!input)
    {
        std::cerr << "Unable to open TAMEX regression fixture\n";
        return 1;
    }

    std::size_t cases = 0;
    std::string line;
    while (std::getline(input, line))
    {
        if (line.empty() || line.front() == '#') continue;

        std::istringstream fields(line);
        std::string name;
        std::uint64_t bytes = 0, index = 0, epoch = 0, coarse = 0;
        std::uint64_t fine = 0, channel = 0, edge = 0, channel_id = 0;
        std::uint64_t fine_code = 0, expected_budget = 0;
        unsigned expected_complete = 0, expected_accepted = 0;
        if (!(fields >> name >> bytes >> index >> epoch >> coarse >> fine >>
                  channel >> edge >> channel_id >> fine_code >> expected_budget >>
                  expected_complete >> expected_accepted))
        {
            std::cerr << "Malformed fixture: " << line << '\n';
            return 1;
        }
        std::string surplus;
        if (fields >> surplus)
        {
            std::cerr << "Unexpected extra fixture field: " << name << '\n';
            return 1;
        }

        const auto budget = c4_tamex_packed_safety::EventHitBudget(
            static_cast<std::uint32_t>(bytes));
        const bool complete = c4_tamex_packed_safety::HasCompleteHit(
            static_cast<std::uint32_t>(index),
            static_cast<std::uint32_t>(epoch),
            static_cast<std::uint32_t>(coarse),
            static_cast<std::uint32_t>(fine),
            static_cast<std::uint32_t>(channel),
            static_cast<std::uint32_t>(edge));
        const bool accepted = index < budget && complete &&
            c4_tamex_packed_safety::ValidChannel(
                static_cast<std::uint32_t>(channel_id), 33) &&
            c4_tamex_packed_safety::ValidFineBin(
                static_cast<std::uint32_t>(fine_code), 1024);

        if (budget != expected_budget || complete != (expected_complete != 0) ||
            accepted != (expected_accepted != 0))
        {
            std::cerr << "Fixture mismatch: " << name << " (budget=" << budget
                      << ", complete=" << complete << ", accepted=" << accepted
                      << ")\n";
            return 1;
        }
        ++cases;
    }

    if (cases < 10)
    {
        std::cerr << "Too few TAMEX regression fixtures: " << cases << '\n';
        return 1;
    }
    std::cout << "Verified " << cases << " TAMEX payload regression fixtures\n";
    return 0;
}
