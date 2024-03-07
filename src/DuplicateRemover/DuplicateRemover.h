#ifndef __DUPLRMV_HEADER__
#define __DUPLRMV_HEADER__

#include "Particle.hpp"

class DuplicateRemover {

    public:
        DuplicateRemover(){}
        ~DuplicateRemover(){}

        void Init() { Clear(); }
        void Clear();
        bool Make(AnalysisTree::Particle);

    private:
        float pt;
        float eta;
        float phi;
};

#endif