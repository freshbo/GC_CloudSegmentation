#include "mainwindow.h"
#include <QtGui/QApplication>
#include "header.h"
#include <iostream>



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
