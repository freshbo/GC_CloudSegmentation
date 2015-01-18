#pragma once
#include <vector>



inline bool fileExists (const std::string &name)
{
	ifstream f(name.c_str());
	if (f.good()) {
		f.close();
		return true;
	} else {
		f.close();
		return false;
	}   
};

