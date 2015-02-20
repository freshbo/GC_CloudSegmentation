#pragma once

#include "operation.h"
#include <vector>
#include <string>

struct container
{
	container(void);
	container(PointCloudT cloud ,PointCloudN normals, std::string ID);
	~container(void);
	
	std::vector<PointCloudT::Ptr> clouds;
	std::vector<PointCloudN::Ptr> normals;
	std::vector<string> ID;
	
	PointCloudT::Ptr singleCloud;
	PointCloudN::Ptr singleNormal;
	PointCloudT::Ptr sampleCloud;
	PointCloudN::Ptr sampleNormal;
	boost::shared_ptr<string> singleID;
	boost::shared_ptr<string> sampleID;

};
