#include <TROOT.h>

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/

// as long as we use the same one, all good right?
extern "C"
{
    // #include "../../config/s101/frs/setup_160_049_2025_conv.C"
    #include "../../config/s100/frs/setup_des_s100_030_2024_conv.C"
}

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_frs_onion_t frs;
} EXT_STR_h101;


void run_frs_online()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "s100";

    // Define important paths.
    TString c4Root_path = "/u/cjones/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes --allow-errors";
    //TString ucesb_path = c4Root_path + "/unpack/exps/" + "s100" + "/" + "s100" + " --debug --input-buffer=200Mi --event-sizes --allow-errors";

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


    // TString filename  = "~/lustre/gamma/stacktest2024_files/ts/aidabplas_OUT_130125_new_0182.lmd";
    //TString filename =  "~/lustre/gamma/s100_files/ts/162Eu_0075_0006.lmd";
    TString filename = "~/lustre/gamma/s100_files/new_ts/162Eu/162Eu_new_0045_0098.lmd";
    TString outputpath = "output";
    TString outputFileName = outputpath + ".root";

    // Create Online run
    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 7070; // Port number for online visualisation - use 5000 on lxg1301 during experiments as it has firewall access.

    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    //EvtHead->Register(false);
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFileName));
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);

    // Create source using ucesb for input
    EXT_STR_h101 ucesb_struct;
    
    TString ntuple_options = "UNPACK,RAW"; // Define which level of data to unpack - we don't use "CAL"
    
    UcesbSource* source = new UcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(nev);
    run->SetSource(source);

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
    
    // ------------------------------------------------------------------------------------ //
    // *** Initialise Gates *************************************************************** //
    

    /*std::string germanium_gate_path = std::string(c4Root_path.Data()) + "/config/" + std::string(fExpName.Data()) + "/germanium/Gates/";
    std::vector<std::string> GePromptCuts = {"GePromptCut1"};
    TCutGGates* GePrompt = new TCutGGates("GeEdT", GePromptCuts, germanium_gate_path);*/
    //TGermaniumConfiguration::SetPromptFlashCut(germanium_gate_path + "/GePromptCut1");
    
    // ------------------------------------------------------------------------------------ //
    // *** Initialise Correlations ******************************************************** //
    
    TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations.dat");


    // ------------------------------------------------------------------------------------ //
    // *** Load Detector Configurations *************************************************** //
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TFrsConfiguration::SetCrateMapFile(config_path + "/frs/crate_map.txt");
    

    // ------------------------------------------------------------------------------------- //
    // *** Read Subsystems - comment out unwanted systems ********************************** //

    // EventHeader - should always be done
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    
    source->AddReader(unpackheader);
    
   

    FrsReader* unpackfrs = new FrsReader((EXT_STR_h101_frs_onion*)&ucesb_struct.frs, offsetof(EXT_STR_h101, frs));
    unpackfrs->SetOnline(false);
    source->AddReader(unpackfrs);

    
    // ---------------------------------------------------------------------------------------- //
    // *** Calibrate Subsystems - comment out unwanted systems ******************************** //
        
    FrsRaw2Cal* calfrs = new FrsRaw2Cal();
    calfrs->SetOnline(false);
    run->AddTask(calfrs);
    
    // // ---------------------------------------------------------------------------------------- //
    // // *** Analyse Subsystem Hits ************************************************************* //
       
    
    FrsCal2Hit* hitfrs = new FrsCal2Hit();
    hitfrs->SetOnline(false);
    run->AddTask(hitfrs);


    // ======================================================================================== //
    // =========== **** SPECTRA ***** ========================================================= //
    // ======================================================================================== //
    
    // ---------------------------------------------------------------------------------------- //
    // *** Online Spectra ********************************************************************* //
    
  
    TFrsConfiguration::Set_Z_range(50,100);
    TFrsConfiguration::Set_AoQ_range(2.3,2.7);

    std::vector<FrsGate*> fgs = {}; // for now just because code cries without a vector
    
    // // // For monitoring FRS on our side
    FrsRawSpectra* frsrawspec = new FrsRawSpectra();
    FrsCalSpectra* frscalspec = new FrsCalSpectra();
    FrsOnlineSpectra* onlinefrs = new FrsOnlineSpectra(fgs);
    
    run->AddTask(frsrawspec);
    run->AddTask(frscalspec);
    run->AddTask(onlinefrs);

    

    // Initialise
    run->Init();
    
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "Online port server: " << port << endl;
    cout << "\n\n" << endl;

    // Run
    run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev); 


    // ---------------------------------------------------------------------------------------- //
    // *** Finish Macro *********************************************************************** //

    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    Float_t cpuUsage = ctime / rtime;
    cout << "CPU used: " << cpuUsage << endl;
    std::cout << std::endl << std::endl;
    std::cout << "Macro finished successfully." << std::endl;
    std::cout << "Output file is " << outputFileName << std::endl;
    std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;
   // gApplication->Terminate(0);
   
   // ----------------------------------------------------------------------------------------- //

}

