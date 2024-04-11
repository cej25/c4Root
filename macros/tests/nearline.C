#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define FATIMA_ON 1
#define FATIMA_VME_ON 1
#define AIDA_ON 0
#define BPLAST_ON 1
#define GERMANIUM_ON 0
#define BGO_ON 0
#define FRS_ON 0
#define TIME_MACHINE_ON 0
#define BEAMMONITOR_ON 0
#define WHITE_RABBIT_CORS 0

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_bplast_onion_t bplast;
    EXT_STR_h101_fatima_onion_t fatima;
} EXT_STR_h101;


void nearline()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "s100";

    // Define important paths.
    TString screenshot_path = "~/lustre/gamma/dryrunmarch24/screenshots/";
    TString c4Root_path = "/u/cjones/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes --allow-errors --max-events=300000";
    ucesb_path.ReplaceAll("//","/");

    std::string config_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data());

    // Macro timing
    TString cRunId = Form("%04d", fRunId);
    TString cExpId = Form("%03d", fExpId);
    TStopwatch timer;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    timer.Start();
    
    // Set level of debug information
    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);

    // Define where to read data from. Online = stream/trans server, Nearline = .lmd file.
    TString filename = "Au_beam_0010_0001_tree.root";
    TString outputpath = "Au_beam_0010_0001_histograms";
    TString outputFileName = outputpath + ".root";

    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName));
    FairSource* fs = new FairFileSource(filename);
    run->SetSource(fs);

    TbPlastConfiguration::SetDetectorMapFile(config_path + "/bplast/bplast_alloc_mar20.txt");
    TFatimaTwinpeaksConfiguration::SetDetectorConfigurationFile(config_path + "/fatima/fatima_alloc_new.txt");
    TFatimaVmeConfiguration::SetDetectorMapFile(config_path + "/fatima/Fatima_VME_allocation.txt");
    TAidaConfiguration::SetBasePath(config_path + "/AIDA");
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TGermaniumConfiguration::SetDetectorConfigurationFile(config_path + "/germanium/ge_alloc_mar21.txt");
    TBGOTwinpeaksConfiguration::SetDetectorConfigurationFile(config_path + "/bgo/bgo_alloc.txt");

    // ======================================================================================== //
    // =========== **** SPECTRA ***** ========================================================= //
    // ======================================================================================== //
    
    // ---------------------------------------------------------------------------------------- //
    // *** Nearline Spectra ********************************************************************* //

    if (BPLAST_ON)
    {
        bPlastNearlineSpectra* nearlinebplast = new bPlastNearlineSpectra();
    
        run->AddTask(nearlinebplast);
    }

    if (FATIMA_ON)
    {
        FatimaNearlineSpectra* nearlinefatima = new FatimaNearlineSpectra();
        nearlinefatima->SetBinningSlowToT(2000,560,660);
        nearlinefatima->SetBinningFastToT(1000,0.1,100.1);
        nearlinefatima->SetBinningEnergy(1000,0.1,1500.1);

        // why is this set to 64
        std::vector<int> fat_dets = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64};
        nearlinefatima->SetDetectorsToPlot(fat_dets);
        
        std::vector<int> fat_ref_dets = {};
        nearlinefatima->SetReferenceDetectorsForTimeDifferences(fat_ref_dets);
    
        run->AddTask(nearlinefatima);
    }
   
    if (FATIMA_VME_ON)
    {    
        FatimaVmeNearlineSpectra* nearlinefatimavme = new FatimaVmeNearlineSpectra();
        
        run->AddTask(nearlinefatimavme);
    }


    // Initialise
    run->Init();
    
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "\n\n" << endl;

    // Run
    //run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev); 
    run->Run(0,10000000); // most files around 9m events? can increase this number? dunno

    // ---------------------------------------------------------------------------------------- //
    // *** Finish Macro *********************************************************************** //

    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    Float_t cpuUsage = ctime / rtime;
    cout << "CPU used: " << cpuUsage << endl;
    std::cout << std::endl << std::endl;
    std::cout << "Macro finished successfully." << std::endl;
    std::cout << "Output file is " << outputFileName << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
   // gApplication->Terminate(0);
   
   // ----------------------------------------------------------------------------------------- //
}
