#ifndef MakePlots_H
#define MakePlots_H

#include "FairTask.h"

class TClonesArray;
class TCanvas;
class TH1F;
class TH2F;

/* 
Here I would like to define some tasks to build OnlineSpectra, etc.
*/

class c4Histogram : public FairTask
{
    public:
        c4Histogram()
        
        void ~c4Histogram();
}

#endif