// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

// c4
#include "FatimaTimingAnalysisSummed.h"
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


FatimaTimingAnalysisSummed::FatimaTimingAnalysisSummed() : FatimaTimingAnalysisSummed("FatimaTimingAnalysisSummed")
{
    fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
}

FatimaTimingAnalysisSummed::FatimaTimingAnalysisSummed(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatima(nullptr)
    , fNEvents(0)
    , header(nullptr)
{
    fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
}

FatimaTimingAnalysisSummed::~FatimaTimingAnalysisSummed()
{
    c4LOG(info, "");
    if (fHitFatima)
        delete fHitFatima;
}

void FatimaTimingAnalysisSummed::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}




InitStatus FatimaTimingAnalysisSummed::Init()
{

    // number of crystals, number of dets 

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatima = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatima, "Branch FatimaTwinpeaksCalData not found!");


    TDirectory* tmp = gDirectory;

    // Access the output file via FairRootManager
    TFile* outFile = FairRootManager::Instance()->GetOutFile();
    outFile->cd();

    // Check if the directory exists
    dir_fatima = outFile->GetDirectory("FatimaTimingAnalysisSummed");
    if (!dir_fatima) {
        // Create the directory if it doesn't exist
        dir_fatima = outFile->mkdir("FatimaTimingAnalysisSummed");
        c4LOG(info, "Created directory FatimaTimingAnalysisSummed");
    } else {
        c4LOG(info, "Directory FatimaTimingAnalysisSummed already exists");
    }

    // Change to the new directory
    dir_fatima->cd();    

    //h_energy_E1_E2_dt
    //E2 stop
    //E1 start
    h_energy_E1_E2_dt =  new TH1F(Form("h_E1_%i_E2_%i_dt_times",(int)E1, (int)E2),Form("E1 = %f, E2 = %f, t2 - t1;dt (ns)",E1,E2),Nbins,lowBin,highBin);
    dir_fatima->Add(h_energy_E1_E2_dt);
    

    h_energy_E1_dt_vs_E = new TH2F(Form("h_E1_%i_E2_%i_dt_E_vs_dt",(int)E1,(int)E2),Form("E1 = %f, E2 = x vs t2 - t1 = y;energy in det 2 (keV);dt = t2-t1 (ns)",E1),fenergy_nbins,fenergy_bin_low, fenergy_bin_high,Nbins,lowBin,highBin);
    dir_fatima->Add(h_energy_E1_dt_vs_E);
    

    return kSUCCESS;
    
}


void FatimaTimingAnalysisSummed::Exec(Option_t* option)
{   
    if (fHitFatima && fHitFatima->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitFatima->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            FatimaTwinpeaksCalData* hit1 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit);

            if (!hit1) continue;

            double slow_ToT1 = hit1->Get_slow_ToT();
            uint16_t detector_id1 = hit1->Get_detector_id();
            double energy1 = hit1->Get_energy();
            double fast_lead_time1 = hit1->Get_fast_lead_time();
            double fast_lead_epoch1 = hit1->Get_fast_lead_epoch();

            if (fatima_configuration->IsDetectorAuxilliary(detector_id1) == true) continue; //not in vector of dets to analyze
            
            if (energy1 == 0) energy1 = slow_ToT1;
            
                            
            if (nHits>=2){ 
                for (size_t ihit2 = ihit+1; ihit2 < nHits; ihit2++) {
                    FatimaTwinpeaksCalData* hit2 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit2);
                    double slow_ToT2 = hit2->Get_slow_ToT();
                    uint16_t detector_id2 = hit2->Get_detector_id();
                    double energy2 = hit2->Get_energy();
                    double fast_lead_time2 = hit2->Get_fast_lead_time();
                    double fast_lead_epoch2 = hit2->Get_fast_lead_epoch();

                    if (fatima_configuration->IsDetectorAuxilliary(detector_id2) == true) continue; //not in vector of dets to analyze
                    

                    if (energy2 == 0) energy2 = slow_ToT2;

                    double dt = fast_lead_time1 - fast_lead_time2 + (fast_lead_epoch1 - fast_lead_epoch2);
                    
                    if (!(TMath::Abs(dt) < 1000)) continue; //require coincidence!

                    double timeshift_to_apply = 0;
                    if (detector_id2>detector_id1 && TMath::Abs(energy1 - E1)<Egatewidth){                        
                        timeshift_to_apply =  fatima_configuration->GetTimeshiftCoefficient(detector_id1,detector_id2); //check ordering
                        h_energy_E1_dt_vs_E->Fill(energy2, - dt - timeshift_to_apply);
                        
                        
                        if (TMath::Abs(energy2 - E2)<Egatewidth){
                        // det1 is start
                        // det2 is stop
                        // det2 > det1
                        // here det1 is i and det2 is j
                        

                        h_energy_E1_E2_dt->Fill(- dt - timeshift_to_apply);
                        }
                    }else if (detector_id1>detector_id2 && TMath::Abs(energy2 - E1)<Egatewidth){
                        timeshift_to_apply =  fatima_configuration->GetTimeshiftCoefficient(detector_id2,detector_id1);
                        
                        h_energy_E1_dt_vs_E->Fill(energy1, dt - timeshift_to_apply);
                        

                        if (TMath::Abs(energy1 - E2)<Egatewidth){
                        // det2 is start
                        // det1 is stop
                        // det1 > det2
                        // here det2 is i and det1 is j
                       
                        h_energy_E1_E2_dt->Fill(dt - timeshift_to_apply);

                        } 
                    }
                }
            }
        }
    }
    fNEvents += 1;
}



void FatimaTimingAnalysisSummed::FinishEvent()
{
    if (fHitFatima)
    {
        fHitFatima->Clear();
    }
}

void FatimaTimingAnalysisSummed::FinishTask()
{

    //h_energy_E1_E2_dt
    h_energy_E1_E2_dt->Write(Form("h_E1_%i_E2_%i_dt_times",(int)E1, (int)E2),TObject::kOverwrite);
    h_energy_E1_dt_vs_E->Write(Form("h_E1_%i_E2_%i_dt_E_vs_dt",(int)E1,(int)E2),TObject::kOverwrite);
}

ClassImp(FatimaTimingAnalysisSummed)
