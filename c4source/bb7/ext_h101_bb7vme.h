#ifndef C4_EXT_H101_BB7VME_H
#define C4_EXT_H101_BB7VME_H

#include <stdint.h>

// BB7's client layout for S181 UNPACK. The UCESB client matches the field
// names below to the unpacker's stream and writes to the registered offsets.
typedef struct EXT_STR_h101_bb7vme_onion_t
{
    uint32_t bbseven_ts_subsystem_id;
    uint32_t bbseven_ts_t[4];

    struct
    {
        uint32_t geo;
        uint32_t n;
        uint32_t nI[32];
        uint32_t data[32];
    } bbseven_v7x5[4];

    struct
    {
        uint32_t geo;
        uint32_t measurement_nM;
        uint32_t measurement_nMI[128];
        uint32_t measurement_nME[128];
        uint32_t measurement_n;
        uint32_t measurement_data[16384];
        uint32_t measurement_leadOrTrailM;
        uint32_t measurement_leadOrTrailMI[128];
        uint32_t measurement_leadOrTrailME[128];
        uint32_t measurement_leadOrTrail;
        uint32_t measurement_leadOrTrailv[16384];
    } bbseven_v1290;
} EXT_STR_h101_bb7vme_onion;

typedef EXT_STR_h101_bb7vme_onion EXT_STR_h101_bb7vme;

#define BB7_V775_ITEMS_INFO(ok, si, offset, type, printerr, slot, prefix) do { \
    EXT_STR_ITEM_INFO_LIM(ok, si, offset, type, printerr, bbseven_v7x5[slot].geo, UINT32, prefix "_geo", 255); \
    EXT_STR_ITEM_INFO_LIM(ok, si, offset, type, printerr, bbseven_v7x5[slot].n, UINT32, prefix "n", 32); \
    EXT_STR_ITEM_INFO_ZZP(ok, si, offset, type, printerr, bbseven_v7x5[slot].nI, UINT32, prefix "nI", prefix "n"); \
    EXT_STR_ITEM_INFO_ZZP(ok, si, offset, type, printerr, bbseven_v7x5[slot].data, UINT32, prefix "data", prefix "n"); \
} while (0)

#define EXT_STR_h101_bb7vme_ITEMS_INFO(ok, si, offset, type, printerr) do { \
    ok = 1; \
    EXT_STR_ITEM_INFO_LIM(ok, si, offset, type, printerr, bbseven_ts_subsystem_id, UINT32, "bbseven_ts_subsystem_id", 65535); \
    EXT_STR_ITEM_INFO_LIM(ok, si, offset, type, printerr, bbseven_ts_t[0], UINT32, "bbseven_ts_t1", 65535); \
    EXT_STR_ITEM_INFO_LIM(ok, si, offset, type, printerr, bbseven_ts_t[1], UINT32, "bbseven_ts_t2", 65535); \
    EXT_STR_ITEM_INFO_LIM(ok, si, offset, type, printerr, bbseven_ts_t[2], UINT32, "bbseven_ts_t3", 65535); \
    EXT_STR_ITEM_INFO_LIM(ok, si, offset, type, printerr, bbseven_ts_t[3], UINT32, "bbseven_ts_t4", 65535); \
    BB7_V775_ITEMS_INFO(ok, si, offset, type, printerr, 0, "bbseven_v7x51"); \
    BB7_V775_ITEMS_INFO(ok, si, offset, type, printerr, 1, "bbseven_v7x52"); \
    BB7_V775_ITEMS_INFO(ok, si, offset, type, printerr, 2, "bbseven_v7x53"); \
    BB7_V775_ITEMS_INFO(ok, si, offset, type, printerr, 3, "bbseven_v7x54"); \
    EXT_STR_ITEM_INFO_LIM(ok, si, offset, type, printerr, bbseven_v1290.geo, UINT32, "bbseven_v1290_geo", 255); \
    EXT_STR_ITEM_INFO_LIM(ok, si, offset, type, printerr, bbseven_v1290.measurement_nM, UINT32, "bbseven_v1290_measurement_nM", 128); \
    EXT_STR_ITEM_INFO_ZZP(ok, si, offset, type, printerr, bbseven_v1290.measurement_nMI, UINT32, "bbseven_v1290_measurement_nMI", "bbseven_v1290_measurement_nM"); \
    EXT_STR_ITEM_INFO_ZZP(ok, si, offset, type, printerr, bbseven_v1290.measurement_nME, UINT32, "bbseven_v1290_measurement_nME", "bbseven_v1290_measurement_nM"); \
    EXT_STR_ITEM_INFO_LIM(ok, si, offset, type, printerr, bbseven_v1290.measurement_n, UINT32, "bbseven_v1290_measurement_n", 16384); \
    EXT_STR_ITEM_INFO_ZZP(ok, si, offset, type, printerr, bbseven_v1290.measurement_data, UINT32, "bbseven_v1290_measurement_data", "bbseven_v1290_measurement_n"); \
    EXT_STR_ITEM_INFO_LIM(ok, si, offset, type, printerr, bbseven_v1290.measurement_leadOrTrailM, UINT32, "bbseven_v1290_measurement_leadOrTrailM", 128); \
    EXT_STR_ITEM_INFO_ZZP(ok, si, offset, type, printerr, bbseven_v1290.measurement_leadOrTrailMI, UINT32, "bbseven_v1290_measurement_leadOrTrailMI", "bbseven_v1290_measurement_leadOrTrailM"); \
    EXT_STR_ITEM_INFO_ZZP(ok, si, offset, type, printerr, bbseven_v1290.measurement_leadOrTrailME, UINT32, "bbseven_v1290_measurement_leadOrTrailME", "bbseven_v1290_measurement_leadOrTrailM"); \
    EXT_STR_ITEM_INFO_LIM(ok, si, offset, type, printerr, bbseven_v1290.measurement_leadOrTrail, UINT32, "bbseven_v1290_measurement_leadOrTrail", 16384); \
    EXT_STR_ITEM_INFO_ZZP(ok, si, offset, type, printerr, bbseven_v1290.measurement_leadOrTrailv, UINT32, "bbseven_v1290_measurement_leadOrTrailv", "bbseven_v1290_measurement_leadOrTrail"); \
} while (0)

#endif
