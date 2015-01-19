#pragma once

#include "operation.h"
#include <vector>

struct PCFrame
{
	PCFrame(void);
	~PCFrame(void);
	
	std::vector<PointCloudT::Ptr> clouds;
	std::vector<PointCloudN::Ptr> normals;
	std::vector<string> ID;
	
	PointCloudT::Ptr singleCloud;
	PointCloudN::Ptr singleNormal;
	boost::shared_ptr<string> singleID;


};
