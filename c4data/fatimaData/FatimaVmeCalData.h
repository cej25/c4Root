#ifndef FatimaVmeCalData_H
#define FatimaVmeCalData_H

#include "TObject.h"
#include "../../config/setup.h"
#include <vector>

class FatimaVmeCalData : public TObject
{
    public:
        FatimaVmeCalData();

        virtual ~FatimaVmeCalData() {}

        // Getters
        inline std::vector<uint32_t> Get_Singles_E() { return fsingles_e; }
        inline std::vector<uint32_t> Get_Singles_E_raw() { return fsingles_e_raw; }
        inline std::vector<uint32_t> Get_Singles_QDC_ID() { return fsingles_qdc_id; }
        inline std::vector<uint32_t> Get_Singles_coarse_time() { return fsingles_coarse_time; }
        inline std::vector<uint64_t> Get_Singles_fine_time() { return fsingles_fine_time; }

        inline std::vector<uint32_t> Get_Singles_TDC_timestamp() { return fsingles_tdc_timestamp; }
        inline std::vector<uint32_t> Get_Singles_TDC_timestamp_raw() { return fsingles_tdc_timestamp_raw; }
        inline std::vector<uint32_t> Get_Singles_TDC_ID() { return fsingles_tdc_id; }

        inline std::vector<uint32_t> Get_SC41L_hits() { return fsc41l_hits; }
        inline std::vector<uint32_t> Get_SC41R_hits() { return fsc41r_hits; }
        inline std::vector<uint32_t> Get_TM_undelayed_hits() { return ftm_undelayed_hits; }
        inline std::vector<uint32_t> Get_TM_delayed_hits() { return ftm_delayed_hits; }
        

        // Setters
        inline void Set_Singles_E(std::vector<uint32_t> e) { fsingles_e = e; }
        inline void Set_Singles_E_raw(std::vector<uint32_t> e) { fsingles_e_raw = e; }
        inline void Set_Singles_QDC_ID(std::vector<uint32_t> qdc) { fsingles_qdc_id = qdc; }
        inline void Set_Singles_coarse_time(std::vector<uint32_t> coarse_time) { fsingles_coarse_time = coarse_time; }
        inline void Set_Singles_fine_time(std::vector<uint64_t> fine_time) { fsingles_fine_time = fine_time; }

        inline void Set_Singles_TDC_timestamp(std::vector<uint32_t> ts) { ftdc_timestamp = ts; }
        inline void Set_Singles_TDC_timestamp_raw(std::vector<uint32_t> ts_raw) { ftdc_timestamp_raw = ts_raw; }
        inline void Set_Singles_TDC_ID(std::vector<uint32_t> tdc) { fsingles_tdc_id = tdc; }
        
        inline void Set_SC41L_hits(std::vector<uint32_t> sc41l) { fsc41l_hits = sc41l; }
        inline void Set_SC41R_hits(std::vector<uint32_t> sc41r) { fsc41r_hits = sc41r; }
        inline void Set_TM_undelayed_hits(std::vector<uint32_t> tm_u) { ftm_undelayed_hits = tm_u; }
        inline void Set_TM_delayed_hits(std::vector<uint32_t> tm_d) { ftm_delayed_hits = tm_d; }

        inline void Set_FatVME_Mult(int mult) { ffatvme_mult = mult; }

        inline void Set_QDC_ID(std::vector<uint32_t> qdc) { fqdc_id = qdc; }
        inline void Set_QDC_E(std::vector<uint32_t> qdc_e) { fqdc_e = qdc_e; }
        inline void Set_QDC_E_raw(std::vector<uint32_t> qdc_e_raw) { fqdc_e_raw = qdc_e_raw; }
        inline void Set_QDC_T_coarse(std::vector<uint32_t> qdc_t_coarse) { fqdc_t_coarse = qdc_t_coarse; }
        inline void Set_QDC_T_fine(std::vector<uint64_t> qdc_t_fine) { fqdc_t_fine = qdc_t_fine; }
        inline void Set_TDC_ID(std::vector<uint32_t> tdc) { ftdc_id = tdc; }
        inline void Set_TDC_time(std::vector<uint32_t> tdc_time) { ftdc_time = tdc_time; }
        inline void Set_TDC_time_raw(std::vector<uint32_t> tdc_time_raw) { ftdc_time_raw = tdc_time_raw; }

    protected:

        uint64_t fwr_t;

        std::vector<uint32_t> fsingles_e;
        std::vector<uint32_t> fsingles_e_raw;
        std::vector<uint32_t> fsingles_qdc_id;
        std::vector<uint32_t> fsingles_coarse_time;
        std::vector<uint64_t> fsingles_fine_time;

        std::vector<uint32_t> ftdc_timestamp;
        std::vector<uint32_t> ftdc_timestamp_raw;
        std::vector<uint32_t> fsingles_tdc_id;

        std::vector<uint32_t> fsc41l_hits;
        std::vector<uint32_t> fsc41r_hits;
        std::vector<uint32_t> ftm_undelayed_hits;
        std::vector<uint32_t> ftm_delayed_hits;

        int ffatvme_mult;

        std::vector<uint32_t> fqdc_id;
        std::vector<uint32_t> fqdc_e;
        std::vector<uint32_t> fqdc_e_raw;
        std::vector<uint32_t> fqdc_t_coarse;
        std::vector<uint64_t> fqdc_t_fine;
        std::vector<uint32_t> ftdc_id;
        std::vector<uint32_t> ftdc_time;
        std::vector<uint32_t> ftdc_time_raw;

    public:
        ClassDef(FatimaVmeCalData, 1)
};

#endif