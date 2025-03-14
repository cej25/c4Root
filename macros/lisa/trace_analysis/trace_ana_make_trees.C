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

void trace_ana_make_trees(int fileNumber)
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
    //TString filename = "/u/gandolfo/data/lustre/despec/lisa/daq_test_0169_*.lmd";  //data with only lisa
    //TString inputpath = "/u/gandolfo/data/lustre/gamma/s092_s143_files/ts/";
    TString inputpath = "/u/gandolfo/data/lustre/despec/lisa/3x3_board_1/";

    TString filename = Form(inputpath + "run_%04d_0001.lmd", fileNumber);

    //___O U T P U T
    TString outputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/c4data/trees/"; 
    TString outputFilename = Form(outputpath + "run_%04d_0001_MWD_v2.root", fileNumber);


    //:::::::Create online run
    Int_t refresh = 10; // not needed
    Int_t port = 5000; // not needed
     
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFilename)); // don't write after termintion
    run->ActivateHttpServer(refresh, port);
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

    // ::: Lisa config
    TLisaConfiguration::SetMappingFile(config_path + "/Lisa_Detector_Map_names.txt");
    TLisaConfiguration::SetGMFile(config_path + "/Lisa_GainMatching.txt");
    TLisaConfiguration::SetMWDParametersFile(config_path + "/Lisa_MWD_Parameters_3x3.txt");
   
    // ::::::: READ Subsystem  ::::::::

    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);

    if (LISA_ON)
    {
        LisaReader* unpacklisa = new LisaReader((EXT_STR_h101_lisa_onion*)&ucesb_struct.lisa, offsetof(EXT_STR_h101, lisa));
        unpacklisa->SetOnline(true); //false= write to a tree; true=doesn't write to tree
        source->AddReader(unpacklisa);

        // ::: Analyse traces :::
        LisaRaw2Ana* lisaraw2ana = new LisaRaw2Ana();
        lisaraw2ana->SetOnline(false);
        run->AddTask(lisaraw2ana);
    }


    // Initialise
    run->Init();

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "LISA online port server: " << port << endl;
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
