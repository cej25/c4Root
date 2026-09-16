#include <TROOT.h>

#define LISAFAST_ON 1
#define LISAFAST_RAW 0

// Definition of setup and configuration files
//#define LISA_CONFIG_FILE "../../config/lisafast/general/lisa_config_fast.C"

// :::  Define LISA setup.C file; place in /config/cologne/general
extern "C"
{    
    // LISA setup
    //#include LISA_CONFIG_FILE
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisafast_onion_t lisafast;

} EXT_STR_h101;

std::string readFileToString(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) return "[Could not open file]";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

//void cologne_make_trees(int fileNumber)
void lisafast_make_trees()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    // ::: Experiment name
    TString fExpName = "lisafast";

    // ::: Here you define commonly used path
    TString c4Root_path = "/home/lisa/programs/c4/fast_c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes --allow-errors";
    ucesb_path.ReplaceAll("//","/");

    std::string config_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data());

    // ::: Macro timing
    TString cRunId = Form("%04d", fRunId);
    TString cExpId = Form("%03d", fExpId);
    TStopwatch timer;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    timer.Start();
    
    // ::: Debug info - set level
    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);

    
    // ::: FILE  PATH
    TString inputpath = "/home/lisa/data/server/groups/wimmer/laboratory/lmd/";
    TString lmdname = "tamex_0010_0001.lmd";
    TString filename = inputpath + lmdname;

    //TString filename = Form(inputpath + "run_%04d_*.lmd", fileNumber);

    // ::: OUTPUT 
    TString outputpath = "/home/lisa/data/server/groups/wimmer/laboratory/trees/";

    TString outputFilename = outputpath + TString(lmdname).ReplaceAll(".lmd", "_tree.root");



    // ::: Create run
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFilename)); // don't write after termintion

    //TFolder* histograms = new TFolder("Histograms", "Histograms");
    //FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    //run->AddObject(histograms);

    // ::: Take ucesb input and create source
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK,RAW"; //level of unpacked data (UNPACK,RAW,CAL)
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

    // ::: L I S A parameter - Initialise
    //lisa_config(config_path);
    TLisaFastConfiguration::SetDetectorConfigurationFile(config_path + "/Lisa_Mapping_LaBr3.txt");

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // S U B S Y S T E M S
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   
    // ::: READ Subsystem  :::

    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);

    if (LISAFAST_ON)
    {
        LisaFastReader* unpacklisafast = new LisaReader((EXT_STR_h101_lisafast_onion*)&ucesb_struct.lisafast, offsetof(EXT_STR_h101, lisafast));

        if (LISAFAST_RAW)
        {
            unpacklisa->SetOnline(false); //false= write to a tree; true=doesn't write to tree
        } else 
        {
            unpacklisa->SetOnline(true); //false= write to a tree; true=doesn't write to tree
        }        
        source->AddReader(unpacklisafast);
    }

    // ::: CALIBRATE Subsystem  :::
    // if (LISAFAST_ON && LISAFAST_CAL )
    // {
    //     LisaFastRaw2Ana* lisafastraw2ana = new LisaFastRaw2Ana();

    //     lisafastraw2ana->SetOnline(false);
    //     run->AddTask(lisafastraw2ana);  
    // } 


    // Write information on setup and config in a "info" tree
    //TString lisaConfigFile = LISA_CONFIG_FILE;

    //TTree* metaTree = new TTree("info", "Setup file and config info");
    //metaTree->Branch("LISA_config", &lisaConfigFile);
    //metaTree->Fill();
    
    run->Init();  
    //metaTree->Write(); 

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
