/*
At the moment the way to access to the traces (vector of vector) is to source c4
All the other branches work the template read_energy.C

WIP
*/

#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <iostream>
#include "LisaCalData.h"

void read_trace() 
{
    TFile *file = TFile::Open("./run_0075_test-merge.root"); 
    
    TTreeReader reader("evt", file);
    TTreeReaderArray<std::vector<short>> trace(reader, "LisaCalData.trace_febex");
    TTreeReaderArray<LisaCalItem> lItem(reader, "LisaCalData");
    // TTreeReaderArray<Int_t[2000]> Test(reader, "LisaCalData.test[2000]");
    // TTreeReaderValue<EventveHeader> Header(reader, "EventHeader.");
    int k = 0;

    while (reader.Next()) 
    {
        k++;
        // uint evtno = Header->GetEventno();

       // std::cout << "Size 1 :: " << trace.GetSize() << std::endl;
        // std::cout << "size test:: " << Test.GetSize() << std::endl;

        for (auto const & item : lItem)
        {
           ///std::cout << "Size 2 :: " << item.size() << std::endl;
           std::vector<short> tr_x = item.Get_trace_x(); // << std::endl;
	   std::cout << tr_x.size() << std::endl;
	   for (int i = 0; i < tr_x.size(); i++)
           {
		   std::cout << tr_x[i] << "  --  ";
	   }

        }
/*
        for (auto const & t : Test)
      {
            // std::cout << "hello, reading test?" << std::endl;
            // std::cout << t[1] << std::endl;
            for (int j = 0; j < 2000; j++)
            {
                // std::cout << "j:: " << j << " array[i]:: " << t.at(j) << std::endl;
            }

            // std::cout << "hello " << std::endl;
            // std::cout << l.size() << std::endl;

            // std::cout 
        }*/

        // for (auto const&Item : LisaItem)
        // {
            
        //     std::vector<int16_t> trace_y = Item;
        //     std::cout <<  "Size 2 :: " << trace_y.size() << std::endl;
        //     // std::vector<short> trace_x = LisaItem.Get_trace_x();
        //     // uint8_t channel_id = LisaItem.Get_channel_id_traces();

        //     // for ( int i = 0; i < trace_y.size(); i++)
        //     // {
        //     //     if (channel_id == 2)
        //     //     {
        //     //         std::cout << "Trace y: " << trace_y[i] << std::endl;
        //     //         // calculations...
        //     //     }
                
        //     // }
                    
        // }
        
    }
    
    file->Close();
}




