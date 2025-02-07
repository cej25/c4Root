#ifndef BB7FebexCalData_H
#define BB7FebexCalData_H

#include "TObject.h"
#include <vector>
#include "TString.h"

class BB7FebexCalItem : public TObject
{
    public:
        BB7FebexCalItem();

        void SetAll(int64_t wr,
                    int d,
                    int si,
                    int st,
                    int e, // probably uint32_t e
                    std::vector<uint16_t> tr,
                    double e_cal,
                    uint64_t evt_t,
                    uint64_t ch_t,
                    int64_t ab_t,
                    int pu,
                    int ov); 
        void Reset();

        int64_t wr_t;
        int DSSD;
        int Side;
        int Strip;
        uint32_t Energy; // double? maybe. e_cal is double.
        std::vector<uint16_t> Trace;
        double EnergyCal;
        uint64_t EventTime;
        uint64_t ChannelTime;
        int64_t AbsoluteTime;
        int Pileup;
        int Overflow;

        ClassDefNV(BB7FebexCalItem, 1);

};

#endif