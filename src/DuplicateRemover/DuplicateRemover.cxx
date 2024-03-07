#include "DuplicateRemover.h"
#include <iostream>
void DuplicateRemover::Clear() {
    pt = -999.0;
    eta = -999.0;
    phi = -999.0;
}

bool DuplicateRemover::Make(AnalysisTree::Particle McParticle) {
    /*
        Args: 1
        :McParticle: should be in the MC particles loop (Detector<Particle>)
        Return:
        :If this MC particle is holding excactly the same pt, eta and phi as the previous one, return true, which means it SHOULD be dropped out
        :Otherwise, return false, and nothing happens
    */
    float pt_ = pt;
    float eta_ = eta;
    float phi_ = phi;
    pt = McParticle.GetPt();
    eta = McParticle.GetEta();
    phi = McParticle.GetPhi();

    return pt_ == pt && eta_ == eta && phi_ == phi;
}
