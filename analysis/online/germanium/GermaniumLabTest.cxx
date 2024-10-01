// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "GermaniumLabTest.h"
#include "EventHeader.h"
#include "GermaniumFebexData.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TF1.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include <sstream>
#include <chrono>


GermaniumLabTest::GermaniumLabTest() : GermaniumLabTest("GermaniumLabTest")
{
}

GermaniumLabTest::GermaniumLabTest(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGeUncal(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
}

GermaniumLabTest::~GermaniumLabTest()
{
    c4LOG(info, "");
    if (fHitGeUncal)
        delete fHitGeUncal;
}

void GermaniumLabTest::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus GermaniumLabTest::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    run->GetHttpServer()->RegisterCommand("ResetAllHisto", Form("/Objects/%s", GetName()) + TString("/->ResetAllHisto()"));
    run->GetHttpServer()->RegisterCommand("ResetOneHisto", Form("/Objects/%s", GetName()) + TString("/->ResetOneHisto(\%arg1\%)"));
    run->GetHttpServer()->RegisterCommand("SetFitLimits1173", Form("/Objects/%s", GetName()) + TString("/->SetFitLimits1173(\%arg1\%,\%arg2\%,\%arg3\%)"));
    run->GetHttpServer()->RegisterCommand("SetFitLimits1332", Form("/Objects/%s", GetName()) + TString("/->SetFitLimits1332(\%arg1\%,\%arg2\%,\%arg3\%)"));
    run->GetHttpServer()->RegisterCommand("AddNewMeasurement", Form("/Objects/%s", GetName()) + TString("/->AddNewMeasurement(\%arg1\%,\%arg2\%,\%arg3\%,\%arg4\%,\%arg5\%)"));
    

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitGeUncal = (TClonesArray*)mgr->GetObject("GermaniumFebexData");
    c4LOG_IF(fatal, !fHitGeUncal, "Branch GermaniumFebexData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");
    
    TDirectory::TContext ctx(nullptr);

    dir_germanium = new TDirectory("DEGAS", "DEGAS", "", 0);
    mgr->Register("DEGAS", "DEGAS Directory", dir_germanium, false);
    histograms->Add(dir_germanium);
    dir_germanium->cd();

    
    c_germanium_uncal  = new TCanvas*[number_of_channels];
    h1_germanium_uncal = new TH1F*[number_of_channels];
    for (int ihist = 0; ihist < number_of_channels; ihist++){
        c_germanium_uncal[ihist] = new TCanvas(Form("c_germanium_uncal_%i",ihist),"Germanium spectra",650,350);
        c_germanium_uncal[ihist]->cd();
        h1_germanium_uncal[ihist] = new TH1F(Form("h1_germanium_uncal_%i",ihist),Form("DEGAS uncal spectrum ihist %i",ihist),funcal_nbins,funcal_bin_low,funcal_bin_high);
        h1_germanium_uncal[ihist]->GetXaxis()->SetTitle("uncal (keV)");
        h1_germanium_uncal[ihist]->Draw();
        
        
        dir_germanium->Append(c_germanium_uncal[ihist]);
        dir_germanium->Append(h1_germanium_uncal[ihist]);
    }
    
    c_germanium_uncal_1173 = new TCanvas*[number_of_channels];
    h1_germanium_uncal_1173 = new TH1F*[number_of_channels];
    c_germanium_uncal_1332 = new TCanvas*[number_of_channels];
    h1_germanium_uncal_1332 = new TH1F*[number_of_channels];

    for (int ihist = 0; ihist < number_of_channels; ihist++){
        c_germanium_uncal_1173[ihist] = nullptr;
        h1_germanium_uncal_1173[ihist] = nullptr;
        c_germanium_uncal_1332[ihist] = nullptr;
        h1_germanium_uncal_1332[ihist] = nullptr;
    } 
    


    return kSUCCESS;
}

void GermaniumLabTest::ResetAllHisto()
{
    for (int ihist = 0; ihist < number_of_channels; ihist++){
        h1_germanium_uncal[ihist]->Reset();
    }
    c4LOG(info, "DEGAS histograms reset.");
}

void GermaniumLabTest::ResetOneHisto(int vector_index)
{
    int ihist = active_channels_indexes.at(vector_index);
    h1_germanium_uncal[ihist]->Reset();
    c4LOG(info, "DEGAS histograms reset.");
}

void GermaniumLabTest::SetFitLimits1173(int vector_index, int xlow, int xhigh)
{
    fit_low_limit_1173.at(vector_index) = xlow;
    fit_high_limit_1173.at(vector_index) = xhigh;
    c4LOG(info, "Fit limits set for 1173 keV line.");

    c_germanium_uncal_1173  = new TCanvas*[number_of_channels];
    h1_germanium_uncal_1173 = new TH1F*[number_of_channels];
    for (int ihist = 0; ihist < number_of_channels; ihist++){
        c_germanium_uncal_1173[ihist] = new TCanvas(Form("c_germanium_uncal_1173_%i",ihist),"Germanium spectra",650,350);
        c_germanium_uncal_1173[ihist]->cd();
        h1_germanium_uncal_1173[ihist] = new TH1F(Form("h1_germanium_uncal_1173_%i",ihist),Form("DEGAS uncal spectrum 1173 ihist %i",ihist),500,xlow,xhigh);
        h1_germanium_uncal_1173[ihist]->GetXaxis()->SetTitle("uncal (keV)");
        h1_germanium_uncal_1173[ihist]->Draw();
        
        
        dir_germanium->Append(c_germanium_uncal_1173[ihist]);
        dir_germanium->Append(h1_germanium_uncal_1173[ihist]);
    }
}

void GermaniumLabTest::SetFitLimits1332(int vector_index, int xlow, int xhigh)
{
    fit_low_limit_1332.at(vector_index) = xlow;
    fit_high_limit_1332.at(vector_index) = xhigh;
    c4LOG(info, "Fit limits set for 1332 keV line.");

    c_germanium_uncal_1332  = new TCanvas*[number_of_channels];
    h1_germanium_uncal_1332 = new TH1F*[number_of_channels];
    for (int ihist = 0; ihist < number_of_channels; ihist++){
        c_germanium_uncal_1332[ihist] = new TCanvas(Form("c_germanium_uncal_1332_%i",ihist),"Germanium spectra",650,350);
        c_germanium_uncal_1332[ihist]->cd();
        h1_germanium_uncal_1332[ihist] = new TH1F(Form("h1_germanium_uncal_1332_%i",ihist),Form("DEGAS uncal spectrum 1332 ihist %i",ihist),500,xlow,xhigh);
        h1_germanium_uncal_1332[ihist]->GetXaxis()->SetTitle("uncal (keV)");
        h1_germanium_uncal_1332[ihist]->Draw();
        
        
        dir_germanium->Append(c_germanium_uncal_1332[ihist]);
        dir_germanium->Append(h1_germanium_uncal_1332[ihist]);
    }
}


double skewed_gaussian(Double_t * x, Double_t * p){
    // p(0) area, p(1) centroid, p(2) sigma, p(3) alpha (skewness)
    double x0 = (x[0] - p[1])/p[2];
    double g = (p[0])/(p[2]*TMath::Sqrt(TMath::Pi()*2))*TMath::Exp(-(x0*x0)/2);
    return g*(1+TMath::Erf(p[3]*x0/TMath::Sqrt(2)));
}



double skewed_gaussian_with_background(Double_t * x, Double_t * p){
    // p(0) area, p(1) centroid, p(2) sigma, p(3) alpha (skewness)

    double x0 = (x[0] - p[1])/p[2];
    double g = (p[0])/(p[2]*TMath::Sqrt(TMath::Pi()*2))*TMath::Exp(-(x0*x0)/2);
    return g*(1+TMath::Erf(p[3]*x0/TMath::Sqrt(2)));
}

TF1 * GermaniumLabTest::MakeFitFunc(TString function, int index){
    
    TF1 * func;

    if (function == "gaus"){
        func = new TF1(Form("gaus_%i",index), "gaus", 0, 1);
        return func;
    }else if (function == "skewedgaus"){
        func = new TF1(Form("skewedgaus_%i",index),skewed_gaussian,0,1,4);
        func->SetParameter(3, 0.);
        func->SetParLimits(3, 0., 100.);

        return func;
    }

    c4LOG(fatal,"Not implemented function");

}


double GermaniumLabTest::GetFWxM(TF1 * func, double ylim, double xrangemin, double xrangemax){
    // ylim = 0.5, 0.1 etc

    double xmax = func->GetMaximumX(xrangemin, xrangemax);
    double max = func->GetMaximum(xrangemin, xrangemax);

    double xlowside = func->GetX(max*ylim,xrangemin,xmax*0.9999);
    double xhighside = func->GetX(max*ylim,xmax*1.00001,xrangemax);

    double fwxm = xhighside - xlowside; 

    return fwxm;
}


void GermaniumLabTest::AddNewMeasurement(
    int vector_index,
    int febex_board_id_value,
    int febex_ch_id_value,
    int degas_det_id_value,
    int degas_crystal_id_value){
    
    c4LOG_IF(fatal, vector_index != active_channels_indexes.size(), "Inconsistency");

    int histo_index = febex_board_id_value*16 + febex_ch_id_value;
    
    active_channels_indexes.push_back(histo_index);
    eb_crystal_id.push_back(degas_crystal_id_value);
    degas_detector_id.push_back(degas_det_id_value);
    board_ids.push_back(febex_board_id_value);
    ch_ids.push_back(febex_ch_id_value);

    fit_low_limit_1173.push_back(-1);
    fit_high_limit_1173.push_back(-1);
    fit_low_limit_1332.push_back(-1);
    fit_high_limit_1332.push_back(-1);

    fitfunc_1173.push_back(nullptr);
    fitfunc_1332.push_back(nullptr);

    gain_coeff.push_back(1);
    offset_coeff.push_back(0);

}

/*
void GermaniumLabTest::StartTest(int vector_index){
    //auto start = std::chrono::high_resolution_clock::now();
    return;
}

void GermaniumLabTest::StopTest(int vector_index){
    return;
}
*/


void GermaniumLabTest::Exec(Option_t* option){

    if (fHitGeUncal && fHitGeUncal->GetEntriesFast() > 0){

        Int_t nHits = fHitGeUncal->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++){
            
            GermaniumFebexData* hit1 = (GermaniumFebexData*)fHitGeUncal->At(ihit);
            if (!hit1) continue;

            uint32_t num_channels_fired1 = hit1->Get_num_channels_fired();
            uint64_t event_trigger_time1 = hit1->Get_event_trigger_time();
            uint16_t hit_pattern1 = hit1->Get_hit_pattern();
            uint8_t board_id1 = hit1->Get_board_id();
            uint8_t pileup1 = hit1->Get_pileup();
            uint8_t overflow1 = hit1->Get_overflow();
            uint8_t channel_id1 = hit1->Get_channel_id();
            double channel_trigger_time1 = hit1->Get_channel_trigger_time();
            int32_t channel_energy1 = hit1->Get_channel_energy();
            uint16_t wr_subsystem_id1 = hit1->Get_wr_subsystem_id();
            uint64_t wr_t1 = hit1->Get_wr_t();
            
            h1_germanium_uncal[board_id1*16 + channel_id1]->Fill(channel_energy1);
            if (h1_germanium_uncal_1173[board_id1*16 + channel_id1]!=nullptr && h1_germanium_uncal_1332[board_id1*16 + channel_id1]!=nullptr) h1_germanium_uncal_1173[board_id1*16 + channel_id1]->Fill(channel_energy1);
            if (h1_germanium_uncal_1332[board_id1*16 + channel_id1]!=nullptr && h1_germanium_uncal_1173[board_id1*16 + channel_id1]!=nullptr) h1_germanium_uncal_1332[board_id1*16 + channel_id1]->Fill(channel_energy1);

        }
    }

    fNEvents += 1;
}



void GermaniumLabTest::FitPeak(int vector_index){
    c4LOG_IF(fatal, vector_index >= active_channels_indexes.size(), "Wrong index");
    

    if (fitfunc_1173.at(vector_index) == nullptr) fitfunc_1173.at(vector_index) = MakeFitFunc("skewedgaus",vector_index);
    if (fitfunc_1332.at(vector_index) == nullptr) fitfunc_1332.at(vector_index) = MakeFitFunc("skewedgaus",vector_index);

    fitfunc_1173.at(vector_index)->SetRange(fit_low_limit_1173.at(vector_index),fit_high_limit_1173.at(vector_index));
    fitfunc_1332.at(vector_index)->SetRange(fit_low_limit_1332.at(vector_index),fit_high_limit_1332.at(vector_index));
    
    TF1 * simple_gaus = new TF1("gaus","gaus",0,1);
    simple_gaus->SetRange(fit_low_limit_1173.at(vector_index),fit_high_limit_1173.at(vector_index));
    h1_germanium_uncal_1173[active_channels_indexes.at(vector_index)]->Fit(simple_gaus,"QR");
    fitfunc_1173.at(vector_index)->SetParameter(0, simple_gaus->GetParameter(0));
    fitfunc_1173.at(vector_index)->SetParameter(1, simple_gaus->GetParameter(1));
    fitfunc_1173.at(vector_index)->SetParameter(2, simple_gaus->GetParameter(2));
    h1_germanium_uncal_1173[active_channels_indexes.at(vector_index)]->Fit(fitfunc_1173.at(vector_index),"QR");
    
    
    simple_gaus->SetRange(fit_low_limit_1332.at(vector_index),fit_high_limit_1332.at(vector_index));
    h1_germanium_uncal_1332[active_channels_indexes.at(vector_index)]->Fit(simple_gaus,"QR");
    fitfunc_1332.at(vector_index)->SetParameter(0, simple_gaus->GetParameter(0));
    fitfunc_1332.at(vector_index)->SetParameter(1, simple_gaus->GetParameter(1));
    fitfunc_1332.at(vector_index)->SetParameter(2, simple_gaus->GetParameter(2));
    h1_germanium_uncal_1332[active_channels_indexes.at(vector_index)]->Fit(fitfunc_1332.at(vector_index),"QR");


    gain_coeff.at(vector_index) = (1332 - 1173)/(fitfunc_1332.at(vector_index)->GetParameter(1) - fitfunc_1173.at(vector_index)->GetParameter(1));
    offset_coeff.at(vector_index) = 1332 - gain_coeff.at(vector_index)*fitfunc_1332.at(vector_index)->GetParameter(1);

    // FWHM:
    double fwhm_1173 = GetFWxM(fitfunc_1173.at(vector_index),0.5,fit_low_limit_1173.at(vector_index),fit_high_limit_1173.at(vector_index));
    double fwhm_1332 = GetFWxM(fitfunc_1332.at(vector_index),0.5,fit_low_limit_1332.at(vector_index),fit_high_limit_1332.at(vector_index));
    
    // FWTM:
    double fwtm_1173 = GetFWxM(fitfunc_1173.at(vector_index),0.1,fit_low_limit_1173.at(vector_index),fit_high_limit_1173.at(vector_index));
    double fwtm_1332 = GetFWxM(fitfunc_1332.at(vector_index),0.1,fit_low_limit_1332.at(vector_index),fit_high_limit_1332.at(vector_index));

    h1_germanium_uncal_1173[active_channels_indexes.at(vector_index)]->SetTitle(Form("FWHM = %f, FWTM = %f",fwhm_1173*gain_coeff.at(vector_index), fwtm_1173*gain_coeff.at(vector_index)));
    h1_germanium_uncal_1332[active_channels_indexes.at(vector_index)]->SetTitle(Form("FWHM = %f, FWTM = %f",fwhm_1332*gain_coeff.at(vector_index), fwtm_1332*gain_coeff.at(vector_index)));

}



void GermaniumLabTest::FinishEvent()
{

    if (fNEvents % 100 == 0){

    for (int vector_index = 0; vector_index<active_channels_indexes.size(); vector_index++){
        if (fit_low_limit_1173.at(vector_index) > 0 && fit_high_limit_1173.at(vector_index) > 0 && fit_low_limit_1332.at(vector_index) > 0 && fit_high_limit_1332.at(vector_index) > 0){
            
            FitPeak(vector_index);
    
        }   
    }   
    
    }
    
    
    if (fHitGeUncal){
        fHitGeUncal->Clear();
    }
}

void GermaniumLabTest::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }
    if (fHitGeUncal)
    {
        c4LOG(info, "DEGAS histograms written to file.");
    }
}

ClassImp(GermaniumLabTest)
