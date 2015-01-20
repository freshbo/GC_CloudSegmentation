#include "operation.h"

namespace frameOperation
{
	void loadSequence(std::string filePath)
	{
		//analyse filename
		char delimiter = '/';
		std::string s;
		std::cout<<filePath<<std::endl;
		
		/*

		PointCloudT::Ptr cloud;
		cloud = operation::loadPLY(filePath);
	*/
	}
}


namespace operation
{
	vector<float> bernsteinDrei(float x)
	{
		vector<float> result;

		result.push_back((1-x)*(1-x));
		result.push_back(2*x*(1-x));
		result.push_back(x*x);

		return result;
	}

		vector<float> bernsteinZwei(float x)
	{
		vector<float> result;

		result.push_back(1-x);
		result.push_back(x);
		result.push_back(0);

		return result;
	}

	string loadPLY(std::string path, PointCloudT::Ptr cloud)
	{	
		//This block extracts the Name of the File. 
		string ID;
		int begin=0;
		int limit = path.length()-1;
		int i = limit;
		while (path.at(i)!='/')
		{
			if (path.at(i)=='.')
				limit = i;
			begin = i;
			i--;
		}
		for (int i = begin; i< limit; i++)
		{
			ID.push_back(path.at(i));
		}

		pcl::PLYReader reader;
		reader.read(path,*cloud,0);

		//std::cout<<"loadPLY: "<<cloud->points.size()<<std::endl;
		return ID;		
	}

	 void calcNormals(PointCloudT::Ptr cloud, PointCloudN::Ptr normals)
	{
		std::cout<<"Start Normal Calculation"<<std::endl;
		// Create the normal estimation class, and pass the input dataset to it
		
		//pcl::NormalEstimation<PointT, pcl::Normal> ne; //One Core
		pcl::NormalEstimationOMP<PointT,pcl::Normal> ne; //Multi Core
		ne.setNumberOfThreads(8);

		ne.setInputCloud (cloud);
		
		// Create an empty kdtree representation, and pass it to the normal estimation object.
		// Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
		pcl::search::KdTree<PointT>::Ptr tree (new pcl::search::KdTree<PointT> ());
		ne.setSearchMethod (tree);

		// Use all neighbors in a sphere of radius 3cm
		//ne.setRadiusSearch (10);
		ne.setKSearch(1000);
		
		// Compute the features
		ne.compute (*normals);
		std::cout<<"Finish Normal Calculation"<<std::endl;
			
		return;
	}

	void linearizeCurvature(PointCloudN::Ptr normals)
	{
	
		float c_p = 0.005;
		float curve_i;
		float mini=1;
		float maxi=0;
		
		for(size_t i =0; i < normals->points.size(); i++)
		{
			//linearize Curvature values.
			curve_i =(-1)* log(max(normals->points.at(i).curvature,c_p));	
			if(curve_i<mini)
				mini=curve_i;

			if(curve_i>maxi)
				maxi=curve_i;
		}

		for (size_t i = 0; i<normals->points.size(); i++)
		{		
			normals->points[i].curvature =abs(log(max(normals->points.at(i).curvature,c_p))/maxi);
		}

		return;
	}
	 
	void colorizeDefault(PointCloudT::Ptr cloud)
	{
		float maximum =cloud->points[0].z;
		float minimum =cloud->points[0].z;
		for (size_t i = 0; i<cloud->points.size(); i++){
				maximum = max(maximum,cloud->points[i].z);
			
				minimum = min(minimum,cloud->points[i].z);
		}

		//Colorize All Points with Standard Color
		for (size_t i = 0; i<cloud->points.size(); i++){

			cloud->points[i].r = 0;
			cloud->points[i].g = 70 + 100*((cloud->points[i].z-minimum)/(maximum-minimum));
			cloud->points[i].b = 0;
		}
	}

	void curvatureColorMap(PointCloudN::Ptr normals, PointCloudT::Ptr wolke)
	{
		float curve_i;
		//Coloring Points according to estimated curvature using bernsteinpolynomials
		vector<float> bernstein;
		for (size_t i = 0; i<wolke->points.size(); i++)
		{					
			curve_i =normals->points[i].curvature;
			bernstein = bernsteinZwei(curve_i);
			
			wolke->points[i].r= bernstein[0]*255;
			wolke->points[i].g= bernstein[1]*255;
			wolke->points[i].b= bernstein[2]*255;
		}

		return;
	}

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
	void MaxFlow(PointCloudT::Ptr cloud, PointCloudN::Ptr curve)
	{
		
		//Points to Work with;
		PointT searchPoint;
		PointN searchPointCurve;
		PointN neighborPointCurve;
	
		//KNN Parameters
		int K = 10;
		vector<int> pointIdxNKNSearch(K);
		vector<float> pointNKNsquaredDistance(K);
		int pointCount = cloud->size();
	
		//KDTree + setInput
		pcl::KdTreeFLANN<pcl::PointXYZRGBA> kdtree;
		kdtree.setInputCloud (cloud);
	
		//Graph for MaxFlow/MinCut
		//GraphType *g = new GraphType(/*estimated # of nodes*/ pointCount * K, /*estimated # of edges*/ K);
		float curvature; 
	
		//Fill Graph with nodes
		for(int i =0; i<pointCount;i++)
		{
			//g->add_node(i);
		}
		cout<<"NODES BUILT"<<endl;

		// For each Point i search K-NN j
		for(int i=0; i< pointCount; i++)
		{
			//Set working Points
			searchPoint = cloud->points[i];
			searchPointCurve = curve->points[i];

			//Search KNN
			kdtree.nearestKSearch(searchPoint,K,pointIdxNKNSearch,pointNKNsquaredDistance);
			curvature = searchPointCurve.curvature;

			/*
			CALCULATE PROBABILITY OF BELONGING TO SOURCE OR SINK
			*/
			

			//SET T-Links to Source and Sink
			//g->add_tweights(i,curvature,curvature);
			cout<<curvature<<endl;
		
			for(int j =0; j<pointIdxNKNSearch.size (); j++)
			{
				neighborPointCurve = curve->at(j);
				//g->add_edge(i,j,curvature,curvature);

			}
		}
		//float flow = g->maxflow();

		for(int i=0;i<pointCount;i++)
		{
			//if (g->what_segment(i) == GraphType::SOURCE)
			{
				//cout<<i<<" SOURCE"<<endl;
				cloud->points[i].r = 128;
				cloud->points[i].g = 128;
				cloud->points[i].b = 128;
			}
			//else
			{
				cloud->points[i].r = 255;
				cloud->points[i].g = 255;
				cloud->points[i].b = 255;
			}
		}
	}
}//end namespace operation


////////////////////////////////////////////////////////////////////////////////////////////////////
//                               GRAPH SEGMENTATION                                               //
////////////////////////////////////////////////////////////////////////////////////////////////////
vector<pcl::PointIndices> cutIt(PointCloudT::Ptr cloud , PointCloudN::Ptr normals)
{
	using namespace boost;

	//Points to Work with;
	PointT searchPoint;
	PointN searchPointCurve;
	PointN neighborPointCurve;
	double curvature;
	double curvature_neighbor;
	
	//KNN Parameters
	int K = 10;
	vector<int> pointIdxNKNSearch(K);
	vector<float> pointNKNsquaredDistance(K);
		
	//KDTree + setInput
	pcl::KdTreeFLANN<pcl::PointXYZRGBA> kdtree;
	kdtree.setInputCloud (cloud);
	

	Graph g; //a graph with 0 vertices
 
	property_map < Graph, edge_reverse_t >::type rev = get(edge_reverse, g);
	
	std::vector< Traits::vertex_descriptor> vertices_;	//Vector to save Nodes
	Traits::vertex_descriptor vertex_descriptor(0.0);		//a single Node;

	int size = cloud->points.size();

	vertices_.clear ();
	vertices_.resize (size + 2, vertex_descriptor);     //allocate memory for all nodes + sink and source
	Traits::vertex_descriptor source = add_vertex(g);	//Create Sink and source
	Traits::vertex_descriptor sink = add_vertex(g);


	for (int i=0;i<size;i++){
		curvature = normals->points[i].curvature;
		vertices_[i] = add_vertex(g);
		AddEdge(source,vertices_[i],rev,static_cast<double>(curvature)*10,g);
		AddEdge(sink,vertices_[i],rev,static_cast<double>(1-curvature)*10,g);
	}

	for (int i=0; i<size;i++){
		searchPoint = cloud->points[i];
		//Search KNN for point i
		kdtree.nearestKSearch(searchPoint,K,pointIdxNKNSearch,pointNKNsquaredDistance);
		curvature = searchPointCurve.curvature;
		//Walk through NKN
		for(int j =0; j<pointIdxNKNSearch.size (); j++){
			curvature_neighbor = (double)normals->points[pointIdxNKNSearch[j]].curvature*10;
			AddEdge(vertices_[i],vertices_[j],rev,(double)abs(curvature-curvature_neighbor)*10,g);
		}
	}

	IndexMap index_map = boost::get (boost::vertex_index, g);
	ResidualCapacityMap residual_capacity = boost::get (boost::edge_residual_capacity, g);

	//find min cut
	double flow = boykov_kolmogorov_max_flow(g, source, sink); // a list of sources will be returned in s, and a list of sinks will be returned in t
	//EdgeWeightType flow = push_relabel_max_flow(g, source, sink); // a list of sources will be returned in s, and a list of sinks will be returned in t
	//EdgeWeightType flow = edmunds_karp_max_flow(g, v0, v3); // a list of sources will be returned in s, and a list of sinks will be returned in t
 
	std::cout << "Max flow is: " << flow << std::endl;
	

	std::vector<pcl::PointIndices> clusters_;

	std::vector<int> labels;
	labels.resize (cloud->points.size (), 0);
	int number_of_indices = static_cast<int> (cloud->points.size ());
	for (int i_point = 0; i_point < number_of_indices; i_point++)
		labels[i_point] = 1;

	clusters_.clear ();
  
	pcl::PointIndices segment;
	clusters_.resize (2, segment);

	OutEdgeIterator edge_iter, edge_end;
	for ( boost::tie (edge_iter, edge_end) = boost::out_edges (source, g); edge_iter != edge_end; edge_iter++ )
	{
		if (labels[edge_iter->m_target] == 1)
		{
			if (residual_capacity[*edge_iter] > 0.01)
				clusters_[1].indices.push_back (static_cast<int> (edge_iter->m_target));
			else
				clusters_[0].indices.push_back (static_cast<int> (edge_iter->m_target));
		}
	}
	

	return clusters_;
}

Traits::edge_descriptor AddEdge(Traits::vertex_descriptor &v1,
	Traits::vertex_descriptor &v2, 
	property_map < Graph, edge_reverse_t >::type &rev, 
	const double capacity, Graph &g)
{
	Traits::edge_descriptor e1 = add_edge(v1, v2, g).first;
	Traits::edge_descriptor e2 = add_edge(v2, v1, g).first;
	put(edge_capacity, g, e1, capacity);
	put(edge_capacity, g, e2, capacity);
 
	rev[e1] = e2;
	rev[e2] = e1;

	return e1;
}

void CalculateUnaryWeights(float curvature, float& sourceWeight, float& sinkWeight)
{


	return;
}


