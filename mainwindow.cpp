#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   	ui->setupUi(this);
	this->setWindowTitle("Point Clout Segmentation");
	
	//Connect SIGNALS and SLOTS
	connect (ui->actionLoad,SIGNAL(triggered()),this,SLOT(loadPC()));
	connect (ui->horizontalSlider_p, SIGNAL (valueChanged (int)), this, SLOT (pSliderValueChanged (int)));
	connect (ui->actionClear_Clouds,SIGNAL(triggered()),this,SLOT(clearClouds()));
	connect (ui->computeCurvature,SIGNAL(released()),this,SLOT(computeNormals()));
	connect (ui->computeTriangulation,SIGNAL(released()),this,SLOT(triangulate(void)));
	connect (ui->ColorCode,SIGNAL(toggled(bool)),this,SLOT(showCurvature(bool)));
	connect (ui->testButton,SIGNAL(released()),this,SLOT(test(void)));
	connect (ui->actionExit,SIGNAL(triggered()),this,SLOT(exit(void)));

	//Set Up VTK window
	viewer.reset(new pcl::visualization::PCLVisualizer("Viewer",false));
	ui->qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
	viewer->setBackgroundColor(0,0,0);
	viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());
	viewer->setCameraPose(0,0,0,1,1,1,0,0,1,0);
	ui->qvtkWidget->update ();
	
	//Init Frame
	Frame.reset(new PCFrame());
	
}

//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

/*
FROM HERE ON FOLLOW THE SLOTS OF MAINWINDOW
pSliderValueChanged()
loadPC()
clearClouds()
computeNormals()
showCurvature
exit()

*/
void MainWindow::pSliderValueChanged (int value)
{
	/*
	This function lets me controll the Size of the Points
	It is calles whenever the GUI-Slider is changed.
	*/
	viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, value, *Frame->singleID);
	ui->qvtkWidget->update();
}


void MainWindow::loadPC(void)
{
	//this block reads the file path
	QString qPath = QFileDialog::getOpenFileName(this,tr("OpenFile"),tr("Files(.ply)"));
	const std::string path = (qPath.toStdString());
		
	string ID = operation::loadPLY(path,Frame->singleCloud); //load PLY into cloud;
	operation::colorizeDefault(Frame->singleCloud);
	Frame->singleID.reset(new string(ID));
	
	viewer->addPointCloud (Frame->singleCloud, *Frame->singleID); //add cloud to viewer with ID.
	viewer->resetCamera ();
	ui->qvtkWidget->update (); //update viewer
}


void MainWindow::clearClouds(void)
{
	viewer->removeAllPointClouds();
	ui->qvtkWidget->update();
}

void MainWindow::computeNormals(void)
{
	std::cout<<"compute Normals"<<std::endl;
	operation::calcNormals(Frame->singleCloud,Frame->singleNormal);
	operation::linearizeCurvature(Frame->singleNormal);
	ui->ColorCode->setEnabled(true);

	//ui->rButton_Curvature->click();
}

void MainWindow::showCurvature(bool checked)
{
	if(checked)
		//(http://www.vtk.org/doc/nightly/html/classvtkColorLegend.html) VTK legend.
		operation::curvatureColorMap(Frame->singleNormal,Frame->singleCloud);
	
	else if(!checked)
		operation::colorizeDefault(Frame->singleCloud);
		
	std::cout<<*Frame->singleID<<std::endl;
	viewer->updatePointCloud (Frame->singleCloud, *Frame->singleID); //update
	ui->qvtkWidget->update();
}

void MainWindow::triangulate(void)
{
	std::cout<<"TRIANGULATE"<<std::endl;
	Mesh triangles = operation::PCLtriangulation(Frame->singleCloud,Frame->singleNormal);
	viewer->addPolygonMesh(triangles,"Mesh");
	ui->qvtkWidget->update();
}
void MainWindow::test(void)
{
	
	cutIt(Frame->singleCloud,Frame->singleNormal);

	viewer->updatePointCloud (Frame->singleCloud, *Frame->singleID); //update
	ui->qvtkWidget->update();
}

void MainWindow::exit()
{
	std::cout<<"EXINTING PROGRAM"<<std::endl;
}
