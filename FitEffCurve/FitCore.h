#ifndef __FITCORE__
#define __FITCORE__

class TEfficiency;
class TH1F;
class TH2F;
class TF1;
class TGraphAsymmErrors;
class TCanvas;

class FitCore {

    private:
        TEfficiency* teff; // load from file
        TH2F *h2tot, *h2pass;
        TH1F *h1tot, *h1pass;
        TGraphAsymmErrors* tg;

    public:
        FitCore(){}
        ~FitCore(){}

        void Init(TH2F* hPass, TH2F* hTotal);
        void Print(TCanvas* c, double rap, TF1* func, const char* name, const char* title);

};


#endif