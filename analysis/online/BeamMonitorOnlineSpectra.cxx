// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "BeamMonitorOnlineSpectra.h"
#include "EventHeader.h"
#include "BeamMonitorData.h"
#include "c4Logger.h"


#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

#define DEBUG_MODE 0
#define S4_MAX_TDIFFS 100000
#define S4_nAna 3000
#define S4_tMax 10000
#define S4_tLimit pow(10,6)
#define S4_MaxTimeDiff 100000

BeamMonitorOnlineSpectra::BeamMonitorOnlineSpectra()
{
}

BeamMonitorOnlineSpectra::BeamMonitorOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitBM(NULL)
    , fNEvents(0)
    , header(nullptr)
    // ranges
{
}

BeamMonitorOnlineSpectra::~BeamMonitorOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitBM)
        delete fHitBM;
}

void BeamMonitorOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus BeamMonitorOnlineSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitBM = (TClonesArray*)mgr->GetObject("BeamMonitorData");
    c4LOG_IF(fatal, !fHitBM, "Branch BeamMonitorData not found!");

    // Create histograms
    TString Name1;
    TString Name2;

    Name1 = "fh1_S4tdiff";
    Name2 = "Beam Monitor: t diffs";

    cS4tdiff = new TCanvas("cS4tdiff","t diffs",10, 10, 800, 700);
    fh1_S4tdiff = new TH1F("fh1_S4tdiff","t diff", 1000, 0, 1e5);
    fh1_S4tdiff->Draw("");

    ct1 = new TCanvas("ct1","t diffs",10,10,800,700);
    hbm_s4h_t1 = new TH1F("hbm_s4h_t1", "S4 Hit Time [ms]: bins are 100us wide", 100000, 0, 10000);
    hbm_s4h_t1->Draw("");

    // this one was a "Graph" in GO4 for online analysis
    cQF = new TCanvas("cQF","t diffs",10,10,800,700);
    fh1_S4_QF = new TH1F("fh1_S4_QF", "Quality Factor", 100,0,100);
    fh1_S4_QF->Draw("");

    cNormDiff = new TCanvas("cNormDiff","t diffs",10,10,800,700);
    hBM_s4h_norm_tdiff = new TH1F("hBM_s4h_norm_tdiff", "S4 Normalized Hit Time Difference [100ns]", 10000, 0, 10000);
    hBM_s4h_norm_tdiff->Draw("");

    cPoisson = new TCanvas("cPoisson","t diffs",10,10,800,700);
    hBM_s4h_poisson =  new TH1F("hBM_s4h_poisson", "S4 Poisson", 10000, 0, 10000);
    hBM_s4h_poisson->Draw("");

    cCum = new TCanvas("cCum","t diffs",10,10,800,700);
    hBM_s4h_c = new TH1F("hBM_s4h_c", "S4 Cumulative Hit Times [100ns]", 10000, 0, 10000);
    hBM_s4h_c->Draw("");

    cCumPoisson = new TCanvas("cCumPoisson","t diffs",10,10,800,700);
    hBM_s4h_cp = new TH1F("hBM_s4h_cp", "S4 Cumulative Poisson [100ns]", 10000, 0, 10000);
    hBM_s4h_cp->Draw("");

    cDev = new TCanvas("cDev","t diffs",10,10,800,700);
    hBM_s4h_dc = new TH1F("hBM_s4h_dc", "S4 Deviation of Cumulative Hit Times [100ns]", 10000, 0, 10000);
    hBM_s4h_dc->Draw("");

    TFolder *bmFold = new TFolder("BeamMonitor", "Beam Monitor");
    bmFold->Add(cS4tdiff);
    bmFold->Add(ct1);
    bmFold->Add(cQF);
    bmFold->Add(cNormDiff);
    bmFold->Add(cPoisson);
    bmFold->Add(cCum);
    bmFold->Add(cCumPoisson);
    bmFold->Add(cDev);


    run->AddObject(bmFold);

    run->GetHttpServer()->RegisterCommand("Reset_BM_Histos", Form("/Objects/%s/->Reset_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Reset_BM_Histos", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void BeamMonitorOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    fh1_S4tdiff->Reset();
    hbm_s4h_t1->Reset();
    fh1_S4_QF->Reset();
    hBM_s4h_c->Reset();
    hBM_s4h_cp->Reset();
    hBM_s4h_dc->Reset();
    hBM_s4h_poisson->Reset();
    hBM_s4h_norm_tdiff->Reset();

}

// change as needed depending on changes
void BeamMonitorOnlineSpectra::Snapshot_Histo()
{
    //date and time stamp folder
    time_t now = time(0);
    tm *ltm = localtime(&now);
    const char* snapshot_dir = Form("BeamMonitor_Snapshot_%d-%d-%d_%d-%d-%d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    gSystem->mkdir(snapshot_dir);
    gSystem->cd(snapshot_dir);

    cS4tdiff->SaveAs("cS4tdiff.png");
    ct1->SaveAs("ct1.png");
    cQF->SaveAs("cQF.png");
    cNormDiff->SaveAs("cNormDiff.png");
    cPoisson->SaveAs("cPoisson.png");
    cCum->SaveAs("cCum.png");
    cCumPoisson->SaveAs("cCumPoisson.png");
    cDev->SaveAs("cDev.png");

    gSystem->cd("..");
    c4LOG(info, "Snapshot saved to:" << snapshot_dir);

}

void BeamMonitorOnlineSpectra::Exec(Option_t* option)
{   

    UInt_t S4count = 0;
    UInt_t S4hits[S4_MAX_TDIFFS]; // is this right?
    
    if (fHitBM && fHitBM->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitBM->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            BeamMonitorData* hit = (BeamMonitorData*)fHitBM->At(ihit);
            if (!hit)
                continue;

            S4hits[S4count] = hit->GetS4Data() / 10; // change units fro [10ns] to [100ns] for analysis
            fh1_S4tdiff->Fill(S4hits[S4count]); // change units fro [10ns] to [100ns] for analysis
            S4count++;

            // this would reset the count to 1?
            if (S4count > S4_MAX_TDIFFS)
            {
                S4count = S4count % S4_MAX_TDIFFS;
            }

            if (S4count % S4_nAna == 0) // analysis every n counts
            {

                if (DEBUG_MODE) std::cout << "we reached this point so we should fill more histograms!\r" << std::flush;
                UInt_t S4_tsum = 0; // timesum
                UInt_t S4_rhits = 0; // relevant hits
                UInt_t S4_sumDiffs = 0;
                Double_t S4_countRate = 0.;
                Double_t S4_tDiff_int = 0.;
                
                for (Int_t k = 0; k < S4_MAX_TDIFFS; k++)
                {
                    if ((Double_t) S4_sumDiffs < (Double_t) S4_tMax * pow(10,5))
                    {
                        S4_sumDiffs += S4hits[(S4count + k) % S4_MAX_TDIFFS];
                        hbm_s4h_t1->Fill((Double_t) S4_sumDiffs * pow(10, -5));
                    }
                    else
                    {
                        hbm_s4h_t1->Reset("ICESM");
                        S4_sumDiffs = 0;
                    }

                    if (S4hits[k] < S4_tLimit)
                    {
                        S4_tsum += S4hits[k];
                        S4_rhits++;
                    }
                }
                
                S4_countRate = (Double_t) S4_rhits / S4_tsum;
                S4_tDiff_int = fh1_S4tdiff->Integral(0, S4_MaxTimeDiff);

                for (Int_t j = 0; j < S4_MAX_TDIFFS; j++)
                {
                    hBM_s4h_norm_tdiff->SetBinContent(j, fh1_S4tdiff->GetBinContent(j) / S4_tDiff_int);
                    hBM_s4h_poisson->SetBinContent(j, exp(-S4_countRate*((Double_t) j)) - exp(-S4_countRate * ((Double_t) j + 1))); // get theoretical tdiffs from S4_CountRate

                    // cumulative histograms for measured, theoretical and their difference
                    if (j == 0)
                    {
                        hBM_s4h_c->SetBinContent(j, 0);
					    hBM_s4h_cp->SetBinContent(j, 0);
                    }
                    else
                    {
                        hBM_s4h_c->SetBinContent(j, hBM_s4h_c->GetBinContent(j - 1) + hBM_s4h_norm_tdiff->GetBinContent(j));
					    hBM_s4h_cp->SetBinContent(j, hBM_s4h_cp->GetBinContent(j - 1) + hBM_s4h_poisson->GetBinContent(j));
                    }
                    hBM_s4h_dc->SetBinContent(j, hBM_s4h_cp->GetBinContent(j) - hBM_s4h_c->GetBinContent(j));
                }

                
                //UInt_t S4_dc_MinBin = hBM_s4h_dc->GetMinimumBin();
			    //UInt_t S4_dc_MinValue = hBM_s4h_dc->GetBinContent(S4_dc_MinBin);
			    Double_t S4_tMean =  hBM_s4h_norm_tdiff->GetMean();

                // compute quality factor
			    Double_t S4_QF = 100.0 * (1.0 - (hBM_s4h_norm_tdiff->Integral(0, (Int_t) S4_tMean) / hBM_s4h_poisson->Integral(0, (Int_t) S4_tMean)));

                // get local time
			    time_t rawtime;
			    time(&rawtime);

                fh1_S4_QF->Fill(S4_QF);
			
			    // add point to graphs
			    /*gBM_s4gr_qf->TGraph::SetPoint(S4_QFcount, rawtime, S4_QF);
			    gBM_s4gr_dcmin->TGraph::SetPoint(S4_QFcount, rawtime, S4_dc_MinValue);
			    gBM_s4gr_dctime->TGraph::SetPoint(S4_QFcount, rawtime, S4_dc_MinBin/10);
			    gBM_s4gr_dt_avrg->TGraph::SetPoint(S4_QFcount, rawtime, (Double_t) BM_tMean/10.);*/
			    //S4_QFcount++;

            }

        }
    }

    fNEvents += 1;
}

void BeamMonitorOnlineSpectra::FinishEvent()
{
    if (fHitBM)
    {
        fHitBM->Clear();
    }
}

void BeamMonitorOnlineSpectra::FinishTask()
{
    if (fHitBM)
    {
        cS4tdiff->Write();
        ct1->Write();
        cQF->Write();
        cNormDiff->Write();
        cPoisson->Write();
        cCum->Write();
        cCumPoisson->Write();
        cDev->Write(); 
    }
}

ClassImp(BeamMonitorOnlineSpectra)