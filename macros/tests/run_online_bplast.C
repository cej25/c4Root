typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_bplast_onion_t bplast;
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

    TString filename = "trans://lxg1257";
    // TString filename = "/lustre/gamma/DESPEC_NOV23_FILES/ts/it1_0006_0006.lmd";
    // TString filename = "/u/jbormans/bplast/NovTest/it1_0006_0004.lmd";
    TString outputpath = "outputbplast";
    TString outputFileName = outputpath + ".root";

    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 5600; // Port number for online visualisation, e.g. lxgXXXX:8886
    // Bool_t fPrintStatistics = true; // Print statistics at the end of the run -- diagnostics
     
    TString ntuple_options = "UNPACK"; // "RAW"? "time=stitch=1000"? can we time-stitch files here pls?
    TString ucesb_dir = getenv("UCESB_DIR"); // CEJ: R3B used input-buffer, can't see in ucesb doc however...
    TString ucesb_path = "~/c4Root/unpack/exps/onlybPlast/onlybPlast --allow-errors --input-buffer=200Mi --event-sizes"; // CEJ: R3B used input-buffer, can't see in ucesb doc however...
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
    bPlastReader* unpackbplast = new bPlastReader((EXT_STR_h101_bplast_onion*)&ucesb_struct.bplast, offsetof(EXT_STR_h101, bplast));
    unpackbplast->SetInputFileFineTimeHistos("../../config/s100/bplast/fine_time_histos_s100.root");
    // unpackbplast->DoFineTimeCalOnline("../../config/s100/bplast/fine_time_histos_s100.root",1000000);

    // Add readers
    unpackbplast->SetOnline(true);
    source->AddReader(unpackbplast);


    bPlastRaw2Cal * calbplast = new bPlastRaw2Cal();
    calbplast->SetDetectorMapFile("../../config/s100/bplast/bplast_mapping_s100.txt");
    calbplast->SetOnline(true);


    // Add online plotters:
    bPlastOnlineSpectra* onlinebplast = new bPlastOnlineSpectra();
    run->AddTask(calbplast);
    run->AddTask(onlinebplast);

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
