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
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include "TDirectory.h"

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
    
    TDirectory::TContext ctx(nullptr);

    folder_germanium = new TFolder("DEGAS", "DEGAS");

    run->AddObject(folder_germanium);

    folder_germanium_energy = new TFolder("Calibrated Energy Spectra", "Calibrated Energy Spectra");
    folder_germanium_time = new TFolder("Time Spectra", "Time Spectra");
    folder_germanium_hitpattern = new TFolder("Hit pattern", "Hit pattern");
    folder_germanium_multiplicity = new TFolder("Multiplicity", "Multiplicity");
    folder_germanium_sci41 = new TFolder("SCI41","SCI41");

    folder_germanium->Add(folder_germanium_energy);
    folder_germanium->Add(folder_germanium_time);
    folder_germanium->Add(folder_germanium_hitpattern);
    folder_germanium->Add(folder_germanium_multiplicity);
    folder_germanium->Add(folder_germanium_sci41);


    // energy spectra:
    c_germanium_energy  = new TCanvas("c_germanium_energy","Calibrated Germanium spectra",650,350);
    c_germanium_energy->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_germanium_energy = new TH1F*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_germanium_energy->cd(ihist+1);
        h1_germanium_energy[ihist] = new TH1F(Form("h1_germanium_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_germanium_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_energy[ihist]->Draw();
        folder_germanium_energy->Add(h1_germanium_energy[ihist]);
    }
    c_germanium_energy->cd(0);
    folder_germanium_energy->Add(c_germanium_energy);


    c_germanium_energy_vs_detidx = new TCanvas("c_germanium_energy_vs_detidx","Calibrated Germanium spectra vs. detector index",650,350);
    h2_germanium_energy_vs_detidx = new TH2F("h2_germanium_energy_vs_detidx","Calibrated Germanium spectra vs. detector index",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,number_of_detectors_to_plot,0,number_of_detectors_to_plot);
    h2_germanium_energy_vs_detidx->GetXaxis()->SetTitle("energy (keV)");
    h2_germanium_energy_vs_detidx->GetYaxis()->SetTitle("detector index");
    h2_germanium_energy_vs_detidx->Draw("COLZ");
    c_germanium_energy_vs_detidx->cd(0);
    folder_germanium_energy->Add(c_germanium_energy_vs_detidx);
    folder_germanium_energy->Add(h2_germanium_energy_vs_detidx);


    c_germanium_energy_summed = new TCanvas("c_germanium_energy_summed","Calibrated Germanium spectra summed all dets",650,350);
    h1_germanium_energy_summed = new TH1F("h1_germanium_energy_summed","Calibrated Germanium spectra summed all dets",fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_germanium_energy_summed->GetXaxis()->SetTitle("energy (keV)");
    h1_germanium_energy_summed->GetYaxis()->SetTitle("counts");
    h1_germanium_energy_summed->Draw();
    c_germanium_energy_summed->cd(0);
    folder_germanium_energy->Add(c_germanium_energy_summed);
    folder_germanium_energy->Add(h1_germanium_energy_summed);



    // Spectra relating to SCI41:
    c_germanium_energy_summed_vetosci41 = new TCanvas("c_germanium_energy_summed_vetosci41","Calibrated Germanium spectra summed all dets veto sci41",650,350);
    h1_germanium_energy_summed_vetosci41 = new TH1F("h1_germanium_energy_summed_vetosci41","Calibrated Germanium spectra summed all dets veto sci 41",fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_germanium_energy_summed_vetosci41->GetXaxis()->SetTitle("energy (keV)");
    h1_germanium_energy_summed_vetosci41->GetYaxis()->SetTitle("counts");
    h1_germanium_energy_summed_vetosci41->Draw();
    c_germanium_energy_summed_vetosci41->cd(0);
    folder_germanium_sci41->Add(c_germanium_energy_summed_vetosci41);
    folder_germanium_sci41->Add(h1_germanium_energy_summed_vetosci41);
    
    
    
    c_germanium_energy_summed_vs_tsci41 = new TCanvas("c_germanium_energy_summed_vs_tsci41","Calibrated Germanium spectra summed all energyies vs t(det) - t(sci41)",650,350);
    h2_germanium_energy_summed_vs_tsci41 = new TH2F("h2_germanium_energy_summed_vs_tsci41","Calibrated Germanium spectra summed all energyies vs t(det) - t(sci41)",1000,-500,5000,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_germanium_energy_summed_vs_tsci41->GetXaxis()->SetTitle("time difference (ns)");
    h2_germanium_energy_summed_vs_tsci41->GetYaxis()->SetTitle("energy (keV)");
    h2_germanium_energy_summed_vs_tsci41->Draw("COLZ");
    c_germanium_energy_summed_vs_tsci41->cd(0);
    folder_germanium_sci41->Add(c_germanium_energy_summed_vs_tsci41);
    folder_germanium_sci41->Add(h2_germanium_energy_summed_vs_tsci41);

    
    c_germanium_energy_summed_vs_tsci41_cut = new TCanvas("c_germanium_energy_summed_vs_tsci41_cut","Calibrated Germanium spectra summed all energyies, t(det) - t(sci41) > 200 ns",650,350);
    h1_germanium_energy_summed_vs_tsci41_cut = new TH1F("h1_germanium_energy_summed_vs_tsci41_cut","Calibrated Germanium spectra summed all energyies, t(det) - t(sci41) > 200 ns",fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_germanium_energy_summed_vs_tsci41_cut->GetXaxis()->SetTitle("energy (keV)");
    h1_germanium_energy_summed_vs_tsci41_cut->Draw("COLZ");
    c_germanium_energy_summed_vs_tsci41_cut->cd(0);
    folder_germanium_sci41->Add(c_germanium_energy_summed_vs_tsci41_cut);
    folder_germanium_sci41->Add(h1_germanium_energy_summed_vs_tsci41_cut);

    
    c_germanium_energy_energy_vetosci41 = new TCanvas("c_germanium_energy_energy_vetosci41","Calibrated Germanium spectra summed all energyies, t(det) - t(sci41) > 200 ns",650,350);
    h2_germanium_energy_energy_vetosci41 = new TH2F("h2_germanium_energy_energy_vetosci41","Calibrated Germanium spectra summed all energyies, t(det) - t(sci41) > 200 ns",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_germanium_energy_energy_vetosci41->GetXaxis()->SetTitle("energy (keV)");
    h2_germanium_energy_energy_vetosci41->Draw("COLZ");
    c_germanium_energy_energy_vetosci41->cd(0);
    folder_germanium_sci41->Add(c_germanium_energy_energy_vetosci41);
    folder_germanium_sci41->Add(h2_germanium_energy_energy_vetosci41);

    
    c_germanium_energy_energy_sci41_cut = new TCanvas("c_germanium_energy_energy_sci41_cut","Calibrated Germanium spectra summed all energyies, t(det) - t(sci41) > 200 ns",650,350);
    h2_germanium_energy_energy_sci41_cut = new TH2F("h2_germanium_energy_energy_sci41_cut","Calibrated Germanium spectra summed all energyies, t(det) - t(sci41) > 200 ns",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_germanium_energy_energy_sci41_cut->GetXaxis()->SetTitle("energy (keV)");
    h2_germanium_energy_energy_sci41_cut->Draw("COLZ");
    c_germanium_energy_energy_sci41_cut->cd(0);
    folder_germanium_sci41->Add(c_germanium_energy_summed_vs_tsci41_cut);
    folder_germanium_sci41->Add(h2_germanium_energy_energy_sci41_cut);

    


    

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


    c_germanium_multiplicity = new TCanvas("c_germanium_multiplicity","Multiplicity of Germanium events",650,350);
    h1_germanium_multiplicity = new TH1F("h1_germanium_multiplicity","Multiplicity of Germanium events",number_of_detectors_to_plot,0,number_of_detectors_to_plot);
    h1_germanium_multiplicity->GetXaxis()->SetTitle("event multiplicity");
    h1_germanium_multiplicity->GetYaxis()->SetTitle("counts");
    h1_germanium_multiplicity->Draw();
    folder_germanium_multiplicity->Add(c_germanium_multiplicity);
    folder_germanium_multiplicity->Add(h1_germanium_multiplicity);


    //time differences!
    number_reference_detectors = dt_reference_detectors.size();
    h1_germanium_time_differences = new TH1F ** [number_reference_detectors];
    h2_germanium_time_differences_vs_energy = new TH2F ** [number_reference_detectors];
    for (int ihist = 0; ihist < number_reference_detectors; ihist++){
        folder_germanium_time_differences = new TFolder(Form("time_differences_rel_%d_%d_energy_gate_%d_%d",dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second), Form("time_differences_rel_%d_%d_energy_gate_%d_%d",dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second));
        folder_germanium->Add(folder_germanium_time_differences);

        c_germanium_time_differences  = new TCanvas(Form("c_germanium_time_differences_rel_det_%d_%d_energy_gate_%d_%d",dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),"germanium relative time differences",650,350);
        c_germanium_time_differences->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
        h1_germanium_time_differences[ihist] = new TH1F*[number_of_detectors_to_plot];

        for (int detid_idx = 0; detid_idx < number_of_detectors_to_plot; detid_idx++){
            c_germanium_time_differences->cd(detid_idx+1);
            h1_germanium_time_differences[ihist][detid_idx] = new TH1F(Form("h1_germanium_rel_time_det_%d_%d_to_det_%d_%d_energy_gate_%d_%d",crystals_to_plot.at(detid_idx).first,crystals_to_plot.at(detid_idx).second,dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("Germanium delta time t(%d%c) - t(%d%c) gated %d and %d",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),1000,-1000,1000); 
            h1_germanium_time_differences[ihist][detid_idx]->GetXaxis()->SetTitle(Form("dt t(%d%c) - t(%d%c) (ns)",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65)));
            h1_germanium_time_differences[ihist][detid_idx]->Draw();
            folder_germanium_time_differences->Add(h1_germanium_time_differences[ihist][detid_idx]);
            
        }
        c_germanium_time_differences->cd(0);
        folder_germanium_time_differences->Add(c_germanium_time_differences);



        c_germanium_time_differences_vs_energy  = new TCanvas(Form("c_germanium_time_differences_rel_det_%d_%d_vs_energy_energy_gate_%d_%d",dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),"germanium relative time differences vs energy",650,350);
        c_germanium_time_differences_vs_energy->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
        h2_germanium_time_differences_vs_energy[ihist] = new TH2F*[number_of_detectors_to_plot];

        for (int detid_idx = 0; detid_idx < number_of_detectors_to_plot; detid_idx++){
            c_germanium_time_differences_vs_energy->cd(detid_idx+1);
            h2_germanium_time_differences_vs_energy[ihist][detid_idx] = new TH2F(Form("h1_germanium_rel_time_det_%d_%d_to_det_%d_%d_vs_energy_energy_gate_%d_%d",crystals_to_plot.at(detid_idx).first,crystals_to_plot.at(detid_idx).second,dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("germanium delta time t(%d%c) - t(%d%c) vs energy, energy gate %d, %d",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,500,-1000,1000); 
            h2_germanium_time_differences_vs_energy[ihist][detid_idx]->GetYaxis()->SetTitle(Form("dt t(%d%c) - t(%d%c) (ns)",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65)));
            h2_germanium_time_differences_vs_energy[ihist][detid_idx]->GetXaxis()->SetTitle(Form("energy det %d%c (keV)",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65)));
            h2_germanium_time_differences_vs_energy[ihist][detid_idx]->Draw("COLZ");
            folder_germanium_time_differences->Add(h2_germanium_time_differences_vs_energy[ihist][detid_idx]);
            
        }
        c_germanium_time_differences_vs_energy->cd(0);
        folder_germanium_time_differences->Add(c_germanium_time_differences_vs_energy);
    }
        
    
    c_germanium_hitpattern = new TCanvas("c_germanium_hitpattern","Hit pattern DEGAS",650,350);
    detector_labels = new char*[number_of_detectors_to_plot];
    h1_germanium_hitpattern = new TH1F("h1_germanium_hitpattern","Hit pattern of DEGAS",number_of_detectors_to_plot,0,number_of_detectors_to_plot);
    h1_germanium_hitpattern->GetXaxis()->SetAlphanumeric();
    
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        detector_labels[ihist] = Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65));
        h1_germanium_hitpattern->GetXaxis()->SetBinLabel(ihist+1,detector_labels[ihist]);
    }    
    h1_germanium_hitpattern->GetXaxis()->LabelsOption("a");
    h1_germanium_hitpattern->GetXaxis()->SetTitle("crystal");
    h1_germanium_hitpattern->GetYaxis()->SetTitle("counts");
    h1_germanium_hitpattern->SetStats(0);
    h1_germanium_hitpattern->Draw();
    c_germanium_hitpattern->cd(0);
    folder_germanium_hitpattern->Add(h1_germanium_hitpattern);
    folder_germanium_hitpattern->Add(c_germanium_hitpattern);

    run->GetHttpServer()->RegisterCommand("Reset_Ge_Histo", Form("/Objects/%s/->Reset_Ge_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_Ge_Histo", Form("/Objects/%s/->Snapshot_Ge_Histo()", GetName()));

    return kSUCCESS;
}

void GermaniumOnlineSpectra::Reset_Ge_Histo()
{
    c4LOG(info, "Resetting DEGAS histograms.");
    for (int i = 0; i < number_reference_detectors; i++){
       for (int ihist = 0; ihist<number_of_detectors_to_plot; ihist++) 
        {
            h1_germanium_time_differences[i][ihist]->Reset();
            h2_germanium_time_differences_vs_energy[i][ihist]->Reset();
        }
    }
    for (int ihist = 0; ihist<number_of_detectors_to_plot; ihist++) 
    {
        h1_germanium_energy[ihist]->Reset();
        h1_germanium_time[ihist]->Reset();
    }


    h1_germanium_multiplicity->Reset();
    h1_germanium_hitpattern->Reset();
    h2_germanium_energy_vs_detidx->Reset();
    h1_germanium_energy_summed->Reset();
    h1_germanium_energy_summed_vetosci41->Reset();
    h2_germanium_energy_summed_vs_tsci41->Reset();
    c4LOG(info, "DEGAS histograms reset.");
}

void GermaniumOnlineSpectra::Snapshot_Ge_Histo()
{
    c4LOG(info, "Snapshotting DEGAS histograms.");
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
    c4LOG(info, "DEGAS snapshots saved to:" << snapshot_dir);
}

void GermaniumOnlineSpectra::Exec(Option_t* option){

    if (fHitGe && fHitGe->GetEntriesFast() > 0){
    
        Int_t nHits = fHitGe->GetEntriesFast();
        int event_multiplicity = 0;
        
        
        bool sci41_seen = false; // off-spill raw spectra

        for (Int_t ihit = 0; ihit < nHits; ihit++){ // core loop for basic detector spectra and simple conincidences.
    
            GermaniumCalData* hit1 = (GermaniumCalData*)fHitGe->At(ihit);
            if (!hit1) continue;
            int detector_id1 = hit1->Get_detector_id();
            int crystal_id1 = hit1->Get_crystal_id();
            double energy1 = hit1->Get_channel_energy();
            double time1 = hit1->Get_channel_trigger_time();

            
            if (!(germanium_configuration->IsDetectorAuxilliary(detector_id1))) event_multiplicity ++; // count only physical events in germaniums

            if (detector_id1 == germanium_configuration->SC41L() || detector_id1 == germanium_configuration->SC41R()) sci41_seen = true;
            
            int crystal_index1 = std::distance(crystals_to_plot.begin(), std::find(crystals_to_plot.begin(),crystals_to_plot.end(),std::pair<int,int>(detector_id1,crystal_id1)));
            
            h1_germanium_energy[crystal_index1]->Fill(energy1);
            h2_germanium_energy_vs_detidx->Fill(hit1->Get_channel_energy(),crystal_index1);
            h1_germanium_time[crystal_index1]->Fill(time1);
            h1_germanium_hitpattern->Fill(detector_labels[crystal_index1],1);
            if (!(germanium_configuration->IsDetectorAuxilliary(detector_id1))) h1_germanium_energy_summed->Fill(energy1);


            if (nHits >= 2 && dt_reference_detectors.size()>=0){ // reference detector id loop.
                for (int ihit2 = 0; ihit2 < nHits; ihit2++){
                    if (ihit == ihit2) continue;
                    GermaniumCalData * hit2 = (GermaniumCalData*)fHitGe->At(ihit2);
                    int detector_id2 = hit2->Get_detector_id();
                    int crystal_id2 = hit2->Get_crystal_id();
                    double energy2 = hit2->Get_channel_energy();
                    double time2 = hit2->Get_channel_trigger_time();

                    int crystal_index2 = std::distance(dt_reference_detectors.begin(), std::find(dt_reference_detectors.begin(),dt_reference_detectors.end(),std::pair<int,int>(detector_id2,crystal_id2)));                   
                    if (crystal_index2 >= dt_reference_detectors.size()) continue;

                    while (crystal_index2 < dt_reference_detectors.size()){

                    if (dt_reference_detectors_energy_gates.at(crystal_index2).first > 0 && dt_reference_detectors_energy_gates.at(crystal_index2).second > 0){
                        if ((TMath::Abs(energy2 - dt_reference_detectors_energy_gates.at(crystal_index2).first) < energygate_width) && (TMath::Abs(energy1 - dt_reference_detectors_energy_gates.at(crystal_index2).second) < energygate_width)){
                            h1_germanium_time_differences[crystal_index2][crystal_index1]->Fill(time1 - time2);
                            h2_germanium_time_differences_vs_energy[crystal_index2][crystal_index1]->Fill(energy1,time1-time2);
                        }
                    }else{ // no gates
                        h1_germanium_time_differences[crystal_index2][crystal_index1]->Fill(time1 - time2);
                        h2_germanium_time_differences_vs_energy[crystal_index2][crystal_index1]->Fill(energy1,time1-time2);
                    }

                    crystal_index2 = std::distance(dt_reference_detectors.begin()+crystal_index2+1, std::find(dt_reference_detectors.begin()+crystal_index2+1,dt_reference_detectors.end(),std::pair<int,int>(detector_id2,crystal_id2)))+crystal_index2+1; 
                    }
                }
            }
        }


        if (!sci41_seen){ // sci41 vetoed spectra:
            for (Int_t ihit = 0; ihit < nHits; ihit++)
            {   
                GermaniumCalData* hit1 = (GermaniumCalData*)fHitGe->At(ihit);
                if (!hit1) continue;
                int detector_id1 = hit1->Get_detector_id();
                int crystal_id1 = hit1->Get_crystal_id();
                double energy1 = hit1->Get_channel_energy();
                double time1 = hit1->Get_channel_trigger_time();
                if (germanium_configuration->IsDetectorAuxilliary(detector_id1)) continue;

                h1_germanium_energy_summed_vetosci41->Fill(energy1);

                if (nHits >= 2){
                    for (Int_t ihit2 = 0; ihit2 < nHits; ihit2++)
                    {   
                        if (ihit2 == ihit) continue;
                        GermaniumCalData* hit2 = (GermaniumCalData*)fHitGe->At(ihit2);
                        if (!hit2) continue;
                        int detector_id2 = hit2->Get_detector_id();
                        int crystal_id2 = hit2->Get_crystal_id();
                        double energy2 = hit2->Get_channel_energy();
                        double time2 = hit2->Get_channel_trigger_time();

                        if (germanium_configuration->IsDetectorAuxilliary(detector_id2) && detector_id1 != detector_id2) continue;
                        if (TMath::Abs(time2 - time1) < 20) {
                            h2_germanium_energy_energy_vetosci41->Fill(energy1,energy2);
                        }
                    }

                }
            }
        }


        // Spectra with respect to SCI41:
        if (nHits >= 2 && sci41_seen){
        for (int ihit1 = 0; ihit1 < nHits; ihit1 ++){

            GermaniumCalData* hit_sci41 = (GermaniumCalData*)fHitGe->At(ihit1);
            if (!hit_sci41) continue;
            int detector_id_sci41 = hit_sci41->Get_detector_id();
            int crystal_id_sci41 = hit_sci41->Get_crystal_id();
            double energy_sci41 = hit_sci41->Get_channel_energy();
            double time_sci41 = hit_sci41->Get_channel_trigger_time();

            // after this test we have the sci41 hit.
            if (detector_id_sci41 != germanium_configuration->SC41L() && detector_id_sci41 != germanium_configuration->SC41R()) continue;

            for (int ihit2 = 0; ihit2 < nHits; ihit2 ++){
                GermaniumCalData* hit2 = (GermaniumCalData*)fHitGe->At(ihit2);
                if (!hit2) continue;
                int detector_id1 = hit2->Get_detector_id();
                int crystal_id1 = hit2->Get_crystal_id();
                double energy1 = hit2->Get_channel_energy();
                double time1 = hit2->Get_channel_trigger_time();

                if (germanium_configuration->IsDetectorAuxilliary(detector_id1)) continue;

                double timediff = time1 - time_sci41 - germanium_configuration->GetTimeshiftCoefficient(detector_id1,crystal_id1);
                
                h2_germanium_energy_summed_vs_tsci41->Fill(timediff ,energy1);
                if ((TMath::Abs(time1-time_sci41 > 2000)) || (germanium_configuration->IsInsidePromptFlashCut(timediff ,energy1)==true) ) h1_germanium_energy_summed_vs_tsci41_cut->Fill(energy1);

                for (int ihit3 = ihit2+1; ihit3 < nHits; ihit3 ++){
                GermaniumCalData* hit3 = (GermaniumCalData*)fHitGe->At(ihit3);
                if (!hit3) continue;
                int detector_id2 = hit3->Get_detector_id();
                int crystal_id2 = hit3->Get_crystal_id();
                double energy2 = hit3->Get_channel_energy();
                double time2 = hit3->Get_channel_trigger_time();

                if (germanium_configuration->IsDetectorAuxilliary(detector_id2)) continue;

                if (TMath::Abs(time1 - time2) < 50) h2_germanium_energy_energy_sci41_cut->Fill(energy1,energy2);
                }
            }
        }
        }
        


        h1_germanium_multiplicity->Fill(event_multiplicity);
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
