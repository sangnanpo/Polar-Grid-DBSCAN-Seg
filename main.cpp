#include "include/loadData.h"
#include "include/groundRemove.h"
#include "include/dataToGrid.h"
#include "include/dbscan.h"
#include "include/viewer.h"

#include<iostream>
using namespace std;

int main(int argc, char** argv) {
    pcl::PointCloud<PointT>::Ptr cloud (
			new pcl::PointCloud<PointT>);
    pcl::PointCloud<PointT>::Ptr cloud_f (
			new pcl::PointCloud<PointT>);

    pcl::PointCloud<PointT>::Ptr cloud_g (
			new pcl::PointCloud<PointT>);
    pcl::PointCloud<PointT>::Ptr cloud_ng (
			new pcl::PointCloud<PointT>);
    

    string filename;
    if (argc == 1) { filename = "./data/test.bin"; }
    else if (argc == 2) { filename = argv[1]; }
    else { cerr << "Command line parameter is not expected" << endl; return -1; }
    
    fileToCloud(filename, cloud);
    
    // -------------------------
    // ------得到网格-------------
    // --------------------------
    dtgSpace::Cdtg dtg;
    vector<float> yaw, range;
    map<int, Sta> staMap;
    dtg.preProcess(*cloud, *cloud_f, yaw, range);
    dtg.getGrid(*cloud_f, yaw, range, staMap);

    // --------------------------
    // --------去除地面----------
    // --------------------------

    grSpace::Cgr gr;
    gr.groundSeg(*cloud_f, staMap, *cloud_g, *cloud_ng);

    // --------------------------
    // --------目标分割----------
    // --------------------------
    dbscanSpace::Cdbscan dbscan;
    map<int, int> cMap;
    dbscan.dbscanSeg(staMap, cMap);

    // --------------------------
    // ----------可视化-----------
    // --------------------------
    segShow(*cloud_f, staMap, cMap, true);
      
    return 0;
}