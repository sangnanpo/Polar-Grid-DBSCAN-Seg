#ifndef __GROUND_REMOVE__
#define __GROUND_REMOVE__

#include "include/common.h"
#include "include/dataToGrid.h"
#include <map>
#include <cmath>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

namespace grSpace {
typedef pcl::PointXYZI PointT;
class Cgr {
public:
    Cgr (float t = 15, float d = 0.1, float z = -0.5): thetath(t), distth(d), zth(z) { }
    // ~Cgr();
    void groundSeg(const pcl::PointCloud<PointT>& cloudIn, map<int, Sta>& staMap,
                    pcl::PointCloud<PointT>& gcloud, pcl::PointCloud<PointT>& ngcloud);
    
private:
    float getDist3(const pcl::PointCloud<PointT>& cloudIn, int i, int j);
    float getTheta(const pcl::PointCloud<PointT>& cloudIn, int i, int j);
    float thetath;
    float distth;
    float zth;
};
}



#endif