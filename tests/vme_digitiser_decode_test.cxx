#include "../c4source/bb7/ext_h101_bb7vme.h"
#include "../c4source/digitisers/vme/VmeDigitiserDecode.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>

struct MockQdc {
    std::uint32_t _channels = 0;
    std::uint32_t _channel_time = 0, _chan_ext_time = 0;
    std::uint32_t _chan_fine_time = 0, _qlong = 0, _qshort = 0;
    std::int32_t _board_id = 6;
};
struct MockTdc {
    std::uint32_t _measurement_nM = 0, _measurement_n = 0;
    std::uint32_t _measurement_leadOrTrail = 0;
    std::uint32_t _measurement_nMI[128] = {};
    std::uint32_t _measurement_nME[128] = {};
    std::int32_t _geo = 2;
};
int main() {
    const std::uint16_t ts[] = {0x1234, 0x5678, 0x9abc, 0xdef0};
    assert(c4::vme::Timestamp(ts) == 0xdef09abc56781234ULL);

    EXT_STR_h101_bb7vme_onion bb7 = {};
    auto& v775 = bb7.bbseven_v7x5[1];
    v775.geo = 13;
    v775.n = 3;
    v775.nI[0] = 1;  // Physical channel 0 with a recorded zero.
    v775.nI[1] = 32; // Physical channel 31 with all status bits set.
    v775.data[1] = 0x7fff;
    v775.nI[2] = 33; // Outside the module's 32 channels.
    using V775Hit = std::tuple<std::uint32_t, std::uint32_t, std::uint32_t, std::int32_t>;
    std::vector<V775Hit> hits;
    for (const auto& module : bb7.bbseven_v7x5)
        c4::vme::DecodeV775(module.n, module.nI, module.data,
            [&](auto channel, auto value, auto status) {
                hits.emplace_back(module.geo, channel, value, status);
            });
    assert((hits == std::vector<V775Hit>{{13, 0, 0, 0}, {13, 31, 4095, 7}}));

    MockQdc qdc;
    qdc._channels = (1u << 1) | (1u << 6);
    qdc._channel_time = 2;
    qdc._chan_ext_time = 2;
    qdc._chan_fine_time = 2;
    qdc._qlong = 2;
    qdc._qshort = 2;
    std::vector<std::uint32_t> channels, offsets;
    c4::vme::DecodeV1751(qdc, 0,
        [&](std::size_t slot, int board, std::uint32_t channel,
            std::uint32_t packed, const auto&) {
            assert(slot == 0 && board == 6);
            channels.push_back(channel);
            offsets.push_back(packed);
        });
    assert((channels == std::vector<std::uint32_t>{1, 6}));
    assert((offsets == std::vector<std::uint32_t>{0, 1}));
    qdc._qshort = 1; // second packed QDC entry is incomplete
    channels.clear();
    c4::vme::DecodeV1751(qdc, 0,
        [&](std::size_t, int, std::uint32_t channel, std::uint32_t, const auto&) {
            channels.push_back(channel);
        });
    assert((channels == std::vector<std::uint32_t>{1}));

    MockTdc tdc;
    tdc._measurement_nM = 3;
    tdc._measurement_n = 4;
    tdc._measurement_leadOrTrail = 4;
    tdc._measurement_nMI[0] = 2;
    tdc._measurement_nME[0] = 2; // 2 hits
    tdc._measurement_nMI[1] = 3;
    tdc._measurement_nME[1] = 8; // malformed, skip
    tdc._measurement_nMI[2] = 4;
    tdc._measurement_nME[2] = 9; // malformed, skip
    int hit_count = 0;
    c4::vme::DecodeV1290(tdc, 1,
        [&](std::size_t slot, int geo, std::uint32_t channel,
            std::uint32_t index, const auto&) {
            assert(slot == 1 && geo == 2 && channel == 2 && index < 2);
            ++hit_count;
        });
    assert(hit_count == 2);
    std::cout << "PASS: generic VME channel and packed block decoding\n";
}
