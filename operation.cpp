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
	
	void outlierRemoval(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,int meanK,float thresh)
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
		ne.setKSearch(500);
		
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

	void downsample(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr input,pcl::PointCloud<pcl::PointXYZRGBA>::Ptr output,float sampleSize)
	{
		
		pcl::VoxelGrid<pcl::PointXYZRGBA> sor;
		sor.setInputCloud(input);
		sor.setLeafSize (sampleSize, sampleSize, sampleSize);
		sor.filter (*output);

		return;
	}

	void calcDownsampledeCurvature(PointCloudT::Ptr cloud,PointCloudN::Ptr normals,PointCloudT::Ptr sampledCloud,PointCloudN::Ptr sampledNormals)
	//Take the average curvature from the original point Cloud as estimated curvature for the down sampled cloud.
	{
		//number of neighbors to be searched
		int K = 10;
		
		//Set up Search method:
		pcl::KdTreeFLANN<pcl::PointXYZRGBA> kdtree;
		kdtree.setInputCloud (cloud);

		//Save list of Indicees within cloud
		vector<int> pointIdxNKNSearch;
		vector<float> pointNKNsquaredDistance;
	
		//Walk through each point of the downsampled cloud
		for (int i=0; i<sampledCloud->size();i++)
		{
			
			float curvature_i = 0;
			
			//Search KNN for point i
			kdtree.nearestKSearch(sampledCloud->points[i],K,pointIdxNKNSearch,pointNKNsquaredDistance);
			
			//Walk through NKN and sum up the curvature
			for(int j =0; j<pointIdxNKNSearch.size (); j++)
			{
				curvature_i += normals->points[pointIdxNKNSearch[j]].curvature;
			}
			//divide curvature by number of neighbors used
			curvature_i = curvature_i/pointIdxNKNSearch.size();
			sampledNormals->points[i].curvature = curvature_i;
		}
		return;
	}

}//end namespace operation

namespace Segmentation
{
	PointCloudT MinCut(PointCloudT::Ptr cloud, PointCloudN::Ptr normals,PointCloudT::Ptr result)
	{

		GraphType *g = new GraphType(/*estimated # of nodes*/ 2, /*estimated # of edges*/ 1); 

		

		
		for(int i=0;i<cloud->size();i++)
		{
			g->  add_node();
			g -> add_tweights( i,   /* capacities */  normals->points[i].curvature, 1-normals->points[i].curvature );
		}
	
		int K = 10;
		//Set up Search method:
		pcl::KdTreeFLANN<pcl::PointXYZRGBA> kdtree; 
		kdtree.setInputCloud (cloud);

		//Save list of Indicees within cloud
		vector<int> pointIdxNKNSearch;
		vector<float> pointNKNsquaredDistance;
		

		//Walk through each point of the downsampled cloud
		for (int i=0; i<cloud->size();i++)
		{			
			//Search KNN for point i
			kdtree.nearestKSearch(cloud->points[i],K,pointIdxNKNSearch,pointNKNsquaredDistance);
			
			//Walk through NKN and sum up the curvature
			for(int j =0; j<pointIdxNKNSearch.size (); j++)
			{
				g->add_edge(i,pointIdxNKNSearch[j],abs(1-(normals->points[i].curvature - normals->points[pointIdxNKNSearch[j]].curvature)),abs(1-( normals->points[i].curvature - normals->points[pointIdxNKNSearch[j]].curvature)));
				
			}

		}
		


		double flow = g -> maxflow();
		
		for(int i=0; i< cloud->size();i++){
			result->push_back(cloud->points[i]);
			if(g->what_segment(i) == GraphType::SOURCE){
				result->points[i].r = 0;
				result->points[i].g = 0;
				result->points[i].b = 160;
			}
			else{
				result->points[i].r = 120;
				result->points[i].g = 120;
				result->points[i].b = 0;
			}
		}

		delete g;

		return *result;
	}
		
}