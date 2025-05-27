#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define FATIMA_ON 0
#define FATIMA_VME_ON 1
#define AIDA_ON 0
#define BPLAST_ON 0
#define GERMANIUM_ON 0
#define BGO_ON 0
#define FRS_ON 0
#define TIME_MACHINE_ON 0
#define BEAMMONITOR_ON 0
#define WHITE_RABBIT_CORS 0

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/
extern "C"
{
    #include "../../config/s100/frs/setup_des_s100_030_2024_conv.C"
}

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fatima_onion_t fatima;
    EXT_STR_h101_fatimavme_onion_t fatimavme;
    EXT_STR_h101_aida_onion_t aida;
    EXT_STR_h101_bplast_onion_t bplast;
    EXT_STR_h101_germanium_onion_t germanium;
    EXT_STR_h101_frs_onion_t frs;
    EXT_STR_h101_beammonitor_onion_t beammonitor;
    EXT_STR_h101_bgo_onion_t bgo;
    // EXT_STR_h101_bb7febex_onion_t bb7febex;
} EXT_STR_h101;


void c_fat_test_2025_histos()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "s100";

    // Define important paths.
    TString c4Root_path = "/u/cjones/c4Root";

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

    // ::: INPUT
    // TString filename = "trans://R4L-21"; // fatima vme now, was beammonitor in principle? 
    TString filename = "run_0009_0001_tree.root";


    // ::: O U T P U T
    TString outputpath = "./"; //test output
    TString outputFileName = "run_0009_0001_histos.root";


    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName)); // don't write after termintion
    FairSource* fs = new FairFileSource(filename);
    run->SetSource(fs);
    
    //Read tree evt
    TFile* file = TFile::Open(filename);
    TTree* eventTree = (TTree*)file->Get("evt"); 
    Int_t totEvt = eventTree->GetEntries();

    // ------------------------------------------------------------------------------------ //
    // *** Initialise Correlations ******************************************************** //
    
    TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations.dat");
    // for S100, 3 and 4. for 2025+ 12 and 13.
    TExperimentConfiguration::SetBOSTrig(3);
    TExperimentConfiguration::SetEOSTrig(4);

    // ------------------------------------------------------------------------------------ //
    // *** Load Detector Configurations *************************************************** //
    TFatimaVmeConfiguration::SetDetectorMapFile(config_path + "/fatima/Fatima_VME_allocation.txt");
    TFatimaVmeConfiguration::Set_QDC_E_CalFile(config_path + "/fatima/Rough_Cal_2005.txt");
    TFatimaVmeConfiguration::Set_QDC_T_CalFile(config_path + "/fatima/Fatima_QDC_Time_Calibration.txt");
    TFatimaVmeConfiguration::Set_TDC_T_CalFile(config_path + "/fatima/Fatima_TDC_Time_Calibration.txt");
    


    FatimaVmeNearlineSpectra* nearlinefatimavme = new FatimaVmeNearlineSpectra();
        
    run->AddTask(nearlinefatimavme);

    // Initialise
    run->Init();

    // Run
    run->Run(0, totEvt); 
    
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
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
    std::cout << "Output file is " << outputFileName << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
   
   // ----------------------------------------------------------------------------------------- //

}

