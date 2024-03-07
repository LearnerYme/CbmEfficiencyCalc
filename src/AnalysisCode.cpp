// std headers
#include <iostream>
#include <vector>
#include <string>

// root headers
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TEfficiency.h"

// AnalysisTree headers
#include "BranchConfig.hpp"
#include "Configuration.hpp"
#include "DataHeader.hpp"
#include "EventHeader.hpp"
#include "Detector.hpp"
#include "Matching.hpp"
#include "Track.hpp"
#include "Chain.hpp"

// additional module headers
#include "IdxConstants/IdxConstants.h"
#include "DuplicateRemover/DuplicateRemover.h"
#include "MultiplicityTool/MultiplicityTool.h"
#include "CentralityTool/CentralityTool.h"
#include "CentralityTool/CentParams.h"
#include "CbmCut/CbmCut.h"

using std::vector;
using std::string;

using namespace AnalysisTree;

using std::cout;
using std::endl;

// main

int main(int argc, char** argv) {

	Chain t(
		vector<string>({"file.list"}),
		vector<string>({"rTree"})
	);
	float BeamRapidity = 1.62179;

	Configuration* cfg = t.GetConfiguration();

	// 
    EventHeader* mSimEventHeader = new EventHeader();
    EventHeader* mRecEventHeader = new EventHeader();
    Particles* mSimTracks = new Particles();
    HitDetector* mTofHits = new HitDetector();
    TrackDetector* mVtxTracks = new TrackDetector();

	// mathing between detectors
	Matching* mMatchingVtx2Sim = new Matching();
    Matching* mMatchingVtx2Tof = new Matching();
    Matching* mMatchingTof2Sim = new Matching();

	// set branch for detectors and matchings
	t.SetBranchAddress("VtxTracks2SimParticles.", &mMatchingVtx2Sim);
    t.SetBranchAddress("VtxTracks2TofHits.", &mMatchingVtx2Tof);
    t.SetBranchAddress("TofHits2SimParticles.", &mMatchingTof2Sim);
    t.SetBranchAddress("RecEventHeader.", &mRecEventHeader);  
    t.SetBranchAddress("SimEventHeader.", &mSimEventHeader);  
    t.SetBranchAddress("SimParticles.", &mSimTracks);
    t.SetBranchAddress("VtxTracks.", &mVtxTracks);  
    t.SetBranchAddress("TofHits.", &mTofHits);  

	// multiplicity tool
	const int nEv = t.GetEntries();
    cout << "[LOG] Reading tracks, there will be " << nEv << " events." << endl;
	MultiplitityTool* mMultTool = new MultiplitityTool();
	mMultTool->Init();
	mMultTool->EnableMc(true);
	
	// duplicated MC particle remover
	DuplicateRemover* mDupRmver = new DuplicateRemover();
	mDupRmver->Init();

	// centrality tool
	CentralityTool* mCentTool = new CentralityTool();
	mCentTool->ReadParams();

	// cbn cut
	MyCbmCut* mCut = new MyCbmCut();
	mCut->Enable(true);

	TFile* tf = new TFile("output.root", "recreate");
	tf->cd();

	TEfficiency* teff[cent_conf::nCentrality];
	TH2F* h2Pass[cent_conf::nCentrality];
	TH2F* h2Total[cent_conf::nCentrality];
	TH1F* hCent = new TH1F("hCent", ";Centrality;", cent_conf::nCentrality, -0.5, cent_conf::nCentrality-0.5);
	const char* centName[cent_conf::nCentrality] = {
        "0-10%", "10-20%",
        "20-30%", "30-40%", "40-50%",
    };
	for (int i=0; i<cent_conf::nCentrality; i++) {
		hCent->GetXaxis()->SetBinLabel(i+1, centName[i]);
	}

	for (int i=0; i<cent_conf::nCentrality; i++) {
		teff[i] = new TEfficiency(
			Form("Eff_cent%d", i), ";y;p_{T} [GeV/c]",
			16, -0.5, 1.1, // rapidity -0.5 to 1.1
			24, 0.20, 2.20 // pT 0.2 to 2.2
		);
		h2Pass[i] = new TH2F(
			Form("hPass_cent%d", i), ";y;p_{T} [GeV/c]",
			16, -0.5, 1.1, 
			24, 0.20, 2.20 
		);
		h2Total[i] = new TH2F(
			Form("hTotal_cent%d", i), ";y;p_{T} [GeV/c]",
			16, -0.5, 1.1, 
			24, 0.20, 2.20 
		);
	}
	
	// event loop starts
	for (auto iEv=0; iEv<nEv; iEv++) {
		t.GetEntry(iEv);
		if (!mCut->IsGoodEvent(*mRecEventHeader)) { continue; }
		mMultTool->Make(mVtxTracks, mTofHits, mMatchingVtx2Tof, mSimTracks);
		auto mRefMult3 = mMultTool->GetRefMult3();
		// auto mRefMult3M = mMultTool->GetRefMult3M();
		int centrality = mCentTool->GetCentrality(mRefMult3, false); // centrality difinition with RefMult3
		if (centrality < 0) { continue; }
		hCent->Fill(centrality);

		mDupRmver->Clear();
		// MC particle loop
		for (const auto& McTrack : *mSimTracks) {
			if (!mCut->IsPrimarySimParticle(McTrack)) { continue; }
			if (McTrack.GetPid() != 2212) { continue; }
			if (mDupRmver->Make(McTrack)) { continue; }
			float pt = McTrack.GetPt();
			float y = McTrack.GetRapidity();
			y -= BeamRapidity; // boost to CoM frame
			h2Total[centrality]->Fill(y, pt);

			// get matched vtx track
			const int cVtxId = mMatchingVtx2Sim->GetMatch(McTrack.GetId(), true);
			if (cVtxId < 0) { // no matched Vtx track
				teff[centrality]->Fill(false, y, pt);
				continue;
			}
			const auto& VtxTrack = mVtxTracks->GetChannel(cVtxId);
			if (!mCut->IsGoodVtxTrack(VtxTrack)) { // Vtx track is dropped out by our cut
				teff[centrality]->Fill(false, y, pt);
				continue;
			}

			// get matched TOF hit
			const int cMatchedTofId = mMatchingVtx2Tof->GetMatch(cVtxId);
			if (cMatchedTofId < 0) { // no matched Tof hit
				teff[centrality]->Fill(false, y, pt);
				continue;
			}
			const auto& TofHit = mTofHits->GetChannel(cMatchedTofId);
			if (!mCut->IsGoodTofHit(TofHit)) { // tof hit is dropped out by our cut
				teff[centrality]->Fill(false, y, pt);
				continue;
			}

			// if you want to applie other TOF cut, do it here
			// currently, I decide to use hard TOF mass2 cut
			float TofMass2 = TofHit.GetField<float>(IdxTofMass2);
			if (TofMass2 < 0.6 || TofMass2 > 1.2) {
				teff[centrality]->Fill(false, y, pt);
				continue;
			}

			// fill passed histogram and TEfficiency with pass
			h2Pass[centrality]->Fill(y, pt);
			teff[centrality]->Fill(true, y, pt);
		}
	}
	for (int i=0; i<cent_conf::nCentrality; i++) {
		teff[i]->Write();
	}
	tf->Write();
	tf->Close();

	return 0;
}
