#include "include/dataToGrid.h"


namespace dtgSpace {

// 完成水平距离的滤波，同时将水平距离和偏航角给保存起来
void Cdtg::preProcess(	const pcl::PointCloud<PointT>& cloudIn,
                        pcl::PointCloud<PointT>& cloudOut, 
                        vector<float>& yaw, vector<float>& range ) {
    float x, y;
    for (int i = 0; i < cloudIn.size(); ++i) {
        x = cloudIn.points[i].x;
        y = cloudIn.points[i].y;
        float r = Cdtg::getRange(x, y);
        if (r > Cdtg::rangeth) continue;
        else {
            cloudOut.push_back(cloudIn.points[i]);
            range.push_back(r);
            float yaw_ = Cdtg::getYaw(x, y);
            if (yaw_ < 0) yaw_ += 360;
            yaw.push_back(yaw_);
        }
    }                    
}

void Cdtg::getGrid(  const pcl::PointCloud<PointT>& cloudIn, 
                    vector<float>& yaw, vector<float>& range, 
                    map<int, Sta>& staMapOut    ) {
    float rangeGap = Cdtg::rangeth / Cdtg::height;
    float yawGap = 360.0 / Cdtg::width;
    int row_i, col_j, gridID;
    Sta sta;
    for (int i = 0; i < cloudIn.size(); ++i) {
        row_i = floor(range[i] / rangeGap);
        col_j = floor(yaw[i] / yawGap);
        gridID = row_i * Cdtg::width + col_j;
        auto ite = staMapOut.find(gridID);
        if (ite == staMapOut.end()) {
            sta.iMean = cloudIn.points[i].intensity;
            sta.PtID.insert(i);
            sta.zMinPtID = i;
            staMapOut.insert(make_pair(gridID, sta));
            sta.PtID.clear();
        } else {
            ite->second.PtID.insert(i);
            ite->second.iMean += (cloudIn.points[i].intensity - ite->second.iMean) / ite->second.PtID.size();
            if (cloudIn.points[i].z < cloudIn.points[ite->second.zMinPtID].z) ite->second.zMinPtID = i;
        }       
    }
}


}