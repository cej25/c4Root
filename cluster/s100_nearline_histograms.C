#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define FATIMA_ON 1
#define FATIMA_VME_ON 1
#define AIDA_ON 1
#define BPLAST_ON 1
#define GERMANIUM_ON 1
#define BGO_ON 0
#define FRS_ON 1
#define TIME_MACHINE_ON 0
#define BEAMMONITOR_ON 0
#define WHITE_RABBIT_CORS 0

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/
extern "C"
{
    #include "../../config/s100/frs/setup_s100_dryrun.C"
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
    EXT_STR_h101_frsmain_onion_t frsmain;
    EXT_STR_h101_frstpc_onion_t frstpc;
    EXT_STR_h101_frsuser_onion_t frsuser;
    EXT_STR_h101_frstpat_onion_t frstpat;
    EXT_STR_h101_beammonitor_onion_t beammonitor;
    EXT_STR_h101_bgo_onion_t bgo;
    // EXT_STR_h101_bb7febex_onion_t bb7febex;
} EXT_STR_h101;


void nearline(TString filename)
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
    TString outputpath = "Au_beam_0010_0001_histograms";
    TString outputFileName = outputpath + ".root";

    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName));
    FairSource* fs = new FairFileSource(filename);
    run->SetSource(fs);

    // ------------------------------------------------------------------------------------ //
    // *** Initialise FRS parameters ****************************************************** //
    
    TFRSParameter* frs = new TFRSParameter();
    TMWParameter* mw = new TMWParameter();
    TTPCParameter* tpc = new TTPCParameter();
    TMUSICParameter* music = new TMUSICParameter();
    TLABRParameter* labr = new TLABRParameter();
    TSCIParameter* sci = new TSCIParameter();
    TIDParameter* id = new TIDParameter();
    TSIParameter* si = new TSIParameter();
    TMRTOFMSParameter* mrtof = new TMRTOFMSParameter();
    TRangeParameter* range = new TRangeParameter();
    setup(frs,mw,tpc,music,labr,sci,id,si,mrtof,range); // Function defined in frs setup.C macro
    TFrsConfiguration::SetParameters(frs,mw,tpc,music,labr,sci,id,si,mrtof,range);

    // ------------------------------------------------------------------------------------ //
    // *** Initialise Gates *************************************************************** //

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

    if (FATIMA_ON)
    {
        FatimaNearlineSpectra* nearlinefatima = new FatimaNearlineSpectra();
        nearlinefatima->SetBinningSlowToT(2000,560,660);
        nearlinefatima->SetBinningFastToT(1000,0.1,100.1);
        nearlinefatima->SetBinningEnergy(1000,0.1,1500.1);

        std::vector<int> fat_dets = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64};
        nearlinefatima->SetDetectorsToPlot(fat_dets);
        
        std::vector<int> fat_ref_dets = {54};
        nearlinefatima->SetReferenceDetectorsForTimeDifferences(fat_ref_dets);
        
        run->AddTask(nearlinefatima);
    }
    
    if (FATIMA_VME_ON)
    {    
        FatimaVmeNearlineSpectra* nearlinefatimavme = new FatimaVmeNearlineSpectra();
        
        run->AddTask(nearlinefatimavme);
    }
    
    if (AIDA_ON)
    {
        AidaNearlineSpectra* aidaNearline = new AidaNearlineSpectra();
        
        run->AddTask(aidaNearline);
    }
    
    if (BPLAST_ON)
    {
        bPlastNearlineSpectra* nearlinebplast = new bPlastNearlineSpectra();
        
        run->AddTask(nearlinebplast);
        
    }
    
    if (GERMANIUM_ON)
    {
        GermaniumNearlineSpectra* nearlinege = new GermaniumNearlineSpectra();
        nearlinege->SetBinningEnergy(3000,0,3e3);
        nearlinege->AddReferenceDetector(15,0);
        nearlinege->AddReferenceDetector(1,0);
        run->AddTask(nearlinege);
    }
    
    if (BGO_ON)
    {
        BGOOnlineSpectra* nearlinebgo = new BGONearlineSpectra();
        nearlinebgo->SetBinningEnergy(1500,0.1,1500.1);

        
        run->AddTask(nearlinebgo);
        
    }
    
    TFrsConfiguration::Set_Z_range(70,100);
    TFrsConfiguration::Set_AoQ_range(2.3,2.7);
    
    if (FRS_ON)
    {
        FrsNearlineSpectra* nearlinefrs = new FrsNearlineSpectra();
        
        run->AddTask(nearlinefrs);
    }
    
    TString b = "Aida";
    TString c = "Fatima";
    TString d = "FatimaVme";
    TString e = "bPlast";
    TString f = "Germanium";

    if (TIME_MACHINE_ON) // a little complicated because it falls apart if the right subsystem is switched off
    {
        TimeMachineOnline* tms = new TimeMachineOnline();
        std::vector a {b, c, d, e, f};
        tms->SetDetectorSystems(a);
        
        run->AddTask(tms);
    }
    
    if (WHITE_RABBIT_CORS)
    {
        WhiterabbitCorrelationOnline* wronline = new WhiterabbitCorrelationOnline();
        wronline->SetDetectorSystems({b, c, d, e, f});
    
        run->AddTask(wronline);
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
