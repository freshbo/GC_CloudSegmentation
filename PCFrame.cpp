#pragma once
#include "PCFrame.h"


	PCFrame::PCFrame(void){
		singleCloud.reset(new PointCloudT());
		singleNormal.reset(new PointCloudN());
	}
	PCFrame::~PCFrame(void){ }

