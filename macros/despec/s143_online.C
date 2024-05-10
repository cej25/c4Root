#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define FIMP_ON 1
#define FATIMA_ON 1
#define FRS_ON 1
#define TRAV_MUSIC_ON 0
#define WHITE_RABBIT_CORS 0 // does not work w/o aida currently

// Define FRS setup.C file - FRS should provide; place in /config/{expName}/frs/
extern "C"
{
    #include "../../config/s100/frs/setup_des_s100_030_2024_conv.C"
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fimp_onion_t fimp;
    EXT_STR_h101_fatima_onion_t fatima;
    EXT_STR_h101_travmus_onion_t travmus;
    EXT_STR_h101_frsmain_onion_t frsmain;
    EXT_STR_h101_frstpc_onion_t frstpc;
    EXT_STR_h101_frsuser_onion_t frsuser;
    EXT_STR_h101_frstpat_onion_t frstpat;
    
} EXT_STR_h101;

void s143_online()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    // Name your experiment. Make sure all relevant directories are named identically.
    TString fExpName = "s143";

    // Define important paths.
    TString c4Root_path = "/u/cjones/c4Root";
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
    TString filename = "~/fimp/testfile.lmd";
    TString outputFilename = "fimp_test.root";	

    // Create online run
    Int_t refresh = 2; // Refresh rate for online histograms
    Int_t port = 6969;

    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    //run->SetSink(new FairRootFileSink(outputFileName)); // don't write after termintion
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);
     
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
    //TFatimaTwinpeaksConfiguration::SetDetectorCoefficientFile(config_path + "/fatima/fatima_cal_apr18.txt");
    //TFatimaTwinpeaksConfiguration::SetDetectorTimeshiftsFile(config_path + "/fatima/fatima_timeshifts_apr20.txt");
    //TFatimaTwinpeaksConfiguration::SetPromptFlashCutFile(config_path + "/fatima/fatima_prompt_flash.root");
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TFimpConfiguration::SetMappingFile(config_path + "/fimp/FIMP_Channel_MAP.txt");


    // ------------------------------------------------------------------------------------- //
    // *** Read Subsystems - comment out unwanted systems ********************************** //

    UnpackReader* unpackheader = new UnpackReader((EXT_STR_h101_unpack*)&ucesb_struct.eventheaders, offsetof(EXT_STR_h101, eventheaders));
    source->AddReader(unpackheader);

    if (FATIMA_ON)
    {
        FatimaReader* unpackfatima = new FatimaReader((EXT_STR_h101_fatima_onion*)&ucesb_struct.fatima, offsetof(EXT_STR_h101, fatima));
        //unpackfatima->DoFineTimeCalOnline(config_path + "/fatima/fine_time_14may_test.root", 100000);
        unpackfatima->SetInputFileFineTimeHistos(config_path + "/fatima/fine_time_23apr_beamON.root");

        unpackfatima->SetOnline(true);
        source->AddReader(unpackfatima);
    }

    if (FIMP_ON)
    {
        FimpReader* unpackfimp = new FimpReader((EXT_STR_h101_fimp_onion*)&ucesb_struct.fimp, offsetof(EXT_STR_h101, fimp));
        //unpackfimp->DoFineTimeCalOnline("fine_time_14may_test.root", 100000);
        unpackfimp->SetInputFileFineTimeHistos(config_path + "/fimp/ft_test.root");

        unpackfimp->SetOnline(true);
        source->AddReader(unpackfimp);
    }

    if (FRS_ON)
    {   
        if (TRAV_MUSIC_ON)
        {
            FrsTravMusReader* unpacktravmus = new FrsTravMusReader((EXT_STR_h101_travmus_onion*)&ucesb_struct.travmus, offsetof(EXT_STR_h101, travmus));
    
            unpacktravmus->SetOnline(true);
            source->AddReader(unpacktravmus);
        }

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


    // ---------------------------------------------------------------------------------------- //
    // *** Calibrate Subsystems - comment out unwanted systems ******************************** //

    if (FATIMA_ON)
    {
        FatimaRaw2Cal* calfatima = new FatimaRaw2Cal();
        
        calfatima->SetOnline(true);
        run->AddTask(calfatima);
    }

    if (FIMP_ON)
    {
        FimpRaw2Cal* calfimp = new FimpRaw2Cal();

        calfimp->SetOnline(true);
        run->AddTask(calfimp);
    }

    if (FRS_ON)
    {
        if (TRAV_MUSIC_ON)
        {
            FrsTravMusRaw2Cal* caltravmus = new FrsTravMusRaw2Cal();

            caltravmus->SetOnline(true);
            run->AddTask(caltravmus);
        }

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

        std::vector<int> fat_dets = {1,2,3,4,5,6,7,8}; // maybe 6-8 with additional signals?
        onlinefatima->SetDetectorsToPlot(fat_dets);

        run->AddTask(onlinefatima);
    }

    if (FIMP_ON)
    {
        // Add analysis task here at some point
        FimpOnlineSpectra* onlinefimp = new FimpOnlineSpectra();

        run->AddTask(onlinefimp);
    }

    TFrsConfiguration::Set_Z_range(50,75);
    TFrsConfiguration::Set_AoQ_range(2.3,3.0);
    
    if (FRS_ON)
    {
        if (TRAV_MUSIC_ON)
        {
            FrsTravMusSpectra* onlinetravmus = new FrsTravMusSpectra();
            run->AddTask(onlinetravmus);
        }

        FrsOnlineSpectra* onlinefrs = new FrsOnlineSpectra();
        // For monitoring FRS on our side
        // FrsRawSpectra* frsrawspec = new FrsRawSpectra();
        // FrsCalSpectra* frscalspec = new FrsCalSpectra();
        
        run->AddTask(onlinefrs);
        // run->AddTask(frsrawspec);
        // run->AddTask(frscalspec);
    }

    TString b = "Fatima";
    TString c = "Fimp";
    TString d = "Frs";
    TString e = "TravMus";

    if (WHITE_RABBIT_CORS)
    {
        WhiterabbitCorrelationOnline* wronline = new WhiterabbitCorrelationOnline();
        wronline->SetDetectorSystems({b,c,d,e});
        
        run->AddTask(wronline);
    }


    // ---------------------------------------------------------------------------------------- //
    // *** Correlations Spectra *************************************************************** //

    // FrsFimp
    // LaBr3Fimp
    // FrsLaBr3

    // Initialise
    run->Init();

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "FIMP online port server: " << port << endl;
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
