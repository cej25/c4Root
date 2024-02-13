#ifndef FrsVFTXData_H
#define FrsVFTXData_H

#include "TObject.h"
#include "TClonesArray.h"
#include "c4Logger.h"

#include "../../config/frs_config.h"

#include <vector>

class TClonesArray;

class FrsVFTXData : public TObject
{
    public:
        FrsVFTXData();

        FrsVFTXData(std::vector<uint32_t>* vftx_leading_cc,
                    std::vector<uint32_t>* vftx_leading_ft,
                    std::vector<uint32_t>* vftx_leading_time,
                    std::vector<uint32_t>* vftx_trailing_cc,
                    std::vector<uint32_t>* vftx_trailing_ft,
                    std::vector<uint32_t>* vftx_trailing_time);

    
        
        virtual ~FrsVFTXData() {}

        // Getters
        //inline std::vector<uint32_t> Get_vftx_lead_times(int channel) { return fvftx_lead_times[channel]; }
        inline std::vector<uint32_t>* Get_vftx_leading_cc() { return fvftx_leading_cc; }
        inline std::vector<uint32_t>* Get_vftx_leading_ft() { return fvftx_leading_ft; }
        inline std::vector<uint32_t>* Get_vftx_leading_time() { return fvftx_leading_time; }
        inline std::vector<uint32_t>* Get_vftx_trailing_cc() { return fvftx_trailing_cc; }
        inline std::vector<uint32_t>* Get_vftx_trailing_ft() { return fvftx_trailing_ft; }
        inline std::vector<uint32_t>* Get_vftx_trailing_time() { return fvftx_trailing_time; }

        // Setters
        /*
        void Set_vftx_lead_times(int channel, std::vector<uint32_t> vftx_lead_times_channel) { 
            c4LOG_IF(fatal,(channel < 0) || (channel > 31), "Channel index for vftx channel must be between 0-31!" );
            fvftx_lead_times[channel] = vftx_lead_times_channel; 
            }
        */
        /*void Add_vftx_lead_time(int channel, uint32_t value){
            c4LOG_IF(fatal,(channel < 0) || (channel > 31), "Channel index for vftx channel must be between 0-31!" );
            fvftx_lead_times[channel].emplace_back(value);
        }*/
    
    private:

        std::vector<uint32_t> fvftx_leading_cc[VFTX_MAX_CHN];
        std::vector<uint32_t> fvftx_leading_ft[VFTX_MAX_CHN];
        std::vector<uint32_t> fvftx_leading_time[VFTX_MAX_CHN];
        std::vector<uint32_t> fvftx_trailing_cc[VFTX_MAX_CHN];
        std::vector<uint32_t> fvftx_trailing_ft[VFTX_MAX_CHN];
        std::vector<uint32_t> fvftx_trailing_time[VFTX_MAX_CHN];

    public:
        ClassDef(FrsVFTXData, 1)
};


#endif