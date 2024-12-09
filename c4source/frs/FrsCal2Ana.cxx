#include "FrsCal2Ana.h"
#include "c4Logger.h"
#include "FrsMainData.h"
#include "FrsMainCalData.h"
#include "FrsHitData.h"
#include "EventData.h"

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "FairTask.h"

#include "TClonesArray.h"
#include "TMath.h"
#include <TMacro.h>
#include <vector>
#include <iostream>
#include <TROOT.h>
#include <chrono>

#define MUSIC_ANA_NEW

FrsCal2Ana::FrsCal2Ana()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   tpatArray(nullptr)   
{
    frs_config = TFrsConfiguration::GetInstance();
    exp_config = TExperimentConfiguration::GetInstance();
    frs = frs_config->FRS();
    mw = frs_config->MW();
    tpc = frs_config->TPC();
    music = frs_config->MUSIC();
    labr = frs_config->LABR();
    sci = frs_config->SCI();
    id = frs_config->ID();
    si = frs_config->SI();
    mrtof = frs_config->MRTOF();
    range = frs_config->Range();
    pathToConfigFiles = frs_config->GetConfigPath();
}

FrsCal2Ana::FrsCal2Ana(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   tpatArray(nullptr)
{
    frs_config = TFrsConfiguration::GetInstance();
    exp_config = TExperimentConfiguration::GetInstance();

    frs = frs_config->FRS();
    mw = frs_config->MW();
    tpc = frs_config->TPC();
    music = frs_config->MUSIC();
    labr = frs_config->LABR();
    sci = frs_config->SCI();
    id = frs_config->ID();
    si = frs_config->SI();
    mrtof = frs_config->MRTOF();
    range = frs_config->Range();
    pathToConfigFiles = frs_config->GetConfigPath();
}

FrsCal2Ana::~FrsCal2Ana()
{   
    c4LOG(info, "Deleting FrsCal2Ana task");
}

InitStatus FrsCal2Ana::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");
    
    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    tpatArray = mgr->InitObjectAs<decltype(tpatArray)>("FrsTpatData");
    c4LOG_IF(fatal, !tpatArray, "Branch FrsTpatData not found!");
    scalerArray = mgr->InitObjectAs<decltype(scalerArray)>("FrsScaLerData");
    c4LOG_IF(fatal, !scalerArray, "Branch FrsScalerArray not found!");
    calSciArray = mgr->InitObjectAs<decltype(calSciArray)>("FrsCalSciData");
    c4LOG_IF(fatal, !calSciArray, "Branch FrsCalSciData not found!");
    musicArray = mgr->InitObjectAs<decltype(musicArray)>("FrsMusicData");
    c4LOG_IF(fatal, !musicArray, "Branch FrsMusicData not found!");
    calTpcArray = mgr->InitObjectAs<decltype(calTpcArray)>("FrsCalTpcData");
    c4LOG_IF(fatal, !calTpcArray, "Branch FrsCalTpcData not found!");

    mgr->RegisterAny("FrsHitData", hitArray, !fOnline);
    mgr->RegisterAny("FrsMultihitData", multihitArray, !fOnline);

   
    return kSUCCESS;
}

// -----   Public method ReInit   ----------------------------------------------
InitStatus FrsCal2Ana::ReInit()
{
    SetParContainers();
    return kSUCCESS;
}

void FrsCal2Ana::Exec(Option_t* option)
{   
    auto start = std::chrono::high_resolution_clock::now();

    if (tpatArray->size() == 0) return;
    fNEvents++;

    auto const & tpatItem = tpatArray->at(0);
    int64_t wr_t = tpatItem.Get_wr_t();
    int16_t tpat = tpatItem.Get_tpat();

    FRS_time_mins = (wr_t - exp_config->exp_start_time) / 60E9;


    ProcessScalers();
    ProcessSciTAC();
    ProcessSciMHTDC();
    ProcessMusic();
    ProcessTpcs();

    ProcessIDs();
    // process other stuff

   
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void FrsCal2Ana::ProcessScalers()
{

}

void FrsCal2Ana::ProcessSciTAC()
{
    
}

void FrsCal2Ana::ProcessSciMHTDC()
{
    
}

void FrsCal2Ana::ProcessMusic()
{
    
}

void FrsCal2Ana::ProcessTpcs()
{
    
}

void FrsCal2Ana::ProcessIDs()
{
    
}



void FrsCal2Ana::Setup_Conditions(std::string path_to_config_files)
{
    std::string line;
    int line_number = 0;

    const char* format = "%f %f %f %f %f %f %f %f %f %f %f %f %f %f";

    std::ifstream cond_a(path_to_config_files +  TString("lim_csum.txt"));

    while(/*cond_a.good()*/getline(cond_a,line,'\n'))
    {
        if(line[0] == '#') continue;


            sscanf(line.c_str(),format,&lim_csum[line_number][0][0],&lim_csum[line_number][0][1]
                        ,&lim_csum[line_number][1][0],&lim_csum[line_number][1][1]
                        ,&lim_csum[line_number][2][0],&lim_csum[line_number][2][1]
                        ,&lim_csum[line_number][3][0],&lim_csum[line_number][3][1]
                        ,&lim_csum[line_number][4][0],&lim_csum[line_number][4][1]
                        ,&lim_csum[line_number][5][0],&lim_csum[line_number][5][1]
                        ,&lim_csum[line_number][6][0],&lim_csum[line_number][6][1]);

        line_number++;

    }

    line_number = 0;

    format = "%f %f";

    std::ifstream cond_b(path_to_config_files +  TString("lim_xsum.txt"));

    while(/*cond_b.good()*/getline(cond_b,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&lim_xsum[line_number][0],&lim_xsum[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f";

    std::ifstream cond_c(path_to_config_files +  TString("lim_ysum.txt"));

    while(/*cond_c.good()*/getline(cond_c,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&lim_ysum[line_number][0],&lim_ysum[line_number][1]);

        line_number++;
    }

    /*** MUSIC Conditions *** */

    line_number = 0;

    format = "%f %f %f %f";

    std::ifstream cond_d(path_to_config_files +  TString("MUSIC1.txt"));

    while(/*cond_d.good()*/getline(cond_d,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic1_E[line_number][0],&cMusic1_E[line_number][1],&cMusic1_T[line_number][0],&cMusic1_T[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f %f %f";

    std::ifstream cond_e(path_to_config_files +  TString("MUSIC2.txt"));

    while(/*cond_e.good()*/getline(cond_e,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic2_E[line_number][0],&cMusic2_E[line_number][1],&cMusic2_T[line_number][0],&cMusic2_T[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f %f %f";

    std::ifstream cond_f(path_to_config_files +  TString("MUSIC3.txt"));

    while(/*cond_f.good()*/getline(cond_f,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic3_E[line_number][0],&cMusic3_E[line_number][1],&cMusic3_T[line_number][0],&cMusic3_T[line_number][1]);

        line_number++;
    }

    line_number = 0;

    format = "%f %f";

    std::ifstream cond_g(path_to_config_files +  TString("MUSIC_dEc3.txt"));

    while(/*cond_g.good()*/getline(cond_g,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cMusic3_dec[0],&cMusic3_dec[1]);
    }

    /***SCINTILATOR Condtions***/

    line_number = 0;

    format = "%f %f";

    std::ifstream cond_h(path_to_config_files +  TString("SCI_Cons.txt"));

    while(/*cond_h.good()*/getline(cond_h,line,'\n'))
    {

        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cSCI_L[0],&cSCI_L[1]);

        getline(cond_h,line,'\n');
            sscanf(line.c_str(),format,&cSCI_R[0],&cSCI_R[1]);

        getline(cond_h,line,'\n');
            sscanf(line.c_str(),format,&cSCI_E[0],&cSCI_E[1]);

        getline(cond_h,line,'\n');
            sscanf(line.c_str(),format,&cSCI_Tx[0],&cSCI_Tx[1]);

        getline(cond_h,line,'\n');
            sscanf(line.c_str(),format,&cSCI_X[0],&cSCI_X[1]);

    }

    format = "%f %f";

    std::ifstream cond_i(path_to_config_files +  TString("SCI_LLRR.txt"));
    c4LOG_IF(fatal, !cond_i.is_open(), "Failed to open SCI_LLRR config file");
    while(cond_i.good())
    {
        getline(cond_i,line,'\n');
        if(line[0] == '#') continue;
        sscanf(line.c_str(),format,&cSCI_LL2[0],&cSCI_LL2[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR2[0],&cSCI_RR2[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_LL3[0],&cSCI_LL3[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR3[0],&cSCI_RR3[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_LL4[0],&cSCI_LL4[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR4[0],&cSCI_RR4[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_LL5[0],&cSCI_LL5[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR5[0],&cSCI_RR5[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_LL6[0],&cSCI_LL6[1]);
        getline(cond_i,line,'\n');
        sscanf(line.c_str(),format,&cSCI_RR6[0],&cSCI_RR6[1]);

        break;

    }

    /***ID Condtions***/

    format = "%f %f";

    std::ifstream cond_k(path_to_config_files +  TString("ID_x2.txt"));


    while(/*cond_k.good()*/getline(cond_k,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cID_x2[0],&cID_x2[1]);
    }

    std::ifstream cond_l(path_to_config_files +  TString("ID_x4.txt"));

    while(/*cond_l.good()*/getline(cond_l,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cID_x4[0],&cID_x4[1]);
    }

    std::ifstream cond_m(path_to_config_files +  TString("ID_Z_Z.txt"));

    while(/*cond_m.good()*/getline(cond_m,line,'\n'))
    {
        if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&cID_Z_Z[0],&cID_Z_Z[1]);
    }

    conditions_files_read = true;

}

// not used in FRS Go4?
void FrsCal2Ana::FRS_GainMatching()
{
    std::ifstream file;
    std::string line;
    Float_t frs_wr_a;
    Float_t frs_wr_b;
    Float_t frs_wr_i;
    Float_t frs_wr_j;
    Float_t z1_shift_value;
    Float_t z2_shift_value;
    Float_t aoq_shift_value;
    Float_t aoq_shift_tpc_value;
    Float_t aoq_shift_sci21_value;
    Float_t aoq_shift_sci22_value;

    int f = 0;
    int d = 0;
    
    file.open("../../config/frs/NovTest/Z1_Z2_Shift.txt");
    while (file.good())
    {
        getline(file, line, '\n');
        if (line[0] == '#') continue;
        sscanf(line.c_str(), "%f %f %f %f", &frs_wr_a, &frs_wr_b, &z1_shift_value, &z2_shift_value);
        FRS_WR_a[f] = frs_wr_a;
        FRS_WR_b[f] = frs_wr_b;
        Z1_shift_value[f] = z1_shift_value;
        Z2_shift_value[f] = z2_shift_value;
        Z_Shift_array = f;
        f++;
    }
    file.close();

    file.open("../../config/frs/NovTest/AoQ_Shift.txt");
    while (file.good())
    {
        getline(file, line, '\n');
        if (line[0] == '#') continue;
        sscanf(line.c_str(), "%f %f %f %f %f", &frs_wr_i, &frs_wr_j, &aoq_shift_tpc_value, &aoq_shift_sci21_value, &aoq_shift_sci22_value);
        FRS_WR_i[d] = frs_wr_i;
        FRS_WR_j[d] = frs_wr_j;
        AoQ_shift_TPC_value[d] = aoq_shift_tpc_value;
        AoQ_shift_Sci21_value[d] = aoq_shift_sci21_value;
        AoQ_shift_Sci22_value[d] = aoq_shift_sci22_value;
        AoQ_Shift_array = d;
        d++;
    }
    file.close();

}

Bool_t FrsCal2Ana::Check_WinCond(Float_t P, Float_t* V)
{
    if (P >= V[0] && P <= V[1]) return true;
    else return false;
}

Bool_t FrsCal2Ana::Check_WinCond_Multi(Float_t P, Float_t V[8][2], int cond_num)
{
    if (P >= V[cond_num][0] && P <= V[cond_num][1]) return true;
    else return false;
}

Float_t FrsCal2Ana::rand3()
{
    return random3.Uniform(-0.5,0.5);
}


void FrsCal2Ana::FinishEvent()
{
    
}

void FrsCal2Ana::FinishTask()
{
    c4LOG(info, Form("Wrote %i events. ", fNEvents));
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents);
}

ClassImp(FrsCal2Ana)
