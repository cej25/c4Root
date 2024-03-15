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
#include "TGermaniumConfiguration.h"

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

GermaniumOnlineSpectra::GermaniumOnlineSpectra() : GermaniumOnlineSpectra("GermaniumOnlineSpectra")
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

GermaniumOnlineSpectra::GermaniumOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
    germanium_configuration = TGermaniumConfiguration::GetInstance();
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


    crystals_to_plot.clear();
    std::map<std::pair<int,int>,std::pair<int,int>> gmap = germanium_configuration->Mapping();

    for (auto it_mapping = gmap.begin(); it_mapping != gmap.end(); ++it_mapping){
        if (it_mapping->second.first >= 0) crystals_to_plot.emplace_back(std::pair<int,int>(it_mapping->second.first,it_mapping->second.second));
    }

    number_of_detectors_to_plot = crystals_to_plot.size();


    folder_germanium = new TFolder("DEGAS", "DEGAS");

    run->AddObject(folder_germanium);

    folder_germanium_energy = new TFolder("Calibrated Energy Spectra", "Calibrated Energy Spectra");
    folder_germanium_time = new TFolder("Time Spectra", "Time Spectra");
    folder_germanium_hitpattern = new TFolder("Hit pattern", "Hit pattern");
    folder_germanium->Add(folder_germanium_energy);
    folder_germanium->Add(folder_germanium_time);
    folder_germanium->Add(folder_germanium_hitpattern);


    // energy spectra:
    c_germanium_energy  = new TCanvas("c_germanium_energy","Calibrated Germanium spectra",650,350);
    c_germanium_energy->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_germanium_energy = new TH1F*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_germanium_energy->cd(ihist+1);
        h1_germanium_energy[ihist] = new TH1F(Form("h1_germanium_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,10e3);
        h1_germanium_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_energy[ihist]->Draw();
        folder_germanium_energy->Add(h1_germanium_energy[ihist]);
    }
    c_germanium_energy->cd(0);
    folder_germanium_energy->Add(c_germanium_energy);
    

    // time spectra:
    c_germanium_time  = new TCanvas("c_germanium_time","Calibrated Germanium spectra",650,350);
    c_germanium_time->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_germanium_time = new TH1F*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_germanium_time->cd(ihist+1);
        h1_germanium_time[ihist] = new TH1F(Form("h1_germanium_time_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS time spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,1e16);
        h1_germanium_time[ihist]->GetXaxis()->SetTitle("time (ns)");
        h1_germanium_time[ihist]->Draw();
        folder_germanium_time->Add(h1_germanium_time[ihist]);
    }
    c_germanium_time->cd(0);
    folder_germanium_time->Add(c_germanium_time);


    c_germanium_hitpattern = new TCanvas("c_germanium_hitpattern","Hit pattern DEGAS",650,350);
    detector_labels = new char*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        detector_labels[ihist] = Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65));
    }
    
    h1_germanium_hitpattern = new TH1F("h1_germanium_hitpattern","Hit pattern of DEGAS",number_of_detectors_to_plot,0,number_of_detectors_to_plot);
    h1_germanium_hitpattern->GetXaxis()->SetAlphanumeric();
    h1_germanium_hitpattern->GetXaxis()->LabelsOption("a");
    h1_germanium_hitpattern->GetXaxis()->SetTitle("crystal");
    h1_germanium_hitpattern->GetYaxis()->SetTitle("counts");
    //h1_germanium_hitpattern->SetCanExtend(TH1::kAllAxes);
    h1_germanium_hitpattern->SetStats(0);
    h1_germanium_hitpattern->Draw();
    //folder_germanium_hitpattern->Add(h1_germanium_hitpattern);
    folder_germanium_hitpattern->Add(c_germanium_hitpattern);
    c_germanium_hitpattern->cd(0);
    


    run->RegisterHttpCommand("Reset_Ge_Hist", "/GermaniumOnlineSpectra->Reset_Histo()");
    run->RegisterHttpCommand("Snapshot_Ge_Hist", "/GermaniumOnlineSpectra->Snapshot_Histo()");

    return kSUCCESS;
}

void GermaniumOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "Reset command received. Clearing histograms.");
    for (int ihist = 0; ihist<number_of_detectors_to_plot; ihist++) h1_germanium_energy[ihist]->Reset();
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

    for (int ihist = 0; ihist<number_of_detectors_to_plot; ihist++)
    {
        if(h1_germanium_energy[ihist]->GetEntries()!=0)
        {
            h1_germanium_energy[ihist]->Draw();
            c_germanium_snapshot->SaveAs(Form("h1_germanium_energy_%d_%d.png",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
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
            int detector_id = hit->Get_detector_id();
            int crystal_id = hit->Get_crystal_id();
            double energy = hit->Get_channel_energy();
            double time = hit->Get_channel_trigger_time();
            
            
            int crystal_index = std::distance(crystals_to_plot.begin(), std::find(crystals_to_plot.begin(),crystals_to_plot.end(),std::pair<int,int>(detector_id,crystal_id)));
            
            h1_germanium_energy[crystal_index]->Fill(energy);
            h1_germanium_time[crystal_index]->Fill(time);
            h1_germanium_hitpattern->Fill(detector_labels[crystal_index],1);


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
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }
    if (fHitGe)
    {
        folder_germanium->Write();
        c4LOG(info, "DEGAS histograms written to file.");
    }
}

ClassImp(GermaniumOnlineSpectra)