#pragma once
#include "PCFrame.h"


	container::container(void)
	{
		singleCloud.reset(new PointCloudT());
		singleNormal.reset(new PointCloudN());
		sampleCloud.reset(new PointCloudT());	
		sampleNormal.reset(new PointCloudN());	
		singleID.reset(new string("single"));
		sampleID.reset(new string("sample"));
	}
	container::container(PointCloudT cloud ,PointCloudN normals, std::string ID)
	{

	}
	container::~container(void)
	{
		

	}

