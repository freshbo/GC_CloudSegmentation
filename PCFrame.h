#pragma once

#include "operation.h"
#include <vector>
#include <string>

struct hypothesis
{
	hypothesis(void);
	~hypothesis(void);
	
	PointCloudT::Ptr original;

	string ID;					//name of the Cloud in Viewer
	PointCloudT::Ptr cloud;		//stores all points of the PointCloud
	PointCloudN::Ptr normal;	//stores the corresponding normals and curvature to cloud
	pclMesh::Ptr triangulation;
	
	/*  Binary Clustering  */
	vector<int> binCluster;		//represents as Integer the Cluster each Point of cloud belongs to
	PointCloudT::Ptr L;			//binary segmented cloud: All leaf points
	vector<int>LCluster;		//represents as integer the Leaf each Point in L belongs to
	PointCloudT::Ptr S;			//binary segmented cloud: All Stem Points
	vector<int>SCluster;		//represents as integer the Leaf each Point in L belongs to

	
	
	
	int phi;

	bool curv;
	bool binSeg;
	bool down;
	bool tri;


	//viewer Update:
	int renderSeq;

};

