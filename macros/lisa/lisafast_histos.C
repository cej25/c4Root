#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1

extern "C"
{
    //#include HISTO_FILE
}

//extern std::vector<LisaGate*> lgs;

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisafast_onion_t lisafast;

} EXT_STR_h101;

void lisafast_histos()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    // ::: Experiment name
    TString fExpName = "lisafast";

    // ::: Here you define commonly used path
    //TString c4Root_path = "/u/gandolfo/c4/c4Root";
    TString c4Root_path = "/home/lisa/programs/c4/fast_c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes --allow-errors ";
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
    TString inputpath = "/home/lisa/data/server1/groups/wimmer/laboratory/trees/";
    TString rootname = "tamex_0030_0001_cal_tree.root";
    TString filename = inputpath + rootname;

    // ::: OUTPUT 
    TString outputpath = "/home/lisa/data/server1/groups/wimmer/laboratory/histos/"; 

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
    //histo_config(config_path);

    TLisaFastConfiguration::SetDetectorConfigurationFile(config_path + "/Lisa_Mapping_LaBr3.txt");


    // :::: ENABLE SYSTEMS  ::::::::::::::::::::::::::::::::::::::::

    if (LISA_ON)
    {

        LisaFastNearlineSpectra* nearlinelisafast = new LisaFastNearlineSpectra();
        nearlinelisafast->AddRefLaBrForDeltaT(1);
        nearlinelisafast->AddDeltaTEnergyGate(500,460); 

        //nearlinelisafast->AddDeltaTEnergyGate(825,825); //1172 in det2, 1333 in ref det
        //nearlinelisafast->AddDeltaTEnergyGate(890,775); //1333 in det2, 1172 in ref det

        //nearlinelisafast->AddDeltaTReferenceEnergyGate(825); //gate in 1333 ref
        //nearlinelisafast->AddDeltaTReferenceEnergyGate(775); //gate in 1172 ref


        run->AddTask(nearlinelisafast);

    }

    TLisaFastConfiguration::SetSlowToT_bin(2000);
    TLisaFastConfiguration::SetSlowToT_max(2000);
    TLisaFastConfiguration::SetSlowToT_min(0);

    TLisaFastConfiguration::SetFastToT_bin(500);
    TLisaFastConfiguration::SetFastToT_max(500);
    TLisaFastConfiguration::SetFastToT_min(0);

    TLisaFastConfiguration::SetEnergy_bin(2000);
    TLisaFastConfiguration::SetEnergy_max(2000);
    TLisaFastConfiguration::SetEnergy_min(0);

    TLisaFastConfiguration::SetdT_bin(2000);
    TLisaFastConfiguration::SetdT_max(20);
    TLisaFastConfiguration::SetdT_min(-20);

    TLisaFastConfiguration::SetEnergyGateWidth(60);

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //TString histoConfigFile = HISTO_FILE;

    // TTree* metaTree = new TTree("info", "Histo info file");
    // metaTree->Branch("histo_config", &histoConfigFile);
    // metaTree->Fill();
    // Initialise
    run->Init();
    //metaTree->Write(); 

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
