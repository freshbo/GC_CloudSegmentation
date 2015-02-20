#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   	ui->setupUi(this);
	this->setWindowTitle("Point Clout Segmentation");
	
	//Connect SIGNALS and SLOTS
	connect (ui->actionLoad,SIGNAL(triggered()),this,SLOT(loadFrame()));
    connect (ui->loadButton,SIGNAL(released()),this,SLOT(loadPC()));
    connect (ui->cleanButton,SIGNAL(released()),this,SLOT(cleanPC()));
	connect (ui->SegmentButton,SIGNAL(released()),this,SLOT(test(void)));

	connect (ui->computeCurvature,SIGNAL(released()),this,SLOT(computeNormals()));
	connect (ui->CurvColorCode,SIGNAL(toggled(bool)),this,SLOT(showCurvature(bool)));
	connect (ui->ShowOriginal,SIGNAL(toggled(bool)),this,SLOT(showOriginal(bool)));
	connect (ui->ShowSampling,SIGNAL(toggled(bool)),this,SLOT(showSampling(bool)));
	connect (ui->sampleButton,SIGNAL(released()),this,SLOT(downsample()));
//	connect (ui->computeTriangulation,SIGNAL(released()),this,SLOT(triangulate(void)));
	
	connect (ui->horizontalSlider_p, SIGNAL (valueChanged (int)), this, SLOT (pSliderValueChanged (int)));
	
	
	connect (ui->actionExit,SIGNAL(triggered()),this,SLOT(exit(void)));

	//Set Up VTK window
	viewer.reset(new pcl::visualization::PCLVisualizer("Viewer",false));
	ui->qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
	viewer->setBackgroundColor(0.941,0.941,0.941);
	viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());
	viewer->setCameraPose(0,0,0,1,1,1,0,0,1,0);
	ui->qvtkWidget->update ();
	
	//Init Frame
	Frame.reset(new PCFrame());
	
	//init Frame Content
	Frame->singleCloud = pcl::PointCloud<pcl::PointXYZRGBA>::Ptr(new pcl::PointCloud<pcl::PointXYZRGBA>);
	
	viewer->addPointCloud (Frame->singleCloud, *Frame->singleID); //add cloud to viewer with ID.
	viewer->addPointCloud (Frame->sampleCloud, *Frame->sampleID);
	viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, *Frame->sampleID);

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
	
	viewer->updatePointCloud(Frame->singleCloud, *Frame->singleID);
	viewer->resetCamera();
	ui->qvtkWidget->update (); //update viewer

}
void MainWindow::loadFrame(void)
{
	QString qPath = QFileDialog::getOpenFileName(this,tr("OpenFile"),tr("Files(.ply)"));
	//std::string path = (qPath.toStdString());
	//int found = path.find_last_of('/');
	//string dir = path.substr(0,found);
	
	
	
}

//Statistical Outlier Removal
void MainWindow::cleanPC(void)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr tmpIN(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::copyPointCloud(*Frame->singleCloud,*tmpIN);

	int meanK = ui->cleanMeanK->text().toFloat();
	int thresh = ui->cleanThresh->text().toFloat();

    cout<<tmpIN->size()<<endl;
	operation::outlierRemoval(tmpIN,meanK,thresh);
    cout<<tmpIN->size()<<endl;

    Frame->singleCloud->clear();
    pcl::copyPointCloud(*tmpIN,*Frame->singleCloud);
    operation::colorizeDefault(Frame->singleCloud);
    cout<<Frame->singleCloud->size()<<endl;
	viewer->updatePointCloud (Frame->singleCloud, *Frame->singleID); //update
    ui->qvtkWidget->update();
}

void MainWindow::downsample()
// this method creates a downsampled 
{
	QString textFieldInput = ui->sampleNumberField->text();
	if(textFieldInput=="")
	{	
		cout<<"please Enter Valid float"<<endl;
		return;
	}
	
	float sampleSize = textFieldInput.toFloat();
	
	operation::downsample(Frame->singleCloud,Frame->sampleCloud,sampleSize);
	operation::calcNormals(Frame->sampleCloud,Frame->sampleNormal);
	//operation::calcDownsampledeCurvature(Frame->singleCloud,Frame->singleNormal,Frame->sampleCloud,Frame->sampleNormal);
	operation::linearizeCurvature(Frame->sampleNormal);
	operation::curvatureColorMap(Frame->sampleNormal,Frame->sampleCloud);
	viewer->updatePointCloud(Frame->sampleCloud,*Frame->sampleID);
	ui->qvtkWidget->update();
	
}

//Normal Calculation
void MainWindow::computeNormals(void)
{
	std::cout<<"compute Normals"<<std::endl;
	operation::calcNormals(Frame->singleCloud,Frame->singleNormal);
	operation::linearizeCurvature(Frame->singleNormal);
	ui->ColorCode->setEnabled(true);
}




//visibility Checkboxes
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
void MainWindow::showOriginal(bool checked)
{
	if(checked)
		viewer->addPointCloud(Frame->singleCloud,*Frame->singleID);
	
	else if(!checked)
		viewer->removePointCloud(*Frame->singleID,0);

	ui->qvtkWidget->update();
}
void MainWindow::showSampling(bool checked)
{
	if(checked){
		viewer->addPointCloud(Frame->sampleCloud,*Frame->sampleID);
		viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, *Frame->sampleID);
		
		ui->InfoBox->setText("Sampled size: " + QString::number(Frame->sampleCloud->size()));
	}
	else if(!checked){
		viewer->removePointCloud(*Frame->sampleID,0);
		ui->InfoBox->setText("");
	}
	ui->qvtkWidget->update();
}




void MainWindow::exit()
{
	std::cout<<"EXINTING PROGRAM"<<std::endl;
}


void MainWindow::test()
{
	PointCloudT::Ptr result(new PointCloudT);
	Segmentation::MinCut(Frame->singleCloud,Frame->singleNormal, result);
	
	viewer->addPointCloud(result,"Test");
	ui->qvtkWidget->update();
}