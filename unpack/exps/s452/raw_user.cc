#include "config/setup.hh"
#include "config/map_structures.hh"

// ucesb
#include "structures.hh"

// c++
#include <math.h>
#include <stdint.h>
#include <algorithm>
#include <iterator>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <bitset>
#include <cstdlib>
#include <unistd.h>

bPlast_Map load_bPlast_allocation(std::ifstream& file)
{
    bPlast_Map map;

    for (int i = 0; i < BPLAST_TAMEX_MODULES; i++)
    {
        for (int j = 0; j < BPLAST_TAMEX_CHANNELS; j++)
        {   
            map.TAMEX_bPlast_Chan[i][j] = 0;
            map.TAMEX_bPlast_Det[i][j] = 0;
        }
    }

    int bPlastTamID = 0;
    int bPlastTamCh = 0;
    int bPlast_det = 0;
    int bPlast_ch = 0;

    std::string line;
    const char* format =  "%d %d %d %d";

    while (file.good())
    {
        getline(file, line, '\n');
        if (line[0] == '#') continue;

        sscanf(line.c_str(), format, &bPlastTamID, &bPlastTamCh, &bPlast_det, &bPlast_ch);

        map.TAMEX_bPlast_Det[bPlastTamID][bPlastTamCh] = bPlast_det;
        map.TAMEX_bPlast_Chan[bPlastTamID][bPlastTamCh] = bPlast_ch;

    }

    return map;

}


void raw_user_function(unpack_event *event, raw_event *raw_event)
{   

    /*if (FRS_USED)
    {   
       
        int multihit = 0;
        int nhit_v1290[32][2];
        for (int i = 0; i < 32; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                nhit_v1290[i][j] = 0;
            }
        }

        // first loop = 32. this is multi hit.
        // we will discard anything above 9 (>=10)
        // but we can have up to 32 i suppose?
        // second loop is the channel, i guess. again 32.
        // maybe we don't need 2 loops, just 2 indices?
        for (int i = 0; i <32; i++)
        {
            int chn = event->frs_main_crate.v1290.channel._items[i].value;
            int lot = event->frs_main_crate.v1290.leadOrTrail._items[i].value;
            int value = event->frs_main_crate.v1290.data._items[chn][i].value;
            multihit = nhit_v1290[chn][lot];

            if (multihit > 9)
            {
                continue;
            }

            if (lot == 0)
            {
                if (value > 0)
                {
                    raw_event->lead.vtn[chn][multihit] = value;
                }
            }
            else
            {
                if (value > 0)
                {
                    raw_event->trail.vtn[chn][multihit] = value;
                }
            }
        }
        
        // frs mapping


    }*/

    if (FRS_USED)
    {   

        // I think perhaps "sorting" can mostly be done here, rather than having this function.?


        // can probably skip a step here (unpack -> sort seems to just set these as equal anyway)
        /*raw_event->TRIGGER = event->frs_tpat.data.frs_info.trigger;
        raw_event->PATTERN = event->frs_tpat.data.frs_info.pattern;
        raw_event->SPTRIGGER = event->frs_tpat.data.frs_info.sptrigger;
        raw_event->SNBTRIG = event->frs_tpat.data.frs_info.snbtrig; 
        raw_event->SMAXTRIG = event->frs_tpat.data.frs_info.smaxtrig;
        

        for (int i = 0; i < 32; i++)
        {
            raw_event->SCLONG[i] = event->frs_crate.data.frs_info.scaler_frs[i];
            raw_event->SCLONG[i+32] = event->frs_main_crate.data.frs_info.scaler_main[i]; 
        }*/

    }

    if (GERMANIUM_USED)
    {
        /*// germanium mapping
        raw_event->GeFired = event->germanium.data.febex_info.Ge_Fired;
        // for (int i = 0; i < raw_event->GeFired; i++)
        for (int i = 0; i < 28; i++)
        {
            raw_event->Sum.Time.lo[i] = event->germanium.data.febex_info.Sum_Time_lo[i];
            raw_event->Sum.Time.hi[i] = event->germanium.data.febex_info.Sum_Time_hi[i];
            raw_event->Hit.Pattern[i] = event->germanium.data.febex_info.Hit_Pattern[i];
            raw_event->Chan.Time.lo[i] = event->germanium.data.febex_info.Chan_Time_lo[i];
            raw_event->Chan.Time.hi[i] = event->germanium.data.febex_info.Chan_Time_hi[i];
            raw_event->Chan.Energy[i] = event->germanium.data.febex_info.Chan_Energy[i]; 
            raw_event->Chan.CF.lo[i] = event->germanium.data.febex_info.Chan_CF_lo[i];
            raw_event->Chan.CF.hi[i] = event->germanium.data.febex_info.Chan_CF_hi[i];
            raw_event->Pileup[i] = event->germanium.data.febex_info.Pileup[i];
            raw_event->Overflow[i] = event->germanium.data.febex_info.Overflow[i];
            raw_event->det.ids[i] = event->germanium.data.febex_info.det_ids[i];
            raw_event->crystal.ids[i] = event->germanium.data.febex_info.crystal_ids[i];       
        }*/
    }

    if (FATIMA_USED)
    {
        // fatima vme mapping
        // fatima tamex mapping
    }

    if (BPLAST_USED)
    {   
        
        std::ifstream bfile("s452/config/bPlast_TAMEX_allocation.txt");
        bPlast_Map map = load_bPlast_allocation(bfile); 

        
        // only 3 (or number of tamex modules?) in go4, but keeping 4 for consistency for now....
        int Phys_Channel_Lead_bPlas[4][BPLAST_CHAN_PER_DET];
        // 3+1 for modules....the go4 code is insane.
        int bPlast_PMT_Lead_N[BPLAST_TAMEX_MODULES+1][BPLAST_CHAN_PER_DET];
        for (int i = 0; i < BPLAST_TAMEX_MODULES+1; i++)
        {
            for (int j = 0; j < BPLAST_CHAN_PER_DET; j++)
            {
                bPlast_PMT_Lead_N[i][j] = 0;
            }
        }
        

        // loop through tamex_iter (set to for now but maybe can be variable)
        for (int i = 0; i < 4; i++) 
        {   

            //raw_event->amFired[i] = event->plastic.data.plastic_info.am_fired[i];
            int chan = -1;
            int detNum = -1;
            // loop through however many fired at amFired[i]
            for (int j = 0; j < event->plastic.data.plastic_info.am_fired[i]; j++)
            {   
                // is this the correct variable?
                if (j < PLASTIC_MAX_ITER)
                {   
                    // lead odd, trail even
                    if (event->plastic.data.plastic_info.ch_ID_edge[i][j] % 2 == 1)
                    {   
                    
                        Phys_Channel_Lead_bPlas[i][j] = map.TAMEX_bPlast_Chan[i][((event->plastic.data.plastic_info.ch_ID_edge[i][j]+1)/2-1)];
                        chan = Phys_Channel_Lead_bPlas[i][j];

                        if (chan > -1)
                        {   
                            detNum = map.TAMEX_bPlast_Det[i][((event->plastic.data.plastic_info.ch_ID_edge[i][j]+1)/2-1)];
                            //raw_event->bPlastDetNum = detNum; // should this be passed along? 
                            //raw_event->bPlastChan[detNum] = chan; // "..." 
                            bPlast_PMT_Lead_N[detNum][chan]++;
                            //raw_event->bPlastPMTLeadN[detNum][chan] = bPlast_PMT_Lead_N[detNum][chan];
                            int N1 = bPlast_PMT_Lead_N[detNum][chan];
                            if (N1 > 100) // BPLAST_TAMEX_HITS
                            {
                                N1 = -1;
                            }
                            if (N1 > -1 && N1 < 100)
                            {   
                                //if ((event->plastic.data.plastic_info.edge_coarse[i][j]-event->plastic.data.plastic_info.edge_fine[i][j]) > 0)
                                //{   
                                //    std::cout << "not zero raw_user: det - " << i << " - chan - " << j << std::endl;
                                //    std::cout << "hello " << (event->plastic.data.plastic_info.edge_coarse[i][j]-event->plastic.data.plastic_info.edge_fine[i][j]) << std::endl;
                                //}
                                raw_event->bPlastPMTLead[detNum][chan][N1] = (event->plastic.data.plastic_info.edge_coarse[i][j]-event->plastic.data.plastic_info.edge_fine[i][j]);
                            }

                        }   

                    }
                }
            }
        }

    }

    if (AIDA_USED)
    {
        // aida mapping
    }

}