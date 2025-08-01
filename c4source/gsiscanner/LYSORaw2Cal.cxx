
// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "FairLogger.h"

#include "c4Logger.h"

// c4
#include "QDCData.h"
#include "LYSOCalData.h"
#include "TLYSOConfiguration.h"

#include "TClonesArray.h"
#include "TMath.h"
#include "LYSORaw2Cal.h"

/*
Empty constructor for FairRoot.
*/
LYSORaw2Cal::LYSORaw2Cal()
: FairTask(), 
fNEvents(0),
header(nullptr),
fOnline(kFALSE),
funcal_data(new TClonesArray("QDCData")),
fcal_data(new TClonesArray("LYSOCalData"))
{
    lyso_configuration = TLYSOConfiguration::GetInstance();
}

/*
Named constructor with verbosity level.
*/
LYSORaw2Cal::LYSORaw2Cal(const TString& name, Int_t verbose) 
    : FairTask(name, verbose),
    fNEvents(0),
    header(nullptr),
    fOnline(kFALSE),
    funcal_data(new TClonesArray("QDCData")),
    fcal_data(new TClonesArray("LYSOCalData"))
{
    lyso_configuration = TLYSOConfiguration::GetInstance();
}

LYSORaw2Cal::~LYSORaw2Cal(){
    c4LOG(info, "Deleting LYSORaw2Cal task");
    if (funcal_data) delete funcal_data;
    if (fcal_data) delete fcal_data;
}



void LYSORaw2Cal::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

/*
Init - register data to output tree and gets input data.
*/
InitStatus LYSORaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    funcal_data = (TClonesArray*)mgr->GetObject("QDCData");
    c4LOG_IF(fatal, !funcal_data, "Germanium branch of QDCData not found.");
 
    // needs to have the name of the detector subsystem here:
    FairRootManager::Instance()->Register("LYSOCalData", "LYSO Cal Data", fcal_data, !fOnline);
    
    fcal_data->Clear();

    return kSUCCESS;
}


/*
Analysis event loop. 
Fatal error if detector map is not set. If calibration coeffs are not written, simply the uncalibrated energies are written.

Picks out the TimeMachine.
*/
void LYSORaw2Cal::Exec(Option_t* option)
{
    if (funcal_data && funcal_data->GetEntriesFast() > 0)
    {
        LYSOCalData * event = new LYSOCalData();

        Int_t event_multiplicity = funcal_data->GetEntriesFast();
        for (Int_t ihit = 0; ihit < event_multiplicity; ihit++)
        {
            funcal_hit = (QDCData*)funcal_data->At(ihit);
            int ch_id = funcal_hit->Get_ch_ID();
            int board_id = funcal_hit->Get_board_id();
            int16_t charge = funcal_hit->Get_charge();
            
            int type = lyso_configuration->GetDetectorID(board_id,ch_id).first;

            int anode_number = lyso_configuration->GetDetectorID(board_id,ch_id).second;

            std::vector<double> coeff = lyso_configuration->GetCalibrationCoeff(board_id,ch_id);

            double energy = 0;

            if (coeff.size() >= 2){
                energy = (coeff.at(0) + (double)charge)*coeff.at(1) + (double)charge*(double)charge*coeff.at(2);
            }else{
                energy = charge;
            }
        
            double threshold = lyso_configuration->GetThreshold(board_id,ch_id);

            //if (energy < threshold) continue;
            
            if (type == 0) //x anode
            {
                event->Set_board_id_x(anode_number,board_id);
                event->Set_ch_ID_x(anode_number,ch_id);
                event->Set_charge_x(anode_number, charge);
                event->Set_energy_x(anode_number, energy);
            }
            if (type == 1) //y anode
            {
                event->Set_board_id_y(anode_number,board_id);
                event->Set_ch_ID_y(anode_number,ch_id);
                event->Set_charge_y(anode_number, charge);
                event->Set_energy_y(anode_number, energy);
            }

            //c4LOG(info,Form("ch id = %i, bid = %i, charge = %i, type = %i, anode_number = %i, energy = %f, thresh = %f, nf = %i",ch_id,board_id,charge,type,anode_number,energy,threshold,event->Get_fired_anodes()));
            //aux channels?
        }

        if (event->Get_fired_anodes() != 32){
            // missing anodes or they are below threshold, discard event.
            return;
        }else{
            // weighted mean for the position:
            double sum_energy_x = 0;
            double weighted_energy_x = 0;
            
            double sum_energy_y = 0;
            double weighted_energy_y = 0;
            
            for (int i = 1; i<=16; i++){
                sum_energy_x += event->Get_energy_x(i);
                weighted_energy_x += ((double)i-1)*event->Get_energy_x(i);
                sum_energy_y += event->Get_energy_y(i);
                weighted_energy_y += ((double)i-1)*event->Get_energy_y(i);
            }

            double posx = weighted_energy_x/sum_energy_x;
            double posy = weighted_energy_y/sum_energy_y;
                       
            // 0,15 -> - 28.125 mm, + 28.125
            

            event->Set_posx(posx*2*28.125/15 - 28.125); //mm
            event->Set_posy(posy*2*28.125/15 - 28.125); //mm

            new ((*fcal_data)[fcal_data->GetEntriesFast()]) LYSOCalData(*event);  
        }
    }
}

/*
Very important function - all TClonesArray must be cleared after each event.
*/
void LYSORaw2Cal::FinishEvent(){
    funcal_data->Clear();
    fcal_data->Clear();
};



ClassImp(LYSORaw2Cal)