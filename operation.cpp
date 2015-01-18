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
	
	vector<float> operation::bernsteinDrei(float x)
	{
		vector<float> result;

		result.push_back((1-x)*(1-x));
		result.push_back(2*x*(1-x));
		result.push_back(x*x);

		return result;
	}

		vector<float> operation::bernsteinZwei(float x)
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

		std::cout<<"loadPLY: "<<cloud->points.size()<<std::endl;
		
		
		return ID;		
	}

	 void calcNormals(PointCloudT::Ptr cloud, PointCloudN::Ptr normals)
	{
		std::cout<<"Start Normal Calculation"<<std::endl;
		// Create the normal estimation class, and pass the input dataset to it
		
		//pcl::NormalEstimation<PointT, pcl::Normal> ne;
		pcl::NormalEstimationOMP<PointT,pcl::Normal> ne;
		ne.setNumberOfThreads(3);

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
	 
	void operation::colorizeDefault(PointCloudT::Ptr cloud)
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
		//Function Curvature |-> Color per pixle.
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

		//Coloring Points according to estimated curvature using bernsteinpolynomials
		vector<float> bernstein;
		for (size_t i = 0; i<wolke->points.size(); i++)
		{			
			
			curve_i =abs(log(max(normals->points.at(i).curvature,c_p))/maxi);
			bernstein = bernsteinZwei(curve_i);
			
			wolke->points[i].r= bernstein[0]*255;
			wolke->points[i].g= bernstein[1]*255;
			wolke->points[i].b= bernstein[2]*255;
		}
		return;
	}

	//Triangulation
	Mesh triangulation(PointCloudT::Ptr inputCloud,PointCloudN::Ptr normals)
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
	void binarySegmentation()
	{

	}
}