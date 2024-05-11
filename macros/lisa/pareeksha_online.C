#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
#define FATIMA_ON 1
#define FRS_ON 1
#define TRAV_MUSIC_ON 1
#define WHITE_RABBIT_CORS 0 // does not work w/o aida currently

// Define FRS setup.C file - FRS should provide; place in /config/pareeksha/frs/
extern "C"
{
    #include "../../config/pareeksha/frs/setup_des_s100_030_2024_conv.C"
}

typedef struct EXT_STR_h101_t
{   
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_lisa_onion_t lisa;
    EXT_STR_h101_travmus_onion_t travmus;
    EXT_STR_h101_frsmain_onion_t frsmain;
    EXT_STR_h101_frstpc_onion_t frstpc;
    EXT_STR_h101_frsuser_onion_t frsuser;
    EXT_STR_h101_frstpat_onion_t frstpat;


} EXT_STR_h101;

void pareeksha_online()
{   
    const Int_t nev = -1; const Int_t fRunId = 1; const Int_t fExpId = 1;
    //:::::::::Experiment name
    TString fExpName = "pareeksha";

    //:::::::::Here you define commonly used path
    TString c4Root_path = "/u/gandolfo/c4/c4Root";
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
    //___O N L I N E
    //TString filename = "stream://x86l-166"; //lisa daq (not time sorted/stitched)
    TString filename = "trans://lxg1257:6000"; // time stitched

    //___O F F L I N E
    //TString filename = "/u/gandolfo/data/lustre/despec/lisa/daq_test_0167_*.lmd";  //data with only lisa
    //TString filename = "/u/gandolfo/data/lustre/despec/s092_s143/daqtest/daqtest_0001_0001.lmd"; //data from ts folder

    //___O U T P U T
    TString outputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/c4data/";
    TString outputFilename = outputpath + "pareeksha_test.root";


    //:::::::Create online run
    Int_t refresh = 10; // Refresh rate for online histograms
    Int_t port = 2222;
     
    FairRunOnline* run = new FairRunOnline();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    //run->SetSink(new FairRootFileSink(outputFileName)); // don't write after termintion
    run->ActivateHttpServer(refresh, port);
    TFolder* histograms = new TFolder("Histograms", "Histograms");
    FairRootManager::Instance()->Register("Histograms", "Histogram Folder", histograms, false);
    run->AddObject(histograms);
     
    //:::::::Take ucesb input and create source
    EXT_STR_h101 ucesb_struct;
    TString ntuple_options = "UNPACK"; //level of unpacked data (UNPACK,RAW,CAL)
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
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TLisaConfiguration::SetMappingFile(config_path + "/lisa/Lisa_Detector_Map_names.txt");

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

        unpacklisa->SetOnline(true); //false= write to a tree; true=doesn't write to tree
        source->AddReader(unpacklisa);
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


    // ::::::: CALIBRATE Subsystem  ::::::::

    if (LISA_ON)
        {
            LisaRaw2Cal* lisaraw2cal = new LisaRaw2Cal();

            lisaraw2cal->SetOnline(true);
            run->AddTask(lisaraw2cal);
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


    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    // ::::::: ANALYSE Subsystem  ::::::::

    if (FRS_ON)
    {
        FrsCal2Hit* hitfrs = new FrsCal2Hit();
        
        hitfrs->SetOnline(true); 
        run->AddTask(hitfrs);
    } 

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::   
    // =========== **** SPECTRA ***** ========================================================= //
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    

    
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    // ::: Online Spectra ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //::::::::: Set ranges for histos :::::::::::::::
    //::::  Channel Energy ::::: (h1_energy_layer_ch)
    TLisaConfiguration::SetEnergyRange(600000,900000);
    TLisaConfiguration::SetEnergyBin(900);

    //:::: LISA WR Time Difference :::::: (h1_wr_diff)
    TLisaConfiguration::SetWrDiffRange(0,100000000);
    TLisaConfiguration::SetWrDiffBin(20000);




    if (LISA_ON)
    {
        // Add analysis task here at some point
        LisaOnlineSpectra* onlinelisa = new LisaOnlineSpectra();

        run->AddTask(onlinelisa);

    }

    TFrsConfiguration::Set_Z_range(50,75);
    TFrsConfiguration::Set_AoQ_range(2.3,3.0);
    
    if (FRS_ON)
    {
        FrsOnlineSpectra* onlinefrs = new FrsOnlineSpectra();
        // For monitoring FRS on our side
        // FrsRawSpectra* frsrawspec = new FrsRawSpectra();
        // FrsCalSpectra* frscalspec = new FrsCalSpectra();
        
        run->AddTask(onlinefrs);
        // run->AddTask(frsrawspec);
        // run->AddTask(frscalspec);

        if (TRAV_MUSIC_ON)
        {
            FrsTravMusSpectra* onlinetravmus = new FrsTravMusSpectra();
            //add task for raw spec?
            run->AddTask(onlinetravmus);
        }
    }

    TString c = "Lisa";
    TString d = "Frs";
    TString e = "TravMus";

    if (WHITE_RABBIT_CORS)
    {
        WhiterabbitCorrelationOnline* wronline = new WhiterabbitCorrelationOnline();
        wronline->SetDetectorSystems({c,d,e});
        
        run->AddTask(wronline);
    }

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: Correlation Spectra :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    if(LISA_ON && FRS_ON)
    {
        LisaFrsCorrelations* LISA_FRS_corr = new LisaFrsCorrelations();
        run->AddTask(LISA_FRS_corr);
    }

    // FrsLisa

    // Initialise
    run->Init();

    // Information about portnumber and main data stream
    cout << "\n\n" << endl;
    cout << "Data stream is: " << filename << endl;
    cout << "LISA online port server: " << port << endl;
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
