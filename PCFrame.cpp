#pragma once
#include "PCFrame.h"


	container::PCFrame(void)
	{
		singleCloud.reset(new PointCloudT());
		singleNormal.reset(new PointCloudN());
		sampleCloud.reset(new PointCloudT());	
		sampleNormal.reset(new PointCloudN());	
		singleID.reset(new string("single"));
		sampleID.reset(new string("sample"));
	}
	container::~PCFrame(void)
	{

	}

