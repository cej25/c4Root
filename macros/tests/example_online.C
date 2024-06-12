#include <TROOT.h>

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fatima_onion_t fatima;
} EXT_STR_h101;


void example_online(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1)
{   
    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "s181";

    // Define important paths.
    TString c4Root_path = "/u/cjones/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes";
    ucesb_path.ReplaceAll("//","/");

    std::string config_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data());

    TString cRunId = Form("%04d", fRunId);
    TString cExpId = Form("%03d", fExpId);
    TStopwatch timer;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    timer.Start();

    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);

    // Define where to read data from. Online = stream/trans server, Nearline = .lmd file.
    TString filename = "~/lustre/gamma/s100_files/ts/168Dy_0033_0003.lmd";
    // TString outputpath = "bb7_test_output";
    // TString outputFileName = outputpath + ".root";

    // Create Online run
    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 7070; // Port number for online visualisation - use 5000 on lxg1301 during experiments as it has firewall access.
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    // run->SetSink(new FairRootFileSink(outputFileName));
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);

    // Create source using ucesb for input
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK"; // Define which level of data to unpack
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

    // ------------------------------------------------------------------------------------ //
    // *** Load Detector Configurations *************************************************** //
    
    TFatimaTwinpeaksConfiguration::SetDetectorConfigurationFile(config_path + "/fatima/fatima_alloc_apr18.txt");
    TFatimaTwinpeaksConfiguration::SetDetectorCoefficientFile(config_path + "/fatima/fatima_cal_apr18.txt");
    TFatimaTwinpeaksConfiguration::SetDetectorTimeshiftsFile(config_path + "/fatima/fatima_timeshifts_apr20.txt");
    TFatimaTwinpeaksConfiguration::SetPromptFlashCutFile(config_path + "/fatima/fatima_prompt_flash.root");

    // ------------------------------------------------------------------------------------- //
    // *** Read Subsystems - comment out unwanted systems ********************************** //

    // EventHeader - should always be done
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    
    source->AddReader(unpackheader);
    
    FatimaReader* unpackfatima = new FatimaReader((EXT_STR_h101_fatima_onion*)&ucesb_struct.fatima, offsetof(EXT_STR_h101, fatima));
    //unpackfatima->DoFineTimeCalOnline(config_path + "/fatima/fine_time_4apr_test.root", 100000);
    unpackfatima->SetInputFileFineTimeHistos(config_path + "/fatima/fine_time_23apr_beamON.root");

    unpackfatima->SetOnline(true);
    source->AddReader(unpackfatima);

    FatimaRaw2Cal* calfatima = new FatimaRaw2Cal();
    
    calfatima->SetOnline(true);
    run->AddTask(calfatima);


    // ExampleSpectra* exampleonline = new ExampleSpectra();

    // run->AddTask(exampleonline);
    
    // Initialise
    run->Init();
    
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "Online port server: " << port << endl;
    cout << "\n\n" << endl;

    // Run
    run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev); 

    // ---------------------------------------------------------------------------------------- //
    // *** Finish Macro *********************************************************************** //
    
    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    Float_t cpuUsage = ctime / rtime;
    cout << "CPU used: " << cpuUsage << endl;
    std::cout << std::endl << std::endl;
    std::cout << "Macro finished successfully." << std::endl;
    // std::cout << "Output file is " << outputFileName << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
   // gApplication->Terminate(0);
   
   // ----------------------------------------------------------------------------------------- //
}
