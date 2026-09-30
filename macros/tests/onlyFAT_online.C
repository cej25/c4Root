typedef struct EXT_STR_h101_t

{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fatima_onion_t fatima;
} EXT_STR_h101;

void onlyFAT_online()
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

    //stream://x86l-116

    TString inputstream ="~/Analysis/LISA/lmd/tamex_0020_0001.lmd" ;
    TString outputpath = "./";
    TString outputFileName = outputpath + "output.root";

    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 1111; // Port number for online visualisation, e.g. lxgXXXX:8886
     
    TString ntuple_options = "UNPACK"; // "RAW"? "time=stitch=1000"? can we time-stitch files here pls?
    TString ucesb_path = "/home/calum/Software/c4Root/unpack/exps/onlyFATIMA/onlyFATIMA --allow-errors --input-buffer=200Mi";
    std::string ucesb_dir = "/home/calum/Software/ucesb";
    ucesb_path.ReplaceAll("//","/");

    // Create online run
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1); // no idea, does it even matter for this
    run->SetSink(new FairRootFileSink(outputFileName));
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);

    // Load ucesb structure
    EXT_STR_h101 ucesb_struct;

    // Create source using ucesb for input
    UcesbSource* source = new UcesbSource(inputstream, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);
    
    TFatimaTwinpeaksConfiguration::SetDetectorConfigurationFile("/home/calum/Analysis/LISA/configs/labr_mapping.txt");

    
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);

    FatimaReader* unpackfatima = new FatimaReader((EXT_STR_h101_fatima_onion*)&ucesb_struct.fatima, offsetof(EXT_STR_h101, fatima));
    unpackfatima->DoFineTimeCalOnline("~/Analysis/LISA/configs/fine_time_histos_300926_labr.root",10000);
    // unpackfatima->SetInputFileFineTimeHistos("/u/despec/s100_online/fatimatimingtest/fine_time_histos_01032024_fatima.root");

    unpackfatima->SetOnline(true);
    
    
    
    source->AddReader(unpackfatima);


    FatimaRaw2Cal * calfatima = new FatimaRaw2Cal();
    //calfatima->SetDetectorMapFile("/u/despec/s100_online/fatimatimingtest/fatima_alloc.txt");
    calfatima->PrintDetectorMap();
    //calfatima->SetDetectorCalFile("/u/jbormans/fatima/fatima_cal.txt");
    //calfatima->PrintDetectorCal();
    calfatima->SetOnline(true);
    //calfatima->SetTimeMachineChannels(16,17);

    run->AddTask(calfatima);


    // Add online plotters:
    FatimaOnlineSpectra * onlinefatima = new FatimaOnlineSpectra();
    onlinefatima->SetBinningSlowToT(1500,570.1,700.1);
    onlinefatima->SetBinningFastToT(1000,0.1,100.1);
    onlinefatima->SetBinningEnergy(1500,0.1,1500.1);

    std::vector<int> fat_dets = {1,2};
    onlinefatima->SetDetectorsToPlot(fat_dets);
    
    std::vector<int> fat_ref_dets = {1};
    // onlinefatima->SetReferenceDetectorsForTimeDifferences(fat_ref_dets);

    run->AddTask(onlinefatima);


    /*
    std::vector<int> dets = {0,1,2,3,4,5,6,7,8,9,10,11};

    FatimaTimingAnalysis * anl_fatima = new FatimaTimingAnalysis();
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
    cout << "Data stream is: " << inputstream << endl;
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
    gApplication->Terminate(0);
}
