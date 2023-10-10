// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "GermaniumFebexData.h"
#include "GermaniumReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_ge_febex.h"
}

GermaniumReader::GermaniumReader(EXT_STR_h101_GE_FEBEX_onion* data, size_t offset)
    : c4Reader("GermaniumReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("GermaniumFebexData"))
{
}

GermaniumReader::~GermaniumReader() { 
    delete fArray;

}

Bool_t GermaniumReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_GE_FEBEX_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_GE_FEBEX, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->Register("GermaniumFebexData", "Germanium Febex Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t GermaniumReader::SetDetectorMapFile(TString filename){
    /*
    TODO: Make the reading fail-safe.

    Assumed structure of detector map is 
    - aribtrary lines of comments starting with #
    - each entry is a line with four number: (febex module id) (febex channel id) (detector id) (crystal id)
    */
    c4LOG(info, "Reading Detector map");

    //std::cout << "reading detector map \n";

    std::ifstream detector_map_file (filename);

    int rfebex_module,rfebex_channel,rdetector_id,rcrystal_id; // temp read variables
    
    //assumes the first line in the file is num-modules used
    while(!detector_map_file.eof()){
        if(detector_map_file.peek()=='#') detector_map_file.ignore(256,'\n');
        else{
            detector_map_file >> rfebex_module >> rfebex_channel >> rdetector_id >> rcrystal_id;
            std::pair<int,int> febex_mc = {rfebex_module,rfebex_channel};
            std::pair<int,int> ge_cd = {rdetector_id,rcrystal_id};
            detector_mapping.insert(std::pair<std::pair<int,int>,std::pair<int,int>>{febex_mc,ge_cd});
            detector_map_file.ignore(256,'\n');

            //TODO: implement a check to make sure keys are unique.
        }
    }
    DetectorMap_loaded = 1;     
    detector_map_file.close();  
    return 0; 
};

Bool_t GermaniumReader::SetDetectorCalFile(TString filename){
    /*
    TODO: Make the reading fail-safe.

    Assumed structure of detector map is 
    - aribtrary lines of comments starting with #
    - each entry is a line with four number: (febex module id) (febex channel id) (detector id) (crystal id)
    */
    c4LOG(info, "Reading Calibration coefficients.");


    std::ifstream cal_map_file (filename);

    int rdetector_id,rcrystal_id; // temp read variables
    double a0,a1;
    
    //assumes the first line in the file is num-modules used
    while(!cal_map_file.eof()){
        if(cal_map_file.peek()=='#') cal_map_file.ignore(256,'\n');
        else{
            cal_map_file >> rdetector_id >> rcrystal_id >> a1 >> a0;
            std::pair<int,int> detector_crystal = {rdetector_id,rcrystal_id};
            std::pair<double,double> cals = {a0,a1};
            calibration_coeffs.insert(std::pair<std::pair<int,int>,std::pair<double,double>>{detector_crystal,cals});
            cal_map_file.ignore(256,'\n');
            //TODO: implement a check to make sure keys are unique.
        }
    }
    DetectorCal_loaded = 1;     
    cal_map_file.close();  
    return 0; 
};

void GermaniumReader::PrintDetectorMap(){
    if (DetectorMap_loaded){
        for (const auto& entry : detector_mapping){
            std::cout << "FEBEXMODULE: " << entry.first.first << " FEBEXCHANNEL " << entry.first.second;
            std::cout << " DETECTORID: " << entry.second.first << " CRYSTALID: " << entry.second.second << "\n";
        }
    }
    else{
        c4LOG(info, "Detector map is not load. Cannot print.");
    }
}

void GermaniumReader::PrintDetectorCal(){
    if (DetectorCal_loaded){
        for (const auto& entry : calibration_coeffs){
            std::cout << "DETECTORID: " << entry.first.first << " CRYSTALID: " << entry.first.second;
            std::cout << " a0: " << entry.second.first << " a1: " << entry.second.second << "\n";
        }
    }
    else{
        c4LOG(info, "Cal map is not load. Cannot print.");
    }
}

Bool_t GermaniumReader::Read() // do the detector mapping here:
{
    c4LOG(debug1, "Event Data");

    //since the febex card has a 100MHz clock which timestamps events.
    event_trigger_time_long = (((uint64_t)(fData->event_trigger_time_hi) << 32) + (fData->event_trigger_time_lo))*10;


    //whiterabbit timestamp:
    wr_t = (((uint64_t)fData->wr_t[3]) << 48) + (((uint64_t)fData->wr_t[2]) << 32) + (((uint64_t)fData->wr_t[1]) << 16) + (uint64_t)(fData->wr_t[0]);

    if (WriteZeroMultEvents & (fData->num_channels_fired == 0)){ 
        // Write if flag is true. See setter to change behaviour.
        new ((*fArray)[fArray->GetEntriesFast()]) GermaniumFebexData(
            fData->num_channels_fired,
            event_trigger_time_long,
            fData->hit_pattern,
            fData->board_id,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            fData->wr_subsystem_id,
            wr_t
        );
    }

    for (int index = 0; index < fData->num_channels_fired; index++)
    {   

        if (VetoOverflow & fData->overflow[index]) continue;
        if (VetoPileup & fData->pileup[index]) continue;
        

        //according to febex manual on gsi website the 24th bit of the energy bits denotes the sign to indicate the polarity of the pulse?
        if (fData->channel_energy[index] & (1 << 23)){
            channel_energy = -(int32_t)(fData->channel_energy[index] & 0x007FFFFF);
        }else{
            channel_energy = +(int32_t)(fData->channel_energy[index] & 0x007FFFFF);            
        }

        //do the detector mapping here:
        if (DetectorMap_loaded){
            std::pair<int,int> unmapped_det {fData->board_id, fData->channel_id[index]};
            
            if (auto result_find = detector_mapping.find(unmapped_det); result_find != detector_mapping.end()){
            detector_id = result_find->second.first; //.find returns an iterator over the pairs matching key.
            crystal_id = result_find->second.second;
            }else{
                c4LOG(fatal, "Detector mapping not complete - exiting.");
            }

            //only do calibrations if mapping is functional:
            if (DetectorCal_loaded){
                std::pair<int,int> calibdet {detector_id, crystal_id};
                if (auto result_find_cal = calibration_coeffs.find(calibdet); result_find_cal != calibration_coeffs.end()){
                double a0 = result_find_cal->second.first; //.find returns an iterator over the pairs matching key.
                double a1 = result_find_cal->second.second;
                channel_energy_cal = a0 + a1*(double)channel_energy;
                }else{
                channel_energy_cal = -1;
                }
            }
        }
        else{ //no map and cal: ->
            detector_id = 0;
            crystal_id = 0;
            channel_energy_cal = -1;
        }


        //collect the LSB and MSB into one variable for channel trigger time
        channel_trigger_time_long = (double)(((uint64_t)(fData->channel_trigger_time_hi[index]) << 32) + (fData->channel_trigger_time_lo[index]));
        //add the CF from the constant fraction. It is denoted by 6 bits in the energy word of the FEBEX data format
        channel_trigger_time_long = (((double)fData->channel_cfd[index])/64.0 + channel_trigger_time_long)*10.0; // units of ns (?)


        new ((*fArray)[fArray->GetEntriesFast()]) GermaniumFebexData(
            fData->num_channels_fired,
            event_trigger_time_long,
            fData->hit_pattern,
            fData->board_id,
            fData->pileup[index],
            fData->overflow[index],
            fData->channel_id[index],
            channel_trigger_time_long,
            channel_energy,
            channel_energy_cal,
            crystal_id,
            detector_id,
            fData->wr_subsystem_id,
            wr_t
        );
    }


    fNEvent += 1;
    return kTRUE;
}

void GermaniumReader::Reset()
{
    // reset output array
    fArray->Clear();
}

ClassImp(GermaniumReader);
