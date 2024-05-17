#ifndef AnalysisTools_H
#define AnalysisTools_H

#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include "Rtypes.h"

class TDirectory;
class TH1;
class TH2;
class TH1I;
class TH1F;
class TH1D;
class TH2I;
class TH2F;
class TH2D;

TH1* MakeTH1(TDirectory* dir, const char* type, const char* name, 
            const char* title, int bins, double xmin, double xmax);
TH1* MakeTH1(TDirectory* dir, const char* type, const char* name, 
            const char* title, int bins, double xmin, double xmax,
            const char* xtitle);
TH1* MakeTH1(TDirectory* dir, const char* type, const char* name, 
            const char* title, int bins, double xmin, double xmax,
            const char* xtitle, EColor fillColour, EColor lineColour);

TH2* MakeTH2(TDirectory* dir, const char* type, const char* name, const char* title, 
            int xbins, double xmin, double xmax, int ybins, int ymin, int ymax);
TH2* MakeTH2(TDirectory* dir, const char* type, const char* name, const char* title, 
            int xbins, double xmin, double xmax, int ybins, int ymin, int ymax,
            const char* xtitle, const char* ytitle);


// not sure how these will work yet. 
TDirectory* CreateDirectory(TDirectory* current_dir);

void FindNextSubDirectory(TDirectory* current_dir, const char* path);




#endif 