#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

#include "FrsFatimaCorrelations.h"
#include "EventHeader.h"
#include "c4Logger.h"



FrsFatimaCorrelations::FrsFatimaCorrelations(std::vector<TCutGGates*> fFrsGates, 
                                            TCutGGates* fFatimaPromptGates,
                                            CorrelationsMap* fCorrel)
    :   FairTask()
    ,   fHitFatimaTwinpeaksArray(new TClonesArray("FatimaTwinpeaksCalData"))
    ,   fHitFrsArray(new TClonesArray("FrsHitData"))
    ,   fNEvents(0)
    ,   header(nullptr)
{
    // Set gates - FRS
    for (auto & Gate : fFrsGates)
    {
        if (Gate->Type == "ZAoQ")
        {
            cutID_Z_AoQ = Gate->Gates;
        }
        else if (Gate->Type == "Z1Z2")
        {
            cutID_Z_Z2 = Gate->Gates;
        }
        else if (Gate->Type == "x2AoQ")
        {
            cutID_x2AoQ = Gate->Gates;
        }
        else if (Gate->Type == "x4AoQ")
        {
            cutID_x4AoQ = Gate->Gates;
        }
        else if (Gate->Type == "dEdegZ")
        {
            cutID_dEdegZ = Gate->Gates;
        }
    }

    if (fFatimaPromptGates->Type == "FatimaEdT")
    {
        cutFatima_EdT = fFatimaPromptGates->Gates;
    }

    Correl = fCorrel;
   
}

FrsFatimaCorrelations::~FrsFatimaCorrelations()
{
    c4LOG(info, "");
    if (fHitFatimaTwinpeaksArray) delete fHitFatimaTwinpeaksArray;
    if (fHitFrsArray) delete fHitFrsArray;
}


InitStatus FrsFatimaCorrelations::Init()
{
    // get branches etc
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    // FairRunOnline

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatimaTwinpeaksArray = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatimaTwinpeaksArray, "Branch FatimaTwinpeaksCalData not found!");

    fHitFrsArray = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fHitFrsArray, "FrsHitData branch not found!");

    // define folders
    // get FRS correlations folder..
    folder_correlations = (TFolder*)mgr->GetObject("Correlations");
    if (!folder_correlations) folder_correlations = new TFolder("Correlations", "Correlations");

    folder_frs_fatima_corr = new TFolder("FRS-Fatima Correlations", "FRS-Fatima Correlations");
    folder_correlations->Add(folder_frs_fatima_corr);
    folder_frs_fatima_corr_ZAoQgated = new TFolder("ZAoQ Gated", "ZAoQ Gated");
    folder_frs_fatima_corr_Z1Z2x2AoQgated = new TFolder("Z1Z2x2AoQ Gated", "Z1Z2x2AoQ Gated");
    folder_frs_fatima_corr_Z1Z2x4AoQgated = new TFolder("Z1Z2x4AoQ Gated", "Z1Z2x4AoQ Gated");
    folder_frs_fatima_corr->Add(folder_frs_fatima_corr_ZAoQgated);
    folder_frs_fatima_corr->Add(folder_frs_fatima_corr_Z1Z2x2AoQgated);
    folder_frs_fatima_corr->Add(folder_frs_fatima_corr_Z1Z2x4AoQgated);

    // define histograms and canvases etc
    //hA_FRS_Fat_LT1_start_stop
    h1_FRS_Fatima_LT1_start_stop = new TH1D("h1_FRS_Fatima_LT1_start_stop", "FRS-Fatima Start-Stop Lifetime 1", 20000, -10000, 10000);
    folder_frs_fatima_corr->Add(h1_FRS_Fatima_LT1_start_stop);
    //hA_FRS_Fat_LT1_start_stop_ns
    h1_FRS_Fatima_LT1_start_stop_ns = new TH1D("h1_FRS_Fatima_LT1_start_stop_ns", "FRS-Fatima Start-Stop Lifetime 1 ns", 1000, -50, 50);
    folder_frs_fatima_corr->Add(h1_FRS_Fatima_LT1_start_stop_ns);
    //hA_FRS_Fat_LT2_start_stop
    h1_FRS_Fatima_LT2_start_stop = new TH1D("h1_FRS_Fatima_LT2_start_stop", "FRS-Fatima Start-Stop Lifetime 2", 20000, -10000, 10000);
    folder_frs_fatima_corr->Add(h1_FRS_Fatima_LT2_start_stop);
    //hA_FRS_Fat_LT2_start_stop_ns
    h1_FRS_Fatima_LT2_start_stop_ns = new TH1D("h1_FRS_Fatima_LT2_start_stop_ns", "FRS-Fatima Start-Stop Lifetime 2 ns", 1000, -50, 50);
    folder_frs_fatima_corr->Add(h1_FRS_Fatima_LT2_start_stop_ns);
    //hA_FRS_Fat_LT3_start_stop
    h1_FRS_Fatima_LT3_start_stop = new TH1D("h1_FRS_Fatima_LT3_start_stop", "FRS-Fatima Start-Stop Lifetime 3", 20000, -10000, 10000);
    folder_frs_fatima_corr->Add(h1_FRS_Fatima_LT3_start_stop);
    // hA_FRS_Fat_LT3_start_stop_ns
    h1_FRS_Fatima_LT3_start_stop_ns = new TH1D("h1_FRS_Fatima_LT3_start_stop_ns", "FRS-Fatima Start-Stop Lifetime 3 ns", 1000, -50, 50);
    folder_frs_fatima_corr->Add(h1_FRS_Fatima_LT3_start_stop_ns);
    //hA_FRS_Fat_LT1_stop_start
    h1_FRS_Fatima_LT1_stop_start = new TH1D("h1_FRS_Fatima_LT1_stop_start", "FRS-Fatima Stop-Start Lifetime 1", 20000, -10000, 10000);
    folder_frs_fatima_corr->Add(h1_FRS_Fatima_LT1_stop_start);
    //hA_FRS_Fat_LT1_stop_start_ns
    h1_FRS_Fatima_LT1_stop_start_ns = new TH1D("h1_FRS_Fatima_LT1_stop_start_ns", "FRS-Fatima Stop-Start Lifetime 1 ns", 1000, -50, 50);
    folder_frs_fatima_corr->Add(h1_FRS_Fatima_LT1_stop_start_ns);
    //hA_FRS_Fat_LT2_stop_start
    h1_FRS_Fatima_LT2_stop_start = new TH1D("h1_FRS_Fatima_LT2_stop_start", "FRS-Fatima Stop-Start Lifetime 2", 20000, -10000, 10000);
    folder_frs_fatima_corr->Add(h1_FRS_Fatima_LT2_stop_start);
    //hA_FRS_Fat_LT2_stop_start_ns
    h1_FRS_Fatima_LT2_stop_start_ns = new TH1D("h1_FRS_Fatima_LT2_stop_start_ns", "FRS-Fatima Stop-Start Lifetime 2 ns", 1000, -50, 50);
    folder_frs_fatima_corr->Add(h1_FRS_Fatima_LT2_stop_start_ns);
    //hA_FRS_Fat_LT3_stop_start
    h1_FRS_Fatima_LT3_stop_start = new TH1D("h1_FRS_Fatima_LT3_stop_start", "FRS-Fatima Stop-Start Lifetime 3", 20000, -10000, 10000);
    folder_frs_fatima_corr->Add(h1_FRS_Fatima_LT3_stop_start);
    //hA_FRS_Fat_LT3_stop_start_ns
    h1_FRS_Fatima_LT3_stop_start_ns = new TH1D("h1_FRS_Fatima_LT3_stop_start_ns", "FRS-Fatima Stop-Start Lifetime 3 ns", 1000, -50, 50);
    folder_frs_fatima_corr->Add(h1_FRS_Fatima_LT3_stop_start_ns);

    if (cutID_Z_AoQ[0] != nullptr)
    {
        for (int gate = 0; gate < cutID_Z_AoQ.size(); gate++)
        {
            //hA_FRS_ZAoQ_FatE[i]
            h1_FRS_FatimaE_ZAoQgate.emplace_back(new TH1F(Form("h1_FRS_FatimaE_ZAoQgate%d", gate), Form("Fatima Energy, FRS ZAoQ Gate: %d ", gate), 2000, 0, 2000));
            folder_frs_fatima_corr_ZAoQgated->Add(h1_FRS_FatimaE_ZAoQgate[gate]);
            //hA_FRS_ZAoQ_FatEvsT[i]
            h2_FRS_FatimaEvsT_ZAoQgate.emplace_back(new TH2D(Form("h2_FRS_FatimaEvsT_ZAoQgate%d", gate), Form("T Diff Fatima T - SC41 vs Fatima Energy, ZAoQ Gate: %d", gate), 2100, -10000, 20000, 1250, 0, 2500));
            folder_frs_fatima_corr_ZAoQgated->Add(h2_FRS_FatimaEvsT_ZAoQgate[gate]);
            //hA_FRS_ZAoQ_FatE1vsE2[i]
            h2_FRS_FatimaE1vsE2_ZAoQgate.emplace_back(new TH2D(Form("h2_FRS_FatimaE1vsE2_ZAoQgate%d", gate), Form("Fatima Energy 1 vs Energy 2, ZAoQ Gate: %d", gate), 2000, 0, 2000, 2000, 0, 2000));
            folder_frs_fatima_corr_ZAoQgated->Add(h2_FRS_FatimaE1vsE2_ZAoQgate[gate]);
        }
    }

    if (cutID_Z_Z2[0] != nullptr)
    {
        for (int gate = 0; gate < cutID_Z_Z2.size(); gate++)
        {
            if (cutID_x2AoQ[0] != nullptr)
            {
                //hA_FRS_Z1Z2_X2AoQ_FatE[i]
                h1_FRS_FatimaE_Z1Z2x2AoQgate.emplace_back(new TH1F(Form("h1_FRS_FatimaE_Z1Z2x2AoQgate%d", gate), Form("Fatima Energy, Z1Z2 and x2AoQ Gate: %d", gate), 2000, 0, 2000));
                folder_frs_fatima_corr_Z1Z2x2AoQgated->Add(h1_FRS_FatimaE_Z1Z2x2AoQgate[gate]);
                //hA_FRS_Z1Z2_X2AoQ_FatEvsT[i]
                h2_FRS_FatimaEvsT_Z1Z2x2AoQgate.emplace_back(new TH2D(Form("h2_FRS_FatimaEvsT_Z1Z2x2AoQgate%d", gate), Form("T Diff Fatima T - SC41 vs Fatima Energy, Z1Z2 and x2AoQ Gate: %d", gate), 2750, -500, 5000, 2000, 0, 2000));
                folder_frs_fatima_corr_Z1Z2x2AoQgated->Add(h2_FRS_FatimaEvsT_Z1Z2x2AoQgate[gate]);
                //hA_FRS_Z1Z2_X2AoQ_FatE1vsE2[i]
                h2_FRS_FatimaE1vsE2_Z1Z2x2AoQgate.emplace_back(new TH2D(Form("h2_FRS_FatimaE1vsE2_Z1Z2x2AoQgate%d", gate), Form("Fatima Energy 1 vs Energy 2, Z1Z2 and x2AoQ Gate: %d", gate), 2000, 0, 2000, 2000, 0, 2000));
                folder_frs_fatima_corr_Z1Z2x2AoQgated->Add(h2_FRS_FatimaE1vsE2_Z1Z2x2AoQgate[gate]);
            }

            if (cutID_x4AoQ[0] != nullptr)
            {
                //hA_FRS_Z1Z2_X4AoQ_FatE[i]
                h1_FRS_FatimaE_Z1Z2x4AoQgate.emplace_back(new TH1F(Form("h1_FRS_FatimaE_Z1Z2x4AoQgate%d", gate), Form("Fatima Energy, Z1Z2 and x4AoQ Gate: %d", gate), 2000, 0, 2000));
                folder_frs_fatima_corr_Z1Z2x4AoQgated->Add(h1_FRS_FatimaE_Z1Z2x4AoQgate[gate]);
                //hA_FRS_Z1Z2_X4AoQ_FatEvsT[i]
                h2_FRS_FatimaEvsT_Z1Z2x4AoQgate.emplace_back(new TH2D(Form("h2_FRS_FatimaEvsT_Z1Z2x4AoQgate%d", gate), Form("T Diff Fatima T - SC41 vs Fatima Energy, Z1Z2 and x4AoQ Gate: %d", gate), 2750, -500, 5000, 2000, 0, 2000));
                folder_frs_fatima_corr_Z1Z2x4AoQgated->Add(h2_FRS_FatimaEvsT_Z1Z2x4AoQgate[gate]);
                //hA_FRS_Z1Z2_X4AoQ_FatE1vsE2[i]
                h2_FRS_FatimaE1vsE2_Z1Z2x4AoQgate.emplace_back(new TH2D(Form("h2_FRS_FatimaE1vsE2_Z1Z2x4AoQgate%d", gate), Form("Fatima Energy 1 vs Energy 2, Z1Z2 and x4AoQ Gate: %d", gate), 2000, 0, 2000, 2000, 0, 2000));
                folder_frs_fatima_corr_Z1Z2x4AoQgated->Add(h2_FRS_FatimaE1vsE2_Z1Z2x4AoQgate[gate]);
            }
        }
    }

    // simply read in prompt cut like FrsGates

    return kSUCCESS;

}


void FrsFatimaCorrelations::Exec(Option_t* option)
{
    // -------------------------------------------------- //
    // ------- PROMPT ----------------------------------- //

    // stop-start does in fact require an FRS hit
    // so we can rewrite this a bit
    int multFRS = fHitFrsArray->GetEntriesFast(); 
    if (multFRS == 0) return;
    
    FrsHitData* FrsHit = (FrsHitData*)fHitFrsArray->At(0);
    if (!FrsHit) return;

    if (fHitFatimaTwinpeaksArray && fHitFatimaTwinpeaksArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitFatimaTwinpeaksArray->GetEntriesFast();

        // CEJ: we need some way to get (if any) the SC41L hit time
        // and we can't do anything if this doesn't exist or the time is <= 0
        // I think this should be done earlier personally..
        Float_t SC41L_T = 0;
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FatimaTwinpeaksCalData* FatimaHit = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaksArray->At(ihit);
            if (!FatimaHit) continue; 
            if (FatimaHit->Get_detector_id() == 18)
            {
                if (FatimaHit->Get_fast_lead_time() > 0)
                {
                    SC41L_T = FatimaHit->Get_fast_lead_time();
                    break;
                }
            }
        } // ihit loop for SC41L hits
        
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FatimaTwinpeaksCalData* FatimaHit = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaksArray->At(ihit);
            if (!FatimaHit) continue;

            // CEJ: these are hard-coded in AidaFatimaCorrelations, I don't like this
            // if (FatimaHit->Get_detector_id() > NDetectors || FatimaHit->Get_detector_id() < 0) continue;
            if (FatimaHit->Get_detector_id() == 18 || FatimaHit->Get_detector_id() == 19) continue; // veto_sc41

            // Start-Stop
            // CEJ: not done yet


            // FRS-Fatima
            Long64_t dT_FRS_Fatima = 0;
            Fatima_time_mins = 0; // used for some gainmonitor in Go4?
            if (FatimaHit->Get_wr_t() > 0) Fatima_time_mins = (FatimaHit->Get_wr_t() / 60e9) - 26900000;
            
            if (FatimaHit->Get_wr_t() > 0 && FrsHit->Get_wr_t() > 0) dT_FRS_Fatima = FatimaHit->Get_wr_t() - FrsHit->Get_wr_t();
            
            if (dT_FRS_Fatima > (*Correl)["FRS-Fatima WR Gate"][0] && dT_FRS_Fatima < (*Correl)["FRS-Fatima WR Gate"][1])
            {   
                // In Go4 sc40[0] is SC41L, sc41[0] is SC41R
                if (FatimaHit->Get_energy() > 0 && FatimaHit->Get_fast_lead_time() > 0 && SC41L_T > 0)
                {
                    if (cutFatima_EdT[0] != nullptr)
                    {
                        for (int gate = 0; gate < cutFatima_EdT.size(); gate++)
                        {
                            if (cutFatima_EdT[gate]->IsInside((FatimaHit->Get_fast_lead_time() - SC41L_T) * 0.025, FatimaHit->Get_energy()))
                            {
                                if (cutID_Z_AoQ[0] != nullptr)
                                {
                                    if (cutID_Z_AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z()))
                                    {

                                        h1_FRS_FatimaE_ZAoQgate[gate]->Fill(FatimaHit->Get_energy());
                                        h2_FRS_FatimaEvsT_ZAoQgate[gate]->Fill((FatimaHit->Get_fast_lead_time() - SC41L_T) * 0.025, FatimaHit->Get_energy());

                                        // CEJ: In Go4 this next hist is filled outside the ZAoQ test
                                        // this must be wrong?
                                        for (int ihit2 = 0; ihit2 < nHits; ihit2++)
                                        {
                                            FatimaTwinpeaksCalData* FatimaHit2 = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaksArray->At(ihit2);
                                            if (!FatimaHit2) continue;

                                            if (FatimaHit2->Get_detector_id() == 18 || FatimaHit2->Get_detector_id() == 19) continue; // veto_sc41

                                            if (ihit != ihit2 && (FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 0.025 > (*Correl)["Fatima Gamma-Gamma dT Gate"][0] && (FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 0.025 < (*Correl)["Fatima Gamma-Gamma dT Gate"][1])
                                            {
                                                h2_FRS_FatimaE1vsE2_ZAoQgate[gate]->Fill(FatimaHit->Get_energy(), FatimaHit2->Get_energy());
                                            }
                                        }

                                    } // Inside ZAoQ gate
                                    
                                }

                                if (cutID_Z_Z2[0] != nullptr)
                                { 
                                    if (cutID_x2AoQ[0] != nullptr)
                                    {
                                        if (cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()) && cutID_x2AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2()))
                                        {
                                            h1_FRS_FatimaE_Z1Z2x2AoQgate[gate]->Fill(FatimaHit->Get_energy());
                                            h2_FRS_FatimaEvsT_Z1Z2x2AoQgate[gate]->Fill((FatimaHit->Get_fast_lead_time() - SC41L_T) * 0.025, FatimaHit->Get_energy());

                                            for (int ihit2 = 0; ihit2 < nHits; ihit2++)
                                            {   
                                                FatimaTwinpeaksCalData* FatimaHit2 = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaksArray->At(ihit2);
                                                if (!FatimaHit2) continue;

                                                if (FatimaHit2->Get_detector_id() == 18 || FatimaHit2->Get_detector_id() == 19) continue; // veto_sc41

                                                if (ihit != ihit2 && (FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 0.025 > (*Correl)["Fatima Gamma-Gamma dT Gate"][0] && (FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 0.025 < (*Correl)["Fatima Gamma-Gamma dT Gate"][1])
                                                {
                                                    h2_FRS_FatimaE1vsE2_Z1Z2x2AoQgate[gate]->Fill(FatimaHit->Get_energy(), FatimaHit2->Get_energy());
                                                }
                                            }

                                        } // Inside Z1Z2 and x2AoQ

                                    }

                                    if (cutID_x4AoQ[0] != nullptr)
                                    {
                                        if (cutID_Z_Z2[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()) && cutID_x4AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4()))
                                        {
                                            h1_FRS_FatimaE_Z1Z2x4AoQgate[gate]->Fill(FatimaHit->Get_energy());
                                            h2_FRS_FatimaEvsT_Z1Z2x4AoQgate[gate]->Fill(FatimaHit->Get_fast_lead_time(), FatimaHit->Get_energy());

                                            for (int ihit2 = 0; ihit2 < nHits; ihit2++)
                                            {   
                                                FatimaTwinpeaksCalData* FatimaHit2 = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaksArray->At(ihit2);
                                                if (!FatimaHit2) continue;

                                                if (FatimaHit2->Get_detector_id() == 18 || FatimaHit2->Get_detector_id() == 19) continue; // veto_sc41

                                                if (ihit != ihit2 && (FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 0.025 > (*Correl)["Fatima Gamma-Gamma dT Gate"][0] && (FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 0.025 < (*Correl)["Fatima Gamma-Gamma dT Gate"][1])
                                                {
                                                    h2_FRS_FatimaE1vsE2_Z1Z2x4AoQgate[gate]->Fill(FatimaHit->Get_energy(), FatimaHit2->Get_energy());
                                                }
                                            }
                                        } // Inside Z1Z2 and x4AoQ
                                    }
                                }

                            } // inside prompt cut
                            
                        } // gate loop based on prompt cuts

                    } // prompt cut isn't null

                } // energy, time and sc40 check

            } // FRS-Fatima WR gate

        } // Fatima hit loop

        // Start-Stop and Stop-Start "Lifetime analysis"
        for (int ihit = 0; ihit < nHits; ihit++)
        {
            FatimaTwinpeaksCalData* FatimaHit = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaksArray->At(ihit);
            if (!FatimaHit) continue;
            // CEJ: these are hard-coded in AidaFatimaCorrelations, I don't like this
            // if (FatimaHit->Get_detector_id() > NDetectors || FatimaHit->Get_detector_id() < 0) continue;
            if (FatimaHit->Get_detector_id() == 18 || FatimaHit->Get_detector_id() == 19) continue; // veto_sc41

            Long64_t dT_FRS_Fatima = 0;            
            if (FatimaHit->Get_wr_t() > 0 && FrsHit->Get_wr_t() > 0) dT_FRS_Fatima = FatimaHit->Get_wr_t() - FrsHit->Get_wr_t();

            if (dT_FRS_Fatima > (*Correl)["FRS-Fatima WR Gate"][0] && dT_FRS_Fatima < (*Correl)["FRS-Fatima WR Gate"][1])
            {
                //if (/*we don't want to do this*/) continue;

                if (cutFatima_EdT[(*Correl)["Start-Stop Analysis PID"][0]-1] != nullptr)
                {
                    if (cutFatima_EdT[(*Correl)["Start-Stop Analysis PID"][0]-1]->IsInside((FatimaHit->Get_fast_lead_time() - SC41L_T) * 0.025, FatimaHit->Get_energy()))
                    {
                        if (cutID_Z_AoQ[(*Correl)["Start-Stop Analysis PID"][0]-1] != nullptr)
                        {
                            if (cutID_Z_AoQ[(*Correl)["Start-Stop Analysis PID"][0]-1]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z()))
                            {
                                for (Int_t ihit2 = 0; ihit2 < nHits; ihit2++)
                                {
                                    FatimaTwinpeaksCalData* FatimaHit2 = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaksArray->At(ihit2);
                                    if (!FatimaHit2) continue;

                                    if (FatimaHit2->Get_detector_id() == 18 || FatimaHit2->Get_detector_id() == 19) continue; // veto_sc41

                                    if (ihit != ihit2 && cutFatima_EdT[(*Correl)["Start-Stop Analysis PID"][0]-1]->IsInside((FatimaHit2->Get_fast_lead_time() - SC41L_T) * 0.025, FatimaHit2->Get_energy()))
                                    {
                                        // Start-Stop
                                        // 1
                                        if (FatimaHit->Get_energy() > (*Correl)["Lifetime 1 Start-Stop Energies"][0] && FatimaHit->Get_energy() < (*Correl)["Lifetime 1 Start-Stop Energies"][1] && FatimaHit2->Get_energy() > (*Correl)["Lifetime 1 Start-Stop Energies"][2] && FatimaHit2->Get_energy() < (*Correl)["Lifetime 1 Start-Stop Energies"][3])
                                        {
                                            h1_FRS_Fatima_LT1_start_stop->Fill((FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 25);
                                            h1_FRS_Fatima_LT1_start_stop_ns->Fill((FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 0.025);
                                        }
                                        // 2
                                        if (FatimaHit->Get_energy() > (*Correl)["Lifetime 2 Start-Stop Energies"][0] && FatimaHit->Get_energy() < (*Correl)["Lifetime 2 Start-Stop Energies"][1] && FatimaHit2->Get_energy() > (*Correl)["Lifetime 2 Start-Stop Energies"][2] && FatimaHit2->Get_energy() < (*Correl)["Lifetime 2 Start-Stop Energies"][3])
                                        {
                                            h1_FRS_Fatima_LT2_start_stop->Fill((FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 25);
                                            h1_FRS_Fatima_LT2_start_stop_ns->Fill((FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 0.025);
                                        }
                                        // 3
                                        if (FatimaHit->Get_energy() > (*Correl)["Lifetime 3 Start-Stop Energies"][0] && FatimaHit->Get_energy() < (*Correl)["Lifetime 3 Start-Stop Energies"][1] && FatimaHit2->Get_energy() > (*Correl)["Lifetime 3 Start-Stop Energies"][2] && FatimaHit2->Get_energy() < (*Correl)["Lifetime 3 Start-Stop Energies"][3])
                                        {
                                            h1_FRS_Fatima_LT3_start_stop->Fill((FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 25);
                                            h1_FRS_Fatima_LT3_start_stop_ns->Fill((FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 0.025);
                                        }
                                        // Stop-Start
                                        // 1
                                        if (FatimaHit->Get_energy() > (*Correl)["Lifetime 1 Start-Stop Energies"][2] && FatimaHit->Get_energy() < (*Correl)["Lifetime 1 Start-Stop Energies"][3] && FatimaHit2->Get_energy() > (*Correl)["Lifetime 1 Start-Stop Energies"][0] && FatimaHit2->Get_energy() < (*Correl)["Lifetime 1 Start-Stop Energies"][1])
                                        {
                                            h1_FRS_Fatima_LT1_stop_start->Fill((FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 25);
                                            h1_FRS_Fatima_LT1_stop_start_ns->Fill((FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 0.025);
                                        }
                                        // 2
                                        if (FatimaHit->Get_energy() > (*Correl)["Lifetime 2 Start-Stop Energies"][2] && FatimaHit->Get_energy() < (*Correl)["Lifetime 2 Start-Stop Energies"][3] && FatimaHit2->Get_energy() > (*Correl)["Lifetime 2 Start-Stop Energies"][0] && FatimaHit2->Get_energy() < (*Correl)["Lifetime 2 Start-Stop Energies"][1])
                                        {
                                            h1_FRS_Fatima_LT2_stop_start->Fill((FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 25);
                                            h1_FRS_Fatima_LT2_stop_start_ns->Fill((FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 0.025);
                                        }
                                        // 3
                                        if (FatimaHit->Get_energy() > (*Correl)["Lifetime 3 Start-Stop Energies"][2] && FatimaHit->Get_energy() < (*Correl)["Lifetime 3 Start-Stop Energies"][3] && FatimaHit2->Get_energy() > (*Correl)["Lifetime 3 Start-Stop Energies"][0] && FatimaHit2->Get_energy() < (*Correl)["Lifetime 3 Start-Stop Energies"][1])
                                        {
                                            h1_FRS_Fatima_LT3_stop_start->Fill((FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 25);
                                            h1_FRS_Fatima_LT3_stop_start_ns->Fill((FatimaHit->Get_fast_lead_time() - FatimaHit2->Get_fast_lead_time()) * 0.025);
                                        }

                                    } // ihit != ihit2 && ihit2 inside prompt cut

                                } // ihit2 loop

                            } // Inside ZAoQ gate
                        }
                    } // Inside Fatima prompt cut
                }

            } // FRS-Fatima WR gate

        } // Fatima hit loop

    } // Fatima hit exists

    // ... long Iso analysis... ?
    // CEJ: we're going to copy Go4 for now and see where it goes..

    // we can use a vector for mult anyhoo
    /*for (int i = 0; i < VME_MAX_MULT; i++)
    {
        FatE_Long[i] = 0;
        FatT_Long[i] = 0;
        FatE_Prm_Long[i] = 0;
        FatT_Prm_Long[i] = 0;
    }

    dT_frsfat_long = 0;
    dT_frsfat_prompt = 0;
    dT_FRS_Fatima_WR = 0;
    Fat_mult_long = 0;
    Fat_mult_prompt = 0;
    dT_frsfat_mult_long = 0;
    dT_frsfat_mult_prompt = 0;
    dT_FatT_long = 0;
    dT_FatT_prompt = 0;
    Fat_FirstT_long = 0;
    Fat_FirstT_prompt = 0;

    if (Fatima_WR > 0)
    {
        if (ZAoQ->Pass && FRS_WR != 0)
        {
            ts_fat = FRS_WR;//?
        }
        else // in go4 "if Fatima_WR > 0", but we already do this..
        {
            ts_fat = Fatima_WR;
        }
    }

    // reset the local variabls in case the time is too long
    if (tag_fat_all.size() > 0)
    {
        for (int i = 0; i < tag_fat_all.size(); i++)
        {
            // the reset time windows are set in config/correlations
            if ((ts_fat - ts_fat_all.at(i) > (*Correl)["FRS-Fatima Long dT Gate"][1]))
            {
                tag_fat_all.erase(tag_fat_all.begin() + i);
                ts_fat_all.erase(ts_fat_all.begin() + i);
            }
        }
    }

    if (FRS_WR > 0 && ZAoQ->Pass)
    {
        if (tag_fat_all.size() == 0)
        {
            tag_fat_all.push_back(1);
            ts_fat_all.push_back(ts_fat);
        }
    }
    else if (Fatima_WR > 0)
    {
        for (int i = (tag_fat_all.size() - 1); i >= 0; i--)
        {
            // frs-gamma long correlations
            if (tag_fat_all.at(i) == 1 && (ts_fat - ts_fat_all.at(i)) > (*Correl)["FRS-Fatima Long dT Gate"][0])
            {
                dT_frsfat_long = ts_fat - ts_fat_all.at(i);
                
                for (int j = 0; j < Fatmult; j++)
                {
                    if (FatimaHit->Get_energy() > 0)
                    {
                        FatE_Long[Fat_mult_long] = FatimaHit->Get_energy();
                        FatT_Long[Fat_mult_long] = FatimaHit->Get_fast_lead_time();

                        Fat_mult_long++;
                    }

                    if (FatimaHit->Get_energy() > 0 && dT_frsfat_long > 0)
                    {
                        if (j == 0)
                        {
                            Fat_FirstT_Long = FatimaHit->Get_fast_lead_time();

                            hA_FRS_PID_FatE_LongIso->Fill(FatimaHit->Get_energy());
                            hA_FRS_FatEvsT_LongIsoGated->Fill(dT_frsfat_long / (*Correl)["FRS-Fatima Long dT Scale"][0], FatimaHit->Get_energy());
                        }

                        // this is for when there is more than 1 gamma in an event to get the correct time
                        if (j > 0 && FatimaHit->Get_fast_lead_time())
                        {
                            dT_FatT_long = (FatimaHit->Get_fast_lead_time() - Fat_FirstT_long);
                            dT_frsfat_mult_long = dT_frsfat_long + ABS(dT_FatT_long);

                            if (FatimaHit->Get_energy() > 10 && dT_frsfat_mult_long > 0)
                            {
                                hA_FRS_FatEvsT_LongIsoGated->Fill(dT_frsfat_mult_long / (*Correl)["FRS-Fatima Long dT Scale"][0], FatimaHit->Get_energy());
                                hA_FRS_PID_FatE_LongIso->Fill(FatimaHit->Get_energy());
                            }
                        }

                    }
                }

                // Gamma-Gamma
                for (int m = 0; m < Fat_mult_long; m++)
                {
                    for (int n = 0; n < Fat_mult_long; n++)
                    {
                        if (m == n) continue;
                        if ((FatT_Long[m] - FatT_Long[n]) * 0.025 > (*Correl)["Gamma-Gamma Fatima..."][0] && (FatT_Long[m] - FatT_Long[n]) * 0.025 < (*Correl)["Gamma-Gamma Fatima...."][1])
                        {
                            hA_FRS_FatE1vsFatE2_LongIsoGated->Fill(FatE_Long[m], FatE_Long[n]);
                        }
                    }
                }


            }
        }
    }

    // include prompt gammas in long isomer analysis
    if ((*Correl)["FRS-Fatima Long Include Prompt"][0])
    {
        dT_frsfat_prompt = 0;
        
        if (FRS_WR > 0 && Fatim_WR > 0) dT_FRS_Fatima_WR = Fatima_WR - FRS_WR;

        if (dT_FRS_Fatima_WR > (*Correl)["FRS-Fatima WR Gate"][0] && dT_FRS_Fatima_WR < (*Correl)["FRS-Fatima WR Gate"][1])
        {
            if (ZAoQ->Pass)
            {
                for (int i = 0; i < Fatmult; i++)
                {
                    dT_frsfat_prompt = ((FatimaHit->Get_fast_lead_time() - SC41L_T) * 0.025);

                    if (FatimaHit->Get_energy() > 0)
                    {
                        FatE_Prm_Long[Fat_mult_prompt] = FatimaHit->Get_energy();
                        FatT_Prm_Long[Fat_mult_prompt] = FatimaHit->Get_fast_lead_time();

                        Fat_mult_prompt++;
                    }

                    // Cut the prompt flash
                    if (cutFatima_EdT[(*Correl)["Something PID"][0]]->IsInside((FatimaHit->Get_fast_lead_time() - SC41L_T) * 0.025, FatimaHit->Get_energy()))
                    {
                        if (i == 0)
                        {
                            Fat_FirstT_prompt = FatimaHit->Get_fast_lead_time();

                            if (FatimaHit->Get_energy() > 1)
                            {
                                hA_FRS_PID_FatE_LongIso->Fill(FatimaHit->Get_energy());
                                hA_FRS_FatEvsT_LongIsoGated->Fill(dT_frsfat_prompt / (*Correl)["FRS-Fatima Long dT Scale"][0], FatimaHit->Get_energy());
                            }
                        }

                        if (i > 0 && FatimaHit->Get_fast_lead_time())
                        {
                            dT_FatT_prompt = (FatimaHit->Get_fast_lead_time() - Fat_FirstT_prompt);

                            dT_frsfat_mult_prompt = (FatimaHit->FatimaWR - FRS_WR) + ABS(dT_FatT_prompt);

                            hA_FRS_PID_FatE_LongIso->Fill(FatimaHit->Get_energy());

                            if (dT_frsfat_mult_prompt != 0)
                            {
                                hA_FRS_FatEvsT_LongIsoGated->Fill(dT_frsfat_mult_prompt / (*Correl)["Scale"][0], FatimaHit->Get_energy());
                            }
                        }
                    }
                }
            }

            // Gamma-Gamma
            for (int m = 0; m < Fat_mult_prompt; m++)
            {
                for (int n = 0; n < Fat_mult_prompt; n++)
                {
                    if (FatE_Prm_Long[m] > 0 && FatE_Prm_Long[n] > 0)
                    {
                        if (m == n) continue;

                        if ((FatT_Prm_Long[m] - FatT_Prm_Long[n]) > (*Correl)["Gamma-Gamma timing"][0] && (FatT_Prm_Long[m] - FatT_Prm_Long[n]) < (*Correl)["Gamma-Gamma etc"][1])
                        {
                            if (cutFatima_EdT[(*Correl)["PID of some kind"][0]]->IsInside(dT_frsfat_prompt, FatE_Prm_Long[m]) && cutFatima_EdT[(*Correl)["PID of some kind"][0]]->IsInside(dT_frsfat_prompt, FatE_Prm_Long[n]))
                            {
                                if (ZAoQ->Pass) hA_FRS_FatE1vsFatE2_LongIsoGated->Fill(FatE_Prm_Long[m], FatE_Prm_Long[n]);
                            }
                        }
                    }
                }
            }
        }
    }*/

}


void FrsFatimaCorrelations::FinishEvent()
{

}

void FrsFatimaCorrelations::FinishTask()
{
    c4LOG(info, "");
    //if (fHitFatimaTwinpeaksArray && fHitFrsArray) folder_frs_fatima_corr->Write();
    folder_correlations->Write();
}


ClassImp(FrsFatimaCorrelations)