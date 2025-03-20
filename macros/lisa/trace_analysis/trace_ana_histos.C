#include <TROOT.h>

#define LISA_ON 1
#define FRS_ON 0
#define TRAV_MUSIC_ON 0
#define WHITE_RABBIT_CORS 0 

// Define FRS setup.C file - FRS should provide; place in /config/pareeksha/frs/
extern "C"
{
    #include "../../../config/pareeksha/frs/setup_Fragment_conv.C"
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;

} EXT_STR_h101;

void trace_ana_histos(int fileNumber)
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
    TString inputpath = "/u/gandolfo/data/";
    TString filename = Form(inputpath + "run_%04d_0001_MWD_fast_v2.root", fileNumber);  
    
    //___O U T P U T
    TString outputpath = "/u/gandolfo/data/"; 
    TString outputFilename = Form(outputpath + "run_%04d_0001_MWD_fast_v2_histos.root", fileNumber);


    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFilename)); // don't write after termintion
    FairSource* fs = new FairFileSource(filename);
    run->SetSource(fs);
    
    // ::: Read tree evt
    TFile* file = TFile::Open(filename);
    TTree* eventTree = (TTree*)file->Get("evt"); 
    Int_t totEvt = eventTree->GetEntries();
     
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: LISA config
    TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters_3x3.txt");

    // ::: Get run number :::
    TFrsConfiguration::SetRunNumber(fileNumber);
    std::cout << "Run number: " << fileNumber << std::endl;

    // ::: Set Board number :::
    //     Since at this stage the mapping is not included, board number is hardcoded.
    TLisaConfiguration::SetBoardNumber(1);
    TLisaConfiguration::SetEventToAnalyze(208250); 
    //for run 0075_0001 good evt is 600004, for run0001 (3x3) evt = 97000 (ID=6)
    // for run_0002_0001 good evt for ch2 is 208250

    //::::::::: Set ranges for histos :::::::::::::::
    //::::  Channel Energy ::::: (h1_energy_)
    TLisaConfiguration::SetEnergyRange(0,2500000);
    TLisaConfiguration::SetEnergyBin(500);

    TLisaConfiguration::SetEnergyRangeMWD(0,100);
    TLisaConfiguration::SetEnergyBinMWD(100);

    //::::::::: Set ranges for traces for 2D histos :::::::::::::::
    // ::: Trace time (x axis)
    TLisaConfiguration::SetTracesBin(3000); //500
    TLisaConfiguration::SetTracesRange(1,30);

    // ::: Trace amplitude (y axis) :::    TLisaConfiguration::SetTracesBin(1000);
    TLisaConfiguration::SetAmplitudeBin(500);
    TLisaConfiguration::SetAmplitudeMin(-400);
    TLisaConfiguration::SetAmplitudeMax(100);


    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: Analyze system

    if (LISA_ON)
    {
        LisaTraceAnalysis* traceanalisa = new LisaTraceAnalysis();
        run->AddTask(traceanalisa);
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
    std::cout << "Output file is " << outputFilename << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
}
