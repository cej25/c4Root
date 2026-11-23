#ifndef GainShift_H
#define GainShift_H

#include "TH1.h"

class GainShift
{
    public:
        GainShift(TString fhistogram_name, TString ffile_name);

        virtual ~GainShift();

        TString GetName();

        double GetGain(uint64_t wr_t);
        
        void ReadGainShiftFile();



    public:
        TString histogram_name;
        TString file_name;

        TH1D * gain_shifts = nullptr;
        
        uint64_t wr_experiment_start;
        uint64_t wr_experiment_end;
        int64_t duration_in_seconds;
        int64_t slices_every;
        int64_t number_of_slices;


    public:
        ClassDef(GainShift, 1)
};

#endif