#include "operation.h"
#include "global.h"

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
		ne.setRadiusSearch (1);
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

	void curvatureColorMap(PointCloudN::Ptr normals, PointCloudT::Ptr wolke)
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

	void colorizeCluster(PointCloudT::Ptr cloud, vector<int> cluster)
	{
		if (cluster.size()!= cloud->size())
			return;
		float g = 12;
		int e = 0;
		for( int i= 0; i< cloud->size();i++)
		{
			e = cluster.at(i)*3;
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
	vector<int> MinCut(PointCloudT::Ptr cloud, PointCloudN::Ptr normals,PointCloudT::Ptr Leafs ,PointCloudT::Ptr Stems)
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
				int j = pointIdxNKNSearch[k];
				g->add_edge(i,j,max(1/(normals->points.at(i).curvature),1/(normals->points.at(j).curvature)),0);
				
			}

		}
		
		float flow = g -> maxflow();
		int leafPointCount =0;
		int stemPointCount =0;
		vector<int> binCluster;
		
		for(int i=0; i< cloud->size();i++){
			if(g->what_segment(i) == GraphType::SOURCE){
				Leafs->push_back(cloud->points[i]);
				Leafs->points[leafPointCount].r = 0;
				Leafs->points[leafPointCount].g = 0;
				Leafs->points[leafPointCount].b = 160;
				binCluster.push_back(1);
				leafPointCount++;
			}
			else{
				Stems->push_back(cloud->points[i]);
				Stems->points[stemPointCount].r = 120;
				Stems->points[stemPointCount].g = 120;
				Stems->points[stemPointCount].b = 0;
				binCluster.push_back(2);
				stemPointCount++;
			}
		}

		delete g;
		return binCluster;
	}
		
}