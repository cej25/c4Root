#ifndef FatimaVmeRaw2Cal_H
#define FatimaVmeRaw2Cal_H

#include "FairTask.h"
#include "FatimaVmeData.h"
#include "FatimaVmeCalData.h"
#include "../../config/setup.h"

#include <vector>
#include <set>
#include <map>



class TClonesArray;
class EventHeader;
class FatimaVmeData;
class FatimaVmeCalData;
//class TimeMachineData;
//class vector;

class FatimaVmeRaw2Cal : public FairTask
{
    public:
        FatimaVmeRaw2Cal();

        FatimaVmeRaw2Cal(const TString& name, Int_t verbose = 1);
        
        virtual ~FatimaVmeRaw2Cal();

        virtual InitStatus Init();

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        double Calibrate_QDC_E(double E, int det_id);
        double Calibrate_QDC_T(unsigned long T, int det_id);
        double Calibrate_TDC_T(unsigned long T, int det_id);

        void Load_QDC_Energy_Calibration_File(TString& filepath);
        void Load_QDC_Time_Calibration_File(TString& filepath);
        void Load_TDC_Time_Calibration_File(TString& filepath);

        void SetOnline(Bool_t option) { fOnline = option; }

    private:

        Bool_t fOnline;
        TClonesArray* fcal_data;
        TClonesArray* funcal_data;

        Int_t fNEvents = 0;
        EventHeader* header;

        // Stuff we need
        std::set<int> extra_signals = {TM_U, TM_D, SC41L_A, SC41R_A, SC41L_D, SC41R_D,
                                    36,37,38,39,40,41,42,43,44,45,46,47,
                                    48,49,50,51};


        // Calibration
        double calib_coeffs_QDC_E[100][5];
        double original_calib_coeffs_QDC_E[100][5];
        double calib_coeffs_TDC_T[100];
        double calib_coeffs_QDC_T[100];

    public:
        ClassDef(FatimaVmeRaw2Cal, 1);

};



#endif