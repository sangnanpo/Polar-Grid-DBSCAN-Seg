#include "include/viewer.h"


float colors[] = {
		0,   0,   0,
		255, 0,   0,   // red 		1
		0,   255, 0,   // green		2
		0,   0,   255, // blue		3
		255, 255, 0,   // yellow		4
		0,   255, 255, // light blue	5
		255, 0,   255, // magenta     6
		255, 255, 255, // white		7
		255, 128, 0,   // orange		8
		255, 153, 255, // pink		9
		51,  153, 255, //			10
		153, 102, 51,  //			11
		128, 51,  153, //			12
		153, 153, 51,  //			13
		163, 38,  51,  //			14
		204, 153, 102, //		15
		204, 224, 255, //		16
		128, 179, 255, //		17
		206, 255, 0,   //			18
		255, 204, 204, //			19
		204, 255, 153, //			20
	}; // 20x3=60 color elements
	
// 默认显示地面
void segShow(	const pcl::PointCloud<PointT>& cloudIn, 
				map<int, Sta>& staMapIn,
				map<int, int>& cMapIn, bool gShowFlag = true) {
	
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(
			new pcl::PointCloud<pcl::PointXYZRGB>);
	int clusterID;
	pcl::PointXYZRGB p;
	for (auto it = staMapIn.begin(); it != staMapIn.end(); ++it) {
		if (gShowFlag && it->second.gPtID.size() > 0) {
			for (auto ite = it->second.gPtID.begin(); ite != it->second.gPtID.end(); ++ite) {
				p.x = cloudIn.points[*ite].x;
				p.y = cloudIn.points[*ite].y;
				p.z = cloudIn.points[*ite].z;
				// 地面设置为白色
				p.r = 255;
				p.g = 255;
				p.b = 255;
				cloud->points.push_back(p);
			}
		}
		// 不管哪一种，都要显示出非地面
		if (it->second.ngPtID.size() > 0) {	// 说明该网格有非地面点
			auto k = cMapIn.find(it->first);
			clusterID = k->second;
			for (auto ite = it->second.ngPtID.begin(); ite != it->second.ngPtID.end(); ++ite) {
				p.x = cloudIn.points[*ite].x;
				p.y = cloudIn.points[*ite].y;
				p.z = cloudIn.points[*ite].z;
				p.r = colors[(clusterID%20)*3];
				p.g = colors[(clusterID%20)*3 + 1];
				p.b = colors[(clusterID%20)*3 + 2];
				cloud->points.push_back(p);
			}
		}
		
    }

	cout << "the size of cloud on this viewer is: " << cloud->size() << endl;

	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer
		(new pcl::visualization::PCLVisualizer("3D Viewer"));

    
    viewer->addPointCloud<pcl::PointXYZRGB>(cloud, "sample cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud"); // 设置点云大小

    while (!viewer->wasStopped())
    {
        viewer->spinOnce(100);
        boost::this_thread::sleep(boost::posix_time::microseconds(100000));
    }
	
	// boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(
	// 		new pcl::visualization::PCLVisualizer("pcd")); //PCLVisualizer 可视化类
	// viewer->setBackgroundColor(0.8, 0.8, 0.8);
	// viewer->addCoordinateSystem(1);
	// viewer->addPointCloud(cloud, "cloud");
	// while (!viewer->wasStopped()) {
	// 	viewer->spin();
	// }
	// // delete cloud;	// 注意释放空间
}
