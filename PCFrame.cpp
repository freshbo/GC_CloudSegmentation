#pragma once
#include "PCFrame.h"


	hypothesis::hypothesis(void)
	{
		
		
		ID = "";									//name in viewer
		cloud.reset(new PointCloudT());				//PointCloud to work with
		normal.reset(new PointCloudN());			//Normals
		
		L.reset(new PointCloudT());					//Leaf Points
		S.reset(new PointCloudT());					//Stem Points

		phi  =	0;									//phi Function |L| x |S|  Gives the number of Organs (leafs x stems)
		
		
		
		//GUI booleans.. curvature, or segmentation already computed? 
		curv	=	false;
		binSeg	=	false;
		down	=	false;
		
		
	}

	hypothesis::hypothesis(PointCloudT cloud ,PointCloudN normals, std::string ID)
	{}

	hypothesis::~hypothesis(void)
	{}

