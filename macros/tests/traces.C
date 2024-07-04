#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
#define FRS_ON 0
#define TRAV_MUSIC_ON 0
#define WHITE_RABBIT_CORS 0 // does not work w/o aida currently

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;
    EXT_STR_h101_travmus_onion_t travmus;
    EXT_STR_h101_frsmain_onion_t frsmain;
    EXT_STR_h101_frstpc_onion_t frstpc;
    EXT_STR_h101_frsuser_onion_t frsuser;
    EXT_STR_h101_frstpat_onion_t frstpat;


} EXT_STR_h101;

void traces()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    //:::::::::Experiment name
    TString fExpName = "pareeksha";

    //:::::::::Here you define commonly used path
    TString c4Root_path = "/u/kwimmer/progs/c4/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes --allow-errors";
    ucesb_path.ReplaceAll("//","/");

    std::string config_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data());

    //:::::::::Macro timing
    TString cRunId = Form("%04d", fRunId);
    TString cExpId = Form("%03d", fExpId);
    TStopwatch timer;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    timer.Start();
    
    //:::::::::::Debug info - set level
    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);

    //::::::::::P A T H   O F   F I L E  to read
    //___O F F L I N E
    TString filename = "/u/kwimmer/lustre/gamma/LISA/data/jikken_trees_c4/run23_0001_c4.root";
    //TString filename = "/u/kwimmer/lustre/gamma/LISA/data/pareeksha_trees/fragments/run_0102_test.root";  
    
    //___O U T P U T
    TString outputpath = "/u/kwimmer/lustre/gamma/LISA/data/jikken_trees_c4/wimmer/";
    TString outputFilename = outputpath + "hist_0023.root";


    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFilename)); // don't write after termintion
    FairSource* fs = new FairFileSource(filename);
    run->SetSource(fs);   
     
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::::: C O N F I G    F O R   D E T E C T O R - Load
    TLisaConfiguration::SetMappingFile(config_path + "/lisa/Lisa_Detector_Map_names.txt");

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::   
    // =========== **** SPECTRA ***** ========================================================= //
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    

    
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    // ::: Nearline Spectra ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //::::::::: Set ranges for histos :::::::::::::::
    //::::  Channel Energy ::::: (h1_energy_layer_ch)
    TLisaConfiguration::SetEnergyRange(500000,3000000);
    TLisaConfiguration::SetEnergyBin(900);

    //:::: LISA WR Time Difference :::::: (h1_wr_diff)
    TLisaConfiguration::SetWrDiffRange(0,100000000);
    TLisaConfiguration::SetWrDiffBin(20000);



    if (LISA_ON)
    {
        // Add analysis task here at some point
        // LisaNearlineSpectra* nearlinelisa = new LisaNearlineSpectra();

        // run->AddTask(nearlinelisa);

        LisaTraceAnalysis* tracelisa = new LisaTraceAnalysis();

        run->AddTask(tracelisa);

    }


    //TString c = "Lisa";

    // Initialise
    run->Init();

    // Run
    run->Run(0,10000000);

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
