#include <TROOT.h>
#include <TNamed.h>
#include <TObjString.h>
#include <fstream>
#include <sstream>

// !!! Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
#define FRS_ON 1

// !!! Select the data level you want to visualize
#define LISA_RAW 0
#define LISA_ANA 0
#define LISA_CAL 0
#define LISA_HIT 1
//...................................................

// Definition of setup and configuration files
// FRS
#define FRS_SETUP_FILE "../../../config/shiyan/frs/setup/setup_103_002_2025_setting10_conv.C"
#define FRS_CONFIG_FILE "../../../config/shiyan/frs/general/frs_config_v1.C"
// LISA
#define LISA_CONFIG_FILE "../../../config/shiyan/lisa/general/lisa_config_v2.C"


// :::  Define FRS and LISA setup.C file; place in /config/shiyan/frs/setup/
extern "C"
{
    // FRS setup
    #include FRS_SETUP_FILE
    #include FRS_CONFIG_FILE
    
    // LISA setup
    #include LISA_CONFIG_FILE
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;
    EXT_STR_h101_frs_onion_t frs;

} EXT_STR_h101;

std::string readFileToString(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) return "[Could not open file]";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void e_shiyan_make_trees()
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

    
    // ::: FILE  PATH
    TString inputpath = "/u/gandolfo/data/lustre/gamma/s092_s103_files/ts/";                       // Data from LISA
    TString filename = inputpath + "run_0018_0001.lmd";

    // ::: OUTPUT 
    TString outputpath = "/u/gandolfo/data/shiyan_debug/";   //testing
    TString outputFilename = outputpath + "run_0018_mhtdc_updates.root";
    
    // ::: Create online run
    Int_t refresh = 10; // not needed
     
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFilename)); // don't write after termintion
    //run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);

    // ::: Take ucesb input and create source
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK,RAW"; //level of unpacked data (UNPACK,RAW,CAL)
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

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
    setup(frs,mw,tpc,music,labr,sci,id,si,mrtof,range); // Function defined in frs setup.C macro
    TFrsConfiguration::SetParameters(frs,mw,tpc,music,labr,sci,id,si,mrtof,range);
    frs_config(config_path);

    // ::: L I S A parameter - Initialise
    lisa_config(config_path);

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // :::C O R R E L A T I O N S - Initialise 
    TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations_tight.dat");
    
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // S U B S Y S T E M S
   
    // ::: READ Subsystem  :::

    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);

    if (LISA_ON)
    {
        LisaReader* unpacklisa = new LisaReader((EXT_STR_h101_lisa_onion*)&ucesb_struct.lisa, offsetof(EXT_STR_h101, lisa));

        if (LISA_RAW)
        {
            unpacklisa->SetOnline(false); //false= write to a tree; true=doesn't write to tree
        } else 
        {
            unpacklisa->SetOnline(true); //false= write to a tree; true=doesn't write to tree
        }        
        source->AddReader(unpacklisa);
    }

    if (FRS_ON)
    {   

        FrsReader* unpackfrs = new FrsReader((EXT_STR_h101_frs_onion*)&ucesb_struct.frs, offsetof(EXT_STR_h101, frs)); 
        unpackfrs->SetOnline(false);
        source->AddReader(unpackfrs);

    }   


    // ::: CALIBRATE Subsystem  :::
    if (LISA_ANA && !LISA_CAL)
    {
        LisaRaw2Ana* lisaraw2ana = new LisaRaw2Ana();

        lisaraw2ana->SetOnline(false);
        run->AddTask(lisaraw2ana);  
    } 

    if (LISA_CAL)
    {
        LisaRaw2Ana* lisaraw2ana = new LisaRaw2Ana();
        if(LISA_ANA)
        {
            lisaraw2ana->SetOnline(false);
        }else
        {
            lisaraw2ana->SetOnline(true);
        }
        run->AddTask(lisaraw2ana); 

        LisaAna2Cal* lisaana2cal = new LisaAna2Cal();
        lisaana2cal->SetOnline(false);
        run->AddTask(lisaana2cal);
    }

    if (FRS_ON)
    {

        FrsRaw2Cal* calfrs = new FrsRaw2Cal();
        
        calfrs->SetOnline(false);
        run->AddTask(calfrs);

    }

    // ::: ANALYSE Subsystem  :::
    if (FRS_ON)
    {
        FrsCal2Hit* hitfrs = new FrsCal2Hit();
        
        hitfrs->SetOnline(false); 
        run->AddTask(hitfrs);
    } 

    if (LISA_HIT)
    {
        LisaRaw2Ana* lisaraw2ana = new LisaRaw2Ana();
        if(LISA_ANA)
        {
            lisaraw2ana->SetOnline(false);
        }else
        {
            lisaraw2ana->SetOnline(true);
        }
        run->AddTask(lisaraw2ana); 

        LisaAna2Cal* lisaana2cal = new LisaAna2Cal();
        if(LISA_CAL)
        {
            lisaana2cal->SetOnline(false);
        }else
        {
            lisaana2cal->SetOnline(true);
        }
        run->AddTask(lisaana2cal);   

        LisaCal2Hit* lisacal2hit = new LisaCal2Hit();
        lisacal2hit->SetOnline(false);
        run->AddTask(lisacal2hit);
    }

    // Write information on setup and config in a "info" tree
    TString frsSetupFile = FRS_SETUP_FILE;
    TString frsConfigFile = FRS_CONFIG_FILE;
    TString lisaConfigFile = LISA_CONFIG_FILE;

    TTree* metaTree = new TTree("info", "Setup file and config info");
    metaTree->Branch("FRS_setup", &frsSetupFile);
    metaTree->Branch("FRS_config", &frsConfigFile);
    metaTree->Branch("LISA_config", &lisaConfigFile);
    metaTree->Fill();
    

    run->Init();  
    metaTree->Write(); 
    
    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    //cout << "LISA online port server: " << port << endl;
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
