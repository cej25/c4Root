#include "TFile.h"
#include "TTree.h"

void mp()
{
	TFile* f = TFile::Open("run_0075_test-merge.root");
	TTree *t = (TTree*)f->Get("evt");
	f->cd();
	f->MakeProject("traces", "*", "RECREATE");

}
