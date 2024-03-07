void GetEffHist() {

    const int nCent = 5;
    auto tf = new TFile("eff.hadd.root");
    TH2F* hPass[nCent];
    TH2F* hTotal[nCent];
    TEfficiency* teff[nCent];
    TH2F* hEff[nCent];

    for (int i=0; i<nCent; i++) {
        tf->GetObject(Form("hPass_cent%d", i), hPass[i]);
        tf->GetObject(Form("hTotal_cent%d", i), hTotal[i]);
        teff[i] = new TEfficiency(*hPass[i], *hTotal[i]);
        hEff[i] = (TH2F*)(teff[i]->CreateHistogram()->Clone());
        hEff[i]->SetName(Form("Eff_cent%d", i));
        hEff[i]->SetTitle(";y;p_{T} [GeV/c];Efficiency");
    }
    auto tfout = new TFile("Efficiency.root", "recreate");
    tfout->cd();
    for (int i=0; i<nCent; i++) {
        hEff[i]->Write();
    }

}