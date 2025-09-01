#include <TROOT.h>
#include <TNamed.h>
#include <TObjString.h>
#include <fstream>
#include <sstream>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
#define LISA_ANA 0
#define LISA_CAL 1

// If you want to have trace histos
#define TRACE_ON 1

#define FRS_ON 1
#define FRS_LISA_CORRELATIONS 1

#define WR_ENABLED 1
//................................................

// Definition of histo ranges for lisa and frs
#define HISTO_FILE "../../../config/shiyan/lisa/general/histo_config_v0.C"

extern "C"
{
    #include HISTO_FILE
}

extern std::vector<FrsGate*> fgs;
extern std::vector<LisaGate*> lgs;

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;
    EXT_STR_h101_frs_onion_t frs;

} EXT_STR_h101;

void e_shiyan_histos()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    // ::: Experiment name
    TString fExpName = "shiyan";

    // ::: Here you define commonly used path
    TString c4Root_path = "/u/gandolfo/c4/c4Root";
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
    //TString inputpath = "/u/gandolfo/data/lustre/gamma/lisa_s092/trees/";
    TString inputpath = "/u/gandolfo/data/shiyan_debug/";
    TString filename = inputpath + "run_0018_mhit_ztesting.root";  
    
    // ::: O U T P U T
    //TString outputpath = "/u/gandolfo/data/lustre/gamma/lisa_s092/histos/";
    TString outputpath = "/u/gandolfo/data/shiyan_debug/";   //energy resolution output
    TString outputFilename = outputpath + "run_0018_mhit_ztesting_histos.root";


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
    // ::: F R S parameter - Initialise

    TFRSParameter* frs = new TFRSParameter();
    TMWParameter* mw = new TMWParameter();
    TTPCParameter* tpc = new TTPCParameter();
    TMUSICParameter* music = new TMUSICParameter();
    TLABRParameter* labr = new TLABRParameter();
    TSCIParameter* sci = new TSCIParameter();
    TIDParameter* id = new TIDParameter();
    TSIParameter* si = new TSIParameter();
    TMRTOFMSParameter* mrtof = new TMRTOFMSParameter();
    TRangeParameter* range = new TRangeParameter();
    TFrsConfiguration::SetParameters(frs,mw,tpc,music,labr,sci,id,si,mrtof,range);
    histo_config(config_path);

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    
    // ::: Get run number :::
    //TFrsConfiguration::SetRunNumber(fileNumber);
    //std::cout << "Run number: " << fileNumber << std::endl;


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
        if(LISA_ANA)
        {
            LisaNearlineSpectraAna* nearlinelisaana = new LisaNearlineSpectraAna();
            run->AddTask(nearlinelisaana);
        }

        if(LISA_CAL)
        {
            LisaNearlineSpectra* nearlinelisa = new LisaNearlineSpectra(lgs);
            run->AddTask(nearlinelisa);
        }

    }

    if (FRS_ON)
    {
        FrsNearlineSpectra* nearlinefrs = new FrsNearlineSpectra(fgs);
        run->AddTask(nearlinefrs);
        //FrsRawNearlineSpectra* rawnearlinefrs = new FrsRawNearlineSpectra();
        //run->AddTask(rawnearlinefrs);
    }
    
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: Correlation Spectra :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    if(LISA_ON && FRS_ON)
    {
        if(FRS_LISA_CORRELATIONS)
        {
            LisaFrsCorrelations* LISA_FRS_corr = new LisaFrsCorrelations(fgs,lgs);
            run->AddTask(LISA_FRS_corr);
        }
    }

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
