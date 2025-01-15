#ifdef __CLING__
#pragma cling optimize(0)
#endif
void cut_Z_vs_AoQ_Pb()
{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Mon Jun 10 17:48:31 2024) by ROOT version 6.26/10
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",3378,420,538,315);
   Canvas_1->Range(2.499353,79.18026,2.675277,85.13245);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TCutG *cutg = new TCutG("CUTG",10);
   cutg->SetVarX("Z1 vs. A/Q");
   cutg->SetVarY("");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,2.547971,84.14042);
   cutg->SetPoint(1,2.594834,83.39799);
   cutg->SetPoint(2,2.631672,82.68117);
   cutg->SetPoint(3,2.645957,81.93875);
   cutg->SetPoint(4,2.628916,80.30029);
   cutg->SetPoint(5,2.583807,80.17229);
   cutg->SetPoint(6,2.532433,80.27469);
   cutg->SetPoint(7,2.528674,82.55317);
   cutg->SetPoint(8,2.546718,84.08922);
   cutg->SetPoint(9,2.547971,84.14042);
   cutg->Draw("alp");
   
   TPaveText *pt = new TPaveText(0.4461567,0.9336582,0.5538433,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("Graph");
   pt->Draw();
   Canvas_1->Modified();
   Canvas_1->cd();
   Canvas_1->SetSelected(Canvas_1);
}
