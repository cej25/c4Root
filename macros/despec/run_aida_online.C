typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_aida_onion_t aida;
    EXT_STR_h101_BPLAST_onion_t bplast;
} EXT_STR_h101;

void run_aida_online(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1)
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

    TString filename = "~/lustre/gamma/DESPEC_S452_FILES/newts/S452f103_0037.lmd";
    TString outputpath = "~/run_online_ge_test";
    TString outputFileName = outputpath + ".root";

    Int_t refresh = 10; // Refresh rate for online histograms
    Int_t port = 5999; // Port number for online visualisation, e.g. lxgXXXX:8886
     
    TString ntuple_options = "UNPACK:aida,RAW,NOTRIGEVENTNO"; // "RAW"? "time=stitch=1000"? can we time-stitch files here pls?
    TString ucesb_dir = getenv("UCESB_DIR"); // .bashrc
    TString ucesb_path = ucesb_dir + "/s452/s452 --allow-errors --input-buffer=200Mi"; // CEJ: R3B used input-buffer, can't see in ucesb doc however...
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
   
    //GermaniumReader* unpackgermanium = new GermaniumReader((EXT_STR_h101_GE_FEBEX_onion*)&ucesb_struct.germanium, offsetof(EXT_STR_h101, germanium));
    AidaReader* unpackaida = new AidaReader((EXT_STR_h101_aida_onion*)&ucesb_struct.aida, offsetof(EXT_STR_h101, aida));
    bPlastReader* unpackbplast = new bPlastReader((EXT_STR_h101_BPLAST_onion*)&ucesb_struct.bplast, offsetof(EXT_STR_h101, bplast));

    // Add readers
    //unpackgermanium->SetOnline(false);
    //source->AddReader(unpackgermanium);

    
    unpackaida->SetOnline(false);
    source->AddReader(unpackaida);
    unpackbplast->SetOnline(false);
    source->AddReader(unpackbplast);

    run->SetSource(source);

    // Runtime data base
    FairRuntimeDb* rtdb = run->GetRuntimeDb();


    // Add analysis task
    //GermaniumOnlineSpectra* online = new GermaniumOnlineSpectra();
    //run->AddTask(online);

    // Initialise
    run->Init();
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "Germanium online port server: " << port << endl;
    cout << "\n\n" << endl;

    // Run
    run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev); // no idea

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
