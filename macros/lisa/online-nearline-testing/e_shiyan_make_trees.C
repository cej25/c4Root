#include <TROOT.h>

// !!! Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
#define FRS_ON 1

// !!! Select the data level you want to visualize
#define LISA_RAW 0
#define LISA_ANA 0
#define LISA_CAL 1

// Define for online if testing or during experient
#define TEST 0
#define EXP 1

// :::  Define FRS setup.C file - FRS should provide; place in /config/shiyan/frs/setup/
extern "C"
{
    //#include "../../config/pareeksha/frs/setup_Fragment_conv_updated.C" //pareeksha data
    #include "../../../config/shiyan/frs/setup/setup_103_002_2025_conv.C" //shiyan
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;
    EXT_STR_h101_frs_onion_t frs;

} EXT_STR_h101;

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
    //TString inputpath = "/u/gandolfo/data/lustre/despec/lisa/S092_shiyan/";
    TString inputpath = "/u/gandolfo/data/lustre/gamma/s092_s103_files/ts/";                       // Data from LISA
    //TString inputpath = "/u/gandolfo/data/lustre/nustar/profi/sec_s160feb25/stitched/";           // Data from FRS with S2 PID
 
    TString filename = inputpath + "run_0006_0001.lmd";
    //TString filename = inputpath + "test_0003_0001.lmd";
    //TString filename = inputpath + "Ag101_withSC11a_s2trig_0121_0001_stitched.lmd";

    // ::: OUTPUT 
    //TString outputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/noise_test_may25/";   //testing
    TString outputpath = "/u/gandolfo/data/shiyan_1st_day/";   //energy resolution data
    
    //TString outputFilename = outputpath + "test_run_0075.root";
    TString outputFilename = outputpath + "run_0006_0001_tree_conv.root"; 
    //TString outputFilename = outputpath + "Ag101_withSC11a_s2trig_0121_0001_stitched_tree.root";  // Data from FRS with S2 PID


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

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // :::C O R R E L A T I O N S - Initialise 
    TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations_tight.dat");

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: C O N F I G    F O R   D E T E C T O R - Load
    // ::: Exp config
    TExperimentConfiguration::SetExperimentStart(1746597600000000000); // Start for Shiyan data: May 7th, 8a.m. //including testing
    //TExperimentConfiguration::SetExperimentStart(1715727045000000000);//Start of pareeksha with primary beam: 15 May 00:50
    //TExperimentConfiguration::SetExperimentStart(1746172830000000000);
    // for S100, 3 and 4. for 2025+ 12 and 13.
    TExperimentConfiguration::SetBOSTrig(3);
    TExperimentConfiguration::SetEOSTrig(4);
    
    // ::: FRS config
    TFrsConfiguration::SetConfigPath(config_path +  "/frs/");
    TFrsConfiguration::SetCrateMapFile(config_path +  "/frs/crate_map.txt");
    TFrsConfiguration::SetTravMusDriftFile(config_path +  "/frs/TM_Drift_fragments.txt");
    TFrsConfiguration::SetZ1DriftFile(config_path +  "/frs/Z1_Drift_fragments.txt");
    TFrsConfiguration::SetAoQDriftFile(config_path +  "/frs/AoQ_Drift_fragments.txt");

    // ::: Lisa config
    if ( TEST )
    {
        // shiyan 
        
        TLisaConfiguration::SetMappingFile(config_path +  "/lisa/Lisa_4x4_shiyan.txt");
        TLisaConfiguration::SetGMFile(config_path +  "/lisa/Lisa_GainMatching_shiyan.txt");
        TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD_shiyan.txt");
        TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters_shiyan_v0.txt");
        
        /*
        //for testing with pareeksha data 
        TLisaConfiguration::SetMappingFile(config_path +  "/lisa/Lisa_Detector_Map_names.txt");
        TLisaConfiguration::SetGMFile(config_path +  "/lisa/Lisa_GainMatching.txt");
        TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD.txt");
        TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters.txt");
        */
    }
    if ( EXP )
    {
        
        TLisaConfiguration::SetMappingFile(config_path +  "/lisa/Lisa_4x4_shiyan.txt");
        TLisaConfiguration::SetGMFile(config_path +  "/lisa/Lisa_GainMatching_shiyan.txt");
        TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD_shiyan.txt");
        TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters_shiyan_v0.txt");

        // //for testing with pareeksha data 
        // TLisaConfiguration::SetMappingFile(config_path +  "/lisa/Lisa_Detector_Map_names.txt");
        // TLisaConfiguration::SetGMFile(config_path +  "/lisa/Lisa_GainMatching.txt");
        // TLisaConfiguration::SetGMFileMWD(config_path +  "/lisa/Lisa_GainMatching_MWD.txt");
        // TLisaConfiguration::SetMWDParametersFile(config_path + "/lisa/Lisa_MWD_Parameters.txt");
    }

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // S U B S Y S T E M S
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   
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
        unpackfrs->SetOnline(true);
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
        
        calfrs->SetOnline(true);
        run->AddTask(calfrs);

    }


    // ::: ANALYSE Subsystem  :::

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
