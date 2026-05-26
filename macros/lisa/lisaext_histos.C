#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
        //LISA_ANA displays only energy and traces; LISA_CAL displays stats,energy,traces. Choose one.
        //Note that if FRS 1, LISA_CAL is needed. 
#define LISA_ANA 0
#define LISA_CAL 1

// If you want to have trace histos
#define TRACE_ON 1

#define WR_ENABLED 1
#define WHITE_RABBIT_CORS 0 // does not work w/o aida currently

//................................................

// Definition of histo ranges for lisa and frs
#define HISTO_FILE "../../config/lisaext/general/histo_config_v0.C"

extern "C"
{
    #include HISTO_FILE
}

extern std::vector<LisaGate*> lgs;

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisaext_onion_t lisa;

} EXT_STR_h101;

void lisaext_histos()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    // ::: Experiment name
    TString fExpName = "lisaext";

    // ::: Here you define commonly used path
    //TString c4Root_path = "/u/gandolfo/c4/c4Root";
    TString c4Root_path = "/home/lisa/programs/c4/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes --allow-errors";
    ucesb_path.ReplaceAll("//","/");

    std::string config_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data());

    // ::: Macro timing
    TString cRunId = Form("%04d", fRunId);
    TString cExpId = Form("%03d", fExpId);
    TStopwatch timer;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    timer.Start();
    
    // ::: Debug info - set level
    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);

    // ::: P A T H   O F   F I L E  to read
    //TString inputpath = "/u/gandolfo/data/lisaext/";
    TString inputpath = "/home/lisa/data/trees/";
    TString rootname = "preamp_test_21may_0007_tree.root";
    TString filename = inputpath + rootname;

    // ::: OUTPUT 
    //TString outputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/ext_daq_debnik/dev_test/"; 
    //TString outputpath = "/u/gandolfo/data/lisaext/"; 
    TString outputpath = "/home/lisa/data/histos/"; 
    TString outputFilename = outputpath + TString(rootname).ReplaceAll("_tree.root", "_histo.root");

    
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
    histo_config(config_path);

    // :::: ENABLE SYSTEMS  ::::::::::::::::::::::::::::::::::::::::
    if(TRACE_ON)
    {
        TLisaConfiguration::SetTrace(1);
    }else
    {
        TLisaConfiguration::SetTrace(0);
    }

    if (LISA_ON)
    {

        if(LISA_CAL)
        {
            LisaNearlineSpectra* nearlinelisa = new LisaNearlineSpectra(lgs);
            run->AddTask(nearlinelisa);
        }

    }
    
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    TString histoConfigFile = HISTO_FILE;

    TTree* metaTree = new TTree("info", "Histo info file");
    metaTree->Branch("histo_config", &histoConfigFile);
    metaTree->Fill();
    // Initialise
    run->Init();
    metaTree->Write(); 

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
