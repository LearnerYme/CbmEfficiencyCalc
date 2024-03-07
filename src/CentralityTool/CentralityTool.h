#ifndef __CENT_TOOL_HEADER__
#define __CENT_TOOL_HEADER__

/*
    Version: 1.0
    Author: yghuang
    Date: 02.03.2024
*/

#include <iostream>

class CentralityTool {

    private:

        static const int PatchNumber = 1;

        // centrality split with bin edge
        double centSplitEdge[5];
        double centSplitEdgeM[5];
        double nPartEdge[5];
        double nPartEdgeM[5];

    public:
        CentralityTool();
        ~CentralityTool(){}
        void ReadParams();

        // -------------------------------------------------------------------
        // - centrality split functions
        void SetCentEdge(int e0, int e1, int e2, int e3, int e4) {
            centSplitEdge[0] = e0;
            centSplitEdge[1] = e1;
            centSplitEdge[2] = e2;
            centSplitEdge[3] = e3;
            centSplitEdge[4] = e4;
            std::cout << "[LOG] - Centrality bin edge (RefMult3) specified.\n";
        }

        void SetCentEdge(int* arr) {
            for (int i=0; i<5; i++) {
                centSplitEdge[i] = *(arr+i);
            }
            std::cout << "[LOG] - Centrality bin edge (RefMult3) specified.\n";
        }

        // -------------------------------------------------------------------
        // - centrality split functions for RefMult3M
        void SetCentEdgeM(int e0, int e1, int e2, int e3, int e4) {
            centSplitEdgeM[0] = e0;
            centSplitEdgeM[1] = e1;
            centSplitEdgeM[2] = e2;
            centSplitEdgeM[3] = e3;
            centSplitEdgeM[4] = e4;
            std::cout << "[LOG] - Centrality bin edge (RefMult3M) specified.\n";
        }
        void SetCentEdgeM(int* arr) {
            for (int i=0; i<5; i++) {
                centSplitEdgeM[i] = *(arr+i);
            }
            std::cout << "[LOG] - Centrality bin edge (RefMult3M) specified.\n";
        }

        // -------------------------------------------------------------------
        // - <Npart> functions
        void SetMeanNpart(double e0, double e1, double e2, double e3, double e4) {
            nPartEdge[0] = e0;
            nPartEdge[1] = e1;
            nPartEdge[2] = e2;
            nPartEdge[3] = e3;
            nPartEdge[4] = e4;
            std::cout << "[LOG] - Mean Npart (with RefMult3) specified.\n";
        }

        void SetMeanNpart(double* arr) {
            for (int i=0; i<5; i++) {
                nPartEdge[i] = *(arr+i);
            }
            std::cout << "[LOG] - Mean Npart (with RefMult3) specified.\n";
        }

        // -------------------------------------------------------------------
        // - <Npart> functions with RefMult3M
        void SetMeanNpartM(double e0, double e1, double e2, double e3, double e4) {
            nPartEdgeM[0] = e0;
            nPartEdgeM[1] = e1;
            nPartEdgeM[2] = e2;
            nPartEdgeM[3] = e3;
            nPartEdgeM[4] = e4;
            std::cout << "[LOG] - Mean Npart (with RefMult3M) specified.\n";
        }

        void SetMeanNpartM(double* arr) {
            for (int i=0; i<5; i++) {
                nPartEdgeM[i] = *(arr+i);
            }
            std::cout << "[LOG] - Mean Npart (with RefMult3M) specified.\n";
        }

        int GetCentrality(int mult, bool withM=false);

        void GetMeanNpart(double* arr) { 
            for (int i=0; i<5; i++) {
                arr[i] = nPartEdge[i];
            }    
        }
        
        void GetMeanNpartM(double* arr) { 
            for (int i=0; i<5; i++) {
                arr[i] = nPartEdgeM[i];
            }    
        }

};

#endif
