#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define FATIMA_ON 1
#define FATIMA_VME_ON 1
#define AIDA_ON 1
#define BPLAST_ON 1
#define GERMANIUM_ON 1
#define BGO_ON 1
#define FRS_ON 1
#define TIME_MACHINE_ON 1
#define BEAMMONITOR_ON 0
#define WHITE_RABBIT_CORS 1

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/
extern "C"
{
    #include "../../config/s100/frs/setup_des_s100_030_2024_conv.C"
}

// Struct should containt all subsystem h101 structures
typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fatima_onion_t fatima;
    EXT_STR_h101_fatimavme_onion_t fatimavme;
    EXT_STR_h101_aida_onion_t aida;
    EXT_STR_h101_bplast_onion_t bplast;
    EXT_STR_h101_germanium_onion_t germanium;
    EXT_STR_h101_frsmain_onion_t frsmain;
    EXT_STR_h101_frstpc_onion_t frstpc;
    EXT_STR_h101_frsuser_onion_t frsuser;
    EXT_STR_h101_frstpat_onion_t frstpat;
    EXT_STR_h101_beammonitor_onion_t beammonitor;
    EXT_STR_h101_bgo_onion_t bgo;
    // EXT_STR_h101_bb7febex_onion_t bb7febex;
} EXT_STR_h101;


void s100_online_new()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;

    // Name your experiment. Make sure all relevant directories are named identically.
    // TString fExpName = "NovTest";
    TString fExpName = "s100";
    //TString fExpName = "beammonitor";

    // Define important paths.
    //TString c4Root_path = "/u/jbormans/c4Root";
    TString c4Root_path = "/u/despec/s100_online/c4Root";
    TString screenshot_path = "~/lustre/gamma/dryrunmarch24/screenshots/";
    //TString c4Root_path = "/u/cjones/c4Root";
    TString ucesb_path = c4Root_path + "/unpack/exps/" + fExpName + "/" + fExpName + " --debug --input-buffer=200Mi --event-sizes --allow-errors";
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
    //TString filename = "trans://x86l-144"; // ??
//    TString filename = "trans://x86l-86"; // ??.
    //TString filename = "trans://x86l-144"; // 
    //TString filename = "stream://x86l-182"; // bgo
    TString filename = "trans://lxg1257"; // timesorter.
    //TString filename = "trans://R4L-21"; // beammonitor
    // TString filename = "stream://x86l-87"; // bplast
    //TString filename = "stream://x86l-117"; // fatima tamex
    //TString filename = "~/lustre/gamma/dryrunmarch24/ts/Au_beam_0010_0001.lmd";
    //TString filename = "~/lustre/gamma/s100_files/ts/calibrations/152Eu_calib_0016_*.lmd";
    //TString filename = "~/lustre/gamma/s100_files/ts/168Dy_0033_0003.lmd";
    TString outputpath = "output";
    TString outputFileName = outputpath + ".root";

    // Create Online run
    Int_t refresh = 1; // Refresh rate for online histograms
    Int_t port = 5000; // Port number for online visualisation - use 5000 on lxg1301 during experiments as it has firewall access.

    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    //run->SetSink(new FairRootFileSink(outputFileName));
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);

    // trying to kill ParSet errors
    /*FairRuntimeDb* rtdb = FairRunOnline::Instance()->GetRuntimeDb();
    FairGeoParSet* geo = new FairGeoParSet("FairGeoParSet");
    FairBaseParSet* base = new FairBaseParSet("FairBaseParSet");
    rtdb->addContainer(geo);rtdb->addContainer(base);*/

    // Create source using ucesb for input
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK"; // Define which level of data to unpack - we don't use "RAW" or "CAL"
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
    
    
    // ------------------------------------------------------------------------------------ //
    // *** Initialise Correlations ******************************************************** //
    
    TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations_tight.dat");


    // ------------------------------------------------------------------------------------ //
    // *** Load Detector Configurations *************************************************** //
    TFatimaTwinpeaksConfiguration::SetDetectorConfigurationFile(config_path + "/fatima/fatima_alloc_apr18.txt");
    TFatimaTwinpeaksConfiguration::SetDetectorCoefficientFile(config_path + "/fatima/fatima_cal_apr18.txt");
    TFatimaTwinpeaksConfiguration::SetDetectorTimeshiftsFile(config_path + "/fatima/fatima_timeshifts_apr20.txt");
    TFatimaTwinpeaksConfiguration::SetPromptFlashCutFile(config_path + "/fatima/fatima_prompt_flash.root");

    TFatimaVmeConfiguration::SetDetectorMapFile(config_path + "/fatima/Fatima_VME_allocation.txt");
    TFatimaVmeConfiguration::Set_QDC_E_CalFile(config_path + "/fatima/Fatima_QDC_Energy_Calibration.txt");
    TFatimaVmeConfiguration::Set_QDC_T_CalFile(config_path + "/fatima/Fatima_QDC_Time_Calibration.txt");
    TFatimaVmeConfiguration::Set_TDC_T_CalFile(config_path + "/fatima/Fatima_TDC_Time_Calibration.txt");
    TAidaConfiguration::SetBasePath(config_path + "/AIDA");
    TbPlastConfiguration::SetDetectorMapFile(config_path + "/bplast/bplast_mapping_s100.txt");
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TGermaniumConfiguration::SetDetectorConfigurationFile(config_path + "/germanium/ge_alloc_apr15.txt");
    TGermaniumConfiguration::SetDetectorCoefficientFile(config_path + "/germanium/ge_cal_apr18.txt");
    TGermaniumConfiguration::SetDetectorTimeshiftsFile(config_path + "/germanium/ge_timeshifts_apr20.txt");
    TGermaniumConfiguration::SetPromptFlashCut(config_path + "/germanium/ge_prompt_flash.root");

    TBGOTwinpeaksConfiguration::SetDetectorConfigurationFile(config_path + "/bgo/bgo_alloc.txt");
    
    

    // ------------------------------------------------------------------------------------- //
    // *** Read Subsystems - comment out unwanted systems ********************************** //

    // EventHeader - should always be done
    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    
    source->AddReader(unpackheader);
    
    if (FATIMA_ON)
    {
        FatimaReader* unpackfatima = new FatimaReader((EXT_STR_h101_fatima_onion*)&ucesb_struct.fatima, offsetof(EXT_STR_h101, fatima));
        //unpackfatima->DoFineTimeCalOnline(config_path + "/fatima/fine_time_4apr_test.root", 100000);
        unpackfatima->SetInputFileFineTimeHistos(config_path + "/fatima/fine_time_4apr_test.root");

        unpackfatima->SetOnline(true);
        source->AddReader(unpackfatima);
    }
    
    if (FATIMA_VME_ON)
    {
        FatimaVmeReader* unpackfatimavme = new FatimaVmeReader((EXT_STR_h101_fatimavme_onion*)&ucesb_struct.fatimavme, offsetof(EXT_STR_h101, fatimavme));
        
        unpackfatimavme->SetOnline(true);
        source->AddReader(unpackfatimavme);
    }
    
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
        FrsMainReader* unpackfrsmain = new FrsMainReader((EXT_STR_h101_frsmain_onion*)&ucesb_struct.frsmain, offsetof(EXT_STR_h101, frsmain));
        FrsTPCReader* unpackfrstpc = new FrsTPCReader((EXT_STR_h101_frstpc_onion*)&ucesb_struct.frstpc, offsetof(EXT_STR_h101, frstpc));
        FrsUserReader* unpackfrsuser = new FrsUserReader((EXT_STR_h101_frsuser_onion*)&ucesb_struct.frsuser, offsetof(EXT_STR_h101, frsuser));
        FrsTpatReader* unpackfrstpat = new FrsTpatReader((EXT_STR_h101_frstpat_onion*)&ucesb_struct.frstpat, offsetof(EXT_STR_h101, frstpat));
        
        unpackfrsmain->SetOnline(true);
        unpackfrstpc->SetOnline(true);
        unpackfrsuser->SetOnline(true);
        unpackfrstpat->SetOnline(true);
        
        source->AddReader(unpackfrsmain);
        source->AddReader(unpackfrstpc);
        source->AddReader(unpackfrsuser);
        source->AddReader(unpackfrstpat);
    }
    
    if (BEAMMONITOR_ON)
    {
        BeamMonitorReader* unpackbeammonitor = new BeamMonitorReader((EXT_STR_h101_beammonitor_onion*)&ucesb_struct.beammonitor, offsetof(EXT_STR_h101, beammonitor));
        
        unpackbeammonitor->SetOnline(true);
        source->AddReader(unpackbeammonitor);
    }

   
    // ---------------------------------------------------------------------------------------- //
    // *** Calibrate Subsystems - comment out unwanted systems ******************************** //
    
    if (FATIMA_ON)
    {
        FatimaRaw2Cal* calfatima = new FatimaRaw2Cal();
        // calfatima->PrintDetectorMap();
        // calfatima->PrintDetectorCal();
        
        calfatima->SetOnline(true);
        run->AddTask(calfatima);
    }
    
    if (FATIMA_VME_ON)
    {
        FatimaVmeRaw2Cal* calfatimavme = new FatimaVmeRaw2Cal();
        
        calfatimavme->SetOnline(true);
        run->AddTask(calfatimavme);
        
    }
    
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
        FrsMainRaw2Cal* calfrsmain = new FrsMainRaw2Cal();
        FrsTPCRaw2Cal* calfrstpc = new FrsTPCRaw2Cal();
        FrsUserRaw2Cal* calfrsuser = new FrsUserRaw2Cal();
        
        calfrsmain->SetOnline(true);
        calfrstpc->SetOnline(true);
        calfrsuser->SetOnline(true);
        run->AddTask(calfrsmain);
        run->AddTask(calfrstpc);
        run->AddTask(calfrsuser);
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
        
        hitfrs->SetOnline(true); 
        run->AddTask(hitfrs);
    } 



    // ======================================================================================== //
    // =========== **** SPECTRA ***** ========================================================= //
    // ======================================================================================== //
    
    // ---------------------------------------------------------------------------------------- //
    // *** Online Spectra ********************************************************************* //
    
    if (FATIMA_ON)
    {
        FatimaOnlineSpectra* onlinefatima = new FatimaOnlineSpectra();
        onlinefatima->SetBinningSlowToT(2000,560,660);
        onlinefatima->SetBinningFastToT(1000,0.1,100.1);
        onlinefatima->SetBinningEnergy(2000,0,1500);

        std::vector<int> fat_dets = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43};
        onlinefatima->SetDetectorsToPlot(fat_dets);
        
         onlinefatima->AddReferenceDetectorForTimeDifferencesWithEnergyGates(1,1332);
        onlinefatima->SetEnergyGateWidth(20);
        //onlinefatima->SetReferenceDetectorsForTimeDifferences(1);
        
        run->AddTask(onlinefatima);
    }
    
    if (FATIMA_VME_ON)
    {    
        FatimaVmeOnlineSpectra* onlinefatimavme = new FatimaVmeOnlineSpectra();
        
        run->AddTask(onlinefatimavme);
    }
    
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
        onlinege->AddReferenceDetectorWithEnergyGates(1,0,1173,1332);
        onlinege->SetEnergyGateWidth(10);
        run->AddTask(onlinege);
    }
    TBGOTwinpeaksConfiguration::SetCoincidenceWindow(5000);
    TBGOTwinpeaksConfiguration::SetCoincidenceOffset(0);
    if (BGO_ON)
    {
        BGOOnlineSpectra* onlinebgo = new BGOOnlineSpectra();
        onlinebgo->SetBinningEnergy(1500,0.1,1500.1);

        run->AddTask(onlinebgo);
        
    }
    
    TFrsConfiguration::Set_Z_range(50,75);
    TFrsConfiguration::Set_AoQ_range(2.3,3.0);
    
    if (FRS_ON)
    {
        FrsOnlineSpectra* onlinefrs = new FrsOnlineSpectra();
        // For monitoring FRS on our side
        FrsRawSpectra* frsrawspec = new FrsRawSpectra();
        FrsCalSpectra* frscalspec = new FrsCalSpectra();
        
        run->AddTask(onlinefrs);
        run->AddTask(frsrawspec);
        run->AddTask(frscalspec);
    }
    
    if (BEAMMONITOR_ON)
    {
        BeamMonitorOnlineSpectra* onlinebm = new BeamMonitorOnlineSpectra();
        
        run->AddTask(onlinebm);
    }
    
    //FRS GATES::
    
    //FrsGate * frsgate170Er = new FrsGate("170Er",config_path+"/frs/Gates/170Er.root");
    //FrsGate * frsgate168Dy = new FrsGate("168Dy",config_path+"/frs/Gates/168Dy.root");
    //FrsGate * frsgate167Dy = new FrsGate("167Dy",config_path+"/frs/Gates/167Dy.root");
    //FrsGate * frsgateZDy = new FrsGate("ZDy",config_path+"/frs/Gates/ZDy.root");
    //FrsGate * frsgateZHo = new FrsGate("ZHo",config_path+"/frs/Gates/ZHo.root");
    FrsGate * frsgateZEu = new FrsGate("ZEu",config_path+"/frs/Gates/ZEu.root");
    FrsGate * frsgate162Eu = new FrsGate("162Eu",config_path+"/frs/Gates/162Eu.root");
    FrsGate * frsgate163Eu = new FrsGate("163Eu",config_path+"/frs/Gates/163Eu.root");
    FrsGate * frsgate167Tb = new FrsGate("167Tb",config_path+"/frs/Gates/167Tb.root");
    FrsGate * frsgate164Gd = new FrsGate("164Gd",config_path+"/frs/Gates/164Gd.root");
    
    if (AIDA_ON && FRS_ON){
        std::vector<FrsGate*> frsgates{};
        
        //frsgates.emplace_back(frsgate170Er);
        //frsgates.emplace_back(frsgate168Dy);
        //frsgates.emplace_back(frsgate167Dy);
        //frsgates.emplace_back(frsgate162Eu);
        //frsgates.emplace_back(frsgate163Eu);
        frsgates.emplace_back(frsgate167Tb);
        frsgates.emplace_back(frsgate164Gd);
        
        FrsAidaCorrelationsOnline * frsaida = new FrsAidaCorrelationsOnline(frsgates);
        
        run->AddTask(frsaida);
    }
    
    
    if (FRS_ON && GERMANIUM_ON){
        /*
        FrsGermaniumCorrelations * ge170Er = new FrsGermaniumCorrelations(frsgate170Er);
        run->AddTask(ge170Er);
        FrsGermaniumCorrelations * ge168Dy = new FrsGermaniumCorrelations(frsgate168Dy);
        ge168Dy->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(ge168Dy);
        FrsGermaniumCorrelations * ge167Dy = new FrsGermaniumCorrelations(frsgate167Dy);
        ge167Dy->AddGammaEnergyOfInterest(69,2);
        ge167Dy->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(ge167Dy);
        
        FrsGermaniumCorrelations * geZDy = new FrsGermaniumCorrelations(frsgateZDy);
        geZDy->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(geZDy);
        FrsGermaniumCorrelations * geZHo = new FrsGermaniumCorrelations(frsgateZHo);
        geZHo->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(geZHo);
        */
        FrsGermaniumCorrelations * ge162Eu = new FrsGermaniumCorrelations(frsgate162Eu);
        run->AddTask(ge162Eu);
        FrsGermaniumCorrelations * ge163Eu = new FrsGermaniumCorrelations(frsgate163Eu);
        ge163Eu->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(ge163Eu);
        FrsGermaniumCorrelations * geZEu = new FrsGermaniumCorrelations(frsgateZEu);
        geZEu->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(geZEu);
        
        FrsGermaniumCorrelations * ge167Tb = new FrsGermaniumCorrelations(frsgate167Tb);
        ge167Tb->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(ge167Tb);
        FrsGermaniumCorrelations * ge164Gd = new FrsGermaniumCorrelations(frsgate164Gd);
        ge164Gd->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(ge164Gd);
        
    }
    if (FRS_ON && FATIMA_ON){
        /*FrsFatimaCorrelations * fa170Er = new FrsFatimaCorrelations(frsgate170Er);
        run->AddTask(fa170Er);
        FrsFatimaCorrelations * fa168Dy = new FrsFatimaCorrelations(frsgate168Dy);
        fa168Dy->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(fa168Dy);
        FrsFatimaCorrelations * fa167Dy = new FrsFatimaCorrelations(frsgate167Dy);
        fa167Dy->AddGammaEnergyOfInterest(69,2);
        fa167Dy->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(fa167Dy);
        
        FrsFatimaCorrelations * faZDy = new FrsFatimaCorrelations(frsgateZDy);
        faZDy->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(faZDy);
        FrsFatimaCorrelations * faZHo = new FrsFatimaCorrelations(frsgateZHo);
        faZHo->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(faZHo);
        */
        
        FrsFatimaCorrelations * fat162Eu = new FrsFatimaCorrelations(frsgate162Eu);
        run->AddTask(fat162Eu);
        FrsFatimaCorrelations * fat163Eu = new FrsFatimaCorrelations(frsgate163Eu);
        fat163Eu->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(fat163Eu);
        FrsFatimaCorrelations * fatZEu = new FrsFatimaCorrelations(frsgateZEu);
        fatZEu->SetShortLifetimeCollectionWindow(5000);
        run->AddTask(fatZEu);
        
    }

    TString b = "Aida";
    TString c = "Fatima";
    TString d = "FatimaVme";
    TString e = "bPlast";
    TString f = "Germanium";

    if (TIME_MACHINE_ON) // a little complicated because it falls apart if the right subsystem is switched off
    {
        TimeMachineOnline* tms = new TimeMachineOnline();
        std::vector a {b, c, d, e, f};
        tms->SetDetectorSystems(a);
        
        run->AddTask(tms);
    }
    
    if (WHITE_RABBIT_CORS)
    {
        WhiterabbitCorrelationOnline* wronline = new WhiterabbitCorrelationOnline();
        wronline->SetDetectorSystems({b,c,d,e,f});
        
        run->AddTask(wronline);
    }

    // Initialise
    run->Init();
    
    FairLogger::GetLogger()->SetLogScreenLevel("info");

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "Online port server: " << port << endl;
    cout << "\n\n" << endl;

    // create sink object before run starts    
    FairSink* sf = FairRunOnline::Instance()->GetSink();

    // Run
    run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev); 

    // write online histograms if desired.
    //TFile* tf = new TFile(sf->GetFileName(), "UPDATE");
    //histograms->Write();

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

