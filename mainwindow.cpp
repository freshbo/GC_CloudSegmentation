#include "mainwindow.h"

#include "global.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   	ui->setupUi(this);
	this->setWindowTitle("Point Clout Segmentation");
	
	/*	SLOTS	*/
	//Load Point Clouds, Frames
	connect (ui->actionLoad,		SIGNAL(triggered()),this,			SLOT(loadFrame())); //not yet implemented
    connect (ui->loadButton,		SIGNAL(released()),this,			SLOT(loadPC()));
	//Controller: Which PointCloud can be seen?
	connect (ui->FrameScrollBar,	SIGNAL(valueChanged(int)), this,	SLOT(frameScroll(int)));
	//Calculate Curvature, Segmentations, Downsampling,Triangulation
	connect (ui->computeCurvature,	SIGNAL(released()),this,			SLOT(computeCurvature()));
	connect (ui->SegmentButton,		SIGNAL(released()),this,			SLOT(BinSeg(void)));
	connect (ui->MultiLeafButton,	SIGNAL(released()),this,			SLOT(LeafSeg(void)));
	connect (ui->sampleButton,		SIGNAL(released()),this,			SLOT(downsample()));	
	connect (ui->triangulationButton,SIGNAL(released()),this,			SLOT(triangulation()));
	//Gui State (see orig. color, Curvature, Segmentations, PointSize in Viewer, etc)
	connect (ui->ShowOriginal,		SIGNAL(toggled(bool)),this,			SLOT(updateGUIstate(bool)));
	connect (ui->CurvColorCode,		SIGNAL(toggled(bool)),this,			SLOT(updateGUIstate(bool)));
	connect (ui->SegColorCode,		SIGNAL(toggled(bool)),this,			SLOT(updateGUIstate(bool)));
	connect (ui->horizontalSlider_p,SIGNAL (valueChanged (int)), this,	SLOT (pSliderValueChanged (int)));
	connect (ui->ShowMesh,			SIGNAL(toggled(bool)),this,			SLOT(showCloud()));	
	connect (ui->ShowLeafs,			SIGNAL(toggled(bool)),this,			SLOT(showCloud()));	
	//Exit Program
	connect (ui->actionExit,		SIGNAL(triggered()),this,			SLOT(close()));

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
	std::string name = path.substr(slash+1,dot-slash-1);
	
	string endung = path.substr(dot+1,-1);
	if(endung!="ply")
		return;
	cout<<"load "<<name<<endl;
	//set File name as File name in hypothesis.
	H_t->ID = name;
			
	//load file into the PCL
	string ID = operation::loadPLY(path,H_t->original); //load PLY into cloud;
	//default (green) color:
	pcl::copyPointCloud(*H_t->original, *H_t->cloud);
	operation::colorizeDefault(H_t->cloud);
	
	//clear viewport
	viewer->removeAllPointClouds();
	//add recently added point cloud to viewer
	viewer->addPointCloud(H_t->cloud, H_t->ID);
	
	//update
	if(t==-1)
		viewer->resetCamera();
	ui->qvtkWidget->update (); //update viewer
	
	//push added to the vector
	Frame.push_back(H_t);
	
	t = Frame.size()-1;
	
	//set correct slider properties
	ui->FrameScrollBar->setMaximum(t);
	ui->FrameScrollBar->setValue(t);
	
	
	ui->PCNumberLABEL->setText("");
	ui->InfoBox->setText("");
	ui->CloudSizeLABEL->setText("");	
	showCloud();

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
	g_renderSeq++;
	showCloud();
}

void MainWindow::showCloud(void)
{
	if(t==-1) //No Cloud loaded
		return;
	
	if(Frame[t]->renderSeq==g_renderSeq) //Nothing has changed in the GUI
		return;
	//If something has changed, remove all clouds
	viewer->removeAllPointClouds();
	
	if(ui->CurvColorCode->isChecked()&& Frame[t]->curv)
	{
		operation::colorizeCurvature(Frame[t]->normal,Frame[t]->cloud);
		viewer->addPointCloud(Frame[t]->cloud,Frame[t]->ID);
		viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, ui->horizontalSlider_p->value(), Frame[t]->ID);
	}
	
	else if(ui->SegColorCode->isChecked() && Frame[t]->binSeg)
	{
		operation::colorizeBinCluster(Frame[t]->cloud,Frame[t]->binCluster);	
		viewer->addPointCloud(Frame[t]->cloud,Frame[t]->ID);
		viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, ui->horizontalSlider_p->value(), Frame[t]->ID);
	}

	else if(ui->ShowLeafs->isChecked()&&Frame[t]->leafs->size()!=0)
	{
		for(int i=0;i< Frame[t]->leafs->size();i++)
			{
				QString asd(i);
				string tmp = asd.toStdString();
				viewer->addPointCloud(Frame[t]->leafs->at(i),tmp);
				viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, ui->horizontalSlider_p->value(), tmp);
			}
		operation::colorizeDefault(Frame[t]->S);
		viewer->addPointCloud(Frame[t]->S,"Stems");
		viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE,ui->horizontalSlider_p->value(), "Stems");
	}
	else
	{
		operation::colorizeDefault(Frame[t]->cloud);
		viewer->addPointCloud(Frame[t]->cloud,Frame[t]->ID);
		viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, ui->horizontalSlider_p->value(), Frame[t]->ID);
	}
	
	ui->PCNumberLABEL->setText(QString::number(t));
	ui->InfoBox->setText(QString::fromStdString(Frame[t]->ID));
	ui->CloudSizeLABEL->setText(QString::number(Frame[t]->cloud->size()));
	
	//Update GUI
	ui->qvtkWidget->update();
	
	ui->PCNumberLABEL->update();
	ui->InfoBox->update();
	ui->CloudSizeLABEL->update();
	

}


void MainWindow::computeCurvature(void)
{
	if(t==-1)
		return;
	if(ui->sampleNumberField->text()!="0")
		operation::downsample(Frame[t]->original,Frame[t]->cloud,0.2);
	cout<<"Calculate Curvature values...";
	operation::calcCurvature(Frame[t]->cloud,Frame[t]->normal);
	cout<<" DONE"<<endl;
	//render Properties
	Frame[t]->curv = true;
	Frame[t]->renderSeq=-1;
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
		cout<<"please Enter a valid float"<<endl;
		return;
	}
	float sampleSize = textFieldInput.toFloat();
	operation::downsample(Frame[t]->original, Frame[t]->cloud,sampleSize);
	Frame[t]->renderSeq=-1;
	Frame[t]->tri = false;
	Frame[t]->binSeg=false;
	Frame[t]->curv = false;
	MainWindow::showCloud();

}

void MainWindow::triangulation(void)
{
	if(t==-1)
		return;
	if(Frame[t]->cloud->size() != Frame[t]->normal->size())
		operation::calcCurvature(Frame[t]->cloud,Frame[t]->normal);
	operation::PCLtriangulation(Frame[t]->cloud,Frame[t]->normal,Frame[t]->triangulation);
	Frame[t]->tri = true;
	MainWindow::showCloud();

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
	showCloud();
	ui->qvtkWidget->update();
}

void MainWindow::BinSeg()
{
	if(t==-1)
		return;
	if(!Frame[t]->curv)
		computeCurvature();
	cout<<"Calculate Binary Segmentation...";
	Frame[t]->binCluster = Segmentation::binary(Frame[t]->cloud,Frame[t]->normal, Frame[t]->L,Frame[t]->S);
	cout<<" DONE"<<endl;
	
	//render Properties
	Frame[t]->binSeg=true;
	Frame[t]->renderSeq=-1;
	showCloud();
}

void MainWindow::LeafSeg(void)
{
	if(t==-1)
		return;
	if(Frame[t]->binSeg==false){
		BinSeg();
		Frame[t]->binSeg=true;
		Frame[t]->leafs->clear();
	}
	if(t==0)
	{
		cout<<"Get Connected Components...";
		Segmentation::getConnectedLeafs(Frame[t]->L,/*vectorCloud*/Frame[t]->leafs,&Frame[t]->LeafLabels);
		cout<<" DONE"<<" ";
		cout<<"Found "<<Frame[t]->LeafLabels.size()<<" mature Leafs"<<endl;
		
		operation::colorizeLeafClusters(Frame[t]->leafs,Frame[t]->LeafLabels);
		Frame[t]->renderSeq=-1;
		showCloud();
		return;
	}else
		Segmentation::multiOrganSegmentation(Frame[t]->L,Frame[t-1]->leafs,&Frame[t-1]->LeafLabels,/*Output:*/Frame[t]->leafs,&Frame[t]->LeafLabels);
	operation::colorizeLeafClusters(Frame[t]->leafs,Frame[t]->LeafLabels);	
	showCloud();
				
	
}

