// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "GermaniumResolution.h"
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
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include "TDirectory.h"

GermaniumResolution::GermaniumResolution() : GermaniumResolution("GermaniumResolution")
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

GermaniumResolution::GermaniumResolution(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

GermaniumResolution::~GermaniumResolution()
{
    c4LOG(info, "");
    if (fHitGe)
        delete fHitGe;
}

InitStatus GermaniumResolution::Init()
{

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();

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
    

    // energy spectra:
    c_germanium_energy  = new TCanvas("c_germanium_energy","Calibrated Germanium spectra",650,350);
    c_germanium_energy->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_germanium_energy = new TH1F*[number_of_detectors_to_plot];
    h1_germanium_energy_clear = new TH1F*[number_of_detectors_to_plot];

    resoltutions = new std::vector<double>[number_of_detectors_to_plot];
    resoltutions_err = new std::vector<double>[number_of_detectors_to_plot];
    time = new std::vector<uint64_t>[number_of_detectors_to_plot];

    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_germanium_energy->cd(ihist+1);
        h1_germanium_energy[ihist] = new TH1F(Form("h1_germanium_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_germanium_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_energy[ihist]->Draw();
        h1_germanium_energy_clear[ihist] = new TH1F(Form("h1_germanium_energy_%d_%d_clear",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_germanium_energy_clear[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_energy_clear[ihist]->Draw();
        run->AddObject(h1_germanium_energy[ihist]);
        

    }
    c_germanium_energy->cd(0);
    run->AddObject(c_germanium_energy);


    return kSUCCESS;
}

void GermaniumResolution::Exec(Option_t* option){

    if (fHitGe && fHitGe->GetEntriesFast() > 0){
    
        Int_t nHits = fHitGe->GetEntriesFast();
    
    
        for (Int_t ihit = 0; ihit < nHits; ihit++){ // core loop for basic detector spectra and simple conincidences.
    
            GermaniumCalData* hit1 = (GermaniumCalData*)fHitGe->At(ihit);
            if (!hit1) continue;
            int detector_id1 = hit1->Get_detector_id();
            int crystal_id1 = hit1->Get_crystal_id();
            double energy1 = hit1->Get_channel_energy();
            double time1 = hit1->Get_channel_trigger_time();

            current_wr = hit1->Get_wr_t();

            if (first_wr == 0) first_wr = current_wr;

            
            int crystal_index1 = std::distance(crystals_to_plot.begin(), std::find(crystals_to_plot.begin(),crystals_to_plot.end(),std::pair<int,int>(detector_id1,crystal_id1)));
            h1_germanium_energy[crystal_index1]->Fill(energy1);
            h1_germanium_energy_clear[crystal_index1]->Fill(energy1);
        }
    }

    fNEvents += 1;
}

void GermaniumResolution::FinishEvent()
{
    if (fHitGe)
    {
        fHitGe->Clear();
    }

    if (((int64_t)current_wr - (int64_t)last_wr > 600e9)) // 10 mins
    {
        TF1 * gaus = new TF1("gaus","gaus",peak_interest_energy-peak_interest_fitwidth,peak_interest_energy+peak_interest_fitwidth);
        for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){        
            h1_germanium_energy_clear[ihist]->Fit(gaus,"QR");


            resoltutions[ihist].emplace_back(gaus->GetParameter(2)*2.355);
            std::cout << "ihist = " << ihist << "  res = " << gaus->GetParameter(2)*2.355 << std::endl;
            resoltutions_err[ihist].emplace_back(gaus->GetParError(2)*2.355);
            time[ihist].emplace_back((int64_t)current_wr - (int64_t)first_wr);

            h1_germanium_energy_clear[ihist]->Reset();

            last_wr = current_wr;
        }
    }
}

void GermaniumResolution::FinishTask()
{

    TF1 * gaus = new TF1("gaus","gaus",peak_interest_energy-peak_interest_fitwidth,peak_interest_energy+peak_interest_fitwidth);
    c4LOG(info,"Resolution measurement results");
    std::cout << "det | crystal | constant | mean (keV) | sigma (keV) | FWHM (keV) | FWTM | ratio" << std::endl;

    if (fHitGe)
    {
        for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){        
        h1_germanium_energy[ihist]->Fit(gaus,"QR");
        
        double tenthmaximum = gaus->Eval(gaus->GetParameter(1))/10.0;
        
        int binnr1 = h1_germanium_energy[ihist]->FindBin(1250.0);
        int binnr2 = h1_germanium_energy[ihist]->FindBin(1350.0);
        int binlow = h1_germanium_energy[ihist]->FindFirstBinAbove(tenthmaximum,1,binnr1,binnr2);        
        int binhigh = h1_germanium_energy[ihist]->FindLastBinAbove(tenthmaximum,1,binnr1,binnr2);

        double fwtm = h1_germanium_energy[ihist]->GetBinCenter(binhigh) - h1_germanium_energy[ihist]->GetBinCenter(binlow);

        std::cout << Form("%d %c %f %f %f %f %f %f",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65),gaus->GetParameter(0),gaus->GetParameter(1),gaus->GetParameter(2),gaus->GetParameter(2)*2.355,fwtm,fwtm/(gaus->GetParameter(2)*2.355)) << std::endl;

        int nvals = resoltutions[ihist].size();
        double x[nvals];
        double ex[nvals];
        
        double y[nvals];
        double ey[nvals];
        
        for (int i = 1; i< nvals; i++){
            x[i] = time[ihist].at(i)/60e9; // in minutes 
            ex[i] = 0;
            
            y[i] = resoltutions[ihist].at(i);
            ey[i] = resoltutions_err[ihist].at(i);
    
        }

        TGraphErrors * g1 = new TGraphErrors(nvals,x,y,ex,ey);
        g1->SetName(Form("resoution_v_time_%d_%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
        g1->Write();

        h1_germanium_energy[ihist]->Write();
        
        }
    }
}

ClassImp(GermaniumResolution)
