#include "../c4source/fatima/FatimaVmeQdcSafety.h"
#include "../c4source/fimp/FimpMultihitSafety.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::ifstream input("tests/fixtures/fatima_vme_qdc_cases.txt");
    if (!input) { std::cerr << "Missing FATIMA QDC fixtures\n"; return 1; }
    std::size_t n = 0;
    std::string line;
    while (std::getline(input, line))
    {
        if (line.empty() || line.front() == '#') continue;
        std::istringstream row(line);
        std::string name, extra;
        std::uint32_t index, coarse, extended, fine, qlong, qshort;
        std::uint32_t w1, w2, w3, expected_triplets;
        unsigned expected_hit;
        if (!(row >> name >> index >> coarse >> extended >> fine >> qlong >>
                  qshort >> w1 >> w2 >> w3 >> expected_hit >> expected_triplets) ||
            (row >> extra))
        {
            std::cerr << "Malformed QDC fixture: " << line << '\n';
            return 1;
        }
        const bool hit = fatima_vme_qdc_safety::CompleteEntry(
            index, coarse, extended, fine, qlong, qshort);
        const auto triplets = fatima_vme_qdc_safety::CompleteWaveformTriplets(w1, w2, w3);
        if (hit != (expected_hit != 0) || triplets != expected_triplets)
        {
            std::cerr << "QDC mismatch: " << name << '\n';
            return 1;
        }
        ++n;
    }
    if (n < 10) { std::cerr << "Too few QDC fixtures\n"; return 1; }

    // Event-style FIMP cases: aligned and misaligned lead/trail buffers,
    // packed block endpoints, and the calibration bin boundary.
    using namespace fimp_multihit_safety;
    if (MatchedHitCount(3, 3, 3, 3) != 3 ||
        MatchedHitCount(3, 2, 3, 3) != 2 ||
        MatchedHitCount(3, 3, 0, 3) != 0 ||
        !ValidPackedHitBlock(0, 3, 3, 3, 3, 33024) ||
        ValidPackedHitBlock(0, 4, 3, 4, 4, 33024) ||
        ValidPackedHitBlock(-1, 1, 3, 3, 3, 33024) ||
        ValidPackedHitBlock(2, 1, 3, 3, 3, 33024) ||
        !ValidFineTimeIndex(258, 259, 1023, 1024) ||
        ValidFineTimeIndex(259, 259, 1023, 1024) ||
        ValidFineTimeIndex(258, 259, 1024, 1024))
    {
        std::cerr << "FIMP combined payload regression mismatch\n";
        return 1;
    }
    std::cout << "Verified " << n << " FATIMA QDC fixtures and FIMP combined cases\n";
    return 0;
}
