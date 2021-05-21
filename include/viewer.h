#ifndef __VIEWER__
#define __VIEWER__

#include "include/common.h"
#include <pcl/visualization/pcl_visualizer.h>


using namespace std;

extern float colors[];


void segShow(	const pcl::PointCloud<PointT>& cloudIn, 
				map<int, Sta>& staMapIn,
				map<int, int>& cMapIn, bool gShowFlag);


#endif