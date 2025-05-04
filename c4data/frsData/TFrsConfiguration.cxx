// c4
#include "TFrsConfiguration.h"
#include "c4Logger.h"
#include <sstream>

TFrsConfiguration* TFrsConfiguration::instance = nullptr;
std::string TFrsConfiguration::config_path = "blank";
std::string TFrsConfiguration::scaler_mapping_file = "blank";
std::string TFrsConfiguration::tm_drift_coeff_file = "blank";
std::string TFrsConfiguration::aoq_drift_coeff_file = "blank";
std::string TFrsConfiguration::z1_drift_coeff_file = "blank";
std::string TFrsConfiguration::crate_map_file = "blank";

TFRSParameter* TFrsConfiguration::ffrs;
TMWParameter* TFrsConfiguration::fmw;
TTPCParameter* TFrsConfiguration::ftpc;
TMUSICParameter* TFrsConfiguration::fmusic;
TLABRParameter* TFrsConfiguration::flabr;
TSCIParameter* TFrsConfiguration::fsci;
TIDParameter* TFrsConfiguration::fid;
TSIParameter* TFrsConfiguration::fsi;
TMRTOFMSParameter* TFrsConfiguration::fmrtof;
TRangeParameter* TFrsConfiguration::frange;
TString TFrsConfiguration::setup_file = "";

Bool_t TFrsConfiguration::old_beta_cal = false;

Double_t TFrsConfiguration::fMin_Z = 0., TFrsConfiguration::fMax_Z = 100.;
Double_t TFrsConfiguration::fMin_AoQ = 2., TFrsConfiguration::fMax_AoQ = 3.;
Double_t TFrsConfiguration::fMin_x2 = -100., TFrsConfiguration::fMax_x2 = 100.;
Double_t TFrsConfiguration::fMin_x4 = -100., TFrsConfiguration::fMax_x4 = 100.;
Double_t TFrsConfiguration::fMin_a2 = -100., TFrsConfiguration::fMax_a2 = 100.;
Double_t TFrsConfiguration::fMin_a4 = -100., TFrsConfiguration::fMax_a4 = 100.;
Double_t TFrsConfiguration::fMin_y2 = -100., TFrsConfiguration::fMax_y2 = 100.;
Double_t TFrsConfiguration::fMin_y4 = -100., TFrsConfiguration::fMax_y4 = 100.;
Double_t TFrsConfiguration::fMin_b2 = -100., TFrsConfiguration::fMax_b2 = 100.;
Double_t TFrsConfiguration::fMin_b4 = -100., TFrsConfiguration::fMax_b4 = 100.;
Double_t TFrsConfiguration::fMin_dE = 10., TFrsConfiguration::fMax_dE = 100.;
Double_t TFrsConfiguration::fMin_dEoQ = 0.1, TFrsConfiguration::fMax_dEoQ = 0.8;
Double_t TFrsConfiguration::fMin_dE_music21 = 0., TFrsConfiguration::fMax_dE_music21 = 4000.;
Double_t TFrsConfiguration::fMin_dE_music41 = 0., TFrsConfiguration::fMax_dE_music41 = 4000.;
Double_t TFrsConfiguration::fMin_dE_music42 = 0., TFrsConfiguration::fMax_dE_music42 = 4000.;
Double_t TFrsConfiguration::fMin_dE_travMus_gate = 0., TFrsConfiguration::fMax_dE_travMus_gate = 30000.;

int TFrsConfiguration::frun_num = 0;

TFrsConfiguration::TFrsConfiguration()
{
    ReadScalerNames();
    ReadCrateMapFile(); // absolutely critical
    ReadTravMusDriftFile(); // not critical
    ReadAoQDriftFile(); // not critical
    ReadZ1DriftFile(); // not critical
    
}

void TFrsConfiguration::ReadScalerNames()
{   
    // set default names incase not provided by mapping or mapping isn't loaded
    for (int i = 0; i < 66; i++) scaler_name[i] =  std::string(Form("scaler_ch_%i",i));

    std::ifstream file(scaler_mapping_file);
    std::string line;

    if (file.fail()) { c4LOG(warn, "Could not open FRS Scaler mapping file"); return; }

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        int scaler;
        std::string name;

        iss >> scaler >> name;

        std::replace(name.begin(), name.end(), '_', ' ');

        scaler_name[scaler] = name;

    }

    file.close();
    return;

}

void TFrsConfiguration::SetParameters(
        TFRSParameter* frs,
        TMWParameter* mw,
        TTPCParameter* tpc,
        TMUSICParameter* music,
        TLABRParameter* labr,
        TSCIParameter* sci,
        TIDParameter* id,
        TSIParameter* si,
        TMRTOFMSParameter* mrtof,
        TRangeParameter* range)
{
    ffrs = frs;
    fmw = mw;
    ftpc = tpc;
    fmusic = music;
    flabr = labr;
    fsci = sci;
    fid = id;
    fsi = si;
    fmrtof = mrtof;
    frange = range;
}

// ::: Read Drift from file - TravMus, AoQ and Z :::
//EG Drift TM for dE (is it better to correct anode? ... not sure)
void TFrsConfiguration::ReadTravMusDriftFile()
{
    std::ifstream travmus_drift_coeff_file (tm_drift_coeff_file);
    std::string line;

    if (travmus_drift_coeff_file.fail()) { c4LOG(warn, "Could not open Trav Mus drift coefficients file."); return; }


    while (std::getline(travmus_drift_coeff_file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        int travmus_wr;
        double drift_val;
        double drift_err;
        std::pair<double, double> drift_coeff;

        iss >> travmus_wr >> drift_val >> drift_err;

        drift_coeff = std::make_pair(drift_val,drift_err);
        travmus_drift_coeff.insert(std::make_pair(travmus_wr, drift_coeff));

        //std::cout << " wr :  "<< travmus_wr << " drift coeff: " << drift_val << "\n";

    }
    
    travmus_drift_loaded = 1;
    travmus_drift_coeff_file.close();
    
    c4LOG(info, "Trav Mus Drift File: " + tm_drift_coeff_file);
    return;    
}

void TFrsConfiguration::ReadAoQDriftFile()
{
    std::ifstream AoQ_drift_coeff_file (aoq_drift_coeff_file);
    std::string line;

    if (AoQ_drift_coeff_file.fail()) c4LOG(warn, "Could not open AoQ drift coefficients file.");


    while (std::getline(AoQ_drift_coeff_file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        int frs_wr;
        double drift_val;
        double drift_err;
        std::pair<double, double> drift_coeff;

        iss >> frs_wr >> drift_val >> drift_err;

        drift_coeff = std::make_pair(drift_val,drift_err);
        aoq_drift_coeff.insert(std::make_pair(frs_wr, drift_coeff));


        //std::cout << " wr:  "<< frs_wr <<  " AoQ drift coeff: " << drift_val << "\n";

    }
    
    aoq_drift_loaded = 1;
    AoQ_drift_coeff_file.close();
    
    c4LOG(info, "AoQ Drift File: " + aoq_drift_coeff_file);
    return;    
}

void TFrsConfiguration::ReadZ1DriftFile()
{
    std::ifstream Z1_drift_coeff_file (z1_drift_coeff_file);
    std::string line;

    if (Z1_drift_coeff_file.fail()) c4LOG(warn, "Could not open Z1 drift coefficients file.");


    while (std::getline(Z1_drift_coeff_file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        int frs_wr;
        double drift_val;
        double drift_err;
        std::pair<double, double> drift_coeff;

        iss >> frs_wr >> drift_val >> drift_err;
        
        drift_coeff = std::make_pair(drift_val,drift_err);
        z1_drift_coeff.insert(std::make_pair(frs_wr, drift_coeff));

        //std::cout << " wr:  "<< frs_wr << " Z1 drift coeff: " << drift_val << "\n";

    }
    
    z1_drift_loaded = 1;
    Z1_drift_coeff_file.close();
    
    c4LOG(info, "Z1 Drift File: " + z1_drift_coeff_file);
    return;    
}


void TFrsConfiguration::ReadCrateMapFile()
{
    std::ifstream file (crate_map_file);
    std::string line;

    c4LOG(info, "FRS Crate Map Path: " + crate_map_file);
    if (file.fail()) c4LOG(fatal, "Could not open FRS Crate Mapping mapping file.");

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss(line);

        std::string signal;
        int channel;

        iss >> signal;

        if (isdigit(signal[0])) { std::cout << "Error in FRS Crate Mapping file. Row should begin with a string." << std::endl; return; }
        else
        {
            iss >> channel;
            
            if (signal == "MUSIC_E_GEO") music_e_geo = channel; // remove
            else if (signal == "DE_GEO") sci_dE_geo = channel; // remove
            else if (signal == "dE_11L") de_11l_ch = channel;
            else if (signal == "dE_11R") de_11r_ch = channel;
            else if (signal == "dE_21L") de_21l_ch = channel;
            else if (signal == "dE_21R") de_21r_ch = channel;
            else if (signal == "dE_22L") de_22l_ch = channel;
            else if (signal == "dE_22R") de_22r_ch = channel;
            else if (signal == "dE_31L") de_31l_ch = channel;
            else if (signal == "dE_31R") de_31r_ch = channel;
            else if (signal == "dE_41L") de_41l_ch = channel;
            else if (signal == "dE_41R") de_41r_ch = channel;
            else if (signal == "dE_42L") de_42l_ch = channel;
            else if (signal == "dE_42R") de_42r_ch = channel;
            else if (signal == "dE_43L") de_43l_ch = channel;
            else if (signal == "dE_43R") de_43r_ch = channel;
            else if (signal == "dE_81L") de_81l_ch = channel;
            else if (signal == "dE_81R") de_81r_ch = channel;
            else if (signal == "DT_GEO") sci_dT_geo = channel; // remove
            else if (signal == "dT_11L_11R") dt_11l_11r_ch = channel;
            else if (signal == "dT_21L_21R") dt_21l_21r_ch = channel;
            else if (signal == "dT_41L_41R") dt_41l_41r_ch = channel;
            else if (signal == "dT_42L_42R") dt_42l_42r_ch = channel;
            else if (signal == "dT_43L_43R") dt_43l_43r_ch = channel;
            else if (signal == "dT_81L_81R") dt_81l_81r_ch = channel;
            else if (signal == "dT_11L_21L") dt_11l_21l_ch = channel;
            else if (signal == "dT_11R_21R") dt_11r_21r_ch = channel;
            else if (signal == "dT_21L_41L") dt_21l_41l_ch = channel;
            else if (signal == "dT_21R_41R") dt_21r_41r_ch = channel;
            else if (signal == "dT_42R_21R") dt_42r_21r_ch = channel;
            else if (signal == "dT_42L_21L") dt_42l_21l_ch = channel;
            else if (signal == "dT_21L_81L") dt_21l_81l_ch = channel;
            else if (signal == "dT_21R_81R") dt_21r_81r_ch = channel;
            else if (signal == "dT_22L_22R") dt_22l_22r_ch = channel;
            else if (signal == "dT_22L_41L") dt_22l_41l_ch = channel;
            else if (signal == "dT_22R_41R") dt_22r_41r_ch = channel;
            else if (signal == "dT_22L_81L") dt_22l_81l_ch = channel;
            else if (signal == "dT_22R_81R") dt_22r_81r_ch = channel;
            else if (signal == "dT_41L_41R") dt_41l_41r_ch = channel;
            else if (signal == "mhtdc_11LA") mhtdc_11LA_ch = channel;
            else if (signal == "mhtdc_11LB") mhtdc_11LB_ch = channel;
            else if (signal == "mhtdc_11LC") mhtdc_11LC_ch = channel;
            else if (signal == "mhtdc_11LD") mhtdc_11LD_ch = channel;
            else if (signal == "mhtdc_11RA") mhtdc_11RA_ch = channel;
            else if (signal == "mhtdc_11RB") mhtdc_11RB_ch = channel;
            else if (signal == "mhtdc_11RC") mhtdc_11RC_ch = channel;
            else if (signal == "mhtdc_11RD") mhtdc_11RD_ch = channel;
            else if (signal == "mhtdc_21L") mhtdc_21L_ch = channel;
            else if (signal == "mhtdc_21R") mhtdc_21R_ch = channel;
            else if (signal == "mhtdc_22L") mhtdc_22L_ch = channel;
            else if (signal == "mhtdc_22R") mhtdc_22R_ch = channel;
            else if (signal == "mhtdc_31L") mhtdc_31L_ch = channel;
            else if (signal == "mhtdc_31R") mhtdc_31R_ch = channel;
            else if (signal == "mhtdc_41L") mhtdc_41L_ch = channel;
            else if (signal == "mhtdc_41R") mhtdc_41R_ch = channel;
            else if (signal == "mhtdc_42L") mhtdc_42L_ch = channel;
            else if (signal == "mhtdc_42R") mhtdc_42R_ch = channel;
            else if (signal == "mhtdc_43L") mhtdc_43L_ch = channel;
            else if (signal == "mhtdc_43R") mhtdc_43R_ch = channel;
            else if (signal == "mhtdc_81L") mhtdc_81L_ch = channel;
            else if (signal == "mhtdc_81R") mhtdc_81R_ch = channel;

        }
    }

    //dT_mapping_loaded = 1;
    file.close();
    
    return;   
}


//:::


void TFrsConfiguration::Set_Z_range(Double_t min, Double_t max)
{
    fMin_Z = min;
    fMax_Z = max;
}

void TFrsConfiguration::Set_AoQ_range(Double_t min, Double_t max)
{
    fMin_AoQ = min;
    fMax_AoQ = max;
}

void TFrsConfiguration::Set_x2_range(Double_t min, Double_t max)
{
    fMin_x2 = min;
    fMax_x2 = max;
}

void TFrsConfiguration::Set_y2_range(Double_t min, Double_t max)
{
    fMin_y2 = min;
    fMax_y2 = max;
}

void TFrsConfiguration::Set_a2_range(Double_t min, Double_t max)
{
    fMin_a2 = min;
    fMax_a2 = max;
}

void TFrsConfiguration::Set_b2_range(Double_t min, Double_t max)
{
    fMin_b2 = min;
    fMax_b2 = max;
}

void TFrsConfiguration::Set_x4_range(Double_t min, Double_t max)
{
    fMin_x4 = min;
    fMax_x4 = max;
}

void TFrsConfiguration::Set_y4_range(Double_t min, Double_t max)
{
    fMin_y4 = min;
    fMax_y4 = max;
}

void TFrsConfiguration::Set_a4_range(Double_t min, Double_t max)
{
    fMin_a4 = min;
    fMax_a4 = max;
}
void TFrsConfiguration::Set_b4_range(Double_t min, Double_t max)
{
    fMin_b4 = min;
    fMax_b4 = max;
}

void TFrsConfiguration::Set_dEdeg_range(Double_t min, Double_t max)
{
    fMin_dE = min;
    fMax_dE = max;
}

void TFrsConfiguration::Set_dEdegoQ_range(Double_t min, Double_t max)
{
    fMin_dEoQ = min;
    fMax_dEoQ = max;
}

void TFrsConfiguration::Set_dE_music21_range(Double_t min, Double_t max)
{
    fMin_dE_music21 = min;
    fMax_dE_music21 = max;
}

void TFrsConfiguration::Set_dE_music41_range(Double_t min, Double_t max)
{
    fMin_dE_music41 = min;
    fMax_dE_music41 = max;
}

void TFrsConfiguration::Set_dE_music42_range(Double_t min, Double_t max)
{
    fMin_dE_music42 = min;
    fMax_dE_music42 = max;
}

void TFrsConfiguration::Set_dE_travMusic_gate(Double_t min, Double_t max)
{
    fMin_dE_travMus_gate = min;
    fMax_dE_travMus_gate = max;
}



// read files and stuff