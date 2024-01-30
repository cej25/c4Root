// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FrsVFTXData.h"
#include "FrsVFTXReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include <vector>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h" 
    #include "ext_h101_frsvftx.h"
}

FrsVFTXReader::FrsVFTXReader(EXT_STR_h101_frsvftx_onion* data, size_t offset)
    :   c4Reader("FrsVFTXReader")
    ,   fNEvent(0)
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   fArray(new TClonesArray("FrsVFTXData"))
{
}

FrsVFTXReader::~FrsVFTXReader()
{
    if (fArray != nullptr) delete fArray;
    c4LOG(info, "Destroyed FrsVFTXReader properly.");
}

Bool_t FrsVFTXReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;

    c4LOG(info, "");
    
    EXT_STR_h101_frsvftx_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_frsvftx, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    FairRootManager::Instance()->Register("FrsVFTXData", "FRS VFTX Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    c4LOG(info, "FrsVFTXReader init complete.");

    return kTRUE;
}

Bool_t FrsVFTXReader::Read()
{
    c4LOG(debug1, "Event data");

    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;

    // do the reading

    uint32_t chn_first_hit = 0;
    uint32_t next_chn_first_hit, hits;
    Bool_t trailing;
    Int_t channel;
    Float_t cc, ft;
    Double_t r, ti;

    for (Int_t i = 0; i < fData->frsvftx_data_vftx_time_coarseM; i++)
    {
        next_chn_first_hit = fData->frsvftx_data_vftx_time_coarseME[i];
        hits = next_chn_first_hit - chn_first_hit;

        for (Int_t j = 0; j < hits; j++)
        {   
            // check if leading somehow
            channel = fData->frsvftx_data_vftx_time_coarseMI[i];
            trailing = channel % 2;
            if ((!trailing) && (vftx_leading_time[channel].size() < VFTX_MAX_HITS))
            {
                cc = fData->frsvftx_data_vftx_time_coarsev[i * 100 + j];
                ft = fData->frsvftx_data_vftx_time_finev[i * 100 + j];
                r = (double)rand.Rndm() - 0.5;
                ti = VFTX_GetTRaw_ps(channel, cc, ft, r);
                vftx_leading_time[channel].emplace_back(ti);
            }
        }
    }


    // CEJ: MTDC and MQDC read but not used by DESPEC
    // ...do nothing for now...


    fNEvent++;
    return kTRUE;
}


void FrsVFTXReader::m_VFTX_Bin2Ps()
{
    int l_VFTX_SN[VFTX_N]  = VFTX_SN;

    for (int i = 0; i < VFTX_N; i++)
    {
        for (int j = 0; j < VFTX_MAX_CHN; j++)
        {
            for (int k = 0; k < 1000; k++)
            {
                VFTX_Bin2Ps[i][j][k]= 0.;
            }
        }
    }

    int b; double ft_ps;
    for (int mod = 0; mod < VFTX_N; mod++)
    {
        for (int ch = 0; ch < VFTX_MAX_CHN; ch++)
        {
            std::ifstream in;
            in.open(Form("Configuration_Files/FRS/VFTX_Calib/VFTX_%05d_Bin2Ps_ch%02d.dat",l_VFTX_SN[mod],ch));
            if (!in.is_open())
            {
                for(int bin=0; bin<1000; bin++)
                {
                    VFTX_Bin2Ps[mod][ch][bin] = 0.; // no data in ps if we don't have the files
                }
            
                printf("WARNING : VFTX %05d ch %02d file not found, you will not have precise data\n",l_VFTX_SN[mod],ch);
            }
            else 
            {
                while(!in.eof()) 
                {
                    in >> b >> ft_ps;
                    VFTX_Bin2Ps[mod][ch][b] = ft_ps;
                    if(b > 1000) printf(" !!! WARNING !!!! file Configuration_Files/VFTX_Calib/VFTX%02d_Bin2Ps_ch%2d.dat, overflow b=%i \n",mod,ch,b);
                } // end of for (ch over VFTX_CHN)
                in.close();
            }
        }//end of for (ch)
    }// end of for (mod over VFTX_N)
    return;
}


// CEJ: module is not needed! There is only 1!
// it is only assigned = 0 in unpacking anyway!
Double_t FrsVFTXReader::VFTX_GetTRaw_ps(int channel, int cc, int ft, float r) 
{
    Double_t gain;
    Double_t calib = (Double_t)VFTX_Bin2Ps[0][channel][ft];

    if (calib == 0) calib = ft;

    if(r < 0) 
    {
        Double_t calib_prev = (Double_t)VFTX_Bin2Ps[0][channel][ft-1];
        gain = calib - calib_prev;
    }
    else 
    {
        Double_t calib_next = (Double_t)VFTX_Bin2Ps[0][channel][ft+1];
        gain = calib_next - calib;
    }

    double ft_ps = calib + gain * (double)r;

    return (5000. * cc - ft_ps);
}


void FrsVFTXReader::ZeroArrays()
{   
    // memset(VFTX_Bin2Ps, 0, sizeof(VFTX_Bin2Ps));
    fArray->Clear();
}

void FrsVFTXReader::ClearVectors()
{
    for (int i = 0; i < 16; i++) vftx_leading_time[i].clear();
}


void FrsVFTXReader::Reset()
{
    ZeroArrays();
    ClearVectors();
}

ClassImp(FrsVFTXReader)