//
//last updated@25 Jul,2024
//Z.Chen
//

#include "../inc/lisa_settings.hh"
#include <TSystem.h>


lisa_settings::lisa_settings(){
    std::cout<<"***lisa_settings::lisa_settings()***"<<std::endl;
}

lisa_settings::lisa_settings(TString name){
    if(gSystem->AccessPathName(name)){//check if file exists
        std::cout<<"***Error_lisa_settings_002:can not find/open setting file: "<<name<<" ***"<<std::endl;
        return;
    }
    loadSettings(name);
}


lisa_settings::~lisa_settings(){
    std::cout<<"***lisa_settings::~lisa_settings()***"<<std::endl;
}

void lisa_settings::loadSettings(TString name){
    setSettings(name);
    TEnv env(name);

    //*** verbose ***//
    fVerbose = env.GetValue("Verbose",0);

    //*** path and name ***//
    //fFebexDataFile = env.GetValue("Febex4.data.filename","./LISA_root_tree.root");
    fSettingFile = env.GetValue("Setting.file.name","lisa_settings.set");
    fNewSettingFile = env.GetValue("New.setting.file.name","settings_Febex_export.set");
    fScopeDataPath = env.GetValue("Scope.data.path","./Scope_data/");
    //fOptRootFileName = env.GetValue("SaveAsRoot.filename","sCVD.root");

    //*** functional switch ***//
    //*** enable and disable ***//
    fIsAllEntryRead = env.GetValue("Enable.read.all.entry",false);
    fIsSingleChMode = env.GetValue("Enable.single.channel.analysis.mode",false);
    fIsMultiChMode = env.GetValue("Enable.multi.channel.analysis.mode",false);
    fIsSubNoise = env.GetValue("Enable.subtract.noise.with.baseline",false);
    fIsIntegral = env.GetValue("Enable.energyCalculation.integral",false);
    fIsMWD = env.GetValue("Enable.energyCalculation.algorithm",true);
    fIsCalcDMi = env.GetValue("Enable.DMi",false);
    fIsCalcMWDi = env.GetValue("Enable.MWDi",true);
    fIsBaselineCorr = env.GetValue("Enable.baseline.correction",false);
    fIsTimeCorr = env.GetValue("Enable.time.correction",false);
    fIsSaveTraces = env.GetValue("Enable.save.traces",false);
    fIsSaveAsRoot = env.GetValue("Enable.save.as.root",false);
	fIsCalcERange = env.GetValue("Enable.calc.energy.via.range",true);
	fIsCalcEKink = env.GetValue("Enable.calc.energy.via.kink",false);

    //*** unpacker ***//
    fIsGo4Unpacker = env.GetValue("Enable.go4.unpacker",false);
    fIsUcesbUnpacker = env.GetValue("Enable.ucesb.unpacker",false);

    //*** details ***//
    fSampleRate = env.GetValue("Sample.rate[MHz]",666);
    fFebexTraceLengthSet = env.GetValue("Febex4.trace.length",1000);
    fRisingTime = env.GetValue("Rising.time[ns]",666);
    //fDecaytime = env.GetValue("Decaytime[ns]",66666);
    fEntry[0] = env.GetValue("Tree.read.from.entry.0",666);
    fEntry[1] = env.GetValue("Tree.read.to.entry.1",6666);
    fEntryScope[0] = env.GetValue("Scope.read.from.entry.0",666);
    fEntryScope[1] = env.GetValue("Scope.read.to.entry.1",6666);
    fScopeSampleWindow[0] = env.GetValue("Scope.sample.window.0",666);
    fScopeSampleWindow[1] = env.GetValue("Scope.sample.window.1",6666);
    fJentry = env.GetValue("Read.from.Jentry",666);
    fJentryScope = env.GetValue("Scope.read.from.Jentry",666);
    fFebexCh = env.GetValue("Febex4.read.from.ch",0);
    for(int i=0;i<16;i++)fMultiCh[i] = env.GetValue(TString::Format("Multimode.read.from.ch.%d",i),0);//i is index here; Int, 0-15; fMultiCh is bool
    for(int i=0;i<16;i++)fThreshold[i] = env.GetValue(TString::Format("Threshold.ch.%d",i),-1);//i is febex ch here; Int
    for(int i=0;i<16;i++)fDecaytime[i] = env.GetValue(TString::Format("Decaytime.ch.%d",i),100000);//i is febex ch here; Int
	fReadFromHit = env.GetValue("Read.from.Hit",0);
	fUndershootThres = env.GetValue("Undershoot.threshold",10);

    //*** MWD and CFD ***//
    fIntergralWindow[0] = env.GetValue("Integral.window.0",-0.2);
    fIntergralWindow[1] = env.GetValue("Integral.window.1",2.);
    fTrapezSampleWindow[0] = env.GetValue("Trapez.Sample.window.0",1);
    fTrapezSampleWindow[1] = env.GetValue("Trapez.Sample.window.1",2);
    fTrapezAmpCalcWindow[0] = env.GetValue("Trapez.Amp.Calc.window.0",-1);
    fTrapezAmpCalcWindow[1] = env.GetValue("Trapez.Amp.Calc.window.1",1);
    fTrapezMovingWindowLength = env.GetValue("Trapez.Moving.Window.Length[ns]",666);
    fCFDWindow[0] = env.GetValue("CFD.window.0",0.0);
    fCFDWindow[1] = env.GetValue("CFD.window.1",0.0);
	fThreads = env.GetValue("Set.MWD.calculation.threads",10);

    //*** histogram and display ***//
    fHistoNbins = env.GetValue("Histogram.bins",4000);
    fEHisto[0] = env.GetValue("Energy.histogram.range.0",0);
    fEHisto[1] = env.GetValue("Energy.histogram.range.1",1);
    fTHisto[0] = env.GetValue("Time.histogram.range.0",-1);
    fTHisto[1] = env.GetValue("Time.histogram.range.1",1);
    fEnergySpecRange[0] = env.GetValue("Energy.spectrum.range.0",0);
    fEnergySpecRange[1] = env.GetValue("Energy.spectrum.range.1",0);
    fTimeSpecRange[0] = env.GetValue("Time.spectrum.range.0",-1);
    fTimeSpecRange[1] = env.GetValue("Time.spectrum.range.1",1);
    fTraceAmpRange[0] = env.GetValue("Trace.graph.Y.min",-2);
    fTraceAmpRange[1] = env.GetValue("Trace.graph.Y.max",2);
    fCFDref = env.GetValue("CFD.reference",0.0);
    fCFDwin[0] = env.GetValue("CFD.window.0",140.);
    fCFDwin[1] = env.GetValue("CFD.window.1",160.);
    fCFDFra = env.GetValue("CFD.pars.fraction",0.9);
    fCFDdelay = env.GetValue("CFD.pars.delay",1.2);

    //*** calibration and fit ***//
    fParLimit = env.GetValue("Fit.Pars.Limit",12.0);
    for(int ii=0;ii<MAX_SIZE;ii++)fCalibPar_b[ii] = env.GetValue(Form("Energy.calib.bias.%d",ii),0.0);
    for(int ii=0;ii<MAX_SIZE;ii++)fCalibPar_s[ii] = env.GetValue(Form("Energy.calib.gradient.%d",ii),1.0);
    for(int ii=0;ii<MAX_SIZE;ii++)fmean[ii] = env.GetValue(Form("Mean.value.%d",ii),-1);
    for(int ii=0;ii<MAX_SIZE;ii++)fsigma[ii] = env.GetValue(Form("Sigma.value.%d",ii),-1);
    for(int ii=0;ii<MAX_SIZE;ii++)famp[ii] = env.GetValue(Form("Amplitude.value.%d",ii),-1);
    for(int ii=0;ii<MAX_SIZE;ii++)fEref[ii] = env.GetValue(Form("Energy.reference.%d",ii),-1);
    for(int ii=0;ii<MAX_SIZE;ii++)fEres[ii] = env.GetValue(Form("Energy.resolution.%d",ii),-1);

}

void lisa_settings::printSettings(){
    std::cout<<"***lisa_settings::printSettings()***"<<std::endl;
    std::cout<<"Verbose = "<<getVerbose()<<std::endl;
    std::cout<<"Febex4.data.filename = "<<getInputFileName()<<std::endl;
    std::cout<<"New.setting.file.name = "<<getNewSettingFile()<<std::endl;
    std::cout<<"SaveAsRoot.filename = "<<getOptRootFileName()<<std::endl;

    //*** functional switch ***//
    //*** enable and disable ***//
    std::cout<<"Enable.read.all.entry = "<<getIsAllEntry()<<std::endl;
    std::cout<<"Enable.single.channel.analysis.mode = "<<getIsSingleChannelMode()<<std::endl;
    std::cout<<"Enable.multi.channel.analysis.mode = "<<getIsMultiChannelMode()<<std::endl;
    std::cout<<"Enable.subtract.noise.with.baseline = "<<getIsSubNoise()<<std::endl;
    std::cout<<"Enable.energyCalculation.integral = "<<getIsIntegral()<<std::endl;
    std::cout<<"Enable.energyCalculation.algorithm = "<<getIsMWD()<<std::endl;
    std::cout<<"Enable.baseline.correction = "<<getIsBaselineCorr()<<std::endl;
    std::cout<<"Enable.time.correction = "<<getIsTimeCorr()<<std::endl;
    std::cout<<"Enable.save.traces = "<<getIsSaveTraces()<<std::endl;
    std::cout<<"Enable.save.as.root = "<<getIsSaveAsRoot()<<std::endl;
    std::cout<<"Enable.DMi = "<<getIsCalcDMi()<<std::endl;
    std::cout<<"Enable.MWDi = "<<getIsCalcMWDi()<<std::endl;

    //*** unpacker ***//
    std::cout<<"Enable.go4.unpacker = "<<getIsGo4Unpacker()<<std::endl;
    std::cout<<"Enable.ucesb.unpacker = "<<getIsUcesbUnpacker()<<std::endl;
    
    //*** details ***//
    std::cout<<"Sample.rate[MHz] = "<<getSampleRate()<<std::endl;
    std::cout<<"Febex4.trace.length = "<<loadFebexTraceL()<<std::endl;
    std::cout<<"Rising.time[ns] = "<<getRisingTime()<<std::endl;
    std::cout<<"Decaytime[ns] = "<<getDecayTime()<<std::endl;
    std::cout<<"Tree.read.from.entry.0 = "<<getEntry()[0]<<std::endl;
    std::cout<<"Tree.read.to.entry.1 = "<<getEntry()[1]<<std::endl;
    std::cout<<"Read.from.Jentry = "<<getJentry()<<std::endl;
    std::cout<<"Febex4.read.from.ch = "<<getFebexCh()<<std::endl;
    std::cout<<"*******************************************************************"<<std::endl;
}

