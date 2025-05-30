//WIP
#ifndef LisaAna2Cal_H
#define LisaAna2Cal_H

#include "TClonesArray.h"
#include "EventHeader.h"
#include "TLisaConfiguration.h"
#include "LisaData.h"
#include "LisaCalData.h"
#include "LisaAnaData.h"
#include <map>
#include <vector>
#include "TVector.h"

class EventHeader;
// class LisaData;
// class LisaCalData;
class LisaItem;
class LisaAnaItem;
class LisaCalItem;

class LisaAna2Cal : public FairTask
{
    public:
        LisaAna2Cal();

        virtual ~LisaAna2Cal();

        virtual InitStatus Init();

        virtual void Exec (Option_t* option);

        virtual void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishEvent();
        virtual void FinishTask();

        void PrintDetectorGainM();
        void PrintDetectorGainM_MWD();

    private:
        TLisaConfiguration const* lisa_config;
    
        std::vector<LisaItem> const* lisaArray;
        std::vector<LisaAnaItem> const* lisaAnaArray;
        std::vector<LisaCalItem>* lisaCalArray;

        // TClonesArray* fLisaArray;
        // TClonesArray* fLisaCalArray;
      

        EventHeader* header;
        Bool_t fOnline;
        Int_t fNEvents;

        uint64_t wr_t;

        //int NBoards = 1; 

        //::: Mapping, GM, Calibration
        //std::map<std::pair<int, int>, std::pair<std::pair<int,std::string>, std::pair<int, int>>> detector_mapping; //Debugging.Raplace std:string-> TString ?
        std::map<std::pair<int,int>, std::pair<std::pair<int, std::pair<int, int>>,std::pair<float,std::pair<std::string,std::string>>>> detector_mapping; //Debugging.Raplace std:string-> TString ?

        std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> detector_gain_matching;
        std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> detector_gain_matching_MWD;

        //std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> detector_calibration;

        /*
        std::vector<int> data_boards;
        std::vector<uint32_t> data_channel;
        std::vector<uint32_t> data_energy;
        std::vector<uint32_t> data_traces;
        std::vector<uint32_t> data_multiplicity;
        */

        double slope;
        double intercept;
        float energy_GM;
        float de_dx;
        double slope_MWD;
        double intercept_MWD;
        float energy_MWD_GM;


    public:
        ClassDef(LisaAna2Cal, 1)

};



#endif