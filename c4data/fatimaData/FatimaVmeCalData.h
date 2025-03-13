#ifndef FatimaVmeCalData_H
#define FatimaVmeCalData_H

#include "TObject.h"
#include <vector>

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

        ClassDefNV(FatimaVmeResiduals, 2);

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

inline double FatimaVmeResiduals::Get_SC41L() const
{
    return sc41l;
} 

inline double FatimaVmeResiduals::Get_SC41R() const
{
    return sc41r;
} 

inline double FatimaVmeResiduals::Get_TM_Delayed() const
{
    return tm_delayed;
} 

inline double FatimaVmeResiduals::Get_TM_Undelayed() const
{
    return tm_undelayed;
} 

#endif
