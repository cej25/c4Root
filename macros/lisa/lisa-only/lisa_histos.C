#include <TROOT.h>

#define LISA_ON 1

#define LISA_DAQ 1
#define LISA_2x2 0


typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;

} EXT_STR_h101;

void lisa_histos()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    //:::::::::Experiment name
    TString fExpName = "lisa";

    //:::::::::Here you define commonly used path
    TString c4Root_path = "/u/gandolfo/c4/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes --allow-errors";
    ucesb_path.ReplaceAll("//","/");

    std::string config_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data());

    //:::::::::Macro timing
    TString cRunId = Form("%04d", fRunId);
    TString cExpId = Form("%03d", fExpId);
    TStopwatch timer;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    timer.Start();
    
    //:::::::::::Debug info - set level
    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);

    //::::::::::P A T H   O F   F I L E  to read
    //___O F F L I N E
    //TString filename = "/u/gandolfo/data/lustre/gamma/LISA/data/daq_test_c4tree/test_F_B_13nov.root";
    //TString filename = "/u/gandolfo/data/test_c4/run_0072_0001.root";
    TString filename = "/u/gandolfo/data/lustre/gamma/LISA/data/x7_241Am/3x3_4_trees/run_0006_0003_trees.root";
       
    //___O U T P U T
    //TString outputfile = "/u/gandolfo/data/test_c4/run_0072_0001_histos.root";
    TString outputfile = "/u/gandolfo/data/lustre/gamma/LISA/data/x7_241Am/3x3_4_histos/run_0006_0003_histo.root";

    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputfile)); // don't write after termintion
    FairSource* fs = new FairFileSource(filename);
    run->SetSource(fs);
    
    //Read tree evt
    TFile* file = TFile::Open(filename);
    TTree* eventTree = (TTree*)file->Get("evt"); 
    Int_t totEvt = eventTree->GetEntries();
     


    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::::: C O N F I G    F O R   D E T E C T O R - Load
    TLisaConfiguration::SetMappingFile(config_path + "/Lisa_3x3_4.txt");
    TLisaConfiguration::SetGMFile(config_path + "/Lisa_GainMatching.txt");
    TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters_3x3.txt");

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::   
    // =========== **** SPECTRA ***** ========================================================= //
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    

    
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    // ::: Nearline Spectra ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //::::::::: Set ranges for histos :::::::::::::::
    //::::  Channel Energy ::::: (h1_energy_layer_ch)
    TLisaConfiguration::SetEnergyRange(0,200000);
    TLisaConfiguration::SetEnergyBin(1000);

    TLisaConfiguration::SetEnergyRangeMWD(0,50);
    TLisaConfiguration::SetEnergyBinMWD(1000);

    //::::  Channel Energy GM ::::: (h1_energy_layer_ch)
    TLisaConfiguration::SetEnergyRangeGM(0,1000);
    TLisaConfiguration::SetEnergyBinGM(500);

    //:::: LISA WR Time Difference :::::: (h1_wr_diff)
    TLisaConfiguration::SetWrDiffRange(0,100000000);
    TLisaConfiguration::SetWrDiffBin(20000);

    //:::: Drifts
    TLisaConfiguration::SetEventNO(50000,1600000);
    

    if (LISA_ON)
    {
        if (LISA_DAQ)
        {
            LisaNearlineSpectraDaq* nearlinelisadaq = new LisaNearlineSpectraDaq();
            run->AddTask(nearlinelisadaq);
        }

        if (LISA_2x2)
        {

        }
        
    }


    // Initialise
    run->Init();

    // Run
    run->Run(0, totEvt); 

    // Finish
    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    Float_t cpuUsage = ctime / rtime;
    cout << "CPU used: " << cpuUsage << endl;
    std::cout << std::endl << std::endl;
    std::cout << "Macro finished successfully." << std::endl;
    std::cout << "Output file is " << outputfile << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
}
