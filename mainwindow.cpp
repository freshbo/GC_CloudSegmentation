#include "mainwindow.h"

#include "global.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   	ui->setupUi(this);
	this->setWindowTitle("Point Clout Segmentation");
	
	/*	SLOTS	*/
	//Load Point Clouds, Frames
	connect (ui->actionLoad,SIGNAL(triggered()),this,SLOT(loadFrame())); //not yet implemented
    connect (ui->loadButton,SIGNAL(released()),this,SLOT(loadPC()));
	//Controller: Which PointCloud can be seen?
	connect (ui->FrameScrollBar, SIGNAL(valueChanged(int)), this, SLOT(frameScroll(int)));
	//Outlier Removal
	connect (ui->cleanButton,SIGNAL(released()),this,SLOT(statisticalOutliers()));
	//Calculate Curvature, Segmentations, Downsampling,Triangulation
	connect (ui->computeCurvature,SIGNAL(released()),this,SLOT(computeCurvature()));
	connect (ui->SegmentButton,SIGNAL(released()),this,SLOT(BinSeg(void)));
	connect (ui->sampleButton,SIGNAL(released()),this,SLOT(downsample()));	
	connect (ui->triangulationButton,SIGNAL(released()),this,SLOT(triangulation()));	
	
	
	//Gui State (see orig. color, Curvature, Segmentations, PointSize in Viewer, etc)
	connect (ui->ShowOriginal,SIGNAL(toggled(bool)),this,SLOT(updateGUIstate(bool)));
	connect (ui->CurvColorCode,SIGNAL(toggled(bool)),this,SLOT(updateGUIstate(bool)));
	connect (ui->SegColorCode,SIGNAL(toggled(bool)),this,SLOT(updateGUIstate(bool)));
	connect (ui->horizontalSlider_p, SIGNAL (valueChanged (int)), this, SLOT (pSliderValueChanged (int)));
	connect (ui->ShowMesh,SIGNAL(toggled(bool)),this,SLOT(showCloud()));	
	//Exit Program
	connect (ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));

	//Set Up VTK window
	viewer.reset(new pcl::visualization::PCLVisualizer("Viewer",false));
	ui->qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
	viewer->setBackgroundColor(0.941,0.941,0.941);
	viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());

	//init current PointCloud
	t = -1;

	
}
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
void MainWindow::loadPC(void)
{
	boost::shared_ptr<hypothesis> H_t (new hypothesis);
	
	//read the file path
	QString qPath = QFileDialog::getOpenFileName(this,tr("OpenFile"),tr("Files(.ply)"));
	const std::string path = (qPath.toStdString());
	if (path=="")
		return;
	//determine File name
	int slash = path.find_last_of('/');
	int dot   = path.find_last_of(".");
	cout<<slash<<"  "<<dot<<endl;
	std::string name = path.substr(slash+1,dot-slash-1);
	cout<<"load "<<name<<endl;
	//set File name as File name in hypothesis.
	H_t->ID = name;
			
	//load file into the PCL
	string ID = operation::loadPLY(path,H_t->cloud); //load PLY into cloud;
	//default (green) color:
	operation::colorizeDefault(H_t->cloud);
	
	//clear viewport
	viewer->removeAllPointClouds();
	//add recently added point cloud to viewer
	viewer->addPointCloud(H_t->cloud, H_t->ID);
	
	//update
	viewer->resetCamera();
	ui->qvtkWidget->update (); //update viewer
	
	//push added to the vector
	Frame.push_back(H_t);
	
	t = Frame.size()-1;
	//set correct slider properties
	ui->FrameScrollBar->setMaximum(t);
	ui->FrameScrollBar->setValue(t);
	

}

void MainWindow::loadFrame(void)
{
	/*
	QString qPath = QFileDialog::getOpenFileName(this,tr("OpenFile"),tr("Files(.ply)"));
	//std::string path = (qPath.toStdString());
	//int found = path.find_last_of('/');
	//string dir = path.substr(0,found);
	*/
	
}

void MainWindow::frameScroll(int value)
{
	t = value;
	showCloud();
}

void MainWindow::showCloud(void)
{
	if(t==-1)
		return;
	if (Frame.at(t)->renderSeq!=g_renderSeq){
		Frame.at(t)->renderSeq = g_renderSeq;

		if(ui->CurvColorCode->isChecked()&& Frame.at(t)->curv)
			operation::colorizeCurvature(Frame.at(t)->normal,Frame.at(t)->cloud);
		else if(ui->SegColorCode->isChecked() && Frame.at(t)->binSeg)
			operation::colorizeBinCluster(Frame.at(t)->cloud,Frame.at(t)->binCluster);
		else
			operation::colorizeDefault(Frame.at(t)->cloud);
	}

	viewer->removeAllPointClouds();
	viewer->addPointCloud(Frame.at(t)->cloud,Frame.at(t)->ID);
	viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, ui->horizontalSlider_p->value(), Frame.at(t)->ID);
	
	
	if(Frame.at(t)->tri && ui->ShowMesh->isChecked())
		viewer->addPolygonMesh(*Frame.at(t)->triangulation, "mesh");
	else
		viewer->removePolygonMesh("mesh");
	
	

	ui->PCNumberLABEL->setText(QString::number(t));
	ui->InfoBox->setText(QString::fromStdString(Frame.at(t)->ID));
	ui->CloudSizeLABEL->setText(QString::number(Frame.at(t)->cloud->size()));	

	ui->qvtkWidget->update();
}


//Outlier
void MainWindow::statisticalOutliers(void)
{
	if(t==-1)
		return;
    pcl::PointCloud<pcl::PointXYZ>::Ptr tmpIN(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::copyPointCloud(*Frame.at(t)->cloud,*tmpIN);

	int meanK = ui->cleanMeanK->text().toFloat();
	int thresh = ui->cleanThresh->text().toFloat();

    cout<<tmpIN->size()<<endl;
	operation::statisticalOutlierRemoval(tmpIN,meanK,thresh);
    cout<<tmpIN->size()<<endl;

	Frame.at(t)->cloud->clear();
    pcl::copyPointCloud(*tmpIN,*Frame.at(t)->cloud);
    showCloud();
	
}
void MainWindow::radiusOutliers(void)
{
	if(t==-1)
		return;
	pcl::PointCloud<pcl::PointXYZ>::Ptr tmpIN(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::copyPointCloud(*Frame.at(t)->cloud,*tmpIN);
	
	float radius = -1;
	radius = ui->cleanMeanK->text().toFloat();
	if (radius<0)
		cout<<"pleaseEnter a positive Radius"<<endl;

    cout<<tmpIN->size()<<endl;
	operation::radiusOutlierRemoval(tmpIN,radius);
    cout<<tmpIN->size()<<endl;

	Frame.at(t)->cloud->clear();
    pcl::copyPointCloud(*tmpIN,*Frame.at(t)->cloud);
    showCloud();
}



//Calculations
void MainWindow::computeCurvature(void)
{
	if(t==-1)
		return;
	std::cout<<"compute Normals"<<std::endl;
	operation::calcCurvature(Frame.at(t)->cloud,Frame.at(t)->normal);
	//render Properties
	Frame.at(t)->curv = true;
	Frame.at(t)->renderSeq=-1;
	showCloud();
}
void MainWindow::downsample()
// this method creates a downsampled 
{	
	if(t==-1)
		return;
	QString textFieldInput = ui->sampleNumberField->text();
	if(textFieldInput=="")
	{	
		cout<<"please Enter Valid float"<<endl;
		return;
	}
	float sampleSize = textFieldInput.toFloat();
	operation::downsample(Frame.at(t)->cloud,sampleSize);
	MainWindow::showCloud();
}
void MainWindow::triangulation(void)
{
	if(t==-1)
		return;
	if(Frame.at(t)->cloud->size() != Frame.at(t)->normal->size())
		operation::calcCurvature(Frame.at(t)->cloud,Frame.at(t)->normal);
	operation::PCLtriangulation(Frame.at(t)->cloud,Frame.at(t)->normal,Frame.at(t)->triangulation);
	Frame.at(t)->tri = true;
	MainWindow::showCloud();
	
	ui->qvtkWidget->update();
}




//Gui State
void MainWindow::updateGUIstate(bool)
{	
	//Called whenever a Radio Button is changed:
	if(t==-1)
		return;
	g_renderSeq++;
	showCloud();
}
//Point Size
void MainWindow::pSliderValueChanged (int value)
{
	if(t==-1)
		return;
	viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, value, Frame.at(t)->ID);
	ui->qvtkWidget->update();
	
}

void MainWindow::BinSeg()
{
	if(t==-1)
		return;
	if(!Frame.at(t)->curv)
		computeCurvature();
	Frame.at(t)->binCluster = Segmentation::binary(Frame.at(t)->cloud,Frame.at(t)->normal, Frame.at(t)->L,Frame.at(t)->S);
	//render Properties
	Frame.at(t)->binSeg=true;
	Frame.at(t)->renderSeq=-1;
	showCloud();
}