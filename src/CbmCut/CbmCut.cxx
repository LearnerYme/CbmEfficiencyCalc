#include "CbmCut.h"

using AnalysisTree::EventHeader;
using AnalysisTree::Track;
using AnalysisTree::Hit;
using AnalysisTree::Particle;

bool MyCbmCut::IsGoodEvent(EventHeader event) {
    if (!mEnableCbmCut) { return true; }
    float vx = event.GetField<float>(-1);
    float vy = event.GetField<float>(-2);
    float vz = event.GetField<float>(-3);
    float chi2 = event.GetField<float>(0);
    return fabs(vx) < 0.5 && fabs(vy) < 0.5 && fabs(vz+44) < 0.5 && chi2 > 0.8 && chi2 < 1.7;
}

bool MyCbmCut::IsGoodVtxTrack(Track vtxTrack) {
    if (!mEnableCbmCut) { return true; }
    float vtx_chi2 = vtxTrack.GetField<float>(1);
    float chi2 = vtxTrack.GetField<float>(0);
    int ndf = vtxTrack.GetField<int>(0);
    int nHits = vtxTrack.GetField<int>(2);
    float eta = vtxTrack.GetEta();
    float chi2OverNdf = ndf == 0 ? 999.0 : chi2 / ndf;
    return nHits >= 4 && nHits <= 100 && vtx_chi2 > 0 && vtx_chi2 < 3 && chi2OverNdf < 3 && eta > 0.2 && eta < 4;
}

bool MyCbmCut::IsGoodTofHit(Hit tofHit) {
    if (!mEnableCbmCut) { return true; }
    float dx = tofHit.GetField<float>(4);
    float dy = tofHit.GetField<float>(5);
    return fabs(dx) < 2 || fabs(dx) < 1;
}

bool MyCbmCut::IsPrimarySimParticle(Particle mcParticle) {
    if (!mEnableCbmCut) { return true; }
    int motherId = mcParticle.GetField<int>(0);
    return motherId == -1;
}