#pragma once

#include <math.h>

//Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>

//Curvature
#include <pcl/common/pca.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/normal_3d_omp.h> //parllel

//triangulation
#include <pcl/surface/gp3.h>

// Segmentation
//#include <pcl\filters\passthrough.h>




typedef pcl::PointXYZRGBA				PointT;
typedef pcl::PointCloud<PointT>			PointCloudT;
typedef pcl::Normal						PointN;
typedef pcl::PointCloud<PointN>			PointCloudN;
typedef pcl::PolygonMesh				Mesh;


namespace frameOperation
{
	void				loadSequence(std::string filePath);
	void				eraseSequence(void);
}

namespace operation
{
	vector<float>		bernsteinDrei(float);
	vector<float>		bernsteinZwei(float);
	string 				loadPLY(std::string path,PointCloudT::Ptr);
	void				calcNormals(PointCloudT::Ptr cloud,PointCloudN::Ptr);
	void				colorizeDefault(PointCloudT::Ptr);
	void				curvatureColorMap(PointCloudN::Ptr curve, PointCloudT::Ptr cloud);
	Mesh				triangulation(PointCloudT::Ptr,PointCloudN::Ptr);
	void				binarySegmentation();
	
}
