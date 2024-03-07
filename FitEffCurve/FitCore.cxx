#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TEfficiency.h"
#include "TMath.h"
#include "TString.h"
#include "TStyle.h"
#include "TGraphAsymmErrors.h"
#include "FitCore.h"
#include "TEfficiency.h"

#include <iostream>
void FitCore::Init(TH2F* hPass, TH2F* hTotal) {
    h2tot = hTotal;
    h2pass = hPass;
}

void FitCore::Print(TCanvas* c, double rap, TF1* func, const char* name, const char* title) {
    // TPC eff can use following parameters: this initial parameters are from DaoGe
    double init_pars[6] = {    
        0.86,
        0.27,
        2.30,
        0.06,
        0.90,
        3.74
    }; 
    func->SetParameters(init_pars);
    func->SetParLimits(0, 0.5, 1.0);
    func->SetParLimits(1, 0.0, 1.0);
    func->SetParLimits(3, 0.0, 0.1);
    func->SetParLimits(4, 0.0, 1.0);
    func->SetParLimits(5, 0.0, 3.0);
    func->SetLineColor(0);
    func->SetLineStyle(2);
    int bin = h2tot->GetXaxis()->FindBin(rap);
    h1tot = (TH1F*)h2tot->ProjectionY("tot_py", bin, bin);
    h1pass = (TH1F*)h2pass->ProjectionY("pass_py", bin, bin);
    teff = new TEfficiency(*h1pass, *h1tot);
    tg = teff->CreateGraph();
    tg->Fit(func, "RN0Q");

    c->Clear();
    c->cd();

    TH2F* frame = (TH2F*)gPad->DrawFrame(0.0, -0.03, 2.2, 1.03);
    frame->SetTitle(title);
    tg->SetMarkerStyle(30);
    tg->SetMarkerColor(1);
    tg->DrawClone("epsame");
    func->Draw("lsame");
    gStyle->SetOptFit(111);
    gStyle->SetStatX(0.7);
    gStyle->SetStatY(0.6);

    c->Print(name);

}
