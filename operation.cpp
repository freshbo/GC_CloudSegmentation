#include "operation.h"
#include "global.h"

namespace operation
{


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
	
	void statisticalOutlierRemoval(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,int meanK,float thresh)
    {
		pcl::PointCloud<pcl::PointXYZ>::Ptr tmpOUT(new pcl::PointCloud<pcl::PointXYZ>());

        pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
        sor.setInputCloud(cloud);
        sor.setMeanK(meanK);
        sor.setStddevMulThresh(thresh);
        sor.filter(*tmpOUT);
        cloud->clear();
        pcl::copyPointCloud(*tmpOUT,*cloud);


        return;
    }
	void radiusOutlierRemoval(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,float)
	{
		pcl::PointCloud<pcl::PointXYZ>::Ptr out;
		out.reset(new pcl::PointCloud<pcl::PointXYZ>);

		pcl::RadiusOutlierRemoval<pcl::PointXYZ> outrem;
		// build the filter
		outrem.setInputCloud(cloud);
		outrem.setRadiusSearch(0.8);
		outrem.setMinNeighborsInRadius (2);
		// apply filter
		outrem.filter (*out);

		pcl::copyPointCloud(*out,*cloud);
	}

	void calcCurvature(PointCloudT::Ptr cloud, PointCloudN::Ptr normals)
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
		ne.setRadiusSearch (0.5);
		//ne.setKSearch(300);
		
		// Compute the features
		ne.compute (*normals);
		std::cout<<"Finish Normal Calculation"<<std::endl;
			
		return;
	}

	void linearizeCurvature(PointCloudN::Ptr normals)
	{
		for (size_t i = 0; i<normals->points.size(); i++)
		{		
			normals->points[i].curvature =log(max(normals->points.at(i).curvature,_ct));
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
	void colorizeCurvature(PointCloudN::Ptr normals, PointCloudT::Ptr wolke)
	{
		float curve_i;

		//Coloring Points according to estimated curvature using bernsteinpolynomials
		for (size_t i = 0; i<wolke->points.size(); i++)
		{					
		
			curve_i =(normals->points[i].curvature- _ct)/C_max;
			
			
			wolke->points[i].r= curve_i*255;
			wolke->points[i].g= (1-curve_i)*255;
			wolke->points[i].b= 128;
		}
		
		return;
	}
	void colorizeBinCluster(PointCloudT::Ptr cloud, vector<int> cluster)
	{
		if (cluster.size()!= cloud->size())
			return;
		float g = 61;
		int e = 0;
		for( int i= 0; i< cloud->size();i++)
		{
			e = cluster.at(i);
			cloud->points[i].r =  (int) pow(g,e)%251;
			cloud->points[i].g =  (int) pow(g,e)%251;
			cloud->points[i].b =  (int) pow(g,e)%251;
		}

	}

	void downsample(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud, float sampleSize)
	{
		
		PointCloudT::Ptr tmp;
		tmp.reset(new PointCloudT);
		
		
		pcl::VoxelGrid<pcl::PointXYZRGBA> sor;
		sor.setInputCloud(cloud);
		sor.setLeafSize (sampleSize, sampleSize, sampleSize);
		sor.filter (*tmp);
		pcl::copyPointCloud(*tmp,*cloud);
				
		return;
	}

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
}//end namespace operation

namespace Segmentation
{
	vector<int> binary(PointCloudT::Ptr cloud, PointCloudN::Ptr normals,PointCloudT::Ptr Leafs ,PointCloudT::Ptr Stems)
	{

		int K = 10;
		GraphType *g = new GraphType(/*estimated # of nodes*/cloud->size() , /*estimated # of edges*/ K*cloud->size()); 
		int count =0;
		for(int i=0;i<cloud->size();i++)
		{
			g->  add_node();
			g -> add_tweights( i,   /* capacities */  _RS - log(normals->points[i].curvature), log( normals->points[i].curvature)-_RL);
		}
		
		
		//Set up Search method:
		pcl::KdTreeFLANN<pcl::PointXYZRGBA> kdtree; 
		kdtree.setInputCloud (cloud);

		//Save list of Indicees within cloud
		vector<int> pointIdxNKNSearch;
		vector<float> pointNKNsquaredDistance;
		

		for (int i=0; i<cloud->size();i++)
		{			
			//Search KNN for point i
			kdtree.nearestKSearch(cloud->points[i],K,pointIdxNKNSearch,pointNKNsquaredDistance);
			
			//Walk through NKN and sum up the curvature
			for(int k =0; k<pointIdxNKNSearch.size (); k++)
			{	
				//Weight increasing significance of neighborhood
				float w = 3.5;
				int j = pointIdxNKNSearch[k];
				g->add_edge(i,j,w*max(1/(normals->points.at(i).curvature),1/(normals->points.at(j).curvature)),0);
				
			}

		}
		
		float flow = g -> maxflow();
		int leafPointCount =0;
		int stemPointCount =0;
		vector<int> binCluster;
		
		Leafs->clear();
		Stems->clear();
		binCluster.clear();

		for(int i=0; i< cloud->size();i++){

			if(g->what_segment(i) == GraphType::SOURCE){
				Leafs->push_back(cloud->points[i]);
				Leafs->points[leafPointCount].r = 0;
				Leafs->points[leafPointCount].g = 0;
				Leafs->points[leafPointCount].b = 160;
				binCluster.push_back(2);
				leafPointCount++;
			}
			else{
				Stems->push_back(cloud->points[i]);
				Stems->points[stemPointCount].r = 120;
				Stems->points[stemPointCount].g = 120;
				Stems->points[stemPointCount].b = 0;
				binCluster.push_back(1);
				stemPointCount++;
			}
		}

		delete g;
		return binCluster;
	}	
	void filterBinary(PointCloudT::Ptr leafs, PointCloudT::Ptr stems, vector<int>*labels)
	{

	}
}