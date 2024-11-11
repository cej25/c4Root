#include <TChain.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>

struct Entry
{
    int64_t time;
    std::string system;
};

void AnalyseTimeStitch()
{

    TChain EventChain("evt");
    EventChain.Add("~/lustre/gamma/s100_nearline/trees/new_trees/162Eu_new_0015_0015_tree.root"); // lets see
        
    TTreeReader tr(&EventChain);
    
    // Branches
    TTreeReaderArray<FatimaTwinpeaksCalData> fatima(tr, "FatimaTwinpeaksCalData");
    TTreeReaderArray<bPlastTwinpeaksCalData> bplast(tr, "bPlastTwinpeaksCalData");
    TTreeReaderArray<GermaniumCalData> germanium(tr, "GermaniumCalData");
    TTreeReaderArray<BGOTwinpeaksCalData> bgo(tr, "BGOTwinpeaksCalData");
    TTreeReaderArray<FrsHitItem> frs(tr, "FrsHitData"); // ignore frs events for now? remake trees? god damn it
    TTreeReaderArray<AidaHit> decays(tr, "AidaDecayHits");
    TTreeReaderArray<AidaHit> implants(tr, "AidaImplantHits");
   

    // Histograms
    TH1F* h1_event_time_distribution; // = new TH1F(); 

    // Variables
    std::vector<Entry> event_times;
    bool decay_found = false;
    int count = 0;
    int frs_events = 0;
    int weird_stitching_events = 0;
    int aida_bad = 0;

    while (tr.Next())
    {

        if (frs.GetSize() > 0) 
        {   
            frs_events++;
            continue;
        }

        for (int i = 0; i < fatima.GetSize(); i++)
        {   
            FatimaTwinpeaksCalData hit  = (FatimaTwinpeaksCalData)fatima[0];
            Entry e;
            e.time =  hit.Get_wr_t();
            e.system = "Fatima";
            event_times.emplace_back(e);
            break;
        }

        for (int i = 0; i < bplast.GetSize(); i++)
        {   
            bPlastTwinpeaksCalData hit  = (bPlastTwinpeaksCalData)bplast[0];
            Entry e;
            e.time =  hit.Get_wr_t();
            e.system = "bPlast";
            event_times.emplace_back(e);
            break;
        }

        for (int i = 0; i < bgo.GetSize(); i++)
        {   
            BGOTwinpeaksCalData hit  = (BGOTwinpeaksCalData)bgo[0];
            Entry e;
            e.time =  hit.Get_wr_t();
            e.system = "BGO";
            event_times.emplace_back(e);
            break;
        }

        for (int i = 0; i < germanium.GetSize(); i++)
        {   
            GermaniumCalData hit  = (GermaniumCalData)germanium[0];
            Entry e;
            e.time =  hit.Get_wr_t();
            e.system = "Germanium";
            event_times.emplace_back(e);
            break;
        }

        for (int i = 0; i < decays.GetSize(); i++)
        {   
            AidaHit hit  = (AidaHit)decays[0];
            Entry e;
            e.time =  hit.Time - 14000;
            e.system = "Aida Decay";
            event_times.emplace_back(e);
            decay_found = true;
            break;
        }

        if (!decay_found)
        {
            for (int i = 0; i < implants.GetSize(); i++)
            {   
                AidaHit hit  = (AidaHit)implants[0];
                Entry e;
                e.time =  hit.Time - 14000;
                e.system = "Aida Implant";
                event_times.emplace_back(e);
                break;
            }
        }
       

        std::sort(event_times.begin(), event_times.end(), [](const Entry &a, const Entry &b)
            { return a.time < b.time; });

        if (event_times.size() > 1)
        {   
            int64_t last_time = event_times.front().time;
            for (int i = 1; i < event_times.size(); i++)
            {
                if (event_times[i].time - last_time > 2500) 
                {
                    weird_stitching_events++;
                    //if (event_times[i].system == "Aida Implant" || event_times[i].system == "Aida Decay") aida_bad++;
                    for (int j = 0; j < event_times.size(); j++)
                    {
                        if (event_times[j].system == "Aida Implant" || event_times[j].system == "Aida Decay")
                        {
                            aida_bad++;
                            break;
                        }
                    }
                    break;
                }

                last_time = event_times[i].time;
            }


            int64_t event_length = event_times.back().time - event_times.front().time;
            // std::cout << "event duration: " << dt << " nanoseconds" << std::endl;


            // if (event_length > 200000)
            // {
            //     std::cout << "Long event! " << std::endl;
            //     for (int i = 0; i < event_times.size(); i++)
            //     {
            //         std::cout << "System: " <<  event_times[i].system << " Time: " << event_times[i].time << std::endl;
            //     }
            // }

        }
       
        decay_found = false;
        event_times.clear();
        count++;

    } // tree reader loop

    std::cout << "Events with gaps of > 2.5 microseconds: " << weird_stitching_events <<  std::endl;
    std::cout << "AIDA's fault.. " << aida_bad << std::endl;
    std::cout << "Total non FRS events: " << count << std::endl;
    std::cout << "FRS events: " << frs_events << std::endl;

}