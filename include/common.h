#ifndef __COMMON__
#define __COMMON__


#include <set>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

using namespace std;

typedef pcl::PointXYZI PointT;

// // 这里定义的话，相当于是全局变量，不太好
// extern int w_ = 360;
// extern int h_ = 100;
// extern float r_ = 30;
// extern int n_ = 1;


// 定义网格中的统计数据
struct Sta {
    float iMean = 0;
    float giMean = 0;
    float ngiMean = 0;
    int zMinPtID = 0;
    set<int> PtID = {};
    set<int> gPtID = {};
    set<int> ngPtID = {};
};

#endif