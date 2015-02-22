///////////////////////////////////////////////////////////////////////
//OPERATION.H

//Triangulation
#include <pcl/surface/gp3.h> //PCL
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h> //CGAL
//...
#include <CGAL/Triangulation_3.h> //CGAL
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Regular_triangulation_3.h>



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



//Triangulations
	Mesh				PCLtriangulation(PointCloudT::Ptr,PointCloudN::Ptr);
	void				CGALtriangulation_regular(void);
    

///////////////////////////////////////////////////////////////////////	
//OPERATION.CPP
    
    //Triangulation
Mesh PCLtriangulation(PointCloudT::Ptr inputCloud,PointCloudN::Ptr normals)
	{
		//INitialize Clouds
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
		pcl::copyPointCloud(*inputCloud,*cloud);
		pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>());
		pcl::concatenateFields(*cloud,*normals,*cloud_with_normals);
		
		// Create search tree*
		pcl::search::KdTree<pcl::PointNormal>::Ptr tree2 (new pcl::search::KdTree<pcl::PointNormal>);
		tree2->setInputCloud (cloud_with_normals);

		// Initialize objects
		pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
		pcl::PolygonMesh triangles;

		// Set the maximum distance between connected points (maximum edge length)
		gp3.setSearchRadius (100);

		// Set typical values for the parameters
		gp3.setMu (2.5);
		gp3.setMaximumNearestNeighbors (100);
		gp3.setMaximumSurfaceAngle(M_PI);
		gp3.setMinimumAngle(M_PI/4);
		gp3.setMaximumAngle(M_PI/2);
		
		gp3.setNormalConsistency(true);
		

		// Get result
		gp3.setInputCloud (cloud_with_normals);
		gp3.setSearchMethod (tree2);
		gp3.reconstruct (triangles);

		// Additional vertex information
		std::vector<int> parts = gp3.getPartIDs();
		std::vector<int> states = gp3.getPointStates();
		
		return triangles;
	}


void CGALtriangulation_regular(void)
	{

		std::cout<<"START CGAL TRIANGULATION"<<std::endl;


		 // construction from a list of points :
		std::list<Point> L;
		L.push_front(Point(0,0,0));
		L.push_front(Point(1,0,0));
		L.push_front(Point(0,1,0));
		L.push_front(Point(0,1,1));
		
		Triangulation T(L.begin(), L.end());
		
		std::set<Simplex> simplices;
		
		Finite_vertices_iterator vit = T.finite_vertices_begin();
		simplices.insert(Simplex(vit));
		Finite_cells_iterator cit = T.finite_cells_begin();
		simplices.insert(Simplex(cit));
		Finite_edges_iterator eit = T.finite_edges_begin();
		simplices.insert(Simplex(*eit));
		Finite_facets_iterator fit = T.finite_facets_begin();
		simplices.insert(Simplex(*fit));
		

		
		for(Finite_edges_iterator ei= T.finite_edges_begin();ei!= T.finite_edges_end(); ei++)
		{
			/*Triangulation::Face& f = *(ei->first);
			int i = ei->second;
			Vertex vs = f.vertex(f.cw(i));
			Vertex vt = f.vertex(f.ccw(i));*/
	  }
	
		std::cout<<"END CGAL TRIANGULATION"<<std::endl;
	}
	


	


