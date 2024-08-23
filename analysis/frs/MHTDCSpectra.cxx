// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "MHTDCSpectra.h"
#include "FrsHitData.h"
#include "FrsMainCalData.h"
#include "FrsTPCData.h"
#include "FrsTPCCalData.h"
#include "FrsUserCalData.h"
#include "FrsHitData.h"
#include "EventHeader.h"
#include "c4Logger.h"


// ROOT
#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TDirectory.h"

#include "TRandom3.h"

Float_t MHTDCSpectra::rand3()
{
    return random3.Uniform(-0.5,0.5);
}

MHTDCSpectra::MHTDCSpectra()
    : MHTDCSpectra("MHTDCSpectra", 1)
{    
    frs_config = TFrsConfiguration::GetInstance();
    frs = frs_config->FRS();
    sci = frs_config->SCI();

}

MHTDCSpectra::MHTDCSpectra(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   mainSciArray(nullptr)
{    
    frs_config = TFrsConfiguration::GetInstance();
    frs = frs_config->FRS();
    sci = frs_config->SCI();
}

MHTDCSpectra::~MHTDCSpectra()
{
    c4LOG(info, "");
    
}

InitStatus MHTDCSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    // also needs TPC raw I think
    mainSciArray = mgr->InitObjectAs<decltype(mainSciArray)>("FrsMainCalSciData");
    c4LOG_IF(fatal, !mainSciArray, "Branch FrsMainCalSciData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    // look for FRS directory, create it if not found
    dir_frs = (TDirectory*)mgr->GetObject("MHTDC spectra");
    if (dir_frs == nullptr) 
    {
        LOG(info) << "Creating MHTDC spectra Online Directory";
        dir_frs = new TDirectory("MHTDC spectra Online", "MHTDC spectra Online", "", 0);
        mgr->Register("MHTDC spectra", "MHTDC spectra Online Directory", dir_frs, false); // allow other tasks to find this
        histograms->Add(dir_frs);
    }

    //Main crate detectors:

    dir_frs->cd();

    //SCI         
    //SCI dts
    h_sci_21l_21r_dt = new TH1D("h_sci_21l_21r_dt", "h_sci_21l_21r_dt", 2000,-1000,1000);
    h_sci_22l_22r_dt = new TH1D("h_sci_22l_22r_dt", "h_sci_22l_22r_dt", 2000,-1000,1000);
    h_sci_41l_41r_dt = new TH1D("h_sci_41l_41r_dt", "h_sci_41l_41r_dt", 2000,-1000,1000);
    h_sci_42l_42r_dt = new TH1D("h_sci_42l_42r_dt", "h_sci_42l_42r_dt", 2000,-1000,1000);

    //dx:
    h_sci21_x = new TH1D("h_sci21_x", "h_sci21_x", 2000,-1000,1000);
    h_sci22_x = new TH1D("h_sci22_x", "h_sci22_x", 2000,-1000,1000);
    h_sci41_x = new TH1D("h_sci41_x", "h_sci41_x", 2000,-1000,1000);
    h_sci42_x = new TH1D("h_sci42_x", "h_sci42_x", 2000,-1000,1000);
    
    //tof:
    h_tof_4121 = new TH1D("h_tof_4121", "h_tof_4121", 40000,-200,200);
    h_tof_4221 = new TH1D("h_tof_4221", "h_tof_4221", 40000,-200,200);
    h_tof_4222 = new TH1D("h_tof_4222", "h_tof_4222", 40000,-200,200);
    h_tof_4122 = new TH1D("h_tof_4122", "h_tof_4122", 40000,-200,200);


    //multiplicities:
    //SCI t
    h_sci_21l_hits = new TH1D("h_sci_21l_hits", "h_sci_21l_hits", 10, 1, 11);
    h_sci_21r_hits = new TH1D("h_sci_21r_hits", "h_sci_21r_hits", 10, 1, 11);
    h_sci_22l_hits = new TH1D("h_sci_22l_hits", "h_sci_22l_hits", 10, 1, 11);
    h_sci_22r_hits = new TH1D("h_sci_22r_hits", "h_sci_22r_hits", 10, 1, 11);
    h_sci_41l_hits = new TH1D("h_sci_41l_hits", "h_sci_41l_hits", 10, 1, 11);
    h_sci_41r_hits = new TH1D("h_sci_41r_hits", "h_sci_41r_hits", 10, 1, 11);
    h_sci_42l_hits = new TH1D("h_sci_42l_hits", "h_sci_42l_hits", 10, 1, 11);
    h_sci_42r_hits = new TH1D("h_sci_42r_hits", "h_sci_42r_hits", 10, 1, 11);

    


    return kSUCCESS;

}

void MHTDCSpectra::Reset_Histo()
{
    c4LOG(info, "");
    // incoming
}

void MHTDCSpectra::Exec(Option_t* option)
{   
    int hits = mainSciArray->size();

    auto const & mainSciItem  = mainSciArray->at(0);
    
    // SCI 21 L and R
    int hits_in_21lr = mainSciItem.Get_mhtdc_sc21l_nr_hits()*mainSciItem.Get_mhtdc_sc21r_nr_hits();
    for (int i = 0; i < mainSciItem.Get_mhtdc_sc21l_nr_hits(); i++)
    {
        for (int j = 0; j < mainSciItem.Get_mhtdc_sc21r_nr_hits(); j ++){
            double sci_21l_21r_dt = ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc21l_hit(i) - mainSciItem.Get_mhtdc_sc21r_hit(j));
            h_sci_21l_21r_dt->Fill(sci_21l_21r_dt);
            h_sci21_x->Fill(sci_21l_21r_dt * mhtdc_factor_21l_21r + mhtdc_offset_21l_21r);
        

        }
    }
    h_sci_21l_hits->Fill(mainSciItem.Get_mhtdc_sc21l_nr_hits());
    h_sci_21r_hits->Fill(mainSciItem.Get_mhtdc_sc21r_nr_hits());

    // SCI 22 L and R
    int hits_in_22lr = mainSciItem.Get_mhtdc_sc22l_nr_hits()*mainSciItem.Get_mhtdc_sc22r_nr_hits();
    for (int i = 0; i < mainSciItem.Get_mhtdc_sc22l_nr_hits(); i++)
    {
        for (int j = 0; j < mainSciItem.Get_mhtdc_sc22r_nr_hits(); j ++){
            double sci_22l_22r_dt = ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc22l_hit(i) - mainSciItem.Get_mhtdc_sc22r_hit(j));
            h_sci_22l_22r_dt->Fill(sci_22l_22r_dt);
            h_sci22_x->Fill(sci_22l_22r_dt * mhtdc_factor_22l_22r + mhtdc_offset_22l_22r);
        

        }
    }
    h_sci_22l_hits->Fill(mainSciItem.Get_mhtdc_sc22l_nr_hits());
    h_sci_22r_hits->Fill(mainSciItem.Get_mhtdc_sc22r_nr_hits());
    
    

    // SCI 41 L and R
    int hits_in_41lr = mainSciItem.Get_mhtdc_sc41l_nr_hits()*mainSciItem.Get_mhtdc_sc41r_nr_hits();
    for (int i = 0; i < mainSciItem.Get_mhtdc_sc41l_nr_hits(); i++)
    {
        for (int j = 0; j < mainSciItem.Get_mhtdc_sc41r_nr_hits(); j ++){
            double sci_41l_41r_dt = ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc41l_hit(i) - mainSciItem.Get_mhtdc_sc41r_hit(j));
            h_sci_41l_41r_dt->Fill(sci_41l_41r_dt);
            h_sci41_x->Fill(sci_41l_41r_dt * mhtdc_factor_41l_41r + mhtdc_offset_41l_41r);
        

        }
    }
    h_sci_41l_hits->Fill(mainSciItem.Get_mhtdc_sc41l_nr_hits());
    h_sci_41r_hits->Fill(mainSciItem.Get_mhtdc_sc41r_nr_hits());


    // SCI 42 L and R
    int hits_in_42lr = mainSciItem.Get_mhtdc_sc42l_nr_hits()*mainSciItem.Get_mhtdc_sc42r_nr_hits();
    for (int i = 0; i < mainSciItem.Get_mhtdc_sc42l_nr_hits(); i++)
    {
        for (int j = 0; j < mainSciItem.Get_mhtdc_sc42r_nr_hits(); j ++){
            double sci_42l_42r_dt = ch_to_ns * (rand3() + mainSciItem.Get_mhtdc_sc42l_hit(i) - mainSciItem.Get_mhtdc_sc42r_hit(j));
            h_sci_42l_42r_dt->Fill(sci_42l_42r_dt);
            h_sci42_x->Fill(sci_42l_42r_dt * mhtdc_factor_42l_42r + mhtdc_offset_42l_42r);
        

        }
    }
    h_sci_42l_hits->Fill(mainSciItem.Get_mhtdc_sc42l_nr_hits());
    h_sci_42r_hits->Fill(mainSciItem.Get_mhtdc_sc42r_nr_hits());
      
    // 21 -> 41
    for (int i = 0; i<mainSciItem.Get_mhtdc_sc41l_nr_hits(); i++) // over 21 hits
    {
        for (int j = 0; j<mainSciItem.Get_mhtdc_sc41r_nr_hits(); j++)
        {
            for (int k = 0; k<mainSciItem.Get_mhtdc_sc21l_nr_hits(); k++) // over 21 hits
            {
                for (int l = 0; l<mainSciItem.Get_mhtdc_sc21r_nr_hits(); l++)
                {
                    if ( (TMath::Abs(mainSciItem.Get_mhtdc_sc41l_hit(i) - mainSciItem.Get_mhtdc_sc41r_hit(j))*ch_to_ns < 40) &&  (TMath::Abs(mainSciItem.Get_mhtdc_sc21l_hit(i) - mainSciItem.Get_mhtdc_sc21r_hit(j))*ch_to_ns < 40) ) {
                        h_tof_4121->Fill(ch_to_ns * (0.5 * (mainSciItem.Get_mhtdc_sc41l_hit(i) + mainSciItem.Get_mhtdc_sc41r_hit(j)) - 0.5 * (mainSciItem.Get_mhtdc_sc21l_hit(k) + mainSciItem.Get_mhtdc_sc21r_hit(l))) + mhtdc_offset_41_21);
                    }
                }
            }
        }
    }

    // 22 -> 41
    for (int i = 0; i < mainSciItem.Get_mhtdc_sc41l_nr_hits(); i++) // over 22 hits
    {
        for (int j = 0; j<mainSciItem.Get_mhtdc_sc41r_nr_hits(); j++)
        {
            for (int k = 0; k < mainSciItem.Get_mhtdc_sc22l_nr_hits(); k++) // over 22 hits
            {
                for (int l = 0; l<mainSciItem.Get_mhtdc_sc22r_nr_hits(); l++)
                {
                    if ( (TMath::Abs(mainSciItem.Get_mhtdc_sc41l_hit(i) - mainSciItem.Get_mhtdc_sc41r_hit(j))*ch_to_ns < 40) &&  (TMath::Abs(mainSciItem.Get_mhtdc_sc22l_hit(i) - mainSciItem.Get_mhtdc_sc22r_hit(j))*ch_to_ns < 40) ) {
                    h_tof_4122->Fill(ch_to_ns * (0.5 * (mainSciItem.Get_mhtdc_sc41l_hit(i) + mainSciItem.Get_mhtdc_sc41r_hit(j)) - 0.5 * (mainSciItem.Get_mhtdc_sc22l_hit(k) + mainSciItem.Get_mhtdc_sc22r_hit(l))) + mhtdc_offset_41_22);
                    }
                }
            }
        }
    }



    // 21 -> 42
    for (int i = 0; i < mainSciItem.Get_mhtdc_sc42l_nr_hits(); i++) // over 21 hits
    {
        for (int j = 0; j<mainSciItem.Get_mhtdc_sc42r_nr_hits(); j++)
        {
            for (int k = 0; k < mainSciItem.Get_mhtdc_sc21l_nr_hits(); k++) // over 21 hits
            {
                for (int l = 0; l<mainSciItem.Get_mhtdc_sc21r_nr_hits(); l++)
                {
                    if ( (TMath::Abs(mainSciItem.Get_mhtdc_sc42l_hit(i) - mainSciItem.Get_mhtdc_sc42r_hit(j))*ch_to_ns < 40) &&  (TMath::Abs(mainSciItem.Get_mhtdc_sc21l_hit(i) - mainSciItem.Get_mhtdc_sc21r_hit(j))*ch_to_ns < 40) ) {
                    h_tof_4221->Fill(ch_to_ns * (0.5 * (mainSciItem.Get_mhtdc_sc42l_hit(i) + mainSciItem.Get_mhtdc_sc42r_hit(j)) - 0.5 * (mainSciItem.Get_mhtdc_sc21l_hit(k) + mainSciItem.Get_mhtdc_sc21r_hit(l))) + mhtdc_offset_42_21);
                    }
                }
            }
        }
    }

    /*
    // 22 -> 42
    int hits_in_tof4222 = hits_in_42lr*hits_in_22lr;
    for (int i = 0; i < hits_in_22lr; i++) // over 22 hits
    {
        for (int j = 0; j<hits_in_42lr; j++)
        {
            h_tof_4222->Fill(ch_to_ns * (0.5 * (mainSciItem.Get_mhtdc_sc42l_hit(j) + mainSciItem.Get_mhtdc_sc42r_hit(j)) - 0.5 * (mainSciItem.Get_mhtdc_sc22l_hit(i) + mainSciItem.Get_mhtdc_sc22r_hit(i))) + mhtdc_offset_42_22);
        }
    }
    */


    fNEvents += 1;

}

void MHTDCSpectra::FinishEvent()
{
}

void MHTDCSpectra::FinishTask()
{
    
}

ClassImp(MHTDCSpectra)
