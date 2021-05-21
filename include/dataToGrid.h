#ifndef __DATA_TO_GRID__
#define __DATA_TO_GRID__

#include "include/common.h"
#include <set>
#include <map>
#include <vector>
#include <cmath>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

using namespace std;

typedef pcl::PointXYZI PointT;

namespace dtgSpace {

class Cdtg {
public:
    // 实际上两个都有默认值，g在创建时就有了，而rth也是定值，都在common.h中，感觉怪怪的
    Cdtg (int w = 360, int h = 100, float r = 30): width(w), height(h), rangeth(r) { }
    ~Cdtg() { sta.PtID.clear(); sta.gPtID.clear(); sta.ngPtID.clear(); }

    void preProcess(	const pcl::PointCloud<PointT>& cloudIn, 
                        pcl::PointCloud<PointT>& cloudOut, 
                        vector<float>& yaw, vector<float>& range );

    void getGrid(   const pcl::PointCloud<PointT>& cloudIn, 
                    vector<float>& yaw, vector<float>& range, 
                    map<int, Sta>& staMapOut );
    

private: 
    inline float getRange(float x, float y) { return sqrt(x * x + y * y); }
    inline float getYaw(float x, float y) { return atan2(y, x) * 180 / M_PI; }
    int width, height;
    float rangeth;
    // 定义grid中需要保存的数据
    Sta sta;
};
}



#endif
