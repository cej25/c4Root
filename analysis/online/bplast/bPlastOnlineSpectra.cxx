// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "bPlastOnlineSpectra.h"
#include "EventHeader.h"
#include "bPlastTwinpeaksCalData.h"
#include "TbPlastConfiguration.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include "TROOT.h"
#include "TDirectory.h"

bPlastOnlineSpectra::bPlastOnlineSpectra() : bPlastOnlineSpectra("bPlastOnlineSpectra")
{
}

bPlastOnlineSpectra::bPlastOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitbPlastTwinpeaks(NULL)
    , fNEvents(0)
    , header(nullptr)
{
}

bPlastOnlineSpectra::~bPlastOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitbPlastTwinpeaks)
        delete fHitbPlastTwinpeaks;
}

void bPlastOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus bPlastOnlineSpectra::Init()
{

    // set batch mode
    gROOT->SetBatch(kTRUE);
    // number of dets 

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitbPlastTwinpeaks = (TClonesArray*)mgr->GetObject("bPlastTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitbPlastTwinpeaks, "Branch bPlastTwinpeaksCalData not found!");

    TDirectory::TContext ctx(nullptr);

    // bPlast Configuration
    bplast_conf = TbPlastConfiguration::GetInstance();
    nDetectors = bplast_conf->NDetectors();
    nTamexBoards = bplast_conf->NTamexBoards();

    // create folders
    folder_bplast = new TFolder("bPlast", "bPlast");

    run->AddObject(folder_bplast);

    folder_bplast_slowToT = new TFolder("Slow ToT", "bPlast_slowToT");
    folder_bplast_fastToT = new TFolder("Fast ToT", "bPlast_fastToT");
    folder_bplast_hitpattern = new TFolder("Hit Pattern", "bPlast_hitpattern");
    folder_bplast_fast_v_slow = new TFolder("Fast Vs. Slow", "bPlast_fast_v_slow");
    folder_bplast_time_spectra = new TFolder("Time Spectra", "bPlast_time_spectra");
    folder_bplast->Add(folder_bplast_slowToT);
    folder_bplast->Add(folder_bplast_fastToT);
    folder_bplast->Add(folder_bplast_hitpattern);
    folder_bplast->Add(folder_bplast_fast_v_slow);
    folder_bplast->Add(folder_bplast_time_spectra);

    // Setting histogram sizes
    h1_bplast_slowToT.resize(nDetectors+1); // index from 1 
    h1_bplast_fastToT.resize(nDetectors+1);
    h1_bplast_hitpatterns.resize(2); // this is hard coded yeah i know, but we aren't going to more bplasts?
    h1_bplast_tamex_card_hitpattern.resize(nTamexBoards);
    h2_bplast_fastToT_vs_slowToT.resize(nDetectors+1);
    h1_bplast_time_spectra.resize(nDetectors+1);

    // energy spectra:
    c_bplast_slowToT  = new TCanvas("c_bplast_slowToT","slow ToT bPlast spectra",1200,800);
    c_bplast_slowToT->Divide(5,(nDetectors%5==0) ? (nDetectors/5) : (nDetectors/5 + 1));

    for (int ihist = 1; ihist <= nDetectors; ihist++){
        c_bplast_slowToT->cd(ihist);
        h1_bplast_slowToT[ihist] = new TH1F(Form("h1_bplast_slowToT_%d",ihist),Form("bPlastic Slow ToT %d",ihist),10000,0,3.5e3);
        h1_bplast_slowToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_bplast_slowToT[ihist]->Draw();   
        folder_bplast_slowToT->Add(h1_bplast_slowToT[ihist]);
      
    }
    c_bplast_slowToT->cd(0);

    folder_bplast->Add(c_bplast_slowToT);

    // energy spectra:
    c_bplast_fastToT  = new TCanvas("c_bplast_fastToT","Fast ToT bPlast spectra",1200,800);
    c_bplast_fastToT->Divide(5,(nDetectors%5==0) ? (nDetectors/5) : (nDetectors/5 + 1));
    
    for (int ihist = 1; ihist <= nDetectors; ihist++){
        c_bplast_fastToT->cd(ihist);
        h1_bplast_fastToT[ihist] = new TH1F(Form("h1_bplast_fastToT_%d",ihist),Form("bPlastic Fast ToT %d",ihist),10000,0,3.5e3);
        h1_bplast_fastToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_bplast_fastToT[ihist]->Draw();   
        folder_bplast_fastToT->Add(h1_bplast_fastToT[ihist]);
    }
    c_bplast_fastToT->cd(0);

    folder_bplast->Add(c_bplast_fastToT);

    // hit pattern:

    
    c_bplast_hitpatterns  = new TCanvas("c_bplast_hitpatterns","bPlast Hit Pattern",1200,800);
    c_bplast_hitpatterns->Divide(2,1);
 
    c_bplast_hitpatterns->cd(1);
    h1_bplast_hitpatterns[0] = new TH1F("h1_bplast_hitpattern_upstream","Upstream detector hit patterns",64,1,65);
    h1_bplast_hitpatterns[0]->GetXaxis()->SetTitle("Detector ID");
    h1_bplast_hitpatterns[0]->GetYaxis()->SetTitle("Counts");
    h1_bplast_hitpatterns[0]->Draw();
    folder_bplast_hitpattern->Add(h1_bplast_hitpatterns[0]);
    c_bplast_hitpatterns->cd(2);
    h1_bplast_hitpatterns[1] = new TH1F("h1_bplast_hitpattern_downstream","Downstream detector hit patterns",64,65,129);
    h1_bplast_hitpatterns[1]->GetXaxis()->SetTitle("Detector ID");
    h1_bplast_hitpatterns[1]->GetYaxis()->SetTitle("Counts");
    h1_bplast_hitpatterns[1]->Draw();
    folder_bplast_hitpattern->Add(h1_bplast_hitpatterns[1]);
    c_bplast_hitpatterns->cd(0);

    folder_bplast->Add(c_bplast_hitpatterns);

    // tamex card hit pattern

    c_bplast_tamex_card_hitpattern  = new TCanvas("c_bplast_tamex_card_hitpattern","bPlast Tamex Card Hit Pattern",1200,800);
    c_bplast_tamex_card_hitpattern->Divide(5,(nTamexBoards%5==0) ? (nTamexBoards/5) : (nTamexBoards/5 + 1));

    for (int ihist = 0; ihist < nTamexBoards; ihist++){
        c_bplast_tamex_card_hitpattern->cd(ihist+1);
        h1_bplast_tamex_card_hitpattern[ihist] = new TH1F(Form("h1_bplast_tamex_card_hitpattern_%d",ihist),Form("bPlastic Tamex Card Hit Pattern %d",ihist),16,1,17);
        h1_bplast_tamex_card_hitpattern[ihist]->GetXaxis()->SetTitle("Channel");
        h1_bplast_tamex_card_hitpattern[ihist]->GetYaxis()->SetTitle("Counts");
        h1_bplast_tamex_card_hitpattern[ihist]->Draw();
        folder_bplast_hitpattern->Add(h1_bplast_tamex_card_hitpattern[ihist]);
    }
    
    c_bplast_tamex_card_hitpattern->cd(0);

    folder_bplast->Add(c_bplast_tamex_card_hitpattern);

    // Time spectra:
    c_bplast_time_spectra  = new TCanvas("h1_bplast_time_spectra","bPlast time spectra",1200,800);
    c_bplast_time_spectra->Divide(5,(nDetectors%5==0) ? (nDetectors/5) : (nDetectors/5 + 1));

    for (int ihist = 1; ihist <= nDetectors; ihist++){
        c_bplast_time_spectra->cd(ihist);
        h1_bplast_time_spectra[ihist] = new TH1F(Form("h1_bplast_time_spectra_%d",ihist),Form("bPlast Time spectrum detector %d",ihist),10000,0,6e10);
        h1_bplast_time_spectra[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_bplast_time_spectra[ihist]->Draw();
        folder_bplast_time_spectra->Add(h1_bplast_time_spectra[ihist]);
    }
    c_bplast_time_spectra->cd(0);

    folder_bplast->Add(c_bplast_time_spectra);

    c_bplast_fast_v_slow  = new TCanvas("c_bplast_fast_v_slow","fast vs slow ToT bplast spectra",1200,800);
    c_bplast_fast_v_slow->Divide(5,(nDetectors%5==0) ? (nDetectors/5) : (nDetectors/5 + 1));

    for (int ihist = 1; ihist <= nDetectors; ihist++){
        c_bplast_fast_v_slow->cd(ihist);
        h2_bplast_fastToT_vs_slowToT[ihist] = new TH2F(Form("h1_bplast_fast_v_slow_%d",ihist),Form("bplast fast vs. slow detector %d",ihist),1000,0,3.5e3,1000,0,3.5e3);
        h2_bplast_fastToT_vs_slowToT[ihist]->GetXaxis()->SetTitle("Slow ToT (ns)");
        h2_bplast_fastToT_vs_slowToT[ihist]->GetYaxis()->SetTitle("Fast ToT (ns)");
        h2_bplast_fastToT_vs_slowToT[ihist]->Draw("COLZ");
        folder_bplast_fast_v_slow->Add(h2_bplast_fastToT_vs_slowToT[ihist]);
    }
    c_bplast_fast_v_slow->cd(0);

    folder_bplast->Add(c_bplast_fast_v_slow);

    c_bplast_multiplicity  = new TCanvas("Multiplicity","bPlast multiplicity spectra",1200,800);
    
    h1_bplast_multiplicity = new TH1F("Multiplicity","bPlast multiplicity",128,1,129);
    h1_bplast_multiplicity->GetXaxis()->SetTitle("Event Multilplicity");
    h1_bplast_multiplicity->GetYaxis()->SetTitle("Counts");
    h1_bplast_multiplicity->Draw();
    c_bplast_multiplicity->SetLogy();
    folder_bplast_hitpattern->Add(h1_bplast_multiplicity);
    c_bplast_multiplicity->cd(0);

    run->GetHttpServer()->RegisterCommand("Reset_bPlast_Histo", Form("/Objects/%s/->Reset_Histo()", GetName()));

    run->GetHttpServer()->RegisterCommand("Snapshot_bPlast_Histo", Form("/Objects/%s/->Snapshot_Histo()", GetName()));

    return kSUCCESS;

}

void bPlastOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "Resetting bPlast histograms.");
    for (int ihist = 1; ihist<=nDetectors; ihist++) h1_bplast_slowToT[ihist]->Reset();
    for (int ihist = 1; ihist<=nDetectors; ihist++) h1_bplast_fastToT[ihist]->Reset();
    for (int ihist = 1; ihist<=nDetectors; ihist++) h2_bplast_fastToT_vs_slowToT[ihist]->Reset();
    h1_bplast_hitpatterns[0]->Reset();
    h1_bplast_hitpatterns[1]->Reset();
    h1_bplast_multiplicity->Reset();
    for (int ihist = 1; ihist<=nDetectors; ihist++) h1_bplast_time_spectra[ihist]->Reset();
    for (int ihist = 0; ihist < nTamexBoards; ihist++) h1_bplast_tamex_card_hitpattern[ihist]->Reset();
    
    c4LOG(info, "bPlast histograms reset.");
}

// make a date and time stamped folder with pngs of the histograms and .root file and save them
void bPlastOnlineSpectra::Snapshot_Histo()
{
    c4LOG(info, "Snapshotting bPlast histograms.");
    // date and time stamp

    time_t now = time(0);
    tm *ltm = localtime(&now);

    // make a folder with the date and time
    const char* snapshot_dir = Form("bPlast_Snapshots_%d_%d_%d_%d_%d_%d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    gSystem->cd(screenshot_path);
    gSystem->mkdir(snapshot_dir);
    gSystem->cd(snapshot_dir);

    // save histograms
    c_bplast_snapshot = new TCanvas("c","c",1200,800);
    for (int ihist = 1; ihist<=nDetectors; ihist++) {
        h1_bplast_slowToT[ihist]->Draw();
        c_bplast_snapshot->SaveAs(Form("Slow_ToT_%d.png", ihist));
        c_bplast_snapshot->Clear();
        h1_bplast_fastToT[ihist]->Draw();
        c_bplast_snapshot->SaveAs(Form("Fast_ToT_%d.png", ihist));
        c_bplast_snapshot->Clear();
        h2_bplast_fastToT_vs_slowToT[ihist]->Draw("COLZ");
        c_bplast_snapshot->SaveAs(Form("Fast_vs._Slow_ToT_%d.png", ihist));
        c_bplast_snapshot->Clear();
        h1_bplast_time_spectra[ihist]->Draw();
        c_bplast_snapshot->SaveAs(Form("Time_Spectrum_%d.png", ihist));
        c_bplast_snapshot->Clear();
    }
    
    // save hit patterns
    c_bplast_hitpatterns->SaveAs("bPlast_HitPatterns.png");
    c_bplast_multiplicity->SaveAs("bPlast_Multiplicity.png");

    for (int ihist = 0; ihist < nTamexBoards; ihist++){
        h1_bplast_tamex_card_hitpattern[ihist]->Draw();
        c_bplast_snapshot->SaveAs(Form("Tamex_Card_HitPattern_%d.png", ihist));
        c_bplast_snapshot->Clear();
    }
    // snapshot .root file with date and time
    file_bplast_snapshot = new TFile(Form("bPlast_snapshot_%d_%d_%d_%d_%d_%d.root", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec), "RECREATE");
    file_bplast_snapshot->cd();
    folder_bplast->Write();
    file_bplast_snapshot->Close();
    delete file_bplast_snapshot;

    gSystem->cd("..");
    c4LOG(info, "bPlast snapshot saved in:" << snapshot_dir);
}

void bPlastOnlineSpectra::Exec(Option_t* option)
{   
        
        bplast_map = bplast_conf->Mapping();

    if (fHitbPlastTwinpeaks && fHitbPlastTwinpeaks->GetEntriesFast() > 0)
    {
        event_multiplicity = 0;
        Int_t nHits = fHitbPlastTwinpeaks->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            bPlastTwinpeaksCalData* hit = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(ihit);
            if (!hit) continue;
            event_multiplicity ++;
            
            double slowToT = hit->Get_slow_ToT();
            double fastToT = hit->Get_fast_ToT();
            double fast_lead_time = hit->Get_fast_lead_time();
            
            int detector_id = hit->Get_detector_id();

            if (detector_id > nDetectors || detector_id < 0) continue;

            // Lead and Trail spectra -- empty for now
            h1_bplast_time_spectra[detector_id]->Fill(fast_lead_time);

            // Fast and Slow Tot spectra
            h1_bplast_slowToT[detector_id]->Fill(slowToT);
            h1_bplast_fastToT[detector_id]->Fill(fastToT);

            h2_bplast_fastToT_vs_slowToT[detector_id]->Fill(slowToT,fastToT);

            // Hit pattern spectra
            // the hit pattern spectrum is generated by filling the histogram with the detector ID of the hit
            for (const auto& entry : bplast_map)
            {
                if (entry.second.first == detector_id)
                {
                    if (entry.second.second.first == "U") h1_bplast_hitpatterns[0]->Fill(detector_id);
                    if (entry.second.second.first == "D") h1_bplast_hitpatterns[1]->Fill(detector_id);

                    for (int i = 0; i < nTamexBoards; i++)
                    {
                        if (entry.first.first == i)
                        {
                            h1_bplast_tamex_card_hitpattern[i]->Fill(entry.first.second);
                        }
                    }
                }

            }


        }
        h1_bplast_multiplicity->Fill(event_multiplicity);
    }
    fNEvents += 1;
}

    void bPlastOnlineSpectra::FinishEvent()
    {
    if (fHitbPlastTwinpeaks)
    {
        fHitbPlastTwinpeaks->Clear();
    }
    }

    void bPlastOnlineSpectra::FinishTask()
    {
    if(fNEvents == 0){ 
        c4LOG(warn, "No events found, not saving histograms!");
        return;
    }
    if (fHitbPlastTwinpeaks){
        folder_bplast->Write();
        c4LOG(info, "bPlast histograms written to file.");
    }
    }

    ClassImp(bPlastOnlineSpectra)
