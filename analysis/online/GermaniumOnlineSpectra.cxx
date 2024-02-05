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

    folder_germanium = new TFolder("DEGAS", "DEGAS");

    run->AddObject(folder_germanium);

    folder_germanium_cal_energy_spectra = new TFolder("Calibrated Energy Spectra", "Calibrated Energy Spectra");
    folder_germanium_energy_mult2 = new TFolder("m=2 Energy Spectra", "m=2 Energy Spectra");
    folder_germanium_time = new TFolder("Time Spectra", "Time Spectra");
    folder_germanium->Add(folder_germanium_cal_energy_spectra);
    folder_germanium->Add(folder_germanium_energy_mult2);
    folder_germanium->Add(folder_germanium_time);


    // energy spectra:
    c_germanium_cal_energy_spectra  = new TCanvas("c_germanium_cal_energy_spectra","Calibrated Germanium spectra",650,350);
    c_germanium_cal_energy_spectra->Divide(NCrystals,NDetectors);

    for (int ihist = 0; ihist < NCrystals*NDetectors; ihist++){
        c_germanium_cal_energy_spectra->cd(ihist+1);
        h1_germanium_energy[ihist] = new TH1F(Form("h1_germanium_energy_%d_%d",ihist/NCrystals,ihist%NCrystals),Form("Germanium Energy spectrum det %d crystal %d",ihist/NCrystals,ihist%NCrystals),10e3,0,10e3);
        h1_germanium_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_energy[ihist]->Draw();
        folder_germanium_cal_energy_spectra->Add(h1_germanium_energy[ihist]);

    }
    c_germanium_cal_energy_spectra->cd(0);

    folder_germanium->Add(c_germanium_cal_energy_spectra);
    
    // energy spectra:
    c_germanium_energy_mult2  = new TCanvas("c_germanium_energy_mult2","Calibrated m = 2 Germanium spectra",650,350);
    c_germanium_energy_mult2->Divide(NCrystals,NDetectors);

    for (int ihist = 0; ihist < NCrystals*NDetectors; ihist++){
        c_germanium_energy_mult2->cd(ihist+1);
        h1_germanium_energy_mult2[ihist] = new TH1F(Form("h1_germanium_energy_mult2_%d_%d",ihist/NCrystals,ihist%NCrystals),Form("Germanium Energy spectrum m=2 det %d crystal %d",ihist/NCrystals,ihist%NCrystals),1000,0,10e3);
        h1_germanium_energy_mult2[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_energy_mult2[ihist]->Draw();
        folder_germanium_energy_mult2->Add(h1_germanium_energy_mult2[ihist]);
    }
    c_germanium_energy_mult2->cd(0);

    folder_germanium->Add(c_germanium_energy_mult2);
    
    // Time spectra:
    c_germanium_time  = new TCanvas("c_germanium_time","Germanium time spectra",650,350);
    c_germanium_time->Divide(NCrystals,NDetectors);

    for (int ihist = 0; ihist < NCrystals*NDetectors; ihist++){
        c_germanium_time->cd(ihist+1);
        h1_germanium_time[ihist] = new TH1F(Form("h1_germanium_time_%d_%d",ihist/NCrystals,ihist%NCrystals),Form("Absolute Time %d %d",ihist/NCrystals,ihist%NCrystals),100,1.5218e14,1.5225e14);
        h1_germanium_time[ihist]->GetXaxis()->SetTitle("Time (ns)");
        h1_germanium_time[ihist]->Draw();
        folder_germanium_time->Add(h1_germanium_time[ihist]);

    }
    c_germanium_time->cd(0);

    folder_germanium->Add(c_germanium_time);

    run->RegisterHttpCommand("Reset_Ge_Hist", "/GermaniumOnlineSpectra->Reset_Histo()");
    run->RegisterHttpCommand("Snapshot_Ge_Hist", "/GermaniumOnlineSpectra->Snapshot_Histo()");

    return kSUCCESS;
}

void GermaniumOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "Reset command received. Clearing histograms.");
    for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_germanium_energy[ihist]->Reset();
    for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_germanium_energy_mult2[ihist]->Reset();
    for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++) h1_germanium_time[ihist]->Reset();
}

void GermaniumOnlineSpectra::Snapshot_Histo()
{
    //date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    //make folder with date and time
    const char* snapshot_dir = Form("Germanium_snapshot_%d_%d_%d_%d_%d_%d",ltm->tm_year+1900,ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec);
    gSystem->mkdir(snapshot_dir);
    gSystem->cd(snapshot_dir);

    // save histograms to canvases
    c_germanium_snapshot = new TCanvas("c","c",650,350);

    for (int ihist = 0; ihist<NCrystals*NDetectors; ihist++)
    {
        if(h1_germanium_energy[ihist]->GetEntries()>0)
        {
            h1_germanium_energy[ihist]->Draw();
            c_germanium_snapshot->SaveAs(Form("h1_germanium_energy_%d_%d.png",ihist/NCrystals,ihist%NCrystals));
            c_germanium_snapshot->Clear();
        }
        if(h1_germanium_energy_mult2[ihist]->GetEntries()>0)
        {
            h1_germanium_energy_mult2[ihist]->Draw();
            c_germanium_snapshot->SaveAs(Form("h1_germanium_energy_mult2_%d_%d.png",ihist/NCrystals,ihist%NCrystals));
            c_germanium_snapshot->Clear();
        }
        if(h1_germanium_time[ihist]->GetEntries()>0)
        {
            h1_germanium_time[ihist]->Draw();
            c_germanium_snapshot->SaveAs(Form("h1_germanium_time_%d_%d.png",ihist/NCrystals,ihist%NCrystals));
            c_germanium_snapshot->Clear();
        }
    }
    delete c_germanium_snapshot;

    // snapshot .root file with data and time
    file_germanium_snapshot = new TFile(Form("Germanium_snapshot_%d_%d_%d_%d_%d_%d.root",ltm->tm_year+1900,ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec),"RECREATE");
    file_germanium_snapshot->cd();
    folder_germanium->Write();
    file_germanium_snapshot->Close();
    delete file_germanium_snapshot;

    gSystem->cd("..");
    c4LOG(info, "Snapshot saved to:" << snapshot_dir);
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
    if (fHitGe)
    {
        folder_germanium->Write();
    }
}

ClassImp(GermaniumOnlineSpectra)