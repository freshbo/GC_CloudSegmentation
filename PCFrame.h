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
	vectorCloud leafs; //Vector containing each leaf as PointCloudT
	vector<int>LeafLabels;		//represents the label number of each leaf in vector leaf

	PointCloudT::Ptr S;			//binary segmented cloud: All Stem Points
	vectorCloud stems; //Vector containing each stem as PointCloudT
	vector<int>StemLabels;		//represents the label number of each stem in vector stem

	
	
	
	int phi;

	bool curv;
	bool binSeg;
	bool down;
	bool tri;


	//viewer Update:
	int renderSeq;

};

