#pragma once

#include <math.h>
#include <iostream>
#include <fstream>
#include <list>
#include <set>

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
#include <pcl/surface/gp3.h> //PCL
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h> //CGAL

#include <CGAL/Triangulation_3.h> //CGAL
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Regular_triangulation_3.h>

//Min Cut
#include <boost\graph\edmonds_karp_max_flow.hpp>
#include <boost\graph\stoer_wagner_min_cut.hpp>


typedef pcl::PointXYZRGBA				PointT;
typedef pcl::PointCloud<PointT>			PointCloudT;
typedef pcl::Normal						PointN;
typedef pcl::PointCloud<PointN>			PointCloudN;
typedef pcl::PolygonMesh				Mesh;

// CGAL Types for Triangulation
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_3<K> Triangulation;
typedef Triangulation::Finite_vertices_iterator Finite_vertices_iterator;
typedef Triangulation::Finite_edges_iterator Finite_edges_iterator;
typedef Triangulation::Finite_facets_iterator Finite_facets_iterator;
typedef Triangulation::Finite_cells_iterator Finite_cells_iterator;
typedef Triangulation::Simplex Simplex;
typedef Triangulation::Locate_type Locate_type;
typedef Triangulation::Point Point;


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
	//Triangulations
	Mesh				PCLtriangulation(PointCloudT::Ptr,PointCloudN::Ptr);
	void				CGALtriangulation_regular(void);
	//MIN-Cut
	void				MaxFlow(PointCloudT::Ptr,PointCloudN::Ptr);
}
