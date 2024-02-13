// FairRoot
#include "FairRootManager.h"
#include "FairTask.h"

// c4
#include "FrsAnalysisSpectra.h"
#include "FrsHitData.h"
#include "c4Logger.h"
#include "../../../config/frs_config.h"

// ROOT
#include "TClonesArray.h"
#include <vector>

FrsAnalysisSpectra::FrsAnalysisSpectra()
    :   FairTask()
    ,   fNEvents()
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
    ,   fFrsAnalysisArray(new TClonesArray("FrsAnalysedData"))
{
}

FrsAnalysisSpectra::FrsAnalysisSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents()
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
    ,   fFrsAnalysisArray(new TClonesArray("FrsAnalysedData"))
{

}

FrsAnalysisSpectra::~FrsAnalysisSpectra()
{
    c4LOG(info, "Deleting FrsAnalysisSpectra task.");
    if (fFrsHitArray) delete fFrsHitArray;
}

InitStatus FrsAnalysisSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    fFrsHitArray = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fFrsHitArray, "FrsHitData branch not found!");

    mgr->Register("FrsAnalysedData", "FRS Analysed Data", fFrsAnalysisArray, !fOnline);

    // clear stuff

    return kSUCCESS;

}

void FrsAnalysisSpectra::Exec(Option_t* option)
{

    if (fFrsHitArray && fFrsHitArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fFrsHitArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FrsHitData* FrsHit = (FrsHitData*)fFrsHitArray->At(ihit);
            if (!FrsHit) continue;

            /* --------  TAC and PID gates ----------- */
            if (FrsHit->Get_ID_z() > 0 && FRS_time_mins > 0) hID_Z1_vs_T->Fill(FRS_time_mins, FrsHit->Get_ID_z());

            if (FrsHit->Get_ID_AoQ() > 0 && FRS_time_mins > 0) hID_AoQ_vs_T->Fill(FRS_time_mins, FrsHit->Get_ID_AoQ());

            if (FrsHit->Get_ID_AoQ() > 0 && FrsHit->Get_ID_z() > 0) hID_Z_AoQ->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
            if (FrsHit->Get_ID_AoQ_corr() > 0 && FrsHit->Get_ID_z() > 0) hID_Z_AoQ_corr->Fill(FrsHit->Get_ID_AoQ_corr(), FrsHit->Get_ID_z());

            if (FrsHit->Get_ID_z() > 0 && FrsHit->Get_ID_z2() > 0) hID_Z_Z2->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
            if (TMath::Abs(FrsHit->Get_ID_z() - FrsHit->Get_ID_z2()) < 0.4) // CEJ: should we .config this condition?
            {
                hID_Z_AoQ_zsame->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                hID_x4AoQ_zsame->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                hID_x2AoQ_zsame->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
            }

            // CEJ: "analysis" taken from Go4 (DESPEC/FRS)
            // is stupid, we already demand the x2 condition to fill the hit.
            // this should be reconidered
            if (FrsHit->Get_ID_AoQ() > 0 && FrsHit->Get_ID_x2() > -100 && FrsHit->Get_ID_x2() < 100) hID_x2AoQ->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
            if (FrsHit->Get_ID_AoQ() > 0 && FrsHit->Get_ID_x4() > -100 && FrsHit->Get_ID_x4() < 100) hID_x4AoQ->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());

            // Charge states
            if (FrsHit->Get_ID_z() > 0 && FrsHit->Get_dEdegoQ() != 0) hdEdegoQ_Z->Fill(FrsHit->Get_ID_z(), FrsHit->Get_dEdegoQ());
            if (FrsHit->Get_ID_z() > 0 && FrsHit->Get_dEdeg() != 0) hdEdeg_Z->Fill(FrsHit->Get_ID_z(), FrsHit->Get_dEdeg());

            // Angles vs AoQ
            if (FrsHit->Get_ID_AoQ() != 0 && FrsHit->Get_ID_a2() != 0) hID_a2AoQ->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_a2());
            if (FrsHit->Get_ID_AoQ() != 0 && FrsHit->Get_ID_a4() != 0) hID_a4AoQ->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_a4());

            // Z vs Energy loss MUSIC 2
            if (FrsHit->Get_ID_z() != 0 && FrsHit->Get_music_dE()[i] != 0) hID_Z_dE2->Fill(FrsHit->Get_ID_z(), FrsHit->Get_music_dE()[1]);

            // x2 vs x4
            if (FrsHit->Get_ID_x2() != 0 && FrsHit->Get_ID_x4() != 0) hID_x2x4->Fill(FrsHit->Get_ID_x2(), FrsHit->Get_ID_x4());

            // CEJ: check sci_e index, maybe "5" is only relevant for Go4
            if (FrsHit->Get_ID_AoQ() != 0 && FrsHit->Get_sci_e()[5] != 0) hID_SC41dE_AoQ->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_sci_e()[5]);

            if (FrsHit->Get_sci_tof2() != 0 && FrsHit->Get_music_dE()[0] != 0) hID_dEToF->Fill(FrsHit->Get_sci_tof2(), FrsHit->Get_music_dE()[0]);

            if (FrsHit->Get_ID_z() != 0, FrsHit->Get_ID_x2() != 0) hID_x2z->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_x2());
            if (FrsHit->Get_ID_z() != 0, FrsHit->Get_ID_x4() != 0) hID_x4z->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_x4());

            if (FrsHit->Get_ID_x2() != 0 && FrsHit->Get_music_dE()[0] != 0) hID_E_Xs2->Fill(FrsHit->Get_ID_x2(), FrsHit->Get_music_dE()[0]);
            if (FrsHit->Get_ID_x4() != 0 && FrsHit->Get_music_dE()[0] != 0) hID_E_Xs4->Fill(FrsHit->Get_ID_x4(), FrsHit->Get_music_dE()[0]);

            if (FrsHit->Get_ID_x2() != 0 && FrsHit->Get_ID_a2() != 0) hID_x2a2->Fill(FrsHit->Get_ID_x2(), FrsHit->Get_ID_a2());
            if (FrsHit->Get_ID_y2() != 0 && FrsHit->Get_ID_b2() != 0) hID_y2b2->Fill(FrsHit->Get_ID_y2(), FrsHit->Get_ID_b2());
            if (FrsHit->Get_ID_x4() != 0 && FrsHit->Get_ID_a4() != 0) hID_x4a4->Fill(FrsHit->Get_ID_x4(), FrsHit->Get_ID_a4());
            if (FrsHit->Get_ID_y4() != 0 && FrsHit->Get_ID_b4() != 0) hID_y4b4->Fill(FrsHit->Get_ID_y4(), FrsHit->Get_ID_b4());

            // CEJ: check sci_l/r indices, same as above
            if (FrsHit->Get_ID_z() != 0 && FrsHit->Get_sci_l()[2] != 0 && fHitFrsArray->Get_sci_r()[2] != 0) hID_Z_Sc21E->Fill(FrsHit->Get_ID_z(), sqrt(FrsHit->Get_sci_l()[2] * FrsHit->Get_sci_r()[2]));

            // Define PID gates
            for (int gate = 0; gate < FRS_GATES; gate++)
            {   
                // conditions: TCutGs?
                // Z1 vs AoQ
                if (cID_Z_AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z()))
                {
                    FrsAnalysisHit->Set_ZvsAoQ_gates(gate) == true;
                    hID_ZAoQ_ZAoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                    hID_Z1Z2_ZAoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
                    hID_x2AoQ_Z1AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                    hID_x4AoQ_Z1AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                    hID_dEdegZ1_Z1AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_dEdeg());
                    hID_dEdegoQ_Z1_Z1AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_dEdegoQ());
                    hID_a2_Z1AoQgate[gate]->Fill(FrsHit->Get_ID_a2());
                    hID_a4_Z1AoQgate[gate]->Fill(FrsHit->Get_ID_a4());
                }

                // Z1 vs Z2
                if(cID_Z_Z2gate[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                {
                    FrsAnalysisHit->Set_ZvsZ2_gates(gate) = true;
                    hID_dEdegZ1_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_z(),FrsHit->Get_dEdeg());
                    hID_dEdegoQ_Z1_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_z(),FrsHit->Get_dEdegoQ());
                    hID_Z1_Z2gate[gate]->Fill(FrsHit->Get_ID_z(),FrsHit->Get_ID_z2());
                    hID_a2_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_a2());
                    hID_a4_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_a4());
                    if(FrsHit->Get_ID_AoQ() > 1 && FrsHit->Get_ID_AoQ() < 3 && FrsHit->Get_ID_x2() > -100 && FrsHit->Get_ID_x2() < 100) hID_x2AoQ_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                    if(FrsHit->Get_ID_AoQ() > 1 && FrsHit->Get_ID_AoQ() < 3 && FrsHit->Get_ID_x4() > -100 && FrsHit->Get_ID_x4() < 100) hID_x4AoQ_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                    if(FrsHit->Get_ID_AoQ() > 1 && FrsHit->Get_ID_AoQ() < 3) hID_ZAoQ_Z1Z2gate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                }

                // x2 vs AoQ
                if(cID_x2AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2()))
                {
                    FrsAnalysisHit->Set_x2vsAoQ_gates(gate) = true;
                    hID_x2AoQ_x2AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                    hID_Z1Z2_x2AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
                    
                    // Z1 Z2 + x2AoQ
                    // The selected Z1 Z2 gate for this part can be found in the Correlations_config.dat file 
                    if(cID_Z_Z2gate[1]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                    {
                        if(cID_x2AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2()))
                        {
                            hID_x2AoQ_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                            hID_x4AoQ_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                            hID_ZAoQ_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                            hID_dEdegZ1_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_dEdeg());
                            hID_dEdegoQ_Z1_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_dEdegoQ());
                            hID_a2_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_a2());
                            hID_a4_Z1Z2x2AoQgate[gate]->Fill(FrsHit->Get_ID_a4());
                        
                        }   
                    }
                }

                // x4 vs AoQ
                if(cID_x4AoQ[gate]->IsInside(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4()))
                { 
                    FrsAnalysisHit->Set_x4vsAoQ_gates(gate) = true;
                    hID_x4AoQ_x4AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                    hID_Z1Z2_x4AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
                    
                    ///Z1 Z2 + x4AoQ
                    ///The selected Z1 Z2 gate for this part can be found in the Correlations_config.dat file 
                    if(cID_Z_Z2gate[1]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2()))
                    {
                        hID_x2AoQ_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                        hID_x4AoQ_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                        hID_ZAoQ_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                        hID_dEdegZ1_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_dEdeg());
                        hID_dEdegoQ_Z1_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_dEdegoQ());
                        hID_a2_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_a2());
                        hID_a4_Z1Z2x4AoQgate[gate]->Fill(FrsHit->Get_ID_a4());
                    }
                }
                
                // GATE: Energy loss S2 vs Z (Charge states)
                if(cID_dEdegZ1[gate]->IsInside(FrsHit->Get_ID_z(), FrsHit->Get_dEdeg()))
                {
                    FrsAnalysisHit->Set_ZvsdEdeg_gates(gate) = true;
                    hID_Z1AoQ_dEdegZgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                    hID_Z1Z2_dEdegZgate[gate]->Fill(FrsHit->Get_ID_z(), FrsHit->Get_ID_z2());
                    hID_x2AoQ_dEdegZgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x2());
                    hID_x4AoQ_dEdegZgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_x4());
                    hID_a2_dEdegZgate[gate]->Fill(FrsHit->Get_ID_a2());
                    hID_a4_dEdegZgate[gate]->Fill(FrsHit->Get_ID_a4());
                
                    if(fabs(FrsHit->Get_ID_z2() - FrsHit->Get_ID_z()) < 0.4) hID_Z1AoQ_zsame_dEdegZgate[gate]->Fill(FrsHit->Get_ID_AoQ(), FrsHit->Get_ID_z());
                }
            }

            /* ----- MHTDC Histograms and PID Gates -------------------------------------------- */
            for (int i = 0; i < MAX_MHTDC_MULT; i++)
            {   
                // Z1 vs Time
                if (FrsHit->Get_ID_z_mhtdc(i) > 0 && FRS_time_mins > 0) hID_Z_mhtdc_T->Fill(FRS_time_mins, FrsHit->Get_ID_z_mhtdc(i));

                // AoQ vs Time
                if (FrsHit->Get_ID_AoQ_mhtdc(i) > 0 && FRS_time_mins > 0) hID_Z_mhtdc_T->Fill(FRS_time_mins, FrsHit->Get_ID_AoQ_mhtdc(i));

                // AoQ vs Z
                if(FrsHit->Get_ID_AoQ_mhtdc(i) > 0 && FrsHit->Get_ID_z_mhtdc(i) > 0) hID_Z_AoQ_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                if(FrsHit->Get_ID_AoQ_corr_mhtdc(i) > 0 && FrsHit->Get_ID_z_mhtdc(i) > 0) hID_Z_AoQ_corr_mhtdc->Fill(FrsHit->Get_ID_AoQ_corr_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
            
                //Z1 Z2 
                if(FrsHit->Get_ID_z_mhtdc(i) > 0 && FrsHit->Get_ID_z2_mhtdc(i) > 0) hID_Z_Z2_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
            
                if(TMath::Abs(FrsHit->Get_ID_z_mhtdc(i) - FrsHit->Get_ID_z2_mhtdc(i)) < 0.4)
                {
                    hID_Z_AoQ_zsame_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                    hID_x4AoQ_zsame_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                    hID_x2AoQ_zsame_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                }
            
                // AoQ vs X2
                if(FrsHit->Get_ID_AoQ_mhtdc(i) > 0 && FrsHit->Get_ID_x2() > -100 && FrsHit->Get_ID_x2() < 100)  hID_x2AoQ_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
            
                if(FrsHit->Get_ID_AoQ_mhtdc(i) > 0 && FrsHit->Get_ID_x4() > -100 && FrsHit->Get_ID_x4() < 100)  hID_x4AoQ_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                
                // Charge states
                // CEJ: dEdeg mhtdc is not used in the check, but it is filled. Why??
                if(FrsHit->Get_ID_z_mhtdc(i) > 0 && FrsHit->Get_ID_dEdegoQ() != 0) hdEdegoQ_Z_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdegoQ_mhtdc(i));
                if(FrsHit->Get_ID_z_mhtdc(i) > 0 && FrsHit->Get_ID_dEdeg() != 0) hdEdeg_Z_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_dEdeg_mhtdc(i));
            
                // Angles vs AoQ 
                if(FrsHit->Get_ID_AoQ_mhtdc(i) != 0 && FrsHit->Get_ID_a2() != 0) hID_a2AoQ_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_a2());
                if(FrsHit->Get_ID_AoQ_mhtdc(i) != 0 && FrsHit->Get_ID_a4() != 0) hID_a4AoQ_mhtdc->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_a4());
            
                if(FrsHit->Get_ID_z_mhtdc(i) != 0 && FrsHit->Get_music_dE()[1] != 0) hID_Z_dE2_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_music_dE()[1]);
                
                if(FrsHit->Get_ID_z_mhtdc(i) != 0 && FrsHit->Get_sci_l()[2] != 0 && FrsHit->Get_sci_r()[2] != 0) hID_Z_Sc21E_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), sqrt(FrsHit->Get_sci_l()[2] * FrsHit->Get_sci_r()[2]));
            
                hID_x2z_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_x2());
                
                hID_x4z_mhtdc->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_x4());

            } // multihit loop

            // MHTDC PID Gates
            for(int gate = 0; gate < FRS_GATES; g++)
            {
                //GATE: AoQ vs Z
                for (int i = 0; i < MAX_FRS_MULT; i++)
                {
                    if(cID_Z_AoQ_mhtdc[gate]->IsInside(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i)))
                    {   
                        // CEJ: this will change based on final hit?
                        FrsAnalysisHit->Set_ZvsAoQ_mhtdc_gates(gate) = true;
                        hID_x2AoQ_Z1AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                        hID_x4AoQ_Z1AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                        hID_ZAoQ_ZAoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                        hID_Z1Z2_ZAoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                        hID_dEdegZ1_Z1AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_dEdeg_mhtdc(i));
                        hID_dEdegoQ_Z1_Z1AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_dEdegoQ_mhtdc(i));
                        hID_a2_Z1AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a2());
                        hID_a4_Z1AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a4());
                    }
                
                    // GATE: Z1 vs Z2
                    if(cID_Z_Z2gate_mhtdc[gate]->IsInside(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i)))
                    {
                        FrsAnalysisHit->Set_ZvsZ2_mhtdc_gates(gate) = true;
                        hID_dEdegZ1_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_dEdeg_mhtdc(i));
                        hID_dEdegoQ_Z1_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_dEdegoQ_mhtdc(i));
                        hID_Z1_Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                        if(FrsHit->Get_ID_a2() != 0) hID_a2_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_a2());
                        if(FrsHit->Get_ID_a4() != 0) hID_a4_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_a4());
                    
                        // X2 AoQ gated on Z1 Z2
                        if(FrsHit->Get_ID_x2() > -100 && FrsHit->Get_ID_x2() < 100)
                        {
                            hID_x2AoQ_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                        }
                        
                        if(FrsHit->Get_ID_x4() > -100 && FrsHit->Get_ID_x4() < 100)
                        {
                            hID_x4AoQ_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                            
                            // Z1 AoQ gated on Z1 Z2
                            if(FrsHit->Get_ID_AoQ_mhtdc(i) != 0 && FrsHit->Get_ID_z_mhtdc(i) != 0) hID_ZAoQ_Z1Z2gate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                            
                        }
                    }    
                        
                    // ID x2 vs AoQ
                    if(cID_x2AoQ_mhtdc[gate]->IsInside(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2()))
                    {
                        FrsAnalysisHit->Set_x2vsAoQ_mhtdc_gates(gate) = true;
                        hID_x2AoQ_x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                        hID_Z1Z2_x2AoQgate[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                        // The selected Z1 Z2 gate for this part can be found in the Correlations_config.dat file
                        // Z1 Z2 +X2 AoQ
                        if(cID_Z_Z2gate_mhtdc[1]->IsInside(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i)))
                        {
                            hID_x2AoQ_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                            hID_x4AoQ_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                            hID_Z1Z2_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                            hID_dEdegZ1_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_dEdeg_mhtdc(i));
                            hID_dEdegoQ_Z1_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_dEdegoQ_mhtdc(i));
                            hID_a2_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a2());
                            hID_a4_Z1Z2x2AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a4());
                        }
                    }

                    // ID x4 vs AoQ
                    if(cID_x4AoQ_mhtdc[gate]->IsInside(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4()))
                    {   
                        FrsAnalysisHit->Set_x4vsAoQ_mhtdc_gates(gate) = true;
                        hID_x4AoQ_x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                        hID_Z1Z2_x4AoQgate[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                        // The selected Z1 Z2 gate for this part can be found in the Correlations_config.dat file
                        // Z1 Z2 +X4 AoQ
                        if(cID_Z_Z2gate_mhtdc[1]->IsInside(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i)))
                        {
                            hID_x2AoQ_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                            hID_x4AoQ_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                            hID_Z1Z2_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z2_mhtdc(i));
                            hID_dEdegZ1_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_dEdeg_mhtdc(i));
                            hID_dEdegoQ_Z1_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_dEdegoQ_mhtdc(i));
                            hID_a2_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a2());
                            hID_a4_Z1Z2x4AoQgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a4());
                            
                        }
                    }

                    // GATE: Energy loss S2 vs Z (Charge states)
                    if (cID_dEdegZ1_mhtdc[gate]->IsInside(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_dEdeg()))
                    {
                        FrsAnalysisHit->Set_ZvsdEdeg_mhtdc_gates(gate) = true;
                        hID_dEdegZ1_dEdegZ1Gated_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_dEdeg()); // CEJ: again why not MHTDC here
                        hID_Z1AoQ_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                        hID_Z1Z2_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_z_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                        hID_x2AoQ_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x2());
                        hID_x4AoQ_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_x4());
                        hID_a2_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a2());
                        hID_a4_dEdegZgate_mhtdc[gate]->Fill(FrsHit->Get_ID_a4());
                
                        if (fabs(FrsHit->Get_ID_z2_mhtdc(i) - FrsHit->Get_ID_z_mhtdc(i)) < 0.4) hID_Z1AoQ_zsame_dEdegZgate_mhtdc[g]->Fill(FrsHit->Get_ID_AoQ_mhtdc(i), FrsHit->Get_ID_z_mhtdc(i));
                    }
                } // mhtdc loop
            } // gate loop
        } // ihits
    } // non-zero FRS entries
    
}


void FrsAnalysisSpectra::FinishEvent()
{

}

void FrsAnalysisSpectra::FinishTask()
{

}

ClassImp(FrsAnalysisSpectra)
