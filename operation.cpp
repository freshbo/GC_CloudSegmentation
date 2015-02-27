#include "operation.h"
#include "global.h"

namespace operation
{

	//Utility:
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
	void linearizeCurvature(PointCloudN::Ptr normals)
	{
		for (size_t i = 0; i<normals->points.size(); i++)
		{		
			normals->points[i].curvature =log(max(normals->points.at(i).curvature,_ct));
		}
		return;
	}
	float dist(pcl::PointXYZRGBA p, PointCloudT::Ptr cloud)
	{
		if(cloud->size()==0)
			return numeric_limits<float>::infinity(); //Return Infinity If cloud is Empty
		int K = 1;
		pcl::KdTreeFLANN<pcl::PointXYZRGBA> kdTree;
		vector <int> pointIdx;
		vector <float> sqDist;
		kdTree.setInputCloud(cloud);
		kdTree.nearestKSearch(p, K, pointIdx,sqDist);
		if(sqDist.size()<1)
			return -1; //Return -1 if no nearest neighbor was found
		return sqrt(sqDist.at(0)); 
	}
	bool compareClouds(PointCloudT::Ptr a,PointCloudT::Ptr b)
	{
		return a->size()>b->size();
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

	//Calculation
	void calcCurvature(PointCloudT::Ptr cloud, PointCloudN::Ptr normals)
	{
		
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
		
			
		return;
	}
	void downsample(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr input, pcl::PointCloud<pcl::PointXYZRGBA>::Ptr output, float sampleSize)
	{
		if(sampleSize == 0){
			pcl::copyPointCloud(*input,*output);
			return;
		}

		PointCloudT::Ptr tmp;
		tmp.reset(new PointCloudT);
		
		
		pcl::VoxelGrid<pcl::PointXYZRGBA> sor;
		sor.setInputCloud(input);
		sor.setLeafSize (sampleSize, sampleSize, sampleSize);
		sor.filter (*tmp);
		pcl::copyPointCloud(*tmp,*output);
				
		return;
	}
	vector<int> PCLtriangulation(PointCloudT::Ptr inputCloud,PointCloudN::Ptr normals, pclMesh::Ptr mesh)
	{
		//INitialize Clouds
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
		pcl::copyPointCloud(*inputCloud,*cloud);
		pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>());
		pcl::concatenateFields(*cloud,*normals,*cloud_with_normals);
		
		// Create search tree*
		pcl::search::KdTree<pcl::PointNormal>::Ptr tree (new pcl::search::KdTree<pcl::PointNormal>);
		tree->setInputCloud (cloud_with_normals);

		// Initialize objects
		pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;

		// Set the maximum distance between connected points (maximum edge length)
		gp3.setSearchRadius (3);

		gp3.setMaximumNearestNeighbors (100);
		gp3.setMu (100);

		gp3.setNormalConsistency(false);

		// Get result
		gp3.setInputCloud (cloud_with_normals);
		gp3.setSearchMethod (tree);
		gp3.reconstruct (*mesh);

		// Additional vertex information
		std::vector<int> parts = gp3.getPartIDs();
		std::vector<int> states = gp3.getPointStates();

		return parts;
	}

	//Colorization
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
		float g = 128;
		int e = 0;
		for( int i= 0; i< cloud->size();i++)
		{
			e = cluster.at(i);
			cloud->points[i].r =  (int) pow(g,e)%251;
			cloud->points[i].g =  (int) pow(g,e)%251;
			cloud->points[i].b =  (int) pow(g,e)%251;
		}

	}
	void colorizeLeafClusters(vectorCloud leafs, vector<int> labels)
	{
		//Apply colors to Clouds with certain label
		vector<int>c;
		
//COLOR 1		
		c.push_back(185);
		c.push_back(20);
		c.push_back(78);
//COLOR 2
		c.push_back(185);
		c.push_back(188);
		c.push_back(78);
//COLOR 3
		c.push_back(185);
		c.push_back(188);
		c.push_back(201);
//COLOR 4
		c.push_back(185);
		c.push_back(69);
		c.push_back(201);
//COLOR 5
		c.push_back(37);
		c.push_back(69);
		c.push_back(201);
//COLOR 6
		c.push_back(235);
		c.push_back(227);
		c.push_back(44);
//COLOR 7
		c.push_back(37);
		c.push_back(69);
		c.push_back(201);
		
		for(int i=0;i<labels.size();i++){
			for(int j=0;j<leafs->at(i)->size();j++)
		{
		
				leafs->at(i)->points[j].r = c[(i%7)*3+0];
				leafs->at(i)->points[j].g = c[(i%7)*3+1];
				leafs->at(i)->points[j].b = c[(i%7)*3+2];
			}
		}
	}
	

}//end namespace operation

namespace Segmentation
{
	//Binary
	vector<int> binary(PointCloudT::Ptr cloud, PointCloudN::Ptr normals,PointCloudT::Ptr L ,PointCloudT::Ptr S)
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
			pointIdxNKNSearch.clear();
			kdtree.nearestKSearch(cloud->points[i],K,pointIdxNKNSearch,pointNKNsquaredDistance);
			//Walk through NKN and sum up the curvature
			for(int k =0; k<pointIdxNKNSearch.size (); k++)
			{	
				//Weight increasing significance of neighborhood
				float w = 3.5;
				int j = pointIdxNKNSearch[k];
				//if (i != j)
				g->add_edge(i,j,w*max(1/(normals->points.at(i).curvature),1/(normals->points.at(j).curvature)),0);
				
			}

		}
		

		float flow = g -> maxflow();
		vector<int> binCluster;
		
		//Copy LeafPoints and Stem points into its respective Cloud L and S
		L->clear();
		S->clear();
		binCluster.clear();
		for(int i=0; i< cloud->size();i++)
			if(g->what_segment(i) == GraphType::SOURCE)
				binCluster.push_back(1);
			else
				binCluster.push_back(0);
			
		
		delete g;
		filterBinary(cloud,&binCluster);
		for(int i=0;i<cloud->size();i++)
		{
			if(binCluster.at(i)==1)
				L->push_back(cloud->points[i]);
			else
				S->push_back(cloud->points[i]);
		}
		return binCluster;
	}	
	void filterBinary(PointCloudT::Ptr cloud, vector<int>*labels)
	{
		pcl::KdTreeFLANN<pcl::PointXYZRGBA> kdtree; 
		kdtree.setInputCloud (cloud);
		
		vector<int>tmp(labels->size());
		copy(labels->begin(),labels->end(),tmp.begin());
		//Save list of Indicees within cloud
		vector<int> pointIdxNKNSearch;
		vector<float> pointNKNsquaredDistance;
		int K = 100;
		int labelI;
		int labelJ;
		int balance; /*is a measure of how many labels are LEAFS and how many are Stems. 
			The innermost loop below will compute +1 if labelJ == LabelI and
										  compute -1 if labelJ != LabelI
			if after that loop balance / K is <10% vector<int>labels will be switched at pos i
		*/
		for(int i=0;i<cloud->size();i++)
		{	
			balance = 0;
			//Search KNN for point i
			pointIdxNKNSearch.clear();
			kdtree.nearestKSearch(cloud->points[i],K,pointIdxNKNSearch,pointNKNsquaredDistance);
			//Walk through KNN
			labelI = tmp.at(i);

			for(int k = 0; k < pointIdxNKNSearch.size(); k++)
			{	
				int j = pointIdxNKNSearch[k];
				labelJ = tmp.at(j);
				if(labelJ==labelI)
					balance++;
				else
					balance--;
			}
			
			if(balance<30){
				labels->at(i)= abs(labels->at(i)-1);
			}

		}

	}
	//Multi Leaf
	void getConnectedLeafs(PointCloudT::Ptr L ,vectorCloud leafs, vector<int> *labels)
	{
		/*
		Find New Hypothesis by
			-Sample from L
			-Triangulating the sampled Cloud
			-get large enough Connected Components
			-export points from L into correctly respective PointCloud
		*/

		//Normals from L for triangulation
		PointCloudN::Ptr normal_L;
		normal_L.reset(new PointCloudN);
		//triangulation
		vector<int> parts;
		pclMesh::Ptr mesh;
		mesh.reset(new pclMesh);

		//function Calls
		operation::downsample(L,L,0.1); //sample L high resolution is not in this step
		operation::calcCurvature(L,normal_L); //Normal estimation on sampled L 
		parts = operation::PCLtriangulation(L,normal_L,mesh); //Triangulate L
		
		int min = 1000; //Min number needed to be recognised as Leaf
		getlargeComponents(/*Cloud*/L,/*ConnectedComponentIndex*/parts,/*MinNumber to be recognised*/min,/*return*/leafs);
		for(int i=0;i<leafs->size();i++)
		{
			labels->push_back(i);
		}
		

	}
	void getlargeComponents(PointCloudT::Ptr L,vector<int> parts,int min ,/*return*/vectorCloud leafs)
	{
		/*
			Get Connected Components with more than at least >min< vertecies:
				-Create Set s from vector<int>parts
				-init leafs (size = s.size())
				-for each Point in L
					-set it into the parts[i]th PointCloud at leafs
				throw away all clouds where cloud.size()<min
				return
		*/
		set<int> s(parts.begin(),parts.end()); //creates a Set of the ComponentIDs
		
		for(int i=0;i<s.size();i++)
		{
			PointCloudT::Ptr tmp_Ptr;
			tmp_Ptr.reset(new PointCloudT);
			leafs->push_back(tmp_Ptr);
		}

		for(int i=0;i<parts.size();i++)
		{
			PointT p = L->points[i];
			leafs->at(parts[i])->push_back(p);

		}
		std::sort(leafs->begin(),leafs->end(),operation::compareClouds);
		
		vector<PointCloudT::Ptr>::iterator it;

		for(it= leafs->begin(); it!=leafs->end();it++)
		{
			if(it->get()->size()<min)
				break;
		}
		leafs->erase(it,leafs->end());

	}
	
	void multiOrganSegmentation(PointCloudT::Ptr L, vectorCloud O_t,  vector<int>*labelsO,/*Output:*/vectorCloud leafs, vector<int>* LeafLabels )
	{
		/*
		Solve consisten Labeling via alpha-Expansion:
		-O_cur = current Organs (either leafs, or Stems)
		-O_neigh = Organs from a neighboring Frame (Forward or Backward)
		-labels_cur = current labels of the organs (this is going to be the 
		*/
		operation::downsample(L,L,0.5);
		GCoptimizationGeneralGraph *gc = new GCoptimizationGeneralGraph(L->size(),labelsO->size());
		
		pclMesh::Ptr mesh(new pclMesh); 
		PointCloudN::Ptr normal(new PointCloudN);
		operation::calcCurvature(L,normal);
		operation::PCLtriangulation(L,normal,mesh);

		//SET T-LINKS
		cout<<"set T-Links for "<< L->points.size()<<" "<<endl;
		for(int i=0;i<L->points.size();i++){						//all points
			for(int l=0;l<labelsO->size();l++)			//all labels
			{			
				pcl::PointXYZRGBA p = L->points[i];
				double d = operation::dist(p, O_t->at(l));
				gc->setDataCost(i,l,d);
			}
		}
		
		//SET N-LINKS
		cout<<"set N-Links for "<<mesh->polygons.size()<<" faces"<<endl;
		for(int i=0; i<mesh->polygons.size();i++){
			int a = mesh->polygons[i].vertices.at(0);
			for(int j=1; j<mesh->polygons[i].vertices.size();j++)
			{
				int b = mesh->polygons[i].vertices.at(j);
				gc->setNeighbors(a,b,1);
				gc->setNeighbors(b,a,1);
			}

		}
		//Set Smoothnes Cost
		for ( int l1 = 0; l1 < labelsO->size(); l1++ ){
				for (int l2 = 0; l2 < labelsO->size(); l2++ ){
					int cost = l1==l2 ? 0:1;
					gc->setSmoothCost(l1,l2,cost);

			}
		}
		cout<<"start Alpha expansion... "<<endl;
		printf("\nBefore optimization energy is %d",gc->compute_energy());
		gc->expansion(2);// run expansion for 2 iterations. For swap use gc->swap(num_iterations);
		printf("\nAfter optimization energy is %d",gc->compute_energy());
		cout<<"DONE"<<endl;


		
		LeafLabels->clear();
		for(int i=0;i<labelsO->size();i++){
			PointCloudT::Ptr tmp_Ptr;
			tmp_Ptr.reset(new PointCloudT);
			LeafLabels->push_back(labelsO->at(i));
			leafs->push_back(tmp_Ptr);
		}
		for(int i=0;i<L->size();i++)
		{
			int label = gc->whatLabel(i);
			leafs->at(label)->push_back(L->points[i]);
		}
		
		delete gc;
		return;

	}
}//end namespace Segmentation