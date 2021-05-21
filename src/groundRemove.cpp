#include "include/groundRemove.h"
#include<iostream>

using namespace std;

namespace grSpace {

float Cgr::getDist3(const pcl::PointCloud<PointT>& cloudIn, int i, int j) {
	if (i == j) return 0;
	float dx = cloudIn.points[i].x - cloudIn.points[j].x;
	float dy = cloudIn.points[i].y - cloudIn.points[j].y;
	float dz = cloudIn.points[i].z - cloudIn.points[j].z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

float Cgr::getTheta(const pcl::PointCloud<PointT>& cloudIn, int i, int j) {
	if (i == j) return 0;
	float dx = cloudIn.points[i].x - cloudIn.points[j].x;
	float dy = cloudIn.points[i].y - cloudIn.points[j].y;
	float dz = cloudIn.points[i].z - cloudIn.points[j].z;
	float theta = atan(fabs(dz) / sqrt(dx * dx + dy * dy)) * 180 / M_PI;
	return theta;
}


void Cgr::groundSeg( const pcl::PointCloud<PointT>& cloudIn, map<int, Sta>& staMap,
                    pcl::PointCloud<PointT>& gcloud, pcl::PointCloud<PointT>& ngcloud) {
    bool distJudge, thetaJudge;
    for (auto it = staMap.begin(); it != staMap.end(); ++it) {
        if (cloudIn.points[it->second.zMinPtID].z < Cgr::zth) { // 说明该网格内有地面点
            for (auto ite = it->second.PtID.begin(); ite != it->second.PtID.end(); ++ite) {
                distJudge = Cgr::getDist3(cloudIn, *ite, it->second.zMinPtID) < Cgr::distth;
                thetaJudge = Cgr::getTheta(cloudIn, *ite, it->second.zMinPtID) < Cgr::thetath;
                if (distJudge || thetaJudge) { // 地面点判断条件
                    it->second.gPtID.insert(*ite);
                    it->second.giMean += (cloudIn.points[*ite].intensity - it->second.giMean) / it->second.gPtID.size();
                } else {
                    it->second.ngPtID.insert(*ite);
                    it->second.ngiMean += (cloudIn.points[*ite].intensity - it->second.ngiMean) / it->second.ngPtID.size();
                }
            }
        } else { // 说明该网格内都不是地面点
            for (auto ite = it->second.PtID.begin(); ite != it->second.PtID.end(); ++ite) {
                it->second.ngPtID.insert(*ite);
                it->second.ngiMean += cloudIn.points[*ite].intensity;
            }
            it->second.ngiMean /= it->second.ngPtID.size(); // 先累加，再一个除法，能快一些
        }
    }

    for (auto it = staMap.begin(); it != staMap.end(); ++it) {
        for (auto ite = it->second.ngPtID.begin(); ite != it->second.ngPtID.end(); ++ite) {
            ngcloud.push_back(cloudIn.points[*ite]);
        }
        for (auto ite = it->second.gPtID.begin(); ite != it->second.gPtID.end(); ++ite) {
            gcloud.push_back(cloudIn.points[*ite]);
        }
    }
}

}



