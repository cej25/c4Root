// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsDetectorsOnline.h"
#include "FrsHitData.h"
#include "FrsMainCalData.h"
#include "EventHeader.h"
#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

FrsDetectorsOnline::FrsDetectorsOnline()
    : FrsDetectorsOnline("FrsDetectorsOnline", 1)
{
}

FrsDetectorsOnline::FrsDetectorsOnline(const TString& name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fFrsMainCalArray(NULL)
    , fFrsUserCalArray(NULL)
    , fFrsTPCCalArray(NULL)
    , fFrsVFTXCalArray(NULL)
    , fNEvents(0)
    , header(nullptr)
{
}

FrsDetectorsOnline::~FrsDetectorsOnline()
{
    c4LOG(info, "");
    if (fFrsMainCalArray)
        delete fFrsMainCalArray;
}

// Public Method SetParContainers
void FrsDetectorsOnline::SetParContainers()
{
    // Parameter Containers
    FairRuntimeDb* rtdb = FairRuntimeDb::instance(); // infuriating lack of consistency with capitalisation...
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus FrsDetectorsOnline::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fFrsMainCalArray = (TClonesArray*)mgr->GetObject("FrsMainCalData");
    c4LOG_IF(fatal, !fFrsMainCalArray, "Branch FrsMainCalData not found");
    fFrsUserCalArray = (TClonesArray*)mgr->GetObject("FrsUserCalData");
    c4LOG_IF(fatal, !fFrsUserCalArray, "Branch FrsUserCalData not found");
    fFrsTPCCalArray = (TClonesArray*)mgr->GetObject("FrsTPCCalData");
    c4LOG_IF(fatal, !fFrsMainCalArray, "Branch FrsTPCCalData not found");
    fFrsVFTXCalArray = (TClonesArray*)mgr->GetObject("FrsVFTXCalData");
    c4LOG_IF(fatal, !fFrsMainCalArray, "Branch FrsVFTXCalData not found");



    TFolder * frs_detectors_spectra_folder_histograms = new TFolder("frs_detectors_histograms", "frs_detectors_histograms");

    run->AddObject(frs_detectors_spectra_folder_histograms);

    //Main crate detectors:

    //SCIs
    int sc_xx_bins = 1000;
    int sc_xx_max_e= 4096; //12 bit adc
    h_sci_21l_de = new TH1D("h_sci_21l_de", "FRS Scintillator 21 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    frs_detectors_spectra_folder_histograms->Add(h_sci_21l_de);
    h_sci_21r_de = new TH1D("h_sci_21r_de", "FRS Scintillator 21 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    frs_detectors_spectra_folder_histograms->Add(h_sci_21r_de);
    h_sci_22l_de = new TH1D("h_sci_22l_de", "FRS Scintillator 22 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    frs_detectors_spectra_folder_histograms->Add(h_sci_22l_de);
    h_sci_22r_de = new TH1D("h_sci_22r_de", "FRS Scintillator 22 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    frs_detectors_spectra_folder_histograms->Add(h_sci_22r_de);
    h_sci_41l_de = new TH1D("h_sci_41l_de", "FRS Scintillator 41 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    frs_detectors_spectra_folder_histograms->Add(h_sci_41l_de);
    h_sci_41r_de = new TH1D("h_sci_41r_de", "FRS Scintillator 41 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    frs_detectors_spectra_folder_histograms->Add(h_sci_41r_de);
    h_sci_42l_de = new TH1D("h_sci_42l_de", "FRS Scintillator 42 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    frs_detectors_spectra_folder_histograms->Add(h_sci_42l_de);
    h_sci_42r_de = new TH1D("h_sci_42r_de", "FRS Scintillator 42 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    frs_detectors_spectra_folder_histograms->Add(h_sci_42r_de);
    h_sci_43l_de = new TH1D("h_sci_43l_de", "FRS Scintillator 43 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    frs_detectors_spectra_folder_histograms->Add(h_sci_43l_de);
    h_sci_43r_de = new TH1D("h_sci_43r_de", "FRS Scintillator 43 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    frs_detectors_spectra_folder_histograms->Add(h_sci_43r_de);
    h_sci_81l_de = new TH1D("h_sci_81l_de", "FRS Scintillator 81 l energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    frs_detectors_spectra_folder_histograms->Add(h_sci_81l_de);
    h_sci_81r_de = new TH1D("h_sci_81r_de", "FRS Scintillator 81 r energy V792 main crate", sc_xx_bins,0,sc_xx_max_e);
    frs_detectors_spectra_folder_histograms->Add(h_sci_81r_de);

    int sc_xx_bins_t = 1000;
    double sc_xx_max_t = 1048576; // 2^20 bits in v1290 data word
    h_sci_21l_t = new TH1D("h_sci_21l_t", "FRS Scintillator 21 l time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    frs_detectors_spectra_folder_histograms->Add(h_sci_21l_t);
    h_sci_21r_t = new TH1D("h_sci_21r_t", "FRS Scintillator 21 r time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    frs_detectors_spectra_folder_histograms->Add(h_sci_21r_t);
    h_sci_22l_t = new TH1D("h_sci_22l_t", "FRS Scintillator 22 l time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    frs_detectors_spectra_folder_histograms->Add(h_sci_22l_t);
    h_sci_22r_t = new TH1D("h_sci_22r_t", "FRS Scintillator 22 r time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    frs_detectors_spectra_folder_histograms->Add(h_sci_22r_t);
    h_sci_41l_t = new TH1D("h_sci_41l_t", "FRS Scintillator 41 l time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    frs_detectors_spectra_folder_histograms->Add(h_sci_41l_t);
    h_sci_41r_t = new TH1D("h_sci_41r_t", "FRS Scintillator 41 r time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    frs_detectors_spectra_folder_histograms->Add(h_sci_41r_t);
    h_sci_42l_t = new TH1D("h_sci_42l_t", "FRS Scintillator 42 l time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    frs_detectors_spectra_folder_histograms->Add(h_sci_42l_t);
    h_sci_42r_t = new TH1D("h_sci_42r_t", "FRS Scintillator 42 r time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    frs_detectors_spectra_folder_histograms->Add(h_sci_42r_t);
    h_sci_43l_t = new TH1D("h_sci_43l_t", "FRS Scintillator 43 l time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    frs_detectors_spectra_folder_histograms->Add(h_sci_43l_t);
    h_sci_43r_t = new TH1D("h_sci_43r_t", "FRS Scintillator 43 r time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    frs_detectors_spectra_folder_histograms->Add(h_sci_43r_t);
    h_sci_81l_t = new TH1D("h_sci_81l_t", "FRS Scintillator 81 l time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    frs_detectors_spectra_folder_histograms->Add(h_sci_81l_t);
    h_sci_81r_t = new TH1D("h_sci_81r_t", "FRS Scintillator 81 r time V1190 main crate",sc_xx_bins_t,0,sc_xx_max_t);
    frs_detectors_spectra_folder_histograms->Add(h_sci_81r_t);
    
    //MUSIC timings:
    int music_xx_bins = 1000;
    double music_xx_max_t = 1048576; // 2^20 bits in v1290 data word
    h_music41_t = new TH2D("h_music41_t", "FRS MUSIC 41 Timestamps V1190 main crate",8,-0.5,7.5,music_xx_bins,0,music_xx_max_t);
    frs_detectors_spectra_folder_histograms->Add(h_music41_t);
    h_music42_t = new TH2D("h_music42_t", "FRS MUSIC 42 Timestamps V1190 main crate",8,-0.5,7.5,music_xx_bins,0,music_xx_max_t); 
    frs_detectors_spectra_folder_histograms->Add(h_music42_t);

    





    // Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_IncomingID_HIST", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;

}

void FrsDetectorsOnline::Reset_Histo()
{
    c4LOG(info, "");
   // fh1_TdcRaw->Clear();
   // fh1_TdcChan->Clear();
}

void FrsDetectorsOnline::Exec(Option_t* option)
{
    // MainCrate:
    if (fFrsMainCalArray && fFrsMainCalArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fFrsMainCalArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            fHitFrsMainCal = (FrsMainCalData*)fFrsMainCalArray->At(ihit);
            if (!fHitFrsMainCal)
                continue;
                    
        const uint32_t* sci_de = fHitFrsMainCal->Get_De_array(); // size 14
        uint32_t sci_21l_de = sci_de[1];
        uint32_t sci_21r_de = sci_de[2];  
        uint32_t sci_22l_de = sci_de[13];  
        uint32_t sci_22r_de = sci_de[6];  
        uint32_t sci_41l_de = sci_de[0];  
        uint32_t sci_41r_de = sci_de[11];  
        uint32_t sci_42l_de = sci_de[3];  
        uint32_t sci_42r_de = sci_de[4];  
        uint32_t sci_43l_de = sci_de[9];  
        uint32_t sci_43r_de = sci_de[10];  
        uint32_t sci_81l_de = sci_de[5];  
        uint32_t sci_81r_de = sci_de[12];

        h_sci_21l_de->Fill(sci_21l_de);
        h_sci_21r_de->Fill(sci_21r_de);
        h_sci_22l_de->Fill(sci_22l_de);
        h_sci_22r_de->Fill(sci_22r_de);
        h_sci_41l_de->Fill(sci_41l_de);
        h_sci_41r_de->Fill(sci_41r_de);
        h_sci_42l_de->Fill(sci_42l_de);
        h_sci_42r_de->Fill(sci_42r_de);
        h_sci_43l_de->Fill(sci_43l_de);
        h_sci_43r_de->Fill(sci_43r_de);
        h_sci_81l_de->Fill(sci_81l_de);
        h_sci_81r_de->Fill(sci_81r_de);

        //music timings:
        const uint32_t* music_t1 = fHitFrsMainCal->Get_music_t1(); // size 8 arrays
        const uint32_t* music_t2 = fHitFrsMainCal->Get_music_t2(); // size 8 arrays
        if (music_t1!=nullptr && music_t2 != nullptr) for (int anode = 0; anode<8; anode++) {h_music41_t->Fill(anode,music_t1[anode]); h_music42_t->Fill(anode,music_t1[anode]);}
        
        
        std::vector<uint32_t> sci_21l_t = fHitFrsMainCal->Get_TDC_channel(2);
        if (sci_21l_t.size()>0) h_sci_21l_t->Fill(sci_21l_t.at(0));
        std::vector<uint32_t> sci_21r_t = fHitFrsMainCal->Get_TDC_channel(3);
        if (sci_21r_t.size()>0) h_sci_21r_t->Fill(sci_21r_t.at(0));
        std::vector<uint32_t> sci_22l_t = fHitFrsMainCal->Get_TDC_channel(12);
        if (sci_22l_t.size()>0) h_sci_22l_t->Fill(sci_22l_t.at(0));
        std::vector<uint32_t> sci_22r_t = fHitFrsMainCal->Get_TDC_channel(13);
        if (sci_22r_t.size()>0) h_sci_22r_t->Fill(sci_22r_t.at(0));
        std::vector<uint32_t> sci_41l_t = fHitFrsMainCal->Get_TDC_channel(0);
        if (sci_41l_t.size()>0) h_sci_41l_t->Fill(sci_41l_t.at(0));
        std::vector<uint32_t> sci_41r_t = fHitFrsMainCal->Get_TDC_channel(1);
        if (sci_41r_t.size()>0) h_sci_41r_t->Fill(sci_41r_t.at(0));
        std::vector<uint32_t> sci_42l_t = fHitFrsMainCal->Get_TDC_channel(4);
        if (sci_42l_t.size()>0) h_sci_42l_t->Fill(sci_42l_t.at(0));
        std::vector<uint32_t> sci_42r_t = fHitFrsMainCal->Get_TDC_channel(14);
        if (sci_42r_t.size()>0) h_sci_42r_t->Fill(sci_42r_t.at(0));
        std::vector<uint32_t> sci_43l_t = fHitFrsMainCal->Get_TDC_channel(5);
        if (sci_43l_t.size()>0) h_sci_43l_t->Fill(sci_43l_t.at(0));
        std::vector<uint32_t> sci_43r_t = fHitFrsMainCal->Get_TDC_channel(6);
        if (sci_43r_t.size()>0) h_sci_43r_t->Fill(sci_43r_t.at(0));
        std::vector<uint32_t> sci_81l_t = fHitFrsMainCal->Get_TDC_channel(7);
        if (sci_81l_t.size()>0) h_sci_81l_t->Fill(sci_81l_t.at(0));
        std::vector<uint32_t> sci_81r_t = fHitFrsMainCal->Get_TDC_channel(8);
        if (sci_81r_t.size()>0) h_sci_81r_t->Fill(sci_81r_t.at(0));




            
        }
    }

    fNEvents += 1;
}

void FrsDetectorsOnline::FinishEvent()
{
    if(fFrsUserCalArray) fFrsUserCalArray->Clear();
    if(fFrsMainCalArray) fFrsMainCalArray->Clear();
    if(fFrsTPCCalArray) fFrsTPCCalArray->Clear();
    if(fFrsVFTXCalArray) fFrsVFTXCalArray->Clear();
}

void FrsDetectorsOnline::FinishTask()
{
    
}

ClassImp(FrsDetectorsOnline)