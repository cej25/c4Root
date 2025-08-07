#include <TROOT.h>
#include <TNamed.h>
#include <TObjString.h>
#include <fstream>
#include <sstream>

//Select the data level you want to visualize
#define LISA_RAW 0
#define LISA_ANA 0
#define LISA_CAL 1

// Definition of setup and configuration files
// LISA
#define LISA_CONFIG_FILE "../../config/lisa/general/lisa_config_v0.C"

extern "C"
{    
    // LISA setup
    #include LISA_CONFIG_FILE
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;

} EXT_STR_h101;

std::string readFileToString(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) return "[Could not open file]";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void lisa_make_trees()
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
    TString filename = "/u/gandolfo/data/lustre/despec/lisa/Pikachu_room/pikachu_0072_0003.lmd"; 

    //___O U T P U T - only used if switched on 
    TString outputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/SummerStudentProject2025/trees/";
    TString outputFilename = outputpath + "pikachu_0072_test.root";   
        
    //:::::::Create online run
    Int_t refresh = 10; // not needed
     
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFilename)); // don't write after termintion
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);
     
    //:::::::Take ucesb input and create source
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK"; //level of unpacked data (UNPACK,RAW,CAL)
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: L I S A parameter - Initialise
    lisa_config(config_path);
    
   

    // ::::::: READ Subsystem  ::::::::
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);


    LisaReader* unpacklisa = new LisaReader((EXT_STR_h101_lisa_onion*)&ucesb_struct.lisa, offsetof(EXT_STR_h101, lisa));
    LisaRaw2Ana* lisaraw2ana = new LisaRaw2Ana();

    if (LISA_RAW)
    {
        unpacklisa->SetOnline(false); //false= write to a tree; true=doesn't write to tree
    } else 
    {
        unpacklisa->SetOnline(true); //false= write to a tree; true=doesn't write to tree
    }
    
    if (LISA_ANA)
    {
        lisaraw2ana->SetOnline(false); //false= write to a tree; true=doesn't write to tree
    } else 
    {
        lisaraw2ana->SetOnline(true); //false= write to a tree; true=doesn't write to tree
    }
    
    source->AddReader(unpacklisa);
    lisaraw2ana->SetOnline(true);
    run->AddTask(lisaraw2ana);
    
    
    // ::::::: CALIBRATE Subsystem  ::::::::

    if (LISA_CAL)
    {
        LisaAna2Cal* lisaana2cal = new LisaAna2Cal();

        lisaana2cal->SetOnline(false);
        run->AddTask(lisaana2cal); 
        
    }
    
    // Write information on setup and config in a "info" tree
    TString lisaConfigFile = LISA_CONFIG_FILE;

    TTree* metaTree = new TTree("info", "Setup file and config info");
    metaTree->Branch("LISA_config", &lisaConfigFile);
    metaTree->Fill(); 


    // Initialise
    run->Init();
    metaTree->Write();

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "\n\n" << endl;

    // Run
    run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);

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
   // gApplication->Terminate(0);
}
