// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "bPlastTamexData.h"
#include "bPlastReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_bplast.h"
}

bPlastReader::bPlastReader(EXT_STR_h101_BPLAST_onion* data, size_t offset)
    : c4Reader("bPlastReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("bPlastTamexData"))
{
}

bPlastReader::~bPlastReader() { delete fArray; }

Bool_t bPlastReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_BPLAST_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_BPLAST, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // initialise calibration arrays

    
    
    // Register output array in a tree
    FairRootManager::Instance()->Register("bPlastTamexData", "bPlast Tamex Data", fArray, !fOnline);
    fArray->Clear();
    
    memset(fData, 0, sizeof *fData);

    return kTRUE;
}
//

Bool_t bPlastReader::bPlasAnalysis()
{
  for (size_t card = 0; card < NCards; card++)
  {
    for (size_t i = 0; i < NChannels; i++)
    {
      calibrations[card][i].min = 0;
      calibrations[card][i].max = 0;
      std::fill(std::begin(calibrations[card][i].lookup),
	  std::end(calibrations[card][i].lookup), 0);
    }
  }
}

Bool_t bPlastReader::LoadCalibrationFiles()
{
  for (size_t card = 0; card < NCards; card++)
  {
    std::cout << "Reading calibration parameters for bPlas card " << card << "..." << std::endl;
    for (size_t i = 0; i < NChannels; i++)
    {
      std::stringstream fpath;
      fpath << "./bPlasCalib/Calib_" << card << "_" << i << ".dat";
      std::ifstream calib;
      calib.open(fpath.str());
      if (calib.fail()) continue;
      calib.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      calib.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      int min = 1024, max = 0;
      while (calib)
      {
	int bin;
	double value;
	calib >> bin >> value;
	if (bin < min) min = bin;
	if (bin > max) max = bin;
	if (value > 1) {
	  throw std::runtime_error("Calibration value seems invalid");
	}
	calibrations[card][i].lookup[bin - 1] = value;
      }
      calibrations[card][i].min = min;
      calibrations[card][i].max = max;
      if (min > max) {
	std::stringstream errbuf;
	errbuf << "Calibration made no sense";
	errbuf << " min=" << min;
	errbuf << " max=" << max;
	throw std::runtime_error(errbuf.str());
      }
    }
  }
}

Bool_t bPlastReader::Read()
{
    c4LOG(debug1, "Event Data");

    std::array<double, NChannels> leads = {0};
    std::array<double, NChannels> trails = {0};
    std::array<double, NChannels> tot = {0};
    std::array<double, NChannels> epoch = {0};

    // Would you look at the time!
    plastic_ts_t = (((uint64_t)fData->plastic_ts_t[3]) << 48) + (((uint64_t)fData->plastic_ts_t[2]) << 32) + (((uint64_t)fData->plastic_ts_t[1]) << 16) + (uint64_t)(fData->plastic_ts_t[0]);

    // BPLAST_TAMEX_MODULES
    for (int det = 0; NCards < 4; det++)
    {   


        struct fineTimeCalib
        {
            int min;
            int max;
            double lookup[600];
        };

        fineTimeCalib calibrations[NCards][NChannels];

        double getFineTime(int card, int channel, int fine, double scale = 5000.)
        {
            if (fine < calibrations[card][channel].min)
                return 0;
            if (fine > calibrations[card][channel].max)
                return scale;
            return (calibrations[card][channel].lookup[fine]) * scale;
        }

        int32_t epoch_base = 0;
        int32_t last_epoch = 0;

        // BPLAST_TAMEX_HITS
        for (int hit = 0; hit < fData->plastic_tamex[det].event_size/4 - 3; hit++) // this will have to change as the variable size is indicated by the variable leading it, we will usually set hits to 5
        {  

            // Time correction

            if (fData->plastic_tamex[det].time_epochv[hit] !=0){
                last_epoch = fData->plastic_tamex[det].time_epochv[hit];
            }
            else{
                if (fData->plastic_tamex[det].time_finev[hit] == 0x3ff) continue;
                int channel = fData->plastic_tamex[det].time_channelv[hit];
                if (channel >= NChannels) continue;

                if (last_epoch != 0){
                    if (epoch_base == 0 && channel == 0){
                        epoch_base = last_epoch;
                    }
                    else if (epoch_base == 0){
                        throw std::runtime_error("Unexpected TDC epoch before trigger");
                    }
                    epoch[channel] = last_epoch - epoch_base;
                    last_epoch = 0;
                }
            }

            // Calculate time event time
            int channel = fData->plastic_tamex[det].time_channelv[hit];
            double time = (epoch[channel] * 1024e4) + fData->plastic_tamex[det].time_coarsev[hit] * 5000 - getFineTime(det, channel, fData->plastic_tamex[det].time_finev[hit]);

            // Leading edge = 1

            if (fData->plastic_tamex[det].time_edgev[hit] == 1){
                leads[channel] = time;
            }

            // Trailing edge = 0

            else {
                if (leads[channel]){
                    trails[channel] = time;
                    tot[channel] = time - leads[channel];
                }

            // Fill TAMEX data arrays

            new ((*fArray)[fArray->GetEntriesFast()]) bPlastTamexData(
                leads[channel],
                trails[channel],
                tot[channel],
                channel,
                epoch[channel],
                fData->plastic_ts_subsystem_id,
                plastic_ts_t
            );

            leads[channel] = 0;
            tot[channel] = 0;
            trails[channel] = 0;
            }
        } 
    }
    fNEvent += 1;
    return kTRUE;    
}


void bPlastReader::Reset()
{
    // reset output array
    fArray->Clear();
}

ClassImp(bPlastReader);