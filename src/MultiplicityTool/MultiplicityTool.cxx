#include "IdxConstants/IdxConstants.h"
#include "MultiplicityTool/MultiplicityTool.h"
#include "DuplicateRemover/DuplicateRemover.h"

using AnalysisTree::TrackDetector;
using AnalysisTree::HitDetector;
using AnalysisTree::Matching;
using AnalysisTree::Particles;

void MultiplitityTool::Init() {
    Clear();
    mDupRmver = new DuplicateRemover();
    mDupRmver->Init();
    mEnableMc = false;
}

void MultiplitityTool::Clear() {
    refMult = refMult3 = 0;
    nVtxTracks = 0;
    refMultM = refMult3M = -1;
}

bool MultiplitityTool::Make(TrackDetector* VtxTracks, HitDetector* TofHits, Matching* MatchingVtx2Tof, Particles* McParticles = 0) {
    /*
        Args: 3+1
        :VtxTracks: pointer to Detector<Track>, the branch name is usually 'VtxTracks'
        :TofHits: pointer to Detector<Hit>, the branch name is usually 'TofHits'
        :Mathing: pointer to Matching, the branch name is usually 'VtxTracks2TofHits'
        :McParticles: valid only when EnableMc is ON, pointer to Detector<Particle>, the branch name is usually 'SimParticles'
        Returns: bool
        :If succeeded, return true, and one can get corresponding multiplicity number via getters
        :If some pointers are incorrect, return false
        Note
        :1) would better not to use RefMultM, since we do not do charge selection (might be neutron or something there included)
    */
    if (mEnableMc && !McParticles) { return false; }
    if (!VtxTracks || !TofHits || !MatchingVtx2Tof) { return false; }
    Clear();

    // for detector simulated
    for (const auto& VtxTrack : *VtxTracks) {
        const int VtxId = VtxTrack.GetId();
        float VtxEta = VtxTrack.GetEta(); 
        int VtxNhits = VtxTrack.GetField<int>(IdxVtxNhits);
        float VtxChi2 = VtxTrack.GetField<float>(IdxVtxChi2);
        float VtxVtxChi2 = VtxTrack.GetField<float>(IdxVtxVtxChi2);
        int VtxNdf = VtxTrack.GetField<int>(IdxVtxNdf);
        // here are track cuts for multiplicity definition
        if (VtxEta < 0.2 || VtxEta > 4.0) { continue; }
        float chi2OverNdf = VtxNdf == 0 ? 999.0 : VtxChi2 / VtxNdf;
        if (chi2OverNdf > 2) { continue; }
        if (VtxVtxChi2 < 0 || VtxVtxChi2 > 3) { continue; }
        if (VtxNhits < 4 || VtxNhits > 100) { continue; }

        refMult += 1;
        const int MatchedTofId = MatchingVtx2Tof->GetMatch(VtxId);
        if (MatchedTofId >= 0) {
            const auto& TofHit = TofHits->GetChannel(MatchedTofId);
            float TofDx = TofHit.GetField<float>(IdxTofDx);
            float TofDy = TofHit.GetField<float>(IdxTofDy);
            float TofMass2 = TofHit.GetField<float>(IdxTofMass2);
            if (fabs(TofDx) > 2 || fabs(TofDy) > 1) {
                // we can use hits with bad Tof information, as they are not taken into account
                refMult3 += 1;
            } else if (TofMass2 < 0.6 || TofMass2 > 1.2) {
                // when we do PID in multiplicity counting, this cut can be a rough hard cut
                refMult3 += 1;
            }            
        }
    }
    nVtxTracks = VtxTracks->GetNumberOfChannels();

    // for pure model simulation
    if (mEnableMc) {
        refMultM = 0;
        refMult3M = 0;
        for (const auto& McParticle : *McParticles) {
            int motherId = McParticle.GetField<int>(IdxSimMotherId);
            if (motherId != -1) { continue; } // not primary track
            if (mDupRmver->Make(McParticle)) { continue; }
            float McEta = McParticle.GetEta();
            if (McEta < 0.2 || McEta > 4.0) { continue; }
            refMultM += 1;
            int McPid = McParticle.GetPid();
            if (fabs(McPid) == 211 || fabs(McPid) == 321) {
                refMult3M += 1;
            }
        }
    }
    return true;
}