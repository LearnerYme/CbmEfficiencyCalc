#include "CentParams.h"
#include "CentralityTool.h"

CentralityTool::CentralityTool() {

    for (int i=0; i<cent_conf::nCentrality; i++) {
        centSplitEdge[i] = 0;
        centSplitEdgeM[i] = 0;
    }
}

void CentralityTool::ReadParams() {
    if (cent_conf::CentralityToolPatch != PatchNumber) {
        std::cout << "[WARNING] - ReadParams: The patch numbers of CentralityTool and from parameter configuration do not match!" << std::endl;
        std::cout << "[WARNING] - ReadParams: Patch number from configuation: " << cent_conf::CentralityToolPatch << ", and from CentralityTool: " << PatchNumber << std::endl;
        std::cout << "[WARNING] - ReadParams: This may lead to some fatal results." << std::endl;
    }

    SetCentEdge(cent_conf::cent_edge);
    SetCentEdgeM(cent_conf::cent_edgeM);
    SetMeanNpart(cent_conf::nPart_edge);
    SetMeanNpartM(cent_conf::nPart_edgeM);
}

int CentralityTool::GetCentrality(int mult, bool withM) {
    if (withM) {
        for (int i=0; i<cent_conf::nCentrality; i++) {
            if (mult > centSplitEdgeM[i]) {
                return i;
            }
        }
    } else {
        for (int i=0; i<5; i++) {
            if (mult > centSplitEdge[i]) {
                return i;
            }
        }
    }
    return -1;
}
