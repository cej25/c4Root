#include <TROOT.h>

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    // EXT_STR_h101_aida_onion_t aida;
    // EXT_STR_h101_bplast_onion_t bplast;
    EXT_STR_h101_germanium_onion_t germanium;
    // 
    // EXT_STR_h101_frs_onion_t frs;
    // EXT_STR_h101_beammonitor_onion_t beammonitor;
    // EXT_STR_h101_bgo_onion_t bgo;
    EXT_STR_h101_bbfebex_onion_t bbfebex;
} EXT_STR_h101;


void run_bb7_online(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1)
{   
    // Name your experiment. Make sure all relevant directories are named identically.
    // TString fExpName = "NovTest";
    //TString fExpName = "s100";
    TString fExpName = "s101";


    // Define important paths.
    // TString c4Root_path = "/u/despec/s101_online/c4Root";
    TString c4Root_path = "/u/cjones/c4Root";
    // TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --input-buffer=200Mi --event-sizes";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + "febex" + "/" + "febex" + " --debug --input-buffer=200Mi --event-sizes";

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
    // TString filename = "~/lustre/despec/bb7_test_2025/Co_jun_ohm_0200.lmd";
    // TString filename = "~/lustre/despec/bb7_test_2025/exp_bkg_daq2_0001.lmd";
    //TString filename = "trans://lxg3107";
    TString filename = "/u/cjones/lustre/gamma/s101_files/ts/107Ag_0108_0008.lmd";
    //TString filename = "~/lustre/despec/s302/107Ag_primary_beam/107Ag_0061_0001.lmd";
    //TString filename = "~/lustre/despec/bb7_test_2025/bkg_jun_ohm_full_0106.lmd";
    TString outputpath = "bb7_test_output";
    TString outputFileName = outputpath + ".root";

    // Create Online run
    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 6060; // Port number for online visualisation - use 5000 on lxg1301 during experiments as it has firewall access.
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    //run->SetSink(new FairRootFileSink(outputFileName));
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);

    // Create source using ucesb for input
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK,RAW"; // Define which level of data to unpack
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

    // ------------------------------------------------------------------------------------ //
    // *** Initialise Correlations ******************************************************** //
    
    // TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations.dat");


    // ------------------------------------------------------------------------------------ //
    // *** Load Detector Configurations *************************************************** //
    
    // TBB7VmeConfiguration::SetDetectorConfigurationFile("/u/cjones/c4Root/config/s181/bb7/BB7_Detector_Map_s181.txt");
    //TBB7FebexConfiguration::SetMappingFile("/u/cjones/c4Root/config/s101/bb7/BB7_Detector_Map.txt");  
    TBB7FebexConfiguration::SetMappingFile("/u/despec/s101_online/c4Root/config/s101/bb7/BB7_Detector_Map_feb21.txt"); 

    TGermaniumConfiguration::SetDetectorConfigurationFile(config_path + "/germanium/ge_alloc_jan22.txt");
    TGermaniumConfiguration::SetDetectorCoefficientFile(config_path + "/germanium/ge_cal_feb21_2025_new_cards.txt");
    TGermaniumConfiguration::SetDetectorTimeshiftsFile(config_path + "/germanium/ge_timeshifts_2202.txt");
    TGermaniumConfiguration::SetPromptFlashCut(config_path + "/germanium/promptflash_new.root");

    // TBB7VmeConfiguration::SetResidualSignalsFile("/u/cjones/c4Root/config/s181/bb7/BB7_Residuals_Map.txt");   

    // ------------------------------------------------------------------------------------- //
    // *** Read Subsystems - comment out unwanted systems ********************************** //

    // EventHeader - should always be done
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    
    source->AddReader(unpackheader);
    

    //BB7Reader* unpackbb7 = new BB7Reader((EXT_STR_h101_bb7vme_onion*)&ucesb_struct.bb7vme, offsetof(EXT_STR_h101, bb7vme));
    BB7FebexReader* unpackbb7 = new BB7FebexReader((EXT_STR_h101_bbfebex_onion*)&ucesb_struct.bbfebex, offsetof(EXT_STR_h101, bbfebex));

    unpackbb7->SetOnline(false);
    source->AddReader(unpackbb7);

    
        GermaniumReader* unpackgermanium = new GermaniumReader((EXT_STR_h101_germanium_onion*)&ucesb_struct.germanium, offsetof(EXT_STR_h101, germanium));
        
        unpackgermanium->SetOnline(true);
        source->AddReader(unpackgermanium);
    
    
    // TBB7VmeConfiguration::SetImplantThreshold(1500);

    // BB7Raw2Cal* calbb7 = new BB7Raw2Cal();
    BB7FebexRaw2Cal* calbb7 = new BB7FebexRaw2Cal();

    calbb7->SetOnline(false);
    run->AddTask(calbb7);

   
        GermaniumRaw2Cal* calge = new GermaniumRaw2Cal();
        // calge->PrintDetectorMap();
        
        // calge->PrintDetectorCal();
        calge->SetOnline(true);
        run->AddTask(calge);
    

    BB7FebexCal2Hit* hitbb7 = new BB7FebexCal2Hit();
    hitbb7->SetOnline(false);
    run->AddTask(hitbb7);

     GermaniumOnlineSpectra* onlinege = new GermaniumOnlineSpectra();
        onlinege->SetBinningEnergy(12000,0,3e3);
        onlinege->AddReferenceDetector(15,0);
        onlinege->AddReferenceDetector(16,0);
        onlinege->AddReferenceDetector(1,0);
        onlinege->AddReferenceDetectorWithEnergyGates(1,0,1332);
        onlinege->AddReferenceDetectorWithEnergyGates(1,0,1173,1332);
        onlinege->SetEnergyGateWidth(10);
        run->AddTask(onlinege);

    // BB7OnlineSpectra* onlinebb7 = new BB7OnlineSpectra();
    BB7FebexOnlineSpectra* onlinebb7 = new BB7FebexOnlineSpectra();

    run->AddTask(onlinebb7);

    BB7GermaniumCorrelationsOnline* bb7germ = new BB7GermaniumCorrelationsOnline();
    run->AddTask(bb7germ);
    
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
    std::cout << "Output file is " << outputFileName << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
   // gApplication->Terminate(0);
   
   // ----------------------------------------------------------------------------------------- //
}
