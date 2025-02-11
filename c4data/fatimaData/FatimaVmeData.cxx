#include "FatimaVmeData.h"


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

ClassImp(FatimaVmeQDCItem)

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

ClassImp(FatimaVmeTDCItem)