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
        inline uint64_t Get_wr_t() { return fwr_t; }

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
        inline std::vector<uint32_t> Get_SC41L_E_hits() { return fsc41l_e_hits; }
        inline std::vector<uint32_t> Get_SC41R_E_hits() { return fsc41r_e_hits; }
        inline std::vector<uint32_t> Get_TM_undelayed_E_hits() { return ftm_undelayed_e_hits; }
        inline std::vector<uint32_t> Get_TM_delayed_E_hits() { return ftm_delayed_e_hits; }
        
        inline int Get_FatVME_Mult() { return ffatvme_mult; }

        inline std::vector<uint32_t> Get_QDC_ID() { return fqdc_id; }
        inline std::vector<uint32_t> Get_QDC_E() { return fqdc_e; }
        inline std::vector<uint32_t> Get_QDC_E_raw() { return fqdc_e_raw; }
        inline std::vector<uint32_t> Get_QDC_T_coarse() { return fqdc_t_coarse; }
        inline std::vector<uint64_t> Get_QDC_T_fine() { return fqdc_t_fine; }
        inline std::vector<uint32_t> Get_TDC_ID() { return ftdc_id; }
        inline std::vector<uint32_t> Get_TDC_time() { return ftdc_time; }
        inline std::vector<uint32_t> Get_TDC_time_raw() { return ftdc_time_raw; }

        // Setters
        inline void Set_wr_t(uint64_t wr) { fwr_t = wr;}

        inline void Set_Singles_E(std::vector<uint32_t> e) { fsingles_e = e; }
        inline void Set_Singles_E_raw(std::vector<uint32_t> e) { fsingles_e_raw = e; }
        inline void Set_Singles_QDC_ID(std::vector<uint32_t> qdc) { fsingles_qdc_id = qdc; }
        inline void Set_Singles_coarse_time(std::vector<uint32_t> coarse_time) { fsingles_coarse_time = coarse_time; }
        inline void Set_Singles_fine_time(std::vector<uint64_t> fine_time) { fsingles_fine_time = fine_time; }
        inline void Set_Singles_TDC_timestamp(std::vector<uint32_t> ts) { fsingles_tdc_timestamp = ts; }
        inline void Set_Singles_TDC_timestamp_raw(std::vector<uint32_t> ts_raw) { fsingles_tdc_timestamp_raw = ts_raw; }
        inline void Set_Singles_TDC_ID(std::vector<uint32_t> tdc) { fsingles_tdc_id = tdc; }
        
        inline void Set_SC41L_hits(std::vector<uint32_t> sc41l) { fsc41l_hits = sc41l; }
        inline void Set_SC41R_hits(std::vector<uint32_t> sc41r) { fsc41r_hits = sc41r; }
        inline void Set_TM_undelayed_hits(std::vector<uint32_t> tm_u) { ftm_undelayed_hits = tm_u; }
        inline void Set_TM_delayed_hits(std::vector<uint32_t> tm_d) { ftm_delayed_hits = tm_d; }
        inline void Set_SC41L_E_hits(std::vector<uint32_t> sc41l) { fsc41l_e_hits = sc41l; }
        inline void Set_SC41R_E_hits(std::vector<uint32_t> sc41r) { fsc41r_e_hits = sc41r; }
        inline void Set_TM_undelayed_E_hits(std::vector<uint32_t> tm_u) { ftm_undelayed_e_hits = tm_u; }
        inline void Set_TM_delayed_E_hits(std::vector<uint32_t> tm_d) { ftm_delayed_e_hits = tm_d; }

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

        std::vector<uint32_t> fsingles_tdc_timestamp;
        std::vector<uint32_t> fsingles_tdc_timestamp_raw;
        std::vector<uint32_t> fsingles_tdc_id;

        std::vector<uint32_t> fsc41l_hits;
        std::vector<uint32_t> fsc41r_hits;
        std::vector<uint32_t> ftm_undelayed_hits;
        std::vector<uint32_t> ftm_delayed_hits;
        std::vector<uint32_t> fsc41l_e_hits;
        std::vector<uint32_t> fsc41r_e_hits;
        std::vector<uint32_t> ftm_undelayed_e_hits;
        std::vector<uint32_t> ftm_delayed_e_hits;

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





class FatimaVmeQDCCalItem : public TObject
{
    public:
        FatimaVmeQDCCalItem();

        void Reset();
        void SetAll(uint64_t wr, int det, double ct, double ft, double ql, uint32_t qlr, uint32_t qsr);
        uint64_t Get_wr_t() const;
        double Get_coarse_time() const;
        double Get_fine_time() const;
        double Get_qlong() const;
        uint32_t Get_qlong_raw() const;
        uint32_t Get_qshort_raw() const;
        int Get_detector() const;

        ClassDefNV(FatimaVmeQDCCalItem, 2)
    
    private:

        uint64_t wr_t;
        double coarse_time;
        double fine_time;
        uint32_t qlong; // calibrate e
        uint32_t qlong_raw;
        uint32_t qshort_raw;
        int detector;

};


class FatimaVmeTDCCalItem : public TObject
{
    public:
        FatimaVmeTDCCalItem();

        void Reset();
        void SetAll(uint64_t wr, int det, double ts, uint32_t ts_raw);

        uint64_t Get_wr_t() const;
        double Get_timestamp() const;
        uint32_t Get_timestamp_raw() const;
        int Get_detector() const;

        ClassDefNV(FatimaVmeTDCCalItem, 2)
    
    private:

        uint64_t wr_t;
        double timestamp;
        uint32_t timestamp_raw;
        int detector;

};

class FatimaVmeResiduals : public TObject
{
    public:
        FatimaVmeResiduals();

        void Reset();
        void SetAll(double left, double right, double tmd, double tmu);

        double Get_SC41L() const;
        double Get_SC41R() const;
        double Get_TM_Delayed() const;
        double Get_TM_Undelayed() const;

        ClassDefNV(FatimaVmeResiduals, 2)

    private:
        double sc41l;
        double sc41r;
        double tm_delayed;
        double tm_undelayed;
};


inline uint64_t FatimaVmeTDCCalItem::Get_wr_t() const
{
    return wr_t;
}

inline double FatimaVmeTDCCalItem::Get_timestamp() const
{
    return timestamp;
}

inline uint32_t FatimaVmeTDCCalItem::Get_timestamp_raw() const
{
    return timestamp_raw;
}

inline int FatimaVmeTDCCalItem::Get_detector() const
{
    return detector;
}

inline int FatimaVmeQDCCalItem::Get_detector() const
{
    return detector;
}

inline uint64_t FatimaVmeQDCCalItem::Get_wr_t() const
{
    return wr_t;
}

inline double FatimaVmeQDCCalItem::Get_coarse_time() const
{
    return coarse_time;
}

inline double FatimaVmeQDCCalItem::Get_fine_time() const
{
    return fine_time;
}

inline double FatimaVmeQDCCalItem::Get_qlong() const
{
    return qlong;
}

inline uint32_t FatimaVmeQDCCalItem::Get_qlong_raw() const
{
    return qlong_raw;
}

inline uint32_t FatimaVmeQDCCalItem::Get_qshort_raw() const
{
    return qshort_raw;
}

#endif
