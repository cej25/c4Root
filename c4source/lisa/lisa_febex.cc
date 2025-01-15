//
//last updated@03 Aug,2024
//Z.Chen
//
//Error_febex_cc_xxx.
//
//01 Jul; debug MWD algorism
//17 Jlu: add findKink(); add new TBranch
//25 Jul: change the way to set resutls to fCorrTrace_and fMWDTrace_
//febex_data_temp.fCorrTrace_x = getCorrectTraceI();//return a vector
//27 Jul: update error info
//03 Aug: add openMP
//
//

#include "../inc/lisa_febex.hh"

#include <vector>
#include <iostream>
#include "TGraph.h"
#include "TTree.h"
#include "TFile.h"
#include "TStopwatch.h"
#include "TRandom3.h"
#include <functional>
#include <numeric>
// for openMP //
#include <omp.h>
#include <TMath.h>
#include <time.h>
#include <chrono>
#include <algorithm>

lisa_febex::lisa_febex()
{
	std::cout << "lisa_febex::lisa_febex()" << std::endl;
}

lisa_febex::lisa_febex(TTree *tree)
{
	if(tree == NULL){
		std::cout << "[ERROR INFO] Error_febex_cc_000:lisa_febex::lisa_febex(tree==0)" << std::endl;
		return;
	}

	//fucesb->Init(tree);
	//loadSettings(settings);

	Init(tree);//from lisa_ucesb
	setTree(tree);//deliver tree to ftree

}

lisa_febex::~lisa_febex()
{
	std::cout << "lisa_febex::~lisa_febex()" << std::endl;
}

/*
   void lisa_febex::loadSettings(lisa_settings *settings){
   if(settings == NULL){
   std::cout << "***Error_febex_cc_001:lisa_febex::loadSettings(settings==0)" << std::endl;
   return;
   }
   lisa_settings::setVerbose(settings->getVerbose());
   setFebexCh(settings->getFebexCh());
   setJentry(settings->getJentry());
   setLength(settings->getFebexTraceL());
   setMWDEnergyCalcWindow( settings->getTrapezAmplitudeCalcWindow() );

   std::cout<<"***lisa_febex::loadSettings()***"<<std::endl;
   }
   */

void lisa_febex::loadSingleTrace(TTree *tree)
{
	if(lisa_settings::getVerbose() == 3)std::cout << "lisa_febex::loadSingleTrace()" << std::endl;

	if (tree == NULL) {
		std::cout << "[ERROR INFO] Error_febex_cc_001:lisa_febex::loadSingleTrace(tree==0)" << std::endl;
		return;
	}
	if(lisa_settings::getVerbose() == 1){
		std::cout<<"*** jentry = "<<getJentry()<<std::endl;
		std::cout<<"*** febex channel = "<<getFebexCh()<<std::endl;
	}
	//debug
	//tree->Draw("lisa_data1traces1v:lisa_data1traces1I");
	//return;

	std::vector<double>yy;//amplitude
	std::vector<double>xx;//sample
	yy.clear();
	xx.clear();

	tree->GetEntry(getJentry());

	std::vector<UInt_t>len;//vector for trace length;directly read from unpacked data
	std::vector<UInt_t*>lisa_data_v;//vector for pointers
	std::vector<UInt_t*>lisa_data_I;
	len.clear();//length
	lisa_data_v.clear();
	lisa_data_I.clear();
	//*** for ucesb ***//
	len.push_back(lisa_data1traces1);
	len.push_back(lisa_data1traces2);
	len.push_back(lisa_data1traces3);
	len.push_back(lisa_data1traces4);
	len.push_back(lisa_data1traces5);
	len.push_back(lisa_data1traces6);
	len.push_back(lisa_data1traces7);
	len.push_back(lisa_data1traces8);
	len.push_back(lisa_data1traces9);
	len.push_back(lisa_data1traces10);
	len.push_back(lisa_data1traces11);
	len.push_back(lisa_data1traces12);
	len.push_back(lisa_data1traces13);
	len.push_back(lisa_data1traces14);
	len.push_back(lisa_data1traces15);
	len.push_back(lisa_data1traces16);

	lisa_data_v.push_back(lisa_data1traces1v);
	lisa_data_v.push_back(lisa_data1traces2v);
	lisa_data_v.push_back(lisa_data1traces3v);
	lisa_data_v.push_back(lisa_data1traces4v);
	lisa_data_v.push_back(lisa_data1traces5v);
	lisa_data_v.push_back(lisa_data1traces6v);
	lisa_data_v.push_back(lisa_data1traces7v);
	lisa_data_v.push_back(lisa_data1traces8v);
	lisa_data_v.push_back(lisa_data1traces9v);
	lisa_data_v.push_back(lisa_data1traces10v);
	lisa_data_v.push_back(lisa_data1traces11v);
	lisa_data_v.push_back(lisa_data1traces12v);
	lisa_data_v.push_back(lisa_data1traces13v);
	lisa_data_v.push_back(lisa_data1traces14v);
	lisa_data_v.push_back(lisa_data1traces15v);
	lisa_data_v.push_back(lisa_data1traces16v);

	lisa_data_I.push_back(lisa_data1traces1I);
	lisa_data_I.push_back(lisa_data1traces2I);
	lisa_data_I.push_back(lisa_data1traces3I);
	lisa_data_I.push_back(lisa_data1traces4I);
	lisa_data_I.push_back(lisa_data1traces5I);
	lisa_data_I.push_back(lisa_data1traces6I);
	lisa_data_I.push_back(lisa_data1traces7I);
	lisa_data_I.push_back(lisa_data1traces8I);
	lisa_data_I.push_back(lisa_data1traces9I);
	lisa_data_I.push_back(lisa_data1traces10I);
	lisa_data_I.push_back(lisa_data1traces11I);
	lisa_data_I.push_back(lisa_data1traces12I);
	lisa_data_I.push_back(lisa_data1traces13I);
	lisa_data_I.push_back(lisa_data1traces14I);
	lisa_data_I.push_back(lisa_data1traces15I);
	lisa_data_I.push_back(lisa_data1traces16I);

	setTrigger(TRIGGER);
	setEvtNo(EVENTNO);
	//setFebexTraceL(len[getFebexCh()]);
	setRawTraceLength(len[getFebexCh()]);
	UInt_t flength_raw = getRawTraceLength();//defined in lisa_febex.hh
	UInt_t flength_set = lisa_settings::loadFebexTraceL();//defined in lisa_settings.hh

	//debug//
	if(lisa_settings::getVerbose() == 1){
		std::cout<<"***raw febex trace length = "<<flength_raw<<std::endl;
		std::cout<<"***febex trace length from setting file= "<<flength_set<<std::endl;
		for(int ii=0;ii<16;ii++)std::cout<<"***febex channel = "<<ii<<"   length(lisa_febex) = "<<len[ii]<<std::endl;
	}

	if(flength_raw == 0){
		std::cout<<"[ERROR INFO] Error_febex_cc_002: getRawTraceLength() == 0 in loadSingleTrace(); febex channel = "<<getFebexCh()<<" "<<std::endl;
		std::cout<<"[ERROR INFO] jentry = "<<getJentry()<<std::endl;
		return;
	}
	UInt_t *p_v = lisa_data_v[getFebexCh()];//y axis
	UInt_t *p_I = lisa_data_I[getFebexCh()];//x axis
	std::vector<Int_t> fraw_v;
	std::vector<Int_t> fraw_I;
	fraw_v.clear();
	fraw_I.clear();
	for(UInt_t ii=0;ii<flength_set;ii++){
		fraw_v.push_back(p_v[ii]);
		fraw_I.push_back(p_I[ii]);
	}
	setRawTraceV(fraw_v);
	setRawTraceI(fraw_I);
	//setRawTraceV(p_v);
	//setRawTraceI(p_I);

	if(lisa_settings::getVerbose() == 3)std::cout << "lisa_febex::loadSingleTrace()_end" << std::endl;
}
//***baseline correction and time correction***//
void lisa_febex::calcCorrectTrace()
{
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcCorrectTrace()***"<<std::endl;
	if(getRawTraceLength() == 0){
		setCorrTraceLength(0);
		std::cout << "[ERROR INFO] Error_febex_cc_003: getRawTraceLength() == 0 in calcCorrectTrace()"<<std::endl;
		std::cout << "[ERROR INFO] Please check if you have loaded raw traces."<<std::endl;
		return;
	}
	if(getCorrectTraceV().size() != 0){
		if(lisa_settings::getVerbose() == 3)std::cout<<"--->Trace is already corrected.***"<<std::endl;
		if(lisa_settings::getVerbose() == 3)std::cout<<"--->Skip this step."<<std::endl;
		return;
	}
	if(lisa_settings::getVerbose() == 1)std::cout<<"***lisa_febex::calcCorrectTrace()***"<<std::endl;
	if(lisa_settings::getVerbose() == 1)std::cout<<"***febex trace length from setting file = "<<lisa_settings::loadFebexTraceL()<<std::endl;
	std::vector<Int_t>fxx = getRawTraceI();
	std::vector<Int_t>fyy = getRawTraceV();
	std::vector<Double_t> fxx_w;
	std::vector<Double_t> fyy_w;
	fxx_w.clear();
	fyy_w.clear();
	Double_t fshift = 0;
	for(int ii=20;ii<100;ii++){
		fshift += fyy[ii];
		//***debug***//
		//std::cout<<"fyy[ii]"<<fyy[ii]<<std::endl;
		//std::cout<<"fshift"<<fshift<<std::endl;
	}
	fshift = fshift/80.0;
	//***debug***//
	//std::cout<<"***fshift***"<<fshift<<std::endl;
	for(int ii=0;ii<lisa_settings::loadFebexTraceL();ii++){
		//fyy_w[ii] = fyy[ii]-fshift;
		Double_t fyytem = fyy[ii]-fshift;
		fyytem = fyytem*1000.0/8000.0;//8000 from Febex corresponds to 1000mV;attention, fyy is Int_t
		fyy_w.push_back(fyytem);
		//fyy[ii] = fyy[ii]*1000/8000;//8000 from Febex corresponds to 1000mV;attention, fyy is Int_t
		//***debug***//
		//fxx_w[ii] = fxx[ii]*MHZ2NS/getSampleRate();//[ns]
		Double_t fxxtem = fxx[ii];
		fxxtem = fxxtem*MHZ2NS/getSampleRate();//[ns]
		fxx_w.push_back(fxxtem);
		//fxx[ii] = fxx[ii]*MHZ2NS/getSampleRate();//[ns]

		//***debug***//
		//if(ii<20){
		//	std::cout<<"in calcCorrectTrace(): ii = "<<ii<<" "<<"fyy_w[ii]"<<fyy_w[ii]<<std::endl;
		//	std::cout<<"in calcCorrectTrace(): ii = "<<ii<<" "<<"fxx_w[ii]"<<fxx_w[ii]<<std::endl;
		//}
	}
	setCorrectTraceV(fyy_w);
	setCorrectTraceI(fxx_w);
	setCorrTraceLength(fyy_w.size());

	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcCorrectTrace()_end***"<<std::endl;
}

//https://doi.org/10.1016/j.apradiso.2020.109171
//B.J.Kim
void lisa_febex::calcMWDTrace()
{
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcMWDTrace()***"<<std::endl;

	if(getCorrectTraceV().size() == 0){
		setMWDTraceLength(0);
		std::cout << "[ERROR INFO] Error_febex_cc_004: getRawTraceV() == NULL in calcMWDTrace()"<<std::endl;
		return;
	}
	if(getIsCalcDMi() * getIsCalcMWDi() != 0){
		std::cout<<"[ERROR INFO] Error_febex_cc_005: You can not enable DM(i) and MWD(i) at the same time in calcMWDTrace()"<<std::endl;
		return;
	}

	std::vector<Double_t> fcorr_x = getCorrectTraceI();
	std::vector<Double_t> fcorr_y = getCorrectTraceV();
	std::vector<Double_t> fxx_mwd;
	std::vector<Double_t> fyy_mwd;
	fxx_mwd.clear();
	fyy_mwd.clear();
	for(UInt_t ii=0;ii<fcorr_x.size();ii++){
		//if(fcorr_x[ii] > 2500 && fcorr_x[ii] < 2700)continue;
		fxx_mwd.push_back(fcorr_x[ii]);//
		fyy_mwd.push_back(fcorr_y[ii]);//
	}

	//std::cout<<"fcorr_x.size() = "<<fcorr_x.size()<<std::endl;
	//std::cout<<"fxx_mwd.size() = "<<fxx_mwd.size()<<std::endl;
	//std::vector<Double_t> fxx_mwd = getCorrectTraceI();
	//std::vector<Double_t> fyy_mwd = getCorrectTraceV();

	std::vector<Double_t> MWD;
	std::vector<Double_t> MWDx;
	MWD.clear();
	MWDx.clear();

	//debug//
	if(lisa_settings::getVerbose() == 1){
		for(int ii=0;ii<16;ii++)std::cout<<"decaytime = "<<getDecayTime()[ii]<<std::endl;
		std::cout<<"risingtime = "<<getRisingTime()<<std::endl;
		std::cout<<"sample rate = "<<getSampleRate()<<std::endl;
		std::cout<<"trapez moving window length = "<<getTrapezMovingWindowLength()<<std::endl;
	}

	Int_t k0,kend,MM,LL;
	//Double_t tau = getDecayTime()*getSampleRate()/MHZ2NS;//[sample points]
	Double_t tau = getDecayTime()[ lisa_settings::getFebexCh() ]*getSampleRate()/MHZ2NS;//[sample points]
	Double_t mwd=0;
	Double_t mwdx=0;

	//********************//
	//---            -----//
	//  a-          -d    //
	//    -        -      //
	//     -      -       //
	//     b------c       //
	//********************//

	MM=(Int_t)getTrapezMovingWindowLength()*getSampleRate()/MHZ2NS;//length from b to d; [sample point]
	LL=(Int_t)getRisingTime()*getSampleRate()/MHZ2NS;//length from a to b; [sample point]

	//flat on top/bottom: MM-LL; [sample point]
	k0=getTrapezSampleWindow()[0]*getSampleRate()/MHZ2NS;//[sample point]
	kend=getTrapezSampleWindow()[1]*getSampleRate()/MHZ2NS;//[sample point]

	//***debug***//
	if(lisa_settings::getVerbose() == 1){
		std::cout<<"tau = "<<tau<<std::endl;
		std::cout<<"MM = "<<MM<<std::endl;
		std::cout<<"LL = "<<LL<<std::endl;
		std::cout<<"k0 = "<<k0<<std::endl;
		std::cout<<"kend = "<<kend<<std::endl;
	}
	//int cnt=0;//for debug
	//int cnt1=0;//for debug

	auto start_single = std::chrono::high_resolution_clock::now();
	if(lisa_settings::getVerbose() == 4){
		std::cout<<"start stopwatch"<<std::endl;
		std::cout<<"k0 = "<<k0<<std::endl;
		std::cout<<"kend = "<<kend<<std::endl;
		std::cout<<"threads = "<<lisa_settings::getThreads()<<std::endl;
	}
	//...oooOO0OOooo......oooOO0OOooo......oooOO0OOooo...//
	//MWDtrace
	int threads = lisa_settings::getThreads();
	int xInterval = (kend-k0)/(int)threads;
	if(lisa_settings::getVerbose() == 4)std::cout<<"set threads"<<std::endl;
	std::vector<Double_t> MWD_private;
	std::vector<Double_t> MWDx_private;
#pragma omp parallel for private(MWD_private, MWDx_private)
	for(int i=0;i<threads;i++){
		MWD_private.clear();
		MWDx_private.clear();
		int x_from_val = i * xInterval+k0;
		int x_to_val = (i + 1) * xInterval+k0;
		if(kend - x_to_val < 10)x_to_val = kend;
#pragma omp critical
		{
			if(lisa_settings::getVerbose() == 4)std::cout<<"x from "<<x_from_val<<" x to "<<x_to_val<<std::endl;
		}
		while(x_from_val < x_to_val){
			if(getIsCalcDMi()){
				mwd = calcD_M(x_from_val,MM,tau,fyy_mwd);
				mwdx = fxx_mwd[x_from_val];
				x_from_val++;
			}else if(getIsCalcMWDi()){
				mwd = calcMWD(x_from_val,MM,tau,fyy_mwd,LL);
				mwdx = fxx_mwd[x_from_val];
				x_from_val++;
			}else{
				std::cout<<"[ERROR INFO] Error_febex_cc_006: Please set calcDMi or calcMWDi in lisa_febex::calcMWDTrace()"<<std::endl;
				//return;
			}
			//mwdx = fxx_mwd[x_from_val];
			//if (std::find(MWDx_private.begin(), MWDx_private.end(), mwdx) == MWDx_private.end()) {
			MWD_private.push_back(mwd);
			MWDx_private.push_back(mwdx);
			//}

			//#pragma omp critical
			//{
			//	if (std::find(MWDx.begin(), MWDx.end(), mwdx) == MWDx.end()) {
			//		MWD.push_back(mwd);
			//		MWDx.push_back(mwdx);
			//	}
			//x_from_val++;
			//}
		}//end of while

#pragma omp critical
		{
			MWD.insert(MWD.end(), MWD_private.begin(), MWD_private.end());
			MWDx.insert(MWDx.end(), MWDx_private.begin(), MWDx_private.end());
		}
	}//end of for; x_from=k0
	 //...oooOO0OOooo......oooOO0OOooo......oooOO0OOooo...//

	auto end_single = std::chrono::high_resolution_clock::now();
	if(lisa_settings::getVerbose() == 4){
		std::chrono::duration<double> elapsed_single = end_single - start_single;
		std::cout <<"[Print INFO] Execution time to calculate MWD: " << elapsed_single.count() << " seconds"<<std::endl;
	}
	std::vector<Double_t> p_v = MWD;//y axis
	std::vector<Double_t> p_I = MWDx;//x axis
	Int_t MWDsize = MWD.size();

	//****debug***//
	if(lisa_settings::getVerbose() == 1){
		for(int ii = 0;ii < 5;ii++){
			std::cout<<"p_I = "<<p_I[ii]<<std::endl;
			std::cout<<"p_v = "<<p_v[ii]<<std::endl;
		}
		std::cout<<"***MWD.size() = "<<MWDsize<<std::endl;
	}

	setMWDTraceLength(MWDsize);
	setMWDTraceV(p_v);//
	setMWDTraceI(p_I);//
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcMWDTrace()_end***"<<std::endl;

	//*** debug ***//
	//to check if we have e-310
	//6.xxe-310, initialization issue
	//this could come up when converting from int to double
	//Double_t *p_I2 = (Double_t*)getMWDTraceI();
	//Double_t *p_v2 = (Double_t*)getMWDTraceV();
	//for(int ii = 0;ii < 5;ii++){
	//    std::cout<<"p_I2 = "<<p_I2[ii]<<std::endl;
	//    std::cout<<"p_v2 = "<<p_v2[ii]<<std::endl;
	//}

	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcMWDTrace()_end***"<<std::endl;
}//end of calcMWDTrace

void lisa_febex::findKink()
{
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::findKink()***"<<std::endl;
	// Calculate slopes between points
	std::vector<double> slopes;
	std::vector<Double_t> x = getMWDTraceI();
	std::vector<Double_t> y = getMWDTraceV();
	for (UInt_t i = 1; i < x.size(); ++i) {
		double dx = x[i] - x[i - 1];
		double dy = y[i] - y[i - 1];
		if(dx == 0)continue;
		slopes.push_back(dy / dx);
	}

	// Set a threshold for detecting kinks
	double threshold = -0.8;  // Adjust this value based on your data

	// Identify the kinks
	std::vector<Int_t> kinkIndices;
	for (UInt_t i = 1; i < slopes.size(); ++i) {
		//double slopeChange = std::abs(slopes[i] - slopes[i - 1]);
		double slopeChange = slopes[i] - slopes[i - 1];
		//if(abs(slopeChange)>0.5)std::cout<<"slopeChange = "<<slopeChange<<std::endl;
		if (slopeChange < threshold) {
			kinkIndices.push_back(i);
		}
	}

	// Output the kink locations
	//std::cout << "Kinks detected at:" << std::endl;
	//for (Int_t index : kinkIndices) {
	//	std::cout << "x = " << x[index] << std::endl;
	//}
	setKink(kinkIndices);
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::findKink()_end***"<<std::endl;
}

Double_t lisa_febex::calcD_M(Int_t index_i, Int_t par_M, Double_t par_tau,std::vector<Double_t> &data_x)
{
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcD_M()***"<<std::endl;
	Double_t sum0=0;
	Double_t DM=0;
	for(int i=index_i - par_M; i<=index_i-1;i++){
		if(i<10){
			std::cout<<"*index_i-par_M = "<<i<<std::endl;
			std::cout<<"[ERROR INFO] Error_febex_cc_007: Please decrease your Trapezoidal moving window length OR shift the start point of sample window to the right."<<std::endl;
			return 0;
		}
		//std::cout<<"data_x[i] ="<<data_x[i]<<std::endl;
		//std::cout<<"new sum0 ="<<sum0<<std::endl;
		sum0 += data_x[i];
	}
	DM = data_x[index_i] - data_x[index_i-par_M] + 1.0*sum0/par_tau;
	//*** for undershoot detection ***//
	/*
	if(DM<lisa_settings::getUndershootThresh()){
		std::cout<<"[WARNING INFO] Undershoot discovered. DM = "<<DM<<" index_i = "<<index_i<<" index_i-par_M = "<<index_i-par_M<<" par_tau = "<<par_tau<<std::endl;
	}
	*/
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcD_M()_end***"<<std::endl;
	return DM;
}

Double_t lisa_febex::calcMWD(Int_t index_i, Int_t par_M, Double_t par_tau,std::vector<Double_t> &data_x, Int_t par_L)
{
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcMWD()***"<<std::endl;
	//std::cout<<"index_i = "<<index_i<<" par_M = "<<par_M<<" par_tau = "<<par_tau<<" par_L = "<<par_L<<std::endl;
	Double_t MWD=0;
	Double_t DM=0;
	//Int_t cnt1=0;
	for(int j=index_i-par_L;j<=index_i-1;j++){
		if(j<10){
			std::cout<<"[ERROR INFO] Error_febex_cc_008: Please decrease your rising time OR shift the start point of sample window to the right."<<std::endl;
			return 0;
		}
		DM += calcD_M(j,par_M,par_tau,data_x);
		//if(cnt1<20){
		//	std::cout<<"j: "<<j<<" cnt1 = "<<cnt1<<" new DM = "<<DM<<std::endl;
		//	cnt1++;
		//}
	}
	MWD = 1.0*DM/par_L;
	//std::cout<<"new MWD = "<<MWD<<std::endl;
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcMWD()_end***"<<std::endl;
	return MWD;
}

//using CFD to determine time;
//NIMA 58(2):253(1968)
//delay ~ 1/4 * total trace width
//fraction ~ 0.9
void lisa_febex::calcCFDTrace()
{
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcCFDTrace()***"<<std::endl;
	if(getCorrectTraceV().size() == 0){
		setCFDTraceLength(0);
		std::cout << "[ERROR INFO] Error_febex_cc_009: getCorrectTraceV() == NULL in calcCFDTrace()"<<std::endl;
		return;
	}
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcCFDTrace()***"<<std::endl;
	Int_t length = lisa_settings::loadFebexTraceL();
	//std::cout<<"length = "<<length<<std::endl;
	//***debug***//
	if(lisa_settings::getVerbose() == 1){
		std::cout<<"delay = "<<getCFDdelay()<<std::endl;
		std::cout<<"fraction = "<<getCFDfraction()<<std::endl;
		std::cout<<"CFDWindow = "<<getCFDWindow()[0]<<"  "<<getCFDWindow()[1]<<std::endl;
	}
	std::vector<Double_t> fxx_cfd = getCorrectTraceI();
	std::vector<Double_t> fyy_cfd = getCorrectTraceV();
	if(lisa_settings::getVerbose() == 1){
		for(int jj=0;jj<length;jj++)if(jj>length/2. && jj<length/2.+10)std::cout<<"**fxx_cfd[jj] = "<<fxx_cfd[jj]<<"  fyy_cfd[jj]"<<fyy_cfd[jj]<<std::endl;
	}
	std::vector<double>xx;
	std::vector<double>yy;
	std::vector<double>yyf;//with fraction
	std::vector<Double_t>xxd;//with delay; for CFD graph
	std::vector<Double_t>yyCFD;//after CFD; for CFD graph
							   //int cnt=0;
	xx.clear();
	yy.clear();
	yyf.clear();
	xxd.clear();
	yyCFD.clear();
	for(int i=0;i<length;i++){
		//double x,y;
		xx.push_back(fxx_cfd[i]);
		yy.push_back(fyy_cfd[i]*(-1.0));//inverted
		yyf.push_back(fyy_cfd[i]*getCFDfraction());//fraction
		xxd.push_back(fxx_cfd[i]+getCFDdelay());//delay[ns]
	}
	TGraph *ftem1 = new TGraph(xx.size(),&xx[0],&yyf[0]);
	for(int i=0;i<length;i++){
		double ytem=0;
		ytem = ftem1->Eval(xxd[i]);
		yyCFD.push_back(ytem+yy[i]);
	}
	//***debug***//
	//ftem1->Draw("AP*");
	//calculate zero
	double ymax_y,ymax_x,ymin_y,ymin_x;
	ymax_y = ymin_y = 0;
	ymax_x = ymin_x = -9999;
	double fx1,fx2;
	fx1 = fx2 = -9999;
	for(int i=0;i<length;i++){
		if(xxd[i]>getCFDWindow()[0] && xxd[i]<getCFDWindow()[1]){//CFD window[ns]
			if(yyCFD[i]>ymax_y){
				ymax_y = yyCFD[i];
				ymax_x = xxd[i];
			}
			if(yyCFD[i]<ymin_y){
				ymin_y = yyCFD[i];
				ymin_x = xxd[i];
			}
		}
	}
	fx1 = ymax_x;
	fx2 = ymin_x;
	//swap
	if(fx2<fx1){
		double tem = fx1;
		fx1 = fx2;
		fx2 = tem;
	}
	std::vector<Double_t>xxz;//to calculate zero
	std::vector<Double_t>yyz;//to calculate zero
	xxz.clear();
	yyz.clear();
	if(lisa_settings::getVerbose() == 1)std::cout<<"fx1 = "<<fx1<<" fx2 = "<<fx2<<std::endl;
	for(int i=0;i<length;i++){
		if(xxd[i]>fx1 && xxd[i]<fx2){
			xxz.push_back(yyCFD[i]);
			yyz.push_back(xxd[i]);//int time related to the sample rate;
		}
	}
	TGraph *ftem3 = new TGraph(xxz.size(),&xxz[0],&yyz[0]);
	Double_t ftiming = ftem3->Eval(0,0)+gRandom->Uniform(-5,5);//use spline interpolation to get the "0" point;Double_t time

	if(lisa_settings::getVerbose() == 1)std::cout<<"xxd.size() = "<<xxd.size()<<std::endl;
	if(xxd.size() == 0){
		std::cout<<"[ERROR INFO ] Error_febex_cc_010. xxd.size() == 0."<<std::endl;
		return;
	}

	//***debug***//
	if(lisa_settings::getVerbose() == 1){
		for(UInt_t ii=0;ii<xxd.size();ii++){
			if(ii>xxd.size()/2. && ii<xxd.size()/2.+10)std::cout<<"xxd[ii]="<<xxd[ii]<<"   yyCFD[ii]="<<yyCFD[ii]<<std::endl;
		}
	}
	setCFDtime(ftiming);
	setCFDTraceV(yyCFD);
	setCFDTraceI(xxd);
	setCFDTraceLength(xxd.size());
	if(lisa_settings::getVerbose() == 2)std::cout<<"zero point @ "<<ftiming<<" ns."<<std::endl;
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::getCFDTrace()***"<<std::endl;
}

//calc energy via assigned range //
void lisa_febex::calcEnergyInRange()
{
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcEnergyInRange()***"<<std::endl;
	if(getMWDTraceV().size() == 0){
		std::cout << "[ERROR INFO] Error_febex_cc_011: getMWDTraceV().size() == 0 in calcEnergy()"<<std::endl;
		return;
	}
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcEnergy()***"<<std::endl;

	std::vector<Double_t> fxx_energy = getMWDTraceI();
	std::vector<Double_t> fyy_energy = getMWDTraceV();
	Int_t length = getMWDTraceLength();
	Int_t *fRange = getTrapezAmplitudeCalcWindow();//fRange[0],[1]

	//double ytem=0;
	int cnt=0;
	double fsum=0;
	for(int i=0;i<length;i++){
		if( fRange == NULL || fRange[0] > fRange[1]){
			std::cout<<"[ERROR INFO] Error_febex_cc_012. Please check trapez amp calc window."<<std::endl;
			return;
		}
		if( fxx_energy[i]>fRange[0] && fxx_energy[i]<fRange[1] ){//ns
			fsum+=fyy_energy[i];
			cnt++;
		}
	}
	if(lisa_settings::getVerbose() == 2)std::cout<<"***average amplitude = "<<fsum/cnt<<std::endl;

	std::vector<Double_t> fenergy_v;
	Double_t fenergy_tem = fsum/cnt;
	if(fenergy_tem<0)fenergy_tem = (-1)*fenergy_tem;
	fenergy_v.push_back(fenergy_tem);
	setMWDenergy(fenergy_v);
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcEnergy()***"<<std::endl;
}

// calc energy via kinks //
void lisa_febex::calcEnergy()
{
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcEnergy()***"<<std::endl;
	//std::cout<<"calcEnergy"<<std::endl;
	if(getMWDTraceV().size() == 0){
		std::cout << "[ERROR INFO] Error_febex_cc_013: getMWDTraceV().size() == 0 in calcEnergy()"<<std::endl;
		return;
	}
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcEnergy()***"<<std::endl;

	std::vector<Double_t> fxx_energy = getMWDTraceI();
	std::vector<Double_t> fyy_energy = getMWDTraceV();
	Int_t length = getMWDTraceLength();
	//Int_t *fRange = getTrapezAmplitudeCalcWindow();//fRange[0],[1]
	std::vector<Int_t> kink = getKink();
	//for(int jj=0;jj<kink.size();jj++)std::cout<<"kink = "<<kink[jj]<<std::endl;
	//if(kink.size()%2==0 && kink.size()>0){//even
	//	std::cout<<"N pileup found = "<<kink.size()/2<<std::endl;
	//}

	//double ytem=0;
	int cnt[10];
	double fsum[10];
	for(int i=0;i<10;i++)cnt[i]=0;
	for(int i=0;i<10;i++)fsum[i]=0;

	for(int i=0;i<length;i++){
		//if( fRange == NULL || fRange[0] > fRange[1]){
		//	if(lisa_settings::getVerbose() == 3)std::cout<<"Error_febex_cc_009. Please check trapez amp calc window."<<std::endl;
		//	return;
		//}
		for(UInt_t jj=0;jj<kink.size()/2;jj++){
			if( fxx_energy[i]>fxx_energy[ kink[jj*2]+2 ] && fxx_energy[i]< fxx_energy[ kink[jj*2+1]-2] ){//ns
																										 //std::cout<<"current range: "<<fxx_energy[ kink[jj]+10]<<"  "<<fxx_energy[kink[jj+1]-10 ]<<std::endl;
																										 //if( fxx_energy[i]>fRange[jj] && fxx_energy[i]<fRange[jj+1] )//ns
				fsum[jj]+=fyy_energy[i];
				cnt[jj]++;
			}
		}
	}
	//if(lisa_settings::getVerbose() == 2)std::cout<<"***average amplitude = "<<fsum/cnt<<std::endl;

	std::vector<Double_t> fenergy_v;
	Double_t fenergy_tem;
	for(UInt_t jj=0;jj<kink.size()/2;jj++){
		//std::cout<<""<<jj<<" sum "<<fsum[jj]<<std::endl;
		//std::cout<<"calc energy: "<<jj<<" "<<fsum[jj]/cnt[jj]<<std::endl;
		fenergy_tem = fsum[jj]/cnt[jj];
		if(fenergy_tem<0)fenergy_tem = (-1)*fenergy_tem;
		fenergy_v.push_back( fenergy_tem );
	}
	setMWDenergy(fenergy_v);
	if(lisa_settings::getVerbose() == 3)std::cout<<"***lisa_febex::calcEnergy()***"<<std::endl;
}

void lisa_febex::getTraces(TTree *tree)
{
	std::cout<<"[Print INFO] *** lisa_febex::getTraces() ***"<<std::endl;
	if(tree == NULL){
		std::cout << "[ERROR INFO] Error_febex_cc_014: tree == NULL in getTraces()"<<std::endl;
		return;
	}
	ULong64_t fnentries = tree->GetEntriesFast();

	TStopwatch timer;
	TStopwatch timer2;//start before the loop; to calculate total running time
	std::vector<Double_t>v_averageSpeed;
	v_averageSpeed.clear();

	//save data to febex_data
	febex_data febex_data_temp;
	std::vector<febex_data> v_febex_data_temp;
	v_febex_data_temp.clear();

	if( lisa_settings::getIsSaveAsRoot() )initOptTree();

	//int cnt = 0;//for debug

	//***set entry reading***//
	ULong64_t entry_beg = 0;//beginning
	ULong64_t entry_end = 0;//end
	if( lisa_settings::getIsAllEntry() ){
		entry_beg = 0;
		entry_end = fnentries;
	}
	else{
		entry_beg = lisa_settings::getEntry()[0];
		entry_end = lisa_settings::getEntry()[1];
	}
	//*** loop from event_i to event_j ***//
	for(ULong64_t jentry = entry_beg;jentry < entry_end;jentry++){

		//stopwatch
		if(jentry%1000==0){
			timer.Reset();
			timer.Start();
		}

		lisa_settings::setJentry(jentry);
		if(lisa_settings::getVerbose() == 2)std::cout<<"current entry = "<<lisa_settings::getJentry()<<"/"<<fnentries<<std::endl;

		//*** clear variables ***//
		resetVariables();//reset variables
		febex_data_temp.clear();//set variables to initial value
		if( lisa_settings::getIsSaveAsRoot() )clearOptTree();

		bool f_is_single_mode = 0;
		for(int cc = 0;cc<16;cc++){
			if( f_is_single_mode == 1 ) continue;//if single mode, only do once without changing febexCh
			if( lisa_settings::getIsMultiChannelMode() && lisa_settings::getIsFebexCh(cc) )lisa_settings::setFebexCh(cc);//if multimode, set enabled febexCh
			if( ! lisa_settings::getIsFebexCh(cc) ) continue;//if multimode, skip disabled febexCh

			//debug
			//std::cout<<"cc = "<<cc<<", febexCh = "<<lisa_settings::getFebexCh()<<std::endl;

			resetTraces();
			loadSingleTrace(tree);
			calcCorrectTrace();
			calcMWDTrace();
			calcCFDTrace();
			if(lisa_settings::getIsCalcEKink() * lisa_settings::getIsCalcERange() == 1 ){
				std::cout<<"[ERROR INFO] Error_febex_cc_015. Can't enable calc.energy.via.kink and range in the meantime."<<std::endl;
				return;
			}
			if(lisa_settings::getIsCalcEKink()){
				findKink();//for pileup analysis
				calcEnergy();
			}else if(lisa_settings::getIsCalcERange()){
				calcEnergyInRange();
			}else{
				std::cout<<"[ERROR INFO] Error_febex_cc_016. THe way to calc energy is not determined in your setting file."<<std::endl;
				return;
			}

			//***debug***//
			//std::cout<<"--->before get values"<<std::endl;
			//febex_data_temp.print();

			//save data to febex_data
			febex_data_temp.fentry = jentry;
			febex_data_temp.fenergy_raw = getMWDenergy();
			//*** pileup anaysis ***//
			Int_t mhit_tem = febex_data_temp.fenergy_raw.size();
			//std::cout<<"febch = "<<cc<<"; mhit = "<<mhit_tem<<std::endl;
			if(mhit_tem == 0 )continue;
			//std::cout<<"febch = "<<cc<<"; mhit = "<<mhit_tem<<std::endl;
			//std::cout<<"energy_ray = "<<febex_data_temp.fenergy_raw[0]<<std::endl;
			//std::cout<<"read from hit = "<<lisa_settings::getReadFromHit()<<std::endl;
			if(mhit_tem <= lisa_settings::getReadFromHit()){
				std::cout<<"[ERROR INFO] Error_febex_cc_017. Can't read energy from hit "<<lisa_settings::getReadFromHit()<<". Please check your setting file."<<std::endl;
				continue;//if multihit in a single channel <= the hit to read, skip this event;
			}

			febex_data_temp.ftime_cfd = getCFDtime();
			febex_data_temp.flength = getCorrTraceLength();
			febex_data_temp.fch = lisa_settings::getFebexCh();
			febex_data_temp.fhit_s = mhit_tem;
			Double_t f_bias = 0;
			Double_t f_grad = 1;
			f_bias = lisa_settings::getEnergyCalib_Bias()[febex_data_temp.fch];
			f_grad = lisa_settings::getEnergyCalib_Grad()[febex_data_temp.fch];
			if( lisa_settings::getIsCalcEKink() )febex_data_temp.fenergy_cal = febex_data_temp.fenergy_raw[lisa_settings::getReadFromHit()]*f_grad + f_bias;
			if( lisa_settings::getIsCalcERange() )febex_data_temp.fenergy_cal = febex_data_temp.fenergy_raw[0]*f_grad + f_bias;
			febex_data_temp.fCorrTrace_x = getCorrectTraceI();//return a vector
			febex_data_temp.fCorrTrace_y = getCorrectTraceV();
			febex_data_temp.fMWDTrace_x = getMWDTraceI();
			febex_data_temp.fMWDTrace_y = getMWDTraceV();
			//***debug***//
			//std::cout<<"debug here1"<<std::endl;
			//std::cout<<"flength = "<<febex_data_temp.flength<<std::endl;
			/*
			   for(UInt_t ii=0;ii<febex_data_temp.flength;ii++){
			   if(febex_data_temp.flength == 0)continue;
			   febex_data_temp.fCorrTrace_x.push_back(fCorr_x[ii]);//fCorr_x[ii];
			   febex_data_temp.fCorrTrace_y.push_back(fCorr_y[ii]);//fCorr_y[ii];
			   }
			   for(UInt_t ii=0;ii<fMWD_x.size();ii++){
			   if(febex_data_temp.flength == 0)continue;
			   febex_data_temp.fMWDTrace_x.push_back(fMWD_x[ii]);//fMWD_x[ii];
			   febex_data_temp.fMWDTrace_y.push_back(fMWD_y[ii]);//fMWD_y[ii];
			   }
			   */
			//std::cout<<"debug here2"<<std::endl;
			//febex_data_temp.fMWDTrace_x = getMWDTraceI();//return a vector
			//febex_data_temp.fMWDTrace_y = getMWDTraceV();

			if(febex_data_temp.flength == 0)febex_data_temp.clear();//if empty
			setFebexData(febex_data_temp);//set febex_data
										  //std::cout<<"debug here3"<<std::endl;

			v_febex_data_temp.push_back(febex_data_temp);//add to febex_data vector; max is 6k events to save RAM
			if(jentry%6000==5999)v_febex_data_temp.clear();
			if( lisa_settings::getIsSaveAsRoot() )fillOptTree(febex_data_temp);//hit ++
			if( lisa_settings::getIsSingleChannelMode() )f_is_single_mode = 1;

		}//end of loop for 16 channels

		//***debug***//
		//std::cout<<"size of v_febex_data_temp = "<<v_febex_data_temp.size()<<std::endl;
		//std::cout<<"--->after get values"<<std::endl;
		//v_febex_data_temp.back().print();

		//***debug***//
		//std::cout<<"cnt = "<<cnt<<std::endl;
		//if(v_febex_data_temp.back().flength!=0){
		//    for(int jj=0;jj<10;jj++){
		//        std::cout<<"febex_data_temp.fCorrTrace_x[jj] = "<<v_febex_data_temp.back().fCorrTrace_x[jj]<<std::endl;
		//        std::cout<<"febex_data_temp.fCorrTrace_y[jj] = "<<v_febex_data_temp.back().fCorrTrace_y[jj]<<std::endl;
		//    }
		//}
		//cnt++;//for debug
		//***debug***//
		/*
		   if(cnt==3){
		   for(int jentry = 0;jentry<v_febex_data_temp.size();jentry++){
		   std::cout<<"jentry = "<<jentry<<std::endl;
		   if(v_febex_data_temp[jentry].flength == 0 || v_febex_data_temp[jentry].fCorrTrace_y.size() == 0)continue;
		   std::cout<<"--->flength = "<<v_febex_data_temp[jentry].flength<<""<<std::endl;
		   std::cout<<"--->fCorrTrace_y address = "<<&v_febex_data_temp[jentry].fCorrTrace_y<<""<<std::endl;
		   std::cout<<"--->fCorrTrace_y[0] = "<<v_febex_data_temp[jentry].fCorrTrace_y[0]<<""<<std::endl;
		   std::cout<<"--->fMWDTrace_y address = "<<&v_febex_data_temp[jentry].fMWDTrace_y<<""<<std::endl;
		   std::cout<<"--->fMWDTrace_y[0] = "<<v_febex_data_temp[jentry].fMWDTrace_y[0]<<""<<std::endl;
		   }
		   }*/

		//*** fill tree ***//
		if( lisa_settings::getIsSaveAsRoot() )getOptTree()->Fill();
		//*** calculate running time ***//
		double fspeed;
		double fduration;
		if(jentry%1000==999){
			fduration = timer.RealTime();//
			fspeed = 1000.0/fduration;// [evt/sec]
			v_averageSpeed.push_back(fspeed);
		}
		double ftimeToGo = 0;
		if(getIsAllEntry()){
			if(jentry%1000==999)ftimeToGo = (fnentries-jentry)/fspeed;
		}else{
			if(jentry%1000==999)ftimeToGo = (getEntry()[1]-jentry)/fspeed;
		}

		if(jentry%1000==999)std::cout<<"*Current speed: "<<fspeed<<"[evt/s]; Duration for 1000 evts: "<<fduration<<", Num:"<<jentry<<"/"<<fnentries<<"  "<<ftimeToGo<<"s to go.";
		fflush(stdout);
		printf("\r");
	}//end of loop

	//save data to febex_data vector
	setFebexDataV(v_febex_data_temp);

	//***export data to root file***//
	if( lisa_settings::getIsSaveAsRoot() )closeOptRoot();

	//***debug***//
	//for(int jentry = 0;jentry<v_febex_data_temp.size();jentry++){
	//    std::cout<<"jentry = "<<jentry<<std::endl;
	//    if(v_febex_data_temp[jentry].flength!=0){
	//        for(int jj=0;jj<10;jj++){
	//            std::cout<<"febex_data_temp.fCorrTrace_x[jj] = "<<v_febex_data_temp[jentry].fCorrTrace_x[jj]<<std::endl;
	//            std::cout<<"febex_data_temp.fCorrTrace_y[jj] = "<<v_febex_data_temp[jentry].fCorrTrace_y[jj]<<std::endl;
	//        }
	//    }
	//}

	Double_t gAverageSpeed = std::accumulate(v_averageSpeed.begin(),v_averageSpeed.end(),0.0)/v_averageSpeed.size();
	Double_t gTotalRunningTime = timer2.RealTime();
	std::cout<<std::endl;
	std::cout<<"--->Total running time: "<<gTotalRunningTime<<" s."<<std::endl;
	std::cout<<"--->Average speed     : "<<gAverageSpeed<<" [evt/s]."<<std::endl;

	std::cout<<"[Print INFO] getTraces() end***"<<std::endl;
	std::cout<<"...oooOO0OOooo......oooOO0OOooo......oooOO0OOooo......oooOO0OOooo..."<<std::endl;
	return;
}

void lisa_febex::resetTraces(){
	resetRawTraceV();
	resetRawTraceI();
	resetCorrectTraceV();
	resetCorrectTraceI();
	resetMWDTraceV();
	resetMWDTraceI();
	resetCFDTraceV();
	resetCFDTraceI();
}

void lisa_febex::initOptTree(){
	std::cout<<"[Print INFO] initOptTree***"<<std::endl;
	TFile *optfile = new TFile(lisa_settings::getOptRootFileName(),"RECREATE");
	TTree *optTree = new TTree("tree","tree");

	optTree->Branch("TRIGGER_c4",&TRIGGER_c4,"TRIGGER_c4/I");
	optTree->Branch("EVENTNO_c4",&EVENTNO_c4,"EVENTNO_c4/I");
	optTree->Branch("hit_m",&hit_m,"hit_m/i");
	optTree->Branch("hit_s",&hit_s,"hit_s/i");
	optTree->Branch("febCh",febCh,"febCh[hit_m]/I");
	optTree->Branch("entry",&entry,"entry/I");
	optTree->Branch("entry_empty",entry_empty,"entry_empty[hit_m]/I");
	optTree->Branch("ts",runts,"runts[hit_m]/L");
	optTree->Branch("tsS",runts_S,"runts_S[hit_m]/L");
	optTree->Branch("Eraw",Eraw,"Eraw[hit_m]/D");
	optTree->Branch("Ecal",Ecal,"Ecal[hit_m]/D");
	optTree->Branch("T_cfd",T_cfd,"T_cfd[hit_m]/D");
	optTree->Branch("if_overflow",if_overflow,"if_overflow[hit_m]/i");
	optTree->Branch("traceLength",traceLength,"traceLength[hit_m]/i");
	optTree->Branch("tracesX",tracesX,"tracesX[hit_m][3000]/D");//this has to be a specific value, MAX_TRACE_LENGTH is not allowed to use here.
	optTree->Branch("tracesY",tracesY,"tracesY[hit_m][3000]/D");
	optTree->Branch("MWDtracesX",MWDtracesX,"MWDtracesX[hit_m][3000]/D");//this has to be a specific value, MAX_TRACE_LENGTH is not allowed to use here.
	optTree->Branch("MWDtracesY",MWDtracesY,"MWDtracesY[hit_m][3000]/D");

	std::cout<<"--->init output root file."<<std::endl;
	setOptTree(optTree);
	setOptFile(optfile);
}

void lisa_febex::fillOptTree(febex_data &fopt){
	if( lisa_settings::getVerbose() ==3 )std::cout<<"[Print INFO] fillOptTree***"<<std::endl;

	TRIGGER_c4 = fopt.trigger;
	EVENTNO_c4 = fopt.evtno;

	if(fopt.flength==0)return;
	Double_t energy_tem = 0;
	if(lisa_settings::getIsCalcEKink())energy_tem = fopt.fenergy_raw[lisa_settings::getReadFromHit()];
	if(lisa_settings::getIsCalcERange())energy_tem = fopt.fenergy_raw[0];
	//std::cout<<"energy in saveasroot: "<<energy_tem<<std::endl;

	if(energy_tem < lisa_settings::getThresholdEnergy()[fopt.fch])return;

	febCh[hit_m] = fopt.fch;//0-15
	hit_s = fopt.fhit_s;
	entry = fopt.fentry;
	entry_empty[hit_m] = fopt.fentry_empty;
	runts[hit_m] = fopt.fts;
	runts_S[hit_m] = fopt.fts%1000000000;
	Eraw[hit_m] = energy_tem;
	Ecal[hit_m] = fopt.fenergy_cal;
	T_cfd[hit_m] = fopt.ftime_cfd;
	if_overflow[hit_m] = fopt.foverflow;
	traceLength[hit_m] = fopt.flength;//

	if(lisa_settings::getVerbose() == 2)std::cout<<"test in saveasroot: "<<Eraw[hit_m]<<" "<<Ecal[hit_m]<<std::endl;
	if(lisa_settings::getIsSaveTraces()){
		for(UInt_t i=0;i<fopt.flength;i++){
			//Double_t x,y;//for corrected traces
			tracesX[hit_m][i] = fopt.fCorrTrace_x[i];
			tracesY[hit_m][i] = fopt.fCorrTrace_y[i];
			MWDtracesX[hit_m][i] = fopt.fMWDTrace_x[i];
			MWDtracesY[hit_m][i] = fopt.fMWDTrace_y[i];
			if(lisa_settings::getVerbose() == 2)std::cout<<"in saveasroot: traceX = "<<tracesX[hit_m][i]<<" traceY = "<<tracesY[hit_m][i]<<std::endl;
		}
	}
	hit_m++;

}

void lisa_febex::clearOptTree(){
	if( lisa_settings::getVerbose() == 3 )std::cout<<"[Print INFO] clearOptTree***"<<std::endl;
	TRIGGER_c4 = 0; //UInt_t
	EVENTNO_c4 = 0; //UInt_t
	hit_m = 0;//hit for 16 febex channels
	hit_s = 0;//hit for a single channel
	entry = -1;
	for(int ii=0;ii<16;ii++){
		febCh[ii] = -1;
		entry_empty[ii] = -1;
		runts[ii] = -1;
		runts_S[ii] = -1;
		Eraw[ii] = -1;
		Ecal[ii] = -1;
		T_cfd[ii] = -9999;
		if_overflow[ii] = 0; //0, no; 1, yes
		traceLength[ii] = 0;//UInt_t
		for(int jj=0;jj<MAX_TRACE_LENGTH;jj++){
			tracesX[ii][jj] = -1;
			tracesY[ii][jj] = -1;
			MWDtracesX[ii][jj] = -1;
			MWDtracesY[ii][jj] = -1;
		}
	}
}

void lisa_febex::closeOptRoot(){
	std::cout<<"[Print INFO] *** closeOptRoot ***"<<std::endl;
	getOptTree()->Write("", TObject::kOverwrite);
	getOptFile()->Close();
	std::cout<<"******************************************"<<std::endl;
	std::cout<<"[Print INFO] Data has been saved to "<<lisa_settings::getOptRootFileName()<<"."<<std::endl;
	std::cout<<"[Print INFO] Root file has been closed."<<std::endl;

	std::cout<<"******************************************"<<std::endl;
}

