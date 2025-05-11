// header link
#include "ext_unpacking.hh"
#include "unpack_aida.hh"
#include "unpack_structures.hh"

// ucesb internals
#include "data_src.hh"
#include "enumerate.hh"
#include "simple_data_ops.hh"
#include "zero_suppress.hh"
#include "zero_suppress_map.hh"
#include "error.hh"

// c++ stuff
#include <algorithm>
#include <iterator>
#include <set>
#include <inttypes.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unistd.h>

#if AIDA_UNPACK_STATS
inline std::string wr_to_string(uint64_t wr)
{
    time_t time = wr / 1000000000LL;
    struct tm* timeinfo;
    timeinfo = gmtime(&time);
    static char buf[63];
    strftime(buf, sizeof(buf), "%c TAI", timeinfo);
    std::string sstr(buf);
    return sstr;
}

inline double wr_to_duration(uint64_t start, uint64_t stop)
{
    double duration = static_cast<double>(stop - start) / 1e9;
    return duration;
}

inline std::string frequency(uint64_t counts, double duration)
{
    if (duration == 0)
    {
        return "0 Hz";
    }
    int hz = static_cast<int>(counts / (uint64_t)duration);
    int unit = hz;
    std::string suffix = "Hz";

    if (hz > 1000000)
    {
        unit /= 1000000;
        suffix = "MHz";
    }
    else if (hz > 1000)
    {
        unit /= 1000;
        suffix = "kHz";
    }

    std::stringstream s;
    s << std::setprecision(2) << unit << " " << suffix;
    return s.str();
}

#endif

EXT_AIDA::EXT_AIDA()
{
    std::fill(&fast_times[0][0], &fast_times[0][0] + sizeof(fast_times) / sizeof(fast_times[0][0]), 0);
    std::fill(std::begin(scalers), std::end(scalers), 0);
#if AIDA_UNPACK_STATS
    stats = {};
    std::fill(std::begin(stats_fee), std::end(stats_fee), AidaUnpackerStats{});
    last_adc_timestamp = 0;
    std::fill(std::begin(last_adc_timestamp_fee), std::end(last_adc_timestamp_fee), 0);
    pause_time = 0;
    std::fill(std::begin(pause_time_fee), std::end(pause_time_fee), 0);
#endif
    __clean();
}

EXT_AIDA::~EXT_AIDA()
{
#if AIDA_UNPACK_STATS
    if (stats.Events == 0) return;
    int width = static_cast<int>(std::log10(stats.DataItems)) + 1;
    std::cout << "==========================================" << std::endl;
    std::cout << "AIDA Unpacker Analysis" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "First event: " << wr_to_string(stats.Start) << std::endl;
    std::cout << "Last event : " << wr_to_string(stats.Stop) << std::endl;
    double duration = wr_to_duration(stats.Start, stats.Stop);
    std::cout << "Duration   : " << duration << " seconds" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
#define AIDA_STATISTIC(x) std::setw(width) << x << " (" << frequency(x, duration) << ")" << std::endl;
    std::cout << "Events       (E): " << AIDA_STATISTIC(stats.Events);
    std::cout << "Data Items   (M): " << AIDA_STATISTIC(stats.DataItems);
    std::cout << "ADC Items    (A): " << AIDA_STATISTIC(stats.Type.ADC);
    std::cout << "-- Decays    (D): " << AIDA_STATISTIC(stats.AdcType.Decay);
    std::cout << "-- Implants  (I): " << AIDA_STATISTIC(stats.AdcType.Implant);
    std::cout << "INFO Items   (F): " << AIDA_STATISTIC(stats.Type.Info);
    std::cout << "-- PAUSE     (p): " << AIDA_STATISTIC(stats.InfoType.Pause);
    std::cout << "-- RESUME    (r): " << AIDA_STATISTIC(stats.InfoType.Resume);
    std::cout << "-- WR4828    (W): " << AIDA_STATISTIC(stats.InfoType.Sync48);
    std::cout << "-- WR6348    (w): " << AIDA_STATISTIC(stats.InfoType.Sync63);
    std::cout << "-- Discrim   (d): " << AIDA_STATISTIC(stats.InfoType.Discriminator);
    std::cout << "-- Scaler    (c): " << AIDA_STATISTIC(stats.InfoType.Scaler);
    std::cout << "Timewarps    (T): " << AIDA_STATISTIC(stats.TimeWarps);
    std::cout << "Dead Time    (X): " << std::setprecision(width-4) << ((double)stats.DeadTime / 1e9) << " s ("
        << (100. * (double)stats.DeadTime / (double)(stats.Stop - stats.Start)) << "%)" << std::endl;
    std::cout << std::endl;

    std::cout << "==========================================" << std::endl;
    std::cout << "Individual FEE Overview" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << std::setw(4) << "FEE" << " | " << std::setw(4)
        << std::setw(width) << "M" <<  " "
        << std::setw(width) << "A" <<  " "
        << std::setw(width) << "D" <<  " "
        << std::setw(width) << "I" <<  " "
        << std::setw(width) << "F" <<  " "
        << std::setw(width) << "p" <<  " "
        << std::setw(width) << "r" <<  " "
        << std::setw(width) << "d" <<  " "
        << std::setw(width) << "c" <<  " "
        << std::setw(width) << "T" <<  " "
        << "X"
        << std::endl;
    for (int i = 0; i < AIDA_MAX_FEES; i++)
    {
        std::cout << std::setw(4) << (i+1) << " | " << std::setw(4)
            << std::setw(width) << stats_fee[i].DataItems <<  " "
            << std::setw(width) << stats_fee[i].Type.ADC <<  " "
            << std::setw(width) << stats_fee[i].AdcType.Decay <<  " "
            << std::setw(width) << stats_fee[i].AdcType.Implant <<  " "
            << std::setw(width) << stats_fee[i].Type.Info <<  " "
            << std::setw(width) << stats_fee[i].InfoType.Pause <<  " "
            << std::setw(width) << stats_fee[i].InfoType.Resume <<  " "
            << std::setw(width) << stats_fee[i].InfoType.Discriminator <<  " "
            << std::setw(width) << stats_fee[i].InfoType.Scaler <<  " "
            << std::setw(width) << stats_fee[i].TimeWarps <<  " "
            << std::setprecision(width - 4) << (100. * (double)stats_fee[i].DeadTime / (double)(stats.Stop - stats.Start)) << "%"
        << std::endl;
    }
#endif
}

void EXT_AIDA::__clean()
{
    std::fill(&multiplexer[0][0], &multiplexer[0][0] + sizeof(multiplexer) / sizeof(multiplexer[0][0]), 0);
    std::fill(&asic_last[0][0], &asic_last[0][0] + sizeof(asic_last) / sizeof(asic_last[0][0]), 0);
    adc.__clean();
    wave.__clean();
    scaler.__clean();
    flow.__clean();
}

EXT_DECL_DATA_SRC_FCN(void, EXT_AIDA::__unpack)
{
    uint32 wr_test = 0;
    __buffer.peek_uint32(&wr_test);
    if (wr_test != 0x700)
    {
        __buffer.reverse(20);
    }

    uint32 wrID = 0, wr1 = 0, wr2 = 0, wr3 = 0, wr4 = 0;
    __buffer.get_uint32(&wrID);
    __buffer.get_uint32(&wr1);
    __buffer.get_uint32(&wr2);
    __buffer.get_uint32(&wr3);
    __buffer.get_uint32(&wr4);

    // Timestamp extract
    uint64 cur_timestamp = 0;
    if (((wr1 & 0xffff0000) != 0x03e10000) || (wr2 & 0xffff0000) != 0x04e10000
        || (wr3 & 0xffff0000) != 0x05e10000 || (wr4 & 0xffff0000) != 0x06e10000)
    {
        ERROR("MBS White Rabbit Header not valid.");
    }
    cur_timestamp = (wr1 & 0xffff);
    cur_timestamp |= (wr2 & 0xffff) << 16;
    cur_timestamp |= (uint64)(wr3 & 0xffff) << 32;
    cur_timestamp |= (uint64)(wr4 & 0xffff) << 48;

    // Adjust ucesb shift!!
    cur_timestamp += AIDA_UCESB_SHIFT;

#if AIDA_UNPACK_STATS
    stats.Events++;
#endif

    // Loop through all AIDA data items
    while (!__buffer.empty())
    {

        uint32 data = 0;
        __buffer.get_uint32(&data);
        uint32 ts_lo = 0;
        __buffer.get_uint32(&ts_lo);

        // this is check /every/ single bit so verify the upper 4 bits of TS are 0
        if (ts_lo & 0xf0000000) // was (ts_lo & 0xf0000000)
        {
            ERROR("Upper 4-bits of AIDA timestamp not 0.");
        }

        cur_timestamp &= ~0x0fffffffULL;
        cur_timestamp |= (ts_lo & 0x0fffffff);

#if AIDA_UNPACK_STATS
        stats.DataItems++;
        if (stats.Start == 0) stats.Start = cur_timestamp;
        if (cur_timestamp >= stats.Stop)
        {
            stats.Stop = cur_timestamp;
        }
#endif

        // AIDA ADC Item to unpack
        // Calum
        //>Check: are the two most significant (left-most) bits of data "1"s
        //If they are its equivanent to "is type == 3" in BuildAIDAEvent"

        if ((data & 0xC0000000) == 0xC0000000)
        {
            auto& item = adc.append_item();
            item.timestamp_raw_lo = (cur_timestamp & 0xffffffff);
            item.timestamp_raw_hi = (uint32)((cur_timestamp >> 32) & 0xffffffff);
            item.vernier = (data & 0b00100000000000000000000000000000) != 0;
            item.range   = (data & 0b00010000000000000000000000000000) != 0;
            uint32 ident = (data & 0b00001111111111110000000000000000) >> 16;
            item.fee     = (uint8)(1 + ((ident >> 6) & 0b111111));

            if (item.fee > AIDA_MAX_FEES)
            {
                ERROR("ADC FEE64 %d greater than %d.", item.fee, AIDA_MAX_FEES);
            }
            if (item.fee < 1)
            {
                ERROR("ADC FEE64 %d less than %d.", item.fee, 1);
            }
            item.channel = (uint8)((ident) & 0b111111);
            if (item.channel > 63)
            {
                ERROR("ADC channel %d greater than %d.", item.channel, 63);
            }
            if (fast_times[item.fee - 1][item.channel] != 0)
            {
                uint64 fast_time = fast_times[item.fee - 1][item.channel];
                item.timestamp_fast_lo = (fast_time & 0xffffffff);
                item.timestamp_fast_hi = (uint32)((fast_time >> 32) & 0xffffffff);
                fast_times[item.fee - 1][item.channel] = 0;
            }
            else
            {
                item.timestamp_fast_lo = 0;
                item.timestamp_fast_hi = 0;
            }
            uint64 corr_timestamp = cur_timestamp;
#if AIDA_UNPACK_STATS
            stats.Type.ADC++;
            stats_fee[item.fee - 1].Type.ADC++;
            stats_fee[item.fee - 1].DataItems++;
            if (item.range)
            {
                stats.AdcType.Implant++;
                stats_fee[item.fee - 1].AdcType.Implant++;
            }
            else if (item.vernier)
            {
                stats.AdcType.Vernier++;
                stats_fee[item.fee - 1].AdcType.Vernier++;
            }
            else
            {
                stats.AdcType.Decay++;
                stats_fee[item.fee - 1].AdcType.Decay++;
            }
            if (last_adc_timestamp && cur_timestamp < last_adc_timestamp) {
                stats.TimeWarps++;
                ERROR("Timestamp %" PRIx64 " before %" PRIx64, cur_timestamp, last_adc_timestamp);
            }
            last_adc_timestamp = cur_timestamp;
#endif
            if (asic_last[item.fee - 1][item.channel / 16] != 0)
            {
                uint64 tsl = cur_timestamp - asic_last[item.fee - 1][item.channel / 16];
                // We are a multiplexed readout
                if (tsl == 2000)
                {
                    corr_timestamp -= 2000U * ++multiplexer[item.fee -1][item.channel / 16];
                    if (multiplexer[item.fee - 1][item.channel / 16] > 16)
                    {
                        WARNING("AIDA multiplexer tracking reported more channels multiplexed than possible. (FEE: %d, ASIC %d, Count %d)", item.fee, item.channel / 16, multiplexer[item.fee - 1][item.channel / 16]);
                    }
                }
                else
                {
                    multiplexer[item.fee - 1][item.channel / 16] = 0;
                }
            }
            asic_last[item.fee - 1][item.channel / 16] = cur_timestamp;
            item.timestamp_slow_lo = (corr_timestamp & 0xffffffff);
            item.timestamp_slow_hi = (uint32)((corr_timestamp >> 32) & 0xffffffff);
            item.data    = (data & 0b00000000000000001111111111111111);
        }
        // AIDA WAVE Item to unpack
        else if ((data & 0xC0000000) == 0x40000000)
        {
            ERROR("AIDA WAVE is not unpacked at the moment.");
        }
        // AIDA INFO Item to unpack
        //Calum
        //>Check same as above, but rather are 2 most significant bits of data "10"
        //>equivalent to "is type == 2?" hooray for binary!

        else if ((data & 0xC0000000) == 0x80000000)
        {
            // Internally unpack the INFO
            uint32 fee = 1 + ((data >> 24) & 0b111111);
            if (fee > AIDA_MAX_FEES)
            {
                ERROR("AIDA INFO FEE64 %d greater than %d", fee, AIDA_MAX_FEES);
            }
            uint32 info_code = (data >> 20) & 0xf;
            uint32 info_field = (data & 0xfffff);
#if AIDA_UNPACK_STATS
            stats.Type.Info++;
            stats_fee[fee - 1].Type.Info++;
            stats_fee[fee - 1].DataItems++;
#endif
            switch (info_code)
            {
                case 2: // PAUSE
                    {
                        // Update middle timestamp
                        uint64 ts_hi = (cur_timestamp >> 48) & 0xfffff;
                        uint64 ts_mi = info_field;
                        cur_timestamp = (ts_hi << 48) | (ts_mi << 28) | ts_lo;

                        auto& entry = flow.append_item();
                        entry.timestamp_lo = (cur_timestamp & 0xffffffff);
                        entry.timestamp_hi = (uint32)((cur_timestamp >> 32) & 0xffffffff);
                        entry.fee = (uint8)fee;
                        entry.paused = 1;
#if AIDA_UNPACK_STATS
                        stats.InfoType.Pause++;
                        stats_fee[fee - 1].InfoType.Pause++;
                        pause_time = cur_timestamp;
                        pause_time_fee[fee - 1] = cur_timestamp;
#endif
                    }
                    break;
                case 3: // RESUME
                    {
                        // Update middle timestamp
                        uint64 ts_hi = (cur_timestamp >> 48) & 0xfffff;
                        uint64 ts_mi = info_field;
                        cur_timestamp = (ts_hi << 48) | (ts_mi << 28) | ts_lo;

                        auto& entry = flow.append_item();
                        entry.timestamp_lo = (cur_timestamp & 0xffffffff);
                        entry.timestamp_hi = (uint32)((cur_timestamp >> 32) & 0xffffffff);
                        entry.fee = (uint8)fee;
                        entry.paused = 0;
#if AIDA_UNPACK_STATS
                        stats.InfoType.Resume++;
                        stats_fee[fee - 1].InfoType.Resume++;
                        if (pause_time)
                            stats.DeadTime += (cur_timestamp - pause_time);
                        pause_time = 0;
                        if (pause_time_fee[fee - 1])
                            stats_fee[fee -1].DeadTime += (cur_timestamp - pause_time_fee[fee -1]);
                        pause_time_fee[fee - 1] = 0;
#endif
                    }
                    break;
                case 4: // WR4728
                    {
                        // Update middle timestamp
                        uint64 ts_hi = (cur_timestamp >> 48) & 0xfffff;
                        uint64 ts_mi = info_field;
                        cur_timestamp = (ts_hi << 48) | (ts_mi << 28) | ts_lo;
#if AIDA_UNPACK_STATS
                        stats.InfoType.Sync48++;
                        stats_fee[fee - 1].InfoType.Sync48++;
#endif
                    }
                    break;
                case 5: // WR6348
                    {
                        // Update upper timestamp
                        uint64 ts_hi = info_field;
                        uint64 ts_mi = (cur_timestamp >> 28) & 0xfffff;
                        cur_timestamp = (ts_hi << 48) | (ts_mi << 28) | ts_lo;
#if AIDA_UNPACK_STATS
                        stats.InfoType.Sync63++;
                        stats_fee[fee - 1].InfoType.Sync63++;
#endif
                    }
                    break;
                case 6: // DISCRIMINATOR (19-16 = adc, 15-0 = flags)
                    {
                        uint8 adc = (uint8)(info_field >> 16);
                        uint16 hitpattern = (uint16)(info_field & 0xffff);
                        for (int i = 0; i < 16; i++)
                        {
                            if (hitpattern & (1 << i))
                            {
                                fast_times[fee - 1][adc * 16 + i] = cur_timestamp;
                            }
                        }
#if AIDA_UNPACK_STATS
                        stats.InfoType.Discriminator++;
                        stats_fee[fee - 1].InfoType.Discriminator++;
#endif
                    }
                    break;
                case 8: // SCALER (19-16 = index, 0-15 = data.
                    {
                        uint8 index = (uint8)(info_field >> 16);
                        uint64 counter = (uint16)(info_field & 0xffff);
                        int shift = index * 16;
                        uint64 mask = (0xffffULL << shift);
                        scalers[fee - 1] &= ~mask;
                        scalers[fee - 1] |= (counter << shift);

                        if (index == 2)
                        {
                            auto& entry = scaler.append_item();
                            entry.timestamp_lo = cur_timestamp & 0xffffffff;
                            entry.timestamp_hi = (uint32)(cur_timestamp >> 32);
                            entry.value_lo = (scalers[fee - 1] & 0xffffffff);
                            entry.value_hi = (uint32)(scalers[fee - 1] >> 32);
                            entry.fee = (uint8)fee;
                        }
#if AIDA_UNPACK_STATS
                        stats.InfoType.Scaler++;
                        stats_fee[fee - 1].InfoType.Scaler++;
#endif
                    }
                    break;
                default:
                    ERROR("AIDA INFO Code %d (with field %05x) is unknown.", info_code, info_field);
                    break;
            }
        }
        else
        {
            ERROR("AIDA Data Item %08x:%08x invalid.", data, ts_lo);
        }
    }
}

EXT_FORCE_IMPL_DATA_SRC_FCN(void, EXT_AIDA::__unpack);

void EXT_AIDA::dump(const signal_id &id,pretty_dump_info &pdi) const
{
    adc.dump(signal_id(id, "adc"), pdi);
    // TODO: need to use fixed array(?) or somethig else... stupid
    //wave.dump(signal_id(id, "wave"), pdi);
    scaler.dump(signal_id(id, "scaler"), pdi);
    flow.dump(signal_id(id, "flow"), pdi);
}

void EXT_AIDA::show_members(const signal_id& id, const char* unit) const
{
    adc.show_members(signal_id(id, "adc"), unit);
    //wave.show_members(signal_id(id, "wave"), unit);
    scaler.show_members(signal_id(id, "scaler"), unit);
    flow.show_members(signal_id(id, "flow"), unit);
}

void EXT_AIDA::enumerate_members(const signal_id &__id, const enumerate_info &__info, enumerate_fcn __callback, void *__extra) const
{
    {
        const signal_id &__shadow_id = __id;
        signal_id __id(__shadow_id, "adc");
        {
            adc.enumerate_members(__id, __info, __callback, __extra);
        }
    }
    //wave.enumerate_members(signal_id(__id, "wave"), __info, __callback, __extra);
    scaler.enumerate_members(signal_id(__id, "scaler"), __info, __callback, __extra);
    flow.enumerate_members(signal_id(__id, "flow"), __info, __callback, __extra);
}

void EXT_AIDA::zero_suppress_info_ptrs(used_zero_suppress_info& used_info)
{
    adc.zero_suppress_info_ptrs(used_info);
    //wave.zero_suppress_info_ptrs(used_info);
    scaler.zero_suppress_info_ptrs(used_info);
    flow.zero_suppress_info_ptrs(used_info);
}

#ifdef NO_UINT64
#define dump32(name) ::dump_uint32(name, signal_id(id, #name), pdi);
#define dump64(name) dump32(name ## _lo); dump32(name ## _hi);
#else
#define dump64(name) ::dump_uint64(name, signal_id(id, #name), pdi);
#endif

void aida_adc_item::dump(const signal_id &id, pretty_dump_info &pdi) const
{
    dump64(timestamp_raw);
    dump64(timestamp_slow);
    dump64(timestamp_fast);
    ::dump_uint16(data, signal_id(id, "data"), pdi);
    ::dump_uint8(fee, signal_id(id, "fee"), pdi);
    ::dump_uint8(channel, signal_id(id, "channel"), pdi);
    ::dump_uint8(vernier, signal_id(id, "vernier"), pdi);
    ::dump_uint8(range, signal_id(id, "range"), pdi);
}

void aida_wave_item::dump(const signal_id& id, pretty_dump_info& pdi) const
{
    dump64(timestamp);
    ::dump_uint16(length, signal_id(id, "length"), pdi);
    ::dump_uint8(fee, signal_id(id, "fee"), pdi);
    ::dump_uint8(channel, signal_id(id, "channel"), pdi);
    data.dump(signal_id(id, "data"), pdi);
}

void aida_scaler_item::dump(const signal_id& id, pretty_dump_info& pdi) const
{
    dump64(timestamp);
    dump64(value);
    ::dump_uint8(fee, signal_id(id, "fee"), pdi);
}

void aida_flow_item::dump(const signal_id& id, pretty_dump_info& pdi) const
{
    dump64(timestamp);
    ::dump_uint8(fee, signal_id(id, "fee"), pdi);
    ::dump_uint8(paused, signal_id(id, "paused"), pdi);
}

#ifdef NO_UINT64
#define show32(name) ::show_members<uint32>(signal_id(id, #name), unit);
#define show64(name) show32(name ## _lo); show32(name ## _hi);
#else
#define show64(name) ::show_members<uint64>(signal_id(id, #name), unit);
#endif

void aida_adc_item::show_members(const signal_id& id, const char* unit) const
{
    show64(timestamp_raw);
    show64(timestamp_slow);
    show64(timestamp_fast);
    ::show_members<uint16>(signal_id(id, "data"), unit);
    ::show_members<uint8>(signal_id(id, "fee"), unit);
    ::show_members<uint8>(signal_id(id, "channel"), unit);
    ::show_members<uint8>(signal_id(id, "vernier"), unit);
    ::show_members<uint8>(signal_id(id, "range"), unit);
}

void aida_wave_item::show_members(const signal_id& id, const char* unit) const
{
    show64(timestamp);
    ::show_members<uint16>(signal_id(id, "length"), unit);
    ::show_members<uint8>(signal_id(id, "fee"), unit);
    ::show_members<uint8>(signal_id(id, "channel"), unit);
    data.show_members(signal_id(id, "data"), unit);
}

void aida_scaler_item::show_members(const signal_id& id, const char* unit) const
{
    show64(timestamp);
    show64(value);
    ::show_members<uint8>(signal_id(id, "fee"), unit);
}

void aida_flow_item::show_members(const signal_id& id, const char* unit) const
{
    show64(timestamp);
    ::show_members<uint8>(signal_id(id, "fee"), unit);
    ::show_members<uint8>(signal_id(id, "paused"), unit);
}

#ifdef NO_UINT64
#define callback32(name) callback(signal_id(id, #name), enumerate_info(info, & name, ENUM_TYPE_UINT), extra);
#define callback64(name)  callback32(name ## _lo); callback32(name ## _hi);
#else
#define callback64(name) callback(signal_id(id, #name), enumerate_info(info, & name, ENUM_TYPE_UINT64), extra);
#endif

void aida_adc_item::enumerate_members(const signal_id &id, const enumerate_info &info, enumerate_fcn callback, void *extra) const
{
    callback64(timestamp_raw);
    callback64(timestamp_slow);
    callback64(timestamp_fast);
    callback(signal_id(id, "data"), enumerate_info(info, &data, ENUM_TYPE_USHORT), extra);
    callback(signal_id(id, "fee"), enumerate_info(info, &fee, ENUM_TYPE_UCHAR), extra);
    callback(signal_id(id, "channel"), enumerate_info(info, &channel, ENUM_TYPE_UCHAR), extra);
    callback(signal_id(id, "vernier"), enumerate_info(info, &vernier, ENUM_TYPE_UCHAR), extra);
    callback(signal_id(id, "range"), enumerate_info(info, &range, ENUM_TYPE_UCHAR), extra);
}

void aida_wave_item::enumerate_members(const signal_id &id, const enumerate_info &info, enumerate_fcn callback, void *extra) const
{
    callback64(timestamp);
    callback(signal_id(id, "length"), enumerate_info(info, &length, ENUM_TYPE_USHORT), extra);
    callback(signal_id(id, "fee"), enumerate_info(info, &fee, ENUM_TYPE_UCHAR), extra);
    callback(signal_id(id, "channel"), enumerate_info(info, &channel, ENUM_TYPE_UCHAR), extra);
    data.enumerate_members(signal_id(id, "data"), info, callback, extra);
}

void aida_scaler_item::enumerate_members(const signal_id &id, const enumerate_info &info, enumerate_fcn callback, void *extra) const
{
    callback64(timestamp);
    callback64(value);
    callback(signal_id(id, "fee"), enumerate_info(info, &fee, ENUM_TYPE_UCHAR), extra);
}

void aida_flow_item::enumerate_members(const signal_id &id, const enumerate_info &info, enumerate_fcn callback, void *extra) const
{
    callback64(timestamp);
    callback(signal_id(id, "fee"), enumerate_info(info, &fee, ENUM_TYPE_UCHAR), extra);
    callback(signal_id(id, "paused"), enumerate_info(info, &paused, ENUM_TYPE_UCHAR), extra);
}

#ifdef NO_UINT64
#define suppress32(name) ::zero_suppress_info_ptrs(& name, used_info);
#define suppress64(name) suppress32(name ## _lo); suppress32(name ## _hi);
#else
#define suppress64(name) ::zero_suppress_info_ptrs(& name, used_info);
#endif

void aida_adc_item::zero_suppress_info_ptrs(used_zero_suppress_info& used_info)
{
    suppress64(timestamp_raw);
    suppress64(timestamp_slow);
    suppress64(timestamp_fast);
    ::zero_suppress_info_ptrs(&data, used_info);
    ::zero_suppress_info_ptrs(&fee, used_info);
    ::zero_suppress_info_ptrs(&channel, used_info);
    ::zero_suppress_info_ptrs(&vernier, used_info);
    ::zero_suppress_info_ptrs(&range, used_info);
}

void aida_wave_item::zero_suppress_info_ptrs(used_zero_suppress_info& used_info)
{
    suppress64(timestamp);
    ::zero_suppress_info_ptrs(&length, used_info);
    ::zero_suppress_info_ptrs(&fee, used_info);
    ::zero_suppress_info_ptrs(&channel, used_info);
    data.zero_suppress_info_ptrs(used_info);
}

void aida_scaler_item::zero_suppress_info_ptrs(used_zero_suppress_info& used_info)
{
    suppress64(timestamp);
    suppress64(value);
    ::zero_suppress_info_ptrs(&fee, used_info);
}

void aida_flow_item::zero_suppress_info_ptrs(used_zero_suppress_info& used_info)
{
    suppress64(timestamp);
    ::zero_suppress_info_ptrs(&fee, used_info);
    ::zero_suppress_info_ptrs(&paused, used_info);
}
