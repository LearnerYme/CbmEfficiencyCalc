#ifndef __MULTTOOL_HEADER__
#define __MULTTOOL_HEADER__

#include "Detector.hpp"
#include "Matching.hpp"

class DuplicateRemover;

class MultiplitityTool {

    public:
        MultiplitityTool(){}
        ~MultiplitityTool(){}
        void Init();
        void Clear();
        bool Make(AnalysisTree::TrackDetector*, AnalysisTree::HitDetector*, AnalysisTree::Matching*, AnalysisTree::Particles*);
        void EnableMc(bool val) { mEnableMc = val; }
        int GetRefMult() { return refMult; }
        int GetRefMult3() { return refMult3; }
        int GetRefMultM() { return refMultM; }
        int GetRefMult3M() { return refMult3M; }
        int GetNVtxTracks() { return nVtxTracks; }

    private:
        bool mEnableMc;

        int refMult;
        int refMult3;
        int refMultM;
        int refMult3M; // with PDG id
        int nVtxTracks;
        DuplicateRemover* mDupRmver;
};

#endif