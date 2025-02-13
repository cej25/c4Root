#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define AIDA_ON 1
#define BPLAST_ON 0
#define GERMANIUM_ON 0
#define BGO_ON 0
#define FRS_ON 1
#define TIME_MACHINE_ON 0
#define BEAMMONITOR_ON 0
#define WHITE_RABBIT_CORS 0

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/

// as long as we use the same one, all good right?
extern "C"
{
    #include "../../config/s100/frs/setup_des_s100_029_2024_conv.C"
}

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_aida_onion_t aida;
    EXT_STR_h101_bplast_onion_t bplast;
    EXT_STR_h101_germanium_onion_t germanium;
    EXT_STR_h101_frs_onion_t frs;
    EXT_STR_h101_beammonitor_onion_t beammonitor;
    EXT_STR_h101_bgo_onion_t bgo;
    // EXT_STR_h101_bb7febex_onion_t bb7febex;
} EXT_STR_h101;


void s101_tests()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    // TString fExpName = "NovTest";
    TString fExpName = "s101";
    //TString fExpName = "beammonitor";

    // Define important paths.
    //TString c4Root_path = "/u/jbormans/c4Root";
    TString c4Root_path = "/u/cjones/c4Root";
    //TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes --allow-errors";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + "s100" + "/" + "s100" + " --debug --input-buffer=200Mi --event-sizes --allow-errors";

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
    //TString filename = "stream://x86l-182"; // BGO
    // DO NOT CHANGE THIS DURING A RUN!!!!!!!
    // TString filename =  "~/lustre/gamma/s100_files/ts/162Eu_0075_0006.lmd";
    //TString filename = "~/lustre/gamma/nhubbard/162Eu_0052_TEST_0001.lmd";

    TString filename  = "~/lustre/gamma/stacktest2024_files/ts/aidabplas_OUT_130125_new_0182.lmd";
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
    TAidaConfiguration::SetBasePath(config_path + "/AIDA");
    TbPlastConfiguration::SetDetectorMapFile(config_path + "/bplast/bplast_alloc.txt");
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TGermaniumConfiguration::SetDetectorConfigurationFile(config_path + "/germanium/ge_alloc_apr15.txt");
    TGermaniumConfiguration::SetDetectorCoefficientFile(config_path + "/germanium/ge_uncal_apr15.txt");
    TBGOTwinpeaksConfiguration::SetDetectorConfigurationFile(config_path + "/bgo/bgo_alloc.txt");
    
    
    TFrsConfiguration::SetCrateMapFile(config_path + "/frs/crate_map.txt");
    

    // ------------------------------------------------------------------------------------- //
    // *** Read Subsystems - comment out unwanted systems ********************************** //

    // EventHeader - should always be done
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    
    source->AddReader(unpackheader);
    
  

    
    if (AIDA_ON)
    {
        AidaReader* unpackaida = new AidaReader((EXT_STR_h101_aida_onion*)&ucesb_struct.aida, offsetof(EXT_STR_h101, aida));
        
        unpackaida->SetOnline(true);
        source->AddReader(unpackaida);
    }

    if (BPLAST_ON)
    {
        bPlastReader* unpackbplast = new bPlastReader((EXT_STR_h101_bplast_onion*)&ucesb_struct.bplast, offsetof(EXT_STR_h101, bplast));
        //unpackbplast->DoFineTimeCalOnline(config_path + "/bplast/fine_time_4apr_test.root", 1000000);
        unpackbplast->SetInputFileFineTimeHistos(config_path + "/bplast/fine_time_4apr_test.root");
        
        unpackbplast->SetOnline(true);
        source->AddReader(unpackbplast);
    }

    if (GERMANIUM_ON)
    {
        GermaniumReader* unpackgermanium = new GermaniumReader((EXT_STR_h101_germanium_onion*)&ucesb_struct.germanium, offsetof(EXT_STR_h101, germanium));
        
        unpackgermanium->SetOnline(true);
        source->AddReader(unpackgermanium);
    }
    
    if (BGO_ON)
    {
        BGOReader* unpackbgo = new BGOReader((EXT_STR_h101_bgo_onion*)&ucesb_struct.bgo, offsetof(EXT_STR_h101, bgo));
        //unpackbgo->DoFineTimeCalOnline(config_path + "/bgo/fine_time_histos_17apr.root", 1000000);
        unpackbgo->SetInputFileFineTimeHistos(config_path + "/bgo/fine_time_histos_17apr.root");
        
        unpackbgo->SetOnline(true);
        source->AddReader(unpackbgo);
        
    }
    
    if (FRS_ON)
    {
        FrsReader* unpackfrs = new FrsReader((EXT_STR_h101_frs_onion*)&ucesb_struct.frs, offsetof(EXT_STR_h101, frs));
        unpackfrs->SetOnline(false);
        source->AddReader(unpackfrs);

    }
    
    if (BEAMMONITOR_ON)
    {
        BeamMonitorReader* unpackbeammonitor = new BeamMonitorReader((EXT_STR_h101_beammonitor_onion*)&ucesb_struct.beammonitor, offsetof(EXT_STR_h101, beammonitor));
        
        unpackbeammonitor->SetOnline(true);
        source->AddReader(unpackbeammonitor);
    }

   
    // ---------------------------------------------------------------------------------------- //
    // *** Calibrate Subsystems - comment out unwanted systems ******************************** //

    if (AIDA_ON)
    {
        AidaUnpack2Cal* aidaCalibrator = new AidaUnpack2Cal();
        
        aidaCalibrator->SetOnline(true);
        run->AddTask(aidaCalibrator);
        
    }
    
    if (BPLAST_ON)
    {
        bPlastRaw2Cal* calbplast = new bPlastRaw2Cal();
        
        calbplast->SetOnline(true);
        run->AddTask(calbplast);
        
        
    }
    
    if (GERMANIUM_ON)
    {
        GermaniumRaw2Cal* calge = new GermaniumRaw2Cal();
        // calge->PrintDetectorMap();

        calge->SetOnline(true);
        run->AddTask(calge);
    }
    
    if (BGO_ON)
    {
        BGORaw2Cal* calbgo = new BGORaw2Cal();
        // calbgo->PrintDetectorMap();
        
        calbgo->SetOnline(true);
        run->AddTask(calbgo);
    }
        
    
    if (FRS_ON)
    {
        FrsRaw2Cal* calfrs = new FrsRaw2Cal();
        calfrs->SetOnline(false);
        run->AddTask(calfrs);
    }


    // ---------------------------------------------------------------------------------------- //
    // *** Analyse Subsystem Hits ************************************************************* //
    
    
    if (AIDA_ON)
    {        
        AidaCal2Hit* aidaHitter = new AidaCal2Hit();
        
        aidaHitter->SetOnline(true);
        run->AddTask(aidaHitter);
    }
    
    if (FRS_ON)
    {
        FrsCal2Hit* hitfrs = new FrsCal2Hit();
        hitfrs->SetOnline(false);
        run->AddTask(hitfrs);
    } 



    // ======================================================================================== //
    // =========== **** SPECTRA ***** ========================================================= //
    // ======================================================================================== //
    
    // ---------------------------------------------------------------------------------------- //
    // *** Online Spectra ********************************************************************* //
    
    if (AIDA_ON)
    {
        AidaOnlineSpectra* aidaOnline = new AidaOnlineSpectra();
        
        run->AddTask(aidaOnline);
    }
    
    if (BPLAST_ON)
    {
        bPlastOnlineSpectra* onlinebplast = new bPlastOnlineSpectra();
        
        run->AddTask(onlinebplast);
        
    }
    
    if (GERMANIUM_ON)
    {
        GermaniumOnlineSpectra* onlinege = new GermaniumOnlineSpectra();
        onlinege->SetBinningEnergy(3000,0,3e3);
        onlinege->AddReferenceDetector(15,0);
        onlinege->AddReferenceDetector(1,0);
        onlinege->AddReferenceDetectorWithEnergyGates(1,0,1332);
        run->AddTask(onlinege);
    }
    
    TBGOTwinpeaksConfiguration::SetCoincidenceWindow(5000); 
    TBGOTwinpeaksConfiguration::SetCoincidenceOffset(0);
    if (BGO_ON)
    {
        BGOOnlineSpectra* onlinebgo = new BGOOnlineSpectra();
        onlinebgo->SetBinningEnergy(1500,0.1,1500.1);
        //onlinebgo->SetCoincidenceWindow(5000);

        
        run->AddTask(onlinebgo);
        
    }
    
    TFrsConfiguration::Set_Z_range(50,100);
    TFrsConfiguration::Set_AoQ_range(2.3,2.7);

    std::vector<FrsGate*> fgs = {}; // for now just because code cries without a vector
    
    if (FRS_ON)
    {
        // // For monitoring FRS on our side
        FrsRawSpectra* frsrawspec = new FrsRawSpectra();
        FrsCalSpectra* frscalspec = new FrsCalSpectra();
        FrsOnlineSpectra* onlinefrs = new FrsOnlineSpectra(fgs);
        
        run->AddTask(frsrawspec);
        run->AddTask(frscalspec);
        run->AddTask(onlinefrs);

    }
    
    if (BEAMMONITOR_ON)
    {
        BeamMonitorOnlineSpectra* onlinebm = new BeamMonitorOnlineSpectra();
        
        run->AddTask(onlinebm);
    }

    TString b = "Aida";
    TString c = "bPlast";
    TString d = "Germanium";
    TString e = "Frs";

    if (TIME_MACHINE_ON) // a little complicated because it falls apart if the right subsystem is switched off
    {
        TimeMachineOnline* tms = new TimeMachineOnline();
        std::vector a {b, c, d, e};
        tms->SetDetectorSystems(a);
        
        run->AddTask(tms);
    }
    
    if (WHITE_RABBIT_CORS)
    {
        WhiterabbitCorrelationOnline* wronline = new WhiterabbitCorrelationOnline();
        wronline->SetDetectorSystems({b, c, d, e});
    
        run->AddTask(wronline);
    }

    if (FRS_ON && AIDA_ON)
    {
        //FrsAidaCorrelationsOnline* frsaidaonline = new FrsAidaCorrelationsOnline(fgs);
        //FrsAidaCorrelations* frsaidaonline = new FrsAidaCorrelations(fgs);

        //run->AddTask(frsaidaonline);
    }

    if (BPLAST_ON && GERMANIUM_ON)
    {
        bPlastGermaniumCorrelationsOnline* bplastgecorr = new bPlastGermaniumCorrelationsOnline();
        // set bplast multiplicity
        // ???
        run->AddTask(bplastgecorr);
    }

    if (BPLAST_ON && FRS_ON)
    {
	    //FrsBplastCorrelations* frsbplast = new FrsBplastCorrelations();
	    //run->AddTask(frsbplast);
    }

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

