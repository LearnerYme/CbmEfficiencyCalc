#ifndef __CBMCUT_YIGE_HEADER__
#define __CBMCUT_YIGE_HEADER__

#include "Detector.hpp"
#include "Matching.hpp"
#include "EventHeader.hpp"

class DuplicateRemover;

class MyCbmCut {

    public:
        MyCbmCut(){ mEnableCbmCut = true; }
        ~MyCbmCut(){}
        void Enable(bool val) { mEnableCbmCut = val; }
        bool IsGoodEvent(AnalysisTree::EventHeader event); // for reconstrcuted event
        bool IsGoodVtxTrack(AnalysisTree::Track vtxTrack);
        bool IsGoodTofHit(AnalysisTree::Hit tofHit);
        bool IsPrimarySimParticle(AnalysisTree::Particle mcParticle);

    private:
        bool mEnableCbmCut;
};

#endif