// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "AidaGermaniumCorrelations.h"
#include "EventHeader.h"
#include "GermaniumFebexData.h"
#include "GermaniumCalData.h"
#include "TGermaniumConfiguration.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include "TDirectory.h"

AidaGermaniumCorrelations::AidaGermaniumCorrelations() : AidaGermaniumCorrelations("AidaGermaniumCorrelations")
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

AidaGermaniumCorrelations::AidaGermaniumCorrelations(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

AidaGermaniumCorrelations::~AidaGermaniumCorrelations()
{
    c4LOG(info, "");
    if (fHitGe)
        delete fHitGe;
}

void AidaGermaniumCorrelations::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus AidaGermaniumCorrelations::Init()
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

    // Hit data
    implantHitArray = mgr->InitObjectAs<decltype(implantHitArray)>("AidaImplantHits");
    c4LOG_IF(fatal, !implantHitArray, "Branch AidaImplantHits not found!");
    
    folder_spectra = new TFolder("DEGAS-AIDA", "DEGAS-AIDA");
    run->AddObject(folder_spectra);

    c_germanium_energy_time = new TCanvas("c_germanium_energy_time","Calibrated Germanium spectra summed after last AIDA implant",650,350);
    h1_aida_germanium_energy_time = new TH2F("h1_aida_germanium_energy_time","Calibrated Germanium spectra time after last implant",1000,-100e3,100e3,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_aida_germanium_energy_time->GetXaxis()->SetTitle("time difference (ns)");
    h1_aida_germanium_energy_time->GetYaxis()->SetTitle("energy (keV)");
    h1_aida_germanium_energy_time->Draw("COLZ");
    c_germanium_energy_time->cd(0);
    folder_spectra->Add(c_germanium_energy_time);
    folder_spectra->Add(h1_aida_germanium_energy_time);
    
    
    c_germanium_energy = new TCanvas("c_germanium_energy","Calibrated Germanium spectra summed after last AIDA implant",650,350);
    h1_aida_germanium_energy = new TH1F("h1_aida_germanium_energy","Calibrated Germanium spectra time after last implant",fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_aida_germanium_energy->GetXaxis()->SetTitle("energy (keV)");
    h1_aida_germanium_energy->Draw();
    c_germanium_energy->cd(0);
    folder_spectra->Add(c_germanium_energy);
    folder_spectra->Add(h1_aida_germanium_energy);

    
    TDirectory::TContext ctx(nullptr);


    run->GetHttpServer()->RegisterCommand("Reset_Ge_Histo", Form("/Objects/%s/->Reset_Ge_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_Ge_Histo", Form("/Objects/%s/->Snapshot_Ge_Histo()", GetName()));
    aida_hit_time = 0;
    return kSUCCESS;
}


void AidaGermaniumCorrelations::Exec(Option_t* option)
{   
    for (auto const& hit : *implantHitArray)
    {
        aida_hit_energy = hit.Energy;
        if (aida_hit_time < hit.Time) aida_hit_time = hit.Time;
    }
    
    if (fHitGe && fHitGe->GetEntriesFast() > 0 && aida_hit_time != 0)
    {
        Int_t nHits = fHitGe->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            GermaniumCalData* hit = (GermaniumCalData*)fHitGe->At(ihit);
            if (!hit) continue;
            int detector_id1 = hit->Get_detector_id();
            int crystal_id1 = hit->Get_crystal_id();
            double energy1 = hit->Get_channel_energy();
            double time1 = hit->Get_channel_trigger_time();
            uint64_t ge_time = hit->Get_wr_t();

            // if (TMath::Abs((int64_t)ge_time - (int64_t)aida_hit_time) < 100e3 && detector_id1 <= 12){
            //     h1_aida_germanium_energy_time->Fill((int64_t)ge_time-(int64_t)aida_hit_time,energy1);
            //     if ((int64_t)ge_time - (int64_t)aida_hit_time > -8e3) h1_aida_germanium_energy->Fill(energy1);
            //     //c4LOG(info,Form("ge_time = %li, aida_time = %li, diff = %li, energy = %f",ge_time,aida_hit_time, (int64_t)ge_time-(int64_t)aida_hit_time,energy1));
            // }

            // 2025, testing
            if (!header->GetSpillFlag()) h1_aida_germanium_energy->Fill(energy1);
        }
    }

    fNEvents += 1;
}

void AidaGermaniumCorrelations::FinishEvent()
{
    if (fHitGe)
    {
        fHitGe->Clear();
    }
    if (implantHitArray){
        //implantHitArray->clear();
    }
}

void AidaGermaniumCorrelations::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }
    if (fHitGe && implantHitArray)
    {
        folder_spectra->Write();
        c4LOG(info, "DEGAS-AIDA histograms written to file.");
    }
}

ClassImp(AidaGermaniumCorrelations)
