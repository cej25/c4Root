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
#include <iomanip>

#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem> // For creating directories
#include <string>


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
    run->GetHttpServer()->RegisterCommand("AddNewMeasurement", Form("/Objects/%s", GetName()) + TString("/->AddNewMeasurement(\%arg1\%,\%arg2\%,\%arg3\%,\%arg4\%,\%arg5\%,\%arg6\%,\%arg7\%)"));
    run->GetHttpServer()->RegisterCommand("StartMeasurement", Form("/Objects/%s", GetName()) + TString("/->StartMeasurement(\%arg1\%)"));
    run->GetHttpServer()->RegisterCommand("StopMeasurementCompleted", Form("/Objects/%s", GetName()) + TString("/->StopMeasurementCompleted(\%arg1\%)"));
    run->GetHttpServer()->RegisterCommand("SetLog", Form("/Objects/%s", GetName()) + TString("/->SetLog(\%arg1\%)"));
    run->GetHttpServer()->RegisterCommand("PauseMeasurement", Form("/Objects/%s", GetName()) + TString("/->PauseMeasurement(\%arg1\%)"));
    

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");
 
    fHitGeUncal = (TClonesArray*)mgr->GetObject("GermaniumFebexTraceData");
    c4LOG_IF(fatal, !fHitGeUncal, "Branch GermaniumFebexTraceData not found!");

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
    
    
    c_germanium_raw_all  = new TCanvas("c_germanium_raw_all","c_germanium_raw_all",600,600);
    c_germanium_raw_all->Divide((number_of_channels<5) ? number_of_channels : 5,(number_of_channels%5==0) ? (number_of_channels/5) : (number_of_channels/5 + 1));
    h1_germanium_raw = new TH1F*[number_of_channels];
    for (int ihist = 0; ihist < number_of_channels; ihist++){
        c_germanium_raw_all->cd(ihist+1);
        h1_germanium_raw[ihist] = new TH1F(Form("h1_germanium_raw_%i",ihist),Form("DEGAS uncal spectrum ihist %i",ihist),funcal_nbins,funcal_bin_low,funcal_bin_high);
        h1_germanium_raw[ihist]->GetXaxis()->SetTitle("uncal (keV)");
        h1_germanium_raw[ihist]->Draw();
        
        
        dir_germanium->Append(h1_germanium_raw[ihist]);
    }
    c_germanium_raw_all->cd(0);
    dir_germanium->Append(c_germanium_raw_all);

    last_trace_plotted = std::chrono::steady_clock::now();

    c_germanium_trace  = new TCanvas("c_germanium_trace","c_germanium_trace",600,600);
    c_germanium_trace->Divide((number_of_channels<5) ? number_of_channels : 5,(number_of_channels%5==0) ? (number_of_channels/5) : (number_of_channels/5 + 1));
    h1_germanium_trace = new TH1F*[number_of_channels];
    for (int ihist = 0; ihist < number_of_channels; ihist++){
        c_germanium_trace->cd(ihist+1);
        h1_germanium_trace[ihist] = new TH1F(Form("h1_germanium_trace_%i",ihist),Form("DEGAS trace ihist %i",ihist),trace_length_plot,0,trace_length_plot);
        h1_germanium_trace[ihist]->GetXaxis()->SetTitle("time (10 ns)");
        h1_germanium_trace[ihist]->GetYaxis()->SetTitle("ADC value");
        h1_germanium_trace[ihist]->Draw();
        
        
        dir_germanium->Append(h1_germanium_trace[ihist]);
    }
    c_germanium_trace->cd(0);
    dir_germanium->Append(c_germanium_trace);


    
    


    return kSUCCESS;
}

void GermaniumLabTest::ResetAllHisto()
{
    for (int ihist = 0; ihist < number_of_channels; ihist++){
        h1_germanium_uncal[ihist]->Reset();
        h1_germanium_raw[ihist]->Reset();
    }
    c4LOG(info, "DEGAS histograms reset.");
}

void GermaniumLabTest::SetLog(int vector_index){
    int ihist = active_channels_indexes.at(vector_index);
    c4LOG(info,Form("Set log %i, current %i",vector_index, c_germanium_uncal[ihist]->GetLogy()));
    if (c_germanium_uncal[ihist]->GetLogy() == 0) c_germanium_uncal[ihist]->SetLogy(1);
    else c_germanium_uncal[ihist]->SetLogy(0);

    c4LOG(info, "Log set");
}

void GermaniumLabTest::ResetOneHisto(int vector_index)
{
    c4LOG(info,Form("Resetting, %i",vector_index));
    int ihist = active_channels_indexes.at(vector_index);
    h1_germanium_uncal[ihist]->Reset();
    c4LOG(info, "DEGAS histograms reset.");
}

void GermaniumLabTest::SetFitLimits1173(int vector_index, int xlow, int xhigh)
{
    fit_low_limit_1173.at(vector_index) = xlow;
    fit_high_limit_1173.at(vector_index) = xhigh;
    c4LOG(info, "Fit limits set for 1173 keV line.");


}

void GermaniumLabTest::SetFitLimits1332(int vector_index, int xlow, int xhigh)
{
    fit_low_limit_1332.at(vector_index) = xlow;
    fit_high_limit_1332.at(vector_index) = xhigh;
    c4LOG(info, "Fit limits set for 1332 keV line.");

}


double skewed_gaussian(Double_t * x, Double_t * p){
    // p(0) area, p(1) centroid, p(2) sigma, p(3) area tail , p(4) beta

    double x0 = (x[0] - p[1])/p[2];
    double g1 = p[0]/(TMath::Sqrt(2*TMath::Pi()*p[2]*p[2]))*TMath::Exp(-x0*x0/2);
    
    //y = constant * EXP( (x-c)/beta ) * ERFC( (x-c)/(SQRT(2)*sigma) + sigma/(SQRT(2)*beta) ) 
    double s2 = p[3]*TMath::Exp((x[0]-p[1])/p[4])*TMath::Erfc((x[0]-p[1])/(p[2]*TMath::Sqrt(2)) + p[2]/(TMath::Sqrt(2)*p[4]));
    
    return g1 + s2;
}



double skewed_gaussian_with_background(Double_t * x, Double_t * par){
    
    // Parameters: par[0] = norm, par[1] = mean, par[2] = sigma, par[3] = alpha, par[4] = bcg_0, par[5] = bcg_1
    Double_t arg      = (x[0] - par[1]) / par[2];
    Double_t erf_term = TMath::Erf(par[3] * arg * (1/TMath::Sqrt(2)));
    return par[0] / (par[2] * (TMath::Sqrt(2*TMath::Pi()))) * TMath::Exp(-0.5 * arg * arg) * (1 + erf_term) + par[4] + par[5] * x[0];
}

double radware_fit(Double_t * x, Double_t * p){
    // p(0) area, p(1) centroid, p(2) sigma
    // p(3) area tail. p[4] beta
    // p(5) step paramteter
    // p(6) bg offset, p(7) bg lin

    double x0 = (x[0] - p[1])/p[2];
    
    double g1 = p[0]*TMath::Exp(-x0*x0/2);
    
    //y = constant * EXP( (x-c)/beta ) * ERFC( (x-c)/(SQRT(2)*sigma) + sigma/(SQRT(2)*beta) ) 
    double s2 = (p[3]*p[0])*TMath::Exp((x[0]-p[1])/p[4])*TMath::Erfc((x[0]-p[1])/(p[2]*TMath::Sqrt(2)) + p[2]/(TMath::Sqrt(2)*p[4]));

    //y = constant * ERFC( (x-c)/(SQRT(2)*sigma) ) 
    double s3 = (p[5]*p[0])*TMath::Erfc(x0/TMath::Sqrt(2));


    double bg = p[6] + x[0]*p[7];

    return g1 + s2 + s3 + bg;
    
}




TF1 * GermaniumLabTest::MakeFitFunc(TString function, int index){
    
    TF1 * func;

    if (function == "gaus"){
        func = new TF1(Form("gaus_%i",index), "gaus", 0, 1);
        func->SetParName(0, "Area");
        func->SetParName(1, "Centroid");
        func->SetParName(2, "Std. Dev.");

        return func;
    }
    else if (function == "skewedgaus"){
        func = new TF1(Form("skewedgaus_%i",index),skewed_gaussian,0,1,5);
        
        func->SetParName(0, "Area");
        func->SetParLimits(0,0,1e20);
        func->SetParName(1, "Centroid");
        func->SetParLimits(1,0,4e6);
        func->SetParName(2, "Std. Dev.");
        func->SetParLimits(2,0,1e4);
        

        func->SetParName(3, "Area tail");
        func->SetParLimits(3,0,1);

        func->SetParName(4, "Beta");
        func->SetParLimits(3,0,10);
        
        return func;
    }else if (function == "skewedgausbg"){
        func = new TF1(Form("skewedgausbg_%i",index),skewed_gaussian_with_background,0,1,6);

        func->SetParName(0, "Area");
        //func->SetParLimits(0,0,1e20);
        func->SetParName(1, "Centroid");
        func->SetParName(2, "Std. Dev.");
        

        func->SetParName(3, "alpha");
        //func->SetParameter(3,0);
        //func->SetParLimits(3,0,100);

        
        func->SetParName(4, "BG off");
        //func->SetParLimits(4, 0., 1e6);
        //func->SetParameter(4, 0.);

        func->SetParName(5, "BG gain");    
        //func->SetParLimits(5, -1e3, 1e3);
        //func->SetParameter(5, 0.);
        
        return func;
    }else if (function == "radwarefunc"){
        func = new TF1(Form("radwarefunc_%i",index),radware_fit,0,1,8);
        func->SetParName(0, "Area");
        func->SetParName(1, "Centroid");
        func->SetParName(2, "Std. Dev.");
        func->SetParName(3, "Area tail (skewness)");
        func->SetParName(4, "beta");
        func->SetParName(5, "Step");    
        func->SetParName(6, "BG offset");    
        func->SetParName(7, "BG gain");    
        
        return func;
    }

    c4LOG(fatal,"Not implemented function");
    func = new TF1(); return func; // avoid dumb warning

}


double GermaniumLabTest::GetFWxM(TF1 * func, double ylim, double xrangemin, double xrangemax){
    // ylim = 0.5, 0.1 etc
    Int_t oldLevel = gErrorIgnoreLevel;

    gErrorIgnoreLevel = kBreak;  // Temporarily suppress warnings
    double xmax = func->GetMaximumX(xrangemin, xrangemax);
    double max = func->GetMaximum(xrangemin, xrangemax);

    double xlowside = func->GetX(max*ylim,xrangemin,xmax*0.9999);
    double xhighside = func->GetX(max*ylim,xmax*1.00001,xrangemax);
    gErrorIgnoreLevel = oldLevel;  // Restore the previous level after

    double fwxm = xhighside - xlowside; 

    return fwxm;
}

double GermaniumLabTest::GetFWxMHistogram(TH1 * histo, TF1 * fitgaus, double ylim, double xrangemin, double xrangemax){
    // ylim = 0.5, 0.1 etc
    Int_t oldLevel = gErrorIgnoreLevel;

    gErrorIgnoreLevel = kBreak;  // Temporarily suppress warnings

    double xmax = fitgaus->GetMaximum(xrangemin, xrangemax);
    double thresholdy = ylim*xmax;

    double xlowside = histo->GetBinCenter(histo->FindFirstBinAbove(thresholdy, 1, histo->FindBin(xrangemin), histo->FindBin(fitgaus->GetParameter(1))));
    double xhighside= histo->GetBinCenter(histo->FindLastBinAbove(thresholdy, 1,  histo->FindBin(fitgaus->GetParameter(1)), histo->FindBin(xrangemax)));

    gErrorIgnoreLevel = oldLevel;  // Restore the previous level after

    double fwxm = xhighside - xlowside; 

    return fwxm;
}


void GermaniumLabTest::AddNewMeasurement(
    int vector_index,
    int febex_board_id_value,
    int febex_ch_id_value,
    int degas_det_id_value,
    int degas_det_channel_value,
    int degas_crystal_id_value,
    int voltage){
    
    c4LOG_IF(fatal, vector_index != active_channels_indexes.size(), "Inconsistency");

    int histo_index = febex_board_id_value*16 + febex_ch_id_value;
    
    active_channels_indexes.push_back(histo_index);
    eb_crystal_id.push_back(degas_crystal_id_value);
    voltages.push_back(voltage);
    degas_detector_id.push_back(degas_det_id_value);
    degas_detector_channel.push_back((char)degas_det_channel_value);
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

    timers.push_back(std::chrono::steady_clock::now());
    test_running.push_back(false);
    test_finished.push_back(false);
    test_paused.push_back(false);

}


int GermaniumLabTest::GetVectorIndex(int febex_board, int febex_channel){
    for (int i = 0; i<board_ids.size(); i++){
        if (board_ids.at(i) == febex_board && ch_ids.at(i) == febex_channel){
            return i;
        }
    }

    return -1;
}

void GermaniumLabTest::StartMeasurement(int vector_index){

    if (test_paused.at(vector_index)){
        test_paused.at(vector_index) = false;
        return;
    }

    ResetOneHisto(vector_index);

    test_running.at(vector_index) = true;
    test_finished.at(vector_index) = false;

    timers.at(vector_index) = std::chrono::steady_clock::now();
}

void GermaniumLabTest::PauseMeasurement(int vector_index){
    
    test_running.at(vector_index) = false;
    test_paused.at(vector_index) = true;

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
    

    
    bool plot_trace = true;
    /*
    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - last_trace_plotted).count() > 0.5){
        plot_trace = true;
    }
    */

    if (fHitGeUncal && fHitGeUncal->GetEntriesFast() > 0){

        Int_t nHits = fHitGeUncal->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++){
            
            GermaniumFebexTraceData* hit1 = (GermaniumFebexTraceData*)fHitGeUncal->At(ihit);
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
            
            int vector_index_this_hit = GetVectorIndex(board_id1,channel_id1);

            if (vector_index_this_hit  >= 0 && plot_trace && fit_low_limit_1332.at(vector_index_this_hit) < channel_energy1 && fit_high_limit_1332.at(vector_index_this_hit) > channel_energy1 ){
                h1_germanium_trace[board_id1*16 + channel_id1]->Reset();
                for (int trace_index = 0; trace_index < trace_length_plot; trace_index ++){
                    h1_germanium_trace[board_id1*16 + channel_id1]->SetBinContent(trace_index+1, hit1->Get_trace_value(trace_index));
                    h1_germanium_trace[board_id1*16 + channel_id1]->SetTitle(Form("Trace energy = %3f (*1000)",channel_energy1/1e3));
                }
            }

            if (overflow1 != 0) continue; 
            if (pileup1 != 0) continue; 

            //c4LOG(info,Form("board = %i, ch = %i",board_id1,channel_id1));

            h1_germanium_raw[board_id1*16 + channel_id1]->Fill(channel_energy1);

            if (vector_index_this_hit < 0) continue;
            
            if (!test_paused.at(vector_index_this_hit) && !test_finished.at(vector_index_this_hit)){

                h1_germanium_uncal[board_id1*16 + channel_id1]->Fill(channel_energy1);
                
            }

        }
    }

    fNEvents += 1;
}



void GermaniumLabTest::FitPeak(int vector_index){
    c4LOG_IF(fatal, vector_index >= active_channels_indexes.size(), "Wrong index");
    
    TString fitfunctionname = "radwarefunc";

    if (fitfunc_1173.at(vector_index) == nullptr) fitfunc_1173.at(vector_index) = MakeFitFunc(fitfunctionname,vector_index);
    if (fitfunc_1332.at(vector_index) == nullptr) fitfunc_1332.at(vector_index) = MakeFitFunc(fitfunctionname,vector_index);

    fitfunc_1173.at(vector_index)->SetRange(fit_low_limit_1173.at(vector_index),fit_high_limit_1173.at(vector_index));
    fitfunc_1332.at(vector_index)->SetRange(fit_low_limit_1332.at(vector_index),fit_high_limit_1332.at(vector_index));
    
    TF1 * simple_gaus = new TF1("gaus","gaus",0,1);
    simple_gaus->SetRange(fit_low_limit_1173.at(vector_index),fit_high_limit_1173.at(vector_index));

    h1_germanium_uncal[active_channels_indexes.at(vector_index)]->Fit(simple_gaus,"QRN");
    fitfunc_1173.at(vector_index)->SetParLimits(0, simple_gaus->GetParameter(0)*0.5, simple_gaus->GetParameter(0));
    fitfunc_1173.at(vector_index)->SetParameter(0, simple_gaus->GetParameter(0));

    fitfunc_1173.at(vector_index)->SetParLimits(1,simple_gaus->GetParameter(1)*0.5, simple_gaus->GetParameter(1)*1.5);
    fitfunc_1173.at(vector_index)->SetParameter(1,simple_gaus->GetParameter(1));
    
    fitfunc_1173.at(vector_index)->SetParLimits(2,simple_gaus->GetParameter(2)*0.5, simple_gaus->GetParameter(2)*1.5);
    fitfunc_1173.at(vector_index)->SetParameter(2,simple_gaus->GetParameter(2));
    //
    if (fitfunctionname == "skewedgausbg"){
        double xmin = fit_low_limit_1173.at(vector_index);
        double ymin = h1_germanium_uncal[active_channels_indexes.at(vector_index)]->GetBinContent(h1_germanium_uncal[active_channels_indexes.at(vector_index)]->FindBin(xmin));
        double xmax = fit_high_limit_1173.at(vector_index);
        double ymax = h1_germanium_uncal[active_channels_indexes.at(vector_index)]->GetBinContent(h1_germanium_uncal[active_channels_indexes.at(vector_index)]->FindBin(xmax));

        double p1guess = (ymax - ymin) / (xmax - xmin);
        double p0guess = ymin - p1guess * xmin;


        fitfunc_1173.at(vector_index)->SetParameter(3, 0);
        fitfunc_1173.at(vector_index)->SetParLimits(3, 0, 10);
        fitfunc_1173.at(vector_index)->SetParameter(4, p0guess);
        fitfunc_1173.at(vector_index)->SetParameter(5, p1guess);
        

    }else if (fitfunctionname == "radwarefunc"){
        double xmin = fit_low_limit_1173.at(vector_index);
        double ymin = h1_germanium_uncal[active_channels_indexes.at(vector_index)]->GetBinContent(h1_germanium_uncal[active_channels_indexes.at(vector_index)]->FindBin(xmin));
        double xmax = fit_high_limit_1173.at(vector_index);
        double ymax = h1_germanium_uncal[active_channels_indexes.at(vector_index)]->GetBinContent(h1_germanium_uncal[active_channels_indexes.at(vector_index)]->FindBin(xmax));

        double p1guess = (ymax - ymin) / (xmax - xmin);
        double p0guess = ymin - p1guess * xmin;


        fitfunc_1173.at(vector_index)->SetParameter(3, 0); // area
        fitfunc_1173.at(vector_index)->SetParLimits(3, 0, 1e6);

        fitfunc_1173.at(vector_index)->SetParameter(4, 1e4); // beta
        fitfunc_1173.at(vector_index)->SetParLimits(4, 1, 1e6);

        fitfunc_1173.at(vector_index)->SetParameter(5, 0); // step
        fitfunc_1173.at(vector_index)->SetParLimits(5, 0, 1);

        fitfunc_1173.at(vector_index)->SetParameter(6, p0guess);
        fitfunc_1173.at(vector_index)->SetParameter(7, p1guess);
        

    }
    //
    h1_germanium_uncal[active_channels_indexes.at(vector_index)]->Fit(fitfunc_1173.at(vector_index),"QRM");
    
    
    simple_gaus->SetRange(fit_low_limit_1332.at(vector_index),fit_high_limit_1332.at(vector_index));
    h1_germanium_uncal[active_channels_indexes.at(vector_index)]->Fit(simple_gaus,"QRN");

    fitfunc_1332.at(vector_index)->SetParLimits(0, simple_gaus->GetParameter(0)*0.5, simple_gaus->GetParameter(0));
    fitfunc_1332.at(vector_index)->SetParameter(0, simple_gaus->GetParameter(0));

    fitfunc_1332.at(vector_index)->SetParLimits(1,simple_gaus->GetParameter(1)*0.5, simple_gaus->GetParameter(1)*1.5);
    fitfunc_1332.at(vector_index)->SetParameter(1,simple_gaus->GetParameter(1));
    
    fitfunc_1332.at(vector_index)->SetParLimits(2,simple_gaus->GetParameter(2)*0.5, simple_gaus->GetParameter(2)*1.5);
    fitfunc_1332.at(vector_index)->SetParameter(2,simple_gaus->GetParameter(2));

    if (fitfunctionname == "skewedgausbg"){
        double xmin = fit_low_limit_1332.at(vector_index);
        double ymin = h1_germanium_uncal[active_channels_indexes.at(vector_index)]->GetBinContent(h1_germanium_uncal[active_channels_indexes.at(vector_index)]->FindBin(xmin));
        double xmax = fit_high_limit_1332.at(vector_index);
        double ymax = h1_germanium_uncal[active_channels_indexes.at(vector_index)]->GetBinContent(h1_germanium_uncal[active_channels_indexes.at(vector_index)]->FindBin(xmax));

        double p1guess = (ymax - ymin) / (xmax - xmin);
        double p0guess = ymin - p1guess * xmin;


        fitfunc_1332.at(vector_index)->SetParameter(3, 0);
        fitfunc_1332.at(vector_index)->SetParLimits(3, 0, 10);
        fitfunc_1332.at(vector_index)->SetParameter(4, p0guess);
        fitfunc_1332.at(vector_index)->SetParameter(5, p1guess);
        

    }else if (fitfunctionname == "radwarefunc"){
        double xmin = fit_low_limit_1332.at(vector_index);
        double ymin = h1_germanium_uncal[active_channels_indexes.at(vector_index)]->GetBinContent(h1_germanium_uncal[active_channels_indexes.at(vector_index)]->FindBin(xmin));
        double xmax = fit_high_limit_1332.at(vector_index);
        double ymax = h1_germanium_uncal[active_channels_indexes.at(vector_index)]->GetBinContent(h1_germanium_uncal[active_channels_indexes.at(vector_index)]->FindBin(xmax));

        double p1guess = (ymax - ymin) / (xmax - xmin);
        double p0guess = ymin - p1guess * xmin;


        fitfunc_1332.at(vector_index)->SetParameter(3, 0); // area
        fitfunc_1332.at(vector_index)->SetParLimits(3, 0, 1e6);

        fitfunc_1332.at(vector_index)->SetParameter(4, 1e4); // beta
        fitfunc_1332.at(vector_index)->SetParLimits(4, 1, 1e6);

        fitfunc_1332.at(vector_index)->SetParameter(5, 0); // step
        fitfunc_1332.at(vector_index)->SetParLimits(5, 0, 1);

        fitfunc_1332.at(vector_index)->SetParameter(6, p0guess);
        fitfunc_1332.at(vector_index)->SetParameter(7, p1guess);
        

    }
    h1_germanium_uncal[active_channels_indexes.at(vector_index)]->Fit(fitfunc_1332.at(vector_index),"QRM+");


    gain_coeff.at(vector_index) = (1332 - 1173)/(fitfunc_1332.at(vector_index)->GetParameter(1) - fitfunc_1173.at(vector_index)->GetParameter(1));
    offset_coeff.at(vector_index) = 1332 - gain_coeff.at(vector_index)*fitfunc_1332.at(vector_index)->GetParameter(1);

    // FWHM:
    double fwhm_1173 = GetFWxM(fitfunc_1173.at(vector_index),0.5,fit_low_limit_1173.at(vector_index),fit_high_limit_1173.at(vector_index));
    double fwhm_1332 = GetFWxM(fitfunc_1332.at(vector_index),0.5,fit_low_limit_1332.at(vector_index),fit_high_limit_1332.at(vector_index));
    
    double fwtm_1173 = GetFWxM(fitfunc_1173.at(vector_index),0.1,fit_low_limit_1173.at(vector_index),fit_high_limit_1173.at(vector_index));
    double fwtm_1332 = GetFWxM(fitfunc_1332.at(vector_index),0.1,fit_low_limit_1332.at(vector_index),fit_high_limit_1332.at(vector_index));
    
    // FWTM:
    //double fwtm_1173 = GetFWxMHistogram(h1_germanium_uncal[active_channels_indexes.at(vector_index)], fitfunc_1173.at(vector_index),0.1,fit_low_limit_1173.at(vector_index),fit_high_limit_1173.at(vector_index));
    //double fwtm_1332 = GetFWxMHistogram(h1_germanium_uncal[active_channels_indexes.at(vector_index)], fitfunc_1332.at(vector_index),0.1,fit_low_limit_1332.at(vector_index),fit_high_limit_1332.at(vector_index));

    float time_elapsed = 0;
    if (test_running.at(vector_index)){
        time_elapsed =  std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - timers.at(vector_index)).count();

    }

    h1_germanium_uncal[active_channels_indexes.at(vector_index)]->SetTitle(Form("%f s, FWHM = %f, Ratio = %f \n FWHM = %f, Ratio = %f",time_elapsed,fwhm_1173*gain_coeff.at(vector_index), fwtm_1173/fwhm_1173,fwhm_1332*gain_coeff.at(vector_index), fwtm_1332/fwhm_1332));

}


void GermaniumLabTest::WriteTestResults(int vector_index) {
    TF1 *fit1173 = fitfunc_1173.at(vector_index);
    TF1 *fit1332 = fitfunc_1332.at(vector_index);

    // Get the HEX number (### part)
    std::string hex_number = std::to_string(eb_crystal_id.at(vector_index));
    std::string hex_folder_name = "HEX" + hex_number;

    // Assume the base path is defined as a string, e.g., base_path_str
    std::string folder_path = base_path_str + "/" + hex_folder_name; // Construct the full path

    // Get current time for timestamp
    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);

    // Format date and time for file name and file content
    std::ostringstream time_stream;
    time_stream << (now->tm_year + 1900) << '-' 
                << std::setfill('0') << std::setw(2) << (now->tm_mon + 1) << '-' 
                << std::setw(2) << now->tm_mday << '_'
                << std::setw(2) << now->tm_hour << '-' 
                << std::setw(2) << now->tm_min << '-' 
                << std::setw(2) << now->tm_sec;
    std::string timestamp = time_stream.str();

    // Build the file name (e.g., "HEX123_test_results_2024-10-16_12-30-45.txt")
    std::string file_base_name = "HEX" + hex_number + "_test_results_" + timestamp;
    std::string txt_file_name = file_base_name + ".txt";
    std::string root_file_name = file_base_name + ".root";

    // Full file path for text and root file
    std::string txt_file_path = folder_path + "/" + txt_file_name; // Concatenate folder path with file name
    std::string root_file_path = folder_path + "/" + root_file_name; // Same for ROOT file

    // Open the text file for writing
    std::ofstream outfile(txt_file_path);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file for writing: " << txt_file_path << std::endl;
        return; // Exit if file couldn't be opened
    }

    // Write the timestamp and test results to the text file
    outfile << "Test performed at: " << timestamp << std::endl;
    outfile << "******************************************" << std::endl;
    outfile << "            Result of test                " << std::endl;

    // Output the test details
    outfile << "HEX NR = " << eb_crystal_id.at(vector_index) << std::endl;
    outfile << "VOLTAGE = " << voltages.at(vector_index) << std::endl;
    outfile << "DEGAS DETECTOR NR = " << degas_detector_id.at(vector_index) << std::endl;
    outfile << "DEGAS CHANNEL NR = " << degas_detector_channel.at(vector_index) << std::endl;
    outfile << "FEBEX BOARD ID = " << board_ids.at(vector_index) << std::endl;
    outfile << "CHANNEL ID = " << ch_ids.at(vector_index) << std::endl;

    outfile << "            Measurement time = " << measurements_duration << " s " << std::endl;
    outfile << " Parameters for 1332 keV peak:            " << std::endl;
    outfile << " Total counts in the histogram: " << h1_germanium_uncal[active_channels_indexes.at(vector_index)]->GetIntegral() << std::endl;

    // Check if fit1332 is initialized
    if (fit1332) {
        outfile << " Parameters of fit: " << std::endl;
        outfile << " Chisquare = " << fit1332->GetChisquare() << "   Chisquare/Ndof = " << fit1332->GetChisquare() / fit1332->GetNpar() << " " << std::endl;
        for (int i = 0; i < fit1332->GetNpar(); i++) {
            outfile << "Parameter " << i << " (" << fit1332->GetParName(i) << "): "
                    << std::setw(10) << std::setprecision(6) 
                    << fit1332->GetParameter(i) 
                    << " ± " 
                    << fit1332->GetParError(i) 
                    << std::endl;
        }
    }

    double fwhm_1332 = GetFWxM(fit1332, 0.5, fit_low_limit_1332.at(vector_index), fit_high_limit_1332.at(vector_index)) * gain_coeff.at(vector_index);
    double fwtm_1332 = GetFWxM(fit1332, 0.1, fit_low_limit_1332.at(vector_index), fit_high_limit_1332.at(vector_index)) * gain_coeff.at(vector_index);

    outfile << "FWHM = " << fwhm_1332 << " keV   FWTM = " << fwtm_1332 << " keV, ratio = " << fwtm_1332/fwhm_1332 << std::endl;
    outfile << " ************************************  " << std::endl;

    // Parameters for 1173 keV peak
    outfile << " Parameters for 1173 keV peak:            " << std::endl;
    outfile << " Total counts in the histogram: " << h1_germanium_uncal[active_channels_indexes.at(vector_index)]->GetIntegral() << std::endl;

    // Check if fit1173 is initialized
    if (fit1173) {
        outfile << " Parameters of fit: " << std::endl;
        outfile << " Chisquare = " << fit1173->GetChisquare() << "   Chisquare/Ndof = " << fit1173->GetChisquare() / fit1173->GetNpar() << " " << std::endl;
        for (int i = 0; i < fit1173->GetNpar(); i++) {
            outfile << "Parameter " << i << " (" << fit1173->GetParName(i) << "): "
                    << std::setw(10) << std::setprecision(6) 
                    << fit1173->GetParameter(i) 
                    << " ± " 
                    << fit1173->GetParError(i) 
                    << std::endl;
        }
    }

    double fwhm_1173 = GetFWxM(fit1173, 0.5, fit_low_limit_1173.at(vector_index), fit_high_limit_1173.at(vector_index)) * gain_coeff.at(vector_index);
    double fwtm_1173 = GetFWxM(fit1173, 0.1, fit_low_limit_1173.at(vector_index), fit_high_limit_1173.at(vector_index)) * gain_coeff.at(vector_index);

    outfile << "FWHM = " << fwhm_1173 << " keV   FWTM = " << fwtm_1173 << " keV, ratio = " << fwtm_1173/fwhm_1173 << std::endl << std::endl;

    // Close the text file after writing
    outfile.close();

    // Save the histogram to a ROOT file
    TFile root_file(root_file_path.c_str(), "RECREATE");  // Open a ROOT file
    h1_germanium_uncal[active_channels_indexes.at(vector_index)]->Write();  // Write the histogram
    root_file.Close();  // Close the ROOT file
}


void GermaniumLabTest::StopMeasurementCompleted(int vector_index){

    FitPeak(vector_index);
    test_running.at(vector_index) = false;
    test_finished.at(vector_index) = true;

    WriteTestResults(vector_index);

    TF1 * fit1173 = fitfunc_1173.at(vector_index);
    TF1 * fit1332 = fitfunc_1332.at(vector_index);


    std::cout << "******************************************" << std::endl;
    std::cout << "            Result of test                " << std::endl;

    std::cout << "HEX NR = " << eb_crystal_id.at(vector_index) << std::endl;
    std::cout << "DEGAS DETECTOR NR = " << degas_detector_id.at(vector_index) << std::endl;
    std::cout << "DEGAS CHANNEL NR = " << degas_detector_channel.at(vector_index) << std::endl;
    std::cout << "FEBEX BOARD ID = " << board_ids.at(vector_index) << std::endl;
    std::cout << "CHANNEL ID = " << ch_ids.at(vector_index) << std::endl;

    std::cout << "            Measurement time = " << measurements_duration << " s " << std::endl;
    std::cout << " Parameters for 1332 keV peak:            " << std::endl;
    std::cout << " Total counts in the histogram: " << h1_germanium_uncal[active_channels_indexes.at(vector_index)]->GetIntegral() << std::endl;
    std::cout << " Parameters of fit: " << std::endl;
    std::cout << " Chisquare = " << fit1332->GetChisquare() << "   Chisquare/Ndof = " << fit1332->GetChisquare()/fit1332->GetNpar() << " " << std::endl;
    for (int i = 0; i < fit1332->GetNpar(); i++) {
    std::cout << "Parameter " << i << " (" << fit1332->GetParName(i) << "): "
                << std::setw(10) << std::setprecision(6) 
                << fit1332->GetParameter(i) 
                << " ± " 
                << fit1332->GetParError(i) 
                << std::endl;
    }
    
    double fwhm_1332 = GetFWxM(fit1332,0.5,fit_low_limit_1332.at(vector_index),fit_high_limit_1332.at(vector_index))*gain_coeff.at(vector_index);
    double fwtm_1332 = GetFWxM(fit1332,0.1,fit_low_limit_1332.at(vector_index),fit_high_limit_1332.at(vector_index))*gain_coeff.at(vector_index);
    

    std::cout << "FWHM = " << fwhm_1332 << " keV   FWTM = " << fwtm_1332 << " keV, ratio = " << fwtm_1332/fwhm_1332 << std::endl;
    std::cout << " ************************************  " << std::endl;
    std::cout << " Parameters for 1173 keV peak:            " << std::endl;
    std::cout << " Total counts in the histogram: " << h1_germanium_uncal[active_channels_indexes.at(vector_index)]->GetIntegral() << std::endl;
    std::cout << " Parameters of fit: " << std::endl;
    std::cout << " Chisquare = " << fit1173->GetChisquare() << "   Chisquare/Ndof = " << fit1173->GetChisquare()/fit1173->GetNpar() << " " << std::endl;
    for (int i = 0; i < fit1173->GetNpar(); i++) {
    std::cout << "Parameter " << i << " (" << fit1173->GetParName(i) << "): "
                << std::setw(10) << std::setprecision(6) 
                << fit1173->GetParameter(i) 
                << " ± " 
                << fit1173->GetParError(i) 
                << std::endl;
    }
    // FWTM:

    double fwhm_1173 = GetFWxM(fit1173,0.5,fit_low_limit_1173.at(vector_index),fit_high_limit_1173.at(vector_index))*gain_coeff.at(vector_index);
    double fwtm_1173 = GetFWxM(fit1173,0.1,fit_low_limit_1173.at(vector_index),fit_high_limit_1173.at(vector_index))*gain_coeff.at(vector_index);
    

    std::cout << "FWHM = " << fwhm_1173 << " keV   FWTM = " << fwtm_1173 << " keV, ratio = " << fwtm_1173/fwhm_1173 << std::endl << std::endl;

}


void GermaniumLabTest::FinishEvent()
{


    for (int vector_index = 0; vector_index<active_channels_indexes.size(); vector_index++){
        float time_elapsed = 0;
        if (test_running.at(vector_index)){
            time_elapsed =  std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - timers.at(vector_index)).count();
        }

        if (time_elapsed > measurements_duration){
            StopMeasurementCompleted(vector_index);
        }
        if (fNEvents % 1000 == 0){

        if (h1_germanium_uncal[active_channels_indexes.at(vector_index)] && fit_low_limit_1173.at(vector_index) > 0 && fit_high_limit_1173.at(vector_index) > 0 && fit_low_limit_1332.at(vector_index) > 0 && fit_high_limit_1332.at(vector_index) > 0){
            
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
