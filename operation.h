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

//Curvature
#include <pcl/common/pca.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/normal_3d_omp.h> //parllel

//triangulation
#include <pcl/surface/gp3.h> //PCL
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h> //CGAL
//...
#include <CGAL/Triangulation_3.h> //CGAL
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Regular_triangulation_3.h>

//Boost Min Cut
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boykov_kolmogorov_max_flow.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>


//PCL typedefs for Point Clouds
typedef pcl::PointXYZRGBA					PointT;
typedef pcl::PointCloud<PointT>				PointCloudT;
typedef pcl::Normal							PointN;
typedef pcl::PointCloud<PointN>				PointCloudN;
typedef pcl::PointNormal					PointNP;
typedef pcl::PointCloud<PointNP>			PointCloudNP;
typedef pcl::PolygonMesh					Mesh;



// CGAL typedefs for Triangulation
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_3<K> Triangulation;
typedef Triangulation::Finite_vertices_iterator Finite_vertices_iterator;
typedef Triangulation::Finite_edges_iterator Finite_edges_iterator;
typedef Triangulation::Finite_facets_iterator Finite_facets_iterator;
typedef Triangulation::Finite_cells_iterator Finite_cells_iterator;
typedef Triangulation::Simplex Simplex;
typedef Triangulation::Locate_type Locate_type;
typedef Triangulation::Point Point;

//Boost typedefs for Mincut
using namespace boost;
typedef int EdgeWeightType;
typedef adjacency_list_traits < vecS, vecS, directedS > Traits;
typedef adjacency_list < vecS, vecS, directedS,
		property < vertex_name_t, std::string,
		property < vertex_index_t, long,
		property < vertex_color_t, boost::default_color_type,
		property < vertex_distance_t, long,
		property < vertex_predecessor_t, Traits::edge_descriptor > > > > >,
		property < edge_capacity_t, EdgeWeightType,
		property < edge_residual_capacity_t, EdgeWeightType,
		property < edge_reverse_t, Traits::edge_descriptor > > > > Graph;
typedef boost::property_map< Graph, boost::edge_residual_capacity_t >::type ResidualCapacityMap;
typedef boost::property_map< Graph, boost::vertex_index_t >::type IndexMap;
typedef boost::graph_traits< Graph >::out_edge_iterator OutEdgeIterator;


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
	void				linearizeCurvature(PointCloudN::Ptr);
	void				colorizeDefault(PointCloudT::Ptr);
	void				curvatureColorMap(PointCloudN::Ptr curve, PointCloudT::Ptr cloud);
	//Triangulations
	Mesh				PCLtriangulation(PointCloudT::Ptr,PointCloudN::Ptr);
	void				CGALtriangulation_regular(void);
	//MIN-Cut
	void				MaxFlow(PointCloudT::Ptr,PointCloudN::Ptr);
}


//Segmentation Methods
vector<pcl::PointIndices>cutIt(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr,pcl::PointCloud<pcl::Normal>::Ptr);
void					CalculateUnaryWeights(float Curvature,float &sourceWeight,float &sinkWeight);

Traits::edge_descriptor AddEdge(Traits::vertex_descriptor &v1,
								Traits::vertex_descriptor &v2,
								property_map < Graph, edge_reverse_t >::type &rev,
								const double capacity,
								Graph &g);



