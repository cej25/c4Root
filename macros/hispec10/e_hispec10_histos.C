#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define MCP_ON 1
#define STEFAN_ON 1
#define FRS_ON 1

#define GET_FILENAME(path) \
	({ \
	   std::string fullPath(path); \
	   size_t lastSlashPos = fullPath.find_last_of("/"); \
	   std::string fn = fullPath.substr(lastSlashPos + 1, fullPath.find_last_of(".") - lastSlashPos -1); \
	   fn; \
	})

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/
extern "C"
{
    //#include "../../config/hispec10/frs/setup_103_002_2025_setting14_conv.C"
    #include "../../config/hispec10/frs/setup_103_016_2025_conv.C" // for run 140

}

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_mcp_t mcp;
    EXT_STR_h101_stefan_t stefan;
    EXT_STR_h101_frs_onion_t frs;
} EXT_STR_h101;


void e_hispec10_histos()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "hispec10";

    // Define important paths.
    TString c4Root_path = "/u/gandolfo/c4/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --input-buffer=200Mi --event-sizes --allow-errors";
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

    // ::: INPUT
    TString inputpath = "/u/gandolfo/data/lustre/gamma/hispec10_dennis/tree/";
    TString filename = inputpath + "run_0140_0001_tree.root";

    // ::: O U T P U T
    TString outputpath = "/u/gandolfo/data//lustre/gamma/hispec10_dennis/histo/";   //testing
    TString outputFileName = outputpath + "run_0140_0001_histos.root";

    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName)); // don't write after termintion
    FairSource* fs = new FairFileSource(filename);
    run->SetSource(fs);
    
    //Read tree evt
    TFile* file = TFile::Open(filename);
    TTree* eventTree = (TTree*)file->Get("evt"); 
    Int_t totEvt = eventTree->GetEntries();


    // ------------------------------------------------------------------------------------ //
    // *** Initialise FRS parameters ****************************************************** //
    
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
    //TFrsConfiguration::SetParameterFilename();
    

    // ------------------------------------------------------------------------------------ //
    // *** Initialise Correlations ******************************************************** //
    
    TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations.dat");

    
    // ------------------------------------------------------------------------------------ //
    // *** Load Detector Configurations *************************************************** //
    TH10MCPConfiguration::SetDetectorConfigurationFile(config_path + "/mcp/mcp_mapping_1105.txt");
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TFrsConfiguration::SetCrateMapFile(config_path + "/frs/crate_map.txt");
 
    TStefanConfiguration::SetDetectorConfigurationFile(config_path + "/stefan/stefan_mapping.txt");
    TStefanConfiguration::SetDetectorCoefficientFile(config_path + "/stefan/stefan_cal.txt");

    TFrsConfiguration::Set_Z_range(10,30);
    TFrsConfiguration::Set_AoQ_range(1.5,2.5);
    TFrsConfiguration::Set_x2_range(-120,120);
    TFrsConfiguration::Set_x4_range(-120,120);

    // ======================================================================================== //
    // =========== **** SPECTRA ***** ========================================================= //
    // ======================================================================================== //
    
    // ---------------------------------------------------------------------------------------- //
    if (MCP_ON)
    {
        H10MCPNearlineSpectra* nearlinemcp = new H10MCPNearlineSpectra();
        run->AddTask(nearlinemcp);
    }
    
    // if (STEFAN_ON)
    // {
    //     StefanOnlineSpectra* onlinestefan = new StefanOnlineSpectra();
    //     // onlinestefan->SetBinningEnergy(65000,0,65000);
    //     run->AddTask(onlinestefan);
    // }


    std::vector<FrsGate*> fgs;
    FrsGate* Ti44 = new FrsGate("Ti44", config_path + "/frs/44Tisetup19.root");  
    FrsGate* full_pid = new FrsGate("full_pid", config_path + "/frs/fullgate_run140.root");  

    fgs.emplace_back(full_pid);
 
    if (FRS_ON)
    {
        FrsNearlineSpectra* nearlinefrs = new FrsNearlineSpectra();
        run->AddTask(nearlinefrs);

        // EG - The following lines are to monitor frs raw data -- This task seems to break on this branch.
        // EG - The same task on the main branch work, if you need it merge or copy it from there.
        //FrsRawNearlineSpectra* rawnearlinefrs = new FrsRawNearlineSpectra();
        //run->AddTask(rawnearlinefrs);
    }

    if (FRS_ON & MCP_ON)
    {
        FrsMCPCorrelations* mcpcorr = new FrsMCPCorrelations(fgs);
        run->AddTask(mcpcorr);
    }
   
  
    // Initialise
    run->Init();

    // Run
    run->Run(0, totEvt); 

    // ---------------------------------------------------------------------------------------- //
    // *** Finish Macro *********************************************************************** //

    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    Float_t cpuUsage = ctime / rtime;
    cout << "CPU used: " << cpuUsage << endl;
    std::cout << std::endl << std::endl;
    std::cout << "Macro finished successfully." << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
   
   // ----------------------------------------------------------------------------------------- //

}

