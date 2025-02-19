#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define AIDA_ON 1
#define BPLAST_ON 1
#define GERMANIUM_ON 1
#define BGO_ON 0
#define FRS_ON 0
#define TIME_MACHINE_ON 1
#define BEAMMONITOR_ON 0
#define WHITE_RABBIT_CORS 1
#define BB7_ON 0

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/
// CEJ: not configured for s101 yet
extern "C"
{
    #include "../../config/s101/frs/setup_s181_010_2024_conv.C"
}

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_aida_onion_t aida;
    EXT_STR_h101_bplast_onion_t bplast;
    EXT_STR_h101_germanium_onion_t germanium;
    EXT_STR_h101_frs_onion_t frs;
    EXT_STR_h101_beammonitor_onion_t beammonitor;
    EXT_STR_h101_bgo_onion_t bgo;
    EXT_STR_h101_bb7vme_onion_t bb7vme;
} EXT_STR_h101;


void s101_online()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "s101";

    // Define important paths.
    TString c4Root_path = "/u/despec/s101_online/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes";
    ucesb_path.ReplaceAll("//","/");

    std::string config_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data());
    
    std::cout << config_path << std::endl;

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
    // DO NOT CHANGE THIS DURING A RUN!!!!!!!
   // TString filename = "trans://x86l-143";
     TString filename = "trans://lxg3107";
    // TString filename = "/lustre/gamma/s101_files/dryrun_ts/*";
//     TString filename = "trans://lxg1257"; // timesorter.
//     TString filename = "trans://x86l-144"; // ??
    TString outputpath = "output";
    TString outputFileName = outputpath + ".root";

    // Create Online run
    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 5000; // Port number for online visualisation - use 5000 on lxg1301 during experiments as it has firewall access.

    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName));
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);

  
    // Create source using ucesb for input
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK"; // Define which level of data to unpack - we don't use "RAW" or "CAL"
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

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
    
    
    // ------------------------------------------------------------------------------------ //
    // *** Initialise Correlations ******************************************************** //
    
    TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations.dat");

    
    // ------------------------------------------------------------------------------------ //
    // *** Load Detector Configurations *************************************************** //
    TAidaConfiguration::SetBasePath(config_path + "/AIDA");
    TbPlastConfiguration::SetDetectorMapFile(config_path + "/bplast/bplast_mapping_220125.txt");
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TGermaniumConfiguration::SetDetectorConfigurationFile(config_path + "/germanium/ge_alloc_jan22.txt");
    TGermaniumConfiguration::SetDetectorCoefficientFile(config_path + "/germanium/ge_cal_feb19_linear.txt");
    //TGermaniumConfiguration::SetDetectorTimeshiftsFile(config_path + "/germanium/ge_timeshifts_apr20.txt");
    //TGermaniumConfiguration::SetPromptFlashCut(config_path + "/germanium/ge_prompt_flash.root");

    TBGOTwinpeaksConfiguration::SetDetectorConfigurationFile(config_path + "/bgo/bgo_alloc.txt");
    
    TBB7VmeConfiguration::SetDetectorConfigurationFile(config_path + "/bb7/BB7_Detector_Map_s181.txt");  
    TBB7VmeConfiguration::SetResidualSignalsFile(config_path + "/bb7/BB7_Residuals_Map.txt");   

    // ------------------------------------------------------------------------------------- //
    // *** Read Subsystems - comment out unwanted systems ********************************** //

    // EventHeader - should always be done
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    
    source->AddReader(unpackheader);
    
    if (AIDA_ON)
    {
        AidaReader* unpackaida = new AidaReader((EXT_STR_h101_aida_onion*)&ucesb_struct.aida, offsetof(EXT_STR_h101, aida));
        
        unpackaida->SetOnline(true);
        source->AddReader(unpackaida);
    }

    if (BB7_ON)
    {
       BB7Reader* unpackbb7 = new BB7Reader((EXT_STR_h101_bb7vme_onion*)&ucesb_struct.bb7vme, offsetof(EXT_STR_h101, bb7vme));
       unpackbb7->SetOnline(true);
       source->AddReader(unpackbb7);
    }

    if (BPLAST_ON)
    {
        bPlastReader* unpackbplast = new bPlastReader((EXT_STR_h101_bplast_onion*)&ucesb_struct.bplast, offsetof(EXT_STR_h101, bplast));
        //unpackbplast->DoFineTimeCalOnline(config_path + "/bplast/fine_time_s181_7June.root", 1000000);
         unpackbplast->SetInputFileFineTimeHistos(config_path + "/bplast/fine_time_s181_7June.root");
        
        unpackbplast->SetOnline(true);
        source->AddReader(unpackbplast);
    }

    if (GERMANIUM_ON)
    {
        GermaniumReader* unpackgermanium = new GermaniumReader((EXT_STR_h101_germanium_onion*)&ucesb_struct.germanium, offsetof(EXT_STR_h101, germanium));
        
        unpackgermanium->SetOnline(true);
        source->AddReader(unpackgermanium);
    }
    
    if (BGO_ON)
    {
        BGOReader* unpackbgo = new BGOReader((EXT_STR_h101_bgo_onion*)&ucesb_struct.bgo, offsetof(EXT_STR_h101, bgo));
        // unpackbgo->DoFineTimeCalOnline(config_path + "/bgo/fine_time_histos_s181_8June.root", 1000000);
        unpackbgo->SetInputFileFineTimeHistos(config_path + "/bgo/fine_time_histos_s181_8June.root");
        
        unpackbgo->SetOnline(true);
        source->AddReader(unpackbgo);
        
    }
    
    if (FRS_ON)
    {
        FrsReader* unpackfrs = new FrsReader((EXT_STR_h101_frs_onion*)&ucesb_struct.frs, offsetof(EXT_STR_h101, frs));
        
        unpackfrs->SetOnline(true);
        
        source->AddReader(unpackfrs);
    }
    
    if (BEAMMONITOR_ON)
    {
        BeamMonitorReader* unpackbeammonitor = new BeamMonitorReader((EXT_STR_h101_beammonitor_onion*)&ucesb_struct.beammonitor, offsetof(EXT_STR_h101, beammonitor));
        
        unpackbeammonitor->SetOnline(true);
        source->AddReader(unpackbeammonitor);
    }

   
    // ---------------------------------------------------------------------------------------- //
    // *** Calibrate Subsystems - comment out unwanted systems ******************************** //    
    if (AIDA_ON)
    {
        AidaUnpack2Cal* aidaCalibrator = new AidaUnpack2Cal();
        
        aidaCalibrator->SetOnline(true);
        run->AddTask(aidaCalibrator);
        
    }
    
    if (BB7_ON)
    {
        TBB7VmeConfiguration::SetImplantThreshold(1500);
        BB7Raw2Cal* calbb7 = new BB7Raw2Cal();
        
        calbb7->SetOnline(true);
        run->AddTask(calbb7);
    }
    
    if (BPLAST_ON)
    {
        bPlastRaw2Cal* calbplast = new bPlastRaw2Cal();
        
        calbplast->SetOnline(true);
        run->AddTask(calbplast);
        
        
    }
    
    if (GERMANIUM_ON)
    {
        GermaniumRaw2Cal* calge = new GermaniumRaw2Cal();
        // calge->PrintDetectorMap();

        calge->SetOnline(true);
        run->AddTask(calge);
    }
    
    if (BGO_ON)
    {
        BGORaw2Cal* calbgo = new BGORaw2Cal();
        // calbgo->PrintDetectorMap();
        
        calbgo->SetOnline(true);
        run->AddTask(calbgo);
    }
        
    
    if (FRS_ON)
    {
        FrsRaw2Cal* calfrs = new FrsRaw2Cal();
        
        calfrs->SetOnline(true);
        run->AddTask(calfrs);
    }


    // ---------------------------------------------------------------------------------------- //
    // *** Analyse Subsystem Hits ************************************************************* //
    
    if (AIDA_ON)
    {        
        AidaCal2Hit* aidaHitter = new AidaCal2Hit();
        
        aidaHitter->SetOnline(true);
        run->AddTask(aidaHitter);
    }
    
    if (FRS_ON)
    {
        FrsCal2Hit* hitfrs = new FrsCal2Hit();
        
        hitfrs->SetOnline(true); 
        run->AddTask(hitfrs);
    } 



    // ======================================================================================== //
    // =========== **** SPECTRA ***** ========================================================= //
    // ======================================================================================== //
    
    // ---------------------------------------------------------------------------------------- //
    // *** Online Spectra ********************************************************************* //    
    if (AIDA_ON)
    {
        AidaOnlineSpectra* aidaOnline = new AidaOnlineSpectra();
        
        run->AddTask(aidaOnline);
    }

    if (BB7_ON)
    {
        BB7OnlineSpectra* onlinebb7 = new BB7OnlineSpectra();

        run->AddTask(onlinebb7);
    }
    
    if (BPLAST_ON)
    {
        bPlastOnlineSpectra* onlinebplast = new bPlastOnlineSpectra();
        
        run->AddTask(onlinebplast);
        
    }
    
    if (GERMANIUM_ON)
    {
        GermaniumOnlineSpectra* onlinege = new GermaniumOnlineSpectra();
        onlinege->SetBinningEnergy(12000,0,3e3);
        onlinege->AddReferenceDetector(15,0);
        onlinege->AddReferenceDetector(16,0);
        onlinege->AddReferenceDetector(1,0);
        onlinege->AddReferenceDetectorWithEnergyGates(1,0,1332);
        onlinege->AddReferenceDetectorWithEnergyGates(1,0,1173,1332);
        onlinege->SetEnergyGateWidth(10);
        run->AddTask(onlinege);
    }

    TBGOTwinpeaksConfiguration::SetCoincidenceWindow(1000);
    TBGOTwinpeaksConfiguration::SetCoincidenceOffset(500);
    if (BGO_ON)
    {
        BGOOnlineSpectra* onlinebgo = new BGOOnlineSpectra();
        onlinebgo->SetBinningEnergy(3000,0.1,3000.1);

        run->AddTask(onlinebgo);
        
    }
    
//     TFrsConfiguration::Set_Z_range(30,120);
//     TFrsConfiguration::Set_AoQ_range(2.0,3.0);
//     FrsGate* zHeavy = new FrsGate("zHeavy",config_path+"/frs/Gates/zHeavy.root");
//     FrsGate* zHeavy2 = new FrsGate("zHeavy2",config_path+"/frs/Gates/zHeavy.root");
//     std::vector<FrsGate*> frsgates{};
//     frsgates.emplace_back(zHeavy);
// 
//     if (FRS_ON)
//     {
//         FrsOnlineSpectra* onlinefrs = new FrsOnlineSpectra(frsgates);
//         For monitoring FRS on our side
//         FrsRawSpectra* frsrawspec = new FrsRawSpectra();
//         FrsCalSpectra* frscalspec = new FrsCalSpectra();
//         
//         run->AddTask(onlinefrs);
//         run->AddTask(frsrawspec);
//         run->AddTask(frscalspec);
//     }
//     
    if (BEAMMONITOR_ON)
    {
        BeamMonitorOnlineSpectra* onlinebm = new BeamMonitorOnlineSpectra();
        
        run->AddTask(onlinebm);
    }
    
    //FRS GATES::

    
//     if (AIDA_ON && FRS_ON)
//     {
//         
//         FrsAidaCorrelationsOnline* frsaida = new FrsAidaCorrelationsOnline(frsgates);
//         
//         run->AddTask(frsaida);
//     }
    
    
//     if (FRS_ON && GERMANIUM_ON)
//     {
//         FrsGermaniumCorrelations* zhv = new FrsGermaniumCorrelations(zHeavy);
//         zhv->SetShortLifetimeCollectionWindow(20000);
//         run->AddTask(zhv);
//         FrsGermaniumCorrelations* zhv2 = new FrsGermaniumCorrelations(zHeavy2);
//         zhv2->SetShortLifetimeCollectionWindow(20000);
//         run->AddTask(zhv2);
//     }


    TString b = "Aida";
    TString c = "bPlast";
    TString d = "Germanium";
    TString e = "Frs";
    //TString f = "BB7";
    TString g = "BGO";

    if (TIME_MACHINE_ON) // a little complicated because it falls apart if the right subsystem is switched off
    {
        TimeMachineOnline* tms = new TimeMachineOnline();
        std::vector a {b, d, c};
        tms->SetDetectorSystems(a);
        
        run->AddTask(tms);
    }
    
    if (WHITE_RABBIT_CORS)
    {
        WhiterabbitCorrelationOnline* wronline = new WhiterabbitCorrelationOnline();
        wronline->SetDetectorSystems({b,c});
        
        run->AddTask(wronline);
    }

    // Initialise
    run->Init();
    
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "Online port server: " << port << endl;
    cout << "\n\n" << endl;

    // create sink object before run starts    
    FairSink* sf = FairRunOnline::Instance()->GetSink();

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
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
   
   // ----------------------------------------------------------------------------------------- //

}

