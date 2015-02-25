#pragma once

#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include <set>

//Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>

//Outlier Removal
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/conditional_removal.h>

//Curvature
#include <pcl/common/pca.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/normal_3d_omp.h> //parllel

//Triangulation
#include <pcl/surface/gp3.h>
//Boost Sparse Matrix for Adjacency Matrix
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>

//visualization
#include <pcl/visualization/pcl_visualizer.h>

//Downsampling
#include <pcl/filters/voxel_grid.h>

//Graph
#include "graph.h"




//PCL typedefs for Point Clouds
typedef pcl::PointXYZRGBA					PointT;
typedef pcl::PointCloud<PointT>				PointCloudT;
typedef pcl::Normal							PointN;
typedef pcl::PointCloud<PointN>				PointCloudN;
typedef pcl::PointNormal					PointNP;
typedef pcl::PointCloud<PointNP>			PointCloudNP;
typedef pcl::PolygonMesh					pclMesh;

//Typedef MaxFlow Graph
typedef Graph<float,float,float> GraphType;

namespace operation
{

	string 				loadPLY(std::string path,PointCloudT::Ptr);
    void                statisticalOutlierRemoval(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,int,float);
	void                radiusOutlierRemoval(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,float);
	void				calcCurvature(PointCloudT::Ptr cloud,PointCloudN::Ptr);
	void				linearizeCurvature(PointCloudN::Ptr);
	void				colorizeDefault(PointCloudT::Ptr);
	void				colorizeCurvature(PointCloudN::Ptr curve, PointCloudT::Ptr cloud);
	void				colorizeBinCluster(PointCloudT::Ptr cloud, vector<int> cluster);
	void				downsample(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr,pcl::PointCloud<pcl::PointXYZRGBA>::Ptr,float);
	
	void				PCLtriangulation(PointCloudT::Ptr,PointCloudN::Ptr,pclMesh::Ptr);
	float				dist(pcl::PointXYZRGBA p, PointCloudT::Ptr cloud);
}

namespace Segmentation
{
	vector<int>			binary(PointCloudT::Ptr cloud, PointCloudN::Ptr normals,PointCloudT::Ptr L,PointCloudT::Ptr S);
	void				filterBinary(PointCloudT::Ptr leafs, PointCloudT::Ptr stems, vector<int>*labels);
}

