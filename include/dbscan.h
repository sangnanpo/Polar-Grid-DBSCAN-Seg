#ifndef __DBSCAN__
#define __DBSCAN__

#include "include/common.h"
#include <set>
#include <map>

namespace dbscanSpace {

class Cdbscan {
public:
    // 初始值都在common.h中给定
    Cdbscan(int w = 360, int h = 100, int n = 1) : width(w), height(h), nNum(n) {}
    // ~Cdbscan();
    void dbscanSeg(map<int, Sta>& staMapIn, map<int, int>& cMapOut);

private:
    inline void getOccuSet(map<int, Sta>& staMapIn, set<int>& occuSetOut);
    int findNei(int query, set<int>& occuSetIn, set<int>& neiSetOut);
    void clusterOne(int query, set<int>& occuSetIn, set<int>& temp, set<int>& cluSetOut);
    
    int width, height;
    int nNum;
};
}


#endif