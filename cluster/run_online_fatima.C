typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fatima_onion_t fatima;
} EXT_STR_h101;

void run_online_fatima(TString inputfile)
{   

    const Int_t nev = -1;
    const Int_t fRunId = 1;
    const Int_t fExpId = 1;

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

    //trans://x86l-116

    TString inputpath = "/lustre/despec/fattest2024/";
    //TString inputfile = "SourceRunEu_Feb5_0005.lmd";
    TString inputfilename = inputpath+inputfile;
    TString outputpath = "/lustre/gamma/jlarsson/FebCFDTamex/rootfiles/";
    TString outputFileName = outputpath + inputfile.ReplaceAll(".lmd",".root");

    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 5000; // Port number for online visualisation, e.g. lxgXXXX:8886
     
    TString ntuple_options = "UNPACK"; // "RAW"? "time=stitch=1000"? can we time-stitch files here pls?
    TString ucesb_path = "/lustre/gamma/jlarsson/c4code/c4Root/unpack/exps/onlyFATIMA/onlyFATIMA --allow-errors --input-buffer=200Mi"; // CEJ: R3B used input-buffer, can't see in ucesb doc however...
    std::string ucesb_dir = "/lustre/jlarsson/ucesb";
    ucesb_path.ReplaceAll("//","/");

    // Create online run
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1); // no idea, does it even matter for this
    run->SetSink(new FairRootFileSink(outputFileName));
    //run->ActivateHttpServer(refresh, port);

    // Load ucesb structure
    EXT_STR_h101 ucesb_struct;

    // Create source using ucesb for input
    UcesbSource* source = new UcesbSource(inputfilename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

    
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);

    FatimaReader* unpackfatima = new FatimaReader((EXT_STR_h101_fatima_onion*)&ucesb_struct.fatima, offsetof(EXT_STR_h101, fatima));
    //unpackfatima->DoFineTimeCalOnline("/lustre/gamma/jlarsson/FebCFDTamex/parameters/fine_time_histos_050224_fatima.root",50000000);
    unpackfatima->SetInputFileFineTimeHistos("/lustre/gamma/jlarsson/FebCFDTamex/parameters/fine_time_histos_190224_fatima.root");

    unpackfatima->SetOnline(true);
    
    
    
    source->AddReader(unpackfatima);


    FatimaRaw2Cal * calfatima = new FatimaRaw2Cal();
    calfatima->SetDetectorMapFile("/lustre/gamma/jlarsson/FebCFDTamex/parameters/fatima_alloc.txt");
    calfatima->PrintDetectorMap();
    calfatima->SetDetectorCalFile("/lustre/gamma/jlarsson/FebCFDTamex/parameters/fatima_cal_2102.txt");
    calfatima->PrintDetectorCal();
    calfatima->SetOnline(false);
    //calfatima->SetTimeMachineChannels(16,17);

    run->AddTask(calfatima);


    // Add online plotters:
    //FatimaOnlineSpectra * onlinefatima = new FatimaOnlineSpectra();
    //onlinefatima->SetBinningSlowToT(2000,570,660);
    //onlinefatima->SetBinningFastToT(1000,0,100);
    //onlinefatima->SetBinningEnergy(500,0,1500);
    //run->AddTask(onlinefatima);


    /*
    FatimaTimingAnalysis * anl_fatima = new FatimaTimingAnalysis();
    std::vector<int> dets = {0,1,2,3,4,5,6,7,8,9,10,11};
    anl_fatima->SetEnergies(778.9, 344.3, 30);
    anl_fatima->SetDetectorToAnalyze(&dets);
    anl_fatima->SetBinningSlowToT(2000,570,660);
    anl_fatima->SetBinningFastToT(1000,0,100);
    anl_fatima->SetBinningEnergy(500,0,1500);
    anl_fatima->SetBinning_dT(1000, -20, 20);
    run->AddTask(anl_fatima);

    FatimaTimingAnalysis * anl_fatima_antidelayed = new FatimaTimingAnalysis();
    anl_fatima_antidelayed->SetEnergies(344.3, 778.9, 30);
    anl_fatima_antidelayed->SetDetectorToAnalyze(&dets);
    anl_fatima_antidelayed->SetBinningSlowToT(2000,570,660);
    anl_fatima_antidelayed->SetBinningFastToT(1000,0,100);
    anl_fatima_antidelayed->SetBinningEnergy(500,0,1500);
    anl_fatima_antidelayed->SetBinning_dT(1000, -20, 20);
    run->AddTask(anl_fatima_antidelayed);
    */

    // Initialise
    run->Init();    
    
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << inputfile << endl;
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
    gApplication->Terminate(0);
}
