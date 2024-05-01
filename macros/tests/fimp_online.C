typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fimp_onion_t fimp;
} EXT_STR_h101;

void fimp_online(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1)
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
    
    TString filename = "~/fimp/*.lmd";
    TString outputFilename = "fimp_test.root";	

    Int_t refresh = 10; // Refresh rate for online histograms
    Int_t port = 8080;
     
    TString ntuple_options = "UNPACK";
    TString temp_path = "/u/cjones/c4Root/unpack/exps"; //at some point move to common computer
    TString ucesb_path = temp_path + "/fimp/fimp --allow-errors --input-buffer=200Mi";
    ucesb_path.ReplaceAll("//","/");

    //set mapping
    //TFimpConfiguration::SetMappingFile("~/c4Root/*");

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

    FimpReader* unpackfimp = new FimpReader((EXT_STR_h101_fimp_onion*)&ucesb_struct.fimp, offsetof(EXT_STR_h101, fimp));
    
    unpackfimp->SetOnline(false); //false= write to a tree; true=doesn't write to tree
    source->AddReader(unpackfimp);

    FimpRaw2Cal* calfimp = new FimpRaw2Cal();
    unpackfimp->SetOnline(false);
    run->AddTask(calfimp);

    // Add analysis task here at some point
    //FimpOnlineSpectra* onlinefimp = new FimpOnlineSpectra();
    //run->AddTask(onlinefimp);

    // Initialise
    run->Init();

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "FIMP online port server: " << port << endl;
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
