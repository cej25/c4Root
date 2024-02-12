// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

// c4
#include "FatimaTimingAnalysis.h"
#include "EventHeader.h"
#include "FatimaTwinpeaksCalData.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TRandom.h"


FatimaTimingAnalysis::FatimaTimingAnalysis() : FatimaTimingAnalysis("FatimaTimingAnalysis")
{
}

FatimaTimingAnalysis::FatimaTimingAnalysis(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatimaTwinpeaks(nullptr)
    , fNEvents(0)
    , header(nullptr)
{
}

FatimaTimingAnalysis::~FatimaTimingAnalysis()
{
    c4LOG(info, "");
    if (fHitFatimaTwinpeaks)
        delete fHitFatimaTwinpeaks;
}

void FatimaTimingAnalysis::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus FatimaTimingAnalysis::Init()
{
    c4LOG(info, "");
    mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    //FairRunAna * run = FairRunAna::Instance();

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatimaTwinpeaks = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatimaTwinpeaks, "Branch FatimaTwinpeaksCalData not found!");


    TFolder * fatima_spectra_folder = new TFolder("FatimaTimingAnalysis", "FatimaTimingAnalysis");

    //run->AddObject(fatima_spectra_folder);


    if (detector_id_analyze == nullptr) {c4LOG(fatal, "Please set which detector ids to analyze");}

    h_slow_ToT_vs_detector_id = new TH2F("h_slow_ToT_vs_detector_id","Energy of detector Y;Slow ToT (ns);det nr.",fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high,detector_id_analyze->size()+1,0,detector_id_analyze->size()+1);
    h_energy_vs_detector_id = new TH2F("h_energy_vs_detector_id","Energy of detector Y;Energy (kev);det nr.",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,detector_id_analyze->size()+1,0,detector_id_analyze->size()+1);
    h_energy_energy = new TH2F("h_energy_energy","Energy det 0 vs det 1",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);

    fatima_spectra_folder->Add(h_slow_ToT_vs_detector_id);
    fatima_spectra_folder->Add(h_energy_vs_detector_id);
    fatima_spectra_folder->Add(h_energy_energy);
    

    //h_energy_E1_E2_dt
    h_energy_E1_E2_dt = new TH1F**[detector_id_analyze->size()];
    for (int i = 0; i<detector_id_analyze->size(); i++){
        h_energy_E1_E2_dt[i] = new TH1F*[detector_id_analyze->size()]; //(-j)
        for (int j=i+1; j<detector_id_analyze->size(); j++){
            h_energy_E1_E2_dt[i][j] = new TH1F(Form("h_energy_E1_%i_E2_%i_det_%i_det_%i_dt",(int)E1, (int)E2,detector_id_analyze->at(i),detector_id_analyze->at(j)),Form("E1 = %f, E2 = %f, t%i - t%i",E1,E2,detector_id_analyze->at(j),detector_id_analyze->at(i)),Nbins,lowBin,highBin);
            fatima_spectra_folder->Add(h_energy_E1_E2_dt[i][j]);
        }
    }

    return kSUCCESS;
    
}


void FatimaTimingAnalysis::Exec(Option_t* option)
{   
    if (fHitFatimaTwinpeaks && fHitFatimaTwinpeaks->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitFatimaTwinpeaks->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            FatimaTwinpeaksCalData* hit1 = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit);

            if (!hit1) continue;

            double slow_ToT1 = hit1->Get_slow_ToT();
            double fast_lead1 = hit1->Get_fast_lead_time();
            uint16_t detector_id1 = hit1->Get_detector_id();
            double energy1 = hit1->Get_energy();

            if (std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id1) == detector_id_analyze->end()) continue; //not in vector of dets to analyze
            
            if (energy1 == 0) energy1 = slow_ToT1;
                
            h_slow_ToT_vs_detector_id->Fill(slow_ToT1,detector_id1);
            h_energy_vs_detector_id->Fill(energy1,detector_id1);
                
            if (nHits>=2){ 
                for (size_t ihit2 = ihit+1; ihit2 < nHits; ihit2++) {
                    FatimaTwinpeaksCalData* hit2 = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit2);
                    double slow_ToT2 = hit2->Get_slow_ToT();
                    double fast_lead2 = hit2->Get_fast_lead_time();
                    uint16_t detector_id2 = hit2->Get_detector_id();

                    if (std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id2) == detector_id_analyze->end()) continue; //not in vector of dets to analyze
                    
                    double energy2 = hit2->Get_energy();

                    if (energy2 == 0) energy2 = slow_ToT2;

                    
                    if (!(TMath::Abs(fast_lead1 - fast_lead2) < 1000)) continue; //require coincidence!
                    //if (!(detector_id1>=0 && detector_id1<=3 && detector_id2>=0 && detector_id2<=3)) continue; // only these are calibrated.

                    if (detector_id2>detector_id1 && TMath::Abs(energy1 - E1)<Egatewidth && TMath::Abs(energy2 - E2)<Egatewidth){
                        int index1 = std::distance(detector_id_analyze->begin(), std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id1));
                        int index2 = std::distance(detector_id_analyze->begin(), std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id2));
                        h_energy_E1_E2_dt[index1][index2]->Fill(fast_lead2-fast_lead1);

                    }else if (detector_id1>detector_id2 && TMath::Abs(energy2 - E2)<Egatewidth && TMath::Abs(energy1 - E1)<Egatewidth){
                        int index1 = std::distance(detector_id_analyze->begin(), std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id2));
                        int index2 = std::distance(detector_id_analyze->begin(), std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id1));
                        h_energy_E1_E2_dt[index1][index2]->Fill(fast_lead1-fast_lead2);
                    }
                }
            }
        }
    }
    fNEvents += 1;
}



void FatimaTimingAnalysis::FinishEvent()
{
    if (fHitFatimaTwinpeaks)
    {
        fHitFatimaTwinpeaks->Clear();
    }
}

void FatimaTimingAnalysis::FinishTask()
{

    TFile * outfile = mgr->GetOutFile();
    if (!outfile->Get("h_slow_ToT_vs_detector_id")) h_slow_ToT_vs_detector_id->Write("h_slow_ToT_vs_detector_id",TObject::kOverwrite);
    if (!outfile->Get("h_energy_vs_detector_id")) h_energy_vs_detector_id->Write("h_energy_vs_detector_id",TObject::kOverwrite);
    if (!outfile->Get("h_energy_energy")) h_energy_energy->Write("h_energy_energy",TObject::kOverwrite);


    //h_energy_E1_E2_dt
    for (int i = 0; i<detector_id_analyze->size(); i++){
        for (int j=i+1; j<detector_id_analyze->size(); j++){
            h_energy_E1_E2_dt[i][j]->Write(Form("h_energy_E1_%i_E2_%i_det_%i_det_%i_dt",(int)E1, (int)E2,detector_id_analyze->at(i),detector_id_analyze->at(j)),TObject::kOverwrite);
        }
    } 
}

ClassImp(FatimaTimingAnalysis)
