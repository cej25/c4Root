#ifndef FrsVFTXData_H
#define FrsVFTXData_H

#include "TObject.h"
#include "TClonesArray.h"
#include "c4Logger.h"

#include <vector>

class TClonesArray;

class FrsVFTXData : public TObject
{
    public:
        FrsVFTXData();

        
        virtual ~FrsVFTXData() {}

        // Getters
        inline std::vector<uint32_t> Get_vftx_lead_times(int channel) { return fvftx_lead_times[channel]; }

        // Setters
        /*
        void Set_vftx_lead_times(int channel, std::vector<uint32_t> vftx_lead_times_channel) { 
            c4LOG_IF(fatal,(channel < 0) || (channel > 31), "Channel index for vftx channel must be between 0-31!" );
            fvftx_lead_times[channel] = vftx_lead_times_channel; 
            }
        */
        void Add_vftx_lead_time(int channel, uint32_t value){
            c4LOG_IF(fatal,(channel < 0) || (channel > 31), "Channel index for vftx channel must be between 0-31!" );
            fvftx_lead_times[channel].emplace_back(value);
        }
    
    private:

        std::vector<uint32_t> fvftx_lead_times[32];

    public:
        ClassDef(FrsVFTXData, 1)
};


#endif