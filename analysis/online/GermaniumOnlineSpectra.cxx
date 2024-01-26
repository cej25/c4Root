// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "GermaniumOnlineSpectra.h"
#include "EventHeader.h"
#include "GermaniumFebexData.h"
#include "GermaniumCalData.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

GermaniumOnlineSpectra::GermaniumOnlineSpectra() : GermaniumOnlineSpectra("GermaniumOnlineSpectra")
{
}

GermaniumOnlineSpectra::GermaniumOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , fNEvents(0)
    , header(nullptr)
{
}

GermaniumOnlineSpectra::~GermaniumOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitGe)
        delete fHitGe;
}

void GermaniumOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus GermaniumOnlineSpectra::Init()
{

    // number of crystals, number of dets 

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitGe = (TClonesArray*)mgr->GetObject("GermaniumCalData");
    c4LOG_IF(fatal, !fHitGe, "Branch GermaniumCalData not found!");

    TFolder * ge_spectra_folder = new TFolder("Germanium", "Germanium");

    run->AddObject(ge_spectra_folder);

    // energy spectra:
    c_germanium_cal_energy_spectra  = new TCanvas("c_germanium_cal_energy_spectra","Calibrated Germanium spectra",650,350);
    c_germanium_cal_energy_spectra->Divide(NCrystals,NDetectors);

    for (int ihist = 0; ihist < NCrystals*NDetectors; ihist++){
        c_germanium_cal_energy_spectra->cd(ihist+1);
        h1_germanium_energy[ihist] = new TH1F(Form("h1_germanium_energy_%d_%d",ihist/NCrystals,ihist%NCrystals),Form("Germanium Energy spectrum det %d crystal %d",ihist/NCrystals,ihist%NCrystals),1000,0,10e3);
        h1_germanium_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_energy[ihist]->Draw();
        ge_spectra_folder->Add(h1_germanium_energy[ihist]);

    }
    c_germanium_cal_energy_spectra->cd(0);

    ge_spectra_folder->Add(c_germanium_cal_energy_spectra);
    
    // energy spectra:
    c_germanium_energy_mult2  = new TCanvas("c_germanium_energy_mult2","Calibrated m = 2 Germanium spectra",650,350);
    c_germanium_energy_mult2->Divide(NCrystals,NDetectors);

    for (int ihist = 0; ihist < NCrystals*NDetectors; ihist++){
        c_germanium_energy_mult2->cd(ihist+1);
        h1_germanium_energy_mult2[ihist] = new TH1F(Form("h1_germanium_energy_mult2_%d_%d",ihist/NCrystals,ihist%NCrystals),Form("Germanium Energy spectrum m=2 det %d crystal %d",ihist/NCrystals,ihist%NCrystals),1000,0,10e3);
        h1_germanium_energy_mult2[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_energy_mult2[ihist]->Draw();
        ge_spectra_folder->Add(h1_germanium_energy_mult2[ihist]);
    }
    c_germanium_energy_mult2->cd(0);

    ge_spectra_folder->Add(c_germanium_energy_mult2);
    
    // Time spectra:
    TCanvas * c_germanium_time  = new TCanvas("c_germanium_time","Germanium time spectra",650,350);
    c_germanium_time->Divide(NCrystals,NDetectors);

    for (int ihist = 0; ihist < NCrystals*NDetectors; ihist++){
        c_germanium_time->cd(ihist+1);
        h1_germanium_time[ihist] = new TH1F(Form("h1_germanium_time_%d_%d",ihist/NCrystals,ihist%NCrystals),Form("Absolute Time %d %d",ihist/NCrystals,ihist%NCrystals),100,1.5218e14,1.5225e14);
        h1_germanium_time[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_germanium_time[ihist]->Draw();
        ge_spectra_folder->Add(h1_germanium_time[ihist]);

    }
    c_germanium_time->cd(0);

    ge_spectra_folder->Add(c_germanium_time);

    run->RegisterHttpCommand("Reset_Ge_Hist", "/GermaniumOnlineSpectra->Reset_Histo()");

    return kSUCCESS;
}

void GermaniumOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "Reset command received. Clearing histograms.");
    for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_germanium_energy[ihist]->Reset();
    for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_germanium_energy_mult2[ihist]->Reset();
    for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_germanium_time[ihist]->Reset();
}

void GermaniumOnlineSpectra::Exec(Option_t* option)
{   
    if (fHitGe && fHitGe->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitGe->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            GermaniumCalData* hit = (GermaniumCalData*)fHitGe->At(ihit);
            if (!hit) continue;

            h1_germanium_energy[hit->Get_crystal_id()+hit->Get_detector_id()*NCrystals]->Fill(hit->Get_channel_energy());
            h1_germanium_time[hit->Get_crystal_id()+hit->Get_detector_id()*NCrystals]->Fill(hit->Get_channel_trigger_time());

            if (nHits>1){ // mult 2 gate:
                for (Int_t ihit2 = ihit+1; ihit2<nHits; ihit2++){
                    GermaniumCalData * hit2 = (GermaniumCalData*)fHitGe->At(ihit2);

                    if (!hit2) continue;
                    if (hit2->Get_detector_id() > 1) continue;
            
                    if (TMath::Abs(hit->Get_channel_trigger_time() - hit2->Get_channel_trigger_time()<20)) {
                        if ((hit->Get_detector_id() == 1) || (hit->Get_detector_id() == 0)) h1_germanium_energy_mult2[hit->Get_crystal_id()+hit->Get_detector_id()*NCrystals]->Fill(hit->Get_channel_energy());
                        if ((hit2->Get_detector_id() == 1) || (hit2->Get_detector_id() == 0)){
                            h1_germanium_energy_mult2[hit2->Get_crystal_id()+hit2->Get_detector_id()*NCrystals]->Fill(hit2->Get_channel_energy());
                            break; // some simpifications.
                        }
                    }
                }
            }
        }
    }

    fNEvents += 1;
}

void GermaniumOnlineSpectra::FinishEvent()
{
    if (fHitGe)
    {
        fHitGe->Clear();
    }
}

void GermaniumOnlineSpectra::FinishTask()
{
    if (fHitGe)//writes to file, test?
    {
        for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_germanium_energy[ihist]->Write();
        for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_germanium_energy_mult2[ihist]->Write();
        for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_germanium_time[ihist]->Write();
    }
}

ClassImp(GermaniumOnlineSpectra)