#include <TROOT.h>

// Switch all tasks related to {subsystem} on (1)/off (0)
#define LISA_ON 1
#define FRS_ON 1
#define TRAV_MUSIC_ON 1
#define WHITE_RABBIT_CORS 0 // does not work w/o aida currently

// Define FRS setup.C file - FRS should provide; place in /config/pareeksha/frs/
extern "C"
{
    #include "../../config/pareeksha/frs/setup_Fragment_conv.C"
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

void pareeksha_histos(int fileNumber)
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
    //___O F F L I N E
    TString inputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/pareeksha_trees/fragments_EG_test/";
    TString filename = Form(inputpath + "run_%04d_EG.root", fileNumber);  
    
    //___O U T P U T
    //TString outputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/pareeksha_histos/fragments_EG_101gate/"; //test output
    TString outputpath = "/u/gandolfo/data/"; //test output

    //TString outputpath = "/u/gandolfo/data/lustre/gamma/LISA/data/pareeksha_histos/fragments_noGate/";
    TString outputFilename = Form(outputpath + "run_%04d_histos.root", fileNumber);


    FairRunAna* run = new FairRunAna();
    EventHeader* EvtHead = new EventHeader();
    run->SetEventHeader(EvtHead);
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(outputFilename)); // don't write after termintion
    FairSource* fs = new FairFileSource(filename);
    run->SetSource(fs);
    
    //Read tree evt
    TFile* file = TFile::Open(filename);
    TTree* eventTree = (TTree*)file->Get("evt"); 
    Int_t totEvt = eventTree->GetEntries();
     
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

    std::vector<FrsGate*> fg;
    FrsGate* cut_0 = new FrsGate("cut", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/all_z_1.root"); 
    FrsGate* cut_1 = new FrsGate("0", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/1p1n.root"); 
    FrsGate* cut_2 = new FrsGate("1", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/1p2n.root"); 
    FrsGate* cut_3 = new FrsGate("2", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/all_z_2.root"); 
    FrsGate* cut_4 = new FrsGate("2", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/2p3n.root"); 
    FrsGate* cut_5 = new FrsGate("2", "/u/gandolfo/c4/c4Root/config/pareeksha/frs/Gates/2p4n.root"); 

    
    fg.emplace_back(cut_0);
    fg.emplace_back(cut_1);
    fg.emplace_back(cut_2);
    fg.emplace_back(cut_3);
    fg.emplace_back(cut_4);
    fg.emplace_back(cut_5);

    //:::: Gates for histos ::::::::
    TFrsConfiguration::Set_dE_travMusic_gate(1940,2000);
    TLisaConfiguration::SetLISAGate(1070,1110); //Gate on LISA 1 for histo of LISA 2 energy (mean +- 3sigma)
    //98Nb -> 1090 (6.6)
    //96Zr -> 1044 (8)
    //95Zr -> 1027 (5)
    //after98Nb -> 1171 (9)
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::: C O R R E L A T I O N S - Initialise 
  
    TCorrelationsConfiguration::SetCorrelationsFile(config_path + "/correlations_tight.dat");

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::::: C O N F I G    F O R   D E T E C T O R - Load
    // ::: FRS config
    TFrsConfiguration::SetConfigPath(config_path + "/frs/");
    TFrsConfiguration::SetTravMusDriftFile(config_path + "/frs/TM_Drift_fragments.txt");
    TFrsConfiguration::SetZ1DriftFile(config_path + "/frs/Z1_Drift_fragments.txt");
    TFrsConfiguration::SetAoQDriftFile(config_path + "/frs/AoQ_Drift_fragments.txt");

    // ::: LISA config
    TLisaConfiguration::SetMappingFile(config_path + "/lisa/Lisa_Detector_Map_names.txt");
    TLisaConfiguration::SetGMFile(config_path + "/lisa/Lisa_GainMatching.txt");

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::   
    // =========== **** SPECTRA ***** ========================================================= //
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    

    
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::    
    // ::: Nearline Spectra ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    
    // ::: Set experiment star time :::
    TExperimentConfiguration::SetExperimentStart(1715734200000000000); //Start of pareeksha with primary beam: 15 May 00:50
    // ::: Get run number :::
    TFrsConfiguration::SetRunNumber(fileNumber);
    std::cout << "Run number: " << fileNumber << std::endl;

    

    //::::::::: Set ranges for histos :::::::::::::::
    //::::  Channel Energy ::::: (h1_energy_layer_ch)
    TLisaConfiguration::SetEnergyRange(500000,3000000);
    TLisaConfiguration::SetEnergyBin(900);

    //::::  Channel Energy GM ::::: (h1_energy_layer_ch)
    TLisaConfiguration::SetEnergyRangeGM(300,1500);
    TLisaConfiguration::SetEnergyBinGM(900);

    //:::: LISA WR Time Difference :::::: (h1_wr_diff)
    TLisaConfiguration::SetWrDiffRange(0,100000000);
    TLisaConfiguration::SetWrDiffBin(20000);

    //:::: FRS Z and AoQ
    TFrsConfiguration::Set_Z_range(20,60);
    TFrsConfiguration::Set_AoQ_range(1,3);
    

    if (LISA_ON)
    {
        // Add analysis task here at some point
        LisaNearlineSpectra* nearlinelisa = new LisaNearlineSpectra();

        run->AddTask(nearlinelisa);

    }
    
    if (FRS_ON)
    {
        FrsNearlineSpectra* nearlinefrs = new FrsNearlineSpectra();
        run->AddTask(nearlinefrs);

        
        if (TRAV_MUSIC_ON)
        {
            TravMusNearlineSpectra* nearlinetravmus = new TravMusNearlineSpectra();
            run->AddTask(nearlinetravmus);
        
            FrsTravMusCorrelations* nearlinetravmusfrs = new FrsTravMusCorrelations();
            run->AddTask(nearlinetravmusfrs);

        }
        
    }

    if(LISA_ON && FRS_ON & TRAV_MUSIC_ON)
    {
        LisaFrsCorrelations* LISA_FRS_corr = new LisaFrsCorrelations(fg);
        run->AddTask(LISA_FRS_corr);
    }

    TString c = "Lisa";
    TString d = "Frs";
    TString e = "TravMus";

    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::: Correlation Spectra :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    // FrsLisa

    // Initialise
    run->Init();

    // Run
    run->Run(0, totEvt); 

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
}
