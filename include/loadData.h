#ifndef __LOAD_DATA__
#define __LOAD_DATA__

#include "include/common.h"
#include <string>
#include <iostream>
#include <fstream>  // 否则ifstream会报错：不允许使用不完整的类型
// #include <istream>
#include <ostream>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

typedef pcl::PointXYZI PointT;

void fileToCloud(string filenameIn, pcl::PointCloud<PointT>::Ptr cloudOut);


#endif