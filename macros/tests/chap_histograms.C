#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define MCP_ON 1
#define STEFAN_ON 0
#define FRS_ON 0

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/
extern "C"
{
    #include "../../config/s115/frs/setup_115_022_2025_s1calib_conv.C"
}

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_mcp_t mcp;
    EXT_STR_h101_stefan_t stefan;
    EXT_STR_h101_frs_onion_t frs;
} EXT_STR_h101;


void chap_histograms()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "hispec10";

    // Define important paths.
    TString c4Root_path = "/mnt/data/builds/c4rootnew/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --input-buffer=200Mi --event-sizes --allow-errors";
    ucesb_path.ReplaceAll("//","/");

    std::string config_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data());
    
    // Macro timing
    TString cRunId = Form("%04d", fRunId);
    TString cExpId = Form("%03d", fExpId);
    TStopwatch timer;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    timer.Start();
    
    // Set level of debug information
    FairLogger::GetLogger()->SetLogScreenLevel("INFO");
    FairLogger::GetLogger()->SetColoredLog(true);

    // Define where to read data from. Online = stream/trans server, Nearline = .lmd file.
    TString filename = "78puliser1.root";
    TString outputpath = "mcp_histogram_";
    TString outputFileName =  filename + outputpath + "1.root";

    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName));
    FairSource* fs = new FairFileSource(filename);
    run->SetSource(fs);

  
  

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
    // *** Initialise Gates *************************************************************** //
    // Position gates on MCP1?
    
    // ------------------------------------------------------------------------------------ //
    // *** Initialise Correlations ******************************************************** //
    
    TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations.dat");

    
    // ------------------------------------------------------------------------------------ //
    // *** Load Detector Configurations *************************************************** //
    TH10MCPConfiguration::SetDetectorConfigurationFile(config_path + "/mcp/mcp_mapping.txt");
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TFrsConfiguration::SetCrateMapFile(config_path + "/frs/crate_map.txt");

   
    // ======================================================================================== //
    // =========== **** SPECTRA ***** ========================================================= //
    // ======================================================================================== //
    
    // ---------------------------------------------------------------------------------------- //
    if (MCP_ON)
    {
        H10MCPNearlineSpectra* nearlinemcp = new H10MCPNearlineSpectra();
        
        run->AddTask(nearlinemcp);
        
    }
    
    if (STEFAN_ON)
    {
        // StefanNearlineSpectra* nearlinestefan = new StefanNearlineSpectra();
        // run->AddTask(nearlinestefan);
    }

    TFrsConfiguration::Set_Z_range(30,50);
    TFrsConfiguration::Set_AoQ_range(1.8,2.4);
    TFrsConfiguration::Set_x2_range(-120,120);
    TFrsConfiguration::Set_x4_range(-120,120);
    std::vector<FrsGate*> frsgates{};
 
    if (FRS_ON)
    {
        FrsNearlineSpectra* nearlinefrs = new FrsNearlineSpectra(frsgates);
       
        run->AddTask(nearlinefrs);
        
    }
   
  
    // Initialise
    run->Init();
    
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "\n\n" << endl;

    // Run
   // run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev); 
run->Run(1000000000); 
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

