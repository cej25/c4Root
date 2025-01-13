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
    TString inputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/c4data/trees/";
    TString filename = Form(inputpath + "run_%04d_0001_c4MWD_v7.root", fileNumber);  
    
    //___O U T P U T
    TString outputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/c4data/histos/"; 
    TString outputFilename = Form(outputpath + "run_%04d_0001_c4MWD_histos_v7.root", fileNumber);


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
    TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters.txt");

    // ::: Get run number :::
    TFrsConfiguration::SetRunNumber(fileNumber);
    std::cout << "Run number: " << fileNumber << std::endl;

    // ::: Set Board number :::
    //     Since at this stage the mapping is not included, board number is hardcoded.
    TLisaConfiguration::SetBoardNumber(1);
    TLisaConfiguration::SetEventToAnalyze(600004);
    
    //::::::::: Set ranges for histos :::::::::::::::
    //::::  Channel Energy ::::: (h1_energy_)
    TLisaConfiguration::SetEnergyRange(0,2500000);
    TLisaConfiguration::SetEnergyBin(500);

    TLisaConfiguration::SetEnergyRangeMWD(0,4000);
    TLisaConfiguration::SetEnergyBinMWD(500);

    //::::::::: Set ranges for traces :::::::::::::::
    // ::: Trace amplitude :::
    // ::: Trace x axis :::


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
