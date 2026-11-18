#ifndef FatimaRaw2Cal_H
#define FatimaRaw2Cal_H

#include "FairTask.h"
#include "TFatimaTwinpeaksConfiguration.h"
#include "TClonesArray.h"
#include <array>
#include <cstdint>
#include <string>
#include <vector>

class TClonesArray;
class EventHeader;
class FatimaTwinpeaksData;
class FatimaTwinpeaksCalData;
class TimeMachineData;
class FatimaVmeCalibrator;

class FatimaRaw2Cal : public FairTask
{
    public:
        FatimaRaw2Cal();

        FatimaRaw2Cal(const TString& name, Int_t verbose);

        ~FatimaRaw2Cal();

        void PrintDetectorMap();
        void PrintDetectorCal();

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online){fOnline = set_online;}

        // Select FATIMA processing modes; independent of generic reader setup.
        void Electronics(const std::string& first, const std::string& second = "");
        void Electronics(const std::vector<std::string>& readouts);

        // Compatibility with existing validation macros.
        // Use generic V1751/V1290 inputs for FATIMA VME calibration.
        // Can be enabled alongside UseTamexRawInput().
        void UseVmeRawInput() { fUseVmeRaw = true; }

        virtual void SetParContainers();

        virtual InitStatus Init();

        void SetMultiplicityFilter(bool v, int s){ApplyMultiplicityCondition = v; MultiplicityGate = s;}

        // Opt in to the generic TAMEX Raw branch. Omit the file only when
        // CalibrateTamexFineTimeOnline is also called before Init().
        void UseTamexRawInput(std::uint16_t procid, const TString& fine_time_histograms = "");
        // Learn from leading edges in the first N events, then reconstruct
        // subsequent events. Output uses legacy ROOT histogram names.
        void CalibrateTamexFineTimeOnline(const TString& output_file, std::uint64_t events_to_collect);

        int CountMultiplicity(TClonesArray *);


    private:
        void ProcessTamex();
        void BuildTamexLegacyHits();
        void AccumulateTamexFineTime();
        void FinaliseTamexFineTime();
        void WriteTamexFineTimeHistograms();

        TFatimaTwinpeaksConfiguration const* fatima_configuration;

        Bool_t fOnline;

        TClonesArray* fcal_data;
        TClonesArray* funcal_data;
        TClonesArray* ftime_machine_array;

        bool fUseVmeRaw = false;
        FatimaVmeCalibrator* fVmeProcessor = nullptr; //! Owned transient calibration helper
        bool fUseTamexRaw = false;
        std::uint16_t fTamexProcId = 0;
        TString fTamexFineTimeFile;
        TString fTamexFineTimeOutput;
        bool fTamexCalibrateOnline = false;
        bool fTamexCalibrationReady = false;
        std::uint64_t fTamexCalibrationEvents = 0;
        std::uint64_t fTamexEventsSeen = 0;
        std::vector<std::array<std::uint64_t, 1024>> fTamexFineCounts; //! board*33 + channel
        TClonesArray* fTamexInput = nullptr; //! Borrowed from FairRootManager
        TClonesArray* fTamexLegacyHits = nullptr; //! Owned transient compatibility hits
        std::vector<std::array<double, 1024>> fTamexFineTimes; //! per (board*33 + channel)


        FatimaTwinpeaksData* funcal_hit;
                
        FatimaTwinpeaksData* funcal_hit_next;
        FatimaTwinpeaksCalData* fcal_hit;

        uint16_t detector_id;
        
        int64_t slow_lead_epoch;
        double slow_lead_time;
        int64_t slow_trail_epoch;
        double slow_trail_time;

        int64_t fast_lead_epoch;
        double fast_lead_time;
        int64_t fast_trail_epoch;
        double fast_trail_time;

        double fast_ToT;
        double slow_ToT;

        uint64_t absolute_event_time;

        double energy;

        bool ApplyMultiplicityCondition = false;
        int MultiplicityGate = 2;

        int fNunmatched = 0;

        EventHeader * header;
        Int_t fNEvents = 0;
        Int_t fExecs = 0;
        int total_time_microsecs = 0;

        double a0,a1,a2,a3;

    public:
        ClassDef(FatimaRaw2Cal, 2);
};

#endif

