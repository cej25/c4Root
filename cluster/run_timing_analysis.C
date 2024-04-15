typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fatima_onion_t fatima;
} EXT_STR_h101;

std::vector<int> dets = {0,1};


void Add_Coinc_Analysis(FairRunAna* run, double E1, double E2){

    FatimaTimingAnalysis * anl_fatima = new FatimaTimingAnalysis();
    //anl_fatima->SetDetectorTimeshifts("/lustre/gamma/jlarsson/FebCFDTamex/parameters/fatima_timeshifts.txt");
    anl_fatima->SetEnergies(E1, E2, 20);
    anl_fatima->SetDetectorToAnalyze(&dets);
    anl_fatima->SetBinningSlowToT(2000,570,660);
    anl_fatima->SetBinningFastToT(1000,0,100);
    anl_fatima->SetBinningEnergy(500,0,1500);
    anl_fatima->SetBinning_dT(1000, -20, 20);
    run->AddTask(anl_fatima);

    FatimaTimingAnalysis * anti_anl_fatima = new FatimaTimingAnalysis();
    //anti_anl_fatima->SetDetectorTimeshifts("/lustre/gamma/jlarsson/FebCFDTamex/parameters/fatima_timeshifts.txt");
    anti_anl_fatima->SetEnergies(E2, E1, 20);
    anti_anl_fatima->SetDetectorToAnalyze(&dets);
    anti_anl_fatima->SetBinningSlowToT(2000,570,660);
    anti_anl_fatima->SetBinningFastToT(1000,0,100);
    anti_anl_fatima->SetBinningEnergy(500,0,1500);
    anti_anl_fatima->SetBinning_dT(1000, -20, 20);
    run->AddTask(anti_anl_fatima);

    return;

}

void run_timing_analysis(TString inputfile)
{   
    TStopwatch timer;


    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    timer.Start();

    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);

    //stream://x86l-116
    TString infilepath = "/lustre/gamma/jlarsson/FebCFDTamex/rootfiles/";
    TString filename = infilepath + inputfile;
    TString outputpath = "/lustre/gamma/jlarsson/FebCFDTamex/rootfilesanalyzed/";
    TString outputFileName = outputpath + inputfile.ReplaceAll(".root","_analyzed.root");

    // Create online run
    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1); 
    run->SetSink(new FairRootFileSink(outputFileName));

    FairFileSource * source = new FairFileSource(filename);
    UInt_t evnts = source->GetEntries();
    
    run->SetSource(source);


    FatimaSinglesAnalysis * fsa = new FatimaSinglesAnalysis();
    fsa->SetDetectorToAnalyze(&dets);
    fsa->SetBinningSlowToT(2000,570,660);
    fsa->SetBinningFastToT(1000,0,100);
    fsa->SetBinningEnergy(500,0,1500);
    run->AddTask(fsa);

    Add_Coinc_Analysis(run, 411, 344);
    Add_Coinc_Analysis(run, 778, 344);
    Add_Coinc_Analysis(run, 1090, 344);
    Add_Coinc_Analysis(run, 1299, 344);
    Add_Coinc_Analysis(run, 444, 244);
    Add_Coinc_Analysis(run, 867, 244);


    // Initialise
    run->Init();    
    
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << inputfile << endl;
    cout << "\n\n" << endl;

    // Run
    run->Run(0,evnts); 


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
