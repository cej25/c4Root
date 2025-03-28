#ifndef BB7FebexCalData_H
#define BB7FebexCalData_H

#include "TObject.h"
#include <vector>
#include "TString.h"

class BB7FebexCalItem : public TObject
{
    public:
        BB7FebexCalItem();

        void SetAll(Long64_t wr,
                    Int_t d,
                    Int_t si,
                    Int_t st,
                    Int_t e,
                    std::vector<UShort_t> tr,
                    Double_t e_cal,
                    ULong64_t evt_t,
                    ULong64_t ch_t,
                    Long64_t ab_t,
                    Bool_t pu,
                    Bool_t ov); 
        void Reset();

        Long64_t wr_t;
        Int_t DSSD;
        Int_t Side;
        Int_t Strip;
        Int_t Energy;
        std::vector<UShort_t> Trace;
        Double_t EnergyCal;
        ULong64_t EventTime;
        ULong64_t ChannelTime;
        Long64_t AbsoluteTime;
        Bool_t Pileup;
        Bool_t Overflow;

        ClassDefNV(BB7FebexCalItem, 1);

};

#endif