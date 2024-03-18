#ifndef FatimaVmeRaw2Cal_H
#define FatimaVmeRaw2Cal_H

#include "FairTask.h"
#include "FatimaVmeData.h"
#include "FatimaVmeCalData.h"
#include "TimeMachineData.h"
#include "../../config/setup.h"

#include <vector>
#include <set>
#include <map>



class TClonesArray;
class EventHeader;
class FatimaVmeData;
class FatimaVmeCalData;
class TimeMachineData;

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

        void SetOnline(Bool_t option) { fOnline = option; }

    private:

        TFatimaVmeConfiguration const* fatima_vme_config;

        Bool_t fOnline;
        TClonesArray* fcal_data;
        TClonesArray* funcal_data;
        TClonesArray* fTimeMachineArray;

        Int_t fNEvents = 0;
        EventHeader* header;

        // Stuff we need
        std::set<int> extra_signals;

        int tm_undelayed;
        int tm_delayed;
        int sc41l;
        int sc41r;

        // Calibration
        // double calib_coeffs_QDC_E[100][5];
        // double original_calib_coeffs_QDC_E[100][5];
        // double calib_coeffs_TDC_T[100];
        // double calib_coeffs_QDC_T[100];

        double** calib_coeffs_QDC_E;
        double** original_calib_coeffs_QDC_E;;
        double* calib_coeffs_TDC_T;
        double* calib_coeffs_QDC_T;

    public:
        ClassDef(FatimaVmeRaw2Cal, 1);

};



#endif
