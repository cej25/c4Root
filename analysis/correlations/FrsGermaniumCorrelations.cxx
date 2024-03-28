// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsGermaniumCorrelations.h"
#include "EventHeader.h"
#include "GermaniumFebexData.h"
#include "GermaniumCalData.h"
#include "FrsGate.h"
#include "FrsHitData.h"
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

FrsGermaniumCorrelations::FrsGermaniumCorrelations() : FrsGermaniumCorrelations("FrsGermaniumCorrelations")
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

FrsGermaniumCorrelations::FrsGermaniumCorrelations(FrsGate * fg) : FrsGermaniumCorrelations("FrsGermaniumCorrelations")
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
    frsgate = fg;
}

FrsGermaniumCorrelations::FrsGermaniumCorrelations(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

FrsGermaniumCorrelations::~FrsGermaniumCorrelations()
{
    c4LOG(info, "");
    if (fHitGe)
        delete fHitGe;
    if (fHitFrs)
        delete fHitFrs;
}


InitStatus FrsGermaniumCorrelations::Init()
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

    fHitFrs = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fHitFrs, "Branch FrsHitData not found!");


    TDirectory::TContext ctx(nullptr);

    folder_germanium = new TFolder(TString("DEGAS FRS GATE " + frsgate->GetName()), TString("DEGAS FRS GATE" + frsgate->GetName()));

    run->AddObject(folder_germanium);    
    
    
    c_germanium_energy_vs_tsci41 = new TCanvas(TString("c_germanium_summed_vs_tsci41_frs_gate_"+frsgate->GetName()),TString("Germanium energies vs t(det) - t(sci41) gated FRS on "+frsgate->GetName()),650,350);
    h2_germanium_summed_vs_tsci41 = new TH2F(TString("h2_germanium_summed_vs_tsci41_frs_gate_"+frsgate->GetName()),TString("Germanium energies vs t(det) - t(sci41) gated FRS on "+frsgate->GetName()),1000,-500,5000,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_germanium_summed_vs_tsci41->GetXaxis()->SetTitle("time difference (ns)");
    h2_germanium_summed_vs_tsci41->GetYaxis()->SetTitle("energy (keV)");
    h2_germanium_summed_vs_tsci41->Draw("COLZ");
    c_germanium_energy_vs_tsci41->cd(0);
    folder_germanium->Add(c_germanium_energy_vs_tsci41);
    folder_germanium->Add(h2_germanium_summed_vs_tsci41);

    
    c_germanium_energy_promptflash_cut = new TCanvas(TString("c_germanium_energy_promptflash_cut_frs_gate_"+frsgate->GetName()),TString("Germanium energy, prompt flash cut out, gated FRS on "+frsgate->GetName()),650,350);
    h1_germanium_energy_promptflash_cut = new TH1F(TString("h1_germanium_energy_promptflash_cut_frs_gate_"+frsgate->GetName()),TString("Germanium energy, prompt flash cut out, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_germanium_energy_promptflash_cut->GetXaxis()->SetTitle("energy (keV)");
    h1_germanium_energy_promptflash_cut->Draw("COLZ");
    c_germanium_energy_promptflash_cut->cd(0);
    folder_germanium->Add(c_germanium_energy_promptflash_cut);
    folder_germanium->Add(h1_germanium_energy_promptflash_cut);



    c_germanium_energy_vs_wr_long = new TCanvas(TString("c_germanium_summed_vs_wr_long_frs_gate_"+frsgate->GetName()),TString("Germanium energies vs t(det,wr) - t(sci41,wr) long, gated FRS on "+frsgate->GetName()),650,350);
    h2_germanium_summed_vs_wr_long = new TH2F(TString("h2_germanium_summed_vs_wr_long_frs_gate_"+frsgate->GetName()),TString("Germanium energies vs t(det,wr) - t(sci41,wr) long, gated FRS on "+frsgate->GetName()),1000,-500,5000,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_germanium_summed_vs_wr_long->GetXaxis()->SetTitle("time difference (ns)");
    h2_germanium_summed_vs_wr_long->GetYaxis()->SetTitle("energy (keV)");
    h2_germanium_summed_vs_wr_long->Draw("COLZ");
    c_germanium_energy_vs_wr_long->cd(0);
    folder_germanium->Add(c_germanium_energy_vs_wr_long);
    folder_germanium->Add(h2_germanium_summed_vs_wr_long);

    
    c_germanium_energy_promptflash_cut_long = new TCanvas(TString("c_germanium_energy_promptflash_cut_long_frs_gate_"+frsgate->GetName()),TString("Germanium energy, prompt flash cut out, gated FRS on "+frsgate->GetName()),650,350);
    h1_germanium_energy_promptflash_cut_long = new TH1F(TString("h1_germanium_energy_promptflash_cut_long_frs_gate_"+frsgate->GetName()),TString("Germanium energy, prompt flash cut out, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_germanium_energy_promptflash_cut_long->GetXaxis()->SetTitle("energy (keV)");
    h1_germanium_energy_promptflash_cut_long->Draw("COLZ");
    c_germanium_energy_promptflash_cut_long->cd(0);
    folder_germanium->Add(c_germanium_energy_promptflash_cut_long);
    folder_germanium->Add(h1_germanium_energy_promptflash_cut_long);
    
    

    run->GetHttpServer()->RegisterCommand("Reset_Ge_Histo", Form("/Objects/%s/->Reset_Ge_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_Ge_Histo", Form("/Objects/%s/->Snapshot_Ge_Histo()", GetName()));

    return kSUCCESS;
}


void FrsGermaniumCorrelations::Exec(Option_t* option){

    if (fHitFrs && fHitFrs->GetEntriesFast() >= 1){
        for (int frsihit = 0; frsihit < fHitFrs->GetEntriesFast(); frsihit++){
            FrsHitData * frshit = (FrsHitData*) fHitFrs->At(frsihit);

            uint64_t wr_t = frshit->Get_wr_t();
            double ID_x2 = frshit->Get_ID_x2();
            double ID_y2 = frshit->Get_ID_y2();
            double ID_x4 = frshit->Get_ID_x4();
            double ID_AoQ = frshit->Get_ID_AoQ();
            double ID_z = frshit->Get_ID_z();
            double ID_z2 = frshit->Get_ID_z2();
            double ID_dEdeg = frshit->Get_ID_dEdeg();

            positive_PID = frsgate->PassedGate(ID_z, ID_z2, ID_x2, ID_x4, ID_AoQ, ID_dEdeg);
            if (positive_PID){
                wr_t_last_frs_hit = wr_t;
            }

            
        }
    }

    if (fHitGe && fHitGe->GetEntriesFast() > 0){
    
        Int_t nHits = fHitGe->GetEntriesFast();
        int event_multiplicity = 0;
        
        
        bool sci41_seen = false; // off-spill raw spectra

        for (Int_t ihit = 0; ihit < nHits; ihit++){ // find the sci41 hit if it is there.
    
            GermaniumCalData* hit1 = (GermaniumCalData*)fHitGe->At(ihit);
            if (!hit1) continue;
            int detector_id1 = hit1->Get_detector_id();
            int crystal_id1 = hit1->Get_crystal_id();
            double energy1 = hit1->Get_channel_energy();
            double time1 = hit1->Get_channel_trigger_time();

            
            if (!(germanium_configuration->IsDetectorAuxilliary(detector_id1))) event_multiplicity ++; // count only physical events in germaniums

            if (detector_id1 == germanium_configuration->SC41L() || detector_id1 == germanium_configuration->SC41R()) sci41_seen = true;
        }

        // Spectra with respect to SCI41 - 'short' isomers
        if (nHits >= 2 && sci41_seen && positive_PID){
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
                
                h2_germanium_summed_vs_tsci41->Fill(timediff ,energy1);
                if ((TMath::Abs(time1-time_sci41 > 2000)) || (germanium_configuration->IsInsidePromptFlashCut(timediff ,energy1)==true) ) h1_germanium_energy_promptflash_cut->Fill(energy1);
            }
        }
        }

        if (nHits >= 1 && !sci41_seen && ((int64_t)((GermaniumCalData*)fHitGe->At(0))->Get_wr_t() - (int64_t)wr_t_last_frs_hit) > 1000 && ((int64_t)((GermaniumCalData*)fHitGe->At(0))->Get_wr_t() - (int64_t)wr_t_last_frs_hit) < 801000){
            //long isomer.
            for (int ihit1 = 0; ihit1 < nHits; ihit1 ++){

            GermaniumCalData* hit_long = (GermaniumCalData*)fHitGe->At(ihit1);
            if (!hit_long) continue;
            int detector_id_long = hit_long->Get_detector_id();
            int crystal_id_long = hit_long->Get_crystal_id();
            double energy_long = hit_long->Get_channel_energy();
            double time_long = hit_long->Get_channel_trigger_time();
            uint64_t ge_wr = hit_long->Get_wr_t();

            if (germanium_configuration->IsDetectorAuxilliary(detector_id_long)) continue;
            
            if (((int64_t)ge_wr-(int64_t)wr_t_last_frs_hit)>1000 && ((int64_t)ge_wr- (int64_t)wr_t_last_frs_hit) < 101000){
                h2_germanium_summed_vs_wr_long->Fill((int64_t)ge_wr- (int64_t)wr_t_last_frs_hit, energy_long);
                h1_germanium_energy_promptflash_cut_long->Fill(energy_long);
            }else if (((int64_t)ge_wr-(int64_t)wr_t_last_frs_hit)>701000 && ((int64_t)ge_wr- (int64_t)wr_t_last_frs_hit) < 801000){
                h2_germanium_summed_vs_wr_long->Fill((int64_t)ge_wr- (int64_t)wr_t_last_frs_hit, energy_long,-1);
                h1_germanium_energy_promptflash_cut_long->Fill(energy_long,-1); 
            }


            }

        }


    }

    fNEvents += 1;
}

void FrsGermaniumCorrelations::FinishEvent()
{
    if (fHitGe)
    {
        fHitGe->Clear();
    }
}

void FrsGermaniumCorrelations::FinishTask()
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

ClassImp(FrsGermaniumCorrelations)
