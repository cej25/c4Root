typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fatima_onion_t fatima;
    EXT_STR_h101_bplast_onion_t bplast;
    EXT_STR_h101_aida_onion_t aida;
    EXT_STR_h101_frsmain_onion_t frsmain;
    EXT_STR_h101_frstpc_onion_t frstpc;
    EXT_STR_h101_frsuser_onion_t frsuser;
    EXT_STR_h101_frsvftx_onion_t frsvftx;
    //EXT_STR_h101_germanium_onion_t germanium;
} EXT_STR_h101;

void run_online(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1)
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
    //"trans://lxg1257"
    //TString filename = "trans://lxg1257";
    TString filename = "~/lustre/gamma/DESPEC_NOV23_FILES/ts/Ubeam_0006_000*.lmd";
    TString outputpath = "output";
    TString outputFileName = outputpath + ".root";

    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 5000; // Port number for online visualisation, e.g. lxgXXXX:8886
     
    TString ntuple_options = "UNPACK"; // "RAW"? "time=stitch=1000"? can we time-stitch files here pls?
    TString ucesb_path = "/u/cjones/c4Root/unpack/exps/NovTest/NovTest --allow-errors --input-buffer=200Mi --event-sizes"; // CEJ: R3B used input-buffer, can't see in ucesb doc however...
    std::string ucesb_dir = "/u/cjones/ucesb";
    ucesb_path.ReplaceAll("//","/");

    // Create online run
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName)); // CEJ: we should try GetRootFile() method to create folders in Task
    run->ActivateHttpServer(refresh, port);

    // Load ucesb structure
    EXT_STR_h101 ucesb_struct;

    // Create source using ucesb for input
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);


    
    
    // Runtime data baserate  
    
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    

    // Add readers

    FatimaReader* unpackfatima = new FatimaReader((EXT_STR_h101_fatima_onion*)&ucesb_struct.fatima, offsetof(EXT_STR_h101, fatima));
    unpackfatima->SetInputFileFineTimeHistos("/u/despec/BB7-c4-test/macros/fine_time_histos_111223_fatima.root");
    //unpackfatima->DoFineTimeCalOnline("/u/despec/BB7-c4-test/macros/fine_time_histos_111223_fatima.root",50000000);


    TAidaConfiguration::SetBasePath("/u/despec/BB7-c4-test/macros/AIDA");
    AidaReader* unpackaida = new AidaReader((EXT_STR_h101_aida_onion*)&ucesb_struct.aida, offsetof(EXT_STR_h101, aida));

    bPlastReader* unpackbplast = new bPlastReader((EXT_STR_h101_bplast_onion*)&ucesb_struct.bplast, offsetof(EXT_STR_h101, bplast));
    //unpackbplast->DoFineTimeCalOnline("/u/cjones/c4Root/config/NovTest/fine_time_histos_111223_bplast.root",10000000);
    unpackbplast->SetInputFileFineTimeHistos("/u/cjones/c4Root/config/NovTest/fine_time_histos_111223_bplast.root");

    FrsMainReader* unpackfrsmain = new FrsMainReader((EXT_STR_h101_frsmain_onion*)&ucesb_struct.frsmain, offsetof(EXT_STR_h101, frsmain));
    FrsTPCReader* unpackfrstpc = new FrsTPCReader((EXT_STR_h101_frstpc_onion*)&ucesb_struct.frstpc, offsetof(EXT_STR_h101, frstpc));
    FrsUserReader* unpackfrsuser = new FrsUserReader((EXT_STR_h101_frsuser_onion*)&ucesb_struct.frsuser, offsetof(EXT_STR_h101, frsuser));
    FrsVFTXReader* unpackfrsvftx = new FrsVFTXReader((EXT_STR_h101_frsvftx_onion*)&ucesb_struct.frsvftx, offsetof(EXT_STR_h101, frsvftx));


    //GermaniumReader* unpackgermanium = new GermaniumReader((EXT_STR_h101_GERMANIUM_onion*)&ucesb_struct.germanium, offsetof(EXT_STR_h101, germanium));

    // Add readers


    // Add readers
    unpackbplast->SetOnline(true);
    unpackaida->SetOnline(true);
    unpackfatima->SetOnline(true);
    //unpackgermanium->SetOnline(true);SetTimeMachineChannels

    unpackfrsmain->SetOnline(true);
    unpackfrstpc->SetOnline(true);
    unpackfrsuser->SetOnline(true);
    unpackfrsvftx->SetOnline(true);

    // Add readers
    source->AddReader(unpackheader);
    source->AddReader(unpackfatima);
    source->AddReader(unpackaida);
    source->AddReader(unpackbplast);
    //source->AddReader(unpackgermanium);
    
    source->AddReader(unpackfrsmain);
    source->AddReader(unpackfrstpc);
    source->AddReader(unpackfrsuser);
    source->AddReader(unpackfrsvftx);

    // Runtime data base

    // Add analysis task
    FatimaRaw2Cal * calfatima = new FatimaRaw2Cal();
    calfatima->SetDetectorMapFile("/u/cjones/c4Root/config/NovTest/fatima_alloc.txt");
    calfatima->PrintDetectorMap();
    calfatima->SetDetectorCalFile("/u/cjones/c4Root/config/NovTest/fatima_cal.txt");
    calfatima->PrintDetectorCal();
    calfatima->SetTimeMachineChannels(16,17);

    // Aida processing tasks
    AidaUnpack2Cal* aidaCalibrator = new AidaUnpack2Cal();
    aidaCalibrator->SetAidaTimeMachineChannels(4,3);
    AidaCal2Hit* aidaHitter = new AidaCal2Hit();

    bPlastRaw2Cal* calbplast = new bPlastRaw2Cal();
    calbplast->SetDetectorMapFile("/u/cjones/c4Root/config/NovTest/bplast_allocation_111223.txt");
    calbplast->SetTimeMachineChannels(68,67);

    //GermaniumRaw2Cal * ge_calib = new GermaniumRaw2Cal();
    //ge_calib->SetDetectorMapFile("/u/despec/BB7-c4-test/c4Root/Germanium_Detector_Map.txt");
    //ge_calib->PrintDetectorMap();

    // CEJ: FRS issue possibly in Reader step
    // Main and TPC checked, should be fine...
    FrsMainRaw2Cal* calfrsmain = new FrsMainRaw2Cal();
    FrsTPCRaw2Cal* calfrstpc = new FrsTPCRaw2Cal();
    FrsUserRaw2Cal* calfrsuser = new FrsUserRaw2Cal();
    FrsVFTXRaw2Cal* calfrsvftx = new FrsVFTXRaw2Cal();

    
    aidaCalibrator->SetOnline(true);
    aidaHitter->SetOnline(true);
    calfatima->SetOnline(true);
    calbplast->SetOnline(true);
    //ge_calib->SetOnline(false);

    calfrsmain->SetOnline(true);
    calfrstpc->SetOnline(true);
    calfrsuser->SetOnline(true);
    calfrsvftx->SetOnline(true);
    
    run->AddTask(calfatima);
    run->AddTask(aidaCalibrator);
    run->AddTask(aidaHitter);
    run->AddTask(calbplast);
    //run->AddTask(ge_calib);

    run->AddTask(calfrsmain);
    run->AddTask(calfrstpc);
    run->AddTask(calfrsuser);
    run->AddTask(calfrsvftx);

    // CEJ: currently some segault after 1 event in Cal2Hit
    FrsCal2Hit* hitfrs = new FrsCal2Hit();

    hitfrs->SetOnline(false); 

    run->AddTask(hitfrs);




    // Add online plotters:
    FatimaOnlineSpectra * onlinefatima = new FatimaOnlineSpectra();

    AidaOnlineSpectra* aidaOnline = new AidaOnlineSpectra();
    bPlastOnlineSpectra* onlinebplast = new bPlastOnlineSpectra();
    //GermaniumOnlineSpectra* onlinege = new GermaniumOnlineSpectra();
    
    TimeMachineOnline* tms = new TimeMachineOnline();
    TString b = "Fatima";
    TString c = "bPlast";
    TString d = "Aida";
    std::vector a {b,c,d};
    tms->SetDetectorSystems(a);

    FrsOnlineSpectra* onlinefrs = new FrsOnlineSpectra();

   //run->AddTask(onlinefrs);


    run->AddTask(tms);
    run->AddTask(onlinefatima);
    run->AddTask(aidaOnline);
    run->AddTask(onlinebplast);
    //run->AddTask(onlinege);

    run->AddTask(onlinefrs);

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
