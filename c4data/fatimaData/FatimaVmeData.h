#ifndef FatimaVmeData_H
#define FatimaVmeData_H

#include "TObject.h"
#include "../../config/setup.h"
#include <vector>

class FatimaVmeData : public TObject
{
    public:
        FatimaVmeData();

        FatimaVmeData(uint64_t wr_t,
                    std::vector<uint32_t> qdc_detectors,
                    std::vector<uint32_t> QDC_time_coarse,
                    std::vector<uint64_t> QDC_time_fine,
                    std::vector<uint32_t> QLong_raw,
                    std::vector<uint32_t> QShort_raw,
                    int qdcs_fired,
                    std::vector<uint32_t> tdc_detectors,
                    std::vector<uint32_t> v1290_data,
                    std::vector<uint32_t> v1290_lot,
                    int tdcs_fired);

        virtual ~FatimaVmeData() {}

        // Getters
        inline uint64_t Get_wr_t() const { return fwr_t; }
        inline uint16_t Get_wr_subsystem_id() const { return fwr_subsystem_id; }

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
        inline void Set_wr_subsystem_id(uint16_t id) { fwr_subsystem_id = id; }
        inline void Set_QDCs_fired(int n) { fqdcs_fired = n; }
        inline void Set_TDCs_fired(int n) { ftdcs_fired = n; }
        inline void Set_QDC_coarse_time(std::vector<uint32_t> coarse_times) { fqdc_coarse_times = coarse_times; }
        inline void Set_QDC_fine_time(std::vector<uint64_t> fine_times) { fqdc_fine_times = fine_times; }
        inline void Set_QLong_raw(std::vector<uint32_t> qlongs) { fqdc_qlong_raw = qlongs; }
        inline void Set_QShort_raw(std::vector<uint32_t> qshorts) { fqdc_qshort_raw = qshorts; }
        inline void Set_QDC_detectors(std::vector<uint32_t> qdcs) { fqdc_detectors = qdcs; }
        inline void Set_TDC_detectors(std::vector<uint32_t> tdcs) { ftdc_detectors = tdcs; }

        inline void Set_v1290_data(std::vector<uint32_t> data) { fv1290_data = data; }
        inline void Set_v1290_lot(std::vector<uint32_t> lot) { fv1290_lot = lot; }

    protected:

        uint64_t fwr_t;
        uint16_t fwr_subsystem_id;
        std::vector<uint32_t> fqdc_coarse_times = {};
        std::vector<uint64_t> fqdc_fine_times = {};
        std::vector<uint32_t> fqdc_qlong_raw = {};
        std::vector<uint32_t> fqdc_qshort_raw = {};

        std::vector<uint32_t> fv1290_channels = {};
        std::vector<uint32_t> fv1290_data = {};
        std::vector<uint32_t> fv1290_lot = {};

        int ftdcs_fired;
        int fqdcs_fired;
        std::vector<uint32_t> ftdc_detectors = {};
        std::vector<uint32_t> fqdc_detectors = {};

    public:
        ClassDef(FatimaVmeData, 1)
};


class FatimaVmeQDCItem : public TObject
{
    public:
        FatimaVmeQDCItem();

        void Reset();
        void SetAll(uint64_t wr, int det, uint32_t ct, uint64_t ft, uint32_t qlr, uint32_t qsr);
        uint64_t Get_wr_t() const;
        uint32_t Get_coarse_time() const;
        uint64_t Get_fine_time() const;
        uint32_t Get_qlong_raw() const;
        uint32_t Get_qshort_raw() const;
        int Get_detector() const;

        ClassDefNV(FatimaVmeQDCItem, 2)
    
    private:

        uint64_t wr_t;
        uint32_t coarse_time;
        uint64_t fine_time;
        uint32_t qlong_raw;
        uint32_t qshort_raw;
        int detector;

};


class FatimaVmeTDCItem : public TObject
{
    public:
        FatimaVmeTDCItem();

        void Reset();
        void SetAll(uint64_t wr, uint32_t wr_id, int det, uint32_t data, uint8_t lot);

        uint64_t Get_wr_t() const;
        uint32_t Get_wr_subsystem_id() const;
        uint32_t Get_v1290_tdc_data() const;
        uint8_t Get_leadOrTrail() const;
        int Get_detector() const;

        ClassDefNV(FatimaVmeTDCItem, 2)
    
    private:
        uint64_t wr_t;
        uint32_t wr_subsystem_id;
        uint32_t v1290_tdc_data;
        uint8_t leadOrTrail; // 32 or 8?
        int detector;

};

inline uint64_t FatimaVmeQDCItem::Get_wr_t() const
{
    return wr_t;
}

inline int FatimaVmeQDCItem::Get_detector() const
{
    return detector;
}

inline uint32_t FatimaVmeQDCItem::Get_coarse_time() const
{
    return coarse_time;
}

inline uint64_t FatimaVmeQDCItem::Get_fine_time() const
{
    return fine_time;
}

inline uint32_t FatimaVmeQDCItem::Get_qlong_raw() const
{
    return qlong_raw;
}

inline uint32_t FatimaVmeQDCItem::Get_qshort_raw() const
{
    return qshort_raw;
}

inline uint64_t FatimaVmeTDCItem::Get_wr_t() const
{
    return wr_t;
}

inline uint32_t FatimaVmeTDCItem::Get_wr_subsystem_id() const
{
    return wr_subsystem_id;
}

inline uint32_t FatimaVmeTDCItem::Get_v1290_tdc_data() const
{
    return v1290_tdc_data;
}

inline uint8_t FatimaVmeTDCItem::Get_leadOrTrail() const
{
    return leadOrTrail;
}

inline int FatimaVmeTDCItem::Get_detector() const
{
    return detector;
}

#endif