#pragma once

//Qt
#include <QtGui\qfiledialog.h>
#include <QtGui\QMainWindow>
#include <QtCore\qstring.h>
#include "ui_mainwindow.h"


//Visualization Tool Kit
#include <vtkRenderWindow.h>
#include <pcl/visualization/pcl_visualizer.h>

#include "operation.h"
#include "PCFrame.h"

#include "MinCut.h"

namespace Ui 
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
	void pSliderValueChanged (int value);
	void loadPC(void);
	void clearClouds(void);
	void computeNormals(void);
	void showCurvature(bool);
	void triangulate(void);
	void test(void);
	void exit(void);
	

protected:
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
	boost::shared_ptr<PCFrame> Frame;

private:
    Ui::MainWindow	*ui;
};
