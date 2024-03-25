typedef struct EXT_STR_h101_t
{
    EXT_STR_h101_lisa_onion_t lisa;
} EXT_STR_h101;

void run_lisa_online(const Int_t nev = -1, const Int_t fRunId = 1, const Int_t fExpId = 1)
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

    TString filename = "~/LISA/lustre/despec/lisa/eris_241Am_1000V_0094_0001.lmd";
    TString outputpath = "/home/lisa_offline/test_online";
    TString outputFilename = outputpath + "eris_test.root";

    Int_t refresh = 10;
    Int_t port = 5999;

    TString ntuple_options = "UNPACK";
    //TString ucesb_dir = getenv("UCESB_DIR");
    TString ucesb_dir = getenv("HOME");
    TString temp_path = ucesb_dir + "/software/c4Root/unpack/exps";
    //TString ucesb_path = ucesb_dir + "/lisa/lisa --allow-errors --input-buffer=200Mi";
    TString ucesb_path = temp_path + "/lisa/lisa --allow-errors --input-buffer=200Mi";
    ucesb_path.ReplaceAll("//","/");

    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvntHeader = new EventHeader();
    run->SetEventHeader(EvntHeader);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFilename));
    run->ActivateHttpServer(refresh, port);

    EXT_STR_h101 ucesb_struct;

    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);

    LisaReader* unpacklisa = new LisaReader((EXT_STR_h101_lisa_onion*)&ucesb_struct.lisa, offsetof(EXT_STR_h101, lisa));

    unpacklisa->SetOnline(false); //false= write to a tree; true=doesn't write to tree
    source->AddReader(unpacklisa);

    run->SetSource(source);

    FairRuntimeDb* rtdb = run->GetRuntimeDb();

    // Add analysis task here at some point

    //LisaOnlineSpectra* onlinelisa = new LisaOnlineSpectra();

    //run->AddTask(onlinelisa);

    run->Init();
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "LISA online port server: " << port << endl;
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
    std::cout << "Output file is " << outputFilename << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
    gApplication->Terminate();


}