#ifndef FatimaVmeData_H
#define FatimaVmeData_H

#include "TObject.h"
#include <vector>

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