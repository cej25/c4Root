#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
#define FRS_ON 1
#define WHITE_RABBIT_CORS 0 // does not work w/o aida currently

//Select the data level you want to visualize
#define LISA_RAW 0
#define LISA_ANA 0
#define LISA_CAL 1

// Define FRS setup.C file - FRS should provide; place in /config/pareeksha/frs/
extern "C"
{
    #include "../../config/pareeksha/frs/setup_Fragment_conv_updated.C"
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;
    EXT_STR_h101_frs_onion_t frs;

} EXT_STR_h101;

void lisadev_make_trees(int fileNumber)
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    //:::::::::Experiment name
    TString fExpName = "pareeksha";

    //:::::::::Here you define commonly used path
    TString c4Root_path = "/u/gandolfo/c4/c4Root";
    //TString c4Root_path = "~/c4Root";
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
    //TString filename = "/u/gandolfo/data/lustre/despec/lisa/daq_test_0169_*.lmd";  //data with only lisa
    //TString filename = "/u/gandolfo/data/lustre/despec/s092_s143/daqtest/daqtest_0001_0001.lmd"; //data from ts folder
    TString inputpath = "/u/gandolfo/data/lustre/gamma/s092_s143_files/ts/";
    TString filename = Form(inputpath + "run_%04d_0001.lmd", fileNumber);

    //___O U T P U T
    TString outputpath = "/u/gandolfo/data/test_c4/"; //testing
    //TString outputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/pareeksha_trees/fragments_EG_test/";    
    TString outputFilename = Form(outputpath + "run_%04d_v3.root", fileNumber);


    //:::::::Create online run
    Int_t refresh = 10; // not needed
    //Int_t port = 5000; // not needed
     
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFilename)); // don't write after termintion
    //run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);
     
    //:::::::Take ucesb input and create source
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK,RAW"; //level of unpacked data (UNPACK,RAW,CAL)
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //::::: F R S parameter - Initialise

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

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::: G A T E S - Initialise 

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::: C O R R E L A T I O N S - Initialise 
  
    TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations_tight.dat");

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::::: C O N F I G    F O R   D E T E C T O R - Load
    // ::: Exp config
    TExperimentConfiguration::SetExperimentStart(1715734200000000000);//Start of pareeksha with primary beam: 15 May 00:50
    // for S100, 3 and 4. for 2025+ 12 and 13.
    TExperimentConfiguration::SetBOSTrig(3);
    TExperimentConfiguration::SetEOSTrig(4);
    
    // ::: FRS config
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TFrsConfiguration::SetCrateMapFile(config_path + "/frs/crate_map.txt");
    TFrsConfiguration::SetTravMusDriftFile(config_path + "/frs/TM_Drift_fragments.txt");
    TFrsConfiguration::SetZ1DriftFile(config_path + "/frs/Z1_Drift_fragments.txt");
    TFrsConfiguration::SetAoQDriftFile(config_path + "/frs/AoQ_Drift_fragments.txt");

    // ::: Lisa config
    TLisaConfiguration::SetMappingFile(config_path + "/lisa/Lisa_Detector_Map_names.txt");
    TLisaConfiguration::SetGMFile(config_path + "/lisa/Lisa_GainMatching.txt");
    TLisaConfiguration::SetGMFileMWD(config_path + "/lisa/Lisa_GainMatching_MWD.txt");
    TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters.txt");


    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // S U B S Y S T E M S
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   
    // ::::::: READ Subsystem  ::::::::

    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);

    if (LISA_ON)
    {
        LisaReader* unpacklisa = new LisaReader((EXT_STR_h101_lisa_onion*)&ucesb_struct.lisa, offsetof(EXT_STR_h101, lisa));
        //unpacklisa->DoFineTimeCalOnline("....root", 100000);
        //unpacklisa->SetInputFileFineTimeHistos(config_path + "....root");

        if (LISA_RAW)
        {
            unpacklisa->SetOnline(false); //false= write to a tree; true=doesn't write to tree
        } else 
        {
            unpacklisa->SetOnline(true); //false= write to a tree; true=doesn't write to tree
        }
        //unpacklisa->SetOnline(true); //false= write to a tree; true=doesn't write to tree
        
        source->AddReader(unpacklisa);
    }

    if (FRS_ON)
    {   

        FrsReader* unpackfrs = new FrsReader((EXT_STR_h101_frs_onion*)&ucesb_struct.frs, offsetof(EXT_STR_h101, frs)); 
        unpackfrs->SetOnline(true);
        source->AddReader(unpackfrs);

    }   


    // ::::::: CALIBRATE Subsystem  ::::::::

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
        
        calfrs->SetOnline(true);
        run->AddTask(calfrs);

    }


    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    // ::::::: ANALYSE Subsystem  ::::::::

    if (FRS_ON)
    {
        FrsCal2Hit* hitfrs = new FrsCal2Hit();
        
        hitfrs->SetOnline(false); 
        run->AddTask(hitfrs);
    } 


    // Initialise
    run->Init();

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
