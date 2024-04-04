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
    
    EXT_STR_h101_frsvftx_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_frsvftx, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    FairRootManager::Instance()->Register("FrsVFTXData", "FRS VFTX Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FrsVFTXReader::Read()
{
    c4LOG(debug2, "Event data");

    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;

    // do the reading

    Bool_t trailing;
    Float_t cc, ft;
    Double_t r, ti;

   // FrsVFTXData fVFTX_hit;

    int hit_index = 0;
    for (uint32_t channel_index = 0; channel_index < fData->frsvftx_data_vftx_time_coarseM; channel_index++)
    {
        int current_channel = fData->frsvftx_data_vftx_time_coarseMI[channel_index];
        int next_channel_start = fData->frsvftx_data_vftx_time_coarseME[channel_index];
        trailing = current_channel % 2;

        for (uint32_t j = hit_index; j < next_channel_start; j++)
        {   

            if (current_channel < VFTX_MAX_CHN)
            {
                cc = fData->frsvftx_data_vftx_time_coarsev[j];
                ft = fData->frsvftx_data_vftx_time_finev[j];
                r = (double)rand.Rndm() - 0.5;
                ti = VFTX_GetTRaw_ps(current_channel, cc, ft, r);
                if ((!trailing) && (vftx_leading_time[current_channel].size() < VFTX_MAX_HITS))
                {   
                    vftx_leading_cc[current_channel].emplace_back(cc);
                    vftx_leading_ft[current_channel].emplace_back(ft);
                    vftx_leading_time[current_channel].emplace_back(ti);
                }
                else if ((trailing) && (vftx_trailing_time[current_channel].size() < VFTX_MAX_HITS))
                {   
                    vftx_trailing_cc[current_channel].emplace_back(cc);
                    vftx_trailing_ft[current_channel].emplace_back(ft);
                    vftx_trailing_time[current_channel].emplace_back(ti);

                    //std::cout << "size cc reader: " << vftx_trailing_cc[current_channel].size() << std::endl;
                    //std::cout << "size time reader: " << vftx_trailing_time[current_channel].size() << std::endl;
                }

                // CEJ:  JEL changed this? but we need more info
                // we can do it like this if its more optimal?
                // but we should be consistent
                // fVFTX_hit.Add_vftx_lead_time(channel,ti);

                b_vftx_data = true;
            }

            
        }

        hit_index = next_channel_start;
    }
    
    //new ((*fArray)[fArray->GetEntriesFast()]) FrsVFTXData(fVFTX_hit);
    
    if (b_vftx_data)
    {
       new ((*fArray)[fArray->GetEntriesFast()]) FrsVFTXData(
            vftx_leading_cc,
            vftx_leading_ft,
            vftx_leading_time,
            vftx_trailing_cc,
            vftx_trailing_ft,
            vftx_trailing_time
        ); 
    }

    b_vftx_data = false;
    

    // CEJ: MTDC and MQDC read but not used by DESPEC
    // ...do nothing for now...


    fNEvent++;
    return kTRUE;
}




// doing nothing currently
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
    for (int i = 0; i < VFTX_MAX_CHN; i++) vftx_leading_cc[i].clear();
    for (int i = 0; i < VFTX_MAX_CHN; i++) vftx_leading_ft[i].clear();
    for (int i = 0; i < VFTX_MAX_CHN; i++) vftx_leading_time[i].clear();
    for (int i = 0; i < VFTX_MAX_CHN; i++) vftx_trailing_cc[i].clear();
    for (int i = 0; i < VFTX_MAX_CHN; i++) vftx_trailing_ft[i].clear();
    for (int i = 0; i < VFTX_MAX_CHN; i++) vftx_trailing_time[i].clear();
}


void FrsVFTXReader::Reset()
{
    ZeroArrays();
    ClearVectors();
}

ClassImp(FrsVFTXReader)