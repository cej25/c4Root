#include <TROOT.h>

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fatimavme_onion_t fatimavme;
   
} EXT_STR_h101;


void run_fatimavme(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1)
{   
    // CEJ: feels like we should define this variable and use it all over the place..
    TString fExpName = "s452";

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

    //TString filename = "stream://x86l-116"
    //TString filename = "trans://lxg1257"
    TString filename = "~/lustre/gamma/DESPEC_S452_FILES/newts/S452f074_0103.lmd";
    TString outputpath = "output";
    TString outputFileName = outputpath + ".root";

    Int_t refresh = 1; // Refresh rate for online histograms
    // 5000 has firewall access
    Int_t port = 5000; // Port number for online visualisation, e.g. lxgXXXX:8886
     
    TString ntuple_options = "UNPACK";
    TString c4Root_path = "/u/cjones/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --allow-errors --input-buffer=200Mi --event-sizes";
    std::string ucesb_dir = "/u/cjones/ucesb";
    ucesb_path.ReplaceAll("//","/");

    // Create online run
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName));
    run->ActivateHttpServer(refresh, port);

    // Load ucesb structure
    EXT_STR_h101 ucesb_struct;

    // Create source using ucesb for input
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);
 
    
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));

    FatimaVmeReader* unpackfatimavme = new FatimaVmeReader((EXT_STR_h101_fatimavme_onion*)&ucesb_struct.fatimavme, offsetof(EXT_STR_h101, fatimavme));
   
    unpackfatimavme->SetOnline(false);
  
    source->AddReader(unpackfatimavme);
  

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

    /* ------------------------------------------------------------- */
    /* -------- Finish Macro --------------------------------------- */
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
   /* ------------------------------------------------------------- */
}