
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
