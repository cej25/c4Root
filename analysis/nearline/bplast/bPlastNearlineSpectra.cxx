// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "bPlastNearlineSpectra.h"
#include "EventHeader.h"
#include "bPlastTwinpeaksCalData.h"

// other modules
#include "AidaNearlineSpectra.h"
#include "AidaData.h"
#include "AidaHitData.h"
#include "TAidaConfiguration.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

bPlastNearlineSpectra::bPlastNearlineSpectra() : bPlastNearlineSpectra("bPlastNearlineSpectra")
{
}

bPlastNearlineSpectra::bPlastNearlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitbPlastTwinpeaks(NULL)
    , implantHitArray(nullptr)
    , decayHitArray(nullptr)
    , fNEvents(0)
    , header(nullptr)
{
}

bPlastNearlineSpectra::~bPlastNearlineSpectra()
{
    c4LOG(info, "");
    if (fHitbPlastTwinpeaks)
        delete fHitbPlastTwinpeaks;
}

void bPlastNearlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus bPlastNearlineSpectra::Init()
{

    // number of dets 

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    // AIDA

    // Hit data
    implantHitArray = mgr->InitObjectAs<decltype(implantHitArray)>("AidaImplantHits");
    c4LOG_IF(fatal, !implantHitArray, "Branch AidaImplantHits not found!");
    decayHitArray = mgr->InitObjectAs<decltype(decayHitArray)>("AidaDecayHits");
    c4LOG_IF(fatal, !decayHitArray, "Branch AidaDecayHits not found!");

    // Aida configuration
    TAidaConfiguration const* conf = TAidaConfiguration::GetInstance();

    // bPlast

    fHitbPlastTwinpeaks = (TClonesArray*)mgr->GetObject("bPlastTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitbPlastTwinpeaks, "Branch bPlastTwinpeaksCalData not found!");

    TFolder * bPlast_spectra_folder = new TFolder("bPlast", "bPlast");

    run->AddObject(bPlast_spectra_folder);

    // energy/tot spectra:
    // slow tot:
    c_bplast_slowToT  = new TCanvas("c_bplast_slowToT","slow ToT bPlast spectra",650,350);
    c_bplast_slowToT->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_bplast_slowToT->cd(ihist+1);
        h1_bplast_slowToT[ihist] = new TH1F(Form("c_bplast_slowToT_%d",ihist),Form("bPlastic slow ToT %d",ihist),10000,0,5e3);
        h1_bplast_slowToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_bplast_slowToT[ihist]->Draw();
    }
    c_bplast_slowToT->cd(0);

    bPlast_spectra_folder->Add(c_bplast_slowToT);
    
    // fast tot:

    c_bplast_fastToT  = new TCanvas("c_bplast_fastToT","fast ToT bPlast spectra",650,350);
    c_bplast_fastToT->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_bplast_fastToT->cd(ihist+1);
        h1_bplast_fastToT[ihist] = new TH1F(Form("c_bplast_fastToT_%d",ihist),Form("bPlastic fast ToT %d",ihist),10000,0,5e3);
        h1_bplast_fastToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
        h1_bplast_fastToT[ihist]->Draw();
    }
    c_bplast_fastToT->cd(0);

    bPlast_spectra_folder->Add(c_bplast_fastToT);

    // fast vs slow tot:

    c_bplast_fast_v_slow  = new TCanvas("c_bplast_fast_v_slow","fast vs slow ToT bplast spectra",650,350);
    c_bplast_fast_v_slow->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_bplast_fast_v_slow->cd(ihist+1);
        h2_bplast_slowToT_vs_fastToT[ihist] = new TH2F(Form("h2_bplast_slowToT_vs_fastToT_ToT_%d",ihist),Form("bplast fast vs. slow detector %d",ihist),1000,0,2.5e3,1000,0,2.5e3);
        h2_bplast_slowToT_vs_fastToT[ihist]->GetXaxis()->SetTitle("fast ToT (ns)");
        h2_bplast_slowToT_vs_fastToT[ihist]->GetYaxis()->SetTitle("slow ToT (ns)");
        h2_bplast_slowToT_vs_fastToT[ihist]->Draw("COLZ");
    }
    c_bplast_fast_v_slow->cd(0);

    bPlast_spectra_folder->Add(c_bplast_fast_v_slow);

    // hit pattern:

    c_bplast_hitpatterns  = new TCanvas("c_bplast_hitpatterns","fast HitPatt bPlast spectra",650,350);
    c_bplast_hitpatterns->Divide(2,1);

    c_bplast_hitpatterns->cd(1);
    h1_bplast_fast_hitpatterns = new TH1F("h1_bplast_fast_hitpatterns","Fast ToT detector hit patterns",NDetectors,0,NDetectors);
    h1_bplast_fast_hitpatterns->GetXaxis()->SetTitle("Detector ID");
    h1_bplast_fast_hitpatterns->GetYaxis()->SetTitle("Counts");
    h1_bplast_fast_hitpatterns->Draw();
    c_bplast_hitpatterns->cd(2);
    h1_bplast_slow_hitpatterns = new TH1F("h1_bplast_slow_hitpatterns","Slow ToT detector hit patterns",NDetectors,0,NDetectors);
    h1_bplast_slow_hitpatterns->GetXaxis()->SetTitle("Detector ID");
    h1_bplast_slow_hitpatterns->GetYaxis()->SetTitle("Counts");
    h1_bplast_slow_hitpatterns->Draw();
    c_bplast_hitpatterns->cd(0);

    bPlast_spectra_folder->Add(c_bplast_hitpatterns);
    
    // Time spectra:
    c_bplast_time_spectra  = new TCanvas("c_bplast_time_spectra","bPlast time spectra",650,350);
    c_bplast_time_spectra->Divide(5,(NDetectors%5==0) ? (NDetectors/5) : (NDetectors/5 + 1));

    for (int ihist = 0; ihist < NDetectors; ihist++){
        c_bplast_time_spectra->cd(ihist+1);
        h1_bplast_abs_time[ihist] = new TH1F(Form("bPlast_Time_spectrum_%d",ihist),Form("bPlast Time spectrum detector %d",ihist),10000,0,2.7e12);
        h1_bplast_abs_time[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_bplast_abs_time[ihist]->Draw();
    }
    c_bplast_time_spectra->cd(0);

    bPlast_spectra_folder->Add(c_bplast_time_spectra);

    // Relative time spectra:

    c_bplast_rel_time_spectra  = new TCanvas("c_bplast_rel_time_spectra","bPlast relative time spectra",650,350);

    for (int ihist = 0; ihist < NDetectors; ihist++){
        h1_bplast_rel_time[ihist] = new TH1F(Form("bPlast_Rel_Time_spectrum_%d",ihist),Form("bPlast Relative Time spectrum detector %d",ihist),1250,-10,10);
        h1_bplast_rel_time[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_bplast_rel_time[ihist]->Draw();
    }

    bPlast_spectra_folder->Add(c_bplast_rel_time_spectra);

    run->GetHttpServer()->RegisterCommand("Reset_bPlast_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
    
}

void bPlastNearlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_slowToT[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_fastToT[ihist]->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h2_bplast_slowToT_vs_fastToT[ihist]->Reset();
    h1_bplast_fast_hitpatterns->Reset();
    h1_bplast_slow_hitpatterns->Reset();
    for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_abs_time[ihist]->Reset();

    c4LOG(info, "Histograms reset.");
   
}

void bPlastNearlineSpectra::Exec(Option_t* option)
{   
    if (fHitbPlastTwinpeaks && fHitbPlastTwinpeaks->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitbPlastTwinpeaks->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++) // bplast hits
        {   
            bPlastTwinpeaksCalData* bplasthit = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(ihit);
            if (!bplasthit) continue;
            
            if (bplasthit->Get_detector_id() > NDetectors || bplasthit->Get_detector_id() < 0) continue;

            // Lead and Trail spectra -- empty for now

            // Fast and Slow Tot spectra
            // if (bplasthit->Get_slow_ToT() != 0) h1_bplast_slowToT[bplasthit->Get_detector_id()]->Fill(bplasthit->Get_slow_ToT());
            // if (bplasthit->Get_fast_ToT() != 0) h1_bplast_fastToT[bplasthit->Get_detector_id()]->Fill(bplasthit->Get_fast_ToT());

            // // fast vs slow:
            // if ( (bplasthit->Get_fast_ToT() != 0) && (bplasthit->Get_slow_ToT() != 0) ) h2_bplast_slowToT_vs_fastToT[bplasthit->Get_detector_id()]->Fill(bplasthit->Get_fast_ToT(),bplasthit->Get_slow_ToT());

            // // Hit pattern spectra
            // // the hit pattern spectrum is generated by filling the histogram with the detector ID of the hit

            // if (bplasthit->Get_fast_ToT() != 0) h1_bplast_fast_hitpatterns->Fill(bplasthit->Get_detector_id());
            // if (bplasthit->Get_slow_ToT() != 0) h1_bplast_slow_hitpatterns->Fill(bplasthit->Get_detector_id());

            // // Absolute time spectra
            // if (bplasthit->Get_fast_ToT() !=0 ) h1_bplast_abs_time[bplasthit->Get_detector_id()]->Fill(bplasthit->Get_fast_lead_time());
            // Relative time spectra

            for (auto const& hit : *decayHitArray)
            {
                if (bplasthit->Get_detector_id() == 1){
                    Int_t nnHits = fHitbPlastTwinpeaks->GetEntriesFast();
                    for (Int_t i = 0; i < nnHits; i++) // bplast hits
                    {   
                        bPlastTwinpeaksCalData* bplasthitsecond = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(i);

                        if (!bplasthitsecond) continue;
                        if (bplasthitsecond->Get_fast_lead_time() == 0 || bplasthit->Get_fast_lead_time() == 0) continue;
                        if (hit.DSSD == 1 && hit.StripX > 178 && hit.StripX < 206 && hit.StripY > 55 && hit.StripY < 73 ){
                            h1_bplast_rel_time[bplasthitsecond->Get_detector_id()]->Fill(bplasthitsecond->Get_fast_lead_time()-bplasthit->Get_fast_lead_time());
                        } // filling histograms gated on aida
                    } // second loop hits
                } // SiPM detector 1 condition
            } // aida loop
        } // bplast loop
    } // if bplast hits
    fNEvents += 1;
} // exec

void bPlastNearlineSpectra::FinishEvent()
{
    if (fHitbPlastTwinpeaks)
    {
        fHitbPlastTwinpeaks->Clear();
    }
}

void bPlastNearlineSpectra::FinishTask()
{
    if (fHitbPlastTwinpeaks)
    {
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_slowToT[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_fastToT[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h2_bplast_slowToT_vs_fastToT[ihist]->Write();
        h1_bplast_fast_hitpatterns->Write();
        h1_bplast_slow_hitpatterns->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_abs_time[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_rel_time[ihist]->Write();
    }
}

ClassImp(bPlastNearlineSpectra)
