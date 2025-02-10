#include "GainShift.h"
#include "TFile.h"
#include "c4Logger.h"
#include "TParameter.h"

GainShift::GainShift(TString fhistogram_name, TString ffile_name){
    
    file_name = ffile_name;
    histogram_name = fhistogram_name;

    ReadGainShiftFile();
};

GainShift::~GainShift(){
    if (gain_shifts != nullptr){
        delete gain_shifts;
    }
};

TString GainShift::GetName(){
    return histogram_name;
};

double GainShift::GetGain(uint64_t wr_t){
    

    int64_t time_since_beginning = ((int64_t)wr_t - wr_experiment_start)/1e9;
    int64_t slice_number = time_since_beginning/slices_every;

    return gain_shifts->GetBinContent(slice_number + 1); 

};

        

void GainShift::ReadGainShiftFile(){
    TFile * infile = new TFile(file_name,"READ");

    if (!infile->IsOpen()) {
        c4LOG(fatal,Form("Reading file %s failed!",histogram_name,file_name));
    }

    infile->GetObject(histogram_name,gain_shifts);

    if (gain_shifts == nullptr){
        c4LOG(fatal,Form("Reading Histogram %s from file %s failed!",histogram_name,file_name));
    }

    TParameter<Long64_t> * experiment_start;
    infile->GetObject("wr_experiment_start",experiment_start);
    TParameter<Long64_t> * experiment_end;
    infile->GetObject("wr_experiment_end",experiment_end);
    TParameter<Long64_t> * duration_in_second;
    infile->GetObject("duration_in_seconds",duration_in_second);
    TParameter<Long64_t> * slices;
    infile->GetObject("slices_every",slices);
    TParameter<Long64_t> * number;
    infile->GetObject("number_of_slices",number);

    wr_experiment_start = (uint64_t)experiment_start->GetVal();
    wr_experiment_end = (uint64_t)experiment_end->GetVal();
    duration_in_seconds = (int64_t)duration_in_second->GetVal();
    slices_every = (int64_t)slices->GetVal();
    number_of_slices = (int64_t)number->GetVal();
}



ClassImp(GainShift)