#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
        //LISA_ANA displays only energy and traces; LISA_CAL displays stats,energy,traces. Choose one.
        //Note that if FRS 1, LISA_CAL is needed. 
#define LISA_ANA 0
#define LISA_CAL 1

#define FRS_ON 0
#define TRAV_MUSIC_ON 0
#define WHITE_RABBIT_CORS 0 // does not work w/o aida currently

// Define FRS setup.C file - FRS should provide; place in /config/pareeksha/frs/
extern "C"
{
    #include "../../config/pareeksha/frs/setup_Fragment_conv.C"
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;

} EXT_STR_h101;

void lisadev_histos(int fileNumber)
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    //:::::::::Experiment name
    TString fExpName = "pareeksha";

    //:::::::::Here you define commonly used path
    TString c4Root_path = "/u/gandolfo/c4/c4Root";
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
    //TString inputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/pareeksha_trees/fragments_EG_test/";
    TString inputpath = "/u/gandolfo/data/test_c4/";
    TString filename = Form(inputpath + "run_%04d_EG.root", fileNumber);  
    
    //___O U T P U T
    //TString outputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/pareeksha_histos/fragments_EG_101gate/"; //test output
    TString outputpath = "/u/gandolfo/data/test_c4/"; //test output

    //TString outputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/pareeksha_histos/fragments_noGate/";
    TString outputFilename = Form(outputpath + "run_%04d_histos.root", fileNumber);


    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFilename)); // don't write after termintion
    FairSource* fs = new FairFileSource(filename);
    run->SetSource(fs);
    
    //Read tree evt
    TFile* file = TFile::Open(filename);
    TTree* eventTree = (TTree*)file->Get("evt"); 
    Int_t totEvt = eventTree->GetEntries();
     
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: LISA config
    TLisaConfiguration::SetMappingFile(config_path + "/lisa/Lisa_Detector_Map_names.txt");
    TLisaConfiguration::SetGMFile(config_path + "/lisa/Lisa_GainMatching.txt");
    TLisaConfiguration::SetGMFileMWD(config_path + "/lisa/Lisa_GainMatching_MWD.txt");
    TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters.txt");
    
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    // ::: Nearline Spectra ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    
    // ::: Set experiment star time :::
    // ::: Get run number :::
    TFrsConfiguration::SetRunNumber(fileNumber);
    std::cout << "Run number: " << fileNumber << std::endl;

    //::::::::: Set experiment configurations
    TExperimentConfiguration::SetExperimentStart(1715734200000000000);
    
    //::::::::: Set ranges for histos :::::::::::::::
    //::::  Channel Energy ::::: (h1_energy_)
    TLisaConfiguration::SetEnergyRange(0,10000000);
    TLisaConfiguration::SetEnergyBin(450);
    //:::: MWD histos
    TLisaConfiguration::SetEnergyRangeMWD(0,1000);
    TLisaConfiguration::SetEnergyBinMWD(450);

    TLisaConfiguration::SetEnergyRangeGM(0,20000);
    TLisaConfiguration::SetEnergyBinGM(450);

    TLisaConfiguration::SetEnergyRangeMWDGM(0,1000);
    TLisaConfiguration::SetEnergyBinMWDGM(450);

    TLisaConfiguration::SetWrDiffRange(0,100000);
    TLisaConfiguration::SetWrDiffBin(500);

    if (LISA_ON)
    {
        if(LISA_ANA)
        {
            LisaNearlineSpectraAna* nearlinelisaana = new LisaNearlineSpectraAna();
            run->AddTask(nearlinelisaana);
        }

        if(LISA_CAL)
        {
            LisaNearlineSpectra* nearlinelisa = new LisaNearlineSpectra();
            run->AddTask(nearlinelisa);
        }

    }
    
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: Correlation Spectra :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    // FrsLisa

    // Initialise
    run->Init();

    // Run
    run->Run(0, totEvt); 

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
}
