#include "IdxConstants.h"

// VtxTracks
#ifdef __VTXTRACK_IDX__
    // init
    constexpr Indey_t IdxVtxChi2 = 0;
    constexpr Indey_t IdxVtxDcax = 2;
    constexpr Indey_t IdxVtxDcay = 3;
    constexpr Indey_t IdxVtxDcaz = 4;
    constexpr Indey_t IdxVtxEta = -3; 
    constexpr Indey_t IdxVtxP = -7;
    constexpr Indey_t IdxVtxPt = -2;
    constexpr Indey_t IdxVtxPx = -4;
    constexpr Indey_t IdxVtxPy = -5;
    constexpr Indey_t IdxVtxPz = -6;
    constexpr Indey_t IdxVtxPhi = -1;
    constexpr Indey_t IdxVtxVtxChi2 = 1;  
    constexpr Indey_t IdxVtxNdf = 0;
    constexpr Indey_t IdxVtxNhits = 2; // number of hits (total MVD+STS)
    constexpr Indey_t IdxVtxCharge = 1;
#endif

// TofHits
#ifdef __TOFHIT_IDX__
    // init
    constexpr Indey_t IdxTofDx = 4;
    constexpr Indey_t IdxTofDy = 5;
    constexpr Indey_t IdxTofDz = 6;
    constexpr Indey_t IdxTofL = 1;
    constexpr Indey_t IdxTofMass2 = 0;
    constexpr Indey_t IdxTofPhi = -1;
    constexpr Indey_t IdxTofRigi = 3;
#endif

// SimParticles
#ifdef __SIMPARTICLE_IDX__
    // init
    constexpr Indey_t IdxSimEta = -6;
    constexpr Indey_t IdxSimP = -10;
    constexpr Indey_t IdxSimPt = -2;
    constexpr Indey_t IdxSimPx = -7;
    constexpr Indey_t IdxSimPy = -8;
    constexpr Indey_t IdxSimPz = -9;
    constexpr Indey_t IdxSimPhi = -1;
    constexpr Indey_t IdxSimRap = -3;
    constexpr Indey_t IdxSimMotherId = 0;
    constexpr Indey_t IdxSimPdgId = -4;
#endif

// McEvent
#ifdef __MCEVENT_IDX__
    // init
    constexpr Indey_t IdxMcB = 1;
    constexpr Indey_t IdxMcVx = -1;
    constexpr Indey_t IdxMcVy = -2;
    constexpr Indey_t IdxMcVz = -3;
#endif

// RecEvent
#ifdef __RECEVENT_IDX__
    // init
    constexpr Indey_t IdxRecVtxChi2 = 0;
    constexpr Indey_t IdxRecVx = -1;
    constexpr Indey_t IdxRecVy = -2;
    constexpr Indey_t IdxRecVz = -3;
    constexpr Indey_t IdxRecMult = 0;
#endif
