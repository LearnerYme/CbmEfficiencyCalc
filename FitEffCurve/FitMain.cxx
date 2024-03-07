#include <iostream>

#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TString.h"
#include "TF1.h"
#include "FitCore.h"

int main(int argc, char** argv) {
    /*
        Args:
        :fname: root file name
        :save name: pdf file name
        :title: text shown in the cover
        :out name: root file name (output TF1)
    */

    gStyle->SetOptFit(1111);
    gStyle->SetStatX(0.7);
    gStyle->SetStatY(0.6);
    auto f = new TFile(argv[1]);
    const char* sname = argv[2];

    TH2F* hPass;
    TH2F* hTotal;

    const int nCent = 5;
    const int nY = 12;

    const char* cents[nCent] = {
        "0-10%",
        "10-20%",
        "20-30%",
        "30-40%",
        "40-50%",
    };

    const char* ys[nY] = {
        "-0.4 < y < -0.3",
        "-0.3 < y < -0.2",
        "-0.2 < y < -0.1",
        "-0.1 < y < -0.0",
        "-0.0 < y < +0.1",
        "+0.1 < y < +0.2",
        "+0.2 < y < +0.3",
        "+0.3 < y < +0.4",
        "+0.4 < y < +0.5",
        "+0.5 < y < +0.6",
        "+0.6 < y < +0.7",
        "+0.7 < y < +0.8",
    };

    const double yvs[nY] = {
        -0.35,
        -0.25,
        -0.15,
        -0.05,
        +0.05,
        +0.15,
        +0.25,
        +0.35,
        +0.45,
        +0.55,
        +0.65,
        +0.75,
    };

    TF1* tfunc[nCent][nY];

    for (int cent=0; cent<nCent; cent++) {
        for (int y=0; y<nY; y++) {
            tfunc[cent][y] = new TF1(
                Form("Eff_cent%d_y%d", cent, y),
                "[0]*TMath::Exp(-1.0* TMath::Power([1]/x, [2])) + [3]*TMath::Exp(-[5]*TMath::Power(x-[4], 2))", 
                0.2, 2.0
            );
        }
    }

    auto c = new TCanvas();
    auto lat = new TLatex();
    lat->SetTextFont(64);
    lat->SetTextColor(2);
    lat->SetTextSize(24);
    lat->SetTextAlign(22);
    c->Clear();
    lat->DrawLatexNDC(0.5, 0.5, argv[3]);
    c->Print(Form("%s(", sname));

    // std::cout << "DEBUG: sname is " << sname << std::endl;
    // return 0;

    TF1* tmp;
    FitCore fitc;
    for (int cent=0; cent<nCent; cent++) {
        hPass = (TH2F*)f->Get(Form("hPass_cent%d", cent));
        hTotal = (TH2F*)f->Get(Form("hTotal_cent%d", cent));
        fitc.Init(hPass, hTotal);
        for (int i=0; i<nY; i++) {
            fitc.Print(c, yvs[i], tfunc[cent][i], sname, Form("%s|%s;p_{T} [GeV/c];Efficiency", cents[cent], ys[i]));
        }
    }

    c->Clear();
    c->cd();
    lat->DrawLatexNDC(0.5, 0.5, "- END -");
    c->Print(Form("%s)", sname));

    TFile* tfout = new TFile(argv[4], "recreate");
    tfout->cd();
    for (int cent=0; cent<nCent; cent++) {
        for (int y=0; y<nY; y++) {
            tfunc[cent][y]->Write();
        }
    }
    tfout->Close();

    return 0;
}