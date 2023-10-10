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

GermaniumOnlineSpectra::GermaniumOnlineSpectra()
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
    TCanvas * energy_spectra_divided  = new TCanvas("energy_spectra_divided","Calibrated Germanium spectra",650,350);
    energy_spectra_divided->Divide(NCrystals,NDetectors);

    for (int ihist = 0; ihist < NCrystals*NDetectors; ihist++){
        energy_spectra_divided->cd(ihist+1);
        h1_energy[ihist] = new TH1F(Form("energy_spectrum_%d_%d",ihist/NCrystals,ihist%NCrystals),Form("energy_spectrum_%d_%d",ihist/NCrystals,ihist%NCrystals),10000,0,10e3);
        h1_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_energy[ihist]->Draw();
    }
    energy_spectra_divided->cd(0);

    ge_spectra_folder->Add(energy_spectra_divided);
    
    // energy spectra:
    TCanvas * energy_spectra_mult2  = new TCanvas("energy_spectra_mult2","Calibrated m = 2 Germanium spectra",650,350);
    energy_spectra_mult2->Divide(NCrystals,NDetectors);

    for (int ihist = 0; ihist < NCrystals*NDetectors; ihist++){
        energy_spectra_mult2->cd(ihist+1);
        h1_energy_mult2[ihist] = new TH1F(Form("energy_spectrum_%d_%d_mult2",ihist/NCrystals,ihist%NCrystals),Form("energy_spectrum_%d_%d_mult2",ihist/NCrystals,ihist%NCrystals),10000,0,10e3);
        h1_energy_mult2[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_energy_mult2[ihist]->Draw();
    }
    energy_spectra_mult2->cd(0);

    ge_spectra_folder->Add(energy_spectra_mult2);
    
    // Time spectra:
    TCanvas * time_spectra_divided  = new TCanvas("time_spectra_divided","Germanium time spectra",650,350);
    time_spectra_divided->Divide(NCrystals,NDetectors);

    for (int ihist = 0; ihist < NCrystals*NDetectors; ihist++){
        time_spectra_divided->cd(ihist+1);
        h1_time[ihist] = new TH1F(Form("Time_spectrum_%d_%d",ihist/NCrystals,ihist%NCrystals),Form("Time_spectrum_%d_%d",ihist/NCrystals,ihist%NCrystals),10000,1.5218e14,1.5225e14);
        h1_time[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_time[ihist]->Draw();
    }
    time_spectra_divided->cd(0);

    ge_spectra_folder->Add(time_spectra_divided);

    run->GetHttpServer()->RegisterCommand("Reset_Ge_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
    
}

void GermaniumOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_energy[ihist]->Reset();
    for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_energy_mult2[ihist]->Reset();
    for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_time[ihist]->Reset();

    
}

void GermaniumOnlineSpectra::Exec(Option_t* option)
{   
    if (fHitGe && fHitGe->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitGe->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            GermaniumCalData* hit = (GermaniumCalData*)fHitGe->At(ihit);
            if (!hit)
                continue;
            if ((hit->Get_detector_id() == 1) | (hit->Get_detector_id() == 0)) h1_energy[hit->Get_crystal_id()+hit->Get_detector_id()*NCrystals]->Fill(hit->Get_channel_energy());
            if ((hit->Get_detector_id() == 1) | (hit->Get_detector_id() == 0)) h1_time[hit->Get_crystal_id()+hit->Get_detector_id()*NCrystals]->Fill(hit->Get_channel_trigger_time());

            if (nHits>1){ // mult 2 gate:
                for (Int_t ihit2 = ihit+1; ihit2<nHits; ihit2++){
                    GermaniumCalData * hit2 = (GermaniumCalData*)fHitGe->At(ihit2);
                    if (!hit2) continue;
                    if (TMath::Abs(hit->Get_channel_trigger_time() - hit2->Get_channel_trigger_time()<10)) {
                        if ((hit->Get_detector_id() == 1) | (hit->Get_detector_id() == 0)) h1_energy_mult2[hit->Get_crystal_id()+hit->Get_detector_id()*NCrystals]->Fill(hit->Get_channel_energy());
                        if ((hit2->Get_detector_id() == 1) | (hit2->Get_detector_id() == 0)){
                            h1_energy_mult2[hit2->Get_crystal_id()+hit2->Get_detector_id()*NCrystals]->Fill(hit2->Get_channel_energy());
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
    if (fHitGe)
    {
        for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_energy[ihist]->Write();
        for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_energy_mult2[ihist]->Write();
        for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_time[ihist]->Write();
    }
}

ClassImp(GermaniumOnlineSpectra)