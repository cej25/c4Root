#include "FatimaVmeData.h"

FatimaVmeData::FatimaVmeData()
    :   fwr_t(0)
    ,   fqdcs_fired(0)
    ,   ftdcs_fired(0)
{
    
}

FatimaVmeData::FatimaVmeData(uint64_t wr_t,
                            std::vector<uint32_t> qdc_detectors,
                            std::vector<uint32_t> QDC_time_coarse,
                            std::vector<uint64_t> QDC_time_fine,
                            std::vector<uint32_t> QLong_raw,
                            std::vector<uint32_t> QShort_raw,
                            int qdcs_fired,
                            std::vector<uint32_t> tdc_detectors,
                            std::vector<uint32_t> v1290_data,
                            std::vector<uint32_t> v1290_lot,
                            int tdcs_fired)
    :   fwr_t(wr_t)
    ,   fqdcs_fired(qdcs_fired)
    ,   ftdcs_fired(tdcs_fired)
{
    fqdc_detectors = qdc_detectors;
    fqdc_coarse_times = QDC_time_coarse;
    fqdc_fine_times = QDC_time_fine;
    fqdc_qlong_raw = QLong_raw;
    fqdc_qshort_raw = QShort_raw;
    fqdcs_fired = qdcs_fired;
    ftdc_detectors = tdc_detectors;
    fv1290_data = v1290_data;
    fv1290_lot = v1290_lot;
    ftdcs_fired = tdcs_fired;
}

FatimaVmeQDCItem::FatimaVmeQDCItem()
{

}

void FatimaVmeQDCItem::SetAll(uint64_t wr, int det, uint32_t ct, uint64_t ft, uint32_t qlr, uint32_t qsr)
{
    wr_t = wr;
    coarse_time = ct;
    fine_time = ft;
    qlong_raw = qlr;
    qshort_raw = qsr;
    detector = det;
}

void FatimaVmeQDCItem::Reset()
{
    wr_t = 0;
    coarse_time = 0;
    fine_time = 0;
    qlong_raw = 0;
    qshort_raw = 0;
    detector = 0;
}

FatimaVmeTDCItem::FatimaVmeTDCItem()
{

}

void FatimaVmeTDCItem::SetAll(uint64_t wr, uint32_t wr_id, int det, uint32_t data, uint8_t lot)
{
    wr_t = wr;
    wr_subsystem_id = wr_id;
    v1290_tdc_data = data;
    leadOrTrail = lot; // 32 or 8?
    detector = det;
}

void FatimaVmeTDCItem::Reset()
{
    wr_t = 0;
    v1290_tdc_data = 0;
    leadOrTrail = 0; // 32 or 8?
    detector = 0;
}


ClassImp(FatimaVmeData)