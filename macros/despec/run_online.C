#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define FATIMA_ON 1
#define FATIMA_VME_ON 0
#define AIDA_ON 0
#define BPLAST_ON 0
#define GERMANIUM_ON 0
#define FRS_ON 0
#define TIME_MACHINE_ON 0

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/
extern "C"
{
    #include "../../config/NovTest/frs/setup.C"
}

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fatima_onion_t fatima;
    EXT_STR_h101_aida_onion_t aida;
    EXT_STR_h101_bplast_onion_t bplast;
    EXT_STR_h101_germanium_onion_t germanium;
    EXT_STR_h101_frsmain_onion_t frsmain;
    EXT_STR_h101_frstpc_onion_t frstpc;
    EXT_STR_h101_frsuser_onion_t frsuser;
    EXT_STR_h101_frsvftx_onion_t frsvftx;
} EXT_STR_h101;


void run_online(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1)
{   
    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "NovTest"; // "s100";

    // Define important paths.
    TString c4Root_path = "/u/despec/s100_online/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --allow-errors --input-buffer=200Mi --event-sizes";
    ucesb_path.ReplaceAll("//","/");

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
    // TString filename = "stream://x86l-117";
    // TString filename = "trans://lxg1257";
    // TString filename = "~/lustre/gamma/DESPEC_NOV23_FILES/ts/Ubeam_0024_0001.lmd";
    TString filename = "~/lustre/nustar/profi/r3b_s118feb24/S118-33_0116.lmd"
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

    // Create source using ucesb for input
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK"; // Define which level of data to unpack
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
    
    // ------------------------------------------------------------------------------------ //
    // *** Initialise Gates *************************************************************** //
    
    // Gates - Note: please name the TCutG and TCutG file the same thing
    // Add as many to the filename vector as you like,
    // but use the "default" gate files if you have none to add 
    std::string frs_gate_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data()) + "/frs/Gates/";
    std::vector<std::string> ZAoQ_cuts = {"ZvsAoQ1"};
    TCutGGates* ZAoQ = new TCutGGates("ZAoQ", ZAoQ_cuts, frs_gate_path);
    std::vector<std::string> Z1Z2_cuts = {"Z1vsZ21"};
    TCutGGates* Z1Z2 = new TCutGGates("Z1Z2", Z1Z2_cuts, frs_gate_path);
    std::vector<std::string> x2AoQ_cuts = {"x2vsAoQ1"};
    TCutGGates* x2AoQ = new TCutGGates("x2AoQ", x2AoQ_cuts, frs_gate_path);
    std::vector<std::string> x4AoQ_cuts = {"x4vsAoQ1"};
    TCutGGates* x4AoQ = new TCutGGates("x4AoQ", x4AoQ_cuts, frs_gate_path);
    std::vector<std::string> dEdegZ_cuts = {"dEdegvsZ1"};
    TCutGGates* dEdegZ = new TCutGGates("dEdegZ", dEdegZ_cuts, frs_gate_path);
    std::vector<TCutGGates*> FrsGates = {ZAoQ, Z1Z2, x2AoQ, x4AoQ, dEdegZ};
    
    // Define prompt cut EdT gates for Fatima Prompt analysis
    std::string fatima_gate_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data()) + "/fatima/Gates/";
    std::vector<std::string> FatimaPromptCuts = {"FatPromptCut1"};
    TCutGGates* FatimaPrompt = new TCutGGates("FatimaEdT", FatimaPromptCuts, fatima_gate_path);

    
    // ------------------------------------------------------------------------------------ //
    // *** Initialise Correlations ******************************************************** //
    
    std::string CorrConfigFile = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data()) + "/correlations.dat";
    CorrelationsMap* CorrMap = new CorrelationsMap(CorrConfigFile);

    
    // ------------------------------------------------------------------------------------- //
    // *** Read Subsystems - comment out unwanted systems ********************************** //

    // EventHeader - should always be done
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));

    // FATIMA
    FatimaReader* unpackfatima = new FatimaReader((EXT_STR_h101_fatima_onion*)&ucesb_struct.fatima, offsetof(EXT_STR_h101, fatima));
    unpackfatima->SetInputFileFineTimeHistos(std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data()) + "/fatima/fine_time_histos_111223_fatima.root");
    // unpackfatima->DoFineTimeCalOnline(std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data()) + "/fatima/fine_time_histos_111223_fatima.root", 50000);
    
    // AIDA
    // TAidaConfiguration::SetBasePath(std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data()) + "/AIDA");
    // AidaReader* unpackaida = new AidaReader((EXT_STR_h101_aida_onion*)&ucesb_struct.aida, offsetof(EXT_STR_h101, aida));
    
    // bPlast
    // bPlastReader* unpackbplast = new bPlastReader((EXT_STR_h101_bplast_onion*)&ucesb_struct.bplast, offsetof(EXT_STR_h101, bplast));
    // unpackbplast->DoFineTimeCalOnline(std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data()) + "/bplast/fine_time_histos_111223_bplast.root", 1000000);
    // unpackbplast->SetInputFileFineTimeHistos(std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data()) + "/bplast/fine_time_histos_111223_bplast.root");    
    
    // Germanium
    // GermaniumReader* unpackgermanium = new GermaniumReader((EXT_STR_h101_GERMANIUM_onion*)&ucesb_struct.germanium, offsetof(EXT_STR_h101, germanium));

    // FRS
    // FrsMainReader* unpackfrsmain = new FrsMainReader((EXT_STR_h101_frsmain_onion*)&ucesb_struct.frsmain, offsetof(EXT_STR_h101, frsmain));
    // FrsTPCReader* unpackfrstpc = new FrsTPCReader((EXT_STR_h101_frstpc_onion*)&ucesb_struct.frstpc, offsetof(EXT_STR_h101, frstpc));
    // FrsUserReader* unpackfrsuser = new FrsUserReader((EXT_STR_h101_frsuser_onion*)&ucesb_struct.frsuser, offsetof(EXT_STR_h101, frsuser));
    // FrsVFTXReader* unpackfrsvftx = new FrsVFTXReader((EXT_STR_h101_frsvftx_onion*)&ucesb_struct.frsvftx, offsetof(EXT_STR_h101, frsvftx));


    // Set 'Reader' tasks Online/Offline - false will write data to a tree.
    unpackfatima->SetOnline(true);
    // unpackaida->SetOnline(true);
    // unpackbplast->SetOnline(true);
    // unpackgermanium->SetOnline(true);SetTimeMachineChannels
    // unpackfrsmain->SetOnline(true);
    // unpackfrstpc->SetOnline(true);
    // unpackfrsuser->SetOnline(true);
    // unpackfrsvftx->SetOnline(true);


    // Add 'Reader' tasks to incoming UcesbSource
    source->AddReader(unpackheader);
    source->AddReader(unpackfatima);
    // source->AddReader(unpackaida);
    // source->AddReader(unpackbplast);
    // source->AddReader(unpackgermanium);
    // source->AddReader(unpackfrsmain);
    // source->AddReader(unpackfrstpc);
    // source->AddReader(unpackfrsuser);
    // source->AddReader(unpackfrsvftx);

   
    // ---------------------------------------------------------------------------------------- //
    // *** Calibrate Subsystems - comment out unwanted systems ******************************** //

    // FATIMA
    FatimaRaw2Cal* calfatima = new FatimaRaw2Cal();
    calfatima->SetDetectorMapFile(std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data()) + "/fatima/fatima_alloc.txt");
    // calfatima->PrintDetectorMap();
    calfatima->SetDetectorCalFile(std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data()) + "/fatima/fatima_cal.txt");
    // calfatima->PrintDetectorCal();
    // CEJ FOR JELL/JPB -- this should be read from alloc file!!!!!
    calfatima->SetTimeMachineChannels(16,17);

    // AIDA
    // AidaUnpack2Cal* aidaCalibrator = new AidaUnpack2Cal();
    // aidaCalibrator->SetAidaTimeMachineChannels(4,3);

    // bPlast
    // bPlastRaw2Cal* calbplast = new bPlastRaw2Cal();
    // calbplast->SetDetectorMapFile(std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data()) + "/bplast/bplast_allocation_111223.txt");
    // calbplast->SetTimeMachineChannels(68,67);

    // Germanium
    // GermaniumRaw2Cal * ge_calib = new GermaniumRaw2Cal();
    // ge_calib->SetDetectorMapFile(std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data()) + "germanium/Germanium_Detector_Map.txt");
    // ge_calib->PrintDetectorMap();

    // FRS
    // FrsMainRaw2Cal* calfrsmain = new FrsMainRaw2Cal();
    // FrsTPCRaw2Cal* calfrstpc = new FrsTPCRaw2Cal(frs,mw,tpc,music,labr,sci,id,si,mrtof,range);
    // FrsUserRaw2Cal* calfrsuser = new FrsUserRaw2Cal();
    // FrsVFTXRaw2Cal* calfrsvftx = new FrsVFTXRaw2Cal();

    
    // Set 'Calibration' tasks Online/Offline - false writes data to a tree.
    calfatima->SetOnline(true);
    // aidaCalibrator->SetOnline(true);
    // calbplast->SetOnline(true);
    // ge_calib->SetOnline(false);
    // calfrsmain->SetOnline(true);
    // calfrstpc->SetOnline(true);
    // calfrsuser->SetOnline(true);
    // calfrsvftx->SetOnline(true);
    

    // Add 'Calibration' tasks to FairRun.
    run->AddTask(calfatima);
    // run->AddTask(aidaCalibrator);
    // run->AddTask(calbplast);
    // run->AddTask(ge_calib);
    // run->AddTask(calfrsmain);
    // run->AddTask(calfrstpc);
    // run->AddTask(calfrsuser);
    // run->AddTask(calfrsvftx);


    // ---------------------------------------------------------------------------------------- //
    // *** Analyse Subsystem Hits ************************************************************* //
    
    // AIDA
    // AidaCal2Hit* aidaHitter = new AidaCal2Hit();
 
    // FRS
    // FrsCal2Hit* hitfrs = new FrsCal2Hit(frs,mw,tpc,music,labr,sci,id,si,mrtof,range);


    // Set 'Hit' tasks Online/Offline - comment out unwanted tasks.
    // aidaHitter->SetOnline(true);
    // hitfrs->SetOnline(false); 
    
    // Add 'Hit' tasks to FairRun.
    // run->AddTask(aidaHitter);
    // run->AddTask(hitfrs);


    // ======================================================================================== //
    // =========== **** SPECTRA ***** ========================================================= //
    // ======================================================================================== //
    
    // ---------------------------------------------------------------------------------------- //
    // *** Online Spectra ********************************************************************* //
    
    // FATIMA
    FatimaOnlineSpectra * onlinefatima = new FatimaOnlineSpectra();
    
    // AIDA
    // AidaOnlineSpectra* aidaOnline = new AidaOnlineSpectra();
    
    // bPlast
    // bPlastOnlineSpectra* onlinebplast = new bPlastOnlineSpectra();
    
    // Germanium
    // GermaniumOnlineSpectra* onlinege = new GermaniumOnlineSpectra();
    
    // FRS
    // FrsOnlineSpectra* onlinefrs = new FrsOnlineSpectra();
    // FrsRawSpectra* frsrawspec = new FrsRawSpectra();
    // FrsCalSpectra* frscalspec = new FrsCalSpectra();
    // FrsAnalysisSpectra* frsanlspec = new FrsAnalysisSpectra(frs,mw,tpc,music,labr,sci,id,si,mrtof,range,FrsGates);
    
    // TimeMachine
    // TimeMachineOnline* tms = new TimeMachineOnline();
    // TString b = "Fatima";
    // TString c = "Aida";
    // TString d = "bPlast";
    // std::vector a {b, c, d};
    // tms->SetDetectorSystems(a);

    
    // Add 'Online Spectra' tasks to FairRun.
    run->AddTask(onlinefatima);
    // run->AddTask(aidaOnline);
    // run->AddTask(onlinebplast);
    // run->AddTask(onlinege);
    // run->AddTask(onlinefrs);
    // run->AddTask(frsrawspec);
    // run->AddTask(frscalspec);
    // run->AddTask(frsanlspec);
    // run->AddTask(tms);

    // ---------------------------------------------------------------------------------------- //
    // *** Correlations *********************************************************************** //

    // FrsFatimaCorrelations* frsfatimacorr = new FrsFatimaCorrelations(FrsGates, FatimaPrompt, CorrMap);

    // FrsAidaCorrelations* frsaidacorr = new FrsAidaCorrelations(FrsGates, CorrMap);

    // Add 'Correlations' task to FairRun.
    // run->AddTask(frsfatimacorr);
    // run->AddTask(frsaidacorr);

    
    
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