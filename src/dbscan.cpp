#include "include/dbscan.h"
#include <iostream>
using namespace std;


namespace dbscanSpace {
    
void Cdbscan::getOccuSet(map<int, Sta>& staMapIn, set<int>& occuSetOut) {
    for (auto it = staMapIn.begin(); it != staMapIn.end(); ++it) {
        if (it->second.ngPtID.size() != 0) occuSetOut.insert(it->first);
    }
}


int Cdbscan::findNei(int query, set<int>& occuSetIn, set<int>& neiSetOut) {
    int w = Cdbscan::width;
    int h = Cdbscan::height;
    int n = Cdbscan::nNum;
    int row_i = query / w;
    int col_j = query % w;
    
    int ite = 0;
    int num = 0;
    for (int ii = row_i - n; ii <= row_i + n; ++ii) {
        if (ii < 0 || ii >= h) continue;
        ite = 0;
        for (int jj = col_j - n; ++ite <= (2 * n + 1); ++jj) {
            if (jj < 0)
                jj += w;
            if (jj >= w)
                jj -= w;
            if (occuSetIn.find(ii * w + jj) != occuSetIn.end()) {
                if (neiSetOut.find(ii * w + jj) == neiSetOut.end()) {
                    neiSetOut.insert(ii * w + jj);
                    ++num;
                }
                    
            }
        }
    }
    return num;
}


void Cdbscan::clusterOne(int query, set<int>& occuSetIn, set<int>& temp, set<int>& cluSetOut) {
    int Ptnew;
    int cluster = 0;
    Ptnew = Cdbscan::findNei(query, occuSetIn, temp);  // 先放入temp中
    // if (Ptnew == 0) return ++cluster;
    int next;
    while (1)
    {
        if (Ptnew == 0) break;
        auto it = temp.begin();
        next = *it;
        if (next == 0) break;
        temp.erase(next);   // 这里每删一个，cluout就要insert一个
        cluSetOut.insert(next);
        occuSetIn.erase(next); 
        Cdbscan::clusterOne(next, occuSetIn, temp, cluSetOut);
    }
}

// cMapOut:first参数为gridID
void Cdbscan::dbscanSeg(map<int, Sta>& staMapIn, map<int, int>& cMapOut) {
    set<int> occuSet;
    Cdbscan::getOccuSet(staMapIn, occuSet);
    int w = Cdbscan::width;
    int h = Cdbscan::height;
	int clusterID = 0;
	set<int> temp;
	set<int> cluster;
	while(occuSet.size() > 1) {
        auto ite = occuSet.begin();
        srand(time(0));
        advance(ite, rand() % occuSet.size());
        Cdbscan::clusterOne(*ite, occuSet, temp, cluster);
        clusterID++;
        for (auto it = cluster.begin(); it != cluster.end(); ++it) {
            cMapOut.insert(make_pair(*it, clusterID));
        }
        temp.clear();
        cluster.clear();
    }
}

}