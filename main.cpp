#include "mainwindow.h"
#include <QtGui/QApplication>
#include <iostream>

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



int main(int argc, char *argv[])
{
	

/*	std::cout<<"# arguments: " << argc<<std::endl
			 << "argument #1: " << argv[0]<< std::endl;*/
	if(argc==2){
		if(fileExists(argv[1]))
		{
			std::cout<<" ---------------------------------------------------------------------------"<<std::endl
					 <<" |                                                                         |"<<std::endl
					 <<" |                                                                         |"<<std::endl
					 <<" |                                                                         |"<<std::endl
					 <<" |                                                                         |"<<std::endl
					 <<" |                                                                         |"<<std::endl
					 <<" ---------------------------------------------------------------------------"<<std::endl;

			
		}
	}
	
	if(argc<2)
	{
		QApplication a(argc, argv);
		MainWindow w;
		w.show();
		return 	a.exec();;
	}

	return 0;
}
