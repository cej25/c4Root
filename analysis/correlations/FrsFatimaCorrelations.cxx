// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsFatimaCorrelations.h"
#include "EventHeader.h"
#include "FatimaTwinpeaksData.h"
#include "FatimaTwinpeaksCalData.h"
#include "FrsGate.h"
#include "FrsHitData.h"
#include "TFatimaTwinpeaksConfiguration.h"

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

FrsFatimaCorrelations::FrsFatimaCorrelations() : FrsFatimaCorrelations("FrsFatimaCorrelations")
{
    fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
}

FrsFatimaCorrelations::FrsFatimaCorrelations(FrsGate * fg) : FrsFatimaCorrelations("FrsFatimaCorrelations")
{
    fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
    frsgate = fg;
}

FrsFatimaCorrelations::FrsFatimaCorrelations(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatima(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
    fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
}

FrsFatimaCorrelations::~FrsFatimaCorrelations()
{
    c4LOG(info, "");
    if (fHitFatima)
        delete fHitFatima;
    if (fHitFrs)
        delete fHitFrs;
}


InitStatus FrsFatimaCorrelations::Init()
{


    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatima = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatima, "Branch FatimaTwinpeaksCalData not found!");

    fHitFrs = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fHitFrs, "Branch FrsHitData not found!");


    TDirectory::TContext ctx(nullptr);

    folder_fatima = new TFolder(TString("FATIMA FRS GATE " + frsgate->GetName()), TString("FATIMA FRS GATE" + frsgate->GetName()));

    run->AddObject(folder_fatima);

    //Implant rate
    c_frs_rate = new TCanvas(TString("c_frs_rate_monitor_gated_")+frsgate->GetName(),TString("Implant rate gated on ")+frsgate->GetName());
    g_frs_rate = new TGraph();
    g_frs_rate->SetName(TString("g_frs_rate_monitor_gated_")+frsgate->GetName());
    g_frs_rate->SetTitle(TString("FRS identified ions per second, avg 60 secs"));
    g_frs_rate->Draw("ALP");
    folder_fatima->Add(c_frs_rate);
    folder_fatima->Add(g_frs_rate);

    c_frs_Z_vs_AoQ_gated = new TCanvas(TString("c_frs_Z_vs_AoQ_gated_")+frsgate->GetName(),TString("Z vs AoQ plot gated on FRS ")+frsgate->GetName());
    h2_frs_Z_vs_AoQ_gated = new TH2F(TString("h2_frs_Z_vs_AoQ_gated_")+frsgate->GetName(),TString("Z vs AoQ plot gated on FRS ")+frsgate->GetName(),1000,2.35,2.60,1000,70,82);
    h2_frs_Z_vs_AoQ_gated->GetXaxis()->SetTitle("A/Q");
    h2_frs_Z_vs_AoQ_gated->GetYaxis()->SetTitle("Z");
    c_frs_Z_vs_AoQ_gated->cd(0);
    folder_fatima->Add(c_frs_Z_vs_AoQ_gated);
    folder_fatima->Add(h2_frs_Z_vs_AoQ_gated);

    
    c_fatima_energy_vs_tsci41 = new TCanvas(TString("c_fatima_summed_vs_tsci41_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det) - t(sci41), short lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_summed_vs_tsci41 = new TH2F(TString("h2_fatima_summed_vs_tsci41_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det) - t(sci41), short lifetime,  gated FRS on "+frsgate->GetName()),1000,-8000,8000,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_summed_vs_tsci41->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_summed_vs_tsci41->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_summed_vs_tsci41->Draw("COLZ");
    c_fatima_energy_vs_tsci41->cd(0);
    folder_fatima->Add(c_fatima_energy_vs_tsci41);
    folder_fatima->Add(h2_fatima_summed_vs_tsci41);

    
    c_fatima_energy_promptflash_cut = new TCanvas(TString("c_fatima_energy_promptflash_cut_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, short lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_energy_promptflash_cut = new TH1F(TString("h1_fatima_energy_promptflash_cut_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, short lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_energy_promptflash_cut->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_energy_promptflash_cut->Draw("COLZ");
    c_fatima_energy_promptflash_cut->cd(0);
    folder_fatima->Add(c_fatima_energy_promptflash_cut);
    folder_fatima->Add(h1_fatima_energy_promptflash_cut);



    c_fatima_energy_vs_wr_long = new TCanvas(TString("c_fatima_summed_vs_wr_long_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_summed_vs_wr_long = new TH2F(TString("h2_fatima_summed_vs_wr_long_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, gated FRS on "+frsgate->GetName()),1000,-1e3,stop_long_lifetime_collection,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_summed_vs_wr_long->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_summed_vs_wr_long->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_summed_vs_wr_long->Draw("COLZ");
    c_fatima_energy_vs_wr_long->cd(0);
    folder_fatima->Add(c_fatima_energy_vs_wr_long);
    folder_fatima->Add(h2_fatima_summed_vs_wr_long);

    
    c_fatima_energy_promptflash_cut_long = new TCanvas(TString("c_fatima_energy_promptflash_cut_long_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, long lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_energy_promptflash_cut_long = new TH1F(TString("h1_fatima_energy_promptflash_cut_long_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, long lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_energy_promptflash_cut_long->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_energy_promptflash_cut_long->Draw("COLZ");
    c_fatima_energy_promptflash_cut_long->cd(0);
    folder_fatima->Add(c_fatima_energy_promptflash_cut_long);
    folder_fatima->Add(h1_fatima_energy_promptflash_cut_long);
    

    //energy-gated spectra:
    folder_energy_gated = new TFolder*[gamma_energies_of_interest.size()];

    c_fatima_tsci41_energy_gated = new TCanvas*[gamma_energies_of_interest.size()];
    h1_fatima_tsci41_energy_gated = new TH1F*[gamma_energies_of_interest.size()];
        
    c_fatima_energy_promptflash_cut_energy_gated = new TCanvas*[gamma_energies_of_interest.size()];
    h1_fatima_energy_promptflash_cut_energy_gated = new TH1F*[gamma_energies_of_interest.size()];
        
    //long:
    c_fatima_energy_promptflash_cut_long_energy_gated = new TCanvas*[gamma_energies_of_interest.size()];
    h1_fatima_energy_promptflash_cut_long_energy_gated = new TH1F*[gamma_energies_of_interest.size()];

    c_fatima_twr_sci41_energy_gated = new TCanvas*[gamma_energies_of_interest.size()];
    h1_fatima_twr_sci41_energy_gated = new TH1F*[gamma_energies_of_interest.size()];
        
    
    for (int idx_gamma_gate = 0; idx_gamma_gate < gamma_energies_of_interest.size(); idx_gamma_gate++){
        folder_energy_gated[idx_gamma_gate] = new TFolder(Form("Energy gated coincidence spectra, Eg = %i",(int)gamma_energies_of_interest.at(idx_gamma_gate)),Form("Energy gated coincidence spectra, Eg = %i",(int)gamma_energies_of_interest.at(idx_gamma_gate)));
        folder_fatima->Add(folder_energy_gated[idx_gamma_gate]);

        c_fatima_tsci41_energy_gated[idx_gamma_gate] = new TCanvas(TString(Form("c_fatima_tsci41_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("t(det) - t(sci41) gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()));
        h1_fatima_tsci41_energy_gated[idx_gamma_gate] = new TH1F(TString(Form("h1_fatima_tsci41_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("t(det) - t(sci41) gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()),1000,-10e3,stop_short_lifetime_collection);
        h1_fatima_tsci41_energy_gated[idx_gamma_gate]->GetXaxis()->SetTitle("time (ns)");
        h1_fatima_tsci41_energy_gated[idx_gamma_gate]->Draw();
        c_fatima_tsci41_energy_gated[idx_gamma_gate]->cd(0);
        folder_energy_gated[idx_gamma_gate]->Add(c_fatima_tsci41_energy_gated[idx_gamma_gate]);
        folder_energy_gated[idx_gamma_gate]->Add(h1_fatima_tsci41_energy_gated[idx_gamma_gate]);

        
        c_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate] = new TCanvas(TString(Form("c_fatima_energy_promptflash_cut_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gammas gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()));
        h1_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate] = new TH1F(TString(Form("h1_fatima_energy_promptflash_cut_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gammas gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate]->GetXaxis()->SetTitle("Energy (keV)");
        h1_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate]->Draw();
        c_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate]->cd(0);
        folder_energy_gated[idx_gamma_gate]->Add(c_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate]);
        folder_energy_gated[idx_gamma_gate]->Add(h1_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate]);

        c_fatima_twr_sci41_energy_gated[idx_gamma_gate] = new TCanvas(TString(Form("c_fatima_twr_sci41_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("WR t(det) - t(sci41) gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()));
        h1_fatima_twr_sci41_energy_gated[idx_gamma_gate] = new TH1F(TString(Form("h1_fatima_twr_sci41_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("WR t(det) - t(sci41) gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()),1000,-1e3,stop_long_lifetime_collection);
        h1_fatima_twr_sci41_energy_gated[idx_gamma_gate]->GetXaxis()->SetTitle("time (ns)");
        h1_fatima_twr_sci41_energy_gated[idx_gamma_gate]->Draw();
        c_fatima_twr_sci41_energy_gated[idx_gamma_gate]->cd(0);
        folder_energy_gated[idx_gamma_gate]->Add(c_fatima_twr_sci41_energy_gated[idx_gamma_gate]);
        folder_energy_gated[idx_gamma_gate]->Add(h1_fatima_twr_sci41_energy_gated[idx_gamma_gate]);

        c_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate] = new TCanvas(TString(Form("c_fatima_energy_promptflash_cut_long_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gammas gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()));
        h1_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate] = new TH1F(TString(Form("h1_fatima_energy_promptflash_cut_long_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gammas gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate]->GetXaxis()->SetTitle("Energy (keV)");
        h1_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate]->Draw();
        c_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate]->cd(0);
        folder_energy_gated[idx_gamma_gate]->Add(c_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate]);
        folder_energy_gated[idx_gamma_gate]->Add(h1_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate]);        

    }
    

    run->GetHttpServer()->RegisterCommand("Reset_Ge_Histo", Form("/Objects/%s/->Reset_Ge_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_Ge_Histo", Form("/Objects/%s/->Snapshot_Ge_Histo()", GetName()));

    return kSUCCESS;
}


void FrsFatimaCorrelations::Exec(Option_t* option){

    if (fHitFrs && fHitFrs->GetEntriesFast() >= 1){
        for (int frsihit = 0; frsihit < fHitFrs->GetEntriesFast(); frsihit++){
            FrsHitData * frshit = (FrsHitData*) fHitFrs->At(frsihit);

            int64_t wr_t = frshit->Get_wr_t();
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
                frs_rate_implanted ++;
                h2_frs_Z_vs_AoQ_gated->Fill(ID_AoQ,ID_z);

                if ((int64_t)wr_t_last_frs_hit  - (int64_t)frs_rate_time > 60e9 ){
                    g_frs_rate->AddPoint(wr_t_last_frs_hit,frs_rate_implanted/60.0);
                    frs_rate_time = wr_t_last_frs_hit;
                    frs_rate_implanted = 0;
                }
            }else{
                wr_t_last_frs_hit = 0;
            }
        }
    }else{
        positive_PID = false;
    }

    if (fHitFatima && fHitFatima->GetEntriesFast() > 0){
    
        Int_t nHits = fHitFatima->GetEntriesFast();
        int event_multiplicity = 0;
        
        
        bool sci41_seen = false; // off-spill raw spectra
        int sci41_hit_idx = -1; // sci41's hit index, for getting the time
        int detector_id_sci41 = 0;
        double energy_sci41 = 0;
        double time_sci41 = 0;

        for (Int_t ihit = 0; ihit < nHits; ihit++){ // find the sci41 hit if it is there.
    
            FatimaTwinpeaksCalData* hit1 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit);
            if (!hit1) continue;
            int detector_id1 = hit1->Get_detector_id();
            double energy1 = hit1->Get_energy();
            double time1 = hit1->Get_fast_lead_time();

            
            if (!(fatima_configuration->IsDetectorAuxilliary(detector_id1))) event_multiplicity ++; // count only physical events in germaniums
            
            if (detector_id1 == fatima_configuration->SC41L() || detector_id1 == fatima_configuration->SC41R()) {
                detector_id_sci41 = hit1->Get_detector_id();
                energy_sci41 = hit1->Get_energy();
                time_sci41 = hit1->Get_fast_lead_time();
                
                sci41_seen = true;
                sci41_hit_idx = ihit;
                break;
            }
        }

        // Spectra with respect to SCI41 - 'short' isomers
        if (nHits >= 2 && sci41_seen && positive_PID){

            for (int ihit1 = 0; ihit1 < nHits; ihit1 ++){
                if (ihit1 == sci41_hit_idx) continue;
                FatimaTwinpeaksCalData* hit1 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit1);
                if (!hit1) continue;
                int detector_id1 = hit1->Get_detector_id();
                double energy1 = hit1->Get_energy();
                double time1 = hit1->Get_fast_lead_time();

                if (fatima_configuration->IsDetectorAuxilliary(detector_id1)) continue;

                double timediff1 = time1 - time_sci41 - fatima_configuration->GetTimeshiftCoefficient(detector_id1);
                
                h2_fatima_summed_vs_tsci41->Fill(timediff1 ,energy1);

                if ((fatima_configuration->IsInsidePromptFlashCut(timediff1 ,energy1)==true) ) continue;
                
                h1_fatima_energy_promptflash_cut->Fill(energy1);

                for (int idx_gamma_gate = 0; idx_gamma_gate < gamma_energies_of_interest.size(); idx_gamma_gate++){
                    if (!(TMath::Abs(energy1 - gamma_energies_of_interest.at(idx_gamma_gate))<gate_width_gamma_energies_of_interest.at(idx_gamma_gate)) && fatima_configuration->IsInsidePromptFlashCut(timediff1,energy1)==false) continue;
                        //now energy1 fulfills the energy requirement and is outside prompt flash
                        
                        h1_fatima_tsci41_energy_gated[idx_gamma_gate]->Fill(timediff1);
                                                
                        if (nHits >= 3){
                        
                        for (int ihit2 = 0; ihit2<nHits; ihit2 ++){
                            if (ihit2 == sci41_hit_idx) continue;
                            FatimaTwinpeaksCalData* hit2 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit2);
                            if (!hit2) continue;
                            if (ihit2 == ihit1) continue;
                            int detector_id2 = hit2->Get_detector_id();
                            double energy2 = hit2->Get_energy();
                            double time2 = hit2->Get_fast_lead_time();

                            if (fatima_configuration->IsDetectorAuxilliary(detector_id2)) continue;
                            if (TMath::Abs(time2-time1) > fatima_coincidence_gate) continue;

                            double timediff2 = time2 - time_sci41 - fatima_configuration->GetTimeshiftCoefficient(detector_id2);
                            if ((fatima_configuration->IsInsidePromptFlashCut(timediff2,energy2))) continue;

                            // energy1 and energy2 are both in coincidence and outside the promptflash here:
                            h1_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate]->Fill(energy2);
                        }
                    }
                }
        
            }
        }

        if (nHits >= 1 && wr_t_last_frs_hit != 0){
            //long isomer
            for (int ihit1 = 0; ihit1 < nHits; ihit1 ++){

            FatimaTwinpeaksCalData* hit_long1 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit1);
            if (!hit_long1) continue;
            int detector_id_long = hit_long1->Get_detector_id();
            double energy_long = hit_long1->Get_energy();
            double time_long = hit_long1->Get_fast_lead_time();
            int64_t fat_wr_long = hit_long1->Get_wr_t();

            if (fatima_configuration->IsDetectorAuxilliary(detector_id_long)) continue;


            h2_fatima_summed_vs_wr_long->Fill((int64_t)fat_wr_long-(int64_t)wr_t_last_frs_hit, energy_long);
            

            // cut the prompt flash on the whiterabbit:
            if ((int64_t)fat_wr_long - (int64_t)wr_t_last_frs_hit < start_long_lifetime_collection) continue;


            
            if ((int64_t)fat_wr_long - (int64_t)wr_t_last_frs_hit < stop_long_lifetime_collection) h1_fatima_energy_promptflash_cut_long->Fill(energy_long);

            for (int idx_gamma_gate = 0; idx_gamma_gate < gamma_energies_of_interest.size(); idx_gamma_gate++){
                    if (!(TMath::Abs(energy_long - gamma_energies_of_interest.at(idx_gamma_gate))<gate_width_gamma_energies_of_interest.at(idx_gamma_gate))) continue;
                        //now energy1 fulfills the energy requirement and is outside prompt flash
                        
                        h1_fatima_twr_sci41_energy_gated[idx_gamma_gate]->Fill((int64_t)fat_wr_long-(int64_t)wr_t_last_frs_hit);

                        
                        if (nHits >= 2){
                        
                        for (int ihit2 = 0; ihit2<nHits; ihit2 ++){
                            FatimaTwinpeaksCalData* hit_long2 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit2);
                            if (!hit_long2) continue;
                            if (ihit1 == ihit2) continue;
                            int detector_id_long2 = hit_long2->Get_detector_id();
                            double energy_long2 = hit_long2->Get_energy();
                            double time_long2 = hit_long2->Get_fast_lead_time();
                            int64_t fat_wr_long2 = hit_long2->Get_wr_t();


                            if (fatima_configuration->IsDetectorAuxilliary(detector_id_long2)) continue;
                            
                            // check coincidence:
                            if (TMath::Abs(time_long2-time_long- fatima_configuration->GetTimeshiftCoefficient(detector_id_long2) - fatima_configuration->GetTimeshiftCoefficient(detector_id_long)) > fatima_coincidence_gate) continue; 
                            if ((int64_t)fat_wr_long2 - (int64_t)wr_t_last_frs_hit < start_long_lifetime_collection) continue;
                            
                            // energy1 and energy2 are both in coincidence and outside the promptflash here:
                            if ((int64_t)fat_wr_long2 - (int64_t)wr_t_last_frs_hit < stop_long_lifetime_collection) h1_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate]->Fill(energy_long2);
                        }
                    }
                }

            }
        }

    }

    fNEvents += 1;
}

void FrsFatimaCorrelations::FinishEvent()
{
    if (fHitFatima)
    {
        fHitFatima->Clear();
    }
}

void FrsFatimaCorrelations::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }
    if (fHitFatima)
    {
        folder_fatima->Write();
        c4LOG(info, "FATIMA-FRS histograms written to file.");
    }
}

ClassImp(FrsFatimaCorrelations)
