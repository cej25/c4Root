typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_travmus_onion_t travmus;
} EXT_STR_h101;

void pareeksha_online(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1)
{   
    TString fExpName = "pareeksha";

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
    
    TString filename = "/u/cjones/lustre/gamma/LISA/data/travMUSIC_apr24/cs_170er_check_0170.lmd";
    TString outputpath = "";
    TString outputFilename = outputpath + "pareeksha_test.root";

    Int_t refresh = 10; // Refresh rate for online histograms
    Int_t port = 8080;
     
    TString ntuple_options = "UNPACK";
    TString c4Root_path = "/u/cjones/c4Root/";
    TString ucesb_path = c4Root_path + "unpack/exps/" + fExpName + "/" + fExpName + " --allow-errors --input-buffer=200Mi";
    ucesb_path.ReplaceAll("//","/");

    //set mapping/configuration

    // Create online run
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFilename));
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);

    // Load ucesb structure
    EXT_STR_h101 ucesb_struct;

    // Create source using ucesb for input
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);  

    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));

    FrsTravMusReader* unpacktravmus = new FrsTravMusReader((EXT_STR_h101_travmus_onion*)&ucesb_struct.travmus, offsetof(EXT_STR_h101, travmus));
    
    unpacktravmus->SetOnline(false); //false= write to a tree; true=doesn't write to tree
    
    //Add readers
    source->AddReader(unpacktravmus);

    // Initialise
    run->Init();
    //FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "LISA online port server: " << port << endl;
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
    std::cout << "Output file is " << outputFilename << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
   // gApplication->Terminate(0);
}
