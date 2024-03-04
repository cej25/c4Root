#ifndef FatimaVmeData_H
#define FatimaVmeData_H

#include "TObject.h"

#define QDC_BOARDS 5
#define CHANNELS_PER_QDC 8

class FatimaVmeData : public TObject
{
    public:
        FatimaVmeData();

        FatimaVmeData(uint64_t wr_t);

        virtual ~FatimaVmeData() {}

        // Getters
        inline uint64_t Get_wr_t() const { return fwr_t; }

        // Setters
        inline void Set_wr_t(uint64_t wr_t) { fwr_t = wr_t; }
        inline void Set_board_id(int qdc, Int_t board_id) { fboard_id[qdc] = board_id; }
        inline void Set_board_time(int qdc, uint32_t time) { fboard_time[qdc] = time; }
        inline void Set_num_channels_fired(int qdc, Int_t n) { fnum_channels_fired[qdc] = n; }
        inline void Set_channel_time_coarse(int qdc, int channel, uint64_t coarse) { fqdc_channel_coarse_time[qdc][channel] = coarse; }
        inline void Set_channel_time_fine(int qdc, int channel, uint32_t fine) { fqdc_channel_fine_time[qdc][channel] = fine; }
        inline void Set_channel_time(int qdc, int channel, int time) { fqdc_channel_time[qdc][channel] = time; }
        inline void Set_channel_QLong(int qdc, int channel, int qlong) { fqdc_channel_qlong[qdc][channel] = qlong; }
        inline void Set_channel_QShort(int qdc, int channel, int qshort) { fqdc_channel_qshort[qdc][channel] = qshort; }

        inline void Set_v1290_channel(int tdc, std::vector<uint32_t> channels) { fv1290_channels = channels; }
        inline void Set_v1290_data(int tdc, std::vector<uint32_t> data) { fv1290_data = data; }
        inline void Set_v1290_lot(int tdc, std::vector<uint32_t> lot) { fv1290_lot = lot; }

    protected:

        // stuff

        // board number != geo/board_id
        uint64_t fwr_t;
        Int_t fboard_id[QDC_BOARDS];
        uint32_t fboard_time[QDC_BOARDS];
        Int_t fnum_channels_fired[QDC_BOARDS];
        uint64_t fqdc_channel_coarse_time[QDC_BOARDS][CHANNELS_PER_QDC];
        uint32_t fqdc_channel_fine_time[QDC_BOARDS][CHANNELS_PER_QDC];
        uint64_t fqdc_channel_time[QDC_BOARDS][CHANNELS_PER_QDC];
        uint32_t fqdc_channel_qlong[QDC_BOARDS][CHANNELS_PER_QDC];
        uint32_t fqdc_channel_qshort[QDC_BOARDS][CHANNELS_PER_QDC];

        std::vector<uint32_t> fv1290_channels;
        std::vector<uint32_t> fv1290_data;
        std::vector<uint32_t> fv1290_lot;

    public:
        ClassDef(FatimaVmeData, 1)
};

#endif