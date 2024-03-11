#ifndef FatimaVmeData_H
#define FatimaVmeData_H

#include "TObject.h"
#include "../../config/setup.h"
#include <vector>

class FatimaVmeData : public TObject
{
    public:
        FatimaVmeData();

        FatimaVmeData(uint64_t wr_t);

        virtual ~FatimaVmeData() {}

        // Getters
        inline uint64_t Get_wr_t() const { return fwr_t; }

        inline int Get_TDCs_fired() const { return ftdcs_fired; }
        inline std::vector<uint32_t> Get_TDC_detectors() const { return ftdc_detectors; }
        inline std::vector<uint32_t> Get_v1290_data() const { return fv1290_data; }
        inline std::vector<uint32_t> Get_v1290_lot() const { return fv1290_lot; }

        inline int Get_QDCs_fired() const { return fqdcs_fired; }
        inline std::vector<uint32_t> Get_QDC_detectors() const { return fqdc_detectors; }
        inline std::vector<uint32_t> Get_QDC_coarse_time() const { return fqdc_coarse_times; }
        inline std::vector<uint64_t> Get_QDC_fine_time() const { return fqdc_fine_times; }
        inline std::vector<uint32_t> Get_QLong_raw() const { return fqdc_qlong_raw; }
        inline std::vector<uint32_t> Get_QShort_raw() const { return fqdc_qshort_raw; }

        // Setters
        inline void Set_wr_t(uint64_t wr_t) { fwr_t = wr_t; }
        inline void Set_board_id(int qdc, Int_t board_id) { fboard_id[qdc] = board_id; }
        inline void Set_board_time(int qdc, uint32_t time) { fboard_time[qdc] = time; }
        //inline void Set_num_channels_fired(int qdc, Int_t n) { fnum_channels_fired[qdc] = n; }
        inline void Set_QDCs_fired(int n) { fqdcs_fired = n; }
        inline void Set_TDCs_fired(int n) { ftdcs_fired = n; }
        inline void Set_QDC_coarse_time(std::vector<uint32_t> coarse_times) { fqdc_coarse_times = coarse_times; }
        // inline void Set_channel_time_coarse(int qdc, int channel, uint64_t coarse) { fqdc_channel_coarse_time[qdc][channel] = coarse; }
        inline void Set_QDC_fine_time(std::vector<uint64_t> fine_times) { fqdc_fine_times = fine_times; }
        //inline void Set_channel_time_fine(int qdc, int channel, uint32_t fine) { fqdc_channel_fine_time[qdc][channel] = fine; }
        //inline void Set_channel_time(int qdc, int channel, int time) { fqdc_channel_time[qdc][channel] = time; }
        //inline void Set_channel_QLong(int qdc, int channel, int qlong) { fqdc_channel_qlong[qdc][channel] = qlong; }
        inline void Set_QLong_raw(std::vector<uint32_t> qlongs) { fqdc_qlong_raw = qlongs; }
        //inline void Set_channel_QShort(int qdc, int channel, int qshort) { fqdc_channel_qshort[qdc][channel] = qshort; }
        inline void Set_QShort_raw(std::vector<uint32_t> qshorts) { fqdc_qshort_raw = qshorts; }
        inline void Set_QDC_detectors(std::vector<uint32_t> qdcs) { fqdc_detectors = qdcs; }
        inline void Set_TDC_detectors(std::vector<uint32_t> tdcs) { ftdc_detectors = tdcs; }

        //inline void Set_v1290_channel(std::vector<uint32_t> channels) { fv1290_channels = channels; }
        inline void Set_v1290_data(std::vector<uint32_t> data) { fv1290_data = data; }
        inline void Set_v1290_lot(std::vector<uint32_t> lot) { fv1290_lot = lot; }

    protected:

        // stuff

        // board number != geo/board_id
        // do we need to define number of qdc boards etc? :confused:
        uint64_t fwr_t;
        Int_t fboard_id[QDC_BOARDS];
        uint32_t fboard_time[QDC_BOARDS];
        Int_t fnum_channels_fired[QDC_BOARDS];
        //uint64_t fqdc_channel_coarse_time[QDC_BOARDS][CHANNELS_PER_QDC];
        std::vector<uint32_t> fqdc_coarse_times;
        //uint32_t fqdc_channel_fine_time[QDC_BOARDS][CHANNELS_PER_QDC];
        std::vector<uint64_t> fqdc_fine_times;
        uint64_t fqdc_channel_time[QDC_BOARDS][CHANNELS_PER_QDC];
        //uint32_t fqdc_channel_qlong[QDC_BOARDS][CHANNELS_PER_QDC];
        std::vector<uint32_t> fqdc_qlong_raw;
        //uint32_t fqdc_channel_qshort[QDC_BOARDS][CHANNELS_PER_QDC];
        std::vector<uint32_t> fqdc_qshort_raw;

        std::vector<uint32_t> fv1290_channels;
        std::vector<uint32_t> fv1290_data;
        std::vector<uint32_t> fv1290_lot;

        int ftdcs_fired;
        int fqdcs_fired;
        std::vector<uint32_t> ftdc_detectors;
        std::vector<uint32_t> fqdc_detectors;

    public:
        ClassDef(FatimaVmeData, 1)
};

#endif