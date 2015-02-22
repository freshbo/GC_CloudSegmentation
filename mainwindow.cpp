#include "mainwindow.h"

#include "global.h"

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
	connect (ui->FrameScrollBar, SIGNAL(valueChanged(int)), this, SLOT(frameScroll(int)));
	connect (ui->computeCurvature,SIGNAL(released()),this,SLOT(computeNormals()));
	connect (ui->CurvColorCode,SIGNAL(toggled(bool)),this,SLOT(showCurvature(bool)));
	connect (ui->sampleButton,SIGNAL(released()),this,SLOT(downsample()));	
	connect (ui->horizontalSlider_p, SIGNAL (valueChanged (int)), this, SLOT (pSliderValueChanged (int)));
	connect (ui->actionExit,SIGNAL(triggered()),this,SLOT(exit(void)));

	
	//Set Up VTK window
	viewer.reset(new pcl::visualization::PCLVisualizer("Viewer",false));
	ui->qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
	viewer->setBackgroundColor(0.941,0.941,0.941);
	viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());

	//sets the currently selected Point Cloud
	t = 0;

	
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

void MainWindow::frameScroll(int value)
{
	t = value;

	showCloud();
	ui->PCNumberLABEL->setText(QString::number(t));
	
	//set viewer to correct cloud



}

void MainWindow::showCloud(void)
{
	
	viewer->removeAllPointClouds();

	if(ui->CurvColorCode->isChecked()&& Frame.at(t)->curv)
		operation::curvatureColorMap(Frame.at(t)->normal,Frame.at(t)->cloud);
	else if(ui->SegColorCode->isChecked() && Frame.at(t)->binSeg)
		operation::colorizeCluster(Frame.at(t)->cloud,Frame.at(t)->binCluster);
	else
		operation::colorizeDefault(Frame.at(t)->cloud);
	
	
	viewer->addPointCloud(Frame.at(t)->cloud,Frame.at(t)->ID);
	viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, ui->horizontalSlider_p->value(), Frame.at(t)->ID);
	ui->qvtkWidget->update();
	
}

void MainWindow::pSliderValueChanged (int value)
{
	/*
	This function lets me controll the Size of the Points
	It is calles whenever the GUI-Slider is changed.
	*/
	viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, value, Frame.at(t)->ID);
	ui->qvtkWidget->update();
	
}

void MainWindow::loadPC(void)
{
	

	boost::shared_ptr<hypothesis> H_t (new hypothesis);
	
	//read the file path
	QString qPath = QFileDialog::getOpenFileName(this,tr("OpenFile"),tr("Files(.ply)"));
	const std::string path = (qPath.toStdString());
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
	
	//set correct slider properties
	ui->FrameScrollBar->setMaximum(Frame.size()-1);
	ui->FrameScrollBar->setValue(Frame.size()-1);
	t = Frame.size()-1;

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

//Normal Calculation
void MainWindow::computeNormals(void)
{
	
	std::cout<<"compute Normals"<<std::endl;
	operation::calcNormals(Frame.at(t)->cloud,Frame.at(t)->normal);
	Frame.at(t)->curv = true;
}

//Statistical Outlier Removal
void MainWindow::cleanPC(void)
{
	
	/*
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
	*/
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
	
	operation::downsample(Frame.at(t)->cloud,sampleSize);
	//operation::calcNormals(Frame.at(t)->sampleC,Frame.at(t)->sampleN);

	
	//operation::curvatureColorMap(Frame.at(t)->sampleN,Frame.at(t)->sampleC);
	viewer->updatePointCloud(Frame.at(t)->cloud,Frame.at(t)->ID);
	ui->qvtkWidget->update();
}




//visibility Checkboxes
void MainWindow::showCurvature(bool checked)
{
	
	if(checked)
		//(http://www.vtk.org/doc/nightly/html/classvtkColorLegend.html) VTK legend.
		operation::curvatureColorMap(Frame.at(t)->normal,Frame.at(t)->cloud);
	
	else if(!checked)
		operation::colorizeDefault(Frame.at(t)->cloud);
		
	
	viewer->updatePointCloud (Frame.at(t)->cloud, Frame.at(t)->ID); //update
	ui->qvtkWidget->update();
	
}







void MainWindow::exit()
{
	std::cout<<"EXINTING PROGRAM"<<std::endl;
}


void MainWindow::test()
{
	
	Frame.at(t)->binCluster = Segmentation::MinCut(Frame.at(t)->cloud,Frame.at(t)->normal, Frame.at(t)->L,Frame.at(t)->S);
	
	viewer->removeAllPointClouds();
	viewer->addPointCloud(Frame.at(t)->L,Frame.at(t)->ID);
	ui->qvtkWidget->update();
	Frame.at(t)->binSeg=true;
}