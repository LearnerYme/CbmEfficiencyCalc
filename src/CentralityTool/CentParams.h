#ifndef __CENT_TOOL_CONFXXX__
#define __CENT_TOOL_CONFXXX__

namespace cent_conf {
    
    // should change this header for each new data set

    static const int CentralityToolPatch = 1;
    static const int nCentrality = 5;
    
    // The name and mode are used to check in the LOG file if the wrong parameter file is used.
    static const char* Name = "4p9";
    static const char* Mode = "FINAL";

    // centrality split with RefMult3
    static int cent_edge[nCentrality] = { // here fill in the centrality bin edge 
        129, 90, 62, 41, 26
    };
    // with RefMult3M
    static int cent_edgeM[nCentrality] = { // here fill in the centrality bin edge
        261, 182, 125, 83, 53 
    };
    // <Npart> with RefMult3
    static double nPart_edge[nCentrality] = {
        310.033, 225.096, 161.604, 112.748, 75.4538
    };
    // <Npart> with RefMult3M
    static double nPart_edgeM[nCentrality] = {
        311.336, 224.592, 161.099, 112.7, 76.0376
    };

} // namespace cent_conf


#endif
