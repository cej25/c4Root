typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_germanium_onion_t germanium; // why can't it find this :()
    EXT_STR_h101_fatima_onion_t fatima;
    EXT_STR_h101_bplast_onion_t bplast;
    EXT_STR_h101_aida_onion_t aida;
} EXT_STR_h101;


void run_online_jeroen(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1)
{   

    TString cRunId = Form("%04d", fRunId);
    TString cExpId = Form("%03d", fExpId);
    // fPrintStatistics = true;

    TStopwatch timer;

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    timer.Start();

    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);

    //stream://x86l-116
    TString filename = "/lustre/gamma/DESPEC_NOV23_FILES/ts/it1_0006_0006.lmd";
    // TString filename = "/u/jbormans/bplast/NovTest/it1_0006_0004.lmd";
    TString outputpath = "outputtest";
    TString outputFileName = outputpath + ".root";

    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 5500; // Port number for online visualisation, e.g. lxgXXXX:8886
    // Bool_t fPrintStatistics = true; // Print statistics at the end of the run -- diagnostics
     
    TString ntuple_options = "UNPACK"; // "RAW"? "time=stitch=1000"? can we time-stitch files here pls?
    TString ucesb_dir = getenv("UCESB_DIR"); // CEJ: R3B used input-buffer, can't see in ucesb doc however...
    TString ucesb_path = "~/c4Root/unpack/exps/NovTest/NovTest --allow-errors --input-buffer=200Mi --event-sizes"; // CEJ: R3B used input-buffer, can't see in ucesb doc however...
    ucesb_path.ReplaceAll("//","/");

    // Create online run
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1); // no idea, does it even matter for this
    run->SetSink(new FairRootFileSink(outputFileName));
    run->ActivateHttpServer(refresh, port);

    // Load ucesb structure
    EXT_STR_h101 ucesb_struct;

    // Create source using ucesb for input
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);


    
    
    // Runtime data base
    FairRuntimeDb* rtdb = run->GetRuntimeDb();
    
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    
    // Add readers
    
    FatimaReader* unpackfatima = new FatimaReader((EXT_STR_h101_fatima_onion*)&ucesb_struct.fatima, offsetof(EXT_STR_h101, fatima));
    unpackfatima->SetInputFileFineTimeHistos("~/c4Root/config/NovTest/fine_time_histos_pos.root");
    // unpackfatima->DoFineTimeCalOnline("/u/jlarsson/Documents/OnlineAnalysisCode/BB7Test/fine_time_histos.root",10000000);


    // TAidaConfiguration::SetBasePath("/u/jbormans/bplast/NovTest/AIDA");
    // AidaReader* unpackaida = new AidaReader((EXT_STR_h101_aida_onion*)&ucesb_struct.aida, offsetof(EXT_STR_h101, aida));

    bPlastReader* unpackbplast = new bPlastReader((EXT_STR_h101_bplast_onion*)&ucesb_struct.bplast, offsetof(EXT_STR_h101, bplast));
    unpackbplast->SetInputFileFineTimeHistos("~/c4Root/config/NovTest/fine_time_histos_pos.root");
    // unpackbplast->DoFineTimeCalOnline("/u/jbormans/bplast/NovTest/fine_time_histos.root",1000000);

    //GermaniumReader* unpackgermanium = new GermaniumReader((EXT_STR_h101_GERMANIUM_onion*)&ucesb_struct.germanium, offsetof(EXT_STR_h101, germanium));

    // Add readers
    
    unpackbplast->SetOnline(true);

//    unpackaida->SetOnline(true);
    unpackfatima->SetOnline(true);
    //unpackgermanium->SetOnline(true);SetTimeMachineChannels



    // Add readers
    source->AddReader(unpackheader);
    source->AddReader(unpackfatima);
//    source->AddReader(unpackaida);
    source->AddReader(unpackbplast);
    //source->AddReader(unpackgermanium);

    // Add analysis task

    FatimaRaw2Cal * calfatima = new FatimaRaw2Cal();
    calfatima->SetDetectorMapFile("../../config/NovTest/bplast_alloc_pos.txt");
   // calfatima->PrintDetectorMap();
    // calfatima->SetTimeMachineChannels(16,17);


    // Aida processing tasks
//    AidaUnpack2Cal* aidaCalibrator = new AidaUnpack2Cal();
    // aidaCalibrator->SetAidaTimeMachineChannels(4,3);
//    AidaCal2Hit* aidaHitter = new AidaCal2Hit();

    bPlastRaw2Cal * calbplast = new bPlastRaw2Cal();
    calbplast->SetDetectorMapFile("../../config/NovTest/bplast_alloc_pos.txt");
    // calbplast->PrintDetectorMap();
    // calbplast->SetTimeMachineChannels(36,35);

    //GermaniumRaw2Cal * ge_calib = new GermaniumRaw2Cal();

    //ge_calib->SetDetectorMapFile("/u/despec/BB7-c4-test/c4Root/Germanium_Detector_Map.txt");
    //ge_calib->PrintDetectorMap();

    //ge_calib->SetDetectorCalFile("/u/despec/BB7-c4-test/c4Root/Germanium_Energy_Calibration.txt");
    //ge_calib->PrintDetectorCal();




    
    
//    aidaCalibrator->SetOnline(true);
//    aidaHitter->SetOnline(true);
    //ge_calib->SetOnline(true);
    calfatima->SetOnline(true);
    calbplast->SetOnline(true);
    

    
    run->AddTask(calfatima);
//    run->AddTask(aidaCalibrator);
//    run->AddTask(aidaHitter);

    //run->AddTask(ge_calib);
    




    // Add online plotters:
    FatimaOnlineSpectra * onlinefatima = new FatimaOnlineSpectra();

//    AidaOnlineSpectra* aidaOnline = new AidaOnlineSpectra();
    bPlastOnlineSpectra* onlinebplast = new bPlastOnlineSpectra();
    //GermaniumOnlineSpectra* onlinege = new GermaniumOnlineSpectra();
    WhiterabbitCorrelationOnline* wrabbit = new WhiterabbitCorrelationOnline();

    wrabbit->SetDetectorSystems({"Fatima","bPlast"});

    // Add nearline plotter

    // AidaNearlineSpectra* aidaNearline = new AidaNearlineSpectra();
    // bPlastNearlineSpectra* bplastNearline = new bPlastNearlineSpectra();

    
    // TimeMachineOnline* tms = new TimeMachineOnline();
    // TString b = "Fatima";
    // TString c = "bPlast";
    // TString d = "Aida";
    // std::vector a {b,c,d};
    // tms->SetDetectorSystems(a);


    // run->AddTask(tms);
    run->AddTask(onlinefatima);
//    run->AddTask(aidaOnline);
    run->AddTask(calbplast);
    run->AddTask(onlinebplast);
    run->AddTask(wrabbit);
    //run->AddTask(onlinege);

    // run->AddTask(aidaNearline);
    // run->AddTask(bplastNearline);


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


    // Finish
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
}
