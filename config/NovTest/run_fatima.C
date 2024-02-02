typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_GERMANIUM_onion_t germanium; // why can't it find this :()
    EXT_STR_h101_FATIMA_onion_t fatima;
    EXT_STR_h101_BPLAST_onion_t bplast;
    EXT_STR_h101_aida_onion_t aida;
} EXT_STR_h101;

void run_fatima(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1)
{   

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

    //stream://x86l-116
    TString filename = "/u/despec/lustre/despec/fattest2023/Test_60Co_CFD_27Nov23_0240.lmd";
    TString outputpath = "/u/despec/lustre/gamma/DESPEC_Timing_Test1/S4/Nov23/Tree/FairRoot/Test_60Co_CFD_27Nov23_0240.lmd";
    TString outputFileName = outputpath + ".root";

    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 5999; // Port number for online visualisation, e.g. lxgXXXX:8886
     
    TString ntuple_options = "UNPACK"; // "RAW"? "time=stitch=1000"? can we time-stitch files here pls?
    TString ucesb_path = "/u/despec/BB7-c4-test/c4Root/unpack/exps/NovTest/NovTest --input-buffer=200Mi --data --event-sizes"; // CEJ: R3B used input-buffer, can't see in ucesb doc however...
    std::string ucesb_dir = "/u/despec/BB7-c4-test/ucesb";
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

    FatimaReader* unpackfatima = new FatimaReader((EXT_STR_h101_FATIMA_onion*)&ucesb_struct.fatima, offsetof(EXT_STR_h101, fatima));
    unpackfatima->SetInputFileFineTimeHistos("/u/despec/lustre/gamma/DESPEC_Timing_Test1/S4/Nov23/Tree/FairRoot/fine_time_histos_Nov23.root");
    //unpackfatima->DoFineTimeCalOnline("/u/despec/lustre/gamma/DESPEC_Timing_Test1/S4/Nov23/Tree/FairRoot/fine_time_histos_Nov23.root",1000000);


    //TAidaConfiguration::SetBasePath("/u/despec/BB7-c4-test/macros/AIDA");
    //AidaReader* unpackaida = new AidaReader((EXT_STR_h101_aida_onion*)&ucesb_struct.aida, offsetof(EXT_STR_h101, aida));

    //bPlastReader* unpackbplast = new bPlastReader((EXT_STR_h101_BPLAST_onion*)&ucesb_struct.bplast, offsetof(EXT_STR_h101, bplast));
    //unpackbplast->SetInputFileFineTimeHistos("/u/despec/BB7-c4-test/macros/fine_time_histos_S450.root");

    //GermaniumReader* unpackgermanium = new GermaniumReader((EXT_STR_h101_GERMANIUM_onion*)&ucesb_struct.germanium, offsetof(EXT_STR_h101, germanium));

    // Add readers


    // Add readers


    
    //unpackbplast->SetOnline(true);
    //unpackaida->SetOnline(true);
    unpackfatima->SetOnline(false);
    //unpackgermanium->SetOnline(true);SetTimeMachineChannels



    // Add readers
    source->AddReader(unpackheader);
    source->AddReader(unpackfatima);

    //source->AddReader(unpackaida);
    //source->AddReader(unpackbplast);
    //source->AddReader(unpackgermanium);
    

    // Add readers


    // Runtime data base



    // Add analysis task

    FatimaRaw2Cal * calfatima = new FatimaRaw2Cal();
    calfatima->SetDetectorMapFile("/u/despec/BB7-c4-test/macros/fatima_alloc.txt");
    calfatima->PrintDetectorMap();
    //calfatima->SetTimeMachineChannels(16,17);


    // Aida processing tasks
    //AidaUnpack2Cal* aidaCalibrator = new AidaUnpack2Cal();
    //aidaCalibrator->SetAidaTimeMachineChannels(4,3);
    //AidaCal2Hit* aidaHitter = new AidaCal2Hit();

    //bPlastRaw2Cal * calbplast = new bPlastRaw2Cal();
    //calbplast->SetDetectorMapFile("/u/despec/BB7-c4-test/macros/bplast_alloc.txt");
    //calbplast->SetTimeMachineChannels(36,35);

    //GermaniumRaw2Cal * ge_calib = new GermaniumRaw2Cal();

    //ge_calib->SetDetectorMapFile("/u/despec/BB7-c4-test/c4Root/Germanium_Detector_Map.txt");
    //ge_calib->PrintDetectorMap();

    //ge_calib->SetDetectorCalFile("/u/despec/BB7-c4-test/c4Root/Germanium_Energy_Calibration.txt");
    //ge_calib->PrintDetectorCal();




    
    
    //aidaCalibrator->SetOnline(true);
    //aidaHitter->SetOnline(true);
    //ge_calib->SetOnline(true);
    calfatima->SetOnline(false);
    //calbplast->SetOnline(true);
    

    
    run->AddTask(calfatima);
    //run->AddTask(aidaCalibrator);
   // run->AddTask(aidaHitter);
    //run->AddTask(calbplast);
    //run->AddTask(ge_calib);
    




    // Add online plotters:
    FatimaOnlineSpectra * onlinefatima = new FatimaOnlineSpectra();

    //AidaOnlineSpectra* aidaOnline = new AidaOnlineSpectra();
   //bPlastOnlineSpectra* onlinebplast = new bPlastOnlineSpectra();
    //GermaniumOnlineSpectra* onlinege = new GermaniumOnlineSpectra();
    
    //TimeMachineOnline* tms = new TimeMachineOnline();
    //TString b = "Fatima";
    //TString c = "bPlast";
    //TString d = "Aida";
    //std::vector a {b,c,d};
    //tms->SetDetectorSystems(a);


    //run->AddTask(tms);
    run->AddTask(onlinefatima);
    //run->AddTask(aidaOnline);
    //run->AddTask(onlinebplast);
    //run->AddTask(onlinege);

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
