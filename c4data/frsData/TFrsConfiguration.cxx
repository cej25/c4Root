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
std::string TFrsConfiguration::dE_file = "blank";
std::string TFrsConfiguration::dT_file = "blank";
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
Double_t TFrsConfiguration::fMin_dE_Music1 = 0., TFrsConfiguration::fMax_dE_Music1 = 4000.;
Double_t TFrsConfiguration::fMin_dE_Music2 = 0., TFrsConfiguration::fMax_dE_Music2 = 4000.;
Double_t TFrsConfiguration::fMin_dE_travMus_gate = 0., TFrsConfiguration::fMax_dE_travMus_gate = 30000.;

//travMUSIC
Double_t TFrsConfiguration::fMin_dE_travMusic = 0., TFrsConfiguration::fMax_dE_travMusic = 60000.;
int TFrsConfiguration::frun_num = 0;

TFrsConfiguration::TFrsConfiguration()
{
    ReadScalerNames();
    //ReadTravMusDriftFile();
    //ReadAoQDriftFile();
    //ReadZ1DriftFile();
    // ReadScidEFile();
    // ReadScidTFile();
    ReadCrateMapFile();
    // for now:
    sci_names[0] = "sci21";
    sci_names[1] = "sci22";
    sci_names[2] = "sci41";
    sci_names[3] = "sci42";
    sci_names[4] = "sci43";
    sci_names[5] = "sci81";
    
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

    if (travmus_drift_coeff_file.fail()) c4LOG(fatal, "Could not open Trav Mus drift coefficients file.");


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

    if (AoQ_drift_coeff_file.fail()) c4LOG(fatal, "Could not open AoQ drift coefficients file.");


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

    if (Z1_drift_coeff_file.fail()) c4LOG(fatal, "Could not open Z1 drift coefficients file.");


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


void TFrsConfiguration::ReadScidEFile()
{
    std::ifstream file (dE_file);
    std::string line;

    if (file.fail()) c4LOG(fatal, "Could not open Sci dE mapping file.");

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss(line);

        std::string signal;
        int channel;

        iss >> signal;

        if (isdigit(signal[0])) { std::cout << "Error in Sci dE mapping file. Row begin with a string." << std::endl; return; }
        else
        {
            iss >> channel;

            if (signal == "GEO") sci_dE_geo = channel;
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

        }
    }

    dE_mapping_loaded = 1;
    file.close();
    
    return;   
}

void TFrsConfiguration::ReadScidTFile()
{
    std::ifstream file (dT_file);
    std::string line;

    if (file.fail()) c4LOG(fatal, "Could not open Sci dT mapping file.");

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss(line);

        std::string signal;
        int channel;

        iss >> signal;

        if (isdigit(signal[0])) { std::cout << "Error in Sci dT mapping file. Row begin with a string." << std::endl; return; }
        else
        {
            iss >> channel;

            if (signal == "GEO") sci_dT_geo = channel;
            else if (signal == "dT_21L_21R") dt_21l_21r_ch = channel;
            else if (signal == "dT_41L_41R") dt_41l_41r_ch = channel;
            else if (signal == "dT_42L_42R") dt_42l_42r_ch = channel;
            else if (signal == "dT_43L_43R") dt_43l_43r_ch = channel;
            else if (signal == "dT_81L_81R") dt_81l_81r_ch = channel;
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

        }
    }

    dT_mapping_loaded = 1;
    file.close();
    
    return;   
}


void TFrsConfiguration::ReadCrateMapFile()
{
    std::ifstream file (crate_map_file);
    std::string line;

    if (file.fail()) c4LOG(fatal, "Could not open FRS Crate Mapping mapping file.");

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss(line);

        std::string signal;
        int channel;

        iss >> signal;

        if (isdigit(signal[0])) { std::cout << "Error in FRS Crate Mapping file. Row begins with a string." << std::endl; return; }
        else
        {
            iss >> channel;
            
            if (signal == "MUSIC_E_GEO") music_e_geo = channel;
            else if (signal == "DE_GEO") sci_dE_geo = channel;
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
            else if (signal == "DT_GEO") sci_dT_geo = channel;
            else if (signal == "dT_21L_21R") dt_21l_21r_ch = channel;
            else if (signal == "dT_41L_41R") dt_41l_41r_ch = channel;
            else if (signal == "dT_42L_42R") dt_42l_42r_ch = channel;
            else if (signal == "dT_43L_43R") dt_43l_43r_ch = channel;
            else if (signal == "dT_81L_81R") dt_81l_81r_ch = channel;
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

        }
    }

    dT_mapping_loaded = 1;
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

void TFrsConfiguration::Set_dE_Music1_range(Double_t min, Double_t max)
{
    fMin_dE_Music1 = min;
    fMax_dE_Music1 = max;
}
void TFrsConfiguration::Set_dE_Music2_range(Double_t min, Double_t max)
{
    fMin_dE_Music2 = min;
    fMax_dE_Music2 = max;
}

void TFrsConfiguration::Set_dE_travMusic_gate(Double_t min, Double_t max)
{
    fMin_dE_travMus_gate = min;
    fMax_dE_travMus_gate = max;
}



// read files and stuff