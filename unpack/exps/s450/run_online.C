typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_GERMANIUM_onion_t germanium; // why can't it find this :()
    EXT_STR_h101_FATIMA_onion_t fatima;

} EXT_STR_h101;

void run_ge_online(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1)
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

    TString filename = "/u/jlarsson/Documents/OnlineAnalysisCode/c4_S450/s450f0055_0036.lmd";
    TString outputpath = "/u/jlarsson/Documents/OnlineAnalysisCode/c4_S450/output";
    TString outputFileName = outputpath + ".root";

    Int_t refresh = 10; // Refresh rate for online histograms
    Int_t port = 5999; // Port number for online visualisation, e.g. lxgXXXX:8886
     
    TString ntuple_options = "UNPACK"; // "RAW"? "time=stitch=1000"? can we time-stitch files here pls?
    TString ucesb_path = "/u/jlarsson/Documents/OnlineAnalysisCode/c4Root/unpack/exps/s450/s450 --allow-errors --input-buffer=200Mi"; // CEJ: R3B used input-buffer, can't see in ucesb doc however...
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
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
   
    FatimaReader* unpackfatima = new FatimaReader((EXT_STR_h101_FATIMA_onion*)&ucesb_struct.fatima, offsetof(EXT_STR_h101, fatima));
    GermaniumReader* unpackgermanium = new GermaniumReader((EXT_STR_h101_GERMANIUM_onion*)&ucesb_struct.germanium, offsetof(EXT_STR_h101, germanium));
    unpackfatima->SetInputFileFineTimeHistos("/u/jlarsson/Documents/OnlineAnalysisCode/c4_S450/fine_time_histos_S450.root");
    //unpackfatima->DoFineTimeCalOnline("/u/jlarsson/Documents/OnlineAnalysisCode/c4_S450/fine_time_histos_S450.root",10000000);
    

    unpackgermanium->SetOnline(true);
    unpackfatima->SetOnline(true);



    // Add readers
    source->AddReader(unpackheader);
    source->AddReader(unpackgermanium);
    source->AddReader(unpackfatima);
    



    // Add analysis task
    GermaniumRaw2Cal * ge_calib = new GermaniumRaw2Cal();
    FatimaRaw2Cal * calfatima = new FatimaRaw2Cal();





    calfatima->SetDetectorMapFile("betaplast_alloc.txt");
    calfatima->PrintDetectorMap();
    ge_calib->SetDetectorMapFile("/u/jlarsson/Documents/OnlineAnalysisCode/c4_S450/Germ_det_map.txt");
    ge_calib->PrintDetectorMap();
    ge_calib->SetDetectorCalFile("/u/jlarsson/Documents/OnlineAnalysisCode/c4_S450/Germ_cals.txt");
    ge_calib->PrintDetectorCal();

    ge_calib->SetTimeMachineChannels(11,2,11,1);
    calfatima->SetTimeMachineChannels(135,136);

    //ge_calib->SetOnline(true);
    //calfatima->SetOnline(true);
    
    
    
    run->AddTask(ge_calib);
    run->AddTask(calfatima);
    


    GermaniumOnlineSpectra* onlinege = new GermaniumOnlineSpectra();
    run->AddTask(onlinege);


    // Add readers
    




    FatimaOnlineSpectra * onlinefatima = new FatimaOnlineSpectra();
    run->AddTask(onlinefatima);


    run->SetSource(source);
    // Runtime data base
    FairRuntimeDb* rtdb = run->GetRuntimeDb();

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
