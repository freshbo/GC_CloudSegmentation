#pragma once
#include "PCFrame.h"
#include "global.h"

	hypothesis::hypothesis(void)
	{
		original.reset(new PointCloudT());				//PointCloud to work with
		
		
		ID = "";									//name in viewer
		cloud.reset(new PointCloudT());				//PointCloud to work with
		normal.reset(new PointCloudN());			//Normals
		triangulation.reset(new pclMesh());
		
		L.reset(new PointCloudT());					//Leaf Points
		leafs.reset(new vector<PointCloudT::Ptr>);

		S.reset(new PointCloudT());					//Stem Points

		phi  =	0;									//phi Function |L| x |S|  Gives the number of Organs (leafs x stems)
		

		//Render Sequence
		renderSeq =-1;
		
		//GUI booleans.. curvature, or segmentation already computed? 
		curv	=	false;
		binSeg	=	false;
		down	=	false;
		tri		=	false;
		
		
	}


	hypothesis::~hypothesis(void)
	{}

