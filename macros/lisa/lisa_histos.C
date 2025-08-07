#include <TROOT.h>
#include <TNamed.h>
#include <TObjString.h>
#include <fstream>
#include <sstream>

// If you want to have trace histos
#define TRACE_ON 1
#define WR_ENABLED 0

// Definition of histo ranges for lisa and frs
#define HISTO_FILE "../../config/lisa/general/histo_config_v0.C"

extern "C"
{
    #include HISTO_FILE
}

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
    TString filename = "/u/gandolfo/data/lustre/gamma/LISA/data/SummerStudentProject2025/trees/pikachu_0072_test.root";
       
    //___O U T P U T
    TString outputfile = "/u/gandolfo/data/lustre/gamma/LISA/data/SummerStudentProject2025/histos/pikachu_0072_histos_test.root";


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
    histo_config(config_path);
     
    if(TRACE_ON)
    {
        TLisaConfiguration::SetTrace(1);
    }else
    {
        TLisaConfiguration::SetTrace(0);
    }
    
    LisaNearlineSpectraDaq* nearlinelisadaq = new LisaNearlineSpectraDaq();
    run->AddTask(nearlinelisadaq);


    TString histoConfigFile = HISTO_FILE;

    TTree* metaTree = new TTree("info", "Histo info file");
    metaTree->Branch("histo_config", &histoConfigFile);
    metaTree->Fill();  

    // Initialise
    run->Init();
    metaTree->Write(); 

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
