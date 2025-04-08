// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRun.h"
#include "FairRuntimeDb.h"

// c4
#include "H10MCPNearlineSpectra.h"
#include "EventHeader.h"

#include "c4Logger.h"
#include "AnalysisTools.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TFile.h"
#include "TRandom.h"
#include <chrono>
#include <sstream>

  //std::string rootRunname = Runname + ".root";
std::string Runname =   "test" 	;	//outputfile
H10MCPNearlineSpectra::H10MCPNearlineSpectra() : H10MCPNearlineSpectra("H10MCPNearlineSpectra")
{
    mcp_config = TH10MCPConfiguration::GetInstance();
}

H10MCPNearlineSpectra::H10MCPNearlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fNEvents(0)
    , header(nullptr)
    , fHitsMCP(NULL)
{    
    mcp_config = TH10MCPConfiguration::GetInstance();
}

H10MCPNearlineSpectra::~H10MCPNearlineSpectra()
{
    // delete
}


InitStatus H10MCPNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    // FairRunAna* run = FairRunAna::Instance();
    // run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitsMCP = (TClonesArray*)mgr->GetObject("H10MCPTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitsMCP, "Branch H10MCPTwinpeaksCalData not found!");
    
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_mcp = gDirectory->mkdir("MCPs");
    gDirectory->cd("MCPs");

    h1_test_histogram = MakeTH1(dir_mcp, "F", "h1_test_histogram", "TEST HIST", 10000, -1000000, 1000000);  
   TH2F* histogram2 = new TH2F("hist", "Heatmap", 1000, -10000, 10000,1000, -10000, 10000);
   TH1F *histogram = new TH1F("time difference", "TDiff Distribution", 1000, -200000, -150000);

 //   h1_time = MakeTH1(dir_mcp, "F", "MCPtimediff", "TEST HIST2", 1000, -1000000, 100000);
  //  h2_mcp1 = MakeTH1(dir_mcp, "F", "Heatmapmcp1", "TEST HIST", 1000, -1000000, 10000000,1000, -1000000, 10000000);
  //  h2_mcp2 = MakeTH1(dir_mcp, "F", "Heatmapmcp1", "TEST HIST", 1000, -1000000, 10000000,1000, -1000000, 10000000);

    return kSUCCESS;
    
}



    // zwischenspeicher fuereventbuilding
  ULong64_t ttrigger0; // T1 hat leider der CAEN stempel geklaut
   ULong64_t T1;
  ULong64_t T2;
  Long64_t X1;
  Long64_t X2;
  Long64_t Y1;
  Long64_t Y2;
  // fertige events speichern
  std::vector<Long64_t> TDiff;
  std::vector<Long64_t> XDiff;
  std::vector<Long64_t> YDiff;
  // variables vor code
  ULong64_t entry2 = 0;
  ULong64_t lastProcessedEntry = 0;
  ULong64_t t2search;
  int ttrigger = 0;
  int maxFileCount = 0;
   int ch0counter = 0;
  int ch1counter = 0;
  int ch2counter = 0;
  int ch3counter = 0;
  int ch4counter = 0;
  int ch5counter = 0;
  int eventcounter = 0;
  int dataPointsCounter = 0;
  int fileCount = 0;
  bool foundMatchingFile = false;
  int reruns = 0;

  // TApplication app("app", nullptr, nullptr); //livebild
  // TApplication app("app", &argc, argv);
  TH1F* histogram = new TH1F("time difference", "TDiff Distribution", 1000, -50000, 50000);

 

                                                                // variable changes performance!

 // TH1F *histogramygated = new TH1F("ygate","ygate; #DeltaY in ns;Time (ns);Counts", 1000, gates[4], gates[5]);
//TH1F *histogramxgated = new TH1F("xgate","xgate; #DeltaX in ns;Time (ns);Counts", 1000, gates[0], gates[1]);

//"histogramxgated", "#DeltaX in ns;Time (ns);Counts"
  //TCanvas *canvas = new TCanvas("canvas", "TDiff Distribution", 1920, 480); // name und groesse des Bildes
  //canvas->Divide(1,2);                                                     // wieviele blods
    TH2F *histogram2 = new TH2F("hist", "DDL Heatmap;#DeltaX in ns;#DeltaY in ns", 2000, -300001, 300001, 2000, -300001, 300001); // binning xmin,max,binning,ymin,ymax
//TH1F* histogram = new TH1F("time difference", "TDiff Distribution", 1000, -50000, 50000);//    
    
    
    

void H10MCPNearlineSpectra::Exec(Option_t* option)
{   
    auto start = std::chrono::high_resolution_clock::now();
       // std::cout << fHitsMCP->GetEntriesFast() << std::endl;

    if (fHitsMCP && fHitsMCP->GetEntriesFast() > 0)
    {   
        Long64_t mpc_wr = 0;
        Int_t nHits = fHitsMCP->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits-1000; ihit++)
{
            H10MCPTwinpeaksCalData* hit = (H10MCPTwinpeaksCalData*)fHitsMCP->At(ihit);
            if (!hit) continue;
            mcp_wr = hit->Get_wr_t();
            
            
            
            
            
            
            Int_t mcp_id = hit->Get_mcp_id();
            Int_t type = hit->Get_type();
            Int_t number = hit->Get_number();

            std::cout << "NEW HIT :: " << std::endl;
        //    std::cout << "MPC :: " << mcp_id << std::endl;
       //     std::cout << "Type :: " << type << std::endl;
      //      std::cout << "Number :: " << number << std::endl;
//MYCODE

    ULong64_t numEntriesToProcess = nHits;
     ULong64_t numEntires = nHits;  
    // for (ULong64 int_t entry2 = 0; entry < numEntriesToProcess; ++entry) {
  //  for (ULong64_t entry2 = 0; entry2 < numEntriesToProcess-1000; ++entry2)
    
      // Load the entry data
 //     tree->GetEntry(entry2);
      // std::cout << "hauptloop: " << entry2 << std::endl;


      // if (Ch == 0 && E !=0 ) {
     
     
     
   //         Y2 = hit->Get_absolute_event_time();
   //         eventcounter++;
    //        ch5counter++;
  

        }
        if (eventcounter ==5){
        TDiff.push_back(ttrigger0 - T2);


        XDiff.push_back(Y1 - Y2);
       
        YDiff.push_back(X1 - X2);
        ch0counter = 0;
        ch1counter = 0;
      ch2counter = 0;
      ch3counter = 0;
      ch4counter = 0;
      ch5counter = 0;
      eventcounter = 0;
std::cout << "fullhit: "  << std::endl;
        dataPointsCounter++; // Increment the counter for each data point collected
                             //                std::cout   << "dataPointsCounter: " << dataPointsCounter << std::endl;
                             // std::cout   << "xdiff: " << XDiff[dataPointsCounter] << std::endl;
        // std::cout << "ydiff: " << YDiff[dataPointsCounter] << std::endl;
		   }

     // if (entry2 == numEntriesToProcess - 1)
   //   {
   //     reruns++;
        // lastProcessedEntry = entry2 + 1;
     //   tree->Reset();
    //    delete tree;
     //   file->Close();
     //   std::cout << "rerunsende: " << reruns << std::endl;
        // std::cout << "endeentry: " << lastProcessedEntry << std::endl;
     //   foundMatchingFile = false;
     // }
    
  }
  std::cout << "start plotting: " << dataPointsCounter << std::endl;

  for (int i = 0; i < dataPointsCounter; i++)
  {
    histogram2->Fill(XDiff[i], YDiff[i]);
    histogram->Fill(TDiff[i]);
}
  std::cout << "plotfin: " << std::endl;

  // canvas->cd(2); // Select the first part of the canvas
 // for (int i = 0; i < dataPointsCounter; i++)
//  {
  //  histogram2->Fill(XDiff[i], YDiff[i]);
 //   if (XDiff[i] > gates[0] && XDiff[i] < gates[1] && YDiff[i] > gates[2] && YDiff[i] < gates[3])
 //   {
 //     histogramxgated->Fill(XDiff[i]);
 //   }
 //   if (XDiff[i] > gates[6] && XDiff[i] < gates[7] && YDiff[i] > gates[4] && YDiff[i] < gates[5])
 //   {
 //     histogramygated->Fill(YDiff[i]);
 //   }
//d::cout << "plot2fin: " << std::endl;
  //canvas->cd(1);
  // Select the first part of the canvas
  //histogramxgated->Draw(); // Draw the first histogram
                           // Select the second part of the canvas
  // col2 for fast
 // canvas->cd(2);
////chatgpt


// Update the canvas
//canvas->Update();

//TPaveStats *stats = (TPaveStats*)histogram2->FindObject("stats"); not working

//if (stats) {
 //   stats->SetX1NDC(0.4); // Set the left edge position in NDC (normalized device coordinates)
  //  stats->SetY1NDC(0.4); // Set the bottom edge position in NDC
 //   stats->SetX2NDC(0.4); // Set the right edge position in NDC
 //   stats->SetY2NDC(0.4); // Set the top edge position in NDC
//}
///endechatgpt

// Redraw the histogram with updated axis labels
//histogram2->Draw("colz");

  //histogramygated->Draw();
  //canvas->Update();

 // canvas2d->cd();
  //histogram2->Draw("colz");
  //gPad->SetLogz(); // logcolorbar
  //canvas2d->Update();

  std::cout << "kein neuer file gefunden" << std::endl;
  std::string rootRunname = Runname + ".root";
  const char *CRunname = rootRunname.c_str(); // umwandlung von string to c_string (vill)

  TFile *file = new TFile(CRunname, "RECREATE");
 // canvas->cd();
 // canvas->Write();
 // canvas2d->cd();

 // canvas2d->Write();
  // histogram->Write();
  // histogram2->Write();
  std::cout << "finite: " << std::endl;

 // file->Close();

  // Clean up
 // delete canvas;
  // delete histogram;
//  delete histogram2;
 // delete file;
    




















    //    }

    
    


    fNEvents++;
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
    
}



void H10MCPNearlineSpectra::FinishEvent()
{
    // resets and whatever
}

void H10MCPNearlineSpectra::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_mcp->Write();
    gDirectory = tmp;
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    
}

ClassImp(H10MCPNearlineSpectra)
